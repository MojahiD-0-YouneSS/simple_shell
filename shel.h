#ifndef SHELL_H
#define SHELL_H


#define MAX_COMMAND_LENGTH 100

void display_prompt(void);
char *read_command(void);
void execute_command(const char *command);
void shell_loop(void);

#endif /* SHELL_H */

