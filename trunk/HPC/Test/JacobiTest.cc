#include "gtest/gtest.h"
#include "InfinityNorm.h"
#include "IterativeSolver.h"

using namespace std;

TEST(JacobiTest, ValuesTest) {

	InfinityNorm norm;
	matrix m(10,10);
	IterativeSolver::initMatrix(m);
	map<int, double> mp;
	IterativeSolver::jacobi(m, 1000, mp, norm);

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
			EXPECT_NE(m(i,j), m2(i,j));
		}
	}
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

TEST(MatrixInitializationTest, StripeDecompositionColumns)
{
	matrix m(100, 10);
	IterativeSolver::initMatrix(m);

	for(int i = 0; i < m.getNumberOfColumns(); i++)
	{	
		EXPECT_EQ(m(i, 0), 0.0);
		EXPECT_EQ(m(m.getNumberOfRows() - 1, 0), 0.0);
	}

	EXPECT_NE(m(0, m.getNumberOfRows() / 2), 0.0);

}

TEST(MatrixInitializationTest, StripeDecompositionRows)
{
	matrix m(10, 100);
	IterativeSolver::initMatrix(m);

	for(int i = 0; i < m.getNumberOfRows(); i++)
	{	
		EXPECT_EQ(m(m.getNumberOfColumns() - 1, i), 0.0);
	}

	for(int i = 0; i < m.getNumberOfColumns(); i++)
	{	
		EXPECT_EQ(m(i, 0), 0.0);
	}


}

TEST(MatrixInitializationTest, BoundaryValuesTest) 
{
	matrix m(100,100);
	IterativeSolver::initMatrix(m);



	for(int i = 0; i < m.getNumberOfColumns(); i++)
	{	
		EXPECT_LE(m(i, 0), STOP_CRITERION);
		EXPECT_LE(m(i, m.getNumberOfRows() - 1), STOP_CRITERION);

	}

	for(int j = 0; j < m.getNumberOfRows(); j++)
	{
		EXPECT_LE(m(m.getNumberOfColumns() - 1,  j), STOP_CRITERION);
	}

	for(int j = 1; j < m.getNumberOfRows() - 1; j++)
	{
		EXPECT_NE(m(0, j), 0.0);
	}
}