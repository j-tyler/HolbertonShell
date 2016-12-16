#include "shell.h"

/**
 * create_history - creates a linked list for user command history, size is 4096
 */

hist_t *create_history(env_t *envp)
{

	hist_t *head;
	char *path;
	int i, fd;

	path = safe_malloc(sizeof(char) * BUFSIZE);
        memset(path, '\0', BUFSIZE);
	path = rm_vname(envp, "HOME", BUFSIZE);
	strcat(path, ".simple_shell_history");
	if ((fd = open(path, O_CREAT | O_RDWR) >= 0))
	{
		/* read how many new lines */
	}
	head = NULL;
	for (i = 0; i < 4096; i++)
		;
	return (head);
}
