/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_cortex.h
  * @brief   Header file for the CORTEX HAL module.
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

/* Define to prevent recursive inclusion. ----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_HAL_CORTEX_H
#define STM32H7PXX_HAL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @defgroup CORTEX CORTEX
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Types HAL CORTEX Types
  * @{
  */

/*! CORTEX priority group enumeration definition */
typedef enum
{
  HAL_CORTEX_NVIC_PRIORITY_GROUP_0 = 0x7U, /*!< 0 bit  for preemption priority, 4 bits for sub-priority */
  HAL_CORTEX_NVIC_PRIORITY_GROUP_1 = 0x6U, /*!< 1 bit  for preemption priority, 3 bits for sub-priority */
  HAL_CORTEX_NVIC_PRIORITY_GROUP_2 = 0x5U, /*!< 2 bits for preemption priority, 2 bits for sub-priority */
  HAL_CORTEX_NVIC_PRIORITY_GROUP_3 = 0x4U, /*!< 3 bits for preemption priority, 1 bit  for sub-priority */
  HAL_CORTEX_NVIC_PRIORITY_GROUP_4 = 0x3U  /*!< 4 bits for preemption priority, 0 bit  for sub-priority */
} hal_cortex_nvic_priority_group_t;

/*! CORTEX preemption priority enumeration definition */
typedef enum
{
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_0  = 0x0U,  /*!< NVIC preemption priority 0  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_1  = 0x1U,  /*!< NVIC preemption priority 1  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_2  = 0x2U,  /*!< NVIC preemption priority 2  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_3  = 0x3U,  /*!< NVIC preemption priority 3  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_4  = 0x4U,  /*!< NVIC preemption priority 4  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_5  = 0x5U,  /*!< NVIC preemption priority 5  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_6  = 0x6U,  /*!< NVIC preemption priority 6  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_7  = 0x7U,  /*!< NVIC preemption priority 7  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_8  = 0x8U,  /*!< NVIC preemption priority 8  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_9  = 0x9U,  /*!< NVIC preemption priority 9  */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_10 = 0xAU,  /*!< NVIC preemption priority 10 */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_11 = 0xBU,  /*!< NVIC preemption priority 11 */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_12 = 0xCU,  /*!< NVIC preemption priority 12 */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_13 = 0xDU,  /*!< NVIC preemption priority 13 */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_14 = 0xEU,  /*!< NVIC preemption priority 14 */
  HAL_CORTEX_NVIC_PREEMP_PRIORITY_15 = 0xFU   /*!< NVIC preemption priority 15 */
} hal_cortex_nvic_preemp_priority_t;

/*! CORTEX sub-priority enumeration definition */
typedef enum
{
  HAL_CORTEX_NVIC_SUB_PRIORITY_0  = 0x0U,  /*!< NVIC sub-priority 0  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_1  = 0x1U,  /*!< NVIC sub-priority 1  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_2  = 0x2U,  /*!< NVIC sub-priority 2  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_3  = 0x3U,  /*!< NVIC sub-priority 3  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_4  = 0x4U,  /*!< NVIC sub-priority 4  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_5  = 0x5U,  /*!< NVIC sub-priority 5  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_6  = 0x6U,  /*!< NVIC sub-priority 6  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_7  = 0x7U,  /*!< NVIC sub-priority 7  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_8  = 0x8U,  /*!< NVIC sub-priority 8  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_9  = 0x9U,  /*!< NVIC sub-priority 9  */
  HAL_CORTEX_NVIC_SUB_PRIORITY_10 = 0xAU,  /*!< NVIC sub-priority 10 */
  HAL_CORTEX_NVIC_SUB_PRIORITY_11 = 0xBU,  /*!< NVIC sub-priority 11 */
  HAL_CORTEX_NVIC_SUB_PRIORITY_12 = 0xCU,  /*!< NVIC sub-priority 12 */
  HAL_CORTEX_NVIC_SUB_PRIORITY_13 = 0xDU,  /*!< NVIC sub-priority 13 */
  HAL_CORTEX_NVIC_SUB_PRIORITY_14 = 0xEU,  /*!< NVIC sub-priority 14 */
  HAL_CORTEX_NVIC_SUB_PRIORITY_15 = 0xFU   /*!< NVIC sub-priority 15 */
} hal_cortex_nvic_sub_priority_t;

