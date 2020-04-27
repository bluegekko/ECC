#ifndef DECRYPTER_H_INCLUDED
#define DECRYPTER_H_INCLUDED

#include "../common/EllipticCurve.h"
#include "../encrypter/EncrypterInput.h"
#include <map>


namespace decrypter
{

void runDecrypter(int argc, char** argv)
{
    std::string inputFileName = argc > 1 ? argv[1] : "inputA.in"; // TODO change
    std::string outputFileName = argc > 2 ? argv[2] : "outputA.out";

    encrypter::EncrypterParameters decrypterParameters = encrypter::readInput(inputFileName);

    // TODO primetest on encrypterParameters.prime
    // TODO check that g is on the curve

    std::map<EllipticCurvePoint, uint64_t> forwardList;
    std::map<EllipticCurvePoint, uint64_t> backwardList;

    EllipticCurve curve = decrypterParameters.curve;
    EllipticCurvePoint base = decrypterParameters.g;
    EllipticCurvePoint key = curve.multiply(base,decrypterParameters.a);

    EllipticCurvePoint runningValue = curve.getIdealPoint();
    auto forwardListIterator = forwardList.end();
    auto backwardListIterator = backwardList.end();

    //EllipticCurvePoint temp = curve.add(base, base);
    //temp = curve.add(base, temp);

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
