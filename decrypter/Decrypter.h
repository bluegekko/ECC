#ifndef DECRYPTER_H_INCLUDED
#define DECRYPTER_H_INCLUDED

#include "../common/EllipticCurve.h"
#include "DecrypterInput.h"
#include <map>


namespace decrypter
{

void runDecrypter(int argc, char** argv)
{
    std::string inputFileName = argc > 1 ? argv[1] : "outputA.out"; // TODO change
    std::string outputFileName = argc > 2 ? argv[2] : "outputB.out";

    DecrypterParamaters decrypterParameters = readInput(inputFileName);

    // TODO primetest on encrypterParameters.prime
    // TODO check that g is on the curve

    std::map<EllipticCurvePoint, uint64_t> forwardList;
    std::map<EllipticCurvePoint, uint64_t> backwardList;

    EllipticCurve curve = decrypterParameters.curve;
    EllipticCurvePoint base = decrypterParameters.g;
    EllipticCurvePoint key = decrypterParameters.key;

    EllipticCurvePoint runningValue = curve.getIdealPoint();
    auto forwardListIterator = forwardList.end();
    auto backwardListIterator = backwardList.end();


    uint64_t m = 1;
    for (; m<decrypterParameters.prime*decrypterParameters.prime; ++m)
    {
        runningValue = curve.add(runningValue, base);
        EllipticCurvePoint reverseValue = curve.subtract(key,runningValue);
        forwardList[runningValue] = m;
        backwardList[reverseValue] = m;
        forwardListIterator = forwardList.find(reverseValue);
        backwardListIterator = backwardList.find(runningValue);
        if (forwardListIterator != forwardList.end() || backwardListIterator != backwardList.end())
        {
            break;
        }

    }
    uint64_t a = forwardListIterator != forwardList.end() ? m + forwardListIterator->second : m + backwardListIterator->second;


    std::cout << a << std::endl;
    std::cout << (key.first.getValue()) << " " << (key.second.getValue()) << std::endl;
    std::cout << curve.multiply(base, a).first.getValue() << " " << curve.multiply(base,a).second.getValue() << std::endl;
   /* std::ofstream outStream(outputFileName);
    outStream << "#prime: " <<  encrypterParameters.prime << std::endl;
    outStream << "#point-in-ECC-field-g: " << encrypterParameters.g.first.getValue() << " " << encrypterParameters.g.second.getValue() << std::endl;
    outStream << "#point-in-ECC-field-g*a: " << output.first.getValue() << " " << output.second.getValue() << std::endl;
    outStream << "#ECC-A-B: " << curve.getA().getValue() << " " << curve.getB().getValue();*/
}

} // namespace decrypter

#endif // DECRYPTER_H_INCLUDED
