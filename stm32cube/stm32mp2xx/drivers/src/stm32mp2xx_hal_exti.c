/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_exti.c
  * @author  MCD Application Team
  * @brief   EXTI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (EXTI) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *
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
  @verbatim
  ==============================================================================
                    ##### EXTI Peripheral features #####
  ==============================================================================
  [..]
    (+) Each Exti line can be configured within this driver.

    (+) Exti line can be configured in 3 different modes
        (++) Interrupt
        (++) Event
        (++) Both of them

    (+) Configurable Exti lines can be configured with 3 different triggers
        (++) Rising
        (++) Falling
        (++) Both of them

    (+) When set in interrupt mode, configurable Exti lines have two diffenrents
        interrupt pending registers which allow to distinguish which transition
        occurs:
        (++) Rising edge pending interrupt
        (++) Falling

    (+) Exti lines 0 to 15 are linked to gpio pin number 0 to 15. Gpio port can
        be selected through multiplexer.

                     ##### How to use this driver #####
  ==============================================================================
  [..]

    (#) Configure the EXTI line using HAL_EXTI_SetConfigLine().
        (++) Choose the interrupt line number by setting "Line" member from
             EXTI_ConfigTypeDef structure.
        (++) Configure the interrupt and/or event mode using "Mode" member from
             EXTI_ConfigTypeDef structure.
        (++) For configurable lines, configure rising and/or falling trigger
             "Trigger" member from EXTI_ConfigTypeDef structure.
        (++) For Exti lines linked to gpio, choose gpio port using "GPIOSel"
             member from GPIO_InitTypeDef structure.

    (#) Get current Exti configuration of a dedicated line using
        HAL_EXTI_GetConfigLine().
        (++) Provide exiting handle as parameter.
        (++) Provide pointer on EXTI_ConfigTypeDef structure as second parameter.

    (#) Clear Exti configuration of a dedicated line using HAL_EXTI_GetConfigLine().
        (++) Provide exiting handle as parameter.

    (#) Register callback to treat Exti interrupts using HAL_EXTI_RegisterCallback().
        (++) Provide exiting handle as first parameter.
        (++) Provide which callback will be registered using one value from
             EXTI_CallbackIDTypeDef.
        (++) Provide callback function pointer.

    (#) Get interrupt pending bit using HAL_EXTI_GetPending().

    (#) Clear interrupt pending bit using HAL_EXTI_GetPending().

    (#) Generate software interrupt using HAL_EXTI_GenerateSWI().

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"


/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

#ifdef HAL_EXTI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines ------------------------------------------------------------*/
/** @addtogroup EXTI_Private_Constants EXTI Private Constants
  * @{
  */

/* to use legacy connector */
/*#define HAL_EXTI_USE_CONNECTOR*/

#define EXTI_MODE_OFFSET                  0x04U  /* 0x10=4*4: offset between IMR#i IMR#(i+1) registers */
#define EXTI_CONFIG_OFFSET                0x08U  /* 0x20=4*8: offset between (R/F)TSR#i and (R/F)TSR#(i+1) registers */
#define EXTI_LINE_CID_CFG_ADD_OFFSET      0x01U
#define CPU_CONNECTOR_CID_CFG_ADD_OFFSET  0x01U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype -----------------------------------------------*/
#if defined (CORE_CA35) || defined (CORE_CM33)
uint32_t  EXTI_Exti1_GetImr1();
uint32_t  EXTI_Exti1_GetImr2();
uint32_t  EXTI_Exti1_GetImr3();
uint32_t  EXTI_Exti1_GetEmr3();
void      EXTI_Exti1_SetEmr3(uint32_t u32Value);
void      EXTI_Exti1_SetImr1(uint32_t u32Value);
void      EXTI_Exti1_SetImr2(uint32_t u32Value);
void      EXTI_Exti1_SetImr3(uint32_t u32Value);
void      EXTI_Exti1_SetImr(uint32_t u32Offset, uint32_t u32Value);
uint32_t  EXTI_Exti1_GetImr(uint32_t u32Offset);
void      EXTI_Exti1_SetEmr(uint32_t u32Offset, uint32_t u32Value);
uint32_t  EXTI_Exti1_GetEmr(uint32_t u32Offset);
uint32_t  EXTI_Exti1_GetEmr1(void);
void      EXTI_Exti1_SetEmr1(uint32_t u32Value);
uint32_t  EXTI_Exti1_CheckImr(uint32_t u32Offset);
uint32_t  EXTI_Exti2_CheckEmr(uint32_t u32Offset);
uint32_t  EXTI_Exti1_GetRtsr(uint32_t u32Offset);
uint32_t  EXTI_Exti2_GetRtsr(uint32_t u32Offset);
uint32_t  EXTI_Exti1_GetFtsr(uint32_t u32Offset);
uint32_t  EXTI_Exti2_GetFtsr(uint32_t u32Offset);
uint32_t  EXTI_Exti1_CheckEmr(uint32_t u32Offset);
#endif  /* CORE_CA35 | CORE_CM33 */

uint32_t  EXTI_Exti2_GetImr1();
uint32_t  EXTI_Exti2_GetImr2();
uint32_t  EXTI_Exti2_GetImr3();
uint32_t  EXTI_Exti2_GetEmr1();
uint32_t  EXTI_Exti2_GetEmr2();
void      EXTI_Exti2_SetImr1(uint32_t u32Value);
void      EXTI_Exti2_SetImr2(uint32_t u32Value);
void      EXTI_Exti2_SetImr3(uint32_t u32Value);
void      EXTI_Exti2_SetEmr1(uint32_t u32Value);
void      EXTI_Exti2_SetEmr2(uint32_t u32Value);
void      EXTI_Exti2_SetEmr(uint32_t u32Offset, uint32_t u32Value);
void      EXTI_Exti2_SetImr(uint32_t u32Offset, uint32_t u32Value);
uint32_t  EXTI_Exti2_GetEmr(uint32_t u32Offset);
uint32_t  EXTI_Exti2_GetImr(uint32_t u32Offset);

void      EXTI_SetImr(const EXTI_TypeDef *Instance, uint32_t u32Offset, uint32_t u32Value);
uint32_t  EXTI_GetImr(const EXTI_TypeDef *Instance, uint32_t u32Offset);
void      EXTI_SetEmr(const EXTI_TypeDef *Instance, uint32_t u32Offset, uint32_t u32Value);
uint32_t  EXTI_GetEmr(const EXTI_TypeDef *Instance, uint32_t u32Offset);
uint32_t  EXTI_CheckEmr(const EXTI_TypeDef *Instance, uint32_t u32Offset);

uint32_t  EXTI_GetRtsr(const EXTI_TypeDef *Instance, uint32_t u32Offset);
uint32_t  EXTI_GetFtsr(const EXTI_TypeDef *Instance, uint32_t u32Offset);

#ifdef HAL_EXTI_USE_CONNECTOR
static EXTI_Core_TypeDef *getExtiConnector(EXTI_HandleTypeDef *hexti)
{
  if (hexti->Instance == EXTI2)
  {
#if defined(CORE_CM0PLUS)
    return EXTI2_C3;
#endif  /* CORE_CM0PLUS */
#if defined(CORE_CM33)
    return EXTI2_C2;
#endif  /* CORE_CM33 */
#if defined(CORE_CA35)
    return EXTI2_C1;
#endif  /* CORE_CA35 */
  }
  else
  {
#if defined(EXTI1)
#if defined(CORE_CM33)
    return EXTI1_C2;
#endif  /* CORE_CM33 */
#if defined(CORE_CA35)
    return EXTI1_C1;
#endif  /* CORE_CA35 */
#else   /* EXTI1 */
    return NULL;
#endif  /* EXTI1 */
  }
}
#endif  /* HAL_EXTI_USE_CONNECTOR */
/* Exported functions --------------------------------------------------------*/

/** @addtogroup EXTI_Exported_Functions
  * @{
  */

/** @addtogroup EXTI_Exported_Functions_Group1
  *  @brief    Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Set configuration of a dedicated Exti line.
  * @param  hexti Exti handle to initialize from pExtiConfig config.
  * @param  pExtiConfig Pointer on EXTI configuration to be set.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, const EXTI_ConfigTypeDef *pExtiConfig)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;
#ifdef HAL_EXTI_USE_CONNECTOR
  EXTI_Core_TypeDef *EXTI_CurrentCPU;
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Check null pointer */
  if ((hexti == NULL) || (pExtiConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_EXTI_LINE(pExtiConfig->Line));
  assert_param(IS_EXTI_MODE(pExtiConfig->Mode));

  if ((pExtiConfig->Line & EXTI_INDEX_MASK) ==  EXTI_EXTI2)
  {
    hexti->Instance = EXTI2;
  }
  else
  {
#if defined(CORE_CM0PLUS)
    /* EXTI1 can't be accessed from M0Plus */
    return HAL_ERROR;
#else   /* CORE_CM0PLUS */
    hexti->Instance = EXTI1;
#endif  /* CORE_CM0PLUS */
  }

  /* get address of used CPU connector interface */
#ifdef HAL_EXTI_USE_CONNECTOR
  EXTI_CurrentCPU = getExtiConnector(hexti);
  if (EXTI_CurrentCPU == NULL)
  {
    return HAL_ERROR;
  }
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Assign line config to handle */
  hexti->Line = pExtiConfig->Line;

  /* compute line register offset and line mask */
  linepos = pExtiConfig->Line & EXTI_PIN_MASK;
  offset = linepos / 32U;
  maskline = 1UL << (linepos % 32U);

  /* Configure triggers for configurable lines */
  if ((pExtiConfig->Line & EXTI_CONFIG) != 0U)
  {
    assert_param(IS_EXTI_TRIGGER(pExtiConfig->Trigger));

    /* Configure rising trigger */
    regaddr = &hexti->Instance->RTSR1 + (EXTI_CONFIG_OFFSET * offset);

    regval = *regaddr;

    /* Mask or set line */
    if ((pExtiConfig->Trigger & EXTI_TRIGGER_RISING) != 0U)
    {
      regval |= maskline;
    }
    else
    {
      regval &= ~maskline;
    }

    /* Store rising trigger mode */
    *regaddr = regval;

    /* Configure falling trigger */
    regaddr = &hexti->Instance->FTSR1 + (EXTI_CONFIG_OFFSET * offset);
    regval = *regaddr;

    /* Mask or set line */
    if ((pExtiConfig->Trigger & EXTI_TRIGGER_FALLING) != 0U)
    {
      regval |= maskline;
    }
    else
    {
      regval &= ~maskline;
    }

    /* Store falling trigger mode */
    *regaddr = regval;

    /* Configure gpio port selection in case of gpio exti line */
    if ((pExtiConfig->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      assert_param(IS_EXTI_GPIO_PORT(hexti->Instance, pExtiConfig->GPIOSel));
      assert_param(IS_EXTI_GPIO_PIN(hexti->Instance, linepos));

      /* sanity check for EXTICR access */
      if (linepos < 16U)
      {
        regval = hexti->Instance->EXTICR[linepos >> 2u];
        regval &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (linepos & 0x03u)));
        regval |= (pExtiConfig->GPIOSel << (EXTI_EXTICR1_EXTI1_Pos * (linepos & 0x03u)));
        hexti->Instance->EXTICR[linepos >> 2u] = regval;
      }
    }
  }

  /* Configure interrupt mode : read current mode */
#ifdef HAL_EXTI_USE_CONNECTOR
  regaddr = (uint32_t *)(&EXTI_CurrentCPU->IMR1 + (EXTI_MODE_OFFSET * offset));
  regval = *regaddr;
#else   /* HAL_EXTI_USE_CONNECTOR */
  regval = EXTI_GetImr(hexti->Instance, offset);
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Mask or set line */
  if ((pExtiConfig->Mode & EXTI_MODE_INTERRUPT) != 0U)
  {
    regval |= maskline;
  }
  else
  {
    regval &= ~maskline;
  }

  /* Store interrupt mode */
#ifdef HAL_EXTI_USE_CONNECTOR
  *regaddr = regval;
#else   /* HAL_EXTI_USE_CONNECTOR */
  EXTI_SetImr(hexti->Instance, offset, regval);
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Configure event mode : read current mode */
  if (EXTI_CheckEmr(hexti->Instance, offset) == 1U)
  {
#ifdef HAL_EXTI_USE_CONNECTOR
    regaddr = (uint32_t *)(&EXTI_CurrentCPU->EMR1 + (EXTI_MODE_OFFSET * offset));
    regval = *regaddr;
#else   /* HAL_EXTI_USE_CONNECTOR */
    regval = EXTI_GetEmr(hexti->Instance, offset);
#endif  /* HAL_EXTI_USE_CONNECTOR */

    /* Mask or set line */
    if ((pExtiConfig->Mode & EXTI_MODE_EVENT) != 0U)
    {
      /* The event mode cannot be configured if the line does not support it */
      assert_param(IS_EXTI_EVENT_PRESENT(pExtiConfig->Line));
      regval |= maskline;
    }
    else
    {
      regval &= ~maskline;
    }

    /* Store event mode */
#ifdef HAL_EXTI_USE_CONNECTOR
    *regaddr = regval;
#else   /* HAL_EXTI_USE_CONNECTOR */
    EXTI_SetEmr(hexti->Instance, offset, regval);
#endif  /* HAL_EXTI_USE_CONNECTOR */
  }

  return HAL_OK;
}


/**
  * @brief  Get configuration of a dedicated Exti line.
  * @param  hexti Exti handle.
  * @param  pExtiConfig Pointer on structure to store Exti configuration.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig)
{
#ifdef HAL_EXTI_USE_CONNECTOR
  __IO uint32_t *regaddr;
#endif  /* HAL_EXTI_USE_CONNECTOR */
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;
#ifdef HAL_EXTI_USE_CONNECTOR
  EXTI_Core_TypeDef *EXTI_CurrentCPU;
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Check null pointer */
  if ((hexti == NULL) || (pExtiConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameter */
  assert_param(IS_EXTI_LINE(hexti->Line));


#ifdef HAL_EXTI_USE_CONNECTOR
  /* get address of used CPU connector interface */
  EXTI_CurrentCPU = getExtiConnector(hexti);
  if (EXTI_CurrentCPU == NULL)
  {
    return HAL_ERROR;
  }
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Store handle line number to configure structure */
  pExtiConfig->Line = hexti->Line;

  /* compute line register offset and line mask */
  linepos = (pExtiConfig->Line & EXTI_PIN_MASK);
  offset = linepos / 32U;
  maskline = 1uL << (linepos % 32U);

  /* 1] Get core mode : interrupt */
#ifdef HAL_EXTI_USE_CONNECTOR
  regaddr = (uint32_t *)(&EXTI_CurrentCPU->IMR1 + (EXTI_MODE_OFFSET * offset));
  regval = *regaddr;
#else   /* HAL_EXTI_USE_CONNECTOR */
  regval = EXTI_GetImr(hexti->Instance, offset);
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Check if selected line is enable */
  if ((regval & maskline) != 0U)
  {
    pExtiConfig->Mode = EXTI_MODE_INTERRUPT;
  }
  else
  {
    pExtiConfig->Mode = EXTI_MODE_NONE;
  }

  /* Get event mode */
#ifdef HAL_EXTI_USE_CONNECTOR
  regaddr = (uint32_t *)(&EXTI_CurrentCPU->EMR1 + (EXTI_MODE_OFFSET * offset));
  regval = *regaddr;
#else   /* HAL_EXTI_USE_CONNECTOR */
  regval = EXTI_GetEmr(hexti->Instance, offset);
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* Check if selected line is enable */
  if ((regval & maskline) != 0U)
  {
    pExtiConfig->Mode |= EXTI_MODE_EVENT;
  }

  /* 2] Get trigger for configurable lines : rising */
  if ((pExtiConfig->Line & EXTI_CONFIG) != 0x00u)
  {
#ifdef HAL_EXTI_USE_CONNECTOR
    regaddr = &hexti->Instance->RTSR1 + (EXTI_CONFIG_OFFSET * offset);
    regval = *regaddr;
#else   /* HAL_EXTI_USE_CONNECTOR */
    regval = EXTI_GetRtsr(hexti->Instance, offset);
#endif  /* HAL_EXTI_USE_CONNECTOR */

    /* Check if configuration of selected line is enable */
    if ((regval & maskline) != 0x00u)
    {
      pExtiConfig->Trigger = EXTI_TRIGGER_RISING;
    }
    else
    {
      pExtiConfig->Trigger = EXTI_TRIGGER_NONE;
    }

    /* Get falling configuration */
#ifdef HAL_EXTI_USE_CONNECTOR
    regaddr = &hexti->Instance->FTSR1 + (EXTI_CONFIG_OFFSET * offset);
    regval = *regaddr;
#else   /* HAL_EXTI_USE_CONNECTOR */
    regval = EXTI_GetFtsr(hexti->Instance, offset);
#endif  /* HAL_EXTI_USE_CONNECTOR */

    /* Check if configuration of selected line is enable */
    if ((regval & maskline) != 0U)
    {
      pExtiConfig->Trigger |= EXTI_TRIGGER_FALLING;
    }

    /* Get Gpio port selection for gpio lines */
    if ((pExtiConfig->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      regval = hexti->Instance->EXTICR[(linepos >> 2U) & 0x03UL];
      pExtiConfig->GPIOSel = (
                               (
                                 regval <<
                                 (EXTI_EXTICR1_EXTI1_Pos * (((32u / EXTI_EXTICR1_EXTI1_Pos) - 1u) - (linepos & 0x03u)))
                               ) >> (32u - EXTI_EXTICR1_EXTI1_Pos)
                             );
    }
    else
    {
      pExtiConfig->GPIOSel = 0U;
    }
  }
  else
  {
    pExtiConfig->Trigger = EXTI_TRIGGER_NONE;
    pExtiConfig->GPIOSel = 0U;
  }

  return HAL_OK;
}


/**
  * @brief  Clear whole configuration of a dedicated Exti line.
  * @param  hexti Exti handle.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;
#ifdef HAL_EXTI_USE_CONNECTOR
  EXTI_Core_TypeDef *EXTI_CurrentCPU;
#endif  /* HAL_EXTI_USE_CONNECTOR */


  /* Check null pointer */
  if (hexti == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameter */
  assert_param(IS_EXTI_LINE(hexti->Line));


#ifdef HAL_EXTI_USE_CONNECTOR
  /* get address of used CPU connector interface */
  EXTI_CurrentCPU = getExtiConnector(hexti);
  if (EXTI_CurrentCPU == NULL)
  {
    return HAL_ERROR;
  }
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* compute line register offset and line mask */
  linepos = (hexti->Line & EXTI_PIN_MASK);
  offset = linepos / 32U;
  maskline = 1UL << (linepos % 32U);

  /* 1] Clear interrupt mode */
#ifdef HAL_EXTI_USE_CONNECTOR
  regaddr = (uint32_t *)(&EXTI_CurrentCPU->IMR1 + (EXTI_MODE_OFFSET * offset));
  regval = (*regaddr & ~maskline);
  *regaddr = regval;
#else   /* HAL_EXTI_USE_CONNECTOR */
  regval = EXTI_GetImr(hexti->Instance, offset);
  regval &= ~maskline;
  EXTI_Exti2_SetImr(offset, regval);
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* 2] Clear event mode */
#ifdef HAL_EXTI_USE_CONNECTOR
  regaddr = (uint32_t *)(&EXTI_CurrentCPU->EMR1 + (EXTI_MODE_OFFSET * offset));
  regval = (*regaddr & ~maskline);
  *regaddr = regval;
#else   /* HAL_EXTI_USE_CONNECTOR */
  if (EXTI_CheckEmr(hexti->Instance, offset) == 1U)
  {
    regval = EXTI_GetEmr(hexti->Instance, offset);
    regval &= ~maskline;
    EXTI_SetEmr(hexti->Instance, offset, regval);
  }
#endif  /* HAL_EXTI_USE_CONNECTOR */

  /* 3] Clear triggers in case of configurable lines */
  if ((hexti->Line & EXTI_CONFIG) != 0U)
  {
    regaddr = &hexti->Instance->RTSR1 + (EXTI_CONFIG_OFFSET * offset);
    regval = (*regaddr & ~maskline);
    *regaddr = regval;

    regaddr = &hexti->Instance->FTSR1 + (EXTI_CONFIG_OFFSET * offset);
    regval = (*regaddr & ~maskline);
    *regaddr = regval;

    /* Get Gpio port selection for gpio lines */
    if ((hexti->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      /* sanity check for EXTICR access */
      if (linepos < 16U)
      {
        regval = hexti->Instance->EXTICR[linepos >> 2u];
        regval &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (linepos & 0x03u)));
        hexti->Instance->EXTICR[linepos >> 2U] = regval;
      }
    }
  }

  return HAL_OK;
}


/**
  * @brief  Register callback for a dedicaated Exti line.
  * @param  hexti Exti handle.
  * @param  CallbackID User callback identifier.
  *         This parameter can be one of @arg @ref EXTI_CallbackIDTypeDef values.
  * @param  pPendingCbfn function pointer to be stored as callback.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID,
                                            void (*pPendingCbfn)(void))
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check null pointer */
  if (hexti == NULL)
  {
    return HAL_ERROR;
  }

  switch (CallbackID)
  {
    case  HAL_EXTI_COMMON_CB_ID:
      hexti->RisingCallback = pPendingCbfn;
      hexti->FallingCallback = pPendingCbfn;
      break;

    case  HAL_EXTI_RISING_CB_ID:
      hexti->RisingCallback = pPendingCbfn;
      break;

    case  HAL_EXTI_FALLING_CB_ID:
      hexti->FallingCallback = pPendingCbfn;
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Store line number as handle private field.
  * @param  hexti Exti handle.
  * @param  ExtiLine Exti line number.
  *         This parameter can be either 0 to @ref EXTI1_LINE_NB or 0 to @ref EXTI2_LINE_NB.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine)
{

  /* Check null pointer */
  if (hexti == NULL)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Check the parameters */
    assert_param(IS_EXTI_LINE(ExtiLine));

    /* Store line number as handle private field */
    hexti->Line = ExtiLine;

    /*Store instance as handle private field*/
    if ((ExtiLine & EXTI_INDEX_MASK) ==  EXTI_EXTI2)
    {
      hexti->Instance = EXTI2;
    }
    else
    {
#if defined(CORE_CM0PLUS)
      /* EXTI1 can't be accessed from M0Plus */
      return HAL_ERROR;
#else   /* CORE_CM0PLUS */
      hexti->Instance = EXTI1;
#endif  /* CORE_CM0PLUS */
    }
    return HAL_OK;
  }
}


/**
  * @}
  */

/** @addtogroup EXTI_Exported_Functions_Group2
  *  @brief EXTI IO functions.
  *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Handle EXTI interrupt request.
  * @param  hexti Exti handle.
  * @retval none.
  */
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t maskline;
  uint32_t linepos;
  uint32_t offset;

  /* Compute line register offset and line mask */
  linepos = (hexti->Line & EXTI_PIN_MASK);
  offset = linepos / 32U;
  maskline = 1UL << (linepos % 32U);

  /* Get pending bit  */
  regaddr = &hexti->Instance->RPR1 + (EXTI_CONFIG_OFFSET * offset);
  regval = (*regaddr & maskline);

  if (regval != 0U)
  {
    /* Clear pending bit */
    *regaddr = maskline;

    /* Call rising callback */
    if (hexti->RisingCallback != NULL)
    {
      hexti->RisingCallback();
    }
  }

  /* Get pending bit  */
  regaddr = &hexti->Instance->FPR1 + (EXTI_CONFIG_OFFSET * offset);
  regval = (*regaddr & maskline);

  if (regval != 0U)
  {
    /* Clear pending bit */
    *regaddr = maskline;

    /* Call rising callback */
    if (hexti->FallingCallback != NULL)
    {
      hexti->FallingCallback();
    }
  }
}


/**
  * @brief  Get interrupt pending bit of a dedicated line.
  * @param  hexti Exti handle.
  * @param  Edge Specify which pending edge as to be checked.
  *         This parameter can be one of the following values:
  *           @arg @ref EXTI_TRIGGER_RISING
  *           @arg @ref EXTI_TRIGGER_FALLING
  *           @arg @ref EXTI_TRIGGER_RISING_FALLING
  * @retval 1 if interrupt is pending else 0.
  */
uint32_t HAL_EXTI_GetPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge)
{
  const __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t maskline;
  uint32_t linepos;
  uint32_t offset;

  /* Check parameters */
  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));
  assert_param(IS_EXTI_PENDING_EDGE(Edge));

  /* compute line register offset and line mask */
  linepos = (hexti->Line & EXTI_PIN_MASK);
  offset = linepos / 32U;
  maskline = 1UL << (linepos % 32U);

  /* Get rising pending bit */
  if ((Edge & EXTI_TRIGGER_RISING) == EXTI_TRIGGER_RISING)
  {
    regaddr = (__IO uint32_t *)(&hexti->Instance->RPR1 + (EXTI_CONFIG_OFFSET * offset));

    /* return 1 if bit is set else 0 */
    regval = (*regaddr & maskline);

    if (regval != 0U)
    {
      return 1;
    }
  }
  /* Get falling pending bit */
  if ((Edge & EXTI_TRIGGER_FALLING) == EXTI_TRIGGER_FALLING)
  {
    regaddr = &hexti->Instance->FPR1 + (EXTI_CONFIG_OFFSET * offset);

    /* return 1 if bit is set else 0 */
    regval = (*regaddr & maskline);
    if (regval != 0U)
    {
      return 1;
    }
  }

  return 0;
}


/**
  * @brief  Clear interrupt pending bit of a dedicated line.
  * @param  hexti Exti handle.
  * @param  Edge Specify which pending edge as to be clear.
  *         This parameter can be one of the following values:
  *           @arg @ref EXTI_TRIGGER_RISING
  *           @arg @ref EXTI_TRIGGER_FALLING
  *           @arg @ref EXTI_TRIGGER_RISING_FALLING
  * @retval None.
  */
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge)
{
  __IO uint32_t *regaddr;
  uint32_t maskline;
  uint32_t linepos;
  uint32_t offset;


  if (hexti == NULL)
  {
    return;
  }

  /* Check parameters */
  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));
  assert_param(IS_EXTI_PENDING_EDGE(Edge));

  /* compute line register offset and line mask */
  linepos = (hexti->Line & EXTI_PIN_MASK);
  offset = linepos / 32U;
  maskline = 1UL << (linepos % 32U);

  if ((Edge & EXTI_TRIGGER_RISING) == EXTI_TRIGGER_RISING)
  {
    /* Get pending register address */
    regaddr = &hexti->Instance->RPR1 + (EXTI_CONFIG_OFFSET * offset);

    /* Clear Pending bit */
    *regaddr =  maskline;
  }
  if ((Edge & EXTI_TRIGGER_FALLING) == EXTI_TRIGGER_FALLING)
  {
    /* Get pending register address */
    regaddr = &hexti->Instance->FPR1 + (EXTI_CONFIG_OFFSET * offset);

    /* Clear Pending bit */
    *regaddr =  maskline;
  }

}


