// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPCodec.hpp"

class g711uCodec: public voipCodec {
public:
    g711uCodec();
    ~g711uCodec();

    int decodeFrame();
    int encodeFrame();
};

int g711uCodec::decodeFrame()
{
// TBD
}

int g711uCodec::encodeFrame();
{
// TBD
}

