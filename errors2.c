#include "shell.h"

/**
 * str_to_int - function that converts a string to an integer
 * @s: string to be converted
 *
 * Return: 0 if no numbers in string, -1 on error,
 * converted number otherwise
 */
int str_to_int(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (index = 0;  s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_error - function that prints an error message
 * @info: the parameter containing poterntial arguments
 * & return info struct
 * @error_str: string containing specified error type
 *
 * Return: None
 */
void display_error(info_t *info, char *error_str)
{
	print_to_stderr(info->shell_name);
	print_to_stderr(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	print_to_stderr(": ");
	print_to_stderr(info->argv[0]);
	print_to_stderr(": ");
	print_to_stderr(error_str);
}

/**
 * print_decimal - function that prints a decimal (integer) number (base 10)
 * @input: the input to print
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*write_char)(char) = write_to_fd;
	int i, char_count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		write_char = write_to_stderr;
	if (input < 0)
	{
		abs_value = -input;
		write_char('-');
		char_count++;
	}
	else
		abs_value = input;
	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			write_char('0' + current / i);
			char_count++;
		}
		current %= i;
	}
	write_char('0' + current);
	char_count++;

	return (char_count);
}

/**
 * num_to_str - converter function, similar to itoa
 * @num: number
 * @base: base
 * @flags: the argument flags
 *
 * Return: the string converted
 */
char *num_to_str(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = digits[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * eliminate_comments - function that replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Nothing
 */
void eliminate_comments(char *buff)
{
	int t;

	for (t = 0; buff[t] != '\0'; t++)
		if (buff[t] == '#' && (!t || buff[t - 1] == ' '))
		{
			buff[t] = '\0';
			break;
		}
}

