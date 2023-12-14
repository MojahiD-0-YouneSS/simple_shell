#include "shell.h"

void execute_command(const char *command);

void shell_loop() {
    char command[MAX_COMMAND_LENGTH];
    size_t len;

    while (1) {
        /* Display prompt */
        printf("$ ");
        fflush(stdout);

        /* Read the command */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\nExiting the shell. Goodbye!\n");
            break;
        }
         len = strlen(command);
        /* Remove the newline character */
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        /* Execute the command */
        execute_command(command);
    }
}

void execute_command(const char *command) {
    pid_t pid = fork();

    if (pid == 0) {
        /* Child process */
        char *args[] = { "/bin/sh", "-c", NULL, NULL };
        args[2] = strdup(command); /* Duplicate the command to a non-const string */

        if (args[2] == NULL) {
            perror("Error duplicating command");
            exit(EXIT_FAILURE);
        }

        if (execvp("/bin/sh", args) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "/bin/sh: 1: %s: not found\n", command);
        }
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
}
