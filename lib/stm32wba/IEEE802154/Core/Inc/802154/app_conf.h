/**
  ******************************************************************************
  * @file    app_conf.h
  * @author  MCD Application Team
  * @brief   Application configuration file for STM32WPAN Middleware.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_CONF_H
#define APP_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "hw_if.h"
#include "utilities_conf.h"

/**
 * PHY preferences
 */
#define CFG_PHY_PREF                  (0)
#define CFG_PHY_PREF_TX               (HCI_TX_PHYS_LE_2M_PREF)
#define CFG_PHY_PREF_RX               (HCI_RX_PHYS_LE_2M_PREF)

/******************************************************************************
 * Low Power
 *
 *  When CFG_LPM_LEVEL is set to:
 *   - 0 : Low Power Mode is not activated, RUN mode will be used.
 *   - 1 : Low power active, mode selected with CFG_LPM_STDBY_SUPPORTED
 *   - 2 : In addition log and debug are disabled to reach lowest power figures.
 *
 * When CFG_LPM_STDBY_SUPPORTED is set to:
 *   - 2 : Stop mode 2 is used as low power mode (if supported by target)
 *   - 1 : Standby is used as low power mode.
 *   - 0 : Stop mode 1 is used as low power mode.
 *
 ******************************************************************************/
#define CFG_LPM_LEVEL            (0)
#define CFG_LPM_STDBY_SUPPORTED  (0)

/* Defines time to wake up from standby before radio event to meet timings */
#define CFG_LPM_STDBY_WAKEUP_TIME (1500)

/**
 * Supported requester to the MCU Low Power Manager - can be increased up  to 32
 * It list a bit mapping of all user of the Low Power Manager
 */
typedef enum
{
  CFG_LPM_APP,
  CFG_LPM_LOG,
  CFG_LPM_LL_DEEPSLEEP,
  CFG_LPM_LL_HW_RCO_CLBR,
} CFG_LPM_Id_t;

/*****************************************************************************
- * Logs
- *
- * Applications must call LOG_INFO_APP for logs.
- *
- * For advanced log use cases, see the log_module.h file.
- *****************************************************************************/

/* Configure Log display settings */
#define CFG_LOG_INSERT_COLOR_INSIDE_THE_TRACE       (0U)
#define CFG_LOG_INSERT_TIME_STAMP_INSIDE_THE_TRACE  (0U)
#define CFG_LOG_INSERT_EOL_INSIDE_THE_TRACE         (0U)

#define CFG_LOG_TRACE_FIFO_SIZE     (4096U)
#define CFG_LOG_TRACE_BUF_SIZE      (256U)

/* macro ensuring retrocompatibility with old applications */
#define APP_DBG                     LOG_INFO_APP
#define APP_DBG_MSG                 LOG_INFO_APP

/******************************************************************************
 * Debugger
 *
 *  When CFG_DEBUGGER_LEVEL is set to:
 *   - 0 : No Debugger available, SWD/JTAG pins are disabled.
 *   - 1 : Debugger available in RUN mode only.
 *   - 2 : Debugger available in low power mode.
 *
 ******************************************************************************/
#define CFG_DEBUGGER_LEVEL                  (0)

/******************************************************************************
 * RealTime GPIO debug module configuration
 ******************************************************************************/

#define CFG_RT_DEBUG_GPIO_MODULE            (0)
#define CFG_RT_DEBUG_DTB                    (0)

/******************************************************************************
 * System Clock Manager module configuration
 ******************************************************************************/

#define CFG_SCM_SUPPORTED                   (0)

/******************************************************************************
 * HW RADIO configuration
 ******************************************************************************/
/* Do not modify - must be 1 */
#define USE_RADIO_LOW_ISR                   (1)

/* Do not modify - must be 1 */
#define NEXT_EVENT_SCHEDULING_FROM_ISR      (1)

