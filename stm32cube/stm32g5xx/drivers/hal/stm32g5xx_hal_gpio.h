/**
  **********************************************************************************************************************
  * @file    stm32g5xx_hal_gpio.h
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
#ifndef STM32G5XX_HAL_GPIO_H
#define STM32G5XX_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_gpio.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */
#if defined (GPIOA) || defined (GPIOB) || defined (GPIOC) || defined (GPIOD) || defined (GPIOE) || defined (GPIOF) \
    || defined (GPIOG) || defined (GPIOH)

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
  * @brief  GPIO Security access level attribute.
  */
typedef enum
{
  HAL_GPIO_NSEC = LL_GPIO_ATTR_NSEC, /*!< I/O pin is nonsecure. */
  HAL_GPIO_SEC  = LL_GPIO_ATTR_SEC   /*!< I/O pin is secure.    */
} hal_gpio_sec_attr_t;

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
#if defined (STM32G5_DEVICE_ID) && (STM32G5_DEVICE_ID == 0x44AU)
/**
  * @brief   AF 0 selection
  */
#define HAL_GPIO_AF0_AUDIOCLK              HAL_GPIO_AF_0  /*!< Audio Clock                       */
#define HAL_GPIO_AF0_DBTRGI                HAL_GPIO_AF_0  /*!< DBTRGI                            */
#define HAL_GPIO_AF0_DBTRGIO               HAL_GPIO_AF_0  /*!< DBTRGIO                           */
#define HAL_GPIO_AF0_DBTRGO                HAL_GPIO_AF_0  /*!< DBTRGO                            */
#define HAL_GPIO_AF0_JTCK                  HAL_GPIO_AF_0  /*!< JTAG Test Clock                   */
#define HAL_GPIO_AF0_JTDI                  HAL_GPIO_AF_0  /*!< JTAG Test Data In                 */
#define HAL_GPIO_AF0_JTDO                  HAL_GPIO_AF_0  /*!< JTAG Test Data Out                */
#define HAL_GPIO_AF0_JTMS                  HAL_GPIO_AF_0  /*!< JTAG Test Mode Select             */
#define HAL_GPIO_AF0_MCO                   HAL_GPIO_AF_0  /*!< MCO Alternate Function mapping    */
#define HAL_GPIO_AF0_MCO1                  HAL_GPIO_AF_0  /*!< MCO1                              */
#define HAL_GPIO_AF0_MCO2                  HAL_GPIO_AF_0  /*!< MCO2                              */
#define HAL_GPIO_AF0_NJTRST                HAL_GPIO_AF_0  /*!< NJTRST                            */
#define HAL_GPIO_AF0_PWR                   HAL_GPIO_AF_0  /*!< PWR Alternate Function mapping    */
#define HAL_GPIO_AF0_PWR_CSLEEP            HAL_GPIO_AF_0  /*!< PWR CSLEEP mode                   */
#define HAL_GPIO_AF0_PWR_CSTOP             HAL_GPIO_AF_0  /*!< PWR CSTOP mode                    */
#define HAL_GPIO_AF0_RTC                   HAL_GPIO_AF_0  /*!< RTC Alternate Function mapping    */
#define HAL_GPIO_AF0_RTC_OUT2              HAL_GPIO_AF_0  /*!< RTC Output 2                      */
#define HAL_GPIO_AF0_RTC_REFIN             HAL_GPIO_AF_0  /*!< RTC Reference input               */
#define HAL_GPIO_AF0_SWCLK                 HAL_GPIO_AF_0  /*!< Serial Wire Clock                 */
#define HAL_GPIO_AF0_SWDIO                 HAL_GPIO_AF_0  /*!< Serial Wire Debug Input/Output    */
#define HAL_GPIO_AF0_TRACECLK              HAL_GPIO_AF_0  /*!< TRACE Clock                       */
#define HAL_GPIO_AF0_TRACED0               HAL_GPIO_AF_0  /*!< TRACE Data Output 0               */
#define HAL_GPIO_AF0_TRACED1               HAL_GPIO_AF_0  /*!< TRACE Data Output 1               */
#define HAL_GPIO_AF0_TRACED2               HAL_GPIO_AF_0  /*!< TRACE Data Output 2               */
#define HAL_GPIO_AF0_TRACED3               HAL_GPIO_AF_0  /*!< TRACE Data Output 3               */
#define HAL_GPIO_AF0_TRACESWO              HAL_GPIO_AF_0  /*!< TRACE Serial Wire Output          */

/**
  * @brief   AF 1 selection
  */
#if defined (HRTIM1)
#define HAL_GPIO_AF1_HRTIM1                HAL_GPIO_AF_1  /*!< HRTIM1 Alternate Function mapping */
#define HAL_GPIO_AF1_HRTIM1_CHB1           HAL_GPIO_AF_1  /*!< HRTIM1 Timer B Output 1           */
#define HAL_GPIO_AF1_HRTIM1_CHC1           HAL_GPIO_AF_1  /*!< HRTIM1 Timer C Output 1           */
#define HAL_GPIO_AF1_HRTIM1_CHC2           HAL_GPIO_AF_1  /*!< HRTIM1 Timer C Output 2           */
#define HAL_GPIO_AF1_HRTIM1_EEV1           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 1           */
#define HAL_GPIO_AF1_HRTIM1_EEV2           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 2           */
#define HAL_GPIO_AF1_HRTIM1_EEV4           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 4           */
#define HAL_GPIO_AF1_HRTIM1_EEV5           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 5           */
#define HAL_GPIO_AF1_HRTIM1_EEV6           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 6           */
#define HAL_GPIO_AF1_HRTIM1_EEV7           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 7           */
#define HAL_GPIO_AF1_HRTIM1_EEV8           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 8           */
#define HAL_GPIO_AF1_HRTIM1_EEV9           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 9           */
#define HAL_GPIO_AF1_HRTIM1_EEV10          HAL_GPIO_AF_1  /*!< HRTIM1 External Event 10          */
#define HAL_GPIO_AF1_HRTIM1_EEV11          HAL_GPIO_AF_1  /*!< HRTIM1 External Event 11          */
#define HAL_GPIO_AF1_HRTIM1_FLT1           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 1                    */
#define HAL_GPIO_AF1_HRTIM1_FLT2           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 2                    */
#define HAL_GPIO_AF1_HRTIM1_FLT3           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 3                    */
#define HAL_GPIO_AF1_HRTIM1_FLT4           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 4                    */
#define HAL_GPIO_AF1_HRTIM1_FLT5           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 5                    */
#define HAL_GPIO_AF1_HRTIM1_FLT6           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 6                    */
#define HAL_GPIO_AF1_HRTIM1_FLT7           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 7                    */
#define HAL_GPIO_AF1_HRTIM1_SCIN           HAL_GPIO_AF_1  /*!< HRTIM1 Synchronization Input      */
#define HAL_GPIO_AF1_HRTIM1_SCOUT          HAL_GPIO_AF_1  /*!< HRTIM1 Synchronization Output     */
#endif /* HRTIM1 */
#define HAL_GPIO_AF1_LPTIM1                HAL_GPIO_AF_1  /*!< LPTIM1 Alternate Function mapping */
#define HAL_GPIO_AF1_LPTIM1_CH1            HAL_GPIO_AF_1  /*!< LPTIM1 Multi-purpose Channel 1    */
#define HAL_GPIO_AF1_LPTIM1_ETR            HAL_GPIO_AF_1  /*!< LPTIM1 External trigger input     */
#define HAL_GPIO_AF1_LPTIM1_IN2            HAL_GPIO_AF_1  /*!< LPTIM1 Channel 2 Input            */
#define HAL_GPIO_AF1_TIM1                  HAL_GPIO_AF_1  /*!< TIM1 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM1_BKIN2            HAL_GPIO_AF_1  /*!< TIM1 Break input 2                */
#define HAL_GPIO_AF1_TIM1_CH2              HAL_GPIO_AF_1  /*!< TIM1 Multi-purpose Channel 2      */
#define HAL_GPIO_AF1_TIM1_CH3              HAL_GPIO_AF_1  /*!< TIM1 Multi-purpose Channel 3      */
#define HAL_GPIO_AF1_TIM1_CH4N             HAL_GPIO_AF_1  /*!< TIM1 CH4 complementary output     */
#define HAL_GPIO_AF1_TIM1_ETR              HAL_GPIO_AF_1  /*!< TIM1 External trigger input       */
#define HAL_GPIO_AF1_TIM2                  HAL_GPIO_AF_1  /*!< TIM2 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM2_CH1              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 1      */
#define HAL_GPIO_AF1_TIM2_CH2              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 2      */
#define HAL_GPIO_AF1_TIM2_CH3              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 3      */
#define HAL_GPIO_AF1_TIM2_CH4              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 4      */
#define HAL_GPIO_AF1_TIM5                  HAL_GPIO_AF_1  /*!< TIM5 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM5_CH1              HAL_GPIO_AF_1  /*!< TIM5 Multi-purpose Channel 1      */
#define HAL_GPIO_AF1_TIM5_CH3              HAL_GPIO_AF_1  /*!< TIM5 Multi-purpose Channel 3      */
#define HAL_GPIO_AF1_TIM5_ETR              HAL_GPIO_AF_1  /*!< TIM5 External trigger input       */
#define HAL_GPIO_AF1_TIM15                 HAL_GPIO_AF_1  /*!< TIM15 Alternate Function mapping  */
#define HAL_GPIO_AF1_TIM15_BKIN            HAL_GPIO_AF_1  /*!< TIM15 Break input                 */
#define HAL_GPIO_AF1_TIM15_CH1             HAL_GPIO_AF_1  /*!< TIM15 Multi-purpose Channel 1     */
#define HAL_GPIO_AF1_TIM15_CH2             HAL_GPIO_AF_1  /*!< TIM15 Multi-purpose Channel 2     */
#define HAL_GPIO_AF1_TIM16                 HAL_GPIO_AF_1  /*!< TIM16 Alternate Function mapping  */
#define HAL_GPIO_AF1_TIM16_BKIN            HAL_GPIO_AF_1  /*!< TIM16 Break input                 */
#define HAL_GPIO_AF1_TIM16_CH1             HAL_GPIO_AF_1  /*!< TIM16 Multi-purpose Channel 1     */
#define HAL_GPIO_AF1_TIM16_CH1N            HAL_GPIO_AF_1  /*!< TIM16 CH1 complementary output    */
#define HAL_GPIO_AF1_TIM17                 HAL_GPIO_AF_1  /*!< TIM17 Alternate Function mapping  */
#define HAL_GPIO_AF1_TIM17_BKIN            HAL_GPIO_AF_1  /*!< TIM17 Break input                 */
#define HAL_GPIO_AF1_TIM17_CH1             HAL_GPIO_AF_1  /*!< TIM17 Multi-purpose Channel 1     */

/**
  * @brief   AF 2 selection
  */
#define HAL_GPIO_AF2_I2C2                  HAL_GPIO_AF_2  /*!< I2C2 Alternate Function mapping   */
#define HAL_GPIO_AF2_I2C2_SMBA             HAL_GPIO_AF_2  /*!< I2C2 SMBus Alert                  */
#define HAL_GPIO_AF2_I2S1                  HAL_GPIO_AF_2  /*!< I2S1 Alternate Function mapping   */
#define HAL_GPIO_AF2_I2S1_CK               HAL_GPIO_AF_2  /*!< I2S1 Clock                        */
#define HAL_GPIO_AF2_I2S1_SDI              HAL_GPIO_AF_2  /*!< I2S1 Serial Data Input            */
#define HAL_GPIO_AF2_I2S1_SDO              HAL_GPIO_AF_2  /*!< I2S1 Serial Data Output           */
#define HAL_GPIO_AF2_I2S1_WS               HAL_GPIO_AF_2  /*!< I2S1 Word Select                  */
#define HAL_GPIO_AF2_SPI1                  HAL_GPIO_AF_2  /*!< SPI1 Alternate Function mapping   */
#define HAL_GPIO_AF2_SPI1_MISO             HAL_GPIO_AF_2  /*!< SPI1 Master-In/Slave-Out          */
#define HAL_GPIO_AF2_SPI1_MOSI             HAL_GPIO_AF_2  /*!< SPI1 Master-Out/Slave-In          */
#define HAL_GPIO_AF2_SPI1_NSS              HAL_GPIO_AF_2  /*!< SPI1 Slave Select                 */
#define HAL_GPIO_AF2_SPI1_SCK              HAL_GPIO_AF_2  /*!< SPI1 Serial Clock                 */
#define HAL_GPIO_AF2_TIM1                  HAL_GPIO_AF_2  /*!< TIM1 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM1_BKIN             HAL_GPIO_AF_2  /*!< TIM1 Break input                  */
#define HAL_GPIO_AF2_TIM1_BKIN2            HAL_GPIO_AF_2  /*!< TIM1 Break input 2                */
#define HAL_GPIO_AF2_TIM1_CH1              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM1_CH1N             HAL_GPIO_AF_2  /*!< TIM1 CH1 complementary output     */
#define HAL_GPIO_AF2_TIM1_CH2              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM1_CH2N             HAL_GPIO_AF_2  /*!< TIM1 CH2 complementary output     */
#define HAL_GPIO_AF2_TIM1_CH3              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM1_CH3N             HAL_GPIO_AF_2  /*!< TIM1 CH3 complementary output     */
#define HAL_GPIO_AF2_TIM1_CH4              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_TIM1_ETR              HAL_GPIO_AF_2  /*!< TIM1 External trigger input       */
#define HAL_GPIO_AF2_TIM2                  HAL_GPIO_AF_2  /*!< TIM2 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM2_CH1              HAL_GPIO_AF_2  /*!< TIM2 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM2_CH2              HAL_GPIO_AF_2  /*!< TIM2 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM2_CH3              HAL_GPIO_AF_2  /*!< TIM2 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM2_ETR              HAL_GPIO_AF_2  /*!< TIM2 External trigger input       */
#define HAL_GPIO_AF2_TIM3                  HAL_GPIO_AF_2  /*!< TIM3 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM3_CH1              HAL_GPIO_AF_2  /*!< TIM3 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM3_CH2              HAL_GPIO_AF_2  /*!< TIM3 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM3_CH3              HAL_GPIO_AF_2  /*!< TIM3 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM3_CH4              HAL_GPIO_AF_2  /*!< TIM3 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_TIM3_ETR              HAL_GPIO_AF_2  /*!< TIM3 External trigger input       */
#define HAL_GPIO_AF2_TIM4                  HAL_GPIO_AF_2  /*!< TIM4 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM4_CH1              HAL_GPIO_AF_2  /*!< TIM4 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM4_CH2              HAL_GPIO_AF_2  /*!< TIM4 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM4_CH3              HAL_GPIO_AF_2  /*!< TIM4 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM4_CH4              HAL_GPIO_AF_2  /*!< TIM4 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_TIM4_ETR              HAL_GPIO_AF_2  /*!< TIM4 External trigger input       */
#define HAL_GPIO_AF2_TIM5                  HAL_GPIO_AF_2  /*!< TIM5 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM5_CH1              HAL_GPIO_AF_2  /*!< TIM5 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM5_CH2              HAL_GPIO_AF_2  /*!< TIM5 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM5_CH3              HAL_GPIO_AF_2  /*!< TIM5 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM5_CH4              HAL_GPIO_AF_2  /*!< TIM5 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_TIM15                 HAL_GPIO_AF_2  /*!< TIM15 Alternate Function mapping  */
#define HAL_GPIO_AF2_TIM15_BKIN            HAL_GPIO_AF_2  /*!< TIM15 Break input                 */
#define HAL_GPIO_AF2_TIM15_CH1N            HAL_GPIO_AF_2  /*!< TIM15 CH1 complementary output    */

