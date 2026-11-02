/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_ll_dbgmcu.h
  * @brief   Header file of LL DBGMCU module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_LL_DBGMCU_H
#define STM32H7PXX_LL_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

#if defined (DBGMCU)
/** @defgroup LL_DBGMCU LL DBGMCU
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup DBGMCU_LL_Exported_Constants LL DBGMCU Constants
  * @{
  */

/** @defgroup DBGMCU_DEV_ID DBGMCU Device ID definition
  * @{
  */
#define LL_DBGMCU_DEV_ID_H7P4X_H7P5X 0x047BU /*!< STM32H7P series device STM32H7P4X/5X */
/**
  * @}
  */

/** @defgroup DBGMCU_REV_ID DBGMCU Device revision ID definition
  * @{
  */
#define LL_DBGMCU_REV_ID_A 0x1000U /*!< STM32H7P device revision A */
#define LL_DBGMCU_REV_ID_Z 0x1001U /*!< STM32H7P device revision Z */
/**
  * @}
  */

/** @defgroup DBGMCU_DEBUG_LOW_POWER_MODE DBGMCU Debug during low power mode
  * @{
  */
#define LL_DBGMCU_SLEEP_MODE_DEBUG   DBGMCU_CR_DBG_SLEEP    /*!< Debug during Sleep mode   */
#define LL_DBGMCU_STOP_MODE_DEBUG    DBGMCU_CR_DBG_STOP     /*!< Debug during Stop mode    */
#define LL_DBGMCU_STANDBY_MODE_DEBUG DBGMCU_CR_DBG_STANDBY  /*!< Debug during Standby mode */
#define LL_DBGMCU_LP_MODE_DEBUG_ALL  (DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP  | \
                                      DBGMCU_CR_DBG_STANDBY)
/*!< Debug during Low power mode
 (Sleep, Stop and Standby modes) */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_APB1_GRP1_STOP_IP DBGMCU APB1_GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_TIM2_STOP      DBGMCU_APB1FZR_TIM2   /*!< The counter clock of TIM2 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM3_STOP      DBGMCU_APB1FZR_TIM3   /*!< The counter clock of TIM3 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM4_STOP      DBGMCU_APB1FZR_TIM4   /*!< The counter clock of TIM4 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM5_STOP      DBGMCU_APB1FZR_TIM5   /*!< The counter clock of TIM5 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM6_STOP      DBGMCU_APB1FZR_TIM6   /*!< The counter clock of TIM6 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM7_STOP      DBGMCU_APB1FZR_TIM7   /*!< The counter clock of TIM7 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM12_STOP     DBGMCU_APB1FZR_TIM12  /*!< The counter clock of TIM12 is stopped when the core is in debug mode             */
