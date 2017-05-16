#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {

int rank, size;
int recv = 0;
int tag = 1;
MPI_Status Stat;

int msg_size = atoi(argv[1]);
char* out_msg = argv[2];
char* recv_msg = malloc(msg_size * sizeof(char));

double initTimeStart = MPI_Wtime();
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
printf("Process %d :: Init Time: %f\n", rank, MPI_Wtime() - initTimeStart);

if(rank == 0) {
	double sendTimeStart = MPI_Wtime();
	MPI_Send(&out_msg, msg_size, MPI_CHAR, (rank+1) % size, tag, MPI_COMM_WORLD);
	MPI_Recv(&recv_msg, 100, MPI_CHAR, size - 1, tag, MPI_COMM_WORLD, &Stat);
	printf("Process : %d :: Msg_Recv -> %s\n", rank, recv_msg);
	printf("Send_Recv Time: %f\n", MPI_Wtime() - initTimeStart);
} else {
	double sendTimeStart = MPI_Wtime();
	MPI_Send(&out_msg, msg_size, MPI_CHAR, (rank+1) % size, tag, MPI_COMM_WORLD);
	MPI_Recv(&recv_msg, 100, MPI_CHAR, rank - 1, tag, MPI_COMM_WORLD, &Stat);
	printf("Process : %d :: Msg_Recv -> %s\n", rank, recv_msg);
	printf("Send_Recv Time: %f\n", MPI_Wtime() - initTimeStart);
}

MPI_Finalize();

return 0;
	
}