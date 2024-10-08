/* Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2018-2020, 2022, 2024 NXP
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
#include <fsl_dpmac.h>
#include <fsl_dpmac_cmd.h>

/** @addtogroup dpmac
 * @{
 */

/**
 * dpmac_open() - Open a control session for the specified object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpmac_id:	DPMAC unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to open a control session for an
 * already created object; an object may have been declared in
 * the DPL or by calling the dpmac_create function.
 * This function returns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * portal; this token must be used in all subsequent commands for
 * this specific object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_open(struct fsl_mc_io *mc_io,
	       uint32_t cmd_flags,
	       int dpmac_id,
	       uint16_t *token)
{
	struct dpmac_cmd_open *cmd_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_OPEN,
					  cmd_flags,
					  0);
	cmd_params = (struct dpmac_cmd_open *)cmd.params;
	cmd_params->dpmac_id = cpu_to_le32(dpmac_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_read_token(&cmd);

	return err;
}

/**
 * dpmac_close() - Close the control session of the object
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 *
 * After this function is called, no further operations are
 * allowed on the object without opening a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_close(struct fsl_mc_io *mc_io,
		uint32_t cmd_flags,
		uint16_t token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_CLOSE, cmd_flags,
					  token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_create() - Create the DPMAC object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @dprc_token: Parent container token; '0' for default container
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @cfg:	Configuration structure
 * @obj_id:	Returned object id
 *
 * Create the DPMAC object, allocate required resources and
 * perform required initialization.
 *
 * The function accepts an authentication token of a parent
 * container that this object should be assigned to. The token
 * can be '0' so the object will be assigned to the default container.
 * The newly created object can be opened with the returned
 * object id and using the container's associated tokens and MC portals.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_create(struct fsl_mc_io *mc_io,
		 uint16_t dprc_token,
		 uint32_t cmd_flags,
		 const struct dpmac_cfg *cfg,
		 uint32_t *obj_id)
{
	struct dpmac_cmd_create *cmd_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_CREATE,
					  cmd_flags,
					  dprc_token);
	cmd_params = (struct dpmac_cmd_create *)cmd.params;
	cmd_params->mac_id = cpu_to_le32(cfg->mac_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*obj_id = mc_cmd_read_object_id(&cmd);

	return 0;
}

/**
 * dpmac_destroy() - Destroy the DPMAC object and release all its resources.
 * @mc_io:	Pointer to MC portal's I/O object
 * @dprc_token: Parent container token; '0' for default container
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @object_id:	The object id; it must be a valid id within the container that
 * created this object;
 *
 * The function accepts the authentication token of the parent container that
 * created the object (not the one that currently owns the object). The object
 * is searched within parent using the provided 'object_id'.
 * All tokens to the object must be closed before calling destroy.
 *
 * Return:	'0' on Success; error code otherwise.
 */
int dpmac_destroy(struct fsl_mc_io *mc_io,
		  uint16_t dprc_token,
		  uint32_t cmd_flags,
		  uint32_t object_id)
{
	struct dpmac_cmd_destroy *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_DESTROY,
					  cmd_flags,
					  dprc_token);
	cmd_params = (struct dpmac_cmd_destroy *)cmd.params;
	cmd_params->dpmac_id = cpu_to_le32(object_id);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_set_irq_enable() - Set overall interrupt state.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
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
int dpmac_set_irq_enable(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint8_t irq_index,
			 uint8_t en)
{
	struct dpmac_cmd_set_irq_enable *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_SET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_set_irq_enable *)cmd.params;
	cmd_params->irq_index = irq_index;
	cmd_params->enable = en;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_get_irq_enable() - Get overall interrupt state
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @irq_index:	The interrupt index to configure
 * @en:		Returned interrupt state - enable = 1, disable = 0
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_get_irq_enable(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint8_t irq_index,
			 uint8_t *en)
{
	struct dpmac_cmd_get_irq_enable *cmd_params;
	struct dpmac_rsp_get_irq_enable *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_get_irq_enable *)cmd.params;
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpmac_rsp_get_irq_enable *)cmd.params;
	*en = rsp_params->enabled;

	return 0;
}

