/**
  ******************************************************************************
  * @file    stm32g5xx_ll_tamp.h
  * @brief   Header file of TAMP LL module.
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
#ifndef STM32G5XX_LL_TAMP_H
#define STM32G5XX_LL_TAMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */

#if defined(TAMP)

/** @defgroup TAMP_LL TAMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------*/
/** @defgroup TAMP_LL_Exported_Constants LL TAMP Constants
  * @{
  */
#define LL_POSITION_FIRST_ITAMP        TAMP_CR1_ITAMP1E_Pos
#define LL_POSITION_OFFSET_REG_ITAMP   16U
#define TAMP_CR2_CFG_MSK               (LL_TAMP_NOERASE_TAMPER_ALL \
                                        | LL_TAMP_ACTIVELEVEL_TAMP_ALL | LL_TAMP_MASK_TAMPER_ALL)

#define LL_TAMP_NUMBER_TAMPERS         2U /*!< Number of tampers */
#define LL_TAMP_POSITION_FIRST_MASKED  TAMP_CR2_TAMP1MSK_Pos /*!< Tamper first masked */
#define LL_TAMP_BACKUP_NB              TAMP_BACKUP_NB /*!< Number of TAMP backup registers */

/** @defgroup TAMP_LL_EC_TAMPER  TAMPER
  * @{
  */
