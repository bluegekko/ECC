#include <iostream>

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
    #ifdef build_encrypter
    //encrypter::runEncrypter(argc, argv);
    #endif // build_encrypter
    #ifdef build_series
    //series::runSeriesGenerator(argc, argv);
    #endif //build_series
    #ifdef build_decrypter
    decrypter::runDecrypter(argc, argv);
    #endif // build_decrypter
    return 0;
}
