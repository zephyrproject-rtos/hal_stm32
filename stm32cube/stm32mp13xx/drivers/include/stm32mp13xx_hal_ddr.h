/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_ddr.h
  * @author  MCD Application Team
  * @brief   Header file of DDR HAL module.
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
#ifndef STM32MP13xx_HAL_DDR_H
#define STM32MP13xx_HAL_DDR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32mp13xx_hal_def.h"

#if defined (DDRCTRL) && defined (DDRPHYC)

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @addtogroup DDR
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DDR_Exported_Types DDR Exported Types
  * @{
  */

/**
  * @brief  HAL DDR type definition
  */
typedef enum
{
  STM32MP_DDR3,
  STM32MP_LPDDR2_16,
  STM32MP_LPDDR2_32,
  STM32MP_LPDDR3_16,
  STM32MP_LPDDR3_32,
} ddr_type;

/**
  * @brief  HAL DDR Self Refresh modes definition
  */
typedef enum
{
  HAL_DDR_SW_SELF_REFRESH_MODE = 0x0U,   /*!< DDR Software Self Refresh Mode */
  HAL_DDR_AUTO_SELF_REFRESH_MODE = 0x1U, /*!< DDR Automatic Self Refresh Mode */
  HAL_DDR_HW_SELF_REFRESH_MODE = 0x2U,   /*!< DDR Hardware Self Refresh Mode */
  HAL_DDR_INVALID_MODE = 0x3U,           /*!< DDR Invalid Self Refresh Mode */
} HAL_DDR_SelfRefreshModeTypeDef;

/**
  * @brief  DDR Initialization Structure definition
  */
typedef struct
{
  bool wakeup_from_standby; /*!< [input]
                                 Specifies if the system is waking up from the
                                 standby mode. The application is in charge to
                                 get this information. It will impact the self
                                 refresh state and the related steps within
                                 the initialization sequence. */

  bool self_refresh;        /*!< [output]
                                 Specifies the DDR self refresh status.
                                 Self Refresh enabled if true. */

  uint32_t zdata;           /*!< [input]
                                 Specifies the ZQ calibration restored value
                                 if any. Only used by the initialization
                                 sequence if wakeup_from_standby is true. The
                                 application is in charge of saving/restoring
                                 it during low power transitions. Value is
                                 obtaines when calling HAL_DDR_SR_Entry. */

  bool clear_bkp;           /*!< [output]
                                 Specifies if backup should be cleared after
                                 DDR initialization (DDR lost content case).
                                 Clear requested if true. */
} DDR_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DDR_Exported_Constants DDR Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup DDR_Exported_Macros DDR Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DDR_Exported_Functions
  * @{
  */

HAL_StatusTypeDef HAL_DDR_Init(DDR_InitTypeDef *iddr);
HAL_StatusTypeDef HAL_DDR_SR_Entry(uint32_t *zq0cr0_zdata);
HAL_StatusTypeDef HAL_DDR_SR_Exit(void);
HAL_StatusTypeDef HAL_DDR_SR_SetMode(HAL_DDR_SelfRefreshModeTypeDef mode);
HAL_DDR_SelfRefreshModeTypeDef HAL_DDR_SR_ReadMode(void);

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/** @defgroup DDR_Private_Types DDR Private Types
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup DDR_Private_Variables DDR Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup DDR_Private_Constants DDR Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup DDR_Private_Macros DDR Private Macros
  * @{
  */

/**
  * @}
  */
/* Private functions ---------------------------------------------------------*/
/** @defgroup DDR_Private_Functions DDR Private Functions
  * @{
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

#endif /* DDRCTRL & DDRPHYC */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xxHAL_DDR_H */
