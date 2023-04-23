#include "shell.h"

/**
 * freeav - free av array
 * @av: pointer to array
 *
 * Return: void
 */
void freeav(char **av)
{
	int i;

	if (av)
	{
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
	}
}
