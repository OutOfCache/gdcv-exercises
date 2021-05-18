#include "PolynomialCurveSegment.h"
#include <cogra/exceptions/RuntimeError.h>
namespace gmca
{
PolynomialCurveSegment::PolynomialCurveSegment()
{}

PolynomialCurveSegment::PolynomialCurveSegment(uint32 degree)
    : m_coefficients(degree+1)
{}

PolynomialCurveSegment::PolynomialCurveSegment(const std::vector<f32vec2>& coefficients)
    : m_coefficients(coefficients)
{
    if(getDegree() > maxDegree)
    {
        throw cogra::exceptions::RuntimeError("Degree is higher than allowed");
    }

    if(getDegree() < minDegree)
    {
        throw cogra::exceptions::RuntimeError("Degree is smaller than allowed");
    }
}

const f32vec2&  PolynomialCurveSegment::operator[](size_t i) const
{
    return m_coefficients[i];
}

f32vec2&  PolynomialCurveSegment::operator[](size_t i)
{
    return m_coefficients[i];
}

 const f32vec2 & PolynomialCurveSegment::getCoefficient(size_t i) const
{
    return m_coefficients[i];
}

 f32vec2 & PolynomialCurveSegment::getCoefficient(size_t i)
{
    return m_coefficients[i];
}

uint32 PolynomialCurveSegment::getDegree() const
{
    return static_cast<uint32>(m_coefficients.size()) - 1;
}

uint32 PolynomialCurveSegment::getOrder() const
{
    return static_cast<uint32>(m_coefficients.size());
}

const std::vector<f32vec2>& PolynomialCurveSegment::getCoefficients() const
{
    return m_coefficients;
}

std::vector<f32vec2>& PolynomialCurveSegment::getCoefficients()
{
    return m_coefficients;
}

std::vector<f32vec2> PolynomialCurveSegment::sample(const uint32 nSamplePoints) const
{
    std::vector<f32vec2> sampledPoints;    
    // Assignment 1b
    float delta_x = 1.0f / nSamplePoints;
    f32vec2 sample(0);

    for (int i = 0; i <= nSamplePoints; i++)
    {
        sample = evaluate(i * delta_x);
        sampledPoints.push_back(sample);
    }

    return sampledPoints;
}

}