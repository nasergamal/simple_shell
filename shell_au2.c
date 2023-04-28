#include "shell.h"

/**
 * _errputs - loop through errormsg to print
 * @str: error string
 *
 * Return: number of printed characters
 */
int _errputs(char *str)
{
	int i;

	if (!(str))
		return (0);
	for (i = 0; str[i]; i++)
		write(2, &str[i], 1);
	return (i);
}
/**
 * _puts - print string
 * @str: string
 *
 * Return: number of printed characters
 */
int _puts(char *str)
{
	int i;

	if (!(str))
		return (0);
	for (i = 0; str[i]; i++)
		write(1, &str[i], 1);
	return (i);
}
/**
 * print_err - print errormsg
 * @av: array
 * @err: error msg
 * @s: struct with filename and status
 *
 * Return: void
 */
void print_err(char **av, char *err, st *s)
{
	_errputs(s->fname);
	_errputs(": ");
	_errputs("1"); /* line counter needed*/
	_errputs(": ");
	_errputs(av[0]);
	_errputs(err);
}
/**
 * _atoi - Entry point
 * @s: the string to be converted
 *
 * Description: take a string and convert it to integer
 *
 * Return: integer
 */

int _atoi(char *s)
{
	int i, m = 0;

	unsigned int n = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ' ' || s[i] == '+')
			continue;
		else if (s[i] == '-')
		{
			m++;
			continue;
		}
		else if ((s[i] >= 'a' && s[i] <= 'z') ||
				(s[i] >= 'A' && s[i] <= 'Z'))
			continue;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			n = n * 10;
			n = n + (s[i] - '0');
		}
	}
	if (m % 2 != 0)
		n = -n;
	return (n);
}
