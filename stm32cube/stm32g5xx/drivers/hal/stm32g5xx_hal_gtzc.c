/**
  **********************************************************************************************************************
  * @file   stm32g5xx_hal_gtzc.c
  * @brief  GTZC HAL module driver.
  *         This file provides firmware functions to manage the following
  *         functionalities of the Global TrustZone Controller (GTZC):
  *          + TZSC control, security and privilege configuration and lock functions
  *          + TZSC_MPCWM control, subregions security and privilege configuration and lock functions
#if !defined(GENERATOR_MPCBB_NOT_AVAILABLE)
  *          + MPCBB control, security and privilege configuration and lock functions
#endif
  *          + TZIC control, illegal access interrupt configuration and handling functions
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"


/** @addtogroup STM32G5XX_LL_Driver
  * @{
  */

#if defined(GTZC1_TZSC1_PERIPH)
#if defined (USE_HAL_GTZC_MODULE) && (USE_HAL_GTZC_MODULE == 1)

/** @addtogroup GTZC
  * @{
  */
/** @defgroup GTZC_Introduction GTZC Introduction
  * @{

  The Global TrustZone Controller (GTZC) hardware abstraction layer provides APIs to manage the GTZC peripheral on STM32
  microcontrollers. It enables configuration and control of security and privilege attributes for peripherals and memory
  regions, and handles illegal access detection.

  The HAL GTZC driver supports configuration of the TrustZone Security Controller (TZSC), Block-Based Memory Protection
  Controller (MPCBB), and TrustZone Illegal Access Controller (TZIC). It allows setting and locking security attributes,
  managing memory watermarking, configuring block-based memory security, and handling illegal access interrupts for
  secure and non-secure contexts.

  */
/**
  * @}
  */

/** @defgroup GTZC_How_To_Use GTZC How To Use
  * @{
This file provides firmware functions to manage the following functionalities of GTZC peripheral:

- Configure the security and privilege attributes of a TZSC securable peripheral.
- Lock the TZSC configuration of a securable peripheral.
- Lock the configuration of TZSC registers.
- Configure subregions boundaries of TZSC_MPCWM memories.
- Configure subregions security and privilege attributes of TZSC_MPCWM memories.
- Lock the configurations of TZSC_MPCWM subregions.
- Enable/Disable subregions of TZSC_MPCWM memories.
- Lock the configuration of TZSC_MPCWM registers.
- Configure the security and privilege attributes of MPCBB memories.
- Enable/Disable the secure read/write data accesses to non-secure blocks and super_blocks of MPCBB memories.
- Lock the configuration of MPCBB registers.
- Partially lock the configuration of MPCBB registers.
- Enable/Disable the read and write access of MPCBB memories.
- Get detailed information on illegal access to MPCBB memories.
- Enable/Disable the illegal access interrupt of a peripheral.
- Handle the illegal access interrupt.

# GTZC main features

The global TrustZone controller (GTZC) block that contains the following subblocks:
1. TZSC: TrustZone security controller
Defines the secure/privileged state of slave peripherals, and controls the subregion area size and properties for the
watermark memory peripheral controller (MPCWM). The TZSC informs some peripherals (such as RCC or GPIOs) about the
secure status of each securable peripheral, by sharing with RCC and I/O logic.

2. TZIC: TrustZone illegal access controller
Gathers all illegal access events in the system, and generates secure interrupts towards NVIC.

3. MPCBB: memory protection controller - block based
Configures the internal RAM in a TrustZone-system product having segmented SRAM (pages of 512 bytes) with
programmable-security and privileged attributes.

These subblocks are used to configure TrustZone system security in a product having bus agents with
programmable-security and privileged attributes such as:

  - On-chip RAM with programmable secure and/or privileged blocks (pages)
  - AHB and APB peripherals with programmable security and/or privileged access
  - Off-chip memories with secure and/or privileged areas

These subblocks are used to enforce and manage the isolation of STM32 hardware resources like memory and peripherals.

# How to use the GTZC HAL module driver

## The GTZC HAL driver can be used as follows:

1. TZSC peripherals security and privilege attributes configuration functions:

  - Set the security attribute of TZSC securable peripherals:
    - This functionality is ensured by HAL_GTZC_TZSC_SetPeriphSecAttr() function.

  - Get the security attribute of TZSC securable peripherals:
    - This functionality is ensured by HAL_GTZC_TZSC_GetPeriphSecAttr() function.

  - Set the privilege attribute of TZSC securable peripherals:
    - This functionality is ensured by HAL_GTZC_TZSC_SetPeriphPrivAttr() function.

  - Get the privilege attribute of TZSC securable peripherals:
    - This functionality is ensured by HAL_GTZC_TZSC_GetPeriphPrivAttr() function.

2. TZSC configuration lock functions:

  - Lock the configuration of TZSC registers:
    - This functionality is ensured by HAL_GTZC_TZSC_LockConfig() function.

  - Retrieve the lock status of TZSC registers configuration:
    - This functionality is ensured by HAL_GTZC_TZSC_IsLockedConfig() function.

4. MPCBB memory block security and privilege attributes configuration functions:

  - Set the security attribute of MPCBB memory block:
    - This functionality is ensured by HAL_GTZC_MPCBB_SetSecAttrByBlock() function.

  - Get the security attribute of MPCBB memory block:
    - This functionality is ensured by HAL_GTZC_MPCBB_GetSecAttrByBlock() function.

  - Set the privilege attribute of MPCBB memory block:
    - This functionality is ensured by HAL_GTZC_MPCBB_SetPrivAttrByBlock() function.

  - Get the privilege attribute of MPCBB memory block:
    - This functionality is ensured by HAL_GTZC_MPCBB_GetPrivAttrByBlock() function.

5. MPCBB memory block security and privilege attributes configuration depending on the input address functions:

  - Set the security attribute of MPCBB memory block depending on the input address:
    - This functionality is ensured by HAL_GTZC_MPCBB_SetSecAttrByAddr() function.

  - Get the security attribute of MPCBB memory block depending on the input address:
    - This functionality is ensured by HAL_GTZC_MPCBB_GetSecAttrByAddr() function.

  - Set the privilege attribute of MPCBB memory block depending on the input address:
    - This functionality is ensured by HAL_GTZC_MPCBB_SetPrivAttrByAddr() function.

  - Get the privilege attribute of MPCBB memory block depending on the input address:
    - This functionality is ensured by HAL_GTZC_MPCBB_GetPrivAttrByAddr() function.

6. MPCBB SRAM clocks security state :

  - Define the internal SRAMs clocks control in RCC as secure or not:
    - This functionality is ensured by HAL_GTZC_MPCBB_SetClkSecStateInversion() function.

  - Check the internal SRAMs clocks control in RCC secure or not state:
    - This functionality is ensured by HAL_GTZC_MPCBB_GetClkSecStateInversion() function.

7. MPCBB secure read/write illegal access :
  - Enable or disable the secure read/write data accesses to non-secure blocks and super_blocks of MPCBB memories:
    - This functionality is ensured by HAL_GTZC_MPCBB_EnableSecToNSecRdWrAccess() and
      HAL_GTZC_MPCBB_DisableSecToNSecRdWrAccess() functions.

  - Check if the secure read/write data accesses to non-secure blocks and super_blocks of MPCBB memories are enabled or
    disabled:
    - This functionality is ensured by HAL_GTZC_MPCBB_IsEnabledSecToNSecRdWrAccess() function.

8. MPCBB lock configuration functions:

  - Lock the MPCBB configuration for a memory super_block:
    - This functionality is ensured by HAL_GTZC_MPCBB_LockConfigBySuperBlock() function.

  - Check if the MPCBB configuration for a memory super_block is locked or unlocked:
    - This functionality is ensured by HAL_GTZC_MPCBB_IsLockedConfigBySuperBlock() function.

  - Lock the MPCBB configuration for a memory super_block depending on the input address:
    - This functionality is ensured by HAL_GTZC_MPCBB_LockConfigByAddr() function.

  - Check if the configuration of a MPCBB memory super_block depending on the input address is locked or unlocked:
    - This functionality is ensured by HAL_GTZC_MPCBB_IsLockedConfigByAddr() function.

  - Lock the configuration of MPCBB registers:
    - This functionality is ensured by HAL_GTZC_MPCBB_LockConfig() function.

  - Check if the configuration of MPCBB registers is locked or unlocked:
    - This functionality is ensured by HAL_GTZC_MPCBB_IsLockedConfig() function.

9. TZSC_MPCWM subregion boundaries defining functions:

  - Set the boundaries of a TZSC_MPCWM subregion:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_SetSubRegionBoundaries() function.

  - Get the boundaries of a TZSC_MPCWM subregion:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_GetSubRegionBoundaries() function.

10. TZSC_MPCWM subregion security and privilege attributes configuration functions:

  - Set the security attribute of a TZSC_MPCWM subregion:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_SetSubRegionSecAttr() function.

  - Get the security attribute of a TZSC_MPCWM subregion:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_GetSubRegionSecAttr() function.

  - Set the privilege attribute of a TZSC_MPCWM subregion:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_SetSubRegionPrivAttr() function.

  - Get the privilege attribute of a TZSC_MPCWM subregion:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_GetSubRegionPrivAttr() function.

11. TZSC_MPCWM subregion enable or disable functions:

  - Enable, disable and check if a TZSC_MPCWM subregion is enabled or disabled:
    - These functionalities are ensured respectively by HAL_GTZC_TZSC_MPCWM_EnableSubRegion(),
      HAL_GTZC_TZSC_MPCWM_DisableSubRegion() and HAL_GTZC_TZSC_MPCWM_IsEnabledSubRegion() functions.

12. TZSC_MPCWM subregion lock configuration functions:

  - Lock the configuration of a TZSC_MPCWM subregion:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_LockSubRegionConfig() function.

  - Check if a TZSC_MPCWM subregion configuration is locked or unlocked:
    - This functionality is ensured by HAL_GTZC_TZSC_MPCWM_IsLockedSubRegionConfig() function.

13. Enable or disable the illegal access interrupt for a peripheral functions:

  - Enable, disable and check if the illegal access interrupt for a peripheral is enabled or disabled:
    - These functionalities are ensured respectively by HAL_GTZC_TZIC_EnableIT(),
      HAL_GTZC_TZIC_DisableIT() and HAL_GTZC_TZIC_IsEnabledIT() functions.

14. Illegal access interrupt functions:

  - Illegal access interrupt service routines are served by:
    - This functionality is ensured by HAL_GTZC_TZIC_IRQHandler() function.

  - User can add their own code using:
    - This functionality is ensured by HAL_GTZC_TZIC_Callback() function.

  */
