/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_cortex.h
  * @author  MCD Application Team
  * @brief   Header file of CORTEX HAL module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP2xx_HAL_CORTEX_H
#define __STM32MP2xx_HAL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"


/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Types Cortex Exported Types
  * @{
  */

#if (__MPU_PRESENT == 1)
/** @defgroup CORTEX_MPU_Region_Initialization_Structure_definition MPU Region Initialization Structure Definition
  * @brief  MPU Region initialization structure
  * @{
  */
/* [MPU/TYPES] M0+ (ARMv6-M) specific definitions */
#ifdef CORE_CM0PLUS
typedef struct
{
  uint8_t                Enable;                /*!< Specifies the status of the region.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Enable   */
  uint8_t                Number;                /*!< Specifies the number of the region to protect.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Number   */
  uint32_t               BaseAddress;           /*!< Specifies the base address of the region to protect.             */
  uint8_t                Size;                  /*!< Specifies the size of the region to protect.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Size     */
  uint8_t                SubRegionDisable;      /*!< Specifies the number of the subregion protection to disable.
                                                     This parameter must be a number between Min_Data = 0x00 and
                                                     Max_Data = 0xFF                                                  */
  uint8_t                TypeExtField;          /*!< Specifies the TEX field level.
                                                     This parameter can be a value of @ref CORTEX_MPU_TEX_Levels      */
  uint8_t                AccessPermission;      /*!< Specifies the region access permission type.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Region_Permission_Attributes                     */
  uint8_t                DisableExec;           /*!< Specifies the instruction access status.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Instruction_Access                               */
  uint8_t                IsShareable;           /*!< Specifies the shareability status of the protected region.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Access_Shareable                                 */
  uint8_t                IsCacheable;           /*!< Specifies the cacheable status of the region protected.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Access_Cacheable                                 */
  uint8_t                IsBufferable;          /*!< Specifies the bufferable status of the protected region.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Access_Bufferable                                */
} MPU_Region_InitTypeDef;
#endif /* CORE_CM0PLUS */
/* [MPU/TYPES] M33 (ARMv8-M) specific definitions */
#ifdef CORE_CM33
typedef struct
{
  uint8_t                Enable;                /*!< Specifies the status of the region.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Enable   */
  uint8_t                Number;                /*!< Specifies the number of the region to protect.
                                                     This parameter can be a value of @ref CORTEX_MPU_Region_Number   */
  uint32_t               BaseAddress;           /*!< Specifies the base address of the region to protect.             */
  uint32_t               LimitAddress;          /*!< Specifies the limit address of the region to protect.            */
  uint8_t                AttributesIndex;       /*!< Specifies the memory attributes index.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Attributes_Number                                */
  uint8_t                AccessPermission;      /*!< Specifies the region access permission type.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Region_Permission_Attributes                     */
  uint8_t                DisableExec;           /*!< Specifies the instruction access status.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Instruction_Access                               */
  uint8_t                IsShareable;           /*!< Specifies the shareability status of the protected region.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Access_Shareable                                 */
} MPU_Region_InitTypeDef;
/**
  * @}
  */
/** @defgroup CORTEX_MPU_Attributes_Initialization_Structure_definition Memory Attributes Structure Definition
  * @{
  */
typedef struct
{
  uint8_t                Number;                /*!< Specifies the index of the memory attributes to be configured.
                                                     This parameter can be a value of
                                                     @ref CORTEX_MPU_Attributes_Number                                */

  uint8_t                Attributes;            /*!< Specifies the memory attributes value.
                                                     This parameter must be a value between Min_Data = 0x0
                                                     and Max_Data = 0xFF                                              */

} MPU_Attributes_InitTypeDef;
/**
  * @}
  */
#endif /* CORE_CM33 */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup CORTEX_Exported_Constants CORTEX Exported Constants
  * @{
  */

#ifdef CORE_CM33
/* [NVIC/CONSTANTS] M33 (ARMv8-M) specific definitions */
/** @defgroup CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group
  * @{
  */
/* WARNING ! Historical define name NVIC_PRIORITYGROUP_* is confusing */
/*           according to ARM specifications, because PRIORITYGROUP_0 */
/*           seems to stand for "Priority Grouping" equal 0           */
/*           whereas it means "Priority Grouping" equal 7 and number  */
/*           of "Group Priority" bits equal 0 ! */
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority
                                                                 4 bits for sub-priority  (NVIC_PRIO_BITS=4) */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority
                                                                 3 bits for sub-priority  (NVIC_PRIO_BITS=4) */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority
                                                                 2 bits for sub-priority  (NVIC_PRIO_BITS=4) */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority
                                                                 1 bit  for sub-priority  (NVIC_PRIO_BITS=4) */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority
                                                                 0 bit  for sub-priority  (NVIC_PRIO_BITS=4) */
/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup CORTEX_Interrupt_Security_State CORTEX Interrupt Security State
  * @{
  */
#define NVIC_SECURE_INTERRUPT    ((uint32_t)0x00000000)
#define NVIC_NONSECURE_INTERRUPT ((uint32_t)0x00000001)
/**
  * @}
  */
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

#endif /* CORE_CM33 */

/** @defgroup CORTEX_SysTick_clock_source CORTEX SysTick clock source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8     0x0U /*!< AHB clock divided by 8 selected as SysTick clock source */
#define SYSTICK_CLKSOURCE_HCLK          0x4U /*!< AHB clock selected as SysTick clock source */
/**
  * @}
  */

#if (__MPU_PRESENT == 1)
/* [MPU/CONSTANTS] M0+ (ARMv6-M) / M33 (ARMv8-M) common definitions */
/** @defgroup CORTEX_MPU_HFNMI_PRIVDEF_Control CORTEX MPU HFNMI and PRIVILEGED Access control
  * @{
  */
#define  MPU_HFNMI_PRIVDEF_NONE           0x00000000U
#define  MPU_HARDFAULT_NMI                (MPU_CTRL_HFNMIENA_Msk)
#define  MPU_PRIVILEGED_DEFAULT           (MPU_CTRL_PRIVDEFENA_Msk)
#define  MPU_HFNMI_PRIVDEF                (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Enable CORTEX MPU Region Enable
  * @{
  */
#define  MPU_REGION_ENABLE     ((uint8_t)0x01)
#define  MPU_REGION_DISABLE    ((uint8_t)0x00)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Instruction_Access CORTEX MPU Instruction Access
  * @{
  */
#define  MPU_INSTRUCTION_ACCESS_ENABLE      ((uint8_t)0x00)
#define  MPU_INSTRUCTION_ACCESS_DISABLE     ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Number CORTEX MPU Region Number
  * @{
  */
#define  MPU_REGION_NUMBER0    ((uint8_t)0x00)
#define  MPU_REGION_NUMBER1    ((uint8_t)0x01)
#define  MPU_REGION_NUMBER2    ((uint8_t)0x02)
#define  MPU_REGION_NUMBER3    ((uint8_t)0x03)
#define  MPU_REGION_NUMBER4    ((uint8_t)0x04)
#define  MPU_REGION_NUMBER5    ((uint8_t)0x05)
#define  MPU_REGION_NUMBER6    ((uint8_t)0x06)
#define  MPU_REGION_NUMBER7    ((uint8_t)0x07)
#ifdef CORE_CM33
#define  MPU_REGION_NUMBER8    ((uint8_t)0x08)
#define  MPU_REGION_NUMBER9    ((uint8_t)0x09)
#define  MPU_REGION_NUMBER10   ((uint8_t)0x0A)
#define  MPU_REGION_NUMBER11   ((uint8_t)0x0B)
#define  MPU_REGION_NUMBER12   ((uint8_t)0x0C)
#define  MPU_REGION_NUMBER13   ((uint8_t)0x0D)
#define  MPU_REGION_NUMBER14   ((uint8_t)0x0E)
#define  MPU_REGION_NUMBER15   ((uint8_t)0x0F)
#endif /* CORE_CM33 */
/**
  * @}
  */

/* [MPU/CONSTANTS] M0+ (ARMv6-M) specific definitions */
#ifdef CORE_CM0PLUS
/** @defgroup CORTEX_MPU_Access_Shareable CORTEX MPU Instruction Access Shareable
  * @{
  */
#define  MPU_ACCESS_NOT_SHAREABLE    ((uint8_t)0x00)
#define  MPU_ACCESS_SHAREABLE        ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Cacheable CORTEX MPU Instruction Access Cacheable
  * @{
  */
#define  MPU_ACCESS_NOT_CACHEABLE     ((uint8_t)0x00)
#define  MPU_ACCESS_CACHEABLE         ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Bufferable CORTEX MPU Instruction Access Bufferable
  * @{
  */
#define  MPU_ACCESS_NOT_BUFFERABLE     ((uint8_t)0x00)
#define  MPU_ACCESS_BUFFERABLE         ((uint8_t)0x01)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_TEX_Levels CORTEX MPU TEX Levels
  * @{
  */
#define  MPU_TEX_LEVEL0                ((uint8_t)0x00)
#define  MPU_TEX_LEVEL1                ((uint8_t)0x01)
#define  MPU_TEX_LEVEL2                ((uint8_t)0x02)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Size CORTEX MPU Region Size
  * @{
  */
/* WARNING ! Only values in range [7;31] are allowed, as specified */
/*           by Table B3-29 ("SIZE" field) in spec. [ARM DDI0419D] */
/*           (at page 259).                                        */
#define   MPU_REGION_SIZE_256B     ((uint8_t)0x07)
#define   MPU_REGION_SIZE_512B     ((uint8_t)0x08)
#define   MPU_REGION_SIZE_1KB      ((uint8_t)0x09)
#define   MPU_REGION_SIZE_2KB      ((uint8_t)0x0A)
#define   MPU_REGION_SIZE_4KB      ((uint8_t)0x0B)
#define   MPU_REGION_SIZE_8KB      ((uint8_t)0x0C)
#define   MPU_REGION_SIZE_16KB     ((uint8_t)0x0D)
#define   MPU_REGION_SIZE_32KB     ((uint8_t)0x0E)
#define   MPU_REGION_SIZE_64KB     ((uint8_t)0x0F)
#define   MPU_REGION_SIZE_128KB    ((uint8_t)0x10)
#define   MPU_REGION_SIZE_256KB    ((uint8_t)0x11)
#define   MPU_REGION_SIZE_512KB    ((uint8_t)0x12)
#define   MPU_REGION_SIZE_1MB      ((uint8_t)0x13)
#define   MPU_REGION_SIZE_2MB      ((uint8_t)0x14)
#define   MPU_REGION_SIZE_4MB      ((uint8_t)0x15)
#define   MPU_REGION_SIZE_8MB      ((uint8_t)0x16)
#define   MPU_REGION_SIZE_16MB     ((uint8_t)0x17)
#define   MPU_REGION_SIZE_32MB     ((uint8_t)0x18)
#define   MPU_REGION_SIZE_64MB     ((uint8_t)0x19)
#define   MPU_REGION_SIZE_128MB    ((uint8_t)0x1A)
#define   MPU_REGION_SIZE_256MB    ((uint8_t)0x1B)
#define   MPU_REGION_SIZE_512MB    ((uint8_t)0x1C)
#define   MPU_REGION_SIZE_1GB      ((uint8_t)0x1D)
#define   MPU_REGION_SIZE_2GB      ((uint8_t)0x1E)
#define   MPU_REGION_SIZE_4GB      ((uint8_t)0x1F)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Permission_Attributes CORTEX MPU Region Permission Attributes
  * @{
  */
#define  MPU_REGION_NO_ACCESS      ((uint8_t)0x00)
#define  MPU_REGION_PRIV_RW        ((uint8_t)0x01)
#define  MPU_REGION_PRIV_RW_URO    ((uint8_t)0x02)
#define  MPU_REGION_FULL_ACCESS    ((uint8_t)0x03)
#define  MPU_REGION_PRIV_RO        ((uint8_t)0x05)
#define  MPU_REGION_PRIV_RO_URO    ((uint8_t)0x06)
/**
  * @}
  */
#endif /* CORE_CM0PLUS */
/* [MPU/CONSTANTS] M33 (ARMv8-M) specific definitions */
#ifdef CORE_CM33
/** @defgroup CORTEX_MPU_Access_Shareable CORTEX MPU Instruction Access Shareable
  * @{
  */
#define  MPU_ACCESS_NOT_SHAREABLE    ((uint8_t)0x00)
#define  MPU_ACCESS_OUTER_SHAREABLE  ((uint8_t)0x02)
#define  MPU_ACCESS_INNER_SHAREABLE  ((uint8_t)0x03)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Permission_Attributes CORTEX MPU Region Permission Attributes
  * @{
  */
#define  MPU_REGION_PRIV_RW          ((uint8_t)0x00)
#define  MPU_REGION_ALL_RW           ((uint8_t)0x01)
#define  MPU_REGION_PRIV_RO          ((uint8_t)0x02)
#define  MPU_REGION_ALL_RO           ((uint8_t)0x03)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Attributes_Number CORTEX MPU Memory Attributes Number
  * @{
  */
#define  MPU_ATTRIBUTES_NUMBER0      ((uint8_t)0x00)
#define  MPU_ATTRIBUTES_NUMBER1      ((uint8_t)0x01)
#define  MPU_ATTRIBUTES_NUMBER2      ((uint8_t)0x02)
#define  MPU_ATTRIBUTES_NUMBER3      ((uint8_t)0x03)
#define  MPU_ATTRIBUTES_NUMBER4      ((uint8_t)0x04)
#define  MPU_ATTRIBUTES_NUMBER5      ((uint8_t)0x05)
#define  MPU_ATTRIBUTES_NUMBER6      ((uint8_t)0x06)
#define  MPU_ATTRIBUTES_NUMBER7      ((uint8_t)0x07)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Attributes CORTEX MPU Attributes
  * @{
  */
#define  MPU_DEVICE_NGNRNE          0x0U  /* Device, noGather, noReorder, noEarly acknowledge. */
#define  MPU_DEVICE_NGNRE           0x4U  /* Device, noGather, noReorder, Early acknowledge.   */
#define  MPU_DEVICE_NGRE            0x8U  /* Device, noGather, Reorder, Early acknowledge.     */
#define  MPU_DEVICE_GRE             0xCU  /* Device, Gather, Reorder, Early acknowledge.       */

#define  MPU_WRITE_THROUGH          0x0U  /* Normal memory, write-through. */
#define  MPU_NOT_CACHEABLE          0x4U  /* Normal memory, non-cacheable. */
#define  MPU_WRITE_BACK             0x4U  /* Normal memory, write-back.    */

#define  MPU_TRANSIENT              0x0U  /* Normal memory, transient.     */
#define  MPU_NON_TRANSIENT          0x8U  /* Normal memory, non-transient. */

#define  MPU_NO_ALLOCATE            0x0U  /* Normal memory, no allocate.         */
#define  MPU_W_ALLOCATE             0x1U  /* Normal memory, write allocate.      */
#define  MPU_R_ALLOCATE             0x2U  /* Normal memory, read allocate.       */
#define  MPU_RW_ALLOCATE            0x3U  /* Normal memory, read/write allocate. */

/**
  * @}
  */
#endif /* CORE_CM33 */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Macros CORTEX Exported Macros
  * @{
  */
#define OUTER(__ATTR__)        ((__ATTR__) << 4U)
#define INNER_OUTER(__ATTR__)  ((__ATTR__) | ((__ATTR__) << 4U))

/**
  * @}
  */

/** @defgroup HAL_CORTEX_Aliased_Defines HAL CORTEX Aliased Defines maintained for legacy purpose
  * @{
  */
#define __HAL_CORTEX_SYSTICKCLK_CONFIG HAL_SYSTICK_CLKSourceConfig
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */

/** @defgroup CORTEX_Exported_Functions_Group1 Initialization and Configuration functions
  * @brief    Initialization and Configuration functions
  * @{
  */
/* Initialization and Configuration functions *****************************/
/* [NVIC/FUNCTIONS] M0+ (ARMv6-M) / M33 (ARMv8-M) common prototypes */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);

/* [NVIC/FUNCTIONS] M33 (ARMv8-M) specific prototypes */
#ifdef CORE_CM33
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGrouping);
#endif /* CORE_CM33 */

/**
  * @}
  */

/** @defgroup CORTEX_Exported_Functions_Group2 Peripheral Control functions
  * @brief   Cortex control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
/* [NVIC/FUNCTIONS] M0+ (ARMv6-M) / M33 (ARMv8-M) common prototypes */
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *const pPreemptPriority,
                          uint32_t *const pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
uint32_t HAL_SYSTICK_GetCLKSourceConfig(void);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);

/* [NVIC/FUNCTIONS] M33 (ARMv8-M) specific prototypes */
#ifdef CORE_CM33
uint32_t HAL_NVIC_GetPriorityGrouping(void);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
/* [NVIC/FUNCTIONS] M33 (ARMv8-M) specific to Security Extension prototypes */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
void HAL_NVIC_ConfigInterruptSecurity(IRQn_Type IRQn, uint32_t IRQSecurityState);
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#endif /* CORE_CM33 */

#if (__MPU_PRESENT == 1U)
/* [MPU/FUNCTIONS] M0+ (ARMv6-M) / M33 (ARMv8-M) common prototypes */
void HAL_MPU_Enable(uint32_t MPU_Control);
void HAL_MPU_Disable(void);
void HAL_MPU_EnableRegion(uint32_t RegionNumber);
void HAL_MPU_DisableRegion(uint32_t RegionNumber);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* MPU_NS Control functions ***********************************************/
void HAL_MPU_Enable_NS(uint32_t MPU_Control);
void HAL_MPU_Disable_NS(void);
void HAL_MPU_EnableRegion_NS(uint32_t RegionNumber);
void HAL_MPU_DisableRegion_NS(uint32_t RegionNumber);
void HAL_MPU_ConfigRegion_NS(const MPU_Region_InitTypeDef *const pMPU_RegionInit);
void HAL_MPU_ConfigMemoryAttributes_NS(const MPU_Attributes_InitTypeDef *const pMPU_AttributesInit);
#endif /* __ARM_FEATURE_CMSE */

/* [MPU/FUNCTIONS] M0+ (ARMv6-M) specific prototypes */
#ifdef CORE_CM0PLUS
void HAL_MPU_ConfigRegion(const MPU_Region_InitTypeDef *MPU_Init);
#endif /* CORE_CM0PLUS */

/* [MPU/FUNCTIONS] M33 (ARMv8-M) specific prototypes */
#ifdef CORE_CM33
void HAL_MPU_ConfigRegion(const MPU_Region_InitTypeDef *const pMPU_RegionInit);
void HAL_MPU_ConfigMemoryAttributes(const MPU_Attributes_InitTypeDef *const pMPU_AttributesInit);
#endif /* CORE_CM33 */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Macros CORTEX Private Macros
  * @{
  */

/* [NVIC/MACROS] M0+ (ARMv6-M) / M33 (ARMv8-M) common definitions */
#define IS_NVIC_DEVICE_IRQ(IRQ)                (((uint32_t)(IRQ) >= 0x00U) && ((uint32_t)(IRQ) < (uint32_t)MAX_IRQ_n))

/* [NVIC/MACROS] M33 (ARMv8-M) specific definitions */
#ifdef CORE_CM33

#define IS_NVIC_PREEMPTION_PRIORITY(__PRIO__, __PRIOGRP__)   (((__PRIO__) < (1uL << __NVIC_PRIO_BITS)) && \
                                                              ((__PRIO__) < (0x1uL << (0x07u -(uint8_t)(__PRIOGRP__)))))
/* WARNING ! Historical macro name IS_NVIC_PRIORITY_GROUP is confusing       */
/*           according to ARM specifications, because IS_NVIC_PRIORITY_GROUP */
/*           seems to stand for checking "Group Priority number of bits"     */
/*           whereas it checks "Priority Grouping" value in respect to       */
/*           number of priority levels (aka "__NVIC_PRIO_BITS").             */
/* As a consequence, it LIMITS lowest value for "Priority Grouping"          */
/* according to __NVIC_PRIO_BITS = 4 to value "NVIC_PRIORITYGROUP_4".        */
#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PRIORITYGROUP_0) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_1) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_2) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_3) || \
                                       ((GROUP) == NVIC_PRIORITYGROUP_4))

/* However, whatever the number of priority levels, all "Priority Grouping" */
/* values in range [0;7] (used to set PRIO field of register AIRCR) are     */
/* managed internally to saturate "Group Priority number of bits" value.    */
/* That is why we can define new macro IS_NVIC_PRIORITY_GROUPING() to check */
/* "Priority Grouping" value. */
#define IS_NVIC_PRIORITY_GROUPING(GROUP) (((GROUP) < 8U) && ((GROUP) >=0U))

#define IS_NVIC_SUB_PRIORITY(__PRIO__, __PRIOGRP__)   (((__PRIOGRP__) < (0x07u - ((uint8_t)__NVIC_PRIO_BITS))) ?\
                                                       ((__PRIO__) < (1u)): \
                                                       ((__PRIO__) < (0x1uL << ((__PRIOGRP__) - \
                                                                                (0x07u -((uint8_t)__NVIC_PRIO_BITS))))))

#define IS_NVIC_IRQN_TYPE(IRQn_Type_value) (((IRQn_Type_value) >= MemoryManagement_IRQn) && \
                                            ((IRQn_Type_value) < MAX_IRQ_n))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_NVIC_IRQ_SECURITY_STATE(IRQ_Security_State_value) ((IRQ_Security_State_value == NVIC_SECURE_INTERRUPT) || \
                                                              (IRQ_Security_State_value == NVIC_NONSECURE_INTERRUPT))
#define IS_MPU_INSTANCE(INSTANCE) (((INSTANCE) == MPU) || ((INSTANCE) == MPU_NS))
#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#endif /* CORE_CM33 */

#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SYSTICK_CLKSOURCE_HCLK)|| \
                                       ((SOURCE) == SYSTICK_CLKSOURCE_HCLK_DIV8))

/* [NVIC/MACROS] M0+ (ARMv6-M) specific definitions */
#ifdef CORE_CM0PLUS
#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < (1UL << __NVIC_PRIO_BITS))
#define IS_NVIC_SUB_PRIORITY(PRIORITY)         (PRIORITY == 0)

#define IS_NVIC_IRQN_TYPE(IRQn_Type_value) ((IRQn_Type_value >= SVC_IRQn) && \
                                            (IRQn_Type_value < MAX_IRQ_n))
#endif /* CORE_CM0PLUS */

#if (__MPU_PRESENT == 1)
/* [MPU/MACROS] M0+ (ARMv6-M) / M33 (ARMv8-M) common definitions */
#define IS_MPU_HFNMI_PRIVDEF_CONTROL(CONTROL) (((CONTROL) == MPU_HFNMI_PRIVDEF_NONE) || \
                                               ((CONTROL) == MPU_HARDFAULT_NMI)      || \
                                               ((CONTROL) == MPU_PRIVILEGED_DEFAULT) || \
                                               ((CONTROL) == MPU_HFNMI_PRIVDEF))

#define IS_MPU_REGION_ENABLE(STATE) (((STATE) == MPU_REGION_ENABLE) || \
                                     ((STATE) == MPU_REGION_DISABLE))

#define IS_MPU_INSTRUCTION_ACCESS(STATE) (((STATE) == MPU_INSTRUCTION_ACCESS_ENABLE) || \
                                          ((STATE) == MPU_INSTRUCTION_ACCESS_DISABLE))

/* [MPU/MACROS] M0+ (ARMv6-M) specific definitions */
#ifdef CORE_CM0PLUS
#define IS_MPU_REGION_NUMBER(NUMBER)    (((NUMBER) == MPU_REGION_NUMBER0) || \
                                         ((NUMBER) == MPU_REGION_NUMBER1) || \
                                         ((NUMBER) == MPU_REGION_NUMBER2) || \
                                         ((NUMBER) == MPU_REGION_NUMBER3) || \
                                         ((NUMBER) == MPU_REGION_NUMBER4) || \
                                         ((NUMBER) == MPU_REGION_NUMBER5) || \
                                         ((NUMBER) == MPU_REGION_NUMBER6) || \
                                         ((NUMBER) == MPU_REGION_NUMBER7))

#define IS_MPU_ACCESS_SHAREABLE(STATE)   (((STATE) == MPU_ACCESS_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_SHAREABLE))

#define IS_MPU_ACCESS_CACHEABLE(STATE)   (((STATE) == MPU_ACCESS_CACHEABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_CACHEABLE))

#define IS_MPU_ACCESS_BUFFERABLE(STATE)   (((STATE) == MPU_ACCESS_BUFFERABLE) || \
                                           ((STATE) == MPU_ACCESS_NOT_BUFFERABLE))

#define IS_MPU_TEX_LEVEL(TYPE)           (((TYPE) == MPU_TEX_LEVEL0)  || \
                                          ((TYPE) == MPU_TEX_LEVEL1)  || \
                                          ((TYPE) == MPU_TEX_LEVEL2))

#define IS_MPU_REGION_PERMISSION_ATTRIBUTE(TYPE) (((TYPE) == MPU_REGION_NO_ACCESS)   || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RW_URO) || \
                                                  ((TYPE) == MPU_REGION_FULL_ACCESS) || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO)     || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO_URO))

