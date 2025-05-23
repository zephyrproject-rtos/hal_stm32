/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_gpio.c
  * @author  MCD Application Team
  * @brief   GPIO HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
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
  @verbatim
  ==============================================================================
                    ##### GPIO Peripheral features #####
  ==============================================================================
  [..]
    (+) Each port bit of the general-purpose I/O (GPIO) ports can be individually
        configured by software in several modes:
        (++) Input mode
        (++) Analog mode
        (++) Output mode
        (++) Alternate function mode
        (++) External interrupt/event lines

    (+) During and just after reset, the alternate functions and external interrupt
        lines are not active and the I/O ports are configured in input floating mode.

    (+) All GPIO pins have weak internal pull-up and pull-down resistors, which can be
        activated or not.

    (+) In Output or Alternate mode, each IO can be configured on open-drain or push-pull
        type and the IO speed can be selected depending on the VDD value.

    (+) The microcontroller IO pins are connected to onboard peripherals/modules through a
        multiplexer that allows only one peripheral alternate function (AF) connected
       to an IO pin at a time. In this way, there can be no conflict between peripherals
       sharing the same IO pin.

    (+) All ports have external interrupt/event capability. To use external interrupt
        lines, the port must be configured in input mode. All available GPIO pins are
        connected to the 16 external interrupt/event lines from EXTI0 to EXTI15.

    (+) The external interrupt/event controller consists of up to 28 edge detectors
        (16 lines are connected to GPIO) for generating event/interrupt requests (each
        input line can be independently configured to select the type (interrupt or event)
        and the corresponding trigger event (rising or falling or both). Each line can
        also be masked independently.

                     ##### How to use this driver #####
  ==============================================================================
  [..]
    (#) Enable the GPIO AHB clock using the following function: __HAL_RCC_GPIOx_CLK_ENABLE().

    (#) Configure the GPIO pin(s) using HAL_GPIO_Init().
        (++) Configure the IO mode using "Mode" member from GPIO_InitTypeDef structure
        (++) Activate Pull-up, Pull-down resistor using "Pull" member from GPIO_InitTypeDef
             structure.
        (++) In case of Output or alternate function mode selection: the speed is
             configured through "Speed" member from GPIO_InitTypeDef structure.
        (++) In alternate mode is selection, the alternate function connected to the IO
             is configured through "Alternate" member from GPIO_InitTypeDef structure.
        (++) Analog mode is required when a pin is to be used as ADC channel
             or DAC output.
        (++) In case of external interrupt/event selection the "Mode" member from
             GPIO_InitTypeDef structure select the type (interrupt or event) and
             the corresponding trigger event (rising or falling or both).

    (#) In case of external interrupt/event mode selection, configure NVIC IRQ priority
        mapped to the EXTI line using HAL_NVIC_SetPriority() and enable it using
        HAL_NVIC_EnableIRQ().

    (#) To get the level of a pin configured in input mode use HAL_GPIO_ReadPin().

    (#) To set/reset the level of a pin configured in output mode use
        HAL_GPIO_WritePin()/HAL_GPIO_TogglePin().

    (#) To set the level of several pins and reset level of several other pins in
        same cycle, use HAL_GPIO_WriteMultipleStatePin().

   (#) To lock pin configuration until next reset use HAL_GPIO_LockPin().

    (#) During and just after reset, the alternate functions are not
        active and the GPIO pins are configured in input floating mode (except JTAG
        pins).

    (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as general purpose
        (PC14 and PC15, respectively) when the LSE oscillator is off. The LSE has
        priority over the GPIO function.

    (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as
        general purpose PH0 and PH1, respectively, when the HSE oscillator is off.
        The HSE has priority over the GPIO function.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

#ifdef HAL_GPIO_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */
#define GPIO_MODE             (0x00000003U)
#define EXTI1_MODE            (0x10000000U)
#define EXTI2_MODE            (0x20000000U)
#define GPIO_MODE_IT          (0x00010000U)
#define GPIO_MODE_EVT         (0x00020000U)
#define RISING_EDGE           (0x00100000U)
#define FALLING_EDGE          (0x00200000U)
#define GPIO_OUTPUT_TYPE      (0x00000010U)

#define GPIO_NUMBER           (16U)

#define GPIO_CIDCFGR_OFFSET                    0x02u   /*offset between GPIOx_CIDCFG#i GPIOx_CIDCFG#(i+1) registers */
#define GPIO_SEMCFGR_OFFSET                    0x02u   /*offset between GPIOx_SEMCFG#i GPIOx_SEMCFG#(i+1) registers */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup GPIO_Exported_Functions
  * @{
  */

/** @addtogroup GPIO_Exported_Functions_Group1
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Init: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  *         Note that EXTI instance (EXTI1/EXTI2) to use in case of interruption mode is part of
  *         GPIO_Init value (see mode field)
  * @retval None
  */
void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, const GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t position = 0x00u;
  uint32_t iocurrent;
  uint32_t temp;
  uint32_t extiRequested = 0;
  EXTI_TypeDef *EXTI = NULL ;
  EXTI_Core_TypeDef *EXTI_CurrentCPU = NULL;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
  assert_param(IS_GPIO_MODE(GPIO_Init->Mode));
  assert_param(IS_GPIO_PULL(GPIO_Init->Pull));


  /* Configure the port pins */
  while (((GPIO_Init->Pin) >> position) != 0x00u)
  {
    /* Get current io position */
    iocurrent = (GPIO_Init->Pin) & (1uL << position);

    if (iocurrent != 0x00u)
    {
      /*--------------------- GPIO Mode Configuration ------------------------*/
      /* In case of Alternate function mode selection */
      if ((GPIO_Init->Mode == GPIO_MODE_AF_PP) || (GPIO_Init->Mode == GPIO_MODE_AF_OD))
      {
        /* Check the Alternate function parameters */
        assert_param(IS_GPIO_AF(GPIO_Init->Alternate));

        /* Configure Alternate function mapped with the current IO */
        temp = GPIOx->AFR[position >> 3U];
        temp &= ~(GPIO_AFRL_AFSEL0 << ((position & 0x07U) * GPIO_AFRL_AFSEL1_Pos));
        temp |= ((GPIO_Init->Alternate) << ((position & 0x07U) * GPIO_AFRL_AFSEL1_Pos));
        GPIOx->AFR[position >> 3u] = temp;
      }

      /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
      temp = GPIOx->MODER;
      temp &= ~(GPIO_MODER_MODE0 << (position * GPIO_MODER_MODE1_Pos));
      temp |= ((GPIO_Init->Mode & GPIO_MODE) << (position * GPIO_MODER_MODE1_Pos));
      GPIOx->MODER = temp;

      /* In case of Output or Alternate function mode selection */
      if ((GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP) || (GPIO_Init->Mode == GPIO_MODE_AF_PP) ||
          (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD) || (GPIO_Init->Mode == GPIO_MODE_AF_OD))
      {
        /* Check the Speed parameter */
        assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
        /* Configure the IO Speed */
        temp = GPIOx->OSPEEDR;
        temp &= ~(GPIO_OSPEEDR_OSPEED0 << (position * GPIO_OSPEEDR_OSPEED1_Pos));
        temp |= (GPIO_Init->Speed << (position * GPIO_OSPEEDR_OSPEED1_Pos));
        GPIOx->OSPEEDR = temp;

        /* Configure the IO Output Type */
        temp = GPIOx->OTYPER;
        temp &= ~(GPIO_OTYPER_OT0 << position) ;
        temp |= (((GPIO_Init->Mode & GPIO_OUTPUT_TYPE) >> 4U) << position);
        GPIOx->OTYPER = temp;
      }

      /* Activate the Pull-up or Pull down resistor for the current IO */
      temp = GPIOx->PUPDR;
      temp &= ~(GPIO_PUPDR_PUPD0 << (position * GPIO_PUPDR_PUPD1_Pos));
      temp |= ((GPIO_Init->Pull) << (position * GPIO_PUPDR_PUPD1_Pos));
      GPIOx->PUPDR = temp;

      /*--------------------- EXTI Mode Configuration ------------------------*/
      /* Configure the External Interrupt or event for the current IO */
#if !defined(CORE_CM0PLUS)
      if ((GPIO_Init->Mode & EXTI1_MODE) == EXTI1_MODE)
      {
        extiRequested = 1;
        EXTI = EXTI1;
#if defined(CORE_CM33)
        EXTI_CurrentCPU = EXTI1_C2; /* GPIOs are connected to M33 NVIC via connection 2*/
#endif  /* CORE_CM33 */
#if defined(CORE_CA35)
        EXTI_CurrentCPU = EXTI1_C1; /* GPIOs are connected to A35 GIC via connection 1*/
#endif  /* CORE_CA35 */
      }
#endif  /* !defined(CORE_CM0PLUS) */
      if ((GPIO_Init->Mode & EXTI2_MODE) == EXTI2_MODE)
      {
        extiRequested = 1;
        EXTI = EXTI2;
#if defined(CORE_CM0PLUS)
        EXTI_CurrentCPU = EXTI2_C3; /* GPIOs are connected to CM0PLUS NVIC via connection 3*/
#endif  /* CORE_CM0PLUS */
#if defined(CORE_CM33)
        EXTI_CurrentCPU = EXTI2_C2; /* GPIOs are connected to M33 NVIC via connection 2*/
#endif  /* CORE_CM33 */
#if defined(CORE_CA35)
        EXTI_CurrentCPU = EXTI2_C1; /* GPIOs are connected to A35 GIC via connection 1*/
#endif  /* CORE_CA35 */
      }


      if (extiRequested != 0U)
      {
        temp = EXTI->EXTICR[position >> 2u];
        temp &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (position & 0x03U)));
        temp |= ((uint32_t)GPIO_GET_INDEX(GPIOx) << (EXTI_EXTICR1_EXTI1_Pos * (position & 0x03U)));
        EXTI->EXTICR[position >> 2u] = temp;

        /* Clear Rising Falling edge configuration */
        temp = EXTI->RTSR1;
        temp &= ~((uint32_t)iocurrent);
        if ((GPIO_Init->Mode & RISING_EDGE) == RISING_EDGE)
        {
          temp |= iocurrent;
        }
        EXTI->RTSR1 = temp;

        temp = EXTI->FTSR1;
        temp &= ~((uint32_t)iocurrent);
        if ((GPIO_Init->Mode & FALLING_EDGE) == FALLING_EDGE)
        {
          temp |= iocurrent;
        }
        EXTI->FTSR1 = temp;

        /* Clear EXTI line configuration */
        temp = EXTI_CurrentCPU->IMR1;
        temp &= ~((uint32_t)iocurrent);
        if ((GPIO_Init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
        {
          temp |= iocurrent;
        }
        EXTI_CurrentCPU->IMR1 = temp;

        temp = EXTI_CurrentCPU->EMR1;
        temp &= ~((uint32_t)iocurrent);
        if ((GPIO_Init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
        {
          temp |= iocurrent;
        }
        EXTI_CurrentCPU->EMR1 = temp;
      }
    }

    position++;
  }
}

#if !defined(CORE_CM0PLUS)
EXTI_TypeDef *getUsedExti(const GPIO_TypeDef  *GPIOx, uint32_t pinPosition)
{
#define EXTI_INSTANCE_NB 2U
  uint32_t extiIndex;
  uint32_t portIndex;
  uint32_t GPIOx_index = 0xFF;
  EXTI_TypeDef  *instanceEXTI;
  EXTI_TypeDef *instanceTab[]  = {EXTI1, EXTI2};
  uint32_t temp;
#if defined(GPIOJ) && defined(GPIOK)
  GPIO_TypeDef *port[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK, GPIOZ};
#else   /* defined(GPIOJ) && defined(GPIOK) */
  GPIO_TypeDef *port[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI, GPIOZ};
#endif  /* defined(GPIOJ) && defined(GPIOK) */
  const EXTI_Core_TypeDef *EXTI_CurrentCPU;


#if defined(CORE_CM33)
  EXTI_Core_TypeDef *EXTI_CPU[]  = {EXTI1_C2, EXTI2_C2};
#endif  /* CORE_CM33 */
#if defined(CORE_CA35)
  EXTI_Core_TypeDef *EXTI_CPU[]  = {EXTI1_C1, EXTI2_C1};
#endif  /* CORE_CA35 */

  /* find port index */
  for (portIndex = 0; portIndex < (sizeof(port) / sizeof(GPIO_TypeDef *)); portIndex++)
  {
    if (GPIOx == port[portIndex])
    {
      GPIOx_index = portIndex;
      break;
    }
  }

  /*parse all EXTI instance*/
  for (extiIndex = 0; extiIndex < EXTI_INSTANCE_NB; extiIndex++)
  {
    EXTI_CurrentCPU = EXTI_CPU[extiIndex];

    /*check if parsed EXTI instance is configured for a connection with input param GPIO bank*/
    instanceEXTI = instanceTab[extiIndex];
    temp = instanceEXTI->EXTICR[pinPosition >> 2u];
    if (((temp >> ((pinPosition % 4U) * EXTI_EXTICR1_EXTI1_Pos)) & EXTI_EXTICR1_EXTI0) == GPIOx_index)
    {
      /*check if interruption mode is selected for input pin*/
      if ((((EXTI_CurrentCPU->IMR1) >> pinPosition) & 0x1U) != 0U)
      {
        return instanceEXTI;  /* both GPIO bank and interruption mode are OK */
      }
      /*check if event mode is selected for input pin*/
      if ((((EXTI_CurrentCPU->EMR1) >> pinPosition) & 0x1U) != 0U)
      {
        return instanceEXTI;  /* both GPIO bank and event mode are OK */
      }
    }
  }
  return NULL;  /* EXTI instance not founded */
}
#endif /*!defined(CORE_CM0PLUS)*/

/**
  * @brief  De-initializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter is a bit mask where  2**k is bit mask of GPIO line k
  * @retval None
  */
void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
  uint32_t position = 0x00uL;
  uint32_t iocurrent;
  uint32_t tmp;
  EXTI_TypeDef *EXTI;
  EXTI_Core_TypeDef *EXTI_CurrentCPU;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));


  /* Configure the port pins */
  while ((GPIO_Pin >> position) != 0x00u)
  {
    /* Get current io position */
    iocurrent = (GPIO_Pin) & (1uL << position);

    if (iocurrent != 0x00u)
    {
      /*------------------------- EXTI Mode Configuration --------------------*/
      /* Clear the External Interrupt or Event for the current IO */
      {
#if defined(CORE_CM0PLUS)
        EXTI = EXTI2;
        EXTI_CurrentCPU = EXTI2_C3;
#else   /* CORE_CM0PLUS */
        EXTI = getUsedExti(GPIOx, position);
#if defined(CORE_CM33)
        EXTI_CurrentCPU = (EXTI == EXTI2) ? (EXTI2_C2) : (EXTI1_C2);
#endif  /* CORE_CM33 */
#if defined(CORE_CA35)
        EXTI_CurrentCPU = (EXTI == EXTI2) ? (EXTI2_C1) : (EXTI1_C1);
#endif  /* CORE_CA35 */
#endif  /* CORE_CM0PLUS */
        if (EXTI != NULL)
        {
          tmp = EXTI->EXTICR[position >> 2u];
          tmp &= ((uint32_t)EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos  * (position & 0x03UL)));
          if (tmp == ((uint32_t)GPIO_GET_INDEX(GPIOx) << (EXTI_EXTICR1_EXTI1_Pos * (position & 0x03UL))))
          {
            /* Clear EXTI line configuration */
            /* Clear the External Interrupt or Event for the current IO */
            EXTI_CurrentCPU->IMR1 &= ~((uint32_t)iocurrent);
            EXTI_CurrentCPU->EMR1 &= ~((uint32_t)iocurrent);

            /* Clear Rising Falling edge configuration */
            EXTI->RTSR1 &= ~(iocurrent);
            EXTI->FTSR1 &= ~(iocurrent);

            /* Clear EXTICR configuration */
            tmp = (uint32_t)EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (position & 0x03U));
            EXTI->EXTICR[position >> 2u] &= ~tmp;
          }
        }
      }

      /*------------------------- GPIO Mode Configuration --------------------*/
      /* Configure IO in Analog Mode */
      GPIOx->MODER |= ((uint32_t)GPIO_MODER_MODE0 << (position * GPIO_MODER_MODE1_Pos));

      /* Configure the default Alternate Function in current IO */
      GPIOx->AFR[position >> 3U] &= ~(GPIO_AFRL_AFSEL0 << ((position & 0x07U) * GPIO_AFRL_AFSEL1_Pos)) ;

      /* Configure the default value for IO Speed */
      GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (position * GPIO_OSPEEDR_OSPEED1_Pos));

      /* Configure the default value IO Output Type */
      GPIOx->OTYPER  &= ~(GPIO_OTYPER_OT0 << position) ;

      /* Deactivate the Pull-up and Pull-down resistor for the current IO */
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPD0 << (position * GPIO_PUPDR_PUPD1_Pos));
    }
    position++;
  }
}

/**
  * @}
  */

/** @addtogroup GPIO_Exported_Functions_Group2
  *  @brief GPIO Read, Write, Toggle, Lock and EXTI management functions.
  *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Read the specified input port pin.
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin specifies the port bit to read.
  *         This parameter can be any combination of GPIO_PIN_x where x can be (0..15).
  * @retval The input port pin value.
  */
GPIO_PinState HAL_GPIO_ReadPin(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != 0x00u)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Set or clear the selected data port bit.
  *
  * @note   This function uses GPIOx_BSRR register to allow atomic read/modify
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  *
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin specifies the port bit to be written.
  *         This parameter can be any combination of GPIO_PIN_x where x can be (0..15).
  * @param PinState specifies the value to be written to the selected bit.
  *         This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @retval None
  */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if (PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << GPIO_NUMBER;
  }
}

/**
  * @brief  Set and clear several pins of a dedicated port in same cycle.
  * @note   This function uses GPIOx_BSRR and GPIOx_BRR registers to allow atomic read/modify
  *         accesses.
  * @param  GPIOx where x can be any bank of GPIO peripheral for STM32MP2xx family
  * @param  PinReset specifies the port bits to be reset
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15) or zero.
  * @param  PinSet specifies the port bits to be set
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15) or zero.
  * @note   Both PinReset and PinSet combinations shall not get any common bit, else
  *         assert would be triggered.
  * @note   At least one of the two parameters used to set or reset shall be different from zero.
  * @retval None
  */
void HAL_GPIO_WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet)
{
  uint32_t tmp;

  /* Check the parameters */
  /* Make sure at least one parameter is different from zero and that there is no common pin */
  assert_param(IS_GPIO_PIN((uint32_t)PinReset | (uint32_t)PinSet));
  assert_param(IS_GPIO_COMMON_PIN(PinReset, PinSet));

  tmp = (((uint32_t)PinReset << 16) | PinSet);
  GPIOx->BSRR = tmp;
}

/**
  * @brief  Toggle the specified GPIO pin.
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin specifies the pin to be toggled.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->ODR & GPIO_Pin) != 0x00u)
  {
    GPIOx->BRR = (uint32_t)GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin;
  }
}

/**
  * @brief  Lock GPIO Pins configuration registers.
  * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next reset.
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin specifies the port bits to be locked.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = GPIO_LCKR_LCKK;

  /* Check the parameters */
  assert_param(IS_GPIO_LOCK_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* Apply lock key write sequence */
  tmp |= GPIO_Pin;
  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
  GPIOx->LCKR = tmp;
  /* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
  GPIOx->LCKR = GPIO_Pin;
  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
  GPIOx->LCKR = tmp;
  /* Read LCKK register. This read is mandatory to complete key lock sequence */
  tmp = GPIOx->LCKR;

  /* read again in order to confirm lock is active */
  if ((GPIOx->LCKR & GPIO_LCKR_LCKK) != 0x00u)
  {
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Handle EXTI interrupt request.
  * @param GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
#if !defined(CORE_CM0PLUS)
void HAL_GPIO_EXTI1_IRQHandler(uint16_t GPIO_Pin)
{
  /* EXTI line interrupt detected */
  if (__HAL_GPIO_EXTI1_GET_RISING_IT(GPIO_Pin) != (uint32_t)RESET)
  {
    __HAL_GPIO_EXTI1_CLEAR_RISING_IT(GPIO_Pin);
    HAL_GPIO_EXTI1_Rising_Callback(GPIO_Pin);
  }

  if (__HAL_GPIO_EXTI1_GET_FALLING_IT(GPIO_Pin) != (uint32_t)RESET)
  {
    __HAL_GPIO_EXTI1_CLEAR_FALLING_IT(GPIO_Pin);
    HAL_GPIO_EXTI1_Falling_Callback(GPIO_Pin);
  }
}
#endif /*!defined(CORE_CM0PLUS)*/

void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  /* EXTI line interrupt detected */
  if (__HAL_GPIO_EXTI_GET_RISING_IT(GPIO_Pin) != (uint32_t)RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_RISING_IT(GPIO_Pin);
    HAL_GPIO_EXTI_Rising_Callback(GPIO_Pin);
  }

  if (__HAL_GPIO_EXTI_GET_FALLING_IT(GPIO_Pin) != (uint32_t)RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_FALLING_IT(GPIO_Pin);
    HAL_GPIO_EXTI_Falling_Callback(GPIO_Pin);
  }
}

/**
  * @brief  EXTI line rising detection callback.
  * @param GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
__weak void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Rising_Callback could be implemented in the user file
   */
}
#if !defined(CORE_CM0PLUS)
__weak void HAL_GPIO_EXTI1_Rising_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Rising_Callback could be implemented in the user file
   */
}
#endif /*!defined(CORE_CM0PLUS)*/


/**
  * @brief  EXTI line falling detection callback.
  * @param  GPIO_Pin Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
__weak void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Falling_Callback could be implemented in the user file
   */
}
#if !defined(CORE_CM0PLUS)
__weak void HAL_GPIO_EXTI1_Falling_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Rising_Callback could be implemented in the user file
   */
}
#endif /*!defined(CORE_CM0PLUS)*/
/**
  * @}
  */


/**
  * @brief  Configure RIF attribute of a GPIO pin bitmap.
  *         Available RIF attributes are CID, security and privilege protection.
  *         RIF attribute is applied on all pins of input param bitmap.
  * @note   If no CID attribute provide, CID filtering is disabled.
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin : gpio pin bitmap.
  * @param  PinAttributes: RIF (CID/secure/privilege) attributes.

  * @retval HAL Status.

  */
HAL_StatusTypeDef HAL_GPIO_ConfigPinAttributes(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t PinAttributes)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __IO uint32_t *regaddr;


  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ATTRIBUTES(PinAttributes));

  /* Configure the port pins */
  while ((GPIO_Pin >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = GPIO_Pin & (1uL << position);
    if (iocurrent != 0U)
    {
#if defined (CORTEX_IN_SECURE_STATE)
      if ((PinAttributes & GPIO_PIN_ATTR_SEC_SELECT) == GPIO_PIN_ATTR_SEC_SELECT)
      {
        /* Configure secure/non-secure attribute */
        if ((PinAttributes & GPIO_PIN_SEC) == GPIO_PIN_SEC)
        {
          GPIOx->SECCFGR |= iocurrent;
        }
        else
        {
          GPIOx->SECCFGR &= (~iocurrent);
        }
      }
#endif  /* CORTEX_IN_SECURE_STATE */
      if ((PinAttributes & GPIO_PIN_ATTR_PRIV_SELECT) == GPIO_PIN_ATTR_PRIV_SELECT)
      {
        /* Configure privilege/non-privilege attribute */
        if ((PinAttributes & GPIO_PIN_PRIV) == GPIO_PIN_PRIV)
        {
          GPIOx->PRIVCFGR |= iocurrent;
        }
        else
        {
          GPIOx->PRIVCFGR &= (~iocurrent);
        }
      }
      regaddr = &GPIOx->CIDCFGR0 + (GPIO_CIDCFGR_OFFSET * position);
      *regaddr = 0;  /*remove any CID filtering on selected pin*/
      if ((PinAttributes & (GPIO_PIN_CID_DISABLE | GPIO_PIN_ATTR_CID_STATIC_SELECT)) == GPIO_PIN_ATTR_CID_STATIC_SELECT)
        /*static CID field value used ONLY is CID filtering not disable */
      {
        /* Write static CID configuration */
        *regaddr = ((PinAttributes & GPIO_CIDCFGR0_SCID_Msk) | GPIO_CIDCFGR0_CFEN);
      }
      if ((PinAttributes & (GPIO_PIN_CID_DISABLE | GPIO_PIN_ATTR_CID_SHARED_SELECT)) == GPIO_PIN_ATTR_CID_SHARED_SELECT)
        /*shared CID field value used ONLY is CID filtering not disable */
      {
        /* Write shared CID configuration */
        *regaddr = ((PinAttributes & GPIO_PIN_ATTR_CID_SHARED_MASK) | GPIO_CIDCFGR0_SEM_EN | GPIO_CIDCFGR0_CFEN);
      }
    }
    position++;
  }
  return HAL_OK;
}


