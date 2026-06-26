/**
  **********************************************************************************************************************
  * @file    stm32g5xx_hal_flash_itf.h
  * @brief   Header file of FLASH HAL module.
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
#ifndef STM32G5XX_HAL_ITF_H
#define STM32G5XX_HAL_ITF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_flash.h"
#include "stm32g5xx_ll_sbs.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (FLASH)

/** @defgroup FLASH_ITF FLASH Interface
  * @{
  */

/* Exported Constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Constants HAL FLASH ITF Constants
  * @{
  */

/** @defgroup FLASH_ITF_OB_PWR_MODE FLASH ITF OB PWR mode
  * @{
  */
#define HAL_FLASH_ITF_OB_STOP_MODE     1U /*!< FLASH ITF option bytes stop mode     */
#define HAL_FLASH_ITF_OB_STANDBY_MODE  2U /*!< FLASH ITF option bytes standby mode  */
/**
  * @}
  */

/** @defgroup FLASH_ITF_OB_SRAM FLASH ITF OB SRAM
  * @{
  */
#define HAL_FLASH_ITF_OB_SRAM2         2U /*!< FLASH ITF option bytes SRAM2         */
#define HAL_FLASH_ITF_OB_SRAM1         8U /*!< FLASH ITF option bytes SRAM1         */
#if defined(SRAM3_BASE)
#define HAL_FLASH_ITF_OB_SRAM3        16U /*!< FLASH ITF option bytes SRAM3         */
#endif /* SRAM3_BASE */
/**
  * @}
  */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/** @defgroup FLASH_ITF_ECC_Interrupts FLASH ITF ECC Interrupts
  * @{
  */
#define HAL_FLASH_ITF_IT_ECC_SINGLE    1U /*!< FLASH ITF ECC single error interrupt */
/**
  * @}
  */
#endif /* USE_HAL_FLASH_ECC */

/** @defgroup FLASH_ITF_secure_items FLASH ITF privilege items definition
  * @{
  */
#define HAL_FLASH_ITF_SEC_ITEM_ALL LL_FLASH_SEC_ITEM_ALL /*!< All secure items  */
/**
  * @}
  */

/** @defgroup FLASH_ITF_privilege_items FLASH ITF privilege items definition
  * @{
  */
#define HAL_FLASH_ITF_PRIV_ITEM_ALL LL_FLASH_PRIV_ITEM_ALL /*!< All privilege items  */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Types HAL FLASH ITF Types
  * @{
  */

/*! HAL FLASH instances enumeration definition */
typedef enum
{
  HAL_FLASH = FLASH_R_BASE, /*!< FLASH Instance */
} hal_flash_t;

/*! HAL FLASH bank enumeration definition */
typedef enum
{
  HAL_FLASH_BANK_1   = 0U, /*!< FLASH bank 1   */
  HAL_FLASH_BANK_2   = 1U, /*!< FLASH bank 2   */
  HAL_FLASH_BANK_ALL = 2U  /*!< FLASH all banks. This value is only used internally for mass erase feature.
                                It must not be used for other purposes. */
} hal_flash_bank_t;

/*! HAL FLASH ITF lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_UNLOCKED = 0U, /*!< FLASH ITF unlocked */
  HAL_FLASH_ITF_LOCKED   = 1U  /*!< FLASH ITF locked   */
} hal_flash_itf_lock_status_t;

