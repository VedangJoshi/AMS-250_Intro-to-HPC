#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char ** argv) {
	if(argc < 2) {
		printf("Incorrect number of parameters");
		return -1;
	}
	
	int MAX = atoi(argv[1]);
	int arrA[MAX][MAX];  
	int arrB[MAX][MAX];
	int arrRes[MAX][MAX];
	int i, j, k;
	
	#pragma omp parallel shared(arrA, arrB, arrRes) private(i, j, k)
	{
	    #pragma omp for schedule(dynamic, MAX/200) nowait // Outer parallelism
		for (i = 0; i < MAX; i++) 
			//#pragma omp for schedule(dynamic, MAX/200) nowait // Inner parallelism
			for (j = 0; j < MAX; j++)
				for (k = 0; k < MAX; k++)
					arrRes[i][j] += arrA[i][k] * arrB[k][j];	
	}
	
	return EXIT_SUCCESS;
}

/*

*****************************************************************************************************
								  Outer parallelism
*****************************************************************************************************
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ OMP_NUM_THREADS=1
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ time ./a.out 1600
real    0m1.370s
user    0m1.319s
sys     0m0.026s

Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ OMP_NUM_THREADS=2
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ time ./a.out 1600
real    0m0.715s
user    0m1.371s
sys     0m0.030s

Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ OMP_NUM_THREADS=4
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ time ./a.out 1600
real    0m0.635s
user    0m2.183s
sys     0m0.068s

*****************************************************************************************************
								 Inner Parallelism
*****************************************************************************************************
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ OMP_NUM_THREADS=1
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ time ./a.out 1600
real    0m1.449s
user    0m1.412s
sys     0m0.022s

Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ OMP_NUM_THREADS=2
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ time ./a.out 1600
real    0m4.715s
user    0m9.303s
sys     0m0.083s

Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ OMP_NUM_THREADS=4
Vedangs-MacBook-Pro:AMS-250_openMP vedangjoshi$ time ./a.out 1600
real    0m3.562s
user    0m13.603s
sys     0m0.143s

*/

