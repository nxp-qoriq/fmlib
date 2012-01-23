/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/******************************************************************************

 @File          sprint_ext.h

 @Description   Debug routines (externals).

*//***************************************************************************/

#ifndef __SPRINT_EXT_H
#define __SPRINT_EXT_H


#if defined(NCSW_LINUX) && defined(__KERNEL__)
#include <linux/kernel.h>

#elif defined(NCSW_LINUX_USD)
#include <stdio.h>
#include "stdarg_ext.h"
#include "std_ext.h"

extern int vsscanf(const char *, const char *, va_list);

#elif defined(NCSW_VXWORKS)
#include "private/stdioP.h"

#else
#include <stdio.h>
#endif /* defined(NCSW_LINUX) && defined(__KERNEL__) */

#include "std_ext.h"


/**************************************************************************//**
 @Group         etc_id   Utility Library Application Programming Interface

 @Description   External routines.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Group         sprint_id Sprint

 @Description   Sprint & Sscan module functions,definitions and enums.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Function      Sprint

 @Description   Format a string and place it in a buffer.

 @Param[in]     buff - The buffer to place the result into.
 @Param[in]     str  - The format string to use.
 @Param[in]     ...  - Arguments for the format string.

 @Return        Number of bytes formatted.
*//***************************************************************************/
int Sprint(char *buff, const char *str, ...);

/**************************************************************************//**
 @Function      Snprint

 @Description   Format a string and place it in a buffer.

 @Param[in]     buf  - The buffer to place the result into.
 @Param[in]     size - The size of the buffer, including the trailing null space.
 @Param[in]     fmt  - The format string to use.
 @Param[in]     ...  - Arguments for the format string.

 @Return        Number of bytes formatted.
*//***************************************************************************/
int Snprint(char * buf, uint32_t size, const char *fmt, ...);

/**************************************************************************//**
 @Function      Sscan

 @Description   Unformat a buffer into a list of arguments.

 @Param[in]     buf  - input buffer.
 @Param[in]     fmt  - formatting of buffer.
 @Param[out]    ...  - resulting arguments.

 @Return        Number of bytes unformatted.
*//***************************************************************************/
int Sscan(const char * buf, const char * fmt, ...);

/** @} */ /* end of sprint_id group */
/** @} */ /* end of etc_id group */


#endif /* __SPRINT_EXT_H */
