#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
	
int main (int argc, char *argv []) {

	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	double res;
	double a = 1.1;
	double b = 0.9;
	
	if (rank == 0) {
		res = a + b;
		printf("Process %d added: %.3f\n", rank, res);
	} 
	else if (rank == 1) {
		res = a - b;
		printf("Process %d subtracted: %.3f\n", rank, res);
	} 
	else if (rank == 2) {
		res = a * b;
		printf("Process %d multiplied: %.3f\n", rank, res);
	} 
	else if (rank == 3) {
		res = a / b;
		printf("Process %d divided : %.3f\n", rank, res);
	}
	
	MPI_Finalize();
	
	return 0;

}