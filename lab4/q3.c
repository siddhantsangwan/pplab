#include <stdio.h>
#include <mpi.h>
#include "err.h"
int main(int argc, char *argv[])
{
	int rank, size, a[9],arr[3],ele, i,j,count=0,countsum,errc;
	errc=MPI_Init(&argc,&argv);
	handle(errc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		printf("Enter the matrix : \n");
		for(i=0;i<9;i++)
		{
			scanf("%d",&a[i]);
		}
		printf("Enter the element : \n");
		scanf("%d",&ele);
	}
	errc=MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);
	handle(errc);
	MPI_Scatter(a,3,MPI_INT,arr,3,MPI_INT, 0, MPI_COMM_WORLD);
	for(j=0;j<3;j++)
	{
			if(arr[j]==ele)
				count++;
	}
	MPI_Reduce(&count,&countsum,1,MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("NUmber of occurences= %d\n",countsum);
	}
	MPI_Finalize();
	return 0;
}