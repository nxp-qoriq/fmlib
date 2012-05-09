/******************************************************************************

 © 1995-2003, 2004, 2005-2012 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**************************************************************************//**
 @File          fm_ext.h

 @Description   FM Application Programming Interface.
*//***************************************************************************/
#ifndef __FM_EXT
#define __FM_EXT

#include "error_ext.h"
#include "std_ext.h"
#include "dpaa_ext.h"


/**************************************************************************//**
 @Group         lnx_usr_FM_grp Frame Manager API

 @Description   FM API functions, definitions and enums.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Group         lnx_usr_FM_lib_grp FM library

 @Description   FM API functions, definitions and enum's.

                The FM module is the main driver module and is a mandatory module
                for FM driver users. This module must be initialized first prior
                to any other drivers modules.
                The FM is a "singleton" module. It is responsible of the common
                HW modules: FPM, DMA, common QMI and common BMI initializations and
                run-time control routines. This module must be initialized always
                when working with any of the FM modules.
                NOTE - We assume that the FMlibrary will be initialize only by core No. 0!

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   Enum for defining port types
*//***************************************************************************/
typedef enum e_FmPortType {
    e_FM_PORT_TYPE_OH_OFFLINE_PARSING = 0,  /**< Offline parsing port */
    e_FM_PORT_TYPE_RX,                      /**< 1G Rx port */
    e_FM_PORT_TYPE_RX_10G,                  /**< 10G Rx port */
    e_FM_PORT_TYPE_TX,                      /**< 1G Tx port */
    e_FM_PORT_TYPE_TX_10G,                  /**< 10G Tx port */
    e_FM_PORT_TYPE_DUMMY
} e_FmPortType;

/**************************************************************************//**
 @Description   Parse results memory layout
*//***************************************************************************/
typedef _Packed struct t_FmPrsResult {
    volatile uint8_t     lpid;               /**< Logical port id */
    volatile uint8_t     shimr;              /**< Shim header result  */
    volatile uint16_t    l2r;                /**< Layer 2 result */
    volatile uint16_t    l3r;                /**< Layer 3 result */
    volatile uint8_t     l4r;                /**< Layer 4 result */
    volatile uint8_t     cplan;              /**< Classification plan id */
    volatile uint16_t    nxthdr;             /**< Next Header  */
    volatile uint16_t    cksum;              /**< Checksum */
    volatile uint16_t    flags_frag_off;     /**< Flags & fragment-offset field of the last IP-header */
    volatile uint8_t     route_type;         /**< Routing type field of a IPv6 routing extension header */
    volatile uint8_t     rhp_ip_valid;       /**< Routing Extension Header Present; last bit is IP valid */
    volatile uint8_t     shim_off[2];        /**< Shim offset */
    volatile uint8_t     ip_pid_off;         /**< IP PID (last IP-proto) offset */
    volatile uint8_t     eth_off;            /**< ETH offset */
    volatile uint8_t     llc_snap_off;       /**< LLC_SNAP offset */
    volatile uint8_t     vlan_off[2];        /**< VLAN offset */
    volatile uint8_t     etype_off;          /**< ETYPE offset */
    volatile uint8_t     pppoe_off;          /**< PPP offset */
    volatile uint8_t     mpls_off[2];        /**< MPLS offset */
    volatile uint8_t     ip_off[2];          /**< IP offset */
    volatile uint8_t     gre_off;            /**< GRE offset */
    volatile uint8_t     l4_off;             /**< Layer 4 offset */
    volatile uint8_t     nxthdr_off;         /**< Parser end point */
} _PackedType t_FmPrsResult;

/**************************************************************************//**
 @Collection   FM Parser results
*//***************************************************************************/
#define FM_PR_L2_VLAN_STACK         0x00000100  /**< Parse Result: VLAN stack */
#define FM_PR_L2_ETHERNET           0x00008000  /**< Parse Result: Ethernet*/
#define FM_PR_L2_VLAN               0x00004000  /**< Parse Result: VLAN */
#define FM_PR_L2_LLC_SNAP           0x00002000  /**< Parse Result: LLC_SNAP */
#define FM_PR_L2_MPLS               0x00001000  /**< Parse Result: MPLS */
#define FM_PR_L2_PPPoE              0x00000800  /**< Parse Result: PPPoE */
/* @} */

