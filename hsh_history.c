#include "shell.h"
/**
 * hsh_history - builtin command hsh_history, mimics builtin history
 * @??:
 * Return: Always 0
 */
int hsh_history(char **arg_list, env_t *envp, int size, hist_t *history)
{
	int i;
	char *num_str;
	hist_t *temp;

	for (i = 0, temp = history; temp != NULL; temp = temp->next, i++)
	{
		num_str = _itoa(i);
		_write(" ");
		_write(num_str);
		_write(" ");
		_write(temp->cmd);
		_write("\n");
	}
	return (0);
}
/**
 * hsh_history_help - builtin help printout for history
 * Return: Always 0
 */
int hsh_history_help(void)
{
	_write("history usage: history\n    ");
	_write("Display the history list with line numbers.\n");
	return (0);
}

/**
 * _itoa - interger to string converter
 * @num: number to convert
 * Return: a string for the number
 */

char *_itoa(int num)
{
	char *num_str;
	int index, exp, temp_exp;

	num_str = safe_malloc(sizeof(char) * BUFSIZE);
	_memset(num_str, '\0', BUFSIZE);
	exp = 1000000000;
	index = 0;
	if (num != 0)
	{
		while ((num / exp) == 0)
			exp /= 10;
		temp_exp = exp;
		while(temp_exp < 1000)
		{
			num_str[index++] = 0 + '0';
			temp_exp *= 10;
		}
		while (exp >= 1)
		{
			num_str[index++] = (num / exp) + '0';
			num %= exp;
			exp /= 10;
		}
	}
	else
		num_str[index] = 0 + '0';
	return (num_str);
}
