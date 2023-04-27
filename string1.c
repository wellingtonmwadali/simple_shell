#include "shell.h"

/**
 * string_length - return the length of a string
 * @str: input string to be measured
 *
 * Return: integer for  length of the string
 */
int string_length(char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
		len++;
	return (len);
}

/**
 * string_compare -compere two strings.
 * @str1: first string
 * @str2: second string
 *
 * Return: (-) if str1 < str2,(+) if str1 > str2, 0 if str1 == str2
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * begins_with - checks if the given substring starts with the main string
 * @main_str: the main string to search
 * @sub_str: the substring to find
 *
 * Return: address of the next character of the main string or NULL
 */
char *begins_with(const char *main_str, const char *sub_str)
{
	while (*sub_str)
		if (*sub_str++ != *main_str++)
			return (NULL);
	return ((char *)main_str);
}

/**
 * strin_concate - concatenates two strings
 * @dest_str: the destination buffer
 * @src_str: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *strin_concate(char *dest_str, char *src_str)
{
	char *result = dest_str;

	while (*dest_str)
		dest_str++;
	while (*src_str)
		*dest_str++ = *src_str++;
	*dest_str = *src_str;
	return (result);
}

