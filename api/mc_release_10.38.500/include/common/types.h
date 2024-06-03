/**************************************************************************//**
 Copyright 2013 Freescale Semiconductor, Inc.
 Copyright 2022 NXP

 @File          types.h

 @Description   TODO
 *//***************************************************************************/
#ifndef __FSL_TYPES_H
#define __FSL_TYPES_H

#if defined(__GNUC__) && defined(__cplusplus)
#include "kernel/types_gpp.h"

#elif defined(__GNUC__)
#include "kernel/types_gcc.h"

#elif defined(__MWERKS__)
#include "kernel/types_mw.h"

#else
#error "missing types definition"
#endif

#if defined(_HOST_DPLIB_)
//build flags:
#define SOC_ARM_CORE
#define LS2100A
#define GPP
//overwrite:
#define __asm__(x)
#if (!defined(__cplusplus))
#define inline __inline
#define __inline__ __inline
#endif
#endif

/**************************************************************************//**
 @Description   General Handle
 *//***************************************************************************/
typedef void * fsl_handle_t; /**< TODO: remove, do not use */


#endif /* __FSL_TYPES_H */
