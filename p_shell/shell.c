#include "shell.h"

int main(int argc, char **argv, char **envp)
{
	char *buff;
	char **arg_list;
	env_t *env_p;
	int j;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	buff = NULL;
	arg_list = NULL;
	while (1)
	{
		print_cmdline();
		buff = _getline(buff);
		strncat(buff, "\0", 1);
		tokenize_buf(buff, &arg_list);
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
		memset(buff, '\0', 100);
	}
/*	printf("%s\n", buff);*/
	return (0);
}
