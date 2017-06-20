// Xiaolin Huang 2017/06
//
// All Copyrights are reserved.

#include "VoIPcodec.hpp"

static const char RTPFILE_VER[] = "1.0";

bool voipCodec::validateRTPDumpVersion(istream &fin)
{
    // rtp dump file version @ first line
    char line[80], magic[80];

    fin.getline(line, sizeof(line);

    sprintf(magic, "#!rtpplay%s ", RTPFILE_VER);

    if(!strncmp(line, magic, strlen(magic))) return true;

    return false;
}

int voipCodec::extractRTPPayload(istream &fin, RD_buffer_t *b)
{
    // RTP DUMP HEADER analysis
    // https://wiki.wireshark.org/rtpdump

    fin.read(b->byte, sizeof(b->p.hdr) + sizeof(b->p.rtp_hdr));

    if (fin.eof()) return 0;

    /* convert to host byte order */
    b->p.hdr.length = ntohs(b->p.hdr.length) - sizeof(b->p.hdr);
    b->p.hdr.offset = ntohl(b->p.hdr.offset);
    b->p.hdr.plen   = ntohs(b->p.hdr.plen);

    b->p.rtp_hdr.ts   = ntohl(b->p.rtp_hdr.ts);
    b->p.rtp_hdr.ssrc = ntohl(b->p.rtp_hdr.ssrc);
    // RTP Payload
    fin.read(b->p.data, b->p.hdr.plen - sizeof(b->p.rtp_hdr));

    return (b->p.hdr.plen - sizeof(b->p.rtp_hdr));
}
