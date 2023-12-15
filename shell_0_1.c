#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
    printf("$ ");
}

/**
 * read_command - Reads a command from the user
 * 
 * Return: The command entered by the user
 */
char *read_command(void)
{
    char *command = NULL;
    size_t len = 0;

    if (getline(&command, &len, stdin) == -1) {
        free(command);
        exit(EXIT_SUCCESS);
    }

    // Remove the newline character at the end
    command[strcspn(command, "\n")] = '\0';

    return command;
}

/**
 * execute_command - Executes a command using execve
 * 
 * Parameters:
 *   - command: The command to be executed
 */
void execute_command(const char *command)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execve(command, NULL, NULL) == -1) {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("Error");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

/**
 * shell_loop - Main loop of the shell
 */
void shell_loop(void)
{
    char *command;

    do {
        display_prompt();
        command = read_command();

        if (*command != '\0') {
            execute_command(command);
        }

        free(command);
    } while (1);
}

