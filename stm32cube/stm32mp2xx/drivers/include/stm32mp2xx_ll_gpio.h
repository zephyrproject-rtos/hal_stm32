/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_gpio.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO LL module.
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
#ifndef __STM32MP2xx_LL_GPIO_H
#define __STM32MP2xx_LL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if (                                                                                 \
      (defined(CORE_CM33) || defined(CORE_CA35))                                      \
      &&                                                                              \
      (                                                                               \
        defined (GPIOA) || defined (GPIOB) || defined (GPIOC) || defined (GPIOD) ||   \
        defined (GPIOE) || defined (GPIOF) || defined (GPIOG) || defined (GPIOH) ||   \
        defined (GPIOI) || defined (GPIOJ) || defined (GPIOK) || defined (GPIOZ)      \
      )                                                                               \
    )                                                                                 \
    ||                                                                                \
    (defined(CORE_CM0PLUS) && defined(GPIOZ))

/** @defgroup GPIO_LL GPIO
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __GPIO_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup GPIO_LL_Private_Macros GPIO Private Macros
  * @{
  */

/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup GPIO_LL_ES_INIT GPIO Exported Init structures
  * @{
  */

/**
  * @brief LL GPIO Init Structure definition
  */
typedef struct
{
  uint32_t Pin;          /*!< Specifies the GPIO pins to be configured.
                              This parameter can be any value of @ref GPIO_LL_EC_PIN */

  uint32_t Mode;         /*!< Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref GPIO_LL_EC_MODE.

                              GPIO HW configuration can be modified afterwards using
                              unitary function @ref LL_GPIO_SetPinMode().*/

  uint32_t Speed;        /*!< Specifies the speed for the selected pins.
                              This parameter can be a value of @ref GPIO_LL_EC_SPEED.

                              GPIO HW configuration can be modified afterwards using
                              unitary function @ref LL_GPIO_SetPinSpeed().*/

  uint32_t OutputType;   /*!< Specifies the operating output type for the selected pins.
                              This parameter can be a value of @ref GPIO_LL_EC_OUTPUT.

                              GPIO HW configuration can be modified afterwards using
                              unitary function @ref LL_GPIO_SetPinOutputType().*/

  uint32_t Pull;         /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                              This parameter can be a value of @ref GPIO_LL_EC_PULL.

                              GPIO HW configuration can be modified afterwards using
                              unitary function @ref LL_GPIO_SetPinPull().*/

  uint32_t Alternate;    /*!< Specifies the Peripheral to be connected to the selected pins.
                              This parameter can be a value of @ref GPIO_LL_EC_AF.

                              GPIO HW configuration can be modified afterwards using
                              unitary function @ref LL_GPIO_SetAFPin_0_7() and LL_GPIO_SetAFPin_8_15().*/
} LL_GPIO_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Constants GPIO Exported Constants
  * @{
  */

/** @defgroup GPIO_LL_EC_PIN PIN
  * @{
  */
#define LL_GPIO_PIN_0                      GPIO_BSRR_BS0 /*!< Select pin 0 */
#define LL_GPIO_PIN_1                      GPIO_BSRR_BS1 /*!< Select pin 1 */
#define LL_GPIO_PIN_2                      GPIO_BSRR_BS2 /*!< Select pin 2 */
#define LL_GPIO_PIN_3                      GPIO_BSRR_BS3 /*!< Select pin 3 */
#define LL_GPIO_PIN_4                      GPIO_BSRR_BS4 /*!< Select pin 4 */
#define LL_GPIO_PIN_5                      GPIO_BSRR_BS5 /*!< Select pin 5 */
#define LL_GPIO_PIN_6                      GPIO_BSRR_BS6 /*!< Select pin 6 */
#define LL_GPIO_PIN_7                      GPIO_BSRR_BS7 /*!< Select pin 7 */
#define LL_GPIO_PIN_8                      GPIO_BSRR_BS8 /*!< Select pin 8 */
#define LL_GPIO_PIN_9                      GPIO_BSRR_BS9 /*!< Select pin 9 */
#define LL_GPIO_PIN_10                     GPIO_BSRR_BS10 /*!< Select pin 10 */
#define LL_GPIO_PIN_11                     GPIO_BSRR_BS11 /*!< Select pin 11 */
#define LL_GPIO_PIN_12                     GPIO_BSRR_BS12 /*!< Select pin 12 */
#define LL_GPIO_PIN_13                     GPIO_BSRR_BS13 /*!< Select pin 13 */
#define LL_GPIO_PIN_14                     GPIO_BSRR_BS14 /*!< Select pin 14 */
#define LL_GPIO_PIN_15                     GPIO_BSRR_BS15 /*!< Select pin 15 */
#define LL_GPIO_PIN_ALL                    (LL_GPIO_PIN_0 | LL_GPIO_PIN_1  | LL_GPIO_PIN_2  | \
                                            LL_GPIO_PIN_3  | LL_GPIO_PIN_4  | LL_GPIO_PIN_5  | \
                                            LL_GPIO_PIN_6  | LL_GPIO_PIN_7  | LL_GPIO_PIN_8  | \
                                            LL_GPIO_PIN_9  | LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | \
                                            LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14 | \
                                            LL_GPIO_PIN_15) /*!< Select all pins */
/**
  * @}
  */

/** @defgroup GPIO_LL_EC_MODE Mode
  * @{
  */
#define LL_GPIO_MODE_INPUT                 (0x0U << GPIO_MODER_MODE0_Pos) /*!< Select input mode */
#define LL_GPIO_MODE_OUTPUT                (0x1U << GPIO_MODER_MODE0_Pos) /*!< Select output mode */
#define LL_GPIO_MODE_ALTERNATE             (0x2U << GPIO_MODER_MODE0_Pos) /*!< Select alternate function mode */
#define LL_GPIO_MODE_ANALOG                (0x3U << GPIO_MODER_MODE0_Pos) /*!< Select analog mode */
/**
  * @}
  */

/** @defgroup GPIO_LL_EC_OUTPUT Output Type
  * @{
  */
#define LL_GPIO_OUTPUT_PUSHPULL            (0x00000000U) /*!< Select push-pull as output type */
#define LL_GPIO_OUTPUT_OPENDRAIN           GPIO_OTYPER_OT0 /*!< Select open-drain as output type */
/**
  * @}
  */

/** @defgroup GPIO_LL_EC_SPEED Output Speed
  * @{
  */
#define LL_GPIO_SPEED_FREQ_LOW             (0x0U << GPIO_OSPEEDR_OSPEED0_Pos) /*!< Select I/O low output speed    */
#define LL_GPIO_SPEED_FREQ_MEDIUM          (0x1U << GPIO_OSPEEDR_OSPEED0_Pos) /*!< Select I/O medium output speed */
#define LL_GPIO_SPEED_FREQ_HIGH            (0x2U << GPIO_OSPEEDR_OSPEED0_Pos) /*!< Select I/O fast output speed   */
#define LL_GPIO_SPEED_FREQ_VERY_HIGH       (0x3U << GPIO_OSPEEDR_OSPEED0_Pos)   /*!< Select I/O high output speed   */
/**
  * @}
  */
#define LL_GPIO_SPEED_LOW                  LL_GPIO_SPEED_FREQ_LOW
#define LL_GPIO_SPEED_MEDIUM               LL_GPIO_SPEED_FREQ_MEDIUM
#define LL_GPIO_SPEED_FAST                 LL_GPIO_SPEED_FREQ_HIGH
#define LL_GPIO_SPEED_HIGH                 LL_GPIO_SPEED_FREQ_VERY_HIGH

/** @defgroup GPIO_LL_EC_PULL Pull Up Pull Down
  * @{
  */
#define LL_GPIO_PULL_NO                    (0x0U << GPIO_PUPDR_PUPD0_Pos) /*!< Select I/O no pull */
#define LL_GPIO_PULL_UP                    (0x1U << GPIO_PUPDR_PUPD0_Pos) /*!< Select I/O pull up */
#define LL_GPIO_PULL_DOWN                  (0x2U << GPIO_PUPDR_PUPD0_Pos) /*!< Select I/O pull down */
/**
  * @}
  */

/** @defgroup GPIO_LL_EC_AF Alternate Function
  * @{
  */
#define LL_GPIO_AF_0                       (0x0000000U) /*!< Select alternate function 0 */
#define LL_GPIO_AF_1                       (0x0000001U) /*!< Select alternate function 1 */
#define LL_GPIO_AF_2                       (0x0000002U) /*!< Select alternate function 2 */
#define LL_GPIO_AF_3                       (0x0000003U) /*!< Select alternate function 3 */
#define LL_GPIO_AF_4                       (0x0000004U) /*!< Select alternate function 4 */
#define LL_GPIO_AF_5                       (0x0000005U) /*!< Select alternate function 5 */
#define LL_GPIO_AF_6                       (0x0000006U) /*!< Select alternate function 6 */
#define LL_GPIO_AF_7                       (0x0000007U) /*!< Select alternate function 7 */
#define LL_GPIO_AF_8                       (0x0000008U) /*!< Select alternate function 8 */
#define LL_GPIO_AF_9                       (0x0000009U) /*!< Select alternate function 9 */
#define LL_GPIO_AF_10                      (0x000000AU) /*!< Select alternate function 10 */
#define LL_GPIO_AF_11                      (0x000000BU) /*!< Select alternate function 11 */
#define LL_GPIO_AF_12                      (0x000000CU) /*!< Select alternate function 12 */
#define LL_GPIO_AF_13                      (0x000000DU) /*!< Select alternate function 13 */
#define LL_GPIO_AF_14                      (0x000000EU) /*!< Select alternate function 14 */
#define LL_GPIO_AF_15                      (0x000000FU) /*!< Select alternate function 15 */
/**
  * @}
  */

/** @defgroup GPIO_LL_EC_DELAY Delay
  * @{
  */
#define LL_GPIO_DELAY_0                       (0x0000000U) /*!< Select no delay */
#define LL_GPIO_DELAY_300                     (0x0000001U) /*!< Select 0.3 ns   */
#define LL_GPIO_DELAY_500                     (0x0000002U) /*!< Select 0.5 ns   */
#define LL_GPIO_DELAY_750                     (0x0000003U) /*!< Select 0.75 ns  */
#define LL_GPIO_DELAY_1000                    (0x0000004U) /*!< Select 1 ns     */
#define LL_GPIO_DELAY_1250                    (0x0000005U) /*!< Select 1.25 ns  */
#define LL_GPIO_DELAY_1500                    (0x0000006U) /*!< Select 1.5 ns   */
#define LL_GPIO_DELAY_1750                    (0x0000007U) /*!< Select 1.75 ns  */
#define LL_GPIO_DELAY_2000                    (0x0000008U) /*!< Select 2 ns     */
#define LL_GPIO_DELAY_2250                    (0x0000009U) /*!< Select 2.25 ns  */
#define LL_GPIO_DELAY_2500                    (0x000000AU) /*!< Select 2.5 ns   */
#define LL_GPIO_DELAY_2750                    (0x000000BU) /*!< Select 2.75 ns  */
#define LL_GPIO_DELAY_3000                    (0x000000CU) /*!< Select 3 ns     */
#define LL_GPIO_DELAY_3250                    (0x000000DU) /*!< Select 3.25 ns  */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Macros GPIO Exported Macros
  * @{
  */

/** @defgroup GPIO_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in GPIO register
  * @param  __INSTANCE__ GPIO Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_GPIO_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in GPIO register
  * @param  __INSTANCE__ GPIO Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_GPIO_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup GPIO_LL_Exported_Functions GPIO Exported Functions
  * @{
  */

/** @defgroup GPIO_LL_EF_Port_Configuration Port Configuration
  * @{
  */

/**
  * @brief  Configure gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         LL_GPIO_SetPinMode
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_MODE_INPUT
  *         @arg @ref LL_GPIO_MODE_OUTPUT
  *         @arg @ref LL_GPIO_MODE_ALTERNATE
  *         @arg @ref LL_GPIO_MODE_ANALOG
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
  MODIFY_REG(GPIOx->MODER, (GPIO_MODER_MODE0 << (POSITION_VAL(Pin) * GPIO_MODER_MODE1_Pos)),
             (Mode << (POSITION_VAL(Pin) * GPIO_MODER_MODE1_Pos)));
}

/**
  * @brief  Return gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         LL_GPIO_GetPinMode
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_MODE_INPUT
  *         @arg @ref LL_GPIO_MODE_OUTPUT
  *         @arg @ref LL_GPIO_MODE_ALTERNATE
  *         @arg @ref LL_GPIO_MODE_ANALOG
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinMode(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->MODER, ((uint32_t)GPIO_MODER_MODE0 << (POSITION_VAL(Pin) * GPIO_MODER_MODE1_Pos)))
                    >> (POSITION_VAL(Pin) * GPIO_MODER_MODE1_Pos));
}

/**
  * @brief  Configure gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @rmtoll OTYPER       OTy           LL_GPIO_SetPinOutputType
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @param  OutputType This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref LL_GPIO_OUTPUT_OPENDRAIN
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t PinMask, uint32_t OutputType)
{
  MODIFY_REG(GPIOx->OTYPER, PinMask, (PinMask * OutputType));
}

/**
  * @brief  Return gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll OTYPER       OTy           LL_GPIO_GetPinOutputType
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_OUTPUT_PUSHPULL
  *         @arg @ref LL_GPIO_OUTPUT_OPENDRAIN
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinOutputType(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->OTYPER, Pin) >> POSITION_VAL(Pin));
}

/**
  * @brief  Configure gpio speed for a dedicated pin on dedicated port.
  * @note   I/O speed can be Low, Medium, Fast or High speed.
  * @note   Warning: only one pin can be passed as parameter.
  * @note   Refer to datasheet for frequency specifications and the power
  *         supply and load conditions for each speed.
  * @rmtoll OSPEEDR      OSPEEDy       LL_GPIO_SetPinSpeed
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @param  Speed This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_SPEED_FREQ_LOW
  *         @arg @ref LL_GPIO_SPEED_FREQ_MEDIUM
  *         @arg @ref LL_GPIO_SPEED_FREQ_HIGH
  *         @arg @ref LL_GPIO_SPEED_FREQ_VERY_HIGH
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t  Speed)
{
  MODIFY_REG(GPIOx->OSPEEDR, (GPIO_OSPEEDR_OSPEED0 << (POSITION_VAL(Pin) * GPIO_OSPEEDR_OSPEED1_Pos)),
             (Speed << (POSITION_VAL(Pin) * GPIO_OSPEEDR_OSPEED1_Pos)));
}

/**
  * @brief  Return gpio speed for a dedicated pin on dedicated port.
  * @note   I/O speed can be Low, Medium, Fast or High speed.
  * @note   Warning: only one pin can be passed as parameter.
  * @note   Refer to datasheet for frequency specifications and the power
  *         supply and load conditions for each speed.
  * @rmtoll OSPEEDR      OSPEEDy       LL_GPIO_GetPinSpeed
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_SPEED_FREQ_LOW
  *         @arg @ref LL_GPIO_SPEED_FREQ_MEDIUM
  *         @arg @ref LL_GPIO_SPEED_FREQ_HIGH
  *         @arg @ref LL_GPIO_SPEED_FREQ_VERY_HIGH
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinSpeed(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->OSPEEDR,
                             ((uint32_t)GPIO_OSPEEDR_OSPEED0 << (POSITION_VAL(Pin) * GPIO_OSPEEDR_OSPEED1_Pos))
                            )
                    >> (POSITION_VAL(Pin) * GPIO_OSPEEDR_OSPEED1_Pos)
                   );
}

/**
  * @brief  Configure gpio pull-up or pull-down for a dedicated pin on a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll PUPDR        PUPDy         LL_GPIO_SetPinPull
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @param  Pull This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PULL_NO
  *         @arg @ref LL_GPIO_PULL_UP
  *         @arg @ref LL_GPIO_PULL_DOWN
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull)
{
  MODIFY_REG(GPIOx->PUPDR, (GPIO_PUPDR_PUPD0 << (POSITION_VAL(Pin) * GPIO_PUPDR_PUPD1_Pos)),
             (Pull << (POSITION_VAL(Pin) * GPIO_PUPDR_PUPD1_Pos)));
}

/**
  * @brief  Return gpio pull-up or pull-down for a dedicated pin on a dedicated port
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll PUPDR        PUPDy         LL_GPIO_GetPinPull
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_PULL_NO
  *         @arg @ref LL_GPIO_PULL_UP
  *         @arg @ref LL_GPIO_PULL_DOWN
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinPull(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->PUPDR, ((uint32_t)GPIO_PUPDR_PUPD0 << (POSITION_VAL(Pin) * GPIO_PUPDR_PUPD1_Pos)))
                    >> (POSITION_VAL(Pin) * GPIO_PUPDR_PUPD1_Pos));
}

/**
  * @brief  Configure gpio alternate function of a dedicated pin from 0 to 7 for a dedicated port.
  * @note   Possible values are from AF0 to AF15 depending on target.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll AFRL         AFSELy        LL_GPIO_SetAFPin_0_7
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  * @param  Alternate This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_AF_0
  *         @arg @ref LL_GPIO_AF_1
  *         @arg @ref LL_GPIO_AF_2
  *         @arg @ref LL_GPIO_AF_3
  *         @arg @ref LL_GPIO_AF_4
  *         @arg @ref LL_GPIO_AF_5
  *         @arg @ref LL_GPIO_AF_6
  *         @arg @ref LL_GPIO_AF_7
  *         @arg @ref LL_GPIO_AF_8
  *         @arg @ref LL_GPIO_AF_9
  *         @arg @ref LL_GPIO_AF_10
  *         @arg @ref LL_GPIO_AF_11
  *         @arg @ref LL_GPIO_AF_12
  *         @arg @ref LL_GPIO_AF_13
  *         @arg @ref LL_GPIO_AF_14
  *         @arg @ref LL_GPIO_AF_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetAFPin_0_7(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate)
{
  MODIFY_REG(GPIOx->AFR[0], (GPIO_AFRL_AFSEL0 << (POSITION_VAL(Pin) * GPIO_AFRL_AFSEL1_Pos)),
             (Alternate << (POSITION_VAL(Pin) * GPIO_AFRL_AFSEL1_Pos)));
}

/**
  * @brief  Return gpio alternate function of a dedicated pin from 0 to 7 for a dedicated port.
  * @rmtoll AFRL         AFSELy        LL_GPIO_GetAFPin_0_7
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_AF_0
  *         @arg @ref LL_GPIO_AF_1
  *         @arg @ref LL_GPIO_AF_2
  *         @arg @ref LL_GPIO_AF_3
  *         @arg @ref LL_GPIO_AF_4
  *         @arg @ref LL_GPIO_AF_5
  *         @arg @ref LL_GPIO_AF_6
  *         @arg @ref LL_GPIO_AF_7
  *         @arg @ref LL_GPIO_AF_8
  *         @arg @ref LL_GPIO_AF_9
  *         @arg @ref LL_GPIO_AF_10
  *         @arg @ref LL_GPIO_AF_11
  *         @arg @ref LL_GPIO_AF_12
  *         @arg @ref LL_GPIO_AF_13
  *         @arg @ref LL_GPIO_AF_14
  *         @arg @ref LL_GPIO_AF_15
  */
__STATIC_INLINE uint32_t LL_GPIO_GetAFPin_0_7(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->AFR[0], ((uint32_t)GPIO_AFRL_AFSEL0 << (POSITION_VAL(Pin) * GPIO_AFRL_AFSEL1_Pos)))
                    >> (POSITION_VAL(Pin) * GPIO_AFRL_AFSEL1_Pos));
}

