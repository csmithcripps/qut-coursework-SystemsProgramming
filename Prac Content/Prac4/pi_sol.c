#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

int main(int argc, char *argv[]) {
	long num_steps = 10000000;
	double step;
	int nthreads = 0;
	double pi = 0.0;
	double sum[NUM_THREADS] = {0,0};	
	step = 1.0/num_steps;
	double start = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int i=0;
		double x=0.0;
		int id = omp_get_thread_num();
		int nthrds = omp_get_num_threads();
		if (id==0) {
			nthreads = nthrds;
		}
		for (i = id,sum[id] = 0; i < num_steps; i=i+nthrds) {
			x=(i+0.5)*step;
			sum[id] += 4.0/(1.0+x*x);
		}
	}
	int i=0;
	for (i=0; i< nthreads; i++) {
		pi = pi + sum[i]*step;
	}
	double end = omp_get_wtime();
	printf("The value for pi = %f and the execution time is %f\n", pi, end-start);
	return EXIT_SUCCESS;
}
