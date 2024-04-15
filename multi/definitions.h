// Wisdom Makokha P15/81777/2017
// BRAISON ORINA  P15/142382/2021
// ALEM CYRIL   P15/2135/2021
// MUKHALISI EDWIN WETUNGU   P15/102488/2017
// PAUL OMONDI ODUOR   P15/1897/2020

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TITLE_LIMIT 256
#define AUTHOR_LIMIT 256
#define PUB_LIMIT 128
#define ISBN_LIMIT 12
#define BOOK_LIMIT 1024
#define READ_ONLY "read_file.txt"
#define DISPLAY_FILE "book_catalog.txt"
#define NULL_ENTRY (struct book_entry *) 0

// program to do the following
// display catalog
// search item
// purchase item
// add item
// pay for item

//date structure
struct date
{
    int day;
    int month;
    int year;
};

//book details structure
struct book_entry
{
    int serial_no;
    char title[TITLE_LIMIT];
    char authors[AUTHOR_LIMIT];
    char isbn_no[ISBN_LIMIT];
    char publisher[PUB_LIMIT];
    struct date date_of_publication;
};

//prototype declarations
int addToReadFile(struct book_entry *entry);
void getline(char *string, FILE *input);
int addItemToCatalog(struct book_entry *entry, int *entries);
void pickFunction(struct book_entry *catalog, int *entries);
int readFileContents(struct book_entry *catalog, int *entries);
int printCatalogToFile(struct book_entry *start_here, FILE *file_ptr, int *entries);
void printEntry(struct book_entry *entry, FILE *file_ptr);
void setupOutput(FILE *file_ptr);
void displayCatalog(FILE *file_ptr, struct book_entry *catalog, int *entries);
struct book_entry * search_item(struct book_entry *catalog, char *isbn, int *entries);
