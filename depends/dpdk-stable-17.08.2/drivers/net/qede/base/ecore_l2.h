/*
 * Copyright (c) 2016 QLogic Corporation.
 * All rights reserved.
 * www.qlogic.com
 *
 * See LICENSE.qede_pmd for copyright and licensing details.
 */

#ifndef __ECORE_L2_H__
#define __ECORE_L2_H__


#include "ecore.h"
#include "ecore_hw.h"
#include "ecore_spq.h"
#include "ecore_l2_api.h"

#define MAX_QUEUES_PER_QZONE	(sizeof(unsigned long) * 8)
#define ECORE_QUEUE_CID_PF	(0xff)

/* Additional parameters required for initialization of the queue_cid
 * and are relevant only for a PF initializing one for its VFs.
 */
struct ecore_queue_cid_vf_params {
	/* Should match the VF's relative index */
	u8 vfid;

	/* 0-based queue index. Should reflect the relative qzone the
	 * VF thinks is associated with it [in its range].
	 */
	u8 vf_qid;

	/* Indicates a VF is legacy, making it differ in several things:
	 *  - Producers would be placed in a different place.
	 *  - Makes assumptions regarding the CIDs.
	 */
	bool b_legacy;

	/* For VFs, this index arrives via TLV to diffrentiate between
	 * different queues opened on the same qzone, and is passed
	 * [where the PF would have allocated it internally for its own].
	 */
	u8 qid_usage_idx;
};

struct ecore_queue_cid {
	/* 'Relative' is a relative term ;-). Usually the indices [not counting
	 * SBs] would be PF-relative, but there are some cases where that isn't
	 * the case - specifically for a PF configuring its VF indices it's
	 * possible some fields [E.g., stats-id] in 'rel' would already be abs.
	 */
	struct ecore_queue_start_common_params rel;
	struct ecore_queue_start_common_params abs;
	u32 cid;
	u16 opaque_fid;

	/* VFs queues are mapped differently, so we need to know the
	 * relative queue associated with them [0-based].
	 * Notice this is relevant on the *PF* queue-cid of its VF's queues,
	 * and not on the VF itself.
	 */
	u8 vfid;
	u8 vf_qid;

	/* We need an additional index to diffrentiate between queues opened
	 * for same queue-zone, as VFs would have to communicate the info
	 * to the PF [otherwise PF has no way to diffrentiate].
	 */
	u8 qid_usage_idx;

	/* Legacy VFs might have Rx producer located elsewhere */
	bool b_legacy_vf;

	struct ecore_hwfn *p_owner;
};

enum _ecore_status_t ecore_l2_alloc(struct ecore_hwfn *p_hwfn);
void ecore_l2_setup(struct ecore_hwfn *p_hwfn);
void ecore_l2_free(struct ecore_hwfn *p_hwfn);

void ecore_eth_queue_cid_release(struct ecore_hwfn *p_hwfn,
				 struct ecore_queue_cid *p_cid);

struct ecore_queue_cid *
ecore_eth_queue_to_cid(struct ecore_hwfn *p_hwfn, u16 opaque_fid,
		       struct ecore_queue_start_common_params *p_params,
		       struct ecore_queue_cid_vf_params *p_vf_params);

enum _ecore_status_t
ecore_sp_eth_vport_start(struct ecore_hwfn *p_hwfn,
			 struct ecore_sp_vport_start_params *p_params);

/**
 * @brief - Starts an Rx queue, when queue_cid is already prepared
 *
 * @param p_hwfn
 * @param p_cid
 * @param bd_max_bytes
 * @param bd_chain_phys_addr
 * @param cqe_pbl_addr
 * @param cqe_pbl_size
 *
 * @return enum _ecore_status_t
 */
enum _ecore_status_t
ecore_eth_rxq_start_ramrod(struct ecore_hwfn *p_hwfn,
			   struct ecore_queue_cid *p_cid,
			   u16 bd_max_bytes,
			   dma_addr_t bd_chain_phys_addr,
			   dma_addr_t cqe_pbl_addr,
			   u16 cqe_pbl_size);

/**
 * @brief - Starts a Tx queue, where queue_cid is already prepared
 *
 * @param p_hwfn
 * @param p_cid
 * @param pbl_addr
 * @param pbl_size
 * @param p_pq_params - parameters for choosing the PQ for this Tx queue
 *
 * @return enum _ecore_status_t
 */
enum _ecore_status_t
ecore_eth_txq_start_ramrod(struct ecore_hwfn *p_hwfn,
			   struct ecore_queue_cid *p_cid,
			   dma_addr_t pbl_addr, u16 pbl_size,
			   u16 pq_id);

u8 ecore_mcast_bin_from_mac(u8 *mac);

/**
 * @brief - ecore_configure_rfs_ntuple_filter
 *
 * This ramrod should be used to add or remove arfs hw filter
 *
 * @params p_hwfn
 * @params p_ptt
 * @params p_cb		Used for ECORE_SPQ_MODE_CB,where client would initialize
			it with cookie and callback function address, if not
			using this mode then client must pass NULL.
 * @params p_addr	p_addr is an actual packet header that needs to be
 *			filter. It has to mapped with IO to read prior to
 *			calling this, [contains 4 tuples- src ip, dest ip,
 *			src port, dest port].
 * @params length	length of p_addr header up to past the transport header.
 * @params qid		receive packet will be directed to this queue.
 * @params vport_id
 * @params b_is_add	flag to add or remove filter.
 *
 */
enum _ecore_status_t
ecore_configure_rfs_ntuple_filter(struct ecore_hwfn *p_hwfn,
				  struct ecore_ptt *p_ptt,
				  struct ecore_spq_comp_cb *p_cb,
				  dma_addr_t p_addr, u16 length,
				  u16 qid, u8 vport_id,
				  bool b_is_add);
#endif
