#include "shell.h"
/**
 * hsh_exit - builtin command hsh_exit, mimics exit()
 * @??:
 */
int hsh_exit(char **arg_list, env_t *envp, int buf_size, hist_t *history)
{
	int tmp;

	tmp = _atoi(arg_list[1]);
	write_history(envp, history);
	defer_free(FREE_ADDRESSES);
	_exit(tmp & 0377);
	return (0);
}
/**
 * hsh_exit_help - builtin help printout for exit
 * Return: Always 0
 */
int hsh_exit_help(void)
{
	_write("exit usage: exit N\n    Exit the shell.\n\n    ");
	_write("Exits the shell with a status of N.  If N is omitted, ");
	_write("the exit status\n    is that of the last command executed.\n");
	return (0);
}
