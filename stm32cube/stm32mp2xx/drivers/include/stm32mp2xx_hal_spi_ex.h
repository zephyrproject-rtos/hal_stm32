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
#if defined(SPI8)
/* @brief  SPI1 to SPI7 Triggers : no Triggers */

/* @brief  SPI8 Triggers */

/*!< HW Trigger signal is LPDMA_CH0_TRG     */
#define HAL_SPI8_LPDMA_CH0_TCF_TRG          (uint32_t)(0x00000000UL)
/*!< HW Trigger signal is LPDMA_CH1_TRG     */
#define HAL_SPI8_LPDMA_CH1_TCF_TRG          (uint32_t)(0x1UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPDMA_CH2_TRG     */
#define HAL_SPI8_LPDMA_CH2_TCF_TRG          (uint32_t)(0x2UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPDMA_CH3_TRG     */
#define HAL_SPI8_LPDMA_CH3_TCF_TRG          (uint32_t)(0x3UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is EXTI4_TRG         */
#define HAL_SPI8_EXTI4_TRG                  (uint32_t)(0x4UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is EXTI8_TRG         */
#define HAL_SPI8_EXTI5_TRG                  (uint32_t)(0x5UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM3_CH1_TRG    */
#define HAL_SPI8_LPTIM3_CH1_TRG             (uint32_t)(0x7UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM4_CH1_TRG    */
#define HAL_SPI8_LPTIM4_CH1_TRG             (uint32_t)(0x8UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM5_CH1_TRG    */
#define HAL_SPI8_LPTIM5_CH1_TRG             (uint32_t)(0x9UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is RTC_ALRA_TRG      */
#define HAL_SPI8_RTC_ALRA_TRG               (uint32_t)(0xAUL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is RTC_WUT_TRG       */
#define HAL_SPI8_RTC_WUT_TRG                (uint32_t)(0xBUL << SPI_AUTOCR_TRIGSEL_Pos)
#else
/* @brief  SPI1 to SPI6 Triggers */

/*!< HW Trigger signal is EXTI4_TRG         */
#define HAL_SPI1_6_EXTI4_TRG                  (uint32_t)(0x4UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is EXTI5_TRG         */
#define HAL_SPI1_6_EXTI5_TRG                  (uint32_t)(0x5UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM3_CH1_TRG    */
#define HAL_SPI1_6_LPTIM3_CH1_TRG             (uint32_t)(0x7UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM4_CH1_TRG    */
#define HAL_SPI1_6_LPTIM4_CH1_TRG             (uint32_t)(0x8UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM5_CH1_TRG    */
#define HAL_SPI1_6_LPTIM5_CH1_TRG             (uint32_t)(0x9UL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is RTC_ALRA_TRG      */
#define HAL_SPI1_6_RTC_ALRA_TRG               (uint32_t)(0xAUL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is RTC_WUT_TRG       */
#define HAL_SPI1_6_RTC_WUT_TRG                (uint32_t)(0xBUL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is EXTI6_TRG         */
#define HAL_SPI1_6_EXTI6_TRG                  (uint32_t)(0xCUL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is EXTI7_TRG         */
#define HAL_SPI1_6_EXTI7_TRG                  (uint32_t)(0xDUL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM1_CH1_TRG    */
#define HAL_SPI1_6_LPTIM1_CH1_TRG             (uint32_t)(0xEUL << SPI_AUTOCR_TRIGSEL_Pos)
/*!< HW Trigger signal is LPTIM1_CH1_TRG    */
#define HAL_SPI1_6_LPTIM2_CH1_TRG             (uint32_t)(0xFUL << SPI_AUTOCR_TRIGSEL_Pos)

#endif /* SPI8 */
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
#if defined(SPI8)
#define IS_SPI_TRIG_SOURCE(__SOURCE__)        (((__SOURCE__) == HAL_SPI8_LPDMA_CH0_TCF_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI8_LPDMA_CH1_TCF_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI8_LPDMA_CH2_TCF_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI8_LPDMA_CH3_TCF_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI8_EXTI4_TRG         ) || \
                                               ((__SOURCE__) == HAL_SPI8_EXTI5_TRG         ) || \
                                               ((__SOURCE__) == HAL_SPI8_LPTIM3_CH1_TRG    ) || \
                                               ((__SOURCE__) == HAL_SPI8_LPTIM4_CH1_TRG    ) || \
                                               ((__SOURCE__) == HAL_SPI8_LPTIM5_CH1_TRG    ) || \
                                               ((__SOURCE__) == HAL_SPI8_RTC_ALRA_TRG      ) || \
                                               ((__SOURCE__) == HAL_SPI8_RTC_WUT_TRG       ))
#else
#define IS_SPI_TRIG_SOURCE(__SOURCE__)        (((__SOURCE__) == HAL_SPI1_6_EXTI4_TRG      ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_EXTI5_TRG      ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_LPTIM3_CH1_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_LPTIM4_CH1_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_LPTIM5_CH1_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_RTC_ALRA_TRG   ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_RTC_WUT_TRG    ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_EXTI6_TRG      ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_EXTI7_TRG      ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_LPTIM1_CH1_TRG ) || \
                                               ((__SOURCE__) == HAL_SPI1_6_LPTIM2_CH1_TRG ))
#endif /* SPI8 */


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
HAL_StatusTypeDef HAL_SPIEx_SetConfigAutonomousMode(SPI_HandleTypeDef *hspi,
                                                    const SPI_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_SPIEx_GetConfigAutonomousMode(const SPI_HandleTypeDef *hspi,
                                                    SPI_AutonomousModeConfTypeDef *sConfig);
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
