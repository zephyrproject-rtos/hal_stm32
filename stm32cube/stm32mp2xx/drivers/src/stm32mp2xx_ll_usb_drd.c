/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_usb_drd.c
  * @author  MCD Application Team
  * @brief   USB Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the USB Peripheral Controller:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Fill parameters of Init structure in USB_DWC3_CfgTypeDef structure.

      (#) Call USB_CoreInit() API to initialize the USB Core peripheral.

      (#) The upper HAL HCD/PCD driver will call the right routines for its internal processes.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_LL_USB_DRIVER
  * @{
  */

#define LL_DBGLOG(...)  (void)printf("LL_DEBUG : " __VA_ARGS__);
#define LL_DBGLOG_ONCE(...) ({ \
                               static bool __warned; \
                               \
                               if (__warned == false) \
                               { \
                                 __warned = true; \
                                 (void)printf("LL_DEBUG(Once) : " __VA_ARGS__); \
                               } \
                             })
#if (LL_DEBUG_LEVEL > 0)
#define LL_DBGLOG1(...) (void)printf("LL_DEBUG : " __VA_ARGS__);
#else
#define LL_DBGLOG1(...)
#endif /*LL_DBGLOG1*/
#if (LL_DEBUG_LEVEL > 1)
#define LL_DBGLOG2(...) (void)printf("LL_DEBUG : " __VA_ARGS__);
#else
#define LL_DBGLOG2(...)
#endif /*LL_DBGLOG2*/
#if (LL_DEBUG_LEVEL > 2)
#define LL_DBGLOG3(...) (void)printf("LL_DEBUG : " __VA_ARGS__);
#else
#define LL_DBGLOG3(...)
#endif /*LL_DBGLOG3*/

#if defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Masking macros */
#define UPPER_32_BITS(n) ((uint32_t)(((n) >> 16) >> 16))
#define LOWER_32_BITS(n) ((uint32_t)(n))

/**
  * @brief DWC3 Specific macros
  */
#define DWC3_REG32(base, x) (*(__IO uint32_t *)(((uint32_t)(base)) + (x)))

/* DWC3 IP Parameter */
#define DWC3_IP_DEVICE_NUM_INT  2U
#define DWC3_IP_NUM_EPS     32U
#define DWC3_IP_NUM_IN_EPS    16U

/* Global Registers */
#define DWC3_GSBUSCFG0    (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GSBUSCFG0
#define DWC3_GSBUSCFG1    (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GSBUSCFG1
#define DWC3_GTXTHRCFG    (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GTXTHRCFG
#define DWC3_GRXTHRCFG    (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GRXTHRCFG
#define DWC3_GCTL     (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GCTL
#define DWC3_GEVTEN     (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GEVTEN
#define DWC3_GSTS     (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GSTS
#define DWC3_GUCTL1     (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GUCTL1
#define DWC3_GSNPSID    (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GSNPSID
#define DWC3_GGPIO      (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GGPIO
#define DWC3_GUID     (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GUID
#define DWC3_GUCTL      (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GUCTL
#define DWC3_GBUSERRADDR0 (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GBUSERRADDRLO
#define DWC3_GBUSERRADDR1 (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GBUSERRADDRHI
#define DWC3_GPRTBIMAP0   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GPRTBIMAPLO
#define DWC3_GPRTBIMAP1   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GPRTBIMAPHI
#define DWC3_GHWPARAMS0   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS0
#define DWC3_GHWPARAMS1   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS1
#define DWC3_GHWPARAMS2   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS2
#define DWC3_GHWPARAMS3   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS3
#define DWC3_GHWPARAMS4   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS4
#define DWC3_GHWPARAMS5   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS5
#define DWC3_GHWPARAMS6   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS6
#define DWC3_GHWPARAMS7   (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GHWPARAMS7
#define DWC3_GDBGFIFOSPACE  (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GDBGFIFOSPACE
#define DWC3_GDBGLTSSM    (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GDBGLTSSM
#define DWC3_GPRTBIMAP_HS0  (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GPRTBIMAP_HSLO
#define DWC3_GPRTBIMAP_HS1  (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GPRTBIMAP_HSHI
#define DWC3_GPRTBIMAP_FS0  (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GPRTBIMAP_FSLO
#define DWC3_GPRTBIMAP_FS1  (uint32_t)&((USB3_TypeDef *)(NULL))->GBLREGS.GPRTBIMAP_FSHI

#define DWC3_GUSB2PHYCFG(n) (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GUSB2PHYCFG + n)
#define DWC3_GUSB2I2CCTL(n) (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GUSB2I2CCTL + n)

#define DWC3_GUSB2PHYACC(n) (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GUSB2PHYACC_ULPI + n)

#define DWC3_GUSB3PIPECTL(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GUSB3PIPECTL + n)

#define DWC3_GTXFIFOSIZ(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GTXFIFOSIZ0 + n)
#define DWC3_GRXFIFOSIZ(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GRXFIFOSIZ0 + n)

#define DWC3_GEVNTADRLO(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GEVNTADRLO + (4UL*n))
#define DWC3_GEVNTADRHI(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GEVNTADRHI + (4UL*n))
#define DWC3_GEVNTSIZ(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GEVNTSIZ + (4UL*n))
#define DWC3_GEVNTCOUNT(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->GBLREGS.GEVNTCOUNT + (4UL*n))

#define DWC3_GUSB2PHYACC_ADDR(n)  ((n) << USB3_GUSB2PHYACC_ULPI_REGADDR_Pos)
#define DWC3_GUSB2PHYACC_EXTEND_ADDR(n) ((n) << USB3_GUSB2PHYACC_ULPI_EXTREGADDR_Pos)
#define DWC3_GUSB2PHYACC_DATA(n)  ((n) & USB3_GUSB2PHYACC_ULPI_REGDATA_Msk)

/* Device Registers */
#define DWC3_DCFG   (uint32_t)&((USB3_TypeDef *)(NULL))->DEVREGS.DCFG
#define DWC3_DCTL   (uint32_t)&((USB3_TypeDef *)(NULL))->DEVREGS.DCTL
#define DWC3_DEVTEN   (uint32_t)&((USB3_TypeDef *)(NULL))->DEVREGS.DEVTEN
#define DWC3_DSTS   (uint32_t)&((USB3_TypeDef *)(NULL))->DEVREGS.DSTS
#define DWC3_DGCMDPAR (uint32_t)&((USB3_TypeDef *)(NULL))->DEVREGS.DGCMDPAR
#define DWC3_DGCMD    (uint32_t)&((USB3_TypeDef *)(NULL))->DEVREGS.DGCMD
#define DWC3_DALEPENA (uint32_t)&((USB3_TypeDef *)(NULL))->DEVREGS.DALEPENA
#define DWC3_DEPCMDPAR2(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->DEVREGS.DEPCMDPAR2 + (4UL*n))
#define DWC3_DEPCMDPAR1(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->DEVREGS.DEPCMDPAR1 + (4UL*n))
#define DWC3_DEPCMDPAR0(n)  (uint32_t)(&((USB3_TypeDef *)(NULL))->DEVREGS.DEPCMDPAR0 + (4UL*n))
#define DWC3_DEPCMD(n)    (uint32_t)(&((USB3_TypeDef *)(NULL))->DEVREGS.DEPCMD + (4UL*n))

/* The EP number goes 0..31 so ep0 is always out and ep1 is always in */
#define DWC3_DALEPENA_EP(n)   (1UL << (n))

#define DWC3_DEPCMD_TYPE_CONTROL  0U
#define DWC3_DEPCMD_TYPE_ISOC   1U
#define DWC3_DEPCMD_TYPE_BULK   2U
#define DWC3_DEPCMD_TYPE_INTR   3U

#define DWC3_GCTL_PRTCAP(n) (((n) & USB3_GCTL_PRTCAPDIR_Msk) >> USB3_GCTL_PRTCAPDIR_Pos)
#define DWC3_GCTL_PRTCAPDIR(n)  ((n) << USB3_GCTL_PRTCAPDIR_Pos)
#define DWC3_GCTL_PRTCAP_HOST 1U
#define DWC3_GCTL_PRTCAP_DEVICE 2U
#define DWC3_GCTL_PRTCAP_OTG  3U

#define DWC3_DSTS_SUPERSPEED  (4U << USB3_DSTS_CONNECTSPD_Pos)
#define DWC3_DSTS_HIGHSPEED   (0U << USB3_DSTS_CONNECTSPD_Pos)
#define DWC3_DSTS_FULLSPEED2  (1U << USB3_DSTS_CONNECTSPD_Pos)
#define DWC3_DSTS_LOWSPEED    (2U << USB3_DSTS_CONNECTSPD_Pos)
#define DWC3_DSTS_FULLSPEED1  (3U << USB3_DSTS_CONNECTSPD_Pos)

#define DWC3_GEVNTCOUNT_MASK  0xfffcU
#define DWC3_GSNPSID_MASK 0xffff0000
#define DWC3_GSNPSREV_MASK  0xffff

#define DWC3_DCFG_DEVADDR(addr) ((addr) << 3)

#define DWC3_EVENT_TYPE_DEV 0U
#define DWC3_EVENT_TYPE_CARKIT  3U
#define DWC3_EVENT_TYPE_I2C 4U

#define DWC3_DEVICE_EVENT_DISCONNECT      0U
#define DWC3_DEVICE_EVENT_RESET         1U
#define DWC3_DEVICE_EVENT_CONNECT_DONE      2U
#define DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE  3U
#define DWC3_DEVICE_EVENT_WAKEUP        4U
#define DWC3_DEVICE_EVENT_HIBER_REQ       5U
#define DWC3_DEVICE_EVENT_EOPF          6U
#define DWC3_DEVICE_EVENT_SOF         7U
#define DWC3_DEVICE_EVENT_ERRATIC_ERROR     9U
#define DWC3_DEVICE_EVENT_CMD_CMPL        10U
#define DWC3_DEVICE_EVENT_OVERFLOW        11U

/* DEPCFG parameter 1 */
#define DWC3_DEPCFG_INT_NUM(n)    (((n) & 0x1f) << 0)
#define DWC3_DEPCFG_XFER_COMPLETE_EN  (1U << 8)
#define DWC3_DEPCFG_XFER_IN_PROGRESS_EN (1U << 9)
#define DWC3_DEPCFG_XFER_NOT_READY_EN (1U << 10)
#define DWC3_DEPCFG_FIFO_ERROR_EN (1U << 11)
#define DWC3_DEPCFG_STREAM_EVENT_EN (1U << 13)
#define DWC3_DEPCFG_BINTERVAL_M1(n) (((n) & 0xffU) << 16)
#define DWC3_DEPCFG_STREAM_CAPABLE  (1U << 24)
#define DWC3_DEPCFG_EP_NUMBER(n)  (((n) & 0x1fUL) << 25)
#define DWC3_DEPCFG_BULK_BASED    (1U << 30)
#define DWC3_DEPCFG_FIFO_BASED    (1U << 31)

/* DEPCFG parameter 0 */
#define DWC3_DEPCFG_EP_TYPE(n)    (((n) & 0x3UL) << 1)
#define DWC3_DEPCFG_MAX_PACKET_SIZE(n)  (((n) & 0x7ffU) << 3)
#define DWC3_DEPCFG_FIFO_NUMBER(n)  (((n) & 0x1fUL) << 17)
#define DWC3_DEPCFG_BURST_SIZE(n) (((n) & 0xf) << 22)
#define DWC3_DEPCFG_DATA_SEQ_NUM(n) ((n) << 26)
/* DEPCFG parameter 1 */
#define DWC3_DEPCFG_EP_INTR_NUM(n)  ((n) & 0x1fUL)
/* This applies for core versions earlier than 1.94a */
#define DWC3_DEPCFG_IGN_SEQ_NUM   (1U << 31)
/* These apply for core versions 1.94a and later */
#define DWC3_DEPCFG_ACTION_INIT   (0U << 30)
#define DWC3_DEPCFG_ACTION_RESTORE  (1U << 30)
#define DWC3_DEPCFG_ACTION_MODIFY (2U << 30)
#define DWC3_DEPCFG_ACTION_VALUE(n)   (((n) & 0x3U) << 30)

/* DEPXFERCFG parameter 0 */
#define DWC3_DEPXFERCFG_NUM_XFER_RES(n) ((n) & 0xffffU)

#define DWC3_DEPCMD_GET_RSC_IDX(x)  (((x) >> USB3_DEPCMD_COMMANDPARAM_Pos) & 0x7fU)
#define DWC3_DEPCMD_STATUS(x)   (((x) & USB3_DEPCMD_CMDSTATUS_Msk) >> 12)
#define DWC3_DGCMD_STATUS(n)  (((n) & USB3_DGCMD_CMDSTATUS_Msk) >> USB3_DGCMD_CMDSTATUS_Pos)
#define DWC3_DEPCMD_PARAM(x)    ((x) << USB3_DEPCMD_COMMANDPARAM_Pos)

/* LINK STATE Types */
#define DWC3_LINK_STATE_SS_U0   0x00U /* in HS, means ON */
#define DWC3_LINK_STATE_SS_U1   0x01U
#define DWC3_LINK_STATE_SS_U2   0x02U /* in HS, means SLEEP */
#define DWC3_LINK_STATE_SS_U3   0x03U /* in HS, means SUSPEND */
#define DWC3_LINK_STATE_SS_DIS    0x04U /* Default State */
#define DWC3_LINK_STATE_SS_RX_DET 0x05U /* in HS, means Early Suspend */
#define DWC3_LINK_STATE_SS_INACT  0x06U
#define DWC3_LINK_STATE_SS_POLL   0x07U
#define DWC3_LINK_STATE_SS_RECOV  0x08U
#define DWC3_LINK_STATE_SS_HRESET 0x09U
#define DWC3_LINK_STATE_SS_CMPLY  0x0aU
#define DWC3_LINK_STATE_SS_LPBK   0x0bU
#define DWC3_LINK_STATE_SS_RESET  0x0eU
#define DWC3_LINK_STATE_SS_RESUME 0x0fU

#define DWC3_LINK_STATE_ON    0x00U /* in HS, means ON */
#define DWC3_LINK_STATE_L1    0x02U /* in HS, means SLEEP */
#define DWC3_LINK_STATE_L2    0x03U /* in HS, means SUSPEND */
#define DWC3_LINK_STATE_DIS   0x04U /* Default State */
#define DWC3_LINK_STATE_EARLY_SUS 0x05U /* in HS, means Early Suspend */
#define DWC3_LINK_STATE_RESET 0x0eU
#define DWC3_LINK_STATE_RESUME  0x0fU

#define DWC3_DCTL_ULSTCHNG_NO_ACTION  0U
#define DWC3_DCTL_ULSTCHNG_SS_DISABLED  4U
#define DWC3_DCTL_ULSTCHNG_RX_DETECT  5U
#define DWC3_DCTL_ULSTCHNG_SS_INACTIVE  6U
#define DWC3_DCTL_ULSTCHNG_RECOVERY   8U
#define DWC3_DCTL_ULSTCHNG_COMPLIANCE 10U
#define DWC3_DCTL_ULSTCHNG_LOOPBACK   11U

#define DWC3_DCTL_ULSTCHNGREQ(n)  (((n) << USB3_DCTL_ULSTCHNGREQ_Pos) & USB3_DCTL_ULSTCHNGREQ_Msk)

#define DWC3_DSTS_USBLNKST(n)   (((n) & USB3_DSTS_USBLNKST_Msk) >> USB3_DSTS_USBLNKST_Pos)

/* TRB Length, PCM and Status */
#define DWC3_TRB_SIZE_MASK  (0x00ffffffU)
#define DWC3_TRB_SIZE_LENGTH(n) ((n) & DWC3_TRB_SIZE_MASK)
#define DWC3_TRB_SIZE_PCM1(n) (((n) & 0x03U) << 24)
#define DWC3_TRB_SIZE_TRBSTS(n) (((n) & (0x0fU << 28)) >> 28)

#define DWC3_TRBSTS_OK      0U
#define DWC3_TRBSTS_MISSED_ISOC   1U
#define DWC3_TRBSTS_SETUP_PENDING 2U
#define DWC3_TRBSTS_XFER_IN_PROG 4U

/* TRB Control */
#define DWC3_TRB_CTRL_HWO   (1U << 0)
#define DWC3_TRB_CTRL_LST   (1U << 1)
#define DWC3_TRB_CTRL_CHN   (1U << 2)
#define DWC3_TRB_CTRL_CSP   (1U << 3)
#define DWC3_TRB_CTRL_TRBCTL(n)   (((n) & 0x3fU) << 4)
#define DWC3_TRB_CTRL_ISP_IMI   (1U << 10)
#define DWC3_TRB_CTRL_IOC   (1U << 11)
#define DWC3_TRB_CTRL_SID_SOFN(n) (((n) & 0xffffU) << 14)

#define DWC3_TRBCTL_NORMAL    DWC3_TRB_CTRL_TRBCTL(1U)
#define DWC3_TRBCTL_CONTROL_SETUP DWC3_TRB_CTRL_TRBCTL(2U)
#define DWC3_TRBCTL_CONTROL_STATUS2 DWC3_TRB_CTRL_TRBCTL(3U)
#define DWC3_TRBCTL_CONTROL_STATUS3 DWC3_TRB_CTRL_TRBCTL(4U)
#define DWC3_TRBCTL_CONTROL_DATA  DWC3_TRB_CTRL_TRBCTL(5U)
#define DWC3_TRBCTL_ISOCHRONOUS_FIRST DWC3_TRB_CTRL_TRBCTL(6U)
#define DWC3_TRBCTL_ISOCHRONOUS   DWC3_TRB_CTRL_TRBCTL(7U)
#define DWC3_TRBCTL_LINK_TRB    DWC3_TRB_CTRL_TRBCTL(8U)

#define MASK(len, pos)    (((1U << (len)) - 1U) << (pos))
#define BIT_MASK(nr)    ((1UL << (nr)) - 1)

/* Event Types */
#define DWC3_EVT_TYPE_EP 0x0U
#define DWC3_EVT_TYPE_LEN 0x1U
#define DWC3_EVT_TYPE_BITPOS 0x0U
#define DWC3_EVT_TYPE_MASK MASK(DWC3_EVT_TYPE_LEN, DWC3_EVT_TYPE_BITPOS)
#define DWC3_EVT_TYPE_DEVSPEC 0x1U
#define DWC3_EVT_TYPE_NEP_TYPE_BITPOS 1U
#define DWC3_EVT_TYPE_NEP_TYPE_LEN 7U
#define DWC3_EVT_TYPE_NEP_TYPE_MASK MASK(DWC3_EVT_TYPE_NEP_TYPE_LEN, DWC3_EVT_TYPE_NEP_TYPE_BITPOS)

#define DWC3_DEPEVT_XFERCOMPLETE  0x01U
#define DWC3_DEPEVT_XFERINPROGRESS  0x02U
#define DWC3_DEPEVT_XFERNOTREADY  0x03U
#define DWC3_DEPEVT_RXTXFIFOEVT   0x04U
#define DWC3_DEPEVT_STREAMEVT   0x06U
#define DWC3_DEPEVT_EPCMDCMPLT    0x07U

#define DWC3_EVT_DEPEVT_TYPE_BITPOS 6U
#define DWC3_EVT_DEPEVT_TYPE_LEN  4U
#define DWC3_EVT_DEPEVT_TYPE_MASK MASK(DWC3_EVT_DEPEVT_TYPE_LEN, DWC3_EVT_DEPEVT_TYPE_BITPOS)

#define DWC3_EVT_DEPEVT_EPNUM_BITPOS  1U
#define DWC3_EVT_DEPEVT_EPNUM_LEN   5U
#define DWC3_EVT_DEPEVT_EPNUM_MASK MASK(DWC3_EVT_DEPEVT_EPNUM_LEN, DWC3_EVT_DEPEVT_EPNUM_BITPOS)

#define DWC3_EVT_DEPEVT_STATUS_BITPOS 12U
#define DWC3_EVT_DEPEVT_STATUS_LEN    4U
#define DWC3_EVT_DEPEVT_STATUS_MASK MASK(DWC3_EVT_DEPEVT_STATUS_LEN, DWC3_EVT_DEPEVT_STATUS_BITPOS)

/* Control-only Status */
#define DWC3_EVT_DEPEVT_STATUS_CONTROL_DATA   1U
#define DWC3_EVT_DEPEVT_STATUS_CONTROL_STATUS 2U

#define DWC3_EVT_DEPEVT_PARAM_BITPOS  16U
#define DWC3_EVT_DEPEVT_PARAM_LEN   16U
#define DWC3_EVT_DEPEVT_PARAM_MASK MASK(DWC3_EVT_DEPEVT_PARAM_LEN, DWC3_EVT_DEPEVT_PARAM_BITPOS)

#define DWC3_EVT_DEVEVT_TYPE_BITPOS   8U
#define DWC3_EVT_DEVEVT_TYPE_LEN    4U
#define DWC3_EVT_DEVEVT_TYPE_MASK MASK(DWC3_EVT_DEVEVT_TYPE_LEN, DWC3_EVT_DEVEVT_TYPE_BITPOS)

#define DWC3_EVT_DEVEVT_LNKSTS_BITPOS 16U
#define DWC3_EVT_DEVEVT_LNKSTS_LEN    4U
#define DWC3_EVT_DEVEVT_LNKSTS_MASK MASK(DWC3_EVT_DEVEVT_LNKSTS_LEN, DWC3_EVT_DEVEVT_LNKSTS_BITPOS)

/*
 * ULPI Register Map
 */
#define ULPI_VENDOR_ID_LOW      0x00U
#define ULPI_VENDOR_ID_HIGH     0x01U
#define ULPI_PRODUCT_ID_LOW     0x02U
#define ULPI_PRODUCT_ID_HIGH      0x03U
#define ULPI_FUNC_CTRL        0x04U
#define ULPI_IFC_CTRL       0x07U
#define ULPI_OTG_CTRL       0x0aU
#define ULPI_USB_INT_EN_RISE      0x0dU
#define ULPI_USB_INT_EN_FALL      0x10U
#define ULPI_USB_INT_STS      0x13U
#define ULPI_USB_INT_LATCH      0x14U
#define ULPI_DEBUG        0x15U
#define ULPI_SCRATCH        0x16U
/* Optional Carkit Registers */
#define ULPI_CARKIT_CTRL      0x19U
#define ULPI_CARKIT_INT_DELAY     0x1cU
#define ULPI_CARKIT_INT_EN      0x1dU
#define ULPI_CARKIT_INT_STS     0x20U
#define ULPI_CARKIT_INT_LATCH     0x21U
#define ULPI_CARKIT_PLS_CTRL      0x22U
/* Other Optional Registers */
#define ULPI_TX_POS_WIDTH     0x25U
#define ULPI_TX_NEG_WIDTH     0x26U
#define ULPI_POLARITY_RECOVERY      0x27U
/* Access Extended Register Set */
#define ULPI_ACCESS_EXTENDED      0x2fU
/* Vendor Specific */
#define ULPI_VENDOR_SPECIFIC      0x30U
/* Extended Registers */
#define ULPI_EXT_VENDOR_SPECIFIC    0x80U

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static void USB_PHYInit(void)
{
  return;
}

static void USB_PHYUnInit(void)
{
  return;
}

static void USB_Delay(uint32_t time_in_us)
{
  __IO uint32_t delay = time_in_us * (SystemCoreClock / 1000000U);

  /* Check if System Clock is at least Mhz */
  if (delay == 0U)
  {
    LL_DBGLOG_ONCE("System Clock %ld is slower than delay period requested %ld uS, delay only 1 SysClock Cycle\n",
                   SystemCoreClock, time_in_us);
  }
  else
  {
    delay += ((SystemCoreClock % 1000000U) == 0U) ? 0U : 1U;
  }

  do
  {
    __NOP();
    delay --;
  } while (delay > 0U);

  return;
}

/* Exported functions --------------------------------------------------------*/
/** @defgroup LL_USB_Exported_Functions USB Low Layer Exported Functions
  * @{
  */

/** @defgroup LL_USB_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization/de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  DWC3_RegRead : USB3 Register Read
  * @param  base    Base Register address
  * @param  offset  Register offset
  * @retval Register Value
  */
static uint32_t DWC3_RegRead(const USB3_TypeDef *base, uint32_t offset)
{
#ifndef DMA_MEM_NON_BUFFERABLE
  __DSB();
#endif /*DMA_MEM_NON_BUFFERABLE*/
  return DWC3_REG32(base, offset);
}

/**
  * @brief  DWC3_RegWrite : USB3 Register Write
  * @param  base    Base Register address
  * @param  offset  Register offset
  * @param  value   Value to be written to the register
  */
static void DWC3_RegWrite(USB3_TypeDef *base, uint32_t offset, uint32_t value)
{
#ifndef DMA_MEM_NON_BUFFERABLE
  __DSB();
#endif /*DMA_MEM_NON_BUFFERABLE*/
  DWC3_REG32(base, offset) = value;
}

/**
  * @brief  DWC3_RegUpdateSet : USB3 Register update set mask
  * @param  base    Base Register address
  * @param  offset  Register offset
  * @param  set_mask   Register set_mask
  */
static void DWC3_RegUpdateSet(USB3_TypeDef *base, uint32_t offset, uint32_t set_mask)
{
  DWC3_RegWrite(base, offset, DWC3_RegRead(base, offset) | set_mask);
}

/**
  * @brief  DWC3_RegUpdateClr : USB3 Register update clr mask
  * @param  base    Base Register address
  * @param  offset  Register offset
  * @param  clr_mask   Register clr_mask
  */
static void DWC3_RegUpdateClr(USB3_TypeDef *base, uint32_t offset, uint32_t clr_mask)
{
  DWC3_RegWrite(base, offset, DWC3_RegRead(base, offset) & ~clr_mask);
}

/**
  * @brief  DWC3_SoftReset : USB3 Device Soft Reset
  * @param  USBx  Selected device
  * @retval HAL status
  */
static HAL_StatusTypeDef DWC3_SoftReset(USB3_TypeDef *USBx)
{
  uint32_t tickstart;
  uint32_t timeout = 500; /* msec */

  /* Get tick */
  tickstart = HAL_GetTick();

  DWC3_RegWrite(USBx, DWC3_DCTL, USB3_DCTL_CSFTRST);
  do
  {
    if ((DWC3_RegRead(USBx, DWC3_DCTL) & USB3_DCTL_CSFTRST) == 0U)
    {
      break;
    }

    if ((HAL_GetTick()  - tickstart) > timeout)
      /* "Reset Timed Out" */
    {
      return HAL_TIMEOUT;
    }

  } while (true);

  return HAL_OK;
}

static uint32_t DWC3_GetTRBCtlType(uint32_t trb_type)
{
  uint32_t ret;

  switch (trb_type)
  {
    case USB_DWC3_TRBCTL_NORMAL:
      ret = DWC3_TRBCTL_NORMAL;
      break;
    case USB_DWC3_TRBCTL_CONTROL_SETUP:
      ret = DWC3_TRBCTL_CONTROL_SETUP;
      break;
    case USB_DWC3_TRBCTL_CONTROL_STATUS2:
      ret = DWC3_TRBCTL_CONTROL_STATUS2;
      break;
    case USB_DWC3_TRBCTL_CONTROL_STATUS3:
      ret = DWC3_TRBCTL_CONTROL_STATUS3;
      break;
    case USB_DWC3_TRBCTL_CONTROL_DATA:
      ret = DWC3_TRBCTL_CONTROL_DATA;
      break;
    case USB_DWC3_TRBCTL_ISOCHRONOUS_FIRST:
      ret = DWC3_TRBCTL_ISOCHRONOUS_FIRST;
      break;
    case USB_DWC3_TRBCTL_ISOCHRONOUS:
      ret = DWC3_TRBCTL_ISOCHRONOUS;
      break;
    case USB_DWC3_TRBCTL_LINK_TRB:
      ret = DWC3_TRBCTL_LINK_TRB;
      break;
    default:
      ret = 0U;
      break;
  }

  return ret;
}

static uint32_t DWC3_GetEPCFGAction(uint8_t action)
{
  uint32_t ret;

  switch (action)
  {
    case USB_DWC3_DEPCFG_ACTION_INIT:
      ret = DWC3_DEPCFG_ACTION_INIT;
      break;
    case USB_DWC3_DEPCFG_ACTION_RESTORE:
      ret = DWC3_DEPCFG_ACTION_RESTORE;
      break;
    case USB_DWC3_DEPCFG_ACTION_MODIFY:
      ret = DWC3_DEPCFG_ACTION_MODIFY;
      break;
    default:
      ret = 0U;
      break;
  }

  return ret;
}


/**
  * @brief  Initializes the USB Core
  * @param  USBx USB Instance
  * @param  cfg  pointer to a USB_DWC3_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_CoreInit(USB3_TypeDef *USBx, USB_DWC3_CfgTypeDef cfg)
{
  HAL_StatusTypeDef ret;
  LL_DBGLOG("Core ID %08lx\n", (uint32_t)DWC3_RegRead(USBx, DWC3_GSNPSID));

  /* Set GUSB3PIPECTL for all USB3 ports (1-n), currently doing only for 0 */
  if ((cfg.phy_itface & USB3PHY_MASK) != 0U)
  {
    /* Relying on default value */
  }

  /* Set GUSB2PHYCFG for all USB2 ports (1-m), currently doing only for 0 */
  if ((cfg.phy_itface & USB2PHY_MASK) != 0U)
  {
    switch (cfg.phy_itface)
    {
      case USBPHY_UTMI:
        DWC3_RegUpdateClr(USBx, DWC3_GUSB2PHYCFG(0UL), USB3_GUSB2PHYCFG_ULPI_UTMI_Sel);
        break;
      case USBPHY_ULPI:
        DWC3_RegUpdateSet(USBx, DWC3_GUSB2PHYCFG(0UL), USB3_GUSB2PHYCFG_ULPI_UTMI_Sel);
        break;
      default:
        /* Relying on default value. */
        break;
    }
  }

  /* issue device SoftReset */
  ret = DWC3_SoftReset(USBx);
  if (ret != HAL_OK)
  {
    LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  /* Put PHYs in reset */
  /* Before Resetting PHY, put Core in Reset */
  DWC3_RegUpdateSet(USBx, DWC3_GCTL, USB3_GCTL_CORESOFTRESET);

  /* Assert USB3 PHY reset for all USB3 ports (1-n), currently doing only for 0 */
  if ((cfg.phy_itface & USB3PHY_MASK) != 0U)
  {
    DWC3_RegUpdateSet(USBx, DWC3_GUSB3PIPECTL(0UL), USB3_GUSB3PIPECTL_PHYSoftRst);
  }

  /* Assert USB2 PHY reset for all USB2 ports (1-m), currently doing only for 0 */
  if ((cfg.phy_itface & USB2PHY_MASK) != 0U)
  {
    DWC3_RegUpdateSet(USBx, DWC3_GUSB2PHYCFG(0UL), USB3_GUSB2PHYCFG_PHYSOFTRST);
  }

  /* Program PHY signals - PHY specific */
  USB_PHYInit();

  /* Release PHY out of reset */
#ifndef USE_STM32MP257CXX_EMU
  /* delay un-necessary in EMU since no phy */
  HAL_Delay(100); /* 100ms*/
#endif /*USE_STM32MP257CXX_EMU*/

  /* Clear USB3 PHY reset for all USB3 ports (1-n), currently doing only for 0 */
  if ((cfg.phy_itface & USB3PHY_MASK) != 0U)
  {
    DWC3_RegUpdateClr(USBx, DWC3_GUSB3PIPECTL(0UL), USB3_GUSB3PIPECTL_PHYSoftRst);
  }

  /* Clear USB2 PHY reset */
  if ((cfg.phy_itface & USB2PHY_MASK) != 0U)
  {
    DWC3_RegUpdateClr(USBx, DWC3_GUSB2PHYCFG(0UL), USB3_GUSB2PHYCFG_PHYSOFTRST);
  }

#ifndef USE_STM32MP257CXX_EMU
  /* delay un-necessary in EMU since no phy */
  HAL_Delay(100); /* 100ms*/
#endif /*USE_STM32MP257CXX_EMU*/

  /* After PHYs are stable we can take Core out of reset state */
  DWC3_RegUpdateClr(USBx, DWC3_GCTL, USB3_GCTL_CORESOFTRESET);

  /* From Linux Driver */
  DWC3_RegWrite(USBx, DWC3_GSBUSCFG0, 0xe);
  DWC3_RegWrite(USBx, DWC3_GSBUSCFG1, 0xf00);

  return HAL_OK;
}

/**
  * @brief  UnInitializes the USB Core
  * @param  USBx USB Instance
  * @retval HAL status
  */
HAL_StatusTypeDef USB_CoreUnInit(const USB3_TypeDef *USBx)
{
  UNUSED(USBx);
  /* Program PHY signals - PHY specific */
  USB_PHYUnInit();
  return HAL_OK;
}

/**
  * @brief  USB_SetCurrentMode : Set functional mode
  * @param  USBx  Selected device
  * @param  mode   current core mode
  *          This parameter can be one of these values:
  *            @arg USB_DWC3_DEVICE_MODE: Peripheral mode
  *            @arg USB_DWC3_HOST_MODE: Host mode
  *            @arg USB_DWC3_DRD_MODE: Dual Role Device mode
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetCurrentMode(USB3_TypeDef *USBx, USB_DWC3_ModeTypeDef mode)
{
  uint32_t reg;
  HAL_StatusTypeDef ret = HAL_OK;
  reg = DWC3_RegRead(USBx, DWC3_GCTL) & ~USB3_GCTL_PRTCAPDIR_Msk;

  switch (mode)
  {
    case USB_DWC3_DEVICE_MODE:
      DWC3_RegWrite(USBx, DWC3_GCTL, reg | DWC3_GCTL_PRTCAPDIR(DWC3_GCTL_PRTCAP_DEVICE));
      break;
    case USB_DWC3_HOST_MODE:
      DWC3_RegWrite(USBx, DWC3_GCTL, reg | DWC3_GCTL_PRTCAPDIR(DWC3_GCTL_PRTCAP_HOST));
      break;
    case USB_DWC3_DRD_MODE:
      DWC3_RegWrite(USBx, DWC3_GCTL, reg | DWC3_GCTL_PRTCAPDIR(DWC3_GCTL_PRTCAP_OTG));
      break;
    default:
      ret = HAL_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  USB_DevInit : Initializes the USB3 controller registers
  *         for device mode
  * @param  USBx  Selected device
  * @param  cfg   pointer to a USB_DWC3_CfgTypeDef structure that contains
  *         the configuration information for the specified USBx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DevInit(USB3_TypeDef *USBx, USB_DWC3_CfgTypeDef cfg,
                              USB_DWC3_DmaBusAddr evt_buf_dma_addr[], USB_DWC3_EPTypeDef *ep0,
                              USB_DWC3_DmaBusAddr setup_buf_dma_addr, USB_DWC3_INTNum intr_dev)
{
  uint32_t reg;
  uint8_t i;
  USB_DWC3_EPCmdParams params;
  HAL_StatusTypeDef ret;

  /* Setup event buffers k = USB_DWC3_INT_INUSE */
  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    DWC3_RegWrite(USBx, DWC3_GEVNTADRLO(i), LOWER_32_BITS(evt_buf_dma_addr[i]));
    DWC3_RegWrite(USBx, DWC3_GEVNTADRHI(i), UPPER_32_BITS(evt_buf_dma_addr[i]));
    DWC3_RegWrite(USBx, DWC3_GEVNTSIZ(i), USB_DWC3_EVENT_BUFFER_SIZE);
    DWC3_RegWrite(USBx, DWC3_GEVNTCOUNT(i), 0);
    /* EvtBufferPos[i] = 0;  Implicit since static done in HAL */
  }

  ret = USB_SetCurrentMode(USBx, USB_DWC3_DEVICE_MODE);
  if (ret != HAL_OK)
  {
    LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  ret = USB_SetDevSpeed(USBx, cfg.speed);
  if (ret != HAL_OK)
  {
    LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  /* Issue a DEPSTARTCFG command with DEPCMD0.XferRscIdx set to 0,
  to initialize the transfer resource allocation */
  (void)memset(&params, 0x00, sizeof(params));
  ret = USB_ExecuteDevEPCmd(USBx, 0U, DWC3_DEPCMD_PARAM(0U) | USB_DWC3_DEPCMD_DEPSTARTCFG, &params);
  if (ret != HAL_OK)
  {
    LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  /* Configure Control EP 0 & 1 mapped to physical EP 0 & 1*/
  ret = USB_ConfigureEP(USBx, 0, false, EP_TYPE_CTRL, cfg.ep0_mps, 0, 0, 0, ep0->intr_num, USB_DWC3_DEPCFG_ACTION_INIT);
  if (ret != HAL_OK)
  {
    LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }
  ret = USB_ConfigureEP(USBx, 0, true, EP_TYPE_CTRL, cfg.ep0_mps, 0, 0, 1, ep0->intr_num, USB_DWC3_DEPCFG_ACTION_INIT);
  if (ret != HAL_OK)
  {
    LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  /* Transfer Resource for Control EP 0 & 1*/
  (void)memset(&params, 0x00, sizeof(params));
  params.param0 = DWC3_DEPXFERCFG_NUM_XFER_RES(1U);
  /* As per databook, "Issue a DEPSTARTCFG command with DEPCMD0.XferRscIdx set to 2 to re-initialize the
  transfer resource allocation on SetConfiguration or SetInterface Request", value is 2 since the EP0 & EP1
  take up the transfer resource 1 & 2, hence further EPs will take resources 2,3,&up.. But in HAL we are not
  decoding the Setup-packet requests, this should ideally come from USB-MW core.
  Instead we follow the same method as Linux dwc3-gadget controller driver, All hardware endpoints can be
  assigned a transfer resource and this setting will stay persistent until either a core reset or hibernation.
  So whenever we do a DEPSTARTCFG(0) we can go ahead and do DEPXFERCFG for every hardware endpoint as well.
  For all k = DWC3_IP_NUM_EPS */
  for (i = 0; i < DWC3_IP_NUM_EPS; i++)
  {
    ret = USB_ExecuteDevEPCmd(USBx, i, USB_DWC3_DEPCMD_SETTRANSFRESOURCE, &params);
    if (ret != HAL_OK)
    {
      LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
      return ret;
    }
  }

  /* setup EP0 to receive SETUP packets */
  ret = USB_EP0_OutStart(USBx, ep0, setup_buf_dma_addr);
  if (ret != HAL_OK)
  {
    LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
    return ret;
  }

  /* Enable EP 0 & 1 */
  DWC3_RegUpdateSet(USBx, DWC3_DALEPENA, DWC3_DALEPENA_EP(0) | DWC3_DALEPENA_EP(1));

  /* Set interrupt/EventQ number on which non-endpoint-specific device-related interrupts are generated */
  reg = DWC3_RegRead(USBx, DWC3_DCFG) & ~USB3_DCFG_INTRNUM_Msk;
  DWC3_RegWrite(USBx, DWC3_DCFG, reg | ((uint32_t)intr_dev << USB3_DCFG_INTRNUM_Pos));

  /* Enable all events but Start and End of Frame IRQs */
  DWC3_RegUpdateSet(USBx, DWC3_DEVTEN, USB3_DEVTEN_VENDEVTSTRCVDEN | USB3_DEVTEN_EVNTOVERFLOWEN |
                    USB3_DEVTEN_CMDCMPLTEN | USB3_DEVTEN_ERRTICERREVTEN | USB3_DEVTEN_U3L2L1SuspEn |
                    USB3_DEVTEN_HibernationReqEvtEn | USB3_DEVTEN_WKUPEVTEN | USB3_DEVTEN_ULSTCNGEN |
                    USB3_DEVTEN_CONNECTDONEEVTEN | USB3_DEVTEN_USBRSTEVTEN | USB3_DEVTEN_DISSCONNEVTEN |
                    USB3_DEVTEN_L1SUSPEN | USB3_DEVTEN_L1WKUPEVTEN);

  if (cfg.Sof_enable)
  {
    DWC3_RegUpdateSet(USBx, DWC3_DEVTEN, USB3_DEVTEN_SOFTEVTEN);
  }

  /* Enable Event Buffer interrupt k = USB_DWC3_INT_INUSE */
  for (i = 0; i < USB_DWC3_INT_INUSE; i++)
  {
    USB_EnableEventInt(USBx, i);
  }

  return HAL_OK;
}

/**
  * @brief  USB_SetDevSpeed :Initializes the DevSpd field of DCFG register
  *         depending the PHY type and the enumeration speed of the device.
  * @param  USBx  Selected device
  * @param  speed  device speed
  *          This parameter can be one of these values:
  *            @arg USB_DWC3_SPEED_HIGH: High speed mode
  *            @arg USB_DWC3_SPEED_HIGH_IN_FULL: High speed core in Full Speed mode
  *            @arg USB_DWC3_SPEED_FULL: Full speed mode
  *            @arg USB_DWC3_SPEED_LOW: Low speed mode
  * @retval  Hal status
  */
HAL_StatusTypeDef USB_SetDevSpeed(USB3_TypeDef *USBx, uint8_t speed)
{
  uint32_t reg;
  HAL_StatusTypeDef ret = HAL_OK;
  reg = DWC3_RegRead(USBx, DWC3_DCFG) & ~USB3_DCFG_DEVSPD_Msk;

  switch (speed)
  {
    case USB_DWC3_SPEED_SUPER:
      DWC3_RegWrite(USBx, DWC3_DCFG, reg | DWC3_DSTS_SUPERSPEED);
      LL_DBGLOG2("%s = SuperSpeed\n", __func__);
      break;
    case USB_DWC3_SPEED_HIGH:
      DWC3_RegWrite(USBx, DWC3_DCFG, reg |  DWC3_DSTS_HIGHSPEED);
      LL_DBGLOG2("%s = HighSpeed\n", __func__);
      break;
    case USB_DWC3_SPEED_FULL_48:
      DWC3_RegWrite(USBx, DWC3_DCFG, reg |  DWC3_DSTS_FULLSPEED1);
      LL_DBGLOG2("%s = FullSpeed_48M\n", __func__);
      break;
    case USB_DWC3_SPEED_FULL:
      DWC3_RegWrite(USBx, DWC3_DCFG, reg |  DWC3_DSTS_FULLSPEED2);
      LL_DBGLOG2("%s = FullSpeed\n", __func__);
      break;
    case USB_DWC3_SPEED_LOW:
      DWC3_RegWrite(USBx, DWC3_DCFG, reg |  DWC3_DSTS_LOWSPEED);
      LL_DBGLOG2("%s = LowSpeed\n", __func__);
      break;
    default:
      ret = HAL_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  USB_GetDevSpeed :Return the  Dev Speed
  * @param  USBx  Selected device
  * @retval speed : device speed
  *          This parameter can be one of these values:
  *            @arg USB_DWC3_SPEED_HIGH: High speed mode
  *            @arg USB_DWC3_SPEED_FULL: Full speed mode
  *            @arg USB_DWC3_SPEED_LOW: Low speed mode
  */
uint8_t USB_GetDevSpeed(USB3_TypeDef *USBx)
{
  uint32_t reg;
  uint8_t ret;
  reg = DWC3_RegRead(USBx, DWC3_DSTS) & USB3_DSTS_CONNECTSPD;

  switch (reg)
  {
    case DWC3_DSTS_SUPERSPEED:
      ret = USB_DWC3_SPEED_SUPER;
      LL_DBGLOG2("%s = SuperSpeed\n", __func__);
      break;
    case DWC3_DSTS_HIGHSPEED:
      ret = USB_DWC3_SPEED_HIGH;
      LL_DBGLOG2("%s = HighSpeed\n", __func__);
      break;
    case DWC3_DSTS_FULLSPEED1:
      ret = USB_DWC3_SPEED_FULL_48;
      LL_DBGLOG2("%s = FullSpeed_48M\n", __func__);
      break;
    case DWC3_DSTS_FULLSPEED2:
      ret = USB_DWC3_SPEED_FULL;
      LL_DBGLOG2("%s = FullSpeed\n", __func__);
      break;
    case DWC3_DSTS_LOWSPEED:
      ret = USB_DWC3_SPEED_LOW;
      LL_DBGLOG2("%s = LowSpeed\n", __func__);
      break;
    default: /* Invalid */
      ret = USB_DWC3_SPEED_INVALID;
      LL_DBGLOG2("%s = Invalid\n", __func__);
      break;
  }

  return ret;
}

/**
  * @brief  Activate and configure an endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_ActivateEndpoint(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep)
{
  HAL_StatusTypeDef ret;
  ret = USB_ConfigureEP(USBx, ep->num, ep->is_in, ep->type, ep->maxpacket, ep->tx_fifo_num, ep->bInterval,
                        ep->phy_epnum, ep->intr_num, USB_DWC3_DEPCFG_ACTION_INIT);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* Enable EP */
  ret = USB_EnableEndpoint(USBx, ep->phy_epnum);
  if (ret != HAL_OK)
  {
    /* Return Error */
    return ret;
  }

  return HAL_OK;
}

/**
  * @brief  De-activate and de-initialize an endpoint
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_DeactivateEndpoint(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep)
{
  HAL_StatusTypeDef ret;
  LL_DBGLOG2("%s PHYEP%d %x\n", __func__, ep->phy_epnum, ep->flags);

  if (ep->is_stall)
  {
    ret = USB_EPClearStall(USBx, ep);
    if (ret != HAL_OK)
    {
      /* Return Error */
      return ret;
    }
  }

  /* Disable EP */
  return USB_DisableEndpoint(USBx, ep->phy_epnum);
}

/**
  * @brief  USB_EPStartXfer : setup and starts a transfer over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPStartXfer(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep)
{
  HAL_StatusTypeDef ret;
  USB_DWC3_EPCmd cmd;
  USB_DWC3_EPCmdParams params;
  uint8_t phy_epnum = ep->phy_epnum;

  LL_DBGLOG1("%s PHYEP%d %x\n", __func__, ep->phy_epnum, ep->flags);

  /* Wait for XferNotReady to get the uF interval to srat ISOC transfers */
  if ((ep->type == EP_TYPE_ISOC) && ((ep->flags & USB_DWC3_EP_ISOC_START_PENDING) == 0U)
      && ((ep->flags & USB_DWC3_EP_ISOC_STARTED) == 0U))
  {
    ep->flags |= USB_DWC3_EP_ISOC_START_PENDING;
    LL_DBGLOG1("INSIDE IF\n");
    return HAL_OK;
  }

  if ((ep->type == EP_TYPE_ISOC) && ((ep->flags & USB_DWC3_EP_ISOC_START_PENDING) != 0U))
  {
    ep->flags &= ~USB_DWC3_EP_ISOC_START_PENDING;
  }

  ep->trb_addr->bpl = LOWER_32_BITS(ep->dma_addr);
  ep->trb_addr->bph = UPPER_32_BITS(ep->dma_addr);
  ep->trb_addr->size = DWC3_TRB_SIZE_LENGTH(ep->xfer_len);
  ep->trb_addr->ctrl = DWC3_GetTRBCtlType(ep->trb_flag & USB_DWC3_TRBCTL_MASK); /* also initializes other bits to 0 */

  ep->trb_addr->ctrl |= ((ep->num == 0U) ? DWC3_TRB_CTRL_ISP_IMI : 0U);
  ep->trb_addr->ctrl |= DWC3_TRB_CTRL_IOC;

  if ((ep->type == EP_TYPE_ISOC) && ((ep->flags & USB_DWC3_EP_ISOC_STARTED) != 0U))
  {
    cmd = USB_DWC3_DEPCMD_UPDATETRANSFER;
  }
  else
  {
    cmd = USB_DWC3_DEPCMD_STARTTRANSFER;
  }

  if (ep->type == EP_TYPE_ISOC)
  {
    ep->trb_addr->ctrl |= DWC3_TRB_CTRL_ISP_IMI | DWC3_TRB_CTRL_CSP;

    if (cmd == USB_DWC3_DEPCMD_STARTTRANSFER)
    {
      cmd |= DWC3_DEPCMD_PARAM(ep->uframe + ((1UL << (ep->bInterval - 1U)) * 4U));

      ep->trb_addr[1].bpl = LOWER_32_BITS(ep->trb_dma_addr);
      ep->trb_addr[1].bph = UPPER_32_BITS(ep->trb_dma_addr);
      ep->trb_addr[1].ctrl |= DWC3_TRBCTL_LINK_TRB | DWC3_TRB_CTRL_HWO;
    }
    else
    {
      cmd |= DWC3_DEPCMD_PARAM((uint32_t)ep->resc_idx);
    }
  }
  else
  {
    ep->trb_addr->ctrl |= DWC3_TRB_CTRL_LST;
  }

  ep->trb_addr->ctrl |= DWC3_TRB_CTRL_HWO;

  (void)memset(&params, 0x00, sizeof(params));

  if ((cmd & USB3_DEPCMD_CMDTYP_Msk) == USB_DWC3_DEPCMD_STARTTRANSFER)
  {
    params.param0 = UPPER_32_BITS(ep->trb_dma_addr);
    params.param1 = LOWER_32_BITS(ep->trb_dma_addr);
  }

  ep->flags |= USB_DWC3_EP_REQ_QUEUED;
  if ((ep->type == EP_TYPE_ISOC) && ((cmd & USB3_DEPCMD_CMDTYP_Msk) == USB_DWC3_DEPCMD_STARTTRANSFER))
  {
    ep->flags |= USB_DWC3_EP_ISOC_STARTED;
  }

  LL_DBGLOG1("EP%d%s: trb %08lx:%08lx:%08lx:%08lx:%08lx length %ld %d\n", ep->num, ep->is_in ? "IN" : "OUT",
             (uint32_t)ep->trb_addr, (uint32_t)ep->trb_addr->bph,
             (uint32_t)ep->trb_addr->bpl, (uint32_t)ep->trb_addr->size,
             (uint32_t)ep->trb_addr->ctrl, ep->xfer_len, ep->flags);

  ret = USB_ExecuteDevEPCmd(USBx, ep->phy_epnum, cmd, &params);
  if (ret != HAL_OK)
  {
    ep->flags &= ~USB_DWC3_EP_REQ_QUEUED;
    if ((ep->type == EP_TYPE_ISOC) && ((cmd & USB3_DEPCMD_CMDTYP_Msk) == USB_DWC3_DEPCMD_STARTTRANSFER))
    {
      ep->flags &= ~USB_DWC3_EP_ISOC_STARTED;
    }
    return ret;
  }

  if ((cmd & USB3_DEPCMD_CMDTYP_Msk) == USB_DWC3_DEPCMD_STARTTRANSFER)
  {
    ep->resc_idx = (uint8_t)DWC3_DEPCMD_GET_RSC_IDX(DWC3_RegRead(USBx, DWC3_DEPCMD(phy_epnum)));
  }

  return ret;
}

