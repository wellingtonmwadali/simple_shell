#include "shell.h"

/**
 * display_history - shows the history list with line numbers, starting at 0
 * @info: Structure holding potential arguments. Maintains
 * a constant function prototype.
 *
 *  Return: Always 0
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - removes an alias
 * @info: parameter struct
 * @str: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
	char *alias_end, c;
	int result;

	alias_end = _strchr(str, '=');
	if (!alias_end)
		return (1);
	c = *alias_end;
	*alias_end = 0;
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*alias_end = c;
	return (result);
}

/**
 * create_alias - creates an alias from a string
 * @info: the parameter struct
 * @str: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int create_alias(info_t *info, char *str)
{
	char *alias_end;

	alias_end = _strchr(str, '=');
	if (!alias_end)
		return (1);
	if (!*++alias_end)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * show_alias - funtion that displays an alias string
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int show_alias(list_t *node)
{
	char *alias_end = NULL, *alias_start = NULL;

	if (node)
	{
		alias_end = _strchr(node->str, '=');
		for (alias_start = node->str; alias_start <= alias_end; alias_start++)
			_putchar(*alias_start);
		_putchar('\'');
		_puts(alias_end + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - function that emulates the alias builtin (man alias)
 * @info: Structure holding potential arguments. Maintains
 * a constant function prototype.
 *
 *  Return: Always 0
 */
int manage_alias(info_t *info)
{
	int t = 0;
	char *alias_end = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			show_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (t = 1; info->argv[t]; t++)
	{
		alias_end = _strchr(info->argv[t], '=');
		if (alias_end)
			create_alias(info, info->argv[t]);
		else
			show_alias(node_starts_with(info->alias, info->argv[t], '='));
	}

	return (0);
}

