/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_system.h
  * @author  MCD Application Team
  * @brief   Header file of SYSTEM LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP2xx_LL_SYSTEM_H
#define __STM32MP2xx_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
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

#if defined(CORE_CA35) || defined(CORE_CM33)


/** @defgroup SYSTEM_LL_EC_CS1 SYSCFG Vdd compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_VDD_CELL_CODE                  0U                   /*VDD I/Os code from the cell
                                                                      (available in the SYSCFG_VDDCCCR)*/
#define LL_SYSCFG_VDD_REGISTER_CODE              SYSCFG_VDDCCCR_CS    /*VDD I/Os code from the SYSCFG compensation
                                                                        cell code register (SYSCFG_VDDCCCR)*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_CS2 SYSCFG VddIO1 compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_VDDIO1_CELL_CODE                0U                    /*VDDIO1 I/Os code from the cell
                                                                        (available in the SYSCFG_VDDIO1CCCR)*/
#define LL_SYSCFG_VDDIO1_REGISTER_CODE            SYSCFG_VDDIO1CCCR_CS  /*VDDIO1 I/Os code from the SYSCFG compensation
                                                                        cell code register (SYSCFG_VDDIO1CCCR)*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_CS3 SYSCFG VddIO2 compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_VDDIO2_CELL_CODE                0U                    /*VDDIO2 I/Os code from the cell
                                                                        (available in the SYSCFG_VDDIO2CCCR)*/
#define LL_SYSCFG_VDDIO2_REGISTER_CODE            SYSCFG_VDDIO2CCCR_CS  /*VDDIO2 I/Os code from the SYSCFG compensation
                                                                        cell code register (SYSCFG_VDDIO2CCCR)*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_CS4 SYSCFG VddIO3 compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_VDDIO3_CELL_CODE                0U                    /*VDDIO3 I/Os code from the cell
                                                                        (available in the SYSCFG_VDDIO3CCCR)*/