#define LL_TAMP_1                    TAMP_CR1_TAMP1E /*!< Tamper 1 input detection */
#define LL_TAMP_2                    TAMP_CR1_TAMP2E /*!< Tamper 2 input detection */
#define LL_TAMP_ALL                  (TAMP_CR1_TAMP1E | TAMP_CR1_TAMP2E) /*!< All tampers input selection */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_MASK  TAMPER MASK
  * @{
  */
#define LL_TAMP_MASK_NONE            0U
#define LL_TAMP_MASK_TAMPER          TAMP_CR2_TAMP1MSK /*!< Tamper 1 event generates a trigger event. TAMP1F is masked and internally cleared by hardware. The backup registers are not erased */
#define LL_TAMP_MASK_TAMPER1         TAMP_CR2_TAMP1MSK /*!< Tamper 1 event generates a trigger event. TAMP1F is masked and internally cleared by hardware.The backup registers are not erased */
#define LL_TAMP_MASK_TAMPER2         TAMP_CR2_TAMP2MSK /*!< Tamper 2 event generates a trigger event. TAMP2F is masked and internally cleared by hardware. The backup registers are not erased. */
#define LL_TAMP_MASK_TAMPER_ALL      (TAMP_CR2_TAMP1MSK | TAMP_CR2_TAMP2MSK) /*!< Tamper 1-2 event generates a trigger event. TAMP1-2F are masked and internally cleared by hardware.The backup registers are not erased */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_NOERASE  TAMPER NO ERASE
  * @{
  */
#define LL_TAMP_ERASE_ACTIVATE_ALL   0U
#define LL_TAMP_NOERASE_TAMPER       TAMP_CR2_TAMP1POM /*!< Tamper 1 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER1      TAMP_CR2_TAMP1POM /*!< Tamper 1 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER2      TAMP_CR2_TAMP2POM /*!< Tamper 2 event does not erase the backup registers. */
#define LL_TAMP_NOERASE_TAMPER_ALL   (TAMP_CR2_TAMP1POM | TAMP_CR2_TAMP2POM) /*!< All tampers events do not erase the backup registers. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_BACKUP_BLOCK BACKUP BLOCKED
  * @{
  */

#define LL_TAMP_BACKUP_BLOCK_DISABLE   0U                /*!< Tamper backup block is disabled */
#define LL_TAMP_BACKUP_BLOCK_ENABLE    TAMP_CR2_BKBLOCK  /*!< Tamper backup block is enabled */

/**
  * @}
  */


/** @defgroup TAMP_LL_EC_TAMPER_DURATION  TAMPER DURATION
  * @{
  */
#define LL_TAMP_DURATION_1RTCCLK     0U                     /*!< Tamper pins are pre-charged before sampling during 1 RTCCLK cycle  */
#define LL_TAMP_DURATION_2RTCCLK     TAMP_FLTCR_TAMPPRCH_0  /*!< Tamper pins are pre-charged before sampling during 2 RTCCLK cycles */
#define LL_TAMP_DURATION_4RTCCLK     TAMP_FLTCR_TAMPPRCH_1  /*!< Tamper pins are pre-charged before sampling during 4 RTCCLK cycles */
#define LL_TAMP_DURATION_8RTCCLK     TAMP_FLTCR_TAMPPRCH    /*!< Tamper pins are pre-charged before sampling during 8 RTCCLK cycles */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_FILTER  TAMPER FILTER
  * @{
  */
#define LL_TAMP_FILTER_DISABLE       0U                      /*!< Tamper filter is disabled */
#define LL_TAMP_FILTER_2SAMPLES      TAMP_FLTCR_TAMPFLT_0    /*!< Tamper is activated after 2 consecutive samples at the active level */
#define LL_TAMP_FILTER_4SAMPLES      TAMP_FLTCR_TAMPFLT_1    /*!< Tamper is activated after 4 consecutive samples at the active level */
#define LL_TAMP_FILTER_8SAMPLES      TAMP_FLTCR_TAMPFLT      /*!< Tamper is activated after 8 consecutive samples at the active level. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_SAMPLFREQDIV  TAMPER SAMPLING FREQUENCY DIVIDER
  * @{
  */
#define LL_TAMP_SAMPLFREQDIV_32768   0U                                              /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 32768 */
#define LL_TAMP_SAMPLFREQDIV_16384   TAMP_FLTCR_TAMPFREQ_0                           /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 16384 */
#define LL_TAMP_SAMPLFREQDIV_8192    TAMP_FLTCR_TAMPFREQ_1                           /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 8192 */
#define LL_TAMP_SAMPLFREQDIV_4096    (TAMP_FLTCR_TAMPFREQ_1 | TAMP_FLTCR_TAMPFREQ_0) /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 4096 */
#define LL_TAMP_SAMPLFREQDIV_2048    TAMP_FLTCR_TAMPFREQ_2                           /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 2048 */
#define LL_TAMP_SAMPLFREQDIV_1024    (TAMP_FLTCR_TAMPFREQ_2 | TAMP_FLTCR_TAMPFREQ_0) /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 1024 */
#define LL_TAMP_SAMPLFREQDIV_512     (TAMP_FLTCR_TAMPFREQ_2 | TAMP_FLTCR_TAMPFREQ_1) /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 512 */
#define LL_TAMP_SAMPLFREQDIV_256     TAMP_FLTCR_TAMPFREQ                             /*!< Each of the tamper inputs is sampled with a frequency = RTCCLK / 256 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_PULL_UP TAMPER PULL UP
  * @{
  */
#define LL_TAMP_PULL_UP_ENABLE        0U                    /*!< Precharge TAMP_INx pins before sampling (enable internal pull-up) */
#define LL_TAMP_PULL_UP_DISABLE       TAMP_FLTCR_TAMPPUDIS  /*!< Disable precharge of TAMP_INx pins                                */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_ACTIVELEVEL  TAMPER ACTIVE LEVEL
  * @{
  */
#define LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL  0U
#define LL_TAMP_ACTIVELEVEL_TAMP            TAMP_CR2_TAMP1TRG /*!< Tamper 1 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP1    TAMP_CR2_TAMP1TRG /*!< Tamper 1 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP2    TAMP_CR2_TAMP2TRG /*!< Tamper 2 input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
#define LL_TAMP_ACTIVELEVEL_TAMP_ALL (TAMP_CR2_TAMP1TRG | TAMP_CR2_TAMP2TRG) /*!< All tamper input falling edge (if TAMPFLT = 00) or staying high (if TAMPFLT != 00) triggers a tamper detection event */
/**
  * @}
  */


/** @defgroup TAMP_LL_EC_INTERNAL  INTERNAL TAMPER
  * @{
  */
#define LL_TAMP_ITAMP1                TAMP_CR1_ITAMP1E  /*!< Internal tamper 1: VDD domain monitoring */
#define LL_TAMP_ITAMP2                TAMP_CR1_ITAMP2E  /*!< Internal tamper 2: Temperature monitoring */
#define LL_TAMP_ITAMP3                TAMP_CR1_ITAMP3E  /*!< Internal tamper 3: LSE monitoring */
#define LL_TAMP_ITAMP4                TAMP_CR1_ITAMP4E  /*!< Internal tamper 4: HSE monitoring */
#define LL_TAMP_ITAMP5                TAMP_CR1_ITAMP5E  /*!< Internal tamper 5: RTC calendar overflow */
#define LL_TAMP_ITAMP6                TAMP_CR1_ITAMP6E  /*!< Internal tamper 6: Unexpected debug activation */
#define LL_TAMP_ITAMP7                TAMP_CR1_ITAMP7E  /*!< Internal tamper 7: ADC2 analog watchdog 1 */
#define LL_TAMP_ITAMP8                TAMP_CR1_ITAMP8E  /*!< Internal tamper 8: Monotonic counter 1 overflow */
#define LL_TAMP_ITAMP9                TAMP_CR1_ITAMP9E  /*!< Internal tamper 9: Cryptographic peripherals fault */
#define LL_TAMP_ITAMP11               TAMP_CR1_ITAMP11E /*!< Internal tamper 11: IWDG reset when tamper flag is set (potential tamper timeout) */
#define LL_TAMP_ITAMP12               TAMP_CR1_ITAMP12E /*!< Internal tamper 12: ADC2 analog watchdog 2 */
#ifdef ADC3
#define LL_TAMP_ITAMP13               TAMP_CR1_ITAMP13E /*!< Internal tamper 13: ADC3 analog watchdog 1 */
#define LL_TAMP_ITAMP14               TAMP_CR1_ITAMP14E /*!< Internal tamper 14: ADC3 analog watchdog 2 */
#endif /* ADC3 */
#define LL_TAMP_ITAMP15               TAMP_CR1_ITAMP15E /*!< Internal tamper 15: System fault */
#ifdef ADC3
#define LL_TAMP_ITAMP_ALL             (TAMP_CR1_ITAMP1E  | TAMP_CR1_ITAMP2E  | TAMP_CR1_ITAMP3E \
                                       | TAMP_CR1_ITAMP4E  | TAMP_CR1_ITAMP5E  | TAMP_CR1_ITAMP6E \
                                       | TAMP_CR1_ITAMP7E  | TAMP_CR1_ITAMP8E  | TAMP_CR1_ITAMP9E \
                                       | TAMP_CR1_ITAMP11E | TAMP_CR1_ITAMP12E | TAMP_CR1_ITAMP13E \
                                       | TAMP_CR1_ITAMP14E | TAMP_CR1_ITAMP15E) /*!< All internal tampers */
#else
#define LL_TAMP_ITAMP_ALL             (TAMP_CR1_ITAMP1E  | TAMP_CR1_ITAMP2E  | TAMP_CR1_ITAMP3E \
                                       | TAMP_CR1_ITAMP4E  | TAMP_CR1_ITAMP5E  | TAMP_CR1_ITAMP6E \
                                       | TAMP_CR1_ITAMP7E  | TAMP_CR1_ITAMP8E  | TAMP_CR1_ITAMP9E \
                                       | TAMP_CR1_ITAMP11E | TAMP_CR1_ITAMP12E | TAMP_CR1_ITAMP15E)
/*!< All internal tampers */
#endif /* ADC3 */
/**
  * @}
  */

/**
  * @defgroup TAMP_LL_EC_INTERNAL_MODE INTERNAL TAMPER MODE
  * @{
  */
#define LL_TAMP_ITAMP_ERASE_ACTIVE_ALL    0U
#define LL_TAMP_ITAMP_NOERASE_TAMPER      TAMP_CR3_ITAMP1POM  /*!< Internal tamper 1 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER1     TAMP_CR3_ITAMP1POM  /*!< Internal tamper 1 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER2     TAMP_CR3_ITAMP2POM  /*!< Internal tamper 2 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER3     TAMP_CR3_ITAMP3POM  /*!< Internal tamper 3 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER4     TAMP_CR3_ITAMP4POM  /*!< Internal tamper 4 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER5     TAMP_CR3_ITAMP5POM  /*!< Internal tamper 5 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER6     TAMP_CR3_ITAMP6POM  /*!< Internal tamper 6 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER7     TAMP_CR3_ITAMP7POM  /*!< Internal tamper 7 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER8     TAMP_CR3_ITAMP8POM  /*!< Internal tamper 8 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER9     TAMP_CR3_ITAMP9POM  /*!< Internal tamper 9 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER11    TAMP_CR3_ITAMP11POM /*!< Internal tamper 11 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER12    TAMP_CR3_ITAMP12POM /*!< Internal tamper 12 potential mode */
#ifdef ADC3
#define LL_TAMP_ITAMP_NOERASE_TAMPER13    TAMP_CR3_ITAMP13POM /*!< Internal tamper 13 potential mode */
#define LL_TAMP_ITAMP_NOERASE_TAMPER14    TAMP_CR3_ITAMP14POM /*!< Internal tamper 14 potential mode */
#endif /* ADC3 */
#define LL_TAMP_ITAMP_NOERASE_TAMPER15    TAMP_CR3_ITAMP15POM /*!< Internal tamper 15 potential mode */
#ifdef ADC3
#define LL_TAMP_ITAMP_NOERASE_TAMPER_ALL  (TAMP_CR3_ITAMP1POM  | TAMP_CR3_ITAMP2POM  | TAMP_CR3_ITAMP3POM \
                                           | TAMP_CR3_ITAMP4POM  | TAMP_CR3_ITAMP5POM  | TAMP_CR3_ITAMP6POM \
                                           | TAMP_CR3_ITAMP7POM  | TAMP_CR3_ITAMP8POM  | TAMP_CR3_ITAMP9POM \
                                           | TAMP_CR3_ITAMP11POM | TAMP_CR3_ITAMP12POM | TAMP_CR3_ITAMP13POM \
                                           | TAMP_CR3_ITAMP14POM | TAMP_CR3_ITAMP15POM)
#else
#define LL_TAMP_ITAMP_NOERASE_TAMPER_ALL  (TAMP_CR3_ITAMP1POM  | TAMP_CR3_ITAMP2POM  | TAMP_CR3_ITAMP3POM \
                                           | TAMP_CR3_ITAMP4POM  | TAMP_CR3_ITAMP5POM  | TAMP_CR3_ITAMP6POM \
                                           | TAMP_CR3_ITAMP7POM  | TAMP_CR3_ITAMP8POM  | TAMP_CR3_ITAMP9POM \
                                           | TAMP_CR3_ITAMP11POM | TAMP_CR3_ITAMP12POM | TAMP_CR3_ITAMP15POM)
#endif /* ADC3 */
/*!< All internal tampers events do not erase the device secrets. */

/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_MODE   ACTIVE TAMPER MODE
  * @{
  */
#define LL_TAMP_ATAMP_TAMP1AM               TAMP_ATCR1_TAMP1AM /*!< tamper 1 is active */
#define LL_TAMP_ATAMP_TAMP2AM               TAMP_ATCR1_TAMP2AM /*!< tamper 2 is active */
#define LL_TAMP_ATAMP_TAMPAM_ALL            (TAMP_ATCR1_TAMP1AM | TAMP_ATCR1_TAMP2AM)
/*!< All tampers are active */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_ATCR1_REGISTER_ACTIVE_TAMP_OUTPUT_PERIOD  Active TAMPER output period
  * @{
  */
#define LL_TAMP_OUTPUT_PERIOD  (TAMP_ATCR1_ATPER_Msk >> TAMP_ATCR1_ATPER_Pos) /*!< Active tamper output period */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_ASYNC_PRESCALER   ACTIVE TAMPER ASYNCHRONOUS PRESCALER CLOCK
  * @{
  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK       0U                                                                      /*!< RTCCLK     */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2     TAMP_ATCR1_ATCKSEL_0                                                    /*!< RTCCLK/2   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_4     TAMP_ATCR1_ATCKSEL_1                                                    /*!< RTCCLK/4   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_8     (TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)                           /*!< RTCCLK/8   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_16    TAMP_ATCR1_ATCKSEL_2                                                    /*!< RTCCLK/16  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_32    (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_0)                           /*!< RTCCLK/32  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_64    (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1)                           /*!< RTCCLK/64  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_128   (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)    /*!< RTCCLK/128 */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_256   TAMP_ATCR1_ATCKSEL_3                                                    /*!< RTCCLK/256   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_512   (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_0)                           /*!< RTCCLK/512   */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_1024  (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_1)                           /*!< RTCCLK/1024  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2048  (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)    /*!< RTCCLK/2048  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_4096  (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_2)                           /*!< RTCCLK/4096  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_8192  (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_0)    /*!< RTCCLK/8192  */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_16384 (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1)    /*!< RTCCLK/16384 */
#define LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_32768 (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1 |\
                                              TAMP_ATCR1_ATCKSEL_0)                                                  /*!< RTCCLK/32768 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_FILTERING ACTIVE TAMPER FILTERING
  * @{
  */
#define LL_TAMP_ATAMP_FILTERING_DISABLE  0U                      /*!< Active tamper filtering disable */
#define LL_TAMP_ATAMP_FILTERING_ENABLE   TAMP_ATCR1_FLTEN        /*!< Active tamper filter enable     */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_SHARING ACTIVE TAMPER SHARING
  * @{
  */
#define LL_TAMP_ATAMP_SHARING_DISABLE     0U                     /*!< Each active tamper input TAMP_INi is compared with its dedicated output TAMP_OUTi */
#define LL_TAMP_ATAMP_SHARING_ENABLE      TAMP_ATCR1_ATOSHARE    /*!< Each active tamper input TAMP_INi is compared with TAMPOUTSELi defined by ATOSELi bits. */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION   ACTIVE TAMPER OUTPUT SELECTION
  * @{
  */
#define TAMP_ATCR2_ATOSEL_MSK       (TAMP_ATCR2_ATOSEL1 | TAMP_ATCR2_ATOSEL2)

#define LL_TAMP_ATAMP1IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP1IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL1_Pos) /*!< Active tamper 1 output is set to TAMP_OUT2 */

#define LL_TAMP_ATAMP2IN_ATAMP1OUT  (0U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT1 */
#define LL_TAMP_ATAMP2IN_ATAMP2OUT  (1U << TAMP_ATCR2_ATOSEL2_Pos) /*!< Active tamper 2 output is set to TAMP_OUT2 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_IT TAMPER IT
  * @{
  */
#define LL_TAMP_IT_NONE         0U
#define LL_TAMP_IT_TAMPER_1     TAMP_IER_TAMP1IE /*!< Tamper 1 interrupt enable */
#define LL_TAMP_IT_TAMPER_2     TAMP_IER_TAMP2IE /*!< Tamper 2 interrupt enable */
#define LL_TAMP_IT_ALL          (TAMP_IER_TAMP1IE | TAMP_IER_TAMP2IE)
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_INTERNAL_TAMPER_IT INTERNAL TAMPER IT
  * @{
  */
#define LL_TAMP_INTERNAL_IT_NONE         0U
#define LL_TAMP_INTERNAL_IT_TAMPER_1     TAMP_IER_ITAMP1IE   /*!< Internal tamper 1 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_2     TAMP_IER_ITAMP2IE   /*!< Internal tamper 2 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_3     TAMP_IER_ITAMP3IE   /*!< Internal tamper 3 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_4     TAMP_IER_ITAMP4IE   /*!< Internal tamper 4 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_5     TAMP_IER_ITAMP5IE   /*!< Internal tamper 5 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_6     TAMP_IER_ITAMP6IE   /*!< Internal tamper 6 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_7     TAMP_IER_ITAMP7IE   /*!< Internal tamper 7 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_8     TAMP_IER_ITAMP8IE   /*!< Internal tamper 8 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_9     TAMP_IER_ITAMP9IE   /*!< Internal tamper 9 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_11    TAMP_IER_ITAMP11IE  /*!< Internal tamper 11 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_12    TAMP_IER_ITAMP12IE  /*!< Internal tamper 12 interrupt enable */
#ifdef ADC3
#define LL_TAMP_INTERNAL_IT_TAMPER_13    TAMP_IER_ITAMP13IE  /*!< Internal tamper 13 interrupt enable */
#define LL_TAMP_INTERNAL_IT_TAMPER_14    TAMP_IER_ITAMP14IE  /*!< Internal tamper 14 interrupt enable */
#endif /* ADC3 */
#define LL_TAMP_INTERNAL_IT_TAMPER_15    TAMP_IER_ITAMP15IE  /*!< Internal tamper 15 interrupt enable */
#ifdef ADC3
#define LL_TAMP_INTERNAL_IT_ALL          (TAMP_IER_ITAMP1IE  | TAMP_IER_ITAMP2IE  | TAMP_IER_ITAMP3IE \
                                          | TAMP_IER_ITAMP4IE  | TAMP_IER_ITAMP5IE  | TAMP_IER_ITAMP6IE \
                                          | TAMP_IER_ITAMP7IE  | TAMP_IER_ITAMP8IE  | TAMP_IER_ITAMP9IE \
                                          | TAMP_IER_ITAMP11IE | TAMP_IER_ITAMP12IE | TAMP_IER_ITAMP13IE \
                                          | TAMP_IER_ITAMP14IE | TAMP_IER_ITAMP15IE)
#else
#define LL_TAMP_INTERNAL_IT_ALL          (TAMP_IER_ITAMP1IE  | TAMP_IER_ITAMP2IE  | TAMP_IER_ITAMP3IE \
                                          | TAMP_IER_ITAMP4IE  | TAMP_IER_ITAMP5IE  | TAMP_IER_ITAMP6IE \
                                          | TAMP_IER_ITAMP7IE  | TAMP_IER_ITAMP8IE  | TAMP_IER_ITAMP9IE \
                                          | TAMP_IER_ITAMP11IE | TAMP_IER_ITAMP12IE | TAMP_IER_ITAMP15IE)
#endif /* ADC3 */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_RESOURCE_PROTECTION RESOURCE PROTECTION
  * @{
  */
#define LL_TAMP_RESOURCE_1        TAMP_RPCFGR_RPCFG1 /*!< SRAM2 is protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_2        TAMP_RPCFGR_RPCFG2 /*!< RHUK, SAES, CRYP, CCB are protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_3        TAMP_RPCFGR_RPCFG3 /*!< ICACHE is protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_4        TAMP_RPCFGR_RPCFG4 /*!< HASH is protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_5        TAMP_RPCFGR_RPCFG5 /*!< PKA is protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_6        TAMP_RPCFGR_RPCFG6 /*!< DCACHE is protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_7        TAMP_RPCFGR_RPCFG7 /*!< OTFDEC KEYS, CRC are protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_8        TAMP_RPCFGR_RPCFG8 /*!< SRAM1 is protected by TAMP peripheral */
#define LL_TAMP_RESOURCE_31       TAMP_RPCFGR_RPCFG31 /*!< Backup registers, BHK are protected by TAMP peripheral */
#define LL_TAMP_RESOURCES_ALL    (TAMP_RPCFGR_RPCFG1 | TAMP_RPCFGR_RPCFG2 | TAMP_RPCFGR_RPCFG3 \
                                  | TAMP_RPCFGR_RPCFG4 | TAMP_RPCFGR_RPCFG5 | TAMP_RPCFGR_RPCFG6 \
                                  | TAMP_RPCFGR_RPCFG7 | TAMP_RPCFGR_RPCFG8 | TAMP_RPCFGR_RPCFG31)
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_TAMPER_REMAP TAMPER REMAP
  * @{
  */
#define LL_TAMP_RMP_TAMP_IN1_PA0_TO_PB9     TAMP_OR_IN1_RMP
#define LL_TAMP_RMP_TAMP_IN2_PA1_TO_PC13    TAMP_OR_IN2_RMP
#define LL_TAMP_RMP_TAMP_OUT1_PA2_TO_PC13   TAMP_OR_OUT1_RMP
#ifdef TAMP_OR_OUT2_RMP
#define LL_TAMP_RMP_TAMP_OUT2_PB9_TO_PE3    TAMP_OR_OUT2_RMP
#endif /* TAMP_OR_OUT2_RMP */
/**
  * @}
  */

/** @defgroup TAMP_LL_EC_BKP  BACKUP REGISTER
  * @{
  */
#define LL_TAMP_BKP_NUMBER                  TAMP_BACKUP_NB        /*!< Number of TAMP backup registers */
#define LL_TAMP_BKP_DR0                     0U                    /*!< TAMP backup register 0 */
#define LL_TAMP_BKP_DR1                     1U                    /*!< TAMP backup register 1 */
#define LL_TAMP_BKP_DR2                     2U                    /*!< TAMP backup register 2 */
#define LL_TAMP_BKP_DR3                     3U                    /*!< TAMP backup register 3 */
#define LL_TAMP_BKP_DR4                     4U                    /*!< TAMP backup register 4 */
#define LL_TAMP_BKP_DR5                     5U                    /*!< TAMP backup register 5 */
#define LL_TAMP_BKP_DR6                     6U                    /*!< TAMP backup register 6 */
#define LL_TAMP_BKP_DR7                     7U                    /*!< TAMP backup register 7 */
#define LL_TAMP_BKP_DR8                     8U                    /*!< TAMP backup register 8 */
#define LL_TAMP_BKP_DR9                     9U                    /*!< TAMP backup register 9 */
#define LL_TAMP_BKP_DR10                    10U                   /*!< TAMP backup register 10 */
#define LL_TAMP_BKP_DR11                    11U                   /*!< TAMP backup register 11 */
#define LL_TAMP_BKP_DR12                    12U                   /*!< TAMP backup register 12 */
#define LL_TAMP_BKP_DR13                    13U                   /*!< TAMP backup register 13 */
#define LL_TAMP_BKP_DR14                    14U                   /*!< TAMP backup register 14 */
#define LL_TAMP_BKP_DR15                    15U                   /*!< TAMP backup register 15 */
#if defined(TAMP_BKP16R_BKP)
#define LL_TAMP_BKP_DR16                    16U                   /*!< TAMP backup register 16 */
#define LL_TAMP_BKP_DR17                    17U                   /*!< TAMP backup register 17 */
#define LL_TAMP_BKP_DR18                    18U                   /*!< TAMP backup register 18 */
#define LL_TAMP_BKP_DR19                    19U                   /*!< TAMP backup register 19 */
#define LL_TAMP_BKP_DR20                    20U                   /*!< TAMP backup register 20 */
#define LL_TAMP_BKP_DR21                    21U                   /*!< TAMP backup register 21 */
#define LL_TAMP_BKP_DR22                    22U                   /*!< TAMP backup register 22 */
#define LL_TAMP_BKP_DR23                    23U                   /*!< TAMP backup register 23 */
#define LL_TAMP_BKP_DR24                    24U                   /*!< TAMP backup register 24 */
#define LL_TAMP_BKP_DR25                    25U                   /*!< TAMP backup register 25 */
#define LL_TAMP_BKP_DR26                    26U                   /*!< TAMP backup register 26 */
#define LL_TAMP_BKP_DR27                    27U                   /*!< TAMP backup register 27 */
#define LL_TAMP_BKP_DR28                    28U                   /*!< TAMP backup register 28 */
#define LL_TAMP_BKP_DR29                    29U                   /*!< TAMP backup register 29 */
#define LL_TAMP_BKP_DR30                    30U                   /*!< TAMP backup register 30 */
#define LL_TAMP_BKP_DR31                    31U                   /*!< TAMP backup register 31 */
#endif /* defined(TAMP_BKP16R_BKP) */
/**
  * @}
  */

/** @defgroup TAMP_secure_attributes_configuration_items TAMP attributes configuration items
  * @{
  */
#define LL_TAMP_ATTR_NSEC 0UL  /*!< Non-secure attribute     */
#define LL_TAMP_ATTR_SEC  1UL  /*!< Secure attribute         */

#define LL_TAMP_SEC_ITEM_TAMPSEC TAMP_SECCFGR_TAMPSEC  /*!< Secure attribute of tamper protection          */
#define LL_TAMP_SEC_ITEM_CNT1SEC TAMP_SECCFGR_CNT1SEC  /*!< Secure attribute of monotonic counter 1        */

/**
  * @}
  */
/** @defgroup TAMP_privilege_attributes_configuration_items TAMP attributes configuration items
  * @{
  */
#define LL_TAMP_ATTR_NPRIV 0UL /*!< Non-privileged attribute */
#define LL_TAMP_ATTR_PRIV  1UL /*!< Privileged attribute     */

#define LL_TAMP_PRIV_ITEM_TAMPPRIV  TAMP_PRIVCFGR_TAMPPRIV  /*!< Privilege attribute of tamper protection  */
#define LL_TAMP_PRIV_ZONE_BKPWPRIV  TAMP_PRIVCFGR_BKPWPRIV  /*!< Privilege multiple attribute of Backup
                                                                 registers zone 2 */
#define LL_TAMP_PRIV_ZONE_BKPRWPRIV TAMP_PRIVCFGR_BKPRWPRIV /*!< Privilege multiple attribute of Backup
                                                                 registers zone 1 */
#define LL_TAMP_PRIV_ITEM_CNT1PRIV  TAMP_PRIVCFGR_CNT1PRIV  /*!< Privilege attribute of Monotonic counter 1     */

/**
  * @}
  */


/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/** @defgroup TAMP_LL_Exported_Macros LL TAMP Macros
  * @{
  */

/** @defgroup TAMP_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */


/**
  * @brief  Write a value in TAMP register.
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_TAMP_WRITE_REG(__REG__, __VALUE__) STM32_WRITE_REG(TAMP->__REG__, (__VALUE__))

/**
  * @brief  Read a value in TAMP register.

  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_TAMP_READ_REG(__REG__) STM32_READ_REG(TAMP->__REG__)
/**
  * @}
  */

/** @defgroup TAMP_LL_EM_helper Helper macros
  * @{
  */

/**
  * @brief Helper macro to retrieve pull_up precharge configuration.
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_PULL_UP_ENABLE
  *        @arg @ref LL_TAMP_PULL_UP_DISABLE
  */
#define LL_TAMP_GET_PULL_UP(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPPUDIS)

/**
  * @brief Helper macro to retrieve pull_up precharge duration configuration.
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_DURATION_1RTCCLK
  *        @arg @ref LL_TAMP_DURATION_2RTCCLK
  *        @arg @ref LL_TAMP_DURATION_4RTCCLK
  *        @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
#define LL_TAMP_GET_PRECHARGE_DURATION(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPPRCH)

/**
  * @brief Helper macro to retrieve pull_up precharge configuration.
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_FILTER_DISABLE
  *        @arg @ref LL_TAMP_FILTER_2SAMPLES
  *        @arg @ref LL_TAMP_FILTER_4SAMPLES
  *        @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
#define LL_TAMP_GET_FILTER_SAMPLE(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPFLT)

/**
  * @brief Helper macro to retrieve pull_up precharge configuration.
  * @param tamp_config_value Value returned by @ref LL_TAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
#define LL_TAMP_GET_FILTER_SAMPLE_FREQUENCY(tamp_config_value) ((tamp_config_value) & TAMP_FLTCR_TAMPFREQ)

/**
  * @brief Helper macro to retrieve the trigger edge or level.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL
  *         @arg @ref LL_TAMP_ACTIVELEVEL_TAMP
  */
#define LL_TAMP_GET_TRIGGER(tamp_config_indiv_value) ((((tamp_config_indiv_value) & \
                                                        LL_TAMP_ACTIVELEVEL_TAMP_ALL) != 0U ) ?\
                                                      LL_TAMP_ACTIVELEVEL_TAMP : LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL)

/**
  * @brief Helper macro to retrieve the mode of the tamper.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ERASE_ACTIVATE_ALL
  *         @arg @ref LL_TAMP_NOERASE_TAMPER
  */
#define LL_TAMP_GET_NOERASE(tamp_config_indiv_value) ((((tamp_config_indiv_value) &\
                                                        LL_TAMP_NOERASE_TAMPER_ALL) != 0U ) ?\
                                                      LL_TAMP_NOERASE_TAMPER : LL_TAMP_ERASE_ACTIVATE_ALL)

/**
  * @brief Helper macro to retrieve the mask of the tamper.
  * @param tamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_MASK_NONE
  *         @arg @ref LL_TAMP_MASK_TAMPER
  */
#define LL_TAMP_GET_MASK(tamp_config_indiv_value) ((((tamp_config_indiv_value) &\
                                                     LL_TAMP_MASK_TAMPER_ALL) != 0U ) ?\
                                                   LL_TAMP_MASK_TAMPER : LL_TAMP_MASK_NONE)

