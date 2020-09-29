//  libs declaration
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  global variables declaration
static struct books_linked_list *address_of_books_list = NULL;
static struct books_linked_list *address_of_last_book = NULL;

static struct customers_linked_list *address_of_customers_list = NULL;
static struct customers_linked_list *address_of_last_customer = NULL;
//  structs declaration

struct book
{
    char title[60];
    char author[50];
    int year;
    float rate;
};

typedef struct
{
    char name[50];
    int age;
    float rate;
} customer;

//  linked-lists
struct books_linked_list
{
    struct book book;
    struct books_linked_list *next;
};

struct customers_linked_list
{
    customer customer;
    struct customers_linked_list *next;
};

//  funcs for books

void show_books()
{
    struct books_linked_list *current = address_of_books_list;

    if (current == NULL)
    {
        printf("\e[31mNothing here\n\n\e[0m");
    }
    else
    {
        int i = 0;
        while (current != NULL)
        {
            printf("\e[34mTitle: \e[0m%s", current->book.title);
            printf("\e[32mAutor: \e[0m%s", current->book.author);
            printf("\e[32mYear: \e[0m%d\n", current->book.year);
            printf("\e[32mRate: \e[0m%f\n", current->book.rate);
            printf("\e[32mIndex: \e[0m%d\n\n", i);
            current = current->next;
            i += 1;
        }
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

void update_book(int index, struct book new)
{
    int i = 0;

    for (struct books_linked_list *current = address_of_books_list; current != NULL; current = current->next)
    {
        if (i == index)
        {
            current->book = new;
            return;
        }

        i += 1;
    }
}

void remove_book(int index)
{
    if (index == 0)
    {
        struct books_linked_list *tmp = address_of_books_list;
        address_of_books_list = address_of_books_list->next;
        free(tmp);
        return;
    }

    struct books_linked_list *previous = NULL;
    struct books_linked_list *current = address_of_books_list;
    auto int i = 0;

    while (current != NULL)
    {
        if (index == i)
        {
            if (address_of_last_book == current)
            {
                address_of_last_book = previous;
                previous->next = NULL;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            return;
        }

        previous = current;
        current = current->next;
        i -= -1;
    }
}

//  funcs for customers

void show_customers()
{
    struct customers_linked_list *current = address_of_customers_list;

    if (current == NULL)
    {
        printf("\e[31mNothing here\n\n\e[0m");
    }
    else
    {
        int i = 0;
        while (current != NULL)
        {
            printf("\e[34mName: \e[0m%s", current->customer.name);
            printf("\e[32mAge: \e[0m%d\n", current->customer.age);
            printf("\e[32mRate: \e[0m%f\n", current->customer.rate);
            printf("\e[32mIndex: \e[0m%d\n\n", i);
            current = current->next;
            i += 1;
        }
    }
}

struct customers_linked_list *add_customer(struct customers_linked_list *after, customer item)
{
    struct customers_linked_list *new = (struct customers_linked_list *)malloc(sizeof(struct customers_linked_list));
    new->customer = item;

    if (after != NULL)
    {
        after->next = new;
    }

    return new;
}

void update_customer(int index, customer new)
{
    int i = 0;

    for (struct customers_linked_list *current = address_of_customers_list; current != NULL; current = current->next)
    {
        if (i == index)
        {
            current->customer = new;
            return;
        }

        i += 1;
    }
}

void remove_customer(int index)
{
    if (index == 0)
    {
        struct customers_linked_list *tmp = address_of_customers_list;
        address_of_customers_list = address_of_customers_list->next;
        free(tmp);
        return;
    }

    struct customers_linked_list *previous = NULL;
    struct customers_linked_list *current = address_of_customers_list;
    auto int i = 0;

    while (current != NULL)
    {
        if (index == i)
        {
            if (address_of_last_customer == current)
            {
                address_of_last_customer = previous;
                previous->next = NULL;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            return;
        }

        previous = current;
        current = current->next;
        i -= -1;
    }
}

//  main
int main()
{
    int input;

    while ("True")
    {
        printf("\e[32mType command: \e[36m");
        scanf("%d", &input);
        while (getchar() != '\n');

        switch (input)
        {
        case 1:
            printf("\e[0mYou choosed function \"\e[33mShow Books\e[0m\"\n\n");
            show_books();
            break;
        case 2:
            printf("\e[0mYou choosed function \"\e[33mAdd Book\e[0m\"\n");
            struct book new_book;

            printf("\e[33mWrite information about book: title, author, year, book rate(each term in new line)\n\n\e[36m");

            printf("\e[33mTitle:\e[36m ");
            fgets(new_book.title, 60, stdin);

            printf("\e[33mAuthor:\e[36m ");
            fgets(new_book.author, 50, stdin);

            printf("\e[33mYear:\e[36m ");
            scanf("%d", &new_book.year);

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &new_book.rate);

            address_of_last_book = add_book(address_of_last_book, new_book);

            if (address_of_books_list == NULL)
            {
                address_of_books_list = address_of_last_book;
            }

            printf("\n\e[33mBook Added!\n\n");

            break;
        case 3:
            printf("\e[0mYou choosed function \"\e[33mUpdate Book\e[0m\"\n");
            printf("\e[33mType index of book, which you want to update\n\n\e[36m");
            show_books();

            int book_update_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &book_update_index);
            while (getchar() != '\n')
                ;

            struct book updated_book;

            printf("\e[33mWrite information about book: title, author, year, book rate (each term in new line)\n\n\e[36m");

            printf("\e[33mTitle:\e[36m ");
            fgets(updated_book.title, 60, stdin);

            printf("\e[33mAuthor:\e[36m ");
            fgets(updated_book.author, 50, stdin);

            printf("\e[33mYear:\e[36m ");
            scanf("%d", &updated_book.year);

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &updated_book.rate);

            update_book(book_update_index, updated_book);

            printf("\n\e[33mBook Updated!\n\n");
            break;
        case 4:
            printf("\e[0mYou choosed function \"\e[33mRemove Book\e[0m\"\n");
            printf("\e[33mType index of book, which you want to remove\n\n\e[36m");
            show_books();

            int book_remove_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &book_remove_index);
            remove_book(book_remove_index);

            printf("\n\e[33mBook Removed!\n\n");
            break;
        case 5:
            printf("\e[0mYou choosed function \"\e[33mShow Customers\e[0m\"\n\n");
            show_customers();
            break;
        case 6:
            printf("\e[0mYou choosed function \"\e[33mAdd Customer\e[0m\"\n");
            customer new_customer;

            printf("\e[33mWrite information about customer: name, age, rate (each term in new line)\n\n\e[36m");

            printf("\e[33mName:\e[36m ");
            fgets(new_customer.name, 60, stdin);

            printf("\e[33mAge:\e[36m ");
            scanf("%d", &new_customer.age);

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &new_customer.rate);

            address_of_last_customer = add_customer(address_of_last_customer, new_customer);

            if (address_of_customers_list == NULL)
            {
                address_of_customers_list = address_of_last_customer;
            }

            printf("\n\e[33mCustomer Added!\n\n");

            break;
        case 7:
            printf("\e[0mYou choosed function \"\e[33mUpdate Customer\e[0m\"\n");
            printf("\e[33mType index of customer, which you want to update\n\n\e[36m");
            show_customers();

            int customer_update_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &customer_update_index);
            while (getchar() != '\n');

            customer updated_customer;

            printf("\e[33mWrite information about book: title, author, year, book rate (each term in new line)\n\n\e[36m");

            printf("\e[33mName:\e[36m ");
            fgets(updated_customer.name, 60, stdin);

            printf("\e[33mAge:\e[36m ");
            scanf("%d", &updated_customer.age);

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &updated_customer.rate);

            update_customer(customer_update_index, updated_customer);

            printf("\n\e[33mCustomer Updated!\n\n");
            break;
        case 8:
            printf("\e[0mYou choosed function \"\e[33mRemove Customer\e[0m\"\n");
            printf("\e[33mType index of customer, which you want to remove\n\n\e[36m");
            show_customers();

            int remove_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &remove_index);
            remove_customer(remove_index);

            printf("\n\e[33mCustomer Removed!\n\n");
            break;
        case 9:
            printf("exit");
            return 0;
        default:
            printf("You wrote wrong command\n");
        }
    }
}