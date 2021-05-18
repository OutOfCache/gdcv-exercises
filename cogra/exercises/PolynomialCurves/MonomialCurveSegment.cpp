#include "MonomialCurveSegment.h"
#include "LagrangeCurveSegment.h"
#include "BezierCurveSegment.h"
#include <cogra/eigen.h>
namespace gmca
{
MonomialCurveSegment::MonomialCurveSegment(uint32 degree)
    : PolynomialCurveSegment(degree)
{}
MonomialCurveSegment::MonomialCurveSegment(const std::vector<f32vec2>& coefficients)
    : PolynomialCurveSegment(coefficients)
{}

f32vec2 MonomialCurveSegment::evaluate(const float t) const
{
    f32vec2 result(getCoefficient(getDegree()));

    // Assignment 1a
    for (int i = getDegree() - 1; i >= 0; i--)
    {
        result = result * t + getCoefficient(i);
    }
    return result;
}

void MonomialCurveSegment::elevateDegree()
{    
    // Assignment 1f
}

void MonomialCurveSegment::reduceDegree()
{    
    // Assignment 3c
}

std::unique_ptr<PolynomialCurveSegment> MonomialCurveSegment::toMonomialCurveSegment() const
{
    return std::make_unique<MonomialCurveSegment>(getCoefficients());
}

std::unique_ptr<PolynomialCurveSegment> MonomialCurveSegment::toLagrangeCurveSegment() const
{
    // Assignment 1d
    return std::make_unique<LagrangeCurveSegment>(getCoefficients());
}

std::unique_ptr<PolynomialCurveSegment> MonomialCurveSegment::toBezierCurveSegment() const
{
    // Assignemt 2b
    return std::make_unique<BezierCurveSegment>(getCoefficients());
}

Eigen::MatrixXf MonomialCurveSegment::monomialBasisFunctionsToBezierBasisFunctions(uint32 degree)
{
    Eigen::MatrixXf m = Eigen::MatrixXf::Identity(degree + 1, degree + 1);
    // Assignment 2b    
    return m;
}
}