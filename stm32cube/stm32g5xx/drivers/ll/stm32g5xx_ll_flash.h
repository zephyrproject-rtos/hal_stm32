/**
  **********************************************************************************************************************
  * @file    stm32g5xx_ll_flash.h
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
#ifndef STM32G5XX_LL_FLASH_H
#define STM32G5XX_LL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined (FLASH)

/** @defgroup FLASH_LL FLASH
  * @{
  */

/** @defgroup FLASH_LL_Exported_Constants LL FLASH Constants
  * @{
  */

/** @defgroup FLASH_Interrupt_Flags FLASH Interrupt flags
  * @{
  */
#define LL_FLASH_IT_EOP          FLASH_CR_EOPIE          /*!< End of operation interrupt           */
#define LL_FLASH_IT_WRPERR       FLASH_CR_WRPERRIE       /*!< Write protection error interrupt     */
#define LL_FLASH_IT_PGSERR       FLASH_CR_PGSERRIE       /*!< Programming sequence error interrupt */
#define LL_FLASH_IT_STRBERR      FLASH_CR_STRBERRIE      /*!< Strobe error interrupt               */
#define LL_FLASH_IT_INCERR       FLASH_CR_INCERRIE       /*!< Inconsistency error interrupt        */
#define LL_FLASH_IT_OBKERR       FLASH_CR_OBKERRIE       /*!< OBK general error interrupt          */
#define LL_FLASH_IT_OBKWERR      FLASH_CR_OBKWERRIE      /*!< OBK write error interrupt            */
#define LL_FLASH_IT_OPTCHANGEERR FLASH_CR_OPTCHANGEERRIE  /*!< Option byte change error interrupt   */
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
#define LL_FLASH_IT_ALL (FLASH_CR_EOPIE     | FLASH_CR_WRPERRIE | FLASH_CR_PGSERRIE \
                         | FLASH_CR_STRBERRIE | FLASH_CR_INCERRIE | FLASH_CR_OBKERRIE \
                         | FLASH_CR_OBKWERRIE)                                                 /*!< All interrupts */
#else
#define LL_FLASH_IT_ALL (FLASH_CR_EOPIE     | FLASH_CR_WRPERRIE | FLASH_CR_PGSERRIE \
                         | FLASH_CR_STRBERRIE | FLASH_CR_INCERRIE | FLASH_CR_OBKERRIE \
                         | FLASH_CR_OBKWERRIE | FLASH_CR_OPTCHANGEERRIE)                      /*!< All interrupts */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @defgroup FLASH_Interrupted_Operation_Area_Flags FLASH Interrupted Operation Area flags
  * @{
  */
#define LL_FLASH_FLAG_DATA_OP      FLASH_OPSR_DATA_OP             /* Interrupted operation in data flash flag   */
#define LL_FLASH_FLAG_BK_OP        FLASH_OPSR_BK_OP               /* Interrupted operation bank flag            */
#define LL_FLASH_FLAG_SYSF_OP      FLASH_OPSR_SYSF_OP             /* Interrupted operation in system flash flag */
#define LL_FLASH_FLAG_OTP_OP       FLASH_OPSR_OTP_OP              /* Interrupted operation in OTP flash flag    */
#define LL_FLASH_FLAG_OP_AREA_ALL  (FLASH_OPSR_DATA_OP | FLASH_OPSR_BK_OP \
                                    | FLASH_OPSR_SYSF_OP | FLASH_OPSR_OTP_OP) /* All interrupted operation area flags */
/**
  * @}
  */

/** @defgroup FLASH_Status_Flags FLASH Status flags
  * @{
  */
#define LL_FLASH_FLAG_BSY             FLASH_SR_BSY                        /*!< Busy flag                    */
#define LL_FLASH_FLAG_WBNE            FLASH_SR_WBNE                       /*!< Write buffer not empty flag  */
#define LL_FLASH_FLAG_DBNE            FLASH_SR_DBNE                       /*!< Data buffer not empty flag   */
#define LL_FLASH_FLAG_STATUS_ALL      (FLASH_SR_BSY | FLASH_SR_WBNE | FLASH_SR_DBNE)  /*!< All Status flags */
/**
  * @}
  */

/** @defgroup FLASH_PUF_Flags FLASH PUF flags
  * @{
  */
#define LL_FLASH_FLAG_PUF_STATE       FLASH_SR_PUF_STATE                  /*!< PUF readiness                */
/**
  * @}
  */

/** @defgroup FLASH_Error_Flags FLASH Error flags
  * @{
  */
#define LL_FLASH_FLAG_WRPERR        FLASH_SR_WRPERR
#define LL_FLASH_FLAG_PGSERR        FLASH_SR_PGSERR
#define LL_FLASH_FLAG_STRBERR       FLASH_SR_STRBERR
#define LL_FLASH_FLAG_INCERR        FLASH_SR_INCERR
#define LL_FLASH_FLAG_OBKERR        FLASH_SR_OBKERR
#define LL_FLASH_FLAG_OBKWERR       FLASH_SR_OBKWERR
#define LL_FLASH_FLAG_OPTCHANGEERR  FLASH_SR_OPTCHANGEERR
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
#define LL_FLASH_FLAG_ERRORS_ALL (FLASH_SR_WRPERR | FLASH_SR_PGSERR | FLASH_SR_STRBERR \
                                  | FLASH_SR_INCERR | FLASH_SR_OBKERR | FLASH_SR_OBKWERR)

#define LL_FLASH_FLAG_ERRORS_ALL_NS (FLASH_SR_WRPERR | FLASH_SR_PGSERR | FLASH_SR_STRBERR   \
                                     | FLASH_SR_INCERR | FLASH_SR_OBKERR | FLASH_SR_OBKWERR \
                                     | FLASH_SR_OPTCHANGEERR)
#else
#define LL_FLASH_FLAG_ERRORS_ALL (FLASH_SR_WRPERR | FLASH_SR_PGSERR | FLASH_SR_STRBERR   \
                                  | FLASH_SR_INCERR | FLASH_SR_OBKERR | FLASH_SR_OBKWERR \
                                  | FLASH_SR_OPTCHANGEERR)
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
#define LL_FLASH_FLAG_EOP        FLASH_SR_EOP
#define LL_FLASH_FLAG_ALL        (FLASH_SR_EOP | LL_FLASH_FLAG_ERRORS_ALL)
/**
  * @}
  */

/** @defgroup FLASH_ECC_Error_Flags FLASH ECC Error flags
  * @{
  */
#define LL_FLASH_FLAG_ECCC            FLASH_ECCCORR_ECCC                 /*!< LL FLASH ECC single error flag */
#define LL_FLASH_FLAG_ECCD            FLASH_ECCDETR_ECCD                 /*!< LL FLASH ECC double error flag */
/**
  * @}
  */

/** @defgroup FLASH_ECC_Area_Flags FLASH ECC Area flags
  * @{
  */
#define LL_FLASH_FLAG_EDATA_ECC       FLASH_ECCCORR_EDATA_ECC            /* ECC error in data flash flag   */
#define LL_FLASH_FLAG_BK_ECC          FLASH_ECCCORR_BK_ECC               /* ECC error bank flag            */
#define LL_FLASH_FLAG_SYSF_ECC        FLASH_ECCCORR_SYSF_ECC             /* ECC error in system flash flag */
#define LL_FLASH_FLAG_OTP_ECC         FLASH_ECCCORR_OTP_ECC              /* ECC error in OTP flash flag    */
#define LL_FLASH_FLAG_ECC_AREA_ALL    (FLASH_ECCCORR_EDATA_ECC | FLASH_ECCCORR_BK_ECC | \
                                       FLASH_ECCCORR_SYSF_ECC  | FLASH_ECCCORR_OTP_ECC) /* All ECC error area flags */
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */
#define LL_FLASH_LATENCY_0WS  0x00000000U                                                       /*!< LL FLASH Zero wait state      */
#define LL_FLASH_LATENCY_1WS  FLASH_ACR_LATENCY_0                                               /*!< LL FLASH One wait state       */
#define LL_FLASH_LATENCY_2WS  FLASH_ACR_LATENCY_1                                               /*!< LL FLASH Two wait states      */
#define LL_FLASH_LATENCY_3WS  (FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0)                       /*!< LL FLASH Three wait states    */
#define LL_FLASH_LATENCY_4WS  FLASH_ACR_LATENCY_2                                               /*!< LL FLASH Four wait states     */
#define LL_FLASH_LATENCY_5WS  (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0)                       /*!< LL FLASH Five wait state      */
#define LL_FLASH_LATENCY_6WS  (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1)                       /*!< LL FLASH Six wait state       */
#define LL_FLASH_LATENCY_7WS  (FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0) /*!< LL FLASH Seven wait states    */
#define LL_FLASH_LATENCY_8WS  FLASH_ACR_LATENCY_3                                               /*!< LL FLASH Eight wait states    */
#define LL_FLASH_LATENCY_9WS  (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_0)                       /*!< LL FLASH Nine wait states     */
#define LL_FLASH_LATENCY_10WS (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1)                       /*!< LL FLASH Ten wait state       */
#define LL_FLASH_LATENCY_11WS (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_1 | FLASH_ACR_LATENCY_0) /*!< LL FLASH Eleven wait state    */
#define LL_FLASH_LATENCY_12WS (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2)                       /*!< LL FLASH Twelve wait states   */
#define LL_FLASH_LATENCY_13WS (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_0) /*!< LL FLASH Thirteen wait states */
#define LL_FLASH_LATENCY_14WS (FLASH_ACR_LATENCY_3 | FLASH_ACR_LATENCY_2 | FLASH_ACR_LATENCY_1) /*!< LL FLASH Fourteen wait states */
#define LL_FLASH_LATENCY_15WS FLASH_ACR_LATENCY                                                 /*!< LL FLASH Fifteen wait states  */
/**
  * @}
  */

/** @defgroup FLASH_ProgrammingDelay FLASH Programming Delay
  * @{
  */
#define LL_FLASH_PROGRAM_DELAY_0 0x00000000U                                       /*!< LL FLASH programming delay for Flash frequency at
                                                                                     84 MHz or less */
#define LL_FLASH_PROGRAM_DELAY_1 FLASH_ACR_WRHIGHFREQ_0                            /*!< LL FLASH programming delay for Flash frequency between
                                                                                     60 MHz and 168 MHz */
#define LL_FLASH_PROGRAM_DELAY_2 FLASH_ACR_WRHIGHFREQ_1                            /*!< LL FLASH programming delay for Flash frequency between
                                                                                     120 MHz and 252 MHz */
#define LL_FLASH_PROGRAM_DELAY_3 (FLASH_ACR_WRHIGHFREQ_0 | FLASH_ACR_WRHIGHFREQ_1) /*!< LL FLASH programming delay for Flash frequency between
                                                                                     204 MHz and 280 MHz */
/**
  * @}
  */

/** @defgroup FLASH_secure_items  FLASH secure items
  * @{
  */
#define LL_FLASH_SEC_ITEM_ALL   FLASH_ACR_ACR_SEC_EN   /*!< All secure items  */
/**
  * @}
  */

/** @defgroup FLASH_secure_attribute  secure attribute
  * @{
  */
#define LL_FLASH_ATTR_NSEC     0U   /*!< Non-Secure attribute  */
#define LL_FLASH_ATTR_SEC      1U   /*!< secured attribute      */
/**
  * @}
  */

/** @defgroup FLASH_privilege_items  FLASH Privilege items
  * @{
  */
#define LL_FLASH_PRIV_ITEM_ALL     FLASH_PRIVCFGR_PRIV   /*!< All privilege items  */
/**
  * @}
  */

/** @defgroup FLASH_privilege_attribute  Privilege attribute
  * @{
  */
#define LL_FLASH_ATTR_NPRIV     0U   /*!< Non-privileged attribute  */
#define LL_FLASH_ATTR_PRIV      1U   /*!< Privileged attribute      */
/**
  * @}
  */

/** @defgroup FLASH_Unlock_Keys FLASH Unlock Keys
  * @{
  */
#define LL_FLASH_KEY1 0x45670123U /*!< LL FLASH key1 */
#define LL_FLASH_KEY2 0xCDEF89ABU /*!< LL FLASH key2 */
/**
  * @}
  */

/** @defgroup FLASH_OB_Unlock_Keys FLASH OB Unlock Keys
  * @{
  */
#define LL_FLASH_OB_OPTKEY1 0x08192A3BU /*!< LL FLASH option byte key1 */
#define LL_FLASH_OB_OPTKEY2 0x4C5D6E7FU /*!< LL FLASH option byte key2 */
/**
  * @}
  */

/** @defgroup FLASH_OBK_Unlock_Keys FLASH OBK Unlock Keys
  * @{
  */
#define LL_FLASH_OBK_OBKKEY1 0x192A083BU /*!< LL FLASH OBK key1 */
#define LL_FLASH_OBK_OBKKEY2 0x6E7F4C5DU /*!< LL FLASH OBK key2 */
/**
  * @}
  */

/** @defgroup FLASH_Bank_Selection FLASH Bank Selection
  * @{
  */
#define LL_FLASH_BANK_1 0x00U /*!< LL FLASH bank 1 */
#define LL_FLASH_BANK_2 0x40U /*!< LL FLASH bank 2 */
/**
  * @}
  */

/** @defgroup FLASH_BB_Page_Selection FLASH BB Page Selection
  * @{
  */
#define LL_FLASH_BB_PAGE_0   0x00000001U
#define LL_FLASH_BB_PAGE_1   0x00000002U
#define LL_FLASH_BB_PAGE_2   0x00000004U
#define LL_FLASH_BB_PAGE_3   0x00000008U
#define LL_FLASH_BB_PAGE_4   0x00000010U
#define LL_FLASH_BB_PAGE_5   0x00000020U
#define LL_FLASH_BB_PAGE_6   0x00000040U
#define LL_FLASH_BB_PAGE_7   0x00000080U
#define LL_FLASH_BB_PAGE_8   0x00000100U
#define LL_FLASH_BB_PAGE_9   0x00000200U
#define LL_FLASH_BB_PAGE_10  0x00000400U
#define LL_FLASH_BB_PAGE_11  0x00000800U
#define LL_FLASH_BB_PAGE_12  0x00001000U
#define LL_FLASH_BB_PAGE_13  0x00002000U
#define LL_FLASH_BB_PAGE_14  0x00004000U
#define LL_FLASH_BB_PAGE_15  0x00008000U
#define LL_FLASH_BB_PAGE_16  0x00010000U
#define LL_FLASH_BB_PAGE_17  0x00020000U
#define LL_FLASH_BB_PAGE_18  0x00040000U
#define LL_FLASH_BB_PAGE_19  0x00080000U
#define LL_FLASH_BB_PAGE_20  0x00100000U
#define LL_FLASH_BB_PAGE_21  0x00200000U
#define LL_FLASH_BB_PAGE_22  0x00400000U
#define LL_FLASH_BB_PAGE_23  0x00800000U
#define LL_FLASH_BB_PAGE_24  0x01000000U
#define LL_FLASH_BB_PAGE_25  0x02000000U
#define LL_FLASH_BB_PAGE_26  0x04000000U
#define LL_FLASH_BB_PAGE_27  0x08000000U
#define LL_FLASH_BB_PAGE_28  0x10000000U
#define LL_FLASH_BB_PAGE_29  0x20000000U
#define LL_FLASH_BB_PAGE_30  0x40000000U
#define LL_FLASH_BB_PAGE_31  0x80000000U
/**
  * @}
  */

/** @defgroup FLASH_Erase_Bank_Selection FLASH Erase Bank Selection
  * @{
  */
#define LL_FLASH_ERASE_BANK_1 0x00000000U     /*!< LL FLASH erase bank 1 */
#define LL_FLASH_ERASE_BANK_2 FLASH_CR_BKSEL  /*!< LL FLASH erase bank 2 */
/**
  * @}
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/** @defgroup FLASH_Security_Inversion FLASH Security Inversion
  * @{
  */
#define LL_FLASH_SEC_NOT_INVERTED 0U               /*!< LL FLASH Security state not inverted */
#define LL_FLASH_SEC_INVERTED     FLASH_SCR_INV    /*!< LL FLASH Security state inverted     */
/**
  * @}
  */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/** @defgroup FLASH_OBKCFGR_Bank_Selection FLASH OBKCFGR OBK page map
  * @{
  */
#define LL_FLASH_OBK_PAGE_ALTERNATE  FLASH_OBKCFGR_ALT_SECT /*!< LL FLASH alternate OBK page is mapped */
#define LL_FLASH_OBK_PAGE_CURRENT    0U                     /*!< LL FLASH current OBK page is mapped   */
/**
  * @}
  */

/** @defgroup FLASH_OBK_HDPL FLASH OBK HDPL
  * @{
  */
#define LL_FLASH_OBK_AREA_1    0x010U /*!< FLASH OBK HDPL1             */
#define LL_FLASH_OBK_AREA_2    0x090U /*!< FLASH OBK HDPL2             */
#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
#define LL_FLASH_OBK_AREA_3S   0x100U /*!< FLASH OBK HDPL3 secure      */
#define LL_FLASH_OBK_AREA_3NS  0x180U /*!< FLASH OBK HDPL3 Non-Secure  */
#else
#define LL_FLASH_OBK_AREA_3    0x100U /*!< FLASH OBK HDPL3             */
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
/**
  * @}
  */

/** @defgroup FLASH_HDPEXT_Bank_Selection FLASH HDPEXT Bank Selection
  * @{
  */
#define LL_FLASH_HDPEXT_BANK_1 FLASH_HDPEXTR_HDP1_EXT_Pos  /*!< LL FLASH HDPEXT bank 1 */
#define LL_FLASH_HDPEXT_BANK_2 FLASH_HDPEXTR_HDP2_EXT_Pos  /*!< LL FLASH HDPEXT bank 2 */
/**
  * @}
  */

/** @defgroup FLASH_OB_IWDG_HW_SW_Selection FLASH OB IWDG HW SW Selection
  * @{
  */
#define LL_FLASH_OB_IWDG_HW 0x00000000U             /*!< LL FLASH OB IWDG Hardware selection */
#define LL_FLASH_OB_IWDG_SW FLASH_OPTSR_CUR_IWDG_SW /*!< LL FLASH OB IWDG Software selection */
/**
  * @}
  */