/**
  * @brief  Generate a software interrupt for a dedicated line.
  * @param  hexti Exti handle.
  * @retval None.
  */
void HAL_EXTI_GenerateSWI(const EXTI_HandleTypeDef *hexti)
{
  __IO uint32_t *regaddr;
  uint32_t maskline;
  uint32_t linepos;
  uint32_t offset;

  if (hexti == NULL)
  {
    return;
  }

  /* Check the parameter */
  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));

  /* compute line register offset and line mask */
  linepos = (hexti->Line & EXTI_PIN_MASK);
  offset = linepos / 32U;
  maskline = 1uL << (linepos % 32U);

  regaddr = &hexti->Instance->SWIER1 + (EXTI_CONFIG_OFFSET * offset);
  *regaddr = maskline;
}

/**
  * @}
  */


/* Register Access control  functions  *******************************************/
/** @addtogroup EXTI_Exported_Functions_Group3 Register Access control functions
  * @{
  */


/**
  * @brief  Configure RIF attribute of an EXTI event line
  *         Available RIF attributes are CID, security and privilege protection.
  * @note   If no CID attribute provide, CID filtering is disabled.
  * @param  ExtiLine : Exti line number.
  * @param  LineAttributes: RIF (CID/secure/privilege) attributes.

  * @retval void.

  */