/**
 * dpmac_set_irq_mask() - Set interrupt mask.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @irq_index:	The interrupt index to configure
 * @mask:	Event mask to trigger interrupt; combination of DPMAC_IRQ_* flags
 *		each bit:
 *			0 = ignore event
 *			1 = consider event for asserting IRQ
 *
 * Every interrupt can have up to 32 causes and the interrupt model supports
 * masking/unmasking each cause independently
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_set_irq_mask(struct fsl_mc_io *mc_io,
		       uint32_t cmd_flags,
		       uint16_t token,
		       uint8_t irq_index,
		       uint32_t mask)
{
	struct dpmac_cmd_set_irq_mask *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_SET_IRQ_MASK,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_set_irq_mask *)cmd.params;
	cmd_params->mask = cpu_to_le32(mask);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_get_irq_mask() - Get interrupt mask.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @irq_index:	The interrupt index to configure
 * @mask:	Returned event mask to trigger interrupt; combination of DPMAC_IRQ_* flags
 *
 * Every interrupt can have up to 32 causes and the interrupt model supports
 * masking/unmasking each cause independently
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_get_irq_mask(struct fsl_mc_io *mc_io,
		       uint32_t cmd_flags,
		       uint16_t token,
		       uint8_t irq_index,
		       uint32_t *mask)
{
	struct dpmac_cmd_get_irq_mask *cmd_params;
	struct dpmac_rsp_get_irq_mask *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_IRQ_MASK,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_get_irq_mask *)cmd.params;
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpmac_rsp_get_irq_mask *)cmd.params;
	*mask = le32_to_cpu(rsp_params->mask);

	return 0;
}

/**
 * dpmac_get_irq_status() - Get the current status of any pending interrupts.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @irq_index:	The interrupt index to configure
 * @status:	Returned interrupts status - one bit per cause:
 *			0 = no interrupt pending
 *			1 = interrupt pending
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_get_irq_status(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint8_t irq_index,
			 uint32_t *status)
{
	struct dpmac_cmd_get_irq_status *cmd_params;
	struct dpmac_rsp_get_irq_status *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_get_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(*status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpmac_rsp_get_irq_status *)cmd.params;
	*status = le32_to_cpu(rsp_params->status);

	return 0;
}

/**
 * dpmac_clear_irq_status() - Clear a pending interrupt's status
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @irq_index:	The interrupt index to configure
 * @status:	Bits to clear (W1C) - one bit per cause:
 *			0 = don't change
 *			1 = clear status bit
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_clear_irq_status(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint8_t irq_index,
			   uint32_t status)
{
	struct dpmac_cmd_clear_irq_status *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_CLEAR_IRQ_STATUS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_clear_irq_status *)cmd.params;
	cmd_params->status = cpu_to_le32(status);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_get_attributes - Retrieve DPMAC attributes.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_get_attributes(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 struct dpmac_attr *attr)
{
	struct dpmac_rsp_get_attributes *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpmac_rsp_get_attributes *)cmd.params;
	attr->eth_if = rsp_params->eth_if;
	attr->link_type = rsp_params->link_type;
	attr->id = le16_to_cpu(rsp_params->id);
	attr->max_rate = le32_to_cpu(rsp_params->max_rate);
	attr->fec_mode = rsp_params->fec_mode;
	attr->serdes_cfg.sgn_post1q = dpmac_get_field(rsp_params->sgn, POST1Q);
	attr->serdes_cfg.sgn_preq = dpmac_get_field(rsp_params->sgn, PREQ);
	attr->serdes_cfg.cfg = rsp_params->eq_mode;
	attr->serdes_cfg.eq_amp_red = rsp_params->eq_amp_red;
	attr->serdes_cfg.eq_post1q = rsp_params->eq_post1q;
	attr->serdes_cfg.eq_preq = rsp_params->eq_preq;
	attr->serdes_cfg.eq_type = rsp_params->eq_type;
	attr->ifg_cfg.ipg_mode = rsp_params->ipg_mode;
	attr->ifg_cfg.ipg_length = rsp_params->ipg_length;

	return 0;
}

/**
 * dpmac_set_params() - Set ipg attributes.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @ifg_cfg:	inter packet attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_set_params(struct fsl_mc_io *mc_io,
		       uint32_t cmd_flags,
		       uint16_t token,
			   uint32_t flags,
			   struct dpmac_ifg_cfg ifg_cfg)
{
	struct dpmac_cmd_set_params *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_SET_PARAMS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_set_params *)cmd.params;
	cmd_params->flags = cpu_to_le32(flags);
	cmd_params->ipg_mode = ifg_cfg.ipg_mode;
	cmd_params->ipg_length = ifg_cfg.ipg_length;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}


/**
 * dpmac_get_mac_addr() - Retrieve MAC address associated to the DPMAC
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @mac_addr:	MAC address of the physical port, if any, otherwise 0
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_get_mac_addr(struct fsl_mc_io *mc_io,
			   uint32_t cmd_flags,
			   uint16_t token,
			   uint8_t mac_addr[6])
{
	struct mc_command cmd = { 0 };
	struct dpmac_rsp_get_mac_addr *rsp_params;
	int i, err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_MAC_ADDR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpmac_rsp_get_mac_addr *)cmd.params;
	for (i = 0; i < 6; i++)
		mac_addr[5 - i] = rsp_params->mac_addr[i];

	return 0;
}

/**
 * dpmac_mdio_read() - Used to read through MDIO.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @mdio:	mdio attributes (clause + phy address + register)
 * @data:	Returned MDIO read value
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_mdio_read(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 struct dpmac_mdio_read mdio,
			 uint16_t *data)
{
	struct dpmac_cmd_mdio_read *cmd_params;
	struct dpmac_rsp_mdio_read *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_MDIO_READ,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_mdio_read *)cmd.params;
	cmd_params->cl45 = mdio.cl45;
	cmd_params->phy_addr = mdio.phy_addr;
	cmd_params->reg = cpu_to_le16(mdio.reg);

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpmac_rsp_mdio_read *)cmd.params;
	*data = le16_to_cpu(rsp_params->data);

	return 0;
}

/**
 * dpmac_mdio_write() - Used to write through MDIO.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @mdio:	mdio attributes (clause + phy address + register + data)
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_mdio_write(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 struct dpmac_mdio_write mdio)
{
	struct dpmac_cmd_mdio_write *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_MDIO_WRITE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_mdio_write *)cmd.params;
	cmd_params->cl45 = mdio.cl45;
	cmd_params->phy_addr = mdio.phy_addr;
	cmd_params->reg = cpu_to_le16(mdio.reg);
	cmd_params->data = cpu_to_le16(mdio.data);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);

}

/**
 * dpmac_get_link_cfg() - Get Ethernet link configuration
 * @mc_io:	Pointer to opaque I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @cfg:	Returned structure with the link configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_get_link_cfg(struct fsl_mc_io *mc_io,
		       uint32_t cmd_flags,
		       uint16_t token,
		       struct dpmac_link_cfg *cfg)
{
	struct dpmac_rsp_get_link_cfg *rsp_params;
	struct mc_command cmd = { 0 };
	int err = 0;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_LINK_CFG,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpmac_rsp_get_link_cfg *)cmd.params;
	cfg->options = le64_to_cpu(rsp_params->options);
	cfg->rate = le32_to_cpu(rsp_params->rate);
    cfg->advertising = le64_to_cpu(rsp_params->advertising);

	return 0;
}

/**
 * dpmac_set_link_state() - Set the Ethernet link status
 * @mc_io:	Pointer to opaque I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @link_state:	Link state configuration
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpmac_set_link_state(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 struct dpmac_link_state *link_state)
{
	struct dpmac_cmd_set_link_state *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_SET_LINK_STATE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpmac_cmd_set_link_state *)cmd.params;
	cmd_params->options = cpu_to_le64(link_state->options);
	cmd_params->rate = cpu_to_le32(link_state->rate);
	cmd_params->up = dpmac_get_field(link_state->up, STATE);
	dpmac_set_field(cmd_params->up, STATE_VALID, link_state->state_valid);
    cmd_params->supported = cpu_to_le64(link_state->supported);
    cmd_params->advertising = cpu_to_le64(link_state->advertising);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_get_counter() - Read a specific DPMAC counter
 * @mc_io:	Pointer to opaque I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPMAC object
 * @type:	The requested counter
 * @counter:	Returned counter value
 *
 * Return:	The requested counter; '0' otherwise.
 */