/**
  * @brief   AF 3 selection
  */
#define HAL_GPIO_AF3_I3C1                  HAL_GPIO_AF_3  /*!< I3C1 Alternate Function mapping    */
#define HAL_GPIO_AF3_I3C1_SCL              HAL_GPIO_AF_3  /*!< I3C1 Clock                         */
#define HAL_GPIO_AF3_I3C1_SDA              HAL_GPIO_AF_3  /*!< I3C1 Data                          */
#define HAL_GPIO_AF3_LPUART1               HAL_GPIO_AF_3  /*!< LPUART1 Alternate Function mapping */
#define HAL_GPIO_AF3_LPUART1_CTS           HAL_GPIO_AF_3  /*!< LPUART1 Clear to send              */
#define HAL_GPIO_AF3_LPUART1_RTS           HAL_GPIO_AF_3  /*!< LPUART1 Request to send            */
#define HAL_GPIO_AF3_LPUART1_RX            HAL_GPIO_AF_3  /*!< LPUART1 Serial Data Receive Input  */
#define HAL_GPIO_AF3_LPUART1_TX            HAL_GPIO_AF_3  /*!< LPUART1 Transmit Data Output       */
#define HAL_GPIO_AF3_TIM8                  HAL_GPIO_AF_3  /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF3_TIM8_BKIN2            HAL_GPIO_AF_3  /*!< TIM8 Break input 2                 */
#define HAL_GPIO_AF3_TIM8_CH1              HAL_GPIO_AF_3  /*!< TIM8 Multi-purpose Channel 1       */
#define HAL_GPIO_AF3_TIM8_CH1N             HAL_GPIO_AF_3  /*!< TIM8 CH1 complementary output      */
#define HAL_GPIO_AF3_TIM8_CH3              HAL_GPIO_AF_3  /*!< TIM8 Multi-purpose Channel 3       */
#define HAL_GPIO_AF3_TIM15                 HAL_GPIO_AF_3  /*!< TIM15 Alternate Function mapping   */
#define HAL_GPIO_AF3_TIM15_CH1             HAL_GPIO_AF_3  /*!< TIM15 Multi-purpose Channel 1      */
#define HAL_GPIO_AF3_TIM15_CH2             HAL_GPIO_AF_3  /*!< TIM15 Multi-purpose Channel 2      */
#define HAL_GPIO_AF3_XSPI1                 HAL_GPIO_AF_3  /*!< XSPI1 Alternate Function mapping   */
#define HAL_GPIO_AF3_XSPI1_CLK             HAL_GPIO_AF_3  /*!< XSPI1 Clock                        */
#define HAL_GPIO_AF3_XSPI1_DQS0            HAL_GPIO_AF_3  /*!< XSPI1 Memory Data Strobe I/O       */
#define HAL_GPIO_AF3_XSPI1_IO0             HAL_GPIO_AF_3  /*!< XSPI1 Data pin 0                   */
#define HAL_GPIO_AF3_XSPI1_IO1             HAL_GPIO_AF_3  /*!< XSPI1 Data pin 1                   */
#define HAL_GPIO_AF3_XSPI1_IO2             HAL_GPIO_AF_3  /*!< XSPI1 Data pin 2                   */
#define HAL_GPIO_AF3_XSPI1_IO3             HAL_GPIO_AF_3  /*!< XSPI1 Data pin 3                   */
#define HAL_GPIO_AF3_XSPI1_IO5             HAL_GPIO_AF_3  /*!< XSPI1 Data pin 5                   */
#define HAL_GPIO_AF3_XSPI1_IO6             HAL_GPIO_AF_3  /*!< XSPI1 Data pin 6                   */
#define HAL_GPIO_AF3_XSPI1_IO7             HAL_GPIO_AF_3  /*!< XSPI1 Data pin 7                   */
#define HAL_GPIO_AF3_XSPI1_NCS1            HAL_GPIO_AF_3  /*!< XSPI1 Chip Select 1                */
#define HAL_GPIO_AF3_XSPI1_NCS2            HAL_GPIO_AF_3  /*!< XSPI1 Chip Select 2                */

/**
  * @brief   AF 4 selection
  */
#define HAL_GPIO_AF4_I2C1                  HAL_GPIO_AF_4  /*!< I2C1 Alternate Function mapping    */
#define HAL_GPIO_AF4_I2C1_SCL              HAL_GPIO_AF_4  /*!< I2C1 Clock                         */
#define HAL_GPIO_AF4_I2C1_SDA              HAL_GPIO_AF_4  /*!< I2C1 Data                          */
#define HAL_GPIO_AF4_I2C2                  HAL_GPIO_AF_4  /*!< I2C2 Alternate Function mapping    */
#define HAL_GPIO_AF4_I2C2_SCL              HAL_GPIO_AF_4  /*!< I2C2 Clock                         */
#define HAL_GPIO_AF4_I2C2_SDA              HAL_GPIO_AF_4  /*!< I2C2 Data                          */
#define HAL_GPIO_AF4_I2C2_SMBA             HAL_GPIO_AF_4  /*!< I2C2 SMBus Alert                   */
#define HAL_GPIO_AF4_I2C3                  HAL_GPIO_AF_4  /*!< I2C3 Alternate Function mapping    */
#define HAL_GPIO_AF4_I2C3_SCL              HAL_GPIO_AF_4  /*!< I2C3 Clock                         */
#define HAL_GPIO_AF4_I2C3_SDA              HAL_GPIO_AF_4  /*!< I2C3 Data                          */
#define HAL_GPIO_AF4_I2C3_SMBA             HAL_GPIO_AF_4  /*!< I2C3 SMBus Alert                   */
#define HAL_GPIO_AF4_TIM5                  HAL_GPIO_AF_4  /*!< TIM5 Alternate Function mapping    */
#define HAL_GPIO_AF4_TIM5_CH1              HAL_GPIO_AF_4  /*!< TIM5 Multi-purpose Channel 1       */
#define HAL_GPIO_AF4_TIM5_CH2              HAL_GPIO_AF_4  /*!< TIM5 Multi-purpose Channel 2       */
#define HAL_GPIO_AF4_TIM5_CH3              HAL_GPIO_AF_4  /*!< TIM5 Multi-purpose Channel 3       */
#define HAL_GPIO_AF4_TIM5_CH4              HAL_GPIO_AF_4  /*!< TIM5 Multi-purpose Channel 4       */
#define HAL_GPIO_AF4_TIM8                  HAL_GPIO_AF_4  /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF4_TIM8_BKIN             HAL_GPIO_AF_4  /*!< TIM8 Break input                   */
#define HAL_GPIO_AF4_TIM8_BKIN2            HAL_GPIO_AF_4  /*!< TIM8 Break input 2                 */
#define HAL_GPIO_AF4_TIM8_CH1              HAL_GPIO_AF_4  /*!< TIM8 Multi-purpose Channel 1       */
#define HAL_GPIO_AF4_TIM8_CH1N             HAL_GPIO_AF_4  /*!< TIM8 CH1 complementary output      */
#define HAL_GPIO_AF4_TIM8_CH2N             HAL_GPIO_AF_4  /*!< TIM8 CH2 complementary output      */
#define HAL_GPIO_AF4_TIM8_CH3              HAL_GPIO_AF_4  /*!< TIM8 Multi-purpose Channel 3       */
#define HAL_GPIO_AF4_TIM8_CH3N             HAL_GPIO_AF_4  /*!< TIM8 CH3 complementary output      */
#define HAL_GPIO_AF4_TIM8_CH4              HAL_GPIO_AF_4  /*!< TIM8 Multi-purpose Channel 4       */
#define HAL_GPIO_AF4_TIM8_ETR              HAL_GPIO_AF_4  /*!< TIM8 External trigger input        */
#define HAL_GPIO_AF4_TIM11                 HAL_GPIO_AF_4  /*!< TIM11 Alternate Function mapping   */
#define HAL_GPIO_AF4_TIM11_CH1             HAL_GPIO_AF_4  /*!< TIM11 Multi-purpose Channel 1      */
#define HAL_GPIO_AF4_TIM14                 HAL_GPIO_AF_4  /*!< TIM14 Alternate Function mapping   */
#define HAL_GPIO_AF4_TIM14_CH1             HAL_GPIO_AF_4  /*!< TIM14 Multi-purpose Channel 1      */
#define HAL_GPIO_AF4_USART1                HAL_GPIO_AF_4  /*!< USART1 Alternate Function mapping  */
#define HAL_GPIO_AF4_USART1_CK             HAL_GPIO_AF_4  /*!< USART1 Clock                       */
#define HAL_GPIO_AF4_USART1_CTS            HAL_GPIO_AF_4  /*!< USART1 Clear To Send input         */
#define HAL_GPIO_AF4_USART1_NSS            HAL_GPIO_AF_4  /*!< USART1 Slave Select                */
#define HAL_GPIO_AF4_USART1_RX             HAL_GPIO_AF_4  /*!< USART1 Serial Data Receive Input   */
#define HAL_GPIO_AF4_USART1_TX             HAL_GPIO_AF_4  /*!< USART1 Transmit Data Output        */

/**
  * @brief   AF 5 selection
  */
#define HAL_GPIO_AF5_I2S1                  HAL_GPIO_AF_5  /*!< I2S1 Alternate Function mapping      */
#define HAL_GPIO_AF5_I2S1_CK               HAL_GPIO_AF_5  /*!< I2S1 Clock                           */
#define HAL_GPIO_AF5_I2S1_MCK              HAL_GPIO_AF_5  /*!< I2S1 Master Clock                    */
#define HAL_GPIO_AF5_I2S1_SDI              HAL_GPIO_AF_5  /*!< I2S1 Serial Data Input               */
#define HAL_GPIO_AF5_I2S1_SDO              HAL_GPIO_AF_5  /*!< I2S1 Serial Data Output              */
#define HAL_GPIO_AF5_I2S1_WS               HAL_GPIO_AF_5  /*!< I2S1 Word Select                     */
#define HAL_GPIO_AF5_I2S2                  HAL_GPIO_AF_5  /*!< I2S2 Alternate Function mapping      */
#define HAL_GPIO_AF5_I2S2_CK               HAL_GPIO_AF_5  /*!< I2S2 Clock                           */
#define HAL_GPIO_AF5_I2S2_SDI              HAL_GPIO_AF_5  /*!< I2S2 Serial Data Input               */
#define HAL_GPIO_AF5_I2S2_SDO              HAL_GPIO_AF_5  /*!< I2S2 Serial Data Output              */
#define HAL_GPIO_AF5_I2S2_WS               HAL_GPIO_AF_5  /*!< I2S2 Word Select                     */
#define HAL_GPIO_AF5_LPTIM1                HAL_GPIO_AF_5  /*!< LPTIM1 Alternate Function mapping    */
#define HAL_GPIO_AF5_LPTIM1_CH1            HAL_GPIO_AF_5  /*!< LPTIM1 Multi-purpose Channel 1       */
#define HAL_GPIO_AF5_LPTIM1_CH2            HAL_GPIO_AF_5  /*!< LPTIM1 Multi-purpose Channel 2       */
#define HAL_GPIO_AF5_LPTIM1_ETR            HAL_GPIO_AF_5  /*!< LPTIM1 External Trigger              */
#define HAL_GPIO_AF5_LPTIM1_IN1            HAL_GPIO_AF_5  /*!< LPTIM1 Channel 1 Input               */
#define HAL_GPIO_AF5_LPTIM1_IN2            HAL_GPIO_AF_5  /*!< LPTIM1 Channel 2 Input               */
#define HAL_GPIO_AF5_SPI1                  HAL_GPIO_AF_5  /*!< SPI1 Alternate Function mapping      */
#define HAL_GPIO_AF5_SPI1_MISO             HAL_GPIO_AF_5  /*!< SPI1 Master-In/Slave-Out             */
#define HAL_GPIO_AF5_SPI1_MOSI             HAL_GPIO_AF_5  /*!< SPI1 Master-Out/Slave-In             */
#define HAL_GPIO_AF5_SPI1_NSS              HAL_GPIO_AF_5  /*!< SPI1 Chip Select                     */
#define HAL_GPIO_AF5_SPI1_RDY              HAL_GPIO_AF_5  /*!< SPI1 Ready                           */
#define HAL_GPIO_AF5_SPI1_SCK              HAL_GPIO_AF_5  /*!< SPI1 Serial Clock                    */
#define HAL_GPIO_AF5_SPI2                  HAL_GPIO_AF_5  /*!< SPI2 Alternate Function mapping      */
#define HAL_GPIO_AF5_SPI2_MISO             HAL_GPIO_AF_5  /*!< SPI2 Master-In/Slave-Out             */
#define HAL_GPIO_AF5_SPI2_MOSI             HAL_GPIO_AF_5  /*!< SPI2 Master-Out/Slave-In             */
#define HAL_GPIO_AF5_SPI2_NSS              HAL_GPIO_AF_5  /*!< SPI2 Chip Select                     */
#define HAL_GPIO_AF5_SPI2_RDY              HAL_GPIO_AF_5  /*!< SPI2 Ready                           */
#define HAL_GPIO_AF5_SPI2_SCK              HAL_GPIO_AF_5  /*!< SPI2 Serial Clock                    */
#define HAL_GPIO_AF5_TIM8                  HAL_GPIO_AF_5  /*!< TIM8 Alternate Function mapping      */
#define HAL_GPIO_AF5_TIM8_BKIN             HAL_GPIO_AF_5  /*!< TIM8 Break input                     */
#define HAL_GPIO_AF5_TIM8_CH1N             HAL_GPIO_AF_5  /*!< TIM8 CH1 complementary output        */
#define HAL_GPIO_AF5_TIM8_CH2              HAL_GPIO_AF_5  /*!< TIM8 Multi-purpose Channel 2         */
#define HAL_GPIO_AF5_TIM8_CH2N             HAL_GPIO_AF_5  /*!< TIM8 CH2 complementary output        */
#define HAL_GPIO_AF5_TIM16                 HAL_GPIO_AF_5  /*!< TIM16 Alternate Function mapping     */
#define HAL_GPIO_AF5_TIM16_BKIN            HAL_GPIO_AF_5  /*!< TIM16 Break input                    */
#define HAL_GPIO_AF5_TIM16_CH1N            HAL_GPIO_AF_5  /*!< TIM16 Channel 1 Complementary Output */

/**
  * @brief   AF 6 selection
  */

