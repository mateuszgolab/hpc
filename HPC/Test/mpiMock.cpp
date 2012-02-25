#include "mpiMock.h"

using namespace std;



void mpiMock::exchangeHaloNodesMock(matrix & m, int rank, int size)
{

	if(rank > 0)
	{
		// sending second row
		MPI_Send_Mock( m.getSecondRow(), m.getXsize(), rank - 1, rank);
		// receiving first row
		MPI_Recv_Mock(m.getFirstRow(), m.getXsize(), rank - 1, rank - 1);
	}

	if(rank < size - 1)
	{
		// sending penultimate row
		MPI_Send_Mock(m.getPenultimateRow(), m.getXsize(), rank + 1, rank);
		// receiving last row
		MPI_Recv_Mock(m.getLastRow(), m.getXsize(), rank + 1, rank + 1);
	}
}

void  mpiMock::MPI_Send_Mock(double* data, int size, int rank , int tag)
{
	haloNodes.insert(pair<int, double*>(rank, data));
}

void  mpiMock::MPI_Recv_Mock(double* data, int size, int rank , int tag)
{
	data = haloNodes[rank];
}
