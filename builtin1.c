#include "shell.h"

/**
 * exit_shell - terminates the shell
 * @info: Structure holding potential arguments. Maintains
 * a constant function prototype.
 *  Return: exits with a specified exit status
 * (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1])  /* If an exit argument is present */
	{
		exit_status = _erratoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - modifies the process's current directory
 * @info: Structure holding potential arguments. Maintains
 * constant function prototype.
 *
 *  Return: Always 0
 */
int change_directory(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_result = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - shows help for the shell
 * @info: Structure holding potential arguments. Maintains
 *          constant function prototype.
 *  Return: Always 0
 */
int display_help(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args); /* temporary att_unused workaround */
	return (0);
}
```
