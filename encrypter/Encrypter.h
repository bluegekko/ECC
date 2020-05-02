#ifndef ENCRYPTER_H_INCLUDED
#define ENCRYPTER_H_INCLUDED

#include "../common/PrimeField.h"
#include "../common/EllipticCurve.h"
#include "EncrypterInput.h"

namespace encrypter
{


void runEncrypter(std::string inputFileName, std::string outputFileName)
{
    EncrypterParameters encrypterParameters = readInput(inputFileName);

    // TODO primetest on encrypterParameters.prime
    // TODO check that g is on the curve

    EllipticCurve curve = encrypterParameters.curve;
    EllipticCurvePoint input = encrypterParameters.g;
    EllipticCurvePoint output = curve.multiply(input,encrypterParameters.a);
    std::cout << output.first.getValue() << " " << output.second.getValue() << std::endl;
    std::ofstream outStream(outputFileName);
    outStream << "#prime " <<  encrypterParameters.prime << std::endl;
    outStream << "#point-in-ECC-field-g " << encrypterParameters.g.first.getValue() << " " << encrypterParameters.g.second.getValue() << std::endl;
    outStream << "#point-in-ECC-field-key " << output.first.getValue() << " " << output.second.getValue() << std::endl;
    outStream << "#ECC-A-B " << curve.getA().getValue() << " " << curve.getB().getValue();
}


} // namespace encrypter

#endif // ENCRYPTER_H_INCLUDED
