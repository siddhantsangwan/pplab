#include <stdio.h>
#include <mpi.h>
#include "err.h"
int main(int argc, char *argv[])
{
	int rank, errc,size, a[16],arr1[4],arr2[4],i,j,count=0,countsum;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		printf("Enter the matrix : \n");
		for(i=0;i<16;i++)
		{
			scanf("%d",&a[i]);
		}
	}
	errc=MPI_Scatter(a,4,MPI_INT,arr1,4,MPI_INT, 0, MPI_COMM_WORLD);
	handle(errc);
	MPI_Scan(arr1,arr2,4,MPI_INT, MPI_SUM,MPI_COMM_WORLD);
	for(int i=0; i<4;i++)
		{
			printf( "%d ",arr2[i]);
		}
		printf("\n");
	MPI_Finalize();
	return 0;
}