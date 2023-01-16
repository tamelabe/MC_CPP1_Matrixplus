#include "s21_matrix_oop.h"

int main() {
    S21Matrix a(3,3);
    a.SetMatrix(0, 0, 5.5);
    a.SetMatrix(2, 2, 1.1);
    S21Matrix b(2, 2);
    b.SetMatrix(0, 0, 5.5);
    b.SetMatrix(1, 1, 1.10001);
    a.Print();
    b.Print();
    bool res = a.EqMatrix(b);
    cout << "res = " <<  res << endl;
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
    if (rows_ > 0 && cols_ > 0 && other.cols_ > 0 && other.rows_ > 0 &&
            rows_ == other.rows_ && cols_ == other.cols_) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; (j < cols_) && flag; j++) {
                cout << matrix_[i][j] - other.matrix_[i][j] << endl;
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
    if (cols_ != other.rows_ || rows_ != other.cols_) {
        throw out_of_range("columns and rows of matrices aren't equal");
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < other.cols_; j++) {
                for (int n = 0; n < other.rows_; n++) {
                    matrix_[i][j] = matrix_[i][n] * other.matrix_[n][j];
                }
            }
        }
    }
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
