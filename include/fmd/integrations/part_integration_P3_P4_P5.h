/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**

 @File          part_integration_P3_P4_P5.h

 @Description   P4080/P5020/P3041 external definitions and structures.
*//***************************************************************************/
#ifndef __PART_INTEGRATION_P3_P4_P5_H
#define __PART_INTEGRATION_P3_P4_P5_H

#include "std_ext.h"
#include "dpaa_integration_ext.h"

#ifndef P1023

/**************************************************************************//**
 @Group         P5020_chip_id P5020 Application Programming Interface

 @Description   P5020 Chip functions,definitions and enums.

 @{
*//***************************************************************************/

#define CORE_E500MC

#define INTG_MAX_NUM_OF_CORES   1
#define CORE_GetId()            0
#define CORE_IS_BIG_ENDIAN
#define SYS_ANY_CORE    ((uint32_t)-1)  /**< Assignment to any valid core */
#define SYS_IS_MASTER_CORE()    TRUE


/**************************************************************************//**
 @Description   Module types.
*//***************************************************************************/
typedef enum e_ModuleId
{
    e_MODULE_ID_DUART_1 = 0,
    e_MODULE_ID_DUART_2,
    e_MODULE_ID_DUART_3,
    e_MODULE_ID_DUART_4,
    e_MODULE_ID_LAW,
    e_MODULE_ID_LBC,
    e_MODULE_ID_PAMU,
    e_MODULE_ID_QM,                 /**< Queue manager module */
    e_MODULE_ID_BM,                 /**< Buffer manager module */
    e_MODULE_ID_QM_CE_PORTAL_0,
    e_MODULE_ID_QM_CI_PORTAL_0,
    e_MODULE_ID_QM_CE_PORTAL_1,
    e_MODULE_ID_QM_CI_PORTAL_1,
    e_MODULE_ID_QM_CE_PORTAL_2,
    e_MODULE_ID_QM_CI_PORTAL_2,
    e_MODULE_ID_QM_CE_PORTAL_3,
    e_MODULE_ID_QM_CI_PORTAL_3,
    e_MODULE_ID_QM_CE_PORTAL_4,
    e_MODULE_ID_QM_CI_PORTAL_4,
    e_MODULE_ID_QM_CE_PORTAL_5,
    e_MODULE_ID_QM_CI_PORTAL_5,
    e_MODULE_ID_QM_CE_PORTAL_6,
    e_MODULE_ID_QM_CI_PORTAL_6,
    e_MODULE_ID_QM_CE_PORTAL_7,
    e_MODULE_ID_QM_CI_PORTAL_7,
    e_MODULE_ID_QM_CE_PORTAL_8,
    e_MODULE_ID_QM_CI_PORTAL_8,
    e_MODULE_ID_QM_CE_PORTAL_9,
    e_MODULE_ID_QM_CI_PORTAL_9,
    e_MODULE_ID_BM_CE_PORTAL_0,
    e_MODULE_ID_BM_CI_PORTAL_0,
    e_MODULE_ID_BM_CE_PORTAL_1,
    e_MODULE_ID_BM_CI_PORTAL_1,
    e_MODULE_ID_BM_CE_PORTAL_2,
    e_MODULE_ID_BM_CI_PORTAL_2,
    e_MODULE_ID_BM_CE_PORTAL_3,
    e_MODULE_ID_BM_CI_PORTAL_3,
    e_MODULE_ID_BM_CE_PORTAL_4,
    e_MODULE_ID_BM_CI_PORTAL_4,
    e_MODULE_ID_BM_CE_PORTAL_5,
    e_MODULE_ID_BM_CI_PORTAL_5,
    e_MODULE_ID_BM_CE_PORTAL_6,
    e_MODULE_ID_BM_CI_PORTAL_6,
    e_MODULE_ID_BM_CE_PORTAL_7,
    e_MODULE_ID_BM_CI_PORTAL_7,
    e_MODULE_ID_BM_CE_PORTAL_8,
    e_MODULE_ID_BM_CI_PORTAL_8,
    e_MODULE_ID_BM_CE_PORTAL_9,
    e_MODULE_ID_BM_CI_PORTAL_9,
    e_MODULE_ID_FM1,                /**< Frame manager #1 module */
    e_MODULE_ID_FM1_RTC,            /**< FM Real-Time-Clock */
    e_MODULE_ID_FM1_MURAM,          /**< FM Multi-User-RAM */
    e_MODULE_ID_FM1_BMI,            /**< FM BMI block */
    e_MODULE_ID_FM1_QMI,            /**< FM QMI block */
    e_MODULE_ID_FM1_PRS,            /**< FM parser block */
    e_MODULE_ID_FM1_PORT_HO0,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM1_PORT_HO1,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM1_PORT_HO2,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM1_PORT_HO3,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM1_PORT_HO4,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM1_PORT_HO5,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM1_PORT_HO6,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM1_PORT_1GRx0,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GRx1,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GRx2,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GRx3,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GRx4,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_10GRx0,    /**< FM Rx 10G MAC port block */
    e_MODULE_ID_FM1_PORT_1GTx0,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GTx1,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GTx2,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GTx3,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_1GTx4,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM1_PORT_10GTx0,    /**< FM Tx 10G MAC port block */
    e_MODULE_ID_FM1_PLCR,           /**< FM Policer */
    e_MODULE_ID_FM1_KG,             /**< FM Keygen */
    e_MODULE_ID_FM1_DMA,            /**< FM DMA */
    e_MODULE_ID_FM1_FPM,            /**< FM FPM */
    e_MODULE_ID_FM1_IRAM,           /**< FM Instruction-RAM */
    e_MODULE_ID_FM1_1GMDIO0,        /**< FM 1G MDIO MAC 0*/
    e_MODULE_ID_FM1_1GMDIO1,        /**< FM 1G MDIO MAC 1*/
    e_MODULE_ID_FM1_1GMDIO2,        /**< FM 1G MDIO MAC 2*/
    e_MODULE_ID_FM1_1GMDIO3,        /**< FM 1G MDIO MAC 3*/
    e_MODULE_ID_FM1_10GMDIO,        /**< FM 10G MDIO */
    e_MODULE_ID_FM1_PRS_IRAM,       /**< FM SW-parser Instruction-RAM */
    e_MODULE_ID_FM1_1GMAC0,         /**< FM 1G MAC #0 */
    e_MODULE_ID_FM1_1GMAC1,         /**< FM 1G MAC #1 */
    e_MODULE_ID_FM1_1GMAC2,         /**< FM 1G MAC #2 */
    e_MODULE_ID_FM1_1GMAC3,         /**< FM 1G MAC #3 */
    e_MODULE_ID_FM1_10GMAC0,        /**< FM 10G MAC #0 */

    e_MODULE_ID_FM2,                /**< Frame manager #2 module */
    e_MODULE_ID_FM2_RTC,            /**< FM Real-Time-Clock */
    e_MODULE_ID_FM2_MURAM,          /**< FM Multi-User-RAM */
    e_MODULE_ID_FM2_BMI,            /**< FM BMI block */
    e_MODULE_ID_FM2_QMI,            /**< FM QMI block */
    e_MODULE_ID_FM2_PRS,            /**< FM parser block */
    e_MODULE_ID_FM2_PORT_HO0,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM2_PORT_HO1,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM2_PORT_HO2,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM2_PORT_HO3,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM2_PORT_HO4,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM2_PORT_HO5,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM2_PORT_HO6,       /**< FM Host-command/offline-parsing port block */
    e_MODULE_ID_FM2_PORT_1GRx0,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_1GRx1,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_1GRx2,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_1GRx3,     /**< FM Rx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_10GRx0,    /**< FM Rx 10G MAC port block */
    e_MODULE_ID_FM2_PORT_1GTx0,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_1GTx1,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_1GTx2,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_1GTx3,     /**< FM Tx 1G MAC port block */
    e_MODULE_ID_FM2_PORT_10GTx0,    /**< FM Tx 10G MAC port block */
    e_MODULE_ID_FM2_PLCR,           /**< FM Policer */
    e_MODULE_ID_FM2_KG,             /**< FM Keygen */
    e_MODULE_ID_FM2_DMA,            /**< FM DMA */
    e_MODULE_ID_FM2_FPM,            /**< FM FPM */
    e_MODULE_ID_FM2_IRAM,           /**< FM Instruction-RAM */
    e_MODULE_ID_FM2_1GMDIO0,        /**< FM 1G MDIO MAC 0*/
    e_MODULE_ID_FM2_1GMDIO1,        /**< FM 1G MDIO MAC 1*/
    e_MODULE_ID_FM2_1GMDIO2,        /**< FM 1G MDIO MAC 2*/
    e_MODULE_ID_FM2_1GMDIO3,        /**< FM 1G MDIO MAC 3*/
    e_MODULE_ID_FM2_10GMDIO,        /**< FM 10G MDIO */
    e_MODULE_ID_FM2_PRS_IRAM,       /**< FM SW-parser Instruction-RAM */
    e_MODULE_ID_FM2_1GMAC0,         /**< FM 1G MAC #0 */
    e_MODULE_ID_FM2_1GMAC1,         /**< FM 1G MAC #1 */
    e_MODULE_ID_FM2_1GMAC2,         /**< FM 1G MAC #2 */
    e_MODULE_ID_FM2_1GMAC3,         /**< FM 1G MAC #3 */
    e_MODULE_ID_FM2_10GMAC0,        /**< FM 10G MAC #0 */

    e_MODULE_ID_SEC_GEN,            /**< SEC 4.0 General registers      */
    e_MODULE_ID_SEC_QI,             /**< SEC 4.0 QI registers           */
    e_MODULE_ID_SEC_JQ0,            /**< SEC 4.0 JQ-0 registers         */
    e_MODULE_ID_SEC_JQ1,            /**< SEC 4.0 JQ-1 registers         */
    e_MODULE_ID_SEC_JQ2,            /**< SEC 4.0 JQ-2 registers         */
    e_MODULE_ID_SEC_JQ3,            /**< SEC 4.0 JQ-3 registers         */
    e_MODULE_ID_SEC_RTIC,           /**< SEC 4.0 RTIC registers         */
    e_MODULE_ID_SEC_DECO0_CCB0,     /**< SEC 4.0 DECO-0/CCB-0 registers */
    e_MODULE_ID_SEC_DECO1_CCB1,     /**< SEC 4.0 DECO-1/CCB-1 registers */
    e_MODULE_ID_SEC_DECO2_CCB2,     /**< SEC 4.0 DECO-2/CCB-2 registers */
    e_MODULE_ID_SEC_DECO3_CCB3,     /**< SEC 4.0 DECO-3/CCB-3 registers */
    e_MODULE_ID_SEC_DECO4_CCB4,     /**< SEC 4.0 DECO-4/CCB-4 registers */

    e_MODULE_ID_MPIC,               /**< MPIC */
    e_MODULE_ID_GPIO,               /**< GPIO */
    e_MODULE_ID_SERDES,             /**< SERDES */
    e_MODULE_ID_CPC_1,              /**< CoreNet-Platform-Cache 1 */
    e_MODULE_ID_CPC_2,              /**< CoreNet-Platform-Cache 2 */

    e_MODULE_ID_SRIO_PORTS,     	/**< RapidIO controller */
    e_MODULE_ID_SRIO_MU,        	/**< RapidIO messaging unit module */

    e_MODULE_ID_DUMMY_LAST
} e_ModuleId;