/**************************************************************************//**
 @Collection   FM Frame descriptor macros
*//***************************************************************************/
#define FM_FD_CMD_FCO               0x80000000  /**< Frame queue Context Override */
#define FM_FD_CMD_RPD               0x40000000  /**< Read Prepended Data */
#define FM_FD_CMD_UPD               0x20000000  /**< Update Prepended Data */
#define FM_FD_CMD_DTC               0x10000000  /**< Do L4 Checksum */
#define FM_FD_CMD_DCL4C             0x10000000  /**< Didn't calculate L4 Checksum */
#define FM_FD_CMD_CFQ               0x00ffffff  /**< Confirmation Frame Queue */

#define FM_FD_TX_STATUS_ERR_MASK    0x07000000  /**< TX Error FD bits */
#define FM_FD_RX_STATUS_ERR_MASK    0x073ee3f8  /**< RX Error FD bits */
#define FM_FD_RX_STATUS_ERR_NON_FM  0x00400000  /**< non Frame-Manager error */
/* @} */

/**************************************************************************//**
 @Description   Context A
*//***************************************************************************/
typedef _Packed struct t_FmContextA {
    volatile uint32_t    command;   /**< ContextA Command */
    volatile uint8_t     res0[4];   /**< ContextA Reserved bits */
} _PackedType t_FmContextA;

/**************************************************************************//**
 @Description   Context B
*//***************************************************************************/
typedef uint32_t t_FmContextB;

/**************************************************************************//**
 @Collection   Special Operation options
*//***************************************************************************/
typedef uint32_t fmSpecialOperations_t;                 /**< typedef for defining Special Operation options */

#define  FM_SP_OP_IPSEC                     0x80000000  /**< activate features that related to IPSec (e.g fix Eth-type) */
#define  FM_SP_OP_IPSEC_UPDATE_UDP_LEN      0x40000000  /**< update the UDP-Len after Encryption */
#define  FM_SP_OP_IPSEC_MANIP               0x20000000  /**< handle the IPSec-manip options */
#define  FM_SP_OP_RPD                       0x10000000  /**< Set the RPD bit */
#define  FM_SP_OP_DCL4C                     0x08000000  /**< Set the DCL4C bit */
#define  FM_SP_OP_CHECK_SEC_ERRORS          0x04000000  /**< Check SEC errors */
/* @} */

/**************************************************************************//**
 @Collection   Context A macros
*//***************************************************************************/
#define FM_CONTEXTA_OVERRIDE_MASK       0x80000000
#define FM_CONTEXTA_ICMD_MASK           0x40000000
#define FM_CONTEXTA_A1_VALID_MASK       0x20000000
#define FM_CONTEXTA_MACCMD_MASK         0x00ff0000
#define FM_CONTEXTA_MACCMD_VALID_MASK   0x00800000
#define FM_CONTEXTA_MACCMD_SECURED_MASK 0x00100000
#define FM_CONTEXTA_MACCMD_SC_MASK      0x000f0000
#define FM_CONTEXTA_A1_MASK             0x0000ffff

#define FM_CONTEXTA_GET_OVERRIDE(contextA)                 ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_OVERRIDE_MASK) >> (31-0))
#define FM_CONTEXTA_GET_ICMD(contextA)                     ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_ICMD_MASK) >> (31-1))
#define FM_CONTEXTA_GET_A1_VALID(contextA)                 ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_A1_VALID_MASK) >> (31-2))
#define FM_CONTEXTA_GET_A1(contextA)                       ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_A1_MASK) >> (31-31))
#define FM_CONTEXTA_GET_MACCMD(contextA)                   ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_MACCMD_MASK) >> (31-15))
#define FM_CONTEXTA_GET_MACCMD_VALID(contextA)             ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_MACCMD_VALID_MASK) >> (31-8))
#define FM_CONTEXTA_GET_MACCMD_SECURED(contextA)           ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_MACCMD_SECURED_MASK) >> (31-11))
#define FM_CONTEXTA_GET_MACCMD_SECURE_CHANNEL(contextA)    ((((t_FmContextA *)contextA)->command & FM_CONTEXTA_MACCMD_SC_MASK) >> (31-15))

