/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**************************************************************************//*

 @File          cq_ext.h

 @Description   External prototypes for the circular queue object.
*//***************************************************************************/

#ifndef __CQ_EXT_H
#define __CQ_EXT_H


#include "std_ext.h"


/**************************************************************************//**
 @Group         etc_id   Utility Library Application Programming Interface

 @Description   External routines.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Group         cq_id Circular Queue

 @Description   Circular Queue module functions, definitions and enums.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Function      CQ_New

 @Description   Allocates and initializes a new circular queue.

 @Param[in]     maxItems    - Maximum number of items in queue.
 @Param[in]     itemSize    - Size, in bytes, of each item in the queue.

 @Return        Handle to the new object on success;
                NULL on failure (out of memory).
*//***************************************************************************/
t_Handle CQ_New(uint16_t maxItems, uint16_t itemSize);

/**************************************************************************//**
 @Function      CQ_Delete

 @Description   Deletes a circular queue.

 @Param[in]     h_Cq - Handle to the circular queue.
*//***************************************************************************/
void    CQ_Delete(t_Handle h_Cq);

/**************************************************************************//**
 @Function      CQ_Flush

 @Description   Empties the circular queue (clears all items).

 @Param[in]     h_Cq - Handle to the circular queue.

 @Return        The number of items that were flushed from the queue.
*//***************************************************************************/
int     CQ_Flush(t_Handle h_Cq);

/**************************************************************************//**
 @Function      CQ_Put

 @Description   Puts a new item in the circular queue.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[in]     p_Item  - Pointer to the item that should be added.

 @Return        Number of items in the queue (including the added item);
                Returns (-1) if failed to put the item (queue is full).
*//***************************************************************************/
int     CQ_Put(t_Handle h_Cq, void *p_Item);

/**************************************************************************//**
 @Function      CQ_PutUnsafe

 @Description   Puts a new item in the circular queue (without freezing interrupts).

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[in]     p_Item  - Pointer to the item that should be added.

 @Return        Number of items in the queue (including the added item);
                Returns (-1) if failed to put the item (queue is full).

 @Cautions      This routine is not interrupt-safe, but is faster than CQ_Put();
                The user must prevent concurrent accesses to the queue.
*//***************************************************************************/
int     CQ_PutUnsafe(t_Handle h_Cq, void *p_Item);

/**************************************************************************//**
 @Function      CQ_Put1Byte

 @Description   Puts a new 1-byte item in the circular queue.
                The routine is more efficient than CQ_Put.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[in]     item    - The item that should be added.

 @Return        Number of items in the queue (including the added item);
                Returns (-1) if failed to put the item (queue is full).
*//***************************************************************************/
int     CQ_Put1Byte(t_Handle h_Cq, uint8_t item);

/**************************************************************************//**
 @Function      CQ_Put2Bytes

 @Description   Puts a new 2-byte item in the circular queue.
                The routine is more efficient than CQ_Put.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[in]     item    - The item that should be added.

 @Return        Number of items in the queue (including the added item);
                Returns (-1) if failed to put the item (queue is full).
*//***************************************************************************/
int     CQ_Put2Bytes(t_Handle h_Cq, uint16_t item);

/**************************************************************************//**
 @Function      CQ_Put4Bytes

 @Description   Puts a new 4-byte item in the circular queue.
                The routine is more efficient than CQ_Put.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[in]     item    - The item that should be added.

 @Return        Number of items in the queue (including the added item);
                Returns (-1) if failed to put the item (queue is full).
*//***************************************************************************/
int     CQ_Put4Bytes(t_Handle h_Cq, uint32_t item);

/**************************************************************************//**
 @Function      CQ_Put8Bytes

 @Description   Puts a new 8-byte item in the circular queue.
                The routine is more efficient than CQ_Put.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[in]     item    - The item that should be added.

 @Return        Number of items in the queue (including the added item);
                Returns (-1) if failed to put the item (queue is full).
*//***************************************************************************/
int     CQ_Put8Bytes(t_Handle h_Cq, uint64_t item);

