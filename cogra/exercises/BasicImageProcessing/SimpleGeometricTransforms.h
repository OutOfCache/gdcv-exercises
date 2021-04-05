#pragma once
#include "Image.h"
namespace GdCV
{
namespace SimpleGeometricTransforms
{
/// <summary>
/// Reflects the image along its horizontal central axis.
/// </summary>
ImageRGB8 flip(const ImageRGB8& input);

/// <summary>
/// Reflects the image along its vertical central axis.
/// </summary>
ImageRGB8 flop(const ImageRGB8& input);

/// <summary>
/// Flips and flops the image.
/// </summary>
ImageRGB8 flipflop(const ImageRGB8& input);

/// <summary>
/// Rotates the image by 90 degrees in clockwise direction.
/// </summary>
ImageRGB8 rotate90DegreesClockwise(const ImageRGB8& input);

/// <summary>
/// Rotates the image by 90 degrees in anti-clockwise direction.
/// </summary>
ImageRGB8 rotate90DegreesAntiClockwise(const ImageRGB8& input);

/// <summary>
/// Rotates the image by 180 degrees.
/// </summary>
ImageRGB8 rotate180Degrees(const ImageRGB8& input);

/// <summary>
/// Returns the region enclosed by the rectangle (upperLeft and lower Right) of the input image as a new image.
/// </summary>
/// <param name="upperLeft">Upper-left point of the rectangular region that we wish to crop. x component is the "left" and y component is the upper part of the coordinate.</param>
/// /// <param name="upperLeft">Lower-right point of the rectangular region that we wish to crop. x component is the right and y component is the lower part of the coordinate.</param>
ImageRGB8 crop(const ImageRGB8& input, ui32vec2& upperLeft, ui32vec2& lowerRight);

/// <summary>
/// Returns a larger image scaled by the provided factor.
/// </summary>
ImageRGB8 upsample(const ImageRGB8& input, const uint32 factor);

/// <summary>
/// Returns an smaller version of the image scaled by the provided factor.
/// </summary>
ImageRGB8 downsample(const ImageRGB8& input, const uint32 factor);
}
}