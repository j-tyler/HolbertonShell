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
	int i, num;
	char *name, *overwrite;
	env_t *temp;

	if (arg_list[1] == NULL || strlen(arg_list[1]) == 0 ||
	    strstr(arg_list[1], "=") != NULL)
		exit(1);
	name = safe_malloc(strlen(arg_list[1]) + strlen(arg_list[2] + 1));
	memset(name, 0, strlen(arg_list[1]) + strlen(arg_list[2] + 1));
	strcpy(name, arg_list[1]);
	strncat(name, "=\0", 2);
	overwrite = arg_list[3];
	num = (overwrite == NULL ? 0 : atoi(overwrite));
	temp = envp;
	while (temp != NULL)
	{
		if(strstr(temp->value, name) != NULL && overwrite != 0)
		{
			temp->value = strcat(name, arg_list[2]);
			exit(1);
		}
		else if (strstr(temp->value, name) != NULL && overwrite == 0)
			exit (1);
		temp = temp->next;
	}
	strcat(name, arg_list[2]);
	strncat(name, "\0", 1);
	add_env(&envp, name);
	print_env(envp);
	printf("something is wrong when i try to return \n");
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
