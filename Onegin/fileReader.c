#include <stdio.h>
#include "fileSize.h"
#include "StringNumber.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "fileReader.h"

#define DEBUG
#define FILE_SIZE "\n>>Size of file is: %d\n", size
#define STRING_NUMBER ">>Number of strings is: %d\n\n", strs

#ifdef DEBUG
    #define PRINT(arg) printf(arg);
#else
    #define PRINT(arg) printf("");
#endif

int fileRead(char *fileName, char** text ,char ***strPointer, int *sizeOfFile, int *numberOfStrings, int option)
{
    assert(fileName != NULL);
    assert(text != NULL || strPointer != NULL);
    assert(1 <= option && option <= 3);
    
    FILE * file = fopen(fileName, "rb");              //Открываем файл, проверка на существование файла и его открытие
    if(file == NULL)
    {
        printf(">>>Can't open the file.\n");
        return 1;
    }

    int size = 0;                                           //Размер файла в символах
    int strs = 0;                                           //Количество строк в файле

    fileSize(file, &size);

    PRINT(FILE_SIZE)
    char *Buff = (char *)calloc(size + 1, sizeof(char));       //Создаем массив, куда запишем весь файл

    rewind(file);                                        //Возвращаемся в начало файла
    if(fread(Buff, sizeof(char), size, file) < size)       //Условие на ошибки
    {
        printf(">>>Text reading error.\n");
        return 1;
    }
    fclose(file); 


    if(option != STRS_ONLY)
        *text = Buff;
    if(option != BUFF_ONLY)
    {
        stringNumber(Buff, &strs);
        PRINT(STRING_NUMBER)

        char **strfile = (char **)calloc(strs, sizeof(char *));          //Создаём массив указателей на начала строк, размер массива - количество строк в тексте

        strfile[0] = &Buff[0];
        for (int i = 1; i < strs; i++)
        {
            strfile[i] = strchr(strfile[i - 1], '\0') + 1;
            if (*strfile[i] == '\n')
                strfile[i] += 1;
        }

        *strPointer = strfile;
    }

    if(sizeOfFile != NULL)
    {
        assert(sizeOfFile != NULL);
        *sizeOfFile = size;
    } 
    if(numberOfStrings != NULL)
    {
        assert(numberOfStrings != NULL);
        *numberOfStrings = strs;
    } 
}