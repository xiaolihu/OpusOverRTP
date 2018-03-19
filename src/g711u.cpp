// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPCodec.hpp"

class g711uCodec: public voipCodec {
public:
    g711uCodec(){};
    ~g711uCodec(){};

    int encodeFrame(int sampleCnt, int16_t *inBuf, int8_t *outBuf);
    int decodeFrame(int sampleCnt, int8_t *inBuf, int16_t *outBuf);
private:
    int16_t linear2ulaw(int8_t number);
    int8_t ulaw2linear(int16_t number);
};

// overload base function
int g711uCodec::encodeFrame(int sampleCnt, int16_t *inBuf, int8_t *outBuf)
{
    for (int n = 0; n < sampleCnt; n++) {
        *outBuf++ = linear2ulaw(*inBuf++);
    }

    return ENCDEC_OK;
}

// overload base function
int g711uCodec::ulaw2linear(int sampleCnt, int8_t *inBuf, int16_t *outBuf)
{
    for (int n = 0; n < sampleCnt; n++) {
        *outBuf++ = decodeFrame_(*inBuf++);
    }

    return ENCDEC_OK;
}

/*
 * linear2ulaw - Convert a linear PCM value to u-law
 *
 * In order to simplify the encoding process, the original linear magnitude
 * is biased by adding 33 which shifts the encoding range from (0 - 8158) to
 * (33 - 8191). The result can be seen in the following encoding table:
 *
 *    Biased Linear Input Code  Compressed Code
 *    ------------------------  ---------------
 *    00000001wxyza             000wxyz
 *    0000001wxyzab             001wxyz
 *    000001wxyzabc             010wxyz
 *    00001wxyzabcd             011wxyz
 *    0001wxyzabcde             100wxyz
 *    001wxyzabcdef             101wxyz
 *    01wxyzabcdefg             110wxyz
 *    1wxyzabcdefgh             111wxyz
 *
 * Each biased linear code has a leading 1 which identifies the segment
 * number. The value of the segment number is equal to 7 minus the number
 * of leading 0's. The quantization interval is directly available as the
 * four bits wxyz.  * The trailing bits (a - h) are ignore.
 *
 * Ordinarily the complement of the resulting code word is used for
 * transmission, and so the code word is complemented before it is returned.
 */
int8_t g711uCodec::linear2ulaw(int16_t number)
{
    const uint16_t MULAW_MAX = 0x1FFF;
    const uint16_t MULAW_BIAS = 33;
    uint16_t mask = 0x1000;
    uint8_t sign = 0;
    uint8_t position = 12;
    uint8_t lsb = 0;

    if (number < 0)
    {
        number = -number;
        sign = 0x80;
    }

    number += MULAW_BIAS;
    if (number > MULAW_MAX)
    {
        number = MULAW_MAX;
    }

    for (; ((number & mask) != mask && position >= 5); mask >>= 1, position--)
        ;

    lsb = (number >> (position - 4)) & 0x0f;

    return (~(sign | ((position - 5) << 4) | lsb));
}

int16_t g711uCodec::ulaw2linear(int8_t number)
{
    const uint16_t MULAW_BIAS = 33;
    uint8_t sign = 0, position = 0;
    int16_t decoded = 0;

    number = ~number;
    if (number & 0x80)
    {
        number &= ~(1 << 7);
        sign = -1;
    }

    position = ((number & 0xF0) >> 4) + 5;
    decoded = ((1 << position) | ((number & 0x0F) << (position - 4))
                | (1 << (position - 5))) - MULAW_BIAS;

    return (sign == 0) ? (decoded) : (-(decoded));
}

