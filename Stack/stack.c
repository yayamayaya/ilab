#include "stack.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void stackCtor(stack *stk, int capacity)
{
    stk-> data = (int *)calloc(capacity + 6, sizeof(int));      //Проверка на каллок
    if(stk-> data == NULL)
    {
        printf("Memory allocation error");
        exit(1);
    }

    stk-> size = 0;
    stk-> capacity = capacity;

    printf("\n>>Stack has been constructed with the capacity of %d\n", stk-> capacity);
}

void stackDtor(stack *stk)
{
    stk-> capacity = 0;
    stk-> size = 0;

    free(stk-> data);
    stk-> data = NULL;

    printf("\n>> Stack has been destructed.\n");
}

void stackPush(stack *stk, int num)
{
    if (stk-> size == stk-> capacity)
    {
        if(realloc(stk-> data, 2 * stk-> capacity * sizeof(int)) == NULL)         //realloc в assert'е
        {
            printf("Reallocation error");
            exit(1);
        }

        stk ->capacity *= 2;

        printf("\n>> Not enough capacity. Capacity has been doubled. Current capacity - %d\n", stk-> capacity);
    }
    
    *(stk-> data + stk-> size) = num;
    stk-> size++;

    printf(">> %d was pushed on position %d.\n", *(stk-> data + stk-> size - 1), stk-> size);
}

int stackPop(stack *stk, int *num) //Указатель на значение.
{
    if (stk-> size == 0)
    {
        printf(">> Stack is empty \n");
        return -1;
    }
    
    --stk-> size;
    int temp = *(stk-> data + stk-> size);
    *(stk-> data + stk-> size) = 0;

    //printf(">> Last number was popped.\n");
    *num = temp;
    return 0;
}

void stackPrint(stack *stk)
{
    printf(">> Current data in stack:\n");
    for (int i = 0; i < stk-> size; i++)
    {
        printf("%d) %d\n", i+1, *(stk-> data + i));
    }
    
}

//Stack dump
//realloc
