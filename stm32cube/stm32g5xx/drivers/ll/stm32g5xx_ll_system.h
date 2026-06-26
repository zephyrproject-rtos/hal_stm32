/**
  **********************************************************************************************************************
  * @file    stm32g5xx_ll_system.h
  * @brief   Header file of LL system module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32G5XX_LL_SYSTEM_H
#define STM32G5XX_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

/** @defgroup LL_SYSTEM LL system
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/

/** @defgroup SYSTEM_LL_Exported_Constants LL SYSTEM Constants
  * @{
  */

/** @defgroup DEVICE_ID_PACKAGE Device package identification
  * @{
  */
#define LL_ID_PACKAGE_VFQFPN32         0x20U /*!< Package VFQFPN32   */
#define LL_ID_PACKAGE_UFQFPN32         0x00U /*!< Package UFQFPN32   */
#define LL_ID_PACKAGE_UFQFPN40         0x24U /*!< Package UFQFPN40   */
#define LL_ID_PACKAGE_LQFP48           0x01U /*!< Package LQFP48     */
#define LL_ID_PACKAGE_TQFP48_EP        0x02U /*!< Package TQFP48-EP  */
#define LL_ID_PACKAGE_UFQFPN48         0x03U /*!< Package UFQFPN48   */
#define LL_ID_PACKAGE_UFQFPN56         0x44U /*!< Package UFQFPN56   */
#define LL_ID_PACKAGE_LQFP64           0x04U /*!< Package LQFP64     */
#define LL_ID_PACKAGE_TQFP64_EP        0x05U /*!< Package TQFP64-EP  */
#define LL_ID_PACKAGE_LQFP80           0x06U /*!< Package LQFP80     */
#define LL_ID_PACKAGE_LQFP80_EP        0x07U /*!< Package LQFP80-EP  */
#define LL_ID_PACKAGE_LQFP100          0x08U /*!< Package LQFP100    */
#define LL_ID_PACKAGE_LQFP100_EP       0x09U /*!< Package LQFP100-EP */
#define LL_ID_PACKAGE_LQFP128          0x0AU /*!< Package LQFP128    */
#define LL_ID_PACKAGE_LQFP128_EP       0x0BU /*!< Package LQFP128-EP */
#define LL_ID_PACKAGE_UFBGA121         0x0DU /*!< Package UFBGA121   */
#define LL_ID_PACKAGE_LQFP128_SMPS     0x1AU /*!< Package LQFP128 with internal SMPS  */

/**
  * @}
  */

/** @defgroup PACKAGE_MASK package data mask
  * @{
  */
#define LL_SYSTEM_PACKAGE_MASK 0x1FU /*!< Mask to get package data */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup LL_System_Exported_Functions LL SYSTEM exported functions
  * @{
  */

/** @defgroup LL_System_Device_Identification Device identification (electronic signature)
  * @{
  */

/**
  * @brief  Get Word0 of the device unique identifier (UID based on 96 bits).
  * @rmtoll
  *  UID             UID         LL_GetUID_Word0
  * @retval UID[31:0]: X and Y coordinates on the wafer expressed in BCD format
  */
__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(STM32_READ_REG(*((uint32_t *)UID_BASE)));
}

/**
  * @brief  Get Word1 of the device unique identifier (UID based on 96 bits).
  * @rmtoll
  *  UID             UID         LL_GetUID_Word1
  * @retval UID[63:32]: Wafer number (UID[39:32]) & LOT_NUM[23:0] (UID[63:40])
  */
__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(STM32_READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}

/**
  * @brief  Get Word2 of the device unique identifier (UID based on 96 bits).
  * @rmtoll
  *  UID             UID         LL_GetUID_Word2
  * @retval UID[95:64]: Lot number (ASCII encoded) - LOT_NUM[55:24]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word2(void)
{
  return (uint32_t)(STM32_READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}

/**
  * @brief  Get the package type.
  * @rmtoll
  *  PKG             PKG         LL_GetPackageType
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_ID_PACKAGE_QFN32
  *         @arg @ref LL_ID_PACKAGE_QFN48
  *         @arg @ref LL_ID_PACKAGE_LQFP48
  *         @arg @ref LL_ID_PACKAGE_LQFP64
  *         @arg @ref LL_ID_PACKAGE_LQFP80
  *         @arg @ref LL_ID_PACKAGE_LQFP100
  *         @arg @ref LL_ID_PACKAGE_LQFP128
  *         @arg @ref LL_ID_PACKAGE_FBGA121
  *         @arg @ref LL_ID_PACKAGE_LQFP64_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP80_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP100_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP128_SMPS
  *         @arg @ref LL_ID_PACKAGE_FBGA121_SMPS
  */
__STATIC_INLINE uint32_t LL_GetPackageType(void)
{
  return ((uint32_t)STM32_READ_REG(*((volatile uint16_t *)PACKAGE_BASE)) & (uint32_t)LL_SYSTEM_PACKAGE_MASK);
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_LL_SYSTEM_H */
