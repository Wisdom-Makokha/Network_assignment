#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold book information
struct Book
{
    int serialNumber;
    char title[100];
    char authors[100];
    char isbn[20];
    char publisher[100];
    char dateOfPublication[20];
};

// Function prototypes
void displayCatalog();
void searchForItem(const char *keyword);
void purchaseItem(const char *isbn);
void payForItem(const char *isbn);
int isISBNUnique(const char *isbn);

// Function to read books from file and display the catalog
void displayCatalog()
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    struct Book book;
    printf("S/No\tTitle\t\t\t\tAuthors\t\t\tISBN\t\tPublisher\t\tDate of publication\n");
    while (fscanf(file, "%d %s %s %s %s %s", &book.serialNumber, book.title, book.authors, book.isbn, book.publisher, book.dateOfPublication) != EOF)
    {
        printf("%d\t%s\t\t\t%s\t\t\t%s\t\t%s\t\t%s\n", book.serialNumber, book.title, book.authors, book.isbn, book.publisher, book.dateOfPublication);
    }
    fclose(file);
}

// Function to search for a book by keyword in title or authors
void searchForItem(const char *keyword)
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    struct Book book;
    int found = 0;
    printf("S/No\tTitle\t\t\t\tAuthors\t\t\tISBN\t\tPublisher\t\tDate of publication\n");
    while (fscanf(file, "%d %s %s %s %s %s", &book.serialNumber, book.title, book.authors, book.isbn, book.publisher, book.dateOfPublication) != EOF)
    {
        if (strstr(book.title, keyword) != NULL || strstr(book.authors, keyword) != NULL)
        {
            printf("%d\t%s\t\t\t%s\t\t\t%s\t\t%s\t\t%s\n", book.serialNumber, book.title, book.authors, book.isbn, book.publisher, book.dateOfPublication);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No book found with keyword '%s'\n", keyword);
    }
    fclose(file);
}

// Function to simulate purchasing a book
void purchaseItem(const char *isbn)
{
    if (!isISBNUnique(isbn))
    {
        printf("Book with ISBN %s is already purchased!\n", isbn);
        return;
    }
    printf("Book with ISBN %s added to cart!\n", isbn);
    // Logic for adding book to cart goes here
}

// Function to simulate paying for a book
void payForItem(const char *isbn)
{
    if (isISBNUnique(isbn))
    {
        printf("No book with ISBN %s found in cart!\n", isbn);
        return;
    }
    // Logic for payment goes here
    printf("Payment for book with ISBN %s completed!\n", isbn);
}

// Function to check if ISBN is unique
int isISBNUnique(const char *isbn)
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1; // Assuming ISBN is unique if file cannot be opened
    }

    struct Book book;
    while (fscanf(file, "%d %s %s %s %s %s", &book.serialNumber, book.title, book.authors, book.isbn, book.publisher, book.dateOfPublication) != EOF)
    {
        if (strcmp(book.isbn, isbn) == 0)
        {
            fclose(file);
            return 0; // ISBN is not unique
        }
    }
    fclose(file);
    return 1; // ISBN is unique
}

int main()
{
    int choice;
    char keyword[100];
    char isbn[20];

    do
    {
        printf("\nOnline Book Shopping Application\n");
        printf("1. Display Catalog\n");
        printf("2. Search for Book\n");
        printf("3. Purchase Book\n");
        printf("4. Pay for Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayCatalog();
            break;
        case 2:
            printf("Enter keyword to search for: ");
            scanf("%s", keyword);
            searchForItem(keyword);
            break;
        case 3:
            printf("Enter ISBN of book to purchase: ");
            scanf("%s", isbn);
            purchaseItem(isbn);
            break;
        case 4:
            printf("Enter ISBN of book to pay for: ");
            scanf("%s", isbn);
            payForItem(isbn);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}


