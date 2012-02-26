#include "gtest/gtest.h"
#include "mpiMock.h"


using namespace std;

TEST(haloNodesExchangeTest, haloNodesTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,j);
		}
	}


	mpiMock mock;
	mock.addHaloNode(1, m.getSecondRow());
	mock.exchangeHaloNodesMock(m, 0, 10);


	for(int i = 0; i < 10; i++)
	{
		EXPECT_EQ(m(i, 9), 1);
	}	
}

TEST(haloNodesExchangeTest, twoNodesTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,j);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j ,j);
		}
	}

	mpiMock mock;
	mock.exchangeHaloNodesMock(m, 0, 10);
	mock.exchangeHaloNodesMock(m2, 1, 10);
	mock.exchangeHaloNodesMock(m, 0, 10);

	for(int i = 0; i < 10; i++)
	{
		EXPECT_EQ(m2(i, 0), 8); 
		EXPECT_EQ(m2(i, 1), 1); 

		EXPECT_EQ(m(i, 8), 8); 
		EXPECT_EQ(m(i, 9), 1); 
	}	
}

TEST(haloNodesExchangeTest, downNodeTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,j);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i,j ,j);
		}
	}

	mpiMock mock;
	mock.exchangeHaloNodesMock(m, 0, 10);
	mock.exchangeHaloNodesMock(m2, 1, 10);

	for(int i = 0; i < 10; i++)
	{
		EXPECT_EQ(m2(i, 0), 8); 
		EXPECT_EQ(m2(i, 1), 1); 
	}	
}

TEST(haloNodesExchangeTest, upNodeTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i, j ,j);
		}
	}

	matrix m2(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m2.setValue(i, j ,j);
		}
	}

	mpiMock mock;
	mock.exchangeHaloNodesMock(m2, 1, 10);
	mock.exchangeHaloNodesMock(m, 0, 10);

	for(int i = 0; i < 10; i++)
	{
		EXPECT_EQ(m(i, 8), 8);
		EXPECT_EQ(m(i, 9), 1); 
	}	
}

TEST(haloNodesExchangeTest, threeNodesTest) {

	matrix m(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m.setValue(i,j ,j);
		}
	}

	matrix m2(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m2.setValue(i,j ,j);
		}
	}

	matrix m3(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m3.setValue(i,j ,j);
		}
	}


	mpiMock mock;
	mock.exchangeHaloNodesMock(m2, 1, 3);
	mock.exchangeHaloNodesMock(m, 0, 3);
	mock.exchangeHaloNodesMock(m3, 2, 3);
	mock.exchangeHaloNodesMock(m2, 1, 3);


	for(int i = 0; i < 3; i++)
	{
		EXPECT_EQ(m(i, 0), 0); 
		EXPECT_EQ(m(i, 1), 1); 
		EXPECT_EQ(m(i, 2), 1); 

		EXPECT_EQ(m3(i, 0), 1); 
		EXPECT_EQ(m3(i, 1), 1); 
		EXPECT_EQ(m3(i, 2), 2); 

		EXPECT_EQ(m2(i, 0), 1); 
		EXPECT_EQ(m2(i, 1), 1); 
		EXPECT_EQ(m2(i, 2), 1);
	}	
}

TEST(haloNodesExchangeTest, middleNodeTest) {

	matrix m(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m.setValue(i,j ,j);
		}
	}

	matrix m2(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m2.setValue(i,j ,j);
		}
	}

	matrix m3(3,3);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m3.setValue(i,j ,j);
		}
	}


	mpiMock mock;
	mock.exchangeHaloNodesMock(m, 0, 3);
	mock.exchangeHaloNodesMock(m3, 2, 3);
	mock.exchangeHaloNodesMock(m2, 1, 3);


	for(int i = 0; i < 3; i++)
	{
		EXPECT_EQ(m2(i, 0), 1); 
		EXPECT_EQ(m2(i, 1), 1); 
		EXPECT_EQ(m2(i, 2), 1);
	}	
}
