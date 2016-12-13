#include "shell.h"

char **tok_list(char *buffer)
{
	static char *arg_list[100];
	char *temp, *str;
	int i, j;

	temp = buffer;
	i = j = 0;
	str = malloc(sizeof(char) * strlen(buffer) + 1);
	memset(str, 0, strlen(buffer));
	while (*temp != '\0')
	{
		if (*temp == ' ')
		{
			if (arg_list[i] == NULL)
				arg_list[i] = malloc(sizeof(char) * strlen(str) + 1);
			strncpy(arg_list[i], str, strlen(str));
			strncat(arg_list[i], "\0", 1);
			memset(str, 0, strlen(buffer));
			j = 0;
			i++;
		}
		else
			str[j++] = *temp;
		temp++;
	}
	if (str[0] != 0)
	{
		arg_list[i] = malloc(sizeof(char) * strlen(str) + 1);
		strncpy(arg_list[i], str, strlen(str));
		strncat(arg_list[i], "\0", 1);
	}
	return (arg_list);
}