int dpmac_get_counter(struct fsl_mc_io *mc_io,
		      uint32_t cmd_flags,
		      uint16_t token,
		      enum dpmac_counter type,
		      uint64_t *counter)
{
	struct dpmac_cmd_get_counter *dpmac_cmd;
	struct dpmac_rsp_get_counter *dpmac_rsp;
	struct mc_command cmd = { 0 };
	int err = 0;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_COUNTER,
					  cmd_flags,
					  token);
	dpmac_cmd = (struct dpmac_cmd_get_counter *)cmd.params;
	dpmac_cmd->type = type;

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	dpmac_rsp = (struct dpmac_rsp_get_counter *)cmd.params;
	*counter = le64_to_cpu(dpmac_rsp->counter);

	return 0;
}

/**
 * dpmac_get_api_version() - Get Data Path MAC version
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	Major version of data path mac API
 * @minor_ver:	Minor version of data path mac API
 *
 * Return:  '0' on Success; Error code otherwise.
 */
int dpmac_get_api_version(struct fsl_mc_io *mc_io,
			  uint32_t cmd_flags,
			  uint16_t *major_ver,
			  uint16_t *minor_ver)
{
	struct dpmac_rsp_get_api_version *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_API_VERSION,
					cmd_flags,
					0);

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpmac_rsp_get_api_version *)cmd.params;
	*major_ver = le16_to_cpu(rsp_params->major);
	*minor_ver = le16_to_cpu(rsp_params->minor);

	return 0;
}

