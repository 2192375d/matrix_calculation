#include <iostream>
#include <vector>
#include "Matrix.h"
#include "SquareMatrix.h"
using namespace std;

//int menu();


int main() {
	SquareMatrix A1;
	A1.v =
	{
		{4, -6, 0, 0},
		{-6, 0, 1, 0},
		{0, 9, -1, 0},
		{0, 1, 4, 0}
	};

	Matrix A2;
	A2.v =
	{
		{-1, 5},
		{1, 2},
		{-2, 3}
	};

	Matrix A3;

	A3.v =
	{
		{1},
		{2}
	};

	cout << A1.rank();
}
