#include "../s21_matrix_oop.h"

#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>

s21::S21Matrix create(int row, int col, double x) {
  s21::S21Matrix matrix = s21::S21Matrix(row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) matrix(i, j) = x;
  return matrix;
}

TEST(Constructors, base_test) {
  s21::S21Matrix matrix = s21::S21Matrix();
  s21::S21Matrix matrix2 = s21::S21Matrix(1, 1);
  EXPECT_TRUE(matrix == matrix2);
}

TEST(Constructors, with_params) {
  s21::S21Matrix matrix = s21::S21Matrix(3, 2);
  s21::S21Matrix matrix2 = s21::S21Matrix();
  matrix2.SetRows(3);
  matrix2.SetCols(2);
  EXPECT_TRUE(matrix == matrix2);
}

TEST(Constructors, copy_matrix) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 4.0;
  s21::S21Matrix new_matrix = s21::S21Matrix(matrix);
  EXPECT_EQ(matrix(0, 0), new_matrix(0, 0));
  EXPECT_EQ(matrix(1, 1), new_matrix(1, 1));
}

TEST(Constructors, move_matrix) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 4.0;
  s21::S21Matrix new_matrix(std::move(matrix));
  EXPECT_EQ(new_matrix(0, 0), 1.0);
  EXPECT_EQ(new_matrix(1, 1), 4.0);
}

TEST(GettersAndSetters, getCols) {
  s21::S21Matrix matrix = create(2, 3, 1.0);
  int cols = matrix.GetCols();
  EXPECT_TRUE(cols == 3);
}

TEST(GettersAndSetters, SetCols) {
  s21::S21Matrix matrix = create(2, 3, 1.0);
  matrix.SetCols(2);
  s21::S21Matrix matrix2 = create(2, 2, 1.0);
  EXPECT_TRUE(matrix.EqMatrix(matrix2));
}

TEST(GettersAndSetters, SetColsBigger) {
  s21::S21Matrix matrix = create(2, 2, 1.0);
  matrix.SetCols(3);
  s21::S21Matrix matrix2 = create(2, 3, 0);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 1.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 1.0;
  EXPECT_TRUE(matrix.EqMatrix(matrix2));
}

TEST(GettersAndSetters, getRows) {
  s21::S21Matrix matrix = create(2, 3, 1.0);
  int rows = matrix.GetRows();
  EXPECT_TRUE(rows == 2);
}

TEST(GettersAndSetters, SetRows) {
  s21::S21Matrix matrix = create(2, 3, 1.0);
  matrix.SetRows(3);
  s21::S21Matrix matrix2 = create(3, 3, 1.0);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 1.0;
  matrix2(0, 2) = 1.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 1.0;
  matrix2(1, 2) = 1.0;
  matrix2(2, 0) = 0;
  matrix2(2, 1) = 0;
  matrix2(2, 2) = 0;
  EXPECT_TRUE(matrix.EqMatrix(matrix2));
}

TEST(Overloads, parenthesis) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 4.0;
  double res = matrix(0, 0);
  EXPECT_EQ(res, 1.0);
  res = matrix(1, 1);
  EXPECT_EQ(res, 4.0);
}

TEST(Overloads, equality) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 4.0;
  s21::S21Matrix matrix2 = s21::S21Matrix(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(1, 1) = 4.0;
  EXPECT_TRUE(matrix == matrix2);
}

TEST(Overloads, sum_and_assign) {
  s21::S21Matrix matrix = create(2, 2, 1.0);
  s21::S21Matrix matrix2 = create(2, 2, 2.0);
  matrix += matrix2;
  s21::S21Matrix matrix3 = create(2, 2, 3.0);
  EXPECT_TRUE(matrix3.EqMatrix(matrix));
}

TEST(Overloads, sum_a_b) {
  s21::S21Matrix matrix = create(2, 2, 1.0);
  s21::S21Matrix matrix2 = create(2, 2, 2.0);
  s21::S21Matrix matrix_result = matrix + matrix2;
  s21::S21Matrix matrix3 = create(2, 2, 3.0);
  EXPECT_FALSE(matrix3 == matrix);
  EXPECT_TRUE(matrix3 == matrix_result);
}

