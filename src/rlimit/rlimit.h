#ifndef __RLIMIT__
#define __RLIMIT__

/******************************************************/
/*      Function: resource limit                      */
/*      Author:   jonly                               */
/*      Date:     20200121                            */
/******************************************************/

#define ADS_MAX_LCORES      RTE_MAX_LCORE     /* max logic cores */
#define ADS_MAX_ETHPORTS    RTE_MAX_ETHPORTS  /* max ether ports */

#define ADS_ETHER_ADDR_LEN  ETHER_ADDR_LEN

#define ADS_IPV6_ADDR_LEN   16
#define ADS_IPV6_ADDR_U64   (ADS_IPV6_ADDR_LEN / sizeof(uint64_t))
#define ADS_IPV6_ADDR_U32   (ADS_IPV6_ADDR_LEN / sizeof(uint32_t))
#define ADS_IPV6_ADDR_U16   (ADS_IPV6_ADDR_LEN / sizeof(uint16_t))

#define ADS_IPV4_ADDR_LEN   4
#define ADS_IPV4_ADDR_U16   (ADS_IPV4_ADDR_LEN / sizeof(uint16_t))

#endif
