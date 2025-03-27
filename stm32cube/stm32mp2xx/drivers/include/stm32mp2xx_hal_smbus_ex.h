/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_smbus_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SMBUS HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_SMBUS_EX_H
#define STM32MP2xx_HAL_SMBUS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup SMBUSEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SMBUS_Exported_Types SMBUS Exported Types
  * @{
  */

/** @defgroup SMBUS_Autonomous_Mode_Configuration_Structure_definition Autonomous Mode Configuration
              Structure definition.
  * @brief  SMBUS Autonomous Mode Configuration structure definition
  * @{
  */
typedef struct
{
  uint32_t TriggerState;        /*!< Specifies the trigger state. This parameter can be a value
                                     of @ref SMBUSEx_AutonomousMode_FunctionalState */

  uint32_t TriggerSelection;    /*!< Specifies the autonomous mode trigger signal selection. This parameter
                                     can be a value of @ref SMBUSEx_AutonomousMode_TriggerSelection */

  uint32_t TriggerPolarity;     /*!< Specifies the autonomous mode trigger signal polarity sensitivity. This parameter
                                     can be a value of @ref SMBUSEx_AutonomousMode_TriggerPolarity */

} SMBUS_AutonomousModeConfTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup SMBUSEx_Exported_Constants SMBUS Extended Exported Constants
  * @{
  */

/** @defgroup SMBUSEx_FastModePlus SMBUS Extended Fast Mode Plus
  * @{
  */
#define SMBUS_FASTMODEPLUS_ENABLE         0x00000000U           /*!< Enable Fast Mode Plus                        */
#define SMBUS_FASTMODEPLUS_DISABLE        0x00000001U           /*!< Disable Fast Mode Plus                       */
/**
  * @}
  */

/** @defgroup SMBUSEx_AutonomousMode_FunctionalState SMBUS Extended Autonomous Mode State
  * @{
  */
#define SMBUS_AUTO_MODE_DISABLE           (0x00000000U)                    /* Autonomous mode disable  */
#define SMBUS_AUTO_MODE_ENABLE            I2C_AUTOCR_TRIGEN                /* Autonomous mode enable   */
/**
  * @}
  */

/** @defgroup SMBUSEx_AutonomousMode_TriggerSelection SMBUS Extended Autonomous Mode Trigger Selection
  * @{
  */
#if defined(I2C8)
#define SMBUS_TRIG_GRP1                   (0x10000000U)                    /*!< Trigger Group for I2C8 */
/* HW Trigger signal is LPDMA_CH0_TRG   */
#define SMBUS_GRP1_LPDMA_CH0_TCF_TRG      (uint32_t)(SMBUS_TRIG_GRP1 | (0x00000000U))
/* HW Trigger signal is LPDMA_CH1_TRG   */
#define SMBUS_GRP1_LPDMA_CH1_TCF_TRG      (uint32_t)(SMBUS_TRIG_GRP1 | (0x1U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPDMA_CH2_TRG   */
#define SMBUS_GRP1_LPDMA_CH2_TCF_TRG      (uint32_t)(SMBUS_TRIG_GRP1 | (0x2U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPDMA_CH3_TRG   */
#define SMBUS_GRP1_LPDMA_CH3_TCF_TRG      (uint32_t)(SMBUS_TRIG_GRP1 | (0x3U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI4_TRG       */
#define SMBUS_GRP1_EXTI4_TRG              (uint32_t)(SMBUS_TRIG_GRP1 | (0x4U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI5_TRG       */
#define SMBUS_GRP1_EXTI5_TRG              (uint32_t)(SMBUS_TRIG_GRP1 | (0x5U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM3_CH1_TRG  */
#define SMBUS_GRP1_LPTIM3_CH1_TRG         (uint32_t)(SMBUS_TRIG_GRP1 | (0x6U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM4_CH1_TRG  */
#define SMBUS_GRP1_LPTIM4_CH1_TRG         (uint32_t)(SMBUS_TRIG_GRP1 | (0x7U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM5_OUT_TRG  */
#define SMBUS_GRP1_LPTIM5_OUT_TRG         (uint32_t)(SMBUS_TRIG_GRP1 | (0x8U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_ALRA_TRG    */
#define SMBUS_GRP1_RTC_ALRA_TRG           (uint32_t)(SMBUS_TRIG_GRP1 | (0x9U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_WUT_TRG     */
#define SMBUS_GRP1_RTC_WUT_TRG            (uint32_t)(SMBUS_TRIG_GRP1 | (0xAU << I2C_AUTOCR_TRIGSEL_Pos))
#else
#if   defined(I2C1) && !defined(I2C8)
#define SMBUS_TRIG_GRP1                   (0x10000000U)         /*!< Trigger Group for I2C8 */
/* HW Trigger signal is EXTI4_TRG         */
#define SMBUS_GRP1_EXTI4_TRG                (uint32_t)(SMBUS_TRIG_GRP1 | (0x4U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI5_TRG         */
#define SMBUS_GRP1_EXTI5_TRG                (uint32_t)(SMBUS_TRIG_GRP1 | (0x5U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM3_CH1_TRG    */
#define SMBUS_GRP1_LPTIM3_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP1 | (0x7U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM4_CH1_TRG    */
#define SMBUS_GRP1_LPTIM4_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP1 | (0x8U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM5_OUT_TRG    */
#define SMBUS_GRP1_LPTIM5_OUT_TRG           (uint32_t)(SMBUS_TRIG_GRP1 | (0x9U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_ALRA_TRG      */
#define SMBUS_GRP1_RTC_ALRA_TRG             (uint32_t)(SMBUS_TRIG_GRP1 | (0xAU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_WUT_TRG       */
#define SMBUS_GRP1_RTC_WUT_TRG              (uint32_t)(SMBUS_TRIG_GRP1 | (0xBU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI6_TRG         */
#define SMBUS_GRP1_EXTI6_TRG                (uint32_t)(SMBUS_TRIG_GRP1 | (0xCU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI7_TRG         */
#define SMBUS_GRP1_EXTI7_TRG                (uint32_t)(SMBUS_TRIG_GRP1 | (0xDU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM1_CH1_TRG    */
#define SMBUS_GRP1_LPTIM1_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP1 | (0xEU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM2_CH1_TRG    */
#define SMBUS_GRP1_LPTIM2_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP1 | (0xFU << I2C_AUTOCR_TRIGSEL_Pos))
#endif /* I2C1 */

#if   defined(I2C2) && !defined(I2C8)
#define SMBUS_TRIG_GRP2                   (0x20000000U)        /*!< Trigger Group for I2C2 */
/* HW Trigger signal is EXTI4_TRG         */
#define SMBUS_GRP2_EXTI4_TRG                (uint32_t)(SMBUS_TRIG_GRP2 | (0x4U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI5_TRG         */
#define SMBUS_GRP2_EXTI5_TRG                (uint32_t)(SMBUS_TRIG_GRP2 | (0x5U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM3_CH1_TRG    */
#define SMBUS_GRP2_LPTIM3_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP2 | (0x7U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM4_CH1_TRG    */
#define SMBUS_GRP2_LPTIM4_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP2 | (0x8U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM5_OUT_TRG    */
#define SMBUS_GRP2_LPTIM5_OUT_TRG           (uint32_t)(SMBUS_TRIG_GRP2 | (0x9U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_ALRA_TRG      */
#define SMBUS_GRP2_RTC_ALRA_TRG             (uint32_t)(SMBUS_TRIG_GRP2 | (0xAU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_WUT_TRG       */
#define SMBUS_GRP2_RTC_WUT_TRG              (uint32_t)(SMBUS_TRIG_GRP2 | (0xBU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI6_TRG         */
#define SMBUS_GRP2_EXTI6_TRG                (uint32_t)(SMBUS_TRIG_GRP2 | (0xCU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI7_TRG         */
#define SMBUS_GRP2_EXTI7_TRG                (uint32_t)(SMBUS_TRIG_GRP2 | (0xDU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM1_CH1_TRG    */
#define SMBUS_GRP2_LPTIM1_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP2 | (0xEU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM2_CH1_TRG    */
#define SMBUS_GRP2_LPTIM2_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP2 | (0xFU << I2C_AUTOCR_TRIGSEL_Pos))
#endif /* I2C2 */

#if   defined(I2C3) && !defined(I2C8)
#define SMBUS_TRIG_GRP3                   (0x30000000U)         /*!< Trigger Group for I2C3 */
/* HW Trigger signal is EXTI4_TRG         */
#define SMBUS_GRP3_EXTI4_TRG                (uint32_t)(SMBUS_TRIG_GRP3 | (0x4U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is EXTI5_TRG         */
#define SMBUS_GRP3_EXTI5_TRG                (uint32_t)(SMBUS_TRIG_GRP3 | (0x5U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM3_CH1_TRG    */
#define SMBUS_GRP3_LPTIM3_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP3 | (0x7U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM4_CH1_TRG    */
#define SMBUS_GRP3_LPTIM4_CH1_TRG           (uint32_t)(SMBUS_TRIG_GRP3 | (0x8U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is LPTIM5_OUT_TRG    */
#define SMBUS_GRP3_LPTIM5_OUT_TRG           (uint32_t)(SMBUS_TRIG_GRP3 | (0x9U << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_ALRA_TRG      */
#define SMBUS_GRP3_RTC_ALRA_TRG             (uint32_t)(SMBUS_TRIG_GRP3 | (0xAU << I2C_AUTOCR_TRIGSEL_Pos))
/* HW Trigger signal is RTC_WUT_TRG       */
#define SMBUS_GRP3_RTC_WUT_TRG              (uint32_t)(SMBUS_TRIG_GRP3 | (0xBU << I2C_AUTOCR_TRIGSEL_Pos))
#endif /* I2C3 */

#endif /* I2C8 */

/**
  * @}
  */

/** @defgroup SMBUSEx_AutonomousMode_TriggerPolarity Extended Autonomous Mode Trigger Polarity
  * @{
  */
#define SMBUS_TRIG_POLARITY_RISING        (0x00000000U)                    /* SMBUS HW Trigger signal on rising edge  */
#define SMBUS_TRIG_POLARITY_FALLING       I2C_AUTOCR_TRIGPOL               /* SMBUS HW Trigger signal on falling edge */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SMBUSEx_Exported_Macros SMBUS Extended Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SMBUSEx_Exported_Functions SMBUS Extended Exported Functions
  * @{
  */

/** @addtogroup SMBUSEx_Exported_Functions_Group2 WakeUp Mode Functions
  * @{
  */
/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_SMBUSEx_EnableWakeUp(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUSEx_DisableWakeUp(SMBUS_HandleTypeDef *hsmbus);
/**
  * @}
  */

/** @addtogroup SMBUSEx_Exported_Functions_Group3 Fast Mode Plus Functions
  * @{
  */
HAL_StatusTypeDef HAL_SMBUSEx_ConfigFastModePlus(SMBUS_HandleTypeDef *hsmbus, uint32_t FastModePlus);
/**
  * @}
  */

/** @addtogroup SMBUSEx_Exported_Functions_Group4 Autonomous Mode Functions
  * @{
  */
HAL_StatusTypeDef HAL_SMBUSEx_SetConfigAutonomousMode(SMBUS_HandleTypeDef *hsmbus,
                                                      const SMBUS_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_SMBUSEx_GetConfigAutonomousMode(const SMBUS_HandleTypeDef *hsmbus,
                                                      SMBUS_AutonomousModeConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_SMBUSEx_ClearConfigAutonomousMode(SMBUS_HandleTypeDef *hsmbus);
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Constants SMBUS Extended Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Macro SMBUS Extended Private Macros
  * @{
  */
#define IS_SMBUS_FASTMODEPLUS(__CONFIG__) (((__CONFIG__) == (SMBUS_FASTMODEPLUS_ENABLE))   || \
                                           ((__CONFIG__) == (SMBUS_FASTMODEPLUS_DISABLE)))

#define IS_SMBUS_AUTO_MODE(__MODE__)                  (((__MODE__) == SMBUS_AUTO_MODE_DISABLE) ||                      \
                                                       ((__MODE__) == SMBUS_AUTO_MODE_ENABLE))

#if defined(I2C8)
#define IS_SMBUS_TRIG_SOURCE(__INSTANCE__, __SOURCE__)  (IS_SMBUS_GRP1_TRIG_SOURCE(__SOURCE__))
#define IS_SMBUS_GRP1_TRIG_SOURCE(__SOURCE__)  (((__SOURCE__) == SMBUS_GRP1_LPDMA_CH0_TCF_TRG  ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPDMA_CH1_TCF_TRG  ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPDMA_CH2_TCF_TRG  ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPDMA_CH3_TCF_TRG  ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_EXTI4_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_EXTI5_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM3_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM4_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM5_OUT_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_RTC_ALRA_TRG       ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_RTC_WUT_TRG        ))
#else
#define IS_SMBUS_TRIG_SOURCE(__INSTANCE__, __SOURCE__)  (((__INSTANCE__) == I2C3) ? \
                                                         IS_SMBUS_GRP3_TRIG_SOURCE(__SOURCE__) : \
                                                         ((__INSTANCE__) == I2C2) ? \
                                                         IS_SMBUS_GRP2_TRIG_SOURCE(__SOURCE__) : \
                                                         IS_SMBUS_GRP1_TRIG_SOURCE(__SOURCE__))

#define IS_SMBUS_GRP1_TRIG_SOURCE(__SOURCE__)  (((__SOURCE__) == SMBUS_GRP1_EXTI4_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_EXTI5_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM3_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM4_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM5_OUT_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_RTC_ALRA_TRG       ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_RTC_WUT_TRG        ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_EXTI6_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_EXTI7_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM1_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP1_LPTIM2_CH1_TRG     ))

#define IS_SMBUS_GRP2_TRIG_SOURCE(__SOURCE__)  (((__SOURCE__) == SMBUS_GRP2_EXTI4_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_EXTI5_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_LPTIM3_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_LPTIM4_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_LPTIM5_OUT_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_RTC_ALRA_TRG       ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_RTC_WUT_TRG        ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_EXTI6_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_EXTI7_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_LPTIM1_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP2_LPTIM2_CH1_TRG     ))

#define IS_SMBUS_GRP3_TRIG_SOURCE(__SOURCE__)  (((__SOURCE__) == SMBUS_GRP3_EXTI4_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP3_EXTI5_TRG          ) || \
                                                ((__SOURCE__) == SMBUS_GRP3_LPTIM3_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP3_LPTIM4_CH1_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP3_LPTIM5_OUT_TRG     ) || \
                                                ((__SOURCE__) == SMBUS_GRP3_RTC_ALRA_TRG       ) || \
                                                ((__SOURCE__) == SMBUS_GRP3_RTC_WUT_TRG        ))
#endif /* I2C8 */

#if defined(SMBUS_TRIG_GRP3)
#if defined(SMBUS_TRIG_GRP2)
#if defined(SMBUS_TRIG_GRP1)
#define IS_SMBUS_TRIG_INPUT_INSTANCE(__INSTANCE__)    (IS_SMBUS_GRP1_INSTANCE(__INSTANCE__) ||                     \
                                                       IS_SMBUS_GRP2_INSTANCE(__INSTANCE__) ||             \
                                                       IS_SMBUS_GRP3_INSTANCE(__INSTANCE__))
#endif /* SMBUS_TRIG_GRP1 */
#else
#define IS_SMBUS_TRIG_INPUT_INSTANCE(__INSTANCE__)    IS_SMBUS_GRP1_INSTANCE(__INSTANCE__)
#endif /* SMBUS_TRIG_GRP2 */
#else
#if defined(SMBUS_TRIG_GRP2)
#if defined(SMBUS_TRIG_GRP1)
#define IS_SMBUS_TRIG_INPUT_INSTANCE(__INSTANCE__)    (IS_SMBUS_GRP1_INSTANCE(__INSTANCE__) || \
                                                       IS_SMBUS_GRP2_INSTANCE(__INSTANCE__))
#endif /* SMBUS_TRIG_GRP1 */
#else
#define IS_SMBUS_TRIG_INPUT_INSTANCE(__INSTANCE__)    IS_SMBUS_GRP1_INSTANCE(__INSTANCE__)
#endif /* SMBUS_TRIG_GRP2 */
#endif /* SMBUS_TRIG_GRP3 */

#define IS_SMBUS_AUTO_MODE_TRG_POL(__POLARITY__)      (((__POLARITY__) == SMBUS_TRIG_POLARITY_RISING) ||               \
                                                       ((__POLARITY__) == SMBUS_TRIG_POLARITY_FALLING))
/**
  * @}
  */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Functions SMBUS Extended Private Functions
  * @{
  */
/* Private functions are defined in stm32mp2xx_hal_smbus_ex.c file */
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

#endif /* STM32MP2xx_HAL_SMBUS_EX_H */