/**
  * @brief  Configure gpio alternate function of a dedicated pin from 8 to 15 for a dedicated port.
  * @note   Possible values are from AF0 to AF15 depending on target.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll AFRH         AFSELy        LL_GPIO_SetAFPin_8_15
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @param  Alternate This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_AF_0
  *         @arg @ref LL_GPIO_AF_1
  *         @arg @ref LL_GPIO_AF_2
  *         @arg @ref LL_GPIO_AF_3
  *         @arg @ref LL_GPIO_AF_4
  *         @arg @ref LL_GPIO_AF_5
  *         @arg @ref LL_GPIO_AF_6
  *         @arg @ref LL_GPIO_AF_7
  *         @arg @ref LL_GPIO_AF_8
  *         @arg @ref LL_GPIO_AF_9
  *         @arg @ref LL_GPIO_AF_10
  *         @arg @ref LL_GPIO_AF_11
  *         @arg @ref LL_GPIO_AF_12
  *         @arg @ref LL_GPIO_AF_13
  *         @arg @ref LL_GPIO_AF_14
  *         @arg @ref LL_GPIO_AF_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetAFPin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate)
{
  MODIFY_REG(GPIOx->AFR[1], (GPIO_AFRH_AFSEL8 << (POSITION_VAL(Pin >> 8U) * GPIO_AFRH_AFSEL9_Pos)),
             (Alternate << (POSITION_VAL(Pin >> 8U) * GPIO_AFRH_AFSEL9_Pos)));
}

/**
  * @brief  Return gpio alternate function of a dedicated pin from 8 to 15 for a dedicated port.
  * @note   Possible values are from AF0 to AF15 depending on target.
  * @rmtoll AFRH         AFSELy        LL_GPIO_GetAFPin_8_15
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_AF_0
  *         @arg @ref LL_GPIO_AF_1
  *         @arg @ref LL_GPIO_AF_2
  *         @arg @ref LL_GPIO_AF_3
  *         @arg @ref LL_GPIO_AF_4
  *         @arg @ref LL_GPIO_AF_5
  *         @arg @ref LL_GPIO_AF_6
  *         @arg @ref LL_GPIO_AF_7
  *         @arg @ref LL_GPIO_AF_8
  *         @arg @ref LL_GPIO_AF_9
  *         @arg @ref LL_GPIO_AF_10
  *         @arg @ref LL_GPIO_AF_11
  *         @arg @ref LL_GPIO_AF_12
  *         @arg @ref LL_GPIO_AF_13
  *         @arg @ref LL_GPIO_AF_14
  *         @arg @ref LL_GPIO_AF_15
  */
