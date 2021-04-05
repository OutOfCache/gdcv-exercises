#pragma once
#include <cogra/types.h>
#include <vector>
using namespace cogra;
namespace   GdCV
{
namespace Filter
{
/// <summary>
/// A class that represents a 1D Stencil.
/// </summary>
class Stencil1D
{
public:
  /// <summary>
  /// Creates a stencil with the provided number of taps
  /// </summary>
  Stencil1D(size_t nTaps)
    : m_weights(nTaps)
  {

  }

  /// <summary>
  /// Returns the value of the i-th tap (zero-based index) for reading.
  /// </summary>
  const float32 operator()(uint32 i) const
  {
    return m_weights[i];
  }

  /// <summary>
  /// Returns the value of the i-th tap (zero-based index) for writing.
  /// </summary>
  float32& operator()(uint32 i)
  {
    return m_weights[i];
  }

  /// <summary>
  /// Returns the number of taps.
  /// </summary>
  size_t nTaps() const
  {
    return m_weights.size();
  }
private:
  std::vector<float32> m_weights;
};
}
}