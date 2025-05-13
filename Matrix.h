#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
using namespace std;

class Matrix{
public:
	vector<vector<double>> v;

	friend ostream& operator<<(ostream& out, const Matrix& m);
	friend istream& operator>>(istream& in, Matrix& m);

	//operators between matrices
	Matrix operator+(const Matrix& right);
	Matrix operator-(const Matrix& right);
	Matrix operator*(const Matrix& right);
	bool operator==(const Matrix& right);

	//scalar multiplication
	Matrix operator*(const double& right);
	friend Matrix operator*(const double& left, const Matrix& right);

	//Other methods
	Matrix transpose();
};
#endif