/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2018 NXP
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
#ifndef __FSL_DPAIOP_H
#define __FSL_DPAIOP_H

struct fsl_mc_io;

/** @addtogroup dpaiop Data Path AIOP API
 * Contains initialization APIs and runtime control APIs for DPAIOP
 * @{
 */

int dpaiop_open(struct fsl_mc_io *mc_io,
		uint32_t cmd_flags,
		int dpaiop_id,
		uint16_t *token);

int dpaiop_close(struct fsl_mc_io *mc_io,
		 uint32_t cmd_flags,
		 uint16_t token);

/**
 * struct dpaiop_cfg - Structure representing DPAIOP configuration
 * @aiop_id:		AIOP ID
 * @aiop_container_id:	AIOP container ID
 */
struct dpaiop_cfg {
	int aiop_id;
	int aiop_container_id;
};

int dpaiop_create(struct fsl_mc_io *mc_io,
		  uint16_t dprc_token,
		  uint32_t cmd_flags,
		  const struct dpaiop_cfg *cfg,
		  uint32_t *obj_id);

int dpaiop_destroy(struct fsl_mc_io *mc_io,
		   uint16_t dprc_token,
		   uint32_t cmd_flags,
		   uint32_t object_id);

int dpaiop_reset(struct fsl_mc_io *mc_io,
		 uint32_t cmd_flags,
		 uint16_t token);

/**
 * struct dpaiop_irq_cfg - IRQ configuration
 * @addr:	Address that must be written to signal a message-based interrupt
 * @val:	Value to write into irq_addr address
 * @irq_num:	A user defined number associated with this IRQ
 */
struct dpaiop_irq_cfg {
	     uint64_t addr;
	     uint32_t val;
	     int irq_num;
};

int dpaiop_set_irq_enable(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint8_t irq_index,
			  uint8_t en);

int dpaiop_get_irq_enable(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint8_t irq_index,
			  uint8_t *en);

int dpaiop_set_irq_mask(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint8_t irq_index,
			uint32_t mask);

int dpaiop_get_irq_mask(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint8_t irq_index,
			uint32_t *mask);

int dpaiop_get_irq_status(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint8_t irq_index,
			  uint32_t *status);

int dpaiop_clear_irq_status(struct fsl_mc_io *mc_io,
			    uint32_t cmd_flags,
			    uint16_t token,
			    uint8_t irq_index,
			    uint32_t status);

/**
 * struct dpaiop_attr - Structure representing DPAIOP attributes
 * @id:	AIOP ID
 */
struct dpaiop_attr {
	int id;
};

int dpaiop_get_attributes(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  struct dpaiop_attr *attr);

/**
 * struct dpaiop_load_cfg - AIOP load configuration
 * @options:	AIOP load options
 * @img_iova:	I/O virtual address of AIOP ELF image
 * @img_size:	Size of AIOP ELF image in memory (in bytes)
 * @tpc: TODO
 */
struct dpaiop_load_cfg {
	uint64_t options;
	uint64_t img_iova;
	uint32_t img_size;
	uint8_t tpc;
};

int dpaiop_load(struct fsl_mc_io *mc_io,
		uint32_t cmd_flags,
		uint16_t token,
		struct dpaiop_load_cfg *cfg);

#define DPAIOP_RUN_OPT_DEBUG	0x0000000000000001ULL

/**
 * struct dpaiop_run_cfg - AIOP run configuration
 * @cores_mask:	Mask of AIOP cores to run (core 0 in most significant bit)
 * @options:	Execution options (currently none defined)
 * @args_iova:	I/O virtual address of AIOP arguments
 * @args_size:	Size of AIOP arguments in memory (in bytes)
 */
struct dpaiop_run_cfg {
	uint64_t cores_mask;
	uint64_t options;
	uint64_t args_iova;
	uint32_t args_size;
};

int dpaiop_run(struct fsl_mc_io *mc_io,
	       uint32_t cmd_flags,
	       uint16_t token,
	       const struct dpaiop_run_cfg *cfg);

/**
 * struct dpaiop_sl_version - AIOP SL (Service Layer) version
 * @major:	AIOP SL major version number
 * @minor:	AIOP SL minor version number
 * @revision:	AIOP SL revision number
 */
struct dpaiop_sl_version {
	uint32_t major;
	uint32_t minor;
	uint32_t revision;
};

int dpaiop_get_sl_version(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  struct dpaiop_sl_version *version);

/**
 * AIOP states
 *
 * AIOP internal states, can be retrieved by calling dpaiop_get_state() routine
 */

/**
 * AIOP reset successfully completed.
 */
#define DPAIOP_STATE_RESET_DONE		0x00000000
/**
 * AIOP reset is ongoing.
 */
#define DPAIOP_STATE_RESET_ONGOING	0x00000001

/**
 * AIOP image loading successfully completed.
 */
#define DPAIOP_STATE_LOAD_DONE		0x00000002
/**
 * AIOP image loading is ongoing.
 */
#define DPAIOP_STATE_LOAD_ONGIONG	0x00000004
/**
 * AIOP image loading completed with error.
 */
#define DPAIOP_STATE_LOAD_ERROR		0x00000008

/**
 * Boot process of AIOP cores is ongoing.
 */
#define DPAIOP_STATE_BOOT_ONGOING	0x00000010
/**
 * Boot process of AIOP cores completed with an error.
 */
#define DPAIOP_STATE_BOOT_ERROR		0x00000020
/**
 * AIOP cores are functional and running
 */
#define DPAIOP_STATE_RUNNING		0x00000040
/** @} */

int dpaiop_get_state(struct fsl_mc_io *mc_io,
		     uint32_t cmd_flags,
		     uint16_t token,
		     uint32_t *state);

int dpaiop_set_time_of_day(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint64_t time_of_day);

int dpaiop_get_time_of_day(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint64_t *time_of_day);

int dpaiop_get_api_version(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t *major_ver,
			   uint16_t *minor_ver);

int dpaiop_set_resetable(struct fsl_mc_io *mc_io,
	     uint32_t cmd_flags,
	     uint16_t token,
		 int enable);

int dpaiop_get_resetable(struct fsl_mc_io *mc_io,
	     uint32_t cmd_flags,
	     uint16_t token,
		 int *enable);

#endif /* __FSL_DPAIOP_H */
