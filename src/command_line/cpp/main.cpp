#include "unicode_string.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <string>

#include <bitset>

void out8(char value, std::string msg = "") {
    std::bitset<8> x(value);
    std::cout << x << " " << msg << std::endl;
}

void out32(uint32_t value, std::string msg = "") {
    std::bitset<32> x(value);
    std::cout << x << " " << msg << std::endl;
}

int main(int argc, char** argv) {
    using namespace echelon::unicode;

    if (argc < 2) {
        std::cout << "Please provide a file as input" << std::endl;
        return 0;
    }

    std::cout << "Ready to start" << std::endl;

    std::ifstream input(argv[1], std::ios_base::binary);

    input.seekg(0, std::ios_base::end);
    size_t length = input.tellg();
    input.seekg(0, std::ios_base::beg);

    std::vector<echelon::unicode::utf8_codePoint> buffer;
    buffer.reserve(length);
    std::copy(std::istreambuf_iterator<char>(input),
           std::istreambuf_iterator<char>(),
           std::back_inserter(buffer));

    auto unicodeString = new UnicodeString(buffer);

    #ifdef ECHELON_DEBUG
    std::cout << "is defined" << std::endl;
    #endif

    #ifdef ECHELON_DEBUG
    unicodeString->print();
    #endif
}