#define LL_SYSCFG_VDDIO3_REGISTER_CODE            SYSCFG_VDDIO3CCCR_CS  /*VDDIO3 I/Os code from the SYSCFG compensation
                                                                        cell code register (SYSCFG_VDDIO3CCCR)*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_CS5 SYSCFG VddIO4 compensation cell Code selection
  * @{
  */
#define LL_SYSCFG_VDDIO4_CELL_CODE                0U                    /*VDDIO4 I/Os code from the cell
                                                                        (available in the SYSCFG_VDDIO4CCCR)*/
#define LL_SYSCFG_VDDIO4_REGISTER_CODE            SYSCFG_VDDIO4CCCR_CS  /*VDDIO4 I/Os code from the SYSCFG compensation
                                                                        cell code register (SYSCFG_VDDIO4CCCR)*/
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_IWDG DBGMCU IWDG Freeze Watchdog
  * @{
  */
#define LL_DBGMCU_IWDG_FREEZE_1CA35_HALT   0U                         /*!< Freeze Watchdog timer when either CA35 core halt in secure debug mode */
#define LL_DBGMCU_IWDG_FREEZE_2CA35_HALT   DBGMCU_CRA35_WDFZCTL       /*!< Freeze Watchdog timer when both CA35 cores halt in secure debug mode */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP_IP  DBGMCU APB1 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_TIM2_STOP         DBGMCU_APB1FZ_DBG_TIM2_STOP         /*!< TIM2 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM3_STOP         DBGMCU_APB1FZ_DBG_TIM3_STOP         /*!< TIM3 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM4_STOP         DBGMCU_APB1FZ_DBG_TIM4_STOP         /*!< TIM4 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM5_STOP         DBGMCU_APB1FZ_DBG_TIM5_STOP         /*!< TIM5 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM6_STOP         DBGMCU_APB1FZ_DBG_TIM6_STOP         /*!< TIM6 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM7_STOP         DBGMCU_APB1FZ_DBG_TIM7_STOP         /*!< TIM7 counter stopped when core is halted  */
#define LL_DBGMCU_APB1_GRP1_TIM10_STOP        DBGMCU_APB1FZ_DBG_TIM10_STOP        /*!< TIM10 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM11_STOP        DBGMCU_APB1FZ_DBG_TIM11_STOP        /*!< TIM11 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM12_STOP        DBGMCU_APB1FZ_DBG_TIM12_STOP        /*!< TIM12 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM13_STOP        DBGMCU_APB1FZ_DBG_TIM13_STOP        /*!< TIM13 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_TIM14_STOP        DBGMCU_APB1FZ_DBG_TIM14_STOP        /*!< TIM14 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP       DBGMCU_APB1FZ_DBG_LPTIM1_STOP       /*!< LPTIM1 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_LPTIM2_STOP       DBGMCU_APB1FZ_DBG_LPTIM2_STOP       /*!< LPTIM2 counter stopped when core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C1_STOP         DBGMCU_APB1FZ_DBG_I2C1_STOP         /*!< I2C1 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C2_STOP         DBGMCU_APB1FZ_DBG_I2C2_STOP         /*!< I2C2 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C3_STOP         DBGMCU_APB1FZ_DBG_I2C3_STOP         /*!< I2C3 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C4_STOP         DBGMCU_APB1FZ_DBG_I2C4_STOP         /*!< I2C4 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C5_STOP         DBGMCU_APB1FZ_DBG_I2C5_STOP         /*!< I2C5 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C6_STOP         DBGMCU_APB1FZ_DBG_I2C6_STOP         /*!< I2C6 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C7_STOP         DBGMCU_APB1FZ_DBG_I2C7_STOP         /*!< I2C7 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I3C1_STOP         DBGMCU_APB1FZ_DBG_I3C1_STOP         /*!< I3C1 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I3C2_STOP         DBGMCU_APB1FZ_DBG_I3C2_STOP         /*!< I3C2 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APB1_GRP1_I3C3_STOP         DBGMCU_APB1FZ_DBG_I3C3_STOP         /*!< I3C3 SMBUS timeout mode stopped when Core is halted */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP_IP  DBGMCU APB2 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB2_GRP1_TIM1_STOP         DBGMCU_APB2FZ_DBG_TIM1_STOP         /*!< TIM1 counter stopped when core is halted */
#define LL_DBGMCU_APB2_GRP1_TIM8_STOP         DBGMCU_APB2FZ_DBG_TIM8_STOP         /*!< TIM8 counter stopped when core is halted */
#define LL_DBGMCU_APB2_GRP1_TIM15_STOP        DBGMCU_APB2FZ_DBG_TIM15_STOP        /*!< TIM15 counter stopped when core is halted */
#define LL_DBGMCU_APB2_GRP1_TIM16_STOP        DBGMCU_APB2FZ_DBG_TIM16_STOP        /*!< TIM16 counter stopped when core is halted */
#define LL_DBGMCU_APB2_GRP1_TIM17_STOP        DBGMCU_APB2FZ_DBG_TIM17_STOP        /*!< TIM17 counter stopped when core is halted */
#define LL_DBGMCU_APB2_GRP1_TIM20_STOP        DBGMCU_APB2FZ_DBG_TIM20_STOP        /*!< TIM20 counter stopped when core is halted */
#define LL_DBGMCU_APB2_GRP1_FDCAN_STOP        DBGMCU_APB2FZ_DBG_FDCAN_STOP        /*!< FDCAN stopped when core is halted */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APB3_GRP1_STOP_IP  DBGMCU APB3 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB3_GRP1_IWDG1_STOP        DBGMCU_APB3FZ_DBG_IWDG1_STOP        /*!< IWDG1 counter stopped when core is halted */
#define LL_DBGMCU_APB3_GRP1_IWDG2_STOP        DBGMCU_APB3FZ_DBG_IWDG2_STOP        /*!< IWDG2 counter stopped when core is halted */
#define LL_DBGMCU_APB3_GRP1_IWDG3_STOP        DBGMCU_APB3FZ_DBG_IWDG3_STOP        /*!< IWDG3 counter stopped when core is halted */
#define LL_DBGMCU_APB3_GRP1_IWDG4_STOP        DBGMCU_APB3FZ_DBG_IWDG4_STOP        /*!< IWDG4 counter stopped when core is halted */
#define LL_DBGMCU_APB3_GRP1_WWDG1_STOP        DBGMCU_APB3FZ_DBG_WWDG1_STOP        /*!< WWDG1 counter stopped when core is halted */

/** @defgroup SYSTEM_LL_EC_CRA35_GRP1_STOP_IP  DBGMCU CRA35 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_CRA35_DBG_STGEN_STOP        DBGMCU_CRA35_DBG_STGEN_STOP         /*!< STGEN counter stopped when CA35 core is halted */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_APBSR_GRP1_STOP_IP  DBGMCU APBSR GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APBSR_GRP1_RTC_STOP         DBGMCU_APBSRFZ_DBG_RTC_STOP         /*!< RTC stopped when Core is halted */
#define LL_DBGMCU_APBSR_GRP1_I3C4_STOP        DBGMCU_APBSRFZ_DBG_I3C4_STOP        /*!< I3C4 stopped when Core is halted */
#define LL_DBGMCU_APBSR_GRP1_I2C8_STOP        DBGMCU_APBSRFZ_DBG_I2C8_STOP        /*!< I2C8 SMBUS timeout mode stopped when Core is halted */
#define LL_DBGMCU_APBSR_GRP1_LPTIM3_STOP      DBGMCU_APBSRFZ_DBG_LPTIM3_STOP      /*!< LPTIM3 counter stopped when core is halted */
#define LL_DBGMCU_APBSR_GRP1_LPTIM4_STOP      DBGMCU_APBSRFZ_DBG_LPTIM4_STOP      /*!< LPTIM4 counter stopped when core is halted */
#define LL_DBGMCU_APBSR_GRP1_LPTIM5_STOP      DBGMCU_APBSRFZ_DBG_LPTIM5_STOP      /*!< LPTIM5 counter stopped when core is halted */
#define LL_DBGMCU_APBSR_GRP1_IWDG5_STOP       DBGMCU_APBSRFZ_DBG_IWDG5_STOP       /*!< IWDG5 counter stopped when core is halted */
#define LL_DBGMCU_APBSR_GRP1_WWDG2_STOP       DBGMCU_APBSRFZ_DBG_WWDG2_STOP       /*!< WWDG2 counter stopped when core is halted */

/** @defgroup SYSTEM_LL_EC_AHB2_GRP1_STOP_IP  DBGMCU AHB2 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH0_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH0_STOP  /*!< HDPMA1 Channel 0 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH1_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH1_STOP  /*!< HDPMA1 Channel 1 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH2_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH2_STOP  /*!< HDPMA1 Channel 2 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH3_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH3_STOP  /*!< HDPMA1 Channel 3 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH4_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH4_STOP  /*!< HDPMA1 Channel 4 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH5_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH5_STOP  /*!< HDPMA1 Channel 5 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH6_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH6_STOP  /*!< HDPMA1 Channel 6 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH7_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH7_STOP  /*!< HDPMA1 Channel 7 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH8_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH8_STOP  /*!< HDPMA1 Channel 8 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH9_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA1_CH9_STOP  /*!< HDPMA1 Channel 9 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH10_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA1_CH10_STOP /*!< HDPMA1 Channel 10 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH11_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA1_CH11_STOP /*!< HDPMA1 Channel 11 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH12_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA1_CH12_STOP /*!< HDPMA1 Channel 12 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH13_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA1_CH13_STOP /*!< HDPMA1 Channel 13 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH14_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA1_CH14_STOP /*!< HDPMA1 Channel 14 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA1_CH15_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA1_CH15_STOP /*!< HDPMA1 Channel 15 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH0_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH0_STOP  /*!< HDPMA2 Channel 0 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH1_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH1_STOP  /*!< HDPMA2 Channel 1 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH2_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH2_STOP  /*!< HDPMA2 Channel 2 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH3_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH3_STOP  /*!< HDPMA2 Channel 3 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH4_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH4_STOP  /*!< HDPMA2 Channel 4 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH5_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH5_STOP  /*!< HDPMA2 Channel 5 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH6_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH6_STOP  /*!< HDPMA2 Channel 6 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH7_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH7_STOP  /*!< HDPMA2 Channel 7 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH8_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH8_STOP  /*!< HDPMA2 Channel 8 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH9_STOP   DBGMCU_AHB2LFZ_DBG_HPDMA2_CH9_STOP  /*!< HDPMA2 Channel 9 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH10_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA2_CH10_STOP /*!< HDPMA2 Channel 10 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH11_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA2_CH11_STOP /*!< HDPMA2 Channel 11 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH12_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA2_CH12_STOP /*!< HDPMA2 Channel 12 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH13_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA2_CH13_STOP /*!< HDPMA2 Channel 13 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH14_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA2_CH14_STOP /*!< HDPMA2 Channel 14 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP1_HPDMA2_CH15_STOP  DBGMCU_AHB2LFZ_DBG_HPDMA2_CH15_STOP /*!< HDPMA2 Channel 15 stopped when core is halted */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_AHB2_GRP2_STOP_IP  DBGMCU AHB2 GRP2 STOP IP
  * @{
  */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH0_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH0_STOP  /*!< HDPMA3 Channel 0 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH1_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH1_STOP  /*!< HDPMA3 Channel 1 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH2_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH2_STOP  /*!< HDPMA3 Channel 2 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH3_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH3_STOP  /*!< HDPMA3 Channel 3 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH4_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH4_STOP  /*!< HDPMA3 Channel 4 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH5_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH5_STOP  /*!< HDPMA3 Channel 5 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH6_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH6_STOP  /*!< HDPMA3 Channel 6 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH7_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH7_STOP  /*!< HDPMA3 Channel 7 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH8_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH8_STOP  /*!< HDPMA3 Channel 8 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH9_STOP   DBGMCU_AHB2HFZ_DBG_HPDMA3_CH9_STOP  /*!< HDPMA3 Channel 9 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH10_STOP  DBGMCU_AHB2HFZ_DBG_HPDMA3_CH10_STOP /*!< HDPMA3 Channel 10 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH11_STOP  DBGMCU_AHB2HFZ_DBG_HPDMA3_CH11_STOP /*!< HDPMA3 Channel 11 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH12_STOP  DBGMCU_AHB2HFZ_DBG_HPDMA3_CH12_STOP /*!< HDPMA3 Channel 12 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH13_STOP  DBGMCU_AHB2HFZ_DBG_HPDMA3_CH13_STOP /*!< HDPMA3 Channel 13 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH14_STOP  DBGMCU_AHB2HFZ_DBG_HPDMA3_CH14_STOP /*!< HDPMA3 Channel 14 stopped when core is halted */
#define LL_DBGMCU_AHB2_GRP2_HPDMA3_CH15_STOP  DBGMCU_AHB2HFZ_DBG_HPDMA3_CH15_STOP /*!< HDPMA3 Channel 15 stopped when core is halted */

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_AHBSR_GRP1_STOP_IP  DBGMCU AHBSR GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_AHBSR_GRP1_LPDMA_CH0_STOP   DBGMCU_AHBSRFZ_DBG_LPDMA_CH0_STOP   /*!< LPDMA Channel 0 stopped when core is halted */
#define LL_DBGMCU_AHBSR_GRP1_LPDMA_CH1_STOP   DBGMCU_AHBSRFZ_DBG_LPDMA_CH1_STOP   /*!< LPDMA Channel 1 stopped when core is halted */
#define LL_DBGMCU_AHBSR_GRP1_LPDMA_CH2_STOP   DBGMCU_AHBSRFZ_DBG_LPDMA_CH2_STOP   /*!< LPDMA Channel 2 stopped when core is halted */
#define LL_DBGMCU_AHBSR_GRP1_LPDMA_CH3_STOP   DBGMCU_AHBSRFZ_DBG_LPDMA_CH3_STOP   /*!< LPDMA Channel 3 stopped when core is halted */

/**
  * @}
  */

/**
  * @}
  */
#endif /* CORE_CA35 || CORE_CM33 */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_COMPENSATION SYSCFG COMPENSATION
  * @{
  */

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDD
  * @rmtoll VDDCCSR  APSRC  LL_SYSCFG_GetPMOSVddCompensationValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddCompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDCCSR, SYSCFG_VDDCCSR_APSRC) >> SYSCFG_VDDCCSR_APSRC_Pos);
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDD
  * @rmtoll VDDCCSR  ANSRC   LL_SYSCFG_GetNMOSVddCompensationValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddCompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDCCSR, SYSCFG_VDDCCSR_ANSRC) >> SYSCFG_VDDCCSR_ANSRC_Pos);
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDD
  * @rmtoll VDDCCCR    RAPSRC  LL_SYSCFG_SetPMOSVddCompensationCode
  * @param  PMOSCode PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CCCSR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddCompensationCode(uint32_t PMOSCode)
{
  MODIFY_REG(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_RAPSRC, PMOSCode << SYSCFG_VDDCCCR_RAPSRC_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDD
  * @rmtoll VDDCCCR    RAPSRC   LL_SYSCFG_GetPMOSVddCompensationCode
  * @retval Returned value is the PMOS compensation
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddCompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_RAPSRC) >> SYSCFG_VDDCCCR_RAPSRC_Pos);
}