#define NUM_OF_MODULES  e_MODULE_ID_DUMMY_LAST

/**************************************************************************//**
 @Description   Transaction source id (for memory conrollers error reporting DDR,LBC,ECM).
*//***************************************************************************/
typedef enum e_TransSrc
{
    e_TRANS_SRC_LBC             = 0x4,  /**< Enhanced local bus      */
    e_TRANS_SRC_BOOTS           = 0xA,  /**< Boot sequencer          */
    e_TRANS_SRC_DDR1            = 0xF,  /**< DDR controller 1        */
    e_TRANS_SRC_CORE_INS_FETCH  = 0x10, /**< Processor (instruction) */
    e_TRANS_SRC_CORE_DATA       = 0x11, /**< Processor (data)        */
    e_TRANS_SRC_DMA             = 0x15  /**< DMA                     */
} e_TransSrc;

/**************************************************************************//**
 @Description   Local Access Window Target interface ID
*//***************************************************************************/
typedef enum e_P5020LawTargetId
{
    e_P5020_LAW_TARGET_BMAN            = 0x18,  /**< BMAN target interface ID */
    e_P5020_LAW_TARGET_LBC             = 0x1F,  /**< Local Bus target interface ID */
    e_P5020_LAW_TARGET_QMAN            = 0x3C,  /**< QMAN target interface ID */
    e_P5020_LAW_TARGET_CPC_DDR1        = 0x10,  /**< DDR controller 1 or CPC1 SRAM */
    e_P5020_LAW_TARGET_CPC_DDR2        = 0x11,  /**< DDR controller 2 or CPC2 SRAM */
    e_P5020_LAW_TARGET_DDR_INTERLEAVED = 0x14,  /**< DDR controller 1 or CPC1 SRAM */
    e_P5020_LAW_TARGET_DCSR            = 0x1D,  /**< DCSR */
    e_P5020_LAW_TARGET_NONE            = 0xFF   /**< None */
} e_P5020LawTargetId;

