#include "IterativeSolver.h"
#include <stdio.h>
#include <math.h>

using namespace std;

/**
standard Jacobi iteration with infinity norm
*/
int IterativeSolver::jacobi(matrix &m, int iterations, map<int, double> & convergence, Norm & norm, double epsilon)
{
	matrix matrices[2];
	matrices[0] = m;
	matrices[1] = m;
	double error = 0.0;
	double value = 0.0;
	int it;
	matrix r(m.getNumberOfRows(), m.getNumberOfColumns());

	for(it = 0; it < iterations; it++)
	{
		for(int i = 1; i < m.getNumberOfRows() - 1; i++)
		{
			for(int j = 1; j < m.getNumberOfColumns() - 1; j++)
			{
				value = 0.25 * (matrices[it%2](i-1,j) + matrices[it%2](i+1,j) + matrices[it%2](i,j-1) + matrices[it%2](i,j+1));
				r.setValue(i, j, fabs(value - matrices[it%2](i, j)));
				matrices[(it+1)%2].setValue(i, j, value);
			}
		}

		error = norm.calculateNorm(r);  

		if(!(it % 10)) convergence.insert(pair<int, double>(it ,error));

		if(error < epsilon)
		{
			m = matrices[(it+1)%2];
			return it;
		}


	}
	m = matrices[it%2];

	return it;
}
/**
red black ordering Jacobi iteration with infinity norm
*/
int IterativeSolver::jacobiRedBlack(matrix &m, int iterations, map<int, double> & convergence, Norm & norm, double epsilon)
{
	matrix matrices[2];
	matrices[0] = m;
	matrices[1] = m;
	double error = 0.0;
	double maxError = 0;
	double value = 0.0;
	int it;
	int color;
	matrix r(m.getNumberOfRows(), m.getNumberOfColumns());


	for(it = 0; it < iterations; it++)
	{
		maxError = 0.0;

		//color = red
		color = 0;
		for(int i = 1; i < m.getNumberOfRows() - 1; i++)
		{
			for(int j = 1 + (i+color)%2; j < m.getNumberOfColumns() - 1; j+=2)
			{
				/*value = 0.25 * (matrices[it%2](i-1,j) + matrices[it%2](i+1,j) + matrices[it%2](i,j-1) + matrices[it%2](i,j+1));
				matrices[(it+1)%2].setValue(i, j, value);*/
				value = 0.25 * (m(i-1,j) + m(i+1,j) + m(i,j-1) + m(i,j+1));
				r.setValue(i, j, fabs(value - m(i, j)));
				m.setValue(i, j, value);
			}
		}
		error = norm.calculateNorm(r); 
		if(error > maxError) maxError = error;

		//color = black
		color = 1;
		for(int i = 1; i < m.getNumberOfRows() - 1; i++)
		{
			for(int j = 1 + (i+color)%2; j < m.getNumberOfColumns() - 1; j+=2)
			{
				/*value = 0.25 * (matrices[(it+1)%2](i-1,j) + matrices[(it+1)%2](i+1,j) + matrices[(it+1)%2](i,j-1) + matrices[(it+1)%2](i,j+1));
				matrices[(it+1)%2].setValue(i, j, value);*/
				value = 0.25 * (m(i-1,j) + m(i+1,j) + m(i,j-1) + m(i,j+1));
				r.setValue(i, j, fabs(value - m(i, j)));
				m.setValue(i, j, value);
			}
		}


		error = norm.calculateNorm(r); 
		if(error > maxError) maxError = error;



		if(!(it % 10)) convergence.insert(pair<int, double>(it ,maxError));

		if(maxError < epsilon)
		{
			//m = matrices[(it+1)%2];
			return it;
		}	
	}
	//m = matrices[it%2];

	return it;
}

double IterativeSolver::jacobiRedBlackForParallel(matrix &m, Norm & norm)
{
	double error = 0.0;
	double maxError = 0.0;
	double value = 0.0;
	int color;
	matrix r(m.getNumberOfRows(), m.getNumberOfColumns());

	//color = red
	color = 0;
	for(int i = 1; i < m.getNumberOfRows() - 1; i++)
	{
		for(int j = 1 + (i+color)%2; j < m.getNumberOfColumns() - 1; j+=2)
		{
			value = 0.25 * (m(i-1,j) + m(i+1,j) + m(i,j-1) + m(i,j+1));
			r.setValue(i, j, fabs(value - m(i, j)));
			m.setValue(i, j, value);
		}
	}
	error = norm.calculateNorm(r); 
	if(error > maxError) maxError = error;

	//color = black
	color = 1;
	for(int i = 1; i < m.getNumberOfRows() - 1; i++)
	{
		for(int j = 1 + (i+color)%2; j < m.getNumberOfColumns() - 1; j+=2)
		{
			value = 0.25 * (m(i-1,j) + m(i+1,j) + m(i,j-1) + m(i,j+1));
			r.setValue(i, j, fabs(value - m(i, j)));
			m.setValue(i, j, value);
		}
	}

	error = norm.calculateNorm(r); 
	if(error > maxError) maxError = error;

	return maxError;
}

void IterativeSolver::initMatrix(matrix &m)
{
	double y = 0.0;
	double y_step = 1.0 / (m.getNumberOfRows() - 1);

	for(int i = 0 ; i < m.getNumberOfRows(); i++)
	{
		m.setValue(i, 0, pow(sin(M_PI * y), 2));	
		y += y_step;
	}

	for(int i = 0 ; i < m.getNumberOfRows(); i++)
	{
		for(int j = 1; j < m.getNumberOfColumns(); j++)
		{
			m.setValue(i, j, 0.0);
		}
	}
}

void IterativeSolver::initMatrixForParallel(matrix &m, int rank, int size)
{
	double y_step = 1.0 / (m.getNumberOfColumns() - 1);
	double chunkSize = m.getNumberOfColumns() / size;
	double y = rank * chunkSize * y_step;

	if(rank > 0) y -= y_step;

	for(int i = 0 ; i < m.getNumberOfRows(); i++)
	{
		m.setValue(i, 0, pow(sin(M_PI * y), 2));	
		y += y_step;
	}

	for(int i = 0 ; i < m.getNumberOfRows(); i++)
	{
		for(int j = 1; j < m.getNumberOfColumns(); j++)
		{
			m.setValue(i, j, 0.0);
		}
	}
}