#pragma once

#include "matrix.h"
#include <map>
#include <iostream>
#include "Norm.h"


class IterativeSolver
{
public:

	void static initMatrix(matrix &m);
	void static initMatrixForParallel(matrix &m, int rank, int size);
	int static jacobi(matrix &m, int iterations, std::map<int, double> & convergence, Norm & norm, double epsilon);
	int static jacobiRedBlack(matrix &m, int iterations, std::map<int, double> & convergence, Norm & norm, double epsilon);
	double static jacobiRedBlackForParallel(matrix &m, Norm & norm);

};

