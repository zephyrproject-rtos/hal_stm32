/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_flash_itf.h
  * @brief   Header file of FLASH ITF HAL module.
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
#ifndef STM32H7Pxx_HAL_FLASH_ITF_H
#define STM32H7Pxx_HAL_FLASH_ITF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_flash.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
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
#define HAL_FLASH_ITF_OB_ALL_SRAM      8U /*!< FLASH ITF option bytes all SRAM      */
/**
  * @}
  */

/** @defgroup FLASH_ITF_OB_VDDIO FLASH ITF OB VDDIO
  * @{
  */
#define HAL_FLASH_ITF_OB_VDDIO         1U /*!< FLASH ITF option bytes VDDIO         */
/**
  * @}
  */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/** @defgroup FLASH_ITF_ECC_Interrupts FLASH ITF ECC Interrupts
  * @{
  */
#define HAL_FLASH_ITF_IT_ECC_SINGLE LL_FLASH_IT_SNECCERR /*!< FLASH ITF ECC single error interrupt */
#define HAL_FLASH_ITF_IT_ECC_DOUBLE LL_FLASH_IT_DBECCERR /*!< FLASH ITF ECC double error interrupt */
#define HAL_FLASH_ITF_IT_ECC_ALL    LL_FLASH_IT_ECC_ALL  /*!< FLASH ITF ECC all error interrupts   */
/**
  * @}
  */
#endif /* USE_HAL_FLASH_ECC */

/** @defgroup FLASH_ITF_OBK_Erase_Key FLASH ITF OBK Erase Key
  * @{
  */
#define HAL_FLASH_OBK_KEY_0   LL_FLASH_OBK_EKEY_0   /*!< OBK Erase key 0    */
#define HAL_FLASH_OBK_KEY_1   LL_FLASH_OBK_EKEY_1   /*!< OBK Erase key 1    */
#define HAL_FLASH_OBK_KEY_2   LL_FLASH_OBK_EKEY_2   /*!< OBK Erase key 2    */
#define HAL_FLASH_OBK_KEY_3   LL_FLASH_OBK_EKEY_3   /*!< OBK Erase key 3    */
#define HAL_FLASH_OBK_KEY_4   LL_FLASH_OBK_EKEY_4   /*!< OBK Erase key 4    */
#define HAL_FLASH_OBK_KEY_5   LL_FLASH_OBK_EKEY_5   /*!< OBK Erase key 5    */
#define HAL_FLASH_OBK_KEY_6   LL_FLASH_OBK_EKEY_6   /*!< OBK Erase key 6    */
#define HAL_FLASH_OBK_KEY_7   LL_FLASH_OBK_EKEY_7   /*!< OBK Erase key 7    */
#define HAL_FLASH_OBK_KEY_8   LL_FLASH_OBK_EKEY_8   /*!< OBK Erase key 8    */
#define HAL_FLASH_OBK_KEY_9   LL_FLASH_OBK_EKEY_9   /*!< OBK Erase key 9    */
#define HAL_FLASH_OBK_KEY_10  LL_FLASH_OBK_EKEY_10  /*!< OBK Erase key 10   */
#define HAL_FLASH_OBK_KEY_11  LL_FLASH_OBK_EKEY_11  /*!< OBK Erase key 11   */
#define HAL_FLASH_OBK_KEY_12  LL_FLASH_OBK_EKEY_12  /*!< OBK Erase key 12   */
#define HAL_FLASH_OBK_KEY_13  LL_FLASH_OBK_EKEY_13  /*!< OBK Erase key 13   */
#define HAL_FLASH_OBK_KEY_14  LL_FLASH_OBK_EKEY_14  /*!< OBK Erase key 14   */
#define HAL_FLASH_OBK_KEY_15  LL_FLASH_OBK_EKEY_15  /*!< OBK Erase key 15   */
#define HAL_FLASH_OBK_KEY_16  LL_FLASH_OBK_EKEY_16  /*!< OBK Erase key 16   */
#define HAL_FLASH_OBK_KEY_17  LL_FLASH_OBK_EKEY_17  /*!< OBK Erase key 17   */
#define HAL_FLASH_OBK_KEY_18  LL_FLASH_OBK_EKEY_18  /*!< OBK Erase key 18   */
#define HAL_FLASH_OBK_KEY_19  LL_FLASH_OBK_EKEY_19  /*!< OBK Erase key 19   */
#define HAL_FLASH_OBK_KEY_20  LL_FLASH_OBK_EKEY_20  /*!< OBK Erase key 20   */
#define HAL_FLASH_OBK_KEY_21  LL_FLASH_OBK_EKEY_21  /*!< OBK Erase key 21   */
#define HAL_FLASH_OBK_KEY_22  LL_FLASH_OBK_EKEY_22  /*!< OBK Erase key 22   */
#define HAL_FLASH_OBK_KEY_23  LL_FLASH_OBK_EKEY_23  /*!< OBK Erase key 23   */
#define HAL_FLASH_OBK_KEY_24  LL_FLASH_OBK_EKEY_24  /*!< OBK Erase key 24   */
#define HAL_FLASH_OBK_KEY_25  LL_FLASH_OBK_EKEY_25  /*!< OBK Erase key 25   */
#define HAL_FLASH_OBK_KEY_26  LL_FLASH_OBK_EKEY_26  /*!< OBK Erase key 26   */
#define HAL_FLASH_OBK_KEY_27  LL_FLASH_OBK_EKEY_27  /*!< OBK Erase key 27   */
#define HAL_FLASH_OBK_KEY_28  LL_FLASH_OBK_EKEY_28  /*!< OBK Erase key 28   */
#define HAL_FLASH_OBK_KEY_29  LL_FLASH_OBK_EKEY_29  /*!< OBK Erase key 29   */
#define HAL_FLASH_OBK_KEY_30  LL_FLASH_OBK_EKEY_30  /*!< OBK Erase key 30   */
#define HAL_FLASH_OBK_KEY_31  LL_FLASH_OBK_EKEY_31  /*!< OBK Erase key 31   */
#define HAL_FLASH_OBK_KEY_ALL LL_FLASH_OBK_EKEY_ALL /*!< All OBK Erase Keys */
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
  HAL_FLASH_BANK_1 = LL_FLASH_BANK_1, /*!< FLASH bank 1   */
  HAL_FLASH_BANK_2 = LL_FLASH_BANK_2, /*!< FLASH bank 2   */
} hal_flash_bank_t;

