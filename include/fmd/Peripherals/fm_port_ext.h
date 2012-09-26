/* Copyright (c) 2008-2012 Freescale Semiconductor, Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/**************************************************************************//**
 @File          fm_port_ext.h

 @Description   FM-Port Application Programming Interface.
*//***************************************************************************/
#ifndef __FM_PORT_EXT
#define __FM_PORT_EXT

#include "error_ext.h"
#include "std_ext.h"
#include "fm_pcd_ext.h"
#include "fm_ext.h"
#include "net_ext.h"


/**************************************************************************//**

 @Group         lnx_usr_FM_grp Frame Manager API

 @Description   FM API functions, definitions and enums

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_grp FM Port

 @Description   FM Port API

                The FM uses a general module called "port" to represent a Tx port
                (MAC), an Rx port (MAC) or Offline Parsing port.
                The number of ports in an FM varies between SOCs.
                The SW driver manages these ports as sub-modules of the FM, i.e.
                after an FM is initialized, its ports may be initialized and
                operated upon.

                The port is initialized aware of its type, but other functions on
                a port may be indifferent to its type. When necessary, the driver
                verifies coherence and returns error if applicable.

                On initialization, user specifies the port type and it's index
                (relative to the port's type). Host command and offline parsing
                ports share the same id range, i.e. the user may only initialize
                port 0 as either host command or offline parsing, but not both.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   An enum for defining port PCD modes.
                This enum defines the superset of PCD engines support - i.e. not
                all engines have to be used, but all have to be enabled. The real
                flow of a specific frame depends on the PCD configuration and the
                frame headers and payload.
                Note: the first engine and the first engine after the parser (if
                exists) should be in order, the order is important as it will
                define the flow of the port. However, as for the rest engines
                (the ones that follows), the order is not important anymore as
                it is defined by the PCD graph itself.
*//***************************************************************************/
typedef enum e_FmPortPcdSupport {
      e_FM_PORT_PCD_SUPPORT_NONE = 0                /**< BMI to BMI, PCD is not used */
    , e_FM_PORT_PCD_SUPPORT_PRS_ONLY                /**< Use only Parser */
    , e_FM_PORT_PCD_SUPPORT_PLCR_ONLY               /**< Use only Policer */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_PLCR            /**< Use Parser and Policer */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG              /**< Use Parser and Keygen */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG_AND_CC       /**< Use Parser, Keygen and Coarse Classification */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG_AND_CC_AND_PLCR
                                                    /**< Use all PCD engines */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG_AND_PLCR     /**< Use Parser, Keygen and Policer */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_CC              /**< Use Parser and Coarse Classification */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_CC_AND_PLCR     /**< Use Parser and Coarse Classification and Policer */
#ifdef FM_CAPWAP_SUPPORT
    , e_FM_PORT_PCD_SUPPORT_CC_ONLY                 /**< Use only Coarse Classification */
    , e_FM_PORT_PCD_SUPPORT_CC_AND_KG               /**< Use Coarse Classification,and Keygen */
    , e_FM_PORT_PCD_SUPPORT_CC_AND_KG_AND_PLCR      /**< Use Coarse Classification, Keygen and Policer */
#endif /* FM_CAPWAP_SUPPORT */
} e_FmPortPcdSupport;

/**************************************************************************//**
 @Description   Port interrupts
*//***************************************************************************/
typedef enum e_FmPortExceptions {
    e_FM_PORT_EXCEPTION_IM_BUSY                 /**< Independent-Mode Rx-BUSY */
} e_FmPortExceptions;


/**************************************************************************//**
 @Collection    General FM Port defines
*//***************************************************************************/
#define FM_PORT_PRS_RESULT_NUM_OF_WORDS     8   /**< Number of 4 bytes words in parser result */
/* @} */

/**************************************************************************//**
 @Collection   FM Frame error
*//***************************************************************************/
typedef uint32_t    fmPortFrameErrSelect_t;                         /**< typedef for defining Frame Descriptor errors */

