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

    fin.getline(line, sizeof(line));
    
    sprintf(magic, "#!rtpplay%s ", RTPFILE_VER);

    if(!strncmp(line, magic, strlen(magic))) return true;

    return false;
}

void voipCodec::getRTPHeader(istream &fin,RD_hdr_t* hd)
{
    // One binary header(RD_hdr_t) follows after rtp dump file version
    // https://wiki.wireshark.org/rtpdump
    char temp[20];

    fin.read(temp, sizeof(RD_hdr_t));
    memcpy(hd, temp, sizeof(RD_hdr_t));

    /* convert to host byte order */
    hd->start.tv_sec = ntohl(hd->start.tv_sec);
    hd->start.tv_usec = ntohl(hd->start.tv_usec);
    hd->source = ntohl(hd->source);
    hd->port = ntohs(hd->port);
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

void print_hex(char *str, int len)
{
    char ch;

    for(int i = 0; i < len; i++) {
        ch = str[i];
        cout << setw(2) << setfill('0') << hex << (static_cast<short>(ch) & 0xff) << " "; 

        if ( (i+1)%16 == 0 )
            cout<< endl;
        else if ( (i+1)%8 == 0 )
            cout<< "  ";
               
    }
    cout<< endl;
}
