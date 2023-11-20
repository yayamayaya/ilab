#include <stdio.h>
#include "Kvadratka.h"

int main()
{
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    printf("Enter a, b, c:\n");
    scanf("%lf%lf%lf", &a, &b, &c);
    kvUr(a, b, c, &x1, &x2);

    printf("x1 = %.3lf\nx2 = %.3lf", x1, x2);

}