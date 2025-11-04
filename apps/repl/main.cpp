#include "../../include/helpers.hpp"
#include "../../include/matrix.hpp"
#include "../../include/square-matrix.hpp"
#include "../../include/triangular-matrix.hpp"

#include <cmath>
#include <exception>
#include <iostream>

namespace {
bool approx_equal(double a, double b, double eps = 1e-9) {
    return std::fabs(a - b) <= eps * max(1.0, max(std::fabs(a), std::fabs(b)));
}
} // namespace

int main() {
    try {
        // Test 1: general 3×3 matrix
        Square_Matrix A({{2.0, 1.0, 3.0}, {0.0, -1.0, 4.0}, {5.0, 2.0, 0.0}});

        double det_cofactor = A.determinant_cofactor_expansion();
        double det_lu = A.determinant_LU();

        std::cout << "A:\n" << A;
        std::cout << "det (cofactor) = " << det_cofactor << '\n';
        std::cout << "det (LU)       = " << det_lu << '\n';

        if (!approx_equal(det_cofactor, det_lu)) {
            std::cerr << "Mismatch between cofactor and LU determinants!\n";
            return 1;
        }

        // Test 2: upper-triangular matrix
        Triangular_Matrix U(
            {{3.0, 2.0, -1.0}, {0.0, 5.0, 4.0}, {0.0, 0.0, -2.0}});

        std::cout << "\nU:\n" << U;
        std::cout << "det(U) = " << U.determinant() << '\n';
        if (!approx_equal(U.determinant(), 3.0 * 5.0 * -2.0)) {
            std::cerr << "Triangular determinant check failed!\n";
            return 1;
        }

        // Test 3: invalid triangular input (should throw)
        try {
            Triangular_Matrix bad({{1.0, 2.0}, {3.0, 4.0}});
            std::cerr << "ERROR: bad triangular matrix was accepted\n";
            return 1;
        } catch (const std::invalid_argument &) {
            std::cout << "\nInvalid triangular matrix correctly rejected.\n";
        }

        std::cout << "\nAll quick checks passed.\n";
        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "Unhandled exception: " << ex.what() << '\n';
        return 1;
    }
}
