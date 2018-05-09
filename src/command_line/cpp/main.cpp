#include "unicode_string.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <string>

#include <bitset>

namespace echelon { namespace unicode {
    typedef char utf8_codePoint;
    typedef uint32_t utf32_codePoint;

    namespace utf_8 {
        enum ByteNumber : unsigned char {
            FirstofOneByteSequence = 0x80,
            ContinuationByteSequence = 0x80,
            FirstOfTwoByteSequence = 0xC0,
            FirstOfThreeByteSequence = 0xE0,
            FirstOfFourByteSequence = 0xF0,
        };
    }
}}

void out8(char value, std::string msg = "") {
    std::bitset<8> x(value);
    std::cout << x << " " << msg << std::endl;
}

void out32(uint32_t value, std::string msg = "") {
    std::bitset<32> x(value);
    std::cout << x << " " << msg << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Please provide a file as input" << std::endl;
        return 0;
    }

    std::ifstream input(argv[1], std::ios_base::binary);

    input.seekg(0, std::ios_base::end);
    size_t length = input.tellg();
    input.seekg(0, std::ios_base::beg);

    std::vector<echelon::unicode::utf8_codePoint> buffer;
    buffer.reserve(length);
    std::copy(std::istreambuf_iterator<char>(input),
           std::istreambuf_iterator<char>(),
           std::back_inserter(buffer));

    std::vector<echelon::unicode::utf32_codePoint> newBuffer;
    newBuffer.reserve(length);

    for (auto b = buffer.begin(); b < buffer.end(); b++) {
        using namespace echelon::unicode;
        using namespace echelon::unicode::utf_8;

        if ((*b & FirstOfFourByteSequence) == FirstOfFourByteSequence) {
            utf8_codePoint v = *b & ~FirstOfFourByteSequence;
            utf32_codePoint value = v << 18;
            b++;

            int i;
            for (i = 1; i < 4 && b < buffer.end(); i++, b++) {
                if (*b & ContinuationByteSequence != ContinuationByteSequence) {
                    throw std::domain_error("Invalid 4 byte sequence");
                }

                utf8_codePoint v = (*b & ~ContinuationByteSequence);
                char shift = (3 - i) * 6;

                value += v << shift;
            }

            b--;

            if (i != 4) {
                throw std::domain_error("Invalid 4 byte sequence");
            }

            newBuffer.push_back(value);
        }
        else if ((*b & FirstOfThreeByteSequence) == FirstOfThreeByteSequence) {
            utf8_codePoint v = *b & ~FirstOfThreeByteSequence;
            utf32_codePoint value = v << 12;
            b++;

            int i;
            for (i = 1; i < 3 && b < buffer.end(); i++, b++) {
                if (*b & ContinuationByteSequence != ContinuationByteSequence) {
                    throw std::domain_error("Invalid 3 byte sequence");
                }

                utf8_codePoint v = *b & ~ContinuationByteSequence;
                char shift = (2 - i) * 6;

                value += v << shift;
            }

            b--;

            if (i != 3) {
                throw std::domain_error("Invalid 3 byte sequence");
            }

            newBuffer.push_back(value);
        }
        else if ((*b & FirstOfTwoByteSequence) == FirstOfTwoByteSequence) {
            utf8_codePoint v = *b & ~FirstOfTwoByteSequence;
            utf32_codePoint value = v << 6;
            b++;

            if (b < buffer.end() && (*b & ContinuationByteSequence) == ContinuationByteSequence) {
                utf8_codePoint v = *b & ~ContinuationByteSequence;
                value += v;
            }
            else {
                throw std::domain_error("Invalid 2 byte sequence");
            }

            newBuffer.push_back(value);
        }
        else if ((*b & FirstofOneByteSequence) == 0x0) {
            newBuffer.push_back(*b);
        }
        else {
            throw std::domain_error("Invalid byte sequence");
        }
    }

    for (auto x : newBuffer) {
        std::cout << x << std::endl;
    }

    auto unicodeString = new UnicodeString();
    unicodeString->test();
}
