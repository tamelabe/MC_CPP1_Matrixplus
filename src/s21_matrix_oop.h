#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

using namespace std;

class S21Matrix {
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  // Constructors & destructor
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();  // Destructor

  // Getters & setters
  int GetCols();
  int GetRows();
  void SetRows(int rows);
  void SetCols(int cols);

  // Basic functions
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  double Determinant();
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  // Additional functions
  void create_matrix();
  void remove_matrix();
  void rm_rc(S21Matrix& other, int ni, int nj);
  void convert_to_minor(S21Matrix& other);

  // Operators
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double& num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& num);
  double& operator()(const int rows, const int cols);
};

#endif  // SRC_S21_MATRIX_OOP_H_
