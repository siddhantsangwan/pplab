#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
	
int main (int argc, char *argv []) {

	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank & 1)
	{
		printf("Process %d: World\n", rank);
	}
	else
		printf("Process %d: Hello\n", rank);


	MPI_Finalize();
	return 0;

}