/**
  * @brief Helper macro to retrieve the mode of the internal tamper.
  * @param itamp_config_indiv_value Value returned by @ref LL_TAMP_GetConfigInternalTampers
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_TAMP_ITAMP_ERASE_ACTIVE_ALL
  *         @arg @ref LL_TAMP_ITAMP_NOERASE_TAMPER
  */
#define LL_TAMP_INTERNAL_GET_NOERASE(itamp_config_indiv_value) ((((itamp_config_indiv_value) &\
                                                                  LL_TAMP_ITAMP_NOERASE_TAMPER_ALL) != 0U ) \
                                                                ? LL_TAMP_ITAMP_NOERASE_TAMPER : \
                                                                LL_TAMP_ITAMP_ERASE_ACTIVE_ALL)

/**
  * @brief Helper macro to retrieve the active filtering status.
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_ATAMP_FILTERING_DISABLE
  *        @arg @ref LL_TAMP_ATAMP_FILTERING_ENABLE
  */
#define LL_TAMP_ACTIVE_GET_FILTER(atamp_config_value) ((atamp_config_value) & TAMP_ATCR1_FLTEN)

/**
  * @brief Helper macro to retrieve the period when the output signals changes.
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value is between 0 and 7.
  */
#define LL_TAMP_ACTIVE_GET_OUTPUT_PERIOD(atamp_config_value) (((atamp_config_value) &\
                                                               TAMP_ATCR1_ATPER) >> TAMP_ATCR1_ATPER_Pos)