#define FM_PORT_FRM_ERR_UNSUPPORTED_FORMAT      FM_FD_ERR_UNSUPPORTED_FORMAT    /**< Not for Rx-Port! Unsupported Format */
#define FM_PORT_FRM_ERR_LENGTH                  FM_FD_ERR_LENGTH                /**< Not for Rx-Port! Length Error */
#define FM_PORT_FRM_ERR_DMA                     FM_FD_ERR_DMA                   /**< DMA Data error */
#ifdef FM_DISABLE_SEC_ERRORS
#define FM_PORT_FRM_ERR_NON_FM                  FM_FD_RX_STATUS_ERR_NON_FM      /*< non Frame-Manager error; probably come from SEC that
                                                                                    was chained to FM */
#endif /* FM_DISABLE_SEC_ERRORS */

#define FM_PORT_FRM_ERR_IPRE                    (FM_FD_ERR_IPR & ~FM_FD_IPR)        /**< IPR error */
#define FM_PORT_FRM_ERR_IPR_NCSP                (FM_FD_ERR_IPR_NCSP & ~FM_FD_IPR)   /**< IPR non-consistent-sp */
#define FM_PORT_FRM_ERR_IPFE                    FM_FD_ERR_IPF                       /**< IPF error */

#ifdef FM_CAPWAP_SUPPORT
#define FM_PORT_FRM_ERR_CRE                     FM_FD_ERR_CRE
#define FM_PORT_FRM_ERR_CHE                     FM_FD_ERR_CHE
#endif /* FM_CAPWAP_SUPPORT */

#define FM_PORT_FRM_ERR_PHYSICAL                FM_FD_ERR_PHYSICAL              /**< Rx FIFO overflow, FCS error, code error, running disparity
                                                                                     error (SGMII and TBI modes), FIFO parity error. PHY
                                                                                     Sequence error, PHY error control character detected. */
#define FM_PORT_FRM_ERR_SIZE                    FM_FD_ERR_SIZE                  /**< Frame too long OR Frame size exceeds max_length_frame  */
#define FM_PORT_FRM_ERR_CLS_DISCARD             FM_FD_ERR_CLS_DISCARD           /**< classification discard */
#define FM_PORT_FRM_ERR_EXTRACTION              FM_FD_ERR_EXTRACTION            /**< Extract Out of Frame */
#define FM_PORT_FRM_ERR_NO_SCHEME               FM_FD_ERR_NO_SCHEME             /**< No Scheme Selected */
#define FM_PORT_FRM_ERR_KEYSIZE_OVERFLOW        FM_FD_ERR_KEYSIZE_OVERFLOW      /**< Keysize Overflow */
#define FM_PORT_FRM_ERR_COLOR_RED               FM_FD_ERR_COLOR_RED             /**< Frame color is red */
#define FM_PORT_FRM_ERR_COLOR_YELLOW            FM_FD_ERR_COLOR_YELLOW          /**< Frame color is yellow */
#define FM_PORT_FRM_ERR_ILL_PLCR                FM_FD_ERR_ILL_PLCR              /**< Illegal Policer Profile selected */
#define FM_PORT_FRM_ERR_PLCR_FRAME_LEN          FM_FD_ERR_PLCR_FRAME_LEN        /**< Policer frame length error */
#define FM_PORT_FRM_ERR_PRS_TIMEOUT             FM_FD_ERR_PRS_TIMEOUT           /**< Parser Time out Exceed */
#define FM_PORT_FRM_ERR_PRS_ILL_INSTRUCT        FM_FD_ERR_PRS_ILL_INSTRUCT      /**< Invalid Soft Parser instruction */
#define FM_PORT_FRM_ERR_PRS_HDR_ERR             FM_FD_ERR_PRS_HDR_ERR           /**< Header error was identified during parsing */
#define FM_PORT_FRM_ERR_BLOCK_LIMIT_EXCEEDED    FM_FD_ERR_BLOCK_LIMIT_EXCEEDED  /**< Frame parsed beyind 256 first bytes */
#define FM_PORT_FRM_ERR_PROCESS_TIMEOUT         0x00000001       /**< FPM Frame Processing Timeout Exceeded */
/* @} */




