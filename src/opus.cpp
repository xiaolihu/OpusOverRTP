// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPCodec.hpp"
#include "opus.h"

typedef struct opusConig {
    int codecMode;
    int frameSizeMs;
    int sampleRateHz;
    int targetBitRate;
    int channels;
    bool vbr;
};

class opusCodec: public voipCodec {
public:
    opusCodec();
    ~opusCodec();

    int decodeFrame(istream &fin, ostream &fout);
    int encodeFrame();
private:
    // members
    //opusConfig configs;
    OpusDecoder *decInst; 
    OpusEncoder *encInst; 
};


opusCodec::opusCodec()
{
    //should be passed-in via command line
    int error, ch = 1; 
    decInst = opus_decoder_create(48000, ch, &error);

    encInst = NULL; // TBD 
}

int opusCodec::decodeFrame(istream &fin, ostream &fout)
{
    //While loop here till EOF

    //Read packets from stored RTP file

    //extract RTP headder and check its payload
    // RTP HEAHER + RTP PAYLOAD
    //
    // https://wiki.wireshark.org/rtpdump

}

int opusCodec::encodeFrame()
{
// TBD
}