/**
  * @brief Helper macro to retrieve the asysnchronous prescaler.
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_4
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_8
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_16
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_32
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_64
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_128
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_256
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_512
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_1024
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_2048
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_4096
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_8192
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_16384
  *        @arg @ref LL_TAMP_ATAMP_ASYNCPRES_RTCCLK_32768
  */
#define LL_TAMP_ACTIVE_GET_PRESCALER(atamp_config_value) ((atamp_config_value) & TAMP_ATCR1_ATCKSEL)

/**
  * @brief Helper macro to retrieve the sharing status of the active tampers.
  * @param atamp_config_value Value returned by @ref LL_TAMP_ATAMP_GetConfig
  * @retval Return value can be one of the following values:
  *        @arg @ref LL_TAMP_ATAMP_SHARING_DISABLE
  *        @arg @ref LL_TAMP_ATAMP_SHARING_ENABLE
  */
#define LL_TAMP_ACTIVE_GET_SHARING(atamp_config_value) ((atamp_config_value) & TAMP_ATCR1_ATOSHARE)

/**
  * @}
  */


/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup TAMP_LL_Exported_Functions LL TAMP Functions
  * @{
  */

/** @defgroup TAMP_LL_EF_Tamper Tamper
  * @{
  */

/**
  * @brief  Enable TAMPx input detection.
  * @rmtoll
  *  TAMP_CR1       TAMPxE        LL_TAMP_Enable
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_Enable(uint32_t Tampers)
{
  STM32_SET_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Clear TAMPx input detection.
  * @rmtoll
  *  TAMP_CR1       TAMPxE         LL_TAMP_Disable
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_Disable(uint32_t Tampers)
{
  STM32_CLEAR_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Get the enabled TAMPx.
  * @rmtoll
  *  TAMP_CR1       TAMPxE         LL_TAMP_GetEnabled
  * @param  Tampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER
  * @retval State of the tampers enable.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetEnabled(uint32_t Tampers)
{
  return STM32_READ_BIT(TAMP->CR1, Tampers);
}

/**
  * @brief  Enable TAMPx interrupts.
  * @rmtoll
  *  TAMP_IER       TAMPxIE       LL_TAMP_EnableIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_EnableIT(uint32_t TampersIT)
{
  STM32_SET_BIT(TAMP->IER, TampersIT);
}

/**
  * @brief  Disable TAMPx interrupts.
  * @rmtoll
  *  TAMP_IER       TAMPxIE       LL_TAMP_DisableIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_DisableIT(uint32_t TampersIT)
{
  STM32_CLEAR_BIT(TAMP->IER, TampersIT);
}

/**
  * @brief  Get the enabled TAMPx interrupts.
  * @rmtoll
  *  TAMP_IER       TAMPxIE        LL_TAMP_IsEnabledIT
  * @param  TampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_IT
  * @retval State of the tamper interrupt enable (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledIT(uint32_t TampersIT)
{
  return ((STM32_READ_BIT(TAMP->IER, TampersIT) == (TampersIT)) ? 1UL : 0UL);

}

/**
  * @brief  Enable Tamper mask flag.
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_EnableMask
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  * @note Associated Tamper IT must not be enabled when the tamper mask is set.
  */
__STATIC_INLINE void LL_TAMP_EnableMask(uint32_t Mask)
{
  STM32_SET_BIT(TAMP->CR2, Mask);
}

/**
  * @brief  Disable Tamper mask flag.
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_DisableMask
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  */
__STATIC_INLINE void LL_TAMP_DisableMask(uint32_t Mask)
{
  STM32_CLEAR_BIT(TAMP->CR2, Mask);
}

/**
  * @brief  Get the enabled TAMPx mask flags.
  * @rmtoll
  *  TAMP_CR2       TAMPxMSK       LL_TAMP_GetMasked
  * @param  Mask
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_MASK
  * @retval State of the tampers mask flag enable.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetMasked(uint32_t Mask)
{
  return STM32_READ_BIT(TAMP->CR2, (Mask & LL_TAMP_MASK_TAMPER_ALL));
}

/**
  * @brief  Enable TAMPx potential mode.
  * @rmtoll
  *  TAMP_CR2       TAMPxPOM     LL_TAMP_EnablePotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  * @note   In potential mode, the backup registers and device secrets can be blocked instead of erased.
  *         See TAMP interconnection table for more information.
  */
__STATIC_INLINE void LL_TAMP_EnablePotentialMode(uint32_t Tamper)
{
  STM32_SET_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Disable TAMPx potential mode.
  * @rmtoll
  *  TAMP_CR2       TAMPxPOM     LL_TAMP_DisablePotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  */
__STATIC_INLINE void LL_TAMP_DisablePotentialMode(uint32_t Tamper)
{
  STM32_CLEAR_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Check if the TAMPx potential mode is enabled or disabled.
  * @rmtoll
  *  TAMP_CR2       TAMPxPOM     LL_TAMP_IsEnabledPotentialMode
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_NOERASE
  * @retval State of TAMPx potential mode (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledPotentialMode(uint32_t Tamper)
{
  return ((STM32_READ_BIT(TAMP->CR2, Tamper) == (Tamper)) ? 1UL : 0UL);
}

/**
  * @brief Configure global tamper parameters.
  * @rmtoll
  *  TAMP_FLTCR     TAMPPUDIS    LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPPRCH     LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPFREQ     LL_TAMP_SetConfig \n
  *  TAMP_FLTCR     TAMPFLT      LL_TAMP_SetConfig
  * @param Pullup pull-up (precharge of TAMP pins) can be one of the following values:
  *        @arg @ref LL_TAMP_PULL_UP_ENABLE
  *        @arg @ref LL_TAMP_PULL_UP_DISABLE
  * @param Precharge time duration of the precharge can be one of the following values:
  *        @arg @ref LL_TAMP_DURATION_1RTCCLK
  *        @arg @ref LL_TAMP_DURATION_2RTCCLK
  *        @arg @ref LL_TAMP_DURATION_4RTCCLK
  *        @arg @ref LL_TAMP_DURATION_8RTCCLK
  * @param FilterCounter filter counter, can be one of the following values:
  *        @arg @ref LL_TAMP_FILTER_DISABLE
  *        @arg @ref LL_TAMP_FILTER_2SAMPLES
  *        @arg @ref LL_TAMP_FILTER_4SAMPLES
  *        @arg @ref LL_TAMP_FILTER_8SAMPLES
  * @param SampleFrequency sample frequency, can be one of the following values:
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *        @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE void LL_TAMP_SetConfig(uint32_t Pullup, uint32_t Precharge, uint32_t FilterCounter,
                                       uint32_t SampleFrequency)
{
  STM32_WRITE_REG(TAMP->FLTCR,  Pullup | Precharge | FilterCounter | SampleFrequency);
}

/**
  * @brief Retrieve the global tamper parameters configuration.
  * @rmtoll
  *  TAMP_FLTCR     TAMPPUDIS    LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPPRCH     LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPFREQ     LL_TAMP_GetConfig \n
  *  TAMP_FLTCR     TAMPFLT      LL_TAMP_GetConfig
  * @retval Combined values of the pull-up precharge, precharge duration, sample frequency and filter
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfig(void)
{
  return STM32_READ_REG(TAMP->FLTCR);
}

/**
  * @brief Configure one or multiple tampers.
  * @rmtoll
  *  TAMP_CR2     TAMPxTRG    LL_TAMP_SetConfigTampers \n
  *  TAMP_CR2     TAMPxMSK    LL_TAMP_SetConfigTampers \n
  *  TAMP_CR2     TAMPxPOM    LL_TAMP_SetConfigTampers
  * @param Tampers
  *        tampers can be one of the group values @ref TAMP_LL_EC_TAMPER
  * @param Trigger trigger mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ACTIVELEVEL_DEACTIVATE_ALL
  *        @arg @ref LL_TAMP_ACTIVELEVEL_TAMP
  * @param EraseSecrets tamper mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ERASE_ACTIVATE_ALL
  *        @arg @ref LL_TAMP_NOERASE_TAMPER
  * @param Masked tamper masked, can be one of the following values:
  *        @arg @ref LL_TAMP_MASK_NONE
  *        @arg @ref LL_TAMP_MASK_TAMPER
  */
__STATIC_INLINE void LL_TAMP_SetConfigTampers(uint32_t Tampers, uint32_t Trigger, uint32_t EraseSecrets,
                                              uint32_t Masked)
{
  uint32_t temp1 = ((Tampers << TAMP_CR2_TAMP1TRG_Pos) | (Tampers << TAMP_CR2_TAMP1POM_Pos)
                    | ((Tampers << TAMP_CR2_TAMP1MSK_Pos) & LL_TAMP_MASK_TAMPER_ALL)) & (TAMP_CR2_CFG_MSK);
  uint32_t temp2 = (Tampers * (Trigger | Masked | EraseSecrets)) & (TAMP_CR2_CFG_MSK);
  STM32_MODIFY_REG(TAMP->CR2, temp1, temp2);
}

/**
  * @brief Retrieve one configuration tamper.
  * @rmtoll
  *  TAMP_CR2     TAMPxTRG    LL_TAMP_GetConfigTampers \n
  *  TAMP_CR2     TAMPxMSK    LL_TAMP_GetConfigTampers \n
  *  TAMP_CR2     TAMPxPOM    LL_TAMP_GetConfigTampers
  * @param Tampers
  *        tampers can be one of the group values @ref TAMP_LL_EC_TAMPER
  * @retval Combined values of the tamper masked, mode and trigger mode.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfigTampers(uint32_t Tampers)
{
  return STM32_READ_BIT(TAMP->CR2, ((Tampers << TAMP_CR2_TAMP1TRG_Pos) | (Tampers << TAMP_CR2_TAMP1POM_Pos)
                                    | (Tampers << TAMP_CR2_TAMP1MSK_Pos)) & TAMP_CR2_CFG_MSK);
}

/**
  * @brief  Enable TAMPx pull-up (Precharge TAMPx pins before sampling).
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_EnablePullUp
  */
__STATIC_INLINE void LL_TAMP_EnablePullUp(void)
{
  STM32_CLEAR_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS);
}

/**
  * @brief  Disable TAMPx pull-up (Disable precharge of TAMPx pins).
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_DisablePullUp
  */
__STATIC_INLINE void LL_TAMP_DisablePullUp(void)
{
  STM32_SET_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS);
}

/**
  * @brief  Check if the TAMPx pull-up is enabled or disabled.
  * @rmtoll
  *  TAMP_FLTCR       TAMPPUDIS     LL_TAMP_IsEnabledPullUp
  * @retval State of TAMPx pull-up (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledPullUp(void)
{
  return ((STM32_READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPUDIS) == (TAMP_FLTCR_TAMPPUDIS)) ? 0UL : 1UL);
}

/**
  * @brief  Set TAMPx precharge duration.
  * @rmtoll
  *  TAMP_FLTCR       TAMPPRCH      LL_TAMP_SetPrecharge
  * @param  Duration This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_DURATION_1RTCCLK
  *         @arg @ref LL_TAMP_DURATION_2RTCCLK
  *         @arg @ref LL_TAMP_DURATION_4RTCCLK
  *         @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
__STATIC_INLINE void LL_TAMP_SetPrecharge(uint32_t Duration)
{
  STM32_MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPPRCH, Duration);
}

/**
  * @brief  Get TAMPx precharge duration.
  * @rmtoll
  *  TAMP_FLTCR       TAMPPRCH      LL_TAMP_GetPrecharge
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_DURATION_1RTCCLK
  *         @arg @ref LL_TAMP_DURATION_2RTCCLK
  *         @arg @ref LL_TAMP_DURATION_4RTCCLK
  *         @arg @ref LL_TAMP_DURATION_8RTCCLK
  */
__STATIC_INLINE uint32_t LL_TAMP_GetPrecharge(void)
{
  return (uint32_t)(STM32_READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPPRCH));
}

/**
  * @brief  Set TAMPx filter count.
  * @rmtoll
  *  TAMP_FLTCR       TAMPFLT       LL_TAMP_SetFilterCount
  * @param  FilterCount This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_FILTER_DISABLE
  *         @arg @ref LL_TAMP_FILTER_2SAMPLES
  *         @arg @ref LL_TAMP_FILTER_4SAMPLES
  *         @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
__STATIC_INLINE void LL_TAMP_SetFilterCount(uint32_t FilterCount)
{
  STM32_MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPFLT, FilterCount);
}

/**
  * @brief  Get TAMPx filter count.
  * @rmtoll
  *  TAMP_FLTCR       TAMPFLT       LL_TAMP_GetFilterCount
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_FILTER_DISABLE
  *         @arg @ref LL_TAMP_FILTER_2SAMPLES
  *         @arg @ref LL_TAMP_FILTER_4SAMPLES
  *         @arg @ref LL_TAMP_FILTER_8SAMPLES
  */
__STATIC_INLINE uint32_t LL_TAMP_GetFilterCount(void)
{
  return (uint32_t)(STM32_READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPFLT));
}

