// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.
#include "rtp.h"
#include <iostream>
<<<<<<< HEAD
#include <cstring>
using namespace std;
=======

>>>>>>> b8f3f6939464f0875c533b561237cc61b00e73d0
class voipCodec {
public:
    voipCodec() { RD_buffer = new RD_buffer_t(); }
    ~voipCodec() { delete RD_buffer;}

    void voipDecInit() {}
    void voipEncInit() {}

<<<<<<< HEAD
    virtual int decodeFrame(){};
    virtual int encodeFrame(){};
=======
    virtual int decodeFrame();
    virtual int encodeFrame();
>>>>>>> b8f3f6939464f0875c533b561237cc61b00e73d0
protected:
    bool validateRTPDumpVersion(std::istream &fin);
    int extractRTPPayload(std::istream &fin, RD_buffer_t *b);
    RD_buffer_t * RD_buffer = NULL;
private:
    static const char RTPFILE_VER[];
    //TBD
};
