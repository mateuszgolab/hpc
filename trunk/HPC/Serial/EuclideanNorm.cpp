#include "EuclideanNorm.h"


double EuclideanNorm::calculateNorm(matrix & prev, matrix & current)
{
	double error = 0.0;
	double value = 0.0;
	for(int i = 0; i < prev.getXsize(); i++)
	{
		for(int j = 0; j < current.getYsize(); j++)
		{
			value = abs(prev(i, j) - current(i,j));
			error += value * value;
		}
	}

	return sqrt(error);

}

double EuclideanNorm::calculateNorm(matrix & r)
{
	double error = 0.0;
	double value = 0.0;
	for(int i = 0; i < r.getYsize(); i++)
	{
		for(int j = 0; j < r.getXsize(); j++)
		{
			error += r(i,j) * r(i,j);
			r.setValue(i,j,0.0);
		}
	}

	return sqrt(error);
}
