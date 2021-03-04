/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2021 NXP
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
#ifndef _FSL_DPDMUX_CMD_H
#define _FSL_DPDMUX_CMD_H

/* DPDMUX Version */
#define DPDMUX_VER_MAJOR		6
#define DPDMUX_VER_MINOR		9

#define DPDMUX_CMD_BASE_VERSION		1
#define DPDMUX_CMD_VERSION_2		2
#define DPDMUX_CMD_VERSION_3		3
#define DPDMUX_CMD_VERSION_4		4
#define DPDMUX_CMD_ID_OFFSET		4

#define DPDMUX_CMD(id)	((id << DPDMUX_CMD_ID_OFFSET) | DPDMUX_CMD_BASE_VERSION)
#define DPDMUX_CMD_V2(id)	(((id) << DPDMUX_CMD_ID_OFFSET) | DPDMUX_CMD_VERSION_2)
#define DPDMUX_CMD_V3(id)	(((id) << DPDMUX_CMD_ID_OFFSET) | DPDMUX_CMD_VERSION_3)
#define DPDMUX_CMD_V4(id)	(((id) << DPDMUX_CMD_ID_OFFSET) | DPDMUX_CMD_VERSION_4)

/* Command IDs */
#define DPDMUX_CMDID_CLOSE			DPDMUX_CMD(0x800)
#define DPDMUX_CMDID_OPEN			DPDMUX_CMD(0x806)
#define DPDMUX_CMDID_CREATE			DPDMUX_CMD_V4(0x906)
#define DPDMUX_CMDID_DESTROY			DPDMUX_CMD(0x986)
#define DPDMUX_CMDID_GET_API_VERSION		DPDMUX_CMD(0xa06)

#define DPDMUX_CMDID_ENABLE			DPDMUX_CMD(0x002)
#define DPDMUX_CMDID_DISABLE			DPDMUX_CMD(0x003)
#define DPDMUX_CMDID_GET_ATTR			DPDMUX_CMD_V2(0x004)
#define DPDMUX_CMDID_RESET			DPDMUX_CMD(0x005)
#define DPDMUX_CMDID_IS_ENABLED			DPDMUX_CMD(0x006)

#define DPDMUX_CMDID_SET_IRQ_ENABLE		DPDMUX_CMD(0x012)
#define DPDMUX_CMDID_GET_IRQ_ENABLE		DPDMUX_CMD(0x013)
#define DPDMUX_CMDID_SET_IRQ_MASK		DPDMUX_CMD(0x014)
#define DPDMUX_CMDID_GET_IRQ_MASK		DPDMUX_CMD(0x015)
#define DPDMUX_CMDID_GET_IRQ_STATUS		DPDMUX_CMD(0x016)
#define DPDMUX_CMDID_CLEAR_IRQ_STATUS		DPDMUX_CMD(0x017)

#define DPDMUX_CMDID_SET_MAX_FRAME_LENGTH	DPDMUX_CMD(0x0a1)
#define DPDMUX_CMDID_GET_MAX_FRAME_LENGTH	DPDMUX_CMD(0x0a2)

#define DPDMUX_CMDID_UL_RESET_COUNTERS		DPDMUX_CMD(0x0a3)

#define DPDMUX_CMDID_IF_SET_ACCEPTED_FRAMES	DPDMUX_CMD(0x0a7)
#define DPDMUX_CMDID_IF_GET_ATTR		DPDMUX_CMD(0x0a8)
#define DPDMUX_CMDID_IF_ENABLE			DPDMUX_CMD(0x0a9)
#define DPDMUX_CMDID_IF_DISABLE			DPDMUX_CMD(0x0aa)

#define DPDMUX_CMDID_IF_ADD_L2_RULE		DPDMUX_CMD(0x0b0)
#define DPDMUX_CMDID_IF_REMOVE_L2_RULE		DPDMUX_CMD(0x0b1)
#define DPDMUX_CMDID_IF_GET_COUNTER		DPDMUX_CMD(0x0b2)
#define DPDMUX_CMDID_IF_SET_LINK_CFG		DPDMUX_CMD_V2(0x0b3)
#define DPDMUX_CMDID_IF_GET_LINK_STATE		DPDMUX_CMD_V2(0x0b4)

#define DPDMUX_CMDID_SET_CUSTOM_KEY		DPDMUX_CMD(0x0b5)
#define DPDMUX_CMDID_ADD_CUSTOM_CLS_ENTRY	DPDMUX_CMD_V2(0x0b6)
#define DPDMUX_CMDID_REMOVE_CUSTOM_CLS_ENTRY	DPDMUX_CMD(0x0b7)