/*! HAL FLASH ITF lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_UNLOCKED = 0U, /*!< FLASH unlocked */
  HAL_FLASH_ITF_LOCKED   = 1U  /*!< FLASH locked   */
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
  HAL_FLASH_ITF_PROGRAM_DELAY_0  = LL_FLASH_PROGRAM_DELAY_0,  /*!< FLASH 0 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_1  = LL_FLASH_PROGRAM_DELAY_1,  /*!< FLASH 1 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_2  = LL_FLASH_PROGRAM_DELAY_2,  /*!< FLASH 2 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_3  = LL_FLASH_PROGRAM_DELAY_3,  /*!< FLASH 3 programming delay */
} hal_flash_itf_program_delay_t;

/*! HAL FLASH ITF option bytes lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_UNLOCKED = 0U, /*!< FLASH ITF option bytes unlocked */
  HAL_FLASH_ITF_OB_LOCKED   = 1U  /*!< FLASH ITF option bytes locked   */
} hal_flash_itf_ob_lock_status_t;

/*! HAL FLASH ITF option-bytes WRP page status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WRP_PAGE_NOT_PROTECTED = 0U, /*!< FLASH ITF option bytes not write protected page */
  HAL_FLASH_ITF_OB_WRP_PAGE_PROTECTED     = 1U  /*!< FLASH ITF option bytes write protected page     */
} hal_flash_itf_ob_wrp_page_status_t;

/*! HAL FLASH ITF option-bytes OTP block lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_OTP_BLK_UNLOCKED = 0U, /*!< FLASH ITF option bytes otp block unlocked */
  HAL_FLASH_ITF_OB_OTP_BLK_LOCKED   = 1U  /*!< FLASH ITF option bytes otp block locked   */
} hal_flash_itf_ob_otp_blk_lock_status_t;

