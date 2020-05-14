#ifndef SERIESGENERATOR_H_INCLUDED
#define SERIESGENERATOR_H_INCLUDED

#include "../common/EllipticCurve.h"
#include "SeriesInput.h"
#include "CalculateLegendre.h"
#include "MultiIndex.h"

namespace series
{

const size_t SERIES_SIZE = 20;

class SeriesGenerator
{
public:
    SeriesGenerator(uint64_t prime, const EllipticCurvePoint& generator, const EllipticCurve& curve,
                     const TwoVariablePolynom& polynom, uint64_t seriesSize) :
        prime(prime), generator(generator), curve(curve), polynom(polynom), seriesSize(seriesSize){}
    std::vector<int> generateSimple();
    std::vector<int> generateLegendre();
    uint64_t calculateWellDistribution(std::vector<int>& series);
    uint64_t calculateAutoCorrelation(std::vector<int>& series, uint64_t l);
private:
    uint64_t prime;
    EllipticCurvePoint generator;
    EllipticCurve curve;
    TwoVariablePolynom polynom;
    uint64_t seriesSize;
};

std::vector<int> SeriesGenerator::generateSimple()
{
    std::vector<int> returnSeries;
    returnSeries.resize(seriesSize);
    EllipticCurvePoint currentPoint = curve.multiply(generator, 0);
    for(size_t counter = 1; counter<= seriesSize; ++counter)
    {
        currentPoint = curve.add(currentPoint, generator);
        uint64_t r = polynom.calculate(currentPoint.first, currentPoint.second).getValue();
        returnSeries[counter-1] = (r > (prime - 1)/2) ? -1 : 1;
    }
    return returnSeries;
}

std::vector<int> SeriesGenerator::generateLegendre()
{
    std::vector<int> returnSeries;
    returnSeries.resize(seriesSize);
    EllipticCurvePoint currentPoint = curve.multiply(generator, 0);
    for(size_t counter = 1; counter<= seriesSize; ++counter)
    {
        currentPoint = curve.add(currentPoint, generator);
        uint64_t r = polynom.calculate(currentPoint.first, currentPoint.second).getValue();
        returnSeries[counter-1] = (calculateLegendre(prime, r) == 1) ? 1 : -1;
    }
    return returnSeries;
}

uint64_t SeriesGenerator::calculateWellDistribution(std::vector<int>& series)
{
    size_t N = series.size();
    uint64_t well_distribution = 0;
    for (size_t a = 1; a<=N; ++a)
    {
        for (size_t b = 1; b<=N-a; ++b)
        {
            for (size_t t = 1; (a + (t-1)*b)<=N; ++t)
            {
                int sum = 0;
                for (size_t j = 0; j<=(t-1); ++j)
                {
                    sum+= series[(a+j*b)-1];
                }
                sum = sum>0 ? sum : - sum;
                if (well_distribution < sum)
                {
                    well_distribution = sum;
                }
            }
        }
    }
    return well_distribution;
}

uint64_t SeriesGenerator::calculateAutoCorrelation(std::vector<int>& series, uint64_t l)
{
    size_t N = series.size();
    uint64_t autoCorrelelation = 0;
    for(size_t M=1; M<=N-l+1; ++M)
    {
        MultiIndex multiIndex(N-M,l);
        size_t counter = 0;

        while(multiIndex.isValid())
        {
            int sum = 0;
            for (size_t n=1; n<=M; ++n)
            {
                sum+= calculateMultiplicationAtIndex(series, multiIndex, n);
            }
            sum = sum>0 ? sum : - sum;
            if (autoCorrelelation < sum)
            {
                autoCorrelelation = sum;
            }
            multiIndex.increment();
            counter++;
        }

    }
    return autoCorrelelation;
}


void runSeriesGenerator(std::string inputFileName, std::string outputFileName)
{
    SeriesParameters params = readInput(inputFileName);
    params.validate();
    SeriesGenerator seriesGenerator(params.prime, params.generator, params.curve, params.polynom, params.seriesSize);
    std::vector<int> series;
    if (params.construction == Construction::SIMPLE)
    {
        series = seriesGenerator.generateSimple();
    }
    else if (params.construction == Construction::LEGENDRE)
    {
        series = seriesGenerator.generateLegendre();
    }
    std::ofstream outStream(outputFileName);
    outStream << "#series ";
    for (auto it = series.begin(); it != series.end(); ++it)
    {
        std::cout << *it << " ";
        outStream << *it << " ";
    }
    std::cout << std::endl;
    outStream << std::endl;
    std::cout << seriesGenerator.calculateWellDistribution(series) << std::endl;
    outStream << "#well-distribution " << seriesGenerator.calculateWellDistribution(series) << std::endl;
    outStream << "#autocorrelation ";
    for (uint64_t l = 2; l <= params.acLimit; ++l)
    {
        std::cout << seriesGenerator.calculateAutoCorrelation(series, l) << " ";
        outStream << seriesGenerator.calculateAutoCorrelation(series, l) << " ";
    }
    std::cout << std::endl;
    outStream << std::endl;
}

} // namespace series

#endif // SERIESGENERATOR_H_INCLUDED