#define HAL_GPIO_AF6_FDCAN3                HAL_GPIO_AF_6  /*!< FDCAN3 Alternate Function mapping    */
#define HAL_GPIO_AF6_FDCAN3_RX             HAL_GPIO_AF_6  /*!< FDCAN3 Receive pin                   */
#define HAL_GPIO_AF6_FDCAN3_TX             HAL_GPIO_AF_6  /*!< FDCAN3 Transmit pin                  */
#define HAL_GPIO_AF6_I2C4                  HAL_GPIO_AF_6  /*!< I2C4 Alternate Function mapping      */
#define HAL_GPIO_AF6_I2C4_SCL              HAL_GPIO_AF_6  /*!< I2C4 Clock                           */
#define HAL_GPIO_AF6_I2C4_SDA              HAL_GPIO_AF_6  /*!< I2C4 Data                            */
#define HAL_GPIO_AF6_I2C4_SMBA             HAL_GPIO_AF_6  /*!< I2C4 SMBus Alert                     */
#define HAL_GPIO_AF6_POSENC1               HAL_GPIO_AF_6  /*!< POSENC1 Alternate Function mapping   */
#define HAL_GPIO_AF6_POSENC1_EN            HAL_GPIO_AF_6  /*!< POSENC1 Enable                       */
#define HAL_GPIO_AF6_POSENC1_IN            HAL_GPIO_AF_6  /*!< POSENC1 Input                        */
#define HAL_GPIO_AF6_POSENC1_MISO          HAL_GPIO_AF_6  /*!< POSENC1 Master-In/Slave-Out          */
#define HAL_GPIO_AF6_POSENC1_MOSI          HAL_GPIO_AF_6  /*!< POSENC1 Master-Out/Slave-In          */
#define HAL_GPIO_AF6_POSENC1_OUT           HAL_GPIO_AF_6  /*!< POSENC1 Output                       */
#define HAL_GPIO_AF6_POSENC1_SCK           HAL_GPIO_AF_6  /*!< POSENC1 Serial Clock                 */
#define HAL_GPIO_AF6_POSENC1_SEL           HAL_GPIO_AF_6  /*!< POSENC1 Select                       */
#define HAL_GPIO_AF6_POSENC2               HAL_GPIO_AF_6  /*!< POSENC2 Alternate Function mapping   */
#define HAL_GPIO_AF6_POSENC2_EN            HAL_GPIO_AF_6  /*!< POSENC2 Enable                       */
#define HAL_GPIO_AF6_POSENC2_IN            HAL_GPIO_AF_6  /*!< POSENC2 Input                        */
#define HAL_GPIO_AF6_POSENC2_MISO          HAL_GPIO_AF_6  /*!< POSENC2 Master-In/Slave-Out          */
#define HAL_GPIO_AF6_POSENC2_MOSI          HAL_GPIO_AF_6  /*!< POSENC2 Master-Out/Slave-In          */
#define HAL_GPIO_AF6_POSENC2_OUT           HAL_GPIO_AF_6  /*!< POSENC2 Output                       */
#define HAL_GPIO_AF6_POSENC2_SCK           HAL_GPIO_AF_6  /*!< POSENC2 Serial Clock                 */
#define HAL_GPIO_AF6_POSENC2_SEL           HAL_GPIO_AF_6  /*!< POSENC2 Select                       */
#define HAL_GPIO_AF6_SPI3                  HAL_GPIO_AF_6  /*!< SPI3 Alternate Function mapping      */
#define HAL_GPIO_AF6_SPI3_MISO             HAL_GPIO_AF_6  /*!< SPI3 Master-In/Slave-Out             */
#define HAL_GPIO_AF6_SPI3_MOSI             HAL_GPIO_AF_6  /*!< SPI3 Master-Out/Slave-In             */
#define HAL_GPIO_AF6_SPI3_NSS              HAL_GPIO_AF_6  /*!< SPI3 Slave Selection                 */
#define HAL_GPIO_AF6_SPI3_RDY              HAL_GPIO_AF_6  /*!< SPI3 Ready                           */
#define HAL_GPIO_AF6_SPI3_SCK              HAL_GPIO_AF_6  /*!< SPI3 Serial Clock                    */
#define HAL_GPIO_AF6_TIM1                  HAL_GPIO_AF_6  /*!< TIM1 Alternate Function mapping      */
#define HAL_GPIO_AF6_TIM1_BKIN             HAL_GPIO_AF_6  /*!< TIM1 Break input                     */
#define HAL_GPIO_AF6_TIM1_BKIN2            HAL_GPIO_AF_6  /*!< TIM1 Break input 2                   */
#define HAL_GPIO_AF6_TIM1_CH1              HAL_GPIO_AF_6  /*!< TIM1 Multi-purpose Channel 1         */
#define HAL_GPIO_AF6_TIM1_CH1N             HAL_GPIO_AF_6  /*!< TIM1 CH1 complementary output        */
#define HAL_GPIO_AF6_TIM1_CH2N             HAL_GPIO_AF_6  /*!< TIM1 CH2 complementary output        */
#define HAL_GPIO_AF6_TIM1_CH3              HAL_GPIO_AF_6  /*!< TIM1 Multi-purpose Channel 3         */
#define HAL_GPIO_AF6_TIM1_CH3N             HAL_GPIO_AF_6  /*!< TIM1 CH3 complementary output        */
#define HAL_GPIO_AF6_TIM1_CH4N             HAL_GPIO_AF_6  /*!< TIM1 CH4 complementary output        */
#define HAL_GPIO_AF6_TIM8                  HAL_GPIO_AF_6  /*!< TIM8 Alternate Function mapping      */
#define HAL_GPIO_AF6_TIM8_BKIN2            HAL_GPIO_AF_6  /*!< TIM8 Break input 2                   */
#define HAL_GPIO_AF6_TIM8_CH2              HAL_GPIO_AF_6  /*!< TIM8 Multi-purpose Channel 2         */
#define HAL_GPIO_AF6_TIM8_CH4N             HAL_GPIO_AF_6  /*!< TIM8 CH4 complementary output        */
#define HAL_GPIO_AF6_TIM8_ETR              HAL_GPIO_AF_6  /*!< TIM8 External trigger input          */
#define HAL_GPIO_AF6_TIM20                 HAL_GPIO_AF_6  /*!< TIM20 Alternate Function mapping     */
#define HAL_GPIO_AF6_TIM20_CH1             HAL_GPIO_AF_6  /*!< TIM20 Multi-purpose Channel 1        */
#define HAL_GPIO_AF6_TIM20_CH3             HAL_GPIO_AF_6  /*!< TIM20 Multi-purpose Channel 3        */
#define HAL_GPIO_AF6_TIM20_CH3N            HAL_GPIO_AF_6  /*!< TIM20 CH3 complementary output       */
#define HAL_GPIO_AF6_TIM20_CH4N            HAL_GPIO_AF_6  /*!< TIM20 CH4 complementary output       */

/**
  * @brief   AF 7 selection
  */
#define HAL_GPIO_AF7_I2S2                  HAL_GPIO_AF_7  /*!< I2S2 Alternate Function mapping      */
#define HAL_GPIO_AF7_I2S2_CK               HAL_GPIO_AF_7  /*!< I2S2 Clock                           */
#define HAL_GPIO_AF7_I2S2_MCK              HAL_GPIO_AF_7  /*!< I2S2 Master Clock                    */
#define HAL_GPIO_AF7_I2S2_WS               HAL_GPIO_AF_7  /*!< I2S2 Word Select                     */
#define HAL_GPIO_AF7_SPI2                  HAL_GPIO_AF_7  /*!< SPI2 Alternate Function mapping      */
#define HAL_GPIO_AF7_SPI2_NSS              HAL_GPIO_AF_7  /*!< SPI2 Chip Select                     */
#define HAL_GPIO_AF7_SPI2_RDY              HAL_GPIO_AF_7  /*!< SPI2 Ready                           */
#define HAL_GPIO_AF7_SPI2_SCK              HAL_GPIO_AF_7  /*!< SPI2 Serial Clock                    */
#define HAL_GPIO_AF7_SPI3                  HAL_GPIO_AF_7  /*!< SPI3 Alternate Function mapping      */
#define HAL_GPIO_AF7_SPI3_MOSI             HAL_GPIO_AF_7  /*!< SPI3 Master-Out/Slave-In             */
#define HAL_GPIO_AF7_SPI3_NSS              HAL_GPIO_AF_7  /*!< SPI3 Slave Selection                 */
#define HAL_GPIO_AF7_SPI3_SCK              HAL_GPIO_AF_7  /*!< SPI3 Serial Clock                    */
#define HAL_GPIO_AF7_TIM17                 HAL_GPIO_AF_7  /*!< TIM17 Alternate Function mapping     */
#define HAL_GPIO_AF7_TIM17_BKIN            HAL_GPIO_AF_7  /*!< TIM17 Break input                    */
#define HAL_GPIO_AF7_TIM17_CH1             HAL_GPIO_AF_7  /*!< TIM17 Multi-purpose Channel 1        */
#define HAL_GPIO_AF7_TIM17_CH1N            HAL_GPIO_AF_7  /*!< TIM17 CH1 complementary output       */
#define HAL_GPIO_AF7_UART6                 HAL_GPIO_AF_7  /*!< UART6 Alternate Function mapping     */
#define HAL_GPIO_AF7_UART6_CTS             HAL_GPIO_AF_7  /*!< UART6 Clear to send                  */
#define HAL_GPIO_AF7_UART6_RTS             HAL_GPIO_AF_7  /*!< UART6 Request to send                */
#define HAL_GPIO_AF7_UART6_RX              HAL_GPIO_AF_7  /*!< UART6 Serial Data Receive Input      */
#define HAL_GPIO_AF7_UART6_TX              HAL_GPIO_AF_7  /*!< UART6 Transmit Data Output           */
#define HAL_GPIO_AF7_USART1                HAL_GPIO_AF_7  /*!< USART1 Alternate Function mapping    */
#define HAL_GPIO_AF7_USART1_CK             HAL_GPIO_AF_7  /*!< USART1  Clock                        */
#define HAL_GPIO_AF7_USART1_CTS            HAL_GPIO_AF_7  /*!< USART1 Clear to send                 */
#define HAL_GPIO_AF7_USART1_NSS            HAL_GPIO_AF_7  /*!< USART1 Slave Selection               */
#define HAL_GPIO_AF7_USART1_RTS            HAL_GPIO_AF_7  /*!< USART1 Request to send               */
#define HAL_GPIO_AF7_USART1_RX             HAL_GPIO_AF_7  /*!< USART1 Serial Data Receive Input     */
#define HAL_GPIO_AF7_USART1_TX             HAL_GPIO_AF_7  /*!< USART1 Transmit Data Output          */
#define HAL_GPIO_AF7_USART2                HAL_GPIO_AF_7  /*!< USART2 Alternate Function mapping    */
#define HAL_GPIO_AF7_USART2_CK             HAL_GPIO_AF_7  /*!< USART2  Clock                        */
#define HAL_GPIO_AF7_USART2_CTS            HAL_GPIO_AF_7  /*!< USART2 Clear to send                 */
#define HAL_GPIO_AF7_USART2_NSS            HAL_GPIO_AF_7  /*!< USART2 Slave Selection               */
#define HAL_GPIO_AF7_USART2_RTS            HAL_GPIO_AF_7  /*!< USART2 Request to send               */
#define HAL_GPIO_AF7_USART2_RX             HAL_GPIO_AF_7  /*!< USART2 Serial Data Receive Input     */
#define HAL_GPIO_AF7_USART2_TX             HAL_GPIO_AF_7  /*!< USART2 Transmit Data Output          */
#define HAL_GPIO_AF7_USART3                HAL_GPIO_AF_7  /*!< USART3 Alternate Function mapping    */
#define HAL_GPIO_AF7_USART3_CK             HAL_GPIO_AF_7  /*!< USART3  Clock                        */
#define HAL_GPIO_AF7_USART3_CTS            HAL_GPIO_AF_7  /*!< USART3 Clear to send                 */
#define HAL_GPIO_AF7_USART3_NSS            HAL_GPIO_AF_7  /*!< USART3 Slave Selection               */
#define HAL_GPIO_AF7_USART3_RTS            HAL_GPIO_AF_7  /*!< USART3 Request to send               */
#define HAL_GPIO_AF7_USART3_RX             HAL_GPIO_AF_7  /*!< USART3 Serial Data Receive Input     */
#define HAL_GPIO_AF7_USART3_TX             HAL_GPIO_AF_7  /*!< USART3 Transmit Data Output          */

/**
  * @brief   AF 8 selection
  */
#define HAL_GPIO_AF8_FDCAN3                HAL_GPIO_AF_8  /*!< FDCAN3 Alternate Function mapping    */
#define HAL_GPIO_AF8_FDCAN3_TX             HAL_GPIO_AF_8  /*!< FDCAN3 Transmit pin                  */
#define HAL_GPIO_AF8_I2C3                  HAL_GPIO_AF_8  /*!< I2C3 Alternate Function mapping      */
#define HAL_GPIO_AF8_I2C3_SCL              HAL_GPIO_AF_8  /*!< I2C3 Clock                           */
#define HAL_GPIO_AF8_I2C3_SDA              HAL_GPIO_AF_8  /*!< I2C3 Data                            */
#define HAL_GPIO_AF8_I2C3_SMBA             HAL_GPIO_AF_8  /*!< I2C3 SMBus Alert                     */
#define HAL_GPIO_AF8_LPUART1               HAL_GPIO_AF_8  /*!< LPUART1 Alternate Function mapping   */
#define HAL_GPIO_AF8_LPUART1_CTS           HAL_GPIO_AF_8  /*!< LPUART1 Clear to send                */
#define HAL_GPIO_AF8_LPUART1_RTS           HAL_GPIO_AF_8  /*!< LPUART1 Request to send              */
#define HAL_GPIO_AF8_LPUART1_RX            HAL_GPIO_AF_8  /*!< LPUART1 Serial Data Receive Input    */
#define HAL_GPIO_AF8_LPUART1_TX            HAL_GPIO_AF_8  /*!< LPUART1 Transmit Data Output         */
#define HAL_GPIO_AF8_TIM3                  HAL_GPIO_AF_8  /*!< TIM3 Alternate Function mapping      */
#define HAL_GPIO_AF8_TIM3_CH3              HAL_GPIO_AF_8  /*!< TIM3_CH3                             */
#define HAL_GPIO_AF8_TIM20                 HAL_GPIO_AF_8  /*!< TIM20 Alternate Function mapping     */
#define HAL_GPIO_AF8_TIM20_BKIN            HAL_GPIO_AF_8  /*!< TIM20 Break input                    */
#define HAL_GPIO_AF8_TIM20_BKIN2           HAL_GPIO_AF_8  /*!< TIM20 Break input 2                  */
#define HAL_GPIO_AF8_TIM20_CH1             HAL_GPIO_AF_8  /*!< TIM20 Multi-purpose Channel 1        */
#define HAL_GPIO_AF8_TIM20_CH1N            HAL_GPIO_AF_8  /*!< TIM20 CH1 complementary output       */
#define HAL_GPIO_AF8_TIM20_CH2             HAL_GPIO_AF_8  /*!< TIM20 Multi-purpose Channel 2        */
#define HAL_GPIO_AF8_TIM20_CH2N            HAL_GPIO_AF_8  /*!< TIM20 CH2 complementary output       */
#define HAL_GPIO_AF8_TIM20_CH3             HAL_GPIO_AF_8  /*!< TIM20 Multi-purpose Channel 3        */
#define HAL_GPIO_AF8_TIM20_CH4             HAL_GPIO_AF_8  /*!< TIM20 Multi-purpose Channel 4        */
#define HAL_GPIO_AF8_TIM20_CH4N            HAL_GPIO_AF_8  /*!< TIM20_CH4N                           */
#define HAL_GPIO_AF8_TIM20_ETR             HAL_GPIO_AF_8  /*!< TIM20 External trigger input         */
#define HAL_GPIO_AF8_UART4                 HAL_GPIO_AF_8  /*!< UART4 Alternate Function mapping     */
#define HAL_GPIO_AF8_UART4_CTS             HAL_GPIO_AF_8  /*!< UART4 Clear to send                  */
#define HAL_GPIO_AF8_UART4_RTS             HAL_GPIO_AF_8  /*!< UART4 Request to send                */
#define HAL_GPIO_AF8_UART4_RX              HAL_GPIO_AF_8  /*!< UART4 Serial Data Receive Input      */
#define HAL_GPIO_AF8_UART4_TX              HAL_GPIO_AF_8  /*!< UART4 Transmit Data Output           */
#define HAL_GPIO_AF8_UART6                 HAL_GPIO_AF_8  /*!< UART6 Alternate Function mapping     */
#define HAL_GPIO_AF8_UART6_RX              HAL_GPIO_AF_8  /*!< UART6 Serial Data Receive Input      */
#define HAL_GPIO_AF8_UART6_TX              HAL_GPIO_AF_8  /*!< UART6 Transmit Data Output           */
#define HAL_GPIO_AF8_XSPI1                 HAL_GPIO_AF_8  /*!< XSPI1 Alternate Function mapping     */
#define HAL_GPIO_AF8_XSPI1_DQS0            HAL_GPIO_AF_8  /*!< XSPI1 Memory Data Strobe I/O         */
#define HAL_GPIO_AF8_XSPI1_IO1             HAL_GPIO_AF_8  /*!< XSPI1 Data pin 1                     */
#define HAL_GPIO_AF8_XSPI1_IO2             HAL_GPIO_AF_8  /*!< XSPI1 Data pin 2                     */
#define HAL_GPIO_AF8_XSPI1_IO3             HAL_GPIO_AF_8  /*!< XSPI1 Data pin 3                     */
#define HAL_GPIO_AF8_XSPI1_IO4             HAL_GPIO_AF_8  /*!< XSPI1 Data pin 4                     */
#define HAL_GPIO_AF8_XSPI1_IO5             HAL_GPIO_AF_8  /*!< XSPI1 Data pin 5                     */
#define HAL_GPIO_AF8_XSPI1_IO6             HAL_GPIO_AF_8  /*!< XSPI1 Data pin 6                     */
#define HAL_GPIO_AF8_XSPI1_IO7             HAL_GPIO_AF_8  /*!< XSPI1 Data pin 7                     */
#define HAL_GPIO_AF8_XSPI1_NCS1            HAL_GPIO_AF_8  /*!< XSPI1 Chip Select 1                  */
#define HAL_GPIO_AF8_XSPI1_NCS2            HAL_GPIO_AF_8  /*!< XSPI1 Chip Select 2                  */

