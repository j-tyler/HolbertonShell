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
/**
 * _str_match - See if two strings are matching
 * @s1: string 1
 * @s2: string 2
 *
 * Return: 1 if match, 0 if not match
 */
int _str_match(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0')
			return (1);
	}
	return (0);
}
