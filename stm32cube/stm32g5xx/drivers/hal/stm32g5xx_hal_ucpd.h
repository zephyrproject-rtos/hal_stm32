/**
  ******************************************************************************
  * @file    stm32g5xx_hal_ucpd.h
  * @brief   Header file of UCPD HAL module.
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
#ifndef STM32G5XX_HAL_UCPD_H
#define STM32G5XX_HAL_UCPD_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_ucpd.h"
#include "stm32g5xx_ll_system.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (UCPD1)

/** @defgroup UCPD UCPD
  * @{
  */

/* Exported constants ---------------------------------------------------------*/
/** @defgroup UCPD_Exported_Constants HAL UCPD Constants
  * @{
  */

#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
/** @defgroup  UCPD_Error_Code UCPD Group Error Code reflecting the processes asynchronous errors
  * @{
  */

#define  HAL_UCPD_ERROR_NONE   (0UL)        /*!< No error          */
#define  HAL_UCPD_ERROR_RXERR  (1UL << 0U)  /*!< Error Rx          */
#define  HAL_UCPD_ERROR_RXOVR  (1UL << 1U)  /*!< Error Rx overrun  */
#define  HAL_UCPD_ERROR_TXUND  (1UL << 2U)  /*!< Error Tx underrun */
#define  HAL_UCPD_ERROR_DMA    (1UL << 3U)  /*!< DMA error         */

/**
  * @}
  */

#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

/** @defgroup UCPD_Group_RXORDEREDSET UCPD Group Rx Ordered set
  * @{
  */

#define HAL_UCPD_RX_ORDERED_SET_SOP        LL_UCPD_RX_ORDERED_SET_SOP        /*!< SOP ordered set detection enabled         */
#define HAL_UCPD_RX_ORDERED_SET_SOP1       LL_UCPD_RX_ORDERED_SET_SOP1       /*!< SOP' ordered set detection enabled        */
#define HAL_UCPD_RX_ORDERED_SET_SOP2       LL_UCPD_RX_ORDERED_SET_SOP2       /*!< SOP'' ordered set detection enabled       */
#define HAL_UCPD_RX_ORDERED_SET_HARD_RST   LL_UCPD_RX_ORDERED_SET_HARD_RST   /*!< Hard reset ordered set detection enabled  */
#define HAL_UCPD_RX_ORDERED_SET_CABLE_RST  LL_UCPD_RX_ORDERED_SET_CABLE_RST  /*!< Cable reset ordered set detection enabled */
#define HAL_UCPD_RX_ORDERED_SET_SOP1_DEBUG LL_UCPD_RX_ORDERED_SET_SOP1_DEBUG /*!< SOP' debug ordered set detection enabled  */
#define HAL_UCPD_RX_ORDERED_SET_SOP2_DEBUG LL_UCPD_RX_ORDERED_SET_SOP2_DEBUG /*!< SOP'' debug ordered set detection enabled */
#define HAL_UCPD_RX_ORDERED_SET_SOP_EXT1   LL_UCPD_RX_ORDERED_SET_SOP_EXT1   /*!< SOP ext#1 ordered set detection enabled   */
#define HAL_UCPD_RX_ORDERED_SET_SOP_EXT2   LL_UCPD_RX_ORDERED_SET_SOP_EXT2   /*!< SOP ext#2 ordered set detection enabled   */
#define HAL_UCPD_RX_ORDERED_SET_NONE       LL_UCPD_RX_ORDERED_SET_NONE       /*!< Ordered set detection disabled            */

/**
  * @}
  */

/** @defgroup UCPD_Group_RXMAXSIZE UCPD Group Rx max size
  * @{
  */

#define HAL_UCPD_RX_MAX_SIZE_CHUNKED   (30U)  /*!< Max size of possible chunked message reception   */
#define HAL_UCPD_RX_MAX_SIZE_UNCHUNKED (264U) /*!< Max size of possible unchunked message reception */

