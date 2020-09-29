//  libs declaration
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  global variables declaration
static struct books_linked_list *address_of_books_list = NULL; //  head of list of books address
static struct books_linked_list *address_of_last_book = NULL;  //  last term of list of books address

static struct customers_linked_list *address_of_customers_list = NULL; //  head of list of customers address
static struct customers_linked_list *address_of_last_customer = NULL;  //  last term of list of customers address

//  structs declaration
struct book //  struct for books
{
    char title[60];
    char author[50];
    int year;
    float rate;
};

typedef struct //  struct for customers
{
    char name[50];
    int age;
    float rate;
} customer;

//  linked-lists
struct books_linked_list //  linked list for books
{
    struct book book;
    struct books_linked_list *next; //  link for next element of list
};

struct customers_linked_list //  linked list for customers
{
    customer customer;
    struct customers_linked_list *next; //  link for next element of list
};

//  -------------------             funcs for books             -------------------
void show_books() //   all books showing
{
    struct books_linked_list *current = address_of_books_list; //  choosing first term in list

    if (current == NULL) //  check for emptiness
    {
        printf("\e[31mNothing here\n\n\e[0m");
    }
    else
    {
        int i = 0;
        while (current != NULL) //  printing
        {
            printf("\e[34mTitle: \e[0m%s", current->book.title);
            printf("\e[32mAutor: \e[0m%s", current->book.author);
            printf("\e[32mYear: \e[0m%d\n", current->book.year);
            printf("\e[32mRate: \e[0m%f\n", current->book.rate);
            printf("\e[32mIndex: \e[0m%d\n\n", i);
            current = current->next; //  step to next term of list
            i += 1;
        }
    }
}

struct books_linked_list *add_book(struct books_linked_list *after, struct book item) //  new book adding
{
    struct books_linked_list *new = (struct books_linked_list *)malloc(sizeof(struct books_linked_list)); //  allocating new book in books linked list
    new->book = item;                                                                                     //  declaring new book

    if (after != NULL)
    {
        after->next = new;
    }

    return new;
}

void update_book(int index, struct book new) //  book updating
{
    int i = 0;

    for (struct books_linked_list *current = address_of_books_list; current != NULL; current = current->next) //  loop for searching certain term
    {
        if (i == index)
        {
            current->book = new; //  book rewriting
            return;
        }

        i += 1;
    }
}

