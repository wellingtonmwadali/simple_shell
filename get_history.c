#include "shell.h"

/**
 * get_history_file - function that returns the path to the history file
 * @info: the parameter struct
 *
 * Return: allocated string containing path to history file,
 * or NULL on failure
 */
char *get_history_file(info_t *info)
{
	char *buffer, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);

	buffer = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;

	_strcpy(buffer, home_dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);

	free(home_dir);
	return (buffer);
}

/**
 * build_history_list - function that adds an entry to the history linked list
 * @info: the parameter struct
 * @buffer: the buffer
 * @linecount: the history line count
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buffer, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - function that renumbers the history
 * linked list after changes
 * @info: the parameter struct
 *
 * Return: the new history count
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int t = 0;

	while (node)
	{
		node->num = t++;
		node = node->next;
	}

	return (info->histcount = t);
}

/**
 * write_history - function that writes history to file
 * @info: the parameter struct containing arguments
 *
 * Return: 1 on success, -1 on failure
 */
int write_history(info_t *info)
{
	ssize_t filedesc;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filedesc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (filedesc == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, filedesc);
		_putfd('\n', filedesc);
	}
	_putfd(BUF_FLUSH, filedesc);

	close(filedesc);
	return (1);
}

/**
 * read_history - function that reads history from file
 * @info: the parameter struct containing arguments
 *
 * Return: the history count, 0 otherwise
 */
int read_history(info_t *info)
{
	int t, last = 0, linecount = 0;
	ssize_t filedesc, readlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	filedesc = open(filename, O_RDONLY);
	free(filename);

	if (filedesc == -1)
		return (0);

	if (!fstat(filedesc, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return (0);

	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);

	readlen = read(filedesc, buffer, fsize);
	buffer[fsize] = 0;

	if (readlen <= 0)
		return (free(buffer), 0);

	close(filedesc);

	for (t = 0; t < fsize; t++)
		if (buffer[t] == '\n')
		{
			buffer[t] = 0;
			build_history_list(info, buffer + last, linecount++);
			last = t + 1;
		}
	if (last != t)
		build_history_list(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

