#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <iostream>
#include <cmath>

using namespace std;

class S21Matrix {
    // Attributes
    int rows_, cols_;         // Rows and columns
    double **matrix_;         // Pointer to the memory where the matrix is allocated

public:
    S21Matrix();              // Default constructor
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();             // Destructor

    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    double Determinant();
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    S21Matrix InverseMatrix();

//    bool check();

    void Print();  // testing

    void SetMatrix(int i, int j, double value);
};

//сonstexpr auto range(int n);

#endif  // SRC_S21_MATRIX_OOP_H_