#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "StringNumber.h"
#include "fileSize.h"
#include "Bsort.h"
#include "Swap.h"
#include <ctype.h>

typedef struct string {
    char *strPointer;
    int strLeng;
} string;

int strCmp(void *string1, void *string2);
void reverseBsort(char **arrPoint, int size);
int reverseStrCmp(void *s1, void *s2);
void StrPrint(char **arrPoint, int strNumber);
void stringPrint(string *strings, int strNumber);

int main() 
{
    FILE * strings = fopen("stroki.txt", "rb");              //Открываем файл, проверка на существонвание файла и его открытие
    if(strings == NULL)
    {
        printf("Can't open the file.");
        return 1;
    }

    int size = 0;                                           //Размер файла в символах
    int strs = 0;                                           //Количество строк в файле

    fileSize(strings, &size);

    printf("\nSize of file is: %d\n", size);
    char *Buff = (char*)calloc(size + 1, sizeof(char));       //Создаем массив, куда запишем весь файл

    rewind(strings);                                        //Возвращаемся в начало файла
    if(fread(Buff, sizeof(char), size, strings) < size)       //Условие на ошибки
    {
        printf(">>>text reading error");
        return 1;
    }
    
    fclose(strings);

    stringNumber(Buff, &strs);
    printf("Number of strings is: %d\n\n", strs);

    string *stroki = (string *)calloc(strs, sizeof(string));          //Создаём массив указателей на начала строк, размер массива - количество строк в тексте

    stroki[0].strPointer = &Buff[0];
    for (int i = 1; i < strs; i++)
    {
        stroki[i].strPointer = strchr((stroki + i - 1)-> strPointer, '\0') + 1; 
        stroki[i - 1].strLeng = stroki[i].strPointer - stroki[i - 1].strPointer;
        if (*stroki[i].strPointer == '\n')
            stroki[i].strPointer += 1;
    }
    stringPrint(stroki, strs);

    printf("\nSorting in alphabet order:\n\n");
    Bsort(stroki, strs, sizeof(string), strCmp);
    stringPrint(stroki, strs);

    printf("\nSorting in alphabet oreder from the end:\n\n");
    Bsort(stroki, strs, sizeof(string), reverseStrCmp);
    stringPrint(stroki, strs);

    printf("\nPrinting original text: \n\n");
    for(int i = 0; i < size; i++)
        printf("%c", Buff[i]);

    free(stroki);
    free(Buff);
}

int strCmp(void *point1, void *point2)                              //Сравнение строк
{
    int pos = 0;
    string *p1 = (string *)point1;
    string *p2 = (string *)point2;
    
    while (*((p1-> strPointer) + pos) != '\0' && *((p2-> strPointer) + pos) != '\0' && *((p1-> strPointer) + pos) == *((p2-> strPointer) + pos))        //EOF просмотреть
        pos++;

    return (*((p1-> strPointer) + pos) - *((p2-> strPointer) + pos));
}

int reverseStrCmp(void *point1, void *point2)                       //Сравнение строк с конца
{
    string *p1 = (string *)point1;
    string *p2 = (string *)point2;

    int pos1 = p1-> strLeng - 1;
    int pos2 = p2-> strLeng - 1;
    
    while(isalpha(*((p1-> strPointer) + pos1)) == 0 && *((p1-> strPointer) + pos1) != '\n')          //Игнорируем знаки препинания
        --pos1;
    while(isalpha(*((p2-> strPointer) + pos2)) == 0 && *((p2-> strPointer) + pos2) != '\n')       
        --pos2; 

    while (*((p1-> strPointer) + pos1) != '\0' && *((p2-> strPointer) + pos2) != '\0' && *((p1-> strPointer) + pos1) == *((p2-> strPointer) + pos2))
    {
        pos1--;
        pos2--;
    }
    
    return (*((p1-> strPointer) + pos1) - *((p2-> strPointer) + pos2));
}

void stringPrint(string* strings, int strNumber)
{
    for (int i = 0; i < strNumber; i++)
        puts((strings + i)-> strPointer );
}