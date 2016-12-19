#include "shell.h"
/**
 * hsh_help - help command for hsh_shell builtins
 * @??:
 * Return: ??
 */
int hsh_help(char **arg)
{
	int i, size;
	builtin table[] = {
	{"exit", hsh_exit_help},     {"env", hsh_env_help},
	{"setenv", hsh_setenv_help}, {"unsetenv", hsh_unsetenv_help},
	{"cd", hsh_cd_help},         {"history", hsh_history_help},
	{"help", hsh_help_help}
	};

	if (arg[1] == NULL)
	{
		_write("help usage: help COMMAND\n    ");
		_write("Prints out useful information on builtin commands\n");
		return (0);
	}
	else
	{
		size = sizeof(table)/sizeof(table[0]);
		for (i = 0; i < size; i++)
		{
			if (_str_match(arg[1], table[i].name))
			{
				table[i].func();
				return (0);
			}
		}
	}
	_write("No help topics match your query (._.)\n");
	return (1);
}
/**
 * hsh_help_help - builtin help printout for help
 * Return: Always 0
 */
int hsh_help_help(void)
{
	_write("help usage: help COMMAND\n    Display helpful information about builtins.\n");
	return (0);
}