/** @defgroup FLASH_OB_WWDG_HW_SW_Selection FLASH OB WWDG HW SW Selection
  * @{
  */
#define LL_FLASH_OB_WWDG_HW 0x00000000U             /*!< LL FLASH OB WWDG Hardware selection */
#define LL_FLASH_OB_WWDG_SW FLASH_OPTSR_CUR_WWDG_SW /*!< LL FLASH OB WWDG Software selection */
/**
  * @}
  */

/** @defgroup FLASH_OB_Reset_Generation_Stop_Mode FLASH OB Reset Generation Stop Mode
  * @{
  */
#define LL_FLASH_OB_RST_STOP_MODE    0x00000000U               /*!< LL FLASH option-bytes reset in stop mode    */
#define LL_FLASH_OB_NO_RST_STOP_MODE FLASH_OPTSR_CUR_NRST_STOP /*!< LL FLASH option-bytes no reset in stop mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_Reset_Generation_Standby_Mode FLASH OB Reset Generation standby Mode
  * @{
  */
#define LL_FLASH_OB_RST_STDBY_MODE    0x00000000U                /*!< LL FLASH option-bytes reset in standby mode    */
#define LL_FLASH_OB_NO_RST_STDBY_MODE FLASH_OPTSR_CUR_NRST_STDBY /*!< LL FLASH option-bytes no reset in standby mode */
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection_Level FLASH OB Read Protection Level
  * @{
  */
#define LL_FLASH_OB_PRODUCT_STATE_OPEN             (0xEDUL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State Open             */
#define LL_FLASH_OB_PRODUCT_STATE_PROVISIONING     (0x17UL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State Provisioning     */
#define LL_FLASH_OB_PRODUCT_STATE_IROT_PROVISIONED (0x2EUL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State iROT-Provisioned */
#define LL_FLASH_OB_PRODUCT_STATE_TZ_CLOSED        (0xC6UL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State TZ-Closed        */
#define LL_FLASH_OB_PRODUCT_STATE_CLOSED           (0x72UL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State Closed           */
#define LL_FLASH_OB_PRODUCT_STATE_LOCKED           (0x5CUL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State Locked           */
#define LL_FLASH_OB_PRODUCT_STATE_REGRESSION       (0x9AUL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State Regression       */
#define LL_FLASH_OB_PRODUCT_STATE_NS_REGRESSION    (0xA3UL << FLASH_OPTSR_CUR_PRODUCT_STATE_Pos) /*!< LL FLASH option-bytes Product State NS-Regression    */
/**
  * @}
  */

/** @defgroup FLASH_OB_UNIQUE_BOOT_Selection FLASH OB Unique boot entry control
  * @{
  */
#define LL_FLASH_OB_BOOT_UBE_ST  (0xC3UL << FLASH_OPTSR_CUR_BOOT_UBE_Pos) /*!< LL FLASH OB ST_iRoT selected  */
#define LL_FLASH_OB_BOOT_UBE_OEM (0xB4UL << FLASH_OPTSR_CUR_BOOT_UBE_Pos) /*!< LL FLASH OB OEM_iRoT selected */
/**
  * @}
  */

/** @defgroup FLASH_OB_Erase_Sram1_System_Reset FLASH OB Erase Sram1 System Reset
  * @{
  */
#define LL_FLASH_OB_ERASED_SRAM1_SYS_RST     0x00000000U                /*!< LL FLASH OB Erased sram1 and sram3 upon system reset     */
#define LL_FLASH_OB_NOT_ERASED_SRAM1_SYS_RST FLASH_OPTSR2_CUR_SRAM1_RST /*!< LL FLASH OB Not erased sram1 and sram3 upon system reset */
/**
  * @}
  */

/** @defgroup FLASH_OB_Erase_Sram2_System_Reset FLASH OB Erase Sram2 System Reset
  * @{
  */
#define LL_FLASH_OB_ERASED_SRAM2_SYS_RST     0x00000000U                /*!< LL FLASH OB Erased sram2 upon system reset     */
#define LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST FLASH_OPTSR2_CUR_SRAM2_RST /*!< LL FLASH OB Not erased sram2 upon system reset */
/**
  * @}
  */

#if defined(SRAM3_BASE)
/** @defgroup FLASH_OB_Erase_Sram3_System_Reset FLASH OB Erase Sram3 System Reset
  * @{
  */
#define LL_FLASH_OB_ERASED_SRAM3_SYS_RST     0x00000000U                /*!< LL FLASH OB Erased sram3 upon system reset     */
#define LL_FLASH_OB_NOT_ERASED_SRAM3_SYS_RST FLASH_OPTSR2_CUR_SRAM3_RST /*!< LL FLASH OB Not erased sram3 upon system reset */
/**
  * @}
  */
#endif /* SRAM3_BASE */

/** @defgroup FLASH_OB_Huk_Source FLASH OB Huk Source
  * @{
  */
#define LL_FLASH_OB_DHUK_RHUK  0x00000000U               /*!< LL FLASH OB Huk source is RHUK */
#define LL_FLASH_OB_DHUK_PUF   FLASH_OPTSR2_CUR_HUK_PUF  /*!< LL FLASH OB Huk source is PUF  */
/**
  * @}
  */

/** @defgroup FLASH_OB_Trustzone_Enable FLASH OB Trustzone Enable
  * @{
  */
#define LL_FLASH_OB_TZEN_ENABLE  (0xB4UL << FLASH_OPTSR2_CUR_TZEN_Pos) /*!< LL FLASH TrustZone enabled  */
#define LL_FLASH_OB_TZEN_DISABLE (0xC3UL << FLASH_OPTSR2_CUR_TZEN_Pos) /*!< LL FLASH TrustZone disabled */
/**
  * @}
  */

/** @defgroup FLASH_OB_BootAddr_Lock FLASH OB Boot Address Lock
  * @{
  */
#define LL_FLASH_OB_BOOT_NOT_LOCKED     (0xC3UL << FLASH_BOOTR_CUR_BOOT_LOCK_Pos) /*!< LL FLASH TrustZone not locked  */
#define LL_FLASH_OB_BOOT_LOCKED         (0xB4UL << FLASH_BOOTR_CUR_BOOT_LOCK_Pos) /*!< LL FLASH TrustZone locked      */
/**
  * @}
  */

/** @defgroup FLASH_OB_Swap_Bank FLASH OB Swap Bank
  * @{
  */
#define LL_FLASH_OB_BANK_NOT_SWAPPED (0xC3UL << FLASH_OPTSR3_CUR_SWAP_BANK_Pos) /*!< LL FLASH OB Bank not swapped */
#define LL_FLASH_OB_BANK_SWAPPED     (0xB4UL << FLASH_OPTSR3_CUR_SWAP_BANK_Pos) /*!< LL FLASH OB Bank swapped     */
/**
  * @}
  */

/** @defgroup FLASH_OB_Swap_Lock FLASH OB Swap Lock
  * @{
  */
#define LL_FLASH_OB_BANK_SWAP_UNLOCKED (0xC3UL << FLASH_OPTSR3_CUR_SWAP_LOCKOUT_Pos) /*!< LL FLASH OB Swap not locked */
#define LL_FLASH_OB_BANK_SWAP_LOCKED   (0xB4UL << FLASH_OPTSR3_CUR_SWAP_LOCKOUT_Pos) /*!< LL FLASH OB Swap locked     */
/**
  * @}
  */

/** @defgroup LL_FLASH_OB_Write_Protection_Pages FLASH OB Write Protection Pages
  * @{
  */
#define LL_FLASH_OB_WRP_PAGE_0_3       0x00000001UL               /*!< Write protection of Page0  to Page3  */
#define LL_FLASH_OB_WRP_PAGE_4_7       0x00000002UL               /*!< Write protection of Page4  to Page7  */
#define LL_FLASH_OB_WRP_PAGE_8_11      0x00000004UL               /*!< Write protection of Page8  to Page11 */
#define LL_FLASH_OB_WRP_PAGE_12_15     0x00000008UL               /*!< Write protection of Page12 to Page15 */
#define LL_FLASH_OB_WRP_PAGE_16_19     0x00000010UL               /*!< Write protection of Page16 to Page19 */
#define LL_FLASH_OB_WRP_PAGE_20_23     0x00000020UL               /*!< Write protection of Page20 to Page23 */
#define LL_FLASH_OB_WRP_PAGE_24_27     0x00000040UL               /*!< Write protection of Page24 to Page27 */
#define LL_FLASH_OB_WRP_PAGE_28_31     0x00000080UL               /*!< Write protection of Page28 to Page31 */
#define LL_FLASH_OB_WRP_PAGE_ALL       FLASH_WRP1R_PRG_WRPG1_Msk  /*!< Write protection of all Pages        */
/**
  * @}
  */

/** @defgroup FLASH_OTP_Blocks FLASH OTP blocks
  * @{
  */
#define LL_FLASH_OB_OTP_BLK_0       0x00000001UL                /*!< OTP Lock Block0  */
#define LL_FLASH_OB_OTP_BLK_1       0x00000002UL                /*!< OTP Lock Block1  */
#define LL_FLASH_OB_OTP_BLK_2       0x00000004UL                /*!< OTP Lock Block2  */
#define LL_FLASH_OB_OTP_BLK_3       0x00000008UL                /*!< OTP Lock Block3  */
#define LL_FLASH_OB_OTP_BLK_4       0x00000010UL                /*!< OTP Lock Block4  */
#define LL_FLASH_OB_OTP_BLK_5       0x00000020UL                /*!< OTP Lock Block5  */
#define LL_FLASH_OB_OTP_BLK_6       0x00000040UL                /*!< OTP Lock Block6  */
#define LL_FLASH_OB_OTP_BLK_7       0x00000080UL                /*!< OTP Lock Block7  */
#define LL_FLASH_OB_OTP_BLK_8       0x00000100UL                /*!< OTP Lock Block8  */
#define LL_FLASH_OB_OTP_BLK_9       0x00000200UL                /*!< OTP Lock Block9  */
#define LL_FLASH_OB_OTP_BLK_10      0x00000400UL                /*!< OTP Lock Block10 */
#define LL_FLASH_OB_OTP_BLK_11      0x00000800UL                /*!< OTP Lock Block11 */
#define LL_FLASH_OB_OTP_BLK_12      0x00001000UL                /*!< OTP Lock Block12 */
#define LL_FLASH_OB_OTP_BLK_13      0x00002000UL                /*!< OTP Lock Block13 */
#define LL_FLASH_OB_OTP_BLK_14      0x00004000UL                /*!< OTP Lock Block14 */
#define LL_FLASH_OB_OTP_BLK_15      0x00008000UL                /*!< OTP Lock Block15 */
#define LL_FLASH_OB_OTP_BLK_16      0x00010000UL                /*!< OTP Lock Block16 */
#define LL_FLASH_OB_OTP_BLK_17      0x00020000UL                /*!< OTP Lock Block17 */
#define LL_FLASH_OB_OTP_BLK_18      0x00040000UL                /*!< OTP Lock Block18 */
#define LL_FLASH_OB_OTP_BLK_19      0x00080000UL                /*!< OTP Lock Block19 */
#define LL_FLASH_OB_OTP_BLK_20      0x00100000UL                /*!< OTP Lock Block20 */
#define LL_FLASH_OB_OTP_BLK_21      0x00200000UL                /*!< OTP Lock Block21 */
#define LL_FLASH_OB_OTP_BLK_22      0x00400000UL                /*!< OTP Lock Block22 */
#define LL_FLASH_OB_OTP_BLK_23      0x00800000UL                /*!< OTP Lock Block23 */
#define LL_FLASH_OB_OTP_BLK_24      0x01000000UL                /*!< OTP Lock Block24 */
#define LL_FLASH_OB_OTP_BLK_25      0x02000000UL                /*!< OTP Lock Block25 */
#define LL_FLASH_OB_OTP_BLK_26      0x04000000UL                /*!< OTP Lock Block26 */
#define LL_FLASH_OB_OTP_BLK_27      0x08000000UL                /*!< OTP Lock Block27 */
#define LL_FLASH_OB_OTP_BLK_28      0x10000000UL                /*!< OTP Lock Block28 */
#define LL_FLASH_OB_OTP_BLK_29      0x20000000UL                /*!< OTP Lock Block29 */
#define LL_FLASH_OB_OTP_BLK_30      0x40000000UL                /*!< OTP Lock Block30 */
#define LL_FLASH_OB_OTP_BLK_31      0x80000000UL                /*!< OTP Lock Block31 */
#define LL_FLASH_OB_OTP_BLK_ALL     FLASH_OTPBLR_CUR_LOCKBL_Msk /*!< OTP Lock All Blocks */
/**
  * @}
  */

/** @defgroup FLASH_Interrupted_Operation_Code FLASH Interrupted Operation Code
  * @{
  */
#define LL_FLASH_INTERRUPTED_NO_OPERATION       0x00000000U                                    /*!< LL FLASH interrupted no operation             */
#define LL_FLASH_INTERRUPTED_SINGLE_WRITE       FLASH_OPSR_CODE_OP_0                           /*!< LL FLASH interrupted OBK alternate page erase */
#define LL_FLASH_INTERRUPTED_OBK_ALT_PAGE_ERASE FLASH_OPSR_CODE_OP_1                           /*!< LL FLASH interrupted single write             */
#define LL_FLASH_INTERRUPTED_PAGE_ERASE         (FLASH_OPSR_CODE_OP_1 | FLASH_OPSR_CODE_OP_0)  /*!< LL FLASH interrupted page erase               */
#define LL_FLASH_INTERRUPTED_BANK_ERASE         FLASH_OPSR_CODE_OP_2                           /*!< LL FLASH interrupted bank erase               */
#define LL_FLASH_INTERRUPTED_MASS_ERASE         (FLASH_OPSR_CODE_OP_2 | FLASH_OPSR_CODE_OP_0)  /*!< LL FLASH interrupted mass erase               */
#define LL_FLASH_INTERRUPTED_OB_CHANGE          (FLASH_OPSR_CODE_OP_2 | FLASH_OPSR_CODE_OP_1)  /*!< LL FLASH interrupted option bytes change      */
#define LL_FLASH_INTERRUPTED_OBK_SWAP_PAGE      FLASH_OPSR_CODE_OP                             /*!< LL FLASH interrupted OBK swap page            */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Macros LL FLASH Macros
  * @{
  */

/**
  * @brief  Write a value in FLASH register.
  * @param  flashx FLASH instance.
  * @param  reg   Register to be written.
  * @param  value Value to be written in the register.
  */
#define LL_FLASH_WRITE_REG(flashx, reg, value) STM32_WRITE_REG(flashx->reg, (value))

/**
  * @brief  Read a value from FLASH register.
  * @param  flashx FLASH instance.
  * @param  reg      Register to be read
  * @retval Register value
  */
#define LL_FLASH_READ_REG(flashx, reg) STM32_READ_REG(flashx->reg)

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup FLASH_LL_Exported_Functions LL FLASH Functions
  * @{
  */

/** @defgroup FLASH_LL_EF_Configuration LL FLASH Configuration
  * @{
  */

/**
  * @brief  Set Flash latency.
  * @rmtoll
  *  ACR           LATENCY           LL_FLASH_SetLatency
  * @param  flashx FLASH instance.
  * @param  latency
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0WS
  *         @arg @ref LL_FLASH_LATENCY_1WS
  *         @arg @ref LL_FLASH_LATENCY_2WS
  *         @arg @ref LL_FLASH_LATENCY_3WS
  *         @arg @ref LL_FLASH_LATENCY_4WS
  *         @arg @ref LL_FLASH_LATENCY_5WS
  *         @arg @ref LL_FLASH_LATENCY_6WS
  *         @arg @ref LL_FLASH_LATENCY_7WS
  *         @arg @ref LL_FLASH_LATENCY_8WS
  *         @arg @ref LL_FLASH_LATENCY_9WS
  *         @arg @ref LL_FLASH_LATENCY_10WS
  *         @arg @ref LL_FLASH_LATENCY_11WS
  *         @arg @ref LL_FLASH_LATENCY_12WS
  *         @arg @ref LL_FLASH_LATENCY_13WS
  *         @arg @ref LL_FLASH_LATENCY_14WS
  *         @arg @ref LL_FLASH_LATENCY_15WS
  */
__STATIC_INLINE void LL_FLASH_SetLatency(FLASH_TypeDef *flashx, uint32_t latency)
{
  STM32_MODIFY_REG(flashx->ACR, FLASH_ACR_LATENCY, latency);
}

/**
  * @brief  Get Flash latency.
  * @rmtoll
  *  ACR           LATENCY           LL_FLASH_GetLatency
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0WS
  *         @arg @ref LL_FLASH_LATENCY_1WS
  *         @arg @ref LL_FLASH_LATENCY_2WS
  *         @arg @ref LL_FLASH_LATENCY_3WS
  *         @arg @ref LL_FLASH_LATENCY_4WS
  *         @arg @ref LL_FLASH_LATENCY_5WS
  *         @arg @ref LL_FLASH_LATENCY_6WS
  *         @arg @ref LL_FLASH_LATENCY_7WS
  *         @arg @ref LL_FLASH_LATENCY_8WS
  *         @arg @ref LL_FLASH_LATENCY_9WS
  *         @arg @ref LL_FLASH_LATENCY_10WS
  *         @arg @ref LL_FLASH_LATENCY_11WS
  *         @arg @ref LL_FLASH_LATENCY_12WS
  *         @arg @ref LL_FLASH_LATENCY_13WS
  *         @arg @ref LL_FLASH_LATENCY_14WS
  *         @arg @ref LL_FLASH_LATENCY_15WS
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ACR, FLASH_ACR_LATENCY));
}

/**
  * @brief  Set Flash programming delay.
  * @rmtoll
  *  ACR           WRHIGHFREQ           LL_FLASH_SetProgrammingDelay
  * @param  flashx FLASH instance.
  * @param  delay
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_0
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_1
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_2
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_3
  */
__STATIC_INLINE void LL_FLASH_SetProgrammingDelay(FLASH_TypeDef *flashx, uint32_t delay)
{
  STM32_MODIFY_REG(flashx->ACR, FLASH_ACR_WRHIGHFREQ, delay);
}

/**
  * @brief  Get Flash programming delay.
  * @rmtoll
  *  ACR           WRHIGHFREQ           LL_FLASH_GetProgrammingDelay
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_0
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_1
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_2
  *         @arg @ref LL_FLASH_PROGRAM_DELAY_3
  */
__STATIC_INLINE uint32_t LL_FLASH_GetProgrammingDelay(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ACR, FLASH_ACR_WRHIGHFREQ));
}

/**
  * @brief  Enable flash prefetch.
  * @rmtoll
  *  ACR           PRFTEN           LL_FLASH_EnablePrefetch
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnablePrefetch(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->ACR, FLASH_ACR_PRFTEN);
}

/**
  * @brief  Disable flash prefetch.
  * @rmtoll
  *  ACR           PRFTEN           LL_FLASH_DisablePrefetch
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisablePrefetch(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->ACR, FLASH_ACR_PRFTEN);
}

/**
  * @brief  Check if the flash prefetch is enabled or disabled.
  * @rmtoll
  *  ACR           PRFTEN           LL_FLASH_IsEnabledPrefetch
  * @param  flashx FLASH instance.
  * @retval State of flash prefetch (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPrefetch(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ACR, FLASH_ACR_PRFTEN) == (FLASH_ACR_PRFTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the flash unlock key.
  * @rmtoll
  *  KEYR/SKEYR           KEY/SKEY           LL_FLASH_SetUnlockKey
  * @param  flashx FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_KEY1
  *         @arg @ref LL_FLASH_KEY2
  */
__STATIC_INLINE void LL_FLASH_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_WRITE_REG(flashx->SKEYR, key);
#else
  STM32_WRITE_REG(flashx->KEYR, key);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the flash unlock key for the Non-Secure flash memory.
  * @rmtoll
  *  KEYR           KEY           LL_FLASH_NS_SetUnlockKey
  * @param  flashx FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_KEY1
  *         @arg @ref LL_FLASH_KEY2
  */
__STATIC_INLINE void LL_FLASH_NS_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
  STM32_WRITE_REG(flashx->KEYR, key);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Set the flash OBK unlock key.
  * @rmtoll
  *  OBKKEYR/SOBKKEYR           OBKKEY/SOBKKEY           LL_FLASH_OBK_SetUnlockKey
  * @param  flashx FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OBK_OBKKEY1
  *         @arg @ref LL_FLASH_OBK_OBKKEY2
  */
__STATIC_INLINE void LL_FLASH_OBK_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_WRITE_REG(flashx->SOBKKEYR, key);
#else
  STM32_WRITE_REG(flashx->OBKKEYR, key);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Set the flash option-bytes unlock key.
  * @rmtoll
  *  OPTKEYR           OPTKEY           LL_FLASH_OB_SetUnlockKey
  * @param  flashx FLASH instance.
  * @param  key
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_OPTKEY1
  *         @arg @ref LL_FLASH_OB_OPTKEY2
  */
__STATIC_INLINE void LL_FLASH_OB_SetUnlockKey(FLASH_TypeDef *flashx, uint32_t key)
{
  STM32_WRITE_REG(flashx->OPTKEYR, key);
}

/**
  * @brief  Get the flash interrupted operation address offset.
  * @rmtoll
  *  OPSR           ADDR_OP           LL_FLASH_GetOperInterruptedAddressOffset
  * @param  flashx FLASH instance.
  * @retval Returned value : the flash interrupted operation address offset.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOperInterruptedAddressOffset(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPSR, FLASH_OPSR_ADDR_OP) >> FLASH_OPSR_ADDR_OP_Pos);
}

/**
  * @brief  Read the state of selected operation status flags.
  * @rmtoll
  *  OPSR     DATA_OP|BK_OP|SYSF_OP|OTP_OP     LL_FLASH_ReadFlag_OP
  * @param  flashx FLASH instance.
  * @param  flags
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_DATA_OP
  *         @arg @ref LL_FLASH_FLAG_BK_OP
  *         @arg @ref LL_FLASH_FLAG_SYSF_OP
  *         @arg @ref LL_FLASH_FLAG_OTP_OP
  *         @arg @ref LL_FLASH_FLAG_OP_AREA_ALL
  * @retval Returned value : state of selected operation status flags.
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag_OP(const FLASH_TypeDef *flashx, uint32_t flags)
{
  return (STM32_READ_BIT(flashx->OPSR, flags));
}

/**
  * @brief  Get the flash interrupted operation data flash flag.
  * @rmtoll
  *  OPSR           DATA_OP           LL_FLASH_IsActiveFlag_DATA_OP
  * @param  flashx FLASH instance.
  * @retval State of interrupted operation data flash flag (1: interrupt from data flash / 0: not from data flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_DATA_OP(const FLASH_TypeDef *flashx)
{
  return (((STM32_READ_BIT(flashx->OPSR, FLASH_OPSR_DATA_OP)) == (FLASH_OPSR_DATA_OP)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash interrupted operation bank.
  * @rmtoll
  *  OPSR           BK_OP           LL_FLASH_IsActiveFlag_BK_OP
  * @param  flashx FLASH instance.
  * @retval Returned value : the flash interrupted operation bank (0: bank1 / 1: bank2).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BK_OP(const FLASH_TypeDef *flashx)
{
  return (((STM32_READ_BIT(flashx->OPSR, FLASH_OPSR_BK_OP)) == (FLASH_OPSR_BK_OP)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash interrupted operation system flash flag.
  * @rmtoll
  *  OPSR           SYSF_OP           LL_FLASH_IsActiveFlag_SYSF_OP
  * @param  flashx FLASH instance.
  * @retval State of interrupted operation system flash flag (1: interrupt from system flash / 0: not from system
  *         flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_SYSF_OP(const FLASH_TypeDef *flashx)
{
  return (((STM32_READ_BIT(flashx->OPSR, FLASH_OPSR_SYSF_OP)) == (FLASH_OPSR_SYSF_OP)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash interrupted operation OTP flash flag.
  * @rmtoll
  *  OPSR           OTP_OP           LL_FLASH_IsActiveFlag_OTP_OP
  * @param  flashx FLASH instance.
  * @retval State of interrupted operation OTP flash flag (1: interrupt from OTP flash / 0: not from OTP flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OTP_OP(const FLASH_TypeDef *flashx)
{
  return (((STM32_READ_BIT(flashx->OPSR, FLASH_OPSR_OTP_OP)) == (FLASH_OPSR_OTP_OP)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash interrupted operation code.
  * @rmtoll
  *  OPSR           CODE_OP           LL_FLASH_GetOperInterruptedCode
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_INTERRUPTED_NO_OPERATION
  *         @arg @ref LL_FLASH_INTERRUPTED_SINGLE_WRITE
  *         @arg @ref LL_FLASH_INTERRUPTED_PAGE_ERASE
  *         @arg @ref LL_FLASH_INTERRUPTED_BANK_ERASE
  *         @arg @ref LL_FLASH_INTERRUPTED_MASS_ERASE
  *         @arg @ref LL_FLASH_INTERRUPTED_OB_CHANGE
  */
__STATIC_INLINE uint32_t LL_FLASH_GetOperInterruptedCode(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPSR, FLASH_OPSR_CODE_OP));
}

