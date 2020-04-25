#include <iostream>
#ifdef build_encrypter
#include "encrypter/Encrypter.h"
#endif // build_encrypter

#include "series/SeriesGenerator.h"


int main(int argc, char** argv)
{
    #ifdef build_encrypter
    encrypter::runEncrypter(argc, argv);
    #endif // build_encrypter
    series::runSeriesGenerator(argc, argv);
    return 0;
}
