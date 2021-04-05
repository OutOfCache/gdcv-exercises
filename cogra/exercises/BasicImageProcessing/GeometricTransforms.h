#pragma once
#include "Image.h"
namespace GdCV
{
namespace GeometricTransforms
{

/// <summary>
/// Transforms an image by a homogenous mapping.
/// 
/// For output pixel that transformation maps to a single input pixel. 
/// If the input pixel coordinates are out of bounds, the output pixel is [0,0,0].
/// </summary>
ImageRGB8 applyTransform(const ImageRGB8& input, const f32mat3& transformation);

/// <summary>
/// Rotates an input image counter-clockwise around the image center by the provided amout of angles (in degrees).
/// 
/// For output pixel that transformation maps to a single input pixel. 
/// If the input pixel coordinates are out of bounds, the output pixel is [0,0,0].
/// </summary>
ImageRGB8 rotateAroundCenter(const ImageRGB8& input, const float32 angleInDegrees);

}
}
