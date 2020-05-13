#ifndef CALCULATELEGENDRE_H_INCLUDED
#define CALCULATELEGENDRE_H_INCLUDED

#include <vector>
#include <bits/stdc++.h>

namespace series
{

std::vector<uint64_t> primeFactors(uint64_t n);

int calculateLegendre(uint64_t prime, uint64_t input)
{
    int value = 1;
    if (input % prime == 0)
    {
        return 0;
    }
    if (input == 1)
    {
        return 1;
    }
    if (input == 2)
    {
        if (prime % 8 == 1 || prime % 8 == 7)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    // TODO Could remove factors by pair.
    std::vector<uint64_t> factors = primeFactors(input);
    if(factors.size() > 1)
    {
        for(uint64_t factor: factors)
        {
            value*= calculateLegendre(prime, factor);
        }
        return value;
    }
    else
    {
        if (input % 4 == 3 && prime % 4 == 3)
        {
            value = -1*value;
        }
        return value*calculateLegendre(input, prime%input);
    }
}

std::vector<uint64_t> primeFactors(uint64_t n)
{
    // Print the number of 2s that divide n
    std::vector<uint64_t> factors;
    while (n % 2 == 0)
    {
        factors.push_back(2);
        n = n/2;
    }

    // n must be odd at this point. So we can skip
    // one element (Note i = i +2)
    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        // While i divides n, print i and divide n
        while (n % i == 0)
        {
            factors.push_back(i);
            n = n/i;
        }
    }

    // This condition is to handle the case when n
    // is a prime number greater than 2
    if (n > 2)
    {
        factors.push_back(n);
    }
    return factors;
}

} // namespace series

#endif // CALCULATELEGENDRE_H_INCLUDED
