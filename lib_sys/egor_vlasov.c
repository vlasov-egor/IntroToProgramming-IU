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
const int INF = 100000000;

//  structs declaration
struct book
{
    char title[60];
    char author[50];
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
    struct book;
    struct books_linked_list *last;
};


//  funcs for books

void show_books () {
    printf("None");
}

void add_book () {
    printf("None");
}

void update_book () {
    printf("None");
}

void remove_book () {
    printf("None");
}


//  funcs for customers

void show_customers () {
    printf("None");
}

void add_customer () {
    printf("None");
}

void update_customer () {
    printf("None");
}

void remove_customer () {
    printf("None");
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
            printf("You choosed case %d\n", input);
            break;
        case 2:
            printf("You choosed case %d\n", input);
            break;
        case 3:
            printf("You choosed case %d\n", input);
            break;
        case 4:
            printf("You choosed case %d\n", input);
            break;
        case 5:
            printf("You choosed case %d\n", input);
            break;
        case 6:
            printf("You choosed case %d\n", input);
            break;
        case 7:
            printf("You choosed case %d\n", input);
            break;
        case 8:
            printf("You choosed case %d\n", input);
            break;
            printf("You choosed case %d\n", input);
        case 9:
            printf("exit");
            return 0;
        default:
            printf("You wrote wrong command\n");
        }
    }
}