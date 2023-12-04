#include "stack.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG

#define STK_CTED  0
#define STK_DTED "\n>> Stack has been destructed.\n" 0
#define MEM_ALC_ERR "\n>>>Memory allocation error" 0
#define MEM_RLC_ERR "\n>>>Memory reallocation error" 

enum stk_realloc
{
    DOWN = 0, 
    UP = 1
};

//Написать typedef для быстрой смены типа
//Проверять, чтобы не подсунули 0 указатель в функцию

int stackCtor(stack *stk, int capacity)
{
    stk-> data = (int *)calloc(capacity, sizeof(int));      //Проверка на каллок
    if(stk-> data == NULL)
    {
        #ifdef DEBUG
            printf("\n>>>Memory allocation error");
        #endif
        return 1; //Убрать exit'ы
    }

    stk-> size = 0;
    stk-> capacity = capacity;

    #ifdef DEBUG
        printf("\n>>Stack has been constructed with the capacity of %d\n", stk-> capacity);
    #endif
    
    return 0;
}

void stackDtor(stack *stk)
{
    stk-> capacity = 0;
    stk-> size = 0;

    free(stk-> data);
    stk-> data = NULL;

    #ifdef DEBUG
        printf("\n>> Stack has been destructed.\n");
    #endif
}

void stackPush(stack *stk, int num)
{
    if (stk-> size == stk-> capacity)
        stk_realloc(stk, UP);
    
    *(stk-> data + stk-> size) = num;
    stk-> size++;

    #ifdef DEBUG
        printf(">> %d was pushed on position %d.\n", *(stk-> data + stk-> size - 1), stk-> size);
    #endif
}

int stackPop(stack *stk, int *num) //Указатель на значение.
{
    if (stk-> size == 0)
    {
        #ifdef DEBUG
            printf(">> Stack is empty \n");
        #endif

        return -1;
    }
    
    --stk-> size;   
    int temp = *(stk-> data + stk-> size);  //Сделать пустой поп, если num == NULL
    *(stk-> data + stk-> size) = 0;
 

    #ifdef DEBUG
    printf(">> Last number was popped. Current free position is %d\n", stk->size); //Инициализация ядом.
    #endif

    if(num != NULL)
    {
        *num = temp;
    }
    return 0;
}

void stackPrint(stack *stk)
{
    printf(">> Current data in stack:\n");
    for (int i = 0; i < stk-> size; i++)
    {
        printf("%d) %d\n", i+1, *(stk-> data + i)); //Написать всю информацию о стеке
    }
}

int stk_realloc(stack *stk, int num)
{
    if(num == UP)
        stk ->capacity *= 2;
    else if(num == DOWN)
        stk ->capacity /= 2;          
    if(realloc(stk-> data, stk-> capacity * sizeof(int)) == NULL)        
    {
        #ifdef DEBUG
            printf("\n>>>Memory reallocation error");
        #endif

        return 1;
    }

    #ifdef DEBUG
        printf("\n>> Not enough capacity. Capacity has been doubled. Current capacity - %d\n", stk-> capacity);
    #endif
}

//Stack dump
