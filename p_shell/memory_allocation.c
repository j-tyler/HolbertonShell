#include "shell.h"
/**
 * _free - frees memory and removes address from defer'd free list
 * @address: address to free
 */
void _free(void *address)
{
	/* ADD: send to defer_free */
	free(address);
}
