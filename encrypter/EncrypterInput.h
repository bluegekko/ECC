#ifndef PROGRAMINPUT_H_INCLUDED
#define PROGRAMINPUT_H_INCLUDED

#include <vector>
#include "../common/InputSerializer.h"

const size_t INPUT_NUMBER = 6;

struct EncrypterParameters
{
    EncrypterParameters(uint64_t prime, uint64_t pointX, uint64_t pointY, uint64_t a, uint64_t curveA, uint64_t curveB) :
        prime(prime), primeFieldValueFactory(std::make_shared<PrimeFieldValueFactory>(prime)),
        g(primeFieldValueFactory->newValue(pointX), primeFieldValueFactory->newValue(pointY)),
        a(a), curve(primeFieldValueFactory->newValue(curveA), primeFieldValueFactory->newValue(curveB), primeFieldValueFactory) {}
    uint64_t prime;
    std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory;
    EllipticCurvePoint g;
    uint64_t a;
    EllipticCurve curve;
};

EncrypterParameters readInput(const std::string fileName)
{
    InputSerializer inputSerializer(fileName);
    inputSerializer.initialize();
    std::vector<uint64_t> inputs;
    inputs.resize(INPUT_NUMBER);
    for(size_t i = 0; i<INPUT_NUMBER; ++i)
    {
        inputs[i] = inputSerializer.getNextNumber();
    }

    return EncrypterParameters(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5]);

}


#endif // PROGRAMINPUT_H_INCLUDED
