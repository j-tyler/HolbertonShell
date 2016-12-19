#include "shell.h"

/**
 * update_path - rewrites PWD path to not include sybols
 * @arg_list: arguement list given by the user to determine directory
 * @envp: environemental variable linked list
 * @path: current path to be updated
 * Return: a path without any symbols such as (., .., ~, or -)
 */

char *update_path(char **arg_list, env_t *envp, char *path, int buf_size)
{
	int i, slash_count, flag;
	char *dir, *new_path;

	new_path = safe_malloc(sizeof(char) * buf_size);
	memset(new_path, '\0', buf_size);
	strcpy(new_path, path);
	for (i = 0, slash_count = 0; new_path[i] != '\0'; i++)
	{
		if (new_path[i] == '/')
			slash_count++;
	}
	dir = arg_list[1];
	if (strcmp(dir, ".") == 0)
		new_path = rm_vname(envp, "PWD=", buf_size);
	else if (strcmp(dir, "..") == 0)
	{
		/* check for if things behind it + append*/
		for (flag = 0, i = 0; flag < slash_count - 1; i++)
		{
			if (new_path[i] == '/')
				flag++;
		}
		new_path[i - 1] = '\0';
	}
	else if (strcmp(dir, "~") == 0)
		new_path = rm_vname(envp, "HOME=", buf_size);
	else if (strcmp(dir, "-") == 0)
		new_path = rm_vname(envp, "OLDPWD=", buf_size);
	return (new_path);

}

/**
 * list_to_array - converts a linked list to an array
 * @envp: environemental list to convert
 * Return: a 2D array containing strings contained in linked list
 */

char **list_to_array(env_t *envp)
{
	char **array;
	env_t *temp;
	int count, i, len;

	for (temp = envp, count = 0; temp != NULL; temp = temp->next)
		count++;
	printf("count is %d\n", count);
	array = malloc(sizeof(char *) * (count + 1));
	for (temp = envp, i = 0; temp != NULL; temp = temp->next, i++)
	{
		len = _strlen(temp->value);
		array[i] = safe_malloc(sizeof(char) * (len + 1));
		memset(array[i], '\0', (len + 1));
		memcpy(array[i], temp->value, len);
	}
	array[i] = NULL;
	return (array);
}
