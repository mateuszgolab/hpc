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
		MPI_Recv(m.getFirstRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank, MPI_COMM_WORLD, &status);
	}

	if(rank < size - 1)
	{
		// sending penultimate row
		MPI_Send(m.getPenultimateRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank, rank, MPI_COMM_WORLD);
		// receiving last row
		MPI_Recv(m.getLastRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank, MPI_COMM_WORLD, &status);
	}
}

void jacobiRedBlack(matrix &m, Norm &norm, int rank, int size, int iterations)
{
	double error, maxError;
	IterativeSolver::initMatrix(m);
	maxError = 0.0;

	for(int i = 0; i < iterations; i++)
	{
		error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

		exchangeHaloNodes(m, rank, size);

		if(maxError < STOP_CRITERION) break;
	}
}

void receiveResults(const matrix & m, matrix & result, int sizeX, int sizeY, int size, int rank)
{
	MPI_Status status;
	int i = sizeY;
	int limit = 0;

	for(int rnk = 1; rnk < size - 1; rnk++)
	{
		limit = (rnk + 1)*sizeY;
		for(; i < limit; i++)
		{
			MPI_Recv(result.getRow(i), sizeX, MPI_DOUBLE, rnk, i, MPI_COMM_WORLD, &status);
		}
	}

	for(; i < sizeX; i++)
	{
		MPI_Recv(result.getRow(i), sizeX, MPI_DOUBLE, size - 1, i, MPI_COMM_WORLD, &status);
	}
}

void sendResults(matrix &m, int rank, int rows)
{
	int offset = rank * rows;

	for(int i = 0; i < m.getNumberOfRows(); i++)
	{
		MPI_Send(m.getRow(i), m.getNumberOfColumns(), MPI_DOUBLE, 0, i + offset, MPI_COMM_WORLD);
	}
}

int main(int argc, char **argv)
{
	int size, rank, sizeY, additionalSize, sizeX, iterations, rows;
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
	rows = sizeY;
	additionalSize = sizeX % size;


	if(rank == 0)
	{
		sizeY++;
	}
	else if(rank == size - 1)
	{
		sizeY += 1 + additionalSize;
	}
	else
	{
		sizeY += 2;
	}

	matrix m(sizeX, sizeY);

	//performing calculations
	jacobiRedBlack(m, norm, rank, size, iterations);
	

	//TODO : sending and receiving : tag matters !!!

	// results collection
	if(rank == 0)
	{
		matrix result(m, sizeX, sizeX);
		receiveResults(m, result, sizeX, sizeY, size, rank);
	}
	else //sending results 
	{
		sendResults(m, rank, rows);
	}

	MPI_Finalize();


	return 0;
}
