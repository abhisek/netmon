#ifndef _NETMON_PACKET_H
#define _NETMON_PACKET_H
#include <netmon.h>

/*
 * Packet state is an integer which denotes the level at
 * which the packet object currently is in the decoder tower
 */
#define PACKET_STATE_DECODE_L1   0x01
#define PACKET_STATE_DECODE_L2   0x02
#define PACKET_STATE_DECODE_L3   0x03
#define PACKET_STATE_DECODE_L4   0x04
#define PACKET_STATE_DECODE_L5   0x05
#define PACKET_STATE_DECODE_L6   0x06
#define PACKET_STATE_DECODE_L7   0x07
/*
 * generic packet definition
 *
 * NOTE: Decoders should not use pointers to point to data within packet object
 * Instead they should allocate memory and copy data for persistent storage
 * since packet object will be free'd after it traverses the decoder tower
 */
struct packet {
   char *frame;         /* non-decoded data frame */
   size_t offset;       /* offset to the non-decoded data area */
   size_t frame_size;

   int state;
   time_t last_decoded;
   time_t last_analyzed;

   pthread_mutex_t lock;   /* might not require lock currently */

   int l1_proto;   /* Host byte order if applicable */
   void *l1_data;  /* generic opaque place holder */
   int l1_data_len;

   int l2_proto;  /* Host byte order if applicable */
   void *l2_data;  /* should be type casted to appropriate proto header */
   int l2_data_len;

   int l3_proto;  /* Host byte order if applicable */
   void *l3_data; /* should be type casted to appropriate proto header */
   int l3_data_len;

   int l4_proto;  /* Host byte order if applicable */
   void *l4_data; /* should be type casted to appropriate proto header */
   int l4_data_len;

   int l5_proto;  /* Host byte order if applicable */
   void *l5_data; /* should be type casted to appropriate proto header */
   int l5_data_len;

   int l6_proto;  /* Host byte order if applicable */
   void *l6_data; /* should be type casted to appropriate proto header */
   int l6_data_len;

   int l7_proto;  /* Host byte order if applicable */
   void *l7_data; /* should be type casted to appropriate proto header */
   int l7_data_len;
};

/*
 * Inspect the packet for debugging purpose
 */
#define DEBUG_PACKET_INSPECT(p)  do {  \
      DEBUG_MSG("- packet: %p", p);    \
      DEBUG_MSG("      packet->frame:         %p", p->frame);  \
      DEBUG_MSG("      packet->offset:        0x%08x", p->offset);  \
      DEBUG_MSG("      packet->frame_size:    0x%08x", p->frame_size);  \
      DEBUG_MSG("      packet->state:         0x%08x", p->state);  \
      DEBUG_MSG("      packet->l2_proto:      0x%08x", p->l2_proto);  \
      DEBUG_MSG("      packet->l2_data:       0x%08x", p->l2_data);  \
      DEBUG_MSG("      packet->l2_data_len:   0x%08x", p->l2_data_len);  \
      DEBUG_MSG("      packet->l3_proto:      0x%08x", p->l3_proto);  \
      DEBUG_MSG("      packet->l3_data:       0x%08x", p->l3_data);  \
      DEBUG_MSG("      packet->l3_data_len:   0x%08x", p->l3_data_len);  \
      DEBUG_MSG("      packet->l4_proto:      0x%08x", p->l4_proto);  \
      DEBUG_MSG("      packet->l4_data:       0x%08x", p->l4_data);  \
      DEBUG_MSG("      packet->l4_data_len:   0x%08x", p->l4_data_len);  \
      DEBUG_MSG("- end");  \
   } while(0)

/*
 * Node for packet processing hook functions (callbacks)
 */
struct packet_hook {
   char *name;
   int (*process)(struct packet *p);

   LIST_ENTRY(packet_hook) link;
};

#endif
