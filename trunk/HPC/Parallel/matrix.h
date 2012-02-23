#pragma once
class matrix
{
	double **data;
	int x_size;
	int y_size;

public:
	matrix();
	matrix(int x_s, int y_s);
	matrix(double **data, int x_s, int y_s);
	~matrix();
	int getXsize();
	int getYsize();
	double** getMatrix();
	void setValue(int x, int y, double v);
	double operator()(int x, int y);
	matrix& operator=(matrix &m);
	void print();
	void graphPrint();
	void printForChart();
	double static validate(matrix &m1, matrix &m2);

};

