#include "shell.h"

/**
 * actv_int - if shell is interactive returns true as outpt.
 * @info: address of the struct.
 *
 * Return: 1 if in interactive mode else 0.
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
 *bst_int - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic else, 0
 */

int bst_int(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *atoi_t - converts a str to int.
 *@s: the string under conversion.
 *Return: 0 if unsuccessful.
 */

int atoi_t(char *s)
{
	int i, sign = 1, flag = 0, outpt;
	unsigned int rsult = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			rsult *= 10;
			rsult += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		outpt = -rsult;
	else
		outpt = rsult;

	return (outpt);
}
