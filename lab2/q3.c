#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	int rank,size,x[10],num, buffer[100],s=100;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Buffer_attach(buffer,100);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter the array elements: ");
		for(int i=0; i<size-1;i++){
			scanf("%d",&x[i]);
			MPI_Bsend(&x[i],1,MPI_INT,i+1,1,MPI_COMM_WORLD);
		}
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&num,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		if(rank%2==0)
		{
			fprintf(stdout,"Received %d in proc %d, square: %d, \n",num,rank,(num*num));
		}
		else
			fprintf(stdout,"Received %d in proc %d, cube: %d, \n",num,rank,(num*num*num));
		fflush(stdout);
	}
	MPI_Buffer_detach(&buffer,&s);
	MPI_Finalize();

	return 0;
}