/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDD
  * @rmtoll VDDCCCR    RANSRC  LL_SYSCFG_SetNMOSVddCompensationCode
  * @param  NMOSCode NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CMPCR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSVddCompensationCode(uint32_t NMOSCode)
{
  MODIFY_REG(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_RANSRC, NMOSCode << SYSCFG_VDDCCCR_RANSRC_Pos);
}


/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDD
  * @rmtoll VDDCCCR    RANSRC   LL_SYSCFG_GetNMOSVddCompensationCode
  * @retval Returned value is the NMOS compensation cell code
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddCompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_RANSRC) >> SYSCFG_VDDCCCR_RANSRC_Pos);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDD
  * @rmtoll VDDCCCR   EN    LL_SYSCFG_EnableVddCompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddCompensationCell(void)
{
  SET_BIT(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_EN);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDD
  * @rmtoll VDDCCCR   EN    LL_SYSCFG_DisableVddCompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddCompensationCell(void)
{
  CLEAR_BIT(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_EN);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDD is enable
  * @rmtoll VDDCCCR   EN   LL_SYSCFG_IsEnabled_VddCompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddCompensationCell(void)
{
  return ((READ_BIT(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_EN) == SYSCFG_VDDCCCR_EN) ? 1UL : 0UL);
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDD
  * @rmtoll VDDCCSR   READY   LL_SYSCFG_IsActiveFlag_VddCMPCR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_VddCMPCR(void)
{
  return ((READ_BIT(SYSCFG->VDDCCSR, SYSCFG_VDDCCSR_READY) == (SYSCFG_VDDCCSR_READY)) ? 1UL : 0UL);
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDD
  * @rmtoll VDDCCCR   CS    LL_SYSCFG_SetVddCellCompensationCode
  * @param  CompCode: Selects the code to be applied for the VddIO compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_VDD_CELL_CODE : Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDD_REGISTER_CODE: Select Code from the SYSCFG compensation cell code register (SYSCFG_CCCR)
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetVddCellCompensationCode(uint32_t CompCode)
{
  SET_BIT(SYSCFG->VDDCCCR, CompCode);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDD
  * @rmtoll VDDCCCR   CS    LL_SYSCFG_GetVddCellCompensationCode
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_VDD_CELL_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDD_REGISTER_CODE: Selected Code is from the SYSCFG compensation
      cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddCellCompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDCCCR, SYSCFG_VDDCCCR_CS));
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDDIO1
  * @rmtoll VDDIO1CCSR  APSRC  LL_SYSCFG_GetPMOSVddIO1CompensationValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO1CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO1CCSR, SYSCFG_VDDIO1CCSR_APSRC) >> SYSCFG_VDDIO1CCSR_APSRC_Pos);
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDDIO1
  * @rmtoll VDDIO1CCSR  ANSRC   LL_SYSCFG_GetNMOSVddIO1CompensationValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO1CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO1CCSR, SYSCFG_VDDIO1CCSR_ANSRC) >> SYSCFG_VDDIO1CCSR_ANSRC_Pos);
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDDIO1
  * @rmtoll VDDIO1CCCR    RAPSRC  LL_SYSCFG_SetPMOSVddIO1CompensationCode
  * @param  PMOSCode PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CCCSR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddIO1CompensationCode(uint32_t PMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_RAPSRC, PMOSCode << SYSCFG_VDDIO1CCCR_RAPSRC_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDDIO1
  * @rmtoll VDDIO1CCCR    RAPSRC   LL_SYSCFG_GetPMOSVddIO1CompensationCode
  * @retval Returned value is the PMOS compensation
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO1CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_RAPSRC) >> SYSCFG_VDDIO1CCCR_RAPSRC_Pos);
}


