#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	double i, y, sum = 0.0;
	double final_sum;
	//step of step_size in every process
	double step_size = 0.0001;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//each process receives an interval
	for (i = (double)(rank/size); i < (double)((rank + 1)/size); i += step_size)
	{
		y = 4 / (1 + i * i);
		//add area of rectangle to sum
		sum += y * step_size;
	}

	//add individual sums from each process
	MPI_Reduce(&sum, &final_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("The sum received is %lf\n", final_sum);
		//printf("Value of pi is final_sum / 4 = %lf\n", final_sum / (double)4);
	}

	MPI_Finalize();
	return 0;
}