#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "definitions.h"

int main(void)
{
    int entries = 0;
    int *entry_ptr = &entries;

    struct book_entry catalog[BOOK_LIMIT];

    // FILE *file_ptr = stdout;
    // if((file_ptr = fopen(DISPLAY_FILE, "w")) == NULL)
    // {
    //     printf("Could not open file %s\n", DISPLAY_FILE);
    //     exit(EXIT_FAILURE);
    // }

    if (!readFileContents(catalog, entry_ptr))
        pickFunction(catalog, &entries);

    exit(EXIT_SUCCESS);
}
