#include "../include/vector.hpp"
#include <stdexcept>
#include <vector>

Vector::Vector() {}

Vector::Vector(std::vector<std::vector<double>> v) : Matrix(v) {

    if (v[0].size() > 1) {
        throw std::invalid_argument("class Vector: constructor: Input vector "
                                    "is not a valid n by 1 vector");
    }
}

Vector::Vector(const Matrix &right) : Matrix(right) {
    if (v[0].size() > 1) {
        throw std::invalid_argument("class Vector: copy constructor: Input "
                                    "matrix's is not a valid vector");
    }
}

Vector Vector::get_zero_vector(size_t n) { return get_zero_matrix(n, 1); }

double Vector::get_element(size_t index) const {

    if (index >= get_num_row()) {
        throw std::invalid_argument(
            "class Vector: method get_element's input index is too large");
    }

    return get_data()[index][0];
}

size_t Vector::get_num_element() const { return get_num_row(); }

double Vector::dot_product(Vector other) const {

    return ((*this) * other.transpose()).get_data()[0][0];
}
