#include "shell.h"
/**
 * hsh_history - builtin command hsh_history, mimics builtin history
 * @??:
 */
void hsh_history(char **arg_list, env_t *envp, int size, hist_t *history)
{
	int i;
	char *num_str;
	hist_t *temp;

	for (i = 0, temp = history; temp != NULL; temp = temp->next, i++)
	{
		num_str = _itoa(i);
		write(0, " ", 1);
		write(0, num_str, _strlen(num_str));
		write(0, " ", 1);
		write(0, temp->cmd, _strlen(temp->cmd));
		write(0, "\n", 1);
	}
}
/**
 * hsh_history_help - builtin help printout for history
 */
void hsh_history_help(void)
{
	write(STDOUT_FILENO,
	"history usage: history\n    Display the history list with line numbers.\n", 71);
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

	num_str = malloc(sizeof(char) * BUFSIZE);
	memset(num_str, '\0', BUFSIZE);
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
