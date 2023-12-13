#include "shell.h"

/**
 * exst_err - Generates integer from string
 * @st: String under transformation.
 * Return: 0 if successful, else -1
 */
int exst_err(char *st)
{
	int u = 0;
	unsigned long int give = 0;

	if (*st == '+')
		st++;
	for (u = 0;  st[u] != '\0'; u++)
	{
		if (st[u] >= '0' && st[u] <= '9')
		{
			give *= 10;
			give += (st[u] - '0');
			if (give > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (give);
}

/**
 * errorprnt - Returns an error message as output
 * @feed: String denoting multiple arguments
 * @errstrng: The string denoting the error
 * Return: 0 if successful, else -1
 */
void errorprnt(pseuarg_ch *feed, char *errstrng)
{
	putide(feed->progname);
	putide(": ");
	disprnt(feed->cnterr, STDERR_FILENO);
	putide(": ");
	putide(feed->argv[0]);
	putide(": ");
	putide(errstrng);
}

/**
 * disprnt - Prints an int no. to base 10.
 * @setit: Input in subject.
 * @fd: The respective file descriptor to be written to.
 * Return: The total no. of printed characters.
 */
int disprnt(int setit, int fd)
{
	int (*__putchar)(char) = _putchar;
	int u, ccount = 0;
	unsigned int bs_arr, currnt;

	if (fd == STDERR_FILENO)
		__putchar = charins;
	if (setit < 0)
	{
		bs_arr = -setit;
		__putchar('-');
		ccount++;
	}
	else
		bs_arr = setit;
	currnt = bs_arr;
	for (u = 1000000000; u > 1; u /= 10)
	{
		if (bs_arr / u)
		{
			__putchar('0' + currnt / u);
			ccount++;
		}
		currnt %= u;
	}
	__putchar('0' + currnt);
	ccount++;

	return (ccount);
}

/**
 * conv_nmber - Function that converts.
 * @numb: The number in subject.
 * @base_s: The base in subject.
 * @argflags: The argument flags in subject.
 * Return: A string of chars.
 */
char *conv_nmber(long int numb, int base_s, int argflags)
{
	static char *arr;
	static char bffer[50];
	char indic = 0;
	char *pter;
	unsigned long m = numb;

	if (!(argflags & CONVERT_UNINT) && numb < 0)
	{
		m = -numb;
		indic = '-';

	}
	arr = argflags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	pter = &bffer[49];
	*pter = '\0';

	do	{
		*--pter = arr[m % base_s];
		m /= base_s;
	} while (m != 0);

	if (indic)
		*--pter = indic;
	return (pter);
}

/**
 * rm_comm - Replaces first instance of '#' with null terminator..
 * @buff: the address of string under modification.
 * Return: 0
 */
void rm_comm(char *buff)
{
	int r;

	for (r = 0; buff[r] != '\0'; r++)
		if (buff[r] == '#' && (!r || buff[r - 1] == ' '))
		{
			buff[r] = '\0';
			break;
		}
}
