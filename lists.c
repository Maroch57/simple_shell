#include "shell.h"

/**
 * populate_node - Adds node to list
 * @h: Head node
 * @strng: String
 * @nmber: Index
 * Return: List size
 */
lst_m *populate_node(lst_m **h, const char *strng, int nmber)
{
	lst_m *addh;

	if (!h)
		return (NULL);
	addh = malloc(sizeof(lst_m));
	if (!addh)
		return (NULL);
	mmry_arn((void *)addh, 0, sizeof(lst_m));
	addh->nmber = nmber;
	if (strng)
	{
		addh->strng = strngclone(strng);
		if (!addh->strng)
		{
			free(addh);
			return (NULL);
		}
	}
	addh->next = *h;
	*h = addh;
	return (addh);
}

/**
 * endnode_add - Adds node to the end of list
 * @h: Head node
 * @strng: Strng
 * @nmber: Index
 * Return: List size
 */
lst_m *endnode_add(lst_m **h, const char *strng, int nmber)
{
	lst_m *node, *addn;

	if (!h)
		return (NULL);

	node = *h;
	addn = malloc(sizeof(lst_m));
	if (!addn)
		return (NULL);
	mmry_arn((void *)addn, 0, sizeof(lst_m));
	addn->nmber = nmber;
	if (strng)
	{
		addn->strng = strngclone(strng);
		if (!addn->strng)
		{
			free(addn);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = addn;
	}
	else
		*h = addn;
	return (addn);
}

/**
 * lststr_prnt - Prints string element
 * @hd: Head node pointer
 * Return: List size
 */
size_t lststr_prnt(const lst_m *hd)
{
	size_t a = 0;

	while (hd)
	{
		strngin(hd->strng ? hd->strng : "(nil)");
		strngin("\n");
		hd = hd->next;
		a++;
	}
	return (a);
}

/**
 * indxnode_del - Deletes node at index
 * @h: Head node
 * @ind: The index
 * Return: 1
 */
int indxnode_del(lst_m **h, unsigned int ind)
{
	unsigned int a = 0;
	lst_m *node, *tdtd;

	if (!h || !*h)
		return (0);

	if (!ind)
	{
		node = *h;
		*h = (*h)->next;
		free(node->strng);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (a == ind)
		{
			tdtd->next = node->next;
			free(node->strng);
			free(node);
			return (1);
		}
		a++;
		tdtd = node;
		node = node->next;
	}
	return (0);
}

/**
 * freelst - Liberator of all nodes
 * @pthd: Head node
 * Return: void
 */
void freelst(lst_m **pthd)
{
	lst_m *node, *nexn, *h;

	if (!pthd || !*pthd)
		return;
	h = *pthd;
	node = h;
	while (node)
	{
		nexn = node->next;
		free(node->strng);
		free(node);
		node = nexn;
	}
	*pthd = NULL;
}
