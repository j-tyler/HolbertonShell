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
	int flag, len;
	char *name, *value;
	env_t *temp;

	/* What to do if nothing is entered*/
	if (arg_list[1] == NULL || arg_list[2] == NULL)
		return (2);
	if (!(is_alpha(arg_list[1][0])))
		return (2);
	/* set up all strings up*/
	len = _strlen(arg_list[1]);
	name = safe_malloc(sizeof(char) * (len + 2));
	_memcpy(name, arg_list[1], len + 1);
	_strncat(name, "=", 1);
	if (arg_list[2] != NULL)
	{
		len = _strlen(arg_list[2]);
		value = safe_malloc(sizeof(char) * (len + 1));
		_memcpy(value, arg_list[2], len + 1);
	}
	else
	{
		value = safe_malloc(sizeof(char) * 2);
		value[0] = ' ';
	}
	for (temp = envp, flag = 0; temp != NULL; temp = temp->next)
	{
		if (_str_match_tonull(temp->value, name) != 0)
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
