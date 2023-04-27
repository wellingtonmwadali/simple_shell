#include "shell.h"

/**
 * free_buffer - function that frees a pointer and sets it to NULL
 * @ptr: pointer to free
 *
 * Return: 1 if successful, otherwise 0.
 */
int free_buffer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

