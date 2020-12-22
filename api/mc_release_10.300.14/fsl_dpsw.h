/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2020 NXP
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * * Neither the name of the above-listed copyright holders nor the
 * names of any contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_DPSW_H
#define __FSL_DPSW_H

#include <fsl_net.h>

/** @addtogroup dpsw Data Path L2-Switch API
 * Contains API for handling DPSW topology and functionality
 * @{
 */

struct fsl_mc_io;

/**
 * DPSW general definitions
 */

/**
 * Maximum number of traffic class priorities
 */
#define DPSW_MAX_PRIORITIES	8
/**
 * Maximum number of interfaces
 */
#define DPSW_MAX_IF		64

#define DPSW_MAX_KEY_SIZE		56

int dpsw_open(struct fsl_mc_io *mc_io,
	      uint32_t cmd_flags,
	      int dpsw_id,
	      uint16_t *token);

int dpsw_close(struct fsl_mc_io *mc_io,
	       uint32_t cmd_flags,
	       uint16_t token);

/**
 * DPSW options
 */

/**
 * Disable flooding
 */
#define DPSW_OPT_FLOODING_DIS		0x0000000000000001ULL
/**
 * Disable Multicast
 */
#define DPSW_OPT_MULTICAST_DIS		0x0000000000000004ULL
/**
 * Support control interface
 */
#define DPSW_OPT_CTRL_IF_DIS		0x0000000000000010ULL
/**
 * Disable flooding metering
 */
#define DPSW_OPT_FLOODING_METERING_DIS	0x0000000000000020ULL
/**
 * Enable metering
 */
#define DPSW_OPT_METERING_EN		0x0000000000000040ULL
/**
 * Each interface will use own buffer pool
 */
#define DPSW_OPT_BP_PER_IF			0x0000000000000080ULL
/**
 * Disable link aggregation
 */
#define DPSW_OPT_LAG_DIS		0x0000000000000100ULL
/**
 * VLAN miss action is reprogrammed to look-up in FDB
 */
#define DPSW_OPT_VLAN_MISS		0x0000000000000200ULL
/**
 * Filter unicast frames sent back on the receiving interface
 */
#define DPSW_OPT_FILTER_RCV_UNICAST		0x0000000000000400ULL

/**
 * enum dpsw_component_type - component type of a bridge
 * @DPSW_COMPONENT_TYPE_C_VLAN: A C-VLAN component of an
 *   enterprise VLAN bridge or of a Provider Bridge used
 *   to process C-tagged frames
 * @DPSW_COMPONENT_TYPE_S_VLAN: An S-VLAN component of a
 *   Provider Bridge
 *
 */
enum dpsw_component_type {
	DPSW_COMPONENT_TYPE_C_VLAN = 0,
	DPSW_COMPONENT_TYPE_S_VLAN
};

/**
 * struct dpsw_cfg - DPSW configuration
 * @num_ifs: Number of external and internal interfaces
 * @adv: Advanced parameters; default is all zeros;
 *	 use this structure to change default settings
 * @adv.options: Enable/Disable DPSW features (bitmap). It is a combination of DPSW_OPT_ flags
 * @adv.max_vlans: Maximum Number of VLAN's; 0 - indicates default 16
 * @adv.max_meters_per_if: Number of meters per interface
 * @adv.max_fdbs: Maximum Number of FDB's; 0 - indicates default 16
 * @adv.max_fdb_entries: Number of FDB entries for default FDB table;
 *	0 - indicates default 1024 entries.
 * @adv.fdb_aging_time: Default FDB aging time for default FDB table;
 *	0 - indicates default 300 seconds
 * @adv.max_fdb_mc_groups: Number of multicast groups in each FDB table;
 *	0 - indicates default 32
 * @adv.mem_size: Size of the memory used for internal buffers expressed as number of 256byte
 * buffers. Must be an integer multiple of number of interfaces.
 * @adv.component_type: Indicates the component type of this bridge
 */
struct dpsw_cfg {
	uint16_t num_ifs;
	struct {
		uint64_t options;
		uint16_t max_vlans;
		uint8_t max_meters_per_if;
		uint8_t max_fdbs;
		uint16_t max_fdb_entries;
		uint16_t fdb_aging_time;
		uint16_t max_fdb_mc_groups;
		uint16_t mem_size;
		enum dpsw_component_type component_type;
	} adv;
};

int dpsw_create(struct fsl_mc_io *mc_io,
		uint16_t dprc_token,
		uint32_t cmd_flags,
		const struct dpsw_cfg *cfg,
		uint32_t *obj_id);

int dpsw_destroy(struct fsl_mc_io *mc_io,
		uint16_t dprc_token,
		uint32_t cmd_flags,
		uint32_t object_id);

int dpsw_enable(struct fsl_mc_io *mc_io,
		uint32_t cmd_flags,
		uint16_t token);

int dpsw_disable(struct fsl_mc_io *mc_io,
		 uint32_t cmd_flags,
		 uint16_t token);

int dpsw_is_enabled(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    int *en);

int dpsw_reset(struct fsl_mc_io *mc_io,
	       uint32_t cmd_flags,
	       uint16_t token);

/**
 * DPSW IRQ Index and Events
 */

#define DPSW_IRQ_INDEX_IF		0x0000
#define DPSW_IRQ_INDEX_L2SW		0x0001

/**
 * IRQ event - Indicates that the link state changed
 */
#define DPSW_IRQ_EVENT_LINK_CHANGED	0x0001

int dpsw_set_irq_enable(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint8_t irq_index,
			uint8_t en);

int dpsw_get_irq_enable(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint8_t irq_index,
			uint8_t *en);

int dpsw_set_irq_mask(struct fsl_mc_io *mc_io,
		      uint32_t cmd_flags,
		      uint16_t token,
		      uint8_t irq_index,
		      uint32_t mask);

int dpsw_get_irq_mask(struct fsl_mc_io *mc_io,
		      uint32_t cmd_flags,
		      uint16_t token,
		      uint8_t irq_index,
		      uint32_t *mask);

int dpsw_get_irq_status(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint8_t irq_index,
			uint32_t *status);

int dpsw_clear_irq_status(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint8_t irq_index,
			  uint32_t status);