/**
  * @}
  */

/** @defgroup GTZC_Configuration_Table GTZC Configuration Table
  * @{

# Configuration inside the GTZC driver

Config defines                    | Description        | Default value | Note                                        |
--------------------------------- | ------------------ | ------------- | --------------------------------------------|
PRODUCT                           | from IDE           |        NA     | The selected device (ex stm32g5xx)    |
USE_HAL_GTZC_MODULE               | from hal_conf.h    |        1      | When set, HAL GTZC module is enabled        |
USE_HAL_CHECK_PARAM               | from hal_conf.h    |        0      | When set, parameters are checked in runtime |
USE_ASSERT_DBG_PARAM              | from IDE           |     Defined   | When defined, enable the params assert      |
CMSE_SECURE_EXECUTION_ENVIRONMENT | from stm32tnxx.h   |        NA     | The application in secure context           |
  */
/**
  * @}
  */

/* Private typedef ---------------------------------------------------------------------------------------------------*/
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT) && defined(USE_ASSERT_DBG_PARAM)
/** @defgroup GTZC_Private_Typedefs GTZC Private Typedefs
  * @{
  */

/**
  * @brief TZSC_MPCWM subregion boundaries range structure
  */
typedef struct
{
  uint32_t                  region_start_addr;          /*!< Start address of region x         */
  uint32_t                  region_end_addr;            /*!< End address of region x           */
} gtzc_range_region_t;
/**
  * @}
  */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT && USE_ASSERT_DBG_PARAM */

/* Private defines ---------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Private_Defines GTZC Private Defines
  * @{
  */

#define GTZC_REG_MAX_FIELD        LL_GTZC_REG_MAX_FIELD      /*!< GTZC maximum register field */

#define GTZC_TZSC_MPCWM_GRANULARITY_1  0x00000020U   /*!< TZSC_MPCWM_XSPI granularity: 32B                              */

#define GTZC_TZSC_MPCWM_RANGE_1        0x00002000U   /*!< 8KB max range   */
#define GTZC_TZSC_MPCWM_RANGE_2        0x10000000U   /*!< 256MB max range */

#define GTZC_MPCBB_BLOCK_SIZE         512U   /*!< MPCBB block size in bytes */
#define GTZC_BLOCKS_MAX_SUPER_BLOCK   32U    /*!< Number of blocks per super block */
#define GTZC_MPCBB_SUPER_BLOCK_SIZE   (GTZC_MPCBB_BLOCK_SIZE * GTZC_BLOCKS_MAX_SUPER_BLOCK) /*!< Super block size (bytes) */

#define GTZC_MAX_SUPER_BLOCK_1    4U  /*!< Number of super blocks for MPCBB1 */
#define GTZC_MAX_SUPER_BLOCK_2    8U  /*!< Number of super blocks for MPCBB2 */
#define GTZC_MAX_SUPER_BLOCK_3    2U  /*!< Number of super blocks for MPCBB3 */

#define GTZC_MPCWM_GRANULARITY_128KB  0x00020000U   /*!< XSPI1 granularity: 128KB */


/**
  * @}
  */
/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup GTZC_Private_Macros GTZC Private Macros
  * @{
  */

/**
  * @brief Macro to check GTZC Secure attribute
  */
#define IS_GTZC_SEC_ATTR(sec_attr) (((sec_attr) == HAL_GTZC_NSEC) \
                                    || ((sec_attr) == HAL_GTZC_SEC))

/**
  * @brief Macro to check GTZC Privilege attribute
  */
#define IS_GTZC_PRIV_ATTR(priv_attr) (((priv_attr) == HAL_GTZC_NPRIV) \
                                      || ((priv_attr) == HAL_GTZC_PRIV))

/**
  * @brief Macro to check GTZC TZSC securable peripherals in the register 1
  */
#define IS_GTZC_PERIPH_REG1(periph) (((0x1UL << ((periph)  % GTZC_REG_MAX_FIELD)) & LL_GTZC_GRP1_ALL) \
                                     == (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/**
  * @brief Macro to check GTZC TZSC securable peripherals in the register 2
  */
#define IS_GTZC_PERIPH_REG2(periph) (((0x1UL << ((periph)  % GTZC_REG_MAX_FIELD)) & LL_GTZC_GRP2_ALL) \
                                     == (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/**
  * @brief Macro to check the GTZC TZSC securable peripherals in the register 3
  */
#define IS_GTZC_PERIPH_REG3(periph) (((0x1UL << ((periph)  % GTZC_REG_MAX_FIELD)) & LL_GTZC_GRP3_ALL) \
                                     == (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/**
  * @brief Macro to check the GTZC TZSC securable peripherals in the register 4
  */
#define IS_GTZC_PERIPH_REG4(periph) (((0x1UL << ((periph)  % GTZC_REG_MAX_FIELD)) & LL_GTZC_GRP4_ALL) \
                                     == (0x1UL << ((periph) % GTZC_REG_MAX_FIELD)))

/**
  * @brief Macro to check TZSC securable peripherals
  */
#define IS_GTZC_TZSC_PERIPH(periph) (((periph) == HAL_GTZC_TZSC_PERIPH_ALL) ? 1U :                         \
                                     (((periph) < LL_GTZC_PERIPH_REG2) ? IS_GTZC_PERIPH_REG1(periph)       \
                                      : (((periph) < LL_GTZC_PERIPH_REG3) ? IS_GTZC_PERIPH_REG2(periph)    \
                                         : (((periph) < LL_GTZC_PERIPH_REG4) ? IS_GTZC_PERIPH_REG3(periph)  \
                                            : (0U == 1U)))))

/**
  * @brief Macro to check TZIC peripherals
  */
#define IS_GTZC_TZIC_PERIPH(periph) (((periph) == HAL_GTZC_TZIC_PERIPH_ALL) ? 1U :                             \
                                     (((periph) < LL_GTZC_PERIPH_REG2) ? IS_GTZC_PERIPH_REG1(periph)           \
                                      : (((periph) < LL_GTZC_PERIPH_REG3) ? IS_GTZC_PERIPH_REG2(periph)        \
                                         : (((periph) < LL_GTZC_PERIPH_REG4) ? IS_GTZC_PERIPH_REG3(periph)      \
                                            : (((periph & ~LL_GTZC_PERIPH_BIT_POSITION) == LL_GTZC_PERIPH_REG4)  \
                                               ? IS_GTZC_PERIPH_REG4(periph) : (0U == 1U))))))

/**
  * @brief Macro to check GTZC Secure attribute
  */
#define IS_GTZC_TZSC_LOCK_PERIPH(lock_periph) (((lock_periph) == HAL_GTZC1_PERIPH_ALL))

/**
  * @brief Macro to check the TZSC_MPCWM memory
  */
#define IS_GTZC_TZSC_MPCWM_MEMORY(mem) (((mem)  == HAL_GTZC_TZSC_MPCWM_XSPI1))

/**
  * @brief Macro to check the TZSC_MPCWM subregion
  */
#define IS_GTZC_TZSC_MPCWM_SUBREGION(subregion) (((subregion) == HAL_GTZC_TZSC_MPCWM_SUBREGION_A) \
                                                 || ((subregion) == HAL_GTZC_TZSC_MPCWM_SUBREGION_B))

/**
  * @brief Macro to check parameters in range of TZSC_MPCWM memory
  */
