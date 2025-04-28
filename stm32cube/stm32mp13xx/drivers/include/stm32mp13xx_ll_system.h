/**
  ******************************************************************************
  * @file    stm32mp13xx_ll_system.h
  * @author  MCD Application Team
  * @brief   Header file of SYSTEM LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL SYSTEM driver contains a set of generic APIs that can be
    used by user:
      (+) Access to DBGCMU registers
      (+) Access to SYSCFG registers

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP13xx_LL_SYSTEM_H
#define STM32MP13xx_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx.h"

/** @addtogroup STM32MP13xx_LL_Driver
  * @{
  */

#if defined (SYSCFG) || defined (DBGMCU)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_BOOT_PIN SYSCFG Boot Pin code selection
  * @{
  */
#define LL_SYSCFG_BOOT0           SYSCFG_BOOTR_BOOT0       /*!< BOOT0 pin connected to VDD */
#define LL_SYSCFG_BOOT1           SYSCFG_BOOTR_BOOT1       /*!< BOOT1 pin connected to VDD */
#define LL_SYSCFG_BOOT2           SYSCFG_BOOTR_BOOT2       /*!< BOOT2 pin connected to VDD */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_I2C_FASTMODEPLUS SYSCFG I2C FASTMODEPLUS
  * @{
  */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C1        SYSCFG_PMCSETR_I2C1_FMP       /*!< Enable Fast Mode Plus for I2C1      */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C2        SYSCFG_PMCSETR_I2C2_FMP       /*!< Enable Fast Mode Plus for I2C2      */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C3        SYSCFG_PMCSETR_I2C3_FMP       /*!< Enable Fast Mode Plus for I2C3      */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C4        SYSCFG_PMCSETR_I2C4_FMP       /*!< Enable Fast Mode Plus for I2C4      */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C5        SYSCFG_PMCSETR_I2C5_FMP       /*!< Enable Fast Mode Plus for I2C5      */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_ETHERNET_PHY Ethernet PHY Interface Selection
  * @{
  */
#define LL_SYSCFG_ETH1_MII               0x00000000U                        /*!< Enable ETH1 Media MII interface */
#define LL_SYSCFG_ETH1_RGMII             SYSCFG_PMCSETR_ETH1_SEL_0          /*!< Enable ETH1 Media RGMII interface */
#define LL_SYSCFG_ETH1_RMII              SYSCFG_PMCSETR_ETH1_SEL_2          /*!< Enable ETH1 Media RMII interface */
#define LL_SYSCFG_ETH2_MII               0x00000000U                        /*!< Enable ETH2 Media MII interface */
#define LL_SYSCFG_ETH2_RGMII             SYSCFG_PMCSETR_ETH2_SEL_0          /*!< Enable ETH2 Media RGMII interface */
#define LL_SYSCFG_ETH2_RMII              SYSCFG_PMCSETR_ETH2_SEL_2          /*!< Enable ETH2 Media RMII interface */

/**
  * @}
  */


/** @defgroup SYSTEM_LL_EC_ETHERNET_CLK Ethernet CLK Mode Selection
  * @{
  */
#define LL_SYSCFG_ETH1_CLK               SYSCFG_PMCSETR_ETH1_CLK_SEL           /*!< Enable ETH1 clock selection */
#define LL_SYSCFG_ETH1_REF_CLK           SYSCFG_PMCSETR_ETH1_REF_CLK_SEL       /*!< Enable ETH1 REF clock selection */
#define LL_SYSCFG_ETH2_CLK               SYSCFG_PMCSETR_ETH2_CLK_SEL           /*!< Enable ETH2 clock selection */
#define LL_SYSCFG_ETH2_REF_CLK           SYSCFG_PMCSETR_ETH2_REF_CLK_SEL       /*!< Enable ETH2 REF clock selection */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK SYSCFG TIMER BREAK
  * @{
  */
#define LL_SYSCFG_TIMBREAK_PVD             SYSCFG_CBR_PVDL    /*!< Enables and locks the PVD connection
                                                                   with TIM1/8/15/16/17 Break Input
                                                                   and also the PVDE and PLS bits of the 
                                                                   Power Control Interface */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_IO_COMPENSATION SYSCFG I/O compensation cell code selection
  * @{
  */
#define LL_SYSCFG_CELL_CODE               0U                     /*!< Disable Compensation Software Control */
#define LL_SYSCFG_REGISTER_CODE           SYSCFG_CMPCR_SW_CTRL   /*!< Enable Compensation Software Control */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_COMPENSATION_CELL SYSCFG compensation cell control register
  * @{
  */
#define LL_SYSCFG_MAIN_COMP_CELL               (0x1U << 1)
#define LL_SYSCFG_SD1_COMP_CELL                (0x1U << 2)
#define LL_SYSCFG_SD2_COMP_CELL                (0x1U << 3)
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_HSLV SYSCFG High Speed Low Voltage Config
  * @{
  */
#define LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL   (0x1U << 0)   /*!< High Speed Low Voltage Pad mode Enable when a TRACEx signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL    (0x1U << 1)   /*!< High Speed Low Voltage Pad mode Enable when a QUADSPI_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL    (0x1U << 2)   /*!< High Speed Low Voltage Pad mode Enable when a ETH_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL    (0x1U << 3)   /*!< High Speed Low Voltage Pad mode Enable when a ETH_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL  (0x1U << 4)   /*!< High Speed Low Voltage Pad mode Enable when a SDMMCy_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL  (0x1U << 5)   /*!< High Speed Low Voltage Pad mode Enable when a SDMMCy_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL    (0x1U << 6)   /*!< High Speed Low Voltage Pad mode Enable when a SPIy_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL    (0x1U << 7)   /*!< High Speed Low Voltage Pad mode Enable when a SPIy_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL    (0x1U << 8)   /*!< High Speed Low Voltage Pad mode Enable when a SPIy_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL    (0x1U << 9)   /*!< High Speed Low Voltage Pad mode Enable when a SPIy_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL    (0x1U << 10)  /*!< High Speed Low Voltage Pad mode Enable when a SPIy_x signal is selected in AFMUX */
#define LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL    (0x1U << 11)  /*!< High Speed Low Voltage Pad mode Enable when a LTDCy_x signal is selected in AFMUX */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP_IP DBGMCU APB1 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_TIM2_STOP      DBGMCU_APB1_FZ_DBG_TIM2_STOP     /*!< TIM2 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP      DBGMCU_APB1_FZ_DBG_TIM3_STOP     /*!< TIM3 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM4_STOP      DBGMCU_APB1_FZ_DBG_TIM4_STOP     /*!< TIM4 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM5_STOP      DBGMCU_APB1_FZ_DBG_TIM5_STOP     /*!< TIM5 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM6_STOP      DBGMCU_APB1_FZ_DBG_TIM6_STOP     /*!< TIM6 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM7_STOP      DBGMCU_APB1_FZ_DBG_TIM7_STOP     /*!< TIM7 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP    DBGMCU_APB1_FZ_DBG_LPTIM1_STOP   /*!< LPTIM1 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C1_STOP      DBGMCU_APB1_FZ_DBG_I2C1_STOP     /*!< I2C1 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C2_STOP      DBGMCU_APB1_FZ_DBG_I2C2_STOP     /*!< I2C2 SMBUS timeout mode stopped when Core is halted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP_IP DBGMCU APB2 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB2_GRP1_TIM1_STOP     DBGMCU_APB2_FZ_DBG_TIM1_STOP     /*!< TIM1 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB2_GRP1_TIM8_STOP     DBGMCU_APB2_FZ_DBG_TIM8_STOP     /*!< TIM8 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB2_GRP1_FDCAN_STOP    DBGMCU_APB2_FZ_DBG_FDCAN_STOP    /*!< FDCAN is frozen while the core is in debug mode */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB3_GRP1_STOP_IP DBGMCU APB3 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB3_GRP1_LPTIM2_STOP     DBGMCU_APB3_FZ_DBG_LPTIM2_STOP   /*!< LPTIM2 counter stopped when core is halted */
#define LL_DBGMCU_APB3_GRP1_LPTIM3_STOP     DBGMCU_APB3_FZ_DBG_LPTIM3_STOP   /*!< LPTIM3 counter stopped when core is halted */
#define LL_DBGMCU_APB3_GRP1_LPTIM4_STOP     DBGMCU_APB3_FZ_DBG_LPTIM4_STOP   /*!< LPTIM4 counter stopped when core is halted */
#define LL_DBGMCU_APB3_GRP1_LPTIM5_STOP     DBGMCU_APB3_FZ_DBG_LPTIM5_STOP   /*!< LPTIM5 counter stopped when core is halted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB4_GRP1_STOP_IP DBGMCU APB4 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB4_GRP1_IWDG2_STOP      DBGMCU_APB4_FZ_DBG_IWDG2_STOP     /*!< IWDG2 is frozen while the core is in debug mode */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB5_GRP1_STOP_IP DBGMCU APB5 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB5_GRP1_IWDG1_STOP      DBGMCU_APB5_FZ_DBG_IWDG1_STOP     /*!< IWDG1 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB5_GRP1_RTC_STOP        DBGMCU_APB5_FZ_DBG_RTC_STOP       /*!< RTC is frozen while the core is in debug mode */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB6_GRP1_STOP_IP DBGMCU APB6 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB6_GRP1_I2C3_STOP      DBGMCU_APB6_FZ_DBG_I2C3_STOP      /*!< I2C3 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_I2C4_STOP      DBGMCU_APB6_FZ_DBG_I2C4_STOP      /*!< I2C4 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_I2C5_STOP      DBGMCU_APB6_FZ_DBG_I2C5_STOP      /*!< I2C5 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_TIM12_STOP     DBGMCU_APB6_FZ_DBG_TIM12_STOP     /*!< TIM12 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_TIM13_STOP     DBGMCU_APB6_FZ_DBG_TIM13_STOP     /*!< TIM13 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_TIM14_STOP     DBGMCU_APB6_FZ_DBG_TIM14_STOP     /*!< TIM14 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_TIM15_STOP     DBGMCU_APB6_FZ_DBG_TIM15_STOP     /*!< TIM15 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_TIM16_STOP     DBGMCU_APB6_FZ_DBG_TIM16_STOP     /*!< TIM16 is frozen while the core is in debug mode */
#define LL_DBGMCU_APB6_GRP1_TIM17_STOP     DBGMCU_APB6_FZ_DBG_TIM17_STOP     /*!< TIM17 is frozen while the core is in debug mode */
/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Get boot pin value connected to VDD
  * @rmtoll SYSCFG_BOOTR   BOOTx   LL_SYSCFG_GetBootPinValueToVDD
  * @param  BootPinValue This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_BOOT0
  *         @arg @ref LL_SYSCFG_BOOT1
  *         @arg @ref LL_SYSCFG_BOOT2
  * @retval None
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetBootPinValueToVDD(uint16_t BootPinValue)
{
  return (uint32_t)(READ_BIT(SYSCFG->BOOTR, BootPinValue));
}

/**
  * @brief  Set Ethernet1 PHY interface
  * @rmtoll SYSCFG_PMCSETR   ETH1_SEL      LL_SYSCFG_SetPHYInterfaceETH1
  * @param  Interface : Interface This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH1_MII
  *         @arg @ref LL_SYSCFG_ETH1_RGMII
  *         @arg @ref LL_SYSCFG_ETH1_RMII
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPHYInterfaceETH1(uint32_t Interface)
{
  MODIFY_REG(SYSCFG->PMCCLRR, SYSCFG_PMCCLRR_ETH1_SEL, SYSCFG_PMCCLRR_ETH1_SEL);
  MODIFY_REG(SYSCFG->PMCSETR, SYSCFG_PMCSETR_ETH1_SEL, Interface);
}

/**
  * @brief  Get Ethernet1 PHY interface
  * @rmtoll SYSCFG_PMCSETR   ETH1_SEL      LL_SYSCFG_GetPHYInterfaceETH1
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH1_MII
  *         @arg @ref LL_SYSCFG_ETH1_RMII
  *         @arg @ref LL_SYSCFG_ETH1_RGMII
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPHYInterfaceETH1(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->PMCSETR, SYSCFG_PMCSETR_ETH1_SEL));
}

/**
  * @brief  Clear Ethernet1 PHY mode
  * @rmtoll SYSCFG_PMCSETR   ETH1_SEL      LL_SYSCFG_ClearPHYInterfaceETH1
  * @param  Interface : Interface This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH1_MII
  *         @arg @ref LL_SYSCFG_ETH1_RGMII
  *         @arg @ref LL_SYSCFG_ETH1_RMII
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_ClearPHYInterfaceETH1(uint32_t Interface)
{
  MODIFY_REG(SYSCFG->PMCCLRR, SYSCFG_PMCCLRR_ETH1_SEL, Interface);
}

/**
  * @brief  Disable Ethernet1 clock
  * @rmtoll SYSCFG_PMCCLRR   ETH1_CLK_SEL       LL_SYSCFG_DisablePHYInternalClockETH1\n
  *         SYSCFG_PMCCLRR   ETH1_REF_CLK_SEL   LL_SYSCFG_DisablePHYInternalClockETH1
  * @param  Clock : This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH1_CLK
  *         @arg @ref LL_SYSCFG_ETH1_REF_CLK
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisablePHYInternalClockETH1(uint32_t Clock)
{
  MODIFY_REG(SYSCFG->PMCCLRR, (SYSCFG_PMCCLRR_ETH1_CLK_SEL | SYSCFG_PMCCLRR_ETH1_REF_CLK_SEL), Clock);
}

/**
  * @brief  Enable Ethernet1 clock
  * @rmtoll SYSCFG_PMCSETR   ETH1_CLK_SEL       LL_SYSCFG_EnablePHYInternalClockETH1\n
  *         SYSCFG_PMCSETR   ETH1_REF_CLK_SEL   LL_SYSCFG_EnablePHYInternalClockETH1
  * @param  Clock : This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH1_CLK
  *         @arg @ref LL_SYSCFG_ETH1_REF_CLK
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnablePHYInternalClockETH1(uint32_t Clock)
{
  MODIFY_REG(SYSCFG->PMCSETR, (SYSCFG_PMCSETR_ETH1_CLK_SEL | SYSCFG_PMCSETR_ETH1_REF_CLK_SEL), Clock);
}

/**
  * @brief  Set Ethernet2 PHY interface
  * @rmtoll SYSCFG_PMCSETR   ETH2_SEL      LL_SYSCFG_SetPHYInterfaceETH2
  * @param  Interface : Interface This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH2_MII
  *         @arg @ref LL_SYSCFG_ETH2_RGMII
  *         @arg @ref LL_SYSCFG_ETH2_RMII
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPHYInterfaceETH2(uint32_t Interface)
{
  MODIFY_REG(SYSCFG->PMCCLRR, SYSCFG_PMCCLRR_ETH2_SEL, SYSCFG_PMCCLRR_ETH2_SEL);
  MODIFY_REG(SYSCFG->PMCSETR, SYSCFG_PMCSETR_ETH2_SEL, Interface);
}

/**
  * @brief  Get Ethernet2 PHY interface
  * @rmtoll SYSCFG_PMCSETR   ETH2_SEL      LL_SYSCFG_GetPHYInterfaceETH2
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH2_MII
  *         @arg @ref LL_SYSCFG_ETH2_RMII
  *         @arg @ref LL_SYSCFG_ETH2_RGMII
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPHYInterfaceETH2(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->PMCSETR, SYSCFG_PMCSETR_ETH2_SEL));
}

/**
  * @brief  Clear Ethernet2 PHY mode
  * @rmtoll SYSCFG_PMCSETR   ETH2_SEL      LL_SYSCFG_ClearPHYInterfaceETH2
  * @param  Interface : Interface This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH2_MII
  *         @arg @ref LL_SYSCFG_ETH2_RGMII
  *         @arg @ref LL_SYSCFG_ETH2_RMII
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_ClearPHYInterfaceETH2(uint32_t Interface)
{
  MODIFY_REG(SYSCFG->PMCCLRR, SYSCFG_PMCCLRR_ETH2_SEL, Interface);
}


/**
  * @brief  Disable Ethernet2 clock
  * @rmtoll SYSCFG_PMCCLRR   ETH2_CLK_SEL       LL_SYSCFG_DisablePHYInternalClockETH2\n
  *         SYSCFG_PMCCLRR   ETH2_REF_CLK_SEL   LL_SYSCFG_DisablePHYInternalClockETH2
  * @param  Clock : This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH2_CLK
  *         @arg @ref LL_SYSCFG_ETH2_REF_CLK
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisablePHYInternalClockETH2(uint32_t Clock)
{
  MODIFY_REG(SYSCFG->PMCCLRR, (SYSCFG_PMCCLRR_ETH2_CLK_SEL | SYSCFG_PMCCLRR_ETH2_REF_CLK_SEL), Clock);
}

/**
  * @brief  Enable Ethernet2 clock
  * @rmtoll SYSCFG_PMCSETR   ETH2_CLK_SEL       LL_SYSCFG_EnablePHYInternalClockETH2\n
  *         SYSCFG_PMCSETR   ETH2_REF_CLK_SEL   LL_SYSCFG_EnablePHYInternalClockETH2
  * @param  Clock : This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ETH2_CLK
  *         @arg @ref LL_SYSCFG_ETH2_REF_CLK
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnablePHYInternalClockETH2(uint32_t Clock)
{
  MODIFY_REG(SYSCFG->PMCSETR, (SYSCFG_PMCSETR_ETH2_CLK_SEL | SYSCFG_PMCSETR_ETH2_REF_CLK_SEL), Clock);
}

/**
  * @brief  Enable the Analog GPIO switch to control voltage selection
  *         when the supply voltage is supplied by VDDA
  * @rmtoll SYSCFG_PMCSETR   ANASWVDD   LL_SYSCFG_EnableAnalogGpioSwitch
  * @note   Activating the gpio switch enable IOs analog switches supplied by VDDA
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableAnalogGpioSwitch(void)
{
  SET_BIT(SYSCFG->PMCSETR, SYSCFG_PMCSETR_ANASWVDD);
}

/**
  * @brief  Disable the Analog GPIO switch to control voltage selection
  *         when the supply voltage is supplied by VDDA
  * @rmtoll SYSCFG_PMCCLRR   ANASWVDD   LL_SYSCFG_DisableAnalogGpioSwitch
  * @note   Activating the gpio switch enable IOs analog switches supplied by VDDA
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableAnalogGpioSwitch(void)
{
  SET_BIT(SYSCFG->PMCCLRR, SYSCFG_PMCCLRR_ANASWVDD);
}

/**
  * @brief  Enable the Analog booster to reduce the total harmonic distortion
  *         of the analog switch when the supply voltage is lower than 2.7 V
  * @rmtoll SYSCFG_PMCSETR   EN_BOOSTER   LL_SYSCFG_EnableAnalogBooster
  * @note   Activating the booster allows to guaranty the analog switch AC performance
  *         when the supply voltage is below 2.7 V: in this case, the analog switch
  *         performance is the same on the full voltage range
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableAnalogBooster(void)
{
  SET_BIT(SYSCFG->PMCSETR, SYSCFG_PMCSETR_EN_BOOSTER);
}

/**
  * @brief  Disable the Analog booster
  * @rmtoll SYSCFG_PMCCLRR   EN_BOOSTER   LL_SYSCFG_DisableAnalogBooster
  * @note   Activating the booster allows to guaranty the analog switch AC performance
  *         when the supply voltage is below 2.7 V: in this case, the analog switch
  *         performance is the same on the full voltage range
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableAnalogBooster(void)
{
  SET_BIT(SYSCFG->PMCCLRR, SYSCFG_PMCCLRR_EN_BOOSTER);
}

/**
  * @brief  Enable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_PMCSETR   I2Cx_FMP   LL_SYSCFG_EnableFastModePlus\n
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C2
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C3
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C4
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C5
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  SET_BIT(SYSCFG->PMCSETR, ConfigFastModePlus);
}

/**
  * @brief  Disable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_PMCCLRR   I2Cx_FMP   LL_SYSCFG_DisableFastModePlus\n
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C2
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C3
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C4
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C5
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  MODIFY_REG(SYSCFG->PMCCLRR, \
             (SYSCFG_PMCCLRR_I2C1_FMP | SYSCFG_PMCCLRR_I2C2_FMP | \
              SYSCFG_PMCCLRR_I2C3_FMP | SYSCFG_PMCCLRR_I2C4_FMP | \
              SYSCFG_PMCCLRR_I2C5_FMP), ConfigFastModePlus);
}

/**
  * @brief  Enable the Compensation Cell
  * @rmtoll SYSCFG_CMPENSETR   EN   LL_SYSCFG_EnableCompensationCell
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @note   The I/O compensation cell can be used only when the device supply
  *         voltage ranges from 2.4 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableCompensationCell(uint32_t CompCells)
{
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPENSETR, SYSCFG_CMPENSETR_EN);
  }

  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPSD1ENSETR, SYSCFG_CMPSD1ENSETR_EN);
  }

  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPSD2ENSETR, SYSCFG_CMPSD2ENSETR_EN);
  }
}

/**
  * @brief  Disable the Compensation Cell
  * @rmtoll SYSCFG_CMPENCLRR   EN   LL_SYSCFG_DisableCompensationCell
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @note   The I/O compensation cell can be used only when the device supply
  *         voltage ranges from 2.4 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableCompensationCell(uint32_t CompCells)
{

  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPENCLRR, SYSCFG_CMPENCLRR_EN);
  }

  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPSD1ENCLRR, SYSCFG_CMPSD1ENCLRR_EN);
  }

  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPSD2ENCLRR, SYSCFG_CMPSD2ENCLRR_EN);
  }
}

/**
  * @brief  Check if the Compensation Cell is enabled
  * @rmtoll SYSCFG_CMPENSETR   EN   LL_SYSCFG_IsEnabledCompensationCell
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledCompensationCell(uint32_t CompCells)
{
  uint32_t status;
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPENSETR, SYSCFG_CMPENSETR_EN) == SYSCFG_CMPENSETR_EN);
  }

  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD1ENSETR, SYSCFG_CMPSD1ENSETR_EN) == SYSCFG_CMPSD1ENSETR_EN);
  }

  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD2ENSETR, SYSCFG_CMPSD2ENSETR_EN) == SYSCFG_CMPSD2ENSETR_EN);
  }
  return status;
}

/**
  * @brief  Get Compensation Cell ready Flag
  * @rmtoll SYSCFG_CMPCR   READY   LL_SYSCFG_IsReadyCompensationCell
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsReadyCompensationCell(uint32_t CompCells)
{
  uint32_t status;
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPCR, SYSCFG_CMPCR_READY) == (SYSCFG_CMPCR_READY));
  }

  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD1CR, SYSCFG_CMPSD1CR_READY) == (SYSCFG_CMPSD1CR_READY));
  }

  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD2CR, SYSCFG_CMPSD2CR_READY) == (SYSCFG_CMPSD2CR_READY));
  }
  return status;
}

/**
  * @brief  To Enable optimize the I/O speed when the product voltage is low.
  * @note   This bit is active only if PRODUCT_BELOW_25V user option bit is set. It must be
  *         used only if the product supply voltage is below 2.5 V. Setting this bit when VDD is
  *         higher than 2.5 V might be destructive.
  * @param  LL_SYSCFG_HighSpeedSignal: Signal selection (TRACE, QUADSPI...)
  *   This parameter can be one or a combination of the following values:
  *   @arg LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIOSpeedOptimization(uint32_t LL_SYSCFG_HighSpeedSignal)
{
  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL) == LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN0R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL) == LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN1R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL) == LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN2R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL) == LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN3R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL) == LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN4R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL) == LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN5R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN6R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN7R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN8R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN9R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN10R, 0x1018U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL) == LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN11R, 0x1018U);
  }
}

/**
  * @brief  To Disable optimize the I/O speed when the product voltage is low.
  * @note   This bit is active only if PRODUCT_BELOW_25V user option bit is set. It must be
  *         used only if the product supply voltage is below 2.5 V. Setting this bit when VDD is
  *         higher than 2.5 V might be destructive.
  * @param  LL_SYSCFG_HighSpeedSignal: Signal selection (TRACE, QUADSPI...)
  *   This parameter can be one or a combination of the following values:
  *   @arg LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIOSpeedOptimization(uint32_t LL_SYSCFG_HighSpeedSignal)
{
  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL) == LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN0R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL) == LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN1R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL) == LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN2R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL) == LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN3R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL) == LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN4R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL) == LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN5R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN6R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN7R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN8R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN9R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN10R, 0x0U);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL) == LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL)
  {
    WRITE_REG(SYSCFG->HSLVEN11R, 0x0U);
  }
}

/**
  * @brief  Check if I/O speed optimization is enabled.
  * @note   This bit is active only if PRODUCT_BELOW_25V user option bit is set. It must be
  *         used only if the product supply voltage is below 2.5 V. Setting this bit when VDD is
  *         higher than 2.5 V might be destructive.
  * @param  LL_SYSCFG_HighSpeedSignal: Signal selection (TRACE, QUADSPI...)
  *   This parameter can be one or a combination of the following values:
  *   @arg LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL
  *   @arg LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIOSpeedOptimization(uint32_t LL_SYSCFG_HighSpeedSignal)
{
  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL) == LL_SYSCFG_HIGHSPEED_TRACE_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN0R, SYSCFG_HSLVEN0R_HSLVEN_TRACE) == SYSCFG_HSLVEN0R_HSLVEN_TRACE);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL) == LL_SYSCFG_HIGHSPEED_QSPI_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN1R, SYSCFG_HSLVEN1R_HSLVEN_QSPI) == SYSCFG_HSLVEN1R_HSLVEN_QSPI);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL) == LL_SYSCFG_HIGHSPEED_ETH1_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN2R, SYSCFG_HSLVEN2R_HSLVEN_ETH1) == SYSCFG_HSLVEN2R_HSLVEN_ETH1);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL) == LL_SYSCFG_HIGHSPEED_ETH2_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN3R, SYSCFG_HSLVEN3R_HSLVEN_ETH2) == SYSCFG_HSLVEN3R_HSLVEN_ETH2);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL) == LL_SYSCFG_HIGHSPEED_SDMMC1_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN4R, SYSCFG_HSLVEN4R_HSLVEN_SDMMC1) == SYSCFG_HSLVEN4R_HSLVEN_SDMMC1);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL) == LL_SYSCFG_HIGHSPEED_SDMMC2_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN5R, SYSCFG_HSLVEN5R_HSLVEN_SDMMC2) == SYSCFG_HSLVEN5R_HSLVEN_SDMMC2);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI1_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN6R, SYSCFG_HSLVEN6R_HSLVEN_SPI1) == SYSCFG_HSLVEN6R_HSLVEN_SPI1);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI2_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN7R, SYSCFG_HSLVEN7R_HSLVEN_SPI2) == SYSCFG_HSLVEN7R_HSLVEN_SPI2);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI3_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN8R, SYSCFG_HSLVEN8R_HSLVEN_SPI3) == SYSCFG_HSLVEN8R_HSLVEN_SPI3);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI4_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN9R, SYSCFG_HSLVEN9R_HSLVEN_SPI4) == SYSCFG_HSLVEN9R_HSLVEN_SPI4);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL) == LL_SYSCFG_HIGHSPEED_SPI5_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN10R, SYSCFG_HSLVEN10R_HSLVEN_SPI5) == SYSCFG_HSLVEN10R_HSLVEN_SPI5);
  }

  if ((LL_SYSCFG_HighSpeedSignal & LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL) == LL_SYSCFG_HIGHSPEED_LTDC_SIGNAL)
  {
    return (uint32_t)(READ_BIT(SYSCFG->HSLVEN11R, SYSCFG_HSLVEN11R_HSLVEN_LTDC) == SYSCFG_HSLVEN11R_HSLVEN_LTDC);
  }
}


/**
  * @brief  Set the code selection for the I/O Compensation cell
  * @rmtoll SYSCFG_CMPCR   SW_CTRL   LL_SYSCFG_SetCellCompensationCode
  * @param  CompCode: Selects the code to be applied for the I/O compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_CELL_CODE : Select Code from the cell
  *   @arg LL_SYSCFG_REGISTER_CODE: Select Code from the SYSCFG compensation cell code register
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetCellCompensationCode(uint32_t CompCells, uint32_t CompCode)
{
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPCR, CompCode);
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPSD1CR, CompCode);
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    SET_BIT(SYSCFG->CMPSD2CR, CompCode);
  }
}

/**
  * @brief  Get the code selected for the I/O Compensation cell
  * @rmtoll SYSCFG_CMPCR   SW_CTRL   LL_SYSCFG_GetCellCompensationCode
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_CELL_CODE : Selected Code is from the cell
  *   @arg LL_SYSCFG_REGISTER_CODE: Selected Code is from the SYSCFG compensation cell code register
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetCellCompensationCode(uint32_t CompCells)
{
  uint32_t status;
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPCR, SYSCFG_CMPCR_SW_CTRL));
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD1CR, SYSCFG_CMPSD1CR_SW_CTRL));
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD2CR, SYSCFG_CMPSD2CR_SW_CTRL));
  }
  return status;
}

/**
  * @brief  Get I/O compensation cell value for PMOS transistors
  * @rmtoll SYSCFG_CMPCR   APSRC   LL_SYSCFG_GetPMOSCompensationValue
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval Returned value is the I/O compensation cell value for PMOS transistors
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSCompensationValue(uint32_t CompCells)
{
  uint32_t status;
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPCR, SYSCFG_CMPCR_APSRC));
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD1CR, SYSCFG_CMPCR_APSRC));
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD2CR, SYSCFG_CMPCR_APSRC));
  }
  return status;
}

/**
  * @brief  Get I/O compensation cell value for NMOS transistors
  * @rmtoll SYSCFG_CMPCR   ANSRC   LL_SYSCFG_GetNMOSCompensationValue
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval Returned value is the I/O compensation cell value for NMOS transistors
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSCompensationValue(uint32_t CompCells)
{
  uint32_t status;
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPCR, SYSCFG_CMPCR_ANSRC));
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD1CR, SYSCFG_CMPCR_ANSRC));
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD2CR, SYSCFG_CMPCR_ANSRC));
  }
  return status;
}

/**
  * @brief  Set I/O compensation cell code for PMOS transistors
  * @rmtoll SYSCFG_CMPCR   RAPSRC   LL_SYSCFG_SetPMOSCompensationCode
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @param  PMOSCode PMOS compensation code
  *         This code is applied to the I/O compensation cell when the CS bit of the
  *         SYSCFG_CMPCR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSCompensationCode(uint32_t CompCells, uint32_t PMOSCode)
{
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    MODIFY_REG(SYSCFG->CMPCR, SYSCFG_CMPCR_RAPSRC, PMOSCode);
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    MODIFY_REG(SYSCFG->CMPSD1CR, SYSCFG_CMPSD1CR_RAPSRC, PMOSCode);
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    MODIFY_REG(SYSCFG->CMPSD2CR, SYSCFG_CMPSD2CR_RAPSRC, PMOSCode);
  }
}

/**
  * @brief  Get I/O compensation cell code for PMOS transistors
  * @rmtoll SYSCFG_CMPCR   RAPSRC   LL_SYSCFG_GetPMOSCompensationCode
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval Returned value is the I/O compensation cell code for PMOS transistors
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSCompensationCode(uint32_t CompCells)
{
  uint32_t status;
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPCR, SYSCFG_CMPCR_RAPSRC));
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD1CR, SYSCFG_CMPCR_RAPSRC));
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD2CR, SYSCFG_CMPCR_RAPSRC));
  }
  return status;
}

/**
  * @brief  Set I/O compensation cell code for NMOS transistors
  * @rmtoll SYSCFG_CMPCR   RANSRC   LL_SYSCFG_SetNMOSCompensationCode
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @param  NMOSCode: NMOS compensation code
  *         This code is applied to the I/O compensation cell when the CS bit of the
  *         SYSCFG_CMPCR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSCompensationCode(uint32_t CompCells, uint32_t NMOSCode)
{
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    MODIFY_REG(SYSCFG->CMPCR, SYSCFG_CMPCR_RANSRC, NMOSCode);
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    MODIFY_REG(SYSCFG->CMPSD1CR, SYSCFG_CMPSD1CR_RANSRC, NMOSCode);
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    MODIFY_REG(SYSCFG->CMPSD2CR, SYSCFG_CMPSD2CR_RANSRC, NMOSCode);
  }
}

/**
  * @brief  Get I/O compensation cell code for NMOS transistors
  * @rmtoll SYSCFG_CMPCR   RANSRC   LL_SYSCFG_GetNMOSCompensationCode
  * @param  CompCells This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_MAIN_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD1_COMP_CELL
  *         @arg @ref LL_SYSCFG_SD2_COMP_CELL
  * @retval Returned value is the I/O compensation cell code for NMOS transistors
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSCompensationCode(uint32_t CompCells)
{
  uint32_t status;
  if ((CompCells & LL_SYSCFG_MAIN_COMP_CELL) == LL_SYSCFG_MAIN_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPCR, SYSCFG_CMPCR_RANSRC));
  }
  if ((CompCells & LL_SYSCFG_SD1_COMP_CELL) == LL_SYSCFG_SD1_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD1CR, SYSCFG_CMPCR_RANSRC));
  }
  if ((CompCells & LL_SYSCFG_SD2_COMP_CELL) == LL_SYSCFG_SD2_COMP_CELL)
  {
    status = (uint32_t)(READ_BIT(SYSCFG->CMPSD2CR, SYSCFG_CMPCR_RANSRC));
  }
  return status;
}

/**
  * @brief  Set connections to TIM1/8/15/16/17 Break inputs
  * @note this feature is available on STM32MP1 rev.B and above
  * @rmtoll SYSCFG_CBR   PVDL   LL_SYSCFG_SetTIMBreakInputs
  * @param  Break This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIMBreakInputs(uint32_t Break)
{
  MODIFY_REG(SYSCFG->CBR,  SYSCFG_CBR_PVDL, Break);
}

/**
  * @brief  Get connections to TIM1/8/15/16/17 Break inputs
  * @note this feature is available on STM32MP1 rev.B and above
  * @rmtoll
  *         SYSCFG_CBR   PVDL   LL_SYSCFG_GetTIMBreakInputs
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIMBreakInputs(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CBR,  SYSCFG_CBR_PVDL));
}


/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the device identifier
  * @rmtoll DBGMCU_IDCODE DEV_ID        LL_DBGMCU_GetDeviceID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDeviceID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier
  * @note This field indicates the revision of the device.
          For example, it is read as RevA -> 0x1000, Cat 2 revZ -> 0x1001
  * @rmtoll DBGMCU_IDCODE REV_ID        LL_DBGMCU_GetRevisionID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable D1 Domain debug during Low Power mode
  * @rmtoll DBGMCU_CR   DBG_DBGLP   LL_DBGMCU_EnableDebugInLowPowerMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDebugInLowPowerMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_DBGLP);
}

/**
  * @brief  Disable D1 Domain debug during Low Power mode
  * @rmtoll DBGMCU_CR   DBG_DBGLP   LL_DBGMCU_DisableDebugInLowPowerMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDebugInLowPowerMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_DBGLP);
}

/**
  * @brief  Freeze APB1 group1 peripherals
  * @rmtoll DBGMCU_APB1FZ1   TIM2      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM3      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM4      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM5      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM6      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM7      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   LPTIM1    LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   I2C1      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ1   I2C2      LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB1FZ1, Periphs);
}

/**
  * @brief  Unfreeze APB1 group1 peripherals
  * @rmtoll DBGMCU_APB1FZ1   TIM2      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM3      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM4      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM5      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM6      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   TIM7      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   LPTIM1    LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   I2C1      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ1   I2C2      LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB1FZ1, Periphs);
}

/**
  * @brief  Freeze APB2 group1 peripherals
  * @rmtoll DBGMCU_APB2FZ1   TIM1    LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ1   TIM8    LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ1   FDCAN   LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM8_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_FDCAN_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB2FZ1, Periphs);
}

/**
  * @brief  Unfreeze APB2 group1 peripherals
  * @rmtoll DBGMCU_APB2FZ1   TIM1    LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ1   TIM8    LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ1   FDCAN   LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM8_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_FDCAN_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB2FZ1, Periphs);
}

/**
  * @brief  Freeze APB3 peripherals
  * @rmtoll DBGMCU_APB3FZ1    LPTIM2    LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  *         DBGMCU_APB3FZ1    LPTIM3    LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  *         DBGMCU_APB3FZ1    LPTIM4    LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  *         DBGMCU_APB3FZ1    LPTIM5    LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM5_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB3FZ1, Periphs);
}

/**
  * @brief  Unfreeze APB3 peripherals
  * @rmtoll DBGMCU_APB3FZ1    LPTIM2    LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB3FZ1    LPTIM3    LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB3FZ1    LPTIM4    LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB3FZ1    LPTIM5    LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_LPTIM5_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB3FZ1, Periphs);
}

/**
  * @brief  Freeze APB4 peripherals
  * @rmtoll DBGMCU_APB4FZ1    IWDG2     LL_DBGMCU_APB4_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB4_GRP1_IWDG2_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB4FZ1, Periphs);
}

/**
  * @brief  Unfreeze APB4 peripherals
  * @rmtoll DBGMCU_APB4FZ1    IWDG2    LL_DBGMCU_APB4_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB4_GRP1_IWDG2_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB4FZ1, Periphs);
}

/**
  * @brief  Freeze APB5 peripherals
  * @rmtoll DBGMCU_APB5FZ1    IWDG1     LL_DBGMCU_APB5_GRP1_FreezePeriph\n
  *         DBGMCU_APB5FZ1    RTC       LL_DBGMCU_APB5_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB5_GRP1_IWDG1_STOP
  *         @arg @ref LL_DBGMCU_APB5_GRP1_RTC_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB5_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB5FZ1, Periphs);
}

/**
  * @brief  Unfreeze APB5 peripherals
  * @rmtoll DBGMCU_APB5FZ2    IWDG1     LL_DBGMCU_APB5_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB5FZ2    RTC       LL_DBGMCU_APB5_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB5_GRP1_IWDG1_STOP
  *         @arg @ref LL_DBGMCU_APB5_GRP1_RTC_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB5_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB5FZ1, Periphs);
}

/**
  * @brief  Freeze APB6 peripherals
  * @rmtoll DBGMCU_APB6FZ1    I2C3      LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    I2C4      LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    I2C5      LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM12     LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM13     LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM14     LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM15     LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM16     LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM17     LL_DBGMCU_APB6_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB6_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_I2C4_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_I2C5_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM12_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM13_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB6_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB6FZ1, Periphs);
}

/**
  * @brief  Unfreeze APB6 peripherals
  * @rmtoll DBGMCU_APB6FZ1    I2C3      LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    I2C4      LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    I2C5      LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM12     LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM13     LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM14     LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM15     LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM16     LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB6FZ1    TIM17     LL_DBGMCU_APB6_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB6_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_I2C4_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_I2C5_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM12_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM13_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB6_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB6_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB6FZ1, Periphs);
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

#endif /* defined (SYSCFG) || defined (DBGMCU) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_LL_SYSTEM_H */
