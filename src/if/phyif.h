#ifndef __PHYIF_H__
#define __PHYIF_H__

#include <stdint.h>
#include "rte_ether.h"
#include "rte_ethdev.h"
#include "ipaddr.h"

/******************************************************/
/*      Function: use to describe physical interface  */
/*      Author:   jonly                               */
/*      Date:     20200121                            */
/******************************************************/

typedef struct phyif_s {
    struct ether_addr macaddr;  /* ether mac addr */
	ipaddr_t ipaddr;            /* ipv4/ipv6 addr */
	uint16_t ifid;              /* physical ether port id init from dpdk portid */
    uint16_t virifid;           /* only support one virtual interface currently */
    uint16_t nb_rxq;            /* number of read queues */
    uint16_t nb_txq;            /* number of transmit queues */
    uint16_t nb_rxd;            /* number of read queues's descriptor */
    uint16_t nb_txd;            /* number of read queues's descriptor */
    struct rte_eth_conf     eth_conf;   /* ether configuration */
    struct rte_eth_fc_conf  fc_conf;    /* flow control configuration */
    
#define PHYIF_FLAGS_PROMISC     (1ULL << 0)  /* indicate in promisc mode */
#define PHYIF_FLAGS_TX_BUFFER   (1ULL << 1)  /* indicate if need tx buffer */
#define PHYIF_FLAGS_MACADDR     (1ULL << 2)  /* indicate if need mac addr */
#define PHYIF_FLAGS_IPADDR      (1ULL << 3)  /* indicate if need ip addr */
	uint64_t flags;
} phyif_t;

#endif
