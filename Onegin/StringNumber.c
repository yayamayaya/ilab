#include <stdio.h>

void stringNumber(char* arrPoint, int* Count)
{
    int i = 0;
    int count = 0;      // Если последний элемент \n  - не нужно + 1

    while (arrPoint[i] != '\0')
    {
        if (arrPoint[i] == '\r')
        {
            arrPoint[i] = '\0';
            count++;
            i += 2;
            continue;
        };
        if (arrPoint[i] == '\n')
        {
            arrPoint[i] = '\0';
            count++;
        }
        i++;
    }

    if(arrPoint[i - 1] != '\0' && arrPoint[i - 1] != '\n')
        count++;

    *Count = count;
}
