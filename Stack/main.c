#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"


int main()
{
    stack Stk1 = {0};
    stackCtor(&Stk1, 5);

    stackPush(&Stk1, 10);
    stackPush(&Stk1, 20);

    stackPrint(&Stk1);

    int c = stackPop(&Stk1);
    stackPrint(&Stk1);
    printf(">>Popped number is %d\n", c);
}