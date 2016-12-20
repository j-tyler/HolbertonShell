#include "shell.h"

/**
 * add_cmdhist - add new command to the history linked list
 * @history: history linked list
 * @cmd: command to put into the history
 * Description: Adds the new command to the end of the linked
 * list, keeps count on how many entries there are in the list,
 * if the list execeeds, 4096, then the head will pop off
 */

void add_cmdhist(hist_t *history, char *cmd)
{
	static int hist_index = 0;
	int i;
	hist_t *temp;
	char *new_cmd;

	new_cmd = safe_malloc(sizeof(char) * _strlen(cmd));
	memset(new_cmd, '\0', _strlen(cmd));
	temp = history;
	if (hist_index == 0)
	{
		for (temp = history; temp != NULL; temp = temp->next)
			hist_index++;
	}
	for (i = 0; i < (_strlen(cmd) - 1); i++)
		new_cmd[i] = cmd[i];
	if (_strlen(cmd) > 1)
		add_history(history, new_cmd);
	hist_index++;
	_free(new_cmd);
}
/**
 * write_history - writing the history linked list to the file: .simple_shell_history
 * @envp: environemental variable linked list to find the path of file
 * @history: history link list to find what to write in
 */

void write_history(env_t *envp, hist_t *history)
{
	hist_t *temp;
	char *path;
	int n, fd;

	history = history->next;
	path = safe_malloc(sizeof(char) * BUFSIZE);
	memset(path, '\0', BUFSIZE);
	path = rm_vname(envp, "HOME", BUFSIZE);
	_strcat(path, "/.simple_shell_history");
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	for (temp = history; temp != NULL; temp = temp->next)
	{
		write(fd, temp->cmd, _strlen(temp->cmd));
		write(fd, "\n", 1);
	}
	_free(history);
	close(fd);
}
