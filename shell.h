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

/* run_execute.c */
void run_execute(char **arg_list, env_t *env_p, int cmd_size);

/* linked_env.c*/
env_t *create_envlist();
env_t *add_env(env_t **head, const char *value);
void  remove_env(env_t **head, int index);
/* helpers.c */
void print_cmdline();
void *safe_malloc(size_t size);
void free_args(char **arg_list);
void execute_func(char *cmd, char **args);

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

/* getline.c */
int _getline(char **buf);

/* path_funcs.c */
void get_path(char *path, env_t *list);
char **tokenize_path(char **search_path, char *path, int size);
/* tokenize.c */
void tokenize_buf(char *buf, char ***av);
void _av_init(char *buf, char ***av);
int _is_whitespace(char c);
/* builtin.c */
int run_builtin(char **arg_list, env_t *env_p/* wat we doing here? */);
/* memory_allocation.c */
void _free(void *address);
void defer_free(void *address);
int clear_addr_list_node(addr_list *list, void *address);
void add_addr_list_node(addr_list *list, void *address);
void free_addr_list(addr_list *list);
/* list of builtin functions */
void hsh_exit();
void hsh_env(char **arg, env_t *env_p);
void  hsh_setenv(char **arg, env_t *env_p);
void hsh_unsetenv(char **arg, env_t *env_p);
void hsh_cd();
void hsh_history();
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
