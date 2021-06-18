#pragma once
#include "Matrix.h"
#include <cassert>
#include <vector>

namespace GdCV
{
template<class T>
class LUDecomposition
{
public:
  LUDecomposition(const Matrix<T>& input)
    : A(input)
  {
    assert(input.nRows() == input.nCols());
  }

  void decompose()
  {
    // Assignment 2
  }

  Matrix<T> getL() const
  {
    Matrix<T> result(A);
    // Assignment 2
    return result;
  }

  Matrix<T> getU() const
  {
    Matrix<T> result(A);
    // Assignment 2
    return result;
  }

  const Matrix<T>& getA() const
  {
    return A;
  }

  Matrix<T> solve(Matrix<T> B)
  {
    const auto n = B.nRows();
    Matrix<T> X(n, 1);
    assert(1 == B.nCols());
    return X;
  }

private:
  Matrix<T> A;
 
};
}
