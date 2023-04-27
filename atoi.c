#include "shell.h"

/**
 * check_alpha - function that checks for alphabetic character
 * @c: alphabetical character
 * Return: 1 if alphabetic  or 0 if otherwise
 */
int check_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *check_delimiter - Function that checks if character is a delimiter
 *@c: charactr the check
 *@delimiter: string
 *Return: 1 true or 0 false
 */
int check_delimiter(char c, char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter++ == c)
			return (1);
	}
	return (0);
}

/**
 *convert_to_integer - Function that converts a string to an integer
 *@string: string to be converted
 * Return: 0 if no string converted, otherwise number
 */
int convert_to_integer(char *string)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; string[i] != '\0' && flag != 2; i++)
	{
		if (string[i] == '-')
			sign *= -1;
		if (string[i] >= '0' && string[i] <= '9')
	{
		flag = 1;
		result *= 10;
		result += (string[i] - '0');
	}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}


/**
 *is_interactive - Function that returns true if shell is in interactive mode
 *@information: struct add
 *Return: 1 interactive, 0 not
 */
int is_interactive(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}