#define IS_TZSC_MPCWM_MEMORY_IN_RANGE(mem, offset, size) ((((offset) + (size)) <= GTZC_TZSC_MPCWM_RANGE_0))

/**
  * @brief Macro to check the TZSC_MPCWM memory granularity
  */
#define IS_TZSC_MPCWM_MEMORY_GRANULARITY(mem, offset, size) ((((offset) % GTZC_MPCWM_GRANULARITY_128KB) == 0U) \
                                                             && (((size) % GTZC_MPCWM_GRANULARITY_128KB) == 0U))

/**
  * @brief Macro to get the TZSC_MPCWM memory granularity
  */
#define GTZC_GET_TZSC_MPCWM_MEMORY_GRANULARITY(mem) (GTZC_MPCWM_GRANULARITY_128KB)

/**
  * @brief Macro to check parameters in range of TZSC_MPCWM region
  */
#define IS_TZSC_MPCWM_MEMORY_REGION_IN_RANGE(offset, size) \
  (((offset) + (size)) <= (0x10000000U))

/**
  * @brief Macro to check the MPCBB memory
  */
#if defined(SRAM3_BASE)
#define IS_GTZC_MPCBB_MEMORY(mem) (((mem)  == HAL_GTZC_MPCBB_SRAM1) \
                                   || ((mem) == HAL_GTZC_MPCBB_SRAM2) \
                                   || ((mem) == HAL_GTZC_MPCBB_SRAM3))
#else
#define IS_GTZC_MPCBB_MEMORY(mem) (((mem)  == HAL_GTZC_MPCBB_SRAM1) \
                                   || ((mem) == HAL_GTZC_MPCBB_SRAM2))
#endif /* SRAM3_BASE */

/**
  * @brief Macro to check parameters in range of MPCBB memory
  */
#if defined (SRAM3_BASE)
#define IS_MPCBB_MEMORY_IN_RANGE(mem, offset, size) \
  (((mem) == HAL_GTZC_MPCBB_SRAM1) ? (((offset) + (size)) <= SRAM1_SIZE)    :\
   ((mem) == HAL_GTZC_MPCBB_SRAM2) ? (((offset) + (size)) <= SRAM2_SIZE)    :\
   (((offset) + (size)) <= SRAM3_SIZE))
#else
#define IS_MPCBB_MEMORY_IN_RANGE(mem, offset, size) \
  (((mem) == HAL_GTZC_MPCBB_SRAM1) ? (((offset) + (size)) <= SRAM1_SIZE)    :\
   (((offset) + (size)) <= SRAM2_SIZE))
#endif /* SRAM3_BASE */

/**
  * @brief Macro to get MPCBB memory Super Block size
  */
#define GTZC_GET_MPCBB_SUPER_BLOCK(mem) \
  (((mem) == HAL_GTZC_MPCBB_SRAM1) ? GTZC_MAX_SUPER_BLOCK_1 :\
   (((mem) == HAL_GTZC_MPCBB_SRAM2) ? GTZC_MAX_SUPER_BLOCK_2 :\
    GTZC_MAX_SUPER_BLOCK_1))

/**
  * @brief Macro to check block size of MPCBB memory
  */
#define IS_MPCBB_MEMORY_BLOCK_GRANULARITY(mem, offset, size) ((((offset) % GTZC_MPCBB_BLOCK_SIZE) == 0U) \
                                                              &&(((size) % GTZC_MPCBB_BLOCK_SIZE) == 0U))

/**
  * @brief Macro to check super_block granularity of MPCBB memory
  */
#define IS_MPCBB_MEMORY_SUPER_BLOCK_GRANULARITY(mem, offset, size) ((((offset) % GTZC_MPCBB_SUPER_BLOCK_SIZE) == 0U) \
                                                                    && (((size) % GTZC_MPCBB_SUPER_BLOCK_SIZE) == 0U))

/**
  * @brief Macro to check mem clock sec state
  */
#define IS_GTZC_MPCBB_MEM_CLK_SEC_INVERT_STATE(clk_sec_invert_state) \
  ((clk_sec_invert_state == HAL_GTZC_TZSC_CLK_SEC_NOT_INVERTED) \
   || (clk_sec_invert_state == HAL_GTZC_TZSC_CLK_SEC_INVERTED))


/**
  * @}
  */
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup GTZC_Exported_Functions
  * @{
  */

/** @addtogroup GTZC_Exported_Functions_Group1
  * @{
This section provides functions for configuring the security and privilege attributes of securable peripherals:

  Security and privilege attributes configuration for TZSC peripherals:

  - Call HAL_GTZC_TZSC_SetPeriphSecAttr()  function to set the security attribute of a TZSC securable peripheral.
  - Call HAL_GTZC_TZSC_GetPeriphSecAttr()  function to get the security attribute of a TZSC securable peripheral.

  - Call HAL_GTZC_TZSC_SetPeriphPrivAttr() function to set the privilege attribute of a TZSC securable peripheral.
  - Call HAL_GTZC_TZSC_GetPeriphPrivAttr() function to get the privilege attribute of a TZSC securable peripheral.

  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set TZSC securable peripheral security attribute.
  * @param  periph   Peripheral identifier\n
  *                  This parameter is an element of @ref hal_gtzc_tzsc_periph_t enumeration.
  * @param  sec_attr Security attribute\n
  *                  This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  * @note   Secure and non-secure attributes can only be set from the secure state.
  * @note   Default state of securable peripheral security attributes is non-secure access allowed.
  * @retval HAL_OK    TZSC securable peripheral security attribute has been correctly configured.
  * @retval HAL_ERROR This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZSC_SetPeriphSecAttr(hal_gtzc_tzsc_periph_t periph, hal_gtzc_sec_attr_t sec_attr)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_PERIPH((uint32_t)periph));
  ASSERT_DBG_PARAM(IS_GTZC_SEC_ATTR(sec_attr));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (periph == HAL_GTZC_TZSC_PERIPH_ALL)
  {
    STM32_MODIFY_REG(GTZC1_TZSC1_PERIPH->SECCFGR[0], LL_GTZC_GRP1_ALL,
                     ((uint32_t)sec_attr * LL_GTZC_GRP1_ALL));
    STM32_MODIFY_REG(GTZC1_TZSC1_PERIPH->SECCFGR[1], LL_GTZC_GRP2_ALL,
                     ((uint32_t)sec_attr * LL_GTZC_GRP2_ALL));
    STM32_MODIFY_REG(GTZC1_TZSC1_PERIPH->SECCFGR[2], LL_GTZC_GRP3_ALL,
                     ((uint32_t)sec_attr * LL_GTZC_GRP3_ALL));
  }
  else
  {
    LL_GTZC_TZSC_SetPeriphSecAttr(GTZC1_TZSC1_PERIPH, (uint32_t)periph, (uint32_t)sec_attr);
  }

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Set TZSC securable peripheral privilege attribute.
  * @param  periph    Peripheral identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_periph_t enumeration.
  * @param  priv_attr Privilege attribute\n
  *                   This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  * @note   Privilege and non-privilege attributes can only be set from the privilege state.
  * @note   Default state of securable peripheral privilege attributes is unprivileged access allowed.
  * @retval HAL_OK    TZSC securable peripheral privilege attribute has been correctly configured.
  * @retval HAL_ERROR This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZSC_SetPeriphPrivAttr(hal_gtzc_tzsc_periph_t periph, hal_gtzc_priv_attr_t priv_attr)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_PERIPH((uint32_t)periph));
  ASSERT_DBG_PARAM(IS_GTZC_PRIV_ATTR(priv_attr));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (periph == HAL_GTZC_TZSC_PERIPH_ALL)
  {
    STM32_MODIFY_REG(GTZC1_TZSC1_PERIPH->PRIVCFGR[0], LL_GTZC_GRP1_ALL,
                     ((uint32_t)priv_attr * LL_GTZC_GRP1_ALL));
    STM32_MODIFY_REG(GTZC1_TZSC1_PERIPH->PRIVCFGR[1], LL_GTZC_GRP2_ALL,
                     ((uint32_t)priv_attr * LL_GTZC_GRP2_ALL));
    STM32_MODIFY_REG(GTZC1_TZSC1_PERIPH->PRIVCFGR[2], LL_GTZC_GRP3_ALL,
                     ((uint32_t)priv_attr * LL_GTZC_GRP3_ALL));
  }
  else
  {
    LL_GTZC_TZSC_SetPeriphPrivAttr(GTZC1_TZSC1_PERIPH, (uint32_t)periph, (uint32_t)priv_attr);
  }

  return HAL_OK;
}

/**
  * @brief  Get the security attribute of a TZSC securable peripheral.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_tzsc_periph_t enumeration.
  * @retval Security attribute\n
  *         This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  */
hal_gtzc_sec_attr_t HAL_GTZC_TZSC_GetPeriphSecAttr(hal_gtzc_tzsc_periph_t periph)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_PERIPH((uint32_t)periph));
  ASSERT_DBG_PARAM(periph != HAL_GTZC_TZSC_PERIPH_ALL);

  return (hal_gtzc_sec_attr_t)LL_GTZC_TZSC_GetPeriphSecAttr(GTZC1_TZSC1_PERIPH, (uint32_t)periph);
}

