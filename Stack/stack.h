#pragma once

struct stack
{
    int* data;
    int size;
    int capacity;
};

typedef int sDT;
typedef struct stack stack;

int stackCtor(stack *stk, int capacity);
void stackDtor(stack *stk);
int stackPush(stack *stk, sDT num);
int stackPop(stack *stk, sDT *num);
void stackPrint(stack *stk);
int stk_realloc(stack *stk, int num);