/**
  * @brief  Start the flash option-bytes modification.
  * @rmtoll
  *  OPTCR           OPTSTRT           LL_FLASH_OB_StartModification
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_StartModification(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTCR, FLASH_OPTCR_OPTSTRT);
}

/**
  * @brief  Lock the flash option-bytes control access registers.
  * @rmtoll
  *  OPTCR           OPTLOCK           LL_FLASH_OB_Lock
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_Lock(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTCR, FLASH_OPTCR_OPTLOCK);
}

/**
  * @brief  Check the flash option-bytes control access registers lock state.
  * @rmtoll
  *  OPTCR           OPTLOCK           LL_FLASH_OB_IsLocked
  * @param  flashx FLASH instance.
  * @retval State of flash option-bytes lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLocked(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTCR, FLASH_OPTCR_OPTLOCK) == (FLASH_OPTCR_OPTLOCK)) ? 1UL : 0UL);
}

/** @defgroup FLASH_LL_EF_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief  Check if any of the selected flag is active.
  * @rmtoll
  *  SSR/SR       BSY|WBNE|DBNE     LL_FLASH_IsActiveFlag
  * @param  flashx FLASH instance.
  * @param  flags
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WBNE
  *         @arg @ref LL_FLASH_FLAG_PUF_STATE
  *         @arg @ref LL_FLASH_FLAG_DBNE
  *         @arg @ref LL_FLASH_FLAG_STATUS_ALL
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_OPTCHANGEERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  * @retval State of selected flag (1 if at least one is active / 0 if none of the selected flags are active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag(const FLASH_TypeDef *flashx, uint32_t flags)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, flags) != 0U) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, flags) != 0U) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if any of the selected flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR       BSY|WBNE|DBNE     LL_FLASH_NS_IsActiveFlag
  * @param  flashx FLASH instance.
  * @param  flags
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WBNE
  *         @arg @ref LL_FLASH_FLAG_PUF_STATE
  *         @arg @ref LL_FLASH_FLAG_DBNE
  *         @arg @ref LL_FLASH_FLAG_STATUS_ALL
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_OPTCHANGEERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  * @retval State of selected flag (1 if at least one is active / 0 if none of the selected flags are active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag(const FLASH_TypeDef *flashx, uint32_t flags)
{
  return ((STM32_READ_BIT(flashx->SR, flags) != 0U) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Read the state of selected flash operation error flag.
  * @rmtoll
  *  SR      EOP/WRPERR/PGSERR/STRBERR/INCERR/OPTCHANGEERR      LL_FLASH_ReadFlag
  * @param  flashx FLASH instance.
  * @param  flags
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WBNE
  *         @arg @ref LL_FLASH_FLAG_PUF_STATE
  *         @arg @ref LL_FLASH_FLAG_DBNE
  *         @arg @ref LL_FLASH_FLAG_STATUS_ALL
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_OPTCHANGEERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  * @retval State of selected flags (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag(const FLASH_TypeDef *flashx, uint32_t flags)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return (STM32_READ_REG(flashx->SSR) & flags);
#else
  return (STM32_READ_REG(flashx->SR) & flags);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Read the state of selected flash operation error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR      EOP/WRPERR/PGSERR/STRBERR/INCERR/OPTCHANGEERR      LL_FLASH_NS_ReadFlag
  * @param  flashx FLASH instance.
  * @param  flags
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_BSY
  *         @arg @ref LL_FLASH_FLAG_WBNE
  *         @arg @ref LL_FLASH_FLAG_PUF_STATE
  *         @arg @ref LL_FLASH_FLAG_DBNE
  *         @arg @ref LL_FLASH_FLAG_STATUS_ALL
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_OPTCHANGEERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  * @retval State of selected flags (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_ReadFlag(const FLASH_TypeDef *flashx, uint32_t flags)
{
  return (STM32_READ_REG(flashx->SR) & flags);
}
#endif /*CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash operation error flag.
  * @rmtoll
  *  SR/SSR      EOP/WRPERR/PGSERR/STRBERR/OBKERR/OBKWERR/OPTCHANGEERR      LL_FLASH_ClearFlag
  * @param  flashx FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_OBKERR
  *         @arg @ref LL_FLASH_FLAG_OBKWERR
  *         @arg @ref LL_FLASH_FLAG_OPTCHANGEERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  */
__STATIC_INLINE void LL_FLASH_ClearFlag(FLASH_TypeDef *flashx, uint32_t flag)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, flag);
#else
  STM32_SET_BIT(flashx->CCR, flag);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash operation error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR      EOP/WRPERR/PGSERR/STRBERR/OBKERR/OBKWERR/OPTCHANGEERR      LL_FLASH_NS_ClearFlag
  * @param  flashx FLASH instance.
  * @param  flag
  *         This parameter can be a combination of the following values :
  *         @arg @ref LL_FLASH_FLAG_EOP
  *         @arg @ref LL_FLASH_FLAG_WRPERR
  *         @arg @ref LL_FLASH_FLAG_PGSERR
  *         @arg @ref LL_FLASH_FLAG_STRBERR
  *         @arg @ref LL_FLASH_FLAG_INCERR
  *         @arg @ref LL_FLASH_FLAG_OBKERR
  *         @arg @ref LL_FLASH_FLAG_OBKWERR
  *         @arg @ref LL_FLASH_FLAG_OPTCHANGEERR
  *         @arg @ref LL_FLASH_FLAG_ERRORS_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag(FLASH_TypeDef *flashx, uint32_t flag)
{
  STM32_SET_BIT(flashx->CCR, flag);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash busy flag is active.
  * @rmtoll
  *  SR/SSR           BSY           LL_FLASH_IsActiveFlag_BSY
  * @param  flashx FLASH instance.
  * @retval State of BSY flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BSY(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_BSY) == (FLASH_SR_BSY)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_BSY) == (FLASH_SR_BSY)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash busy flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           BSY           LL_FLASH_NS_IsActiveFlag_BSY
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure BSY flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_BSY(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_BSY) == (FLASH_SR_BSY)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the write buffer not empty flag is active.
  * @rmtoll
  *  SR/SSR           WBNE           LL_FLASH_IsActiveFlag_WBNE
  * @param  flashx FLASH instance.
  * @retval State of WBNE flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WBNE(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_WBNE) == (FLASH_SR_WBNE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_WBNE) == (FLASH_SR_WBNE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the write buffer not empty flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           WBNE           LL_FLASH_NS_IsActiveFlag_WBNE
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure WBNE flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_WBNE(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_WBNE) == (FLASH_SR_WBNE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the data buffer not empty flag is active.
  * @rmtoll
  *  SR/SSR           PUF_STATE           LL_FLASH_IsActiveFlag_PUFState
  * @param  flashx FLASH instance.
  * @retval State of PUF_STATE flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PUFState(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_PUF_STATE) == (FLASH_SR_PUF_STATE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_PUF_STATE) == (FLASH_SR_PUF_STATE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the data buffer not empty flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           PUF_STATE           LL_FLASH_NS_IsActiveFlag_PUFState
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure PUF_STATE flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_PUFState(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_PUF_STATE) == (FLASH_SR_PUF_STATE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the data buffer not empty flag is active.
  * @rmtoll
  *  SR/SSR           DBNE           LL_FLASH_IsActiveFlag_DBNE
  * @param  flashx FLASH instance.
  * @retval State of DBNE flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_DBNE(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_DBNE) == (FLASH_SR_DBNE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_DBNE) == (FLASH_SR_DBNE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the data buffer not empty flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           DBNE           LL_FLASH_NS_IsActiveFlag_DBNE
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure DBNE flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_DBNE(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_DBNE) == (FLASH_SR_DBNE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash end of operation flag is active.
  * @rmtoll
  *  SR/SSR           EOP           LL_FLASH_IsActiveFlag_EOP
  * @param  flashx FLASH instance.
  * @retval State of EOP flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_EOP(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_EOP) == (FLASH_SR_EOP)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_EOP) == (FLASH_SR_EOP)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash end of operation flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           EOP           LL_FLASH_NS_IsActiveFlag_EOP
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure EOP flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_EOP(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_EOP) == (FLASH_SR_EOP)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash end of operation flag.
  * @rmtoll
  *  SR/SSR           EOP           LL_FLASH_ClearFlag_EOP
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_EOP(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, FLASH_CCR_EOP);
#else
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_EOP);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash end of operation flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           EOP           LL_FLASH_NS_ClearFlag_EOP
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_EOP(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_EOP);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash write protection error flag is active.
  * @rmtoll
  *  SR/SSR           WRPERR           LL_FLASH_IsActiveFlag_WRPERR
  * @param  flashx FLASH instance.
  * @retval State of ERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WRPERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_WRPERR) == (FLASH_SR_WRPERR)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_WRPERR) == (FLASH_SR_WRPERR)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash write protection error flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           WRPERR           LL_FLASH_NS_IsActiveFlag_WRPERR
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure ERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_WRPERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_WRPERR) == (FLASH_SR_WRPERR)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash write protection error flag.
  * @rmtoll
  *  SR/SSR           WRPERR           LL_FLASH_ClearFlag_WRPERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_WRPERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, FLASH_CCR_WRPERR);
#else
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_WRPERR);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash write protection error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           WRPERR           LL_FLASH_NS_ClearFlag_WRPERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_WRPERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_WRPERR);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash programming sequence error flag is active.
  * @rmtoll
  *  SR/SSR           PGSERR           LL_FLASH_IsActiveFlag_PGSERR
  * @param  flashx FLASH instance.
  * @retval State of PGSERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_PGSERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_PGSERR) == (FLASH_SR_PGSERR)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_PGSERR) == (FLASH_SR_PGSERR)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash programming sequence error flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           PGSERR           LL_FLASH_NS_IsActiveFlag_PGSERR
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure PGSERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_PGSERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_PGSERR) == (FLASH_SR_PGSERR)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash programming sequence error flag.
  * @rmtoll
  *  SR/SSR           PGSERR           LL_FLASH_ClearFlag_PGSERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_PGSERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, FLASH_CCR_PGSERR);
#else
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_PGSERR);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash programming sequence error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           PGSERR           LL_FLASH_NS_ClearFlag_PGSERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_PGSERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_PGSERR);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash strobe error flag is active.
  * @rmtoll
  *  SR/SSR           STRBERR           LL_FLASH_IsActiveFlag_STRBERR
  * @param  flashx FLASH instance.
  * @retval State of STRBERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_STRBERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_STRBERR) == (FLASH_SR_STRBERR)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_STRBERR) == (FLASH_SR_STRBERR)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash strobe error flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           STRBERR           LL_FLASH_NS_IsActiveFlag_STRBERR
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure STRBERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_STRBERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_STRBERR) == (FLASH_SR_STRBERR)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash strobe error flag.
  * @rmtoll
  *  SR/SSR           STRBERR           LL_FLASH_ClearFlag_STRBERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_STRBERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, FLASH_CCR_STRBERR);
