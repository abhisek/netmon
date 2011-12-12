What is it
==========

Experiment for packet fun.

Architecture
============

* Netmon
 * Core
   * ui
   * module (redesign: Implements independent loosely coupled capabilities)
   * packet capturer |
   * packet decoder  |-- Closely coupled subsystems
   * packet analyzer |
   * packet hooks
     * pre-decode
     * post-decode
     * pre-analysis
     * post-analysis
 * UI - Mostly for messaging
   * Text (default)
   * GTK (planning)
 * Modules
   * Analysis
      * Dummy
      * ARP - ARP poinsoning detection module
      * DHCP - DHCP poisoning detection module (planned)
      * Shellcode - Exploitation attempt detection module (long term plan)
   * Decoder
      * Ethernet
      * ARP
      * ICMP
      * IP
      * TCP

Core
----

Packet Subsystem
-----------------

The packet subsystem is responsible for capturing a packet off the wire and
perform decoding, analysis using the registered decoder and analzer
functions.

The packet subsystem internally uses tower (array) for decoder managemenet. Each
decoder is reponsible for decoding a protocol in a layer/level as per OSI model
ie. there are 7 levels in the tower and each decoder is registered in any one of
the level in the tower.

Each decoder function receives a packet structure (struct packet) as its sole
argument when it is called. Each decoder should also return any one of the
following:

* DECODER_RET_SUCCESS: Successfully decoded the protocol for the level
* DECODER_RET_CONTINUE: Decoded partially, decoding must continue
* DECODER_RET_FAILED: Decoding failed for some reason

Each decoder should also remember that packet->lX_data is a pointer which is
intialized to be NULL by packet subsytem and as the packet traverses the decoder
tower, appropriate decoders are free to make approriate packet->lX_data point to
correct protocol header, but those structures must *always* be allocated with
malloc() since the packet subsystem free()'s the packet->lX_data pointers if not
set to NULL. (This design might be insecure and needs to be looked up)

The packet subsystem also provides specialized hooks for modules for performing
various operations. Following hooks are provided:

* Pre Decode Hook: Hook functions are called just after a packet is captured and
before any decoding is started.

* Post Decode Hook: Hook functions are called just after decoding is completed
on the packet.

* Post Analysis Hook: Hook functions are called just after analysis is completed
on the packet.

UI
--

Modules
-------
