#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * simple_shell - Simple UNIX command line interpreter
 * Return: Always 0 (success)
 */
void simple_shell(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        printf("#cisfun$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            printf("\n");
            break; /* End of file (Ctrl+D) detected */
        }

        command[strcspn(command, "\n")] = '\0'; /* Remove the newline character */

        if (*command != '\0')
        {
            pid_t pid, wpid;
            int status;

            pid = fork();
            if (pid == 0)
            {
                /* Child process */
                if (execlp(command, command, (char *)NULL) == -1)
                {
                    perror(command);
                    exit(EXIT_FAILURE);
                }
            }
            else if (pid < 0)
            {
                perror(command);
            }
            else
            {
                /* Parent process */
                do
                {
                    wpid = waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
        }
    }
}

/**
 * main - Example main function
 * Return: Always 0 (success)
 */
int main(void)
{
    simple_shell();
    return (0);
}

