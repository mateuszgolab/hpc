#include "InfinityNorm.h"


double InfinityNorm::calculateNorm(matrix & prev, matrix & current)
{
	double max = 0.0;
	double error = 0.0;

	for(int i = 0; i < prev.getNumberOfRows(); i++)
	{
		error = 0.0;
		for(int j = 0; j < current.getNumberOfColumns(); j++)
		{
			error += fabs(prev(i, j) - current(i, j));
		}

		if(error > max) max = error;
	}

	return max;
}

double InfinityNorm::calculateNorm(matrix & r)
{
	double max = 0.0;
	double error = 0.0;

	for(int i = 0; i < r.getNumberOfRows(); i++)
	{
		error = 0.0;
		for(int j = 0; j < r.getNumberOfColumns(); j++)
		{
			error += r(i, j);
			r.setValue(i, j, 0.0);
		}

		if(error > max) max = error;
	}

	return max;
}

