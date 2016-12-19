#include "shell.h"

/**
 * run_ execute - an execution function for the command given
 * @arg_list: argument list of what is inputed by user
 * @env_p: the linked list containing environmental variables
 * @cmd_size: size that cmd should be allocated for
 * Description: Checks if the command given is given the path (i.e /bin/ls)
 * if not, then the function will find the path for the command and if it fails
 * to find the command, an Error: command not found will be printed.
 */

void run_execute(char **arg_list, env_t *env_p, int cmd_size)
{
	char *cmd, *path;
	char **search_path;

	search_path = NULL;
	cmd = safe_malloc(sizeof(char) * cmd_size);
	path = safe_malloc(sizeof(char) * cmd_size);
	strcpy(cmd, arg_list[0]);
	if (strchr(cmd, '/') != NULL)
		execute_func(cmd, arg_list);
	else
	{
		get_path(path, env_p);
		search_path = tokenize_path(search_path, path, cmd_size);
		if (create_path(cmd, search_path) == 0)
			execute_func(cmd, arg_list);
	}
}

/**
 * execute_func - function that runs the execve system call.
 * @cmd: full path to the command
 * @args: the arguement list (if any) given by the user.
 */

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