#pragma once

#include <cmath>
#include <iostream>

class Matrix {
    friend Matrix operator*(const Matrix& other, float const num);
    friend Matrix operator*(float const num, const Matrix& other);

 private:
    int _rows, _cols;
    float** _matrix;
    float** New_matrix(int rows, int cols);
    void Free_matrix();
    void CopyMatrix(float** matrix_copy);
    Matrix create_minor(int row, int column);

 public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    Matrix operator=(const Matrix& other);

    bool eq_matrix(const Matrix& other) const;
    bool operator==(const Matrix& other) const;
    // sum
    void sum_matrix(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix operator+=(const Matrix& other);
    // sub
    void sub_matrix(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator-=(const Matrix& other);
    // mul
    void mul_number(const float num);
    void mul_matrix(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator*=(const Matrix& other);
    Matrix operator*=(const float num);
    // operation
    Matrix transpose();
    Matrix calc_complements();
    double determinant();
    Matrix inverse_matrix();

    float& operator()(int i, int j) const;
    // other
    int getRows();
    int getCols();
    float* getMass();
    void setRows(int rows);
    void setCols(int cols);
};

