#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/* Structure to store aliases */
typedef struct Alias {
    char *name;
    char *value;
    struct Alias *next;
} Alias;

Alias *alias_list = NULL;

/* Structure to store environment variables */
typedef struct Variable {
    char *name;
    char *value;
    struct Variable *next;
} Variable;

Variable *variable_list = NULL;

/* Function prototypes */
const char *get_alias(const char *name);
const char *get_variable(const char *name);

/**
 * Replace variables in the command
 */
void replace_variables(char *command) {
    char variable_name[MAX_COMMAND_LENGTH];
    const char *variable_value;

    char *variable_start = strstr(command, "$");
    while (variable_start != NULL) {
        char *variable_end = strpbrk(variable_start, " \t\n");
        if (variable_end == NULL)
            variable_end = variable_start + strlen(variable_start);

        strncpy(variable_name, variable_start + 1, variable_end - variable_start - 1);
        variable_name[variable_end - variable_start - 1] = '\0';

        variable_value = get_variable(variable_name);
        if (variable_value != NULL) {
            char replacement[MAX_COMMAND_LENGTH];
            snprintf(replacement, sizeof(replacement), "%s%s%s", command, variable_value, variable_end);
            strcpy(command, replacement);
        }

        variable_start = strstr(variable_end, "$");
    }
}

/**
 * Simple shell - UNIX command line interpreter
 * Return: Always 0 (success)
 */
void simple_shell(void) {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    int status;
    
    printf("**** welcome to YOUNESS_SHELL !! ****\n");
    while (1) {
        const char *alias_value;
        printf("#Youness_shell$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break; /* End of file (Ctrl+D) detected */
        }

        command[strcspn(command, "\n")] = '\0'; /* Remove the newline character */

        /* Check for comments and skip them */
        if (command[0] == '#')
            continue;

        /* Check for aliases */
        alias_value = get_alias(command);
        if (alias_value != NULL)
            strcpy(command, alias_value);

        /* Replace variables */
        replace_variables(command);

        if (*command != '\0') {
            /* Handle built-in commands */
            if (strcmp(command, "exit") == 0) {
                exit(0);
            } else if (strcmp(command, "env") == 0) {
                Variable *current = variable_list;
                while (current != NULL) {
                    printf("%s=%s\n", current->name, current->value);
                    current = current->next;
                }
                continue;
            }

            pid = fork();
            if (pid == 0) {
                /* Child process */
                if (execlp(command, command, (char *)NULL) == -1) {
                    perror(command);
                    exit(EXIT_FAILURE);
                }
            } else if (pid < 0) {
                perror(command);
            } else {
                /* Parent process */
                do {
                    waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
        }
    }
}
/* Function to get the alias value */
const char *get_alias(const char *name) {
    Alias *current = alias_list;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

/* Function to get the variable value */
const char *get_variable(const char *name) {
    Variable *current = variable_list;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

