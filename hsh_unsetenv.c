#include "shell.h"
/**
 * hsh_unsetenv - builtin command hsh_unsetenv, mimics builtin unsetenv
 * @arg_list: arguement list for unstenv, contains the variable name
 * @envp: the linked list of all environment variables
 * Description: This will delete the node that contains the variable given, if
 * node does not exist then function will succeed
 */
int hsh_unsetenv(char **arg_list, env_t *envp)
{
	int count;
	env_t *temp;
	char *name;

	if (arg_list[1] == NULL)
	{
		write(0, "Error: wrong number for arguments\n", 34);
		return (0);
	}
	/* set up for strings */
	name = safe_malloc(sizeof(char) * _strlen(arg_list[1]) + 3);
	_memset(name, '\0', (_strlen(arg_list[1]) + 3));
	_memcpy(name, arg_list[1], _strlen(arg_list[1]));
	_strcat(name, "=");
	/* go through loop to search for environemental variable*/
	for (temp = envp, count = 0; temp != NULL; temp = temp->next)
	{
		if (_strstr(temp->value, name) != NULL)
		{
			remove_env(&envp, count);
			break;
		}
		count++;
	}
	return (0);
}
/**
 * hsh_unsetenv_help - builtin help printout for unsetenv
 */
int hsh_unsetenv_help(void)
{
	write(STDOUT_FILENO,
	"unsetenv usage: unsetenv VARIABLE:\n    Remove an envirornment variable.\n",
	72);
	return (0);
}