/**
 * struct dpsw_attr - Structure representing DPSW attributes
 * @id: DPSW object ID
 * @options: Enable/Disable DPSW features
 * @max_vlans: Maximum Number of VLANs
 * @max_meters_per_if:  Number of meters per interface
 * @max_fdbs: Maximum Number of FDBs
 * @max_fdb_entries: Number of FDB entries for default FDB table;
 *			0 - indicates default 1024 entries.
 * @fdb_aging_time: Default FDB aging time for default FDB table;
 *			0 - indicates default 300 seconds
 * @max_fdb_mc_groups: Number of multicast groups in each FDB table;
 *			0 - indicates default 32
 * @mem_size: DPSW frame storage memory size
 * @num_ifs: Number of interfaces
 * @num_vlans: Current number of VLANs
 * @num_fdbs: Current number of FDBs
 * @component_type: Component type of this bridge
 */
struct dpsw_attr {
	int id;
	uint64_t options;
	uint16_t max_vlans;
	uint8_t max_meters_per_if;
	uint8_t max_fdbs;
	uint16_t max_fdb_entries;
	uint16_t fdb_aging_time;
	uint16_t max_fdb_mc_groups;
	uint16_t num_ifs;
	uint16_t mem_size;
	uint16_t num_vlans;
	uint8_t num_fdbs;
	enum dpsw_component_type component_type;
};

int dpsw_get_attributes(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			struct dpsw_attr *attr);

int dpsw_set_reflection_if(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint16_t if_id);

/**
 * enum dpsw_action - Action selection for special/control frames
 * @DPSW_ACTION_DROP: Drop frame
 * @DPSW_ACTION_REDIRECT: Redirect frame to control port
 */
enum dpsw_action {
	DPSW_ACTION_DROP = 0,
	DPSW_ACTION_REDIRECT = 1
};

/**
 * Enable auto-negotiation
 */
#define DPSW_LINK_OPT_AUTONEG		0x0000000000000001ULL
/**
 * Enable half-duplex mode
 */
#define DPSW_LINK_OPT_HALF_DUPLEX	0x0000000000000002ULL
/**
 * Enable pause frames
 */
#define DPSW_LINK_OPT_PAUSE		0x0000000000000004ULL
/**
 * Enable a-symmetric pause frames
 */
#define DPSW_LINK_OPT_ASYM_PAUSE	0x0000000000000008ULL

/**
 * struct dpsw_link_cfg - Structure representing DPSW link configuration
 * @rate: Rate
 * @options: Mask of available options; use 'DPSW_LINK_OPT_<X>' values
 */
struct dpsw_link_cfg {
	uint32_t rate;
	uint64_t options;
	uint64_t advertising;
};

int dpsw_if_set_link_cfg(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint16_t if_id,
			 struct dpsw_link_cfg *cfg);
/**
 * struct dpsw_link_state - Structure representing DPSW link state
 * @rate: Rate
 * @options: Mask of available options; use 'DPSW_LINK_OPT_<X>' values
 * @up: 0 - covers two cases: down and disconnected, 1 - up
 * @state_valid: Ignore/Update the state of the link
 * @supported: Speeds capability of the phy (bitmap)
 * @advertising: Speeds that are advertised for autoneg (bitmap)
 */
struct dpsw_link_state {
	uint32_t rate;
	uint64_t options;
	int up;
	int state_valid;
	uint64_t supported;
	uint64_t advertising;
};

int dpsw_if_get_link_state(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint16_t if_id,
			   struct dpsw_link_state *state);

int dpsw_if_set_flooding(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint16_t if_id,
			 int en);

int dpsw_if_set_broadcast(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint16_t if_id,
			  int en);

int dpsw_if_set_multicast(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint16_t if_id,
			  int en);

/**
 * Traffic types used for isolation feature
 * to allow or deny certain traffic between interfaces
 */
#define DPSW_TRAFFIC_TYPE_UNICAST       0x01
#define DPSW_TRAFFIC_TYPE_MULTICAST     0x02
#define DPSW_TRAFFIC_TYPE_BROADCAST     0x04

int dpsw_if_allow_traffic(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint16_t if_src,
			  uint16_t if_dst,
			  uint8_t type);

int dpsw_if_deny_traffic(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint16_t if_src,
			  uint16_t if_dst,
			  uint8_t type);

/**
 * struct dpsw_tci_cfg - Tag Contorl Information (TCI) configuration
 * @pcp: Priority Code Point (PCP): a 3-bit field which refers
 *		 to the IEEE 802.1p priority
 * @dei: Drop Eligible Indicator (DEI): a 1-bit field. May be used
 *		 separately or in conjunction with PCP to indicate frames
 *		 eligible to be dropped in the presence of congestion
 * @vlan_id: VLAN Identifier (VID): a 12-bit field specifying the VLAN
 *			to which the frame belongs. The hexadecimal values
 *			of 0x000 and 0xFFF are reserved;
 *			all other values may be used as VLAN identifiers,
 *			allowing up to 4,094 VLANs
 */
struct dpsw_tci_cfg {
	uint8_t pcp;
	uint8_t dei;
	uint16_t vlan_id;
};

int dpsw_if_set_tci(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    uint16_t if_id,
		    const struct dpsw_tci_cfg *cfg);

int dpsw_if_get_tci(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    uint16_t if_id,
		    struct dpsw_tci_cfg *cfg);

/**
 * enum dpsw_stp_state - Spanning Tree Protocol (STP) states
 * @DPSW_STP_STATE_BLOCKING: Blocking state
 * @DPSW_STP_STATE_LISTENING: Listening state
 * @DPSW_STP_STATE_LEARNING: Learning state
 * @DPSW_STP_STATE_FORWARDING: Forwarding state
 *
 */
enum dpsw_stp_state {
	DPSW_STP_STATE_BLOCKING = 0,
	DPSW_STP_STATE_LISTENING = 1,
	DPSW_STP_STATE_LEARNING = 2,
	DPSW_STP_STATE_FORWARDING = 3
};

/**
 * struct dpsw_stp_cfg - Spanning Tree Protocol (STP) Configuration
 * @vlan_id: VLAN ID STP state
 * @state: STP state
 */
struct dpsw_stp_cfg {
	uint16_t vlan_id;
	enum dpsw_stp_state state;
};

int dpsw_if_set_stp(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    uint16_t if_id,
		    const struct dpsw_stp_cfg *cfg);

/**
 * enum dpsw_accepted_frames - Types of frames to accept
 * @DPSW_ADMIT_ALL: The device accepts VLAN tagged, untagged and
 *			priority tagged frames
 * @DPSW_ADMIT_ONLY_VLAN_TAGGED: The device discards untagged frames or
 *			Priority-Tagged frames received on this interface.
 *
 */