/**
  * @brief  Set Tamper sampling frequency.
  * @rmtoll
  *  TAMP_FLTCR       TAMPFREQ      LL_TAMP_SetSamplingFreq
  * @param  SamplingFreq This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE void LL_TAMP_SetSamplingFreq(uint32_t SamplingFreq)
{
  STM32_MODIFY_REG(TAMP->FLTCR, TAMP_FLTCR_TAMPFREQ, SamplingFreq);
}

/**
  * @brief  Get Tamper sampling frequency.
  * @rmtoll
  *  TAMP_FLTCR       TAMPFREQ      LL_TAMP_GetSamplingFreq
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_32768
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_16384
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_8192
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_4096
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_2048
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_1024
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_512
  *         @arg @ref LL_TAMP_SAMPLFREQDIV_256
  */
__STATIC_INLINE uint32_t LL_TAMP_GetSamplingFreq(void)
{
  return (uint32_t)(STM32_READ_BIT(TAMP->FLTCR, TAMP_FLTCR_TAMPFREQ));
}

/**
  * @brief  Enable Active level for Tamper input.
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG       LL_TAMP_EnableActiveLevel
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  */
__STATIC_INLINE void LL_TAMP_EnableActiveLevel(uint32_t Tamper)
{
  STM32_SET_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Disable Active level for Tamper input.
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG      LL_TAMP_DisableActiveLevel
  * @param  Tamper
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  */
__STATIC_INLINE void LL_TAMP_DisableActiveLevel(uint32_t Tamper)
{
  STM32_CLEAR_BIT(TAMP->CR2, Tamper);
}

/**
  * @brief  Check if the TAMPx active level is enabled or disabled.
  * @rmtoll
  *  TAMP_CR2       TAMPxTRG     LL_TAMP_IsEnabledActiveLevel
  * @param  Tamper
  *         This parameter can be one of the group values @ref TAMP_LL_EC_TAMPER_ACTIVELEVEL
  * @retval State of TAMPx Active level (1 enabled / 0 disabled).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledActiveLevel(uint32_t Tamper)
{
  return ((STM32_READ_BIT(TAMP->CR2, Tamper) == (Tamper)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Internal_Tamper Internal Tamper
  * @{
  */

/**
  * @brief Configure one or multiple internal tampers.
  * @rmtoll
  *  TAMP_CR3     ITAMPxPOM        LL_TAMP_SetConfigInternalTampers
  * @param InternalTampers
  *        This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @param EraseSecrets tamper mode, can be one of the following values:
  *        @arg @ref LL_TAMP_ITAMP_ERASE_ACTIVE_ALL
  *        @arg @ref LL_TAMP_ITAMP_NOERASE_TAMPER
  */
__STATIC_INLINE void LL_TAMP_SetConfigInternalTampers(uint32_t InternalTampers, uint32_t EraseSecrets)
{
  uint32_t temp = InternalTampers >> LL_POSITION_FIRST_ITAMP;
  STM32_MODIFY_REG(TAMP->CR3, temp, temp * EraseSecrets);
}

/**
  * @brief Retrieve configuration for one internal tamper.
  * @rmtoll
  *  TAMP_CR3     ITAMPxPOM        LL_TAMP_GetConfigInternalTampers
  * @param InternalTampers
  *        This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @retval Value of the selected internal tamper no-erase mode.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetConfigInternalTampers(uint32_t InternalTampers)
{
  uint32_t temp = InternalTampers >> LL_POSITION_OFFSET_REG_ITAMP;
  return STM32_READ_BIT(TAMP->CR3, temp);
}

/**
  * @brief  Enable ITAMPx input detection.
  * @rmtoll
  *  TAMP_CR1       ITAMPxE        LL_TAMP_ITAMP_Enable
  * @param  InternalTampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ITAMP_Enable(uint32_t InternalTampers)
{
  STM32_SET_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Disable ITAMPx input detection.
  * @rmtoll
  *  TAMP_CR1       ITAMPxE         LL_TAMP_ITAMP_Disable
  * @param  InternalTampers
  *          This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ITAMP_Disable(uint32_t InternalTampers)
{
  STM32_CLEAR_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Get the enabled ITAMPx.
  * @rmtoll
  *  TAMP_CR1       ITAMPxE         LL_TAMP_ITAMP_GetEnabled
  * @param  InternalTampers
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ITAMP_GetEnabled(uint32_t InternalTampers)
{
  return STM32_READ_BIT(TAMP->CR1, InternalTampers);
}

/**
  * @brief  Enable ITAMPx input detection interrupts.
  * @rmtoll
  *  TAMP_IER       ITAMPxE        LL_TAMP_ITAMP_EnableIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_ITAMP_EnableIT(uint32_t InternalTampersIT)
{
  STM32_SET_BIT(TAMP->IER, InternalTampersIT);
}

/**
  * @brief  Clear ITAMPx input detection interrupts.
  * @rmtoll
  *  TAMP_IER       ITAMPxE         LL_TAMP_ITAMP_DisableIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  */
__STATIC_INLINE void LL_TAMP_ITAMP_DisableIT(uint32_t InternalTampersIT)
{
  STM32_CLEAR_BIT(TAMP->IER, InternalTampersIT);
}

/**
  * @brief  Get the enabled ITAMPx interrupts.
  * @rmtoll
  *  TAMP_IER       ITAMPxE         LL_TAMP_ITAMP_IsEnabledIT
  * @param  InternalTampersIT
  *         This parameter can be a combination of the group values @ref TAMP_LL_EC_INTERNAL_TAMPER_IT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ITAMP_IsEnabledIT(uint32_t InternalTampersIT)
{
  return ((STM32_READ_BIT(TAMP->IER, InternalTampersIT) == (InternalTampersIT)) ? 1UL : 0UL);
}

/**
  * @}
  */
/** @defgroup TAMP_LL_EF_Active_Tamper Active Tamper
  * @{
  */

/**
  * @brief  Enable tamper active mode.
  * @rmtoll
  *  TAMP_ATCR1     TAMPxAM       LL_TAMP_ATAMP_EnableActiveMode
  * @param Tampers to configure as active.
  *                This parameter can be a combination of @arg @ref TAMP_LL_EC_ACTIVE_MODE
  */
__STATIC_INLINE void LL_TAMP_ATAMP_EnableActiveMode(uint32_t Tampers)
{
  STM32_SET_BIT(TAMP->ATCR1, Tampers);
}

/**
  * @brief  Disable tamper active mode.
  * @rmtoll
  *  TAMP_ATCR1     TAMPxAM       LL_TAMP_ATAMP_DisableActiveMode
  * @param Tampers to configure as active.
  *                This parameter can be a combination of @arg @ref TAMP_LL_EC_ACTIVE_MODE
  */
__STATIC_INLINE void LL_TAMP_ATAMP_DisableActiveMode(uint32_t Tampers)
{
  STM32_CLEAR_BIT(TAMP->ATCR1, Tampers);
}

/**
  * @brief  Retrieve the active tampers configuration.
  * @rmtoll
  *  TAMP_ATCR1     TAMPxM       LL_TAMP_ATAMP_GetActiveMode
  * @retval Combined values of the active tampers.
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetActiveMode(void)
{
  return STM32_READ_BIT(TAMP->ATCR1, LL_TAMP_ATAMP_TAMPAM_ALL);
}

/**
  * @brief  Configure active tampers.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_SetConfig \n
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_SetConfig \n
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_SetConfig \n
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_SetConfig
  * @param  Filter Active tamper filtering state.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_ATAMP_FILTERING_DISABLE
  *         @arg @ref LL_TAMP_ATAMP_FILTERING_ENABLE
  * @param  OutputPeriod Active tamper output change period.
  *         This parameter can be a value from 0 to 7.
  * @param  Shared Active tamper output sharing state.
  *         This parameter can be one of the following values:
  *         @arg @ref LL_TAMP_ATAMP_SHARING_DISABLE
  *         @arg @ref LL_TAMP_ATAMP_SHARING_ENABLE
  * @param  Prescaler Active tamper asynchronous prescaler clock.
  *         This parameter can be a value of the group @ref TAMP_LL_EC_ACTIVE_ASYNC_PRESCALER.
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetConfig(uint32_t Filter, uint32_t OutputPeriod, uint32_t Shared,
                                             uint32_t Prescaler)
{
  STM32_MODIFY_REG(TAMP->ATCR1, TAMP_ATCR1_FLTEN | TAMP_ATCR1_ATPER | TAMP_ATCR1_ATCKSEL | TAMP_ATCR1_ATOSHARE,
                   Filter | (OutputPeriod << TAMP_ATCR1_ATPER_Pos) | Shared | Prescaler);
}

/**
  * @brief  Retrieve the active tampers configuration.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_GetConfig \n
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_GetConfig \n
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_GetConfig \n
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_GetConfig
  * @retval Combined values of the filter, sharing, prescaler and output period
  * of the active tampers.
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetConfig(void)
{
  return STM32_READ_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN | TAMP_ATCR1_ATPER | TAMP_ATCR1_ATCKSEL | TAMP_ATCR1_ATOSHARE);
}

/**
  * @brief  Enable active tamper filter.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_EnableFilter
  */
__STATIC_INLINE void LL_TAMP_ATAMP_EnableFilter(void)
{
  STM32_SET_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN);
}

