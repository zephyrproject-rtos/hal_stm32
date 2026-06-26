/**
  ******************************************************************************
  * @file    stm32g5xx_ll_ucpd.h
  * @brief   Header file of UCPD LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G5XX_LL_UCPD_H
#define STM32G5XX_LL_UCPD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined(UCPD1)

/** @defgroup UCPD_LL UCPD
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup UCPD_LL_Exported_Constants LL UCPD Constants
  * @{
  */

/** @defgroup UCPD_LL_EC_GET_FLAG Status flags definition
  * @brief    Flags defines which can be used with LL_UCPD_READ_REG function.
  * @{
  */

#define LL_UCPD_SR_TXIS             UCPD_SR_TXIS             /*!< Transmit interrupt status                     */
#define LL_UCPD_SR_TXMSGDISC        UCPD_SR_TXMSGDISC        /*!< Transmit message discarded interrupt          */
#define LL_UCPD_SR_TXMSGSENT        UCPD_SR_TXMSGSENT        /*!< Transmit message sent interrupt               */
#define LL_UCPD_SR_TXMSGABT         UCPD_SR_TXMSGABT         /*!< Transmit message abort interrupt              */
#define LL_UCPD_SR_HRSTDISC         UCPD_SR_HRSTDISC         /*!< HRST discarded interrupt                      */
#define LL_UCPD_SR_HRSTSENT         UCPD_SR_HRSTSENT         /*!< HRST sent interrupt                           */
#define LL_UCPD_SR_TXUND            UCPD_SR_TXUND            /*!< Tx data underrun condition interrupt          */
#define LL_UCPD_SR_RXNE             UCPD_SR_RXNE             /*!< Receive data register not empty interrupt     */
#define LL_UCPD_SR_RXORDDET         UCPD_SR_RXORDDET         /*!< Rx ordered set (4 K-codes) detected interrupt */
#define LL_UCPD_SR_RXHRSTDET        UCPD_SR_RXHRSTDET        /*!< Rx Hard Reset detect interrupt                */
#define LL_UCPD_SR_RXOVR            UCPD_SR_RXOVR            /*!< Rx data overflow interrupt                    */
#define LL_UCPD_SR_RXMSGEND         UCPD_SR_RXMSGEND         /*!< Rx message received                           */
#define LL_UCPD_SR_RXERR            UCPD_SR_RXERR            /*!< Rx error                                      */
#define LL_UCPD_SR_TYPECEVT1        UCPD_SR_TYPECEVT1        /*!< Type-C voltage level event on CC1             */
#define LL_UCPD_SR_TYPECEVT2        UCPD_SR_TYPECEVT2        /*!< Type-C voltage level event on CC2             */
#define LL_UCPD_SR_TYPEC_VSTATE_CC1 UCPD_SR_TYPEC_VSTATE_CC1 /*!< Status of DC level on CC1 pin                 */
#define LL_UCPD_SR_TYPEC_VSTATE_CC2 UCPD_SR_TYPEC_VSTATE_CC2 /*!< Status of DC level on CC2 pin                 */
#define LL_UCPD_SR_FRSEVT           UCPD_SR_FRSEVT           /*!< Fast Role Swap detection event                */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_IT Interrupts definition
  * @brief    IT defines which can be used with LL_UCPD_READ_REG and LL_UCPD_WRITE_REG functions.
  * @{
  */

#define LL_UCPD_IMR_TXIS      UCPD_IMR_TXISIE      /*!< Enable transmit interrupt status                     */
#define LL_UCPD_IMR_TXMSGDISC UCPD_IMR_TXMSGDISCIE /*!< Enable transmit message discarded interrupt          */
#define LL_UCPD_IMR_TXMSGSENT UCPD_IMR_TXMSGSENTIE /*!< Enable transmit message sent interrupt               */
#define LL_UCPD_IMR_TXMSGABT  UCPD_IMR_TXMSGABTIE  /*!< Enable transmit message abort interrupt              */
#define LL_UCPD_IMR_HRSTDISC  UCPD_IMR_HRSTDISCIE  /*!< Enable HRST discarded interrupt                      */
#define LL_UCPD_IMR_HRSTSENT  UCPD_IMR_HRSTSENTIE  /*!< Enable HRST sent interrupt                           */
#define LL_UCPD_IMR_TXUND     UCPD_IMR_TXUNDIE     /*!< Enable tx data underrun condition interrupt          */
#define LL_UCPD_IMR_RXNE      UCPD_IMR_RXNEIE      /*!< Enable Receive data register not empty interrupt     */
#define LL_UCPD_IMR_RXORDDET  UCPD_IMR_RXORDDETIE  /*!< Enable Rx ordered set (4 K-codes) detected interrupt */
#define LL_UCPD_IMR_RXHRSTDET UCPD_IMR_RXHRSTDETIE /*!< Enable Rx Hard Reset detect interrupt                */
#define LL_UCPD_IMR_RXOVR     UCPD_IMR_RXOVRIE     /*!< Enable Rx data overflow interrupt                    */
#define LL_UCPD_IMR_RXMSGEND  UCPD_IMR_RXMSGENDIE  /*!< Enable Rx message received                           */
#define LL_UCPD_IMR_TYPECEVT1 UCPD_IMR_TYPECEVT1IE /*!< Enable Type-C voltage level event on CC1             */
#define LL_UCPD_IMR_TYPECEVT2 UCPD_IMR_TYPECEVT2IE /*!< Enable Type-C voltage level event on CC2             */
#define LL_UCPD_IMR_FRSEVT    UCPD_IMR_FRSEVTIE    /*!< Enable Fast Role Swap detection event                */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_ORDERSET Tx ordered sets definition
  * @brief    Definition of the usual Tx ordered sets.
  * @{
  */

#define LL_UCPD_SYNC1 (0x18U) /*!< K-code for Startsynch #1     */
#define LL_UCPD_SYNC2 (0x11U) /*!< K-code for Startsynch #2     */
#define LL_UCPD_SYNC3 (0x06U) /*!< K-code for Startsynch #3     */
#define LL_UCPD_RST1  (0x07U) /*!< K-code for Hard Reset #1     */
#define LL_UCPD_RST2  (0x19U) /*!< K-code for Hard Reset #2     */
#define LL_UCPD_EOP   (0x0DU) /*!< K-code for EOP End of Packet */

/*!< SOP Ordered set coding */
#define LL_UCPD_TX_ORDERED_SET_SOP         ((uint32_t)(LL_UCPD_SYNC1)             \
                                            | ((uint32_t)(LL_UCPD_SYNC1) << 5U)   \
                                            | ((uint32_t)(LL_UCPD_SYNC1) << 10U)  \
                                            | ((uint32_t)(LL_UCPD_SYNC2) << 15U))

/*!< SOP' Ordered set coding */
#define LL_UCPD_TX_ORDERED_SET_SOP1        ((uint32_t)(LL_UCPD_SYNC1)             \
                                            | ((uint32_t)(LL_UCPD_SYNC1) << 5U)   \
                                            | ((uint32_t)(LL_UCPD_SYNC3) << 10U)  \
                                            | ((uint32_t)(LL_UCPD_SYNC3) << 15U))

/*!< SOP'' Ordered set coding */
#define LL_UCPD_TX_ORDERED_SET_SOP2        ((uint32_t)(LL_UCPD_SYNC1)             \
                                            | ((uint32_t)(LL_UCPD_SYNC3) << 5U)   \
                                            | ((uint32_t)(LL_UCPD_SYNC1) << 10U)  \
                                            | ((uint32_t)(LL_UCPD_SYNC3) << 15U))

/*!< Hard Reset Ordered set coding */
#define LL_UCPD_TX_ORDERED_SET_HARD_RESET  ((uint32_t)(LL_UCPD_RST1)              \
                                            | ((uint32_t)(LL_UCPD_RST1) << 5U)    \
                                            | ((uint32_t)(LL_UCPD_RST1) << 10U)   \
                                            | ((uint32_t)(LL_UCPD_RST2) << 15U))

/*!< Cable Reset Ordered set coding */
#define LL_UCPD_TX_ORDERED_SET_CABLE_RESET ((uint32_t)(LL_UCPD_RST1)              \
                                            | ((uint32_t)(LL_UCPD_SYNC1) << 5U)   \
                                            | ((uint32_t)(LL_UCPD_RST1) << 10U)   \
                                            | ((uint32_t)(LL_UCPD_SYNC3) << 15U))

/*!< SOP' Debug Ordered set coding */
#define LL_UCPD_TX_ORDERED_SET_SOP1_DEBUG  ((uint32_t)(LL_UCPD_SYNC1)             \
                                            | ((uint32_t)(LL_UCPD_RST2) << 5U)    \
                                            | ((uint32_t)(LL_UCPD_RST2) << 10U)   \
                                            | ((uint32_t)(LL_UCPD_SYNC3) << 15U))

