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
    f32vec2 new_coeff(0, 0);

    getCoefficients().push_back(new_coeff);
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
    std::vector<f32vec2> coefficients;
    const float n = getDegree();
    for (int i = 0; i <= getDegree(); i++) {
        coefficients.push_back(evaluate(i / n));
    }
    return std::make_unique<LagrangeCurveSegment>(coefficients);
}

std::unique_ptr<PolynomialCurveSegment> MonomialCurveSegment::toBezierCurveSegment() const
{
    // Assignemt 2b

    
    auto coeff = std::make_unique<BezierCurveSegment>(getDegree());

    Eigen::MatrixXf m = monomialBasisFunctionsToBezierBasisFunctions(getDegree()).inverse().transpose();

    Eigen::VectorXf x(getDegree() + 1);
    Eigen::VectorXf y(getDegree() + 1);

    for (int i = 0; i < getDegree() + 1; i++) {
        x(i) = getCoefficient(i).x;
        y(i) = getCoefficient(i).y;
    }

    x = m * x;
    y = m * y;

    for (int i = 0; i < getDegree() + 1; i++) {
        coeff->getCoefficient(i) = f32vec2(x(i), y(i));
    }
    
    return coeff;
    
}

Eigen::MatrixXf MonomialCurveSegment::monomialBasisFunctionsToBezierBasisFunctions(uint32 degree)
{
    Eigen::MatrixXf m = Eigen::MatrixXf::Identity(degree + 1, degree + 1);
    // Assignment 2b 

    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            float binom = i> j ? 0.0f : BezierCurveSegment::binomial(j, i);
            
            // avoiding pow
            int sign = (j - i) % 2 == 0 ? 1 : -1;

           m(i, j) = sign * BezierCurveSegment::binomial(degree, j) * binom;
        }

    }


    return m;
}
}