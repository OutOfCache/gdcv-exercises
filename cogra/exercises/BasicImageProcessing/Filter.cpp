#include "Filter.h"
namespace
{
/// <summary>
/// Returns the number of taps of a 1D Gaussian stencnil in positive direction required for the provided sigma.
/// </summary>
int32 nPosTaps(float32 sigma)
{
  // Assignmet 6: 
  // Currently, we compute a box filter. 
  // Compute the right number of positive taps.
  return 11;
}
}

namespace GdCV
{
namespace Filter
{

/// <summary>
/// Computes and returns Gaussian stencil from the provided stencil.
/// </summary>
Stencil1D gaussianStencil(const float32 sigma)
{
  const auto tapMax = nPosTaps(sigma);
  const auto tapMin = -tapMax;
  const auto nTaps = tapMax - tapMin + 1;
  Stencil1D weights(nTaps);

  // Assignment 12:
  // Currently, we compute a box filter. 
  // Change to Gaussian.

  for(int32 i = tapMin; i <= tapMax; i++)
  {
    weights(i - tapMin) = 1.0f / static_cast<float32>(nTaps);
  }
  return weights;

}

Stencil2D tensorProduct(const Stencil1D& stencilX, const Stencil1D& stencilY)
{  
  Stencil2D result(stencilX.nTaps(), stencilY.nTaps());
  // Assignment 10: Compute the tensor product of the provided stencils.
  return result;
}

ImageRGB8 filter1D_X_Clamp(const ImageRGB8 & input, const Stencil1D& stencil)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignment 7: Filter in x direction
  return result;
}

ImageRGB8 filter1D_Y_Clamp(const ImageRGB8 & input, const Stencil1D& stencil)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignment 8: Filter in y direction
  return result;
}

ImageRGB8 filter2D_Sep_Clamp(const ImageRGB8 & input, const Stencil1D& stencil)
{
  // Assignment 9
  // Filter in x and y direction.
  ImageRGB8 result(input.width(), input.height());
  return result;
}

ImageRGB8 filter2D_Clamp(const ImageRGB8 & input, const Stencil2D & stencil)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignemt 10
  // Apply a 2D mask on a 2D image.
  return result;
}
}
}