#include "PointTransformations.h"
#include <glm/glm.hpp>
#include <algorithm>
namespace
{
/// <summary>
/// Converts an i32vec3 to an ui8vec3 making sure that overflow and underflow are properly clammed to 0 and 255, respectively. 
/// </summary>
ui8vec3 sat(const i32vec3& input)
{
  // Assignment 3
  return input;
}

/// <summary>
/// Converts and rounds an f32vec3 to an ui8vec3 making sure that overflow and underflow are properly clammed to 0 and 255, respectively. 
/// </summary>
ui8vec3 sat(const f32vec3& input)
{
  // Assignment 3
  return input;
}
}

namespace GdCV
{
namespace PointTransformations
{
  ImageRGB8 negativeImage(const ImageRGB8 & input)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignment 4
  return result;
}

ImageRGB8 gain(const ImageRGB8 & input, const f32vec3& factor)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignment 4
  return result;
}

ImageRGB8 bias(const ImageRGB8& input, const i32vec3& bias)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignment 4
  return result;
}

ImageRGB8 toGrayScale(const ImageRGB8& input)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignment 4
  return result;
}


ImageRGB8 blend(const ImageRGB8& a, const ImageRGB8& b, const float32 alpha)
{
  const auto minWidth = std::min(a.width(), b.width());
  const auto minHeight = std::min(a.height(), b.height());
  ImageRGB8 result(minWidth, minHeight);
  // Assignment 4
  return result;
}
}
}