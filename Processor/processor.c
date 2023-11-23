#include <stdio.h>
#include <stdlib.h>
#include "..\Stack\stack.h"
#include "..\Assembler\asm.h"
#include "..\Onegin\fileSize.h"

struct Processor 
{
    stack Stack;
    int Register[4];
};

int main()
{
    FILE * bytecode = fopen("../Assembler/bytecode.txt", "r");      

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

    for (int num = 0, temp1 = 0, temp2 = 0, pos = 0, ch = 0;;)
    {
        sscanf(Buff + pos, "%d %n", &num, &ch);
        pos += ch;

        switch (num)
        {
        case PUSH:
            sscanf(Buff + pos, "%d %n", &num, &ch);
            pos += ch;

            stackPush(&processor.Stack, num);
            
            break;
        case rpush:
            sscanf(Buff + pos, "%d %n", &temp1, &ch);
            pos += ch;

            stackPush(&processor.Stack, processor.Register[temp1 - 1]);

            break;
        case POP:
            sscanf(Buff + pos, "%d %n", &temp1, &ch);
            pos += ch;

            stackPop(&processor.Stack, processor.Register + temp1 - 1);
            
            break;
        case ADD:
            if(stackPop(&processor.Stack, &temp1))
                return 1;
            if(stackPop(&processor.Stack, &temp2))
                return 1;
            stackPush(&processor.Stack, temp2 + temp1);
            break;
        case SUB:
            if(stackPop(&processor.Stack, &temp1))
                return 1;
            if(stackPop(&processor.Stack, &temp2))
                return 1;
            stackPush(&processor.Stack, temp2 - temp1);
            break;
        case MULT:
            if(stackPop(&processor.Stack, &temp1))
                return 1;
            if(stackPop(&processor.Stack, &temp2))
                return 1;
            stackPush(&processor.Stack, temp2 * temp1);
            break;
        case DIV:
            if(stackPop(&processor.Stack, &temp1))
                return 1;
            if(stackPop(&processor.Stack, &temp2))
                return 1;
            stackPush(&processor.Stack, temp2 / temp1);
            break;
        case IN:
            printf("Enter the number:\n");
            scanf("%d", &temp1);

            stackPush(&processor.Stack, temp1);
            break;
        case OUT:
            temp1 = 0;
            while (stackPop(&processor.Stack, &temp1) != -1)
                printf("\n>> %d\n", temp1);    
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