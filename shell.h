#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() to get files*/
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

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
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg:  string generated from getline containing arguements
 *@argv: array of strings generated from arg
 *@path: string path for the current cmd
 *@argc: argument count
 *@line_count:  error count
 *@err_num: error code for exit()s in lin
 *@linecount_flag: if on count then this line of input
 *@shell_name:  program filename
 *@env:a  linked list local copy of environment
 *@environ:  modified copy of environ from LL env
 *@history:  history node
 *@alias:  alias node
 *@env_changed: on if environent was changed
 *@status: return status of the last exec'd cmd
 *@cmd_buf: address of ptr to cmd_buf,  if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd:  fd from  line to read input
 *@histcount:history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *shell_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* ptr to cmd ; , for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - has a builtin string and related function
 *@type: the builtin cmd flag
 *@func:  function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* loop.c */
int shell_loop(info_t *, char **);
int locate_builtin(info_t *);
void locate_command(info_t *);
void execute_command(info_t *);

/* parse.c */
char *duplicate_chars(char *, int, int);
int executable_cmd(info_t *, char *);
char *locate_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors1.c */
void print_to_stderr(char *);
int write_to_stderr(char);
int write_to_fd(char c, int fd);
int print_to_fd(char *str, int fd);

/* string1.c */
int string_length(char *);
int string_compare(char *, char *);
char *begins_with(const char *, const char *);
char *string_concat(char *, char *);

/*string2.c */
int write_char(char);
void print_str(char *);
char *duplicate_str(const char *);
char *copy_str(char *, char *);

/*exit_shell.c */
char *string_copy(char *, char *, int);
char *string_concat(char *, char *, int);
char *find_char(char *, char);

/*tow.c */
char **split_string_by_delimiter(char *, char *);
char **split_string_by_char(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*memory_buffer*/
int free_buffer(void **);

/* atoi.c */
int check_alpha(int);
int check_delimiter(char, char *);
int convert_to_integer(char *);
int is_interactive(info_t *);

/*errors1.c */
int str_to_int(char *);
void display_error(info_t *, char *);
int print_decimal(int, int);
char *num_to_str(long int, int, int);
void eliminate_comments(char *);

/* builtin1.c */
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);

/*builtin2.c */
int display_history(info_t *);
int remove_alias(info_t *, char *);
int create_alias(info_t *, char *);
int show_alias(list_t *);
int manage_alias(info_t *);

/*getline.c */
ssize_t input_buf(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
ssize_t read_buf(info_t *, char *, size_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* get_info.c */
void clear_information(info_t *);
void set_information(info_t *, char **);
void free_information(info_t *, int);

/*environ.c */
int display_env(info_t *);
char *find_env_var(info_t *, const char *);
int create_or_modify_env(info_t *);
int remove_env_var(info_t *);
int fill_env_list(info_t *);

/*get_environ.c */
char **get_environment(info_t *);
int unset_environment_var(info_t *, char *);
int set_environment_var(info_t *, char *, char *);

/*get_history.c */
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buffer, int linecount);
int renumber_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);

/* list1.c */
list_t *insert_node_begin(list_t **, const char *, int);
list_t *insert_node_end(list_t **, const char *, int);
size_t display_list_str(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void release_list(list_t **);

/* list2.c */
size_t linked_list_length(const list_t *);
char **linked_list_to_string_array(list_t *);
size_t display_linked_list(const list_t *);
list_t *find_node_prefix(list_t *, char *, char);
ssize_t find_node_index(list_t *, list_t *);

/* vars.c */
int test_chain_delimeter(info_t *, char *, size_t *);
void verify_chain(info_t *, char *, size_t *, size_t, size_t);
int substitute_alias(info_t *);
int substitute_vars(info_t *);
int swap_string(char **, char *);

#endif
