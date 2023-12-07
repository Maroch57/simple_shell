#include "shell.h"

/**
 * hist_rep - This command displays history-related details
 * @info: The structure that denotes possible arguments
 * Return: Always 0
 */
int hist_rep(pseuarg_ch *info)
{
	prnt_lst(info->hst);
	return (0);
}

/**
 * rmalias - This command assigns an alias to a string
 * @info: The parameter
 * @strng: The alias denoting the string
 * Return: 0 if success, 1 if error
 */
int rmalias(pseuarg_ch *info, char *strng)
{
	char *p, d;
	int rtrn;

	p = str_imp(strng, '=');
	if (!p)
		return (1);
	d = *p;
	*p = 0;
	rtrn = indxnode_del(&(info->fake), indx_gt(info->fake, strt_strng(info->fake, strng, -1)));
	*p = d;
	return (rtrn);
}

/**
 * putalias - Assigns an alias to a string
 * @info: The parameter
 * @strng: Alias denoting the string
 * Return: 0 if success, 1 if error
 */
int putalias(pseuarg_ch *info, char *strng)
{
	char *p;

	p = str_imp(strng, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (rmalias(info, strng));

	rmalias(info, strng);
	return (endnode_add(&(info->fake), strng, 0) == NULL);
}

/**
 * prntalias - The command to print an alias string 
 * @node: The node denoting the alias
 * Return: 0 if success, 1 if error
 */
int prntalias(lst_m *node)
{
	char *p = NULL, *x = NULL;

	if (node)
	{
		p = str_imp(node->strng, '=');
		for (x = node->strng; x <= p; x++)
			_putchar(*x);
		_putchar('\'');
		strngin(p + 1);
		strngin("'\n");
		return (0);
	}
	return (1);
}

/**
 * alum_hist - Replicates the builtin alias
 * @info: The structure denoting possible arguments
 *  Return: 0
 */
int alum_hist(pseuarg_ch *info)
{
	int n = 0;
	char *p = NULL;
	lst_m *node = NULL;

	if (info->argc == 1)
	{
		node = info->fake;
		while (node)
		{
			prntalias(node);
			node = node->next;
		}
		return (0);
	}
	for (n = 1; info->argv[n]; n++)
	{
		p = str_imp(info->argv[n], '=');
		if (p)
			putalias(info, info->argv[n]);
		else
			prntalias(strt_strng(info->fake, info->argv[n], '='));
	}

	return (0);
}
