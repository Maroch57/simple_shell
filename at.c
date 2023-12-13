#include "shell.h"

/**
 * actv_int - if shell is interactive returns true as outpt.
 * @info: address of the struct.
 *
 * Return: 1 if successful else 0.
 */
int actv_int(pseuarg_ch *info)
{
	return (isatty(STDIN_FILENO) && info->telldes <= 2);
}

/**
 * prser - deliminates a string.
 * @c: the char in examination.
 * @delim: the delimeter string
 * Return: 1 if true else, 0.
 */
int prser(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *bst_int - Checks character
 *@c: Inputed character
 *Return: 1 else, 0
 */

int bst_int(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *atoi_t - Generates integer from string
 *@s: Converted string
 *Return: 0 if unsuccessful.
 */

int atoi_t(char *s)
{
	int a, sign = 1, warn = 0, outpt;
	unsigned int rsult = 0;

	for (a = 0;  s[a] != '\0' &&warn != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			warn = 1;
			rsult *= 10;
			rsult += (s[a] - '0');
		}
		else if (warn == 1)
			warn = 2;
	}

	if (sign == -1)
		outpt = -rsult;
	else
		outpt = rsult;

	return (outpt);
}
