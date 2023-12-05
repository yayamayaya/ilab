#include <stdio.h>

typedef struct
{
    double a;
    double b;
    double c;

    double x1;
    double x2;
} kvUr;

int coeffInput(kvUr *KV);

void main()
{
    kvUr KV = {0};
    //Запись коэффицентов
    coeffInput(&KV);

}

int coeffInput(kvUr *KV)
{
    printf("Enter coefficients:\nEnter a:\n");
    while (scanf("%lf", &KV-> a) == 0)
        printf("Try again.\n");

    printf("Enter b:\n");
    while (scanf("%lf", &KV-> b) == 0)
        printf("Try again.\n");
    
    printf("Enter c:\n");
    while (scanf("%lf", &KV-> c) == 0)
        printf("Try again.\n");

    printf("Coefficients were read successfully. Equation is:\n %.1lfx^2 + %.1lfx + %.1lf = 0", KV-> a, KV-> b, KV-> c);
}