// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPCodec.hpp"

class opusCodec: public voipCodec {
public:
    opusCodec();
    ~opusCodec();

    int decodeFrame();
    int encodeFrame();
};

int opusCodec::decodeFrame()
{
// TBD
}

int opusCodec::encodeFrame();
{
// TBD
}
