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
    , m_data(new T[other.m_nRows * other.m_nCols])
  {

    // Assignment 1
      //std::copy((other.m_data, other.m_data + m_nCols * m_nRows, m_data);
      std::memcpy(m_data, other.m_data, m_nCols * m_nRows * sizeof(T));
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
      T* tmp = m_data;

      m_data = other.m_data;
      m_nCols = other.m_nCols;
      m_nRows = other.m_nRows;

      other.m_data = nullptr;
      other.m_nCols = 0;
      other.m_nRows = 0;

      if (tmp)
      {
          delete[] tmp;
      }
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

  const T operator()(uint32 row, uint32 col) const
  {
      // Assignment 1
    return m_data[col * nRows() + row];
  }

  T& operator()(uint32 row, uint32 col)
  {
      // Assignment 1
    return m_data[col * nRows() + row];
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
      // Zeilen und Spalten prüfen?
      if (m_nCols == rhs.m_nCols && m_nRows == rhs.m_nRows)
      {
          for (uint32 i = 0; i < nElements(); i++)
          {

              m_data[i] += rhs[i];
          }

      }
      
    return *this;
  }

  friend Matrix operator+(Matrix lhs, Matrix& rhs) 
  {
      // Assignment 1
      lhs += rhs;

    return lhs;
  }

  Matrix operator-=(const Matrix& rhs)
  {
      // Assignment 1
      if (m_nCols == rhs.m_nCols && m_nRows == rhs.m_nRows)
      {
          for (uint32 i = 0; i < nElements(); i++)
          {

              m_data[i] -= rhs[i];
          }

      }
    return *this;
  }

  friend Matrix operator-(Matrix lhs, Matrix& rhs)
  {
      // Assignment 1
      lhs -= rhs;
    return lhs;
  }

  Matrix operator*=(const T s)
  {
      // Assignment 1
      for (uint32 i = 0; i < nElements(); i++)
      {
          m_data[i] *= s;
      }
      
    return *this;
  }

  friend Matrix operator*(Matrix lhs, const T s)
  {
      // Assignment 1
      lhs *= s;

      return lhs;
  }

  friend Matrix operator*(const T s, Matrix rhs)
  {
      // Assignment 1
      rhs *= s;
    return rhs;
  }

  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs)
  {
      // Assignment 1
      
    Matrix result(lhs.nRows(), rhs.nCols());
    result.setZero();
    
    if (lhs.nCols() == rhs.nRows()) {

        for (uint32 i = 0; i < lhs.nRows(); i++)
        {
            for (uint32 j = 0; j < rhs.nCols(); j++)
            {
                for (uint32 k = 0; k < lhs.nCols(); k++)
                {
                    result(i, j) += lhs(i, k) * rhs(k, j);
                }
            }
        }
    }
    
    return result;
  }

  Matrix operator *=(const Matrix& rhs)
  {
      // Assignment 1

      *this = *this * rhs;
    return *this;
  }

  Matrix transpose() const
  {
      // Assignment 1
    Matrix result(nCols(), nRows());

    for (uint32 i = 0; i < result.nRows(); i++)
    {
        for (uint32 j = 0; j < result.nCols(); j++)
        {
            result(i, j) = operator()(j, i);
        }
    }

    return result;
  }

  void setZero()
  {
      // Assignment 1
      uint32 n = nElements();
      for (uint32 i = 0; i < n; i++)
      {
          m_data[i] = T(0); 
      }
  }

  void setIdentity()
  {
      // Assignment 1
      //setZero();
      for (uint32 i = 0; i < nRows(); i++)
      {
          for (uint32 j = 0; j < nCols(); j++)
          {

              operator()(i, j) = j == i ? T(1): T(0);
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