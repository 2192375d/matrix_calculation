#include "../include/Matrix.hpp"
#include "../include/helpers.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
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
    size_t numRow;
    size_t numCol;

    // Get number of row
    do {

        // std::system("clear");

        std::cout << "Enter number of row: ";
        std::cin >> numRow;
        if (numRow < 0) {
            std::cout << "Invalid input!" << std::endl;
            pause_console();
        }
    } while (numRow < 0);

    // Get number of column
    do {

        // std::system("clear");

        std::cout << "Enter number of column: ";
        std::cin >> numCol;
        if (numCol < 0) {
            std::cout << "Invalid input!" << std::endl;
            pause_console();
        }
    } while (numCol < 0);

    // Create an empty vector
    for (size_t i = 0; i < numRow; i++) {
        std::vector<double> row;

        for (size_t j = 0; j < numCol; j++) {
            row.push_back(0);
        }

        m.v.push_back(row);
    }

    // Get each value
    for (size_t i = 0; i < numRow; i++) {
        for (size_t j = 0; j < numCol; j++) {

            // std::system("clear");

            // Print the matrix
            std::cout << m << std::endl;

            // Get the value
            std::cout << "Enter the value at " << i + 1 << ", " << j + 1
                      << ": ";
            in >> m.v[i][j];
        }
    }

    // std::system("clear");

    // std::cout << "Here is yoru matrix!" << std::endl;
    std::cout << m << std::endl;

    pause_console();

    return in;
}

// default constructor
Matrix::Matrix() { v.resize(0); }

// constructor
Matrix::Matrix(std::vector<std::vector<double>> v) { this->v = v; }

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

/*
 * The method returns the matrix from the scalar
 * multiplication where the scalar value is on the
 * right.
 *
 * Note that this method is removed because it's
 * not a good practice to have stuffs like M * 4
 * Should just be 4 * M instead
 */
// Matrix Matrix::operator*(const double &right) {
//     Matrix m;
//
//     for (int i = 0; i < v.size(); i++) {
//         std::vector<double> row;
//
//         for (int j = 0; j < v[0].size(); j++) {
//             row.push_back(right * v[i][j]);
//         }
//
//         m.v.push_back(row);
//     }
//
//     return m;
// }

/*
 * The method returns the matrix from the scalar
 * multiplication where the scalar value is on the
 * left.
 */
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

/*
 * Use linear search to loop through each number
 * in the given matrix, find the one with the
 * largest number of digit and returns the number
 * of digit of it. Note that the decimal point is
 * considered as a digit as well.
 */
int getLargestDigit(std::vector<std::vector<double>> m) {
    int largest = 0;
    for (size_t i = 0; i < m.size(); i++) {
        for (size_t j = 0; j < m[i].size(); j++) {
            if (largest < getNumDigit(m[i][j])) {
                largest = getNumDigit(m[i][j]);
            }
        }
    }

    return largest;
}

/*
 * Return the number of digit of the given number.
 * The decimal point is considered as a digit as well.
 */
int getNumDigit(double n) {

    int numDigit = 0;

    if (n < 0) {
        numDigit++;
    }

    n = std::abs(n);

    // Special case n = 0 or n is null (printed as "?"), the number of digit is
    // 1
    if (n == 0) {
        return 1;
    }

    // When the number is an integer
    else if (n == int(n)) {

        int x = n;

        while (x != 0) {
            x /= 10;
            numDigit++;
        }
    }

    // When the number is a decimal
    else {
        std::string s = std::to_string(n);

        for (int i = s.size() - 1; s[i] == '0'; i--) {
            s.pop_back();
        }

        numDigit += s.size();
    }

    // Return it!
    return numDigit;
}
