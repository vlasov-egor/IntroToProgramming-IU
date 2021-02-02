#include <stdio.h>
#include <stdlib.h>

struct student
{
    char *name;
    char *surname;
    int group;

    struct
    {
        int year;
        char* month;
        int day;
    } exam_day;
};

int main()
{
    struct student A;
    A.name = "Egor";
    A.surname = "Vlasov";
    A.group = 5;
    A.exam_day.year = 2020;
    A.exam_day.month = "September";
    A.exam_day.day = 29;

    printf("name = %s, surname = %s, group = %d\n", A.name, A.surname, A.group);
    printf("exam: day = %d, month = %s, year = %d", A.exam_day.day, A.exam_day.month, A.exam_day.year);
}