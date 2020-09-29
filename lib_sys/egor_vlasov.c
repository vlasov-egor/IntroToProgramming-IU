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
            printf("\e[32mIndex: \e[0m%d\n", i);
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
        while(getchar() != '\n');

        switch (input)
        {
        case 1:
            printf("\e[0mYou choosed function \"\e[33mShow Books\e[0m\"\n\n");
            show_books();
            printf("\n");
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

            int update_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &update_index);
            while(getchar() != '\n');

            struct book updated_book;

            printf("\e[33mWrite information about book: title, author, year, book rate(each term in new line)\n\n\e[36m");

            printf("\e[33mTitle:\e[36m ");
            fgets(updated_book.title, 60, stdin);

            printf("\e[33mAuthor:\e[36m ");
            fgets(updated_book.author, 50, stdin);

            printf("\e[33mYear:\e[36m ");
            scanf("%d", &updated_book.year);

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &updated_book.rate);

            update_book(update_index, updated_book);

            printf("\n\e[33mBook Updated!\n\n");
            break;
        case 4:
            printf("\e[0mYou choosed function \"\e[33mRemove Book\e[0m\"\n");
            printf("\e[33mType index of book, which you want to remove\n\n\e[36m");
            show_books();

            int remove_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &remove_index);
            remove_book(remove_index);

            printf("\n\e[33mBook Removed!\n\n");
            break;
        case 5:
            printf("You choosed function \"\e[33mShow Customers\e[0m\"\n");
            show_customers();
            break;
        case 6:
            printf("You choosed function \"\e[33mAdd customer\e[0m\"\n");
            add_customer();
            break;
        case 7:
            printf("You choosed function \"\e[33mUpdate customer\e[0m\"\n");
            update_customer();
            break;
        case 8:
            printf("You choosed function \"\e[33mRemove customer\e[0m\"\n");
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