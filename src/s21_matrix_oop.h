#ifndef SRC_S21MATRIX_H_
#define SRC_S21MATRIX_H_

#include <cmath>
#include <cstring>
#include <iostream>

namespace s21 {

class S21Matrix {
 public:
  S21Matrix();
  ~S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  /* операции */
  void SumMatrix(const S21Matrix& other);
  bool EqMatrix(const S21Matrix& other) const;
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  /* операторы */
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;
  S21Matrix operator+(const S21Matrix& other) const;
  void operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  void operator-=(const S21Matrix& other);
  S21Matrix operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double& num) const;
  void operator*=(const S21Matrix& other);
  void operator*=(const double numb);

  /* геттеры и сеттеры */
  int GetRows() const;
  int GetCols() const;
  double** GetMatrix() const;
  void SetRows(int cols);
  void SetCols(int rows);

  /*дополнительные функции */
  void CreateMatrix();
  S21Matrix GetComplementMatrix(int i_row, int j_col) const;
  void Swap(S21Matrix& other);

 private:
  int rows_, cols_;
  double** matrix_;
};

}  // namespace s21

#endif  // SRC_S21MATRIX_H_