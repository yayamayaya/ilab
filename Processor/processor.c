#include <stdio.h>
#include "C:\Users\megas\Clearn\ilab\Stack\stack.h"

int main()
{
    FILE * bytecode = fopen("../Assembler/bytecode.txt", "r");       //Открываем файл

    stack memory = {0};
    stackCtor(&memory, 10);

    for (int num = 0, temp1 = 0, temp2 = 0;; fscanf(bytecode, "%d", &num))
    {
        getc(bytecode);
        switch (num)
        {
        case 0:
            fscanf(bytecode, "%d", &num);
            stackPush(&memory, num);
            
            break;
        case 11:
            if(stackPop(&memory, &temp1))
                return 1;
            if(stackPop(&memory, &temp2))
                return 1;
            stackPush(&memory, temp2 + temp1);
            break;
        case 12:
            if(stackPop(&memory, &temp1))
                return 1;
            if(stackPop(&memory, &temp2))
                return 1;
            stackPush(&memory, temp2 - temp1);
            break;
        case 13:
            if(stackPop(&memory, &temp1))
                return 1;
            if(stackPop(&memory, &temp2))
                return 1;
            stackPush(&memory, temp2 * temp1);
            break;
        case 14:
            if(stackPop(&memory, &temp1))
                return 1;
            if(stackPop(&memory, &temp2))
                return 1;
            stackPush(&memory, temp2 / temp1);
            break;
        case 21:
            temp1 = 0;
            while (stackPop(&memory, &temp1) != -1)
                printf("\n>> %d\n", temp1);    
            break;
        case 210:
            fclose(bytecode);          
            stackDtor(&memory);
            return 0;
        default:
            printf("Error in computing");
            return 1;
        }
    }
}