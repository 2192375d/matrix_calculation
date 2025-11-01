#pragma once

#include "./matrix.hpp"
#include <utility>
#include <vector>

class Square_Matrix : public Matrix {
  public:
    Square_Matrix();
    Square_Matrix(std::vector<std::vector<double>> v);
    Square_Matrix(const Matrix &right);

    static Square_Matrix get_identity(size_t n);
    static Square_Matrix get_permutation_matrix(size_t n, size_t row1,
                                                size_t row2);
    static Square_Matrix
    get_permutation_matrix(size_t n,
                           std::vector<std::pair<size_t, size_t>> instructions);

    double determinant() const;

    double cofactor(int row, int col) const;

    Square_Matrix minor(size_t row, size_t col) const;
    Square_Matrix adjoint() const;
    Square_Matrix inverse() const;

    int rank();
};
