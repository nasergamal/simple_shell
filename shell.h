#ifndef SHELL_C
#define SHELL_C
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

extern char **environ;

/**
 * struct buildin - struct containing builtins
 * @bld: builtin name
 * @func: function corresponding to bld
 */
typedef struct buildin
{
	char *bld;
	void (*func)(char **);
} build;

/* main */
void loop(char **av, char *buf);
char **tokenize(char **av, char *buf, ssize_t char_count);
char **sep(char **av, int *status);

/* shell_au */
int is_cmd(char *cmd);
char *check_cmd(char *cmd);
void (*buildin(char **av))(char **av);
void execute(char **argv, int *status);

/* free */
void freeav(char **av);

/* strings handling */
int _strlen(char *str);
char *_strdup(char *str);
char *_strcpy(char *newc, char *original);
char *_strcat(char *str1, char *str2);
int _strcmp(char *str1, char *str2);
int _puts(char *str);

/* errors */
int _errputs(char *str);
void print_err(char **av, char *err);
int _atoi(char *s);

/* builtin */
void exitf(char **av);
void cdir(char **av);
void msenv(char **av);
void uenv(char **av);

/* env */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void _initenv(void);
void freeenv(void);

/* separators */
char *num_to_char(long int num);
int logicalop(char **av, char *del, int *status, int mod);
void conv(char **av, int i, int *status);
int conv2(char **av, int *status, int n, int i);

/* not implemented */
ssize_t _tkline(char **lineptr, size_t *n);
#endif
