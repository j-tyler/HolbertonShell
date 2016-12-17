#include "shell.h"

/**
 * _getline - a function that grabs stdin and puts in buffer and returns
 * string.
 *
 */
int _getline(buffer *b)
{
	int offset, n;
	char *new_buf;

	/* DEBUG, does not work on realloc the third time */

	offset = 0;
	while ((n = read(0, b->buf + offset, b->size - offset)) > 0)
	{
		if (n < b->size - offset)
		{
			b->buf[n + offset] = '\0';
			return (b->size);
		}
		buffer_reallocate(b);
		offset += n;
	}
	if (n == 0) /* Exit when given EOF */
	{
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	return (b->size);
}