void HAL_EXTI_ConfigLineAttributes(uint32_t ExtiLine, uint32_t LineAttributes)
{
  __IO uint32_t *regaddr;
  __IO uint32_t *regaddrP;
#if defined (CORTEX_IN_SECURE_STATE)
  __IO uint32_t *regaddrS;
#endif  /* CORTEX_IN_SECURE_STATE */
  uint32_t eventCurrent;
  uint32_t linepos;
  uint32_t offset;
  EXTI_TypeDef *Instance;

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(ExtiLine));
  assert_param(IS_EXTI_LINE_ATTRIBUTES(LineAttributes));

  /* compute line register offset and line mask */
  linepos = (ExtiLine & EXTI_PIN_MASK);
  offset = linepos / 32U;

  if ((ExtiLine & EXTI_INDEX_MASK) ==  EXTI_EXTI2)
  {
    Instance = EXTI2;
  }
  else
  {
#if defined(CORE_CM0PLUS)
    /* EXTI1 can't be accessed from M0Plus */
    return;
#else   /* CORE_CM0PLUS */
    Instance = EXTI1;
#endif  /* CORE_CM0PLUS */
  }

  /* Configure Event attribute */
#if defined (CORTEX_IN_SECURE_STATE)
  regaddrS = &Instance->SECCFGR1 + (EXTI_CONFIG_OFFSET * offset);