/***************************************************************
    P5020 general routines
****************************************************************/
/**************************************************************************//**
 @Group         P5020_init_grp P5020 Initialization Unit

 @Description   P5020 initialization unit API functions, definitions and enums

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   Part ID and revision number
*//***************************************************************************/
typedef enum e_P5020DeviceName
{
    e_P5020_REV_INVALID   = 0x00000000,   /**< Invalid revision      */
    e_P5020E_REV_1_0      = 0x82080010,   /**< P5020E with security, revision 1.0 */
    e_P5020E_REV_2_0      = 0x82080020    /**< P5020E with security, revision 2.0 */
} e_P5020DeviceName;

/**************************************************************************//**
 @Description   structure representing P5020 initialization parameters
*//***************************************************************************/
typedef struct
{
    uint64_t        ccsrBaseAddress;        /**< CCSR base address (virtual) */
    uint64_t        bmPortalsBaseAddress;   /**< Portals base address (virtual) */
    uint64_t        qmPortalsBaseAddress;   /**< Portals base address (virtual) */
    uint8_t         serdesLanesBank2;
    uint8_t         serdesLanesBank3;
    bool            (*f_BoardIsValidSerDesConfigurationCB) (uint8_t val);
    uint8_t         guestId;                /**< Guest partition ID */
} t_P5020Params;

