/**
  ******************************************************************************
  * @file    stm32h5xx_ll_play.h
  * @brief   Header file of PLAY LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_LL_PLAY_H
#define STM32H5xx_LL_PLAY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx.h"

/** @addtogroup STM32H5xx_LL_Driver
  * @{
  */

#if defined(PLAY1)

/** @defgroup PLAY_LL PLAY
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PLAY_LL_Exported_Constants  PLAY Exported Constants
  * @{
  */

/** @defgroup PLAY_LL_EC_LOCK_CONFIG  Lock Configuration Definitions
  * @brief    Configuration definitions which can be used with LL_PLAY_ReadReg and LL_PLAY_WriteReg functions.
  * @{
  */

#define LL_PLAY_CONFIG_LOCK    (0UL)              /*!< Lock Configuration Registers   */
#define LL_PLAY_CONFIG_UNLOCK  PLAY_CFGCR_UNLOCK  /*!< Unlock Configuration Registers */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_INPUT_MULTIPLEXER  Input Multiplexer Definitions
  * @{
  */

#define LL_PLAY_IN0    (0U)  /*!< Input 0             */
#define LL_PLAY_IN1    (1U)  /*!< Input 1             */
#define LL_PLAY_IN2    (2U)  /*!< Input 2             */
#define LL_PLAY_IN3    (3U)  /*!< Input 3             */
#define LL_PLAY_IN4    (4U)  /*!< Input 4             */
#define LL_PLAY_IN5    (5U)  /*!< Input 5             */
#define LL_PLAY_IN6    (6U)  /*!< Input 6             */
#define LL_PLAY_IN7    (7U)  /*!< Input 7             */
#define LL_PLAY_IN8    (8U)  /*!< Input 8             */
#define LL_PLAY_IN9    (9U)  /*!< Input 9             */
#define LL_PLAY_IN10   (10U) /*!< Input 10            */
#define LL_PLAY_IN11   (11U) /*!< Input 11            */
#define LL_PLAY_IN12   (12U) /*!< Input 12            */
#define LL_PLAY_IN13   (13U) /*!< Input 13            */
#define LL_PLAY_IN14   (14U) /*!< Input 14            */
#define LL_PLAY_IN15   (15U) /*!< Input 15            */
#define LL_PLAY_IN_MAX (16U) /*!< Maximum input index */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_LOOKUP_TABLE  Lookup table Definitions
  * @{
  */

/** @defgroup PLAY_LL_EC_LOOKUP_TABLE_INDEX  Lookup table Index Definitions
  * @{
  */

#define LL_PLAY_LUT0    (0U)  /*!< Lookup table 0   */
#define LL_PLAY_LUT1    (1U)  /*!< Lookup table 1   */
#define LL_PLAY_LUT2    (2U)  /*!< Lookup table 2   */
#define LL_PLAY_LUT3    (3U)  /*!< Lookup table 3   */
#define LL_PLAY_LUT4    (4U)  /*!< Lookup table 4   */
#define LL_PLAY_LUT5    (5U)  /*!< Lookup table 5   */
#define LL_PLAY_LUT6    (6U)  /*!< Lookup table 6   */
#define LL_PLAY_LUT7    (7U)  /*!< Lookup table 7   */
#define LL_PLAY_LUT8    (8U)  /*!< Lookup table 8   */
#define LL_PLAY_LUT9    (9U)  /*!< Lookup table 9   */
#define LL_PLAY_LUT10   (10U) /*!< Lookup table 10  */
#define LL_PLAY_LUT11   (11U) /*!< Lookup table 11  */
#define LL_PLAY_LUT12   (12U) /*!< Lookup table 12  */
#define LL_PLAY_LUT13   (13U) /*!< Lookup table 13  */
#define LL_PLAY_LUT14   (14U) /*!< Lookup table 14  */
#define LL_PLAY_LUT15   (15U) /*!< Lookup table 15  */
#define LL_PLAY_LUT_MAX (16U) /*!< Maximum LUT index */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_LOOKUP_TABLE_INPUT  Lookup table Input Definitions
  * @{
  */

#define LL_PLAY_LUT_INPUT0 (0UL) /*!< Lookup table Input 0 */
#define LL_PLAY_LUT_INPUT1 (1UL) /*!< Lookup table Input 1 */
#define LL_PLAY_LUT_INPUT2 (2UL) /*!< Lookup table Input 2 */
#define LL_PLAY_LUT_INPUT3 (3UL) /*!< Lookup table Input 3 */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_LUT_INPUT_SOURCE  Lookup table Input Source Definitions
  * @brief    Lookup table Input Source definitions which can be used with LL_PLAY_WriteReg function.
  * @note      Depending of Lookup table, some LUT direct output sources can not be connected.
  *           For example, configuring the LUT direct output 0 as input of LUT 4 will
  *           have no effect and the input signal will stay always at 0.
  * @{
  */

#define LL_PLAY_LUT_SOURCE_LUT0_OUT_DIRECT      (0x00UL) /*!< LUT direct output 0              */
#define LL_PLAY_LUT_SOURCE_LUT1_OUT_DIRECT      (0x01UL) /*!< LUT direct output 1              */
#define LL_PLAY_LUT_SOURCE_LUT2_OUT_DIRECT      (0x02UL) /*!< LUT direct output 2              */
#define LL_PLAY_LUT_SOURCE_LUT3_OUT_DIRECT      (0x03UL) /*!< LUT direct output 3              */
#define LL_PLAY_LUT_SOURCE_LUT4_OUT_DIRECT      (0x04UL) /*!< LUT direct output 4              */
#define LL_PLAY_LUT_SOURCE_LUT5_OUT_DIRECT      (0x05UL) /*!< LUT direct output 5              */
#define LL_PLAY_LUT_SOURCE_LUT6_OUT_DIRECT      (0x06UL) /*!< LUT direct output 6              */
#define LL_PLAY_LUT_SOURCE_LUT7_OUT_DIRECT      (0x07UL) /*!< LUT direct output 7              */
#define LL_PLAY_LUT_SOURCE_LUT8_OUT_DIRECT      (0x08UL) /*!< LUT direct output 8              */
#define LL_PLAY_LUT_SOURCE_LUT9_OUT_DIRECT      (0x09UL) /*!< LUT direct output 9              */
#define LL_PLAY_LUT_SOURCE_LUT10_OUT_DIRECT     (0x0AUL) /*!< LUT direct output 10             */
#define LL_PLAY_LUT_SOURCE_LUT11_OUT_DIRECT     (0x0BUL) /*!< LUT direct output 11             */
#define LL_PLAY_LUT_SOURCE_LUT12_OUT_DIRECT     (0x0CUL) /*!< LUT direct output 12             */
#define LL_PLAY_LUT_SOURCE_LUT13_OUT_DIRECT     (0x0DUL) /*!< LUT direct output 13             */
#define LL_PLAY_LUT_SOURCE_LUT14_OUT_DIRECT     (0x0EUL) /*!< LUT direct output 14             */
#define LL_PLAY_LUT_SOURCE_LUT15_OUT_DIRECT     (0x0FUL) /*!< LUT direct output 15             */
#define LL_PLAY_LUT_SOURCE_LUT0_OUT_REGISTERED  (0x10UL) /*!< LUT registered output 0          */
#define LL_PLAY_LUT_SOURCE_LUT1_OUT_REGISTERED  (0x11UL) /*!< LUT registered output 1          */
#define LL_PLAY_LUT_SOURCE_LUT2_OUT_REGISTERED  (0x12UL) /*!< LUT registered output 2          */
#define LL_PLAY_LUT_SOURCE_LUT3_OUT_REGISTERED  (0x13UL) /*!< LUT registered output 3          */
#define LL_PLAY_LUT_SOURCE_LUT4_OUT_REGISTERED  (0x14UL) /*!< LUT registered output 4          */
#define LL_PLAY_LUT_SOURCE_LUT5_OUT_REGISTERED  (0x15UL) /*!< LUT registered output 5          */
#define LL_PLAY_LUT_SOURCE_LUT6_OUT_REGISTERED  (0x16UL) /*!< LUT registered output 6          */
#define LL_PLAY_LUT_SOURCE_LUT7_OUT_REGISTERED  (0x17UL) /*!< LUT registered output 7          */
#define LL_PLAY_LUT_SOURCE_LUT8_OUT_REGISTERED  (0x18UL) /*!< LUT registered output 8          */
#define LL_PLAY_LUT_SOURCE_LUT9_OUT_REGISTERED  (0x19UL) /*!< LUT registered output 9          */
#define LL_PLAY_LUT_SOURCE_LUT10_OUT_REGISTERED (0x1AUL) /*!< LUT registered output 10         */
#define LL_PLAY_LUT_SOURCE_LUT11_OUT_REGISTERED (0x1BUL) /*!< LUT registered output 11         */
#define LL_PLAY_LUT_SOURCE_LUT12_OUT_REGISTERED (0x1CUL) /*!< LUT registered output 12         */
#define LL_PLAY_LUT_SOURCE_LUT13_OUT_REGISTERED (0x1DUL) /*!< LUT registered output 13         */
#define LL_PLAY_LUT_SOURCE_LUT14_OUT_REGISTERED (0x1EUL) /*!< LUT registered output 14         */
#define LL_PLAY_LUT_SOURCE_LUT15_OUT_REGISTERED (0x1FUL) /*!< LUT registered output 15         */
#define LL_PLAY_LUT_SOURCE_FILTER0              (0x20UL) /*!< Signal from Input Multiplexer 0  */
#define LL_PLAY_LUT_SOURCE_FILTER1              (0x21UL) /*!< Signal from Input Multiplexer 1  */
#define LL_PLAY_LUT_SOURCE_FILTER2              (0x22UL) /*!< Signal from Input Multiplexer 2  */
#define LL_PLAY_LUT_SOURCE_FILTER3              (0x23UL) /*!< Signal from Input Multiplexer 3  */
#define LL_PLAY_LUT_SOURCE_FILTER4              (0x24UL) /*!< Signal from Input Multiplexer 4  */
#define LL_PLAY_LUT_SOURCE_FILTER5              (0x25UL) /*!< Signal from Input Multiplexer 5  */
#define LL_PLAY_LUT_SOURCE_FILTER6              (0x26UL) /*!< Signal from Input Multiplexer 6  */
#define LL_PLAY_LUT_SOURCE_FILTER7              (0x27UL) /*!< Signal from Input Multiplexer 7  */
#define LL_PLAY_LUT_SOURCE_FILTER8              (0x28UL) /*!< Signal from Input Multiplexer 8  */
#define LL_PLAY_LUT_SOURCE_FILTER9              (0x29UL) /*!< Signal from Input Multiplexer 9  */
#define LL_PLAY_LUT_SOURCE_FILTER10             (0x2AUL) /*!< Signal from Input Multiplexer 10 */
#define LL_PLAY_LUT_SOURCE_FILTER11             (0x2BUL) /*!< Signal from Input Multiplexer 11 */
#define LL_PLAY_LUT_SOURCE_FILTER12             (0x2CUL) /*!< Signal from Input Multiplexer 12 */
#define LL_PLAY_LUT_SOURCE_FILTER13             (0x2DUL) /*!< Signal from Input Multiplexer 13 */
#define LL_PLAY_LUT_SOURCE_FILTER14             (0x2EUL) /*!< Signal from Input Multiplexer 14 */
#define LL_PLAY_LUT_SOURCE_FILTER15             (0x2FUL) /*!< Signal from Input Multiplexer 15 */
#define LL_PLAY_LUT_SOURCE_SWTRIG0              (0x30UL) /*!< Software Trigger 0               */
#define LL_PLAY_LUT_SOURCE_SWTRIG1              (0x31UL) /*!< Software Trigger 1               */
#define LL_PLAY_LUT_SOURCE_SWTRIG2              (0x32UL) /*!< Software Trigger 2               */
#define LL_PLAY_LUT_SOURCE_SWTRIG3              (0x33UL) /*!< Software Trigger 3               */
#define LL_PLAY_LUT_SOURCE_SWTRIG4              (0x34UL) /*!< Software Trigger 4               */
#define LL_PLAY_LUT_SOURCE_SWTRIG5              (0x35UL) /*!< Software Trigger 5               */
#define LL_PLAY_LUT_SOURCE_SWTRIG6              (0x36UL) /*!< Software Trigger 6               */
#define LL_PLAY_LUT_SOURCE_SWTRIG7              (0x37UL) /*!< Software Trigger 7               */
#define LL_PLAY_LUT_SOURCE_SWTRIG8              (0x38UL) /*!< Software Trigger 8               */
#define LL_PLAY_LUT_SOURCE_SWTRIG9              (0x39UL) /*!< Software Trigger 9               */
#define LL_PLAY_LUT_SOURCE_SWTRIG10             (0x3AUL) /*!< Software Trigger 10              */
#define LL_PLAY_LUT_SOURCE_SWTRIG11             (0x3BUL) /*!< Software Trigger 11              */
#define LL_PLAY_LUT_SOURCE_SWTRIG12             (0x3CUL) /*!< Software Trigger 12              */
#define LL_PLAY_LUT_SOURCE_SWTRIG13             (0x3DUL) /*!< Software Trigger 13              */
#define LL_PLAY_LUT_SOURCE_SWTRIG14             (0x3EUL) /*!< Software Trigger 14              */
#define LL_PLAY_LUT_SOURCE_SWTRIG15             (0x3FUL) /*!< Software Trigger 15              */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_CLOCK_ENABLE  PLAY Lookup table Clock Enable Definitions
  * @brief    Clock Enable definitions which can be used with LL_PLAY_WriteReg function.
  * @{
  */

#define LL_PLAY_LUT_CLK_GATE_OFF                  (0x00UL) /*!< Clock disabled                   */
#define LL_PLAY_LUT_CLK_GATE_ON                   (0x01UL) /*!< Clock always enabled             */
#define LL_PLAY_LUT_CLK_GATE_SW_ACK               (0x02UL) /*!< SWIN WE signal                   */
#define LL_PLAY_LUT_CLK_GATE_LUT0_OUT_REGISTERED  (0x10UL) /*!< LUT registered output 0          */
#define LL_PLAY_LUT_CLK_GATE_LUT1_OUT_REGISTERED  (0x11UL) /*!< LUT registered output 1          */
#define LL_PLAY_LUT_CLK_GATE_LUT2_OUT_REGISTERED  (0x12UL) /*!< LUT registered output 2          */
#define LL_PLAY_LUT_CLK_GATE_LUT3_OUT_REGISTERED  (0x13UL) /*!< LUT registered output 3          */
#define LL_PLAY_LUT_CLK_GATE_LUT4_OUT_REGISTERED  (0x14UL) /*!< LUT registered output 4          */
#define LL_PLAY_LUT_CLK_GATE_LUT5_OUT_REGISTERED  (0x15UL) /*!< LUT registered output 5          */
#define LL_PLAY_LUT_CLK_GATE_LUT6_OUT_REGISTERED  (0x16UL) /*!< LUT registered output 6          */
#define LL_PLAY_LUT_CLK_GATE_LUT7_OUT_REGISTERED  (0x17UL) /*!< LUT registered output 7          */
#define LL_PLAY_LUT_CLK_GATE_LUT8_OUT_REGISTERED  (0x18UL) /*!< LUT registered output 8          */
#define LL_PLAY_LUT_CLK_GATE_LUT9_OUT_REGISTERED  (0x19UL) /*!< LUT registered output 9          */
#define LL_PLAY_LUT_CLK_GATE_LUT10_OUT_REGISTERED (0x1AUL) /*!< LUT registered output 10         */
#define LL_PLAY_LUT_CLK_GATE_LUT11_OUT_REGISTERED (0x1BUL) /*!< LUT registered output 11         */
#define LL_PLAY_LUT_CLK_GATE_LUT12_OUT_REGISTERED (0x1CUL) /*!< LUT registered output 12         */
#define LL_PLAY_LUT_CLK_GATE_LUT13_OUT_REGISTERED (0x1DUL) /*!< LUT registered output 13         */
#define LL_PLAY_LUT_CLK_GATE_LUT14_OUT_REGISTERED (0x1EUL) /*!< LUT registered output 14         */
#define LL_PLAY_LUT_CLK_GATE_LUT15_OUT_REGISTERED (0x1FUL) /*!< LUT registered output 15         */
#define LL_PLAY_LUT_CLK_GATE_FILTER0              (0x20UL) /*!< Signal from Input Multiplexer 0  */
#define LL_PLAY_LUT_CLK_GATE_FILTER1              (0x21UL) /*!< Signal from Input Multiplexer 1  */
#define LL_PLAY_LUT_CLK_GATE_FILTER2              (0x22UL) /*!< Signal from Input Multiplexer 2  */
#define LL_PLAY_LUT_CLK_GATE_FILTER3              (0x23UL) /*!< Signal from Input Multiplexer 3  */
#define LL_PLAY_LUT_CLK_GATE_FILTER4              (0x24UL) /*!< Signal from Input Multiplexer 4  */
#define LL_PLAY_LUT_CLK_GATE_FILTER5              (0x25UL) /*!< Signal from Input Multiplexer 5  */
#define LL_PLAY_LUT_CLK_GATE_FILTER6              (0x26UL) /*!< Signal from Input Multiplexer 6  */
#define LL_PLAY_LUT_CLK_GATE_FILTER7              (0x27UL) /*!< Signal from Input Multiplexer 7  */
#define LL_PLAY_LUT_CLK_GATE_FILTER8              (0x28UL) /*!< Signal from Input Multiplexer 8  */
#define LL_PLAY_LUT_CLK_GATE_FILTER9              (0x29UL) /*!< Signal from Input Multiplexer 9  */
#define LL_PLAY_LUT_CLK_GATE_FILTER10             (0x2AUL) /*!< Signal from Input Multiplexer 10 */
#define LL_PLAY_LUT_CLK_GATE_FILTER11             (0x2BUL) /*!< Signal from Input Multiplexer 11 */
#define LL_PLAY_LUT_CLK_GATE_FILTER12             (0x2CUL) /*!< Signal from Input Multiplexer 12 */
#define LL_PLAY_LUT_CLK_GATE_FILTER13             (0x2DUL) /*!< Signal from Input Multiplexer 13 */
#define LL_PLAY_LUT_CLK_GATE_FILTER14             (0x2EUL) /*!< Signal from Input Multiplexer 14 */
#define LL_PLAY_LUT_CLK_GATE_FILTER15             (0x2FUL) /*!< Signal from Input Multiplexer 15 */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG0              (0x30UL) /*!< Software Trigger 0               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG1              (0x31UL) /*!< Software Trigger 1               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG2              (0x32UL) /*!< Software Trigger 2               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG3              (0x33UL) /*!< Software Trigger 3               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG4              (0x34UL) /*!< Software Trigger 4               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG5              (0x35UL) /*!< Software Trigger 5               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG6              (0x36UL) /*!< Software Trigger 6               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG7              (0x37UL) /*!< Software Trigger 7               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG8              (0x38UL) /*!< Software Trigger 8               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG9              (0x39UL) /*!< Software Trigger 9               */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG10             (0x3AUL) /*!< Software Trigger 10              */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG11             (0x3BUL) /*!< Software Trigger 11              */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG12             (0x3CUL) /*!< Software Trigger 12              */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG13             (0x3DUL) /*!< Software Trigger 13              */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG14             (0x3EUL) /*!< Software Trigger 14              */
#define LL_PLAY_LUT_CLK_GATE_SWTRIG15             (0x3FUL) /*!< Software Trigger 15              */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_OUTPUT  Output Definitions
  * @{
  */

/** @defgroup PLAY_LL_EC_OUTPUT_MULTIPLEXER  Output Multiplexer Definitions
  * @{
  */

#define LL_PLAY_OUT0    (0U)  /*!< Output 0             */
#define LL_PLAY_OUT1    (1U)  /*!< Output 1             */
#define LL_PLAY_OUT2    (2U)  /*!< Output 2             */
#define LL_PLAY_OUT3    (3U)  /*!< Output 3             */
#define LL_PLAY_OUT4    (4U)  /*!< Output 4             */
#define LL_PLAY_OUT5    (5U)  /*!< Output 5             */
#define LL_PLAY_OUT6    (6U)  /*!< Output 6             */
#define LL_PLAY_OUT7    (7U)  /*!< Output 7             */
#define LL_PLAY_OUT8    (8U)  /*!< Output 8             */
#define LL_PLAY_OUT9    (9U)  /*!< Output 9             */
#define LL_PLAY_OUT10   (10U) /*!< Output 10            */
#define LL_PLAY_OUT11   (11U) /*!< Output 11            */
#define LL_PLAY_OUT12   (12U) /*!< Output 12            */
#define LL_PLAY_OUT13   (13U) /*!< Output 13            */
#define LL_PLAY_OUT14   (14U) /*!< Output 14            */
#define LL_PLAY_OUT15   (15U) /*!< Output 15            */
#define LL_PLAY_OUT_MAX (16U) /*!< Maximum output index */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_LUT_OUTPUT  Lookup table Output Definitions
  * @{
  */

#define LL_PLAY_LUT0_OUT_DIRECT  PLAY_OSR_LEOUTD0  /*!< LUT direct output 0  */
#define LL_PLAY_LUT1_OUT_DIRECT  PLAY_OSR_LEOUTD1  /*!< LUT direct output 1  */
#define LL_PLAY_LUT2_OUT_DIRECT  PLAY_OSR_LEOUTD2  /*!< LUT direct output 2  */
#define LL_PLAY_LUT3_OUT_DIRECT  PLAY_OSR_LEOUTD3  /*!< LUT direct output 3  */
#define LL_PLAY_LUT4_OUT_DIRECT  PLAY_OSR_LEOUTD4  /*!< LUT direct output 4  */
#define LL_PLAY_LUT5_OUT_DIRECT  PLAY_OSR_LEOUTD5  /*!< LUT direct output 5  */
#define LL_PLAY_LUT6_OUT_DIRECT  PLAY_OSR_LEOUTD6  /*!< LUT direct output 6  */
#define LL_PLAY_LUT7_OUT_DIRECT  PLAY_OSR_LEOUTD7  /*!< LUT direct output 7  */
#define LL_PLAY_LUT8_OUT_DIRECT  PLAY_OSR_LEOUTD8  /*!< LUT direct output 8  */
#define LL_PLAY_LUT9_OUT_DIRECT  PLAY_OSR_LEOUTD9  /*!< LUT direct output 9  */
#define LL_PLAY_LUT10_OUT_DIRECT PLAY_OSR_LEOUTD10 /*!< LUT direct output 10 */
#define LL_PLAY_LUT11_OUT_DIRECT PLAY_OSR_LEOUTD11 /*!< LUT direct output 11 */
#define LL_PLAY_LUT12_OUT_DIRECT PLAY_OSR_LEOUTD12 /*!< LUT direct output 12 */
#define LL_PLAY_LUT13_OUT_DIRECT PLAY_OSR_LEOUTD13 /*!< LUT direct output 13 */
#define LL_PLAY_LUT14_OUT_DIRECT PLAY_OSR_LEOUTD14 /*!< LUT direct output 14 */
#define LL_PLAY_LUT15_OUT_DIRECT PLAY_OSR_LEOUTD15 /*!< LUT direct output 15 */

/*! All LUT direct output */
#define LL_PLAY_LUT_ALL_OUT_DIRECT \
  (LL_PLAY_LUT0_OUT_DIRECT         \
   | LL_PLAY_LUT1_OUT_DIRECT       \
   | LL_PLAY_LUT2_OUT_DIRECT       \
   | LL_PLAY_LUT3_OUT_DIRECT       \
   | LL_PLAY_LUT4_OUT_DIRECT       \
   | LL_PLAY_LUT5_OUT_DIRECT       \
   | LL_PLAY_LUT6_OUT_DIRECT       \
   | LL_PLAY_LUT7_OUT_DIRECT       \
   | LL_PLAY_LUT8_OUT_DIRECT       \
   | LL_PLAY_LUT9_OUT_DIRECT       \
   | LL_PLAY_LUT10_OUT_DIRECT      \
   | LL_PLAY_LUT11_OUT_DIRECT      \
   | LL_PLAY_LUT12_OUT_DIRECT      \
   | LL_PLAY_LUT13_OUT_DIRECT      \
   | LL_PLAY_LUT14_OUT_DIRECT      \
   | LL_PLAY_LUT15_OUT_DIRECT)

#define LL_PLAY_LUT0_OUT_REGISTERED  PLAY_OSR_LEOUTR0  /*!< LUT registered output 0  */
#define LL_PLAY_LUT1_OUT_REGISTERED  PLAY_OSR_LEOUTR1  /*!< LUT registered output 1  */
#define LL_PLAY_LUT2_OUT_REGISTERED  PLAY_OSR_LEOUTR2  /*!< LUT registered output 2  */
#define LL_PLAY_LUT3_OUT_REGISTERED  PLAY_OSR_LEOUTR3  /*!< LUT registered output 3  */
#define LL_PLAY_LUT4_OUT_REGISTERED  PLAY_OSR_LEOUTR4  /*!< LUT registered output 4  */
#define LL_PLAY_LUT5_OUT_REGISTERED  PLAY_OSR_LEOUTR5  /*!< LUT registered output 5  */
#define LL_PLAY_LUT6_OUT_REGISTERED  PLAY_OSR_LEOUTR6  /*!< LUT registered output 6  */
#define LL_PLAY_LUT7_OUT_REGISTERED  PLAY_OSR_LEOUTR7  /*!< LUT registered output 7  */
#define LL_PLAY_LUT8_OUT_REGISTERED  PLAY_OSR_LEOUTR8  /*!< LUT registered output 8  */
#define LL_PLAY_LUT9_OUT_REGISTERED  PLAY_OSR_LEOUTR9  /*!< LUT registered output 9  */
#define LL_PLAY_LUT10_OUT_REGISTERED PLAY_OSR_LEOUTR10 /*!< LUT registered output 10 */
#define LL_PLAY_LUT11_OUT_REGISTERED PLAY_OSR_LEOUTR11 /*!< LUT registered output 11 */
#define LL_PLAY_LUT12_OUT_REGISTERED PLAY_OSR_LEOUTR12 /*!< LUT registered output 12 */
#define LL_PLAY_LUT13_OUT_REGISTERED PLAY_OSR_LEOUTR13 /*!< LUT registered output 13 */
#define LL_PLAY_LUT14_OUT_REGISTERED PLAY_OSR_LEOUTR14 /*!< LUT registered output 14 */
#define LL_PLAY_LUT15_OUT_REGISTERED PLAY_OSR_LEOUTR15 /*!< LUT registered output 15 */

/*! All LUT registered output */
#define LL_PLAY_LUT_ALL_OUT_REGISTERED \
  (LL_PLAY_LUT0_OUT_REGISTERED         \
   | LL_PLAY_LUT1_OUT_REGISTERED       \
   | LL_PLAY_LUT2_OUT_REGISTERED       \
   | LL_PLAY_LUT3_OUT_REGISTERED       \
   | LL_PLAY_LUT4_OUT_REGISTERED       \
   | LL_PLAY_LUT5_OUT_REGISTERED       \
   | LL_PLAY_LUT6_OUT_REGISTERED       \
   | LL_PLAY_LUT7_OUT_REGISTERED       \
   | LL_PLAY_LUT8_OUT_REGISTERED       \
   | LL_PLAY_LUT9_OUT_REGISTERED       \
   | LL_PLAY_LUT10_OUT_REGISTERED      \
   | LL_PLAY_LUT11_OUT_REGISTERED      \
   | LL_PLAY_LUT12_OUT_REGISTERED      \
   | LL_PLAY_LUT13_OUT_REGISTERED      \
   | LL_PLAY_LUT14_OUT_REGISTERED      \
   | LL_PLAY_LUT15_OUT_REGISTERED)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_SW_TRIGGER  Software Trigger Definitions
  *  @brief   Software Trigger definitions which can be used with LL_PLAY_ReadReg and LL_PLAY_WriteReg functions.
  * @{
  */

#define LL_PLAY_SWTRIG0  PLAY_SWIN_SWIN0  /*!< Software Trigger 0  */
#define LL_PLAY_SWTRIG1  PLAY_SWIN_SWIN1  /*!< Software Trigger 1  */
#define LL_PLAY_SWTRIG2  PLAY_SWIN_SWIN2  /*!< Software Trigger 2  */
#define LL_PLAY_SWTRIG3  PLAY_SWIN_SWIN3  /*!< Software Trigger 3  */
#define LL_PLAY_SWTRIG4  PLAY_SWIN_SWIN4  /*!< Software Trigger 4  */
#define LL_PLAY_SWTRIG5  PLAY_SWIN_SWIN5  /*!< Software Trigger 5  */
#define LL_PLAY_SWTRIG6  PLAY_SWIN_SWIN6  /*!< Software Trigger 6  */
#define LL_PLAY_SWTRIG7  PLAY_SWIN_SWIN7  /*!< Software Trigger 7  */
#define LL_PLAY_SWTRIG8  PLAY_SWIN_SWIN8  /*!< Software Trigger 8  */
#define LL_PLAY_SWTRIG9  PLAY_SWIN_SWIN9  /*!< Software Trigger 9  */
#define LL_PLAY_SWTRIG10 PLAY_SWIN_SWIN10 /*!< Software Trigger 10 */
#define LL_PLAY_SWTRIG11 PLAY_SWIN_SWIN11 /*!< Software Trigger 11 */
#define LL_PLAY_SWTRIG12 PLAY_SWIN_SWIN12 /*!< Software Trigger 12 */
#define LL_PLAY_SWTRIG13 PLAY_SWIN_SWIN13 /*!< Software Trigger 13 */
#define LL_PLAY_SWTRIG14 PLAY_SWIN_SWIN14 /*!< Software Trigger 14 */
#define LL_PLAY_SWTRIG15 PLAY_SWIN_SWIN15 /*!< Software Trigger 15 */

/*! All Software Triggers */
#define LL_PLAY_SWTRIG_ALL \
  (LL_PLAY_SWTRIG0         \
   | LL_PLAY_SWTRIG1       \
   | LL_PLAY_SWTRIG2       \
   | LL_PLAY_SWTRIG3       \
   | LL_PLAY_SWTRIG4       \
   | LL_PLAY_SWTRIG5       \
   | LL_PLAY_SWTRIG6       \
   | LL_PLAY_SWTRIG7       \
   | LL_PLAY_SWTRIG8       \
   | LL_PLAY_SWTRIG9       \
   | LL_PLAY_SWTRIG10      \
   | LL_PLAY_SWTRIG11      \
   | LL_PLAY_SWTRIG12      \
   | LL_PLAY_SWTRIG13      \
   | LL_PLAY_SWTRIG14      \
   | LL_PLAY_SWTRIG15)

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_GET_FLAG  Get Flags Definitions
  * @brief    Flags definitions which can be used with LL_PLAY_ReadReg function.
  * @{
  */

#define LL_PLAY_ISR_SWINWC     PLAY_ISR_SWINWC     /*!< Software Trigger write complete               */
#define LL_PLAY_ISR_FLCTLWC    PLAY_ISR_FLCTLWC    /*!< Edge Trigger write complete                   */
#define LL_PLAY_ISR_FLAGS      PLAY_ISR_FLAGS      /*!< One or more bits in FLSTAT register is active */
#define LL_PLAY_MSR_SWINWBFS   PLAY_MSR_SWINWBFS   /*!< Software Trigger write busy                   */
#define LL_PLAY_MSR_FLCTLWBFS  PLAY_MSR_FLCTLWBFS  /*!< Edge Trigger write busy                       */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_IT  IT Definitions
  * @brief    IT definitions which can be used with LL_PLAY_ReadReg and LL_PLAY_WriteReg functions
  * @{
  */

#define LL_PLAY_IER_SWINWC_IEN   PLAY_IER_SWINWC_IEN   /*!< Software Trigger write complete */
#define LL_PLAY_IER_FLCTLWC_IEN  PLAY_IER_FLCTLWC_IEN  /*!< Edge Trigger write complete     */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_EDGE_TRIGGER_TRANSITION  Output edge trigger transition
  * @{
  */

#define LL_PLAY_LUT_EDGE_TRIGGER_FALLING  (0x00000000UL) /*!< Falling edge trigger  */
#define LL_PLAY_LUT_EDGE_TRIGGER_RISING   (0xFFFFFFFFUL) /*!< Rising edge trigger   */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_FILTER_EDGE_DETECTION_MODE  Input Filter Detection Mode Definitions
  * @{
  */

#define LL_PLAY_EDGE_DETECTION_MODE_BYPASSED        (0U)                        /*!< Bypassed mode: No edge detection            */
#define LL_PLAY_EDGE_DETECTION_MODE_RISING          (PLAY_FILTxCFG_EDGEDET_0)   /*!< Rising edge detection mode                  */
#define LL_PLAY_EDGE_DETECTION_MODE_FALLING         (PLAY_FILTxCFG_EDGEDET_1)   /*!< Falling edge detection mode                 */
#define LL_PLAY_EDGE_DETECTION_MODE_RISING_FALLING  (PLAY_FILTxCFG_EDGEDET_0 \
                                                     | PLAY_FILTxCFG_EDGEDET_1) /*!< Both rising and falling edge detection mode */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_TRUSTZONE_ATTRIBUTES  TrustZone Attributes Definitions
  * @{
  */

#define LL_PLAY_NPRIV        (0U)                                          /*!< Non-Privileged mode           */
#define LL_PLAY_CONFIG_PRIV  (PLAY_PRIVCFGR_PRIV_0)                        /*!< Configuration Privileged mode */
#define LL_PLAY_FULL_PRIV    (PLAY_PRIVCFGR_PRIV_0 | PLAY_PRIVCFGR_PRIV_1) /*!< Full Privileged mode          */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define LL_PLAY_NSEC         (0U)                                          /*!< Non-Secure mode               */
#define LL_PLAY_CONFIG_SEC   (PLAY_SECCFGR_SEC_0)                          /*!< Configuration Secure mode     */
#define LL_PLAY_FULL_SEC     (PLAY_SECCFGR_SEC_0 | PLAY_SECCFGR_SEC_1)     /*!< Full Secure mode              */

#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup PLAY_LL_EC_GLOBAL Global constants
  * @{
  */

#define LL_PLAY_LUT_INPUT_SOURCE_NBR         (4U)                                                         /*!< Number of input sources per lookup table */
#define LL_PLAY_LUT_TRUTH_TABLE_VALUE_MAX    (PLAY_LExCFG1_LUT_Msk >> PLAY_LExCFG1_LUT_Pos)               /*!< Maximal Lookup table value               */
#define LL_PLAY_INPUT_FILTER_WIDTH_VALUE_MAX (PLAY_FILTxCFG_WIDTH_Msk >> PLAY_FILTxCFG_WIDTH_Pos)         /*!< Maximal pulse width value                */
#define LL_PLAY_IN_SRC_VALUE_MAX             (PLAY_FILTxCFG_PREMUXSEL_Msk >> PLAY_FILTxCFG_PREMUXSEL_Pos) /*!< Max value of premux_sel field            */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PLAY_LL_EM_WRITE_READ  Common Write and Read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PLAY register.
  * @param  instance PLAY Instance.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_PLAY_WRITE_REG(instance, reg, value)  WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in PLAY register.
  * @param  instance PLAY Instance.
  * @param  reg      Register to be read.
  * @return Register value.
  */
#define LL_PLAY_READ_REG(instance, reg)  READ_REG((instance)->reg)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PLAY_LL_Exported_Functions  PLAY Exported Functions
  * @{
  */

/** @defgroup PLAY_LL_EF_Configuration  Configuration functions
  * @{
  */

/**
  * @brief  Configure the filter of a Logic Array input.
  * @rmtoll FILTxCFG          PREMUXSEL     LL_PLAY_INPUT_Config\n
  *         FILTxCFG          EDGEDET       LL_PLAY_INPUT_Config\n
  *         FILTxCFG          WIDTH         LL_PLAY_INPUT_Config
  * @param  playx     PLAY Instance.
  * @param  input_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_IN0
  *         @arg @ref LL_PLAY_IN1
  *         @arg @ref LL_PLAY_IN2
  *         @arg @ref LL_PLAY_IN3
  *         @arg @ref LL_PLAY_IN4
  *         @arg @ref LL_PLAY_IN5
  *         @arg @ref LL_PLAY_IN6
  *         @arg @ref LL_PLAY_IN7
  *         @arg @ref LL_PLAY_IN8
  *         @arg @ref LL_PLAY_IN9
  *         @arg @ref LL_PLAY_IN10
  *         @arg @ref LL_PLAY_IN11
  *         @arg @ref LL_PLAY_IN12
  *         @arg @ref LL_PLAY_IN13
  *         @arg @ref LL_PLAY_IN14
  *         @arg @ref LL_PLAY_IN15
  * @param  premuxsel_value     Value in range [0..7].
  * @param  edge_detection_mode Value can be one of the following values:
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_BYPASSED
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_RISING
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_FALLING
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_RISING_FALLING
  * @param  min_pulse_width Value in range 0x0000 to 0x00FF.
  * @note   This function set all parameters of a Logic Array input.
  *         These parameters can also be set individually using
  *         dedicated functions:
  *         - @ref LL_PLAY_INPUT_SetMinimumPulseWidth()
  *         - @ref LL_PLAY_INPUT_SetSource()
  *         - @ref LL_PLAY_INPUT_SetEdgeDetectionMode()
  */
__STATIC_INLINE void LL_PLAY_INPUT_Config(PLAY_TypeDef *playx,
                                          uint32_t input_mux, uint32_t premuxsel_value,
                                          uint32_t edge_detection_mode, uint32_t min_pulse_width)
{
  MODIFY_REG(playx->FILTCFG[input_mux & 0x0FU],
             (PLAY_FILTxCFG_WIDTH | PLAY_FILTxCFG_EDGEDET | PLAY_FILTxCFG_PREMUXSEL),
             ((min_pulse_width << PLAY_FILTxCFG_WIDTH_Pos) | edge_detection_mode
              | (premuxsel_value << PLAY_FILTxCFG_PREMUXSEL_Pos)));
}

/**
  * @brief  Configure the inputs and the clock enable of a LUT.
  * @rmtoll LExCFG2          IN_0_SEL     LL_PLAY_LUT_ConfigInputs\n
  *         LExCFG2          IN_1_SEL     LL_PLAY_LUT_ConfigInputs\n
  *         LExCFG2          IN_2_SEL     LL_PLAY_LUT_ConfigInputs\n
  *         LExCFG2          IN_3_SEL     LL_PLAY_LUT_ConfigInputs
  * @param  playx  PLAY Instance.
  * @param  lut    Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0
  *         @arg @ref LL_PLAY_LUT1
  *         @arg @ref LL_PLAY_LUT2
  *         @arg @ref LL_PLAY_LUT3
  *         @arg @ref LL_PLAY_LUT4
  *         @arg @ref LL_PLAY_LUT5
  *         @arg @ref LL_PLAY_LUT6
  *         @arg @ref LL_PLAY_LUT7
  *         @arg @ref LL_PLAY_LUT8
  *         @arg @ref LL_PLAY_LUT9
  *         @arg @ref LL_PLAY_LUT10
  *         @arg @ref LL_PLAY_LUT11
  *         @arg @ref LL_PLAY_LUT12
  *         @arg @ref LL_PLAY_LUT13
  *         @arg @ref LL_PLAY_LUT14
  *         @arg @ref LL_PLAY_LUT15
  * @param  source_sel0 Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER0
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER1
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER2
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER3
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER4
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER5
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER6
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER7
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER8
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER9
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER10
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER11
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER12
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER13
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER14
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER15
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG0
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG1
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG2
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG3
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG4
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG5
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG6
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG7
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG8
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG9
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG10
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG11
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG12
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG13
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG14
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG15
  * @param  source_sel1 Value can be one of the values listed for source_sel0.
  * @param  source_sel2 Value can be one of the values listed for source_sel0.
  * @param  source_sel3 Value can be one of the values listed for source_sel0.
  * @param  clk_enable Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_OFF
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_ON
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SW_ACK
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER0
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER1
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER2
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER3
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER4
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER5
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER6
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER7
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER8
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER9
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER10
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER11
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER12
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER13
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER14
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER15
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG0
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG1
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG2
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG3
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG4
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG5
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG6
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG7
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG8
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG9
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG10
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG11
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG12
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG13
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG14
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG15
  * @note   This function set some parameters of a LUT.
  *         These parameters can also be set individually using
  *         dedicated functions:
  *         - @ref LL_PLAY_LUT_SetSource()
  *         - @ref LL_PLAY_LUT_SetClockGate()
  */
__STATIC_INLINE void LL_PLAY_LUT_ConfigInputs(PLAY_TypeDef *playx, uint32_t lut,
                                              uint32_t source_sel0, uint32_t source_sel1,
                                              uint32_t source_sel2, uint32_t source_sel3,
                                              uint32_t clk_enable)
{
  MODIFY_REG(playx->LECFG2[lut],
             (PLAY_LExCFG2_IN0_SEL | PLAY_LExCFG2_IN1_SEL | PLAY_LExCFG2_IN2_SEL | PLAY_LExCFG2_IN3_SEL
              | PLAY_LExCFG2_CK_SEL),
             ((source_sel0 << PLAY_LExCFG2_IN0_SEL_Pos) | (source_sel1 << PLAY_LExCFG2_IN1_SEL_Pos)
              | (source_sel2 << PLAY_LExCFG2_IN2_SEL_Pos) | (source_sel3 << PLAY_LExCFG2_IN3_SEL_Pos)
              | (clk_enable << PLAY_LExCFG2_CK_SEL_Pos)));
}

/**
  * @brief  Lock the Configuration registers.
  * @rmtoll CFGCR        UNLOCK        LL_PLAY_Lock
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_Lock(PLAY_TypeDef *playx)
{
  CLEAR_BIT(playx->CFGCR, PLAY_CFGCR_UNLOCK);
}

/**
  * @brief  Unlock the Configuration registers.
  * @rmtoll CFGCR        UNLOCK        LL_PLAY_Unlock
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_Unlock(PLAY_TypeDef *playx)
{
  SET_BIT(playx->CFGCR, PLAY_CFGCR_UNLOCK);
}

/**
  * @brief  Indicates whether the PLAY Configuration registers are locked.
  * @rmtoll CFGCR          UNLOCK        LL_PLAY_IsLocked
  * @param  playx PLAY Instance.
  * @return Status of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsLocked(const PLAY_TypeDef *playx)
{
  return (((READ_BIT(playx->CFGCR, PLAY_CFGCR_UNLOCK) == PLAY_CFGCR_UNLOCK) ? 0UL : 1UL));
}

/**
  * @brief  Configure Minimum Pulse Width of an input filter.
  * @rmtoll FILTxCFG          WIDTH          LL_PLAY_INPUT_SetMinimumPulseWidth
  * @param  playx     PLAY Instance.
  * @param  input_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_IN0
  *         @arg @ref LL_PLAY_IN1
  *         @arg @ref LL_PLAY_IN2
  *         @arg @ref LL_PLAY_IN3
  *         @arg @ref LL_PLAY_IN4
  *         @arg @ref LL_PLAY_IN5
  *         @arg @ref LL_PLAY_IN6
  *         @arg @ref LL_PLAY_IN7
  *         @arg @ref LL_PLAY_IN8
  *         @arg @ref LL_PLAY_IN9
  *         @arg @ref LL_PLAY_IN10
  *         @arg @ref LL_PLAY_IN11
  *         @arg @ref LL_PLAY_IN12
  *         @arg @ref LL_PLAY_IN13
  *         @arg @ref LL_PLAY_IN14
  *         @arg @ref LL_PLAY_IN15
  * @param  min_pulse_width Value in range 0x0000 to 0x00FF.
  */
__STATIC_INLINE void LL_PLAY_INPUT_SetMinimumPulseWidth(PLAY_TypeDef *playx, uint32_t input_mux,
                                                        uint32_t min_pulse_width)
{
  MODIFY_REG(playx->FILTCFG[input_mux & 0x0FU], PLAY_FILTxCFG_WIDTH, (min_pulse_width << PLAY_FILTxCFG_WIDTH_Pos));
}

/**
  * @brief  Get the Minimum Pulse Width.
  * @rmtoll FILTxCFG          WIDTH          LL_PLAY_INPUT_GetMinimumPulseWidth
  * @param  playx     PLAY Instance.
  * @param  input_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_IN0
  *         @arg @ref LL_PLAY_IN1
  *         @arg @ref LL_PLAY_IN2
  *         @arg @ref LL_PLAY_IN3
  *         @arg @ref LL_PLAY_IN4
  *         @arg @ref LL_PLAY_IN5
  *         @arg @ref LL_PLAY_IN6
  *         @arg @ref LL_PLAY_IN7
  *         @arg @ref LL_PLAY_IN8
  *         @arg @ref LL_PLAY_IN9
  *         @arg @ref LL_PLAY_IN10
  *         @arg @ref LL_PLAY_IN11
  *         @arg @ref LL_PLAY_IN12
  *         @arg @ref LL_PLAY_IN13
  *         @arg @ref LL_PLAY_IN14
  *         @arg @ref LL_PLAY_IN15
  * @return Value in range 0x0000 to 0x00FF.
  */
__STATIC_INLINE uint32_t LL_PLAY_INPUT_GetMinimumPulseWidth(const PLAY_TypeDef *playx, uint32_t input_mux)
{
  return (uint32_t)(READ_BIT(playx->FILTCFG[input_mux], PLAY_FILTxCFG_WIDTH));
}

/**
  * @brief  Configure Filtering Edge mode.
  * @rmtoll FILTxCFG          EDGEDET     LL_PLAY_INPUT_SetEdgeDetectionMode
  * @param  playx     PLAY Instance.
  * @param  input_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_IN0
  *         @arg @ref LL_PLAY_IN1
  *         @arg @ref LL_PLAY_IN2
  *         @arg @ref LL_PLAY_IN3
  *         @arg @ref LL_PLAY_IN4
  *         @arg @ref LL_PLAY_IN5
  *         @arg @ref LL_PLAY_IN6
  *         @arg @ref LL_PLAY_IN7
  *         @arg @ref LL_PLAY_IN8
  *         @arg @ref LL_PLAY_IN9
  *         @arg @ref LL_PLAY_IN10
  *         @arg @ref LL_PLAY_IN11
  *         @arg @ref LL_PLAY_IN12
  *         @arg @ref LL_PLAY_IN13
  *         @arg @ref LL_PLAY_IN14
  *         @arg @ref LL_PLAY_IN15
  * @param  edge_detection_mode Value can be one of the following values:
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_BYPASSED
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_RISING
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_FALLING
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_RISING_FALLING
  */
__STATIC_INLINE void LL_PLAY_INPUT_SetEdgeDetectionMode(PLAY_TypeDef *playx, uint32_t input_mux,
                                                        uint32_t edge_detection_mode)
{
  MODIFY_REG(playx->FILTCFG[input_mux], PLAY_FILTxCFG_EDGEDET, edge_detection_mode);
}

/**
  * @brief  Get the Filtering Edge Detection Mode configuration of a PLAY input.
  * @rmtoll FILTxCFG          EDGEDET     LL_PLAY_INPUT_GetEdgeDetectionMode
  * @param  playx     PLAY Instance.
  * @param  input_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_IN0
  *         @arg @ref LL_PLAY_IN1
  *         @arg @ref LL_PLAY_IN2
  *         @arg @ref LL_PLAY_IN3
  *         @arg @ref LL_PLAY_IN4
  *         @arg @ref LL_PLAY_IN5
  *         @arg @ref LL_PLAY_IN6
  *         @arg @ref LL_PLAY_IN7
  *         @arg @ref LL_PLAY_IN8
  *         @arg @ref LL_PLAY_IN9
  *         @arg @ref LL_PLAY_IN10
  *         @arg @ref LL_PLAY_IN11
  *         @arg @ref LL_PLAY_IN12
  *         @arg @ref LL_PLAY_IN13
  *         @arg @ref LL_PLAY_IN14
  *         @arg @ref LL_PLAY_IN15
  * @return Returned Value can be one of the following values:
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_BYPASSED
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_RISING
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_FALLING
  *         @arg @ref LL_PLAY_EDGE_DETECTION_MODE_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_PLAY_INPUT_GetEdgeDetectionMode(const PLAY_TypeDef *playx, uint32_t input_mux)
{
  return (uint32_t)(READ_BIT(playx->FILTCFG[input_mux], PLAY_FILTxCFG_EDGEDET));
}

/**
  * @brief  Configure the signal source of a PLAY input.
  * @rmtoll FILTxCFG          PREMUXSEL     LL_PLAY_INPUT_SetSource
  * @param  playx     PLAY Instance.
  * @param  input_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_IN0
  *         @arg @ref LL_PLAY_IN1
  *         @arg @ref LL_PLAY_IN2
  *         @arg @ref LL_PLAY_IN3
  *         @arg @ref LL_PLAY_IN4
  *         @arg @ref LL_PLAY_IN5
  *         @arg @ref LL_PLAY_IN6
  *         @arg @ref LL_PLAY_IN7
  *         @arg @ref LL_PLAY_IN8
  *         @arg @ref LL_PLAY_IN9
  *         @arg @ref LL_PLAY_IN10
  *         @arg @ref LL_PLAY_IN11
  *         @arg @ref LL_PLAY_IN12
  *         @arg @ref LL_PLAY_IN13
  *         @arg @ref LL_PLAY_IN14
  *         @arg @ref LL_PLAY_IN15
  * @param  source    Value in range [0..7].
  */
__STATIC_INLINE void LL_PLAY_INPUT_SetSource(PLAY_TypeDef *playx, uint32_t input_mux, uint32_t source)
{
  MODIFY_REG(playx->FILTCFG[input_mux & (LL_PLAY_IN_MAX - 1U)], PLAY_FILTxCFG_PREMUXSEL,
             ((uint32_t)source) << PLAY_FILTxCFG_PREMUXSEL_Pos);
}

/**
  * @brief  Return the signal source of a PLAY input.
  * @rmtoll FILTxCFG          PREMUXSEL     LL_PLAY_INPUT_GetSource
  * @param  playx     PLAY Instance.
  * @param  input_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_IN0
  *         @arg @ref LL_PLAY_IN1
  *         @arg @ref LL_PLAY_IN2
  *         @arg @ref LL_PLAY_IN3
  *         @arg @ref LL_PLAY_IN4
  *         @arg @ref LL_PLAY_IN5
  *         @arg @ref LL_PLAY_IN6
  *         @arg @ref LL_PLAY_IN7
  *         @arg @ref LL_PLAY_IN8
  *         @arg @ref LL_PLAY_IN9
  *         @arg @ref LL_PLAY_IN10
  *         @arg @ref LL_PLAY_IN11
  *         @arg @ref LL_PLAY_IN12
  *         @arg @ref LL_PLAY_IN13
  *         @arg @ref LL_PLAY_IN14
  *         @arg @ref LL_PLAY_IN15
  * @return Premux_sel value in range [0..7].
  */
__STATIC_INLINE uint32_t LL_PLAY_INPUT_GetSource(const PLAY_TypeDef *playx, uint32_t input_mux)
{
  return (READ_BIT(playx->FILTCFG[input_mux & (LL_PLAY_IN_MAX - 1U)],
                   PLAY_FILTxCFG_PREMUXSEL) >> PLAY_FILTxCFG_PREMUXSEL_Pos);
}

/**
  * @brief  Configure the TruthTable value of a Lookup table.
  * @rmtoll LExCFG1          LUT     LL_PLAY_LUT_SetTruthTable
  * @param  playx PLAY Instance.
  * @param  lut   Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0
  *         @arg @ref LL_PLAY_LUT1
  *         @arg @ref LL_PLAY_LUT2
  *         @arg @ref LL_PLAY_LUT3
  *         @arg @ref LL_PLAY_LUT4
  *         @arg @ref LL_PLAY_LUT5
  *         @arg @ref LL_PLAY_LUT6
  *         @arg @ref LL_PLAY_LUT7
  *         @arg @ref LL_PLAY_LUT8
  *         @arg @ref LL_PLAY_LUT9
  *         @arg @ref LL_PLAY_LUT10
  *         @arg @ref LL_PLAY_LUT11
  *         @arg @ref LL_PLAY_LUT12
  *         @arg @ref LL_PLAY_LUT13
  *         @arg @ref LL_PLAY_LUT14
  *         @arg @ref LL_PLAY_LUT15
  * @param  truth_table Value in range 0x0000 to 0xFFFF.
  */
__STATIC_INLINE void LL_PLAY_LUT_SetTruthTable(PLAY_TypeDef *playx, uint32_t lut, uint32_t truth_table)
{
  MODIFY_REG(playx->LECFG1[lut], PLAY_LExCFG1_LUT, (truth_table << PLAY_LExCFG1_LUT_Pos));
}

/**
  * @brief  Get the LUT value of a Lookup table.
  * @rmtoll LExCFG1          LUT     LL_PLAY_LUT_GetTruthTable
  * @param  playx PLAY Instance.
  * @param  lut   Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0
  *         @arg @ref LL_PLAY_LUT1
  *         @arg @ref LL_PLAY_LUT2
  *         @arg @ref LL_PLAY_LUT3
  *         @arg @ref LL_PLAY_LUT4
  *         @arg @ref LL_PLAY_LUT5
  *         @arg @ref LL_PLAY_LUT6
  *         @arg @ref LL_PLAY_LUT7
  *         @arg @ref LL_PLAY_LUT8
  *         @arg @ref LL_PLAY_LUT9
  *         @arg @ref LL_PLAY_LUT10
  *         @arg @ref LL_PLAY_LUT11
  *         @arg @ref LL_PLAY_LUT12
  *         @arg @ref LL_PLAY_LUT13
  *         @arg @ref LL_PLAY_LUT14
  *         @arg @ref LL_PLAY_LUT15
  * @return Value in range 0x0000 to 0xFFFF.
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_GetTruthTable(const PLAY_TypeDef *playx, uint32_t lut)
{
  return (uint32_t)(READ_BIT(playx->LECFG1[lut], PLAY_LExCFG1_LUT) >> PLAY_LExCFG1_LUT_Pos);
}

/**
  * @brief  Configure an Input of a Lookup table.
  * @rmtoll LExCFG2          IN0_SEL     LL_PLAY_LUT_SetSource\n
  *         LExCFG2          IN1_SEL     LL_PLAY_LUT_SetSource\n
  *         LExCFG2          IN2_SEL     LL_PLAY_LUT_SetSource\n
  *         LExCFG2          IN3_SEL     LL_PLAY_LUT_SetSource
  * @param  playx PLAY Instance.
  * @param  lut   Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0
  *         @arg @ref LL_PLAY_LUT1
  *         @arg @ref LL_PLAY_LUT2
  *         @arg @ref LL_PLAY_LUT3
  *         @arg @ref LL_PLAY_LUT4
  *         @arg @ref LL_PLAY_LUT5
  *         @arg @ref LL_PLAY_LUT6
  *         @arg @ref LL_PLAY_LUT7
  *         @arg @ref LL_PLAY_LUT8
  *         @arg @ref LL_PLAY_LUT9
  *         @arg @ref LL_PLAY_LUT10
  *         @arg @ref LL_PLAY_LUT11
  *         @arg @ref LL_PLAY_LUT12
  *         @arg @ref LL_PLAY_LUT13
  *         @arg @ref LL_PLAY_LUT14
  *         @arg @ref LL_PLAY_LUT15
  * @param  input_idx Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_INPUT0
  *         @arg @ref LL_PLAY_LUT_INPUT1
  *         @arg @ref LL_PLAY_LUT_INPUT2
  *         @arg @ref LL_PLAY_LUT_INPUT3
  * @param  source_sel Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER0
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER1
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER2
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER3
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER4
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER5
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER6
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER7
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER8
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER9
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER10
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER11
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER12
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER13
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER14
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER15
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG0
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG1
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG2
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG3
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG4
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG5
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG6
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG7
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG8
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG9
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG10
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG11
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG12
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG13
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG14
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG15
  */
__STATIC_INLINE void LL_PLAY_LUT_SetSource(PLAY_TypeDef *playx, uint32_t lut, uint32_t input_idx, uint32_t source_sel)
{
  MODIFY_REG(playx->LECFG2[lut], (PLAY_LExCFG2_IN0_SEL << (input_idx * PLAY_LExCFG2_IN1_SEL_Pos)),
             (source_sel << (input_idx * PLAY_LExCFG2_IN1_SEL_Pos)));
}

/**
  * @brief  Get the value of an input of a Lookup table.
  * @rmtoll LExCFG2          IN0_SEL     LL_PLAY_LUT_GetSource\n
  *         LExCFG2          IN1_SEL     LL_PLAY_LUT_GetSource\n
  *         LExCFG2          IN2_SEL     LL_PLAY_LUT_GetSource\n
  *         LExCFG2          IN3_SEL     LL_PLAY_LUT_GetSource
  * @param  playx PLAY Instance.
  * @param  lut   Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0
  *         @arg @ref LL_PLAY_LUT1
  *         @arg @ref LL_PLAY_LUT2
  *         @arg @ref LL_PLAY_LUT3
  *         @arg @ref LL_PLAY_LUT4
  *         @arg @ref LL_PLAY_LUT5
  *         @arg @ref LL_PLAY_LUT6
  *         @arg @ref LL_PLAY_LUT7
  *         @arg @ref LL_PLAY_LUT8
  *         @arg @ref LL_PLAY_LUT9
  *         @arg @ref LL_PLAY_LUT10
  *         @arg @ref LL_PLAY_LUT11
  *         @arg @ref LL_PLAY_LUT12
  *         @arg @ref LL_PLAY_LUT13
  *         @arg @ref LL_PLAY_LUT14
  *         @arg @ref LL_PLAY_LUT15
  * @param  input_idx Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_INPUT0
  *         @arg @ref LL_PLAY_LUT_INPUT1
  *         @arg @ref LL_PLAY_LUT_INPUT2
  *         @arg @ref LL_PLAY_LUT_INPUT3
  * @return Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER0
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER1
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER2
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER3
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER4
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER5
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER6
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER7
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER8
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER9
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER10
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER11
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER12
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER13
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER14
  *         @arg @ref LL_PLAY_LUT_SOURCE_FILTER15
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG0
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG1
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG2
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG3
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG4
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG5
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG6
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG7
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG8
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG9
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG10
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG11
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG12
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG13
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG14
  *         @arg @ref LL_PLAY_LUT_SOURCE_SWTRIG15
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_GetSource(const PLAY_TypeDef *playx, uint32_t lut, uint32_t input_idx)
{
  return (uint32_t)((READ_BIT(playx->LECFG2[lut],
                              (PLAY_LExCFG2_IN0_SEL << (input_idx * PLAY_LExCFG2_IN1_SEL_Pos))))
                    >> (input_idx * PLAY_LExCFG2_IN1_SEL_Pos));
}

/**
  * @brief  Configure the Clock Gate of a Lookup table.
  * @rmtoll LExCFG2          CK_SEL     LL_PLAY_LUT_SetClockGate
  * @param  playx PLAY Instance.
  * @param  lut   Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0
  *         @arg @ref LL_PLAY_LUT1
  *         @arg @ref LL_PLAY_LUT2
  *         @arg @ref LL_PLAY_LUT3
  *         @arg @ref LL_PLAY_LUT4
  *         @arg @ref LL_PLAY_LUT5
  *         @arg @ref LL_PLAY_LUT6
  *         @arg @ref LL_PLAY_LUT7
  *         @arg @ref LL_PLAY_LUT8
  *         @arg @ref LL_PLAY_LUT9
  *         @arg @ref LL_PLAY_LUT10
  *         @arg @ref LL_PLAY_LUT11
  *         @arg @ref LL_PLAY_LUT12
  *         @arg @ref LL_PLAY_LUT13
  *         @arg @ref LL_PLAY_LUT14
  *         @arg @ref LL_PLAY_LUT15
  * @param  clk_gate Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_OFF
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_ON
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SW_ACK
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER0
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER1
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER2
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER3
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER4
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER5
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER6
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER7
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER8
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER9
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER10
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER11
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER12
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER13
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER14
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER15
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG0
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG1
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG2
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG3
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG4
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG5
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG6
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG7
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG8
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG9
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG10
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG11
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG12
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG13
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG14
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG15
  */
__STATIC_INLINE void LL_PLAY_LUT_SetClockGate(PLAY_TypeDef *playx, uint32_t lut, uint32_t clk_gate)
{
  MODIFY_REG(playx->LECFG2[lut], PLAY_LExCFG2_CK_SEL, clk_gate << PLAY_LExCFG2_CK_SEL_Pos);
}

/**
  * @brief  Get the Clock Gate of a Lookup table.
  * @rmtoll LExCFG2          CK_SEL     LL_PLAY_LUT_GetClockGate
  * @param  playx PLAY Instance.
  * @param  lut   Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0
  *         @arg @ref LL_PLAY_LUT1
  *         @arg @ref LL_PLAY_LUT2
  *         @arg @ref LL_PLAY_LUT3
  *         @arg @ref LL_PLAY_LUT4
  *         @arg @ref LL_PLAY_LUT5
  *         @arg @ref LL_PLAY_LUT6
  *         @arg @ref LL_PLAY_LUT7
  *         @arg @ref LL_PLAY_LUT8
  *         @arg @ref LL_PLAY_LUT9
  *         @arg @ref LL_PLAY_LUT10
  *         @arg @ref LL_PLAY_LUT11
  *         @arg @ref LL_PLAY_LUT12
  *         @arg @ref LL_PLAY_LUT13
  *         @arg @ref LL_PLAY_LUT14
  *         @arg @ref LL_PLAY_LUT15
  * @return Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_OFF
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_ON
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SW_ACK
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER0
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER1
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER2
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER3
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER4
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER5
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER6
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER7
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER8
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER9
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER10
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER11
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER12
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER13
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER14
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_FILTER15
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG0
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG1
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG2
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG3
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG4
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG5
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG6
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG7
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG8
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG9
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG10
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG11
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG12
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG13
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG14
  *         @arg @ref LL_PLAY_LUT_CLK_GATE_SWTRIG15
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_GetClockGate(const PLAY_TypeDef *playx, uint32_t lut)
{
  return (uint32_t)(READ_BIT(playx->LECFG2[lut], PLAY_LExCFG2_CK_SEL) >> PLAY_LExCFG2_CK_SEL_Pos);
}

/**
  * @brief  Get LUT Output status.
  * @rmtoll OSR          LEOUTD           LL_PLAY_LUT_GetStatus
  * @rmtoll OSR          LEOUTR           LL_PLAY_LUT_GetStatus
  * @param  playx  PLAY Instance.
  * @param  output Value can be a one of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  * @note PLAY instance must be locked otherwise OSR register will be on hold.
  * @return State of the bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_GetStatus(const PLAY_TypeDef *playx, uint32_t output)
{
  return (((READ_BIT(playx->OSR, output) == output) ? 1UL : 0UL));
}

/**
  * @brief  Configure the source of an PLAY output.
  * @rmtoll OUTxCFG          SEL     LL_PLAY_OUTPUT_SetSource
  * @param  playx      PLAY Instance.
  * @param  output_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_OUT0
  *         @arg @ref LL_PLAY_OUT1
  *         @arg @ref LL_PLAY_OUT2
  *         @arg @ref LL_PLAY_OUT3
  *         @arg @ref LL_PLAY_OUT4
  *         @arg @ref LL_PLAY_OUT5
  *         @arg @ref LL_PLAY_OUT6
  *         @arg @ref LL_PLAY_OUT7
  *         @arg @ref LL_PLAY_OUT8
  *         @arg @ref LL_PLAY_OUT9
  *         @arg @ref LL_PLAY_OUT10
  *         @arg @ref LL_PLAY_OUT11
  *         @arg @ref LL_PLAY_OUT12
  *         @arg @ref LL_PLAY_OUT13
  *         @arg @ref LL_PLAY_OUT14
  *         @arg @ref LL_PLAY_OUT15
  * @param  source Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  */
__STATIC_INLINE void LL_PLAY_OUTPUT_SetSource(PLAY_TypeDef *playx, uint32_t output_mux, uint32_t source)
{
  MODIFY_REG(playx->OUTCFG[output_mux], PLAY_OUTxCFG_SEL, (POSITION_VAL(source)) << PLAY_OUTxCFG_SEL_Pos);
}

/**
  * @brief  Get the source of an PLAY output.
  * @rmtoll OUTxCFG          SEL     LL_PLAY_OUTPUT_GetSource
  * @param  playx      PLAY Instance.
  * @param  output_mux Value can be one of the following values:
  *         @arg @ref LL_PLAY_OUT0
  *         @arg @ref LL_PLAY_OUT1
  *         @arg @ref LL_PLAY_OUT2
  *         @arg @ref LL_PLAY_OUT3
  *         @arg @ref LL_PLAY_OUT4
  *         @arg @ref LL_PLAY_OUT5
  *         @arg @ref LL_PLAY_OUT6
  *         @arg @ref LL_PLAY_OUT7
  *         @arg @ref LL_PLAY_OUT8
  *         @arg @ref LL_PLAY_OUT9
  *         @arg @ref LL_PLAY_OUT10
  *         @arg @ref LL_PLAY_OUT11
  *         @arg @ref LL_PLAY_OUT12
  *         @arg @ref LL_PLAY_OUT13
  *         @arg @ref LL_PLAY_OUT14
  *         @arg @ref LL_PLAY_OUT15
  * @return Value can be one of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  */
__STATIC_INLINE uint32_t LL_PLAY_OUTPUT_GetSource(const PLAY_TypeDef *playx, uint32_t output_mux)
{
  return (uint32_t)(1UL << (READ_BIT(playx->OUTCFG[output_mux], PLAY_OUTxCFG_SEL) >> PLAY_OUTxCFG_SEL_Pos));
}

/**
  * @}
  */

/** @defgroup PLAY_LL_EF_SWTRIGGER_Management  Software Trigger Management
  * @{
  */

/**
  * @brief  Set High level to a Software Trigger input.
  * @rmtoll SWINSET          SWIN           LL_PLAY_SetSWTrigger
  * @param  playx          PLAY Instance.
  * @param  msk_swtriggers Value can be a combination of the following values:
  *         @arg @ref LL_PLAY_SWTRIG0
  *         @arg @ref LL_PLAY_SWTRIG1
  *         @arg @ref LL_PLAY_SWTRIG2
  *         @arg @ref LL_PLAY_SWTRIG3
  *         @arg @ref LL_PLAY_SWTRIG4
  *         @arg @ref LL_PLAY_SWTRIG5
  *         @arg @ref LL_PLAY_SWTRIG6
  *         @arg @ref LL_PLAY_SWTRIG7
  *         @arg @ref LL_PLAY_SWTRIG8
  *         @arg @ref LL_PLAY_SWTRIG9
  *         @arg @ref LL_PLAY_SWTRIG10
  *         @arg @ref LL_PLAY_SWTRIG11
  *         @arg @ref LL_PLAY_SWTRIG12
  *         @arg @ref LL_PLAY_SWTRIG13
  *         @arg @ref LL_PLAY_SWTRIG14
  *         @arg @ref LL_PLAY_SWTRIG15
  *         @arg @ref LL_PLAY_SWTRIG_ALL
  */
__STATIC_INLINE void LL_PLAY_SetSWTrigger(PLAY_TypeDef *playx, uint32_t msk_swtriggers)
{
  SET_BIT(playx->SWINSET, msk_swtriggers);
}

/**
  * @brief  Set Low level to a Software Trigger input.
  * @rmtoll SWINCLR          SWIN           LL_PLAY_ResetSWTrigger
  * @param  playx          PLAY Instance.
  * @param  msk_swtriggers Value can be a combination of the following values:
  *         @arg @ref LL_PLAY_SWTRIG0
  *         @arg @ref LL_PLAY_SWTRIG1
  *         @arg @ref LL_PLAY_SWTRIG2
  *         @arg @ref LL_PLAY_SWTRIG3
  *         @arg @ref LL_PLAY_SWTRIG4
  *         @arg @ref LL_PLAY_SWTRIG5
  *         @arg @ref LL_PLAY_SWTRIG6
  *         @arg @ref LL_PLAY_SWTRIG7
  *         @arg @ref LL_PLAY_SWTRIG8
  *         @arg @ref LL_PLAY_SWTRIG9
  *         @arg @ref LL_PLAY_SWTRIG10
  *         @arg @ref LL_PLAY_SWTRIG11
  *         @arg @ref LL_PLAY_SWTRIG12
  *         @arg @ref LL_PLAY_SWTRIG13
  *         @arg @ref LL_PLAY_SWTRIG14
  *         @arg @ref LL_PLAY_SWTRIG15
  *         @arg @ref LL_PLAY_SWTRIG_ALL
  */
__STATIC_INLINE void LL_PLAY_ResetSWTrigger(PLAY_TypeDef *playx, uint32_t msk_swtriggers)
{
  SET_BIT(playx->SWINCLR, msk_swtriggers);
}

/**
  * @brief  Get the level of a Software Trigger input.
  * @rmtoll SWIN          SWIN           LL_PLAY_IsSWTriggerSet
  * @param  playx     PLAY Instance.
  * @param  swtrigger Value can be a one of the following values:
  *         @arg @ref LL_PLAY_SWTRIG0
  *         @arg @ref LL_PLAY_SWTRIG1
  *         @arg @ref LL_PLAY_SWTRIG2
  *         @arg @ref LL_PLAY_SWTRIG3
  *         @arg @ref LL_PLAY_SWTRIG4
  *         @arg @ref LL_PLAY_SWTRIG5
  *         @arg @ref LL_PLAY_SWTRIG6
  *         @arg @ref LL_PLAY_SWTRIG7
  *         @arg @ref LL_PLAY_SWTRIG8
  *         @arg @ref LL_PLAY_SWTRIG9
  *         @arg @ref LL_PLAY_SWTRIG10
  *         @arg @ref LL_PLAY_SWTRIG11
  *         @arg @ref LL_PLAY_SWTRIG12
  *         @arg @ref LL_PLAY_SWTRIG13
  *         @arg @ref LL_PLAY_SWTRIG14
  *         @arg @ref LL_PLAY_SWTRIG15
  * @return State of the bit (1 or 0)
  */
__STATIC_INLINE uint32_t LL_PLAY_IsSWTriggerSet(const PLAY_TypeDef *playx, uint32_t swtrigger)
{
  return (((READ_BIT(playx->SWIN, swtrigger) == swtrigger) ? 1UL : 0UL));
}

/**
  * @brief  Toggle the level of Software Trigger input.
  * @rmtoll SWIN          SWIN           LL_PLAY_ToggleSWTrigger
  * @param  playx          PLAY Instance.
  * @param  msk_swtriggers Value can be a combination of the following values:
  *         @arg @ref LL_PLAY_SWTRIG0
  *         @arg @ref LL_PLAY_SWTRIG1
  *         @arg @ref LL_PLAY_SWTRIG2
  *         @arg @ref LL_PLAY_SWTRIG3
  *         @arg @ref LL_PLAY_SWTRIG4
  *         @arg @ref LL_PLAY_SWTRIG5
  *         @arg @ref LL_PLAY_SWTRIG6
  *         @arg @ref LL_PLAY_SWTRIG7
  *         @arg @ref LL_PLAY_SWTRIG8
  *         @arg @ref LL_PLAY_SWTRIG9
  *         @arg @ref LL_PLAY_SWTRIG10
  *         @arg @ref LL_PLAY_SWTRIG11
  *         @arg @ref LL_PLAY_SWTRIG12
  *         @arg @ref LL_PLAY_SWTRIG13
  *         @arg @ref LL_PLAY_SWTRIG14
  *         @arg @ref LL_PLAY_SWTRIG15
  *         @arg @ref LL_PLAY_SWTRIG_ALL
  */
__STATIC_INLINE void LL_PLAY_ToggleSWTrigger(PLAY_TypeDef *playx, uint32_t msk_swtriggers)
{
  uint32_t curr_swtrigger = READ_REG(playx->SWIN);
  MODIFY_REG(playx->SWIN, msk_swtriggers, (curr_swtrigger ^ msk_swtriggers));
}

/**
  * @}
  */

/** @defgroup PLAY_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable lookup table output flag interrupt.
  * @rmtoll FLIER          FLAGD_IEN           LL_PLAY_LUT_EnableIT
  * @rmtoll FLIER          FLAGR_IEN           LL_PLAY_LUT_EnableIT
  * @param  playx   PLAY Instance.
  * @param  msk_its Value can be a combination of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_REGISTERED
  */
__STATIC_INLINE void LL_PLAY_LUT_EnableIT(PLAY_TypeDef *playx, uint32_t msk_its)
{
  SET_BIT(playx->FLIER, msk_its);
}

/**
  * @brief  Disable lookup table output flag interrupt.
  * @rmtoll FLIER          FLAGD_IEN           LL_PLAY_LUT_DisableIT
  * @rmtoll FLIER          FLAGR_IEN           LL_PLAY_LUT_DisableIT
  * @param  playx   PLAY Instance.
  * @param  msk_its Value can be a combination of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_REGISTERED
  */
__STATIC_INLINE void LL_PLAY_LUT_DisableIT(PLAY_TypeDef *playx, uint32_t msk_its)
{
  CLEAR_BIT(playx->FLIER, msk_its);
}

/**
  * @brief  Check lookup table output flag interrupt.
  * @rmtoll FLIER          FLAGD_IEN           LL_PLAY_LUT_IsEnabledIT
  * @rmtoll FLIER          FLAGR_IEN           LL_PLAY_LUT_IsEnabledIT
  * @param  playx PLAY Instance.
  * @param  flag  Value can be a one of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_IsEnabledIT(const PLAY_TypeDef *playx, uint32_t flag)
{
  return ((READ_BIT(playx->FLIER, flag) == flag) ? 1U : 0U);
}

/**
  * @brief  Get the lookup table output flag interrupt mask.
  * @rmtoll FLIER          FLAGD_IEN           LL_PLAY_LUT_GetIT
  * @rmtoll FLIER          FLAGR_IEN           LL_PLAY_LUT_GetIT
  * @param  playx PLAY Instance.
  * @return Mask of enabled Lookup table output interrupts.
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_GetIT(const PLAY_TypeDef *playx)
{
  return (READ_REG(playx->FLIER));
}

/**
  * @brief  Enable Software Trigger write complete interrupt.
  * @rmtoll IER          SWINWC_IEN           LL_PLAY_EnableIT_SWTriggerWriteComplete
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_EnableIT_SWTriggerWriteComplete(PLAY_TypeDef *playx)
{
  SET_BIT(playx->IER, PLAY_IER_SWINWC_IEN);
}

/**
  * @brief  Disable Software Trigger write complete interrupt.
  * @rmtoll IER          SWINWC_IEN           LL_PLAY_DisableIT_SWTriggerWriteComplete
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_DisableIT_SWTriggerWriteComplete(PLAY_TypeDef *playx)
{
  CLEAR_BIT(playx->IER, PLAY_IER_SWINWC_IEN);
}

/**
  * @brief  Check Software Trigger write complete interrupt.
  * @rmtoll IER          SWINWC_IEN           LL_PLAY_IsEnabledIT_SWTriggerWriteComplete
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsEnabledIT_SWTriggerWriteComplete(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->IER, PLAY_IER_SWINWC_IEN) == PLAY_IER_SWINWC_IEN) ? 1U : 0U);
}

/**
  * @brief  Enable Edge Trigger write complete interrupt.
  * @rmtoll IER          FLCTLWC_IEN           LL_PLAY_LUT_EnableIT_EdgeTriggerWriteComplete
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_LUT_EnableIT_EdgeTriggerWriteComplete(PLAY_TypeDef *playx)
{
  SET_BIT(playx->IER, PLAY_IER_FLCTLWC_IEN);
}

/**
  * @brief  Disable Edge Trigger write complete interrupt.
  * @rmtoll IER          FLCTLWC_IEN           LL_PLAY_LUT_DisableIT_EdgeTriggerWriteComplete
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_LUT_DisableIT_EdgeTriggerWriteComplete(PLAY_TypeDef *playx)
{
  CLEAR_BIT(playx->IER, PLAY_IER_FLCTLWC_IEN);
}

/**
  * @brief  Check Edge Trigger write complete interrupt.
  * @rmtoll IER          FLCTLWC_IEN           LL_PLAY_LUT_IsEnabledIT_EdgeTriggerWriteComplete
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_IsEnabledIT_EdgeTriggerWriteComplete(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->IER, PLAY_IER_FLCTLWC_IEN) == PLAY_IER_FLCTLWC_IEN) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup PLAY_LL_EF_FLAG_Management  FLAG Management
  * @{
  */

/**
  * @brief  Set flag transition of all lookup table outputs.
  * @rmtoll FLCTL          FLAGD_EDGE          LL_PLAY_LUT_ConfigEdgeTrigger
  * @rmtoll FLCTL          FLAGR_EDGE          LL_PLAY_LUT_ConfigEdgeTrigger
  * @param  playx            PLAY Instance.
  * @param  msk_rising_flags Mask of flags to configure on rising edge.
  *         The others flag  will be configured on falling edge.
  *         The value of this parameter can be a combination of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_REGISTERED
  * @note   To configure some transitions without impacting the others use the function
  *         @ref LL_PLAY_LUT_SetEdgeTrigger().
  */
__STATIC_INLINE void LL_PLAY_LUT_ConfigEdgeTrigger(PLAY_TypeDef *playx, uint32_t msk_rising_flags)
{
  WRITE_REG(playx->FLCTL, msk_rising_flags);
}

/**
  * @brief  Set flag transition for lookup table output.
  * @rmtoll FLCTL          FLAGD_EDGE          LL_PLAY_LUT_SetEdgeTrigger
  * @rmtoll FLCTL          FLAGR_EDGE          LL_PLAY_LUT_SetEdgeTrigger
  * @param  playx           PLAY Instance.
  * @param  msk_out_falling Value can be a combination of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_REGISTERED
  * @param  msk_out_rising Value can be a combination of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT_ALL_OUT_REGISTERED
  * @note   To configure all transitions (Rising & Falling), by only one call,
  *         use function @ref LL_PLAY_LUT_ConfigEdgeTrigger().
  */
__STATIC_INLINE void LL_PLAY_LUT_SetEdgeTrigger(PLAY_TypeDef *playx, uint32_t msk_out_falling,
                                                uint32_t msk_out_rising)
{
  uint32_t msk_flags = msk_out_falling | msk_out_rising;
  MODIFY_REG(playx->FLCTL, msk_flags, msk_out_rising);
}

/**
  * @brief  Get flag transitions of all lookup table outputs.
  * @rmtoll FLCTL          FLAGD_EDGE          LL_PLAY_LUT_GetEdgeTrigger
  * @rmtoll FLCTL          FLAGR_EDGE          LL_PLAY_LUT_GetEdgeTrigger
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_GetEdgeTrigger(const PLAY_TypeDef *playx)
{
  return READ_REG(playx->FLCTL);
}

/**
  * @brief  Check lookup table output flag status.
  * @rmtoll FLSTAT          FLAGD          LL_PLAY_LUT_IsActiveFlag
  * @rmtoll FLSTAT          FLAGR          LL_PLAY_LUT_IsActiveFlag
  * @param  playx PLAY Instance.
  * @param  flag  Value can be a one of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_IsActiveFlag(const PLAY_TypeDef *playx, uint32_t flag)
{
  return ((READ_BIT(playx->FLSTAT, flag) == flag) ? 1U : 0U);
}

/**
  * @brief  Clear lookup table output flag.
  * @rmtoll FLCLR          FLAGD_CLR       LL_PLAY_LUT_ClearFlag
  * @rmtoll FLCLR          FLAGR_CLR       LL_PLAY_LUT_ClearFlag
  * @param  playx PLAY Instance.
  * @param  msk_flags  Value can be a one of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  */
__STATIC_INLINE void LL_PLAY_LUT_ClearFlag(PLAY_TypeDef *playx, uint32_t msk_flags)
{
  SET_BIT(playx->FLCLR, msk_flags);
}

/**
  * @brief  Set lookup table output flag.
  * @rmtoll FLSET          FLAGD_SET       LL_PLAY_LUT_SetFlag
  * @rmtoll FLSET          FLAGR_SET       LL_PLAY_LUT_SetFlag
  * @param  playx PLAY Instance.
  * @param  msk_flags  Value can be a one of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  * @note   The peripheral allows to activate by software the LUT Output flags
  *         for debugging case.
  */
__STATIC_INLINE void LL_PLAY_LUT_SetFlag(PLAY_TypeDef *playx, uint32_t msk_flags)
{
  SET_BIT(playx->FLSET, msk_flags);
}

/**
  * @brief  Retrieve the status of all lookup table flags.
  * @rmtoll FLSTAT          FLAGD          LL_PLAY_LUT_GetFlags
  * @rmtoll FLSTAT          FLAGR          LL_PLAY_LUT_GetFlags
  * @param  playx PLAY Instance.
  * @return Flags status (bit mask).
  *         This value can be a combination of the following values:
  *         @arg @ref LL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref LL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref LL_PLAY_LUT15_OUT_REGISTERED
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_GetFlags(const PLAY_TypeDef *playx)
{
  return READ_REG(playx->FLSTAT);
}

/**
  * @brief  Check Software Trigger write busy flag status.
  * @rmtoll MSR          SWINWBFS          LL_PLAY_IsSWTriggerWriteBusy
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsSWTriggerWriteBusy(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->MSR, PLAY_MSR_SWINWBFS) == PLAY_MSR_SWINWBFS) ? 1U : 0U);
}

/**
  * @brief  Check Software Trigger write complete flag status.
  * @rmtoll ISR          SWINWC          LL_PLAY_IsSWTriggerWriteComplete
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsSWTriggerWriteComplete(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->ISR, PLAY_ISR_SWINWC) == PLAY_ISR_SWINWC) ? 1U : 0U);
}
/**
  * @brief  Clear Software Trigger write complete flag.
  * @rmtoll ICR          SWINWC_CLR       LL_PLAY_ClearFlag_SWTriggerWriteComplete
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_ClearFlag_SWTriggerWriteComplete(PLAY_TypeDef *playx)
{
  SET_BIT(playx->ICR, PLAY_ICR_SWINWC_CLR);
}

/**
  * @brief  Check Edge Trigger write busy flag status.
  * @rmtoll MSR          FLCTLWBFS          LL_PLAY_LUT_IsEdgeTriggerWriteBusy
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_IsEdgeTriggerWriteBusy(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->MSR, PLAY_MSR_FLCTLWBFS) == PLAY_MSR_FLCTLWBFS) ? 1U : 0U);
}

/**
  * @brief  Check Edge Trigger write complete flag status.
  * @rmtoll ISR          FLCTLWC          LL_PLAY_LUT_IsEdgeTriggerWriteComplete
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_IsEdgeTriggerWriteComplete(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->ISR, PLAY_ISR_FLCTLWC) == PLAY_ISR_FLCTLWC) ? 1U : 0U);
}

/**
  * @brief  Clear Edge Trigger write complete flag.
  * @rmtoll ICR          FLCTLWC_CLR       LL_PLAY_LUT_ClearFlag_EdgeTriggerWriteComplete
  * @param  playx PLAY Instance.
  */
__STATIC_INLINE void LL_PLAY_LUT_ClearFlag_EdgeTriggerWriteComplete(PLAY_TypeDef *playx)
{
  SET_BIT(playx->ICR, PLAY_ICR_FLCTLWC_CLR);
}

/**
  * @brief  Check Flags flag status.
  * @rmtoll ISR          FLAGS          LL_PLAY_LUT_IsActiveFlag_FLAGS
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_LUT_IsActiveFlag_FLAGS(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->ISR, PLAY_ISR_FLAGS) == PLAY_ISR_FLAGS) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup PLAY_LL_EF_TrustZone  TrustZone management functions
  * @{
  */

/**
  * @brief  Configure Privilege mode.
  * @rmtoll PRIVCFGR          PRIV          LL_PLAY_ConfigPrivilege
  * @param  playx     PLAY Instance.
  * @param  attribute Value can be a one of the following values:
  *         @arg @ref LL_PLAY_NPRIV
  *         @arg @ref LL_PLAY_CONFIG_PRIV
  *         @arg @ref LL_PLAY_FULL_PRIV
  */
__STATIC_INLINE void LL_PLAY_ConfigPrivilege(PLAY_TypeDef *playx, uint32_t attribute)
{
  MODIFY_REG(playx->PRIVCFGR, PLAY_PRIVCFGR_PRIV_Msk, attribute);
}

/**
  * @brief  Get Privilege mode configuration.
  * @rmtoll PRIVCFGR          PRIV          LL_PLAY_GetConfigPrivilege
  * @param  playx PLAY Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_PLAY_NPRIV
  *         @arg @ref LL_PLAY_CONFIG_PRIV
  *         @arg @ref LL_PLAY_FULL_PRIV
  */
__STATIC_INLINE uint32_t LL_PLAY_GetConfigPrivilege(const PLAY_TypeDef *playx)
{
  return (uint32_t)(READ_BIT(playx->PRIVCFGR, PLAY_PRIVCFGR_PRIV_Msk));
}

/**
  * @brief  Indicates if the PLAY Configuration registers require a Privilege access.
  * @rmtoll PRIVCFGR          PRIV          LL_PLAY_IsEnabledConfigPrivilege
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsEnabledConfigPrivilege(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->PRIVCFGR, PLAY_PRIVCFGR_PRIV_Msk) == LL_PLAY_CONFIG_PRIV) ? 1UL : 0UL);
}

/**
  * @brief  Indicates if all PLAY registers require a Privilege access.
  * @rmtoll PRIVCFGR          PRIV          LL_PLAY_IsEnabledFullPrivilege
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsEnabledFullPrivilege(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->PRIVCFGR, PLAY_PRIVCFGR_PRIV_Msk) == LL_PLAY_FULL_PRIV) ? 1UL : 0UL);
}

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Configure Secure mode
  * @rmtoll SECCFGR          SEC          LL_PLAY_ConfigSecure
  * @param  playx     PLAY Instance.
  * @param  attribute Value can be a one of the following values:
  *         @arg @ref LL_PLAY_NSEC
  *         @arg @ref LL_PLAY_CONFIG_SEC
  *         @arg @ref LL_PLAY_FULL_SEC
  * @note Only available when system implements security (TZEN=1).
  */
__STATIC_INLINE void LL_PLAY_ConfigSecure(PLAY_TypeDef *playx, uint32_t attribute)
{
  MODIFY_REG(playx->SECCFGR, PLAY_SECCFGR_SEC_Msk, attribute);
}

/**
  * @brief  Get Secure mode configuration
  * @rmtoll SECCFGR          SEC          LL_PLAY_GetConfigSecure
  * @param  playx PLAY Instance.
  * @note Only available when system implements security (TZEN=1).
  * @return Returned value of configuration can be one of the following values:
  *         @arg @ref LL_PLAY_NSEC
  *         @arg @ref LL_PLAY_CONFIG_SEC
  *         @arg @ref LL_PLAY_FULL_SEC
  */
__STATIC_INLINE uint32_t LL_PLAY_GetConfigSecure(const PLAY_TypeDef *playx)
{
  return (uint32_t)(READ_BIT(playx->SECCFGR, PLAY_SECCFGR_SEC_Msk));
}

/**
  * @brief  Indicates if the PLAY Configuration registers require a Secure access.
  * @rmtoll SECCFGR          SEC          LL_PLAY_IsEnabledConfigSecure
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsEnabledConfigSecure(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->SECCFGR, PLAY_SECCFGR_SEC_Msk) == LL_PLAY_CONFIG_SEC) ? 1UL : 0UL);
}

/**
  * @brief  Indicates if all PLAY registers require a Secure access.
  * @rmtoll SECCFGR          SEC          LL_PLAY_IsEnabledFullSecure
  * @param  playx PLAY Instance.
  * @return State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PLAY_IsEnabledFullSecure(const PLAY_TypeDef *playx)
{
  return ((READ_BIT(playx->SECCFGR, PLAY_SECCFGR_SEC_Msk) == LL_PLAY_FULL_SEC) ? 1UL : 0UL);
}

#endif /* defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PLAY_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_PLAY_DeInit(PLAY_TypeDef *PLAYx);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* PLAY1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H5xx_LL_PLAY_H */
