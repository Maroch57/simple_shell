#include "shell.h"

/**
 *cppy_strng - This command copies a string
 *@strngdest: The string destination
 *@strngsrce: The string source
 *@n: Number of copied characters
 *Return: The string
 */
char cppy_strng(char *strngdest, char *strngsrce, int n)
{
	int a, b;
	char *st = strngdest;

	a = 0;
	while (strngsrce[a] != '\0' && a < n - 1)
	{
		strngdest[a] = strngsrce[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			strngdest[b] = '\0';
			b++;
		}
	}
	return (st);
}

/**
 *strngmod - Concatenates strings
 *@strngdest: String destination
 *@strngsrce: String source
 *@n: Amount of memory
 *Return: The string
 */
char *strngmod(char *strngdest, char *strngsrce, int n)
{
	int a, b;
	char *st = strngdest;

	a = 0;
	b = 0;
	while (strngdest[a] != '\0')
		a++;
	while (strngsrce[a] != '\0' && b < n)
	{
		strngdest[a] = strngsrce[b];
		a++;
		b++;
	}
	if (b < n)
		strngdest[a] = '\0';
	return (st);
}

/**
 *str_imp - Locates a character in the string
 *@st: The string
 *@c: The character
 *Return: The string
 */
char *str_imp(char *st, char c)
{
	do {
		if (*st == c)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
