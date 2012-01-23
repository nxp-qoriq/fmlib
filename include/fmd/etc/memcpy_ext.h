/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**************************************************************************//**

 @File          memcpy_ext.h

 @Description   Efficient functions for copying and setting blocks of memory.
*//***************************************************************************/

#ifndef __MEMCPY_EXT_H
#define __MEMCPY_EXT_H

#include "std_ext.h"


/**************************************************************************//**
 @Group         etc_id   Utility Library Application Programming Interface

 @Description   External routines.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Group         mem_cpy Memory Copy

 @Description   Memory Copy module functions,definitions and enums.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Function      MemCpy32

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
void * MemCpy32(void* pDst,void* pSrc, uint32_t size);
void * IO2IOCpy32(void* pDst,void* pSrc, uint32_t size);
void * IO2MemCpy32(void* pDst,void* pSrc, uint32_t size);
void * Mem2IOCpy32(void* pDst,void* pSrc, uint32_t size);

/**************************************************************************//**
 @Function      MemCpy64

 @Description   Copies one memory buffer into another one in 8-byte chunks!
                Which should be more efficient than byte by byte.

                For large buffers (over 60 bytes) this function is about 8 times
                more efficient than the trivial memory copy. For short buffers
                it is reduced to the trivial copy and may be a bit worse.

                Some testing suggests that MemCpy32() preforms better than
                MemCpy64() over small buffers. On average they break even at
                100 byte buffers. For buffers larger than that MemCpy64 is
                superior.

 @Param[in]     pDst    - The address of the destination buffer.
 @Param[in]     pSrc    - The address of the source buffer.
 @Param[in]     size    - The number of bytes that will be copied from pSrc to pDst.

 @Return        pDst (the address of the destination buffer).

 @Cautions      There is no parameter or boundary checking! It is up to the user
                to supply non null parameters as source & destination and size
                that actually fits into their buffer.

                Do not use under Linux.
*//***************************************************************************/
void * MemCpy64(void* pDst,void* pSrc, uint32_t size);

/**************************************************************************//**
 @Function      MemSet32

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
void * MemSet32(void* pDst, uint8_t val, uint32_t size);
void * IOMemSet32(void* pDst, uint8_t val, uint32_t size);

/**************************************************************************//**
 @Function      MemSet64

 @Description   Sets all bytes of a memory buffer to a specific value, in
                8-byte chunks.

 @Param[in]     pDst    - The address of the destination buffer.
 @Param[in]     val     - Value to set destination bytes to.
 @Param[in]     size    - The number of bytes that will be set to val.

 @Return        pDst (the address of the destination buffer).

 @Cautions      There is no parameter or boundary checking! It is up to the user
                to supply non null parameter as destination and size
                that actually fits into the destination buffer.
*//***************************************************************************/
void * MemSet64(void* pDst, uint8_t val, uint32_t size);

/**************************************************************************//**
 @Function      MemDisp

 @Description   Displays a block of memory in chunks of 32 bits.

 @Param[in]     addr    - The address of the memory to display.
 @Param[in]     size    - The number of bytes that will be displayed.

 @Return        None.

 @Cautions      There is no parameter or boundary checking! It is up to the user
                to supply non null parameter as destination and size
                that actually fits into the destination buffer.
*//***************************************************************************/
void MemDisp(uint8_t *addr, int size);

/** @} */ /* end of mem_cpy group */
/** @} */ /* end of etc_id group */


#endif /* __MEMCPY_EXT_H */
