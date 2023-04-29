#include "shell.h"

/**
 * exitf - exit builtin function
 * @av: pointer to array
 * @s: struct with filename and status
 *
 * Return: void
 */
void exitf(char **av, st * s __attribute__((unused)))
{
	int n;

	if (av[1])
	{
		n = _atoi(av[1]);
		if (n <= 0)
		{
			print_err(av, ": Illegal number: ", s);
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
 * @s: struct with filename and status
 *
 * Return: void
 */
void cdir(char **av, st *s)
{
	int i = 1;
	char cwd[1024], *ermsg = NULL;

	if (av[1])
	{	ermsg = malloc(sizeof(char) * (_strlen(av[1]) + 17));
		if (ermsg != NULL)
		{	_strcpy(ermsg, ": can't cd to ");
			_strcat(ermsg, av[1]), _strcat(ermsg, "\n\0"); }
	}
	if (!(av[1]))
	{
		if (_getenv("HOME") != NULL)
			i = chdir(_getenv("HOME"));
		else
			i = chdir(_getenv("PWD"));
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
	{	print_err(av, (ermsg ? ermsg : ": can't cd to\n"), s); }
	else
	{
		_setenv("OLDPWD", _getenv("PWD"), 1);
		_setenv("PWD", getcwd(cwd, 1024), 1);
	}
	if (av && *av)
		freeav(av);
	if (ermsg)
		free(ermsg);
}
/**
 * menv - print enviorn
 * @av: double pointer
 * @s: struct with filename and status
 *
 * Return: void
 */
void menv(char **av, st *s __attribute__ ((unused)))
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
 * @s: struct with filename and status
 *
 * Return: void
 */

void msenv(char **av, st *s)
{
	if (!(av) || !av[1] || !av[2] || av[3])
		print_err(av, ": Wrong number of argument\n", s);
	else if (_setenv(av[1], av[2], 1) == 0)
		print_err(av, ": failed to set envirioment\n", s);
	if (av && *av)
		freeav(av);
}

/**
 * uenv - unset environment builtin
 * @av: array
 * @s: struct with filename and status
 *
 * Return: void
 */
void uenv(char **av, st *s)
{
	if (!av[1] || av[2])
		print_err(av, ": Wrong number of argument\n", s);
	else if (_unsetenv(av[1]) == 0)
		print_err(av, ": failed to set enviroment\n", s);
	if (av && *av)
		freeav(av);
}