__STATIC_INLINE uint32_t LL_GPIO_GetAFPin_8_15(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->AFR[1],
                             ((uint32_t)GPIO_AFRH_AFSEL8 << (POSITION_VAL(Pin >> 8U) * GPIO_AFRH_AFSEL9_Pos))
                            )
                    >> (POSITION_VAL(Pin >> 8U) * GPIO_AFRH_AFSEL9_Pos)
                   );
}


/**
  * @brief  Lock configuration of several pins for a dedicated port.
  * @note   When the lock sequence has been applied on a port bit, the
  *         value of this port bit can no longer be modified until the
  *         next reset.
  * @note   Each lock bit freezes a specific configuration register
  *         (control and alternate function registers).
  * @rmtoll LCKR         LCKK          LL_GPIO_LockPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  __IO uint32_t temp;
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | PinMask);
  WRITE_REG(GPIOx->LCKR, PinMask);
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | PinMask);
  /* Read LCKK register. This read is mandatory to complete key lock sequence */
  temp = READ_REG(GPIOx->LCKR);
  (void) temp;
}

/**
  * @brief  Return 1 if all pins passed as parameter, of a dedicated port, are locked. else Return 0.
  * @rmtoll LCKR         LCKy          LL_GPIO_IsPinLocked
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsPinLocked(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return ((READ_BIT(GPIOx->LCKR, PinMask) == (PinMask)) ? 1UL : 0UL);
}

/**
  * @brief  Return 1 if one of the pin of a dedicated port is locked. else return 0.
  * @rmtoll LCKR         LCKK          LL_GPIO_IsAnyPinLocked
  * @param  GPIOx GPIO Port
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsAnyPinLocked(const GPIO_TypeDef *GPIOx)
{
  return ((READ_BIT(GPIOx->LCKR, GPIO_LCKR_LCKK) == (GPIO_LCKR_LCKK)) ? 1UL : 0UL);
}

/**
  * @brief  Lock resource configuration of several pins for a dedicated port.
  * @note   When the lock sequence has been applied on a port bit, the
  *         value of this port bit can no longer be modified until the
  *         next reset.
  * @note   Each lock bit freezes a security configuration register
  *         (control and alternate function registers).
  * @rmtoll LCKR         LCKK          LL_GPIO_LockPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_LockResourcePin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  MODIFY_REG(GPIOx->RCFGLOCKR, 0U, PinMask);
}

/**
  * @brief  Return 1 if all resource pins passed as parameter, of a dedicated port, are locked. else Return 0.
  * @rmtoll LCKR         LCKy          LL_GPIO_IsPinLocked
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsResourcePinLocked(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return ((READ_BIT(GPIOx->RCFGLOCKR, PinMask) == (PinMask)) ? 1UL : 0UL);
}

/**
  * @brief  Return 1 if one of the resource pin of a dedicated port is locked. else return 0.
  * @rmtoll LCKR         LCKK          LL_GPIO_IsAnyPinLocked
  * @param  GPIOx GPIO Port
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsAnyResourcePinLocked(const GPIO_TypeDef *GPIOx)
{
  return ((READ_BIT(GPIOx->RCFGLOCKR, GPIO_LCKR_LCKK) == (GPIO_LCKR_LCKK)) ? 1UL : 0UL);
}

/**
  * @}
  */

