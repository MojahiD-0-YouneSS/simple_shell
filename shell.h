#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

typedef struct Alias
{
    char *name;
    char *value;
    struct Alias *next;
} Alias;

typedef struct Variable
{
    char *name;
    char *value;
    struct Variable *next;
} Variable;

void add_alias(const char *name, const char *value);
void add_variable(const char *name, const char *value);
const char *get_alias(const char *name);
const char *get_variable(const char *name);
void replace_variables(char *command);
void simple_shell(void);

#endif