#else
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_STRBERR);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash strobe error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           STRBERR           LL_FLASH_NS_ClearFlag_STRBERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_STRBERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_STRBERR);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash inconsistency error flag is active.
  * @rmtoll
  *  SR/SSR           INCERR           LL_FLASH_IsActiveFlag_INCERR
  * @param  flashx FLASH instance.
  * @retval State of INCERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_INCERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_INCERR) == (FLASH_SR_INCERR)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_INCERR) == (FLASH_SR_INCERR)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash inconsistency error flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           INCERR           LL_FLASH_NS_IsActiveFlag_INCERR
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure INCERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_INCERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_INCERR) == (FLASH_SR_INCERR)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash inconsistency error flag.
  * @rmtoll
  *  SR/SSR           INCERR           LL_FLASH_ClearFlag_INCERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_INCERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, FLASH_CCR_INCERR);
#else
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_INCERR);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash inconsistency error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           INCERR           LL_FLASH_NS_ClearFlag_INCERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_INCERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_INCERR);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash OBK general error flag is active.
  * @rmtoll
  *  SR/SSR           OBKERR           LL_FLASH_IsActiveFlag_OBKERR
  * @param  flashx FLASH instance.
  * @retval State of OBKERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OBKERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_OBKERR) == (FLASH_SR_OBKERR)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_OBKERR) == (FLASH_SR_OBKERR)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash OBK general error flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           OBKERR           LL_FLASH_NS_IsActiveFlag_OBKERR
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure OBKERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_OBKERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_OBKERR) == (FLASH_SR_OBKERR)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash OBK general error flag.
  * @rmtoll
  *  SR/SSR           OBKERR           LL_FLASH_ClearFlag_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OBKERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, FLASH_CCR_OBKERR);
#else
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_OBKERR);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash OBK general error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           OBKERR           LL_FLASH_NS_ClearFlag_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_OBKERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_OBKERR);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash OBK write error flag is active.
  * @rmtoll
  *  SR/SSR           OBKWERR           LL_FLASH_IsActiveFlag_OBKWERR
  * @param  flashx FLASH instance.
  * @retval State of OBKWERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OBKWERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SSR, FLASH_SR_OBKWERR) == (FLASH_SR_OBKWERR)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_OBKWERR) == (FLASH_SR_OBKWERR)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash OBK write error flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           OBKWERR           LL_FLASH_NS_IsActiveFlag_OBKWERR
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure OBKWERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_OBKWERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_OBKWERR) == (FLASH_SR_OBKWERR)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Clear the flash OBK write error flag.
  * @rmtoll
  *  SR/SSR           OBKWERR           LL_FLASH_ClearFlag_OBKWERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OBKWERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCCR, FLASH_CCR_OBKWERR);
#else
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_OBKWERR);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash OBK write error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           OBKWERR           LL_FLASH_NS_ClearFlag_OBKWERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_OBKWERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_OBKWERR);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash option-byte change error flag is active for the Non-Secure flash memory.
  * @rmtoll
  *  SR           OPTCHANGEERR           LL_FLASH_NS_IsActiveFlag_OPTCHANGEERR
  * @param  flashx FLASH instance.
  * @retval State of Non-Secure OPTCHANGEERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsActiveFlag_OPTCHANGEERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_OPTCHANGEERR) == (FLASH_SR_OPTCHANGEERR)) ? 1UL : 0UL);
}
#else
/**
  * @brief  Check if the flash option-byte change error flag is active.
  * @rmtoll
  *  SR                 OPTCHANGEERR           LL_FLASH_IsActiveFlag_OPTCHANGEERR
  * @param  flashx FLASH instance.
  * @retval State of OPTCHANGEERR flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OPTCHANGEERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->SR, FLASH_SR_OPTCHANGEERR) == (FLASH_SR_OPTCHANGEERR)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Clear the flash option-byte change error flag for the Non-Secure flash memory.
  * @rmtoll
  *  SR           OPTCHANGEERR           LL_FLASH_NS_ClearFlag_OPTCHANGEERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_ClearFlag_OPTCHANGEERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_OPTCHANGEERR);
}
#else
/**
  * @brief  Clear the flash option-byte change error flag.
  * @rmtoll
  *  SR                 OPTCHANGEERR           LL_FLASH_ClearFlag_OPTCHANGEERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OPTCHANGEERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CCR, FLASH_CCR_OPTCHANGEERR);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Lock the flash control access registers.
  * @rmtoll
  *  CR/SCR        LOCK           LL_FLASH_Lock
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_Lock(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_LOCK);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_LOCK);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the flash control access registers for the Non-Secure flash memory.
  * @rmtoll
  *  CR              LOCK           LL_FLASH_NS_Lock
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_Lock(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_LOCK);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check the flash control access registers lock state.
  * @rmtoll
  *  CR/SCR   LOCK           LL_FLASH_IsLocked
  * @param  flashx FLASH instance.
  * @retval State of flash lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsLocked(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_LOCK) == (FLASH_CR_LOCK)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_LOCK) == (FLASH_CR_LOCK)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check the flash control access registers lock state for the Non-Secure flash memory.
  * @rmtoll
  *  CR         LOCK           LL_FLASH_NS_IsLocked
  * @param  flashx FLASH instance.
  * @retval State of flash lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsLocked(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_LOCK) == (FLASH_CR_LOCK)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash programming.
  * @rmtoll
  *  CR/SCR           PG           LL_FLASH_EnableProgramming
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableProgramming(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_PG);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_PG);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash programming for the Non-Secure flash memory.
  * @rmtoll
  *  CR           PG           LL_FLASH_NS_EnableProgramming
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableProgramming(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_PG);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash programming.
  * @rmtoll
  *  CR/SCR           PG           LL_FLASH_DisableProgramming
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableProgramming(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_PG);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_PG);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash programming for the Non-Secure flash memory.
  * @rmtoll
  *  CR           PG           LL_FLASH_NS_DisableProgramming
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableProgramming(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_PG);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash programming is enabled or disabled.
  * @rmtoll
  *  CR/SCR           PG           LL_FLASH_IsEnabledProgramming
  * @param  flashx FLASH instance.
  * @retval State of flash programming (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledProgramming(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_PG) == (FLASH_CR_PG)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_PG) == (FLASH_CR_PG)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash programming is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR           PG           LL_FLASH_NS_IsEnabledProgramming
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure programming (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledProgramming(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_PG) == (FLASH_CR_PG)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash page erase.
  * @rmtoll
  *  CR/SCR           SER           LL_FLASH_EnablePageErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnablePageErase(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_PER);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_PER);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash page erase for the Non-Secure flash memory.
  * @rmtoll
  *  CR           SER           LL_FLASH_NS_EnablePageErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnablePageErase(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_PER);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash page erase.
  * @rmtoll
  *  CR/SCR           SER           LL_FLASH_DisablePageErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisablePageErase(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_PER);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_PER);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash page erase for the Non-Secure flash memory.
  * @rmtoll
  *  CR           SER           LL_FLASH_NS_DisablePageErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisablePageErase(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_PER);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash page erase is enabled or disabled.
  * @rmtoll
  *  CR/SCR           SER           LL_FLASH_IsEnabledPageErase
  * @param  flashx FLASH instance.
  * @retval State of flash page erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageErase(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_PER) == (FLASH_CR_PER)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_PER) == (FLASH_CR_PER)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash page erase is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR           SER           LL_FLASH_NS_IsEnabledPageErase
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure page erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledPageErase(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_PER) == (FLASH_CR_PER)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash bank erase.
  * @rmtoll
  *  SCR/CR        BKSEL/BER           LL_FLASH_EnableBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_EnableBankErase(FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SCR, (FLASH_CR_BKSEL | FLASH_CR_BER), (bank | FLASH_CR_BER));
#else
  STM32_MODIFY_REG(flashx->CR, (FLASH_CR_BKSEL | FLASH_CR_BER), (bank | FLASH_CR_BER));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash bank erase for the Non-Secure flash memory.
  * @rmtoll
  *  SCR/CR        BKSEL/BER           LL_FLASH_NS_EnableBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_NS_EnableBankErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  STM32_MODIFY_REG(flashx->CR, (FLASH_CR_BKSEL | FLASH_CR_BER), (bank | FLASH_CR_BER));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash bank erase.
  * @rmtoll
  *  SCR/CR           BKSEL/BER           LL_FLASH_DisableBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_DisableBankErase(FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, (bank | FLASH_CR_BER));
#else
  STM32_CLEAR_BIT(flashx->CR, (bank | FLASH_CR_BER));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash bank erase for the Non-Secure flash memory.
  * @rmtoll
  *  CR           BKSEL/BER           LL_FLASH_NS_DisableBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_NS_DisableBankErase(FLASH_TypeDef *flashx, uint32_t bank)
{
  STM32_CLEAR_BIT(flashx->CR, (bank | FLASH_CR_BER));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash bank erase is enabled or disabled.
  * @rmtoll
  *  SCR/CR           BKSEL/BER           LL_FLASH_IsEnabledBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  * @retval State of flash mass erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledBankErase(const FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, (FLASH_CR_BKSEL | FLASH_CR_BER)) == (bank | FLASH_CR_BER)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, (FLASH_CR_BKSEL | FLASH_CR_BER)) == (bank | FLASH_CR_BER)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash bank erase is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR           BKSEL/BER           LL_FLASH_NS_IsEnabledBankErase
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  * @retval State of flash Non-Secure bank erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledBankErase(const FLASH_TypeDef *flashx, uint32_t bank)
{
  return ((STM32_READ_BIT(flashx->CR, (FLASH_CR_BKSEL | FLASH_CR_BER)) == (bank | FLASH_CR_BER)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash programming.
  * @rmtoll
  *  CR/SCR           FW           LL_FLASH_EnableForceWrite
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableForceWrite(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_FW);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_FW);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash programming for the Non-Secure flash memory.
  * @rmtoll
  *  CR           FW           LL_FLASH_NS_EnableForceWrite
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableForceWrite(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_FW);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash programming is enabled or disabled.
  * @rmtoll
  *  CR/SCR           FW           LL_FLASH_IsEnabledForceWrite
  * @param  flashx FLASH instance.
  * @retval State of flash programming (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledForceWrite(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_FW) == (FLASH_CR_FW)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_FW) == (FLASH_CR_FW)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash programming is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR           FW           LL_FLASH_NS_IsEnabledForceWrite
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure programming (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledForceWrite(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_FW) == (FLASH_CR_FW)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Start the flash erase operation.
  * @rmtoll
  *  CR/SCR           STRT           LL_FLASH_StartEraseOperation
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_StartEraseOperation(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_STRT);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_STRT);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Start the flash erase operation for the Non-Secure flash memory.
  * @rmtoll
  *  CR           STRT           LL_FLASH_NS_StartEraseOperation
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_StartEraseOperation(FLASH_TypeDef *flashx)
{
  STM32_UNUSED(flashx);

  STM32_SET_BIT(FLASH_NS->CR, FLASH_CR_STRT);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Set the flash page erase index.
  * @rmtoll
  *  CR/SCR           BKSEL/PNB           LL_FLASH_SetPageEraseIndex
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  * @param  page_idx This parameter a value in [0:31]
  */
__STATIC_INLINE void LL_FLASH_SetPageEraseIndex(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_idx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SCR, FLASH_CR_BKSEL | FLASH_CR_PNB, (bank | (page_idx << FLASH_CR_PNB_Pos)));
#else
  STM32_MODIFY_REG(flashx->CR, FLASH_CR_BKSEL | FLASH_CR_PNB, (bank | (page_idx << FLASH_CR_PNB_Pos)));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the flash page erase index for the Non-Secure flash memory.
  * @rmtoll
  *  CR           BKSEL/PNB           LL_FLASH_NS_SetPageEraseIndex
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  * @param  page_idx This parameter a value in [0:31]
  */
__STATIC_INLINE void LL_FLASH_NS_SetPageEraseIndex(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_idx)
{
  STM32_MODIFY_REG(flashx->CR, FLASH_CR_BKSEL | FLASH_CR_PNB, (bank | (page_idx << FLASH_CR_PNB_Pos)));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Start the flash erase page.
  * @rmtoll
  *  CR           BKER/PNB/PER/STRT           LL_FLASH_StartErasePage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  * @param  page This parameter can take any value in [0:31]
  */
__STATIC_INLINE void LL_FLASH_StartErasePage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SCR, (FLASH_CR_BKSEL | FLASH_CR_PNB | FLASH_CR_STRT | FLASH_CR_PER),
                   (bank | (page << FLASH_CR_PNB_Pos) | FLASH_CR_STRT | FLASH_CR_PER));
#else
  STM32_MODIFY_REG(flashx->CR, (FLASH_CR_BKSEL | FLASH_CR_PNB | FLASH_CR_STRT | FLASH_CR_PER),
                   (bank | (page << FLASH_CR_PNB_Pos) | FLASH_CR_STRT | FLASH_CR_PER));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Start the flash erase page for the Non-Secure flash memory.
  * @rmtoll
  *  CR           BKER/PNB/PER/STRT           LL_FLASH_NS_StartErasePage
  * @param  flashx FLASH instance.
  * @param  bank   This parameter can be one of the following values:
  *                @arg @ref LL_FLASH_ERASE_BANK_1
  *                @arg @ref LL_FLASH_ERASE_BANK_2
  * @param  page   This parameter can take any value in [0:31]
  */
__STATIC_INLINE void LL_FLASH_NS_StartErasePage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  STM32_UNUSED(flashx);

  STM32_MODIFY_REG(FLASH_NS->CR, (FLASH_CR_BKSEL | FLASH_CR_PNB | FLASH_CR_STRT | FLASH_CR_PER),
                   (bank | (page << FLASH_CR_PNB_Pos) | FLASH_CR_STRT | FLASH_CR_PER));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Start the flash erase bank.
  * @rmtoll
  *  CR           BER/STRT           LL_FLASH_StartEraseBank
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_StartEraseBank(FLASH_TypeDef *flashx, uint32_t bank)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SCR, (FLASH_CR_BKSEL | FLASH_CR_BER | FLASH_CR_STRT), (bank | FLASH_CR_BER | FLASH_CR_STRT));
#else
  STM32_MODIFY_REG(flashx->CR, (FLASH_CR_BKSEL | FLASH_CR_BER | FLASH_CR_STRT), (bank | FLASH_CR_BER | FLASH_CR_STRT));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Start the flash erase bank for the Non-Secure flash memory.
  * @rmtoll
  *  CR           BER/STRT           LL_FLASH_NS_StartEraseBank
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_ERASE_BANK_1
  *         @arg @ref LL_FLASH_ERASE_BANK_2
  */
__STATIC_INLINE void LL_FLASH_NS_StartEraseBank(FLASH_TypeDef *flashx, uint32_t bank)
{
  STM32_UNUSED(flashx);

  STM32_MODIFY_REG(FLASH_NS->CR, (FLASH_CR_BKSEL | FLASH_CR_BER | FLASH_CR_STRT),
                   (bank | FLASH_CR_BER | FLASH_CR_STRT));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Start the flash PUF operation.
  * @rmtoll
  *  CR/SCR           PUF_LAUNCH           LL_FLASH_StartPUFOperation
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_StartPUFOperation(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_PUF_LAUNCH);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_PUF_LAUNCH);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Start the flash mass erase operation.
  * @rmtoll
  *  CR/SCR           MER/STRT           LL_FLASH_StartMassErase
  * @param  flashx FLASH instance.

  */
__STATIC_INLINE void LL_FLASH_StartMassErase(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, (FLASH_CR_MER | FLASH_CR_STRT));
#else
  STM32_SET_BIT(flashx->CR, (FLASH_CR_MER | FLASH_CR_STRT));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Start the flash mass erase operation for the Non-Secure flash memory.
  * @rmtoll
  *  CR           MER/STRT           LL_FLASH_NS_StartMassErase
  * @param  flashx FLASH instance.

  */
__STATIC_INLINE void LL_FLASH_NS_StartMassErase(FLASH_TypeDef *flashx)
{
  STM32_UNUSED(flashx);

  STM32_SET_BIT(FLASH_NS->CR, (FLASH_CR_MER | FLASH_CR_STRT));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable all flash operation.
  * @rmtoll
  *  CR/SCR           EOPIE/PG/PER/MER/BER           LL_FLASH_DisableAllOperation
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableAllOperation(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, LL_FLASH_IT_ALL | FLASH_CR_PG \
                  | FLASH_CR_PER | FLASH_CR_MER | FLASH_CR_BER);
#else
  STM32_CLEAR_BIT(flashx->CR, LL_FLASH_IT_ALL | FLASH_CR_PG \
                  | FLASH_CR_PER | FLASH_CR_MER | FLASH_CR_BER);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable all flash operation for the Non-Secure flash memory.
  * @rmtoll
  *  CR           EOPIE/ERRIE/PG/PER/MER1/MER2          LL_FLASH_NS_DisableAllOperation
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableAllOperation(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, LL_FLASH_IT_ALL | FLASH_CR_PG \
                  | FLASH_CR_PER | FLASH_CR_MER | FLASH_CR_BER);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash bank mass erase.
  * @rmtoll
  *  CR/SCR           MER/BER/BKSEL           LL_FLASH_EnableMassErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableMassErase(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_MER);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_MER);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash bank mass erase for the Non-Secure flash memory.
  * @rmtoll
  *  CR           MER/BER/BKSEL           LL_FLASH_NS_EnableMassErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableMassErase(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_MER);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash bank mass erase.
  * @rmtoll
  *  CR/SCR           MER/BER/BKSEL           LL_FLASH_DisableMassErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableMassErase(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_MER);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_MER);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash bank mass erase for the Non-Secure flash memory.
  * @rmtoll
  *  CR           MER/BER/BKSEL           LL_FLASH_NS_DisableMassErase
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableMassErase(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_MER);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash bank mass erase is enabled or disabled.
  * @rmtoll
  *  CR/SCR           MER1/MER2           LL_FLASH_IsEnabledMassErase
  * @param  flashx FLASH instance.
  * @retval State of flash mass erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledMassErase(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_MER) == (FLASH_CR_MER)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_MER) == (FLASH_CR_MER)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash bank mass erase is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR           MER1/MER2           LL_FLASH_NS_IsEnabledMassErase
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure mass erase (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledMassErase(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_MER) == (FLASH_CR_MER)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash interrupt.
  * @rmtoll
  *  CR/SCR EOPIE/WRPERRIE/PGSERRIE/STRBERRIE/INCERRIE/OBKERRIE/OBKWERRIE/OPTCHANGEERRIE LL_FLASH_EnableIT
  * @param  flashx FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_WRPERR
  *         @arg @ref LL_FLASH_IT_PGSERR
  *         @arg @ref LL_FLASH_IT_STRBERR
  *         @arg @ref LL_FLASH_IT_INCERR
  *         @arg @ref LL_FLASH_IT_OBKERR
  *         @arg @ref LL_FLASH_IT_OBKWERR
  *         @arg @ref LL_FLASH_IT_OPTCHANGEERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_EnableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, interrupt);
