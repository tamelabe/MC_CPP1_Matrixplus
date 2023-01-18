#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructors, Default) {
  S21Matrix mtr;
  EXPECT_EQ(mtr.GetRows(), 0);
  EXPECT_EQ(mtr.GetCols(), 0);
}

TEST(Constructors, Parameterized) {
  S21Matrix mtr(4, 3);
  EXPECT_EQ(mtr.GetRows(), 4);
  EXPECT_EQ(mtr.GetCols(), 3);
}

TEST(Constructors, ParameterizedExcept) {
  EXPECT_ANY_THROW(S21Matrix mtr(-3, -2));
  EXPECT_ANY_THROW(S21Matrix mtr(1, 0));
}

TEST(Constructors, Copy) {
  S21Matrix mtr(4, 3);
  S21Matrix cmp(mtr);
  EXPECT_EQ(cmp.GetRows(), 4);
  EXPECT_EQ(cmp.GetCols(), 3);
  EXPECT_EQ(mtr.EqMatrix(cmp), true);
}

TEST(Constructors, Move) {
  S21Matrix mtr(4, 5);
  S21Matrix cmp(std::move(mtr));
  EXPECT_EQ(cmp.GetRows(), 4);
  EXPECT_EQ(cmp.GetCols(), 5);
  EXPECT_EQ(mtr.GetRows(), 0);
  EXPECT_EQ(mtr.GetCols(), 0);
}

TEST(Methods, EqMatrix) {
  S21Matrix mtr(4, 5);
  S21Matrix cmp(4, 5);
  EXPECT_TRUE(mtr.EqMatrix(cmp));
  cmp(0, 0) = 2.2;
  EXPECT_FALSE(mtr.EqMatrix(cmp));
  mtr(0, 0) = 2.2;
  EXPECT_TRUE(mtr.EqMatrix(cmp));
}

TEST(Methods, SumMatrix) {
  S21Matrix mtr1(5, 5);
  S21Matrix mtr2(5, 5);
  mtr2(1, 1) = 1.1;
  mtr1.SumMatrix(mtr2);
  EXPECT_TRUE(mtr1.EqMatrix(mtr2));
}

TEST(Methods, SumMatrixExcept) {
  S21Matrix mtr1(5, 4);
  S21Matrix mtr2(4, 5);
  EXPECT_ANY_THROW(mtr1.SumMatrix(mtr2));
}

TEST(Methods, SubMatrix) {
  S21Matrix mtr1(5, 5);
  S21Matrix mtr2(5, 5);
  mtr2(1, 1) = 1.1;
  mtr1.SubMatrix(mtr2);
  mtr2(1, 1) = -1.1;
  EXPECT_TRUE(mtr1.EqMatrix(mtr2));
}

TEST(Methods, SubMatrixExcept) {
  S21Matrix mtr1(5, 4);
  S21Matrix mtr2(4, 5);
  EXPECT_ANY_THROW(mtr1.SubMatrix(mtr2));
}

TEST(Methods, MulNumber) {
  S21Matrix mtr1(3, 3);
  double num = 2.2;
  mtr1(1, 1) = 2;
  mtr1.MulNumber(num);
  EXPECT_DOUBLE_EQ(mtr1(1, 1), 4.4);
}

TEST(Methods, MulMatrix) {
  S21Matrix mtr1(3, 2);
  S21Matrix mtr2(2, 3);
  S21Matrix res(3, 3);

  mtr1(0, 0) = 1;
  mtr1(1, 0) = 2;
  mtr1(2, 0) = 3;
  mtr1(0, 1) = 4;
  mtr1(1, 1) = 5;
  mtr1(2, 1) = 6;

  mtr2(0, 0) = 1;
  mtr2(0, 1) = -1;
  mtr2(0, 2) = 1;
  mtr2(1, 0) = 2;
  mtr2(1, 1) = 3;
  mtr2(1, 2) = 4;

  res(0, 0) = 9;
  res(0, 1) = 11;
  res(0, 2) = 17;
  res(1, 0) = 12;
  res(1, 1) = 13;
  res(1, 2) = 22;
  res(2, 0) = 15;
  res(2, 1) = 15;
  res(2, 2) = 27;

  mtr1.MulMatrix(mtr2);
  EXPECT_TRUE(mtr1.EqMatrix(res));
}

