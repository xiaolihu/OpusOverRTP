// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

class voipCodec {
public:
    voipCodec();
    virtual ~voipCodec() = default;

    void voipDecInit();
    void voipEncInit();

    virtual int decodeFrame();
    virtual int encodeFrame();
protect:
    void extractRTPHeader();
private:
    //TBD
};
