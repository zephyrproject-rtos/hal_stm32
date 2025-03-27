/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_usb_drd.h
  * @author  MCD Application Team
  * @brief   Header file of USB Low Layer HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_LL_USB_DRD_H
#define STM32MP2xx_LL_USB_DRD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup USB_LL
  * @{
  */

/* Exported macro ------------------------------------------------------------*/
#define USB3_HS_MAX_PACKET_SIZE     512U
#define USB3_FS_MAX_PACKET_SIZE     64U
#ifdef USE_USB_HS
#define USB3_MAX_PACKET_SIZE        USB3_HS_MAX_PACKET_SIZE
#else
#define USB3_MAX_PACKET_SIZE        USB3_FS_MAX_PACKET_SIZE
#endif /*USE_USB_HS*/

/* USB_DWC3_EPTypeDef->trb_flag */
#define USB_DWC3_TRBCTL_NORMAL            1U
#define USB_DWC3_TRBCTL_CONTROL_SETUP     2U
#define USB_DWC3_TRBCTL_CONTROL_STATUS2   3U
#define USB_DWC3_TRBCTL_CONTROL_STATUS3   4U
#define USB_DWC3_TRBCTL_CONTROL_DATA      5U
#define USB_DWC3_TRBCTL_ISOCHRONOUS_FIRST 6U
#define USB_DWC3_TRBCTL_ISOCHRONOUS       7U
#define USB_DWC3_TRBCTL_LINK_TRB          8U
#define USB_DWC3_TRBCTL_MASK              0x3fUL

/* USB_DWC3_EPTypeDef->flags */
#define USB_DWC3_EP_REQ_QUEUED          (1U << 0)
#define USB_DWC3_EP_ISOC_START_PENDING  (1U << 1)
#define USB_DWC3_EP_ISOC_STARTED        (1U << 2)

/**
  * @brief DWC3 Specific Configurable macros
  */
#define USB_DWC3_INT_INUSE          1U
#define USB_DWC3_EVENT_BUFFER_SIZE  4096U
#define USB_DWC3_NUM_IN_EP          16U
#define USB_DWC3_NUM_OUT_EP         16U

/**
  * @brief USB Speed
  */
#define USB_DWC3_SPEED_SUPER                    0U
#define USB_DWC3_SPEED_HIGH                     1U
#define USB_DWC3_SPEED_FULL_48                  2U
#define USB_DWC3_SPEED_FULL                     3U
#define USB_DWC3_SPEED_LOW                      4U
#define USB_DWC3_SPEED_INVALID                  15U

/**
  * @brief USB PHY Type
  */
/* USB2 PHY Mask 0xf */
#define USBPHY_ULPI           1U
#define USBPHY_UTMI           2U
#define USBPHY_EMBEDDED_USB2  8U
#define USB2PHY_MASK          15U
/* USB3 PHY Mask (0xf << 4) */
#define USBPHY_PIPE3          16U
#define USBPHY_EMBEDDED_USB3  128U
#define USB3PHY_MASK          (15U << 4)

/**
  * @brief USB EP Type
  */
#define EP_TYPE_CTRL                           0U
#define EP_TYPE_ISOC                           1U
#define EP_TYPE_BULK                           2U
#define EP_TYPE_INTR                           3U
#define EP_TYPE_MSK                            3U

/* Event Size */
#define USB_DWC3_EVENT_SIZE   4U

/* USB_ExecuteDevEPCmd::USB_DWC3_EPCmd */
#define USB_DWC3_DEPCMD_DEPSTARTCFG     (0x09UL << USB3_DEPCMD_CMDTYP_Pos)
#define USB_DWC3_DEPCMD_ENDTRANSFER     (0x08UL << USB3_DEPCMD_CMDTYP_Pos)
#define USB_DWC3_DEPCMD_UPDATETRANSFER  (0x07UL << USB3_DEPCMD_CMDTYP_Pos)
#define USB_DWC3_DEPCMD_STARTTRANSFER   (0x06UL << USB3_DEPCMD_CMDTYP_Pos)
#define USB_DWC3_DEPCMD_CLEARSTALL      (0x05UL << USB3_DEPCMD_CMDTYP_Pos)
#define USB_DWC3_DEPCMD_SETSTALL        (0x04UL << USB3_DEPCMD_CMDTYP_Pos)
/* This applies for core versions 1.94a and later */
#define USB_DWC3_DEPCMD_GETEPSTATE      (0x03UL << USB3_DEPCMD_CMDTYP_Pos)
#define USB_DWC3_DEPCMD_SETTRANSFRESOURCE (0x02UL << USB3_DEPCMD_CMDTYP_Pos)
#define USB_DWC3_DEPCMD_SETEPCONFIG     (0x01UL << USB3_DEPCMD_CMDTYP_Pos)

/* USB_ConfigureEP::action */
#define USB_DWC3_DEPCFG_ACTION_INIT     0U
#define USB_DWC3_DEPCFG_ACTION_RESTORE  1U
#define USB_DWC3_DEPCFG_ACTION_MODIFY   2U

/* USB_ReadEndpointEventType @return EPEventType */
#define USB_DWC3_DEPEVT_XFERCOMPLETE    0x01U
#define USB_DWC3_DEPEVT_XFERINPROGRESS  0x02U
#define USB_DWC3_DEPEVT_XFERNOTREADY    0x03U
#define USB_DWC3_DEPEVT_RXTXFIFOEVT     0x04U
#define USB_DWC3_DEPEVT_STREAMEVT       0x06U
#define USB_DWC3_DEPEVT_EPCMDCMPLT      0x07U

/* USB_ReadEndpointEventStatus @return EPEventStatus */
#define USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_DATA   0x01U
#define USB_DWC3_DEPEVT_XFERNOTREADY_STATUS_CTRL_STATUS 0x02U

/* USB_ReadDeviceEventType @return DevEventType */
#define USB_DWC3_DEVICE_EVENT_DISCONNECT          0U
#define USB_DWC3_DEVICE_EVENT_RESET               1U
#define USB_DWC3_DEVICE_EVENT_CONNECT_DONE        2U
#define USB_DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE  3U
#define USB_DWC3_DEVICE_EVENT_WAKEUP              4U
#define USB_DWC3_DEVICE_EVENT_HIBER_REQ           5U
#define USB_DWC3_DEVICE_EVENT_EOPF                6U
#define USB_DWC3_DEVICE_EVENT_SOF                 7U
#define USB_DWC3_DEVICE_EVENT_L1SUSPEND           8U
#define USB_DWC3_DEVICE_EVENT_ERRATIC_ERROR       9U
#define USB_DWC3_DEVICE_EVENT_CMD_CMPL            10U
#define USB_DWC3_DEVICE_EVENT_OVERFLOW            11U
#define USB_DWC3_DEVICE_EVENT_L1WAKEUP            14U

#define USB_DWC3_TRBSTS_OK          0U
#define USB_DWC3_TRBSTS_MISSED_ISOC   1U
#define USB_DWC3_TRBSTS_SETUP_PENDING 2U
#define USB_DWC3_TRBSTS_XFER_IN_PROG  4U


/* Exported types ------------------------------------------------------------*/

/**
  * @brief  USB Mode definition
  */
typedef enum
{
  USB_DWC3_DEVICE_MODE  = 0U,
  USB_DWC3_HOST_MODE    = 1U,
  USB_DWC3_DRD_MODE     = 2U,
  USB_DWC3_INVALID_MODE = 0xFU

} USB_DWC3_ModeTypeDef;

/**
  * @brief  USB LL Initialization Structure definition
  */
typedef struct
{
  uint8_t speed;                /*!< USB Core speed.
                                      This parameter can be any value of @ref USB_Core_Speed_                */

  uint32_t ep0_mps;              /*!< Set the Endpoint 0 Max Packet size.
                                      This parameter can be any value of @ref USB_EP0_MPS_                   */

  uint32_t phy_itface;           /*!< Select the used PHY interface.
                                      This parameter can be any value of @ref USB_Core_PHY_                  */

  bool Sof_enable;           /*!< Enable or disable the event of the SOF signal.                        */

  /* To be used later, in further features */
  bool low_power_enable;     /*!< Enable or disable the low power mode.                                  */

  bool lpm_enable;           /*!< Enable or disable Link Power Management.                               */

  bool battery_charging_enable; /*!< Enable or disable Battery charging.                                 */

  bool vbus_sensing_enable;  /*!< Enable or disable the VBUS Sensing feature.                            */

  bool use_dedicated_ep1;    /*!< Enable or disable the use of the dedicated EP1 interrupt.              */

  bool use_external_vbus;    /*!< Enable or disable the use of the external VBUS.                        */
  /* To be used later, in further features */

} USB_DWC3_CfgTypeDef;

typedef struct
{
  uint32_t    bpl;      /*!< Buffer Pointer Low Address */

  uint32_t    bph;      /*!< Buffer Pointer High Address */

  uint32_t    size;     /*!< Buffer Size */

  uint32_t    ctrl;     /*!< Control and Status field */

} __packed USB_DWC3_Trb __attribute__((aligned(16)));

typedef uint32_t USB_DWC3_DmaBusAddr;

typedef uint8_t USB_DWC3_INTNum;
typedef uint8_t USB_DWC3_EPNum;

typedef struct
{
  uint8_t   num;            /*!< Endpoint number
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15    */

  bool   is_in;          /*!< Endpoint direction
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1     */

  bool   is_stall;       /*!< Endpoint stall condition
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1     */

  uint8_t   type;           /*!< Endpoint type
                                 This parameter can be any value of @ref USB_EP_Type_                     */

  USB_DWC3_Trb  trb[2];   /*!< Trb descriptor for this endpoint, second descriptor added for link (used in isoc) */

  USB_DWC3_Trb *trb_addr; /*!< Trb descriptor coherent address                                          */

  uint32_t  trb_dma_addr;    /*!< 32 bits aligned trb bus address                                         */

  uint8_t trb_flag;     /*! TRB Control Flag                                                      */

  uint8_t flags;      /*!< Endpoint state flags condition                                           */

  uint8_t phy_epnum;    /*!< physical EP number 0 - 31                                                */

  USB_DWC3_INTNum intr_num; /*!< Interrupt number to get events for this EP                               */

  uint16_t  bInterval;       /*!< 2 ^ polling interval                                                    */

  uint16_t  uframe;     /*!< last micro frame number, used for isoc transfers                         */

  uint8_t bounce_buf[USB3_MAX_PACKET_SIZE]; /*!< to be used for receiving packet < EP-Max-Packet-Size    */

  uint8_t  tx_fifo_num;    /*!< Transmission FIFO number
                                 This parameter must be a number between Min_Data = 1 and Max_Data = 15   */

  uint32_t  maxpacket;      /*!< Endpoint Max packet size
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 64KB */

  uint8_t   resc_idx;       /*!< Resource index                                                           */

  uint8_t   *xfer_buff;     /*!< Pointer to transfer buffer                                               */

  uint32_t  dma_addr;       /*!< 32 bits aligned transfer buffer address                                  */

  uint32_t  xfer_len;       /*!< Current transfer length                                                  */

  uint32_t  xfer_count;     /*!< Partial transfer length in case of multi packet transfer                 */

  uint8_t   *xfer_dest_buff;/*!< Pointer to destination buffer, used for receive case, where bounce_buf is used  */

  uint32_t  xfer_dest_len;  /*!< length of destination buffer, used for receive case, where bounce_buf is used   */

} USB_DWC3_EPTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup PCD_Exported_Constants PCD Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/**
  * @}
  */
/* Exported typedef ------------------------------------------------------------*/

/**
  * @brief DWC3 Specific typedef
  */
typedef uint32_t USB_DWC3_Cmd;
typedef uint32_t USB_DWC3_CmdParams;

typedef uint32_t USB_DWC3_EPCmd;
typedef struct
{
  uint32_t  param2;
  uint32_t  param1;
  uint32_t  param0;
} USB_DWC3_EPCmdParams;

/* Exported functions --------------------------------------------------------*/
HAL_StatusTypeDef USB_CoreInit(USB3_TypeDef *USBx, USB_DWC3_CfgTypeDef cfg);
HAL_StatusTypeDef USB_CoreUnInit(const USB3_TypeDef *USBx);
HAL_StatusTypeDef USB_DevInit(USB3_TypeDef *USBx, USB_DWC3_CfgTypeDef cfg,
                              USB_DWC3_DmaBusAddr evt_buf_dma_addr[], USB_DWC3_EPTypeDef *ep0,
                              USB_DWC3_DmaBusAddr setup_buf_dma_addr, USB_DWC3_INTNum intr_dev);
HAL_StatusTypeDef USB_SetCurrentMode(USB3_TypeDef *USBx, USB_DWC3_ModeTypeDef mode);
HAL_StatusTypeDef USB_SetDevSpeed(USB3_TypeDef *USBx, uint8_t speed);
HAL_StatusTypeDef USB_ActivateEndpoint(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep);
HAL_StatusTypeDef USB_DeactivateEndpoint(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPStartXfer(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPStopXfer(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPSetStall(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep);
HAL_StatusTypeDef USB_EPClearStall(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep);
HAL_StatusTypeDef USB_SetDevAddress(USB3_TypeDef *USBx, uint8_t address);
HAL_StatusTypeDef USB_SetTestMode(USB3_TypeDef *USBx, uint8_t test_mode);
HAL_StatusTypeDef USB_DevConnect(USB3_TypeDef *USBx);
HAL_StatusTypeDef USB_DevDisconnect(USB3_TypeDef *USBx);
HAL_StatusTypeDef USB_EP0_OutStart(USB3_TypeDef *USBx, USB_DWC3_EPTypeDef *ep0, USB_DWC3_DmaBusAddr setup_buf_dma_addr);
uint8_t           USB_GetDevSpeed(USB3_TypeDef *USBx);
USB_DWC3_ModeTypeDef  USB_GetMode(USB3_TypeDef *USBx);

void USB_AckEventCount(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num, uint32_t evt_count);
uint32_t USB_ReadInterruptCount(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num);
HAL_StatusTypeDef USB_ExecuteDevCmd(USB3_TypeDef *USBx, USB_DWC3_Cmd cmd, USB_DWC3_CmdParams *params);

HAL_StatusTypeDef USB_ExecuteDevEPCmd(USB3_TypeDef *USBx, uint8_t phy_epnum, USB_DWC3_EPCmd cmd,
                                      USB_DWC3_EPCmdParams *params);
HAL_StatusTypeDef USB_ActivateRemoteWakeup(USB3_TypeDef *USBx);

HAL_StatusTypeDef USB_ConfigureEP(USB3_TypeDef *USBx, USB_DWC3_EPNum epnum, bool is_in,
                                  uint8_t type, uint32_t max_packet, uint8_t tx_fifo, uint16_t bInterval,
                                  uint8_t phy_epnum, uint8_t intr_num, uint8_t action);
void USB_EnableEventInt(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num);
void USB_DisableEventInt(USB3_TypeDef *USBx, USB_DWC3_INTNum intr_num);
HAL_StatusTypeDef USB_EnableEndpoint(USB3_TypeDef *USBx, uint8_t phy_epnum);
HAL_StatusTypeDef USB_DisableEndpoint(USB3_TypeDef *USBx, uint8_t phy_epnum);
bool USB_IsEndpointEnabled(USB3_TypeDef *USBx, uint8_t phy_epnum);
bool USB_IsEndpointEvent(uint32_t event);
bool USB_IsDeviceEvent(uint32_t event);

uint8_t USB_ReadEndpointEventType(uint32_t event);
uint8_t USB_ReadEndpointEventEpNum(uint32_t event);
uint16_t USB_ReadEndpointEventParam(uint32_t event);
uint32_t USB_GetTRBLengthEP(const USB_DWC3_EPTypeDef *ep);
uint32_t USB_GetTRBStatusEP(const USB_DWC3_EPTypeDef *ep);

uint8_t USB_ReadEndpointEventStatus(uint32_t event);

uint8_t USB_ReadDeviceEventType(uint32_t event);

uint8_t USB_ReadDeviceEventLinkState(uint32_t event);
const char *USB_GetLinkStateString(uint8_t state);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* STM32MP2xx_LL_USB_DRD_H */
