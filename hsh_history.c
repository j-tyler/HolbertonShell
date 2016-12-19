#include "shell.h"
/**
 * hsh_history - builtin command hsh_history, mimics builtin history
 * @??:
 */
int hsh_history()
{
	printf("We executed history (◕‿◕✿)\n");
	return (0);
}
/**
 * hsh_history_help - builtin help printout for history
 */
int hsh_history_help(void)
{
	write(STDOUT_FILENO,
	"history usage: history\n    Display the history list with line numbers.\n", 71);
	return (0);
}