/**************************************************************************//**
 @Description   structure representing FM initialization parameters
*//***************************************************************************/
typedef struct t_FmPortParams {
    t_Handle                    h_Fm;               /**< A handle to the FM object this port belongs to */

    e_FmPortType                portType;           /**< Port type */
    uint8_t                     portId;             /**< Port Id - relative to type */
} t_FmPortParams;


t_Handle FM_PORT_Open(t_FmPortParams *p_FmPortParams);
void     FM_PORT_Close(t_Handle h_FmPort);

/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_advanced_init_grp    FM Port Advanced Configuration Unit

 @Description   Configuration functions used to change default values.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   A structure for defining Dual Tx rate limiting scale
*//***************************************************************************/
typedef enum e_FmPortDualRateLimiterScaleDown {
    e_FM_PORT_DUAL_RATE_LIMITER_NONE = 0,           /**< Use only single rate limiter  */
    e_FM_PORT_DUAL_RATE_LIMITER_SCALE_DOWN_BY_2,    /**< Divide high rate limiter by 2 */
    e_FM_PORT_DUAL_RATE_LIMITER_SCALE_DOWN_BY_4,    /**< Divide high rate limiter by 4 */
    e_FM_PORT_DUAL_RATE_LIMITER_SCALE_DOWN_BY_8     /**< Divide high rate limiter by 8 */
} e_FmPortDualRateLimiterScaleDown;

/**************************************************************************//**
 @Description   A structure for defining Tx rate limiting
*//***************************************************************************/
typedef struct t_FmPortRateLimit {
    uint16_t                            maxBurstSize;           /**< in kBytes for Tx ports, in frames
                                                                     for offline parsing ports. (note that
                                                                     for early chips burst size is
                                                                     rounded up to a multiply of 1000 frames).*/
    uint32_t                            rateLimit;              /**< in Kb/sec for Tx ports, in frame/sec for
                                                                     offline parsing ports. Rate limit refers to
                                                                     data rate (rather than line rate). */
    e_FmPortDualRateLimiterScaleDown    rateLimitDivider;       /**< For offline parsing ports only. Not-valid
                                                                     for some earlier chip revisions */
} t_FmPortRateLimit;

/**************************************************************************//**
 @Description   Structure for Port id parameters.
                Fields commented 'IN' are passed by the port module to be used
                by the FM module.
                Fields commented 'OUT' will be filled by FM before returning to port.
*//***************************************************************************/
typedef struct t_FmPortCongestionGrps {
    uint16_t    numOfCongestionGrpsToConsider;          /**< The number of required congestion groups
                                                             to define the size of the following array */
    uint8_t     congestionGrpsToConsider[FM_PORT_NUM_OF_CONGESTION_GRPS];
                                                        /**< An array of CG indexes;
                                                             Note that the size of the array should be
                                                             'numOfCongestionGrpsToConsider'. */
#if (DPAA_VERSION >= 11)
    bool        pfcPrioritiesEn[FM_PORT_NUM_OF_CONGESTION_GRPS][FM_MAX_NUM_OF_PFC_PRIORITIES];
                                                        /**< a matrix that represents the map between the CG ids
                                                             defined in 'congestionGrpsToConsider' to the priorties
                                                             mapping array. */
#endif /* (DPAA_VERSION >= 11) */
} t_FmPortCongestionGrps;


