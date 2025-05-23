/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_pcd_drd.h
  * @author  MCD Application Team
  * @brief   Header file of PCD HAL module.
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
#ifndef STM32MP2xx_HAL_PCD_DRD_H
#define STM32MP2xx_HAL_PCD_DRD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_ll_usb.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup PCD
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PCD_Exported_Types PCD Exported Types
  * @{
  */

/**
  * @brief  PCD State structure definition
  */
typedef enum
{
  HAL_PCD_STATE_RESET   = 0x00U,
  HAL_PCD_STATE_READY   = 0x01U,
  HAL_PCD_STATE_ERROR   = 0x02U,
  HAL_PCD_STATE_BUSY    = 0x03U,
  HAL_PCD_STATE_TIMEOUT = 0x04U
} PCD_StateTypeDef;

typedef enum
{
  HAL_PCD_EP0_SETUP_COMPLETED = 0x00U,
  HAL_PCD_EP0_SETUP_QUEUED  = 0x01U
} PCD_EP0StateTypeDef;


typedef USB3_TypeDef    PCD_TypeDef;
typedef USB_DWC3_CfgTypeDef   PCD_InitTypeDef;
typedef USB_DWC3_EPTypeDef    PCD_EPTypeDef;
typedef USB_DWC3_DmaBusAddr   PCD_DmaAddrDef;

typedef struct
{
  uint8_t       EvtBufferArea[USB_DWC3_EVENT_BUFFER_SIZE];  /* Event Buffer area */
} PCD_INTBufferAreaDef_t __attribute__((aligned(USB_DWC3_EVENT_BUFFER_SIZE)));   /* Aligned to make EvtBuffer start
                                                                                address evtbuffer-size aligned */

typedef struct
{
  PCD_INTBufferAreaDef_t  EvtBuffer[USB_DWC3_INT_INUSE];  /* Event Buffer area */
  uint8_t      *EvtBuffer_addr[USB_DWC3_INT_INUSE]; /* Event Buffer coherent addr */
  PCD_DmaAddrDef    EvtBuffer_dma_addr[USB_DWC3_INT_INUSE]; /* Event Buffer dma addr */
  uint32_t      EvtBufferPos[USB_DWC3_INT_INUSE];   /*!< Read Position inside the Event Buffer */
} PCD_INTBuffersDef_t;

/**
  * @brief  PCD Handle Structure definition
  */
typedef struct
{
  /* Kept at top to avoid struct size wastage since EvtBufferArea needs to be USB_DWC3_EVENT_BUFFER_SIZE aligned */
  PCD_INTBuffersDef_t IntBuffers;

  PCD_TypeDef     *Instance;   /*!< Register base address              */
  PCD_InitTypeDef   Init;       /*!< PCD required parameters            */
  PCD_EPTypeDef   IN_ep[USB_DWC3_NUM_IN_EP];  /*!< IN endpoint parameters             */
  PCD_EPTypeDef   OUT_ep[USB_DWC3_NUM_OUT_EP]; /*!< OUT endpoint parameters            */

  HAL_LockTypeDef   Lock;       /*!< PCD peripheral status              */
  PCD_StateTypeDef  State;      /*!< PCD communication state            */
  uint8_t       Setup[12];  /*!< Setup packet buffer                */
  uint8_t       *Setup_addr;  /*!< Setup packet coherent address    */
  PCD_DmaAddrDef    Setup_dma_addr;  /*!< Setup packet buffer DMA Bus address */
  PCD_EP0StateTypeDef EP0_State;  /*!< EP0 State */

  void          *pData;       /*!< Pointer to upper stack Handler */
} PCD_HandleTypeDef;

/**
  * @}
  */

/* Include PCD HAL Extension module */
#include "stm32mp2xx_hal_pcd_ex.h"

/* Exported constants --------------------------------------------------------*/
/** @defgroup PCD_Exported_Constants PCD Exported Constants
  * @{
  */

/** @defgroup PCD_Speed PCD Speed
  * @{
  */
#define PCD_SPEED_SUPER                    USB_DWC3_SPEED_SUPER
#define PCD_SPEED_HIGH                     USB_DWC3_SPEED_HIGH
#define PCD_SPEED_FULL                     USB_DWC3_SPEED_FULL
#define PCD_SPEED_FULL_48                  USB_DWC3_SPEED_FULL_48
#define PCD_SPEED_LOW                      USB_DWC3_SPEED_LOW
/**
  * @}
  */

/** @defgroup PCD_MAXPACKETSIZE PCD MAXPACKETSIZE
  * @{
  */
#define PCD_SPEED_SUPER_MAXPACKETSIZE                    512U
#define PCD_SPEED_HIGH_MAXPACKETSIZE                     64U
#define PCD_SPEED_FULL_MAXPACKETSIZE                     64U
#define PCD_SPEED_FULL_48_MAXPACKETSIZE                  64U
#define PCD_SPEED_LOW_MAXPACKETSIZE                      8U
/**
  * @}
  */

/** @defgroup PCD_PHY_Module PCD PHY Module
  * @{
  */
/* USB2 PHY Mask 0xf */
#define PCD_PHY_ULPI                       USBPHY_ULPI
#define PCD_PHY_UTMI                       USBPHY_UTMI
#define PCD_USB2_EMBEDDED_PHY              USBPHY_EMBEDDED_USB2
/* USB3 PHY Mask (0xf << 4) */
#define PCD_PHY_PIPE3                      USBPHY_PIPE3
#define PCD_USB3_EMBEDDED_PHY              USBPHY_EMBEDDED_USB3
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PCD_Exported_Macros PCD Exported Macros
  *  @brief macros to handle interrupts and specific clock configurations
  * @{
  */
#define __HAL_PCD_ENABLE_INTR(__HANDLE__, intr)       USB_EnableEventInt((__HANDLE__)->Instance, intr)
#define __HAL_PCD_DISABLE_INTR(__HANDLE__, intr)      USB_DisableEventInt((__HANDLE__)->Instance, intr)

#define __HAL_PCD_SETUP_REQ_LEN(addr)   (((uint16_t)(*((/*__IO*/ uint8_t *)(addr) + 6))) + \
                                         (((uint16_t)(*((/*__IO*/ uint8_t *)(addr) + 7))) << 8))

#define __HAL_PCD_SETUP_REQ_DATA_DIR_IN(addr)   ((*(/*__IO*/ uint8_t *)(addr)) & 0x80U)

#define __HAL_PCD_INCR_EVENT_POS(__HANDLE__, intr, incr)  (__HANDLE__)->IntBuffers.EvtBufferPos[intr] = \
    ((__HANDLE__)->IntBuffers.EvtBufferPos[intr] + (incr)) \
    % USB_DWC3_EVENT_BUFFER_SIZE
#define __HAL_PCD_READ_EVENT(__HANDLE__, intr)    *(__IO uint32_t *)&((__HANDLE__)->IntBuffers.EvtBuffer_addr[intr]\
                                                                      [(__HANDLE__)->IntBuffers.EvtBufferPos[intr]])

