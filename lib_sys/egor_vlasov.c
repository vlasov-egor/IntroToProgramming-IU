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

//  global variables declaration
static int *address_of_books_list = NULL;
static int *address_of_last_book = NULL;

//  structs declaration

struct book
{
    char title[60];
    char *author[50];
    int year;
    float book_rate;
};

struct customer
{
    char name[50];
    int age;
    float customer_rate;
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
    stru
    while (auto book = )
    printf("None");
}

struct books_linked_list* add_book(struct books_linked_list *after, struct book item)
{
    struct books_linked_list new = {
        .book = item,
    };

    if (after != NULL)
    {
        after->next = &new;
    }

    return &new;
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
    printf("EGOR SOSET HUY");
}

//  main
int main()
{
    int input;

    while ("True")
    {
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            printf("You choosed function \"Show Books\"\n");
            show_books();
            break;
        case 2:
            printf("You choosed function \"Add Book\"\n");
            struct book new = {.title = "1wqasada", .author = "dsadsad", .year = 22, .book_rate = 1.0};

            address_of_last_book = add_book(&address_of_last_book, new);

            if (address_of_books_list == NULL) {
                address_of_books_list = address_of_last_book;
            }
            
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