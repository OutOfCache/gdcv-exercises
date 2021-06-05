
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

    getCoefficients() = sample(getDegree() + 1);
}

void LagrangeCurveSegment::reduceDegree()
{
    // Assignment 3c
}

std::unique_ptr<PolynomialCurveSegment> LagrangeCurveSegment::toMonomialCurveSegment() const
{    
    // Assignemt 1e


    Eigen::VectorXf x(getDegree() + 1);
    Eigen::VectorXf y(getDegree() + 1);

    for (int i = 0; i < getDegree() + 1; i++) {
        x(i) = getCoefficient(i).x;
        y(i) = getCoefficient(i).y;
    }

    Eigen::MatrixXf v = lagrangeBasisFunctionsToMonomialBasisfunctions(getDegree()).inverse();

    x = v * x;
    y = v * y;


    auto result = std::make_unique<MonomialCurveSegment>(getDegree());


    for (int i = 0; i < getDegree() + 1; i++) {
        result->getCoefficient(i) = f32vec2(x[i], y[i]);
    }

    return result;
}

std::unique_ptr<PolynomialCurveSegment> LagrangeCurveSegment::toLagrangeCurveSegment() const
{
    return std::make_unique<LagrangeCurveSegment>(getCoefficients());
}
 
std::unique_ptr<PolynomialCurveSegment> LagrangeCurveSegment::toBezierCurveSegment() const
 {
    // Assignment 2c
    auto result = std::make_unique<BezierCurveSegment>(getDegree());

    Eigen::MatrixXf m = MonomialCurveSegment::monomialBasisFunctionsToBezierBasisFunctions(getDegree()).transpose().inverse();
    Eigen::MatrixXf v = LagrangeCurveSegment::lagrangeBasisFunctionsToMonomialBasisfunctions(getDegree()).inverse();

    Eigen::VectorXf x(getDegree() + 1);
    Eigen::VectorXf y(getDegree() + 1);

    for (int i = 0; i < getDegree() + 1; i++) {
        x(i) = getCoefficient(i).x;
        y(i) = getCoefficient(i).y;
    }

    x = m * v * x;
    y = m * v * y;

    for (int i = 0; i < getDegree() + 1; i++) {
        result->getCoefficient(i) = f32vec2(x(i), y(i));
    }

    return result;
 }

Eigen::MatrixXf LagrangeCurveSegment::lagrangeBasisFunctionsToMonomialBasisfunctions(uint32 degree)
{
    Eigen::MatrixXf v(degree + 1, degree + 1);
    // Assignment 1e

    for (int i = 0; i < v.rows(); i++) {
        for (int j = 0; j < v.cols(); j++) {
            v(i, j) = pow((double)i / degree, j);
        }
    }

    return v;
}
}