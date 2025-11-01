#include "../include/matrix.hpp"
#include "../include/square-matrix.hpp"
#include <iostream>
#include <vector>

int main() {
    Matrix a{{{1, 2, 3}, {4, 5, 6}}};
    Matrix b{{{-1, 0, 1}, {2, 3, 4}}};
    Square_Matrix s{{{4, -6, 0}, {-6, 0, 1}, {0, 9, -1}}};

    std::cout << "A:\n" << a;
    std::cout << "B:\n" << b;
    std::cout << "S:\n" << s;

    std::cout << "A + B:\n" << (a + b);
    std::cout << "A - B:\n" << (a - b);
    std::cout << "A * B^T:\n" << (a * b.transpose());

    std::cout << "det(S): " << s.determinant() << '\n';
    std::cout << "rank(S): " << s.rank() << '\n';

    try {
        std::cout << "S inverse:\n" << s.inverse();
    } catch (const std::exception &ex) {
        std::cout << "Inverse failed: " << ex.what() << '\n';
    }

    return 0;
}
