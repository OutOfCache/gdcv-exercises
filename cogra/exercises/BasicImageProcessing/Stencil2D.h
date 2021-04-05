#pragma once
#include <cogra/types.h>
#include <vector>
using namespace cogra;
namespace   GdCV
{
/// <summary>
/// A class that represents 2D stencils.
/// </summary>
class Stencil2D
{
public:
  /// <summary>
  /// Creates an empty 2D stencil withn nTapsx in x direction and nTapsY in y direction.
  /// </summary>
  Stencil2D(size_t nTapsX, size_t nTapsY)
    : m_weights(nTapsX * nTapsY)
    , m_nTapsX(nTapsX)
    , m_nTapsY(nTapsY)

  { }


  /// <summary>
  /// Returns the value of the (i-th,j-th) tap (zero-based indices) for reading.
  /// </summary>
  const float32 operator()(uint32 i, uint32 j) const
  {
    return m_weights[j * m_nTapsX + i];
  }

  /// <summary>
  /// Returns the value of the (i-th,j-th) tap (zero-based indices) for writing.
  /// </summary>
  float32& operator()(uint32 i, uint32 j)
  {
    return m_weights[j * m_nTapsX + i];
  }

  /// <summary>
  /// Returns the number of taps in x direction.
  /// </summary>
  size_t nTapsX() const
  {
    return m_nTapsX;
  }

  /// <summary>
  /// Returns the number taps in y direction.
  /// </summary>
  size_t nTapsY() const
  {
    return m_nTapsY;
  }
private:
  std::vector<float32> m_weights;
  size_t m_nTapsX;
  size_t m_nTapsY;
};
}
