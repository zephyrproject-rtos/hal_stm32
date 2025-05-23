/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_ipcc.h
  * @author  MCD Application Team
  * @brief   Header file of Mailbox HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_IPCC_H
#define STM32MP2xx_HAL_IPCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

#if defined(IPCC) || defined(IPCC1) || defined(IPCC2)

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @defgroup IPCC IPCC
  * @brief IPCC HAL module driver
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup IPCC_Exported_Constants IPCC Exported Constants
  * @{
  */

/** @defgroup IPCC_Channel IPCC Channel
  * @{
  */
#define IPCC_CHANNEL_1    0x00000000U
#define IPCC_CHANNEL_2    0x00000001U
#define IPCC_CHANNEL_3    0x00000002U
#define IPCC_CHANNEL_4    0x00000003U
#define IPCC_CHANNEL_5    0x00000004U
#define IPCC_CHANNEL_6    0x00000005U
#define IPCC_CHANNEL_7    0x00000006U
#define IPCC_CHANNEL_8    0x00000007U
#define IPCC_CHANNEL_9    0x00000008U
#define IPCC_CHANNEL_10   0x00000009U
#define IPCC_CHANNEL_11   0x0000000AU
#define IPCC_CHANNEL_12   0x0000000BU
#define IPCC_CHANNEL_13   0x0000000CU
#define IPCC_CHANNEL_14   0x0000000DU
#define IPCC_CHANNEL_15   0x0000000EU
#define IPCC_CHANNEL_16   0x0000000FU
/**
  * @}
  */

/** @defgroup IPCC_Local_Processor_Id IPCC Local Processor Id
  * @{
  */
#define IPCC_CPU1 0x00000000U
#define IPCC_CPU2 0x00000001U
/**
  * @}
  */

/** @defgroup IPCC_Channel_attributes IPCC channel RIF protection attributes
  * @{
  */
#define IPCC_CHANNEL_PRIV  (IPCC_CHANNEL_PRIV_SELECT | (1U << IPCC_CHANNEL_PRIV_VAL_Pos))
#define IPCC_CHANNEL_NPRIV (IPCC_CHANNEL_PRIV_SELECT | (0U << IPCC_CHANNEL_PRIV_VAL_Pos))
#define IPCC_CHANNEL_SEC   (IPCC_CHANNEL_SEC_SELECT | (1U << IPCC_CHANNEL_SEC_VAL_Pos))
#define IPCC_CHANNEL_NSEC  (IPCC_CHANNEL_SEC_SELECT | (0U << IPCC_CHANNEL_SEC_VAL_Pos))

/**
  * @}
  */

/** @defgroup IPCC_attributes IPCC RIF protection attributes
  * @{
  */
#define IPCC_CPU_CID_DISABLE   (IPCC_CPU_CID_DISABLE_SELECT)
#define IPCC_CPU_CID_STATIC_0  (IPCC_CPU_CID_STATIC_SELECT | (00U << IPCC_CPU_CID_VAL_Pos))
#define IPCC_CPU_CID_STATIC_1  (IPCC_CPU_CID_STATIC_SELECT | (01U << IPCC_CPU_CID_VAL_Pos))
#define IPCC_CPU_CID_STATIC_2  (IPCC_CPU_CID_STATIC_SELECT | (02U << IPCC_CPU_CID_VAL_Pos))
#define IPCC_CPU_CID_STATIC_3  (IPCC_CPU_CID_STATIC_SELECT | (03U << IPCC_CPU_CID_VAL_Pos))
#define IPCC_CPU_CID_STATIC_4  (IPCC_CPU_CID_STATIC_SELECT | (04U << IPCC_CPU_CID_VAL_Pos))
#define IPCC_CPU_CID_STATIC_5  (IPCC_CPU_CID_STATIC_SELECT | (05U << IPCC_CPU_CID_VAL_Pos))
#define IPCC_CPU_CID_STATIC_6  (IPCC_CPU_CID_STATIC_SELECT | (06U << IPCC_CPU_CID_VAL_Pos))
#define IPCC_CPU_CID_STATIC_7  (IPCC_CPU_CID_STATIC_SELECT | (07U << IPCC_CPU_CID_VAL_Pos))

/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup IPCC_Exported_Types IPCC Exported Types
  * @{
  */

/**
  * @brief HAL IPCC State structures definition
  */
typedef enum
{
  HAL_IPCC_STATE_RESET             = 0x00U,  /*!< IPCC not yet initialized or disabled  */
  HAL_IPCC_STATE_READY             = 0x01U,  /*!< IPCC initialized and ready for use    */
  HAL_IPCC_STATE_BUSY              = 0x02U   /*!< IPCC internal processing is ongoing   */
} HAL_IPCC_StateTypeDef;

/**
  * @brief  IPCC channel direction structure definition
  */
typedef enum
{
  IPCC_CHANNEL_DIR_TX  = 0x00U,  /*!< Channel direction Tx is used by an MCU to transmit */
  IPCC_CHANNEL_DIR_RX  = 0x01U   /*!< Channel direction Rx is used by an MCU to receive */
} IPCC_CHANNELDirTypeDef;

/**
  * @brief  IPCC channel status structure definition
  */
typedef enum
{
  IPCC_CHANNEL_STATUS_FREE       = 0x00U,  /*!< Means that a new msg can be posted on that channel */
  IPCC_CHANNEL_STATUS_OCCUPIED   = 0x01U,  /*!< An MCU has posted a msg the other MCU hasn't retrieved */
  IPCC_CHANNEL_STATUS_ERROR      = 0x02U   /*!< Error (eg invalid channel index) */
} IPCC_CHANNELStatusTypeDef;

/**
  * @brief  IPCC handle structure definition
  */
typedef struct __IPCC_HandleTypeDef
{
  IPCC_TypeDef                   *Instance;     /*!< IPCC registers base address */
  void (* ChannelCallbackRx[IPCC_CHANNEL_NUMBER])(struct __IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);                            /*!< Rx Callback registration table */
  void (* ChannelCallbackTx[IPCC_CHANNEL_NUMBER])(struct __IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);                            /*!< Tx Callback registration table */
  uint32_t                       callbackRequest; /*!< Store information about callback notification by channel */
  __IO HAL_IPCC_StateTypeDef     State;           /*!< IPCC State: initialized or not */
  uint32_t                       channelNumber;   /*!< Number of supported channels */
} IPCC_HandleTypeDef;

/**
  * @brief  IPCC callback typedef
  */
typedef void ChannelCb(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup IPCC_Intermediate_Macros IPCC intermediate macros used by exported macro
  * @{
  */

#define __HAL_IPCC_ENABLE_IT_C2(__HANDLE__, __CHDIRECTION__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C2CR |= IPCC_C2CR_RXOIE) : \
   ((__HANDLE__)->Instance->C2CR |= IPCC_C2CR_TXFIE))

#define __HAL_IPCC_ENABLE_IT_C1(__HANDLE__, __CHDIRECTION__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C1CR |= IPCC_C1CR_RXOIE) : \
   ((__HANDLE__)->Instance->C1CR |= IPCC_C1CR_TXFIE))

#define __HAL_IPCC_DISABLE_IT_C2(__HANDLE__, __CHDIRECTION__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C2CR &= ~IPCC_C2CR_RXOIE) : \
   ((__HANDLE__)->Instance->C2CR &= ~IPCC_C2CR_TXFIE))

#define __HAL_IPCC_DISABLE_IT_C1(__HANDLE__, __CHDIRECTION__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C1CR &= ~IPCC_C1CR_RXOIE) : \
   ((__HANDLE__)->Instance->C1CR &= ~IPCC_C1CR_TXFIE))

