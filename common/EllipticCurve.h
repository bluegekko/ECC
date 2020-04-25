#ifndef ELLIPTICCURVE_H_INCLUDED
#define ELLIPTICCURVE_H_INCLUDED

#include "PrimeField.h"
#include "memory"

// 0,0 is the ideal point O
typedef std::pair<PrimeFieldValue,PrimeFieldValue> EllipticCurvePoint;

class EllipticCurve
{
public:
    EllipticCurve(PrimeFieldValue A, PrimeFieldValue B, std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory)
        :primeFieldValueFactory(primeFieldValueFactory), A(A), B(B), zero(primeFieldValueFactory->newValue(0)), idealPoint(zero, zero) {}
    EllipticCurvePoint doublePoint(const EllipticCurvePoint& point) const;
    EllipticCurvePoint add(const EllipticCurvePoint& pointFirst, const EllipticCurvePoint& pointSecond) const;
    EllipticCurvePoint multiply(const EllipticCurvePoint& point, uint64_t m) const;
    PrimeFieldValue getA() const {return A;}
    PrimeFieldValue getB() const {return B;}
private:
    std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory;
    PrimeFieldValue A;
    PrimeFieldValue B;
    PrimeFieldValue zero;
    EllipticCurvePoint idealPoint;
};

EllipticCurvePoint EllipticCurve::doublePoint(const EllipticCurvePoint& point) const
{
    if (point.second == zero)
    {
        return EllipticCurvePoint(zero, zero);
    }
    PrimeFieldValue lambda = (point.first*point.first*3 + A)/(point.second*2);
    PrimeFieldValue x = lambda*lambda - point.first*2;
    PrimeFieldValue y = lambda*(point.first - x) - point.second;
    return EllipticCurvePoint(x,y);
}

EllipticCurvePoint EllipticCurve::add(const EllipticCurvePoint& pointP, const EllipticCurvePoint& pointQ) const
{
    if(pointP == idealPoint)
    {
        return pointQ;
    }

    if(pointQ == idealPoint)
    {
        return pointP;
    }

    if (pointP == pointQ)
    {
        return doublePoint(pointP);
    }

    if (pointP.second == pointQ.second)
    {
        return EllipticCurvePoint(zero, zero);
    }

    PrimeFieldValue lambda = (pointP.second - pointQ.second)/(pointP.first - pointQ.first);
    PrimeFieldValue x = lambda*lambda - pointP.first - pointQ.first;
    PrimeFieldValue y = lambda*(pointP.first - x) - pointP.second;
    return EllipticCurvePoint(x,y);
}

EllipticCurvePoint EllipticCurve::multiply(const EllipticCurvePoint& point, uint64_t m) const
{
    EllipticCurvePoint returnValue = EllipticCurvePoint(zero, zero);
    EllipticCurvePoint rollingValue(point);
    while(m > 0)
    {
       if (m % 2 == 1)
       {
           returnValue = add(returnValue, rollingValue);
       }
       rollingValue = doublePoint(rollingValue);
       m = m >> 1;
    }
    return returnValue;

}

#endif // ELLIPTICCURVE_H_INCLUDED