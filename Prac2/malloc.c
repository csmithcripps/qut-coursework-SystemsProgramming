// Introduction to memory management in C
// NOTE: this is C99 code, compile with c99 instead of gcc, or pass -std=c99 to gcc as a parameter

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH_1 10
#define ARRAY_LENGTH_2 20

int main(int argc, char **argv) {
    // type "man malloc" at a linux terminal to read about malloc and friends

    int *array = malloc(ARRAY_LENGTH_1*(sizeof(int)));
    for (int i = 0; i<ARRAY_LENGTH_1;i++){
        printf("%d",*(array + i));
    }
    printf("\n");

    //initialise array with values 0 through 9
    //print array of 10 integers
    for (int i = 0; i<ARRAY_LENGTH_1;i++){
        *(array + i) = i;
        printf("%d",*(array + i));
    }
    printf("\n");

    //reallocate the array of 10 integers to 20 integers using realloc()
    array = (int *) realloc(array,ARRAY_LENGTH_2*sizeof(int));

    // TODO: print array of 20 integers
    for(int i = 0; i<ARRAY_LENGTH_2; i++){
        printf("%d", *(array + i));
    }
    printf("\n");
    // TODO: free memory for 20 integers allocated by realloc()
    free(array);
    // TODO: print pointer to free'd memory as an integer, what happens if you dereference this pointer?
    printf("Free'd Array had address: %p\n", array);
    printf("Dereferenced Free'd Pointer: %d\n", *array);
    // TODO: allocate an array of 20 integers using calloc()
    array = calloc(ARRAY_LENGTH_2,sizeof(int));
    // TODO: print array of 20 integers
    for(int i = 0; i<ARRAY_LENGTH_2; i++){
        printf("%d", *(array + i));
    }
    printf("\n");

    // TODO; free memory for 20 integers allocated by calloc()
    free(array);

    return EXIT_SUCCESS;
}
