/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ll_sys_if.c
  * @author  MCD Application Team
  * @brief   Source file for initiating system
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
/* USER CODE END Header */
#include <zephyr/logging/log.h>
#include "ll_intf.h"
#include "ll_intf_cmn.h"
#include "ll_sys.h"
#include "ll_sys_if.h"
#include "utilities_common.h"
#ifndef __ZEPHYR__
#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)
#include "temp_measurement.h"
#endif /* (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1) */
#endif /*__ZEPHYR__*/
/* Private defines -----------------------------------------------------------*/
/* Radio event scheduling method - must be set at 1 */
#define USE_RADIO_LOW_ISR                   (1)
#define NEXT_EVENT_SCHEDULING_FROM_ISR      (1)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private constants ---------------------------------------------------------*/
/* USER CODE BEGIN PC */

/* USER CODE END PC */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Global variables ----------------------------------------------------------*/

/* USER CODE BEGIN GV */

/* USER CODE END GV */

/* Private functions prototypes-----------------------------------------------*/
static void ll_sys_sleep_clock_source_selection(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

#ifndef __ZEPHYR__
/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  Link Layer background process initialization
  * @param  None
  * @retval None
  */
void ll_sys_bg_process_init(void)
{
  /* Register Link Layer task */
  UTIL_SEQ_RegTask(1U << CFG_TASK_LINK_LAYER, UTIL_SEQ_RFU, ll_sys_bg_process);
}

/**
  * @brief  Link Layer background process next iteration scheduling
  * @param  None
  * @retval None
  */
void ll_sys_schedule_bg_process(void)
{
  UTIL_SEQ_SetTask(1U << CFG_TASK_LINK_LAYER, TASK_PRIO_LINK_LAYER);
}

/**
  * @brief  Link Layer background process next iteration scheduling from ISR
  * @param  None
  * @retval None
  */
void ll_sys_schedule_bg_process_isr(void)
{
  UTIL_SEQ_SetTask(1U << CFG_TASK_LINK_LAYER, TASK_PRIO_LINK_LAYER);
}
#endif

/**
  * @brief  Link Layer configuration phase before application startup.
  * @param  None
  * @retval None
  */
void ll_sys_config_params(void)
{
/* USER CODE BEGIN ll_sys_config_params_0 */

/* USER CODE END ll_sys_config_params_0 */

  /* Configure link layer behavior for low ISR use and next event scheduling method:
   * - SW low ISR is used.
   * - Next event is scheduled from ISR.
   */
  ll_intf_cmn_config_ll_ctx_params(USE_RADIO_LOW_ISR, NEXT_EVENT_SCHEDULING_FROM_ISR);
  /* Apply the selected link layer sleep timer source */
  ll_sys_sleep_clock_source_selection();

/* USER CODE BEGIN ll_sys_config_params_1 */

/* USER CODE END ll_sys_config_params_1 */

#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)
  /* Initialize link layer temperature measurement background task */
  ll_sys_bg_temperature_measurement_init();

  /* Link layer IP uses temperature based calibration instead of periodic one */
  ll_intf_cmn_set_temperature_sensor_state();
#endif /* USE_TEMPERATURE_BASED_RADIO_CALIBRATION */

#ifndef __ZEPHYR__
  /* Link Layer power table */
  ll_intf_cmn_select_tx_power_table(CFG_RF_TX_POWER_TABLE_ID);
#endif  /*__ZEPHYR__*/
/* USER CODE BEGIN ll_sys_config_params_2 */

/* USER CODE END ll_sys_config_params_2 */
}

#ifndef __ZEPHYR__
#if (USE_TEMPERATURE_BASED_RADIO_CALIBRATION == 1)

/**
  * @brief  Link Layer temperature request background process initialization
  * @param  None
  * @retval None
  */
void ll_sys_bg_temperature_measurement_init(void)
{
  /* Register Temperature Measurement task */
  UTIL_SEQ_RegTask(1U << CFG_TASK_TEMP_MEAS, UTIL_SEQ_RFU, TEMPMEAS_RequestTemperatureMeasurement);
}

/**
  * @brief  Request backroud task processing for temperature measurement
  * @param  None
  * @retval None
  */
void ll_sys_bg_temperature_measurement(void)
{
  static uint8_t initial_temperature_acquisition = 0;

  if(initial_temperature_acquisition == 0)
  {
    TEMPMEAS_RequestTemperatureMeasurement();
    initial_temperature_acquisition = 1;
  }
  else
  {
    UTIL_SEQ_SetTask(1U << CFG_TASK_TEMP_MEAS, CFG_SEQ_PRIO_0);
  }
}

#endif /* USE_TEMPERATURE_BASED_RADIO_CALIBRATION */
#endif

void ll_sys_sleep_clock_source_selection(void)
{
  uint16_t freq_value = 0;
  uint32_t linklayer_slp_clk_src = LL_RCC_RADIOSLEEPSOURCE_NONE;

  linklayer_slp_clk_src = LL_RCC_RADIO_GetSleepTimerClockSource();
  switch(linklayer_slp_clk_src)
  {
    case LL_RCC_RADIOSLEEPSOURCE_LSE:
      linklayer_slp_clk_src = RTC_SLPTMR;
      break;

    case LL_RCC_RADIOSLEEPSOURCE_LSI:
      linklayer_slp_clk_src = RCO_SLPTMR;
      break;

    case LL_RCC_RADIOSLEEPSOURCE_HSE_DIV1000:
      linklayer_slp_clk_src = CRYSTAL_OSCILLATOR_SLPTMR;
      break;

    case LL_RCC_RADIOSLEEPSOURCE_NONE:
      /* No Link Layer sleep clock source selected */
      assert_param(0);
      break;
  }
  ll_intf_cmn_le_select_slp_clk_src((uint8_t)linklayer_slp_clk_src, &freq_value);
}


