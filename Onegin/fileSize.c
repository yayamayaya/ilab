#include <stdio.h>

//Возвращает размер файла с учетом \r

void fileSize(FILE * fileName, int* Size) 
{ 
    fseek(fileName, 0, SEEK_END);
    *Size = ftell(fileName);
}