#else
  STM32_SET_BIT(flashx->CR, interrupt);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR EOPIE/WRPERRIE/PGSERRIE/STRBERRIE/INCERRIE/OBKERRIE/OBKWERRIE/OPTCHANGEERRIE LL_FLASH_NS_EnableIT
  * @param  flashx FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_WRPERR
  *         @arg @ref LL_FLASH_IT_PGSERR
  *         @arg @ref LL_FLASH_IT_STRBERR
  *         @arg @ref LL_FLASH_IT_INCERR
  *         @arg @ref LL_FLASH_IT_OBKERR
  *         @arg @ref LL_FLASH_IT_OBKWERR
  *         @arg @ref LL_FLASH_IT_OPTCHANGEERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
  STM32_SET_BIT(flashx->CR, interrupt);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash interrupt.
  * @rmtoll
  *  CR/SCR EOPIE/WRPERRIE/PGSERRIE/STRBERRIE/INCERRIE/OBKERRIE/OBKWERRIE/OPTCHANGEERRIE LL_FLASH_DisableIT
  * @param  flashx FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_WRPERR
  *         @arg @ref LL_FLASH_IT_PGSERR
  *         @arg @ref LL_FLASH_IT_STRBERR
  *         @arg @ref LL_FLASH_IT_INCERR
  *         @arg @ref LL_FLASH_IT_OBKERR
  *         @arg @ref LL_FLASH_IT_OBKWERR
  *         @arg @ref LL_FLASH_IT_OPTCHANGEERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_DisableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, interrupt);
#else
  STM32_CLEAR_BIT(flashx->CR, interrupt);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR EOPIE/WRPERRIE/PGSERRIE/STRBERRIE/INCERRIE/OBKERRIE/OBKWERRIE/OPTCHANGEERRIE LL_FLASH_NS_DisableIT
  * @param  flashx FLASH instance.
  * @param  interrupt
  *         This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IT_EOP
  *         @arg @ref LL_FLASH_IT_WRPERR
  *         @arg @ref LL_FLASH_IT_PGSERR
  *         @arg @ref LL_FLASH_IT_STRBERR
  *         @arg @ref LL_FLASH_IT_INCERR
  *         @arg @ref LL_FLASH_IT_OBKERR
  *         @arg @ref LL_FLASH_IT_OBKWERR
  *         @arg @ref LL_FLASH_IT_OPTCHANGEERR
  *         @arg @ref LL_FLASH_IT_ALL
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT(FLASH_TypeDef *flashx, uint32_t interrupt)
{
  STM32_CLEAR_BIT(flashx->CR, interrupt);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash end of operation interrupt.
  * @rmtoll
  *  CR/SCR          EOPIE        LL_FLASH_EnableIT_EOP
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_EOP(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_EOPIE);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_EOPIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash end of operation interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          EOPIE        LL_FLASH_NS_EnableIT_EOP
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_EOP(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_EOPIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash end of operation interrupt.
  * @rmtoll
  *  CR          EOPIE        LL_FLASH_DisableIT_EOP
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_EOP(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_EOPIE);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_EOPIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash end of operation interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          EOPIE        LL_FLASH_NS_DisableIT_EOP
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_EOP(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_EOPIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash end of operation interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          EOPIE        LL_FLASH_IsEnabledIT_EOP
  * @param  flashx FLASH instance.
  * @retval State of flash EOP interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_EOP(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_EOPIE) == (FLASH_CR_EOPIE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_EOPIE) == (FLASH_CR_EOPIE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash end of operation interrupt is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR          EOPIE        LL_FLASH_NS_IsEnabledIT_EOP
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure EOP interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_EOP(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_EOPIE) == (FLASH_CR_EOPIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          WRPERRIE        LL_FLASH_EnableIT_WRPERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_WRPERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_WRPERRIE);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_WRPERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          WRPERRIE        LL_FLASH_NS_EnableIT_WRPERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_WRPERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_WRPERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          WRPERRIE        LL_FLASH_DisableIT_WRPERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_WRPERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_WRPERRIE);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_WRPERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          WRPERRIE        LL_FLASH_NS_DisableIT_WRPERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_WRPERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_WRPERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          WRPERRIE        LL_FLASH_IsEnabledIT_WRPERR
  * @param  flashx FLASH instance.
  * @retval State of flash WRPERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_WRPERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_WRPERRIE) == (FLASH_CR_WRPERRIE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_WRPERRIE) == (FLASH_CR_WRPERRIE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash error interrupt is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR          WRPERRIE        LL_FLASH_NS_IsEnabledIT_WRPERR
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure WRPERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_WRPERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_WRPERRIE) == (FLASH_CR_WRPERRIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          PGSERRIE        LL_FLASH_EnableIT_PGSERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_PGSERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_PGSERRIE);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_PGSERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          PGSERRIE        LL_FLASH_NS_EnableIT_PGSERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_PGSERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_PGSERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          PGSERRIE        LL_FLASH_DisableIT_PGSERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_PGSERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_PGSERRIE);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_PGSERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          PGSERRIE        LL_FLASH_NS_DisableIT_PGSERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_PGSERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_PGSERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          PGSERRIE        LL_FLASH_IsEnabledIT_PGSERR
  * @param  flashx FLASH instance.
  * @retval State of flash PGSERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_PGSERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_PGSERRIE) == (FLASH_CR_PGSERRIE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_PGSERRIE) == (FLASH_CR_PGSERRIE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash error interrupt is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR          PGSERRIE        LL_FLASH_NS_IsEnabledIT_PGSERR
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure PGSERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_PGSERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_PGSERRIE) == (FLASH_CR_PGSERRIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          STRBERRIE        LL_FLASH_EnableIT_STRBERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_STRBERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_STRBERRIE);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_STRBERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          STRBERRIE        LL_FLASH_NS_EnableIT_STRBERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_STRBERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_STRBERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          STRBERRIE        LL_FLASH_DisableIT_STRBERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_STRBERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_STRBERRIE);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_STRBERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          STRBERRIE        LL_FLASH_NS_DisableIT_STRBERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_STRBERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_STRBERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          STRBERRIE        LL_FLASH_IsEnabledIT_STRBERR
  * @param  flashx FLASH instance.
  * @retval State of flash STRBERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_STRBERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_STRBERRIE) == (FLASH_CR_STRBERRIE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_STRBERRIE) == (FLASH_CR_STRBERRIE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash error interrupt is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR          STRBERRIE        LL_FLASH_NS_IsEnabledIT_STRBERR
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure STRBERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_STRBERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_STRBERRIE) == (FLASH_CR_STRBERRIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          INCERRIE        LL_FLASH_EnableIT_INCERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_INCERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_INCERRIE);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_INCERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          INCERRIE        LL_FLASH_NS_EnableIT_INCERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_INCERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_INCERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          INCERRIE        LL_FLASH_DisableIT_INCERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_INCERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_INCERRIE);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_INCERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          INCERRIE        LL_FLASH_NS_DisableIT_INCERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_INCERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_INCERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          INCERRIE        LL_FLASH_IsEnabledIT_INCERR
  * @param  flashx FLASH instance.
  * @retval State of flash INCERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_INCERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_INCERRIE) == (FLASH_CR_INCERRIE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_INCERRIE) == (FLASH_CR_INCERRIE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash error interrupt is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR          INCERRIE        LL_FLASH_NS_IsEnabledIT_INCERR
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure INCERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_INCERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_INCERRIE) == (FLASH_CR_INCERRIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          OBKERRIE        LL_FLASH_EnableIT_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_OBKERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_OBKERRIE);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_OBKERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          OBKERRIE        LL_FLASH_NS_EnableIT_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_OBKERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_OBKERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          OBKERRIE        LL_FLASH_DisableIT_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_OBKERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_OBKERRIE);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_OBKERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          OBKERRIE        LL_FLASH_NS_DisableIT_OBKERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_OBKERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_OBKERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          OBKERRIE        LL_FLASH_IsEnabledIT_OBKERR
  * @param  flashx FLASH instance.
  * @retval State of flash OBKERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_OBKERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_OBKERRIE) == (FLASH_CR_OBKERRIE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_OBKERRIE) == (FLASH_CR_OBKERRIE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash error interrupt is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR          OBKERRIE        LL_FLASH_NS_IsEnabledIT_OBKERR
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure OBKERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_OBKERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_OBKERRIE) == (FLASH_CR_OBKERRIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          OBKWERRIE        LL_FLASH_EnableIT_OBKWERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_OBKWERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SCR, FLASH_CR_OBKWERRIE);
#else
  STM32_SET_BIT(flashx->CR, FLASH_CR_OBKWERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          OBKWERRIE        LL_FLASH_NS_EnableIT_OBKWERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_OBKWERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_OBKWERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          OBKWERRIE        LL_FLASH_DisableIT_OBKWERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_OBKWERR(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->SCR, FLASH_CR_OBKWERRIE);
#else
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_OBKWERRIE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Disable the flash error interrupt for the Non-Secure flash memory.
  * @rmtoll
  *  CR          OBKWERRIE        LL_FLASH_NS_DisableIT_OBKWERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_OBKWERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_OBKWERRIE);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          OBKWERRIE        LL_FLASH_IsEnabledIT_OBKWERR
  * @param  flashx FLASH instance.
  * @retval State of flash OBKWERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_OBKWERR(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SCR, FLASH_CR_OBKWERRIE) == (FLASH_CR_OBKWERRIE)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_OBKWERRIE) == (FLASH_CR_OBKWERRIE)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Check if the flash error interrupt is enabled or disabled for the Non-Secure flash memory.
  * @rmtoll
  *  CR          OBKWERRIE        LL_FLASH_NS_IsEnabledIT_OBKWERR
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure OBKWERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_OBKWERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_OBKWERRIE) == (FLASH_CR_OBKWERRIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          OPTCHANGEERRIE        LL_FLASH_NS_EnableIT_OPTCHANGEERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnableIT_OPTCHANGEERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_OPTCHANGEERRIE);
}

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          OPTCHANGEERRIE        LL_FLASH_NS_DisableIT_OPTCHANGEERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisableIT_OPTCHANGEERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_OPTCHANGEERRIE);
}

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          OPTCHANGEERRIE        LL_FLASH_NS_IsEnabledIT_OPTCHANGEERR
  * @param  flashx FLASH instance.
  * @retval State of flash OPTCHANGEERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledIT_OPTCHANGEERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_OPTCHANGEERRIE) == (FLASH_CR_OPTCHANGEERRIE)) ? 1UL : 0UL);
}
#else
/**
  * @brief  Enable the flash error interrupt.
  * @rmtoll
  *  CR/SCR          OPTCHANGEERRIE        LL_FLASH_EnableIT_OPTCHANGEERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_OPTCHANGEERR(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->CR, FLASH_CR_OPTCHANGEERRIE);
}

/**
  * @brief  Disable the flash error interrupt.
  * @rmtoll
  *  CR          OPTCHANGEERRIE        LL_FLASH_DisableIT_OPTCHANGEERR
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_OPTCHANGEERR(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->CR, FLASH_CR_OPTCHANGEERRIE);
}

/**
  * @brief  Check if the flash error interrupt is enabled or disabled.
  * @rmtoll
  *  CR/SCR          OPTCHANGEERRIE        LL_FLASH_IsEnabledIT_OPTCHANGEERR
  * @param  flashx FLASH instance.
  * @retval State of flash OPTCHANGEERR interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_OPTCHANGEERR(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->CR, FLASH_CR_OPTCHANGEERRIE) == (FLASH_CR_OPTCHANGEERRIE)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Set the privilege attribute.
  * @rmtoll
  *  PRIVCFGR     PRIV        LL_FLASH_SetPrivAttr
  * @param  flashx    FLASH instance.
  * @param  item      The item attribute to be configured.
  *                   This parameter can be one of the following values:
  *                   @arg @ref LL_FLASH_PRIV_ITEM_ALL
  * @param  priv_attr This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_ATTR_NPRIV
  *         @arg @ref LL_FLASH_ATTR_PRIV
  * @note  This register can be written only when the access is privileged.
  */
__STATIC_INLINE void LL_FLASH_SetPrivAttr(FLASH_TypeDef *flashx, uint32_t item, uint32_t priv_attr)
{
  STM32_MODIFY_REG(flashx->PRIVCFGR, item, (item * priv_attr));
}

/**
  * @brief  Get the privilege attribute.
  * @rmtoll
  *  PRIVCFGR     PRIV        LL_FLASH_GetPrivAttr
  * @param  flashx FLASH instance.
  * @param  item   The item attribute to be queried.
  *                This parameter can be one of the following values:
  *                @arg @ref LL_FLASH_PRIV_ITEM_ALL
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_ATTR_NPRIV
  *         @arg @ref LL_FLASH_ATTR_PRIV
  */
