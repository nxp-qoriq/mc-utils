#ifndef __FSL_CORE_ARM_H
#define __FSL_CORE_ARM_H

//#include "arch/fsl_soc.h"

#define CORE_IS_LITTLE_ENDIAN
//#define CORE_IS_BIG_ENDIAN        0
#define CORE_CACHELINE_SIZE       64
//#define _STRING_ARCH_unaligned         1
//#define UINT_TO_PTR(_val)        ((void*)(uintptr_t)(_val))

#endif /* __FSL_CORE_ARM_H */

#define core_memory_barrier      arm_memory_barrier

static __inline__ void arm_memory_barrier(void)
{
	__asm__("dmb ish" : : : "memory");
} 


