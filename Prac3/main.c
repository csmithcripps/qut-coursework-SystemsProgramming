#include "fib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s [print the first n number of the Fibonacci sequence]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if (n < 1)
    {
        n = 1;
    }
    fib(atoi(argv[1]));
    return EXIT_SUCCESS;
}
