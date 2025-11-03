#include "../include/triangular-matrix.hpp"
#include <stdexcept>
#include <vector>

bool is_upper_triangular(const std::vector<std::vector<double>> &v) {

    const int N = v.size();
    for (int i = 1; i < N; ++i)
        for (int j = 0; j < i; ++j)
            if (v[i][j] != 0.0) {
                return false;
            }
    return true;
}

bool is_lower_triangular(const std::vector<std::vector<double>> &v) {
    int n = v.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (v[i][j] != 0.0) {
                return false;
            }
    return true;
}

bool is_triangular(std::vector<std::vector<double>> v) {
    return is_lower_triangular(v) or is_upper_triangular(v);
}

Triangular_Matrix::Triangular_Matrix() : Square_Matrix() {}

Triangular_Matrix::Triangular_Matrix(std::vector<std::vector<double>> v)
    : Square_Matrix(v) {

    if (!is_triangular(v)) {
        throw std::invalid_argument(
            "class Triangular_Matrix: constructor: Input vector v is not a "
            "valid triangular matrix");
    }
}

Triangular_Matrix::Triangular_Matrix(const Matrix &right)
    : Square_Matrix(right) {
    if (!is_triangular(right.get_data())) {
        throw std::invalid_argument("class Triangular_Matrix: copy "
                                    "constructor: Input matrix right is not a "
                                    "valid triangular matrix");
    }
}

bool Triangular_Matrix::is_upper_triangular() {

    return ::is_upper_triangular(v);
}

double Triangular_Matrix::determinant() const {
    double product = 1.0;
    for (size_t i = 0; i < get_num_row(); i++) {
        product *= v[i][i];
    }

    return product;
}
