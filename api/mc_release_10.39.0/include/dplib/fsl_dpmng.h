/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2022 NXP
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
#ifndef __FSL_DPMNG_H
#define __FSL_DPMNG_H

/** @addtogroup dpmng Management Complex General API
 * Contains general API for the Management Complex firmware
 * @{
 */

struct fsl_mc_io;

/**
 * Management Complex firmware version information
 */
#define MC_VER_MAJOR 10
#define MC_VER_MINOR 39

/**
 * struct mc_version
 * @major: Major version number: incremented on API compatibility changes
 * @minor: Minor version number: incremented on API additions (that are
 *		backward compatible); reset when major version is incremented
 * @revision: Internal revision number: incremented on implementation changes
 *		and/or bug fixes that have no impact on API
 */
struct mc_version {
	uint32_t major;
	uint32_t minor;
	uint32_t revision;
};

int mc_get_version(struct fsl_mc_io *mc_io,
		   uint32_t cmd_flags,
		   struct mc_version *mc_ver_info);

/**
 * struct mc_platform
 * @svr:	System version (content of platform SVR register)
 * @pvr:	Processor version (content of platform PVR register)
 */
struct mc_soc_version {
	uint32_t svr;
	uint32_t pvr;
};

int mc_get_soc_version(struct fsl_mc_io *mc_io,
		       uint32_t cmd_flags,
		       struct mc_soc_version *mc_platform_info);
#endif /* __FSL_DPMNG_H */
