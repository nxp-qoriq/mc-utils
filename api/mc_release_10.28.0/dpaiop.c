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
#include <fsl_mc_sys.h>
#include <fsl_mc_cmd.h>
#include <fsl_dpaiop.h>
#include <fsl_dpaiop_cmd.h>

/** @addtogroup dpaiop
 * @{
 */

/**
 * dpaiop_open() - Open a control session for the specified object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpaiop_id:	DPAIOP unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to open a control session for an
 * already created object; an object may have been declared in
 * the DPL or by calling the dpaiop_create function.
 * This function returns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * portal; this token must be used in all subsequent commands for
 * this specific object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_open(struct fsl_mc_io *mc_io,
		uint32_t cmd_flags,
		int dpaiop_id,
		uint16_t *token)
{
	struct dpaiop_cmd_open *cmd_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_OPEN,
					  cmd_flags,
					  0);
	cmd_params = (struct dpaiop_cmd_open *)cmd.params;
	cmd_params->dpaiop_id = cpu_to_le32(dpaiop_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_read_token(&cmd);

	return err;
}

/**
 * dpaiop_close() - Close the control session of the object
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 *
 * After this function is called, no further operations are
 * allowed on the object without opening a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_close(struct fsl_mc_io *mc_io,
		 uint32_t cmd_flags,
		 uint16_t token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_CLOSE, cmd_flags,
					  token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_create() - Create the DPAIOP object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @dprc_token:	Parent container token; '0' for default container
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @cfg:	Configuration structure
 * @obj_id:	Returned object id
 *
 * Create the DPAIOP object, allocate required resources and
 * perform required initialization.
 *
 * The object can be created either by declaring it in the
 * DPL file, or by calling this function.
 *
 * The function accepts an authentication token of a parent
 * container that this object should be assigned to. The token
 * can be '0' so the object will be assigned to the default container.
 * The newly created object can be opened with the returned
 * object id and using the container's associated tokens and MC portals.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_create(struct fsl_mc_io *mc_io,
		  uint16_t dprc_token,
		  uint32_t cmd_flags,
		  const struct dpaiop_cfg *cfg,
		  uint32_t *obj_id)
{
	struct dpaiop_cmd_create *cmd_params;
	struct mc_command cmd = { 0 };
	int err;

	(void)(cfg); /* unused */

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_CREATE,
					  cmd_flags,
					  dprc_token);
	cmd_params = (struct dpaiop_cmd_create *)cmd.params;
	cmd_params->aiop_id = cpu_to_le32(cfg->aiop_id);
	cmd_params->aiop_container_id = cpu_to_le32(cfg->aiop_container_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*obj_id = mc_cmd_read_object_id(&cmd);

	return 0;
}

/**
 * dpaiop_destroy() - Destroy the DPAIOP object and release all its resources.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 *
 * The function accepts the authentication token of the parent container that
 * created the object (not the one that currently owns the object). The object
 * is searched within parent using the provided 'object_id'.
 * All tokens to the object must be closed before calling destroy.
 *
 * Return:	'0' on Success; error code otherwise.
 */
int dpaiop_destroy(struct fsl_mc_io *mc_io,
		   uint16_t dprc_token,
		   uint32_t cmd_flags,
		   uint32_t object_id)
{
	struct dpaiop_cmd_destroy *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_DESTROY,
					  cmd_flags,
					  dprc_token);
	cmd_params = (struct dpaiop_cmd_destroy *)cmd.params;
	cmd_params->dpaiop_id = cpu_to_le32(object_id);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_reset() - Reset the DPAIOP, returns the object to initial state.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_reset(struct fsl_mc_io *mc_io,
		 uint32_t cmd_flags,
		 uint16_t token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_RESET,
					  cmd_flags,
					  token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_set_irq_enable() - Set overall interrupt state.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @irq_index:	The interrupt index to configure
 * @en:		Interrupt state - enable = 1, disable = 0
 *
 * Allows GPP software to control when interrupts are generated.
 * Each interrupt can have up to 32 causes.  The enable/disable control's the
 * overall interrupt state. if the interrupt is disabled no causes will cause
 * an interrupt.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_set_irq_enable(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint8_t irq_index,
			  uint8_t en)
{
	struct dpaiop_cmd_set_irq_enable *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_SET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_set_irq_enable *)cmd.params;
	cmd_params->irq_index = irq_index;
	cmd_params->en = en;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_get_irq_enable() - Get overall interrupt state
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @irq_index:	The interrupt index to configure
 * @en:		Returned interrupt state - enable = 1, disable = 0
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_get_irq_enable(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint8_t irq_index,
			  uint8_t *en)
{
	struct dpaiop_cmd_get_irq_enable *cmd_params;
	struct dpaiop_rsp_get_irq_enable *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_get_irq_enable *)cmd.params;
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpaiop_rsp_get_irq_enable *)cmd.params;
	*en = rsp_params->en;

	return 0;
}

