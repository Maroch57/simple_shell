#include "shell.h"

/**
 * hist_rep - This command displays history-related details
 * @feed: The structure that denotes possible arguments
 * Return: Always 0
 */
int hist_rep(pseuarg_ch *feed)
{
	prnt_lst(feed->hst);
	return (0);
}

/**
 * rmalias - This command assigns an alias to a string
 * @feed: The structure that denotes possible arguments
 * @strng: The alias denoting the string
 * Return: 0 if success, 1 if error
 */
int rmalias(pseuarg_ch *feed, char *strng)
{
	char *q, d;
	int rtrn;

	q = str_imp(strng, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	rtrn = indxnode_del(&(feed->fake), indx_gt(feed->fake, strt_strng(feed->fake, strng, -1)));
	*q = d;
	return (rtrn);
}

/**
 * putalias - Assigns an alias to a string
 * @feed: The structure that denotes possible arguments
 * @strng: Alias denoting the string
 * Return: 0 if success, 1 if error
 */
int putalias(pseuarg_ch *feed, char *strng)
{
	char *q;

	q = str_imp(strng, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (rmalias(feed, strng));

	rmalias(feed, strng);
	return (endnode_add(&(feed->fake), strng, 0) == NULL);
}

/**
 * prntalias - The command to print an alias string
 * @node: The node denoting the alias
 * Return: 0 if success, 1 if error
 */
int prntalias(lst_m *node)
{
	char *q = NULL, *x = NULL;

	if (node)
	{
		q = str_imp(node->strng, '=');
		for (x = node->strng; x <= q; x++)
			_putchar(*x);
		_putchar('\'');
		strngin(q + 1);
		strngin("'\n");
		return (0);
	}
	return (1);
}

/**
 * alum_hist - Replicates the builtin alias
 * @feed: The structure denoting possible arguments
 * Return: 0
 */
int alum_hist(pseuarg_ch *feed)
{
	int n = 0;
	char *q = NULL;
	lst_m *node = NULL;

	if (feed->argc == 1)
	{
		node = feed->fake;
		while (node)
		{
			prntalias(node);
			node = node->next;
		}
		return (0);
	}
	for (n = 1; feed->argv[n]; n++)
	{
		q = str_imp(feed->argv[n], '=');
		if (q)
			putalias(feed, feed->argv[n]);
		else
			prntalias(strt_strng(feed->fake, feed->argv[n], '='));
	}

	return (0);
}