#define FM_CONTEXTA_SET_OVERRIDE(contextA,val)              (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_OVERRIDE_MASK) | (((uint32_t)(val) << (31-0)) & FM_CONTEXTA_OVERRIDE_MASK) ))
#define FM_CONTEXTA_SET_ICMD(contextA,val)                  (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_ICMD_MASK) | (((val) << (31-1)) & FM_CONTEXTA_ICMD_MASK) ))
#define FM_CONTEXTA_SET_A1_VALID(contextA,val)              (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_A1_VALID_MASK) | (((val) << (31-2)) & FM_CONTEXTA_A1_VALID_MASK) ))
#define FM_CONTEXTA_SET_A1(contextA,val)                    (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_A1_MASK) | (((val) << (31-31)) & FM_CONTEXTA_A1_MASK) ))
#define FM_CONTEXTA_SET_MACCMD(contextA,val)                (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_MACCMD_MASK) | (((val) << (31-15)) & FM_CONTEXTA_MACCMD_MASK) ))
#define FM_CONTEXTA_SET_MACCMD_VALID(contextA,val)          (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_MACCMD_VALID_MASK) | (((val) << (31-8)) & FM_CONTEXTA_MACCMD_VALID_MASK) ))
#define FM_CONTEXTA_SET_MACCMD_SECURED(contextA,val)        (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_MACCMD_SECURED_MASK) | (((val) << (31-11)) & FM_CONTEXTA_MACCMD_SECURED_MASK) ))
#define FM_CONTEXTA_SET_MACCMD_SECURE_CHANNEL(contextA,val) (((t_FmContextA *)contextA)->command = (uint32_t)((((t_FmContextA *)contextA)->command & ~FM_CONTEXTA_MACCMD_SC_MASK) | (((val) << (31-15)) & FM_CONTEXTA_MACCMD_SC_MASK) ))
/* @} */

/**************************************************************************//**
 @Collection   Context B macros
*//***************************************************************************/
#define FM_CONTEXTB_FQID_MASK               0x00ffffff

#define FM_CONTEXTB_GET_FQID(contextB)      (*((t_FmContextB *)contextB) & FM_CONTEXTB_FQID_MASK)
#define FM_CONTEXTB_SET_FQID(contextB,val)  (*((t_FmContextB *)contextB) = ((*((t_FmContextB *)contextB) & ~FM_CONTEXTB_FQID_MASK) | ((val) & FM_CONTEXTB_FQID_MASK)))
/* @} */

#if defined(__MWERKS__) && !defined(__GNUC__)
#pragma pack(pop)
#endif /* defined(__MWERKS__) && ... */


/**************************************************************************//**
 @Description   FM Exceptions
*//***************************************************************************/
typedef enum e_FmExceptions {
    e_FM_EX_DMA_BUS_ERROR,              /**< DMA bus error. */
    e_FM_EX_DMA_READ_ECC,               /**< Read Buffer ECC error (Valid for FM rev < 6)*/
    e_FM_EX_DMA_SYSTEM_WRITE_ECC,       /**< Write Buffer ECC error on system side (Valid for FM rev < 6)*/
    e_FM_EX_DMA_FM_WRITE_ECC,           /**< Write Buffer ECC error on FM side (Valid for FM rev < 6)*/
    e_FM_EX_DMA_SINGLE_PORT_ECC,        /**< Single Port ECC error on FM side (Valid for FM rev > 6)*/
    e_FM_EX_FPM_STALL_ON_TASKS,         /**< Stall of tasks on FPM */
    e_FM_EX_FPM_SINGLE_ECC,             /**< Single ECC on FPM. */
    e_FM_EX_FPM_DOUBLE_ECC,             /**< Double ECC error on FPM ram access */
    e_FM_EX_QMI_SINGLE_ECC,             /**< Single ECC on QMI. */
    e_FM_EX_QMI_DOUBLE_ECC,             /**< Double bit ECC occurred on QMI */
    e_FM_EX_QMI_DEQ_FROM_UNKNOWN_PORTID,/**< Dequeue from unknown port id */
    e_FM_EX_BMI_LIST_RAM_ECC,           /**< Linked List RAM ECC error */
    e_FM_EX_BMI_STORAGE_PROFILE_ECC,    /**< Storage Profile ECC Error */
    e_FM_EX_BMI_STATISTICS_RAM_ECC,     /**< Statistics Count RAM ECC Error Enable */
    e_FM_EX_BMI_DISPATCH_RAM_ECC,       /**< Dispatch RAM ECC Error Enable */
    e_FM_EX_IRAM_ECC,                   /**< Double bit ECC occurred on IRAM*/
    e_FM_EX_MURAM_ECC                   /**< Double bit ECC occurred on MURAM*/
} e_FmExceptions;