/**
  * @brief  Get the privilege attribute of a TZSC securable peripheral.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_tzsc_periph_t enumeration.
  * @retval Privilege attribute\n
  *         This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  */
hal_gtzc_priv_attr_t HAL_GTZC_TZSC_GetPeriphPrivAttr(hal_gtzc_tzsc_periph_t periph)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_PERIPH((uint32_t)periph));
  ASSERT_DBG_PARAM(periph != HAL_GTZC_TZSC_PERIPH_ALL);

  return (hal_gtzc_priv_attr_t)LL_GTZC_TZSC_GetPeriphPrivAttr(GTZC1_TZSC1_PERIPH, (uint32_t)periph);
}

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group2
  * @{
This section provides functions allowing to configure the lock of TZSC registers configuration:

  - Call HAL_GTZC_TZSC_LockConfig() function to set the lock on the configuration of TZSC registers.
  - Call HAL_GTZC_TZSC_IsLockedConfig() function to get the lock status of TZSC registers configuration.

  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief Set the lock on the configuration of TZSC registers.
  * @param periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_lock_periph_t enumeration.
  * @return HAL_OK if the lock was successfully set
  * @return HAL_ERROR otherwise.
  */
hal_status_t HAL_GTZC_TZSC_LockConfig(hal_gtzc_lock_periph_t periph)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_LOCK_PERIPH((uint32_t)periph));
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_GTZC_TZSC_LockConfig((GTZC_TZSC_Periph_TypeDef *)(uint32_t)periph);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief Get the lock status of TZSC registers configuration.
  * @param periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_lock_periph_t enumeration.
  * @return hal_gtzc_lock_status_t Lock status of TZSC registers configuration\n
  *         This parameter is an element of @ref hal_gtzc_lock_status_t enumeration.
  */
hal_gtzc_lock_status_t HAL_GTZC_TZSC_IsLockedConfig(hal_gtzc_lock_periph_t periph)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_LOCK_PERIPH((uint32_t)periph));

  return (hal_gtzc_lock_status_t)LL_GTZC_TZSC_IsLockedConfig((GTZC_TZSC_Periph_TypeDef *)(uint32_t)periph);
}

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group3
  * @{
This section provides functions allowing to configure subregion boundaries of TZSC_MPCWM memory:

 - Call HAL_GTZC_TZSC_MPCWM_EnableSubRegion() function to enable a TZSC_MPCWM subregion.
 - Call HAL_GTZC_TZSC_MPCWM_DisableSubRegion() function to disable a TZSC_MPCWM subregion.
 - Call HAL_GTZC_TZSC_MPCWM_IsEnabledSubRegion() function to check if a TZSC_MPCWM subregion is enabled or disabled.
 - Call HAL_GTZC_TZSC_MPCWM_SetSubRegionBoundaries() function to set the boundaries of a TZSC_MPCWM subregion.
 - Call HAL_GTZC_TZSC_MPCWM_GetSubRegionBoundaries() function to get the boundaries of a TZSC_MPCWM subregion.

  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable TZSC_MPCWM subregion.
  * @param  memory   TZSC_MPCWM memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion   Subregion identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @retval HAL_OK      Subregion boundaries has been correctly configured.
  */
hal_status_t HAL_GTZC_TZSC_MPCWM_EnableSubRegion(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                 hal_gtzc_tzsc_mpcwm_subregion_t subregion)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));

  GTZC_TZSC_MPCWM_TypeDef *p_mem;
  p_mem = (GTZC_TZSC_MPCWM_TypeDef *)((uint32_t)memory);

  LL_GTZC_TZSC_MPCWM_EnableSubRegion(p_mem, (uint32_t)subregion);

  return HAL_OK;
}

/**
  * @brief  Disable TZSC_MPCWM subregion.
  * @param  memory   TZSC_MPCWM memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion   Subregion identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @retval HAL_OK      Subregion boundaries has been correctly configured.
  */
hal_status_t HAL_GTZC_TZSC_MPCWM_DisableSubRegion(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                  hal_gtzc_tzsc_mpcwm_subregion_t subregion)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));

  GTZC_TZSC_MPCWM_TypeDef *p_mem;
  p_mem = (GTZC_TZSC_MPCWM_TypeDef *)((uint32_t)memory);

  LL_GTZC_TZSC_MPCWM_DisableSubRegion(p_mem, (uint32_t)subregion);

  return HAL_OK;
}

/**
  * @brief  Check if TZSC_MPCWM subregion is enabled.
  * @param  memory   TZSC_MPCWM memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion   Subregion identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @retval Subregion status.
  */
hal_gtzc_tzsc_mpcwm_subregion_status_t HAL_GTZC_TZSC_MPCWM_IsEnabledSubRegion(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                                              hal_gtzc_tzsc_mpcwm_subregion_t subregion)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));

  GTZC_TZSC_MPCWM_TypeDef *p_mem;
  p_mem = (GTZC_TZSC_MPCWM_TypeDef *)((uint32_t)memory);

  return (hal_gtzc_tzsc_mpcwm_subregion_status_t)LL_GTZC_TZSC_MPCWM_IsEnabledSubRegion(p_mem, (uint32_t)subregion);
}

/**
  * @brief  Set TZSC_MPCWM subregion boundaries.
  * @param  memory   TZSC_MPCWM memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion   Subregion identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @param  offset_byte Offset in bytes of the subregion.
  * @param  size_byte   Length in bytes of the subregion to be configured.
  * @retval HAL_OK      Subregion boundaries has been correctly configured.
  * @retval HAL_ERROR   This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZSC_MPCWM_SetSubRegionBoundaries(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                        hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                        uint32_t offset_byte,
                                                        uint32_t size_byte)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));
  ASSERT_DBG_PARAM(IS_TZSC_MPCWM_MEMORY_GRANULARITY(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_TZSC_MPCWM_MEMORY_REGION_IN_RANGE(offset_byte, size_byte));

  GTZC_TZSC_MPCWM_TypeDef *p_mem;
  p_mem = (GTZC_TZSC_MPCWM_TypeDef *)((uint32_t)memory);
  uint32_t granularity = GTZC_GET_TZSC_MPCWM_MEMORY_GRANULARITY(memory);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */


  LL_GTZC_TZSC_MPCWM_ConfigSubRegionArea(p_mem,
                                         (uint32_t)subregion,
                                         offset_byte / granularity,
                                         size_byte / granularity);

  return HAL_OK;
}

/**
  * @brief  Get TZSC_MPCWM subregion boundaries.
  * @param  memory   TZSC_MPCWM memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion   Subregion identifier\n
  *                     This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @param  offset_byte Pointer to store the offset in bytes of the subregion.
  * @param  size_byte   Pointer to store the length in bytes of the subregion.
  */
void HAL_GTZC_TZSC_MPCWM_GetSubRegionBoundaries(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                uint32_t *offset_byte,
                                                uint32_t *size_byte)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));
  ASSERT_DBG_PARAM(offset_byte != NULL);
  ASSERT_DBG_PARAM(size_byte != NULL);
  uint32_t granularity = GTZC_GET_TZSC_MPCWM_MEMORY_GRANULARITY(memory);

  GTZC_TZSC_MPCWM_TypeDef *p_mem;
  p_mem = (GTZC_TZSC_MPCWM_TypeDef *)((uint32_t)memory);

  *offset_byte = LL_GTZC_TZSC_MPCWM_GetSubRegionStartAddr(p_mem, (uint32_t)subregion) * granularity;
  *size_byte = LL_GTZC_TZSC_MPCWM_GetSubRegionLength(p_mem, (uint32_t)subregion) * granularity;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group4
  * @{
This section provides functions allowing to configure the security and privilege attributes of a TZSC_MPCWM subregion:

  - Call HAL_GTZC_TZSC_MPCWM_SetSubRegionSecAttr()  function to set the security attribute of a TZSC_MPCWM subregion.
  - Call HAL_GTZC_TZSC_MPCWM_GetSubRegionSecAttr()  function to get the security attribute of a TZSC_MPCWM subregion.

  - Call HAL_GTZC_TZSC_MPCWM_SetSubRegionPrivAttr() function to set the privilege attribute of a TZSC_MPCWM subregion.
  - Call HAL_GTZC_TZSC_MPCWM_GetSubRegionPrivAttr() function to get the privilege attribute of a TZSC_MPCWM subregion.
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set TZSC_MPCWM subregion security attribute.
  * @param  memory TZSC_MPCWM memory identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion Subregion identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @param  sec_attr  Security attribute\n
  *                   This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  * @retval HAL_OK    Subregion security attribute has been correctly configured.
  * @retval HAL_ERROR This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZSC_MPCWM_SetSubRegionSecAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                     hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                     hal_gtzc_sec_attr_t sec_attr)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));
  ASSERT_DBG_PARAM(IS_GTZC_SEC_ATTR(sec_attr));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_GTZC_TZSC_MPCWM_SetSubRegionSecAttr((GTZC_TZSC_MPCWM_TypeDef *)(uint32_t)memory, (uint32_t)subregion,
                                         (uint32_t)sec_attr);

  return HAL_OK;
}

