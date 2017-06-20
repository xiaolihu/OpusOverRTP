// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.
#include "rtp.h"

class voipCodec {
public:
    voipCodec() { RD_buffer = new RD_buffer_t(); } // to delete
    virtual ~voipCodec() = default;

    void voipDecInit() {}
    void voipEncInit() {}

    virtual int decodeFrame();
    virtual int encodeFrame();
protect:
    bool validateRTPDumpVersion(istream &fin);
    int extractRTPPayload(istream &fin, RD_buffer_t *b);
    RD_buffer_t * RD_buffer = 0;
private:
    static const char RTPFILE_VER[];
    //TBD
};
