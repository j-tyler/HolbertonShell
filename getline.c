#include "shell.h"

/**
 * _getline - a function that grabs stdin and puts in buffer and returns
 * string.
 *
 */
int _getline(buffer *b)
{
	int offset, n;

	/* ADD: Take fd for using with scripts */
	/* DEBUG: READ is undefined when taking newline from pipes */
	offset = 0;
	while ((n = read(0, b->buf + offset, b->size - offset)) > 0 &&
			b->buf[n + offset - 1] != '\n')
	{
		buffer_reallocate(b);
		offset += n;
	}
	if (n == 0) /* Exit when given EOF */
	{
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	b->buf[n + offset] = '\0';
	return (b->size);
}
