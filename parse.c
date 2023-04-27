#include "shell.h"

/**
 * duplicate_chars - creates a copy of specific characters
 * @path_string: the PATH string
 * @begin: starting index
 * @end: stopping index
 *
 * Return: pointer to the new buffer
 */
char *duplicate_chars(char *path_string, int begin, int end)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = begin; i < end; i++)
		if (path_string[i] != ':')
			buffer[j++] = path_string[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * executable_cmd - checks if a file is an executable command
 * @info_struct: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int executable_cmd(info_t *info_struct, char *file_path)
{
	struct stat st;

	(void)info_struct;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
	return (1);
	}
	return (0);
}

/**
 * locate_path - locates the cmd in the PATH string
 * @info_struct: the info struct
 * @path_string: the PATH string
 * @command: the cmd to locate
 *
 * Return: full path of cmd if found or NULL
 */
char *locate_path(info_t *info_struct, char *path_string, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (executable_cmd(info_struct, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = duplicate_chars(path_string, current_position, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (executable_cmd(info_struct, path))
				return (path);
			if (!path_string[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}