/*!< SOP'' Debug Ordered set coding */
#define LL_UCPD_TX_ORDERED_SET_SOP2_DEBUG  ((uint32_t)(LL_UCPD_SYNC1)             \
                                            | ((uint32_t)(LL_UCPD_RST2) << 5U)    \
                                            | ((uint32_t)(LL_UCPD_SYNC3) << 10U)  \
                                            | ((uint32_t)(LL_UCPD_SYNC2) << 15U))

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_MODE Role mode
  * @{
  */

#define LL_UCPD_ROLE_SNK UCPD_CR_ANAMODE /*!< Mode SNK Rd */
#define LL_UCPD_ROLE_SRC (0x0U)          /*!< Mode SRC Rp */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_RESISTOR Resistor value
  * @{
  */

#define LL_UCPD_RESISTOR_DEFAULT UCPD_CR_ANASUBMODE_0 /*!< Rp default  */
#define LL_UCPD_RESISTOR_1_5A    UCPD_CR_ANASUBMODE_1 /*!< Rp 1.5 A    */
#define LL_UCPD_RESISTOR_3_0A    UCPD_CR_ANASUBMODE   /*!< Rp 3.0 A    */
#define LL_UCPD_RESISTOR_NONE    (0x0U)               /*!< No resistor */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_CFGR1_ORDERSET Rx ordered set configuration
  * @{
  */

#define LL_UCPD_RX_ORDERED_SET_SOP        UCPD_CFGR1_RXORDSETEN_0 /*!< SOP Ordered set detection enabled             */
#define LL_UCPD_RX_ORDERED_SET_SOP1       UCPD_CFGR1_RXORDSETEN_1 /*!< SOP' Ordered set detection enabled            */
#define LL_UCPD_RX_ORDERED_SET_SOP2       UCPD_CFGR1_RXORDSETEN_2 /*!< SOP'' Ordered set detection enabled           */
#define LL_UCPD_RX_ORDERED_SET_HARD_RST   UCPD_CFGR1_RXORDSETEN_3 /*!< Hard Reset Ordered set detection enabled      */
#define LL_UCPD_RX_ORDERED_SET_CABLE_RST  UCPD_CFGR1_RXORDSETEN_4 /*!< Cable Reset Ordered set detection enabled     */
#define LL_UCPD_RX_ORDERED_SET_SOP1_DEBUG UCPD_CFGR1_RXORDSETEN_5 /*!< SOP' Debug Ordered set detection enabled      */
#define LL_UCPD_RX_ORDERED_SET_SOP2_DEBUG UCPD_CFGR1_RXORDSETEN_6 /*!< SOP'' Debug Ordered set detection enabled     */
#define LL_UCPD_RX_ORDERED_SET_SOP_EXT1   UCPD_CFGR1_RXORDSETEN_7 /*!< SOP extension#1 Ordered set detection enabled */
#define LL_UCPD_RX_ORDERED_SET_SOP_EXT2   UCPD_CFGR1_RXORDSETEN_8 /*!< SOP extension#2 Ordered set detection enabled */
#define LL_UCPD_RX_ORDERED_SET_NONE       (0x0U)                  /*!< Ordered set detection disabled                */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_Vstate Voltage state on CCx line
  * @{
  */

#define LL_UCPD_CC1_VSTATE_LOWEST  (0x00U)                         /*!< Voltage level on CC1 line is lowest  */
#define LL_UCPD_CC1_VSTATE_LOW     UCPD_SR_TYPEC_VSTATE_CC1_0      /*!< Voltage level on CC1 line is low     */
#define LL_UCPD_CC1_VSTATE_HIGH    UCPD_SR_TYPEC_VSTATE_CC1_1      /*!< Voltage level on CC1 line is high    */
#define LL_UCPD_CC1_VSTATE_HIGHEST (UCPD_SR_TYPEC_VSTATE_CC1_0 \
                                    | UCPD_SR_TYPEC_VSTATE_CC1_1)   /*!< Voltage level on CC1 line is highest */
#define LL_UCPD_CC2_VSTATE_LOWEST  (0x00U)                         /*!< Voltage level on CC2 line is lowest  */
#define LL_UCPD_CC2_VSTATE_LOW     UCPD_SR_TYPEC_VSTATE_CC2_0      /*!< Voltage level on CC2 line is low     */
#define LL_UCPD_CC2_VSTATE_HIGH    UCPD_SR_TYPEC_VSTATE_CC2_1      /*!< Voltage level on CC2 line is high    */
#define LL_UCPD_CC2_VSTATE_HIGHEST (UCPD_SR_TYPEC_VSTATE_CC2_0 \
                                    | UCPD_SR_TYPEC_VSTATE_CC2_1)   /*!< Voltage level on CC2 line is highest */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_PSC Prescaler for UCPDCLK
  * @{
  */

#define LL_UCPD_PSC_DIV1  (0x0U)                        /*!< Bypass pre-scaling / divide by 1  */
#define LL_UCPD_PSC_DIV2  UCPD_CFGR1_PSC_UCPDCLK_0      /*!< Pre-scale clock by dividing by 2  */
#define LL_UCPD_PSC_DIV4  UCPD_CFGR1_PSC_UCPDCLK_1      /*!< Pre-scale clock by dividing by 4  */
#define LL_UCPD_PSC_DIV8  (UCPD_CFGR1_PSC_UCPDCLK_1 \
                           | UCPD_CFGR1_PSC_UCPDCLK_0)   /*!< Pre-scale clock by dividing by 8  */
#define LL_UCPD_PSC_DIV16 UCPD_CFGR1_PSC_UCPDCLK_2      /*!< Pre-scale clock by dividing by 16 */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_HBITCLKDIV Divider for producing half-bit clock hbit_clk from ucpd_clk
  * @{
  */

#define LL_UCPD_HBITCLK_DIV1  (0x00U)
#define LL_UCPD_HBITCLK_DIV2  (0x01U)
#define LL_UCPD_HBITCLK_DIV3  (0x02U)
#define LL_UCPD_HBITCLK_DIV4  (0x03U)
#define LL_UCPD_HBITCLK_DIV5  (0x04U)
#define LL_UCPD_HBITCLK_DIV6  (0x05U)
#define LL_UCPD_HBITCLK_DIV7  (0x06U)
#define LL_UCPD_HBITCLK_DIV8  (0x07U)
#define LL_UCPD_HBITCLK_DIV9  (0x08U)
#define LL_UCPD_HBITCLK_DIV10 (0x09U)
#define LL_UCPD_HBITCLK_DIV11 (0x0AU)
#define LL_UCPD_HBITCLK_DIV12 (0x0BU)
#define LL_UCPD_HBITCLK_DIV13 (0x0CU)
#define LL_UCPD_HBITCLK_DIV14 (0x0DU)
#define LL_UCPD_HBITCLK_DIV15 (0x0EU)
#define LL_UCPD_HBITCLK_DIV16 (0x0FU)
#define LL_UCPD_HBITCLK_DIV17 (0x10U)
#define LL_UCPD_HBITCLK_DIV18 (0x11U)
#define LL_UCPD_HBITCLK_DIV19 (0x12U)
#define LL_UCPD_HBITCLK_DIV20 (0x13U)
#define LL_UCPD_HBITCLK_DIV21 (0x14U)
#define LL_UCPD_HBITCLK_DIV22 (0x15U)
#define LL_UCPD_HBITCLK_DIV23 (0x16U)
#define LL_UCPD_HBITCLK_DIV24 (0x17U)
#define LL_UCPD_HBITCLK_DIV25 (0x18U)
#define LL_UCPD_HBITCLK_DIV26 (0x19U)
#define LL_UCPD_HBITCLK_DIV27 (0x1AU)
#define LL_UCPD_HBITCLK_DIV28 (0x1BU)
#define LL_UCPD_HBITCLK_DIV29 (0x1CU)
#define LL_UCPD_HBITCLK_DIV30 (0x1DU)
#define LL_UCPD_HBITCLK_DIV31 (0x1EU)
#define LL_UCPD_HBITCLK_DIV32 (0x1FU)
#define LL_UCPD_HBITCLK_DIV33 (0x20U)
#define LL_UCPD_HBITCLK_DIV34 (0x21U)
#define LL_UCPD_HBITCLK_DIV35 (0x22U)
#define LL_UCPD_HBITCLK_DIV36 (0x23U)
#define LL_UCPD_HBITCLK_DIV37 (0x24U)
#define LL_UCPD_HBITCLK_DIV38 (0x25U)
#define LL_UCPD_HBITCLK_DIV39 (0x26U)
#define LL_UCPD_HBITCLK_DIV40 (0x27U)
#define LL_UCPD_HBITCLK_DIV41 (0x28U)
#define LL_UCPD_HBITCLK_DIV42 (0x29U)
#define LL_UCPD_HBITCLK_DIV43 (0x2AU)
#define LL_UCPD_HBITCLK_DIV44 (0x2BU)
#define LL_UCPD_HBITCLK_DIV45 (0x2CU)
#define LL_UCPD_HBITCLK_DIV46 (0x2DU)
#define LL_UCPD_HBITCLK_DIV47 (0x2EU)
#define LL_UCPD_HBITCLK_DIV48 (0x2FU)
#define LL_UCPD_HBITCLK_DIV49 (0x30U)
#define LL_UCPD_HBITCLK_DIV50 (0x31U)
#define LL_UCPD_HBITCLK_DIV51 (0x32U)
#define LL_UCPD_HBITCLK_DIV52 (0x33U)
#define LL_UCPD_HBITCLK_DIV53 (0x34U)
#define LL_UCPD_HBITCLK_DIV54 (0x35U)
#define LL_UCPD_HBITCLK_DIV55 (0x36U)
#define LL_UCPD_HBITCLK_DIV56 (0x37U)
#define LL_UCPD_HBITCLK_DIV57 (0x38U)
#define LL_UCPD_HBITCLK_DIV58 (0x39U)
#define LL_UCPD_HBITCLK_DIV59 (0x3AU)
#define LL_UCPD_HBITCLK_DIV60 (0x3BU)
#define LL_UCPD_HBITCLK_DIV61 (0x3CU)
#define LL_UCPD_HBITCLK_DIV62 (0x3DU)
#define LL_UCPD_HBITCLK_DIV63 (0x3EU)
#define LL_UCPD_HBITCLK_DIV64 (0x3FU)

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_TRANSWINDIV Divider for producing transition window duration from hbit_clk
  * @{
  */

#define LL_UCPD_TRANSWIN_DIVINVALID (0x00U) /*!< Not supported         */
#define LL_UCPD_TRANSWIN_DIV2       (0x01U) /*!< Divide hbit_clk by 2  */
#define LL_UCPD_TRANSWIN_DIV3       (0x02U) /*!< Divide hbit_clk by 3  */
#define LL_UCPD_TRANSWIN_DIV4       (0x03U) /*!< Divide hbit_clk by 4  */
#define LL_UCPD_TRANSWIN_DIV5       (0x04U) /*!< Divide hbit_clk by 5  */
#define LL_UCPD_TRANSWIN_DIV6       (0x05U) /*!< Divide hbit_clk by 6  */
#define LL_UCPD_TRANSWIN_DIV7       (0x06U) /*!< Divide hbit_clk by 7  */
#define LL_UCPD_TRANSWIN_DIV8       (0x07U) /*!< Divide hbit_clk by 8  */
#define LL_UCPD_TRANSWIN_DIV9       (0x08U) /*!< Divide hbit_clk by 9  */
#define LL_UCPD_TRANSWIN_DIV10      (0x09U) /*!< Divide hbit_clk by 10 */
#define LL_UCPD_TRANSWIN_DIV11      (0x0AU) /*!< Divide hbit_clk by 11 */
#define LL_UCPD_TRANSWIN_DIV12      (0x0BU) /*!< Divide hbit_clk by 12 */
#define LL_UCPD_TRANSWIN_DIV13      (0x0CU) /*!< Divide hbit_clk by 13 */
#define LL_UCPD_TRANSWIN_DIV14      (0x0DU) /*!< Divide hbit_clk by 14 */
#define LL_UCPD_TRANSWIN_DIV15      (0x0EU) /*!< Divide hbit_clk by 15 */
#define LL_UCPD_TRANSWIN_DIV16      (0x0FU) /*!< Divide hbit_clk by 16 */
#define LL_UCPD_TRANSWIN_DIV17      (0x10U) /*!< Divide hbit_clk by 17 */
#define LL_UCPD_TRANSWIN_DIV18      (0x11U) /*!< Divide hbit_clk by 18 */
#define LL_UCPD_TRANSWIN_DIV19      (0x12U) /*!< Divide hbit_clk by 19 */
#define LL_UCPD_TRANSWIN_DIV20      (0x13U) /*!< Divide hbit_clk by 20 */
#define LL_UCPD_TRANSWIN_DIV21      (0x14U) /*!< Divide hbit_clk by 21 */
#define LL_UCPD_TRANSWIN_DIV22      (0x15U) /*!< Divide hbit_clk by 22 */
#define LL_UCPD_TRANSWIN_DIV23      (0x16U) /*!< Divide hbit_clk by 23 */
#define LL_UCPD_TRANSWIN_DIV24      (0x17U) /*!< Divide hbit_clk by 24 */
#define LL_UCPD_TRANSWIN_DIV25      (0x18U) /*!< Divide hbit_clk by 25 */
#define LL_UCPD_TRANSWIN_DIV26      (0x19U) /*!< Divide hbit_clk by 26 */
#define LL_UCPD_TRANSWIN_DIV27      (0x1AU) /*!< Divide hbit_clk by 27 */
#define LL_UCPD_TRANSWIN_DIV28      (0x1BU) /*!< Divide hbit_clk by 28 */
#define LL_UCPD_TRANSWIN_DIV29      (0x1CU) /*!< Divide hbit_clk by 29 */
#define LL_UCPD_TRANSWIN_DIV30      (0x1DU) /*!< Divide hbit_clk by 30 */
#define LL_UCPD_TRANSWIN_DIV31      (0x1EU) /*!< Divide hbit_clk by 31 */
#define LL_UCPD_TRANSWIN_DIV32      (0x1FU) /*!< Divide hbit_clk by 32 */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_IFRGAPDIV Divider for producing inter-frame gap timer clock from ucpd_clk
  * @{
  */

#define LL_UCPD_IFRGAP_DIVINVALID (0x00U) /*!< Not supported         */
#define LL_UCPD_IFRGAP_DIV2       (0x01U) /*!< Divide ucpd_clk by 2  */
#define LL_UCPD_IFRGAP_DIV3       (0x02U) /*!< Divide ucpd_clk by 3  */
#define LL_UCPD_IFRGAP_DIV4       (0x03U) /*!< Divide ucpd_clk by 4  */
#define LL_UCPD_IFRGAP_DIV5       (0x04U) /*!< Divide ucpd_clk by 5  */
#define LL_UCPD_IFRGAP_DIV6       (0x05U) /*!< Divide ucpd_clk by 6  */
#define LL_UCPD_IFRGAP_DIV7       (0x06U) /*!< Divide ucpd_clk by 7  */
#define LL_UCPD_IFRGAP_DIV8       (0x07U) /*!< Divide ucpd_clk by 8  */
#define LL_UCPD_IFRGAP_DIV9       (0x08U) /*!< Divide ucpd_clk by 9  */
#define LL_UCPD_IFRGAP_DIV10      (0x09U) /*!< Divide ucpd_clk by 10 */
#define LL_UCPD_IFRGAP_DIV11      (0x0AU) /*!< Divide ucpd_clk by 11 */
#define LL_UCPD_IFRGAP_DIV12      (0x0BU) /*!< Divide ucpd_clk by 12 */
#define LL_UCPD_IFRGAP_DIV13      (0x0CU) /*!< Divide ucpd_clk by 13 */
#define LL_UCPD_IFRGAP_DIV14      (0x0DU) /*!< Divide ucpd_clk by 14 */
#define LL_UCPD_IFRGAP_DIV15      (0x0EU) /*!< Divide ucpd_clk by 15 */
#define LL_UCPD_IFRGAP_DIV16      (0x0FU) /*!< Divide ucpd_clk by 16 */
#define LL_UCPD_IFRGAP_DIV17      (0x10U) /*!< Divide ucpd_clk by 17 */
#define LL_UCPD_IFRGAP_DIV18      (0x11U) /*!< Divide ucpd_clk by 18 */
#define LL_UCPD_IFRGAP_DIV19      (0x12U) /*!< Divide ucpd_clk by 19 */
#define LL_UCPD_IFRGAP_DIV20      (0x13U) /*!< Divide ucpd_clk by 20 */
#define LL_UCPD_IFRGAP_DIV21      (0x14U) /*!< Divide ucpd_clk by 21 */
#define LL_UCPD_IFRGAP_DIV22      (0x15U) /*!< Divide ucpd_clk by 22 */
#define LL_UCPD_IFRGAP_DIV23      (0x16U) /*!< Divide ucpd_clk by 23 */
#define LL_UCPD_IFRGAP_DIV24      (0x17U) /*!< Divide ucpd_clk by 24 */
#define LL_UCPD_IFRGAP_DIV25      (0x18U) /*!< Divide ucpd_clk by 25 */
#define LL_UCPD_IFRGAP_DIV26      (0x19U) /*!< Divide ucpd_clk by 26 */
#define LL_UCPD_IFRGAP_DIV27      (0x1AU) /*!< Divide ucpd_clk by 27 */
#define LL_UCPD_IFRGAP_DIV28      (0x1BU) /*!< Divide ucpd_clk by 28 */
#define LL_UCPD_IFRGAP_DIV29      (0x1CU) /*!< Divide ucpd_clk by 29 */
#define LL_UCPD_IFRGAP_DIV30      (0x1DU) /*!< Divide ucpd_clk by 30 */
#define LL_UCPD_IFRGAP_DIV31      (0x1EU) /*!< Divide ucpd_clk by 31 */
#define LL_UCPD_IFRGAP_DIV32      (0x1FU) /*!< Divide ucpd_clk by 32 */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_RXFILT2N3 BMC decoder Rx pre-filter sampling method
  * @{
  */

#define LL_UCPD_RX_PREFILTER_3SAMPLES (0x0U) /*!< 3 samples method for BMC decoder Rx pre-filter */
#define LL_UCPD_RX_PREFILTER_2SAMPLES (0x1U) /*!< 2 samples method for BMC decoder Rx pre-filter */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_CCENABLE CC pin enable
  * @{
  */

#define LL_UCPD_CCENABLE_NONE   (0x0U)                  /*!< Neither PHY is activated           */
#define LL_UCPD_CCENABLE_CC1    UCPD_CR_CCENABLE_0      /*!< Controls apply to only CC1         */
#define LL_UCPD_CCENABLE_CC2    UCPD_CR_CCENABLE_1      /*!< Controls apply to only CC1         */
#define LL_UCPD_CCENABLE_CC1CC2 (UCPD_CR_CCENABLE_0  \
                                 | UCPD_CR_CCENABLE_1)   /*!< Controls apply to both CC1 and CC2 */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_CCPIN CC pin selection
  * @{
  */

#define LL_UCPD_CCPIN_CC1 (0x0U)           /*!< Use CC1 IO for power delivery communication */
#define LL_UCPD_CCPIN_CC2 UCPD_CR_PHYCCSEL /*!< Use CC2 IO for power delivery communication */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_RXMODE Receiver mode
  * @{
  */

#define LL_UCPD_RXMODE_NORMAL         (0x0U)         /*!< Normal receive mode                     */
#define LL_UCPD_RXMODE_BIST_TEST_DATA UCPD_CR_RXMODE /*!< BIST receive mode (BIST Test Data Mode) */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_TXMODE Type of Tx packet
  * @{
  */

#define LL_UCPD_TXMODE_NORMAL        (0x0U)           /*!< Initiate the transfer of a Tx message                   */
#define LL_UCPD_TXMODE_CABLE_RESET   UCPD_CR_TXMODE_0 /*!< Trigger a the transfer of a Cable Reset sequence        */
#define LL_UCPD_TXMODE_BIST_CARRIER2 UCPD_CR_TXMODE_1 /*!< Trigger a BIST test sequence send (BIST Carrier Mode 2) */

/**
  * @}
  */

/** @defgroup UCPD_LL_EC_RXORDSET Detected Rx ordered set code
  * @{
  */
/*!< SOP code detected in receiver             */
#define LL_UCPD_RX_ORDERED_SET_DETECT_SOP         (0x0U)
/*!< SOP' code detected in receiver            */
#define LL_UCPD_RX_ORDERED_SET_DETECT_SOP1        UCPD_RX_ORDSETR_RXORDSET_0
/*!< SOP'' code detected in receiver           */
#define LL_UCPD_RX_ORDERED_SET_DETECT_SOP2        UCPD_RX_ORDSETR_RXORDSET_1
/*!< SOP' Debug code detected in receiver      */
#define LL_UCPD_RX_ORDERED_SET_DETECT_SOP1_DEBUG  (UCPD_RX_ORDSETR_RXORDSET_0 | UCPD_RX_ORDSETR_RXORDSET_1)
/*!< SOP'' Debug code detected in receiver     */
#define LL_UCPD_RX_ORDERED_SET_DETECT_SOP2_DEBUG  UCPD_RX_ORDSETR_RXORDSET_2
/*!< Cable Reset code detected in receiver     */
#define LL_UCPD_RX_ORDERED_SET_DETECT_CABLE_RESET (UCPD_RX_ORDSETR_RXORDSET_2 | UCPD_RX_ORDSETR_RXORDSET_0)
/*!< SOP extension#1 code detected in receiver */
#define LL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT1     (UCPD_RX_ORDSETR_RXORDSET_2 | UCPD_RX_ORDSETR_RXORDSET_1)
/*!< SOP extension#2 code detected in receiver */
#define LL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT2     (UCPD_RX_ORDSETR_RXORDSET_2      \
                                                   | UCPD_RX_ORDSETR_RXORDSET_1    \
                                                   | UCPD_RX_ORDSETR_RXORDSET_0)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup UCPD_LL_Exported_Macros LL UCPD Macros
  * @{
  */

/** @defgroup UCPD_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in UCPD register.
  * @param  instance UCPD Instance.
  * @param  reg Register to be written.
  * @param  value Value to be written in the register.
  */
#define LL_UCPD_WRITE_REG(instance, reg, value) STM32_WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in UCPD register.
  * @param  instance UCPD Instance.
  * @param  reg Register to be read.
  * @retval Register value.
  */
#define LL_UCPD_READ_REG(instance, reg) STM32_READ_REG((instance)->reg)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup UCPD_LL_Exported_Functions LL UCPD Functions
  * @{
  */

/** @defgroup UCPD_LL_EF_Configuration Configuration
  * @{
  */

/** @defgroup UCPD_LL_EF_CFGR1 CFGR1 register
  * @{
  */

/**
  * @brief  Enable UCPD peripheral.
  * @rmtoll
  *  CFGR1          UCPDEN          LL_UCPD_Enable
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_Enable(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CFGR1, UCPD_CFGR1_UCPDEN);
}

/**
  * @brief  Disable UCPD peripheral.
  * @rmtoll
  *  CFGR1          UCPDEN          LL_UCPD_Disable
  * @param  p_ucpd UCPD Instance.
  * @note   When disabling the UCPD, follow the procedure described in the Reference Manual.
  */
__STATIC_INLINE void LL_UCPD_Disable(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CFGR1, UCPD_CFGR1_UCPDEN);
}

/**
  * @brief  Check if UCPD peripheral is enabled.
  * @rmtoll
  *  CFGR1          UCPDEN          LL_UCPD_IsEnabled
  * @param  p_ucpd UCPD Instance.
  * @retval 0 UCPD peripheral is disabled.
  * @retval 1 UCPD peripheral is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabled(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_UCPDEN) == (UCPD_CFGR1_UCPDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the receiver ordered set detection enable.
  * @rmtoll
  *  CFGR1          RXORDSETEN          LL_UCPD_SetRxOrderSet
  * @param  p_ucpd UCPD Instance.
  * @param  order_set This parameter can be combination of the following values:
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP1
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP2
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_HARD_RST
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_CABLE_RST
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP1_DEBUG
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP2_DEBUG
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP_EXT1
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP_EXT2
  */
__STATIC_INLINE void LL_UCPD_SetRxOrderSet(UCPD_TypeDef *p_ucpd, uint32_t order_set)
{
  STM32_MODIFY_REG(p_ucpd->CFGR1, UCPD_CFGR1_RXORDSETEN, order_set);
}

/**
  * @brief  Get the receiver ordered set detection enable.
  * @rmtoll
  *  CFGR1          RXORDSETEN          LL_UCPD_GetRxOrderSet
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP1
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP2
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_HARD_RST
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_CABLE_RST
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP1_DEBUG
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP2_DEBUG
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP_EXT1
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_SOP_EXT2
  */
__STATIC_INLINE uint32_t LL_UCPD_GetRxOrderSet(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_RXORDSETEN));
}

/**
  * @brief  Configure CFGR1 static settings in one write.
  * @rmtoll
  *  CFGR1          PSC_UCPDCLK/HBITCLKDIV/TRANSWIN/IFRGAP/RXORDSETEN  LL_UCPD_Config
  * @param  p_ucpd UCPD Instance.
  * @param  clk_psc This parameter can be one of the UCPD_LL_EC_PSC group values
  * @param  hbitclk_div This parameter can be one of the UCPD_LL_EC_HBITCLKDIV group values
  * @param  transwin_div This parameter can be one of the UCPD_LL_EC_TRANSWINDIV group values
  * @param  ifrgap_div This parameter can be one of the UCPD_LL_EC_IFRGAPDIV group values
  * @param  rx_ordered_set This parameter can be a combination of the UCPD_LL_EC_CFGR1_ORDERSET group values
  */
__STATIC_INLINE void LL_UCPD_Config(UCPD_TypeDef *p_ucpd,
                                    uint32_t clk_psc,
                                    uint32_t hbitclk_div,
                                    uint32_t transwin_div,
                                    uint32_t ifrgap_div,
                                    uint32_t rx_ordered_set)
{
  STM32_MODIFY_REG(p_ucpd->CFGR1,
                   UCPD_CFGR1_PSC_UCPDCLK | UCPD_CFGR1_HBITCLKDIV | UCPD_CFGR1_TRANSWIN |
                   UCPD_CFGR1_IFRGAP | UCPD_CFGR1_RXORDSETEN,
                   clk_psc |
                   (hbitclk_div << UCPD_CFGR1_HBITCLKDIV_Pos) |
                   (transwin_div << UCPD_CFGR1_TRANSWIN_Pos) |
                   (ifrgap_div << UCPD_CFGR1_IFRGAP_Pos) |
                   rx_ordered_set);
}

/**
  * @brief  Set the prescaler for UCPD clock.
  * @rmtoll
  *  CFGR1          UCPDCLK          LL_UCPD_SetPSCClk
  * @param  p_ucpd UCPD Instance.
  * @param  psc This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_PSC_DIV1
  *         @arg @ref LL_UCPD_PSC_DIV2
  *         @arg @ref LL_UCPD_PSC_DIV4
  *         @arg @ref LL_UCPD_PSC_DIV8
  *         @arg @ref LL_UCPD_PSC_DIV16
  */
__STATIC_INLINE void LL_UCPD_SetPSCClk(UCPD_TypeDef *p_ucpd, uint32_t psc)
{
  STM32_MODIFY_REG(p_ucpd->CFGR1, UCPD_CFGR1_PSC_UCPDCLK, psc);
}

/**
  * @brief  Get the prescaler for UCPD clock.
  * @rmtoll
  *  CFGR1          UCPDCLK          LL_UCPD_GetPSCClk
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_PSC_DIV1
  *         @arg @ref LL_UCPD_PSC_DIV2
  *         @arg @ref LL_UCPD_PSC_DIV4
  *         @arg @ref LL_UCPD_PSC_DIV8
  *         @arg @ref LL_UCPD_PSC_DIV16
  */
__STATIC_INLINE uint32_t LL_UCPD_GetPSCClk(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_PSC_UCPDCLK));
}

/**
  * @brief  Set the clock divider producing transition window clock from hbit_clk.
  * @rmtoll
  *  CFGR1          TRANSWIN          LL_UCPD_SetTransWin
  * @param  p_ucpd UCPD Instance.
  * @param  trans_win This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_TRANSWIN_DIV2
  *         @arg @ref LL_UCPD_TRANSWIN_DIV3
  *         @arg @ref LL_UCPD_TRANSWIN_DIV4
  *         @arg @ref LL_UCPD_TRANSWIN_DIV5
  *         @arg @ref LL_UCPD_TRANSWIN_DIV6
  *         @arg @ref LL_UCPD_TRANSWIN_DIV7
  *         @arg @ref LL_UCPD_TRANSWIN_DIV8
  *         @arg @ref LL_UCPD_TRANSWIN_DIV9
  *         @arg @ref LL_UCPD_TRANSWIN_DIV10
  *         @arg @ref LL_UCPD_TRANSWIN_DIV11
  *         @arg @ref LL_UCPD_TRANSWIN_DIV12
  *         @arg @ref LL_UCPD_TRANSWIN_DIV13
  *         @arg @ref LL_UCPD_TRANSWIN_DIV14
  *         @arg @ref LL_UCPD_TRANSWIN_DIV15
  *         @arg @ref LL_UCPD_TRANSWIN_DIV16
  *         @arg @ref LL_UCPD_TRANSWIN_DIV17
  *         @arg @ref LL_UCPD_TRANSWIN_DIV18
  *         @arg @ref LL_UCPD_TRANSWIN_DIV19
  *         @arg @ref LL_UCPD_TRANSWIN_DIV20
  *         @arg @ref LL_UCPD_TRANSWIN_DIV21
  *         @arg @ref LL_UCPD_TRANSWIN_DIV22
  *         @arg @ref LL_UCPD_TRANSWIN_DIV23
  *         @arg @ref LL_UCPD_TRANSWIN_DIV24
  *         @arg @ref LL_UCPD_TRANSWIN_DIV25
  *         @arg @ref LL_UCPD_TRANSWIN_DIV26
  *         @arg @ref LL_UCPD_TRANSWIN_DIV27
  *         @arg @ref LL_UCPD_TRANSWIN_DIV28
  *         @arg @ref LL_UCPD_TRANSWIN_DIV29
  *         @arg @ref LL_UCPD_TRANSWIN_DIV30
  *         @arg @ref LL_UCPD_TRANSWIN_DIV31
  *         @arg @ref LL_UCPD_TRANSWIN_DIV32
  */
__STATIC_INLINE void LL_UCPD_SetTransWin(UCPD_TypeDef *p_ucpd, uint32_t trans_win)
{
  STM32_MODIFY_REG(p_ucpd->CFGR1, UCPD_CFGR1_TRANSWIN, trans_win << UCPD_CFGR1_TRANSWIN_Pos);
}

/**
  * @brief  Get the clock divider producing transition window clock from hbit_clk.
  * @rmtoll
  *  CFGR1          TRANSWIN          LL_UCPD_GetTransWin
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_TRANSWIN_DIV2
  *         @arg @ref LL_UCPD_TRANSWIN_DIV3
  *         @arg @ref LL_UCPD_TRANSWIN_DIV4
  *         @arg @ref LL_UCPD_TRANSWIN_DIV5
  *         @arg @ref LL_UCPD_TRANSWIN_DIV6
  *         @arg @ref LL_UCPD_TRANSWIN_DIV7
  *         @arg @ref LL_UCPD_TRANSWIN_DIV8
  *         @arg @ref LL_UCPD_TRANSWIN_DIV9
  *         @arg @ref LL_UCPD_TRANSWIN_DIV10
  *         @arg @ref LL_UCPD_TRANSWIN_DIV11
  *         @arg @ref LL_UCPD_TRANSWIN_DIV12
  *         @arg @ref LL_UCPD_TRANSWIN_DIV13
  *         @arg @ref LL_UCPD_TRANSWIN_DIV14
  *         @arg @ref LL_UCPD_TRANSWIN_DIV15
  *         @arg @ref LL_UCPD_TRANSWIN_DIV16
  *         @arg @ref LL_UCPD_TRANSWIN_DIV17
  *         @arg @ref LL_UCPD_TRANSWIN_DIV18
  *         @arg @ref LL_UCPD_TRANSWIN_DIV19
  *         @arg @ref LL_UCPD_TRANSWIN_DIV20
  *         @arg @ref LL_UCPD_TRANSWIN_DIV21
  *         @arg @ref LL_UCPD_TRANSWIN_DIV22
  *         @arg @ref LL_UCPD_TRANSWIN_DIV23
  *         @arg @ref LL_UCPD_TRANSWIN_DIV24
  *         @arg @ref LL_UCPD_TRANSWIN_DIV25
  *         @arg @ref LL_UCPD_TRANSWIN_DIV26
  *         @arg @ref LL_UCPD_TRANSWIN_DIV27
  *         @arg @ref LL_UCPD_TRANSWIN_DIV28
  *         @arg @ref LL_UCPD_TRANSWIN_DIV29
  *         @arg @ref LL_UCPD_TRANSWIN_DIV30
  *         @arg @ref LL_UCPD_TRANSWIN_DIV31
  *         @arg @ref LL_UCPD_TRANSWIN_DIV32
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTransWin(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_TRANSWIN) >> UCPD_CFGR1_TRANSWIN_Pos);
}

/**
  * @brief  Set the clock divider value to generate an interframe gap.
  * @rmtoll
  *  CFGR1          IFRGAP          LL_UCPD_SetIfrGap
  * @param  p_ucpd UCPD Instance.
  * @param  ifr_gap This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_IFRGAP_DIV2
  *         @arg @ref LL_UCPD_IFRGAP_DIV3
  *         @arg @ref LL_UCPD_IFRGAP_DIV4
  *         @arg @ref LL_UCPD_IFRGAP_DIV5
  *         @arg @ref LL_UCPD_IFRGAP_DIV6
  *         @arg @ref LL_UCPD_IFRGAP_DIV7
  *         @arg @ref LL_UCPD_IFRGAP_DIV8
  *         @arg @ref LL_UCPD_IFRGAP_DIV9
  *         @arg @ref LL_UCPD_IFRGAP_DIV10
  *         @arg @ref LL_UCPD_IFRGAP_DIV11
  *         @arg @ref LL_UCPD_IFRGAP_DIV12
  *         @arg @ref LL_UCPD_IFRGAP_DIV13
  *         @arg @ref LL_UCPD_IFRGAP_DIV14
  *         @arg @ref LL_UCPD_IFRGAP_DIV15
  *         @arg @ref LL_UCPD_IFRGAP_DIV16
  *         @arg @ref LL_UCPD_IFRGAP_DIV17
  *         @arg @ref LL_UCPD_IFRGAP_DIV18
  *         @arg @ref LL_UCPD_IFRGAP_DIV19
  *         @arg @ref LL_UCPD_IFRGAP_DIV20
  *         @arg @ref LL_UCPD_IFRGAP_DIV21
  *         @arg @ref LL_UCPD_IFRGAP_DIV22
  *         @arg @ref LL_UCPD_IFRGAP_DIV23
  *         @arg @ref LL_UCPD_IFRGAP_DIV24
  *         @arg @ref LL_UCPD_IFRGAP_DIV25
  *         @arg @ref LL_UCPD_IFRGAP_DIV26
  *         @arg @ref LL_UCPD_IFRGAP_DIV27
  *         @arg @ref LL_UCPD_IFRGAP_DIV28
  *         @arg @ref LL_UCPD_IFRGAP_DIV29
  *         @arg @ref LL_UCPD_IFRGAP_DIV30
  *         @arg @ref LL_UCPD_IFRGAP_DIV31
  *         @arg @ref LL_UCPD_IFRGAP_DIV32
  */
__STATIC_INLINE void LL_UCPD_SetIfrGap(UCPD_TypeDef *p_ucpd, uint32_t ifr_gap)
{
  STM32_MODIFY_REG(p_ucpd->CFGR1, UCPD_CFGR1_IFRGAP, ifr_gap << UCPD_CFGR1_IFRGAP_Pos);
}

/**
  * @brief  Get the clock divider value for generating an interframe gap.
  * @rmtoll
  *  CFGR1          IFRGAP          LL_UCPD_GetIfrGap
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_IFRGAP_DIV2
  *         @arg @ref LL_UCPD_IFRGAP_DIV3
  *         @arg @ref LL_UCPD_IFRGAP_DIV4
  *         @arg @ref LL_UCPD_IFRGAP_DIV5
  *         @arg @ref LL_UCPD_IFRGAP_DIV6
  *         @arg @ref LL_UCPD_IFRGAP_DIV7
  *         @arg @ref LL_UCPD_IFRGAP_DIV8
  *         @arg @ref LL_UCPD_IFRGAP_DIV9
  *         @arg @ref LL_UCPD_IFRGAP_DIV10
  *         @arg @ref LL_UCPD_IFRGAP_DIV11
  *         @arg @ref LL_UCPD_IFRGAP_DIV12
  *         @arg @ref LL_UCPD_IFRGAP_DIV13
  *         @arg @ref LL_UCPD_IFRGAP_DIV14
  *         @arg @ref LL_UCPD_IFRGAP_DIV15
  *         @arg @ref LL_UCPD_IFRGAP_DIV16
  *         @arg @ref LL_UCPD_IFRGAP_DIV17
  *         @arg @ref LL_UCPD_IFRGAP_DIV18
  *         @arg @ref LL_UCPD_IFRGAP_DIV19
  *         @arg @ref LL_UCPD_IFRGAP_DIV20
  *         @arg @ref LL_UCPD_IFRGAP_DIV21
  *         @arg @ref LL_UCPD_IFRGAP_DIV22
  *         @arg @ref LL_UCPD_IFRGAP_DIV23
  *         @arg @ref LL_UCPD_IFRGAP_DIV24
  *         @arg @ref LL_UCPD_IFRGAP_DIV25
  *         @arg @ref LL_UCPD_IFRGAP_DIV26
  *         @arg @ref LL_UCPD_IFRGAP_DIV27
  *         @arg @ref LL_UCPD_IFRGAP_DIV28
  *         @arg @ref LL_UCPD_IFRGAP_DIV29
  *         @arg @ref LL_UCPD_IFRGAP_DIV30
  *         @arg @ref LL_UCPD_IFRGAP_DIV31
  *         @arg @ref LL_UCPD_IFRGAP_DIV32
  */
__STATIC_INLINE uint32_t LL_UCPD_GetIfrGap(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_IFRGAP) >> UCPD_CFGR1_IFRGAP_Pos);
}

/**
  * @brief  Set the half bit clock divider.
  * @rmtoll
  *  CFGR1          HBITCLKDIV          LL_UCPD_SetHbitClockDiv
  * @param  p_ucpd UCPD Instance.
  * @param  HbitClock This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_HBITCLK_DIV1
  *         @arg @ref LL_UCPD_HBITCLK_DIV2
  *         @arg @ref LL_UCPD_HBITCLK_DIV3
  *         @arg @ref LL_UCPD_HBITCLK_DIV4
  *         @arg @ref LL_UCPD_HBITCLK_DIV5
  *         @arg @ref LL_UCPD_HBITCLK_DIV6
  *         @arg @ref LL_UCPD_HBITCLK_DIV7
  *         @arg @ref LL_UCPD_HBITCLK_DIV8
  *         @arg @ref LL_UCPD_HBITCLK_DIV9
  *         @arg @ref LL_UCPD_HBITCLK_DIV10
  *         @arg @ref LL_UCPD_HBITCLK_DIV11
  *         @arg @ref LL_UCPD_HBITCLK_DIV12
  *         @arg @ref LL_UCPD_HBITCLK_DIV13
  *         @arg @ref LL_UCPD_HBITCLK_DIV14
  *         @arg @ref LL_UCPD_HBITCLK_DIV15
  *         @arg @ref LL_UCPD_HBITCLK_DIV16
  *         @arg @ref LL_UCPD_HBITCLK_DIV17
  *         @arg @ref LL_UCPD_HBITCLK_DIV18
  *         @arg @ref LL_UCPD_HBITCLK_DIV19
  *         @arg @ref LL_UCPD_HBITCLK_DIV20
  *         @arg @ref LL_UCPD_HBITCLK_DIV21
  *         @arg @ref LL_UCPD_HBITCLK_DIV22
  *         @arg @ref LL_UCPD_HBITCLK_DIV23
  *         @arg @ref LL_UCPD_HBITCLK_DIV24
  *         @arg @ref LL_UCPD_HBITCLK_DIV25
  *         @arg @ref LL_UCPD_HBITCLK_DIV26
  *         @arg @ref LL_UCPD_HBITCLK_DIV27
  *         @arg @ref LL_UCPD_HBITCLK_DIV28
  *         @arg @ref LL_UCPD_HBITCLK_DIV29
  *         @arg @ref LL_UCPD_HBITCLK_DIV30
  *         @arg @ref LL_UCPD_HBITCLK_DIV31
  *         @arg @ref LL_UCPD_HBITCLK_DIV32
  *         @arg @ref LL_UCPD_HBITCLK_DIV33
  *         @arg @ref LL_UCPD_HBITCLK_DIV34
  *         @arg @ref LL_UCPD_HBITCLK_DIV35
  *         @arg @ref LL_UCPD_HBITCLK_DIV36
  *         @arg @ref LL_UCPD_HBITCLK_DIV37
  *         @arg @ref LL_UCPD_HBITCLK_DIV38
  *         @arg @ref LL_UCPD_HBITCLK_DIV39
  *         @arg @ref LL_UCPD_HBITCLK_DIV40
  *         @arg @ref LL_UCPD_HBITCLK_DIV41
  *         @arg @ref LL_UCPD_HBITCLK_DIV42
  *         @arg @ref LL_UCPD_HBITCLK_DIV43
  *         @arg @ref LL_UCPD_HBITCLK_DIV44
  *         @arg @ref LL_UCPD_HBITCLK_DIV45
  *         @arg @ref LL_UCPD_HBITCLK_DIV46
  *         @arg @ref LL_UCPD_HBITCLK_DIV47
  *         @arg @ref LL_UCPD_HBITCLK_DIV48
  *         @arg @ref LL_UCPD_HBITCLK_DIV49
  *         @arg @ref LL_UCPD_HBITCLK_DIV50
  *         @arg @ref LL_UCPD_HBITCLK_DIV51
  *         @arg @ref LL_UCPD_HBITCLK_DIV52
  *         @arg @ref LL_UCPD_HBITCLK_DIV53
  *         @arg @ref LL_UCPD_HBITCLK_DIV54
  *         @arg @ref LL_UCPD_HBITCLK_DIV55
  *         @arg @ref LL_UCPD_HBITCLK_DIV56
  *         @arg @ref LL_UCPD_HBITCLK_DIV57
  *         @arg @ref LL_UCPD_HBITCLK_DIV58
  *         @arg @ref LL_UCPD_HBITCLK_DIV59
  *         @arg @ref LL_UCPD_HBITCLK_DIV60
  *         @arg @ref LL_UCPD_HBITCLK_DIV61
  *         @arg @ref LL_UCPD_HBITCLK_DIV62
  *         @arg @ref LL_UCPD_HBITCLK_DIV63
  *         @arg @ref LL_UCPD_HBITCLK_DIV64
  */
__STATIC_INLINE void LL_UCPD_SetHbitClockDiv(UCPD_TypeDef *p_ucpd, uint32_t HbitClock)
{
  STM32_MODIFY_REG(p_ucpd->CFGR1, UCPD_CFGR1_HBITCLKDIV, HbitClock << UCPD_CFGR1_HBITCLKDIV_Pos);
}

/**
  * @brief  Set the half bit clock divider.
  * @rmtoll
  *  CFGR1          HBITCLKDIV          LL_UCPD_GetHbitClockDiv
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_HBITCLK_DIV1
  *         @arg @ref LL_UCPD_HBITCLK_DIV2
  *         @arg @ref LL_UCPD_HBITCLK_DIV3
  *         @arg @ref LL_UCPD_HBITCLK_DIV4
  *         @arg @ref LL_UCPD_HBITCLK_DIV5
  *         @arg @ref LL_UCPD_HBITCLK_DIV6
  *         @arg @ref LL_UCPD_HBITCLK_DIV7
  *         @arg @ref LL_UCPD_HBITCLK_DIV8
  *         @arg @ref LL_UCPD_HBITCLK_DIV9
  *         @arg @ref LL_UCPD_HBITCLK_DIV10
  *         @arg @ref LL_UCPD_HBITCLK_DIV11
  *         @arg @ref LL_UCPD_HBITCLK_DIV12
  *         @arg @ref LL_UCPD_HBITCLK_DIV13
  *         @arg @ref LL_UCPD_HBITCLK_DIV14
  *         @arg @ref LL_UCPD_HBITCLK_DIV15
  *         @arg @ref LL_UCPD_HBITCLK_DIV16
  *         @arg @ref LL_UCPD_HBITCLK_DIV17
  *         @arg @ref LL_UCPD_HBITCLK_DIV18
  *         @arg @ref LL_UCPD_HBITCLK_DIV19
  *         @arg @ref LL_UCPD_HBITCLK_DIV20
  *         @arg @ref LL_UCPD_HBITCLK_DIV21
  *         @arg @ref LL_UCPD_HBITCLK_DIV22
  *         @arg @ref LL_UCPD_HBITCLK_DIV23
  *         @arg @ref LL_UCPD_HBITCLK_DIV24
  *         @arg @ref LL_UCPD_HBITCLK_DIV25
  *         @arg @ref LL_UCPD_HBITCLK_DIV26
  *         @arg @ref LL_UCPD_HBITCLK_DIV27
  *         @arg @ref LL_UCPD_HBITCLK_DIV28
  *         @arg @ref LL_UCPD_HBITCLK_DIV29
  *         @arg @ref LL_UCPD_HBITCLK_DIV30
  *         @arg @ref LL_UCPD_HBITCLK_DIV31
  *         @arg @ref LL_UCPD_HBITCLK_DIV32
  *         @arg @ref LL_UCPD_HBITCLK_DIV33
  *         @arg @ref LL_UCPD_HBITCLK_DIV34
  *         @arg @ref LL_UCPD_HBITCLK_DIV35
  *         @arg @ref LL_UCPD_HBITCLK_DIV36
  *         @arg @ref LL_UCPD_HBITCLK_DIV37
  *         @arg @ref LL_UCPD_HBITCLK_DIV38
  *         @arg @ref LL_UCPD_HBITCLK_DIV39
  *         @arg @ref LL_UCPD_HBITCLK_DIV40
  *         @arg @ref LL_UCPD_HBITCLK_DIV41
  *         @arg @ref LL_UCPD_HBITCLK_DIV42
  *         @arg @ref LL_UCPD_HBITCLK_DIV43
  *         @arg @ref LL_UCPD_HBITCLK_DIV44
  *         @arg @ref LL_UCPD_HBITCLK_DIV45
  *         @arg @ref LL_UCPD_HBITCLK_DIV46
  *         @arg @ref LL_UCPD_HBITCLK_DIV47
  *         @arg @ref LL_UCPD_HBITCLK_DIV48
  *         @arg @ref LL_UCPD_HBITCLK_DIV49
  *         @arg @ref LL_UCPD_HBITCLK_DIV50
  *         @arg @ref LL_UCPD_HBITCLK_DIV51
  *         @arg @ref LL_UCPD_HBITCLK_DIV52
  *         @arg @ref LL_UCPD_HBITCLK_DIV53
  *         @arg @ref LL_UCPD_HBITCLK_DIV54
  *         @arg @ref LL_UCPD_HBITCLK_DIV55
  *         @arg @ref LL_UCPD_HBITCLK_DIV56
  *         @arg @ref LL_UCPD_HBITCLK_DIV57
  *         @arg @ref LL_UCPD_HBITCLK_DIV58
  *         @arg @ref LL_UCPD_HBITCLK_DIV59
  *         @arg @ref LL_UCPD_HBITCLK_DIV60
  *         @arg @ref LL_UCPD_HBITCLK_DIV61
  *         @arg @ref LL_UCPD_HBITCLK_DIV62
  *         @arg @ref LL_UCPD_HBITCLK_DIV63
  *         @arg @ref LL_UCPD_HBITCLK_DIV64
  */
__STATIC_INLINE uint32_t LL_UCPD_GetHbitClockDiv(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_HBITCLKDIV) >> UCPD_CFGR1_HBITCLKDIV_Pos);
}

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_CFGR2 CFGR2 register
  * @{
  */

/**
  * @brief  Enable the Rx analog filter.
  * @rmtoll
  *  CFGR2          RXAFILTEN          LL_UCPD_EnableRxAnalogFilter
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableRxAnalogFilter(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CFGR2, UCPD_CFGR2_RXAFILTEN);
}

/**
  * @brief  Disable the Rx analog filter.
  * @rmtoll
  *  CFGR2          RXAFILTEN          LL_UCPD_DisableRxAnalogFilter
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableRxAnalogFilter(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CFGR2, UCPD_CFGR2_RXAFILTEN);
}

/**
  * @brief  Check if the Rx analog filter is enabled.
  * @rmtoll
  *  CFGR2          RXAFILTEN          LL_UCPD_IsEnabledRxAnalogFilter
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx analog filter is disabled.
  * @retval 1 Rx analog filter is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledRxAnalogFilter(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CFGR2, UCPD_CFGR2_RXAFILTEN) == UCPD_CFGR2_RXAFILTEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable the wakeup mode.
  * @rmtoll
  *  CFGR2          WUPEN          LL_UCPD_EnableWakeUp
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableWakeUp(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CFGR2, UCPD_CFGR2_WUPEN);
}

/**
  * @brief  Disable the wakeup mode.
  * @rmtoll
  *  CFGR2          WUPEN          LL_UCPD_DisableWakeUp
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableWakeUp(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CFGR2, UCPD_CFGR2_WUPEN);
}

/**
  * @brief  Check if wakeup mode is enabled.
  * @rmtoll
  *  CFGR2          WUPEN          LL_UCPD_IsEnabledWakeUp
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Wakeup mode is disabled.
  * @retval 1 Wakeup mode is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledWakeUp(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CFGR2, UCPD_CFGR2_WUPEN) == UCPD_CFGR2_WUPEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable ClkReq clock request forcing.
  * @rmtoll
  *  CFGR2          FORCECLK          LL_UCPD_EnableForceClock
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableForceClock(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CFGR2, UCPD_CFGR2_FORCECLK);
}

/**
  * @brief  Disable ClkReq clock request forcing.
  * @rmtoll
  *  CFGR2          FORCECLK          LL_UCPD_DisableForceClock
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableForceClock(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CFGR2, UCPD_CFGR2_FORCECLK);
}

/**
  * @brief  Check if ClkReq clock request forcing is enabled.
  * @rmtoll
  *  CFGR2          FORCECLK          LL_UCPD_IsEnabledForceClock
  * @param  p_ucpd UCPD Instance.
  * @retval 0 ClkReq clock request forcing is disabled.
  * @retval 1 ClkReq clock request forcing is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledForceClock(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CFGR2, UCPD_CFGR2_FORCECLK) == UCPD_CFGR2_FORCECLK) ? 1UL : 0UL);
}

/**
  * @brief  Set BMC decoder Rx pre-filter sampling method.
  * @rmtoll
  *  CFGR2          RXFILT2N3          LL_UCPD_SetRxPreFilterSampling
  * @param  p_ucpd UCPD Instance.
  * @param  rx_filt_samples This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_RX_PREFILTER_3SAMPLES
  *         @arg @ref LL_UCPD_RX_PREFILTER_2SAMPLES
  */
__STATIC_INLINE void LL_UCPD_SetRxPreFilterSampling(UCPD_TypeDef *p_ucpd, uint32_t rx_filt_samples)
{
  STM32_MODIFY_REG(p_ucpd->CFGR2, UCPD_CFGR2_RXFILT2N3, rx_filt_samples << UCPD_CFGR2_RXFILT2N3_Pos);
}

/**
  * @brief  Get BMC decoder Rx pre-filter sampling method.
  * @rmtoll
  *  CFGR2          RXFILT2N3          LL_UCPD_GetRxPreFilterSampling
  * @param  p_ucpd UCPD Instance.
  * @retval BMC decoder Rx pre-filter sampling method.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetRxPreFilterSampling(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR2, UCPD_CFGR2_RXFILT2N3) >> UCPD_CFGR2_RXFILT2N3_Pos);
}

/**
  * @brief  BMC decoder Rx pre-filter enable.
  * @rmtoll
  *  CFGR2          RXFILTDIS          LL_UCPD_EnableRxPreFilter
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableRxPreFilter(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CFGR2, UCPD_CFGR2_RXFILTDIS);
}

/**
  * @brief  BMC decoder Rx pre-filter disable.
  * @rmtoll
  *  CFGR2          RXFILTDIS          LL_UCPD_DisableRxPreFilter
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableRxPreFilter(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CFGR2, UCPD_CFGR2_RXFILTDIS);
}

/**
  * @brief  Check if BMC decoder Rx pre-filter is enabled.
  * @rmtoll
  *  CFGR2          RXFILTDIS          LL_UCPD_IsEnabledRxPreFilter
  * @param  p_ucpd UCPD Instance.
  * @retval 0 BMC decoder Rx pre-filter is disabled.
  * @retval 1 BMC decoder Rx pre-filter is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledRxPreFilter(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CFGR2, UCPD_CFGR2_RXFILTDIS) == UCPD_CFGR2_RXFILTDIS) ? 0UL : 1UL);
}

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_CFGR3 CFGR3 register
  * @{
  */

/**
  * @brief  Apply trimming of Rp resistor on the CC1 line.
  * @rmtoll
  *  CFGR3          TRIM_CC1_RP3A0          LL_UCPD_SetTrimCC1_Rp3A0
  * @param  p_ucpd UCPD Instance.
  * @param  trim_cc1_rp SW trim value for Rp resistor on the CC1 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE void LL_UCPD_SetTrimCC1_Rp3A0(UCPD_TypeDef *p_ucpd, uint32_t trim_cc1_rp)
{
  STM32_MODIFY_REG(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC1_RP3A0, trim_cc1_rp << UCPD_CFGR3_TRIM_CC1_RP3A0_Pos);
}

/**
  * @brief  Apply trimming of Rp1A5 resistor on the CC1 line.
  * @rmtoll
  *  CFGR3          TRIM_CC1_RP1A5          LL_UCPD_SetTrimCC1_Rp1A5
  * @param  p_ucpd UCPD Instance.
  * @param  trim_cc1_rp SW trim value for Rp resistor on the CC1 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE void LL_UCPD_SetTrimCC1_Rp1A5(UCPD_TypeDef *p_ucpd, uint32_t trim_cc1_rp)
{
  STM32_MODIFY_REG(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC1_RP1A5, trim_cc1_rp << UCPD_CFGR3_TRIM_CC1_RP1A5_Pos);
}
/**
  * @brief  Get trimming of Rp resistor on the CC1 line.
  * @rmtoll
  *  CFGR3          TRIM_CC1_RP3A0          LL_UCPD_GetTrimCC1_Rp3A0
  * @param  p_ucpd UCPD Instance.
  * @retval SW trim value for Rp resistor on the CC1 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTrimCC1_Rp3A0(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC1_RP3A0) >> UCPD_CFGR3_TRIM_CC1_RP3A0_Pos);
}

/**
  * @brief  Get trimming of Rp1A5 resistor on the CC1 line.
  * @rmtoll
  *  CFGR3          TRIM_CC1_RP1A5          LL_UCPD_GetTrimCC1_Rp1A5
  * @param  p_ucpd UCPD Instance.
  * @retval SW trim value for Rp1A5 resistor on the CC1 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTrimCC1_Rp1A5(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC1_RP1A5) >> UCPD_CFGR3_TRIM_CC1_RP1A5_Pos);
}

/**
  * @brief  Apply trimming of Rp resistor on the CC2 line.
  * @rmtoll
  *  CFGR3          TRIM_CC2_RP3A0          LL_UCPD_SetTrimCC2_Rp3A0
  * @param  p_ucpd UCPD Instance.
  * @param  trim_cc2_rp SW trim value for Rp resistor on the CC2 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE void LL_UCPD_SetTrimCC2_Rp3A0(UCPD_TypeDef *p_ucpd, uint32_t trim_cc2_rp)
{
  STM32_MODIFY_REG(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC2_RP3A0, trim_cc2_rp << UCPD_CFGR3_TRIM_CC2_RP3A0_Pos);
}

/**
  * @brief  Apply trimming of Rp1A5 resistor on the CC2 line.
  * @rmtoll
  *  CFGR3          TRIM_CC2_RP1A5          LL_UCPD_SetTrimCC2_Rp1A5
  * @param  p_ucpd UCPD Instance.
  * @param  trim_cc1_rp SW trim value for Rp resistor on the CC2 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE void LL_UCPD_SetTrimCC2_Rp1A5(UCPD_TypeDef *p_ucpd, uint32_t trim_cc2_rp)
{
  STM32_MODIFY_REG(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC2_RP1A5, trim_cc2_rp << UCPD_CFGR3_TRIM_CC2_RP1A5_Pos);
}

/**
  * @brief  Get trimming of Rp resistor on the CC2 line.
  * @rmtoll
  *  CFGR3          TRIM_CC2_RP3A0          LL_UCPD_GetTrimCC2_Rp3A0
  * @param  p_ucpd UCPD Instance.
  * @retval SW trim value for Rp resistor on the CC2 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTrimCC2_Rp3A0(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC2_RP3A0) >> UCPD_CFGR3_TRIM_CC2_RP3A0_Pos);
}

/**
  * @brief  Get trimming of Rp1A5 resistor on the CC2 line.
  * @rmtoll
  *  CFGR3          TRIM_CC2_RP1A5          LL_UCPD_GetTrimCC2_Rp1A5
  * @param  p_ucpd UCPD Instance.
  * @retval SW trim value for Rp1A5 resistor on the CC2 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTrimCC2_Rp1A5(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC2_RP1A5) >> UCPD_CFGR3_TRIM_CC2_RP1A5_Pos);
}

/**
  * @brief  Apply trimming of Rd resistor on the CC1 line.
  * @rmtoll
  *  CFGR3          TRIM_CC1_RD          LL_UCPD_SetTrimCC1_Rd
  * @param  p_ucpd UCPD Instance.
  * @param  trim_cc1_rd SW trim value for Rd resistor on the CC1 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE void LL_UCPD_SetTrimCC1_Rd(UCPD_TypeDef *p_ucpd, uint32_t trim_cc1_rd)
{
  STM32_MODIFY_REG(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC1_RD, trim_cc1_rd << UCPD_CFGR3_TRIM_CC1_RD_Pos);
}

/**
  * @brief  Get trimming of Rd resistor on the CC1 line.
  * @rmtoll
  *  CFGR3          TRIM_CC1_RD          LL_UCPD_GetTrimCC1_Rd
  * @param  p_ucpd UCPD Instance.
  * @retval SW trim value for Rd resistor on the CC1 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTrimCC1_Rd(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC1_RD) >> UCPD_CFGR3_TRIM_CC1_RD_Pos);
}

/**
  * @brief  Apply trimming of Rd resistor on the CC2 line.
  * @rmtoll
  *  CFGR3          TRIM_CC2_RD          LL_UCPD_SetTrimCC2_Rd
  * @param  p_ucpd UCPD Instance.
  * @param  trim_cc2_rd SW trim value for Rd resistor on the CC2 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE void LL_UCPD_SetTrimCC2_Rd(UCPD_TypeDef *p_ucpd, uint32_t trim_cc2_rd)
{
  STM32_MODIFY_REG(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC2_RD, trim_cc2_rd << UCPD_CFGR3_TRIM_CC2_RD_Pos);
}

/**
  * @brief  Get trimming of Rd resistor on the CC2 line.
  * @rmtoll
  *  CFGR3          TRIM_CC2_RD          LL_UCPD_GetTrimCC2_Rd
  * @param  p_ucpd UCPD Instance.
  * @retval SW trim value for Rd resistor on the CC2 line. Value between 0x0 and 0xF.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTrimCC2_Rd(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CFGR3, UCPD_CFGR3_TRIM_CC2_RD) >> UCPD_CFGR3_TRIM_CC2_RD_Pos);
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_CR CR register
  * @{
  */

/**
  * @brief  Type-C detector for CC2 enable.
  * @rmtoll
  *  CR          CC2TCDIS          LL_UCPD_EnableTypeCDetectionCC2
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableTypeCDetectionCC2(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CR, UCPD_CR_CC2TCDIS);
}

/**
  * @brief  Type-C detector for CC2 disable.
  * @rmtoll
  *  CR          CC2TCDIS          LL_UCPD_DisableTypeCDetectionCC2
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableTypeCDetectionCC2(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_CC2TCDIS);
}

/**
  * @brief  Check if Type-C detector for CC2 is enabled.
  * @rmtoll
  *  CR          CC2TCDIS          LL_UCPD_IsEnabledTypeCDetectionCC2
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Type-C detector for CC2 is disabled.
  * @retval 1 Type-C detector for CC2 is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledTypeCDetectionCC2(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CR, UCPD_CR_CC2TCDIS) == UCPD_CR_CC2TCDIS) ? 0UL : 1UL);
}

/**
  * @brief  Type-C detector for CC1 enable.
  * @rmtoll
  *  CR          CC1TCDIS          LL_UCPD_EnableTypeCDetectionCC1
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableTypeCDetectionCC1(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CR, UCPD_CR_CC1TCDIS);
}

/**
  * @brief  Type-C detector for CC1 disable.
  * @rmtoll
  *  CR          CC1TCDIS          LL_UCPD_DisableTypeCDetectionCC1
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableTypeCDetectionCC1(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_CC1TCDIS);
}

/**
  * @brief  Check if Type-C detector for CC1 is enabled.
  * @rmtoll
  *  CR          CC1TCDIS          LL_UCPD_IsEnabledTypeCDetectionCC1
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Type-C detector for CC1 is disabled.
  * @retval 1 Type-C detector for CC1 is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledTypeCDetectionCC1(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CR, UCPD_CR_CC1TCDIS) == UCPD_CR_CC1TCDIS) ? 0UL : 1UL);
}

/**
  * @brief  Source Vconn discharge enable.
  * @rmtoll
  *  CR          RDCH          LL_UCPD_EnableVconnDischarge
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableVconnDischarge(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_RDCH);
}

/**
  * @brief  Source Vconn discharge disable.
  * @rmtoll
  *  CR          RDCH          LL_UCPD_DisableVconnDischarge
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableVconnDischarge(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CR, UCPD_CR_RDCH);
}

/**
  * @brief  Check if source Vconn discharge is enabled.
  * @rmtoll
  *  CR          RDCH          LL_UCPD_IsEnabledVconnDischarge
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Source Vconn discharge is disabled.
  * @retval 1 Source Vconn discharge is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledVconnDischarge(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CR, UCPD_CR_RDCH) == UCPD_CR_RDCH) ? 1UL : 0UL);
}

/**
  * @brief  Signal Fast Role Swap request.
  * @rmtoll
  *  CR          FRSTX          LL_UCPD_SignalFRSTX
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_SignalFRSTX(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_FRSTX);
}

/**
  * @brief  Fast Role Swap RX detection enable.
  * @rmtoll
  *  CR          FRSRXEN          LL_UCPD_EnableFRSDetection
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableFRSDetection(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_FRSRXEN);
}

/**
  * @brief  Fast Role Swap RX detection disable.
  * @rmtoll
  *  CR          FRSRXEN          LL_UCPD_DisableFRSDetection
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableFRSDetection(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CR, UCPD_CR_FRSRXEN);
}

/**
  * @brief  Check if Fast Role Swap RX detection is enabled.
  * @rmtoll
  *  CR          FRSRXEN          LL_UCPD_IsEnabledFRSDetection
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Fast Role Swap RX detection is disabled.
  * @retval 1 Fast Role Swap RX detection is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledFRSDetection(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CR, UCPD_CR_FRSRXEN) == UCPD_CR_FRSRXEN) ? 1UL : 0UL);
}

/**
  * @brief  Set CC line enable.
  * @rmtoll
  *  CR          CCENABLE          LL_UCPD_SetCCEnable
  * @param  p_ucpd UCPD Instance.
  * @param  CCEnable This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_CCENABLE_NONE
  *         @arg @ref LL_UCPD_CCENABLE_CC1
  *         @arg @ref LL_UCPD_CCENABLE_CC2
  *         @arg @ref LL_UCPD_CCENABLE_CC1CC2
  */
__STATIC_INLINE void LL_UCPD_SetCCEnable(UCPD_TypeDef *p_ucpd, uint32_t CCEnable)
{
  STM32_MODIFY_REG(p_ucpd->CR, UCPD_CR_CCENABLE, CCEnable);
}

/**
  * @brief  Get CC line enable.
  * @rmtoll
  *  CR          CCENABLE          LL_UCPD_GetCCEnable
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_CCENABLE_NONE
  *         @arg @ref LL_UCPD_CCENABLE_CC1
  *         @arg @ref LL_UCPD_CCENABLE_CC2
  *         @arg @ref LL_UCPD_CCENABLE_CC1CC2
  */
__STATIC_INLINE uint32_t LL_UCPD_GetCCEnable(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->CR, UCPD_CR_CCENABLE));
}