#define __HAL_PCD_EPADDR_TO_PHYEPNUM(ep_addr) ((2U*((ep_addr) & 0x7FU)) + ((((ep_addr) & 0x80U) != 0U) ? 1U : 0U))
#define __HAL_PCD_PHYEPNUM_TO_EPADDR(phy_epnum) (((phy_epnum)/2U) | ((((phy_epnum) & 0x1U) != 0U) ? 0x80U : 0U))


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCD_Exported_Functions PCD Exported Functions
  * @{
  */

/* Initialization/de-initialization functions  ********************************/
/** @addtogroup PCD_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
HAL_StatusTypeDef HAL_PCD_Init(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_DeInit(PCD_HandleTypeDef *hpcd);
void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd);
void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd);
/**
  * @}
  */

/* I/O operation functions  ***************************************************/
/* Non-Blocking mode: Interrupt */
/** @addtogroup PCD_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */
HAL_StatusTypeDef HAL_PCD_Start(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_Stop(PCD_HandleTypeDef *hpcd);
void HAL_PCD_IRQHandler(PCD_HandleTypeDef *hpcd);

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd);
void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd);
/**
  * @}
  */

/* Peripheral Control functions  **********************************************/
/** @addtogroup PCD_Exported_Functions_Group3 Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_PCD_SetAddress(PCD_HandleTypeDef *hpcd, uint8_t address);
HAL_StatusTypeDef HAL_PCD_SetTestMode(PCD_HandleTypeDef *hpcd, uint8_t test_mode);
HAL_StatusTypeDef HAL_PCD_EP_Open(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
HAL_StatusTypeDef HAL_PCD_EP_Open_Periodic(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type,
                                           uint8_t ep_bInterval);
HAL_StatusTypeDef HAL_PCD_EP_Close(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_Receive(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
HAL_StatusTypeDef HAL_PCD_EP_Transmit(PCD_HandleTypeDef *hpcd, uint8_t ep_addr, uint8_t *pBuf, uint32_t len);
uint16_t          HAL_PCD_EP_GetRxCount(const PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_SetStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_ClrStall(PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_EP_Flush(const PCD_HandleTypeDef *hpcd, uint8_t ep_addr);
HAL_StatusTypeDef HAL_PCD_ActivateRemoteWakeup(PCD_HandleTypeDef *hpcd);
HAL_StatusTypeDef HAL_PCD_DeActivateRemoteWakeup(PCD_HandleTypeDef *hpcd);

/**
  * @}
  */

/* Peripheral State functions  ************************************************/
/** @addtogroup PCD_Exported_Functions_Group4 Peripheral State functions
  * @{
  */
PCD_StateTypeDef HAL_PCD_GetState(const PCD_HandleTypeDef *hpcd);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup PCD_Private_Macros PCD Private Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup PCD_Instance_definition PCD Instance definition
  * @{
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* STM32MP2xx_HAL_PCD_DRD_H */

/**
  * @}
  */

/**
  * @}
 */
