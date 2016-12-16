#include "shell.h"
/**
 * tokenize_buf - tokenize buffer by inputting NULLs and filling **av
 * @buf: The buffer with the command string
 * @av: Command argument vector
 * Description: This function accepts a string such as 'ls -l' and changes 
 *              it to 'ls\0-l'. It puts pointers to 'ls' and '-l' into *av
 */
void tokenize_buf(buffer *buf, char ***av)
{
	int i, avp, flag, whitespace;

	_av_init(buf->buf + buf->bp, av);

	/* Build the argument vector from the given buffer */
	for (i = buf->bp, avp = 0, flag = 1; !_is_endofcmd(buf->buf[i]); i++)
	{
		whitespace = _is_whitespace(buf->buf[i]);
		if (flag && !whitespace)
		{
			(*av)[avp++] = buf->buf + i;
			flag = 0;
		}
		if (whitespace)
		{
			buf->buf[i] = '\0';
			flag = 1;
		}
	}
	(*av)[avp] = NULL;

	/* If the reason we ended was because of flow control commands, */
	/* increment the buffer point and add a null before the character */
	if (buf->buf[i] == ';' || buf->buf[i] == '|' || buf->buf[i] == '&')
	{
		buf->bp += i - buf->bp;
		_add_null(buf->buf + buf->bp);
		buf->bp++;
	}
	else
		buf->bp = 0;
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

	for (c = 0, flag = 1; !_is_endofcmd(*buf); buf++)
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
 * _add_null - Add a null before the multi-command operator
 * @buf: buffer structure to add null into
 */
void _add_null(char *buf)
{ 
	int i;

	/* DEBUG: overwrites by one when buffer is completely full */

	for (i = 0; buf[i] != '\0'; i++)
		;
	i++;
	for ( ; i > 0; i--)
		buf[i + 1] = buf[i];
	buf[i + 1] = buf[i];
	buf[i] = '\0';
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
/**
 * _is_endofcmd - Boolean true or false if char signals end of command
 * @c: char to evaluate
 *
 * Return: 1 if end of command, 0 if not
 */
int _is_endofcmd(char c)
{
	if (c == '\0' || c == '|' || c == '&' || c == ';' || c == '#')
		return (1);
	return (0);
}
