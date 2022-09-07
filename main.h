#ifndef MAIN_H
#define MAIN_H

/* Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

/* Global Variable*/
extern char **environ;

/* Macros */
#define BUFSIZE 256
#define TOKENSIZE 64
#define PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define PROMPT "$ "
#define SUCCESS (1)
#define FAIL (-1)
#define NEUTRAL (0)

/* Struct */
/**
 * struct sh_data - A Global data structure
 * @line: Line input
 * @args: arguments token
 * @error_msg: global path
 * @cmd: parsed command
 * @index: command index
 * @oldpwd: old path visited
 * @env: environment
 *
 * Description: Structure containing all the variables needed
 */

typedef struct sh_data
{
	char *line;
	char **args;
	char *cmd;
	char *error_msg;
	char *oldpwd;
	unsigned long int index;
	char *env;
} sh_t;

typedef struct builtin
{
	char *cmd;
	int (*f)(sh_t *data);
} blt_t;

int prompt(void);
char *_read(void);
char *_fullpathbuffer(char **av, char *PATH, char *copy);
int checkbuiltins(char **av, char *buffer, int exitstatus);
int _forkprocess(char **av, char *buffer, char *fullpathbuffer);

int main(int ac, char **av, char **env);
void prompt(void);
void handle(int signals);
void _EOF(char *buffer);
void shell_exit(char **command);

char *prompt_n_read(char *path_str, char **array_path);
char **split_buf(char *buf);
int token_count_buf(char *buf);
int fork_n_exec(char *str_buf_path, char **array_buf);
char *_getenv(const char *name);
char **split_path(char *path_str);
int token_count_path(char *path_str);
int _strlen(char *s);
char *buf_path_cat(int counter, char *av, char *array_buf, char **array_path);
int _status(char *str_buf_path);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _putchar(char c);
int _print(char *str);
void print_number(int n);
void sig_handler(int signo);

int handle_cmd(char **av, int counter, char **array_buf, char **array_path,
char *str_buf_path);
int handle_path_cmd(char **av, int counter, char **array_buf);
int handle_nopath_cmd(char **array_path, char **av, char **array_buf,
int counter, char *str_buf_path);


typedef struct builtins
{
	char *name;
	void (*f)(char **, char *, char *, char **, int);
} built_ins;

void (*get_builtins_func(char *s))(char **, char *, char *, char **, int);
void env_(char **array_buf, char *buf, char *path_str, char **array_path,
int exit_status);
void exit_(char **array_buf, char *buf, char *path_str, char **array_path,
int exit_status);
void help_(char **array_buf, char *buf, char *path_str, char **array_path,
int exit_status);

/* Tools */
void *fill_an_array(void *a, int el, unsigned int len);
void signal_handler(int signo);
char *_getenv(char *path_name);
void index_cmd(sh_t *data);
void array_rev(char *arr, int len);

/* More Tools */
char *_itoa(unsigned int n);
int intlen(int num);
int _atoi(char *c);
int print_error(sh_t *data);
int write_history(sh_t *data);
int _isalpha(int c);

/* Memory */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
int free_data(sh_t *);

/* Parses */
int is_path_form(sh_t *data);
int is_builtin(sh_t *data);
void is_short_from(sh_t *data);

#endif