__STATIC_INLINE uint32_t LL_FLASH_GetPrivAttr(const FLASH_TypeDef *flashx, uint32_t item)
{
  return ((STM32_READ_BIT(flashx->PRIVCFGR, item) == item) ? LL_FLASH_ATTR_PRIV : LL_FLASH_ATTR_NPRIV);
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the secure attribute.
  * @rmtoll
  *  ACR           ACR_SEC_EN   LL_FLASH_SetSecAttr
  * @param  flashx    FLASH instance.
  * @param  item      The item attribute to be configured.
  *                   This parameter can be one of the following values:
  *                   @arg @ref LL_FLASH_SEC_ITEM_ALL
  * @param  sec_attr  This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_ATTR_NSEC
  *         @arg @ref LL_FLASH_ATTR_SEC
  * @note  This register can be written only when the access is privileged.
  */
__STATIC_INLINE void LL_FLASH_SetSecAttr(FLASH_TypeDef *flashx, uint32_t item, uint32_t sec_attr)
{
  STM32_MODIFY_REG(flashx->ACR, item, (item * sec_attr));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the secure attribute.
  * @rmtoll
  *  ACR           ACR_SEC_EN   LL_FLASH_GetSecAttr
  * @param  flashx FLASH instance.
  * @param  item   The item attribute to be queried.
  *                This parameter can be one of the following values:
  *                @arg @ref LL_FLASH_SEC_ITEM_ALL
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_ATTR_NSEC
  *         @arg @ref LL_FLASH_ATTR_SEC
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSecAttr(const FLASH_TypeDef *flashx, uint32_t item)
{
  return ((STM32_READ_BIT(flashx->ACR, item) == item) ? LL_FLASH_ATTR_SEC : LL_FLASH_ATTR_NSEC);
}


#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the flash security state inversion.
  * @rmtoll
  *  SCR           INV           LL_FLASH_SetSecurityStateInversion
  * @param  flashx FLASH instance.
  * @param  sec_state_inversion
  *         This parameter can be one of the following values :
  *         @arg @ref LL_FLASH_SEC_NOT_INVERTED
  *         @arg @ref LL_FLASH_SEC_INVERTED
  */
__STATIC_INLINE void LL_FLASH_SetSecurityStateInversion(FLASH_TypeDef *flashx, uint32_t sec_state_inversion)
{
  STM32_MODIFY_REG(flashx->SCR, FLASH_SCR_INV, sec_state_inversion);
}

/**
  * @brief  Get the flash security state inversion.
  * @rmtoll
  *  SCR           INV           LL_FLASH_GetSecurityStateInversion
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_SEC_NOT_INVERTED
  *         @arg @ref LL_FLASH_SEC_INVERTED
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSecurityStateInversion(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->SCR, FLASH_SCR_INV));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash privileged protection for the secure registers.
  * @rmtoll
  *  PRIVCFGR          SPRIV          LL_FLASH_EnablePrivilege
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnablePrivilege(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_SPRIV);
#else
  STM32_SET_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_PRIV);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Disable the flash privileged protection for the secure registers.
  * @rmtoll
  *  PRIVCFGR          SPRIV          LL_FLASH_DisablePrivilege
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisablePrivilege(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_CLEAR_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_SPRIV);
#else
  STM32_CLEAR_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_PRIV);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Check if the flash privileged protection for the secure registers is enabled or disabled.
  * @rmtoll
  *  PRIVCFGR          SPRIV          LL_FLASH_IsEnabledPrivilege
  * @param  flashx FLASH instance.
  * @retval State of flash secure privilege (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPrivilege(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_SPRIV) == (FLASH_PRIVCFGR_SPRIV)) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_PRIV) == (FLASH_PRIVCFGR_PRIV)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Enable the flash privileged protection for the Non-Secure registers.
  * @rmtoll
  *  PRIVCFGR          PRIV          LL_FLASH_NS_EnablePrivilege
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_EnablePrivilege(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_PRIV);
}

/**
  * @brief  Disable the flash privileged protection for the Non-Secure registers.
  * @rmtoll
  *  PRIVCFGR          PRIV          LL_FLASH_NS_DisablePrivilege
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_DisablePrivilege(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_PRIV);
}

/**
  * @brief  Check if the flash privileged protection for the Non-Secure registers is enabled or disabled.
  * @rmtoll
  *  PRIVCFGR          PRIV          LL_FLASH_NS_IsEnabledPrivilege
  * @param  flashx FLASH instance.
  * @retval State of flash Non-Secure privilege (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_IsEnabledPrivilege(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->PRIVCFGR, FLASH_PRIVCFGR_PRIV) == (FLASH_PRIVCFGR_PRIV)) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Lock the flash OBKCFGR register.
  * @rmtoll
  *  OBKCFGR           LOCK           LL_FLASH_OBK_Lock
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OBK_Lock(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SOBKCFGR, FLASH_OBKCFGR_LOCK);
#else
  STM32_SET_BIT(flashx->OBKCFGR, FLASH_OBKCFGR_LOCK);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Check the flash OBK control access registers lock state.
  * @rmtoll
  *  OBKCFGR           LOCK           LL_FLASH_OBK_IsLocked
  * @param  flashx FLASH instance.
  * @retval State of flash OBK lock (1 locked / 0 unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OBK_IsLocked(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return (((STM32_READ_BIT(flashx->SOBKCFGR, FLASH_OBKCFGR_LOCK)) == (FLASH_OBKCFGR_LOCK)) ? 1UL : 0UL);
#else
  return (((STM32_READ_BIT(flashx->OBKCFGR, FLASH_OBKCFGR_LOCK)) == (FLASH_OBKCFGR_LOCK)) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Set the flash swap page request bit.
  * @rmtoll
  *  SOBKCFGR/OBKCFGR      SWAP_SECT_REQ           LL_FLASH_OBK_EnableSwapPage
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OBK_EnableSwapPage(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SOBKCFGR, FLASH_OBKCFGR_SWAP_SECT_REQ);
#else
  STM32_SET_BIT(flashx->OBKCFGR, FLASH_OBKCFGR_SWAP_SECT_REQ);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Get the flash swap page request bit.
  * @rmtoll
  *  SOBKCFGR/OBKCFGR           SWAP_SECT_REQ           LL_FLASH_OBK_IsEnabledSwapPage
  * @param  flashx FLASH instance.
  * @retval State of flash swap page request (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OBK_IsEnabledSwapPage(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SOBKCFGR, FLASH_OBKCFGR_SWAP_SECT_REQ) == (FLASH_OBKCFGR_SWAP_SECT_REQ)) ? 0UL : 1UL);
#else
  return ((STM32_READ_BIT(flashx->OBKCFGR, FLASH_OBKCFGR_SWAP_SECT_REQ) == (FLASH_OBKCFGR_SWAP_SECT_REQ)) ? 0UL : 1UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Set the flash alternate.
  * @rmtoll
  *  SOBKCFGR/OBKCFGR      ALT_SEC           LL_FLASH_OBK_SetAlternatePage
  * @param  flashx FLASH instance.
  * @param  alternate_page
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OBK_PAGE_ALTERNATE
  *         @arg @ref LL_FLASH_OBK_PAGE_CURRENT
  */
__STATIC_INLINE void LL_FLASH_OBK_SetAlternatePage(FLASH_TypeDef *flashx, uint32_t alternate_page)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SOBKCFGR, FLASH_OBKCFGR_ALT_SECT, alternate_page);
#else
  STM32_MODIFY_REG(flashx->OBKCFGR, FLASH_OBKCFGR_ALT_SECT, alternate_page);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Get the flash alternate.
  * @rmtoll
  *  SOBKCFGR/OBKCFGR           ALT_SEC           LL_FLASH_OBK_GetAlternatePage
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OBK_PAGE_ALTERNATE
  *         @arg @ref LL_FLASH_OBK_PAGE_CURRENT
  */
__STATIC_INLINE uint32_t LL_FLASH_OBK_GetAlternatePage(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return (STM32_READ_BIT(flashx->SOBKCFGR, FLASH_OBKCFGR_ALT_SECT));
#else
  return (STM32_READ_BIT(flashx->OBKCFGR, FLASH_OBKCFGR_ALT_SECT));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Erase the flash OBK alternate page.
  * @rmtoll
  *  SOBKCFGR/OBKCFGR      ALT_SECT_ERASE           LL_FLASH_OBK_EraseAlternatePage
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OBK_EraseAlternatePage(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_SET_BIT(flashx->SOBKCFGR, FLASH_OBKCFGR_ALT_SECT_ERASE);
#else
  STM32_SET_BIT(flashx->OBKCFGR, FLASH_OBKCFGR_ALT_SECT_ERASE);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Set the flash OBK swap offset.
  * @rmtoll
  *  OBKCFGR/SOBKCFGR           SWAP_OFFSET           LL_FLASH_OBK_SetSwapOffset
  * @param  flashx FLASH instance.
  * @param  offset
  */
__STATIC_INLINE void LL_FLASH_OBK_SetSwapOffset(FLASH_TypeDef *flashx, uint32_t offset)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SOBKCFGR, FLASH_OBKCFGR_SWAP_OFFSET, (offset << FLASH_OBKCFGR_SWAP_OFFSET_Pos));
#else
  STM32_MODIFY_REG(flashx->OBKCFGR, FLASH_OBKCFGR_SWAP_OFFSET, (offset << FLASH_OBKCFGR_SWAP_OFFSET_Pos));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Get the flash OBK swap offset.
  * @rmtoll
  *  OBKCFGR/SOBKCFGR           SWAP_OFFSET           LL_FLASH_OBK_GetSwapOffset
  * @param  flashx FLASH instance.
  * @retval Returned value : the flash OBK swap offset.
  */
__STATIC_INLINE uint32_t LL_FLASH_OBK_GetSwapOffset(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return (STM32_READ_BIT(flashx->SOBKCFGR, FLASH_OBKCFGR_SWAP_OFFSET) >> FLASH_OBKCFGR_SWAP_OFFSET_Pos);
#else
  return (STM32_READ_BIT(flashx->OBKCFGR, FLASH_OBKCFGR_SWAP_OFFSET) >> FLASH_OBKCFGR_SWAP_OFFSET_Pos);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

/**
  * @brief  Set the flash end page for extended hide protection area by bank.
  * @rmtoll
  *  HDPEXTR       HDP1_EXT/HDP2_EXT          LL_FLASH_SetHDPExtArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_HDPEXT_BANK_1
  *         @arg @ref LL_FLASH_HDPEXT_BANK_2
  * @param  page_nbr
  *         This parameter can be a value between 0x00U and the maximum number of pages by bank.
  */
__STATIC_INLINE void LL_FLASH_SetHDPExtArea(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_nbr)
{
  STM32_MODIFY_REG(flashx->HDPEXTR, FLASH_HDPEXTR_HDP1_EXT << bank, page_nbr << bank);
}

/**
  * @brief  Get the flash end page for extended hide protection area by bank.
  * @rmtoll
  *  HDPEXTR       HDP1_EXT/HDP2_EXT          LL_FLASH_GetHDPExtArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_HDPEXT_BANK_1
  *         @arg @ref LL_FLASH_HDPEXT_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of pages by bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetHDPExtArea(const FLASH_TypeDef *flashx, uint32_t bank)
{
  return (STM32_READ_BIT(flashx->HDPEXTR, FLASH_HDPEXTR_HDP1_EXT << bank) >> bank);
}

/**
  * @brief  Set the flash independent watchdog selection.
  * @rmtoll
  *  OPTSR           IWDG_SW           LL_FLASH_OB_SetIWDGSelection
  * @param  flashx FLASH instance.
  * @param  hw_sw_selection
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_IWDG_HW
  *         @arg @ref LL_FLASH_OB_IWDG_SW
  */
__STATIC_INLINE void LL_FLASH_OB_SetIWDGSelection(FLASH_TypeDef *flashx, uint32_t hw_sw_selection)
{
  STM32_MODIFY_REG(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_IWDG_SW, hw_sw_selection);
}

/**
  * @brief  Get the flash independent watchdog selection.
  * @rmtoll
  *  OPTSR           IWDG_SW           LL_FLASH_OB_GetIWDGSelection
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_IWDG_HW
  *         @arg @ref LL_FLASH_OB_IWDG_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetIWDGSelection(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_IWDG_SW));
}

/**
  * @brief  Set the flash window watchdog selection.
  * @rmtoll
  *  OPTSR           WWDG_SW           LL_FLASH_OB_SetWWDGSelection
  * @param  flashx FLASH instance.
  * @param  hw_sw_selection
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_WWDG_HW
  *         @arg @ref LL_FLASH_OB_WWDG_SW
  */
__STATIC_INLINE void LL_FLASH_OB_SetWWDGSelection(FLASH_TypeDef *flashx, uint32_t hw_sw_selection)
{
  STM32_MODIFY_REG(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_WWDG_SW, hw_sw_selection);
}

/**
  * @brief  Get the flash window watchdog selection.
  * @rmtoll
  *  OPTSR           WWDG_SW           LL_FLASH_OB_GetWWDGSelection
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_WWDG_HW
  *         @arg @ref LL_FLASH_OB_WWDG_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetWWDGSelection(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_WWDG_SW));
}

/**
  * @brief  Set the flash reset generation in stop mode.
  * @rmtoll
  *  OPTSR           NRST_STOP           LL_FLASH_OB_SetNRSTStopMode
  * @param  flashx FLASH instance.
  * @param  rst_generation
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STOP_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STOP_MODE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNRSTStopMode(FLASH_TypeDef *flashx, uint32_t rst_generation)
{
  STM32_MODIFY_REG(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_NRST_STOP, rst_generation);
}

/**
  * @brief  Get the flash reset generation in stop mode.
  * @rmtoll
  *  OPTSR           NRST_STOP           LL_FLASH_OB_GetNRSTStopMode
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STOP_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STOP_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNRSTStopMode(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_NRST_STOP));
}

/**
  * @brief  Set the flash reset generation in standby mode.
  * @rmtoll
  *  OPTSR           NRST_STDBY           LL_FLASH_OB_SetNRSTStandbyMode
  * @param  flashx FLASH instance.
  * @param  rst_generation
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STDBY_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STDBY_MODE
  */
__STATIC_INLINE void LL_FLASH_OB_SetNRSTStandbyMode(FLASH_TypeDef *flashx, uint32_t rst_generation)
{
  STM32_MODIFY_REG(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_NRST_STDBY, rst_generation);
}

/**
  * @brief  Get the flash reset generation in standby mode.
  * @rmtoll
  *  OPTSR           NRST_STDBY           LL_FLASH_OB_GetNRSTStandbyMode
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_RST_STDBY_MODE
  *         @arg @ref LL_FLASH_OB_NO_RST_STDBY_MODE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetNRSTStandbyMode(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_NRST_STDBY));
}

/**
  * @brief Set the flash Readout protection level.
  * @rmtoll
  *  OPTR           ProductState           LL_FLASH_OB_SetProductState
  * @param  flashx FLASH instance.
  * @param  product_state
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_OPEN
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_PROVISIONING
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_IROT_PROVISIONED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_TZ_CLOSED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_CLOSED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_LOCKED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_REGRESSION
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_NS_REGRESSION
  */
__STATIC_INLINE void LL_FLASH_OB_SetProductState(FLASH_TypeDef *flashx, uint32_t product_state)
{
  STM32_MODIFY_REG(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_PRODUCT_STATE, product_state);
}

/**
  * @brief  Get the flash Readout protection level.
  * @rmtoll
  *  OPTSR_PGR           ProductState           LL_FLASH_OB_GetProductState
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_OPEN
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_PROVISIONING
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_IROT_PROVISIONED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_TZ_CLOSED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_CLOSED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_LOCKED
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_REGRESSION
  *         @arg @ref LL_FLASH_OB_PRODUCT_STATE_NS_REGRESSION
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetProductState(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_PRODUCT_STATE));
}

/**
  * @brief  Freeze the flash independent watchdog counter in stop mode.
  * @rmtoll
  *  OPTSR           IWDG_STOP           LL_FLASH_OB_FreezeIWDGStopMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_FreezeIWDGStopMode(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_IWDG_STOP);
}

/**
  * @brief  Unfreeze the flash independent watchdog counter in stop mode.
  * @rmtoll
  *  OPTSR           IWDG_STOP           LL_FLASH_OB_UnfreezeIWDGStopMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnfreezeIWDGStopMode(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_IWDG_STOP);
}

/**
  * @brief  Check the flash independent watchdog counter in stop mode is frozen.
  * @rmtoll
  *  OPTSR           IWDG_STOP           LL_FLASH_OB_IsFrozenIWDGStopMode
  * @param  flashx FLASH instance.
  * @retval State of flash option-bytes IWDG counter in stop mode (1 frozen / 0 not frozen).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsFrozenIWDGStopMode(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_IWDG_STOP) == (FLASH_OPTSR_CUR_IWDG_STOP)) ? 0UL : 1UL);
}

/**
  * @brief  Freeze the flash independent watchdog counter in standby mode.
  * @rmtoll
  *  OPTSR           IWDG_STDBY           LL_FLASH_OB_FreezeIWDGStandbyMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_FreezeIWDGStandbyMode(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_IWDG_STDBY);
}

/**
  * @brief  Unfreeze the flash independent watchdog counter in standby mode.
  * @rmtoll
  *  OPTSR           IWDG_STDBY           LL_FLASH_OB_UnfreezeIWDGStandbyMode
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnfreezeIWDGStandbyMode(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_IWDG_STDBY);
}

/**
  * @brief  Check the flash independent watchdog counter in standby mode is frozen.
  * @rmtoll
  *  OPTSR           IWDG_STDBY           LL_FLASH_OB_IsFrozenIWDGStandbyMode
  * @param  flashx FLASH instance.
  * @retval State of flash option-bytes IWDG counter in standby mode (1 frozen / 0 not frozen).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsFrozenIWDGStandbyMode(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_IWDG_STDBY) == (FLASH_OPTSR_CUR_IWDG_STDBY)) \
          ? 0UL : 1UL);
}

/**
  * @brief  Set the flash window watchdog selection.
  * @rmtoll
  *  OPTSR           BOOT_UBE           LL_FLASH_OB_SetBootUbe
  * @param  flashx FLASH instance.
  * @param  boot_ube
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT_UBE_ST
  *         @arg @ref LL_FLASH_OB_BOOT_UBE_OEM
  */
__STATIC_INLINE void LL_FLASH_OB_SetBootUbe(FLASH_TypeDef *flashx, uint32_t boot_ube)
{
  STM32_MODIFY_REG(flashx->OPTSR_PRG, FLASH_OPTSR_CUR_BOOT_UBE, boot_ube);
}

/**
  * @brief  Get the flash window watchdog selection.
  * @rmtoll
  *  OPTSR           BOOT_UBE           LL_FLASH_OB_GetBootUbe
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BOOT_UBE_ST
  *         @arg @ref LL_FLASH_OB_BOOT_UBE_OEM
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetBootUbe(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR_CUR, FLASH_OPTSR_CUR_BOOT_UBE));
}

/**
  * @brief  Get the flash EPOCH counter.
  * @rmtoll
  *  SEPOCH/EPOCH        EPOCH           LL_FLASH_OB_GetEPOCHCounterValue
  * @param  flashx FLASH instance.
  * @retval Return EPOCH value
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetEPOCHCounterValue(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return (STM32_READ_BIT(flashx->SEPOCHR_CUR, FLASH_EPOCHR_CUR_EPOCH));
#else
  return (STM32_READ_BIT(flashx->EPOCHR_CUR, FLASH_EPOCHR_CUR_EPOCH));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Get the flash Non-Secure EPOCH counter.
  * @rmtoll
  *  EPOCH        EPOCH           LL_FLASH_NS_OB_GetEPOCHCounterValue
  * @param  flashx FLASH instance.
  * @retval Return EPOCH value
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_OB_GetEPOCHCounterValue(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->EPOCHR_CUR, FLASH_EPOCHR_CUR_EPOCH));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Set the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2_PRG           SRAM1_RST           LL_FLASH_OB_SetSystemResetSRAM1Erase
  * @param  flashx FLASH instance.
  * @param  erase_sram
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM1_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM1_SYS_RST
  */
__STATIC_INLINE void LL_FLASH_OB_SetSystemResetSRAM1Erase(FLASH_TypeDef *flashx, uint32_t erase_sram)
{
  STM32_MODIFY_REG(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM1_RST, erase_sram);
}

/**
  * @brief  Get the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2_CUR           SRAM1_RST           LL_FLASH_OB_GetSystemResetSRAM1Erase
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM1_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM1_SYS_RST
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSystemResetSRAM1Erase(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR2_CUR, FLASH_OPTSR2_CUR_SRAM1_RST));
}

/**
  * @brief  Set the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2_PRG           SRAM2_RST           LL_FLASH_OB_SetSystemResetSRAM2Erase
  * @param  flashx FLASH instance.
  * @param  erase_sram
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM2_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST
  */
__STATIC_INLINE void LL_FLASH_OB_SetSystemResetSRAM2Erase(FLASH_TypeDef *flashx, uint32_t erase_sram)
{
  STM32_MODIFY_REG(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM2_RST, erase_sram);
}

/**
  * @brief  Get the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2_CUR           SRAM2_RST           LL_FLASH_OB_GetSystemResetSRAM2Erase
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM2_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM2_SYS_RST
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSystemResetSRAM2Erase(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR2_CUR, FLASH_OPTSR2_CUR_SRAM2_RST));
}

#if defined(SRAM3_BASE)
/**
  * @brief  Set the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2_PRG           SRAM3_RST           LL_FLASH_OB_SetSystemResetSRAM3Erase
  * @param  flashx FLASH instance.
  * @param  erase_sram
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM3_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM3_SYS_RST
  */
__STATIC_INLINE void LL_FLASH_OB_SetSystemResetSRAM3Erase(FLASH_TypeDef *flashx, uint32_t erase_sram)
{
  STM32_MODIFY_REG(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM3_RST, erase_sram);
}

/**
  * @brief  Get the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2_CUR           SRAM3_RST           LL_FLASH_OB_GetSystemResetSRAM3Erase
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_ERASED_SRAM3_SYS_RST
  *         @arg @ref LL_FLASH_OB_NOT_ERASED_SRAM3_SYS_RST
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSystemResetSRAM3Erase(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR2_CUR, FLASH_OPTSR2_CUR_SRAM3_RST));
}

/**
  * @brief  Enable the flash backup ram ECC.
  * @rmtoll
  *  OPTSR2           SRAM3_ECC           LL_FLASH_OB_EnableECCSRAM3
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableECCSRAM3(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM3_ECC);
}

/**
  * @brief  Disable the flash backup ram ECC.
  * @rmtoll
  *  OPTSR2           SRAM3_ECC           LL_FLASH_OB_DisableECCSRAM3
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableECCSRAM3(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM3_ECC);
}

/**
  * @brief  Check if flash backup rAM ECC is enabled or disabled.
  * @rmtoll
  *  OPTSR2           SRAM3_ECC           LL_FLASH_OB_IsEnabledECCSRAM3
  * @param  flashx FLASH instance.
  * @retval State of flash option-bytes ECCSRAM3 (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledECCSRAM3(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTSR2_CUR, FLASH_OPTSR2_CUR_SRAM3_ECC) == (FLASH_OPTSR2_CUR_SRAM3_ECC)) ? 0UL : 1UL);
}
#endif /* SRAM3_BASE */

/**
  * @brief  Enable the flash sram2 ECC.
  * @rmtoll
  *  OPTSR2           SRAM1_ECC           LL_FLASH_OB_EnableECCSRAM1
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableECCSRAM1(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM1_ECC);
}

/**
  * @brief  Disable the flash sram2 ECC.
  * @rmtoll
  *  OPTSR2           SRAM1_ECC           LL_FLASH_OB_DisableECCSRAM1
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableECCSRAM1(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM1_ECC);
}

/**
  * @brief  Check if the flash sram2 ECC is enabled or disabled.
  * @rmtoll
  *  OPTSR2           SRAM1_ECC           LL_FLASH_OB_IsEnabledECCSRAM1
  * @param  flashx FLASH instance.
  * @retval State of flash option-bytes SRAM1_ECC (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledECCSRAM1(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTSR2_CUR, FLASH_OPTSR2_CUR_SRAM1_ECC) == (FLASH_OPTSR2_CUR_SRAM1_ECC)) ? 0UL : 1UL);
}

/**
  * @brief  Enable the flash sram2 ECC.
  * @rmtoll
  *  OPTSR2           SRAM2_ECC           LL_FLASH_OB_EnableECCSRAM2
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableECCSRAM2(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM2_ECC);
}

/**
  * @brief  Disable the flash sram2 ECC.
  * @rmtoll
  *  OPTSR2           SRAM2_ECC           LL_FLASH_OB_DisableECCSRAM2
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableECCSRAM2(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_SRAM2_ECC);
}

/**
  * @brief  Check if the flash sram2 ECC is enabled or disabled.
  * @rmtoll
  *  OPTSR2           SRAM2_ECC           LL_FLASH_OB_IsEnabledECCSRAM2
  * @param  flashx FLASH instance.
  * @retval State of flash option-bytes ECCSRAM2 (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledECCSRAM2(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->OPTSR2_CUR, FLASH_OPTSR2_CUR_SRAM2_ECC) == (FLASH_OPTSR2_CUR_SRAM2_ECC)) ? 0UL : 1UL);
}

/**
  * @brief  Set the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2           TZEN           LL_FLASH_OB_EnableTrustZone
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_EnableTrustZone(FLASH_TypeDef *flashx)
{
  STM32_MODIFY_REG(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_TZEN, LL_FLASH_OB_TZEN_ENABLE);
}

/**
  * @brief  Set the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2           TZEN           LL_FLASH_OB_DisableTrustZone
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_DisableTrustZone(FLASH_TypeDef *flashx)
{
  STM32_MODIFY_REG(flashx->OPTSR2_PRG, FLASH_OPTSR2_CUR_TZEN, LL_FLASH_OB_TZEN_DISABLE);
}

/**
  * @brief  Get the flash erase sram upon system reset.
  * @rmtoll
  *  OPTSR2           TZEN           LL_FLASH_OB_IsEnabledTrustZone
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_TZEN_ENABLE
  *         @arg @ref LL_FLASH_OB_TZEN_DISABLE
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledTrustZone(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR2_CUR, FLASH_OPTSR2_CUR_TZEN));
}

/**
  * @brief  Set the flash swap banks.
  * @rmtoll
  *  OPTSR3           SWAP_BANK           LL_FLASH_OB_SetSwapBank
  * @param  flashx FLASH instance.
  * @param  swap_bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_NOT_SWAPPED
  *         @arg @ref LL_FLASH_OB_BANK_SWAPPED
  */
__STATIC_INLINE void LL_FLASH_OB_SetSwapBank(FLASH_TypeDef *flashx, uint32_t swap_bank)
{
  STM32_MODIFY_REG(flashx->OPTSR3_PRG, FLASH_OPTSR3_CUR_SWAP_BANK, swap_bank);
}

/**
  * @brief  Get the flash swap banks.
  * @rmtoll
  *  OPTSR3          SWAP_BANK        LL_FLASH_OB_GetSwapBank
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_NOT_SWAPPED
  *         @arg @ref LL_FLASH_OB_BANK_SWAPPED
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetSwapBank(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR3_CUR, FLASH_OPTSR3_CUR_SWAP_BANK));
}

/**
  * @brief  Set the flash lock swap.
  * @rmtoll
  *  OPTSR3           SWAP_LOCK           LL_FLASH_OB_SetLockSwap
  * @param  flashx FLASH instance.
  * @param  lock_bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_SWAP_UNLOCKED
  *         @arg @ref LL_FLASH_OB_BANK_SWAP_LOCKED
  */
__STATIC_INLINE void LL_FLASH_OB_SetLockSwap(FLASH_TypeDef *flashx, uint32_t lock_bank)
{
  STM32_MODIFY_REG(flashx->OPTSR3_PRG, FLASH_OPTSR3_CUR_SWAP_LOCKOUT, lock_bank);
}

/**
  * @brief  Get the flash lock swap.
  * @rmtoll
  *  OPTSR3          SWAP_LOCK        LL_FLASH_OB_GetLockSwap
  * @param  flashx FLASH instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_OB_BANK_SWAP_UNLOCKED
  *         @arg @ref LL_FLASH_OB_BANK_SWAP_LOCKED
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetLockSwap(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->OPTSR3_CUR, FLASH_OPTSR3_CUR_SWAP_LOCKOUT));
}

/**
  * @brief  Set the flash boot base Address.
  * @rmtoll
  *  SBOOTR_PRG/BOOTR_PRG          BOOTADD          LL_FLASH_OB_SetBootAddr
  * @param  flashx FLASH instance.
  * @param  boot_Addr
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_OB_SetBootAddr(FLASH_TypeDef *flashx, uint32_t boot_Addr)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SBOOTR_PRG, FLASH_BOOTR_CUR_BOOTADD, boot_Addr);
#else
  STM32_MODIFY_REG(flashx->BOOTR_PRG, FLASH_BOOTR_CUR_BOOTADD, boot_Addr);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the flash boot base Address.
  * @rmtoll
  *  BOOTR_PRG          BOOTADD          LL_FLASH_NS_OB_SetBootAddr
  * @param  flashx FLASH instance.
  * @param  boot_Addr
  *         This parameter can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE void LL_FLASH_NS_OB_SetBootAddr(FLASH_TypeDef *flashx, uint32_t boot_Addr)
{
  STM32_MODIFY_REG(flashx->BOOTR_PRG, FLASH_BOOTR_CUR_BOOTADD, boot_Addr);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the flash boot base Address.
  * @rmtoll
  *  SBOOTR_CUR/BOOT_CUR          BOOTADD          LL_FLASH_OB_GetBootAddr
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetBootAddr(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return (STM32_READ_BIT(flashx->SBOOTR_CUR, FLASH_BOOTR_CUR_BOOTADD));
#else
  return (STM32_READ_BIT(flashx->BOOTR_CUR, FLASH_BOOTR_CUR_BOOTADD));
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Get the flash boot base Address.
  * @rmtoll
  *  BOOTR_CUR          BOOTADD          LL_FLASH_NS_OB_GetBootAddr
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00000000U and 0xFFFFFFFFU.
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_OB_GetBootAddr(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->BOOTR_CUR, FLASH_BOOTR_CUR_BOOTADD));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Lock the flash boot configuration.
  * @rmtoll
  *  SBOOTR_PRG/BOOTR_PRG          BOOT_LOCK          LL_FLASH_OB_LockBootConfig
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_LockBootConfig(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SBOOTR_PRG, FLASH_BOOTR_CUR_BOOT_LOCK, LL_FLASH_OB_BOOT_LOCKED);
#else
  STM32_MODIFY_REG(flashx->BOOTR_PRG, FLASH_BOOTR_CUR_BOOT_LOCK, LL_FLASH_OB_BOOT_LOCKED);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Lock the flash boot configuration.
  * @rmtoll
  *  BOOTR_PRG          BOOT_LOCK          LL_FLASH_NS_OB_LockBootConfig
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_OB_LockBootConfig(FLASH_TypeDef *flashx)
{
  STM32_MODIFY_REG(flashx->BOOTR_PRG, FLASH_BOOTR_CUR_BOOT_LOCK, LL_FLASH_OB_BOOT_LOCKED);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Unlock the flash boot configuration.
  * @rmtoll
  *  SBOOTR_PRG/BOOTR_PRG          BOOT_LOCK          LL_FLASH_OB_UnlockBootConfig
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_OB_UnlockBootConfig(FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  STM32_MODIFY_REG(flashx->SBOOTR_PRG, FLASH_BOOTR_CUR_BOOT_LOCK, LL_FLASH_OB_BOOT_NOT_LOCKED);
#else
  STM32_MODIFY_REG(flashx->BOOTR_PRG, FLASH_BOOTR_CUR_BOOT_LOCK, LL_FLASH_OB_BOOT_NOT_LOCKED);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Unlock the flash boot configuration.
  * @rmtoll
  *  BOOTR_PRG          BOOT_LOCK          LL_FLASH_NS_OB_UnlockBootConfig
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_NS_OB_UnlockBootConfig(FLASH_TypeDef *flashx)
{
  STM32_MODIFY_REG(flashx->BOOTR_PRG, FLASH_BOOTR_CUR_BOOT_LOCK, LL_FLASH_OB_BOOT_NOT_LOCKED);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the flash boot configuration lock state.
  * @rmtoll
  *  SBOOTR_CUR/BOOT_CUR          BOOT_LOCK          LL_FLASH_OB_IsLockedBootConfig
  * @param  flashx FLASH instance.
  * @retval State of boot address lock (1: locked, 0: unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLockedBootConfig(const FLASH_TypeDef *flashx)
{
#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
  return ((STM32_READ_BIT(flashx->SBOOTR_CUR, FLASH_BOOTR_CUR_BOOT_LOCK) == LL_FLASH_OB_BOOT_LOCKED) ? 1UL : 0UL);
#else
  return ((STM32_READ_BIT(flashx->BOOTR_CUR, FLASH_BOOTR_CUR_BOOT_LOCK) == LL_FLASH_OB_BOOT_LOCKED) ? 1UL : 0UL);
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Get the flash boot configuration lock state.
  * @rmtoll
  *  BOOTR_CUR          BOOT_LOCK          LL_FLASH_NS_OB_IsLockedBootConfig
  * @param  flashx FLASH instance.
  * @retval State of boot address lock (1: locked, 0: unlocked).
  */
__STATIC_INLINE uint32_t LL_FLASH_NS_OB_IsLockedBootConfig(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->BOOTR_CUR, FLASH_BOOTR_CUR_BOOT_LOCK) == LL_FLASH_OB_BOOT_LOCKED) ? 1UL : 0UL);
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Enable the flash OTP locking protection for the selected blocks.
  * @rmtoll
  *  OTPBLR_PRG          LOCKBL          LL_FLASH_OB_LockOTPBlock
  * @param  flashx FLASH instance.
  * @param  block specifies the OTP blocks to be locked.
  *         This parameter can be any combination of @ref FLASH_OTP_Blocks possible values.
  */
__STATIC_INLINE void LL_FLASH_OB_LockOTPBlock(FLASH_TypeDef *flashx, uint32_t block)
{
  STM32_SET_BIT(flashx->OTPBLR_PRG, (FLASH_OTPBLR_PRG_LOCKBL & block));
}

/**
  * @brief  Get the flash OTP locking protection by block.
  * @rmtoll
  *  OTPBLR_CUR          LOCKBL          LL_FLASH_OB_IsLockedOTPBlock
  * @param  flashx FLASH instance.
  * @param  block specifies the OTP blocks to check.
  *         This parameter can be any combination of @ref FLASH_OTP_Blocks possible values.
  * @retval 1 if all blocks specified by blocks are locked, 0 otherwise.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsLockedOTPBlock(const FLASH_TypeDef *flashx, uint32_t block)
{
  const uint32_t masked_block = block & FLASH_OTPBLR_PRG_LOCKBL;
  return (((STM32_READ_BIT(flashx->OTPBLR_CUR, FLASH_OTPBLR_CUR_LOCKBL) & masked_block) == masked_block) ? 1UL : 0UL);
}

/**
  * @brief  Set the bootloader interface configuration.
  * @rmtoll
  *  BL_COM_CFGR         BL_COM_CFG          LL_FLASH_OB_SetBootloaderInterfaceConfig
  * @param  flashx FLASH instance.
  * @param  bootloader_config specifies the bootloader interface configuration to set.
  *         This parameter can be any value between 0x00000000 and 0xFFFFFFFF.
  */
__STATIC_INLINE void LL_FLASH_OB_SetBootloaderInterfaceConfig(FLASH_TypeDef *flashx, uint32_t bootloader_config)
{
  STM32_WRITE_REG(flashx->BL_COM_CFG_PRG, bootloader_config);
}

/**
  * @brief  Get the bootloader interface configuration.
  * @rmtoll
  *  BL_COM_CFGR         BL_COM_CFG          LL_FLASH_OB_GetBootloaderInterfaceConfig
  * @param  flashx FLASH instance.
  * @retval Returned value can be a value between 0x00000000 and 0xFFFFFFFF.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetBootloaderInterfaceConfig(const FLASH_TypeDef *flashx)
{
  return STM32_READ_BIT(flashx->BL_COM_CFG_CUR, FLASH_BL_COM_CFG_CUR_BL_COM_CFG);
}

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the flash security attribute for the bank page based.
  * @rmtoll
  *  SECBB1Rx/SECBB2Rx SEC1BBi/SEC2BBi  LL_FLASH_SetPageSecAttr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page_msk
  *         This parameter can be a combination of @ref FLASH_BB_Page_Selection values.
  * @param  sec_attr
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_ATTR_NSEC
  *         @arg @ref LL_FLASH_ATTR_SEC
  */
__STATIC_INLINE void LL_FLASH_SetPageSecAttr(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_msk,
                                             uint32_t sec_attr)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->SECBB1R : &flashx->SECBB2R;
  STM32_MODIFY_REG(*reg_addr, page_msk, (page_msk * sec_attr));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the flash security attribute for a bank page.
  * @rmtoll
  *  SECBB1Rx/SECBB2Rx   SEC1BBi/SEC2BBi   LL_FLASH_GetPageSecAttr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page_msk
  *         This parameter can be one value of @ref FLASH_BB_Page_Selection.
  * @retval State of bit (0 Non-Secure / 1 Secure).
  */
__STATIC_INLINE uint32_t LL_FLASH_GetPageSecAttr(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_msk)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->SECBB1R : &flashx->SECBB2R;
  return ((STM32_READ_BIT(*reg_addr, page_msk) == page_msk) ? 1UL : 0UL);
}

