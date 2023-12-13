#include "shell.h"

/**
 * lngth_lst - Responsible for the length of a linked list.
 * @pr: Ptr to first node in a list
 * Return: Total size of the list.
 */
size_t lngth_lst(const lst_m *pr)
{
	size_t y = 0;

	while (pr)
	{
		pr = pr->next;
		y++;
	}
	return (y);
}

/**
 * strng_lst - This function returns an array of strings.
 * @phead: Ptr to first node in the linked list.
 * Return: String array.
 */
char **strng_lst(lst_m *phead)
{
	lst_m *node = phead;
	size_t y = lngth_lst(phead), z;
	char **sstrs;
	char *strng;

	if (!phead || !y)
		return (NULL);
	sstrs = malloc(sizeof(char *) * (y + 1));
	if (!sstrs)
		return (NULL);
	for (y = 0; node; node = node->next, y++)
	{
		strng = malloc(lngth_str(node->strng) + 1);
		if (!strng)
		{
			for (z = 0; z < y; z++)
				free(sstrs[z]);
			free(sstrs);
			return (NULL);
		}

		strng = strngcop(strng, node->strng);
		sstrs[y] = strng;
	}
	sstrs[y] = NULL;
	return (sstrs);
}


/**
 * prnt_lst - Prints elements.
 * @pr: Ptr to first element/node in the list.
 * Return: Total size of the list in subject.
 */
size_t prnt_lst(const lst_m *pr)
{
	size_t d = 0;

	while (pr)
	{
		strngin(conv_nmber(pr->nmber, 10, 0));
		_putchar(':');
		_putchar(' ');
		strngin(pr->strng ? pr->strng : "(nil)");
		strngin("\n");
		pr = pr->next;
		d++;
	}
	return (d);
}

/**
 * strt_stng - Returns node starting a string.
 * @nod: Ptr to head of list.
 * @upfront: String in subject under match.
 * @charinp: Next char after prefix under match.
 * Return: Void
 */
lst_m *strt_strng(lst_m *nod, char *upfront, char charinp)
{
	char *m = NULL;

	while (nod)
	{
		m = at_strt(nod->strng, upfront);
		if (m && ((charinp == -1) || (*m == charinp)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * indx_gt - Obtains node index.
 * @nog: Ptr to head of list.
 * @node: The ptr to the node in subject.
 * Return: node index else, -1
 */
ssize_t indx_gt(lst_m *nog, lst_m *node)
{
	size_t b = 0;

	while (nog)
	{
		if (nog == node)
			return (b);
		nog = nog->next;
		b++;
	}
	return (-1);
}
