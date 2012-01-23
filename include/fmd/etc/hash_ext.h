/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**

 @File          hash_ext.h

 @Description   Hash table implementation

                This is a module that implements a hash table

                User can create (using HASH_Create) the table with a fixed size and

                hash function to his liking.

 @Cautions      None.

*//***************************************************************************/
#ifndef __HASH_EXT_H
#define __HASH_EXT_H


#include "list_ext.h"

/**************************************************************************//**
 @Group         etc_id   Utility Library Application Programming Interface

 @Description   External routines.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Group         hash_id Hash Table

 @Description   Hash Table functions and typedefs.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   The t_HashEntry is infact a t_List.

*//***************************************************************************/
typedef t_List t_HashEntry;


/**************************************************************************//**
 @Description   The hash table control structure.
*//***************************************************************************/
typedef struct t_HashTable
{
    uint32_t        numOfItems; /**< A counter for the number of items in the table */
    uint32_t        tableSize;  /**< A variable holding the number of bins in the table */
    t_HashEntry *   (*f_HashFunc)(t_Handle, t_HashEntry*);
                                /**< A user-defined callback routine for fitting an
                                     appropriate bin to a given entry. */
    t_HashEntry     *hashTable; /**< The bins table, after initialization contains
                                     tableSize items. */
} t_HashTable;


/**************************************************************************//**
 @Function      HASH_Create

 @Description   Allocate and initialize the hash table.

                This function allocates memory space and initializes all the
                members of the hash table object.

 @Param[in]     f_HashFunc  - The hash function.
 @Param[in]     tableSize   - The number of entries in the table.

 @Return        Pointer to the created hash table.

 @Cautions      f_HashFunc should limit itself to the table size,
                it's up to the user to check that it does not exceed the limits.
*//***************************************************************************/
t_HashTable * HASH_Create(t_HashEntry * (*f_HashFunc)(t_Handle, t_HashEntry*),
                          uint32_t      tableSize);


/**************************************************************************//**
 @Function      HASH_Terminate

 @Description   destructor

                free the allocated memory

 @Param[in]     p_HashTable - A pointer to a hash table instance.

 @Return        None

 @Cautions      User can no longer reach the items through this table.
                It is recommended to handle this issue before calling this function
*//***************************************************************************/
void HASH_Terminate(t_HashTable *p_HashTable);


/**************************************************************************//**
 @Function      HASH_Insert

 @Description   insert a member to the hash table.

                Insert an item to the location specified by the
                hash function.

 @Param[in]     p_HashTable - A pointer to the hash table instance.
 @Param[in]     p_NewEntry  - A pointer to the new entry.

 @Return        None
*//***************************************************************************/
void HASH_Insert(t_HashTable *p_HashTable, t_HashEntry *p_NewEntry);


/**************************************************************************//**
 @Function      HASH_IsEmpty

 @Description   Checks if no items are contained in the hash table.

 @Param[in]     p_HashTable - A pointer to a hash table instance.

 @Return        TRUE when empty , FALSE otherwise.
*//***************************************************************************/
int32_t HASH_IsEmpty(t_HashTable *p_HashTable);


/**************************************************************************//**
 @Function      HASH_Find

 @Description   Finds an entry that is equivalent to the given entry.

                Checks if in the bin that the hash function leads to, there's an
                item that causes the f_Compare to return TRUE when tested on it.
                if there is such an item return its address.

 @Param[in]     p_HashTable - A pointer to the hash table instance.
 @Param[in]     p_LookFor   - A pointer to the requested entry.
 @Param[in]     f_Compare   - The compare function.

 @Return        Pointer to an entry to the first item for which f_Compare
                returned TRUE.
*//***************************************************************************/
t_HashEntry * HASH_Find(t_HashTable *p_HashTable,
                        t_HashEntry *p_LookFor,
                        int32_t     (*f_Compare)(t_HashEntry*, t_HashEntry*));


/**************************************************************************//**
 @Function      HASH_DelInit

 @Description   Extracts an item from the hash table.

 @Param[in]     p_HashTable - A pointer to the hash table instance.
 @Param[in]     p_HashEntry - A pointer to the deleted entry.

 @Return        None.
*//***************************************************************************/
void HASH_DelInit(t_HashTable* p_HashTable, t_HashEntry *p_HashEntry);


/** @} */ /* end of group hash_id */
/** @} */ /* end of group etc_id */

#endif /* __HASH_EXT_H */

