#include "shell.h"

/**
 * _getline - Read input and put in buffer
 * @b: buffer structure
 * @fd: file descriptor to read from
 * @envp: enviornment structure
 * Return: Always 0. Exit on failure or EOF
 */
int _getline(buffer *b, int fd, env_t *envp)
{
	int offset, n;

	/* DEBUG: READ is undefined when taking newline from pipes? */

	offset = 0;
	while ((n = read(fd, b->buf + offset, b->size - offset)) > 0 &&
			b->buf[b->bp + offset + n - 1] != '\n' &&
			b->buf[b->bp + offset + n] != '\0')
	{
		buffer_reallocate(b);
		offset += n;
	}
	if (n == 0)
	{
		if (fd > 2)
			close(fd);
		history_wrapper("", envp, 'w');
		defer_free(FREE_ADDRESSES);
		_write("\n");
		_exit(0);
	}
	b->buf[n + offset] = '\0';
	return (0);
}
/**
 * _getline_fileread - wrapper function that reads a file into buffer
 * @b: buffer structure
 * @envp: enviornment structure
 *
 * Return: 1 on file not exist, else 0
 */
int _getline_fileread(buffer *b, env_t *envp)
{
	int fd, i;
	char *filename, *fullfilename;

	i = b->bp;
	while (_is_whitespace(b->buf[i]))
		i++;
	if (!_str_match(b->buf + i, "simple_shell") || b->buf[i] == '\0')
		return (0);
	while (!_is_whitespace(b->buf[i]) && b->buf != '\0')
		i++;
	while (_is_whitespace(b->buf[i]) && b->buf != '\0')
		i++;
	filename = b->buf + i;
	while (!_is_whitespace(b->buf[i]) && b->buf != '\0')
		i++;
	b->buf[i] = '\0';
	make_path(&fullfilename, filename, "PWD", envp, b->size);
	fd = open(fullfilename, O_RDONLY);
	if (fd == -1)
	{
		_write("Cannot open filename specified\n");
		_getline_file_exit(b);
		return (1);
	}
	_getline(b, fd, envp);
	close(fd);
	return (FILEREADING);
}
/**
 * _getline_file_exit - janky solution to correctly exit on fileread failure
 * @b: buffer structure
 */
void _getline_file_exit(buffer *b)
{
	/* DEBUG: We need to rework some builtins for this solution to be fixed*/
	b->buf[0] = 'e';
	b->buf[1] = 'x';
	b->buf[2] = 'i';
	b->buf[3] = 't';
	b->buf[4] = ' ';
	b->buf[5] = '1';
	b->buf[6] = '\0';
	b->bp = 0;
}
