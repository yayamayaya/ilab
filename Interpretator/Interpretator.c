#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "C:\Users\megas\Clearn\ilab\Onegin\fileSize.h"
#include "C:\Users\megas\Clearn\ilab\Stack\stack.h"
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

    printf("\nSize of file is: %d\n", size);
    char *Buff = (char *)calloc(size + 1, sizeof(char));       //Создаем массив, куда запишем весь файл

    rewind(code);                                        //Возвращаемся в начало файла
    if(fread(Buff, sizeof(char), size, code) < size)       //Условие на ошибки
    {
        printf(">>>text reading error");
        return 1;
    }
    
    fclose(code);

    stringNumber(Buff, &strs);

    for(int i = 0; i < size; i++)
        printf(" %d ", Buff[i]);

    char **strCode = (char **)calloc(strs, sizeof(char *));          //Создаём массив указателей на начала строк, размер массива - количество строк в тексте

    strCode[0] = &Buff[0];
    for (int i = 1; i < strs; i++)
    {
        strCode[i] = strchr(*(strCode + i - 1), '\0') + 1;
        if (*strCode[i] == '\n')
            strCode[i] += 1;
    }

    stack Stk = {0};    
    stackCtor(&Stk, 10);

    for(int pos = 0, temp1 = 0, temp2 = 0; pos < strs; pos++)
    {     
        if (strncmp(strCode[pos], "push ", 5) == 0)
        {
            temp1 = 0;
            sscanf(strCode[pos] + 5, "%d", &temp1);
            stackPush(&Stk, temp1);
        }
        else if (strcmp(strCode[pos], "add\0") == 0)
        {
            if(stackPop(&Stk, &temp1))
                return 1;
            if(stackPop(&Stk, &temp2))
                return 1;
            stackPush(&Stk, temp1 + temp2);
        }
        else if (strcmp(strCode[pos], "sub\0") == 0)
        {
            if(stackPop(&Stk, &temp1))
                return 1;
            if(stackPop(&Stk, &temp2))
                return 1;
            stackPush(&Stk, temp2 - temp1);
        }
        else if (strcmp(strCode[pos], "mult\0") == 0)
        {
            if(stackPop(&Stk, &temp1))
                return 1;
            if(stackPop(&Stk, &temp2))
                return 1;
            stackPush(&Stk, temp2 * temp1);
        }
        else if (strcmp(strCode[pos], "div\0") == 0)
        {
            if(stackPop(&Stk, &temp1))
                return 1;
            if(stackPop(&Stk, &temp2))
                return 1;
            stackPush(&Stk, temp2 / temp1);
        }
        else if (strcmp(strCode[pos], "out\0") == 0)
        {
            temp1 = 0;
            while (stackPop(&Stk, &temp1) != -1)
                printf("\n>> %d\n", temp1);    
        }
        else if (strcmp(strCode[pos], "halt\0") == 0)
        {
            stackDtor(&Stk);
            free(strCode);
            free(Buff);
            break;
        }
        else
        {
            printf("\n\n>>>Command not found.");
            return 1;
        }
    }
}