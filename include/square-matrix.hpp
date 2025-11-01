#pragma once

#include "./matrix.hpp"
#include <vector>

class Square_Matrix : public Matrix {
  public:
    Square_Matrix();
    Square_Matrix(std::vector<std::vector<double>> m);
    Square_Matrix(const Matrix &right);

    double determinant() const;

    double cofactor(int row, int col) const;

    Square_Matrix minor(size_t row, size_t col) const;
    Square_Matrix adjoint() const;
    Square_Matrix inverse() const;

    int rank();
};
