#include "shell.h"

/**
 * execute - excute cmd with argument argv
 * @argv: pointer to array
 * @s: struct with filename and status
 *
 * Return: void
 */

void execute(char **argv, st *s)
{
	char *cmd;
	pid_t pid;

	if (!argv || !(*argv))
	{	return; }
	cmd = _strdup(argv[0]);
	if (!cmd)
		return;
	if (!(is_cmd(cmd) && (_strcmp(cmd, "./") ||
			_strcmp(cmd, "../")))) /* check if argument is cmd else check in $PATH*/
		cmd = check_cmd(cmd);
	if  (is_cmd(cmd) && (_strcmp(cmd, ".") ||
			_strcmp(cmd, "/")))
		pid = fork();
	else
	{
		print_err(argv, ": not found\n", s);
		free(cmd);
		s->status = 127;
		return;
	}
	if (pid == -1)
	{	s->status = 1, print_err(argv, ": failed to fork\n", s); }
	else if (pid == 0)
	{
		if (execve(cmd, argv, environ) == -1)
		{
			print_err(argv, ": No such file or directory", s);
			free(cmd);
			freeav(argv);
			exit(98);
		}
	}
	else
		wait(&(s->status));
	if (WIFEXITED(s->status))
		s->status = WEXITSTATUS(s->status);
	free(cmd);
}

/**
 * check_cmd - check if given argument is cmd
 * @cmd: command to be checked
 *
 * Return: cmd if exist or NULL
 */
char *check_cmd(char *cmd)
{
	char *path = _getenv("PATH"), *cpath2, *pathtok, *pathcpy;
	int pathlen, cmdlen;

	if (!path || _strlen(path) == 0 || !cmd)
		return (cmd);
	cmdlen = _strlen(cmd);
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
		if ((is_cmd(cpath2) && (access(cpath2, F_OK) == 0)))
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

void (*buildin(char **av))(char **av, st *s)
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
