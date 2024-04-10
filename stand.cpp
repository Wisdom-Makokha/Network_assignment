#include <stdlib.h>
#include <stdio.h>

#define TITLE_LIMIT 256
#define AUTHOR_LIMIT 256
#define PUB_LIMIT 128
#define ISBN_LIMIT 12
#define BOOK_LIMIT 1024

// program to do the following
// display catalog
// search item
// purchase item
// add item
// pay for item

// S/No    Title                   Authors         ISBN          Publisher       Date of publication
// 1       Network programming     xxxxxxx        xxxxxx        xxxxxxxxx       xxxxxxxxxxxxxx
// 2

struct date
{
    int day;
    int month;
    int year;
};

struct book_entry
{
    // int serial_no;
    char title[TITLE_LIMIT];
    char authors[AUTHOR_LIMIT];
    char isbn_no[ISBN_LIMIT];
    char publisher[PUB_LIMIT];
    struct date date_of_publication;
};

void getline(char *string);
void addItemToCatalog(struct book_entry *entry);
void printCatalogToFile(struct book_entry *start_here, FILE *file_ptr);

int main(void)
{
    FILE *file_ptr;
    char filename[] = "book_catalog.txt";

    if (((file_ptr = fopen(filename, "w")) == NULL))
    {
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
    }

    struct book_entry catalog[BOOK_LIMIT];

    printCatalogToFile(catalog, file_ptr);

    fclose(file_ptr);
    exit(EXIT_SUCCESS);
}



void printCatalogToFile(struct book_entry *start_here, FILE *file_ptr)
{
    int index = 1;

    char serial_format[] = "%-5d";
    char title_format[] = "%-32s";
    char author_format[] = "%-32s";
    char isbn_format[] = "%-12s";
    char publisher_format[] = "%-24s";
    char date_format[] = "%d/%d/%d\n";

    fprintf(file_ptr, "%-6s", "S/No");
    fprintf(file_ptr, title_format, "Title");
    fprintf(file_ptr, author_format, "Author");
    fprintf(file_ptr, isbn_format, "ISBN");
    fprintf(file_ptr, publisher_format, "Publisher");
    fprintf(file_ptr, "%-21s\n", "Date of publication");

    // fprintf(file_ptr, serial_format, index);
    // fprintf(file_ptr, title_format, start_here->title);
    // fprintf(file_ptr, author_format, start_here->authors);
    // fprintf(file_ptr, isbn_format, start_here->isbn_no);
    // fprintf(file_ptr, publisher_format, start_here->publisher);
    // fprintf(file_ptr, date_format, start_here->date_of_publication.day, start_here->date_of_publication.month, start_here->date_of_publication.year);
}

void addItemToCatalog(struct book_entry *entry)
{
    printf("Enter book details: ");

    printf("Book title: ");
    getline(entry->title);

    printf("Author: ");
    getline(entry->authors);

    printf("ISBN: ");
    getline(entry->isbn_no);

    printf("Publisher: ");
    getline(entry->publisher);

    printf("Date of publication: ");
    scanf("%d/%d/%d",
          &entry->date_of_publication.day,
          &entry->date_of_publication.month,
          &entry->date_of_publication.year);
}

void getline(char *string)
{
    char ch;
    int index = 0;

    while ((ch = getchar()) != '\n')
    {
        string[index] = ch;
        index++;
    }
}