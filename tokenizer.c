#include "shell.h"

/**
 * mod_strng - Splits string
 * @strng: Structure denoting possible arguments
 * @delim: Delimeter
 * Return: Pointer
 */
char **mod_strng(char *strng, char *delim)
{
	int a, b, q, z, linesay = 0;
	char **stst;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (a = 0; strng[a] != '\0'; a++)
		if (!prser(strng[i], delim) && (prser(strng[a + 1], delim) || !strng[a + 1]))
			linesay++;

	if (linesay == 0)
		return (NULL);
	stst = malloc((1 + linesay) * sizeof(char *));
	if (!stst)
		return (NULL);
	for (a = 0, b = 0; b < linesay; b++)
	{
		while (prser(strng[a], delim))
			a++;
		q = 0;
		while (!prser(strng[a + q], delim) && strng[a + q])
			q++;
		stst[b] = malloc((q + 1) * sizeof(char));
		if (!stst[b])
		{
			for (q = 0; q < b; q++)
				free(stst[q]);
			free(stst);
			return (NULL);
		}
		for (z = 0; z < q; z++)
			stst[b][z] = strng[a++];
		stst[b][z] = 0;
	}
	stst[b] = NULL;
	return (stst);
}

/**
 * checkstrn - Splits string
 * @strng: Structure denoting multiple arguments
 * @delim: Delimeter
 * Return: Pointer
 */
char **checkstrn(char *strng, char delim)
{
	int a, b, q, z, linesay = 0;
	char **stst;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (a = 0; strng[a] != '\0'; a++)
		if ((strng[a] != delim && strng[a + 1] == delim) ||
		    (strng[a] != delim && !strng[a + 1]) || strng[a + 1] == delim)
			linesay++;
	if (linesay == 0)
		return (NULL);
	stst = malloc((1 + linesay) * sizeof(char *));
	if (!stst)
		return (NULL);
	for (a = 0, b = 0; b < linesay; b++)
	{
		while (strng[a] == delim && strng[a] != delim)
			i++;
		q = 0;
		while (strng[a + q] != delim && strng[a + q] && strng[a + q] != delim)
			q++;
		stst[b] = malloc((q + 1) * sizeof(char));
		if (!stst[b])
		{
			for (q = 0; q < b; q++)
				free(stst[q]);
			free(stst);
			return (NULL);
		}
		for (z = 0; z < q; z++)
			stst[b][z] = strng[a++];
		stst[b][z] = 0;
	}
	stst[b] = NULL;
	return (stst);
}
