#pragma once
#include"matrix.h"
#include<map>

class mpiMock
{
	 std::map<int, double*> haloNodesUp;
	 std::map<int, double*> haloNodesDown;

	 static void printNode(double* node, int size);

public:
	void MPI_Send_Mock(double* data, int size, int rank , int tag);
	void MPI_Recv_Mock(double* data, int size, int rank , int tag);
	void exchangeHaloNodesMock(matrix & m, int rank, int size);
	void addHaloNode(int rank, double* haloNode);
	void receiveResultsMock(const matrix & m, int sizeX, int sizeY, int size, int rank);
	void sendResultsMock(matrix &m, int rank);
};

