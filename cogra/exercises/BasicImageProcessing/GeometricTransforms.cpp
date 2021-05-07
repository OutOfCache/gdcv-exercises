#define _USE_MATH_DEFINES
#include <cmath>
#include "GeometricTransforms.h"
#include "Image.h"

// #include <numbers>



//#include <math.h>

namespace GdCV
{
namespace GeometricTransforms
{

ImageRGB8 applyTransform(const ImageRGB8 & input, const f32mat3 & transformation)
{
  // Assignment 5
  ImageRGB8 result(input.width(), input.height());

  for (int y = 0; y < result.height(); y++) {
	  for (int x = 0; x < result.width(); x++) {
		  f32vec3 transformed = transformation * f32vec3(x, y, 1);

		  if (transformed.x >= 0 && transformed.x < result.width() && transformed.y >= 0 && transformed.y < result.height()) {
			  result(x, y) = input((int)transformed.x, (int)transformed.y);
		  }
		  else {
			  result(x, y) = ui8vec3(0, 0, 0);
		  }
		  
	  }
  }

  return result;
}

ImageRGB8 rotateAroundCenter(const ImageRGB8 & input, const float32 angleInDegrees)
{
  // Assignment 6

	float32 angleInRadians = M_PI * angleInDegrees / 180.0f;
	f32mat3 T0 = f32mat3(1, 0, 0,
		                 0, 1, 0,
		                 -1 * int(input.width() / 2), -1 * int(input.height() / 2), 1);
	f32mat3 R0 = glm::transpose(f32mat3(cos(angleInRadians), -sin(angleInRadians), 0,
			sin(angleInRadians), cos(angleInRadians), 0,
			0, 0, 1));
	
	f32mat3 T1 = glm::transpose(f32mat3(1, 0, (input.width()/2),
						0, 1, (input.height()/2 ),
						0, 0, 1));
  return applyTransform(input, T1 * R0 * T0);
}
}
}