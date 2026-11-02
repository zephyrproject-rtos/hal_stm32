/**
  *********************************************************************************************************************
  * @file    stm32h7pxx_hal_exti.h
  * @brief   Header file of EXTI HAL module.
  *********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *********************************************************************************************************************
  */

/* Define to prevent recursive inclusion ----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_HAL_EXTI_H
#define STM32H7PXX_HAL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_exti.h"
#include "stm32h7pxx_ll_sbs.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined (EXTI)

/** @defgroup EXTI EXTI
  * @{
  */

/* Exported types ---------------------------------------------------------------------------------------------------*/
/** @defgroup  EXTI_Exported_Types HAL EXTI Types
  * @{
  */

/*! EXTI Global State Machine */
typedef enum
{
  HAL_EXTI_STATE_RESET                   =  0U, /*!< Reset state */
  HAL_EXTI_STATE_INIT                    = (1U << 31U), /*!< EXTI initialized but not yet configured */
  HAL_EXTI_STATE_IDLE                    = (1U << 30U), /*!< EXTI initialized and configured */
  HAL_EXTI_STATE_ACTIVE                  = (1U << 29U)  /*!< EXTI initialized, configured and activated */
} hal_exti_state_t;

/*! EXTI Lines */
typedef enum
{
  HAL_EXTI_LINE_0                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x00U), /*!< EXTI Line 0 */
  HAL_EXTI_LINE_1                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x01U), /*!< EXTI Line 1 */
  HAL_EXTI_LINE_2                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x02U), /*!< EXTI Line 2 */
  HAL_EXTI_LINE_3                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR1 | 0x03U), /*!< EXTI Line 3 */
  HAL_EXTI_LINE_4                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x04U), /*!< EXTI Line 4 */
  HAL_EXTI_LINE_5                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x05U), /*!< EXTI Line 5 */
  HAL_EXTI_LINE_6                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x06U), /*!< EXTI Line 6 */
  HAL_EXTI_LINE_7                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR2 | 0x07U), /*!< EXTI Line 7 */
  HAL_EXTI_LINE_8                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x08U), /*!< EXTI Line 8 */
  HAL_EXTI_LINE_9                        = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x09U), /*!< EXTI Line 9 */
  HAL_EXTI_LINE_10                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x0AU), /*!< EXTI Line 10 */
  HAL_EXTI_LINE_11                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR3 | 0x0BU), /*!< EXTI Line 11 */
  HAL_EXTI_LINE_12                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0CU), /*!< EXTI Line 12 */
  HAL_EXTI_LINE_13                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0DU), /*!< EXTI Line 13 */
  HAL_EXTI_LINE_14                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0EU), /*!< EXTI Line 14 */
  HAL_EXTI_LINE_15                       = (LL_EXTI_GPIO     | LL_EXTI_REG1 | LL_EXTI_CR4 | 0x0FU), /*!< EXTI Line 15 */
  HAL_EXTI_LINE_16                       = (LL_EXTI_CONFIG | LL_EXTI_REG1 | 0x10U), /*!< EXTI Line 16 */
  HAL_EXTI_LINE_17                       = (LL_EXTI_CONFIG | LL_EXTI_REG1 | 0x11U), /*!< EXTI Line 17 */
  HAL_EXTI_LINE_18                       = (LL_EXTI_CONFIG | LL_EXTI_REG1 | 0x12U), /*!< EXTI Line 18 */
  HAL_EXTI_LINE_19                       = (LL_EXTI_CONFIG | LL_EXTI_REG1 | 0x13U), /*!< EXTI Line 19 */
  HAL_EXTI_LINE_20                       = (LL_EXTI_CONFIG | LL_EXTI_REG1 | 0x14U), /*!< EXTI Line 20 */
  HAL_EXTI_LINE_21                       = (LL_EXTI_CONFIG | LL_EXTI_REG1 | 0x15U), /*!< EXTI Line 21 */
  HAL_EXTI_LINE_22                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x16U), /*!< EXTI Line 22 */
  HAL_EXTI_LINE_23                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x17U), /*!< EXTI Line 23 */
  HAL_EXTI_LINE_24                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x18U), /*!< EXTI Line 24 */
  HAL_EXTI_LINE_25                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x19U), /*!< EXTI Line 25 */
  HAL_EXTI_LINE_26                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x1AU), /*!< EXTI Line 26 */
  HAL_EXTI_LINE_27                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x1BU), /*!< EXTI Line 27 */
  HAL_EXTI_LINE_28                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x1CU), /*!< EXTI Line 28 */
  HAL_EXTI_LINE_29                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x1DU), /*!< EXTI Line 29 */
  HAL_EXTI_LINE_30                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x1EU), /*!< EXTI Line 30 */
  HAL_EXTI_LINE_31                       = (LL_EXTI_DIRECT | LL_EXTI_REG1 | 0x1FU), /*!< EXTI Line 31 */
  HAL_EXTI_LINE_32                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x00U), /*!< EXTI Line 32 */
  HAL_EXTI_LINE_33                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x01U), /*!< EXTI Line 33 */
  HAL_EXTI_LINE_34                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x02U), /*!< EXTI Line 34 */
  HAL_EXTI_LINE_35                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x03U), /*!< EXTI Line 35 */
  HAL_EXTI_LINE_36                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x04U), /*!< EXTI Line 36 */
  HAL_EXTI_LINE_37                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x05U), /*!< EXTI Line 37 */
  HAL_EXTI_LINE_38                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x06U), /*!< EXTI Line 38 */
  HAL_EXTI_LINE_39                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x07U), /*!< EXTI Line 39 */
  HAL_EXTI_LINE_40                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x08U), /*!< EXTI Line 40 */
  HAL_EXTI_LINE_41                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x09U), /*!< EXTI Line 41 */
  HAL_EXTI_LINE_42                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x0AU), /*!< EXTI Line 42 */
  HAL_EXTI_LINE_43                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x0BU), /*!< EXTI Line 43 */
  HAL_EXTI_LINE_44                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x0CU), /*!< EXTI Line 44 */
  HAL_EXTI_LINE_45                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x0DU), /*!< EXTI Line 45 */
  HAL_EXTI_LINE_46                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x0EU), /*!< EXTI Line 46 */
  HAL_EXTI_LINE_47                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x0FU), /*!< EXTI Line 47 */
  HAL_EXTI_LINE_48                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x10U), /*!< EXTI Line 48 */
  HAL_EXTI_LINE_49                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x11U), /*!< EXTI Line 49 */
  HAL_EXTI_LINE_50                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x12U), /*!< EXTI Line 50 */
  HAL_EXTI_LINE_51                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x13U), /*!< EXTI Line 51 */
  HAL_EXTI_LINE_52                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x14U), /*!< EXTI Line 52 */
  HAL_EXTI_LINE_53                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x15U), /*!< EXTI Line 53 */
  HAL_EXTI_LINE_55                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x17U), /*!< EXTI Line 55 */
  HAL_EXTI_LINE_56                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x18U), /*!< EXTI Line 56 */
  HAL_EXTI_LINE_57                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x19U), /*!< EXTI Line 57 */
  HAL_EXTI_LINE_58                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x1AU), /*!< EXTI Line 58 */
  HAL_EXTI_LINE_59                       = (LL_EXTI_DIRECT | LL_EXTI_REG2 | 0x1BU), /*!< EXTI Line 59 */
  HAL_EXTI_LINE_60                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x1CU), /*!< EXTI Line 60 */
  HAL_EXTI_LINE_61                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x1DU), /*!< EXTI Line 61 */
  HAL_EXTI_LINE_62                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x1EU), /*!< EXTI Line 62 */
  HAL_EXTI_LINE_63                       = (LL_EXTI_CONFIG | LL_EXTI_REG2 | 0x1FU), /*!< EXTI Line 63 */
  HAL_EXTI_LINE_64                       = (LL_EXTI_DIRECT | LL_EXTI_REG3 | 0x00U), /*!< EXTI Line 64 */
  HAL_EXTI_LINE_65                       = (LL_EXTI_DIRECT | LL_EXTI_REG3 | 0x01U), /*!< EXTI Line 65 */
  HAL_EXTI_LINE_66                       = (LL_EXTI_DIRECT | LL_EXTI_REG3 | 0x02U), /*!< EXTI Line 66 */
  HAL_EXTI_LINE_67                       = (LL_EXTI_DIRECT | LL_EXTI_REG3 | 0x03U), /*!< EXTI Line 67 */
  HAL_EXTI_LINE_68                       = (LL_EXTI_CONFIG | LL_EXTI_REG3 | 0x04U), /*!< EXTI Line 68 */
  HAL_EXTI_LINE_69                       = (LL_EXTI_CONFIG | LL_EXTI_REG3 | 0x05U), /*!< EXTI Line 69 */
  HAL_EXTI_LINE_70                       = (LL_EXTI_CONFIG | LL_EXTI_REG3 | 0x06U), /*!< EXTI Line 70 */
  HAL_EXTI_LINE_71                       = (LL_EXTI_CONFIG | LL_EXTI_REG3 | 0x07U), /*!< EXTI Line 71 */
  HAL_EXTI_LINE_77                       = (LL_EXTI_DIRECT | LL_EXTI_REG3 | 0x0DU), /*!< EXTI Line 77 */
} hal_exti_line_t;

