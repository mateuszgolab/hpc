#pragma once
#include"matrix.h"
#include<map>
#include<vector>

class mpiMock
{
	 std::vector<std::map<int, double*>> haloNodesUp;
	 std::vector<std::map<int, double*>> haloNodesDown;

	 static void printNode(double* node, int size);

public:
	mpiMock(int n);
	void MPI_Send_Mock(double* data, int size, int dstRank , int srcRank, int tag);
	void MPI_Recv_Mock(double* data, int size, int dstRank , int srcRank, int tag);
	void exchangeHaloNodesMock(matrix & m, int rank, int size);
	void addHaloNode(int rank,int tag, double* haloNode);
	void receiveResultsMock(const matrix & m, matrix & result, int sizeX, int sizeY, int size, int rank);
	void sendResultsMock(matrix &m,  int dstRank, int srcRank, int offset);
};