#endif  /* CORTEX_IN_SECURE_STATE */
  regaddrP = &Instance->PRIVCFGR1 + (EXTI_CONFIG_OFFSET * offset);

  eventCurrent = 1UL << (linepos % 32UL);

#if defined (CORTEX_IN_SECURE_STATE)
  if ((LineAttributes & EXTI_LINE_ATTR_SEC_SELECT) == EXTI_LINE_ATTR_SEC_SELECT)
  {
    /* Configure secure/non-secure attribute */
    if ((LineAttributes & EXTI_LINE_SEC) == EXTI_LINE_SEC)
    {
      *regaddrS |= eventCurrent;
    }
    else
    {
      *regaddrS &= (~eventCurrent);
    }
  }
#endif  /* CORTEX_IN_SECURE_STATE */
  if ((LineAttributes & EXTI_LINE_ATTR_PRIV_SELECT) == EXTI_LINE_ATTR_PRIV_SELECT)
  {
    /* Configure privilege/non-privilege attribute */
    if ((LineAttributes & EXTI_LINE_PRIV) == EXTI_LINE_PRIV)
    {
      *regaddrP |= eventCurrent;
    }
    else
    {
      *regaddrP &= (~eventCurrent);
    }
  }
  /* Selected register corresponding to current event */
  regaddr = &Instance->ECIDCFGR[0] + (EXTI_LINE_CID_CFG_ADD_OFFSET * linepos);
  *regaddr = 0;  /*remove any CID filtering on selected pin*/
  if ((LineAttributes & (EXTI_LINE_CID_DISABLE | EXTI_LINE_ATTR_CID_STATIC_SELECT)) == EXTI_LINE_ATTR_CID_STATIC_SELECT)
    /*static CID field value used ONLY is CID filtering not disable */
  {
    /* Write static CID configuration */
    *regaddr = ((LineAttributes & EXTI_EnCIDCFGR_CID_Msk) | EXTI_EnCIDCFGR_CFEN);
  }
}