#define DPDMUX_CMDID_IF_SET_DEFAULT		DPDMUX_CMD(0x0b8)
#define DPDMUX_CMDID_IF_GET_DEFAULT		DPDMUX_CMD(0x0b9)

#define DPDMUX_CMDID_SET_RESETABLE		DPDMUX_CMD(0x0ba)
#define DPDMUX_CMDID_GET_RESETABLE		DPDMUX_CMD(0x0bb)

#define DPDMUX_CMDID_IF_SET_TAILDROP		DPDMUX_CMD(0x0bc)
#define DPDMUX_CMDID_IF_GET_TAILDROP		DPDMUX_CMD(0x0bd)

#define DPDMUX_CMDID_DUMP_TABLE           DPDMUX_CMD(0x0be)

#define DPDMUX_CMDID_SET_ERRORS_BEHAVIOR	DPDMUX_CMD(0x0bf)


#define DPDMUX_MASK(field)        \
	GENMASK(DPDMUX_##field##_SHIFT + DPDMUX_##field##_SIZE - 1, \
		DPDMUX_##field##_SHIFT)
#define dpdmux_set_field(var, field, val) \
	((var) |= (((val) << DPDMUX_##field##_SHIFT) & DPDMUX_MASK(field)))
#define dpdmux_get_field(var, field)      \
	(((var) & DPDMUX_MASK(field)) >> DPDMUX_##field##_SHIFT)

#pragma pack(push, 1)
struct dpdmux_cmd_open {
	uint32_t dpdmux_id;
};

struct dpdmux_cmd_create {
	uint8_t method;
	uint8_t manip;
	uint16_t num_ifs;
	uint16_t default_if;
	uint16_t pad;

	uint16_t adv_max_dmat_entries;
	uint16_t adv_max_mc_groups;
	uint16_t adv_max_vlan_ids;
	uint16_t mem_size;

	uint64_t options;
};

struct dpdmux_cmd_destroy {
	uint32_t dpdmux_id;
};

#define DPDMUX_ENABLE_SHIFT	0
#define DPDMUX_ENABLE_SIZE	1
#define DPDMUX_IS_DEFAULT_SHIFT		1
#define DPDMUX_IS_DEFAULT_SIZE		1

struct dpdmux_rsp_is_enabled {
	uint8_t en;
};

struct dpdmux_cmd_set_irq_enable {
	uint8_t enable;
	uint8_t pad[3];
	uint8_t irq_index;
};

struct dpdmux_cmd_get_irq_enable {
	uint32_t pad;
	uint8_t irq_index;
};

struct dpdmux_rsp_get_irq_enable {
	uint8_t enable;
};

struct dpdmux_cmd_set_irq_mask {
	uint32_t mask;
	uint8_t irq_index;
};

struct dpdmux_cmd_get_irq_mask {
	uint32_t pad;
	uint8_t irq_index;
};

struct dpdmux_rsp_get_irq_mask {
	uint32_t mask;
};

struct dpdmux_cmd_get_irq_status {
	uint32_t status;
	uint8_t irq_index;
};

struct dpdmux_rsp_get_irq_status {
	uint32_t status;
};

struct dpdmux_cmd_clear_irq_status {
	uint32_t status;
	uint8_t irq_index;
};

struct dpdmux_rsp_get_attr {
	uint8_t method;
	uint8_t manip;
	uint16_t num_ifs;
	uint16_t mem_size;
	uint16_t default_if;

	uint64_t pad1;

	uint32_t id;
	uint32_t pad2;

	uint64_t options;
};

struct dpdmux_cmd_set_max_frame_length {
	uint16_t max_frame_length;
};

struct dpdmux_cmd_get_max_frame_len {
	uint16_t if_id;
};

struct dpdmux_rsp_get_max_frame_len {
	uint16_t max_len;
};

#define DPDMUX_ACCEPTED_FRAMES_TYPE_SHIFT	0
#define DPDMUX_ACCEPTED_FRAMES_TYPE_SIZE	4
#define DPDMUX_UNACCEPTED_FRAMES_ACTION_SHIFT	4
#define DPDMUX_UNACCEPTED_FRAMES_ACTION_SIZE	4

struct dpdmux_cmd_if_set_accepted_frames {
	uint16_t if_id;
	uint8_t frames_options;
};

struct dpdmux_cmd_if {
	uint16_t if_id;
};

struct dpdmux_rsp_if_get_attr {
	uint8_t pad[3];
	uint8_t enabled;
	uint8_t pad1[3];
	uint8_t accepted_frames_type;
	uint32_t rate;
};

struct dpdmux_cmd_if_l2_rule {
	uint16_t if_id;
	uint8_t mac_addr5;
	uint8_t mac_addr4;
	uint8_t mac_addr3;
	uint8_t mac_addr2;
	uint8_t mac_addr1;
	uint8_t mac_addr0;

	uint32_t pad;
	uint16_t vlan_id;
};

struct dpdmux_cmd_if_get_counter {
	uint16_t if_id;
	uint8_t counter_type;
};

struct dpdmux_rsp_if_get_counter {
	uint64_t pad;
	uint64_t counter;
};

struct dpdmux_cmd_if_set_link_cfg {
	uint16_t if_id;
	uint16_t pad[3];

	uint32_t rate;
	uint32_t pad1;

	uint64_t options;
	uint64_t advertising;
};

struct dpdmux_cmd_if_get_link_state {
	uint16_t if_id;
};

#define DPDMUX_UP_SHIFT				0
#define DPDMUX_UP_SIZE				1
#define DPDMUX_STATE_VALID_SHIFT	1
#define DPDMUX_STATE_VALID_SIZE		1
struct dpdmux_rsp_if_get_link_state {
	uint32_t pad;
	uint8_t up;
	uint8_t pad1[3];

	uint32_t rate;
	uint32_t pad2;

	uint64_t options;
	uint64_t supported;
	uint64_t advertising;
};

struct dpdmux_rsp_get_api_version {
	uint16_t major;
	uint16_t minor;
};

struct dpdmux_set_custom_key {
	uint64_t pad[6];
	uint64_t key_cfg_iova;
};

struct dpdmux_cmd_add_custom_cls_entry {
	uint8_t pad[3];
	uint8_t key_size;
	uint16_t entry_index;
	uint16_t dest_if;
	uint64_t key_iova;
	uint64_t mask_iova;
};

struct dpdmux_cmd_remove_custom_cls_entry {
	uint8_t pad[3];
	uint8_t key_size;
	uint32_t pad1;
	uint64_t key_iova;
	uint64_t mask_iova;
};

#define DPDMUX_SKIP_RESET_FLAGS_SHIFT    0
#define DPDMUX_SKIP_RESET_FLAGS_SIZE     3

struct dpdmux_cmd_set_skip_reset_flags {
	uint8_t skip_reset_flags;
};

struct dpdmux_rsp_get_skip_reset_flags {
	uint8_t skip_reset_flags;
};

struct dpdmux_cmd_set_taildrop {
	uint32_t	pad1;
	uint16_t	if_id;
	uint16_t	pad2;
	uint16_t	oal_en;
	uint8_t		units;
	uint8_t		pad3;
	uint32_t	threshold;
};

struct dpdmux_cmd_get_taildrop {
	uint32_t	pad1;
	uint16_t	if_id;
};

struct dpdmux_rsp_get_taildrop {
	uint16_t	pad1;
	uint16_t	pad2;
	uint16_t	if_id;
	uint16_t	pad3;
	uint16_t	oal_en;
	uint8_t		units;
	uint8_t		pad4;
	uint32_t	threshold;
};

struct dpdmux_cmd_dump_table {
	uint16_t table_type;
	uint16_t table_index;
	uint32_t pad0;
	uint64_t iova_addr;
	uint32_t iova_size;
};

struct dpdmux_rsp_dump_table {
	uint16_t num_entries;
};

struct dpdmux_dump_table_header {
	uint16_t table_type;
	uint16_t table_num_entries;
	uint16_t table_max_entries;
	uint8_t default_action;
	uint8_t match_type;
	uint8_t reserved[24];
};

struct dpdmux_dump_table_entry {
	uint8_t key[DPDMUX_MAX_KEY_SIZE];
	uint8_t mask[DPDMUX_MAX_KEY_SIZE];
	uint8_t key_action;
	uint16_t result[3];
	uint8_t reserved[21];
};

#define DPDMUX_ERROR_ACTION_SHIFT		0
#define DPDMUX_ERROR_ACTION_SIZE		4

struct dpdmux_cmd_set_errors_behavior {
	uint32_t errors;
	uint16_t flags;
	uint16_t if_id;
};

#pragma pack(pop)
#endif /* _FSL_DPDMUX_CMD_H */
