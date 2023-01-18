#include "s21_matrix_oop.h"

//////***CONSTRUCTORS AND DESTRUCTOR***//////
S21Matrix::S21Matrix() {
  rows_ = cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  create_matrix();
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) this->matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  //    cout << "Destr start" << endl;
  remove_matrix();
  rows_ = cols_ = 0;
  //    cout << "Destr end" << endl;
}

//////***ADDONS FOR CONSTR AND DESTR***//////
void S21Matrix::create_matrix() {
  if (rows_ <= 0 || cols_ <= 0) throw out_of_range("Incorrect matrix size");
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::remove_matrix() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  matrix_ = nullptr;
}

//////***GETTERS & SETTERS***//////
int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows != rows_) {
    S21Matrix temp(rows, cols_);
    int tmp_rows = 0;
    if (rows < rows_)
      tmp_rows = rows;
    else
      tmp_rows = rows_;
    for (int i = 0; i < tmp_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = temp;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols != cols_) {
    S21Matrix temp(rows_, cols);
    int tmp_cols = 0;
    if (cols < cols_)
      tmp_cols = cols;
    else
      tmp_cols = cols_;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < tmp_cols; j++) {
        temp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = temp;
  }
}

//////***MATRIX FUNCTIONS***//////
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool flag = true;
  if (rows_ > 0 && cols_ > 0 && other.cols_ > 0 && other.rows_ > 0 &&
      rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; (j < cols_) && flag; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          flag = false;
        }
      }
    }
  } else {
    flag = false;
  }
  return flag;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range("matrices aren't equal");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw out_of_range("matrices aren't equal");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_ || rows_ != other.cols_)
    throw out_of_range("columns and rows of matrices aren't equal");
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int n = 0; n < other.rows_; n++) {
        temp.matrix_[i][j] += matrix_[i][n] * other.matrix_[n][j];
      }
    }
  }
  *this = temp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix temp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return temp;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw out_of_range("rows and cols aren't equal");
  }
  double res = 0, degree = 1;
  if (rows_ == 1) {
    res = matrix_[0][0];
  } else if (rows_ == 2) {
    res = (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  } else {
    S21Matrix temp((rows_ - 1), (cols_ - 1));
    for (int j = 0; j < rows_; j++) {
      this->rm_rc(temp, 0, j);
      res += degree * matrix_[0][j] * temp.Determinant();
      degree *= -1;
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw out_of_range("rows and cols aren't equal");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = matrix_[0][0];
  } else {
    this->convert_to_minor(res);
    for (int i = 0; i < res.rows_; i++) {
      for (int j = 0; j < res.cols_; j++) {
        res.matrix_[i][j] *= pow(-1, i + j);
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw out_of_range("Rows and columns must be equal");
  }
  double det = 0;
  det = this->Determinant();
  if (!det) throw out_of_range("Determinant must not be zero");
  S21Matrix M1(rows_, cols_);
  if (fabs(det) > 1e-7) {
    M1 = this->CalcComplements();
    M1 = M1.Transpose();
    M1.MulNumber((double)1.0 / det);
  }
  return M1;
}

//////***ADDITIONAL FUNCTIONS***//////
// Creates matrix of the minors from the default matrix
void S21Matrix::convert_to_minor(S21Matrix& other) {
  S21Matrix res(rows_, cols_);
  S21Matrix mnr(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double det = 0;
      this->rm_rc(mnr, i, j);
      det = mnr.Determinant();
      other.matrix_[i][j] = det;
    }
  }
}

// Creates minor of any element of the matrix (i and j)
void S21Matrix::rm_rc(S21Matrix& other, int ni, int nj) {
  int i_row = 0, i_col = 0;
  for (int i = 0; i < other.rows_; i++) {
    if (i == ni) {
      i_row = 1;  // Catches the desired row to skip
    }
    for (int j = 0; j < other.cols_; j++) {
      if (j == nj) {
        i_col = 1;  // Catches the desired column to skip
      }
      other.matrix_[i][j] = matrix_[i + i_row][j + i_col];
    }
    i_col = 0;
  }
}

//////***OPERATORS***//////
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double& num) {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    remove_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    create_matrix();
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& num) {
  this->MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(const int row, const int col) {
  if (rows_ <= row || cols_ <= col || row < 0 || col < 0) {
    throw out_of_range("Incorrect index");
  }
  return matrix_[row][col];
}
