#include "../include/SquareMatrix.hpp"
#include <stdexcept>
#include <vector>

double getDeterminant(std::vector<std::vector<double>> matrix);
int getRank(SquareMatrix m);

/*
 * The method returns the determinant of the matrix
 * using the helper function det.
 */
double SquareMatrix::determinant() const { return getDeterminant(v); }

/*
 * A recursion function which provides the determinant
 * of the given square vector, note that the vector
 * is assumed to be square, an error will occur if it's
 * not the case.
 */
double getDeterminant(std::vector<std::vector<double>> matrix) {

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

            first == true ? sum += matrix[0][i] * getDeterminant(v)
                          : sum -= matrix[0][i] * getDeterminant(v);

            first = !first;
        }

        return sum;
    }
}

// A no-arg constructor
SquareMatrix::SquareMatrix() {}

/*
 * A copy constructor to copy from it's base class
 * Matrix.
 */
SquareMatrix::SquareMatrix(const Matrix &right) { v = right.v; }

/*
 * Returns the cofactor at the indicated row and column.
 *
 * If the row/column is less than 1 or larger than
 * the size of the matrix, the method will display
 * a message indicating the case and return a 1 by 1
 * matrix with NULL as it's only index.
 */
double SquareMatrix::cofactor(int row, int col) const {

    if (row < 1 or row > v.size() or col < 1 or col > v[0].size()) {
        throw std::invalid_argument("class SquareMatrix: function cofactor: "
                                    "input row or argument is out of bound");
    }

    SquareMatrix m = minor(row, col);
    return (row + col) % 2 == 0 ? m.determinant() : -m.determinant();
}

/*
 * The method returns a square matrix that is the
 * minor of the original matrix based on the row
 * and column in the parameter list.
 *
 * If the row/column is less than 1 or larger than
 * the size of the matrix, the method will display
 * a message indicating the case and return a 1 by 1
 * matrix with NULL as it's only index.
 */
SquareMatrix SquareMatrix::minor(int row, int col) const {

    Matrix m;
    m.v = v;

    // Check if the row/column is in the range
    if (row < 1 or row > v.size() or col < 1 or col > v.size()) {
        throw std::invalid_argument("class SquareMatrix: function minor: "
                                    "input row or argument is out of bound");
    }

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
SquareMatrix SquareMatrix::adjoint() const {
    SquareMatrix m;

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
SquareMatrix SquareMatrix::inverse() const {
    SquareMatrix m;

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
int SquareMatrix::rank() { return getRank(*this); }

/*
 * This is a recursion function which takes the input
 * SquareMatrix object and return the rank of it.
 * Note that non square matrices will return error.
 */
int getRank(SquareMatrix m) {

    if (m.v.size() == 0) {
        return 0;
    }

    else if (m.determinant() != 0) {
        return m.v.size();
    }

    else {

        int largest = getRank(m.minor(1, 1));

        for (int i = 0; i < m.v.size(); i++) {
            for (int j = 0; j < m.v[0].size(); j++) {

                int currentRank = getRank(m.minor(i + 1, j + 1));

                if (currentRank > largest) {
                    largest = currentRank;
                }
            }
        }

        return largest;
    }
}
