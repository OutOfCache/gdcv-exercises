#pragma once
#include <cogra/types.h>
#include <algorithm>
using namespace cogra;

namespace GdCV
{
template<class T>
class Matrix
{
public:
  Matrix()
    : m_data(new T[1])
    , m_nRows(1)
    , m_nCols(1)

  { }

  explicit Matrix(uint32 nCols)
    : m_data(new T[m_nCols])
    , m_nRows(1)
    , m_nCols(nCols)

  {}

  Matrix(uint32 nRows, uint32 nCols)
    : m_data(new T[nRows * nCols])
    , m_nRows(nRows)
    , m_nCols(nCols)
  {}

  Matrix(const Matrix<T>& other)
      // Assignment 1
    : m_nRows(other.m_nRows)
    , m_nCols(other.m_nCols)
    , m_data(new T[nRows * nCols])
  {

    // Assignment 1
      std::copy(std::begin(other.m_data), std::end(other.m_data), std::begin(m_data));
  }

  Matrix(Matrix<T>&& other) noexcept
      : m_nRows(std::exchange(other.m_nRows, 0))
      , m_nCols(std::exchange(other.m_nCols, 0))
      , m_data(std::exchange(other.m_data, nullptr))
  {
      // Assignment 1
  }

  Matrix& operator=(const Matrix<T>& other)
  {
      // Assignment 1
      Matrix<T> tmp(other);

      std::swap(m_nRows, tmp.m_nRows);
      std::swap(m_nCols, tmp.m_nCols);
      std::swap(m_data, tmp.m_data);
    return *this;
  }

  Matrix& operator=(Matrix<T>&& other) noexcept
  {
      // Assignment 1
      std::swap(m_n_Rows, other.m_nRows);
      std::swap(m_n_Cols, other.m_nCols);
      std::swap(m_data, other.m_data);

    return *this;
  }

  ~Matrix()
  {
      delete[] m_data;
  }

  uint32 nRows() const
  {
      // Assignment 1
    return m_nRows;
  }

  uint32 nCols() const
  {
      // Assignment 1
    return m_nCols;
  }

  uint32 nElements() const
  {
      // Assignment 1
    return m_nRows * m_nCols;
  }

  const T* const data()  const
  {
      // Assignment 1
    return m_data;
  }

  T* data()
  {
      // Assignment 1
    return m_data;
  }

  const T operator()(uint32 x, uint32 y) const
  {
      // Assignment 1
    return m_data[0];
  }

  T& operator()(uint32 x, uint32 y)
  {
      // Assignment 1
    return m_data[0];
  }

  const T operator[](uint32 ofs) const
  {
      // Assignment 1
    return m_data[ofs];
  }

  T& operator[](uint32 ofs)
  {
      // Assignment 1
    return m_data[ofs];
  }

  Matrix operator+=(const Matrix& rhs)
  {
      // Assignment 1
    return *this;
  }

  friend Matrix operator+(Matrix lhs, Matrix& rhs) 
  {
      // Assignment 1
    return lhs;
  }

  Matrix operator-=(const Matrix& rhs)
  {
      // Assignment 1
    return *this;
  }

  friend Matrix operator-(Matrix lhs, Matrix& rhs)
  {
      // Assignment 1
    return lhs;
  }

  Matrix operator*=(const T s)
  {
      // Assignment 1
    return *this;
  }

  friend Matrix operator*(Matrix lhs, const T s)
  {
      // Assignment 1
    return lhs;
  }

  friend Matrix operator*(const T s, Matrix rhs)
  {
      // Assignment 1
    return rhs;
  }

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs)
  {
      // Assignment 1
    Matrix result(1, 1);
    return result;
  }

  Matrix operator *=(const Matrix& rhs)
  {
      // Assignment 1
    return *this;
  }

  Matrix transpose() const
  {
      // Assignment 1
    Matrix result(1, 1);
    return result;
  }

  void setZero()
  {
      // Assignment 1
      uint32 n = nElements();
      for (int i = 0; i < n; i++)
      {
          m_data[i] = 0.0f; 
      }
  }

  void setIdentity()
  {
      // Assignment 1
      for (int i = 0; i < nRows(); i++)
      {
          for (int j = 0; j < nCols(); j++)
          {
              if (i == j)
              {
                  m_data[i] = 1.0f;
              }
              else
              {
                  m_data[i] = 0.0f;
              }
          }
      }
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
  {
    os << "[\n";
    for(uint32 i = 0; i < m.m_nRows; i++)
    {
      os << "[";
      for(uint32 j = 0; j < m.m_nCols-1; j++)
      {
        os << m(i, j) << ", ";
      }
      os << m(i, m.m_nCols - 1) << "];\n";
    }
    os << "]\n";
    return os;
  }

private:
  T*                     m_data;

  uint32                      m_nRows;

  uint32                      m_nCols;
};


}