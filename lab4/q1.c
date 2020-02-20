#include <stdio.h>
#include <mpi.h>
#include "err.h"

int main(int argc, char *argv[])
{
	int rank, size, fact=1, factsum, errc,i;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for(i=1; i<=rank+1; i++)
		fact=fact*i;

	errc=MPI_Scan(&fact,&factsum,1,MPI_INT, MPI_SUM,MPI_COMM_WORLD);
	handle(errc);

	if(rank == size-1)
	{
		printf("Sum of all the factorials = %d\n",factsum);
	}

	MPI_Finalize();
	return 0;
}