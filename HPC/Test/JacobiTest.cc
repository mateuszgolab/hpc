#include "gtest/gtest.h"
#include "InfinityNorm.h"
#include "IterativeSolver.h"
#include "AnalyticSolver.h"

using namespace std;


TEST(JacobiTest, ValuesTest) {

	InfinityNorm norm;
	matrix m(10,10);
	IterativeSolver::initMatrix(m);
	map<int, double> mp;
	IterativeSolver::jacobi(m, 1000, mp, norm);

	matrix m2(10,10);
	IterativeSolver::initMatrix(m2);

	for(int i = 1; i < m.getNumberOfRows() - 1; i++)
	{
		for(int j = 1; j < m.getNumberOfColumns() - 1; j++)
		{
			EXPECT_NE(m(i,j), m2(i,j));
		}
	}
}

TEST(JacobiTest, ConvergenceTest)
{
	InfinityNorm norm;
	matrix m(10, 10);
	IterativeSolver::initMatrix(m);

	map<int, double> mp;
	IterativeSolver::jacobi(m, 1000, mp, norm);
	map<int, double>::iterator it;
	double prev = 1000000000000;
	for(it = mp.begin(); it != mp.end(); it++)
	{
		EXPECT_LT((*it).second, prev);
		prev = (*it).second;
	}
}

TEST(JacobiRedBlackTest, ValuesTest) {

	InfinityNorm norm;
	matrix m(10,10);
	IterativeSolver::initMatrix(m);
	map<int, double> mp;
	IterativeSolver::jacobiRedBlack(m, 1000, mp, norm);

	matrix m2(10,10);
	IterativeSolver::initMatrix(m2);

	for(int i = 1; i < m.getNumberOfColumns() - 1; i++)
	{
		for(int j = 1; j < m.getNumberOfRows() - 1; j++)
		{
			EXPECT_NE(m(i,j), m2(i,j));
		}
	}

}

TEST(JacobiRedBlackTest, ConvergenceTest)
{
	InfinityNorm norm;
	matrix m(10, 10);
	IterativeSolver::initMatrix(m);

	map<int, double> mp;
	IterativeSolver::jacobiRedBlack(m, 1000, mp, norm);
	map<int, double>::iterator it;
	double prev = 1000000000000;
	for(it = mp.begin(); it != mp.end(); it++)
	{
		EXPECT_LT((*it).second, prev);
		prev = (*it).second;
	}
}

TEST(JacobiRedBlackForParallelTest, ValuesTest) 
{
	
	InfinityNorm norm;
	matrix m(10,10);
	IterativeSolver::initMatrix(m);

	for(int i = 0; i < 100; i++)
	{
		IterativeSolver::jacobiRedBlackForParallel(m, norm);
	}

	matrix m2(10,10);
	IterativeSolver::initMatrix(m2);

	for(int i = 1; i < m.getNumberOfColumns() - 1; i++)
	{
		for(int j = 1; j < m.getNumberOfRows() - 1; j++)
		{
			EXPECT_GE(m(i,j), m2(i,j));
		}
	}
}

TEST(JacobiRedBlackForParallelTest, ValuesTest2) 
{
	InfinityNorm norm;
	matrix m(10,10);
	IterativeSolver::initMatrix(m);

	for(int i = 0; i < 100; i++)
	{
		IterativeSolver::jacobiRedBlackForParallel(m, norm);
	}

	matrix m2(10,10);
	AnalyticSolver::analyticSolution(m2, 100);

	EXPECT_LE(AnalyticSolver::validate(m, m2), 0.01);

}

TEST(JacobiRedBlackForParallelTest, ValuesTest3) 
{
	InfinityNorm norm;
	matrix m(16, 32);
	IterativeSolver::initMatrix(m);
	
	for(int i = 0; i < 500; i++)
	{
		IterativeSolver::jacobiRedBlackForParallel(m, norm);
	}
	

	matrix m2(32, 32);
	AnalyticSolver::analyticSolution(m2, 100);
	
	EXPECT_LE(AnalyticSolver::validate(m, m2), STOP_CRITERION);

}

