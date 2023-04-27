#include "shell.h"

/**
 * write_char - outputs a character to stdout
 * @ch: The character to output
 *
 * Return: 1 on success, -1 on error with errno set accordingly.
 */
int write_char(char ch)
{
	static int idx;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(1, buffer, idx);
		idx = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[idx++] = ch;
	return (1);
}

/**
 * print_str - outputs a given string
 * @input_str: the string to output
 *
 * Return: None
 */
void print_str(char *input_str)
{
	int idx = 0;

	if (!input_str)
		return;
	while (input_str[idx] != '\0')
	{
		write_char(input_str[idx]);
		idx++;
	}
}

/**
 * duplicate_str - creates a copy of a string
 * @input_str: the string to copy
 *
 * Return: pointer to the copied string
 */
char *duplicate_str(const char *input_str)
{
	int len = 0;
	char *result;

	if (input_str == NULL)
		return (NULL);
	while (*input_str++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--input_str;
	return (result);
}

/**
 * copy_str - copies one string to another
 * @destination: the target string
 * @source: the source string
 *
 * Return: pointer to the target string
 */
char *copy_str(char *destination, char *source)
{
	int idx = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[idx])
	{
		destination[idx] = source[idx];
		idx++;
	}
	destination[idx] = 0;
	return (destination);
}

