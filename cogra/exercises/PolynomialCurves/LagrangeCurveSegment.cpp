
#include "LagrangeCurveSegment.h"
#include "MonomialCurveSegment.h"
#include "BezierCurveSegment.h"
#include <cogra/exceptions/RuntimeError.h>
#include <cogra/eigen.h>
namespace gmca
{
LagrangeCurveSegment::LagrangeCurveSegment(const std::vector<f32vec2>& coefficients)
    : PolynomialCurveSegment(coefficients)
{}

LagrangeCurveSegment::LagrangeCurveSegment(uint32 degree)
    : PolynomialCurveSegment(degree)
{}
f32vec2 LagrangeCurveSegment::evaluate(const float t) const
{
    f32vec2 result(0);
    // Assignment 1c
    float n = getDegree();
    for (int i = getDegree(); i >= 0; i--)
    {
        // Lagrange coefficient
        float lagrange_i = 1.0f;
        for (int j = 0; j <= getDegree(); j++)
        {
            if (j != i) 
            {
                // lagrange_i *= (t - j/n) / ((i - j)/n);
                lagrange_i *= (n * t - j) / (i - j);
            }
        }
        result += lagrange_i * getCoefficient(i);
    }
    return result;
}

void LagrangeCurveSegment::elevateDegree()
{
    if(getDegree() + 1 > maxDegree)
    {
        throw cogra::exceptions::RuntimeError("Degree is higher than allowed");
    }
    // Assignment 1f
}

void LagrangeCurveSegment::reduceDegree()
{
    // Assignment 3c
}

std::unique_ptr<PolynomialCurveSegment> LagrangeCurveSegment::toMonomialCurveSegment() const
{    
    // Assignemt 1e
    return std::make_unique<MonomialCurveSegment>(getCoefficients());
}

std::unique_ptr<PolynomialCurveSegment> LagrangeCurveSegment::toLagrangeCurveSegment() const
{
    return std::make_unique<LagrangeCurveSegment>(getCoefficients());
}
 
std::unique_ptr<PolynomialCurveSegment> LagrangeCurveSegment::toBezierCurveSegment() const
 {
    // Assignment 2c
    return std::make_unique<BezierCurveSegment>(getCoefficients());
 }

Eigen::MatrixXf LagrangeCurveSegment::lagrangeBasisFunctionsToMonomialBasisfunctions(uint32 degree)
{
    Eigen::MatrixXf v(degree + 1, degree + 1);
    // Assignment 1e
    return v;
}
}