/**
  * @brief   AF 9 selection
  */
#define HAL_GPIO_AF9_FDCAN1                HAL_GPIO_AF_9  /*!< FDCAN1 Alternate Function mapping    */
#define HAL_GPIO_AF9_FDCAN1_RX             HAL_GPIO_AF_9  /*!< FDCAN1 Receive pin                   */
#define HAL_GPIO_AF9_FDCAN1_TX             HAL_GPIO_AF_9  /*!< FDCAN1 Transmit pin                  */
#define HAL_GPIO_AF9_I2C1                  HAL_GPIO_AF_9  /*!< I2C1 Alternate Function mapping      */
#define HAL_GPIO_AF9_I2C1_SCL              HAL_GPIO_AF_9  /*!< I2C1 Clock                           */
#define HAL_GPIO_AF9_I2C1_SDA              HAL_GPIO_AF_9  /*!< I2C1 Data                            */
#define HAL_GPIO_AF9_I2C1_SMBA             HAL_GPIO_AF_9  /*!< I2C1 SMBus Alert                     */
#define HAL_GPIO_AF9_LPTIM1                HAL_GPIO_AF_9  /*!< LPTIM1 Alternate Function mapping    */
#define HAL_GPIO_AF9_LPTIM1_CH1            HAL_GPIO_AF_9  /*!< LPTIM1 Multi-purpose Channel 1       */
#define HAL_GPIO_AF9_LPTIM1_CH2            HAL_GPIO_AF_9  /*!< LPTIM1 Multi-purpose Channel 2       */
#define HAL_GPIO_AF9_LPTIM1_ETR            HAL_GPIO_AF_9  /*!< LPTIM1 External trigger input        */
#define HAL_GPIO_AF9_LPTIM1_IN1            HAL_GPIO_AF_9  /*!< LPTIM1 Channel 1 Input               */
#define HAL_GPIO_AF9_LPTIM1_IN2            HAL_GPIO_AF_9  /*!< LPTIM1 Channel 2 Input               */
#define HAL_GPIO_AF9_POSENC1               HAL_GPIO_AF_9  /*!< POSENC1 Alternate Function mapping   */
#define HAL_GPIO_AF9_POSENC1_EN            HAL_GPIO_AF_9  /*!< POSENC1 Enable                       */
#define HAL_GPIO_AF9_POSENC1_IN            HAL_GPIO_AF_9  /*!< POSENC1 Input                        */
#define HAL_GPIO_AF9_POSENC1_MOSI          HAL_GPIO_AF_9  /*!< POSENC1 Master-Out/Slave-In          */
#define HAL_GPIO_AF9_POSENC1_OUT           HAL_GPIO_AF_9  /*!< POSENC1 Output                       */
#define HAL_GPIO_AF9_POSENC1_SCK           HAL_GPIO_AF_9  /*!< POSENC1 Serial Clock                 */
#define HAL_GPIO_AF9_POSENC1_SEL           HAL_GPIO_AF_9  /*!< POSENC1 Select                       */
#define HAL_GPIO_AF9_POSENC2               HAL_GPIO_AF_9  /*!< POSENC2 Alternate Function mapping   */
#define HAL_GPIO_AF9_POSENC2_EN            HAL_GPIO_AF_9  /*!< POSENC2 Enable                       */
#define HAL_GPIO_AF9_POSENC2_IN            HAL_GPIO_AF_9  /*!< POSENC2 Input                        */
#define HAL_GPIO_AF9_POSENC2_MISO          HAL_GPIO_AF_9  /*!< POSENC2 Master-In/Slave-Out          */
#define HAL_GPIO_AF9_POSENC2_MOSI          HAL_GPIO_AF_9  /*!< POSENC2 Master-Out/Slave-In          */
#define HAL_GPIO_AF9_POSENC2_OUT           HAL_GPIO_AF_9  /*!< POSENC2 Output                       */
#define HAL_GPIO_AF9_POSENC2_SCK           HAL_GPIO_AF_9  /*!< POSENC2 Serial Clock                 */
#define HAL_GPIO_AF9_POSENC2_SEL           HAL_GPIO_AF_9  /*!< POSENC2 Select                       */
#define HAL_GPIO_AF9_SPI3                  HAL_GPIO_AF_9  /*!< SPI3 Alternate Function mapping      */
#define HAL_GPIO_AF9_SPI3_MISO             HAL_GPIO_AF_9  /*!< SPI3 Master-In/Slave-Out             */
#define HAL_GPIO_AF9_SPI3_RDY              HAL_GPIO_AF_9  /*!< SPI3 Ready                           */
#define HAL_GPIO_AF9_SPI3_SCK              HAL_GPIO_AF_9  /*!< SPI3 Serial Clock                    */
#define HAL_GPIO_AF9_TIM1                  HAL_GPIO_AF_9  /*!< TIM1 Alternate Function mapping      */
#define HAL_GPIO_AF9_TIM1_BKIN             HAL_GPIO_AF_9  /*!< TIM1 Break input                     */
#define HAL_GPIO_AF9_TIM1_BKIN2            HAL_GPIO_AF_9  /*!< TIM1 Break input 2                   */
#define HAL_GPIO_AF9_TIM1_CH1              HAL_GPIO_AF_9  /*!< TIM1 Multi-purpose Channel 1         */
#define HAL_GPIO_AF9_TIM1_CH3N             HAL_GPIO_AF_9  /*!< TIM1 CH3 complementary output        */
#define HAL_GPIO_AF9_TIM15                 HAL_GPIO_AF_9  /*!< TIM15 Alternate Function mapping     */
#define HAL_GPIO_AF9_TIM15_BKIN            HAL_GPIO_AF_9  /*!< TIM15 Break input                    */
#define HAL_GPIO_AF9_TIM15_CH1             HAL_GPIO_AF_9  /*!< TIM15 Multi-purpose Channel 1        */
#define HAL_GPIO_AF9_TIM15_CH1N            HAL_GPIO_AF_9  /*!< TIM15 CH1 complementary output       */
#define HAL_GPIO_AF9_TIM15_CH2             HAL_GPIO_AF_9  /*!< TIM15 Multi-purpose Channel 2        */
#define HAL_GPIO_AF9_TIM20                 HAL_GPIO_AF_9  /*!< TIM20 Alternate Function mapping     */
#define HAL_GPIO_AF9_TIM20_BKIN            HAL_GPIO_AF_9  /*!< TIM20 Break input                    */
#define HAL_GPIO_AF9_TIM20_CH1             HAL_GPIO_AF_9  /*!< TIM20 Multi-purpose Channel 1        */
#define HAL_GPIO_AF9_TIM20_CH1N            HAL_GPIO_AF_9  /*!< TIM20 CH1 complementary output       */
#define HAL_GPIO_AF9_TIM20_CH2             HAL_GPIO_AF_9  /*!< TIM20 Multi-purpose Channel 2        */
#define HAL_GPIO_AF9_TIM20_CH2N            HAL_GPIO_AF_9  /*!< TIM20 CH2 complementary output       */
#define HAL_GPIO_AF9_TIM20_CH3             HAL_GPIO_AF_9  /*!< TIM20 Multi-purpose Channel 3        */
#define HAL_GPIO_AF9_TIM20_CH3N            HAL_GPIO_AF_9  /*!< TIM20 CH3 complementary output       */
#define HAL_GPIO_AF9_TIM20_CH4             HAL_GPIO_AF_9  /*!< TIM20 Multi-purpose Channel 4        */
#define HAL_GPIO_AF9_TIM20_ETR             HAL_GPIO_AF_9  /*!< TIM20 External trigger input         */
#define HAL_GPIO_AF9_UART5                 HAL_GPIO_AF_9  /*!< UART5 Alternate Function mapping     */
#define HAL_GPIO_AF9_UART5_CTS             HAL_GPIO_AF_9  /*!< UART5 Clear to send                  */
#define HAL_GPIO_AF9_UART5_RTS             HAL_GPIO_AF_9  /*!< UART5 Request to send                */
#define HAL_GPIO_AF9_UART5_RX              HAL_GPIO_AF_9  /*!< UART5 Serial Data Receive Input      */
#define HAL_GPIO_AF9_UART5_TX              HAL_GPIO_AF_9  /*!< UART5 Transmit Data Output           */

/**
  * @brief   AF 10 selection
  */
#define HAL_GPIO_AF10_I2C4                 HAL_GPIO_AF_10 /*!< I2C4 Alternate Function mapping  */
#define HAL_GPIO_AF10_I2C4_SCL             HAL_GPIO_AF_10 /*!< I2C4 Clock                       */
#define HAL_GPIO_AF10_I2C4_SDA             HAL_GPIO_AF_10 /*!< I2C4 Data                        */
#define HAL_GPIO_AF10_I2C4_SMBA            HAL_GPIO_AF_10 /*!< I2C4 SMBus Alert                 */
#define HAL_GPIO_AF10_TIM2                 HAL_GPIO_AF_10 /*!< TIM2 Alternate Function mapping  */
#define HAL_GPIO_AF10_TIM2_CH1             HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 1     */
#define HAL_GPIO_AF10_TIM2_CH3             HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 3     */
#define HAL_GPIO_AF10_TIM2_CH4             HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 4     */
#define HAL_GPIO_AF10_TIM2_ETR             HAL_GPIO_AF_10 /*!< TIM2 External trigger input      */
#define HAL_GPIO_AF10_TIM4                 HAL_GPIO_AF_10 /*!< TIM4 Alternate Function mapping  */
#define HAL_GPIO_AF10_TIM4_CH1             HAL_GPIO_AF_10 /*!< TIM4 Multi-purpose Channel 1     */
#define HAL_GPIO_AF10_TIM4_CH2             HAL_GPIO_AF_10 /*!< TIM4 Multi-purpose Channel 2     */
#define HAL_GPIO_AF10_TIM4_ETR             HAL_GPIO_AF_10 /*!< TIM4 External trigger input      */
#define HAL_GPIO_AF10_TIM8                 HAL_GPIO_AF_10 /*!< TIM8 Alternate Function mapping  */
#define HAL_GPIO_AF10_TIM8_BKIN            HAL_GPIO_AF_10 /*!< TIM8 Break input                 */
#define HAL_GPIO_AF10_TIM8_BKIN2           HAL_GPIO_AF_10 /*!< TIM8 Break input 2               */
#define HAL_GPIO_AF10_TIM8_CH1             HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 1     */
#define HAL_GPIO_AF10_TIM8_CH2             HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 2     */
#define HAL_GPIO_AF10_TIM8_CH3             HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 3     */
#define HAL_GPIO_AF10_TIM8_CH3N            HAL_GPIO_AF_10 /*!< TIM8 CH3 complementary output    */
#define HAL_GPIO_AF10_TIM8_CH4             HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 4     */
#define HAL_GPIO_AF10_TIM8_CH4N            HAL_GPIO_AF_10 /*!< TIM8 CH4 complementary output    */
#define HAL_GPIO_AF10_TIM8_ETR             HAL_GPIO_AF_10 /*!< TIM8 External trigger input      */
#define HAL_GPIO_AF10_XSPI1                HAL_GPIO_AF_10 /*!< XSPI1 Alternate Function mapping */
#define HAL_GPIO_AF10_XSPI1_CLK            HAL_GPIO_AF_10 /*!< XSPI1 Clock                      */
#define HAL_GPIO_AF10_XSPI1_DQS0           HAL_GPIO_AF_10 /*!< XSPI1 Memory Data Strobe I/O     */
#define HAL_GPIO_AF10_XSPI1_IO0            HAL_GPIO_AF_10 /*!< XSPI1 Data pin 0                 */
#define HAL_GPIO_AF10_XSPI1_IO4            HAL_GPIO_AF_10 /*!< XSPI1 Data pin 4                 */
#define HAL_GPIO_AF10_XSPI1_IO5            HAL_GPIO_AF_10 /*!< XSPI1 Data pin 5                 */
#define HAL_GPIO_AF10_XSPI1_IO6            HAL_GPIO_AF_10 /*!< XSPI1 Data pin 6                 */
#define HAL_GPIO_AF10_XSPI1_IO7            HAL_GPIO_AF_10 /*!< XSPI1 Data pin 7                 */
#define HAL_GPIO_AF10_XSPI1_NCS1           HAL_GPIO_AF_10 /*!< XSPI1 Chip Select 1              */
#define HAL_GPIO_AF10_XSPI1_NCS2           HAL_GPIO_AF_10 /*!< XSPI1 Chip Select 2              */

/**
  * @brief   AF 11 selection
  */
