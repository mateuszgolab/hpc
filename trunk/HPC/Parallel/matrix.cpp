#include "matrix.h"
#include <math.h>
#include <time.h>
#include<iostream>

using namespace std;

matrix::matrix() : x_size(0), y_size(0), data(NULL) {};

matrix::matrix(int x_s, int y_s) : x_size(x_s), y_size(y_s)
{
	data = new double*[x_size];
	for(int i = 0; i < x_size; i++)
	{
		data[i] = new double[y_size];
	}

	for(int i = 0; i < x_size; i++)
	{
		for(int j = 0; j < y_size; j++)
		{
			data[i][j] = 0.0;
		}
	}

}

matrix::matrix(double **d, int x_s, int y_s) : x_size(x_s), y_size(y_s)
{
	data = new double*[x_size];
	for(int i = 0; i < x_size; i++)
	{
		data[i] = new double[y_size];
	}

	for(int i = 0; i < x_size; i++)
	{
		for(int j = 0; j < y_size; j++)
		{
			data[i][j] = d[i][j];
		}
	}
}

matrix::~matrix()
{
	if(data != NULL)
	{
		for(int i = 0; i < x_size; i++)
		{
			if(data[i] != NULL)
			{
				delete [] data[i];
				data[i] = NULL;
			}
		}

		delete [] data;
		data = NULL;
	}
}

matrix& matrix::operator=(matrix &m)
{
	if(this == &m) return *this;

	if(x_size == m.getXsize() && y_size == m.getYsize())
	{
		for(int i = 0; i < x_size; i++)
		{
			for(int j = 0; j < y_size; j++)
			{
				data[i][j] = m(i, j);
			}
		}

		return *this;
	}

	if(data != NULL)
	{
		for(int i = 0; i < x_size; i++)
		{
			if(data[i] != NULL)
			{
				delete [] data[i];
				data[i] = NULL;
			}
		}

		delete [] data;
		data = NULL;
	}

	x_size = m.getXsize();
	y_size = m.getYsize();

	data = new double*[x_size];
	for(int i = 0; i < x_size; i++)
	{
		data[i] = new double[y_size];
	}

	for(int i = 0; i < x_size; i++)
	{
		for(int i = 0; i < x_size; i++)
		{
			for(int j = 0; j < y_size; j++)
			{
				data[i][j] = m(i, j);
			}
		}
	}

	return *this;
}

int matrix::getXsize()
{
	return x_size;
}

int matrix::getYsize()
{
	return y_size;
}

double** matrix::getMatrix()
{
	return data;
}

void matrix::setValue(int x, int y, double v)
{
	data[x][y] = v;
}

double matrix::operator()(int x, int y)
{
	return data[x][y];
}

void matrix::graphPrint()
{
	puts("Y    |");
	//puts("1.00 |");
	for(int i = 0 ; i < x_size; i++)
	{
		printf("%.2f |",(double)i/(x_size - 1));
		for(int j = 0; j < y_size; j++)
		{
			printf("%f ", data[j][i]);
		}
		puts("");
	}
	puts("      ------------------------------------------------------------------->");
	puts("									X");
}

void matrix::print()
{
	for(int i = y_size -1  ; i >= 0; i--)
	{
		
		for(int j = 0; j < x_size; j++)
		{
			printf("%f ", data[i][j]);
		}
		puts("");
	}
}

void matrix::printForChart()
{
	for(int i = 0  ; i < x_size; i++)
	{
		
		for(int j = 0; j < y_size; j++)
		{
			printf("%f ", data[j][i]);
		}
		puts("");
	}
}

double matrix::validate(matrix & m1, matrix & m2)
{
	if((m1.getXsize() != m2.getXsize()) || (m1.getYsize() != m2.getYsize())) return false;

	srand(unsigned int(time(0)));
	double accuracy = 0.0;

	for(int i = 0; i < m1.getXsize(); i++)
	{
		int x = rand() % m1.getXsize();
		int y = rand() % m2.getYsize();
		
		if(abs(m1(x,y) - m2(x,y)) > accuracy) accuracy = abs(m1(x,y) - m2(x,y));
	}

	return accuracy;
}