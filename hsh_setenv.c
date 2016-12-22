#include "shell.h"
/**
 * hsh_setenv - builtin command hsh_setenv, mimics builtin setenv
 * @arg_list: list of arguements that contain the env name, value and
 * overwrite value
 * @envp: a pointer to the linked list of environmental variables
 * @buf_size: buf size to set malloc space
 * Return: 0 on success and 1 on error
 */
int hsh_setenv(char **arg_list, env_t *envp, int buf_size)
{
	int flag;
	char *name, *value;
	env_t *temp;

	/* What to do if nothing is entered*/
	if (arg_list[1] == NULL && arg_list[2] == NULL)
	{
		_write("Error: wrong number of arguments\n");
		return (2);
	}
	if (!(is_alpha(arg_list[1][0])))
	{
		_write("setenv: variable name must begin with a letter\n");
		return (2);
	}
	/* set up all strings up*/
	name = safe_malloc(sizeof(char) * buf_size), _memset(name, 0, buf_size);
	_memcpy(name, arg_list[1], _strlen(arg_list[1]));
	value = safe_malloc(sizeof(char) * buf_size), _memset(value, 0, buf_size);
	if (arg_list[2] != NULL)
		_memcpy(value, arg_list[2], _strlen(arg_list[2]));
	else
		value[0] = ' ';
	_strcat(name, "=");
	for (temp = envp, flag = 0; temp != NULL; temp = temp->next)
	{
		if (_strstr(temp->value, name) != NULL)
		{
			_strcat(name, value);
			temp->value = name;
			flag = 1;
		}
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
 * Return: Always 0
 */
int hsh_setenv_help(void)
{
	_write("setenv usage: setenv VARIABLE VALUE\n    Initialize a new");
	_write(" environment variable, or modify an existing one.\n");
	return (0);
}