#if defined (HRTIM1)
#define HAL_GPIO_AF11_HRTIM1               HAL_GPIO_AF_11 /*!< HRTIM1 Alternate Function mapping */
#define HAL_GPIO_AF11_HRTIM1_CHA2          HAL_GPIO_AF_11 /*!< HRTIM1 Timer A Output 2           */
#define HAL_GPIO_AF11_HRTIM1_CHD1          HAL_GPIO_AF_11 /*!< HRTIM1 Timer D Output 1           */
#define HAL_GPIO_AF11_HRTIM1_CHD2          HAL_GPIO_AF_11 /*!< HRTIM1 Timer D Output 2           */
#define HAL_GPIO_AF11_HRTIM1_CHE1          HAL_GPIO_AF_11 /*!< HRTIM1 Timer E Output 1           */
#define HAL_GPIO_AF11_HRTIM1_CHE2          HAL_GPIO_AF_11 /*!< HRTIM1 Timer E Output 2           */
#define HAL_GPIO_AF11_HRTIM1_CHF1          HAL_GPIO_AF_11 /*!< HRTIM1 Timer F Output 1           */
#define HAL_GPIO_AF11_HRTIM1_CHF2          HAL_GPIO_AF_11 /*!< HRTIM1 Timer F Output 2           */
#define HAL_GPIO_AF11_HRTIM1_EEV1          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 1           */
#define HAL_GPIO_AF11_HRTIM1_EEV2          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 2           */
#define HAL_GPIO_AF11_HRTIM1_EEV3          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 3           */
#define HAL_GPIO_AF11_HRTIM1_EEV4          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 4           */
#define HAL_GPIO_AF11_HRTIM1_EEV6          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 6           */
#define HAL_GPIO_AF11_HRTIM1_EEV9          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 9           */
#define HAL_GPIO_AF11_HRTIM1_EEV10         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 10          */
#define HAL_GPIO_AF11_HRTIM1_EEV12         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 12          */
#define HAL_GPIO_AF11_HRTIM1_EEV13         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 13          */
#define HAL_GPIO_AF11_HRTIM1_EEV14         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 14          */
#define HAL_GPIO_AF11_HRTIM1_EEV15         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 15          */
#define HAL_GPIO_AF11_HRTIM1_EEV16         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 16          */
#define HAL_GPIO_AF11_HRTIM1_FLT2          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 2                    */
#define HAL_GPIO_AF11_HRTIM1_FLT3          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 3                    */
#define HAL_GPIO_AF11_HRTIM1_FLT4          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 4                    */
#define HAL_GPIO_AF11_HRTIM1_FLT5          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 5                    */
#define HAL_GPIO_AF11_HRTIM1_FLT6          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 6                    */
#define HAL_GPIO_AF11_HRTIM1_FLT7          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 7                    */
#define HAL_GPIO_AF11_HRTIM1_FLT8          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 8                    */
#define HAL_GPIO_AF11_HRTIM1_SCIN          HAL_GPIO_AF_11 /*!< HRTIM1 Synchronization Input      */
#endif /* HRTIM1 */
#define HAL_GPIO_AF11_TIM9                 HAL_GPIO_AF_11 /*!< TIM9 Alternate Function mapping   */
#define HAL_GPIO_AF11_TIM9_CH1             HAL_GPIO_AF_11 /*!< TIM9 Multi-purpose Channel 1      */
#define HAL_GPIO_AF11_TIM9_CH2             HAL_GPIO_AF_11 /*!< TIM9 Multi-purpose Channel 2      */

/**
  * @brief   AF 12 selection
  */
#if defined (HRTIM1)
#define HAL_GPIO_AF12_HRTIM1               HAL_GPIO_AF_12 /*!< HRTIM1 Alternate Function mapping */
#define HAL_GPIO_AF12_HRTIM1_CHA1          HAL_GPIO_AF_12 /*!< HRTIM1 Timer A Output 1           */
#define HAL_GPIO_AF12_HRTIM1_CHB2          HAL_GPIO_AF_12 /*!< HRTIM1 Timer B Output 2           */
#define HAL_GPIO_AF12_HRTIM1_EEV3          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 3           */
#define HAL_GPIO_AF12_HRTIM1_EEV4          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 4           */
#define HAL_GPIO_AF12_HRTIM1_EEV5          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 5           */
#define HAL_GPIO_AF12_HRTIM1_EEV6          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 6           */
#define HAL_GPIO_AF12_HRTIM1_EEV7          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 7           */
#define HAL_GPIO_AF12_HRTIM1_EEV9          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 9           */
#define HAL_GPIO_AF12_HRTIM1_FLT1          HAL_GPIO_AF_12 /*!< HRTIM1 Fault 1                    */
#define HAL_GPIO_AF12_HRTIM1_FLT4          HAL_GPIO_AF_12 /*!< HRTIM1 Fault 4                    */
#define HAL_GPIO_AF12_HRTIM1_FLT5          HAL_GPIO_AF_12 /*!< HRTIM1 Fault 5                    */
#define HAL_GPIO_AF12_HRTIM1_FLT6          HAL_GPIO_AF_12 /*!< HRTIM1 Fault 6                    */
#endif /* HRTIM1 */
#define HAL_GPIO_AF12_UCPD1                HAL_GPIO_AF_12 /*!< UCPD1 Alternate Function mapping  */
#define HAL_GPIO_AF12_UCPD1_FRSTX          HAL_GPIO_AF_12 /*!< UCPD1 Fast Role Swap transmit     */
#define HAL_GPIO_AF12_XSPI1                HAL_GPIO_AF_12 /*!< XSPI1 Alternate Function mapping  */
#define HAL_GPIO_AF12_XSPI1_DQS0           HAL_GPIO_AF_12 /*!< XSPI1 Memory Data Strobe I/O      */
#define HAL_GPIO_AF12_XSPI1_IO0            HAL_GPIO_AF_12 /*!< XSPI1 Data pin 0                  */
#define HAL_GPIO_AF12_XSPI1_IO2            HAL_GPIO_AF_12 /*!< XSPI1 Data pin 2                  */
#define HAL_GPIO_AF12_XSPI1_IO3            HAL_GPIO_AF_12 /*!< XSPI1 Data pin 3                  */

/**
  * @brief   AF 13 selection
  */
#define HAL_GPIO_AF13_COMP1                HAL_GPIO_AF_13 /*!< COMP1 Alternate Function mapping  */
#define HAL_GPIO_AF13_COMP1_OUT            HAL_GPIO_AF_13 /*!< COMP1 Output channel              */
#define HAL_GPIO_AF13_COMP4                HAL_GPIO_AF_13 /*!< COMP4 Alternate Function mapping  */
#define HAL_GPIO_AF13_COMP4_OUT            HAL_GPIO_AF_13 /*!< COMP4 Output channel              */
#define HAL_GPIO_AF13_COMP7                HAL_GPIO_AF_13 /*!< COMP7 Alternate Function mapping  */
#define HAL_GPIO_AF13_COMP7_OUT            HAL_GPIO_AF_13 /*!< COMP7 Output channel              */
#define HAL_GPIO_AF13_FDCAN1               HAL_GPIO_AF_13 /*!< FDCAN1 Alternate Function mapping */
#define HAL_GPIO_AF13_FDCAN1_RX            HAL_GPIO_AF_13 /*!< FDCAN1 Receive pin                */
#define HAL_GPIO_AF13_FDCAN1_TX            HAL_GPIO_AF_13 /*!< FDCAN1 Transmit pin               */
#define HAL_GPIO_AF13_FDCAN2               HAL_GPIO_AF_13 /*!< FDCAN2 Alternate Function mapping */
#define HAL_GPIO_AF13_FDCAN2_RX            HAL_GPIO_AF_13 /*!< FDCAN2 Receive pin                */
#define HAL_GPIO_AF13_FDCAN2_TX            HAL_GPIO_AF_13 /*!< FDCAN2 Transmit pin               */
#if defined (HRTIM1)
#define HAL_GPIO_AF13_HRTIM1               HAL_GPIO_AF_13 /*!< HRTIM1 Alternate Function mapping */
#define HAL_GPIO_AF13_HRTIM1_EEV5          HAL_GPIO_AF_13 /*!< HRTIM1 External Event 5           */
#define HAL_GPIO_AF13_HRTIM1_EEV11         HAL_GPIO_AF_13 /*!< HRTIM1 External Event 11          */
#define HAL_GPIO_AF13_HRTIM1_EEV12         HAL_GPIO_AF_13 /*!< HRTIM1 External Event 12          */
#define HAL_GPIO_AF13_HRTIM1_EEV15         HAL_GPIO_AF_13 /*!< HRTIM1 External Event 15          */
#define HAL_GPIO_AF13_HRTIM1_EEV16         HAL_GPIO_AF_13 /*!< HRTIM1 External Event 16          */
#define HAL_GPIO_AF13_HRTIM1_FLT3          HAL_GPIO_AF_13 /*!< HRTIM1 Fault 3                    */
#define HAL_GPIO_AF13_HRTIM1_SCOUT         HAL_GPIO_AF_13 /*!< HRTIM1 Synchronization Output     */
#endif /* HRTIM1 */

/**
  * @brief   AF 14 selection
  */
#define HAL_GPIO_AF14_COMP2                HAL_GPIO_AF_14 /*!< COMP2 Alternate Function mapping  */
#define HAL_GPIO_AF14_COMP2_OUT            HAL_GPIO_AF_14 /*!< COMP2 Output channel              */
#define HAL_GPIO_AF14_COMP3                HAL_GPIO_AF_14 /*!< COMP3 Alternate Function mapping  */
#define HAL_GPIO_AF14_COMP3_OUT            HAL_GPIO_AF_14 /*!< COMP3 Output channel              */
#define HAL_GPIO_AF14_COMP5                HAL_GPIO_AF_14 /*!< COMP5 Alternate Function mapping  */
#define HAL_GPIO_AF14_COMP5_OUT            HAL_GPIO_AF_14 /*!< COMP5 Output channel              */
#define HAL_GPIO_AF14_COMP6                HAL_GPIO_AF_14 /*!< COMP6 Alternate Function mapping  */
#define HAL_GPIO_AF14_COMP6_OUT            HAL_GPIO_AF_14 /*!< COMP6 Output channel              */
#define HAL_GPIO_AF14_COMP8                HAL_GPIO_AF_14 /*!< COMP8 Alternate Function mapping  */
#define HAL_GPIO_AF14_COMP8_OUT            HAL_GPIO_AF_14 /*!< COMP8 Output channel              */
#define HAL_GPIO_AF14_CRS                  HAL_GPIO_AF_14 /*!< CRS Alternate Function mapping    */
#define HAL_GPIO_AF14_CRS_SYNC             HAL_GPIO_AF_14 /*!< CRS synchronization               */
#define HAL_GPIO_AF14_PLAY1                HAL_GPIO_AF_14 /*!< PLAY1 Alternate Function mapping  */
#define HAL_GPIO_AF14_PLAY1_IN0            HAL_GPIO_AF_14 /*!< PLAY1 Input 0                     */
#define HAL_GPIO_AF14_PLAY1_IN1            HAL_GPIO_AF_14 /*!< PLAY1 Input 1                     */
#define HAL_GPIO_AF14_PLAY1_IN2            HAL_GPIO_AF_14 /*!< PLAY1 Input 2                     */
#define HAL_GPIO_AF14_PLAY1_IN3            HAL_GPIO_AF_14 /*!< PLAY1 Input 3                     */
#define HAL_GPIO_AF14_PLAY1_IN4            HAL_GPIO_AF_14 /*!< PLAY1 Input 4                     */
#define HAL_GPIO_AF14_PLAY1_IN5            HAL_GPIO_AF_14 /*!< PLAY1 Input 5                     */
#define HAL_GPIO_AF14_PLAY1_IN6            HAL_GPIO_AF_14 /*!< PLAY1 Input 6                     */
#define HAL_GPIO_AF14_PLAY1_IN7            HAL_GPIO_AF_14 /*!< PLAY1 Input 7                     */
#define HAL_GPIO_AF14_PLAY1_IN8            HAL_GPIO_AF_14 /*!< PLAY1 Input 8                     */
#define HAL_GPIO_AF14_PLAY1_IN9            HAL_GPIO_AF_14 /*!< PLAY1 Input 9                     */
#define HAL_GPIO_AF14_PLAY1_IN10           HAL_GPIO_AF_14 /*!< PLAY1 Input 10                    */
#define HAL_GPIO_AF14_PLAY1_IN11           HAL_GPIO_AF_14 /*!< PLAY1 Input 11                    */
#define HAL_GPIO_AF14_PLAY1_IN12           HAL_GPIO_AF_14 /*!< PLAY1 Input 12                    */
#define HAL_GPIO_AF14_PLAY1_IN13           HAL_GPIO_AF_14 /*!< PLAY1 Input 13                    */
#define HAL_GPIO_AF14_PLAY1_IN14           HAL_GPIO_AF_14 /*!< PLAY1 Input 14                    */
#define HAL_GPIO_AF14_PLAY1_IN15           HAL_GPIO_AF_14 /*!< PLAY1 Input 15                    */
#define HAL_GPIO_AF14_PLAY1_OUT0           HAL_GPIO_AF_14 /*!< PLAY1 Output 0                    */
#define HAL_GPIO_AF14_PLAY1_OUT1           HAL_GPIO_AF_14 /*!< PLAY1 Output 1                    */
#define HAL_GPIO_AF14_PLAY1_OUT2           HAL_GPIO_AF_14 /*!< PLAY1 Output 2                    */
#define HAL_GPIO_AF14_PLAY1_OUT3           HAL_GPIO_AF_14 /*!< PLAY1 Output 3                    */
#define HAL_GPIO_AF14_PLAY1_OUT4           HAL_GPIO_AF_14 /*!< PLAY1 Output 4                    */
#define HAL_GPIO_AF14_PLAY1_OUT5           HAL_GPIO_AF_14 /*!< PLAY1 Output 5                    */
#define HAL_GPIO_AF14_PLAY1_OUT6           HAL_GPIO_AF_14 /*!< PLAY1 Output 6                    */
#define HAL_GPIO_AF14_PLAY1_OUT7           HAL_GPIO_AF_14 /*!< PLAY1 Output 7                    */
#define HAL_GPIO_AF14_PLAY1_OUT8           HAL_GPIO_AF_14 /*!< PLAY1 Output 8                    */
#define HAL_GPIO_AF14_PLAY1_OUT9           HAL_GPIO_AF_14 /*!< PLAY1 Output 9                    */
#define HAL_GPIO_AF14_PLAY1_OUT10          HAL_GPIO_AF_14 /*!< PLAY1 Output 10                   */
#define HAL_GPIO_AF14_PLAY1_OUT11          HAL_GPIO_AF_14 /*!< PLAY1 Output 11                   */
#define HAL_GPIO_AF14_PLAY1_OUT12          HAL_GPIO_AF_14 /*!< PLAY1 Output 12                   */
#define HAL_GPIO_AF14_PLAY1_OUT13          HAL_GPIO_AF_14 /*!< PLAY1 Output 13                   */
#define HAL_GPIO_AF14_PLAY1_OUT14          HAL_GPIO_AF_14 /*!< PLAY1 Output 14                   */
#define HAL_GPIO_AF14_PLAY1_OUT15          HAL_GPIO_AF_14 /*!< PLAY1 Output 15                   */
#define HAL_GPIO_AF14_TIM8                 HAL_GPIO_AF_14 /*!< TIM8 Alternate Function mapping   */
#define HAL_GPIO_AF14_TIM8_BKIN            HAL_GPIO_AF_14 /*!< TIM8 Break input                  */
#define HAL_GPIO_AF14_TIM8_BKIN2           HAL_GPIO_AF_14 /*!< TIM8 Break input 2                */
#define HAL_GPIO_AF14_TIM8_CH1             HAL_GPIO_AF_14 /*!< TIM8 Multi-purpose Channel 1      */
#define HAL_GPIO_AF14_TIM8_CH3N            HAL_GPIO_AF_14 /*!< TIM8 CH3 complementary output     */
#define HAL_GPIO_AF14_TIM8_CH4N            HAL_GPIO_AF_14 /*!< TIM8 CH4 complementary output     */
#define HAL_GPIO_AF14_TIM10                HAL_GPIO_AF_14 /*!< TIM10 Alternate Function mapping  */
#define HAL_GPIO_AF14_TIM10_CH1            HAL_GPIO_AF_14 /*!< TIM10 Multi-purpose Channel 1     */
#define HAL_GPIO_AF14_TIM12                HAL_GPIO_AF_14 /*!< TIM12 Alternate Function mapping  */
#define HAL_GPIO_AF14_TIM12_CH1            HAL_GPIO_AF_14 /*!< TIM12 Multi-purpose Channel 1     */
#define HAL_GPIO_AF14_TIM12_CH2            HAL_GPIO_AF_14 /*!< TIM12 Multi-purpose Channel 2     */
#define HAL_GPIO_AF14_TIM13                HAL_GPIO_AF_14 /*!< TIM13 Alternate Function mapping  */
#define HAL_GPIO_AF14_TIM13_CH1            HAL_GPIO_AF_14 /*!< TIM13 Multi-purpose Channel 1     */
#define HAL_GPIO_AF14_TIM15                HAL_GPIO_AF_14 /*!< TIM15 Alternate Function mapping  */
#define HAL_GPIO_AF14_TIM15_BKIN           HAL_GPIO_AF_14 /*!< TIM15 Break input                 */
#define HAL_GPIO_AF14_TIM15_CH1N           HAL_GPIO_AF_14 /*!< TIM15 CH1 complementary output    */
#define HAL_GPIO_AF14_UART5                HAL_GPIO_AF_14 /*!< UART5 Alternate Function mapping  */
#define HAL_GPIO_AF14_UART5_CTS            HAL_GPIO_AF_14 /*!< UART5 Clear to send               */
#define HAL_GPIO_AF14_UART5_RTS            HAL_GPIO_AF_14 /*!< UART5 Request to send             */
#define HAL_GPIO_AF14_UART5_RX             HAL_GPIO_AF_14 /*!< UART5 Serial Data Receive Input   */
#define HAL_GPIO_AF14_UART5_TX             HAL_GPIO_AF_14 /*!< UART5 Transmit Data Output        */

