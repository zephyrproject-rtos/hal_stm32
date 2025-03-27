/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_exti.h
  * @author  MCD Application Team
  * @brief   Header file of EXTI LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP2xx_LL_EXTI_H
#define __STM32MP2xx_LL_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined(EXTI1) || defined(EXTI2)

/** @defgroup EXTI_LL EXTI
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
#define LL_EXTI_REGISTER_PINPOS_SHFT        16U   /*!< Define used to shift pin position in EXTICR register */

/* Private Macros ------------------------------------------------------------*/
/**
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __EXTI_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
  ((__IO uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2UL))))

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup EXTI_LL_Private_Macros EXTI Private Macros
  * @{
  */


#if defined (EXTI1)
#define IS_LL_EXTI1_LINE_0_31(__VALUE__)              (( (__VALUE__) & ~LL_EXTI1_LINE_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI1_LINE_32_63(__VALUE__)             (( (__VALUE__) & ~LL_EXTI1_LINE_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI1_LINE_64_95(__VALUE__)             (( (__VALUE__) & ~LL_EXTI1_LINE_ALL_64_95) == 0x00000000U)

#define IS_LL_EXTI1_DIRECT_LINE_0_31(__VALUE__)       (( (__VALUE__) & ~LL_EXTI1_DIRECT_LINE_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI1_DIRECT_LINE_32_63(__VALUE__)      (( (__VALUE__) & ~LL_EXTI1_DIRECT_LINE_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI1_DIRECT_LINE_64_95(__VALUE__)      (( (__VALUE__) & ~LL_EXTI1_DIRECT_LINE_ALL_64_95) == 0x00000000U)

#define IS_LL_EXTI1_CONFIG_LINE_0_31(__VALUE__)       (( (__VALUE__) & ~LL_EXTI1_CONFIG_LINE_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI1_CONFIG_LINE_32_63(__VALUE__)      (( (__VALUE__) & ~LL_EXTI1_CONFIG_LINE_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI1_CONFIG_LINE_64_95(__VALUE__)      (( (__VALUE__) & ~LL_EXTI1_CONFIG_LINE_ALL_64_95) == 0x00000000U)
#endif /* EXTI1 */

#define IS_LL_EXTI2_LINE_0_31(__VALUE__)              (( (__VALUE__) & ~LL_EXTI2_LINE_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI2_LINE_32_63(__VALUE__)             (( (__VALUE__) & ~LL_EXTI2_LINE_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI2_LINE_64_95(__VALUE__)             (( (__VALUE__) & ~LL_EXTI2_LINE_ALL_64_95) == 0x00000000U)

#define IS_LL_EXTI2_DIRECT_LINE_0_31(__VALUE__)       (( (__VALUE__) & ~LL_EXTI2_DIRECT_LINE_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI2_DIRECT_LINE_32_63(__VALUE__)      (( (__VALUE__) & ~LL_EXTI2_DIRECT_LINE_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI2_DIRECT_LINE_64_95(__VALUE__)      (( (__VALUE__) & ~LL_EXTI2_DIRECT_LINE_ALL_64_95) == 0x00000000U)

#define IS_LL_EXTI2_CONFIG_LINE_0_31(__VALUE__)       (( (__VALUE__) & ~LL_EXTI2_CONFIG_LINE_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI2_CONFIG_LINE_32_63(__VALUE__)      (( (__VALUE__) & ~LL_EXTI2_CONFIG_LINE_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI2_CONFIG_LINE_64_95(__VALUE__)      (( (__VALUE__) & ~LL_EXTI2_CONFIG_LINE_ALL_64_95) == 0x00000000U)

