#include "../include/triangular-matrix.hpp"
#include "../include/vector.hpp"
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

// expects a nonsingular lower triangular matrix, otherwise throw exception
Vector Triangular_Matrix::forward_substitution(Vector b) const {

    if (!::is_lower_triangular(v)) {
        throw std::invalid_argument(
            "class Triangular_Matrix: method forward_substitution: Current "
            "matrix is not a lower triangular matrix");
    }

    if (b.get_num_element() != get_num_row()) {
        throw std::invalid_argument(
            "class Triangular_Matrix: method forward_substitution: input "
            "Vector b's size does not match");
    }

    int n = get_num_row();

    Vector result = Vector::get_zero_vector(n);

    for (size_t i = 0; i < n; i++) {

        if (get_data()[i][i] == 0.0) {
            throw std::invalid_argument(
                "class Triangular_Matrix: method forward_substitution: Current "
                "matrix is singular");
        }

        double val = b.get_element(i);

        for (size_t j = 0; j < i; j++) {
            val -= get_data()[i][j] * result.get_element(j);
        }

        val /= get_data()[i][i];

        result.set_entry(i, 0, val);
    }

    return result;
}

// expects a nonsingular upper triangular matrix, otherwise throw exception
Vector Triangular_Matrix::backward_substitution(Vector b) const {

    if (!::is_upper_triangular(v)) {
        throw std::invalid_argument(
            "class Triangular_Matrix: method backward_substitution: Current "
            "matrix is not a lower triangular matrix");
    }

    if (b.get_num_element() != get_num_row()) {
        throw std::invalid_argument(
            "class Triangular_Matrix: method backward_substitution: input "
            "Vector b's size does not match");
    }

    int n = get_num_row();

    Vector result = Vector::get_zero_vector(n);

    for (size_t i = n - 1; i >= 0; i--) {

        if (get_data()[i][i] == 0.0) {
            throw std::invalid_argument("class Triangular_Matrix: method "
                                        "backward_substitution: Current "
                                        "matrix is singular");
        }

        double val = b.get_element(i);

        for (size_t j = n - 1; j >= i + 1; j--) {
            val -= get_data()[i][j] * result.get_element(j);
        }

        val /= get_data()[i][i];

        result.set_entry(i, 0, val);
    }

    return result;
}
