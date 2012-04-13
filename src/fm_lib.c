/* =====================================================================
 *
 *  Copyright 2009-2012, Freescale Semiconductor, Inc., All Rights Reserved.
 *
 *  This file contains copyrighted material. Use of this file is restricted
 *  by the provisions of a Freescale Software License Agreement, which has
 *  either accompanied the delivery of this software in shrink wrap
 *  form or been expressly executed between the parties.
 *
 * ===================================================================*/
/******************************************************************************
 @File          fm_lib.c

 @Description   Frame Manager Linux User-Space library implementation.
*//***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "fm_ext.h"
#include "fm_pcd_ext.h"
#include "fm_port_ext.h"

#include "fm_ioctls.h"
#include "fm_pcd_ioctls.h"
#include "fm_port_ioctls.h"

#define __ERR_MODULE__      MODULE_FM


/*******************************************************************************
*  FM FUNCTIONS                                                                *
*******************************************************************************/

t_Handle FM_Open(uint8_t id)
{
    t_Device    *p_Dev;
    int         fd;
    char        devName[20];

    p_Dev = (t_Device*) malloc(sizeof(t_Device));
    if (!p_Dev)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM device!!"));
        return NULL;
    }

    memset(devName, 0, 20);
    sprintf(devName, "%s%s%d", "/dev/", DEV_FM_NAME, id);
    fd = open(devName, O_RDWR);
    if (fd < 0)
    {
       free(p_Dev);
       REPORT_ERROR(MAJOR, E_OPEN_FAILED, ("Could not open FM. Ret code=%d, errno=%d. Aborting!!!",
               fd,
               errno));
       return NULL;
    }

    p_Dev->id = id;
    p_Dev->fd = fd;
    return (t_Handle)p_Dev;
}

void FM_Close(t_Handle h_Fm)
{
    t_Device    *p_Dev = (t_Device*) h_Fm;

    SANITY_CHECK_RETURN(p_Dev, E_INVALID_HANDLE);

    close(p_Dev->fd);
    free(p_Dev);
}

t_Error FM_SetPortsBandwidth(t_Handle h_Fm, t_FmPortsBandwidthParams *p_PortsBandwidth)
{
    t_Device    *p_Dev = (t_Device*) h_Fm;

    ASSERT_COND(sizeof(t_FmPortsBandwidthParams) == sizeof(ioc_fm_port_bandwidth_params));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_IOC_SET_PORTS_BANDWIDTH, p_PortsBandwidth))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error  FM_GetRevision(t_Handle h_Fm, t_FmRevisionInfo *p_FmRevisionInfo)
{
    t_Device    *p_Dev = (t_Device*) h_Fm;

    ASSERT_COND(sizeof(t_FmRevisionInfo) == sizeof(ioc_fm_revision_info_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_IOC_GET_REVISION, p_FmRevisionInfo))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

uint32_t FM_GetCounter(t_Handle h_Fm, e_FmCounters counter)
{
    t_Device                    *p_Dev = (t_Device*) h_Fm;
    ioc_fm_counters_params_t    params;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, 0);

    params.cnt = (ioc_fm_counters) counter;

    if (ioctl(p_Dev->fd, FM_IOC_GET_COUNTER, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return params.val;
}

t_Error  FM_SetCounter(t_Handle h_Fm, e_FmCounters counter, uint32_t val)
{
    t_Device                    *p_Dev = (t_Device*) h_Fm;
    ioc_fm_counters_params_t    params;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, 0);

    params.cnt = (ioc_fm_counters) counter;
    params.val = val;

    if (ioctl(p_Dev->fd, FM_IOC_SET_COUNTER, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_ForceIntr(t_Handle h_Fm, e_FmExceptions exception)
{
    t_Device    *p_Dev = (t_Device*) h_Fm;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_IOC_FORCE_INTR, (ioc_fm_exceptions) exception))
        REPORT_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}
/* TODO:FMD16 FM Control Monito export functions */
/* TODO:FMD16 FM_GetSpecialOperationCoding */
/********************************************************************************************/
/*  FM_PCD FUNCTIONS                                                                        */
/********************************************************************************************/

t_Handle FM_PCD_Open(t_FmPcdParams *p_FmPcdParams)
{
    t_Device    *p_Dev;
    int         fd;
    char        devName[20];

    p_Dev = (t_Device*) malloc(sizeof(t_Device));
    if (!p_Dev)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM PCD device!!"));
        return NULL;
    }

    memset(devName, 0, 20);
    sprintf(devName, "%s%s%d-pcd", "/dev/", DEV_FM_NAME, ((t_Device*) p_FmPcdParams->h_Fm)->id);
    fd = open(devName, O_RDWR);
    if (fd < 0)
    {
       free(p_Dev);
       REPORT_ERROR(MAJOR, E_OPEN_FAILED, ("Could not open FM. Ret code=%d, errno=%d. Aborting!!!",
               fd,
               errno));
       return NULL;
    }

    p_Dev->id = ((t_Device*) p_FmPcdParams->h_Fm)->id;
    p_Dev->fd = fd;
    return (t_Handle) p_Dev;
}

void FM_PCD_Close(t_Handle h_FmPcd)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;

    SANITY_CHECK_RETURN(p_Dev, E_INVALID_HANDLE);

    close(p_Dev->fd);
    free(p_Dev);
}

