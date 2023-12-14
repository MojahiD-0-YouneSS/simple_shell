#include "shell.h"

/**
 * Computes the length of a string.
 * @param s: The string whose length to check.
 * @return: Integer length of the string.
 */
int string_length(const char *s)
{
    int length = 0;

    if (!s)
        return 0;

    while (*s++)
        length++;

    return length;
}

/**
 * Performs lexicographic comparison of two strings.
 * @param s1: The first string.
 * @param s2: The second string.
 * @return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int string_compare(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);

        s1++;
        s2++;
    }

    return (*s1 == *s2) ? 0 : (*s1 < *s2 ? -1 : 1);
}

/**
 * Checks if the beginning of a string matches a given substring.
 * @param haystack: The string to search.
 * @param needle: The substring to find.
 * @return: Address of the next character of haystack or NULL.
 */
const char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;

    return haystack;
}

/**
 * Concatenates two strings.
 * @param dest: The destination buffer.
 * @param src: The source buffer.
 * @return: Pointer to the destination buffer.
 */
char *string_concat(char *dest, const char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = *src;

    return result;
}

