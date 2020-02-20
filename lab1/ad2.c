#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
	
int main (int argc, char *argv []) {

	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int primes[101];

    int i,j;

    int z = 1, limit = 100;

    for (i = 2; i < limit; i++)
        primes[i] = 1;

    for (i = 2; i < limit; i++)
        if (primes[i])
            for (j = i; i * j < limit; j++)
                primes[i * j] = 0;

    printf("\nPrime numbers in range 1 to 100 are: \n");

    if(rank == 0)
    {
    	for (i = 2; i < 50; i++)
        	if (primes[i])
            	printf("%d\n", i);
    }
    else
    {
    	for (i = 50; i < limit; i++)
    		if (primes[i])
    			printf("%d\n", i);
    }

    MPI_Finalize();
 	return 0;
}

