/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_gpio.h
  * @brief   Header file of GPIO HAL module.
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
#ifndef STM32H7PXX_HAL_GPIO_H
#define STM32H7PXX_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_gpio.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined (GPIOA) || defined (GPIOB) || defined (GPIOC) || defined (GPIOD) || defined (GPIOE)  || defined (GPIOF) \
    || defined (GPIOG) || defined (GPIOH) || defined (GPIOI)

/** @defgroup GPIO GPIO
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/

/** @defgroup GPIO_Exported_Types HAL GPIO Types
  * @{
  */

/**
  * @brief HAL GPIO instance
  */
typedef enum
{
  HAL_GPIOA = GPIOA_BASE,     /*!< GPIO port A. */
  HAL_GPIOB = GPIOB_BASE,     /*!< GPIO port B. */
  HAL_GPIOC = GPIOC_BASE,     /*!< GPIO port C. */
  HAL_GPIOD = GPIOD_BASE,     /*!< GPIO port D. */
  HAL_GPIOE = GPIOE_BASE,     /*!< GPIO port E. */
  HAL_GPIOF = GPIOF_BASE,     /*!< GPIO port F. */
  HAL_GPIOG = GPIOG_BASE,     /*!< GPIO port G. */
  HAL_GPIOH = GPIOH_BASE,     /*!< GPIO port H. */
  HAL_GPIOI = GPIOI_BASE,     /*!< GPIO port I. */
} hal_gpio_t;

/**
  * @brief HAL GPIO mode
  */
typedef enum
{
  HAL_GPIO_MODE_INPUT     =  LL_GPIO_MODE_INPUT,      /*!< Input Floating mode. */
  HAL_GPIO_MODE_OUTPUT    =  LL_GPIO_MODE_OUTPUT,     /*!< Output mode.         */
  HAL_GPIO_MODE_ALTERNATE =  LL_GPIO_MODE_ALTERNATE,  /*!< Alternate mode.      */
  HAL_GPIO_MODE_ANALOG    =  LL_GPIO_MODE_ANALOG      /*!< Analog mode.         */
} hal_gpio_mode_t;

/**
  * @brief HAL GPIO Output Type.
  */
typedef enum
{
  HAL_GPIO_OUTPUT_PUSHPULL  = LL_GPIO_OUTPUT_PUSHPULL,   /*!< Select push-pull as output type.  */
  HAL_GPIO_OUTPUT_OPENDRAIN = LL_GPIO_OUTPUT_OPENDRAIN   /*!< Select open-drain as output type. */
} hal_gpio_output_t;

/**
  * @brief HAL GPIO speed.
  * @note  Refer to the device datasheet for the frequency specifications, and the power supply and load conditions
  *        for each speed.
  */
typedef enum
{
  HAL_GPIO_SPEED_FREQ_LOW        = LL_GPIO_SPEED_FREQ_LOW,        /*!< Low speed.       */
  HAL_GPIO_SPEED_FREQ_MEDIUM     = LL_GPIO_SPEED_FREQ_MEDIUM,     /*!< Medium speed.    */
  HAL_GPIO_SPEED_FREQ_HIGH       = LL_GPIO_SPEED_FREQ_HIGH,       /*!< High speed.      */
  HAL_GPIO_SPEED_FREQ_VERY_HIGH  = LL_GPIO_SPEED_FREQ_VERY_HIGH   /*!< Very-high speed. */
} hal_gpio_speed_freq_t;

/**
  * @brief HAL GPIO pull
  */
typedef enum
{
  HAL_GPIO_PULL_NO   = LL_GPIO_PULL_NO,   /*!< No Pull-up or Pull-down activation.  */
  HAL_GPIO_PULL_UP   = LL_GPIO_PULL_UP,   /*!< Pull-up activation.                  */
  HAL_GPIO_PULL_DOWN = LL_GPIO_PULL_DOWN  /*!< Pull-down activation.                */
} hal_gpio_pull_t;

/**
  * @brief HAL GPIO Alternate function.
  */
typedef enum
{
  HAL_GPIO_AF_0  = LL_GPIO_AF_0,  /*!< Select alternate function 0.  */
  HAL_GPIO_AF_1  = LL_GPIO_AF_1,  /*!< Select alternate function 1.  */
  HAL_GPIO_AF_2  = LL_GPIO_AF_2,  /*!< Select alternate function 2.  */
  HAL_GPIO_AF_3  = LL_GPIO_AF_3,  /*!< Select alternate function 3.  */
  HAL_GPIO_AF_4  = LL_GPIO_AF_4,  /*!< Select alternate function 4.  */
  HAL_GPIO_AF_5  = LL_GPIO_AF_5,  /*!< Select alternate function 5.  */
  HAL_GPIO_AF_6  = LL_GPIO_AF_6,  /*!< Select alternate function 6.  */
  HAL_GPIO_AF_7  = LL_GPIO_AF_7,  /*!< Select alternate function 7.  */
  HAL_GPIO_AF_8  = LL_GPIO_AF_8,  /*!< Select alternate function 8.  */
  HAL_GPIO_AF_9  = LL_GPIO_AF_9,  /*!< Select alternate function 9.  */
  HAL_GPIO_AF_10 = LL_GPIO_AF_10, /*!< Select alternate function 10. */
  HAL_GPIO_AF_11 = LL_GPIO_AF_11, /*!< Select alternate function 11. */
  HAL_GPIO_AF_12 = LL_GPIO_AF_12, /*!< Select alternate function 12. */
  HAL_GPIO_AF_13 = LL_GPIO_AF_13, /*!< Select alternate function 13. */
  HAL_GPIO_AF_14 = LL_GPIO_AF_14, /*!< Select alternate function 14. */
  HAL_GPIO_AF_15 = LL_GPIO_AF_15  /*!< Select alternate function 15. */
} hal_gpio_af_t;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration.
  */
typedef enum
{
  HAL_GPIO_PIN_RESET = LL_GPIO_PIN_RESET,  /*!< Pin state is reset/low. */
  HAL_GPIO_PIN_SET   = LL_GPIO_PIN_SET     /*!< Pin state is set/high.  */
} hal_gpio_pin_state_t;

/**
  * @brief   GPIO Init structure definition.
  */
