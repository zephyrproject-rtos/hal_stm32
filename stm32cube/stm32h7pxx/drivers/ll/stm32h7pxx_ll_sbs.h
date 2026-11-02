/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_ll_sbs.h
  * @brief   Header file of LL SBS module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software
  * component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_LL_SBS_H
#define STM32H7PXX_LL_SBS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

#if defined (SBS)
/** @defgroup LL_SBS LL SBS
  * @{
  */

/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_LL_Private_Constants LL SBS private constants
  * @{
  */
#define LL_SBS_HDPL_INCREMENT_VALUE   0x6AU                                /*!< Define used for the HDPL increment */
#define LL_SBS_DBG_LOCK               0x00U                                /*!< Define used to lock debug */
#define LL_SBS_DBG_UNLOCK             (0xB4UL << SBS_DBGCR_DBG_UNLOCK_Pos) /*!< Define used to unlock debug */
#define LL_SBS_ACCESS_PORT_LOCK       0x00U                                /*!< Define used to lock access port */
#define LL_SBS_ACCESS_PORT_UNLOCK     0xB4U                                /*!< Define used to unlock access port */
#define LL_SBS_DBG_CONFIG_LOCK        0xC3U                                /*!< Define used to lock debug configuration */
#define LL_SBS_DBG_CONFIG_UNLOCK      0xB4U                                /*!< Define used to unlock debug configuration */

#define LL_SBS_EXTI_CR_REGISTER_SHIFT 8U
#define LL_SBS_EXTI_CR1               (0x00U << LL_SBS_EXTI_CR_REGISTER_SHIFT)
#define LL_SBS_EXTI_CR2               (0x01UL << LL_SBS_EXTI_CR_REGISTER_SHIFT)
#define LL_SBS_EXTI_CR3               (0x02UL << LL_SBS_EXTI_CR_REGISTER_SHIFT)
#define LL_SBS_EXTI_CR4               (0x03UL << LL_SBS_EXTI_CR_REGISTER_SHIFT)
/**
  * @}
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_LL_Exported_Constants LL SBS Constants
  * @{
  */

/** @defgroup LL_SBS_HDPL_Value SBS HDPL value
  * @{
  */
#define LL_SBS_HDPL_VALUE_0 0x000000B4U /*!< Hide protection level 0 */
#define LL_SBS_HDPL_VALUE_1 0x00000051U /*!< Hide protection level 1 */
#define LL_SBS_HDPL_VALUE_2 0x0000008AU /*!< Hide protection level 2 */
#define LL_SBS_HDPL_VALUE_3 0x0000006FU /*!< Hide protection level 3 */
/**
  * @}
  */

/** @defgroup LL_SBS_IO_Analog_Switch_Value SBS IO analog switch value
  * @{
  */
#define LL_SBS_VDDA_SUPPLY    0x0U                 /*!< Select VDDA as analog switch supply    */
#define LL_SBS_BOOSTER_SUPPLY SBS_PMCR_BOOSTEN     /*!< Select booster as analog switch supply */
#define LL_SBS_VDD_SUPPLY     SBS_PMCR_BOOSTVDDSEL /*!< Select VDD as analog switch supply     */
/**
  * @}
  */

/** @defgroup LL_SBS_Floating_Point_Unit_Interrupts SBS floating point unit interrupts
  * @{
  */
#define LL_SBS_IT_FPU_IOC SBS_FPUIMR_FPU_IE_0                           /*!< Invalid operation interrupt        */
#define LL_SBS_IT_FPU_DZC SBS_FPUIMR_FPU_IE_1                           /*!< Divide-by-zero interrupt           */
#define LL_SBS_IT_FPU_UFC SBS_FPUIMR_FPU_IE_2                           /*!< underflow interrupt                */
#define LL_SBS_IT_FPU_OFC SBS_FPUIMR_FPU_IE_3                           /*!< Overflow interrupt                 */
#define LL_SBS_IT_FPU_IDC SBS_FPUIMR_FPU_IE_4                           /*!< Input abnormal interrupt           */
#define LL_SBS_IT_FPU_IXC SBS_FPUIMR_FPU_IE_5                           /*!< Inexact interrupt                  */
#define LL_SBS_IT_FPU_ALL (SBS_FPUIMR_FPU_IE_0 | SBS_FPUIMR_FPU_IE_1   \
                           | SBS_FPUIMR_FPU_IE_2 | SBS_FPUIMR_FPU_IE_3 \
                           | SBS_FPUIMR_FPU_IE_4 | SBS_FPUIMR_FPU_IE_5) /*!< All floating point unit interrupts */
/**
  * @}
  */

/** @defgroup LL_SBS_Erase_Status_Flags SBS erase status flags
  * @{
  */
#define LL_SBS_FLAG_BKPMEF  SBS_MESR_BKPMEF                      /*!< PKPSRAM erase status flag  */
#define LL_SBS_FLAG_AXIRMEF SBS_MESR_AXIRMEF                     /*!< AXISRAM1 erase status flag */
/**
  * @}
  */

/** @defgroup LL_SBS_Compensation_Cell_Code_Source SBS compensation cell Code source
  * @{
  */
#define LL_SBS_CCELL_VDDIO SBS_CCCSR_COMP_EN /*!< Compensation cell selection for VDDIO */

#define LL_SBS_CCELL_CODE_DEFAULT 0U /*!< I/Os code from the cell (available in the SBS_CCVALR)                 */
#define LL_SBS_CCELL_CODE_CUSTOM  1U /*!< I/Os code from the SBS compensation cell code register (SBS_CCSWVALR) */
/**
  * @}
  */

/** @defgroup LL_SBS_VDDIO_Compensation_Cell_Code_Selection SBS VDDIO compensation cell Code selection
  * @{
  */
#define LL_SBS_CCELL_VDDIO_DEFAULT_CODE 0U                     /*!< VDD I/Os code from the cell (available in the SBS_CCVALR)                 */
#define LL_SBS_CCELL_VDDIO_CUSTOM_CODE  SBS_CCCSR_COMP_CODESEL /*!< VDD I/Os code from the SBS compensation cell code register (SBS_CCSWVALR) */
/**
  * @}
  */

