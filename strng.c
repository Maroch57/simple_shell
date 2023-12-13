#include "shell.h"

/**
 * lngth_str - Determines string length
 * @r: String
 * Return: String length
 */
int lngth_str(char *r)
{
	int a = 0;

	if (!r)
		return (0);

	while (*r++)
		a++;
	return (a);
}

/**
 * strn_cmp - Compares strings
 * @r1: String 1
 * @r2: String 2
 * Return: String comparison
 */
int strn_cmp(char *r1, char *r2)
{
	while (*r1 && *r2)
	{
		if (*r1 != *r2)
			return (*r1 - *r2);
		r1++;
		r2++;
	}
	if (*r1 == *r2)
		return (0);
	else
		return (*r1 < *r2 ? -1 : 1);
}

/**
 * at_strt - Checks given requirement
 * @getit: The string to locate
 * @forme: The string to be located
 * Return: String
 */
char *at_strt(const char *getit, const char *forme)
{
	while (*forme)
		if (*forme++ != *getit++)
			return (NULL);
	return ((char *)getit);
}

/**
 * strn_cat - String concatenator
 * @strngdest: The destination buff
 * @strngsrce: The source buff
 * Return: Destination pointer
 */
char *strn_cat(char *strngdest, char *strngsrce)
{
	char *rtrn = strngdest;

	while (*strngdest)
		strngdest++;
	while (*strngsrce)
		*strngdest++ = *strngsrce++;
	*strngdest = *strngsrce;
	return (rtrn);
}
