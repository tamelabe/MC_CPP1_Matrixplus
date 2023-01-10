#ifndef SRC_TESTING_HPP_
#define SRC_TESTING_HPP_

#include  <iostream>
#include <vector>

using namespace std;

class info {
    int a, b;
public:
    info() {
        a = b = 0;
    }
    info(int A) {
        a = A;
        b = A;
    }
    info(int A, int B) {
        a = A, b = B;
    }
    info(int A, bool boolean) {
        a = A;
        if (boolean) {
            b = 1;
        } else {
            b = -1;
        }
    }
    int sum() {
        return a + b;
    }
    void Print() {
        cout << "a = " << a << " b = " << b << endl;
    }
    void set_V(int A, int B) {
        a = A;
        b = B;
    }
    int get_V_a () {
        return a;
    }
    int get_V_b () {
        return b;
    }
};

#endif  // SRC_TESTING_HPP_