/**
  * @brief   AF 15 selection
  */
#define HAL_GPIO_AF15_EVENTOUT             HAL_GPIO_AF_15 /*!< EVENTOUT Alternate Function mapping */
#elif defined (STM32G5_DEVICE_ID) && (STM32G5_DEVICE_ID == 0x44BU)
/**
  * @brief   AF 0 selection
  */
#define HAL_GPIO_AF0_AUDIOCLK              HAL_GPIO_AF_0  /*!< Audio Clock                       */
#define HAL_GPIO_AF0_JTCK                  HAL_GPIO_AF_0  /*!< JTAG Test Clock                   */
#define HAL_GPIO_AF0_JTDI                  HAL_GPIO_AF_0  /*!< JTAG Test Data In                 */
#define HAL_GPIO_AF0_JTDO                  HAL_GPIO_AF_0  /*!< JTAG Test Data Out                */
#define HAL_GPIO_AF0_JTMS                  HAL_GPIO_AF_0  /*!< JTAG Test Mode Select             */
#define HAL_GPIO_AF0_MCO                   HAL_GPIO_AF_0  /*!< MCO Alternate Function mapping    */
#define HAL_GPIO_AF0_MCO1                  HAL_GPIO_AF_0  /*!< MCO1                              */
#define HAL_GPIO_AF0_MCO2                  HAL_GPIO_AF_0  /*!< MCO2                              */
#define HAL_GPIO_AF0_NJTRST                HAL_GPIO_AF_0  /*!< NJTRST                            */
#define HAL_GPIO_AF0_PWR                   HAL_GPIO_AF_0  /*!< PWR Alternate Function mapping    */
#define HAL_GPIO_AF0_PWR_CSLEEP            HAL_GPIO_AF_0  /*!< PWR CSLEEP mode                   */
#define HAL_GPIO_AF0_PWR_CSTOP             HAL_GPIO_AF_0  /*!< PWR CSTOP mode                    */
#define HAL_GPIO_AF0_RTC                   HAL_GPIO_AF_0  /*!< RTC Alternate Function mapping    */
#define HAL_GPIO_AF0_RTC_OUT2              HAL_GPIO_AF_0  /*!< RTC Output 2                      */
#define HAL_GPIO_AF0_RTC_REFIN             HAL_GPIO_AF_0  /*!< RTC Reference input               */
#define HAL_GPIO_AF0_SWCLK                 HAL_GPIO_AF_0  /*!< Serial Wire Clock                 */
#define HAL_GPIO_AF0_SWDIO                 HAL_GPIO_AF_0  /*!< Serial Wire Debug Input/Output    */
#define HAL_GPIO_AF0_TRACECLK              HAL_GPIO_AF_0  /*!< TRACE Clock                       */
#define HAL_GPIO_AF0_TRACED0               HAL_GPIO_AF_0  /*!< TRACE Data Output 0               */
#define HAL_GPIO_AF0_TRACED1               HAL_GPIO_AF_0  /*!< TRACE Data Output 1               */
#define HAL_GPIO_AF0_TRACED2               HAL_GPIO_AF_0  /*!< TRACE Data Output 2               */
#define HAL_GPIO_AF0_TRACED3               HAL_GPIO_AF_0  /*!< TRACE Data Output 3               */
#define HAL_GPIO_AF0_TRACESWO              HAL_GPIO_AF_0  /*!< TRACE Serial Wire Output          */

/**
  * @brief   AF 1 selection
  */
#define HAL_GPIO_AF1_HRTIM1                HAL_GPIO_AF_1  /*!< HRTIM1 Alternate Function mapping */
#define HAL_GPIO_AF1_HRTIM1_CHB1           HAL_GPIO_AF_1  /*!< HRTIM1 Timer B Output 1           */
#define HAL_GPIO_AF1_HRTIM1_CHC1           HAL_GPIO_AF_1  /*!< HRTIM1 Timer C Output 1           */
#define HAL_GPIO_AF1_HRTIM1_CHC2           HAL_GPIO_AF_1  /*!< HRTIM1 Timer C Output 2           */
#define HAL_GPIO_AF1_HRTIM1_EEV2           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 2           */
#define HAL_GPIO_AF1_HRTIM1_EEV4           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 4           */
#define HAL_GPIO_AF1_HRTIM1_EEV6           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 6           */
#define HAL_GPIO_AF1_HRTIM1_EEV7           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 7           */
#define HAL_GPIO_AF1_HRTIM1_EEV8           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 8           */
#define HAL_GPIO_AF1_HRTIM1_EEV9           HAL_GPIO_AF_1  /*!< HRTIM1 External Event 9           */
#define HAL_GPIO_AF1_HRTIM1_EEV10          HAL_GPIO_AF_1  /*!< HRTIM1 External Event 10          */
#define HAL_GPIO_AF1_HRTIM1_EEV11          HAL_GPIO_AF_1  /*!< HRTIM1 External Event 11          */
#define HAL_GPIO_AF1_HRTIM1_FLT1           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 1                    */
#define HAL_GPIO_AF1_HRTIM1_FLT2           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 2                    */
#define HAL_GPIO_AF1_HRTIM1_FLT3           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 3                    */
#define HAL_GPIO_AF1_HRTIM1_FLT4           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 4                    */
#define HAL_GPIO_AF1_HRTIM1_FLT5           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 5                    */
#define HAL_GPIO_AF1_HRTIM1_FLT6           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 6                    */
#define HAL_GPIO_AF1_HRTIM1_FLT7           HAL_GPIO_AF_1  /*!< HRTIM1 Fault 7                    */
#define HAL_GPIO_AF1_HRTIM1_SCIN           HAL_GPIO_AF_1  /*!< HRTIM1 Synchronization Input      */
#define HAL_GPIO_AF1_HRTIM1_SCOUT          HAL_GPIO_AF_1  /*!< HRTIM1 Synchronization Output     */
#define HAL_GPIO_AF1_LPTIM1                HAL_GPIO_AF_1  /*!< LPTIM1 Alternate Function mapping */
#define HAL_GPIO_AF1_LPTIM1_IN2            HAL_GPIO_AF_1  /*!< LPTIM1 Channel 2 Input            */
#define HAL_GPIO_AF1_TIM1                  HAL_GPIO_AF_1  /*!< TIM1 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM1_BKIN2            HAL_GPIO_AF_1  /*!< TIM1 Break input 2                */
#define HAL_GPIO_AF1_TIM1_CH2              HAL_GPIO_AF_1  /*!< TIM1 Multi-purpose Channel 2      */
#define HAL_GPIO_AF1_TIM1_CH3              HAL_GPIO_AF_1  /*!< TIM1 Multi-purpose Channel 3      */
#define HAL_GPIO_AF1_TIM1_CH4N             HAL_GPIO_AF_1  /*!< TIM1 CH4 complementary output     */
#define HAL_GPIO_AF1_TIM1_ETR              HAL_GPIO_AF_1  /*!< TIM1 External trigger input       */
#define HAL_GPIO_AF1_TIM2                  HAL_GPIO_AF_1  /*!< TIM2 Alternate Function mapping   */
#define HAL_GPIO_AF1_TIM2_CH1              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 1      */
#define HAL_GPIO_AF1_TIM2_CH2              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 2      */
#define HAL_GPIO_AF1_TIM2_CH3              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 3      */
#define HAL_GPIO_AF1_TIM2_CH4              HAL_GPIO_AF_1  /*!< TIM2 Multi-purpose Channel 4      */
#define HAL_GPIO_AF1_TIM15                 HAL_GPIO_AF_1  /*!< TIM15 Alternate Function mapping  */
#define HAL_GPIO_AF1_TIM15_BKIN            HAL_GPIO_AF_1  /*!< TIM15 Break input                 */
#define HAL_GPIO_AF1_TIM15_CH1             HAL_GPIO_AF_1  /*!< TIM15 Multi-purpose Channel 1     */
#define HAL_GPIO_AF1_TIM15_CH2             HAL_GPIO_AF_1  /*!< TIM15 Multi-purpose Channel 2     */
#define HAL_GPIO_AF1_TIM16                 HAL_GPIO_AF_1  /*!< TIM16 Alternate Function mapping  */
#define HAL_GPIO_AF1_TIM16_BKIN            HAL_GPIO_AF_1  /*!< TIM16 Break input                 */
#define HAL_GPIO_AF1_TIM16_CH1             HAL_GPIO_AF_1  /*!< TIM16 Multi-purpose Channel 1     */
#define HAL_GPIO_AF1_TIM16_CH1N            HAL_GPIO_AF_1  /*!< TIM16 CH1 complementary output    */
#define HAL_GPIO_AF1_TIM17                 HAL_GPIO_AF_1  /*!< TIM17 Alternate Function mapping  */
#define HAL_GPIO_AF1_TIM17_BKIN            HAL_GPIO_AF_1  /*!< TIM17 Break input                 */
#define HAL_GPIO_AF1_TIM17_CH1             HAL_GPIO_AF_1  /*!< TIM17 Multi-purpose Channel 1     */

/**
  * @brief   AF 2 selection
  */
#define HAL_GPIO_AF2_I2S1                  HAL_GPIO_AF_2  /*!< I2S1 Alternate Function mapping   */
#define HAL_GPIO_AF2_I2S1_CK               HAL_GPIO_AF_2  /*!< I2S1 Clock                        */
#define HAL_GPIO_AF2_I2S1_SDO              HAL_GPIO_AF_2  /*!< I2S1 Serial Data Output           */
#define HAL_GPIO_AF2_SPI1                  HAL_GPIO_AF_2  /*!< SPI1 Alternate Function mapping   */
#define HAL_GPIO_AF2_SPI1_MOSI             HAL_GPIO_AF_2  /*!< SPI1 Master Out Slave In          */
#define HAL_GPIO_AF2_SPI1_SCK              HAL_GPIO_AF_2  /*!< SPI1 Serial Clock                 */
#define HAL_GPIO_AF2_TIM1                  HAL_GPIO_AF_2  /*!< TIM1 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM1_BKIN             HAL_GPIO_AF_2  /*!< TIM1 Break input                  */
#define HAL_GPIO_AF2_TIM1_BKIN2            HAL_GPIO_AF_2  /*!< TIM1 Break input 2                */
#define HAL_GPIO_AF2_TIM1_CH1              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM1_CH2              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 2      */
#define HAL_GPIO_AF2_TIM1_CH3              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM1_CH3N             HAL_GPIO_AF_2  /*!< TIM1 CH3 complementary output     */
#define HAL_GPIO_AF2_TIM1_CH4              HAL_GPIO_AF_2  /*!< TIM1 Multi-purpose Channel 4      */
#define HAL_GPIO_AF2_TIM1_ETR              HAL_GPIO_AF_2  /*!< TIM1 External trigger input       */
#define HAL_GPIO_AF2_TIM2                  HAL_GPIO_AF_2  /*!< TIM2 Alternate Function mapping   */
#define HAL_GPIO_AF2_TIM2_CH1              HAL_GPIO_AF_2  /*!< TIM2 Multi-purpose Channel 1      */
#define HAL_GPIO_AF2_TIM2_CH3              HAL_GPIO_AF_2  /*!< TIM2 Multi-purpose Channel 3      */
#define HAL_GPIO_AF2_TIM2_ETR              HAL_GPIO_AF_2  /*!< TIM2 External trigger input       */
#define HAL_GPIO_AF2_TIM15                 HAL_GPIO_AF_2  /*!< TIM15 Alternate Function mapping  */
#define HAL_GPIO_AF2_TIM15_BKIN            HAL_GPIO_AF_2  /*!< TIM15 Break input                 */
#define HAL_GPIO_AF2_TIM15_CH1N            HAL_GPIO_AF_2  /*!< TIM15 CH1 complementary output    */

/**
  * @brief   AF 3 selection
  */
#define HAL_GPIO_AF3_I3C1                  HAL_GPIO_AF_3  /*!< I3C1 Alternate Function mapping    */
#define HAL_GPIO_AF3_I3C1_SCL              HAL_GPIO_AF_3  /*!< I3C1 Clock                         */
#define HAL_GPIO_AF3_I3C1_SDA              HAL_GPIO_AF_3  /*!< I3C1 Data                          */
#define HAL_GPIO_AF3_LPUART1               HAL_GPIO_AF_3  /*!< LPUART1 Alternate Function mapping */
#define HAL_GPIO_AF3_LPUART1_CTS           HAL_GPIO_AF_3  /*!< LPUART1 Clear to send              */
#define HAL_GPIO_AF3_LPUART1_RTS           HAL_GPIO_AF_3  /*!< LPUART1 Request to send            */
#define HAL_GPIO_AF3_LPUART1_RX            HAL_GPIO_AF_3  /*!< LPUART1 Serial Data Receive Input  */
#define HAL_GPIO_AF3_LPUART1_TX            HAL_GPIO_AF_3  /*!< LPUART1 Transmit Data Output       */
#define HAL_GPIO_AF3_TIM8                  HAL_GPIO_AF_3  /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF3_TIM8_BKIN2            HAL_GPIO_AF_3  /*!< TIM8 Break input 2                 */
#define HAL_GPIO_AF3_TIM8_CH1              HAL_GPIO_AF_3  /*!< TIM8 Multi-purpose Channel 1       */
#define HAL_GPIO_AF3_TIM8_CH3              HAL_GPIO_AF_3  /*!< TIM8 Multi-purpose Channel 3       */
#define HAL_GPIO_AF3_TIM15                 HAL_GPIO_AF_3  /*!< TIM15 Alternate Function mapping   */
#define HAL_GPIO_AF3_TIM15_CH1             HAL_GPIO_AF_3  /*!< TIM15 Multi-purpose Channel 1      */
#define HAL_GPIO_AF3_TIM15_CH2             HAL_GPIO_AF_3  /*!< TIM15 Multi-purpose Channel 2      */

/**
  * @brief   AF 4 selection
  */
