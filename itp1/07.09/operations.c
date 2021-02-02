#include <stdio.h>

int main () {

    int x, y;
    
    scanf("%d %d", &x, &y);
    int sum = x+y;
    int dif = x-y;
    int mul = x*y;
    int div = x/y;

    printf("%d %d %d %d %d %d", x, y, sum, dif, mul, div);

    return 0;
}