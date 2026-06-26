/**
  **********************************************************************************************************************
  * @file    stm32g5xx_otfdec_core.h
  * @brief   Header file of OTFDEC module.
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
#ifndef STM32G5XX_OTFDEC_CORE_H
#define STM32G5XX_OTFDEC_CORE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */
#if defined(OTFDEC1)
/** @defgroup OTFDEC_CORE OTFDEC Core
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup OTFDEC_Exported_Constants OTFDEC CORE Exported Constants
  * @{
  */

/** @defgroup OTFDEC_Flags OTFDEC Flags
  * @{
  */
#define OTFDEC_FLAG_KEY_ERROR                  OTFDEC_ICR_KEIF   /*!< OTFDEC key error flags                          */
#define OTFDEC_FLAG_SECURITY_ERROR             OTFDEC_ICR_SEIF   /*!< OTFDEC security error flags                     */
#define OTFDEC_FLAG_EXEC_ONLY_EXEC_NEVER_ERROR OTFDEC_ICR_XONEIF /*!< OTFDEC execute-only execute-never error flags   */
#define OTFDEC_FLAG_ALL                        (OTFDEC_ICR_KEIF | OTFDEC_ICR_SEIF | OTFDEC_ICR_XONEIF) /*!< All flags */
/**
  * @}
  */

/** @defgroup OTFDEC_Interrupts OTFDEC interrupts
  * @{
  */
#define OTFDEC_IT_NONE                       0U                /*!< No interrupt                                      */
#define OTFDEC_IT_KEY_ERROR                  OTFDEC_IER_KEIE   /*!< OTFDEC key error interrupt                        */
#define OTFDEC_IT_SECURITY_ERROR             OTFDEC_IER_SEIE   /*!< OTFDEC security error interrupt                   */
#define OTFDEC_IT_EXEC_ONLY_EXEC_NEVER_ERROR OTFDEC_IER_XONEIE /*!< OTFDEC execute-only execute-never error interrupt */
#define OTFDEC_IT_ALL                        (OTFDEC_IER_KEIE | OTFDEC_IER_SEIE | OTFDEC_IER_XONEIE) /*!< All ITs     */
/**
  * @}
  */

/** @defgroup OTFDEC_Region_Mode OTFDEC region mode
  * @{
  */
#define OTFDEC_MODE_ALL_READ_ACCESS     OTFDEC_REG_CONFIGR_MODE_1 /*!< OTFDEC all read access mode      */
#define OTFDEC_MODE_ENHANCED_ENCRYPTION OTFDEC_REG_CONFIGR_MODE   /*!< OTFDEC enhanced encryption mode  */
/**
  * @}
  */

/** @defgroup OTFDEC_Region_Configuration_Lock OTFDEC region configuration lock
  * @{
  */
#define OTFDEC_LOCK_CONFIG_ENABLED  OTFDEC_REG_CONFIGR_CONFIGLOCK  /*!< OTFDEC configuration lock enabled  */
#define OTFDEC_LOCK_CONFIG_DISABLED 0x00000000U                     /*!< OTFDEC configuration lock disabled */
/**
  * @}
  */

/** @defgroup OTFDEC_Region_Key_Lock OTFDEC region key lock
  * @{
  */
#define OTFDEC_LOCK_KEY_ENABLED  OTFDEC_REG_CONFIGR_KEYLOCK /*!< OTFDEC key lock enabled  */
#define OTFDEC_LOCK_KEY_DISABLED 0x00000000U                 /*!< OTFDEC key lock disabled */
/**
  * @}
  */

/** @defgroup OTFDEC_Region_Access_Level OTFDEC region access level
  * @{
  */
#define OTFDEC_NPRIV     0U                                 /*!< Non-privileged access level attribute */
#define OTFDEC_PRIV      OTFDEC_PRIVCFGR_PRIV               /*!< Privileged access level attribute     */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup OTFDEC_CORE_Exported_Types OTFDEC Exported Types
  * @{
  */
/**
  * @brief OTFDEC CORE Status definition
  */
typedef enum
{
  OTFDEC_CORE_OK    = 0x00000000U, /* OTFDEC CORE operation completed successfully */
  OTFDEC_CORE_ERROR = 0xFFFFFFFFU  /* OTFDEC CORE operation completed with error   */
} otfdec_core_status_t;
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup OTFDEC_CORE_Exported_Functions OTFDEC Exported Functions
  * @{
  */

/** @defgroup OTFDEC_CORE_Group1 OTFDEC region unitary configuration functions
  * @{
  */
/**
  * @brief Get the region key crc.
  * @param regionx OTFDEC region instance.
  * @retval The key CRC value: between 0 and 0xFF.
  */
__STATIC_INLINE uint8_t OTFDEC_GetRegionKeyCRC(const OTFDEC_Region_TypeDef *regionx)
{
  return (uint8_t)(STM32_READ_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_KEYCRC) >> OTFDEC_REG_CONFIGR_KEYCRC_Pos);
}

/**
  * @brief Lock the region configuration.
  * @param regionx OTFDEC region instance.
  */
__STATIC_INLINE void OTFDEC_LockRegionConfig(OTFDEC_Region_TypeDef *regionx)
{
  STM32_SET_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_CONFIGLOCK);
}

