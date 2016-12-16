#include "shell.h"
/**
 * main - Holberton Shell
 */
int main(int argc, char **argv, char **envp)
{
	buffer buf;
	char **arg_list;
	env_t *env_p;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	buf.size = BUFSIZE, buf.bp = 0;
	buf.buf = safe_malloc(sizeof(char) * buf.size);
	arg_list = NULL;
	while (1)
	{
		print_cmdline();
		_getline(&buf);
		tokenize_buf(&buf, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		if (run_builtin(arg_list, env_p, buf.size) != 0)
			run_execute(arg_list, env_p, buf.size);
	}
	return (0);
}