/*! CORTEX NVIC IRQ status enumeration definition */
typedef enum
{
  HAL_CORTEX_NVIC_IRQ_DISABLED = 0U, /*!< NVIC IRQ disabled */
  HAL_CORTEX_NVIC_IRQ_ENABLED  = 1U  /*!< NVIC IRQ enabled  */
} hal_cortex_nvic_irq_status_t;

/*! CORTEX NVIC IRQ active status enumeration definition */
typedef enum
{
  HAL_CORTEX_NVIC_IRQ_NOT_ACTIVE = 0U, /*!< NVIC IRQ not active */
  HAL_CORTEX_NVIC_IRQ_ACTIVE     = 1U  /*!< NVIC IRQ active     */
} hal_cortex_nvic_irq_active_status_t;

/*! CORTEX NVIC IRQ pending status enumeration definition */
typedef enum
{
  HAL_CORTEX_NVIC_IRQ_NOT_PENDING = 0U, /*!< NVIC IRQ not pending */
  HAL_CORTEX_NVIC_IRQ_PENDING     = 1U  /*!< NVIC IRQ pending     */
} hal_cortex_nvic_irq_pending_status_t;

/*! CORTEX SysTick clock source enumeration definition */
typedef enum
{
  HAL_CORTEX_SYSTICK_CLKSOURCE_INTERNAL = SysTick_CTRL_CLKSOURCE_Msk,      /*!< Internal clock selected as SysTick clock
                                                                           source */
  HAL_CORTEX_SYSTICK_CLKSOURCE_EXTERNAL = 0U                               /*!< External clock selected as SysTick clock
                                                                           source */
} hal_cortex_systick_clk_src_t;

/*! CORTEX MPU unmapped address fault enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_ACCESS_FAULT_ALL       = 0x00,                    /*!< All accesses to unmapped addresses result
                                                                        in faults */
  HAL_CORTEX_MPU_ACCESS_FAULT_ONLY_PRIV = MPU_CTRL_PRIVDEFENA_Msk  /*!< Enables the default memory map for privileged
                                                                        code      */
} hal_cortex_mpu_unmapped_addr_fault_t;

/*! CORTEX MPU HardFault NMI status enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_HARDFAULT_NMI_DISABLE = 0x00,                  /*!< HardFault and NMI handlers bypass MPU
                                                                      configuration as if MPU is disabled */
  HAL_CORTEX_MPU_HARDFAULT_NMI_ENABLE  = MPU_CTRL_HFNMIENA_Msk  /*!< MPU access rules apply to HardFault and NMI
                                                                      handlers                            */
} hal_cortex_mpu_hardfault_nmi_state_t;

