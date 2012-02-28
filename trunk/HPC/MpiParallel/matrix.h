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
	matrix(const matrix & m, int sizeX, int sizeY);
	matrix(const matrix & m);
	~matrix();
	matrix& operator=(matrix &m);
	int getNumberOfRows() const;
	int getNumberOfColumns() const;
	double** getMatrix();
	double* getRow(int i);
	double* getFirstRow();
    double* getSecondRow();
	double* getPenultimateRow();
	double* getLastRow();
	void setFirstRow(double* row);
	void setLastRow(double* row);
	void setValue(int x, int y, double v);
	double operator()(int x, int y) const;
	void print();
	void graphPrint();



};

