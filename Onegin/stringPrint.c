#include <stdio.h>

void stringPrint(char** arrPoint, int strNumber)
{
    for (int i = 0; i < strNumber; i++)
        puts(arrPoint[i]);
}