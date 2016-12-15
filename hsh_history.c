#include "shell.h"
/**
 * hsh_history - builtin command hsh_history, mimics builtin history
 * @??:
 */
void hsh_history()
{
	printf("We executed history (◕‿◕✿)\n");
}
/**
 * hsh_history_help - builtin help printout for history
 */
void hsh_history_help(void)
{
	write(STDOUT_FILENO,
	"history usage: history\n    Display the history list with line numbers.\n", 71);
}