/*! HAL FLASH ITF latency enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_LATENCY_0  = LL_FLASH_LATENCY_0WS,  /*!< FLASH ITF zero wait state      */
  HAL_FLASH_ITF_LATENCY_1  = LL_FLASH_LATENCY_1WS,  /*!< FLASH ITF one wait state       */
  HAL_FLASH_ITF_LATENCY_2  = LL_FLASH_LATENCY_2WS,  /*!< FLASH ITF two wait states      */
  HAL_FLASH_ITF_LATENCY_3  = LL_FLASH_LATENCY_3WS,  /*!< FLASH ITF three wait states    */
  HAL_FLASH_ITF_LATENCY_4  = LL_FLASH_LATENCY_4WS,  /*!< FLASH ITF four wait states     */
  HAL_FLASH_ITF_LATENCY_5  = LL_FLASH_LATENCY_5WS,  /*!< FLASH ITF five wait states     */
  HAL_FLASH_ITF_LATENCY_6  = LL_FLASH_LATENCY_6WS,  /*!< FLASH ITF six wait states      */
  HAL_FLASH_ITF_LATENCY_7  = LL_FLASH_LATENCY_7WS,  /*!< FLASH ITF seven wait states    */
  HAL_FLASH_ITF_LATENCY_8  = LL_FLASH_LATENCY_8WS,  /*!< FLASH ITF eight wait states    */
  HAL_FLASH_ITF_LATENCY_9  = LL_FLASH_LATENCY_9WS,  /*!< FLASH ITF nine wait states     */
  HAL_FLASH_ITF_LATENCY_10 = LL_FLASH_LATENCY_10WS, /*!< FLASH ITF ten wait states      */
  HAL_FLASH_ITF_LATENCY_11 = LL_FLASH_LATENCY_11WS, /*!< FLASH ITF eleven wait states   */
  HAL_FLASH_ITF_LATENCY_12 = LL_FLASH_LATENCY_12WS, /*!< FLASH ITF twelve wait states   */
  HAL_FLASH_ITF_LATENCY_13 = LL_FLASH_LATENCY_13WS, /*!< FLASH ITF thirteen wait states */
  HAL_FLASH_ITF_LATENCY_14 = LL_FLASH_LATENCY_14WS, /*!< FLASH ITF fourteen wait states */
  HAL_FLASH_ITF_LATENCY_15 = LL_FLASH_LATENCY_15WS  /*!< FLASH ITF fifteen wait states  */
} hal_flash_itf_latency_t;

/*! HAL FLASH ITF programming delay enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PROGRAM_DELAY_0  = LL_FLASH_PROGRAM_DELAY_0,  /*!< FLASH ITF 0 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_1  = LL_FLASH_PROGRAM_DELAY_1,  /*!< FLASH ITF 1 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_2  = LL_FLASH_PROGRAM_DELAY_2,  /*!< FLASH ITF 2 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_3  = LL_FLASH_PROGRAM_DELAY_3,  /*!< FLASH ITF 3 programming delay */
} hal_flash_itf_program_delay_t;

/*! HAL FLASH ITF Prefetch enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PREFETCH_DISABLED  = 0U, /*!< FLASH ITF prefetch disabled */
  HAL_FLASH_ITF_PREFETCH_ENABLED   = 1U  /*!< FLASH ITF prefetch enabled  */
} hal_flash_itf_prefetch_status_t;

/*! HAL FLASH ITF secure attribute enumeration definition  */
typedef enum
{
  HAL_FLASH_ITF_NSEC = LL_FLASH_ATTR_NSEC,  /*!< FLASH ITF Non-Secure attribute */
  HAL_FLASH_ITF_SEC  = LL_FLASH_ATTR_SEC    /*!< FLASH ITF Secured attribute     */
} hal_flash_itf_sec_attr_t;

/*! HAL FLASH ITF privilege attribute enumeration definition  */
typedef enum
{
  HAL_FLASH_ITF_NPRIV = LL_FLASH_ATTR_NPRIV,  /*!< FLASH ITF Non-privileged attribute */
  HAL_FLASH_ITF_PRIV  = LL_FLASH_ATTR_PRIV    /*!< FLASH ITF Privileged attribute     */
} hal_flash_itf_priv_attr_t;

/*! HAL FLASH ITF option bytes lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_UNLOCKED = 0U, /*!< FLASH ITF option bytes unlocked */
  HAL_FLASH_ITF_OB_LOCKED   = 1U  /*!< FLASH ITF option bytes locked   */
} hal_flash_itf_ob_lock_status_t;

/*! HAL FLASH ITF option bytes OTP block lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_OTP_BLK_UNLOCKED = 0U, /*!< FLASH ITF option bytes OTP block unlocked */
  HAL_FLASH_ITF_OB_OTP_BLK_LOCKED   = 1U  /*!< FLASH ITF option bytes OTP block locked   */
} hal_flash_itf_ob_otp_blk_lock_status_t;

