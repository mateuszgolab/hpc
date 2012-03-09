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



#define N 256
#define ANALYTIC_ITERATIONS 100
#define JACOBI_ITERATIONS 100000

using namespace std;


void jacobiMethods(Norm & norm, int n, matrix & m, double epsilon)
{
	// jacobi 
	matrix m2(n,n);
	IterativeSolver::initMatrix(m2);
	map<int, double> mp;
	int time = GetTickCount();
	int it = IterativeSolver::jacobi(m2, JACOBI_ITERATIONS, mp, norm, epsilon);
	cout<<"jacobi using "<<typeid(norm).name()<<endl;
	cout<<GetTickCount() - time<<" ms"<<endl;
	cout<<it<<" iterations"<<endl;
	double accuracy = AnalyticSolver::validate(m, m2);
	cout<<"validated successfully with "<<accuracy<<" accuracy"<<endl<<endl;

	 //jacobi red black ordering
	matrix m3(n,n);
	IterativeSolver::initMatrix(m3);
	map<int, double> mp2;
	time = GetTickCount();
	it = IterativeSolver::jacobiRedBlack(m3, JACOBI_ITERATIONS, mp2, norm, epsilon);
	cout<<"jacobi red-black ordering using "<<typeid(norm).name()<<endl;
	cout<<GetTickCount() - time<<" ms"<<endl;
	cout<<it<<" iterations"<<endl;
	cout<<"validated successfully with "<<accuracy<<" accuracy"<<endl<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;

}

void jacobiConvergence(Norm & norm, int n, double epsilon)
{
	// jacobi 
	matrix m(n,n);
	IterativeSolver::initMatrix(m);
	map<int, double> mp;
	map<int, double>::iterator it;
	IterativeSolver::jacobi(m, JACOBI_ITERATIONS, mp, norm, epsilon);

	for(it = mp.begin(); it != mp.end(); it++)
	{
		cout<<(*it).second<<endl;
	}
}

void jacobiRedBlackConvergence(Norm & norm, int n, double epsilon)
{
	// jacobi red black ordering
	matrix m(n,n);
	IterativeSolver::initMatrix(m);
	map<int, double> mp;
	map<int, double>::iterator it;
	IterativeSolver::jacobiRedBlack(m, JACOBI_ITERATIONS, mp, norm, epsilon);

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
	//
	matrix m(10,10);
	AnalyticSolver::analyticSolution(m, 100);
	m.graphPrint();
	m.print();

	//matrix m2(10,10);
	//map<int, double> mp;
	//cout<<endl;
	//
	//IterativeSolver::initMatrix(m2);
	//m2.printForChart();
	//IterativeSolver::jacobi(m2, 100, mp, infNorm);
	//cout<<endl;
	//m2.printForChart();


	/*matrix m(N, N);
	AnalyticSolver::analyticSolution(m, ANALYTIC_ITERATIONS);

	jacobiMethods(infNorm, N, m);
	jacobiMethods(fstNorm, N, m);
	jacobiMethods(eucNorm, N, m);*/

	return 0;
}