#include "AnalyticSolver.h"
#include <math.h>
#include <time.h>
#include<iostream>

using namespace std;

void AnalyticSolver::analyticSolution(matrix &m, int iterations)
{
	double x = 0.0;
	double y = 0.0;
	double x_step = 1.0 / (m.getNumberOfColumns() - 1);
	double y_step = 1.0 / (m.getNumberOfRows() - 1);
	double tmp;

	for(int i = 0; i < m.getNumberOfRows(); i++)
	{
		x = 0.0;
		for(int j = 0; j < m.getNumberOfColumns(); j++)
		{
			tmp = 0.0;
			
			for(int it = 1; it < iterations; it+=2)
			{
				tmp += (-8 * sinh(it * M_PI * (1.0-x)) * sin(it * M_PI * y)) / (M_PI * it * (it * it - 4) * sinh(it * M_PI)) ;
			}
			m.setValue(i, j, tmp);
			x += x_step;
		}
		y += y_step;
	}
}

double AnalyticSolver::validate(matrix & m1, matrix & m2)
{
	if((m1.getNumberOfColumns() != m2.getNumberOfColumns()) || (m1.getNumberOfRows() != m2.getNumberOfRows())) return -1.0;

	srand(unsigned int(time(0)));
	double accuracy = 0.0;

	for(int i = 0; i < m1.getNumberOfRows(); i++)
	{
		int c = rand() % m1.getNumberOfColumns();
		int r = rand() % m1.getNumberOfRows();
		
		if(abs(m1(r,c) - m2(r,c)) > accuracy) accuracy = abs(m1(r,c) - m2(r,c));
	}

	return accuracy;
}