/*! CORTEX MPU memory region size enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_REGION_SIZE_32B   = 0x04U, /*!< MPU memory region size 32 Bytes   */
  HAL_CORTEX_MPU_REGION_SIZE_64B   = 0x05U, /*!< MPU memory region size 64 Bytes   */
  HAL_CORTEX_MPU_REGION_SIZE_128B  = 0x06U, /*!< MPU memory region size 128 Bytes  */
  HAL_CORTEX_MPU_REGION_SIZE_256B  = 0x07U, /*!< MPU memory region size 256 Bytes  */
  HAL_CORTEX_MPU_REGION_SIZE_512B  = 0x08U, /*!< MPU memory region size 512 Bytes  */
  HAL_CORTEX_MPU_REGION_SIZE_1KB   = 0x09U, /*!< MPU memory region size 1 KBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_2KB   = 0x0AU, /*!< MPU memory region size 2 KBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_4KB   = 0x0BU, /*!< MPU memory region size 4 KBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_8KB   = 0x0CU, /*!< MPU memory region size 8 KBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_16KB  = 0x0DU, /*!< MPU memory region size 16 KBytes  */
  HAL_CORTEX_MPU_REGION_SIZE_32KB  = 0x0EU, /*!< MPU memory region size 32 KBytes  */
  HAL_CORTEX_MPU_REGION_SIZE_64KB  = 0x0FU, /*!< MPU memory region size 64 KBytes  */
  HAL_CORTEX_MPU_REGION_SIZE_128KB = 0x10U, /*!< MPU memory region size 128 KBytes */
  HAL_CORTEX_MPU_REGION_SIZE_256KB = 0x11U, /*!< MPU memory region size 256 KBytes */
  HAL_CORTEX_MPU_REGION_SIZE_512KB = 0x12U, /*!< MPU memory region size 512 KBytes */
  HAL_CORTEX_MPU_REGION_SIZE_1MB   = 0x13U, /*!< MPU memory region size 1 MBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_2MB   = 0x14U, /*!< MPU memory region size 2 MBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_4MB   = 0x15U, /*!< MPU memory region size 4 MBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_8MB   = 0x16U, /*!< MPU memory region size 8 MBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_16MB  = 0x17U, /*!< MPU memory region size 16 MBytes  */
  HAL_CORTEX_MPU_REGION_SIZE_32MB  = 0x18U, /*!< MPU memory region size 32 MBytes  */
  HAL_CORTEX_MPU_REGION_SIZE_64MB  = 0x19U, /*!< MPU memory region size 64 MBytes  */
  HAL_CORTEX_MPU_REGION_SIZE_128MB = 0x1AU, /*!< MPU memory region size 128 MBytes */
  HAL_CORTEX_MPU_REGION_SIZE_256MB = 0x1BU, /*!< MPU memory region size 256 MBytes */
  HAL_CORTEX_MPU_REGION_SIZE_512MB = 0x1CU, /*!< MPU memory region size 512 MBytes */
  HAL_CORTEX_MPU_REGION_SIZE_1GB   = 0x1DU, /*!< MPU memory region size 1 GBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_2GB   = 0x1EU, /*!< MPU memory region size 2 GBytes   */
  HAL_CORTEX_MPU_REGION_SIZE_4GB   = 0x1FU  /*!< MPU memory region size 4 GBytes   */
} hal_cortex_mpu_region_size_t;

/*! CORTEX MPU memory attributes enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_SO_MEM_SHAREABLE                     = (0x00U << 16U), /*!< Strongly ordered, Shareable                                                */
  HAL_CORTEX_MPU_DEVICE_MEM_SHAREABLE                 = (0x01U << 16U), /*!< Device, Shareable                                                          */
  HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA      = (0x02U << 16U), /*!< Normal, Non-shareable, Outer and inner write-through, No write allocate    */
  HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WB_NWA      = (0x03U << 16U), /*!< Normal, Non-shareable, Outer and inner write-back, No write allocate       */
  HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_WT_NWA       = (0x06U << 16U), /*!< Normal, Shareable, Outer and inner write-through, No write allocate        */
  HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_WB_NWA       = (0x07U << 16U), /*!< Normal, Shareable, Outer and inner write-back, No write allocate           */
  HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_NCACHEABLE  = (0x08U << 16U), /*!< Normal, Non-shareable, outer and inner Non-cacheable                       */
  HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_NCACHEABLE   = (0x0CU << 16U), /*!< Normal, Shareable, outer and inner Non-cacheable                           */
  HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WB_RWA      = (0x0BU << 16U), /*!< Normal, Non-shareable, outer and inner write-back, read and write allocate */
  HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_WB_RWA       = (0x0FU << 16U), /*!< Normal, Shareable, outer and inner write-back, read and write allocate     */
  HAL_CORTEX_MPU_DEVICE_MEM_NSHAREABLE                = (0x10U << 16U)  /*!< Device, Not shareable                                                      */
} hal_cortex_mpu_mem_attr_t;