#define __HAL_IPCC_MASK_CHANNEL_IT_C2(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C2MR |= (IPCC_C1MR_CH1OM_Msk << (__CHINDEX__))) : \
   ((__HANDLE__)->Instance->C2MR |= (IPCC_C1MR_CH1FM_Msk << (__CHINDEX__))))

#define __HAL_IPCC_MASK_CHANNEL_IT_C1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C1MR |= (IPCC_C1MR_CH1OM_Msk << (__CHINDEX__))) : \
   ((__HANDLE__)->Instance->C1MR |= (IPCC_C1MR_CH1FM_Msk << (__CHINDEX__))))

#define __HAL_IPCC_UNMASK_CHANNEL_IT_C2(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C2MR &= ~(IPCC_C1MR_CH1OM_Msk << (__CHINDEX__))) : \
   ((__HANDLE__)->Instance->C2MR &= ~(IPCC_C1MR_CH1FM_Msk << (__CHINDEX__))))

#define __HAL_IPCC_UNMASK_CHANNEL_IT_C1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  (((__CHDIRECTION__) == IPCC_CHANNEL_DIR_RX) ? \
   ((__HANDLE__)->Instance->C1MR &= ~(IPCC_C1MR_CH1OM_Msk << (__CHINDEX__))) : \
   ((__HANDLE__)->Instance->C1MR &= ~(IPCC_C1MR_CH1FM_Msk << (__CHINDEX__))))