/**
  * @brief  Set UCPD SNK/SRC role.
  * @rmtoll
  *  CR        ANAMODE          LL_UCPD_SetRole
  * @param  p_ucpd UCPD Instance.
  * @param  Role   This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_ROLE_SNK
  *         @arg @ref LL_UCPD_ROLE_SRC
  */
__STATIC_INLINE void LL_UCPD_SetRole(UCPD_TypeDef *p_ucpd, uint32_t Role)
{
  STM32_MODIFY_REG(p_ucpd->CR, UCPD_CR_ANAMODE, Role);
}

/**
  * @brief  Get UCPD Role.
  * @rmtoll
  *  CR          ANAMODE          LL_UCPD_GetRole
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_ROLE_SNK
  *         @arg @ref LL_UCPD_ROLE_SRC
  */
__STATIC_INLINE uint32_t LL_UCPD_GetRole(const UCPD_TypeDef *p_ucpd)
{
  return (uint32_t)(STM32_READ_BIT(p_ucpd->CR, UCPD_CR_ANAMODE));
}

/**
  * @brief  Set Rp resistor.
  * @rmtoll
  *  CR          ANASUBMODE          LL_UCPD_SetRpResistor
  * @param  p_ucpd UCPD Instance.
  * @param  Resistor This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_RESISTOR_DEFAULT
  *         @arg @ref LL_UCPD_RESISTOR_1_5A
  *         @arg @ref LL_UCPD_RESISTOR_3_0A
  *         @arg @ref LL_UCPD_RESISTOR_NONE
  */
