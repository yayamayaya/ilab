#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "C:\Users\megas\Clearn\ilab\Onegin\fileReader.h"
#include "C:\Users\megas\Clearn\ilab\Stack\stack.h"

int arithmetics(stack *stackName, char action);

int main()
{
    char **strCode = NULL;
    int fileSize = 0;
    int stringNumber = 0;

    fileRead("code.txt", &strCode, &fileSize, &stringNumber);

    stack Stk = {0};    
    stackCtor(&Stk, 10);

    for(int pos = 0;; pos++)
    {     
        assert(pos < stringNumber);
        if (strncmp(strCode[pos], "push ", 5) == 0)
        {
            int temp = 0;
            sscanf(strCode[pos] + 5, "%d", &temp);
            stackPush(&Stk, temp);
        }
        else if (strcmp(strCode[pos], "add\0") == 0)
            arithmetics(&Stk, '+');
        else if (strcmp(strCode[pos], "sub\0") == 0)
            arithmetics(&Stk, '-');
        else if (strcmp(strCode[pos], "mult\0") == 0)
            arithmetics(&Stk, '*');
        else if (strcmp(strCode[pos], "div\0") == 0)
           arithmetics(&Stk, '/'); 
        else if (strcmp(strCode[pos], "out\0") == 0)
        {
            int temp = 0;
            while (stackPop(&Stk, &temp) != -1)
                printf("\n>> %d\n", temp);    
        }
        else if (strcmp(strCode[pos], "halt\0") == 0)
        {
            stackDtor(&Stk);
            free(strCode);
            break;
        }
        else
        {
            printf("\n\n>>>Command not found.");
            return 1;
        }
    }
}

int arithmetics(stack *stackName, char action)
{
    int temp1 = 0;
    int temp2 = 0;

    if(stackPop(stackName, &temp1))
        return 1;
    if(stackPop(stackName, &temp2))
        return 1;
       
    switch (action)
    {
    case '+':
        stackPush(stackName, temp1 + temp2);
        break;
    case '-':
        stackPush(stackName, temp1 - temp2);
        break;
    case '*':
        stackPush(stackName, temp1 * temp2);
        break;
    case '/':
        stackPush(stackName, temp1 / temp2);
        break;
    default:
        //Ошибка действия
        return 0;
        break;
    }
}