#define LL_DBGMCU_TIM13_STOP     DBGMCU_APB1FZR_TIM13  /*!< The counter clock of TIM13 is stopped when the core is in debug mode             */
#define LL_DBGMCU_TIM14_STOP     DBGMCU_APB1FZR_TIM14  /*!< The counter clock of TIM14 is stopped when the core is in debug mode             */
#define LL_DBGMCU_LPTIM1_STOP    DBGMCU_APB1FZR_LPTIM1 /*!< The counter clock of LPTIM1 is stopped when the core is in debug mode            */
#define LL_DBGMCU_WWDG_STOP      DBGMCU_APB1FZR_WWDG   /*!< The window watchdog counter clock is stopped when the core is in debug mode      */
#define LL_DBGMCU_TIM10_STOP     DBGMCU_APB1FZR_TIM10  /*!< The counter clock of TIM13 is stopped when the core is in debug mode             */
#define LL_DBGMCU_TIM11_STOP     DBGMCU_APB1FZR_TIM11  /*!< The counter clock of TIM14 is stopped when the core is in debug mode             */
#define LL_DBGMCU_I2C1_STOP      DBGMCU_APB1FZR_I2C1   /*!< The I2C1 SMBus timeout is frozen while the core is in debug mode                 */
#define LL_DBGMCU_I2C2_STOP      DBGMCU_APB1FZR_I2C2   /*!< The I2C2 SMBus timeout is frozen  while the core is in debug mode                */
#define LL_DBGMCU_I2C3_STOP      DBGMCU_APB1FZR_I2C3   /*!< The I2C2 SMBus timeout is frozen  while the core is in debug mode                */
#define LL_DBGMCU_I3C1_STOP      DBGMCU_APB1FZR_I3C1   /*!< The I3C1 timeout is frozen while the core is in debug mode                       */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_APB2_GRP1_STOP_IP DBGMCU APB2_GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_HRTIM1_STOP    DBGMCU_APB2FZR_HRTIM1  /*!< The counter clock of HRTIM1 is stopped when the core is in debug mode */
#define LL_DBGMCU_HRTIM2_STOP    DBGMCU_APB2FZR_HRTIM2  /*!< The counter clock of HRTIM2 is stopped when the core is in debug mode */
#define LL_DBGMCU_TIM1_STOP      DBGMCU_APB2FZR_TIM1    /*!< The counter clock of TIM1 is stopped when the core is in debug mode   */
#define LL_DBGMCU_TIM8_STOP      DBGMCU_APB2FZR_TIM8    /*!< The counter clock of TIM8 is stopped when the core is in debug mode   */
#define LL_DBGMCU_TIM15_STOP     DBGMCU_APB2FZR_TIM15   /*!< The counter clock of TIM15 is stopped when the core is in debug mode  */
#define LL_DBGMCU_TIM16_STOP     DBGMCU_APB2FZR_TIM16   /*!< The counter clock of TIM16 is stopped when the core is in debug mode  */
#define LL_DBGMCU_TIM17_STOP     DBGMCU_APB2FZR_TIM17   /*!< The counter clock of TIM17 is stopped when the core is in debug mode  */
#define LL_DBGMCU_TIM9_STOP      DBGMCU_APB2FZR_TIM9    /*!< The counter clock of TIM9 is stopped when the core is in debug mode  */
#define LL_DBGMCU_TIM20_STOP     DBGMCU_APB2FZR_TIM20   /*!< The counter clock of TIM20 is stopped when the core is in debug mode  */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_APB4_GRP1_STOP_IP DBGMCU APB4_GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_LPTIM2_STOP     DBGMCU_APB4FZR_LPTIM2   /*!< The counter clock of LPTIM2 is stopped when the core is in debug mode  */
#define LL_DBGMCU_LPTIM3_STOP     DBGMCU_APB4FZR_LPTIM3   /*!< The counter clock of LPTIM3 is stopped when the core is in debug mode  */
#define LL_DBGMCU_LPTIM4_STOP     DBGMCU_APB4FZR_LPTIM4   /*!< The counter clock of LPTIM4 is stopped when the core is in debug mode  */
#define LL_DBGMCU_LPTIM5_STOP     DBGMCU_APB4FZR_LPTIM5   /*!< The counter clock of LPTIM4 is stopped when the core is in debug mode  */
#define LL_DBGMCU_RTC_STOP        DBGMCU_APB4FZR_RTC      /*!< The counter clock of RTC is stopped when the core is in debug mode     */
#define LL_DBGMCU_IWDG_STOP       DBGMCU_APB4FZR_IWDG     /*!< The counter clock of IWDG is stopped when the core is in debug mode    */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_AHB1_GRP1_STOP_IP DBGMCU AHB1_GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_GPDMA1_CH0_STOP     DBGMCU_AHB1FZR_GPDMA_0   /*!< The counter clock of GPDMA1 channel 0 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH1_STOP     DBGMCU_AHB1FZR_GPDMA_1   /*!< The counter clock of GPDMA1 channel 1 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH2_STOP     DBGMCU_AHB1FZR_GPDMA_2   /*!< The counter clock of GPDMA1 channel 2 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH3_STOP     DBGMCU_AHB1FZR_GPDMA_3   /*!< The counter clock of GPDMA1 channel 3 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH4_STOP     DBGMCU_AHB1FZR_GPDMA_4   /*!< The counter clock of GPDMA1 channel 4 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH5_STOP     DBGMCU_AHB1FZR_GPDMA_5   /*!< The counter clock of GPDMA1 channel 5 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH6_STOP     DBGMCU_AHB1FZR_GPDMA_6   /*!< The counter clock of GPDMA1 channel 6 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH7_STOP     DBGMCU_AHB1FZR_GPDMA_7   /*!< The counter clock of GPDMA1 channel 7 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH8_STOP     DBGMCU_AHB1FZR_GPDMA_8   /*!< The counter clock of GPDMA1 channel 8 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH9_STOP     DBGMCU_AHB1FZR_GPDMA_9   /*!< The counter clock of GPDMA1 channel 9 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH10_STOP    DBGMCU_AHB1FZR_GPDMA_10  /*!< The counter clock of GPDMA1 channel 10 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH11_STOP    DBGMCU_AHB1FZR_GPDMA_11  /*!< The counter clock of GPDMA1 channel 11 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH12_STOP    DBGMCU_AHB1FZR_GPDMA_12  /*!< The counter clock of GPDMA1 channel 12 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH13_STOP    DBGMCU_AHB1FZR_GPDMA_13  /*!< The counter clock of GPDMA1 channel 13 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH14_STOP    DBGMCU_AHB1FZR_GPDMA_14  /*!< The counter clock of GPDMA1 channel 14 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH15_STOP    DBGMCU_AHB1FZR_GPDMA_15  /*!< The counter clock of GPDMA1 channel 15 is stopped when the core is in debug mode */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_AHB5_GRP1_STOP_IP DBGMCU AHB5_GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_HPDMA1_CH0_STOP     DBGMCU_AHB5FZR_HPDMA_0   /*!< The counter clock of GPDMA1 channel 0 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH1_STOP     DBGMCU_AHB5FZR_HPDMA_1   /*!< The counter clock of GPDMA1 channel 1 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH2_STOP     DBGMCU_AHB5FZR_HPDMA_2   /*!< The counter clock of GPDMA1 channel 2 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH3_STOP     DBGMCU_AHB5FZR_HPDMA_3   /*!< The counter clock of GPDMA1 channel 3 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH4_STOP     DBGMCU_AHB5FZR_HPDMA_4   /*!< The counter clock of GPDMA1 channel 4 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH5_STOP     DBGMCU_AHB5FZR_HPDMA_5   /*!< The counter clock of GPDMA1 channel 5 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH6_STOP     DBGMCU_AHB5FZR_HPDMA_6   /*!< The counter clock of GPDMA1 channel 6 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH7_STOP     DBGMCU_AHB5FZR_HPDMA_7   /*!< The counter clock of GPDMA1 channel 7 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH8_STOP     DBGMCU_AHB5FZR_HPDMA_8   /*!< The counter clock of GPDMA1 channel 8 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH9_STOP     DBGMCU_AHB5FZR_HPDMA_9   /*!< The counter clock of GPDMA1 channel 9 is stopped when the core is in debug mode  */
#define LL_DBGMCU_HPDMA1_CH10_STOP    DBGMCU_AHB5FZR_HPDMA_10  /*!< The counter clock of GPDMA1 channel 10 is stopped when the core is in debug mode */
#define LL_DBGMCU_HPDMA1_CH11_STOP    DBGMCU_AHB5FZR_HPDMA_11  /*!< The counter clock of GPDMA1 channel 11 is stopped when the core is in debug mode */
#define LL_DBGMCU_HPDMA1_CH12_STOP    DBGMCU_AHB5FZR_HPDMA_12  /*!< The counter clock of GPDMA1 channel 12 is stopped when the core is in debug mode */
#define LL_DBGMCU_HPDMA1_CH13_STOP    DBGMCU_AHB5FZR_HPDMA_13  /*!< The counter clock of GPDMA1 channel 13 is stopped when the core is in debug mode */
#define LL_DBGMCU_HPDMA1_CH14_STOP    DBGMCU_AHB5FZR_HPDMA_14  /*!< The counter clock of GPDMA1 channel 14 is stopped when the core is in debug mode */
#define LL_DBGMCU_HPDMA1_CH15_STOP    DBGMCU_AHB5FZR_HPDMA_15  /*!< The counter clock of GPDMA1 channel 15 is stopped when the core is in debug mode */
#if defined(NPU_PRESENT)
#define LL_DBGMCU_NPU_STOP            DBGMCU_AHB5FZR_NPU       /*!< The counter clock of NPU is stopped when the core is in debug mode               */
#endif /* NPU_PRESENT */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ------------------------------------------------------------*/
/** @defgroup DBGMCU_LL_Exported_Macros LL DBGMCU Macros
  * @{
  */