enum dpsw_accepted_frames {
	DPSW_ADMIT_ALL = 1,
	DPSW_ADMIT_ONLY_VLAN_TAGGED = 3
};

/**
 * struct dpsw_accepted_frames_cfg - Types of frames to accept configuration
 * @type: Defines ingress accepted frames
 * @unaccept_act: When a frame is not accepted, it may be discarded or
 *			redirected to control interface depending on this mode
 */
struct dpsw_accepted_frames_cfg {
	enum dpsw_accepted_frames type;
	enum dpsw_action unaccept_act;
};

int dpsw_if_set_accepted_frames(struct fsl_mc_io *mc_io,
				uint32_t cmd_flags,
				uint16_t token,
				uint16_t if_id,
				const struct dpsw_accepted_frames_cfg *cfg);

int dpsw_if_set_accept_all_vlan(struct fsl_mc_io *mc_io,
				uint32_t cmd_flags,
				uint16_t token,
				uint16_t if_id,
				int accept_all);

/**
 * enum dpsw_counter  - Counters types
 * @DPSW_CNT_ING_FRAME: Counts ingress frames
 * @DPSW_CNT_ING_BYTE: Counts ingress bytes
 * @DPSW_CNT_ING_FLTR_FRAME: Counts filtered ingress frames
 * @DPSW_CNT_ING_FRAME_DISCARD: Counts discarded ingress frame
 * @DPSW_CNT_ING_MCAST_FRAME: Counts ingress multicast frames
 * @DPSW_CNT_ING_MCAST_BYTE: Counts ingress multicast bytes
 * @DPSW_CNT_ING_BCAST_FRAME: Counts ingress broadcast frames
 * @DPSW_CNT_ING_BCAST_BYTES: Counts ingress broadcast bytes
 * @DPSW_CNT_EGR_FRAME: Counts egress frames
 * @DPSW_CNT_EGR_BYTE: Counts eEgress bytes
 * @DPSW_CNT_EGR_FRAME_DISCARD: Counts discarded egress frames
 * @DPSW_CNT_EGR_STP_FRAME_DISCARD: Counts egress STP discarded frames
 * @DPSW_CNT_ING_NO_BUFFER_DISCARD: Counts ingress no buffer discarded frames
 */
enum dpsw_counter {
	DPSW_CNT_ING_FRAME = 0x0,
	DPSW_CNT_ING_BYTE = 0x1,
	DPSW_CNT_ING_FLTR_FRAME = 0x2,
	DPSW_CNT_ING_FRAME_DISCARD = 0x3,
	DPSW_CNT_ING_MCAST_FRAME = 0x4,
	DPSW_CNT_ING_MCAST_BYTE = 0x5,
	DPSW_CNT_ING_BCAST_FRAME = 0x6,
	DPSW_CNT_ING_BCAST_BYTES = 0x7,
	DPSW_CNT_EGR_FRAME = 0x8,
	DPSW_CNT_EGR_BYTE = 0x9,
	DPSW_CNT_EGR_FRAME_DISCARD = 0xa,
	DPSW_CNT_EGR_STP_FRAME_DISCARD = 0xb,
	DPSW_CNT_ING_NO_BUFFER_DISCARD = 0xc,
};

int dpsw_if_get_counter(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint16_t if_id,
			enum dpsw_counter type,
			uint64_t *counter);

int dpsw_if_set_counter(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint16_t if_id,
			enum dpsw_counter type,
			uint64_t counter);

/**
 * Maximum number of TC
 */
#define DPSW_MAX_TC             8

/**
 * enum dpsw_priority_selector - User priority
 * @DPSW_UP_PCP: Priority Code Point (PCP): a 3-bit field which
 *				 refers to the IEEE 802.1p priority.
 * @DPSW_UP_DSCP: Differentiated services Code Point (DSCP): 6 bit
 *				field from IP header
 */
enum dpsw_priority_selector {
	DPSW_UP_PCP = 0,
	DPSW_UP_DSCP = 1
};

/**
 * enum dpsw_schedule_mode - Traffic classes scheduling
 * @DPSW_SCHED_STRICT_PRIORITY: schedule strict priority
 * @DPSW_SCHED_WEIGHTED: schedule based on token bucket created algorithm
 */
enum dpsw_schedule_mode {
	DPSW_SCHED_STRICT_PRIORITY,
	DPSW_SCHED_WEIGHTED
};

/**
 * struct dpsw_tx_schedule_cfg - traffic class configuration
 * @mode: Strict or weight-based scheduling
 * @delta_bandwidth: weighted Bandwidth in range from 100 to 10000
 */
struct dpsw_tx_schedule_cfg {
	enum dpsw_schedule_mode mode;
	uint16_t delta_bandwidth;
};

/**
 * struct dpsw_tx_selection_cfg - Mapping user priority into traffic
 *					class configuration
 * @priority_selector: Source for user priority regeneration
 * @tc_id: The Regenerated User priority that the incoming
 *				User Priority is mapped to for this interface
 * @tc_sched: Traffic classes configuration
 */
struct dpsw_tx_selection_cfg {
	enum dpsw_priority_selector priority_selector;
	uint8_t tc_id[DPSW_MAX_PRIORITIES];
	struct dpsw_tx_schedule_cfg tc_sched[DPSW_MAX_TC];
};

int dpsw_if_set_tx_selection(struct fsl_mc_io *mc_io,
			     uint32_t cmd_flags,
			     uint16_t token,
			     uint16_t if_id,
			     const struct dpsw_tx_selection_cfg *cfg);

/**
 * enum dpsw_reflection_filter - Filter type for frames to reflect
 * @DPSW_REFLECTION_FILTER_INGRESS_ALL: Reflect all frames
 * @DPSW_REFLECTION_FILTER_INGRESS_VLAN: Reflect only frames belong to
 *			particular VLAN defined by vid parameter
 *
 */
enum dpsw_reflection_filter {
	DPSW_REFLECTION_FILTER_INGRESS_ALL = 0,
	DPSW_REFLECTION_FILTER_INGRESS_VLAN = 1
};

/**
 * struct dpsw_reflection_cfg - Structure representing reflection information
 * @filter: Filter type for frames to reflect
 * @vlan_id: Vlan Id to reflect; valid only when filter type is
 *		DPSW_INGRESS_VLAN
 */
struct dpsw_reflection_cfg {
	enum dpsw_reflection_filter filter;
	uint16_t vlan_id;
};

