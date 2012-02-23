#include <map>
#include <iostream>
#include <Windows.h>
#include <typeinfo>
#include "Norm.h"
#include "InfinityNorm.h"
#include "EuclideanNorm.h"
#include "FirstNorm.h"
#include "AnalyticSolver.h"
#include "IterativeSolver.h"



#define N 64
#define ANALYTIC_ITERATIONS 100
#define JACOBI_ITERATIONS 1000

using namespace std;


void jacobiMethods(Norm & norm, int n, matrix & m)
{
	// jacobi 
	matrix m2(n,n);
	IterativeSolver::initMatrix(m2);
	map<int, double> mp;
	int time = GetTickCount();
	int it = IterativeSolver::jacobi(m2, JACOBI_ITERATIONS, mp, norm);
	cout<<"jacobi using "<<typeid(norm).name()<<endl;
	cout<<GetTickCount() - time<<" ms"<<endl;
	cout<<it<<" iterations"<<endl;
	double accuracy = matrix::validate(m, m2);
	cout<<"validated successfully with "<<accuracy<<" accuracy"<<endl<<endl;

	 //jacobi red black ordering
	matrix m3(n,n);
	IterativeSolver::initMatrix(m3);
	map<int, double> mp2;
	time = GetTickCount();
	it = IterativeSolver::jacobiRedBlack(m3, JACOBI_ITERATIONS, mp2, norm);
	cout<<"jacobi red-black ordering using "<<typeid(norm).name()<<endl;
	cout<<GetTickCount() - time<<" ms"<<endl;
	cout<<it<<" iterations"<<endl;
	accuracy = matrix::validate(m, m3);
	cout<<"validated successfully with "<<accuracy<<" accuracy"<<endl<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
}

void jacobiConvergence(Norm & norm, int n)
{
	// jacobi 
	matrix m(n,n);
	IterativeSolver::initMatrix(m);
	map<int, double> mp;
	map<int, double>::iterator it;
	IterativeSolver::jacobi(m, JACOBI_ITERATIONS, mp, norm);

	for(it = mp.begin(); it != mp.end(); it++)
	{
		cout<<(*it).second<<endl;
	}
}

void jacobiRedBlackConvergence(Norm & norm, int n)
{
	// jacobi red black ordering
	matrix m(n,n);
	IterativeSolver::initMatrix(m);
	map<int, double> mp;
	map<int, double>::iterator it;
	IterativeSolver::jacobiRedBlack(m, JACOBI_ITERATIONS, mp, norm);

	for(it = mp.begin(); it != mp.end(); it++)
	{
		cout<<(*it).second<<endl;
	}
}

void analyticSolution()
{
	// analytic solution
	cout<<"calculating analytic solution ..."<<endl;
	matrix m(N,N);
	AnalyticSolver::analyticSolution(m, ANALYTIC_ITERATIONS);
	cout<<"analytic solution calculated"<<endl;
}


int main()
{
	InfinityNorm infNorm;
	EuclideanNorm eucNorm;
	FirstNorm fstNorm;


	// analytic solution

	//cout<<"calculating analytic solution ..."<<endl;
	//matrix m(N,N);
	//analyticSolution(m, ANALYTIC_ITERATIONS);
	//cout<<"analytic solution calculated"<<endl<<endl;
	////m.printForChart();
	//cout<<endl;

	/*matrix m2(N,N);
	initMatrix(m2);
	m2.print();*/
	/*map<int, double> mp;
	matrix m2(N,N);
	initMatrix(m2);
	int it = jacobiRedBlack(m2, JACOBI_ITERATIONS, mp, infNorm);
	m2.printForChart();*/
	//jacobiMethods(infNorm, N, m);
	//m.printForChart();
	/*jacobiMethods(eucNorm, N, m);
	jacobiMethods(fstNorm, N, m);*/


	//jacobiConvergence(infNorm, N);
	jacobiRedBlackConvergence(infNorm, N);

	//cout<<"jacobi's convergence"<<endl;
	//cout<<"it norm_value"<<endl;
	//map<int, double>::iterator it;
	//for(it = mp.begin(); it != mp.end(); it++)
	//{
	//	cout<<(*it).first<<" "<<(*it).second<<endl;
	//}




	//m.graphPrint();
	//m2.graphPrint();

	// performace measurement
	//	private void timer_Tick(object sender, EventArgs e)
	//{
	//    performanceCounter1.InstanceName = instance;
	//    Utilization.Value = (int)(performanceCounter1.NextValue());
	//}
	//getchar();
	return 0;
}