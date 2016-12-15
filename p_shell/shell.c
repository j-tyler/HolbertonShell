#include "shell.h"

int main(int argc, char **argv, char **envp)
{
	char *buff, *cmd, *path;
	char **arg_list, **search_path;
	env_t *env_p;
	int j;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	cmd = safe_malloc(sizeof(char) * BUFSIZE);
	path = safe_malloc(sizeof(char) * BUFSIZE);
	buff = NULL;
	search_path = NULL;
	arg_list = NULL;
	while (1)
	{
		print_cmdline();
		buff = _getline(buff);
		strncat(buff, "\0", 1);
		tokenize_buf(buff, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		run_builtin(arg_list); /* need to pass more args than this! */
		strcpy(cmd, arg_list[0]);
		if (strchr(cmd, '/') != NULL)
			execute_func(cmd, arg_list);
		else
		{
			get_path(path, env_p);
			search_path = tokenize_path(search_path, path);
			if (create_path(cmd, search_path) == 0)
			{
				execute_func(cmd, arg_list);
			}
		}
		memset(buff, '\0', 100);
		free_args(arg_list);
	}
/*	printf("%s\n", buff);*/
	return (0);
}
void execute_func(char *cmd, char **args)
{
	int status, i;

	if (fork() == 0)
	{
		i = execve(cmd, args, NULL);
		if (i < 0)
		{
			write (0, "Error: command not found\n", 25);
			exit(1);
		}
	}
	else
		wait(&status);
}

void free_args(char **arg_list)
{
	int i;

	for (i = 0; arg_list[i] != '\0'; i++)
	{
		memset(arg_list[i], '\0', strlen(arg_list[i]));
		arg_list[i] = NULL;
		_free(arg_list[i]);
	}
}
