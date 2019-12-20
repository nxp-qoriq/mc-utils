/* Copyright 2018 NXP
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
#ifndef _FSL_DPSPARSER_CMD_H
#define _FSL_DPSPARSER_CMD_H

/* DPSPARSER last supported API version */
#define DPSPARSER_VER_MAJOR				1
#define DPSPARSER_VER_MINOR				0

#define DPSPARSER_CMD_BASE_VERSION		1
#define DPSPARSER_CMD_ID_OFFSET		4

#define DPSPARSER_CMD(id)	(((id) << DPSPARSER_CMD_ID_OFFSET) | DPSPARSER_CMD_BASE_VERSION)

/* Command IDs */
#define DPSPARSER_CMDID_CLOSE				DPSPARSER_CMD(0x800)
#define DPSPARSER_CMDID_OPEN				DPSPARSER_CMD(0x811)
#define DPSPARSER_CMDID_CREATE				DPSPARSER_CMD(0x911)
#define DPSPARSER_CMDID_DESTROY				DPSPARSER_CMD(0x991)
#define DPSPARSER_CMDID_GET_API_VERSION		DPSPARSER_CMD(0xa11)

#define DPSPARSER_CMDID_APPLY_SPB				DPSPARSER_CMD(0x118)

/* Macros for accessing command fields smaller than 1byte */
#define DPSPARSER_MASK(field)	\
	GENMASK(DPSPARSER_##field##_SHIFT + DPSPARSER_##field##_SIZE - 1, \
		DPSPARSER_##field##_SHIFT)
#define DPSPARSER_set_field(var, field, val)	\
	((var) |= (((val) << DPSPARSER_##field##_SHIFT) & DPSPARSER_MASK(field)))
#define DPSPARSER_get_field(var, field)	\
	(((var) & DPSPARSER_MASK(field)) >> DPSPARSER_##field##_SHIFT)

#pragma pack(push, 1)

struct dpsparser_cmd_destroy {
	uint32_t dpsparser_id;
};

struct dpsparser_cmd_blob_set_address {
	uint64_t blob_addr;
};

struct dpsparser_rsp_blob_report_error {
	uint16_t error;
};

struct dpsparser_rsp_get_api_version {
	uint16_t major;
	uint16_t minor;
};

#pragma pack(pop)


#endif /* _FSL_DPSPARSER_CMD_H */
