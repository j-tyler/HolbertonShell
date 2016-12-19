#include "shell.h"
/**
 * hsh_setenv - builtin command hsh_setenv, mimics builtin setenv
 * @arg_list: list of arguements that contain the env name, value and
 * overwrite value
 * @envp: a pointer to the linked list of environmental variables
 * Return: WHO KNOWS. 0 on success and -1 on error
 */
int hsh_setenv(char **arg_list, env_t *envp, int buf_size)
{
	int flag;
	char *name, *value;
	env_t *temp;

	/* What to do if nothing is entered*/
	if (arg_list[1] == NULL || arg_list[2] == NULL)
	{
		write(0, "Error: wrong number of arguments\n", 37);
		return (0);
	}
	/* set up all strings up*/
	name = safe_malloc(sizeof(char) * buf_size);
	_memset(name, 0, buf_size);
	_memcpy(name, arg_list[1], strlen(arg_list[1]));
	value = safe_malloc(sizeof(char) * buf_size);
	_memset(value, 0, buf_size);
	_memcpy(value, arg_list[2], strlen(arg_list[2]));
	_strcat(name, "=");
	temp = envp;
	flag = 0;
	while (temp != NULL)
	{
		if (_strstr(temp->value, name) != NULL)
		{
			_strcat(name, value);
			temp->value = name;
			flag = 1;
		}
		temp = temp->next;
	}
	if (flag == 0)
	{
		_strcat(name, value);
		add_env(&envp, name);
	}
	return (0);
}
/**
 * hsh_setenv_help - builtin help printout for setenv
 */
int hsh_setenv_help(void)
{
	write(STDOUT_FILENO,
	"setenv usage: setenv VARIABLE VALUE\n    Initialize a new", 56);
	write(STDOUT_FILENO,
	" environment variable, or modify an existing one.\n", 50);
	return (0);
}
