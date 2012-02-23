#include "gtest/gtest.h"
#include "matrix.h"
#include "AnalyticSolver.h"
#include "IterativeSolver.h"

TEST(AnalyticSolutionTest, ValuesRangeTest) {

	matrix m(100,100);
	AnalyticSolver::analyticSolution(m, 100);

	for(int i = 0; i < m.getXsize(); i++)
	{
		for(int j = 0; j < m.getYsize(); j++)
		{
			EXPECT_LE(m(i,j), 1.000001);
			EXPECT_GE(m(i,j), -0.000001);
		}
	}
}


TEST(AnalyticSolutionTest, BoundaryValuesTest) {

	matrix m(100,100);
	AnalyticSolver::analyticSolution(m, 100);
	for(int i = 0; i < m.getYsize(); i++)
	{	
		EXPECT_LE(m(m.getXsize() - 1, i), STOP_CRITERION);
		EXPECT_LE(m(0, i), STOP_CRITERION);
		
	}

	for(int j = 0; j < m.getYsize(); j++)
	{
		EXPECT_LE(m(j, m.getYsize() - 1), STOP_CRITERION);
	}
}

