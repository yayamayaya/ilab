#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int *Arr = (int *)calloc(10, sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        Arr[i] = i;
        printf("%d", Arr[i]);
    }

    &Arr[10] = calloc(1, sizeof(long long int));

    //10101010101010;
    

    for (int i = 0; i < 10; i++)
    {
        printf(" %ld", Arr[i]);
    }
}