/**
  * @brief Check whether the region configuration is locked or not.
  * @param regionx OTFDEC region instance.
  * @retval 0 OTFDEC region configuration not locked.
  * @retval 1 OTFDEC region configuration is locked.
  */
__STATIC_INLINE uint32_t OTFDEC_IsRegionConfigLocked(const OTFDEC_Region_TypeDef *regionx)
{
  return (uint32_t)((STM32_READ_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_CONFIGLOCK) \
                     == OTFDEC_REG_CONFIGR_CONFIGLOCK) ? 1U : 0U);
}

/**
  * @brief Enable the region key lock.
  * @param regionx OTFDEC region instance.
  */
__STATIC_INLINE void OTFDEC_LockRegionKey(OTFDEC_Region_TypeDef *regionx)
{
  STM32_SET_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_KEYLOCK);
}

/**
  * @brief Check whether the region key is locked.
  * @param regionx OTFDEC region instance.
  * @retval 0 OTFDEC region key not locked.
  * @retval 1 OTFDEC region key is locked.
  */
__STATIC_INLINE uint32_t OTFDEC_IsRegionKeyLocked(const OTFDEC_Region_TypeDef *regionx)
{
  return (uint32_t)((STM32_READ_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_KEYLOCK) \
                     == OTFDEC_REG_CONFIGR_KEYLOCK) ? 1U : 0U);
}

/**
  * @brief Check whether the OTFDEC encryption mode is enabled or not.
  * @param otfdecx OTFDEC instance.
  * @retval 0 OTFDEC encryption is disabled.
  * @retval 1 OTFDEC encryption is enabled.
  */
__STATIC_INLINE uint32_t OTFDEC_IsEnabledEncryption(const OTFDEC_TypeDef *otfdecx)
{
  return (uint32_t)((STM32_READ_BIT(otfdecx->CR, OTFDEC_CR_ENC) == OTFDEC_CR_ENC) ? 1U : 0U);
}
/**
  * @}
  */

/** @defgroup OTFDEC_CORE_Group2 OTFDEC interrupt and flag configuration
  * @{
  */
/** @brief  Enable the specified OTFDEC interrupt.
  * @param  otfdecx   OTFDEC instance.
  * @param  it_source specifies the OTFDEC interrupt source to enable.
  *         This parameter can be a combination of @ref OTFDEC_Interrupts :
  *            @arg OTFDEC_IT_KEY_ERROR                 : key error interrupt.
  *            @arg OTFDEC_IT_SECURITY_ERROR            : security error interrupt.
  *            @arg OTFDEC_IT_EXEC_ONLY_EXEC_NEVER_ERROR: execute only/execute never error interrupt.
  *            @arg OTFDEC_IT_ALL                       : OTFDEC all interrupts.
  */
__STATIC_INLINE void OTFDEC_EnableIT(OTFDEC_TypeDef *otfdecx, uint32_t it_source)
{
  STM32_SET_BIT(otfdecx->IER, it_source);
}

/** @brief  Disable the specified OTFDEC interrupt.
  * @param  otfdecx   OTFDEC instance.
  * @param  it_source specifies the OTFDEC interrupt source to disable.
  *         This parameter can be a combination of @ref OTFDEC_Interrupts :
  *            @arg OTFDEC_IT_KEY_ERROR                 : key error interrupt.
  *            @arg OTFDEC_IT_SECURITY_ERROR            : security error interrupt.
  *            @arg OTFDEC_IT_EXEC_ONLY_EXEC_NEVER_ERROR: execute only/execute never error interrupt.
  *            @arg OTFDEC_IT_ALL                       : OTFDEC all interrupts.
  */
__STATIC_INLINE void OTFDEC_DisableIT(OTFDEC_TypeDef *otfdecx, uint32_t it_source)
{
  STM32_CLEAR_BIT(otfdecx->IER, it_source);
}

