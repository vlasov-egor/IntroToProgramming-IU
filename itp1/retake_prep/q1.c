#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct my_struct {
    bool my_bool;        // 1 byte
    char *my_pointer;    // 4 bytes
    // int my_int;          // 8 bytes
};

int main() {
    printf("size of struct now is %d", sizeof(struct my_struct));
};