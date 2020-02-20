#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank, size, N, i = 0, length;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	char sendString1[100], sendString2[100], receiveString1[100], finalString[100], receiveString2[100];

	if (rank == 0)
	{
		N = size;
		// fprintf(stdout, "Enter length of string\n");
		// fflush(stdout);
	
		// scanf("%d", &length);

		fprintf(stdout, "Enter the first string\n");
		fflush(stdout);

		scanf("%s", sendString1);

		fprintf(stdout, "Enter the second string\n");
		fflush(stdout);

		scanf("%s", sendString2);

		length = strlen(sendString1);
	}

	MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);

	//evenly dividing string to be sent
	int m = length / size;

	MPI_Scatter(sendString1, m, MPI_CHAR, receiveString1, m, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Scatter(sendString2, m, MPI_CHAR, receiveString2, m, MPI_CHAR, 0, MPI_COMM_WORLD);

	char intermediateString[100] = "";
	//perform the intermediate concatenation
	for (int j = 0; j < m; j++)
	{
		char a[1];
		a[0] = receiveString1[j];
		//append char by char
		strcat(intermediateString, a);
		a[0] = receiveString2[j];
		strcat(intermediateString, a);
		// fprintf(stdout, "%s\n", intermediateString);
		// fflush(stdout);
	}

	fprintf(stdout, "\nProcess %d, string is %s\n", rank, intermediateString);
	fflush(stdout);
	
	MPI_Gather(intermediateString, 2 * m, MPI_CHAR, finalString, 2 * m, MPI_CHAR, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		fprintf(stdout, "\nThe final string is %s\n", finalString);
	}

	MPI_Finalize();

	return 0;
}
