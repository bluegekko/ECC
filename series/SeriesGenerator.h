#ifndef SERIESGENERATOR_H_INCLUDED
#define SERIESGENERATOR_H_INCLUDED

#include "../common/EllipticCurve.h"
#include "SeriesInput.h"

namespace series
{

const size_t SERIES_SIZE = 100;

class SeriesGenerator
{
public:
    SeriesGenerator(uint64_t prime, const EllipticCurvePoint& generator,const EllipticCurve& curve) :
        prime(prime), generator(generator), curve(curve) {}
    std::vector<int> generateSimple();
private:
    uint64_t prime;
    EllipticCurvePoint generator;
    EllipticCurve curve;
};

PrimeFieldValue generalizingFunction(EllipticCurvePoint point)
{
    return point.first;
}

std::vector<int> SeriesGenerator::generateSimple()
{
    std::vector<int> returnSeries;
    returnSeries.resize(SERIES_SIZE);
    EllipticCurvePoint currentPoint = curve.multiply(generator, 0);
    for(size_t counter = 1; counter<= SERIES_SIZE; ++counter)
    {
        currentPoint = curve.add(currentPoint, generator);
        uint64_t r = generalizingFunction(currentPoint).getValue();
        returnSeries[counter-1] = (r > (prime - 1)/2) ? -1 : 1;
    }
    return returnSeries;
}

void runSeriesGenerator(std::string inputFileName, std::string outputFileName)
{
    SeriesParameters params = readInput(inputFileName);
    SeriesGenerator seriesGenerator(params.prime, params.generator, params.curve);
    auto series = seriesGenerator.generateSimple();
    std::ofstream outStream(outputFileName);
    for (auto it = series.begin(); it != series.end(); ++it)
    {
        std::cout << *it << " ";
        outStream << *it << " ";
    }
    std::cout << std::endl;
}

} // namespace series

#endif // SERIESGENERATOR_H_INCLUDED