/**
  * @brief  Disable active tamper filter.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN         LL_TAMP_ATAMP_DisableFilter
  */
__STATIC_INLINE void LL_TAMP_ATAMP_DisableFilter(void)
{
  STM32_CLEAR_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN);
}

/**
  * @brief Check if active tamper filter is enabled.
  * @rmtoll
  *  TAMP_ATCR1     FLTEN      LL_TAMP_ATAMP_IsEnabledFilter
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_IsEnabledFilter(void)
{
  return ((STM32_READ_BIT(TAMP->ATCR1, TAMP_ATCR1_FLTEN) == (TAMP_ATCR1_FLTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set Active tamper output change period.
  * @rmtoll
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_SetOutputChangePeriod
  * @param  ActiveOutputChangePeriod This parameter can be a value from 0 to 7
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetOutputChangePeriod(uint32_t ActiveOutputChangePeriod)
{
  STM32_MODIFY_REG(TAMP->ATCR1, TAMP_ATCR1_ATPER, (ActiveOutputChangePeriod << TAMP_ATCR1_ATPER_Pos));
}

/**
  * @brief  Get Active tamper output change period.
  * @rmtoll
  *  TAMP_ATCR1     ATPER         LL_TAMP_ATAMP_GetOutputChangePeriod
  * @retval Output change period. This parameter can be a value from 0 to 7.
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetOutputChangePeriod(void)
{
  return (STM32_READ_BIT(TAMP->ATCR1, TAMP_ATCR1_ATPER) >> TAMP_ATCR1_ATPER_Pos);
}

/**
  * @brief  Set Active tamper asynchronous prescaler clock selection.
  * @rmtoll
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_SetAsyncPrescaler
  * @param  ActiveAsynvPrescaler Specifies the Active Tamper asynchronous Prescaler clock.
            This parameter can be a value of the group @ref TAMP_LL_EC_ACTIVE_ASYNC_PRESCALER
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetAsyncPrescaler(uint32_t ActiveAsynvPrescaler)
{
  STM32_MODIFY_REG(TAMP->ATCR1, TAMP_ATCR1_ATCKSEL, ActiveAsynvPrescaler);
}

/**
  * @brief  Get Active tamper asynchronous prescaler clock selection.
  * @rmtoll
  *  TAMP_ATCR1     ATCKSEL       LL_TAMP_ATAMP_GetAsyncPrescaler
  * @retval One of @ref TAMP_LL_EC_ACTIVE_ASYNC_PRESCALER
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetAsyncPrescaler(void)
{
  return (STM32_READ_BIT(TAMP->ATCR1, TAMP_ATCR1_ATCKSEL));
}

/**
  * @brief  Enable active tamper output sharing.
  * @rmtoll
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_EnableOutputSharing
  */
__STATIC_INLINE void LL_TAMP_ATAMP_EnableOutputSharing(void)
{
  STM32_SET_BIT(TAMP->ATCR1, TAMP_ATCR1_ATOSHARE);
}

/**
  * @brief  Disable active tamper output sharing.
  * @rmtoll
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_DisableOutputSharing
  */
__STATIC_INLINE void LL_TAMP_ATAMP_DisableOutputSharing(void)
{
  STM32_CLEAR_BIT(TAMP->ATCR1, TAMP_ATCR1_ATOSHARE);
}

/**
  * @brief Check if active tamper output sharing is enabled.
  * @rmtoll
  *  TAMP_ATCR1     ATOSHARE      LL_TAMP_ATAMP_IsEnabledOutputSharing
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_IsEnabledOutputSharing(void)
{
  return ((STM32_READ_BIT(TAMP->ATCR1, TAMP_ATCR1_ATOSHARE) == (TAMP_ATCR1_ATOSHARE)) ? 1UL : 0UL);
}

/**
  * @brief  Set Active tamper shared output.
  * @rmtoll
  *  TAMP_ATCR2     ATOSELx       LL_TAMP_ATAMP_SetSharedOutputs
  * @param  OutputSelection Specifies all the output selection of the Active Tamper.
  *         This parameter is a one of the group values @ref TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION
  * @param  Positions Specifies all the bits that need to be changed on the register
  *          ATCR2
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetSharedOutputs(uint32_t Positions, uint32_t OutputSelection)
{
  STM32_MODIFY_REG(TAMP->ATCR2, Positions, OutputSelection);
}

/**
  * @brief  Set Active tamper shared output selection.
  * @rmtoll
  *  TAMP_ATCR2     ATOSELx       LL_TAMP_ATAMP_SetSharedOutputSelection
  * @param  OutputSelection Specifies all the output selection of the Active Tamper.
  *         This parameter is a one of the group values @ref TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION
  */
