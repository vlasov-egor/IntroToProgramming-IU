#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 100;
    int* p = &x;

    printf("%d", *p);
}