/**************************************************************************//**
 @Function      FM_PORT_Disable

 @Description   Gracefully disable an FM port. The port will not start new tasks after all
                tasks associated with the port are terminated.

 @Param[in]     h_FmPort    A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
                This is a blocking routine, it returns after port is
                gracefully stopped, i.e. the port will not except new frames,
                but it will finish all frames or tasks which were already began
*//***************************************************************************/
t_Error FM_PORT_Disable(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_Enable

 @Description   A runtime routine provided to allow disable/enable of port.

 @Param[in]     h_FmPort    A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_Enable(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_SetRateLimit

 @Description   Calling this routine enables rate limit algorithm.
                By default, this functionality is disabled.
                Note that rate-limit mechanism uses the FM time stamp.
                The selected rate limit specified here would be
                rounded DOWN to the nearest 16M.

                May be used for Tx and offline parsing ports only

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_RateLimit     A structure of rate limit parameters

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetRateLimit(t_Handle h_FmPort, t_FmPortRateLimit *p_RateLimit);

/**************************************************************************//**
 @Function      FM_PORT_DeleteRateLimit

 @Description   Calling this routine disables and clears rate limit
                initialization.

                May be used for Tx and offline parsing ports only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_DeleteRateLimit(t_Handle h_FmPort);


/**************************************************************************//**
 @Function      FM_PORT_AddCongestionGrps

 @Description   This routine effects the corresponding Tx port.
                It should be called in order to enable pause
                frame transmission in case of congestion in one or more
                of the congestion groups relevant to this port.
                Each call to this routine may add one or more congestion
                groups to be considered relevant to this port.

                May be used for Rx, or RX+OP ports only (depending on chip)
                (Not implemented yet in fm-lib!)

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     p_CongestionGrps    A pointer to an array of congestion groups
                                    id's to consider.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_AddCongestionGrps(t_Handle h_FmPort, t_FmPortCongestionGrps *p_CongestionGrps);

/**************************************************************************//**
 @Function      FM_PORT_RemoveCongestionGrps

 @Description   This routine effects the corresponding Tx port. It should be
                called when congestion groups were
                defined for this port and are no longer relevant, or pause
                frames transmitting is not required on their behalf.
                Each call to this routine may remove one or more congestion
                groups to be considered relevant to this port.

                May be used for Rx, or RX+OP ports only (depending on chip)
                (Not implemented yet in fm-lib!)

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     p_CongestionGrps    A pointer to an array of congestion groups
                                    id's to consider.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_RemoveCongestionGrps(t_Handle h_FmPort, t_FmPortCongestionGrps *p_CongestionGrps);

/**************************************************************************//**
 @Function      FM_PORT_SetRxL4ChecksumVerify

 @Description   This routine is relevant for Rx ports (1G and 10G). The routine
                set/clear the L3/L4 checksum verification (on RX side).
                Note that this takes effect only if hw-parser is enabled!
                (Not implemented yet in fm-lib!)

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     l4Checksum      boolean indicates whether to do L3/L4 checksum
                                on frames or not.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetRxL4ChecksumVerify(t_Handle h_FmPort, bool l4Checksum);

/**************************************************************************//**
 @Function      FM_PORT_SetErrorsRoute

 @Description   Errors selected for this routine will cause a frame with that error
                to be enqueued to error queue.
                Errors not selected for this routine will cause a frame with that error
                to be enqueued to the one of the other port queues.
                By default all errors are defined to be enqueued to error queue.
                Errors that were configured to be discarded (at initialization)
                may not be selected here.

                May be used for Rx and offline parsing ports only

 @Param[in]     h_FmPort    A handle to a FM Port module.
 @Param[in]     errs        A list of errors to enqueue to error queue

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Config() and before FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetErrorsRoute(t_Handle h_FmPort, fmPortFrameErrSelect_t errs);


/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_pcd_runtime_control_grp FM Port PCD Runtime Control Unit

 @Description   FM Port PCD Runtime control unit API functions, definitions and enums.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   A structure defining the KG scheme after the parser.
                This is relevant only to change scheme selection mode - from
                direct to indirect and vice versa, or when the scheme is selected directly,
                to select the scheme id.

*//***************************************************************************/
typedef struct t_FmPcdKgSchemeSelect {
    bool        direct;                 /**< TRUE to use 'h_Scheme' directly, FALSE to use LCV. */
    t_Handle    h_DirectScheme;         /**< Scheme handle, selects the scheme after parser;
                                             Relevant only when 'direct' is TRUE. */
} t_FmPcdKgSchemeSelect;

/**************************************************************************//**
 @Description   A structure of scheme parameters
*//***************************************************************************/
typedef struct t_FmPcdPortSchemesParams {
    uint8_t     numOfSchemes;                           /**< Number of schemes for port to be bound to. */
    t_Handle    h_Schemes[FM_PCD_KG_NUM_OF_SCHEMES];    /**< Array of 'numOfSchemes' schemes for the
                                                             port to be bound to */
} t_FmPcdPortSchemesParams;

/**************************************************************************//**
 @Description   Union for defining port protocol parameters for parser
*//***************************************************************************/
typedef union u_FmPcdHdrPrsOpts {
    /* MPLS */
    struct {
        bool            labelInterpretationEnable;  /**< When this bit is set, the last MPLS label will be
                                                         interpreted as described in HW spec table. When the bit
                                                         is cleared, the parser will advance to MPLS next parse */
        e_NetHeaderType nextParse;                  /**< must be equal or higher than IPv4 */
    } mplsPrsOptions;
    /* VLAN */
    struct {
        uint16_t        tagProtocolId1;             /**< User defined Tag Protocol Identifier, to be recognized
                                                         on VLAN TAG on top of 0x8100 and 0x88A8 */
        uint16_t        tagProtocolId2;             /**< User defined Tag Protocol Identifier, to be recognized
                                                         on VLAN TAG on top of 0x8100 and 0x88A8 */
    } vlanPrsOptions;
    /* PPP */
    struct{
        bool            enableMTUCheck;             /**< Check validity of MTU according to RFC2516 */
    } pppoePrsOptions;

    /* IPV6 */
    struct{
        bool            routingHdrEnable;          /**< TRUE to enable routing header, otherwise ignore */
    } ipv6PrsOptions;

    /* UDP */
    struct{
        bool            padIgnoreChecksum;          /**< TRUE to ignore pad in checksum */
    } udpPrsOptions;

    /* TCP */
    struct {
        bool            padIgnoreChecksum;          /**< TRUE to ignore pad in checksum */
    } tcpPrsOptions;
} u_FmPcdHdrPrsOpts;

/**************************************************************************//**
 @Description   A structure for defining each header for the parser
*//***************************************************************************/
typedef struct t_FmPcdPrsAdditionalHdrParams {
    e_NetHeaderType         hdr;            /**< Selected header */
    bool                    errDisable;     /**< TRUE to disable error indication */
    bool                    swPrsEnable;    /**< Enable jump to SW parser when this
                                                 header is recognized by the HW parser. */
    uint8_t                 indexPerHdr;    /**< Normally 0, if more than one sw parser
                                                 attachments exists for the same header,
                                                 (in the main sw parser code) use this
                                                 index to distinguish between them. */
    bool                    usePrsOpts;     /**< TRUE to use parser options. */
    u_FmPcdHdrPrsOpts       prsOpts;        /**< A union according to header type,
                                                 defining the parser options selected.*/
} t_FmPcdPrsAdditionalHdrParams;

/**************************************************************************//**
 @Description   struct for defining port PCD parameters
*//***************************************************************************/
typedef struct t_FmPortPcdPrsParams {
    uint8_t                         prsResultPrivateInfo;           /**< The private info provides a method of inserting
                                                                         port information into the parser result. This information
                                                                         may be extracted by Keygen and be used for frames
                                                                         distribution when a per-port distinction is required,
                                                                         it may also be used as a port logical id for analyzing
                                                                         incoming frames. */
    uint8_t                         parsingOffset;                  /**< Number of bytes from beginning of packet to start parsing */
    e_NetHeaderType                 firstPrsHdr;                    /**< The type of the first header expected at 'parsingOffset' */
    bool                            includeInPrsStatistics;         /**< TRUE to include this port in the parser statistics */
    uint8_t                         numOfHdrsWithAdditionalParams;  /**< Normally 0, some headers may get
                                                                         special parameters */
    t_FmPcdPrsAdditionalHdrParams   additionalParams[FM_PCD_PRS_NUM_OF_HDRS];
                                                                    /**< 'numOfHdrsWithAdditionalParams'  structures
                                                                         of additional parameters
                                                                         for each header that requires them */
    bool                            setVlanTpid1;                   /**< TRUE to configure user selection of Ethertype to
                                                                         indicate a VLAN tag (in addition to the TPID values
                                                                         0x8100 and 0x88A8). */
    uint16_t                        vlanTpid1;                      /**< extra tag to use if setVlanTpid1=TRUE. */
    bool                            setVlanTpid2;                   /**< TRUE to configure user selection of Ethertype to
                                                                         indicate a VLAN tag (in addition to the TPID values
                                                                         0x8100 and 0x88A8). */
    uint16_t                        vlanTpid2;                      /**< extra tag to use if setVlanTpid1=TRUE. */
} t_FmPortPcdPrsParams;

/**************************************************************************//**
 @Description   struct for defining coarse alassification parameters
*//***************************************************************************/
typedef struct t_FmPortPcdCcParams {
    t_Handle            h_CcTree;                       /**< A handle to a CC tree */
} t_FmPortPcdCcParams;

/**************************************************************************//**
 @Description   struct for defining keygen parameters
*//***************************************************************************/
typedef struct t_FmPortPcdKgParams {
    uint8_t             numOfSchemes;                   /**< Number of schemes for port to be bound to. */
    t_Handle            h_Schemes[FM_PCD_KG_NUM_OF_SCHEMES];
                                                        /**< Array of 'numOfSchemes' schemes handles for the
                                                             port to be bound to */
    bool                directScheme;                   /**< TRUE for going from parser to a specific scheme,
                                                             regardless of parser result */
    t_Handle            h_DirectScheme;                 /**< relevant only if direct == TRUE, Scheme handle,
                                                             as returned by FM_PCD_KgSetScheme */
} t_FmPortPcdKgParams;

/**************************************************************************//**
 @Description   struct for defining policer parameters
*//***************************************************************************/
typedef struct t_FmPortPcdPlcrParams {
    t_Handle                h_Profile;          /**< Selected profile handle; Relevant for one of
                                                     following cases:
                                                     e_FM_PORT_PCD_SUPPORT_PLCR_ONLY or
                                                     e_FM_PORT_PCD_SUPPORT_PRS_AND_PLCR were selected,
                                                     or if any flow uses a KG scheme were policer
                                                     profile is not generated
                                                     (bypassPlcrProfileGeneration selected) */
} t_FmPortPcdPlcrParams;

/**************************************************************************//**
 @Description   struct for defining port PCD parameters
*//***************************************************************************/
typedef struct t_FmPortPcdParams {
    e_FmPortPcdSupport      pcdSupport;         /**< Relevant for Rx and offline ports only.
                                                     Describes the active PCD engines for this port. */
    t_Handle                h_NetEnv;           /**< HL Unused in PLCR only mode */
    t_FmPortPcdPrsParams    *p_PrsParams;       /**< Parser parameters for this port */
    t_FmPortPcdCcParams     *p_CcParams;        /**< Coarse classification parameters for this port */
    t_FmPortPcdKgParams     *p_KgParams;        /**< Keygen parameters for this port */
    t_FmPortPcdPlcrParams   *p_PlcrParams;      /**< Policer parameters for this port */
    t_Handle                h_IpReassemblyManip;/**< IP Reassembly manipulation */
} t_FmPortPcdParams;

/**************************************************************************//**
 @Description   A structure for defining the Parser starting point
*//***************************************************************************/
typedef struct t_FmPcdPrsStart {
    uint8_t             parsingOffset;  /**< Number of bytes from beginning of packet to
                                             start parsing */
    e_NetHeaderType     firstPrsHdr;    /**< The type of the first header axpected at
                                             'parsingOffset' */
} t_FmPcdPrsStart;

#if (DPAA_VERSION >= 11)
/**************************************************************************//**
 @Description   struct for defining external buffer margins
*//***************************************************************************/
typedef struct t_FmPortVSPAllocParams {
    uint8_t     numOfProfiles;          /**< Number of Virtual Storage Profiles */
    uint8_t     dfltRelativeId;         /**< The default Virtual-Storage-Profile-id dedicated to Rx/OP port
                                             The same default Virtual-Storage-Profile-id will be for coupled Tx port
                                             if relevant function called for Rx port */
    t_Handle    h_FmTxPort;             /**< Handle to coupled Tx Port; not relevant for OP port. */
} t_FmPortVSPAllocParams;
#endif /* (DPAA_VERSION >= 11) */


/**************************************************************************//**
 @Function      FM_PORT_SetPCD

 @Description   Calling this routine defines the port's PCD configuration.
                It changes it from its default configuration which is PCD
                disabled (BMI to BMI) and configures it according to the passed
                parameters.

                May be used for Rx and offline parsing ports only

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_FmPortPcd     A Structure of parameters defining the port's PCD
                                configuration.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetPCD(t_Handle h_FmPort, t_FmPortPcdParams *p_FmPortPcd);

/**************************************************************************//**
 @Function      FM_PORT_DeletePCD

 @Description   Calling this routine releases the port's PCD configuration.
                The port returns to its default configuration which is PCD
                disabled (BMI to BMI) and all PCD configuration is removed.

                May be used for Rx and offline parsing ports which are
                in PCD mode  only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_DeletePCD(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_AttachPCD

 @Description   This routine may be called after FM_PORT_DetachPCD was called,
                to return to the originally configured PCD support flow.
                The couple of routines are used to allow PCD configuration changes
                that demand that PCD will not be used while changes take place.

                May be used for Rx and offline parsing ports which are
                in PCD mode only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_AttachPCD(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_DetachPCD

 @Description   Calling this routine detaches the port from its PCD functionality.
                The port returns to its default flow which is BMI to BMI.

                May be used for Rx and offline parsing ports which are
                in PCD mode only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_AttachPCD().
*//***************************************************************************/
t_Error FM_PORT_DetachPCD(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_PcdPlcrAllocProfiles

 @Description   This routine may be called only for ports that use the Policer in
                order to allocate private policer profiles.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     numOfProfiles       The number of required policer profiles

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PCD_Init(),
                and before FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdPlcrAllocProfiles(t_Handle h_FmPort, uint16_t numOfProfiles);

/**************************************************************************//**
 @Function      FM_PORT_PcdPlcrFreeProfiles

 @Description   This routine should be called for freeing private policer profiles.

 @Param[in]     h_FmPort            A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PCD_Init(),
                and before FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdPlcrFreeProfiles(t_Handle h_FmPort);

#if (DPAA_VERSION >= 11)
/**************************************************************************//**
 @Function      FM_PORT_VSPAlloc

 @Description   This routine allocated VSPs per port and forces the port to work
                in VSP mode. Note that the port is initialized by default with the
                physical-storage-profile only.

 @Param[in]     h_FmPort    A handle to a FM Port module.
 @Param[in]     p_Params    A structure of parameters for allocation VSP's per port

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init(), and before FM_PORT_SetPCD()
                and also before FM_PORT_Enable() (i.e. the port should be disabled).
*//***************************************************************************/
t_Error FM_PORT_VSPAlloc(t_Handle h_FmPort, t_FmPortVSPAllocParams *p_Params);
#endif /* (DPAA_VERSION >= 11) */

/**************************************************************************//**
 @Function      FM_PORT_PcdKgModifyInitialScheme

 @Description   This routine may be called only for ports that use the keygen in
                order to change the initial scheme frame should be routed to.
                The change may be of a scheme id (in case of direct mode),
                from direct to indirect, or from indirect to direct - specifying the scheme id.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     p_FmPcdKgScheme     A structure of parameters for defining whether
                                    a scheme is direct/indirect, and if direct - scheme id.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdKgModifyInitialScheme (t_Handle h_FmPort, t_FmPcdKgSchemeSelect *p_FmPcdKgScheme);

/**************************************************************************//**
 @Function      FM_PORT_PcdPlcrModifyInitialProfile

 @Description   This routine may be called for ports with flows
                e_FM_PORT_PCD_SUPPORT_PLCR_ONLY or e_FM_PORT_PCD_SUPPORT_PRS_AND_PLCR
                only, to change the initial Policer profile frame should be
                routed to. The change may be of a profile and/or absolute/direct
                mode selection.

 @Param[in]     h_FmPort                A handle to a FM Port module.
 @Param[in]     h_Profile               Policer profile handle

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdPlcrModifyInitialProfile (t_Handle h_FmPort, t_Handle h_Profile);

/**************************************************************************//**
 @Function      FM_PORT_PcdCcModifyTree

 @Description   This routine may be called for ports that use coarse classification tree
                if the user wishes to replace the tree. The routine may not be called while port
                receives packets using the PCD functionalities, therefor port must be first detached
                from the PCD, only than the routine may be called, and than port be attached to PCD again.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     h_CcTree            A CC tree that was already built. The tree id as returned from
                                    the BuildTree routine.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init(), FM_PORT_SetPCD() and FM_PORT_DetachPCD()
*//***************************************************************************/
t_Error FM_PORT_PcdCcModifyTree (t_Handle h_FmPort, t_Handle h_CcTree);

/**************************************************************************//**
 @Function      FM_PORT_PcdKgBindSchemes

 @Description   These routines may be called for adding more schemes for the
                port to be bound to. The selected schemes are not added,
                just this specific port starts using them.

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_PortScheme    A structure defining the list of schemes to be added.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdKgBindSchemes (t_Handle h_FmPort, t_FmPcdPortSchemesParams *p_PortScheme);

/**************************************************************************//**
 @Function      FM_PORT_PcdKgUnbindSchemes

 @Description   These routines may be called for adding more schemes for the
                port to be bound to. The selected schemes are not removed or invalidated,
                just this specific port stops using them.

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_PortScheme    A structure defining the list of schemes to be added.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdKgUnbindSchemes (t_Handle h_FmPort, t_FmPcdPortSchemesParams *p_PortScheme);

/**************************************************************************//**
 @Function      FM_PORT_PcdPrsModifyStartOffset

 @Description   Runtime change of the parser start offset within the header.
                The routine may not be called while port
                receives packets using the PCD functionalities, therefore port must be first detached
                from the PCD, only than the routine may be called, and than port be attached to PCD again.
 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_FmPcdPrsStart A structure of parameters for defining the
                                start point for the parser.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init(), FM_PORT_SetPCD() and FM_PORT_DetatchPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdPrsModifyStartOffset (t_Handle h_FmPort, t_FmPcdPrsStart *p_FmPcdPrsStart);

#if (DPAA_VERSION >= 11)
#ifdef FM_EXP_FEATURES
/*              (Not implemented yet in fm-lib!) */
t_Error FM_PORT_GetIPv4OptionsCount(t_Handle h_FmPort, uint32_t *p_Ipv4OptionsCount);
#endif /* FM_EXP_FEATURES */
#endif /* (DPAA_VERSION >= 11) */

/** @} */ /* end of lnx_usr_FM_PORT_pcd_runtime_control_grp group */


/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_runtime_data_grp FM Port Runtime Data-path Unit

 @Description   FM Port Runtime data unit API functions, definitions and enums.
                This API is valid only if working in Independent-Mode.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Function      FM_PORT_AllocPCDFqids

 @Description   Allocates a sequence of consecutive FQIDs for this port's use.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     num_Fqids           # of FQIDs to allocate
 @Param[in]     alignment           First FQID may need to be aligned
                                    to this value (watch out, as passing in
                                    a zero here can spell "trouble"!)

 @Return        The first of the allocated consecutive FQIDs;
                0 on error (0 is an invalid FQID, too)

 @Cautions      Try not to pass in zero for alignment!
*//***************************************************************************/
uint32_t FM_PORT_AllocPCDFqids (t_Handle h_FmPort, uint32_t numFqids, uint8_t alignment);

/**************************************************************************//**
 @Function      FM_PORT_FreePCDFqids

 @Description   Frees a previously-allocated range of consecutive FQIDs
                for this port's use.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     base_fqid           Base FQID of previously-allocated range.

 @Return        Error code, or 0 on success.
*//***************************************************************************/
t_Error FM_PORT_FreePCDFqids (t_Handle h_FmPort, uint32_t base_fqid);

/** @} */ /* end of lnx_usr_FM_PORT_runtime_data_grp group */
/** @} */ /* end of lnx_usr_FM_PORT_grp group */
/** @} */ /* end of lnx_usr_FM_grp group */

#endif /* __FM_PORT_EXT */
