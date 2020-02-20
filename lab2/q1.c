#include <mpi.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int rank,size;
	char x[15];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter a word in master process: ");
		scanf("%s",x);
		MPI_Ssend(x,15,MPI_CHAR,1,1,MPI_COMM_WORLD);
		fprintf(stdout, "Sent %s from proc 0\n",x );
		fflush(stdout);
	}
	else
	{
		MPI_Recv(x,15,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		for(int i=0; i<=strlen(x);i++)
		{
			if(isupper(x[i]))
				x[i]=tolower(x[i]);
			else
				x[i]=toupper(x[i]);
		}
		fprintf(stdout,"Received %s in proc 1\n",x);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}