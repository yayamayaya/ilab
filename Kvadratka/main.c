#include <stdio.h>
#include "Kvadratka.h"

void main()
{
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;

    printf("Enter a, b and c:\n");
    if(scanf("%lf%lf%lf", &a, &b, &c) < 3)
    {
        printf("too few coefficient");
    }

    if(kvUr(a, b, c, &x1, &x2))
        printf("\nError in solving");

    printf("x1 = %.3f, x2 = %.3f", x1, x2);
}

/*Ввод чисел с консоли как отдельная функиця
Решение как отдельная функция(Рассмотрим все случаю), вывод как отдельная, unit тест, doxygen документация*/