typedef struct
{
  hal_gpio_mode_t       mode;            /*!< Specifies the operating mode for the selected pins. */
  hal_gpio_pull_t       pull;            /*!< Specifies the Pull-up or Pull-Down activation for the selected pins. */
  hal_gpio_speed_freq_t speed;           /*!< Specifies the speed for the selected pins. */
  hal_gpio_output_t     output_type;     /*!< Specifies the operating output type for the selected pins. */
  hal_gpio_af_t         alternate;       /*!< Specifies the alternate function for the selected pins. */
  hal_gpio_pin_state_t  init_state;      /*!< Specifies the initial state Set or Reset for the selected pins. */
} hal_gpio_config_t;

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants HAL GPIO Constants
  * @{
  */

/** @defgroup GPIO_pins GPIO pins
  * @{
  */

#define HAL_GPIO_PIN_0                 LL_GPIO_PIN_0    /*!< GPIO pin 0.  */
#define HAL_GPIO_PIN_1                 LL_GPIO_PIN_1    /*!< GPIO pin 1.  */
#define HAL_GPIO_PIN_2                 LL_GPIO_PIN_2    /*!< GPIO pin 2.  */
#define HAL_GPIO_PIN_3                 LL_GPIO_PIN_3    /*!< GPIO pin 3.  */
#define HAL_GPIO_PIN_4                 LL_GPIO_PIN_4    /*!< GPIO pin 4.  */
#define HAL_GPIO_PIN_5                 LL_GPIO_PIN_5    /*!< GPIO pin 5.  */
#define HAL_GPIO_PIN_6                 LL_GPIO_PIN_6    /*!< GPIO pin 6.  */
#define HAL_GPIO_PIN_7                 LL_GPIO_PIN_7    /*!< GPIO pin 7.  */
#define HAL_GPIO_PIN_8                 LL_GPIO_PIN_8    /*!< GPIO pin 8.  */
#define HAL_GPIO_PIN_9                 LL_GPIO_PIN_9    /*!< GPIO pin 9.  */
#define HAL_GPIO_PIN_10                LL_GPIO_PIN_10   /*!< GPIO pin 10. */
#define HAL_GPIO_PIN_11                LL_GPIO_PIN_11   /*!< GPIO pin 11. */
#define HAL_GPIO_PIN_12                LL_GPIO_PIN_12   /*!< GPIO pin 12. */
#define HAL_GPIO_PIN_13                LL_GPIO_PIN_13   /*!< GPIO pin 13. */
#define HAL_GPIO_PIN_14                LL_GPIO_PIN_14   /*!< GPIO pin 14. */
#define HAL_GPIO_PIN_15                LL_GPIO_PIN_15   /*!< GPIO pin 15. */
#define HAL_GPIO_PIN_ALL               LL_GPIO_PIN_ALL  /*!< All GPIO pins. */
/**
  * @}
  */

/** @defgroup GPIO_Alternates GPIO Alternates
  * @{
  */
/**
  * @brief   AF 0 selection
  */
#define HAL_GPIO_AF0_AUDIOCLK            HAL_GPIO_AF_0  /*!< Audio Clock                       */
#define HAL_GPIO_AF0_DBTRGI              HAL_GPIO_AF_0  /*!< DBTRGI                            */
#define HAL_GPIO_AF0_DBTRGIO             HAL_GPIO_AF_0  /*!< DBTRGIO                           */
#define HAL_GPIO_AF0_DBTRGO              HAL_GPIO_AF_0  /*!< DBTRGO                            */
#define HAL_GPIO_AF0_JTCK                HAL_GPIO_AF_0  /*!< JTAG Test Clock                   */
#define HAL_GPIO_AF0_JTDI                HAL_GPIO_AF_0  /*!< JTAG Test Data In                 */
#define HAL_GPIO_AF0_JTDO                HAL_GPIO_AF_0  /*!< JTAG Test Data Out                */
#define HAL_GPIO_AF0_JTMS                HAL_GPIO_AF_0  /*!< JTAG Test Mode Select             */
#define HAL_GPIO_AF0_MCO                 HAL_GPIO_AF_0  /*!< MCO Alternate Function mapping    */
#define HAL_GPIO_AF0_MCO1                HAL_GPIO_AF_0  /*!< MCO1                              */
#define HAL_GPIO_AF0_MCO2                HAL_GPIO_AF_0  /*!< MCO2                              */
#define HAL_GPIO_AF0_NJTRST              HAL_GPIO_AF_0  /*!< NJTRST                            */
#define HAL_GPIO_AF0_PWR                 HAL_GPIO_AF_0  /*!< PWR Alternate Function mapping    */
#define HAL_GPIO_AF0_PWR_CSLEEP          HAL_GPIO_AF_0  /*!< PWR CSLEEP mode                   */
#define HAL_GPIO_AF0_PWR_CSTOP           HAL_GPIO_AF_0  /*!< PWR CSTOP mode                    */
#define HAL_GPIO_AF0_RTC                 HAL_GPIO_AF_0  /*!< RTC Alternate Function mapping    */
#define HAL_GPIO_AF0_RTC_OUT2            HAL_GPIO_AF_0  /*!< RTC Output 2                      */
#define HAL_GPIO_AF0_RTC_REFIN           HAL_GPIO_AF_0  /*!< RTC Reference input               */
#define HAL_GPIO_AF0_SWCLK               HAL_GPIO_AF_0  /*!< Serial Wire Clock                 */
#define HAL_GPIO_AF0_SWDIO               HAL_GPIO_AF_0  /*!< Serial Wire Debug Input/Output    */
#define HAL_GPIO_AF0_TRACECLK            HAL_GPIO_AF_0  /*!< TRACE Clock                       */
#define HAL_GPIO_AF0_TRACED0             HAL_GPIO_AF_0  /*!< TRACE Data Output 0               */
#define HAL_GPIO_AF0_TRACED1             HAL_GPIO_AF_0  /*!< TRACE Data Output 1               */
#define HAL_GPIO_AF0_TRACED2             HAL_GPIO_AF_0  /*!< TRACE Data Output 2               */
#define HAL_GPIO_AF0_TRACED3             HAL_GPIO_AF_0  /*!< TRACE Data Output 3               */
#define HAL_GPIO_AF0_TRACESWO            HAL_GPIO_AF_0  /*!< TRACE Serial Wire Output          */

/**
  * @brief   AF 1 selection
  */
#define HAL_GPIO_AF1_HRTIM1              HAL_GPIO_AF_1 /*!< HRTIM1 Alternate Function mapping      */
#define HAL_GPIO_AF1_HRTIM1_CHB1         HAL_GPIO_AF_1 /*!< HRTIM1 Timer B Output 1                */
#define HAL_GPIO_AF1_HRTIM1_CHC1         HAL_GPIO_AF_1 /*!< HRTIM1 Timer C Output 1                */
#define HAL_GPIO_AF1_HRTIM1_CHC2         HAL_GPIO_AF_1 /*!< HRTIM1 Timer C Output 2                */
#define HAL_GPIO_AF1_HRTIM1_EEV1         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 1               */
#define HAL_GPIO_AF1_HRTIM1_EEV2         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 2               */
#define HAL_GPIO_AF1_HRTIM1_EEV4         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 4               */
#define HAL_GPIO_AF1_HRTIM1_EEV5         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 5               */
#define HAL_GPIO_AF1_HRTIM1_EEV6         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 6               */
#define HAL_GPIO_AF1_HRTIM1_EEV7         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 7               */
#define HAL_GPIO_AF1_HRTIM1_EEV8         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 8               */
#define HAL_GPIO_AF1_HRTIM1_EEV9         HAL_GPIO_AF_1 /*!< HRTIM1  External Event 9               */
#define HAL_GPIO_AF1_HRTIM1_EEV10        HAL_GPIO_AF_1 /*!< HRTIM1  External Event 10              */
#define HAL_GPIO_AF1_HRTIM1_EEV11        HAL_GPIO_AF_1 /*!< HRTIM1  External Event 11              */
#define HAL_GPIO_AF1_HRTIM1_FLT1         HAL_GPIO_AF_1 /*!< HRTIM1  Fault 1                        */
#define HAL_GPIO_AF1_HRTIM1_FLT2         HAL_GPIO_AF_1 /*!< HRTIM1  Fault 2                        */
#define HAL_GPIO_AF1_HRTIM1_FLT3         HAL_GPIO_AF_1 /*!< HRTIM1  Fault 3                        */
#define HAL_GPIO_AF1_HRTIM1_FLT4         HAL_GPIO_AF_1 /*!< HRTIM1  Fault 4                        */
#define HAL_GPIO_AF1_HRTIM1_FLT5         HAL_GPIO_AF_1 /*!< HRTIM1  Fault 5                        */
#define HAL_GPIO_AF1_HRTIM1_FLT6         HAL_GPIO_AF_1 /*!< HRTIM1  Fault 6                        */
#define HAL_GPIO_AF1_HRTIM1_FLT7         HAL_GPIO_AF_1 /*!< HRTIM1  Fault 7                        */
#define HAL_GPIO_AF1_HRTIM1_SCIN         HAL_GPIO_AF_1 /*!< HRTIM1  Synchronization Input          */
#define HAL_GPIO_AF1_HRTIM1_SCOUT        HAL_GPIO_AF_1 /*!< HRTIM1  Synchronization Output         */
#define HAL_GPIO_AF1_HRTIM2              HAL_GPIO_AF_1 /*!< HRTIM2 Alternate Function mapping      */
#define HAL_GPIO_AF1_HRTIM2_CHA1         HAL_GPIO_AF_1 /*!< HRTIM2 Timer A Output 1                */
#define HAL_GPIO_AF1_HRTIM2_CHA2         HAL_GPIO_AF_1 /*!< HRTIM2 Timer A Output 2                */
#define HAL_GPIO_AF1_HRTIM2_CHB1         HAL_GPIO_AF_1 /*!< HRTIM2 Timer B Output 1                */
#define HAL_GPIO_AF1_HRTIM2_CHB2         HAL_GPIO_AF_1 /*!< HRTIM2 Timer B Output 2                */
#define HAL_GPIO_AF1_HRTIM2_CHC2         HAL_GPIO_AF_1 /*!< HRTIM2 Timer C Output 2                */
#define HAL_GPIO_AF1_HRTIM2_CHD1         HAL_GPIO_AF_1 /*!< HRTIM2 Timer D Output 1                */
#define HAL_GPIO_AF1_HRTIM2_CHD2         HAL_GPIO_AF_1 /*!< HRTIM2 Timer D Output 2                */
#define HAL_GPIO_AF1_HRTIM2_CHE1         HAL_GPIO_AF_1 /*!< HRTIM2 Timer E Output 1                */
#define HAL_GPIO_AF1_HRTIM2_CHE2         HAL_GPIO_AF_1 /*!< HRTIM2 Timer E Output 2                */
#define HAL_GPIO_AF1_HRTIM2_CHF1         HAL_GPIO_AF_1 /*!< HRTIM2 Timer F Output 1                */
#define HAL_GPIO_AF1_HRTIM2_CHF2         HAL_GPIO_AF_1 /*!< HRTIM2 Timer F Output 2                */
#define HAL_GPIO_AF1_HRTIM2_EEV1         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 1               */
#define HAL_GPIO_AF1_HRTIM2_EEV2         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 2               */
#define HAL_GPIO_AF1_HRTIM2_EEV3         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 3               */
#define HAL_GPIO_AF1_HRTIM2_EEV4         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 4               */
#define HAL_GPIO_AF1_HRTIM2_EEV5         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 5               */
#define HAL_GPIO_AF1_HRTIM2_EEV6         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 6               */
#define HAL_GPIO_AF1_HRTIM2_EEV8         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 8               */
#define HAL_GPIO_AF1_HRTIM2_EEV9         HAL_GPIO_AF_1 /*!< HRTIM2  External Event 9               */
#define HAL_GPIO_AF1_HRTIM2_EEV10        HAL_GPIO_AF_1 /*!< HRTIM2  External Event 10              */
#define HAL_GPIO_AF1_HRTIM2_EEV13        HAL_GPIO_AF_1 /*!< HRTIM2  External Event 13              */
#define HAL_GPIO_AF1_HRTIM2_FLT1         HAL_GPIO_AF_1 /*!< HRTIM2  Fault 1                        */
#define HAL_GPIO_AF1_HRTIM2_FLT3         HAL_GPIO_AF_1 /*!< HRTIM2  Fault 3                        */
#define HAL_GPIO_AF1_HRTIM2_FLT4         HAL_GPIO_AF_1 /*!< HRTIM2  Fault 4                        */
#define HAL_GPIO_AF1_HRTIM2_FLT5         HAL_GPIO_AF_1 /*!< HRTIM2  Fault 5                        */
#define HAL_GPIO_AF1_HRTIM2_FLT6         HAL_GPIO_AF_1 /*!< HRTIM2  Fault 6                        */
#define HAL_GPIO_AF1_I3C1                HAL_GPIO_AF_1 /*!< I3C1 Alternate Function mapping        */
#define HAL_GPIO_AF1_I3C1_SCL            HAL_GPIO_AF_1 /*!< I3C1 Clock                             */
#define HAL_GPIO_AF1_I3C1_SDA            HAL_GPIO_AF_1 /*!< I3C1 Data                              */
#define HAL_GPIO_AF1_LPTIM1              HAL_GPIO_AF_1 /*!< LPTIM1 Alternate Function mapping      */
#define HAL_GPIO_AF1_LPTIM1_CH1          HAL_GPIO_AF_1 /*!< LPTIM1 Multi-purpose Channel 1         */
#define HAL_GPIO_AF1_LPTIM1_CH2          HAL_GPIO_AF_1 /*!< LPTIM1 Multi-purpose Channel 2         */
#define HAL_GPIO_AF1_LPTIM1_ETR          HAL_GPIO_AF_1 /*!< LPTIM1 External trigger input          */
#define HAL_GPIO_AF1_LPTIM1_IN2          HAL_GPIO_AF_1 /*!< LPTIM1 Channel 2 Input                 */
#define HAL_GPIO_AF1_SDMMC1              HAL_GPIO_AF_1 /*!< SDMMC1 Alternate Function mapping      */
#define HAL_GPIO_AF1_SDMMC1_CK           HAL_GPIO_AF_1 /*!< SDMMC1 Card clock                      */
#define HAL_GPIO_AF1_SDMMC1_D5           HAL_GPIO_AF_1 /*!< SDMMC1 Card bidirectional data line 5  */
#define HAL_GPIO_AF1_TIM1                HAL_GPIO_AF_1 /*!< TIM1 Alternate Function mapping        */
#define HAL_GPIO_AF1_TIM1_BKIN2          HAL_GPIO_AF_1 /*!< TIM1 Break input 2                     */
#define HAL_GPIO_AF1_TIM1_CH1            HAL_GPIO_AF_1 /*!< TIM1 Multi-purpose Channel 1           */
#define HAL_GPIO_AF1_TIM1_CH2            HAL_GPIO_AF_1 /*!< TIM1 Multi-purpose Channel 2           */
#define HAL_GPIO_AF1_TIM1_CH3            HAL_GPIO_AF_1 /*!< TIM1 Multi-purpose Channel 3           */
#define HAL_GPIO_AF1_TIM1_CH4N           HAL_GPIO_AF_1 /*!< TIM1 CH4 complementary output          */
#define HAL_GPIO_AF1_TIM1_ETR            HAL_GPIO_AF_1 /*!< TIM1 External trigger input            */
#define HAL_GPIO_AF1_TIM2                HAL_GPIO_AF_1 /*!< TIM2 Alternate Function mapping        */
#define HAL_GPIO_AF1_TIM2_CH1            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 1           */
#define HAL_GPIO_AF1_TIM2_CH2            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 2           */
#define HAL_GPIO_AF1_TIM2_CH3            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 3           */
#define HAL_GPIO_AF1_TIM2_CH4            HAL_GPIO_AF_1 /*!< TIM2 Multi-purpose Channel 4           */
#define HAL_GPIO_AF1_TIM5                HAL_GPIO_AF_1 /*!< TIM5 Alternate Function mapping        */
#define HAL_GPIO_AF1_TIM5_CH3            HAL_GPIO_AF_1 /*!< TIM5 Multi-purpose Channel 3           */
#define HAL_GPIO_AF1_TIM5_ETR            HAL_GPIO_AF_1 /*!< TIM5 External trigger input            */
#define HAL_GPIO_AF1_TIM15               HAL_GPIO_AF_1 /*!< TIM15 Alternate Function mapping       */
#define HAL_GPIO_AF1_TIM15_BKIN          HAL_GPIO_AF_1 /*!< TIM15 Break input                      */
#define HAL_GPIO_AF1_TIM15_CH1           HAL_GPIO_AF_1 /*!< TIM15 Multi-purpose Channel 1          */
#define HAL_GPIO_AF1_TIM15_CH2           HAL_GPIO_AF_1 /*!< TIM15 Multi-purpose Channel 2          */
#define HAL_GPIO_AF1_TIM16               HAL_GPIO_AF_1 /*!< TIM16 Alternate Function mapping       */
#define HAL_GPIO_AF1_TIM16_CH1           HAL_GPIO_AF_1 /*!< TIM16 Multi-purpose Channel 1          */
#define HAL_GPIO_AF1_TIM16_CH1N          HAL_GPIO_AF_1 /*!< TIM16 CH1 complementary output         */
#define HAL_GPIO_AF1_TIM16_BKIN          HAL_GPIO_AF_1 /*!< TIM16 Break input                      */
#define HAL_GPIO_AF1_TIM17               HAL_GPIO_AF_1 /*!< TIM17 Alternate Function mapping       */
#define HAL_GPIO_AF1_TIM17_BKIN          HAL_GPIO_AF_1 /*!< TIM17 Break input                      */
#define HAL_GPIO_AF1_TIM17_CH1           HAL_GPIO_AF_1 /*!< TIM17 Multi-purpose Channel 1          */

/**
  * @brief   AF 2 selection
  */
#define HAL_GPIO_AF2_HRTIM2              HAL_GPIO_AF_2 /*!< HRTIM2 Alternate Function mapping      */
#define HAL_GPIO_AF2_HRTIM2_EEV1         HAL_GPIO_AF_2 /*!< HRTIM2  External Event 1               */
#define HAL_GPIO_AF2_HRTIM2_EEV2         HAL_GPIO_AF_2 /*!< HRTIM2  External Event 2               */
#define HAL_GPIO_AF2_HRTIM2_EEV3         HAL_GPIO_AF_2 /*!< HRTIM2  External Event 3               */
#define HAL_GPIO_AF2_HRTIM2_EEV4         HAL_GPIO_AF_2 /*!< HRTIM2  External Event 4               */
#define HAL_GPIO_AF2_HRTIM2_EEV5         HAL_GPIO_AF_2 /*!< HRTIM2  External Event 5               */
#define HAL_GPIO_AF2_HRTIM2_EEV8         HAL_GPIO_AF_2 /*!< HRTIM2  External Event 8               */
#define HAL_GPIO_AF2_HRTIM2_EEV9         HAL_GPIO_AF_2 /*!< HRTIM2  External Event 9               */
#define HAL_GPIO_AF2_HRTIM2_EEV10        HAL_GPIO_AF_2 /*!< HRTIM2  External Event 10              */
#define HAL_GPIO_AF2_HRTIM2_EEV11        HAL_GPIO_AF_2 /*!< HRTIM2  External Event 11              */
#define HAL_GPIO_AF2_HRTIM2_EEV12        HAL_GPIO_AF_2 /*!< HRTIM2  External Event 12              */
#define HAL_GPIO_AF2_HRTIM2_EEV15        HAL_GPIO_AF_2 /*!< HRTIM2  External Event 15              */
#define HAL_GPIO_AF2_HRTIM2_FLT2         HAL_GPIO_AF_2 /*!< HRTIM2  Fault 2                        */
#define HAL_GPIO_AF2_HRTIM2_FLT3         HAL_GPIO_AF_2 /*!< HRTIM2  Fault 3                        */
#define HAL_GPIO_AF2_HRTIM2_FLT4         HAL_GPIO_AF_2 /*!< HRTIM2  Fault 4                        */
#define HAL_GPIO_AF2_HRTIM2_FLT5         HAL_GPIO_AF_2 /*!< HRTIM2  Fault 5                        */
#define HAL_GPIO_AF2_HRTIM2_FLT8         HAL_GPIO_AF_2 /*!< HRTIM2  Fault 8                        */
#define HAL_GPIO_AF2_HRTIM2_SCIN         HAL_GPIO_AF_2 /*!< HRTIM2  Synchronization Input          */
#define HAL_GPIO_AF2_HRTIM2_SCOUT        HAL_GPIO_AF_2 /*!< HRTIM2  Synchronization Output         */
#define HAL_GPIO_AF2_I2C2                HAL_GPIO_AF_2 /*!< I2C2 Alternate Function mapping        */
#define HAL_GPIO_AF2_I2C2_SMBA           HAL_GPIO_AF_2 /*!< I2C2 SMBus Alert                       */
#define HAL_GPIO_AF2_I2S1                HAL_GPIO_AF_2 /*!< I2S1 Alternate Function mapping        */
#define HAL_GPIO_AF2_I2S1_CK             HAL_GPIO_AF_2 /*!< I2S1 Clock                             */
#define HAL_GPIO_AF2_I2S1_SDI            HAL_GPIO_AF_2 /*!< I2S1 Serial Data Input                 */
#define HAL_GPIO_AF2_I2S1_SDO            HAL_GPIO_AF_2 /*!< I2S1 Serial Data Output                */
#define HAL_GPIO_AF2_I2S1_WS             HAL_GPIO_AF_2 /*!< I2S1 Word Select                       */
#define HAL_GPIO_AF2_SPI1                HAL_GPIO_AF_2 /*!< SPI1 Alternate Function mapping        */
#define HAL_GPIO_AF2_SPI1_MISO           HAL_GPIO_AF_2 /*!< SPI1 Master-In/Slave-Out               */
#define HAL_GPIO_AF2_SPI1_MOSI           HAL_GPIO_AF_2 /*!< SPI1 Master-Out/Slave-In               */
#define HAL_GPIO_AF2_SPI1_NSS            HAL_GPIO_AF_2 /*!< SPI1 Slave Selection                   */
#define HAL_GPIO_AF2_SPI1_RDY            HAL_GPIO_AF_2 /*!< SPI1 Ready                             */
#define HAL_GPIO_AF2_SPI1_SCK            HAL_GPIO_AF_2 /*!< SPI1 Serial Clock                      */
#define HAL_GPIO_AF2_TIM1                HAL_GPIO_AF_2 /*!< TIM1 Alternate Function mapping        */
#define HAL_GPIO_AF2_TIM1_BKIN           HAL_GPIO_AF_2 /*!< TIM1 Break input                       */
#define HAL_GPIO_AF2_TIM1_BKIN2          HAL_GPIO_AF_2 /*!< TIM1 Break input 2                     */
#define HAL_GPIO_AF2_TIM1_CH1            HAL_GPIO_AF_2 /*!< TIM1 Multi-purpose Channel 1           */
#define HAL_GPIO_AF2_TIM1_CH1N           HAL_GPIO_AF_2 /*!< TIM1 CH1 complementary output          */
#define HAL_GPIO_AF2_TIM1_CH2            HAL_GPIO_AF_2 /*!< TIM1 Multi-purpose Channel 2           */
#define HAL_GPIO_AF2_TIM1_CH2N           HAL_GPIO_AF_2 /*!< TIM1 CH2 complementary output          */
#define HAL_GPIO_AF2_TIM1_CH3            HAL_GPIO_AF_2 /*!< TIM1 Multi-purpose Channel 3           */
#define HAL_GPIO_AF2_TIM1_CH3N           HAL_GPIO_AF_2 /*!< TIM1 CH3 complementary output          */
#define HAL_GPIO_AF2_TIM1_CH4            HAL_GPIO_AF_2 /*!< TIM1 Multi-purpose Channel 4           */
#define HAL_GPIO_AF2_TIM1_ETR            HAL_GPIO_AF_2 /*!< TIM1 External trigger input            */
#define HAL_GPIO_AF2_TIM2                HAL_GPIO_AF_2 /*!< TIM2 Alternate Function mapping        */
#define HAL_GPIO_AF2_TIM2_CH1            HAL_GPIO_AF_2 /*!< TIM2 Multi-purpose Channel 1           */
#define HAL_GPIO_AF2_TIM2_CH2            HAL_GPIO_AF_2 /*!< TIM2 Multi-purpose Channel 2           */
#define HAL_GPIO_AF2_TIM2_CH3            HAL_GPIO_AF_2 /*!< TIM2 Multi-purpose Channel 3           */
#define HAL_GPIO_AF2_TIM2_ETR            HAL_GPIO_AF_2 /*!< TIM2 External trigger input            */
#define HAL_GPIO_AF2_TIM3                HAL_GPIO_AF_2 /*!< TIM3 Alternate Function mapping        */
#define HAL_GPIO_AF2_TIM3_CH1            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 1           */
#define HAL_GPIO_AF2_TIM3_CH2            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 2           */
#define HAL_GPIO_AF2_TIM3_CH3            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 3           */
#define HAL_GPIO_AF2_TIM3_CH4            HAL_GPIO_AF_2 /*!< TIM3 Multi-purpose Channel 4           */
#define HAL_GPIO_AF2_TIM3_ETR            HAL_GPIO_AF_2 /*!< TIM3 External trigger input            */
#define HAL_GPIO_AF2_TIM4                HAL_GPIO_AF_2 /*!< TIM4 Alternate Function mapping        */
#define HAL_GPIO_AF2_TIM4_CH1            HAL_GPIO_AF_2 /*!< TIM4 Multi-purpose Channel 1           */
#define HAL_GPIO_AF2_TIM4_CH2            HAL_GPIO_AF_2 /*!< TIM4 Multi-purpose Channel 2           */
#define HAL_GPIO_AF2_TIM4_CH3            HAL_GPIO_AF_2 /*!< TIM4 Multi-purpose Channel 3           */
#define HAL_GPIO_AF2_TIM4_CH4            HAL_GPIO_AF_2 /*!< TIM4 Multi-purpose Channel 4           */
#define HAL_GPIO_AF2_TIM4_ETR            HAL_GPIO_AF_2 /*!< TIM4 External trigger input            */
#define HAL_GPIO_AF2_TIM5                HAL_GPIO_AF_2 /*!< TIM5 Alternate Function mapping        */
#define HAL_GPIO_AF2_TIM5_CH1            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 1           */
#define HAL_GPIO_AF2_TIM5_CH2            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 2           */
#define HAL_GPIO_AF2_TIM5_CH3            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 3           */
#define HAL_GPIO_AF2_TIM5_CH4            HAL_GPIO_AF_2 /*!< TIM5 Multi-purpose Channel 4           */
#define HAL_GPIO_AF2_TIM15               HAL_GPIO_AF_2 /*!< TIM15 Alternate Function mapping       */
#define HAL_GPIO_AF2_TIM15_BKIN          HAL_GPIO_AF_2 /*!< TIM15 Break input                      */
#define HAL_GPIO_AF2_TIM15_CH1N          HAL_GPIO_AF_2 /*!< TIM15 CH1 complementary output         */

/**
  * @brief   AF 3 selection
  */
#define HAL_GPIO_AF3_HRTIM1              HAL_GPIO_AF_3 /*!< HRTIM1 Alternate Function mapping                      */
#define HAL_GPIO_AF3_HRTIM1_FLT6         HAL_GPIO_AF_3 /*!< HRTIM1  Fault 6                                        */
#define HAL_GPIO_AF3_HRTIM2              HAL_GPIO_AF_3 /*!< HRTIM2 Alternate Function mapping                      */
#define HAL_GPIO_AF3_HRTIM2_EEV6         HAL_GPIO_AF_3 /*!< HRTIM2  External Event 6                               */
#define HAL_GPIO_AF3_HRTIM2_EEV12        HAL_GPIO_AF_3 /*!< HRTIM2  External Event 12                              */
#define HAL_GPIO_AF3_HRTIM2_EEV13        HAL_GPIO_AF_3 /*!< HRTIM2  External Event 13                              */
#define HAL_GPIO_AF3_HRTIM2_EEV14        HAL_GPIO_AF_3 /*!< HRTIM2  External Event 14                              */
#define HAL_GPIO_AF3_HRTIM2_EEV16        HAL_GPIO_AF_3 /*!< HRTIM2  External Event 16                              */
#define HAL_GPIO_AF3_HRTIM2_FLT1         HAL_GPIO_AF_3 /*!< HRTIM2  Fault 1                                        */
#define HAL_GPIO_AF3_HRTIM2_FLT3         HAL_GPIO_AF_3 /*!< HRTIM2  Fault 3                                        */
#define HAL_GPIO_AF3_I2C3                HAL_GPIO_AF_3 /*!< I2C3 Alternate Function mapping                        */
#define HAL_GPIO_AF3_I2C3_SCL            HAL_GPIO_AF_3 /*!< I2C3 Clock                                             */
#define HAL_GPIO_AF3_I3C1                HAL_GPIO_AF_3 /*!< I3C1 Alternate Function mapping                        */
#define HAL_GPIO_AF3_I3C1_SCL            HAL_GPIO_AF_3 /*!< I3C1 Clock                                             */
#define HAL_GPIO_AF3_I3C1_SDA            HAL_GPIO_AF_3 /*!< I3C1 Data                                              */
#define HAL_GPIO_AF3_LPTIM2              HAL_GPIO_AF_3 /*!< LPTIM2 Alternate Function mapping                      */
#define HAL_GPIO_AF3_LPTIM2_CH1          HAL_GPIO_AF_3 /*!< LPTIM2 Multi-purpose Channel 1                         */
#define HAL_GPIO_AF3_LPTIM2_CH2          HAL_GPIO_AF_3 /*!< LPTIM2 Multi-purpose Channel 2                         */
#define HAL_GPIO_AF3_LPTIM2_ETR          HAL_GPIO_AF_3 /*!< LPTIM2 External trigger input                          */
#define HAL_GPIO_AF3_LPTIM2_IN1          HAL_GPIO_AF_3 /*!< LPTIM2 Channel 1 Input                                 */
#define HAL_GPIO_AF3_LPTIM2_IN2          HAL_GPIO_AF_3 /*!< LPTIM2 Channel 2 Input                                 */
#define HAL_GPIO_AF3_LPUART1             HAL_GPIO_AF_3 /*!< LPUART1 Alternate Function mapping                     */
#define HAL_GPIO_AF3_LPUART1_CTS         HAL_GPIO_AF_3 /*!< LPUART1 Clear to send                                  */
#define HAL_GPIO_AF3_LPUART1_RTS         HAL_GPIO_AF_3 /*!< LPUART1 Request to send                                */
#define HAL_GPIO_AF3_LPUART1_RX          HAL_GPIO_AF_3 /*!< LPUART1 Serial Data Receive Input                      */
#define HAL_GPIO_AF3_LPUART1_TX          HAL_GPIO_AF_3 /*!< LPUART1 Transmit Data Output                           */
#define HAL_GPIO_AF3_SDMMC1              HAL_GPIO_AF_3 /*!< SDMMC1 Alternate Function mapping                      */
#define HAL_GPIO_AF3_SDMMC1_D1           HAL_GPIO_AF_3 /*!< SDMMC1 Card bidirectional data line 1                  */
#define HAL_GPIO_AF3_SDMMC1_D123DIR      HAL_GPIO_AF_3 /*!< SDMMC1 Card I/O data lines 1,2,3 direction indication  */
#define HAL_GPIO_AF3_TIM8                HAL_GPIO_AF_3 /*!< TIM8 Alternate Function mapping                        */
#define HAL_GPIO_AF3_TIM8_BKIN           HAL_GPIO_AF_3 /*!< TIM8 Break input                                       */
#define HAL_GPIO_AF3_TIM8_BKIN2          HAL_GPIO_AF_3 /*!< TIM8 Break input 2                                     */
#define HAL_GPIO_AF3_TIM8_CH1            HAL_GPIO_AF_3 /*!< TIM8 Multi-purpose Channel 1                           */
#define HAL_GPIO_AF3_TIM8_CH1N           HAL_GPIO_AF_3 /*!< TIM8 CH1 complementary output                          */
#define HAL_GPIO_AF3_TIM8_CH2N           HAL_GPIO_AF_3 /*!< TIM8 CH2 complementary output                          */
#define HAL_GPIO_AF3_TIM8_CH3            HAL_GPIO_AF_3 /*!< TIM8 Multi-purpose Channel 3                           */
#define HAL_GPIO_AF3_TIM8_CH4N           HAL_GPIO_AF_3 /*!< TIM8 CH4 complementary output                          */
#define HAL_GPIO_AF3_TIM15               HAL_GPIO_AF_3 /*!< TIM15 Alternate Function mapping                       */
#define HAL_GPIO_AF3_TIM15_CH1           HAL_GPIO_AF_3 /*!< TIM15 Multi-purpose Channel 1                          */
#define HAL_GPIO_AF3_TIM15_CH2           HAL_GPIO_AF_3 /*!< TIM15 Multi-purpose Channel 2                          */
#define HAL_GPIO_AF3_USART6              HAL_GPIO_AF_3 /*!< USART6 Alternate Function mapping                      */
#define HAL_GPIO_AF3_USART6_CK           HAL_GPIO_AF_3 /*!< USART6 Clock                                           */
#define HAL_GPIO_AF3_USART6_CTS          HAL_GPIO_AF_3 /*!< USART6 Clear to send                                   */
#define HAL_GPIO_AF3_USART6_NSS          HAL_GPIO_AF_3 /*!< USART6 Slave Selection                                 */
#define HAL_GPIO_AF3_USART6_RTS          HAL_GPIO_AF_3 /*!< USART6 Request to send                                 */
#define HAL_GPIO_AF3_USART6_RX           HAL_GPIO_AF_3 /*!< USART6 Serial Data Receive Input                       */
#define HAL_GPIO_AF3_USART6_TX           HAL_GPIO_AF_3 /*!< USART6 Transmit Data Output                            */
#define HAL_GPIO_AF3_XSPI1               HAL_GPIO_AF_3 /*!< XSPI1 Alternate Function mapping                       */
#define HAL_GPIO_AF3_XSPI1_CLK           HAL_GPIO_AF_3 /*!< XSPI1 Clock                                            */
#define HAL_GPIO_AF3_XSPI1_DQS0          HAL_GPIO_AF_3 /*!< XSPI1 Memory Data Strobe I/O                           */
#define HAL_GPIO_AF3_XSPI1_IO0           HAL_GPIO_AF_3 /*!< XSPI1 Data Pin 0                                       */
#define HAL_GPIO_AF3_XSPI1_IO1           HAL_GPIO_AF_3 /*!< XSPI1 Data Pin 1                                       */
#define HAL_GPIO_AF3_XSPI1_IO2           HAL_GPIO_AF_3 /*!< XSPI1 Data Pin 2                                       */
#define HAL_GPIO_AF3_XSPI1_IO3           HAL_GPIO_AF_3 /*!< XSPI1 Data Pin 3                                       */
#define HAL_GPIO_AF3_XSPI1_IO4           HAL_GPIO_AF_3 /*!< XSPI1 Data Pin 4                                       */
#define HAL_GPIO_AF3_XSPI1_IO5           HAL_GPIO_AF_3 /*!< XSPI1 Data Pin 5                                       */
#define HAL_GPIO_AF3_XSPI1_NCLK          HAL_GPIO_AF_3 /*!< XSPI1 Inverted Clock                                   */
#define HAL_GPIO_AF3_XSPI1_NCS1          HAL_GPIO_AF_3 /*!< XSPI1 Memory Chip Select 1                             */
#define HAL_GPIO_AF3_XSPI1_NCS2          HAL_GPIO_AF_3 /*!< XSPI1 Memory Chip Select 2                             */

/**
  * @brief   AF 4 selection
  */
#define HAL_GPIO_AF4_HSP1                HAL_GPIO_AF_4 /*!< HSP1 Alternate Function mapping                   */
#define HAL_GPIO_AF4_HSP1_SNP0           HAL_GPIO_AF_4 /*!< HSP1 Snap or Sample Point 0                       */
#define HAL_GPIO_AF4_HSP1_SNP1           HAL_GPIO_AF_4 /*!< HSP1 Snap or Sample Point 1                       */
#define HAL_GPIO_AF4_HSP1_SNP3           HAL_GPIO_AF_4 /*!< HSP1 Snap or Sample Point 3                       */
#define HAL_GPIO_AF4_HSP1_SNP4           HAL_GPIO_AF_4 /*!< HSP1 Snap or Sample Point 4                       */
#define HAL_GPIO_AF4_HSP1_SNP5           HAL_GPIO_AF_4 /*!< HSP1 Snap or Sample Point 5                       */
#define HAL_GPIO_AF4_I2C1                HAL_GPIO_AF_4 /*!< I2C1 Alternate Function mapping                   */
#define HAL_GPIO_AF4_I2C1_SCL            HAL_GPIO_AF_4 /*!< I2C1 Clock                                        */
#define HAL_GPIO_AF4_I2C1_SDA            HAL_GPIO_AF_4 /*!< I2C1 Data                                         */
#define HAL_GPIO_AF4_I2C2                HAL_GPIO_AF_4 /*!< I2C2 Alternate Function mapping                   */
#define HAL_GPIO_AF4_I2C2_SCL            HAL_GPIO_AF_4 /*!< I2C2 Clock                                        */
#define HAL_GPIO_AF4_I2C2_SDA            HAL_GPIO_AF_4 /*!< I2C2 Data                                         */
#define HAL_GPIO_AF4_I2C2_SMBA           HAL_GPIO_AF_4 /*!< I2C2 SMBus Alert                                  */
#define HAL_GPIO_AF4_I2C3                HAL_GPIO_AF_4 /*!< I2C3 Alternate Function mapping                   */
#define HAL_GPIO_AF4_I2C3_SCL            HAL_GPIO_AF_4 /*!< I2C3 Clock                                        */
#define HAL_GPIO_AF4_I2C3_SDA            HAL_GPIO_AF_4 /*!< I2C3 Data                                         */
#define HAL_GPIO_AF4_I2C3_SMBA           HAL_GPIO_AF_4 /*!< I2C3 SMBus Alert                                  */
#define HAL_GPIO_AF4_LPTIM5              HAL_GPIO_AF_4 /*!< LPTIM5 Alternate Function mapping                 */
#define HAL_GPIO_AF4_LPTIM5_IN1          HAL_GPIO_AF_4 /*!< LPTIM5 Channel 1 Input                            */
#define HAL_GPIO_AF4_TIM2                HAL_GPIO_AF_4 /*!< TIM2 Alternate Function mapping                   */
#define HAL_GPIO_AF4_TIM2_ETR            HAL_GPIO_AF_4 /*!< TIM2 External trigger input                       */
#define HAL_GPIO_AF4_TIM5                HAL_GPIO_AF_4 /*!< TIM5 Alternate Function mapping                   */
#define HAL_GPIO_AF4_TIM5_CH1            HAL_GPIO_AF_4 /*!< TIM5 Multi-purpose Channel 1                      */
#define HAL_GPIO_AF4_TIM5_CH2            HAL_GPIO_AF_4 /*!< TIM5 Multi-purpose Channel 2                      */
#define HAL_GPIO_AF4_TIM5_CH3            HAL_GPIO_AF_4 /*!< TIM5 Multi-purpose Channel 3                      */
#define HAL_GPIO_AF4_TIM5_CH4            HAL_GPIO_AF_4 /*!< TIM5 Multi-purpose Channel 4                      */
#define HAL_GPIO_AF4_TIM8                HAL_GPIO_AF_4 /*!< TIM8 Alternate Function mapping                   */
#define HAL_GPIO_AF4_TIM8_BKIN           HAL_GPIO_AF_4 /*!< TIM8 Break input                                  */
#define HAL_GPIO_AF4_TIM8_BKIN2          HAL_GPIO_AF_4 /*!< TIM8 Break input 2                                */
#define HAL_GPIO_AF4_TIM8_CH1            HAL_GPIO_AF_4 /*!< TIM8 Multi-purpose Channel 1                      */
#define HAL_GPIO_AF4_TIM8_CH1N           HAL_GPIO_AF_4 /*!< TIM8 CH1 complementary output                     */
#define HAL_GPIO_AF4_TIM8_CH2N           HAL_GPIO_AF_4 /*!< TIM8 CH2 complementary output                     */
#define HAL_GPIO_AF4_TIM8_CH3            HAL_GPIO_AF_4 /*!< TIM8 Multi-purpose Channel 3                      */
#define HAL_GPIO_AF4_TIM8_CH3N           HAL_GPIO_AF_4 /*!< TIM8 CH3 complementary output                     */
#define HAL_GPIO_AF4_TIM8_CH4            HAL_GPIO_AF_4 /*!< TIM8 Multi-purpose Channel 4                      */
#define HAL_GPIO_AF4_TIM8_ETR            HAL_GPIO_AF_4 /*!< TIM8 External trigger input                       */
#define HAL_GPIO_AF4_TIM11               HAL_GPIO_AF_4 /*!< TIM11 Alternate Function mapping                  */
#define HAL_GPIO_AF4_TIM11_CH1           HAL_GPIO_AF_4 /*!< TIM11 Multi-purpose Channel 1                     */
#define HAL_GPIO_AF4_TIM14               HAL_GPIO_AF_4 /*!< TIM14 Alternate Function mapping                  */
#define HAL_GPIO_AF4_TIM14_CH1           HAL_GPIO_AF_4 /*!< TIM14 Multi-purpose Channel 1                     */
#define HAL_GPIO_AF4_TIM16               HAL_GPIO_AF_4 /*!< TIM16 Alternate Function mapping                  */
#define HAL_GPIO_AF4_TIM16_BKIN          HAL_GPIO_AF_4 /*!< TIM16 Break input                                 */
#define HAL_GPIO_AF4_TIM17               HAL_GPIO_AF_4 /*!< TIM17 Alternate Function mapping                  */
#define HAL_GPIO_AF4_TIM17_CH1           HAL_GPIO_AF_4 /*!< TIM17 Multi-purpose Channel 1                     */
#define HAL_GPIO_AF4_USART1              HAL_GPIO_AF_4 /*!< USART1 Alternate Function mapping                 */
#define HAL_GPIO_AF4_USART1_CK           HAL_GPIO_AF_4 /*!< USART1 Clock                                      */
#define HAL_GPIO_AF4_USART1_CTS          HAL_GPIO_AF_4 /*!< USART1 Clear to send                              */
#define HAL_GPIO_AF4_USART1_NSS          HAL_GPIO_AF_4 /*!< USART1 Slave Selection                            */
#define HAL_GPIO_AF4_USART1_RX           HAL_GPIO_AF_4 /*!< USART1 Serial Data Receive Input                  */
#define HAL_GPIO_AF4_USART1_TX           HAL_GPIO_AF_4 /*!< USART1 Transmit Data Output                       */
#define HAL_GPIO_AF4_USART6              HAL_GPIO_AF_4 /*!< USART6 Alternate Function mapping                 */
#define HAL_GPIO_AF4_USART6_CK           HAL_GPIO_AF_4 /*!< USART6 Clock                                      */

/**
  * @brief   AF 5 selection
  */
#define HAL_GPIO_AF5_FMC                 HAL_GPIO_AF_5 /*!< FMC Alternate Function mapping                    */
#define HAL_GPIO_AF5_FMC_NBL0            HAL_GPIO_AF_5 /*!< FMC Byte lane output 0                            */
#define HAL_GPIO_AF5_I2C2                HAL_GPIO_AF_5 /*!< I2C2 Alternate Function mapping                   */
#define HAL_GPIO_AF5_I2C2_SCL            HAL_GPIO_AF_5 /*!< I2C2 Clock                                        */
#define HAL_GPIO_AF5_I2C2_SDA            HAL_GPIO_AF_5 /*!< I2C2 Data                                         */
#define HAL_GPIO_AF5_I2C2_SMBA           HAL_GPIO_AF_5 /*!< I2C2 SMBus Alert                                  */
#define HAL_GPIO_AF5_I2S1                HAL_GPIO_AF_5 /*!< I2S1 Alternate Function mapping                   */
#define HAL_GPIO_AF5_I2S1_CK             HAL_GPIO_AF_5 /*!< I2S1 Clock                                        */
#define HAL_GPIO_AF5_I2S1_MCK            HAL_GPIO_AF_5 /*!< I2S1 Master Clock                                 */
#define HAL_GPIO_AF5_I2S1_SDI            HAL_GPIO_AF_5 /*!< I2S1 Serial Data Input                            */
#define HAL_GPIO_AF5_I2S1_SDO            HAL_GPIO_AF_5 /*!< I2S1 Serial Data Output                           */
#define HAL_GPIO_AF5_I2S1_WS             HAL_GPIO_AF_5 /*!< I2S1 Word Select                                  */
#define HAL_GPIO_AF5_I2S2                HAL_GPIO_AF_5 /*!< I2S2 Alternate Function mapping                   */
#define HAL_GPIO_AF5_I2S2_CK             HAL_GPIO_AF_5 /*!< I2S2 Clock                                        */
#define HAL_GPIO_AF5_I2S2_MCK            HAL_GPIO_AF_5 /*!< I2S2 Master Clock                                 */
#define HAL_GPIO_AF5_I2S2_SDI            HAL_GPIO_AF_5 /*!< I2S2 Serial Data Input                            */
#define HAL_GPIO_AF5_I2S2_SDO            HAL_GPIO_AF_5 /*!< I2S2 Serial Data Output                           */
#define HAL_GPIO_AF5_I2S2_WS             HAL_GPIO_AF_5 /*!< I2S2 Word Select                                  */
#define HAL_GPIO_AF5_I3C1                HAL_GPIO_AF_5 /*!< I3C1 Alternate Function mapping                   */
#define HAL_GPIO_AF5_I3C1_SCL            HAL_GPIO_AF_5 /*!< I3C1 Clock                                        */
#define HAL_GPIO_AF5_I3C1_SDA            HAL_GPIO_AF_5 /*!< I3C1 Data                                         */
#define HAL_GPIO_AF5_LPTIM1              HAL_GPIO_AF_5 /*!< LPTIM1 Alternate Function mapping                 */
#define HAL_GPIO_AF5_LPTIM1_CH1          HAL_GPIO_AF_5 /*!< LPTIM1 Multi-purpose Channel 1                    */
#define HAL_GPIO_AF5_LPTIM1_IN1          HAL_GPIO_AF_5 /*!< LPTIM1 Channel 1 Input                            */
#define HAL_GPIO_AF5_LPTIM1_IN2          HAL_GPIO_AF_5 /*!< LPTIM1 Channel 2 Input                            */
#define HAL_GPIO_AF5_SDMMC1              HAL_GPIO_AF_5 /*!< SDMMC1 Alternate Function mapping                 */
#define HAL_GPIO_AF5_SDMMC1_CMD          HAL_GPIO_AF_5 /*!< SDMMC1 Card bidirectional command/response signal */
#define HAL_GPIO_AF5_SDMMC1_D0           HAL_GPIO_AF_5 /*!< SDMMC1 Card bidirectional data line 0             */
#define HAL_GPIO_AF5_SDMMC1_D6           HAL_GPIO_AF_5 /*!< SDMMC1 Card bidirectional data line 6             */
#define HAL_GPIO_AF5_SPI1                HAL_GPIO_AF_5 /*!< SPI1 Alternate Function mapping                   */
#define HAL_GPIO_AF5_SPI1_MISO           HAL_GPIO_AF_5 /*!< SPI1 Master-In/Slave-Out                          */
#define HAL_GPIO_AF5_SPI1_MOSI           HAL_GPIO_AF_5 /*!< SPI1 Master-Out/Slave-In                          */
#define HAL_GPIO_AF5_SPI1_NSS            HAL_GPIO_AF_5 /*!< SPI1 Slave Selection                              */
#define HAL_GPIO_AF5_SPI1_RDY            HAL_GPIO_AF_5 /*!< SPI1 Ready                                        */
#define HAL_GPIO_AF5_SPI1_SCK            HAL_GPIO_AF_5 /*!< SPI1 Serial Clock                                 */
#define HAL_GPIO_AF5_SPI2                HAL_GPIO_AF_5 /*!< SPI2 Alternate Function mapping                   */
#define HAL_GPIO_AF5_SPI2_MISO           HAL_GPIO_AF_5 /*!< SPI2 Master-In/Slave-Out                          */
#define HAL_GPIO_AF5_SPI2_MOSI           HAL_GPIO_AF_5 /*!< SPI2 Master-Out/Slave-In                          */
#define HAL_GPIO_AF5_SPI2_NSS            HAL_GPIO_AF_5 /*!< SPI2 Slave Selection                              */
#define HAL_GPIO_AF5_SPI2_RDY            HAL_GPIO_AF_5 /*!< SPI2 Ready                                        */
#define HAL_GPIO_AF5_SPI2_SCK            HAL_GPIO_AF_5 /*!< SPI2 Serial Clock                                 */
#define HAL_GPIO_AF5_SPI5                HAL_GPIO_AF_5 /*!< SPI5 Alternate Function mapping                   */
#define HAL_GPIO_AF5_SPI5_MISO           HAL_GPIO_AF_5 /*!< SPI5 Master-In/Slave-Out                          */
#define HAL_GPIO_AF5_SPI5_MOSI           HAL_GPIO_AF_5 /*!< SPI5 Master-Out/Slave-In                          */
#define HAL_GPIO_AF5_SPI5_NSS            HAL_GPIO_AF_5 /*!< SPI5 Slave Selection                              */
#define HAL_GPIO_AF5_SPI5_RDY            HAL_GPIO_AF_5 /*!< SPI5 Ready                                        */
#define HAL_GPIO_AF5_SPI5_SCK            HAL_GPIO_AF_5 /*!< SPI5 Serial Clock                                 */
#define HAL_GPIO_AF5_SPI6                HAL_GPIO_AF_5 /*!< SPI6 Alternate Function mapping                   */
#define HAL_GPIO_AF5_SPI6_MISO           HAL_GPIO_AF_5 /*!< SPI6 Master-In/Slave-Out                          */
#define HAL_GPIO_AF5_SPI6_MOSI           HAL_GPIO_AF_5 /*!< SPI6 Master-Out/Slave-In                          */
#define HAL_GPIO_AF5_SPI6_NSS            HAL_GPIO_AF_5 /*!< SPI6 Slave Selection                              */
#define HAL_GPIO_AF5_SPI6_SCK            HAL_GPIO_AF_5 /*!< SPI6 Serial Clock                                 */
#define HAL_GPIO_AF5_TIM2                HAL_GPIO_AF_5 /*!< TIM2 Alternate Function mapping                   */
#define HAL_GPIO_AF5_TIM2_CH3            HAL_GPIO_AF_5 /*!< TIM2 Multi-purpose Channel 3                      */
#define HAL_GPIO_AF5_TIM8                HAL_GPIO_AF_5 /*!< TIM8 Alternate Function mapping                   */
#define HAL_GPIO_AF5_TIM8_CH1N           HAL_GPIO_AF_5 /*!< TIM8 CH1 complementary output                     */
#define HAL_GPIO_AF5_TIM8_CH2            HAL_GPIO_AF_5 /*!< TIM8 Multi-purpose Channel 2                      */
#define HAL_GPIO_AF5_TIM8_CH2N           HAL_GPIO_AF_5 /*!< TIM8 CH2 complementary output                     */
#define HAL_GPIO_AF5_XSPI1               HAL_GPIO_AF_5 /*!< XSPI1 Alternate Function mapping                  */
#define HAL_GPIO_AF5_XSPI1_IO4           HAL_GPIO_AF_5 /*!< XSPI1 Data Pin 4                                  */
#define HAL_GPIO_AF5_XSPI1_IO6           HAL_GPIO_AF_5 /*!< XSPI1 Data Pin 6                                  */
#define HAL_GPIO_AF5_XSPI1_IO7           HAL_GPIO_AF_5 /*!< XSPI1 Data Pin 7                                  */

/**
  * @brief   AF 6 selection
  */
#define HAL_GPIO_AF6_FDCAN3              HAL_GPIO_AF_6 /*!< FDCAN3 Alternate Function mapping                */
#define HAL_GPIO_AF6_FDCAN3_RX           HAL_GPIO_AF_6 /*!< FDCAN3 Receive pin                               */
#define HAL_GPIO_AF6_FDCAN3_TX           HAL_GPIO_AF_6 /*!< FDCAN3 Transmit pin                              */
#define HAL_GPIO_AF6_I2C1                HAL_GPIO_AF_6 /*!< I2C1 Alternate Function mapping                  */
#define HAL_GPIO_AF6_I2C1_SCL            HAL_GPIO_AF_6 /*!< I2C1 Clock                                       */
#define HAL_GPIO_AF6_I2C1_SDA            HAL_GPIO_AF_6 /*!< I2C1 Data                                        */
#define HAL_GPIO_AF6_I2C1_SMBA           HAL_GPIO_AF_6 /*!< I2C1 SMBus Alert                                 */
#define HAL_GPIO_AF6_I2S3                HAL_GPIO_AF_6 /*!< I2S3 Alternate Function mapping                  */
#define HAL_GPIO_AF6_I2S3_CK             HAL_GPIO_AF_6 /*!< I2S3 Clock                                       */
#define HAL_GPIO_AF6_I2S3_SDI            HAL_GPIO_AF_6 /*!< I2S3 Serial Data Input                           */
#define HAL_GPIO_AF6_I2S3_SDO            HAL_GPIO_AF_6 /*!< I2S3 Serial Data Output                          */
#define HAL_GPIO_AF6_I2S3_WS             HAL_GPIO_AF_6 /*!< I2S3 Word Select                                 */
#define HAL_GPIO_AF6_LPTIM2              HAL_GPIO_AF_6 /*!< LPTIM2 Alternate Function mapping                */
#define HAL_GPIO_AF6_LPTIM2_CH1          HAL_GPIO_AF_6 /*!< LPTIM2 Multi-purpose Channel 1                   */
#define HAL_GPIO_AF6_LPTIM2_ETR          HAL_GPIO_AF_6 /*!< LPTIM2 External trigger input                    */
#define HAL_GPIO_AF6_LPTIM2_IN1          HAL_GPIO_AF_6 /*!< LPTIM2 Channel 1 Input                           */
#define HAL_GPIO_AF6_LPTIM2_IN2          HAL_GPIO_AF_6 /*!< LPTIM2 Channel 2 Input                           */
#define HAL_GPIO_AF6_SDMMC1              HAL_GPIO_AF_6 /*!< SDMMC1 Alternate Function mapping                */
#define HAL_GPIO_AF6_SDMMC1_D0DIR        HAL_GPIO_AF_6 /*!< SDMMC1 Card I/O data line 0 direction indication */
#define HAL_GPIO_AF6_SDMMC1_D7           HAL_GPIO_AF_6 /*!< SDMMC1 Card bidirectional data line 7            */
#define HAL_GPIO_AF6_SPI3                HAL_GPIO_AF_6 /*!< SPI3 Alternate Function mapping                  */
#define HAL_GPIO_AF6_SPI3_MISO           HAL_GPIO_AF_6 /*!< SPI3 Master-In/Slave-Out                         */
#define HAL_GPIO_AF6_SPI3_MOSI           HAL_GPIO_AF_6 /*!< SPI3 Master-Out/Slave-In                         */
#define HAL_GPIO_AF6_SPI3_NSS            HAL_GPIO_AF_6 /*!< SPI3 Slave Selection                             */
#define HAL_GPIO_AF6_SPI3_RDY            HAL_GPIO_AF_6 /*!< SPI3 Ready                                       */
#define HAL_GPIO_AF6_SPI3_SCK            HAL_GPIO_AF_6 /*!< SPI3 Clock                                       */
#define HAL_GPIO_AF6_SPI6                HAL_GPIO_AF_6 /*!< SPI6 Alternate Function mapping                  */
#define HAL_GPIO_AF6_SPI6_MOSI           HAL_GPIO_AF_6 /*!< SPI6 Master-Out/Slave-In                         */
#define HAL_GPIO_AF6_TIM1                HAL_GPIO_AF_6 /*!< TIM1 Alternate Function mapping                  */
#define HAL_GPIO_AF6_TIM1_BKIN           HAL_GPIO_AF_6 /*!< TIM1 Break input                                 */
#define HAL_GPIO_AF6_TIM1_BKIN2          HAL_GPIO_AF_6 /*!< TIM1 Break input 2                               */
#define HAL_GPIO_AF6_TIM1_CH1            HAL_GPIO_AF_6 /*!< TIM1 Multi-purpose Channel 1                     */
#define HAL_GPIO_AF6_TIM1_CH1N           HAL_GPIO_AF_6 /*!< TIM1 CH1 complementary output                    */
#define HAL_GPIO_AF6_TIM1_CH2N           HAL_GPIO_AF_6 /*!< TIM1 CH2 complementary output                    */
#define HAL_GPIO_AF6_TIM1_CH3            HAL_GPIO_AF_6 /*!< TIM1 Multi-purpose Channel 3                     */
#define HAL_GPIO_AF6_TIM1_CH3N           HAL_GPIO_AF_6 /*!< TIM1 CH3 complementary output                    */
#define HAL_GPIO_AF6_TIM1_CH4N           HAL_GPIO_AF_6 /*!< TIM1 CH4 complementary output                    */
#define HAL_GPIO_AF6_TIM3                HAL_GPIO_AF_6 /*!< TIM3 Alternate Function mapping                  */
#define HAL_GPIO_AF6_TIM3_ETR            HAL_GPIO_AF_6 /*!< TIM3 External trigger input                      */
#define HAL_GPIO_AF6_TIM8                HAL_GPIO_AF_6 /*!< TIM8 Alternate Function mapping                  */
#define HAL_GPIO_AF6_TIM8_BKIN2          HAL_GPIO_AF_6 /*!< TIM8 Break input 2                               */
#define HAL_GPIO_AF6_TIM8_CH2            HAL_GPIO_AF_6 /*!< TIM8 Multi-purpose Channel 2                     */
#define HAL_GPIO_AF6_TIM8_ETR            HAL_GPIO_AF_6 /*!< TIM8 External trigger input                      */
#define HAL_GPIO_AF6_TIM20               HAL_GPIO_AF_6 /*!< TIM20 Alternate Function mapping                 */
#define HAL_GPIO_AF6_TIM20_CH1           HAL_GPIO_AF_6 /*!< TIM20 Multi-purpose Channel 1                    */
#define HAL_GPIO_AF6_TIM20_CH2N          HAL_GPIO_AF_6 /*!< TIM20 CH2 complementary output                   */
#define HAL_GPIO_AF6_TIM20_CH3           HAL_GPIO_AF_6 /*!< TIM20 Multi-purpose Channel 3                    */
#define HAL_GPIO_AF6_TIM20_CH3N          HAL_GPIO_AF_6 /*!< TIM20 CH3 complementary output                   */
#define HAL_GPIO_AF6_TIM20_CH4           HAL_GPIO_AF_6 /*!< TIM20 Multi-purpose Channel 4                    */
#define HAL_GPIO_AF6_TIM20_CH4N          HAL_GPIO_AF_6 /*!< TIM20 CH4 complementary output                   */
#define HAL_GPIO_AF6_USART6              HAL_GPIO_AF_6 /*!< USART6 Alternate Function mapping                */
#define HAL_GPIO_AF6_USART6_TX           HAL_GPIO_AF_6 /*!< USART6 Transmit Data Output                      */
#define HAL_GPIO_AF6_USART6_RX           HAL_GPIO_AF_6 /*!< USART6 Serial Data Receive Input                 */
#define HAL_GPIO_AF6_USART10             HAL_GPIO_AF_6 /*!< USART10 Alternate Function mapping               */
#define HAL_GPIO_AF6_USART10_CK          HAL_GPIO_AF_6 /*!< USART10 Clock                                    */
#define HAL_GPIO_AF6_USART10_CTS         HAL_GPIO_AF_6 /*!< USART10 Clear to send                            */
#define HAL_GPIO_AF6_USART10_NSS         HAL_GPIO_AF_6 /*!< USART10 Slave Select                             */
#define HAL_GPIO_AF6_USART10_RTS         HAL_GPIO_AF_6 /*!< USART10 Request to send                          */
#define HAL_GPIO_AF6_USART10_RX          HAL_GPIO_AF_6 /*!< USART10 Serial Data Receive Input                */

/**
  * @brief   AF 7 selection
  */
#define HAL_GPIO_AF7_ADF1                HAL_GPIO_AF_7 /*!< ADF1 Alternate Function mapping          */
#define HAL_GPIO_AF7_ADF1_CCK0           HAL_GPIO_AF_7 /*!< ADF1 External sensors clock 0            */
#define HAL_GPIO_AF7_ADF1_CCK1           HAL_GPIO_AF_7 /*!< ADF1 External sensors clock 1            */
#define HAL_GPIO_AF7_I2S2                HAL_GPIO_AF_7 /*!< I2S2 Alternate Function mapping          */
#define HAL_GPIO_AF7_I2S2_CK             HAL_GPIO_AF_7 /*!< I2S2 Serial Clock                        */
#define HAL_GPIO_AF7_I2S2_MCK            HAL_GPIO_AF_7 /*!< I2S2 Master Clock                        */
#define HAL_GPIO_AF7_I2S2_SDO            HAL_GPIO_AF_7 /*!< I2S2 Serial Data Output                  */
#define HAL_GPIO_AF7_I2S2_WS             HAL_GPIO_AF_7 /*!< I2S2 Word Select                         */
#define HAL_GPIO_AF7_I2S3                HAL_GPIO_AF_7 /*!< I2S3 Alternate Function mapping          */
#define HAL_GPIO_AF7_I2S3_CK             HAL_GPIO_AF_7 /*!< I2S3 Serial Clock                        */
#define HAL_GPIO_AF7_I2S3_SDI            HAL_GPIO_AF_7 /*!< I2S3 Serial Data Input                   */
#define HAL_GPIO_AF7_I2S3_SDO            HAL_GPIO_AF_7 /*!< I2S3 Serial Data Output                  */
#define HAL_GPIO_AF7_I2S3_WS             HAL_GPIO_AF_7 /*!< I2S3 Word Select                         */
#define HAL_GPIO_AF7_SPI2                HAL_GPIO_AF_7 /*!< SPI2 Alternate Function mapping          */
#define HAL_GPIO_AF7_SPI2_MOSI           HAL_GPIO_AF_7 /*!< SPI2 Master-Out/Slave-In                 */
#define HAL_GPIO_AF7_SPI2_NSS            HAL_GPIO_AF_7 /*!< SPI2 Slave Selection                     */
#define HAL_GPIO_AF7_SPI2_RDY            HAL_GPIO_AF_7 /*!< SPI2 Ready                               */
#define HAL_GPIO_AF7_SPI2_SCK            HAL_GPIO_AF_7 /*!< SPI2 Clock                               */
#define HAL_GPIO_AF7_SPI3                HAL_GPIO_AF_7 /*!< SPI3 Alternate Function mapping          */
#define HAL_GPIO_AF7_SPI3_MISO           HAL_GPIO_AF_7 /*!< SPI3 Master-In/Slave-Out                 */
#define HAL_GPIO_AF7_SPI3_MOSI           HAL_GPIO_AF_7 /*!< SPI3 Master-Out/Slave-In                 */
#define HAL_GPIO_AF7_SPI3_NSS            HAL_GPIO_AF_7 /*!< SPI3 Slave Selection                     */
#define HAL_GPIO_AF7_SPI3_RDY            HAL_GPIO_AF_7 /*!< SPI3 Ready                               */
#define HAL_GPIO_AF7_SPI3_SCK            HAL_GPIO_AF_7 /*!< SPI3 Clock                               */
#define HAL_GPIO_AF7_SPI4                HAL_GPIO_AF_7 /*!< SPI4 Alternate Function mapping          */
#define HAL_GPIO_AF7_SPI4_MISO           HAL_GPIO_AF_7 /*!< SPI4 Master-In/Slave-Out                 */
#define HAL_GPIO_AF7_SPI4_MOSI           HAL_GPIO_AF_7 /*!< SPI4 Master-Out/Slave-In                 */
#define HAL_GPIO_AF7_SPI4_NSS            HAL_GPIO_AF_7 /*!< SPI4 Slave Selection                     */
#define HAL_GPIO_AF7_SPI4_RDY            HAL_GPIO_AF_7 /*!< SPI4 Ready                               */
#define HAL_GPIO_AF7_SPI4_SCK            HAL_GPIO_AF_7 /*!< SPI4 Serial Clock                        */
#define HAL_GPIO_AF7_SPI6                HAL_GPIO_AF_7 /*!< SPI6 Alternate Function mapping          */
#define HAL_GPIO_AF7_SPI6_NSS            HAL_GPIO_AF_7 /*!< SPI6 Slave Selection                     */
#define HAL_GPIO_AF7_SPI6_RDY            HAL_GPIO_AF_7 /*!< SPI6 Ready                               */
#define HAL_GPIO_AF7_TIM17               HAL_GPIO_AF_7 /*!< TIM17 Alternate Function mapping         */
#define HAL_GPIO_AF7_TIM17_BKIN          HAL_GPIO_AF_7 /*!< TIM17 Break input                        */
#define HAL_GPIO_AF7_TIM17_CH1           HAL_GPIO_AF_7 /*!< TIM17 Multi-purpose Channel 1            */
#define HAL_GPIO_AF7_TIM17_CH1N          HAL_GPIO_AF_7 /*!< TIM17 CH1 complementary output           */
#define HAL_GPIO_AF7_UART7               HAL_GPIO_AF_7 /*!< UART7 Alternate Function mapping         */
#define HAL_GPIO_AF7_UART7_CTS           HAL_GPIO_AF_7 /*!< UART7 Clear to send                      */
#define HAL_GPIO_AF7_UART7_RTS           HAL_GPIO_AF_7 /*!< UART7 Request to send                    */
#define HAL_GPIO_AF7_UART7_RX            HAL_GPIO_AF_7 /*!< UART7 Serial Data Receive Input          */
#define HAL_GPIO_AF7_UART7_TX            HAL_GPIO_AF_7 /*!< UART7 Transmit Data Output               */
#define HAL_GPIO_AF7_UART8               HAL_GPIO_AF_7 /*!< UART8 Alternate Function mapping         */
#define HAL_GPIO_AF7_UART8_CTS           HAL_GPIO_AF_7 /*!< UART8 Clear to send                      */
#define HAL_GPIO_AF7_UART8_RTS           HAL_GPIO_AF_7 /*!< UART8 Request to send                    */
#define HAL_GPIO_AF7_UART8_RX            HAL_GPIO_AF_7 /*!< UART8 Serial Data Receive Input          */
#define HAL_GPIO_AF7_UART8_TX            HAL_GPIO_AF_7 /*!< UART8 Transmit Data Output               */
#define HAL_GPIO_AF7_UART9               HAL_GPIO_AF_7 /*!< UART9 Alternate Function mapping         */
#define HAL_GPIO_AF7_UART9_CTS           HAL_GPIO_AF_7 /*!< UART9 Clear to send                      */
#define HAL_GPIO_AF7_UART9_RTS           HAL_GPIO_AF_7 /*!< UART9 Request to send                    */
#define HAL_GPIO_AF7_UART9_RX            HAL_GPIO_AF_7 /*!< UART9 Serial Data Receive Input          */
#define HAL_GPIO_AF7_UART9_TX            HAL_GPIO_AF_7 /*!< UART9 Transmit Data Output               */
#define HAL_GPIO_AF7_USART1              HAL_GPIO_AF_7 /*!< USART1 Alternate Function mapping        */
#define HAL_GPIO_AF7_USART1_CK           HAL_GPIO_AF_7 /*!< USART1 Clock                             */
#define HAL_GPIO_AF7_USART1_CTS          HAL_GPIO_AF_7 /*!< USART1 Clear to send                     */
#define HAL_GPIO_AF7_USART1_NSS          HAL_GPIO_AF_7 /*!< USART1 Slave Select                      */
#define HAL_GPIO_AF7_USART1_RTS          HAL_GPIO_AF_7 /*!< USART1 Request to send                   */
#define HAL_GPIO_AF7_USART1_RX           HAL_GPIO_AF_7 /*!< USART1 Serial Data Receive Input         */
#define HAL_GPIO_AF7_USART1_TX           HAL_GPIO_AF_7 /*!< USART1 Transmit Data Output              */
#define HAL_GPIO_AF7_USART2              HAL_GPIO_AF_7 /*!< USART2 Alternate Function mapping        */
#define HAL_GPIO_AF7_USART2_CK           HAL_GPIO_AF_7 /*!< USART2 Clock                             */
#define HAL_GPIO_AF7_USART2_CTS          HAL_GPIO_AF_7 /*!< USART2 Clear to send                     */
#define HAL_GPIO_AF7_USART2_NSS          HAL_GPIO_AF_7 /*!< USART2 Slave Select                      */
#define HAL_GPIO_AF7_USART2_RTS          HAL_GPIO_AF_7 /*!< USART2 Request to send                   */
#define HAL_GPIO_AF7_USART2_RX           HAL_GPIO_AF_7 /*!< USART2 Serial Data Receive Input         */
#define HAL_GPIO_AF7_USART2_TX           HAL_GPIO_AF_7 /*!< USART2 Transmit Data Output              */
#define HAL_GPIO_AF7_USART3              HAL_GPIO_AF_7 /*!< USART3 Alternate Function mapping        */
#define HAL_GPIO_AF7_USART3_CK           HAL_GPIO_AF_7 /*!< USART3 Clock                             */
#define HAL_GPIO_AF7_USART3_CTS          HAL_GPIO_AF_7 /*!< USART3 Clear to send                     */
#define HAL_GPIO_AF7_USART3_NSS          HAL_GPIO_AF_7 /*!< USART3 Slave Select                      */
#define HAL_GPIO_AF7_USART3_RTS          HAL_GPIO_AF_7 /*!< USART3 Request to send                   */
#define HAL_GPIO_AF7_USART3_RX           HAL_GPIO_AF_7 /*!< USART3 Serial Data Receive Input         */
#define HAL_GPIO_AF7_USART3_TX           HAL_GPIO_AF_7 /*!< USART3 Transmit Data Output              */

/**
  * @brief   AF 8 selection
  */
#define HAL_GPIO_AF8_ADF1                HAL_GPIO_AF_8 /*!< ADF1 Alternate Function mapping          */
#define HAL_GPIO_AF8_ADF1_SDI0           HAL_GPIO_AF_8 /*!< ADF1 Data from external sensors          */
#define HAL_GPIO_AF8_FDCAN3              HAL_GPIO_AF_8 /*!< FDCAN3 Alternate Function mapping        */
#define HAL_GPIO_AF8_FDCAN3_RX           HAL_GPIO_AF_8 /*!< FDCAN3 Receive pin                       */
#define HAL_GPIO_AF8_FDCAN3_TX           HAL_GPIO_AF_8 /*!< FDCAN3 Transmit pin                      */
#define HAL_GPIO_AF8_I2C3                HAL_GPIO_AF_8 /*!< I2C3 Alternate Function mapping          */
#define HAL_GPIO_AF8_I2C3_SCL            HAL_GPIO_AF_8 /*!< I2C3 Clock                               */
#define HAL_GPIO_AF8_I2C3_SDA            HAL_GPIO_AF_8 /*!< I2C3 Data                                */
#define HAL_GPIO_AF8_I2C3_SMBA           HAL_GPIO_AF_8 /*!< I2C3 SMBus Alert                         */
#define HAL_GPIO_AF8_LPUART1             HAL_GPIO_AF_8 /*!< LPUART1 Alternate Function mapping       */
#define HAL_GPIO_AF8_LPUART1_CTS         HAL_GPIO_AF_8 /*!< LPUART1 Clear to send                    */
#define HAL_GPIO_AF8_LPUART1_RTS         HAL_GPIO_AF_8 /*!< LPUART1 Request to send                  */
#define HAL_GPIO_AF8_LPUART1_TX          HAL_GPIO_AF_8 /*!< LPUART1 Transmit Data Output             */
#define HAL_GPIO_AF8_LPUART1_RX          HAL_GPIO_AF_8 /*!< LPUART1 Serial Data Receive Input        */
#define HAL_GPIO_AF8_SPI6                HAL_GPIO_AF_8 /*!< SPI6 Alternate Function mapping          */
#define HAL_GPIO_AF8_SPI6_MISO           HAL_GPIO_AF_8 /*!< SPI6 Master-In/Slave-Out                 */
#define HAL_GPIO_AF8_SPI6_MOSI           HAL_GPIO_AF_8 /*!< SPI6 Master-Out/Slave-In                 */
#define HAL_GPIO_AF8_SPI6_NSS            HAL_GPIO_AF_8 /*!< SPI6 Slave Selection                     */
#define HAL_GPIO_AF8_SPI6_RDY            HAL_GPIO_AF_8 /*!< SPI6 Ready                               */
#define HAL_GPIO_AF8_SPI6_SCK            HAL_GPIO_AF_8 /*!< SPI6 Serial Clock                        */
#define HAL_GPIO_AF8_TIM3                HAL_GPIO_AF_8 /*!< TIM3 Alternate Function mapping          */
#define HAL_GPIO_AF8_TIM3_CH3            HAL_GPIO_AF_8 /*!< TIM3 Multi-purpose Channel 3             */
#define HAL_GPIO_AF8_TIM20               HAL_GPIO_AF_8 /*!< TIM20 Alternate Function mapping         */
#define HAL_GPIO_AF8_TIM20_BKIN          HAL_GPIO_AF_8 /*!< TIM20 Break input                        */
#define HAL_GPIO_AF8_TIM20_BKIN2         HAL_GPIO_AF_8 /*!< TIM20 Break input 2                      */
#define HAL_GPIO_AF8_TIM20_CH1           HAL_GPIO_AF_8 /*!< TIM20 Multi-purpose Channel 1            */
#define HAL_GPIO_AF8_TIM20_CH1N          HAL_GPIO_AF_8 /*!< TIM20 CH1 complementary output           */
#define HAL_GPIO_AF8_TIM20_CH2           HAL_GPIO_AF_8 /*!< TIM20 Multi-purpose Channel 2            */
#define HAL_GPIO_AF8_TIM20_CH2N          HAL_GPIO_AF_8 /*!< TIM20 CH2 complementary output           */
#define HAL_GPIO_AF8_TIM20_CH3           HAL_GPIO_AF_8 /*!< TIM20 Multi-purpose Channel 3            */
#define HAL_GPIO_AF8_TIM20_CH4           HAL_GPIO_AF_8 /*!< TIM20 Multi-purpose Channel 4            */
#define HAL_GPIO_AF8_TIM20_CH4N          HAL_GPIO_AF_8 /*!< TIM20 CH4 complementary output           */
#define HAL_GPIO_AF8_TIM20_ETR           HAL_GPIO_AF_8 /*!< TIM20 External trigger input             */
#define HAL_GPIO_AF8_UART4               HAL_GPIO_AF_8 /*!< UART4 Alternate Function mapping         */
#define HAL_GPIO_AF8_UART4_CTS           HAL_GPIO_AF_8 /*!< UART4 Clear to send                      */
#define HAL_GPIO_AF8_UART4_RTS           HAL_GPIO_AF_8 /*!< UART4 Request to send                    */
#define HAL_GPIO_AF8_UART4_RX            HAL_GPIO_AF_8 /*!< UART4 Serial Data Receive Input          */
#define HAL_GPIO_AF8_UART4_TX            HAL_GPIO_AF_8 /*!< UART4 Transmit Data Output               */
#define HAL_GPIO_AF8_UART8               HAL_GPIO_AF_8 /*!< UART8 Alternate Function mapping         */
#define HAL_GPIO_AF8_UART8_CTS           HAL_GPIO_AF_8 /*!< UART8 Clear to send                      */
#define HAL_GPIO_AF8_UART8_RTS           HAL_GPIO_AF_8 /*!< UART8 Request to send                    */
#define HAL_GPIO_AF8_UART8_RX            HAL_GPIO_AF_8 /*!< UART8 Serial Data Receive Input          */
#define HAL_GPIO_AF8_UART8_TX            HAL_GPIO_AF_8 /*!< UART8 Transmit Data Output               */
#define HAL_GPIO_AF8_UART9               HAL_GPIO_AF_8 /*!< UART9 Alternate Function mapping         */
#define HAL_GPIO_AF8_UART9_RX            HAL_GPIO_AF_8 /*!< UART9 Serial Data Receive Input          */
#define HAL_GPIO_AF8_UART9_TX            HAL_GPIO_AF_8 /*!< UART9 Transmit Data Output               */
#define HAL_GPIO_AF8_XSPI1               HAL_GPIO_AF_8 /*!< XSPI1 Alternate Function mapping         */
#define HAL_GPIO_AF8_XSPI1_DQS0          HAL_GPIO_AF_8 /*!< XSPI1 Memory Data Strobe I/O             */
#define HAL_GPIO_AF8_XSPI1_IO0           HAL_GPIO_AF_8 /*!< XSPI1 Data Pin 0                         */
#define HAL_GPIO_AF8_XSPI1_IO1           HAL_GPIO_AF_8 /*!< XSPI1 Data Pin 1                         */
#define HAL_GPIO_AF8_XSPI1_IO2           HAL_GPIO_AF_8 /*!< XSPI1 Data Pin 2                         */
#define HAL_GPIO_AF8_XSPI1_IO3           HAL_GPIO_AF_8 /*!< XSPI1 Data Pin 3                         */
#define HAL_GPIO_AF8_XSPI1_NCS2          HAL_GPIO_AF_8 /*!< XSPI1 Memory Chip Select 2               */

/**
  * @brief   AF 9 selection
  */
#define HAL_GPIO_AF9_FDCAN1              HAL_GPIO_AF_9 /*!< FDCAN1 Alternate Function mapping        */
#define HAL_GPIO_AF9_FDCAN1_RX           HAL_GPIO_AF_9 /*!< FDCAN1 Receive pin                       */
#define HAL_GPIO_AF9_FDCAN1_TX           HAL_GPIO_AF_9 /*!< FDCAN1 Transmit pin                      */
#define HAL_GPIO_AF9_I2C1                HAL_GPIO_AF_9 /*!< I2C1 Alternate Function mapping          */
#define HAL_GPIO_AF9_I2C1_SCL            HAL_GPIO_AF_9 /*!< I2C1 Clock                               */
#define HAL_GPIO_AF9_I2C1_SDA            HAL_GPIO_AF_9 /*!< I2C1 Data                                */
#define HAL_GPIO_AF9_I2C1_SMBA           HAL_GPIO_AF_9 /*!< I2C1 SMBus Alert                         */
#define HAL_GPIO_AF9_I2S3                HAL_GPIO_AF_9 /*!< I2S3 Alternate Function mapping          */
#define HAL_GPIO_AF9_I2S3_CK             HAL_GPIO_AF_9 /*!< I2S3 Serial Clock                        */
#define HAL_GPIO_AF9_I2S3_MCK            HAL_GPIO_AF_9 /*!< I2S3 Master Clock                        */
#define HAL_GPIO_AF9_I2S3_SDI            HAL_GPIO_AF_9 /*!< I2S3 Serial Data Input                   */
#define HAL_GPIO_AF9_LPTIM1              HAL_GPIO_AF_9 /*!< LPTIM1 Alternate Function mapping        */
#define HAL_GPIO_AF9_LPTIM1_CH1          HAL_GPIO_AF_9 /*!< LPTIM1 Multi-purpose Channel 1           */
#define HAL_GPIO_AF9_LPTIM1_CH2          HAL_GPIO_AF_9 /*!< LPTIM1 Multi-purpose Channel 2           */
#define HAL_GPIO_AF9_LPTIM1_ETR          HAL_GPIO_AF_9 /*!< LPTIM1 External trigger input            */
#define HAL_GPIO_AF9_LPTIM1_IN1          HAL_GPIO_AF_9 /*!< LPTIM1 Channel 1 Input                   */
#define HAL_GPIO_AF9_LPTIM1_IN2          HAL_GPIO_AF_9 /*!< LPTIM1 Channel 2 Input                   */
#define HAL_GPIO_AF9_LPTIM4              HAL_GPIO_AF_9 /*!< LPTIM4 Alternate Function mapping        */
#define HAL_GPIO_AF9_LPTIM4_IN1          HAL_GPIO_AF_9 /*!< LPTIM4 Channel 1 Input                   */
#define HAL_GPIO_AF9_SPI3                HAL_GPIO_AF_9 /*!< SPI3 Alternate Function mapping          */
#define HAL_GPIO_AF9_SPI3_MISO           HAL_GPIO_AF_9 /*!< SPI3 Master-In/Slave-Out                 */
#define HAL_GPIO_AF9_SPI3_RDY            HAL_GPIO_AF_9 /*!< SPI3 Ready                               */
#define HAL_GPIO_AF9_SPI3_SCK            HAL_GPIO_AF_9 /*!< SPI3 Serial Clock                        */
#define HAL_GPIO_AF9_SPI4                HAL_GPIO_AF_9 /*!< SPI4 Alternate Function mapping          */
#define HAL_GPIO_AF9_SPI4_MISO           HAL_GPIO_AF_9 /*!< SPI4 Master-In/Slave-Out                 */
#define HAL_GPIO_AF9_SPI4_NSS            HAL_GPIO_AF_9 /*!< SPI4 Slave Selection                     */
#define HAL_GPIO_AF9_SPI4_RDY            HAL_GPIO_AF_9 /*!< SPI4 Ready                               */
#define HAL_GPIO_AF9_SPI4_SCK            HAL_GPIO_AF_9 /*!< SPI4 Serial Clock                        */
#define HAL_GPIO_AF9_TIM1                HAL_GPIO_AF_9 /*!< TIM1 Alternate Function mapping          */
#define HAL_GPIO_AF9_TIM1_BKIN           HAL_GPIO_AF_9 /*!< TIM1 Break input                         */
#define HAL_GPIO_AF9_TIM1_BKIN2          HAL_GPIO_AF_9 /*!< TIM1 Break input 2                       */
#define HAL_GPIO_AF9_TIM1_CH2            HAL_GPIO_AF_9 /*!< TIM1 Multi-purpose Channel 2             */
#define HAL_GPIO_AF9_TIM15               HAL_GPIO_AF_9 /*!< TIM15 Alternate Function mapping         */
#define HAL_GPIO_AF9_TIM15_BKIN          HAL_GPIO_AF_9 /*!< TIM15 Break input                        */
#define HAL_GPIO_AF9_TIM15_CH1           HAL_GPIO_AF_9 /*!< TIM15 Multi-purpose Channel 1            */
#define HAL_GPIO_AF9_TIM15_CH1N          HAL_GPIO_AF_9 /*!< TIM15 CH1 complementary output           */
#define HAL_GPIO_AF9_TIM15_CH2           HAL_GPIO_AF_9 /*!< TIM15 Multi-purpose Channel 2            */
#define HAL_GPIO_AF9_TIM20               HAL_GPIO_AF_9 /*!< TIM20 Alternate Function mapping         */
#define HAL_GPIO_AF9_TIM20_BKIN          HAL_GPIO_AF_9 /*!< TIM20 Break input                        */
#define HAL_GPIO_AF9_TIM20_CH1           HAL_GPIO_AF_9 /*!< TIM20 Multi-purpose Channel 1            */
#define HAL_GPIO_AF9_TIM20_CH1N          HAL_GPIO_AF_9 /*!< TIM20 CH1 complementary output           */
#define HAL_GPIO_AF9_TIM20_CH2           HAL_GPIO_AF_9 /*!< TIM20 Multi-purpose Channel 2            */
#define HAL_GPIO_AF9_TIM20_CH2N          HAL_GPIO_AF_9 /*!< TIM20 CH2 complementary output           */
#define HAL_GPIO_AF9_TIM20_CH3           HAL_GPIO_AF_9 /*!< TIM20 Multi-purpose Channel 3            */
#define HAL_GPIO_AF9_TIM20_CH3N          HAL_GPIO_AF_9 /*!< TIM20 CH3 complementary output           */
#define HAL_GPIO_AF9_TIM20_CH4           HAL_GPIO_AF_9 /*!< TIM20 Multi-purpose Channel 4            */
#define HAL_GPIO_AF9_TIM20_ETR           HAL_GPIO_AF_9 /*!< TIM20 External trigger input             */
#define HAL_GPIO_AF9_UART5               HAL_GPIO_AF_9 /*!< UART5 Alternate Function mapping         */
#define HAL_GPIO_AF9_UART5_CTS           HAL_GPIO_AF_9 /*!< UART5 Clear to send                      */
#define HAL_GPIO_AF9_UART5_RTS           HAL_GPIO_AF_9 /*!< UART5 Request to send                    */
#define HAL_GPIO_AF9_UART5_RX            HAL_GPIO_AF_9 /*!< UART5 Serial Data Receive Input          */
#define HAL_GPIO_AF9_UART5_TX            HAL_GPIO_AF_9 /*!< UART5 Transmit Data Output               */
#define HAL_GPIO_AF9_UCPD1               HAL_GPIO_AF_9 /*!< UCPD1 Alternate Function mapping         */
#define HAL_GPIO_AF9_UCPD1_FRSTX2        HAL_GPIO_AF_9 /*!< UCPD1 Fast Role Swap signaling output 2  */
#define HAL_GPIO_AF9_USART10             HAL_GPIO_AF_9 /*!< USART10 Alternate Function mapping       */
#define HAL_GPIO_AF9_USART10_RX          HAL_GPIO_AF_9 /*!< USART10 Serial Data Receive Input        */
#define HAL_GPIO_AF9_USART10_TX          HAL_GPIO_AF_9 /*!< USART10 Transmit Data Output             */
#define HAL_GPIO_AF9_XSPI1               HAL_GPIO_AF_9 /*!< XSPI1 Alternate Function mapping         */
#define HAL_GPIO_AF9_XSPI1_IO5           HAL_GPIO_AF_9 /*!< XSPI1 Data Pin 5                         */

/**
  * @brief   AF 10 selection
  */
#define HAL_GPIO_AF10_HRTIM2             HAL_GPIO_AF_10 /*!< HRTIM2 Alternate Function mapping       */
#define HAL_GPIO_AF10_HRTIM2_EEV11       HAL_GPIO_AF_10 /*!< HRTIM2  External Event 11               */
#define HAL_GPIO_AF10_HRTIM2_FLT5        HAL_GPIO_AF_10 /*!< HRTIM2  Fault 5                         */
#define HAL_GPIO_AF10_HRTIM2_FLT7        HAL_GPIO_AF_10 /*!< HRTIM2  Fault 7                         */
#define HAL_GPIO_AF10_HRTIM2_FLT8        HAL_GPIO_AF_10 /*!< HRTIM2  Fault 8                         */
#define HAL_GPIO_AF10_HSP1               HAL_GPIO_AF_10 /*!< HSP1 Alternate Function mapping         */
#define HAL_GPIO_AF10_HSP1_SNP0          HAL_GPIO_AF_10 /*!< HSP1 Snap or Sample Point 0             */
#define HAL_GPIO_AF10_HSP1_SNP1          HAL_GPIO_AF_10 /*!< HSP1 Snap or Sample Point 1             */
#define HAL_GPIO_AF10_HSP1_SNP2          HAL_GPIO_AF_10 /*!< HSP1 Snap or Sample Point 2             */
#define HAL_GPIO_AF10_HSP1_SNP3          HAL_GPIO_AF_10 /*!< HSP1 Snap or Sample Point 3             */
#define HAL_GPIO_AF10_HSP1_SNP4          HAL_GPIO_AF_10 /*!< HSP1 Snap or Sample Point 4             */
#define HAL_GPIO_AF10_HSP1_SNP5          HAL_GPIO_AF_10 /*!< HSP1 Snap or Sample Point 5             */
#define HAL_GPIO_AF10_LPTIM3             HAL_GPIO_AF_10 /*!< LPTIM3 Alternate Function mapping       */
#define HAL_GPIO_AF10_LPTIM3_ETR         HAL_GPIO_AF_10 /*!< LPTIM3 External trigger input           */
#define HAL_GPIO_AF10_LPTIM4             HAL_GPIO_AF_10 /*!< LPTIM4 Alternate Function mapping       */
#define HAL_GPIO_AF10_LPTIM4_ETR         HAL_GPIO_AF_10 /*!< LPTIM4 External trigger input           */
#define HAL_GPIO_AF10_SDMMC1             HAL_GPIO_AF_10 /*!< SDMMC1 Alternate Function mapping       */
#define HAL_GPIO_AF10_SDMMC1_D3          HAL_GPIO_AF_10 /*!< SDMMC1 Card bidirectional data line 3   */
#define HAL_GPIO_AF10_SDMMC1_D4          HAL_GPIO_AF_10 /*!< SDMMC1 Card bidirectional data line 4   */
#define HAL_GPIO_AF10_SPI1               HAL_GPIO_AF_10 /*!< SPI1 Alternate Function mapping         */
#define HAL_GPIO_AF10_SPI1_RDY           HAL_GPIO_AF_10 /*!< SPI1 Ready                              */
#define HAL_GPIO_AF10_TIM1               HAL_GPIO_AF_10 /*!< TIM1 Alternate Function mapping         */
#define HAL_GPIO_AF10_TIM1_BKIN          HAL_GPIO_AF_10 /*!< TIM1 Break input                        */
#define HAL_GPIO_AF10_TIM1_BKIN2         HAL_GPIO_AF_10 /*!< TIM1 Break input 2                      */
#define HAL_GPIO_AF10_TIM1_ETR           HAL_GPIO_AF_10 /*!< TIM1 External trigger input             */
#define HAL_GPIO_AF10_TIM2               HAL_GPIO_AF_10 /*!< TIM2 Alternate Function mapping         */
#define HAL_GPIO_AF10_TIM2_CH1           HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 1            */
#define HAL_GPIO_AF10_TIM2_CH3           HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 3            */
#define HAL_GPIO_AF10_TIM2_CH4           HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 4            */
#define HAL_GPIO_AF10_TIM2_ETR           HAL_GPIO_AF_10 /*!< TIM2 External trigger input             */
#define HAL_GPIO_AF10_TIM4               HAL_GPIO_AF_10 /*!< TIM4 Alternate Function mapping         */
#define HAL_GPIO_AF10_TIM4_CH4           HAL_GPIO_AF_10 /*!< TIM4 Multi-purpose Channel 4            */
#define HAL_GPIO_AF10_TIM4_ETR           HAL_GPIO_AF_10 /*!< TIM4 External trigger input             */
#define HAL_GPIO_AF10_TIM8               HAL_GPIO_AF_10 /*!< TIM8 Alternate Function mapping         */
#define HAL_GPIO_AF10_TIM8_BKIN          HAL_GPIO_AF_10 /*!< TIM8 Break input                        */
#define HAL_GPIO_AF10_TIM8_BKIN2         HAL_GPIO_AF_10 /*!< TIM8 Break input 2                      */
#define HAL_GPIO_AF10_TIM8_CH1           HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 1            */
#define HAL_GPIO_AF10_TIM8_CH1N          HAL_GPIO_AF_10 /*!< TIM8 CH1 complementary output           */
#define HAL_GPIO_AF10_TIM8_CH2           HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 2            */
#define HAL_GPIO_AF10_TIM8_CH3           HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 3            */
#define HAL_GPIO_AF10_TIM8_CH3N          HAL_GPIO_AF_10 /*!< TIM8 CH3 complementary output           */
#define HAL_GPIO_AF10_TIM8_CH4           HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 4            */
#define HAL_GPIO_AF10_TIM8_CH4N          HAL_GPIO_AF_10 /*!< TIM8 CH4 complementary output           */
#define HAL_GPIO_AF10_TIM8_ETR           HAL_GPIO_AF_10 /*!< TIM8 External trigger input             */
#define HAL_GPIO_AF10_UART7              HAL_GPIO_AF_10 /*!< UART7 Alternate Function mapping        */
#define HAL_GPIO_AF10_UART7_TX           HAL_GPIO_AF_10 /*!< UART7 Transmit Data Output              */
#define HAL_GPIO_AF10_UCPD1              HAL_GPIO_AF_10 /*!< UCPD1 Alternate Function mapping        */
#define HAL_GPIO_AF10_UCPD1_FRSTX1       HAL_GPIO_AF_10 /*!< UCPD1 Fast Role Swap signaling output 1 */
#define HAL_GPIO_AF10_UCPD1_FRSTX2       HAL_GPIO_AF_10 /*!< UCPD1 Fast Role Swap signaling output 2 */
#define HAL_GPIO_AF10_USART6             HAL_GPIO_AF_10 /*!< USART6 Alternate Function mapping       */
#define HAL_GPIO_AF10_USART6_CK          HAL_GPIO_AF_10 /*!< USART6 Clock                            */
#define HAL_GPIO_AF10_USART6_CTS         HAL_GPIO_AF_10 /*!< USART6 Clear to send                    */
#define HAL_GPIO_AF10_USART6_NSS         HAL_GPIO_AF_10 /*!< USART6 Slave Selection                  */
#define HAL_GPIO_AF10_USART6_RTS         HAL_GPIO_AF_10 /*!< USART6 Request to send                  */
#define HAL_GPIO_AF10_USART6_RX          HAL_GPIO_AF_10 /*!< USART6 Serial Data Receive Input        */
#define HAL_GPIO_AF10_USART6_TX          HAL_GPIO_AF_10 /*!< USART6 Transmit Data Output             */
#define HAL_GPIO_AF10_USART10            HAL_GPIO_AF_10 /*!< USART10 Alternate Function mapping      */
#define HAL_GPIO_AF10_USART10_RTS        HAL_GPIO_AF_10 /*!< USART10 Request to send                 */
#define HAL_GPIO_AF10_USART10_RX         HAL_GPIO_AF_10 /*!< USART10 Serial Data Receive Input       */
#define HAL_GPIO_AF10_USART10_TX         HAL_GPIO_AF_10 /*!< USART10 Transmit Data Output            */
#define HAL_GPIO_AF10_XSPI1              HAL_GPIO_AF_10 /*!< XSPI1 Alternate Function mapping        */
#define HAL_GPIO_AF10_XSPI1_DQS0         HAL_GPIO_AF_10 /*!< XSPI1 Memory Data Strobe I/O            */
#define HAL_GPIO_AF10_XSPI1_IO6          HAL_GPIO_AF_10 /*!< XSPI1 Data Pin 6                        */
#define HAL_GPIO_AF10_XSPI1_NCS1         HAL_GPIO_AF_10 /*!< XSPI1 Memory Chip Select 1              */
#define HAL_GPIO_AF10_XSPI1_NCS2         HAL_GPIO_AF_10 /*!< XSPI1 Memory Chip Select 2              */

/**
  * @brief   AF 11 selection
  */
#define HAL_GPIO_AF11_FMC                HAL_GPIO_AF_11 /*!< FMC Alternate Function mapping          */
#define HAL_GPIO_AF11_FMC_A18            HAL_GPIO_AF_11 /*!< FMC Address bus bit 18                  */
#define HAL_GPIO_AF11_FMC_A24            HAL_GPIO_AF_11 /*!< FMC Address bus bit 24                  */
#define HAL_GPIO_AF11_HRTIM1             HAL_GPIO_AF_11 /*!< HRTIM1 Alternate Function mapping       */
#define HAL_GPIO_AF11_HRTIM1_CHE1        HAL_GPIO_AF_11 /*!< HRTIM1 Timer E Output 1                 */
#define HAL_GPIO_AF11_HRTIM1_CHE2        HAL_GPIO_AF_11 /*!< HRTIM1 Timer E Output 2                 */
#define HAL_GPIO_AF11_HRTIM1_CHF1        HAL_GPIO_AF_11 /*!< HRTIM1 Timer F Output 1                 */
#define HAL_GPIO_AF11_HRTIM1_CHF2        HAL_GPIO_AF_11 /*!< HRTIM1 Timer F Output 2                 */
#define HAL_GPIO_AF11_HRTIM1_EEV1        HAL_GPIO_AF_11 /*!< HRTIM1  External Event 1                */
#define HAL_GPIO_AF11_HRTIM1_EEV2        HAL_GPIO_AF_11 /*!< HRTIM1  External Event 2                */
#define HAL_GPIO_AF11_HRTIM1_EEV3        HAL_GPIO_AF_11 /*!< HRTIM1  External Event 3                */
#define HAL_GPIO_AF11_HRTIM1_EEV4        HAL_GPIO_AF_11 /*!< HRTIM1  External Event 4                */
#define HAL_GPIO_AF11_HRTIM1_EEV6        HAL_GPIO_AF_11 /*!< HRTIM1  External Event 6                */
#define HAL_GPIO_AF11_HRTIM1_EEV8        HAL_GPIO_AF_11 /*!< HRTIM1  External Event 8                */
#define HAL_GPIO_AF11_HRTIM1_EEV9        HAL_GPIO_AF_11 /*!< HRTIM1  External Event 9                */
#define HAL_GPIO_AF11_HRTIM1_EEV10       HAL_GPIO_AF_11 /*!< HRTIM1  External Event 10               */
#define HAL_GPIO_AF11_HRTIM1_EEV12       HAL_GPIO_AF_11 /*!< HRTIM1  External Event 12               */
#define HAL_GPIO_AF11_HRTIM1_EEV13       HAL_GPIO_AF_11 /*!< HRTIM1  External Event 13               */
#define HAL_GPIO_AF11_HRTIM1_EEV14       HAL_GPIO_AF_11 /*!< HRTIM1  External Event 14               */
#define HAL_GPIO_AF11_HRTIM1_EEV15       HAL_GPIO_AF_11 /*!< HRTIM1  External Event 15               */
#define HAL_GPIO_AF11_HRTIM1_EEV16       HAL_GPIO_AF_11 /*!< HRTIM1  External Event 16               */
#define HAL_GPIO_AF11_HRTIM1_FLT1        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 1                         */
#define HAL_GPIO_AF11_HRTIM1_FLT2        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 2                         */
#define HAL_GPIO_AF11_HRTIM1_FLT3        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 3                         */
#define HAL_GPIO_AF11_HRTIM1_FLT4        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 4                         */
#define HAL_GPIO_AF11_HRTIM1_FLT5        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 5                         */
#define HAL_GPIO_AF11_HRTIM1_FLT6        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 6                         */
#define HAL_GPIO_AF11_HRTIM1_FLT7        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 7                         */
#define HAL_GPIO_AF11_HRTIM1_FLT8        HAL_GPIO_AF_11 /*!< HRTIM1  Fault 8                         */
#define HAL_GPIO_AF11_HRTIM1_SCIN        HAL_GPIO_AF_11 /*!< HRTIM1  Synchronization Input           */
#define HAL_GPIO_AF11_HRTIM2             HAL_GPIO_AF_11 /*!< HRTIM2 Alternate Function mapping       */
#define HAL_GPIO_AF11_HRTIM2_EEV4        HAL_GPIO_AF_11 /*!< HRTIM2  External Event 4                */
#define HAL_GPIO_AF11_HRTIM2_FLT2        HAL_GPIO_AF_11 /*!< HRTIM2  Fault 2                         */
#define HAL_GPIO_AF11_HRTIM2_FLT6        HAL_GPIO_AF_11 /*!< HRTIM2  Fault 6                         */
#define HAL_GPIO_AF11_HRTIM2_FLT7        HAL_GPIO_AF_11 /*!< HRTIM2  Fault 7                         */
#define HAL_GPIO_AF11_HRTIM2_FLT8        HAL_GPIO_AF_11 /*!< HRTIM2  Fault 8                         */
#define HAL_GPIO_AF11_I2C2               HAL_GPIO_AF_11 /*!< I2C2 Alternate Function mapping         */
#define HAL_GPIO_AF11_I2C2_SMBA          HAL_GPIO_AF_11 /*!< I2C2 SMBus Alert                        */
#define HAL_GPIO_AF11_I2S1               HAL_GPIO_AF_11 /*!< I2S1 Alternate Function mapping         */
#define HAL_GPIO_AF11_I2S1_WS            HAL_GPIO_AF_11 /*!< I2S1 Word Select                        */
#define HAL_GPIO_AF11_I3C1               HAL_GPIO_AF_11 /*!< I3C1 Alternate Function mapping         */
#define HAL_GPIO_AF11_I3C1_SCL           HAL_GPIO_AF_11 /*!< I3C1 Clock                              */
#define HAL_GPIO_AF11_I3C1_SDA           HAL_GPIO_AF_11 /*!< I3C1 Data                               */
#define HAL_GPIO_AF11_LPTIM3             HAL_GPIO_AF_11 /*!< LPTIM3 Alternate Function mapping       */
#define HAL_GPIO_AF11_LPTIM3_CH1         HAL_GPIO_AF_11 /*!< LPTIM3 Multi-purpose Channel 1          */
#define HAL_GPIO_AF11_LPTIM3_CH2         HAL_GPIO_AF_11 /*!< LPTIM3 Multi-purpose Channel 2          */
#define HAL_GPIO_AF11_LPTIM3_ETR         HAL_GPIO_AF_11 /*!< LPTIM3 External trigger input           */
#define HAL_GPIO_AF11_LPTIM3_IN1         HAL_GPIO_AF_11 /*!< LPTIM3 Channel 1 Input                  */
#define HAL_GPIO_AF11_LPTIM3_IN2         HAL_GPIO_AF_11 /*!< LPTIM3 Channel 2 Input                  */
#define HAL_GPIO_AF11_LPTIM4             HAL_GPIO_AF_11 /*!< LPTIM4 Alternate Function mapping       */
#define HAL_GPIO_AF11_LPTIM4_IN1         HAL_GPIO_AF_11 /*!< LPTIM4 Channel 1 Input                  */
#define HAL_GPIO_AF11_LPTIM4_OUT         HAL_GPIO_AF_11 /*!< LPTIM4 Output                           */
#define HAL_GPIO_AF11_LPTIM5             HAL_GPIO_AF_11 /*!< LPTIM5 Alternate Function mapping       */
#define HAL_GPIO_AF11_LPTIM5_ETR         HAL_GPIO_AF_11 /*!< LPTIM5 External trigger input           */
#define HAL_GPIO_AF11_OTG_FS             HAL_GPIO_AF_11 /*!< OTG_FS Alternate Function mapping       */
#define HAL_GPIO_AF11_OTG_FS_SOF         HAL_GPIO_AF_11 /*!< OTG_FS Start of frame                   */
#define HAL_GPIO_AF11_SDMMC1             HAL_GPIO_AF_11 /*!< SDMMC1 Alternate Function mapping       */
#define HAL_GPIO_AF11_SDMMC1_CKIN        HAL_GPIO_AF_11 /*!< SDMMC1 Card clock                       */
#define HAL_GPIO_AF11_SDMMC1_D6          HAL_GPIO_AF_11 /*!< SDMMC1 Card bidirectional data line 6   */
#define HAL_GPIO_AF11_SPI1               HAL_GPIO_AF_11 /*!< SPI1 Alternate Function mapping         */
#define HAL_GPIO_AF11_SPI1_NSS           HAL_GPIO_AF_11 /*!< SPI1 Slave Selection                    */
#define HAL_GPIO_AF11_TIM1               HAL_GPIO_AF_11 /*!< TIM1 Alternate Function mapping         */
#define HAL_GPIO_AF11_TIM1_CH1           HAL_GPIO_AF_11 /*!< TIM1 Multi-purpose Channel 1            */
#define HAL_GPIO_AF11_TIM1_CH3           HAL_GPIO_AF_11 /*!< TIM1 Multi-purpose Channel 3            */
#define HAL_GPIO_AF11_TIM1_CH3N          HAL_GPIO_AF_11 /*!< TIM1 CH3 complementary output           */
#define HAL_GPIO_AF11_TIM9               HAL_GPIO_AF_11 /*!< TIM9 Alternate Function mapping         */
#define HAL_GPIO_AF11_TIM9_CH1           HAL_GPIO_AF_11 /*!< TIM9 Multi-purpose Channel 1            */
#define HAL_GPIO_AF11_TIM9_CH2           HAL_GPIO_AF_11 /*!< TIM9 Multi-purpose Channel 2            */
#define HAL_GPIO_AF11_USART10            HAL_GPIO_AF_11 /*!< USART10 Alternate Function mapping      */
#define HAL_GPIO_AF11_USART10_CK         HAL_GPIO_AF_11 /*!< USART10 Clock                           */
#define HAL_GPIO_AF11_USART10_CTS        HAL_GPIO_AF_11 /*!< USART10 Clear to send                   */
#define HAL_GPIO_AF11_USART10_NSS        HAL_GPIO_AF_11 /*!< USART10 Slave Selection                 */
/**
  * @brief   AF 12 selection
  */
#define HAL_GPIO_AF12_FMC                HAL_GPIO_AF_12 /*!< FMC Alternate Function mapping           */
#define HAL_GPIO_AF12_FMC_A0             HAL_GPIO_AF_12 /*!< FMC Address line 0                       */
#define HAL_GPIO_AF12_FMC_A1             HAL_GPIO_AF_12 /*!< FMC Address line 1                       */
#define HAL_GPIO_AF12_FMC_A2             HAL_GPIO_AF_12 /*!< FMC Address line 2                       */
#define HAL_GPIO_AF12_FMC_A3             HAL_GPIO_AF_12 /*!< FMC Address line 3                       */
#define HAL_GPIO_AF12_FMC_A4             HAL_GPIO_AF_12 /*!< FMC Address line 4                       */
#define HAL_GPIO_AF12_FMC_A5             HAL_GPIO_AF_12 /*!< FMC Address line 5                       */
#define HAL_GPIO_AF12_FMC_A6             HAL_GPIO_AF_12 /*!< FMC Address line 6                       */
#define HAL_GPIO_AF12_FMC_A7             HAL_GPIO_AF_12 /*!< FMC Address line 7                       */
#define HAL_GPIO_AF12_FMC_A8             HAL_GPIO_AF_12 /*!< FMC Address line 8                       */
#define HAL_GPIO_AF12_FMC_A9             HAL_GPIO_AF_12 /*!< FMC Address line 9                       */
#define HAL_GPIO_AF12_FMC_A10            HAL_GPIO_AF_12 /*!< FMC Address line 10                      */
#define HAL_GPIO_AF12_FMC_A11            HAL_GPIO_AF_12 /*!< FMC Address line 11                      */
#define HAL_GPIO_AF12_FMC_A12            HAL_GPIO_AF_12 /*!< FMC Address line 12                      */
#define HAL_GPIO_AF12_FMC_A13            HAL_GPIO_AF_12 /*!< FMC Address line 13                      */
#define HAL_GPIO_AF12_FMC_A14            HAL_GPIO_AF_12 /*!< FMC Address line 14                      */
#define HAL_GPIO_AF12_FMC_A15            HAL_GPIO_AF_12 /*!< FMC Address line 15                      */
#define HAL_GPIO_AF12_FMC_A16            HAL_GPIO_AF_12 /*!< FMC Address line 16                      */
#define HAL_GPIO_AF12_FMC_A17            HAL_GPIO_AF_12 /*!< FMC Address line 17                      */
#define HAL_GPIO_AF12_FMC_A19            HAL_GPIO_AF_12 /*!< FMC Address line 19                      */
#define HAL_GPIO_AF12_FMC_A20            HAL_GPIO_AF_12 /*!< FMC Address line 20                      */
#define HAL_GPIO_AF12_FMC_A21            HAL_GPIO_AF_12 /*!< FMC Address line 21                      */
#define HAL_GPIO_AF12_FMC_A22            HAL_GPIO_AF_12 /*!< FMC Address line 22                      */
#define HAL_GPIO_AF12_FMC_A23            HAL_GPIO_AF_12 /*!< FMC Address line 23                      */
#define HAL_GPIO_AF12_FMC_A25            HAL_GPIO_AF_12 /*!< FMC Address line 25                      */
#define HAL_GPIO_AF12_FMC_AD0            HAL_GPIO_AF_12 /*!< FMC Address/Data line 0                  */
#define HAL_GPIO_AF12_FMC_AD1            HAL_GPIO_AF_12 /*!< FMC Address/Data line 1                  */
#define HAL_GPIO_AF12_FMC_AD2            HAL_GPIO_AF_12 /*!< FMC Address/Data line 2                  */
#define HAL_GPIO_AF12_FMC_AD3            HAL_GPIO_AF_12 /*!< FMC Address/Data line 3                  */
#define HAL_GPIO_AF12_FMC_AD4            HAL_GPIO_AF_12 /*!< FMC Address/Data line 4                  */
#define HAL_GPIO_AF12_FMC_AD5            HAL_GPIO_AF_12 /*!< FMC Address/Data line 5                  */
#define HAL_GPIO_AF12_FMC_AD6            HAL_GPIO_AF_12 /*!< FMC Address/Data line 6                  */
#define HAL_GPIO_AF12_FMC_AD7            HAL_GPIO_AF_12 /*!< FMC Address/Data line 7                  */
#define HAL_GPIO_AF12_FMC_AD8            HAL_GPIO_AF_12 /*!< FMC Address/Data line 8                  */
#define HAL_GPIO_AF12_FMC_AD9            HAL_GPIO_AF_12 /*!< FMC Address/Data line 9                  */
#define HAL_GPIO_AF12_FMC_AD10           HAL_GPIO_AF_12 /*!< FMC Address/Data line 10                 */
#define HAL_GPIO_AF12_FMC_AD11           HAL_GPIO_AF_12 /*!< FMC Address/Data line 11                 */
#define HAL_GPIO_AF12_FMC_AD12           HAL_GPIO_AF_12 /*!< FMC Address/Data line 12                 */
#define HAL_GPIO_AF12_FMC_AD13           HAL_GPIO_AF_12 /*!< FMC Address/Data line 13                 */
#define HAL_GPIO_AF12_FMC_AD14           HAL_GPIO_AF_12 /*!< FMC Address/Data line 14                 */
#define HAL_GPIO_AF12_FMC_AD15           HAL_GPIO_AF_12 /*!< FMC Address/Data line 15                 */
#define HAL_GPIO_AF12_FMC_ALE            HAL_GPIO_AF_12 /*!< FMC Address Latch Enable                 */
#define HAL_GPIO_AF12_FMC_BA0            HAL_GPIO_AF_12 /*!< FMC SDRAM Bank Address bit 0             */
#define HAL_GPIO_AF12_FMC_BA1            HAL_GPIO_AF_12 /*!< FMC SDRAM Bank Address bit 1             */
#define HAL_GPIO_AF12_FMC_CLE            HAL_GPIO_AF_12 /*!< FMC Command Latch Enable                 */
#define HAL_GPIO_AF12_FMC_CLK            HAL_GPIO_AF_12 /*!< FMC Clock Output                         */
#define HAL_GPIO_AF12_FMC_D0             HAL_GPIO_AF_12 /*!< FMC Data line 0                          */
#define HAL_GPIO_AF12_FMC_D1             HAL_GPIO_AF_12 /*!< FMC Data line 1                          */
#define HAL_GPIO_AF12_FMC_D2             HAL_GPIO_AF_12 /*!< FMC Data line 2                          */
#define HAL_GPIO_AF12_FMC_D3             HAL_GPIO_AF_12 /*!< FMC Data line 3                          */
#define HAL_GPIO_AF12_FMC_D4             HAL_GPIO_AF_12 /*!< FMC Data line 4                          */
#define HAL_GPIO_AF12_FMC_D5             HAL_GPIO_AF_12 /*!< FMC Data line 5                          */
#define HAL_GPIO_AF12_FMC_D6             HAL_GPIO_AF_12 /*!< FMC Data line 6                          */
#define HAL_GPIO_AF12_FMC_D7             HAL_GPIO_AF_12 /*!< FMC Data line 7                          */
#define HAL_GPIO_AF12_FMC_D8             HAL_GPIO_AF_12 /*!< FMC Data line 8                          */
#define HAL_GPIO_AF12_FMC_D9             HAL_GPIO_AF_12 /*!< FMC Data line 9                          */
#define HAL_GPIO_AF12_FMC_D10            HAL_GPIO_AF_12 /*!< FMC Data line 10                         */
#define HAL_GPIO_AF12_FMC_D11            HAL_GPIO_AF_12 /*!< FMC Data line 11                         */
#define HAL_GPIO_AF12_FMC_D12            HAL_GPIO_AF_12 /*!< FMC Data line 12                         */
#define HAL_GPIO_AF12_FMC_D13            HAL_GPIO_AF_12 /*!< FMC Data line 13                         */
#define HAL_GPIO_AF12_FMC_D14            HAL_GPIO_AF_12 /*!< FMC Data line 14                         */
#define HAL_GPIO_AF12_FMC_D15            HAL_GPIO_AF_12 /*!< FMC Data line 15                         */
#define HAL_GPIO_AF12_FMC_INT            HAL_GPIO_AF_12 /*!< FMC NAND flash ready/busy input          */
#define HAL_GPIO_AF12_FMC_NBL1           HAL_GPIO_AF_12 /*!< FMC Byte lane output 1                   */
#define HAL_GPIO_AF12_FMC_NCAS           HAL_GPIO_AF_12 /*!< FMC Column Address Strobe                */
#define HAL_GPIO_AF12_FMC_NCE            HAL_GPIO_AF_12 /*!< FMC NAND Chip select                     */
#define HAL_GPIO_AF12_FMC_NE1            HAL_GPIO_AF_12 /*!< FMC Chip select 1                        */
#define HAL_GPIO_AF12_FMC_NE2            HAL_GPIO_AF_12 /*!< FMC Chip select 2                        */
#define HAL_GPIO_AF12_FMC_NE4            HAL_GPIO_AF_12 /*!< FMC Chip select 4                        */
#define HAL_GPIO_AF12_FMC_NL             HAL_GPIO_AF_12 /*!< FMC Latch enable                         */
#define HAL_GPIO_AF12_FMC_NOE            HAL_GPIO_AF_12 /*!< FMC Output enable A                      */
#define HAL_GPIO_AF12_FMC_NRAS           HAL_GPIO_AF_12 /*!< FMC Row Address Strobe                   */
#define HAL_GPIO_AF12_FMC_NWAIT          HAL_GPIO_AF_12 /*!< FMC NAND flash ready/busy input          */
#define HAL_GPIO_AF12_FMC_NWE            HAL_GPIO_AF_12 /*!< FMC Write enable                         */
#define HAL_GPIO_AF12_FMC_SDCKE0         HAL_GPIO_AF_12 /*!< FMC SDRAM Clock Enable 0                 */
#define HAL_GPIO_AF12_FMC_SDCKE1         HAL_GPIO_AF_12 /*!< FMC SDRAM Clock Enable 1                 */
#define HAL_GPIO_AF12_FMC_SDCLK          HAL_GPIO_AF_12 /*!< FMC SDRAM Clock                          */
#define HAL_GPIO_AF12_FMC_SDNE0          HAL_GPIO_AF_12 /*!< FMC SDRAM Chip Select 0                  */
#define HAL_GPIO_AF12_FMC_SDNE1          HAL_GPIO_AF_12 /*!< FMC SDRAM Chip Select 1                  */
#define HAL_GPIO_AF12_FMC_SDNWE          HAL_GPIO_AF_12 /*!< FMC SDRAM Write Enable                   */
#define HAL_GPIO_AF12_HRTIM1             HAL_GPIO_AF_12 /*!< HRTIM1 Alternate Function mapping        */
#define HAL_GPIO_AF12_HRTIM1_CHA1        HAL_GPIO_AF_12 /*!< HRTIM1 Timer A Output 1                  */
#define HAL_GPIO_AF12_HRTIM1_CHA2        HAL_GPIO_AF_12 /*!< HRTIM1 Timer A Output 2                  */
#define HAL_GPIO_AF12_HRTIM1_CHB2        HAL_GPIO_AF_12 /*!< HRTIM1 Timer B Output 2                  */
#define HAL_GPIO_AF12_HRTIM1_CHD1        HAL_GPIO_AF_12 /*!< HRTIM1 Timer D Output 1                  */
#define HAL_GPIO_AF12_HRTIM1_CHD2        HAL_GPIO_AF_12 /*!< HRTIM1 Timer D Output 2                  */
#define HAL_GPIO_AF12_HRTIM1_EEV3        HAL_GPIO_AF_12 /*!< HRTIM1  External Event 3                 */
#define HAL_GPIO_AF12_HRTIM1_EEV4        HAL_GPIO_AF_12 /*!< HRTIM1  External Event 4                 */
#define HAL_GPIO_AF12_HRTIM1_EEV5        HAL_GPIO_AF_12 /*!< HRTIM1  External Event 5                 */
#define HAL_GPIO_AF12_HRTIM1_EEV6        HAL_GPIO_AF_12 /*!< HRTIM1  External Event 6                 */
#define HAL_GPIO_AF12_HRTIM1_EEV7        HAL_GPIO_AF_12 /*!< HRTIM1  External Event 7                 */
#define HAL_GPIO_AF12_HRTIM1_EEV9        HAL_GPIO_AF_12 /*!< HRTIM1  External Event 9                 */
#define HAL_GPIO_AF12_HRTIM1_EEV15       HAL_GPIO_AF_12 /*!< HRTIM1  External Event 15                */
#define HAL_GPIO_AF12_HRTIM1_FLT1        HAL_GPIO_AF_12 /*!< HRTIM1  Fault 1                          */
#define HAL_GPIO_AF12_HRTIM1_FLT5        HAL_GPIO_AF_12 /*!< HRTIM1  Fault 5                          */
#define HAL_GPIO_AF12_HRTIM2             HAL_GPIO_AF_12 /*!< HRTIM2 Alternate Function mapping        */
#define HAL_GPIO_AF12_HRTIM2_EEV11       HAL_GPIO_AF_12 /*!< HRTIM2  External Event 11                */
#define HAL_GPIO_AF12_HRTIM2_EEV13       HAL_GPIO_AF_12 /*!< HRTIM2  External Event 13                */
#define HAL_GPIO_AF12_HRTIM2_EEV14       HAL_GPIO_AF_12 /*!< HRTIM2  External Event 14                */
#define HAL_GPIO_AF12_HRTIM2_EEV15       HAL_GPIO_AF_12 /*!< HRTIM2  External Event 15                */
#define HAL_GPIO_AF12_HRTIM2_FLT1        HAL_GPIO_AF_12 /*!< HRTIM2  Fault 1                          */
#define HAL_GPIO_AF12_HRTIM2_FLT2        HAL_GPIO_AF_12 /*!< HRTIM2  Fault 2                          */
#define HAL_GPIO_AF12_HRTIM2_FLT3        HAL_GPIO_AF_12 /*!< HRTIM2  Fault 3                          */
#define HAL_GPIO_AF12_HRTIM2_FLT5        HAL_GPIO_AF_12 /*!< HRTIM2  Fault 5                          */
#define HAL_GPIO_AF12_HRTIM2_FLT8        HAL_GPIO_AF_12 /*!< HRTIM2  Fault 8                          */
#define HAL_GPIO_AF12_SDMMC1             HAL_GPIO_AF_12 /*!< SDMMC1 Alternate Function mapping        */
#define HAL_GPIO_AF12_SDMMC1_D4          HAL_GPIO_AF_12 /*!< SDMMC1 Card bidirectional data line 4    */
#define HAL_GPIO_AF12_SDMMC1_D5          HAL_GPIO_AF_12 /*!< SDMMC1 Card bidirectional data line 5    */
#define HAL_GPIO_AF12_SDMMC1_D7          HAL_GPIO_AF_12 /*!< SDMMC1 Card bidirectional data line 7    */
#define HAL_GPIO_AF12_XSPI1              HAL_GPIO_AF_12 /*!< XSPI1 Alternate Function mapping         */
#define HAL_GPIO_AF12_XSPI1_CLK          HAL_GPIO_AF_12 /*!< XSPI1 Clock                              */
#define HAL_GPIO_AF12_XSPI1_IO7          HAL_GPIO_AF_12 /*!< XSPI1 Data Pin 7                         */
#define HAL_GPIO_AF12_XSPI1_NCLK         HAL_GPIO_AF_12 /*!< XSPI1 Inverted Clock                     */

/**
  * @brief   AF 13 selection
  */
#define HAL_GPIO_AF13_ADF1               HAL_GPIO_AF_13 /*!< ADF1 Alternate Function mapping            */
#define HAL_GPIO_AF13_ADF1_CCK0          HAL_GPIO_AF_13 /*!< ADF1 External sensors clock 0              */
#define HAL_GPIO_AF13_ADF1_CCK1          HAL_GPIO_AF_13 /*!< ADF1 External sensors clock 1              */
#define HAL_GPIO_AF13_ADF1_SDI0          HAL_GPIO_AF_13 /*!< ADF1 Data from external sensors            */
#define HAL_GPIO_AF13_COMP1              HAL_GPIO_AF_13 /*!< COMP1 Alternate Function mapping           */
#define HAL_GPIO_AF13_COMP1_OUT          HAL_GPIO_AF_13 /*!< COMP1 Output channel                       */
#define HAL_GPIO_AF13_COMP4              HAL_GPIO_AF_13 /*!< COMP4 Alternate Function mapping           */
#define HAL_GPIO_AF13_COMP4_OUT          HAL_GPIO_AF_13 /*!< COMP4 Output channel                       */
#define HAL_GPIO_AF13_COMP6              HAL_GPIO_AF_13 /*!< COMP6 Alternate Function mapping           */
#define HAL_GPIO_AF13_COMP6_OUT          HAL_GPIO_AF_13 /*!< COMP6 Output channel                       */
#define HAL_GPIO_AF13_COMP7              HAL_GPIO_AF_13 /*!< COMP7 Alternate Function mapping           */
#define HAL_GPIO_AF13_COMP7_OUT          HAL_GPIO_AF_13 /*!< COMP7 Output channel                       */
#define HAL_GPIO_AF13_FDCAN1             HAL_GPIO_AF_13 /*!< FDCAN1 Alternate Function mapping          */
#define HAL_GPIO_AF13_FDCAN1_RX          HAL_GPIO_AF_13 /*!< FDCAN1 Receive pin                         */
#define HAL_GPIO_AF13_FDCAN1_TX          HAL_GPIO_AF_13 /*!< FDCAN1 Transmit pin                        */
#define HAL_GPIO_AF13_FDCAN2             HAL_GPIO_AF_13 /*!< FDCAN2 Alternate Function mapping          */
#define HAL_GPIO_AF13_FDCAN2_RX          HAL_GPIO_AF_13 /*!< FDCAN2 Receive pin                         */
#define HAL_GPIO_AF13_FDCAN2_TX          HAL_GPIO_AF_13 /*!< FDCAN2 Transmit pin                        */
#define HAL_GPIO_AF13_FMC                HAL_GPIO_AF_13 /*!< FMC Alternate Function mapping             */
#define HAL_GPIO_AF13_FMC_NE3            HAL_GPIO_AF_13 /*!< FMC Chip select 3                          */
#define HAL_GPIO_AF13_HRTIM2             HAL_GPIO_AF_13 /*!< HRTIM2 Alternate Function mapping          */
#define HAL_GPIO_AF13_HRTIM2_CHC1        HAL_GPIO_AF_13 /*!< HRTIM2 Timer C Output 1                    */
#define HAL_GPIO_AF13_HRTIM2_EEV1        HAL_GPIO_AF_13 /*!< HRTIM2 External Event 1                    */
#define HAL_GPIO_AF13_HRTIM2_EEV2        HAL_GPIO_AF_13 /*!< HRTIM2 External Event 2                    */
#define HAL_GPIO_AF13_HRTIM2_EEV4        HAL_GPIO_AF_13 /*!< HRTIM2 External Event 4                    */
#define HAL_GPIO_AF13_HRTIM2_EEV6        HAL_GPIO_AF_13 /*!< HRTIM2 External Event 6                    */
#define HAL_GPIO_AF13_HRTIM2_EEV7        HAL_GPIO_AF_13 /*!< HRTIM2 External Event 7                    */
#define HAL_GPIO_AF13_HRTIM2_EEV8        HAL_GPIO_AF_13 /*!< HRTIM2 External Event 8                    */
#define HAL_GPIO_AF13_HRTIM2_EEV9        HAL_GPIO_AF_13 /*!< HRTIM2 External Event 9                    */
#define HAL_GPIO_AF13_HRTIM2_EEV10       HAL_GPIO_AF_13 /*!< HRTIM2 External Event 10                   */
#define HAL_GPIO_AF13_HRTIM2_FLT1        HAL_GPIO_AF_13 /*!< HRTIM2 Fault 1                             */
#define HAL_GPIO_AF13_HRTIM2_FLT2        HAL_GPIO_AF_13 /*!< HRTIM2 Fault 2                             */
#define HAL_GPIO_AF13_HRTIM2_FLT4        HAL_GPIO_AF_13 /*!< HRTIM2 Fault 4                             */
#define HAL_GPIO_AF13_HRTIM2_FLT5        HAL_GPIO_AF_13 /*!< HRTIM2 Fault 5                             */
#define HAL_GPIO_AF13_HRTIM2_FLT6        HAL_GPIO_AF_13 /*!< HRTIM2 Fault 6                             */
#define HAL_GPIO_AF13_HRTIM2_FLT7        HAL_GPIO_AF_13 /*!< HRTIM2 Fault 7                             */
#define HAL_GPIO_AF13_HRTIM2_SCIN        HAL_GPIO_AF_13 /*!< HRTIM2 Synchronization Input               */
#define HAL_GPIO_AF13_HRTIM2_SCOUT       HAL_GPIO_AF_13 /*!< HRTIM2 Synchronization Output              */
#define HAL_GPIO_AF13_HSP1               HAL_GPIO_AF_13 /*!< HSP1 Alternate Function mapping            */
#define HAL_GPIO_AF13_HSP1_SNP0          HAL_GPIO_AF_13 /*!< HSP1 Snap or Sample Point 0                */
#define HAL_GPIO_AF13_LPTIM4             HAL_GPIO_AF_13 /*!< LPTIM4 Alternate Function mapping          */
#define HAL_GPIO_AF13_LPTIM4_ETR         HAL_GPIO_AF_13 /*!< LPTIM4 External trigger input              */
#define HAL_GPIO_AF13_LPTIM4_OUT         HAL_GPIO_AF_13 /*!< LPTIM4 Output                              */
#define HAL_GPIO_AF13_LPTIM5             HAL_GPIO_AF_13 /*!< LPTIM5 Alternate Function mapping          */
#define HAL_GPIO_AF13_LPTIM5_ETR         HAL_GPIO_AF_13 /*!< LPTIM5 External trigger input              */
#define HAL_GPIO_AF13_LPTIM5_IN1         HAL_GPIO_AF_13 /*!< LPTIM5 Channel 1 Input                     */
#define HAL_GPIO_AF13_LPTIM5_OUT         HAL_GPIO_AF_13 /*!< LPTIM5 Output                              */
#define HAL_GPIO_AF13_SDMMC1             HAL_GPIO_AF_13 /*!< SDMMC1 Alternate Function mapping          */
#define HAL_GPIO_AF13_SDMMC1_D2          HAL_GPIO_AF_13 /*!< SDMMC1 Card bidirectional data line 2      */
#define HAL_GPIO_AF13_TIM12              HAL_GPIO_AF_13 /*!< TIM12 Alternate Function mapping           */
#define HAL_GPIO_AF13_TIM12_CH2          HAL_GPIO_AF_13 /*!< TIM12 Multi-purpose Channel 2              */
#define HAL_GPIO_AF13_TIM15              HAL_GPIO_AF_13 /*!< TIM15 Alternate Function mapping           */
#define HAL_GPIO_AF13_TIM15_BKIN         HAL_GPIO_AF_13 /*!< TIM15 Break input                          */
#define HAL_GPIO_AF13_UART7              HAL_GPIO_AF_13 /*!< UART7 Alternate Function mapping           */
#define HAL_GPIO_AF13_UART7_RX           HAL_GPIO_AF_13 /*!< UART7 Serial Data Receive Input            */
#define HAL_GPIO_AF13_UART7_TX           HAL_GPIO_AF_13 /*!< UART7 Transmit Data Output                 */
#define HAL_GPIO_AF13_UCPD1              HAL_GPIO_AF_13 /*!< UCPD1 Alternate Function mapping           */
#define HAL_GPIO_AF13_UCPD1_FRSTX1       HAL_GPIO_AF_13 /*!< UCPD1 Fast Role Swap signaling output 1    */
#define HAL_GPIO_AF13_UCPD1_FRSTX2       HAL_GPIO_AF_13 /*!< UCPD1 Fast Role Swap signaling output 2    */

/**
  * @brief   AF 14 selection
  */
#define HAL_GPIO_AF14_ADF1               HAL_GPIO_AF_14 /*!< ADF1 Alternate Function mapping                   */
#define HAL_GPIO_AF14_ADF1_CCK0          HAL_GPIO_AF_14 /*!< ADF1 External sensors clock 0                     */
#define HAL_GPIO_AF14_ADF1_CCK1          HAL_GPIO_AF_14 /*!< ADF1 External sensors clock 1                     */
#define HAL_GPIO_AF14_ADF1_SDI0          HAL_GPIO_AF_14 /*!< ADF1 Data from external sensors                   */
#define HAL_GPIO_AF14_COMP2              HAL_GPIO_AF_14 /*!< COMP2 Alternate Function mapping                  */
#define HAL_GPIO_AF14_COMP2_OUT          HAL_GPIO_AF_14 /*!< COMP2 Output channel                              */
#define HAL_GPIO_AF14_COMP3              HAL_GPIO_AF_14 /*!< COMP3 Alternate Function mapping                  */
#define HAL_GPIO_AF14_COMP3_OUT          HAL_GPIO_AF_14 /*!< COMP3 Output channel                              */
#define HAL_GPIO_AF14_COMP5              HAL_GPIO_AF_14 /*!< COMP5 Alternate Function mapping                  */
#define HAL_GPIO_AF14_COMP5_OUT          HAL_GPIO_AF_14 /*!< COMP5 Output channel                              */
#define HAL_GPIO_AF14_COMP6              HAL_GPIO_AF_14 /*!< COMP6 Alternate Function mapping                  */
#define HAL_GPIO_AF14_COMP6_OUT          HAL_GPIO_AF_14 /*!< COMP6 Output channel                              */
#define HAL_GPIO_AF14_COMP8              HAL_GPIO_AF_14 /*!< COMP8 Alternate Function mapping                  */
#define HAL_GPIO_AF14_COMP8_OUT          HAL_GPIO_AF_14 /*!< COMP8 Output channel                              */
#define HAL_GPIO_AF14_CRS                HAL_GPIO_AF_14 /*!< CRS Alternate Function mapping                    */
#define HAL_GPIO_AF14_CRS_SYNC           HAL_GPIO_AF_14 /*!< CRS Synchronization source                        */
#define HAL_GPIO_AF14_SDMMC1             HAL_GPIO_AF_14 /*!< SDMMC1 Alternate Function mapping                 */
#define HAL_GPIO_AF14_SDMMC1_CDIR        HAL_GPIO_AF_14 /*!< SDMMC1 Card I/O signal direction indication       */
#define HAL_GPIO_AF14_SDMMC1_CK          HAL_GPIO_AF_14 /*!< SDMMC1 Card clock                                 */
#define HAL_GPIO_AF14_SDMMC1_CMD         HAL_GPIO_AF_14 /*!< SDMMC1 Card bidirectional command/response signal */
#define HAL_GPIO_AF14_SDMMC1_D0          HAL_GPIO_AF_14 /*!< SDMMC2 Card bidirectional data line 0             */
#define HAL_GPIO_AF14_SDMMC1_D1          HAL_GPIO_AF_14 /*!< SDMMC2 Card bidirectional data line 1             */
#define HAL_GPIO_AF14_SDMMC1_D2          HAL_GPIO_AF_14 /*!< SDMMC2 Card bidirectional data line 2             */
#define HAL_GPIO_AF14_SDMMC1_D3          HAL_GPIO_AF_14 /*!< SDMMC2 Card bidirectional data line 3             */
#define HAL_GPIO_AF14_TIM2               HAL_GPIO_AF_14 /*!< TIM2 Alternate Function mapping                   */
#define HAL_GPIO_AF14_TIM2_CH1           HAL_GPIO_AF_14 /*!< TIM2 Multi-purpose Channel 1                      */
#define HAL_GPIO_AF14_TIM8               HAL_GPIO_AF_14 /*!< TIM8 Alternate Function mapping                   */
#define HAL_GPIO_AF14_TIM8_BKIN          HAL_GPIO_AF_14 /*!< TIM8 Break input                                  */
#define HAL_GPIO_AF14_TIM8_BKIN2         HAL_GPIO_AF_14 /*!< TIM8 Break input 2                                */
#define HAL_GPIO_AF14_TIM8_CH1           HAL_GPIO_AF_14 /*!< TIM8 Multi-purpose Channel 1                      */
#define HAL_GPIO_AF14_TIM8_CH3N          HAL_GPIO_AF_14 /*!< TIM8 CH3 complementary output                     */
#define HAL_GPIO_AF14_TIM8_CH4N          HAL_GPIO_AF_14 /*!< TIM8 CH4 complementary output                     */
#define HAL_GPIO_AF14_TIM10              HAL_GPIO_AF_14 /*!< TIM10 Alternate Function mapping                  */
#define HAL_GPIO_AF14_TIM10_CH1          HAL_GPIO_AF_14 /*!< TIM10 Multi-purpose Channel 1                     */
#define HAL_GPIO_AF14_TIM12              HAL_GPIO_AF_14 /*!< TIM12 Alternate Function mapping                  */
#define HAL_GPIO_AF14_TIM12_CH1          HAL_GPIO_AF_14 /*!< TIM12 Multi-purpose Channel 1                     */
#define HAL_GPIO_AF14_TIM12_CH2          HAL_GPIO_AF_14 /*!< TIM12 Multi-purpose Channel 2                     */
#define HAL_GPIO_AF14_TIM13              HAL_GPIO_AF_14 /*!< TIM13 Alternate Function mapping                  */
#define HAL_GPIO_AF14_TIM13_CH1          HAL_GPIO_AF_14 /*!< TIM13 Multi-purpose Channel 1                     */
#define HAL_GPIO_AF14_TIM15              HAL_GPIO_AF_14 /*!< TIM15 Alternate Function mapping                  */
#define HAL_GPIO_AF14_TIM15_CH1N         HAL_GPIO_AF_14 /*!< TIM15 CH1 complementary output                    */
#define HAL_GPIO_AF14_TIM20              HAL_GPIO_AF_14 /*!< TIM20 Alternate Function mapping                  */
#define HAL_GPIO_AF14_TIM20_CH1N         HAL_GPIO_AF_14 /*!< TIM20 CH1 complementary output                    */
#define HAL_GPIO_AF14_UART5              HAL_GPIO_AF_14 /*!< UART5 Alternate Function mapping                  */
#define HAL_GPIO_AF14_UART5_CTS          HAL_GPIO_AF_14 /*!< UART5 Clear to send                               */
#define HAL_GPIO_AF14_UART5_RTS          HAL_GPIO_AF_14 /*!< UART5 Request to send                             */
#define HAL_GPIO_AF14_UART5_RX           HAL_GPIO_AF_14 /*!< UART5 Serial Data Receive Input                   */
#define HAL_GPIO_AF14_UART5_TX           HAL_GPIO_AF_14 /*!< UART5 Transmit Data Output                        */
#define HAL_GPIO_AF14_UART7              HAL_GPIO_AF_14 /*!< UART7 Alternate Function mapping                  */
#define HAL_GPIO_AF14_UART7_RX           HAL_GPIO_AF_14 /*!< UART7 Serial Data Receive Input                   */
#define HAL_GPIO_AF14_UART7_TX           HAL_GPIO_AF_14 /*!< UART7 Transmit Data Output                        */

/**
  * @brief   AF 15 selection
  */
#define HAL_GPIO_AF15_EVENTOUT           HAL_GPIO_AF_15 /*!< EVENTOUT Alternate Function mapping */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Functions HAL GPIO Functions
  * @{
  */

/** @defgroup GPIO_Exported_Functions_Group1 Initialization/de-initialization functions
  * @{
  */

hal_status_t  HAL_GPIO_Init(hal_gpio_t gpiox, uint32_t pins, const hal_gpio_config_t *p_config);
void          HAL_GPIO_DeInit(hal_gpio_t  gpiox, uint32_t pins);

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions
  * @{
  */

hal_gpio_pin_state_t HAL_GPIO_ReadPin(hal_gpio_t gpiox, uint32_t pin);
void HAL_GPIO_WritePin(hal_gpio_t gpiox, uint32_t pins, hal_gpio_pin_state_t pin_state);
void HAL_GPIO_WriteMultipleStatePin(hal_gpio_t gpiox, uint32_t pins_reset, uint32_t pins_set);
void HAL_GPIO_TogglePin(hal_gpio_t gpiox, uint32_t pins);
hal_status_t HAL_GPIO_LockPin(hal_gpio_t gpiox, uint32_t pins);
#if defined(USE_HAL_GPIO_HSLV) && (USE_HAL_GPIO_HSLV == 1U)
void HAL_GPIO_EnableHighSpeedLowVoltage(void);
void HAL_GPIO_DisableHighSpeedLowVoltage(void);
#endif /* USE_HAL_GPIO_HSLV */
GPIO_TypeDef *HAL_GPIO_GetLLInstance(hal_gpio_t gpiox);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* GPIOA || GPIOB || GPIOC || GPIOD || GPIOE || GPIOF || GPIOG || GPIOH || GPIOI */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_HAL_GPIO_H */