/** @defgroup LL_SBS_Timer_Break_Input SBS timer break input
  * @{
  */
#define LL_SBS_SRAM1_ECC_DOUBLE_ERROR  SBS_BKLOCKR_ARAM1ECC_BL  /*!< Enables and locks the AXISRAM1 ECC double error signal with Break Input of TIM1/8/15/16/17/20                                          */
#define LL_SBS_SRAM2_ECC_DOUBLE_ERROR  SBS_BKLOCKR_ARAM2ECC_BL  /*!< Enables and locks the AXISRAM2 ECC double error signal with Break Input of TIM1/8/15/16/17/20                                          */
#define LL_SBS_SRAM3_ECC_DOUBLE_ERROR  SBS_BKLOCKR_ARAM3ECC_BL  /*!< Enables and locks the AXISRAM3 ECC double error signal with Break Input of TIM1/8/15/16/17/20                                          */
#define LL_SBS_SRAM4_ECC_DOUBLE_ERROR  SBS_BKLOCKR_ARAM4ECC_BL  /*!< Enables and locks the AXISRAM4 ECC double error signal with Break Input of TIM1/8/15/16/17/20                                          */
#define LL_SBS_ITCM_ECC_DOUBLE_ERROR   SBS_BKLOCKR_ITCMECC_BL   /*!< Enables and locks the ITCM ECC double error signal with Break Input of TIM1/8/15/16/17/20                                              */
#define LL_SBS_DTCM_ECC_DOUBLE_ERROR   SBS_BKLOCKR_DTCMECC_BL   /*!< Enables and locks the DTCM ECC double error signal with Break Input of TIM1/8/15/16/17/20                                              */
#define LL_SBS_BKPRAM_ECC_DOUBLE_ERROR SBS_BKLOCKR_BKRAMECC_BL  /*!< Enables and locks the Backup SRAM ECC double error signal with Break Input of TIM1/8/15/16/17/20                                       */
#define LL_SBS_LOCKUP_OUT              SBS_BKLOCKR_CM7LCKUP_BL  /*!< Enables and locks the LOCKUP (Hardfault) output of Cortex-M7 with Break Input of TIM1/15/16/17/20                                      */
#define LL_SBS_FLASH_ECC_DOUBLE_ERROR  SBS_BKLOCKR_FLASHECC_BL  /*!< Enables and locks the FLASH ECC double error signal with Break Input of TIM1/8/15/16/17/20                                             */
#define LL_SBS_PVD                     SBS_BKLOCKR_PVD_BL       /*!< Enables and locks the PVD connection with TIM1/8/15/16/17/20 Break Input and also the PVDE and PLS bits of the Power Control Interface */
#define LL_SBS_TIM_BREAK_INPUTS_ALL    (SBS_BKLOCKR_PVD_BL  | SBS_BKLOCKR_FLASHECC_BL | SBS_BKLOCKR_CM7LCKUP_BL | \
                                        SBS_BKLOCKR_BKRAMECC_BL | SBS_BKLOCKR_DTCMECC_BL | SBS_BKLOCKR_ITCMECC_BL | \
                                        SBS_BKLOCKR_ARAM4ECC_BL | SBS_BKLOCKR_ARAM3ECC_BL |  SBS_BKLOCKR_ARAM2ECC_BL | \
                                        SBS_BKLOCKR_ARAM1ECC_BL) /*!< Enables and locks the all with Break Input */
/**
  * @}
  */

/** @defgroup LL_SBS_EXTI_GPIO_ort SBS EXTI GPIO port
  * @{
  */
#define LL_SBS_EXTI_GPIO_PORTA 0U                                                                         /*!< EXTI PORT A */
#define LL_SBS_EXTI_GPIO_PORTB SBS_EXTICR1_PC_EXTI0_0                                                     /*!< EXTI PORT B */
#define LL_SBS_EXTI_GPIO_PORTC SBS_EXTICR1_PC_EXTI0_1                                                     /*!< EXTI PORT C */
#define LL_SBS_EXTI_GPIO_PORTD (SBS_EXTICR1_PC_EXTI0_1 | SBS_EXTICR1_PC_EXTI0_0)                          /*!< EXTI PORT D */
#define LL_SBS_EXTI_GPIO_PORTE SBS_EXTICR1_PC_EXTI0_2                                                     /*!< EXTI PORT E */
#define LL_SBS_EXTI_GPIO_PORTF (SBS_EXTICR1_PC_EXTI0_2 | SBS_EXTICR1_PC_EXTI0_0)                          /*!< EXTI PORT F */
#define LL_SBS_EXTI_GPIO_PORTG (SBS_EXTICR1_PC_EXTI0_2 | SBS_EXTICR1_PC_EXTI0_1)                          /*!< EXTI PORT G */
#define LL_SBS_EXTI_GPIO_PORTH (SBS_EXTICR1_PC_EXTI0_2 | SBS_EXTICR1_PC_EXTI0_1 | SBS_EXTICR1_PC_EXTI0_0) /*!< EXTI PORT H */
#define LL_SBS_EXTI_GPIO_PORTI (SBS_EXTICR1_PC_EXTI0_3)                                                   /*!< EXTI PORT I */
/**
  * @}
  */

/** @defgroup LL_SBS_EXTI_GPIO_Line SBS EXTI GPIO line
  * @{
  */