/** @defgroup DBGMCU_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value to the DBGMCU register.
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_DBGMCU_WRITE_REG(reg, value) STM32_WRITE_REG((DBGMCU->reg), (value))

/**
  * @brief  Read a value from the DBGMCU register.
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_DBGMCU_READ_REG(reg) STM32_READ_REG(DBGMCU->reg)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup DBGMCU_LL_Exported_Functions LL DBGMCU Functions
  * @{
  */

/** @defgroup DBGMCU_LL_EF_ID LL DBGMCU Identifications
  * @{
  */

/**
  * @brief  Return the device identifier.
  * @rmtoll
  *  IDCODE    DEV_ID    LL_DBGMCU_GetDeviceID
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DBGMCU_DEV_ID_H7P4X_H7P5X
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDeviceID(void)
{
  return (uint32_t)(STM32_READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier.
  * @rmtoll
  *  IDCODE    REV_ID    LL_DBGMCU_GetRevisionID
  * @note This field indicates the revision of the device.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DBGMCU_REV_ID_A
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(STM32_READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @}
  */

/** @defgroup DBGMCU_LL_EF_LOW_POWER_MODE LL DBGMCU Debug Low power mode
  * @{
  */

/**
  * @brief  Enable the debug module during low power mode.
  * @rmtoll
  *  CR    DBG_SLEEP       LL_DBGMCU_EnableDebugLowPowerMode \n
  *  CR    DBG_STOP        LL_DBGMCU_EnableDebugLowPowerMode \n
  *  CR    DBG_STANDBY     LL_DBGMCU_EnableDebugLowPowerMode
  * @param mode This parameter can be one or a combination of the following values:
  *        @arg @ref LL_DBGMCU_SLEEP_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_STOP_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_STANDBY_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_LP_MODE_DEBUG_ALL
  */
