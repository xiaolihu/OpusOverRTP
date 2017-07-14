// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.
#include "rtp.h"
#include <iostream>
#include <cstring>
using namespace std;
class voipCodec {
public:
    voipCodec() { RD_buffer = new RD_buffer_t(); }
    ~voipCodec() { delete RD_buffer;}

    void voipDecInit() {}
    void voipEncInit() {}

    virtual int decodeFrame(){};
    virtual int encodeFrame(){};
protected:
    bool validateRTPDumpVersion(std::istream &fin);
    int extractRTPPayload(std::istream &fin, RD_buffer_t *b);
    RD_buffer_t * RD_buffer = NULL;
private:
    static const char RTPFILE_VER[];
    //TBD
};
