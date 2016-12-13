#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void tok_list(char *buffer, char **arg_list);
void print_cmdline();
int _strlen(char *s);
void free_args(char **arg_list);
void tokenize_buf(char *buf, char **av);
#endif
