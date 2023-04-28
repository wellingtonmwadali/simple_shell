#include "shell.h"

/**
 * **strtow - functon that splits a string into words.
 * Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 *
 * Return: a pointer to an array of strings,
 * NULL on failure
 */

char **strtow(char *str, char *d)
{
	int x, y, a, b, numwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (is_delim(str[x], d))
			x++;
		a = 0;
		while (!is_delim(str[x + a], d) && str[x + a])
			a++;
		c[y] = malloc((a + 1) * sizeof(char));
		if (!c[y])
		{
			for (a = 0; a < y; a++)
				free(c[a]);
			free(c);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			c[y][b] = str[x++];
		c[y][b] = 0;
	}
	c[y] = NULL;
	return (c);
}

/**
 * **strtow2 - function that splits a string into words
 * @str: the input string
 * @d: the delimeter
 *
 * Return: a pointer to an array of strings,
 * NULL on failure
 */
char **strtow2(char *str, char d)
{
	int x, y, a, b, numwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (x = 0, y = 0; y < numwords; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		a = 0;
		while (str[x + a] != d && str[x + a] && str[x + a] != d)
			a++;
		c[y] = malloc((a + 1) * sizeof(char));
		if (!c[y])
		{
			for (a = 0; a < y; a++)
				free(c[a]);
			free(c);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			c[y][b] = str[x++];
		c[y][b] = 0;
	}
	c[y] = NULL;
	return (c);
}
