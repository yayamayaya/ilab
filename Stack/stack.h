#pragma once

struct stack
{
    int* data;
    int size;
    int capacity;
    long long int *firstCanaryPtr;
    long long int *secondCanaryPtr;
};

typedef int dataType;
typedef struct stack stack;

enum debugging
{
    STK_CTED = 0,
    CAPACITY_ZERO = 1,
    MEM_ALC_ERR = 2,
    MEM_RLC_ERR = 3,
    STK_PUSH = 4,
    STK_POP = 5,
    STK_EMPTY = 6,
    CAPACITY_UP = 7,
    CAPACITY_DOWN = 8,
    STK_DTED = 9,
    PSN_ERR = 10,
    CANARY_ERR = 11,
    STK_KILL = -1
};

enum stk_realloc
{
    DOWN = 0, 
    UP = 1
};

int stackCtor(stack *pstk, const int capacity);
void stackDtor(stack *pstk);
int stackPush(stack *pstk, const dataType num);
int stackPop(stack *pstk, dataType *num);
void stackPrint(const stack *pstk);
int stk_realloc(stack *stk, const int num);