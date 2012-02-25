#include<stdio.h>
#include"mpi.h"
#include"matrix.h"
#include"IterativeSolver.h"
#include"InfinityNorm.h"

#define DEFAULT_SIZE 128
#define DEFAULT_MAX_ITERATIONS 1000

void exchangeHaloNodes(matrix & m, int rank, int size)
{
	MPI_Status status;

	if(rank > 0)
	{
		// sending second row
		MPI_Send(m.getSecondRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank, MPI_COMM_WORLD);
		// receiving first row
		MPI_Recv(m.getFirstRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
	}

	if(rank < size - 1)
	{
		// sending penultimate row
		MPI_Send(m.getPenultimateRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank, MPI_COMM_WORLD);
		// receiving last row
		MPI_Recv(m.getLastRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank + 1, MPI_COMM_WORLD, &status);
	}
}

int main(int argc, char **argv)
{
	int size, rank, sizeY, additionalSize, sizeX, iterations;
	double error, maxError;
	InfinityNorm norm;

	

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("%d\n", rank);

	sizeX = DEFAULT_SIZE;
	if(argc > 1)
		sscanf_s(argv[1], "%d", &sizeX);

	iterations = DEFAULT_MAX_ITERATIONS;
	if(argc > 2)
		sscanf(argv[2], "%d", &iterations);


	sizeY = sizeX / size;
	additionalSize = sizeX % size;
	maxError = 0.0;

	if(rank == 0)
	{
		sizeY++;
		matrix m(sizeX, sizeY);
		IterativeSolver::initMatrix(m);

		for(int i = 0; i < iterations; i++)
		{
			error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

			exchangeHaloNodes(m, rank, size);
			
			if(maxError < STOP_CRITERION) break;
		}
	}
	else if(rank == size - 1)
	{
		sizeY += 1 + additionalSize;
		matrix m(sizeX, sizeY);
		IterativeSolver::initMatrix(m);

		for(int i = 0; i < iterations; i++)
		{
			error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

			exchangeHaloNodes(m, rank, size);
		}
	}
	else
	{
		sizeY += 2;
		matrix m(sizeX, sizeY);
		IterativeSolver::initMatrix(m);

		for(int i = 0; i < iterations; i++)
		{
			error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

			exchangeHaloNodes(m, rank, size);
		}
	}


	MPI_Finalize();

	
	return 0;
}
