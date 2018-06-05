#include "unicode_string.hpp"

// #include <iostream> // debug only

#include "re_encode.hpp"

namespace echelon { namespace unicode {

using namespace echelon::unicode::encoding;

UnicodeString::UnicodeString(const std::vector<utf8_codePoint> &input) {
    this->inner = re_encode(input);
}

#ifdef ECHELON_DEBUG
void UnicodeString::print() {
    for (auto x : this->inner) {
        std::cout << x << std::endl;
    }
}
#endif

}}

