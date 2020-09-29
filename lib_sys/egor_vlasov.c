//  TODO show books
//  TODO add book
//  TODO update book
//  TODO remove books

//  TODO show customer
//  TODO add customer
//  TODO update customer
//  TODO remove customer

//  libs declaration

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  global variables declaration
static struct books_linked_list *address_of_books_list = NULL;
static struct books_linked_list *address_of_last_book = NULL;

//  structs declaration

struct book
{
    char title[60];
    char author[50];
    int year;
    float rate;
};

struct customer
{
    char name[50];
    int age;
    float rate;
};

//  linked-lists
struct books_linked_list
{
    struct book book;
    struct books_linked_list *next;
};

//  funcs for books

void show_books()
{
    struct books_linked_list *current = address_of_books_list;

    while (current != NULL)
    {
        printf("\e[34mTitle: \e[0m%s", current->book.title);
        printf("\e[32mAutor: \e[0m%s", current->book.author);
        printf("\e[32mYear: \e[0m%d\n", current->book.year);
        printf("\e[32mRate: \e[0m%f\n\n", current->book.rate);
        current = current->next;
    }
}

struct books_linked_list *add_book(struct books_linked_list *after, struct book item)
{
    struct books_linked_list *new = (struct books_linked_list *)malloc(sizeof(struct books_linked_list));
    new->book = item;

    if (after != NULL)
    {
        after->next = new;
    }

    return new;
}

void update_book()
{
    printf("None");
}

void remove_book()
{
    printf("None");
}

//  funcs for customers

void show_customers()
{
    printf("None");
}

void add_customer()
{
    printf("None");
}

void update_customer()
{
    printf("None");
}

void remove_customer()
{
    printf("None");
}

//  main
int main()
{
    int input;

    while ("True")
    {
        printf("\e[32mType command: \e[36m");
        scanf("%d", &input);
        getchar(); // Read fucking newline symbol

        switch (input)
        {
        case 1:
            printf("\e[0mYou choosed function \"Show Books\"\n\n");
            show_books();
            printf("\n");
            break;
        case 2:
            printf("\e[0mYou choosed function \"Add Book\"\n");
            struct book new_book;

            printf("\e[33mWrite information about book: title, author, year, book rate\n\n\e[36m");

            fgets(new_book.title, 60, stdin);
            fgets(new_book.author, 50, stdin);
            scanf("%d", &new_book.year);
            scanf("%f", &new_book.rate);

            address_of_last_book = add_book(address_of_last_book, new_book);

            if (address_of_books_list == NULL)
            {
                address_of_books_list = address_of_last_book;
            }

            printf("\n\e[33mBook Added!\n\n");

            break;
        case 3:
            printf("You choosed function \"Update Book\"\n");
            update_book();
            break;
        case 4:
            printf("You choosed function \"Remove Book\"\n");
            remove_book();
            break;
        case 5:
            printf("You choosed function \"Show Customers\"\n");
            show_customers();
            break;
        case 6:
            printf("You choosed function \"Add customer\"\n");
            add_customer();
            break;
        case 7:
            printf("You choosed function \"Update customer\"\n");
            update_customer();
            break;
        case 8:
            printf("You choosed function \"Remove customer\"\n");
            remove_customer();
            break;
        case 9:
            printf("exit");
            return 0;
        default:
            printf("You wrote wrong command\n");
        }
    }
}