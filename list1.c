#include "shell.h"

/**
 * insert_node_begin - Inserts a node at the beginning of the list
 * @head_ptr: address of the pointer to the head node
 * @input_str: string field of the node
 * @index: node index utilized by history
 *
 * Return: pointer to the new head node
 */
list_t *insert_node_begin(list_t **head_ptr, const char *input_str, int index)
{
	list_t *new_head;

	if (!head_ptr)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = index;
	if (input_str)
	{
		new_head->str = strdup(input_str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head_ptr;
	*head_ptr = new_head;
	return (new_head);
}

/**
 * insert_node_end - Inserts a node at the end of the list
 * @head_ptr: address of the pointer to the head node
 * @input_str: string field of the node
 * @index: node index utilized by history
 *
 * Return: pointer to the new node
 */
list_t *insert_node_end(list_t **head_ptr, const char *input_str, int index)
{
	list_t *new_node, *current_node;

	if (!head_ptr)
		return (NULL);

	current_node = *head_ptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;
	if (input_str)
	{
		new_node->str = strdup(input_str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next){
			current_node = current_node->next;
			current_node->next = new_node;
				}
	}
				else
				*head_ptr = new_node;
				return (new_node);
				}

/**
 * display_list_str - Displays only the string element of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
				size_t display_list_str(const list_t *head)
				{
				size_t count = 0;

				while (head)
				{
				puts(head->str ? head->str : "(nil)");
				puts("\n");
				head = head->next;
				count++;
				}
				return (count);
				}

/**
 * remove_node_at_index - Removes a node at the specified index
 * @head_ptr: address of the pointer to the first node
 * @index: index of the node to remove
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **head_ptr, unsigned int index)
{
	list_t *current_node, *previous_node;
	unsigned int i = 0;

	if (!head_ptr || !*head_ptr)
		return (0);
	if (!index)
	{
		current_node = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *head_ptr;
	while (current_node)
	{
		if (i == index)
		{
			previous_node->next = current_node->next;
				free(current_node->str);
				free(current_node);
				return (1);
		}
		i++;
		previous_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 * release_list - Releases all nodes of a list
 * @head_ptr: address of the pointer to the head node
 *
 * Return: void
 */
void release_list(list_t **head_ptr)
{
	list_t *current_node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	current_node = head;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*head_ptr = NULL;
}

