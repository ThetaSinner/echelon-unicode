#ifndef ENCODE_HEADER_INCLUDED
#define ENCODE_HEADER_INCLUDED

#include <vector>

#include "utf_types.hpp"

namespace echelon { namespace unicode { namespace encoding {

/**
 * Convert UTF-8 encoded data into UTF-32 encoded data.
 * 
 * \throws std::domain_error If the input encoding is invalid.
 */
std::vector<echelon::unicode::utf32_codePoint> re_encode(std::vector<echelon::unicode::utf8_codePoint> input);

}}}

#endif // ENCODE_HEADER_INCLUDED
