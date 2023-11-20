#include <stdio.h>
#include <math.h>
#include "Kvadratka.h"

int kvUr(double a, double b, double c, double *x1, double *x2)
{
    if (aCondition(a))
        return 1;
    if (bcCondition(a, b, x1, x2) || bCondition(a, b, c, x1, x2) || cCondition(a, b, c, x1, x2))
        return 0;
    if (Discriminant(a, b, c) < 0)
    {
        printf("No solutions\n");
        return 0;
    }
    else
    {
        *x1 = (-b + Discriminant(a, b, c)) / (2 * a);
        *x2 = (-b - Discriminant(a, b, c)) / (2 * a);
        return 0;
    }
}

int aCondition(double a)
{
    if (a == 0)
    {
        printf("a can't be equal 0\n");
        return 1;
    }
    return 0;
}

int bcCondition(double b, double c, double *x1, double *x2)
{
    if (b == 0 && c == 0)
    {
        *x1 = 0;
        *x2 = 0;
        return 1;
    }
    return 0;
}

int bCondition(double a, double b, double c, double *x1, double *x2)
{
    if(b == 0)
    {
        if (c / a > 0)
        {
            printf("No solutions\n");
            return 1;
        }
        else 
        {
            *x1 = sqrt(-(c / a));
            *x2 = -sqrt(-(c / a));
            return 1;
        }
    }
    return 0;  
}

int cCondition(double a, double b, double c, double *x1, double *x2)
{
    if (c == 0)
    {
        *x1 = 0;
        *x2 = -(b / a);
        return 1;
    }
    return 0;
}

int Discriminant(double a, double b, double c)
{
    return sqrt(b * b - 4 * a * c);
}