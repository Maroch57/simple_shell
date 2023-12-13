#include "shell.h"

/**
 * mem_free - Liberates pointer and nullifies address.
 * @pttr: Liberated pointer address.
 * Return: 1 if successful, else 0.
 */
int mem_free(void **pttr)
{
	if (pttr && *pttr)
	{
		free(*pttr);
		*pttr = NULL;
		return (1);
	}
	return (0);
}