/*! EXTI Modes */
typedef enum
{
  HAL_EXTI_MODE_INTERRUPT                = LL_EXTI_MODE_IT,       /*!< Interrupt Mode */
  HAL_EXTI_MODE_EVENT                    = LL_EXTI_MODE_EVENT,    /*!< Event Mode */
  HAL_EXTI_MODE_INTERRUPT_EVENT          = LL_EXTI_MODE_IT_EVENT  /*!< Interrupt/Event Mode */
} hal_exti_mode_t;

/*! EXTI Triggers */
typedef enum
{
  HAL_EXTI_TRIGGER_NONE                  = LL_EXTI_TRIGGER_NONE,           /*!< No Trigger */
  HAL_EXTI_TRIGGER_RISING                = LL_EXTI_TRIGGER_RISING,         /*!< Rising Trigger */
  HAL_EXTI_TRIGGER_FALLING               = LL_EXTI_TRIGGER_FALLING,        /*!< Falling Trigger */
  HAL_EXTI_TRIGGER_RISING_FALLING        = LL_EXTI_TRIGGER_RISING_FALLING  /*!< Rising/Falling Trigger */
} hal_exti_trigger_t;

/*! EXTI GPIO Ports */
typedef enum
{
  HAL_EXTI_GPIOA                         = LL_SBS_EXTI_GPIO_PORTA, /*!< GPIO Port A */
  HAL_EXTI_GPIOB                         = LL_SBS_EXTI_GPIO_PORTB, /*!< GPIO Port B */
  HAL_EXTI_GPIOC                         = LL_SBS_EXTI_GPIO_PORTC, /*!< GPIO Port C */
  HAL_EXTI_GPIOD                         = LL_SBS_EXTI_GPIO_PORTD, /*!< GPIO Port D */
  HAL_EXTI_GPIOE                         = LL_SBS_EXTI_GPIO_PORTE, /*!< GPIO Port E */
  HAL_EXTI_GPIOF                         = LL_SBS_EXTI_GPIO_PORTF, /*!< GPIO Port F */
  HAL_EXTI_GPIOG                         = LL_SBS_EXTI_GPIO_PORTG, /*!< GPIO Port G */
  HAL_EXTI_GPIOH                         = LL_SBS_EXTI_GPIO_PORTH, /*!< GPIO Port H */
  HAL_EXTI_GPIOI                         = LL_SBS_EXTI_GPIO_PORTI, /*!< GPIO Port I */
} hal_exti_gpio_port_t;

