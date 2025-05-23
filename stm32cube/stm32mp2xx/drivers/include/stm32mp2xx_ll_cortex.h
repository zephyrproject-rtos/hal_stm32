/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_cortex.h
  * @author  MCD Application Team
  * @brief   Header file of CORTEX LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL CORTEX driver contains a set of generic APIs that can be
    used by user:
      (+) SYSTICK configuration used by @ref LL_mDelay and @ref LL_Init1msTick with
           HCLK source or @ref LL_Init1msTick_HCLK_Div8, @ref LL_Init1msTick_LSI or
           @ref LL_Init1msTick_LSE with external source
      (+) Low power mode configuration (SCB register of Cortex-MCU)
      (+) API to access to MCU info (CPUID register)
      (+) API to enable fault handler (SHCSR accesses)
      (+) API to enable and disable the MPU secure and non-secure
      (+) API to configure the region of MPU secure and non-secure
      (+) API to configure the attributes region of MPU secure and non-secure

  @endverbatim
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP2xx_LL_CORTEX_H
#define __STM32MP2xx_LL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

/** @defgroup CORTEX_LL CORTEX
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Constants CORTEX LL Exported Constants
  * @{
  */

/** @defgroup CORTEX_LL_EC_CLKSOURCE_HCLK SYSTICK Clock Source
  * @{
  */
#define LL_SYSTICK_CLKSOURCE_EXTERNAL      0x00000000U                 /*!< External clock source selected as SysTick
                                                                            clock source */
#define LL_SYSTICK_CLKSOURCE_HCLK          SysTick_CTRL_CLKSOURCE_Msk  /*!< AHB clock selected as SysTick
                                                                            clock source */
/** Legacy definitions for backward compatibility purpose
  */
#define LL_SYSTICK_CLKSOURCE_HCLK_DIV8    LL_SYSTICK_CLKSOURCE_EXTERNAL
/**
  */
/**
  * @}
  */

#if !defined(CORE_CM0PLUS)
/** @defgroup CORTEX_LL_EC_FAULT Handler Fault type
  * @{
  */
#define LL_HANDLER_FAULT_USG               SCB_SHCSR_USGFAULTENA_Msk              /*!< Usage fault */
#define LL_HANDLER_FAULT_BUS               SCB_SHCSR_BUSFAULTENA_Msk              /*!< Bus fault */
#define LL_HANDLER_FAULT_MEM               SCB_SHCSR_MEMFAULTENA_Msk              /*!< Memory management fault */
#define LL_HANDLER_FAULT_SECURE            SCB_SHCSR_SECUREFAULTENA_Msk           /*!< Secure fault */
/**
  * @}
  */
#endif /* !defined(CORE_CM0PLUS) */

#if __MPU_PRESENT
/* [MPU/CONSTANTS] M0+ (ARMv6-M) / M33 (ARMv8-M) common definitions */
/* Register MPU_CTRL */
/** @defgroup CORTEX_LL_MPU_HFNMI_PRIVDEF_Control CORTEX LL MPU HFNMI and PRIVILEGED Access control
  * @{
  */
#define LL_MPU_CTRL_HFNMI_PRIVDEF_NONE     0x00000000U                                       /*!< Disable NMI and privileged SW access */
#define LL_MPU_CTRL_HARDFAULT_NMI          MPU_CTRL_HFNMIENA_Msk                             /*!< Enables the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
#define LL_MPU_CTRL_PRIVILEGED_DEFAULT     MPU_CTRL_PRIVDEFENA_Msk                           /*!< Enable privileged software access to default memory map */
#define LL_MPU_CTRL_HFNMI_PRIVDEF          (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk) /*!< Enable NMI and privileged SW access */
/**
  * @}
  */

/* Register MPU_RBAR */
/** @defgroup CORTEX_LL_EC_REGION_INDEX CORTEX LL MPU Region Index
  * @{
  */
#define LL_MPU_REGION_NUMBER0              0x00U /*!< Region Index 0 */
#define LL_MPU_REGION_NUMBER1              0x01U /*!< Region Index 1 */
#define LL_MPU_REGION_NUMBER2              0x02U /*!< Region Index 2 */
#define LL_MPU_REGION_NUMBER3              0x03U /*!< Region Index 3 */
#define LL_MPU_REGION_NUMBER4              0x04U /*!< Region Index 4 */
#define LL_MPU_REGION_NUMBER5              0x05U /*!< Region Index 5 */
#define LL_MPU_REGION_NUMBER6              0x06U /*!< Region Index 6 */
#define LL_MPU_REGION_NUMBER7              0x07U /*!< Region Index 7 */
/* On MP2, Cortex-M33 MPU has got 16 secure and 16 non-secure regions */
#if defined(CORE_CM33)
#define LL_MPU_REGION_NUMBER8              0x08U /*!< Region Index 8 */
#define LL_MPU_REGION_NUMBER9              0x09U /*!< Region Index 9 */
#define LL_MPU_REGION_NUMBER10             0x0AU /*!< Region Index 10 */
#define LL_MPU_REGION_NUMBER11             0x0BU /*!< Region Index 11 */
#define LL_MPU_REGION_NUMBER12             0x0CU /*!< Region Index 12 */
#define LL_MPU_REGION_NUMBER13             0x0DU /*!< Region Index 13 */
#define LL_MPU_REGION_NUMBER14             0x0EU /*!< Region Index 14 */
#define LL_MPU_REGION_NUMBER15             0x0FU /*!< Region Index 15 */
#endif /* defined(CORE_CM33) */
/**
  * @}
  */

/* Register MPU_RASR (M0+) / MPU_RLAR (M33) */
/** @defgroup CORTEX_LL_MPU_Region_Enable CORTEX LL MPU Region Enable
  * @{
  */
#define LL_MPU_REGION_ENABLE               1U
#define LL_MPU_REGION_DISABLE              0U
/**
  * @}
  */

/** @defgroup CORTEX_LL_MPU_Instruction_Access CORTEX LL MPU Instruction Access
  * @{
  */
/* Register MPU_RBAR (Cortex-M33) : bit 0 */
#if defined(CORE_CM33)
#define LL_MPU_INSTRUCTION_ACCESS_ENABLE   (0U << MPU_RBAR_XN_Pos)
#define LL_MPU_INSTRUCTION_ACCESS_DISABLE  (1U << MPU_RBAR_XN_Pos)
/* Register MPU_RASR (Cortex-M0+) : bit 28 */
#else /* defined(CORE_CM33) */
#define LL_MPU_INSTRUCTION_ACCESS_ENABLE   0x00U            /*!< Instruction fetches enabled */
#define LL_MPU_INSTRUCTION_ACCESS_DISABLE  MPU_RASR_XN_Msk  /*!< Instruction fetches disabled */
#endif /* defined(CORE_CM33) */
/**
  * @}
  */

/** @defgroup CORTEX_LL_MPU_Access_Shareable CORTEX LL MPU Instruction Access Shareable
  * @{
  */
/* Register MPU_RBAR (Cortex-M33) : bits [4:3] */
#if defined(CORE_CM33)
#define LL_MPU_ACCESS_NOT_SHAREABLE        (0U << MPU_RBAR_SH_Pos)
#define LL_MPU_ACCESS_OUTER_SHAREABLE      (2U << MPU_RBAR_SH_Pos)
#define LL_MPU_ACCESS_INNER_SHAREABLE      (3U << MPU_RBAR_SH_Pos)
/* Register MPU_RASR (Cortex-M0+) : bit 18 */
#else /* defined(CORE_CM33) */
#define LL_MPU_ACCESS_SHAREABLE            MPU_RASR_S_Msk   /*!< Shareable memory attribute */
#define LL_MPU_ACCESS_NOT_SHAREABLE        0x00U            /*!< Not Shareable memory attribute */
#endif /* defined(CORE_CM33) */
/**
  * @}
  */

/** @defgroup CORTEX_LL_MPU_Region_Permission_Attributes CORTEX LL MPU Region Permission Attributes
  * @{
  */