/* Link Layer uses temperature based calibration (0 --> NO ; 1 --> YES) */
#define USE_TEMPERATURE_BASED_RADIO_CALIBRATION  (0)

#define RADIO_INTR_NUM                      RADIO_IRQn     /* 2.4GHz RADIO global interrupt */
#define RADIO_INTR_PRIO_HIGH                (0)            /* 2.4GHz RADIO interrupt priority when radio is Active */
#define RADIO_INTR_PRIO_LOW                 (5)            /* 2.4GHz RADIO interrupt priority when radio is Not Active - Sleep Timer Only */

#if (USE_RADIO_LOW_ISR == 1)
#define RADIO_SW_LOW_INTR_NUM               HASH_IRQn      /* Selected interrupt vector for 2.4GHz RADIO low ISR */
#define RADIO_SW_LOW_INTR_PRIO              (14)           /* 2.4GHz RADIO low ISR priority */
#endif /* USE_RADIO_LOW_ISR */

/* Link Layer supported number of antennas */
#define RADIO_NUM_OF_ANTENNAS               (4)

#define RCC_INTR_PRIO                       (1)           /* HSERDY and PLL1RDY */

/* RF TX power table ID selection:
 *   0 -> RF TX output level from -20 dBm to +10 dBm
 *   1 -> RF TX output level from -20 dBm to +3 dBm
 *   2 -> RF TX output level at +20 dBm with an external PA
 */
#define CFG_RF_TX_POWER_TABLE_ID            (1)

#define CFG_EXTERNAL_PA_ENABLE              (0)

#define CFG_BLE_AOA_AOD_ENABLE              (0)
#define CFG_RADIO_NUM_OF_ANTENNAS           (8)           /* Link Layer supported number of antennas */

/* Custom LSE sleep clock accuracy to use if both conditions are met:
 * - LSE is selected as Link Layer sleep clock source
 * - the LSE used is different from the default one.
 */
/* Radio sleep clock LSE accuracy configuration */
#define CFG_RADIO_LSE_SLEEP_TIMER_CUSTOM_SCA_RANGE (0x00)

/**
 * User interaction
 * When CFG_LED_SUPPORTED is set, LEDs are activated if requested
 * When CFG_BUTTON_SUPPORTED is set, the push button are activated if requested
 */

#define CFG_LED_SUPPORTED                       (1)
#define CFG_BUTTON_SUPPORTED                    (1)

/**
 * Overwrite some configuration imposed by Low Power level selected.
 */
#if (CFG_LPM_LEVEL > 1)
  #if CFG_LED_SUPPORTED
    #undef  CFG_LED_SUPPORTED
    #define CFG_LED_SUPPORTED      (0)
  #endif /* CFG_LED_SUPPORTED */
#endif /* CFG_LPM_LEVEL */

/**
 * Overwrite some configuration imposed by Low Power level selected.
 */
#if (CFG_LPM_LEVEL > 1)
  #if CFG_LOG_SUPPORTED
    #undef  CFG_LOG_SUPPORTED
    #define CFG_LOG_SUPPORTED       (0)
  #endif /* CFG_LOG_SUPPORTED */
  #if CFG_DEBUGGER_LEVEL
    #undef  CFG_DEBUGGER_LEVEL
    #define CFG_DEBUGGER_LEVEL      (0)
  #endif /* CFG_DEBUGGER_LEVEL */
#endif /* CFG_LPM_LEVEL */

#if (CFG_LPM_STDBY_SUPPORTED != 0) && (CFG_LPM_LEVEL != 0)
  #if CFG_LOG_SUPPORTED
    #undef  CFG_LOG_SUPPORTED
    #define CFG_LOG_SUPPORTED       (0)
  #endif /* CFG_LOG_SUPPORTED */
#endif /* (CFG_LPM_STDBY_SUPPORTED > 0) && (CFG_LPM_LEVEL != 0) */


#endif /*APP_CONF_H */