t_Error FM_PCD_Enable(t_Handle h_FmPcd)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PCD_IOC_ENABLE))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_Disable(t_Handle h_FmPcd)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PCD_IOC_DISABLE))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_PrsLoadSw(t_Handle h_FmPcd, t_FmPcdPrsSwParams *p_SwPrs)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;

    ASSERT_COND(sizeof(t_FmPcdPrsSwParams) == sizeof(ioc_fm_pcd_prs_sw_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PCD_IOC_PRS_LOAD_SW, p_SwPrs))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_KgSetDfltValue(t_Handle h_FmPcd, uint8_t valueId, uint32_t value)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_kg_dflt_value_params_t params;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.value = value;
    params.valueId = valueId;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_KG_SET_DFLT_VALUE, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_KgSetAdditionalDataAfterParsing(t_Handle h_FmPcd, uint8_t payloadOffset)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PCD_IOC_KG_SET_ADDITIONAL_DATA_AFTER_PARSING, &payloadOffset))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_SetException(t_Handle h_FmPcd, e_FmPcdExceptions exception, bool enable)
{
    t_Device                        *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_exception_params_t   params;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.exception = exception;
    params.enable = enable;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_SET_EXCEPTION, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

uint32_t FM_PCD_GetCounter(t_Handle h_FmPcd, e_FmPcdCounters counter)
{
    t_Device                        *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_counters_params_t    params;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.cnt = (ioc_fm_pcd_counters) counter;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_GET_COUNTER, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return params.val;
}

t_Error FM_PCD_SetCounter(t_Handle h_FmPcd, e_FmPcdCounters counter, uint32_t value)
{
    t_Device                        *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_counters_params_t    params;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.cnt = (ioc_fm_pcd_counters) counter;
    params.val = value;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_SET_COUNTER, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_ForceIntr (t_Handle h_FmPcd, e_FmPcdExceptions exception)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    int         intCast = (int) exception;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PCD_IOC_FORCE_INTR, &intCast))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Handle FM_PCD_SetNetEnvCharacteristics(t_Handle h_FmPcd, t_FmPcdNetEnvParams *p_NetEnvParams)
{
    t_Device                    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_net_env_params_t params;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, NULL);

    memcpy(&params, p_NetEnvParams, sizeof(t_FmPcdNetEnvParams));
    if (ioctl(p_Dev->fd, FM_PCD_IOC_SET_NET_ENV_CHARACTERISTICS, &params))
    {
        REPORT_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);
        return NULL;
    }

    return (t_Handle) params.id;
}

t_Error FM_PCD_DeleteNetEnvCharacteristics(t_Handle h_FmPcd, t_Handle h_NetEnv)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_NetEnv;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_DELETE_NET_ENV_CHARACTERISTICS, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Handle FM_PCD_KgSetScheme (t_Handle h_FmPcd, t_FmPcdKgSchemeParams *p_Scheme)
{
    t_Device                      *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_kg_scheme_params_t params;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, NULL);

    memcpy(&params, p_Scheme, sizeof(t_FmPcdKgSchemeParams));
    if (ioctl(p_Dev->fd, FM_PCD_IOC_KG_SET_SCHEME, &params))
    {
        REPORT_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);
        return NULL;
    }

    return (t_Handle) params.id;
}

