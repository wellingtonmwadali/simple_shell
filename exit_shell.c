
#include "shell.h"

/**
 * string_copy - function that copies a given string
 * @destination: the destination string to be copied to
 * @source: source string
 * @num_chars: amount of characters to be copied
 *
 * Return: the copied string
 */
char *string_copy(char *destination, char *source, int num_chars)
{
	int x, y;
	char *result = destination;

	x = 0;
	while (source[x] != '\0' && x < num_chars - 1)
	{
		destination[x] = source[x];
		x++;
	}
	if (x < num_chars)
	{
		y = x;
		while (y < num_chars)
		{
			destination[y] = '\0';
			y++;
		}
	}
	return (result);
}

/**
 * string_concate - function that concatenates two strings
 * @dest: the first string to concatenate
 * @src: the second string to concatenate
 * @num_bytes: the amount of bytes to be used at max
 *
 * Return: the concatenated string
 */
char *string_concate(char *dest, char *src, int num_bytes)
{
	int x, y;
	char *result = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < num_bytes)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < num_bytes)
		dest[y] = '\0';
	return (result);
}

/**
 * find_char - function that locates a character in a string
 * @str: the string to parse
 * @char_to_find: the character to look for
 *
 * Return: a pointer to the memory area str
 */
char *find_char(char *str, char char_to_find)
{
	do {
		if (*str == char_to_find)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

