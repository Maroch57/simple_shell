#include "shell.h"

/**
 * str_ch - responsible for testing if chars are delimeters.
 * @feed: the param struct in subject.
 * @buf: char buffer in subject.
 * @potr: the address current position in buffer.
 *
 * Return: 1 if successful,else 0.
 */
int str_ch(pseuarg_ch *feed, char *buf, size_t *potr)
{
	size_t k = *potr;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		feed->cdbuffertype = OR_CMND;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		feed->cdbuffertype = AND_CMND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		feed->cdbuffertype = CHAIN_CMND;
	}
	else
		return (0);
	*potr = k;
	return (1);
}

/**
 * look_ch - indluences chaining processes.
 * @feed: struct parameter in subject.
 * @buf: buffer character in subject.
 * @m: current position buffer address.
 * @n: the starting buffer position.
 * @lngth: current buffer lngth.
 *
 * Return: NULL.
 */
void look_ch(pseuarg_ch *feed, char *buf, size_t *m, size_t n, size_t lngth)
{
	size_t q = *m;

	if (feed->cdbuffertype == AND_CMND)
	{
		if (feed->tellstat)
		{
			buf[n] = 0;
			q = lngth;
		}
	}
	if (feed->cdbuffertype == OR_CMND)
	{
		if (!feed->tellstat)
		{
			buf[n] = 0;
			q = lngth;
		}
	}

	*m = q;
}

/**
 * rp_alias - makes replacements in the tokenized strings.
 * @feed: struct param in subject.
 *
 * Return: 1 if succesful; else 0.
 */
int rp_alias(pseuarg_ch *feed)
{
	int a;
	lst_m *node;
	char *r;

	for (a = 0; a < 10; a++)
	{
		node = strt_strng(feed->fake, feed->argv[0], '=');
		if (!node)
			return (0);
		free(feed->argv[0]);
		r = str_imp(node->strng, '=');
		if (!r)
			return (0);
		r = strngclone(r + 1);
		if (!r)
			return (0);
		feed->argv[0] = r;
	}
	return (1);
}

/**
 * rp_vstr - makes var changes in the tokenized string.
 * @feed: the struct param in subject.
 *
 * Return: 1 if successful, else 0.
 */
int rp_vstr(pseuarg_ch *feed)
{
	int v = 0;
	lst_m *node;

	for (v = 0; feed->argv[v]; v++)
	{
		if (feed->argv[v][0] != '$' || !feed->argv[v][1])
			continue;

		if (!strn_cmp(feed->argv[v], "$?"))
		{
			strn_chng(&(feed->argv[v]),
				strngclone(conv_nmber(feed->tellstat, 10, 0)));
			continue;
		}
		if (!strn_cmp(feed->argv[v], "$$"))
		{
			strn_chng(&(feed->argv[v]),
				strngclone(conv_nmber(getpid(), 10, 0)));
			continue;
		}
		node = strt_strng(feed->exvar, &feed->argv[v][1], '=');
		if (node)
		{
			strn_chng(&(feed->argv[v]),
				strngclone(str_imp(node->strng, '=') + 1));
			continue;
		}
		strn_chng(&feed->argv[v], strngclone(""));

	}
	return (0);
}

/**
 * strn_chng - responsible for replacing the string in subject.
 * @o_str: the address of initial string.
 * @n_str: the new string in subject.
 *
 * Return: 1 on success, else 0.
 */
int strn_chng(char **o_str, char *n_str)
{
	free(*o_str);
	*o_str = n_str;
	return (1);
}
