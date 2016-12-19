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
 * Return: Always 0
 */
int hsh_env_help(void)
{
	_write("env usage: env\n    Prints out the current envirornment.\n");
	return (0);
}
