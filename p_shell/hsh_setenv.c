#include "shell.h"
/**
 * hsh_setenv - builtin command hsh_setenv, mimics builtin setenv
 * @arg_list: list of arguements that contain the env name, value and
 * overwrite value
 * @envp: a pointer to the linked list of environmental variables
 * Return: WHO KNOWS. 0 on success and -1 on error
 */
void hsh_setenv(char **arg_list, env_t *envp)
{
	int flag;
	char *name, *value;
	env_t *temp;

	if (arg_list[1] == NULL || arg_list[2] == NULL)
		exit (1);
	/* set up all strings up*/
	name = safe_malloc(sizeof(char) * (strlen(arg_list[1]) + strlen(arg_list[2]) + 2));
	memset(name, 0, (strlen(arg_list[1]) + strlen(arg_list[2]) + 2));
	memcpy(name, arg_list[1], strlen(arg_list[1]));
	value = safe_malloc(sizeof(char) * (strlen(arg_list[2]) + 1));
	memset(value, 0, strlen(arg_list[2]) + 1);
	memcpy(value, arg_list[2], strlen(arg_list[2]));
	strcat(name, "=");
	temp = envp;
	flag = 0;
	while (temp != NULL)
	{
		if (strstr(temp->value, name) != NULL)
		{
			strcat(name, value);
			temp->value = name;
			flag = 1;
		}
		temp = temp->next;
	}
	if (flag == 0)
	{
		strcat(name, value);
		add_env(&envp, name);
	}
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
