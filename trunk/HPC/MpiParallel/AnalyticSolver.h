#pragma once

#include"matrix.h"

class AnalyticSolver
{
public:

	void static analyticSolution(matrix &m, int iterations);
	double static validate(matrix &m1, matrix &m2);
};

