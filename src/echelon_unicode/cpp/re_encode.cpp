#include "re_encode.hpp"

#include <stdexcept>

#include "utf_constants.hpp"

namespace echelon { namespace unicode { namespace encoding {

using namespace echelon::unicode::utf_8;

std::vector<echelon::unicode::utf32_codePoint> re_encode(std::vector<echelon::unicode::utf8_codePoint> input) {
    std::vector<utf32_codePoint> result;
    result.reserve(input.size());

    for (auto b = input.begin(); b < input.end(); b++) {
        if ((*b & FirstOfFourByteSequence) == FirstOfFourByteSequence) {
            utf8_codePoint v = *b & ~FirstOfFourByteSequence;
            utf32_codePoint value = v << 18;
            b++;

            int i;
            for (i = 1; i < 4 && b < input.end(); i++, b++) {
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

            result.push_back(value);
        }
        else if ((*b & FirstOfThreeByteSequence) == FirstOfThreeByteSequence) {
            utf8_codePoint v = *b & ~FirstOfThreeByteSequence;
            utf32_codePoint value = v << 12;
            b++;

            int i;
            for (i = 1; i < 3 && b < input.end(); i++, b++) {
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

            result.push_back(value);
        }
        else if ((*b & FirstOfTwoByteSequence) == FirstOfTwoByteSequence) {
            utf8_codePoint v = *b & ~FirstOfTwoByteSequence;
            utf32_codePoint value = v << 6;
            b++;

            if (b < input.end() && (*b & ContinuationByteSequence) == ContinuationByteSequence) {
                utf8_codePoint v = *b & ~ContinuationByteSequence;
                value += v;
            }
            else {
                throw std::domain_error("Invalid 2 byte sequence");
            }

            result.push_back(value);
        }
        else if ((*b & FirstofOneByteSequence) == 0x0) {
            result.push_back(*b);
        }
        else {
            throw std::domain_error("Invalid byte sequence");
        }
    }

    return result;
}

}}}