/**
  * @brief  USB_EPSetStall : set a stall condition over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPSetStall(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep)
{
  USB_DWC3_EPCmdParams params;
  (void)memset(&params, 0x00, sizeof(params));
  return USB_ExecuteDevEPCmd(USBx, ep->phy_epnum, USB_DWC3_DEPCMD_SETSTALL, &params);
}


/**
  * @brief  USB_EPClearStall : Clear a stall condition over an EP
  * @param  USBx  Selected device
  * @param  ep pointer to endpoint structure
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EPClearStall(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep)
{
  USB_DWC3_EPCmdParams params;
  (void)memset(&params, 0x00, sizeof(params));
  return USB_ExecuteDevEPCmd(USBx, ep->phy_epnum, USB_DWC3_DEPCMD_CLEARSTALL, &params);
}

/**
  * @brief  USB_SetDevAddress : Stop the usb device mode
  * @param  USBx  Selected device
  * @param  address  new device address to be assigned
  *          This parameter can be a value from 0 to 255
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetDevAddress(USB3_TypeDef *USBx, uint8_t address)
{
  LL_DBGLOG1("%s: %d\n", __func__, address);
  /* set device address */
  DWC3_RegUpdateClr(USBx, DWC3_DCFG, USB3_DCFG_DEVADDR_Msk);
  DWC3_RegUpdateSet(USBx, DWC3_DCFG, DWC3_DCFG_DEVADDR((uint32_t)address));

  return HAL_OK;
}

