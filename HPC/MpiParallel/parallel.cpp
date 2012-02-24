#include<stdio.h>
#include"mpi.h"
#include"matrix.h"
#include"IterativeSolver.h"
#include"InfinityNorm.h"

#define DEFAULT_SIZE 128
#define DEFAULT_MAX_ITERATIONS 1000

void exchangeHaloNodes(matrix m, int rank)
{
//	MPI_Send(tab[size_d - 2], size_x, MPI_DOUBLE, rank+DOWN, rank, MPI_COMM_WORLD);
//	MPI_Recv(halo_down, size_x, MPI_DOUBLE, rank+DOWN,rank+DOWN,MPI_COMM_WORLD,&status);
}

int main(int argc, char **argv)
{
	int size, rank, sizeY, additionalSize, sizeX, iterations;
	double error, maxError;
	MPI_Status status;
	InfinityNorm norm;

	

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("%d\n", rank);

	sizeX = DEFAULT_SIZE;
	if(argc > 1)
		sscanf(argv[1], "%d", &sizeX);

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

		for(int i; i < iterations; i++)
		{
			error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
			
			if(maxError < STOP_CRITERION) break;
		}
	}
	else if(rank == size - 1)
	{
		sizeY += 1 + additionalSize;
		matrix m(sizeX, sizeY);
		IterativeSolver::initMatrix(m);

		for(int i; i < iterations; i++)
		{
			error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
		}
	}
	else
	{
		sizeY += 2;
		matrix m(sizeX, sizeY);
		IterativeSolver::initMatrix(m);

		for(int i; i < iterations; i++)
		{
			error = IterativeSolver::jacobiRedBlackForParallel(m, norm);
			MPI_Barrier(MPI_COMM_WORLD);
			MPI_Allreduce(&error, &maxError, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
		}
	}


	MPI_Finalize();

	
	return 0;
}
