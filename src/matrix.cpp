#include "../include/matrix.hpp"
#include "../include/helpers.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

int getLargestDigit(std::vector<std::vector<double>> v);
int getNumDigit(double n);

/*
 * Outputs the matrix, leaves 2 spaces between each
 * value in the same row.
 */
std::ostream &operator<<(std::ostream &out, const Matrix &m) {
    int largestNumDigit = getLargestDigit(m.v);

    // Loop through each index
    for (size_t i = 0; i < m.v.size(); i++) {

        // Print the values
        for (size_t j = 0; j < m.v[i].size(); j++) {

            // Print the value
            out << m.v[i][j];

            // Leave 2 extra spaces
            out << "  ";

            // Leave space based on the largest digit in the matrix
            for (int k = 0; k < largestNumDigit - getNumDigit(m.v[i][j]); k++) {
                out << " ";
            }
        }
        out << std::endl;
    }
    return out;
}

/*
 * The function first prompts for the number of row
 * and column. Then prompts for the value at each.
 *
 * Upon prompting each value, the function will print
 * the matrix with all the prompted values. The empty
 * ones will be printed with a zero(0)
 */
std::istream &operator>>(std::istream &in, Matrix &m) {
    m.v.clear();

    // Read dimensions
    std::size_t rows = 0, cols = 0;
    if (&in == &std::cin) {
        std::cout << "rows cols: ";
    }
    if (!(in >> rows >> cols)) {
        return in;
    }

    m.v.assign(rows, std::vector<double>(cols));

    // Read entries row by row
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            if (&in == &std::cin) {
                std::cout << "A[" << r + 1 << "," << c + 1 << "]: ";
            }
            if (!(in >> m.v[r][c])) {
                return in;
            }
        }
    }

    if (&in == &std::cin) {
        std::cout << '\n' << m << '\n';
    }

    return in;
}

size_t Matrix::get_num_row() const {
    if (v.empty()) {
        return 0;
    }

    return v.size();
}

size_t Matrix::get_num_col() const {
    if (v.empty()) {
        return 0;
    }

    return v[0].size();
}

std::vector<std::vector<double>> Matrix::get_data() const { return v; }

// default constructor
Matrix::Matrix() { v.resize(0); }

// constructor
Matrix::Matrix(std::vector<std::vector<double>> v) {
    if (!v.empty()) {
        int expected_size = v[0].size();
        for (size_t i = 0; i < v.size(); i++) {
            if (v[i].size() == 0 or v[i].size() != expected_size) {
                throw std::invalid_argument("class Matrix: constructor: input "
                                            "matrix is not an n by m vector");
            }
        }
    }

    this->v = v;
}

// copy constructor
Matrix::Matrix(const Matrix &right) { v = right.v; }

/*
 * The method will return a matrix which is the
 * sum of the two given matrices.
 *
 * If the two given matrices have different sizes,
 * the method will leave a message indicating the
 * input is invalid and returns a 1 by 1 matrix with
 * NULL as it's only value.
 *
 * If the two given matrices have the same size,
 * the method will return the sum of them.
 */
Matrix Matrix::operator+(const Matrix &right) const {

    if (v.size() != right.v.size() or v[0].size() != right.v[0].size()) {
        throw std::invalid_argument(
            "class Matrix: operator+: Input matrix dimension does not match");
    }

    Matrix sum;

    // Get the sum of the matrices
    for (size_t i = 0; i < v.size(); i++) {
        std::vector<double> row;

        // Get the sum of each row
        for (size_t j = 0; j < v[i].size(); j++) {
            row.push_back(v[i][j] + right.v[i][j]);
        }

        sum.v.push_back(row);
    }

    return sum;
}

/*
 * The method will return a matrix which is the
 * difference of the two given matrices.
 *
 * If the two given matrices have different sizes,
 * the method will leave a message indicating the
 * input is invalid and returns a 1 by 1 matrix with
 * NULL as it's only value.
 *
 * If the two given matrices have the same size,
 * the method will return the difference of them.
 */
Matrix Matrix::operator-(const Matrix &right) const {

    if (v.size() != right.v.size() or v[0].size() != right.v[0].size()) {
        throw std::invalid_argument(
            "class Matrix: operator-: Input matrix dimension does not match");
    }

    Matrix difference;

    // Get the sum of the matrices
    for (size_t i = 0; i < v.size(); i++) {
        std::vector<double> row;

        // Get the sum of each row
        for (size_t j = 0; j < v[i].size(); j++) {
            row.push_back(v[i][j] - right.v[i][j]);
        }

        difference.v.push_back(row);
    }

    return difference;
}

/*
 * The method will return a matrix which is the
 * product of the two given matrices.
 *
 * If the two given matrices do not satisfy the
 * criteria for a matrix multiplication (for
 * A x B, A's number of row != B's number of
 * column), the method will leave a message
 * indicating the input is invalid and return
 * a 1 by 1 matrix with NULL as it's only value.
 *
 * If the condition is satisfied, the method will
 * return their product as desired.
 */
Matrix Matrix::operator*(const Matrix &right) const {

    if (v[0].size() != right.v.size()) {
        throw std::invalid_argument(
            "class Matrix: operator*: Input matrix dimension does not match");
    }

    Matrix product;

    // For the following code, assume A and B are matrices, while A x B =
    // product

    /*
     * For the following nested for loop:
     * A's index is i, k (row, col)
     * B's index is k, j (row, col)
     */

    // Access every row in A
    for (size_t i = 0; i < v.size(); i++) {

        std::vector<double> row;

        // Access every column in B
        for (size_t j = 0; j < right.v[0].size(); j++) {

            double sum = 0;

            // Access every column in A and every row in B
            for (int k = 0; k < v[0].size(); k++) {
                sum += v[i][k] * right.v[k][j];
            }

            row.push_back(sum);
        }

        product.v.push_back(row);
    }

    return product;
}

/*
 * If the two matrices have the same size and
 * each value in each indices are the same, the
 * method will return true
 */
bool Matrix::operator==(const Matrix &right) const {

    if (right.v == v) {
        return true;
    }

    return false;
}

Matrix operator*(const double &left, const Matrix &right) {
    Matrix m;

    for (size_t i = 0; i < right.v.size(); i++) {
        std::vector<double> row;

        for (size_t j = 0; j < right.v[0].size(); j++) {
            row.push_back(left * right.v[i][j]);
        }

        m.v.push_back(row);
    }

    return m;
}

/*
 * The method returns the transpose of the original
 * matrix.
 */
Matrix Matrix::transpose() {
    Matrix m;

    // Access the column
    for (size_t i = 0; i < v[0].size(); i++) {
        std::vector<double> row;

        // Access the row
        for (size_t j = 0; j < v.size(); j++) {
            row.push_back(v[j][i]);
        }

        m.v.push_back(row);
    }

    return m;
}