__STATIC_INLINE void LL_DBGMCU_EnableDebugLowPowerMode(uint32_t mode)
{
  STM32_SET_BIT(DBGMCU->CR, mode);
}

/**
  * @brief  Disable the debug module during low power mode.
  * @rmtoll
  *  CR    DBG_SLEEP       LL_DBGMCU_DisableDebugLowPowerMode \n
  *  CR    DBG_STOP        LL_DBGMCU_DisableDebugLowPowerMode \n
  *  CR    DBG_STANDBY     LL_DBGMCU_DisableDebugLowPowerMode
  * @param mode This parameter can be one or a combination of the following values:
  *        @arg @ref LL_DBGMCU_SLEEP_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_STOP_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_STANDBY_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_LP_MODE_DEBUG_ALL
  */
__STATIC_INLINE void LL_DBGMCU_DisableDebugLowPowerMode(uint32_t mode)
{
  STM32_CLEAR_BIT(DBGMCU->CR, mode);
}

/**
  * @brief  Check whether the debug module during low power mode is enabled.
  * @rmtoll
  *  CR    DBG_SLEEP       LL_DBGMCU_IsEnabledDebugLowPowerMode \n
  *  CR    DBG_STOP        LL_DBGMCU_IsEnabledDebugLowPowerMode \n
  *  CR    DBG_STANDBY     LL_DBGMCU_IsEnabledDebugLowPowerMode
  * @param mode This parameter can be one of the following values:
  *        @arg @ref LL_DBGMCU_SLEEP_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_STOP_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_STANDBY_MODE_DEBUG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDebugLowPowerMode(uint32_t mode)
{
  return ((STM32_READ_BIT(DBGMCU->CR, mode) == (mode)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the debug module during Sleep mode.
  * @rmtoll
  *  CR    DBG_SLEEP    LL_DBGMCU_EnableDBGSleepMode
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  STM32_SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the debug module during Sleep mode.
  * @rmtoll
  *  CR    DBG_SLEEP    LL_DBGMCU_DisableDBGSleepMode
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  STM32_CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Check whether the debug module during Sleep mode is enabled.
  * @rmtoll
  *  CR    DBG_SLEEP    LL_DBGMCU_IsEnabledDBGSleepMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGSleepMode(void)
{
  return ((STM32_READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP) == (DBGMCU_CR_DBG_SLEEP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the debug module during Stop mode.
  * @rmtoll
  *  CR    DBG_STOP    LL_DBGMCU_EnableDBGStopMode
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  STM32_SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the debug module during Stop mode.
  * @rmtoll
  *  CR    DBG_STOP    LL_DBGMCU_DisableDBGStopMode
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  STM32_CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Check whether the debug module during Stop mode is enabled.
  * @rmtoll
  *  CR    DBG_STOP    LL_DBGMCU_IsEnabledDBGStopMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStopMode(void)
{
  return ((STM32_READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP) == (DBGMCU_CR_DBG_STOP)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the debug module during Standby mode.
  * @rmtoll
  *  CR    DBG_STANDBY    LL_DBGMCU_EnableDBGStandbyMode
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStandbyMode(void)
{
  STM32_SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the debug module during Standby mode.
  * @rmtoll
  *  CR    DBG_STANDBY    LL_DBGMCU_DisableDBGStandbyMode
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStandbyMode(void)
{
  STM32_CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Check whether the debug module during Standby mode is enabled.
  * @rmtoll
  *  CR    DBG_STANDBY    LL_DBGMCU_IsEnabledDBGStandbyMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDBGStandbyMode(void)
{
  return ((STM32_READ_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY) == (DBGMCU_CR_DBG_STANDBY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup DBGMCU_LL_EF_FREEZE_UNFREEZE LL DBGMCU Freeze/Unfreeze
  * @{
  */

