#include "s21_matrix_oop.h"

int main() {
    S21Matrix a(3,3);
    a.SetMatrix(0, 0, 5.5);
    a.SetMatrix(2, 2, 1.1);
    a.Print();
    return 0;
}

//////***CONSTRUCTORS AND DESTRUCTOR***//////
S21Matrix::S21Matrix() {
    rows_ = cols_ = 0;
    matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        matrix_ = new double* [rows];
        for (int i = 0; i < rows; i++) {
            matrix_[i] = new double[cols];
        }
    }
    rows_ = rows;
    cols_ = cols;
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = new double* [other.rows_];
    for (int i = 0; i < other.rows_; i++) {
        this->matrix_[i] = new double[other.cols_];
        for (int j = 0; j < this->cols_; j++) {
            this->matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    :   rows_(other.rows_),
        cols_(other.cols_),
        matrix_(other.matrix_) {
    other.matrix_ = nullptr;
    other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
    rows_ = cols_ = 0;
    for(int i = 0; i < rows_; i++) {
        delete[]matrix_[i];
    }
    delete[]matrix_;
    matrix_ = nullptr;
}

//////***MATRIX FUNCTIONS***//////

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    bool flag = true;
    if (this->rows_ > 0 && this->cols_ > 0 && other.cols_ > 0 && other.rows_ > 0 &&
            this->rows_ == other.rows_ && this->cols_ == other.cols_) {
        for (int i = 0; i < this->rows_; i++) {
            for (int j = 0; (j < this->cols_) && flag; j++) {
                if (fabs(this->matrix_[i][j] - other.matrix_[i][j] > 1e-7) {
                    flag = false;
                }
            }
        }
    } else {
        flag = false;
    }
    return flag;
}


//bool S21Matrix::check() {
//    bool flag  = false;
//    if (rows_ > 0 && cols_ > 0) {
//        flag = true;
//    }
//    return flag;
//}

void S21Matrix::Print() {
    for(int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            cout << matrix_[j][i] << " ";
        }
        cout << endl;
    }
}

void S21Matrix::SetMatrix(int i, int j, double value) {
    matrix_[i][j] = value;
}
