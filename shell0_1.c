#include "shell.h"

/* Helper function declarations */
void _clear();
void _printstr(const char *str);
char *_getenv(const char *name);
size_t _strlen(const char *str);
char *_strdup(const char *str);

/**
 * shell_init - initializes the shell, providing the name and username
 */
void shell_init() {
    /* Declare variables to use in this function */
    char *username;
    ssize_t input_read;
    char user_input[256];

    /* Clear terminal */
    _clear();

    _printstr("\n\t****WELCOME TO  SIMPLE SHELL****\n");
    _printstr("- CREATED BY YOUNESS, USE with coution !!");
    _printstr("\n*******************\\:> ");

    /* Step 2: Retrieve the username using getenv("USER") */
    username = _getenv("USER");

    if (username != NULL) {
        write(STDOUT_FILENO, "\nUSER is: @", 13);
        write(STDOUT_FILENO, username, _strlen(username));
        write(STDOUT_FILENO, "\n", 1);
    } else {
        /* Prompt the user for a username */
        write(STDOUT_FILENO, "\nEnter your username: ", 24);
        input_read = read(STDIN_FILENO, user_input, sizeof(user_input) - 1);

        if (input_read > 0) {
            user_input[input_read - 1] = '\0';
            username = _strdup(user_input);

            if (username != NULL) {
                write(STDOUT_FILENO, "\nUSER is: @", 13);
                write(STDOUT_FILENO, username, _strlen(username));
                write(STDOUT_FILENO, "\n", 1);
            } else {
                write(STDOUT_FILENO, "\nUnable to allocate memory for username.\n", 43);
            }
        } else {
            write(STDOUT_FILENO, "\nError reading username.\n", 28);
        }
    }
    /* Pause for 1 second */
    sleep(1);

    /* Clear the terminal after */
    _clear();
}

/* Implementations of helper functions go here */

void _clear() {
    /* Implementation for clearing the terminal */
}

void _printstr(const char *str) {
    /* Implementation for printing a string */
	 if (str != NULL) {
        printf("%s", str);
    }
}

char *_getenv(const char *name) {
    /* Implementation for getting an environment variable */
    return getenv(name);
}

size_t _strlen(const char *str) {
    /* Implementation for getting the length of a string */
    return strlen(str);
}

char *_strdup(const char *str) {
    /* Implementation for duplicating a string */
    return strdup(str);
}
