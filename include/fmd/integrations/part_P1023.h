/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**************************************************************************//**

 @File          part_P1023.h

 @Description   Definitions for the part (integration) module.
*//***************************************************************************/

#ifndef __PART_P1023_H
#define __PART_P1023_H

#include "std_ext.h"
#include "part_integration_ext.h"


#if !(defined(MPC8306) || defined(MPC8309) || defined(MPC834x) || defined(MPC836x) || defined(MPC832x) || defined(MPC837x) || defined(MPC8568) || defined(MPC8569) || defined(PSC9131) || defined(P1020) || defined(P1021) || defined(P1022) || defined(P1023) || defined(P2040) || defined(P3041) || defined(P4080) || defined(SC4080) || defined(P5020))
#error "unable to proceed without chip-definition"
#endif

#ifdef P1023

/**************************************************************************//*
 @Description   Part data structure - must be contained in any integration
                data structure.
*//***************************************************************************/
typedef struct t_Part
{
    uintptr_t   (* f_GetModuleBase)(t_Handle h_Part, e_ModuleId moduleId);
                /**< Returns the address of the module's memory map base. */
    e_ModuleId  (* f_GetModuleIdByBase)(t_Handle h_Part, uintptr_t baseAddress);
                /**< Returns the module's ID according to its memory map base. */
} t_Part;

#endif /* P1023 */

#endif /* __PART_P1023_H */
