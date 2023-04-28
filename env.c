#include "shell.h"

/**
 * _getenv - get environment
 * @name: environment var
 *
 * Return: environment value
 */
char *_getenv(const char *name)
{
	int i, n;
	char *ptr;

	for (i = 0, n = 0; environ[i]; i++, n = 0)
	{
		if (name[n] == environ[i][n])
			for (n = 0; name[n]; n++)
			{
				if (name[n] != environ[i][n])
					break;
			}
		if (!name[n])
		{
			ptr = (environ[i] + (n + 1));
			return (ptr);
		}
	}
	return (NULL);
}
/**
 * _setenv - set environment
 * @name: environment var
 * @value: environment value
 * @overwrite: non zero to overwrite exising var
 *
 * Return: 1(success) or 0(failure)
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i, n, f = 0;
	char *buf, *ptr, **cenvi;

	for (i = 0, n = 0; environ[i]; i++, n = 0)
	{
		if (name[n] == environ[i][n])
			for (n = 0; name[n]; n++)
			{
				if (name[n] != environ[i][n])
					break; }
		if (!name[n])
			break;
	}
	if (!environ[i])
		f = 1;
	if (!environ[i] || (overwrite && !name[n]))
	{
		if (!f)
			ptr = environ[i];
		buf = malloc(sizeof(char) * (_strlen((char *)name)
					+ _strlen((char *)value) + 2));
		if (buf == NULL)
			return (0);
		_strcpy(buf, (char *)name);
		_strcat(buf, "=");
		_strcat(buf, (char *)value);
		environ[i] = buf;
		if (f)
		{
			cenvi = environ;
			_initenv();
			for (i = 0; cenvi[i]; i++)
				free(cenvi[i]);
			free(cenvi);
		}
		else if (!f)
			free(ptr);
		return (1);
	}
	return (0);
}
/**
 * _unsetenv - remove environmental variable
 * @name: environment var
 *
 * Return: 1(success) or 0(failure)
 */
int _unsetenv(const char *name)
{
	int i, n;
	char *ptr;

	for (i = 0, n = 0; environ[i]; i++, n = 0)
	{
		if (name[n] == environ[i][n])
			for (n = 0; name[n]; n++)
			{
				if (name[n] != environ[i][n])
					break;
			}
		if (!name[n])
			break;
	}
	if (!name[n])
	{
		ptr = environ[i];
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
		free(ptr);
		return (1);
	}
	else
		return (0);
}

/**
 * _initenv - intiate environ for the program
 *
 * Return: void
 */
void _initenv(void)
{
	int i, n;
	char **envi = NULL;

	for (i = 0; environ[i]; i++)
		;
	envi = malloc(sizeof(char *) * (i + 2));
	if (envi == NULL)
		return;
	for (i = 0 ; environ[i]; i++)
	{
		envi[i] = malloc(sizeof(char) * (_strlen(environ[i]) + 1));
		if (envi[i] == NULL)
		{
			for (; i >= 0; i--)
				free(envi[i]);
			free(envi);
			return;
		}
		for (n = 0; environ[i][n]; n++)
			envi[i][n] = environ[i][n];
		envi[i][n] = '\0';
	}
	envi[i] = NULL;
	envi[i + 1] = '\0';
	environ = envi;
}

/**
 * freeenv - free program environ
 * Return: void
 */
void freeenv(void)
{
	int i = 0;

	if (environ && *environ)
	{
		while (environ[i])
		{
			free(environ[i]);
			i++;
		}
		free(environ);
	}
}
