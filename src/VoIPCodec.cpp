// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPCodec.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

const char voipCodec::RTPFILE_VER[] = "1.0";

bool voipCodec::validateRTPDumpVersion(istream &fin)
{
    // rtp dump file version @ first line
    // first line format : !#rtpplay1.0 address/port\n
    char line[80], magic[80];
    char temp[40];

    fin.getline(line, sizeof(line));
    
    //skip extra 16 bytes data
    fin.read(temp,16);
    
    sprintf(magic, "#!rtpplay%s ", RTPFILE_VER);

    if(!strncmp(line, magic, strlen(magic))) return true;

    return false;
}

int voipCodec::extractRTPPayload(istream &fin, RD_buffer_t *b)
{
    // RTP DUMP HEADER analysis
    // https://wiki.wireshark.org/rtpdump
        
    if (fin.eof()) return 0;

    fin.read(b->byte, sizeof(b->p.hdr) + sizeof(b->p.rtp_hdr));

    /* convert to host byte order */
    b->p.hdr.length = ntohs(b->p.hdr.length) - sizeof(b->p.hdr);
    b->p.hdr.offset = ntohl(b->p.hdr.offset);
    b->p.hdr.plen   = ntohs(b->p.hdr.plen) - sizeof(b->p.rtp_hdr);
    b->p.rtp_hdr.ts   = ntohl(b->p.rtp_hdr.ts);
    b->p.rtp_hdr.ssrc = ntohl(b->p.rtp_hdr.ssrc);
    
    // RTP Payload
    fin.read(b->p.data, b->p.hdr.plen);

    return (b->p.hdr.plen - sizeof(b->p.rtp_hdr));
}

void print_hex(char *str,int len)
{
    char ch;
    if(len>256) len = 256;
    for(int i=0; i<len;i++){
        ch = str[i];
        cout<<setw(2)<<setfill('0')<<hex<<(static_cast<short>(ch) & 0xff)<<" "; 

        if((i+1)%16 == 0) cout<<endl;
        else if((i+1)%8 == 0) cout<<"  ";
               
    }
    cout<<"end"<<endl<<endl;
}