#define IS_MPU_REGION_SIZE(SIZE)    (((SIZE) == MPU_REGION_SIZE_256B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_512B)  || \
                                     ((SIZE) == MPU_REGION_SIZE_1KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8KB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64KB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512KB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_8MB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_16MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_32MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_64MB)  || \
                                     ((SIZE) == MPU_REGION_SIZE_128MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_256MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_512MB) || \
                                     ((SIZE) == MPU_REGION_SIZE_1GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_2GB)   || \
                                     ((SIZE) == MPU_REGION_SIZE_4GB))

#define IS_MPU_SUB_REGION_DISABLE(SUBREGION)      ((SUBREGION) < (uint16_t)0x00FFU)

#endif /* CORE_CM0PLUS */
/* [MPU/MACROS] M33 (ARMv8-M) specific definitions */
#ifdef CORE_CM33
#define IS_MPU_REGION_NUMBER(NUMBER)    (((NUMBER) == MPU_REGION_NUMBER0)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER1)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER2)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER3)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER4)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER5)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER6)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER7)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER8)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER9)  || \
                                         ((NUMBER) == MPU_REGION_NUMBER10) || \
                                         ((NUMBER) == MPU_REGION_NUMBER11) || \
                                         ((NUMBER) == MPU_REGION_NUMBER12) || \
                                         ((NUMBER) == MPU_REGION_NUMBER13) || \
                                         ((NUMBER) == MPU_REGION_NUMBER14) || \
                                         ((NUMBER) == MPU_REGION_NUMBER15))

#define IS_MPU_ACCESS_SHAREABLE(STATE)   (((STATE) == MPU_ACCESS_OUTER_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_INNER_SHAREABLE) || \
                                          ((STATE) == MPU_ACCESS_NOT_SHAREABLE))

#define IS_MPU_REGION_PERMISSION_ATTRIBUTE(TYPE) (((TYPE) == MPU_REGION_PRIV_RW) || \
                                                  ((TYPE) == MPU_REGION_ALL_RW)  || \
                                                  ((TYPE) == MPU_REGION_PRIV_RO)     || \
                                                  ((TYPE) == MPU_REGION_ALL_RO))

#define IS_MPU_ATTRIBUTES_NUMBER(NUMBER)  (((NUMBER) == MPU_ATTRIBUTES_NUMBER0) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER1) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER2) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER3) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER4) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER5) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER6) || \
                                           ((NUMBER) == MPU_ATTRIBUTES_NUMBER7))
#endif /* CORE_CM33 */
#endif /* __MPU_PRESENT */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP2xx_HAL_CORTEX_H */