__STATIC_INLINE void LL_UCPD_SetRpResistor(UCPD_TypeDef *p_ucpd, uint32_t Resistor)
{
  STM32_MODIFY_REG(p_ucpd->CR, UCPD_CR_ANASUBMODE,  Resistor);
}

/**
  * @brief  Get Rp resistor.
  * @rmtoll
  *  CR          ANASUBMODE          LL_UCPD_GetRpResistor
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_RESISTOR_DEFAULT
  *         @arg @ref LL_UCPD_RESISTOR_1_5A
  *         @arg @ref LL_UCPD_RESISTOR_3_0A
  *         @arg @ref LL_UCPD_RESISTOR_NONE
  */
__STATIC_INLINE uint32_t LL_UCPD_GetRpResistor(const UCPD_TypeDef *p_ucpd)
{
  return (uint32_t)(STM32_READ_BIT(p_ucpd->CR, UCPD_CR_ANASUBMODE));
}

/**
  * @brief  Set CC pin.
  * @rmtoll
  *  CR          PHYCCSEL          LL_UCPD_SetCCPin
  * @param  p_ucpd UCPD Instance.
  * @param  CCPin This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_CCPIN_CC1
  *         @arg @ref LL_UCPD_CCPIN_CC2
  */
__STATIC_INLINE void LL_UCPD_SetCCPin(UCPD_TypeDef *p_ucpd, uint32_t CCPin)
{
  STM32_MODIFY_REG(p_ucpd->CR, UCPD_CR_PHYCCSEL,  CCPin);
}

