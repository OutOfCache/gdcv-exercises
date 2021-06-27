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
      // idea: lower triangle of A has values of L, upper triangle has values of U
      // L_ik = A_ik / A_kk

      for (uint32 k = 0; k < A.nRows() - 1; k++)  // current row we are subtracting from the others
      {
          for (uint32 i = k + 1; i < A.nRows(); i++)
          {
              T l_value = A(i, k) / A(k, k);
              for (uint32 j = k; j < A.nCols(); j++)
              {
                  A(i, j) -= l_value * getA()(k, j);
              }
             A(i, k) = l_value;
          }
      }
  }

  Matrix<T> getL() const
  {
    Matrix<T> result(A);
    // Assignment 2
    result.setIdentity();

    for (uint32 i = 1; i < A.nRows(); i++)
    {
        for (uint32 j = 0; j < i; j++)
        {
            result(i, j) = A(i, j);
        }
    }

    return result;
  }

  Matrix<T> getU() const
  {
      Matrix<T> result(A);
      // Assignment 2
      result.setZero();

      for (uint32 i = 0; i < A.nRows(); i++)
      {
          for (uint32 j = i; j < A.nCols(); j++)
          {
              result(i, j) = A(i, j);
          }
      }
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

    Matrix<T> l = getL();
    Matrix<T> u = getU();
    Matrix<T> Y(n, 1);

    // forward: L * y = b
    for (uint32 i = 0; i < l.nRows(); i++)
    {
        Y(i, 0) = B(i, 0);
        for (uint32 k = 0; k < i; k++)
        {
            Y(i, 0) -= l(i, k) * Y(k, 0);
        }
    }

    // backward: U * x = y
    for (uint32 i = 0; i < u.nRows(); i++)
    {
        uint32 off = n - i - 1;
        X(off, 0) = Y(off, 0);
        for (uint32 k = off + 1; k < n; k++)
        {
            X(off, 0) -= u(off, k) * X(k, 0);
        }
        X(off, 0) /= u(off, off);
    }

    return X;
  }

private:
  Matrix<T> A;
 
};
}
