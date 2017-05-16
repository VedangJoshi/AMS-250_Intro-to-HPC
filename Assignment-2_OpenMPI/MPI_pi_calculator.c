#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#define N 1000000

int main(int argc, char** argv) {

  MPI_Init(NULL, NULL);

  int world_rank;
  int world_size;
  long long i;
  long long hits = 0;
  double x, y;
  long long global_hits = 0;
  
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Initialize rand generator
  srand(clock()); 

  for (i = 0, hits = 0; i < N; i++) {
  	 x = (double) rand() / RAND_MAX;
  	 y = (double) rand() / RAND_MAX;
		
	 if ((x*x + y*y) < 1) {
		hits++;
	 }  		    
  }
  	
  printf("%d \n", hits);
  
  // Reduce all the local hits into the global hit count
  MPI_Reduce(&hits, &global_hits, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Result
  if (world_rank == 0) {
  	float pi = (4 * global_hits) / (N * world_size);
    printf("π = %f \n", pi);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  
  return 0;	
}

/*
$ mpirun -n 10 pi 
785997 
785248 
785727 
785233 
785043 
785907 
785502 
784836 
785515 
785715 
π = 3.000000
*/