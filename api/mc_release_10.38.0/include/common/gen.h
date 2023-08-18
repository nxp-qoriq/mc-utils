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

/**************************************************************************//**
 @File          gen.h

 @Description   General FSL OS Standard Definitions
*//***************************************************************************/

#ifndef __FSL_SYS_GEN_H
#define __FSL_SYS_GEN_H

#include "common/types.h"


#define PTR_TO_UINT(_ptr)       ((uintptr_t)(_ptr))
#define UINT_TO_PTR(_val)       ((void*)(uintptr_t)(_val))

#define PTR_MOVE(_ptr, _offset)	(void*)((uint8_t*)(_ptr) + (_offset))

#define MAKE_UINT64(_h32, _l32)	(((uint64_t)high32 << 32) | (low32))

#define MAKE_UMASK32(_width)	(uint32_t)(((uint64_t)1 << (_width)) - 1)
#define MAKE_UMASK64(_width)	((uint64_t)((_width) < 64 ? ((uint64_t)1 << (_width)) - 1 \
                                 : -1))



/*----------------------*/
/* Miscellaneous macros */
/*----------------------*/

#define UNUSED(_x)	((void)(_x))

#define KILOBYTE	1024UL
#define MEGABYTE	(KILOBYTE * KILOBYTE)
#define GIGABYTE	((KILOBYTE * MEGABYTE))

/* Macro for checking if a number is a power of 2 */
#define is_power_of_2(n)   (!((n) & ((n)-1)))

/* Macro for calculating log of base 2 */
//TODO: replace with static inline function, if needed
#define LOG2(_num, _log2_num)   \
    do  {                       \
        uint64_t tmp = (_num);  \
        _log2_num = 0;          \
        while (tmp > 1) {       \
            _log2_num++;        \
            tmp >>= 1;          \
        }                       \
    } while (0)

//TODO: replace with static inline function, if needed
#define NEXT_POWER_OF_2(_num, _next_pow) \
    do {                                 \
        if (is_power_of_2(_num))         \
            _next_pow = (_num);          \
        else {                           \
            uint64_t tmp = (_num);       \
            _next_pow = 1;               \
            while (tmp) {                \
                _next_pow <<= 1;         \
                tmp >>= 1;               \
            }                            \
        }                                \
    } while (0)

/* Ceiling division - not the fastest way, but safer in terms of overflow */
#define DIV_CEIL(x,y)   (((x)/(y)) + ((((((x)/(y)))*(y)) == (x)) ? 0 : 1))

/* Round up a number to be a multiple of a second number */
#define ROUND_UP(x,y)   ((((x) + (y) - 1) / (y)) * (y))

/* Timing macro for converting usec units to number of ticks.   */
/* (number of usec *  clock_Hz) / 1,000,000) - since            */
/* clk is in MHz units, no division needed.                     */
#define USEC_TO_CLK(usec,clk)       ((usec) * (clk))
#define CYCLES_TO_USEC(cycles,clk)  ((cycles) / (clk))

/* Timing macros for converting between nsec units and number of clocks. */
#define NSEC_TO_CLK(nsec,clk)       DIV_CEIL(((nsec) * (clk)), 1000)
#define CYCLES_TO_NSEC(cycles,clk)  (((cycles) * 1000) / (clk))

/* Timing macros for converting between psec units and number of clocks. */
#define PSEC_TO_CLK(psec,clk)       DIV_CEIL(((psec) * (clk)), 1000000)
#define CYCLES_TO_PSEC(cycles,clk)  (((cycles) * 1000000) / (clk))

/* Min, Max macros */
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

#define IN_RANGE(_min,_val,_max)	((_min)<=(_val) && (_val)<=(_max))

#define ABS(a)  ((a<0)?(a*-1):a)

#if !(defined(ARRAY_SIZE))
#define ARRAY_SIZE(arr)		(sizeof(arr) / sizeof((arr)[0]))
#endif /* !defined(ARRAY_SIZE) */
#define ARRAY_EL_SIZE(arr)	(sizeof((arr)[0]))

#ifndef IS_ALIGNED
#define IS_ALIGNED(n,align)     (!((uint32_t)(n) & (align - 1)))
#endif /* IS_ALIGNED */

#ifndef ALIGN_UP
#define ALIGN_UP(ADDRESS, ALIGNMENT)           \
        ((((uint32_t)(ADDRESS)) + ((uint32_t)(ALIGNMENT)) - 1) & (~(((uint32_t)(ALIGNMENT)) - 1)))
        /**< Align a given address - equivalent to ceil(ADDRESS,ALIGNMENT) */
#endif /* ALIGN_UP */

#ifndef ALIGN_DOWN
#define ALIGN_DOWN(ADDRESS, ALIGNMENT)      \
        ((uint32_t)(ADDRESS) & (~(((uint32_t)(ALIGNMENT)) - 1)))
        /**< Align a given address to a lower aligned address - equivalent to floor(ADDRESS,ALIGNMENT) */
#endif /* ALIGN_DOWN */

#define ILLEGAL_BASE    (~0)	//TODO - remove

/* @} */

#define DECLARE_UINT_CODEC(w) \
static inline uint##w##_t u##w##_enc(int lsoffset, int width, uint##w##_t val) \
{ \
	return (uint##w##_t)(((uint##w##_t)val & MAKE_UMASK##w(width)) << lsoffset); \
} \
static inline uint##w##_t u##w##_dec(uint##w##_t val, int lsoffset, int width) \
{ \
	return (uint##w##_t)((val >> lsoffset) & MAKE_UMASK##w(width)); \
} \
static inline uint##w##_t u##w##_clr(uint##w##_t val, int lsoffset, int width) \
{ \
	return (uint##w##_t)(val & ~(MAKE_UMASK##w(width) << lsoffset)); \
} \
static inline uint##w##_t u##w##_iso(uint##w##_t val, int lsoffset, int width) \
{ \
	return (uint##w##_t)(val & (MAKE_UMASK##w(width) << lsoffset)); \
} \
static inline uint##w##_t u##w##_rmw(uint##w##_t val, int lsoffset, int width, uint##w##_t new_val) \
{ \
	return (uint##w##_t)(u##w##_clr(val, lsoffset, width) | u##w##_enc(lsoffset, width, new_val)); \
}

DECLARE_UINT_CODEC(32)
#if (!defined(DECLARE_UINT_CODEC))
DECLARE_UINT_CODEC(64)
#endif

#endif /* __FSL_SYS_GEN_H */
