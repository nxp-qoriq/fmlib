/******************************************************************************

 © 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
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
