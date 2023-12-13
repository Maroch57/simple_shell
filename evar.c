#include "shell.h"

/**
 * myown_env - ensures current environment is printed.
 * @feed: struct contains potential constant fn prototype.
 * Return: 0
 */
int myown_env(pseuarg_ch *feed)
{
	lststr_prnt(feed->exvar);
	return (0);
}

/**
 * pop_env - fn gets environment variable values.
 * @feed: struct of arguments in use.
 * @vname: variable name on env in subject.
 *
 * Return: value.
 */
char *pop_env(pseuarg_ch *feed, const char *vname)
{
	lst_m *node = feed->exvar;
	char *k;

	while (node)
	{
		k = at_strt(node->strng, vname);
		if (k && *k)
			return (k);
		node = node->next;
	}
	return (NULL);
}

/**
 * good_env - configs/modif new environment variables.
 * @feed: struct containing potential arg prototypes.
 * Return: 0
 */
int good_env(pseuarg_ch *feed)
{
	if (feed->argc != 3)
	{
		putide("Incorrect number of arguements\n");
		return (1);
	}
	if (ptenv(feed, feed->argv[1], feed->argv[2]))
		return (0);
	return (1);
}

/**
 * bad_env - eliminates/removes an env var.
 * @feed: struct containing potential arg prototype.
 *  Return: 0
 */
int bad_env(pseuarg_ch *feed)
{
	int d;

	if (feed->argc == 1)
	{
		putide("Too few arguements.\n");
		return (1);
	}
	for (d = 1; d <= feed->argc; d++)
		envunp(feed, feed->argv[d]);

	return (0);
}

/**
 * fill_env - adds to an environmnt lst.
 * @feed: struct contains potential arg prototypes.
 * Return: 0
 */
int fill_env(pseuarg_ch *feed)
{
	lst_m *node = NULL;
	size_t d;

	for (d = 0; environ[d]; d++)
		endnode_add(&node, environ[d], 0);
	feed->exvar = node;
	return (0);
}
