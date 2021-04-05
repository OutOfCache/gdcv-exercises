#pragma once
#include "Image.h"

namespace GdCV
{
namespace PointTransformations
{

/// <summary>
/// Computes the negative image.
/// </summary>
ImageRGB8 negativeImage(const ImageRGB8& input);

/// <summary>
/// Scales each channel by respective factor provided "factor"
/// </summary>
ImageRGB8 gain(const ImageRGB8& input, const f32vec3& factor);


/// <summary>
/// Adds a constant term "bias" to each pixel.
/// </summary>
ImageRGB8 bias(const ImageRGB8& input, const i32vec3& bias);

/// <summary>
/// Converts a color image to a gray scale image and stores the gray-scale intensity in all three channels of the output image.
/// </summary>
ImageRGB8 toGrayScale(const ImageRGB8& input);

/// <summary>
/// Blends between two images, thereby alpha = 0 returns a, alpha = 1 returns b. 
/// Anything between returns a linearly interpolated averaged image.
/// The dimensions of the result image are the minimum width and height of the input images a and b.
/// </summary>
ImageRGB8 blend(const ImageRGB8& a, const ImageRGB8& b, const float32 alpha);



}
}