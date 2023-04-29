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
#include <signal.h>
extern char **environ;

/**
 * struct stats - struct containing stats
 * @status: execution status
 * @fname: program name
 */
typedef struct stats
{
	int status;
	char *fname;
} st;
/**
 * struct buildin - struct containing builtins
 * @bld: builtin name
 * @func: function corresponding to bld
 */
typedef struct buildin
{
	char *bld;
	void (*func)(char **, st *);
} build;

/* main */
int loop(char **av, char *buf);
char **tokenize(char **av, char *buf, ssize_t char_count);
char **sep(char **av, st *s);
void sighand(int sig_num __attribute__((unused)));

/* shell_au */
int is_cmd(char *cmd);
char *check_cmd(char *cmd);
void (*buildin(char **av))(char **av, st *s);
void execute(char **argv, st *s);

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
void print_err(char **av, char *err, st *s);
int _atoi(char *s);

/* builtin */
void exitf(char **av, st *s);
void cdir(char **av, st *s);
void menv(char **av, st *s);
void msenv(char **av, st *s);
void uenv(char **av, st *s);

/* env */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void _initenv(void);
void freeenv(void);

/* separators */
char *num_to_char(long int num);
int logicalop(char **av, char *del, st *s, int mod);
void conv(char **av, int i, st *s);
int conv2(char **av, st *s, int n, int i);
void rmcomment(char *buf);

/* not implemented */
ssize_t _tkline(char **lineptr, size_t *n);
#endif
