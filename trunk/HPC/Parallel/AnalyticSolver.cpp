#include "AnalyticSolver.h"
#include <math.h>

void AnalyticSolver::analyticSolution(matrix &m, int iterations)
{
	double x = 0.0;
	double y = 0.0;
	double x_step = 1.0 / (m.getXsize() - 1);
	double y_step = 1.0 / (m.getYsize() - 1);
	double tmp;

	for(int i = 0; i < m.getYsize(); i++)
	{
		x = 0.0;
		for(int j = 0; j < m.getXsize(); j++)
		{
			tmp = 0.0;
			for(int it = 1; it < iterations; it+=2)
			{
				tmp += (-8 * sinh(it * M_PI * (1.0-x)) * sin(it * M_PI * y)) / (M_PI * it * (it * it - 4) * sinh(it * M_PI)) ;
			}
			m.setValue(i, j , tmp);
			x += x_step;
		}
		y += y_step;
	}
}