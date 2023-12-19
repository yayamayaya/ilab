#include "stack.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG
#define SECURE

#ifdef DEBUG
    #define VER(arg) Verificator(logFile, *pstk, arg);
    FILE *logFile = NULL;
#else
    #define VER(arg)
#endif

#ifdef SECURE
    #define STKKILL(ptr) stackKiller(ptr);
#else
    #define STKKILL(ptr)
#endif

void Verificator(FILE* fileName, const stack stk, const int errNum);
int poisonCheck(const stack *pstk);
int canaryCheck(const stack *pstk);
void stackKiller(stack *pstk);

const dataType poison = 0xDEAD;
const long long int canary = 0xDEDDEAD;

int stackCtor(stack *pstk, const int capacity)
{
    assert(pstk != NULL);
    if (capacity == 0)               //Проверки
    {
        VER(CAPACITY_ZERO)
        return CAPACITY_ZERO;
    }

    #ifdef DEBUG            //Открываем логфайл
        logFile = fopen("logFile.txt", "w");
        if (logFile == NULL)
            printf("[error]>>Can't open the log.\n");
    #endif

    pstk->firstCanaryPtr = (long long int *)calloc(capacity * sizeof(dataType) + 2 * sizeof(canary), 1);       
    if (pstk->firstCanaryPtr == NULL)        //Аллоцируем память под канареек и данные, присваиваем адреса памяти канарейкам и данным
    {
        VER(MEM_ALC_ERR)
        return MEM_ALC_ERR;
    }
    pstk->data = (dataType *)(pstk->firstCanaryPtr + 1);
    pstk->secondCanaryPtr = (long long int *)(pstk->data + capacity);

    pstk->size = 0;
    pstk->capacity = capacity;

    for (int i = 0; i < pstk->capacity; i++) //Инициализируем ядом
        pstk->data[i] = poison;

    *(pstk->firstCanaryPtr) = canary;   //Присваиваем канарейкам значения
    *(pstk->secondCanaryPtr) = canary;

    if (poisonCheck(pstk) != 0)      //Poison check
    {
        STKKILL(pstk)
        return PSN_ERR;
    }

    VER(STK_CTED)
    return STK_CTED;
}

void stackDtor(stack *pstk)
{
    assert(pstk != NULL);

    pstk->capacity = 0;
    pstk->size = 0;

    free(pstk->firstCanaryPtr);

    pstk->firstCanaryPtr = NULL;        //Высвобождаем память, занулляем указатели
    pstk->data = NULL;
    pstk->secondCanaryPtr = NULL;

    VER(STK_DTED)
}

int stackPush(stack *pstk, const dataType num)
{
    assert(pstk != NULL);

    if (pstk->size == pstk->capacity)           //Проверка на переполнение массива
        if(stk_realloc(pstk, UP) != 0)
            return MEM_RLC_ERR;
    
    pstk->data[pstk->size] = num;
    pstk->size++;

    if (poisonCheck(pstk) != 0)      //poison check and canary check
    {
        STKKILL(pstk)
        return PSN_ERR;
    }
    if (canaryCheck(pstk) != 0)
    {
        STKKILL(pstk)
        return CANARY_ERR;
    }

    VER(STK_PUSH)

    return 0;
}

int stackPop(stack *pstk, dataType *num)
{
    assert(pstk != NULL);
    if (pstk->size == 0)
    {
        VER(STK_EMPTY)
        return -1;
    }
    
    --pstk->size;   
    dataType temp = pstk->data[pstk->size];      //Берем значение, заполняем ячейку ядом
    pstk->data[pstk->size] = poison;

    if (num != NULL)     //Это пустой поп
        *num = temp;

    if (poisonCheck(pstk) != 0)
    {
        STKKILL(pstk)
        return PSN_ERR;
    }
    if (canaryCheck(pstk) != 0)
    {
        STKKILL(pstk)
        return CANARY_ERR;
    }

    VER(STK_POP)
    return 0;
}

void stackPrint(const stack *pstk)
{
    assert(pstk != NULL);
    printf("\n>> Stack info:\n");
    printf("\n>> Size: %d", pstk->size);
    printf("\n>> Capacity: %d", pstk->capacity);
    printf("\n>> Current data in stack:\n");    
    for (int i = 0; i < pstk->size; i++)
        printf("%d) %d\n", i + 1, pstk->data[i]);
    printf(">> Poison is: %X", poison);
    printf("\n>> Canaries are %llX and %llX\n", *(pstk->firstCanaryPtr), *(pstk->secondCanaryPtr));
}