/**
  * @brief  Configure gpio delay of a dedicated pin from 0 to 7 for a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  * @param  Delay This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_DELAY_0
  *         @arg @ref LL_GPIO_DELAY_300
  *         @arg @ref LL_GPIO_DELAY_500
  *         @arg @ref LL_GPIO_DELAY_750
  *         @arg @ref LL_GPIO_DELAY_1000
  *         @arg @ref LL_GPIO_DELAY_1250
  *         @arg @ref LL_GPIO_DELAY_1500
  *         @arg @ref LL_GPIO_DELAY_1750
  *         @arg @ref LL_GPIO_DELAY_2000
  *         @arg @ref LL_GPIO_DELAY_2250
  *         @arg @ref LL_GPIO_DELAY_2500
  *         @arg @ref LL_GPIO_DELAY_2750
  *         @arg @ref LL_GPIO_DELAY_3000
  *         @arg @ref LL_GPIO_DELAY_3250
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetDelayPin_0_7(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Delay)
{
  MODIFY_REG(GPIOx->DELAYRL,
             (GPIO_DELAYRL_DLY0 << (POSITION_VAL(Pin) * GPIO_DELAYRL_DLY1_Pos)),
             (Delay << (POSITION_VAL(Pin) * GPIO_DELAYRL_DLY1_Pos))
            );
}

/**
  * @brief  Return gpio delay of a dedicated pin from 0 to 7 for a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_DELAY_0
  *         @arg @ref LL_GPIO_DELAY_300
  *         @arg @ref LL_GPIO_DELAY_500
  *         @arg @ref LL_GPIO_DELAY_750
  *         @arg @ref LL_GPIO_DELAY_1000
  *         @arg @ref LL_GPIO_DELAY_1250
  *         @arg @ref LL_GPIO_DELAY_1500
  *         @arg @ref LL_GPIO_DELAY_1750
  *         @arg @ref LL_GPIO_DELAY_2000
  *         @arg @ref LL_GPIO_DELAY_2250
  *         @arg @ref LL_GPIO_DELAY_2500
  *         @arg @ref LL_GPIO_DELAY_2750
  *         @arg @ref LL_GPIO_DELAY_3000
  *         @arg @ref LL_GPIO_DELAY_3250
  */
