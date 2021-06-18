#include "Matrix.h"
#include "LUDecomposition.h"
#include <iostream>

using namespace GdCV;

typedef Matrix<float32> Matrix32;
typedef Matrix<float64> Matrix64;

template<class T>
Matrix<T> increasingMatrix(uint32 nRows, uint32 nCols)
{
  Matrix<T> result(nRows, nCols);
  T i = 1;
  for(uint32 r = 0; r < nRows; r++)
  {
    for(uint32 c = 0; c < nCols; c++)
    {
      result(r, c) = i;
      i += T(1);
    }
  }
  return result;
}

template<class T>
Matrix<T> hilbertMatrix(uint32 nRows, uint32 nCols)
{
  Matrix<T> result(nRows, nCols);
  for(uint32 r = 0; r < nRows; r++)
  {
    for(uint32 c = 0; c < nCols; c++)
    {
      result(r, c) = T(1) / T(r + c + 1 );
      
    }
  }
  return result;
}


void testZero()
{
  {
    Matrix32 a(4, 4);
    a.setZero();
    std::cerr << a;
  }

  {
    Matrix32 a(5, 4);
    a.setZero();
    std::cerr << a;
  }

  {
    Matrix32 a(4, 5);
    a.setZero();
    std::cerr << a;
  }
}

void testIdentity()
{
  {
    Matrix32 a(4, 4);
    a.setIdentity();
    std::cerr << a;
  }

  {
    Matrix32 a(5, 4);
    a.setIdentity();
    std::cerr << a;
  }

  {
    Matrix32 a(4, 5);
    a.setIdentity();
    std::cerr << a;
  }
}

void testTranspose()
{
  {
    auto a = increasingMatrix<float32>(3, 3);
    std::cerr << a;
    auto b = a.transpose();
    std::cerr << b;
  }
  {
    auto a = increasingMatrix<float32>(4, 3);
    std::cerr << a;
    auto b = a.transpose();
    std::cerr << b;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    std::cerr << a;
    auto b = a.transpose();
    std::cerr << b;
  }
}

void testScale()
{
  {
    auto a = increasingMatrix<float32>(3, 3);
    std::cerr << a;
    auto b = 2 * a;
    std::cerr << b;
  }

  {
    auto a = increasingMatrix<float32>(3, 3);
    std::cerr << a;
    auto b = a * 2;
    std::cerr << b;
  }

  {
    auto a = increasingMatrix<float32>(3, 3);
    std::cerr << a;
    a *= 2;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(4, 3);
    std::cerr << a;
    auto b = 2 * a;
    std::cerr << b;
  }

  {
    auto a = increasingMatrix<float32>(4, 3);
    std::cerr << a;
    auto b = a * 2;
    std::cerr << b;
  }

  {
    auto a = increasingMatrix<float32>(4, 3);
    std::cerr << a;
    a *= 2;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    std::cerr << a;
    auto b = 2 * a;
    std::cerr << b;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    std::cerr << a;
    auto b = a * 2;
    std::cerr << b;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    std::cerr << a;
    a *= 2;
    std::cerr << a;
  }
}

void testAdd()
{
  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = 2 * increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    a += b;
    std::cerr << a;
  }
  
  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = 2 * increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    auto c = a + b;
    std::cerr << c;
  }

  {
    auto a = increasingMatrix<float32>(4, 3);
    auto b = 2 * increasingMatrix<float32>(4, 3);
    std::cerr << a << b;
    a += b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(4, 3);
    auto b = 2 * increasingMatrix<float32>(4, 3);
    std::cerr << a << b;
    auto c = a + b;
    std::cerr << c;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    auto b = 2 * increasingMatrix<float32>(3, 4);
    std::cerr << a << b;
    a += b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    auto b = 2 * increasingMatrix<float32>(3, 4);
    std::cerr << a << b;
    auto c = a + b;
    std::cerr << c;
  }
}

void testMinus()
{
  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = 2 * increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    a -= b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = 2 * increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    auto c = a - b;
    std::cerr << c;
  }

  {
    auto a = increasingMatrix<float32>(4, 3);
    auto b = 2 * increasingMatrix<float32>(4, 3);
    std::cerr << a << b;
    a -= b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(4, 3);
    auto b = 2 * increasingMatrix<float32>(4, 3);
    std::cerr << a << b;
    auto c = a - b;
    std::cerr << c;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    auto b = 2 * increasingMatrix<float32>(3, 4);
    std::cerr << a << b;
    a -= b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(3, 4);
    auto b = 2 * increasingMatrix<float32>(3, 4);
    std::cerr << a << b;
    auto c = a - b;
    std::cerr << c;
  }
}

void testMultiplication()
{
  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    a *= b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    auto c = a * b;
    std::cerr << c;
  }

  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = increasingMatrix<float32>(3, 1);
    std::cerr << a << b;
    a *= b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(3, 3);
    auto b = increasingMatrix<float32>(3, 1);
    std::cerr << a << b;
    auto c = a * b;
    std::cerr << c;
  }

  {
    auto a = increasingMatrix<float32>(1, 3);
    auto b = increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    a *= b;
    std::cerr << a;
  }

  {
    auto a = increasingMatrix<float32>(1, 3);
    auto b = increasingMatrix<float32>(3, 3);
    std::cerr << a << b;
    auto c = a * b;
    std::cerr << c;
  }


}

void testLUDecomposition()
{
  Matrix64 a(3, 3);
  a(0, 0) = 1.0; a(0, 1) = 1.0; a(0, 2) =   1.0;
  a(1, 0) = 4.0; a(1, 1) = 2.0; a(1, 2) =   1.0;
  a(2, 0) = 9.0; a(2, 1) = 3.0; a(2, 2) =   1.0;


  std::cerr << "A = " << a << "\n";
  LUDecomposition<float64> lu(a);
  lu.decompose();
  auto L = lu.getL();
  auto U = lu.getU();
  std::cerr << "L = " << L << "\n";
  std::cerr << "U = " << U << "\n";
  
  auto residualMatrix = L * U;
  std::cerr << "L*U =  " << residualMatrix << "\n";

  Matrix64 Id(3, 1);
  Id.setIdentity();
  auto aInv = lu.solve(Id);
  std::cerr << "A^-1 = " << aInv << "\n";
}

int main(int argc, char** argv)
{
  //testIdentity();
  //testZero();
  //testTranspose();
  //testScale();
  //testAdd();
  //testMinus();
  //testMultiplication();
  testLUDecomposition();
  return 1;
}