/*! CORTEX MPU region index enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_REGION_0  = 0U,  /*!< MPU Region Index 0 */
  HAL_CORTEX_MPU_REGION_1  = 1U,  /*!< MPU Region Index 1 */
  HAL_CORTEX_MPU_REGION_2  = 2U,  /*!< MPU Region Index 2 */
  HAL_CORTEX_MPU_REGION_3  = 3U,  /*!< MPU Region Index 3 */
  HAL_CORTEX_MPU_REGION_4  = 4U,  /*!< MPU Region Index 4 */
  HAL_CORTEX_MPU_REGION_5  = 5U,  /*!< MPU Region Index 5 */
  HAL_CORTEX_MPU_REGION_6  = 6U,  /*!< MPU Region Index 6 */
  HAL_CORTEX_MPU_REGION_7  = 7U,   /*!< MPU Region Index 7 */
  HAL_CORTEX_MPU_REGION_8  = 8U,  /*!< MPU Region Index 8 */
  HAL_CORTEX_MPU_REGION_9  = 9U,  /*!< MPU Region Index 9 */
  HAL_CORTEX_MPU_REGION_10 = 10U, /*!< MPU Region Index 10 */
  HAL_CORTEX_MPU_REGION_11 = 11U, /*!< MPU Region Index 11 */
  HAL_CORTEX_MPU_REGION_12 = 12U, /*!< MPU Region Index 12 */
  HAL_CORTEX_MPU_REGION_13 = 13U, /*!< MPU Region Index 13 */
  HAL_CORTEX_MPU_REGION_14 = 14U, /*!< MPU Region Index 14 */
  HAL_CORTEX_MPU_REGION_15 = 15U  /*!< MPU Region Index 15 */
} hal_cortex_mpu_region_idx_t;

/*! CORTEX MPU region access attributes enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_REGION_ALL_RW_FAULT   = 0x00U, /*!< All accesses generate a permission fault                     */
  HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW   = 0x01U, /*!< Access from privileged software only                         */
  HAL_CORTEX_MPU_REGION_NPRIV_W_FAULT  = 0x02U, /*!< Writes by unprivileged software generate a permission fault  */
  HAL_CORTEX_MPU_REGION_ALL_RW         = 0x03U, /*!< Full access                                                  */
  HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO   = 0x05U, /*!< Reads by privileged software only                            */
  HAL_CORTEX_MPU_REGION_ALL_RO         = 0x06U  /*!< Read only, by privileged or unprivileged software            */
} hal_cortex_mpu_region_access_attr_t;

/*! CORTEX MPU execution access enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE = 0x01U, /*!< MPU execution attribute disable */
  HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE  = 0x00U  /*!< MPU execution attribute enable  */
} hal_cortex_mpu_execution_attr_t;

/*! CORTEX MPU status enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_DISABLED  = 0U, /*!< MPU disabled */
  HAL_CORTEX_MPU_ENABLED   = 1U  /*!< MPU enabled  */
} hal_cortex_mpu_status_t;

/*! CORTEX MPU region status enumeration definition */
typedef enum
{
  HAL_CORTEX_MPU_REGION_DISABLED  = 0U, /*!< MPU region disabled */
  HAL_CORTEX_MPU_REGION_ENABLED   = 1U  /*!< MPU region enabled  */
} hal_cortex_mpu_region_status_t;

