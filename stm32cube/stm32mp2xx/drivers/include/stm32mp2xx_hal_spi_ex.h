/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_spi_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SPI HAL Extended module.
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
#ifndef STM32MP2xx_HAL_SPI_EX_H
#define STM32MP2xx_HAL_SPI_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup SPIEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SPIEx_Exported_Types SPIEx Exported Types
  * @{
  */

/**
  * @brief  SPI Autonomous Mode Configuration structure definition
  */
typedef struct
{
  uint32_t TriggerState;        /*!< Specifies the trigger state. This parameter can be a value
                                     of @ref FunctionalState */

  uint32_t TriggerSelection;    /*!< Specifies the autonomous mode trigger signal selection. This parameter
                                     can be a value of @ref SPI_AutonomousMode_TriggerSelection */

  uint32_t TriggerPolarity;     /*!< Specifies the autonomous mode trigger signal polarity sensitivity. This parameter
                                     can be a value of @ref SPI_AutonomousMode_TriggerPolarity */

} SPI_AutonomousModeConfTypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SPIEx_Exported_Constants SPIEx Exported Constants
  * @{
  */

/** @defgroup FunctionalState SPI Autonomous Mode State
  * @{
  */
#define SPI_AUTO_MODE_DISABLE           (0x00000000UL)
#define SPI_AUTO_MODE_ENABLE            SPI_AUTOCR_TRIGEN
/**
  * @}
  */

/** @defgroup SPI_AutonomousMode_TriggerSelection Autonomous Mode Trigger Selection
  * @{
  */
/* @brief  SPI1 to SPI7 Triggers : no Triggers */

/* @brief  SPI8 Triggers */
#define SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH0             (0x00000000UL)
#define SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH1             (0x00010000UL)
#define SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH2             (0x00020000UL)
#define SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH3             (0x00030000UL)
#define SPI_AUTO_MODE_SPI8_TRG_EXTI4                 (0x00040000UL)
#define SPI_AUTO_MODE_SPI8_TRG_EXTI5                 (0x00050000UL)
#define SPI_AUTO_MODE_SPI8_TRG_LPTIM3_CH1            (0x00070000UL)
#define SPI_AUTO_MODE_SPI8_TRG_LPTIM4_CH1            (0x00080000UL)
#define SPI_AUTO_MODE_SPI8_TRG_LPTIM5_CH1            (0x00090000UL)
#define SPI_AUTO_MODE_SPI8_TRG_RTC_ALRA              (0x000A0000UL)
#define SPI_AUTO_MODE_SPI8_TRG_RTC_WUT               (0x000B0000UL)

/**
  * @}
  */

/** @defgroup SPI_AutonomousMode_TriggerPolarity Autonomous Mode Trigger Polarity
  * @{
  */
#define SPI_TRIG_POLARITY_RISING        (0x00000000UL)       /* SPI HW Trigger signal on rising edge  */
#define SPI_TRIG_POLARITY_FALLING       SPI_AUTOCR_TRIGPOL   /* SPI HW Trigger signal on falling edge */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup SPIEx_Exported_Macros SPIEx Extended Exported Macros
  * @{
  */

#define IS_SPI_AUTO_MODE(__MODE__)                  (((__MODE__) == SPI_AUTO_MODE_DISABLE) || \
                                                     ((__MODE__) == SPI_AUTO_MODE_ENABLE))
#define IS_SPI_TRIG_SOURCE(SOURCE)                (((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH0   ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH1   ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH2   ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_LPDMA_CH3   ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_EXTI4       ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_EXTI5       ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_LPTIM3_CH1  ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_LPTIM4_CH1  ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_LPTIM5_CH1  ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_RTC_ALRA    ) || \
                                                   ((SOURCE) == SPI_AUTO_MODE_SPI8_TRG_RTC_WUT     ))


#define IS_SPI_AUTO_MODE_TRG_POL(__POLARITY__)      (((__POLARITY__) == SPI_TRIG_POLARITY_RISING) || \
                                                     ((__POLARITY__) == SPI_TRIG_POLARITY_FALLING))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SPIEx_Exported_Functions
  * @{
  */

/* Initialization and de-initialization functions  ****************************/
/* IO operation functions *****************************************************/
/** @addtogroup SPIEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_SPIEx_FlushRxFifo(const SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPIEx_EnableLockConfiguration(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPIEx_ConfigureUnderrun(SPI_HandleTypeDef *hspi, uint32_t UnderrunDetection,
                                              uint32_t UnderrunBehaviour);
/**
  * @}
  */

/** @addtogroup SPI_Autonomous_Mode_Functions Autonomous Mode Functions
  * @{
  */
HAL_StatusTypeDef HAL_SPIEx_SetConfigAutonomousMode(SPI_HandleTypeDef *hspi, SPI_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_SPIEx_GetConfigAutonomousMode(const SPI_HandleTypeDef *hspi, SPI_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_SPIEx_ClearConfigAutonomousMode(SPI_HandleTypeDef *hspi);
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


#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_SPI_EX_H */