/**
  * @brief  Set TZSC_MPCWM subregion privilege attribute.
  * @param  memory TZSC_MPCWM memory identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion Subregion identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @param  priv_attr Privilege attribute\n
  *                   This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  * @retval HAL_OK    Subregion privilege attribute has been correctly configured.
  * @retval HAL_ERROR This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZSC_MPCWM_SetSubRegionPrivAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                      hal_gtzc_tzsc_mpcwm_subregion_t subregion,
                                                      hal_gtzc_priv_attr_t priv_attr)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));
  ASSERT_DBG_PARAM(IS_GTZC_PRIV_ATTR(priv_attr));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_GTZC_TZSC_MPCWM_SetSubRegionPrivAttr((GTZC_TZSC_MPCWM_TypeDef *)(uint32_t)memory, (uint32_t)subregion,
                                          (uint32_t)priv_attr);

  return HAL_OK;
}

/**
  * @brief  Get TZSC_MPCWM subregion security attribute.
  * @param  memory TZSC_MPCWM memory identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion Subregion identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @retval Security attribute\n
  *         This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  */
hal_gtzc_sec_attr_t HAL_GTZC_TZSC_MPCWM_GetSubRegionSecAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                            hal_gtzc_tzsc_mpcwm_subregion_t subregion)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));

  return (hal_gtzc_sec_attr_t)LL_GTZC_TZSC_MPCWM_GetSubRegionSecAttr((GTZC_TZSC_MPCWM_TypeDef *)(uint32_t)memory,
                                                                     (uint32_t)subregion);
}

/**
  * @brief  Get TZSC_MPCWM subregion privilege attribute.
  * @param  memory TZSC_MPCWM memory identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion Subregion identifier\n
  *                   This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @retval Privilege attribute\n
  *         This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  */
hal_gtzc_priv_attr_t HAL_GTZC_TZSC_MPCWM_GetSubRegionPrivAttr(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                              hal_gtzc_tzsc_mpcwm_subregion_t subregion)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));

  return (hal_gtzc_priv_attr_t)LL_GTZC_TZSC_MPCWM_GetSubRegionPrivAttr((GTZC_TZSC_MPCWM_TypeDef *)(uint32_t)memory,
                                                                       (uint32_t)subregion);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @}
  */


/** @addtogroup GTZC_Exported_Functions_Group5
  * @{
This section provides functions allowing to lock the configuration of a TZSC_MPCWM subregion:

  - Call HAL_GTZC_TZSC_MPCWM_LockSubRegionConfig() function to lock the configuration of a TZSC_MPCWM subregion.
  - Call HAL_GTZC_TZSC_MPCWM_IsLockedSubRegionConfig() function to check if the configuration of a TZSC_MPCWM subregion
    is locked or unlocked.
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock TZSC_MPCWM subregion configurations.
  * @param  memory  TZSC_MPCWM memory identifier\n
  *                    This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion  Subregion identifier\n
  *                    This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @note   This function locks the configurations of TZSC_MPCWM_REGx_zCFGR, TZSC_MPCWM_REGx_zSTARTR, and
  *         TZSC_MPCWM_REGx_zENDR registers until the next TZSC_MPCWM reset.
  * @retval HAL_OK     TZSC_MPCWM subregion configuration has been successfully locked.
  * @retval HAL_ERROR  This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZSC_MPCWM_LockSubRegionConfig(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                     hal_gtzc_tzsc_mpcwm_subregion_t subregion)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_GTZC_TZSC_MPCWM_LockSubRegion((GTZC_TZSC_MPCWM_TypeDef *)(uint32_t)memory, (uint32_t)subregion);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get lock state of TZSC_MPCWM subregion configurations.
  * @param  memory  TZSC_MPCWM memory identifier\n
  *                    This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_memory_t enumeration.
  * @param  subregion  Subregion identifier\n
  *                    This parameter is an element of @ref hal_gtzc_tzsc_mpcwm_subregion_t enumeration.
  * @retval HAL_GTZC_LOCKED   TZSC_MPCWM subregion configurations are locked.
  * @retval HAL_GTZC_UNLOCKED TZSC_MPCWM subregion configurations are unlocked.
  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_gtzc_lock_status_t HAL_GTZC_TZSC_MPCWM_IsLockedSubRegionConfig(hal_gtzc_tzsc_mpcwm_memory_t memory,
                                                                   hal_gtzc_tzsc_mpcwm_subregion_t subregion)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_TZSC_MPCWM_SUBREGION(subregion));

  return (hal_gtzc_lock_status_t)LL_GTZC_TZSC_MPCWM_IsLockedSubRegion
         ((GTZC_TZSC_MPCWM_TypeDef *)(uint32_t)memory, (uint32_t)subregion);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group6
  * @{
This section provides functions allowing to configure the security and privilege attributes of MPCBB memory block:

  - Call HAL_GTZC_MPCBB_SetSecAttrByBlock() function to set the security attribute of a set of MPCBB memory blocks.
  - Call HAL_GTZC_MPCBB_GetSecAttrByBlock() function to get the security attribute of a MPCBB memory block.

  - Call HAL_GTZC_MPCBB_SetPrivAttrByBlock() function to set the privilege attribute of a set of MPCBB memory blocks.
  - Call HAL_GTZC_MPCBB_GetPrivAttrByBlock() function to get the privilege attribute of a MPCBB memory block.

  - Call HAL_GTZC_MPCBB_SetSecAttrByAddr() function to set the security attribute of a set of MPCBB memory blocks based
    on the address.
  - Call HAL_GTZC_MPCBB_GetSecAttrByAddr() function to get the security attribute of a set of MPCBB memory blocks based
    on the address.

  - Call HAL_GTZC_MPCBB_SetPrivAttrByAddr() function to set the privilege attribute of a set of MPCBB memory blocks
    based on the address.
  - Call HAL_GTZC_MPCBB_GetPrivAttrByAddr() function to get the privilege attribute of a set of MPCBB memory blocks
    based on the address.

  */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set MPCBB memory block security attribute.
  * @param  memory   MPCBB memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  start_block Memory start block.
  * @param  block_nbr   Memory block number.
  * @param  sec_attr    Security attribute\n
  *                     This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  * @retval HAL_OK      MPCBB memory security attribute has been correctly configured.
  * @retval HAL_ERROR   This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_MPCBB_SetSecAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t start_block, uint32_t block_nbr,
                                              hal_gtzc_sec_attr_t sec_attr)
{
  uint32_t block_idx;
  uint32_t block_cnt;
  uint32_t super_block_idx;
  uint32_t block_msk = 0U;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_SEC_ATTR(sec_attr));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, (start_block * GTZC_MPCBB_BLOCK_SIZE),
                                            (block_nbr * GTZC_MPCBB_BLOCK_SIZE)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  block_idx = start_block % GTZC_BLOCKS_MAX_SUPER_BLOCK;
  block_cnt = block_nbr;
  super_block_idx = start_block / GTZC_BLOCKS_MAX_SUPER_BLOCK;

  while (block_cnt != 0U)
  {
    while ((block_idx < GTZC_BLOCKS_MAX_SUPER_BLOCK) && (block_cnt != 0U))
    {
      block_msk |= (1UL << block_idx);
      block_idx++;
      block_cnt--;
    }

    LL_GTZC_MPCBB_SetBlockSecAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory, super_block_idx, block_msk,
                                  (uint32_t)sec_attr);

    block_msk = 0U;
    block_idx = 0U;
    super_block_idx++;
  }

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Set MPCBB memory block privilege attribute.
  * @param  memory   MPCBB memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  start_block Memory start block.
  * @param  block_nbr   Memory block number.
  * @param  priv_attr   Privilege attribute\n
  *                     This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  * @retval HAL_OK      MPCBB memory privilege attribute has been correctly configured.
  * @retval HAL_ERROR   This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_MPCBB_SetPrivAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t start_block,
                                               uint32_t block_nbr, hal_gtzc_priv_attr_t priv_attr)
{
  uint32_t block_idx;
  uint32_t block_cnt;
  uint32_t super_block_idx;
  uint32_t block_msk = 0U;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_PRIV_ATTR(priv_attr));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, (start_block * GTZC_MPCBB_BLOCK_SIZE),
                                            (block_nbr * GTZC_MPCBB_BLOCK_SIZE)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  block_idx = start_block % GTZC_BLOCKS_MAX_SUPER_BLOCK;
  block_cnt = block_nbr;
  super_block_idx = start_block / GTZC_BLOCKS_MAX_SUPER_BLOCK;

  while (block_cnt != 0U)
  {
    while ((block_idx < GTZC_BLOCKS_MAX_SUPER_BLOCK) && (block_cnt != 0U))
    {
      block_msk |= (1UL << block_idx);
      block_idx++;
      block_cnt--;
    }

    LL_GTZC_MPCBB_SetBlockPrivAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory, super_block_idx, block_msk,
                                   (uint32_t)priv_attr);

    block_msk = 0U;
    block_idx = 0U;
    super_block_idx++;
  }

  return HAL_OK;
}

