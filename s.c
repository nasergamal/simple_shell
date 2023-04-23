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
	size_t bsize = 0;
	int att = isatty(STDIN_FILENO);
	void (*e)(char **);
	ssize_t char_count;
	char *buf = NULL;

	_initenv();
	while (1)
	{
		if (att)
			_puts("($) ");
		char_count = /*_tkline(&buf, &bsize);*/ getline(&buf, &bsize, stdin);
		if (char_count == -1)
		{
			printf("\n");
			break; }
		else if (char_count == 1)
			continue;
		else
			av = tokenize(av, buf, char_count);
		if (char_count > 1)
		{
			e = buildin(av);
			if (e)
			{
				if (_strcmp(av[0], "exit"))
					free(buf);
				e(av);
				continue; }
		} sep(av);
		if (!(is_cmd(av[0])))
			av[0] = check_cmd(av[0]);
		execute(av);
		if (av && *av)
			freeav(av);
		if (!att)
			break;
	}
	freeenv(), free(buf);
	return (0);
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
	const char *d = " \n";

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
 *
 * Return: av
 */

char **sep(char **av)
{
	int i;
	char **av2;

	for (i = 0; av[i]; i++)
	{
		if (_strcmp(av[i], ";"))
		{
			av2 = av;
			av += (i + 1);
			av2[i] = NULL;
			if (!(is_cmd(av2[0])))
				av2[0] = check_cmd(av2[0]);
			execute(av2);
			i = 0;
		}
	}
	return (av);
}
