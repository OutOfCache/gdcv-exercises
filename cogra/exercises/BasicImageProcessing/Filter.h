#pragma once
#include "Image.h"
#include "Stencil1D.h"
#include "Stencil2D.h"

#include <vector>
namespace GdCV
{
namespace Filter
{
/// <summary>
/// Returns the stencil of a Gaussian Filter.
/// </summary>
Stencil1D gaussianStencil(const float32 sigma);

/// <summary>
/// Computes the tensor product of two stencils.
/// </summary>
Stencil2D tensorProduct(const Stencil1D& stencilX, const Stencil1D& stencilY);

/// <summary>
/// Filters the input image in x direction with the provided stencil.
/// At the boundary, pixels are clamped.
/// </summary>
ImageRGB8 filter1D_X_Clamp(const ImageRGB8& input, const Stencil1D& stencil);

/// <summary>
/// Filters the input image in y direction with the provided stencil.
/// At the boundary, pixels are clamped.
/// </summary>
ImageRGB8 filter1D_Y_Clamp(const ImageRGB8& input, const Stencil1D& stencil);

/// <summary>
/// Filters the input image in x and y direction with the provided stencil in both directions.
/// At the boundary, pixels are clamped.
/// </summary>
ImageRGB8 filter2D_Sep_Clamp(const ImageRGB8& input, const Stencil1D& stencil);


/// <summary>
/// Filters the input image in with the provided stencil.
/// At the boundary, pixels are clamped.
/// </summary>
ImageRGB8 filter2D_Clamp(const ImageRGB8& input, const Stencil2D& stencil);


}
}