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
	int st = 0;

	_initenv(); /** create an environ for the program **/
	st = loop(av, buf); /** shell loop **/
	freeenv(); /** free created environ **/
	return (st);
}
/**
 * loop - shell loop
 * @av: double pointer
 * @buf: buffer for input
 *
 * Return: void
 */
int loop(char **av, char *buf)
{
	size_t bsize = 0;
	int att = isatty(STDIN_FILENO);
	void (*e)(char **, st *);
	ssize_t char_count = 0;
	char **cav;
	st s[] = { {0, NULL} };

	s->fname = av[0];
	signal(SIGINT, sighand);
	while (char_count != EOF)
	{
		if (att) /** check mode (interactive or not) */
			_puts("($) ");
		char_count = getline(&buf, &bsize, stdin);
		if (char_count == -1 && att) /* EOF */
		{	_puts("\n");
			break; }
		else if (char_count == -1)
		{	break; }
		else /* normal input */
			av = tokenize(av, buf, char_count);
		if (!av || !av[0])
		{	freeav(av);
			continue; }
		cav = av, e = buildin(av); /* check for builtins */
		if (e)
		{
			if ((_strcmp(av[0], "exit") && !(av[1])))
				{	free(buf), buf = NULL, freeenv(), freeav(av);
					exit(s->status); }
				if (_strcmp(av[0], "exit") && av[1])
					free(buf), buf = NULL, s->status = 2;
				e(av, s);
				continue; }
		cav = sep(cav, s); /* check for separator and execute based on it */
		execute(cav, s);
		if (av && *av)
			freeav(av); }
	if (buf != NULL)
		free(buf);
	return (s->status); }

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
		perror("failed to allocate memory");
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
		perror("failed to allocate memory");
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
 * @s: struct with filename and status
 *
 * Return: av
 */

char **sep(char **av, st *s)
{
	int i, n = 0;

	for (i = 0; av[i]; i++)
	{
		if (_strcmp(av[i], ";"))
		{
			n = conv2(av, s, n, i); }
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
			conv(av, i, s); }
		else if (_strcmp(av[i], "$") && av[i][1])
		{
			conv(av, i, s); }
		else if (_strcmp(av[i], "&&") && av[i + 1])
		{
			n = logicalop(av, "&&", s, 0);
			break; }
		else if (_strcmp(av[i], "||") && av[i + 1])
		{
			n = logicalop(av, "||", s, 1);
			break; }
	}
	return (av + n);
}
/**
 * sighand - handle signals
 * @sig_num: not used
 *
 * Return: void
 */
void sighand(int sig_num __attribute__((unused)))
{
	_puts("\n($) ");
}
