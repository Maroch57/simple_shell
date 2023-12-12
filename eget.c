#include "shell.h"

/**
 * aqrenv - Returns the environment array
 * @info: The structure denoting possible arguments
 * Return: 0
 */
char **aqrenv(pseuarg_ch *info)
{
	if (!info->environ || info->new_env)
	{
		info->environ = strng_lst(info->exvar);
		info->new_env = 0;
	}

	return (info->environ);
}

/**
 * envunp - Gets rid of the environment variable
 * @info: The structure denoting possible arguments
 * @var: The environment variable
 * Return: 1
 */
int envunp(pseuarg_ch *info, char *var)
{
	lst_m *node = info->exvar;
	size_t a = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = at_strt(node->strng, var);
		if (p && *p == '=')
		{
			info->new_env = indxnode_del(&(info->exvar), a);
			a = 0;
			node = info->exvar;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->new_env);
}

/**
 * ptenv - Sets and enhances environment variables
 * @info: The structure denoting possible arguments
 * @var: The environment variable
 * @value: The string environment variable
 * Return: 0
 */
int ptenv(pseuarg_ch *info, char *var, char *value)
{
	char *buff = NULL;
	lst_m *node;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(lngth_str(var) + lngth_str(value) + 2);
	if (!buff)
		return (1);
	strngcop(buff, var);
	strn_cat(buff, "=");
	strn_cat(buff, value);
	node = info->exvar;
	while (node)
	{
		p = at_strt(node->strng, var);
		if (p && *p == '=')
		{
			free(node->strng);
			node->strng = buff;
			info->new_env = 1;
			return (0);
		}
		node = node->next;
	}
	endnode_add(&(info->exvar), buff, 0);
	free(buff);
	info->new_env = 1;
	return (0);
}
