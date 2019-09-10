#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	long num_steps = 10000000;
	double step;
	int i =0;
	double x,pi,sum = 0.0;
	step = 1.0/num_steps;
	#pragma omp parallel for private (i, x) shared(sum)
	for (i = 0; i < num_steps; i++) {
		x=(i+.5)*step;
		#pragma omp critical
		sum = sum + 4.0/(1.0+x*x);
	}
	
	pi = step * sum;
	printf("The value for pi = %f\n", pi);
	return EXIT_SUCCESS;
}
