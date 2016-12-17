#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define ARGLISTINIT 5
#define FREE_ADDRESSES ((void *)3)
/**
 * struct buffer - structure for controlling buffer
 * @buf: pointer the buffer
 * @size: size of the buffer
 * @bp: current point in buffer to check for multiple command passes
 */
typedef struct buffer
{
	char *buf;
	unsigned int size;
	unsigned int bp;
} buffer;
/**
 * struct builtin - lookup structure for builtin functions
 * @name: string name user types to call function
 * @func: function pointer to that function
 */
typedef struct builtin
{
	char *name;
	void (*func)();
} builtin;
/**
 * struct addr_list
 * @address: an address of any type
 * @next: the next node in the list
 */
typedef struct addr_list
{
	void *address;
	struct addr_list *next;
} addr_list;

/**
 * struct history_list
 * @cmd: command given as input
 * @next: pointer to next node on list
 */

typedef struct hist_s
{
	char *cmd;
	struct hist_s *next;
} hist_t;

extern char **environ;

/**
 * struct env_s - structure for each environmental variable
 * @value: value of the environmental variable
 * @next: next environmental variable
 */

typedef struct env_s
{
	char *value;
	struct env_s *next;
} env_t;

/* history_func.c*/
hist_t *create_history(env_t *envp);
int read_file(env_t *envp, char **buf);
hist_t *add_history(hist_t **head, const char *cmd);
void print_history(hist_t *head);

/* history_func2.c*/
hist_t *add_cmdhist(hist_t *history, char *cmd);
hist_t *pop_head(hist_t **head);
void write_history(env_t *envp, hist_t *history);
char *_itoa(int num);

int more_cmds(buffer *buf, int return_value);
void trim_cmd(buffer *buf);
/* run_execute.c */
void run_execute(char **arg_list, env_t *env_p, int cmd_size);

/* linked_env.c*/
env_t *create_envlist();
env_t *add_env(env_t **head, const char *value);
void  remove_env(env_t **head, int index);
void update_env(env_t *envp, char *name, char *value);

/* helpers.c */
void print_cmdline();
void *safe_malloc(size_t size);
void free_args(char **arg_list);
void execute_func(char *cmd, char **args);
char *rm_vname(env_t *envp, char *arg, int buf_size);

/* helper_str.c*/
char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *s, char b, unsigned int n);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strstr(char *haystack, char *needle);

/* helper_str2.c */
char *_strdup(char *str);
char *_strchr(char *s, char c);
int _strlen(char *s);
int _str_match(char *s1, char *s2);
int _atoi(char *s);

/* getline.c */
int _getline(buffer *buf);

/* path_funcs.c */
void get_path(char *path, env_t *list);
char **tokenize_path(char **search_path, char *path, int size);

/* tokenize.c */
void tokenize_buf(buffer *buf, char ***av);
void _av_init(char *buf, char ***av);
void _add_null(char *buf);
int _is_whitespace(char c);
int _is_endofcmd(char c);
/* builtin.c */
int run_builtin(char **arg_list, env_t *env_p, int buf_size, hist_t *history);

/* memory_allocation.c */
void _free(void *address);
void defer_free(void *address);
int clear_addr_list_node(addr_list *list, void *address);
void add_addr_list_node(addr_list *list, void *address);
void free_addr_list(addr_list *list);

/* list of builtin functions */
void hsh_exit(char **arg_list, env_t *env_p, int buf_size, hist_t *history);
void hsh_env(char **arg, env_t *env_p);
void hsh_setenv(char **arg, env_t *env_p);
void hsh_unsetenv(char **arg, env_t *env_p);
void hsh_cd(char **arg, env_t *env_p, int buf_size);
void hsh_history(char **arg, env_t *env_p, int buf_size, hist_t *history);
void hsh_help(char **arg);

/* list of builtin help printouts */
void hsh_exit_help(void);
void hsh_env_help(void);
void hsh_setenv_help(void);
void hsh_unsetenv_help(void);
void hsh_cd_help(void);
void hsh_history_help(void);
void hsh_help_help(void);
#endif