TEST(Overloads, sub_a_b) {
  s21::S21Matrix matrix1 = create(2, 2, 1.0);
  s21::S21Matrix matrix2 = create(2, 2, 2.0);
  s21::S21Matrix matrix3 = create(2, 2, 3.0);
  s21::S21Matrix matrix_result = matrix3 - matrix2;
  EXPECT_TRUE(matrix1 == matrix_result);
}

TEST(Overloads, sub_and_assign) {
  s21::S21Matrix matrix = create(2, 2, 1.0);
  s21::S21Matrix matrix2 = create(2, 2, 2.0);
  matrix -= matrix2;
  s21::S21Matrix matrix3 = create(2, 2, -1.0);
  EXPECT_TRUE(matrix3.EqMatrix(matrix));
}

TEST(Overloads, assign) {
  s21::S21Matrix matrix = create(2, 2, 1.0);
  s21::S21Matrix matrix2 = create(1, 2, 2.0);
  matrix = matrix2;
  EXPECT_TRUE(matrix == matrix2);
}

TEST(Overloads, mul_number) {
  s21::S21Matrix matrix = create(2, 2, 4.0);
  s21::S21Matrix matrix3 = create(2, 2, 8.0);
  s21::S21Matrix matrix_result = matrix * 2;
  EXPECT_TRUE(matrix3.EqMatrix(matrix_result));
}

TEST(Overloads, mul_matrix) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = 1.0;
  s21::S21Matrix matrix2 = s21::S21Matrix(3, 2);
  matrix2(0, 0) = 4.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 1.0;
  matrix2(2, 0) = 1.0;
  matrix2(2, 1) = 5.0;
  s21::S21Matrix matrix_result = matrix * matrix2;
  s21::S21Matrix matrix_assert(2, 2);
  matrix_assert(0, 0) = 12;
  matrix_assert(0, 1) = 14;
  matrix_assert(1, 0) = 16;
  matrix_assert(1, 1) = 12;
  EXPECT_TRUE(matrix_assert.EqMatrix(matrix_result));
}

TEST(Overloads, mul_and_assign_number) {
  s21::S21Matrix matrix = create(2, 2, 4.0);
  s21::S21Matrix matrix3 = create(2, 2, 8.0);
  matrix *= 2;
  EXPECT_TRUE(matrix3.EqMatrix(matrix));
}

TEST(Overloads, mul_and_assign_matrix) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = 1.0;
  s21::S21Matrix matrix2 = s21::S21Matrix(3, 2);
  matrix2(0, 0) = 4.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 1.0;
  matrix2(2, 0) = 1.0;
  matrix2(2, 1) = 5.0;
  matrix *= matrix2;
  s21::S21Matrix matrix_assert(2, 2);
  matrix_assert(0, 0) = 12;
  matrix_assert(0, 1) = 14;
  matrix_assert(1, 0) = 16;
  matrix_assert(1, 1) = 12;
  EXPECT_TRUE(matrix_assert.EqMatrix(matrix));
}

TEST(Operations, equality) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 4.0;
  s21::S21Matrix matrix2 = s21::S21Matrix(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(1, 1) = 4.0;
  EXPECT_TRUE(matrix.EqMatrix(matrix2));
}

TEST(Operations, sum) {
  s21::S21Matrix matrix = create(2, 2, 1);
  s21::S21Matrix matrix2 = create(2, 2, 2);
  s21::S21Matrix matrix3 = create(2, 2, 3);
  matrix.SumMatrix(matrix2);
  EXPECT_TRUE(matrix3.EqMatrix(matrix));
}

TEST(Operations, sub) {
  s21::S21Matrix matrix = create(2, 2, 4.0);
  s21::S21Matrix matrix2 = create(2, 2, 1.0);
  s21::S21Matrix matrix3 = create(2, 2, 3.0);
  matrix.SubMatrix(matrix2);
  EXPECT_TRUE(matrix3.EqMatrix(matrix));
}

