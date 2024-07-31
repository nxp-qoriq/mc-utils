/* Copyright 2013 Freescale Semiconductor, Inc.
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
 @File          fsl_soc_spec.h

 @Description   LS2100A external definitions and structures.
*//***************************************************************************/
#ifndef __FSL_SOC_SPEC_H
#define __FSL_SOC_SPEC_H

#include "common/types.h"
#if defined(AIOP)
#include "arch/ls2100a/fsl_soc_aiop_spec.h"
#elif defined(MC)
#include "arch/ls2100a/fsl_soc_mc_spec.h"
#elif defined(GPP)
#include "arch/ls2100a/fsl_soc_gpp_spec.h"
#else
#error "SoC subsystem not defined!"
#endif


/**************************************************************************//**
 @Group         ls2100a_g LS2100A Application Programming Interface

 @Description   LS2100A Chip functions,definitions and enums.

 @{
*//***************************************************************************/

#define FSL_OS_NUM_MODULES  FSL_OS_MOD_DUMMY_LAST

/* Offsets relative to CCSR base */
#define SOC_PERIPH_OFF_LAW              0x00000c00
#define SOC_PERIPH_OFF_PM1              0x00004000
#define SOC_PERIPH_OFF_DDR1             0x00008000
#define SOC_PERIPH_OFF_DDR2             0x00009000
#define SOC_PERIPH_OFF_CPC1             0x00010000
#define SOC_PERIPH_OFF_CPC2             0x00011000
#define SOC_PERIPH_OFF_CPC3             0x00012000
#define SOC_PERIPH_OFF_IOMMU            0x00020000
#define SOC_PERIPH_OFF_SRIO_PORTS       0x000c0000
#define SOC_PERIPH_OFF_SERDES1          0x000ea000
#define SOC_PERIPH_OFF_SERDES2          0x000eb000
#define SOC_PERIPH_OFF_SERDES3          0x000ec000
#define SOC_PERIPH_OFF_SERDES4          0x000ed000
#define SOC_PERIPH_OFF_I2C1             0x00118000
#define SOC_PERIPH_OFF_I2C2             0x00118100
#define SOC_PERIPH_OFF_DUART1           0x0811c500/*0x021c0500*/
#define SOC_PERIPH_OFF_DUART2           0x081c0600
#define SOC_PERIPH_OFF_DUART3           0x081d0500
#define SOC_PERIPH_OFF_DUART4           0x081d0600
#define SOC_PERIPH_OFF_RMAN_GENERAL     0x001e0b00
#define SOC_PERIPH_OFF_RMAN_BLOCK0      0x001e0000
#define SOC_PERIPH_OFF_RMAN_BLOCK1      0x001e1000
#define SOC_PERIPH_OFF_RMAN_BLOCK2      0x001e2000
#define SOC_PERIPH_OFF_RMAN_BLOCK3      0x001e3000
#define SOC_PERIPH_OFF_USB1             0x00210000
#define SOC_PERIPH_OFF_USB2             0x00211000
#define SOC_PERIPH_OFF_PCIE1            0x00240000
#define SOC_PERIPH_OFF_PCIE2            0x00250000
#define SOC_PERIPH_OFF_SEC_GEN          0x08300000/*0x08000000*/
#define SOC_PERIPH_OFF_SEC_JQ0          0x08301000/*0x08001000*/
#define SOC_PERIPH_OFF_SEC_JQ1          0x08302000
#define SOC_PERIPH_OFF_SEC_JQ2          0x08303000
#define SOC_PERIPH_OFF_SEC_JQ3          0x08304000
#define SOC_PERIPH_OFF_SEC_RESERVED     0x08305000
#define SOC_PERIPH_OFF_SEC_RTIC         0x08306000
#define SOC_PERIPH_OFF_SEC_QI           0x08307000
#define SOC_PERIPH_OFF_QMAN             0x08318000/*0x08180000*/
#define SOC_PERIPH_OFF_BMAN             0x0831a000/*0x08190000*/
#define SOC_PERIPH_OFF_EIOP             0x08810000/*0x08b90000*/
#define SOC_PERIPH_OFF_EIOP_CTLU        0x08800000/*0x08b80000*/
#define SOC_PERIPH_OFF_EIOP_PP          0x08900000/*0x08c00000*/
#define SOC_PERIPH_OFF_EIOP_IFP         0x08a00000/*0x08800000*/
#define SOC_PERIPH_OFF_AIOP             0x08001000
#define SOC_PERIPH_OFF_MCPIC            0x01040000
#define SOC_PERIPH_OFF_MCCPM            0x00180000

/* Offsets relative to QBMan portals base */
#define SOC_PERIPH_OFF_PORTALS_CE_AREA  0x0000000        /* cache enabled area */
#define SOC_PERIPH_OFF_PORTALS_CI_AREA  0x1000000        /* cache inhibited area */
/* Offsets relative to MC portals base */
#define SOC_PERIPH_OFF_PORTALS_MC_AREA  0x0000000        /* cache enabled area */

#define SOC_PERIPH_CE_PORTAL_SIZE       0x4000
#define SOC_PERIPH_CI_PORTAL_SIZE       0x1000
#define SOC_PERIPH_MC_PORTAL_SIZE       0x40

#define SOC_PERIPH_OFF_PORTALS_CE(_prtl) \
    (SOC_PERIPH_OFF_PORTALS_CE_AREA + SOC_PERIPH_CE_PORTAL_SIZE * (_prtl))
#define SOC_PERIPH_OFF_PORTALS_CI(_prtl) \
    (SOC_PERIPH_OFF_PORTALS_CI_AREA + SOC_PERIPH_CI_PORTAL_SIZE * (_prtl))
#define SOC_PERIPH_OFF_PORTALS_MC(_prtl) \
    (SOC_PERIPH_OFF_PORTALS_MC_AREA + SOC_PERIPH_MC_PORTAL_SIZE * (_prtl))


/**************************************************************************//**
 @Group         ls2100a_init_g LS2100A Initialization Unit

 @Description   LS2100A initialization unit API functions, definitions and enums

 @{
*//***************************************************************************/

/** @} */ /* end of ls2100a_init_g group */
/** @} */ /* end of ls2100a_g group */


/*****************************************************************************
 INTEGRATION-SPECIFIC MODULE CODES
******************************************************************************/
#define MODULE_UNKNOWN          0x00000000
#define MODULE_SLAB             0x00010000
#define MODULE_SLOB             0x00020000
#define MODULE_CORE             0x00030000
#define MODULE_SOC              0x00040000
#define MODULE_SOC_PLATFORM     0x00050000
#define MODULE_PM               0x00060000
#define MODULE_MMU              0x00070000
#define MODULE_PIC              0x00080000
#define MODULE_DUART            0x000a0000
#define MODULE_SERDES           0x000b0000
#define MODULE_QM               0x000d0000
#define MODULE_BM               0x000e0000
#define MODULE_SEC              0x000f0000
#define MODULE_LAW              0x00100000
#define MODULE_LBC              0x00110000
#define MODULE_MII              0x001b0000
#define MODULE_DMA              0x001d0000
#define MODULE_SRIO             0x00210000
#define MODULE_RMAN             0x00220000
#define MODULE_DPNI             0x00230000
#define MODULE_DPSW             0x00240000
#define MODULE_EIOP             0x00250000
#define MODULE_CTLU             0x00260000
#define MODULE_CMDIF            0x00270000
#define MODULE_DPRC             0x00280000
#define MODULE_DPIO             0x00290000
#define MODULE_DPSP             0x002a0000


#endif /* __FSL_SOC_SPEC_H */
