#pragma once

#define STOP_CRITERION 0.001

#include"matrix.h"

class AnalyticSolver
{
public:

	void static analyticSolution(matrix &m, int iterations);
	double static validate(matrix &m1, matrix &m2);
};