/**************************************************************************//**
 @Function      CQ_Get

 @Description   Gets (and removes) an item from the circular queue.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[out]    p_Item  - Pointer that will receive the item from the queue.

 @Return        Number of items left in the queue;
                Returns (-1) if failed to get an item (queue is empty).
 *//***************************************************************************/
int     CQ_Get(t_Handle h_Cq, void *p_Item);

/**************************************************************************//**
 @Function      CQ_GetUnsafe

 @Description   Gets (and removes) an item from the circular queue (without freezing interrupts).

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[in]     p_Item  - Pointer that will receive the item from the queue.

 @Return        Number of items left in the queue;
                Returns (-1) if failed to get an item (queue is empty).

 @Cautions      This routine is not interrupt-safe, but is faster than CQ_Get();
                The user must prevent concurrent accesses to the queue.
*//***************************************************************************/
int     CQ_GetUnsafe(t_Handle h_Cq, void *p_Item);

/**************************************************************************//**
 @Function      CQ_Get1Byte

 @Description   Gets and removes a 1-byte item from the circular queue.
                The routine is more efficient than CQ_Get.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[out]    p_Item  - Pointer that will receive the item from the queue.

 @Return        Number of items left in the queue;
                Returns (-1) if failed to get an item (queue is empty).
 *//***************************************************************************/
int     CQ_Get1Byte(t_Handle h_Cq, uint8_t *p_Item);

/**************************************************************************//**
 @Function      CQ_Get2Bytes

 @Description   Gets and removes a 2-byte item from the circular queue.
                The routine is more efficient than CQ_Get.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[out]    p_Item  - Pointer that will receive the item from the queue.

 @Return        Number of items left in the queue;
                Returns (-1) if failed to get an item (queue is empty).
 *//***************************************************************************/
int     CQ_Get2Bytes(t_Handle h_Cq, uint16_t *p_Item);

/**************************************************************************//**
 @Function      CQ_Get4Bytes

 @Description   Gets and removes a 4-byte item from the circular queue.
                The routine is more efficient than CQ_Get.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[out]    p_Item  - Pointer that will receive the item from the queue.

 @Return        Number of items left in the queue;
                Returns (-1) if failed to get an item (queue is empty).
 *//***************************************************************************/
int     CQ_Get4Bytes(t_Handle h_Cq, uint32_t *p_Item);

/**************************************************************************//**
 @Function      CQ_Get8Bytes

 @Description   Gets and removes a 8-byte item from the circular queue.
                The routine is more efficient than CQ_Get.

 @Param[in]     h_Cq    - Handle to the circular queue.
 @Param[out]    p_Item  - Pointer that will receive the item from the queue.

 @Return        Number of items left in the queue;
                Returns (-1) if failed to get an item (queue is empty).
 *//***************************************************************************/
int     CQ_Get8Bytes(t_Handle h_Cq, uint64_t *p_Item);

/**************************************************************************//**
 @Function      CQ_ItemsInQueue

 @Description   Returns the number of items that are currently in the queue.

 @Param[in]     h_Cq - Handle to the circular queue.

 @Return        The number of items in the queue.
*//***************************************************************************/
int     CQ_ItemsInQueue(t_Handle h_Cq);

/**************************************************************************//**
 @Function      CQ_Read

 @Description   Reads an item in the queue. The contents of the queue are not altered.

 @Param[in]     h_Cq        - Handle to the circular queue.
 @Param[out]    p_ReadItem  - Pointer that will receive the item from the queue.
 @Param[in]     position    - The position of the item which should be read
                              (1 is the position of the first item in the queue)

 @Return        The number of items in the queue; Returns (-1) if failed to
                read the item (either the queue is empty, or the requested
                position exceeds number of items).
*//***************************************************************************/
int     CQ_Read(t_Handle h_Cq, void *p_ReadItem, uint16_t position);


/** @} */ /* end of cq_id group */
/** @} */ /* end of etc_id group */


#endif /* __CQ_EXT_H */