/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDDIO1
  * @rmtoll VDDIO1CCCR    RANSRC  LL_SYSCFG_SetNMOSVddIO1CompensationCode
  * @param  NMOSCode NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CMPCR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSVddIO1CompensationCode(uint32_t NMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_RANSRC, NMOSCode << SYSCFG_VDDIO1CCCR_RANSRC_Pos);
}


/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDDIO1
  * @rmtoll VDDIO1CCCR    RANSRC   LL_SYSCFG_GetNMOSVddIO1CompensationCode
  * @retval Returned value is the NMOS compensation cell code
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO1CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_RANSRC) >> SYSCFG_VDDIO1CCCR_RANSRC_Pos);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDDIO1
  * @rmtoll VDDIO1CCCR   EN    LL_SYSCFG_EnableVddIO1CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddIO1CompensationCell(void)
{
  SET_BIT(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_EN);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDDIO1
  * @rmtoll VDDIO1CCCR   EN    LL_SYSCFG_DisableVddIO1CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddIO1CompensationCell(void)
{
  CLEAR_BIT(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_EN);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDDIO1 is enable
  * @rmtoll VDDIO1CCCR   EN   LL_SYSCFG_IsEnabled_VddIO1CompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddIO1CompensationCell(void)
{
  return ((READ_BIT(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_EN) == SYSCFG_VDDIO1CCCR_EN) ? 1UL : 0UL);
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDDIO1
  * @rmtoll VDDIO1CCSR   READY   LL_SYSCFG_IsActiveFlag_VddIO1CMPCR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_VddIO1CMPCR(void)
{
  return ((READ_BIT(SYSCFG->VDDIO1CCSR, SYSCFG_VDDIO1CCSR_READY) == (SYSCFG_VDDIO1CCSR_READY)) ? 1UL : 0UL);
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDDIO1
  * @rmtoll VDDIO1CCCR   CS    LL_SYSCFG_SetVddIO1CellCompensationCode
  * @param  CompCode: Selects the code to be applied for the VddIO compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO1_CELL_CODE : Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO1_REGISTER_CODE: Select Code from the SYSCFG compensation cell code register (SYSCFG_CCCR)
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetVddIO1CellCompensationCode(uint32_t CompCode)
{
  SET_BIT(SYSCFG->VDDIO1CCCR, CompCode);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDDIO1
  * @rmtoll VDDIO1CCCR   CS    LL_SYSCFG_GetVddIO1CellCompensationCode
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO1_CELL_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO1_REGISTER_CODE: Selected Code is from the SYSCFG compensation
      cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddIO1CellCompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO1CCCR, SYSCFG_VDDIO1CCCR_CS));
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDDIO2
  * @rmtoll VDDIO2CCSR  APSRC  LL_SYSCFG_GetPMOSVddIO2CompensationValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO2CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO2CCSR, SYSCFG_VDDIO2CCSR_APSRC) >> SYSCFG_VDDIO2CCSR_APSRC_Pos);
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDDIO2
  * @rmtoll VDDIO2CCSR  ANSRC   LL_SYSCFG_GetNMOSVddIO2CompensationValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO2CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO2CCSR, SYSCFG_VDDIO2CCSR_ANSRC) >> SYSCFG_VDDIO2CCSR_ANSRC_Pos);
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDDIO2
  * @rmtoll VDDIO2CCCR    RAPSRC  LL_SYSCFG_SetPMOSVddIO2CompensationCode
  * @param  PMOSCode PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CCCSR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddIO2CompensationCode(uint32_t PMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_RAPSRC, PMOSCode << SYSCFG_VDDIO2CCCR_RAPSRC_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDDIO2
  * @rmtoll VDDIO2CCCR    RAPSRC   LL_SYSCFG_GetPMOSVddIO2CompensationCode
  * @retval Returned value is the PMOS compensation
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO2CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_RAPSRC) >> SYSCFG_VDDIO2CCCR_RAPSRC_Pos);
}


/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDDIO2
  * @rmtoll VDDIO2CCCR    RANSRC  LL_SYSCFG_SetNMOSVddIO2CompensationCode
  * @param  NMOSCode NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CMPCR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSVddIO2CompensationCode(uint32_t NMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_RANSRC, NMOSCode << SYSCFG_VDDIO2CCCR_RANSRC_Pos);
}


/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDDIO2
  * @rmtoll VDDIO2CCCR    RANSRC   LL_SYSCFG_GetNMOSVddIO2CompensationCode
  * @retval Returned value is the NMOS compensation cell code
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO2CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_RANSRC) >> SYSCFG_VDDIO2CCCR_RANSRC_Pos);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDDIO2
  * @rmtoll VDDIO2CCCR   EN    LL_SYSCFG_EnableVddIO2CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddIO2CompensationCell(void)
{
  SET_BIT(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_EN);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDDIO2
  * @rmtoll VDDIO2CCCR   EN    LL_SYSCFG_DisableVddIO2CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddIO2CompensationCell(void)
{
  CLEAR_BIT(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_EN);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDDIO2 is enable
  * @rmtoll VDDIO2CCCR   EN   LL_SYSCFG_IsEnabled_VddIO2CompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddIO2CompensationCell(void)
{
  return ((READ_BIT(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_EN) == SYSCFG_VDDIO2CCCR_EN) ? 1UL : 0UL);
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDDIO2
  * @rmtoll VDDIO2CCSR   READY   LL_SYSCFG_IsActiveFlag_VddIO2CMPCR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_VddIO2CMPCR(void)
{
  return ((READ_BIT(SYSCFG->VDDIO2CCSR, SYSCFG_VDDIO2CCSR_READY) == (SYSCFG_VDDIO2CCSR_READY)) ? 1UL : 0UL);
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDDIO2
  * @rmtoll VDDIO2CCCR   CS    LL_SYSCFG_SetVddIO2CellCompensationCode
  * @param  CompCode: Selects the code to be applied for the VddIO compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO2_CELL_CODE : Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO2_REGISTER_CODE: Select Code from the SYSCFG compensation cell code register (SYSCFG_CCCR)
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetVddIO2CellCompensationCode(uint32_t CompCode)
{
  SET_BIT(SYSCFG->VDDIO2CCCR, CompCode);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDDIO2
  * @rmtoll VDDIO2CCCR   CS    LL_SYSCFG_GetVddIO2CellCompensationCode
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO2_CELL_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO2_REGISTER_CODE: Selected Code is from the SYSCFG compensation
      cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddIO2CellCompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO2CCCR, SYSCFG_VDDIO2CCCR_CS));
}

/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDDIO3
  * @rmtoll VDDIO3CCSR  APSRC  LL_SYSCFG_GetPMOSVddIO3CompensationValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO3CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO3CCSR, SYSCFG_VDDIO3CCSR_APSRC) >> SYSCFG_VDDIO3CCSR_APSRC_Pos);
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDDIO3
  * @rmtoll VDDIO3CCSR  ANSRC   LL_SYSCFG_GetNMOSVddIO3CompensationValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO3CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO3CCSR, SYSCFG_VDDIO3CCSR_ANSRC) >> SYSCFG_VDDIO3CCSR_ANSRC_Pos);
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDDIO3
  * @rmtoll VDDIO3CCCR    RAPSRC  LL_SYSCFG_SetPMOSVddIO3CompensationCode
  * @param  PMOSCode PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CCCSR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddIO3CompensationCode(uint32_t PMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_RAPSRC, PMOSCode << SYSCFG_VDDIO3CCCR_RAPSRC_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDDIO3
  * @rmtoll VDDIO3CCCR    RAPSRC   LL_SYSCFG_GetPMOSVddIO3CompensationCode
  * @retval Returned value is the PMOS compensation
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO3CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_RAPSRC) >> SYSCFG_VDDIO3CCCR_RAPSRC_Pos);
}


