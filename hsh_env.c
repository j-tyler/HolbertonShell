#include "shell.h"
/**
 * hsh_env - builtin command hsh_env, mimics sh builtin env
 * @??:
 */
int hsh_env(char **arg_list, env_t *envp)
{
	print_env(envp);
	return (0);
}
/**
 * hsh_env_help - builtin help printout for env
 */
int hsh_env_help(void)
{
	write(STDOUT_FILENO,
	"env usage: env\n    Prints out the current envirornment.\n", 56);
	return (0);
}
