#include "shell.h"

void run_execute(char **arg_list, env_t *env_p)
{
	char *cmd, *path;
	char **search_path;

	search_path = NULL;
	cmd = safe_malloc(sizeof(char) * BUFSIZE);
	path = safe_malloc(sizeof(char) * BUFSIZE);
	strcpy(cmd, arg_list[0]);
	if (strchr(cmd, '/') != NULL)
		execute_func(cmd, arg_list);
	else
	{
		get_path(path, env_p);
		search_path = tokenize_path(search_path, path);
		if (create_path(cmd, search_path) == 0)
			execute_func(cmd, arg_list);
	}
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
