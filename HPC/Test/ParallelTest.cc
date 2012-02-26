#include "gtest/gtest.h"
#include "mpiMock.h"


using namespace std;

TEST(parallelAlgorithmTest, haloNodesExchangeTest) {

	matrix m(10,10);
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			m.setValue(i,j ,j);
		}
	}

	double* upHaloNode = m.getFirstRow();
	double*	downHaloNode = m.getLastRow();

	mpiMock mock;
	mock.addHaloNode(1, m.getSecondRow());
	mock.exchangeHaloNodesMock(m, 0, 10, upHaloNode, downHaloNode);


	for(int i = 0; i < 10; i++)
	{
		EXPECT_EQ(m(i, 9), 1);
	}	
}