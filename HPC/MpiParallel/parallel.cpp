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
		//puts(" sending second row");
		// sending second row
		MPI_Send(m.getSecondRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank, MPI_COMM_WORLD);
		// receiving first row
		//puts(" receiving first row");
		MPI_Recv(m.getFirstRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
	}

	if(rank < size - 1)
	{
		//puts("sending penultimate row");
		// sending penultimate row
		MPI_Send(m.getPenultimateRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank, MPI_COMM_WORLD);
		//puts("receiving last row");
		// receiving last row
		MPI_Recv(m.getLastRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank + 1, MPI_COMM_WORLD, &status);
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
//		printf("%f\n", error);
		exchangeHaloNodes(m, rank, size);
		if(maxError < STOP_CRITERION) break;
	}
}

void receiveResults(matrix & result, int colsNumber, int rowsNumber, int size)
{
	MPI_Status status;
	int i = rowsNumber;
	int limit = 0;

	for(int rnk = 1; rnk < size - 1; rnk++)
	{
		limit = (rnk + 1)*rowsNumber;
		for(; i < limit; i++)
		{
			MPI_Recv(result.getRow(i), colsNumber, MPI_DOUBLE, rnk, i, MPI_COMM_WORLD, &status);
		}
	}

	for(; i < colsNumber; i++)
	{
		MPI_Recv(result.getRow(i), colsNumber, MPI_DOUBLE, size - 1, i, MPI_COMM_WORLD, &status);
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
	int size, rank, rowsNumber, additionalSize, colsNumber, iterations, rows;
	InfinityNorm norm;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	colsNumber = DEFAULT_SIZE;
	if(argc > 1)
		sscanf(argv[1], "%d", &colsNumber);

	iterations = DEFAULT_MAX_ITERATIONS;
	if(argc > 2)
		sscanf(argv[2], "%d", &iterations);


	rowsNumber = colsNumber / size;
	rows = rowsNumber;
	additionalSize = colsNumber % size;


	if(rank == 0)
	{
		rowsNumber++;
	}
	else if(rank == size - 1)
	{
		rowsNumber += 1 + additionalSize;
	}
	else
	{
		rowsNumber += 2;
	}

	matrix m(rowsNumber, colsNumber);
	//performing calculations
	jacobiRedBlack(m, norm, rank, size, iterations);

	// results collection
	if(rank == 0)
	{
		//puts("receiving");
		matrix result(m, colsNumber, colsNumber);
		receiveResults(result, colsNumber, rowsNumber, size);

		result.print();
	}
	else //sending results 
	{
		//puts("sending");
		sendResults(m, rank, rows);
	}

	MPI_Finalize();

	return 0;
}
