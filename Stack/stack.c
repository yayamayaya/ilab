#include "stack.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG

#ifdef DEBUG
    #define PRINT(arg) printf(arg);
#else
    #define PRINT(arg)
#endif

#define STK_CTED  "\n>> Stack has been constructed with the capacity of: %d", stk-> capacity 
#define STK_DTED "\n>> Stack has been destructed" 
#define MEM_ALC_ERR "\n\n>>>Memory allocation error" 
#define MEM_RLC_ERR "\n\n>>>Memory reallocation error" 
#define STK_PUSH "\n>> %d was pushed on position %d", *(stk-> data + stk-> size - 1), stk-> size
#define STK_POP "\n>> %d was popped from the stack", temp
#define STK_EMPTY "\n>> Stack is empty"
#define CAPACITY_UP "\n>> Capacity has been doubled"
#define CAPACITY_DOWN "\n>> Capacity has been halfed"

enum stk_realloc
{
    DOWN = 0, 
    UP = 1
};

int stackCtor(stack *stk, int capacity)
{
    assert(stk != NULL && capacity > 0);
    stk-> data = (sDT *)calloc(capacity, sizeof(sDT));
    if(stk-> data == NULL)
    {
        PRINT(MEM_ALC_ERR);
        return 1;
    }

    stk-> size = 0;
    stk-> capacity = capacity;

    PRINT(STK_CTED)
    
    return 0;
}

void stackDtor(stack *stk)
{
    assert(stk != NULL);
    stk-> capacity = 0;
    stk-> size = 0;

    free(stk-> data);
    stk-> data = NULL;

    PRINT(STK_DTED);
}

int stackPush(stack *stk, sDT num)
{
    assert(stk != NULL);
    if (stk-> size == stk-> capacity)
        if(stk_realloc(stk, UP) != 0)
            return 1;
    
    stk-> data[stk-> size] = num;
    stk-> size++;

    PRINT(STK_PUSH)
    return 0;
}

int stackPop(stack *stk, sDT *num)
{
    assert(stk != NULL);
    if (stk-> size == 0)
    {
        PRINT(STK_EMPTY)
        return -1;
    }
    
    --stk-> size;   
    sDT temp = stk-> data[stk-> size];
    stk-> data[stk-> size] = 0; //Инициализация ядом???
 
    PRINT(STK_POP)

    if(num != NULL)
        *num = temp;

    return 0;
}

void stackPrint(stack *stk)
{
    assert(stk != NULL);
    printf("\n>> Stack info:\n");
    printf("\n>> Size: %d", stk-> size);
    printf("\n>> Capacity: %d", stk-> capacity);
    printf("\n>> Current data in stack:");    
    for (int i = 0; i < stk-> size; i++)
        printf("%d) %d\n", i + 1, *(stk-> data + i));
}

int stk_realloc(stack *stk, int num)
{
    assert(stk != NULL);
    if(num == UP)
    {
        stk ->capacity *= 2;
        PRINT(CAPACITY_UP)
    }
    else if(num == DOWN)
    {
        stk ->capacity /= 2;
        PRINT(CAPACITY_DOWN)           
    }
    if(realloc(stk-> data, stk-> capacity * sizeof(sDT)) == NULL)        
    {
        PRINT(MEM_RLC_ERR)
        return 1;
    }

    return 0;
}