/**
 * dpaiop_set_irq_mask() - Set interrupt mask.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @irq_index:	The interrupt index to configure
 * @mask:	Event mask to trigger interrupt;
 *		each bit:
 *			0 = ignore event
 *			1 = consider event for asserting IRQ
 *
 * Every interrupt can have up to 32 causes and the interrupt model supports
 * masking/unmasking each cause independently
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_set_irq_mask(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint8_t irq_index,
			uint32_t mask)
{
	struct dpaiop_cmd_set_irq_mask *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_SET_IRQ_MASK,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_set_irq_mask *)cmd.params;
	cmd_params->mask = cpu_to_le32(mask);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_get_irq_mask() - Get interrupt mask.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @irq_index:	The interrupt index to configure
 * @mask:	Returned event mask to trigger interrupt
 *
 * Every interrupt can have up to 32 causes and the interrupt model supports
 * masking/unmasking each cause independently
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_get_irq_mask(struct fsl_mc_io *mc_io,
			uint32_t cmd_flags,
			uint16_t token,
			uint8_t irq_index,
			uint32_t *mask)
{
	struct dpaiop_cmd_get_irq_mask *cmd_params;
	struct dpaiop_rsp_get_irq_mask *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_IRQ_MASK,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_get_irq_mask *)cmd.params;
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpaiop_rsp_get_irq_mask *)cmd.params;
	*mask = le32_to_cpu(rsp_params->mask);

	return 0;
}

/**
 * dpaiop_get_irq_status() - Get the current status of any pending interrupts.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @irq_index:	The interrupt index to configure
 * @status:	Returned interrupts status - one bit per cause:
 *			0 = no interrupt pending
 *			1 = interrupt pending
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_get_irq_status(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  uint8_t irq_index,
			  uint32_t *status)
{
	struct dpaiop_cmd_irq_status *cmd_params;
	struct dpaiop_rsp_get_irq_status *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(*status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpaiop_rsp_get_irq_status *)cmd.params;
	*status = le32_to_cpu(rsp_params->status);

	return 0;
}

/**
 * dpaiop_clear_irq_status() - Clear a pending interrupt's status
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @irq_index:	The interrupt index to configure
 * @status:	Bits to clear (W1C) - one bit per cause:
 *			0 = don't change
 *			1 = clear status bit
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_clear_irq_status(struct fsl_mc_io *mc_io,
			    uint32_t cmd_flags,
			    uint16_t token,
			    uint8_t irq_index,
			    uint32_t status)
{
	struct dpaiop_cmd_irq_status *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_CLEAR_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_get_attributes - Retrieve DPAIOP attributes.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_get_attributes(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t token,
			  struct dpaiop_attr *attr)
{
	struct dpaiop_rsp_get_attributes *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpaiop_rsp_get_attributes *)cmd.params;
	attr->id = le32_to_cpu(rsp_params->id);

	return 0;
}

/**
 * dpaiop_load_aiop() - Loads an image to AIOP
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @cfg:	AIOP load configurations
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_load(struct fsl_mc_io *mc_io,
		uint32_t cmd_flags,
		uint16_t token,
		struct dpaiop_load_cfg *cfg)
{
	struct dpaiop_cmd_load *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_LOAD,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_load *)cmd.params;
	cmd_params->img_size = cpu_to_le32(cfg->img_size);
	cmd_params->img_iova = cpu_to_le64(cfg->img_iova);
	cmd_params->options = cpu_to_le64(cfg->options);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_run() - Starts AIOP execution
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @cfg:	AIOP run configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_run(struct fsl_mc_io *mc_io,
	       uint32_t cmd_flags,
	       uint16_t token,
	       const struct dpaiop_run_cfg *cfg)
{
	struct dpaiop_cmd_run *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_RUN,
					  cmd_flags,
					  token);
	cmd_params = (struct dpaiop_cmd_run *)cmd.params;
	cmd_params->args_size = cpu_to_le32(cfg->args_size);
	cmd_params->args_iova = cpu_to_le64(cfg->args_iova);
	cmd_params->cores_mask = cpu_to_le64(cfg->cores_mask);
	cmd_params->options = cpu_to_le64(cfg->options);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_get_sl_version() - Get AIOP SL (Service Layer) version
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @version:	AIOP SL version number
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_get_sl_version(struct fsl_mc_io		*mc_io,
			  uint32_t			cmd_flags,
			  uint16_t			token,
			  struct dpaiop_sl_version	*version)
{
	struct dpaiop_rsp_get_sl_version *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_SL_VERSION,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpaiop_rsp_get_sl_version *)cmd.params;
	version->major = le32_to_cpu(rsp_params->version_major);
	version->minor = le32_to_cpu(rsp_params->version_minor);
	version->revision = le32_to_cpu(rsp_params->revision);

	return 0;
}

/**
 * dpaiop_get_state() - Get AIOP state
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPAIOP object
 * @state:	AIOP state
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpaiop_get_state(struct fsl_mc_io	*mc_io,
		     uint32_t		cmd_flags,
		     uint16_t		token,
		     uint32_t		*state)
{
	struct dpaiop_rsp_get_state *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_STATE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpaiop_rsp_get_state *)cmd.params;
	*state = le32_to_cpu(rsp_params->state);

	return 0;
}

/**
 * dpaiop_set_time_of_day() - Set AIOP internal time-of-day
 * @mc_io:		Pointer to MC portal's I/O object
 * @cmd_flags:		Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:		Token of DPAIOP object
 * @time_of_day:	Current number of milliseconds since the Epoch
 *
 * Return:  '0' on Success; Error code otherwise.
 */