/**************************************************************************//**
 @Group         lnx_usr_FM_init_grp FM Initialization Unit

 @Description   FM Initialization Unit

                Initialization Flow
                Initialization of the FM Module will be carried out by the application
                according to the following sequence:
                -  Calling the configuration routine with basic parameters.
                -  Calling the advance initialization routines to change driver's defaults.
                -  Calling the initialization routine.

 @{
*//***************************************************************************/

t_Handle FM_Open(uint8_t id);
void     FM_Close(t_Handle h_Fm);

/** @} */ /* end of lnx_usr_FM_init_grp group */


/**************************************************************************//**
 @Group         lnx_usr_FM_runtime_control_grp FM Runtime Control Unit

 @Description   FM Runtime control unit API functions, definitions and enum's.
                The FM driver provides a set of control routines.
                These routines may only be called after the module was fully
                initialized (both configuration and initialization routines were
                called). They are typically used to get information from hardware
                (status, counters/statistics, revision etc.), to modify a current
                state or to force/enable a required action. Run-time control may
                be called whenever necessary and as many times as needed.
 @{
*//***************************************************************************/

/**************************************************************************//**
 @Collection   General FM defines.
*//***************************************************************************/
#define FM_MAX_NUM_OF_VALID_PORTS   (FM_MAX_NUM_OF_OH_PORTS +       \
                                     FM_MAX_NUM_OF_1G_RX_PORTS +    \
                                     FM_MAX_NUM_OF_10G_RX_PORTS +   \
                                     FM_MAX_NUM_OF_1G_TX_PORTS +    \
                                     FM_MAX_NUM_OF_10G_TX_PORTS)      /**< Number of available FM ports */

/**************************************************************************//**
 @Description   A Structure for Port bandwidth requirement. Port is identified
                by type and relative id.
*//***************************************************************************/
typedef struct t_FmPortBandwidth {
    e_FmPortType        type;           /**< FM port type */
    uint8_t             relativePortId; /**< Type relative port id */
    uint8_t             bandwidth;      /**< bandwidth - (in term of percents) */
} t_FmPortBandwidth;

/**************************************************************************//**
 @Description   A Structure containing an array of Port bandwidth requirements.
                The user should state the ports requiring bandwidth in terms of
                percentage - i.e. all port's bandwidths in the array must add
                up to 100.
*//***************************************************************************/
typedef struct t_FmPortsBandwidthParams {
    uint8_t             numOfPorts;         /**< The number of relevant ports, which is the
                                                 number of valid entries in the array below */
    t_FmPortBandwidth   portsBandwidths[FM_MAX_NUM_OF_VALID_PORTS];
                                            /**< for each port, it's bandwidth (all port's
                                                 bandwidths must add up to 100.*/
} t_FmPortsBandwidthParams;

