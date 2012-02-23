#include "InfinityNorm.h"


double InfinityNorm::calculateNorm(matrix & prev, matrix & current)
{
	double max = 0.0;
	double error = 0.0;

	for(int i = 0; i < prev.getYsize(); i++)
	{
		error = 0.0;
		for(int j = 0; j < current.getXsize(); j++)
		{
			error += abs(prev(i, j) - current(i,j));
		}

		if(error > max) max = error;
	}

	return max;
}

double InfinityNorm::calculateNorm(matrix & r)
{
	double max = 0.0;
	double error = 0.0;

	for(int i = 0; i < r.getYsize(); i++)
	{
		error = 0.0;
		for(int j = 0; j < r.getXsize(); j++)
		{
			error += r(i, j);
			r.setValue(i, j, 0.0);
		}

		if(error > max) max = error;
	}

	return max;
}

