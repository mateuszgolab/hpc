#pragma once
#include "norm.h"
class FirstNorm : public Norm
{
public:
	double calculateNorm(matrix & prev, matrix & current);
	double calculateNorm(matrix & r);

};

