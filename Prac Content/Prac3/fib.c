#include "fib.h"
#include <stdio.h>
void fib(int n)
{
    if (n < 0)
    {
        return;
    }
    unsigned long n_1 = 0;
    unsigned long n_2 = 1;
    unsigned long currentN;
    if (n > 0)
    {
        printf("0");
    }

    if (n > 1)
    {
        printf(", 1");
    }
    if (n > 2)
    {
        for (int i = 2; i < n; i++)
        {
            currentN = n_1 + n_2;
            n_1 = n_2;
            n_2 = currentN;

            printf(", %lu", currentN);
        }
    }
    printf("\n\n");
}
