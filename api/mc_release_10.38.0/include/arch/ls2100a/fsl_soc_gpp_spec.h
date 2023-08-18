/* Copyright 2023 NXP
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

/**

 @File          fsl_soc_mc_spec.h

 @Description   LS2100A external definitions and structures.
 *//***************************************************************************/
#ifndef __FSL_SOC_GPP_SPEC_H
#define __FSL_SOC_GPP_SPEC_H

#include "common/types.h"


/**************************************************************************//**
 @Group         ls2100a_g LS2100A Application Programming Interface

 @Description   LS2100A Chip functions,definitions and enums.

 @{
 *//***************************************************************************/

//#define CORE_E6500

#define INTG_MAX_NUM_OF_CORES   6
#define INTG_THREADS_PER_CORE   1


/**************************************************************************//**
 @Description   Module types.
 *//***************************************************************************/
enum fsl_os_module {
    FSL_OS_MOD_SOC = 0,

	FSL_OS_MOD_CMDIF_SRV,
	FSL_OS_MOD_DPRC,
    FSL_OS_MOD_DPNI,
    FSL_OS_MOD_DPIO,
    FSL_OS_MOD_DPSP,
    FSL_OS_MOD_DPSW,

	FSL_OS_MOD_LAW,
	FSL_OS_MOD_PIC, /**< PIC */

    FSL_OS_MOD_UART,

    FSL_OS_MOD_MC_PORTAL,
	FSL_OS_MOD_QBMAN_CE_PORTAL,
	FSL_OS_MOD_QBMAN_CI_PORTAL,

	FSL_OS_MOD_DUMMY_LAST
};

/** @} *//* end of ls2100a_g group */


#endif /* __FSL_SOC_GPP_SPEC_H */
