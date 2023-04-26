#include "shell.h"

/**
 * exitf - exit builtin function
 * @av: pointer to array
 *
 * Return: void
 */
void exitf(char **av)
{
	int n;

	if (av[1])
	{
		n = _atoi(av[1]);
		if (n == 0)
		{
			print_err(av, ": Illegal number: ");
			_errputs(av[1]);
			_errputs("\n");
			freeav(av);
			return;
		}
		freeav(av);
		freeenv();
		exit(n);
	}
}
/**
 * cdir - change directory builtin function
 * @av: pointer to array
 *
 * Return: void
 */
void cdir(char **av)
{
	int i = 1;
	char cwd[1024];

	if (!(av[1]))
	{
		i = chdir(_getenv("HOME"));
	}
	else if (_strcmp(av[1], "-"))
	{
		if (_getenv("OLDPWD") != NULL)
		{	i = chdir(_getenv("OLDPWD"));
			_puts(_getenv("OLDPWD"));
			_puts("\n"); }
		else
		{ _puts(_getenv("PWD"));
			_puts("\n"); }

	}
	else
		i = chdir(av[1]);
	if (i == -1)
	{
		print_err(av, ": No such file or directory\n");
	}
	else
	{
		_setenv("OLDPWD", _getenv("PWD"), 1);
		_setenv("PWD", getcwd(cwd, 1024), 1);
	}
	if (av && *av)
		freeav(av);
}
/**
 * menv - print enviorn
 * @av: double pointer
 *
 * Return: void
 */
void menv(char **av)
{
	int i;

	for (i = 0; environ[i]; i++)
		puts(environ[i]);
	if (av && *av)
		freeav(av);
}
/**
 * msenv - set environment builtin
 * @av: array
 *
 * Return: void
 */

void msenv(char **av)
{
	if (!(av) || !av[1] || !av[2] || av[3])
		print_err(av, ": Wrong number of argument\n");
	else if (_setenv(av[1], av[2], 1) == 0)
		print_err(av, ": failed to set envirioment\n");
	if (av && *av)
		freeav(av);
}

/**
 * uenv - unset environment builtin
 * @av: array
 *
 * Return: void
 */
void uenv(char **av)
{
	if (!av[1] || av[2])
		print_err(av, ": Wrong number of argument\n");
	else if (_unsetenv(av[1]) == 0)
		print_err(av, ": failed to set enviroment\n");
	if (av && *av)
		freeav(av);
}