/**************************************************************************//**
 @Description   structure representing P5020 SERDES initialization parameters
*//***************************************************************************/
typedef struct
{
    uint64_t        baseAddress;      /**< base address (virtual) */
    t_Handle        h_P5020;
    uint8_t         serdesLanesBank2;
    uint8_t         serdesLanesBank3;
} t_P5020SerdesParams;

/**************************************************************************//**
 @Description   SERDES lanes activation
*//***************************************************************************/
typedef enum e_SerDesLaneActivation
{
    e_SERDES_LANE_F,                /**<  */
    e_SERDES_LANE_H,                /**<  */
    e_SERDES_LANE_A_B,              /**<  */
    e_SERDES_LANE_C_D,              /**<  */
    e_SERDES_LANE_E_F,              /**<  */
    e_SERDES_LANE_G_H,              /**<  */
    e_SERDES_LANE_I_J,              /**<  */
    e_SERDES_LANE_A_B_C_D,          /**<  */
    e_SERDES_LANE_E_F_G_H,          /**<  */
    e_SERDES_LANE_A_B_C_D_E_F_G_H   /**<  */
} e_SerDesLaneActivation;

/**************************************************************************//**
 @Description   structure representing P5020 devices configuration
*//***************************************************************************/
typedef struct t_P5020Devices
{
    struct
    {
        struct
        {
            bool                    enabled;
            uint8_t                 serdesBank;
            uint16_t                serdesLane;     /**< Most significant bits represent lanes used by this bank,
                                                         one bit for lane, lane A is the first and so on, e.g.,
                                                         set 0xF000 for ABCD lanes */
            uint8_t                 ratio;
            bool                    divByTwo;
            bool                    isTwoHalfSgmii;
        } dtsecs[FM_MAX_NUM_OF_1G_MACS];
        struct
        {
            bool                    enabled;
            uint8_t                 serdesBank;
            uint16_t                serdesLane;
        } tgec;
    } fms[2];
} t_P5020DevParams;

