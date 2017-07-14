// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPCodec.hpp"
#include "opus.h"

#include <cstring>

#define OPUS_DEFAULT_SAMPLE_RATE 48000 // To be done, should be passed in via CLI command

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

const int max_output_samples = OPUS_DEFAULT_SAMPLE_RATE * 0.001 * 120;

class opusCodec: public voipCodec {
public:
    opusCodec();
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


opusCodec::opusCodec()
{
    //should be passed-in via command line
    int error, ch = 1; 
    decInst = opus_decoder_create(16000, ch, &error);

    encInst = NULL; // TBD

    decOutputBuf = new char[5760]();
}

int opusCodec::decodeFrame(istream &fin, ostream &fout)
{
    bool decode_done = false;

    //extract RTP headder and check its payload
    // https://wiki.wireshark.org/rtpdump
    if(!validateRTPDumpVersion(fin)) {
        cerr << "Not valid RTP file !" << endl;
        return DEC_FAILURE; // DEC_FAILURE
    }

    //While loop here till EOF
    while (extractRTPPayload(fin, voipCodec::RD_buffer) > 0) {
       outSamples = opus_decode(decInst, RD_buffer->p.data, RD_buffer->p.hdr.plen,
                                decOutputBuf, max_output_samples, 0); // no fec
       fout.write(decOutputBuf, outSamples >> 2);

       memset(decOutputBuf, 0, 5760);
       memset(RD_buffer, 0, sizeof(RD_buffer_t));
    }

    return DEC_SUCCESS;

}

int opusCodec::encodeFrame()
{
// TBD
    return 0;
}
