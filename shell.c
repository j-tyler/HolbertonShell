#include "shell.h"
/**
 * main - Holberton Shell
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc, (void)argv, (void)envp;
	char **arg_list;
	env_t *env_p;
	int retrn_value;
	hist_t *history;
	buffer b = {NULL, BUFSIZE, 0};

	b.buf = safe_malloc(sizeof(char) * b.size);
	arg_list = NULL;
	env_p = create_envlist();
	retrn_value = 0;
	history = create_history(env_p);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);

	while (1)
	{
		if (!more_cmds(&b, retrn_value)) /* need to read return_value from builtin and execute */
		{
			print_cmdline();
			_getline(&b);
		}
		history = add_cmdhist(history, b.buf);
		check_alias(&b, env_p);
		tokenize_buf(&b, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		if (run_builtin(arg_list, env_p, b.size, history) != 0)
			run_execute(arg_list, env_p, b.size);

	}
	return (0);
}
/**
 * more_cmds - check the command line for the next command
 * @b: buffer structure
 * @retrn_value: Return value from last command
 * Description: Controls the logic behind if multi-part input has more
 *				commands to execute. Handles ; && and ||.
 *				Will advance buffer to next command.
 *
 * Return: 1 if we have more commands to execute, 0 if we don't
 */
int more_cmds(buffer *b, int retrn_value)
{
	int i;

	printf("help!");
	if (b->bp == 0)
		return (0);

	while (b->buf[b->bp] != '\0')
	{
		printf("stuck in here :(");
		if (b->buf[b->bp] == ';')
		{
			trim_cmd(b);
			return (1);
		}
		if (b->buf[b->bp] == '&' && retrn_value == 0)
		{
			trim_cmd(b);
			return (1);
		}
		if (b->buf[b->bp] == '|' && retrn_value != 0)
		{
			trim_cmd(b);
			return (1);
		}
		b->bp++;
	}
	b->bp = 0;
	return (0);
}
/**
 * trim_cmd - move past cmd flowcontrol point at given buffer position
 * @b: buffer structure
 * Description: Small helper function for function more_cmds. Advances
 *				the buffer point past command control characters.
 */
static void trim_cmd(buffer *b)
{
	while (b->buf[b->bp] == ';')
		b->bp++;
	while (b->buf[b->bp] == '|')
		b->bp++;
	while (b->buf[b->bp] == '&')
		b->bp++;
}
