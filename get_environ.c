#include "shell.h"

/**
 * get_environ - function that returns the string array copy of the environ
 * @info: Structure tht has potential arguments. maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - function that Remove  environment variables
 * @info: Structure that has  arguments.  maintain
 *        constant function prototype.
 *  Return: 1 for delete, 0 otherwise
 * @vari: the string env var property
 */
int _unsetenv(info_t *info, char *vari)
{
	list_t *node = info->env;
	size_t j = 0;
	char *q;

	if (!node || !vari)
		return (0);

	while (node)
	{
		q = starts_with(node->str, vari);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _setenv - function tht Initialize  new environ var,
 *             or modify  existing ones
 * @info: Structure that has arguments.  maintain
 *        constant function prototype.
 * @var:  string environent variable property
 * @value:  string environment variable value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