t_Error FM_PCD_KgDeleteScheme(t_Handle h_FmPcd, t_Handle h_Scheme)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_Scheme;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_KG_DEL_SCHEME, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Handle FM_PCD_CcBuildTree (t_Handle h_FmPcd, t_FmPcdCcTreeParams *p_PcdTreeParam)
{
    t_Device                    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_tree_params_t params;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, NULL);

    memcpy(&params, p_PcdTreeParam, sizeof(t_FmPcdCcTreeParams));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_BUILD_TREE, &params))
    {
        REPORT_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);
        return NULL;
    }

    return (t_Handle) params.id;
}

t_Error FM_PCD_CcDeleteTree(t_Handle h_FmPcd, t_Handle h_CcTree)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_CcTree;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_DELETE_TREE, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Handle FM_PCD_CcSetNode(t_Handle h_FmPcd, t_FmPcdCcNodeParams *p_CcNodeParam)
{
    t_Device                    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_node_params_t params;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, NULL);

    memcpy(&params, p_CcNodeParam, sizeof(t_FmPcdCcNodeParams));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_SET_NODE, &params))
    {
        REPORT_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);
        return NULL;
    }

    return (t_Handle) params.id;
}

t_Error FM_PCD_CcDeleteNode(t_Handle h_FmPcd, t_Handle h_CcNode)
{
    t_Device    *p_Dev = (t_Device *)h_FmPcd;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_CcNode;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_DELETE_NODE, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_CcTreeModifyNextEngine(t_Handle h_FmPcd, t_Handle h_CcTree, uint8_t grpId, uint8_t index, t_FmPcdCcNextEngineParams *p_FmPcdCcNextEngineParams)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_tree_modify_next_engine_params_t  params;

    ASSERT_COND(sizeof(t_FmPcdCcNextEngineParams) == sizeof(ioc_fm_pcd_cc_next_engine_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.id = h_CcTree;
    params.grp_indx = grpId;
    params.indx = index;
    memcpy(&params.cc_next_engine_params, p_FmPcdCcNextEngineParams, sizeof(t_FmPcdCcNextEngineParams));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_TREE_MODIFY_NEXT_ENGINE, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_CcNodeModifyNextEngine(t_Handle h_FmPcd, t_Handle h_CcNode, uint16_t keyIndex, t_FmPcdCcNextEngineParams *p_FmPcdCcNextEngineParams)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_node_modify_next_engine_params_t  params;

    ASSERT_COND(sizeof(t_FmPcdCcNextEngineParams) == sizeof(ioc_fm_pcd_cc_next_engine_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.id = h_CcNode;
    params.key_indx = keyIndex;
    memcpy(&params.cc_next_engine_params, p_FmPcdCcNextEngineParams, sizeof(t_FmPcdCcNextEngineParams));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_NODE_MODIFY_NEXT_ENGINE, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_CcNodeModifyMissNextEngine(t_Handle h_FmPcd, t_Handle h_CcNode, t_FmPcdCcNextEngineParams *p_FmPcdCcNextEngineParams)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_node_modify_next_engine_params_t  params;

    ASSERT_COND(sizeof(t_FmPcdCcNextEngineParams) == sizeof(ioc_fm_pcd_cc_next_engine_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.id = h_CcNode;
    memcpy(&params.cc_next_engine_params, p_FmPcdCcNextEngineParams, sizeof(t_FmPcdCcNextEngineParams));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_NODE_MODIFY_MISS_NEXT_ENGINE, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_CcNodeRemoveKey(t_Handle h_FmPcd, t_Handle h_CcNode, uint16_t keyIndex)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_node_remove_key_params_t  params;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.id = h_CcNode;
    params.key_indx = keyIndex;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_NODE_REMOVE_KEY, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_CcNodeAddKey(t_Handle h_FmPcd, t_Handle h_CcNode, uint16_t keyIndex, uint8_t keySize, t_FmPcdCcKeyParams  *p_KeyParams)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_node_modify_key_and_next_engine_params_t  params;

    ASSERT_COND(sizeof(t_FmPcdCcKeyParams) == sizeof(ioc_fm_pcd_cc_key_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.id = h_CcNode;
    params.key_indx = keyIndex;
    params.key_size = keySize;
    memcpy(&params.key_params, p_KeyParams, sizeof(t_FmPcdCcKeyParams));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_NODE_ADD_KEY, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_CcNodeModifyKeyAndNextEngine(t_Handle h_FmPcd, t_Handle h_CcNode, uint16_t keyIndex, uint8_t keySize, t_FmPcdCcKeyParams *p_KeyParams)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_node_modify_key_and_next_engine_params_t  params;

    ASSERT_COND(sizeof(t_FmPcdCcKeyParams) == sizeof(ioc_fm_pcd_cc_key_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.id = h_CcNode;
    params.key_indx = keyIndex;
    params.key_size = keySize;
    memcpy(&params.key_params, p_KeyParams, sizeof(t_FmPcdCcKeyParams));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_NODE_MODIFY_KEY_AND_NEXT_ENGINE, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PCD_CcNodeModifyKey(t_Handle h_FmPcd, t_Handle h_CcNode, uint16_t keyIndex, uint8_t keySize, uint8_t  *p_Key, uint8_t *p_Mask)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_cc_node_modify_key_params_t  params;
    uint8_t                                 key[IOC_FM_PCD_MAX_SIZE_OF_KEY];
    uint8_t                                 mask[IOC_FM_PCD_MAX_SIZE_OF_KEY];

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    params.id = h_CcNode;
    params.key_indx = keyIndex;
    params.key_size = keySize;
    memcpy(key, p_Key, keySize);
    if (p_Mask)
        memcpy(mask, p_Mask, keySize);
    params.p_key = key;
    params.p_mask = mask;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_CC_NODE_MODIFY_KEY, &params))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Handle FM_PCD_PlcrSetProfile(t_Handle h_FmPcd, t_FmPcdPlcrProfileParams *p_Profile)
{
    t_Device                            *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_pcd_plcr_profile_params_t    params;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, NULL);

    memcpy(&params, p_Profile, sizeof(t_FmPcdPlcrProfileParams));

    if (!params.modify &&
        (params.profile_select.new_params.profile_type
                != (ioc_fm_pcd_profile_type_selection)e_FM_PCD_PLCR_SHARED))
        params.profile_select.new_params.p_port =
            (fm_pcd_port_params_t*) (((t_Device*) p_Profile->id.newParams.h_FmPort)->h_UserPriv);

    if (ioctl(p_Dev->fd, FM_PCD_IOC_PLCR_SET_PROFILE, &params))
    {
        REPORT_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);
        return NULL;
    }

    return (t_Handle) params.id;
	return NULL;
}

t_Error FM_PCD_PlcrDeleteProfile(t_Handle h_FmPcd, t_Handle h_Profile)
{
    t_Device    *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_Profile;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_PLCR_DEL_PROFILE, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

#if defined(FM_CAPWAP_SUPPORT) || defined(FM_IP_FRAG_N_REASSEM_SUPPORT)

t_Handle FM_PCD_ManipSetNode(t_Handle h_FmPcd, t_FmPcdManipParams *p_FmPcdManipParams)
{
    t_Device *p_Dev = (t_Device*) h_FmPcd;
	ioc_fm_pcd_manip_params_t params;

    memset(&params, 0, sizeof(ioc_fm_pcd_manip_params_t));
    memcpy(&params, p_FmPcdManipParams, sizeof(ioc_fm_pcd_manip_params_t));

    if (ioctl(p_Dev->fd, FM_PCD_IOC_MANIP_SET_NODE , &params)){
        REPORT_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);
        return NULL;
    }

	return (t_Handle)params.id;
}

t_Error  FM_PCD_ManipDeleteNode(t_Handle h_FmPcd, t_Handle h_HdrManipNode)
{
    t_Device *p_Dev = (t_Device*) h_FmPcd;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_HdrManipNode;

    if (ioctl(p_Dev->fd, FM_PCD_IOC_MANIP_DELETE_NODE, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}
#endif /* defined(FM_CAPWAP_SUPPORT) || ... */

#ifdef FM_CAPWAP_SUPPORT
t_Handle FM_PCD_StatisticsSetNode(t_Handle h_FmPcd, t_FmPcdStatsParams *p_StatsParams)
{
warning "CAPWAP lib function missing"
    return NULL;
}
#endif

typedef struct {
    e_FmPortType            portType;           /**< Port type */
    uint8_t                 portId;             /**< Port Id - relative to type */
} t_FmPort;

/********************************************************************************************/
/*  FM_PORT FUNCTIONS                                                                       */
/********************************************************************************************/

t_Handle FM_PORT_Open(t_FmPortParams *p_FmPortParams)
{
    t_Device    *p_Dev;
    int         fd;
    char        devName[30];
    t_FmPort    *p_FmPort;

    p_Dev = (t_Device*) malloc(sizeof(t_Device));
    if (!p_Dev)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM Port device!!"));
        return NULL;
    }
    memset(p_Dev, 0, sizeof(t_Device));

    p_FmPort = (t_FmPort*) malloc(sizeof(t_FmPort));
    if (!p_FmPort)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM Port device!!"));
        free(p_Dev);
        return NULL;
    }
    memset(p_FmPort, 0, sizeof(t_FmPort));

    memset(devName, 0, sizeof(devName));
    switch (p_FmPortParams->portType)
    {
        /*TODO:FMD16 OH parsing port breaks down  */
#if 0
        case e_FM_PORT_TYPE_OH_HOST_COMMAND:
            sprintf(devName, "%s%s%d-port-oh", "/dev/", DEV_FM_NAME, ((t_Device*)p_FmPortParams->h_Fm)->id);
            break;
#endif
        case e_FM_PORT_TYPE_OH_OFFLINE_PARSING:
            sprintf(devName, "%s%s%d-port-oh%d", "/dev/", DEV_FM_NAME,
                    ((t_Device*)p_FmPortParams->h_Fm)->id, p_FmPortParams->portId);
            break;
        case e_FM_PORT_TYPE_RX:
            sprintf(devName, "%s%s%d-port-rx%d", "/dev/", DEV_FM_NAME,
                    ((t_Device*)p_FmPortParams->h_Fm)->id, p_FmPortParams->portId);
            break;
        case e_FM_PORT_TYPE_RX_10G:
            sprintf(devName, "%s%s%d-port-rx%d", "/dev/", DEV_FM_NAME,
                    ((t_Device*)p_FmPortParams->h_Fm)->id, FM_MAX_NUM_OF_1G_RX_PORTS+p_FmPortParams->portId);
            break;
        case e_FM_PORT_TYPE_TX:
            sprintf(devName, "%s%s%d-port-tx%d", "/dev/", DEV_FM_NAME,
                    ((t_Device*)p_FmPortParams->h_Fm)->id, p_FmPortParams->portId);
            break;
        case e_FM_PORT_TYPE_TX_10G:
            sprintf(devName, "%s%s%d-port-tx%d", "/dev/", DEV_FM_NAME,
                    ((t_Device*)p_FmPortParams->h_Fm)->id, FM_MAX_NUM_OF_1G_TX_PORTS+p_FmPortParams->portId);
            break;
        default:
            free(p_FmPort);
            free(p_Dev);
            REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("port id!"));
            return NULL;
    }

    fd = open(devName, O_RDWR);
    if (fd < 0)
    {
       free(p_FmPort);
       free(p_Dev);
       REPORT_ERROR(MAJOR, E_OPEN_FAILED, ("Could not open FM-port %s. Ret code=%d, errno=%d. Aborting!!!",
               devName,
               fd,
               errno));
       return NULL;
    }

    p_FmPort->portType = p_FmPortParams->portType;
    p_FmPort->portId = p_FmPortParams->portId;
    p_Dev->id = p_FmPortParams->portId;
    p_Dev->fd = fd;
    p_Dev->h_UserPriv = (t_Handle) p_FmPort;

    return (t_Handle) p_Dev;
}

void FM_PORT_Close(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device *)h_FmPort;

    SANITY_CHECK_RETURN(p_Dev, E_INVALID_HANDLE);

    close(p_Dev->fd);
    if (p_Dev->h_UserPriv)
        free(p_Dev->h_UserPriv);
    free(p_Dev);
}

t_Error FM_PORT_Disable(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device *)h_FmPort;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, E_OK);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_DISABLE))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_Enable(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device *)h_FmPort;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, E_OK);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_ENABLE))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_DeleteRateLimit(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, E_OK);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_REMOVE_RATE_LIMIT))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_SetRateLimit(t_Handle h_FmPort, t_FmPortRateLimit *p_RateLimit)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    ASSERT_COND(sizeof(t_FmPortRateLimit) == sizeof(ioc_fm_port_rate_limit_t));
    SANITY_CHECK_RETURN_VALUE(p_Dev, E_INVALID_HANDLE, E_OK);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_SET_RATE_LIMIT, p_RateLimit))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_SetErrorsRoute(t_Handle h_FmPort, fmPortFrameErrSelect_t errs)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;
    int         intCast = (int) errs;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_SET_ERRORS_ROUTE, &intCast))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

