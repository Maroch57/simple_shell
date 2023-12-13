#include "shell.h"

/**
 * aqrenv - Returns the environment array
 * @feed: The structure denoting possible arguments
 * Return: 0
 */
char **aqrenv(pseuarg_ch *feed)
{
	if (!feed->environ || feed->new_env)
	{
		feed->environ = strng_lst(feed->exvar);
		feed->new_env = 0;
	}

	return (feed->environ);
}

/**
 * envunp - Gets rid of the environment variable
 * @feed: The structure denoting possible arguments
 * @var: The environment variable
 * Return: 1
 */
int envunp(pseuarg_ch *feed, char *var)
{
	lst_m *node = feed->exvar;
	size_t a = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = at_strt(node->strng, var);
		if (p && *p == '=')
		{
			feed->new_env = indxnode_del(&(feed->exvar), a);
			a = 0;
			node = feed->exvar;
			continue;
		}
		node = node->next;
		a++;
	}
	return (feed->new_env);
}

/**
 * ptenv - Sets and enhances environment variables
 * @feed: The structure denoting possible arguments
 * @var: The environment variable
 * @value: The string environment variable
 * Return: 0
 */
int ptenv(pseuarg_ch *feed, char *var, char *value)
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
	node = feed->exvar;
	while (node)
	{
		p = at_strt(node->strng, var);
		if (p && *p == '=')
		{
			free(node->strng);
			node->strng = buff;
			feed->new_env = 1;
			return (0);
		}
		node = node->next;
	}
	endnode_add(&(feed->exvar), buff, 0);
	free(buff);
	feed->new_env = 1;
	return (0);
}
