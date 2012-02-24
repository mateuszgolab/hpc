#pragma once
#include<vector>

class matrix
{
	double **data;
	int x_size;
	int y_size;
	std::vector<double*> overridenRows;


public:
	matrix();
	matrix(int x_s, int y_s);
	matrix(double **data, int x_s, int y_s);
	~matrix();
	matrix& operator=(matrix &m);
	int getXsize();
	int getYsize();
	double** getMatrix();
	double* getFirstRow(int i);
	void setFirstRow(double* row);
	void setLastRow(double* row);
	void setValue(int x, int y, double v);
	double operator()(int x, int y);
	void print();
	void graphPrint();
	void printForChart();


};