/**************************************************************************//**
 @Description   enum for defining FM counters
*//***************************************************************************/
typedef enum e_FmCounters {
    e_FM_COUNTERS_ENQ_TOTAL_FRAME = 0,              /**< QMI total enqueued frames counter */
    e_FM_COUNTERS_DEQ_TOTAL_FRAME,                  /**< QMI total dequeued frames counter */
    e_FM_COUNTERS_DEQ_0,                            /**< QMI 0 frames from QMan counter */
    e_FM_COUNTERS_DEQ_1,                            /**< QMI 1 frames from QMan counter */
    e_FM_COUNTERS_DEQ_2,                            /**< QMI 2 frames from QMan counter */
    e_FM_COUNTERS_DEQ_3,                            /**< QMI 3 frames from QMan counter */
    e_FM_COUNTERS_DEQ_FROM_DEFAULT,                 /**< QMI dequeue from default queue counter */
    e_FM_COUNTERS_DEQ_FROM_CONTEXT,                 /**< QMI dequeue from FQ context counter */
    e_FM_COUNTERS_DEQ_FROM_FD,                      /**< QMI dequeue from FD command field counter */
    e_FM_COUNTERS_DEQ_CONFIRM                       /**< QMI dequeue confirm counter */
} e_FmCounters;

/**************************************************************************//**
 @Description   A Structure for returning FM revision information
*//***************************************************************************/
typedef struct t_FmRevisionInfo {
    uint8_t         majorRev;               /**< Major revision */
    uint8_t         minorRev;               /**< Minor revision */
} t_FmRevisionInfo;

/**************************************************************************//**
 @Function      FM_SetPortsBandwidth

 @Description   Sets relative weights between ports when accessing common resources.

 @Param[in]     h_Fm                A handle to an FM Module.
 @Param[in]     p_PortsBandwidth    A structure of ports bandwidths in percentage, i.e.
                                    total must equal 100.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_Init().
                This routine should NOT be called from guest-partition
                (i.e. guestId != NCSW_MASTER_ID)
*//***************************************************************************/
t_Error FM_SetPortsBandwidth(t_Handle h_Fm, t_FmPortsBandwidthParams *p_PortsBandwidth);

/**************************************************************************//**
 @Function      FM_GetRevision

 @Description   Returns the FM revision

 @Param[in]     h_Fm                A handle to an FM Module.
 @Param[out]    p_FmRevisionInfo    A structure of revision information parameters.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_Init().
*//***************************************************************************/
t_Error  FM_GetRevision(t_Handle h_Fm, t_FmRevisionInfo *p_FmRevisionInfo);

/**************************************************************************//**
 @Function      FM_GetCounter

 @Description   Reads one of the FM counters.

 @Param[in]     h_Fm        A handle to an FM Module.
 @Param[in]     counter     The requested counter.

 @Return        Counter's current value.

 @Cautions      Allowed only following FM_Init().
                Note that it is user's responsibility to call this routine only
                for enabled counters, and there will be no indication if a
                disabled counter is accessed.
*//***************************************************************************/
uint32_t  FM_GetCounter(t_Handle h_Fm, e_FmCounters counter);

/**************************************************************************//**
 @Function      FM_ModifyCounter

 @Description   Sets a value to an enabled counter. Use "0" to reset the counter.

 @Param[in]     h_Fm        A handle to an FM Module.
 @Param[in]     counter     The requested counter.
 @Param[in]     val         The requested value to be written into the counter.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_Init().
                This routine should NOT be called from guest-partition
                (i.e. guestId != NCSW_MASTER_ID)
*//***************************************************************************/
t_Error  FM_ModifyCounter(t_Handle h_Fm, e_FmCounters counter, uint32_t val);

/**************************************************************************//**
 @Function      FM_ForceIntr

 @Description   Causes an interrupt event on the requested source.

 @Param[in]     h_Fm            A handle to an FM Module.
 @Param[in]     exception       An exception to be forced.

 @Return        E_OK on success; Error code if the exception is not enabled,
                or is not able to create interrupt.

 @Cautions      Allowed only following FM_Init().
                This routine should NOT be called from guest-partition
                (i.e. guestId != NCSW_MASTER_ID)
*//***************************************************************************/
t_Error FM_ForceIntr (t_Handle h_Fm, e_FmExceptions exception);

/** @} */ /* end of lnx_usr_FM_runtime_control_grp group */
/** @} */ /* end of lnx_usr_FM_lib_grp group */
/** @} */ /* end of lnx_usr_FM_grp group */


#endif /* __FM_EXT */
