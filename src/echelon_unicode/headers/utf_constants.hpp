#ifndef UTF_CONSTANTS_HEADER_INCLUDED
#define UTF_CONSTANTS_HEADER_INCLUDED

namespace echelon { namespace unicode { namespace utf_8 {
    enum ByteNumber : unsigned char {
        FirstofOneByteSequence = 0x80,
        ContinuationByteSequence = 0x80,
        FirstOfTwoByteSequence = 0xC0,
        FirstOfThreeByteSequence = 0xE0,
        FirstOfFourByteSequence = 0xF0,
    };
}}}

#endif // UTF_CONSTANTS_HEADER_INCLUDED
