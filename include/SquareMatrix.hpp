#pragma once

#include "Matrix.hpp"

class SquareMatrix : public Matrix {
  public:
    double determinant() const;

    SquareMatrix();

    SquareMatrix(const Matrix &right);

    double cofactor(int row, int col) const;

    SquareMatrix minor(int row, int col) const;
    SquareMatrix adjoint() const;
    SquareMatrix inverse() const;
    int rank();
};
