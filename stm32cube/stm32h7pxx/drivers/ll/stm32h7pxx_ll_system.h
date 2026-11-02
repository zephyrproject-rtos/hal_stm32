/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_ll_system.h
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
#ifndef STM32H7PXX_LL_SYSTEM_H
#define STM32H7PXX_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
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
#define LL_ID_PACKAGE_LQFP100             0x00000002U /*!< Package LQFP100                                    */
#define LL_ID_PACKAGE_TFBGA100            0x00000003U /*!< Package TFBGA100                                   */
#define LL_ID_PACKAGE_LQFP128             0x00000004U /*!< Package LQFP128                                    */
#define LL_ID_PACKAGE_LQFP144             0x00000005U /*!< Package LQFP144                                    */
#define LL_ID_PACKAGE_LQFP176             0x00000006U /*!< Package LQFP176                                    */
#define LL_ID_PACKAGE_UFBGA176_25         0x00000007U /*!< Package UFBGA176+25                                */
#define LL_ID_PACKAGE_LQFP100_SMPS        0x0000000AU /*!< Package LQFP100 with internal SMPS                 */
#define LL_ID_PACKAGE_TFBGA100_SMPS       0x0000000BU /*!< Package TFBGA100 with internal SMPS                */
#define LL_ID_PACKAGE_LQFP128_SMPS        0x0000000CU /*!< Package LQFP128 with internal SMPS                 */
#define LL_ID_PACKAGE_LQFP144_SMPS        0x0000000DU /*!< Package LQFP144 with internal SMPS                 */
#define LL_ID_PACKAGE_LQFP176_SMPS        0x0000000EU /*!< Package LQFP176 with internal SMPS                 */
#define LL_ID_PACKAGE_UFBGA176_25_SMPS    0x0000000FU /*!< Package UFBGA176+25 with internal SMPS             */
#define LL_ID_PACKAGE_LQFP100_EP_SMPS     0x0000001AU /*!< Package LQFP100 with exposed pad and internal SMPS */
#define LL_ID_PACKAGE_LQFP144_EP_SMPS     0x0000001DU /*!< Package LQFP144 with exposed pad and internal SMPS */
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
  *         @arg @ref LL_ID_PACKAGE_LQFP100
  *         @arg @ref LL_ID_PACKAGE_TFBGA100
  *         @arg @ref LL_ID_PACKAGE_LQFP128
  *         @arg @ref LL_ID_PACKAGE_LQFP144
  *         @arg @ref LL_ID_PACKAGE_LQFP176
  *         @arg @ref LL_ID_PACKAGE_UFBGA176_25
  *         @arg @ref LL_ID_PACKAGE_LQFP100_SMPS
  *         @arg @ref LL_ID_PACKAGE_TFBGA100_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP128_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP144_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP176_SMPS
  *         @arg @ref LL_ID_PACKAGE_UFBGA176_25_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP100_EP_SMPS
  *         @arg @ref LL_ID_PACKAGE_LQFP144_EP_SMPS
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

#endif /* STM32H7PXX_LL_SYSTEM_H */
