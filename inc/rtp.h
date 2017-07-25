#ifndef _RTP_H_
#define _RTP_H_

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTP_VERSION 2
/*
 * RTP data header
 */
typedef struct {
    // RTP_BIG_ENDIAN
    unsigned int version:2;   /* protocol version */
    unsigned int p:1;         /* padding flag */
    unsigned int x:1;         /* header extension flag */
    unsigned int cc:4;        /* CSRC count */
    unsigned int m:1;         /* marker bit */
    unsigned int pt:7;        /* payload type */
    unsigned int seq:16;      /* sequence number */
    u_int32 ts;               /* timestamp */
    u_int32 ssrc;             /* synchronization source */
    //u_int32 csrc[1];          /* optional CSRC list */
} rtp_hdr_t;

/* http://www.cs.columbia.edu/irt/software/rtptools/
 *
 * This is followed by one binary header (RD_hdr_t) and one RD_packet_t
 * structure for each received packet.  All fields are in network byte
 * order.  We don't need the source IP address since we can do mapping
 * based on SSRC.  This saves (a little) space, avoids non-IPv4
 * problems and privacy/security concerns. The header is followed by
 * the RTP/RTCP header and (optionally) the actual payload.
 *
 */

struct timev {
  int32    tv_sec;/*second(s)*/
  int32    tv_usec;/*microsecond(us)*/
};

typedef struct {
  struct timev start;  /* start of recording (GMT) */
  u_int32 source;        /* network source (multicast address) */
  u_int16 port;          /* UDP port */
} RD_hdr_t;

typedef struct {
  u_int16 length;    /* length of packet, including this header (may 
                        be smaller than plen if not whole packet recorded) */
  u_int16 plen;      /* actual header+payload length for RTP, 0 for RTCP */
  u_int32 offset;    /* milliseconds since the start of recording */
} RD_packet_t;

typedef union {
  struct {
    RD_packet_t hdr;
    rtp_hdr_t rtp_hdr;
    char data[8000];
  } p;
  char byte[8192];
} RD_buffer_t;

#ifdef __cplusplus
}
#endif

#endif
