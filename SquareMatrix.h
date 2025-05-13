#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"

class SquareMatrix :public Matrix{
public:
	double determinant();

	SquareMatrix();

	SquareMatrix(const Matrix& right);
	
	double cofactor(int row, int col);

	SquareMatrix minor(int row, int col);
	SquareMatrix adjoint();
	SquareMatrix inverse();
	int rank();
};

#endif