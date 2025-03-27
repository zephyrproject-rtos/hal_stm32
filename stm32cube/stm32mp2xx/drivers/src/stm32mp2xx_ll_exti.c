/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_exti.c
  * @author  MCD Application Team
  * @brief   EXTI LL module driver.
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
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else   /* USE_FULL_ASSERT */
#define assert_param(expr) ((void)0U)
#endif  /* USE_FULL_ASSERT */

#include "stm32mp2xx_ll_exti.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined (EXTI1) || defined (EXTI2)

/** @defgroup EXTI_LL EXTI
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup EXTI_LL_Private_Macros
  * @{
  */


#define IS_LL_EXTI_MODE(__VALUE__)                   (((__VALUE__) == LL_EXTI_MODE_IT)            \
                                                      || ((__VALUE__) == LL_EXTI_MODE_EVENT)         \
                                                      || ((__VALUE__) == LL_EXTI_MODE_IT_EVENT))


#define IS_LL_EXTI_TRIGGER(__VALUE__)                (((__VALUE__) == LL_EXTI_TRIGGER_NONE)       \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_RISING)     \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_FALLING)    \
                                                      || ((__VALUE__) == LL_EXTI_TRIGGER_RISING_FALLING))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup EXTI_LL_Exported_Functions
  * @{
  */

/** @addtogroup EXTI_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize the EXTI registers to their default reset values.
  * @param  EXTIx EXTI Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_EXTI_DeInit(EXTI_TypeDef *EXTIx)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));

  /* Rising Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, RTSR1, 0x00000000U);

  /* Falling Trigger selection register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, FTSR1, 0x00000000U);

  /* Software interrupt event register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, SWIER1, 0x00000000U);

  /* Pending register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, RPR1, 0x00000000U);

  /* Pending register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, FPR1, 0x00000000U);

  /* Privilege register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, PRIVCFGR1,  0x00000000U);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Secure register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, SECCFGR1,  0x00000000U);
#endif /* __ARM_FEATURE_CMSE */

  /* Rising Trigger selection register 2 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, RTSR2, 0x00000000U);

  /* Falling Trigger selection register 2 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, FTSR2, 0x00000000U);

  /* Software interrupt event register 2 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, SWIER2, 0x00000000U);

  /* Pending register 2 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, RPR2, 0x00000000U);

  /* Pending register 2 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, FPR2, 0x00000000U);

  /* Privilege register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, PRIVCFGR2,  0x00000000U);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Secure register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, SECCFGR2,  0x00000000U);
#endif /* __ARM_FEATURE_CMSE */

  /* Rising Trigger selection register 3 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, RTSR3, 0x00000000U);

  /* Falling Trigger selection register 3 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, FTSR3, 0x00000000U);

  /* Software interrupt event register 3 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, SWIER3, 0x00000000U);

  /* Pending register 3 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, RPR3, 0x00000000U);

  /* Pending register 3 set to default reset values */
  LL_EXTI_WriteReg(EXTIx, FPR3, 0x00000000U);

  /* Privilege register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, PRIVCFGR3,  0x00000000U);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Secure register set to default reset values */
  LL_EXTI_WriteReg(EXTIx, SECCFGR3,  0x00000000U);
#endif /* __ARM_FEATURE_CMSE */

  /* Interrupt mask register set to default reset values */
#if defined (CORE_CM0PLUS)
  LL_EXTI_WriteReg(EXTIx, C3IMR1, 0x00000000U);
#elif defined (CORE_CM33)
  LL_EXTI_WriteReg(EXTIx, C2IMR1, 0x00000000U);
#else   /* CORE_CM0PLUS | CORE_CM33 */
  LL_EXTI_WriteReg(EXTIx, C1IMR1, 0x00000000U);
#endif  /* CORE_CM0PLUS | CORE_CM33 */

  /* Event mask register set to default reset values */
#if defined (CORE_CM0PLUS)
  LL_EXTI_WriteReg(EXTIx, C3EMR1, 0x00000000U);
#elif defined (CORE_CM33)
  LL_EXTI_WriteReg(EXTIx, C2EMR1, 0x00000000U);
#else   /* CORE_CM0PLUS | CORE_CM33 */
  /* LL_EXTI_WriteReg(EXTIx, C1EMR1, 0x00000000U); */
#endif  /* CORE_CM0PLUS | CORE_CM33 */

  /* Interrupt mask register 2 set to default reset values */
#if defined (CORE_CM0PLUS)
  LL_EXTI_WriteReg(EXTIx, C3IMR2, 0x00000000U);
#elif defined(CORE_CM33)
  LL_EXTI_WriteReg(EXTIx, C2IMR2, 0x00000000U);
#else   /* CORE_CM0PLUS | CORE_CM33 */
  LL_EXTI_WriteReg(EXTIx, C1IMR2, 0x00000000U);
#endif  /* CORE_CM0PLUS | CORE_CM33 */

  /* Event mask register 2 set to default reset values */
#if defined (CORE_CM0PLUS)
  /* No C2EMR2 on EXTI1 */
  if (EXTIx == EXTI2)
  {
    LL_EXTI_WriteReg(EXTIx, C3EMR2, 0x00000000U);
  }
#elif defined (CORE_CM33)
  /* No C2EMR2 on EXTI1 */
  if (EXTIx == EXTI2)
  {
    LL_EXTI_WriteReg(EXTIx, C2EMR2, 0x00000000U);
  }
#else   /* CORE_CM0PLUS | CORE_CM33 */
  /* LL_EXTI_WriteReg(EXTIx, C1EMR2, 0x00000000U); */
#endif  /* CORE_CM0PLUS | CORE_CM33 */

  /* Interrupt mask register 2 set to default reset values */
#if defined (CORE_CM0PLUS)
  LL_EXTI_WriteReg(EXTIx, C3IMR3, 0x00000000U);
#elif defined(CORE_CM33)
  LL_EXTI_WriteReg(EXTIx, C2IMR3, 0x00000000U);
#else   /* CORE_CM0PLUS | CORE_CM33 */
  LL_EXTI_WriteReg(EXTIx, C1IMR3, 0x00000000U);
#endif  /* CORE_CM0PLUS | CORE_CM33 */

  /* Event mask register 2 set to default reset values */
#if defined (CORE_CM0PLUS)
  /* LL_EXTI_WriteReg(EXTIx, C3EMR3, 0x00000000U); */
#elif defined (CORE_CM33)
  /* No C2EMR3 on EXTI2 */
  if (EXTIx == EXTI1)
  {
    LL_EXTI_WriteReg(EXTIx, C2EMR3, 0x00000000U);
  }
#else   /* CORE_CM0PLUS | CORE_CM33 */
  /* LL_EXTI_WriteReg(EXTIx, C1EMR3, 0x00000000U); */
#endif  /* CORE_CM0PLUS | CORE_CM33 */

  return SUCCESS;
}