TEST(Operations, mul_number) {
  s21::S21Matrix matrix = create(2, 2, 4.0);
  s21::S21Matrix matrix3 = create(2, 2, 8.0);
  matrix.MulNumber(2);
  EXPECT_TRUE(matrix3.EqMatrix(matrix));
}

TEST(Operations, mul_matrix) {
  s21::S21Matrix matrix = s21::S21Matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = 1.0;
  s21::S21Matrix matrix2 = s21::S21Matrix(3, 2);
  matrix2(0, 0) = 4.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 1.0;
  matrix2(2, 0) = 1.0;
  matrix2(2, 1) = 5.0;
  matrix.MulMatrix(matrix2);
  s21::S21Matrix matrix_result(2, 2);
  matrix_result(0, 0) = 12;
  matrix_result(0, 1) = 14;
  matrix_result(1, 0) = 16;
  matrix_result(1, 1) = 12;
  EXPECT_TRUE(matrix_result.EqMatrix(matrix));
}

TEST(Operations, transpose) {
  s21::S21Matrix matrix = create(2, 3, 1.0);
  s21::S21Matrix matrix2 = create(3, 2, 1.0);
  s21::S21Matrix transposed = matrix.Transpose();
  EXPECT_TRUE(transposed.EqMatrix(matrix2));
}

TEST(Operations, determinant) {
  s21::S21Matrix matrix = s21::S21Matrix(4, 4);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 3.0;
  matrix(0, 2) = 2.0;
  matrix(0, 3) = 2.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = -3.0;
  matrix(1, 3) = 3.0;
  matrix(2, 0) = 0.0;
  matrix(2, 1) = -1.0;
  matrix(2, 2) = 3.0;
  matrix(2, 3) = 3.0;
  matrix(3, 0) = 0.0;
  matrix(3, 1) = 3.0;
  matrix(3, 2) = 1.0;
  matrix(3, 3) = 1.0;
  double result = matrix.Determinant();
  EXPECT_TRUE(result == -240);
}

TEST(Operations, calcComplements) {
  s21::S21Matrix m1 = s21::S21Matrix(3, 3);
  m1(0, 0) = 0.0;
  m1(0, 1) = -1.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = 1.0;
  m1(1, 2) = 2.0;
  m1(2, 0) = -2.0;
  m1(2, 1) = -1.0;
  m1(2, 2) = 4.0;
  s21::S21Matrix m2 = m1.CalcComplements();
  s21::S21Matrix m3 = s21::S21Matrix(3, 3);
  m3(0, 0) = 6.0;
  m3(0, 1) = -16.0;
  m3(0, 2) = -1.0;
  m3(1, 0) = 1.0;
  m3(1, 1) = 6.0;
  m3(1, 2) = 2.0;
  m3(2, 0) = -5.0;
  m3(2, 1) = 9.0;
  m3(2, 2) = 3.0;
  EXPECT_TRUE(m2 == m3);
}

TEST(Operations, inverse) {
  s21::S21Matrix m1 = s21::S21Matrix(3, 3);
  m1(0, 0) = -1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = -2.0;
  m1(1, 0) = 2.0;
  m1(1, 1) = -1.0;
  m1(1, 2) = 5.0;
  m1(2, 0) = 3.0;
  m1(2, 1) = -2.0;
  m1(2, 2) = 4.0;
  s21::S21Matrix m2 = m1.InverseMatrix();
  s21::S21Matrix m3 = s21::S21Matrix(3, 3);
  m3(0, 0) = 0.6;
  m3(0, 1) = -0.4;
  m3(0, 2) = 0.8;
  m3(1, 0) = 0.7;
  m3(1, 1) = 0.2;
  m3(1, 2) = 0.1;
  m3(2, 0) = -0.1;
  m3(2, 1) = 0.4;
  m3(2, 2) = -0.3;
  EXPECT_TRUE(m2 == m3);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
