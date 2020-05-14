#ifndef SERIESPARAMETERS_H_INCLUDED
#define SERIESPARAMETERS_H_INCLUDED

#include "../common/EllipticCurve.h"
#include "../common/PrimeField.h"
#include "../common/InputSerializer.h"
#include "Polynom.h"

namespace series
{

enum class Construction
{
    SIMPLE,
    LEGENDRE,
    NONE
};

struct SeriesParameters
{
    SeriesParameters(uint64_t prime, std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory,
                     uint64_t pointX, uint64_t pointY, uint64_t curveA, uint64_t curveB,
                     Construction construction, TwoVariablePolynom polynom, uint64_t acLimit) :
        prime(prime), primeFieldValueFactory(primeFieldValueFactory),
         generator(primeFieldValueFactory->newValue(pointX), primeFieldValueFactory->newValue(pointY)),
         curve(primeFieldValueFactory->newValue(curveA), primeFieldValueFactory->newValue(curveB), primeFieldValueFactory),
         construction(construction), polynom(polynom), acLimit(acLimit){}


    uint64_t prime;
    std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory;
    EllipticCurvePoint generator;
    EllipticCurve curve;
    bool validate() const;
    Construction construction;
    TwoVariablePolynom polynom;
    uint64_t acLimit;
};

Construction getConstructionFromString(std::string value)
{
    if (value == "simple")
    {
        return Construction::SIMPLE;
    }
    else if (value == "legendre")
    {
        return Construction::LEGENDRE;
    }
    return Construction::NONE;
}

SeriesParameters readInput(const std::string& fileName)
{
    InputSerializer inputSerializer(fileName);
    inputSerializer.initializeMap();
    uint64_t prime = inputSerializer.getNumberForKey("#prime");
    std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory = std::make_shared<PrimeFieldValueFactory>(prime);
    std::pair<uint64_t,uint64_t> pointCoordinates = inputSerializer.getNumberPairForKey("#point-in-ECC-field-g");
    std::pair<uint64_t,uint64_t> curveParams = inputSerializer.getNumberPairForKey("#ECC-A-B");
    Construction construction = getConstructionFromString(inputSerializer.getStringForKey("#construction"));
    std::vector<std::string> monoms = inputSerializer.getStringVectorForKey("#polynom");
    TwoVariablePolynom polynom;
    for(auto monom : monoms)
    {
        if (!validateMonomString(monom))
        {
            std::cout << "monom is not valid in #polynom parameter: " << monom << "!" << std::endl;
        }
        polynom.add(TwoVariableMonom(primeFieldValueFactory, monom));
    }
    uint64_t autoCorrelationLimit = inputSerializer.getNumberForKey("#autocorrelation-limit");
    return SeriesParameters(prime, primeFieldValueFactory, pointCoordinates.first, pointCoordinates.second,
                               curveParams.first, curveParams.second, construction, polynom, autoCorrelationLimit);
}

bool SeriesParameters::validate() const
{
    if (!curve.isOnCurve(generator))
    {
        std::cout << "g is not on curve!" << std::endl;
        return false;
    }

    if (construction == Construction::NONE)
    {
        std::cout << "not supported construction type!" << std::endl;
        return false;
    }
    return true;
}

} // namespace series

#endif // SERIESPARAMETERS_H_INCLUDED
