#include <stdlib.h>
#include <stdio.h>

#define TITLE_LIMIT 256
#define AUTHOR_LIMIT 256
#define PUB_LIMIT 128
#define ISBN_LIMIT 12
#define BOOK_LIMIT 1024

//program to do the following
//display catalog
//search item
//purchase item 
//add item
//pay for item

// S/No    Title                   Authors         ISBN          Publisher       Date of publication
// 1       Network programming     xxxxxxx        xxxxxx        xxxxxxxxx       xxxxxxxxxxxxxx
// 2 

struct date {
    int day;
    int month;
    int year;
};

struct book_entry{
    int serial_no;
    char title[TITLE_LIMIT];
    char authors[AUTHOR_LIMIT];
    char isbn_no[ISBN_LIMIT];
    char publisher[PUB_LIMIT];
    struct date date_of_publication;
};

void getline(char *string);

int main()
{
    FILE* file_ptr;
    char filename[] = "book_catalog.txt";

    if(((file_ptr = fopen(filename, "w")) == NULL))
    {
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
    }

    struct book_entry catalog[BOOK_LIMIT];
    
    printf("Date of publication: ");
    scanf("%d/%d/%d", &catalog[0].date_of_publication.day, &catalog[0].date_of_publication.month, &catalog[0].date_of_publication.year);

    printf("\n%d/%d/%d\n", catalog[0].date_of_publication.day, catalog[0].date_of_publication.month, catalog[0].date_of_publication.year);

    fclose(file_ptr);
    exit(EXIT_SUCCESS);
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
    scanf("%d/%d/%d", &entry->date_of_publication.day, &entry->date_of_publication.month, &entry->date_of_publication.year);
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