// HPC-MPI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"

int main(int argc, char* argv[])
{

	MPI_Init(&argc, &argv);

	int procNum, procRank;
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

	int rbuf, sbuf = 30;
	MPI_Status status;

	if (procRank == 0) {
		MPI_Recv(&rbuf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("\nHello from proc 0. Recieved data: %d\n", rbuf);
	}
	else {
		MPI_Send(&sbuf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

    return 0;
}