#define LL_SBS_EXTI_GPIO_LINE0  (LL_SBS_EXTI_CR1 | 0x00U) /*!< EXTI GPIO Line 0 */
#define LL_SBS_EXTI_GPIO_LINE1  (LL_SBS_EXTI_CR1 | 0x01U) /*!< EXTI GPIO Line 1 */
#define LL_SBS_EXTI_GPIO_LINE2  (LL_SBS_EXTI_CR1 | 0x02U) /*!< EXTI GPIO Line 2 */
#define LL_SBS_EXTI_GPIO_LINE3  (LL_SBS_EXTI_CR1 | 0x03U) /*!< EXTI GPIO Line 3 */
#define LL_SBS_EXTI_GPIO_LINE4  (LL_SBS_EXTI_CR2 | 0x04U) /*!< EXTI GPIO Line 4 */
#define LL_SBS_EXTI_GPIO_LINE5  (LL_SBS_EXTI_CR2 | 0x05U) /*!< EXTI GPIO Line 5 */
#define LL_SBS_EXTI_GPIO_LINE6  (LL_SBS_EXTI_CR2 | 0x06U) /*!< EXTI GPIO Line 6 */
#define LL_SBS_EXTI_GPIO_LINE7  (LL_SBS_EXTI_CR2 | 0x07U) /*!< EXTI GPIO Line 7 */
#define LL_SBS_EXTI_GPIO_LINE8  (LL_SBS_EXTI_CR3 | 0x08U) /*!< EXTI GPIO Line 8 */
#define LL_SBS_EXTI_GPIO_LINE9  (LL_SBS_EXTI_CR3 | 0x09U) /*!< EXTI GPIO Line 9 */
#define LL_SBS_EXTI_GPIO_LINE10 (LL_SBS_EXTI_CR3 | 0x0AU) /*!< EXTI GPIO Line 10 */
#define LL_SBS_EXTI_GPIO_LINE11 (LL_SBS_EXTI_CR3 | 0x0BU) /*!< EXTI GPIO Line 11 */
#define LL_SBS_EXTI_GPIO_LINE12 (LL_SBS_EXTI_CR4 | 0x0CU) /*!< EXTI GPIO Line 12 */
#define LL_SBS_EXTI_GPIO_LINE13 (LL_SBS_EXTI_CR4 | 0x0DU) /*!< EXTI GPIO Line 13 */
#define LL_SBS_EXTI_GPIO_LINE14 (LL_SBS_EXTI_CR4 | 0x0EU) /*!< EXTI GPIO Line 14 */
#define LL_SBS_EXTI_GPIO_LINE15 (LL_SBS_EXTI_CR4 | 0x0FU) /*!< EXTI GPIO Line 15 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_LL_Exported_Macros LL SBS Macros
  * @{
  */

/** @defgroup SBS_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in SBS register.
  * @param  reg Register to be written
  * @param  value Value to be written in the register
  */
#define LL_SBS_WRITE_REG(reg, value) STM32_WRITE_REG(SBS->reg, (value))

/**
  * @brief  Read a value in SBS register.
  * @param  reg Register to be read
  * @retval Register value
  */
#define LL_SBS_READ_REG(reg) STM32_READ_REG(SBS->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup SBS_LL_Exported_Functions LL SBS Functions
  * @{
  */

/** @defgroup LL_SBS_EF_Boot_address Boot Address
  * @{
  */

/**
  * @brief  Get the initial VTOR after reset.
  * @rmtoll
  *  BOOTSR     INITVTOR      LL_SBS_GetBootAddress
  * @retval Return the initial VTOR for cortex M7
  */
__STATIC_INLINE uint32_t LL_SBS_GetBootAddress(void)
{
  return (uint32_t)(STM32_READ_REG(SBS->BOOTSR));
}

/**
  * @}
  */

/** @defgroup SBS_HDPL_Management SBS HDPL Management
  * @{
  */

/**
  * @brief  Increment by 1 the HDPL value.
  * @rmtoll
  *  HDPLCR     INCR_HDPL      LL_SBS_IncrementHDPLLevel
  */
__STATIC_INLINE void LL_SBS_IncrementHDPLevel(void)
{
  STM32_MODIFY_REG(SBS->HDPLCR, SBS_HDPLCR_INCR_HDPL, LL_SBS_HDPL_INCREMENT_VALUE);
}

/**
  * @brief  Get the HDPL Value.
  * @rmtoll
  *  HDPLSR     HDPL      LL_SBS_GetHDPLevel
  * @retval  Returns the HDPL value
  *          This return value can be one of the following values:
  *           @arg @ref LL_SBS_HDPL_VALUE_0: HDPL0
  *           @arg @ref LL_SBS_HDPL_VALUE_1: HDPL1
  *           @arg @ref LL_SBS_HDPL_VALUE_2: HDPL2
  *           @arg @ref LL_SBS_HDPL_VALUE_3: HDPL3
  */
__STATIC_INLINE uint32_t LL_SBS_GetHDPLevel(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->HDPLSR, SBS_HDPLSR_HDPL));
}

/**
  * @}
  */

/** @defgroup SBS_Debug_Control SBS Debug Control
  * @{
  */

/**
  * @brief  Set the authenticated debug hide protection level.
  * @rmtoll
  *  DBGCR     DBG_AUTH_HDPL     LL_SBS_SetAuthenticatedDbgHDPLevel
  * @param  Level This parameter can be one of the following values:
  *         @arg @ref LL_SBS_HDPL_VALUE_1
  *         @arg @ref LL_SBS_HDPL_VALUE_2
  *         @arg @ref LL_SBS_HDPL_VALUE_3
  */
__STATIC_INLINE void LL_SBS_SetAuthenticatedDbgHDPLevel(uint32_t Level)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_HDPL, (Level << SBS_DBGCR_DBG_AUTH_HDPL_Pos));
}

/**
  * @brief  Get current hide protection level.
  * @rmtoll
  *  DBGCR     DBG_AUTH_HDPL     LL_SBS_GetAuthenticatedDbgHDPLevel
  * @retval Returned value is the hide protection level where the authenticated debug is opened:
  *         @arg @ref LL_SBS_HDPL_VALUE_1
  *         @arg @ref LL_SBS_HDPL_VALUE_2
  *         @arg @ref LL_SBS_HDPL_VALUE_3
  */
__STATIC_INLINE uint32_t LL_SBS_GetAuthenticatedDbgHDPLevel(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_HDPL) >> SBS_DBGCR_DBG_AUTH_HDPL_Pos);
}

/**
  * @brief  Lock the debug.
  * @rmtoll
  *  DBGCR     DBG_UNLOCK     LL_SBS_LockDebug
  */
__STATIC_INLINE void LL_SBS_LockDebug(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK, LL_SBS_DBG_LOCK);
}

/**
  * @brief  Unlock the debug.
  * @rmtoll
  *  DBGCR     DBG_UNLOCK     LL_SBS_UnlockDebug
  */
__STATIC_INLINE void LL_SBS_UnlockDebug(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK, LL_SBS_DBG_UNLOCK);
}