int dpsw_if_add_reflection(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint16_t if_id,
			   const struct dpsw_reflection_cfg *cfg);

int dpsw_if_remove_reflection(struct fsl_mc_io *mc_io,
			      uint32_t cmd_flags,
			      uint16_t token,
			      uint16_t if_id,
			      const struct dpsw_reflection_cfg *cfg);

/**
 * enum dpsw_metering_mode - Metering modes
 * @DPSW_METERING_MODE_NONE: metering disabled
 * @DPSW_METERING_MODE_RFC2698: RFC 2698
 * @DPSW_METERING_MODE_RFC4115: RFC 4115
 */
enum dpsw_metering_mode {
	DPSW_METERING_MODE_NONE = 0,
	DPSW_METERING_MODE_RFC2698,
	DPSW_METERING_MODE_RFC4115
};

/**
 * enum dpsw_metering_unit - Metering count
 * @DPSW_METERING_UNIT_BYTES: count bytes
 * @DPSW_METERING_UNIT_FRAMES: count frames
 */
enum dpsw_metering_unit {
	DPSW_METERING_UNIT_BYTES = 0,
	DPSW_METERING_UNIT_FRAMES
};

/**
 * struct dpsw_metering_cfg - Metering configuration
 * @mode: metering modes
 * @units: Bytes or frame units
 * @cir: Committed information rate (CIR) in Kbits/s
 * @eir: Peak information rate (PIR) Kbit/s  rfc2698
 *	 Excess information rate (EIR) Kbit/s rfc4115
 * @cbs: Committed burst size (CBS) in bytes
 * @ebs: Peak burst size (PBS) in bytes for rfc2698
 *       Excess bust size (EBS) in bytes rfc4115
 *
 */
struct dpsw_metering_cfg {
	enum dpsw_metering_mode mode;
	enum dpsw_metering_unit units;
	uint32_t cir;
	uint32_t eir;
	uint32_t cbs;
	uint32_t ebs;
};

int dpsw_if_set_flooding_metering(struct fsl_mc_io *mc_io,
				  uint32_t cmd_flags,
				  uint16_t token,
				  uint16_t if_id,
				  const struct dpsw_metering_cfg *cfg);

int dpsw_if_set_metering(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint16_t if_id,
			 uint8_t tc_id,
			 const struct dpsw_metering_cfg *cfg);

/**
 * enum dpsw_early_drop_unit - DPSW early drop unit
 * @DPSW_EARLY_DROP_UNIT_BYTE: count bytes
 * @DPSW_EARLY_DROP_UNIT_FRAMES: count frames
 */
enum dpsw_early_drop_unit {
	DPSW_EARLY_DROP_UNIT_BYTE = 0,
	DPSW_EARLY_DROP_UNIT_FRAMES
};

/**
 * enum dpsw_early_drop_mode - DPSW early drop mode
 * @DPSW_EARLY_DROP_MODE_NONE: early drop is disabled
 * @DPSW_EARLY_DROP_MODE_TAIL: early drop in taildrop mode
 * @DPSW_EARLY_DROP_MODE_WRED: early drop in WRED mode
 */
enum dpsw_early_drop_mode {
	DPSW_EARLY_DROP_MODE_NONE = 0,
	DPSW_EARLY_DROP_MODE_TAIL,
	DPSW_EARLY_DROP_MODE_WRED
};

/**
 * struct dpsw_wred_cfg - WRED configuration
 * @max_threshold: maximum threshold that packets may be discarded. Above this
 *	  threshold all packets are discarded; must be less than 2^39;
 *	  approximated to be expressed as (x+256)*2^(y-1) due to HW
 *	    implementation.
 * @min_threshold: minimum threshold that packets may be discarded at
 * @drop_probability: probability that a packet will be discarded (1-100,
 *	associated with the maximum threshold)
 */
struct dpsw_wred_cfg {
	uint64_t min_threshold;
	uint64_t max_threshold;
	uint8_t drop_probability;
};

/**
 * struct dpsw_early_drop_cfg - early-drop configuration
 * @drop_mode: drop mode
 * @units: count units
 * @yellow: WRED - 'yellow' configuration
 * @green: WRED - 'green' configuration
 * @tail_drop_threshold: tail drop threshold
 */
struct dpsw_early_drop_cfg {
	enum dpsw_early_drop_mode drop_mode;
	enum dpsw_early_drop_unit units;
	struct dpsw_wred_cfg yellow;
	struct dpsw_wred_cfg green;
	uint32_t tail_drop_threshold;
};

void dpsw_prepare_early_drop(const struct dpsw_early_drop_cfg *cfg,
			     uint8_t *early_drop_buf);

int dpsw_if_set_early_drop(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint16_t if_id,
			   uint8_t tc_id,
			   uint64_t early_drop_iova);

/**
 * struct dpsw_custom_tpid_cfg - Structure representing tag Protocol identifier
 * @tpid: An additional tag protocol identifier
 */
struct dpsw_custom_tpid_cfg {
	uint16_t tpid;
};

int dpsw_add_custom_tpid(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 const struct dpsw_custom_tpid_cfg *cfg);

int dpsw_remove_custom_tpid(struct fsl_mc_io *mc_io,
			    uint32_t cmd_flags,
			    uint16_t token,
			    const struct dpsw_custom_tpid_cfg *cfg);

int dpsw_if_enable(struct fsl_mc_io *mc_io,
		   uint32_t cmd_flags,
		   uint16_t token,
		   uint16_t if_id);

int dpsw_if_disable(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    uint16_t if_id);

/**
 * struct dpsw_if_attr - Structure representing DPSW interface attributes
 * @num_tcs: Number of traffic classes
 * @rate: Transmit rate in bits per second
 * @options: Interface configuration options (bitmap)
 * @enabled: Indicates if interface is enabled
 * @accept_all_vlan: The device discards/accepts incoming frames
 *		for VLANs that do not include this interface
 * @admit_untagged: When set to 'DPSW_ADMIT_ONLY_VLAN_TAGGED', the device
 *		discards untagged frames or priority-tagged frames received on
 *		this interface;
 *		When set to 'DPSW_ADMIT_ALL', untagged frames or priority-
 *		tagged frames received on this interface are accepted
 * @qdid: control frames transmit qdid
 */
struct dpsw_if_attr {
	uint8_t num_tcs;
	uint32_t rate;
	uint32_t options;
	int enabled;
	int accept_all_vlan;
	enum dpsw_accepted_frames admit_untagged;
	uint16_t qdid;
};