__STATIC_INLINE uint32_t LL_GPIO_GetDelayPin_0_7(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->DELAYRL,
                             ((uint32_t)GPIO_DELAYRL_DLY0 << (POSITION_VAL(Pin) * GPIO_DELAYRL_DLY1_Pos))
                            )
                    >> (POSITION_VAL(Pin) * GPIO_DELAYRL_DLY1_Pos)
                   );
}

/**
  * @brief  Configure gpio delay of a dedicated pin from 8 to 15 for a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @param  Delay This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_DELAY_0
  *         @arg @ref LL_GPIO_DELAY_300
  *         @arg @ref LL_GPIO_DELAY_500
  *         @arg @ref LL_GPIO_DELAY_750
  *         @arg @ref LL_GPIO_DELAY_1000
  *         @arg @ref LL_GPIO_DELAY_1250
  *         @arg @ref LL_GPIO_DELAY_1500
  *         @arg @ref LL_GPIO_DELAY_1750
  *         @arg @ref LL_GPIO_DELAY_2000
  *         @arg @ref LL_GPIO_DELAY_2250
  *         @arg @ref LL_GPIO_DELAY_2500
  *         @arg @ref LL_GPIO_DELAY_2750
  *         @arg @ref LL_GPIO_DELAY_3000
  *         @arg @ref LL_GPIO_DELAY_3250
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetDelayPin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Delay)
{
  MODIFY_REG(GPIOx->DELAYRH,
             (GPIO_DELAYRH_DLY8 << (POSITION_VAL(Pin) * GPIO_DELAYRH_DLY9_Pos)),
             (Delay << (POSITION_VAL(Pin) * GPIO_DELAYRH_DLY9_Pos))
            );
}

/**
  * @brief  Return gpio delay of a dedicated pin from 8 to 15 for a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_GPIO_DELAY_0
  *         @arg @ref LL_GPIO_DELAY_300
  *         @arg @ref LL_GPIO_DELAY_500
  *         @arg @ref LL_GPIO_DELAY_750
  *         @arg @ref LL_GPIO_DELAY_1000
  *         @arg @ref LL_GPIO_DELAY_1250
  *         @arg @ref LL_GPIO_DELAY_1500
  *         @arg @ref LL_GPIO_DELAY_1750
  *         @arg @ref LL_GPIO_DELAY_2000
  *         @arg @ref LL_GPIO_DELAY_2250
  *         @arg @ref LL_GPIO_DELAY_2500
  *         @arg @ref LL_GPIO_DELAY_2750
  *         @arg @ref LL_GPIO_DELAY_3000
  *         @arg @ref LL_GPIO_DELAY_3250
  */