/*! HAL FLASH ITF option bytes BOR Level enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOR_LEVEL_0 = LL_FLASH_OB_BOR_LEVEL_0, /*!< FLASH ITF option bytes BOR level 0 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_1 = LL_FLASH_OB_BOR_LEVEL_1, /*!< FLASH ITF option bytes BOR level 1 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_2 = LL_FLASH_OB_BOR_LEVEL_2, /*!< FLASH ITF option bytes BOR level 2 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_3 = LL_FLASH_OB_BOR_LEVEL_3, /*!< FLASH ITF option bytes BOR level 3 */
} hal_flash_itf_ob_bor_level_t;

/*! HAL FLASH ITF option bytes key HDP Level enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OBK_HDPL_0 = LL_FLASH_OBK_HDPL_0, /*!< Key stored for the HDPL indicated in SBS_HDPLSR     */
  HAL_FLASH_ITF_OBK_HDPL_1 = LL_FLASH_OBK_HDPL_1, /*!< Key stored for the HDPL indicated in SBS_HDPLSR + 1 */
} hal_flash_itf_obk_hpdl_t;

/*! HAL FLASH ITF option bytes boot address lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_UNLOCKED = 0U, /*!< FLASH ITF option bytes boot unlocked */
  HAL_FLASH_ITF_OB_BOOT_LOCKED   = 1U  /*!< FLASH ITF option bytes boot locked   */
} hal_flash_itf_ob_boot_lock_status_t;

/*! HAL FLASH ITF option bytes hide protection area enumeration definition*/
typedef enum
{
  HAL_FLASH_ITF_HDP_NO_ACCESS_PROTECTION        = LL_FLASH_HDP_NO_ACCESS_PROTECTION,        /*!< HDP extension is not active and can be configured with HDPEXT */
  HAL_FLASH_ITF_HDP_ONLY_AREA_ACCESS_PROTECTION = LL_FLASH_HDP_ONLY_AREA_ACCESS_PROTECTION, /*!< HDP extension is active and can only be increased with HDPEXT */
  HAL_FLASH_ITF_HDP_ALL_ACCESS_PROTECTION       = LL_FLASH_HDP_ALL_ACCESS_PROTECTION        /*!< HDP extension is active and its configuration is locked until reset */
} hal_flash_itf_hdp_access_protection_t;

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/*! HAL FLASH ITF ECC interruption status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_ECC_IT_DISABLED = 0U, /*!< FLASH ITF ECC interruption disabled */
  HAL_FLASH_ITF_ECC_IT_ENABLED  = 1U  /*!< FLASH ITF ECC interruption enabled  */
} hal_flash_itf_ecc_it_status_t;
#endif /* USE_HAL_FLASH_ECC */

/*! HAL FLASH ITF option bytes non-volatile state programming enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_NVSTATE_OPEN  = LL_FLASH_OB_NVSTATE_OPEN,   /*!< FLASH ITF option bytes Open non-volatile state   */
  HAL_FLASH_ITF_OB_NVSTATE_CLOSE = LL_FLASH_OB_NVSTATE_CLOSE  /*!< FLASH ITF option bytes Closed non-volatile state */
} hal_flash_itf_ob_nv_state_t;

/*! HAL FLASH ITF option bytes debug authentication method programming enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_DBG_AUTH_DEFAULT  = LL_FLASH_OB_DBG_AUTH_DEFAULT,     /*!< FLASH ITF option bytes Locked device (no debug allowed)      */
  HAL_FLASH_ITF_OB_DBG_AUTH_PASSWORD = LL_FLASH_OB_DBG_AUTH_PASSWORD,    /*!< FLASH ITF option bytes Authentication method using password  */
  HAL_FLASH_ITF_OB_DBG_AUTH_LOCKED   = LL_FLASH_OB_DBG_AUTH_LOCKED       /*!< FLASH ITF option bytes No authentication method selected (default value) */
} hal_flash_itf_ob_dbg_auth_t;

/*! HAL FLASH ITF option bytes OEM provisioned device enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_OEM_PROVD_ENABLE  = LL_FLASH_OB_OEM_PROVD_ENABLE,  /*!< FLASH ITF option bytes Device is in OEM provisioned state     */
  HAL_FLASH_ITF_OB_OEM_PROVD_DEFAULT = LL_FLASH_OB_OEM_PROVD_DEFAULT  /*!< FLASH ITF option bytes Device is not in OEM provisioned state */
} hal_flash_itf_ob_oem_provd_t;

