/**
  **********************************************************************************************************************
  * @file    stm32g5xx_ll_dbgmcu.h
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
#ifndef STM32G5XX_LL_DBGMCU_H
#define STM32G5XX_LL_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
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
#define LL_DBGMCU_DEV_ID_G55X_G56X 0x044AU /*!< STM32G5 series device STM32G55X/56X */
#define LL_DBGMCU_DEV_ID_G53X_G54X 0x044BU /*!< STM32G5 series device STM32G53X/54X */
/**
  * @}
  */

/** @defgroup DBGMCU_REV_ID DBGMCU Device revision ID definition
  * @{
  */
#define LL_DBGMCU_REV_ID_A 0x1000U /*!< STM32G5 device revision A */
#define LL_DBGMCU_REV_ID_Z 0x1001U /*!< STM32G5 device revision Z */
/**
  * @}
  */

/** @defgroup DBGMCU_DEBUG_LOW_POWER_MODE DBGMCU Debug during low power mode
  * @{
  */
#define LL_DBGMCU_STOP_MODE_DEBUG    DBGMCU_CR_DBG_STOP     /*!< Debug during Stop mode    */
#define LL_DBGMCU_STANDBY_MODE_DEBUG DBGMCU_CR_DBG_STANDBY  /*!< Debug during Standby mode */
#define LL_DBGMCU_LP_MODE_DEBUG_ALL  (DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY)
/*!< Debug during Low power mode
 (Stop and Standby modes) */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_APB1_GRP1_STOP_IP DBGMCU APB1_GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_TIM2_STOP      DBGMCU_APB1FZR_DBG_TIM2_STOP  /*!< The counter clock of TIM2 is stopped when the core is in debug mode              */