/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDDIO3
  * @rmtoll VDDIO3CCCR    RANSRC  LL_SYSCFG_SetNMOSVddIO3CompensationCode
  * @param  NMOSCode NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CMPCR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSVddIO3CompensationCode(uint32_t NMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_RANSRC, NMOSCode << SYSCFG_VDDIO3CCCR_RANSRC_Pos);
}


/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDDIO3
  * @rmtoll VDDIO3CCCR    RANSRC   LL_SYSCFG_GetNMOSVddIO3CompensationCode
  * @retval Returned value is the NMOS compensation cell code
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO3CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_RANSRC) >> SYSCFG_VDDIO3CCCR_RANSRC_Pos);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDDIO3
  * @rmtoll VDDIO3CCCR   EN    LL_SYSCFG_EnableVddIO3CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddIO3CompensationCell(void)
{
  SET_BIT(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_EN);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDDIO3
  * @rmtoll VDDIO3CCCR   EN    LL_SYSCFG_DisableVddIO3CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddIO3CompensationCell(void)
{
  CLEAR_BIT(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_EN);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDDIO3 is enable
  * @rmtoll VDDIO3CCCR   EN   LL_SYSCFG_IsEnabled_VddIO3CompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddIO3CompensationCell(void)
{
  return ((READ_BIT(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_EN) == SYSCFG_VDDIO3CCCR_EN) ? 1UL : 0UL);
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDDIO3
  * @rmtoll VDDIO3CCSR   READY   LL_SYSCFG_IsActiveFlag_VddIO3CMPCR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_VddIO3CMPCR(void)
{
  return ((READ_BIT(SYSCFG->VDDIO3CCSR, SYSCFG_VDDIO3CCSR_READY) == (SYSCFG_VDDIO3CCSR_READY)) ? 1UL : 0UL);
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDDIO3
  * @rmtoll VDDIO3CCCR   CS    LL_SYSCFG_SetVddIO3CellCompensationCode
  * @param  CompCode: Selects the code to be applied for the VddIO compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO3_CELL_CODE : Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO3_REGISTER_CODE: Select Code from the SYSCFG compensation cell code register (SYSCFG_CCCR)
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetVddIO3CellCompensationCode(uint32_t CompCode)
{
  SET_BIT(SYSCFG->VDDIO3CCCR, CompCode);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDDIO3
  * @rmtoll VDDIO3CCCR   CS    LL_SYSCFG_GetVddIO3CellCompensationCode
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO3_CELL_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO3_REGISTER_CODE: Selected Code is from the SYSCFG compensation
      cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddIO3CellCompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO3CCCR, SYSCFG_VDDIO3CCCR_CS));
}
/**
  * @brief  Get the compensation cell value of the GPIO PMOS transistor supplied by VDDIO4
  * @rmtoll VDDIO4CCSR  APSRC  LL_SYSCFG_GetPMOSVddIO4CompensationValue
  * @retval Returned value is the PMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO4CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO4CCSR, SYSCFG_VDDIO4CCSR_APSRC) >> SYSCFG_VDDIO4CCSR_APSRC_Pos);
}

/**
  * @brief  Get the compensation cell value of the GPIO NMOS transistor supplied by VDDIO4
  * @rmtoll VDDIO4CCSR  ANSRC   LL_SYSCFG_GetNMOSVddIO4CompensationValue
  * @retval Returned value is the NMOS compensation cell
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO4CompensationValue(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO4CCSR, SYSCFG_VDDIO4CCSR_ANSRC) >> SYSCFG_VDDIO4CCSR_ANSRC_Pos);
}

/**
  * @brief  Set the compensation cell code of the GPIO PMOS transistor supplied by VDDIO4
  * @rmtoll VDDIO4CCCR    RAPSRC  LL_SYSCFG_SetPMOSVddIO4CompensationCode
  * @param  PMOSCode PMOS compensation code
  *         This code is applied to the PMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CCCSR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetPMOSVddIO4CompensationCode(uint32_t PMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_RAPSRC, PMOSCode << SYSCFG_VDDIO4CCCR_RAPSRC_Pos);
}

/**
  * @brief  Get the compensation cell code of the GPIO PMOS transistor supplied by VDDIO4
  * @rmtoll VDDIO4CCCR    RAPSRC   LL_SYSCFG_GetPMOSVddIO4CompensationCode
  * @retval Returned value is the PMOS compensation
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetPMOSVddIO4CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_RAPSRC) >> SYSCFG_VDDIO4CCCR_RAPSRC_Pos);
}


/**
  * @brief  Set the compensation cell code of the GPIO NMOS transistor supplied by VDDIO4
  * @rmtoll VDDIO4CCCR    RANSRC  LL_SYSCFG_SetNMOSVddIO4CompensationCode
  * @param  NMOSCode NMOS compensation code
  *         This code is applied to the NMOS compensation cell when the CS2 bit of the
  *         SYSCFG_CMPCR is set
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetNMOSVddIO4CompensationCode(uint32_t NMOSCode)
{
  MODIFY_REG(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_RANSRC, NMOSCode << SYSCFG_VDDIO4CCCR_RANSRC_Pos);
}


/**
  * @brief  Get the compensation cell code of the GPIO NMOS transistor supplied by VDDIO4
  * @rmtoll VDDIO4CCCR    RANSRC   LL_SYSCFG_GetNMOSVddIO4CompensationCode
  * @retval Returned value is the NMOS compensation cell code
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetNMOSVddIO4CompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_RANSRC) >> SYSCFG_VDDIO4CCCR_RANSRC_Pos);
}

/**
  * @brief  Enable the Compensation Cell of GPIO supplied by VDDIO4
  * @rmtoll VDDIO4CCCR   EN    LL_SYSCFG_EnableVddIO4CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableVddIO4CompensationCell(void)
{
  SET_BIT(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_EN);
}

/**
  * @brief  Disable the Compensation Cell of GPIO supplied by VDDIO4
  * @rmtoll VDDIO4CCCR   EN    LL_SYSCFG_DisableVddIO4CompensationCell
  * @note   The Vdd I/O compensation cell can be used only when the device supply
  *         voltage ranges from 1.08 to 3.6 V
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableVddIO4CompensationCell(void)
{
  CLEAR_BIT(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_EN);
}

/**
  * @brief  Check if the Compensation Cell of GPIO supplied by VDDIO4 is enable
  * @rmtoll VDDIO4CCCR   EN   LL_SYSCFG_IsEnabled_VddIO4CompensationCell
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabled_VddIO4CompensationCell(void)
{
  return ((READ_BIT(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_EN) == SYSCFG_VDDIO4CCCR_EN) ? 1UL : 0UL);
}

/**
  * @brief  Get Compensation Cell ready Flag of GPIO supplied by VDDIO4
  * @rmtoll VDDIO4CCSR   READY   LL_SYSCFG_IsActiveFlag_VddIO4CMPCR
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_VddIO4CMPCR(void)
{
  return ((READ_BIT(SYSCFG->VDDIO4CCSR, SYSCFG_VDDIO4CCSR_READY) == (SYSCFG_VDDIO4CCSR_READY)) ? 1UL : 0UL);
}

/**
  * @brief  Set the compensation cell code selection of GPIO supplied by VDDIO4
  * @rmtoll VDDIO4CCCR   CS    LL_SYSCFG_SetVddIO4CellCompensationCode
  * @param  CompCode: Selects the code to be applied for the VddIO compensation cell
  *   This parameter can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO4_CELL_CODE : Select Code from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO4_REGISTER_CODE: Select Code from the SYSCFG compensation cell code register (SYSCFG_CCCR)
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetVddIO4CellCompensationCode(uint32_t CompCode)
{
  SET_BIT(SYSCFG->VDDIO4CCCR, CompCode);
}

/**
  * @brief  Get the compensation cell code selection of GPIO supplied by VDDIO4
  * @rmtoll VDDIO4CCCR   CS    LL_SYSCFG_GetVddIO4CellCompensationCode
  * @retval Returned value can be one of the following values:
  *   @arg LL_SYSCFG_VDDIO4_CELL_CODE : Selected Code is from the cell (available in the SYSCFG_CCVR)
  *   @arg LL_SYSCFG_VDDIO4_REGISTER_CODE: Selected Code is from the SYSCFG compensation
      cell code register (SYSCFG_CCCR)
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetVddIO4CellCompensationCode(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->VDDIO4CCCR, SYSCFG_VDDIO4CCCR_CS));
}

/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Enable Floating Point Unit Invalid operation Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_0      LL_SYSCFG_EnableIT_FPU_IOC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IOC(void)
{
  SET_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_0);
}

/**
  * @brief  Enable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_1      LL_SYSCFG_EnableIT_FPU_DZC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_DZC(void)
{
  SET_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_1);
}

/**
  * @brief  Enable Floating Point Unit Overflow Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_2      LL_SYSCFG_EnableIT_FPU_OFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_OFC(void)
{
  SET_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_2);
}

/**
  * @brief  Enable Floating Point Unit Underflow Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_3      LL_SYSCFG_EnableIT_FPU_UFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_UFC(void)
{
  SET_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_3);
}

/**
  * @brief  Enable Floating Point Unit Inexact Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_4      LL_SYSCFG_EnableIT_FPU_IXC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IXC(void)
{
  SET_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_4);
}

/**
  * @brief  Enable Floating Point Unit Input abnormal Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_5      LL_SYSCFG_EnableIT_FPU_IDC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableIT_FPU_IDC(void)
{
  SET_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_5);
}

/**
  * @brief  Disable Floating Point Unit Invalid operation Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_0      LL_SYSCFG_DisableIT_FPU_IOC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IOC(void)
{
  CLEAR_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_0);
}

/**
  * @brief  Disable Floating Point Unit Divide-by-zero Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_1      LL_SYSCFG_DisableIT_FPU_DZC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_DZC(void)
{
  CLEAR_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_1);
}

/**
  * @brief  Disable Floating Point Unit Overflow Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_2      LL_SYSCFG_DisableIT_FPU_OFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_OFC(void)
{
  CLEAR_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_2);
}

/**
  * @brief  Disable Floating Point Unit Underflow Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_3      LL_SYSCFG_DisableIT_FPU_UFC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_UFC(void)
{
  CLEAR_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_3);
}

/**
  * @brief  Disable Floating Point Unit Inexact Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_4      LL_SYSCFG_DisableIT_FPU_IXC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IXC(void)
{
  CLEAR_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_4);
}

/**
  * @brief  Disable Floating Point Unit Input abnormal Interrupt
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_5      LL_SYSCFG_DisableIT_FPU_IDC
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableIT_FPU_IDC(void)
{
  CLEAR_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_5);
}

/**
  * @brief  Check whether Floating Point Unit Invalid operation Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_0      LL_SYSCFG_IsEnabledIT_FPU_IOC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IOC(void)
{
  return ((READ_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_0) == SYSCFG_M33SSCR_FPU_IT_EN_0) ? 1UL : 0UL);
}

/**
  * @brief  Check whether Floating Point Unit Divide-by-zero Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_1      LL_SYSCFG_IsEnabledIT_FPU_DZC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_DZC(void)
{
  return ((READ_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_1) == SYSCFG_M33SSCR_FPU_IT_EN_1) ? 1UL : 0UL);
}

/**
  * @brief  Check whether Floating Point Unit Overflow Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_2      LL_SYSCFG_IsEnabledIT_FPU_OFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_OFC(void)
{
  return ((READ_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_2) == SYSCFG_M33SSCR_FPU_IT_EN_2) ? 1UL : 0UL);
}

/**
  * @brief  Check whether Floating Point Unit Underflow Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_3      LL_SYSCFG_IsEnabledIT_FPU_UFC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_UFC(void)
{
  return ((READ_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_3) == SYSCFG_M33SSCR_FPU_IT_EN_3) ? 1UL : 0UL);
}

/**
  * @brief  Check whether Floating Point Unit Inexact Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_4      LL_SYSCFG_IsEnabledIT_FPU_IXC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IXC(void)
{
  return ((READ_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_4) == SYSCFG_M33SSCR_FPU_IT_EN_4) ? 1UL : 0UL);
}

/**
  * @brief  Check whether Floating Point Unit Input abnormal Interrupt source is enabled or disabled.
  * @rmtoll SYSCFG_M33SSCR FPU_IT_EN_5      LL_SYSCFG_IsEnabledIT_FPU_IDC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsEnabledIT_FPU_IDC(void)
{
  return ((READ_BIT(SYSCFG->M33SSCR, SYSCFG_M33SSCR_FPU_IT_EN_5) == SYSCFG_M33SSCR_FPU_IT_EN_5) ? 1UL : 0UL);
}

/**
  * @}
  */

/**
  * @}
  */

#if defined(CORE_CA35) || defined(CORE_CM33)
/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @{
  */

/**
  * @brief  Return the device identifier
  * @note For STM32MP25x devices, the device ID is 0x???
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
          For example, it is read as 0x1000 for Revision 1.0.
  * @rmtoll DBGMCU_IDCODE REV_ID        LL_DBGMCU_GetRevisionID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable the Debug Module during SLEEP mode
  * @rmtoll DBGMCU_CR    DBG_SLEEP      LL_DBGMCU_EnableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode
  * @rmtoll DBGMCU_CR    DBG_SLEEP      LL_DBGMCU_DisableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @rmtoll DBGMCU_CR    DBG_STOP      LL_DBGMCU_EnableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @rmtoll DBGMCU_CR    DBG_STOP      LL_DBGMCU_DisableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @rmtoll DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_EnableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @rmtoll DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_DisableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Set the Watchdog Timer behaviour
  * @rmtoll DBGMCU_CRA35 WDFZCTL   LL_DBGMCU_SetWatchdogTimerBehaviour\n
  * @param  PinBehaviour This parameter can be one of the following values:
  *         @arg @ref LL_DBGMCU_IWDG_FREEZE_1CA35_HALT
  *         @arg @ref LL_DBGMCU_IWDG_FREEZE_2CA35_HALT
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_SetWatchdogTimerBehaviour(uint32_t PinBehaviour)
{
  MODIFY_REG(DBGMCU->CRA35, DBGMCU_CRA35_WDFZCTL, PinBehaviour);
}

/**
  * @brief  Get the Watchdog Timer behaviour
  * @rmtoll DBGMCU_CR   WDFZCTL   LL_DBGMCU_GetWatchdogTimerBehaviour\n
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_DBGMCU_IWDG_FREEZE_1CA35_HALT
  *         @arg @ref LL_DBGMCU_IWDG_FREEZE_2CA35_HALT
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetWatchdogTimerBehaviour(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->CRA35, DBGMCU_CRA35_WDFZCTL));
}

/**
  * @brief  Freeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZ DBG_TIM2_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM3_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM4_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM5_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM6_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM7_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM10_STOP          LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM11_STOP          LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM12_STOP          LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM13_STOP          LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM14_STOP          LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_LPTIM1_STOP         LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_LPTIM2_STOP         LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C1_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C2_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C3_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C4_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C5_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C6_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C7_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I3C1_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I3C2_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I3C3_STOP           LL_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM10_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM11_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM12_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM13_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I3C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I3C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I3C3_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->APB1FZ1, Periphs);
#elif defined (CORE_CM33)
  SET_BIT(DBGMCU->APB1FZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Unfreeze APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZ DBG_TIM2_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM3_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM4_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM5_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM6_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM7_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM10_STOP          LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM11_STOP          LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM12_STOP          LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM13_STOP          LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_TIM14_STOP          LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_LPTIM1_STOP         LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_LPTIM2_STOP         LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C1_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C2_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C3_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C4_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C5_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C6_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I2C7_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I3C1_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I3C2_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB1FZ DBG_I3C3_STOP           LL_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM10_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM11_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM12_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM13_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM14_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C4_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C5_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C6_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C7_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I3C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I3C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I3C3_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->APB1FZ1, Periphs);
#elif defined (CORE_CM33)
  CLEAR_BIT(DBGMCU->APB1FZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Freeze APB2 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB2FZ DBG_TIM1_STOP           LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM8_STOP           LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM15_STOP          LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM16_STOP          LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM17_STOP          LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM20_STOP          LL_DBGMCU_APB2_GRP1_FreezePeriph\n
  *         DBGMCU_APB2FZ DBG_FDCAN_STOP          LL_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM8_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM20_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_FDCAN_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->APB2FZ1, Periphs);
#elif defined (CORE_CM33)
  SET_BIT(DBGMCU->APB2FZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Unfreeze APB2 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB2FZ DBG_TIM1_STOP           LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM8_STOP           LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM15_STOP          LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM16_STOP          LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM17_STOP          LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_TIM20_STOP          LL_DBGMCU_APB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB2FZ DBG_FDCAN_STOP          LL_DBGMCU_APB2_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM8_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM15_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM20_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_FDCAN_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->APB2FZ1, Periphs);
#elif defined (CORE_CM33)
  CLEAR_BIT(DBGMCU->APB2FZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Freeze APB3 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB3FZ_DBG_IWDG1_STOP          LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  *         DBGMCU_APB3FZ DBG_IWDG2_STOP          LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  *         DBGMCU_APB3FZ DBG_IWDG3_STOP          LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  *         DBGMCU_APB3FZ DBG_IWDG4_STOP          LL_DBGMCU_APB3_GRP1_FreezePeriph\n
  *         DBGMCU_APB3FZ DBG_WWDG1_STOP          LL_DBGMCU_APB3_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG1_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG2_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG3_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG4_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_WWDG1_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->APB3FZ1, Periphs);
#elif defined (CORE_CM33)
  SET_BIT(DBGMCU->APB3FZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Unfreeze APB3 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB3FZ_DBG_IWDG1_STOP          LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB3FZ DBG_IWDG2_STOP          LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB3FZ DBG_IWDG3_STOP          LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB3FZ DBG_IWDG4_STOP          LL_DBGMCU_APB3_GRP1_UnFreezePeriph\n
  *         DBGMCU_APB3FZ DBG_WWDG1_STOP          LL_DBGMCU_APB3_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG1_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG2_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG3_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_IWDG4_STOP
  *         @arg @ref LL_DBGMCU_APB3_GRP1_WWDG1_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB3_GRP1_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->APB3FZ1, Periphs);
#elif defined (CORE_CM33)
  CLEAR_BIT(DBGMCU->APB3FZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Freeze APB4 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_CRA35_DBG_STGEN_STOP           LL_DBGMCU_APB4_GRP1_FreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_CRA35_DBG_STGEN_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->CRA35, Periphs);
#endif /*CORE_CA35*/
}

/**
  * @brief  Unfreeze APB4 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_CRA35_DBG_STGEN_STOP           LL_DBGMCU_APB4_GRP1_UnFreezePeriph\n
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_CRA35_DBG_STGEN_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB4_GRP1_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->CRA35, Periphs);
#endif /*CORE_CA35*/
}

/**
  * @brief  Freeze APBSR peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APBSRFZ DBG_RTC_STOP           LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_I2C8_STOP          LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM3_STOP        LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM4_STOP        LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM5_STOP        LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_IWDG5_STOP         LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_WWDG2_STOP         LL_DBGMCU_APBSR_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_I2C8_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_IWDG5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_WWDG2_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APBSR_GRP1_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->APBSRFZ1, Periphs);
#elif defined (CORE_CM33)
  SET_BIT(DBGMCU->APBSRFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

#if defined (CORE_CM33)
/**
  * @brief  Freeze APBSR peripherals (group1 peripherals) for M0+ delegated to M33.
  * @rmtoll DBGMCU_APBSRFZ DBG_RTC_STOP           LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_I2C8_STOP          LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_I3C4_STOP          LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM3_STOP        LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM4_STOP        LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM5_STOP        LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_IWDG5_STOP         LL_DBGMCU_APBSR_GRP1_FreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_WWDG2_STOP         LL_DBGMCU_APBSR_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_I2C8_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_I3C4_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_IWDG5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_WWDG2_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_C3_DBGMCU_APBSR_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APBSRFZ3, Periphs);
}
#endif /* CORE_CM33 */

/**
  * @brief  Unfreeze APBSR peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APBSRFZ DBG_RTC_STOP           LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_I2C8_STOP          LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_I3C4_STOP          LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM3_STOP        LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM4_STOP        LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM5_STOP        LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_IWDG5_STOP         LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_WWDG2_STOP         LL_DBGMCU_APBSR_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_I2C8_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_I3C4_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_IWDG5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_WWDG2_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APBSR_GRP1_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->APBSRFZ1, Periphs);
#elif defined (CORE_CM33)
  CLEAR_BIT(DBGMCU->APBSRFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

#if defined (CORE_CM33)
/**
  * @brief  Unfreeze APBSR peripherals (group1 peripherals) for M0+ delegated to M33.
  * @rmtoll DBGMCU_APBSRFZ DBG_RTC_STOP           LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_I2C8_STOP          LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM3_STOP        LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM4_STOP        LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_LPTIM5_STOP        LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_IWDG5_STOP         LL_DBGMCU_APBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_APBSRFZ DBG_WWDG2_STOP         LL_DBGMCU_APBSR_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_I2C8_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM3_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM4_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_LPTIM5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_IWDG5_STOP
  *         @arg @ref LL_DBGMCU_APBSR_GRP1_WWDG2_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_C3_DBGMCU_APBSR_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APBSRFZ3, Periphs);
}
#endif /* CORE_CM33 */

/**
  * @brief  Freeze AHB2 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHB2LFZ DBG_HPDMA1_CH0_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH1_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH2_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH3_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH4_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH5_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH6_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH7_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH8_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH9_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH10_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH11_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH12_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH13_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH14_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH15_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH0_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH1_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH2_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH3_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH4_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH5_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH6_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH7_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH8_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH9_STOP    LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH10_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH11_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH12_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH13_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH14_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH15_STOP   LL_DBGMCU_AHB2_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH15_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH3_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH4_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH5_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH6_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH7_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH8_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH9_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH10_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH11_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH12_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH13_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH14_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH15_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB2_GRP1_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->AHB2LFZ1, Periphs);
#elif defined (CORE_CM33)
  SET_BIT(DBGMCU->AHB2LFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Unfreeze AHB2 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHB2LFZ DBG_HPDMA1_CH0_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH1_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH2_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH3_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH4_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH5_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH6_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH7_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH8_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH9_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH10_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH11_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH12_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH13_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH14_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA1_CH15_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH0_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH1_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH2_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH3_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH4_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH5_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH6_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH7_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH8_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH9_STOP    LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH10_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH11_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH12_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH13_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH14_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHB2LFZ DBG_HPDMA2_CH15_STOP   LL_DBGMCU_AHB2_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH3_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH4_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH5_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH6_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH7_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH8_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH9_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH10_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH11_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH12_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH13_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH14_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA1_CH15_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH3_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH4_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH5_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH6_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH7_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH8_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH9_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH10_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH11_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH12_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH13_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH14_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP1_HPDMA2_CH15_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB2_GRP1_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->AHB2LFZ1, Periphs);
#elif defined (CORE_CM33)
  CLEAR_BIT(DBGMCU->AHB2LFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Freeze AHB2 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_AHB2HFZ DBG_HPDMA3_CH0_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH1_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH2_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH3_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH4_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH5_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH6_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH7_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH8_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH9_STOP    LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH10_STOP   LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH11_STOP   LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH12_STOP   LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH13_STOP   LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH14_STOP   LL_DBGMCU_AHB2_GRP2_FreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH15_STOP   LL_DBGMCU_AHB2_GRP2_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH3_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH4_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH5_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH6_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH7_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH8_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH9_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH10_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH11_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH12_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH13_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH14_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH15_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB2_GRP2_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->AHB2HFZ1, Periphs);
#elif defined (CORE_CM33)
  SET_BIT(DBGMCU->AHB2HFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Unfreeze AHB2 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_AHB2HFZ DBG_HPDMA3_CH0_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH1_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH2_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH3_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH4_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH5_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH6_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH7_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH8_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH9_STOP    LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH10_STOP   LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH11_STOP   LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH12_STOP   LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH13_STOP   LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH14_STOP   LL_DBGMCU_AHB2_GRP2_UnFreezePeriph\n
  *         DBGMCU_AHB2HFZ DBG_HPDMA3_CH15_STOP   LL_DBGMCU_AHB2_GRP2_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH3_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH4_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH5_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH6_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH7_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH8_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH9_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH10_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH11_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH12_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH13_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH14_STOP
  *         @arg @ref LL_DBGMCU_AHB2_GRP2_HPDMA3_CH15_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHB2_GRP2_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->AHB2HFZ1, Periphs);
#elif defined (CORE_CM33)
  CLEAR_BIT(DBGMCU->AHB2HFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

/**
  * @brief  Freeze AHBSR peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHBSRFZ DBG_LPDMA_CH0_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH1_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH2_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH3_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH3_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHBSR_GRP1_FreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  SET_BIT(DBGMCU->AHBSRFZ1, Periphs);
#elif defined (CORE_CM33)
  SET_BIT(DBGMCU->AHBSRFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

#if defined (CORE_CM33)
/**
  * @brief  Freeze AHBSR peripherals (group1 peripherals) for M0+ delegated to M33.
  * @rmtoll DBGMCU_AHBSRFZ DBG_LPDMA_CH0_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH1_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH2_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH3_STOP     LL_DBGMCU_AHBSR_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH3_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_C3_DBGMCU_AHBSR_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->AHBSRFZ3, Periphs);
}
#endif /* CORE_CM33 */

/**
  * @brief  Unfreeze AHBSR peripherals (group1 peripherals)
  * @rmtoll DBGMCU_AHBSRFZ DBG_LPDMA_CH0_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH1_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH2_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH3_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH3_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph(uint32_t Periphs)
{
#if defined (CORE_CA35)
  CLEAR_BIT(DBGMCU->AHBSRFZ1, Periphs);
#elif defined (CORE_CM33)
  CLEAR_BIT(DBGMCU->AHBSRFZ2, Periphs);
#endif /*CORE_CA35 CORE_CM33*/
}

#if defined (CORE_CM33)
/**
  * @brief  Unfreeze AHBSR peripherals (group1 peripherals) for M0+ delegated to M33.
  * @rmtoll DBGMCU_AHBSRFZ DBG_LPDMA_CH0_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH1_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH2_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph\n
  *         DBGMCU_AHBSRFZ DBG_LPDMA_CH3_STOP     LL_DBGMCU_AHBSR_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH0_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH1_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH2_STOP
  *         @arg @ref LL_DBGMCU_AHBSR_GRP1_LPDMA_CH3_STOP
  *
  *         (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_C3_DBGMCU_AHBSR_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->AHBSRFZ3, Periphs);
}
#endif /* CORE_CM33 */

/**
  * @}
  */
#endif /* CORE_CA35 || CORE_CM33 */


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

#endif /* __STM32MP2xx_LL_SYSTEM_H */
