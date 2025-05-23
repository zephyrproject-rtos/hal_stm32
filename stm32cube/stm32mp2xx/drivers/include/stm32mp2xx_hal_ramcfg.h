/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_ramcfg.h
  * @author  MCD Application Team
  * @brief   Header file of RAMCFG HAL module.
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
#ifndef STM32MP2xx_HAL_RAMCFG_H
#define STM32MP2xx_HAL_RAMCFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup RAMCFG
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Types RAMCFG Exported Types
  * @brief    RAMCFG Exported Types
  * @{
  */

/**
  * @brief  HAL RAMCFG State Enumeration Definition
  */
typedef enum
{
  HAL_RAMCFG_STATE_RESET             = 0x00U,  /*!< RAMCFG not yet initialized or disabled */
  HAL_RAMCFG_STATE_READY             = 0x01U,  /*!< RAMCFG initialized and ready for use   */
  HAL_RAMCFG_STATE_BUSY              = 0x02U,  /*!< RAMCFG process is ongoing              */
  HAL_RAMCFG_STATE_ERROR             = 0x03U,  /*!< RAMCFG error state                     */
} HAL_RAMCFG_StateTypeDef;

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL RAMCFG Callbacks IDs Enumeration Definition
  */
typedef enum
{
  HAL_RAMCFG_MSPINIT_CB_ID           = 0x00U,  /*!< RAMCFG MSP Init Callback ID            */
  HAL_RAMCFG_MSPDEINIT_CB_ID         = 0x01U,  /*!< RAMCFG MSP DeInit Callback ID          */
  HAL_RAMCFG_SE_DETECT_CB_ID         = 0x02U,  /*!< RAMCFG Single Error Detect Callback ID */
  HAL_RAMCFG_DE_DETECT_CB_ID         = 0x03U,  /*!< RAMCFG Double Error Detect Callback ID */
  HAL_RAMCFG_ALL_CB_ID               = 0x04U,  /*!< RAMCFG All callback ID                 */
} HAL_RAMCFG_CallbackIDTypeDef;
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

/**
  * @brief  RAMCFG Handle Structure Definition
  */
typedef struct __RAMCFG_HandleTypeDef
{
  RAMCFG_TypeDef                  *Instance;                                                              /*!< RAMCFG Register Base Address        */
  __IO HAL_RAMCFG_StateTypeDef    State;                                                                  /*!< RAMCFG State                        */
  __IO uint32_t                   ErrorCode;                                                              /*!< RAMCFG Error Code                   */
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
  void (* MspInitCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);                                       /*!< RAMCFG MSP Init Callback            */
  void (* MspDeInitCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);                                     /*!< RAMCFG MSP DeInit Callback          */
  void (* DetectSingleErrorCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);                             /*!< RAMCFG Single Error Detect Callback */
  void (* DetectDoubleErrorCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);                             /*!< RAMCFG Double Error Detect Callback */
#endif  /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
} RAMCFG_HandleTypeDef;

/**
  * @brief  HAL RAMCFG State Enumeration Definition
  */
typedef enum
{
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_16KB  = 0x00000000U,
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_32KB  = 0x00000001U,
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_48KB  = 0x00000002U,
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_64KB  = 0x00000003U,
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_80KB  = 0x00000004U,
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_96KB  = 0x00000005U,
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_112KB = 0x00000006U,
  HAL_RAMCFG_CRC_RETRAM_BUFFERSIZE_128KB = 0x00000007U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_1KB  = 0x00000000U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_2KB  = 0x00000001U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_3KB  = 0x00000002U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_4KB  = 0x00000003U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_5KB  = 0x00000004U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_6KB  = 0x00000005U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_7KB  = 0x00000006U,
  HAL_RAMCFG_CRC_LPSRAM1_BUFFERSIZE_8KB  = 0x00000007U,
} HAL_RAMCFG_CRCBufferSizeTypeDef;

/**
  * @brief  HAL RAMCFG State Enumeration Definition
  */
typedef enum
{
  HAL_RAMCFG_CRC_MODE_DISABLE           = 0x00U,  /*!< CRC disabled                        */
  HAL_RAMCFG_CRC_MODE_COMPUTE_REFERENCE = 0x01U,  /*!< CRC reference signature computation */
  HAL_RAMCFG_CRC_MODE_COMPUTE_AND_CHECK = 0x02U,  /*!< CRC computation and signature check */
} HAL_RAMCFG_CRCModeTypeDef;

/**
  * @brief  RAMCFG Config CRC Structure Definition
  */
typedef struct
{
  HAL_RAMCFG_CRCBufferSizeTypeDef CRCBufferSize;
  HAL_RAMCFG_CRCModeTypeDef       CRCMode;
} HAL_RAMCFG_ConfigCRCTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Constants RAMCFG Exported Constants
  * @brief    RAMCFG Exported Constants
  * @{
  */

/** @defgroup RAMCFG_Error_Codes RAMCFG Error Codes
  * @brief    RAMCFG Error Codes
  * @{
  */
#define HAL_RAMCFG_ERROR_NONE             0x00000000U  /*!< RAMCFG No Error         */
#define HAL_RAMCFG_ERROR_TIMEOUT          0x00000001U  /*!< RAMCFG Timeout Error    */
#define HAL_RAMCFG_ERROR_BUSY             0x00000002U  /*!< RAMCFG Busy Error       */
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
#define HAL_RAMCFG_ERROR_INVALID_CALLBACK 0x00000003U  /*!< Invalid Callback error  */
#endif  /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
#define HAL_RAMCFG_ERROR_CRC              0x00000004U  /*!< RAMCFG CRC Error        */
/**
  * @}
  */

/** @defgroup RAMCFG_Interrupt RAMCFG Interrupts
  * @brief    RAMCFG Interrupts
  * @{
  */
#define RAMCFG_IT_SINGLEERR   RAMCFG_IER_SEIE                       /* RAMCFG Single Error Interrupt */
#define RAMCFG_IT_DOUBLEERR   RAMCFG_IER_DEIE                       /* RAMCFG Double Error Interrupt */
#define RAMCFG_IT_ALL         (RAMCFG_IER_SEIE | RAMCFG_IER_DEIE)   /* RAMCFG All RAMCFG interrupt   */
/**
  * @}
  */

/** @defgroup RAMCFG_FLAG RAMCFG Monitor Flags
  * @brief    RAMCFG Monitor Flags
  * @{
  */
#define RAMCFG_FLAG_SINGLEERR   RAMCFG_ISR_SEC           /* RAMCFG Single Error Corrected Flag     */
#define RAMCFG_FLAG_DOUBLEERR   RAMCFG_ISR_DED           /* RAMCFG Double Error Detected Flag      */
#define RAMCFG_FLAG_SRAMBUSY    RAMCFG_ISR_SRAMBUSY      /* RAMCFG SRAM busy Flag                  */
#define RAMCFG_FLAGS_ALL        (RAMCFG_ISR_SEC    \
                                 | RAMCFG_ISR_DED  \
                                 | RAMCFG_ISR_SRAMBUSY)  /* RAMCFG All Flags                       */
#define RAMCFG_FLAG_CRCSCS      RAMCFG_CSR_CRCSCS        /* RAMCFG CRC signature check status Flag */
#define RAMCFG_FLAG_CRCEOC      RAMCFG_CSR_CRCEOC        /* RAMCFG CRC end of computation Flag     */
#define RAMCFG_FLAG_CRCFC       RAMCFG_CCR2_CRCFC        /* RAMCFG CRC flags clear                 */
/**
  * @}
  */

/** @defgroup RAMCFG_Keys RAMCFG Keys
  * @brief    RAMCFG Keys
  * @{
  */
#define RAMCFG_ERASE_KEY1  (0xCAU) /* RAMCFG launch Erase Key 1 */
#define RAMCFG_ERASE_KEY2  (0x53U) /* RAMCFG launch Erase Key 2 */

#define RAMCFG_ECC_KEY1    (0xAEU) /* RAMCFG launch ECC Key 1 */
#define RAMCFG_ECC_KEY2    (0x75U) /* RAMCFG launch ECC Key 2 */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Macros RAMCFG Exported Macros
  * @brief    RAMCFG Exported Macros
  * @{
  */

/**
  * @brief  Enable the specified RAMCFG interrupts.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __INTERRUPT__: Specifies the RAMCFG interrupt sources to be enabled.
  *         This parameter can be one of the following values:
  *           @arg RAMCFG_IT_SINGLEERR    : Single Error Interrupt Mask.
  *           @arg RAMCFG_IT_DOUBLEERR    : Double Error Interrupt Mask.
  *           @arg RAMCFG_IT_NMIERR       : Double Error Interrupt redirection to NMI Mask.
  *           @arg RAMCFG_IT_ALL          : All Interrupt Mask.
  * @retval None
  */
#define __HAL_RAMCFG_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/**
  * @brief  Disable the specified RAMCFG interrupts.
  * @note   This macros is used only to disable RAMCFG_IT_SINGLEERR and RAMCFG_IT_DOUBLEERR
  *         interrupts. RAMCFG_IT_NMIERR interrupt could not be disabled only by global
  *         peripheral reset or system reset.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __INTERRUPT__: Specifies the RAMCFG interrupt sources to be disabled.
  *         This parameter can be one of the following values:
  *           @arg RAMCFG_IT_SINGLEERR    : Single Error Interrupt Mask.
  *           @arg RAMCFG_IT_DOUBLEERR    : Double Error Interrupt Mask.
  * @retval None
  */
#define __HAL_RAMCFG_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RAMCFG interrupt source is enabled or not.
  * @param  __HANDLE__    : Specifies the RAMCFG Handle.
  * @param  __INTERRUPT__ : Specifies the RAMCFG interrupt source to check.
  *          This parameter can be one of the following values:
  *           @arg RAMCFG_IT_SINGLEERR    : Single Error Interrupt Mask.
  *           @arg RAMCFG_IT_DOUBLEERR    : Double Error Interrupt Mask.
  *           @arg RAMCFG_IT_NMIERR       : Double Error Interrupt Redirection to NMI Mask.
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_RAMCFG_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IER &\
                                                                 (__INTERRUPT__)) == (__INTERRUPT__)) ? 1U : 0U)