#if defined(TIM3)
#define LL_DBGMCU_TIM3_STOP      DBGMCU_APB1FZR_DBG_TIM3_STOP  /*!< The counter clock of TIM3 is stopped when the core is in debug mode              */
#endif /* #if defined(TIM3) */
#define LL_DBGMCU_TIM6_STOP      DBGMCU_APB1FZR_DBG_TIM6_STOP  /*!< The counter clock of TIM6 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM7_STOP      DBGMCU_APB1FZR_DBG_TIM7_STOP  /*!< The counter clock of TIM7 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM9_STOP      DBGMCU_APB1FZR_DBG_TIM9_STOP  /*!< The counter clock of TIM9 is stopped when the core is in debug mode              */
#define LL_DBGMCU_TIM10_STOP     DBGMCU_APB1FZR_DBG_TIM10_STOP /*!< The counter clock of TIM10 is stopped when the core is in debug mode             */
#define LL_DBGMCU_TIM11_STOP     DBGMCU_APB1FZR_DBG_TIM11_STOP /*!< The counter clock of TIM11 is stopped when the core is in debug mode             */
#define LL_DBGMCU_TIM12_STOP     DBGMCU_APB1FZR_DBG_TIM12_STOP /*!< The counter clock of TIM12 is stopped when the core is in debug mode             */
#define LL_DBGMCU_TIM13_STOP     DBGMCU_APB1FZR_DBG_TIM13_STOP /*!< The counter clock of TIM13 is stopped when the core is in debug mode             */
#define LL_DBGMCU_TIM14_STOP     DBGMCU_APB1FZR_DBG_TIM14_STOP /*!< The counter clock of TIM14 is stopped when the core is in debug mode             */
#define LL_DBGMCU_WWDG_STOP      DBGMCU_APB1FZR_DBG_WWDG_STOP  /*!< The window watchdog counter clock is stopped when the core is in debug mode      */
#define LL_DBGMCU_IWDG_STOP      DBGMCU_APB1FZR_DBG_IWDG_STOP  /*!< The independent watchdog counter clock is stopped when the core is in debug mode */
#define LL_DBGMCU_I2C1_STOP      DBGMCU_APB1FZR_DBG_I2C1_STOP  /*!< The I2C1 SMBus timeout is frozen while the core is in debug mode                 */
#define LL_DBGMCU_I2C2_STOP      DBGMCU_APB1FZR_DBG_I2C2_STOP  /*!< The I2C2 SMBus timeout is frozen  while the core is in debug mode                */
#define LL_DBGMCU_I3C1_STOP      DBGMCU_APB1FZR_DBG_I3C1_STOP  /*!< The I3C1 timeout is frozen while the core is in debug mode                       */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_APB2_GRP1_STOP_IP DBGMCU APB2_GRP1 STOP IP
  * @{
  */
#if defined(HRTIM1)
#define LL_DBGMCU_HRTIM1_STOP    DBGMCU_APB2FZR_DBG_HRTIM1_STOP  /*!< The counter clock of HRTIM1 is stopped when the core is in debug mode */
#endif /* #if defined(HRTIM1) */
#define LL_DBGMCU_TIM1_STOP      DBGMCU_APB2FZR_DBG_TIM1_STOP    /*!< The counter clock of TIM1 is stopped when the core is in debug mode   */
#if defined(TIM4)
#define LL_DBGMCU_TIM4_STOP      DBGMCU_APB2FZR_DBG_TIM4_STOP    /*!< The counter clock of TIM4 is stopped when the core is in debug mode   */
#endif /* #if defined(TIM4) */
#if defined(TIM5)
#define LL_DBGMCU_TIM5_STOP      DBGMCU_APB2FZR_DBG_TIM5_STOP    /*!< The counter clock of TIM5 is stopped when the core is in debug mode   */
#endif /* #if defined(TIM5) */
#define LL_DBGMCU_TIM8_STOP      DBGMCU_APB2FZR_DBG_TIM8_STOP    /*!< The counter clock of TIM8 is stopped when the core is in debug mode   */
#define LL_DBGMCU_TIM15_STOP     DBGMCU_APB2FZR_DBG_TIM15_STOP   /*!< The counter clock of TIM15 is stopped when the core is in debug mode  */
#define LL_DBGMCU_TIM16_STOP     DBGMCU_APB2FZR_DBG_TIM16_STOP   /*!< The counter clock of TIM16 is stopped when the core is in debug mode  */
#define LL_DBGMCU_TIM17_STOP     DBGMCU_APB2FZR_DBG_TIM17_STOP   /*!< The counter clock of TIM17 is stopped when the core is in debug mode  */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_APB3_GRP1_STOP_IP DBGMCU APB3_GRP1 STOP IP
  * @{
  */
#if defined(TIM20)
#define LL_DBGMCU_TIM20_STOP     DBGMCU_APB3FZR_DBG_TIM20_STOP   /*!< The counter clock of TIM20 is stopped when the core is in debug mode  */
#endif /* #if defined(TIM20) */
#define LL_DBGMCU_TIM26_STOP     DBGMCU_APB3FZR_DBG_TIM26_STOP   /*!< The counter clock of TIM26 is stopped when the core is in debug mode  */
#define LL_DBGMCU_TIM27_STOP     DBGMCU_APB3FZR_DBG_TIM27_STOP   /*!< The counter clock of TIM27 is stopped when the core is in debug mode  */
#if defined(I2C3)
#define LL_DBGMCU_I2C3_STOP      DBGMCU_APB3FZR_DBG_I2C3_STOP    /*!< The I2C3 SMBus timeout is frozen  while the core is in debug mode     */
#endif /* #if defined(I2C3) */
#if defined(I2C4)
#define LL_DBGMCU_I2C4_STOP      DBGMCU_APB3FZR_DBG_I2C4_STOP    /*!< The I2C4 SMBus timeout is frozen  while the core is in debug mode     */
#endif /* #if defined(I2C4) */
#define LL_DBGMCU_LPTIM1_STOP    DBGMCU_APB3FZR_DBG_LPTIM1_STOP  /*!< The counter clock of LPTIM1 is stopped when the core is in debug mode */
#define LL_DBGMCU_RTC_STOP       DBGMCU_APB3FZR_DBG_RTC_STOP     /*!< The counter clock of RTC is stopped when the core is in debug mode    */
/**
  * @}
  */

/** @defgroup DBGMCU_LL_EC_AHB1_GRP1_STOP_IP DBGMCU AHB1_GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_GPDMA1_CH0_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_0_STOP  /*!< The counter clock of GPDMA1 channel 0 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH1_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_1_STOP  /*!< The counter clock of GPDMA1 channel 1 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH2_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_2_STOP  /*!< The counter clock of GPDMA1 channel 2 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH3_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_3_STOP  /*!< The counter clock of GPDMA1 channel 3 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH4_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_4_STOP  /*!< The counter clock of GPDMA1 channel 4 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA1_CH5_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_5_STOP  /*!< The counter clock of GPDMA1 channel 5 is stopped when the core is in debug mode */
#if defined(GPDMA1_CH6)
#define LL_DBGMCU_GPDMA1_CH6_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_6_STOP  /*!< The counter clock of GPDMA1 channel 6 is stopped when the core is in debug mode */
#endif /* GPDMA1_CH6 */
#if defined(GPDMA1_CH7)
#define LL_DBGMCU_GPDMA1_CH7_STOP    DBGMCU_AHB1FZR_DBG_GPDMA1_7_STOP  /*!< The counter clock of GPDMA1 channel 7 is stopped when the core is in debug mode */
#endif /* GPDMA1_CH7 */
#define LL_DBGMCU_GPDMA2_CH0_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_0_STOP  /*!< The counter clock of GPDMA2 channel 0 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA2_CH1_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_1_STOP  /*!< The counter clock of GPDMA2 channel 1 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA2_CH2_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_2_STOP  /*!< The counter clock of GPDMA2 channel 2 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA2_CH3_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_3_STOP  /*!< The counter clock of GPDMA2 channel 3 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA2_CH4_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_4_STOP  /*!< The counter clock of GPDMA2 channel 4 is stopped when the core is in debug mode */
#define LL_DBGMCU_GPDMA2_CH5_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_5_STOP  /*!< The counter clock of GPDMA2 channel 5 is stopped when the core is in debug mode */
#if defined(GPDMA2_CH6)
#define LL_DBGMCU_GPDMA2_CH6_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_6_STOP  /*!< The counter clock of GPDMA2 channel 6 is stopped when the core is in debug mode */
#endif /* GPDMA2_CH6 */
#if defined(GPDMA2_CH7)
#define LL_DBGMCU_GPDMA2_CH7_STOP    DBGMCU_AHB1FZR_DBG_GPDMA2_7_STOP  /*!< The counter clock of GPDMA2 channel 7 is stopped when the core is in debug mode */
#endif /* GPDMA2_CH7 */
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
  *         @arg @ref LL_DBGMCU_DEV_ID_G55X_G56X
  *         @arg @ref LL_DBGMCU_DEV_ID_G53X_G54X
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
  *         @arg @ref LL_DBGMCU_REV_ID_Z
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
  *  CR    DBG_STOP        LL_DBGMCU_EnableDebugLowPowerMode \n
  *  CR    DBG_STANDBY     LL_DBGMCU_EnableDebugLowPowerMode
  * @param mode This parameter can be one or a combination of the following values:
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
  *  CR    DBG_STOP        LL_DBGMCU_DisableDebugLowPowerMode \n
  *  CR    DBG_STANDBY     LL_DBGMCU_DisableDebugLowPowerMode
  * @param mode This parameter can be one or a combination of the following values:
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
  *  CR    DBG_STOP        LL_DBGMCU_IsEnabledDebugLowPowerMode \n
  *  CR    DBG_STANDBY     LL_DBGMCU_IsEnabledDebugLowPowerMode
  * @param mode This parameter can be one of the following values:
  *        @arg @ref LL_DBGMCU_STOP_MODE_DEBUG
  *        @arg @ref LL_DBGMCU_STANDBY_MODE_DEBUG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_DBGMCU_IsEnabledDebugLowPowerMode(uint32_t mode)
{
  return ((STM32_READ_BIT(DBGMCU->CR, mode) == (mode)) ? 1UL : 0UL);
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
  * @if (TIM3)
  *         @arg @ref LL_DBGMCU_TIM3_STOP  (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_TIM9_STOP
  *         @arg @ref LL_DBGMCU_TIM10_STOP
  *         @arg @ref LL_DBGMCU_TIM11_STOP
  *         @arg @ref LL_DBGMCU_TIM12_STOP
  *         @arg @ref LL_DBGMCU_TIM13_STOP
  *         @arg @ref LL_DBGMCU_TIM14_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  *         @arg @ref LL_DBGMCU_I2C1_STOP
  *         @arg @ref LL_DBGMCU_I2C2_STOP
  *         @arg @ref LL_DBGMCU_I3C1_STOP
  * @note   (*) value not defined in all devices.
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
  * @if (TIM3)
  *         @arg @ref LL_DBGMCU_TIM3_STOP  (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM6_STOP
  *         @arg @ref LL_DBGMCU_TIM7_STOP
  *         @arg @ref LL_DBGMCU_TIM9_STOP
  *         @arg @ref LL_DBGMCU_TIM10_STOP
  *         @arg @ref LL_DBGMCU_TIM11_STOP
  *         @arg @ref LL_DBGMCU_TIM12_STOP
  *         @arg @ref LL_DBGMCU_TIM13_STOP
  *         @arg @ref LL_DBGMCU_TIM14_STOP
  *         @arg @ref LL_DBGMCU_WWDG_STOP
  *         @arg @ref LL_DBGMCU_IWDG_STOP
  *         @arg @ref LL_DBGMCU_I2C1_STOP
  *         @arg @ref LL_DBGMCU_I2C2_STOP
  *         @arg @ref LL_DBGMCU_I3C1_STOP
  * @note   (*) value not defined in all devices.
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
  * @if (HRTIM1)
  *         @arg @ref LL_DBGMCU_HRTIM1_STOP (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  * @if (TIM4)
  *         @arg @ref LL_DBGMCU_TIM4_STOP   (*)
  * @endif
  * @if (TIM5)
  *         @arg @ref LL_DBGMCU_TIM5_STOP   (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM15_STOP
  *         @arg @ref LL_DBGMCU_TIM16_STOP
  *         @arg @ref LL_DBGMCU_TIM17_STOP
  * @note   (*) value not defined in all devices.
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
  * @if (HRTIM1)
  *         @arg @ref LL_DBGMCU_HRTIM1_STOP (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM1_STOP
  * @if (TIM4)
  *         @arg @ref LL_DBGMCU_TIM4_STOP   (*)
  * @endif
  * @if (TIM5)
  *         @arg @ref LL_DBGMCU_TIM5_STOP   (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM8_STOP
  *         @arg @ref LL_DBGMCU_TIM15_STOP
  *         @arg @ref LL_DBGMCU_TIM16_STOP
  *         @arg @ref LL_DBGMCU_TIM17_STOP
  * @note   (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->APB2FZR, periphs);
}

/**
  * @brief  Freeze APB3_GRP1 peripherals.
  * @rmtoll
  *  APB3FZR    DBG_XXXX_STOP    LL_DBGMCU_APB3_GRP1_FreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  * @if (TIM20)
  *         @arg @ref LL_DBGMCU_TIM20_STOP  (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM26_STOP
  *         @arg @ref LL_DBGMCU_TIM27_STOP
  * @if (I2C3)
  *         @arg @ref LL_DBGMCU_I2C3_STOP   (*)
  * @endif
  * @if (I2C4)
  *         @arg @ref LL_DBGMCU_I2C4_STOP   (*)
  * @endif
  *         @arg @ref LL_DBGMCU_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_RTC_STOP
  * @note   (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_FreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_SET_BIT_32(DBGMCU->APB3FZR, periphs);
}

/**
  * @brief  Unfreeze APB3_GRP1 peripherals.
  * @rmtoll
  *  APB3FZR    DBG_XXXX_STOP    LL_DBGMCU_APB3_GRP1_UnFreezePeriph
  * @param  periphs This parameter can be a combination of the following values:
  * @if (TIM20)
  *         @arg @ref LL_DBGMCU_TIM20_STOP  (*)
  * @endif
  *         @arg @ref LL_DBGMCU_TIM26_STOP
  *         @arg @ref LL_DBGMCU_TIM27_STOP
  * @if (I2C3)
  *         @arg @ref LL_DBGMCU_I2C3_STOP   (*)
  * @endif
  * @if (I2C4)
  *         @arg @ref LL_DBGMCU_I2C4_STOP   (*)
  * @endif
  *         @arg @ref LL_DBGMCU_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_RTC_STOP
  * @note   (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_UnFreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->APB3FZR, periphs);
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
  * @if (GPDMA1_CH6)
  *         @arg @ref LL_DBGMCU_GPDMA1_CH6_STOP  (*)
  * @endif
  * @if (GPDMA1_CH7)
  *         @arg @ref LL_DBGMCU_GPDMA1_CH7_STOP  (*)
  * @endif
  *         @arg @ref LL_DBGMCU_GPDMA2_CH0_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH1_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH2_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH3_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH4_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH5_STOP
  * @if (GPDMA2_CH6)
  *         @arg @ref LL_DBGMCU_GPDMA2_CH6_STOP  (*)
  * @endif
  * @if (GPDMA2_CH76)
  *         @arg @ref LL_DBGMCU_GPDMA2_CH7_STOP  (*)
  * @endif
  * @note   (*) value not defined in all devices.
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
  * @if (GPDMA1_CH6)
  *         @arg @ref LL_DBGMCU_GPDMA1_CH6_STOP  (*)
  * @endif
  * @if (GPDMA1_CH7)
  *         @arg @ref LL_DBGMCU_GPDMA1_CH7_STOP  (*)
  * @endif
  *         @arg @ref LL_DBGMCU_GPDMA2_CH0_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH1_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH2_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH3_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH4_STOP
  *         @arg @ref LL_DBGMCU_GPDMA2_CH5_STOP
  * @if (GPDMA2_CH6)
  *         @arg @ref LL_DBGMCU_GPDMA2_CH6_STOP  (*)
  * @endif
  * @if (GPDMA2_CH76)
  *         @arg @ref LL_DBGMCU_GPDMA2_CH7_STOP  (*)
  * @endif
  * @note   (*) value not defined in all devices.
  */
__STATIC_INLINE void LL_DBGMCU_AHB1_GRP1_UnFreezePeriph(uint32_t periphs)
{
  STM32_ATOMIC_CLEAR_BIT_32(DBGMCU->AHB1FZR, periphs);
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

#endif /* STM32G5XX_LL_DBGMCU_H */
