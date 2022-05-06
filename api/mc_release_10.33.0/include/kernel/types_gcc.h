 /**************************************************************************//**
 @File          types_gcc.h

 @Description   General types Standard Definitions
*//***************************************************************************/

#ifndef __TYPES_GCC_H
#define __TYPES_GCC_H

#include <stdint.h>
#include <stddef.h>


//#define __inline__      inline
#define _prepacked
#define _packed         __attribute__ ((packed))


typedef uint64_t            dma_addr_t;


#ifndef NULL
#define NULL ((0L))
#endif /* NULL */


#endif /* __TYPES_GCC_H */