/**
  * @brief  Get the RAMCFG pending flags.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __FLAG__     : Specifies the flag to be checked.
  *         This parameter can be one of the following values:
  *            @arg RAMCFG_FLAG_SINGLEERR  : Single Error Detected and Corrected Flag.
  *            @arg RAMCFG_FLAG_DOUBLEERR  : Double Error Detected Flag.
  *            @arg RAMCFG_FLAG_SRAMBUSY   : SRAM Busy Flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_RAMCFG_GET_FLAG(__HANDLE__, __FLAG__) (READ_BIT((__HANDLE__)->Instance->ISR, (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the RAMCFG pending flags.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __FLAG__     : Specifies the flag to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg RAMCFG_FLAG_SINGLEERR  : Single Error Detected and Corrected Flag.
  *            @arg RAMCFG_FLAG_DOUBLEERR  : Double Error Detected Flag.
  * @retval None.
  */
#define __HAL_RAMCFG_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR |= (__FLAG__))

/** @brief  Reset the RAMCFG handle state.
  * @param  __HANDLE__    : Specifies the RAMCFG Handle.
  * @retval None.
  */
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
#define __HAL_RAMCFG_RESET_HANDLE_STATE(__HANDLE__) do{\
                                                        (__HANDLE__)->State = HAL_RAMCFG_STATE_RESET; \
                                                        (__HANDLE__)->MspInitCallback   = NULL;       \
                                                        (__HANDLE__)->MspDeInitCallback = NULL;       \
                                                      }while(0)