__STATIC_INLINE void LL_TAMP_ATAMP_SetSharedOutputSelection(uint32_t OutputSelection)
{
  STM32_MODIFY_REG(TAMP->ATCR2, TAMP_ATCR2_ATOSEL_MSK, OutputSelection);
}

/**
  * @brief  Get Active tamper shared output selection.
  * @rmtoll
  *  TAMP_ATCR2     ATOSELx       LL_TAMP_ATAMP_GetSharedOutputSelection
  * @retval A combination of @arg @ref TAMP_LL_EC_ACTIVE_OUTPUT_SELECTION
  */
__STATIC_INLINE uint32_t LL_TAMP_ATAMP_GetSharedOutputSelection(void)
{
  return STM32_READ_REG(TAMP->ATCR2);
}

/**
  * @brief  Write active tamper seed.
  * @rmtoll
  *  TAMP_ATSEEDR   SEED          LL_TAMP_ATAMP_WriteSeed
  * @param  Seed
  */
__STATIC_INLINE void LL_TAMP_ATAMP_WriteSeed(uint32_t Seed)
{
  STM32_WRITE_REG(TAMP->ATSEEDR, Seed);
}

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Read pseudo-random generator value.
  * @rmtoll
  *  TAMP_ATOR   PRNG          LL_TAMP_ReadPRNG
  * @retval Pseudo-random generator value.
  * @note: Because of potential inconsistencies due to synchronization delays, PRNG must be read at least twice.
  */
