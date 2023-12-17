#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../Assembler/asm.h"
#include "../Onegin/fileReader.h"

#ifdef DEBUG
    #define PRINT(arg) printf(arg);
#else
    #define PRINT(arg)
#endif

int registerNum(int charNum, FILE* fileName);
void cmdJmp(FILE * fileName, int cmd, int* ppos, char* arr);

int main()
{
    char *Buff = 0;

    fileRead("../Assembler/bytecode.txt", &Buff, NULL, NULL, NULL, BUFF_ONLY);

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
        case JMP:
            cmdJmp(code, 0, &pos, Buff);
            break;
        case JB:
            cmdJmp(code, '<', &pos, Buff);
            break;
        case JBE:
            cmdJmp(code, 'l', &pos, Buff);
            break;
        case JA:
            cmdJmp(code, '>', &pos, Buff);
            break;
        case JAE:
            cmdJmp(code, 'm', &pos, Buff);
            break;
        case JE:
            cmdJmp(code, '=', &pos, Buff);
            break;
        case JNE:
            cmdJmp(code, '!', &pos, Buff);
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

void cmdJmp(FILE * fileName, int cmd, int* ppos, char* arr)
{
    ++*ppos;
    switch(cmd)
    {
        case '<':
            fprintf(fileName, "jb ");
        case '>':
            fprintf(fileName, "ja ");
            break;
        case '=':
            fprintf(fileName, "je ");
            break;
        case '!':
            fprintf(fileName, "jne ");
            break;
        case 'm':
            fprintf(fileName, "jae ");
            break;
        case 'l':
            fprintf(fileName, "jbe ");
            break;
        default:
            fprintf(fileName, "jmp ");
            break;    
    }

    fprintf(fileName, "%d", arr[*ppos]);
    fprintf(fileName, "\n");
}