TEST(Methods, MulMatrixExcept) {
  S21Matrix mtr1(5, 4);
  S21Matrix mtr2(5, 5);
  EXPECT_ANY_THROW(mtr1.MulMatrix(mtr2));
}

TEST(Methods, Transpose) {
  S21Matrix mtr1(3, 2);
  S21Matrix res(2, 3);

  mtr1(0, 0) = 1;
  mtr1(1, 0) = 2;
  mtr1(2, 0) = 3;
  mtr1(0, 1) = 4;
  mtr1(1, 1) = 5;
  mtr1(2, 1) = 6;

  res(0, 0) = 1;
  res(0, 1) = 2;
  res(0, 2) = 3;
  res(1, 0) = 4;
  res(1, 1) = 5;
  res(1, 2) = 6;

  S21Matrix mtr2(mtr1.Transpose());
  EXPECT_TRUE(mtr2.EqMatrix(res));
}

TEST(Methods, Determinant) {
  S21Matrix mtr1(4, 4);
  mtr1(0, 0) = 9;
  mtr1(0, 1) = 2;
  mtr1(0, 2) = 2;
  mtr1(0, 3) = 4;
  mtr1(1, 0) = 3;
  mtr1(1, 1) = 4;
  mtr1(1, 2) = 4;
  mtr1(1, 3) = 4;
  mtr1(2, 0) = 4;
  mtr1(2, 1) = 4;
  mtr1(2, 2) = 9;
  mtr1(2, 3) = 9;
  mtr1(3, 0) = 1;
  mtr1(3, 1) = 1;
  mtr1(3, 2) = 5;
  mtr1(3, 3) = 1;
  EXPECT_EQ(mtr1.Determinant(), -578);
  S21Matrix mtr2(1, 1);
  mtr2(0, 0) = 10;
  EXPECT_EQ(mtr2.Determinant(), 10);
  S21Matrix mtr3(2, 2);
  mtr3(0, 0) = 1.1;
  mtr3(0, 1) = 3.5;
  mtr3(1, 0) = -2;
  mtr3(1, 1) = 4;
  EXPECT_DOUBLE_EQ(mtr3.Determinant(), 11.4);
}

TEST(Methods, DeterminantDop) {
  S21Matrix mtr(4, 4);
  mtr(0, 0) = 1;
  mtr(0, 1) = 2;
  mtr(0, 2) = 3;
  mtr(0, 3) = 4;
  mtr(1, 0) = 1;
  mtr(1, 1) = 2;
  mtr(1, 2) = 5;
  mtr(1, 3) = 7;
  mtr(2, 0) = 1;
  mtr(2, 1) = 0;
  mtr(2, 2) = 6;
  mtr(2, 3) = 8;
  mtr(3, 0) = 1;
  mtr(3, 1) = 0;
  mtr(3, 2) = 6;
  mtr(3, 3) = 6;
  EXPECT_EQ(mtr.Determinant(), -8);
}

TEST(Methods, DeterminantExcept) {
  S21Matrix mtr(3, 2);
  EXPECT_ANY_THROW(mtr.Determinant());
}

TEST(Methods, CalcComplements) {
  S21Matrix mtr1(3, 3);
  S21Matrix res(3, 3);
  mtr1(0, 0) = 1;
  mtr1(0, 1) = 2;
  mtr1(0, 2) = 3;
  mtr1(1, 0) = 0;
  mtr1(1, 1) = 4;
  mtr1(1, 2) = 2;
  mtr1(2, 0) = 5;
  mtr1(2, 1) = 2;
  mtr1(2, 2) = 1;

  res(0, 0) = 0;
  res(0, 1) = 10;
  res(0, 2) = -20;
  res(1, 0) = 4;
  res(1, 1) = -14;
  res(1, 2) = 8;
  res(2, 0) = -8;
  res(2, 1) = -2;
  res(2, 2) = 4;

  S21Matrix mtr2(mtr1.CalcComplements());
  EXPECT_TRUE(mtr2.EqMatrix(res));

  mtr1.SetCols(1);
  mtr1.SetRows(1);
  res.SetCols(1);
  res.SetRows(1);
  mtr1(0, 0) = 1;
  res(0, 0) = 1;
  S21Matrix mtr3(mtr1.CalcComplements());
  EXPECT_TRUE(mtr3.EqMatrix(res));
}