/** @brief  Check whether the specified OTFDEC interrupt source is enabled or not.
  * @param  otfdecx   OTFDEC instance.
  * @param  it_source specifies the OTFDEC interrupt source to check.
  *         This parameter can be a combination of @ref OTFDEC_Interrupts :
  *            @arg OTFDEC_IT_KEY_ERROR                 : key error interrupt.
  *            @arg OTFDEC_IT_SECURITY_ERROR            : security error interrupt.
  *            @arg OTFDEC_IT_EXEC_ONLY_EXEC_NEVER_ERROR: execute only/execute never error interrupt.
  * @retval 0 OTFDEC interrupt source is disabled.
  * @retval 1 OTFDEC interrupt source is enabled.
  */
__STATIC_INLINE uint32_t OTFDEC_IsEnabledIT(const OTFDEC_TypeDef *otfdecx, uint32_t it_source)
{
  return (uint32_t)((STM32_READ_BIT(otfdecx->IER, it_source) == it_source) ? 1U : 0U);
}

/** @brief  Check whether the specified OTFDEC interrupt source is enabled or not.
  * @param  otfdecx OTFDEC instance.
  * @param  flag    specifies the OTFDEC interrupt source to check.
  *         This parameter can be a combination of @ref OTFDEC_Interrupts :
  *            @arg OTFDEC_FLAG_KEY_ERROR                 : key error flag.
  *            @arg OTFDEC_FLAG_SECURITY_ERROR            : security error flag.
  *            @arg OTFDEC_FLAG_EXEC_ONLY_EXEC_NEVER_ERROR: execute only/execute never error flag.
  *            @arg OTFDEC_FLAG_ALL                       : OTFDEC all flags.
  */
__STATIC_INLINE void OTFDEC_ClearFlag(OTFDEC_TypeDef *otfdecx, uint32_t flag)
{
  STM32_SET_BIT(otfdecx->ICR, flag);
}

/** @brief  Check whether the specified OTFDEC flag is active or not.
  * @param  otfdecx OTFDEC instance.
  * @param  flag    specifies the OTFDEC flag to check.
  *         This parameter can be a combination of @ref OTFDEC_Interrupts :
  *            @arg OTFDEC_FLAG_KEY_ERROR                 : key error flag.
  *            @arg OTFDEC_FLAG_SECURITY_ERROR            : security error flag.
  *            @arg OTFDEC_FLAG_EXEC_ONLY_EXEC_NEVER_ERROR: execute only/execute never error flag.
  * @retval 0 OTFDEC flag is not active.
  * @retval 1 OTFDEC flag is active.
  */
__STATIC_INLINE uint32_t OTFDEC_IsActiveFlag(const OTFDEC_TypeDef *otfdecx, uint32_t flag)
{
  return (uint32_t)((STM32_READ_BIT(otfdecx->ISR, flag) == flag) ? 1U : 0U);
}
/**
  * @}
  */

/** @defgroup OTFDEC_CORE_Group3 OTFDEC region global configuration functions
  * @{
  */
otfdec_core_status_t OTFDEC_SetConfigRegion(OTFDEC_Region_TypeDef *regionx, uint8_t mode, const uint8_t *p_key,
                                            uint32_t nonce_0, uint32_t nonce_1, uint32_t start_address,
                                            uint32_t end_address, uint16_t version);
void OTFDEC_GetConfigRegion(const OTFDEC_Region_TypeDef *regionx, uint8_t *p_mode, uint32_t *p_nonce_0,
                            uint32_t *p_nonce_1, uint32_t *p_start_address, uint32_t *p_end_address,
                            uint16_t *p_version);
/**
  * @}
  */

/** @defgroup OTFDEC_CORE_Group4 OTFDEC region on the fly decryption functions
  * @{
  */
void OTFDEC_StartRegionDecryption(OTFDEC_TypeDef *otfdecx, OTFDEC_Region_TypeDef *regionx, uint32_t interrupts);

/**
  * @brief Stop the OTFDEC region decryption.
  * @param regionx OTFDEC region instance.
  */
__STATIC_INLINE void OTFDEC_StopRegionDecryption(OTFDEC_Region_TypeDef *regionx)
{
  STM32_CLEAR_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_REG_EN);
}
/**
  * @}
  */

/** @defgroup OTFDEC_CORE_Group5 OTFDEC encryption functions
  * @{
  */
void OTFDEC_Encrypt(OTFDEC_TypeDef *otfdecx, OTFDEC_Region_TypeDef *regionx, const uint32_t *p_input,
                    uint32_t *p_output, uint32_t size_byte, uint32_t start_address, uint32_t interrupts);
/**
  * @}
  */

/** @defgroup OTFDEC_CORE_Group6 OTFDEC privileged access level attributes management functions
  * @{
  */
otfdec_core_status_t OTFDEC_SetPrivAttr(OTFDEC_TypeDef *otfdecx, uint32_t priv_attr);
uint32_t OTFDEC_GetPrivAttr(const OTFDEC_TypeDef *otfdecx);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* OTFDEC1 */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_OTFDEC_CORE_H */