int dpaiop_set_time_of_day(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint64_t time_of_day)
{
	struct dpaiop_cmd_set_time_of_day *cmd_params;
	struct mc_command cmd = { 0 };

	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_SET_TIME_OF_DAY,
					cmd_flags,
					token);
	cmd_params = (struct dpaiop_cmd_set_time_of_day *)cmd.params;
	cmd_params->time_of_day = cpu_to_le64(time_of_day);

	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_get_time_of_day() - Get AIOP internal time-of-day
 * @mc_io:		Pointer to MC portal's I/O object
 * @cmd_flags:		Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:		Token of DPAIOP object
 * @time_of_day:	Current number of milliseconds since the Epoch
 *
 * Return:  '0' on Success; Error code otherwise.
 */
int dpaiop_get_time_of_day(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint64_t *time_of_day)
{
	struct dpaiop_rsp_get_time_of_day *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_TIME_OF_DAY,
					cmd_flags,
					token);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpaiop_rsp_get_time_of_day *)cmd.params;
	*time_of_day = le64_to_cpu(rsp_params->time_of_day);

	return 0;
}

/**
 * dpaiop_get_api_version() - Get Data Path AIOP API version
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	Major version of data path aiop API
 * @minor_ver:	Minor version of data path aiop API
 *
 * Return:  '0' on Success; Error code otherwise.
 */
int dpaiop_get_api_version(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t *major_ver,
			   uint16_t *minor_ver)
{
	struct dpaiop_rsp_get_api_version *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_API_VERSION,
					cmd_flags,
					0);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpaiop_rsp_get_api_version *)cmd.params;
	*major_ver = le16_to_cpu(rsp_params->major);
	*minor_ver = le16_to_cpu(rsp_params->minor);

	return 0;
}

/**
 * dpaiop_set_resetable() - enable/disable dpaiop reset capability
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:		Token of DPAIOP object
 * @enable:		Set to 1 to enable reset capability, 0 to disable
 *
 * If reset capability is disabled the object will ignore the reset command.
 * Return:  '0' on Success; Error code otherwise.
 */
int dpaiop_set_resetable(struct fsl_mc_io *mc_io,
	     uint32_t cmd_flags,
	     uint16_t token,
		 int enable)
{
	struct dpaiop_cmd_set_resetable *cmd_params;
	struct mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_SET_RESETABLE,
			cmd_flags,
			token);
	cmd_params = (struct dpaiop_cmd_run *)cmd.params;
	cmd_params->resetable = !!enable;

	return mc_send_command(mc_io, &cmd);
}

/**
 * dpaiop_set_resetable() - enable/disable dpaiop reset capability
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:		Token of DPAIOP object
 * @enable:		Reset enable status. 0 dpaiop will ignore reset command, 1 dpaiop will execute the command
 *
 * Return:  '0' on Success; Error code otherwise.
 */
int dpaiop_get_resetable(struct fsl_mc_io *mc_io,
	     uint32_t cmd_flags,
	     uint16_t token,
		 int *enable)
{
	struct dpaiop_rsp_get_resetable *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPAIOP_CMDID_GET_RESETABLE,
			cmd_flags,
			token);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpaiop_rsp_get_resetable *)cmd.params;
	enable = rsp_params->resetable;

	return 0;
}
