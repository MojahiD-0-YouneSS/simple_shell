#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void execute_command(const char *command);
void shell_loop();

#endif 