/**
  * @brief  Get a RIF attributes a single GPIO pin.
  * @note   In case input bitmap selects several pins, RIF attributes of first low rank pin is returned
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin : gpio pin bitmap, should select only ONE pin
  * @param  pPinAttributes: pointer of  RIF attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_GPIO_GetConfigPinAttributes(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                                  uint32_t *pPinAttributes)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __I uint32_t *regaddr;

  /* Check null pointer */
  if (pPinAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin) && (GPIO_Pin != GPIO_PIN_ALL));
  *pPinAttributes = 0;

  /* Get secure attribute of the port pin */
  while ((GPIO_Pin >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = (GPIO_Pin & (1UL << position));

    if (iocurrent != 0U)
    {
#if defined (CORTEX_IN_SECURE_STATE)
      *pPinAttributes |= ((GPIOx->SECCFGR & iocurrent) == 0U) ? GPIO_PIN_NSEC : GPIO_PIN_SEC;
#endif  /* CORTEX_IN_SECURE_STATE */
      *pPinAttributes |= ((GPIOx->PRIVCFGR & iocurrent) == 0U) ? GPIO_PIN_NPRIV : GPIO_PIN_PRIV;
      regaddr = &GPIOx->CIDCFGR0 + (GPIO_CIDCFGR_OFFSET * position);
      if ((*regaddr & GPIO_CIDCFGR0_CFEN_Msk) == GPIO_CIDCFGR0_CFEN)
      {
        if ((*regaddr & GPIO_CIDCFGR0_SEM_EN_Msk) == GPIO_CIDCFGR0_SEM_EN)
        {
          /* Get CIDs value from Semaphore white list */
          *pPinAttributes |= ((GPIO_PIN_ATTR_CID_SHARED_SELECT) |
                              (((*regaddr)) &
                               (GPIO_CIDCFGR0_SEMWLC3_Msk |
                                GPIO_CIDCFGR0_SEMWLC2_Msk |
                                GPIO_CIDCFGR0_SEMWLC1_Msk |
                                GPIO_CIDCFGR0_SEMWLC0_Msk)));
        }
        else
        {
          /* Get CIDs value from Static CID field and translate it in bitfield value as
           * defined by GPIO attribute definition */
          *pPinAttributes |= (GPIO_PIN_ATTR_CID_STATIC_SELECT | ((*regaddr) & GPIO_CIDCFGR0_SCID_Msk));
        }
      }
      else
      {
        *pPinAttributes |= GPIO_PIN_CID_DISABLE;
      }
      break;
    }
    position++;
  }

  return HAL_OK;
}