/**
  * @brief  USB_SetTestMode : Set Test Mode for usb device mode
  * @param  USBx  Selected device
  * @param  test_mode  test mode to be set
  *          This parameter can be a value from 0 to 255
  * @retval HAL status
  */
HAL_StatusTypeDef USB_SetTestMode(USB3_TypeDef *USBx, uint8_t test_mode)
{
  LL_DBGLOG1("%s: %d\n", __func__, test_mode);
  /* set device address */
  DWC3_RegUpdateClr(USBx, DWC3_DCTL, USB3_DCTL_TSTCTL_Msk);
  DWC3_RegUpdateSet(USBx, DWC3_DCTL, (uint32_t)test_mode << USB3_DCTL_TSTCTL_Pos);

  return HAL_OK;
}

/**
  * @brief  USB_DevConnect : Connect the USB device by enabling the pull-up/pull-down
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_DevConnect(USB3_TypeDef *USBx)
{
  DWC3_RegUpdateSet(USBx, DWC3_DCTL, USB3_DCTL_RUN_STOP);

  return HAL_OK;
}

/**
  * @brief  USB_DevDisconnect : Disconnect the USB device by disabling the pull-up/pull-down
  * @param  USBx  Selected device
  * @retval HAL status
  */
HAL_StatusTypeDef  USB_DevDisconnect(USB3_TypeDef *USBx)
{
  uint32_t timeout = 500; /* usec */
  DWC3_RegUpdateClr(USBx, DWC3_DCTL, USB3_DCTL_RUN_STOP);
  do
  {
    if ((DWC3_RegRead(USBx, DWC3_DSTS) & USB3_DSTS_DEVCTRLHLT) != 0U) /*"Halt Complete"*/
    {
      break;
    }

    /* Can be called from interrupt context hence cannot wait for Tick */
    USB_Delay(1); /*Need 1us delay*/
    timeout--;
    if (timeout == 0U)
      /* "Reset Timed Out" */
    {
      return HAL_TIMEOUT;
    }
  } while (true);

  return HAL_OK;
}

