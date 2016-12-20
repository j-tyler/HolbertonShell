#include "shell.h"

/**
 * create_history - creates a linked list for user command history, size is 4096
 * @envp: environmental variable linked list
 * Return: a pointer to the history linked list
 */

void create_history(hist_t *history, env_t *envp)
{

	hist_t *new_node;
	char *str, *buf;
	int i, j, count, n;

	/* create a buf of what is in the file */
	buf = safe_malloc(sizeof(char) * BUFSIZE);
	_memset(buf, '\0', BUFSIZE);
	n = read_file(envp, &buf);
	if (n > 0)
	{
		str = safe_malloc(sizeof(char) * _strlen(buf));
		_memset(str, '\0', _strlen(buf));
		if (*buf == '\0')
		{
			add_history(history, "");
		}
		/* create linked list and fill in with what is in file*/
		for (i = 0, j = 0, count = 0; buf[i] != '\0'; i++)
		{
			if (buf[i] == '\n')
			{
				add_history(history, str);
				count++, j = 0;
				_memset(str, '\0', _strlen(str));
			}
			else
				str[j++] = buf[i];
		}
	}
}

/**
 * print_history - prints the history
 * @head: the head of the linked list
 */

void print_history(hist_t *head)
{
	char *str;
	while (head != NULL)
	{
		str = _strdup(head->cmd);
		write(0, str, strlen(str));
		write(0, "\n", 1);
		head = head->next;
	}
}


/**
 * add_history - creates another history node to the linked list
 * @head: head of the history linked list
 * @cmd: command to store in list
 * Description: this function will add node to the end of the list
 */

hist_t *add_history(hist_t *head, char *cmd)
{
	hist_t *new_node;
	hist_t *temp;

	new_node = safe_malloc(sizeof(hist_t));
	new_node->cmd = _strdup(cmd);
	new_node->next = NULL;
	if (head == NULL)
		head = new_node;
	else
	{
		temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}

/**
 * read_file - reads the simple_shell_history file and put it in a buffer
 * @envp: environemental variable linked list to get the HOME directory for file
 * @buf: buffer to input what is read
 */

int read_file(env_t *envp, char **buf)
{
	static int b_size = BUFSIZE;
	int offset, n, fd;
	char *path, *new_buf;

	path = safe_malloc(sizeof(char) * BUFSIZE);
	_memset(path, '\0', BUFSIZE);
	path = rm_vname(envp, "HOME", BUFSIZE);
	_strcat(path, "/.simple_shell_history");
	fd = open(path, O_RDWR | 0600);
	if (fd > 0)
	{
		offset = 0;
		while ((n = read(fd, *buf + offset, b_size - offset)) > 0)
		{
			if (n < b_size - offset)
			{
				(*buf)[n + offset] = '\0';
			}
			b_size *= 2;
			new_buf = safe_malloc((b_size) * sizeof(char));
			offset += n;
			memcpy(new_buf, *buf, b_size / 2);
			*buf = new_buf;
		}
		close(fd);
		return (1);
	}
	return (0);
}
/**
 * make_path
 */
void make_path(char **path, char *filename, env_t *envp, int size)
{
     *path = safe_malloc(sizeof(char) * BUFSIZE);
     memset(*path, '\0', BUFSIZE);
     *path = rm_vname(envp, "PWD", BUFSIZE);
	_write(*path);
     strcat(*path, "/");
	strcat(*path, filename);
	_write(*path);
	_write("||||||||||||\n");
}
