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

	for(int i = 1; i < m.getXsize() - 1; i++)
	{
		for(int j = 1; j < m.getYsize() - 1; j++)
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

TEST(MatrixInitializationTest, StripeRowsMatrixBoudaryColumns)
{
	matrix m(100, 10);
	IterativeSolver::initMatrix(m);

	for(int i = 0; i < m.getYsize(); i++)
	{	
		EXPECT_EQ(m(m.getXsize() - 1, i), 0.0);
	}


	for(int j = 1; j < m.getYsize() - 1; j++)
	{
		EXPECT_NE(m(0, j), 0.0);
	}
}

TEST(MatrixInitializationTest, StripeRowsMatrixBoudaryRows)
{
	matrix m(100, 10);
	IterativeSolver::initMatrix(m);



	for(int j = 0; j < m.getYsize(); j++)
	{
		EXPECT_EQ(m(j, m.getXsize() - 1), 0.0);
		EXPECT_EQ(m(j, 0), 0.0);
	}

}



TEST(MatrixInitializationTest, BoundaryValuesTest) 
{
	matrix m(100,100);
	IterativeSolver::initMatrix(m);

	for(int i = 0; i < m.getYsize(); i++)
	{	
		EXPECT_LE(m(m.getXsize() - 1, i), STOP_CRITERION);
		EXPECT_LE(m(0, i), STOP_CRITERION);

	}

	for(int j = 0; j < m.getYsize(); j++)
	{
		EXPECT_LE(m(j, m.getYsize() - 1), STOP_CRITERION);
	}

	for(int j = 1; j < m.getYsize() - 1; j++)
	{
		EXPECT_NE(m(j, 0), 0.0);
	}
}