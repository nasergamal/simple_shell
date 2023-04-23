#include "shell.h"

/**
 * _strlen - measure string length
 * @str: string to be measured
 *
 * Return: length
 */
int _strlen(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		;
	return (i);
}

/**
 * _strdup - duplicate string
 * @str: string to be duplicated
 *
 * Return: new string
 */
char *_strdup(char *str)
{
	int i, len;
	char *newstr;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	newstr = malloc(sizeof(char) * len + 1);
	if (newstr == NULL)
		return (NULL);
	for (i = 0; str[i]; i++)
		newstr[i] = str[i];
	newstr[i] = '\0';
	return (newstr);
}
/**
 * _strcpy - copy string to a new one
 * @original: string source
 * @newc: copy destination
 *
 * Return: pointer to copied string
 */
char *_strcpy(char *newc, char *original)
{
	int i;

	if (original == NULL)
		return (newc);
	for (i = 0; original[i]; i++)
		newc[i] = original[i];
	newc[i] = '\0';
	return (newc);
}
/**
 * _strcat - concatenate string from str2 to str1
 * @str2: string source
 * @str1: concatenation destination
 *
 * Return: pointer to concatenated string
 */
char *_strcat(char *str1, char *str2)
{
	int lens1;
	char *ptr;

	lens1 = _strlen(str1);
	ptr = str1 + lens1;
	while (*str2)
		*ptr++ = *str2++;
	*ptr = *str2;
	return (str1);
}

/**
 * _strcmp - compare two strings
 * @str1: 1st string
 * @str2: 2nd string
 *
 * Return: 1 on success or 0 on failure
 */
int _strcmp(char *str1, char *str2)
{
	int i, f = 0;

	for (i = 0; str1[i] && str2[i]; i++)
	{
		if (str1[i] != str2[i])
			f = 1;
	}
	if (f)
		return (0);
	return (1);
}