/**************************************************************************//**
 @Function      P5020_ConfigAndInit

 @Description   General initiation of the chip registers.

 @Param[in]     p_P5020Params  - A pointer to data structure of parameters

 @Return        A handle to the P5020 data structure.
*//***************************************************************************/
t_Handle P5020_ConfigAndInit(t_P5020Params *p_P5020Params);

/**************************************************************************//**
 @Function      P5020_Free

 @Description   Free all resources.

 @Param[in]     h_P5020 - The handle of the initialized P5020 object.

 @Return        E_OK on success; Other value otherwise.
*//***************************************************************************/
t_Error P5020_Free(t_Handle h_P5020);

/**************************************************************************//**
 @Function      P5020_GetModulePhysBase

 @Description   returns the base address of a P5020 module's
                memory mapped registers.

 @Param[in]     h_P5020   - The handle of the initialized P5020 object.
 @Param[in]     module    - The module ID.

 @Return        Base address of module's memory mapped registers.
                ILLEGAL_BASE in case of non-existent module
*//***************************************************************************/
uint64_t P5020_GetModulePhysBase(t_Handle h_P5020, e_ModuleId module);

/**************************************************************************//**
 @Function      P5020_GetRevInfo

 @Description   This routine enables access to chip and revision information.

 @Param[in]     h_P5020 - The handle of the initialized P5020 object.

 @Return        Part ID and revision.
*//***************************************************************************/
e_P5020DeviceName P5020_GetRevInfo(t_Handle h_P5020);

/**************************************************************************//**
 @Function      P5020_GetE500Factor

 @Description   returns system multiplication factor.

 @Param[in]     h_P5020         - A handle to the P5020 object.
 @Param[in]     coreIndex       - core index.
 @Param[out]    p_E500MulFactor - returns E500 to CCB multification factor.
 @Param[out]    p_E500DivFactor - returns E500 to CCB division factor.

 @Return        E_OK on success; Other value otherwise.
*
*//***************************************************************************/
t_Error P5020_GetE500Factor(t_Handle h_P5020, uint8_t coreIndex, uint32_t *p_E500MulFactor, uint32_t *p_E500DivFactor);

/**************************************************************************//**
 @Function      P5020_GetCcbFactor

 @Description   returns system multiplication factor.

 @Param[in]     h_P5020 - The handle of the initialized P5020 object.

 @Return        System multiplication factor.
*//***************************************************************************/
uint32_t P5020_GetCcbFactor(t_Handle h_P5020);

/**************************************************************************//**
 @Function      P5020_GetDdrFactor

 @Description   returns the multiplication factor of the clock in for the DDR clock.

 @Param[in]     h_P080 - a handle to the P5020 object.

 @Return        System multiplication factor.
*//***************************************************************************/
uint32_t P5020_GetDdrFactor(t_Handle h_P5020);

