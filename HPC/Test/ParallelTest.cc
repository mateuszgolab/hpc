#include "gtest/gtest.h"
#include "mpiMock.h"


using namespace std;

TEST(parallelAlgorithmTest, haloNodesExchangeTest) {

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
			m2.setValue(i,j ,10 - i);
		}
	}

	mpiMock mock;

	mock.exchangeHaloNodesMock(m, 0, 10);
	mock.exchangeHaloNodesMock(m2, 1, 10);


	for(int i = 0; i < 10; i++)
	{
		m(0, i) == 10;
		m2(9, i) == 0;
	}
	
}