uint32_t FM_PORT_AllocPCDFqids (t_Handle h_FmPort, uint32_t numFqids, uint8_t alignment)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;
    ioc_fm_port_pcd_fqids_params_t  param;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    param.num_fqids  = numFqids;
    param.alignment = alignment;
    if (ioctl(p_Dev->fd, FM_PORT_IOC_ALLOC_PCD_FQIDS, &param))
    {
        REPORT_ERROR(MINOR, E_INVALID_OPERATION,
                ("Failed to allocate %d queue IDs!", numFqids));
        return 0;
    }

    return param.base_fqid;
}

t_Error FM_PORT_FreePCDFqids (t_Handle h_FmPort, uint32_t base_fqid)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_FREE_PCD_FQIDS, &base_fqid))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION,
                ("Invalid base FQID %d or other error!", base_fqid));
    return E_OK;
}

t_Error FM_PORT_SetPCD(t_Handle h_FmPort, t_FmPortPcdParams *p_FmPortPcd)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    ASSERT_COND(sizeof(t_FmPortPcdParams) == sizeof(ioc_fm_port_pcd_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_SET_PCD, p_FmPortPcd))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_DeletePCD(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_DELETE_PCD))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_DetachPCD(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_DETACH_PCD))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_AttachPCD(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_ATTACH_PCD))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdPlcrAllocProfiles(t_Handle h_FmPort, uint16_t numOfProfiles)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_PLCR_ALLOC_PROFILES, &numOfProfiles))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdPlcrFreeProfiles(t_Handle h_FmPort)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_PLCR_FREE_PROFILES))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdKgModifyInitialScheme(t_Handle h_FmPort, t_FmPcdKgSchemeSelect *p_FmPcdKgScheme)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    ASSERT_COND(sizeof(t_FmPcdKgSchemeSelect) == sizeof(ioc_fm_pcd_kg_scheme_select_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_KG_MODIFY_INITIAL_SCHEME, p_FmPcdKgScheme))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdPlcrModifyInitialProfile (t_Handle h_FmPort, t_Handle h_Profile)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_Profile;

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_PLCR_MODIFY_INITIAL_PROFILE, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdCcModifyTree (t_Handle h_FmPort, t_Handle h_CcTree)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;
    ioc_fm_obj_t id;

    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    id.obj = h_CcTree;

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_CC_MODIFY_TREE, &id))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdKgBindSchemes (t_Handle h_FmPort, t_FmPcdPortSchemesParams *p_PortScheme)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    ASSERT_COND(sizeof(t_FmPcdPortSchemesParams) == sizeof(ioc_fm_pcd_port_schemes_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_KG_BIND_SCHEMES, p_PortScheme))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdKgUnbindSchemes (t_Handle h_FmPort, t_FmPcdPortSchemesParams *p_PortScheme)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    ASSERT_COND(sizeof(t_FmPcdPortSchemesParams) == sizeof(ioc_fm_pcd_port_schemes_params_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_KG_UNBIND_SCHEMES, p_PortScheme))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

t_Error FM_PORT_PcdModifyPrsStart (t_Handle h_FmPort, t_FmPcdPrsStart *p_FmPcdPrsStart)
{
    t_Device    *p_Dev = (t_Device*) h_FmPort;

    ASSERT_COND(sizeof(t_FmPcdPrsStart) == sizeof(ioc_fm_pcd_prs_start_t));
    SANITY_CHECK_RETURN_ERROR(p_Dev, E_INVALID_HANDLE);

    if (ioctl(p_Dev->fd, FM_PORT_IOC_PCD_PRS_MODIFY_START_OFFSET, p_FmPcdPrsStart))
        RETURN_ERROR(MINOR, E_INVALID_OPERATION, NO_MSG);

    return E_OK;
}

#ifdef P1023
void Platform_is_P1023()
{
}
#else
void Platform_is_P3_P4_P5()
{
}
#endif
