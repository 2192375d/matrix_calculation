#include "../include/square-matrix.hpp"
#include <stdexcept>
#include <vector>

double get_determinant(std::vector<std::vector<double>> matrix);
int get_rank(Square_Matrix m);

// A no-arg constructor
Square_Matrix::Square_Matrix() {}

Square_Matrix::Square_Matrix(std::vector<std::vector<double>> v) {
    if (!v.empty() and v.size() != v[0].size()) {
        throw std::invalid_argument(
            "class SquareMatrix: constructor: input matrix is not square");
    }

    this->v = v;
}

/*
 * A copy constructor to copy from it's base class Matrix.
 */
Square_Matrix::Square_Matrix(const Matrix &right) {
    if (right.get_num_col() != right.get_num_row()) {
        throw std::invalid_argument(
            "class SquareMatrix: copy constructor: input matrix cannot be "
            "converted to a square matrix");
    }

    v = right.get_data();
}

Square_Matrix Square_Matrix::get_identity(size_t n) {

    return Square_Matrix(Matrix::get_identity(n, n));
}

// bad time complexity of k * n^2, can be refined to n^2 + k
Square_Matrix Square_Matrix::get_permutation_matrix(
    size_t n, std::vector<std::pair<size_t, size_t>> instructions) {

    Square_Matrix m = get_identity(n);

    for (int i = 0; i < instructions.size(); i++) {

        if (instructions[i].first > n || instructions[i].second > n) {
            throw std::invalid_argument(
                "class SquareMatrix: get_permutation_matrix: input set of "
                "instructions have row value larger than n");
        }

        m.row_operation_swap(instructions[i].first, instructions[i].second);
    }

    return m;
}

Square_Matrix Square_Matrix::get_permutation_matrix(size_t n, size_t row1,
                                                    size_t row2) {

    Square_Matrix m = get_identity(n);
    return get_permutation_matrix(n, {{row1, row2}});
}

/*
 * The method returns the determinant of the matrix
 * using the helper function det.
 */
double Square_Matrix::determinant() const { return get_determinant(v); }

/*
 * A recursion function which provides the determinant
 * of the given square vector, note that the vector
 * is assumed to be square, an error will occur if it's
 * not the case.
 */
double get_determinant(std::vector<std::vector<double>> matrix) {

    if (matrix.size() == 1) {
        return matrix[0][0];
    }

    else {
        bool first = true;
        double sum = 0;

        for (int i = 0; i < matrix.size(); i++) {

            std::vector<std::vector<double>> v = matrix;
            v.erase(v.begin());

            for (int j = 0; j < v.size(); j++) {
                v[j].erase(v[j].begin() + i);
            }

            first == true ? sum += matrix[0][i] * get_determinant(v)
                          : sum -= matrix[0][i] * get_determinant(v);

            first = !first;
        }

        return sum;
    }
}

/*
 * Returns the cofactor at the indicated row and column.
 *
 * If the row/column is less than 1 or larger than
 * the size of the matrix, the method will display
 * a message indicating the case and return a 1 by 1
 * matrix with NULL as it's only index.
 */
double Square_Matrix::cofactor(int row, int col) const {

    if (row < 1 or row > v.size() or col < 1 or col > v[0].size()) {
        throw std::invalid_argument("class SquareMatrix: function cofactor: "
                                    "input row or argument is out of bound");
    }

    Square_Matrix m = minor(row, col);
    return (row + col) % 2 == 0 ? m.determinant() : -m.determinant();
}

/*
 * The method returns a square matrix that is the
 * minor of the original matrix based on the row
 * and column in the parameter list.
 *
 */
Square_Matrix Square_Matrix::minor(size_t row, size_t col) const {
    // Check if the row/column is in the range
    if (row < 1 or row > v.size() or col < 1 or col > v.size()) {
        throw std::invalid_argument("class SquareMatrix: function minor: "
                                    "input row or argument is out of bound");
    }

    Square_Matrix m;
    m = *this;

    // Erase the row
    m.v.erase(m.v.begin() + row - 1);

    // Erase the column
    for (size_t i = 0; i < m.v.size(); i++) {
        m.v[i].erase(m.v[i].begin() + col - 1);
    }

    return m;
}

/*
 * The method returns the adjoint of the given
 * matrix
 */
Square_Matrix Square_Matrix::adjoint() const {
    Square_Matrix m;

    for (size_t i = 0; i < v.size(); i++) {

        std::vector<double> row;
        for (int j = 0; j < v[0].size(); j++) {
            row.push_back(cofactor(i + 1, j + 1));
        }

        m.v.push_back(row);
    }

    return m.transpose();
}

/*
 * The method returns a square matrix which is the
 * inverse of the original one.
 *
 * If the original matrix is linearly dependent, the
 * method will leave a message indicating no inverse
 * exists and returns a matrix with a single value
 * NULL.
 */
Square_Matrix Square_Matrix::inverse() const {
    Square_Matrix m;

    if (determinant() == 0) {
        throw std::runtime_error("class SquareMatrix: function inverse: "
                                 "input matrix not invertable!");

    }

    else {

        double reciprocal = 1 / determinant();
        m = reciprocal * adjoint();
    }

    return m;
}

/*
 */
int Square_Matrix::rank() { return get_rank(*this); }

/*
 * This is a recursion function which takes the input
 * SquareMatrix object and return the rank of it.
 * Note that non square matrices will return error.
 */
int get_rank(Square_Matrix m) {

    if (m.get_num_row() == 0) {
        return 0;
    }

    if (m.determinant() != 0) {
        return m.get_num_row();
    }

    int largest = get_rank(m.minor(1, 1));

    for (int i = 0; i < m.get_num_row(); i++) {
        for (int j = 0; j < m.get_num_col(); j++) {

            int currentRank = get_rank(m.minor(i + 1, j + 1));

            if (currentRank > largest) {
                largest = currentRank;
            }
        }
    }

    return largest;
}