/**
  * @brief  Get CC pin.
  * @rmtoll
  *  CR          PHYCCSEL          LL_UCPD_GetCCPin
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_CCPIN_CC1
  *         @arg @ref LL_UCPD_CCPIN_CC2
  */
__STATIC_INLINE uint32_t LL_UCPD_GetCCPin(const UCPD_TypeDef *p_ucpd)
{
  return (uint32_t)(STM32_READ_BIT(p_ucpd->CR, UCPD_CR_PHYCCSEL));
}

/**
  * @brief  Rx enable.
  * @rmtoll
  *  CR          PHYRXEN          LL_UCPD_EnableRx
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableRx(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_PHYRXEN);
}

/**
  * @brief  Rx disable.
  * @rmtoll
  *  CR          PHYRXEN          LL_UCPD_DisableRx
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableRx(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CR, UCPD_CR_PHYRXEN);
}

/**
  * @brief  Check if Rx is enabled.
  * @rmtoll
  *  CR          PHYRXEN          LL_UCPD_IsEnabledIT_FRS
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx is disabled.
  * @retval 1 Rx is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledRx(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CR, UCPD_CR_PHYRXEN) == UCPD_CR_PHYRXEN) ? 1UL : 0UL);
}

/**
  * @brief  Set Rx mode.
  * @rmtoll
  *  CR          RXMODE          LL_UCPD_SetRxMode
  * @param  p_ucpd UCPD Instance.
  * @param  RxMode This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_RXMODE_NORMAL
  *         @arg @ref LL_UCPD_RXMODE_BIST_TEST_DATA
  */