/**
  * @brief  Get a RIF attributes of an EXTI event line.
  * @param  ExtiLine : Exti line number.
  * @param  pLineAttributes : pointer of  RIF attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_GetConfigLineAttributes(uint32_t ExtiLine, uint32_t *pLineAttributes)
{
  __I uint32_t *regaddr;
  __I uint32_t *regaddrP;
#if defined (CORTEX_IN_SECURE_STATE)
  __IO uint32_t *regaddrS;
#endif  /* CORTEX_IN_SECURE_STATE */
  uint32_t eventCurrent;
  uint32_t offset;
  uint32_t linepos;
  const EXTI_TypeDef *Instance;

  /* Check null pointer */
  if (pLineAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(ExtiLine));
  *pLineAttributes = 0;

  /* compute line register offset and line mask */
  linepos = (ExtiLine & EXTI_PIN_MASK);
  offset = linepos / 32U;

  if ((ExtiLine & EXTI_INDEX_MASK) ==  EXTI_EXTI2)
  {
    Instance = EXTI2;
  }
  else
  {
#if defined(CORE_CM0PLUS)
    /* EXTI1 can't be accessed from M0Plus */
    return HAL_ERROR;
#else   /* CORE_CM0PLUS */
    Instance = EXTI1;
#endif  /* CORE_CM0PLUS */
  }

