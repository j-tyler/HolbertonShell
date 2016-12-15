#include "shell.h"
/**
 * main - Holberton Shell
 */
int main(int argc, char **argv, char **envp)
{
	char *buf, *cmd, *path;
	char **arg_list, **search_path;
	env_t *env_p;
	int j;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	cmd = safe_malloc(sizeof(char) * BUFSIZE);
	path = safe_malloc(sizeof(char) * BUFSIZE);
	buf = NULL; search_path = arg_list = NULL;
	while (1)
	{
		print_cmdline();
		_getline(&buf);
		tokenize_buf(buf, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		if (run_builtin(arg_list, env_p) != 0)
		{
			run_execute(arg_list, env_p);
		}
/**
 *		strcpy(cmd, arg_list[0]);
 *		if(!run_builtin(arg_list, env_p))
 *			continue;
 *		else if (strchr(cmd, '/') != NULL)
 *			execute_func(cmd, arg_list);
 *		else
 *		{
 *			get_path(path, env_p);
 *			search_path = tokenize_path(search_path, path);
 *			if (create_path(cmd, search_path) == 0)
 *			{
 *				execute_func(cmd, arg_list);
 *			}
 *		}
 */
		memset(buf, '\0', 100);
	}
	return (0);
}
