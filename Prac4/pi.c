#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void calcPi(int NUM_THREADS){
	long num_steps = 10000000;
	double step;
	int nthreads = 0;
	double pi = 0.0;
	double sum[NUM_THREADS];

	step = 1.0/num_steps;

	double start = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		double x=0.0;
		int id = omp_get_thread_num();
		sum[id] = 0;
		int nthrds = omp_get_num_threads();
		if (id==0) {
			nthreads = nthrds;
		}

		int i = 0;
		for (i = id,sum[id] = 0; i < num_steps; i=i+nthrds) {
			x=(i+0.5)*step;
			sum[id] += 4.0/(1.0+x*x);
		}
	}

	for (int i=0; i< nthreads; i++) {
		pi = pi + sum[i]*step;
	}
	double end = omp_get_wtime();

	char s[100] = "";
	for (int i=0; i<(int)((end-start)*200); i++){
		strcat(s,".");
	}
	if ((int)((end-start)*1000)%10>5){
		strcat(s,"+");
	}
	else
	{
		strcat(s,"*");
	}

	// s = " " * int((end-start)*100) + "*";
		//  |nThreads Used |Value of Pi |Time Taken  |
	printf("|       %2d      |   %2f  |  %f  | %s\n",nthreads, pi, end-start, s);
}

int main(int argc, char *argv[]) {
	printf("| nThreads Used | Value of Pi | Time Taken |------------------------------------------------\n");
	for(int i=1; i<33*2;i++){
		calcPi(ceil(i/2));
	}
	return EXIT_SUCCESS;
}
