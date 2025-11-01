#pragma once

#include <iostream>
#include <tuple>
#include <utility>
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

    static Matrix get_zero_matrix(size_t num_row, size_t num_col);
    static Matrix get_identity(size_t num_row, size_t num_col);

    size_t get_num_row() const;
    size_t get_num_col() const;

    std::vector<std::vector<double>> get_data() const;

    std::vector<double> get_row(size_t row_num) const;
    std::vector<double> get_col(size_t col_num) const;

    void set_row(size_t row_num, const std::vector<double> &row);
    void set_col(size_t col_num, const std::vector<double> &col);
    void set_entry(size_t i, size_t j, double val);

    void row_operation_add(size_t source_row, size_t to_add_row, double scalar);
    void row_operation_multiply(size_t source_row, double scalar);
    void row_operation_swap(size_t row1, size_t row2);

    Matrix operator+(const Matrix &right) const;
    Matrix operator-(const Matrix &right) const;
    Matrix operator*(const Matrix &right) const;
    bool operator==(const Matrix &right) const;

    friend Matrix operator*(const double &left, const Matrix &right);

    // Other methods
    Matrix transpose();

    std::tuple<Matrix, Matrix, Matrix> LU_factorization();
};

struct PLU {
    std::pair<std::vector<Matrix>, std::vector<Matrix>> PL_pair;
    Matrix U;
};
