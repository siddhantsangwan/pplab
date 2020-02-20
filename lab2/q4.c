#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank,size,x;
	//char* word;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter a value in master process: ");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		MPI_Recv(&x,1,MPI_INT,size-1,size,MPI_COMM_WORLD,&status);
		fprintf(stdout,"Received %d in proc %d\n",x,rank);
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,rank,MPI_COMM_WORLD,&status);
		fprintf(stdout,"Received %d in proc %d\n",x,rank);
		if(rank==(size-1)){
			++x;
			MPI_Send(&x,1,MPI_INT,0,rank+1,MPI_COMM_WORLD);
		}
		else{
			++x;
			MPI_Send(&x,1,MPI_INT,rank+1,rank+1,MPI_COMM_WORLD);
		}
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}