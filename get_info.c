#include "shell.h"

/**
 * clear_information - function that nitializes info_t struct.
 * @info: Address of struct to initialize.
 *
 * Return: nothing
 */
void clear_information(info_t *info)
{
	info->command = NULL;
	info->command_args = NULL;
	info->path = NULL;
	info->command_arg_count = 0;
}

/**
 * set_information - function that Sets info_t struct fields.
 * @info: Address of struct to set fields for.
 * @argv: Argument vector.
 *
 * Return: nothing
 */
void set_information(info_t *info, char **argv)
{
	int t = 0;

	info->shell_name = argv[0];

	if (info->command)
	{
		info->command_args = strtow(info->command, " \t");
		if (!info->command_args)
		{

			info->command_args = malloc(sizeof(char *) * 2);
			if (info->command_args)
			{
				info->command_args[0] = _strdup(info->command);
				info->command_args[1] = NULL;
			}
		}

		for (t = 0; info->command_args && info->command_args[t]; t++)
			;
		info->command_arg_count = t;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_information - Function that frees info_t struct fields.
 * @info: Address of struct to free fields for.
 * @free_all: If true, free all fields.
 *
 * Return: 0
 */
void free_information(info_t *info, int free_all)
{
	ffree(info->command_args);
	info->command_args = NULL;
	info->path = NULL;

	if (free_all)
	{
		if (!info->command_buffer)
			free(info->command);
		if (info->env_list)
			free_list(&(info->env_list));
		if (info->history_list)
			free_list(&(info->history_list));
		if (info->alias_list)
			free_list(&(info->alias_list));

		ffree(info->environment);
		info->environment = NULL;

		bfree((void **)info->command_buffer);

		if (info->read_fd > 2)
			close(info->read_fd);

		_putchar(BUF_FLUSH);
	}
}

