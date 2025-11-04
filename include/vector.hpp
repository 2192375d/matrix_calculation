#pragma once

#include "./matrix.hpp"
#include <vector>

class Vector : public Matrix {
  public:
    Vector();
    Vector(std::vector<std::vector<double>> v);
    Vector(const Matrix &right);

    static Vector get_zero_vector(size_t n);

    double get_element(size_t index) const;
    size_t get_num_element() const;

    double dot_product(Vector other) const;
};
