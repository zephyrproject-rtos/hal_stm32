/**
  **********************************************************************************************************************
  * @file    stm32g5xx_ll_pwr.h
  * @brief   Header file of PWR LL module.
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
#ifndef STM32G5XX_LL_PWR_H
#define STM32G5XX_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined (PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_LL_WAKEUP_PIN_OFFSET Wake-Up Pins register offsets Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
/* Wake-Up Pins PWR register offsets */
#define LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET    2UL
#define LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK       0x7FU
#define LL_PWR_WAKEUP_PIN_REF                   PWR_WUCR_WUPP1
#define LL_PWR_WAKEUP_PIN_REF_POS               PWR_WUCR_WUPP1_Pos
#define LL_PWR_WAKEUP_PIN_PULL_REF              PWR_WUCR_WUPPUPD1
#define LL_PWR_WAKEUP_PIN_PULL_REF_POS          PWR_WUCR_WUPPUPD1_Pos
/**
  * @}
  */

/** @defgroup PWR_LL_SRAM2_STOP_RETENTION_POSITION SRAM2 Stop Retention bits position
  * @brief    Position define which can be used in HAL_PWR_LP_EnableMemoryPageRetention /
  *           HAL_PWR_LP_EnableMemoryPageRetention functions.
  * @{
  */
