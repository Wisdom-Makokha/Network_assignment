#include <stdlib.h>
#include <stdio.h>
//program to do the following
//display catalog
//search item
//purchase item 
//add item
//pay for item

int main()
{
    FILE* file_ptr;
    char *filename = "book_catalog.txt";

    if(((file_ptr = fopen(filename, "w")) == NULL))
    {
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
    }

    fclose(file_ptr);
    exit(EXIT_SUCCESS);
}