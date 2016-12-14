#include "shell.h"

/**
 * get_path - copies the $PATH into the string path
 * @path: string to copy the $PATH into
 */

void get_path(char *path)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strstr(environ[i], "PATH") != NULL)
			strcpy(path, environ[i]);
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
	search_path = malloc(sizeof(char *) * (count + 1));
	printf("Debug: check if malloc failed\n");

	/* skip the PATH= */
	temp = path;
	while (*temp != '=')
		temp++;
	temp++;
	for (s_index = 0; *temp; temp++)
	{
		if (*temp == ':')
		{
			strncat(buffer, "/", 1);
			search_path[s_index] = (char *)malloc(sizeof(char) * (strlen(buffer) + 2));
			/*printf("Debug: check if malloc failed"); */
			strncat(search_path[s_index], buffer, strlen(buffer));
			strncat(search_path[s_index], "\0", 1);
			s_index++;
			memset(buffer, '\0', BUFSIZE);
		}
		else
			strncat(buffer, temp, 1);
	}
	s_index++;
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
			return (0);
		}
	}
	write(0, "Error: command not found\n", 25);
	return (-1);
}
