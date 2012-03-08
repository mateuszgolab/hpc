#include "gtest/gtest.h"
#include "matrix.h"
#include "AnalyticSolver.h"
#include "IterativeSolver.h"

TEST(AnalyticSolutionTests, ValuesRangeTest) {

	matrix m(100,100);
	AnalyticSolver::analyticSolution(m, 100);

	for(int i = 0; i < m.getNumberOfRows(); i++)
	{
		for(int j = 0; j < m.getNumberOfColumns(); j++)
		{
			EXPECT_LE(m(i,j), 1.000001);
			EXPECT_GE(m(i,j), -0.000001);
		}
	}
}


TEST(AnalyticSolutionTests, BoundaryValuesTest) {

	matrix m(100,100);
	AnalyticSolver::analyticSolution(m, 100);
	for(int i = 0; i < m.getNumberOfRows(); i++)
	{	
		EXPECT_LE(m(i, m.getNumberOfColumns() - 1), STOP_CRITERION);
		
		
	}

	for(int j = 0; j < m.getNumberOfColumns(); j++)
	{
		EXPECT_LE(m(0, j), STOP_CRITERION);
		EXPECT_LE(m(m.getNumberOfRows() - 1, j), STOP_CRITERION);
	}
}

