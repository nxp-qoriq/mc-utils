/* Copyright 2014 Freescale Semiconductor, Inc.
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

#ifndef __FSL_IO_H
#define __FSL_IO_H

#include "common/types.h"
#include "fsl_endian.h"

static inline uint8_t ioread8(const volatile uint8_t *addr)
{
	uint8_t ret = *addr;
	core_memory_barrier();
	return ret;
}

static inline uint16_t ioread16(const volatile uint16_t *addr)
{
	uint16_t ret = LE16_TO_CPU(*addr);
	core_memory_barrier();
	return ret;
}

static inline uint16_t ioread16be(const volatile uint16_t *addr)
{
	uint16_t ret = BE16_TO_CPU(*addr);
	core_memory_barrier();
	return ret;
}

static inline uint32_t ioread32(const volatile uint32_t *addr)
{
	uint32_t ret = LE32_TO_CPU(*addr);
	core_memory_barrier();
	return ret;
}

static inline uint32_t ioread32be(const volatile uint32_t *addr)
{
	uint32_t ret = BE32_TO_CPU(*addr);
	core_memory_barrier();
	return ret;
}

static inline uint64_t ioread64(const volatile uint64_t *addr)
{
	uint64_t ret = LE64_TO_CPU(*addr);
	core_memory_barrier();
	return ret;
}

static inline uint64_t ioread64be(const volatile uint64_t *addr)
{
	uint64_t ret = BE64_TO_CPU(*addr);
	core_memory_barrier();
	return ret;
}

static inline void iowrite8(uint8_t val, volatile uint8_t *addr)
{
	*addr = val;
	core_memory_barrier();
}

static inline void iowrite16(uint16_t val, volatile uint16_t *addr)
{
	*addr = CPU_TO_LE16(val);
	core_memory_barrier();
}

static inline void iowrite16be(uint16_t val, volatile uint16_t *addr)
{
	*addr = CPU_TO_BE16(val);
	core_memory_barrier();
}

static inline void iowrite32(uint32_t val, volatile uint32_t *addr)
{
	*addr = CPU_TO_LE32(val);
	core_memory_barrier();
}

static inline void iowrite32be(uint32_t val, volatile uint32_t *addr)
{
	*addr = CPU_TO_BE32(val);
	core_memory_barrier();
}

static inline void iowrite64(uint64_t val, volatile uint64_t *addr)
{
	*addr = CPU_TO_LE64(val);
	core_memory_barrier();
}

static inline void iowrite64be(uint64_t val, volatile uint64_t *addr)
{
	*addr = CPU_TO_BE64(val);
	core_memory_barrier();
}

/**************************************************************************//**
 @Function      memcpy32

 @Description   Copies one memory buffer into another one in 4-byte chunks!
 Which should be more efficient than byte by byte.

 For large buffers (over 60 bytes) this function is about 4 times
 more efficient than the trivial memory copy. For short buffers
 it is reduced to the trivial copy and may be a bit worse.

 @Param[in]     pDst    - The address of the destination buffer.
 @Param[in]     pSrc    - The address of the source buffer.
 @Param[in]     size    - The number of bytes that will be copied from pSrc to pDst.

 @Return        pDst (the address of the destination buffer).

 @Cautions      There is no parameter or boundary checking! It is up to the user
 to supply non-null parameters as source & destination and size
 that actually fits into the destination buffer.
 *//***************************************************************************/
void *io2iocpy32(void* p_dst, void* p_src, uint32_t size);
void *io2memcpy32(void* p_dst, void* p_src, uint32_t size);
void *mem2iocpy32(void* p_dst, void* p_src, uint32_t size);

/**************************************************************************//**
 @Function      iomemset32

 @Description   Sets all bytes of a memory buffer to a specific value, in
 4-byte chunks.

 @Param[in]     pDst    - The address of the destination buffer.
 @Param[in]     val     - Value to set destination bytes to.
 @Param[in]     size    - The number of bytes that will be set to val.

 @Return        pDst (the address of the destination buffer).

 @Cautions      There is no parameter or boundary checking! It is up to the user
 to supply non null parameter as destination and size
 that actually fits into the destination buffer.
 *//***************************************************************************/
void *iomemset32(void* p_dst, uint8_t val, uint32_t size);

/**************************************************************************//**
 @Function      fsl_os_phys_to_virt

 @Description   Translates a physical address to the matching virtual address.

 @Param[in]     addr - The physical address to translate.

 @Return        Virtual address.
 *//***************************************************************************/
void *fsl_os_phys_to_virt(dma_addr_t addr);

/**************************************************************************//**
 @Function      fsl_os_virt_to_phys

 @Description   Translates a virtual address to the matching physical address.

 @Param[in]     addr - The virtual address to translate.

 @Return        Physical address.
 *//***************************************************************************/
dma_addr_t fsl_os_virt_to_phys(void *addr);

#endif /* __FSL_IO_H */