#define LL_PWR_SRAM2_STOP_RETENTION_POS     PWR_LPMCR_SRAM2PDS1_Pos /*!< SRAM2 Page 1 retention in Stop mode position */
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_LOW_POWER_MODE_SELECTION  Low Power Mode Selection
  * @{
  */
#define LL_PWR_STOP_MODE    (0U)                   /*!< STOP mode    */
#define LL_PWR_STANDBY_MODE PWR_LPMCR_LPMS         /*!< STANDBY mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_REGU_VOLT_SCALE_POS  PWR_VOSCR_VOS_Pos /*!< Voltage scaling range register position */
#define LL_PWR_REGU_VOLT_SCALE_0    PWR_VOSCR_VOS     /*!< Voltage scaling range 0 */
#define LL_PWR_REGU_VOLT_SCALE_1    PWR_VOSCR_VOS_1   /*!< Voltage scaling range 1 */
#define LL_PWR_REGU_VOLT_SCALE_2    PWR_VOSCR_VOS_0   /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ACTIVE_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_ACTIVE_VOLT_SCALE_POS  PWR_VOSSR_ACTVOS_Pos  /*!< Active voltage scaling range register position */
#define LL_PWR_ACTIVE_VOLT_SCALE_0    PWR_VOSSR_ACTVOS      /*!< Voltage scaling range 0 */
#define LL_PWR_ACTIVE_VOLT_SCALE_1    PWR_VOSSR_ACTVOS_1    /*!< Voltage scaling range 1 */
#define LL_PWR_ACTIVE_VOLT_SCALE_2    PWR_VOSSR_ACTVOS_0    /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM_SPEED_SELECTION PWR SRAM speed selection
  * @{
  */
#define LL_PWR_SRAM_HIGH_SPEED   0                 /*!< SRAMs operating at high speed (VOS1 or VOS0 voltage scaling) */
#define LL_PWR_SRAM_LOW_SPEED    PWR_VOSSR_SRAMLS  /*!< SRAMs operating at low speed (VOS2 voltage scaling) */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_INTERNAL_REGULATORS_BYPASS PWR SMPS and LDO internal regulators bypass in Range 0 definition
  * @{
  */
#define LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED  0U /*!< SMPS / LDO internal regulators bypass in Range 0 */
#define LL_PWR_MAIN_REGU_SUPPLY_BYPASSED      PWR_SCCR_BYPASS /*!< SMPS / LDO internal regulators bypass in Range 0 */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_INTERNAL_REGULATOR_SUPPLY PWR Regulator supply
  * @{
  */
#define LL_PWR_MAIN_REGU_SUPPLY_LDO_ENABLED             PWR_SCCR_LDOEN  /*!< LDO regulator supply  */
#if defined(PWR_SCCR_SMPSEN)
#define LL_PWR_MAIN_REGU_SUPPLY_SMPS_ENABLED            PWR_SCCR_SMPSEN /*!< SMPS regulator supply */
#endif /* PWR_SCCR_SMPSEN */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM1_STOP_CONTENTS_RETENTION PWR SRAM1 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM1_STOP_RETENTION    PWR_LPMCR_SRAM1PDS  /*!< SRAM1 retention in Stop mode  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SRAM2_STOP_CONTENTS_RETENTION PWR SRAM2 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM2_PAGE1_STOP_RETENTION   PWR_LPMCR_SRAM2PDS1      /*!< SRAM2 Page 1 retention in Stop mode */
#define LL_PWR_SRAM2_PAGE2_STOP_RETENTION   PWR_LPMCR_SRAM2PDS2      /*!< SRAM2 Page 2 retention in Stop mode */
#define LL_PWR_SRAM2_STOP_RETENTION         (PWR_LPMCR_SRAM2PDS1 | PWR_LPMCR_SRAM2PDS2)  /*!< SRAM2 retention
                                                                                          in Stop mode */
/**
  * @}
  */
#if defined(SRAM3_BASE)
/** @defgroup PWR_LL_EC_SRAM3_STOP_CONTENTS_RETENTION PWR SRAM3 Content retention in Stop mode
  * @{
  */
#define LL_PWR_SRAM3_STOP_RETENTION    PWR_LPMCR_SRAM3PDS          /*!< SRAM3 retention in Stop mode  */
/**
  * @}
  */
#endif /* SRAM3_BASE */

/** @defgroup PWR_LL_EC_PVD_LEVEL_SELECTION PWR Power Voltage Detector Level Selection
  * @{
  */
#define LL_PWR_PVD_VDD_LEVEL_0   0U               /*!< Voltage threshold detected by PVD
                                                         Rising edge typical :   2.85V
                                                         Falling edge typical :  2.75V   */
#define LL_PWR_PVD_VDD_LEVEL_1   PWR_VMCR_PLS_0  /*!< Voltage threshold detected by PVD
                                                         Rising edge typical :   3.05V
                                                         Falling edge typical :  2.95V   */
#define LL_PWR_PVD_PVDIN_VREFINT PWR_VMCR_PLS    /*!< External voltage on PVD_IN pin,
                                                      compared to internal VREFINT level */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_MONITORING_STATE RTC domain voltage and temperature monitoring state
  * @{
  */
#define LL_PWR_VDD_TEMP_MONITOR_DISABLED  0U                /*!< Monitoring disabled  */
#define LL_PWR_VDD_TEMP_MONITOR_ENABLED   PWR_TMCR_MONEN    /*!< Monitoring enabled   */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_AVDLEVEL Power Analog Voltage Level Detector
  * @{
  */
#define LL_PWR_AVD_VDDA_LEVEL_0   0U             /*!< Voltage threshold detected by AVD
                                                        Rising edge typical :   2.80V
                                                        Falling edge typical :  2.74V */
#define LL_PWR_AVD_VDDA_LEVEL_1   PWR_VMCR_ALS  /*!< Voltage threshold detected by AVD
                                                        Rising edge typical :   3.00V
                                                        Falling edge typical :  2.94V */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN PWR Wake Up Pin
  * @{
  */
#define LL_PWR_WAKEUP_PIN_1   PWR_WUCR_WUPEN1  /*!< Wakeup pin 1 enable   */
#define LL_PWR_WAKEUP_PIN_2   PWR_WUCR_WUPEN2  /*!< Wakeup pin 2 enable   */
#define LL_PWR_WAKEUP_PIN_4   PWR_WUCR_WUPEN4  /*!< Wakeup pin 4 enable   */
#define LL_PWR_WAKEUP_PIN_5   PWR_WUCR_WUPEN5  /*!< Wakeup pin 5 enable   */
#define LL_PWR_WAKEUP_PIN_6   PWR_WUCR_WUPEN6  /*!< Wakeup pin 6 enable   */
#define LL_PWR_WAKEUP_PIN_7   PWR_WUCR_WUPEN7  /*!< Wakeup pin 7 enable   */
#if defined(PWR_WUCR_WUPEN8)
#define LL_PWR_WAKEUP_PIN_8   PWR_WUCR_WUPEN8  /*!< Wakeup pin 8 enable   */
#define LL_PWR_WAKEUP_PIN_ALL (0xFBU)          /*!< Wakeup all pin enable */
#else
#define LL_PWR_WAKEUP_PIN_ALL (0x7BU)          /*!< Wakeup all pin enable */
#endif /* PWR_WUCR_WUPEN8 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_PULL  Wakeup Pins pull configuration
  * @{
  */
#define LL_PWR_WAKEUP_PIN_PULL_NO     0x00000000UL   /*!< Configure Wake-Up pin in no pull   */
#define LL_PWR_WAKEUP_PIN_PULL_UP     0x00000001UL   /*!< Configure Wake-Up pin in pull Up   */
#define LL_PWR_WAKEUP_PIN_PULL_DOWN   0x00000002UL   /*!< Configure Wake-Up pin in pull Down */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_POLARITY  Wakeup Pins polarity
  * @{
  */
#define LL_PWR_WAKEUP_PIN_POLARITY_HIGH     0x00000000UL   /*!< Wakeup pin polarity high  */
#define LL_PWR_WAKEUP_PIN_POLARITY_LOW      0x00000001UL   /*!< Wakeup pin polarity low   */
/**
  * @}
  */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PRIVILEGE_ITEM  Privilege items
  * @{
  */
#define LL_PWR_PRIV_ITEM_SPRIV    PWR_PRIVCFGR_SPRIV                          /*!< Secure privilege item      */
#define LL_PWR_PRIV_ITEM_NSPRIV   PWR_PRIVCFGR_NSPRIV                         /*!< Non-Secure privilege items */
#define LL_PWR_PRIV_ITEM_ALL      (PWR_PRIVCFGR_SPRIV | PWR_PRIVCFGR_NSPRIV)  /*!< All privilege items        */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PRIVILEGE_ATTRIBUTE  Privilege attribute
  * @{
  */
#define LL_PWR_ATTR_NPRIV     0U   /*!< Non-privileged attribute  */
#define LL_PWR_ATTR_PRIV      1U   /*!< Privileged attribute      */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ITEMS_SECURE_ATTRIBUTE PWR Items Secure Attribute
  * @{
  */
#define LL_PWR_SEC_ITEM_WUP1SEC   PWR_SECCFGR_WUP1SEC /* Wake up pin 1 secure mode                  */
#define LL_PWR_SEC_ITEM_WUP2SEC   PWR_SECCFGR_WUP2SEC /* Wake up pin 2 secure mode                  */
#define LL_PWR_SEC_ITEM_WUP4SEC   PWR_SECCFGR_WUP4SEC /* Wake up pin 4 secure mode                  */
#define LL_PWR_SEC_ITEM_WUP5SEC   PWR_SECCFGR_WUP5SEC /* Wake up pin 5 secure mode                  */
#define LL_PWR_SEC_ITEM_WUP6SEC   PWR_SECCFGR_WUP6SEC /* Wake up pin 6 secure mode                  */
#define LL_PWR_SEC_ITEM_WUP7SEC   PWR_SECCFGR_WUP7SEC /* Wake up pin 7 secure mode                  */
#if defined(PWR_WUCR_WUPEN8)
#define LL_PWR_SEC_ITEM_WUP8SEC   PWR_SECCFGR_WUP8SEC /* Wake up pin 8 secure mode                  */
#endif /* PWR_WUCR_WUPEN8 */
#define LL_PWR_SEC_ITEM_RETSEC    PWR_SECCFGR_RETSEC  /* Retention secure mode                      */
#define LL_PWR_SEC_ITEM_LPMSEC    PWR_SECCFGR_LPMSEC  /* Low-power modes secure mode                */
#define LL_PWR_SEC_ITEM_SCMSEC    PWR_SECCFGR_SCMSEC  /* Supply configuration and monitoring secure */
#define LL_PWR_SEC_ITEM_RTCSEC    PWR_SECCFGR_RTMSEC  /* RTC domain secure mode                     */
#if defined(PWR_USBSCR_USB33SV)
#define LL_PWR_SEC_ITEM_VUSBSEC   PWR_SECCFGR_VUSBSEC /* Voltage USB secure mode                    */
#endif /* PWR_USBSCR_USB33SV */

#if defined(PWR_WUCR_WUPEN8) && defined(PWR_USBSCR_USB33SV)
#define LL_PWR_SEC_ITEM_ALL (PWR_SECCFGR_WUP1SEC | PWR_SECCFGR_WUP2SEC | PWR_SECCFGR_WUP4SEC | \
                             PWR_SECCFGR_WUP5SEC | PWR_SECCFGR_WUP6SEC | PWR_SECCFGR_WUP7SEC | \
                             PWR_SECCFGR_WUP8SEC | PWR_SECCFGR_RETSEC  | PWR_SECCFGR_LPMSEC  | \
                             PWR_SECCFGR_SCMSEC  | PWR_SECCFGR_RTMSEC  | PWR_SECCFGR_VUSBSEC)
#elif defined(PWR_WUCR_WUPEN8)
#define LL_PWR_SEC_ITEM_ALL (PWR_SECCFGR_WUP1SEC | PWR_SECCFGR_WUP2SEC | PWR_SECCFGR_WUP4SEC | \
                             PWR_SECCFGR_WUP5SEC | PWR_SECCFGR_WUP6SEC | PWR_SECCFGR_WUP7SEC | \
                             PWR_SECCFGR_WUP8SEC | PWR_SECCFGR_RETSEC  | PWR_SECCFGR_LPMSEC  | \
                             PWR_SECCFGR_SCMSEC  | PWR_SECCFGR_RTMSEC)
#elif defined(PWR_USBSCR_USB33SV)
#define LL_PWR_SEC_ITEM_ALL (PWR_SECCFGR_WUP1SEC | PWR_SECCFGR_WUP2SEC | PWR_SECCFGR_WUP4SEC | \
                             PWR_SECCFGR_WUP5SEC | PWR_SECCFGR_WUP6SEC | PWR_SECCFGR_WUP7SEC | \
                             PWR_SECCFGR_RETSEC  | PWR_SECCFGR_LPMSEC  | PWR_SECCFGR_SCMSEC  | \
                             PWR_SECCFGR_RTMSEC  | PWR_SECCFGR_VUSBSEC)
#else
#define LL_PWR_SEC_ITEM_ALL (PWR_SECCFGR_WUP1SEC | PWR_SECCFGR_WUP2SEC | PWR_SECCFGR_WUP4SEC | \
                             PWR_SECCFGR_WUP5SEC | PWR_SECCFGR_WUP6SEC | PWR_SECCFGR_WUP7SEC | \
                             PWR_SECCFGR_RETSEC  | PWR_SECCFGR_LPMSEC  | PWR_SECCFGR_SCMSEC  | \
                             PWR_SECCFGR_RTMSEC)
#endif /* PWR_WUCR_WUPEN8 && PWR_USBSCR_USB33SV */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SECURE_ATTRIBUTE  Secure attribute
  * @{
  */
#define LL_PWR_ATTR_NSEC     0U   /*!< Non-secure attribute  */
#define LL_PWR_ATTR_SEC      1U   /*!< Secure attribute      */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/

/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common Write and Read Registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_PWR_WRITE_REG(reg, value) STM32_WRITE_REG((PWR)->reg, (value))

/**
  * @brief  Read a value in PWR register.
  * @param  reg      Register to be read.
  * @retval Register value
  */
#define LL_PWR_READ_REG(reg) STM32_READ_REG((PWR)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_CONFIGURATION PWR Configuration
  * @{
  */

/**
  * @brief  Set system power mode.
  * @rmtoll
  *   LPMCR              LPMS          LL_PWR_SetPowerMode
  * @param  mode : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOP_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  * @note   When Stop mode is selected, WFI or WFE instruction is required to enter Stop mode.
  * @note   When Standby mode is selected, only WFI instruction is required to enter Standby mode.
  * @note   Call DSB instruction to ensure there are no outstanding memory transactions prior to executing WFI or WFE.
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t mode)
{
  STM32_MODIFY_REG(PWR->LPMCR, PWR_LPMCR_LPMS, mode);
}

/**
  * @brief  Get system power mode.
  * @rmtoll
  *   LPMCR             LPMS          LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOP_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (STM32_READ_BIT(PWR->LPMCR, PWR_LPMCR_LPMS));
}

/**
  * @brief  Enable the Flash Power Down in stop mode.
  * @rmtoll
  *    LPMCR    FLPS       LL_PWR_EnableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_EnableFlashLowPWRMode(void)
{
  STM32_SET_BIT(PWR->LPMCR, PWR_LPMCR_FLPS);
}

/**
  * @brief  Disable the Flash Power Down in stop mode.
  * @rmtoll
  *    LPMCR    FLPS       LL_PWR_DisableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_DisableFlashLowPWRMode(void)
{
  STM32_CLEAR_BIT(PWR->LPMCR, PWR_LPMCR_FLPS);
}

/**
  * @brief  Check if the Flash Power Down in stop mode is enabled.
  * @rmtoll
  *    LPMCR    FLPS       LL_PWR_IsEnabledFlashLowPWRMode
  * @retval 0 if flash low power mode is disabled, 1 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashLowPWRMode(void)
{
  return ((STM32_READ_BIT(PWR->LPMCR, PWR_LPMCR_FLPS) == (PWR_LPMCR_FLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable memory content stop retention.
  * @rmtoll
  *    LPMCR              SRAM1PDS     LL_PWR_EnableMemoryStopRetention \n
  *    LPMCR              SRAM2PDS1    LL_PWR_EnableMemoryStopRetention \n
  *    LPMCR              SRAM2PDS2    LL_PWR_EnableMemoryStopRetention \n
#if defined(SRAM3_BASE)
  *    LPMCR              SRAM3PDS     LL_PWR_EnableMemoryStopRetention
#endif
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_RETENTION
#if defined(SRAM3_BASE)
  *         @arg @ref LL_PWR_SRAM3_STOP_RETENTION
#endif
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_EnableMemoryStopRetention(uint32_t memory)
{
  STM32_CLEAR_BIT(PWR->LPMCR, memory);
}

/**
  * @brief  Disable memory content stop retention.
  * @rmtoll
  *    LPMCR              SRAM1PDS     LL_PWR_DisableMemoryStopRetention \n
  *    LPMCR              SRAM2PDS1    LL_PWR_DisableMemoryStopRetention \n
  *    LPMCR              SRAM2PDS2    LL_PWR_DisableMemoryStopRetention \n
#if defined(SRAM3_BASE)
  *    LPMCR              SRAM3PDS     LL_PWR_DisableMemoryStopRetention
#endif
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_RETENTION
#if defined(SRAM3_BASE)
  *         @arg @ref LL_PWR_SRAM3_STOP_RETENTION
#endif
  * @note   (*) value not defined in all devices
  */
__STATIC_INLINE void LL_PWR_DisableMemoryStopRetention(uint32_t memory)
{
  STM32_SET_BIT(PWR->LPMCR, memory);
}

/**
  * @brief  Get memory content stop retention.
  * @rmtoll
  *    LPMCR              SRAM1PDS     LL_PWR_IsEnabledMemoryStopRetention \n
  *    LPMCR              SRAM2PDS1    LL_PWR_IsEnabledMemoryStopRetention \n
  *    LPMCR              SRAM2PDS2    LL_PWR_IsEnabledMemoryStopRetention \n
#if defined(SRAM3_BASE)
  *    LPMCR              SRAM3PDS     LL_PWR_IsEnabledMemoryStopRetention
#endif
  * @param  memory This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SRAM1_STOP_RETENTION
  *         @arg @ref LL_PWR_SRAM2_STOP_RETENTION
#if defined(SRAM3_BASE)
  *         @arg @ref LL_PWR_SRAM3_STOP_RETENTION
#endif
  * @note   (*) value not defined in all devices
  * @retval 0 if memory bank is not retained, 1 otherwise
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMemoryStopRetention(uint32_t memory)
{
  return ((STM32_READ_BIT(PWR->LPMCR, memory) == (memory)) ? 0UL : 1UL);
}

/**
  * @brief  Enable SRAM2 page(s) content stop retention.
  * @rmtoll
  *    LPMCR              SRAM2PDS1   LL_PWR_EnableSRAM2PagesStopRetention \n
  *    LPMCR              SRAM2PDS2   LL_PWR_EnableSRAM2PagesStopRetention
  * @param  pages This parameter is a bitfield representing each page of the SRAM2
  */
__STATIC_INLINE void LL_PWR_EnableSRAM2PagesStopRetention(uint32_t pages)
{
  STM32_CLEAR_BIT(PWR->LPMCR, (pages & LL_PWR_SRAM2_STOP_RETENTION));
}

/**
  * @brief  Disable SRAM2 page(s) content stop retention.
  * @rmtoll
  *    LPMCR              SRAM2PDS1   LL_PWR_DisableSRAM2PagesStopRetention \n
  *    LPMCR              SRAM2PDS2   LL_PWR_DisableSRAM2PagesStopRetention
  * @param  pages This parameter is a bitfield representing each page of the SRAM2
  */
__STATIC_INLINE void LL_PWR_DisableSRAM2PagesStopRetention(uint32_t pages)
{
  STM32_SET_BIT(PWR->LPMCR, (pages & LL_PWR_SRAM2_STOP_RETENTION));
}

/**
  * @brief  Check SRAM2 page content stop retention.
  * @rmtoll
  *    LPMCR              SRAM2PDS1   LL_PWR_IsEnabledSRAM2PagesStopRetention \n
  *    LPMCR              SRAM2PDS2   LL_PWR_IsEnabledSRAM2PagesStopRetention
  * @param  page This parameter is a bitfield representing each page of the SRAM2
  * @retval 0 if the memory page is not retained, 1 otherwise.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSRAM2PagesStopRetention(uint32_t page)
{
  return (STM32_IS_BIT_SET(PWR->LPMCR, page) ? 0UL : 1UL);
}

/**
  * @brief  Set the regulator supply output voltage.
  * @rmtoll
  *    VOSCR          VOS           LL_PWR_SetRegulatorVoltageScaling
  * @param  voltage_scale This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_0
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  */
__STATIC_INLINE void LL_PWR_SetRegulatorVoltageScaling(uint32_t voltage_scale)
{
  STM32_MODIFY_REG(PWR->VOSCR, PWR_VOSCR_VOS, voltage_scale);
}

/**
  * @brief  Get the programmed regulator supply output voltage.
  * @rmtoll
  *    VOSCR          VOS           LL_PWR_GetRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_0
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulatorVoltageScaling(void)
{
  return (uint32_t)(STM32_READ_BIT(PWR->VOSCR, PWR_VOSCR_VOS));
}

/**
  * @brief  Get current voltage scaling applied to VCORE.
  * @rmtoll
  *    VOSSR            ACTVOS[1:0]          LL_PWR_GetActiveRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_0
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_1
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_2
  */
__STATIC_INLINE uint32_t LL_PWR_GetActiveRegulatorVoltageScaling(void)
{
  return (STM32_READ_BIT(PWR->VOSSR, PWR_VOSSR_ACTVOS));
}

/**
  * @brief  Get current SRAM memories operation speed.
  * @rmtoll
  *    VOSSR            SRAMLS          LL_PWR_GetSRAMOperationSpeed
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_SRAM_HIGH_SPEED
  *         @arg @ref LL_PWR_SRAM_LOW_SPEED
  */
__STATIC_INLINE uint32_t LL_PWR_GetSRAMOperationSpeed(void)
{
  return (STM32_READ_BIT(PWR->VOSSR, PWR_VOSSR_SRAMLS));
}

/**
  * @brief  Enable VDD voltage and Temperature monitoring.
  * @rmtoll
  *    TMCR    MONEN       LL_PWR_EnableTemperatureVddMonitor
  */
__STATIC_INLINE void LL_PWR_EnableTemperatureVddMonitor(void)
{
  STM32_SET_BIT(PWR->TMCR, PWR_TMCR_MONEN);
}

/**
  * @brief  Disable VDD voltage and Temperature monitoring.
  * @rmtoll
  *    TMCR    MONEN       LL_PWR_DisableTemperatureVddMonitor
  */
__STATIC_INLINE void LL_PWR_DisableTemperatureVddMonitor(void)
{
  STM32_CLEAR_BIT(PWR->TMCR, PWR_TMCR_MONEN);
}

/**
  * @brief  Check if the VDD voltage and Temperature monitoring is enabled.
  * @rmtoll
  *    TMCR    MONEN      LL_PWR_IsEnabledTemperatureVddMonitor
  * @retval 0 if temperature and VDD monitoring is disabled, 1 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledTemperatureVddMonitor(void)
{
  return ((STM32_READ_BIT(PWR->TMCR, PWR_TMCR_MONEN) == PWR_TMCR_MONEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable write protection on the RTC domain.
  * @rmtoll
  *    RTCCR    DRTCP       LL_PWR_EnableRTCDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_EnableRTCDomainWriteProtection(void)
{
  STM32_CLEAR_BIT(PWR->RTCCR, PWR_RTCCR_DRTCP);
}

/**
  * @brief  Disable write protection on the RTC domain.
  * @rmtoll
  *    RTCCR    DRTCP       LL_PWR_DisableRTCDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_DisableRTCDomainWriteProtection(void)
{
  STM32_SET_BIT(PWR->RTCCR, PWR_RTCCR_DRTCP);
}

/**
  * @brief  Check if the RTC domain write protection is enabled.
  * @rmtoll
  *    RTCCR    DRTCP       LL_PWR_IsEnabledRTCDomainWriteProtection
  * @retval 0 if RTC domain write protection is disabled, 1 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledRTCDomainWriteProtection(void)
{
  return ((STM32_READ_BIT(PWR->RTCCR, PWR_RTCCR_DRTCP) == (PWR_RTCCR_DRTCP)) ? 0UL : 1UL);
}

#if defined (PWR_UCPDR_UCPD_STBY)
/**
  * @brief  Enable the USB type-C and power delivery retention in Standby mode.
  * @note   This function must be called just before entering Standby mode.
  * @rmtoll
  *    UCPDR          UCPD_STBY    LL_PWR_EnableUCPDRetentionStandbyMode
  */
__STATIC_INLINE void LL_PWR_EnableUCPDRetentionStandbyMode(void)
{
  STM32_SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief  Disable the USB type-C and power delivery retention in Standby mode.
  * @note   This function must be called after exiting Standby mode and before
  *         any UCPD configuration update.
  * @rmtoll
  *    UCPDR          UCPD_STBY     LL_PWR_DisableUCPDRetentionStandbyMode
  */
__STATIC_INLINE void LL_PWR_DisableUCPDRetentionStandbyMode(void)
{
  STM32_CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief  Check if the USB Type-C and Power Delivery Standby mode retention is enabled.
  * @rmtoll
  *    UCPDR          UCPD_STBY           LL_PWR_IsEnabledUCPDRetentionStandbyMode
  * @retval 0 if USB Type-C and Power Delivery Standby mode retention is disabled, 1 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDRetentionStandbyMode(void)
{
  return ((STM32_READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY) == (PWR_UCPDR_UCPD_STBY)) ? 1UL : 0UL);
}
#endif /* PWR_UCPDR_UCPD_STBY */

#if defined (PWR_UCPDR_UCPD_DBDIS)
/**
  * @brief  Enable the USB Type-C and power delivery dead battery pull-down behavior
  *         on UCPD CC1 and CC2 pins.
  * @note   After exiting reset, the USB Type-C dead battery behavior is enabled,
  *         which have a pull-down effect on CC1 and CC2 pins. It is recommended
  *         to disable it in all cases, either to stop this pull-down or to hand over
  *         control to the UCPD (which must therefore be initialized before doing the disable).
  * @rmtoll
  *    UCPDR          UCPD_DBDIS           LL_PWR_EnableUCPDDeadBattery
  */
__STATIC_INLINE void LL_PWR_EnableUCPDDeadBattery(void)
{
  STM32_CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Disable the USB Type-C and power delivery dead battery pull-down behavior on UCPD CC1 and CC2 pins.
  * @note   After exiting reset, the USB Type-C dead battery behavior is enabled,
  *         which have a pull-down effect on CC1 and CC2 pins. It is recommended
  *         to disable it in all cases, either to stop this pull-down or to hand over
  *         control to the UCPD (which must therefore be initialized before doing the disable).
  * @rmtoll
  *    UCPDR          UCPD_DBDIS           LL_PWR_DisableUCPDDeadBattery
  */
__STATIC_INLINE void LL_PWR_DisableUCPDDeadBattery(void)
{
  STM32_SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Check the USB Type-C and power delivery dead battery pull-down behavior on UCPD CC1 and CC2 pins.
  * @note   After exiting reset, the USB Type-C dead battery behavior is enabled,
  *         which have a pull-down effect on CC1 and CC2 pins. It is recommended
  *         to disable it in all cases, either to stop this pull-down or to hand over
  *         control to the UCPD (which must therefore be initialized before doing the disable).
  * @rmtoll
  *    UCPDR          UCPD_DBDIS           LL_PWR_IsEnabledUCPDDeadBattery
  * @retval 0 if USB Type-C and Power Delivery dead battery pull-down behavior is disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDDeadBattery(void)
{
  return ((STM32_READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS) == (PWR_UCPDR_UCPD_DBDIS)) ? 0UL : 1UL);
}
#endif /* PWR_UCPDR_UCPD_DBDIS */

/**
  * @brief  Enable power management unit bypass.
  * @rmtoll
  *    SCCR          BYPASS     LL_PWR_EnableBypass
  * @note   Once set, only a complete power cycle can clear this bit. Every other write access will be ignored.
  */
__STATIC_INLINE void LL_PWR_EnableBypass(void)
{
  STM32_SET_BIT(PWR->SCCR, PWR_SCCR_BYPASS);
}

/**
  * @brief  Check if the PWR management unit bypass is enabled or disabled.
  * @rmtoll
  *    SCCR          BYPASS     LL_PWR_IsEnabledBypass
  * @retval 0 if PWR management unit regulator bypass is disabled, 1 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBypass(void)
{
  return ((STM32_READ_BIT(PWR->SCCR, PWR_SCCR_BYPASS) == PWR_SCCR_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  Get the LDO supply status.
  * @rmtoll
  *    SCCR          LDOEN     LL_PWR_IsEnabledLDOSupply
  * @retval 0 if LDO supply is disabled, 1 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledLDOSupply(void)
{
  return ((STM32_READ_BIT(PWR->SCCR, PWR_SCCR_LDOEN) == PWR_SCCR_LDOEN) ? 1UL : 0UL);
}

#if defined(PWR_SCCR_SMPSEN)
/**
  * @brief  Get the SMPS supply status.
  * @rmtoll
  *    SCCR          SMPSEN     LL_PWR_IsEnabledSMPSSupply
  * @retval 0 if SMPS supply is disabled, 1 if enabled
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSSupply(void)
{
  return ((STM32_READ_BIT(PWR->SCCR, PWR_SCCR_SMPSEN) == PWR_SCCR_SMPSEN) ? 1UL : 0UL);
}
#endif /* PWR_SCCR_SMPSEN */

/**
  * @brief  Enable Power Voltage Detector.
  * @rmtoll
  *    VMCR    PVDE       LL_PWR_EnablePVD
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  STM32_SET_BIT(PWR->VMCR, PWR_VMCR_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector.
  * @rmtoll
  *    VMCR    PVDE       LL_PWR_DisablePVD
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  STM32_CLEAR_BIT(PWR->VMCR, PWR_VMCR_PVDE);
}

/**
  * @brief  Check if programmable voltage detector is enabled.
  * @rmtoll
  *    VMCR    PVDE       LL_PWR_IsEnabledPVD
  * @retval 0 if programmable voltage detector is disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((STM32_READ_BIT(PWR->VMCR, PWR_VMCR_PVDE) == (PWR_VMCR_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector.
  * @rmtoll
  *    VMCR    PLS       LL_PWR_SetPVDLevel
  * @param  pvd_level This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_0
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_1
  *         @arg @ref LL_PWR_PVD_PVDIN_VREFINT
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t pvd_level)
{
  STM32_MODIFY_REG(PWR->VMCR, PWR_VMCR_PLS, pvd_level);
}

/**
  * @brief  Get the voltage threshold detection.
  * @rmtoll
  *    VMCR    PLS       LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_0
  *         @arg @ref LL_PWR_PVD_VDD_LEVEL_1
  *         @arg @ref LL_PWR_PVD_PVDIN_VREFINT
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(STM32_READ_BIT(PWR->VMCR, PWR_VMCR_PLS));
}

/**
  * @brief  Enable Analog Power Voltage Detector.
  * @rmtoll
  *    VMCR    AVDEN       LL_PWR_EnableAVD
  */
__STATIC_INLINE void LL_PWR_EnableAVD(void)
{
  STM32_SET_BIT(PWR->VMCR, PWR_VMCR_AVDEN);
}

/**
  * @brief  Disable Analog Power Voltage Detector.
  * @rmtoll
  *    VMCR    AVDEN       LL_PWR_DisableAVD
  */
__STATIC_INLINE void LL_PWR_DisableAVD(void)
{
  STM32_CLEAR_BIT(PWR->VMCR, PWR_VMCR_AVDEN);
}

/**
  * @brief  Check if Analog voltage detector is enabled.
  * @rmtoll
  *    VMCR    AVDEN       LL_PWR_IsEnabledAVD
  * @retval 0 if analog voltage detector is disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAVD(void)
{
  return ((STM32_READ_BIT(PWR->VMCR, PWR_VMCR_AVDEN) == (PWR_VMCR_AVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold to be detected by the Analog Power Voltage Detector.
  * @rmtoll
  *    VMCR    ALS       LL_PWR_SetAVDLevel
  * @param  avd_level This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_0
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_1
  */
__STATIC_INLINE void LL_PWR_SetAVDLevel(uint32_t avd_level)
{
  STM32_MODIFY_REG(PWR->VMCR, PWR_VMCR_ALS, avd_level);
}

/**
  * @brief  Get the Analog Voltage threshold to be detected by the Analog Power Voltage Detector.
  * @rmtoll
  *    VMCR    ALS       LL_PWR_GetAVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_0
  *         @arg @ref LL_PWR_AVD_VDDA_LEVEL_1
  */
__STATIC_INLINE uint32_t LL_PWR_GetAVDLevel(void)
{
  return (uint32_t)(STM32_READ_BIT(PWR->VMCR, PWR_VMCR_ALS));
}

#if defined(PWR_USBSCR_USB33SV)
/**
  * @brief  Enable USB Power supply and disable electrical isolation barrier.
  * @rmtoll
  *    USBSCR    USB33SV       LL_PWR_EnableUSBSupply
  */
__STATIC_INLINE void LL_PWR_EnableUSBSupply(void)
{
  STM32_SET_BIT(PWR->USBSCR, PWR_USBSCR_USB33SV);
}

/**
  * @brief  Disable USB Power supply and enable electrical isolation barrier.
  * @rmtoll
  *    USBSCR    USB33SV       LL_PWR_DisableUSBSupply
  */
__STATIC_INLINE void LL_PWR_DisableUSBSupply(void)
{
  STM32_CLEAR_BIT(PWR->USBSCR, PWR_USBSCR_USB33SV);
}

/**
  * @brief  Check if USB Power supply is enabled.
  * @rmtoll
  *    USBSCR    USB33SV       LL_PWR_IsEnabledUSBSupply
  * @retval 0 if USB Power supply is disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUSBSupply(void)
{
  return ((STM32_READ_BIT(PWR->USBSCR, PWR_USBSCR_USB33SV) == (PWR_USBSCR_USB33SV)) ? 1UL : 0UL);
}
#endif /* PWR_USBSCR_USB33SV */

/**
  * @brief  Enable the wake up pin(s).
  * @rmtoll
  *    WUCR    WUPEN1       LL_PWR_EnableWakeUpPin \n
  *    WUCR    WUPEN2       LL_PWR_EnableWakeUpPin \n
  *    WUCR    WUPEN4       LL_PWR_EnableWakeUpPin \n
  *    WUCR    WUPEN5       LL_PWR_EnableWakeUpPin \n
  *    WUCR    WUPEN6       LL_PWR_EnableWakeUpPin \n
  *    WUCR    WUPEN7       LL_PWR_EnableWakeUpPin \n
#if defined(PWR_WUCR_WUPEN8)
  *    WUCR    WUPEN8       LL_PWR_EnableWakeUpPin
#endif
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t wakeup_pin)
{
  STM32_SET_BIT(PWR->WUCR, wakeup_pin);
}

/**
  * @brief  Disable the wake up pin(s).
  * @rmtoll
  *    WUCR    WUPEN1       LL_PWR_DisableWakeUpPin \n
  *    WUCR    WUPEN2       LL_PWR_DisableWakeUpPin \n
  *    WUCR    WUPEN4       LL_PWR_DisableWakeUpPin \n
  *    WUCR    WUPEN5       LL_PWR_DisableWakeUpPin \n
  *    WUCR    WUPEN6       LL_PWR_DisableWakeUpPin \n
  *    WUCR    WUPEN7       LL_PWR_DisableWakeUpPin \n
#if defined(PWR_WUCR_WUPEN8)
  *    WUCR    WUPEN8       LL_PWR_DisableWakeUpPin
#endif
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t wakeup_pin)
{
  STM32_CLEAR_BIT(PWR->WUCR, wakeup_pin);
}

/**
  * @brief  Check if the wake up pin_x is enabled.
  * @rmtoll
  *    WUCR    WUPEN1       LL_PWR_IsEnabledWakeUpPin \n
  *    WUCR    WUPEN2       LL_PWR_IsEnabledWakeUpPin \n
  *    WUCR    WUPEN4       LL_PWR_IsEnabledWakeUpPin \n
  *    WUCR    WUPEN5       LL_PWR_IsEnabledWakeUpPin \n
  *    WUCR    WUPEN6       LL_PWR_IsEnabledWakeUpPin \n
  *    WUCR    WUPEN7       LL_PWR_IsEnabledWakeUpPin \n
#if defined(PWR_WUCR_WUPEN8)
  *    WUCR    WUPEN8       LL_PWR_IsEnabledWakeUpPin
#endif
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  * @retval 0 if the wake up pin is disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t wakeup_pin)
{
  return ((STM32_READ_BIT(PWR->WUCR, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the wake up pin polarity for the event detection.
  * @rmtoll
  *    WUCR          WUPP1       LL_PWR_SetWakeUpPinPolarity \n
  *    WUCR          WUPP2       LL_PWR_SetWakeUpPinPolarity \n
  *    WUCR          WUPP4       LL_PWR_SetWakeUpPinPolarity \n
  *    WUCR          WUPP5       LL_PWR_SetWakeUpPinPolarity \n
  *    WUCR          WUPP6       LL_PWR_SetWakeUpPinPolarity \n
  *    WUCR          WUPP7       LL_PWR_SetWakeUpPinPolarity \n
#if defined(PWR_WUCR_WUPP8)
  *    WUCR          WUPP8       LL_PWR_SetWakeUpPinPolarity
#endif
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_HIGH
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_LOW
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarity(uint32_t wakeup_pin, uint32_t polarity)
{
  STM32_MODIFY_REG(PWR->WUCR, (uint32_t)(PWR_WUCR_WUPP1 << STM32_POSITION_VAL(wakeup_pin)), \
                   (uint32_t)(polarity << (PWR_WUCR_WUPP1_Pos + STM32_POSITION_VAL(wakeup_pin))));
}

/**
  * @brief  Get the wake up pin polarity for the event detection.
  * @rmtoll
  *    WUCR          WUPP1       LL_PWR_GetWakeUpPinPolarity \n
  *    WUCR          WUPP2       LL_PWR_GetWakeUpPinPolarity \n
  *    WUCR          WUPP4       LL_PWR_GetWakeUpPinPolarity \n
  *    WUCR          WUPP5       LL_PWR_GetWakeUpPinPolarity \n
  *    WUCR          WUPP6       LL_PWR_GetWakeUpPinPolarity \n
  *    WUCR          WUPP7       LL_PWR_GetWakeUpPinPolarity \n
#if defined(PWR_WUCR_WUPP8)
  *    WUCR          WUPP8       LL_PWR_GetWakeUpPinPolarity
#endif
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  * @retval 0 if the wake up pin polarity is high, 1 if low.
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPolarity(uint32_t wakeup_pin)
{
  return ((STM32_READ_BIT(PWR->WUCR, (uint32_t)(PWR_WUCR_WUPP1 << STM32_POSITION_VAL(wakeup_pin))) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin pull.
  * @rmtoll
  *    WUCR   WUPPUPD1       LL_PWR_SetWakeUpPinPull \n
  *    WUCR   WUPPUPD2       LL_PWR_SetWakeUpPinPull \n
  *    WUCR   WUPPUPD4       LL_PWR_SetWakeUpPinPull \n
  *    WUCR   WUPPUPD5       LL_PWR_SetWakeUpPinPull \n
  *    WUCR   WUPPUPD6       LL_PWR_SetWakeUpPinPull \n
  *    WUCR   WUPPUPD7       LL_PWR_SetWakeUpPinPull \n
#if defined(PWR_WUCR_WUPEN8)
  *    WUCR   WUPPUPD8       LL_PWR_SetWakeUpPinPull
#endif
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  * @param  pull This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPull(uint32_t wakeup_pin, uint32_t pull)
{
  STM32_MODIFY_REG(PWR->WUCR, (PWR_WUCR_WUPPUPD1 << (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                     (STM32_POSITION_VAL(wakeup_pin)))), \
                   pull << (PWR_WUCR_WUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                     (STM32_POSITION_VAL(wakeup_pin)))));
}

/**
  * @brief  Get the Wake-Up pin pull.
  * @rmtoll
  *    WUCR   WUPPUPD1       LL_PWR_GetWakeUpPinPull \n
  *    WUCR   WUPPUPD2       LL_PWR_GetWakeUpPinPull \n
  *    WUCR   WUPPUPD4       LL_PWR_GetWakeUpPinPull \n
  *    WUCR   WUPPUPD5       LL_PWR_GetWakeUpPinPull \n
  *    WUCR   WUPPUPD6       LL_PWR_GetWakeUpPinPull \n
  *    WUCR   WUPPUPD7       LL_PWR_GetWakeUpPinPull \n
#if defined(PWR_WUCR_WUPEN8)
  *    WUCR   WUPPUPD8       LL_PWR_GetWakeUpPinPull
#endif
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPull(uint32_t wakeup_pin)
{
  uint32_t regValue = STM32_READ_BIT(PWR->WUCR, (PWR_WUCR_WUPPUPD1 << ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                                        (STM32_POSITION_VAL(wakeup_pin) & 0xFU)) & \
                                                                       LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));

  return (uint32_t)(regValue >> ((PWR_WUCR_WUPPUPD1_Pos + ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * \
                                                            STM32_POSITION_VAL(wakeup_pin)) & 0xFU)) & \
                                 LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));
}

/**
  * @brief  Enable IO Retention.
  * @rmtoll
  *    IORETR        IORETEN           LL_PWR_EnableIORetentionStandbyMode
  */
__STATIC_INLINE void LL_PWR_EnableIORetentionStandbyMode(void)
{
  STM32_SET_BIT(PWR->IORETR, PWR_IORETR_IORETEN);
}

/**
  * @brief  Disable IO Retention.
  * @rmtoll
  *    IORETR        IORETEN           LL_PWR_DisableIORetentionStandbyMode
  */
__STATIC_INLINE void LL_PWR_DisableIORetentionStandbyMode(void)
{
  STM32_CLEAR_BIT(PWR->IORETR, PWR_IORETR_IORETEN);
}

/**
  * @brief  Check if IO Retention is enabled.
  * @rmtoll
  *    IORETR        IORETEN           LL_PWR_IsEnabledIORetentionStandbyMode
  * @retval 0 if IO Retention is disabled, 1 if IO Retention is enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledIORetentionStandbyMode(void)
{
  return ((STM32_READ_BIT(PWR->IORETR, PWR_IORETR_IORETEN) == (PWR_IORETR_IORETEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable JTAGIO Retention.
  * @rmtoll
  *    IORETR    JTAGIORETEN       LL_PWR_EnableJTAGIORetentionStandbyMode
  */
__STATIC_INLINE void LL_PWR_EnableJTAGIORetentionStandbyMode(void)
{
  STM32_SET_BIT(PWR->IORETR, PWR_IORETR_JTAGIORETEN);
}

/**
  * @brief  Disable JTAGIO Retention.
  * @rmtoll
  *    IORETR     JTAGIORETEN      LL_PWR_DisableJTAGIORetentionStandbyMode
  */
__STATIC_INLINE void LL_PWR_DisableJTAGIORetentionStandbyMode(void)
{
  STM32_CLEAR_BIT(PWR->IORETR, PWR_IORETR_JTAGIORETEN);
}

/**
  * @brief  Check if JTAGIO Retention is enabled.
  * @rmtoll
  *    IORETR     JTAGIORETEN          LL_PWR_IsEnabledJTAGIORetentionStandbyMode
  * @retval 0 if JTAGIO Retention is disabled, 1 if JTAGIO Retention is enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledJTAGIORetentionStandbyMode(void)
{
  return ((STM32_READ_BIT(PWR->IORETR, PWR_IORETR_JTAGIORETEN) == (PWR_IORETR_JTAGIORETEN)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR FLAG Management
  * @{
  */

/**
  * @brief  Indicate whether the regulator voltage output is above voltage scaling range or not.
  * @rmtoll
  *    VOSSR          VOSRDY          LL_PWR_IsActiveFlag_VOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return ((STM32_READ_BIT(PWR->VOSSR, PWR_VOSSR_VOSRDY) == (PWR_VOSSR_VOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the system was in standby mode or not.
  * @rmtoll
  *    PMSR          SBF          LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((STM32_READ_BIT(PWR->PMSR, PWR_PMSR_SBF) == (PWR_PMSR_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the system was in stop mode or not.
  * @rmtoll
  *    PMSR          STOPF          LL_PWR_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((STM32_READ_BIT(PWR->PMSR, PWR_PMSR_STOPF) == (PWR_PMSR_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDD voltage is below the threshold or not.
  * @rmtoll
  *    VMSR          PVDO          LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((STM32_READ_BIT(PWR->VMSR, PWR_VMSR_PVDO) == (PWR_VMSR_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDD voltage is below the threshold or not.
  * @rmtoll
  *    VMSR          AVDO          LL_PWR_IsActiveFlag_AVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_AVDO(void)
{
  return ((STM32_READ_BIT(PWR->VMSR, PWR_VMSR_AVDO) == (PWR_VMSR_AVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the regulator voltage output is equal to current
  *         used voltage scaling range or not.
  * @rmtoll
  *    VOSSR          ACTVOSRDY          LL_PWR_IsActiveFlag_ACTVOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ACTVOS(void)
{
  return ((STM32_READ_BIT(PWR->VOSSR, PWR_VOSSR_ACTVOSRDY) == (PWR_VOSSR_ACTVOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VDD level is below high threshold or not.
  * @rmtoll
  *    TMSR   VDDH       LL_PWR_IsActiveFlag_VDDH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VDDH(void)
{
  return ((STM32_READ_BIT(PWR->TMSR, PWR_TMSR_VDDH) == (PWR_TMSR_VDDH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the CPU temperature level is above low threshold or not.
  * @rmtoll
  *    TMSR   TEMPL       LL_PWR_IsActiveFlag_TEMPL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((STM32_READ_BIT(PWR->TMSR, PWR_TMSR_TEMPL) == (PWR_TMSR_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the CPU temperature level is below high threshold.
  *         or not.
  * @rmtoll
  *    TMSR   TEMPH       LL_PWR_IsActiveFlag_TEMPH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((STM32_READ_BIT(PWR->TMSR, PWR_TMSR_TEMPH) == (PWR_TMSR_TEMPH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 1.
  * @rmtoll
  *    WUSR          WUF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((STM32_READ_BIT(PWR->WUSR, PWR_WUSR_WUF1) == (PWR_WUSR_WUF1)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 2.
  * @rmtoll
  *    WUSR          WUF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((STM32_READ_BIT(PWR->WUSR, PWR_WUSR_WUF2) == (PWR_WUSR_WUF2)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 4.
  * @rmtoll
  *    WUSR          WUF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((STM32_READ_BIT(PWR->WUSR, PWR_WUSR_WUF4) == (PWR_WUSR_WUF4)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 5.
  * @rmtoll
  *    WUSR          WUF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((STM32_READ_BIT(PWR->WUSR, PWR_WUSR_WUF5) == (PWR_WUSR_WUF5)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 6.
  * @rmtoll
  *    WUSR          WUF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((STM32_READ_BIT(PWR->WUSR, PWR_WUSR_WUF6) == (PWR_WUSR_WUF6)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 7.
  * @rmtoll
  *    WUSR          WUF7          LL_PWR_IsActiveFlag_WU7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((STM32_READ_BIT(PWR->WUSR, PWR_WUSR_WUF7) == (PWR_WUSR_WUF7)) ? 1UL : 0UL);
}

#if defined (PWR_WUSR_WUF8)
/**
  * @brief  Indicate whether a wakeup event is detected on wake up pin 8.
  * @rmtoll
  *    WUSR          WUF8          LL_PWR_IsActiveFlag_WU8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU8(void)
{
  return ((STM32_READ_BIT(PWR->WUSR, PWR_WUSR_WUF8) == (PWR_WUSR_WUF8)) ? 1UL : 0UL);
}
#endif /* PWR_WUSR_WUF8 */

/**
  * @brief  Clear stop flag.
  * @rmtoll
  *    LPMCR          CSSF          LL_PWR_ClearFlag_STOP
  * @warning STOPF and SBF flags are cleared together using this API.
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP(void)
{
  STM32_SET_BIT(PWR->LPMCR, PWR_LPMCR_CSSF);
}

/**
  * @brief  Clear standby flag.
  * @rmtoll
  *    LPMCR          CSSF          LL_PWR_ClearFlag_SB
  * @warning STOPF and SBF flags are cleared together using this API.
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  STM32_SET_BIT(PWR->LPMCR, PWR_LPMCR_CSSF);
}

/**
  * @brief  Clear wake up flag 1.
  * @rmtoll
  *    WUSCR          CWUF1         LL_PWR_ClearFlag_WU1
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU1(void)
{
  STM32_WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF1);
}

/**
  * @brief  Clear wake up flag 2.
  * @rmtoll
  *    WUSCR          CWUF2         LL_PWR_ClearFlag_WU2
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU2(void)
{
  STM32_WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF2);
}

/**
  * @brief  Clear wake up flag 4.
  * @rmtoll
  *    WUSCR          CWUF4         LL_PWR_ClearFlag_WU4
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU4(void)
{
  STM32_WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF4);
}

/**
  * @brief  Clear wake up flag 5.
  * @rmtoll
  *    WUSCR          CWUF5         LL_PWR_ClearFlag_WU5
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU5(void)
{
  STM32_WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF5);
}

/**
  * @brief  Clear wake up flag 6.
  * @rmtoll
  *    WUSCR          CWUF6         LL_PWR_ClearFlag_WU6
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU6(void)
{
  STM32_WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF6);
}

/**
  * @brief  Clear wake up flag 7.
  * @rmtoll
  *    WUSCR          CWUF7         LL_PWR_ClearFlag_WU7
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU7(void)
{
  STM32_WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF7);
}

#if defined (PWR_WUSCR_CWUF8)
/**
  * @brief  Clear wake up flag 8.
  * @rmtoll
  *    WUSCR          CWUF8         LL_PWR_ClearFlag_WU8
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU8(void)
{
  STM32_WRITE_REG(PWR->WUSCR, PWR_WUSCR_CWUF8);
}
#endif /* PWR_WUSCR_CWUF8 */

/**
  * @brief  Clear the wake up flag(s).
  * @rmtoll
  *    WUSCR          CWUFx         LL_PWR_ClearFlag_WU
  * @param  wakeup_pin
  *         This parameter can be one or a combination of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
#if defined (PWR_WUSCR_CWUF8)
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
#endif
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(uint32_t wakeup_pin)
{
  STM32_WRITE_REG(PWR->WUSCR, wakeup_pin);
}
/**
  * @}
  */

/** @defgroup PWR_LL_EF_ATTRIBUTE_MANAGEMENT PWR Attribute Management
  * @{
  */

/**
  * @brief  Set the privilege attribute.
  * @rmtoll
  *  PRIVCFGR     PRIV        LL_PWR_SetPrivAttr
  * @param  item This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PRIV_ITEM_SPRIV
  *         @arg @ref LL_PWR_PRIV_ITEM_NSPRIV
  *         @arg @ref LL_PWR_PRIV_ITEM_ALL
  * @param  priv_attr This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ATTR_NPRIV
  *         @arg @ref LL_PWR_ATTR_PRIV
  * @note  This register can be written only when the access is privileged.
  */
__STATIC_INLINE void LL_PWR_SetPrivAttr(uint32_t item, uint32_t priv_attr)
{
  STM32_MODIFY_REG(PWR->PRIVCFGR, item, (item * priv_attr));
}

/**
  * @brief  Get the privilege attribute.
  * @rmtoll
  *  PRIVCFGR     PRIV        LL_PWR_GetPrivAttr
  * @param  item This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PRIV_ITEM_SPRIV
  *         @arg @ref LL_PWR_PRIV_ITEM_NSPRIV
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ATTR_NPRIV
  *         @arg @ref LL_PWR_ATTR_PRIV
  */
__STATIC_INLINE uint32_t LL_PWR_GetPrivAttr(uint32_t item)
{
  return ((STM32_READ_BIT(PWR->PRIVCFGR, item) == item) ? 1UL : 0UL);
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Configure secure attribute mode.
  * @rmtoll
  *    SECCFGR     WUP1SEC       LL_PWR_SetSecAttr \n
  *    SECCFGR     WUP2SEC       LL_PWR_SetSecAttr \n
  *    SECCFGR     WUP4SEC       LL_PWR_SetSecAttr \n
  *    SECCFGR     WUP5SEC       LL_PWR_SetSecAttr \n
  *    SECCFGR     WUP6SEC       LL_PWR_SetSecAttr \n
  *    SECCFGR     WUP7SEC       LL_PWR_SetSecAttr \n
#if defined(PWR_WUCR_WUPEN8)
  *    SECCFGR     WUP8SEC       LL_PWR_SetSecAttr \n
#endif
  *    SECCFGR     RETSEC        LL_PWR_SetSecAttr \n
  *    SECCFGR     LPMSEC        LL_PWR_SetSecAttr \n
  *    SECCFGR     VDMSEC        LL_PWR_SetSecAttr \n
  *    SECCFGR     VBSEC         LL_PWR_SetSecAttr \n
  *    SECCFGR     VUSBSEC       LL_PWR_SetSecAttr
  * @param  item This parameter can be the full combination of the following values:
  *         @arg @ref LL_PWR_SEC_ITEM_WUP1SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP2SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP4SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP5SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP6SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP7SEC
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_SEC_ITEM_WUP8SEC
#endif
  *         @arg @ref LL_PWR_SEC_ITEM_RETSEC
  *         @arg @ref LL_PWR_SEC_ITEM_LPMSEC
  *         @arg @ref LL_PWR_SEC_ITEM_SCMSEC
  *         @arg @ref LL_PWR_SEC_ITEM_RTCSEC
#if defined(PWR_USBSCR_USB33SV)
  *         @arg @ref LL_PWR_SEC_ITEM_VUSBSEC
#endif
  *         @arg @ref LL_PWR_SEC_ITEM_ALL
  * @param  sec_attr This parameter can be one of the following values:
  *         @arg @ref LL_PWR_ATTR_NSEC
  *         @arg @ref LL_PWR_ATTR_SEC
  * @note   This API can be executed only by CPU in secure mode.
  * @note   The register is write-protected against unprivileged write accesses when SPRIV = 1 in the PWR_PRIVCFGR.
  */
__STATIC_INLINE void LL_PWR_SetSecAttr(uint32_t item, uint32_t sec_attr)
{
  STM32_MODIFY_REG(PWR->SECCFGR, item, (item * sec_attr));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get secure attribute for the selected item.
  * @rmtoll
  *    SECCFGR     WUP1SEC       LL_PWR_GetSecAttr \n
  *    SECCFGR     WUP2SEC       LL_PWR_GetSecAttr \n
  *    SECCFGR     WUP4SEC       LL_PWR_GetSecAttr \n
  *    SECCFGR     WUP5SEC       LL_PWR_GetSecAttr \n
  *    SECCFGR     WUP6SEC       LL_PWR_GetSecAttr \n
  *    SECCFGR     WUP7SEC       LL_PWR_GetSecAttr \n
#if defined(PWR_WUCR_WUPEN8)
  *    SECCFGR     WUP8SEC       LL_PWR_GetSecAttr \n
#endif
  *    SECCFGR     RETSEC        LL_PWR_GetSecAttr \n
  *    SECCFGR     LPMSEC        LL_PWR_GetSecAttr \n
  *    SECCFGR     VDMSEC        LL_PWR_GetSecAttr \n
  *    SECCFGR     VBSEC         LL_PWR_GetSecAttr \n
#if defined(PWR_USBSCR_USB33SV)
  *    SECCFGR     VUSBSEC       LL_PWR_GetSecAttr
#endif
  * @param  item This parameter can be one of the following values:
  *         @arg @ref LL_PWR_SEC_ITEM_WUP1SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP2SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP4SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP5SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP6SEC
  *         @arg @ref LL_PWR_SEC_ITEM_WUP7SEC
#if defined(PWR_WUCR_WUPEN8)
  *         @arg @ref LL_PWR_SEC_ITEM_WUP8SEC
#endif
  *         @arg @ref LL_PWR_SEC_ITEM_RETSEC
  *         @arg @ref LL_PWR_SEC_ITEM_LPMSEC
  *         @arg @ref LL_PWR_SEC_ITEM_SCMSEC
  *         @arg @ref LL_PWR_SEC_ITEM_RTCSEC
#if defined(PWR_USBSCR_USB33SV)
  *         @arg @ref LL_PWR_SEC_ITEM_VUSBSEC
#endif
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ATTR_NSEC
  *         @arg @ref LL_PWR_ATTR_SEC
  */
__STATIC_INLINE uint32_t LL_PWR_GetSecAttr(uint32_t item)
{
  return ((STM32_READ_BIT(PWR->SECCFGR, item) == item) ? 1UL : 0UL);
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

#endif /* defined (PWR) */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_LL_PWR_H */
