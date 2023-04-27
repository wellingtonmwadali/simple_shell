#include "shell.h"

/**
 * display_env - shows the current environment
 * @info: Structure holding potential arguments. Maintains
 *          constant function prototype.
 * Return: Always 0
 */
int display_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * find_env_var - retrieves the value of an environment variable
 * @info: Structure holding potential arguments. Maintains
 * @var_name: environment variable name
 *
 * Return: the value
 */
char *find_env_var(info_t *info, const char *var_name)
{
	list_t *current_node = info->env;
	char *result;

	while (current_node)
	{
		result = starts_with(current_node->str, var_name);
		if (result && *result)
			return (result);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * create_or_modify_env - Set up a new environment variable,
 *                        or change an existing one
 * @info: Structure holding potential arguments. Maintains
 *        constant function prototype.
 *  Return: Always 0
 */
int create_or_modify_env(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * remove_env_var - Delete an environment variable
 * @info: Structure holding potential arguments. Maintains
 *        constant function prototype.
 *  Return: Always 0
 */
int remove_env_var(info_t *info)
{
	int idx;

	if (info->argc == 1)
	{
		_eputs("Not enough arguments.\n");
		return (1);
	}
	for (idx = 1; idx <= info->argc; idx++)
		_unsetenv(info, info->argv[idx]);

	return (0);
}

/**
 * fill_env_list - fills the environment linked list
 * @info: Structure holding potential arguments. Maintains
 *          constant function prototype.
 * Return: Always 0
 */
int fill_env_list(info_t *info)
{
	list_t *new_node = NULL;
	size_t idx;

	for (idx = 0; environ[idx]; idx++)
		add_node_end(&new_node, environ[idx], 0);
	info->env = new_node;
	return (0);
}