/**
  * @brief  Returns USB core mode
  * @param  USBx  Selected device
  * @retval return core mode : Host or Device
  *          This parameter can be one of these values:
  *           0 : Host
  *           1 : Device
  */
USB_DWC3_ModeTypeDef USB_GetMode(USB3_TypeDef *USBx)
{
  uint32_t reg;
  USB_DWC3_ModeTypeDef ret;
  reg = (DWC3_RegRead(USBx, DWC3_GCTL) & USB3_GCTL_PRTCAPDIR_Msk) >> USB3_GCTL_PRTCAPDIR_Pos;

  switch (reg)
  {
    case DWC3_GCTL_PRTCAP_DEVICE:
      ret = USB_DWC3_DEVICE_MODE;
      break;
    case DWC3_GCTL_PRTCAP_HOST:
      ret = USB_DWC3_HOST_MODE;
      break;
    case DWC3_GCTL_PRTCAP_OTG:
      ret = USB_DWC3_DRD_MODE;
      break;
    default:  /* Invalid */
      ret = USB_DWC3_INVALID_MODE;
      LL_DBGLOG1("Error : %s: %d\n", __func__, __LINE__);
      break;
  }

  return ret;
}

/**
  * @brief  Prepare the EP0 to start the first control setup
  * @param  USBx  Selected device
  * @param  dma USB dma enabled or disabled
  *          This parameter can be one of these values:
  *           0 : DMA feature not used
  *           1 : DMA feature used
  * @param  psetup  pointer to setup packet
  * @retval HAL status
  */
