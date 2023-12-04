#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "..\Onegin\fileReader.h"
#include "asm.h"

#define DEBUG
#define CMD_PUSH ">>PUSH compiled\n"
#define CMD_ADD ">>ADD compiled\n"
#define CMD_SUB ">>SUB compiled\n"
#define CMD_MULT ">>MULT compiled\n"
#define CMD_DIV ">>DIV compiled\n"
#define CMD_OUT ">>OUT compiled\n"
#define CMD_HALT ">>HALT compiled, Compilation successful\n"
#define CMD_POP ">>POP compiled\n"
#define CMD_IN ">>IN compiled\n"
#define CMD_rpush ">>PUSH (reg) compiled\n"
#define CMD_REG ">>register found\n"
#define CMD_NUMPUSHED ">>Number was pushed\n"

#ifdef DEBUG
    #define PRINT(arg) printf(arg);
#else
    #define PRINT(arg)
#endif

int registerNum(int charNum, FILE* fileName);
int codeInFile(int codeElement, FILE* fileName, char CDM_name[]);

int main()
{
    char **strCode = NULL;
    int fileSize = 0;
    int stringNumber = 0;

    fileRead("code.txt", &strCode, &fileSize, &stringNumber);

    FILE * byteCode = fopen("bytecode.txt", "wb");

    for(int pos = 0;; pos++)
    {     
        assert(pos <= stringNumber);
        if (strncmp(strCode[pos], "push ", 5) == 0)
        {
            int temp = 0;
            if(sscanf(strCode[pos] + 5, "%d", &temp) == 0)
            {
                codeInFile(rpush, byteCode, CMD_rpush);
                registerNum(*(strCode[pos] + 5), byteCode);              
            }
            else
            {
                codeInFile(PUSH, byteCode, CMD_PUSH);
                codeInFile(temp, byteCode, CMD_NUMPUSHED);            
            }
        }
        else if (strcmp(strCode[pos], "add\0") == 0)
            codeInFile(ADD, byteCode, CMD_ADD);
        else if (strcmp(strCode[pos], "sub\0") == 0)
            codeInFile(SUB, byteCode, CMD_SUB);
        else if (strcmp(strCode[pos], "mult\0") == 0)
            codeInFile(MULT, byteCode, CMD_MULT);
        else if (strcmp(strCode[pos], "div\0") == 0)
            codeInFile(DIV, byteCode, CMD_DIV);
        else if (strcmp(strCode[pos], "out\0") == 0)
            codeInFile(OUT, byteCode, CMD_OUT);
        else if (strcmp(strCode[pos], "in\0") == 0)
            codeInFile(IN, byteCode, CMD_IN);
        else if (strncmp(strCode[pos], "pop ", 4) == 0)
        {

            codeInFile(POP, byteCode, CMD_POP);
            registerNum(*(strCode[pos] + 4), byteCode);
        }
        else if (strcmp(strCode[pos], "halt\0") == 0)           
        {
            codeInFile(HALT, byteCode, CMD_HALT);
            fclose(byteCode);
            free(strCode);
            return 0;
        }
        else
        {
            printf("\n\n>>>Compilation error.");
            return 1;
        }
    }
}

int registerNum(int charNum, FILE* fileName)
{
    assert('a' <= charNum && charNum <= 'd');
    switch (charNum)
    {
        case 'a':
            codeInFile(1, fileName, CMD_REG);
            break;
        case 'b':
            codeInFile(2, fileName, CMD_REG);
            break;
        case 'c':
            codeInFile(3, fileName, CMD_REG);
            break;
        case 'd':
            codeInFile(4, fileName, CMD_REG);
            break; 
        default:
            printf("Compilation error: incompatable register name");
            return 1;
            break;
    }
}

int codeInFile(int codeElement, FILE* fileName, char CMD_name[])
{
    int temp = codeElement;
    int *tempPointer = &temp;

    fwrite(tempPointer, sizeof(char), 1, fileName);

    PRINT(CMD_name)
}