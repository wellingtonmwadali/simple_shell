
#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: parameter
 * @av: argument vector
 *
 * Return: on success 0, on failure 1
 */
int shell_loop(info_t *info, char **av)
{
	ssize_t input_read = 0;
	int builtin_result = 0;

	while (input_read != -1 && builtin_result != -2)
	{
		reset_info(info);
		if (is_interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_read = read_input(info);
		if (input_read != -1)
		{
			update_info(info, av);
			builtin_result = locate_builtin(info);
			if (builtin_result == -1)
				locate_command(info);
		}
		else if (is_interactive(info))
			__putchar('\n');
		free_info(info, 0);
	}
	save_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * locate_builtin - function that locates a builtin command
 * @info: parameter
 *
 * Return: 0 if builtin is executed succcessfully
 *	1 if builtin is found but not successfull
 *	-1 if builtin is not found
 *	-2 if builtin signals exit()
 */
int locate_builtin(info_t *info)
{
	int t, builtin_result = -1;
	builtin_table builtin_tbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (t = 0; builtintbl[t].type; t++)
		if (_strcmp(info->argv[0], builtintbl[t].type) == 0)
		{
			info->line_count++;
			builtin_result = builtintbl[t].func(info);
			break;
		}
	return (builtin_result);
}

/**
 * locate_command - function that Finds a command in PATH
 * @info: parameter containing potential arguments
 *
 * Return: nothing
 */
void locate_command(info_t *info)
{
	char *path = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[i], " \t\n"))
			y++;
	if (!y)
		return;

	path = search_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		execute_command(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			execute_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_error(info, "not found\n");
		}
	}
}

/**
 * execute_command - Forks an exec thread to run a command
 * @info: parameter containing potentiial arguments
 *
 * Return: nothing
 */
void execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_error(info, "Permission denied\n");
		}
	}
}

