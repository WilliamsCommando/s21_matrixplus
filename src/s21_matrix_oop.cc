#include "s21_matrix_oop.h"

/* методы */

s21::S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

s21::S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete[] matrix_;
  this->rows_ = 0;
  this->cols_ = 0;
}

s21::S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

s21::S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (auto i = 0; i < other.rows_; i++)
    memcpy(this->matrix_[i], other.matrix_[i], sizeof(double) * cols_);
}

s21::S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  this->Swap(other);
  other.matrix_ = nullptr;
  other.rows_ = 0;
}

/* операции */

bool s21::S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (auto i = 0; i < other.rows_; i++)
    for (auto j = 0; j < other.cols_; j++)
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > __DBL_EPSILON__)
        return false;
  return true;
}

void s21::S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("Incorrect input");

  for (auto i = 0; i < other.rows_; i++)
    for (auto j = 0; j < other.cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void s21::S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("Incorrect input");

  for (auto i = 0; i < other.rows_; i++)
    for (auto j = 0; j < other.cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void s21::S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; i++)
    for (auto j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void s21::S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ != other.cols_ || cols_ != other.rows_)
    throw std::out_of_range("Incorrect input");

  S21Matrix res = S21Matrix(this->rows_, other.cols_);
  for (auto i = 0; i < rows_; i++)
    for (auto j = 0; j < other.cols_; j++)
      for (auto k = 0; k < cols_; k++)
        res.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
  *this = std::move(res);
}

s21::S21Matrix s21::S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);
  for (auto i = 0; i < res.rows_; i++)
    for (auto j = 0; j < res.cols_; j++) res.matrix_[i][j] = matrix_[j][i];
  return res;
}

s21::S21Matrix s21::S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::out_of_range("Incorrect input");

  S21Matrix res(rows_, cols_);
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      S21Matrix comp_matrix = this->GetComplementMatrix(i, j);
      res.matrix_[i][j] = comp_matrix.Determinant();
      if ((i + j) % 2) res.matrix_[i][j] *= -1;
    }
  }
  return res;
}

double s21::S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::out_of_range("Incorrect input");

  double res = 0, temp = 0;
  int s = 1;
  if (rows_ == 1) {
    res = matrix_[0][0];
  } else {
    for (auto j = 0; j < cols_; ++j) {
      S21Matrix comp_matrix = this->GetComplementMatrix(0, j);
      temp = comp_matrix.Determinant();
      res += s * matrix_[0][j] * temp;
      s *= -1;
    }
  }
  return res;
}

s21::S21Matrix s21::S21Matrix::InverseMatrix() const {
  double det = this->Determinant();
  if (det == 0) throw std::invalid_argument("invalid matrix");
  S21Matrix result = this->CalcComplements().Transpose();
  result.MulNumber(1.0 / det);
  return result;
}

/* операторы */

double& s21::S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_)
    throw std::out_of_range("index is out of range");
  return this->matrix_[row][col];
}

const double& s21::S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_)
    throw std::out_of_range("index is out of range");
  return this->matrix_[row][col];
}

s21::S21Matrix s21::S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

s21::S21Matrix s21::S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

s21::S21Matrix s21::S21Matrix::operator*(const s21::S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

s21::S21Matrix s21::S21Matrix::operator*(const double& num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

void s21::S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
}

void s21::S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
}

void s21::S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
}

void s21::S21Matrix::operator*=(const double num) { this->MulNumber(num); }

s21::S21Matrix s21::S21Matrix::operator=(const S21Matrix& other) {
  this->~S21Matrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->CreateMatrix();
  this->SumMatrix(other);
  return *this;
}

bool s21::S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
}

/* геттеры */

int s21::S21Matrix::GetRows() const { return this->rows_; }

int s21::S21Matrix::GetCols() const { return this->cols_; }

double** s21::S21Matrix::GetMatrix() const { return this->matrix_; }

/* сеттеры */

void s21::S21Matrix::SetRows(int rows) {
  if (rows <= 0) throw std::out_of_range("Incorrect input");
  S21Matrix matrix(rows, this->cols_);
  for (int i = 0; i < matrix.rows_; i++)
    for (int j = 0; j < matrix.cols_; j++)
      if (i < this->rows_) matrix.matrix_[i][j] = this->matrix_[i][j];
  *this = matrix;
}

void s21::S21Matrix::SetCols(int cols) {
  if (cols <= 0) throw std::out_of_range("Incorrect input");
  S21Matrix matrix(this->rows_, cols);
  for (int i = 0; i < matrix.rows_; i++)
    for (int j = 0; j < matrix.cols_; j++)
      if (j < this->cols_) matrix.matrix_[i][j] = this->matrix_[i][j];
  *this = matrix;
}

/* дополнительные */

void s21::S21Matrix::CreateMatrix() {
  if (rows_ < 0 || cols_ < 0) throw std::out_of_range("Incorrect input");
  this->matrix_ = new double*[this->rows_]();
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_]();
  }
}

s21::S21Matrix s21::S21Matrix::GetComplementMatrix(int i_row, int j_col) const {
  S21Matrix res(rows_ - 1, cols_ - 1);
  int set_row = 0, set_col = 0;
  for (int i = 0; i < res.rows_; ++i) {
    if (i == i_row) set_row = 1;
    set_col = 0;
    for (int j = 0; j < res.cols_; ++j) {
      if (j == j_col) set_col = 1;
      res.matrix_[i][j] = matrix_[i + set_row][j + set_col];
    }
  }
  return res;
}

void s21::S21Matrix::Swap(s21::S21Matrix& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}
