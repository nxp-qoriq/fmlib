/*
 * Copyright 2008-2012 Freescale Semiconductor, Inc
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *      * Neither the name of Freescale Semiconductor nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * This software is provided by Freescale Semiconductor "as is" and any
 * express or implied warranties, including, but not limited to, the implied
 * warranties of merchantability and fitness for a particular purpose are
 * disclaimed. In no event shall Freescale Semiconductor be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential damages
 * (including, but not limited to, procurement of substitute goods or services;
 * loss of use, data, or profits; or business interruption) however caused and
 * on any theory of liability, whether in contract, strict liability, or tort
 * (including negligence or otherwise) arising in any way out of the use of
 * this software, even if advised of the possibility of such damage.
 */

/**************************************************************************//**
 @File          enet_ext.h

 @Description   Ethernet generic definitions and enums.
*//***************************************************************************/

#ifndef __ENET_EXT_H
#define __ENET_EXT_H


#define ENET_NUM_OCTETS_PER_ADDRESS 6     /**< Number of octets (8-bit bytes) in an ethernet address */
#define ENET_GROUP_ADDR             0x01  /**< Group address mask for ethernet addresses */


/**************************************************************************//**
 @Description   Ethernet Address
*//***************************************************************************/
typedef uint8_t t_EnetAddr[ENET_NUM_OCTETS_PER_ADDRESS];

/**************************************************************************//**
 @Description   Ethernet Address Type.
*//***************************************************************************/
typedef enum e_EnetAddrType
{
    e_ENET_ADDR_TYPE_INDIVIDUAL,    /**< Individual (unicast) address */
    e_ENET_ADDR_TYPE_GROUP,         /**< Group (multicast) address */
    e_ENET_ADDR_TYPE_BROADCAST      /**< Broadcast address */
} e_EnetAddrType;


/**************************************************************************//**
 @Description   Ethernet MAC-PHY Interface
*//***************************************************************************/
typedef enum e_EnetInterface
{
    e_ENET_IF_MII   = 0x00010000,   /**< MII interface */
    e_ENET_IF_RMII  = 0x00020000,   /**< RMII interface */
    e_ENET_IF_SMII  = 0x00030000,   /**< SMII interface */
    e_ENET_IF_GMII  = 0x00040000,   /**< GMII interface */
    e_ENET_IF_RGMII = 0x00050000,   /**< RGMII interface */
    e_ENET_IF_TBI   = 0x00060000,   /**< TBI interface */
    e_ENET_IF_RTBI  = 0x00070000,   /**< RTBI interface */
    e_ENET_IF_SGMII = 0x00080000,   /**< SGMII interface */
    e_ENET_IF_XGMII = 0x00090000,   /**< XGMII interface */
    e_ENET_IF_QSGMII= 0x000a0000,   /**< QSGMII interface */
    e_ENET_IF_XFI   = 0x000b0000    /**< XFI interface */
} e_EnetInterface;

/**************************************************************************//**
 @Description   Ethernet Duplex Mode
*//***************************************************************************/
typedef enum e_EnetDuplexMode
{
    e_ENET_HALF_DUPLEX,             /**< Half-Duplex mode */
    e_ENET_FULL_DUPLEX              /**< Full-Duplex mode */
} e_EnetDuplexMode;

/**************************************************************************//**
 @Description   Ethernet Speed (nominal data rate)
*//***************************************************************************/
typedef enum e_EnetSpeed
{
    e_ENET_SPEED_10     = 10,       /**< 10 Mbps */
    e_ENET_SPEED_100    = 100,      /**< 100 Mbps */
    e_ENET_SPEED_1000   = 1000,     /**< 1000 Mbps = 1 Gbps */
    e_ENET_SPEED_10000  = 10000     /**< 10000 Mbps = 10 Gbps */
} e_EnetSpeed;

