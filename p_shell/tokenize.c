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
	int i, avp, flag;

	_av_init(buf, av);

	flag = 1;
	for (i = 0, avp = 0; buf[i] != '\0'; i++)
	{
		if (flag && buf[i] != ' ')
		{
			*av[avp++] = (buf + i);
			flag = 0;
		}
		if (buf[i] == ' ')
		{
			buf[i] = '\0';
			flag = 1;
		}
	}
	*av[avp] = NULL;
}
/**
 * _av_init - resize av if needed
 * @buf: The buffer with the command string
 * @av: Command argument vector
 */
void _av_init(char *buf, char ***av)
{
	int i, c, flag;

	c = 0, flag = 1;
	for (i = 0; buf[i] != '\0'; i++)
	{
		if (flag && buf[i] != ' ')
			flag = 0, c++;
		if (buf[i] == ' ')
			flag = 1;
	}
	if (*av != NULL)
		for (i = 0; *av[i] != NULL; i++)
			;			
	else
		i = 0;

	printf("I see %d tokens\n", c);
	if (c > i)
	{
		if (*av != NULL)
			free(*av);
		*av = malloc(sizeof(char *) * (c + 1));
		printf("DEBUG: Need to give condition for malloc failure\n");
	}
}