#define HAL_GPIO_AF4_I2C1                  HAL_GPIO_AF_4  /*!< I2C1 Alternate Function mapping    */
#define HAL_GPIO_AF4_I2C1_SCL              HAL_GPIO_AF_4  /*!< I2C1 Clock                         */
#define HAL_GPIO_AF4_I2C1_SDA              HAL_GPIO_AF_4  /*!< I2C1 Data                          */
#define HAL_GPIO_AF4_I2C2                  HAL_GPIO_AF_4  /*!< I2C2 Alternate Function mapping    */
#define HAL_GPIO_AF4_I2C2_SCL              HAL_GPIO_AF_4  /*!< I2C2 Clock                         */
#define HAL_GPIO_AF4_I2C2_SDA              HAL_GPIO_AF_4  /*!< I2C2 Data                          */
#define HAL_GPIO_AF4_I2C2_SMBA             HAL_GPIO_AF_4  /*!< I2C2 SMBus Alert                   */
#define HAL_GPIO_AF4_TIM8                  HAL_GPIO_AF_4  /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF4_TIM8_BKIN             HAL_GPIO_AF_4  /*!< TIM8 Break input                   */
#define HAL_GPIO_AF4_TIM8_CH1              HAL_GPIO_AF_4  /*!< TIM8 Multi-purpose Channel 1       */
#define HAL_GPIO_AF4_TIM8_CH1N             HAL_GPIO_AF_4  /*!< TIM8 CH1 complementary output      */
#define HAL_GPIO_AF4_TIM8_CH2N             HAL_GPIO_AF_4  /*!< TIM8 CH2 complementary output      */
#define HAL_GPIO_AF4_TIM8_CH3              HAL_GPIO_AF_4  /*!< TIM8 Multi-purpose Channel 3       */
#define HAL_GPIO_AF4_TIM8_CH3N             HAL_GPIO_AF_4  /*!< TIM8 CH3 complementary output      */
#define HAL_GPIO_AF4_TIM8_CH4              HAL_GPIO_AF_4  /*!< TIM8 Multi-purpose Channel 4       */
#define HAL_GPIO_AF4_TIM8_ETR              HAL_GPIO_AF_4  /*!< TIM8 External trigger input        */
#define HAL_GPIO_AF4_TIM11                 HAL_GPIO_AF_4  /*!< TIM11 Alternate Function mapping   */
#define HAL_GPIO_AF4_TIM11_CH1             HAL_GPIO_AF_4  /*!< TIM11 Multi-purpose Channel 1      */
#define HAL_GPIO_AF4_TIM14                 HAL_GPIO_AF_4  /*!< TIM14 Alternate Function mapping   */
#define HAL_GPIO_AF4_TIM14_CH1             HAL_GPIO_AF_4  /*!< TIM14 Multi-purpose Channel 1      */
#define HAL_GPIO_AF4_USART1                HAL_GPIO_AF_4  /*!< USART1 Alternate Function mapping  */
#define HAL_GPIO_AF4_USART1_CK             HAL_GPIO_AF_4  /*!< USART1 Clock                       */
#define HAL_GPIO_AF4_USART1_RX             HAL_GPIO_AF_4  /*!< USART1 Serial Data Receive Input   */
#define HAL_GPIO_AF4_USART1_TX             HAL_GPIO_AF_4  /*!< USART1 Transmit Data Output        */

/**
  * @brief   AF 5 selection
  */
#define HAL_GPIO_AF5_I2S1                  HAL_GPIO_AF_5  /*!< I2S1 Alternate Function mapping    */
#define HAL_GPIO_AF5_I2S1_CK               HAL_GPIO_AF_5  /*!< I2S1 Clock                         */
#define HAL_GPIO_AF5_I2S1_MCK              HAL_GPIO_AF_5  /*!< I2S1 Master Clock                  */
#define HAL_GPIO_AF5_I2S1_SDI              HAL_GPIO_AF_5  /*!< I2S1 Serial Data Input             */
#define HAL_GPIO_AF5_I2S1_SDO              HAL_GPIO_AF_5  /*!< I2S1 Serial Data Output            */
#define HAL_GPIO_AF5_I2S1_WS               HAL_GPIO_AF_5  /*!< I2S1 Word Select                   */
#define HAL_GPIO_AF5_I2S2                  HAL_GPIO_AF_5  /*!< I2S2 Alternate Function mapping    */
#define HAL_GPIO_AF5_I2S2_CK               HAL_GPIO_AF_5  /*!< I2S2 Clock                         */
#define HAL_GPIO_AF5_I2S2_SDI              HAL_GPIO_AF_5  /*!< I2S2 Serial Data Input             */
#define HAL_GPIO_AF5_I2S2_SDO              HAL_GPIO_AF_5  /*!< I2S2 Serial Data Output            */
#define HAL_GPIO_AF5_I2S2_WS               HAL_GPIO_AF_5  /*!< I2S2 Word Select                   */
#define HAL_GPIO_AF5_LPTIM1                HAL_GPIO_AF_5  /*!< LPTIM1 Alternate Function mapping  */
#define HAL_GPIO_AF5_LPTIM1_CH1            HAL_GPIO_AF_5  /*!< LPTIM1 Multi-purpose Channel 1     */
#define HAL_GPIO_AF5_LPTIM1_IN1            HAL_GPIO_AF_5  /*!< LPTIM1 Channel 1 Input             */
#define HAL_GPIO_AF5_LPTIM1_IN2            HAL_GPIO_AF_5  /*!< LPTIM1 Channel 2 Input             */
#define HAL_GPIO_AF5_SPI1                  HAL_GPIO_AF_5  /*!< SPI1 Alternate Function mapping    */
#define HAL_GPIO_AF5_SPI1_MISO             HAL_GPIO_AF_5  /*!< SPI1 Master In Slave Out           */
#define HAL_GPIO_AF5_SPI1_MOSI             HAL_GPIO_AF_5  /*!< SPI1 Master Out Slave In           */
#define HAL_GPIO_AF5_SPI1_NSS              HAL_GPIO_AF_5  /*!< SPI1 Slave Select                  */
#define HAL_GPIO_AF5_SPI1_RDY              HAL_GPIO_AF_5  /*!< SPI1 Ready                         */
#define HAL_GPIO_AF5_SPI1_SCK              HAL_GPIO_AF_5  /*!< SPI1 Serial Clock                  */
#define HAL_GPIO_AF5_SPI2                  HAL_GPIO_AF_5  /*!< SPI2 Alternate Function mapping    */
#define HAL_GPIO_AF5_SPI2_MISO             HAL_GPIO_AF_5  /*!< SPI2 Master In Slave Out           */
#define HAL_GPIO_AF5_SPI2_MOSI             HAL_GPIO_AF_5  /*!< SPI2 Master Out Slave In           */
#define HAL_GPIO_AF5_SPI2_NSS              HAL_GPIO_AF_5  /*!< SPI2 Slave Select                  */
#define HAL_GPIO_AF5_SPI2_RDY              HAL_GPIO_AF_5  /*!< SPI2 Ready                         */
#define HAL_GPIO_AF5_SPI2_SCK              HAL_GPIO_AF_5  /*!< SPI2 Serial Clock                  */
#define HAL_GPIO_AF5_TIM8                  HAL_GPIO_AF_5  /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF5_TIM8_BKIN             HAL_GPIO_AF_5  /*!< TIM8 Break input                   */
#define HAL_GPIO_AF5_TIM8_CH1N             HAL_GPIO_AF_5  /*!< TIM8 CH1 complementary output      */
#define HAL_GPIO_AF5_TIM8_CH2              HAL_GPIO_AF_5  /*!< TIM8 Multi-purpose Channel 2       */
#define HAL_GPIO_AF5_TIM8_CH2N             HAL_GPIO_AF_5  /*!< TIM8 CH2 complementary output      */
#define HAL_GPIO_AF5_TIM16                 HAL_GPIO_AF_5  /*!< TIM16 Alternate Function mapping   */
#define HAL_GPIO_AF5_TIM16_BKIN            HAL_GPIO_AF_5  /*!< TIM16 Break input                  */
#define HAL_GPIO_AF5_TIM16_CH1N            HAL_GPIO_AF_5  /*!< TIM16 CH1 complementary output     */

/**
  * @brief   AF 6 selection
  */
#define HAL_GPIO_AF6_TIM1                  HAL_GPIO_AF_6  /*!< TIM1 Alternate Function mapping    */
#define HAL_GPIO_AF6_TIM1_BKIN             HAL_GPIO_AF_6  /*!< TIM1 Break input                   */
#define HAL_GPIO_AF6_TIM1_BKIN2            HAL_GPIO_AF_6  /*!< TIM1 Break input 2                 */
#define HAL_GPIO_AF6_TIM1_CH1              HAL_GPIO_AF_6  /*!< TIM1 Multi-purpose Channel 1       */
#define HAL_GPIO_AF6_TIM1_CH1N             HAL_GPIO_AF_6  /*!< TIM1 CH1 complementary output      */
#define HAL_GPIO_AF6_TIM1_CH2N             HAL_GPIO_AF_6  /*!< TIM1 CH2 complementary output      */
#define HAL_GPIO_AF6_TIM1_CH3              HAL_GPIO_AF_6  /*!< TIM1 Multi-purpose Channel 3       */
#define HAL_GPIO_AF6_TIM1_CH3N             HAL_GPIO_AF_6  /*!< TIM1 CH3 complementary output      */
#define HAL_GPIO_AF6_TIM1_CH4N             HAL_GPIO_AF_6  /*!< TIM1 CH4 complementary output      */
#define HAL_GPIO_AF6_TIM8                  HAL_GPIO_AF_6  /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF6_TIM8_CH2              HAL_GPIO_AF_6  /*!< TIM8 Multi-purpose Channel 2       */
#define HAL_GPIO_AF6_TIM8_CH4N             HAL_GPIO_AF_6  /*!< TIM8 CH4 complementary output      */
#define HAL_GPIO_AF6_TIM8_ETR              HAL_GPIO_AF_6  /*!< TIM8 External trigger input        */

/**
  * @brief   AF 7 selection
  */
#define HAL_GPIO_AF7_I2S2                  HAL_GPIO_AF_7  /*!< I2S2 Alternate Function mapping    */
#define HAL_GPIO_AF7_I2S2_CK               HAL_GPIO_AF_7  /*!< I2S2 Clock                         */
#define HAL_GPIO_AF7_I2S2_MCK              HAL_GPIO_AF_7  /*!< I2S2 Master Clock                  */
#define HAL_GPIO_AF7_SPI2                  HAL_GPIO_AF_7  /*!< SPI2 Alternate Function mapping    */
#define HAL_GPIO_AF7_SPI2_RDY              HAL_GPIO_AF_7  /*!< SPI2 Ready                         */
#define HAL_GPIO_AF7_SPI2_SCK              HAL_GPIO_AF_7  /*!< SPI2 Serial Clock                  */
#define HAL_GPIO_AF7_TIM17                 HAL_GPIO_AF_7  /*!< TIM17 Alternate Function mapping   */
#define HAL_GPIO_AF7_TIM17_BKIN            HAL_GPIO_AF_7  /*!< TIM17 Break input                  */
#define HAL_GPIO_AF7_TIM17_CH1             HAL_GPIO_AF_7  /*!< TIM17 Multi-purpose Channel 1      */
#define HAL_GPIO_AF7_TIM17_CH1N            HAL_GPIO_AF_7  /*!< TIM17 CH1 complementary output     */
#define HAL_GPIO_AF7_UART6                 HAL_GPIO_AF_7  /*!< UART6 Alternate Function mapping   */
#define HAL_GPIO_AF7_UART6_CTS             HAL_GPIO_AF_7  /*!< UART6 Clear to send                */
#define HAL_GPIO_AF7_UART6_RTS             HAL_GPIO_AF_7  /*!< UART6 Request to send              */
#define HAL_GPIO_AF7_UART6_TX              HAL_GPIO_AF_7  /*!< UART6 Transmit Data Output         */
#define HAL_GPIO_AF7_USART1                HAL_GPIO_AF_7  /*!< USART1 Alternate Function mapping  */
#define HAL_GPIO_AF7_USART1_CK             HAL_GPIO_AF_7  /*!< USART1 Clock                       */
#define HAL_GPIO_AF7_USART1_CTS            HAL_GPIO_AF_7  /*!< USART1 Clear to send               */
#define HAL_GPIO_AF7_USART1_NSS            HAL_GPIO_AF_7  /*!< USART1 Slave Select                */
#define HAL_GPIO_AF7_USART1_RTS            HAL_GPIO_AF_7  /*!< USART1 Request to send             */
#define HAL_GPIO_AF7_USART1_RX             HAL_GPIO_AF_7  /*!< USART1 Serial Data Receive Input   */
#define HAL_GPIO_AF7_USART1_TX             HAL_GPIO_AF_7  /*!< USART1 Transmit Data Output        */
#define HAL_GPIO_AF7_USART2                HAL_GPIO_AF_7  /*!< USART2 Alternate Function mapping  */
#define HAL_GPIO_AF7_USART2_CK             HAL_GPIO_AF_7  /*!< USART2 Clock                       */
#define HAL_GPIO_AF7_USART2_CTS            HAL_GPIO_AF_7  /*!< USART2 Clear to send               */
#define HAL_GPIO_AF7_USART2_NSS            HAL_GPIO_AF_7  /*!< USART2 Slave Select                */
#define HAL_GPIO_AF7_USART2_RTS            HAL_GPIO_AF_7  /*!< USART2 Request to send             */
#define HAL_GPIO_AF7_USART2_RX             HAL_GPIO_AF_7  /*!< USART2 Serial Data Receive Input   */
#define HAL_GPIO_AF7_USART2_TX             HAL_GPIO_AF_7  /*!< USART2 Transmit Data Output        */

/**
  * @brief   AF 8 selection
  */
#define HAL_GPIO_AF8_LPUART1               HAL_GPIO_AF_8  /*!< LPUART1 Alternate Function mapping */
#define HAL_GPIO_AF8_LPUART1_CTS           HAL_GPIO_AF_8  /*!< LPUART1 Clear to send              */
#define HAL_GPIO_AF8_LPUART1_RTS           HAL_GPIO_AF_8  /*!< LPUART1 Request to send            */
#define HAL_GPIO_AF8_LPUART1_RX            HAL_GPIO_AF_8  /*!< LPUART1 Serial Data Receive Input  */
#define HAL_GPIO_AF8_LPUART1_TX            HAL_GPIO_AF_8  /*!< LPUART1 Transmit Data Output       */
#define HAL_GPIO_AF8_UART4                 HAL_GPIO_AF_8  /*!< UART4 Alternate Function mapping   */
#define HAL_GPIO_AF8_UART4_CTS             HAL_GPIO_AF_8  /*!< UART4 Clear to send                */
#define HAL_GPIO_AF8_UART4_RTS             HAL_GPIO_AF_8  /*!< UART4 Request to send              */
#define HAL_GPIO_AF8_UART4_RX              HAL_GPIO_AF_8  /*!< UART4 Serial Data Receive Input    */
#define HAL_GPIO_AF8_UART4_TX              HAL_GPIO_AF_8  /*!< UART4 Transmit Data Output         */
#define HAL_GPIO_AF8_UART6                 HAL_GPIO_AF_8  /*!< UART6 Alternate Function mapping   */
#define HAL_GPIO_AF8_UART6_RX              HAL_GPIO_AF_8  /*!< UART6 Serial Data Receive Input    */
#define HAL_GPIO_AF8_UART6_TX              HAL_GPIO_AF_8  /*!< UART6 Transmit Data Output         */

/**
  * @brief   AF 9 selection
  */
