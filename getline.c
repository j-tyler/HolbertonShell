#include "shell.h"

/**
 * _getline - a function that grabs stdin and puts in buffer and returns
 * string.
 *
 */
int _getline(buffer *buf)
{
	int offset, n;
	char *new_buf;

	/* DEBUG, does not work on realloc the third time */

	offset = 0;
	while ((n = read(0, buf->buf + offset, buf->size - offset)) > 0)
	{
		if (n < buf->size - offset)
		{
			buf->buf[n + offset] = '\0';
			return (buf->size);
		}
		buf->size *= 2;
		new_buf = safe_malloc((buf->size) * sizeof(char));
		offset += n;
		memcpy(new_buf, buf->buf, buf->size / 2); /* DEBUG: rewrite this non-stdlib */
		buf->buf = new_buf;
	}
	if (n == 0) /* Exit when given EOF */
	{
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	return (buf->size);
}
