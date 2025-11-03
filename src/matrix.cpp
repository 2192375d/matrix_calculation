#include "../include/matrix.hpp"
#include "../include/helpers.hpp"
#include "../include/square-matrix.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

/*
 * Outputs the matrix, leaves 2 spaces between each
 * value in the same row.
 */
std::ostream &operator<<(std::ostream &out, const Matrix &m) {
    int largestNumDigit = get_largest_digit(m.v);

    // Loop through each index
    for (size_t i = 0; i < m.v.size(); i++) {

        // Print the values
        for (size_t j = 0; j < m.v[i].size(); j++) {

            // Print the value
            out << m.v[i][j];

            // Leave 2 extra spaces
            out << "  ";

            // Leave space based on the largest digit in the matrix
            for (int k = 0; k < largestNumDigit - get_num_digit(m.v[i][j]);
                 k++) {
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

Matrix Matrix::get_zero_matrix(size_t num_row, size_t num_col) {

    std::vector<std::vector<double>> v(num_row,
                                       std::vector<double>(num_col, 0.0));

    return Matrix(v);
}

Matrix Matrix::get_identity(size_t num_row, size_t num_col) {
    std::vector<std::vector<double>> I;
    I.assign(num_row, std::vector<double>(num_col, 0.0));
    const size_t N = std::min(num_row, num_col);
    for (std::size_t i = 0; i < N; i++) {
        I[i][i] = 1.0;
    }
    return Matrix(I);
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

std::vector<double> Matrix::get_row(size_t row_num) const {
    if (row_num >= get_num_row()) {
        throw std::invalid_argument(
            "class Matrix: get_row: input row_num larger than the number of "
            "rows in the matrix");
    }

    std::vector<double> row;
    for (size_t j = 0; j < get_num_col(); j++) {
        row.push_back(v[row_num][j]);
    }

    return row;
}

std::vector<double> Matrix::get_col(size_t col_num) const {
    if (col_num >= get_num_col()) {
        throw std::invalid_argument(
            "class Matrix: get_col: input col_num larger than the number of "
            "columns in the matrix");
    }

    std::vector<double> col;
    for (size_t j = 0; j < get_num_row(); j++) {
        col.push_back(v[j][col_num]);
    }

    return col;
}

void Matrix::set_row(size_t row_num, const std::vector<double> &row) {

    if (row_num >= get_num_row()) {
        throw std::invalid_argument(
            "class Matrix: set_row: input row_num larger than the number of "
            "rows in the matrix");
    }

    if (row.size() != get_num_col()) {
        throw std::invalid_argument(
            "class Matrix: set_row: input row's size does not match");
    }

    v[row_num] = row;
}

void Matrix::set_col(size_t col_num, const std::vector<double> &col) {

    if (col_num >= get_num_col()) {
        throw std::invalid_argument(
            "class Matrix: set_col: input row_num larger than the number of "
            "columns in the matrix");
    }

    if (col.size() != get_num_row()) {
        throw std::invalid_argument(
            "class Matrix: set_col: input column's size does not match");
    }

    for (size_t i = 0; i < get_num_row(); i++) {
        v[i][col_num] = col[i];
    }
}

void Matrix::set_entry(size_t i, size_t j, double val) {

    if (i >= get_num_row()) {
        throw std::invalid_argument(
            "class Matrix: set_entry: input i larger than the number of "
            "rows in the matrix");
    }

    if (j >= get_num_col()) {
        throw std::invalid_argument(
            "class Matrix: set_entry: input j larger than the number of "
            "columns in the matrix");
    }

    v[i][j] = val;
}

void Matrix::row_operation_add(size_t source_row, size_t to_add_row,
                               double scalar) {
    if (source_row >= get_num_row()) {
        throw std::invalid_argument("class Matrix: row_operation_add: input "
                                    "source_row larger than the number of "
                                    "rows in the matrix");
    }

    if (to_add_row >= get_num_row()) {
        throw std::invalid_argument("class Matrix: row_operation_add: input "
                                    "to_add_row larger than the number of "
                                    "rows in the matrix");
    }

    for (size_t j = 0; j < get_num_col(); j++) {
        v[source_row][j] += scalar * v[to_add_row][j];
    }
}

void Matrix::row_operation_multiply(size_t source_row, double scalar) {
    if (source_row >= get_num_row()) {
        throw std::invalid_argument(
            "class Matrix: row_operation_multiply: input "
            "source_row larger than the number of "
            "rows in the matrix");
    }

    if (scalar == 0) {
        throw std ::invalid_argument(
            "class Matrix: row_operation_multiply: input scalar is zero");
    }

    for (size_t j = 0; j < get_num_col(); j++) {
        v[source_row][j] *= scalar;
    }
}

void Matrix::row_operation_swap(size_t row1, size_t row2) {

    if (row1 >= v.size()) {
        throw std::invalid_argument("class Matrix: row_operation_swap: input "
                                    "row1 larger than the number of "
                                    "rows in the matrix");
    }

    if (row2 >= v.size()) {
        throw std::invalid_argument("class Matrix: row_operation_swap: input "
                                    "row2 larger than the number of "
                                    "rows in the matrix");
    }

    std::swap(v[row1], v[row2]);
}

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

std::tuple<Matrix, Matrix, Matrix> Matrix::LU_factorization() const {
    const int N = get_num_row();
    const int M = get_num_col();
    Square_Matrix P = Square_Matrix::get_identity(N);
    Matrix L = get_identity(N, std::min(N, M));
    Matrix U = get_data();

    for (size_t j = 0; j < std::min(N, M); j++) {
        size_t pivot_index = get_largest_index(get_abs(get_col(j)), j);

        if (pivot_index != j) {
            P.row_operation_swap(pivot_index, j);
            U.row_operation_swap(pivot_index, j);
        }

        if (U.get_data()[j][j] == 0) {
            continue;
        }

        for (size_t i = j + 1; i < N; i++) {
            double multiplier = U.get_data()[i][j] / U.get_data()[j][j];
            L.set_entry(i, j, multiplier);

            U.row_operation_add(i, j, -multiplier);
        }
    }

    std::tuple<Matrix, Matrix, Matrix> plu = std::make_tuple(P, L, U);
    return plu;
}
