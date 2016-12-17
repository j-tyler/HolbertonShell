#include "shell.h"
/**
 * main - Holberton Shell
 */
int main(int argc, char **argv, char **envp)
{
	buffer b;
	char **arg_list;
	env_t *env_p;
	int return_value;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	b.size = BUFSIZE, b.bp = return_value = 0;
	b.buf = safe_malloc(sizeof(char) * b.size);
	arg_list = NULL;
	while (1)
	{
		if (!more_cmds(&b, return_value)) /* need to read return_value from builtin and execute */
		{
			print_cmdline();
			_getline(&b);
		}
		test_alias(&b);
		tokenize_buf(&b, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		if (run_builtin(arg_list, env_p, b.size) != 0)
			run_execute(arg_list, env_p, b.size);
	}
	return (0);
}
/**
 * more_cmds - check the command line for the next command
 * @buf: buffer structure
 * @return_value: Return value from last command
 *
 * Return: 1 if we have more commands to execute, 0 if we don't
 */
int more_cmds(buffer *b, int return_value)
{
	int i;
	// if buf->bp == 0, return 0
	// if buf->buf[buf->bp] == ';', trim off; and return 1
	// if buf->buf[buf->bp] == '&' && return_value == 0,
	//	trim off & and return 1
 	// if buf->buf[buf->bp] == '|' && return_value != 0,
	//   trim off | and return 1

	// else return 0;
	if (b->bp == 0)
		return (0);
	while (b->buf[b->bp] != '\0')
	{
		if (b->buf[b->bp] == ';')
		{
			trim_cmd(b);
			return (1);
		}
		if (b->buf[b->bp] == '&' && return_value == 0)
		{
			trim_cmd(b);
			return (1);
		}
		if (b->buf[b->bp] == '|' && return_value != 0)
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
 * @buf: buffer structure
 */
void trim_cmd(buffer *b)
{
	while (b->buf[b->bp] == ';')
		b->bp++;
	while (b->buf[b->bp] == '|')
		b->bp++;
	while (b->buf[b->bp] == '&')
		b->bp++;
}
