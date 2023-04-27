#include "shell.h"

/**
 * input_buf -it buffers the chained commands
 * @info: parameter struct with arg
 * @buf: address of buffer with arg
 * @len: address of length  variable
 *
 * Return: bytes thaat is to be read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t l = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in buffer, fill */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		l = getline(buf, &len_p, stdin);
#else
		l = _getline(info, buf, &len_p);
#endif
		if (l > 0)
		{
			if ((*buf)[l - 1] == '\n')
			{
				(*buf)[l - 1] = '\0'; /* remove trailing line */
				l--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is it a command chain? */
			{
				*len = l;
				info->cmd_buf = buf;
			}
		}
	}
	return (l);
}

/**
 * get_input - gets a line - the newline
 * @info: parameter struct with potential arguments
 *
 * Return: byte
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t x, y, len;
	ssize_t z = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	z = input_buf(info, &buf, &len);
	if (z == -1) /* EOF */
		return (-1);
	if (len)	/*  commands left in chain buffer */
	{
		y = x; /* init new iterator to current buf position */
		p = buf + x; /* get pointer for return */

		check_chain(info, buf, &y, x, len);
		while (y < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= len) /* reached end of buffer? */
		{
			x = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (z); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer where data is stored temporarily
 * @info: parameter struct with potential arguments
 * @buf: buffer
 * @t: size
 *
 * Return: y
 */
ssize_t read_buf(info_t *info, char *buf, size_t *t)
{
	ssize_t y = 0;

	if (*t)
		return (0);
	y = read(info->readfd, buf, READ_BUF_SIZE);
	if (y >= 0)
		*t = y;
	return (y);
}

/**
 * _getline - gets the next line of input from standard input (STDIN)
 * @info: parameter struct, containing potential arguments
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: y
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t n;
	ssize_t r = 0, y = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		y = *length;
	if (t == len)
		t = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + t, '\n');
	n = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, y, y ? y + n : n + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (y)
		_strncat(new_p, buf + t, n - t);
	else
		_strncpy(new_p, buf + t, n - t + 1);

	y += n - t;
	t = n;
	p = new_p;

	if (length)
		*length = y;
	*ptr = p;
	return (y);
}

/**
 * sigintHandler - blocks ctrl-C copy command
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
