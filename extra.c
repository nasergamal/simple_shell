#include "shell.h"

/**
 * num_to_char - convert numbers to characters
 * @num: numbers to be converted
 *
 * Return: pointer
 */
char *num_to_char(long int num)
{
	static char buf[50];
	char *ptr, sign = 0;
	unsigned int n = num;

	if (num < 0)
	{
		n = -num;
		sign = '-';
	}
	ptr = &buf[50];
	*ptr = '\0';

	do {
		*(--ptr) = (n % 10) + '0';
		n /= 10;
	} while (n > 0);
	if (sign)
		*(--ptr) = sign;
	return (ptr);
}
/**
 * logicalop - deal with logical operator in input
 * @av: double pointer
 * @del: operators && or ||
 * @s: struct with filename and status
 * @mod: mode 0 for && and 1 for ||
 *
 * Return: end of av
 */
int logicalop(char **av, char *del, st *s, int mod)
{
	char **av2, *li;
	int i, n = 0;

	s->status = 0;
	if (mod)
		s->status = 1;
	for (i = 0; av[i]; i++)
	{
		if (_strcmp(av[i], del) && av[i + 1])
		{
			av2 = &av[n], n = i + 1, li = av[i], av[i] = NULL;
			if ((!(s->status) && !(mod)) || ((s->status) && (mod)))
			{
				execute(av2, s); }
			if (!(av[i]) && av[i + 1])
				av[i] = li;
			if (((s->status) && !mod) || (!(s->status) && (mod)))
			{
				while (av[i])
					i++;
				n = i;
				break;
			}
			if (av[i] && (!av[i + 1]))
			{
				if ((!(s->status) && !mod) || ((s->status) && (mod)))
				{
					av2 = &av[n], n = i + 1;
					execute(av2, s); }
			}

		}
	}
	return (n);
}
/**
 * conv - convert $ to equivalent variable
 * @av: double pointer
 * @i: av count at which $ exist
 * @s: struct with filename and status
 *
 * Return: void
 */
void conv(char **av, int i, st *s)
{
	int f = 0;
	char *name = '\0';

	if (_strcmp(av[i], "$?") || (_strcmp(av[i], "$$")))
	{
		if (av[i][2])
		{	name = malloc(sizeof(char) * (_strlen(av[i]) + 1));
			_strcpy(name, av[i]), name += 2;
			f = 1; }
		if (_strcmp(av[i], "$?"))
		{	free(av[i]), av[i] = malloc(sizeof(char) *
			(_strlen(num_to_char(s->status)) + (f ? _strlen(name) : 0) + 1));
			_strcpy(av[i], num_to_char(s->status));
			if (f)
			{
				_strcat(av[i], name), free(name -= 2); }
		}
		else if (_strcmp(av[i], "$$"))
		{
			free(av[i]), av[i] = malloc(sizeof(char) *
				(_strlen(num_to_char(getpid())) + (f ? _strlen(name) : 0) + 1));
			_strcpy(av[i], num_to_char(getpid()));
			if (f)
			{
				_strcat(av[i], name), free(name -= 2); }
			return; }
	}
	else if (_strcmp(av[i], "$"))
	{
		name = malloc(sizeof(char) * (_strlen(av[i]) + 1));
		_strcpy(name, av[i]), name++;
		if (getenv(name))
		{
			free(av[i]), av[i] =  malloc(sizeof(char) * (_strlen(_getenv(name)) + 1));
			_strcpy(av[i], _getenv(name)); }
		else
		{	free(av[i]), av[i] =  malloc(sizeof(char) * (2));
			_strcpy(av[i], "\0"); }
		free(--name);
		return; }
}

/**
 * conv2 - deal with ; separator
 * @av: double pointer
 * @n: start of next function after ; separator
 * @i: av count at which $ exist
 * @s: struct with filename and status
 *
 * Return: void
 */
int conv2(char **av, st *s, int n, int i)
{
	char **av2, *li, *cmd;

	av2 = &av[n], n = i + 1, li = av[i], av[i] = NULL;
	execute(av2, s), av[i] = li;

	if (!av[i + 1] && av[i][1])
	{
		cmd = malloc(sizeof(char) * (_strlen(av[i]) + 1));
		_strcpy(cmd, av[i]), cmd++;
		free(av[i]), av[i] = malloc(sizeof(char) * (_strlen(cmd) + 1));
		_strcpy(av[i], cmd);
		free(--cmd);
		n = i;
	}
	return (n);
}