/**************************************************************************//**
 @Function      P5020_GetDdrType

 @Description   returns the multiplication factor of the clock in for the DDR clock .

 @Param[in]     h_P080 - a handle to the P5020 object.
 @Param[out]    p_DdrType - returns DDR type DDR2/DDR3.

 @Return        E_OK on success; Other value otherwise.
*//***************************************************************************/
//t_Error P5020_GetDdrType(t_Handle h_P5020, e_DdrType *p_DdrType);

/**************************************************************************//**
 @Function      P5020_GetFmFactor

 @Description   returns FM multiplication factors. (This value is returned using
                two parameters to avoid using float parameter).

 @Param[in]     h_P5020         - The handle of the initialized P5020 object.
 @Param[in]     fmIndex         - fm index.
 @Param[out]    p_FmMulFactor   - returns E500 to CCB multification factor.
 @Param[out]    p_FmDivFactor   - returns E500 to CCB division factor.

 @Return        E_OK on success; Other value otherwise.
*//***************************************************************************/
t_Error  P5020_GetFmFactor(t_Handle h_P5020, uint8_t fmIndex, uint32_t *p_FmMulFactor, uint32_t *p_FmDivFactor);

/**************************************************************************//**
 @Function      P5020_Reset

 @Description   Reset the chip.

 @Param[in]     h_P5020 - The handle of the initialized P5020 object.
*//***************************************************************************/
void P5020_Reset(t_Handle h_P5020);

t_Error P5020_CoreTimeBaseEnable(t_Handle h_P5020);
t_Error P5020_CoreTimeBaseDisable(t_Handle h_P5020);

typedef enum e_SrdsPrtcl {
    SRDS_PRTCL_NONE = 0,
    SRDS_PRTCL_PCIE1,
    SRDS_PRTCL_PCIE2,
    SRDS_PRTCL_PCIE3,
    SRDS_PRTCL_SRIO1,
    SRDS_PRTCL_SRIO2,
    SRDS_PRTCL_SGMII_FM1,
    SRDS_PRTCL_SGMII_FM2,
    SRDS_PRTCL_XAUI_FM1,
    SRDS_PRTCL_XAUI_FM2,
    SRDS_PRTCL_AURORA
} e_SrdsPrtcl;
t_P5020DevParams * P5020_GetDevicesConfiguration(t_Handle h_P5020);
t_Error P5020_DeviceEnable(t_Handle h_P5020,e_ModuleId module, bool enable);
uint32_t P5020_GetRcwSrdsPrtcl(t_Handle h_P5020);
bool P5020_IsDeviceConfiguredInRcw(t_Handle h_P5020, e_SrdsPrtcl device);
bool P5020_IsSrdsLaneEnabledInRcw(t_Handle h_P5020, uint32_t lane);
t_Error P5020_PamuDisableBypass(t_Handle h_P5020, uint8_t pamuId, bool disable);
t_Error P5020_SetDevicesBankStatus(t_Handle h_P5020, uint8_t serdesBank, bool status);
t_Error P5020_DumpDevicesConfiguration(t_Handle h_P5020);

/** @} */ /* end of P5020_init_grp group */
/** @} */ /* end of P5020_grp group */


/*****************************************************************************
 INTEGRATION-SPECIFIC MODULE CODES
******************************************************************************/
#define MODULE_UNKNOWN          0x00000000
#define MODULE_MEM              0x00010000
#define MODULE_MM               0x00020000
#define MODULE_CORE             0x00030000
#define MODULE_P5020            0x00040000
#define MODULE_P5020_PLTFRM     0x00050000
#define MODULE_PM               0x00060000
#define MODULE_MMU              0x00070000
#define MODULE_PIC              0x00080000
#define MODULE_CPC              0x00090000
#define MODULE_DUART            0x000a0000
#define MODULE_SERDES           0x000b0000
#define MODULE_PIO              0x000c0000
#define MODULE_QM               0x000d0000
#define MODULE_BM               0x000e0000
#define MODULE_SEC              0x000f0000
#define MODULE_LAW              0x00100000
#define MODULE_LBC              0x00110000
#define MODULE_PAMU             0x00120000
#define MODULE_FM               0x00130000
#define MODULE_FM_MURAM         0x00140000
#define MODULE_FM_PCD           0x00150000
#define MODULE_FM_RTC           0x00160000
#define MODULE_FM_MAC           0x00170000
#define MODULE_FM_PORT          0x00180000
#define MODULE_DPA              0x00190000
#define MODULE_SRIO             0x00200000
#define MODULE_DMA              0x00100000

