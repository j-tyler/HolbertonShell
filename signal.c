#include "shell.h"

void signal_handler(int signo)
{
	write(0, "\n", 1);
	print_cmdline();
}
