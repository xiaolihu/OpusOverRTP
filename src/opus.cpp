#include "opus.hpp"

const int max_output_samples = OPUS_DEFAULT_SAMPLE_RATE * 0.001 * 120;

void error_anylsis(int code)
{
    switch(code){
        case OPUS_BAD_ARG:
            cerr<<"OPUS_BAD_ARG"<<endl;
            break;
        case OPUS_BUFFER_TOO_SMALL:
            cerr<<"OPUS_BUFFER_TOO_SMALL"<<endl;
            break;
        case OPUS_INTERNAL_ERROR:
            cerr<<"OPUS_INTERNAL_ERROR"<<endl;
            break;
        case OPUS_UNIMPLEMENTED:
            cerr<<"OPUS_UNIMPLEMENTED"<<endl;
            break;
        case OPUS_INVALID_STATE:
            cerr<<"OPUS_INVALID_STATE"<<endl;
            break;
        case OPUS_ALLOC_FAIL:
            cerr<<"OPUS_ALLOC_FAIL"<<endl;
            break;
        default:
            cerr<<"unknown fault"<<endl;
    }
}

opusCodec::opusCodec(opus_int32 sampRate,int ch)
{
    //should be passed-in via command line
    int error; 
    decInst = opus_decoder_create(sampRate, ch, &error);
    
    encInst = NULL; // TBD

    decOutputBuf = new char[5760]();
}

int opusCodec::decodeFrame(istream &fin, ostream &fout)
{
    bool decode_done = false;
    int outSamples = -1;
    //extract RTP headder and check its payload
    // https://wiki.wireshark.org/rtpdump
    if(!validateRTPDumpVersion(fin)) {
        cerr << "Not valid RTP file !" << endl;
        return DEC_FAILURE; // DEC_FAILURE
    }

    //While loop here till EOF
    while (extractRTPPayload(fin, voipCodec::RD_buffer) > 0) {
        outSamples = opus_decode(decInst, (unsigned char *)RD_buffer->p.data, RD_buffer->p.hdr.plen,
                                (opus_int16*)decOutputBuf, max_output_samples, 0); // no fec
        if(outSamples != OPUS_BAD_ARG && outSamples != OPUS_BUFFER_TOO_SMALL 
            && outSamples != OPUS_INTERNAL_ERROR && outSamples != OPUS_UNIMPLEMENTED 
            && outSamples != OPUS_INVALID_STATE && outSamples != OPUS_ALLOC_FAIL)
            fout.write(decOutputBuf, outSamples << 1);
        else if(outSamples != OPUS_OK){
            error_anylsis(outSamples);
            return DEC_FAILURE;
        }

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
