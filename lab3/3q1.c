#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, num_of_elements, sendArray[10], receiveArray[10], value, i = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0)
	{
		num_of_elements = size;
		fprintf(stdout, "Enter %d values\n", num_of_elements);
		fflush(stdout);

		for(i = 0; i < num_of_elements; i++)
			scanf("%d", &sendArray[i]);
	}

	MPI_Scatter(sendArray, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);
	fprintf(stdout, "Process %d has received number %d\n", rank, value);

	int factorial = 1;
	for (int j = 1; j <= value; j++)
		factorial *= j;

	MPI_Gather(&factorial, 1, MPI_INT, receiveArray, 1, MPI_INT, 0, MPI_COMM_WORLD);\

	if (rank == 0)
	{
		int sum = 0;
		for (i = 0; i < num_of_elements; i++)
			sum += receiveArray[i];

		fprintf(stdout, "\nThe final sum is %d\n", sum);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}