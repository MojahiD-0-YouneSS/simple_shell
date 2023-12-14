#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 256

void execute_command(const char *command);
void shell_loop();

#endif 
