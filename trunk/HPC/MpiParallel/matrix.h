#pragma once
#include<vector>

class matrix
{
	double **data;
	int rows;
	int columns;
	std::vector<double*> overridenRows;


public:
	matrix();
	matrix(int r, int c);
	matrix(double **data, int r, int c);
	~matrix();
	matrix& operator=(matrix &m);
	int getNumberOfRows();
	int getNumberOfColumns();
	double** getMatrix();
	double* getFirstRow();
    double* getSecondRow();
	double* getPenultimateRow();
	double* & getLastRow();
	void setFirstRow(double* row);
	void setLastRow(double* row);
	void setValue(int x, int y, double v);
	double operator()(int x, int y);
	void print();
	void graphPrint();



};