/**
 * dpmac_reset() - Reset the DPMAC, returns the object to initial state.
 * @mc_io:     Pointer to MC portal's I/O object
 * @cmd_flags: Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:     Token of DPMAC object
 *
 * Return:     '0' on Success; Error code otherwise.
 */
int dpmac_reset(struct fsl_mc_io *mc_io,
		uint32_t cmd_flags,
		uint16_t token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_RESET,
					  cmd_flags,
					  token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_set_protocol() - Reconfigure the DPMAC protocol
 * @mc_io:      Pointer to opaque I/O object
 * @cmd_flags:  Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:      Token of DPMAC object
 * @protocol:   New protocol for the DPMAC to be reconfigured in.
 *
 * Return:      '0' on Success; Error code otherwise.
 */
int dpmac_set_protocol(struct fsl_mc_io *mc_io, uint32_t cmd_flags,
		       uint16_t token, enum dpmac_eth_if protocol)
{
	struct dpmac_cmd_set_protocol *cmd_params;
	struct mc_command cmd = { 0 };

	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_SET_PROTOCOL,
					  cmd_flags, token);
	cmd_params = (struct dpmac_cmd_set_protocol *)cmd.params;
	cmd_params->eth_if = protocol;

	return mc_send_command(mc_io, &cmd);
}

/**
 * dpmac_get_statistics() - Get MAC statistics
 * @mc_io:       Pointer to opaque I/O object
 * @cmd_flags:   Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:       Token of DPMAC object
 * @iova_cnt:    IOVA containing the requested MAC counters formatted as an
 *               array of __le32 representing the dpmac_counter_id.
 * @iova_values: IOVA containing the values for all the requested counters
 *               formatted as an array of __le64.
 * @num_cnt:     Number of counters requested
 *
 * Return:       '0' on Success; Error code otherwise.
 */
int dpmac_get_statistics(struct fsl_mc_io *mc_io, uint32_t cmd_flags, uint16_t token,
			 uint64_t iova_cnt, uint64_t iova_values, uint32_t num_cnt)
{
	struct dpmac_cmd_get_statistics *cmd_params;
	struct mc_command cmd = { 0 };

	cmd.header = mc_encode_cmd_header(DPMAC_CMDID_GET_STATISTICS, cmd_flags, token);
	cmd_params = (struct dpmac_cmd_get_statistics *)cmd.params;
	cmd_params->iova_cnt = cpu_to_le64(iova_cnt);
	cmd_params->iova_values = cpu_to_le64(iova_values);
	cmd_params->num_cnt = cpu_to_le32(num_cnt);

	return mc_send_command(mc_io, &cmd);
}
