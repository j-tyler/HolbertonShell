/**
 * tokenize_buf - tokenize buffer by inputting NULLs and filling **av
 * buf: The buffer with the command string
 * av: Command argument vector
 * Description: This function accepts a string such as 'ls -l' and changes 
 *              it to 'ls\0-l'. It puts pointers to 'ls' and '-l' into *av
 */
void tokenize_buf(char *buf, char **av)
{
	int bp, avp, flag;

	flag = 1;
	for (bp = 0, avp = 0; buf[bp] != '\0'; bp++)
	{
		if (flag && buf[bp] != ' ')
		{
			av[avp++] = (buf + bp);
			flag = 0;
		}
		if (buf[bp] == ' ')
		{
			buf[bp] = '\0';
			flag = 1;
		}
	}
}
