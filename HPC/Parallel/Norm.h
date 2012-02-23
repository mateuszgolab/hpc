#pragma once
#include "matrix.h"
#include <math.h>


class Norm
{
public:
	virtual double calculateNorm(matrix & prev, matrix & current) = 0;
	virtual double calculateNorm(matrix & r) = 0;

};

