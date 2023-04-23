#include "shell.h"

/**
 * execute - excute cmd with argument argv
 * @argv: pointer to array
 *
 * Return: void
 */

void execute(char **argv)
{
	int status;
	pid_t pid;

	if  (is_cmd(argv[0]))
		pid = fork();
	else
	{
		print_err(argv, ": not found\n");
		return;
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(getenv("_"));
			freeav(argv);
			exit(98);
		}
	}
	else
		wait(&status);
}

/**
 * check_cmd - check if given argument is cmd
 * @cmd: command to be checked
 *
 * Return: cmd if exist or NULL
 */
char *check_cmd(char *cmd)
{
	char *path, *cpath2, *pathtok, *pathcpy;
	int pathlen, cmdlen;

	if (!cmd)
		return (NULL);
	cmdlen = _strlen(cmd);
	path = _getenv("PATH");
	pathcpy = _strdup(path);
	pathtok = strtok(pathcpy, ":");

	while (pathtok != NULL)
	{
		pathlen = _strlen(pathtok);
		cpath2 = malloc(sizeof(char) * (cmdlen + pathlen + 2));
		_strcpy(cpath2, pathtok);
		_strcat(cpath2, "/");
		_strcat(cpath2, cmd);
		_strcat(cpath2, "\0");
		if ((is_cmd(cpath2)))
		{
			free(pathcpy);
			free(cmd);
			return (cpath2);
		}
		else
		{
			free(cpath2);
			pathtok = strtok(NULL, ":");
		}
	}
	free(pathcpy);
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
	else if (stat(cmd, &st) == 0)
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

		if (!(b[i].bld[n]))
			return (b[i].func);
	}
	return (0);
}
