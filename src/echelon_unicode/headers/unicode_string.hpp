#ifndef UNICODE_STRING_HEADER_INCLUDED
#define UNICODE_STRING_HEADER_INCLUDED

#include <vector>

#include "utf_types.hpp"

namespace echelon { namespace unicode {

class UnicodeString {
    std::vector<echelon::unicode::utf32_codePoint> inner;
public:
    UnicodeString(const std::vector<echelon::unicode::utf8_codePoint> &input);

#ifdef ECHELON_DEBUG
    void print();
#endif
};

}}

#endif // UNICODE_STRING_HEADER_INCLUDED
