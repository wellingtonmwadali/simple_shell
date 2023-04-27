#include "shell.h"

/**
 * _fill_mem - function that fills memory with a constant byte
 * @memory: the pointer to the memory area
 * @byte: the byte to fill *memory with
 * @size: the amount of bytes to be filled
 *
 * Return: a pointer to the memory area
 */
char *_fill_mem(char *memory, char byte, unsigned int size)
{
	unsigned int t;

	for (t = 0; t < size; t++)
		memory[t] = byte;
	return (memory);
}

/**
 * free_strings - function that frees a string of strings
 * @string_array: string of strings
 */
void free_strings(char **string_array)
{
	char **a = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(a);
}

/**
 * _reallocate - function that reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the new block of memory
 */
void *_reallocate(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *new_pointer;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(pointer), NULL);
	if (new_size == old_size)
		return (pointer);

	new_pointer = malloc(new_size);
	if (!new_pointer)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_pointer[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (new_pointer);
}

