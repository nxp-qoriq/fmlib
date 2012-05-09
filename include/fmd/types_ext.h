/******************************************************************************

 © 1995-2003, 2004, 2005-2012 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
 /**************************************************************************//**
 @File          types_ext.h

 @Description   General types Standard Definitions
*//***************************************************************************/

#ifndef __TYPES_EXT_H
#define __TYPES_EXT_H

#if defined(NCSW_LINUX)
#include "types_linux.h"

#elif defined(NCSW_LINUX_USD)
#include "types_linux_usd.h"

#elif defined(NCSW_VXWORKS)
#include "types_vxworks.h"

#elif defined(__GNUC__) && defined(__cplusplus)
#include "types_bb_gpp.h"

#elif defined(__GNUC__)
#include "types_bb_gcc.h"

#elif defined(__ghs__)
#include "types_ghs.h"

#else
#include "types_dflt.h"
#endif /* defined (__ROCOO__) */

static __inline__ void TypesChecker(void)
{
#if defined(__MWERKS__) && !defined(__GNUC__)
#pragma pack(push,1)
#endif /* defined(__MWERKS__) && ... */
     _Packed struct strct {
        __volatile__ int vi;
    } _PackedType;
#if defined(__MWERKS__) && !defined(__GNUC__)
#pragma pack(pop)
#endif /* defined(__MWERKS__) && ... */
    size_t          size = 0;
    bool            tr = TRUE, fls = FALSE;
    struct strct    *p_Struct = NULL;
    physAddress_t   addr = 0x100;

    tr          = fls;
    p_Struct    = p_Struct;
    size++;
    if (tr) size++;

    WRITE_UINT8(*((uint8_t*)((size_t)(addr))),
                 GET_UINT8(*((uint8_t*)((size_t)(addr)))));

    WRITE_UINT8(*((uint8_t*)((size_t)(UINT8_MAX))),
                 GET_UINT8(*((uint8_t*)((size_t)(UINT8_MAX)))));
    WRITE_UINT16(*((uint16_t*)((size_t)(UINT16_MAX))),
                 GET_UINT16(*((uint16_t*)((size_t)(UINT16_MAX)))));
    WRITE_UINT32(*((uint32_t*)((size_t)(UINT32_MAX))),
                 GET_UINT32(*((uint32_t*)((size_t)(UINT32_MAX)))));
    WRITE_UINT64(*((uint64_t*)((size_t)(UINT64_MAX))),
                 GET_UINT64(*((uint64_t*)((size_t)(UINT64_MAX)))));
    WRITE_UINT8(*((uint8_t*)((size_t)(INT8_MAX))),
                 GET_UINT8(*((uint8_t*)((size_t)(INT8_MIN)))));
    WRITE_UINT16(*((uint16_t*)((size_t)(INT16_MAX))),
                 GET_UINT16(*((uint16_t*)((size_t)(INT16_MIN)))));
    WRITE_UINT32(*((uint32_t*)((size_t)(INT32_MAX))),
                 GET_UINT32(*((uint32_t*)((size_t)(INT32_MIN)))));
    WRITE_UINT64(*((uint64_t*)((size_t)(INT64_MAX))),
                 GET_UINT64(*((uint64_t*)((size_t)(INT64_MIN)))));
}

#endif /* __TYPES_EXT_H */
