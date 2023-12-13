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
 * @evible: The environment variable
 * Return: 1
 */
int envunp(pseuarg_ch *feed, char *evible)
{
	lst_m *node = feed->exvar;
	size_t a = 0;
	char *q;

	if (!node || !evible)
		return (0);

	while (node)
	{
		q = at_strt(node->strng, evible);
		if (q && *q == '=')
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
 * @evible: The environment variable
 * @strev: The string environment variable
 * Return: 0
 */
int ptenv(pseuarg_ch *feed, char *evible, char *strev)
{
	char *buff = NULL;
	lst_m *node;
	char *q;

	if (!evible || !strev)
		return (0);

	buff = malloc(lngth_str(evible) + lngth_str(strev) + 2);
	if (!buff)
		return (1);
	strngcop(buff, evible);
	strn_cat(buff, "=");
	strn_cat(buff, strev);
	node = feed->exvar;
	while (node)
	{
		q = at_strt(node->strng, evible);
		if (q && *q == '=')
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
