#include <stdio.h>
#include <stdlib.h>

struct Student {
    char* name;
    float gpa;
    struct Student* neighbour;
};

struct Student* get_max_grade(struct Student** students, int len) {
    float max_grade = 0;
    struct Student* coolest_man = 0;
    for (int i = 0; i < len; i++) {
        if (students[i]->gpa > max_grade) {
            coolest_man = students[i];
            max_grade = students[i] -> gpa;
        }
        
    }
    return coolest_man;
}

int main() {
    struct Student* students[2];

    students[0] = malloc(sizeof(struct Student));
    students[1] = malloc(sizeof(struct Student));

    students[0]->name = "Egor";
    students[0]->gpa = 2.0;
    students[0]->neighbour = students[1];

    students[1]->name = "AlexStrNik";
    students[1]->gpa = 3.0;
    students[1]->neighbour = students[0];

    printf("student with highest grade is %s", get_max_grade(students, 2)->name);
}