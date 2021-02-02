#include <stdio.h>

void pyramide(int n)
{
    int hmSpaces = n - 1;
    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < hmSpaces; ++k)
        {
            printf(" ");
        }
        for (int k = 0; k < 2 * i + 1; ++k)
        {
            printf("*");
        }
        hmSpaces--;
        printf("\n");
    }
}

int main()
{
    int n = 0;
    scanf("%d", n);
    pyramide(n);
    return 0;
}