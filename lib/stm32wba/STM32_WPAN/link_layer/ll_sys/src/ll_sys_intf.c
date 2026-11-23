/**
  ******************************************************************************
  * @file    ll_sys_intf.c
  * @author  MCD Application Team
  * @brief   Link Layer IP general system interface
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
#include <stdint.h>

#include "ll_sys.h"
#include "linklayer_plat.h"
#include "event_manager.h"
#include "ll_intf.h"

/**
  * @brief  Initialize the Link Layer SoC dependencies
  * @param  None
  * @retval None
  */
void ll_sys_init()
{
  LINKLAYER_PLAT_ClockInit();
}

/**
  * @brief  Assert checking
  * @param  None
  * @retval None
  */
void ll_sys_assert(uint8_t condition)
{
  LINKLAYER_PLAT_Assert(condition);
}

/**
  * @brief  Radio active clock management
  * @param  None
  * @retval None
  */
void ll_sys_radio_ack_ctrl(uint8_t enable)
{
  LINKLAYER_PLAT_AclkCtrl(enable);
}

/**
  * @brief  Link Layer waits for radio bus clock ready
  * @param  None
  * @retval None
  */
void ll_sys_radio_wait_for_busclkrdy(void)
{
  LINKLAYER_PLAT_WaitHclkRdy();
}

/**
  * @brief  Get RNG number for the Link Layer IP
  * @param  None
  * @retval None
  */
void ll_sys_get_rng(uint8_t *ptr_rnd, uint32_t len)
{
  LINKLAYER_PLAT_GetRNG(ptr_rnd, len);
}

/**
  * @brief  Initialize the main radio interrupt
  * @param  intr_cb    radio interrupt callback to link with the radio IRQ
  * @retval None
  */
void ll_sys_setup_radio_intr(void (*intr_cb)())
{
  LINKLAYER_PLAT_SetupRadioIT(intr_cb);
}

/**
  * @brief  Initialize the radio SW low interrupt
  * @param  intr_cb    radio SW low interrupt interrupt callback to link
  *                    with the defined interrupt vector
  * @retval None
  */
void ll_sys_setup_radio_sw_low_intr(void (*intr_cb)())
{
  LINKLAYER_PLAT_SetupSwLowIT(intr_cb);
}

/**
  * @brief  Trigger the radio SW low interrupt
  * @param  None
  * @retval None
  */
void ll_sys_radio_sw_low_intr_trigger(uint8_t priority)
{
  LINKLAYER_PLAT_TriggerSwLowIT(priority);
}

/**
  * @brief  Link Layer radio activity event notification
  * @param  start      start/end of radio event
  * @retval None
  */
void ll_sys_radio_evt_not(uint8_t start)
{
  if(start)
  {
    LINKLAYER_PLAT_StartRadioEvt();
  }

  else
  {
    LINKLAYER_PLAT_StopRadioEvt();
  }
}

/**
  * @brief  Link Layer RCO calibration notification
  * @param  start      start/end of RCO calibration
  * @retval None
  */
void ll_sys_rco_clbr_not(uint8_t start)
{
  if(start)
  {
    LINKLAYER_PLAT_RCOStartClbr();
  }

  else
  {
    LINKLAYER_PLAT_RCOStopClbr();
  }
}

/**
  * @brief  Link Layer temperature request
  * @param  None
  * @retval None
  */
void ll_sys_request_temperature(void)
{
   LINKLAYER_PLAT_RequestTemperature();
}

/**
  * @brief  Link Layer background task pcoessing procedure
  * @param  None
  * @retval None
  */
void ll_sys_bg_process(void)
{
  if(emngr_can_mcu_sleep() == 0)
  {
    emngr_handle_all_events();

    HostStack_Process();
  }

  if(emngr_can_mcu_sleep() == 0)
  {
    ll_sys_schedule_bg_process();
  }
}

void ll_sys_schldr_timing_update_not(Evnt_timing_t * p_evnt_timing)
{
  LINKLAYER_PLAT_SCHLDR_TIMING_UPDATE_NOT(p_evnt_timing);
}

#if (SUPPORT_PROFILE != PROFILE_DISABLED)

ble_stat_t ll_sys_advanced_profile_init(uint32_t* drift_values, uint32_t* exec_values,
			       const uint8_t drift_size, const uint8_t exec_size,
			       profiming_timing_clbk max_profiling_time_detected_cbk)
{
  return ll_intf_advanced_profile_init( drift_values, exec_values,
			       drift_size, exec_size,
			       max_profiling_time_detected_cbk);
}

void ll_sys_get_timing_stats( uint32_t* exec_time, uint32_t* drift_time, uint32_t* average_drift_time,
			      uint8_t reset_timing )
{
  ll_intf_get_profile_statistics(exec_time, drift_time,average_drift_time, reset_timing);
}

ble_stat_t ll_sys_get_advanced_timing_stats( uint32_t* exec_time, uint32_t* drift_time,
				         uint8_t reset_timing )
{
  return ll_intf_get_advanced_profile_statistics(exec_time, drift_time, reset_timing);
}
#endif

__WEAK void HostStack_Process(void)
{

}
