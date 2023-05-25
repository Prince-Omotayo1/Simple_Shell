#ifndef _SHELL_H_
#define _SHELL_H_


/* for read/write buffers */
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024


/* 1 if using system getline() */
#define USE_STRTOK 0
#define USE_GETLINE 0


/* for command chainig */
#define CMD_CHAIN	3
#define CMD_AND		2
#define CMD_NORM	0
#define CMD_OR		1


#include <fcntl.h> /* for open files*/
#include <sys/types.h> /* for type pid */
#include <sys/stat.h> /* for use of stat function */
#include <unistd.h> /* for fork, execve*/
#include <errno.h> /* for errno and perror */
#include <sys/wait.h> /* for wait */
#include <stdio.h> /* for printf*/
#include <limits.h>
#include <stdlib.h>
#include <string.h> /* for strtok*/


/* for convert_number() */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"


extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 *struct passinfo - contains pseudo-arguments to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */

typedef struct passinfo
{
	list_t *env;
	int argc;
	char *arg;
	int env_changed;
	list_t *alias;
	char **argv;
	unsigned int line_count;
	list_t *history;
	int linecount_flag;
	int status;
	char *fname;
	char *path;
	int err_num;
	char **environ;

	int histcount;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
} 

info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
char *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
int _eputchar(char);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _putfd(char c, int fd);

/* toem_string2.c */
char *_strdup(const char *);
void _puts(char *);
char *_strcpy(char *, char *);
int _putchar(char);

/* toem_string1.c */
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_memory.c */
int bfree(void **);

/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);

/* toem_realloc.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_errors1.c */
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);

/* toem_builtin.c */
int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *);

/* toem_atoi.c */
int interactive(info_t *);
int _isalpha(int);
int is_delim(char, char *);
int _atoi(char *);

/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* toem_getinfo.c */
void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);

/* toem_environ.c */
int _myunsetenv(info_t *);
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);
int _myenv(info_t *);
int _mysetenv(info_t *);

/*toem_getline.c */
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t get_input(info_t *);

/* toem_getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/* toem_vars.c */
int replace_alias(info_t *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

/* toem_lists1.c */
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
void free_list(list_t **);
size_t print_list_str(const list_t *);

/* toem_lists2.c */
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* toem_history.c */
int write_history(info_t *info);
int read_history(info_t *info);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

#endif
