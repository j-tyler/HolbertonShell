#include "shell.h"

/**
 * _getline - a function that grabs stdin and puts in buffer and returns
 * string.
 *
 */

char * _getline()
{
	int i, n, size, b_size;
	char *buff, *buff_p;
	char *new_buff;

	b_size = 1024;
	buff = safe_malloc(sizeof(char) * b_size);
	memset(buff, 0, b_size);
	buff_p = buff;
	while ((n = read(0, buff, b_size)) > 0)
	{
		size = strlen(buff_p);
		new_buff = safe_malloc((b_size + size) * sizeof(char));
		memcpy(new_buff, buff, b_size);
		buff = new_buff;
		b_size += size;
		for (i = 0; buff[i] != '\0'; i++)
		{
			return (new_buff);
		}
	}
	if (n ==  0)
	{
		printf("Debug: Exit 1\n");
		exit(1);
	}
	return (NULL);
}