int stk_realloc(stack *pstk, const int num)
{
    assert(pstk != NULL);

    if (num == UP)
    {
        pstk->capacity *= 2;
        VER(CAPACITY_UP)
    }
    else if(num == DOWN)
    {
        pstk->capacity /= 2;
        VER(CAPACITY_DOWN)           
    }

    long long int canaryHolder = *(pstk->secondCanaryPtr);      //Запоминаем значение старой канарейки на случай её изменения

    long long int *temp = (long long int *)realloc(pstk->firstCanaryPtr, pstk->capacity * sizeof(dataType) + 2 * sizeof(canary));
    if (temp == NULL)        
    {
        VER(MEM_RLC_ERR)
        return MEM_RLC_ERR;
    }
    pstk->firstCanaryPtr = temp;
    pstk->data = (dataType *)(pstk->firstCanaryPtr + 1);             //Присваиваем указатели данным и канарейкам
    pstk->secondCanaryPtr = (long long int *)(pstk->data + pstk->capacity);

    *(pstk->secondCanaryPtr) = canaryHolder;      //Присваиваем значение новой конечной канарейке, значение старой сотрётся ядом

    if (num == UP)
        for (int i = pstk->capacity - 1; i >= pstk->capacity / 2 ; i--)
            pstk->data[i] = poison;

    if (poisonCheck(pstk) != 0 || canaryCheck(pstk) != 0)
        STKKILL(pstk)

    return 0;
}

void Verificator(FILE* fileName, const stack stk, const int errNum)
{
    switch (errNum)
    {
    case STK_CTED:
        fprintf(fileName, ">> Stack has been constructed with the capacity of: %d       STK_CTED       < %d >\n", stk.capacity, errNum);
        break;
    case STK_DTED:
        fprintf(fileName, ">> Stack has been destructed     STK_DTED     < %d >\n", errNum);
        fclose(fileName);
        break;
    case CAPACITY_ZERO:
        fprintf(fileName, ">> Capacity can't be zero        CAPACITY_ZERO        < %d >         [error]\n", errNum);
        break;
    case MEM_ALC_ERR:
        fprintf(fileName, ">> Memory allocation error       MEM_ALC_ERR       < %d >          [error]\n", errNum);
        break;
    case MEM_RLC_ERR:
        fprintf(fileName, ">> Memory reallocation error     MEM_RLC_ERR     < %d >            [error]\n", errNum);
        break;
    case STK_PUSH:
        fprintf(fileName, ">> %d was pushed on position %d      STK_PUSH      < %d >\n", stk.data[stk.size - 1], stk.size, errNum);
        break;
    case STK_POP:
        fprintf(fileName, ">> Number was popped from the stack      STK_POP      < %d >\n", errNum);
        break;
    case STK_EMPTY:
        fprintf(fileName, ">> Stack is empty        STK_EMPTY        < %d >\n", errNum);
        break;
    case CAPACITY_UP:
        fprintf(fileName, ">> Capacity has been doubled     CAPACITY_UP     < %d >\n", errNum);
        break;
    case CAPACITY_DOWN:
        fprintf(fileName, ">> Capacity has been halfed      CAPACITY_DOWN      < %d >\n", errNum);
        break;
    case PSN_ERR:
        fprintf(fileName, ">> Number is not poison      PSN_ERR      < %d >          [danger]\n", errNum);
        break;
    case CANARY_ERR:
        fprintf(fileName, ">> Canary is damaged         CANARY_ERR      < %d >           [danger]\n", errNum);
        break;
    case STK_KILL:
        fprintf(fileName, ">> Stack security was broken, stack to be destructed      STK_KILL        < %d >         [danger]\n", errNum);
        break;
    default:
        break;
    }
}

int poisonCheck(const stack *pstk)
{
    for (int pos = pstk->size; pos < pstk->capacity; pos++)
        if (pstk->data[pos] != poison)
        {
            VER(PSN_ERR)
            return PSN_ERR;
        }    
    return 0;
}

int canaryCheck(const stack *pstk)
{
    if (*(pstk->firstCanaryPtr) != canary || *(pstk->secondCanaryPtr) != canary)
    {
        VER(CANARY_ERR)
        return CANARY_ERR;
    }
        
    return 0;
}

void stackKiller(stack *pstk)
{
    VER(STK_KILL)
    stackDtor(pstk);
    printf("\n>> Stack security was broken, stack has been destructed\n");
    exit(1);
}

//TO DO: переписать фунцию проверки яда*, подумать над канарейкой в реаллоке