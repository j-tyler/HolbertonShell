#include "shell.h"
/**
 * hsh_exit - builtin command hsh_exit, mimics exit()
 * @??:
 */
void hsh_exit(char **arg_list)
{
	defer_free(FREE_ADDRESSES);
	/* Call _exit() with argument[1] & 0377 ?*/
	_exit(_atoi(arg_list[1]));
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
