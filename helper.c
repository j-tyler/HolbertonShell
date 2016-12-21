#include "shell.h"

/**
 * print_cmdline - prints the command line or PS1
 */

void print_cmdline(void)
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
 * @envp: the environemental varaible name and value string
 * @name: the variable name to search for
 * @buf_size: the size of the path
 * Return: a string containing the path
 */

char *rm_vname(env_t *envp, char *name, int buf_size)
{
	char *pwd;
	env_t *temp;

	pwd = safe_malloc(sizeof(char) * buf_size);
	_memset(pwd, '\0', buf_size);
	temp = envp;
	for (; ; temp = temp->next)
	{
		if (_str_match(temp->value, name))
		{
			_strcpy(pwd, temp->value);
			break;
		}
		else if (temp->next == NULL)
		{
			_free(pwd);
			return (NULL);
		}
	}
	while (*pwd != '=')
		pwd++;
	pwd++;
	return (pwd);
}
