#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INF = 100000000;

int main()
{
    int arrayLen;
    printf("Enter the array size: ");
    scanf("%d", &arrayLen);
    printf("Enter an array of integers (they must be positive less than %d): ", INF);
    int *array = malloc(arrayLen * sizeof(int));
    int maxNumber = 0;
    int minNumber = INF;
    for (int i = 0; i < arrayLen; i++)
    {
        scanf("%d", &array[i]);
        if (array[i] > maxNumber)
        {
            maxNumber = array[i];
        }
        if (array[i] < minNumber)
        {
            minNumber = array[i];
        }
    }
    int mapSize = maxNumber - minNumber + 1;
    bool *map = calloc(mapSize, sizeof(bool));
    for (int i = 0; i < arrayLen; i++)
    {
        if (!map[array[i]])
        {
            map[array[i]] = true;
            printf("%d ", array[i]);
        }
    }
    printf("\n");
    free(map);
    free(array);
}