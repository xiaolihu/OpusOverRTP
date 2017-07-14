// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "opus.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main(int agrc, char *argv[])
{
    if (agrc < 3) {
        cerr<< "Usage: " << argv[0] << "[input filename] [output filename]"
                <<endl;
    }

    // more parameters for indicating decode or encode only
    // TBD
    //

    ifstream fin(argv[1], ios::binary);
    ofstream fout(argv[2], ios::binary);

    opusCodec opusDecEnc; // TBD passed-in parameters
    
    opusDecEnc.decodeFrame(fin, fout);

    return 0;
}