#if defined (CORTEX_IN_SECURE_STATE)
  regaddrS = (uint32_t *)&Instance->SECCFGR1 + (EXTI_CONFIG_OFFSET * offset);
#endif  /* CORTEX_IN_SECURE_STATE */
  regaddrP = &Instance->PRIVCFGR1 + (EXTI_CONFIG_OFFSET * offset);

  eventCurrent = 1UL << (linepos % 32UL);


#if defined (CORTEX_IN_SECURE_STATE)
  *pLineAttributes |= ((*regaddrS & eventCurrent)  == 0U) ? EXTI_LINE_NSEC  : EXTI_LINE_SEC;
#endif  /* CORTEX_IN_SECURE_STATE */
  *pLineAttributes |= ((*regaddrP & eventCurrent) == 0U) ? EXTI_LINE_NPRIV : EXTI_LINE_PRIV;

  /* Select register corresponding to current event */
  regaddr = &Instance->ECIDCFGR[0] + (EXTI_LINE_CID_CFG_ADD_OFFSET * linepos);
  if ((*regaddr & EXTI_EnCIDCFGR_CFEN_Msk) == EXTI_EnCIDCFGR_CFEN)
  {
    /* Get CIDs value from Static CID field */
    *pLineAttributes |= (EXTI_LINE_ATTR_CID_STATIC_SELECT | ((*regaddr) & EXTI_EnCIDCFGR_CID_Msk));
  }
  else
  {
    *pLineAttributes |= EXTI_LINE_CID_DISABLE;
  }
  return HAL_OK;
}

/**
  * @}
  */

#if defined (CORE_CA35) || defined (CORE_CM33)
/* EXTI1 can't be accessed from M0Plus */

uint32_t EXTI_Exti1_GetImr1(void)
{
#if defined (CORE_CA35)
  return EXTI1->C1IMR1;
#elif defined(CORE_CM33)
  return EXTI1->C2IMR1;
#endif  /* CORE_CA35 | CORE_CM33 */
}

uint32_t EXTI_Exti1_GetImr2(void)
{
#if defined (CORE_CA35)
  return EXTI1->C1IMR2;
#elif defined(CORE_CM33)
  return EXTI1->C2IMR2;
#endif  /* CORE_CA35 | CORE_CM33 */
}

uint32_t EXTI_Exti1_GetImr3(void)
{
#if defined (CORE_CA35)
  return EXTI1->C1IMR3;
#elif defined(CORE_CM33)
  return EXTI1->C2IMR3;
#endif  /* CORE_CA35 | CORE_CM33 */
}

void EXTI_Exti1_SetImr1(uint32_t u32Value)
{
#if defined (CORE_CA35)
  EXTI1->C1IMR1 = u32Value;
#elif defined(CORE_CM33)
  EXTI1->C2IMR1 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 */
}

void EXTI_Exti1_SetImr2(uint32_t u32Value)
{
#if defined (CORE_CA35)
  EXTI1->C1IMR2 = u32Value;
#elif defined(CORE_CM33)
  EXTI1->C2IMR2 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 */
}

void EXTI_Exti1_SetImr3(uint32_t u32Value)
{
#if defined (CORE_CA35)
  EXTI1->C1IMR3 = u32Value;
#elif defined(CORE_CM33)
  EXTI1->C2IMR3 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 */
}

uint32_t EXTI_Exti1_GetEmr1(void)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR1*/
  return 0;
#elif defined(CORE_CM33)
  return EXTI1->C2EMR1;
#endif  /* CORE_CA35 | CORE_CM33 */
}

uint32_t EXTI_Exti1_GetEmr3(void)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR3*/
  return 0;
#elif defined(CORE_CM33)
  return EXTI1->C2EMR3;
#endif  /* CORE_CA35 | CORE_CM33 */
}

void EXTI_Exti1_SetEmr1(uint32_t u32Value)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR1*/
  UNUSED(u32Value);
#elif defined(CORE_CM33)
  EXTI1->C2EMR1 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 */
}

void EXTI_Exti1_SetEmr3(uint32_t u32Value)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR3*/
  UNUSED(u32Value);
#elif defined(CORE_CM33)
  EXTI1->C2EMR3 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 */
}

