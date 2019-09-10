#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void Hello(void);  /* Function to thread */

int main(int argc, char *argv[]) {
		
	# pragma omp parallel 
	{
		Hello();
	}
	return EXIT_SUCCESS;
}

void Hello(void) {
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();

	printf("Hello for thread %d of %d\n", my_rank, thread_count);
}

