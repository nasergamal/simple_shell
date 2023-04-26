#include "shell.h"

/**
 * main - entry point of main shell
 * @ac: argument count
 * @av: pointer to an array of arguments
 *
 * Return: 1 on success
 */
int main(int ac __attribute__((unused)), char **av)
{
	char *buf = NULL;

	_initenv(); /** create an environ for the program **/
	loop(av, buf); /** shell loop **/
	freeenv(); /** free created environ **/
	return (0);
}
/**
 * loop - shell loop
 * @av: double pointer
 * @buf: buffer for input
 *
 * Return: void
 */
void loop(char **av, char *buf)
{
	size_t bsize = 0;
	int status = 0, att = isatty(STDIN_FILENO);
	void (*e)(char **);
	ssize_t char_count = 0;
	char **cav;

	while (char_count != EOF)
	{
		if (att) /** check mode (interactive or not) */
			_puts("($) ");
		char_count = getline(&buf, &bsize, stdin);
		if (char_count == -1 && att) /* EOF */
		{
			_puts("\n");
			break; }
		else if (char_count == -1)
			break;
		else if (char_count == 1) /* empty line*/
			continue;
		else /* normal input */
			av = tokenize(av, buf, char_count);
		cav = av;
		if (char_count > 1) /* check for builtins */
		{
			e = buildin(av);
			if (e)
			{
				if (_strcmp(av[0], "exit"))
					free(buf);
				e(av);
				continue; }
		} cav = sep(cav, &status); /* check for separator and execute based on it */
		if (!(is_cmd(cav[0]))) /* check if argument is cmd else check in $PATH*/
			cav[0] = check_cmd(cav[0]);
		execute(cav, &status);
		if (av && *av)
			freeav(av);
	}
	free(buf);
}

/**
 * tokenize - tokenize inputs and add tokens to an array
 * @av: pointer to an array
 * @buf: input content
 * @char_count: input length
 *
 * Return: poitner to array av
 */
char **tokenize(char **av, char *buf, ssize_t char_count)
{
	size_t tokenc = 0;
	int i;
	char *bufc = NULL, *token;
	const char *d = " \t\n";

	bufc = malloc(sizeof(char) * (char_count + 1));
	if (bufc == NULL)
	{
		perror("memory allocation error");
		return (NULL);
	}
	_strcpy(bufc, buf);
	token = strtok(bufc, d);
	while (token != NULL)
	{
		tokenc++;
		token = strtok(NULL, d);
	}
	tokenc++;
	token = strtok(buf, d);
	av = malloc(sizeof(char *) * tokenc);
	if (av == NULL)
	{
		perror("memory allocation error");
		return (NULL);

	}
	for (i = 0; token != NULL; i++)
	{
		av[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		_strcpy(av[i], token);
		token = strtok(NULL, d);
	}
	av[i] = NULL;
	free(bufc);
	return (av);
}
/**
 * sep - look for separators
 * @av: pointer to an array
 * @status: last execution status
 *
 * Return: av
 */

char **sep(char **av, int *status)
{
	int i, n = 0;

	for (i = 0; av[i]; i++)
	{
		if (_strcmp(av[i], ";"))
		{
			n = conv2(av, status, n, i); }
		else if (_strcmp(av[i], "#"))
		{
			free(av[i]), av[i] = '\0';
			for (i += 1; av[i] ; i++)
				free(av[i]);
			break; }
		else if (_strcmp(av[i], "$") && !(av[i][1]))
			continue;
		else if (_strcmp(av[i], "$$") || (_strcmp(av[i], "$?")))
		{
			conv(av, i, status); }
		else if (_strcmp(av[i], "$") && av[i][1])
		{
			conv(av, i, status); }
		else if (_strcmp(av[i], "&&") && av[i + 1])
		{
			n = logicalop(av, "&&", status, 0);
			break; }
		else if (_strcmp(av[i], "||") && av[i + 1])
		{
			n = logicalop(av, "||", status, 1);
			break; }
	}
	return (av + n);
}
