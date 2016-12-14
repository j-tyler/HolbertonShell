/**
 * run_builtin - frame for checking command vs builtins and executing found cmd.
 * @??:
 *
 * Return: 0 on found builtin, 1 on found nothing
 */
int run_builtin(int x)
{
	int i, size;
	builtin table[] = {
	{"exit", hsh_exit},     {"env", hsh_env},
	{"setenv", hsh_setenv}, {"unsetenv", hsh_unsetenv},
	{"cd", hsh_cd},         {"history", hsh_history}
	};

	size = sizeof(table)/sizeof(table[0]);
	for (i = 0; i < size; i++)
		if (_str_match(/*arg0*/, table[i].name))
		{
			table[i].func(/*arguments + pointer structure? ? */i);
			return (0);
		}
	return (1);
}
