#pragma once
#include"matrix.h"
#include<map>

class mpiMock
{
	 std::map<int, double*> haloNodes;

public:
	void  MPI_Send_Mock(double* data, int size, int rank , int tag);
	void  MPI_Recv_Mock(double* data, int size, int rank , int tag);
	void  exchangeHaloNodesMock(matrix & m, int rank, int size);
};

