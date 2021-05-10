#define _USE_MATH_DEFINES
#include <cmath>
#include "Filter.h"

// #include <random>

namespace
{
    /// <summary>
    /// Converts an i32vec3 to an ui8vec3 making sure that overflow and underflow are properly clammed to 0 and 255, respectively. 
    /// </summary>
    ui8vec3 sat(const i32vec3& input)
    {
        // Assignment 3
        ui8vec3 output;
        output.x = std::max(std::min(input.x, 255), 0);
        output.y = std::max(std::min(input.y, 255), 0);
        output.z = std::max(std::min(input.z, 255), 0);

        return output;
    }

    /// <summary>
    /// Converts and rounds an f32vec3 to an ui8vec3 making sure that overflow and underflow are properly clammed to 0 and 255, respectively. 
    /// </summary>
    ui8vec3 sat(const f32vec3& input)
    {
        // Assignment 3
        ui8vec3 output;
        output.x = std::max(std::min((int)(input.x + 0.5), 255), 0);
        output.y = std::max(std::min((int)(input.y + 0.5), 255), 0);
        output.z = std::max(std::min((int)(input.z + 0.5), 255), 0);

        return output;
    }
}

namespace
{
/// <summary>
/// Returns the number of taps of a 1D Gaussian stencil in positive direction required for the provided sigma.
/// </summary>
int32 nPosTaps(float32 sigma)
{
  // Assignmet 6: 
  // Currently, we compute a box filter. 
  // Compute the right number of positive taps.
  // return 11;
  return (int)(2.5f * sigma);
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


  // std::normal_distribution<double> distribution(0.0f, sigma);
  float32 sum = 0;
  for(int32 i = tapMin; i <= tapMax; i++)
  {
    // weights(i - tapMin) = 1.0f / static_cast<float32>(nTaps);
    //   weights(i - tapMin) = distribution(i);
    weights(i - tapMin) = (1 / (sigma * std::sqrt(2 * M_PI))) * std::exp(-(i * i) / (2 * sigma * sigma));
    sum += weights(i - tapMin);
  }
  
  for (int i = 0; i < weights.nTaps(); i++)
  {
      weights(i) /= sum;
  }
  
  return weights;

}

Stencil2D tensorProduct(const Stencil1D& stencilX, const Stencil1D& stencilY)
{  
  Stencil2D result(stencilX.nTaps(), stencilY.nTaps());
  // Assignment 10: Compute the tensor product of the provided stencils.
  for (int x = 0; x < stencilX.nTaps(); x++)
  {
      for (int y = 0; y < stencilY.nTaps(); y++)
      {
          result(x, y) = stencilX(x) * stencilY(y);
      }
  }

  return result;
}

ImageRGB8 filter1D_X_Clamp(const ImageRGB8 & input, const Stencil1D& stencil)
{
  ImageRGB8 result(input.width(), input.height());

  const int stencil_center = (stencil.nTaps() -1) / 2;
  

  for (int y = 0; y < result.height(); y++) 
  {
      for (int x = 0; x < result.width(); x++)
      {
          f32vec3 filter_result(0);
          for (int i = 0; i < stencil.nTaps(); i++)
          {
              const auto current_x = std::max(std::min(x + stencil_center - i, (int)input.width() -1), 0);
              filter_result += f32vec3(input(current_x, y)) * f32vec3(stencil(i));
          }

          result(x, y) = sat(filter_result);
          
      }
  }
  // Assignment 7: Filter in x direction
  return result;
}

ImageRGB8 filter1D_Y_Clamp(const ImageRGB8 & input, const Stencil1D& stencil)
{
  ImageRGB8 result(input.width(), input.height());
  int stencil_center = (stencil.nTaps() -1) / 2;

  // Assignment 8: Filter in y direction
  for (int y = 0; y < result.height(); y++)
  {
      for (int x = 0; x < result.width(); x++)
      {
          f32vec3 filter_result(0);
          for (int i = 0; i < stencil.nTaps(); i++)
          {
              const auto current_y = std::max(std::min(y + stencil_center - i, (int)input.height() -1), 0);
              filter_result += f32vec3(input(x, current_y)) * f32vec3(stencil(i));
              
          }
          result(x, y) = sat(filter_result);
      }
  }
  return result;
}

ImageRGB8 filter2D_Sep_Clamp(const ImageRGB8 & input, const Stencil1D& stencil)
{
  // Assignment 9
  // Filter in x and y direction.
  ImageRGB8 result(input.width(), input.height());


  return filter1D_X_Clamp(filter1D_Y_Clamp(input, stencil), stencil);
}

ImageRGB8 filter2D_Clamp(const ImageRGB8 & input, const Stencil2D & stencil)
{
  ImageRGB8 result(input.width(), input.height());
  // Assignemt 10
  // Apply a 2D mask on a 2D image.
  int stencil_center_x = (stencil.nTapsX() -1) / 2;
  int stencil_center_y = (stencil.nTapsY() -1) / 2;

  // Assignment 8: Filter in y direction
  for (int y = 0; y < result.height(); y++)
  {
      for (int x = 0; x < result.width(); x++)
      {
          f32vec3 filter_result(0);
          for (int i = 0; i < stencil.nTapsX(); i++)
          {
              const auto current_x = std::max(std::min(x - stencil_center_x + i, (int)input.width() -1), 0);
              for (int j = 0; j < stencil.nTapsY(); j++)
              {
                  const auto current_y = std::max(std::min(y - stencil_center_y + j, (int)input.height() -1), 0);

                  filter_result += f32vec3(input(current_x, current_y)) * f32vec3(stencil(i, j));
              }
          }
          result(x, y) = sat(filter_result);
      }
  }
  return result;
}
}
}