#else
#define __HAL_RAMCFG_RESET_HANDLE_STATE(__HANDLE__) do{\
                                                        (__HANDLE__)->State = HAL_RAMCFG_STATE_RESET; \
                                                      }while(0)
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

/**
  * @brief  Get the RAMCFG CRC pending flags.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __FLAG__     : Specifies the flag to be checked.
  *         This parameter can be one of the following values:
  *            @arg RAMCFG_FLAG_CRCSCS : CRC signature check status flag.
  *            @arg RAMCFG_FLAG_CRCEOC : CRC end of computation flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_RAMCFG_CRC_GET_FLAG(__HANDLE__, __FLAG__) (READ_BIT((__HANDLE__)->Instance->CSR, (__FLAG__))\
                                                         == (__FLAG__))

/**
  * @brief  Clear the RAMCFG CRC pending flags.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __FLAG__     : Specifies the flag to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg RAMCFG_FLAG_CRCFC : CRC flags clear.
  * @retval None.
  */
#define __HAL_RAMCFG_CRC_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->CCR2 |= (__FLAG__))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Functions RAMCFG Exported Functions
  * @brief    RAMCFG Exported Functions
  * @{
  */

/** @defgroup RAMCFG_Exported_Functions_Group1 Initialization and De-Initialization Functions
  * @brief    Initialization and De-Initialization Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_Init(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_DeInit(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_MspInit(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_MspDeInit(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group2 ECC Operation Functions
  * @brief    ECC Operation Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_StartECC(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_StopECC(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_EnableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications);
HAL_StatusTypeDef HAL_RAMCFG_DisableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications);
uint32_t HAL_RAMCFG_IsECCSingleErrorDetected(const RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_IsECCDoubleErrorDetected(const RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_GetSingleErrorAddress(const RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_GetDoubleErrorAddress(const RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group5 Erase Operation Functions
  * @brief    Erase Operation Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_Erase(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group6 Handle Interrupt and Callbacks Functions
  * @brief    Handle Interrupt and Callbacks Functions
  * @{
  */
void              HAL_RAMCFG_IRQHandler(RAMCFG_HandleTypeDef *hramcfg);
void              HAL_RAMCFG_DetectSingleErrorCallback(RAMCFG_HandleTypeDef *hramcfg);
void              HAL_RAMCFG_DetectDoubleErrorCallback(RAMCFG_HandleTypeDef *hramcfg);
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_RAMCFG_RegisterCallback(RAMCFG_HandleTypeDef *hramcfg, HAL_RAMCFG_CallbackIDTypeDef CallbackID,
                                              void (* pCallback)(RAMCFG_HandleTypeDef *_hramcfg));
HAL_StatusTypeDef HAL_RAMCFG_UnRegisterCallback(RAMCFG_HandleTypeDef *hramcfg, HAL_RAMCFG_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group7 State and Error Functions
  * @brief    State and Error Functions
  * @{
  */
uint32_t HAL_RAMCFG_GetError(const RAMCFG_HandleTypeDef *hramcfg);
HAL_RAMCFG_StateTypeDef HAL_RAMCFG_GetState(const RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group8 CRC Functions
  * @brief    CRC Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_ConfigCRC(RAMCFG_HandleTypeDef *hramcfg, const HAL_RAMCFG_ConfigCRCTypeDef *crcConfig);
HAL_StatusTypeDef HAL_RAMCFG_ComputeCRC(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_HWEraseEnable(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_HWEraseDisable(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/**
  * @}
  */

/* Private Constants ---------------------------------------------------------*/

/** @defgroup RAMCFG_Private_Constants RAMCFG Private Defines and Constants
  * @brief    RAMCFG Private Defines and Constants
  * @{
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup RAMCFG_Private_Macros RAMCFG Private Macros
  * @brief    RAMCFG Private Macros
  * @{
  */
#define IS_RAMCFG_INTERRUPT(INTERRUPT)         (((INTERRUPT) != 0U) &&\
                                                (((INTERRUPT) & ~(RAMCFG_IT_SINGLEERR | RAMCFG_IT_DOUBLEERR)) == 0U))

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* STM32MP2xx_HAL_RAMCFG_H */