/*! HAL FLASH ITF option bytes WRP page status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WRP_PAGE_NOT_PROTECTED = 0U, /*!< FLASH ITF option bytes write protection page not protected */
  HAL_FLASH_ITF_OB_WRP_PAGE_PROTECTED     = 1U  /*!< FLASH ITF option bytes write protection page protected     */
} hal_flash_itf_ob_wrp_page_status_t;

/*! HAL FLASH ITF option bytes EDATA area status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_EDATA_AREA_DISABLED = 0U, /*!< FLASH ITF option bytes EDATA area disabled */
  HAL_FLASH_ITF_OB_EDATA_AREA_ENABLED  = 1U  /*!< FLASH ITF option bytes EDATA area enabled  */
} hal_flash_itf_ob_edata_area_status_t;

/*! HAL FLASH ITF option-bytes Product State enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_PRODUCT_STATE_OPEN             = LL_FLASH_OB_PRODUCT_STATE_OPEN,              /*!< FLASH ITF option-bytes Product State Open             */
  HAL_FLASH_ITF_OB_PRODUCT_STATE_PROVISIONING     = LL_FLASH_OB_PRODUCT_STATE_PROVISIONING,      /*!< FLASH ITF option-bytes Product State Provisioning     */
  HAL_FLASH_ITF_OB_PRODUCT_STATE_IROT_PROVISIONED = LL_FLASH_OB_PRODUCT_STATE_IROT_PROVISIONED,  /*!< FLASH ITF option-bytes Product State iROT-Provisioned */
  HAL_FLASH_ITF_OB_PRODUCT_STATE_TZ_CLOSED        = LL_FLASH_OB_PRODUCT_STATE_TZ_CLOSED,         /*!< FLASH ITF option-bytes Product State TZ-Closed        */
  HAL_FLASH_ITF_OB_PRODUCT_STATE_CLOSED           = LL_FLASH_OB_PRODUCT_STATE_CLOSED,            /*!< FLASH ITF option-bytes Product State Closed           */
  HAL_FLASH_ITF_OB_PRODUCT_STATE_LOCKED           = LL_FLASH_OB_PRODUCT_STATE_LOCKED,            /*!< FLASH ITF option-bytes Product State Locked           */
  HAL_FLASH_ITF_OB_PRODUCT_STATE_REGRESSION       = LL_FLASH_OB_PRODUCT_STATE_REGRESSION,        /*!< FLASH ITF option-bytes Product State Regression       */
  HAL_FLASH_ITF_OB_PRODUCT_STATE_NS_REGRESSION    = LL_FLASH_OB_PRODUCT_STATE_NS_REGRESSION      /*!< FLASH ITF option-bytes Product State NS-Regression    */
} hal_flash_itf_ob_product_state_t;

/*! HAL FLASH ITF option bytes reset generation when enter in low power mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_RST_GENERATION    = 0U, /*!< FLASH ITF option bytes reset generation when entering low power mode */
  HAL_FLASH_ITF_OB_NO_RST_GENERATION = 1U  /*!< FLASH ITF option bytes no reset generation when entering
                                                low power mode                                                       */
} hal_flash_itf_ob_rst_generation_status_t;

/*! HAL FLASH ITF option bytes Erased SRAM when system reset enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SYS_RST_SRAM_ERASE    = 0U, /*!< FLASH ITF option bytes erased SRAM when system reset occurs    */
  HAL_FLASH_ITF_OB_SYS_RST_SRAM_NO_ERASE = 1U  /*!< FLASH ITF option bytes no erased SRAM when system reset occurs */
} hal_flash_itf_ob_sys_rst_sram_erase_t;

/*! HAL FLASH ITF option bytes xWDG hardware/software mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_HARDWARE = 0U,  /*!< FLASH ITF option bytes xWDG hardware select */
  HAL_FLASH_ITF_OB_WDG_SOFTWARE = 1U   /*!< FLASH ITF option bytes xWDG software select */
} hal_flash_itf_ob_wdg_mode_t;

