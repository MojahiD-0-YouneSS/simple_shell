#include "shell.h"

/**
 * Copies at most n characters from the source string to the destination string.
 * @param dest: The destination string to be copied to.
 * @param src: The source string.
 * @param n: The maximum number of characters to copy.
 * @return: The concatenated string.
 */

char *string_copy_n(char *dest, const char *src, int n)
{
    int i, j;
    char *result = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }

    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }

    return result;
}

/**
 * Concatenates at most n characters from the source string to the destination string.
 * @param dest: The first string.
 * @param src: The second string.
 * @param n: The maximum number of bytes to be used.
 * @return: The concatenated string.
 */

char *string_concat_n(char *dest, const char *src, int n)
{
    int i, j;
    char *result = dest;

    i = 0;
    while (dest[i] != '\0')
        i++;

    j = 0;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    if (j < n)
        dest[i] = '\0';

    return result;
}

/**
 * Locates a character in a string.
 * @param s: The string to be parsed.
 * @param c: The character to look for.
 * @return: A pointer to the memory area s.
 */

char *find_character(char *s, char c)
{
    do
    {
        if (*s == c)
            return s;
    } while (*s++ != '\0');

    return NULL;
}