TEST(JacobiRedBlackForParallelTest, ConvergenceTest)
{
	InfinityNorm norm;
	matrix m(10, 10);
	IterativeSolver::initMatrix(m);
	IterativeSolver::jacobiRedBlackForParallel(m, norm);

	matrix m2(m);
	IterativeSolver::jacobiRedBlackForParallel(m2, norm);
	double r1 = norm.calculateNorm(m, m2);

	matrix m3(m2);
	IterativeSolver::jacobiRedBlackForParallel(m2, norm);
	double r2 = norm.calculateNorm(m2, m3);

	EXPECT_LE(r2, r1);
}

TEST(MatrixInitialionTest, StripeDecompositionColumns)
{
	matrix m(100, 10);
	IterativeSolver::initMatrix(m);

	for(int j = 1; j < m.getNumberOfColumns(); j++)
	{	
		EXPECT_EQ(m(0, j), 0.0);
		EXPECT_EQ(m(m.getNumberOfRows() - 1, j), 0.0);
	}

	EXPECT_NE(m(m.getNumberOfRows() / 2, 0), 0.0);

}

TEST(MatrixInitializationTest, StripeDecompositionRows)
{
	matrix m(10, 100);
	IterativeSolver::initMatrix(m);

	for(int i = 0; i < m.getNumberOfRows(); i++)
	{	
		EXPECT_EQ(m(i, m.getNumberOfColumns() - 1), 0.0);
	}

	for(int j = 0; j < m.getNumberOfColumns(); j++)
	{	
		EXPECT_EQ(m(0, j), 0.0);
	}
}

TEST(MatrixInitializationTest, BoundaryValuesTest) 
{
	matrix m(100,100);
	IterativeSolver::initMatrix(m);

	for(int j = 0; j < m.getNumberOfColumns(); j++)
	{	
		EXPECT_LE(m(0, j), STOP_CRITERION);
		EXPECT_LE(m(m.getNumberOfRows() - 1, j), STOP_CRITERION);
	}

	for(int i = 0; i < m.getNumberOfRows(); i++)
	{
		EXPECT_LE(m(i, m.getNumberOfColumns() - 1), STOP_CRITERION);
	}

	for(int i = 1; i < m.getNumberOfRows() - 1; i++)
	{
		EXPECT_NE(m(i, 0), 0.0);
	}
}

TEST(MatrixInitializationForParallelTest, BoundaryValuesTest) 
{
	matrix m(5, 10);
	matrix m1(5, 10);

	IterativeSolver::initMatrixForParallel(m, 0, 2);
	IterativeSolver::initMatrixForParallel(m1, 1, 2);

	for(int i = 0; i < 2; i++)
	{
		EXPECT_GE(m1(i, 0) , m(i, 0));

	}

}

TEST(MatrixInitializationForParallelTest, BoundaryValuesTest2) 
{
	matrix m(4, 20);
	matrix m1(4, 20);
	matrix m2(4, 20);
	matrix m3(4, 20);
	matrix m4(4, 20);

	IterativeSolver::initMatrixForParallel(m, 0, 5);
	IterativeSolver::initMatrixForParallel(m1, 1, 5);
	IterativeSolver::initMatrixForParallel(m2, 2, 5);
	IterativeSolver::initMatrixForParallel(m3, 3, 5);
	IterativeSolver::initMatrixForParallel(m4, 4, 5);

	for(int i = 1; i < 3; i++)
	{
		EXPECT_GE(m1(i, 0) , m(i, 0));
		EXPECT_GE(m2(i, 0) , m1(i, 0));
		EXPECT_GE(m2(i, 0) , m3(i, 0));
		EXPECT_GE(m3(i, 0) , m4(i, 0));
	}

}