#if defined(CORE_CM33)
#define __HAL_IPCC_ENABLE_IT_IPCC1(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_ENABLE_IT_C2(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_DISABLE_IT_IPCC1(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_DISABLE_IT_C2(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_MASK_CHANNEL_IT_IPCC1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_MASK_CHANNEL_IT_C2(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#define __HAL_IPCC_UNMASK_CHANNEL_IT_IPCC1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_UNMASK_CHANNEL_IT_C2(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#else   /* CORE_CM33 */
#define __HAL_IPCC_ENABLE_IT_IPCC1(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_ENABLE_IT_C1(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_DISABLE_IT_IPCC1(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_DISABLE_IT_C1(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_MASK_CHANNEL_IT_IPCC1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_MASK_CHANNEL_IT_C1(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#define __HAL_IPCC_UNMASK_CHANNEL_IT_IPCC1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_UNMASK_CHANNEL_IT_C1(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#endif  /* CORE_CM33 */
#if defined (CORE_CA35) || defined(CORE_CM33)
#define __HAL_IPCC_ENABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_ENABLE_IT_C2(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_DISABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_DISABLE_IT_C2(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_MASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_MASK_CHANNEL_IT_C2(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#define __HAL_IPCC_UNMASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_UNMASK_CHANNEL_IT_C2(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#else   /* (CORE_CA35) || (CORE_CM33) */
#define __HAL_IPCC_ENABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_ENABLE_IT_C1(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_DISABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_DISABLE_IT_C1(__HANDLE__, __CHDIRECTION__)
#define __HAL_IPCC_MASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_MASK_CHANNEL_IT_C1(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#define __HAL_IPCC_UNMASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_UNMASK_CHANNEL_IT_C1(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#endif  /* (CORE_CA35) || (CORE_CM33) */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup IPCC_Exported_Macros IPCC Exported Macros
  * @{
  */

/**
  * @brief  Enable the specified interrupt.
  * @param  __HANDLE__ specifies the IPCC Handle
  * @param  __CHDIRECTION__ specifies the channels Direction
  *          This parameter can be one of the following values:
  *            @arg @ref IPCC_CHANNEL_DIR_TX Transmit channel free interrupt enable
  *            @arg @ref IPCC_CHANNEL_DIR_RX Receive channel occupied interrupt enable
  */
#if !defined(IPCC1)
#define __HAL_IPCC_ENABLE_IT(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_ENABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__)
#else /* !IPCC1 */
#define __HAL_IPCC_ENABLE_IT(__HANDLE__, __CHDIRECTION__) \
  (((__HANDLE__)->Instance == IPCC1) ? \
   __HAL_IPCC_ENABLE_IT_IPCC1(__HANDLE__, __CHDIRECTION__) : \
   __HAL_IPCC_ENABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__))
#endif /* !IPCC1 */

/**
  * @brief  Disable the specified interrupt.
  * @param  __HANDLE__ specifies the IPCC Handle
  * @param  __CHDIRECTION__ specifies the channels Direction
  *          This parameter can be one of the following values:
  *            @arg @ref IPCC_CHANNEL_DIR_TX Transmit channel free interrupt enable
  *            @arg @ref IPCC_CHANNEL_DIR_RX Receive channel occupied interrupt enable
  */
