#ifndef __IPADDR_H__
#define __IPADDR_H__

/******************************************************/
/*      Function: resource limit                      */
/*      Author:   jonly                               */
/*      Date:     20200121                            */
/******************************************************/

#include <stdint.h>
#include "rlimit.h"

typedef struct ipaddr4_s {    
     union {
        __be32 addr32;
        __be16 addr16[ADS_IPV4_ADDR_U16];
        __u8   addr8[ADS_IPV4_ADDR_LEN];
    };
} ipaddr4_t;

typedef struct ipaddr6_s {
    union {
        __be64 addr64[ADS_IPV6_ADDR_U64];
        __be32 addr32[ADS_IPV6_ADDR_U32];
        __be16 addr16[ADS_IPV6_ADDR_U16];
        __u8   addr8[ADS_IPV6_ADDR_LEN];
    };
} ipaddr6_t;


typedef struct ipaddr_s {
    int family; /* AF_INET or AF_INT6 */
    union {
        ipaddr4_t ipaddr4;
        ipaddr6_t ipaddr6;
    };
} ipaddr_t;

#endif