__STATIC_INLINE uint32_t LL_GPIO_GetDelayPin_8_15(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->DELAYRH,
                             ((uint32_t)GPIO_DELAYRH_DLY8 << (POSITION_VAL(Pin) * GPIO_DELAYRH_DLY9_Pos))
                            )
                    >> (POSITION_VAL(Pin) * GPIO_DELAYRH_DLY9_Pos)
                   );
}

/**
  * @brief  Configure gpio delay of a dedicated pin from 0 to 7 for a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  * @param  CfgMask:
  *         ADVCFG[0] : Delay on ouptput path
  *         ADVCFG[1] : input and ouptput data are double edge
  *         ADVCFG[2] : I/O clocks are inverted
  *         ADVCFG[3] : input and ouptput data are retimed
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetPIOControlPin_0_7(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t CfgMask)
{
  MODIFY_REG(GPIOx->ADVCFGRL,
             (GPIO_ADVCFGRL_0 << (POSITION_VAL(Pin) * GPIO_ADVCFGRL_1_Pos)),
             (CfgMask << (POSITION_VAL(Pin) * GPIO_ADVCFGRL_1_Pos))
            );
}

/**
  * @brief  Return gpio delay of a dedicated pin from 0 to 7 for a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         ADVCFG[0] : Delay on ouptput path
  *         ADVCFG[1] : input and ouptput data are double edge
  *         ADVCFG[2] : I/O clocks are inverted
  *         ADVCFG[3] : input and ouptput data are retimed
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPIOControlPin_0_7(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->ADVCFGRL,
                             ((uint32_t)GPIO_ADVCFGRL_0 << (POSITION_VAL(Pin) * GPIO_ADVCFGRL_1_Pos))
                            )
                    >> (POSITION_VAL(Pin) * GPIO_ADVCFGRL_1_Pos)
                   );
}

/**
  * @brief  Configure gpio delay of a dedicated pin from 8 to 15 for a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @param  CfgMask:
  *         ADVCFG[0] : Delay on ouptput path
  *         ADVCFG[1] : input and ouptput data are double edge
  *         ADVCFG[2] : I/O clocks are inverted
  *         ADVCFG[3] : input and ouptput data are retimed
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetPIOControlPin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t CfgMask)
{
  MODIFY_REG(GPIOx->ADVCFGRH,
             (GPIO_ADVCFGRH_8 << (POSITION_VAL(Pin) * GPIO_ADVCFGRH_9_Pos)),
             (CfgMask << (POSITION_VAL(Pin) * GPIO_ADVCFGRH_9_Pos))
            );
}

/**
  * @brief  Return gpio delay of a dedicated pin from 8 to 15 for a dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         ADVCFG[0] : Delay on ouptput path
  *         ADVCFG[1] : input and ouptput data are double edge
  *         ADVCFG[2] : I/O clocks are inverted
  *         ADVCFG[3] : input and ouptput data are retimed
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPIOControlPin_8_15(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->ADVCFGRH,
                             ((uint32_t)GPIO_ADVCFGRH_8 << (POSITION_VAL(Pin) * GPIO_ADVCFGRH_9_Pos))
                            )
                    >> (POSITION_VAL(Pin) * GPIO_ADVCFGRH_9_Pos)
                   );
}


/** @defgroup GPIO_LL_EF_Data_Access Data Access
  * @{
  */

/**
  * @brief  Return full input data register value for a dedicated port.
  * @rmtoll IDR          IDy           LL_GPIO_ReadInputPort
  * @param  GPIOx GPIO Port
  * @retval Input data register value of port
  */
