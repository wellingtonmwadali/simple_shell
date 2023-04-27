#include "shell.h"

/**
 * **split_string_by_delimiter - Splits a string into words using a delimiter
 * @str: The input string
 * @delim: The delimiter string
 * Return: A pointer to an array of strings,
 * NULL on failure
 */
char **split_string_by_delimiter(char *str, char *delim)
{
	int w, x, y, z, num_words = 0;
	char **words;

	/* Check if input string is empty or NULL */
	if (str == NULL || str[0] == 0)
		return (NULL);

	/* If delimiter is not provided, use a space */
	if (!delim)
		delim = " ";

	/* Count the number of words in the string */
	for (w = 0; str[w] != '\0'; w++)
		if (!is_delim(str[i], delim) && (is_delim(str[w + 1], delim) || !str[w + 1]))
			num_words++;

	/* If there are no words, return NULL */
	if (num_words == 0)
		return (NULL);

	/* Allocate memory for the array of words */
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);

	/* Split the string into words and store them in the array*/
	for (w = 0, x = 0; x < num_words; x++)
	{
		while (is_delim(str[w], delim))
			w++;
		y = 0;
		while (!is_delim(str[w + y], delim) && str[w + y])
			y++;
		words[x] = malloc((y + 1) * sizeof(char));
		if (!words[x])
		{
			for (y = 0; y < x; y++)
				free(words[y]);
			free(words);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			words[x][z] = str[w++];
		words[x][z] = 0;
	}
	words[x] = NULL;
	return (words);
}

/**
 * **split_string_by_char - Splits a string into words using
 * a single character delimiter
 * @str: The input string
 * @delim: The delimiter character
 *
 * Return: A pointer to an array of strings,
 * NULL on failure
 */
char **split_string_by_char(char *str, char delim)
{
	int w, x, y, z, num_words = 0;
	char **words;

	/* Check if input string is empty or NULL */
	if (str == NULL || str[0] == 0)
		return (NULL);

	/* Count the number of words in the string */
	for (w = 0; str[w] != '\0'; w++)
		if ((str[w] != delim && str[w + 1] == delim) ||
		    (str[w] != delim && !str[w + 1]) || str[w + 1] == delim)
			num_words++;

	/* If there are no words, return NULL */
	if (num_words == 0)
		return (NULL);

	/* Allocate memory for the array of words */
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);

	/* Split the string into words and store them in the array*/
	for (w = 0, x = 0; x < num_words; x++)
	{
		while (str[w] == delim && str[w] != delim)
			w++;
		y = 0;
		while (str[w + y] != delim && str[w + y] && str[w + y] != delim)
			y++;
		words[x] = malloc((y + 1) * sizeof(char));
		if (!words[x])
		{
			for (y = 0; y < x; y++)
				free(words[y]);
			free(words);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			words[x][z] = str[w++];
		words[x][z] = 0;
	}
	words[x] = NULL;
	return (words);
}