/*****************************************************************************
 PAMU INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
#define PAMU_NUM_OF_PARTITIONS  5

#define PAMU_PICS_AVICS_ERRATA_PAMU3

/*****************************************************************************
 LAW INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
#define LAW_NUM_OF_WINDOWS      32
#define LAW_MIN_WINDOW_SIZE     0x0000000000001000LL    /**< 4KB */
#define LAW_MAX_WINDOW_SIZE     0x0000002000000000LL    /**< 64GB */


/*****************************************************************************
 LBC INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
/**************************************************************************//**
 @Group         lbc_exception_grp LBC Exception Unit

 @Description   LBC Exception unit API functions, definitions and enums

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Anchor        lbc_exbm

 @Collection    LBC Errors Bit Mask

                These errors are reported through the exceptions callback..
                The values can be or'ed in any combination in the errors mask
                parameter of the errors report structure.

                These errors can also be passed as a bit-mask to
                LBC_EnableErrorChecking() or LBC_DisableErrorChecking(),
                for enabling or disabling error checking.
 @{
*//***************************************************************************/
#define LBC_ERR_BUS_MONITOR     0x80000000  /**< Bus monitor error */
#define LBC_ERR_PARITY_ECC      0x20000000  /**< Parity error for GPCM/UPM */
#define LBC_ERR_WRITE_PROTECT   0x04000000  /**< Write protection error */
#define LBC_ERR_ATOMIC_WRITE    0x00800000  /**< Atomic write error */
#define LBC_ERR_ATOMIC_READ     0x00400000  /**< Atomic read error */
#define LBC_ERR_CHIP_SELECT     0x00080000  /**< Unrecognized chip select */

#define LBC_ERR_ALL             (LBC_ERR_BUS_MONITOR | LBC_ERR_PARITY_ECC | \
                                 LBC_ERR_WRITE_PROTECT | LBC_ERR_ATOMIC_WRITE | \
                                 LBC_ERR_ATOMIC_READ | LBC_ERR_CHIP_SELECT)
                                            /**< All possible errors */
/* @} */
/** @} */ /* end of lbc_exception_grp group */

#define LBC_INCORRECT_ERROR_REPORT_ERRATA

#define LBC_NUM_OF_BANKS            8
#define LBC_MAX_CS_SIZE             0x0000000100000000LL
#define LBC_ATOMIC_OPERATION_SUPPORT
#define LBC_PARITY_SUPPORT
#define LBC_ADDRESS_HOLD_TIME_CTRL
#define LBC_HIGH_CLK_DIVIDERS
#define LBC_FCM_AVAILABLE

/*****************************************************************************
 GPIO INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
#define GPIO_NUM_OF_PORTS   1   /**< Number of ports in GPIO module;
                                     Each port contains up to 32 i/O pins. */

#define GPIO_VALID_PIN_MASKS  \
    { /* Port A */ 0xFFFFFFFF }

#define GPIO_VALID_INTR_MASKS \
    { /* Port A */ 0xFFFFFFFF }


