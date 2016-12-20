#include "shell.h"
/**
 * variable_expansion - Expand variables in the buffer
 * @b: buffer structure
 * @envp: Enviorn structure
 * Description: Expands variables from input of $VALUE.
 * 				$? = Last return value.
 *				$$ = Process ID.
 *				$VALUE = Any enviormental variable. Deletes if found none.
 */
void variable_expansion(buffer *b, env_t *envp, int retrn_value)
{
	char buffer[BUFSIZE];
	char *hold;
	int index, offset, fp;


	offset = index = 0;
	while ((index = _strstr_int(b->buf + b->bp + offset, "$")) >= 0)
	{
		index += offset;
		offset = index + 1;
		if (b->buf[b->bp + index + 1] == '?')
		{
			hold = _itoa(retrn_value);
			buffer_word_erase(b, b->bp + index);
			buffer_insert(b, hold, b->bp + index);
			_free(hold);
		}
		else if (b->buf[b->bp + index + 1] == '$')
		{
			buffer_word_erase(b, b->bp + index);
			hold =  _getpid();
			buffer_insert(b, hold, b->bp + index);
			// insert PID at b->bp + index
		}
		else if (!_is_whitespace(b->buf[b->bp + index + 1]))
		{
			hold = rm_vname(envp, b->buf + b->bp + index + 1, b->size);
			buffer_word_erase(b, b->bp + index);
			if (hold != NULL)
				buffer_insert(b, hold, b->bp + index);
		}
	}
}

/**
 * _getpid - gets the pid of the current process
 * Return: a string of the pid
 */

char *_getpid(void)
{
	char path[BUFSIZE], id[BUFSIZE];
	char *hold, *ppid;
	pid_t pid, real_pid;
	int fd, fr;

	_memset(path, '\0', BUFSIZE);
	_memset(id, '\0', BUFSIZE);
	pid = fork();
	if (pid == 0)
	{
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	else
	{
		hold = _itoa(pid);
		_strcat(path, "/proc/");
		_strcat(path, hold);
		_strcat(path, "/stat");
		fd = open(path, O_RDONLY);
		if (fd > 0)
		{
			fr = read(fd, id, 100);
			ppid = _getTok(id, 4);
		}
		wait(NULL);
	}
	return (ppid);
}

/**
 * _getTok - gets the nth element of buffer, seperated by space
 * @n: which element to get
 */

char * _getTok(char *stat, int n)
{
	int i, j, space_count;
	char *buf;

	buf = safe_malloc(sizeof(char) * BUFSIZE);
	_memset(buf, '\0', BUFSIZE);
	space_count = 0;
	for(i = 0, j = 0; stat[i] != '\0' || space_count <= n; i++)
	{
		if (stat[i] == ' ' && space_count != n - 1)
		{
			memset(buf, '\0', BUFSIZE);
			j = 0;
			space_count++;
		}
		else if (stat[i] == ' '  && space_count == n - 1)
			return (buf);
		else
			buf[j++] = stat[i];
	}
	return (NULL);
}