int dpsw_if_get_attributes(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint16_t if_id,
			   struct dpsw_if_attr *attr);

int dpsw_if_set_max_frame_length(struct fsl_mc_io *mc_io,
				 uint32_t cmd_flags,
				 uint16_t token,
				 uint16_t if_id,
				 uint16_t frame_length);

int dpsw_if_get_max_frame_length(struct fsl_mc_io *mc_io,
				 uint32_t cmd_flags,
				 uint16_t token,
				 uint16_t if_id,
				 uint16_t *frame_length);

/**
 * struct dpsw_vlan_cfg - VLAN Configuration
 * @fdb_id: Forwarding Data Base
 */
struct dpsw_vlan_cfg {
	uint16_t fdb_id;
};

int dpsw_vlan_add(struct fsl_mc_io *mc_io,
		  uint32_t cmd_flags,
		  uint16_t token,
		  uint16_t vlan_id,
		  const struct dpsw_vlan_cfg *cfg);

/**
 * struct dpsw_vlan_if_cfg - Set of VLAN Interfaces
 * @num_ifs: The number of interfaces that are assigned to the egress
 *		list for this VLAN
 * @if_id: The set of interfaces that are
 *		assigned to the egress list for this VLAN
 */
struct dpsw_vlan_if_cfg {
	uint16_t num_ifs;
	uint16_t if_id[DPSW_MAX_IF];
};