#if defined (EXTI1)
#define IS_LL_EXTI_LINE_0_31(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_LINE_0_31( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_LINE_0_31( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_LINE_0_31(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                            IS_LL_EXTI2_LINE_0_31(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_LINE_32_63(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_LINE_32_63( (__VALUE__) ) ) \
      ||                                                                         \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_LINE_32_63( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_LINE_32_63(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                             IS_LL_EXTI2_LINE_32_63(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_LINE_64_95(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_LINE_64_95( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_LINE_64_95( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_LINE_64_95(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                             IS_LL_EXTI2_LINE_64_95(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_DIRECT_LINE_0_31(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_DIRECT_EXTI1_LINE_0_31( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_DIRECT_EXTI2_LINE_0_31( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_DIRECT_LINE_0_31(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                                   IS_LL_EXTI2_DIRECT_LINE_0_31(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_DIRECT_LINE_32_63(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_DIRECT_EXTI1_LINE_32_63( (__VALUE__) ) ) \
      ||                                                                         \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_DIRECT_EXTI2_LINE_32_63( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_DIRECT_LINE_32_63(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                                    IS_LL_EXTI2_DIRECT_LINE_32_63(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_DIRECT_LINE_64_95(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_DIRECT_LINE_64_95( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_DIRECT_LINE_64_95( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_DIRECT_LINE_64_95(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                                    IS_LL_EXTI2_DIRECT_LINE_64_95(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_CONFIG_LINE_0_31(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_CONFIG_LINE_0_31( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_CONFIG_LINE_0_31( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_CONFIG_LINE_0_31(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                                   IS_LL_EXTI2_CONFIG_LINE_0_31(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_CONFIG_LINE_32_63(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_CONFIG_LINE_32_63( (__VALUE__) ) ) \
      ||                                                                         \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_CONFIG_LINE_32_63( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_CONFIG_LINE_32_63(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                                    IS_LL_EXTI2_CONFIG_LINE_32_63(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_CONFIG_LINE_64_95(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_CONFIG_LINE_64_95( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_CONFIG_LINE_64_95( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_CONFIG_LINE_64_95(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                                    IS_LL_EXTI2_CONFIG_LINE_64_95(__VALUE__))
#endif /* EXTI1 */

/* type cast to int is required to prevent warning when using some compilers (pointless comparison of
 * unsigned integer with zero) */
#if defined (EXTI1)
#define IS_EXTI1_EVT_CID_VALID(__VALUE__)               \
  ( ( ((__VALUE__) >=  0U) && ( (__VALUE__) <= 19U) ) || \
    ( ((__VALUE__) >= 21U) && ( (__VALUE__) <= 34U) ) || \
    ( ((__VALUE__) >= 36U) && ( (__VALUE__) <= 50U) ) || \
    ( ((__VALUE__) >= 52U) && ( (__VALUE__) <= 57U) ) || \
    ( ((__VALUE__) >= 59U) && ( (__VALUE__) <= 62U) ) || \
    ( ((__VALUE__) >= 64U) && ( (__VALUE__) <= 65U) ) || \
    ( ((__VALUE__) >= 67U) && ( (__VALUE__) <= 68U) ) || \
    ((__VALUE__) == 70U)                            || \
    ( ((__VALUE__) >= 72U) && ( (__VALUE__) <= 84U)) )
#endif /* EXTI1 */

#define IS_EXTI2_EVT_CID_VALID(__VALUE__)                 \
  ( ( ((__VALUE__) >=  0U) && ( (__VALUE__) <= 27U)) || \
    ( ((__VALUE__) >= 29U) && ( (__VALUE__) <= 31U)) || \
    ( ((__VALUE__) >= 33U) && ( (__VALUE__) <= 38U)) || \
    ( ((__VALUE__) >= 40U) && ( (__VALUE__) <= 44U)) || \
    ( ((__VALUE__) >= 46U) && ( (__VALUE__) <= 56U)) || \
    ( ((__VALUE__) >= 59U) && ( (__VALUE__) <= 70U)) || \
    ((__VALUE__) == 76U) )

#if defined (EXTI1)
#define IS_EXTI_EVT_CID_VALID(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_EXTI1_EVT_CID_VALID( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_EXTI2_EVT_CID_VALID( (__VALUE__) ) ) )
#else
#define IS_EXTI_EVT_CID_VALID(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                             IS_EXTI2_EVT_CID_VALID(__VALUE__))
#endif /* EXTI1 */


#if defined (EXTI1)
#define IS_LL_EXTI1_EVT_0_31(__VALUE__)              (0U)
#define IS_LL_EXTI1_EVT_32_63(__VALUE__)             (0U)
#define IS_LL_EXTI1_EVT_64_95(__VALUE__)             (( (__VALUE__) & ~LL_EXTI1_EVT_ALL_64_95) == 0x00000000U)
#endif  /* EXTI1 */

#define IS_LL_EXTI2_EVT_0_31(__VALUE__)              (( (__VALUE__) & ~LL_EXTI2_EVT_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI2_EVT_32_63(__VALUE__)             (( (__VALUE__) & ~LL_EXTI2_EVT_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI2_EVT_64_95(__VALUE__)             (0U)

#if defined (EXTI1)
#define IS_LL_EXTI_EVT_0_31(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_EVT_0_31( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_EVT_0_31( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_EVT_0_31(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) && IS_LL_EXTI2_EVT_0_31(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_EVT_32_63(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_EVT_32_63( (__VALUE__) ) ) \
      ||                                                                         \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_EVT_32_63( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_EVT_32_63(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                            IS_LL_EXTI2_EVT_32_63(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_EVT_64_95(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_EVT_64_95( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_EVT_64_95( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_EVT_64_95(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                            IS_LL_EXTI2_EVT_64_95(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI1_SEC_0_31(__VALUE__)              (( (__VALUE__) & ~LL_EXTI1_SEC_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI1_SEC_32_63(__VALUE__)             (( (__VALUE__) & ~LL_EXTI1_SEC_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI1_SEC_64_95(__VALUE__)             (( (__VALUE__) & ~LL_EXTI1_SEC_ALL_64_95) == 0x00000000U)
#endif /* EXTI1 */

#define IS_LL_EXTI2_SEC_0_31(__VALUE__)              (( (__VALUE__) & ~LL_EXTI2_SEC_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI2_SEC_32_63(__VALUE__)             (( (__VALUE__) & ~LL_EXTI2_SEC_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI2_SEC_64_95(__VALUE__)             (( (__VALUE__) & ~LL_EXTI2_SEC_ALL_64_95) == 0x00000000U)

#if defined (EXTI1)
#define IS_LL_EXTI_SEC_0_31(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_SEC_0_31( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_SEC_0_31( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_SEC_0_31(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) && IS_LL_EXTI2_SEC_0_31(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_SEC_32_63(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_SEC_32_63( (__VALUE__) ) ) \
      ||                                                                         \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_SEC_32_63( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_SEC_32_63(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                            IS_LL_EXTI2_SEC_32_63(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_SEC_64_95(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_SEC_64_95( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_SEC_64_95( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_SEC_64_95(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                            IS_LL_EXTI2_SEC_64_95(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI1_PRIV_0_31(__VALUE__)              (( (__VALUE__) & ~LL_EXTI1_PRIV_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI1_PRIV_32_63(__VALUE__)             (( (__VALUE__) & ~LL_EXTI1_PRIV_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI1_PRIV_64_95(__VALUE__)             (( (__VALUE__) & ~LL_EXTI1_PRIV_ALL_64_95) == 0x00000000U)
#endif /* EXTI1 */

#define IS_LL_EXTI2_PRIV_0_31(__VALUE__)              (( (__VALUE__) & ~LL_EXTI2_PRIV_ALL_0_31 ) == 0x00000000U)
#define IS_LL_EXTI2_PRIV_32_63(__VALUE__)             (( (__VALUE__) & ~LL_EXTI2_PRIV_ALL_32_63) == 0x00000000U)
#define IS_LL_EXTI2_PRIV_64_95(__VALUE__)             (( (__VALUE__) & ~LL_EXTI2_PRIV_ALL_64_95) == 0x00000000U)

#if defined (EXTI1)
#define IS_LL_EXTI_PRIV_0_31(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_PRIV_0_31( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_PRIV_0_31( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_PRIV_0_31(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                            IS_LL_EXTI2_PRIV_0_31(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_PRIV_32_63(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_PRIV_32_63( (__VALUE__) ) ) \
      ||                                                                         \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_PRIV_32_63( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_PRIV_32_63(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                             IS_LL_EXTI2_PRIV_32_63(__VALUE__))
#endif /* EXTI1 */

#if defined (EXTI1)
#define IS_LL_EXTI_PRIV_64_95(__INSTANCE__, __VALUE__)                          \
  (   ( ( (__INSTANCE__) == EXTI1) && IS_LL_EXTI1_PRIV_64_95( (__VALUE__) ) ) \
      ||                                                                        \
      ( ( (__INSTANCE__) == EXTI2) && IS_LL_EXTI2_PRIV_64_95( (__VALUE__) ) ) )
#else
#define IS_LL_EXTI_PRIV_64_95(__INSTANCE__, __VALUE__)      (((__INSTANCE__) == EXTI2) &&\
                                                             IS_LL_EXTI2_PRIV_64_95(__VALUE__))
#endif /* EXTI1 */


/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/
/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup EXTI_LL_ES_INIT EXTI Exported Init structure
  * @{
  */
typedef struct
{

  uint32_t Line_0_31;           /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range 0 to 31.
                                     This parameter can be any combination of @ref LL_EXTI1_LINE_x or
                                     @ref LL_EXTI2_LINE_x */

  uint32_t Line_32_63;          /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range 32 to 63.
                                     This parameter can be any combination of @ref LL_EXTI1_LINE_x or
                                     @ref LL_EXTI2_LINE_x */

  uint32_t Line_64_95;          /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range 64 to 95.
                                     This parameter can be any combination of @ref LL_EXTI1_LINE_x or
                                     @ref LL_EXTI2_LINE_x */

  FunctionalState LineCommand;  /*!< Specifies the new state of the selected EXTI lines.
                                     This parameter can be set either to ENABLE or DISABLE */

  uint8_t Mode;                 /*!< Specifies the mode for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_LL_EC_MODE. */

  uint8_t Trigger;              /*!< Specifies the trigger signal active edge for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_LL_EC_TRIGGER. */
} LL_EXTI_InitTypeDef;

/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Constants EXTI Exported Constants
  * @{
  */

#if defined(EXTI1)
/** @defgroup LL_EXTI1_LINE_x EXTI1 Line x
  * @{
  */
#define LL_EXTI1_LINE_0                  EXTI1_IMR1_IM0    /*!< Extended line 0  */
#define LL_EXTI1_LINE_1                  EXTI1_IMR1_IM1    /*!< Extended line 1  */
#define LL_EXTI1_LINE_2                  EXTI1_IMR1_IM2    /*!< Extended line 2  */
#define LL_EXTI1_LINE_3                  EXTI1_IMR1_IM3    /*!< Extended line 3  */
#define LL_EXTI1_LINE_4                  EXTI1_IMR1_IM4    /*!< Extended line 4  */
#define LL_EXTI1_LINE_5                  EXTI1_IMR1_IM5    /*!< Extended line 5  */
#define LL_EXTI1_LINE_6                  EXTI1_IMR1_IM6    /*!< Extended line 6  */
#define LL_EXTI1_LINE_7                  EXTI1_IMR1_IM7    /*!< Extended line 7  */
#define LL_EXTI1_LINE_8                  EXTI1_IMR1_IM8    /*!< Extended line 8  */
#define LL_EXTI1_LINE_9                  EXTI1_IMR1_IM9    /*!< Extended line 9  */
#define LL_EXTI1_LINE_10                 EXTI1_IMR1_IM10   /*!< Extended line 10 */
#define LL_EXTI1_LINE_11                 EXTI1_IMR1_IM11   /*!< Extended line 11 */
#define LL_EXTI1_LINE_12                 EXTI1_IMR1_IM12   /*!< Extended line 12 */
#define LL_EXTI1_LINE_13                 EXTI1_IMR1_IM13   /*!< Extended line 13 */
#define LL_EXTI1_LINE_14                 EXTI1_IMR1_IM14   /*!< Extended line 14 */
#define LL_EXTI1_LINE_15                 EXTI1_IMR1_IM15   /*!< Extended line 15 */
#define LL_EXTI1_LINE_16                 EXTI1_IMR1_IM16   /*!< Extended line 16 */
#define LL_EXTI1_LINE_17                 EXTI1_IMR1_IM17   /*!< Extended line 17 */
#define LL_EXTI1_LINE_18                 EXTI1_IMR1_IM18   /*!< Extended line 18 */
#define LL_EXTI1_LINE_19                 EXTI1_IMR1_IM19   /*!< Extended line 19 */
#define LL_EXTI1_LINE_21                 EXTI1_IMR1_IM21   /*!< Extended line 21 */
#define LL_EXTI1_LINE_22                 EXTI1_IMR1_IM22   /*!< Extended line 22 */
#define LL_EXTI1_LINE_23                 EXTI1_IMR1_IM23   /*!< Extended line 23 */
#define LL_EXTI1_LINE_24                 EXTI1_IMR1_IM24   /*!< Extended line 24 */
#define LL_EXTI1_LINE_25                 EXTI1_IMR1_IM25   /*!< Extended line 25 */
#define LL_EXTI1_LINE_26                 EXTI1_IMR1_IM26   /*!< Extended line 26 */
#define LL_EXTI1_LINE_27                 EXTI1_IMR1_IM27   /*!< Extended line 27 */
#define LL_EXTI1_LINE_28                 EXTI1_IMR1_IM28   /*!< Extended line 28 */
#define LL_EXTI1_LINE_29                 EXTI1_IMR1_IM29   /*!< Extended line 29 */
#define LL_EXTI1_LINE_30                 EXTI1_IMR1_IM30   /*!< Extended line 30 */
#define LL_EXTI1_LINE_31                 EXTI1_IMR1_IM31   /*!< Extended line 31 */
#define LL_EXTI1_LINE_ALL_0_31 \
  ( LL_EXTI1_LINE_0  | LL_EXTI1_LINE_1  | LL_EXTI1_LINE_2 | \
    LL_EXTI1_LINE_3  | LL_EXTI1_LINE_4  | LL_EXTI1_LINE_5 | \
    LL_EXTI1_LINE_6  | LL_EXTI1_LINE_7  | LL_EXTI1_LINE_8 | \
    LL_EXTI1_LINE_9  | LL_EXTI1_LINE_10 | LL_EXTI1_LINE_11 | \
    LL_EXTI1_LINE_12 | LL_EXTI1_LINE_13 | LL_EXTI1_LINE_14 | \
    LL_EXTI1_LINE_15 | LL_EXTI1_LINE_16 | LL_EXTI1_LINE_17 | \
    LL_EXTI1_LINE_18 | LL_EXTI1_LINE_19 | \
    LL_EXTI1_LINE_21 | LL_EXTI1_LINE_22 | LL_EXTI1_LINE_23 | \
    LL_EXTI1_LINE_24 | LL_EXTI1_LINE_25 | LL_EXTI1_LINE_26 | \
    LL_EXTI1_LINE_27 | LL_EXTI1_LINE_28 | LL_EXTI1_LINE_29 | \
    LL_EXTI1_LINE_30 | LL_EXTI1_LINE_31)
/*!< All Extended line not reserved*/

#define LL_EXTI1_DIRECT_LINE_ALL_0_31 \
  ( LL_EXTI1_LINE_19 | \
    LL_EXTI1_LINE_21 | LL_EXTI1_LINE_22 | LL_EXTI1_LINE_23 | \
    LL_EXTI1_LINE_24 | LL_EXTI1_LINE_25 | LL_EXTI1_LINE_26 | \
    LL_EXTI1_LINE_27 | LL_EXTI1_LINE_28 | LL_EXTI1_LINE_29 | \
    LL_EXTI1_LINE_30 | LL_EXTI1_LINE_31)
/*!< All direct lines*/

#define LL_EXTI1_CONFIG_LINE_ALL_0_31 \
  ( LL_EXTI1_LINE_0  | LL_EXTI1_LINE_1  | LL_EXTI1_LINE_2 | \
    LL_EXTI1_LINE_3  | LL_EXTI1_LINE_4  | LL_EXTI1_LINE_5 | \
    LL_EXTI1_LINE_6  | LL_EXTI1_LINE_7  | LL_EXTI1_LINE_8 | \
    LL_EXTI1_LINE_9  | LL_EXTI1_LINE_10 | LL_EXTI1_LINE_11 | \
    LL_EXTI1_LINE_12 | LL_EXTI1_LINE_13 | LL_EXTI1_LINE_14 | \
    LL_EXTI1_LINE_15 | LL_EXTI1_LINE_16 | LL_EXTI1_LINE_17 | \
    LL_EXTI1_LINE_18 )
/*!< All configurable lines */

#define LL_EXTI1_LINE_32                 EXTI1_IMR2_IM32   /*!< Extended line 32 */
#define LL_EXTI1_LINE_33                 EXTI1_IMR2_IM33   /*!< Extended line 33 */
#define LL_EXTI1_LINE_34                 EXTI1_IMR2_IM34   /*!< Extended line 34 */
/* no line 35 */
#define LL_EXTI1_LINE_36                 EXTI1_IMR2_IM36   /*!< Extended line 36 */
#define LL_EXTI1_LINE_37                 EXTI1_IMR2_IM37   /*!< Extended line 37 */
#define LL_EXTI1_LINE_38                 EXTI1_IMR2_IM38   /*!< Extended line 38 */
#define LL_EXTI1_LINE_39                 EXTI1_IMR2_IM39   /*!< Extended line 39 */
#define LL_EXTI1_LINE_40                 EXTI1_IMR2_IM40   /*!< Extended line 40 */
#define LL_EXTI1_LINE_41                 EXTI1_IMR2_IM41   /*!< Extended line 41 */
#define LL_EXTI1_LINE_42                 EXTI1_IMR2_IM42   /*!< Extended line 42 */
#define LL_EXTI1_LINE_43                 EXTI1_IMR2_IM43   /*!< Extended line 43 */
#define LL_EXTI1_LINE_44                 EXTI1_IMR2_IM44   /*!< Extended line 44 */
#define LL_EXTI1_LINE_45                 EXTI1_IMR2_IM45   /*!< Extended line 45 */
#define LL_EXTI1_LINE_46                 EXTI1_IMR2_IM46   /*!< Extended line 46 */
#define LL_EXTI1_LINE_47                 EXTI1_IMR2_IM47   /*!< Extended line 47 */
#define LL_EXTI1_LINE_48                 EXTI1_IMR2_IM48   /*!< Extended line 48 */
#define LL_EXTI1_LINE_49                 EXTI1_IMR2_IM49   /*!< Extended line 49 */
#define LL_EXTI1_LINE_50                 EXTI1_IMR2_IM50   /*!< Extended line 50 */
/* no line 51 */
#define LL_EXTI1_LINE_52                 EXTI1_IMR2_IM52   /*!< Extended line 52 */
#define LL_EXTI1_LINE_53                 EXTI1_IMR2_IM53   /*!< Extended line 53 */
#define LL_EXTI1_LINE_54                 EXTI1_IMR2_IM54   /*!< Extended line 54 */
#define LL_EXTI1_LINE_55                 EXTI1_IMR2_IM55   /*!< Extended line 55 */
#define LL_EXTI1_LINE_56                 EXTI1_IMR2_IM56   /*!< Extended line 56 */
#define LL_EXTI1_LINE_57                 EXTI1_IMR2_IM57   /*!< Extended line 57 */
/* no line 57 */
#define LL_EXTI1_LINE_59                 EXTI1_IMR2_IM59   /*!< Extended line 59 */
#define LL_EXTI1_LINE_60                 EXTI1_IMR2_IM60   /*!< Extended line 60 */
#define LL_EXTI1_LINE_61                 EXTI1_IMR2_IM61   /*!< Extended line 61 */
#define LL_EXTI1_LINE_62                 EXTI1_IMR2_IM62   /*!< Extended line 62 */
/* no line 63 */

#define LL_EXTI1_LINE_ALL_32_63 \
  ( LL_EXTI1_LINE_32 | LL_EXTI1_LINE_33 | LL_EXTI1_LINE_34 | \
    LL_EXTI1_LINE_36 | LL_EXTI1_LINE_37 | LL_EXTI1_LINE_38 | \
    LL_EXTI1_LINE_39 | LL_EXTI1_LINE_40 | LL_EXTI1_LINE_41 | \
    LL_EXTI1_LINE_42 | LL_EXTI1_LINE_43 | LL_EXTI1_LINE_44 | \
    LL_EXTI1_LINE_45 | LL_EXTI1_LINE_46 | LL_EXTI1_LINE_47 | LL_EXTI1_LINE_48 | \
    LL_EXTI1_LINE_49 | LL_EXTI1_LINE_50 | LL_EXTI1_LINE_52 | \
    LL_EXTI1_LINE_53 | LL_EXTI1_LINE_54 | LL_EXTI1_LINE_55 | \
    LL_EXTI1_LINE_56 | LL_EXTI1_LINE_57 | LL_EXTI1_LINE_59 | \
    LL_EXTI1_LINE_60 | LL_EXTI1_LINE_61 | LL_EXTI1_LINE_62 )
/*!< All direct line */

#define LL_EXTI1_DIRECT_LINE_ALL_32_63 \
  ( LL_EXTI1_LINE_32 | LL_EXTI1_LINE_33 | LL_EXTI1_LINE_34 | \
    LL_EXTI1_LINE_36 | LL_EXTI1_LINE_37 | LL_EXTI1_LINE_38 | \
    LL_EXTI1_LINE_39 | LL_EXTI1_LINE_40 | LL_EXTI1_LINE_41 | \
    LL_EXTI1_LINE_42 | \
    LL_EXTI1_LINE_46 | LL_EXTI1_LINE_47 | LL_EXTI1_LINE_48 | \
    LL_EXTI1_LINE_49 | LL_EXTI1_LINE_50 | LL_EXTI1_LINE_52 | \
    LL_EXTI1_LINE_53 | LL_EXTI1_LINE_54 | LL_EXTI1_LINE_55 | \
    LL_EXTI1_LINE_56 | LL_EXTI1_LINE_57 | LL_EXTI1_LINE_59 | \
    LL_EXTI1_LINE_60 | LL_EXTI1_LINE_61 | LL_EXTI1_LINE_62 )
/*!< All Extended line not reserved*/

#define LL_EXTI1_CONFIG_LINE_ALL_32_63 \
  ( LL_EXTI1_LINE_43 | LL_EXTI1_LINE_44 | LL_EXTI1_LINE_45  )
/*!< All configurable lines */

#define LL_EXTI1_LINE_64                 EXTI1_IMR3_IM64   /*!< Extended line 64 */
#define LL_EXTI1_LINE_65                 EXTI1_IMR3_IM65   /*!< Extended line 65 */
#define LL_EXTI1_LINE_67                 EXTI1_IMR3_IM67   /*!< Extended line 67 */
#define LL_EXTI1_LINE_68                 EXTI1_IMR3_IM68   /*!< Extended line 68 */
#define LL_EXTI1_LINE_70                 EXTI1_IMR3_IM70   /*!< Extended line 70 */
#define LL_EXTI1_LINE_72                 EXTI1_IMR3_IM72   /*!< Extended line 72 */
#define LL_EXTI1_LINE_73                 EXTI1_IMR3_IM73   /*!< Extended line 73 */
#define LL_EXTI1_LINE_74                 EXTI1_IMR3_IM74   /*!< Extended line 74 */
#define LL_EXTI1_LINE_75                 EXTI1_IMR3_IM75   /*!< Extended line 75 */
#define LL_EXTI1_LINE_76                 EXTI1_IMR3_IM76   /*!< Extended line 76 */
#define LL_EXTI1_LINE_77                 EXTI1_IMR3_IM77   /*!< Extended line 77 */
#define LL_EXTI1_LINE_78                 EXTI1_IMR3_IM78   /*!< Extended line 78 */
#define LL_EXTI1_LINE_79                 EXTI1_IMR3_IM79   /*!< Extended line 79 */
#define LL_EXTI1_LINE_80                 EXTI1_IMR3_IM80   /*!< Extended line 80 */
#define LL_EXTI1_LINE_81                 EXTI1_IMR3_IM81   /*!< Extended line 81 */
#define LL_EXTI1_LINE_82                 EXTI1_IMR3_IM82   /*!< Extended line 82 */
#define LL_EXTI1_LINE_83                 EXTI1_IMR3_IM83   /*!< Extended line 83 */
#define LL_EXTI1_LINE_84                 EXTI1_IMR3_IM84   /*!< Extended line 84 */

#define LL_EXTI1_LINE_ALL_64_95 \
  ( LL_EXTI1_LINE_64 | LL_EXTI1_LINE_65 | LL_EXTI1_LINE_67 | \
    LL_EXTI1_LINE_68 |  LL_EXTI1_LINE_70 | \
    LL_EXTI1_LINE_72 | LL_EXTI1_LINE_73 | \
    LL_EXTI1_LINE_74 | LL_EXTI1_LINE_75 | LL_EXTI1_LINE_76 | \
    LL_EXTI1_LINE_77 | LL_EXTI1_LINE_78 | LL_EXTI1_LINE_79 | \
    LL_EXTI1_LINE_80 | LL_EXTI1_LINE_81 | LL_EXTI1_LINE_82 | \
    LL_EXTI1_LINE_83 | LL_EXTI1_LINE_84)
/*!< All Extended line not reserved*/

#define LL_EXTI1_DIRECT_LINE_ALL_64_95 \
  ( LL_EXTI1_LINE_68 | LL_EXTI1_LINE_70 | \
    LL_EXTI1_LINE_72 | LL_EXTI1_LINE_74 | LL_EXTI1_LINE_75 | LL_EXTI1_LINE_76 | \
    LL_EXTI1_LINE_77 | LL_EXTI1_LINE_78 | LL_EXTI1_LINE_79 | LL_EXTI1_LINE_80 | \
    LL_EXTI1_LINE_81 | LL_EXTI1_LINE_82 )
/*!< All Extended line not reserved*/

#define LL_EXTI1_CONFIG_LINE_ALL_64_95 \
  ( LL_EXTI1_LINE_64 | LL_EXTI1_LINE_65 | LL_EXTI1_LINE_67 | \
    LL_EXTI1_LINE_73 | LL_EXTI1_LINE_83 | LL_EXTI1_LINE_84)
/*!< All Extended line not reserved*/

/**
  * @}
  */

/** @defgroup LL_EXTI1_SEC_x EXTI1 Secure x
  * @{
  */
#define LL_EXTI1_SEC_0              EXTI1_SECCFGR1_SEC0   /*!< Secure Line 0 */
#define LL_EXTI1_SEC_1              EXTI1_SECCFGR1_SEC1   /*!< Secure Line 1 */
#define LL_EXTI1_SEC_2              EXTI1_SECCFGR1_SEC2   /*!< Secure Line 2 */
#define LL_EXTI1_SEC_3              EXTI1_SECCFGR1_SEC3   /*!< Secure Line 3 */
#define LL_EXTI1_SEC_4              EXTI1_SECCFGR1_SEC4   /*!< Secure Line 4 */
#define LL_EXTI1_SEC_5              EXTI1_SECCFGR1_SEC5   /*!< Secure Line 5 */
#define LL_EXTI1_SEC_6              EXTI1_SECCFGR1_SEC6   /*!< Secure Line 6 */
#define LL_EXTI1_SEC_7              EXTI1_SECCFGR1_SEC7   /*!< Secure Line 7 */
#define LL_EXTI1_SEC_8              EXTI1_SECCFGR1_SEC8   /*!< Secure Line 8 */
#define LL_EXTI1_SEC_9              EXTI1_SECCFGR1_SEC9   /*!< Secure Line 9 */
#define LL_EXTI1_SEC_10             EXTI1_SECCFGR1_SEC10  /*!< Secure Line 10 */
#define LL_EXTI1_SEC_11             EXTI1_SECCFGR1_SEC11  /*!< Secure Line 11 */
#define LL_EXTI1_SEC_12             EXTI1_SECCFGR1_SEC12  /*!< Secure Line 12 */
#define LL_EXTI1_SEC_13             EXTI1_SECCFGR1_SEC13  /*!< Secure Line 13 */
#define LL_EXTI1_SEC_14             EXTI1_SECCFGR1_SEC14  /*!< Secure Line 14 */
#define LL_EXTI1_SEC_15             EXTI1_SECCFGR1_SEC15  /*!< Secure Line 15 */
#define LL_EXTI1_SEC_16             EXTI1_SECCFGR1_SEC16  /*!< Secure Line 16 */
#define LL_EXTI1_SEC_17             EXTI1_SECCFGR1_SEC17  /*!< Secure Line 17 */
#define LL_EXTI1_SEC_18             EXTI1_SECCFGR1_SEC18  /*!< Secure Line 18 */
#define LL_EXTI1_SEC_19             EXTI1_SECCFGR1_SEC19  /*!< Secure Line 19 */
/*#define LL_EXTI1_SEC_20              EXTI1_SECCFGR1_SEC20  !< Secure Line 20 */
#define LL_EXTI1_SEC_21             EXTI1_SECCFGR1_SEC21  /*!< Secure Line 21 */
#define LL_EXTI1_SEC_22             EXTI1_SECCFGR1_SEC22  /*!< Secure Line 22 */
#define LL_EXTI1_SEC_23             EXTI1_SECCFGR1_SEC23  /*!< Secure Line 23 */
#define LL_EXTI1_SEC_24             EXTI1_SECCFGR1_SEC24  /*!< Secure Line 24 */
#define LL_EXTI1_SEC_25             EXTI1_SECCFGR1_SEC25  /*!< Secure Line 25 */
#define LL_EXTI1_SEC_26             EXTI1_SECCFGR1_SEC26  /*!< Secure Line 26 */
#define LL_EXTI1_SEC_27             EXTI1_SECCFGR1_SEC27  /*!< Secure Line 27 */
#define LL_EXTI1_SEC_28             EXTI1_SECCFGR1_SEC28  /*!< Secure Line 28 */
#define LL_EXTI1_SEC_29             EXTI1_SECCFGR1_SEC29  /*!< Secure Line 29 */
#define LL_EXTI1_SEC_30             EXTI1_SECCFGR1_SEC30  /*!< Secure Line 30 */
#define LL_EXTI1_SEC_31             EXTI1_SECCFGR1_SEC31  /*!< Secure Line 31 */

#define LL_EXTI1_SEC_ALL_0_31 \
  ( LL_EXTI1_SEC_0 | LL_EXTI1_SEC_1  | LL_EXTI1_SEC_2 | \
    LL_EXTI1_SEC_3  | LL_EXTI1_SEC_4  | LL_EXTI1_SEC_5 | \
    LL_EXTI1_SEC_6  | LL_EXTI1_SEC_7  | LL_EXTI1_SEC_8 | \
    LL_EXTI1_SEC_9  | LL_EXTI1_SEC_10 | LL_EXTI1_SEC_11 | \
    LL_EXTI1_SEC_12 | LL_EXTI1_SEC_13 | LL_EXTI1_SEC_14 | \
    LL_EXTI1_SEC_15 | LL_EXTI1_SEC_16 | LL_EXTI1_SEC_17 | \
    LL_EXTI1_SEC_18 | LL_EXTI1_SEC_19 | \
    LL_EXTI1_SEC_21 | LL_EXTI1_SEC_22 | LL_EXTI1_SEC_23 | \
    LL_EXTI1_SEC_24 | LL_EXTI1_SEC_25 | LL_EXTI1_SEC_26 | \
    LL_EXTI1_SEC_27 | LL_EXTI1_SEC_28 | LL_EXTI1_SEC_29 | \
    LL_EXTI1_SEC_30 | LL_EXTI1_SEC_31)
/*!< All Extended secure line not reserved*/


#define LL_EXTI1_SEC_32             EXTI1_SECCFGR2_SEC32   /*!< Secure Line 0 */
#define LL_EXTI1_SEC_33             EXTI1_SECCFGR2_SEC33   /*!< Secure Line 1 */
#define LL_EXTI1_SEC_34             EXTI1_SECCFGR2_SEC34   /*!< Secure Line 2 */
/*#define LL_EXTI1_SEC_35             EXTI1_SECCFGR2_SEC35   !< Secure Line 3 */
#define LL_EXTI1_SEC_36             EXTI1_SECCFGR2_SEC36   /*!< Secure Line 4 */
#define LL_EXTI1_SEC_37             EXTI1_SECCFGR2_SEC37   /*!< Secure Line 5 */
#define LL_EXTI1_SEC_38             EXTI1_SECCFGR2_SEC38   /*!< Secure Line 6 */
#define LL_EXTI1_SEC_39             EXTI1_SECCFGR2_SEC39   /*!< Secure Line 7 */
#define LL_EXTI1_SEC_40             EXTI1_SECCFGR2_SEC40   /*!< Secure Line 8 */
#define LL_EXTI1_SEC_41             EXTI1_SECCFGR2_SEC41   /*!< Secure Line 9 */
#define LL_EXTI1_SEC_42             EXTI1_SECCFGR2_SEC42  /*!< Secure Line 10 */
#define LL_EXTI1_SEC_43             EXTI1_SECCFGR2_SEC43  /*!< Secure Line 11 */
#define LL_EXTI1_SEC_44             EXTI1_SECCFGR2_SEC44  /*!< Secure Line 12 */
#define LL_EXTI1_SEC_45             EXTI1_SECCFGR2_SEC45  /*!< Secure Line 13 */
#define LL_EXTI1_SEC_46             EXTI1_SECCFGR2_SEC46  /*!< Secure Line 14 */
#define LL_EXTI1_SEC_47             EXTI1_SECCFGR2_SEC47  /*!< Secure Line 15 */
#define LL_EXTI1_SEC_48             EXTI1_SECCFGR2_SEC48  /*!< Secure Line 16 */
#define LL_EXTI1_SEC_49             EXTI1_SECCFGR2_SEC49  /*!< Secure Line 17 */
#define LL_EXTI1_SEC_50             EXTI1_SECCFGR2_SEC50  /*!< Secure Line 18 */
/*#define LL_EXTI1_SEC_51             EXTI1_SECCFGR2_SEC51  !< Secure Line 19 */
#define LL_EXTI1_SEC_52              EXTI1_SECCFGR2_SEC52  /*!< Secure Line 20 */
#define LL_EXTI1_SEC_53             EXTI1_SECCFGR2_SEC53  /*!< Secure Line 21 */
#define LL_EXTI1_SEC_54             EXTI1_SECCFGR2_SEC54  /*!< Secure Line 22 */
#define LL_EXTI1_SEC_55             EXTI1_SECCFGR2_SEC55  /*!< Secure Line 23 */
#define LL_EXTI1_SEC_56             EXTI1_SECCFGR2_SEC56  /*!< Secure Line 24 */
#define LL_EXTI1_SEC_57             EXTI1_SECCFGR2_SEC57  /*!< Secure Line 25 */
/*#define LL_EXTI1_SEC_58             EXTI1_SECCFGR2_SEC58  !< Secure Line 26 */
#define LL_EXTI1_SEC_59             EXTI1_SECCFGR2_SEC59  /*!< Secure Line 27 */
#define LL_EXTI1_SEC_60             EXTI1_SECCFGR2_SEC60  /*!< Secure Line 28 */
#define LL_EXTI1_SEC_61             EXTI1_SECCFGR2_SEC61  /*!< Secure Line 29 */
#define LL_EXTI1_SEC_62             EXTI1_SECCFGR2_SEC62  /*!< Secure Line 30 */
/*#define LL_EXTI1_SEC_63             EXTI1_SECCFGR2_SEC63  !< Secure Line 31 */

#define LL_EXTI1_SEC_ALL_32_63 \
  ( LL_EXTI1_SEC_32 | LL_EXTI1_SEC_33 | LL_EXTI1_SEC_34 | \
    LL_EXTI1_SEC_36 | LL_EXTI1_SEC_37 | LL_EXTI1_SEC_38 | \
    LL_EXTI1_SEC_39 | LL_EXTI1_SEC_40 | LL_EXTI1_SEC_41 | \
    LL_EXTI1_SEC_42 | LL_EXTI1_SEC_43 | LL_EXTI1_SEC_44 | \
    LL_EXTI1_SEC_45 | LL_EXTI1_SEC_46 | LL_EXTI1_SEC_47 | LL_EXTI1_SEC_48 | \
    LL_EXTI1_SEC_49 | LL_EXTI1_SEC_50 | LL_EXTI1_SEC_52 | \
    LL_EXTI1_SEC_53 | LL_EXTI1_SEC_54 | LL_EXTI1_SEC_55 | \
    LL_EXTI1_SEC_56 | LL_EXTI1_SEC_57 | LL_EXTI1_SEC_59 | \
    LL_EXTI1_SEC_60 | LL_EXTI1_SEC_61 | LL_EXTI1_LINE_62 )
/*!< All Extended line not reserved*/

#define LL_EXTI1_SEC_64             EXTI1_SECCFGR3_SEC64   /*!< Secure Line 0 */
#define LL_EXTI1_SEC_65             EXTI1_SECCFGR3_SEC65  /*!< Secure Line 1 */
/*#define LL_EXTI1_SEC_66             EXTI1_SECCFGR3_SEC66   !< Secure Line 2 */
#define LL_EXTI1_SEC_67             EXTI1_SECCFGR3_SEC67  /*!< Secure Line 3 */
#define LL_EXTI1_SEC_68             EXTI1_SECCFGR3_SEC68  /*!< Secure Line 4 */
/*#define LL_EXTI1_SEC_69             EXTI1_SECCFGR3_SEC69   !< Secure Line 5 */
#define LL_EXTI1_SEC_70             EXTI1_SECCFGR3_SEC70  /*!< Secure Line 6 */
/*#define LL_EXTI1_SEC_71             EXTI1_SECCFGR3_SEC71   !< Secure Line 7 */
#define LL_EXTI1_SEC_72             EXTI1_SECCFGR3_SEC72  /*!< Secure Line 8 */
#define LL_EXTI1_SEC_73             EXTI1_SECCFGR3_SEC73  /*!< Secure Line 9 */
#define LL_EXTI1_SEC_74             EXTI1_SECCFGR3_SEC74  /*!< Secure Line 10 */
#define LL_EXTI1_SEC_75             EXTI1_SECCFGR3_SEC75  /*!< Secure Line 11 */
#define LL_EXTI1_SEC_76             EXTI1_SECCFGR3_SEC76  /*!< Secure Line 12 */
#define LL_EXTI1_SEC_77             EXTI1_SECCFGR3_SEC77  /*!< Secure Line 13 */
#define LL_EXTI1_SEC_78             EXTI1_SECCFGR3_SEC78  /*!< Secure Line 14 */
#define LL_EXTI1_SEC_79             EXTI1_SECCFGR3_SEC79  /*!< Secure Line 15 */
#define LL_EXTI1_SEC_80             EXTI1_SECCFGR3_SEC80  /*!< Secure Line 16 */
#define LL_EXTI1_SEC_81             EXTI1_SECCFGR3_SEC81  /*!< Secure Line 17 */
#define LL_EXTI1_SEC_82             EXTI1_SECCFGR3_SEC82  /*!< Secure Line 18 */
#define LL_EXTI1_SEC_83             EXTI1_SECCFGR3_SEC83  /*!< Secure Line 19 */
#define LL_EXTI1_SEC_84             EXTI1_SECCFGR3_SEC84  /*!< Secure Line 20 */

#define LL_EXTI1_SEC_ALL_64_95 \
  ( LL_EXTI1_SEC_64 | LL_EXTI1_SEC_65 | LL_EXTI1_SEC_67 | \
    LL_EXTI1_SEC_68 |  LL_EXTI1_SEC_70 | \
    LL_EXTI1_SEC_72 | LL_EXTI1_SEC_73 | \
    LL_EXTI1_SEC_74 | LL_EXTI1_SEC_75 | LL_EXTI1_SEC_76 | \
    LL_EXTI1_SEC_77 | LL_EXTI1_SEC_78 | LL_EXTI1_SEC_79 | \
    LL_EXTI1_SEC_80 | LL_EXTI1_SEC_81 | LL_EXTI1_SEC_82 | \
    LL_EXTI1_SEC_83 | LL_EXTI1_SEC_84)
/*!< All Extended secure line not reserved*/

/**
  * @}
  */

/** @defgroup LL_EXTI1_PRIV_x EXTI1 Privilege x
  * @{
  */
#define LL_EXTI1_PRIV_0              EXTI1_PRIVCFGR1_PRIV0   /*!< Secure Line 0 */
#define LL_EXTI1_PRIV_1              EXTI1_PRIVCFGR1_PRIV1   /*!< Secure Line 1 */
#define LL_EXTI1_PRIV_2              EXTI1_PRIVCFGR1_PRIV2   /*!< Secure Line 2 */
#define LL_EXTI1_PRIV_3              EXTI1_PRIVCFGR1_PRIV3   /*!< Secure Line 3 */
#define LL_EXTI1_PRIV_4              EXTI1_PRIVCFGR1_PRIV4   /*!< Secure Line 4 */
#define LL_EXTI1_PRIV_5              EXTI1_PRIVCFGR1_PRIV5   /*!< Secure Line 5 */
#define LL_EXTI1_PRIV_6              EXTI1_PRIVCFGR1_PRIV6   /*!< Secure Line 6 */
#define LL_EXTI1_PRIV_7              EXTI1_PRIVCFGR1_PRIV7   /*!< Secure Line 7 */
#define LL_EXTI1_PRIV_8              EXTI1_PRIVCFGR1_PRIV8   /*!< Secure Line 8 */
#define LL_EXTI1_PRIV_9              EXTI1_PRIVCFGR1_PRIV9   /*!< Secure Line 9 */
#define LL_EXTI1_PRIV_10             EXTI1_PRIVCFGR1_PRIV10  /*!< Secure Line 10 */
#define LL_EXTI1_PRIV_11             EXTI1_PRIVCFGR1_PRIV11  /*!< Secure Line 11 */
#define LL_EXTI1_PRIV_12             EXTI1_PRIVCFGR1_PRIV12  /*!< Secure Line 12 */
#define LL_EXTI1_PRIV_13             EXTI1_PRIVCFGR1_PRIV13  /*!< Secure Line 13 */
#define LL_EXTI1_PRIV_14             EXTI1_PRIVCFGR1_PRIV14  /*!< Secure Line 14 */
#define LL_EXTI1_PRIV_15             EXTI1_PRIVCFGR1_PRIV15  /*!< Secure Line 15 */
#define LL_EXTI1_PRIV_16             EXTI1_PRIVCFGR1_PRIV16  /*!< Secure Line 16 */
#define LL_EXTI1_PRIV_17             EXTI1_PRIVCFGR1_PRIV17  /*!< Secure Line 17 */
#define LL_EXTI1_PRIV_18             EXTI1_PRIVCFGR1_PRIV18  /*!< Secure Line 18 */
#define LL_EXTI1_PRIV_19             EXTI1_PRIVCFGR1_PRIV19  /*!< Secure Line 19 */
/*#define LL_EXTI1_PRIV_20              EXTI1_PRIVCFGR1_PRIV20  !< Secure Line 20 */
#define LL_EXTI1_PRIV_21             EXTI1_PRIVCFGR1_PRIV21  /*!< Secure Line 21 */
#define LL_EXTI1_PRIV_22             EXTI1_PRIVCFGR1_PRIV22  /*!< Secure Line 22 */
#define LL_EXTI1_PRIV_23             EXTI1_PRIVCFGR1_PRIV23  /*!< Secure Line 23 */
#define LL_EXTI1_PRIV_24             EXTI1_PRIVCFGR1_PRIV24  /*!< Secure Line 24 */
#define LL_EXTI1_PRIV_25             EXTI1_PRIVCFGR1_PRIV25  /*!< Secure Line 25 */
#define LL_EXTI1_PRIV_26             EXTI1_PRIVCFGR1_PRIV26  /*!< Secure Line 26 */
#define LL_EXTI1_PRIV_27             EXTI1_PRIVCFGR1_PRIV27  /*!< Secure Line 27 */
#define LL_EXTI1_PRIV_28             EXTI1_PRIVCFGR1_PRIV28  /*!< Secure Line 28 */
#define LL_EXTI1_PRIV_29             EXTI1_PRIVCFGR1_PRIV29  /*!< Secure Line 29 */
#define LL_EXTI1_PRIV_30             EXTI1_PRIVCFGR1_PRIV30  /*!< Secure Line 30 */
#define LL_EXTI1_PRIV_31             EXTI1_PRIVCFGR1_PRIV31  /*!< Secure Line 31 */

#define LL_EXTI1_PRIV_ALL_0_31 \
  ( LL_EXTI1_PRIV_0 | LL_EXTI1_PRIV_1  | LL_EXTI1_PRIV_2 | \
    LL_EXTI1_PRIV_3  | LL_EXTI1_PRIV_4  | LL_EXTI1_PRIV_5 | \
    LL_EXTI1_PRIV_6  | LL_EXTI1_PRIV_7  | LL_EXTI1_PRIV_8 | \
    LL_EXTI1_PRIV_9  | LL_EXTI1_PRIV_10 | LL_EXTI1_PRIV_11 | \
    LL_EXTI1_PRIV_12 | LL_EXTI1_PRIV_13 | LL_EXTI1_PRIV_14 | \
    LL_EXTI1_PRIV_15 | LL_EXTI1_PRIV_16 | LL_EXTI1_PRIV_17 | \
    LL_EXTI1_PRIV_18 | LL_EXTI1_PRIV_19 | \
    LL_EXTI1_PRIV_21 | LL_EXTI1_PRIV_22 | LL_EXTI1_PRIV_23 | \
    LL_EXTI1_PRIV_24 | LL_EXTI1_PRIV_25 | LL_EXTI1_PRIV_26 | \
    LL_EXTI1_PRIV_27 | LL_EXTI1_PRIV_28 | LL_EXTI1_PRIV_29 | \
    LL_EXTI1_PRIV_30 | LL_EXTI1_PRIV_31)
/*!< All Extended secure line not reserved*/

#define LL_EXTI1_PRIV_32             EXTI1_PRIVCFGR2_PRIV32   /*!< Secure Line 0 */
#define LL_EXTI1_PRIV_33             EXTI1_PRIVCFGR2_PRIV33   /*!< Secure Line 1 */
#define LL_EXTI1_PRIV_34             EXTI1_PRIVCFGR2_PRIV34  /*!< Secure Line 2 */
/*#define LL_EXTI1_PRIV_35             EXTI1_PRIVCFGR2_PRIV35  !< Secure Line 3 */
#define LL_EXTI1_PRIV_36             EXTI1_PRIVCFGR2_PRIV36  /*!< Secure Line 4 */
#define LL_EXTI1_PRIV_37             EXTI1_PRIVCFGR2_PRIV37  /*!< Secure Line 5 */
#define LL_EXTI1_PRIV_38             EXTI1_PRIVCFGR2_PRIV38  /*!< Secure Line 6 */
#define LL_EXTI1_PRIV_39             EXTI1_PRIVCFGR2_PRIV39  /*!< Secure Line 7 */
#define LL_EXTI1_PRIV_40             EXTI1_PRIVCFGR2_PRIV40  /*!< Secure Line 8 */
#define LL_EXTI1_PRIV_41             EXTI1_PRIVCFGR2_PRIV41  /*!< Secure Line 9 */
#define LL_EXTI1_PRIV_42             EXTI1_PRIVCFGR2_PRIV42  /*!< Secure Line 10 */
#define LL_EXTI1_PRIV_43             EXTI1_PRIVCFGR2_PRIV43  /*!< Secure Line 11 */
#define LL_EXTI1_PRIV_44             EXTI1_PRIVCFGR2_PRIV44  /*!< Secure Line 12 */
#define LL_EXTI1_PRIV_45             EXTI1_PRIVCFGR2_PRIV45  /*!< Secure Line 13 */
#define LL_EXTI1_PRIV_46             EXTI1_PRIVCFGR2_PRIV46  /*!< Secure Line 14 */
#define LL_EXTI1_PRIV_47             EXTI1_PRIVCFGR2_PRIV47  /*!< Secure Line 15 */
#define LL_EXTI1_PRIV_48             EXTI1_PRIVCFGR2_PRIV48  /*!< Secure Line 16 */
#define LL_EXTI1_PRIV_49             EXTI1_PRIVCFGR2_PRIV49  /*!< Secure Line 17 */
#define LL_EXTI1_PRIV_50             EXTI1_PRIVCFGR2_PRIV50  /*!< Secure Line 18 */
/*#define LL_EXTI1_PRIV_51             EXTI1_PRIVCFGR2_PRIV51  !< Secure Line 19 */
#define LL_EXTI1_PRIV_52              EXTI1_PRIVCFGR2_PRIV52  /*!< Secure Line 20 */
#define LL_EXTI1_PRIV_53             EXTI1_PRIVCFGR2_PRIV53  /*!< Secure Line 21 */
#define LL_EXTI1_PRIV_54             EXTI1_PRIVCFGR2_PRIV54  /*!< Secure Line 22 */
#define LL_EXTI1_PRIV_55             EXTI1_PRIVCFGR2_PRIV55  /*!< Secure Line 23 */
#define LL_EXTI1_PRIV_56             EXTI1_PRIVCFGR2_PRIV56  /*!< Secure Line 24 */
#define LL_EXTI1_PRIV_57             EXTI1_PRIVCFGR2_PRIV57  /*!< Secure Line 25 */
/*#define LL_EXTI1_PRIV_58             EXTI1_PRIVCFGR2_PRIV58  !< Secure Line 26 */
#define LL_EXTI1_PRIV_59             EXTI1_PRIVCFGR2_PRIV59  /*!< Secure Line 27 */
#define LL_EXTI1_PRIV_60             EXTI1_PRIVCFGR2_PRIV60  /*!< Secure Line 28 */
#define LL_EXTI1_PRIV_61             EXTI1_PRIVCFGR2_PRIV61  /*!< Secure Line 29 */
#define LL_EXTI1_PRIV_62             EXTI1_PRIVCFGR2_PRIV62  /*!< Secure Line 30 */
/*#define LL_EXTI1_PRIV_63             EXTI1_PRIVCFGR2_PRIV63  !< Secure Line 31 */

#define LL_EXTI1_PRIV_ALL_32_63 \
  ( LL_EXTI1_PRIV_32 | LL_EXTI1_PRIV_33 | LL_EXTI1_PRIV_34 | \
    LL_EXTI1_PRIV_36 | LL_EXTI1_PRIV_37 | LL_EXTI1_PRIV_38 | \
    LL_EXTI1_PRIV_39 | LL_EXTI1_PRIV_40 | LL_EXTI1_PRIV_41 | \
    LL_EXTI1_PRIV_42 | LL_EXTI1_PRIV_43 | LL_EXTI1_PRIV_44 | \
    LL_EXTI1_PRIV_45 | LL_EXTI1_PRIV_46 | LL_EXTI1_PRIV_47 | LL_EXTI1_PRIV_48 | \
    LL_EXTI1_PRIV_49 | LL_EXTI1_PRIV_50 | LL_EXTI1_PRIV_52 | \
    LL_EXTI1_PRIV_53 | LL_EXTI1_PRIV_54 | LL_EXTI1_PRIV_55 | \
    LL_EXTI1_PRIV_56 | LL_EXTI1_PRIV_57 | LL_EXTI1_PRIV_59 | \
    LL_EXTI1_PRIV_60 | LL_EXTI1_PRIV_61 | LL_EXTI1_LINE_62 )
/*!< All Extended line not reserved*/

#define LL_EXTI1_PRIV_64             EXTI1_PRIVCFGR3_PRIV64   /*!< Secure Line 0 */
#define LL_EXTI1_PRIV_65             EXTI1_PRIVCFGR3_PRIV65  /*!< Secure Line 1 */
#define LL_EXTI1_PRIV_66             EXTI1_PRIVCFGR3_PRIV66  /*!< Secure Line 2 */
#define LL_EXTI1_PRIV_67             EXTI1_PRIVCFGR3_PRIV67  /*!< Secure Line 3 */
#define LL_EXTI1_PRIV_68             EXTI1_PRIVCFGR3_PRIV68  /*!< Secure Line 4 */
#define LL_EXTI1_PRIV_69             EXTI1_PRIVCFGR3_PRIV69  /*!< Secure Line 5 */
#define LL_EXTI1_PRIV_70             EXTI1_PRIVCFGR3_PRIV70  /*!< Secure Line 6 */
#define LL_EXTI1_PRIV_71             EXTI1_PRIVCFGR3_PRIV71  /*!< Secure Line 7 */
#define LL_EXTI1_PRIV_72             EXTI1_PRIVCFGR3_PRIV72  /*!< Secure Line 8 */
#define LL_EXTI1_PRIV_73             EXTI1_PRIVCFGR3_PRIV73  /*!< Secure Line 9 */
#define LL_EXTI1_PRIV_74             EXTI1_PRIVCFGR3_PRIV74  /*!< Secure Line 10 */
#define LL_EXTI1_PRIV_75             EXTI1_PRIVCFGR3_PRIV75  /*!< Secure Line 11 */
#define LL_EXTI1_PRIV_76             EXTI1_PRIVCFGR3_PRIV76  /*!< Secure Line 12 */
#define LL_EXTI1_PRIV_77             EXTI1_PRIVCFGR3_PRIV77  /*!< Secure Line 13 */
#define LL_EXTI1_PRIV_78             EXTI1_PRIVCFGR3_PRIV78  /*!< Secure Line 14 */
#define LL_EXTI1_PRIV_79             EXTI1_PRIVCFGR3_PRIV79  /*!< Secure Line 15 */
#define LL_EXTI1_PRIV_80             EXTI1_PRIVCFGR3_PRIV80  /*!< Secure Line 16 */
#define LL_EXTI1_PRIV_81             EXTI1_PRIVCFGR3_PRIV81  /*!< Secure Line 17 */
#define LL_EXTI1_PRIV_82             EXTI1_PRIVCFGR3_PRIV82  /*!< Secure Line 18 */
#define LL_EXTI1_PRIV_83             EXTI1_PRIVCFGR3_PRIV83  /*!< Secure Line 19 */
#define LL_EXTI1_PRIV_84             EXTI1_PRIVCFGR3_PRIV84  /*!< Secure Line 20 */

#define LL_EXTI1_PRIV_ALL_64_95 \
  ( LL_EXTI1_PRIV_64 | LL_EXTI1_PRIV_65 | LL_EXTI1_PRIV_67 | \
    LL_EXTI1_PRIV_68 |  LL_EXTI1_PRIV_70 | \
    LL_EXTI1_PRIV_72 | LL_EXTI1_PRIV_73 | \
    LL_EXTI1_PRIV_74 | LL_EXTI1_PRIV_75 | LL_EXTI1_PRIV_76 | \
    LL_EXTI1_PRIV_77 | LL_EXTI1_PRIV_78 | LL_EXTI1_PRIV_79 | \
    LL_EXTI1_PRIV_80 | LL_EXTI1_PRIV_81 | LL_EXTI1_PRIV_82 | \
    LL_EXTI1_PRIV_83 | LL_EXTI1_PRIV_84)
/*!< All Extended secure line not reserved*/

/**
  * @}
  */

/** @defgroup LL_EXTI1_EVT_x EXTI1 Event x
  * @{
  */

/* No EMR1 */
/* No EMR2 */

#define LL_EXTI1_EVT_65                 EXTI1_EMR3_EM65   /*!< Extended EVT 65 */

#define LL_EXTI1_EVT_ALL_64_95 \
  ( LL_EXTI1_EVT_65)
/*!< All Extended EVT not reserved*/

/**
  * @}
  */


/** @defgroup LL_EXTI1_EnCIDCFGR_x EXTI1 EnCIDCFGR x
  * @{
  */
#define LL_EXTI1_EnCIDCFGR_0                  (0U)    /*!< E0CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_1                  (1U)    /*!< E1CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_2                  (2U)    /*!< E2CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_3                  (3U)    /*!< E3CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_4                  (4U)    /*!< E4CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_5                  (5U)    /*!< E5CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_6                  (6U)    /*!< E6CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_7                  (7U)    /*!< E7CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_8                  (8U)    /*!< E8CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_9                  (9U)    /*!< E9CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_10                 (10U)   /*!< E10CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_11                 (11U)   /*!< E11CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_12                 (12U)   /*!< E12CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_13                 (13U)   /*!< E13CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_14                 (14U)   /*!< E14CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_15                 (15U)   /*!< E15CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_16                 (16U)   /*!< E16CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_17                 (17U)   /*!< E17CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_18                 (18U)   /*!< E18CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_19                 (19U)   /*!< E19CIDCFGR */
/*!< no E20CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_21                 (21U)   /*!< E21CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_22                 (22U)   /*!< E22CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_23                 (23U)   /*!< E23CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_24                 (24U)   /*!< E24CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_25                 (25U)   /*!< E25CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_26                 (26U)   /*!< E26CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_27                 (27U)   /*!< E27CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_28                 (28U)   /*!< E28CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_29                 (29U)   /*!< E29CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_30                 (30U)   /*!< E30CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_31                 (31U)   /*!< E31CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_32                 (32U)   /*!< E32CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_33                 (33U)   /*!< E33CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_34                 (34U)   /*!< E34CIDCFGR */
/*!< no E35CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_36                 (36U)   /*!< E36CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_37                 (37U)   /*!< E37CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_38                 (38U)   /*!< E38CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_39                 (39U)   /*!< E39CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_40                 (40U)   /*!< E40CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_41                 (41U)   /*!< E41CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_42                 (42U)   /*!< E42CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_43                 (43U)   /*!< E43CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_44                 (44U)   /*!< E44CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_45                 (45U)   /*!< E45CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_46                 (46U)   /*!< E46CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_47                 (47U)   /*!< E47CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_48                 (48U)   /*!< E48CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_49                 (49U)   /*!< E49CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_50                 (50U)   /*!< E50CIDCFGR */
/*!< no E51CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_52                 (52U)   /*!< E52CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_53                 (53U)   /*!< E53CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_54                 (54U)   /*!< E54CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_55                 (55U)   /*!< E55CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_56                 (56U)   /*!< E56CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_57                 (57U)   /*!< E57CIDCFGR */
/*!< no E58CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_59                 (59U)   /*!< E59CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_60                 (60U)   /*!< E60CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_61                 (61U)   /*!< E61CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_62                 (62U)   /*!< E62CIDCFGR */
/*!< no E63CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_64                 (64U)   /*!< E64CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_65                 (65U)   /*!< E65CIDCFGR */
/*!< no E66CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_67                 (67U)   /*!< E67CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_68                 (68U)   /*!< E68CIDCFGR */
/*!< no E69CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_70                 (70U)   /*!< E70CIDCFGR */
/*!< no E71CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_72                 (72U)   /*!< E72CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_73                 (73U)   /*!< E73CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_74                 (74U)   /*!< E74CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_75                 (75U)   /*!< E75CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_76                 (76U)   /*!< E76CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_77                 (77U)   /*!< E77CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_78                 (78U)   /*!< E78CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_79                 (79U)   /*!< E79CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_80                 (80U)   /*!< E80CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_81                 (81U)   /*!< E81CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_82                 (82U)   /*!< E82CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_83                 (83U)   /*!< E83CIDCFGR */
#define LL_EXTI1_EnCIDCFGR_84                 (84U)   /*!< E84CIDCFGR */
#endif /* EXTI1 */

/**
  * @}
  */


/** @defgroup LL_EXTI2_LINE_x EXTI2 Line x
  * @{
  */
#define LL_EXTI2_LINE_0                  EXTI2_IMR1_IM0   /*!< Extended line 0 */
#define LL_EXTI2_LINE_1                  EXTI2_IMR1_IM1   /*!< Extended line 1 */
#define LL_EXTI2_LINE_2                  EXTI2_IMR1_IM2   /*!< Extended line 2 */
#define LL_EXTI2_LINE_3                  EXTI2_IMR1_IM3   /*!< Extended line 3 */
#define LL_EXTI2_LINE_4                  EXTI2_IMR1_IM4   /*!< Extended line 4 */
#define LL_EXTI2_LINE_5                  EXTI2_IMR1_IM5   /*!< Extended line 5 */
#define LL_EXTI2_LINE_6                  EXTI2_IMR1_IM6   /*!< Extended line 6 */
#define LL_EXTI2_LINE_7                  EXTI2_IMR1_IM7   /*!< Extended line 7 */
#define LL_EXTI2_LINE_8                  EXTI2_IMR1_IM8   /*!< Extended line 8 */
#define LL_EXTI2_LINE_9                  EXTI2_IMR1_IM9   /*!< Extended line 9 */
#define LL_EXTI2_LINE_10                 EXTI2_IMR1_IM10   /*!< Extended line 10 */
#define LL_EXTI2_LINE_11                 EXTI2_IMR1_IM11   /*!< Extended line 11 */
#define LL_EXTI2_LINE_12                 EXTI2_IMR1_IM12   /*!< Extended line 12 */
#define LL_EXTI2_LINE_13                 EXTI2_IMR1_IM13   /*!< Extended line 13 */
#define LL_EXTI2_LINE_14                 EXTI2_IMR1_IM14   /*!< Extended line 14 */
#define LL_EXTI2_LINE_15                 EXTI2_IMR1_IM15   /*!< Extended line 15 */
#define LL_EXTI2_LINE_16                 EXTI2_IMR1_IM16   /*!< Extended line 16 */
#define LL_EXTI2_LINE_17                 EXTI2_IMR1_IM17   /*!< Extended line 17 */
#define LL_EXTI2_LINE_18                 EXTI2_IMR1_IM18   /*!< Extended line 18 */
#define LL_EXTI2_LINE_19                 EXTI2_IMR1_IM19   /*!< Extended line 19 */
#define LL_EXTI2_LINE_20                 EXTI2_IMR1_IM20   /*!< Extended line 20 */
#define LL_EXTI2_LINE_21                 EXTI2_IMR1_IM21   /*!< Extended line 21 */
#define LL_EXTI2_LINE_22                 EXTI2_IMR1_IM22   /*!< Extended line 22 */
#define LL_EXTI2_LINE_23                 EXTI2_IMR1_IM23   /*!< Extended line 23 */
#define LL_EXTI2_LINE_24                 EXTI2_IMR1_IM24   /*!< Extended line 24 */
#define LL_EXTI2_LINE_25                 EXTI2_IMR1_IM25   /*!< Extended line 25 */
#define LL_EXTI2_LINE_26                 EXTI2_IMR1_IM26   /*!< Extended line 26 */
#define LL_EXTI2_LINE_27                 EXTI2_IMR1_IM27   /*!< Extended line 27 */
#define LL_EXTI2_LINE_29                 EXTI2_IMR1_IM29   /*!< Extended line 29 */
#define LL_EXTI2_LINE_30                 EXTI2_IMR1_IM30   /*!< Extended line 30 */
#define LL_EXTI2_LINE_31                 EXTI2_IMR1_IM31   /*!< Extended line 31 */

#define LL_EXTI2_LINE_ALL_0_31 \
  ( LL_EXTI2_LINE_0 | LL_EXTI2_LINE_1 | LL_EXTI2_LINE_2 | LL_EXTI2_LINE_3 | \
    LL_EXTI2_LINE_4 | LL_EXTI2_LINE_5 | LL_EXTI2_LINE_6 | \
    LL_EXTI2_LINE_7 | LL_EXTI2_LINE_8 | LL_EXTI2_LINE_9 | \
    LL_EXTI2_LINE_10 | LL_EXTI2_LINE_11 | LL_EXTI2_LINE_12 | \
    LL_EXTI2_LINE_13 | LL_EXTI2_LINE_14 | LL_EXTI2_LINE_15 | \
    LL_EXTI2_LINE_16 | LL_EXTI2_LINE_17 | LL_EXTI2_LINE_18 | \
    LL_EXTI2_LINE_19 | LL_EXTI2_LINE_20 | LL_EXTI2_LINE_21 | \
    LL_EXTI2_LINE_22 | LL_EXTI2_LINE_23 | LL_EXTI2_LINE_24 | \
    LL_EXTI2_LINE_25 | LL_EXTI2_LINE_26 | LL_EXTI2_LINE_27 | \
    LL_EXTI2_LINE_29 | LL_EXTI2_LINE_30 | LL_EXTI2_LINE_31)
/*!< All Extended line not reserved*/

#define LL_EXTI2_DIRECT_LINE_ALL_0_31 \
  ( LL_EXTI2_LINE_16 | LL_EXTI2_LINE_17 | LL_EXTI2_LINE_18 | \
    LL_EXTI2_LINE_19 | LL_EXTI2_LINE_20 | LL_EXTI2_LINE_21 | \
    LL_EXTI2_LINE_22 | LL_EXTI2_LINE_23 | LL_EXTI2_LINE_24 | \
    LL_EXTI2_LINE_25 | LL_EXTI2_LINE_26 | LL_EXTI2_LINE_27 | \
    LL_EXTI2_LINE_29 | LL_EXTI2_LINE_30 | LL_EXTI2_LINE_31)
/*!< All Extended line not reserved*/

#define LL_EXTI2_CONFIG_LINE_ALL_0_31 \
  ( LL_EXTI2_LINE_0 | LL_EXTI2_LINE_1 | LL_EXTI2_LINE_2 | LL_EXTI2_LINE_3 | \
    LL_EXTI2_LINE_4 | LL_EXTI2_LINE_5 | LL_EXTI2_LINE_6 | \
    LL_EXTI2_LINE_7 | LL_EXTI2_LINE_8 | LL_EXTI2_LINE_9 | \
    LL_EXTI2_LINE_10 | LL_EXTI2_LINE_11 | LL_EXTI2_LINE_12 | \
    LL_EXTI2_LINE_13 | LL_EXTI2_LINE_14 | LL_EXTI2_LINE_15 )
/*!< All Extended line not reserved*/

#define LL_EXTI2_LINE_33                 EXTI2_IMR2_IM33   /*!< Extended line 33 */
#define LL_EXTI2_LINE_34                 EXTI2_IMR2_IM34   /*!< Extended line 34 */
#define LL_EXTI2_LINE_35                 EXTI2_IMR2_IM35   /*!< Extended line 35 */
#define LL_EXTI2_LINE_36                 EXTI2_IMR2_IM36   /*!< Extended line 36 */
#define LL_EXTI2_LINE_37                 EXTI2_IMR2_IM37   /*!< Extended line 37 */
#define LL_EXTI2_LINE_38                 EXTI2_IMR2_IM38   /*!< Extended line 38 */
#define LL_EXTI2_LINE_40                 EXTI2_IMR2_IM40   /*!< Extended line 40 */
#define LL_EXTI2_LINE_41                 EXTI2_IMR2_IM41   /*!< Extended line 41 */
#define LL_EXTI2_LINE_42                 EXTI2_IMR2_IM42   /*!< Extended line 42 */
#define LL_EXTI2_LINE_43                 EXTI2_IMR2_IM43   /*!< Extended line 43 */
#define LL_EXTI2_LINE_44                 EXTI2_IMR2_IM44   /*!< Extended line 44 */
#define LL_EXTI2_LINE_46                 EXTI2_IMR2_IM46   /*!< Extended line 46 */
#define LL_EXTI2_LINE_47                 EXTI2_IMR2_IM47   /*!< Extended line 47 */
#define LL_EXTI2_LINE_48                 EXTI2_IMR2_IM48   /*!< Extended line 48 */
#define LL_EXTI2_LINE_49                 EXTI2_IMR2_IM49   /*!< Extended line 49 */
#define LL_EXTI2_LINE_50                 EXTI2_IMR2_IM50   /*!< Extended line 50 */
#define LL_EXTI2_LINE_51                 EXTI2_IMR2_IM51   /*!< Extended line 51 */
#define LL_EXTI2_LINE_52                 EXTI2_IMR2_IM52   /*!< Extended line 52 */
#define LL_EXTI2_LINE_53                 EXTI2_IMR2_IM53   /*!< Extended line 53 */
#define LL_EXTI2_LINE_54                 EXTI2_IMR2_IM54   /*!< Extended line 54 */
#define LL_EXTI2_LINE_55                 EXTI2_IMR2_IM55   /*!< Extended line 55 */
#define LL_EXTI2_LINE_56                 EXTI2_IMR2_IM56   /*!< Extended line 56 */
#define LL_EXTI2_LINE_59                 EXTI2_IMR2_IM59   /*!< Extended line 59 */
#define LL_EXTI2_LINE_60                 EXTI2_IMR2_IM60   /*!< Extended line 60 */
#define LL_EXTI2_LINE_61                 EXTI2_IMR2_IM61   /*!< Extended line 61 */
#define LL_EXTI2_LINE_62                 EXTI2_IMR2_IM62   /*!< Extended line 62 */
#define LL_EXTI2_LINE_63                 EXTI2_IMR2_IM63   /*!< Extended line 63 */

#define LL_EXTI2_LINE_ALL_32_63 \
  ( LL_EXTI2_LINE_33 | LL_EXTI2_LINE_34 | \
    LL_EXTI2_LINE_35 | LL_EXTI2_LINE_36 | LL_EXTI2_LINE_37 | \
    LL_EXTI2_LINE_38 | LL_EXTI2_LINE_40 | LL_EXTI2_LINE_41 | \
    LL_EXTI2_LINE_42 | LL_EXTI2_LINE_43 | LL_EXTI2_LINE_44 | \
    LL_EXTI2_LINE_46 | LL_EXTI2_LINE_47 | LL_EXTI2_LINE_48 | \
    LL_EXTI2_LINE_49 | LL_EXTI2_LINE_50 | LL_EXTI2_LINE_51 | \
    LL_EXTI2_LINE_52 | LL_EXTI2_LINE_53 | LL_EXTI2_LINE_54 | \
    LL_EXTI2_LINE_55 | LL_EXTI2_LINE_56 | LL_EXTI2_LINE_59 | \
    LL_EXTI2_LINE_60 | LL_EXTI2_LINE_61 | LL_EXTI2_LINE_62 | LL_EXTI2_LINE_63)
/*!< All Extended line not reserved*/

#define LL_EXTI2_DIRECT_LINE_ALL_32_63 \
  ( LL_EXTI2_LINE_46 | LL_EXTI2_LINE_47 | LL_EXTI2_LINE_48 | \
    LL_EXTI2_LINE_49 | LL_EXTI2_LINE_50 | LL_EXTI2_LINE_51 | \
    LL_EXTI2_LINE_52 | LL_EXTI2_LINE_53 | LL_EXTI2_LINE_54 | \
    LL_EXTI2_LINE_55 | LL_EXTI2_LINE_56 | LL_EXTI2_LINE_62 | \
    LL_EXTI2_LINE_63)
/*!< All Extended line not reserved*/

#define LL_EXTI2_CONFIG_LINE_ALL_32_63 \
  ( LL_EXTI2_LINE_33 | LL_EXTI2_LINE_34 | \
    LL_EXTI2_LINE_35 | LL_EXTI2_LINE_36 | LL_EXTI2_LINE_37 | \
    LL_EXTI2_LINE_38 | LL_EXTI2_LINE_40 | LL_EXTI2_LINE_41 | \
    LL_EXTI2_LINE_42 | LL_EXTI2_LINE_43 | LL_EXTI2_LINE_44 | \
    LL_EXTI2_LINE_46 | LL_EXTI2_LINE_47 | LL_EXTI2_LINE_48 | \
    LL_EXTI2_LINE_49 | LL_EXTI2_LINE_50 | LL_EXTI2_LINE_51 | \
    LL_EXTI2_LINE_52 | LL_EXTI2_LINE_53 | LL_EXTI2_LINE_54 | \
    LL_EXTI2_LINE_55 | LL_EXTI2_LINE_56 | LL_EXTI2_LINE_59 | \
    LL_EXTI2_LINE_60 | LL_EXTI2_LINE_61 | LL_EXTI2_LINE_62 | \
    LL_EXTI2_LINE_63)
/*!< All Extended line not reserved*/

#define LL_EXTI2_LINE_64                 EXTI2_IMR3_IM64   /*!< Extended line 64 */
#define LL_EXTI2_LINE_65                 EXTI2_IMR3_IM65   /*!< Extended line 65 */
#define LL_EXTI2_LINE_66                 EXTI2_IMR3_IM66   /*!< Extended line 66 */
#define LL_EXTI2_LINE_67                 EXTI2_IMR3_IM67   /*!< Extended line 67 */
#define LL_EXTI2_LINE_68                 EXTI2_IMR3_IM68   /*!< Extended line 68 */
#define LL_EXTI2_LINE_69                 EXTI2_IMR3_IM69   /*!< Extended line 69 */
#define LL_EXTI2_LINE_70                 EXTI2_IMR3_IM70   /*!< Extended line 70 */
#define LL_EXTI2_LINE_76                 EXTI2_IMR3_IM76   /*!< Extended line 76 */

#define LL_EXTI2_LINE_ALL_64_95 \
  ( LL_EXTI2_LINE_64 | LL_EXTI2_LINE_65 | LL_EXTI2_LINE_66 | \
    LL_EXTI2_LINE_67 | LL_EXTI2_LINE_68 | LL_EXTI2_LINE_69 | \
    LL_EXTI2_LINE_70 | LL_EXTI2_LINE_76)
/*!< All Extended line not reserved*/

#define LL_EXTI2_DIRECT_LINE_ALL_64_95 \
  ( LL_EXTI2_LINE_67 | LL_EXTI2_LINE_68 | LL_EXTI2_LINE_69 | \
    LL_EXTI2_LINE_70 | LL_EXTI2_LINE_76)
/*!< All Extended line not reserved*/

#define LL_EXTI2_CONFIG_LINE_ALL_64_95 \
  ( LL_EXTI2_LINE_64 | LL_EXTI2_LINE_65 | LL_EXTI2_LINE_66 )
/*!< All Extended line not reserved*/

/**
  * @}
  */

/** @defgroup LL_EXTI2_EVT_x EXTI2 Event x
  * @{
  */
#define LL_EXTI2_EVT_0                  EXTI2_EMR1_EM0   /*!< Extended EVT 0 */
#define LL_EXTI2_EVT_1                  EXTI2_EMR1_EM1   /*!< Extended EVT 1 */
#define LL_EXTI2_EVT_2                  EXTI2_EMR1_EM2   /*!< Extended EVT 2 */
#define LL_EXTI2_EVT_3                  EXTI2_EMR1_EM3   /*!< Extended EVT 3 */
#define LL_EXTI2_EVT_4                  EXTI2_EMR1_EM4   /*!< Extended EVT 4 */
#define LL_EXTI2_EVT_5                  EXTI2_EMR1_EM5   /*!< Extended EVT 5 */
#define LL_EXTI2_EVT_6                  EXTI2_EMR1_EM6   /*!< Extended EVT 6 */
#define LL_EXTI2_EVT_7                  EXTI2_EMR1_EM7   /*!< Extended EVT 7 */
#define LL_EXTI2_EVT_8                  EXTI2_EMR1_EM8   /*!< Extended EVT 8 */
#define LL_EXTI2_EVT_9                  EXTI2_EMR1_EM9   /*!< Extended EVT 9 */
#define LL_EXTI2_EVT_10                 EXTI2_EMR1_EM10   /*!< Extended EVT 10 */
#define LL_EXTI2_EVT_11                 EXTI2_EMR1_EM11   /*!< Extended EVT 11 */
#define LL_EXTI2_EVT_12                 EXTI2_EMR1_EM12   /*!< Extended EVT 12 */
#define LL_EXTI2_EVT_13                 EXTI2_EMR1_EM13   /*!< Extended EVT 13 */
#define LL_EXTI2_EVT_14                 EXTI2_EMR1_EM14   /*!< Extended EVT 14 */
#define LL_EXTI2_EVT_15                 EXTI2_EMR1_EM15   /*!< Extended EVT 15 */

#define LL_EXTI2_EVT_ALL_0_31 \
  ( LL_EXTI2_EVT_0 | LL_EXTI2_EVT_1 | LL_EXTI2_EVT_2 | LL_EXTI2_EVT_3 | \
    LL_EXTI2_EVT_4 | LL_EXTI2_EVT_5 | LL_EXTI2_EVT_6 | \
    LL_EXTI2_EVT_7 | LL_EXTI2_EVT_8 | LL_EXTI2_EVT_9 | \
    LL_EXTI2_EVT_10 | LL_EXTI2_EVT_11 | LL_EXTI2_EVT_12 | \
    LL_EXTI2_EVT_13 | LL_EXTI2_EVT_14 | LL_EXTI2_EVT_15)
/*!< All Extended EVT not reserved*/

#define LL_EXTI2_EVT_59                 EXTI2_EMR2_EM59   /*!< Extended EVT 59 */
#define LL_EXTI2_EVT_60                 EXTI2_EMR2_EM60   /*!< Extended EVT 60 */
#define LL_EXTI2_EVT_61                 EXTI2_EMR2_EM61   /*!< Extended EVT 61 */

#define LL_EXTI2_EVT_ALL_32_63 \
  ( LL_EXTI2_EVT_59 | LL_EXTI2_EVT_60 | LL_EXTI2_EVT_61)
/*!< All Extended EVT not reserved*/

/**
  * @}
  */

/* no CxEMR3 */

/** @defgroup LL_EXTI2_EnCIDCFGR_x EXTI2 EnCIDCFGR x
  * @{
  */
#define LL_EXTI2_EnCIDCFGR_0                  (0U)    /*!< E0CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_1                  (1U)    /*!< E1CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_2                  (2U)    /*!< E2CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_3                  (3U)    /*!< E3CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_4                  (4U)    /*!< E4CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_5                  (5U)    /*!< E5CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_6                  (6U)    /*!< E6CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_7                  (7U)    /*!< E7CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_8                  (8U)    /*!< E8CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_9                  (9U)    /*!< E9CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_10                 (10U)   /*!< E10CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_11                 (11U)   /*!< E11CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_12                 (12U)   /*!< E12CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_13                 (13U)   /*!< E13CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_14                 (14U)   /*!< E14CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_15                 (15U)   /*!< E15CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_16                 (16U)   /*!< E16CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_17                 (17U)   /*!< E17CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_18                 (18U)   /*!< E18CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_19                 (19U)   /*!< E19CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_20                 (20U)   /*!< E20CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_21                 (21U)   /*!< E21CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_22                 (22U)   /*!< E22CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_23                 (23U)   /*!< E23CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_24                 (24U)   /*!< E24CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_25                 (25U)   /*!< E25CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_26                 (26U)   /*!< E26CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_27                 (27U)   /*!< E27CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_29                 (29U)   /*!< E29CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_30                 (30U)   /*!< E30CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_31                 (31U)   /*!< E31CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_33                 (33U)   /*!< E33CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_34                 (34U)   /*!< E34CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_35                 (35U)   /*!< E35CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_36                 (36U)   /*!< E36CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_37                 (37U)   /*!< E37CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_38                 (38U)   /*!< E38CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_40                 (40U)   /*!< E40CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_41                 (41U)   /*!< E41CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_42                 (42U)   /*!< E42CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_43                 (43U)   /*!< E43CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_44                 (44U)   /*!< E44CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_46                 (46U)   /*!< E46CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_47                 (47U)   /*!< E47CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_48                 (48U)   /*!< E48CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_49                 (49U)   /*!< E49CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_50                 (50U)   /*!< E50CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_51                 (51U)   /*!< E51CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_52                 (52U)   /*!< E52CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_53                 (53U)   /*!< E53CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_54                 (54U)   /*!< E54CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_55                 (55U)   /*!< E55CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_56                 (56U)   /*!< E56CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_59                 (59U)   /*!< E59CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_60                 (60U)   /*!< E60CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_61                 (61U)   /*!< E61CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_62                 (62U)   /*!< E62CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_63                 (63U)   /*!< E63CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_64                 (64U)   /*!< E64CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_65                 (65U)   /*!< E65CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_66                 (66U)   /*!< E66CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_67                 (67U)   /*!< E67CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_68                 (68U)   /*!< E68CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_69                 (69U)   /*!< E69CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_70                 (70U)   /*!< E70CIDCFGR */
#define LL_EXTI2_EnCIDCFGR_76                 (76U)   /*!< E76CIDCFGR */

/**
  * @}
  */

/** @defgroup LL_EXTI2_SEC_x EXTI2 Secure x
  * @{
  */
#define LL_EXTI2_SEC_0              EXTI2_SECCFGR1_SEC0   /*!< Secure Line 0 */
#define LL_EXTI2_SEC_1              EXTI2_SECCFGR1_SEC1   /*!< Secure Line 1 */
#define LL_EXTI2_SEC_2              EXTI2_SECCFGR1_SEC2   /*!< Secure Line 2 */
#define LL_EXTI2_SEC_3              EXTI2_SECCFGR1_SEC3   /*!< Secure Line 3 */
#define LL_EXTI2_SEC_4              EXTI2_SECCFGR1_SEC4   /*!< Secure Line 4 */
#define LL_EXTI2_SEC_5              EXTI2_SECCFGR1_SEC5   /*!< Secure Line 5 */
#define LL_EXTI2_SEC_6              EXTI2_SECCFGR1_SEC6   /*!< Secure Line 6 */
#define LL_EXTI2_SEC_7              EXTI2_SECCFGR1_SEC7   /*!< Secure Line 7 */
#define LL_EXTI2_SEC_8              EXTI2_SECCFGR1_SEC8   /*!< Secure Line 8 */
#define LL_EXTI2_SEC_9              EXTI2_SECCFGR1_SEC9   /*!< Secure Line 9 */
#define LL_EXTI2_SEC_10             EXTI2_SECCFGR1_SEC10  /*!< Secure Line 10 */
#define LL_EXTI2_SEC_11             EXTI2_SECCFGR1_SEC11  /*!< Secure Line 11 */
#define LL_EXTI2_SEC_12             EXTI2_SECCFGR1_SEC12  /*!< Secure Line 12 */
#define LL_EXTI2_SEC_13             EXTI2_SECCFGR1_SEC13  /*!< Secure Line 13 */
#define LL_EXTI2_SEC_14             EXTI2_SECCFGR1_SEC14  /*!< Secure Line 14 */
#define LL_EXTI2_SEC_15             EXTI2_SECCFGR1_SEC15  /*!< Secure Line 15 */
#define LL_EXTI2_SEC_16             EXTI2_SECCFGR1_SEC16  /*!< Secure Line 16 */
#define LL_EXTI2_SEC_17             EXTI2_SECCFGR1_SEC17  /*!< Secure Line 17 */
#define LL_EXTI2_SEC_18             EXTI2_SECCFGR1_SEC18  /*!< Secure Line 18 */
#define LL_EXTI2_SEC_19             EXTI2_SECCFGR1_SEC19  /*!< Secure Line 19 */
#define LL_EXTI2_SEC_20             EXTI2_SECCFGR1_SEC20  /*!< Secure Line 20 */
#define LL_EXTI2_SEC_21             EXTI2_SECCFGR1_SEC21  /*!< Secure Line 21 */
#define LL_EXTI2_SEC_22             EXTI2_SECCFGR1_SEC22  /*!< Secure Line 22 */
#define LL_EXTI2_SEC_23             EXTI2_SECCFGR1_SEC23  /*!< Secure Line 23 */
#define LL_EXTI2_SEC_24             EXTI2_SECCFGR1_SEC24  /*!< Secure Line 24 */
#define LL_EXTI2_SEC_25             EXTI2_SECCFGR1_SEC25  /*!< Secure Line 25 */
#define LL_EXTI2_SEC_26             EXTI2_SECCFGR1_SEC26  /*!< Secure Line 26 */
#define LL_EXTI2_SEC_27             EXTI2_SECCFGR1_SEC27  /*!< Secure Line 27 */
/*#define LL_EXTI2_SEC_28             EXTI2_SECCFGR1_SEC28  !< Secure Line 28 */
#define LL_EXTI2_SEC_29             EXTI2_SECCFGR1_SEC29  /*!< Secure Line 29 */
#define LL_EXTI2_SEC_30             EXTI2_SECCFGR1_SEC30  /*!< Secure Line 30 */
#define LL_EXTI2_SEC_31             EXTI2_SECCFGR1_SEC31  /*!< Secure Line 31 */

#define LL_EXTI2_SEC_ALL_0_31 \
  ( LL_EXTI2_SEC_0 | LL_EXTI2_SEC_1 | LL_EXTI2_SEC_2 | LL_EXTI2_SEC_3 | \
    LL_EXTI2_SEC_4 | LL_EXTI2_SEC_5 | LL_EXTI2_SEC_6 | \
    LL_EXTI2_SEC_7 | LL_EXTI2_SEC_8 | LL_EXTI2_SEC_9 | \
    LL_EXTI2_SEC_10 | LL_EXTI2_SEC_11 | LL_EXTI2_SEC_12 | \
    LL_EXTI2_SEC_13 | LL_EXTI2_SEC_14 | LL_EXTI2_SEC_15 | \
    LL_EXTI2_SEC_16 | LL_EXTI2_SEC_17 | LL_EXTI2_SEC_18 | \
    LL_EXTI2_SEC_19 | LL_EXTI2_SEC_20 | LL_EXTI2_SEC_21 | \
    LL_EXTI2_SEC_22 | LL_EXTI2_SEC_23 | LL_EXTI2_SEC_24 | \
    LL_EXTI2_SEC_25 | LL_EXTI2_SEC_26 | LL_EXTI2_SEC_27 | \
    LL_EXTI2_SEC_29 | LL_EXTI2_SEC_30 | LL_EXTI2_SEC_31)
/*!< All Extended line not reserved*/

/* #define LL_EXTI2_SEC_32             EXTI2_SECCFGR2_SEC32   !< Secure Line 32 */
#define LL_EXTI2_SEC_33             EXTI2_SECCFGR2_SEC33   /*!< Secure Line 33 */
#define LL_EXTI2_SEC_34             EXTI2_SECCFGR2_SEC34   /*!< Secure Line 34 */
#define LL_EXTI2_SEC_35             EXTI2_SECCFGR2_SEC35   /*!< Secure Line 34 */
#define LL_EXTI2_SEC_36             EXTI2_SECCFGR2_SEC36   /*!< Secure Line 36 */
#define LL_EXTI2_SEC_37             EXTI2_SECCFGR2_SEC37   /*!< Secure Line 37 */
#define LL_EXTI2_SEC_38             EXTI2_SECCFGR2_SEC38   /*!< Secure Line 38 */
/* #define LL_EXTI2_SEC_39             EXTI2_SECCFGR2_SEC39   !< Secure Line 39 */
#define LL_EXTI2_SEC_40             EXTI2_SECCFGR2_SEC40   /*!< Secure Line 40 */
#define LL_EXTI2_SEC_41             EXTI2_SECCFGR2_SEC41   /*!< Secure Line 41 */
#define LL_EXTI2_SEC_42             EXTI2_SECCFGR2_SEC42   /*!< Secure Line 42 */
#define LL_EXTI2_SEC_43             EXTI2_SECCFGR2_SEC43   /*!< Secure Line 43 */
#define LL_EXTI2_SEC_44             EXTI2_SECCFGR2_SEC44   /*!< Secure Line 44 */
/*#define LL_EXTI2_SEC_45             EXTI2_SECCFGR2_SEC45  !< Secure Line 45 */
#define LL_EXTI2_SEC_46             EXTI2_SECCFGR2_SEC46   /*!< Secure Line 46 */
#define LL_EXTI2_SEC_47             EXTI2_SECCFGR2_SEC47   /*!< Secure Line 47 */
#define LL_EXTI2_SEC_48             EXTI2_SECCFGR2_SEC48   /*!< Secure Line 48 */
#define LL_EXTI2_SEC_49             EXTI2_SECCFGR2_SEC49   /*!< Secure Line 49 */
#define LL_EXTI2_SEC_50             EXTI2_SECCFGR2_SEC50   /*!< Secure Line 50 */
#define LL_EXTI2_SEC_51             EXTI2_SECCFGR2_SEC51   /*!< Secure Line 51 */
#define LL_EXTI2_SEC_52             EXTI2_SECCFGR2_SEC52   /*!< Secure Line 52 */
#define LL_EXTI2_SEC_53             EXTI2_SECCFGR2_SEC53   /*!< Secure Line 53 */
#define LL_EXTI2_SEC_54             EXTI2_SECCFGR2_SEC54   /*!< Secure Line 54 */
#define LL_EXTI2_SEC_55             EXTI2_SECCFGR2_SEC55   /*!< Secure Line 55 */
#define LL_EXTI2_SEC_56             EXTI2_SECCFGR2_SEC56   /*!< Secure Line 56 */
/*#define LL_EXTI2_SEC_57             EXTI2_SECCFGR2_SEC57   !< Secure Line 57 */
/*#define LL_EXTI2_SEC_58             EXTI2_SECCFGR2_SEC58   !< Secure Line 58 */
#define LL_EXTI2_SEC_59             EXTI2_SECCFGR2_SEC59   /*!< Secure Line 59 */
#define LL_EXTI2_SEC_60             EXTI2_SECCFGR2_SEC60   /*!< Secure Line 60 */
#define LL_EXTI2_SEC_61             EXTI2_SECCFGR2_SEC61   /*!< Secure Line 61 */
#define LL_EXTI2_SEC_62             EXTI2_SECCFGR2_SEC62   /*!< Secure Line 62 */
#define LL_EXTI2_SEC_63             EXTI2_SECCFGR2_SEC63   /*!< Secure Line 63 */

#define LL_EXTI2_SEC_ALL_32_63 \
  ( LL_EXTI2_SEC_33 | LL_EXTI2_SEC_34 | \
    LL_EXTI2_SEC_35 | LL_EXTI2_SEC_36 | LL_EXTI2_SEC_37 | \
    LL_EXTI2_SEC_38 | LL_EXTI2_SEC_40 | LL_EXTI2_SEC_41 | \
    LL_EXTI2_SEC_42 | LL_EXTI2_SEC_43 | LL_EXTI2_SEC_44 | \
    LL_EXTI2_SEC_46 | LL_EXTI2_SEC_47 | LL_EXTI2_SEC_48 | \
    LL_EXTI2_SEC_49 | LL_EXTI2_SEC_50 | LL_EXTI2_SEC_51 | \
    LL_EXTI2_SEC_52 | LL_EXTI2_SEC_53 | LL_EXTI2_SEC_54 | \
    LL_EXTI2_SEC_55 | LL_EXTI2_SEC_56 | LL_EXTI2_SEC_59 | \
    LL_EXTI2_SEC_60 | LL_EXTI2_SEC_61 | LL_EXTI2_SEC_62 | \
    LL_EXTI2_SEC_63)
/*!< All Extended line not reserved*/

#define LL_EXTI2_SEC_64             EXTI2_SECCFGR3_SEC64  /*!< Secure Line 64 */
#define LL_EXTI2_SEC_65             EXTI2_SECCFGR3_SEC65  /*!< Secure Line 65 */
#define LL_EXTI2_SEC_66             EXTI2_SECCFGR3_SEC66  /*!< Secure Line 66 */
#define LL_EXTI2_SEC_67             EXTI2_SECCFGR3_SEC67  /*!< Secure Line 67 */
#define LL_EXTI2_SEC_68             EXTI2_SECCFGR3_SEC68  /*!< Secure Line 68 */
#define LL_EXTI2_SEC_69             EXTI2_SECCFGR3_SEC69  /*!< Secure Line 69 */
#define LL_EXTI2_SEC_70             EXTI2_SECCFGR3_SEC70  /*!< Secure Line 70 */
/* #define LL_EXTI2_SEC_71             EXTI2_SECCFGR3_SEC71  !< Secure Line 71 */
/* #define LL_EXTI2_SEC_72             EXTI2_SECCFGR3_SEC72  !< Secure Line 72 */
/* #define LL_EXTI2_SEC_73             EXTI2_SECCFGR3_SEC73  !< Secure Line 73 */
/* #define LL_EXTI2_SEC_74             EXTI2_SECCFGR3_SEC74  !< Secure Line 74 */
/* #define LL_EXTI2_SEC_75             EXTI2_SECCFGR3_SEC75  !< Secure Line 75 */
#define LL_EXTI2_SEC_76             EXTI2_SECCFGR3_SEC76  /*!< Secure Line 76 */

#define LL_EXTI2_SEC_ALL_64_95 \
  ( LL_EXTI2_SEC_64 | LL_EXTI2_SEC_65 | LL_EXTI2_SEC_66 | \
    LL_EXTI2_SEC_67 | LL_EXTI2_SEC_68 | LL_EXTI2_SEC_69 | \
    LL_EXTI2_SEC_70 | LL_EXTI2_SEC_76)
/*!< All Extended line not reserved*/

/**
  * @}
  */

/** @defgroup LL_EXTI2_PRIV_x EXTI2 Privilege x
  * @{
  */
#define LL_EXTI2_PRIV_0              EXTI2_PRIVCFGR1_PRIV0   /*!< Secure Line 0 */
#define LL_EXTI2_PRIV_1              EXTI2_PRIVCFGR1_PRIV1   /*!< Secure Line 1 */
#define LL_EXTI2_PRIV_2              EXTI2_PRIVCFGR1_PRIV2   /*!< Secure Line 2 */
#define LL_EXTI2_PRIV_3              EXTI2_PRIVCFGR1_PRIV3   /*!< Secure Line 3 */
#define LL_EXTI2_PRIV_4              EXTI2_PRIVCFGR1_PRIV4   /*!< Secure Line 4 */
#define LL_EXTI2_PRIV_5              EXTI2_PRIVCFGR1_PRIV5   /*!< Secure Line 5 */
#define LL_EXTI2_PRIV_6              EXTI2_PRIVCFGR1_PRIV6   /*!< Secure Line 6 */
#define LL_EXTI2_PRIV_7              EXTI2_PRIVCFGR1_PRIV7   /*!< Secure Line 7 */
#define LL_EXTI2_PRIV_8              EXTI2_PRIVCFGR1_PRIV8   /*!< Secure Line 8 */
#define LL_EXTI2_PRIV_9              EXTI2_PRIVCFGR1_PRIV9   /*!< Secure Line 9 */
#define LL_EXTI2_PRIV_10             EXTI2_PRIVCFGR1_PRIV10  /*!< Secure Line 10 */
#define LL_EXTI2_PRIV_11             EXTI2_PRIVCFGR1_PRIV11  /*!< Secure Line 11 */
#define LL_EXTI2_PRIV_12             EXTI2_PRIVCFGR1_PRIV12  /*!< Secure Line 12 */
#define LL_EXTI2_PRIV_13             EXTI2_PRIVCFGR1_PRIV13  /*!< Secure Line 13 */
#define LL_EXTI2_PRIV_14             EXTI2_PRIVCFGR1_PRIV14  /*!< Secure Line 14 */
#define LL_EXTI2_PRIV_15             EXTI2_PRIVCFGR1_PRIV15  /*!< Secure Line 15 */
#define LL_EXTI2_PRIV_16             EXTI2_PRIVCFGR1_PRIV16  /*!< Secure Line 16 */
#define LL_EXTI2_PRIV_17             EXTI2_PRIVCFGR1_PRIV17  /*!< Secure Line 17 */
#define LL_EXTI2_PRIV_18             EXTI2_PRIVCFGR1_PRIV18  /*!< Secure Line 18 */
#define LL_EXTI2_PRIV_19             EXTI2_PRIVCFGR1_PRIV19  /*!< Secure Line 19 */
#define LL_EXTI2_PRIV_20             EXTI2_PRIVCFGR1_PRIV20  /*!< Secure Line 20 */
#define LL_EXTI2_PRIV_21             EXTI2_PRIVCFGR1_PRIV21  /*!< Secure Line 21 */
#define LL_EXTI2_PRIV_22             EXTI2_PRIVCFGR1_PRIV22  /*!< Secure Line 22 */
#define LL_EXTI2_PRIV_23             EXTI2_PRIVCFGR1_PRIV23  /*!< Secure Line 23 */
#define LL_EXTI2_PRIV_24             EXTI2_PRIVCFGR1_PRIV24  /*!< Secure Line 24 */
#define LL_EXTI2_PRIV_25             EXTI2_PRIVCFGR1_PRIV25  /*!< Secure Line 25 */
#define LL_EXTI2_PRIV_26             EXTI2_PRIVCFGR1_PRIV26  /*!< Secure Line 26 */
#define LL_EXTI2_PRIV_27             EXTI2_PRIVCFGR1_PRIV27  /*!< Secure Line 27 */
/* #define LL_EXTI2_PRIV_28             EXTI2_PRIVCFGR1_PRIV28  !< Secure Line 28 */
#define LL_EXTI2_PRIV_29             EXTI2_PRIVCFGR1_PRIV29  /*!< Secure Line 29 */
#define LL_EXTI2_PRIV_30             EXTI2_PRIVCFGR1_PRIV30  /*!< Secure Line 30 */
#define LL_EXTI2_PRIV_31             EXTI2_PRIVCFGR1_PRIV31  /*!< Secure Line 31 */

#define LL_EXTI2_PRIV_ALL_0_31 \
  ( LL_EXTI2_PRIV_0 | LL_EXTI2_PRIV_1 | LL_EXTI2_PRIV_2 | LL_EXTI2_PRIV_3 | \
    LL_EXTI2_PRIV_4 | LL_EXTI2_PRIV_5 | LL_EXTI2_PRIV_6 | \
    LL_EXTI2_PRIV_7 | LL_EXTI2_PRIV_8 | LL_EXTI2_PRIV_9 | \
    LL_EXTI2_PRIV_10 | LL_EXTI2_PRIV_11 | LL_EXTI2_PRIV_12 | \
    LL_EXTI2_PRIV_13 | LL_EXTI2_PRIV_14 | LL_EXTI2_PRIV_15 | \
    LL_EXTI2_PRIV_16 | LL_EXTI2_PRIV_17 | LL_EXTI2_PRIV_18 | \
    LL_EXTI2_PRIV_19 | LL_EXTI2_PRIV_20 | LL_EXTI2_PRIV_21 | \
    LL_EXTI2_PRIV_22 | LL_EXTI2_PRIV_23 | LL_EXTI2_PRIV_24 | \
    LL_EXTI2_PRIV_25 | LL_EXTI2_PRIV_26 | LL_EXTI2_PRIV_27 | \
    LL_EXTI2_PRIV_29 | LL_EXTI2_PRIV_30 | LL_EXTI2_PRIV_31)
/*!< All Extended line not reserved*/

/* #define LL_EXTI2_PRIV_32             EXTI2_PRIVCFGR2_PRIV32   !< Secure Line 0 */
#define LL_EXTI2_PRIV_33             EXTI2_PRIVCFGR2_PRIV33  /*!< Secure Line 1 */
#define LL_EXTI2_PRIV_34             EXTI2_PRIVCFGR2_PRIV34  /*!< Secure Line 2 */
#define LL_EXTI2_PRIV_35             EXTI2_PRIVCFGR2_PRIV35  /*!< Secure Line 3 */
#define LL_EXTI2_PRIV_36             EXTI2_PRIVCFGR2_PRIV36  /*!< Secure Line 4 */
#define LL_EXTI2_PRIV_37             EXTI2_PRIVCFGR2_PRIV37  /*!< Secure Line 5 */
#define LL_EXTI2_PRIV_38             EXTI2_PRIVCFGR2_PRIV38  /*!< Secure Line 6 */
/* #define LL_EXTI2_PRIV_39             EXTI2_PRIVCFGR2_PRIV39   !< Secure Line 7 */
#define LL_EXTI2_PRIV_40             EXTI2_PRIVCFGR2_PRIV40  /*!< Secure Line 8 */
#define LL_EXTI2_PRIV_41             EXTI2_PRIVCFGR2_PRIV41  /*!< Secure Line 9 */
#define LL_EXTI2_PRIV_42             EXTI2_PRIVCFGR2_PRIV42  /*!< Secure Line 10 */
#define LL_EXTI2_PRIV_43             EXTI2_PRIVCFGR2_PRIV43  /*!< Secure Line 11 */
#define LL_EXTI2_PRIV_44             EXTI2_PRIVCFGR2_PRIV44  /*!< Secure Line 12 */
/* #define LL_EXTI2_PRIV_45             EXTI2_PRIVCFGR2_PRIV45  !< Secure Line 13 */
#define LL_EXTI2_PRIV_46             EXTI2_PRIVCFGR2_PRIV46  /*!< Secure Line 14 */
#define LL_EXTI2_PRIV_47             EXTI2_PRIVCFGR2_PRIV47 /*!< Secure Line 15 */
#define LL_EXTI2_PRIV_48             EXTI2_PRIVCFGR2_PRIV48 /*!< Secure Line 16 */
#define LL_EXTI2_PRIV_49             EXTI2_PRIVCFGR2_PRIV49 /*!< Secure Line 17 */
#define LL_EXTI2_PRIV_50             EXTI2_PRIVCFGR2_PRIV50 /*!< Secure Line 18 */
#define LL_EXTI2_PRIV_51             EXTI2_PRIVCFGR2_PRIV51 /*!< Secure Line 19 */
#define LL_EXTI2_PRIV_52             EXTI2_PRIVCFGR2_PRIV52  /*!< Secure Line 20 */
#define LL_EXTI2_PRIV_53             EXTI2_PRIVCFGR2_PRIV53 /*!< Secure Line 21 */
#define LL_EXTI2_PRIV_54             EXTI2_PRIVCFGR2_PRIV54  /*!< Secure Line 22 */
#define LL_EXTI2_PRIV_55             EXTI2_PRIVCFGR2_PRIV55  /*!< Secure Line 23 */
#define LL_EXTI2_PRIV_56             EXTI2_PRIVCFGR2_PRIV56  /*!< Secure Line 24 */
/* #define LL_EXTI2_PRIV_57             EXTI2_PRIVCFGR2_PRIV57  !< Secure Line 25 */
/* #define LL_EXTI2_PRIV_58             EXTI2_PRIVCFGR2_PRIV58  !< Secure Line 26 */
#define LL_EXTI2_PRIV_59             EXTI2_PRIVCFGR2_PRIV59  /*!< Secure Line 27 */
#define LL_EXTI2_PRIV_60             EXTI2_PRIVCFGR2_PRIV60  /*!< Secure Line 28 */
#define LL_EXTI2_PRIV_61             EXTI2_PRIVCFGR2_PRIV61  /*!< Secure Line 29 */
#define LL_EXTI2_PRIV_62             EXTI2_PRIVCFGR2_PRIV62  /*!< Secure Line 30 */
#define LL_EXTI2_PRIV_63             EXTI2_PRIVCFGR2_PRIV63  /*!< Secure Line 31 */

#define LL_EXTI2_PRIV_ALL_32_63 \
  ( LL_EXTI2_PRIV_33 | LL_EXTI2_PRIV_34 | \
    LL_EXTI2_PRIV_35 | LL_EXTI2_PRIV_36 | LL_EXTI2_PRIV_37 | \
    LL_EXTI2_PRIV_38 | LL_EXTI2_PRIV_40 | LL_EXTI2_PRIV_41 | \
    LL_EXTI2_PRIV_42 | LL_EXTI2_PRIV_43 | LL_EXTI2_PRIV_44 | \
    LL_EXTI2_PRIV_46 | LL_EXTI2_PRIV_47 | LL_EXTI2_PRIV_48 | \
    LL_EXTI2_PRIV_49 | LL_EXTI2_PRIV_50 | LL_EXTI2_PRIV_51 | \
    LL_EXTI2_PRIV_52 | LL_EXTI2_PRIV_53 | LL_EXTI2_PRIV_54 | \
    LL_EXTI2_PRIV_55 | LL_EXTI2_PRIV_56 | LL_EXTI2_PRIV_59 | \
    LL_EXTI2_PRIV_60 | LL_EXTI2_PRIV_61 | LL_EXTI2_PRIV_62 | \
    LL_EXTI2_PRIV_63)
/*!< All Extended line not reserved*/

#define LL_EXTI2_PRIV_64             EXTI2_PRIVCFGR3_PRIV64  /*!< Secure Line 0 */
#define LL_EXTI2_PRIV_65             EXTI2_PRIVCFGR3_PRIV65  /*!< Secure Line 1 */
#define LL_EXTI2_PRIV_66             EXTI2_PRIVCFGR3_PRIV66  /*!< Secure Line 2 */
#define LL_EXTI2_PRIV_67             EXTI2_PRIVCFGR3_PRIV67  /*!< Secure Line 3 */
#define LL_EXTI2_PRIV_68             EXTI2_PRIVCFGR3_PRIV68  /*!< Secure Line 4 */
#define LL_EXTI2_PRIV_69             EXTI2_PRIVCFGR3_PRIV69  /*!< Secure Line 5 */
#define LL_EXTI2_PRIV_70             EXTI2_PRIVCFGR3_PRIV70  /*!< Secure Line 6 */
/* #define LL_EXTI2_PRIV_71             EXTI2_PRIVCFGR3_PRIV71  !< Secure Line 7 */
/* #define LL_EXTI2_PRIV_72             EXTI2_PRIVCFGR3_PRIV72  !< Secure Line 8 */
/* #define LL_EXTI2_PRIV_73             EXTI2_PRIVCFGR3_PRIV73  !< Secure Line 9 */
/* #define LL_EXTI2_PRIV_74             EXTI2_PRIVCFGR3_PRIV74  !< Secure Line 10 */
/*#define LL_EXTI2_PRIV_75             EXTI2_PRIVCFGR3_PRIV75   !< Secure Line 11 */
#define LL_EXTI2_PRIV_76             EXTI2_PRIVCFGR3_PRIV76  /*!< Secure Line 12 */

#define LL_EXTI2_PRIV_ALL_64_95 \
  ( LL_EXTI2_PRIV_64 | LL_EXTI2_PRIV_65 | LL_EXTI2_PRIV_66 | \
    LL_EXTI2_PRIV_67 | LL_EXTI2_PRIV_68 | LL_EXTI2_PRIV_69 | \
    LL_EXTI2_PRIV_70 | LL_EXTI2_PRIV_76)
/*!< All Extended line not reserved*/

#define IS_EXTI_CID_VALID(__VALUE__) ((__VALUE__) < 4U)


#if defined(USE_FULL_LL_DRIVER)
#define LL_EXTI_LINE_NONE              (0x00000000U)  /*!< None Extended line */
#endif /*USE_FULL_LL_DRIVER*/

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup EXTI_LL_EC_MODE Mode
  * @{
  */
#define LL_EXTI_MODE_IT                 ((uint8_t)0x00U) /*!< Interrupt Mode */
#define LL_EXTI_MODE_EVENT              ((uint8_t)0x01U) /*!< Event Mode */
#define LL_EXTI_MODE_IT_EVENT           ((uint8_t)0x02U) /*!< Interrupt & Event Mode */
/**
  * @}
  */

/** @defgroup EXTI_LL_EC_TRIGGER Edge Trigger
  * @{
  */
#define LL_EXTI_TRIGGER_NONE            ((uint8_t)0x00U) /*!< No Trigger Mode */
#define LL_EXTI_TRIGGER_RISING          ((uint8_t)0x01U) /*!< Trigger Rising Mode */
#define LL_EXTI_TRIGGER_FALLING         ((uint8_t)0x02U) /*!< Trigger Falling Mode */
#define LL_EXTI_TRIGGER_RISING_FALLING  ((uint8_t)0x03U) /*!< Trigger Rising & Falling Mode */
/**
  * @}
  */


/** @defgroup EXTI_LL_EC_PORT EXTICR Port
  * @{
  */
#define LL_EXTI_EXTICR_PORTA            EXTI_EXTICR1_EXTI0_PA
#define LL_EXTI_EXTICR_PORTB            EXTI_EXTICR1_EXTI0_PB
#define LL_EXTI_EXTICR_PORTC            EXTI_EXTICR1_EXTI0_PC
#define LL_EXTI_EXTICR_PORTD            EXTI_EXTICR1_EXTI0_PD
#define LL_EXTI_EXTICR_PORTE            EXTI_EXTICR1_EXTI0_PE
#define LL_EXTI_EXTICR_PORTF            EXTI_EXTICR1_EXTI0_PF
#define LL_EXTI_EXTICR_PORTG            EXTI_EXTICR1_EXTI0_PG
#define LL_EXTI_EXTICR_PORTH            EXTI_EXTICR1_EXTI0_PH
#define LL_EXTI_EXTICR_PORTI            EXTI_EXTICR1_EXTI0_PI
#define LL_EXTI_EXTICR_PORTJ            EXTI_EXTICR1_EXTI0_PJ
#define LL_EXTI_EXTICR_PORTK            EXTI_EXTICR1_EXTI0_PK
#define LL_EXTI_EXTICR_PORTZ            EXTI_EXTICR1_EXTI0_PZ
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_EXTI_LINE EXTI EXTI LINE
  * @{
  */
#define LL_EXTI_EXTI_LINE0               (0U  << LL_EXTI_REGISTER_PINPOS_SHFT | 0U)  /*!< EXTI_POSITION_0  | EXTICR[0] */
#define LL_EXTI_EXTI_LINE1               (8U  << LL_EXTI_REGISTER_PINPOS_SHFT | 0U)  /*!< EXTI_POSITION_8  | EXTICR[0] */
#define LL_EXTI_EXTI_LINE2               (16U << LL_EXTI_REGISTER_PINPOS_SHFT | 0U)  /*!< EXTI_POSITION_16 | EXTICR[0] */
#define LL_EXTI_EXTI_LINE3               (24U << LL_EXTI_REGISTER_PINPOS_SHFT | 0U)  /*!< EXTI_POSITION_24 | EXTICR[0] */
#define LL_EXTI_EXTI_LINE4               (0U  << LL_EXTI_REGISTER_PINPOS_SHFT | 1U)  /*!< EXTI_POSITION_0  | EXTICR[1] */
#define LL_EXTI_EXTI_LINE5               (8U  << LL_EXTI_REGISTER_PINPOS_SHFT | 1U)  /*!< EXTI_POSITION_8  | EXTICR[1] */
#define LL_EXTI_EXTI_LINE6               (16U << LL_EXTI_REGISTER_PINPOS_SHFT | 1U)  /*!< EXTI_POSITION_16 | EXTICR[1] */
#define LL_EXTI_EXTI_LINE7               (24U << LL_EXTI_REGISTER_PINPOS_SHFT | 1U)  /*!< EXTI_POSITION_24 | EXTICR[1] */
#define LL_EXTI_EXTI_LINE8               (0U  << LL_EXTI_REGISTER_PINPOS_SHFT | 2U)  /*!< EXTI_POSITION_0  | EXTICR[2] */
#define LL_EXTI_EXTI_LINE9               (8U  << LL_EXTI_REGISTER_PINPOS_SHFT | 2U)  /*!< EXTI_POSITION_8  | EXTICR[2] */
#define LL_EXTI_EXTI_LINE10              (16U << LL_EXTI_REGISTER_PINPOS_SHFT | 2U)  /*!< EXTI_POSITION_16 | EXTICR[2] */
#define LL_EXTI_EXTI_LINE11              (24U << LL_EXTI_REGISTER_PINPOS_SHFT | 2U)  /*!< EXTI_POSITION_24 | EXTICR[2] */
#define LL_EXTI_EXTI_LINE12              (0U  << LL_EXTI_REGISTER_PINPOS_SHFT | 3U)  /*!< EXTI_POSITION_0  | EXTICR[3] */
#define LL_EXTI_EXTI_LINE13              (8U  << LL_EXTI_REGISTER_PINPOS_SHFT | 3U)  /*!< EXTI_POSITION_8  | EXTICR[3] */
#define LL_EXTI_EXTI_LINE14              (16U << LL_EXTI_REGISTER_PINPOS_SHFT | 3U)  /*!< EXTI_POSITION_16 | EXTICR[3] */
#define LL_EXTI_EXTI_LINE15              (24U << LL_EXTI_REGISTER_PINPOS_SHFT | 3U)  /*!< EXTI_POSITION_24 | EXTICR[3] */
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Macros EXTI Exported Macros
  * @{
  */

/** @defgroup EXTI_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in a specified EXTI register
  * @param  __INSTANCE__ The EXTI instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_EXTI_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, __VALUE__)

/**
  * @brief  Read a value in EXTI register
  * @param  __INSTANCE__ The EXTI instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_EXTI_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

#define IS_EXTI2_INSTANCE(INSTANCE)  ( ((INSTANCE) == EXTI2) )
#if defined (CORE_CM0PLUS)
#define IS_EXTI1_INSTANCE(INSTANCE)  ( 1U < 0 )
#else   /* CORE_CM0PLUS */
#define IS_EXTI1_INSTANCE(INSTANCE)  ( ((INSTANCE) == EXTI1) )
#endif  /* CORE_CM0PLUS */


/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup EXTI_LL_Exported_Functions EXTI Exported Functions
  * @{
  */
/** @defgroup EXTI_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 0 to 31
  * @rmtoll IMR1         IMx           LL_EXTI_EnableIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C1_EXTI_EnableIT_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C1IMR1, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 0 to 31 for cpu2
  * @rmtoll C2IMR1         IMx           LL_C2_EXTI_EnableIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_EnableIT_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C2IMR1, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 0 to 31 for cpu3
  * @rmtoll C3IMR1         IMx           LL_C3_EXTI_EnableIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_EnableIT_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C3IMR1, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 32 to 63
  * @rmtoll C1IMR2         IMx           LL_EXTI_EnableIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C1_EXTI_EnableIT_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C1IMR2, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2IMR2         IMx           LL_C2_EXTI_EnableIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_EnableIT_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C2IMR2, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu3
  * @rmtoll C3IMR2         IMx           LL_C3_EXTI_EnableIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_EnableIT_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C3IMR2, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 32 to 63
  * @rmtoll C1IMR3         IMx           LL_EXTI_EnableIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C1_EXTI_EnableIT_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C1IMR3, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2IMR3         IMx           LL_C2_EXTI_EnableIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_EnableIT_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C2IMR3, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu3
  * @rmtoll C3IMR3         IMx           LL_C3_EXTI_EnableIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_EnableIT_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C3IMR3, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 0 to 31
  * @rmtoll IMR1         IMx           LL_EXTI_DisableIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C1_EXTI_DisableIT_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C1IMR1, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 0 to 31 for cpu2
  * @rmtoll C2IMR1         IMx           LL_C2_EXTI_DisableIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_DisableIT_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C2IMR1, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 0 to 31 for cpu3
  * @rmtoll C3IMR1         IMx           LL_C3_EXTI_DisableIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_DisableIT_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C3IMR1, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 32 to 63
  * @rmtoll IMR2         IMx           LL_EXTI_DisableIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C1_EXTI_DisableIT_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C1IMR2, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2IMR2         IMx           LL_C2_EXTI_DisableIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_DisableIT_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C2IMR2, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu3
  * @rmtoll C3IMR2         IMx           LL_C3_EXTI_DisableIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_DisableIT_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C3IMR2, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 32 to 63
  * @rmtoll C1IMR3         IMx           LL_EXTI_DisableIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C1_EXTI_DisableIT_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C1IMR3, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2IMR3         IMx           LL_C2_EXTI_DisableIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_DisableIT_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C2IMR3, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 32 to 63 for cpu3
  * @rmtoll C3IMR3         IMx           LL_C3_EXTI_DisableIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_DisableIT_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C3IMR3, ExtiLine);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 0 to 31
  * @rmtoll IMR1         IMx           LL_EXTI_IsEnabledIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_EXTI_IsEnabledIT_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C1IMR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 0 to 31 for cpu2
  * @rmtoll C2IMR1         IMx           LL_C2_EXTI_IsEnabledIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_EXTI_IsEnabledIT_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C2IMR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 0 to 31 for cpu3
  * @rmtoll C3IMR1         IMx           LL_C3_EXTI_IsEnabledIT_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C3_EXTI_IsEnabledIT_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C3IMR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 32 to 63
  * @rmtoll IMR2         IMx           LL_EXTI_IsEnabledIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_EXTI_IsEnabledIT_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C1IMR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 32 to 63 for cpu2
  * @rmtoll C2IMR2         IMx           LL_C2_EXTI_IsEnabledIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_EXTI_IsEnabledIT_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C2IMR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 32 to 63 for cpu3
  * @rmtoll C3IMR2         IMx           LL_C3_EXTI_IsEnabledIT_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C3_EXTI_IsEnabledIT_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C3IMR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 32 to 63
  * @rmtoll IMR2         IMx           LL_EXTI_IsEnabledIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_EXTI_IsEnabledIT_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C1IMR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 32 to 63 for cpu2
  * @rmtoll C2IMR2         IMx           LL_C2_EXTI_IsEnabledIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_EXTI_IsEnabledIT_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C2IMR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 32 to 63 for cpu3
  * @rmtoll C3IMR2         IMx           LL_C3_EXTI_IsEnabledIT_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C3_EXTI_IsEnabledIT_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C3IMR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Event_Management Event_Management
  * @{
  */


/**
  * @brief  Enable ExtiLine Event request for Lines in range 0 to 31 for cpu2
  * @rmtoll C2EMR1         EMx           LL_C2_EXTI_EnableEvent_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_EnableEvent_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C2EMR1, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Event request for Lines in range 0 to 31 for cpu3
  * @rmtoll C3EMR1         EMx           LL_C3_EXTI_EnableEvent_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_EnableEvent_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C3EMR1, ExtiLine);
}


/**
  * @brief  Enable ExtiLine Event request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2EMR2         EMx           LL_C2_EXTI_EnableEvent_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_EnableEvent_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C2EMR2, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Event request for Lines in range 32 to 63 for cpu3
  * @rmtoll C3EMR2         EMx           LL_C3_EXTI_EnableEvent_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_EnableEvent_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C3EMR2, ExtiLine);
}


/**
  * @brief  Enable ExtiLine Event request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2EMR3         EMx           LL_C2_EXTI_EnableEvent_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_EnableEvent_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI1_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  SET_BIT(EXTIx->C2EMR3, ExtiLine);
}


/**
  * @brief  Disable ExtiLine Event request for Lines in range 0 to 31 for cpu2
  * @rmtoll C2EMR1         EMx           LL_C2_EXTI_DisableEvent_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_DisableEvent_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C2EMR1, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Event request for Lines in range 0 to 31 for cpu3
  * @rmtoll C3EMR1         EMx           LL_C3_EXTI_DisableEvent_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_DisableEvent_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C3EMR1, ExtiLine);
}


/**
  * @brief  Disable ExtiLine Event request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2EMR2         EMx           LL_C2_EXTI_DisableEvent_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_DisableEvent_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C2EMR2, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Event request for Lines in range 32 to 63 for cpu3
  * @rmtoll C3EMR2         EMx           LL_C3_EXTI_DisableEvent_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C3_EXTI_DisableEvent_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C3EMR2, ExtiLine);
}


/**
  * @brief  Disable ExtiLine Event request for Lines in range 32 to 63 for cpu2
  * @rmtoll C2EMR3         EMx           LL_C2_EXTI_DisableEvent_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_C2_EXTI_DisableEvent_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI1_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->C2EMR3, ExtiLine);
}


/**
  * @brief  Indicate if ExtiLine Event request is enabled for Lines in range 0 to 31 for cpu2
  * @rmtoll C2EMR1         EMx           LL_C2_EXTI_IsEnabledEvent_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_EXTI_IsEnabledEvent_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C2EMR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Event request is enabled for Lines in range 0 to 31 for cpu3
  * @rmtoll C3EMR1         EMx           LL_C3_EXTI_IsEnabledEvent_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be one of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C3_EXTI_IsEnabledEvent_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C3EMR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}


/**
  * @brief  Indicate if ExtiLine Event request is enabled for Lines in range 32 to 63 for cpu2
  * @rmtoll EMR2         EMx           LL_C2_EXTI_IsEnabledEvent_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_EXTI_IsEnabledEvent_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C2EMR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if ExtiLine Event request is enabled for Lines in range 32 to 63 for cpu3
  * @rmtoll EMR2         EMx           LL_C3_EXTI_IsEnabledEvent_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C3_EXTI_IsEnabledEvent_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C3EMR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}


/**
  * @brief  Indicate if ExtiLine Event request is enabled for Lines in range 32 to 63 for cpu2
  * @rmtoll C2EMR3         EMx           LL_C2_EXTI_IsEnabledEvent_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_EXTI_IsEnabledEvent_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI1_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->C2EMR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Rising_Trigger_Management Rising_Trigger_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Rising Edge Trigger for Lines in range 0 to 31
  * @note   The configurable wakeup lines are edge-triggered. No glitch must be
  *         generated on these lines. If a rising edge on a configurable interrupt
  *         line occurs during a write operation in the EXTI_RTSR register, the
  *         pending bit is not set.
  *         Rising and falling edge triggers can be set for
  *         the same interrupt line. In this case, both generate a trigger
  *         condition.
  * @rmtoll RTSR1        RTx           LL_EXTI_EnableRisingTrig_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableRisingTrig_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->RTSR1, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Rising Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll RTSR2        RTx           LL_EXTI_EnableRisingTrig_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableRisingTrig_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->RTSR2, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Rising Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll RTSR3        RTx           LL_EXTI_EnableRisingTrig_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableRisingTrig_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  SET_BIT(EXTIx->RTSR3, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Rising Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll RTSR1        RTx           LL_EXTI_DisableRisingTrig_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableRisingTrig_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->RTSR1, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Rising Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll RTSR2        RTx           LL_EXTI_DisableRisingTrig_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableRisingTrig_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->RTSR2, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Rising Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll RTSR3        RTx           LL_EXTI_DisableRisingTrig_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableRisingTrig_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->RTSR3, ExtiLine);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 0 to 31
  * @rmtoll RTSR1        RTx           LL_EXTI_IsEnabledRisingTrig_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledRisingTrig_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->RTSR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 32 to 63
  * @rmtoll RTSR2        RTx           LL_EXTI_IsEnabledRisingTrig_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledRisingTrig_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->RTSR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 32 to 63
  * @rmtoll RTSR3        RTx           LL_EXTI_IsEnabledRisingTrig_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledRisingTrig_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->RTSR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Falling_Trigger_Management Falling_Trigger_Management
  * @{
  */

/**
  * @brief  Enable ExtiLine Falling Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll FTSR1        FTx           LL_EXTI_EnableFallingTrig_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableFallingTrig_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->FTSR1, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Falling Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a Falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll FTSR2        FTx           LL_EXTI_EnableFallingTrig_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableFallingTrig_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->FTSR2, ExtiLine);
}

/**
  * @brief  Enable ExtiLine Falling Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a Falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll FTSR3        FTx           LL_EXTI_EnableFallingTrig_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableFallingTrig_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  SET_BIT(EXTIx->FTSR3, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Falling Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a Falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for the same interrupt line.
  *       In this case, both generate a trigger condition.
  * @rmtoll FTSR1        FTx           LL_EXTI_DisableFallingTrig_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableFallingTrig_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->FTSR1, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Falling Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a Falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for the same interrupt line.
  *       In this case, both generate a trigger condition.
  * @rmtoll FTSR2        FTx           LL_EXTI_DisableFallingTrig_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableFallingTrig_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->FTSR2, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Falling Edge Trigger for Lines in range 32 to 63
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a Falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for the same interrupt line.
  *       In this case, both generate a trigger condition.
  * @rmtoll FTSR3        FTx           LL_EXTI_DisableFallingTrig_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableFallingTrig_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  CLEAR_BIT(EXTIx->FTSR3, ExtiLine);
}

/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 0 to 31
  * @rmtoll FTSR1        FTx           LL_EXTI_IsEnabledFallingTrig_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledFallingTrig_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->FTSR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 32 to 63
  * @rmtoll FTSR2        FTx           LL_EXTI_IsEnabledFallingTrig_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledFallingTrig_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->FTSR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 32 to 63
  * @rmtoll FTSR3        FTx           LL_EXTI_IsEnabledFallingTrig_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledFallingTrig_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->FTSR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Software_Interrupt_Management Software_Interrupt_Management
  * @{
  */

/**
  * @brief  Generate a software Interrupt Event for Lines in range 0 to 31
  * @note If the interrupt is enabled on this line in the EXTI_IMR1, writing a 1 to
  *       this bit when it is at '0' sets the corresponding pending bit in EXTI_PR1
  *       resulting in an interrupt request generation.
  *       This bit is cleared by clearing the corresponding bit in the EXTI_PR1
  *       register (by writing a 1 into the bit)
  * @rmtoll SWIER1       SWIx          LL_EXTI_GenerateSWI_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_GenerateSWI_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  SET_BIT(EXTIx->SWIER1, ExtiLine);
}

/**
  * @brief  Generate a software Interrupt Event for Lines in range 32 to 63
  * @note If the interrupt is enabled on this line in the EXTI_IMR2, writing a 1 to
  *       this bit when it is at '0' sets the corresponding pending bit in EXTI_PR2
  *       resulting in an interrupt request generation.
  *       This bit is cleared by clearing the corresponding bit in the EXTI_PR2
  *       register (by writing a 1 into the bit)
  * @rmtoll SWIER2       SWIx          LL_EXTI_GenerateSWI_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_GenerateSWI_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  SET_BIT(EXTIx->SWIER2, ExtiLine);
}

/**
  * @brief  Generate a software Interrupt Event for Lines in range 32 to 63
  * @note If the interrupt is enabled on this line in the EXTI_IMR2, writing a 1 to
  *       this bit when it is at '0' sets the corresponding pending bit in EXTI_PR2
  *       resulting in an interrupt request generation.
  *       This bit is cleared by clearing the corresponding bit in the EXTI_PR2
  *       register (by writing a 1 into the bit)
  * @rmtoll SWIER3       SWIx          LL_EXTI_GenerateSWI_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_GenerateSWI_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  SET_BIT(EXTIx->SWIER3, ExtiLine);
}

/**
  * @}
  */

/** @defgroup EXTI_LL_EF_Flag_Management Flag_Management
  * @{
  */

/**
  * @brief  Check if the ExtLine Flag is set or not for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR1          PIFx           LL_EXTI_IsActiveRisingFlag_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveRisingFlag_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->RPR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the ExtLine Flag is set or not for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR2          PIFx           LL_EXTI_IsActiveRisingFlag_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveRisingFlag_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->RPR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the ExtLine Flag is set or not for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR3          PIFx           LL_EXTI_IsActiveRisingFlag_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveRisingFlag_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->RPR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Read ExtLine Combination Flag for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR1          PIFx           LL_EXTI_ReadRisingFlag_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadRisingFlag_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return (uint32_t)(READ_BIT(EXTIx->RPR1, ExtiLine));
}

/**
  * @brief  Read ExtLine Combination Flag for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR2          PIFx           LL_EXTI_ReadRisingFlag_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadRisingFlag_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return (uint32_t)(READ_BIT(EXTIx->RPR2, ExtiLine));
}

/**
  * @brief  Read ExtLine Combination Flag for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR3          PIFx           LL_EXTI_ReadRisingFlag_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadRisingFlag_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return (uint32_t)(READ_BIT(EXTIx->RPR3, ExtiLine));
}

/**
  * @brief  Clear ExtLine Flags for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR1          PIFx           LL_EXTI_ClearRisingFlag_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_ClearRisingFlag_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  WRITE_REG(EXTIx->RPR1, ExtiLine);
}

/**
  * @brief  Clear ExtLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR2          PIFx           LL_EXTI_ClearRisingFlag_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_ClearRisingFlag_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  WRITE_REG(EXTIx->RPR2, ExtiLine);
}

/**
  * @brief  Clear ExtLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll RPR3          PIFx           LL_EXTI_ClearRisingFlag_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_ClearRisingFlag_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  WRITE_REG(EXTIx->RPR3, ExtiLine);
}


/**
  * @brief  Check if the ExtLine Flag is set or not for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR1          PIFx           LL_EXTI_IsActiveFallingFlag_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveFallingFlag_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->FPR1, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the ExtLine Flag is set or not for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR2          PIFx           LL_EXTI_IsActiveFallingFlag_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveFallingFlag_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->FPR2, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the ExtLine Flag is set or not for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR3          PIFx           LL_EXTI_IsActiveFallingFlag_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_EXTI_IsActiveFallingFlag_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return ((READ_BIT(EXTIx->FPR3, ExtiLine) == (ExtiLine)) ? 1UL : 0UL);
}

/**
  * @brief  Read ExtLine Combination Flag for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR1          PIFx           LL_EXTI_ReadFallingFlag_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadFallingFlag_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  return (uint32_t)(READ_BIT(EXTIx->FPR1, ExtiLine));
}

/**
  * @brief  Read ExtLine Combination Flag for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR2          PIFx           LL_EXTI_ReadFallingFlag_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadFallingFlag_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  return (uint32_t)(READ_BIT(EXTIx->FPR2, ExtiLine));
}

/**
  * @brief  Read ExtLine Combination Flag for  Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR3          PIFx           LL_EXTI_ReadFallingFlag_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t LL_EXTI_ReadFallingFlag_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  return (uint32_t)(READ_BIT(EXTIx->FPR3, ExtiLine));
}

/**
  * @brief  Clear ExtLine Flags for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR1          PIFx           LL_EXTI_ClearFallingFlag_0_31
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_LINE_ALL_0_31
  *         @arg @ref LL_EXTI2_LINE_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_ClearFallingFlag_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_0_31(EXTIx, ExtiLine));
  WRITE_REG(EXTIx->FPR1, ExtiLine);
}

/**
  * @brief  Clear ExtLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR2          PIFx           LL_EXTI_ClearFallingFlag_32_63
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_LINE_ALL_32_63
  *         @arg @ref LL_EXTI2_LINE_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_ClearFallingFlag_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_32_63(EXTIx, ExtiLine));
  WRITE_REG(EXTIx->FPR2, ExtiLine);
}

/**
  * @brief  Clear ExtLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll FPR3          PIFx           LL_EXTI_ClearFallingFlag_64_95
  * @param  EXTIx EXTI Instance
  * @param  ExtiLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_LINE_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_LINE_ALL_64_95
  *         @arg @ref LL_EXTI2_LINE_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_ClearFallingFlag_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_LINE_64_95(EXTIx, ExtiLine));
  WRITE_REG(EXTIx->FPR3, ExtiLine);
}


/* SECCFGRx */

/**
  * @brief  Enable ExtiSecureLine Flags for Lines in range 0 to 31
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_SEC_ALL_0_31
  *         @arg @ref LL_EXTI2_SEC_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableSecure_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_0_31(EXTIx, ExtiSecureLine));
  SET_BIT(EXTIx->SECCFGR1, ExtiSecureLine);
}
/**
  * @brief  Enable ExtiSecureLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_SEC_ALL_32_63
  *         @arg @ref LL_EXTI2_SEC_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableSecure_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_32_63(EXTIx, ExtiSecureLine));
  SET_BIT(EXTIx->SECCFGR2, ExtiSecureLine);
}

/**
  * @brief  Enable ExtiSecureLine Flags for Lines in range 64 to 95
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_SEC_ALL_64_95
  *         @arg @ref LL_EXTI2_SEC_ALL_64_95
  *         (*) all values are not $defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableSecure_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_64_95(EXTIx, ExtiSecureLine));
  SET_BIT(EXTIx->SECCFGR3, ExtiSecureLine);
}

/**
  * @brief  Return ExtiSecureLine Combination Flag for Lines in range 0 to 31
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_SEC_ALL_0_31
  *         @arg @ref LL_EXTI2_SEC_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected line secure flag is enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledSecure_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_0_31(EXTIx, ExtiSecureLine));
  return (uint32_t)(READ_BIT(EXTIx->SECCFGR1, ExtiSecureLine));
}

/**
  * @brief  Return ExtiSecureLine Combination Flag for Lines in range 32 to 63
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_SEC_ALL_32_63
  *         @arg @ref LL_EXTI2_SEC_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected line secure flag is enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledSecure_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_32_63(EXTIx, ExtiSecureLine));
  return (uint32_t)(READ_BIT(EXTIx->SECCFGR2, ExtiSecureLine));
}

/**
  * @brief  Return ExtiSecureLine Combination Flag for Lines in range 64 to 95
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_SEC_ALL_64_95
  *         @arg @ref LL_EXTI2_SEC_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected line secure flag is enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledSecure_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_64_95(EXTIx, ExtiSecureLine));
  return (uint32_t)(READ_BIT(EXTIx->SECCFGR3, ExtiSecureLine));
}

/**
  * @brief  Disable ExtiSecureLine Flags for Lines in range 0 to 31
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_SEC_ALL_0_31
  *         @arg @ref LL_EXTI2_SEC_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableSecure_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_0_31(EXTIx, ExtiSecureLine));
  CLEAR_BIT(EXTIx->SECCFGR1, ExtiSecureLine);
}

/**
  * @brief  Disable ExtiSecureLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_SEC_ALL_32_63
  *         @arg @ref LL_EXTI2_SEC_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableSecure_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_32_63(EXTIx, ExtiSecureLine));
  CLEAR_BIT(EXTIx->SECCFGR2, ExtiSecureLine);
}

/**
  * @brief  Disable ExtiSecureLine Flags for Lines in range 64 to 95
  * @note This bit is set when the selected line security is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiSecureLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_SEC_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_SEC_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_SEC_ALL_64_95
  *         @arg @ref LL_EXTI2_SEC_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableSecure_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiSecureLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_SEC_64_95(EXTIx, ExtiSecureLine));
  CLEAR_BIT(EXTIx->SECCFGR3, ExtiSecureLine);
}


/* PRIVCFGRx */

/**
  * @brief  Enable ExtiPrivilegeLine Flags for Lines in range 0 to 31
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_PRIV_ALL_0_31
  *         @arg @ref LL_EXTI2_PRIV_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnablePrivilege_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_0_31(EXTIx, ExtiPrivilegeLine));
  SET_BIT(EXTIx->PRIVCFGR1, ExtiPrivilegeLine);
}
/**
  * @brief  Enable ExtiPrivilegeLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_PRIV_ALL_32_63
  *         @arg @ref LL_EXTI2_PRIV_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnablePrivilege_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_32_63(EXTIx, ExtiPrivilegeLine));
  SET_BIT(EXTIx->PRIVCFGR2, ExtiPrivilegeLine);
}

/**
  * @brief  Enable ExtiPrivilegeLine Flags for Lines in range 64 to 95
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_PRIV_ALL_64_95
  *         @arg @ref LL_EXTI2_PRIV_ALL_64_95
  *         (*) all values are not $defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnablePrivilege_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_64_95(EXTIx, ExtiPrivilegeLine));
  SET_BIT(EXTIx->PRIVCFGR3, ExtiPrivilegeLine);
}

/**
  * @brief  Return ExtiPrivilegeLine Combination Flag for Lines in range 0 to 31
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_PRIV_ALL_0_31
  *         @arg @ref LL_EXTI2_PRIV_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected line Privilege flag is enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledPrivilege_0_31(const EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_0_31(EXTIx, ExtiPrivilegeLine));
  return (uint32_t)(READ_BIT(EXTIx->PRIVCFGR1, ExtiPrivilegeLine));
}

/**
  * @brief  Return ExtiPrivilegeLine Combination Flag for Lines in range 32 to 63
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_PRIV_ALL_32_63
  *         @arg @ref LL_EXTI2_PRIV_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected line Privilege flag is enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledPrivilege_32_63(const EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_32_63(EXTIx, ExtiPrivilegeLine));
  return (uint32_t)(READ_BIT(EXTIx->PRIVCFGR2, ExtiPrivilegeLine));
}

/**
  * @brief  Return ExtiPrivilegeLine Combination Flag for Lines in range 64 to 95
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_PRIV_ALL_64_95
  *         @arg @ref LL_EXTI2_PRIV_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval @note This bit is set when the selected line Privilege flag is enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledPrivilege_64_95(const EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_64_95(EXTIx, ExtiPrivilegeLine));
  return (uint32_t)(READ_BIT(EXTIx->PRIVCFGR3, ExtiPrivilegeLine));
}

/**
  * @brief  Disable ExtiPrivilegeLine Flags for Lines in range 0 to 31
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 0 to 31)
  *         @arg @ref LL_EXTI1_PRIV_ALL_0_31
  *         @arg @ref LL_EXTI2_PRIV_ALL_0_31
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisablePrivilege_0_31(EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_0_31(EXTIx, ExtiPrivilegeLine));
  CLEAR_BIT(EXTIx->PRIVCFGR1, ExtiPrivilegeLine);
}

/**
  * @brief  Disable ExtiPrivilegeLine Flags for Lines in range 32 to 63
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 32 to 63)
  *         @arg @ref LL_EXTI1_PRIV_ALL_32_63
  *         @arg @ref LL_EXTI2_PRIV_ALL_32_63
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisablePrivilege_32_63(EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_32_63(EXTIx, ExtiPrivilegeLine));
  CLEAR_BIT(EXTIx->PRIVCFGR2, ExtiPrivilegeLine);
}

/**
  * @brief  Disable ExtiPrivilegeLine Flags for Lines in range 64 to 95
  * @note This bit is set when the selected line privilege is enabled
  * @param  EXTIx EXTI Instance
  * @param  ExtiPrivilegeLine This parameter can be a combination of the following values(*):
  *         @arg @ref LL_EXTI1_PRIV_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI2_PRIV_x (with x, the line number from 64 to 95)
  *         @arg @ref LL_EXTI1_PRIV_ALL_64_95
  *         @arg @ref LL_EXTI2_PRIV_ALL_64_95
  *         (*) all values are not defined in all instances
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisablePrivilege_64_95(EXTI_TypeDef *EXTIx, uint32_t ExtiPrivilegeLine)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_LL_EXTI_PRIV_64_95(EXTIx, ExtiPrivilegeLine));
  CLEAR_BIT(EXTIx->PRIVCFGR3, ExtiPrivilegeLine);
}

/**
  * @brief  Enable Global security, privilege, CID configuration lock
  * @param  EXTIx EXTI Instance
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_EnableGlobalSecurityLock(EXTI_TypeDef *EXTIx)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  SET_BIT(EXTIx->LOCKR, EXTI_LOCKR_GLOCK);
}


/**
  * @brief  Disable Global security, privilege, CID configuration lock
  * @param  EXTIx EXTI Instance
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_DisableGlobalSecurityLock(EXTI_TypeDef *EXTIx)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  CLEAR_BIT(EXTIx->LOCKR, EXTI_LOCKR_GLOCK);
}

/**
  * @brief  return Global security, privilege, CID configuration lock status
  * @param  EXTIx EXTI Instance
  * @retval true is locked
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnableGlobalSecurityLock(const EXTI_TypeDef *EXTIx)
{
  /* Check the parameters */
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  return ((READ_BIT(EXTIx->LOCKR, EXTI_LOCKR_GLOCK) == (EXTI_LOCKR_GLOCK)) ? 1UL : 0UL);
}


/**
  * @brief  Set  authorised  CID for  accessing a event line configuration
  * @note relevant only in case of  CID filtering active on event input resource
  * @param  EXTIx EXTI Instance
  * @param  evtIndex : LL_EXTIx_EnCIDCFGR_y (from 0 to 95). valid index depends on EXTI instance
  * @param  cid : authorised cid value   2 bits (or 3 bits soon)
  */
__STATIC_INLINE void LL_EXTI_setEventCid(EXTI_TypeDef *EXTIx, uint32_t evtIndex, uint32_t cid)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_EXTI_EVT_CID_VALID(EXTIx, evtIndex));
  assert_param(IS_EXTI_CID_VALID(cid));

  MODIFY_REG(EXTIx->ECIDCFGR[evtIndex], EXTI_EnCIDCFGR_CID, cid << EXTI_EnCIDCFGR_CID_Pos);
}


/**
  * @brief  Get  authorised  CID for  accessing a non shareable resource
  * @note relevant only in case of  CID filtering active on input resource
  * @param  EXTIx EXTI Instance
  * @param  evtIndex : from 0 to 95. valid index depends on EXTI instance
  * @retval CID for event line configuration
  */
__STATIC_INLINE uint32_t LL_EXTI_getEventCid(const EXTI_TypeDef *EXTIx, uint32_t evtIndex)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_EXTI_EVT_CID_VALID(EXTIx, evtIndex));

  return ((READ_REG(EXTIx->ECIDCFGR[evtIndex]) & (EXTI_EnCIDCFGR_CID)) >> EXTI_EnCIDCFGR_CID_Pos) ;
}

/**
  * @brief  Enable/Disable CID filtering  to  control event configuration
  * @param  EXTIx EXTI Instance
  * @param  evtIndex : from 0 to 95. valid index depends on EXTI instance
  */
__STATIC_INLINE void LL_EXTI_EnableEventCidFiltering(EXTI_TypeDef *EXTIx, uint32_t evtIndex)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_EXTI_EVT_CID_VALID(EXTIx, evtIndex));

  SET_BIT(EXTIx->ECIDCFGR[evtIndex], EXTI_EnCIDCFGR_CFEN);
}

/**
  * @brief  Enable/Disable CID filtering  to  control event configuration
  * @param  EXTIx EXTI Instance
  * @param  evtIndex : from 0 to 95. valid index depends on EXTI instance
  */
__STATIC_INLINE void LL_EXTI_DisableEventCidFiltering(EXTI_TypeDef *EXTIx, uint32_t evtIndex)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_EXTI_EVT_CID_VALID(EXTIx, evtIndex));

  SET_BIT(EXTIx->ECIDCFGR[evtIndex], EXTI_EnCIDCFGR_CFEN);
}

/**
  * @brief  Check if CID filtering t  control event configuration access is enabled.
  * @param  EXTIx EXTI Instance
  * @param  evtIndex : from 0 to 95. valid index depends on EXTI instance
  * @retval true is filtering enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledEventCidFiltering(const EXTI_TypeDef *EXTIx, uint32_t evtIndex)
{
  return ((READ_BIT(EXTIx->ECIDCFGR[evtIndex], EXTI_EnCIDCFGR_CFEN) == EXTI_EnCIDCFGR_CFEN) ? 1UL : 0UL);
}


/**
  * @brief  Set  authorised  CID for  accessing C1 processor configuration
  * @note relevant only in case of  CID filtering active on processor resource
  * @param  EXTIx EXTI Instance
  * @param  cid : authorised cid value   2 bits (or 3 bits soon)
  */
__STATIC_INLINE void LL_EXTI_setC1ProcessorCid(EXTI_TypeDef *EXTIx, uint32_t cid)
{
  assert_param(IS_EXTI_CID_VALID(cid));
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  MODIFY_REG(EXTIx->C1CIDCFGR, EXTI_CmCIDCFGR_CID, cid << EXTI_CmCIDCFGR_CID_Pos);
}


/**
  * @brief  Get  authorised  CID for  accessing C1 processor configuration
  * @note relevant only in case of  CID filtering active on input resource
  * @param  EXTIx EXTI Instance
  * @retval CID for C1 processor configuration
  */
__STATIC_INLINE uint32_t LL_EXTI_getC1ProcessorCid(const EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  return ((READ_REG(EXTIx->C1CIDCFGR) & (EXTI_CmCIDCFGR_CID)) >> EXTI_CmCIDCFGR_CID_Pos) ;
}

/**
  * @brief  Enable EXTI CID filtering  to  control processor C1 configuration
  * @param  EXTIx EXTI Instance
  */
__STATIC_INLINE void LL_EXTI_EnableC1ProcessorCidFiltering(EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  SET_BIT(EXTIx->C1CIDCFGR, EXTI_CmCIDCFGR_CFEN);
}

/**
  * @brief  Disable  CID filtering  to  control processor C1 configuration
  * @param  EXTIx EXTI Instance
  */
__STATIC_INLINE void LL_EXTI_DisableC1ProcessorCidFiltering(EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  CLEAR_BIT(EXTIx->C1CIDCFGR, EXTI_CmCIDCFGR_CFEN);
}

/**
  * @brief  Check if CID filtering to control processor C1 configuration access is enabled.
  * @param  EXTIx EXTI Instance
  * @retval true is filtering enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledC1ProcessorCidFiltering(const EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  return ((READ_BIT(EXTIx->C1CIDCFGR, EXTI_CmCIDCFGR_CFEN) == EXTI_CmCIDCFGR_CFEN) ? 1UL : 0UL);
}

/**
  * @brief  Set  authorised  CID for  accessing C2 processor configuration
  * @note relevant only in case of  CID filtering active on processor resource
  * @param  EXTIx EXTI Instance
  * @param  cid : authorised cid value   2 bits (or 3 bits soon)
  */
__STATIC_INLINE void LL_EXTI_setC2ProcessorCid(EXTI_TypeDef *EXTIx, uint32_t cid)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  assert_param(IS_EXTI_CID_VALID(cid));
  MODIFY_REG(EXTIx->C2CIDCFGR, EXTI_CmCIDCFGR_CID, cid << EXTI_CmCIDCFGR_CID_Pos);
}


/**
  * @brief  Get  authorised  CID for  accessing C2 processor configuration
  * @note relevant only in case of  CID filtering active on input resource
  * @param  EXTIx EXTI Instance
  * @retval CID for C2 processor configuration
  */
__STATIC_INLINE uint32_t LL_EXTI_getC2ProcessorCid(const EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  return ((READ_REG(EXTIx->C2CIDCFGR) & (EXTI_CmCIDCFGR_CID)) >> EXTI_CmCIDCFGR_CID_Pos) ;
}

/**
  * @brief  Enable CID filtering  to  control processor C2 configuration
  * @param  EXTIx EXTI Instance
  */
__STATIC_INLINE void LL_EXTI_EnableC2ProcessorCidFiltering(EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  SET_BIT(EXTIx->C2CIDCFGR, EXTI_CmCIDCFGR_CFEN);
}

/**
  * @brief  Disable CID filtering  to  control processor C2 configuration
  * @param  EXTIx EXTI Instance
  */
__STATIC_INLINE void LL_EXTI_DisableC2ProcessorCidFiltering(EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  CLEAR_BIT(EXTIx->C2CIDCFGR, EXTI_CmCIDCFGR_CFEN);
}

/**
  * @brief  Check if  CID filtering to control processor C2 configuration access is enabled.
  * @param  EXTIx EXTI Instance
  * @retval true is filtering enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledC2ProcessorCidFiltering(const EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI_ALL_INSTANCE(EXTIx));
  return ((READ_BIT(EXTIx->C2CIDCFGR, EXTI_CmCIDCFGR_CFEN) == EXTI_CmCIDCFGR_CFEN) ? 1UL : 0UL);
}


/**
  * @brief  Set  authorised  CID for  accessing C3 processor configuration
  * @note relevant only in case of  CID filtering active on processor resource
  * @param  EXTIx EXTI2 Instance only
  * @param  cid : authorised cid value   2 bits (or 3 bits soon)
  */
__STATIC_INLINE void LL_EXTI_setC3ProcessorCid(EXTI_TypeDef *EXTIx, uint32_t cid)
{
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  assert_param(IS_EXTI_CID_VALID(cid));
  MODIFY_REG(EXTIx->C3CIDCFGR, EXTI_CmCIDCFGR_CID, cid << EXTI_CmCIDCFGR_CID_Pos);
}


/**
  * @brief  Get  authorised  CID for  accessing C3 processor configuration
  * @note relevant only in case of  CID filtering active on input resource
  * @param  EXTIx EXTI2 Instance only
  * @retval CID for C3 processor configuration
  */
__STATIC_INLINE uint32_t LL_EXTI_getC3ProcessorCid(const EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  return ((READ_REG(EXTIx->C3CIDCFGR) & (EXTI_CmCIDCFGR_CID)) >> EXTI_CmCIDCFGR_CID_Pos) ;
}


/**
  * @brief  Enable  CID filtering  to  control processor C3 configuration
  * @param  EXTIx EXTI2 Instance only
  */
__STATIC_INLINE void LL_EXTI_EnableC3ProcessorCidFiltering(EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  SET_BIT(EXTIx->C3CIDCFGR, EXTI_CmCIDCFGR_CFEN);
}

/**
  * @brief  Disable CID filtering  to  control processor C3 configuration
  * @param  EXTIx EXTI2 Instance only
  */
__STATIC_INLINE void LL_EXTI_DisableC3ProcessorCidFiltering(EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  CLEAR_BIT(EXTIx->C3CIDCFGR, EXTI_CmCIDCFGR_CFEN);
}

/**
  * @brief  Check if CID filtering to control processor C3 configuration access is enabled.
  * @param  EXTIx EXTI2 Instance only
  * @retval true is filtering enabled
  */
__STATIC_INLINE uint32_t LL_EXTI_IsEnabledC3ProcessorCidFiltering(const EXTI_TypeDef *EXTIx)
{
  assert_param(IS_EXTI2_INSTANCE(EXTIx));
  return ((READ_BIT(EXTIx->C3CIDCFGR, EXTI_CmCIDCFGR_CFEN) == EXTI_CmCIDCFGR_CFEN) ? 1UL : 0UL);
}


/**
  * @brief  Configure source input for the EXTI external interrupt.
  * @rmtoll EXTIx_EXTICR1 EXTI0         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR1 EXTI1         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR1 EXTI2         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR1 EXTI3         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR2 EXTI4         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR2 EXTI5         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR2 EXTI6         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR2 EXTI7         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR3 EXTI8         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR3 EXTI9         LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR3 EXTI10        LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR3 EXTI11        LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR4 EXTI12        LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR4 EXTI13        LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR4 EXTI14        LL_EXTI_SetEXTISource\n
  *         EXTIx_EXTICR4 EXTI15        LL_EXTI_SetEXTISource
  * @param  EXTIx EXTI Instance
  * @param  Port This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_EXTICR_PORTA
  *         @arg @ref LL_EXTI_EXTICR_PORTB
  *         @arg @ref LL_EXTI_EXTICR_PORTC
  *         @arg @ref LL_EXTI_EXTICR_PORTD
  *         @arg @ref LL_EXTI_EXTICR_PORTE
  *         @arg @ref LL_EXTI_EXTICR_PORTF
  *         @arg @ref LL_EXTI_EXTICR_PORTG
  *         @arg @ref LL_EXTI_EXTICR_PORTH
  *         @arg @ref LL_EXTI_EXTICR_PORTI
  *         @arg @ref LL_EXTI_EXTICR_PORTJ
  *         @arg @ref LL_EXTI_EXTICR_PORTK
  *         @arg @ref LL_EXTI_EXTICR_PORTZ
  *
  *         (*) value not defined in all devices
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_EXTI_LINE0
  *         @arg @ref LL_EXTI_EXTI_LINE1
  *         @arg @ref LL_EXTI_EXTI_LINE2
  *         @arg @ref LL_EXTI_EXTI_LINE3
  *         @arg @ref LL_EXTI_EXTI_LINE4
  *         @arg @ref LL_EXTI_EXTI_LINE5
  *         @arg @ref LL_EXTI_EXTI_LINE6
  *         @arg @ref LL_EXTI_EXTI_LINE7
  *         @arg @ref LL_EXTI_EXTI_LINE8
  *         @arg @ref LL_EXTI_EXTI_LINE9
  *         @arg @ref LL_EXTI_EXTI_LINE10
  *         @arg @ref LL_EXTI_EXTI_LINE11
  *         @arg @ref LL_EXTI_EXTI_LINE12
  *         @arg @ref LL_EXTI_EXTI_LINE13
  *         @arg @ref LL_EXTI_EXTI_LINE14
  *         @arg @ref LL_EXTI_EXTI_LINE15
  * @retval None
  */
__STATIC_INLINE void LL_EXTI_SetEXTISource(EXTI_TypeDef *EXTIx, uint32_t Port, uint32_t Line)
{
  MODIFY_REG(EXTIx->EXTICR[Line & 0x03U], EXTI_EXTICR1_EXTI0 << (Line >> LL_EXTI_REGISTER_PINPOS_SHFT), \
             Port << (Line >> LL_EXTI_REGISTER_PINPOS_SHFT));
}

/**
  * @brief  Get the configured defined for specific EXTI Line
  * @rmtoll EXTIx_EXTICR1 EXTI0         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR1 EXTI1         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR1 EXTI2         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR1 EXTI3         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR2 EXTI4         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR2 EXTI5         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR2 EXTI6         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR2 EXTI7         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR3 EXTI8         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR3 EXTI9         LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR3 EXTI10        LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR3 EXTI11        LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR4 EXTI12        LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR4 EXTI13        LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR4 EXTI14        LL_EXTI_GetEXTISource\n
  *         EXTIx_EXTICR4 EXTI15        LL_EXTI_GetEXTISource
  * @param  EXTIx EXTI Instance
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_EXTI_EXTI_LINE0
  *         @arg @ref LL_EXTI_EXTI_LINE1
  *         @arg @ref LL_EXTI_EXTI_LINE2
  *         @arg @ref LL_EXTI_EXTI_LINE3
  *         @arg @ref LL_EXTI_EXTI_LINE4
  *         @arg @ref LL_EXTI_EXTI_LINE5
  *         @arg @ref LL_EXTI_EXTI_LINE6
  *         @arg @ref LL_EXTI_EXTI_LINE7
  *         @arg @ref LL_EXTI_EXTI_LINE8
  *         @arg @ref LL_EXTI_EXTI_LINE9
  *         @arg @ref LL_EXTI_EXTI_LINE10
  *         @arg @ref LL_EXTI_EXTI_LINE11
  *         @arg @ref LL_EXTI_EXTI_LINE12
  *         @arg @ref LL_EXTI_EXTI_LINE13
  *         @arg @ref LL_EXTI_EXTI_LINE14
  *         @arg @ref LL_EXTI_EXTI_LINE15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_EXTI_EXTICR_PORTA
  *         @arg @ref LL_EXTI_EXTICR_PORTB
  *         @arg @ref LL_EXTI_EXTICR_PORTC
  *         @arg @ref LL_EXTI_EXTICR_PORTD
  *         @arg @ref LL_EXTI_EXTICR_PORTE
  *         @arg @ref LL_EXTI_EXTICR_PORTF
  *         @arg @ref LL_EXTI_EXTICR_PORTG
  *         @arg @ref LL_EXTI_EXTICR_PORTH
  *         @arg @ref LL_EXTI_EXTICR_PORTI
  *         @arg @ref LL_EXTI_EXTICR_PORTJ
  *         @arg @ref LL_EXTI_EXTICR_PORTK
  *         @arg @ref LL_EXTI_EXTICR_PORTZ
  */
__STATIC_INLINE uint32_t LL_EXTI_GetEXTISource(const EXTI_TypeDef *EXTIx, uint32_t Line)
{
  return (uint32_t)(READ_BIT(EXTIx->EXTICR[Line & 0x03U],
                             ((uint32_t)EXTI_EXTICR1_EXTI0 << (Line >> LL_EXTI_REGISTER_PINPOS_SHFT))) >>
                    (Line >> LL_EXTI_REGISTER_PINPOS_SHFT));
}


/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup EXTI_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_EXTI_Init(EXTI_TypeDef *EXTIx, LL_EXTI_InitTypeDef *EXTI_InitStruct);
ErrorStatus LL_EXTI_DeInit(EXTI_TypeDef *EXTIx);
void        LL_EXTI_StructInit(LL_EXTI_InitTypeDef *EXTI_InitStruct);
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

#endif /* EXTI1 || EXTI2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP2xx_LL_EXTI_H */
