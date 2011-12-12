#ifndef _NETMON_LINUX_SLL_H
#define _NETMON_LINUX_SLL_H

/*
 * From: http://wiki.wireshark.org/SLL
 *
 * This is the pseudo-protocol used by libpcap on Linux to capture from the
 * "any" device and to capture on some devices where the native link layer
 * header isn't available or can't be used. (For example, the Linux PPP code
 * doesn't reliably supply a PPP header to libpcap - it's usually either absent,
 * meaning that the packet type isn't available, or contains extra random gunk
 * in some but not all packets, as happens on some PPP-over-ISDN interfaces - so
 * the SLL pseudo-link-layer is used on PPP interfaces. It's used on the "any"
 * device because not all interfaces on a machine necessarily have the same
 * link-layer type, but, in order for capture filters to work, all packets on an
 * interface must have the same type of link-layer header.)
 */

#define SLL_PACKET_TYPE_TO_US    0x0000
#define SLL_PACKET_TYPE_FROM_US  0x0004

struct linux_sll_header {
   unsigned short pkt_type;
   unsigned short link_addr_type;
   unsigned short link_addr_len;
   unsigned char pad[8];
   unsigned short proto;
} __attribute__((packed));

#endif