#if !defined(IPCC1)
#define __HAL_IPCC_DISABLE_IT(__HANDLE__, __CHDIRECTION__) \
  __HAL_IPCC_DISABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__)
#else /* ! IPCC1 */
#define __HAL_IPCC_DISABLE_IT(__HANDLE__, __CHDIRECTION__) \
  (((__HANDLE__)->Instance == IPCC1) ? \
   __HAL_IPCC_DISABLE_IT_IPCC1(__HANDLE__, __CHDIRECTION__) : \
   __HAL_IPCC_DISABLE_IT_IPCC2(__HANDLE__, __CHDIRECTION__))
#endif /* ! IPCC1 */

/**
  * @brief  Mask the specified interrupt.
  * @param  __HANDLE__ specifies the IPCC Handle
  * @param  __CHDIRECTION__ specifies the channels Direction
  *          This parameter can be one of the following values:
  *            @arg @ref IPCC_CHANNEL_DIR_TX Transmit channel free interrupt enable
  *            @arg @ref IPCC_CHANNEL_DIR_RX Receive channel occupied interrupt enable
  * @param  __CHINDEX__ specifies the channels number:
  *         This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  */
#if !defined(IPCC1)
#define __HAL_IPCC_MASK_CHANNEL_IT(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_MASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#else /* !IPCC1 */
#define __HAL_IPCC_MASK_CHANNEL_IT(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  (((__HANDLE__)->Instance == IPCC1) ? \
   __HAL_IPCC_MASK_CHANNEL_IT_IPCC1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) : \
   __HAL_IPCC_MASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__))
#endif /* !IPCC1 */

/**
  * @brief  Unmask the specified interrupt.
  * @param  __HANDLE__ specifies the IPCC Handle
  * @param  __CHDIRECTION__ specifies the channels Direction
  *          This parameter can be one of the following values:
  *            @arg @ref IPCC_CHANNEL_DIR_TX Transmit channel free interrupt enable
  *            @arg @ref IPCC_CHANNEL_DIR_RX Receive channel occupied interrupt enable
  * @param  __CHINDEX__ specifies the channels number:
  *         This parameter can be one of the following values:
  *            @arg IPCC_CHANNEL_1: IPCC Channel 1
  *            ...
  *            @arg IPCC_CHANNEL_16: IPCC Channel 16
  */
#if !defined(IPCC1)
#define __HAL_IPCC_UNMASK_CHANNEL_IT(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  __HAL_IPCC_UNMASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__)
#else /* !IPCC1 */
#define __HAL_IPCC_UNMASK_CHANNEL_IT(__HANDLE__, __CHDIRECTION__, __CHINDEX__) \
  (((__HANDLE__)->Instance == IPCC1) ? \
   __HAL_IPCC_UNMASK_CHANNEL_IT_IPCC1(__HANDLE__, __CHDIRECTION__, __CHINDEX__) : \
   __HAL_IPCC_UNMASK_CHANNEL_IT_IPCC2(__HANDLE__, __CHDIRECTION__, __CHINDEX__))
#endif /* !IPCC1 */

/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/** @defgroup IPCC_Private_Constants IPCC Private Constants
  * @{
  */
#define IPCC_CHANNEL_PRIV_VAL_Pos         0U
#define IPCC_CHANNEL_SEC_VAL_Pos          1U
#define IPCC_CPU_CID_VAL_Pos              2U
#define IPCC_CHANNEL_PRIV_SELECT_Pos     24U
#define IPCC_CHANNEL_SEC_SELECT_Pos      25U
#define IPCC_CPU_CID_STATIC_SELECT_Pos   29U
#define IPCC_CPU_CID_DISABLE_SELECT_Pos  31U

#define IPCC_CPU_CID_VAL_Msk             (0x0FU << IPCC_CPU_CID_VAL_Pos)