/**
  * @brief  Get MPCBB memory block security attribute.
  * @param  memory  MPCBB memory identifier\n
  *                 This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  block   Memory block.
  * @retval Security attribute\n
  *         This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  */
hal_gtzc_sec_attr_t HAL_GTZC_MPCBB_GetSecAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t block)
{
  uint32_t super_block;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, (block * GTZC_MPCBB_BLOCK_SIZE), 0U));


  super_block = block / GTZC_BLOCKS_MAX_SUPER_BLOCK;

  return (hal_gtzc_sec_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlockSecAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory,
                                                                             super_block) \
                                          & (1UL << (block % GTZC_BLOCKS_MAX_SUPER_BLOCK))) \
                                         >> (block % GTZC_BLOCKS_MAX_SUPER_BLOCK));
}

/**
  * @brief  Get MPCBB memory block privilege attribute.
  * @param  memory MPCBB memory identifier\n
  *                This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  block  Memory block.
  * @retval Privilege attribute\n
  *         This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  */
hal_gtzc_priv_attr_t HAL_GTZC_MPCBB_GetPrivAttrByBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t block)
{
  uint32_t super_block;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, (block * GTZC_MPCBB_BLOCK_SIZE), 0U));

  super_block = block / GTZC_BLOCKS_MAX_SUPER_BLOCK;

  return (hal_gtzc_priv_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlockPrivAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory,
                                                                               super_block) \
                                           & (1UL << (block % GTZC_BLOCKS_MAX_SUPER_BLOCK))) \
                                          >> (block % GTZC_BLOCKS_MAX_SUPER_BLOCK));
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set MPCBB memory block security attribute depending on the input address.
  * @param  memory   MPCBB memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  offset_byte Offset in byte of the MPCBB memory area.
  * @param  size_byte   Length in byte of the MPCBB memory area to be protected.
  * @param  sec_attr    Security attribute\n
  *                     This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  * @note The configuration granularity is by block:
  *       - If the provided offset_byte is not aligned to the start of a block, the entire block containing this offset
  *         will be configured.
  *       - Similarly, if the range defined by offset_byte + size_byte does not end on a block boundary, the entire
  *         block containing the end address will be configured.
  *       - As a result, the function can configure more memory than explicitly specified.
  *       - Users must take this granularity into consideration and, if necessary, ensure that offset_byte and
  *         size_byte are aligned to block boundaries or apply
  *         appropriate padding to fully cover the intended blocks and avoid unintended overlapping with adjacent
  *  blocks.
  * @retval HAL_OK      Memory security attribute has been correctly configured.
  * @retval HAL_ERROR   This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_MPCBB_SetSecAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte, uint32_t size_byte,
                                             hal_gtzc_sec_attr_t sec_attr)
{
  uint32_t block_idx;
  uint32_t block_cnt;
  uint32_t super_block_idx;
  uint32_t block_msk = 0U;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_SEC_ATTR(sec_attr));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_BLOCK_GRANULARITY(memory, offset_byte, size_byte));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  block_idx  = (offset_byte / GTZC_MPCBB_BLOCK_SIZE) % GTZC_BLOCKS_MAX_SUPER_BLOCK;
  block_cnt  = size_byte / GTZC_MPCBB_BLOCK_SIZE;
  super_block_idx = offset_byte / GTZC_MPCBB_SUPER_BLOCK_SIZE;

  while (block_cnt != 0U)
  {
    while ((block_idx < GTZC_BLOCKS_MAX_SUPER_BLOCK) && (block_cnt != 0U))
    {
      block_msk |= (1UL << block_idx);
      block_idx++;
      block_cnt--;
    }

    LL_GTZC_MPCBB_SetBlockSecAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory, super_block_idx, block_msk,
                                  (uint32_t)sec_attr);

    block_msk = 0U;
    block_idx = 0U;
    super_block_idx++;
  }

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Set MPCBB memory block privilege attribute depending on the input address.
  * @param  memory   MPCBB memory identifier\n
  *                     This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  offset_byte Offset in byte of the MPCBB memory area.
  * @param  size_byte   Length in byte of the MPCBB memory area to be protected.
  * @param  priv_attr   Privilege attribute\n
  *                     This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  * @note The configuration granularity is by block:
  *       - If the provided offset_byte is not aligned to the start of a block, the entire block containing this offset
  *         will be configured.
  *       - Similarly, if the range defined by offset_byte + size_byte does not end on a block boundary, the entire
  *         block containing the end address will be configured.
  *       - As a result, the function can configure more memory than explicitly specified.
  *       - Users must take this granularity into consideration and, if necessary, ensure that offset_byte and
  *         size_byte are aligned to block boundaries or apply
  *         appropriate padding to fully cover the intended blocks and avoid unintended overlapping with adjacent
  *         blocks.
  * @retval HAL_OK      Memory privilege attribute has been correctly configured.
  * @retval HAL_ERROR   This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_MPCBB_SetPrivAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte, uint32_t size_byte,
                                              hal_gtzc_priv_attr_t priv_attr)
{
  uint32_t block_idx;
  uint32_t block_cnt;
  uint32_t super_block_idx;
  uint32_t block_msk = 0U;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_PRIV_ATTR(priv_attr));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_BLOCK_GRANULARITY(memory, offset_byte, size_byte));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  block_idx  = (offset_byte / GTZC_MPCBB_BLOCK_SIZE) % GTZC_BLOCKS_MAX_SUPER_BLOCK;
  block_cnt  = size_byte / GTZC_MPCBB_BLOCK_SIZE;
  super_block_idx = offset_byte / GTZC_MPCBB_SUPER_BLOCK_SIZE;

  while (block_cnt != 0U)
  {
    while ((block_idx < GTZC_BLOCKS_MAX_SUPER_BLOCK) && (block_cnt != 0U))
    {
      block_msk |= (1UL << block_idx);
      block_idx++;
      block_cnt--;
    }

    LL_GTZC_MPCBB_SetBlockPrivAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory, super_block_idx, block_msk,
                                   (uint32_t)priv_attr);

    block_msk = 0U;
    block_idx = 0U;
    super_block_idx++;
  }

  return HAL_OK;
}

/**
  * @brief  Get a MPCBB memory block security attribute depending on the input address.
  * @param  memory MPCBB memory identifier\n
  *                This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  offset_byte Offset in bytes of the MPCBB memory.
  * @retval Security attribute\n
  *         This parameter is an element of @ref hal_gtzc_sec_attr_t enumeration.
  * @note   The security attribute is retrieved at block granularity:
  *         - The offset_byte must be aligned to the start of a block to ensure accurate attribute retrieval.
  *         - If offset_byte is not block-aligned, the attribute returned corresponds to the block containing the
  *           offset.
  */
hal_gtzc_sec_attr_t HAL_GTZC_MPCBB_GetSecAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte)
{
  uint32_t super_block;
  uint32_t block;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, offset_byte, 0U));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_BLOCK_GRANULARITY(memory, offset_byte, 0U));

  super_block = offset_byte / GTZC_MPCBB_SUPER_BLOCK_SIZE;
  block  = (offset_byte / GTZC_MPCBB_BLOCK_SIZE) % GTZC_BLOCKS_MAX_SUPER_BLOCK;

  return (hal_gtzc_sec_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlockSecAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory,
                                                                             super_block) \
                                          & (1UL << block)) >> block);
}
/**
  * @brief  Get a MPCBB memory block privilege attribute depending on the input address.
  * @param  memory MPCBB memory identifier\n
  *                This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  offset_byte Offset in bytes of the MPCBB memory.
  * @retval Privilege attribute\n
  *         This parameter is an element of @ref hal_gtzc_priv_attr_t enumeration.
  * @note   The privilege attribute is retrieved at block granularity:
  *         - The offset_byte must be aligned to the start of a block to ensure accurate attribute retrieval.
  *         - If offset_byte is not block-aligned, the attribute returned corresponds to the block containing the
  *           offset.
  */