/*! HAL FLASH ITF option bytes reset generation when enter in low power mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_RST_GENERATION    = 0U, /*!< FLASH ITF OB reset generation when enter in low power mode */
  HAL_FLASH_ITF_OB_NO_RST_GENERATION = 1U  /*!< FLASH ITF OB no reset generation when enter in low power mode */
} hal_flash_itf_ob_rst_generation_status_t;

/*! HAL FLASH ITF option bytes WDG hardware/software mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_HARDWARE = 0U, /*!< FLASH ITF option bytes WDG hardware select */
  HAL_FLASH_ITF_OB_WDG_SOFTWARE = 1U  /*!< FLASH ITF option bytes WDG software select */
} hal_flash_itf_ob_wdg_mode_t;

/*! HAL FLASH ITF option bytes WDG counter low power mode freeze enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_FROZEN   = 1U, /*!< FLASH ITF OB WDG counter low power mode frozen  */
  HAL_FLASH_ITF_OB_WDG_UNFROZEN = 0U  /*!< FLASH ITF OB WDG counter low power mode running */
} hal_flash_itf_ob_wdg_freeze_status_t;

/*! HAL FLASH ITF option bytes Swapping bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_NO_SWAP = LL_FLASH_OB_BANK_NOT_SWAPPED, /*!< FLASH ITF option bytes Bank not swapped */
  HAL_FLASH_ITF_OB_BANK_SWAP    = LL_FLASH_OB_BANK_SWAPPED      /*!< FLASH ITF option bytes Bank swapped     */
} hal_flash_itf_ob_bank_swap_t;

/*! HAL FLASH ITF option-bytes Swapping bank status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_NOT_SWAPPED = 0U, /*!< FLASH ITF option-bytes Bank not swapped */
  HAL_FLASH_ITF_OB_BANK_SWAPPED     = 1U  /*!< FLASH ITF option-bytes Bank swapped     */
} hal_flash_itf_ob_bank_swap_status_t;

/*! HAL FLASH ITF option bytes SRAM ECC enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SRAM_ECC_DISABLED = 0U, /*!< FLASH ITF option bytes SRAM ECC disable */
  HAL_FLASH_ITF_OB_SRAM_ECC_ENABLED  = 1U  /*!< FLASH ITF option bytes SRAM ECC enable  */
} hal_flash_itf_ob_sram_ecc_status_t ;

/*! HAL FLASH ITF option bytes VDDI HSLV enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_VDDX_HSLV_DISABLED = 0U, /*!< FLASH ITF option bytes VDD HSLV disable */
  HAL_FLASH_ITF_OB_VDDX_HSLV_ENABLED  = 1U  /*!< FLASH ITF option bytes VDD HSLV enable  */
} hal_flash_itf_ob_vddx_hslv_status_t;

/*! HAL FLASH ITF option bytes key structure definition */
typedef struct
{
  uint32_t key_w0; /*!< FLASH ITF OBK word 0 */
  uint32_t key_w1; /*!< FLASH ITF OBK word 1 */
  uint32_t key_w2; /*!< FLASH ITF OBK word 2 */
  uint32_t key_w3; /*!< FLASH ITF OBK word 3 */
} hal_flash_itf_ob_obk_t;
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
hal_status_t                HAL_FLASH_ITF_Lock(hal_flash_t instance);
hal_status_t                HAL_FLASH_ITF_Unlock(hal_flash_t instance);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(hal_flash_t instance);

hal_status_t                HAL_FLASH_ITF_LockBank(hal_flash_t instance, hal_flash_bank_t bank);
hal_status_t                HAL_FLASH_ITF_UnlockBank(hal_flash_t instance, hal_flash_bank_t bank);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLockedBank(hal_flash_t instance, hal_flash_bank_t bank);

hal_status_t            HAL_FLASH_ITF_SetLatency(hal_flash_t instance, hal_flash_itf_latency_t latency);
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_SetProgrammingDelay(hal_flash_t instance, hal_flash_itf_program_delay_t prog_delay);
hal_flash_itf_program_delay_t HAL_FLASH_ITF_GetProgrammingDelay(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_SetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank, uint32_t block_nbr);
uint32_t     HAL_FLASH_ITF_GetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank);

hal_status_t HAL_FLASH_ITF_SetHDPExtAccessProtection(hal_flash_t instance,
                                                     hal_flash_bank_t bank,
                                                     hal_flash_itf_hdp_access_protection_t access_protection);
