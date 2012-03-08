#include "gtest/gtest.h"
#include "mpiMock.h"


using namespace std;

TEST(HaloNodesExchangeTests, haloNodesTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,i);
		}
	}

	mpiMock mock(10);
	mock.addHaloNode(1, 0, m.getSecondRow());
	mock.exchangeHaloNodesMock(m, 0, 10);

	for(int j = 0; j < 10; j++)
	{
		EXPECT_EQ(m(9, j), 1);
	}	
}

TEST(HaloNodesExchangeTests, twoNodesTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i, j , i);
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

	mpiMock mock(10);
	mock.exchangeHaloNodesMock(m, 0, 10);
	mock.exchangeHaloNodesMock(m2, 1, 10);
	mock.exchangeHaloNodesMock(m, 0, 10);

	for(int j = 0; j < 10; j++)
	{
		EXPECT_EQ(m2(0, j), 8); 
		EXPECT_EQ(m2(1, j), 1); 

		EXPECT_EQ(m(8, j), 8); 
		EXPECT_EQ(m(9, j), 1); 
	}	
}

TEST(HaloNodesExchangeTests, downNodeTest) {

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
			m2.setValue(i,j ,i);
		}
	}

	mpiMock mock(10);
	mock.exchangeHaloNodesMock(m, 0, 10);
	mock.exchangeHaloNodesMock(m2, 1, 10);

	for(int j = 0; j < 10; j++)
	{
		EXPECT_EQ(m2(0, j), 8); 
		EXPECT_EQ(m2(1, j), 1); 
	}	
}

TEST(HaloNodesExchangeTests, upNodeTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i, j , i);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i, j , i);
		}
	}

	mpiMock mock(10);
	mock.exchangeHaloNodesMock(m2, 1, 10);
	mock.exchangeHaloNodesMock(m, 0, 10);

	for(int j = 0; j < 10; j++)
	{
		EXPECT_EQ(m(8, j), 8);
		EXPECT_EQ(m(9, j), 1); 
	}	
}

TEST(HaloNodesExchangeTests, threeNodesTest) {

	matrix m(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m.setValue(i,j , i);
		}
	}

	matrix m2(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m2.setValue(i,j , i);
		}
	}

	matrix m3(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m3.setValue(i,j ,i);
		}
	}


	mpiMock mock(10);
	mock.exchangeHaloNodesMock(m2, 1, 3);
	mock.exchangeHaloNodesMock(m, 0, 3);
	mock.exchangeHaloNodesMock(m3, 2, 3);
	mock.exchangeHaloNodesMock(m2, 1, 3);


	for(int j = 0; j < 3; j++)
	{
		EXPECT_EQ(m(0, j), 0); 
		EXPECT_EQ(m(1, j), 1); 
		EXPECT_EQ(m(2, j), 1); 

		EXPECT_EQ(m3(0, j), 1); 
		EXPECT_EQ(m3(1, j), 1); 
		EXPECT_EQ(m3(2, j), 2); 

		EXPECT_EQ(m2(0, j), 1); 
		EXPECT_EQ(m2(1, j), 1); 
		EXPECT_EQ(m2(2, j), 1);
	}	
}

TEST(HaloNodesExchangeTests, middleNodeTest) {

	matrix m(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m.setValue(i,j ,i);
		}
	}

	matrix m2(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m2.setValue(i,j ,i);
		}
	}

	matrix m3(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m3.setValue(i,j ,i);
		}
	}


	mpiMock mock(10);
	mock.exchangeHaloNodesMock(m, 0, 3);
	mock.exchangeHaloNodesMock(m3, 2, 3);
	mock.exchangeHaloNodesMock(m2, 1, 3);


	for(int j = 0; j < 3; j++)
	{
		EXPECT_EQ(m2(0, j), 1); 
		EXPECT_EQ(m2(1, j), 1); 
		EXPECT_EQ(m2(2, j), 1);
	}	
}
