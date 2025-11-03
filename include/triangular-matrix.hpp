#pragma once

#include "./square-matrix.hpp"
#include <vector>

class Triangular_Matrix : public Square_Matrix {
  public:
    Triangular_Matrix();
    Triangular_Matrix(std::vector<std::vector<double>>);
    Triangular_Matrix(const Matrix &right);

    bool is_upper_triangular();

    double determinant() const;
};
