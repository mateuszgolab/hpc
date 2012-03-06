#include<stdio.h>
#include"mpi.h"
#include"matrix.h"
#include"IterativeSolver.h"
#include"InfinityNorm.h"
#include"AnalyticSolver.h"


#define DEFAULT_SIZE 128
#define DEFAULT_MAX_ITERATIONS 1000

void exchangeHaloNodes(matrix & m, int rank, int size)
{
	MPI_Status status;

	if(rank > 0)
	{
		//puts(" sending second row");
		// sending second row
		//MPI_Send(m.getSecondRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank, MPI_COMM_WORLD);
		MPI_Sendrecv(m.getSecondRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank, 
			m.getFirstRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
		//MPI_Isend(m.getSecondRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank, MPI_COMM_WORLD, &req);
		// receiving first row
		//puts(" receiving first row");
		//MPI_Recv(m.getFirstRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
	}

	if(rank < size - 1)
	{
		//puts("sending penultimate row");
		// sending penultimate row
	//	MPI_Send(m.getPenultimateRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank, MPI_COMM_WORLD);
		MPI_Sendrecv(m.getPenultimateRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank, 
			m.getLastRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank + 1, MPI_COMM_WORLD, &status);
		//MPI_Isend(m.getPenultimateRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank, MPI_COMM_WORLD, &req);
		//puts("receiving last row");
		// receiving last row
		//MPI_Recv(m.getLastRow(), m.getNumberOfColumns(), MPI_DOUBLE, rank + 1, rank + 1, MPI_COMM_WORLD, &status);
	}
}

void jacobiRedBlack(matrix &m, Norm &norm, int rank, int size, int iterations, int * iterationsPerformed)
{
	double error, maxError;
	int i = 0;
	IterativeSolver::initMatrixForParallel(m, rank, size);
	maxError = 0.0;

//	m.print();
	//puts("++++");

	for(i = 0; i < iterations; i++)
	{
		error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
//		printf("%f\n", error);
		exchangeHaloNodes(m, rank, size);
		if(maxError < STOP_CRITERION) break;
	}

	MPI_Allreduce(&i, iterationsPerformed, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
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
			//printf("receiving : %d\n", i);
			MPI_Recv(result.getRow(i), colsNumber, MPI_DOUBLE, rnk, i, MPI_COMM_WORLD, &status);
		}
	}

	for(; i < colsNumber; i++)
	{
		//printf("receiving : %d\n", i);
		MPI_Recv(result.getRow(i), colsNumber, MPI_DOUBLE, size - 1, i, MPI_COMM_WORLD, &status);
	}
}

void sendResults(matrix &m, int rank, int rows, int size)
{
	int offset = rank * rows - 1;
	int n = m.getNumberOfRows();

	if(rank < size - 1) n--;
	

	for(int i = 1; i < n; i++)
	{
		//printf("sending : %d\n", i+ offset); 
		MPI_Send(m.getRow(i), m.getNumberOfColumns(), MPI_DOUBLE, 0, i + offset, MPI_COMM_WORLD);
	}
}

int main(int argc, char **argv)
{
	int size, rank, rowsNumber, additionalSize, colsNumber, iterations, rows, iterationsPerformed;
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

	// initial synchronisation
	MPI_Barrier(MPI_COMM_WORLD);

	//time counting starts
	double start_time = MPI_Wtime();

	iterationsPerformed = 0;

	//performing calculations
	jacobiRedBlack(m, norm, rank, size, iterations, &iterationsPerformed);

//	m.print();
//	puts("----");
	// results collection
	if(rank == 0)
	{
		//puts("receiving");
		matrix result(m, colsNumber, colsNumber);
		receiveResults(result, colsNumber, rows, size);

		printf("Calculations time : %f seconds\n",  MPI_Wtime() - start_time);
		printf("Max number of iterations performed on every processor  : %d \n",  iterationsPerformed);
		puts("validating results ... ");
		//result.print();

		matrix m2(colsNumber, colsNumber);
		AnalyticSolver::analyticSolution(m2, 100);
		printf("error = %f\n",AnalyticSolver::validate(result, m2));
	}
	else //sending results 
	{
		//puts("sending");
		sendResults(m, rank, rows, size);
	}

	MPI_Finalize();

	return 0;
}