/**
  * @brief  Freeze APB1_GRP1 peripherals.
  * @rmtoll
  *  APB1FZR    DBG_xxxx_STOP    LL_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_TIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM3_STOP
  *         @arg @ref LL_DBGMCU_TIM4_STOP
  *         @arg @ref LL_DBGMCU_TIM5_STOP
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_TIM10_STOP
  *         @arg @ref LL_DBGMCU_TIM11_STOP
  *         @arg @ref LL_DBGMCU_TIM12_STOP
  *         @arg @ref LL_DBGMCU_TIM13_STOP
  *         @arg @ref LL_DBGMCU_TIM14_STOP
  *         @arg @ref LL_DBGMCU_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_I2C1_STOP
  *         @arg @ref LL_DBGMCU_I2C2_STOP
  *         @arg @ref LL_DBGMCU_I2C3_STOP
  *         @arg @ref LL_DBGMCU_I3C1_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_SET_BIT_32(DBGMCU->APB1FZR, periphs);
}

/**
  * @brief  Unfreeze APB1_GRP1 peripherals.
  * @rmtoll
  *  APB1FZR    DBG_xxxx_STOP    LL_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_TIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM3_STOP
  *         @arg @ref LL_DBGMCU_TIM4_STOP
  *         @arg @ref LL_DBGMCU_TIM5_STOP
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_TIM10_STOP
  *         @arg @ref LL_DBGMCU_TIM11_STOP
  *         @arg @ref LL_DBGMCU_TIM12_STOP
  *         @arg @ref LL_DBGMCU_TIM13_STOP
  *         @arg @ref LL_DBGMCU_TIM14_STOP
  *         @arg @ref LL_DBGMCU_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_I2C1_STOP
  *         @arg @ref LL_DBGMCU_I2C2_STOP
  *         @arg @ref LL_DBGMCU_I2C3_STOP
  *         @arg @ref LL_DBGMCU_I3C1_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->APB1FZR, periphs);
}

/**
  * @brief  Freeze APB2_GRP1 peripherals.
  * @rmtoll
  *  APB2FZR    DBG_XXXX_STOP    LL_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_HRTIM1_STOP
  *         @arg @ref LL_DBGMCU_HRTIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM9_STOP
  *         @arg @ref LL_DBGMCU_TIM15_STOP
  *         @arg @ref LL_DBGMCU_TIM16_STOP
  *         @arg @ref LL_DBGMCU_TIM17_STOP
  *         @arg @ref LL_DBGMCU_TIM20_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_SET_BIT_32(DBGMCU->APB2FZR, periphs);
}

/**
  * @brief  Unfreeze APB2_GRP1 peripherals.
  * @rmtoll
  *  APB2FZR    DBG_XXXX_STOP    LL_DBGMCU_APB2_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_HRTIM1_STOP
  *         @arg @ref LL_DBGMCU_HRTIM2_STOP
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM9_STOP
  *         @arg @ref LL_DBGMCU_TIM15_STOP
  *         @arg @ref LL_DBGMCU_TIM16_STOP
  *         @arg @ref LL_DBGMCU_TIM17_STOP
  *         @arg @ref LL_DBGMCU_TIM20_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->APB2FZR, periphs);
}

/**
  * @brief  Freeze APB4_GRP1 peripherals.
  * @rmtoll
  *  APB4FZR    DBG_XXXX_STOP    LL_DBGMCU_APB4_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_RTC_STOP
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_FreezePeriph(uint32_t Periphs)
{
  STM32_ATOMIC_SET_BIT_32(DBGMCU->APB4FZR, Periphs);
}

/**
  * @brief  Unfreeze APB4_GRP1 peripherals.
  * @rmtoll
  *  APB4FZR    DBG_XXXX_STOP    LL_DBGMCU_APB4_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_RTC_STOP
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->APB4FZR, Periphs);
}

/**
  * @brief  Freeze AHB1_GRP1 peripherals.
  * @rmtoll
  *  AHB1FZR    DBG_XXXX_STOP    LL_DBGMCU_AHB1_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_GPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH15_STOP
  */