/* Register MPU_RBAR (Cortex-M33) : bits [2:1] */
#if defined(CORE_CM33)
#define LL_MPU_REGION_PRIV_RW              (0U << MPU_RBAR_AP_Pos)
#define LL_MPU_REGION_ALL_RW               (1U << MPU_RBAR_AP_Pos)
#define LL_MPU_REGION_PRIV_RO              (2U << MPU_RBAR_AP_Pos)
#define LL_MPU_REGION_ALL_RO               (3U << MPU_RBAR_AP_Pos)
/* Register MPU_RASR (Cortex-M0+) : bits [26:24] */
#else /* defined(CORE_CM33) */
#define LL_MPU_REGION_NO_ACCESS            (0x00U << MPU_RASR_AP_Pos) /*!< No access*/
#define LL_MPU_REGION_PRIV_RW              (0x01U << MPU_RASR_AP_Pos) /*!< RW privileged (privileged access only)*/
#define LL_MPU_REGION_PRIV_RW_URO          (0x02U << MPU_RASR_AP_Pos) /*!< RW privileged - RO user (Write in a user program generates a fault) */
#define LL_MPU_REGION_FULL_ACCESS          (0x03U << MPU_RASR_AP_Pos) /*!< RW privileged & user (Full access) */
#define LL_MPU_REGION_PRIV_RO              (0x05U << MPU_RASR_AP_Pos) /*!< RO privileged (privileged read only)*/
#define LL_MPU_REGION_PRIV_RO_URO          (0x06U << MPU_RASR_AP_Pos) /*!< RO privileged & user (read only) */
#endif /* defined(CORE_CM33) */
/**
  * @}
  */

/**************************************************/
/* [MPU/TYPES] M0+ (ARMv6-M) specific definitions */
/**************************************************/
#if defined(CORE_CM0PLUS)
/** @defgroup CORTEX_LL_EC_REGION_SIZE CORTEX LL MPU Region Size
  * @{
  */