void remove_book(int index) //  book removing
{
    if (index == 0) //  case for first book
    {
        struct books_linked_list *tmp = address_of_books_list;
        address_of_books_list = address_of_books_list->next; //  book deleting
        free(tmp);
        return;
    }

    struct books_linked_list *previous = NULL;
    struct books_linked_list *current = address_of_books_list;
    auto int i = 0;

    while (current != NULL)
    {
        if (index == i) //  book searching
        {
            //  book removing
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

//  -------------------             funcs for customers             -------------------

void show_customers() //   all customers showing
{
    struct customers_linked_list *current = address_of_customers_list; //  choosing first term in list

    if (current == NULL) //  check for emptiness
    {
        printf("\e[31mNothing here\n\n\e[0m");
    }
    else
    {
        int i = 0;
        while (current != NULL) //  printing
        {
            printf("\e[34mName: \e[0m%s", current->customer.name);
            printf("\e[32mAge: \e[0m%d\n", current->customer.age);
            printf("\e[32mRate: \e[0m%f\n", current->customer.rate);
            printf("\e[32mIndex: \e[0m%d\n\n", i);
            current = current->next; //  step to next term of list
            i += 1;
        }
    }
}

struct customers_linked_list *add_customer(struct customers_linked_list *after, customer item) //  new customer adding
{
    struct customers_linked_list *new = (struct customers_linked_list *)malloc(sizeof(struct customers_linked_list)); //  allocating new customer in customers linked list
    new->customer = item;                                                                                             //  declaring new customer

    if (after != NULL)
    {
        after->next = new;
    }

    return new;
}

void update_customer(int index, customer new) //  customer updating
{
    int i = 0;

    for (struct customers_linked_list *current = address_of_customers_list; current != NULL; current = current->next) //  loop for searching certain term
    {
        if (i == index)
        {
            current->customer = new; //  customer rewriting
            return;
        }

        i += 1;
    }
}

void remove_customer(int index) //  customer removing
{
    if (index == 0) //  case for first customer
    {
        struct customers_linked_list *tmp = address_of_customers_list;
        address_of_customers_list = address_of_customers_list->next; //  customer deleting
        free(tmp);
        return;
    }

    struct customers_linked_list *previous = NULL;
    struct customers_linked_list *current = address_of_customers_list;
    auto int i = 0;

    while (current != NULL)
    {
        if (index == i) //  customer searching
        {
            //  customer removing
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

//  -------------------             main             -------------------
int main()
{
    int input;

    //  list of functionalities
    printf("\e[33mFunctionalities:\n\
    1 - Show Books\n\
    2 - Add Book\n\
    3 - Update Book\n\
    4 - Remove Book\n\
    5 - Show Customers\n\
    6 - Add Customer\n\
    7 - Update Customer\n\
    8 - Remove Customer\n\
    9 - Exit\n\n");

    //  main loop
    while ("True")
    {
        //  scanning input
        printf("\e[32mType command: \e[36m");
        scanf("%d", &input);

        //  filter for \n
        while (getchar() != '\n')
            ;

        //  switch for each function
        switch (input)
        {
        case 1:
            //  books showing

            printf("\e[0mYou choosed function \"\e[33mShow Books\e[0m\"\n\n");
            show_books();
            break;
        case 2:
            //  book adding

            printf("\e[0mYou choosed function \"\e[33mAdd Book\e[0m\"\n");
            struct book new_book;

            printf("\e[33mWrite information about book: title, author, year, book rate(each term in new line)\n\n\e[36m");

            printf("\e[33mTitle:\e[36m ");
            fgets(new_book.title, 60, stdin); //  title reading

            printf("\e[33mAuthor:\e[36m ");
            fgets(new_book.author, 50, stdin); //  author reading

            printf("\e[33mYear:\e[36m ");
            scanf("%d", &new_book.year); //  year reading

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &new_book.rate); //  book rate reading

            address_of_last_book = add_book(address_of_last_book, new_book); //  adding new book in linked list

            //  check for emptiness
            if (address_of_books_list == NULL)
            {
                address_of_books_list = address_of_last_book;
            }

            //  result printing
            printf("\n\e[33mBook Added!\n\n");

            break;
        case 3:
            //  book updating

            printf("\e[0mYou choosed function \"\e[33mUpdate Book\e[0m\"\n");
            printf("\e[33mType index of book, which you want to update\n\n\e[36m");
            show_books();

            int book_update_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &book_update_index); //  scanning book index

            //  filter for \n
            while (getchar() != '\n')
                ;

            struct book updated_book;

            printf("\e[33mWrite information about book: title, author, year, book rate (each term in new line)\n\n\e[36m");

            printf("\e[33mTitle:\e[36m ");
            fgets(updated_book.title, 60, stdin); //  title reading

            printf("\e[33mAuthor:\e[36m ");
            fgets(updated_book.author, 50, stdin); //  author reading

            printf("\e[33mYear:\e[36m ");
            scanf("%d", &updated_book.year); //  year reading

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &updated_book.rate); //  book rate reading

            update_book(book_update_index, updated_book); //  book updating

            //  result printing
            printf("\n\e[33mBook Updated!\n\n");
            break;
        case 4:
            //  book removing

            printf("\e[0mYou choosed function \"\e[33mRemove Book\e[0m\"\n");
            printf("\e[33mType index of book, which you want to remove\n\n\e[36m");
            show_books();

            int book_remove_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &book_remove_index); //  book index reading
            remove_book(book_remove_index);  //  book removing

            //  result printing
            printf("\n\e[33mBook Removed!\n\n");
            break;
        case 5:
            //  customers showing

            printf("\e[0mYou choosed function \"\e[33mShow Customers\e[0m\"\n\n");
            show_customers();
            break;
        case 6:
            //  customer adding

            printf("\e[0mYou choosed function \"\e[33mAdd Customer\e[0m\"\n");
            customer new_customer;

            printf("\e[33mWrite information about customer: name, age, rate (each term in new line)\n\n\e[36m");

            printf("\e[33mName:\e[36m ");
            fgets(new_customer.name, 60, stdin); // name reading

            printf("\e[33mAge:\e[36m ");
            scanf("%d", &new_customer.age); //  age reading

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &new_customer.rate); //  customer rate reading

            address_of_last_customer = add_customer(address_of_last_customer, new_customer); //  adding new customer in linked list

            //  check for emptiness
            if (address_of_customers_list == NULL)
            {
                address_of_customers_list = address_of_last_customer;
            }

            //  result printing
            printf("\n\e[33mCustomer Added!\n\n");

            break;
        case 7:
            //  customer updating

            printf("\e[0mYou choosed function \"\e[33mUpdate Customer\e[0m\"\n");
            printf("\e[33mType index of customer, which you want to update\n\n\e[36m");
            show_customers();

            int customer_update_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &customer_update_index); //  scanning customer index

            //  filter for \n
            while (getchar() != '\n')
                ;

            customer updated_customer;

            printf("\e[33mWrite information about book: title, author, year, book rate (each term in new line)\n\n\e[36m");

            printf("\e[33mName:\e[36m ");
            fgets(updated_customer.name, 60, stdin); //  name reading

            printf("\e[33mAge:\e[36m ");
            scanf("%d", &updated_customer.age); //  age reading

            printf("\e[33mRate:\e[36m ");
            scanf("%f", &updated_customer.rate); //  customer rate reading

            update_customer(customer_update_index, updated_customer); //  updating

            //  result printing
            printf("\n\e[33mCustomer Updated!\n\n");
            break;
        case 8:
            //  customer removing

            printf("\e[0mYou choosed function \"\e[33mRemove Customer\e[0m\"\n");
            printf("\e[33mType index of customer, which you want to remove\n\n\e[36m");
            show_customers();

            int remove_index;
            printf("\e[32mType index: \e[36m");
            scanf("%d", &remove_index);    //  customer index reading
            remove_customer(remove_index); //  customer removing

            //  result printing
            printf("\n\e[33mCustomer Removed!\n\n");
            break;
        case 9:
            //  exit case

            printf("exit");
            return 0;
        default:
            printf("\n\e[31mYou wrote wrong command, write integer from 1 to 9\n");
            //  list of functionalities
            printf("\e[33mFunctionalities:\n\
            1 - Show Books\n\
            2 - Add Book\n\
            3 - Update Book\n\
            4 - Remove Book\n\
            5 - Show Customers\n\
            6 - Add Customer\n\
            7 - Update Customer\n\
            8 - Remove Customer\n\
            9 - Exit\n\n");
        }
    }
}