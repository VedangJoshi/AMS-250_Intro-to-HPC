#include <stdio.h>
#include <omp.h>

inline double func(double x) {
	return (1 / (1 + x*x));
}

int main (int argc, char ** argv) {
	int n;
	int a = 0, b = 1;
	int N = 100000;
	double sum = 0;

	// h
	double h = (b-a) / (double) N;

	// Calculation of π using midpoint rule 
	#pragma omp parallel shared(a, h) private(n) reduction(+:sum)
	{	
		#pragma omp for schedule(dynamic, N/1000) nowait
		for(n = 0; n < N; n++) {
			sum += func(a + n*h);
		}
	}
	
	printf("\nπ = %f\n", h * sum * 4);
	
	return EXIT_SUCCESS;
}

/*

Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ icc Pie_calculator.c -fopenmp
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ ./a.out 

π = 3.141603

*/