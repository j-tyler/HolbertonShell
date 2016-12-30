#include "shell.h"
/**
 * _str_match - See if two strings are matching
 * @s1: string 1
 * @s2: string 2
 * Description: Returns a match if either string reaches \0 or space
 *
 * Return: 1 if match, 0 if not match
 */
int _str_match(char *s1, char *s2)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return (1);
		if (_is_whitespace(s1[i]) || _is_whitespace(s2[i]))
			return (1);
	}
	if (s1[i] == '\0' || s2[i] == '\0')
		return (1);
	if (_is_whitespace(s1[i]) || _is_whitespace(s2[i]))
		return (1);
	return (0);
}
