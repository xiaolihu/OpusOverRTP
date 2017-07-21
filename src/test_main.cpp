// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "opus.hpp"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

void print_usage(char *argv[])
{
    cerr<< "Usage: " << argv[0] << "-d [options] "<< "<input filename> <output filename>"<<endl;
    cerr<< "options:"<<endl;
    cerr<< "        -d : runs the decoder"<<endl;
    cerr<< "        -r <sampling rate(Hz)>: default value is 16000 Hz. Supported sampling rates are 8000, 12000, 16000, 24000 and 48000."<<endl;
}

int main(int argc, char *argv[])
{
    int args;
    bool decode_only = false;
    string temp_str;
    opus_int32 sampling_rate = 16000;

    if (argc < 3) {
        print_usage(argv);
        return -1;
    }

    // more parameters for indicating decode or encode only
    // TBD
    //

    args = 1;
    temp_str = argv[args];
    if(temp_str == "-d") {
        args++;
        decode_only = true;
    }

    while(args < argc-2){
        temp_str = argv[args];
        if(temp_str == "-r") {
            sampling_rate = (opus_int32)atol(argv[++args]);
            args++;
            if(sampling_rate != 8000 && sampling_rate != 12000 && sampling_rate != 16000 && sampling_rate != 24000 && sampling_rate != 48000){
                cerr<< "Supported sampling rates are 8000, 12000, 16000, 24000 and 48000."<<endl;
                cerr<< "Using default value 16000"<<endl;
                sampling_rate = 16000;
            }
        } else if(temp_str == ""){

        } else{
            cerr<<"unreconize options"<<endl;
            print_usage(argv);
        }
    }

    ifstream fin(argv[argc-2], ios::binary);
    if(!fin.good()){
        cerr<<"Could not open input file "<<argv[argc-2]<<endl;
        fin.close();
        return -1;
    }

    ofstream fout(argv[argc-1], ios::binary);
    if(!fout.good()){
        cerr<<"Could not open output file "<<argv[argc-1]<<endl;
        fout.close();
        return -1;
    }

    opusCodec opusDecEnc(sampling_rate);

    if(decode_only){ 
        opusDecEnc.decodeFrame(fin, fout);
    }

    return 0;
}

