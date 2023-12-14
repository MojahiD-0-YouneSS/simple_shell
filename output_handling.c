#include "shell.h"

/**
 * Prints an input string to stderr.
 * @param str: The string to be printed.
 * @return: Nothing.
 */
void eputs(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * Writes the character c to stderr.
 * @param c: The character to print.
 * @return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * Writes the character c to the given file descriptor.
 * @param c: The character to print.
 * @param fd: The file descriptor to write to.
 * @return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return 1;
}

/**
 * Prints an input string to the given file descriptor.
 * @param str: The string to be printed.
 * @param fd: The file descriptor to write to.
 * @return: The number of characters written.
 */
int putsfd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;

    while (*str)
    {
        i += putfd(*str++, fd);
    }

    return i;
}

