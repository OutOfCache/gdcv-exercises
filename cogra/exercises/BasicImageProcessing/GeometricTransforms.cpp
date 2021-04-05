#include "GeometricTransforms.h"
#include "Image.h"
namespace GdCV
{
namespace GeometricTransforms
{

ImageRGB8 applyTransform(const ImageRGB8 & input, const f32mat3 & transformation)
{
  // Assignment 5
  ImageRGB8 result(1, 1);
  return result;
}

ImageRGB8 rotateAroundCenter(const ImageRGB8 & input, const float32 angleInDegrees)
{
  // Assignment 6
  f32mat3 A(1.0f);
  return applyTransform(input, A);
}
}
}