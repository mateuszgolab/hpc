#include "FirstNorm.h"


double FirstNorm::calculateNorm(matrix & prev, matrix & current)
{
	
	double max = 0.0;
	double error = 0.0;

	for(int j = 0; j < prev.getNumberOfColumns(); j++)
	{
		error = 0.0;
		for(int i = 0; i < current.getNumberOfRows(); i++)
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

	for(int j = 0; j < r.getNumberOfColumns(); j++)
	{
		error = 0.0;
		for(int i = 0; i < r.getNumberOfRows(); i++)
		{
			error += r(i, j);
			r.setValue(i, j, 0.0);
		}

		if(error > max) max = error;
	}

	return max;
}

