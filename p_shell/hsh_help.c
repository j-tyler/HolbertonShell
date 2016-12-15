#include "shell.h"
/**
 * hsh_help - help command for hsh_shell builtins
 * @??:
 * Return: ??
 */
void hsh_help(char **arg)
{
	int i, size;
	builtin table[] = {
	{"exit", hsh_exit_help},     {"env", hsh_env_help},
	{"setenv", hsh_setenv_help}, {"unsetenv", hsh_unsetenv_help},
	{"cd", hsh_cd_help},         {"history", hsh_history_help},
	{"help", hsh_help_help}
	};

	if (arg == NULL)
		printf("We executed help (◕‿◕✿)\n");
	else
	{
		size = sizeof(table)/sizeof(table[0]);
		for (i = 0; i < size; i++)
		{
			if (_str_match(arg[1], table[i].name))
			{
				table[i].func();
				return;
			}
		}
	}
	write(STDOUT_FILENO, "No help topics match your query (._.)\n", 38);
}
/**
 * hsh_help_help - builtin help printout for help
 */
void hsh_help_help(void)
{
	write(STDOUT_FILENO,
	"help usage: help COMMAND\n    Display helpful information about builtins.\n",73);
}
