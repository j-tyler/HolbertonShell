#include "shell.h"

/**
 * signal_handler - handles the ctrl-c signal
 * @signo: signal received
 */

void signal_handler(int signo)
{
	(void) signo;
	write(0, "\n", 1);
	print_cmdline();
}