#define IPCC_CHANNEL_PRIV_SELECT         (1U << IPCC_CHANNEL_PRIV_SELECT_Pos)
#define IPCC_CHANNEL_SEC_SELECT          (1U << IPCC_CHANNEL_SEC_SELECT_Pos)
#define IPCC_CPU_CID_STATIC_SELECT       (1U << IPCC_CPU_CID_STATIC_SELECT_Pos)
#define IPCC_CPU_CID_DISABLE_SELECT      (1U << IPCC_CPU_CID_DISABLE_SELECT_Pos)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup IPCC_Exported_Functions IPCC Exported Functions
  * @{
  */

/* Initialization and de-initialization functions *******************************/
/** @defgroup IPCC_Exported_Functions_Group1 Initialization and deinitialization functions
  *  @{
  */
HAL_StatusTypeDef HAL_IPCC_Init(IPCC_HandleTypeDef *hipcc);
HAL_StatusTypeDef HAL_IPCC_DeInit(IPCC_HandleTypeDef *hipcc);
void HAL_IPCC_MspInit(IPCC_HandleTypeDef *hipcc);
void HAL_IPCC_MspDeInit(IPCC_HandleTypeDef *hipcc);
/**
  * @}
  */

/** @defgroup IPCC_Exported_Functions_Group2 Communication functions
  *  @{
  */
/* IO operation functions  *****************************************************/
HAL_StatusTypeDef HAL_IPCC_ActivateNotification(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex,
                                                IPCC_CHANNELDirTypeDef ChannelDir, ChannelCb cb);
HAL_StatusTypeDef HAL_IPCC_DeActivateNotification(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex,
                                                  IPCC_CHANNELDirTypeDef ChannelDir);
IPCC_CHANNELStatusTypeDef HAL_IPCC_GetChannelStatus(IPCC_HandleTypeDef const *const hipcc, uint32_t ChannelIndex,
                                                    IPCC_CHANNELDirTypeDef ChannelDir);
HAL_StatusTypeDef HAL_IPCC_NotifyCPU(IPCC_HandleTypeDef const *const hipcc, uint32_t ChannelIndex,
                                     IPCC_CHANNELDirTypeDef ChannelDir);
/**
  * @}
  */

/** @defgroup IPCC_Exported_Functions_Group3 Peripheral State and Error functions
  *  @{
  */
/* Peripheral State and Error functions ****************************************/
HAL_IPCC_StateTypeDef HAL_IPCC_GetState(IPCC_HandleTypeDef const *const hipcc);
uint32_t HAL_IPCC_GetChannelNumber(const IPCC_HandleTypeDef *hipcc);
/**
  * @}
  */

/** @defgroup IPCC_IRQ_Handler_and_Callbacks Peripheral IRQ Handler and Callbacks
  *  @{
  */
/* IRQHandler and Callbacks used in non blocking modes  ************************/
void HAL_IPCC_TX_IRQHandler(IPCC_HandleTypeDef   *const hipcc);
void HAL_IPCC_RX_IRQHandler(IPCC_HandleTypeDef *const hipcc);
void HAL_IPCC_TxCallback(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);
void HAL_IPCC_RxCallback(IPCC_HandleTypeDef *hipcc, uint32_t ChannelIndex, IPCC_CHANNELDirTypeDef ChannelDir);
/**
  * @}
  */

/** @defgroup IPCC_Exported_Functions_Group4 RIF protection configuration functions
  *  @{
  */
/* RIF protection configuration functions **************************************/
HAL_StatusTypeDef HAL_IPCC_ConfigChannelAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t LocalProcessorId,
                                                   uint32_t ChannelIndex, uint32_t ChannelAttributes);
HAL_StatusTypeDef HAL_IPCC_GetConfigChannelAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t LocalProcessorId,
                                                      uint32_t ChannelIndex, uint32_t *pChannelAttributes);
HAL_StatusTypeDef HAL_IPCC_ConfigAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t Item, uint32_t Attributes);
HAL_StatusTypeDef HAL_IPCC_GetConfigAttributes(const IPCC_HandleTypeDef *hipcc, uint32_t Item, uint32_t *pAttributes);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* IPCC || IPCC1 || IPCC2 */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_IPCC_H */

