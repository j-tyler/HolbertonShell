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
