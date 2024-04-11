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
    int serial_no;
    char title[TITLE_LIMIT];
    char authors[AUTHOR_LIMIT];
    char isbn_no[ISBN_LIMIT];
    char publisher[PUB_LIMIT];
    struct date date_of_publication;
};

int addToReadFile(struct book_entry *entry);
void getline(char *string, FILE *input);
int addItemToCatalog(struct book_entry *entry, int *entries);
void pickFunction(struct book_entry *catalog, int *entries);
int readFileContents(struct book_entry *catalog, int *entries);
int printCatalogToFile(struct book_entry *start_here, FILE *file_ptr, int *entries);
void printEntry(struct book_entry *entry, FILE *file_ptr);
void setupOutput(FILE *file_ptr);
void displayCatalog(FILE *file_ptr, struct book_entry *catalog, int *entries);

int main(void)
{
    int entries = 0;
    int *entry_ptr = &entries;

    struct book_entry catalog[BOOK_LIMIT];

    FILE *file_ptr;
    if((file_ptr = fopen(DISPLAY_FILE, "w")) == NULL)
    {
        printf("Could not open file %s\n", DISPLAY_FILE);
        exit(EXIT_FAILURE);
    }

    if (!readFileContents(catalog, entry_ptr))
    {
        pickFunction(catalog, &entries);
        displayCatalog(file_ptr, catalog, entry_ptr);
    }

    exit(EXIT_SUCCESS);
}

void pickFunction(struct book_entry *catalog, int *entries)
{
    enum Functions
    {
        DISPLAY_CATALOG = 1,
        SEARCH_ITEM,
        ADD_ITEM,
        PURCHASE_ITEM,
        STOP,
        UNKNOWN
    };

    bool stop_running = false;
    int response;

    while (!stop_running)
    {
        printf("\n\n\nWhat would you like to do: (pick the number for the function you want to use)\n");
        printf("  Display the catalog: %d\n", DISPLAY_CATALOG);
        printf("  Search for an item: %d\n", SEARCH_ITEM);
        printf("  Add an item: %d\n", ADD_ITEM);
        printf("  Purchase an item: %d\n", PURCHASE_ITEM);
        printf("  Stop: %d\n\n", STOP);

        printf("Response: ");

        scanf("%d", &response);
        switch (response)
        {
        case DISPLAY_CATALOG:
            displayCatalog(stdout, catalog, entries);
            break;
        case SEARCH_ITEM:
            break;
        case ADD_ITEM:
            printf("%d\n", *entries);
            addItemToCatalog(catalog + *entries, entries);
            printf("%d\n", (catalog + *entries) - catalog);
            *entries = *entries + 1;
            break;
        case PURCHASE_ITEM:
            break;
        case STOP:
            stop_running = true;
            break;
        default:
            break;
        }
    }
}

int readFileContents(struct book_entry *catalog, int *entries)
{
    char filename[] = "read_file.txt";

    FILE *read_fileptr;
    if ((read_fileptr = fopen(filename, "r")) == NULL)
    {
        printf("Could not opern file %s\n", filename);
        return -1;
    }

    if(feof(read_fileptr))
    {
        printf("File empty\n");
        return 0;
    }

    do
    {
        // printf("Read line\n");
        fscanf(read_fileptr, "%d", &catalog->serial_no);
        // printf("%d\n", catalog->serial_no);
        
        getline(catalog->title, read_fileptr);
        // printf("%s\n", catalog->title);
        
        getline(catalog->authors, read_fileptr);
        // printf("%s\n", catalog->authors);
        
        getline(catalog->isbn_no, read_fileptr);
        // printf("%s\n", catalog->isbn_no);
        
        getline(catalog->publisher, read_fileptr);
        // printf("%s\n", catalog->publisher);
        
        fscanf(
            read_fileptr,
            "%d/%d/%d",
            &catalog->date_of_publication.day,
            &catalog->date_of_publication.month,
            &catalog->date_of_publication.year);
        // printf("%d/%d/%d\n", catalog->date_of_publication.day, catalog->date_of_publication.month, catalog->date_of_publication.year);


        catalog++;
        *entries = *entries + 1;
    }while (!feof(read_fileptr));

    fclose(read_fileptr);
    return 0;
}

