#include "s21_matrix_oop.h"

int main() {
    return 0;
}

S21Matrix::S21Matrix() {
    rows_ = cols_ = 0;
    matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        matrix_ = new double* [rows];
        for (int i : range(rows)) {
            matrix_[i] = new double[cols];
        }
    }
}

S21Matrix::~S21Matrix() {

}

constexpr auto range(int n) {
    struct iterator {
        int i;
        void operator++() { ++i; }
        bool operator!=(const iterator& rhs) const { return i != rhs.i; }
        const int &operator*() const { return i; }
    };
    struct wrapper {
        int n;
        auto begin() { return iterator{0}; }
        auto end()   { return iterator{n}; }
    };
    return wrapper{n};
}