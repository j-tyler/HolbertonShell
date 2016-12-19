#include "shell.h"
/**
 * hsh_exit - builtin command hsh_exit, mimics exit()
 * @??:
 */
void hsh_exit(char **arg_list, env_t *envp, int buf_size, hist_t *history)
{
	int tmp;

	tmp = _atoi(arg_list[1]);
	write_history(envp, history);
	defer_free(FREE_ADDRESSES);
	_exit(tmp);
}
/**
 * hsh_exit_help - builtin help printout for exit
 */
void hsh_exit_help(void)
{
	write(STDOUT_FILENO,
	"exit usage: exit N\n    Exit the shell.\n\n    ", 44);
	write(STDOUT_FILENO,
	"Exits the shell with a status of N.  If N is omitted, ", 54);
	write(STDOUT_FILENO,
	"the exit status\n    is that of the last command executed.\n", 58);
}
