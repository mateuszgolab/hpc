#include "AnalyticSolver.h"
#include <math.h>
#include <time.h>
#include<iostream>

using namespace std;

void AnalyticSolver::analyticSolution(matrix &m, int iterations)
{
	double x = 0.0;
	double y = 0.0;
	double x_step = 1.0 / (m.getXsize() - 1);
	double y_step = 1.0 / (m.getYsize() - 1);
	double tmp;

	for(int i = 0; i < m.getXsize(); i++)
	{
		y = 0.0;
		for(int j = 0; j < m.getYsize(); j++)
		{
			tmp = 0.0;
			
			for(int it = 1; it < iterations; it+=2)
			{
				tmp += (-8 * sinh(it * M_PI * (1.0-x)) * sin(it * M_PI * y)) / (M_PI * it * (it * it - 4) * sinh(it * M_PI)) ;
			}
			m.setValue(i, j , tmp);
			y += y_step;
		}
		x += x_step;
	}
}

double AnalyticSolver::validate(matrix & m1, matrix & m2)
{
	if((m1.getXsize() != m2.getXsize()) || (m1.getYsize() != m2.getYsize())) return -1.0;

	srand(unsigned int(time(0)));
	double accuracy = 0.0;

	for(int i = 0; i < m1.getXsize(); i++)
	{
		int x = rand() % m1.getXsize();
		int y = rand() % m2.getYsize();
		
		if(abs(m1(x,y) - m2(x,y)) > accuracy) accuracy = abs(m1(x,y) - m2(x,y));
	}

	return accuracy;
}