#include "shell.h"

/**
 * linked_list_length - determines the length of a linked list
 * @first_node: pointer to the first node
 *
 * Return: size of the list
 */
size_t linked_list_length(const list_t *first_node)
{
	size_t count = 0;

	while (first_node)
	{
		first_node = first_node->next;
		count++;
	}
	return (count);
}

/**
 * linked_list_to_string_array - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **linked_list_to_string_array(list_t *head)
{
	list_t *current_node = head;
	size_t list_length = linked_list_length(head), index;
	char **string_array;
	char *temp_string;

	if (!head || !list_length)
		return (NULL);
	string_array = malloc(sizeof(char *) * (list_length + 1));
	if (!string_array)
		return (NULL);
	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		temp_string = malloc(_strlen(current_node->str) + 1);
		if (!temp_string)
		{
			for (size_t j = 0; j < index; j++)
				free(string_array[j]);
			free(string_array);
			return (NULL);
		}

		temp_string = _strcpy(temp_string, current_node->str);
		string_array[index] = temp_string;
	}
	string_array[index] = NULL;
	return (string_array);
}

/**
 * display_linked_list - prints all elements of a list_t linked list
 * @first_node: pointer to the first node
 *
 * Return: size of the list
 */
size_t display_linked_list(const list_t *first_node)
{
	size_t count = 0;

	while (first_node)
	{
		_puts(convert_number(first_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(first_node->str ? first_node->str : "(nil)");
		_puts("\n");
		first_node = first_node->next;
		count++;
	}
	return (count);
}

/**
 * find_node_prefix - returns node whose str starts with given prefix
 * @current_node: pointer to the list head
 * @prefix: string to match
 * @next_char: the next character after the prefix to match
 *
 * Return: matching node or null
 */
list_t *find_node_prefix(list_t *current_node, char *prefix, char next_char)
{
	char *matched_prefix = NULL;

	while (current_node)
	{
		matched_prefix = starts_with(current_node->str, prefix);
		if (matched_prefix && ((next_char == -1) || (*matched_prefix == next_char)))
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * find_node_index - gets the index of a node
 * @list_head: pointer to the list head
 * @target_node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t find_node_index(list_t *list_head, list_t *target_node)
{
	size_t index = 0;

	while (list_head)
	{
		if (list_head == target_node)
			return (index);
		list_head = list_head->next;
		index++;
	}
	return (-1);
}