/**
  * @brief  Attempt to acquire semaphore(s) of  GPIO pin bitmap.
  * @note   In case of semaphore acquisition failure, returned status is HAL_KO and
  *         semaphore acquisition is abandoned  for all bitmap
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin : gpio pin bitmap
  * @retval HAL Status, HAL_OK if semaphore acquisition for all pins of GPIO_Pin is successful
  */

HAL_StatusTypeDef HAL_GPIO_TakePinSemaphore(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  uint32_t cidcurrent;
  uint32_t msk = 0x00;
  __IO uint32_t *regaddr;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

#if defined(CORE_CM0PLUS)
  cidcurrent = RIF_CID_CPU3_CM0;
#endif  /* CORE_CM0PLUS */
#if defined(CORE_CM33)
  cidcurrent = RIF_CID_CPU2_CM33;
#endif  /* CORE_CM33 */
#if defined(CORE_CA35)
  cidcurrent = RIF_CID_CPU1_CA35;
#endif  /* CORE_CA35 */
  /* Get secure attribute of the port pin */
  while ((GPIO_Pin >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = GPIO_Pin & (1UL << position);
    if (iocurrent != 0U)
    {
      /* Take Semaphore*/
      regaddr = &GPIOx->SEMCR0 + (GPIO_SEMCFGR_OFFSET * position);
      *regaddr = GPIO_SEMCR0_SEM_MUTEX;
      if (((*regaddr) & GPIO_SEMCR0_SEMCID_Msk) != (cidcurrent << GPIO_SEMCR0_SEMCID_Pos))
      {
        /* Mutex not taken with current CID - it means that other authorized CID has control,
         * all previous acquired semaphores (if any) shall be released and status error is returned */
        if ((GPIO_Pin & msk) != 0U)
        {
          (void)HAL_GPIO_ReleasePinSemaphore(GPIOx, (GPIO_Pin & (uint16_t)msk));
        }
        return HAL_ERROR;
      }
    }
    msk += (1UL << position);
    position++;
  }
  return HAL_OK;
}

/**
  * @brief  Release semaphore(s) of  GPIO pin bitmap.
  * @param  GPIOx : pointer to GPIO peripheral instance
  * @param  GPIO_Pin : gpio pin bitmap
  * @retval HAL Status, HAL_OK
  */
HAL_StatusTypeDef HAL_GPIO_ReleasePinSemaphore(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t position = 0x00;
  uint32_t iocurrent;
  __IO uint32_t *regaddr;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* Get secure attribute of the port pin */
  while ((GPIO_Pin >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = GPIO_Pin & (1UL << position);
    if (iocurrent != 0U)
    {
      /* Release Semaphore*/
      regaddr = &GPIOx->SEMCR0 + (GPIO_SEMCFGR_OFFSET * position);
      *regaddr = ~GPIO_SEMCR0_SEM_MUTEX;
    }
    position++;
  }
  return HAL_OK;
}


/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_GPIO_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
