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
#include <fsl_mc_sys.h>
#include <fsl_mc_cmd.h>
#include <fsl_dpsparser.h>
#include <fsl_dpsparser_cmd.h>

/** @addtogroup dpsparser
 * @{
 */

int dpsparser_open(struct fsl_mc_io *mc_io,
	      uint32_t cmd_flags,
	      uint16_t *token)
{
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSPARSER_CMDID_OPEN,
					  cmd_flags,
					  0);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_read_token(&cmd);

	return err;
}

int dpsparser_close(struct fsl_mc_io *mc_io,
	       uint32_t cmd_flags,
	       uint16_t token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSPARSER_CMDID_CLOSE, cmd_flags,
					  token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

int dpsparser_create(struct fsl_mc_io *mc_io,
		uint16_t token,
		uint32_t cmd_flags,
		uint32_t *obj_id)
{
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSPARSER_CMDID_CREATE,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*obj_id = mc_cmd_read_object_id(&cmd);

	return 0;
}

int dpsparser_destroy(struct fsl_mc_io *mc_io,
		 uint16_t token,
		 uint32_t cmd_flags,
		 uint32_t obj_id)
{
	struct dpsparser_cmd_destroy *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSPARSER_CMDID_DESTROY,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsparser_cmd_destroy *)cmd.params;
	cmd_params->dpsparser_id = cpu_to_le32(obj_id);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

int dpsparser_apply_spb(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint64_t blob_addr,
			 uint16_t *error)
{
	struct dpsparser_cmd_blob_set_address *cmd_params;
	struct dpsparser_rsp_blob_report_error *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSPARSER_CMDID_APPLY_SPB,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsparser_cmd_blob_set_address *)cmd.params;
	cmd_params->blob_addr = cpu_to_le64(blob_addr);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters: MC error code */
	rsp_params = (struct dpsparser_rsp_blob_report_error *)cmd.params;
	*error = le16_to_cpu(rsp_params->error);

	return 0;
}

int dpsparser_get_api_version(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t *major_ver,
			 uint16_t *minor_ver)
{
	struct dpsparser_rsp_get_api_version *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSPARSER_CMDID_GET_API_VERSION,
					  cmd_flags, 0);

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpsparser_rsp_get_api_version *)cmd.params;
	*major_ver = le16_to_cpu(rsp_params->major);
	*minor_ver = le16_to_cpu(rsp_params->minor);

	return 0;
}