void EXTI_Exti1_SetEmr(uint32_t u32Offset, uint32_t u32Value)
{
  /* EMR2 not available*/
  if (u32Offset == 0U)
  {
    EXTI_Exti1_SetEmr1(u32Value);
  }
  else if (u32Offset == 2U)
  {
    EXTI_Exti1_SetEmr3(u32Value);
  }
  else
  {
    /* Nothing to do */
  }
}

uint32_t EXTI_Exti1_GetEmr(uint32_t u32Offset)
{
  /* EMR2 not available*/
  if (u32Offset == 0U)
  {
    return EXTI_Exti1_GetEmr1();
  }
  else if (u32Offset == 2U)
  {
    return EXTI_Exti1_GetEmr3();
  }
  else
  {
    /* Nothing to do */
  }
  return 0;
}


uint32_t EXTI_Exti1_CheckEmr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return 1;
  }
  else if (u32Offset == 1U)
  {
    /* EMR2 not available*/
    return 0;
  }
  else if (u32Offset == 2U)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


void EXTI_Exti1_SetImr(uint32_t u32Offset, uint32_t u32Value)
{
  if (u32Offset == 0U)
  {
    EXTI_Exti1_SetImr1(u32Value);
  }
  else if (u32Offset == 1U)
  {
    EXTI_Exti1_SetImr2(u32Value);
  }
  else if (u32Offset == 2U)
  {
    EXTI_Exti1_SetImr3(u32Value);
  }
  else
  {
    /* Nothing to do */
  }
}

uint32_t EXTI_Exti1_GetImr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return EXTI_Exti1_GetImr1();
  }
  else if (u32Offset == 1U)
  {
    return EXTI_Exti1_GetImr2();
  }
  else if (u32Offset == 2U)
  {
    return EXTI_Exti1_GetImr3();
  }
  else
  {
    return 0;
  }
}

uint32_t EXTI_Exti1_CheckImr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return 1;
  }
  else if (u32Offset == 1U)
  {
    return 1;
  }
  else if (u32Offset == 2U)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

#endif  /* CORE_CA35 | CORE_CM33 */


uint32_t EXTI_Exti2_GetImr1(void)
{
#if defined (CORE_CA35)
  return EXTI2->C1IMR1;
#elif defined(CORE_CM33)
  return EXTI2->C2IMR1;
#elif defined(CORE_CM0PLUS)
  return EXTI2->C3IMR1;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

uint32_t EXTI_Exti2_GetImr2(void)
{
#if defined (CORE_CA35)
  return EXTI2->C1IMR2;
#elif defined(CORE_CM33)
  return EXTI2->C2IMR2;
#elif defined(CORE_CM0PLUS)
  return EXTI2->C3IMR2;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

uint32_t EXTI_Exti2_GetImr3(void)
{
#if defined (CORE_CA35)
  return EXTI2->C1IMR3;
#elif defined(CORE_CM33)
  return EXTI2->C2IMR3;
#elif defined(CORE_CM0PLUS)
  return EXTI2->C3IMR3;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

uint32_t EXTI_Exti2_GetEmr1(void)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR1*/
  return 0;
#elif defined(CORE_CM33)
  return EXTI2->C2EMR1;
#elif defined(CORE_CM0PLUS)
  return EXTI2->C3EMR1;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

uint32_t EXTI_Exti2_GetEmr2(void)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR2*/
  return 0;
#elif defined(CORE_CM33)
  return EXTI2->C2EMR2;
#elif defined(CORE_CM0PLUS)
  return EXTI2->C3EMR2;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

/* EMR3 not available*/


void EXTI_Exti2_SetImr1(uint32_t u32Value)
{
#if defined (CORE_CA35)
  EXTI2->C1IMR1 = u32Value;
#elif defined(CORE_CM33)
  EXTI2->C2IMR1 = u32Value;
#elif defined(CORE_CM0PLUS)
  EXTI2->C3IMR1 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

void EXTI_Exti2_SetImr2(uint32_t u32Value)
{
#if defined (CORE_CA35)
  EXTI2->C1IMR2 = u32Value;
#elif defined(CORE_CM33)
  EXTI2->C2IMR2 = u32Value;
#elif defined(CORE_CM0PLUS)
  EXTI2->C3IMR2 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

void EXTI_Exti2_SetImr3(uint32_t u32Value)
{
#if defined (CORE_CA35)
  EXTI2->C1IMR3 = u32Value;
#elif defined(CORE_CM33)
  EXTI2->C2IMR3 = u32Value;
#elif defined(CORE_CM0PLUS)
  EXTI2->C3IMR3 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

void EXTI_Exti2_SetEmr1(uint32_t u32Value)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR1*/
  UNUSED(u32Value);
#elif defined(CORE_CM33)
  EXTI2->C2EMR1 = u32Value;
#elif defined(CORE_CM0PLUS)
  EXTI2->C3EMR1 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

void EXTI_Exti2_SetEmr2(uint32_t u32Value)
{
#if defined (CORE_CA35)
  /*no event connected to C1EMR2*/
  UNUSED(u32Value);
#elif defined(CORE_CM33)
  EXTI2->C2EMR2 = u32Value;
#elif defined(CORE_CM0PLUS)
  EXTI2->C3EMR2 = u32Value;
#endif  /* CORE_CA35 | CORE_CM33 | CORE_CM0PLUS */
}

/* EMR3 not available*/


void EXTI_Exti2_SetEmr(uint32_t u32Offset, uint32_t u32Value)
{
  if (u32Offset == 0U)
  {
    EXTI_Exti2_SetEmr1(u32Value);
  }
  else if (u32Offset == 1U)
  {
    EXTI_Exti2_SetEmr2(u32Value);
  }
  /* EMR3 not available*/
  else
  {
    /* Nothing to do */
  }
}


void EXTI_Exti2_SetImr(uint32_t u32Offset, uint32_t u32Value)
{
  if (u32Offset == 0U)
  {
    EXTI_Exti2_SetImr1(u32Value);
  }
  else if (u32Offset == 1U)
  {
    EXTI_Exti2_SetImr2(u32Value);
  }
  else if (u32Offset == 2U)
  {
    EXTI_Exti2_SetImr3(u32Value);
  }
  else
  {
    /* Nothing to do */
  }
}


uint32_t EXTI_Exti2_GetEmr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return EXTI_Exti2_GetEmr1();
  }
  else if (u32Offset == 1U)
  {
    return EXTI_Exti2_GetEmr2();
  }
  /* EMR3 not available*/
  else
  {
    return 0;
  }
}


uint32_t EXTI_Exti2_CheckEmr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return 1;
  }
  else if (u32Offset == 1U)
  {
    return 1;
  }
  else if (u32Offset == 2U)
  {
    /* EMR3 not available*/
    return 0;
  }
  else
  {
    return 0;
  }
}


uint32_t EXTI_Exti2_GetImr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return EXTI_Exti2_GetImr1();
  }
  else if (u32Offset == 1U)
  {
    return EXTI_Exti2_GetImr2();
  }
  else if (u32Offset == 2U)
  {
    return EXTI_Exti2_GetImr3();
  }
  else
  {
    return 0;
  }
}


