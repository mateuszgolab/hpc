#include "matrix.h"
#include <math.h>
#include <stdio.h>


matrix::matrix() : rows(0), columns(0), data(NULL) {};

matrix::matrix(int r, int c) : rows(r), columns(c)
{
	data = new double*[rows];
	for(int i = 0; i < rows; i++)
	{
		data[i] = new double[columns];
	}

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			data[i][j] = 0.0;
		}
	}

}



matrix::matrix(double **d, int r, int c) : rows(r), columns(c)
{
	data = new double*[rows];
	for(int i = 0; i < rows; i++)
	{
		data[i] = new double[columns];
	}

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			data[i][j] = d[i][j];
		}
	}
}

matrix::~matrix()
{
	if(data != NULL)
	{
		for(int i = 0; i < rows; i++)
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

	std::vector<double*>::iterator it;

	for(it = overridenRows.begin(); it != overridenRows.end(); it++)
	{
		double* val = (*it);
		if(val != NULL)
		{
			delete [] val;
			val = NULL;
		}
	}
}

matrix::matrix(const matrix &m, int sizeX, int sizeY)
{
	rows = sizeY;
	columns = sizeX;

	int rowSize = (rows < m.getNumberOfRows())?rows:m.getNumberOfRows();
	int columnSize = (columns < m.getNumberOfColumns())?columns:m.getNumberOfColumns();

	data = new double*[rows];
	for(int i = 0; i < rows; i++)
	{
		data[i] = new double[columns];
	}


	for(int i = 0; i < rowSize; i++)
	{
		for(int j = 0; j < columnSize; j++)
		{
			data[i][j] = m(j, i);
		}
	}
}

matrix::matrix(const matrix & m)
{
	rows = m.getNumberOfRows();
	columns = m.getNumberOfColumns();

	data = new double*[rows];
	for(int i = 0; i < rows; i++)
	{
		data[i] = new double[columns];
	}

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			data[i][j] = m(i, j);
		}
	}
}

matrix& matrix::operator=(matrix &m)
{
	if(this == &m) return *this;

	if(columns == m.getNumberOfColumns() && rows == m.getNumberOfRows())
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < columns; j++)
			{
				data[i][j] = m(i, j);
			}
		}

		return *this;
	}

	if(data != NULL)
	{
		for(int i = 0; i < rows; i++)
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

	rows = m.getNumberOfRows();
	columns = m.getNumberOfColumns();

	data = new double*[rows];
	for(int i = 0; i < rows; i++)
	{
		data[i] = new double[columns];
	}


	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			data[i][j] = m(i, j);
		}
	}


	return *this;
}

int matrix::getNumberOfColumns() const
{
	return columns;
}

int matrix::getNumberOfRows() const
{
	return rows;
}

double** matrix::getMatrix()
{
	return data;
}

double* matrix::getRow(int i)
{
	return data[i];
}

void matrix::setValue(int x, int y, double v)
{
	data[y][x] = v;
}

double matrix::operator()(int x, int y) const
{
	return data[y][x];
}

void matrix::graphPrint()
{
	puts("Y    |");
	//puts("1.00 |");
	for(int i = columns - 1 ; i >= 0; i--)
	{
		printf("%.2f |",(double)i/(rows - 1));
		for(int j = 0; j < rows; j++)
		{
			printf("%f ", data[i][j]);
		}
		puts("");
	}
	puts("      ------------------------------------------------------------------->");
	puts("									X");
}

void matrix::print()
{
	for(int i = 0 ; i < columns; i++)
	{
		
		for(int j = 0; j < rows; j++)
		{
			printf("%f ", data[i][j]);
		}
		puts("");
	}
}

double* matrix::getFirstRow()
{
	return data[0];
}

double* matrix::getSecondRow()
{
	return data[1];
}

double* matrix::getPenultimateRow()
{
	return data[rows - 2];
}

double* matrix::getLastRow()
{
	return data[rows - 1];
}

void matrix::setFirstRow(double* row)
{
	overridenRows.push_back(data[0]);
	data[0] = row;
}

void matrix::setLastRow(double* row)
{
	overridenRows.push_back(data[rows - 1]);
	data[rows - 1] = row;
}