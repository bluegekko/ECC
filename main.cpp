#include <iostream>
#ifdef build_encrypter
#include "encrypter/Encrypter.h"
#endif // build_encrypter


int main(int argc, char** argv)
{
    #ifdef build_encrypter
    runEncrypter(argc, argv);
    #endif // build_encrypter
    return 0;
}
