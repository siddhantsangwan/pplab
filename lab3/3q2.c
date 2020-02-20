#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, N, sendArray[100], receiveArray[100], i = 0, M;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0)
	{
		N = size;
		fprintf(stdout, "Enter M\n");
		fflush(stdout);
	
		scanf("%d", &M);
	
		fprintf(stdout, "Enter N*M (%d) values\n", N * M);
		fflush(stdout);
	
		int array_size = N * M;
	
		for (i = 0; i < array_size; ++i)
			scanf("%d", &sendArray[i]);
	}

	//send M to all the processes, they receive it in their M
	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
	double avgReceived[size];

	MPI_Scatter(sendArray, M, MPI_INT, receiveArray, M, MPI_INT, 0, MPI_COMM_WORLD);

	//find average
	double average = 0;
	for (int j = 0; j < M; j++)
		average += receiveArray[j];
	average /= (double)M;

	MPI_Gather(&average, 1, MPI_DOUBLE, avgReceived, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	//find the final average
	if (rank == 0)
	{
		double total_avg = 0;
		for (i = 0; i < N; i++)
			total_avg += avgReceived[i];

		total_avg /= (double)N;

		fprintf(stdout, "\nThe final total average is %lf\n", total_avg);
		fflush(stdout);
	}

	MPI_Finalize();
	return 0;
}