__STATIC_INLINE void LL_DBGMCU_AHB1_GRP1_FreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_SET_BIT_32(DBGMCU->AHB1FZR, periphs);
}

/**
  * @brief  Unfreeze  peripherals.
  * @rmtoll
  *  AHB1FZR    DBG_XXXX_STOP    LL_DBGMCU_AHB1_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_GPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_GPDMA1_CH15_STOP
  */
__STATIC_INLINE void LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->AHB1FZR, periphs);
}

/**
  * @brief  Freeze AHB5_GRP1 peripherals.
  * @rmtoll
  *  AHB5FZR    DBG_XXXX_STOP    LL_DBGMCU_AHB5_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_HPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH15_STOP
  *         @arg @ref LL_DBGMCU_NPU_STOP (*)
  *
  * @note   (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_DBGMCU_AHB5_GRP1_FreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_SET_BIT_32(DBGMCU->AHB5FZR, periphs);
}

/**
  * @brief  Unfreeze AHB5_GRP1 peripherals.
  * @rmtoll
  *  AHB5FZR    DBG_XXXX_STOP    LL_DBGMCU_AHB5_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_HPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_HPDMA1_CH15_STOP
  *         @arg @ref LL_DBGMCU_NPU_STOP (*)
  *
  * @note   (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_DBGMCU_AHB5_GRP1_UnFreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->AHB5FZR, periphs);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* DBGMCU */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_LL_DBGMCU_H */
