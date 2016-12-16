#include "shell.h"
/**
 * main - Holberton Shell
 */
int main(int argc, char **argv, char **envp)
{
	char *buf;
	char **arg_list;
	env_t *env_p;
	hist_t *history;
	int buf_size;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	history = create_history(env_p);
	buf = safe_malloc(sizeof(char) * BUFSIZE);
	arg_list = NULL;
	while (1)
	{
		print_cmdline();
		buf_size = _getline(&buf);
		tokenize_buf(buf, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		if (run_builtin(arg_list, env_p, buf_size) != 0)
			run_execute(arg_list, env_p, buf_size);
	}
	return (0);
}