/*****************************************************************************
 SerDes INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
#define SRDS_MAX_LANES      18
#define SRDS_MAX_BANK       3

#define SRDS_LANES  \
{                   \
    { 0, 152, 0 },     \
    { 1, 153, 0 },     \
    { 2, 154, 0 },     \
    { 3, 155, 0 },     \
    { 4, 156, 0 },     \
    { 5, 157, 0 },     \
    { 6, 158, 0 },     \
    { 7, 159, 0 },     \
    { 8, 160, 0 },     \
    { 9, 161, 0 },     \
    { 16, 162, 1 },    \
    { 17, 163, 1 },    \
    { 18, 164, 1 },    \
    { 19, 165, 1 },    \
    { 20, 170, 2 },    \
    { 21, 171, 2 },    \
    { 22, 172, 2 },    \
    { 23, 173, 2 },    \
}

/* valid Prtcl : 0x2,0x5,0x8,0xd,0xe,0xf,0x10,0x13,0x16,0x19,0x1d,0x22,0x25 */
#define SRDS_PRTCL_OPTIONS \
{   \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2,                                                                                                                \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,          \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE2, SRDS_PRTCL_PCIE2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,          \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,  \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_NONE, SRDS_PRTCL_NONE, SRDS_PRTCL_NONE, SRDS_PRTCL_NONE},                                                                                                               \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,  \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_NONE, SRDS_PRTCL_NONE, SRDS_PRTCL_NONE, SRDS_PRTCL_NONE},                                                                                                               \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2, SRDS_PRTCL_SGMII_FM2,                                                                                                                \
     SRDS_PRTCL_SGMII_FM1, SRDS_PRTCL_SGMII_FM1, SRDS_PRTCL_SGMII_FM1, SRDS_PRTCL_SGMII_FM1},                                                                                                               \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO2, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3,                                                                                                                                \
     SRDS_PRTCL_SGMII_FM1, SRDS_PRTCL_SGMII_FM1, SRDS_PRTCL_SGMII_FM1, SRDS_PRTCL_SGMII_FM1},                                                                                                               \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3, SRDS_PRTCL_NONE, SRDS_PRTCL_SRIO2, SRDS_PRTCL_NONE, SRDS_PRTCL_SRIO1, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                    \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1},                                                                                                                   \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  \
    {SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE1, SRDS_PRTCL_PCIE3, SRDS_PRTCL_PCIE3, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_SRIO1, SRDS_PRTCL_AURORA, SRDS_PRTCL_AURORA,                  \
     SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2, SRDS_PRTCL_XAUI_FM2,                                                                                                                    \
     SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1, SRDS_PRTCL_XAUI_FM1}                                                                                                                    \
}

#define SERDES_POWER_DOWN_SWAPPED_ERRATA_SERDES_A001
#define SERDES_POWER_DOWN_LANES_DONT_HOLD_SOFT_RESET_ERRATA_SERDES_A002
#define SERDES_POWER_DOWN_LANES_ERRATA_SERDES1
#define SERDES_REIDL_RCTL_ERRATA_SERDES2
#define SERDES_TEQ_TYPE_ERRATA_SERDES3
#define SERDES_TX_CLK_ERRATA_SERDES4
#define SERDES_PEX_PLL_BANDWIDTH_ERRATA_SERDES5
#define SERDES_OPAD_CTL_ERRATA_SERDES6
#define SERDES_PEX3_ON_BANK1_ERRATA_SERDES7
#define SERDES_PLL_JITTER_ERRATA_SERDES8
#define SERDES_INTERMITTENT_LANE_ERRATA_SERDES9


/*****************************************************************************
 CPC INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/

#define CPC_FLASH_INVALIDATE_ERRATA_CPC2
#define CPC_MAX_SIZE_SRAM_ERRATA_CPC4
#define CPC_MULTI_WAY_HITS_ERRATA_CPC6
#define CPC_DATA_SINGLE_BIT_ECC_ERRATA_CPC7
#define CPC_ECC_CHECKING_AND_CORRECTION_ERRATA_CPC9
#define CPC_HARDWARE_FLUSH_ERRATA_CPC10

#endif /* P1023 */

#endif /* __PART_INTEGRATION_P3_P4_P5_H */