__STATIC_INLINE void LL_UCPD_SetRxMode(UCPD_TypeDef *p_ucpd, uint32_t RxMode)
{
  STM32_MODIFY_REG(p_ucpd->CR, UCPD_CR_RXMODE, RxMode);
}

/**
  * @brief  Get Rx mode.
  * @rmtoll
  *  CR          RXMODE          LL_UCPD_GetRxMode
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_RXMODE_NORMAL
  *         @arg @ref LL_UCPD_RXMODE_BIST_TEST_DATA
  */
__STATIC_INLINE uint32_t LL_UCPD_GetRxMode(const UCPD_TypeDef *p_ucpd)
{
  return (uint32_t)(STM32_READ_BIT(p_ucpd->CR, UCPD_CR_RXMODE));
}

/**
  * @brief  Send Hard Reset.
  * @rmtoll
  *  CR          TXHRST          LL_UCPD_SendHardReset
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_SendHardReset(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_TXHRST);
}

/**
  * @brief  Send message.
  * @rmtoll
  *  CR          TXSEND          LL_UCPD_SendMessage
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_SendMessage(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CR, UCPD_CR_TXSEND);
}

/**
  * @brief  Set Tx mode.
  * @rmtoll
  *  CR          TXMODE          LL_UCPD_SetTxMode
  * @param  p_ucpd UCPD Instance.
  * @param  TxMode This parameter can be one of the following values:
  *         @arg @ref LL_UCPD_TXMODE_NORMAL
  *         @arg @ref LL_UCPD_TXMODE_CABLE_RESET
  *         @arg @ref LL_UCPD_TXMODE_BIST_CARRIER2
  */
__STATIC_INLINE void LL_UCPD_SetTxMode(UCPD_TypeDef *p_ucpd, uint32_t TxMode)
{
  STM32_MODIFY_REG(p_ucpd->CR, UCPD_CR_TXMODE, TxMode);
}

/**
  * @brief  Get Tx mode.
  * @rmtoll
  *  CR          TXMODE          LL_UCPD_GetTxMode
  * @param  p_ucpd UCPD Instance.
  * @return Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_TXMODE_NORMAL
  *         @arg @ref LL_UCPD_TXMODE_CABLE_RESET
  *         @arg @ref LL_UCPD_TXMODE_BIST_CARRIER2
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTxMode(const UCPD_TypeDef *p_ucpd)
{
  return (uint32_t)(STM32_READ_BIT(p_ucpd->CR, UCPD_CR_TXMODE));
}

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief  Enable FRS interrupt.
  * @rmtoll
  *  IMR          FRSEVTIE          LL_UCPD_EnableIT_FRS
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_FRS(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_FRSEVTIE);
}

/**
  * @brief  Enable Type-C event on CC2.
  * @rmtoll
  *  IMR          TYPECEVT2IE          LL_UCPD_EnableIT_TypeCEventCC2
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TypeCEventCC2(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_TYPECEVT2IE);
}

/**
  * @brief  Enable Type-C event on CC1.
  * @rmtoll
  *  IMR          TYPECEVT1IE          LL_UCPD_EnableIT_TypeCEventCC1
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TypeCEventCC1(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_TYPECEVT1IE);
}

/**
  * @brief  Enable Rx message end interrupt.
  * @rmtoll
  *  IMR          RXMSGENDIE          LL_UCPD_EnableIT_RxMsgEnd
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_RxMsgEnd(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_RXMSGENDIE);
}

/**
  * @brief  Enable Rx overrun interrupt.
  * @rmtoll
  *  IMR          RXOVRIE          LL_UCPD_EnableIT_RxOvr
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_RxOvr(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_RXOVRIE);
}

/**
  * @brief  Enable Rx hard reset interrupt.
  * @rmtoll
  *  IMR          RXHRSTDETIE          LL_UCPD_EnableIT_RxHRST
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_RxHRST(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_RXHRSTDETIE);
}

/**
  * @brief  Enable Rx ordered set interrupt.
  * @rmtoll
  *  IMR          RXORDDETIE          LL_UCPD_EnableIT_RxOrderSet
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_RxOrderSet(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_RXORDDETIE);
}

/**
  * @brief  Enable Rx non empty interrupt.
  * @rmtoll
  *  IMR          RXNEIE          LL_UCPD_EnableIT_RxNE
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_RxNE(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_RXNEIE);
}

/**
  * @brief  Enable interrupts.
  * @rmtoll IMR          RXMSGENDIE         LL_UCPD_EnableIT
  * @rmtoll IMR          RXOVRIE            LL_UCPD_EnableIT
  * @rmtoll IMR          RXHRSTDETIE        LL_UCPD_EnableIT
  * @rmtoll IMR          RXORDDETIE         LL_UCPD_EnableIT
  * @rmtoll IMR          RXNEIE             LL_UCPD_EnableIT
  * @rmtoll IMR          TXUNDIE            LL_UCPD_EnableIT
  * @rmtoll IMR          HRSTSENTIE         LL_UCPD_EnableIT
  * @rmtoll IMR          HRSTDISCIE         LL_UCPD_EnableIT
  * @rmtoll IMR          TXMSGABTIE         LL_UCPD_EnableIT
  * @rmtoll IMR          TXMSGSENTIE        LL_UCPD_EnableIT
  * @rmtoll IMR          TXMSGDISCIE        LL_UCPD_EnableIT
  * @rmtoll IMR          TYPECEVT1IE        LL_UCPD_EnableIT
  * @rmtoll IMR          TYPECEVT2IE        LL_UCPD_EnableIT
  * @rmtoll IMR          FRSEVTIE           LL_UCPD_EnableIT
  * @param  p_ucpd UCPD Instance.
  * @param  interrupts This parameter can be a combination of the following values:
  *         @arg @ref LL_UCPD_IMR_RXMSGEND
  *         @arg @ref LL_UCPD_IMR_RXOVR
  *         @arg @ref LL_UCPD_IMR_RXHRSTDET
  *         @arg @ref LL_UCPD_IMR_RXORDDET
  *         @arg @ref LL_UCPD_IMR_RXNE
  *         @arg @ref LL_UCPD_IMR_TXUND
  *         @arg @ref LL_UCPD_IMR_HRSTSENT
  *         @arg @ref LL_UCPD_IMR_HRSTDISC
  *         @arg @ref LL_UCPD_IMR_TXMSGABT
  *         @arg @ref LL_UCPD_IMR_TXMSGSENT
  *         @arg @ref LL_UCPD_IMR_TXMSGDISC
  *         @arg @ref LL_UCPD_IMR_TYPECEVT1
  *         @arg @ref LL_UCPD_IMR_TYPECEVT2
  *         @arg @ref LL_UCPD_IMR_FRSEVT
  */
__STATIC_INLINE void LL_UCPD_EnableIT(UCPD_TypeDef *p_ucpd, uint32_t interrupts)
{
  STM32_SET_BIT(p_ucpd->IMR, interrupts);
}

/**
  * @brief  Disable one or several interrupts.
  * @rmtoll IMR          RXMSGENDIE         LL_UCPD_DisableIT
  * @rmtoll IMR          RXOVRIE            LL_UCPD_DisableIT
  * @rmtoll IMR          RXHRSTDETIE        LL_UCPD_DisableIT
  * @rmtoll IMR          RXORDDETIE         LL_UCPD_DisableIT
  * @rmtoll IMR          RXNEIE             LL_UCPD_DisableIT
  * @rmtoll IMR          TXUNDIE            LL_UCPD_DisableIT
  * @rmtoll IMR          HRSTSENTIE         LL_UCPD_DisableIT
  * @rmtoll IMR          HRSTDISCIE         LL_UCPD_DisableIT
  * @rmtoll IMR          TXMSGABTIE         LL_UCPD_DisableIT
  * @rmtoll IMR          TXMSGSENTIE        LL_UCPD_DisableIT
  * @rmtoll IMR          TXMSGDISCIE        LL_UCPD_DisableIT
  * @rmtoll IMR          TYPECEVT1IE        LL_UCPD_DisableIT
  * @rmtoll IMR          TYPECEVT2IE        LL_UCPD_DisableIT
  * @rmtoll IMR          FRSEVTIE           LL_UCPD_DisableIT
  * @param  p_ucpd UCPD Instance.
  * @param  interrupts This parameter can be a combination of the following values:
  *         @arg @ref LL_UCPD_IMR_RXMSGEND
  *         @arg @ref LL_UCPD_IMR_RXOVR
  *         @arg @ref LL_UCPD_IMR_RXHRSTDET
  *         @arg @ref LL_UCPD_IMR_RXORDDET
  *         @arg @ref LL_UCPD_IMR_RXNE
  *         @arg @ref LL_UCPD_IMR_TXUND
  *         @arg @ref LL_UCPD_IMR_HRSTSENT
  *         @arg @ref LL_UCPD_IMR_HRSTDISC
  *         @arg @ref LL_UCPD_IMR_TXMSGABT
  *         @arg @ref LL_UCPD_IMR_TXMSGSENT
  *         @arg @ref LL_UCPD_IMR_TXMSGDISC
  *         @arg @ref LL_UCPD_IMR_TYPECEVT1
  *         @arg @ref LL_UCPD_IMR_TYPECEVT2
  *         @arg @ref LL_UCPD_IMR_FRSEVT
  */
__STATIC_INLINE void LL_UCPD_DisableIT(UCPD_TypeDef *p_ucpd, uint32_t interrupts)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, interrupts);
}

