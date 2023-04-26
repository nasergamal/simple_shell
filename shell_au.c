#include "shell.h"

/**
 * execute - excute cmd with argument argv
 * @argv: pointer to array
 * @status: child pid excution status
 *
 * Return: void
 */

void execute(char **argv, int *status)
{
	pid_t pid;

	if (!argv || !argv[0])
	{
		return;
	}
	if  (is_cmd(argv[0]) && (access(argv[0], F_OK) == 0))
		pid = fork();
	else
	{
		print_err(argv, ": not found\n");
		*status = 127;
		return;
	}
	if (pid == -1)
	{	*status = 1, print_err(argv, ": failed to fork\n"); }
	else if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(getenv("_"));
			freeav(argv);
			exit(98);
		}
	}
	else
		wait(status);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
}

/**
 * check_cmd - check if given argument is cmd
 * @cmd: command to be checked
 *
 * Return: cmd if exist or NULL
 */
char *check_cmd(char *cmd)
{
	char *path = _getenv("PATH"), *cpath2;
	int cp = 0, sp = 0, n;

	if (!path || _strlen(path) == 0)
		return (cmd);
	if (_strcmp(cmd, "./"))
		return (cmd);

	while (1)
	{
		if (!path[cp] || path[cp] == ':')
		{
			cpath2 = malloc(sizeof(char) * (cp - sp + _strlen(cmd) + 2));
			if (cpath2 == NULL)
				return (cmd);
			for (n = 0; sp < cp; sp++)
				if (path[sp] != ':')
					cpath2[n++] = path[sp];
			cpath2[n] = '\0';
			if (!cpath2)
				_strcat(cpath2, cmd);
			else
			{
				_strcat(cpath2, "/");
				_strcat(cpath2, cmd); }
			if ((is_cmd(cpath2) && (access(cpath2, F_OK) == 0)))
			{
				free(cmd);
				return (cpath2);
			}
			free(cpath2);
			if (!path[cp])
				break;
			sp = cp;
			} cp++;
	}
	return (cmd);

}
/**
 * is_cmd - check if cmd exist
 * @cmd: command
 *
 * Return: 1(success) or 0(failure)
 */
int is_cmd(char *cmd)
{
	struct stat st;

	if (!cmd || stat(cmd, &st))
	{
		return (0);
	}
	else if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}
/**
 * buildin - check if given cmd is builtin cmd
 * @av: pointer to array
 *
 * Return: void
 */

void (*buildin(char **av))(char **av)
{
	int i, n = 0;

	build b[] = {
		{"exit", exitf},
		{"cd", cdir},
		{"env", menv},
		{"setenv", msenv},
		{"unsetenv", uenv},
		{NULL, NULL}
	};
	for (i = 0; b[i].bld; i++)
	{
		if (av[0][n] ==  b[i].bld[n])
		{
			for (n = 0; av[0][n]; n++)
			{
				if (av[0][n] !=  b[i].bld[n])
					break;
			}
		}

		if (!(b[i].bld[n]) && !(av[0][n]))
			return (b[i].func);
	}
	return (0);
}
