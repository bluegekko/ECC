#ifndef SERIESPARAMETERS_H_INCLUDED
#define SERIESPARAMETERS_H_INCLUDED

#include "../common/EllipticCurve.h"
#include "../common/PrimeField.h"
#include "../common/InputSerializer.h"

namespace series
{

const size_t INPUT_NUMBER = 5;

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
    inputSerializer.initialize();
    std::vector<uint64_t> inputs;
    inputs.resize(INPUT_NUMBER);
    for(size_t i = 0; i<INPUT_NUMBER; ++i)
    {
        inputs[i] = inputSerializer.getNextNumber();
    }

    return SeriesParameters(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4]);
}


}

#endif // SERIESPARAMETERS_H_INCLUDED
