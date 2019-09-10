
/* Includes */
#include "fib.h"        /* Fib Sequence code */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s [print the first n number of the Fibonacci sequence]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);

    pid_t childpid; /* variable to store the child's pid */

    /* only 1 int variable is needed because each process would have its
       own instance of the variable
       here, 2 int variables are used for clarity */

    /* now create new process */
    childpid = fork();

    if (childpid >= 0) /* fork succeeded */
    {
        if (childpid == 0) /* fork() returns 0 to the child process */
        {
            printf("[CHILD]: Executing fib for %d values.\n", n);
            fib(n);
        }
        else /* fork() returns new pid to the parent process */
        {
            wait(NULL);
            printf("[PARENT]: CHILD exited Successfully\n");
        }
        return EXIT_SUCCESS;
    }
    else /* fork returns -1 on failure */
    {
        perror("fork"); /* display error message */
        return EXIT_FAILURE;
    }
}