/*! HAL FLASH ITF option bytes xWDG low-power mode freeze status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_FROZEN   = 1U, /*!< FLASH ITF option bytes xWDG counter low-power mode frozen  */
  HAL_FLASH_ITF_OB_WDG_UNFROZEN = 0U  /*!< FLASH ITF option bytes xWDG counter low-power mode running */
} hal_flash_itf_ob_wdg_freeze_status_t;

/*! HAL FLASH ITF option-bytes Swapping bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_NO_SWAP = LL_FLASH_OB_BANK_NOT_SWAPPED, /*!< FLASH ITF option-bytes Bank not swapped */
  HAL_FLASH_ITF_OB_BANK_SWAP    = LL_FLASH_OB_BANK_SWAPPED      /*!< FLASH ITF option-bytes Bank swapped     */
} hal_flash_itf_ob_bank_swap_t;

/*! HAL FLASH ITF option-bytes Swapping bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_SWAP_LOCKED   = LL_FLASH_OB_BANK_SWAP_LOCKED,  /*!< FLASH ITF option-bytes Bank swap locked   */
  HAL_FLASH_ITF_OB_BANK_SWAP_UNLOCKED = LL_FLASH_OB_BANK_SWAP_UNLOCKED /*!< FLASH ITF option-bytes Bank swap unlocked */
} hal_flash_itf_ob_bank_swap_lock_status_t;

/*! HAL FLASH ITF option bytes SRAM ECC enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SRAM_ECC_DISABLED = 0U, /*!< FLASH ITF option bytes SRAM ECC disable */
  HAL_FLASH_ITF_OB_SRAM_ECC_ENABLED  = 1U  /*!< FLASH ITF option bytes SRAM ECC enable  */
} hal_flash_itf_ob_sram_ecc_status_t;

/*! HAL FLASH ITF option bytes boot lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_UNLOCKED = 0U, /*!< FLASH ITF option bytes boot unlocked */
  HAL_FLASH_ITF_OB_BOOT_LOCKED   = 1U  /*!< FLASH ITF option bytes boot locked   */
} hal_flash_itf_ob_boot_lock_status_t;

/*! HAL FLASH ITF option-bytes Unique boot entry control definition */
typedef enum
{
  HAL_FLASH_ITF_OB_UNIQUE_BOOT_SYSTEM_FLASH = LL_FLASH_OB_BOOT_UBE_ST,  /*!< LL FLASH ITF OB ST_iRoT selected  */
  HAL_FLASH_ITF_OB_UNIQUE_BOOT_USER_FLASH   = LL_FLASH_OB_BOOT_UBE_OEM  /*!< LL FLASH ITF OB OEM_iRoT selected */
} hal_flash_itf_ob_unique_boot_entry_t;

/*! HAL FLASH ITF option-bytes TrustZone enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_TRUSTZONE_DISABLED = LL_FLASH_OB_TZEN_DISABLE, /*!< FLASH ITF option-bytes TrustZone disable */
  HAL_FLASH_ITF_OB_TRUSTZONE_ENABLED  = LL_FLASH_OB_TZEN_ENABLE  /*!< FLASH ITF option-bytes TrustZone enable  */
} hal_flash_itf_ob_trustzone_status_t;

/*! HAL FLASH OBK page enumeration definition */
typedef enum
{
  HAL_FLASH_OBK_PAGE_CURRENT   = LL_FLASH_OBK_PAGE_CURRENT,   /*!< FLASH current OBK page   */
  HAL_FLASH_OBK_PAGE_ALTERNATE = LL_FLASH_OBK_PAGE_ALTERNATE  /*!< FLASH alternate OBK page */
} hal_flash_obk_page_t;