typedef struct hal_exti_handle_s hal_exti_handle_t; /*!< EXTI handle structure type */

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
/*! Pointer to an EXTI callback function */
typedef void(*hal_exti_cb_t)(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger); /*!< EXTI callback function pointer definition */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

/*! EXTI handle structure definition */
struct hal_exti_handle_s /*! EXTI handle structure */
{
  hal_exti_line_t line; /*!< EXTI line */
  uint32_t ll_line;     /*!< Corresponding LL EXTI line */

  volatile hal_exti_state_t global_state; /*!< EXTI global state */
  volatile hal_exti_state_t prev_state;   /*!< Previous status of EXTI global state */

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
  hal_exti_cb_t p_trigger_cb;  /*!< EXTI trigger callback */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

#if defined (USE_HAL_EXTI_USER_DATA) && (USE_HAL_EXTI_USER_DATA == 1)
  const void *p_user_data; /*!< User data pointer */
#endif /* USE_HAL_EXTI_USER_DATA */
};

/*! EXTI Configuration structure definition */
typedef struct
{
  hal_exti_trigger_t trigger;     /*!< The EXTI Trigger edge to be configured */
  hal_exti_gpio_port_t gpio_port; /*!< The GPIO Port to be configured for the EXTI line */
} hal_exti_config_t;
/**
  * @}
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants HAL EXTI Constants
  * @{
  */