/**************************************************************************//**
 @Description   Ethernet mode (combination of MAC-PHY interface and speed)
*//***************************************************************************/
typedef enum e_EnetMode
{
    e_ENET_MODE_INVALID     = 0,                                        /**< Invalid Ethernet mode */
    e_ENET_MODE_MII_10      = (e_ENET_IF_MII   | e_ENET_SPEED_10),      /**<    10 Mbps MII   */
    e_ENET_MODE_MII_100     = (e_ENET_IF_MII   | e_ENET_SPEED_100),     /**<   100 Mbps MII   */
    e_ENET_MODE_RMII_10     = (e_ENET_IF_RMII  | e_ENET_SPEED_10),      /**<    10 Mbps RMII  */
    e_ENET_MODE_RMII_100    = (e_ENET_IF_RMII  | e_ENET_SPEED_100),     /**<   100 Mbps RMII  */
    e_ENET_MODE_SMII_10     = (e_ENET_IF_SMII  | e_ENET_SPEED_10),      /**<    10 Mbps SMII  */
    e_ENET_MODE_SMII_100    = (e_ENET_IF_SMII  | e_ENET_SPEED_100),     /**<   100 Mbps SMII  */
    e_ENET_MODE_GMII_1000   = (e_ENET_IF_GMII  | e_ENET_SPEED_1000),    /**<  1000 Mbps GMII  */
    e_ENET_MODE_RGMII_10    = (e_ENET_IF_RGMII | e_ENET_SPEED_10),      /**<    10 Mbps RGMII */
    e_ENET_MODE_RGMII_100   = (e_ENET_IF_RGMII | e_ENET_SPEED_100),     /**<   100 Mbps RGMII */
    e_ENET_MODE_RGMII_1000  = (e_ENET_IF_RGMII | e_ENET_SPEED_1000),    /**<  1000 Mbps RGMII */
    e_ENET_MODE_TBI_1000    = (e_ENET_IF_TBI   | e_ENET_SPEED_1000),    /**<  1000 Mbps TBI   */
    e_ENET_MODE_RTBI_1000   = (e_ENET_IF_RTBI  | e_ENET_SPEED_1000),    /**<  1000 Mbps RTBI  */
    e_ENET_MODE_SGMII_10    = (e_ENET_IF_SGMII | e_ENET_SPEED_10),      /**<    10 Mbps SGMII */
    e_ENET_MODE_SGMII_100   = (e_ENET_IF_SGMII | e_ENET_SPEED_100),     /**<   100 Mbps SGMII */
    e_ENET_MODE_SGMII_1000  = (e_ENET_IF_SGMII | e_ENET_SPEED_1000),    /**<  1000 Mbps SGMII */
    e_ENET_MODE_XGMII_10000 = (e_ENET_IF_XGMII | e_ENET_SPEED_10000),   /**< 10000 Mbps XGMII */
    e_ENET_MODE_QSGMII_1000 = (e_ENET_IF_QSGMII| e_ENET_SPEED_1000),    /**<  1000 Mbps QSGMII */
    e_ENET_MODE_XFI_10000   = (e_ENET_IF_XFI   | e_ENET_SPEED_10000)    /**< 10000 Mbps XFI */
} e_EnetMode;


#define IS_ENET_MODE_VALID(mode) \
        (((mode) == e_ENET_MODE_MII_10     ) || \
         ((mode) == e_ENET_MODE_MII_100    ) || \
         ((mode) == e_ENET_MODE_RMII_10    ) || \
         ((mode) == e_ENET_MODE_RMII_100   ) || \
         ((mode) == e_ENET_MODE_SMII_10    ) || \
         ((mode) == e_ENET_MODE_SMII_100   ) || \
         ((mode) == e_ENET_MODE_GMII_1000  ) || \
         ((mode) == e_ENET_MODE_RGMII_10   ) || \
         ((mode) == e_ENET_MODE_RGMII_100  ) || \
         ((mode) == e_ENET_MODE_RGMII_1000 ) || \
         ((mode) == e_ENET_MODE_TBI_1000   ) || \
         ((mode) == e_ENET_MODE_RTBI_1000  ) || \
         ((mode) == e_ENET_MODE_SGMII_10   ) || \
         ((mode) == e_ENET_MODE_SGMII_100  ) || \
         ((mode) == e_ENET_MODE_SGMII_1000 ) || \
         ((mode) == e_ENET_MODE_XGMII_10000) || \
         ((mode) == e_ENET_MODE_QSGMII_1000) || \
         ((mode) == e_ENET_MODE_XFI_10000))


#define MAKE_ENET_MODE(_interface, _speed)     (e_EnetMode)((_interface) | (_speed))

#define ENET_INTERFACE_FROM_MODE(mode)          (e_EnetInterface)((mode) & 0xFFFF0000)
#define ENET_SPEED_FROM_MODE(mode)              (e_EnetSpeed)((mode) & 0x0000FFFF)

#define ENET_ADDR_TO_UINT64(_enetAddr)                  \
        (uint64_t)(((uint64_t)(_enetAddr)[0] << 40) |   \
                   ((uint64_t)(_enetAddr)[1] << 32) |   \
                   ((uint64_t)(_enetAddr)[2] << 24) |   \
                   ((uint64_t)(_enetAddr)[3] << 16) |   \
                   ((uint64_t)(_enetAddr)[4] << 8) |    \
                   ((uint64_t)(_enetAddr)[5]))

#define MAKE_ENET_ADDR_FROM_UINT64(_addr64, _enetAddr)              \
        do {                                                        \
            int i;                                                  \
            for (i=0; i < ENET_NUM_OCTETS_PER_ADDRESS; i++)         \
                (_enetAddr)[i] = (uint8_t)((_addr64) >> ((5-i)*8)); \
        } while (0)


#endif /* __ENET_EXT_H */
