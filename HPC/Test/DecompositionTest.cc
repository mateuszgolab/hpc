#include "gtest/gtest.h"
#include "mpiMock.h"



TEST(sendResultsTest, dataAmountTest) 
{

	matrix m0(2,9);
	matrix m1(2,9);
	matrix m2(2,9);
	matrix m3(3,9);

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			m0.setValue(j, i, i);
			m1.setValue(j, i, i + 2);
			m2.setValue(j, i, i + 4);
			m3.setValue(j, i, i + 6);
		}
	}

	for(int j = 0; j < 9; j++)
	{
		m3.setValue(j, 2, 8);
	}

	mpiMock mock;
	mock.sendResultsMock(m1, 1);
	mock.sendResultsMock(m2, 2);
	mock.sendResultsMock(m3, 3);

	mock.receiveResultsMock(m0, 9, 2, 4, 0);

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			EXPECT_EQ(m0(j, i), i);
		}
	}
}