int dpsw_vlan_add_if(struct fsl_mc_io *mc_io,
		     uint32_t cmd_flags,
		     uint16_t token,
		     uint16_t vlan_id,
		     const struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_add_if_untagged(struct fsl_mc_io *mc_io,
			      uint32_t cmd_flags,
			      uint16_t token,
			      uint16_t vlan_id,
			      const struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_add_if_flooding(struct fsl_mc_io *mc_io,
			      uint32_t cmd_flags,
			      uint16_t token,
			      uint16_t vlan_id,
			      const struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_remove_if(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint16_t vlan_id,
			const struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_remove_if_untagged(struct fsl_mc_io *mc_io,
				 uint32_t cmd_flags,
				 uint16_t token,
				 uint16_t vlan_id,
				 const struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_remove_if_flooding(struct fsl_mc_io *mc_io,
				 uint32_t cmd_flags,
				 uint16_t token,
				 uint16_t vlan_id,
				 const struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_remove(struct fsl_mc_io *mc_io,
		     uint32_t cmd_flags,
		     uint16_t token,
		     uint16_t vlan_id);

/**
 * struct dpsw_vlan_attr - VLAN attributes
 * @fdb_id: Associated FDB ID
 * @num_ifs: Number of interfaces
 * @num_untagged_ifs: Number of untagged interfaces
 * @num_flooding_ifs: Number of flooding interfaces
 */
struct dpsw_vlan_attr {
	uint16_t fdb_id;
	uint16_t num_ifs;
	uint16_t num_untagged_ifs;
	uint16_t num_flooding_ifs;
};

int dpsw_vlan_get_attributes(struct fsl_mc_io *mc_io,
			     uint32_t cmd_flags,
			     uint16_t token,
			     uint16_t vlan_id,
			     struct dpsw_vlan_attr *attr);

int dpsw_vlan_get_if(struct fsl_mc_io *mc_io,
		     uint32_t cmd_flags,
		     uint16_t token,
		     uint16_t vlan_id,
		     struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_get_if_flooding(struct fsl_mc_io *mc_io,
			      uint32_t cmd_flags,
			      uint16_t token,
			      uint16_t vlan_id,
			      struct dpsw_vlan_if_cfg *cfg);

int dpsw_vlan_get_if_untagged(struct fsl_mc_io *mc_io,
			      uint32_t cmd_flags,
			      uint16_t token,
			      uint16_t vlan_id,
			      struct dpsw_vlan_if_cfg *cfg);

/**
 * struct dpsw_fdb_cfg  - FDB Configuration
 * @num_fdb_entries: Number of FDB entries
 * @fdb_aging_time: Aging time in seconds
 */
struct dpsw_fdb_cfg {
	uint16_t num_fdb_entries;
	uint16_t fdb_aging_time;
};

int dpsw_fdb_add(struct fsl_mc_io *mc_io,
		 uint32_t cmd_flags,
		 uint16_t token,
		 uint16_t *fdb_id,
		 const struct dpsw_fdb_cfg *cfg);

int dpsw_fdb_remove(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    uint16_t fdb_id);

/**
 * enum dpsw_fdb_entry_type - FDB Entry type - Static/Dynamic
 * @DPSW_FDB_ENTRY_STATIC: Static entry
 * @DPSW_FDB_ENTRY_DINAMIC: Dynamic entry
 */
enum dpsw_fdb_entry_type {
	DPSW_FDB_ENTRY_STATIC = 0,
	DPSW_FDB_ENTRY_DINAMIC = 1
};

/**
 * struct dpsw_fdb_unicast_cfg - Unicast entry configuration
 * @type: Select static or dynamic entry
 * @mac_addr: MAC address
 * @if_egress: Egress interface ID
 */
struct dpsw_fdb_unicast_cfg {
	enum dpsw_fdb_entry_type type;
	uint8_t mac_addr[6];
	uint16_t if_egress;
};

int dpsw_fdb_add_unicast(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint16_t fdb_id,
			 const struct dpsw_fdb_unicast_cfg *cfg);

int dpsw_fdb_get_unicast(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint16_t fdb_id,
			 struct dpsw_fdb_unicast_cfg *cfg);

int dpsw_fdb_remove_unicast(struct fsl_mc_io *mc_io,
			    uint32_t cmd_flags,
			    uint16_t token,
			    uint16_t fdb_id,
			    const struct dpsw_fdb_unicast_cfg *cfg);

/**
 * struct fdb_dump_entry - fdb snapshot entry
 * @mac_addr: MAC address
 * @type: bit0 - DINAMIC(1)/STATIC(0), bit1 - UNICAST(1)/MULTICAST(0)
 * @if_info: unicast - egress interface, multicast - number of egress interfaces
 * @if_mask: multicast - egress interface mask
 */
struct fdb_dump_entry {
	uint8_t mac_addr[6];
	uint8_t type;
	uint8_t if_info;
	uint8_t if_mask[8];
};

int dpsw_fdb_dump(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint16_t fdb_id,
			 uint64_t iova_addr,
			 uint32_t iova_size,
			 uint16_t *num_entries);

/**
 * struct dpsw_fdb_multicast_cfg - Multi-cast entry configuration
 * @type: Select static or dynamic entry
 * @mac_addr: MAC address
 * @num_ifs: Number of external and internal interfaces
 * @if_id: Egress interface IDs
 */
struct dpsw_fdb_multicast_cfg {
	enum dpsw_fdb_entry_type type;
	uint8_t mac_addr[6];
	uint16_t num_ifs;
	uint16_t if_id[DPSW_MAX_IF];
};

int dpsw_fdb_add_multicast(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint16_t fdb_id,
			   const struct dpsw_fdb_multicast_cfg *cfg);

int dpsw_fdb_get_multicast(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint16_t fdb_id,
			   struct dpsw_fdb_multicast_cfg *cfg);

int dpsw_fdb_remove_multicast(struct fsl_mc_io *mc_io,
			      uint32_t cmd_flags,
			      uint16_t token,
			      uint16_t fdb_id,
			      const struct dpsw_fdb_multicast_cfg *cfg);

/**
 * enum dpsw_fdb_learning_mode - Auto-learning modes
 * @DPSW_FDB_LEARNING_MODE_DIS: Disable Auto-learning
 * @DPSW_FDB_LEARNING_MODE_HW: Enable HW auto-Learning
 * @DPSW_FDB_LEARNING_MODE_NON_SECURE: Enable None secure learning by CPU
 * @DPSW_FDB_LEARNING_MODE_SECURE: Enable secure learning by CPU
 *
 *	NONE - SECURE LEARNING
 *	SMAC found	DMAC found	CTLU Action
 *	v		v	Forward frame to
 *						1.  DMAC destination
 *	-		v	Forward frame to
 *						1.  DMAC destination
 *						2.  Control interface
 *	v		-	Forward frame to
 *						1.  Flooding list of interfaces
 *	-		-	Forward frame to
 *						1.  Flooding list of interfaces
 *						2.  Control interface
 *	SECURE LEARING
 *	SMAC found	DMAC found	CTLU Action
 *	v		v		Forward frame to
 *						1.  DMAC destination
 *	-		v		Forward frame to
 *						1.  Control interface
 *	v		-		Forward frame to
 *						1.  Flooding list of interfaces
 *	-		-		Forward frame to
 *						1.  Control interface
 */
enum dpsw_fdb_learning_mode {
	DPSW_FDB_LEARNING_MODE_DIS = 0,
	DPSW_FDB_LEARNING_MODE_HW = 1,
	DPSW_FDB_LEARNING_MODE_NON_SECURE = 2,
	DPSW_FDB_LEARNING_MODE_SECURE = 3
};

int dpsw_fdb_set_learning_mode(struct fsl_mc_io *mc_io,
			       uint32_t cmd_flags,
			       uint16_t token,
			       uint16_t fdb_id,
			       enum dpsw_fdb_learning_mode mode);

/**
 * struct dpsw_fdb_attr - FDB Attributes
 * @max_fdb_entries: Number of FDB entries
 * @fdb_aging_time: Aging time in seconds
 * @learning_mode: Learning mode
 * @num_fdb_mc_groups: Current number of multicast groups
 * @max_fdb_mc_groups: Maximum number of multicast groups
 */
struct dpsw_fdb_attr {
	uint16_t max_fdb_entries;
	uint16_t fdb_aging_time;
	enum dpsw_fdb_learning_mode learning_mode;
	uint16_t num_fdb_mc_groups;
	uint16_t max_fdb_mc_groups;
};

int dpsw_fdb_get_attributes(struct fsl_mc_io *mc_io,
			    uint32_t cmd_flags,
			    uint16_t token,
			    uint16_t fdb_id,
			    struct dpsw_fdb_attr *attr);

/**
 * struct dpsw_acl_cfg - ACL Configuration
 * @max_entries: Number of FDB entries
 */
struct dpsw_acl_cfg {
	uint16_t max_entries;
};

/**
 * Flag used while adding ACL entries to match on miss from FDB
 */
#define DPSW_ACL_MATCH_ON_FDB_MISS				0x80

/**
 * struct dpsw_acl_fields - ACL fields.
 * @l2_dest_mac: Destination MAC address: BPDU, Multicast, Broadcast, Unicast,
 *			slow protocols, MVRP, STP
 * @l2_source_mac: Source MAC address
 * @l2_tpid: Layer 2 (Ethernet) protocol type, used to identify the following
 *		protocols: MPLS, PTP, PFC, ARP, Jumbo frames, LLDP, IEEE802.1ae,
 *		Q-in-Q, IPv4, IPv6, PPPoE
 * @l2_pcp_dei: indicate which protocol is encapsulated in the payload
 * @l2_vlan_id: layer 2 VLAN ID
 * @l2_ether_type: layer 2 Ethernet type
 * @l3_dscp: Layer 3 differentiated services code point
 * @l3_protocol: Tells the Network layer at the destination host, to which
 *		Protocol this packet belongs to. The following protocol are
 *		supported: ICMP, IGMP, IPv4 (encapsulation), TCP, IPv6
 *		(encapsulation), GRE, PTP
 * @l3_source_ip: Source IPv4 IP
 * @l3_dest_ip: Destination IPv4 IP
 * @l4_source_port: Source TCP/UDP Port
 * @l4_dest_port: Destination TCP/UDP Port
 * @frame_flags: Field used to pass frame flags. Supported values: DPSW_ACL_MATCH_ON_FDB_MISS
 */
struct dpsw_acl_fields {
	uint8_t l2_dest_mac[6];
	uint8_t l2_source_mac[6];
	uint16_t l2_tpid;
	uint8_t l2_pcp_dei;
	uint16_t l2_vlan_id;
	uint16_t l2_ether_type;
	uint8_t l3_dscp;
	uint8_t l3_protocol;
	uint32_t l3_source_ip;
	uint32_t l3_dest_ip;
	uint16_t l4_source_port;
	uint16_t l4_dest_port;
	uint8_t frame_flags;
	uint8_t rcv_fltr_unicast_if;
};

/**
 * struct dpsw_acl_key - ACL key
 * @match: Match fields
 * @mask: Mask: b'1 - valid, b'0 don't care
 */
struct dpsw_acl_key {
	struct dpsw_acl_fields match;
	struct dpsw_acl_fields mask;
};

/**
 * enum dpsw_acl_action
 * @DPSW_ACL_ACTION_DROP: Drop frame
 * @DPSW_ACL_ACTION_REDIRECT: Redirect to certain port
 * @DPSW_ACL_ACTION_ACCEPT: Accept frame
 * @DPSW_ACL_ACTION_REDIRECT_TO_CTRL_IF: Redirect to control interface
 * @DPSW_ACL_ACTION_LOOKUP: Goto Lookup table
 */
enum dpsw_acl_action {
	DPSW_ACL_ACTION_DROP,
	DPSW_ACL_ACTION_REDIRECT,
	DPSW_ACL_ACTION_ACCEPT,
	DPSW_ACL_ACTION_REDIRECT_TO_CTRL_IF,
	DPSW_ACL_ACTION_LOOKUP
};

/**
 * enum dpsw_acl_lookup_table
 * @DPSW_ACL_LOOKUP_TBL_BCAST: Broadcast table
 * @DPSW_ACL_LOOKUP_TBL_MCAST: Multicast table
 * @DPSW_ACL_LOOKUP_TBL_UCAST: Unknown Unicast table
 */
enum dpsw_acl_lookup_table {
	DPSW_ACL_LOOKUP_TBL_BCAST,	/* Broadcast table */
	DPSW_ACL_LOOKUP_TBL_MCAST,  /* Multicast table */
	DPSW_ACL_LOOKUP_TBL_UCAST   /* Unknown Unicast table */
};

/**
 * struct dpsw_acl_result - ACL action
 * @action: Action should be taken when	ACL entry hit
 * @if_id:  Interface IDs to redirect frame. Valid only if redirect selected for
 *		 action
 * @lookup_table: Lookup Table id - Valid only if lookup selected for action
 */
struct dpsw_acl_result {
	enum dpsw_acl_action action;
	uint16_t if_id;
    enum dpsw_acl_lookup_table lookup_table;
};

/**
 * struct dpsw_acl_entry_cfg - ACL entry
 * @key_iova: I/O virtual address of DMA-able memory filled with key after call
 *				to dpsw_acl_prepare_entry_cfg()
 * @result: Required action when entry hit occurs
 * @precedence: Precedence inside ACL 0 is lowest; This priority can not change
 *		during the lifetime of a Policy. It is user responsibility to
 *		space the priorities according to consequent rule additions.
 */
struct dpsw_acl_entry_cfg {
	uint64_t key_iova;
	struct dpsw_acl_result result;
	int precedence;
};

int dpsw_acl_add(struct fsl_mc_io *mc_io,
		 uint32_t cmd_flags,
		 uint16_t token,
		 uint16_t *acl_id,
		 const struct dpsw_acl_cfg *cfg);
int dpsw_acl_remove(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    uint16_t acl_id);

void dpsw_acl_prepare_entry_cfg(const struct dpsw_acl_key *key,
				uint8_t *entry_cfg_buf);

int dpsw_acl_add_entry(struct fsl_mc_io *mc_io,
		       uint32_t cmd_flags,
		       uint16_t token,
		       uint16_t acl_id,
		       const struct dpsw_acl_entry_cfg *cfg);

int dpsw_acl_remove_entry(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint16_t acl_id,
			  const struct dpsw_acl_entry_cfg *cfg);

/**
 * struct dpsw_acl_if_cfg - List of interfaces to Associate with ACL
 * @num_ifs: Number of interfaces
 * @if_id: List of interfaces
 */
struct dpsw_acl_if_cfg {
	uint16_t num_ifs;
	uint16_t if_id[DPSW_MAX_IF];
};

int dpsw_acl_add_if(struct fsl_mc_io *mc_io,
		    uint32_t cmd_flags,
		    uint16_t token,
		    uint16_t acl_id,
		    const struct dpsw_acl_if_cfg *cfg);

int dpsw_acl_remove_if(struct fsl_mc_io *mc_io,
		       uint32_t cmd_flags,
		       uint16_t token,
		       uint16_t acl_id,
		       const struct dpsw_acl_if_cfg *cfg);

/**
 * struct dpsw_acl_attr -  ACL Attributes
 * @max_entries: Max number of ACL entries
 * @num_entries: Number of used ACL entries
 * @num_ifs: Number of interfaces associated with ACL
 */
struct dpsw_acl_attr {
	uint16_t max_entries;
	uint16_t num_entries;
	uint16_t num_ifs;
};

int dpsw_acl_get_attributes(struct fsl_mc_io *mc_io,
			    uint32_t cmd_flags,
			    uint16_t token,
			    uint16_t acl_id,
			    struct dpsw_acl_attr *attr);
/**
 * struct dpsw_ctrl_if_attr - Control interface attributes
 * @rx_fqid:		Receive FQID
 * @rx_err_fqid:	Receive error FQID
 * @tx_err_conf_fqid:	Transmit error and confirmation FQID
 */
struct dpsw_ctrl_if_attr {
	uint32_t rx_fqid;
	uint32_t rx_err_fqid;
	uint32_t tx_err_conf_fqid;
};

int dpsw_ctrl_if_get_attributes(struct fsl_mc_io *mc_io,
				uint32_t cmd_flags,
				uint16_t token,
				struct dpsw_ctrl_if_attr *attr);

/**
 * Maximum number of DPBP
 */
#define DPSW_MAX_DPBP     8

/**
 * struct dpsw_ctrl_if_pools_cfg - Control interface buffer pools configuration
 * @num_dpbp: Number of DPBPs
 * @pools: Array of buffer pools parameters; The number of valid entries
 *	must match 'num_dpbp' value
 * @pools.dpbp_id: DPBP object ID
 * @pools.buffer_size: Buffer size
 * @pools.backup_pool: Backup pool
 */
struct dpsw_ctrl_if_pools_cfg {
	uint8_t num_dpbp;
	struct {
		int dpbp_id;
		uint16_t buffer_size;
		int backup_pool;
	} pools[DPSW_MAX_DPBP];
};

int dpsw_ctrl_if_set_pools(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   const struct dpsw_ctrl_if_pools_cfg *cfg);

#define DPSW_CTRL_IF_QUEUE_OPT_USER_CTX		0x00000001
#define DPSW_CTRL_IF_QUEUE_OPT_DEST		0x00000002

enum dpsw_queue_type {
	DPSW_QUEUE_RX,
	DPSW_QUEUE_TX_ERR_CONF,
	DPSW_QUEUE_RX_ERR,
};

enum dpsw_ctrl_if_dest {
	DPSW_CTRL_IF_DEST_NONE = 0,
	DPSW_CTRL_IF_DEST_DPIO = 1,
};

struct dpsw_ctrl_if_dest_cfg {
	enum dpsw_ctrl_if_dest dest_type;
	int dest_id;
	uint8_t priority;
};

struct dpsw_ctrl_if_queue_cfg {
	uint32_t options;
	uint64_t user_ctx;
	struct dpsw_ctrl_if_dest_cfg dest_cfg;
};

int dpsw_ctrl_if_set_queue(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   enum dpsw_queue_type qtype,
			   const struct dpsw_ctrl_if_queue_cfg *cfg);

int dpsw_ctrl_if_enable(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token);

int dpsw_ctrl_if_disable(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token);

int dpsw_get_api_version(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t *major_ver,
			   uint16_t *minor_ver);

struct dpsw_lag_cfg {
	uint8_t group_id;
	uint8_t num_ifs;
	uint8_t if_id[8];
};

int dpsw_lag_set(struct fsl_mc_io *mc_io,
				uint32_t cmd_flags,
				uint16_t token,
				const struct dpsw_lag_cfg *cfg);

int dpsw_lag_get_cfg(struct fsl_mc_io *mc_io,
				uint32_t cmd_flags,
                uint16_t token,
				uint8_t group_id,
                struct dpsw_lag_cfg *cfg);

int dpsw_if_get_port_mac_addr(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
			      uint16_t if_id, uint8_t mac_addr[6]);

enum dpsw_congestion_unit {
	DPSW_TAIDLROP_DROP_UNIT_BYTE = 0,
	DPSW_TAILDROP_DROP_UNIT_FRAMES,
	DPSW_TAILDROP_DROP_UNIT_BUFFERS
};

/**
 * struct dpsw_taildrop_cfg - interface taildrop configuration
 * @enable - enable (1 ) or disable (0) taildrop
 * @units - taildrop units
 * @threshold - taildtop threshold
 */
struct dpsw_taildrop_cfg {
	char enable;
	enum dpsw_congestion_unit units;
	uint32_t threshold;
};

int dpsw_if_set_taildrop(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
			      uint16_t if_id, uint8_t tc, struct dpsw_taildrop_cfg *cfg);

int dpsw_if_get_taildrop(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
			      uint16_t if_id, uint8_t tc, struct dpsw_taildrop_cfg *cfg);

enum dpsw_table_type {
	DPSW_FDB_TABLE = 1,
	DPSW_VLAN_ING_TABLE = 2,
	DPSW_VLAN_EGR_TABLE = 3,
	DPSW_ACL_TABLE	= 4,
	DPSW_BCAST_TABLE = 5,
};

int dpsw_dump_table(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
			 	 uint16_t table_type, uint16_t table_index,  uint64_t iova_addr,
				 uint32_t iova_size, uint16_t *num_entries);

/**
 * DPSW errors
 */

/**
 * Discard error. When set all discarded frames in wriop will be enqueued to
 * error queue. To be used in dpsw_set_errors_behavior() only if error_action
 * parameter is set to DPSW_ERROR_ACTION_SEND_TO_ERROR_QUEUE.
 */

#define DPSW_ERROR_DISC			0x80000000

/**
 * Extract out of frame header error
 */
#define DPSW_ERROR_MS			0x40000000
#define DPSW_ERROR_PTP			0x08000000
/* Ethernet multicast frame */
#define DPSW_ERROR_MC			0x04000000
/* Ethernet broadcast frame */
#define DPSW_ERROR_BC			0x02000000
#define DPSW_ERROR_KSE			0x00040000
#define DPSW_ERROR_EOFHE		0x00020000
#define DPSW_ERROR_MNLE			0x00010000
#define DPSW_ERROR_TIDE			0x00008000
#define DPSW_ERROR_PIEE			0x00004000
/**
 * Frame length error
 */
#define DPSW_ERROR_FLE			0x00002000
/**
 * Frame physical error
 */
#define DPSW_ERROR_FPE			0x00001000

#define DPSW_ERROR_PTE			0x00000080
#define DPSW_ERROR_ISP			0x00000040
/**
 * Parsing header error
 */
#define DPSW_ERROR_PHE			0x00000020

#define DPSW_ERROR_BLE			0x00000010
/**
 * Parser L3 checksum error
 */

#define DPSW_ERROR_L3CV			0x00000008

#define DPSW_ERROR_L3CE			0x00000004
/**
 * Parser L4 checksum error
 */

#define DPSW_ERROR_L4CV			0x00000002

#define DPSW_ERROR_L4CE			0x00000001

/**
 * enum dpsw_error_action - Defines DPSW behavior for errors
 * @DPSW_ERROR_ACTION_DISCARD: Discard the frame
 * @DPSW_ERROR_ACTION_CONTINUE: Continue with the normal flow
 */
enum dpsw_error_action {
	DPSW_ERROR_ACTION_DISCARD = 0,
	DPSW_ERROR_ACTION_CONTINUE = 1
};

/**
 * struct dpsw_error_cfg - Structure representing DPSW errors treatment
 * @errors:			Errors mask; use 'DPSW_ERROR__<X>
 * @error_action:		The desired action for the errors mask
 * @set_frame_annotation:	Set to '1' to mark the errors in frame
 *				annotation status (FAS); relevant only
 *				for the non-discard action
 */
struct dpsw_error_cfg {
	uint32_t errors;
	enum dpsw_error_action error_action;
	int set_frame_annotation;
};

int dpsw_if_set_errors_behavior(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
			      uint16_t if_id, struct dpsw_error_cfg *cfg);

/**
 * struct dpsw_rcv_filter_if_cfg - List of interfaces to Associate with ACL
 * @num_ifs: Number of interfaces
 * @if_id: List of interfaces
 */
struct dpsw_rcv_filter_if_cfg {
	uint16_t num_ifs;
	uint16_t if_id[DPSW_MAX_IF];
};

int dpsw_set_rcv_filter_unicast_if(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
		const struct dpsw_rcv_filter_if_cfg *cfg);

#define DPSW_IF_ISOLATE_IF_UNICAST_DISABLE		0xFFFFFFFF

int dpsw_if_isolate_if_unicast(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
		uint16_t acl_id, uint16_t if_src, uint16_t if_dst, uint32_t precedence);

#endif /* __FSL_DPSW_H */