hal_gtzc_priv_attr_t HAL_GTZC_MPCBB_GetPrivAttrByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte)
{
  uint32_t super_block;
  uint32_t block;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, offset_byte, 0U));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_BLOCK_GRANULARITY(memory, offset_byte, 0U));

  super_block = offset_byte / GTZC_MPCBB_SUPER_BLOCK_SIZE;
  block  = (offset_byte / GTZC_MPCBB_BLOCK_SIZE) % GTZC_BLOCKS_MAX_SUPER_BLOCK;

  return (hal_gtzc_priv_attr_t)(uint32_t)((LL_GTZC_MPCBB_GetSuperBlockPrivAttr((GTZC_MPCBB_TypeDef *)(uint32_t)memory,
                                                                               super_block) \
                                           & (1UL << block)) >> block);
}

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group7
  * @{
This section provides functions allowing to enable or disable the secure read/write data accesses to non-secure blocks
and super_blocks of MPCBB memory:

  - Call HAL_GTZC_MPCBB_EnableSecToNSecRdWrAccess() function to enable secure read/write data accesses to non-secure
    blocks and super_blocks.
  - Call HAL_GTZC_MPCBB_DisableSecToNSecRdWrAccess() function to disable secure read/write data accesses to non-secure
    blocks and super_blocks.
  - Call HAL_GTZC_MPCBB_IsEnabledSecToNSecRdWrAccess() function to check if secure read/write data accesses to
    non-secure blocks and super_blocks is enabled or disabled.

  - Call HAL_GTZC_MPCBB_SetClkSecStateInvertion() function to set the clock security state inversion for MPCBB memory.
  - Call HAL_GTZC_MPCBB_GetClkSecStateInvertion() function to get the clock security state inversion for MPCBB memory.

  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable secure read/write data accesses to non-secure blocks and super_blocks of MPCBB memory.
  * @param  memory  MPCBB memory identifier\n
  *                 This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @retval HAL_OK  Secure read/write data accesses to non-secure blocks and super_blocks have been enabled.
  */
hal_status_t HAL_GTZC_MPCBB_EnableSecToNSecRdWrAccess(hal_gtzc_mpcbb_memory_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));

  LL_GTZC_MPCBB_EnableSecToNSecRdWrAccess((GTZC_MPCBB_TypeDef *)(uint32_t)memory);

  return HAL_OK;
}

/**
  * @brief  Disable secure read/write data accesses to non-secure blocks and super_blocks of MPCBB memory.
  * @param  memory  MPCBB memory identifier\n
  *                 This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @retval HAL_OK  Secure read/write data accesses to non-secure blocks and super_blocks have been disabled.
  */
hal_status_t HAL_GTZC_MPCBB_DisableSecToNSecRdWrAccess(hal_gtzc_mpcbb_memory_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));

  LL_GTZC_MPCBB_DisableSecToNSecRdWrAccess((GTZC_MPCBB_TypeDef *)(uint32_t)memory);

  return HAL_OK;
}

/**
  * @brief  Check if secure read/write data accesses to non-secure blocks and super_blocks of MPCBB memory is enabled.
  * @param  memory  MPCBB memory identifier\n
  *                 This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @retval HAL_GTZC_MPCBB_SEC_TO_NSEC_ACCESS_ENABLED  Secure read/write data accesses to non-secure blocks and
  *         super_blocks are enabled.
  * @retval HAL_GTZC_MPCBB_SEC_TO_NSEC_ACCESS_DISABLED Secure read/write data accesses to non-secure blocks and
  *         super_blocks are disabled.
  */
hal_gtzc_mpcbb_sec_to_nsec_access_status_t HAL_GTZC_MPCBB_IsEnabledSecToNSecRdWrAccess(hal_gtzc_mpcbb_memory_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));

  return (hal_gtzc_mpcbb_sec_to_nsec_access_status_t)LL_GTZC_MPCBB_IsEnabledSecToNSecRdWrAccess
         ((GTZC_MPCBB_TypeDef *)(uint32_t)memory);
}

/**
  * @brief  Set the clock security state inversion for MPCBB memory.
  * @param  memory  MPCBB memory identifier\n
  *                 This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  clk_sec_invert_state Clock security state inversion\n
  *                              This parameter is an element of @ref hal_gtzc_mpcbb_clk_sec_invert_state_t enumeration.
  * @retval HAL_OK  Clock security state inversion has been set.
  */
hal_status_t HAL_GTZC_MPCBB_SetClkSecStateInvertion(hal_gtzc_mpcbb_memory_t memory,
                                                    hal_gtzc_mpcbb_clk_sec_invert_state_t clk_sec_invert_state)
{
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEM_CLK_SEC_INVERT_STATE(clk_sec_invert_state));

  LL_GTZC_MPCBB_SetClockSecurityState((GTZC_MPCBB_TypeDef *)(uint32_t)memory, (uint32_t)clk_sec_invert_state);

  return HAL_OK;
}

/**
  * @brief  Get the clock security state inversion for MPCBB memory.
  * @param  memory  MPCBB memory identifier\n
  *                 This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @retval HAL_GTZC_MPCBB_CLK_SEC_NOT_INVERTED  Clock security state is not inverted.
  * @retval HAL_GTZC_MPCBB_CLK_SEC_INVERTED      Clock security state is inverted.
  */
hal_gtzc_mpcbb_clk_sec_invert_state_t  HAL_GTZC_MPCBB_GetClkSecStateInvertion(hal_gtzc_mpcbb_memory_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));

  return (hal_gtzc_mpcbb_clk_sec_invert_state_t)LL_GTZC_MPCBB_GetClockSecurityState
         ((GTZC_MPCBB_TypeDef *)(uint32_t)memory);
}

#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group8
  * @{
This section provides functions allowing to lock the configurations of MPCBB memory:

  - Call HAL_GTZC_MPCBB_LockConfigBySuperBlock() function to lock the configurations of a set of MPCBB memory
    super_blocks.
  - Call HAL_GTZC_MPCBB_IsLockedConfigBySuperBlock() function to get the lock status of a MPCBB memory super_block.

  - Call HAL_GTZC_MPCBB_LockConfigByAddr() function to lock the configurations of a set of MPCBB memory super_blocks
    depending on the input address.
  - Call HAL_GTZC_MPCBB_IsLockedConfigByAddr() function to get the lock status of a MPCBB memory super_block depending
    on the input address.

  - Call HAL_GTZC_MPCBB_LockConfig() function to lock the configuration of MPCBB registers.
  - Call HAL_GTZC_MPCBB_IsLockedConfig() function to check if the configuration of MPCBB registers is locked or
    unlocked.
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock MPCBB memory super_block configuration.
  * @param  memory  MPCBB memory identifier\n
  *                    This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  start_super_block Memory super_block start.
  * @param  super_block_nbr   Number of memory super_blocks.
  * @note   This function locks the configurations of MPCBB_PGy_SECCFGR and MPCBB_PGy_PRIVCFGR
            registers until the next reset.
  * @retval HAL_OK     MPCBB memory super_block configuration has been successfully locked.
  * @retval HAL_ERROR  This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_MPCBB_LockConfigBySuperBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t start_super_block,
                                                   uint32_t super_block_nbr)
{
  uint32_t super_block_mask = 0;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, (start_super_block * GTZC_MPCBB_SUPER_BLOCK_SIZE),
                                            (super_block_nbr * GTZC_MPCBB_SUPER_BLOCK_SIZE)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  for (uint32_t idx = start_super_block; idx < (start_super_block + super_block_nbr); idx++)
  {
    super_block_mask |= (1UL << idx);
  }

  LL_GTZC_MPCBB_LockSuperBlockConfig((GTZC_MPCBB_TypeDef *)(uint32_t)memory, super_block_mask);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get lock status of a MPCBB memory super_block configuration.
  * @param  memory  MPCBB memory identifier\n
  *                 This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  super_block    Memory super_block.
  * @retval HAL_GTZC_LOCKED   Super_block memory configuration are locked.
  * @retval HAL_GTZC_UNLOCKED Super_block memory configuration are unlocked.
  */
hal_gtzc_lock_status_t HAL_GTZC_MPCBB_IsLockedConfigBySuperBlock(hal_gtzc_mpcbb_memory_t memory, uint32_t super_block)
{

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, (super_block * GTZC_MPCBB_SUPER_BLOCK_SIZE), 0U));

  return (hal_gtzc_lock_status_t)LL_GTZC_MPCBB_IsLockedSuperBlockConfig((GTZC_MPCBB_TypeDef *)(uint32_t)memory,
                                                                        (1UL << super_block));
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock MPCBB memory super_blocks configuration depending on the input address.
  * @param  memory    MPCBB memory identifier\n
  *                      This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  offset_byte  Offset in bytes of the MPCBB memory area. Must be aligned with super_block size.
  * @param  size_byte    Length in bytes of the MPCBB memory area to be locked. Must be aligned with super_block size.
  * @note   The configuration granularity is by super_block:
  *         - If offset_byte is not aligned to the start of a super_block, the entire super_block containing this offset
  *           will be locked.
  *         - Similarly, if the range defined by offset_byte + size_byte does not end on a super_block boundary,
  *           the entire super_block containing the end address will be locked.
  *         - As a result, the function can lock more super_blocks than explicitly specified.
  *         - Users must ensure offset_byte and size_byte are aligned to super_block boundaries or apply appropriate
  *           padding to fully cover the intended super_blocks and avoid unintended locking of adjacent super_blocks.
  *         - This function locks the configurations of MPCBB_PGy_SECCFGR and MPCBB_PGy_PRIVCFGR
  *           registers for the specified super_blocks until the next system reset.
  * @retval HAL_OK       MPCBB memory super_blocks configuration has been successfully locked.
  * @retval HAL_ERROR    This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_MPCBB_LockConfigByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte, uint32_t size_byte)
{
  uint32_t start_super_block;
  uint32_t super_block_nbr;
  uint32_t super_block_mask = 0;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, offset_byte, size_byte));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_SUPER_BLOCK_GRANULARITY(memory, offset_byte, size_byte));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  start_super_block = offset_byte / GTZC_MPCBB_SUPER_BLOCK_SIZE;
  super_block_nbr = size_byte / GTZC_MPCBB_SUPER_BLOCK_SIZE;

  for (uint32_t idx = start_super_block; idx < (start_super_block + super_block_nbr); idx++)
  {
    super_block_mask |= (1UL << idx);
  }

  LL_GTZC_MPCBB_LockSuperBlockConfig((GTZC_MPCBB_TypeDef *)(uint32_t)memory, super_block_mask);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get lock status of a MPCBB memory super_block configuration depending on the input address.
  * @param  memory    MPCBB memory identifier\n
  *                      This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @param  offset_byte  Offset in bytes of the MPCBB memory. Must be aligned with super_block size.
  * @retval HAL_GTZC_LOCKED   Super_block memory configuration are locked.
  * @retval HAL_GTZC_UNLOCKED Super_block memory configuration are unlocked.
  * @note   The lock status is retrieved at super_block granularity:
  *         - The offset_byte must be aligned to the start of a super_block to ensure accurate status retrieval.
  *         - If offset_byte is not super_block-aligned, the status returned corresponds to the super_block containing
  *           the offset.
  */
