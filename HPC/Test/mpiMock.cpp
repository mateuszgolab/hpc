#include "mpiMock.h"

using namespace std;



void mpiMock::exchangeHaloNodesMock(matrix & m, int rank, int size)
{
	if(rank > 0)
	{
		// sending second row
		MPI_Send_Mock(m.getSecondRow(), m.getNumberOfColumns(), rank - 1, rank);
		// receiving first row
		MPI_Recv_Mock(m.getFirstRow(), m.getNumberOfColumns(), rank - 1, rank);
	}

	if(rank < size - 1)
	{
		// sending penultimate row
		MPI_Send_Mock(m.getPenultimateRow(), m.getNumberOfColumns(), rank + 1, rank);
		// receiving last row
		MPI_Recv_Mock(m.getLastRow(), m.getNumberOfColumns(), rank + 1, rank);
	}
}

void  mpiMock::MPI_Send_Mock(double* data, int size, int rank , int tag)
{
	if(rank < tag)
	{
		haloNodesDown.insert(pair<int, double*>(tag, data));
	}
	else
	{
		haloNodesUp.insert(pair<int, double*>(tag, data));
	}
}

void  mpiMock::MPI_Recv_Mock(double*  data, int size, int rank , int tag)
{
	double *tmp = NULL;

	if(rank < tag)
	{
		if(haloNodesUp.find(rank) != haloNodesUp.end())
		{
			tmp = haloNodesUp[rank];
		}
	}
	else
	{
		if(haloNodesDown.find(rank) != haloNodesDown.end())
		{
			tmp = haloNodesDown[rank];
		}
	}

	
	if(tmp != NULL)
	{
		for(int i = 0; i < size; i++) data[i] = tmp[i];
	}
}

void mpiMock::addHaloNode(int rank, double* haloNode)
{
	haloNodesUp.insert(pair<int, double*>(rank, haloNode));
	haloNodesDown.insert(pair<int, double*>(rank, haloNode));
}

void mpiMock::printNode(double *node, int size)
{
	for(int i = 0; i < size; i++) printf("%f ", node[i]);
	puts("");
}