#ifndef POLYNOM_H_INCLUDED
#define POLYNOM_H_INCLUDED

#include <regex>
#include "../common/PrimeField.h"

bool validateMonomString(std::string input)
{
    std::regex regexp("[0-9]+x[0-9]+y[0-9]");
    return std::regex_match(input, regexp);
}

class TwoVariableMonom
{
public:
    TwoVariableMonom(PrimeFieldValue coefficient, uint64_t xPower, uint64_t yPower)
        : coefficient(coefficient), xPower(xPower), yPower(yPower) {}
    TwoVariableMonom(std::shared_ptr<PrimeFieldValueFactory> primeFieldValueFactory, std::string input) : coefficient(primeFieldValueFactory->newValue(0))
    {
        size_t xPos = input.find("x");
        size_t yPos = input.find("y");
        std::string coefficientString = input.substr(0, xPos);
        std::string xPowerString = input.substr(xPos+1, yPos-xPos-1);
        std::string yPowerString = input.substr(yPos+1);
        coefficient = primeFieldValueFactory->newValue(convertStringToInt(coefficientString));
        xPower = convertStringToInt(xPowerString);
        yPower = convertStringToInt(yPowerString);
    }
    PrimeFieldValue calculate(const PrimeFieldValue x, const PrimeFieldValue y) const
    {
        return coefficient * x.pow(xPower) * y.pow(yPower);
    }
private:
    PrimeFieldValue coefficient;
    uint64_t xPower;
    uint64_t yPower;
};

class TwoVariablePolynom
{
public:
    void add(const TwoVariableMonom& monom)
    {
        monoms.push_back(monom);
    }
    PrimeFieldValue calculate(const PrimeFieldValue x, const PrimeFieldValue y) const
    {
        if (monoms.size() > 0)
        {
            PrimeFieldValue returnValue = monoms[0].calculate(x,y);
            for(size_t i = 1; i<monoms.size(); ++i)
            {
                returnValue = returnValue + monoms[i].calculate(x,y);
            }
            return returnValue;
        }
        // TODO exception?
    }
private:
    std::vector<TwoVariableMonom> monoms;
};

#endif // POLYNOM_H_INCLUDED
