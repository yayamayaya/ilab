#include <stdio.h>
#include <stdlib.h>
#include "..\Stack\stack.h"
#include "..\Assembler\asm.h"
#include "..\Onegin\fileSize.h"

#ifdef DEBUG
    #define PRINT(arg) printf(arg);
#else
    #define PRINT(arg)
#endif

struct Processor 
{
    stack Stack;
    int Register[4];
};

int arithmetics(stack *stackName, char action);

int main()
{
    FILE * bytecode = fopen("../Assembler/bytecode.txt", "rb");
    if(bytecode == NULL)
    {
        printf("Can't open the file.");
        return 1;
    }      

    int size = 0;                                          

    fileSize(bytecode, &size);
    char *Buff = (char *)calloc(size + 1, sizeof(char));      

    rewind(bytecode);                               
    if(fread(Buff, sizeof(char), size, bytecode) < size)      
    {
        printf(">>>text reading error");
        return 1;
    }
    fclose(bytecode); 

    struct Processor processor = {0};
    stackCtor(&processor.Stack, 10);


    for (int num = 0, pos = 0, temp = 0 ;; pos++)
    {
        switch (Buff[pos])
        {
        case PUSH:
            ++pos;
            stackPush(&processor.Stack, Buff[pos]);
            break;
        case rpush:
            ++pos;
            stackPush(&processor.Stack, processor.Register[Buff[pos] - 1]);
            break;
        case POP:
            ++pos;
            stackPop(&processor.Stack, processor.Register + Buff[pos] - 1);
            break;
        case ADD:
            arithmetics(&processor.Stack, '+');
            break;
        case SUB:
            arithmetics(&processor.Stack, '-');
            break;
        case MULT:
            arithmetics(&processor.Stack, '*');
            break;
        case DIV:
            arithmetics(&processor.Stack, '/');
            break;
        case IN:
            printf("Enter the number:\n");
            scanf("%d", &temp);

            stackPush(&processor.Stack, temp);
            break;
        case OUT:
            while (stackPop(&processor.Stack, temp) != -1)    //пустой поп
                printf("\n--> %d\n", temp);    
            break;
        case HALT:
            free(Buff);         
            stackDtor(&processor.Stack);
            return 0;
            break;
        default:
            printf("Error in computing");
            return 1;
            break;
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