/**
  * @brief  Check if the debug is unlocked.
  * @rmtoll
  *  DBGCR     DBG_UNLOCK     LL_SBS_IsLockedDebug
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedDebug(void)
{
  return ((STM32_READ_BIT(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK) == LL_SBS_DBG_UNLOCK) ? 0UL : 1UL);
}

/**
  * @brief  Lock the access port.
  * @rmtoll
  *  DBGCR     AP_UNLOCK     LL_SBS_LockAPBAHBAccessPorts
  */
__STATIC_INLINE void LL_SBS_LockAPBAHBAccessPorts(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK, LL_SBS_ACCESS_PORT_LOCK);
}

/**
  * @brief  Unlock the access port.
  * @rmtoll
  *  DBGCR     AP_UNLOCK     LL_SBS_UnlockAPBAHBAccessPorts
  */
__STATIC_INLINE void LL_SBS_UnlockAPBAHBAccessPorts(void)
{
  STM32_MODIFY_REG(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK, LL_SBS_ACCESS_PORT_UNLOCK);
}

/**
  * @brief  Check if the access port is unlocked.
  * @rmtoll
  *  DBGCR     AP_UNLOCK     LL_SBS_IsLockedAPBAHBAccessPorts
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedAPBAHBAccessPorts(void)
{
  return ((STM32_READ_BIT(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK) == LL_SBS_ACCESS_PORT_UNLOCK) ? 0UL : 1UL);
}

/**
  * @brief  Lock the debug configuration.
  * @rmtoll
  *  DBGLOCKR     DBGCFG_LOCK     LL_SBS_LockDebugConfig
  */
__STATIC_INLINE void LL_SBS_LockDebugConfig(void)
{
  STM32_MODIFY_REG(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK, LL_SBS_DBG_CONFIG_LOCK);
}

/**
  * @brief  Check if the debug is unlocked.
  * @rmtoll
  *  DBGLOCKR     DBGCFG_LOCK     LL_SBS_IsLockedDebugConfig
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsLockedDebugConfig(void)
{
  return ((STM32_READ_BIT(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK) != LL_SBS_DBG_CONFIG_UNLOCK) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_RSS_COMMAND SBS RSS COMMAND
  * @{
  */

/**
  * @brief  Set the RSS command.
  * @rmtoll
  *  RSSCMDR      RSSCMD      LL_SBS_SetRSSCommand
  * @param  rss_command
  */
__STATIC_INLINE void LL_SBS_SetRSSCommand(uint32_t rss_command)
{
  STM32_MODIFY_REG(SBS->RSSCMDR, SBS_RSSCMDR_RSSCMD, rss_command);
}

/**
  * @brief  Get the RSS command.
  * @rmtoll
  *  RSSCMDR      RSSCMD      LL_SBS_GetRSSCommand
  * @retval Returned the RSS command
  */
__STATIC_INLINE uint32_t LL_SBS_GetRSSCommand(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->RSSCMDR, SBS_RSSCMDR_RSSCMD));
}

/**
  * @}
  */

/** @defgroup SBS_IO_Analog_Switch_Supply SBS IO analog switch supply
  * @{
  */

/**
  * @brief  Set the analog switch supply.
  * @rmtoll
  *  PMCR   BOOSTVDDSEL    LL_SBS_SetAnalogIOSwitchSupply \n
  *  PMCR   BOOSTEN        LL_SBS_SetAnalogIOSwitchSupply
  * @param  analog_supply This parameter can be one of the following values:
  *         @arg LL_SYSTEM_SBS_VDDA_SUPPLY : Set VDDA analog supply
  *         @arg LL_SYSTEM_SBS_BOOSTER_SUPPLY: Set Booster analog supply
  *         @arg LL_SYSTEM_SBS_VDD_SUPPLY: Set VDD analog supply
  */
__STATIC_INLINE void LL_SBS_SetAnalogIOSwitchSupply(uint32_t analog_supply)
{
  STM32_MODIFY_REG(SBS->PMCR, SBS_PMCR_BOOSTEN | SBS_PMCR_BOOSTVDDSEL, analog_supply);
}

/**
  * @brief  Get the analog switch supply.
  * @rmtoll
  *  PMCR   BOOSTVDDSEL    LL_SBS_GetAnalogIOSwitchSupply \n
  *  PMCR   BOOSTEN        LL_SBS_GetAnalogIOSwitchSupply
  * @retval Returned value can be one of the following values:
  *         @arg LL_SYSTEM_SBS_VDDA_SUPPLY : Set VDDA analog supply
  *         @arg LL_SYSTEM_SBS_BOOSTER_SUPPLY: Set Booster analog supply
  *         @arg LL_SYSTEM_SBS_VDD_SUPPLY: Set VDD analog supply
  */
__STATIC_INLINE uint32_t LL_SBS_GetAnalogIOSwitchSupply(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->PMCR, (SBS_PMCR_BOOSTEN | SBS_PMCR_BOOSTVDDSEL)));
}

/**
  * @}
  */

/** @defgroup SBS_FPUIT_Management SBS FPUIT Management
  * @{
  */

/**
  * @brief  Enable floating point unit interrupts bits.
  * @rmtoll
  *  FPUIMR FPU_IE_0   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_1   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_2   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_3   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_4   LL_SBS_EnableFPUIT \n
  *  FPUIMR FPU_IE_5   LL_SBS_EnableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  *         @arg @ref LL_SBS_IT_FPU_ALL
  */
__STATIC_INLINE void LL_SBS_EnableFPUIT(uint32_t floating_point)
{
  STM32_SET_BIT(SBS->FPUIMR, floating_point);
}

/**
  * @brief  Disable floating point unit interrupts bits.
  * @rmtoll
  *  FPUIMR FPU_IE_0   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_1   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_2   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_3   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_4   LL_SBS_DisableFPUIT \n
  *  FPUIMR FPU_IE_5   LL_SBS_DisableFPUIT
  * @param  floating_point This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  *         @arg @ref LL_SBS_IT_FPU_ALL
  */
__STATIC_INLINE void LL_SBS_DisableFPUIT(uint32_t floating_point)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, floating_point);
}

