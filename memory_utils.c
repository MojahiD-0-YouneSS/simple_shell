#include "shell.h"

/**
 * Frees a pointer and sets it to NULL.
 * @param memory_pointer: Address of the pointer to free.
 * @return: 1 if freed successfully, 0 otherwise.
 */

int free_and_null(void **memory_pointer)
{
    if (memory_pointer == NULL || *memory_pointer == NULL) {
        return 0;  // Nothing to free or already NULL
    }

    free(*memory_pointer);
    *memory_pointer = NULL;

    return 1;
}