/**
  * @brief  Set the flash privilege attribute for the bank page based.
  * @rmtoll
  *  PRIVBB1Rx/PRIVBB2Rx   PRIV1BBi/PRIV2BBi   LL_FLASH_SetPagePrivAttr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page_msk
  *         This parameter can be a combination of @ref FLASH_BB_Page_Selection values.
  * @param  priv_attr
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_ATTR_NPRIV
  *         @arg @ref LL_FLASH_ATTR_PRIV
  */
__STATIC_INLINE void LL_FLASH_SetPagePrivAttr(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_msk,
                                              uint32_t priv_attr)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->PRIVBB1R : &flashx->PRIVBB2R;
  STM32_MODIFY_REG(*reg_addr, page_msk, (page_msk * priv_attr));
}

/**
  * @brief  Get the flash privilege attribute for a bank page.
  * @rmtoll
  *  PRIVBB1Rx/PRIVBB2Rx   PRIV1BBi/PRIV2BBi   LL_FLASH_GetPagePrivAttr
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page_msk
  *         This parameter can be one value of @ref FLASH_BB_Page_Selection.
  * @retval State of bit (0 Non-privileged / 1 Privileged).
  */
__STATIC_INLINE uint32_t LL_FLASH_GetPagePrivAttr(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page_msk)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->PRIVBB1R : &flashx->PRIVBB2R;
  return ((STM32_READ_BIT(*reg_addr, page_msk) == page_msk) ? 1UL : 0UL);
}

/**
  * @brief  Set the flash start page of the secure watermark area by bank.
  * @rmtoll
  *  SECWM1R/SECWM2R          SECWM1_STRT/SECWM2_STRT          LL_FLASH_OB_SetWMAreaStartPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_SetWMAreaStartPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t start_page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->SECWM1R_PRG : &flashx->SECWM2R_PRG;
  STM32_MODIFY_REG(*reg_addr, FLASH_SECWM1R_CUR_STRT, start_page);
}

/**
  * @brief  Get the flash start page of the secure watermark area by bank.
  * @rmtoll
  *  SECWM1R1/SECWM2R1          SECWM1_STRT/SECWM2_STRT          LL_FLASH_OB_GetWMAreaStartPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetWMAreaStartPage(FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->SECWM1R_CUR : &flashx->SECWM2R_CUR;
  return (STM32_READ_BIT(*reg_addr, FLASH_SECWM1R_CUR_STRT));
}

/**
  * @brief  Set the flash end page of the secure watermark area by bank.
  * @rmtoll
  *  SECWM1R1/SECWM2R1          SECWM1_END/SECWM2_END          LL_FLASH_OB_SetWMAreaEndPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  end_page This parameter can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_SetWMAreaEndPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t end_page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->SECWM1R_PRG : &flashx->SECWM2R_PRG;
  STM32_MODIFY_REG(*reg_addr, FLASH_SECWM1R_CUR_END, (end_page << FLASH_SECWM1R_CUR_END_Pos));
}

/**
  * @brief  Get the flash end page of the secure watermark area by bank.
  * @rmtoll
  *  SECWM1R1          SECWM1_END/SECWM2_END          LL_FLASH_OB_GetWMAreaEndPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetWMAreaEndPage(FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->SECWM1R_CUR : &flashx->SECWM2R_CUR;
  return (STM32_READ_BIT(*reg_addr, FLASH_SECWM1R_CUR_END) >> FLASH_SECWM1R_CUR_END_Pos);
}

/**
  * @brief  Configuration the flash secure watermark area by bank.
  * @rmtoll
  *  SECWM1R1/SECWM2R1   SECWM1_PSTRT/SECWM2_PSTRT/SECWM1_PEND/SECWM2_PEND   LL_FLASH_OB_ConfigSecureWMArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of page by bank.
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_ConfigSecureWMArea(FLASH_TypeDef *flashx, uint32_t bank, uint32_t start_page,
                                                    uint32_t end_page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->SECWM1R_PRG : &flashx->SECWM2R_PRG;
  STM32_MODIFY_REG(*reg_addr, (FLASH_SECWM1R_CUR_STRT | FLASH_SECWM1R_CUR_END),
                   (start_page | (end_page << FLASH_SECWM1R_CUR_END_Pos)));
}

/**
  * @brief  Set the flash start page of the write protection area A by bank.
  * @rmtoll
  *  WRP1AR/WRP2AR          WRP1_STRT/WRP2_STRT          LL_FLASH_OB_EnablePageWRP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page specifies the pages to be write protected.
  *         This parameter can be any combination of @ref LL_FLASH_OB_Write_Protection_Pages possible values.
  */
