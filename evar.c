#include "shell.h"

/**
 * myown_env - Ensures current environment is printed.
 * @feed: Structure denoting possible arguments
 * Return: 0
 */
int myown_env(pseuarg_ch *feed)
{
	lststr_prnt(feed->exvar);
	return (0);
}

/**
 * pop_env - Obtains environment variable values.
 * @feed: Structure denoting possible arguments
 * @vname: Variable name of env in subject.
 * Return: Environment variable values
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
 * good_env - Configures/modifies new environment variables.
 * @feed: Structure denoting possible arguments
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
 * bad_env - Eliminates/removes env var.
 * @feed: Structure denoting possible arguments
 * Return: 0
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
 * fill_env - Adds to an environmnt lst.
 * @feed: Structure denoting possible arguments
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
