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
#ifndef _FSL_DPSPARSER_H
#define _FSL_DPSPARSER_H

struct fsl_mc_io;


/**
 * dpsparser_open() - Open a control session for the specified object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to open a control session for an
 * already created object; an object may have been declared in
 * the DPL or by calling the dpsparser_create function.
 * This function returns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * portal; this token must be used in all subsequent commands for
 * this specific object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpsparser_open(struct fsl_mc_io	*mc_io,
	      uint32_t		cmd_flags,
	      uint16_t		*token);

/**
 * dpsparser_close() - Close the control session of the object
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSPARSER object
 *
 * After this function is called, no further operations are
 * allowed on the object without opening a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpsparser_close(struct fsl_mc_io	*mc_io,
	       uint32_t		cmd_flags,
	       uint16_t	token);

/**
 * dpsparser_create() - Create the DPSPARSER object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Returned token; use in subsequent API calls
 *
 * Create the DPSPARSER object, allocate required resources and
 * perform required initialization.
 *
 * The object can be created either by declaring it in the
 * DPL file, or by calling this function.
 * This function returns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * portal; this token must be used in all subsequent calls to
 * this specific object. For objects that are created using the
 * DPL file, call dpsparser_open function to get an authentication
 * token first.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpsparser_create(struct fsl_mc_io	*mc_io,
		uint16_t		token,
		uint32_t		cmd_flags,
		uint32_t		*obj_id);

/**
 * dpsparser_destroy() - Destroy the DPSPARSER object and release all its resources.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSPARSER object
 *
 * Return:	'0' on Success; error code otherwise.
 */
int dpsparser_destroy(struct fsl_mc_io	*mc_io,
		 uint16_t		token,
		 uint32_t		cmd_flags,
		 uint32_t		obj_id);

/**
 * dpsparser_apply_spb() - Applies the Soft Parser Blob loaded at specified address.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPSPARSER object
 * @blob_addr:	Blob loading address
 * @error: Error reported by MC related to SP Blob parsing and apply
 *
 * Return:	'0' on Success; error code otherwise.
 */
int dpsparser_apply_spb(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t token,
			 uint64_t blob_addr,
			 uint16_t *error);

/**
 * dpsparser_get_api_version - Retrieve DPSPARSER Major and Minor version info.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	DPSPARSER major version
 * @minor_ver:	DPSPARSER minor version
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpsparser_get_api_version(struct fsl_mc_io *mc_io,
			 uint32_t cmd_flags,
			 uint16_t *major_ver,
			 uint16_t *minor_ver);


#endif /* _FSL_DPSPARSER_H */