hal_flash_itf_hdp_access_protection_t HAL_FLASH_ITF_GetHDPExtAccessProtection(hal_flash_t instance,
                                                                              hal_flash_bank_t bank);

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
hal_status_t HAL_FLASH_ITF_ECC_EnableIT(hal_flash_t instance, hal_flash_bank_t bank, uint32_t interrupt);
hal_status_t HAL_FLASH_ITF_ECC_DisableIT(hal_flash_t instance, hal_flash_bank_t bank, uint32_t interrupt);
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledIT(hal_flash_t instance,
                                                            hal_flash_bank_t bank,
                                                            uint32_t interrupt);
#endif /* USE_HAL_FLASH_ECC */

hal_status_t HAL_FLASH_ITF_OBK_EnableErrorIT(hal_flash_t instance);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group2 FLASH ITF Configure option bytes functions
  * @{
  */
hal_status_t                   HAL_FLASH_ITF_OB_Lock(hal_flash_t instance);
hal_status_t                   HAL_FLASH_ITF_OB_Unlock(hal_flash_t instance);
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(hal_flash_t instance);

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
                                         uint32_t start_block,
                                         uint32_t block_nbr);
void HAL_FLASH_ITF_OB_GetHDPArea(hal_flash_t instance,
                                 hal_flash_bank_t bank,
                                 uint32_t *p_start_block,
                                 uint32_t *p_block_nbr);

hal_status_t HAL_FLASH_ITF_OB_LockOTPBlock(hal_flash_t instance, uint32_t start_otp_block, uint32_t otp_block_nbr);
hal_flash_itf_ob_otp_blk_lock_status_t HAL_FLASH_ITF_OB_IsLockedOTPBlock(hal_flash_t instance, uint32_t otp_block);

hal_status_t HAL_FLASH_ITF_OB_SetNVState(hal_flash_t instance, hal_flash_itf_ob_nv_state_t nv_state);
hal_flash_itf_ob_nv_state_t HAL_FLASH_ITF_OB_GetNVState(hal_flash_t instance);

hal_status_t                        HAL_FLASH_ITF_OB_LockBootConfig(hal_flash_t instance);
hal_status_t                        HAL_FLASH_ITF_OB_UnlockBootConfig(hal_flash_t instance);
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(hal_flash_t instance);

hal_flash_itf_ob_dbg_auth_t HAL_FLASH_ITF_OB_GetDebugAuthenticationMethod(hal_flash_t instance);

hal_flash_itf_ob_oem_provd_t HAL_FLASH_ITF_OB_GetOEMProvisioning(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetBORLevel(hal_flash_t instance, hal_flash_itf_ob_bor_level_t bor_level);
hal_flash_itf_ob_bor_level_t HAL_FLASH_ITF_OB_GetBORLevel(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(hal_flash_t instance, uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen);
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(hal_flash_t instance,
    uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(hal_flash_t instance, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode);
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode);
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(hal_flash_t instance,
    uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(hal_flash_t instance, hal_flash_itf_ob_bank_swap_t bank_swap);
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(hal_flash_t instance);
hal_flash_itf_ob_bank_swap_status_t HAL_FLASH_ITF_OB_IsBankSwapped(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(hal_flash_t instance, uint32_t sram);
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(hal_flash_t instance, uint32_t sram);
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(hal_flash_t instance, uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd);
hal_status_t HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd);
hal_flash_itf_ob_vddx_hslv_status_t HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage(hal_flash_t instance,
    uint32_t vdd);

hal_status_t HAL_FLASH_ITF_OB_ProgramKey(hal_flash_t instance,
                                         hal_flash_itf_obk_hpdl_t hdp_level,
                                         uint32_t key_index,
                                         const hal_flash_itf_ob_obk_t *key);
hal_status_t HAL_FLASH_ITF_OB_ReadKey(hal_flash_t instance,
                                      hal_flash_itf_obk_hpdl_t hdp_level,
                                      uint32_t key_index,
                                      hal_flash_itf_ob_obk_t *key);
hal_status_t HAL_FLASH_ITF_OB_EraseKey(hal_flash_t instance,
                                       hal_flash_itf_obk_hpdl_t hdp_level,
                                       uint32_t key_mask);

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

#endif /* STM32H7Pxx_HAL_FLASH_ITF_H */
