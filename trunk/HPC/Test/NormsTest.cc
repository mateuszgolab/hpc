#include "gtest/gtest.h"
#include "FirstNorm.h"
#include "InfinityNorm.h"
#include "EuclideanNorm.h"

using namespace std;

TEST(FirstNormTest, equalsMatricesTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j ,i);
		}
	}

	FirstNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 0.0);
	
}

TEST(FirstNormTest, differentMatricesTest1) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j ,i + 1);
		}
	}

	FirstNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 10.0);
	
}

TEST(FirstNormTest, differentMatricesTest2) {

	matrix m(10,10);
	// last row = 135
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j , i+j);
		}
	}

	// last row = 45
	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j , i);
		}
	}

	FirstNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 90.0);
	
}

TEST(InfinityNormTest, equalsMatricesTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j ,i);
		}
	}

	InfinityNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 0.0);
	
}

TEST(InfinityNormTest, differentMatricesTest1) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j ,i + 1);
		}
	}

	InfinityNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 10.0);
	
}

TEST(InfinityNormTest, differentMatricesTest2) {

	matrix m(10,10);
	// last row = 135
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j , i+j);
		}
	}

	// last row = 90
	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j , i);
		}
	}

	InfinityNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 45.0);
	
}

TEST(EuclideanNormTest, equalsMatricesTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j ,i);
		}
	}

	EuclideanNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 0.0);
	
}

TEST(EuclideanNormTest, differentMatricesTest1) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i, j ,i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i, j ,i + 1);
		}
	}

	EuclideanNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 10.0);
	
}

TEST(EuclideanNormTest, differentMatricesTest2) {

	matrix m(10,10);

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j , i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j , i + 2);
		}
	}

	EuclideanNorm norm;
	EXPECT_EQ(norm.calculateNorm(m, m2), 20.0);
	
}