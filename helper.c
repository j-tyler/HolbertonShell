#include "shell.h"

/**
 * print_cmdline - prints the command line or PS1
 */

void print_cmdline()
{
	char *str;

	str = "(^.^) ";
	write(0, str, _strlen(str));
}

/**
 * safe_malloc - allocates memory and handles errors
 * @size: size of space to allocate
 *
 * Return: pointer to new space
 */
void *safe_malloc(size_t size)
{
	void *tmp;

	tmp = malloc(size);
	if (tmp == NULL)
	{
		write(STDOUT_FILENO, "Out of Memory (._.)\n", 20);
		/* ADD: Exit! */	
	}
	defer_free(tmp);
	return (tmp);
}

/**
 * rm_vname - removes varaiable name of an environemental variable
 * @env: the environemental varaible name and value string
 * Return: a string containing the path
 */

char *rm_vname(env_t *envp, char *name, int buf_size)
{
	char *pwd;
	env_t *temp;
	int i;

	pwd = safe_malloc(sizeof(char) * buf_size);
	memset(pwd, '\0', buf_size);
	temp = envp;
	for (i = 0; temp->next != NULL; temp = temp->next)
	{
		if (_str_match(temp->value, name))
			strcpy(pwd, temp->value);
	}
	while (*pwd != '=')
		pwd++;
	pwd++;
	return(pwd);
}
