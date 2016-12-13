#include "shell.h"

void print_cmdline()
{
	char *str;

	str = "(^.^) ";
	write(0, str, _strlen(str));
}


/**
 * _strlen - returns length of string
 * @s: character of string
 * Return: length of string
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
	{
	}
	return (i);
}
