#include "shell.h"

/**
 * history_wrapper - determines what to do for history
 */

void history_wrapper(char *cmd, env_t *envp, char mode)
{
	char **arg;

	arg = safe_malloc(sizeof(char *) * 2);
	if (mode == 'c')
		hsh_history(NULL, envp, 0);
	else if (mode == 'a')
	{
		arg[0] = malloc(sizeof(char) * (_strlen(cmd) + 1));
		memset(arg[0], '\0', (_strlen(cmd) + 1));
		memcpy(arg[0], cmd, _strlen(cmd));
		hsh_history(arg, envp, 1);
	}
	else if (mode == 'w')
		hsh_history(arg, envp, 2);
}
