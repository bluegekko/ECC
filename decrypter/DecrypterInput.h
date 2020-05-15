#ifndef DECRYPTERINPUT_H_INCLUDED
#define DECRYPTERINPUT_H_INCLUDED


#include <vector>
#include "../common/InputSerializer.h"

namespace decrypter
{

struct DecrypterParamaters
{
    DecrypterParamaters(uint64_t prime, uint64_t pointX, uint64_t pointY, uint64_t keyPointX, uint64_t keyPointY, uint64_t curveA, uint64_t curveB) :
        prime(prime), primeFieldValueFactory(std::make_shared<PrimeFieldValueFactory>(prime)),
        g(primeFieldValueFactory->newValue(pointX), primeFieldValueFactory->newValue(pointY)),
        key(primeFieldValueFactory->newValue(keyPointX), primeFieldValueFactory->newValue(keyPointY)),
         curve(primeFieldValueFactory->newValue(curveA), primeFieldValueFactory->newValue(curveB), primeFieldValueFactory) {}
    uint64_t prime;
    std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory;
    EllipticCurvePoint g;
    EllipticCurvePoint key;
    EllipticCurve curve;
    bool validate() const;
};

DecrypterParamaters readInput(const std::string fileName)
{
    InputSerializer inputSerializer(fileName);
    inputSerializer.initializeMap();
    uint64_t prime = inputSerializer.getNumberForKey("#prime");
    std::pair<uint64_t,uint64_t> pointCoordinates = inputSerializer.getNumberPairForKey("#point-in-ECC-field-g");
    std::pair<uint64_t,uint64_t> keyPoint = inputSerializer.getNumberPairForKey("#point-in-ECC-field-key");
    std::pair<uint64_t,uint64_t> curveParams = inputSerializer.getNumberPairForKey("#ECC-A-B");
    return DecrypterParamaters(prime, pointCoordinates.first, pointCoordinates.second, keyPoint.first, keyPoint.second,
                                curveParams.first, curveParams.second);

}

bool DecrypterParamaters::validate() const
{
    if (!curve.isOnCurve(g))
    {
        std::cout << "g is not on the curve!" << std::endl;
        return false;
    }
    if (!curve.isOnCurve(key))
    {
        std::cout << "key is not on the curve!" << std::endl;
        return false;
    }

    return true;
}

} // decrypter


#endif // DECRYPTERINPUT_H_INCLUDED
