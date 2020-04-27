#include "PrimeField.h"



PrimeFieldValue PrimeFieldValue::operator+(const PrimeFieldValue& other) const
{
    PrimeFieldValue primeFieldValue(prime, this->value + other.value);
    return primeFieldValue;
}

PrimeFieldValue PrimeFieldValue::operator*(const PrimeFieldValue& other) const
{
    PrimeFieldValue primeFieldValue(prime, this->value * other.value);
    return primeFieldValue;
}

PrimeFieldValue PrimeFieldValue::operator-(const PrimeFieldValue& other) const
{
    uint64_t returnValue = this->value > other.value ? this->value - other.value : this->value + prime - other.value;
    PrimeFieldValue primeFieldValue(prime, returnValue);
    return primeFieldValue;
}

PrimeFieldValue PrimeFieldValue::operator/(const PrimeFieldValue& other) const
{
    return (*this)*(other.pow(prime-2));
}


PrimeFieldValue PrimeFieldValue::operator*(uint64_t other) const
{
    PrimeFieldValue primeFieldValue(prime, value*other);
    return primeFieldValue;
}

PrimeFieldValue PrimeFieldValue::pow(uint64_t other) const
{
    PrimeFieldValue returnValue(prime, 1);
    PrimeFieldValue rollingValue(*this);
    while(other > 0)
    {
       if (other % 2 == 1)
       {
           returnValue = returnValue * rollingValue;
       }
       rollingValue = rollingValue*rollingValue;
       other = other >> 1;
    }
    return returnValue;
}

bool PrimeFieldValue::operator==(const PrimeFieldValue& other) const
{
    return value == other.value;
}

bool PrimeFieldValue::operator!=(const PrimeFieldValue& other) const
{
    return value != other.value;
}

bool PrimeFieldValue::operator<(const PrimeFieldValue& other) const
{
    return value < other.value;
}
