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