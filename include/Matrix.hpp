#pragma once

#include <iostream>
#include <vector>

class Matrix {
  public:
    std::vector<std::vector<double>> v;

    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
    friend std::istream &operator>>(std::istream &in, Matrix &m);

    Matrix();
    Matrix(std::vector<std::vector<double>> v);
    Matrix(const Matrix &right);

    // operators between matrices
    Matrix operator+(const Matrix &right) const;
    Matrix operator-(const Matrix &right) const;
    Matrix operator*(const Matrix &right) const;
    bool operator==(const Matrix &right) const;

    // scalar multiplication
    // Matrix operator*(const double &right);
    friend Matrix operator*(const double &left, const Matrix &right);

    // Other methods
    Matrix transpose();
};
