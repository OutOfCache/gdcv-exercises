#include "SimpleGeometricTransforms.h"
#include <algorithm>
namespace GdCV
{

ImageRGB8 SimpleGeometricTransforms::flip(const ImageRGB8 & input)
{
  // Assignment 2
  // ImageRGB8 result(1, 1);
    ImageRGB8 result(input);
    
    for (int y = 0; y < result.height(); y++)
    {
        for (int x = 0; x < result.width(); x++)
        {
            result(x, y) = input(x, input.height() - y - 1);
        }
    }
  return result;
}

ImageRGB8 SimpleGeometricTransforms::flop(const ImageRGB8 & input)
{
  // Assignment 2
  // ImageRGB8 result(1, 1);
    ImageRGB8 result(input.width(), input.height());

    for (int y = 0; y < result.height(); y++)
    {
        for (int x = 0; x < result.width(); x++)
        {
            result(x, y) = input(input.width() - x -1, y);
        }
    }
  return result;
}

ImageRGB8 SimpleGeometricTransforms::flipflop(const ImageRGB8 & input)
{
  // Assignment 2
  // ImageRGB8 result = flop(flip(input));
    ImageRGB8 result(input.width(), input.height());

    for (int y = 0; y < result.height(); y++) {
        for (int x = 0; x < result.width(); x++) {
            result(x, y) = input(input.width() - x - 1, input.height() - y - 1);
        }
    }
  return result;
}

ImageRGB8 SimpleGeometricTransforms::rotate90DegreesClockwise(const ImageRGB8 & input)
{
  // Assignment 2
  ImageRGB8 result(input.height(), input.width());

  for (int y = 0; y < result.height(); y++) {
      for (int x = 0; x < result.width(); x++) {
          result(x, y) = input(y, input.width() - x - 1);
      }
  }
  return result;
}

ImageRGB8 SimpleGeometricTransforms::rotate90DegreesAntiClockwise(const ImageRGB8 & input)
{
  // Assignment 2
    ImageRGB8 result(input.height(), input.width());

    for (int y = 0; y < result.height(); y++) {
        for (int x = 0; x < result.width(); x++) {
            result(x, y) = input(y, x);
        }
    }
    return result;
}

ImageRGB8 SimpleGeometricTransforms::rotate180Degrees(const ImageRGB8 & input)
{
  return flipflop(input);
}

ImageRGB8 SimpleGeometricTransforms::crop(const ImageRGB8 & input, 
                                          ui32vec2 & upperLeft, 
                                          ui32vec2 & lowerRight)
{
  // Assignment 2
  int cropWidth = lowerRight.x - upperLeft.x;
  int cropHeight = lowerRight.y - upperLeft.y;
  ImageRGB8 result(cropWidth, cropHeight);
  

  for (int y = 0; y < cropHeight; y++) {
      for (int x = 0; x < cropWidth; x++) {
          result(x, y) = input(x + upperLeft.x, y + upperLeft.y);
      }
  }
  return result;

}

ImageRGB8 SimpleGeometricTransforms::upsample(const ImageRGB8 & input, const uint32 factor)
{
  // Assignment 2
  ImageRGB8 result(input.width() * factor, input.height() * factor);

  for (int y = 0; y < result.height(); y++) {
      for (int x = 0; x < result.width(); x++) {
          result(x, y) = input(x / factor, y / factor);
      }
  }
  return result;
}

ImageRGB8 SimpleGeometricTransforms::downsample(const ImageRGB8 & input, const uint32 factor)
{
  // Assignment 2
  ImageRGB8 result(input.width() / factor, input.height() / factor);

  for (int y = 0; y < result.height(); y++) {
      for (int x = 0; x < result.width(); x++) {
          result(x, y) = input(x * factor, y * factor);
      }
  }
  return result;
}


}