HAL_StatusTypeDef USB_EP0_OutStart(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep0, USB_DWC3_DmaBusAddr setup_buf_dma_addr)
{
  ep0->dma_addr = setup_buf_dma_addr;
  ep0->xfer_len = 8;
  ep0->trb_flag = USB_DWC3_TRBCTL_CONTROL_SETUP;
  return USB_EPStartXfer(USBx, ep0);
}

HAL_StatusTypeDef USB_ExecuteDevEPCmd(USB3_TypeDef *USBx, uint8_t phy_epnum, USB_DWC3_EPCmd cmd,
                                      USB_DWC3_EPCmdParams *params)
{
  uint32_t reg;
  uint32_t timeout = 500; /* usec */
  LL_DBGLOG1("PHYEP%d: cmd '%s' %08lx params %08lx %08lx %08lx\n", phy_epnum, DWC3_GetEPCmdString(cmd),
             (uint32_t)cmd, (uint32_t)params->param0, (uint32_t)params->param1, (uint32_t)params->param2);

  DWC3_RegWrite(USBx, DWC3_DEPCMDPAR0(phy_epnum), params->param0);
  DWC3_RegWrite(USBx, DWC3_DEPCMDPAR1(phy_epnum), params->param1);
  DWC3_RegWrite(USBx, DWC3_DEPCMDPAR2(phy_epnum), params->param2);
  DWC3_RegWrite(USBx, DWC3_DEPCMD(phy_epnum), cmd | USB3_DEPCMD_CMDACT);
  do
  {
    reg = DWC3_RegRead(USBx, DWC3_DEPCMD(phy_epnum));
    if ((reg & USB3_DEPCMD_CMDACT) == 0U)   /*"Command Complete"*/
    {
      LL_DBGLOG1("Command Complete --> %ld PHYEP%d %lx\n", DWC3_DEPCMD_STATUS(reg), phy_epnum, reg);
      if (DWC3_DEPCMD_STATUS(reg) != 0U)
      {
        /* Return Error */
        return HAL_ERROR;
      }
      return HAL_OK;
    }

    USB_Delay(1); /*Need 1us delay*/
    timeout--;
    if (timeout == 0U)
    {
      LL_DBGLOG1("TIMEOUT Command Complete --> %ld PHYEP%d %lx\n", DWC3_DEPCMD_STATUS(reg), phy_epnum, reg);
      /* "Command Timed Out" */
      return HAL_TIMEOUT;
    }
  } while (true);
}

