#include "shell.h"

/**
 **mmry_arn - Responsible for populating the memory.
 *@r: Ptr to memory.
 *@p: Reponsible byte for populating the memory.
 *@m: Bytes to be populated.
 *Return: Ptr to the memory.
 */
char *mmry_arn(char *r, char p, unsigned int m)
{
	unsigned int l;

	for (l = 0; l < m; l++)
		r[l] = p;
	return (r);
}

/**
 * dmfree - Responsible for freeing a string of strings.
 * @ss: The string of strings in subject.
 */
void dmfree(char **ss)
{
	char **g = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(g);
}

/**
 * mem_ralloc - Responsible for allocating memory block.
 * @pptr: Ptr to memory allocated block.
 * @init_size: Initial size of a block of memory.
 * @curr_size: Size of the new mem allocated block.
 * Return: Ptr to the memory block.
 */
void *mem_ralloc(void *pptr, unsigned int init_size, unsigned int curr_size)
{
	char *t;

	if (!pptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(pptr), NULL);
	if (curr_size == init_size)
		return (pptr);

	t = malloc(curr_size);
	if (!t)
		return (NULL);

	init_size = init_size < curr_size ? init_size : curr_size;
	while (init_size--)
		t[init_size] = ((char *)pptr)[init_size];
	free(pptr);
	return (t);
}