/**
  * @brief  Initialize the EXTI registers according to the specified parameters in EXTI_InitStruct.
  * @param  EXTIx EXTI Instance
  * @param  EXTI_InitStruct pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: EXTI registers are initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_EXTI_Init(EXTI_TypeDef *EXTIx, LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  ErrorStatus status = SUCCESS;
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, EXTI_InitStruct->Line_0_31));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, EXTI_InitStruct->Line_32_63));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, EXTI_InitStruct->Line_64_95));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->LineCommand));
  assert_param(IS_LL_EXTI_MODE(EXTI_InitStruct->Mode));

  /* ENABLE LineCommand */
  if (EXTI_InitStruct->LineCommand != DISABLE)
  {
    assert_param(IS_LL_EXTI_TRIGGER(EXTI_InitStruct->Trigger));

    /* Configure EXTI Lines in range from 0 to 31 */
    if (EXTI_InitStruct->Line_0_31 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
#if defined (CORE_CM0PLUS)
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_C3_EXTI_DisableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          /* Then Enable IT on provided Lines */
          LL_C3_EXTI_EnableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_C3_EXTI_DisableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          /* Then Enable Event on provided Lines */
          LL_C3_EXTI_EnableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_C3_EXTI_EnableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          LL_C3_EXTI_EnableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          break;
        default:
          status = ERROR;
          break;
#elif defined (CORE_CM33)
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_C2_EXTI_DisableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          /* Then Enable IT on provided Lines */
          LL_C2_EXTI_EnableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_C2_EXTI_DisableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          /* Then Enable Event on provided Lines */
          LL_C2_EXTI_EnableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_C2_EXTI_EnableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          LL_C2_EXTI_EnableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          break;
        default:
          status = ERROR;
          break;
#else   /* CORE_CM0PLUS | CORE_CM33 */
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          /* LL_C1_EXTI_DisableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31); */
          /* Then Enable IT on provided Lines */
          LL_C1_EXTI_EnableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          /* LL_C1_EXTI_DisableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31); */
          /* Then Enable Event on provided Lines */
          /* LL_C1_EXTI_EnableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31); */
          /* No Event on C1 */
          status = ERROR;
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          /* LL_C1_EXTI_EnableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31); */
          /* LL_C1_EXTI_EnableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31); */
          /* No Event on C1 */
          status = ERROR;
          break;
        default:
          status = ERROR;
          break;
#endif  /* CORE_CM0PLUS | CORE_CM33 */
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
            /* Then Enable Rising Trigger on provided Lines */
            LL_EXTI_EnableRisingTrig_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
            LL_EXTI_EnableFallingTrig_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }
    /* Configure EXTI Lines in range from 32 to 63 */
    if (EXTI_InitStruct->Line_32_63 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
#if defined(CORE_CM0PLUS)
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          LL_C3_EXTI_DisableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          /* Then Enable IT on provided Lines */
          LL_C3_EXTI_EnableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_C3_EXTI_DisableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          /* Then Enable Event on provided Lines */
          LL_C3_EXTI_EnableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_C3_EXTI_EnableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          LL_C3_EXTI_EnableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          break;
        default:
          status = ERROR;
          break;
#elif defined(CORE_CM33)
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          if (EXTIx == EXTI2)
            /* no such event on EXTI1 */
          {
            LL_C2_EXTI_DisableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          }
          /* Then Enable IT on provided Lines */
          LL_C2_EXTI_EnableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          break;
        case LL_EXTI_MODE_EVENT:
          if (EXTIx == EXTI2)
            /* no such event on EXTI1 */
          {
            /* First Disable IT on provided Lines */
            LL_C2_EXTI_DisableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
            /* Then Enable Event on provided Lines */
            LL_C2_EXTI_EnableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          }
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_C2_EXTI_EnableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          if (EXTIx == EXTI2)
            /* no such event on EXTI1 */
          {
            LL_C2_EXTI_EnableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          }
          break;
        default:
          status = ERROR;
          break;
#else   /* CORE_CM0PLUS | CORE_CM33 */
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          /* LL_C1_EXTI_DisableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63); */
          /* Then Enable IT on provided Lines */
          LL_C1_EXTI_EnableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          /* LL_C1_EXTI_DisableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63); */
          /* Then Enable Event on provided Lines */
          /* LL_C1_EXTI_EnableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63); */
          /* No Event on C1 */
          status = ERROR;
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          /* LL_C1_EXTI_EnableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63); */
          /* LL_C1_EXTI_EnableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63); */
          /* No Event on C1 */
          status = ERROR;
          break;
        default:
          status = ERROR;
          break;
#endif  /* CORE_CM0PLUS | CORE_CM33 */
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
            /* Then Enable IT on provided Lines */
            LL_EXTI_EnableRisingTrig_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
            LL_EXTI_EnableFallingTrig_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }

    /* Configure EXTI Lines in range from 64 to 95 */
    if (EXTI_InitStruct->Line_64_95 != LL_EXTI_LINE_NONE)
    {
      switch (EXTI_InitStruct->Mode)
      {
#if defined(CORE_CM0PLUS)
        case LL_EXTI_MODE_IT:

          /* Then Enable IT on provided Lines */
          LL_C3_EXTI_EnableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          LL_C3_EXTI_DisableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_C3_EXTI_EnableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          break;
        default:
          status = ERROR;
          break;
#elif defined(CORE_CM33)
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          if (EXTIx == EXTI1)
            /*no such event line if instance is EXTi2*/
          {
            LL_C2_EXTI_DisableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          }
          /* Then Enable IT on provided Lines */
          LL_C2_EXTI_EnableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_EVENT:
          if (EXTIx == EXTI1)
            /*no such event line if instance is EXTi2*/
          {
            /* First Disable IT on provided Lines */
            LL_C2_EXTI_DisableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
            /* Then Enable Event on provided Lines */
            LL_C2_EXTI_EnableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          }
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          LL_C2_EXTI_EnableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          if (EXTIx == EXTI1)
            /*no such event line if instance is EXTi2*/
          {
            LL_C2_EXTI_EnableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          }
          break;
        default:
          status = ERROR;
          break;
#else   /* CORE_CM0PLUS | CORE_CM33 */
        case LL_EXTI_MODE_IT:
          /* First Disable Event on provided Lines */
          /* LL_C1_EXTI_DisableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95); */
          /* Then Enable IT on provided Lines */
          LL_C1_EXTI_EnableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
          break;
        case LL_EXTI_MODE_EVENT:
          /* First Disable IT on provided Lines */
          /* LL_C1_EXTI_DisableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95); */
          /* Then Enable Event on provided Lines */
          /* LL_C1_EXTI_EnableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95); */
          /* No Event on C1 */
          status = ERROR;
          break;
        case LL_EXTI_MODE_IT_EVENT:
          /* Directly Enable IT & Event on provided Lines */
          /* LL_C1_EXTI_EnableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95); */
          /* LL_C1_EXTI_EnableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95); */
          /* No Event on C1 */
          status = ERROR;
          break;
        default:
          status = ERROR;
          break;
#endif  /* CORE_CM0PLUS | CORE_CM33 */
      }
      if (EXTI_InitStruct->Trigger != LL_EXTI_TRIGGER_NONE)
      {
        switch (EXTI_InitStruct->Trigger)
        {
          case LL_EXTI_TRIGGER_RISING:
            /* First Disable Falling Trigger on provided Lines */
            LL_EXTI_DisableFallingTrig_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
            /* Then Enable IT on provided Lines */
            LL_EXTI_EnableRisingTrig_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
            break;
          case LL_EXTI_TRIGGER_FALLING:
            /* First Disable Rising Trigger on provided Lines */
            LL_EXTI_DisableRisingTrig_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
            /* Then Enable Falling Trigger on provided Lines */
            LL_EXTI_EnableFallingTrig_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
            break;
          case LL_EXTI_TRIGGER_RISING_FALLING:
            LL_EXTI_EnableRisingTrig_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
            LL_EXTI_EnableFallingTrig_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
            break;
          default:
            status = ERROR;
            break;
        }
      }
    }
  }
  /* DISABLE LineCommand */
  else
  {
#if defined(CORE_CM0PLUS)
    /* De-configure EXTI Lines in range from 0 to 31 */
    LL_C3_EXTI_DisableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
    LL_C3_EXTI_DisableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
    /* De-configure EXTI Lines in range from 32 to 63 */
    LL_C3_EXTI_DisableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
    LL_C3_EXTI_DisableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
    /* De-configure EXTI Lines in range from 64 to 95 */
    LL_C3_EXTI_DisableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
#elif defined(CORE_CM33)
    /* De-configure EXTI Lines in range from 0 to 31 */
    LL_C2_EXTI_DisableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
    LL_C2_EXTI_DisableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
    /* De-configure EXTI Lines in range from 32 to 63 */
    LL_C2_EXTI_DisableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
    if (EXTIx == EXTI2)
      /* test to avoid assert into LL_C2_EXTI_DisableEvent_32_63 function*/
    {
      LL_C2_EXTI_DisableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
    }
    /* De-configure EXTI Lines in range from 32 to 63 */
    LL_C2_EXTI_DisableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
    if (EXTIx == EXTI1)
      /* test to avoid assert into LL_C2_EXTI_DisableEvent_64_95 function*/
    {
      LL_C2_EXTI_DisableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
    }
#else   /* CORE_CM0PLUS | CORE_CM33 */
    /* De-configure EXTI Lines in range from 0 to 31 */
    LL_C1_EXTI_DisableIT_0_31(EXTIx, EXTI_InitStruct->Line_0_31);
    /* LL_C1_EXTI_DisableEvent_0_31(EXTIx, EXTI_InitStruct->Line_0_31); */
    /* De-configure EXTI Lines in range from 32 to 63 */
    LL_C1_EXTI_DisableIT_32_63(EXTIx, EXTI_InitStruct->Line_32_63);
    /* LL_C1_EXTI_DisableEvent_32_63(EXTIx, EXTI_InitStruct->Line_32_63); */
    /* De-configure EXTI Lines in range from 32 to 63 */
    LL_C1_EXTI_DisableIT_64_95(EXTIx, EXTI_InitStruct->Line_64_95);
    /* LL_C1_EXTI_DisableEvent_64_95(EXTIx, EXTI_InitStruct->Line_64_95); */
#endif  /* CORE_CM0PLUS | CORE_CM33 */
  }
  return status;
}

/**
  * @brief  Set each @ref LL_EXTI_InitTypeDef field to default value.
  * @param  EXTI_InitStruct Pointer to a @ref LL_EXTI_InitTypeDef structure.
  * @retval None
  */
void LL_EXTI_StructInit(LL_EXTI_InitTypeDef *EXTI_InitStruct)
{
  EXTI_InitStruct->Line_0_31      = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->Line_32_63     = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->Line_64_95     = LL_EXTI_LINE_NONE;
  EXTI_InitStruct->LineCommand    = DISABLE;
  EXTI_InitStruct->Mode           = LL_EXTI_MODE_IT;
  EXTI_InitStruct->Trigger        = LL_EXTI_TRIGGER_FALLING;
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

#endif /* defined (EXTI1) || defined (EXTI2) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */
