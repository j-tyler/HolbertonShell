#include "shell.h"
/**
 *
 */
void test_alias(buffer *b)
{
	while (b->buf[b->bp] == ' ')
		b->bp++;
	buffer_word_erase(b, b->bp);
	buffer_insert(b, "HAHA I HAVE INSERTED IT!", b->bp);
	printf("__%s\n", b->buf);
}
