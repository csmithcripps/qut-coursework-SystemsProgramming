#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int calcSquare(int val);

int main(int argc, char *argv[]) {
	int i=0, j=5, NUM = 1000;
	long int result = 0;
	long int A[NUM];
	
	for (i=0; i < NUM; i++) {
		j+=2;
		A[i] = calcSquare(j);
	}
	
	printf("The square of the last number is %li\n", A[NUM-1]);
}

int calcSquare(int val) {
	return val*val;
}
