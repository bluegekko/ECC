#ifndef SERIESPARAMETERS_H_INCLUDED
#define SERIESPARAMETERS_H_INCLUDED

#include "../common/EllipticCurve.h"
#include "../common/PrimeField.h"
#include "../common/InputSerializer.h"

namespace series
{

struct SeriesParameters
{
    SeriesParameters(uint64_t prime, uint64_t pointX, uint64_t pointY, uint64_t curveA, uint64_t curveB) :
        prime(prime), primeFieldValueFactory(std::make_shared<PrimeFieldValueFactory>(prime)), generator(primeFieldValueFactory->newValue(pointX), primeFieldValueFactory->newValue(pointY)), curve(primeFieldValueFactory->newValue(curveA), primeFieldValueFactory->newValue(curveB), primeFieldValueFactory) {}

    uint64_t prime;;
    std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory;
    EllipticCurvePoint generator;
    EllipticCurve curve;
};

SeriesParameters readInput(const std::string& fileName)
{
    InputSerializer inputSerializer(fileName);
    inputSerializer.initializeMap();
    uint64_t prime = inputSerializer.getNumberForKey("#prime");
    std::pair<uint64_t,uint64_t> pointCoordinates = inputSerializer.getNumberPairForKey("#point-in-ECC-field-g");
    std::pair<uint64_t,uint64_t> curveParams = inputSerializer.getNumberPairForKey("#ECC-A-B");
    return SeriesParameters(prime, pointCoordinates.first, pointCoordinates.second,
                               curveParams.first, curveParams.second);
}


}

#endif // SERIESPARAMETERS_H_INCLUDED
