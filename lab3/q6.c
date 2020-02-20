
#include <mpi.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
void operate(int* arr, int m)
{
	int sum=0;
	for(int i=0; i<m;i++)
	{
		sum+=arr[i];
		arr[i]=sum;

	}
}
int main(int argc, char *argv[])
{
	int rank,size,n,m,i, arr[100],b[10],c[10],co[10],count=0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		printf("Enter array size: \n");
		scanf("%d",&n);
		for(int i=0; i<n;i++)
		{
			scanf("%d",&arr[i]);
		}
	}
	m=n/size;
	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(arr,m,MPI_INT,c, m, MPI_INT,0,MPI_COMM_WORLD);
	operate(c,m);
	MPI_Gather(c,m, MPI_INT,b, m,MPI_INT, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		for(int i=0; i<n;i++)
			printf("%d\t",b[i]);
	}
	MPI_Finalize();
	return 0;
}
