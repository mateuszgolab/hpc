#pragma once

#include "matrix.h"
#include <map>
#include <iostream>
#include "Norm.h"

#define STOP_CRITERION 0.001

class IterativeSolver
{
public:

	void static initMatrix(matrix &m);
	int static jacobi(matrix &m, int iterations, std::map<int, double> & convergence, Norm & norm);
	int static jacobiRedBlack(matrix &m, int iterations, std::map<int, double> & convergence, Norm & norm);

};

