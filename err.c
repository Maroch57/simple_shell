#include "shell.h"

/**
 * putide - Prints input string
 * @strng: Denotes string to be printed
 * Return: Void
*/
void putide(char *strng)
{
	int n = 0;

	if (!strng)
		return;
	while (strng[n] != '\0')
	{
		charins(strng[n]);
		n++;
	}
}

/**
 * charins - Prints the char c
 * @charinp: The character to be printed
 * Return: 1 if success, -1 if error
 */
int charins(char charinp)
{
	static int n;
	static char buff[WRITE_BUFFER_SIZE];

	if (charinp == BUFFER_FLUSH || n >= WRITE_BUFFER_SIZE)
	{
		write(2, buff, n);
		n = 0;
	}
	if (charinp != BUFFER_FLUSH)
		buff[n++] = charinp;
	return (1);
}

/**
 * fputer - Prints the char c to the file descriptor
 * @charinp: The character to be printed
 * @fd: The file descriptor
 * Return: 1 if success, -1 if error
 */
int fputer(char charinp, int fd)
{
	static int n;
	static char buff[WRITE_BUFFER_SIZE];

	if (charinp == BUFFER_FLUSH || n >= WRITE_BUFFER_SIZE)
	{
		write(fd, buff, n);
		n = 0;
	}
	if (charinp != BUFFER_FLUSH)
		buff[n++] = charinp;
	return (1);
}

/**
 * fndpt - Prints input string
 * @strng: Printed string
 * @fd: The file descriptor in question
 * Return: Character count
 */
int fndpt(char *strng, int fd)
{
	int n = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		n += fputer(*strng++, fd);
	}
	return (n);
}