HAL_StatusTypeDef USB_ConfigureEP(USB3_TypeDef *USBx, USB_DWC3_EPNum epnum, bool is_in,
                                  uint8_t type, uint32_t max_packet, uint8_t tx_fifo, uint16_t bInterval,
                                  uint8_t phy_epnum, uint8_t intr_num, uint8_t action)
{
  USB_DWC3_EPCmdParams params;

  (void)memset(&params, 0x00, sizeof(params));
  params.param0 = DWC3_DEPCFG_EP_TYPE(type) | DWC3_DEPCFG_MAX_PACKET_SIZE(max_packet);
  /* Burst size is only needed in SuperSpeed mode */
  params.param0 |= DWC3_GetEPCFGAction(action);
  params.param1 = DWC3_DEPCFG_XFER_COMPLETE_EN | DWC3_DEPCFG_XFER_NOT_READY_EN;
  if (type == EP_TYPE_ISOC)
  {
    params.param1 |= DWC3_DEPCFG_XFER_IN_PROGRESS_EN;
  }

  params.param1 |= DWC3_DEPCFG_EP_NUMBER(((uint32_t)epnum << 1) + (is_in ? 1UL : 0UL));

  params.param1 |= DWC3_DEPCFG_EP_INTR_NUM(intr_num);

  if (is_in)
  {
    params.param0 |= DWC3_DEPCFG_FIFO_NUMBER(tx_fifo);
  }

  if (bInterval != 0U)
  {
    params.param1 |= DWC3_DEPCFG_BINTERVAL_M1(bInterval - 1UL);
  }

  return USB_ExecuteDevEPCmd(USBx, phy_epnum, USB_DWC3_DEPCMD_SETEPCONFIG, &params);
}

