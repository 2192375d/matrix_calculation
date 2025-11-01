#pragma once

#include <iostream>
#include <vector>

struct PLU;

class Matrix {
  protected:
    std::vector<std::vector<double>> v;

  public:
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
    friend std::istream &operator>>(std::istream &in, Matrix &m);

    Matrix();
    Matrix(std::vector<std::vector<double>> v);
    Matrix(const Matrix &right);

    size_t get_num_row() const;
    size_t get_num_col() const;

    std::vector<std::vector<double>> get_data() const;

    std::vector<double> get_col(size_t col_num) const;
    std::vector<double> get_row(size_t row_num) const;
    Matrix row_operation_add(size_t source_row, size_t to_add_row,
                             double scalar) const;
    Matrix row_operation_multiply(size_t source_row, double scalar) const;
    Matrix row_operation_swap(size_t row1, size_t row2) const;

    Matrix operator+(const Matrix &right) const;
    Matrix operator-(const Matrix &right) const;
    Matrix operator*(const Matrix &right) const;
    bool operator==(const Matrix &right) const;

    friend Matrix operator*(const double &left, const Matrix &right);

    // Other methods
    Matrix transpose();

    PLU LU_factorization();
};

struct PLU {
    Matrix permutation_matrix;
    Matrix lower_triangular_matrix;
    Matrix upper_triangular_matrix;
};