/** @defgroup EXTI_Lines_Aliases EXTI Lines Aliases for STM32H7Pxx series
  * @{
  */
#define HAL_EXTI_GPIO_0                  HAL_EXTI_LINE_0  /*!< EXTI GPIO Line 0 */
#define HAL_EXTI_GPIO_1                  HAL_EXTI_LINE_1  /*!< EXTI GPIO Line 1 */
#define HAL_EXTI_GPIO_2                  HAL_EXTI_LINE_2  /*!< EXTI GPIO Line 2 */
#define HAL_EXTI_GPIO_3                  HAL_EXTI_LINE_3  /*!< EXTI GPIO Line 3 */
#define HAL_EXTI_GPIO_4                  HAL_EXTI_LINE_4  /*!< EXTI GPIO Line 4 */
#define HAL_EXTI_GPIO_5                  HAL_EXTI_LINE_5  /*!< EXTI GPIO Line 5 */
#define HAL_EXTI_GPIO_6                  HAL_EXTI_LINE_6  /*!< EXTI GPIO Line 6 */
#define HAL_EXTI_GPIO_7                  HAL_EXTI_LINE_7  /*!< EXTI GPIO Line 7 */
#define HAL_EXTI_GPIO_8                  HAL_EXTI_LINE_8  /*!< EXTI GPIO Line 8 */
#define HAL_EXTI_GPIO_9                  HAL_EXTI_LINE_9  /*!< EXTI GPIO Line 9 */
#define HAL_EXTI_GPIO_10                 HAL_EXTI_LINE_10 /*!< EXTI GPIO Line 10 */
#define HAL_EXTI_GPIO_11                 HAL_EXTI_LINE_11 /*!< EXTI GPIO Line 11 */
#define HAL_EXTI_GPIO_12                 HAL_EXTI_LINE_12 /*!< EXTI GPIO Line 12 */
#define HAL_EXTI_GPIO_13                 HAL_EXTI_LINE_13 /*!< EXTI GPIO Line 13 */
#define HAL_EXTI_GPIO_14                 HAL_EXTI_LINE_14 /*!< EXTI GPIO Line 14 */
#define HAL_EXTI_GPIO_15                 HAL_EXTI_LINE_15 /*!< EXTI GPIO Line 15 */
#define HAL_EXTI_PVD_AVD                 HAL_EXTI_LINE_16 /*!< EXTI PVD and AVD Line */
#define HAL_EXTI_RTC_ALARM_SSRU          HAL_EXTI_LINE_17 /*!< EXTI RTC ALARM SSRU Line */
#define HAL_EXTI_RTC_TIMESTAMP           HAL_EXTI_LINE_18 /*!< EXTI RTC TIMESTAMP Line */
#define HAL_EXTI_RTC_WKUP_TIMER          HAL_EXTI_LINE_19 /*!< EXTI RTC wake-up timer Line */
#define HAL_EXTI_USB_OTG_FS_VBUS         HAL_EXTI_LINE_20 /*!< EXTI USB OTG VBUS_PLUG_UNPLUG Line */
#define HAL_EXTI_TAMP                    HAL_EXTI_LINE_21 /*!< EXTI TAMP Line */
#define HAL_EXTI_I2C1                    HAL_EXTI_LINE_22 /*!< EXTI I2C1 Line */
#define HAL_EXTI_I2C2                    HAL_EXTI_LINE_23 /*!< EXTI I2C2 Line*/
#define HAL_EXTI_I2C3                    HAL_EXTI_LINE_24 /*!< EXTI I2C3 Line */
#define HAL_EXTI_I3C1                    HAL_EXTI_LINE_25 /*!< EXTI I3C1 Line */
#define HAL_EXTI_USART1                  HAL_EXTI_LINE_26 /*!< EXTI USART1 Line */
#define HAL_EXTI_USART2                  HAL_EXTI_LINE_27 /*!< EXTI USART2 Line */
#define HAL_EXTI_USART3                  HAL_EXTI_LINE_28 /*!< EXTI USART3 Line */
#define HAL_EXTI_USART6                  HAL_EXTI_LINE_29 /*!< EXTI USART6 Line */
#define HAL_EXTI_UART4                   HAL_EXTI_LINE_30 /*!< EXTI UART4 Line */
#define HAL_EXTI_UART5                   HAL_EXTI_LINE_31 /*!< EXTI UART5 Line */
#define HAL_EXTI_UART7                   HAL_EXTI_LINE_32 /*!< EXTI UART7 Line */
#define HAL_EXTI_UART8                   HAL_EXTI_LINE_33 /*!< EXTI UART8 Line */
#define HAL_EXTI_ADF                     HAL_EXTI_LINE_34 /*!< EXTI ADF Line */
#define HAL_EXTI_LPUART1                 HAL_EXTI_LINE_35 /*!< EXTI LPUART1 Line */
#define HAL_EXTI_SPI1                    HAL_EXTI_LINE_36 /*!< EXTI SPI1 Line */
#define HAL_EXTI_SPI2                    HAL_EXTI_LINE_37 /*!< EXTI SPI2 Line */
#define HAL_EXTI_SPI3                    HAL_EXTI_LINE_38 /*!< EXTI SPI3 Line */
#define HAL_EXTI_SPI4                    HAL_EXTI_LINE_39 /*!< EXTI SPI4 Line */
#define HAL_EXTI_SPI5                    HAL_EXTI_LINE_40 /*!< EXTI SPI5 Line */
#define HAL_EXTI_SPI6                    HAL_EXTI_LINE_41 /*!< EXTI SPI6 Line */
#define HAL_EXTI_UART9                   HAL_EXTI_LINE_42 /*!< EXTI UART9 Line */
#define HAL_EXTI_USB_OTG_FS_WKUP         HAL_EXTI_LINE_43 /*!< EXTI USB_OTG_FS wake-up Line */
#define HAL_EXTI_USART10                 HAL_EXTI_LINE_44 /*!< EXTI USART10 Line */
#define HAL_EXTI_UCPD                    HAL_EXTI_LINE_45 /*!< EXTI UCPD Line */
#define HAL_EXTI_RCC_LSECSS              HAL_EXTI_LINE_46 /*!< EXTI RCC LSECSS Line */
#define HAL_EXTI_LPTIM1                  HAL_EXTI_LINE_47 /*!< EXTI LPTIM1 Line */
#define HAL_EXTI_LPTIM2                  HAL_EXTI_LINE_48 /*!< EXTI LPTIM2 Line */
#define HAL_EXTI_LPTIM2_CH1              HAL_EXTI_LINE_49 /*!< EXTI LPTIM2 CH1 Line */
#define HAL_EXTI_LPTIM3                  HAL_EXTI_LINE_50 /*!< EXTI LPTIM3 Line */
#define HAL_EXTI_LPTIM3_CH1              HAL_EXTI_LINE_51 /*!< EXTI LPTIM3 CH1 Line */
#define HAL_EXTI_LPTIM4                  HAL_EXTI_LINE_52 /*!< EXTI LPTIM4 Line */
#define HAL_EXTI_LPTIM5                  HAL_EXTI_LINE_53 /*!< EXTI LPTIM5 Line */
#define HAL_EXTI_WKUP1                   HAL_EXTI_LINE_55 /*!< EXTI wake-up 1 Line */
#define HAL_EXTI_WKUP2                   HAL_EXTI_LINE_56 /*!< EXTI wake-up 2 Line */
#define HAL_EXTI_WKUP3                   HAL_EXTI_LINE_57 /*!< EXTI wake-up 3 Line */
#define HAL_EXTI_WKUP4                   HAL_EXTI_LINE_58 /*!< EXTI wake-up 4 Line */
#define HAL_EXTI_IWDG                    HAL_EXTI_LINE_59 /*!< EXTI IWDG Line */
#define HAL_EXTI_COMP1                   HAL_EXTI_LINE_60 /*!< EXTI COMP1 Line */
#define HAL_EXTI_COMP2                   HAL_EXTI_LINE_61 /*!< EXTI COMP2 Line */
#define HAL_EXTI_COMP3                   HAL_EXTI_LINE_62 /*!< EXTI COMP3 Line */
#define HAL_EXTI_COMP4                   HAL_EXTI_LINE_63 /*!< EXTI COMP4 Line */
#define HAL_EXTI_WKUP5                   HAL_EXTI_LINE_64 /*!< EXTI wake-up 5 Line */
#define HAL_EXTI_WKUP6                   HAL_EXTI_LINE_65 /*!< EXTI wake-up 6 Line */
#define HAL_EXTI_WKUP7                   HAL_EXTI_LINE_66 /*!< EXTI wake-up 7 Line */
#define HAL_EXTI_WKUP8                   HAL_EXTI_LINE_67 /*!< EXTI wake-up 8 Line */
#define HAL_EXTI_COMP5                   HAL_EXTI_LINE_68 /*!< EXTI COMP5 Line */
#define HAL_EXTI_COMP6                   HAL_EXTI_LINE_69 /*!< EXTI COMP6 Line */
#define HAL_EXTI_COMP7                   HAL_EXTI_LINE_70 /*!< EXTI COMP7 Line */
#define HAL_EXTI_COMP8                   HAL_EXTI_LINE_71 /*!< EXTI COMP8 Line */
#define HAL_EXTI_DTS                     HAL_EXTI_LINE_77 /*!< EXTI DTS Line */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions HAL EXTI Functions
  * @{
  */

/** @defgroup EXTI_Exported_Functions_Group1 Initialization/De-initialization and configuration functions
  * @{
  */
hal_status_t HAL_EXTI_Init(hal_exti_handle_t *hexti, hal_exti_line_t line);
void HAL_EXTI_DeInit(hal_exti_handle_t *hexti);
hal_status_t HAL_EXTI_SetConfig(hal_exti_handle_t *hexti, const hal_exti_config_t *p_exti_config);
void HAL_EXTI_GetConfig(const hal_exti_handle_t *hexti, hal_exti_config_t *p_exti_config);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group2 I/O operation functions
  * @{
  */
hal_status_t HAL_EXTI_Enable(hal_exti_handle_t *hexti, hal_exti_mode_t mode);
hal_status_t HAL_EXTI_Disable(hal_exti_handle_t *hexti);
hal_status_t HAL_EXTI_GenerateSWI(hal_exti_handle_t *hexti);
hal_exti_trigger_t HAL_EXTI_GetPending(const hal_exti_handle_t *hexti);
void HAL_EXTI_ClearPending(const hal_exti_handle_t *hexti, hal_exti_trigger_t edge);
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group3 IRQHandler and callback functions
  * @{
  */
void HAL_EXTI_IRQHandler(hal_exti_handle_t *hexti);

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
hal_status_t HAL_EXTI_RegisterTriggerCallback(hal_exti_handle_t *hexti, hal_exti_cb_t p_exti_cb);
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

void HAL_EXTI_TriggerCallback(hal_exti_handle_t *hexti, hal_exti_trigger_t trigger);

#if defined (USE_HAL_EXTI_USER_DATA) && (USE_HAL_EXTI_USER_DATA == 1)
void HAL_EXTI_SetUserData(hal_exti_handle_t *hexti, const void *p_user_data);
const void *HAL_EXTI_GetUserData(const hal_exti_handle_t *hexti);
#endif /* USE_HAL_EXTI_USER_DATA */
/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group4 EXTI state and info functions
  * @{
  */
hal_exti_state_t HAL_EXTI_GetState(const hal_exti_handle_t *hexti);

hal_exti_line_t HAL_EXTI_GetInstance(const hal_exti_handle_t *hexti);
uint32_t HAL_EXTI_GetLLInstance(const hal_exti_handle_t *hexti);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* EXTI */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_HAL_EXTI_H */