void EXTI_SetImr(const EXTI_TypeDef *Instance, uint32_t u32Offset, uint32_t u32Value)
{
#ifdef EXTI1
  if (Instance == EXTI1)
  {
    EXTI_Exti1_SetImr(u32Offset, u32Value);
  }
#endif  /* EXTI1 */

#ifdef EXTI2
  if (Instance == EXTI2)
  {
    EXTI_Exti2_SetImr(u32Offset, u32Value);
  }
#endif  /* EXTI2 */

}

uint32_t  EXTI_GetImr(const EXTI_TypeDef *Instance, uint32_t u32Offset)
{
#ifdef EXTI1
  if (Instance == EXTI1)
  {
    return EXTI_Exti1_GetImr(u32Offset);
  }
#endif  /* EXTI1 */

#ifdef EXTI2
  if (Instance == EXTI2)
  {
    return EXTI_Exti2_GetImr(u32Offset);
  }
#endif  /* EXTI2 */

  return 0;

}

void EXTI_SetEmr(const EXTI_TypeDef *Instance, uint32_t u32Offset, uint32_t u32Value)
{
#ifdef EXTI1
  if (Instance == EXTI1)
  {
    EXTI_Exti1_SetEmr(u32Offset, u32Value);
  }
#endif  /* EXTI1 */

#ifdef EXTI2
  if (Instance == EXTI2)
  {
    EXTI_Exti2_SetEmr(u32Offset, u32Value);
  }
#endif  /* EXTI2 */

}

uint32_t  EXTI_GetEmr(const EXTI_TypeDef *Instance, uint32_t u32Offset)
{
#ifdef EXTI1
  if (Instance == EXTI1)
  {
    return EXTI_Exti1_GetEmr(u32Offset);
  }
#endif  /* EXTI1 */

#ifdef EXTI2
  if (Instance == EXTI2)
  {
    return EXTI_Exti2_GetEmr(u32Offset);
  }
#endif  /* EXTI2 */

  return 0;
}


uint32_t  EXTI_CheckEmr(const EXTI_TypeDef *Instance, uint32_t u32Offset)
{
#ifdef EXTI1
  if (Instance == EXTI1)
  {
    return EXTI_Exti1_CheckEmr(u32Offset);
  }
#endif  /* EXTI1 */

#ifdef EXTI2
  if (Instance == EXTI2)
  {
    return EXTI_Exti2_CheckEmr(u32Offset);
  }
#endif  /* EXTI2 */

  return 0;

}

uint32_t EXTI_Exti1_GetRtsr(uint32_t u32Offset)
{
#if !defined(CORE_CM0PLUS)
  if (u32Offset == 0U)
  {
    return EXTI1->RTSR1;
  }
  else if (u32Offset == 1U)
  {
    return EXTI1->RTSR2;
  }
  else if (u32Offset == 2U)
  {
    return EXTI1->RTSR3;
  }
  else
  {
    return 0;
  }
#else   /* !defined(CORE_CM0PLUS) */
  UNUSED(u32Offset);
  return 0;
#endif  /* !defined(CORE_CM0PLUS) */
}

uint32_t EXTI_Exti2_GetRtsr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return EXTI2->RTSR1;
  }
  else if (u32Offset == 1U)
  {
    return EXTI2->RTSR2;
  }
  else if (u32Offset == 2U)
  {
    return EXTI2->RTSR3;
  }
  else
  {
    return 0;
  }
}


uint32_t  EXTI_GetRtsr(const EXTI_TypeDef *Instance, uint32_t u32Offset)
{
#ifdef EXTI1
  if (Instance == EXTI1)
  {
    return EXTI_Exti1_GetRtsr(u32Offset);
  }
#endif  /* EXTI1 */

#ifdef EXTI2
  if (Instance == EXTI2)
  {
    return EXTI_Exti2_GetRtsr(u32Offset);
  }
#endif  /* EXTI2 */

  return 0;
}


uint32_t EXTI_Exti1_GetFtsr(uint32_t u32Offset)
{
#if !defined(CORE_CM0PLUS)
  if (u32Offset == 0U)
  {
    return EXTI1->FTSR1;
  }
  else if (u32Offset == 1U)
  {
    return EXTI1->FTSR2;
  }
  else if (u32Offset == 2U)
  {
    return EXTI1->FTSR3;
  }
  else
  {
    return 0;
  }
#else   /* !defined(CORE_CM0PLUS) */
  UNUSED(u32Offset);
  return 0;
#endif  /* !defined(CORE_CM0PLUS) */
}

uint32_t EXTI_Exti2_GetFtsr(uint32_t u32Offset)
{
  if (u32Offset == 0U)
  {
    return EXTI2->FTSR1;
  }
  else if (u32Offset == 1U)
  {
    return EXTI2->FTSR2;
  }
  else if (u32Offset == 2U)
  {
    return EXTI2->FTSR3;
  }
  else
  {
    return 0;
  }
}


uint32_t  EXTI_GetFtsr(const EXTI_TypeDef *Instance, uint32_t u32Offset)
{
#ifdef EXTI1
  if (Instance == EXTI1)
  {
    return EXTI_Exti1_GetFtsr(u32Offset);
  }
#endif  /* EXTI1 */

#ifdef EXTI2
  if (Instance == EXTI2)
  {
    return EXTI_Exti2_GetFtsr(u32Offset);
  }
#endif  /* EXTI2 */

  return 0;
}


#endif /* HAL_EXTI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