__STATIC_INLINE uint32_t LL_GPIO_ReadInputPort(const GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->IDR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll IDR          IDy           LL_GPIO_IsInputPinSet
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsInputPinSet(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return ((READ_BIT(GPIOx->IDR, PinMask) == (PinMask)) ? 1UL : 0UL);
}

/**
  * @brief  Write output data register for the port.
  * @rmtoll ODR          ODy           LL_GPIO_WriteOutputPort
  * @param  GPIOx GPIO Port
  * @param  PortValue Level value for each pin of the port
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue)
{
  WRITE_REG(GPIOx->ODR, PortValue);
}

/**
  * @brief  Return full output data register value for a dedicated port.
  * @rmtoll ODR          ODy           LL_GPIO_ReadOutputPort
  * @param  GPIOx GPIO Port
  * @retval Output data register value of port
  */
__STATIC_INLINE uint32_t LL_GPIO_ReadOutputPort(const GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->ODR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll ODR          ODy           LL_GPIO_IsOutputPinSet
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsOutputPinSet(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return ((READ_BIT(GPIOx->ODR, PinMask) == (PinMask)) ? 1UL : 0UL);
}

/**
  * @brief  Set several pins to high level on dedicated gpio port.
  * @rmtoll BSRR         BSy           LL_GPIO_SetOutputPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BSRR, PinMask);
}

/**
  * @brief  Set several pins to low level on dedicated gpio port.
  * @rmtoll BRR          BRy           LL_GPIO_ResetOutputPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_ResetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BRR, PinMask);
}

/**
  * @brief  Toggle data value for several pin of dedicated port.
  * @rmtoll ODR          ODy           LL_GPIO_TogglePin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->ODR, READ_REG(GPIOx->ODR) ^ PinMask);
}


/**
  * @brief  Enable CID filtering for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinCidFiltering(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  SET_BIT(*regaddr, GPIO_CIDCFGR0_CFEN);
}

/**
  * @brief  Disable CID filtering for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinCidFiltering(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  CLEAR_BIT(*regaddr, GPIO_CIDCFGR0_CFEN);
}

/**
  * @brief  Check if CID filtering for a pin of dedicated port is enabled.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval xxx
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinCidFiltering(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  return ((READ_BIT(*regaddr, GPIO_CIDCFGR0_CFEN) == GPIO_CIDCFGR0_CFEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable semaphore for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinSemaphore(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  SET_BIT(*regaddr, GPIO_CIDCFGR0_SEM_EN);
}

/**
  * @brief  Disable semaphore for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinSemaphore(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  CLEAR_BIT(*regaddr, GPIO_CIDCFGR0_SEM_EN);
}

/**
  * @brief  Check if semaphore for a pin of dedicated port is enabled.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval xxx
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinSemaphore(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  return ((READ_BIT(*regaddr, GPIO_CIDCFGR0_SEM_EN) == GPIO_CIDCFGR0_SEM_EN) ? 1UL : 0UL);
}

/**
  * @brief  Set CID for pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @param  cid
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_SetPinCid(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t cid)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);

  MODIFY_REG(*regaddr, GPIO_CIDCFGR0_SCID, cid << GPIO_CIDCFGR0_SCID_Pos);
}

/**
  * @brief  Get CID for pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval CID
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinCid(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);

  return ((READ_REG(*regaddr) & (GPIO_CIDCFGR0_SCID)) >> GPIO_CIDCFGR0_SCID_Pos) ;
}

/**
  * @brief  Enable semaphore whitelist for compartment for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinSemaphoreWhitelistCompartment0(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  SET_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC0);
}

/**
  * @brief  Disable semaphore whitelist for compartment a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinSemaphoreWhitelistCompartment0(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  CLEAR_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC0);
}

/**
  * @brief  Check if semaphore whitelist for compartment a pin of dedicated port is enabled.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval true is semaphire whitelist for compartment is enabled
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinSemaphoreWhitelistCompartment0(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  return ((READ_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC0) == GPIO_CIDCFGR0_SEMWLC0) ? 1UL : 0UL);
}


/**
  * @brief  Enable semaphore whitelist for compartment for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinSemaphoreWhitelistCompartment1(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  SET_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC1);
}

/**
  * @brief  Disable semaphore whitelist for compartment a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinSemaphoreWhitelistCompartment1(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  CLEAR_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC1);
}

/**
  * @brief  Check if semaphore whitelist for compartment a pin of dedicated port is enabled.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval true is semaphire whitelist for compartment is enabled
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinSemaphoreWhitelistCompartment1(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  return ((READ_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC1) == GPIO_CIDCFGR0_SEMWLC1) ? 1UL : 0UL);
}

/**
  * @brief  Enable semaphore whitelist for compartment for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinSemaphoreWhitelistCompartment2(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  SET_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC2);
}

/**
  * @brief  Disable semaphore whitelist for compartment a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinSemaphoreWhitelistCompartment2(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  CLEAR_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC2);
}

/**
  * @brief  Check if semaphore whitelist for compartment a pin of dedicated port is enabled.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval true is semaphire whitelist for compartment is enabled
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinSemaphoreWhitelistCompartment2(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  return ((READ_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC2) == GPIO_CIDCFGR0_SEMWLC2) ? 1UL : 0UL);
}

/**
  * @brief  Enable semaphore whitelist for compartment for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinSemaphoreWhitelistCompartment3(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  SET_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC3);
}

/**
  * @brief  Disable semaphore whitelist for compartment a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinSemaphoreWhitelistCompartment3(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  CLEAR_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC3);
}

/**
  * @brief  Check if semaphore whitelist for compartment a pin of dedicated port is enabled.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval true is semaphire whitelist for compartment is enabled
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinSemaphoreWhitelistCompartment3(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->CIDCFGR0 + (POSITION_VAL(Pin) * 2U);
  return ((READ_BIT(*regaddr, GPIO_CIDCFGR0_SEMWLC3) == GPIO_CIDCFGR0_SEMWLC3) ? 1UL : 0UL);
}


/**
  * @brief  Enable semaphore for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval true if semaphore is taken
  */
__STATIC_INLINE uint32_t LL_GPIO_TakePinSemaphore(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->SEMCR0 + (POSITION_VAL(Pin) * 2U);
  SET_BIT(*regaddr, GPIO_SEMCR0_SEM_MUTEX);

  return ((READ_BIT(*regaddr, GPIO_SEMCR0_SEM_MUTEX) == GPIO_SEMCR0_SEM_MUTEX) ? 1UL : 0UL);
}

/**
  * @brief  Disable semaphore for a pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval true if semaphore is release
  */
__STATIC_INLINE uint32_t LL_GPIO_ReleasePinSemaphore(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t *regaddr;

  regaddr = &GPIOx->SEMCR0 + (POSITION_VAL(Pin) * 2U);
  CLEAR_BIT(*regaddr, GPIO_SEMCR0_SEM_MUTEX);

  return ((READ_BIT(*regaddr, GPIO_SEMCR0_SEM_MUTEX) != GPIO_SEMCR0_SEM_MUTEX) ? 1UL : 0UL);
}

/**
  * @brief  Check if semaphore for a pin of dedicated port is enabled.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval xxx
  */
__STATIC_INLINE uint32_t LL_GPIO_IsPinSemaphoreTaken(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->SEMCR0 + (POSITION_VAL(Pin) * 2U);
  return ((READ_BIT(*regaddr, GPIO_SEMCR0_SEM_MUTEX) == GPIO_SEMCR0_SEM_MUTEX) ? 1UL : 0UL);
}

/**
  * @brief  Get semaphore CID for pin of dedicated port.
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  * @retval CID
  */
__STATIC_INLINE uint32_t LL_GPIO_GetPinSemaphoreCid(const GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  const __IO uint32_t *regaddr;

  regaddr = &GPIOx->SEMCR0 + (POSITION_VAL(Pin) * 2U);

  return ((READ_REG(*regaddr) & (GPIO_SEMCR0_SEMCID)) >> GPIO_SEMCR0_SEMCID_Pos) ;
}


/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
  * @brief  Enable secure write only access for several pin of dedicated port.
  * @rmtoll SECCFGR      SECy           LL_GPIO_EnablePinSecure
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinSecure(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  SET_BIT(GPIOx->SECCFGR, PinMask);
}


/**
  * @brief  Disable secure write only access for several pin of dedicated port.
  * @rmtoll SECCFGR      SECy           LL_GPIO_DisablePinSecure
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinSecure(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  CLEAR_BIT(GPIOx->SECCFGR, PinMask);
}

#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Return if secure write only access for several pin of dedicated port is enabled or not.
  * @rmtoll SECCFGR      SECy           LL_GPIO_IsEnabledPinSecure
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinSecure(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return ((READ_BIT(GPIOx->SECCFGR, PinMask) == (PinMask)) ? 1UL : 0UL);
}


/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/**
  * @brief  Enable secure write only access for several pin of dedicated port.
  * @rmtoll SECCFGR      SECy           LL_GPIO_EnablePinPrivilege
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_EnablePinPrivilege(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  SET_BIT(GPIOx->PRIVCFGR, PinMask);
}


/**
  * @brief  Disable secure write only access for several pin of dedicated port.
  * @rmtoll SECCFGR      SECy           LL_GPIO_DisablePinPrivilege
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_GPIO_DisablePinPrivilege(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  CLEAR_BIT(GPIOx->PRIVCFGR, PinMask);
}

#endif /* __ARM_FEATURE_CMSE */

/**
  * @brief  Return if privilege write only access for several pin of dedicated port is enabled or not.
  * @rmtoll SECCFGR      SECy           LL_GPIO_IsEnabledPinSecure
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_GPIO_PIN_0
  *         @arg @ref LL_GPIO_PIN_1
  *         @arg @ref LL_GPIO_PIN_2
  *         @arg @ref LL_GPIO_PIN_3
  *         @arg @ref LL_GPIO_PIN_4
  *         @arg @ref LL_GPIO_PIN_5
  *         @arg @ref LL_GPIO_PIN_6
  *         @arg @ref LL_GPIO_PIN_7
  *         @arg @ref LL_GPIO_PIN_8
  *         @arg @ref LL_GPIO_PIN_9
  *         @arg @ref LL_GPIO_PIN_10
  *         @arg @ref LL_GPIO_PIN_11
  *         @arg @ref LL_GPIO_PIN_12
  *         @arg @ref LL_GPIO_PIN_13
  *         @arg @ref LL_GPIO_PIN_14
  *         @arg @ref LL_GPIO_PIN_15
  *         @arg @ref LL_GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_GPIO_IsEnabledPinPrivilege(const GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return ((READ_BIT(GPIOx->PRIVCFGR, PinMask) == (PinMask)) ? 1UL : 0UL);
}


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup GPIO_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_GPIO_DeInit(const GPIO_TypeDef *GPIOx);
ErrorStatus LL_GPIO_Init(GPIO_TypeDef *GPIOx, LL_GPIO_InitTypeDef *GPIO_InitStruct);
void        LL_GPIO_StructInit(LL_GPIO_InitTypeDef *GPIO_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif  /* (                                                                                  \
              (defined(CORE_CM33) || defined(CORE_CA35))                                      \
              &&                                                                              \
              (                                                                               \
                defined (GPIOA) || defined (GPIOB) || defined (GPIOC) || defined (GPIOD) ||   \
                defined (GPIOE) || defined (GPIOF) || defined (GPIOG) || defined (GPIOH) ||   \
                defined (GPIOI) || defined (GPIOJ) || defined (GPIOK) || defined (GPIOZ)      \
              )                                                                               \
            )                                                                                 \
            ||                                                                                \
            (defined(CORE_CM0PLUS) && defined(GPIOZ))
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

#endif /* __STM32MP2xx_LL_GPIO_H */