/**
  * @brief  Check if floating point unit interrupts bits is enabled.
  * @rmtoll
  *  FPUIMR FPU_IE_0   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_1   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_2   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_3   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_4   LL_SBS_IsEnabledFPUIT \n
  *  FPUIMR FPU_IE_5   LL_SBS_IsEnabledFPUIT
  * @param  capacitance This parameter can be one of the following values:
  *         @arg @ref LL_SBS_IT_FPU_IOC
  *         @arg @ref LL_SBS_IT_FPU_DZC
  *         @arg @ref LL_SBS_IT_FPU_UFC
  *         @arg @ref LL_SBS_IT_FPU_OFC
  *         @arg @ref LL_SBS_IT_FPU_IDC
  *         @arg @ref LL_SBS_IT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledFPUIT(uint32_t floating_point)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, floating_point) == floating_point) ? 1UL : 0UL);
}

/**
  * @brief  Enable Floating Point Unit Invalid operation Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_EnableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IOC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Enable Floating Point Unit Divide-by-zero Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_1      LL_SBS_EnableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_DZC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Enable Floating Point Unit Underflow Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_EnableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_UFC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Enable Floating Point Unit Overflow Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_EnableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_OFC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Enable Floating Point Unit Input denormal Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_EnableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IDC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Enable Floating Point Unit Inexact Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_EnableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SBS_EnableIT_FPU_IXC(void)
{
  STM32_SET_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Disable Floating Point Unit Invalid operation Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_DisableIT_FPU_IOC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IOC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0);
}

/**
  * @brief  Disable Floating Point Unit Divide-by-zero Interrupt.
  * @rmtoll
  *  FPUIMR      FPU_IE_1      LL_SBS_DisableIT_FPU_DZC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_DZC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1);
}

/**
  * @brief  Disable Floating Point Unit Underflow Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_DisableIT_FPU_UFC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_UFC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2);
}

/**
  * @brief  Disable Floating Point Unit Overflow Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_DisableIT_FPU_OFC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_OFC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3);
}

/**
  * @brief  Disable Floating Point Unit Input denormal Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_DisableIT_FPU_IDC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IDC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4);
}

/**
  * @brief  Disable Floating Point Unit Inexact Interrupt.
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_DisableIT_FPU_IXC
  */
__STATIC_INLINE void LL_SBS_DisableIT_FPU_IXC(void)
{
  STM32_CLEAR_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5);
}

/**
  * @brief  Check if Floating Point Unit Invalid operation Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_0      LL_SBS_IsEnabledIT_FPU_IOC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IOC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_0) == SBS_FPUIMR_FPU_IE_0) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Divide-by-zero Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_1      LL_SBS_IsEnabledIT_FPU_DZC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_DZC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_1) == SBS_FPUIMR_FPU_IE_1) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Underflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_2      LL_SBS_IsEnabledIT_FPU_UFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_UFC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_2) == SBS_FPUIMR_FPU_IE_2) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Overflow Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_3      LL_SBS_IsEnabledIT_FPU_OFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_OFC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_3) == SBS_FPUIMR_FPU_IE_3) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Input denormal Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_4      LL_SBS_IsEnabledIT_FPU_IDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IDC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_4) == SBS_FPUIMR_FPU_IE_4) ? 1UL : 0UL);
}

/**
  * @brief  Check if Floating Point Unit Inexact Interrupt source is enabled or disabled.
  * @rmtoll
  *  FPUIMR     FPU_IE_5      LL_SBS_IsEnabledIT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIT_FPU_IXC(void)
{
  return ((STM32_READ_BIT(SBS->FPUIMR, SBS_FPUIMR_FPU_IE_5) == SBS_FPUIMR_FPU_IE_5) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_Erase_Memorie_Status SBS erase memorie status
  * @{
  */

/**
  * @brief  Get Status of End of Erase after reset for Backup SRAM.
  * @rmtoll
  *  MESR   BKPMEF    LL_SBS_IsActiveFlag_BKPMEF
  * @retval retrieve the state of the IPMEE flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_BKPMEF(void)
{
  return ((STM32_READ_BIT(SBS->MESR, SBS_MESR_BKPMEF) == SBS_MESR_BKPMEF) ? 1UL : 0UL);
}

/**
  * @brief  Get Status of End of Erase after reset for AXISRAM1.
  * @rmtoll
  *  MESR   AXIRMEF    LL_SBS_IsActiveFlag_AXIRMEF
  * @retval retrieve the state of the IPMEE flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_AXIRMEF(void)
{
  return ((STM32_READ_BIT(SBS->MESR, SBS_MESR_AXIRMEF) == SBS_MESR_AXIRMEF) ? 1UL : 0UL);
}

/**
  * @brief Check if an SBS memories erase status flag is active or not.
  * @rmtoll
  *  MESR   BKPMEF     LL_SBS_IsActiveFlag \n
  *  MESR   AXIRMEF    LL_SBS_IsActiveFlag
  * @param flag This parameter can be one of the following values:
  *        @arg @ref LL_SBS_FLAG_BKPMEF
  *        @arg @ref LL_SBS_FLAG_AXIRMEF
  * @retval retrieve the state of the selected memory flag (1U or 0U).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag(uint32_t flag)
{
  return ((STM32_READ_BIT(SBS->MESR, flag) == flag) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_IO_Speed_Optimization SBS IO speed optimization
  * @{
  */

/**
  * @brief  Enable the IO speed optimization.
  * @rmtoll
  *  CCCSR       IOHSLV       LL_SBS_EnableIOSpeedOptimization
  */
__STATIC_INLINE void LL_SBS_EnableIOSpeedOptimization(void)
{
  STM32_SET_BIT(SBS->CCCSR, SBS_CCCSR_IOHSLV);
}

/**
  * @brief  Disable the IO speed optimization.
  * @rmtoll
  *  CCCSR       IOHSLV       LL_SBS_DisableIOSpeedOptimization
  */
__STATIC_INLINE void LL_SBS_DisableIOSpeedOptimization(void)
{
  STM32_CLEAR_BIT(SBS->CCCSR, SBS_CCCSR_IOHSLV);
}

