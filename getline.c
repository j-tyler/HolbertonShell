#include "shell.h"

/**
 * _getline - a function that grabs stdin and puts in buffer and returns
 * string.
 *
 */
char *_getline(char **buf)
{
	int i, n, size, b_size;
	char *new_buf;

	b_size = 1024;
	*buf = safe_malloc(sizeof(char) * b_size);
	while ((n = read(0, *buf, b_size)) > 0)
	{
		if (n < b_size)
		{
			(*buf)[n] = '\0';
			return (*buf);
		}
		b_size *= 2;
		new_buf = safe_malloc((b_size) * sizeof(char));
		memcpy(new_buf, *buf, b_size/2); /* This does not work to save buffer */
		*buf = new_buf;
	}
	if (n == 0) /* Exit when given EOF */
	{
		defer_free(FREE_ADDRESSES);
		_exit(0);
	}
	return (*buf);
}
