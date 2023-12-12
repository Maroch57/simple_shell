#include "shell.h"

/**
 *cppy_strng - This command copies the string
 *@strngdest: The string destination
 *@strngsrce: The string source
 *@nm: Number of copied characters
 *Return: The string
 */
char *cppy_strng(char *strngdest, char *strngsrce, int nm)
{
	int a, b;
	char *stst = strngdest;

	a = 0;
	while (strngsrce[a] != '\0' && a < nm - 1)
	{
		strngdest[a] = strngsrce[a];
		a++;
	}
	if (a < nm)
	{
		b = a;
		while (b < nm)
		{
			strngdest[b] = '\0';
			b++;
		}
	}
	return (stst);
}

/**
 *strngmod - Executes a link function on respective strings
 *@strngdest: String destination
 *@strngsrce: String source
 *@m: Amount of memory
 *Return: The string
 */
char *strngmod(char *strngdest, char *strngsrce, int m)
{
	int a, b;
	char *stst = strngdest;

	a = 0;
	b = 0;
	while (strngdest[a] != '\0')
		a++;
	while (strngsrce[a] != '\0' && b < m)
	{
		strngdest[a] = strngsrce[b];
		a++;
		b++;
	}
	if (b < m)
		strngdest[a] = '\0';
	return (stst);
}

/**
 *str_imp - Distinguishes string characters
 *@stst: The string
 *@c: The character
 *Return: The string
 */
char *str_imp(char *stst, char c)
{
	do {
		if (*stst == c)
			return (stst);
	} while (*stst++ != '\0');

	return (NULL);
}
