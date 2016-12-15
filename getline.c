#include "shell.h"

/**
 * _getline - a function that grabs stdin and puts in buffer and returns
 * string.
 *
 */
int _getline(char **buf)
{
	static int b_size = BUFSIZE;
	int offset, n;
	char *new_buf;

	/* DEBUG, does not work on realloc the third time */

	offset = 0;
	while ((n = read(0, *buf + offset, b_size - offset)) > 0)
	{
		if (n < b_size - offset)
		{
			(*buf)[n + offset] = '\0';
			return (b_size);
		}
		b_size *= 2;
		new_buf = safe_malloc((b_size) * sizeof(char));
		offset += n;
		memcpy(new_buf, *buf, b_size / 2); /* DEBUG: rewrite this non-stdlib */
		*buf = new_buf;
	}
	if (n == 0) /* Exit when given EOF */
	{
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	return (b_size);
}
