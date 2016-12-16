#include "shell.h"
/**
 * main - Holberton Shell
 */
int main(int argc, char **argv, char **envp)
{
	buffer buf;
	char **arg_list;
	env_t *env_p;
	int return_value;
	(void)argv, (void)envp, (void)argc;

	env_p = create_envlist();
	buf.size = BUFSIZE, buf.bp = return_value = 0;
	buf.buf = safe_malloc(sizeof(char) * buf.size);
	arg_list = NULL;
	while (1)
	{
		if (!check_cmd(&buf, return_value)) /* need to read return_value from builtin and execute */
		{
			print_cmdline();
			_getline(&buf);
		}
		tokenize_buf(&buf, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		if (run_builtin(arg_list, env_p, buf.size) != 0)
			run_execute(arg_list, env_p, buf.size);
	}
	return (0);
}
/**
 * check_cmd - check the command line for the next command
 * @buf: buffer structure
 * @return_value: Return value from last command
 *
 * Return: 1 if we have more commands to execute, 0 if we don't
 */
int check_cmd(buffer *buf, int return_value)
{
	int i;
	// if buf->bp == 0, return 0
	// if buf->buf[buf->bp] == ';', trim off; and return 1
	// if buf->buf[buf->bp] == '&' && return_value == 0,
	//	trim off & and return 1
 	// if buf->buf[buf->bp] == '|' && return_value != 0,
	//   trim off | and return 1

	// seach for | or ;, trim and return 1,
	// else return 0;
	if (buf->bp == 0)
		return (0);
	while (buf->buf[buf->bp] != '\0')
	{
		if (buf->buf[buf->bp] == ';')
		{
			trim_cmd(buf);
			return (1);
		}
		if (buf->buf[buf->bp] == '&' && return_value == 0)
		{
			trim_cmd(buf);
			return (1);
		}
		if (buf->buf[buf->bp] == '|' && return_value != 0)
		{
			trim_cmd(buf);
			return (1);
		}
		buf->bp++;
	}
	buf->bp = 0;
	return (0);
}
/**
 * trim_cmd - move past cmd point at given buffer position
 * @buf: buffer structure
 */
void trim_cmd(buffer *buf)
{
	while (buf->buf[buf->bp] == ';')
		buf->bp++;
	while (buf->buf[buf->bp] == '|')
		buf->bp++;
	while (buf->buf[buf->bp] == '&')
		buf->bp++;
}