TEST(Methods, CalcComplementsExcept) {
  S21Matrix mtr1(5, 4);
  EXPECT_ANY_THROW(mtr1.CalcComplements());
}

TEST(Methods, InverseMatrix) {
  S21Matrix mtr1(3, 3);
  S21Matrix res(3, 3);
  mtr1(0, 0) = 2;
  mtr1(0, 1) = 6;
  mtr1(0, 2) = 5;
  mtr1(1, 0) = 5;
  mtr1(1, 1) = 3;
  mtr1(1, 2) = -2;
  mtr1(2, 0) = 7;
  mtr1(2, 1) = 4;
  mtr1(2, 2) = -3;

  res(0, 0) = 1;
  res(0, 1) = -38;
  res(0, 2) = 27;
  res(1, 0) = -1;
  res(1, 1) = 41;
  res(1, 2) = -29;
  res(2, 0) = 1;
  res(2, 1) = -34;
  res(2, 2) = 24;

  S21Matrix mtr2(mtr1.InverseMatrix());
  EXPECT_TRUE(mtr2.EqMatrix(res));
}

TEST(Methods, InverseMatrixDop) {
  S21Matrix mtr1(3, 3);
  mtr1(0, 0) = 4;
  mtr1(0, 1) = -2;
  mtr1(0, 2) = 1;
  mtr1(1, 0) = 1;
  mtr1(1, 1) = 6;
  mtr1(1, 2) = -2;
  mtr1(2, 0) = 1;
  mtr1(2, 1) = 0;
  mtr1(2, 2) = 0;
  mtr1 = mtr1.InverseMatrix();
  EXPECT_EQ(mtr1(0, 1), 0);
  EXPECT_EQ(mtr1(0, 2), 1);
  EXPECT_EQ(mtr1(1, 0), 1);
  EXPECT_EQ(mtr1(2, 0), 3);
  EXPECT_EQ(mtr1(2, 1), 1);
  EXPECT_EQ(mtr1(2, 2), -13);
}

TEST(Methods, InverseMatrixExcept) {
  S21Matrix mtr1(3, 3);

  mtr1(0, 0) = 1;
  mtr1(0, 1) = 4;
  mtr1(0, 2) = 1;
  mtr1(1, 0) = 3;
  mtr1(1, 1) = 7;
  mtr1(1, 2) = 2;
  mtr1(2, 0) = 3;
  mtr1(2, 1) = 2;
  mtr1(2, 2) = 1;
  EXPECT_EQ(mtr1.Determinant(), 0);
  EXPECT_ANY_THROW(mtr1.InverseMatrix());
}

TEST(Methods, InverseMatrixExceptDop) {
  S21Matrix mtr1(5, 4);
  EXPECT_ANY_THROW(mtr1.CalcComplements());
}

TEST(AccessorMutator, GetRows_cols) {
  S21Matrix mtr(2, 3);
  EXPECT_EQ(mtr.GetRows(), 2);
  EXPECT_EQ(mtr.GetCols(), 3);
}

TEST(AccessorMutator, SetRows) {
  S21Matrix m(2, 3);
  m(1, 1) = 4.4;
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 3);
  m.SetRows(4);
  m(3, 2) = 5.5;
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m(3, 2), 5.5);
  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(AccessorMutator, SetCols) {
  S21Matrix m(2, 3);
  m(1, 1) = 4.4;
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 3);
  m.SetCols(5);
  m(1, 4) = 5.5;
  EXPECT_EQ(m(1, 1), 4.4);
  EXPECT_EQ(m(1, 4), 5.5);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 5);
}

TEST(Operators, OperatorSum) {
  S21Matrix mtr1(5, 5);
  S21Matrix mtr2(5, 5);
  mtr2(1, 1) = 1.1;
  S21Matrix mtr3 = mtr1 + mtr2;
  EXPECT_TRUE(mtr3.EqMatrix(mtr2));
}

TEST(Operators, OperatorSumExcept) {
  S21Matrix mtr1(5, 5);
  S21Matrix mtr2(6, 5);
  EXPECT_ANY_THROW(mtr1 + mtr2);
}

