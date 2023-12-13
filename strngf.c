#include "shell.h"

/**
 * strngcop - Function used to copy a string.
 * @destn: Destination in subject.
 * @srce: Source in subject.
 * Return: A ptr to the destination.
 */
char *strngcop(char *destn, char *srce)
{
	int h = 0;

	if (destn == srce || srce == 0)
		return (destn);
	while (srce[h])
	{
		destn[h] = srce[h];
		h++;
	}
	destn[h] = 0;
	return (destn);
}

/**
 * strngclone - Funtion that duplicates a strng.
 * @strr: Strng under duplication.
 * Return: A ptr to the resulting strng.
 */
char *strngclone(const char *strr)
{
	int lngth = 0;
	char *retn;

	if (strr == NULL)
		return (NULL);
	while (*strr++)
		lngth++;
	retn = malloc(sizeof(char) * (lngth + 1));
	if (!retn)
		return (NULL);
	for (lngth++; lngth--;)
		retn[lngth] = *--strr;
	return (retn);
}

/**
 *strngin - Ensures an input string is printed.
 *@sstr: Printed strng.
 * Return: void.
 */
void strngin(char *sstr)
{
	int n = 0;

	if (!sstr)
		return;
	while (sstr[n] != '\0')
	{
		_putchar(sstr[n]);
		n++;
	}
}

/**
 * _putchar - Function to write a char to standard output console.
 * @charinp: The char to be printed.
 * Return: If successful 1 else, 0.
 */
int _putchar(char charinp)
{
	static int k;
	static char buff[WRITE_BUFFER_SIZE];

	if (k == BUFFER_FLUSH || k >= WRITE_BUFFER_SIZE)
	{
		write(1, buff, k);
		k = 0;
	}
	if (charinp != BUFFER_FLUSH)
		buff[k++] = charinp;
	return (1);
}
