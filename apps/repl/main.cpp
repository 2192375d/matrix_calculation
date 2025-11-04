#include "helpers.hpp"
#include "matrix.hpp"
#include "square-matrix.hpp"
#include "triangular-matrix.hpp"

#include <replxx.hxx>
#include <tabulate/table.hpp>

#include <cmath>
#include <exception>
#include <iostream>
#include <string>

constexpr auto DARK_BLUE = "\033[34m";
constexpr auto LIGHT_BLUE = "\033[94m";
constexpr auto ORANGE = "\033[38;5;208m";

// constexpr auto RESET = "\033[0m";
constexpr auto RESET = DARK_BLUE;

void print(std::string message = "", std::string colour_string = RESET,
           bool skip_line = true) {
    std::cout << colour_string << message << RESET;
    std::cout << (skip_line ? "\n" : "");
}

int main() {
    replxx::Replxx rx;

    while (true) {
        rx.clear_screen();
        print("_______________MATRIX CALCULATOR_______________");

        const char *input = rx.input(">>> ");
        if (!input)
            break;

        std::string line(input);
        if (line == "exit" or line == "quit") {
            break;
        }

        rx.history_add(line);
        std::cout << "You typed: " << line << std::endl;
    }
}

// namespace {
// bool approx_equal(double a, double b, double eps = 1e-9) {
//     return std::fabs(a - b) <= eps * max(1.0, max(std::fabs(a),
//     std::fabs(b)));
// }
// } // namespace
//
// int main() {
//     try {
//         // Test 1: general 3×3 matrix
//         Square_Matrix A({{2.0, 1.0, 3.0}, {0.0, -1.0, 4.0}, {5.0, 2.0,
//         0.0}});
//
//         double det_cofactor = A.determinant_cofactor_expansion();
//         double det_lu = A.determinant_LU();
//
//         std::cout << "A:\n" << A;
//         std::cout << "det (cofactor) = " << det_cofactor << '\n';
//         std::cout << "det (LU)       = " << det_lu << '\n';
//
//         if (!approx_equal(det_cofactor, det_lu)) {
//             std::cerr << "Mismatch between cofactor and LU determinants!\n";
//             return 1;
//         }
//
//         // Test 2: upper-triangular matrix
//         Triangular_Matrix U(
//             {{3.0, 2.0, -1.0}, {0.0, 5.0, 4.0}, {0.0, 0.0, -2.0}});
//
//         std::cout << "\nU:\n" << U;
//         std::cout << "det(U) = " << U.determinant() << '\n';
//         if (!approx_equal(U.determinant(), 3.0 * 5.0 * -2.0)) {
//             std::cerr << "Triangular determinant check failed!\n";
//             return 1;
//         }
//
//         // Test 3: invalid triangular input (should throw)
//         try {
//             Triangular_Matrix bad({{1.0, 2.0}, {3.0, 4.0}});
//             std::cerr << "ERROR: bad triangular matrix was accepted\n";
//             return 1;
//         } catch (const std::invalid_argument &) {
//             std::cout << "\nInvalid triangular matrix correctly rejected.\n";
//         }
//
//         std::cout << "\nAll quick checks passed.\n";
//         return 0;
//     } catch (const std::exception &ex) {
//         std::cerr << "Unhandled exception: " << ex.what() << '\n';
//         return 1;
//     }
// }