/* Register MPU_RASR (Cortex-M0+) */
/* On Cortex-M0+, only values in range [7;31] are allowed. */
/* (see Table B3-29 ("SIZE" field) at page 259 of spec. [ARM DDI0419D] */
#define LL_MPU_REGION_SIZE_256B            (0x07U << MPU_RASR_SIZE_Pos) /*!< 256B Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_512B            (0x08U << MPU_RASR_SIZE_Pos) /*!< 512B Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_1KB             (0x09U << MPU_RASR_SIZE_Pos) /*!< 1KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_2KB             (0x0AU << MPU_RASR_SIZE_Pos) /*!< 2KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_4KB             (0x0BU << MPU_RASR_SIZE_Pos) /*!< 4KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_8KB             (0x0CU << MPU_RASR_SIZE_Pos) /*!< 8KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_16KB            (0x0DU << MPU_RASR_SIZE_Pos) /*!< 16KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_32KB            (0x0EU << MPU_RASR_SIZE_Pos) /*!< 32KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_64KB            (0x0FU << MPU_RASR_SIZE_Pos) /*!< 64KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_128KB           (0x10U << MPU_RASR_SIZE_Pos) /*!< 128KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_256KB           (0x11U << MPU_RASR_SIZE_Pos) /*!< 256KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_512KB           (0x12U << MPU_RASR_SIZE_Pos) /*!< 512KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_1MB             (0x13U << MPU_RASR_SIZE_Pos) /*!< 1MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_2MB             (0x14U << MPU_RASR_SIZE_Pos) /*!< 2MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_4MB             (0x15U << MPU_RASR_SIZE_Pos) /*!< 4MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_8MB             (0x16U << MPU_RASR_SIZE_Pos) /*!< 8MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_16MB            (0x17U << MPU_RASR_SIZE_Pos) /*!< 16MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_32MB            (0x18U << MPU_RASR_SIZE_Pos) /*!< 32MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_64MB            (0x19U << MPU_RASR_SIZE_Pos) /*!< 64MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_128MB           (0x1AU << MPU_RASR_SIZE_Pos) /*!< 128MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_256MB           (0x1BU << MPU_RASR_SIZE_Pos) /*!< 256MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_512MB           (0x1CU << MPU_RASR_SIZE_Pos) /*!< 512MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_1GB             (0x1DU << MPU_RASR_SIZE_Pos) /*!< 1GB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_2GB             (0x1EU << MPU_RASR_SIZE_Pos) /*!< 2GB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_4GB             (0x1FU << MPU_RASR_SIZE_Pos) /*!< 4GB Size of the MPU protection region */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_TEX MPU TEX Level
  * @{
  */
#define LL_MPU_TEX_LEVEL0                  (0x00U << MPU_RASR_TEX_Pos) /*!< b000 for TEX bits */
#define LL_MPU_TEX_LEVEL1                  (0x01U << MPU_RASR_TEX_Pos) /*!< b001 for TEX bits */
#define LL_MPU_TEX_LEVEL2                  (0x02U << MPU_RASR_TEX_Pos) /*!< b010 for TEX bits */
#define LL_MPU_TEX_LEVEL4                  (0x04U << MPU_RASR_TEX_Pos) /*!< b100 for TEX bits */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_CACHEABLE_ACCESS CORTEX LL MPU Cacheable Access
  * @{
  */
/* Register MPU_RASR (Cortex-M0+) : bit 17 */
#define LL_MPU_ACCESS_CACHEABLE            MPU_RASR_C_Msk   /*!< Cacheable memory attribute */
#define LL_MPU_ACCESS_NOT_CACHEABLE        0x00U            /*!< Not Cacheable memory attribute */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_BUFFERABLE_ACCESS CORTEX LL MPU Bufferable Access
  * @{
  */
/* Register MPU_RASR (Cortex-M0+) : bit 16 */
#define LL_MPU_ACCESS_BUFFERABLE           MPU_RASR_B_Msk   /*!< Bufferable memory attribute */
#define LL_MPU_ACCESS_NOT_BUFFERABLE       0x00U            /*!< Not Bufferable memory attribute */
/**
  * @}
  */

#endif /* defined(CORE_CM0PLUS) */

/**************************************************/
/* [MPU/TYPES] M33 (ARMv8-M) specific definitions */
/**************************************************/
#if defined(CORE_CM33)
/** @defgroup CORTEX_LL_EC_REGION_ACCESS CORTEX LL MPU Region Access Attributes
  * @{
  */
/* Register MPU_RBAR (Cortex-M33) : bits [4:0] */
#define LL_MPU_ACCESS_MSK                  (MPU_RBAR_SH_Msk|MPU_RBAR_AP_Msk|MPU_RBAR_XN_Msk)
/**
  * @}
  */

/** @defgroup CORTEX_LL_MPU_Attributes_Index CORTEX LL MPU Memory Attributes Index
  * @{
  */
/* Register MPU_RLAR (Cortex-M33) : bits [3:1] */
#define LL_MPU_ATTRIBUTES_NUMBER0          0U
#define LL_MPU_ATTRIBUTES_NUMBER1          1U
#define LL_MPU_ATTRIBUTES_NUMBER2          2U
#define LL_MPU_ATTRIBUTES_NUMBER3          3U
#define LL_MPU_ATTRIBUTES_NUMBER4          4U
#define LL_MPU_ATTRIBUTES_NUMBER5          5U
#define LL_MPU_ATTRIBUTES_NUMBER6          6U
#define LL_MPU_ATTRIBUTES_NUMBER7          7U
/**
  * @}
  */

/** @defgroup CORTEX_LL_MPU_Attributes CORTEX LL MPU Attributes
  * @{
  */
/* Registers MPU_MAIR0/MPU_MAIR1 (Cortex-M33) : MAIR_ATTR bits [7:0] */
/* - bits [3:2] (bits [7:4] = 0b0000 - bits [1:0] = 0b00) */
#define  LL_MPU_DEVICE_NGNRNE          0x00U  /* Device, noGather, noReorder, noEarly acknowledge. */
#define  LL_MPU_DEVICE_NGNRE           0x04U  /* Device, noGather, noReorder, Early acknowledge.   */
#define  LL_MPU_DEVICE_NGRE            0x08U  /* Device, noGather, Reorder, Early acknowledge.     */
#define  LL_MPU_DEVICE_GRE             0x0CU  /* Device, Gather, Reorder, Early acknowledge.       */
/* - bits [7:6] / bits [3:2] */
#define  LL_MPU_NOT_CACHEABLE          0x4U  /* Normal memory, non-cacheable. */
/* - bit 6 / bit 2 */
#define  LL_MPU_WRITE_THROUGH          0x0U  /* Normal memory, write-through. */
#define  LL_MPU_WRITE_BACK             0x4U  /* Normal memory, write-back.    */
/* - bit 7 / bit 3 */
#define  LL_MPU_TRANSIENT              0x0U  /* Normal memory, transient.     */
#define  LL_MPU_NON_TRANSIENT          0x8U  /* Normal memory, non-transient. */
/* - bits [5:4] / bits [1:0] */
#define  LL_MPU_NO_ALLOCATE            0x0U  /* Normal memory, no allocate.         */
#define  LL_MPU_W_ALLOCATE             0x1U  /* Normal memory, write allocate.      */
#define  LL_MPU_R_ALLOCATE             0x2U  /* Normal memory, read allocate.       */
#define  LL_MPU_RW_ALLOCATE            0x3U  /* Normal memory, read/write allocate. */
/**
  * @}
  */
#endif /* defined(CORE_CM33) */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Functions CORTEX LL Exported Functions
  * @{
  */

/** @defgroup CORTEX_LL_EF_SYSTICK SYSTICK
  * @brief CORTEX SYSTICK LL module driver
  * @{
  */
/**********************************************************/
/* M0+ (ARMv6-M) / M33 (ARMv8-M) SYSTICK common functions */
/**********************************************************/
/* Register SYST_CSR */
/**
  * @brief  This function checks if the Systick counter flag is active or not.
  * @note   It can be used in timeout function on application side.
  * @rmtoll STK_CTRL     COUNTFLAG     LL_SYSTICK_IsActiveCounterFlag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSTICK_IsActiveCounterFlag(void)
{
  return (((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Configures the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     LL_SYSTICK_SetClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_SYSTICK_CLKSOURCE_EXTERNAL
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_SetClkSource(uint32_t Source)
{
  if (Source == LL_SYSTICK_CLKSOURCE_HCLK)
  {
    SET_BIT(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
  }
  else
  {
    CLEAR_BIT(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
  }
}

/**
  * @brief  Get the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     LL_SYSTICK_GetClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSTICK_CLKSOURCE_EXTERNAL
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK
  */
__STATIC_INLINE uint32_t LL_SYSTICK_GetClkSource(void)
{
  return READ_BIT(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
}

/**
  * @brief  Enable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       LL_SYSTICK_EnableIT
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_EnableIT(void)
{
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Disable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       LL_SYSTICK_DisableIT
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_DisableIT(void)
{
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Checks if the SYSTICK interrupt is enabled or disabled.
  * @rmtoll STK_CTRL     TICKINT       LL_SYSTICK_IsEnabledIT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSTICK_IsEnabledIT(void)
{
  return ((READ_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk) == (SysTick_CTRL_TICKINT_Msk)) ? 1UL : 0UL);
}

/******************************************/
/* M33 (ARMv8-M) SYSTICK secure functions */
/******************************************/
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Register SYST_CSR_NS */
/**
  * @brief  This function checks if the non-secure Systick counter flag is active or not.
  * @note   It can be used in timeout function on application side.
  * @rmtoll SYST_CSR_NS     COUNTFLAG     LL_SYSTICK_IsActiveCounterFlag_NS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSTICK_IsActiveCounterFlag_NS(void)
{
  return ((SysTick_NS->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk));
}

/**
  * @brief  Configures the non-secure SysTick clock source
  * @rmtoll SYST_CSR_NS     CLKSOURCE     LL_SYSTICK_SetClkSource_NS
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_SetClkSource_NS(uint32_t Source)
{
  if (Source == LL_SYSTICK_CLKSOURCE_HCLK)
  {
    SET_BIT(SysTick_NS->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
  }
  else
  {
    CLEAR_BIT(SysTick_NS->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
  }
}

/**
  * @brief  Get the non-secure SysTick clock source
  * @rmtoll SYST_CSR_NS     CLKSOURCE     LL_SYSTICK_GetClkSource_NS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK
  */
__STATIC_INLINE uint32_t LL_SYSTICK_GetClkSource_NS(void)
{
  return READ_BIT(SysTick_NS->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
}

/**
  * @brief  Enable non-secure SysTick exception request
  * @rmtoll SYST_CSR_NS     TICKINT       LL_SYSTICK_EnableIT_NS
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_EnableIT_NS(void)
{
  SET_BIT(SysTick_NS->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Disable non-secure SysTick exception request
  * @rmtoll SYST_CSR_NS     TICKINT       LL_SYSTICK_DisableIT_NS
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_DisableIT_NS(void)
{
  CLEAR_BIT(SysTick_NS->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Checks if the SYSTICK interrupt is enabled or disabled.
  * @rmtoll SYST_CSR_NS     TICKINT       LL_SYSTICK_IsEnabledIT_NS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSTICK_IsEnabledIT_NS(void)
{
  return (READ_BIT(SysTick_NS->CTRL, SysTick_CTRL_TICKINT_Msk) == (SysTick_CTRL_TICKINT_Msk));
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_LOW_POWER_MODE CORTEX LL LOW POWER MODE
  * @{
  */
/*****************************************************************/
/* M0+ (ARMv6-M) / M33 (ARMv8-M) LOW POWER MODE common functions */
/*****************************************************************/
/* Register SCB_SCR */
/**
  * @brief  Processor uses sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     LL_LPM_EnableSleep
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableSleep(void)
{
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Processor uses deep sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     LL_LPM_EnableDeepSleep
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableDeepSleep(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Configures sleep-on-exit when returning from Handler mode to Thread mode.
  * @note   Setting this bit to 1 enables an interrupt-driven application
  *         to avoid returning to an empty main application.
  * @rmtoll SCB_SCR      SLEEPONEXIT   LL_LPM_EnableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Do not sleep when returning to Thread mode.
  * @rmtoll SCB_SCR      SLEEPONEXIT   LL_LPM_DisableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void LL_LPM_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Enabled events and all interrupts, including disabled interrupts, can wakeup the
  *         processor.
  * @rmtoll SCB_SCR      SEVEONPEND    LL_LPM_EnableEventOnPend
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableEventOnPend(void)
{
  /* Set SEVONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @brief  Only enabled interrupts or events can wakeup the processor, disabled interrupts are
  *         excluded
  * @rmtoll SCB_SCR      SEVONPEND    LL_LPM_DisableEventOnPend
  * @retval None
  */
__STATIC_INLINE void LL_LPM_DisableEventOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/*************************************************/
/* M33 (ARMv8-M) LOW POWER MODE secure functions */
/*************************************************/
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Register SCB_SCR */
/**
  * @brief  Allow Processor to set deep sleep as its low power mode only in secure state
  * @rmtoll SCB_SCR      SLEEPDEEPS     LL_LPM_SecureDeepSleep
  * @retval None
  */
__STATIC_INLINE void LL_LPM_SecureDeepSleep(void)
{
  /* Set SLEEPDEEPS bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEPS_Msk));
}

/**
  * @brief  Allow Processor to set deep sleep as its low power mode in any state
  * @rmtoll SCB_SCR      SLEEPDEEPS     LL_LPM_UnsecureDeepSleep
  * @retval None
  */
__STATIC_INLINE void LL_LPM_UnsecureDeepSleep(void)
{
  /* Clear SLEEPDEEPS bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEPS_Msk));
}

/* Register SCB_SCR_NS */
/**
  * @brief  Processor uses sleep as its low power mode
  * @rmtoll SCB_SCR_NS      SLEEPDEEP     LL_LPM_EnableSleep_NS
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableSleep_NS(void)
{
  /* Clear SLEEPDEEP bit of non-secure Cortex System Control Register */
  CLEAR_BIT(SCB_NS->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Processor uses deep sleep as its low power mode
  * @rmtoll SCB_SCR_NS      SLEEPDEEP     LL_LPM_EnableDeepSleep_NS
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableDeepSleep_NS(void)
{
  /* Set SLEEPDEEP bit of non-secure Cortex System Control Register */
  SET_BIT(SCB_NS->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

/**
  * @brief  Configures sleep-on-exit when returning from Handler mode to Thread mode.
  * @note   Setting this bit to 1 enables an interrupt-driven application
  *         to avoid returning to an empty main application.
  * @rmtoll SCB_SCR_NS      SLEEPONEXIT   LL_LPM_EnableSleepOnExit_NS
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableSleepOnExit_NS(void)
{
  /* Set SLEEPONEXIT bit of non-secure Cortex System Control Register */
  SET_BIT(SCB_NS->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Do not sleep when returning to Thread mode.
  * @rmtoll SCB_SCR_NS      SLEEPONEXIT   LL_LPM_DisableSleepOnExit_NS
  * @retval None
  */
__STATIC_INLINE void LL_LPM_DisableSleepOnExit_NS(void)
{
  /* Clear SLEEPONEXIT bit of non-secure Cortex System Control Register */
  CLEAR_BIT(SCB_NS->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Enabled events and all interrupts, including disabled interrupts,
  *         can wakeup the processor.
  * @rmtoll SCB_SCR_NS      SEVONPEND    LL_LPM_EnableEventOnPend_NS
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableEventOnPend_NS(void)
{
  /* Set SEVONPEND bit of non-secure Cortex System Control Register */
  SET_BIT(SCB_NS->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @brief  Only enabled interrupts or events can wakeup the processor,
  *         disabled interrupts are excluded
  * @rmtoll SCB_SCR_NS      SEVONPEND    LL_LPM_DisableEventOnPend_NS
  * @retval None
  */
__STATIC_INLINE void LL_LPM_DisableEventOnPend_NS(void)
{
  /* Clear SEVONPEND bit of non-secure Cortex System Control Register */
  CLEAR_BIT(SCB_NS->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */


/**
  * @}
  */
/* On Cortex-M33 only */
#if !defined(CORE_CM0PLUS)
/** @defgroup CORTEX_LL_EF_HANDLER CORTEX LL HANDLER
  * @{
  */
/***********************************/
/* M33 (ARMv8-M) HANDLER functions */
/***********************************/
/* Register SCB_SHCSR */
/**
  * @brief  Enable a fault in System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR    USGFAULTENA     LL_HANDLER_EnableFault\n
  *         SCB_SHCSR    BUSFAULTENA     LL_HANDLER_EnableFault\n
  *         SCB_SHCSR    MEMFAULTENA     LL_HANDLER_EnableFault\n
  *         SCB_SHCSR    SECUREFAULTENA  LL_HANDLER_EnableFault
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref LL_HANDLER_FAULT_USG
  *         @arg @ref LL_HANDLER_FAULT_BUS
  *         @arg @ref LL_HANDLER_FAULT_MEM
  *         @arg @ref LL_HANDLER_FAULT_SECURE (*)
  *
  *         (*) value applicable in secure when the system implements the security.
  * @retval None
  */
__STATIC_INLINE void LL_HANDLER_EnableFault(uint32_t Fault)
{
  /* Enable the system handler fault */
  SET_BIT(SCB->SHCSR, Fault);
}

/**
  * @brief  Disable a fault in System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR    USGFAULTENA     LL_HANDLER_DisableFault\n
  *         SCB_SHCSR    BUSFAULTENA     LL_HANDLER_DisableFault\n
  *         SCB_SHCSR    MEMFAULTENA     LL_HANDLER_DisableFault\n
  *         SCB_SHCSR    SECUREFAULTENA  LL_HANDLER_DisableFault
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref LL_HANDLER_FAULT_USG
  *         @arg @ref LL_HANDLER_FAULT_BUS
  *         @arg @ref LL_HANDLER_FAULT_MEM
  *         @arg @ref LL_HANDLER_FAULT_SECURE (*)
  *
  *         (*) value applicable in secure when the system implements the security.
  * @retval None
  */
__STATIC_INLINE void LL_HANDLER_DisableFault(uint32_t Fault)
{
  /* Disable the system handler fault */
  CLEAR_BIT(SCB->SHCSR, Fault);
}

/*******************************************/
/* M33 (ARMv8-M) HANDLER secure functions */
/*******************************************/
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Register SCB_SHCSR_NS */
/**
  * @brief  Enable a fault in non-secure System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR_NS    USGFAULTENA     LL_HANDLER_EnableFault_NS\n
  *         SCB_SHCSR_NS    BUSFAULTENA     LL_HANDLER_EnableFault_NS\n
  *         SCB_SHCSR_NS    MEMFAULTENA     LL_HANDLER_EnableFault_NS
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref LL_HANDLER_FAULT_USG
  *         @arg @ref LL_HANDLER_FAULT_BUS
  *         @arg @ref LL_HANDLER_FAULT_MEM
  *
  * @retval None
  */
__STATIC_INLINE void LL_HANDLER_EnableFault_NS(uint32_t Fault)
{
  /* Enable the non-secure system handler fault */
  SET_BIT(SCB_NS->SHCSR, Fault);
}

/**
  * @brief  Disable a fault in non-secure System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR_NS    USGFAULTENA     LL_HANDLER_DisableFault_NS\n
  *         SCB_SHCSR_NS    BUSFAULTENA     LL_HANDLER_DisableFault_NS\n
  *         SCB_SHCSR_NS    MEMFAULTENA     LL_HANDLER_DisableFault_NS
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref LL_HANDLER_FAULT_USG
  *         @arg @ref LL_HANDLER_FAULT_BUS
  *         @arg @ref LL_HANDLER_FAULT_MEM
  *
  * @retval None
  */
__STATIC_INLINE void LL_HANDLER_DisableFault_NS(uint32_t Fault)
{
  /* Disable the non-secure system handler fault */
  CLEAR_BIT(SCB_NS->SHCSR, Fault);
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */
#endif /* !defined(CORE_CM0PLUS) */

/** @defgroup CORTEX_LL_EF_MCU_INFO CORTEX LL MCU INFO
  * @{
  */
/***********************************************************/
/* M0+ (ARMv6-M) / M33 (ARMv8-M) MCU INFO common functions */
/***********************************************************/
/* Register SCB_CPUID */
/**
  * @brief  Get Implementer code
  * @rmtoll SCB_CPUID    IMPLEMENTER   LL_CPUID_GetImplementer
  * @retval Value should be equal to 0x41 for ARM
  */
__STATIC_INLINE uint32_t LL_CPUID_GetImplementer(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_IMPLEMENTER_Msk) >> SCB_CPUID_IMPLEMENTER_Pos);
}

/**
  * @brief  Get Variant number (The r value in the rnpn product revision identifier)
  * @rmtoll SCB_CPUID    VARIANT       LL_CPUID_GetVariant
  * @retval Value between 0 and 255
  */
__STATIC_INLINE uint32_t LL_CPUID_GetVariant(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_VARIANT_Msk) >> SCB_CPUID_VARIANT_Pos);
}

/* Cortex-M33 (ARMv8-M) case */
#if !defined(CORE_CM0PLUS)
/**
  * @brief  Get Architecture version
  * @rmtoll SCB_CPUID    ARCHITECTURE  LL_CPUID_GetArchitecture
  * @retval Value should be equal to 0xF for Cortex-M33 ("ARMv8-M with Main Extension")
  */
/* Cortex-M0+ (ARMv6-M) case */
#else /* !defined(CORE_CM0PLUS) */
/**
  * @brief  Get Architecture version
  * @rmtoll SCB_CPUID    ARCHITECTURE  LL_CPUID_GetArchitecture
  * @retval Value should be equal to 0xC for Cortex-M0+ ("ARMv6-M")
  */
#endif /* !defined(CORE_CM0PLUS) */
__STATIC_INLINE uint32_t LL_CPUID_GetArchitecture(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_ARCHITECTURE_Msk) >> SCB_CPUID_ARCHITECTURE_Pos);
}

/* Cortex-M33 case */
#if !defined(CORE_CM0PLUS)
/**
  * @brief  Get Part number
  * @rmtoll SCB_CPUID    PARTNO        LL_CPUID_GetParNo
  * @retval Value should be equal to 0xD21 for Cortex-M33
  */
/* Cortex-M0+ (ARMv6-M) case */
#else /* !defined(CORE_CM0PLUS) */
/**
  * @brief  Get Part number
  * @rmtoll SCB_CPUID    PARTNO        LL_CPUID_GetParNo
  * @retval Value should be equal to 0xC20 for Cortex-M0+
  */
#endif /* !defined(CORE_CM0PLUS) */
__STATIC_INLINE uint32_t LL_CPUID_GetParNo(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos);
}

/**
  * @brief  Get Revision number (The p value in the rnpn product revision identifier, indicates patch release)
  * @rmtoll SCB_CPUID    REVISION      LL_CPUID_GetRevision
  * @retval Value between 0 and 255
  */
__STATIC_INLINE uint32_t LL_CPUID_GetRevision(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos);
}

/*******************************************/
/* M33 (ARMv8-M) MCU INFO secure functions */
/*******************************************/
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Register SCB_CPUID_NS */
/**
  * @brief  Get Implementer code
  * @rmtoll SCB_CPUID_NS    IMPLEMENTER   LL_CPUID_GetImplementer_NS
  * @retval Value should be equal to 0x41 for ARM
  */
__STATIC_INLINE uint32_t LL_CPUID_GetImplementer_NS(void)
{
  return (uint32_t)(READ_BIT(SCB_NS->CPUID, SCB_CPUID_IMPLEMENTER_Msk) >> SCB_CPUID_IMPLEMENTER_Pos);
}

/**
  * @brief  Get Variant number (The r value in the rnpn product revision identifier)
  * @rmtoll SCB_CPUID_NS    VARIANT       LL_CPUID_GetVariant_NS
  * @retval Value between 0 and 255
  */
__STATIC_INLINE uint32_t LL_CPUID_GetVariant_NS(void)
{
  return (uint32_t)(READ_BIT(SCB_NS->CPUID, SCB_CPUID_VARIANT_Msk) >> SCB_CPUID_VARIANT_Pos);
}

/**
  * @brief  Get Architecture version
  * @rmtoll SCB_CPUID_NS    ARCHITECTURE  LL_CPUID_GetArchitecture_NS
  * @retval Value should be equal to 0xF for Cortex-M33 ("ARMv8-M with Main Extension")
  */
__STATIC_INLINE uint32_t LL_CPUID_GetArchitecture_NS(void)
{
  return (uint32_t)(READ_BIT(SCB_NS->CPUID, SCB_CPUID_ARCHITECTURE_Msk) >> SCB_CPUID_ARCHITECTURE_Pos);
}

/**
  * @brief  Get Part number
  * @rmtoll SCB_CPUID_NS    PARTNO        LL_CPUID_GetParNo_NS
  * @retval Value should be equal to 0xD21 for Cortex-M33
  */
__STATIC_INLINE uint32_t LL_CPUID_GetParNo_NS(void)
{
  return (uint32_t)(READ_BIT(SCB_NS->CPUID, SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos);
}

/**
  * @brief  Get Revision number (The p value in the rnpn product revision identifier, indicates patch release)
  * @rmtoll SCB_CPUID_NS    REVISION      LL_CPUID_GetRevision_NS
  * @retval Value between 0 and 255
  */
__STATIC_INLINE uint32_t LL_CPUID_GetRevision_NS(void)
{
  return (uint32_t)(READ_BIT(SCB_NS->CPUID, SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos);
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

#if __MPU_PRESENT
/** @defgroup CORTEX_LL_EF_MPU CORTEX LL MPU
  * @{
  */
/******************************************************/
/* M0+ (ARMv6-M) / M33 (ARMv8-M) MPU common functions */
/******************************************************/
/* Register MPU_CTRL */
/**
  * @brief  Enable MPU with input options
  * @rmtoll MPU_CTRL     ENABLE        LL_MPU_Enable
  * @param  MPU_Control This parameter can be one of the following values:
  *         @arg @ref LL_MPU_CTRL_HFNMI_PRIVDEF_NONE
  *         @arg @ref LL_MPU_CTRL_HARDFAULT_NMI
  *         @arg @ref LL_MPU_CTRL_PRIVILEGED_DEFAULT
  *         @arg @ref LL_MPU_CTRL_HFNMI_PRIVDEF
  * @retval None
  */
__STATIC_INLINE void LL_MPU_Enable(uint32_t MPU_Control)
{
  __DMB(); /* Data Memory Barrier operation to force any outstanding writes to memory before enabling the MPU */

  /* Enable the MPU*/
  MPU->CTRL = MPU_CTRL_ENABLE_Msk | MPU_Control;

  /* Follow ARM recommendation with */
  /* Data Synchronization and Instruction Synchronization Barriers to ensure MPU configuration */
  __DSB(); /* Ensure that the subsequent instruction is executed only after the write to memory */
  __ISB(); /* Flush and refill pipeline with updated MPU configuration settings */
}

/**
  * @brief  Disable MPU
  * @rmtoll MPU_CTRL     ENABLE        LL_MPU_Disable
  * @retval None
  */
__STATIC_INLINE void LL_MPU_Disable(void)
{
  __DMB(); /* Data Memory Barrier operation to force any outstanding writes to memory before disabling the MPU */

  /* Disable MPU */
  WRITE_REG(MPU->CTRL, 0U);

  /* Follow ARM recommendation with */
  /* Data Synchronization and Instruction Synchronization Barriers to ensure MPU configuration */
  __DSB(); /* Ensure that the subsequent instruction is executed only after the write to memory */
  __ISB(); /* Flush and refill pipeline with updated MPU configuration settings */
}

/**
  * @brief  Check if MPU is enabled or not
  * @rmtoll MPU_CTRL     ENABLE        LL_MPU_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MPU_IsEnabled(void)
{
  return ((READ_BIT(MPU->CTRL, MPU_CTRL_ENABLE_Msk) == (MPU_CTRL_ENABLE_Msk)) ? 1UL : 0UL);
}


/****************************************/
/* M0+ (ARMv6-M) MPU specific functions */
/****************************************/
/* Registers MPU_RNR, MPU_RBAR & MPU_RASR */
#if defined(CORE_CM0PLUS)
/**
  * @brief  Configure and enable a MPU region
  * @rmtoll MPU_RNR      REGION        LL_MPU_ConfigRegion\n
  *         MPU_RBAR     REGION        LL_MPU_ConfigRegion\n
  *         MPU_RBAR     VALID         LL_MPU_ConfigRegion\n
  *         MPU_RBAR     ADDR          LL_MPU_ConfigRegion\n
  *         MPU_RASR     XN            LL_MPU_ConfigRegion\n
  *         MPU_RASR     AP            LL_MPU_ConfigRegion\n
  *         MPU_RASR     S             LL_MPU_ConfigRegion\n
  *         MPU_RASR     C             LL_MPU_ConfigRegion\n
  *         MPU_RASR     B             LL_MPU_ConfigRegion\n
  *         MPU_RASR     SIZE          LL_MPU_ConfigRegion\n
  *         MPU_RASR     ENABLE        LL_MPU_ConfigRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  * @param  Address Value of region base address
  * @param  SubRegionDisable Sub-region disable value between Min_Data = 0x00 and Max_Data = 0xFF
  * @param  Attributes This parameter can be a combination of the following values:
  *           or @ref LL_MPU_REGION_SIZE_256B or @ref LL_MPU_REGION_SIZE_512B or @ref LL_MPU_REGION_SIZE_1KB
  *           or @ref LL_MPU_REGION_SIZE_2KB or @ref LL_MPU_REGION_SIZE_4KB or @ref LL_MPU_REGION_SIZE_8KB
  *           or @ref LL_MPU_REGION_SIZE_16KB or @ref LL_MPU_REGION_SIZE_32KB or @ref LL_MPU_REGION_SIZE_64KB
  *           or @ref LL_MPU_REGION_SIZE_128KB or @ref LL_MPU_REGION_SIZE_256KB or @ref LL_MPU_REGION_SIZE_512KB
  *           or @ref LL_MPU_REGION_SIZE_1MB or @ref LL_MPU_REGION_SIZE_2MB or @ref LL_MPU_REGION_SIZE_4MB
  *           or @ref LL_MPU_REGION_SIZE_8MB or @ref LL_MPU_REGION_SIZE_16MB or @ref LL_MPU_REGION_SIZE_32MB
  *           or @ref LL_MPU_REGION_SIZE_64MB or @ref LL_MPU_REGION_SIZE_128MB or @ref LL_MPU_REGION_SIZE_256MB
  *           or @ref LL_MPU_REGION_SIZE_512MB or @ref LL_MPU_REGION_SIZE_1GB or @ref LL_MPU_REGION_SIZE_2GB
  *           or @ref LL_MPU_REGION_SIZE_4GB
  *         @arg @ref LL_MPU_REGION_NO_ACCESS or @ref LL_MPU_REGION_PRIV_RW or @ref LL_MPU_REGION_PRIV_RW_URO
  *           or @ref LL_MPU_REGION_FULL_ACCESS or @ref LL_MPU_REGION_PRIV_RO or @ref LL_MPU_REGION_PRIV_RO_URO
  *         @arg @ref LL_MPU_INSTRUCTION_ACCESS_ENABLE or @ref LL_MPU_INSTRUCTION_ACCESS_DISABLE
  *         @arg @ref LL_MPU_ACCESS_SHAREABLE or @ref LL_MPU_ACCESS_NOT_SHAREABLE
  *         @arg @ref LL_MPU_ACCESS_CACHEABLE or @ref LL_MPU_ACCESS_NOT_CACHEABLE
  *         @arg @ref LL_MPU_ACCESS_BUFFERABLE or @ref LL_MPU_ACCESS_NOT_BUFFERABLE
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigRegion(uint32_t Region, uint32_t SubRegionDisable, uint32_t Address,
                                         uint32_t Attributes)
{
  /* Set region index */
  WRITE_REG(MPU->RNR, Region);
  /* Set region base address */
  WRITE_REG(MPU->RBAR, (Address & 0xFFFFFFE0U));
  /* Set region access attributes and enable region */
  WRITE_REG(MPU->RASR, (MPU_RASR_ENABLE_Msk | Attributes | (SubRegionDisable << MPU_RASR_SRD_Pos)));
}

/**
  * @brief  Enable a MPU region
  * @rmtoll MPU_RASR     ENABLE        LL_MPU_EnableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  * @retval None
  */
__STATIC_INLINE void LL_MPU_EnableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);
  /* Enable the MPU region */
  SET_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

/**
  * @brief  Disable a MPU region
  * @rmtoll MPU_RNR      REGION        LL_MPU_DisableRegion\n
  *         MPU_RASR     ENABLE        LL_MPU_DisableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  * @retval None
  */
__STATIC_INLINE void LL_MPU_DisableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);
  /* Disable the MPU region */
  CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

/****************************************/
/* M33 (ARMv8-M) MPU specific functions */
/****************************************/
#else /* defined(CORE_CM0PLUS) */
/* Registers MPU_RNR / MPU_RLAR */
/**
  * @brief  Enable a MPU region
  * @rmtoll MPU_RNR      REGION        LL_MPU_EnableRegion\n
  *         MPU_RLAR     ENABLE        LL_MPU_EnableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_EnableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Enable the MPU region */
  SET_BIT(MPU->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Disable a MPU region
  * @rmtoll MPU_RNR      REGION        LL_MPU_DisableRegion\n
  *         MPU_RLAR     ENABLE        LL_MPU_DisableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_DisableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Disable the MPU region */
  CLEAR_BIT(MPU->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Check if MPU region is enabled or not
  * @rmtoll MPU_RNR      REGION        LL_MPU_IsEnabled_Region\n
  *         MPU_RLAR     ENABLE        LL_MPU_IsEnabled_Region
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MPU_IsEnabled_Region(uint32_t Region)
{
  /* Set region index */
  WRITE_REG(MPU->RNR, Region);
  /* Return region enable status */
  return ((READ_BIT(MPU->RLAR, MPU_RLAR_EN_Msk) == (MPU_RLAR_EN_Msk)) ? 1UL : 0UL);
}

/* Registers MPU_RNR, MPU_RBAR & MPU_RLAR */
/**
  * @brief  Configure and enable a MPU region
  * @rmtoll MPU_RNR      REGION        LL_MPU_ConfigRegion\n
  *         MPU_RBAR     BASE          LL_MPU_ConfigRegion\n
  *         MPU_RLAR     LIMIT          LL_MPU_ConfigRegion\n
  *         MPU_RBAR     XN            LL_MPU_ConfigRegion\n
  *         MPU_RBAR     AP            LL_MPU_ConfigRegion\n
  *         MPU_RBAR     SH            LL_MPU_ConfigRegion\n
  *         MPU_RLAR     EN            LL_MPU_ConfigRegion\n
  *         MPU_RLAR     AttrIndx      LL_MPU_ConfigRegion\n
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  Attributes This parameter can be a combination of the following values:
  *         @arg @ref LL_MPU_INSTRUCTION_ACCESS_ENABLE or @ref LL_MPU_INSTRUCTION_ACCESS_DISABLE
  *         @arg @ref LL_MPU_ACCESS_NOT_SHAREABLE or @ref LL_MPU_ACCESS_OUTER_SHAREABLE
  *              or @ref LL_MPU_ACCESS_INNER_SHAREABLE
  *         @arg @ref LL_MPU_REGION_PRIV_RW or @ref LL_MPU_REGION_ALL_RW or @ref LL_MPU_REGION_PRIV_RO
  *              or @ref LL_MPU_REGION_ALL_RO
  * @param  AttrIndx This parameter can be one of the following values:
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER0
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER1
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER2
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER3
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER4
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER5
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER6
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER7
  * @param  BaseAddress Value of region base address
  * @param  LimitAddress Value of region limit address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigRegion(uint32_t Region, uint32_t Attributes, uint32_t AttrIndx, uint32_t BaseAddress,
                                         uint32_t LimitAddress)
{
  /* Set region index */
  WRITE_REG(MPU->RNR, Region);

  /* Set region base address and region access attributes */
  WRITE_REG(MPU->RBAR, ((BaseAddress & MPU_RBAR_BASE_Msk) | Attributes));

  /* Set region limit address, memory attributes index and enable region */
  WRITE_REG(MPU->RLAR, ((LimitAddress & MPU_RLAR_LIMIT_Msk) | AttrIndx | MPU_RLAR_EN_Msk));
}

/**
  * @brief  Configure a MPU region address range
  * @rmtoll MPU_RNR      REGION        LL_MPU_ConfigRegionAddress\n
  *         MPU_RBAR     BASE          LL_MPU_ConfigRegionAddress\n
  *         MPU_RLAR     LIMIT         LL_MPU_ConfigRegionAddress
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  BaseAddress Value of region base address
  * @param  LimitAddress Value of region limit address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigRegionAddress(uint32_t Region, uint32_t BaseAddress, uint32_t LimitAddress)
{
  /* Set region number */
  WRITE_REG(MPU->RNR, Region);

  /* Modify region base address */
  MODIFY_REG(MPU->RBAR, MPU_RBAR_BASE_Msk, (BaseAddress & MPU_RBAR_BASE_Msk));

  /* Modify region limit address */
  MODIFY_REG(MPU->RLAR, MPU_RLAR_LIMIT_Msk, (LimitAddress & MPU_RLAR_LIMIT_Msk));
}

/* Registers MPU_RNR & MPU_RBAR */
/**
  * @brief  Configure one MPU region base address
  * @rmtoll MPU_RNR      REGION        LL_MPU_SetRegionBaseAddress\n
  *         MPU_RBAR     BASE          LL_MPU_SetRegionBaseAddress
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  BaseAddress Value of region base address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_SetRegionBaseAddress(uint32_t Region, uint32_t BaseAddress)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Set region base address */
  MODIFY_REG(MPU->RBAR, MPU_RBAR_BASE_Msk, (BaseAddress & MPU_RBAR_BASE_Msk));
}

/**
  * @brief  Get a MPU region base address
  * @rmtoll MPU_RNR      REGION        LL_MPU_GetRegionBaseAddress\n
  *         MPU_RBAR     BASE          LL_MPU_GetRegionBaseAddress
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval 32-bit base address of selected region
  */
__STATIC_INLINE uint32_t LL_MPU_GetRegionBaseAddress(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Return region base address */
  return (READ_REG(MPU->RBAR & MPU_RBAR_BASE_Msk));
}

/**
  * @brief  Configure a MPU region access attributes
  * @rmtoll MPU_RNR      REGION        LL_MPU_SetRegionAccess\n
  *         MPU_RBAR     XN            LL_MPU_SetRegionAccess\n
  *         MPU_RBAR     AP            LL_MPU_SetRegionAccess\n
  *         MPU_RBAR     SH            LL_MPU_SetRegionAccess
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  Attributes This parameter can be a combination of the following values:
  *         @arg @ref LL_MPU_INSTRUCTION_ACCESS_ENABLE or @ref LL_MPU_INSTRUCTION_ACCESS_DISABLE
  *         @arg @ref LL_MPU_ACCESS_NOT_SHAREABLE or @ref LL_MPU_ACCESS_OUTER_SHAREABLE
  *              or @ref LL_MPU_ACCESS_INNER_SHAREABLE
  *         @arg @ref LL_MPU_REGION_PRIV_RW or @ref LL_MPU_REGION_ALL_RW or @ref LL_MPU_REGION_PRIV_RO
  *              or @ref LL_MPU_REGION_ALL_RO
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_SetRegionAccess(uint32_t Region, uint32_t Attributes)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);
  /* Set region access attributes */
  MODIFY_REG(MPU->RBAR, LL_MPU_ACCESS_MSK, (Attributes & LL_MPU_ACCESS_MSK));
}

/**
  * @brief  Get a MPU region access attributes
  * @rmtoll MPU_RNR      REGION        LL_MPU_GetRegionAccess\n
  *         MPU_RBAR     XN            LL_MPU_GetRegionAccess\n
  *         MPU_RBAR     AP            LL_MPU_GetRegionAccess\n
  *         MPU_RBAR     SH            LL_MPU_GetRegionAccess
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval 5-bit access attributes of selected region
  */
__STATIC_INLINE uint32_t LL_MPU_GetRegionAccess(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Return region access attributes */
  return (READ_REG(MPU->RBAR & (MPU_RBAR_XN_Msk | MPU_RBAR_AP_Msk | MPU_RBAR_SH_Msk)));
}

/* Registers MPU_RNR & MPU_RLAR */
/**
  * @brief  Configure a MPU region limit address
  * @rmtoll MPU_RNR      REGION        LL_MPU_SetRegionLimitAddress\n
  *         MPU_RLAR     LIMIT         LL_MPU_SetRegionLimitAddress
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  LimitAddress Value of region limit address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_SetRegionLimitAddress(uint32_t Region, uint32_t LimitAddress)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Set region limit address */
  MODIFY_REG(MPU->RLAR, MPU_RLAR_LIMIT_Msk, (LimitAddress & MPU_RLAR_LIMIT_Msk));
}

/**
  * @brief  Get a MPU region limit address
  * @rmtoll MPU_RNR      REGION        LL_MPU_GetRegionLimitAddress\n
  *         MPU_RLAR     LIMIT         LL_MPU_GetRegionLimitAddress
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval 32-bit limit address of selected region
  */
__STATIC_INLINE uint32_t LL_MPU_GetRegionLimitAddress(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Return region limit address */
  return (READ_REG(MPU->RLAR & MPU_RLAR_LIMIT_Msk));
}

/* Registers MPU_MAIR0 & MPU_MAIR1 */
/**
  * @brief  Configure a MPU attributes index
  * @rmtoll MPU_MAIR0      Attribute       LL_MPU_ConfigAttributes\n
  *         MPU_MAIR1      Attribute       LL_MPU_ConfigAttributes\n
  * @param  AttIndex This parameter can be one of the following values:
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER0
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER1
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER2
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER3
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER4
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER5
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER6
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER7
  * @param  Attributes This parameter can be a combination of @ref CORTEX_LL_MPU_Attributes
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigAttributes(uint32_t AttIndex, uint32_t  Attributes)
{
  /* When selected index is in range [0;3] */
  if (AttIndex < LL_MPU_ATTRIBUTES_NUMBER4)
  {
    /* Modify Attr<i> field of MPU_MAIR0 accordingly */
    MODIFY_REG(MPU->MAIR0, (0xFFU << (AttIndex * 8U)), (Attributes << (AttIndex * 8U)));
  }
  /* When selected index is in range [4;7] */
  else
  {
    /* Modify Attr<i> field of MPU_MAIR1 accordingly */
    MODIFY_REG(MPU->MAIR1, (0xFFU << ((AttIndex - 4U) * 8U)), (Attributes << ((AttIndex - 4U) * 8U)));
  }
}
#endif /* defined(CORE_CM0PLUS) */

/*******************************************/
/* M33 secure functions for non-secure MPU */
/*******************************************/
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Register MPU_CTRL_NS */
/**
  * @brief  Enable non-secure MPU with input options
  * @rmtoll MPU_CTRL_NS     ENABLE        LL_MPU_Enable_NS
  * @param  MPU_Control This parameter can be one of the following values:
  *         @arg @ref LL_MPU_CTRL_HFNMI_PRIVDEF_NONE
  *         @arg @ref LL_MPU_CTRL_HARDFAULT_NMI
  *         @arg @ref LL_MPU_CTRL_PRIVILEGED_DEFAULT
  *         @arg @ref LL_MPU_CTRL_HFNMI_PRIVDEF
  * @retval None
  */
__STATIC_INLINE void LL_MPU_Enable_NS(uint32_t MPU_Control)
{
  __DMB(); /* Data Memory Barrier operation to force any outstanding writes to memory before enabling the MPU */

  /* Enable the MPU */
  MPU_NS->CTRL = MPU_CTRL_ENABLE_Msk | MPU_Control;

  /* Follow ARM recommendation with */
  /* Data Synchronization and Instruction Synchronization Barriers to ensure MPU configuration */
  __DSB(); /* Ensure that the subsequent instruction is executed only after the write to memory */
  __ISB(); /* Flush and refill pipeline with updated MPU configuration settings */
}

/**
  * @brief  Disable the non-secure MPU
  * @rmtoll MPU_CTRL_NS     ENABLE        LL_MPU_Disable_NS
  * @retval None
  */
__STATIC_INLINE void LL_MPU_Disable_NS(void)
{
  __DMB(); /* Data Memory Barrier operation to force any outstanding writes to memory before disabling the MPU */

  /* Disable MPU */
  WRITE_REG(MPU_NS->CTRL, 0U);

  /* Follow ARM recommendation with */
  /* Data Synchronization and Instruction Synchronization Barriers to ensure MPU configuration */
  __DSB(); /* Ensure that the subsequent instruction is executed only after the write to memory */
  __ISB(); /* Flush and refill pipeline with updated MPU configuration settings */
}

/**
  * @brief  Check if non-secure MPU is enabled or not
  * @rmtoll MPU_CTRL_NS     ENABLE        LL_MPU_IsEnabled_NS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MPU_IsEnabled_NS(void)
{
  return ((READ_BIT(MPU_NS->CTRL, MPU_CTRL_ENABLE_Msk) == (MPU_CTRL_ENABLE_Msk)) ? 1UL : 0UL);
}

/* Registers MPU_RNR_NS / MPU_RLAR_NS */
/**
  * @brief  Enable a non-secure MPU region
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_EnableRegion_NS\n
  *         MPU_RLAR_NS     ENABLE        LL_MPU_EnableRegion_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_EnableRegion_NS(uint32_t Region)
{
  /* Set region number */
  WRITE_REG(MPU_NS->RNR, Region);
  /* Enable the non-secure MPU region */
  SET_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Disable a non-secure MPU region
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_DisableRegion_NS\n
  *         MPU_RLAR_NS     ENABLE        LL_MPU_DisableRegion_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_DisableRegion_NS(uint32_t Region)
{
  /* Set region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Disable the non-secure MPU region */
  CLEAR_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk);
}

/**
  * @brief  Check if non-secure MPU region is enabled or not
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_IsEnabled_Region_NS\n
  *         MPU_RLAR_NS     ENABLE        LL_MPU_IsEnabled_Region_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MPU_IsEnabled_Region_NS(uint32_t Region)
{
  /* Set region index */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Return non-secure MPU region status */
  return ((READ_BIT(MPU_NS->RLAR, MPU_RLAR_EN_Msk) == (MPU_RLAR_EN_Msk)) ? 1UL : 0UL);
}

/* Registers MPU_RNR_NS, MPU_RBAR_NS & MPU_RLAR_NS */
/**
  * @brief  Configure and enable a non-secure MPU region
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_ConfigRegion_NS\n
  *         MPU_RBAR_NS     BASE          LL_MPU_ConfigRegion_NS\n
  *         MPU_RLAR_NS     LIMIT         LL_MPU_ConfigRegion_NS\n
  *         MPU_RBAR_NS     XN            LL_MPU_ConfigRegion_NS\n
  *         MPU_RBAR_NS     AP            LL_MPU_ConfigRegion_NS\n
  *         MPU_RBAR_NS     SH            LL_MPU_ConfigRegion_NS\n
  *         MPU_RLAR_NS     EN            LL_MPU_ConfigRegion_NS\n
  *         MPU_RLAR_NS     AttrIndx      LL_MPU_ConfigRegion_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  Attributes This parameter can be a combination of the following values:
  *         @arg @ref LL_MPU_INSTRUCTION_ACCESS_ENABLE or @ref LL_MPU_INSTRUCTION_ACCESS_DISABLE
  *         @arg @ref LL_MPU_ACCESS_NOT_SHAREABLE or @ref LL_MPU_ACCESS_OUTER_SHAREABLE
  *              or @ref LL_MPU_ACCESS_INNER_SHAREABLE
  *         @arg @ref LL_MPU_REGION_PRIV_RW or @ref LL_MPU_REGION_ALL_RW or @ref LL_MPU_REGION_PRIV_RO
  *              or @ref LL_MPU_REGION_ALL_RO
  * @param  AttrIndx This parameter can be one of the following values:
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER0
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER1
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER2
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER3
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER4
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER5
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER6
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER7
  * @param  BaseAddress Value of region base address
  * @param  LimitAddress Value of region limit address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigRegion_NS(uint32_t Region, uint32_t Attributes, uint32_t AttrIndx,
                                            uint32_t BaseAddress, uint32_t LimitAddress)
{
  /* Set Region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Set region base address and region access attributes */
  WRITE_REG(MPU_NS->RBAR, ((BaseAddress & MPU_RBAR_BASE_Msk) | Attributes));

  /* Set region limit address, memory attributes index and enable region */
  WRITE_REG(MPU_NS->RLAR, ((LimitAddress & MPU_RLAR_LIMIT_Msk) | AttrIndx | MPU_RLAR_EN_Msk));
}

/**
  * @brief  Configure a non-secure MPU region address range
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_ConfigRegionAddress_NS\n
  *         MPU_RBAR_NS     BASE          LL_MPU_ConfigRegionAddress_NS\n
  *         MPU_RLAR_NS     LIMIT         LL_MPU_ConfigRegionAddress_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  BaseAddress Value of region base address
  * @param  LimitAddress Value of region limit address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigRegionAddress_NS(uint32_t Region, uint32_t BaseAddress, uint32_t LimitAddress)
{
  /* Set region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Modify non-secure region base address */
  MODIFY_REG(MPU_NS->RBAR, MPU_RBAR_BASE_Msk, (BaseAddress & MPU_RBAR_BASE_Msk));

  /* Modify non-secure region limit address */
  MODIFY_REG(MPU_NS->RLAR, MPU_RLAR_LIMIT_Msk, (LimitAddress & MPU_RLAR_LIMIT_Msk));
}

/* Registers MPU_RNR_NS & MPU_RBAR_NS */
/**
  * @brief  Configure a non-secure MPU region base address
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_SetRegionBaseAddress_NS\n
  *         MPU_RBAR_NS     BASE          LL_MPU_SetRegionBaseAddress_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  BaseAddress Value of region base address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_SetRegionBaseAddress_NS(uint32_t Region, uint32_t BaseAddress)
{
  /* Set non-secure region number */
  WRITE_REG(MPU_NS->RNR, Region);
  /* Set non-secure region base address */
  MODIFY_REG(MPU_NS->RBAR, MPU_RBAR_BASE_Msk, (BaseAddress & MPU_RBAR_BASE_Msk));
}

/**
  * @brief  Get one non-secure MPU region base address
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_GetRegionBaseAddress_NS\n
  *         MPU_RBAR_NS     BASE          LL_MPU_GetRegionBaseAddress_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval 32-bit base address of selected non-secure region
  */
__STATIC_INLINE uint32_t LL_MPU_GetRegionBaseAddress_NS(uint32_t Region)
{
  /* Set non-secure region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Return non-secure region base address */
  return (READ_REG(MPU_NS->RBAR & MPU_RBAR_BASE_Msk));
}

/**
  * @brief  Configure a non-secure MPU region access attributes
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_SetRegionAccess_NS\n
  *         MPU_RBAR_NS     XN            LL_MPU_SetRegionAccess_NS\n
  *         MPU_RBAR_NS     AP            LL_MPU_SetRegionAccess_NS\n
  *         MPU_RBAR_NS     SH            LL_MPU_SetRegionAccess_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  Attributes This parameter can be a combination of the following values:
  *         @arg @ref LL_MPU_INSTRUCTION_ACCESS_ENABLE or @ref LL_MPU_INSTRUCTION_ACCESS_DISABLE
  *         @arg @ref LL_MPU_ACCESS_NOT_SHAREABLE or @ref LL_MPU_ACCESS_OUTER_SHAREABLE
  *              or @ref LL_MPU_ACCESS_INNER_SHAREABLE
  *         @arg @ref LL_MPU_REGION_PRIV_RW or @ref LL_MPU_REGION_ALL_RW or @ref LL_MPU_REGION_PRIV_RO
  *              or @ref LL_MPU_REGION_ALL_RO
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_SetRegionAccess_NS(uint32_t Region, uint32_t Attributes)
{
  /* Set non-secure region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Modify non-secure region attributes */
  MODIFY_REG(MPU_NS->RBAR, LL_MPU_ACCESS_MSK, (Attributes & LL_MPU_ACCESS_MSK));
}

/**
  * @brief  Get a non-secure MPU region access attributes
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_GetRegionAccess_NS\n
  *         MPU_RBAR_NS     XN            LL_MPU_GetRegionAccess_NS\n
  *         MPU_RBAR_NS     AP            LL_MPU_GetRegionAccess_NS\n
  *         MPU_RBAR_NS     SH            LL_MPU_GetRegionAccess_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval 5-bit access attributes of selected non-secure region
  */
__STATIC_INLINE uint32_t LL_MPU_GetRegionAccess_NS(uint32_t Region)
{
  /* Set non-secure region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Return non-secure region access attributes */
  return (READ_REG(MPU_NS->RBAR & (MPU_RBAR_XN_Msk | MPU_RBAR_AP_Msk | MPU_RBAR_SH_Msk)));
}

/* Registers MPU_RNR_NS & MPU_RLAR_NS */
/**
  * @brief  Configure one MPU region limit address
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_SetRegionLimitAddress_NS\n
  *         MPU_RLAR_NS     LIMIT         LL_MPU_SetRegionLimitAddress_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  LimitAddress Value of region limit address
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval None
  */
__STATIC_INLINE void LL_MPU_SetRegionLimitAddress_NS(uint32_t Region, uint32_t LimitAddress)
{
  /* Set non-secure region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Set region limit address */
  MODIFY_REG(MPU_NS->RLAR, MPU_RLAR_LIMIT_Msk, (LimitAddress & MPU_RLAR_LIMIT_Msk));
}

/**
  * @brief  Get a non-secure MPU region limit address
  * @rmtoll MPU_RNR_NS      REGION        LL_MPU_GetRegionLimitAddress_NS\n
  *         MPU_RLAR_NS     LIMIT         LL_MPU_GetRegionLimitAddress_NS
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @note   MP2 Cortex-M33 supports 16 secure and 16 non-secure regions.
  * @retval 32-bit limit address of selected non-secure region
  */
__STATIC_INLINE uint32_t LL_MPU_GetRegionLimitAddress_NS(uint32_t Region)
{
  /* Set non-secure region number */
  WRITE_REG(MPU_NS->RNR, Region);

  /* Return non-secure region limit address */
  return (READ_REG(MPU_NS->RLAR & MPU_RLAR_LIMIT_Msk));
}

/* Registers MPU_MAIR0_NS & MPU_MAIR1_NS */
/**
  * @brief  Configure a non-secure MPU attributes index
  * @rmtoll MPU_MAIR0      Attribute       LL_MPU_ConfigAttributes_NS\n
  *         MPU_MAIR1      Attribute       LL_MPU_ConfigAttributes_NS\n
  * @param  AttIndex This parameter can be one of the following values:
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER0
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER1
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER2
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER3
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER4
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER5
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER6
  *         @arg @ref LL_MPU_ATTRIBUTES_NUMBER7
  * @param  Attributes This parameter can be a combination of @ref CORTEX_LL_MPU_Attributes
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigAttributes_NS(uint32_t AttIndex, uint32_t  Attributes)
{
  /* When selected index is in range [0;3] */
  if (AttIndex < LL_MPU_ATTRIBUTES_NUMBER4)
  {
    /* Modify Attr<i> field of MPU_MAIR0_NS accordingly */
    MODIFY_REG(MPU_NS->MAIR0, (0xFFU << (AttIndex * 8U)), (Attributes << (AttIndex * 8U)));
  }
  /* When selected index is in range [4;7] */
  else
  {
    /* Modify Attr<i> field of MPU_MAIR1_NS accordingly */
    MODIFY_REG(MPU_NS->MAIR1, (0xFFU << ((AttIndex - 4U) * 8U)), (Attributes << ((AttIndex - 4U) * 8U)));
  }
}
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

#endif /* __MPU_PRESENT */
/**
  * @}
  */

/**
  * @}
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

#endif /* __STM32MP2xx_LL_CORTEX_H */
