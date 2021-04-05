#include "SimpleGeometricTransforms.h"
#include "PointTransformations.h"
#include "Filter.h"
#include "GeometricTransforms.h"
#include <cogra/tools/Timer.h>
#include <iostream>

using namespace GdCV;
using namespace cogra;

void testSimpleGeometricTransformations()
{
  GdCV::ImageRGB8 inputImage("../data/Pirate.png");

  const auto flip = SimpleGeometricTransforms::flip(inputImage);
  flip.saveAsPNG("../flip.png");

  const auto flop = SimpleGeometricTransforms::flop(inputImage);
  flop.saveAsPNG("../flop.png");

  const auto flipflop = SimpleGeometricTransforms::flipflop(inputImage);
  flipflop.saveAsPNG("../flipflop.png");

  const auto rotate90Clockwise = SimpleGeometricTransforms::rotate90DegreesClockwise(inputImage);
  rotate90Clockwise.saveAsPNG("../rotate90Clockwise.png");

  const auto rotate90AntiClockwise = SimpleGeometricTransforms::rotate90DegreesAntiClockwise(inputImage);
  rotate90AntiClockwise.saveAsPNG("../rotate90AntiClockwise.png");

  const auto crop = SimpleGeometricTransforms::crop(inputImage, ui32vec2(10, 20), ui32vec2(100, 90));
  crop.saveAsPNG("../crop.png");

  const auto upsample = SimpleGeometricTransforms::upsample(inputImage, 3);
  upsample.saveAsPNG("../upsample.png");

  const auto downsample = SimpleGeometricTransforms::downsample(inputImage, 7);
  downsample.saveAsPNG("../downsample.png");
}

void testPointTransformations()
{
  GdCV::ImageRGB8 inputImageA("../data/Peppers.png");
  const auto negative = GdCV::PointTransformations::negativeImage(inputImageA);
  negative.saveAsPNG("../negative.png");
  const auto darker = GdCV::PointTransformations::gain(inputImageA, f32vec3(0.5f, 0.2f, 0.1f));
  darker.saveAsPNG("../darker.png");
  const auto brighter = GdCV::PointTransformations::gain(inputImageA, f32vec3(1.5f, 1.2f, 1.1f));
  brighter.saveAsPNG("../brighter.png");
  const auto sepia = GdCV::PointTransformations::bias(inputImageA, i32vec3(128, 64, 0));
  sepia.saveAsPNG("../sepia.png");
  const auto grayScale = GdCV::PointTransformations::toGrayScale(inputImageA);
  grayScale.saveAsPNG("../grayScale.png");

  GdCV::ImageRGB8 inputImageB("../data/Barbara.png");
  const auto blend25P = GdCV::PointTransformations::blend(inputImageA, inputImageB, 0.25f);
  blend25P.saveAsPNG("../blend25p.png");
  const auto blend50P = GdCV::PointTransformations::blend(inputImageA, inputImageB, 0.50f);
  blend50P.saveAsPNG("../blend50p.png");
  const auto blend75P = GdCV::PointTransformations::blend(inputImageA, inputImageB, 0.75f);
  blend75P.saveAsPNG("../blend75p.png");
}

void testGeometricTransformations()
{
  GdCV::ImageRGB8 inputImageA("../data/Barbara.png");
  const auto rotateP30 = GdCV::GeometricTransforms::rotateAroundCenter(inputImageA, 30);
  rotateP30.saveAsPNG("../RotateP30.png");

  const auto rotateM30 = GdCV::GeometricTransforms::rotateAroundCenter(inputImageA, -30);
  rotateM30.saveAsPNG("../RotateM30.png");
}

void testFilter()
{
  const auto stencil = GdCV::Filter::gaussianStencil(8.0f);
  const auto stencil2D = GdCV::Filter::tensorProduct(stencil, stencil);
  GdCV::ImageRGB8 inputImageA("../data/Mandril.png");

  cogra::Timer timer;
  {
    timer.start();
    auto filterX = GdCV::Filter::filter1D_X_Clamp(inputImageA, stencil);
    const auto timeFilterX = timer.getTimeInMilliseconds();
    filterX.saveAsPNG("../filterX.png");
    std::cerr << "FilterX:\t" << timeFilterX << "ms\n";
  }
  {
    timer.start();
    auto filterY = GdCV::Filter::filter1D_Y_Clamp(inputImageA, stencil);
    const auto timeFilterY = timer.getTimeInMilliseconds();
    filterY.saveAsPNG("../filterY.png");
    std::cerr << "FilterY:\t" << timeFilterY << "ms\n";
  }
  {
    timer.start();
    auto filterXYSep = GdCV::Filter::filter2D_Sep_Clamp(inputImageA, stencil);
    const auto timeFilterXYSep = timer.getTimeInMilliseconds();
    filterXYSep.saveAsPNG("../filterXYSep.png");
    std::cerr << "FilterXYSep:\t" << timeFilterXYSep << "ms\n";
  }
  {
    timer.start();
    auto filterXY = GdCV::Filter::filter2D_Clamp(inputImageA, stencil2D);
    const auto timeFilterXY = timer.getTimeInMilliseconds();
    filterXY.saveAsPNG("../filterXY.png");
    std::cerr << "FilterXY:\t" << timeFilterXY << "ms\n";
  }
}

int main()
{
  testSimpleGeometricTransformations();

  // Uncomment the following lines as you proceed with the Lab.
  // testPointTransformations();
  // testGeometricTransformations();
  // testFilter();
  return 0;
}