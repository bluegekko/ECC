#ifndef PRIMEFIELD_H_INCLUDED
#define PRIMEFIELD_H_INCLUDED

#include <cstdint>

class PrimeFieldValueFactory;

class PrimeFieldValue
{
public:
    PrimeFieldValue operator+(const PrimeFieldValue& other) const;
    PrimeFieldValue operator-(const PrimeFieldValue& other) const;
    PrimeFieldValue operator*(const PrimeFieldValue& other) const;
    PrimeFieldValue operator/(const PrimeFieldValue& other) const;

    PrimeFieldValue operator*(uint64_t other) const;
    PrimeFieldValue pow(uint64_t other) const;

    bool operator==(const PrimeFieldValue& other) const;
    bool operator<(const PrimeFieldValue& other) const;

    uint64_t getValue() {return value;}
private:
    PrimeFieldValue(uint64_t prime, uint64_t value) :prime(prime), value(value%prime) {}
    uint64_t prime;
    uint64_t value;
    friend class PrimeFieldValueFactory;
};

class PrimeFieldValueFactory {
public:
    PrimeFieldValueFactory(uint64_t prime) : prime(prime) {}
    PrimeFieldValue newValue(uint64_t value) {PrimeFieldValue primeFieldValue(prime, value); return primeFieldValue;}
private:
    uint64_t prime;
};


#endif // PRIMEFIELD_H_INCLUDED
