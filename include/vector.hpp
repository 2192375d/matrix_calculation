#include "./matrix.hpp"
#include <vector>

class Vector : Matrix {
  public:
    Vector();
    Vector(std::vector<std::vector<double>> v);

    double dot_product(Vector other);
};
