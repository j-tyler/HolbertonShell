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

#define BUFSIZE 1024
#define ARGLISTINIT 5

void tok_list(char *buffer, char **arg_list);
void print_cmdline();
int _strlen(char *s);
void free_args(char **arg_list);
/* tokenize.c */
void tokenize_buf(char *buf, char ***av);
void _av_init(char *buf, char ***av);
int _is_whitespace(char c);
#endif
