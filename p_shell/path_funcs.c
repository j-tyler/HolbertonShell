#include "shell.h"

/**
 * get_path - copies the $PATH into the string path
 * @path: string to copy the $PATH into
 */

void get_path(char *path, env_t *list)
{
	int i;
	env_t *temp;

	temp = list;
	for (i = 0; temp->next != NULL; temp = temp->next)
	{
		if (strstr(temp->value, "PATH") != NULL)
			strcpy(path, temp->value);
	}
}

/**
 * tokenize_path - creates an array of strings, each string is a directory
 * in the $PATH variable
 * @search_path: array of strings that contains a searchable path for each
 * string space.
 * @path: the string containing $PATH
 * Description: This also mallocs search_path with how many directories are
 * found in path.
 */

char  **tokenize_path(char **search_path, char *path)
{
	int i, count, b_index, s_index;
	char *temp;
	char buffer[BUFSIZE];

	memset(buffer, '\0', BUFSIZE);
	for (i = 0, count = 1; path[i] != '\0'; i++)
	{
		if (path[i] == ':')
			count++;
	}
	count++;
	search_path = safe_malloc(sizeof(char *) * count);
/*	printf("Debug: check if malloc failed\n");/*
	/* skip the PATH= */
	for (temp = path; *temp != '='; temp++);
	temp++;
	for (s_index = 0; *temp; temp++)
	{
		if (*temp == ':')
		{
			strncat(buffer, "/", 1);
			search_path[s_index] = safe_malloc(sizeof(char) * (strlen(buffer) + 6));
			memset(search_path[s_index], 0, (strlen(buffer) + 6));
			/*printf("Debug: check if malloc failed"); */
			strncat(search_path[s_index], buffer, strlen(buffer));
			s_index++;
			memset(buffer, '\0', BUFSIZE);
		}
		else
			strncat(buffer, temp, 1);
	}
	strncat(buffer, "/", 1);
	search_path[s_index] = safe_malloc(sizeof(char) * (strlen(buffer) + 6));
	memset(search_path[s_index], 0, (strlen(buffer) + 6));
	strncat(search_path[s_index], buffer, strlen(buffer));
	s_index++;
	search_path[s_index] = malloc(sizeof(char *));
	search_path[s_index] = NULL;
	return (search_path);
}

/**
 * create_path - checks whether or not the command exist or not
 * @cmd: command given by user, need to append to end of path strings
 * @search_path: array of path strings to check for existance of command
 * Description: Checks whether or not a command exist by trying to open commands
 * in the different path directories.
 * Return: 0 if found and -1 if not;
 */

int create_path(char *cmd, char **search_path)
{
	int i, fd;

	for (i = 0; search_path[i] != NULL; i++)
	{
		strncat(search_path[i], cmd, strlen(cmd));
		fd = open(search_path[i], O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			strcpy(cmd, search_path[i]);
/*			strncat(cmd, "\0", 1); */
			return (0);
		}
	}
	write(0, "Error: command not found\n", 25);
	return (-1);
}
