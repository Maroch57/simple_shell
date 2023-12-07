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
 * charins - Prints the character c to stderr
 * @c: The character to be printed //Ask if this c should be changed
 * Return: 1 if success, -1 if error
 */
int charins(char c)
{
	static int n;
	static char buff[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || n >= WRITE_BUFFER_SIZE)
	{
		write(2, buff, n);
		n = 0;
	}
	if (c != BUFFER_FLUSH)
		buff[n++] = c;
	return (1);
}

/**
 * fputer - Writes the character c to the file descriptor
 * @c: The character to be printed
 * @fd: The file descriptor in question
 * Return: 1 if success, -1 if error
 */
int fputer(char c, int fd)
{
	static int n;
	static char buff[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buff, n);
		n = 0;
	}
	if (c != BUFFER_FLUSH)
		buff[n++] = c;
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
	return (i);
}