/*! CORTEX MPU region configuration structure definition */
typedef struct
{
  uint32_t                              base_addr;      /*!< Base address of the region to protect  */
  hal_cortex_mpu_region_size_t          size;           /*!< Size of the region to protect          */
  hal_cortex_mpu_region_access_attr_t   access_attr;    /*!< Region access permission               */
  hal_cortex_mpu_mem_attr_t             mem_attr;       /*!< Memory attributes                      */
  hal_cortex_mpu_execution_attr_t       exec_attr;      /*!< Execution attribute status             */
  uint8_t                               sub_region;     /*!< Subregion(s) to enable/disable         */
} hal_cortex_mpu_region_config_t;

/*! CORTEX SCB CPU ID information structure definition */
typedef struct
{
  uint32_t revision     : 4U;  /*!< Revision number identifier */
  uint32_t part_number  : 12U; /*!< Cortex part number         */
  uint32_t architecture : 4U;  /*!< Architecture version       */
  uint32_t variant      : 4U;  /*!< Variant                    */
  uint32_t implementer  : 8U;  /*!< Implementer identifier     */
} hal_cortex_scb_cpuid_info_t;
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Constants HAL CORTEX Constants
  * @{
  */

/** @defgroup  CORTEX_MPU_Sub_Region_Enable_Disable CORTEX MPU subregion enable/disable definition
  * @{
  */
#define HAL_CORTEX_MPU_SUB_REGION_ENABLE_ALL   0x00U /*!< Enable all MPU subregions     */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_0    0x01U /*!< Disable MPU subregion Index 0 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_1    0x02U /*!< Disable MPU subregion Index 1 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_2    0x04U /*!< Disable MPU subregion Index 2 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_3    0x08U /*!< Disable MPU subregion Index 3 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_4    0x10U /*!< Disable MPU subregion Index 4 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_5    0x20U /*!< Disable MPU subregion Index 5 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_6    0x40U /*!< Disable MPU subregion Index 6 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_7    0x80U /*!< Disable MPU subregion Index 7 */
#define HAL_CORTEX_MPU_SUB_REGION_DISABLE_ALL  0xFFU /*!< Disable all MPU subregions    */
/**
  * @}
  */
/** @defgroup  CORTEX_Fault_Exceptions Fault Exceptions definition
  * @{
  */
#define HAL_CORTEX_SCB_USAGE_FAULT          SCB_SHCSR_USGFAULTENA_Msk    /*!< Usage fault             */
#define HAL_CORTEX_SCB_BUS_FAULT            SCB_SHCSR_BUSFAULTENA_Msk    /*!< Bus fault               */
#define HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT SCB_SHCSR_MEMFAULTENA_Msk    /*!< Memory management fault */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Functions HAL CORTEX Functions
  * @{
  */

/**
  * @defgroup CORTEX_Exported_Functions_Group1 NVIC management functions
  * @{
  */
/* Priority grouping functions */
void                             HAL_CORTEX_NVIC_SetPriorityGrouping(hal_cortex_nvic_priority_group_t prio_grp);
hal_cortex_nvic_priority_group_t HAL_CORTEX_NVIC_GetPriorityGrouping(void);

/* Set and get priority configuration functions */
void HAL_CORTEX_NVIC_SetPriority(IRQn_Type irqn, hal_cortex_nvic_preemp_priority_t preemp_prio,
                                 hal_cortex_nvic_sub_priority_t sub_prio);
void HAL_CORTEX_NVIC_GetPriority(IRQn_Type irqn, hal_cortex_nvic_preemp_priority_t *p_preemp_prio,
                                 hal_cortex_nvic_sub_priority_t *p_sub_prio);

/* NVIC IRQ management functions */
void                                 HAL_CORTEX_NVIC_EnableIRQ(IRQn_Type irqn);
void                                 HAL_CORTEX_NVIC_DisableIRQ(IRQn_Type irqn);
hal_cortex_nvic_irq_status_t         HAL_CORTEX_NVIC_IsEnabledIRQ(IRQn_Type irqn);
hal_cortex_nvic_irq_active_status_t  HAL_CORTEX_NVIC_IsActiveIRQ(IRQn_Type irqn);
void                                 HAL_CORTEX_NVIC_SetPendingIRQ(IRQn_Type irqn);
void                                 HAL_CORTEX_NVIC_ClearPendingIRQ(IRQn_Type irqn);
hal_cortex_nvic_irq_pending_status_t HAL_CORTEX_NVIC_IsPendingIRQ(IRQn_Type irqn);

/* NVIC system reset function */
__NO_RETURN void HAL_CORTEX_NVIC_SystemReset(void);

/**
  * @}
  */

/**
  * @defgroup CORTEX_Exported_Functions_Group2 SYSTICK management functions
  * @{
  */
hal_status_t HAL_CORTEX_SYSTICK_SetFreq(uint32_t ticks_freq);
void         HAL_CORTEX_SYSTICK_SetClkSource(hal_cortex_systick_clk_src_t clk_src);
void         HAL_CORTEX_SYSTICK_Enable(void);
void         HAL_CORTEX_SYSTICK_Enable_IT(void);
void         HAL_CORTEX_SYSTICK_Disable(void);
void         HAL_CORTEX_SYSTICK_Suspend(void);
void         HAL_CORTEX_SYSTICK_Resume(void);
void         HAL_CORTEX_SYSTICK_IRQHandler(void);
void         HAL_CORTEX_SYSTICK_Callback(void);

/**
  * @}
  */

/**
  * @defgroup CORTEX_Exported_Functions_Group3 MPU management functions
  * @{
  */
/* MPU config functions */
void                    HAL_CORTEX_MPU_Enable(hal_cortex_mpu_hardfault_nmi_state_t fault_state,
                                              hal_cortex_mpu_unmapped_addr_fault_t priv_default_state);
void                    HAL_CORTEX_MPU_Disable(void);
hal_cortex_mpu_status_t HAL_CORTEX_MPU_IsEnabled(void);
void                    HAL_CORTEX_MPU_GetConfig(hal_cortex_mpu_hardfault_nmi_state_t *p_fault_state,
                                                 hal_cortex_mpu_unmapped_addr_fault_t *p_priv_default_state);
uint32_t                HAL_CORTEX_MPU_GetRegionCount(void);

/* MPU region management functions */
hal_status_t                   HAL_CORTEX_MPU_SetConfigRegion(hal_cortex_mpu_region_idx_t region_idx,
                                                              const hal_cortex_mpu_region_config_t *p_config);
void                           HAL_CORTEX_MPU_GetConfigRegion(hal_cortex_mpu_region_idx_t region_idx,
                                                              hal_cortex_mpu_region_config_t *p_config);
void                           HAL_CORTEX_MPU_EnableRegion(hal_cortex_mpu_region_idx_t region_idx);
void                           HAL_CORTEX_MPU_DisableRegion(hal_cortex_mpu_region_idx_t region_idx);
hal_cortex_mpu_region_status_t HAL_CORTEX_MPU_IsEnabledRegion(hal_cortex_mpu_region_idx_t region_idx);

/**
  * @}
  */

/**
  * @defgroup CORTEX_Exported_Functions_Group4 SCB management functions
  * @{
  */
/* SCB CPU ID information function */
void HAL_CORTEX_SCB_GetInfo(hal_cortex_scb_cpuid_info_t *p_info);

/* SCB Cortex Fault management functions */
void HAL_CORTEX_SCB_EnableHardFaultEscalation(uint32_t faults);
void HAL_CORTEX_SCB_DisableHardFaultEscalation(uint32_t faults);
/**
  * @}
  */

/**
  * @defgroup CORTEX_Exported_Functions_Group5 DCB management functions
  * @{
  */
void HAL_CORTEX_DCB_EnableDebugMonitor(void);
void HAL_CORTEX_DCB_DisableDebugMonitor(void);
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

#endif /* STM32H7PXX_HAL_CORTEX_H */
