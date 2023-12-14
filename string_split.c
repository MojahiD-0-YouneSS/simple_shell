#include "shell.h"

/**
 * Splits a string into words based on delimiters.
 * Repeated delimiters are ignored.
 * @param str: The input string.
 * @param delimiters: The delimiter string.
 * @return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string(char *str, char *delimiters)
{
    int i, j, k, m, num_words = 0;
    char **result;

    if (str == NULL || str[0] == '\0')
        return NULL;

    if (!delimiters)
        delimiters = " ";

    // Count the number of words
    for (i = 0; str[i] != '\0'; i++)
        if (!is_delim(str[i], delimiters) && (is_delim(str[i + 1], delimiters) || !str[i + 1]))
            num_words++;

    if (num_words == 0)
        return NULL;

    // Allocate memory for the array of strings
    result = malloc((1 + num_words) * sizeof(char *));
    if (!result)
        return NULL;

    for (i = 0, j = 0; j < num_words; j++)
    {
        // Skip delimiters
        while (is_delim(str[i], delimiters))
            i++;

        k = 0;
        while (!is_delim(str[i + k], delimiters) && str[i + k])
            k++;

        // Allocate memory for each word
        result[j] = malloc((k + 1) * sizeof(char));
        if (!result[j])
        {
            // Handle memory allocation failure
            for (k = 0; k < j; k++)
                free(result[k]);
            free(result);
            return NULL;
        }

        // Copy the word to the result array
        for (m = 0; m < k; m++)
            result[j][m] = str[i++];
        result[j][m] = '\0';
    }

    result[j] = NULL;
    return result;
}

