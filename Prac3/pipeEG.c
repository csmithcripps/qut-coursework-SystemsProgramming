#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <string.h>

char *message = "This is a message from parent!!!";
int main(void)
{
    pid_t childpid; /* variable to store the child's pid */
    char buf[1024];
    int fd[2];
    pipe(fd); /*create pipe*/
    if (fork() != 0)
    { /* I am the parent */
        write(fd[1], message, strlen(message) + 1);
    }
    else
    { /*Child code */
        printf("CHILD: I am the child process!\n");
        printf("CHILD: Here's my PID: %d\n", getpid());
        printf("CHILD: My parent's PID is: %d\n", getppid());
        read(fd[0], buf, 1024);
        printf("I got the following message from my parent: %s\n", buf);
    }
}