/*! HAL FLASH OBK HDPL enumeration definition */
typedef enum
{
  HAL_FLASH_OBK_AREA_1   = LL_FLASH_OBK_AREA_1,   /*!< FLASH OBK HDPL1             */
  HAL_FLASH_OBK_AREA_2   = LL_FLASH_OBK_AREA_2,   /*!< FLASH OBK HDPL2             */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
  HAL_FLASH_OBK_AREA_3S  = LL_FLASH_OBK_AREA_3S,  /*!< FLASH OBK HDPL3 secure      */
  HAL_FLASH_OBK_AREA_3NS = LL_FLASH_OBK_AREA_3NS  /*!< FLASH OBK HDPL3 Non-Secure  */
#else
  HAL_FLASH_OBK_AREA_3   = LL_FLASH_OBK_AREA_3    /*!< FLASH OBK HDPL3             */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
} hal_flash_obk_area_t;

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/*! HAL FLASH ITF ECC interrupt status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_ECC_IT_DISABLED = 0U, /*!< FLASH ITF ECC interrupt disabled */
  HAL_FLASH_ITF_ECC_IT_ENABLED  = 1U  /*!< FLASH ITF ECC interrupt enabled  */
} hal_flash_itf_ecc_it_status_t;
#endif /* USE_HAL_FLASH_ECC */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Functions HAL FLASH ITF Functions
  * @{
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group1 FLASH ITF Control and Lock/Unlock functions
  * @{
  */

hal_status_t HAL_FLASH_ITF_Lock(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_Unlock(hal_flash_t instance);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(hal_flash_t instance);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_FLASH_ITFNS_Lock(hal_flash_t instance);
hal_status_t HAL_FLASH_ITFNS_Unlock(hal_flash_t instance);
hal_flash_itf_lock_status_t HAL_FLASH_ITFNS_IsLocked(hal_flash_t instance);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

hal_status_t HAL_FLASH_ITF_LaunchPUFOperation(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OBK_Lock(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_OBK_Unlock(hal_flash_t instance);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_OBK_IsLocked(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_OBK_SetPage(hal_flash_t instance, hal_flash_obk_page_t obk_page);
hal_flash_obk_page_t HAL_FLASH_ITF_OBK_GetPage(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OBK_SwapPage(hal_flash_t instance, uint32_t last_key_offset);
hal_status_t HAL_FLASH_ITF_OBK_SwapPage_IT(hal_flash_t instance, uint32_t last_key_offset);

hal_status_t HAL_FLASH_ITF_SetLatency(hal_flash_t instance, hal_flash_itf_latency_t latency);
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_SetProgrammingDelay(hal_flash_t instance, hal_flash_itf_program_delay_t prog_delay);
hal_flash_itf_program_delay_t HAL_FLASH_ITF_GetProgrammingDelay(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_EnablePrefetch(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_DisablePrefetch(hal_flash_t instance);
hal_flash_itf_prefetch_status_t HAL_FLASH_ITF_IsEnabledPrefetch(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_SetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank, uint32_t page_nbr);
uint32_t HAL_FLASH_ITF_GetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank);

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
hal_status_t HAL_FLASH_ITF_ECC_EnableIT(hal_flash_t instance, uint32_t interrupt);
hal_status_t HAL_FLASH_ITF_ECC_DisableIT(hal_flash_t instance, uint32_t interrupt);
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledIT(hal_flash_t instance, uint32_t interrupt);
#endif /* USE_HAL_FLASH_ECC */

/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group2 FLASH ITF Option-bytes configuration functions
  * @{
  */
hal_status_t HAL_FLASH_ITF_OB_Lock(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_OB_Unlock(hal_flash_t instance);
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(hal_flash_t instance);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_FLASH_ITF_OB_SetSecWMArea(hal_flash_t instance,
                                           hal_flash_bank_t bank,
                                           uint32_t start_page,
                                           uint32_t page_nbr);
void HAL_FLASH_ITF_OB_GetSecWMArea(hal_flash_t instance,
                                   hal_flash_bank_t bank,
                                   uint32_t *p_start_page,
                                   uint32_t *p_page_nbr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

hal_status_t HAL_FLASH_ITF_OB_LockOTPBlock(hal_flash_t instance, uint32_t start_otp_block, uint32_t otp_block_nbr);
hal_flash_itf_ob_otp_blk_lock_status_t HAL_FLASH_ITF_OB_IsLockedOTPBlock(hal_flash_t instance,
                                                                         uint32_t otp_block);

hal_status_t HAL_FLASH_ITF_OB_EnablePageWRP(hal_flash_t instance,
                                            hal_flash_bank_t bank,
                                            uint32_t start_page,
                                            uint32_t page_nbr);
hal_status_t HAL_FLASH_ITF_OB_DisablePageWRP(hal_flash_t instance,
                                             hal_flash_bank_t bank,
                                             uint32_t start_page,
                                             uint32_t page_nbr);
hal_flash_itf_ob_wrp_page_status_t HAL_FLASH_ITF_OB_IsEnabledPageWRP(hal_flash_t instance,
                                                                     hal_flash_bank_t bank,
                                                                     uint32_t page);

hal_status_t HAL_FLASH_ITF_OB_SetHDPArea(hal_flash_t instance,
                                         hal_flash_bank_t bank,
                                         uint32_t start_page,
                                         uint32_t page_nbr);
void HAL_FLASH_ITF_OB_GetHDPArea(hal_flash_t instance,
                                 hal_flash_bank_t bank,
                                 uint32_t *p_start_page,
                                 uint32_t *p_page_nbr);

hal_status_t HAL_FLASH_ITF_OB_EnableEDATAArea(hal_flash_t instance, hal_flash_bank_t bank);
hal_status_t HAL_FLASH_ITF_OB_DisableEDATAArea(hal_flash_t instance, hal_flash_bank_t bank);
hal_flash_itf_ob_edata_area_status_t HAL_FLASH_ITF_OB_IsEnabledEDATAArea(hal_flash_t instance,
                                                                         hal_flash_bank_t bank);

hal_status_t HAL_FLASH_ITF_OB_SetEDATAPageArea(hal_flash_t instance, hal_flash_bank_t bank, uint32_t start_page);
uint32_t HAL_FLASH_ITF_OB_GetEDATAPageArea(hal_flash_t instance, hal_flash_bank_t bank);

hal_status_t HAL_FLASH_ITF_OB_SetProductState(hal_flash_t instance, hal_flash_itf_ob_product_state_t product_state);
hal_flash_itf_ob_product_state_t HAL_FLASH_ITF_OB_GetProductState(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(hal_flash_t instance, uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen);
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(hal_flash_t instance,
                                                                                          uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetSystemRstSRAMErase(hal_flash_t instance,
                                                    uint32_t sram,
                                                    hal_flash_itf_ob_sys_rst_sram_erase_t sram_erase);
hal_flash_itf_ob_sys_rst_sram_erase_t HAL_FLASH_ITF_OB_GetSystemRstSRAMErase(hal_flash_t instance,
                                                                             uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(hal_flash_t instance, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetWWDGMode(hal_flash_t instance, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetWWDGMode(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode);
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode);
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(hal_flash_t instance,
                                                                                    uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(hal_flash_t instance, hal_flash_itf_ob_bank_swap_t bank_swap);
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_LockBankSwap(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_OB_UnlockBankSwap(hal_flash_t instance);
hal_flash_itf_ob_bank_swap_lock_status_t HAL_FLASH_ITF_OB_IsLockedBankSwap(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(hal_flash_t instance, uint32_t sram);
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(hal_flash_t instance, uint32_t sram);
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(hal_flash_t instance, uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_SetBootAddr(hal_flash_t instance, uint32_t boot_addr);
uint32_t HAL_FLASH_ITF_OB_GetBootAddr(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_LockBootConfig(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_OB_UnlockBootConfig(hal_flash_t instance);
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetBootloaderInterfaceConfig(hal_flash_t instance, uint32_t bootloader_config);
uint32_t HAL_FLASH_ITF_OB_GetBootloaderInterfaceConfig(hal_flash_t instance);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_FLASH_ITFNS_OB_SetBootAddr(hal_flash_t instance, uint32_t boot_addr);
uint32_t HAL_FLASH_ITFNS_OB_GetBootAddr(hal_flash_t instance);

hal_status_t HAL_FLASH_ITFNS_OB_LockBootConfig(hal_flash_t instance);
hal_status_t HAL_FLASH_ITFNS_OB_UnlockBootConfig(hal_flash_t instance);
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITFNS_OB_IsLockedBootConfig(hal_flash_t instance);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

hal_status_t HAL_FLASH_ITF_OB_SetUniqueBootEntry(hal_flash_t instance, hal_flash_itf_ob_unique_boot_entry_t boot_entry);
hal_flash_itf_ob_unique_boot_entry_t HAL_FLASH_ITF_OB_GetUniqueBootEntry(hal_flash_t instance);

uint32_t HAL_FLASH_ITF_OB_GetEPOCHCounterValue(hal_flash_t instance);
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
uint32_t HAL_FLASH_ITFNS_OB_GetEPOCHCounterValue(hal_flash_t instance);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

hal_status_t HAL_FLASH_ITF_OB_EnableTrustZone(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_OB_DisableTrustZone(hal_flash_t instance);
hal_flash_itf_ob_trustzone_status_t HAL_FLASH_ITF_OB_IsEnabledTrustZone(hal_flash_t instance);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group3 FLASH ITF IRQHandler and callback functions
  * @{
  */
void HAL_FLASH_ITF_IRQHandler(hal_flash_t instance);


void HAL_FLASH_ITF_OB_ProgramCpltCallback(hal_flash_t instance);
void HAL_FLASH_ITF_OB_ErrorCallback(hal_flash_t instance);
void HAL_FLASH_ITF_OBK_ErrorCallback(hal_flash_t instance);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group4 FLASH ITF program option-bytes functions configuration
  * @{
  */
hal_status_t HAL_FLASH_ITF_OB_Program(hal_flash_t instance);
hal_status_t HAL_FLASH_ITF_OB_Program_IT(hal_flash_t instance);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group5 FLASH ITF privileged access levels attributes management functions
  * @{
  */
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_FLASH_ITF_SetSecAttr(hal_flash_t instance, uint32_t item, hal_flash_itf_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_flash_itf_sec_attr_t HAL_FLASH_ITF_GetSecAttr(hal_flash_t instance, uint32_t item);
hal_status_t HAL_FLASH_ITF_SetPrivAttr(hal_flash_t instance, uint32_t item, hal_flash_itf_priv_attr_t priv_attr);
hal_flash_itf_priv_attr_t HAL_FLASH_ITF_GetPrivAttr(hal_flash_t instance, uint32_t item);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_FLASH_ITF_BB_SetSecAttrByPage(hal_flash_t instance,
                                               hal_flash_bank_t bank,
                                               uint32_t start_page,
                                               uint32_t page_nbr,
                                               hal_flash_itf_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
hal_status_t HAL_FLASH_ITF_BB_SetPrivAttrByPage(hal_flash_t instance,
                                                hal_flash_bank_t bank,
                                                uint32_t start_page,
                                                uint32_t page_nbr,
                                                hal_flash_itf_priv_attr_t priv_attr);

hal_flash_itf_sec_attr_t HAL_FLASH_ITF_BB_GetSecAttrByPage(hal_flash_t instance,
                                                           hal_flash_bank_t bank,
                                                           uint32_t page);

hal_flash_itf_priv_attr_t HAL_FLASH_ITF_BB_GetPrivAttrByPage(hal_flash_t instance,
                                                             hal_flash_bank_t bank,
                                                             uint32_t page);

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
hal_status_t HAL_FLASH_ITF_BB_SetSecAttrByAddr(hal_flash_t instance,
                                               hal_flash_bank_t bank,
                                               uint32_t offset_byte,
                                               uint32_t size_byte,
                                               hal_flash_itf_sec_attr_t sec_attr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

hal_status_t HAL_FLASH_ITF_BB_SetPrivAttrByAddr(hal_flash_t instance,
                                                hal_flash_bank_t bank,
                                                uint32_t offset_byte,
                                                uint32_t size_byte,
                                                hal_flash_itf_priv_attr_t priv_attr);

hal_flash_itf_sec_attr_t HAL_FLASH_ITF_BB_GetSecAttrByAddr(hal_flash_t instance,
                                                           hal_flash_bank_t bank,
                                                           uint32_t offset_byte);

hal_flash_itf_priv_attr_t HAL_FLASH_ITF_BB_GetPrivAttrByAddr(hal_flash_t instance,
                                                             hal_flash_bank_t bank,
                                                             uint32_t offset_byte);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* FLASH */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_HAL_ITF_H */
