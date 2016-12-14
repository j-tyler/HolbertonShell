#include "shell.h"
/**
 * hsh_setenv - builtin command hsh_setenv, mimics builtin setenv
 * @??:
 */
void hsh_setenv()
{
	printf("We executed setenv (◕‿◕✿)\n");

	/* hsh_setenv(!something else?, char *name, char *value, int overwrite) */
	/* Add env variable NAME, with VALUE */
	/* if NAME exists, overwrite if overwite is non-zero */
	/* return 0 on success, -1 on error */
	/* Fails on name is NULL, string len 0, string contains '=' or out of mem */
}
/**
 * hsh_setenv_help - builtin help printout for setenv
 */
void hsh_setenv_help(void)
{
	write(STDOUT_FILENO,
	"setenv usage: setenv VARIABLE VALUE\n    Initialize a new", 56);
	write(STDOUT_FILENO,
	" environment variable, or modify an existing one.\n", 50);
}
