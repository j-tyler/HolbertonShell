#include "shell.h"
/**
 * hsh_env - builtin command hsh_env, mimics sh builtin env
 * @??:
 */
void hsh_env(char **arg_list, env_t *envp)
{
	print_env(envp);
}
/**
 * hsh_env_help - builtin help printout for env
 */
void hsh_env_help(void)
{
	write(STDOUT_FILENO,
	"env usage: env\n    Prints out the current envirornment.\n", 56);
}
