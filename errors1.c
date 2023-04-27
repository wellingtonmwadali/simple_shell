#include "shell.h"

/**
 * print_to_stderr - function that outputs a given string to stderr
 * @str: the string to be printed
 *
 * Return: None
 */
void print_to_stderr(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		write_to_stderr(str[index]);
		index++;
	}
}

/**
 * write_to_stderr - function that writes the character c to stderr
 * @c: character to print
 *
 * Return: 1 on success,
 * -1 on error, and sets errno appropriately.
 */
int write_to_stderr(char c)
{
	static int counter;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || counter >= WRITE_BUF_SIZE)
	{
		write(2, buffer, counter);
		counter = 0;
	}
	if (c != BUF_FLUSH)
		buffer[counter++] = c;
	return (1);
}

/**
 * write_to_fd - writes the character c to the specified file descriptor
 * @c: character to print
 * @fd: file descriptor to write to
 *
 * Return: 1 on success,
 * 1 on error, and sets errno appropriately.
 */
int write_to_fd(char c, int fd)
{
	static int counter;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || counter >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, counter);
		counter = 0;
	}
	if (c != BUF_FLUSH)
		buffer[counter++] = c;
	return (1);
}

/**
 * print_to_fd - outputs a given string to the specified file descriptor
 * @str: string to be printed
 * @fd: file descriptor to write to
 *
 * Return: the number of characters printed
 */
int print_to_fd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		char_count += write_to_fd(*str++, fd);
	}
	return (char_count);
}

