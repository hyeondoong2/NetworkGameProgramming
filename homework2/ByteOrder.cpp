#include "Common.h"
#include <iostream>

bool is_big_endian() {
    uint32_t x = 0x01020304;
    return (htonl(x) == x);
}

int main(int argc, char* argv[])
{
    if (is_big_endian()) {
        std::cout << "Big-endian" << '\n';
    }
    else {
        std::cout << "Little-endian" << '\n';
    }
}