#define HAL_GPIO_AF9_FDCAN1                HAL_GPIO_AF_9  /*!< FDCAN1 Alternate Function mapping  */
#define HAL_GPIO_AF9_FDCAN1_RX             HAL_GPIO_AF_9  /*!< FDCAN1 Receive pin                 */
#define HAL_GPIO_AF9_FDCAN1_TX             HAL_GPIO_AF_9  /*!< FDCAN1 Transmit pin                */
#define HAL_GPIO_AF9_I2C1                  HAL_GPIO_AF_9  /*!< I2C1 Alternate Function mapping    */
#define HAL_GPIO_AF9_I2C1_SCL              HAL_GPIO_AF_9  /*!< I2C1 Clock                         */
#define HAL_GPIO_AF9_I2C1_SMBA             HAL_GPIO_AF_9  /*!< I2C1 SMBus Alert                   */
#define HAL_GPIO_AF9_LPTIM1                HAL_GPIO_AF_9  /*!< LPTIM1 Alternate Function mapping  */
#define HAL_GPIO_AF9_LPTIM1_CH1            HAL_GPIO_AF_9  /*!< LPTIM1 Multi-purpose Channel 1     */
#define HAL_GPIO_AF9_LPTIM1_CH2            HAL_GPIO_AF_9  /*!< LPTIM1 Multi-purpose Channel 2     */
#define HAL_GPIO_AF9_LPTIM1_ETR            HAL_GPIO_AF_9  /*!< LPTIM1 External trigger input      */
#define HAL_GPIO_AF9_LPTIM1_IN1            HAL_GPIO_AF_9  /*!< LPTIM1 Channel 1 Input             */
#define HAL_GPIO_AF9_TIM1                  HAL_GPIO_AF_9  /*!< TIM1 Alternate Function mapping    */
#define HAL_GPIO_AF9_TIM1_BKIN             HAL_GPIO_AF_9  /*!< TIM1 Break input                   */
#define HAL_GPIO_AF9_TIM1_BKIN2            HAL_GPIO_AF_9  /*!< TIM1 Break input 2                 */
#define HAL_GPIO_AF9_TIM1_CH3N             HAL_GPIO_AF_9  /*!< TIM1 CH3 complementary output      */
#define HAL_GPIO_AF9_TIM15                 HAL_GPIO_AF_9  /*!< TIM15 Alternate Function mapping   */
#define HAL_GPIO_AF9_TIM15_BKIN            HAL_GPIO_AF_9  /*!< TIM15 Break input                  */
#define HAL_GPIO_AF9_TIM15_CH1             HAL_GPIO_AF_9  /*!< TIM15 Multi-purpose Channel 1      */
#define HAL_GPIO_AF9_TIM15_CH1N            HAL_GPIO_AF_9  /*!< TIM15 CH1 complementary output     */
#define HAL_GPIO_AF9_TIM15_CH2             HAL_GPIO_AF_9  /*!< TIM15 Multi-purpose Channel 2      */
#define HAL_GPIO_AF9_UART5                 HAL_GPIO_AF_9  /*!< UART5 Alternate Function mapping   */
#define HAL_GPIO_AF9_UART5_CTS             HAL_GPIO_AF_9  /*!< UART5 Clear to send                */
#define HAL_GPIO_AF9_UART5_RTS             HAL_GPIO_AF_9  /*!< UART5 Request to send              */
#define HAL_GPIO_AF9_UART5_RX              HAL_GPIO_AF_9  /*!< UART5 Serial Data Receive Input    */
#define HAL_GPIO_AF9_UART5_TX              HAL_GPIO_AF_9  /*!< UART5 Transmit Data Output         */

/**
  * @brief   AF 10 selection
  */
#define HAL_GPIO_AF10_TIM2                 HAL_GPIO_AF_10 /*!< TIM2 Alternate Function mapping    */
#define HAL_GPIO_AF10_TIM2_CH1             HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 1       */
#define HAL_GPIO_AF10_TIM2_CH4             HAL_GPIO_AF_10 /*!< TIM2 Multi-purpose Channel 4       */
#define HAL_GPIO_AF10_TIM2_ETR             HAL_GPIO_AF_10 /*!< TIM2 External trigger input        */
#define HAL_GPIO_AF10_TIM8                 HAL_GPIO_AF_10 /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF10_TIM8_BKIN            HAL_GPIO_AF_10 /*!< TIM8 Break input                   */
#define HAL_GPIO_AF10_TIM8_BKIN2           HAL_GPIO_AF_10 /*!< TIM8 Break input 2                 */
#define HAL_GPIO_AF10_TIM8_CH2             HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 2       */
#define HAL_GPIO_AF10_TIM8_CH3             HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 3       */
#define HAL_GPIO_AF10_TIM8_CH3N            HAL_GPIO_AF_10 /*!< TIM8 CH3 complementary output      */
#define HAL_GPIO_AF10_TIM8_CH4             HAL_GPIO_AF_10 /*!< TIM8 Multi-purpose Channel 4       */
#define HAL_GPIO_AF10_TIM8_CH4N            HAL_GPIO_AF_10 /*!< TIM8 CH4 complementary output      */
#define HAL_GPIO_AF10_TIM8_ETR             HAL_GPIO_AF_10 /*!< TIM8 External trigger input        */

/**
  * @brief   AF 11 selection
  */
#define HAL_GPIO_AF11_HRTIM1               HAL_GPIO_AF_11 /*!< HRTIM1 Alternate Function mapping  */
#define HAL_GPIO_AF11_HRTIM1_CHA2          HAL_GPIO_AF_11 /*!< HRTIM1 Timer A Output 2            */
#define HAL_GPIO_AF11_HRTIM1_CHD1          HAL_GPIO_AF_11 /*!< HRTIM1 Timer D Output 1            */
#define HAL_GPIO_AF11_HRTIM1_CHD2          HAL_GPIO_AF_11 /*!< HRTIM1 Timer D Output 2            */
#define HAL_GPIO_AF11_HRTIM1_CHE1L         HAL_GPIO_AF_11 /*!< HRTIM1 Timer E Output 1 Low        */
#define HAL_GPIO_AF11_HRTIM1_CHE2L         HAL_GPIO_AF_11 /*!< HRTIM1 Timer E Output 2 Low        */
#define HAL_GPIO_AF11_HRTIM1_CHF1L         HAL_GPIO_AF_11 /*!< HRTIM1 Timer F Output 1 Low        */
#define HAL_GPIO_AF11_HRTIM1_CHF2L         HAL_GPIO_AF_11 /*!< HRTIM1 Timer F Output 2 Low        */
#define HAL_GPIO_AF11_HRTIM1_EEV1          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 1            */
#define HAL_GPIO_AF11_HRTIM1_EEV2          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 2            */
#define HAL_GPIO_AF11_HRTIM1_EEV3          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 3            */
#define HAL_GPIO_AF11_HRTIM1_EEV6          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 6            */
#define HAL_GPIO_AF11_HRTIM1_EEV9          HAL_GPIO_AF_11 /*!< HRTIM1 External Event 9            */
#define HAL_GPIO_AF11_HRTIM1_EEV10         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 10           */
#define HAL_GPIO_AF11_HRTIM1_EEV14         HAL_GPIO_AF_11 /*!< HRTIM1 External Event 14           */
#define HAL_GPIO_AF11_HRTIM1_FLT2          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 2                     */
#define HAL_GPIO_AF11_HRTIM1_FLT5          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 5                     */
#define HAL_GPIO_AF11_HRTIM1_FLT6          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 6                     */
#define HAL_GPIO_AF11_HRTIM1_FLT7          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 7                     */
#define HAL_GPIO_AF11_HRTIM1_FLT8          HAL_GPIO_AF_11 /*!< HRTIM1 Fault 8                     */
#define HAL_GPIO_AF11_HRTIM1_SCIN          HAL_GPIO_AF_11 /*!< HRTIM1 Synchronization Input       */
#define HAL_GPIO_AF11_TIM9                 HAL_GPIO_AF_11 /*!< TIM9 Alternate Function mapping    */
#define HAL_GPIO_AF11_TIM9_CH1             HAL_GPIO_AF_11 /*!< TIM9 Multi-purpose Channel 1       */
#define HAL_GPIO_AF11_TIM9_CH2             HAL_GPIO_AF_11 /*!< TIM9 Multi-purpose Channel 2       */

/**
  * @brief   AF 12 selection
  */
#define HAL_GPIO_AF12_HRTIM1               HAL_GPIO_AF_12 /*!< HRTIM1 Alternate Function mapping  */
#define HAL_GPIO_AF12_HRTIM1_CHA1          HAL_GPIO_AF_12 /*!< HRTIM1 Timer A Output 1            */
#define HAL_GPIO_AF12_HRTIM1_CHB2          HAL_GPIO_AF_12 /*!< HRTIM1 Timer B Output 2            */
#define HAL_GPIO_AF12_HRTIM1_EEV3          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 3            */
#define HAL_GPIO_AF12_HRTIM1_EEV4          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 4            */
#define HAL_GPIO_AF12_HRTIM1_EEV5          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 5            */
#define HAL_GPIO_AF12_HRTIM1_EEV6          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 6            */
#define HAL_GPIO_AF12_HRTIM1_EEV7          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 7            */
#define HAL_GPIO_AF12_HRTIM1_EEV9          HAL_GPIO_AF_12 /*!< HRTIM1 External Event 9            */
#define HAL_GPIO_AF12_HRTIM1_FLT1          HAL_GPIO_AF_12 /*!< HRTIM1 Fault 1                     */
#define HAL_GPIO_AF12_HRTIM1_FLT5          HAL_GPIO_AF_12 /*!< HRTIM1 Fault 5                     */
#define HAL_GPIO_AF12_HRTIM1_FLT6          HAL_GPIO_AF_12 /*!< HRTIM1 Fault 6                     */

/**
  * @brief   AF 13 selection
  */
#define HAL_GPIO_AF13_COMP1                HAL_GPIO_AF_13 /*!< COMP1 Alternate Function mapping   */
#define HAL_GPIO_AF13_COMP1_OUT            HAL_GPIO_AF_13 /*!< COMP1 Output channel               */
#define HAL_GPIO_AF13_COMP4                HAL_GPIO_AF_13 /*!< COMP4 Alternate Function mapping   */
#define HAL_GPIO_AF13_COMP4_OUT            HAL_GPIO_AF_13 /*!< COMP4 Output channel               */
#define HAL_GPIO_AF13_COMP7                HAL_GPIO_AF_13 /*!< COMP7 Alternate Function mapping   */
#define HAL_GPIO_AF13_COMP7_OUT            HAL_GPIO_AF_13 /*!< COMP7 Output channel               */
#define HAL_GPIO_AF13_FDCAN1               HAL_GPIO_AF_13 /*!< FDCAN1 Alternate Function mapping  */
#define HAL_GPIO_AF13_FDCAN1_RX            HAL_GPIO_AF_13 /*!< FDCAN1 Receive pin                 */
#define HAL_GPIO_AF13_FDCAN1_TX            HAL_GPIO_AF_13 /*!< FDCAN1 Transmit pin                */
#define HAL_GPIO_AF13_HRTIM1               HAL_GPIO_AF_13 /*!< HRTIM1 Alternate Function mapping  */
#define HAL_GPIO_AF13_HRTIM1_EEV5          HAL_GPIO_AF_13 /*!< HRTIM1 External Event 5            */
#define HAL_GPIO_AF13_HRTIM1_EEV11         HAL_GPIO_AF_13 /*!< HRTIM1 External Event 11           */
#define HAL_GPIO_AF13_HRTIM1_EEV12         HAL_GPIO_AF_13 /*!< HRTIM1 External Event 12           */
#define HAL_GPIO_AF13_HRTIM1_EEV15         HAL_GPIO_AF_13 /*!< HRTIM1 External Event 15           */
#define HAL_GPIO_AF13_HRTIM1_FLT3          HAL_GPIO_AF_13 /*!< HRTIM1 Fault 3                     */

/**
  * @brief   AF 14 selection
  */
#define HAL_GPIO_AF14_COMP2                HAL_GPIO_AF_14 /*!< COMP2 Alternate Function mapping   */
#define HAL_GPIO_AF14_COMP2_OUT            HAL_GPIO_AF_14 /*!< COMP2 Output channel               */
#define HAL_GPIO_AF14_COMP3                HAL_GPIO_AF_14 /*!< COMP3 Alternate Function mapping   */
#define HAL_GPIO_AF14_COMP3_OUT            HAL_GPIO_AF_14 /*!< COMP3 Output channel               */
#define HAL_GPIO_AF14_COMP5                HAL_GPIO_AF_14 /*!< COMP5 Alternate Function mapping   */
#define HAL_GPIO_AF14_COMP5_OUT            HAL_GPIO_AF_14 /*!< COMP5 Output channel               */
#define HAL_GPIO_AF14_COMP6                HAL_GPIO_AF_14 /*!< COMP6 Alternate Function mapping   */
#define HAL_GPIO_AF14_COMP6_OUT            HAL_GPIO_AF_14 /*!< COMP6 Output channel               */
#define HAL_GPIO_AF14_COMP8                HAL_GPIO_AF_14 /*!< COMP8 Alternate Function mapping   */
#define HAL_GPIO_AF14_COMP8_OUT            HAL_GPIO_AF_14 /*!< COMP8 Output channel               */
#define HAL_GPIO_AF14_TIM8                 HAL_GPIO_AF_14 /*!< TIM8 Alternate Function mapping    */
#define HAL_GPIO_AF14_TIM8_BKIN            HAL_GPIO_AF_14 /*!< TIM8 Break input                   */
#define HAL_GPIO_AF14_TIM8_CH1             HAL_GPIO_AF_14 /*!< TIM8 Multi-purpose Channel 1       */
#define HAL_GPIO_AF14_TIM8_CH3N            HAL_GPIO_AF_14 /*!< TIM8 CH3 complementary output      */
#define HAL_GPIO_AF14_TIM10                HAL_GPIO_AF_14 /*!< TIM10 Alternate Function mapping   */
#define HAL_GPIO_AF14_TIM10_CH1            HAL_GPIO_AF_14 /*!< TIM10 Multi-purpose Channel 1      */
#define HAL_GPIO_AF14_TIM12                HAL_GPIO_AF_14 /*!< TIM12 Alternate Function mapping   */
#define HAL_GPIO_AF14_TIM12_CH1            HAL_GPIO_AF_14 /*!< TIM12 Multi-purpose Channel 1      */
#define HAL_GPIO_AF14_TIM12_CH2            HAL_GPIO_AF_14 /*!< TIM12 Multi-purpose Channel 2      */
#define HAL_GPIO_AF14_TIM13                HAL_GPIO_AF_14 /*!< TIM13 Alternate Function mapping   */
#define HAL_GPIO_AF14_TIM13_CH1            HAL_GPIO_AF_14 /*!< TIM13 Multi-purpose Channel 1      */
#define HAL_GPIO_AF14_TIM15                HAL_GPIO_AF_14 /*!< TIM15 Alternate Function mapping   */
#define HAL_GPIO_AF14_TIM15_BKIN           HAL_GPIO_AF_14 /*!< TIM15 Break input                  */
#define HAL_GPIO_AF14_UART5                HAL_GPIO_AF_14 /*!< UART5 Alternate Function mapping   */
#define HAL_GPIO_AF14_UART5_CTS            HAL_GPIO_AF_14 /*!< UART5 Clear to send                */
#define HAL_GPIO_AF14_UART5_RTS            HAL_GPIO_AF_14 /*!< UART5 Request to send              */
#define HAL_GPIO_AF14_UART5_RX             HAL_GPIO_AF_14 /*!< UART5 Serial Data Receive Input    */
#define HAL_GPIO_AF14_UART5_TX             HAL_GPIO_AF_14 /*!< UART5 Transmit Data Output         */

/**
  * @brief   AF 15 selection
  */

#define HAL_GPIO_AF15_EVENTOUT             HAL_GPIO_AF_15 /*!< EVENTOUT Alternate Function mapping */
#endif /* STM32G5_DEVICE_ID */
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
GPIO_TypeDef *HAL_GPIO_GetLLInstance(hal_gpio_t gpiox);
/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions_Group3 GPIO attributes functions
  * @{
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_GPIO_SetSecAttr(hal_gpio_t gpiox, uint32_t pins, hal_gpio_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_gpio_sec_attr_t HAL_GPIO_GetSecAttr(hal_gpio_t gpiox, uint32_t pin);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* GPIOA || GPIOB || GPIOC || GPIOD || GPIOE || GPIOF || GPIOG || GPIOH */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_HAL_GPIO_H */
