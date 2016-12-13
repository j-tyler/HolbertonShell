#include "shell.h"

static char *arg_list[100];

int main(int argc, char **argv, char **envp)
{
	char c;
	char *buff;
	char *command;
	int i, j, bp;
	(void)argv, (void)envp, (void)argc;

	c = '\0';
	i = 0, bp = 0;
	buff = malloc(sizeof(char) * 100);
	if (buff == NULL)
		return (0);
	memset(buff, 0, 100);
	command = malloc(sizeof(char) * 100);
	if (command == NULL)
		return (0);
	/* shell loop */
	print_cmdline();

	while (bp < 5)
	{
		read(0, buff, 100);
		bp++;

		if (bp == 10)
		{
			if (buff[0] == 0)
				print_cmdline();
			else
			{
				buff[i] = '\0';
				tok_list(buff);
				strcpy(command, arg_list[0]);
			}
			for(j = 0; arg_list[j] != '\0'; j++)
				printf("%s\n", arg_list[j]);
			i = 0;
			memset(buff, '\0', 100);
			free_args();
			print_cmdline();
		}
		/*else */
			/*buff[i++] = c;*/
	}
	printf("%s\n", buff);
	return (0);
}

char **tok_list(char *buffer)
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

void free_args()
{
	int i;

	for (i = 0; arg_list[i] != '\0'; i++)
	{
		memset(arg_list[i], '\0', strlen(arg_list[i]));
		arg_list[i] = NULL;
		free(arg_list[i]);
	}
}
