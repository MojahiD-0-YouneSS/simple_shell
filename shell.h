#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void shell_loop();
void shell_init();
void _clear();
void _printstr(const char *str);
char *_getenv(const char *name);
size_t _strlen(const char *str);
char *_strdup(const char *str);

#endif 
