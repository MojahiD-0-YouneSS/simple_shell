#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * shell_loop - function is responsible for repeatedly prompting the user for input
 * @command : comand provided by the user
 * return 0
 * */

void execute_command(const char *command) {
    pid_t pid = fork();

    if (pid == 0) {
        /* Child process */
        char **args = (char **)malloc(2 * sizeof(char *));
        if (execve(command, args, NULL) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
}

void shell_loop() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        /* Display prompt */
        printf("$ ");
        fflush(stdout);

        /* Read the command */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\nExiting the shell. Goodbye!\n");
            break;
        }

        /* Remove the newline character */
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        /* Execute the command */
        execute_command(command);
    }
}