/**
  * @brief  Check if the IO speed optimization is enabled.
  * @rmtoll
  *  CCCSR       IOHSLV       LL_SBS_IsEnabledIOSpeedOptimization
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledIOSpeedOptimization(void)
{
  return ((STM32_READ_BIT(SBS->CCCSR, SBS_CCCSR_IOHSLV) == (SBS_CCCSR_IOHSLV)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_Compensation_Cell_Control SBS compensation cell control
  * @{
  */

/**
  * @brief  Set the compensation cell code.
  * @rmtoll
  *  CCCSR    COMP_CODESEL    LL_SBS_SetCompensationCellCodeSrc
  * @param  comp_cell This parameter can be one of the following value:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  code_source: This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_CODE_DEFAULT
  *         @arg @ref LL_SBS_CCELL_CODE_CUSTOM
  */
__STATIC_INLINE void LL_SBS_SetCompensationCellCodeSrc(uint32_t comp_cell, uint32_t code_source)
{
  STM32_ATOMIC_MODIFY_REG_32(SBS->CCCSR, (comp_cell << 1U), (code_source * (comp_cell << 1U)));
}

/**
  * @brief  Get the compensation cell code.
  * @rmtoll
  *  CCCSR    COMP_CODESEL    LL_SBS_GetCompensationCellCodeSrc
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @retval Returned value can be one of the following values:
  *   @arg LL_SBS_CCELL_CODE_DEFAULT : Selected Code is from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_CODE_CUSTOM  : Selected Code is from the SBS compensation cell code register (SBS_CCSWVALR)
  */
__STATIC_INLINE uint32_t LL_SBS_GetCompensationCellCodeSrc(uint32_t comp_cell)
{
  return (STM32_READ_BIT(SBS->CCCSR, (SBS_CCCSR_COMP_CODESEL << STM32_POSITION_VAL(comp_cell)))
          >> STM32_POSITION_VAL(comp_cell << 1U));
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR    COMP_CODESEL    LL_SBS_SetVddIOCompensationCellCodeSrc
  * @param  code_source: Select the code to be applied for the Vdd compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SBS_CCELL_VDDIO_DEFAULT_CODE : Select Code from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_VDDIO_CUSTOM_CODE  : Select Code from the SBS compensation cell code register (SBS_CCSWVALR)
  */
__STATIC_INLINE void LL_SBS_SetVddIOCompensationCellCodeSrc(uint32_t code_source)
{
  STM32_ATOMIC_SET_BIT_32(SBS->CCCSR, code_source);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR   COMP_CODESEL    LL_SBS_GetVddIOCompensationCellCodeSrc
  * @retval Returned value can be one of the following values:
  *   @arg LL_SBS_CCELL_VDDIO_DEFAULT_CODE : Select Code from the cell (available in the SBS_CCVALR)
  *   @arg LL_SBS_CCELL_VDDIO_CUSTOM_CODE  : Select Code from the SBS compensation cell code
  *                                                  register (SBS_CCSWVALR)
  */
__STATIC_INLINE uint32_t LL_SBS_GetVddIOCompensationCellCodeSrc(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCCSR, SBS_CCCSR_COMP_CODESEL));
}

/**
  * @brief  Enable the Compensation Cell.
  * @rmtoll
  *  CCCSR    COMP_EN    LL_SBS_EnableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note  X= [1]
  */
__STATIC_INLINE void LL_SBS_EnableCompensationCell(uint32_t comp_cell)
{
  STM32_ATOMIC_SET_BIT_32(SBS->CCCSR, comp_cell);
}

/**
  * @brief  Disable the Compensation Cell.
  * @rmtoll
  *  CCCSR    COMP_EN    LL_SBS_DisableCompensationCell
  * @param  comp_cell This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note  X= [1]
  */
__STATIC_INLINE void LL_SBS_DisableCompensationCell(uint32_t comp_cell)
{
  STM32_ATOMIC_CLEAR_BIT_32(SBS->CCCSR, comp_cell);
}

/**
  * @brief  Check if the Compensation Cell is enable.
  * @rmtoll
  *  CCCSR    COMP_EN    LL_SBS_IsEnabledCompensationCell
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note  x= [1]
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledCompensationCell(uint32_t comp_cell)
{
  return ((STM32_READ_BIT(SBS->CCCSR, comp_cell) == comp_cell) ? 1U : 0U);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR    COMP_EN    LL_SBS_EnableVddIOCompensationCell
  * @note   The vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  */