void displayCatalog(FILE *file_ptr, struct book_entry *catalog, int *entries)
{
    setupOutput(file_ptr);
    printCatalogToFile(catalog, file_ptr, entries);
}

void setupOutput(FILE *file_ptr)
{
    char serial_format[] = "%-6d";
    char title_format[] = "%-32s";
    char author_format[] = "%-24s";
    char isbn_format[] = "%-15s";
    char publisher_format[] = "%-24s";
    char date_format[] = "%d/%d/%d\n";

    fprintf(file_ptr, "%-6s", "S/No");
    fprintf(file_ptr, title_format, "Title");
    fprintf(file_ptr, author_format, "Author");
    fprintf(file_ptr, isbn_format, "ISBN");
    fprintf(file_ptr, publisher_format, "Publisher");
    fprintf(file_ptr, "%-21s\n", "Date of publication");
}

int printCatalogToFile(struct book_entry *start_here, FILE *file_ptr, int *entries)
{
    if(*entries == 0)
    {
        printf("No entries in catalog");
        return 0;
    }
    
    for (int index = 0; index < *entries; index++)
        printEntry(start_here + index, file_ptr);

    return 1;
}

int addItemToCatalog(struct book_entry *entry, int *entries)
{
    FILE *file_ptr;

    char filename[] = "book_catalog.txt";

    if (((file_ptr = fopen(filename, "a")) == NULL))
    {
        printf("Could not open file\n");
        return -1;
    }

    entry->serial_no = *entries + 1;

    printf("Enter book details: \n");
    printf("  Book title: ");
    getline(entry->title, stdin);

    printf("  Author: ");
    getline(entry->authors, stdin);

    printf("  ISBN: ");
    getline(entry->isbn_no, stdin);

    printf("  Publisher: ");
    getline(entry->publisher, stdin);

    printf("  Date of publication: ");
    scanf("%d/%d/%d",
          &entry->date_of_publication.day,
          &entry->date_of_publication.month,
          &entry->date_of_publication.year);

    addToReadFile(entry);
    printEntry(entry, file_ptr);
    fclose(file_ptr);
    return 0;
}

void printEntry(struct book_entry *entry, FILE *file_ptr)
{
    char serial_format[] = "%-6d";
    char title_format[] = "%-32s";
    char author_format[] = "%-24s";
    char isbn_format[] = "%-15s";
    char publisher_format[] = "%-24s";
    char date_format[] = "%d/%d/%d\n";

    fprintf(file_ptr, serial_format, entry->serial_no);
    fprintf(file_ptr, title_format, entry->title);
    fprintf(file_ptr, author_format, entry->authors);
    fprintf(file_ptr, isbn_format, entry->isbn_no);
    fprintf(file_ptr, publisher_format, entry->publisher);
    fprintf(
        file_ptr,
        date_format,
        entry->date_of_publication.day,
        entry->date_of_publication.month,
        entry->date_of_publication.year);
}

int addToReadFile(struct book_entry *entry)
{
    FILE *file_ptr;
    char filename[] = "read_file.txt";

    if (((file_ptr = fopen(filename, "a")) == NULL))
    {
        printf("Could not open file\n");
        return -1;
    }

    char serial_format[] = "\n\n%d\n";
    char title_format[] = "%s\n";
    char author_format[] = "%s\n";
    char isbn_format[] = "%s\n";
    char publisher_format[] = "%s\n";
    char date_format[] = "%d/%d/%d\n\n";

    fprintf(file_ptr, serial_format, entry->serial_no);
    fprintf(file_ptr, title_format, entry->title);
    fprintf(file_ptr, author_format, entry->authors);
    fprintf(file_ptr, isbn_format, entry->isbn_no);
    fprintf(file_ptr, publisher_format, entry->publisher);
    fprintf(
        file_ptr,
        date_format,
        entry->date_of_publication.day,
        entry->date_of_publication.month,
        entry->date_of_publication.year);

    fclose(file_ptr);
    return 0;
}

void getline(char *string, FILE *input)
{
    char ch;
    int index = 0;

    char newline;
    fscanf(input, "%[\n]", &newline);

    while ((ch = fgetc(input)) != '\n')
    {
        string[index] = ch;
        index++;
    }
}