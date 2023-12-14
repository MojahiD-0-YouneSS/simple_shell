#include "shell.h"

/**
 * Copies a string.
 * @param dest: The destination.
 * @param src: The source.
 * @return: Pointer to the destination.
 */
char *string_copy(char *dest, const char *src)
{
    int i = 0;

    if (dest == src || src == NULL)
        return dest;

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return dest;
}

/**
 * Duplicates a string.
 * @param str: The string to duplicate.
 * @return: Pointer to the duplicated string.
 */
char *string_duplicate(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    result = malloc(sizeof(char) * (length + 1));

    if (!result)
        return NULL;

    for (length++; length--;)
        result[length] = *--str;

    return result;
}

/**
 * Prints an input string to stdout.
 * @param str: The string to be printed.
 * @return: Nothing.
 */
void string_print(const char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * Writes the character c to stdout.
 * @param c: The character to print.
 * @return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int character_print(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

