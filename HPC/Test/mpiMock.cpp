#include "mpiMock.h"

using namespace std;

mpiMock::mpiMock(int n)
{
	haloNodesDown.resize(n);
	haloNodesUp.resize(n);
}

void mpiMock::exchangeHaloNodesMock(matrix & m, int rank, int size)
{
	if(rank > 0)
	{
		// sending second row
		MPI_Send_Mock(m.getSecondRow(), m.getNumberOfColumns(), rank - 1, rank, 0);
		// receiving first row
		MPI_Recv_Mock(m.getFirstRow(), m.getNumberOfColumns(), rank - 1, rank, 0);
	}

	if(rank < size - 1)
	{
		// sending penultimate row
		MPI_Send_Mock(m.getPenultimateRow(), m.getNumberOfColumns(), rank + 1, rank, 0);
		// receiving last row
		MPI_Recv_Mock(m.getLastRow(), m.getNumberOfColumns(), rank + 1, rank, 0);
	}
}

void  mpiMock::MPI_Send_Mock(double* data, int size, int dstRank , int srcRank, int tag)
{
	if(dstRank < srcRank)
	{
		haloNodesUp[srcRank].insert(pair<int, double*>(tag, data));
	}
	else
	{
		haloNodesDown[srcRank].insert(pair<int, double*>(tag, data));
	}
}

void  mpiMock::MPI_Recv_Mock(double*  data, int size, int dstRank ,int srcRank, int tag)
{
	map<int, double*> map;
	double *tmp = NULL;

	if(dstRank > srcRank)
	{
		if(haloNodesUp[dstRank].size() > 0)
		{
			tmp = haloNodesUp[dstRank][tag];
		}
	}
	else
	{
		if(haloNodesDown[dstRank].size() > 0)
		{
			tmp = haloNodesDown[dstRank][tag];
		}
	}
	
	if(tmp != NULL)
	{
		for(int i = 0; i < size; i++) data[i] = tmp[i];
	}
}

void mpiMock::addHaloNode(int rank,int tag, double* haloNode)
{
	haloNodesUp[rank].insert(pair<int, double*>(tag, haloNode));
	haloNodesDown[rank].insert(pair<int, double*>(tag, haloNode));

}

void mpiMock::printNode(double *node, int size)
{
	for(int i = 0; i < size; i++) printf("%f ", node[i]);
	puts("");
}

void mpiMock::receiveResultsMock(const matrix & m, matrix & result, int sizeX, int sizeY, int size, int rank)
{
	int i = sizeY;
	int limit = 0;

	for(int rnk = 1; rnk < size - 1; rnk++)
	{
		limit = (rnk + 1)*sizeY;
		for(; i < limit; i++)
		{
			MPI_Recv_Mock(result.getRow(i), sizeX, rnk, rank, i);
		}
	}

	for(; i < sizeX; i++)
	{
		MPI_Recv_Mock(result.getRow(i), sizeX, size - 1,rank, i);
	}
}

void mpiMock::sendResultsMock(matrix &m, int dstRank, int srcRank, int rows)
{
	int offset = srcRank * rows;

	for(int i = 0; i < m.getNumberOfRows(); i++)
	{
		MPI_Send_Mock(m.getRow(i), m.getNumberOfColumns(), dstRank, srcRank, i + offset);
	}
}