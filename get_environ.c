#include "shell.h"

/**
 * get_environment - funct that returns a copy of the environment string array
 * @info: Structure that contains potential arguments.
 *
 * Return: The copy of the environment string array.
 */
char **get_environment(info_t *info)
{
	if (!info->environment || info->env_changed)
	{
		info->environment = list_to_strings(info->env_list);
		info->env_changed = 0;
	}

	return (info->environment);
}

/**
 * unset_environment_var - function that removes an environment variable.
 * @info: Structure that contains potential arguments.
 * @variable: The environment variable to remove.
 *
 * Return: 1 if the variable was removed, 0 otherwise.
 */
int unset_environment_var(info_t *info, char *variable)
{
	list_t *node = info->env_list;
	size_t t = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env_list), t);
			t = 0;
			node = info->env_list;
			continue;
		}
		node = node->next;
		t++;
	}
	return (info->env_changed);
}

/**
 * set_environment_var - function that initializes a new environment variable,
 * or modifies an existing one.
 * @info: Structure that contains potential arguments.
 * @variable: The environment variable to set.
 * @value: The value of the environment variable.
 *
 * Return: Always 0.
 */
int set_environment_var(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env_list;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_list), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

