#include "shell.h"
/**
 * hsh_unsetenv - builtin command hsh_unsetenv, mimics builtin unsetenv
 * @??:
 */
void hsh_unsetenv()
{
	printf("We executed unsetenv (◕‿◕✿)\n");

	/* delete variable name from env */
	/* return 0 on success, -1 on failure */
	/* fails if name is NULL,string is len 0, string contains '=', or out of memory */
}
/**
 * hsh_unsetenv_help - builtin help printout for unsetenv
 */
void hsh_unsetenv_help(void)
{
	write(STDOUT_FILENO,
	"unsetenv usage: unsetenv VARIABLE:\n    Remove an envirornment variable.\n",
	72);
}