__STATIC_INLINE void LL_FLASH_OB_EnablePageWRP(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->WRP1R_PRG : &flashx->WRP2R_PRG;
  STM32_CLEAR_BIT(*reg_addr, (FLASH_WRP1R_CUR_WRPG1 & page));
}

/**
  * @brief  Disable the flash write protection on the selected pages of the selected bank.
  * @rmtoll
  *  WRP1R/WRP2R          WRP1R_WRPSG/WRP2R_WRPSG          LL_FLASH_OB_DisablePageWRP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page specifies the pages to be write protected.
  *         This parameter can be any combination of @ref LL_FLASH_OB_Write_Protection_Pages possible values.
  */
__STATIC_INLINE void LL_FLASH_OB_DisablePageWRP(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->WRP1R_PRG : &flashx->WRP2R_PRG;
  STM32_SET_BIT(*reg_addr, (FLASH_WRP1R_CUR_WRPG1 & page));
}

/**
  * @brief  Get the flash page write protection flags by bank.
  * @rmtoll
  *  WRP1R_PRG/WRP2R_PRG          WRP1R_WRPSG/WRP2R_WRPSG          LL_FLASH_OB_IsEnabledPageWRP
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  page specifies the pages to be write protected.
  *         This parameter can be any combination of @ref LL_FLASH_OB_Write_Protection_Pages possible values.
  * @retval 1 if all pages specified by the page parameter are write protected, 0 otherwise.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledPageWRP(FLASH_TypeDef *flashx, uint32_t bank, uint32_t page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->WRP1R_PRG : &flashx->WRP2R_PRG;
  return ((((~(STM32_READ_BIT(*reg_addr, FLASH_WRP1R_CUR_WRPG1))) & page) == page) ? 1UL : 0UL);
}

/**
  * @brief  Enable the data flash area.
  * @rmtoll
  *  OPTSR_PRG    EDATA_EN   LL_FLASH_OB_EnableEDATAArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_EnableEDATAArea(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->EDATA1R_PRG : &flashx->EDATA2R_PRG;
  STM32_SET_BIT(*reg_addr, FLASH_EDATA1R_CUR_EN);
}

/**
  * @brief  Disable the data flash area.
  * @rmtoll
  *  EDATAR_PRG   EDATA_EN   LL_FLASH_OB_DisableEDATAArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  */
__STATIC_INLINE void LL_FLASH_OB_DisableEDATAArea(FLASH_TypeDef *flashx, uint32_t bank)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->EDATA1R_PRG : &flashx->EDATA2R_PRG;
  STM32_CLEAR_BIT(*reg_addr, FLASH_EDATA1R_CUR_EN);
}

/**
  * @brief  Check if the data flash area is enabled or disabled.
  * @rmtoll
  *  EDATAR_CUR   EDATA_EN   LL_FLASH_OB_IsEnabledEDATAArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval State of flash option bit EDATA_EN (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_IsEnabledEDATAArea(FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->EDATA1R_PRG : &flashx->EDATA2R_PRG;
  return ((STM32_READ_BIT(*reg_addr, FLASH_EDATA1R_CUR_EN) == (FLASH_EDATA1R_CUR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the data flash start page by bank.
  * @rmtoll
  *  EDATA1R_PRG/EDATA2R_PRG    EDATA1R_EDATA_STRT/EDATA2R_EDATA_STRT   LL_FLASH_OB_SetEDATAAreaStartPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can take any value between 0 and 7.
  */
__STATIC_INLINE void LL_FLASH_OB_SetEDATAAreaStartPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t start_page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->EDATA1R_PRG : &flashx->EDATA2R_PRG;
  STM32_MODIFY_REG(*reg_addr, FLASH_EDATA1R_CUR_STRT, start_page << FLASH_EDATA1R_CUR_STRT_Pos);
}

/**
  * @brief  Get the data flash start page by bank.
  * @rmtoll
  *  WRP1R_PRG/WRP2R_PRG          WRP1R_WRPSG/WRP2R_WRPSG          LL_FLASH_OB_GetEDATAAreaStartPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval The start page of the data flash area.
  *         This parameter can take any value between 0 and 15.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetEDATAAreaStartPage(FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->EDATA1R_PRG : &flashx->EDATA2R_PRG;
  return (STM32_READ_BIT(*reg_addr, FLASH_EDATA1R_CUR_STRT) >> FLASH_EDATA1R_CUR_STRT_Pos);
}

/**
  * @brief  Set the flash start page of the hide protection area by bank.
  * @rmtoll
  *  HDP1R/HDP2R          HDP1_STRT/HDP2_STRT          LL_FLASH_OB_SetHDPAreaStartPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_SetHDPAreaStartPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t start_page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->HDP1R_PRG : &flashx->HDP2R_PRG;
  STM32_MODIFY_REG(*reg_addr, FLASH_HDP1R_CUR_STRT, (start_page << FLASH_HDP1R_CUR_STRT_Pos));
}

/**
  * @brief  Get the flash start page of the hide protection area by bank.
  * @rmtoll
  *  HDP1R1/HDP2R1          HDP1_STRT/HDP2_STRT          LL_FLASH_OB_GetHDPAreaStartPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetHDPAreaStartPage(FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->HDP1R_CUR : &flashx->HDP2R_CUR;
  return (STM32_READ_BIT(*reg_addr, FLASH_HDP1R_CUR_STRT));
}

/**
  * @brief  Set the flash end page of the hide protection area by bank.
  * @rmtoll
  *  HDP1R1/HDP2R1          HDP1_END/HDP2_END          LL_FLASH_OB_SetHDPAreaEndPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  end_page This parameter can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_SetHDPAreaEndPage(FLASH_TypeDef *flashx, uint32_t bank, uint32_t end_page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->HDP1R_PRG : &flashx->HDP2R_PRG;
  STM32_MODIFY_REG(*reg_addr, FLASH_HDP1R_CUR_END, (end_page << FLASH_HDP1R_CUR_END_Pos));
}

/**
  * @brief  Get the flash end page of the hide protection area by bank.
  * @rmtoll
  *  HDP1R1          HDP1_END/HDP2_END          LL_FLASH_OB_GetHDPAreaEndPage
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @retval Returned value can be a value between 0x00U and the maximum number of page by bank.
  */
__STATIC_INLINE uint32_t LL_FLASH_OB_GetHDPAreaEndPage(FLASH_TypeDef *flashx, uint32_t bank)
{
  const __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->HDP1R_CUR : &flashx->HDP2R_CUR;
  return (STM32_READ_BIT(*reg_addr, FLASH_HDP1R_CUR_END) >> FLASH_HDP1R_CUR_END_Pos);
}

/**
  * @brief  Configure the flash hide protection area by bank.
  * @rmtoll
  *  HDP1R_PRG/HDP2R_PRG        HDP1R_END|HDP1R_STRT/HDP2R_END|HDP2R_STRT      LL_FLASH_OB_ConfigHDPArea
  * @param  flashx FLASH instance.
  * @param  bank
  *         This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BANK_1
  *         @arg @ref LL_FLASH_BANK_2
  * @param  start_page
  *         This parameter can be a value between 0x00U and the maximum number of pages by bank.
  * @param  end_page
  *         This parameter can be a value between 0x00U and the maximum number of pages by bank.
  */
__STATIC_INLINE void LL_FLASH_OB_ConfigHDPArea(FLASH_TypeDef *flashx,
                                               uint32_t bank,
                                               uint32_t start_page,
                                               uint32_t end_page)
{
  __IO uint32_t *reg_addr = (bank == LL_FLASH_BANK_1) ? &flashx->HDP1R_PRG : &flashx->HDP2R_PRG;
  STM32_MODIFY_REG(*reg_addr, FLASH_HDP1R_CUR_END | FLASH_HDP1R_CUR_STRT,
                   (end_page << FLASH_HDP1R_CUR_END_Pos) + (start_page << FLASH_HDP1R_CUR_STRT_Pos));
}

/**
  * @brief  Get the flash ECC single-error (ECC) corrected address offset.
  * @rmtoll
  *  ECCCORR           ADDR_ECC           LL_FLASH_GetECCCAddressOffset
  * @param  flashx FLASH instance.
  * @retval ECC single-error corrected address offset.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCCAddressOffset(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ECCCORR, FLASH_ECCCORR_ADDR_ECC));
}

/**
  * @brief  Get the flash corrected ECC single fail data flash flag.
  * @rmtoll
  *  ECCCORR           DATA_ECC           LL_FLASH_IsActiveFlag_DATA_ECCC
  * @param  flashx FLASH instance.
  * @retval State of corrected ECC single fail data flash flag (1: ECC fail in data flash / 0: not in data flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_DATA_ECCC(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCCORR, FLASH_ECCCORR_EDATA_ECC) == (FLASH_ECCCORR_EDATA_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash ECC single fail bank flag.
  * @rmtoll
  *  ECCCORR           BK_ECC           LL_FLASH_IsActiveFlag_BK_ECCC
  * @param  flashx FLASH instance.
  * @retval Returned value : ECC failed bank (1: ECC fail in Bank 2 / 0: ECC fail in Bank 1).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BK_ECCC(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCCORR, FLASH_ECCCORR_BK_ECC) == (FLASH_ECCCORR_BK_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash corrected ECC single fail system flash flag.
  * @rmtoll
  *  ECCCORR           SYSF_ECC           LL_FLASH_IsActiveFlag_SYSF_ECCC
  * @param  flashx FLASH instance.
  * @retval State of corrected ECC single fail system flash flag (1: ECC fail in system flash / 0: not in system flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_SYSF_ECCC(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCCORR, FLASH_ECCCORR_SYSF_ECC) == (FLASH_ECCCORR_SYSF_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash corrected ECC single fail OTP flash flag.
  * @rmtoll
  *  ECCCORR           OTP_ECC           LL_FLASH_IsActiveFlag_OTP_ECCC
  * @param  flashx FLASH instance.
  * @retval State of corrected ECC single fail OTP flash flag (1: ECC fail in OTP flash / 0: not in OTP flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OTP_ECCC(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCCORR, FLASH_ECCCORR_OTP_ECC) == (FLASH_ECCCORR_OTP_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Read the state of selected ECCC flags.
  * @rmtoll
  *  ECCCORR     DATA_ECC|BK_ECC/SYSF_ECC|OTP_ECC      LL_FLASH_ReadFlag_ECCC
  * @param  flashx FLASH instance.
  * @param  flags
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EDATA_ECC
  *         @arg @ref LL_FLASH_FLAG_BK_ECC
  *         @arg @ref LL_FLASH_FLAG_SYSF_ECC
  *         @arg @ref LL_FLASH_FLAG_OTP_ECC
  *         @arg @ref LL_FLASH_FLAG_ECC_AREA_ALL
  * @retval Returned value : state of ECCC selected flags.
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag_ECCC(const FLASH_TypeDef *flashx, uint32_t flags)
{
  return (STM32_READ_BIT(flashx->ECCCORR, flags));
}

/**
  * @brief  Enable the flash ECC single correction error interrupt.
  * @rmtoll
  *  ECCCORR           ECCCIE           LL_FLASH_EnableIT_ECCC
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_EnableIT_ECCC(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->ECCCORR, FLASH_ECCCORR_ECCCIE);
}

/**
  * @brief  Disable the flash ECC single correction error interrupt.
  * @rmtoll
  *  ECCCORR           ECCCIE           LL_FLASH_DisableIT_ECCC
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_DisableIT_ECCC(FLASH_TypeDef *flashx)
{
  STM32_CLEAR_BIT(flashx->ECCCORR, FLASH_ECCCORR_ECCCIE);
}

/**
  * @brief  Check if the flash ECC interrupt is enabled or disabled.
  * @rmtoll
  *  ECCCORR           ECCCIE           LL_FLASH_IsEnabledIT_ECCC
  * @param  flashx FLASH instance.
  * @retval State of flash ECC interruption (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_ECCC(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCCORR, FLASH_ECCCORR_ECCCIE) == (FLASH_ECCCORR_ECCCIE)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the flash ECC single error flag is active.
  * @rmtoll
  *  ECCCORR           ECCC           LL_FLASH_IsActiveFlag_ECCC
  * @param  flashx FLASH instance.
  * @retval State of flash ECCC flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_ECCC(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCCORR, FLASH_ECCCORR_ECCC) == (FLASH_ECCCORR_ECCC)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flash ECC single error flag.
  * @rmtoll
  *  ECCCORR           ECCC           LL_FLASH_ClearFlag_ECCC
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_ECCC(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->ECCCORR, FLASH_ECCCORR_ECCC);
}

/**
  * @brief  Get the flash ECC double-error (ECCD) fail address offset.
  * @rmtoll
  *  ECCDETR           ADDR_ECC           LL_FLASH_GetECCDAddressOffset
  * @param  flashx FLASH instance.
  * @retval ECC double-error detected address offset.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCDAddressOffset(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ECCDETR, FLASH_ECCDETR_ADDR_ECC));
}

/**
  * @brief  Get the flash ECC double fail data flash flag.
  * @rmtoll
  *  ECCDETR           DATA_ECC           LL_FLASH_IsActiveFlag_DATA_ECCD
  * @param  flashx FLASH instance.
  * @retval State of ECC double fail data flash flag (1: ECC fail in data flash / 0: not in data flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_DATA_ECCD(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCDETR, FLASH_ECCDETR_EDATA_ECC) == (FLASH_ECCDETR_EDATA_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash ECC double fail bank flag.
  * @rmtoll
  *  ECCDETR           BK_ECC           LL_FLASH_IsActiveFlag_BK_ECCD
  * @param  flashx FLASH instance.
  * @retval Returned value : ECC failed bank (1: ECC fail in Bank 2 / 0: ECC fail in Bank 1).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BK_ECCD(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCDETR, FLASH_ECCDETR_BK_ECC) == (FLASH_ECCDETR_BK_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash ECC double fail system flash flag.
  * @rmtoll
  *  ECCDETR           SYSF_ECC           LL_FLASH_IsActiveFlag_SYSF_ECCD
  * @param  flashx FLASH instance.
  * @retval State of ECC double fail system flash flag (1: ECC fail in system flash / 0: not in system flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_SYSF_ECCD(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCDETR, FLASH_ECCDETR_SYSF_ECC) == (FLASH_ECCDETR_SYSF_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Get the flash ECC double fail OTP flash flag.
  * @rmtoll
  *  ECCDETR           OTP_ECC           LL_FLASH_IsActiveFlag_OTP_ECCD
  * @param  flashx FLASH instance.
  * @retval State of ECC double fail OTP flash flag (1: ECC fail in OTP flash / 0: not in OTP flash).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OTP_ECCD(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCDETR, FLASH_ECCDETR_OTP_ECC) == (FLASH_ECCDETR_OTP_ECC)) ? 1UL : 0UL);
}

/**
  * @brief  Read the state of selected ECCD flags.
  * @rmtoll
  *  ECCDETR     DATA_ECC|BK_ECC/SYSF_ECC|OTP_ECC     LL_FLASH_ReadFlag_ECCD
  * @param  flashx FLASH instance.
  * @param  flags
  *         This parameter can one or a combination of the following values:
  *         @arg @ref LL_FLASH_FLAG_EDATA_ECC
  *         @arg @ref LL_FLASH_FLAG_BK_ECC
  *         @arg @ref LL_FLASH_FLAG_SYSF_ECC
  *         @arg @ref LL_FLASH_FLAG_OTP_ECC
  *         @arg @ref LL_FLASH_FLAG_ECC_AREA_ALL
  * @retval Returned value : state of ECCD selected flags.
  */
__STATIC_INLINE uint32_t LL_FLASH_ReadFlag_ECCD(const FLASH_TypeDef *flashx, uint32_t flags)
{
  return (STM32_READ_BIT(flashx->ECCDETR, flags));
}

/**
  * @brief  Check if the flash ECC double error flag is active.
  * @rmtoll
  *  ECCDETR           ECCD           LL_FLASH_IsActiveFlag_ECCD
  * @param  flashx FLASH instance.
  * @retval State of flash ECCD flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_ECCD(const FLASH_TypeDef *flashx)
{
  return ((STM32_READ_BIT(flashx->ECCDETR, FLASH_ECCDETR_ECCD) == (FLASH_ECCDETR_ECCD)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the flash ECC single error flag.
  * @rmtoll
  *  ECCDETR           ECCD           LL_FLASH_ClearFlag_ECCD
  * @param  flashx FLASH instance.
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_ECCD(FLASH_TypeDef *flashx)
{
  STM32_SET_BIT(flashx->ECCDETR, FLASH_ECCDETR_ECCD);
}

/**
  * @brief  Get the flash ECC double fail data.
  * @rmtoll
  *  ECCDR           DATA_ECC           LL_FLASH_GetECCDData
  * @param  flashx FLASH instance.
  * @retval Returned value : ECC failed data.
  */
__STATIC_INLINE uint32_t LL_FLASH_GetECCDData(const FLASH_TypeDef *flashx)
{
  return (STM32_READ_BIT(flashx->ECCDR, FLASH_ECCDR_DATA_ECC) >> FLASH_ECCDR_DATA_ECC_Pos);
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

#endif /* defined (FLASH) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_LL_FLASH_H */
