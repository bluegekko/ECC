#ifndef ENCRYPTER_H_INCLUDED
#define ENCRYPTER_H_INCLUDED

#include "PrimeField.h"
#include "EllipticCurve.h"
#include "EncrypterInput.h"

void runEncrypter(int argc, char** argv)
{
    std::string inputFileName = argc > 1 ? argv[1] : "inputA.in";
    std::string outputFileName = argc > 2 ? argv[2] : "outputA.out";

    EncrypterParameters encrypterParameters = readInput(inputFileName);

    // TODO primetest on encrypterParameters.prime
    // TODO check that g is on the curve

    EllipticCurve curve = encrypterParameters.curve;
    EllipticCurvePoint input = encrypterParameters.g;
    EllipticCurvePoint output = curve.multiply(input,encrypterParameters.a);
    std::cout << output.first.getValue() << " " << output.second.getValue();
    std::ofstream outStream(outputFileName);
    outStream << "#prime: " <<  encrypterParameters.prime << std::endl;
    outStream << "#point-in-ECC-field-g: " << encrypterParameters.g.first.getValue() << " " << encrypterParameters.g.second.getValue() << std::endl;
    outStream << "#point-in-ECC-field-g*a: " << output.first.getValue() << " " << output.second.getValue() << std::endl;
    outStream << "#ECC-A-B: " << curve.getA().getValue() << " " << curve.getB().getValue();
}

#endif // ENCRYPTER_H_INCLUDED
