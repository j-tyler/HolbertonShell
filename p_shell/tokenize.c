#include "shell.h"
/**
 * tokenize_buf - tokenize buffer by inputting NULLs and filling **av
 * @buf: The buffer with the command string
 * @av: Command argument vector
 * Description: This function accepts a string such as 'ls -l' and changes 
 *              it to 'ls\0-l'. It puts pointers to 'ls' and '-l' into *av
 */
void tokenize_buf(char *buf, char ***av)
{
	int avp, flag, whitespace;

	printf("buff is %s\n", buf);
	_av_init(buf, av);

	for (avp = 0, flag = 1; *buf; buf++)
	{
		whitespace = _is_whitespace(*buf);
		if (flag && !whitespace)
		{
			(*av)[avp++] = buf;
			flag = 0;
		}
		if (whitespace)
		{
			*buf = '\0';
			flag = 1;
		}
	}
	printf("AVP is %d\n", avp);
	(*av)[avp] = NULL;
	/* Command debugging */
	for (avp = 0; (*av)[avp] != NULL; avp++)
		printf("Command %d is %s\n", avp, (*av)[avp]);
}
/**
 * _av_init - resize av if needed
 * @buf: The buffer with the command string
 * @av: Command argument vector
 */
void _av_init(char *buf, char ***av)
{
	int c, flag, whitespace;

	for (c = 0, flag = 1; *buf; buf++)
	{
		whitespace = _is_whitespace(*buf);
		if (flag && !whitespace)
			flag = 0, c++;
		else if (whitespace)
			flag = 1;
	}

	/* ADD: Do not reallocate if array is big enough ! */

	if (*av != NULL)
		_free(*av);
	*av = safe_malloc(sizeof(char *) * (c + 1));
}
/**
 * _is_whitespace - Boolean true for false for whitespace
 * @c: char to evalute.
 *
 * Return: 1 if whitespace, 0 if not
 */
int _is_whitespace(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}