void USB_EnableEventInt(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num)
{
  DWC3_RegUpdateClr(USBx, DWC3_GEVNTSIZ(intr_num), USB3_GEVNTSIZ_EVNTINTRPTMASK_Msk);
}

void USB_DisableEventInt(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num)
{
  DWC3_RegUpdateSet(USBx, DWC3_GEVNTSIZ(intr_num), USB3_GEVNTSIZ_EVNTINTRPTMASK_Msk);
}

HAL_StatusTypeDef USB_EPStopXfer(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep)
{
  HAL_StatusTypeDef ret;
  USB_DWC3_EPCmd cmd;
  USB_DWC3_EPCmdParams params;
  LL_DBGLOG2("%s PHYEP%d %x\n", __func__, ep->phy_epnum, ep->flags);

  /*Reset ISOC flags*/
  if (ep->type == EP_TYPE_ISOC)
  {
    ep->flags &= ~(USB_DWC3_EP_ISOC_START_PENDING | USB_DWC3_EP_ISOC_STARTED);
  }

  if ((ep->flags & USB_DWC3_EP_REQ_QUEUED) == 0U)
  {
    /* Return Error */
    return HAL_ERROR;
  }

  (void)memset(&params, 0x00, sizeof(params));
  cmd = USB_DWC3_DEPCMD_ENDTRANSFER | USB3_DEPCMD_HIPRI_FORCERM | USB3_DEPCMD_CMDIOC
        | DWC3_DEPCMD_PARAM((uint32_t)ep->resc_idx);

  ret = USB_ExecuteDevEPCmd(USBx, ep->phy_epnum, cmd, &params);
  USB_Delay(100); /*Need Delay 100us as mentioned in Linux Driver*/

  ep->xfer_count = ep->xfer_len - (ep->trb_addr->size & DWC3_TRB_SIZE_MASK);
  ep->flags &= ~USB_DWC3_EP_REQ_QUEUED;

  return ret;
}

void USB_AckEventCount(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num, uint32_t evt_count)
{
  DWC3_RegWrite(USBx, DWC3_GEVNTCOUNT(intr_num), evt_count);
}

uint32_t USB_ReadInterruptCount(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num)
{
  return DWC3_RegRead(USBx, DWC3_GEVNTCOUNT(intr_num)) & DWC3_GEVNTCOUNT_MASK;
}

HAL_StatusTypeDef USB_ExecuteDevCmd(USB3_TypeDef *USBx, USB_DWC3_Cmd cmd, USB_DWC3_CmdParams *params)
{
  uint32_t reg;
  uint32_t timeout = 500; /* usec */

  DWC3_RegWrite(USBx, DWC3_DGCMDPAR, *params);
  DWC3_RegWrite(USBx, DWC3_DGCMD, cmd | USB3_DGCMD_CMDACT);
  do
  {
    reg = DWC3_RegRead(USBx, DWC3_DGCMD);
    if ((reg & USB3_DGCMD_CMDACT) == 0U)   /*"Command Complete"*/
    {
      if (DWC3_DGCMD_STATUS(reg) != 0U)
      {
        /* Return Error */
        return HAL_ERROR;
      }
      return HAL_OK;
    }

    /* Can be called from interrupt context hence cannot wait for Tick */
    USB_Delay(1); /* Need 1us delay*/
    timeout--;
    if (timeout == 0U)
    {
      LL_DBGLOG1("TIMEOUT Command Complete --> %ld %lx\n", DWC3_DGCMD_STATUS(reg), reg);
      /* "Command Timed Out" */
      return HAL_TIMEOUT;
    }
  } while (true);
}

