#include "shell.h"

ssize_t _tkline(char **lineptr, size_t *n)
{
	size_t no_ch;
	char new[1024];
	char *line = *lineptr;

	fflush(stdout);
	no_ch = read(STDIN_FILENO, new, 1024);
	if (no_ch == 0)
		return (-1);
	if (line == NULL || no_ch > *n)
	{
		*n = no_ch + 1;
		line = malloc(sizeof(char) * (*n + 1));
		if (line == NULL)
		{
			perror("malloc failed");
			return (-1);
		}
		*lineptr = line;
	}
	memcpy(line, new, no_ch);
	line[no_ch] = '\0';
	return (no_ch);
}
