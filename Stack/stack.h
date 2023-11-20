#pragma once

struct stack
{
    int* data;
    int size;
    int capacity;
};
typedef struct stack stack;
void stackCtor(stack *stk, int capacity);
void stackDtor(stack *stk);
void stackPush(stack *stk, int num);
int stackPop(stack *stk, int *num);
void stackPrint(stack *stk);