hal_gtzc_lock_status_t HAL_GTZC_MPCBB_IsLockedConfigByAddr(hal_gtzc_mpcbb_memory_t memory, uint32_t offset_byte)
{
  uint32_t super_block;

  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_IN_RANGE(memory, offset_byte, 0U));
  ASSERT_DBG_PARAM(IS_MPCBB_MEMORY_SUPER_BLOCK_GRANULARITY(memory, offset_byte, 0U));

  super_block = offset_byte / GTZC_MPCBB_SUPER_BLOCK_SIZE;

  return (hal_gtzc_lock_status_t)LL_GTZC_MPCBB_IsLockedSuperBlockConfig((GTZC_MPCBB_TypeDef *)(uint32_t)memory,
                                                                        (1UL << super_block));
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the configuration of MPCBB registers.
  * @param  memory MPCBB memory identifier\n
  *                   This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @note   This function locks the configuration of MPCBB registers until the next reset, except MPCBB_TZICR.
  * @retval HAL_OK    MPCBB registers configuration has been successfully locked.
  * @retval HAL_ERROR This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_MPCBB_LockConfig(hal_gtzc_mpcbb_memory_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  LL_GTZC_MPCBB_LockConfig((GTZC_MPCBB_TypeDef *)(uint32_t)memory);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the lock status of MPCBB registers configuration.
  * @param  memory        MPCBB memory identifier\n
  *                          This parameter is an element of @ref hal_gtzc_mpcbb_memory_t enumeration.
  * @retval HAL_GTZC_LOCKED   MPCBB registers configuration is locked.
  * @retval HAL_GTZC_UNLOCKED MPCBB registers configuration is unlocked.
  */
hal_gtzc_lock_status_t HAL_GTZC_MPCBB_IsLockedConfig(hal_gtzc_mpcbb_memory_t memory)
{
  ASSERT_DBG_PARAM(IS_GTZC_MPCBB_MEMORY(memory));

  return (hal_gtzc_lock_status_t)LL_GTZC_MPCBB_IsLockedConfig((GTZC_MPCBB_TypeDef *)(uint32_t)memory);
}

/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group9
  * @{
This section provides functions allowing to enable or disable the illegal access interrupt of a peripheral:

  - Call HAL_GTZC_TZIC_EnableIT() function to activate the illegal access interrupt to a peripheral.
  - Call HAL_GTZC_TZIC_DisableIT() function to deactivate the illegal access interrupt to a peripheral.
  - Call HAL_GTZC_TZIC_IsEnabledIT() function to check if the illegal access interrupt to a peripheral is enabled or
    disabled.
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Activate the illegal access interrupt to a peripheral.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_tzic_periph_t enumeration.
  * @retval HAL_OK    Illegal access interrupt has been successfully enabled.
  * @retval HAL_ERROR This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZIC_EnableIT(hal_gtzc_tzic_periph_t periph)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZIC_PERIPH((uint32_t)periph));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (periph == HAL_GTZC_TZIC_PERIPH_ALL)
  {
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[0], LL_GTZC_GRP1_ALL, LL_GTZC_GRP1_ALL);
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[1], LL_GTZC_GRP2_ALL, LL_GTZC_GRP2_ALL);
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[2], LL_GTZC_GRP3_ALL, LL_GTZC_GRP3_ALL);
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[3], LL_GTZC_GRP4_ALL, LL_GTZC_GRP4_ALL);
  }
  else
  {
    LL_GTZC_TZIC_EnableIT(GTZC1_TZIC1, (uint32_t)periph);
  }

  return HAL_OK;
}

/**
  * @brief  Deactivate the illegal access interrupt to a peripheral.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_tzic_periph_t enumeration.
  * @retval HAL_OK    Illegal access interrupt has been successfully disabled.
  * @retval HAL_ERROR This function was called from a non-privileged execution environment.
  */
hal_status_t HAL_GTZC_TZIC_DisableIT(hal_gtzc_tzic_periph_t periph)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZIC_PERIPH((uint32_t)periph));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (periph == HAL_GTZC_TZIC_PERIPH_ALL)
  {
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[0], LL_GTZC_GRP1_ALL, 0U);
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[1], LL_GTZC_GRP2_ALL, 0U);
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[2], LL_GTZC_GRP3_ALL, 0U);
    STM32_MODIFY_REG(GTZC1_TZIC1->IER[3], LL_GTZC_GRP4_ALL, 0U);
  }
  else
  {
    LL_GTZC_TZIC_DisableIT(GTZC1_TZIC1, (uint32_t)periph);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the illegal access interrupt to a peripheral enabled or disabled.
  * @param  periph Peripheral identifier\n
  *                This parameter is an element of @ref hal_gtzc_tzic_periph_t enumeration.
  * @retval HAL_OK     Interrupt enable status has been successfully retrieved.
  * @retval HAL_ERROR  Function was called from a non-privileged execution environment.
  */
hal_gtzc_tzic_it_status_t HAL_GTZC_TZIC_IsEnabledIT(hal_gtzc_tzic_periph_t periph)
{
  ASSERT_DBG_PARAM(IS_GTZC_TZIC_PERIPH((uint32_t)periph));
  ASSERT_DBG_PARAM(periph != HAL_GTZC_TZIC_PERIPH_ALL);

  return (hal_gtzc_tzic_it_status_t)LL_GTZC_TZIC_IsEnabledIT(GTZC1_TZIC1, (uint32_t)periph);
}
/**
  * @}
  */

/** @addtogroup GTZC_Exported_Functions_Group10
  * @{
This section provides functions allowing to treat ISR and provide user callback:

  - Call HAL_GTZC_TZIC_IRQHandler() function to handle GTZC illegal access interrupt request.
  - Implement HAL_GTZC_TZIC_Callback() function to handle the GTZC illegal access subblock interrupt callback.
  */

/**
  * @brief  This function handles GTZC illegal access interrupt request.
  */
void HAL_GTZC_TZIC_IRQHandler(void)
{
  for (uint32_t index_reg = 0U; index_reg < 4U; index_reg++)
  {
    /* Get current enabled interrupts and their status flags on register x of TZIC */
    uint32_t active_flags = LL_GTZC_READ_REG(GTZC1_TZIC1, SR[index_reg]);
    uint32_t active_it    = LL_GTZC_READ_REG(GTZC1_TZIC1, IER[index_reg]) & active_flags;

    if (active_it != 0U)
    {
      /* Clear the active interrupts */
      LL_GTZC_WRITE_REG(GTZC1_TZIC1, FCR[index_reg], active_it);

      /* Loop on active_it to check which interrupts have been raised */
      for (uint32_t periph_pos = 0U; (active_it >> periph_pos) != 0U; periph_pos++)
      {
        if ((active_it & (1UL << periph_pos)) != 0U)
        {
          /* Call callback function */
          uint32_t periph = periph_pos + (index_reg * LL_GTZC_REG_MAX_FIELD);
          HAL_GTZC_TZIC_Callback((hal_gtzc_tzic_periph_t)periph);
        }
      }
    }
  }
}

/**
  * @brief  GTZC illegal access subblock interrupt callback.
  * @param  periph Peripheral identifier
  *                This parameter can be an element of @ref hal_gtzc_tzic_periph_t enumeration.
  */
__WEAK void HAL_GTZC_TZIC_Callback(hal_gtzc_tzic_periph_t periph)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(periph);

  /* NOTE: This function must not be modified. When the callback is needed,
   * the HAL_GTZC_TZIC_Callback is to be implemented in the user file.
   */
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_GTZC_MODULE */
#endif /* GTZC1_TZSC1_PERIPH */

/**
  * @}
  */

/**
  * @}
  */
