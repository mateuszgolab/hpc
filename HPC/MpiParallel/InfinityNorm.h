#pragma once

#include "Norm.h"

class InfinityNorm : public Norm
{
public :
	 double calculateNorm(matrix & prev, matrix & current);
	 double calculateNorm(matrix & r);

};

