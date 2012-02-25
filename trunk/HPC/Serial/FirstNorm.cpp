#include "FirstNorm.h"


double FirstNorm::calculateNorm(matrix & prev, matrix & current)
{
	
	double max = 0.0;
	double error = 0.0;

	for(int i = 0; i < prev.getNumberOfColumns(); i++)
	{
		error = 0.0;
		for(int j = 0; j < current.getNumberOfRows(); j++)
		{
			error += abs(prev(i, j) - current(i, j));
		}

		if(error > max) max = error;
	}

	return max;
}

double FirstNorm::calculateNorm(matrix & r)
{
	double max = 0.0;
	double error = 0.0;

	for(int i = 0; i < r.getNumberOfColumns(); i++)
	{
		error = 0.0;
		for(int j = 0; j < r.getNumberOfRows(); j++)
		{
			error += r(i, j);
			r.setValue(i, j, 0.0);
		}

		if(error > max) max = error;
	}

	return max;
}

