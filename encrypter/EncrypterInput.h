#ifndef PROGRAMINPUT_H_INCLUDED
#define PROGRAMINPUT_H_INCLUDED

#include <vector>
#include "../common/InputSerializer.h"

namespace encrypter
{

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
    inputSerializer.initializeMap();
    uint64_t prime = inputSerializer.getNumberForKey("#prime");
    std::pair<uint64_t,uint64_t> pointCoordinates = inputSerializer.getNumberPairForKey("#point-in-ECC-field-g");
    uint64_t multiplicant = inputSerializer.getNumberForKey("#number-to-multiply-a");
    std::pair<uint64_t,uint64_t> curveParams = inputSerializer.getNumberPairForKey("#ECC-A-B");
    return EncrypterParameters(prime, pointCoordinates.first, pointCoordinates.second, multiplicant,
                               curveParams.first, curveParams.second);

}

} // namespace encypter

#endif // PROGRAMINPUT_H_INCLUDED
