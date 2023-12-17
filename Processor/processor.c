#include <stdio.h>
#include <stdlib.h>
#include "../Stack/stack.h"
#include "../Assembler/asm.h"
#include  "../Onegin/fileReader.h"

struct Processor 
{
    stack Stack;
    int Register[4];
};

int arithmetics(stack *stackName, char action);
int condJMP(stack *stackName, char *arr, int *ip, char condition);
int jmp(char* arr, int *ip);

int main(int argc, char** argv) // argc argv
{
    char* Buff = 0;
    int BuffSize = 0;

    fileRead(argv[1], &Buff, NULL, &BuffSize, NULL, BUFF_ONLY);

    struct Processor processor = {0};
    stackCtor(&processor.Stack, 10);


    for (int num = 0, ip = 0, temp = 0 ; ip < BuffSize;)
    {
        switch (Buff[ip++])
        {
        case PUSH:
            ++ip;
            stackPush(&processor.Stack, Buff[ip]);
            ip++;
            break;
        case rpush:
            ++ip;
            stackPush(&processor.Stack, processor.Register[Buff[ip] - 1]);
            ip++;
            break;
        case POP:
            ++ip;
            stackPop(&processor.Stack, processor.Register + Buff[ip] - 1);
            ip++;
            break;
        case ADD:
            arithmetics(&processor.Stack, '+');
            ip++;
            break;
        case SUB:
            arithmetics(&processor.Stack, '-');
            ip++;
            break;
        case MULT:
            arithmetics(&processor.Stack, '*');
            ip++;
            break;
        case DIV:
            arithmetics(&processor.Stack, '/');
            ip++;
            break;
        case IN:
            printf("Enter the number:\n");
            scanf("%d", &temp);

            stackPush(&processor.Stack, temp);
            ip++;
            break;
        case JMP:
            jmp(Buff, &ip);
            break;
        case JB:
            condJMP(&processor.Stack, Buff, &ip, '<');
            break;
        case JBE:
            condJMP(&processor.Stack, Buff, &ip, 'l');
            break;
        case JA:
            condJMP(&processor.Stack, Buff, &ip, '>');
            break;
        case JAE:
            condJMP(&processor.Stack, Buff, &ip, 'm');
            break;
        case JE:
            condJMP(&processor.Stack, Buff, &ip, '=');
            break;
        case JNE:
            condJMP(&processor.Stack, Buff, &ip, '!');
            break;
        case OUT:
            while (stackPop(&processor.Stack, &temp) != -1)    //пустой поп
                printf("\n--> %d\n", temp);    
            ip++;
            break;
        case HALT:
            free(Buff);         
            stackDtor(&processor.Stack);
            return 0;
            break;
        default:
            continue;
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

int jmp(char* arr, int *ip)
{
    *ip = arr[*ip + 1];
}

int condJMP(stack *stackName, char *arr, int *ip, char condition)
{
    int temp1 = 0;
    int temp2 = 0;

    if(stackPop(stackName, &temp2))
        return 1;
    if(stackPop(stackName, &temp1))
        return 1;

    stackPush(stackName, temp1);
    stackPush(stackName, temp2);

    switch(condition)
    {
        case '<':
            if(temp2 < temp1)   //меньше
                jmp(arr, ip);
            else
                *ip += 2;
            break;
        case '>':
            if(temp2 > temp1)   //больше
                jmp(arr, ip);
            else
                *ip += 2;
            break;
        case '=':
            if(temp2 == temp1)  //равно
                jmp(arr, ip);
            else
                *ip += 2;
            break;
        case '!':
            if(temp2 != temp1)  //не равно
                jmp(arr, ip);
            else
                *ip += 2;
            break;
        case 'm':
            if(temp2 >= temp1)  //больше или равно
                jmp(arr, ip);
            else
                *ip += 2;
            break;
        case 'l':
            if(temp2 <= temp1)  //меньше или равно
                jmp(arr, ip);
            else
                *ip += 2;
            break;
        default:
            printf("\n>>ERROR\n\n");
            break;    
    }
}

//Сделать call, ret, сделать оперативную память, сделать битовые маски