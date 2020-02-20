#include <mpi.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


int operate(int* arr, int m)
{
	int count=0;
	for(int i=0; i<m;i++)
	{
		if((arr[i]%2)==0){
			arr[i]=1;
			count++;
		}
		else
			arr[i]=0;

	}
	return count;
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
	count=operate(c,m);
	MPI_Gather(c,m, MPI_INT,b, m,MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(&count,1, MPI_INT,co, 1,MPI_INT, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		count=0;
		for(int i=0; i<n;i++)
			count+=co[i];
		printf("Count of even : %d. \n",count);
		printf("Count of odd : %d.\n",n-count);
		for(int i=0; i<n;i++)
			printf("%d\t",b[i]);
	}
	MPI_Finalize();
	return 0;
}