/**
  * @}
  */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup  UCPD_Exported_Types HAL UCPD Types
  * @{
  */

/**
  * @brief UCPD States
  */
typedef enum
{
  HAL_UCPD_STATE_RESET       = 0U,          /*!< UCPD is not yet initialized                         */
  HAL_UCPD_STATE_INIT        = (1U << 31U), /*!< UCPD is initialized but not yet configured          */
  HAL_UCPD_STATE_IDLE        = (1U << 30U), /*!< UCPD is initialized and a global config was applied */
  HAL_UCPD_STATE_ACTIVE      = (1U << 29U), /*!< UCPD is configured and enabled, ready for TX or Rx  */
  HAL_UCPD_STATE_RX          = (1U << 28U), /*!< UCPD is in Rx mode                                  */
  HAL_UCPD_STATE_TX          = (1U << 27U), /*!< UCPD is in Tx mode                                  */
  HAL_UCPD_STATE_ABORT       = (1U << 26U), /*!< UCPD is aborting                                    */
} hal_ucpd_state_t;

/**
  * @brief UCPD Prescaler for producing ucpd_clk from ucpd_ker_ck
  */
typedef enum
{
  HAL_UCPD_PSC_DIV1  = LL_UCPD_PSC_DIV1,  /*!< Divide kernel clock by 1  */
  HAL_UCPD_PSC_DIV2  = LL_UCPD_PSC_DIV2,  /*!< Divide kernel clock by 2  */
  HAL_UCPD_PSC_DIV4  = LL_UCPD_PSC_DIV4,  /*!< Divide kernel clock by 4  */
  HAL_UCPD_PSC_DIV8  = LL_UCPD_PSC_DIV8,  /*!< Divide kernel clock by 8  */
  HAL_UCPD_PSC_DIV16 = LL_UCPD_PSC_DIV16, /*!< Divide kernel clock by 16 */
} hal_ucpd_clk_prescaler_t;

/**
  * @brief UCPD Divider for producing half-bit clock hbit_clk from ucpd_clk
  */
typedef uint8_t hal_ucpd_half_bit_clk_divider_t;

#define HAL_UCPD_HBITCLK_DIV1  LL_UCPD_HBITCLK_DIV1   /*!< Divide ucpd_clk by 1 */
#define HAL_UCPD_HBITCLK_DIV2  LL_UCPD_HBITCLK_DIV2   /*!< Divide ucpd_clk by 2 */
#define HAL_UCPD_HBITCLK_DIV3  LL_UCPD_HBITCLK_DIV3   /*!< Divide ucpd_clk by 3 */
#define HAL_UCPD_HBITCLK_DIV4  LL_UCPD_HBITCLK_DIV4   /*!< Divide ucpd_clk by 4 */
#define HAL_UCPD_HBITCLK_DIV5  LL_UCPD_HBITCLK_DIV5   /*!< Divide ucpd_clk by 5 */
#define HAL_UCPD_HBITCLK_DIV6  LL_UCPD_HBITCLK_DIV6   /*!< Divide ucpd_clk by 6 */
#define HAL_UCPD_HBITCLK_DIV7  LL_UCPD_HBITCLK_DIV7   /*!< Divide ucpd_clk by 7 */
#define HAL_UCPD_HBITCLK_DIV8  LL_UCPD_HBITCLK_DIV8   /*!< Divide ucpd_clk by 8 */
#define HAL_UCPD_HBITCLK_DIV9  LL_UCPD_HBITCLK_DIV9   /*!< Divide ucpd_clk by 9 */
#define HAL_UCPD_HBITCLK_DIV10 LL_UCPD_HBITCLK_DIV10  /*!< Divide ucpd_clk by 10 */
#define HAL_UCPD_HBITCLK_DIV11 LL_UCPD_HBITCLK_DIV11  /*!< Divide ucpd_clk by 11 */
#define HAL_UCPD_HBITCLK_DIV12 LL_UCPD_HBITCLK_DIV12  /*!< Divide ucpd_clk by 12 */
#define HAL_UCPD_HBITCLK_DIV13 LL_UCPD_HBITCLK_DIV13  /*!< Divide ucpd_clk by 13 */
#define HAL_UCPD_HBITCLK_DIV14 LL_UCPD_HBITCLK_DIV14  /*!< Divide ucpd_clk by 14 */
#define HAL_UCPD_HBITCLK_DIV15 LL_UCPD_HBITCLK_DIV15  /*!< Divide ucpd_clk by 15 */
#define HAL_UCPD_HBITCLK_DIV16 LL_UCPD_HBITCLK_DIV16  /*!< Divide ucpd_clk by 16 */
#define HAL_UCPD_HBITCLK_DIV17 LL_UCPD_HBITCLK_DIV17  /*!< Divide ucpd_clk by 17 */
#define HAL_UCPD_HBITCLK_DIV18 LL_UCPD_HBITCLK_DIV18  /*!< Divide ucpd_clk by 18 */
#define HAL_UCPD_HBITCLK_DIV19 LL_UCPD_HBITCLK_DIV19  /*!< Divide ucpd_clk by 19 */
#define HAL_UCPD_HBITCLK_DIV20 LL_UCPD_HBITCLK_DIV20  /*!< Divide ucpd_clk by 20 */
#define HAL_UCPD_HBITCLK_DIV21 LL_UCPD_HBITCLK_DIV21  /*!< Divide ucpd_clk by 21 */
#define HAL_UCPD_HBITCLK_DIV22 LL_UCPD_HBITCLK_DIV22  /*!< Divide ucpd_clk by 22 */
#define HAL_UCPD_HBITCLK_DIV23 LL_UCPD_HBITCLK_DIV23  /*!< Divide ucpd_clk by 23 */
#define HAL_UCPD_HBITCLK_DIV24 LL_UCPD_HBITCLK_DIV24  /*!< Divide ucpd_clk by 24 */
#define HAL_UCPD_HBITCLK_DIV25 LL_UCPD_HBITCLK_DIV25  /*!< Divide ucpd_clk by 25 */
#define HAL_UCPD_HBITCLK_DIV26 LL_UCPD_HBITCLK_DIV26  /*!< Divide ucpd_clk by 26 */
#define HAL_UCPD_HBITCLK_DIV27 LL_UCPD_HBITCLK_DIV27  /*!< Divide ucpd_clk by 27 */
#define HAL_UCPD_HBITCLK_DIV28 LL_UCPD_HBITCLK_DIV28  /*!< Divide ucpd_clk by 28 */
#define HAL_UCPD_HBITCLK_DIV29 LL_UCPD_HBITCLK_DIV29  /*!< Divide ucpd_clk by 29 */
#define HAL_UCPD_HBITCLK_DIV30 LL_UCPD_HBITCLK_DIV30  /*!< Divide ucpd_clk by 30 */
#define HAL_UCPD_HBITCLK_DIV31 LL_UCPD_HBITCLK_DIV31  /*!< Divide ucpd_clk by 31 */
#define HAL_UCPD_HBITCLK_DIV32 LL_UCPD_HBITCLK_DIV32  /*!< Divide ucpd_clk by 32 */
#define HAL_UCPD_HBITCLK_DIV33 LL_UCPD_HBITCLK_DIV33  /*!< Divide ucpd_clk by 33 */
#define HAL_UCPD_HBITCLK_DIV34 LL_UCPD_HBITCLK_DIV34  /*!< Divide ucpd_clk by 34 */
#define HAL_UCPD_HBITCLK_DIV35 LL_UCPD_HBITCLK_DIV35  /*!< Divide ucpd_clk by 35 */
#define HAL_UCPD_HBITCLK_DIV36 LL_UCPD_HBITCLK_DIV36  /*!< Divide ucpd_clk by 36 */
#define HAL_UCPD_HBITCLK_DIV37 LL_UCPD_HBITCLK_DIV37  /*!< Divide ucpd_clk by 37 */
#define HAL_UCPD_HBITCLK_DIV38 LL_UCPD_HBITCLK_DIV38  /*!< Divide ucpd_clk by 38 */
#define HAL_UCPD_HBITCLK_DIV39 LL_UCPD_HBITCLK_DIV39  /*!< Divide ucpd_clk by 39 */
#define HAL_UCPD_HBITCLK_DIV40 LL_UCPD_HBITCLK_DIV40  /*!< Divide ucpd_clk by 40 */
#define HAL_UCPD_HBITCLK_DIV41 LL_UCPD_HBITCLK_DIV41  /*!< Divide ucpd_clk by 41 */
#define HAL_UCPD_HBITCLK_DIV42 LL_UCPD_HBITCLK_DIV42  /*!< Divide ucpd_clk by 42 */
#define HAL_UCPD_HBITCLK_DIV43 LL_UCPD_HBITCLK_DIV43  /*!< Divide ucpd_clk by 43 */
#define HAL_UCPD_HBITCLK_DIV44 LL_UCPD_HBITCLK_DIV44  /*!< Divide ucpd_clk by 44 */
#define HAL_UCPD_HBITCLK_DIV45 LL_UCPD_HBITCLK_DIV45  /*!< Divide ucpd_clk by 45 */
#define HAL_UCPD_HBITCLK_DIV46 LL_UCPD_HBITCLK_DIV46  /*!< Divide ucpd_clk by 46 */
#define HAL_UCPD_HBITCLK_DIV47 LL_UCPD_HBITCLK_DIV47  /*!< Divide ucpd_clk by 47 */
#define HAL_UCPD_HBITCLK_DIV48 LL_UCPD_HBITCLK_DIV48  /*!< Divide ucpd_clk by 48 */
#define HAL_UCPD_HBITCLK_DIV49 LL_UCPD_HBITCLK_DIV49  /*!< Divide ucpd_clk by 49 */
#define HAL_UCPD_HBITCLK_DIV50 LL_UCPD_HBITCLK_DIV50  /*!< Divide ucpd_clk by 50 */
#define HAL_UCPD_HBITCLK_DIV51 LL_UCPD_HBITCLK_DIV51  /*!< Divide ucpd_clk by 51 */
#define HAL_UCPD_HBITCLK_DIV52 LL_UCPD_HBITCLK_DIV52  /*!< Divide ucpd_clk by 52 */
#define HAL_UCPD_HBITCLK_DIV53 LL_UCPD_HBITCLK_DIV53  /*!< Divide ucpd_clk by 53 */
#define HAL_UCPD_HBITCLK_DIV54 LL_UCPD_HBITCLK_DIV54  /*!< Divide ucpd_clk by 54 */
#define HAL_UCPD_HBITCLK_DIV55 LL_UCPD_HBITCLK_DIV55  /*!< Divide ucpd_clk by 55 */
#define HAL_UCPD_HBITCLK_DIV56 LL_UCPD_HBITCLK_DIV56  /*!< Divide ucpd_clk by 56 */
#define HAL_UCPD_HBITCLK_DIV57 LL_UCPD_HBITCLK_DIV57  /*!< Divide ucpd_clk by 57 */
#define HAL_UCPD_HBITCLK_DIV58 LL_UCPD_HBITCLK_DIV58  /*!< Divide ucpd_clk by 58 */
#define HAL_UCPD_HBITCLK_DIV59 LL_UCPD_HBITCLK_DIV59  /*!< Divide ucpd_clk by 59 */
#define HAL_UCPD_HBITCLK_DIV60 LL_UCPD_HBITCLK_DIV60  /*!< Divide ucpd_clk by 60 */
#define HAL_UCPD_HBITCLK_DIV61 LL_UCPD_HBITCLK_DIV61  /*!< Divide ucpd_clk by 61 */
#define HAL_UCPD_HBITCLK_DIV62 LL_UCPD_HBITCLK_DIV62  /*!< Divide ucpd_clk by 62 */
#define HAL_UCPD_HBITCLK_DIV63 LL_UCPD_HBITCLK_DIV63  /*!< Divide ucpd_clk by 63 */
#define HAL_UCPD_HBITCLK_DIV64 LL_UCPD_HBITCLK_DIV64  /*!< Divide ucpd_clk by 64 */

/**
  * @brief UCPD Divider for producing transition window clock from hbit_clk
  */
typedef enum
{
  HAL_UCPD_TRANSWIN_DIVINVALID = LL_UCPD_TRANSWIN_DIVINVALID, /*!< Not supported         */
  HAL_UCPD_TRANSWIN_DIV2       = LL_UCPD_TRANSWIN_DIV2,       /*!< Divide hbit_clk by 2  */
  HAL_UCPD_TRANSWIN_DIV3       = LL_UCPD_TRANSWIN_DIV3,       /*!< Divide hbit_clk by 3  */
  HAL_UCPD_TRANSWIN_DIV4       = LL_UCPD_TRANSWIN_DIV4,       /*!< Divide hbit_clk by 4  */
  HAL_UCPD_TRANSWIN_DIV5       = LL_UCPD_TRANSWIN_DIV5,       /*!< Divide hbit_clk by 5  */
  HAL_UCPD_TRANSWIN_DIV6       = LL_UCPD_TRANSWIN_DIV6,       /*!< Divide hbit_clk by 6  */
  HAL_UCPD_TRANSWIN_DIV7       = LL_UCPD_TRANSWIN_DIV7,       /*!< Divide hbit_clk by 7  */
  HAL_UCPD_TRANSWIN_DIV8       = LL_UCPD_TRANSWIN_DIV8,       /*!< Divide hbit_clk by 8  */
  HAL_UCPD_TRANSWIN_DIV9       = LL_UCPD_TRANSWIN_DIV9,       /*!< Divide hbit_clk by 9  */
  HAL_UCPD_TRANSWIN_DIV10      = LL_UCPD_TRANSWIN_DIV10,      /*!< Divide hbit_clk by 10 */
  HAL_UCPD_TRANSWIN_DIV11      = LL_UCPD_TRANSWIN_DIV11,      /*!< Divide hbit_clk by 11 */
  HAL_UCPD_TRANSWIN_DIV12      = LL_UCPD_TRANSWIN_DIV12,      /*!< Divide hbit_clk by 12 */
  HAL_UCPD_TRANSWIN_DIV13      = LL_UCPD_TRANSWIN_DIV13,      /*!< Divide hbit_clk by 13 */
  HAL_UCPD_TRANSWIN_DIV14      = LL_UCPD_TRANSWIN_DIV14,      /*!< Divide hbit_clk by 14 */
  HAL_UCPD_TRANSWIN_DIV15      = LL_UCPD_TRANSWIN_DIV15,      /*!< Divide hbit_clk by 15 */
  HAL_UCPD_TRANSWIN_DIV16      = LL_UCPD_TRANSWIN_DIV16,      /*!< Divide hbit_clk by 16 */
  HAL_UCPD_TRANSWIN_DIV17      = LL_UCPD_TRANSWIN_DIV17,      /*!< Divide hbit_clk by 17 */
  HAL_UCPD_TRANSWIN_DIV18      = LL_UCPD_TRANSWIN_DIV18,      /*!< Divide hbit_clk by 18 */
  HAL_UCPD_TRANSWIN_DIV19      = LL_UCPD_TRANSWIN_DIV19,      /*!< Divide hbit_clk by 19 */
  HAL_UCPD_TRANSWIN_DIV20      = LL_UCPD_TRANSWIN_DIV20,      /*!< Divide hbit_clk by 20 */
  HAL_UCPD_TRANSWIN_DIV21      = LL_UCPD_TRANSWIN_DIV21,      /*!< Divide hbit_clk by 21 */
  HAL_UCPD_TRANSWIN_DIV22      = LL_UCPD_TRANSWIN_DIV22,      /*!< Divide hbit_clk by 22 */
  HAL_UCPD_TRANSWIN_DIV23      = LL_UCPD_TRANSWIN_DIV23,      /*!< Divide hbit_clk by 23 */
  HAL_UCPD_TRANSWIN_DIV24      = LL_UCPD_TRANSWIN_DIV24,      /*!< Divide hbit_clk by 24 */
  HAL_UCPD_TRANSWIN_DIV25      = LL_UCPD_TRANSWIN_DIV25,      /*!< Divide hbit_clk by 25 */
  HAL_UCPD_TRANSWIN_DIV26      = LL_UCPD_TRANSWIN_DIV26,      /*!< Divide hbit_clk by 26 */
  HAL_UCPD_TRANSWIN_DIV27      = LL_UCPD_TRANSWIN_DIV27,      /*!< Divide hbit_clk by 27 */
  HAL_UCPD_TRANSWIN_DIV28      = LL_UCPD_TRANSWIN_DIV28,      /*!< Divide hbit_clk by 28 */
  HAL_UCPD_TRANSWIN_DIV29      = LL_UCPD_TRANSWIN_DIV29,      /*!< Divide hbit_clk by 29 */
  HAL_UCPD_TRANSWIN_DIV30      = LL_UCPD_TRANSWIN_DIV30,      /*!< Divide hbit_clk by 30 */
  HAL_UCPD_TRANSWIN_DIV31      = LL_UCPD_TRANSWIN_DIV31,      /*!< Divide hbit_clk by 31 */
  HAL_UCPD_TRANSWIN_DIV32      = LL_UCPD_TRANSWIN_DIV32       /*!< Divide hbit_clk by 32 */
} hal_ucpd_transition_window_divider_t;

/**
  * @brief UCPD Divider for producing inter-frame gap timer clock from ucpd_clk
  */
typedef enum
{
  HAL_UCPD_IFRGAP_DIVINVALID = LL_UCPD_IFRGAP_DIVINVALID, /*!< Not supported         */
  HAL_UCPD_IFRGAP_DIV2       = LL_UCPD_IFRGAP_DIV2,       /*!< Divide ucpd_clk by 2  */
  HAL_UCPD_IFRGAP_DIV3       = LL_UCPD_IFRGAP_DIV3,       /*!< Divide ucpd_clk by 3  */
  HAL_UCPD_IFRGAP_DIV4       = LL_UCPD_IFRGAP_DIV4,       /*!< Divide ucpd_clk by 4  */
  HAL_UCPD_IFRGAP_DIV5       = LL_UCPD_IFRGAP_DIV5,       /*!< Divide ucpd_clk by 5  */
  HAL_UCPD_IFRGAP_DIV6       = LL_UCPD_IFRGAP_DIV6,       /*!< Divide ucpd_clk by 6  */
  HAL_UCPD_IFRGAP_DIV7       = LL_UCPD_IFRGAP_DIV7,       /*!< Divide ucpd_clk by 7  */
  HAL_UCPD_IFRGAP_DIV8       = LL_UCPD_IFRGAP_DIV8,       /*!< Divide ucpd_clk by 8  */
  HAL_UCPD_IFRGAP_DIV9       = LL_UCPD_IFRGAP_DIV9,       /*!< Divide ucpd_clk by 9  */
  HAL_UCPD_IFRGAP_DIV10      = LL_UCPD_IFRGAP_DIV10,      /*!< Divide ucpd_clk by 10 */
  HAL_UCPD_IFRGAP_DIV11      = LL_UCPD_IFRGAP_DIV11,      /*!< Divide ucpd_clk by 11 */
  HAL_UCPD_IFRGAP_DIV12      = LL_UCPD_IFRGAP_DIV12,      /*!< Divide ucpd_clk by 12 */
  HAL_UCPD_IFRGAP_DIV13      = LL_UCPD_IFRGAP_DIV13,      /*!< Divide ucpd_clk by 13 */
  HAL_UCPD_IFRGAP_DIV14      = LL_UCPD_IFRGAP_DIV14,      /*!< Divide ucpd_clk by 14 */
  HAL_UCPD_IFRGAP_DIV15      = LL_UCPD_IFRGAP_DIV15,      /*!< Divide ucpd_clk by 15 */
  HAL_UCPD_IFRGAP_DIV16      = LL_UCPD_IFRGAP_DIV16,      /*!< Divide ucpd_clk by 16 */
  HAL_UCPD_IFRGAP_DIV17      = LL_UCPD_IFRGAP_DIV17,      /*!< Divide ucpd_clk by 17 */
  HAL_UCPD_IFRGAP_DIV18      = LL_UCPD_IFRGAP_DIV18,      /*!< Divide ucpd_clk by 18 */
  HAL_UCPD_IFRGAP_DIV19      = LL_UCPD_IFRGAP_DIV19,      /*!< Divide ucpd_clk by 19 */
  HAL_UCPD_IFRGAP_DIV20      = LL_UCPD_IFRGAP_DIV20,      /*!< Divide ucpd_clk by 20 */
  HAL_UCPD_IFRGAP_DIV21      = LL_UCPD_IFRGAP_DIV21,      /*!< Divide ucpd_clk by 21 */
  HAL_UCPD_IFRGAP_DIV22      = LL_UCPD_IFRGAP_DIV22,      /*!< Divide ucpd_clk by 22 */
  HAL_UCPD_IFRGAP_DIV23      = LL_UCPD_IFRGAP_DIV23,      /*!< Divide ucpd_clk by 23 */
  HAL_UCPD_IFRGAP_DIV24      = LL_UCPD_IFRGAP_DIV24,      /*!< Divide ucpd_clk by 24 */
  HAL_UCPD_IFRGAP_DIV25      = LL_UCPD_IFRGAP_DIV25,      /*!< Divide ucpd_clk by 25 */
  HAL_UCPD_IFRGAP_DIV26      = LL_UCPD_IFRGAP_DIV26,      /*!< Divide ucpd_clk by 26 */
  HAL_UCPD_IFRGAP_DIV27      = LL_UCPD_IFRGAP_DIV27,      /*!< Divide ucpd_clk by 27 */
  HAL_UCPD_IFRGAP_DIV28      = LL_UCPD_IFRGAP_DIV28,      /*!< Divide ucpd_clk by 28 */
  HAL_UCPD_IFRGAP_DIV29      = LL_UCPD_IFRGAP_DIV29,      /*!< Divide ucpd_clk by 29 */
  HAL_UCPD_IFRGAP_DIV30      = LL_UCPD_IFRGAP_DIV30,      /*!< Divide ucpd_clk by 30 */
  HAL_UCPD_IFRGAP_DIV31      = LL_UCPD_IFRGAP_DIV31,      /*!< Divide ucpd_clk by 31 */
  HAL_UCPD_IFRGAP_DIV32      = LL_UCPD_IFRGAP_DIV32       /*!< Divide ucpd_clk by 32 */
} hal_ucpd_inter_frame_gap_divider_t;

/**
  * @brief UCPD Tx ordered set configuration
  */
typedef enum
{
  HAL_UCPD_TX_ORDERED_SET_SOP        = LL_UCPD_TX_ORDERED_SET_SOP,         /*!< SOP message type         */
  HAL_UCPD_TX_ORDERED_SET_SOP1       = LL_UCPD_TX_ORDERED_SET_SOP1,        /*!< SOP' message type        */
  HAL_UCPD_TX_ORDERED_SET_SOP2       = LL_UCPD_TX_ORDERED_SET_SOP2,        /*!< SOP'' message type       */
  HAL_UCPD_TX_ORDERED_SET_HARD_RST   = LL_UCPD_TX_ORDERED_SET_HARD_RESET,  /*!< Hard reset message type  */
  HAL_UCPD_TX_ORDERED_SET_CABLE_RST  = LL_UCPD_TX_ORDERED_SET_CABLE_RESET, /*!< Cable reset message type */
  HAL_UCPD_TX_ORDERED_SET_SOP1_DEBUG = LL_UCPD_TX_ORDERED_SET_SOP1_DEBUG,  /*!< SOP' message type        */
  HAL_UCPD_TX_ORDERED_SET_SOP2_DEBUG = LL_UCPD_TX_ORDERED_SET_SOP2_DEBUG,  /*!< SOP'' message type       */
} hal_ucpd_tx_ordered_set_t;

/**
  * @brief UCPD Rx ordered set detected
  */
typedef enum
{
  HAL_UCPD_RX_ORDERED_SET_DETECT_SOP         = LL_UCPD_RX_ORDERED_SET_DETECT_SOP,         /*!< SOP detected         */
  HAL_UCPD_RX_ORDERED_SET_DETECT_SOP1        = LL_UCPD_RX_ORDERED_SET_DETECT_SOP1,        /*!< SOP' detected        */
  HAL_UCPD_RX_ORDERED_SET_DETECT_SOP2        = LL_UCPD_RX_ORDERED_SET_DETECT_SOP2,        /*!< SOP'' detected       */
  HAL_UCPD_RX_ORDERED_SET_DETECT_SOP1_DEBUG  = LL_UCPD_RX_ORDERED_SET_DETECT_SOP1_DEBUG,  /*!< SOP' debug detected  */
  HAL_UCPD_RX_ORDERED_SET_DETECT_SOP2_DEBUG  = LL_UCPD_RX_ORDERED_SET_DETECT_SOP2_DEBUG,  /*!< SOP'' debug detected */
  HAL_UCPD_RX_ORDERED_SET_DETECT_CABLE_RESET = LL_UCPD_RX_ORDERED_SET_DETECT_CABLE_RESET, /*!< Cable reset detected */
  HAL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT1     = LL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT1,     /*!< SOP ext#1 detected   */
  HAL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT2     = LL_UCPD_RX_ORDERED_SET_DETECT_SOPEXT2,     /*!< SOP ext#2 detected   */
} hal_ucpd_detected_rx_ordered_set_t;

/**
  * @brief UCPD TX mode
  */
typedef enum
{
  HAL_UCPD_TX_MODE_NORMAL      = LL_UCPD_TXMODE_NORMAL,       /*!< Tx mode normal      */
  HAL_UCPD_TX_MODE_CABLE_RESET = LL_UCPD_TXMODE_CABLE_RESET,  /*!< Tx mode cable reset */
  HAL_UCPD_TX_MODE_BIST        = LL_UCPD_TXMODE_BIST_CARRIER2 /*!< Tx mode BIST        */
} hal_ucpd_tx_mode_t;

/**
  * @brief UCPD Rx mode
  */
typedef enum
{
  HAL_UCPD_RX_MODE_NORMAL = LL_UCPD_RXMODE_NORMAL,        /*!< Rx mode normal */
  HAL_UCPD_RX_MODE_BIST   = LL_UCPD_RXMODE_BIST_TEST_DATA /*!< Rx mode BIST   */
} hal_ucpd_rx_mode_t;

/**
  * @brief UCPD Analog PHY operating role
  */
typedef enum
{
  HAL_UCPD_ROLE_SOURCE = LL_UCPD_ROLE_SRC, /*!< Source role */
  HAL_UCPD_ROLE_SINK   = LL_UCPD_ROLE_SNK  /*!< Sink role   */
} hal_ucpd_role_t;

/**
  * @brief UCPD Rp resistor values
  */
typedef enum
{
  HAL_UCPD_RP_DEFAULT = LL_UCPD_RESISTOR_DEFAULT, /*!< Rp resistor default USB value */
  HAL_UCPD_RP_1_5A    = LL_UCPD_RESISTOR_1_5A,    /*!< Rp resistor 1.5A value        */
  HAL_UCPD_RP_3_0A    = LL_UCPD_RESISTOR_3_0A,    /*!< Rp resistor 3.0A value        */
  HAL_UCPD_RP_NONE    = LL_UCPD_RESISTOR_NONE     /*!< no Rp resistor                */
} hal_ucpd_rp_value_t;

/**
  * @brief UCPD CC line enable
  */
typedef enum
{
  HAL_UCPD_CC_ENABLE_NONE   = LL_UCPD_CCENABLE_NONE,  /*!< Both CC1 and CC2 PHYs disabled */
  HAL_UCPD_CC_ENABLE_CC1    = LL_UCPD_CCENABLE_CC1,   /*!< CC1 PHY enabled                */
  HAL_UCPD_CC_ENABLE_CC2    = LL_UCPD_CCENABLE_CC2,   /*!< CC2 PHY enabled                */
  HAL_UCPD_CC_ENABLE_CC1CC2 = LL_UCPD_CCENABLE_CC1CC2 /*!< Both CC1 and CC2 PHYs enabled  */
} hal_ucpd_cc_enable_t;

/**
  * @brief UCPD BMC decoder Rx pre-filter sampling method
  */
typedef enum
{
  HAL_UCPD_RX_PREFILTER_3SAMPLES = LL_UCPD_RX_PREFILTER_3SAMPLES, /*!< 3 samples method for BMC decoder Rx pre-filter */
  HAL_UCPD_RX_PREFILTER_2SAMPLES = LL_UCPD_RX_PREFILTER_2SAMPLES  /*!< 2 samples method for BMC decoder Rx pre-filter */
} hal_ucpd_rx_prefilter_samples_t;

/**
  * @brief UCPD Global configuration
  */
typedef struct
{
  hal_ucpd_clk_prescaler_t             clk_psc;        /*!< Pre-scaler for generating ucpd_clk                       */
  hal_ucpd_half_bit_clk_divider_t      hbitclk_div;    /*!< Division ratio for producing half-bit clock              */
  hal_ucpd_transition_window_divider_t transwin_div;   /*!< Division ratio for producing transition window clock     */
  hal_ucpd_inter_frame_gap_divider_t   ifrgap_div;     /*!< Division ratio for producing inter-frame gap timer clock */
  uint32_t                             rx_ordered_set; /*!< Receiver accepted ordered set types. This variable is a
                                                            bitfield of type @ref UCPD_Group_RXORDEREDSET            */
} hal_ucpd_config_t;

/**
  * @brief UCPD Rp resistor values for trimming
  */
typedef enum
{
  HAL_UCPD_TRIM_RP_1_5A    = LL_UCPD_RESISTOR_1_5A,    /*!< Rp resistor 1.5A value for trimming */
  HAL_UCPD_TRIM_RP_3_0A    = LL_UCPD_RESISTOR_3_0A,    /*!< Rp resistor 3.0A value for trimming */
} hal_ucpd_trim_rp_value_t;


/**
  * @brief UCPD Rx PHY status
  */
typedef enum
{
  HAL_UCPD_RX_PHY_DISABLED = 0U, /*!< Rx PHY disabled */
  HAL_UCPD_RX_PHY_ENABLED  = 1U  /*!< Rx PHY enabled  */
} hal_ucpd_rx_phy_status_t;

/**
  * @brief UCPD Type-C detector status
  */
typedef enum
{
  HAL_UCPD_TYPE_C_DETECTOR_DISABLED = 0U, /*!< Type-C detector disabled */
  HAL_UCPD_TYPE_C_DETECTOR_ENABLED  = 1U  /*!< Type-C detector enabled  */
} hal_ucpd_type_c_detector_status_t;

/**
  * @brief UCPD Vconn discharge status
  */
typedef enum
{
  HAL_UCPD_VCONN_DISCHARGE_DISABLED = 0U, /*!< Vconn discharge disabled */
  HAL_UCPD_VCONN_DISCHARGE_ENABLED  = 1U  /*!< Vconn discharge enabled  */
} hal_ucpd_vconn_discharge_status_t;

/**
  * @brief UCPD Rx analog filter status
  */
typedef enum
{
  HAL_UCPD_RX_ANALOG_FILTER_DISABLED = 0U, /*!< Rx analog filter disabled */
  HAL_UCPD_RX_ANALOG_FILTER_ENABLED  = 1U  /*!< Rx analog filter enabled  */
} hal_ucpd_rx_analog_filter_status_t;

/**
  * @brief UCPD Wake-up from stop mode status
  */
typedef enum
{
  HAL_UCPD_WAKEUP_MODE_DISABLED = 0U, /*!< Wake-up from Stop mode disabled */
  HAL_UCPD_WAKEUP_MODE_ENABLED  = 1U  /*!< Wake-up from Stop mode enabled  */
} hal_ucpd_wakeup_mode_status_t;

/**
  * @brief UCPD ClkReq clock request forcing status
  */
typedef enum
{
  HAL_UCPD_FORCE_CLOCK_DISABLED = 0U, /*!< ClkReq clock request forcing disabled */
  HAL_UCPD_FORCE_CLOCK_ENABLED  = 1U  /*!< ClkReq clock request forcing enabled  */
} hal_ucpd_force_clk_status_t;

/**
  * @brief UCPD Rx pre-filter status
  */
typedef enum
{
  HAL_UCPD_RX_PREFILTER_DISABLED = 0U, /*!< Rx pre-filter disabled */
  HAL_UCPD_RX_PREFILTER_ENABLED  = 1U  /*!< Rx pre-filter enabled  */
} hal_ucpd_rx_prefilter_status_t;

/**
  * @brief UCPD CC lines
  */
typedef enum
{
  HAL_UCPD_LINE_CC1    = LL_UCPD_CCPIN_CC1,                       /*!< CC1 line */
  HAL_UCPD_LINE_CC2    = LL_UCPD_CCPIN_CC2,                       /*!< CC2 line */
  HAL_UCPD_LINE_CC1CC2 = (LL_UCPD_CCPIN_CC1 | LL_UCPD_CCPIN_CC2)  /*!< CC1 and CC2 lines */
} hal_ucpd_cc_line_t;

/**
  * @brief UCPD Fast Role Swap Rx status
  */
typedef enum
{
  HAL_UCPD_FRS_RX_DISABLED = 0U, /*!< Fast Role Swap Rx disabled */
  HAL_UCPD_FRS_RX_ENABLED  = 1U  /*!< Fast Role Swap Rx enabled  */
} hal_ucpd_frs_rx_status_t;


/**
  * @brief UCPD Hard reset reception status
  */
typedef enum
{
  HAL_UCPD_HARD_RESET_RX_DISABLED = 0U, /*!< Hard reset reception disabled */
  HAL_UCPD_HARD_RESET_RX_ENABLED  = 1U  /*!< Hard reset reception enabled  */
} hal_ucpd_hard_reset_rx_status_t;

/**
  * @brief UCPD Voltage state on CCx line in sink or source mode.
  */
typedef enum
{
  HAL_UCPD_VSTATE_SRC_VRA      = 0U, /*!< CCx voltage corresponds to an Ra state when current mode is source         */
  HAL_UCPD_VSTATE_SRC_VRD      = 1U, /*!< CCx voltage corresponds to an Rd state when current mode is source         */
  HAL_UCPD_VSTATE_SRC_VOPEN    = 2U, /*!< CCx voltage corresponds to an open state when current mode is source       */
  HAL_UCPD_VSTATE_SRC_INVALID  = 3U, /*!< CCx voltage corresponds to an invalid state when current mode is source    */
  HAL_UCPD_VSTATE_SNK_VRA      = 4U, /*!< CCx voltage corresponds to an Ra state when current mode is sink           */
  HAL_UCPD_VSTATE_SNK_VRPDFLT  = 5U, /*!< CCx voltage corresponds to an Rp default state when current mode is sink   */
  HAL_UCPD_VSTATE_SNK_VRP15A   = 6U, /*!< CCx voltage corresponds to an Rp 1.5A state when current mode is sink      */
  HAL_UCPD_VSTATE_SNK_VRP30A   = 7U  /*!< CCx voltage corresponds to an Rp 3.0A state when current mode is sink      */
} hal_ucpd_vstate_t;

/**
  * @brief HAL UCPD instance
  */
typedef enum
{
  HAL_UCPD1 = UCPD1_BASE, /*!< Peripheral instance UCPD1 */
} hal_ucpd_t;

typedef struct hal_ucpd_handle_s hal_ucpd_handle_t; /*!< UCPD handle type definition */

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
/**
  * @brief Pointer to a UCPD callback functions
  */
typedef  void (*hal_ucpd_cb_t)(hal_ucpd_handle_t *hucpd);

/**
  * @brief Pointer to a UCPD CC event callback functions
  */
typedef  void (*hal_ucpd_cc_event_cb_t)(hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */

/**
  * @brief UCPD Handle Structure Definition
  */
struct hal_ucpd_handle_s
{
  hal_ucpd_t                instance;              /*!< Peripheral instance       */
  volatile hal_ucpd_state_t global_state;          /*!< Peripheral state          */
  volatile hal_ucpd_state_t previous_state;        /*!< Peripheral previous state */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  uint8_t                   *p_buf_rx;             /*!< Rx transfer buffer        */
  const uint8_t             *p_buf_tx;             /*!< Tx transfer buffer        */

  uint16_t                  buff_goodcrc;          /*!< GoodCRC buffer (2 bytes)  */

  hal_dma_handle_t          *hdma_tx;            /*!< Tx DMA handle             */
  hal_dma_handle_t          *hdma_rx;            /*!< Rx DMA handle             */
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

#if defined (USE_HAL_UCPD_USER_DATA) && (USE_HAL_UCPD_USER_DATA == 1)
  const void                *p_user_data;          /*!< User Data Pointer         */
#endif /* USE_HAL_UCPD_USER_DATA */

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hal_ucpd_cb_t             p_tx_cplt_cb;          /*!< Tx message sent callback               */
  hal_ucpd_cb_t             p_tx_goodcrc_cplt_cb;  /*!< Tx GoodCRC message sent callback       */
  hal_ucpd_cb_t             p_tx_discard_cb;       /*!< Tx message discarded callback          */
  hal_ucpd_cb_t             p_tx_abort_cb;         /*!< Tx message aborted callback            */
  hal_ucpd_cb_t             p_rx_cplt_cb;          /*!< Rx complete callback                   */
  hal_ucpd_cb_t             p_rx_ord_set_cb;       /*!< Rx ordered set detected callback       */
  hal_ucpd_cb_t             p_hrst_sent_cb;        /*!< Hard reset sent callback               */
  hal_ucpd_cb_t             p_hrst_rx_cb;          /*!< Hard reset received callback           */
  hal_ucpd_cb_t             p_hrst_discard_cb;     /*!< Hard reset discarded callback          */
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hal_ucpd_cc_event_cb_t    p_type_c_event_ccx_cb; /*!< Type-C event on CCx callback           */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hal_ucpd_cb_t             p_frs_evt_cb;          /*!< Fast Role Swap event detected callback */
  hal_ucpd_cb_t             p_abort_cplt_cb;       /*!< Abort complete callback                */
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hal_ucpd_cb_t             p_error_cb;            /*!< Error callback                         */
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */

#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
  volatile uint32_t         last_error_codes;      /*!< Last error codes. This variable is a
                                                        bitfield of type @ref UCPD_Error_Code  */
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  hal_os_semaphore_t        semaphore;             /*!< OS semaphore              */
#endif /* USE_HAL_MUTEX */
};

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup UCPD_Exported_Functions HAL UCPD Functions
  * @{
  */

/** @defgroup UCPD_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

hal_status_t HAL_UCPD_Init(hal_ucpd_handle_t *hucpd, hal_ucpd_t instance);
void HAL_UCPD_DeInit(hal_ucpd_handle_t *hucpd);

/**
  * @}
  */

/** @defgroup UCPD_Exported_Functions_Group2 Configuration functions
  * @{
  */

/* Global configuration */
hal_status_t HAL_UCPD_SetConfig(hal_ucpd_handle_t *hucpd, const hal_ucpd_config_t *p_config);
void HAL_UCPD_GetConfig(const hal_ucpd_handle_t *hucpd, hal_ucpd_config_t *p_config);

/* Rx Ordered Sets */
hal_status_t HAL_UCPD_SetRxOrderedSet(const hal_ucpd_handle_t *hucpd, uint32_t rx_ordered_set);
uint32_t HAL_UCPD_GetRxOrderedSet(hal_ucpd_handle_t *hucpd);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/* Rx DMA */
hal_status_t HAL_UCPD_SetRxDMA(hal_ucpd_handle_t *hucpd, hal_dma_handle_t *hdma_rx);

/* Tx DMA */
hal_status_t HAL_UCPD_SetTxDMA(hal_ucpd_handle_t *hucpd, hal_dma_handle_t *hdma_tx);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/* Rx analog filter */
hal_status_t HAL_UCPD_EnableRxAnalogFilter(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableRxAnalogFilter(hal_ucpd_handle_t *hucpd);
hal_ucpd_rx_analog_filter_status_t HAL_UCPD_IsEnabledRxAnalogFilter(hal_ucpd_handle_t *hucpd);

/* Wakeup */
hal_status_t HAL_UCPD_EnableWakeupMode(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableWakeupMode(hal_ucpd_handle_t *hucpd);
hal_ucpd_wakeup_mode_status_t HAL_UCPD_IsEnabledWakeupMode(hal_ucpd_handle_t *hucpd);

/* ClkReq clock request forcing */
hal_status_t HAL_UCPD_EnableForceClock(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableForceClock(hal_ucpd_handle_t *hucpd);
hal_ucpd_force_clk_status_t HAL_UCPD_IsEnabledForceClock(hal_ucpd_handle_t *hucpd);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/* BMC decoder Rx pre-filter sampling method */
hal_status_t HAL_UCPD_SetRxPreFilterSampling(hal_ucpd_handle_t *hucpd,
                                             hal_ucpd_rx_prefilter_samples_t rx_prefilter_samples);
hal_ucpd_rx_prefilter_samples_t HAL_UCPD_GetRxPreFilterSampling(hal_ucpd_handle_t *hucpd);

/* BMC decoder Rx pre-filter */
hal_status_t HAL_UCPD_EnableRxPreFilter(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableRxPreFilter(hal_ucpd_handle_t *hucpd);
hal_ucpd_rx_prefilter_status_t HAL_UCPD_IsEnabledRxPreFilter(hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/* Software trimming of Rp and Rd resistors */
hal_status_t HAL_UCPD_ApplyTrimmingRp(hal_ucpd_handle_t *hucpd, hal_ucpd_trim_rp_value_t trim_rp_value);
hal_status_t HAL_UCPD_ApplyTrimmingRd(hal_ucpd_handle_t *hucpd);

/* Start/Stop */
hal_status_t HAL_UCPD_Start(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_Stop(hal_ucpd_handle_t *hucpd);
/**
  * @}
  */

/** @defgroup UCPD_Exported_Functions_Group3 Control functions
  * @{
  */

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/* Rx PHY */
hal_status_t HAL_UCPD_EnableRx(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableRx(hal_ucpd_handle_t *hucpd);
hal_ucpd_rx_phy_status_t HAL_UCPD_IsEnabledRx(hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/* Type-C detector */
hal_status_t HAL_UCPD_EnableTypeCDetectorCCx(const hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line);
hal_status_t HAL_UCPD_DisableTypeCDetectorCCx(const hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line);
hal_ucpd_type_c_detector_status_t HAL_UCPD_IsEnabledTypeCDetectorCCx(const hal_ucpd_handle_t *hucpd,
                                                                     hal_ucpd_cc_line_t cc_line);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/* Vconn discharge */
hal_status_t HAL_UCPD_EnableVconnDischarge(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableVconnDischarge(hal_ucpd_handle_t *hucpd);
hal_ucpd_vconn_discharge_status_t HAL_UCPD_IsEnabledVconnDischarge(hal_ucpd_handle_t *hucpd);

/* Tx ordered set */
hal_status_t HAL_UCPD_SetTxOrderedSet(hal_ucpd_handle_t *hucpd, hal_ucpd_tx_ordered_set_t tx_ordered_set);
hal_ucpd_tx_ordered_set_t HAL_UCPD_GetTxOrderedSet(hal_ucpd_handle_t *hucpd);

/* Tx mode */
hal_status_t HAL_UCPD_SetTxMode(hal_ucpd_handle_t *hucpd, hal_ucpd_tx_mode_t tx_mode);
hal_ucpd_tx_mode_t HAL_UCPD_GetTxMode(hal_ucpd_handle_t *hucpd);

/* Rx mode */
hal_status_t HAL_UCPD_SetRxMode(hal_ucpd_handle_t *hucpd, hal_ucpd_rx_mode_t rx_mode);
hal_ucpd_rx_mode_t HAL_UCPD_GetRxMode(hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/* PHY operating role */
hal_status_t HAL_UCPD_SetRole(hal_ucpd_handle_t *hucpd, hal_ucpd_role_t role);
hal_ucpd_role_t HAL_UCPD_GetRole(hal_ucpd_handle_t *hucpd);

/* Pull-ups (Rp) resistors */
hal_status_t HAL_UCPD_SetRp(hal_ucpd_handle_t *hucpd, hal_ucpd_rp_value_t rp_value);
hal_ucpd_rp_value_t HAL_UCPD_GetRp(hal_ucpd_handle_t *hucpd);

/* CC line enabling */
hal_status_t HAL_UCPD_SetCCLines(hal_ucpd_handle_t *hucpd, const hal_ucpd_cc_enable_t cc_enable);
hal_ucpd_cc_enable_t HAL_UCPD_GetCCLines(const hal_ucpd_handle_t *hucpd);

/* Active CC line */
hal_status_t HAL_UCPD_SetActiveCC(hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line);
hal_ucpd_cc_line_t HAL_UCPD_GetActiveCC(hal_ucpd_handle_t *hucpd);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/* Fast Role Swap Rx */
hal_status_t HAL_UCPD_EnableFRS_Rx(const hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableFRS_Rx(const hal_ucpd_handle_t *hucpd);
hal_ucpd_frs_rx_status_t HAL_UCPD_IsEnabledFRS_Rx(hal_ucpd_handle_t *hucpd);

/* Fast Role Swap Tx */
hal_status_t HAL_UCPD_SendFRS(hal_ucpd_handle_t *hucpd);

/* Cable reset Tx */
hal_status_t HAL_UCPD_SendCableReset(hal_ucpd_handle_t *hucpd);

/* Hard reset Tx */
hal_status_t HAL_UCPD_SendHardReset(const hal_ucpd_handle_t *hucpd);

/* Hard reset Rx */
hal_status_t HAL_UCPD_EnableHardReset_Rx(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_DisableHardReset_Rx(hal_ucpd_handle_t *hucpd);
hal_ucpd_hard_reset_rx_status_t HAL_UCPD_IsEnabledHardReset_Rx(hal_ucpd_handle_t *hucpd);

/* BIST */
hal_status_t HAL_UCPD_SendBIST(hal_ucpd_handle_t *hucpd);
hal_status_t HAL_UCPD_StopBIST(hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @}
  */

/** @defgroup UCPD_Exported_Functions_Group4 Status functions
  * @{
  */

/* CC line voltage status */
hal_ucpd_vstate_t HAL_UCPD_GetTypeCVoltageLevelCCx(const hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/* Detected Rx ordered set */
hal_ucpd_detected_rx_ordered_set_t HAL_UCPD_GetDetectedRxOrderedSet(hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @}
  */

/** @defgroup UCPD_Exported_Functions_Group5 IO operation functions
  * @{
  */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
hal_status_t HAL_UCPD_Transmit_DMA(hal_ucpd_handle_t *hucpd, const void *p_data, uint32_t size_byte);
hal_status_t HAL_UCPD_Receive_DMA(hal_ucpd_handle_t *hucpd, void *p_data, uint32_t size_byte);

hal_status_t HAL_UCPD_Abort_IT(hal_ucpd_handle_t *hucpd);

hal_status_t HAL_UCPD_SetGoodCRCData(hal_ucpd_handle_t *hucpd, uint16_t goodcrc_data);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
/**
  * @}
  */

/** @defgroup UCPD_Exported_Functions_Group6 IRQHandler and Callbacks functions
  * @{
  */

void HAL_UCPD_IRQHandler(hal_ucpd_handle_t *hucpd);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
void HAL_UCPD_TxCpltCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_TxGoodCRCCpltCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_TxDiscardCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_TxAbortCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_RxCpltCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_RxOrdDetCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_HRstSentCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_HRstRxCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_HRstDiscardCallback(hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
void HAL_UCPD_TypeCEventCCxCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line);
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
void HAL_UCPD_FRSEvtCallback(hal_ucpd_handle_t *hucpd);
void HAL_UCPD_AbortCpltCallback(hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
void HAL_UCPD_ErrorCallback(hal_ucpd_handle_t *hucpd);


#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
hal_status_t HAL_UCPD_RegisterTxCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterTxGoodCRCCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterTxDiscardCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterTxAbortCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterRxCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterRxOrdDetCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterHRstSentCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterHRstRxCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterHRstDiscardCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
hal_status_t HAL_UCPD_RegisterTypeCEventCCxCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cc_event_cb_t p_callback);
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
hal_status_t HAL_UCPD_RegisterFRSEvtCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
hal_status_t HAL_UCPD_RegisterAbortCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
hal_status_t HAL_UCPD_RegisterErrorCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback);

#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup UCPD_Exported_Functions_Group7 Peripheral State, Error functions
  * @{
  */

hal_ucpd_state_t HAL_UCPD_GetState(const hal_ucpd_handle_t *hucpd);

#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
uint32_t HAL_UCPD_GetLastErrorCodes(const hal_ucpd_handle_t *hucpd);
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

/**
  * @}
  */

#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @defgroup UCPD_Exported_Functions_Group8 Acquire/Release the bus
  * @{
  */

hal_status_t HAL_UCPD_AcquireBus(hal_ucpd_handle_t *hucpd, uint32_t timeout_ms);
hal_status_t HAL_UCPD_ReleaseBus(hal_ucpd_handle_t *hucpd);

/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_UCPD_USER_DATA) && (USE_HAL_UCPD_USER_DATA == 1)
/** @defgroup UCPD_Exported_Functions_Group9 Set/Get user data
  * @{
  */

void HAL_UCPD_SetUserData(hal_ucpd_handle_t *hucpd, const void *p_user_data);
const void *HAL_UCPD_GetUserData(const hal_ucpd_handle_t *hucpd);

/**
  * @}
  */

#endif /* USE_HAL_UCPD_USER_DATA */
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

#endif /* STM32G5XX_HAL_UCPD_H */
