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

namespace GdCV
{
	namespace PointTransformations
	{
		ImageRGB8 negativeImage(const ImageRGB8& input)
		{
			ImageRGB8 result(input.width(), input.height());
			// Assignment 4

			for (int i = 0; i < input.nPixels(); i++) {
				result(i) = ui8vec3(255) - input(i);
			}
			return result;
		}

		ImageRGB8 gain(const ImageRGB8& input, const f32vec3& factor)
		{
			ImageRGB8 result(input.width(), input.height());
			// Assignment 4
			for (int i = 0; i < input.nPixels(); i++) {
				result(i) = sat(factor * (f32vec3)input(i));
			}
			return result;
		}

		ImageRGB8 bias(const ImageRGB8& input, const i32vec3& bias)
		{
			ImageRGB8 result(input.width(), input.height());
			// Assignment 4
			for (int i = 0; i < input.nPixels(); i++) {
				result(i) = sat(bias + (i32vec3)input(i));
			}
			return result;
		}

		ImageRGB8 toGrayScale(const ImageRGB8& input)
		{
			ImageRGB8 result(input.width(), input.height());
			// Assignment 4
			for (int i = 0; i < input.nPixels(); i++)
			{
				f32mat3 test(1.0 / 3, 1.0 / 3, 1.0 / 3, 1.0 / 3, 1.0 / 3, 1.0 / 3, 1.0 / 3, 1.0 / 3, 1.0 / 3);
				result(i) = (test * input(i));
			}
			return result;
		}


		ImageRGB8 blend(const ImageRGB8& a, const ImageRGB8& b, const float32 alpha)
		{
			const auto minWidth = std::min(a.width(), b.width());
			const auto minHeight = std::min(a.height(), b.height());
			ImageRGB8 result(minWidth, minHeight);
			// Assignment 4

			//for (int i = 0; i < result.nPixels(); i++) {
			for (int y = 0; y < result.height(); y++) {
				for (int x = 0; x < result.width(); x++) {
					result(x, y) = f32mat3(1.0 - alpha) * a(x, y) + f32mat3(alpha) * b(x, y);
				}
			}

		return result;
		}
	}
}