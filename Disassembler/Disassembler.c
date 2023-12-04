#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "..\Assembler\asm.h"
#include "..\Onegin\fileSize.h"

#ifdef DEBUG
    #define PRINT(arg) printf(arg);
#else
    #define PRINT(arg)
#endif

int registerNum(int charNum, FILE* fileName);

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

    FILE * code = fopen("disassembledCode.txt", "w");


    for (int num = 0, pos = 0, temp = 0 ;; pos++)
    {
        switch (Buff[pos])
        {
        case PUSH:
            ++pos;            
            fprintf(code, "push ");
            fprintf(code, "%d\n", Buff[pos]);
            break;
        case rpush:
            ++pos;
            fprintf(code, "push ");
            registerNum(Buff[pos], code);
            break;
        case POP:
            ++pos;
            fprintf(code, "pop ");
            registerNum(Buff[pos], code);
            break;
        case ADD:
            fprintf(code, "add\n");
            break;
        case SUB:
            fprintf(code, "sub\n");
            break;
        case MULT:
            fprintf(code, "mult\n");
            break;
        case DIV:
            fprintf(code, "div\n");
            break;
        case IN:
            fprintf(code, "in\n");
            break;
        case OUT:
            fprintf(code, "out\n");
            break;
        case HALT:
            free(Buff); 
            fprintf(code, "halt");      
            return 0;
            break;
        default:
            printf("Error in computing");
            return 1;
            break;
        }
    }
}

int registerNum(int charNum, FILE* fileName)
{
    assert(1 <= charNum && charNum <= 4);
    switch (charNum)
    {
        case 1:
            fprintf(fileName, "ax\n");
            break;
        case 2:
            fprintf(fileName, "bx\n");
            break;
        case 3:
            fprintf(fileName, "cx\n");
            break;
        case 4:
            fprintf(fileName, "dx\n");
            break; 
        default:
            printf("Decompilation error");
            return 1;
            break;
    }
}