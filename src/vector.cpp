#include "../include/vector.hpp"
#include <stdexcept>
#include <vector>

Vector::Vector() {}

Vector::Vector(std::vector<std::vector<double>> v) {

    if (v[0].size() > 1) {
        throw std::invalid_argument("class Vector: constructor: input vector "
                                    "is not a valid n by 1 vector");
    }
    this->v = v;
}

double Vector::dot_product(Vector other) {

    return ((*this) * other.transpose()).get_data()[0][0];
}