__STATIC_INLINE uint32_t LL_TAMP_ReadPRNG(void)
{
  return (STM32_READ_BIT(TAMP->ATOR, TAMP_ATOR_PRNG));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get active tamper initialization status flag.
  * @rmtoll
  *  TAMP_ATOR      INITS         LL_TAMP_IsActiveFlag_ATAMP_INITS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ATAMP_INITS(void)
{
  return ((STM32_READ_BIT(TAMP->ATOR, TAMP_ATOR_INITS) == (TAMP_ATOR_INITS)) ? 1UL : 0UL);
}

/**
  * @brief  Get active tamper seed running status flag.
  * @rmtoll
  *  TAMP_ATOR      SEEDF         LL_TAMP_IsActiveFlag_ATAMP_SEEDF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ATAMP_SEEDF(void)
{
  return ((STM32_READ_BIT(TAMP->ATOR, TAMP_ATOR_SEEDF) == (TAMP_ATOR_SEEDF)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Backup_Registers Backup_Registers
  * @{
  */

/**
  * @brief  Writes a data in a specified Backup data register.
  * @rmtoll
  *  TAMP_BKPxR        BKP           LL_TAMP_BKP_SetRegister
  * @param  BackupRegister This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @param  Data Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE void LL_TAMP_BKP_SetRegister(uint32_t BackupRegister, uint32_t Data)
{
  uint32_t tmp;

  tmp = (uint32_t)(&(TAMP->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Write the specified register */
  *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * @brief  Reads data from the specified TAMP Backup data Register.
  * @rmtoll
  *  TAMP_BKPxR        BKP           LL_TAMP_BKP_GetRegister
  * @param  BackupRegister This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @retval Value between Min_Data=0x00 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_TAMP_BKP_GetRegister(uint32_t BackupRegister)
{
  uint32_t tmp;

  tmp = (uint32_t)(&(TAMP->BKP0R));
  tmp += (BackupRegister * 4U);

  /* Read the specified register */
  return (*(__IO uint32_t *)tmp);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get tampers interrupt flags.
  * @rmtoll
  *  TAMP_SR          TAMPx       LL_TAMP_IsActiveFlag_TAMP
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_TAMP(uint32_t Tampers)
{
  return ((STM32_READ_BIT(TAMP->SR, Tampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get internal tampers interrupt flags.
  * @rmtoll
  *  TAMP_SR          ITAMPx       LL_TAMP_IsActiveFlag_ITAMP
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ITAMP(uint32_t InternalTampers)
{
  return ((STM32_READ_BIT(TAMP->SR, InternalTampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_MISR          TAMPxMF       LL_TAMP_IsActiveFlag_TAMPM
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_TAMPM(uint32_t Tampers)
{
  return ((STM32_READ_BIT(TAMP->MISR, Tampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Get internal tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_MISR          ITAMPxMF       LL_TAMP_IsActiveFlag_ITAMPM
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsActiveFlag_ITAMPM(uint32_t InternalTampers)
{
  return ((STM32_READ_BIT(TAMP->MISR, InternalTampers) != 0U) ? 1UL : 0UL);
}

/**
  * @brief  Clear tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_SCR          CTAMPxF       LL_TAMP_ClearFlag_TAMP
  * @param Tampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_TAMPER
  */
__STATIC_INLINE void LL_TAMP_ClearFlag_TAMP(uint32_t Tampers)
{
  STM32_WRITE_REG(TAMP->SCR, Tampers);
}

/**
  * @brief  Clear internal tampers interrupt masked flags.
  * @rmtoll
  *  TAMP_SCR          CITAMPxF       LL_TAMP_ClearFlag_ITAMP
  * @param InternalTampers This parameter can be a combination of the following values:
  *        @arg @ref TAMP_LL_EC_INTERNAL
  */
__STATIC_INLINE void LL_TAMP_ClearFlag_ITAMP(uint32_t InternalTampers)
{
  STM32_WRITE_REG(TAMP->SCR, InternalTampers);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Device_Secret_Management Device_Secret Management
  * @{
  */

/**
  * @brief Block access to the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_BlockDeviceSecretsAccess
  */
__STATIC_INLINE void LL_TAMP_BlockDeviceSecretsAccess(void)
{
  STM32_SET_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK);
}

/**
  * @brief Unblock access to the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_UnblockDeviceSecretsAccess
  */
__STATIC_INLINE void LL_TAMP_UnblockDeviceSecretsAccess(void)
{
  STM32_CLEAR_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK);
}

/**
  * @brief Check if the access to the backup registers and device secrets is blocked.
  * @rmtoll
  *  TAMP_CR2      BKBLOCK    LL_TAMP_IsBlockedDeviceSecretsAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsBlockedDeviceSecretsAccess(void)
{
  return ((STM32_READ_BIT(TAMP->CR2, TAMP_CR2_BKBLOCK) == (TAMP_CR2_BKBLOCK)) ? 1UL : 0UL);
}

/**
  * @brief Erase the backup registers and device secrets.
  * @rmtoll
  *  TAMP_CR2      BKERASE    LL_TAMP_EraseDeviceSecrets
  */
__STATIC_INLINE void LL_TAMP_EraseDeviceSecrets(void)
{
  STM32_SET_BIT(TAMP->CR2, TAMP_CR2_BKERASE);
}

/**
  * @brief Enable protection by TAMP peripheral of the device secrets.
  * @rmtoll
  *  TAMP_RPCFGR      RPCFGx    LL_TAMP_EnableResourceProtection
  * @param Resources can be a combination of the group values @ref TAMP_LL_EC_RESOURCE_PROTECTION
  */
__STATIC_INLINE void LL_TAMP_EnableResourceProtection(uint32_t Resources)
{
  STM32_SET_BIT(TAMP->RPCFGR, Resources);
}

/**
  * @brief Disable protection by TAMP peripheral of the device secrets.
  * @rmtoll
  *  TAMP_RPCFGR      RPCFGx    LL_TAMP_DisableResourceProtection
  * @param Resources can be a combination of the group values @ref TAMP_LL_EC_RESOURCE_PROTECTION
  */
__STATIC_INLINE void LL_TAMP_DisableResourceProtection(uint32_t Resources)
{
  STM32_CLEAR_BIT(TAMP->RPCFGR, Resources);
}

/**
  * @brief Check if the protection by TAMP peripheral of the device secret is enabled.
  * @rmtoll
  *  TAMP_RPCFGR      RPCFGx    LL_TAMP_IsEnabledResourceProtection
  * @param Resources can be a combination of the group values @ref TAMP_LL_EC_RESOURCE_PROTECTION
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledResourceProtection(uint32_t Resources)
{
  return ((STM32_READ_BIT(TAMP->RPCFGR, Resources) == (Resources)) ? 1UL : 0UL);
}

/**
  * @brief  Blocks access to the eight first backup registers corresponding to the hardware boot key.
  * @note   If TZEN is set to 1, the hardware boot key can be locked only through secure APB access.
  *         If TZEN is set to 0, it can also be locked through nonsecure APB access.
  * @rmtoll
  *  TAMP_SECCFGR      BHKLOCK    LL_TAMP_LockBootHardwareKey
  */
__STATIC_INLINE void LL_TAMP_LockBootHardwareKey(void)
{
  STM32_SET_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BHKLOCK);
}

/**
  * @brief Check if the eight first backup registers corresponding to the hardware boot key are blocked.
  * @rmtoll
  *  TAMP_SECCFGR      BHKLOCK    LL_TAMP_IsLockedBootHardwareKey
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsLockedBootHardwareKey(void)
{
  return ((STM32_READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BHKLOCK) == (TAMP_SECCFGR_BHKLOCK)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Monotonic_Counter Monotonic Counter 1
  * @{
  */

/**
  * @brief  Increment Monotonic counter 1.
  * @rmtoll
  *  TAMP_COUNT1R         COUNT        LL_TAMP_IncrementMonotonicCounter1
  */
__STATIC_INLINE void LL_TAMP_IncrementMonotonicCounter1(void)
{
  STM32_WRITE_REG(TAMP->COUNT1R, 0U);
}

/**
  * @brief  Increment Monotonic counter 1.
  * @rmtoll
  *  TAMP_COUNT1R         COUNT        LL_TAMP_GetMonotonicCounter1
  * @retval Monotonic counter value.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetMonotonicCounter1(void)
{
  return STM32_READ_REG(TAMP->COUNT1R);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Remap Tamp remap
  * @{
  */
/**
  * @brief  Enable remap of TAMP INx / OUTx on different pin.
  * @rmtoll TAMP_OR           IN1_RMP       LL_TAMP_EnableRemap\n
  * @rmtoll TAMP_OR           IN2_RMP       LL_TAMP_EnableRemap\n
  * @rmtoll TAMP_OR           OUT1_RMP      LL_TAMP_EnableRemap\n
  * @rmtoll TAMP_OR           OUT2_RMP      LL_TAMP_EnableRemap
  * @param  tamp_remap This parameter can be a combination of the following values:
  *         @arg @ref LL_TAMP_RMP_TAMP_IN1_PA0_TO_PB9
  *         @arg @ref LL_TAMP_RMP_TAMP_IN2_PA1_TO_PC13
  *         @arg @ref LL_TAMP_RMP_TAMP_OUT1_PA2_TO_PC13
  *         @arg @ref LL_TAMP_RMP_TAMP_OUT2_PB9_TO_PE3   (*)
  * @note   (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_TAMP_EnableRemap(uint32_t tamp_remap)
{
  STM32_SET_BIT(TAMP->OR, tamp_remap);
}

/**
  * @brief  Disable remap of TAMP INx / OUTx on different pin.
  * @rmtoll TAMP_OR           IN1_RMP       LL_TAMP_DisableRemap\n
  * @rmtoll TAMP_OR           IN2_RMP       LL_TAMP_DisableRemap\n
  * @rmtoll TAMP_OR           OUT1_RMP      LL_TAMP_DisableRemap\n
  * @rmtoll TAMP_OR           OUT2_RMP      LL_TAMP_DisableRemap
  * @param  tamp_remap This parameter can be a combination of the following values:
  *         @arg @ref LL_TAMP_RMP_TAMP_IN1_PA0_TO_PB9
  *         @arg @ref LL_TAMP_RMP_TAMP_IN2_PA1_TO_PC13
  *         @arg @ref LL_TAMP_RMP_TAMP_OUT1_PA2_TO_PC13
  *         @arg @ref LL_TAMP_RMP_TAMP_OUT2_PB9_TO_PE3   (*)
  * @note   (*) value not defined in all devices
  * @retval None
  */
__STATIC_INLINE void LL_TAMP_DisableRemap(uint32_t tamp_remap)
{
  STM32_CLEAR_BIT(TAMP->OR, tamp_remap);
}

/**
  * @brief  Check if remap TAMP INx / OUTx is enabled or disabled.
  * @rmtoll TAMP_OR           IN1_RMP       LL_TAMP_IsEnabledRemap\n
  * @rmtoll TAMP_OR           IN2_RMP       LL_TAMP_IsEnabledRemap\n
  * @rmtoll TAMP_OR           OUT1_RMP      LL_TAMP_IsEnabledRemap\n
  * @rmtoll TAMP_OR           OUT2_RMP      LL_TAMP_IsEnabledRemap
  * @param  tamp_remap This parameter can be a combination of the following values:
  *         @arg @ref LL_TAMP_RMP_TAMP_IN1_PA0_TO_PB9
  *         @arg @ref LL_TAMP_RMP_TAMP_IN2_PA1_TO_PC13
  *         @arg @ref LL_TAMP_RMP_TAMP_OUT1_PA2_TO_PC13
  *         @arg @ref LL_TAMP_RMP_TAMP_OUT2_PB9_TO_PE3   (*)
  * @note   (*) value not defined in all devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_TAMP_IsEnabledRemap(uint32_t tamp_remap)
{
  return ((STM32_READ_BIT(TAMP->OR, tamp_remap) == tamp_remap) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Security_Services Security Services
  * @{
  */

#if defined (CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set TAMP item(s) security configuration.
  * @rmtoll
  *  SECCFGR           CNT1SEC            LL_TAMP_SetSecAttr \n
  *  SECCFGR           TAMPSEC            LL_TAMP_SetSecAttr
  * @param item This parameter can be one or a combination of the following values:
  *        @arg @ref LL_TAMP_SEC_ITEM_CNT1SEC
  *        @arg @ref LL_TAMP_SEC_ITEM_TAMPSEC
  * @param sec_attr This parameter can be one of the following values:
  *        @arg @ref LL_TAMP_ATTR_SEC
  *        @arg @ref LL_TAMP_ATTR_NSEC
  */
__STATIC_INLINE void LL_TAMP_SetSecAttr(uint32_t item, uint32_t sec_attr)
{
  STM32_MODIFY_REG(TAMP->SECCFGR, item, (item & ((~sec_attr) + 1U)));
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get TAMP item security configuration.
  * @rmtoll
  *  SECCFGR           CNT1SEC            LL_TAMP_GetSecAttr \n
  *  SECCFGR           TAMPSEC            LL_TAMP_GetSecAttr
  * @param  item This parameter can be one of the following values:
  *        @arg @ref LL_TAMP_SEC_ITEM_CNT1SEC
  *        @arg @ref LL_TAMP_SEC_ITEM_TAMPSEC
  * @retval Status of bit (1 or 0).
  *         - 1: Secure attribute enabled for the item.
  *         - 0: Non-secure attribute for the item.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetSecAttr(uint32_t item)
{
  return ((STM32_READ_BIT(TAMP->SECCFGR, item) == (item)) ? LL_TAMP_ATTR_SEC : LL_TAMP_ATTR_NSEC);
}

/**
  * @}
  */

/** @defgroup TAMP_LL_EF_Privilege_Services Privilege Services
  * @{
  */

/**
  * @brief  Set privilege attribute configuration.
  * @rmtoll
  *  PRIVCFGR           CNT1PRIV            LL_TAMP_SetPrivAttr \n
  *  PRIVCFGR           TAMPPRIV            LL_TAMP_SetPrivAttr \n
  *  PRIVCFGR           BKPWPRIV            LL_TAMP_SetPrivAttr \n
  *  PRIVCFGR           BKPRWPRIV           LL_TAMP_SetPrivAttr
  * @param item This parameter can be one or a combination of the following values:
  *        @arg @ref LL_TAMP_PRIV_ITEM_CNT1PRIV
  *        @arg @ref LL_TAMP_PRIV_ITEM_TAMPPRIV
  *        @arg @ref LL_TAMP_PRIV_ZONE_BKPWPRIV
  *        @arg @ref LL_TAMP_PRIV_ZONE_BKPRWPRIV
  * @param priv_attr This parameter can be one of the following values:
  *        @arg @ref LL_TAMP_ATTR_PRIV
  *        @arg @ref LL_TAMP_ATTR_NPRIV
  */
__STATIC_INLINE void LL_TAMP_SetPrivAttr(uint32_t item, uint32_t priv_attr)
{
  STM32_MODIFY_REG(TAMP->PRIVCFGR, item, (item & ((~priv_attr) + 1U)));
}

/**
  * @brief  Get privilege attribute configuration.
  * @rmtoll
  *  PRIVCFGR           CNT1PRIV            LL_TAMP_GetPrivAttr \n
  *  PRIVCFGR           TAMPPRIV            LL_TAMP_GetPrivAttr \n
  *  PRIVCFGR           BKPWPRIV            LL_TAMP_GetPrivAttr \n
  *  PRIVCFGR           BKPRWPRIV           LL_TAMP_GetPrivAttr
  * @param  item This parameter can be one of the following values:
  *        @arg @ref LL_TAMP_PRIV_ITEM_CNT1PRIV
  *        @arg @ref LL_TAMP_PRIV_ITEM_TAMPPRIV
  *        @arg @ref LL_TAMP_PRIV_ZONE_BKPWPRIV
  *        @arg @ref LL_TAMP_PRIV_ZONE_BKPRWPRIV
  * @retval Status of bit (1 or 0).
  *         - 1: Privileged attribute enabled for the item.
  *         - 0: Non-privileged attribute for the item.
  */
__STATIC_INLINE uint32_t LL_TAMP_GetPrivAttr(uint32_t item)
{
  return ((STM32_READ_BIT(TAMP->PRIVCFGR, item) == (item)) ? LL_TAMP_ATTR_PRIV : LL_TAMP_ATTR_NPRIV);
}

/**
  * @brief  Set backup register protection boundary start index of Zone 2 and Zone 3.
  * @rmtoll
  *  SECCFGR           BKPRWSEC           LL_TAMP_SetBackupRegProtection \n
  *  SECCFGR           BKPWSEC            LL_TAMP_SetBackupRegProtection
  * @param  start_zone2 This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @param  start_zone3 This parameter can be one of the group values @ref TAMP_LL_EC_BKP
  * @note   If TZEN is set to 1, the zone 1 and zone 2 boundaries can be configured only through secure APB access.
  *         If TZEN is set to 0, both boundaries can also be configured through nonsecure APB access.
  */
__STATIC_INLINE void LL_TAMP_SetBackupRegProtection(uint32_t start_zone2, uint32_t start_zone3)
{
  STM32_MODIFY_REG(TAMP->SECCFGR, (TAMP_SECCFGR_BKPRWSEC_Msk | TAMP_SECCFGR_BKPWSEC_Msk),
                   (start_zone2 << TAMP_SECCFGR_BKPRWSEC_Pos) |
                   (start_zone3 << TAMP_SECCFGR_BKPWSEC_Pos));
}

/**
  * @brief  Get backup register protection boundary start index of Zone 2.
  * @note   Zone 1 : read protection write protection
  * @note   Zone 2 : read non-protection  write protection
  * @note   Zone 3 : read non-protection  write non-protection
  * @rmtoll
  *  TAMP_SECCFGR          BKPRWSEC         LL_TAMP_GetBackupRegStartZone2
  * @retval Start index of backup zone 2
  */
__STATIC_INLINE uint32_t LL_TAMP_GetBackupRegStartZone2(void)
{
  return STM32_READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BKPRWSEC_Msk) >> TAMP_SECCFGR_BKPRWSEC_Pos;
}

/**
  * @brief  Get backup register protection boundary start index of Zone 3.
  * @note   Zone 1 : read protection write protection
  * @note   Zone 2 : read non-protection  write protection
  * @note   Zone 3 : read non-protection  write non-protection
  * @rmtoll
  *  TAMP_SECCFGR          BKPWSEC           LL_TAMP_GetBackupRegStartZone3
  * @retval Start index of backup zone 3
  */
__STATIC_INLINE uint32_t LL_TAMP_GetBackupRegStartZone3(void)
{
  return STM32_READ_BIT(TAMP->SECCFGR, TAMP_SECCFGR_BKPWSEC_Msk) >> TAMP_SECCFGR_BKPWSEC_Pos;
}


/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(TAMP) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_LL_TAMP_H */