TEST(Operators, OperatorSub) {
  S21Matrix mtr1(5, 5);
  S21Matrix mtr2(5, 5);
  mtr1(1, 1) = 6.6;
  mtr2(1, 1) = 1.1;
  S21Matrix mtr3 = mtr1 - mtr2;
  EXPECT_EQ(mtr3(1, 1), 5.5);
}

TEST(Operators, OperatorSubExcept) {
  S21Matrix mtr1(5, 5);
  S21Matrix mtr2(6, 5);
  EXPECT_ANY_THROW(mtr1 - mtr2);
}

TEST(Operators, OperatorMulNum) {
  S21Matrix mtr1(3, 3);
  double num = 2.2;
  mtr1(1, 1) = 2;
  S21Matrix mtr2 = mtr1 * num;
  EXPECT_DOUBLE_EQ(mtr2(1, 1), 4.4);
}

TEST(Operators, OperatorMulMatrix) {
  S21Matrix mtr1(3, 2);
  S21Matrix mtr2(2, 3);
  S21Matrix res(3, 3);

  mtr1(0, 0) = 1;
  mtr1(1, 0) = 2;
  mtr1(2, 0) = 3;
  mtr1(0, 1) = 4;
  mtr1(1, 1) = 5;
  mtr1(2, 1) = 6;

  mtr2(0, 0) = 1;
  mtr2(0, 1) = -1;
  mtr2(0, 2) = 1;
  mtr2(1, 0) = 2;
  mtr2(1, 1) = 3;
  mtr2(1, 2) = 4;

  res(0, 0) = 9;
  res(0, 1) = 11;
  res(0, 2) = 17;
  res(1, 0) = 12;
  res(1, 1) = 13;
  res(1, 2) = 22;
  res(2, 0) = 15;
  res(2, 1) = 15;
  res(2, 2) = 27;

  S21Matrix mtr3 = mtr1 * mtr2;
  EXPECT_TRUE(mtr3.EqMatrix(res));
}

TEST(Operators, OperatorEq) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, false);
  b.SetCols(3);
  a(1, 1) = 1.1;
  b(1, 1) = 1.1;
  EXPECT_EQ(a == b, true);
  b(1, 2) = 1.1;
  EXPECT_EQ(a == b, false);
}

TEST(Operators, OperatorAssign) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 5);
  a = b;
  EXPECT_EQ(a == b, true);
}

TEST(Operators, OperatorSumAssign) {
  S21Matrix mtr1(5, 5);
  mtr1(1, 1) = 1.1;
  S21Matrix mtr2(5, 5);
  mtr2 += mtr1;
  EXPECT_TRUE(mtr1.EqMatrix(mtr2));
}

TEST(Operators, OperatorSubAssign) {
  S21Matrix mtr1(5, 5);
  mtr1(1, 1) = 1.1;
  S21Matrix mtr2(5, 5);
  mtr2 -= mtr1;
  mtr1(1, 1) = -1.1;
  EXPECT_TRUE(mtr1.EqMatrix(mtr2));
}

TEST(Operators, OperatorMulEqMatr) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, OperatorMulEqExcept) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(Operators, OperatorMulEqNum) {
  S21Matrix a(3, 2);
  double num = 2;
  a(1, 1) = 1.1;
  a *= num;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(assignmentOperator, OperatorBraket) {
  S21Matrix m(2, 3);
  m(1, 1) = 3;
  EXPECT_EQ(m(1, 1), 3);
}

TEST(functionalFuncTest, OperatorBraketExcept) {
  S21Matrix m(1, 1);
  EXPECT_ANY_THROW(m(5, 0) = 5);
}

TEST(functionalFuncTest, OperatorBraketExceptDop) {
  S21Matrix m(3, 3);
  m(1, 1) = 1;
  EXPECT_EQ(m(1, 1), 1);
  EXPECT_ANY_THROW(m(-1, -1));
  EXPECT_ANY_THROW(m(0, -1));
  EXPECT_ANY_THROW(m(-1, 0));
  EXPECT_ANY_THROW(m(-1, 1));
}

TEST(assignmentOperator, OperatorBraketExceptDop2) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m(1, 5));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}