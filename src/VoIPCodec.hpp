// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.
#include "rtp.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

void print_hex(char *str, int len);

enum {
    ENCDEC_OK,
    ENCDEC_ERROR
};

class voipCodec {
public:
    voipCodec() { RD_buffer = new RD_buffer_t(); }
    ~voipCodec() { delete RD_buffer;}

    void voipDecInit() {}
    void voipEncInit() {}

    int decodeFrame() {return 0;}
    int encodeFrame() {return 0;}
protected:
    bool validateRTPDumpVersion(std::istream &fin);
    void getRTPHeader(istream &fin, RD_hdr_t *hd);
    int extractRTPPayload(std::istream &fin, RD_buffer_t *b);
    RD_buffer_t * RD_buffer;
private:
    static const char RTPFILE_VER[];
    //TBD
};
