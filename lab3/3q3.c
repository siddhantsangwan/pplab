#include <mpi.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int numNoVowel(char str[50], int n)
{
	int i=0,count=0,lowercase=0,uppercase=0;
	for(int i=0; i<n;i++)
	{
		if(strchr("aeiouAEIOU",str[i])==NULL)
    		count++;
	}
	return count;
	
}
int main(int argc, char *argv[])
{
	int rank,size,i,len,m,b[10],count,sum=0;
	char str[30],c[10];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank==0)
	{
		printf("Enter a string: \n");
		scanf("%s",str);
		// if((strlen(str)%size)!=0)
		// 	exit(0);
	}
	m=strlen(str)/size;
	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(str,m,MPI_CHAR,c, m, MPI_CHAR,0,MPI_COMM_WORLD);
	count=numNoVowel(c,m);
	fprintf(stdout,"my num: %d in process %d \n",count,rank);
	fflush(stdout);
	MPI_Gather(&count,1, MPI_INT,b, 1,MPI_INT, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("Result gathered in root \n");
		for(int i=0; i<size;i++)
		{
			sum+=b[i];
		}
		printf("%d \n",sum);
	}
	MPI_Finalize();
	return 0;
}