HAL_StatusTypeDef USB_EnableEndpoint(USB3_TypeDef *USBx, uint8_t phy_epnum)
{
  if ((DWC3_RegRead(USBx, DWC3_DALEPENA) & DWC3_DALEPENA_EP(phy_epnum)) != 0U)
  {
    /* Return Error */
    return HAL_ERROR;
  }
  /* Enable EP */
  DWC3_RegUpdateSet(USBx, DWC3_DALEPENA, DWC3_DALEPENA_EP(phy_epnum));
  return HAL_OK;
}

HAL_StatusTypeDef USB_DisableEndpoint(USB3_TypeDef *USBx, uint8_t phy_epnum)
{
  /* Disable EP */
  DWC3_RegUpdateClr(USBx, DWC3_DALEPENA, DWC3_DALEPENA_EP(phy_epnum));
  return HAL_OK;
}

bool USB_IsEndpointEnabled(USB3_TypeDef *USBx, uint8_t phy_epnum)
{
  if ((DWC3_RegRead(USBx, DWC3_DALEPENA) & DWC3_DALEPENA_EP(phy_epnum)) != 0U)
  {
    return true;
  }

  return false;
}


HAL_StatusTypeDef USB_ActivateRemoteWakeup(USB3_TypeDef *USBx)
{
#ifdef USB3_SW_REMWAKEUP_USED
  HAL_StatusTypeDef ret;
  uint8_t link_state;
  uint32_t reg;
  uint32_t timeout = 100000; /* usec */

  link_state = (uint8_t)DWC3_DSTS_USBLNKST(DWC3_RegRead(USBx, DWC3_DSTS));
  if ((link_state != DWC3_LINK_STATE_EARLY_SUS) &&
      (link_state != DWC3_LINK_STATE_L1) &&
      (link_state != DWC3_LINK_STATE_L2))
  {
    LL_DBGLOG2("Can't wakeup from link state %d\n", link_state);
    return HAL_ERROR;
  }

  ret = DWC3_SetLinkState(USBx, DWC3_DCTL_ULSTCHNG_RECOVERY);
  if (ret != HAL_OK)
  {
    LL_DBGLOG("Failed to put link in Recovery\n");
    return HAL_ERROR;
  }

  do
  {
    reg = DWC3_RegRead(USBx, DWC3_DSTS);
    if (DWC3_DSTS_USBLNKST(reg) == DWC3_LINK_STATE_ON)
    {
      LL_DBGLOG2("Wake-up Done\n");
      return HAL_OK;
    }

    /* Can be called from interrupt context hence cannot wait for Tick */
    USB_Delay(5);
    timeout -= 5;
    if (timeout == 0U)
    {
      LL_DBGLOG("Failed to send remote wakeup\n");
      /* "Command Timed Out" */
      return HAL_TIMEOUT;
    }
  } while (true);
#else
  DWC3_RegUpdateSet(USBx, DWC3_GUCTL1, USB3_GUCTL1_DEV_L1_EXIT_BY_HW);

  return HAL_OK;
#endif /*USB3_SW_REMWAKEUP_USED*/
}

bool USB_IsEndpointEvent(uint32_t event)
{
  return ((event & DWC3_EVT_TYPE_MASK) == (DWC3_EVT_TYPE_EP << DWC3_EVT_TYPE_BITPOS));
}

bool USB_IsDeviceEvent(uint32_t event)
{
  return ((event & DWC3_EVT_TYPE_MASK) == (DWC3_EVT_TYPE_DEVSPEC << DWC3_EVT_TYPE_BITPOS));
}

uint8_t USB_ReadEndpointEventType(uint32_t event)
{
  uint8_t ret;

  switch ((event & DWC3_EVT_DEPEVT_TYPE_MASK) >> DWC3_EVT_DEPEVT_TYPE_BITPOS)
  {
    case DWC3_DEPEVT_XFERCOMPLETE:
      ret =  USB_DWC3_DEPEVT_XFERCOMPLETE;
      break;
    case DWC3_DEPEVT_XFERINPROGRESS:
      ret =  USB_DWC3_DEPEVT_XFERINPROGRESS;
      break;
    case DWC3_DEPEVT_XFERNOTREADY:
      ret =  USB_DWC3_DEPEVT_XFERNOTREADY;
      break;
    case DWC3_DEPEVT_RXTXFIFOEVT:
      ret =  USB_DWC3_DEPEVT_RXTXFIFOEVT;
      break;
    case DWC3_DEPEVT_STREAMEVT:
      ret =  USB_DWC3_DEPEVT_STREAMEVT;
      break;
    case DWC3_DEPEVT_EPCMDCMPLT:
      ret =  USB_DWC3_DEPEVT_EPCMDCMPLT;
      break;
    default:
      ret = 0;
      break;
  }

  return ret;
}

uint8_t USB_ReadEndpointEventEpNum(uint32_t event)
{
  return (uint8_t)((event & DWC3_EVT_DEPEVT_EPNUM_MASK) >> DWC3_EVT_DEPEVT_EPNUM_BITPOS);
}
\
uint16_t USB_ReadEndpointEventParam(uint32_t event)
{
  return (uint16_t)((event & DWC3_EVT_DEPEVT_PARAM_MASK) >> DWC3_EVT_DEPEVT_PARAM_BITPOS);
}

uint8_t USB_ReadDeviceEventLinkState(uint32_t event)
{
  return (uint8_t)((event & DWC3_EVT_DEVEVT_LNKSTS_MASK) >> DWC3_EVT_DEVEVT_LNKSTS_BITPOS);
}

const char *USB_GetLinkStateString(uint8_t state)
{
  const char *ret;

  switch (state)
  {
    case DWC3_LINK_STATE_ON:
      ret = "ON";
      break;
    case DWC3_LINK_STATE_L1:
      ret = "L1";
      break;
    case DWC3_LINK_STATE_L2:
      ret = "L2";
      break;
    case DWC3_LINK_STATE_DIS:
      ret = "Disconnect";
      break;
    case DWC3_LINK_STATE_EARLY_SUS:
      ret = "Early Suspend";
      break;
    case DWC3_LINK_STATE_RESET:
      ret = "Reset";
      break;
    case DWC3_LINK_STATE_RESUME:
      ret = "Resume";
      break;
    default:
      ret = "UNKNOWN state";
      break;
  }

  return ret;
}

uint32_t USB_GetTRBLengthEP(const USB_DWC3_EPTypeDef *ep)
{
  return DWC3_TRB_SIZE_LENGTH(ep->trb_addr->size);
}

uint32_t USB_GetTRBStatusEP(const USB_DWC3_EPTypeDef *ep)
{
  return DWC3_TRB_SIZE_TRBSTS(ep->trb_addr->size);
}

uint8_t USB_ReadEndpointEventStatus(uint32_t event)
{
  uint8_t ret;

  switch ((event & DWC3_EVT_DEPEVT_STATUS_MASK) >> DWC3_EVT_DEPEVT_STATUS_BITPOS)
  {
    case DWC3_EVT_DEPEVT_STATUS_CONTROL_DATA:
      ret = USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_DATA;
      break;
    case DWC3_EVT_DEPEVT_STATUS_CONTROL_STATUS:
      ret = USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_STATUS;
      break;
    default:
      ret = 0;
      break;
  }

  return ret;
}

uint8_t USB_ReadDeviceEventType(uint32_t event)
{
  uint8_t ret;

  switch ((event & DWC3_EVT_DEVEVT_TYPE_MASK) >> DWC3_EVT_DEVEVT_TYPE_BITPOS)
  {
    case DWC3_DEVICE_EVENT_DISCONNECT:
      ret = USB_DWC3_DEVICE_EVENT_DISCONNECT;
      break;
    case DWC3_DEVICE_EVENT_RESET:
      ret = USB_DWC3_DEVICE_EVENT_RESET;
      break;
    case DWC3_DEVICE_EVENT_CONNECT_DONE:
      ret = USB_DWC3_DEVICE_EVENT_CONNECT_DONE;
      break;
    case DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
      ret = USB_DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE;
      break;
    case DWC3_DEVICE_EVENT_WAKEUP:
      ret = USB_DWC3_DEVICE_EVENT_WAKEUP;
      break;
    case DWC3_DEVICE_EVENT_HIBER_REQ:
      ret = USB_DWC3_DEVICE_EVENT_HIBER_REQ;
      break;
    case DWC3_DEVICE_EVENT_EOPF:
      ret = USB_DWC3_DEVICE_EVENT_EOPF;
      break;
    case DWC3_DEVICE_EVENT_SOF:
      ret = USB_DWC3_DEVICE_EVENT_SOF;
      break;
    case DWC3_DEVICE_EVENT_ERRATIC_ERROR:
      ret = USB_DWC3_DEVICE_EVENT_ERRATIC_ERROR;
      break;
    case DWC3_DEVICE_EVENT_CMD_CMPL:
      ret = USB_DWC3_DEVICE_EVENT_CMD_CMPL;
      break;
    case DWC3_DEVICE_EVENT_OVERFLOW:
      ret = USB_DWC3_DEVICE_EVENT_OVERFLOW;
      break;
    case USB_DWC3_DEVICE_EVENT_L1WAKEUP:
      ret = USB_DWC3_DEVICE_EVENT_OVERFLOW;
      break;
    default:
      ret = 0;
      break;
  }

  return ret;
}

#endif /* defined (HAL_PCD_MODULE_ENABLED) || defined (HAL_HCD_MODULE_ENABLED) */

/**
  * @}
  */

