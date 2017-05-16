#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {

int rank, size;
char* msg = argv[1]; 
int recv = 0;
int tag = 1;
MPI_Status Stat;
int inmsg;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

if(rank == 0) {
	MPI_Send(&baton, 1, MPI_INT, (rank+1) % size, tag, MPI_COMM_WORLD);
	MPI_Recv(&inmsg, 1, MPI_INT, size - 1, tag, MPI_COMM_WORLD, &Stat);
	printf("Process : %d :: Msg_Recv -> %d\n", rank, inmsg);
} else {
	MPI_Send(&baton, 1, MPI_INT, (rank+1) % size, tag, MPI_COMM_WORLD);
	MPI_Recv(&inmsg, 1, MPI_INT, rank - 1, tag, MPI_COMM_WORLD, &Stat);
	printf("Process : %d :: Msg_Recv -> %d\n", rank, inmsg);
}

MPI_Finalize();

return 0;
	
}

/*

Vedangs-MacBook-Pro:Assignment-2_OpenMPI vedangjoshi$ mpicc MPI_Ring.c -o ring

Vedangs-MacBook-Pro:Assignment-2_OpenMPI vedangjoshi$ mpirun -n 4 ./ring 
Process : 0 :: Msg_Recv -> 12345
Process : 1 :: Msg_Recv -> 12345
Process : 2 :: Msg_Recv -> 12345
Process : 3 :: Msg_Recv -> 12345

Vedangs-MacBook-Pro:Assignment-2_OpenMPI vedangjoshi$ mpirun -n 8 ./ring 
Process : 1 :: Msg_Recv -> 12345
Process : 2 :: Msg_Recv -> 12345
Process : 4 :: Msg_Recv -> 12345
Process : 3 :: Msg_Recv -> 12345
Process : 5 :: Msg_Recv -> 12345
Process : 6 :: Msg_Recv -> 12345
Process : 0 :: Msg_Recv -> 12345
Process : 7 :: Msg_Recv -> 12345
*/