#include "gtest/gtest.h"
#include "mpiMock.h"



TEST(sendResultsTest, dataAmountTest) 
{

	matrix m0(2,9);
	matrix m1(2,9);
	matrix m2(2,9);
	matrix m3(3,9);

	int rows = 2;

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			m0.setValue(i, j, i);
			m1.setValue(i, j, i + 2);
			m2.setValue(i, j, i + 4);
			m3.setValue(i, j, i + 6);
		}
	}
	for(int j = 0; j < 9; j++)
	{
		m3.setValue(2, j, 8);
	}

	mpiMock mock(4);
	mock.sendResultsMock(m1, 0, 1, rows);
	mock.sendResultsMock(m2, 0, 2, rows);
	mock.sendResultsMock(m3, 0, 3, rows);

	matrix result(m0, 9, 9);

	mock.receiveResultsMock(m0,result, 9, 2, 4, 0);
	
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			EXPECT_EQ(result(i, j), i);
		}
	}
}