/**
  * @brief  Enable TX underrun interrupt.
  * @rmtoll
  *  IMR          TXUNDIE          LL_UCPD_EnableIT_TxUND
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TxUND(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_TXUNDIE);
}

/**
  * @brief  Enable hard reset sent interrupt.
  * @rmtoll
  *  IMR          HRSTSENTIE          LL_UCPD_EnableIT_TxHRSTSENT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TxHRSTSENT(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_HRSTSENTIE);
}

/**
  * @brief  Enable hard reset discard interrupt.
  * @rmtoll
  *  IMR          HRSTDISCIE          LL_UCPD_EnableIT_TxHRSTDISC
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TxHRSTDISC(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_HRSTDISCIE);
}

/**
  * @brief  Enable Tx message abort interrupt.
  * @rmtoll
  *  IMR          TXMSGABTIE          LL_UCPD_EnableIT_TxMSGABT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TxMSGABT(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGABTIE);
}

/**
  * @brief  Enable Tx message sent interrupt.
  * @rmtoll
  *  IMR          TXMSGSENTIE          LL_UCPD_EnableIT_TxMSGSENT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TxMSGSENT(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGSENTIE);
}

/**
  * @brief  Enable Tx message discarded interrupt.
  * @rmtoll
  *  IMR          TXMSGDISCIE          LL_UCPD_EnableIT_TxMSGDISC
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TxMSGDISC(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGDISCIE);
}

/**
  * @brief  Enable Tx data receive interrupt.
  * @rmtoll
  *  IMR          TXISIE          LL_UCPD_EnableIT_TxIS
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableIT_TxIS(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->IMR, UCPD_IMR_TXISIE);
}

/**
  * @brief  Disable FRS interrupt.
  * @rmtoll
  *  IMR          FRSEVTIE          LL_UCPD_DisableIT_FRS
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_FRS(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_FRSEVTIE);
}

/**
  * @brief  Disable Type-C event on CC2.
  * @rmtoll
  *  IMR          TYPECEVT2IE          LL_UCPD_DisableIT_TypeCEventCC2
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TypeCEventCC2(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_TYPECEVT2IE);
}

/**
  * @brief  Disable Type-C event on CC1.
  * @rmtoll
  *  IMR          TYPECEVT1IE          LL_UCPD_DisableIT_TypeCEventCC1
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TypeCEventCC1(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_TYPECEVT1IE);
}

/**
  * @brief  Disable Rx message end interrupt.
  * @rmtoll
  *  IMR          RXMSGENDIE          LL_UCPD_DisableIT_RxMsgEnd
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_RxMsgEnd(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_RXMSGENDIE);
}

/**
  * @brief  Disable Rx overrun interrupt.
  * @rmtoll
  *  IMR          RXOVRIE          LL_UCPD_DisableIT_RxOvr
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_RxOvr(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_RXOVRIE);
}

/**
  * @brief  Disable Rx hard reset interrupt.
  * @rmtoll
  *  IMR          RXHRSTDETIE          LL_UCPD_DisableIT_RxHRST
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_RxHRST(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_RXHRSTDETIE);
}

/**
  * @brief  Disable Rx ordered set interrupt.
  * @rmtoll
  *  IMR          RXORDDETIE          LL_UCPD_DisableIT_RxOrderSet
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_RxOrderSet(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_RXORDDETIE);
}

/**
  * @brief  Disable Rx non empty interrupt.
  * @rmtoll
  *  IMR          RXNEIE          LL_UCPD_DisableIT_RxNE
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_RxNE(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_RXNEIE);
}

/**
  * @brief  Disable TX underrun interrupt.
  * @rmtoll
  *  IMR          TXUNDIE          LL_UCPD_DisableIT_TxUND
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TxUND(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_TXUNDIE);
}

/**
  * @brief  Disable hard reset sent interrupt.
  * @rmtoll
  *  IMR          HRSTSENTIE          LL_UCPD_DisableIT_TxHRSTSENT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TxHRSTSENT(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_HRSTSENTIE);
}

/**
  * @brief  Disable hard reset discard interrupt.
  * @rmtoll
  *  IMR          HRSTDISCIE          LL_UCPD_DisableIT_TxHRSTDISC
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TxHRSTDISC(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_HRSTDISCIE);
}

/**
  * @brief  Disable Tx message abort interrupt.
  * @rmtoll
  *  IMR          TXMSGABTIE          LL_UCPD_DisableIT_TxMSGABT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TxMSGABT(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGABTIE);
}

/**
  * @brief  Disable Tx message sent interrupt.
  * @rmtoll
  *  IMR          TXMSGSENTIE          LL_UCPD_DisableIT_TxMSGSENT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TxMSGSENT(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGSENTIE);
}

/**
  * @brief  Disable Tx message discarded interrupt.
  * @rmtoll
  *  IMR          TXMSGDISCIE          LL_UCPD_DisableIT_TxMSGDISC
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TxMSGDISC(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGDISCIE);
}

/**
  * @brief  Disable Tx data receive interrupt.
  * @rmtoll
  *  IMR          TXISIE          LL_UCPD_DisableIT_TxIS
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableIT_TxIS(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->IMR, UCPD_IMR_TXISIE);
}

/**
  * @brief  Check if FRS interrupt is enabled.
  * @rmtoll
  *  IMR          FRSEVTIE          LL_UCPD_IsEnabledIT_FRS
  * @param  p_ucpd UCPD Instance.
  * @retval 0 FRS interrupt is disabled.
  * @retval 1 FRS interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_FRS(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_FRSEVTIE) == UCPD_IMR_FRSEVTIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Type-C event on CC2 is enabled.
  * @rmtoll
  *  IMR          TYPECEVT2IE          LL_UCPD_IsEnabledIT_TypeCEventCC2
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Type-C event on CC2 is disabled.
  * @retval 1 Type-C event on CC2 is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TypeCEventCC2(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_TYPECEVT2IE) == UCPD_IMR_TYPECEVT2IE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Type-C event on CC1 is enabled.
  * @rmtoll
  *  IMR2          TYPECEVT1IE          LL_UCPD_IsEnabledIT_TypeCEventCC1
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Type-C event on CC1 is disabled.
  * @retval 1 Type-C event on CC1 is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TypeCEventCC1(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_TYPECEVT1IE) == UCPD_IMR_TYPECEVT1IE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx message end interrupt is enabled.
  * @rmtoll
  *  IMR          RXMSGENDIE          LL_UCPD_IsEnabledIT_RxMsgEnd
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx message end interrupt is disabled.
  * @retval 1 Rx message end interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_RxMsgEnd(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_RXMSGENDIE) == UCPD_IMR_RXMSGENDIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx overrun interrupt is enabled.
  * @rmtoll
  *  IMR          RXOVRIE          LL_UCPD_IsEnabledIT_RxOvr
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx overrun interrupt is disabled.
  * @retval 1 Rx overrun interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_RxOvr(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_RXOVRIE) == UCPD_IMR_RXOVRIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx hard reset interrupt is enabled.
  * @rmtoll
  *  IMR          RXHRSTDETIE          LL_UCPD_IsEnabledIT_RxHRST
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx hard reset interrupt is disabled.
  * @retval 1 Rx hard reset interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_RxHRST(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_RXHRSTDETIE) == UCPD_IMR_RXHRSTDETIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx ordered set interrupt is enabled.
  * @rmtoll
  *  IMR          RXORDDETIE          LL_UCPD_IsEnabledIT_RxOrderSet
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx ordered set interrupt is disabled.
  * @retval 1 Rx ordered set interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_RxOrderSet(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_RXORDDETIE) == UCPD_IMR_RXORDDETIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx non empty interrupt is enabled.
  * @rmtoll
  *  IMR          RXNEIE          LL_UCPD_IsEnabledIT_RxNE
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx non empty interrupt is disabled.
  * @retval 1 Rx non empty interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_RxNE(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_RXNEIE) == UCPD_IMR_RXNEIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if TX underrun interrupt is enabled.
  * @rmtoll
  *  IMR          TXUNDIE          LL_UCPD_IsEnabledIT_TxUND
  * @param  p_ucpd UCPD Instance.
  * @retval 0 TX underrun interrupt is disabled.
  * @retval 1 TX underrun interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TxUND(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_TXUNDIE) == UCPD_IMR_TXUNDIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if hard reset sent interrupt is enabled.
  * @rmtoll
  *  IMR          HRSTSENTIE          LL_UCPD_IsEnabledIT_TxHRSTSENT
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Hard reset sent interrupt is disabled.
  * @retval 1 Hard reset sent interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TxHRSTSENT(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_HRSTSENTIE) == UCPD_IMR_HRSTSENTIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if hard reset discard interrupt is enabled.
  * @rmtoll
  *  IMR          HRSTDISCIE          LL_UCPD_IsEnabledIT_TxHRSTDISC
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Hard reset discard interrupt is disabled.
  * @retval 1 Hard reset discard interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TxHRSTDISC(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_HRSTDISCIE) == UCPD_IMR_HRSTDISCIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx message abort interrupt is enabled.
  * @rmtoll
  *  IMR          TXMSGABTIE          LL_UCPD_IsEnabledIT_TxMSGABT
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx message abort interrupt is enabled is disabled.
  * @retval 1 Tx message abort interrupt is enabled is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TxMSGABT(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGABTIE) == UCPD_IMR_TXMSGABTIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx message sent interrupt is enabled.
  * @rmtoll
  *  IMR          TXMSGSENTIE          LL_UCPD_IsEnabledIT_TxMSGSENT
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx message sent interrupt is disabled.
  * @retval 1 Tx message sent interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TxMSGSENT(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGSENTIE) == UCPD_IMR_TXMSGSENTIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx message discarded interrupt is enabled.
  * @rmtoll
  *  IMR          TXMSGDISCIE          LL_UCPD_IsEnabledIT_TxMSGDISC
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx message discarded interrupt is disabled.
  * @retval 1 Tx message discarded interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TxMSGDISC(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_TXMSGDISCIE) == UCPD_IMR_TXMSGDISCIE) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx data receive interrupt is enabled.
  * @rmtoll
  *  IMR          TXISIE          LL_UCPD_IsEnabledIT_TxIS
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx data receive interrupt is disabled.
  * @retval 1 Tx data receive interrupt is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledIT_TxIS(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->IMR, UCPD_IMR_TXISIE) == UCPD_IMR_TXISIE) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_IT_Clear Interrupt Clear
  * @{
  */

/**
  * @brief  Clear one or several interrupt flags.
  * @rmtoll ICR          RXMSGENDCF         LL_UCPD_ClearFlag
  * @rmtoll ICR          RXOVRCF            LL_UCPD_ClearFlag
  * @rmtoll ICR          RXHRSTDETCF        LL_UCPD_ClearFlag
  * @rmtoll ICR          RXORDDETCF         LL_UCPD_ClearFlag
  * @rmtoll ICR          TXUNDCF            LL_UCPD_ClearFlag
  * @rmtoll ICR          HRSTSENTCF         LL_UCPD_ClearFlag
  * @rmtoll ICR          HRSTDISCCF         LL_UCPD_ClearFlag
  * @rmtoll ICR          TXMSGABTCF         LL_UCPD_ClearFlag
  * @rmtoll ICR          TXMSGSENTCF        LL_UCPD_ClearFlag
  * @rmtoll ICR          TXMSGDISCCF        LL_UCPD_ClearFlag
  * @rmtoll ICR          TYPECEVT1CF        LL_UCPD_ClearFlag
  * @rmtoll ICR          TYPECEVT2CF        LL_UCPD_ClearFlag
  * @rmtoll ICR          FRSEVTCF           LL_UCPD_ClearFlag
  * @param  p_ucpd UCPD Instance.
  * @param  flags This parameter can be a combination of the following values:
  *         @arg @ref UCPD_ICR_RXMSGENDCF
  *         @arg @ref UCPD_ICR_RXOVRCF
  *         @arg @ref UCPD_ICR_RXHRSTDETCF
  *         @arg @ref UCPD_ICR_RXORDDETCF
  *         @arg @ref UCPD_ICR_TXUNDCF
  *         @arg @ref UCPD_ICR_HRSTSENTCF
  *         @arg @ref UCPD_ICR_HRSTDISCCF
  *         @arg @ref UCPD_ICR_TXMSGABTCF
  *         @arg @ref UCPD_ICR_TXMSGSENTCF
  *         @arg @ref UCPD_ICR_TXMSGDISCCF
  *         @arg @ref UCPD_ICR_TYPECEVT1CF
  *         @arg @ref UCPD_ICR_TYPECEVT2CF
  *         @arg @ref UCPD_ICR_FRSEVTCF
  */
__STATIC_INLINE void LL_UCPD_ClearFlag(UCPD_TypeDef *p_ucpd, uint32_t flags)
{
  STM32_SET_BIT(p_ucpd->ICR, flags);
}

