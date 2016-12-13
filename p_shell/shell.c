#include "shell.h"

int main(int argc, char **argv, char **envp)
{
	char *buff;
	char **arg_list;
	int j;
	(void)argv, (void)envp, (void)argc;

	buff = malloc(sizeof(char) * BUFSIZE);
	if (buff == NULL)
		return (0);
	memset(buff, '\0', BUFSIZE);
	arg_list = NULL;
	printf("size of buff is %d\n", BUFSIZE);
	print_cmdline();
	while (1)
	{
		read(0, buff, 100);
		tokenize_buf(buff, &arg_list);
		for(j = 0; arg_list[j] != '\0'; j++)
			printf("%s\n", arg_list[j]);
		memset(buff, '\0', 100);
		free_args(arg_list);
		print_cmdline();
	}
	printf("%s\n", buff);
	return (0);
}

void tok_list(char *buffer, char **arg_list)
{

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
                                arg_list[i] = malloc(sizeof(char) * strlen(str)+ 1);
			strncpy(arg_list[i], str, strlen(str));
			strncat(arg_list[i], "\0", 1);
			memset(str, 0, strlen(buffer));
			j = 0;
			i++;
		}
		else
		{
			str[j++] = *temp;
		}
		temp++;
	}
	if (str[0] != 0)
	{
		arg_list[i] = malloc(sizeof(char) * strlen(str) + 1);
		strncpy(arg_list[i], str, strlen(str));
		strncat(arg_list[i], "\0", 1);
	}
}

void free_args(char **arg_list)
{
	int i;

	for (i = 0; arg_list[i] != '\0'; i++)
	{
		memset(arg_list[i], '\0', strlen(arg_list[i]));
		arg_list[i] = NULL;
		free(arg_list[i]);
	}
}
