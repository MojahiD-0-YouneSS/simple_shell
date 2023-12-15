#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char *command = NULL;

    do {
        printf("#c_is_Here_$> ");
        size_t len = 0;

        if (getline(&command, &len, stdin) == -1) {
            free(command);
            exit(EXIT_SUCCESS);
        }

        command[strcspn(command, "\n")] = '\0';

        if (*command != '\0') {
            pid_t pid, wpid;
            int status;

            pid = fork();
            if (pid == 0) {

                if (execlp(command, command, (char *)NULL) == -1) {
                    perror("./shell");
                    exit(EXIT_FAILURE);
                }
            } else if (pid < 0) {
                perror("./shell");
            } else {

                do {
                    wpid = waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
        }

    } while (1);

    return 0;
}

