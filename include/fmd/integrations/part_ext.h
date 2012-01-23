/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**************************************************************************//**

 @File          part_ext.h

 @Description   Definitions for the part (integration) module.
*//***************************************************************************/

#ifndef __PART_EXT_H
#define __PART_EXT_H

#ifdef P1023
#include "part_P1023.h"
#else
#include "part_P3_P4_P5.h"
#endif

#endif /* __PART_EXT_H */