/**
  * @brief  Clear FRS interrupt.
  * @rmtoll
  *  ICR          FRSEVTCF          LL_UCPD_ClearFlag_FRS
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_FRS(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_FRSEVTCF);
}

/**
  * @brief  Clear Type-C event on CC2.
  * @rmtoll
  *  ICR          TYPECEVT2CF          LL_UCPD_ClearFlag_TypeCEventCC2
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TypeCEventCC2(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_TYPECEVT2CF);
}

/**
  * @brief  Clear Type-C event on CC1.
  * @rmtoll
  *  ICR          TYPECEVT1CF          LL_UCPD_ClearFlag_TypeCEventCC1
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TypeCEventCC1(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_TYPECEVT1CF);
}

/**
  * @brief  Clear Rx message end interrupt.
  * @rmtoll
  *  ICR          RXMSGENDCF          LL_UCPD_ClearFlag_RxMsgEnd
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_RxMsgEnd(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_RXMSGENDCF);
}

/**
  * @brief  Clear Rx overrun interrupt.
  * @rmtoll
  *  ICR          RXOVRCF          LL_UCPD_ClearFlag_RxOvr
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_RxOvr(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_RXOVRCF);
}

/**
  * @brief  Clear Rx hard reset interrupt.
  * @rmtoll
  *  ICR          RXHRSTDETCF          LL_UCPD_ClearFlag_RxHRST
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_RxHRST(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_RXHRSTDETCF);
}

/**
  * @brief  Clear Rx ordered set interrupt.
  * @rmtoll
  *  ICR          RXORDDETCF          LL_UCPD_ClearFlag_RxOrderSet
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_RxOrderSet(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_RXORDDETCF);
}

/**
  * @brief  Clear TX underrun interrupt.
  * @rmtoll
  *  ICR          TXUNDCF          LL_UCPD_ClearFlag_TxUND
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TxUND(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_TXUNDCF);
}

/**
  * @brief  Clear hard reset sent interrupt.
  * @rmtoll
  *  ICR          HRSTSENTCF          LL_UCPD_ClearFlag_TxHRSTSENT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TxHRSTSENT(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_HRSTSENTCF);
}

/**
  * @brief  Clear hard reset discard interrupt.
  * @rmtoll
  *  ICR          HRSTDISCCF          LL_UCPD_ClearFlag_TxHRSTDISC
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TxHRSTDISC(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_HRSTDISCCF);
}

/**
  * @brief  Clear Tx message abort interrupt.
  * @rmtoll
  *  ICR          TXMSGABTCF          LL_UCPD_ClearFlag_TxMSGABT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TxMSGABT(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_TXMSGABTCF);
}

/**
  * @brief  Clear Tx message sent interrupt.
  * @rmtoll
  *  ICR          TXMSGSENTCF          LL_UCPD_ClearFlag_TxMSGSENT
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TxMSGSENT(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_TXMSGSENTCF);
}

/**
  * @brief  Clear Tx message discarded interrupt.
  * @rmtoll
  *  ICR          TXMSGDISCCF          LL_UCPD_ClearFlag_TxMSGDISC
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_ClearFlag_TxMSGDISC(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->ICR, UCPD_ICR_TXMSGDISCCF);
}

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Check if FRS interrupt is active.
  * @rmtoll
  *  SR          FRSEVT          LL_UCPD_IsActiveFlag_FRS
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_FRS(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_FRSEVT) == UCPD_SR_FRSEVT) ? 1UL : 0UL);
}

/**
  * @brief  Return the Vstate value for CC2.
  * @rmtoll
  *  SR          TYPEC_VSTATE_CC2          LL_UCPD_GetTypeCVstateCC2
  * @param  p_ucpd UCPD Instance.
  * @retval val.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTypeCVstateCC2(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TYPEC_VSTATE_CC2));
}

/**
  * @brief  Return the Vstate value for CC1.
  * @rmtoll
  *  SR          TYPEC_VSTATE_CC1          LL_UCPD_GetTypeCVstateCC1
  * @param  p_ucpd UCPD Instance.
  * @retval val.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTypeCVstateCC1(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TYPEC_VSTATE_CC1));
}

/**
  * @brief  Check if Type-C event on CC2 is active.
  * @rmtoll
  *  SR          TYPECEVT2          LL_UCPD_IsActiveFlag_TypeCEventCC2
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TypeCEventCC2(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TYPECEVT2) == UCPD_SR_TYPECEVT2) ? 1UL : 0UL);
}

/**
  * @brief  Check if Type-C event on CC1 is active.
  * @rmtoll
  *  SR          TYPECEVT1          LL_UCPD_IsActiveFlag_TypeCEventCC1
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TypeCEventCC1(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TYPECEVT1) == UCPD_SR_TYPECEVT1) ? 1UL : 0UL);
}

/**
  * @brief  Check if receive message error interrupt is active.
  * @rmtoll
  *  SR          RXERR          LL_UCPD_IsActiveFlag_RxErr
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_RxErr(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_RXERR) == UCPD_SR_RXERR) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx message end interrupt is active.
  * @rmtoll
  *  SR          RXMSGEND          LL_UCPD_IsActiveFlag_RxMsgEnd
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_RxMsgEnd(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_RXMSGEND) == UCPD_SR_RXMSGEND) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx overrun interrupt is active.
  * @rmtoll
  *  SR          RXOVR          LL_UCPD_IsActiveFlag_RxOvr
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_RxOvr(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_RXOVR) == UCPD_SR_RXOVR) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx hard reset interrupt is active.
  * @rmtoll
  *  SR          RXHRSTDET          LL_UCPD_IsActiveFlag_RxHRST
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_RxHRST(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_RXHRSTDET) == UCPD_SR_RXHRSTDET) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx ordered set interrupt is active.
  * @rmtoll
  *  SR          RXORDDET          LL_UCPD_IsActiveFlag_RxOrderSet
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx ordered set interrupt is not active.
  * @retval 1 Rx ordered set interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_RxOrderSet(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_RXORDDET) == UCPD_SR_RXORDDET) ? 1UL : 0UL);
}

/**
  * @brief  Check if Rx non empty interrupt is active.
  * @rmtoll
  *  SR          RXNE          LL_UCPD_IsActiveFlag_RxNE
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx non empty interrupt is not active.
  * @retval 1 Rx non empty interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_RxNE(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_RXNE) == UCPD_SR_RXNE) ? 1UL : 0UL);
}

/**
  * @brief  Check if TX underrun interrupt is active.
  * @rmtoll
  *  SR          TXUND          LL_UCPD_IsActiveFlag_TxUND
  * @param  p_ucpd UCPD Instance.
  * @retval 0 TX underrun interrupt is not active.
  * @retval 1 TX underrun interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TxUND(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TXUND) == UCPD_SR_TXUND) ? 1UL : 0UL);
}

/**
  * @brief  Check if hard reset sent interrupt is active.
  * @rmtoll
  *  SR          HRSTSENT          LL_UCPD_IsActiveFlag_TxHRSTSENT
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Hard reset sent interrupt is not active.
  * @retval 1 Hard reset sent interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TxHRSTSENT(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_HRSTSENT) == UCPD_SR_HRSTSENT) ? 1UL : 0UL);
}

/**
  * @brief  Check if hard reset discard interrupt is active.
  * @rmtoll
  *  SR          HRSTDISC          LL_UCPD_IsActiveFlag_TxHRSTDISC
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Hard reset discard interrupt is not active.
  * @retval 1 Hard reset discard interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TxHRSTDISC(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_HRSTDISC) == UCPD_SR_HRSTDISC) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx message abort interrupt is active.
  * @rmtoll
  *  SR          TXMSGABT          LL_UCPD_IsActiveFlag_TxMSGABT
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx message abort interrupt is not active.
  * @retval 1 Tx message abort interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TxMSGABT(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TXMSGABT) == UCPD_SR_TXMSGABT) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx message sent interrupt is active.
  * @rmtoll
  *  SR          TXMSGSENT          LL_UCPD_IsActiveFlag_TxMSGSENT
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx message sent interrupt is not active.
  * @retval 1 Tx message sent interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TxMSGSENT(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TXMSGSENT) == UCPD_SR_TXMSGSENT) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx message discarded interrupt is active.
  * @rmtoll
  *  SR          TXMSGDISC          LL_UCPD_IsActiveFlag_TxMSGDISC
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx message discarded interrupt is not active.
  * @retval 1 Tx message discarded interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TxMSGDISC(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TXMSGDISC) == UCPD_SR_TXMSGDISC) ? 1UL : 0UL);
}

/**
  * @brief  Check if Tx data receive interrupt is active.
  * @rmtoll
  *  SR          TXIS          LL_UCPD_IsActiveFlag_TxIS
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx data receive interrupt is not active.
  * @retval 1 Tx data receive interrupt is active.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsActiveFlag_TxIS(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->SR, UCPD_SR_TXIS) == UCPD_SR_TXIS) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_DMA_Management DMA Management
  * @{
  */

/**
  * @brief  Rx DMA Enable.
  * @rmtoll
  *  CFGR1          RXDMAEN          LL_UCPD_EnableRxDMA
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableRxDMA(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CFGR1, UCPD_CFGR1_RXDMAEN);
}

/**
  * @brief  Rx DMA Disable.
  * @rmtoll
  *  CFGR1          RXDMAEN          LL_UCPD_DisableRxDMA
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableRxDMA(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CFGR1, UCPD_CFGR1_RXDMAEN);
}

/**
  * @brief  Check if Rx DMA is enabled.
  * @rmtoll
  *  CFGR1          RXDMAEN          LL_UCPD_IsEnabledRxDMA
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Rx DMA is disabled.
  * @retval 1 Rx DMA is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledRxDMA(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_RXDMAEN) == (UCPD_CFGR1_RXDMAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Tx DMA Enable.
  * @rmtoll
  *  CFGR1          TXDMAEN          LL_UCPD_EnableTxDMA
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_EnableTxDMA(UCPD_TypeDef *p_ucpd)
{
  STM32_SET_BIT(p_ucpd->CFGR1, UCPD_CFGR1_TXDMAEN);
}

/**
  * @brief  Tx DMA Disable.
  * @rmtoll
  *  CFGR1          TXDMAEN          LL_UCPD_DisableTxDMA
  * @param  p_ucpd UCPD Instance.
  */
__STATIC_INLINE void LL_UCPD_DisableTxDMA(UCPD_TypeDef *p_ucpd)
{
  STM32_CLEAR_BIT(p_ucpd->CFGR1, UCPD_CFGR1_TXDMAEN);
}

/**
  * @brief  Check if Tx DMA is enabled.
  * @rmtoll
  *  CFGR1          TXDMAEN          LL_UCPD_IsEnabledTxDMA
  * @param  p_ucpd UCPD Instance.
  * @retval 0 Tx DMA is disabled.
  * @retval 1 Tx DMA is enabled.
  */
__STATIC_INLINE uint32_t LL_UCPD_IsEnabledTxDMA(const UCPD_TypeDef *p_ucpd)
{
  return ((STM32_READ_BIT(p_ucpd->CFGR1, UCPD_CFGR1_TXDMAEN) == (UCPD_CFGR1_TXDMAEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup UCPD_LL_EF_DATA_Management DATA Management
  * @{
  */

/**
  * @brief  Write the ordered set for Tx message.
  * @rmtoll
  *  TX_ORDSETR          TXORDSET          LL_UCPD_WriteTxOrderSet
  * @param  p_ucpd UCPD Instance.
  * @param  TxOrderSet one of the following values:
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP1
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP2
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_HARD_RESET
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_CABLE_RESET
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP1_DEBUG
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP2_DEBUG
  */
__STATIC_INLINE void LL_UCPD_WriteTxOrderSet(UCPD_TypeDef *p_ucpd, uint32_t TxOrderSet)
{
  STM32_WRITE_REG(p_ucpd->TX_ORDSETR, TxOrderSet);
}

/**
  * @brief  Read the configured ordered set for Tx message.
  * @rmtoll
  *  TX_ORDSETR          TXORDSET          LL_UCPD_ReadTxOrderSet
  * @param  p_ucpd UCPD Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP1
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP2
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_HARD_RESET
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_CABLE_RESET
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP1_DEBUG
  *         @arg @ref LL_UCPD_TX_ORDERED_SET_SOP2_DEBUG
  */
__STATIC_INLINE uint32_t LL_UCPD_ReadTxOrderSet(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->TX_ORDSETR, UCPD_TX_ORDSETR_TXORDSET));
}

/**
  * @brief  Write the Tx paysize.
  * @rmtoll
  *  TX_PAYSZR          TXPAYSZ          LL_UCPD_WriteTxPaySize
  * @param  p_ucpd UCPD Instance.
  * @param  TxPaySize Payload size yet to transmit. Value between 0x000 and 0x3FF.
  */
__STATIC_INLINE void LL_UCPD_WriteTxPaySize(UCPD_TypeDef *p_ucpd, uint32_t TxPaySize)
{
  STM32_WRITE_REG(p_ucpd->TX_PAYSZR, TxPaySize);
}

/**
  * @brief  Write data.
  * @rmtoll
  *  TXDR          TXDATA          LL_UCPD_WriteData
  * @param  p_ucpd UCPD Instance.
  * @param  Data Value between 0x00 and 0xFF.
  */
__STATIC_INLINE void LL_UCPD_WriteData(UCPD_TypeDef *p_ucpd, uint8_t Data)
{
  STM32_WRITE_REG(p_ucpd->TXDR, Data);
}

/**
  * @brief  Get Tx data register address.
  * @param  p_ucpd UCPD Instance.
  * @retval UCPD Tx data register address.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetTxDataAddress(const UCPD_TypeDef *p_ucpd)
{
  return (uint32_t)&p_ucpd->TXDR;
}

/**
  * @brief  Read RX the ordered set detected.
  * @rmtoll
  *  RX_ORDSETR          RXORDSET          LL_UCPD_ReadRxOrderSet
  * @param  p_ucpd UCPD Instance.
  * @retval RxOrderSet one of the following values:
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_SOP
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_SOP1
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_SOP2
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_SOP1_DEBUG
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_SOP2_DEBUG
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_CABLE_RESET
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT1
  *         @arg @ref LL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT2
  */
__STATIC_INLINE uint32_t LL_UCPD_ReadRxOrderSet(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->RX_ORDSETR, UCPD_RX_ORDSETR_RXORDSET));
}

/**
  * @brief  Read the Rx paysize.
  * @rmtoll
  *  RX_PAYSZR          RXPAYSZ          LL_UCPD_ReadRxPaySize
  * @param  p_ucpd UCPD Instance.
  * @retval RXPaysize Value between 0x000 and 0x3FF.
  */
__STATIC_INLINE uint32_t LL_UCPD_ReadRxPaySize(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_BIT(p_ucpd->RX_PAYSZR, UCPD_RX_PAYSZR_RXPAYSZ));
}

/**
  * @brief  Read data.
  * @rmtoll
  *  RXDR          RXDATA          LL_UCPD_ReadData
  * @param  p_ucpd UCPD Instance.
  * @retval RxData Value between 0x00 and 0xFF.
  */
__STATIC_INLINE uint32_t LL_UCPD_ReadData(const UCPD_TypeDef *p_ucpd)
{
  return (STM32_READ_REG(p_ucpd->RXDR));
}

/**
  * @brief  Get Rx data register address.
  * @param  p_ucpd UCPD Instance.
  * @retval UCPD Rx data register address.
  */
__STATIC_INLINE uint32_t LL_UCPD_GetRxDataAddress(const UCPD_TypeDef *p_ucpd)
{
  return (uint32_t)&p_ucpd->RXDR;
}

/**
  * @brief  Set Rx OrderSet Ext1.
  * @rmtoll
  *  RX_ORDEXTR1          RXSOPX1          LL_UCPD_SetRxOrdExt1
  * @param  p_ucpd UCPD Instance.
  * @param  SOPExt Value between 0x00000 and 0xFFFFF.
  */
__STATIC_INLINE void LL_UCPD_SetRxOrdExt1(UCPD_TypeDef *p_ucpd, uint32_t SOPExt)
{
  STM32_WRITE_REG(p_ucpd->RX_ORDEXTR1, SOPExt);
}

/**
  * @brief  Set Rx OrderSet Ext2.
  * @rmtoll
  *  RX_ORDEXTR2          RXSOPX2          LL_UCPD_SetRxOrdExt2
  * @param  p_ucpd UCPD Instance.
  * @param  SOPExt Value between 0x00000 and 0xFFFFF.
  */
__STATIC_INLINE void LL_UCPD_SetRxOrdExt2(UCPD_TypeDef *p_ucpd, uint32_t SOPExt)
{
  STM32_WRITE_REG(p_ucpd->RX_ORDEXTR2, SOPExt);
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

#endif /* UCPD1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32G5XX_LL_UCPD_H */
