#include <stdio.h>
#include "Bsort.h"
#include <stdint.h>

int Comparator(void* int1, void* int2);

void main()
{
    int numbers[10] = {2, 5, 1, 6, 8, 16, 20, 6, 331, 1};

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", numbers[i]);
    }

    Bsort(numbers, 10, sizeof(int), Comparator);

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", numbers[i]);
    }
    
}

int Comparator(void* int1, void* int2)
{
    return (uint32_t)int1 - (uint32_t)int2;
}