__STATIC_INLINE void LL_SBS_EnableVddIOCompensationCell(void)
{
  STM32_ATOMIC_SET_BIT_32(SBS->CCCSR, SBS_CCCSR_COMP_EN);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR    COMP_EN    LL_SBS_DisableVddIOCompensationCell
  * @note   The Vdd compensation cell can be used only when the device supply
  *         voltage ranges from 1.71 to 3.6 V
  */
__STATIC_INLINE void LL_SBS_DisableVddIOCompensationCell(void)
{
  STM32_ATOMIC_CLEAR_BIT_32(SBS->CCCSR, SBS_CCCSR_COMP_EN);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDD is enable.
  * @rmtoll
  *  CCCSR    COMP_EN    LL_SBS_IsEnabled_VddIOCompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledVddIOCompensationCell(void)
{
  return ((STM32_READ_BIT(SBS->CCCSR, SBS_CCCSR_COMP_EN) == SBS_CCCSR_COMP_EN) ? 1UL : 0UL);
}

/**
  * @brief  Get the PMOS transistor of the compensation cell value.
  * @rmtoll
  *  CCVALR  PSRC[3:0]  LL_SBS_GetPMOSCompensationCellValue
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note  x= [1]
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSCompensationCellValue(uint32_t comp_cell)
{
  return STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_PSRC) >> (STM32_POSITION_VAL(comp_cell << 1U) * 4U);
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value.
  * @rmtoll
  *  CCVALR    NSRC[3:0]   LL_SBS_GetNMOSCompensationCellValue
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note  x= [1]
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSCompensationCellValue(uint32_t comp_cell)
{
  return STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_NSRC) >> (STM32_POSITION_VAL(comp_cell) * 4U);
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDD.
  * @rmtoll
  *  CCVALR    PSRC[3:0]   LL_SBS_GetPMOSVddIOCompensationCellValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSVddIOCompensationCellValue(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_PSRC));
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCVALR    NSRC[3:0]   LL_SBS_GetNMOSVddIOCompensationCellValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSVddIOCompensationCellValue(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCVALR, SBS_CCVALR_NSRC));
}

/**
  * @brief  Set the compensation cell code of PMOS transistor.
  * @rmtoll
  *  CCSWVALR    SW_PSRC[3:0]   LL_SBS_SetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  pmos_code PMOS compensation code
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE void LL_SBS_SetPMOSCompensationCellCode(uint32_t comp_cell, uint32_t pmos_code)
{
  STM32_ATOMIC_MODIFY_REG_32(SBS->CCSWVALR, SBS_CCSWVALR_SW_PSRC,
                             (pmos_code << (STM32_POSITION_VAL(comp_cell << 1U) * 4U)));
}

/**
  * @brief  Get the compensation cell code of PMOS transistor.
  * @rmtoll
  *  CCSWVALR    SW_PSRC[3:0]   LL_SBS_GetPMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note   This code is applied to the PMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @retval Returned value of the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSCompensationCellCode(uint32_t comp_cell)
{
  return (STM32_READ_BIT(SBS->CCSWVALR, (SBS_CCSWVALR_SW_PSRC << (STM32_POSITION_VAL(comp_cell) * 4U))));
}

/**
  * @brief  Set the compensation cell code of NMOS transistor.
  * @rmtoll
  *  CCSWVALR    SW_NSRC[3:0]   LL_SBS_SetNMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @param  nmos_code NMOS compensation code
  * @note   This code is applied to the NMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE void LL_SBS_SetNMOSCompensationCellCode(uint32_t comp_cell, uint32_t nmos_code)
{
  STM32_ATOMIC_MODIFY_REG_32(SBS->CCSWVALR, SBS_CCSWVALR_SW_NSRC, (nmos_code << (STM32_POSITION_VAL(comp_cell) * 4U)));
}

/**
  * @brief  Get the NMOS transistor of the compensation cell value.
  * @rmtoll
  *  CCSWVALR    SW_NSRC[3:0]   LL_SBS_GetNMOSCompensationCellCode
  * @param  comp_cell This parameter can be one of the following values:
  *         @arg @ref LL_SBS_CCELL_VDDIO
  * @note   This code is applied to the NMOS compensation cell when the CSx x=[1] bits of the SBS_CCCSR is set
  * @retval Returned value of the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSCompensationCellCode(uint32_t comp_cell)
{
  return (STM32_READ_BIT(SBS->CCSWVALR, (SBS_CCSWVALR_SW_NSRC << (STM32_POSITION_VAL(comp_cell) * 4U))));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS and NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWVALR    SW_NSRC[3:0]  LL_SBS_SetxMOSVddIOCompensationCellCode \n
  *  CCSWVALR    SW_PSRC[3:0]  LL_SBS_SetxMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetxMOSVddIOCompensationCellCode(uint32_t pmos_code, uint32_t nmos_code)
{
  STM32_MODIFY_REG(SBS->CCSWVALR, (SBS_CCSWVALR_SW_PSRC | SBS_CCSWVALR_SW_NSRC),
                   ((pmos_code << SBS_CCSWVALR_SW_PSRC_Pos) | (nmos_code << SBS_CCSWVALR_SW_NSRC_Pos)));
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWVALR    SW_PSRC[3:0]  LL_SBS_SetPMOSVddIOCompensationCellCode
  * @param  pmos_code PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetPMOSVddIOCompensationCellCode(uint32_t pmos_code)
{
  STM32_MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_SW_PSRC, pmos_code << SBS_CCSWVALR_SW_PSRC_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWVALR    SW_PSRC[3:0]   LL_SBS_GetPMOSVddIOCompensationCellCode
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SBS_GetPMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_SW_PSRC));
}

/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWVALR    SW_NSRC[3:0]  LL_SBS_SetNMOSVddIOCompensationCellCode
  * @param  nmos_code NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS1 bit of the
  *         SBS_CCCSR is set
  */
__STATIC_INLINE void LL_SBS_SetNMOSVddIOCompensationCellCode(uint32_t nmos_code)
{
  STM32_MODIFY_REG(SBS->CCSWVALR, SBS_CCSWVALR_SW_NSRC, nmos_code << SBS_CCSWVALR_SW_NSRC_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDD.
  * @rmtoll
  *  CCSWVALR    SW_NSRC[3:0]   LL_SBS_GetNMOSVddIOCompensationCellCode
  * @retval Returned value is the Vdd compensation cell code for NMOS transistors
  */
__STATIC_INLINE uint32_t LL_SBS_GetNMOSVddIOCompensationCellCode(void)
{
  return (uint32_t)(STM32_READ_BIT(SBS->CCSWVALR, SBS_CCSWVALR_SW_NSRC));
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDD.
  * @rmtoll
  *  CCCSR    COMP_RDY    LL_SBS_IsActiveFlag_RDY1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsActiveFlag_RDY1(void)
{
  return ((STM32_READ_BIT(SBS->CCCSR, SBS_CCCSR_COMP_RDY) == (SBS_CCCSR_COMP_RDY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_Tim_Break_Management SBS tim break management
  * @{
  */

/**
  * @brief  Set connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  BKLOCKR       ARAM1ECC_BL       LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       ARAM2ECC_BL       LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       ARAM3ECC_BL       LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       ARAM4ECC_BL       LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       ITCMECC_BL        LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       DTCMECC_BL        LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       BKRAMECC_BL       LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       CM7LCKUP_BL       LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       FLASHECC_BL       LL_SBS_EnableTIMBreakInputs \n
  *  BKLOCKR       PVD_BL            LL_SBS_EnableTIMBreakInputs
  * @param  break_input This parameter can be one or a combination of the following values:
  *         @arg @ref LL_SBS_SRAM1_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_SRAM2_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_SRAM3_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_SRAM4_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_ITCM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_DTCM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_BKPRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_LOCKUP_OUT
  *         @arg @ref LL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_PVD
  */
__STATIC_INLINE void LL_SBS_EnableTIMBreakInputs(uint32_t break_input)
{
  STM32_SET_BIT(SBS->BKLOCKR, break_input);
}

/**
  * @brief  Get connections to TIM1/8/15/16/17 break inputs.
  * @rmtoll
  *  BKLOCKR       ARAM1ECC_BL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       ARAM2ECC_BL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       ARAM3ECC_BL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       ARAM4ECC_BL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       ITCMECC_BL        LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       DTCMECC_BL        LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       BKRAMECC_BL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       CM7LCKUP_BL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       FLASHECC_BL       LL_SBS_IsEnabledTIMBreakInputs \n
  *  BKLOCKR       PVD_BL            LL_SBS_IsEnabledTIMBreakInputs
  * @param  break_input This parameter can be one of the following values:
  *         @arg @ref LL_SBS_SRAM1_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_SRAM2_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_SRAM3_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_SRAM4_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_ITCM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_DTCM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_BKPRAM_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_LOCKUP_OUT
  *         @arg @ref LL_SBS_FLASH_ECC_DOUBLE_ERROR
  *         @arg @ref LL_SBS_PVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SBS_IsEnabledTIMBreakInputs(uint32_t break_input)
{
  return ((STM32_READ_BIT(SBS->BKLOCKR, break_input) == (break_input)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup SBS_EXTI_Source_Config SBS EXTI source config
  * @{
  */

/**
  * @brief  Configure source input for the EXTI external interrupt.
  * @rmtoll
  *  EXTICR1 PC_EXTI0         LL_SBS_SetEXTISource \n
  *  EXTICR1 PC_EXTI1         LL_SBS_SetEXTISource \n
  *  EXTICR1 PC_EXTI2         LL_SBS_SetEXTISource \n
  *  EXTICR1 PC_EXTI3         LL_SBS_SetEXTISource \n
  *  EXTICR2 PC_EXTI4         LL_SBS_SetEXTISource \n
  *  EXTICR2 PC_EXTI5         LL_SBS_SetEXTISource \n
  *  EXTICR2 PC_EXTI6         LL_SBS_SetEXTISource \n
  *  EXTICR2 PC_EXTI7         LL_SBS_SetEXTISource \n
  *  EXTICR3 PC_EXTI8         LL_SBS_SetEXTISource \n
  *  EXTICR3 PC_EXTI9         LL_SBS_SetEXTISource \n
  *  EXTICR3 PC_EXTI10        LL_SBS_SetEXTISource \n
  *  EXTICR3 PC_EXTI11        LL_SBS_SetEXTISource \n
  *  EXTICR4 PC_EXTI12        LL_SBS_SetEXTISource \n
  *  EXTICR4 PC_EXTI13        LL_SBS_SetEXTISource \n
  *  EXTICR4 PC_EXTI14        LL_SBS_SetEXTISource \n
  *  EXTICR4 PC_EXTI15        LL_SBS_SetEXTISource
  * @param  port This parameter can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTA
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTB
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTC
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTD
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTE
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTF
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTG
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTH
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTI
  * @param  line This parameter can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE0
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE1
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE2
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE3
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE4
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE5
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE6
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE7
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE8
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE9
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE10
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE11
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE12
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE13
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE14
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE15
  * @note   (*)Please check each device gpio port mapping for SBS EXTI GPIO port availability
  */
__STATIC_INLINE void LL_SBS_SetEXTISource(uint32_t port, uint32_t line)
{
  STM32_ATOMIC_MODIFY_REG_32(SBS->EXTICR[line >> LL_SBS_EXTI_CR_REGISTER_SHIFT],
                             (SBS_EXTICR1_PC_EXTI0 << ((line & 3U) << 2U)), (port << ((line & 3U) << 2U)));
}

/**
  * @brief  Get the configured defined for specific EXTI Line.
  * @rmtoll
  *  EXTICR1 PC_EXTI0         LL_SBS_GetEXTISource \n
  *  EXTICR1 PC_EXTI1         LL_SBS_GetEXTISource \n
  *  EXTICR1 PC_EXTI2         LL_SBS_GetEXTISource \n
  *  EXTICR1 PC_EXTI3         LL_SBS_GetEXTISource \n
  *  EXTICR2 PC_EXTI4         LL_SBS_GetEXTISource \n
  *  EXTICR2 PC_EXTI5         LL_SBS_GetEXTISource \n
  *  EXTICR2 PC_EXTI6         LL_SBS_GetEXTISource \n
  *  EXTICR2 PC_EXTI7         LL_SBS_GetEXTISource \n
  *  EXTICR3 PC_EXTI8         LL_SBS_GetEXTISource \n
  *  EXTICR3 PC_EXTI9         LL_SBS_GetEXTISource \n
  *  EXTICR3 PC_EXTI10        LL_SBS_GetEXTISource \n
  *  EXTICR3 PC_EXTI11        LL_SBS_GetEXTISource \n
  *  EXTICR4 PC_EXTI12        LL_SBS_GetEXTISource \n
  *  EXTICR4 PC_EXTI13        LL_SBS_GetEXTISource \n
  *  EXTICR4 PC_EXTI14        LL_SBS_GetEXTISource \n
  *  EXTICR4 PC_EXTI15        LL_SBS_GetEXTISource
  * @param  line This parameter can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE0
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE1
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE2
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE3
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE4
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE5
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE6
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE7
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE8
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE9
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE10
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE11
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE12
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE13
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE14
  *         @arg @ref LL_SBS_EXTI_GPIO_LINE15
  * @note   (*)Please check each device gpio port mapping for SBS EXTI GPIO port availability
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTA
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTB
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTC
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTD
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTE
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTF
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTG
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTH
  *         @arg @ref LL_SBS_EXTI_GPIO_PORTI
  */
__STATIC_INLINE uint32_t LL_SBS_GetEXTISource(uint32_t line)
{
  return ((uint32_t)(STM32_READ_BIT(SBS->EXTICR[line >> LL_SBS_EXTI_CR_REGISTER_SHIFT],
                                    (SBS_EXTICR1_PC_EXTI0 << ((line & 3U) << 2U)))) >> ((line & 3U) << 2U));
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
#endif /* SBS */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_LL_SBS_H */
