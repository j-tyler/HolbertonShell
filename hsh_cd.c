#include "shell.h"
/**
 * hsh_cd - builtin command hsh_cd, mimics cd
 * @??:
 */
void hsh_cd()
{
	printf("We executed cd (◕‿◕✿)\n");
}
/**
 * hsh_cd_help - builtin help printout for cd
 */
void hsh_cd_help(void)
{
	/* Maybe write more here, actualy help printout is a book */
	write(STDOUT_FILENO,
	"cd usage: cd DIR\n    Change the current directory to DIR.\n", 58);
}
