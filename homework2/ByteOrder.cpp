#include "Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
    uint32_t x = 0x01020304;

    if (htonl(x) == x) {
        std::cout << "Big-endian" << '\n';
    }
    else {
        std::cout << "Little-endian" << '\n';
    }
}