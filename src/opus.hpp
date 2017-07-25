// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPCodec.hpp"
#include "opus.h"
#include <cstring>

#define OPUS_DEFAULT_SAMPLE_RATE 16000 // To be done, should be passed in via CLI command

struct opusConig {
    int codecMode;
    int frameSizeMs;
    int sampleRateHz;
    int targetBitRate;
    int channels;
    bool vbr;
};

typedef enum {
	DEC_FAILURE = -1,
	DEC_SUCCESS = 0
} CODEC_RC;

extern void print_hex(char *str, int len);

class opusCodec: public voipCodec {
public:
    opusCodec(opus_int32 sampRate = 16000, int ch=1);
    ~opusCodec() { opus_decoder_destroy(decInst); delete[] decOutputBuf; }

    int decodeFrame(istream &fin, ostream &fout);
    int encodeFrame();
private:
    // members
    //opusConfig configs;
    OpusDecoder *decInst; 
    OpusEncoder *encInst;
    char *decOutputBuf;
};



