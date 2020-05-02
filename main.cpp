#include <iostream>

// The corresponding macros should be given as build parameters for each module to be run.

#ifdef build_encrypter
#include "encrypter/Encrypter.h"
#endif // build_encrypter

#ifdef build_series
#include "series/SeriesGenerator.h"
#endif // build_series

#ifdef build_decrypter
#include "decrypter/Decrypter.h"
#endif // build_decrypter

int main(int argc, char** argv)
{
    InputSerializer mainConfig("ecc.conf");
    mainConfig.initializeMap();
    #ifdef build_encrypter
    encrypter::runEncrypter(mainConfig.getStringForKey("#encrypter-input"), mainConfig.getStringForKey("#encrypter-output"));
    #endif // build_encrypter
    #ifdef build_series
    series::runSeriesGenerator(mainConfig.getStringForKey("#series-input"), mainConfig.getStringForKey("#series-output"));
    #endif //build_series
    #ifdef build_decrypter
    decrypter::runDecrypter(mainConfig.getStringForKey("#decrypter-input"), mainConfig.getStringForKey("#decrypter-output"));
    #endif // build_decrypter
    return 0;
}
