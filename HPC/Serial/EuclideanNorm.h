#pragma once
#include "norm.h"
class EuclideanNorm : public Norm
{
public:
	double calculateNorm(matrix & prev, matrix & current);
	double calculateNorm(matrix & r);
};

