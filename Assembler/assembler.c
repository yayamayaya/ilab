#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "C:\Users\megas\Clearn\ilab\Onegin\fileSize.h"
#include "C:\Users\megas\Clearn\ilab\Onegin\StringNumber.h"


int main()
{
    FILE * code = fopen("code.txt", "rb");              //Открываем файл, проверка на существонвание файла и его открытие
    if(code == NULL)
    {
        printf("Can't open the file.");
        return 1;
    }

    int size = 0;                                           //Размер файла в символах
    int strs = 0;                                           //Количество строк в файле

    fileSize(code, &size);

    //printf("\nSize of file is: %d\n", size);
    char *Buff = (char *)calloc(size + 1, sizeof(char));       //Создаем массив, куда запишем весь файл

    rewind(code);                                        //Возвращаемся в начало файла
    if(fread(Buff, sizeof(char), size, code) < size)       //Условие на ошибки
    {
        printf(">>>text reading error");
        return 1;
    }
    
    fclose(code);

    stringNumber(Buff, &strs);

    char **strCode = (char **)calloc(strs, sizeof(char *));          //Создаём массив указателей на начала строк, размер массива - количество строк в тексте

    strCode[0] = &Buff[0];
    for (int i = 1; i < strs; i++)
    {
        strCode[i] = strchr(*(strCode + i - 1), '\0') + 1;
        if (*strCode[i] == '\n')
            strCode[i] += 1;
    }

    FILE * bytecode = fopen("bytecode.txt", "w");

    for(int pos = 0; pos < strs; pos++)
    {     
        if (strncmp(strCode[pos], "push ", 5) == 0)
        {
            fprintf(bytecode, "%d ", 0);
            int temp = 0;
            sscanf(strCode[pos] + 5, "%d", &temp);
            fprintf(bytecode, "%d ", temp);
        }
        else if (strcmp(strCode[pos], "plus\0") == 0)
            fprintf(bytecode, "%d ", 101);
        else if (strcmp(strCode[pos], "add\0") == 0)
            fprintf(bytecode, "%d ", 11);
        else if (strcmp(strCode[pos], "sub\0") == 0)
            fprintf(bytecode, "%d ", 12);
        else if (strcmp(strCode[pos], "mult\0") == 0)
            fprintf(bytecode, "%d ", 13);
        else if (strcmp(strCode[pos], "div\0") == 0)
            fprintf(bytecode, "%d ", 14);
        else if (strcmp(strCode[pos], "out\0") == 0)
            fprintf(bytecode, "%d ", 21);
        else if (strcmp(strCode[pos], "halt\0") == 0)
        {
            fprintf(bytecode, "%d", 210);
            printf(">>> Compilation successful\n");
            return 0;
        }
        else
        {
            printf("\n\n>>>Compilation error. Command not found.");
            return 1;
        }
    }
}


//0 - push
//11 - add
//12 - sub
//13 - mult
//14 - div
//21 - out
//210 - halt