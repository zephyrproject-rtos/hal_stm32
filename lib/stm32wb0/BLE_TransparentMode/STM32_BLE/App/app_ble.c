/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_ble.c
  * @author  GPM WBL Application Team
  * @brief   BLE Application
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "stm32wb0x.h"
#include "ble.h"
#include "gap_profile.h"
#include "app_ble.h"
#include "stm32wb0x_hal_radio_timer.h"
#include "bleplat.h"
#include "nvm_db.h"
#include "blenvm.h"
#include "pka_manager.h"
#include "stm32_seq.h"
#include "transport_layer.h"
#include "miscutil.h"
#include "aci_l2cap_nwk.h"
#include "aci_gatt_nwk.h"
#include "dm_alloc.h"
#include "aci_adv_nwk.h"
#include "dtm_burst.h"
/* Add aci_blue_initialized_event() prototype */
void aci_blue_initialized_event(uint8_t Reason_Code);

/* Add aci_blue_crash_info_event() prototype */
void aci_blue_crash_info_event(uint8_t Crash_Type,
                               uint32_t SP,
                               uint32_t R0,
                               uint32_t R1,
                               uint32_t R2,
                               uint32_t R3,
                               uint32_t R12,
                               uint32_t LR,
                               uint32_t PC,
                               uint32_t xPSR,
                               uint8_t Debug_Data_Length,
                               uint8_t Debug_Data[]);

uint16_t num_packets = 0;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */
/* Private define ------------------------------------------------------------*/
#define RESET_REASON_WDG        ((uint8_t)0x05)
#define RESET_REASON_LOCKUP     ((uint8_t)0x06)
#define RESET_REASON_POR_BOR    ((uint8_t)0x07)
#define RESET_REASON_CRASH      ((uint8_t)0x08)
/* USER CODE BEGIN PD */

/* USER CODE END PD */
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */
/* Private variables ---------------------------------------------------------*/

NO_INIT(uint32_t dyn_alloc_a[BLE_DYN_ALLOC_SIZE>>2]);

NO_INIT(uint32_t aci_gatt_adv_nwk_buffer[CFG_BLE_GATT_ADV_NWK_BUFFER_SIZE>>2]);

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private functions ---------------------------------------------------------*/

/* USER CODE BEGIN PF */

/* USER CODE END PF */

/* Functions Definition ------------------------------------------------------*/
void ModulesInit(void)
{
  BLENVM_Init();
  if (PKAMGR_Init() == PKAMGR_ERROR)
  {
    Error_Handler();
  }
}

void BLE_Init(void)
{
  tBleStatus ret;

  BLE_STACK_InitTypeDef BLE_STACK_InitParams = {
    .BLEStartRamAddress = (uint8_t*)dyn_alloc_a,
    .TotalBufferSize = BLE_DYN_ALLOC_SIZE,
    .NumAttrRecords = CFG_BLE_NUM_GATT_ATTRIBUTES,
    .MaxNumOfClientProcs = CFG_BLE_NUM_OF_CONCURRENT_GATT_CLIENT_PROC,
    .NumOfRadioTasks = CFG_BLE_NUM_RADIO_TASKS,
    .NumOfEATTChannels = CFG_BLE_NUM_EATT_CHANNELS,
    .NumBlockCount = CFG_BLE_MBLOCKS_COUNT,
    .ATT_MTU = CFG_BLE_ATT_MTU_MAX,
    .MaxConnEventLength = CFG_BLE_CONN_EVENT_LENGTH_MAX,
    .SleepClockAccuracy = CFG_BLE_SLEEP_CLOCK_ACCURACY,
    .NumOfAdvDataSet = CFG_BLE_NUM_ADV_SETS,
    .NumOfSubeventsPAwR = CFG_BLE_NUM_PAWR_SUBEVENTS,
    .MaxPAwRSubeventDataCount = CFG_BLE_PAWR_SUBEVENT_DATA_COUNT_MAX,
    .NumOfAuxScanSlots = CFG_BLE_NUM_AUX_SCAN_SLOTS,
    .FilterAcceptListSizeLog2 = CFG_BLE_FILTER_ACCEPT_LIST_SIZE_LOG2,
    .L2CAP_MPS = CFG_BLE_COC_MPS_MAX,
    .L2CAP_NumChannels = CFG_BLE_COC_NBR_MAX,
    .NumOfSyncSlots = CFG_BLE_NUM_SYNC_SLOTS,
    .CTE_MaxNumAntennaIDs = CFG_BLE_NUM_CTE_ANTENNA_IDS_MAX,
    .CTE_MaxNumIQSamples = CFG_BLE_NUM_CTE_IQ_SAMPLES_MAX,
    .NumOfSyncBIG = CFG_BLE_NUM_SYNC_BIG_MAX,
    .NumOfBrcBIG = CFG_BLE_NUM_BRC_BIG_MAX,
    .NumOfSyncBIS = CFG_BLE_NUM_SYNC_BIS_MAX,
    .NumOfBrcBIS = CFG_BLE_NUM_BRC_BIS_MAX,
    .NumOfCIG = CFG_BLE_NUM_CIG_MAX,
    .NumOfCIS = CFG_BLE_NUM_CIS_MAX,
    .isr0_fifo_size = CFG_BLE_ISR0_FIFO_SIZE,
    .isr1_fifo_size = CFG_BLE_ISR1_FIFO_SIZE,
    .user_fifo_size = CFG_BLE_USER_FIFO_SIZE
  };

  /* Bluetooth LE stack init */
  ret = BLE_STACK_Init(&BLE_STACK_InitParams);
  if (ret != BLE_STATUS_SUCCESS) {
    Error_Handler();
  }
}

void BLEStack_Process_Schedule(void)
{
  /* Keep BLE Stack Process priority low, since there are limited cases
     where stack wants to be rescheduled for busy waiting.  */
  UTIL_SEQ_SetTask( 1U << CFG_TASK_BLE_STACK, CFG_SEQ_PRIO_1);
}

static void BLEStack_Process(void)
{
  APP_DEBUG_SIGNAL_SET(APP_STACK_PROCESS);
  BLE_STACK_Tick();

  if(BLE_STACK_SleepCheck() == 0)
  {
    BLEStack_Process_Schedule();
  }
  APP_DEBUG_SIGNAL_RESET(APP_STACK_PROCESS);
}

void VTimer_Process(void)
{
  HAL_RADIO_TIMER_Tick();
}

void VTimer_Process_Schedule(void)
{
  UTIL_SEQ_SetTask( 1U << CFG_TASK_VTIMER, CFG_SEQ_PRIO_0);
}

void NVM_Process(void)
{
  NVMDB_Tick();
}

void NVM_Process_Schedule(void)
{
  UTIL_SEQ_SetTask( 1U << CFG_TASK_NVM, CFG_SEQ_PRIO_1);
}

void TM_Process_Schedule(void)
{
  UTIL_SEQ_SetTask( 1U << CFG_TASK_TM, CFG_SEQ_PRIO_1);
}

void TM_Process(void)
{
  transport_layer_tick();
}

void BURST_Process_Schedule(void)
{
  UTIL_SEQ_SetTask( 1U << CFG_TASK_BURST, CFG_SEQ_PRIO_1);
}

void BURST_Process(void)
{
  BURST_Tick();
}

/* Function called from PKA_IRQHandler() context. */
void PKAMGR_IRQCallback(void)
{
  BLEStack_Process_Schedule();
}

/* Function called from RADIO_TIMER_TXRX_WKUP_IRQHandler() context. */
void HAL_RADIO_TIMER_TxRxWakeUpCallback(void)
{
  VTimer_Process_Schedule();
  BLEStack_Process_Schedule();
}

/* Function called from RADIO_TIMER_CPU_WKUP_IRQHandler() context. */
void HAL_RADIO_TIMER_CpuWakeUpCallback(void)
{
  VTimer_Process_Schedule();
  BLEStack_Process_Schedule();
}

/* Function called from RADIO_TXRX_IRQHandler() context. */
void HAL_RADIO_TxRxCallback(uint32_t flags)
{
  BLE_STACK_RadioHandler(flags);

  BLEStack_Process_Schedule();
  VTimer_Process_Schedule();
  NVM_Process_Schedule();
}

/* Functions Definition ------------------------------------------------------*/
void APP_BLE_Init(void)
{
  crash_info_t crash_info;
  /* USER CODE BEGIN APP_BLE_Init_1 */

  /* USER CODE END APP_BLE_Init_1 */

  UTIL_SEQ_RegTask(1U << CFG_TASK_BLE_STACK, UTIL_SEQ_RFU, BLEStack_Process);
  UTIL_SEQ_RegTask(1U << CFG_TASK_VTIMER, UTIL_SEQ_RFU, VTimer_Process);
  UTIL_SEQ_RegTask(1U << CFG_TASK_NVM, UTIL_SEQ_RFU, NVM_Process);
  UTIL_SEQ_RegTask(1U << CFG_TASK_TM, UTIL_SEQ_RFU, TM_Process);
  UTIL_SEQ_RegTask(1U << CFG_TASK_BURST, UTIL_SEQ_RFU, BURST_Process);

  ModulesInit();

  /* Initialization of HCI & GATT & GAP layer */
  BLE_Init();

  /* Need to call stack process at least once. */
  BLEStack_Process_Schedule();

    /* Used by aci_gatt_nwk and adv_buff_alloc libraries.  */
  dm_init(CFG_BLE_GATT_ADV_NWK_BUFFER_SIZE, aci_gatt_adv_nwk_buffer);

  aci_adv_nwk_init();

#if (BLESTACK_CONTROLLER_ONLY == 0)
  ACI_gatt_nwk_init(CFG_BLE_ATT_QUEUED_WRITE_SIZE);
#endif

  transport_layer_init();

  /* Get crash info */
  GetCrashInfo(&crash_info);

  if(RAM_VR.Reserved[0] == 0x01){
    // Send a command complete event for HCI_Reset
    uint8_t buffer_out[] = {0x04,0x0E,0x04,0x01,0x03,0x0C,0x00};
    RAM_VR.Reserved[0] = 0x00;
    send_event(buffer_out,7,-1);
  }

#if (BLESTACK_CONTROLLER_ONLY == 0)

  uint8_t reset_reason = 0x01;

  /* EVT_BLUE_INITIALIZED */
  /* Check the reset reason */
  if(RAM_VR.ResetReason & RCC_CSR_WDGRSTF){
    reset_reason = RESET_REASON_WDG;
  }
  else if(RAM_VR.ResetReason & RCC_CSR_LOCKUPRSTF) {
    reset_reason = RESET_REASON_LOCKUP;
  }
  else if(RAM_VR.ResetReason & RCC_CSR_PORRSTF) {
    reset_reason = RESET_REASON_POR_BOR;
  }

  if((crash_info.signature&0xFFFF0000) == CRASH_SIGNATURE_BASE) {
    reset_reason = RESET_REASON_CRASH;
  }

  aci_blue_initialized_event(reset_reason);

#endif

  if((crash_info.signature&0xFFFF0000) == CRASH_SIGNATURE_BASE) {
    aci_blue_crash_info_event(crash_info.signature&0xFF,
                              crash_info.SP,
                              crash_info.R0,
                              crash_info.R1,
                              crash_info.R2,
                              crash_info.R3,
                              crash_info.R12,
                              crash_info.LR,
                              crash_info.PC,
                              crash_info.xPSR,
                              0,
                              NULL);
  }

  /* USER CODE BEGIN APP_BLE_Init_2 */

  /* USER CODE END APP_BLE_Init_2 */

  return;
}

/* Implementation of event hooks. */

int aci_l2cap_cos_disconnection_complete_event_preprocess(uint16_t Connection_Handle,
                                                      uint16_t CID)
{
  ACI_gatt_nwk_disconnection(Connection_Handle, CID);

  return 0;
}

int aci_gatt_srv_attribute_modified_event_preprocess(uint16_t Connection_Handle,
                                                     uint16_t CID,
                                                     uint16_t Attr_Handle,
                                                     uint16_t Attr_Data_Length,
                                                     uint8_t Attr_Data[])
{
  return BURST_WriteReceived(Connection_Handle, Attr_Handle, Attr_Data_Length, Attr_Data);
}

int aci_gatt_clt_notification_event_preprocess(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t Attribute_Handle,
                                               uint16_t Attribute_Value_Length,
                                               uint8_t Attribute_Value[])
{
  return BURST_NotificationReceived(Connection_Handle, Attribute_Handle, Attribute_Value_Length, Attribute_Value);
}

int aci_gatt_tx_pool_available_event_preprocess(uint16_t Connection_Handle,
                                                uint16_t Available_Buffers)
{
  if(BURST_BufferAvailableNotify())
  {
    /* BURST is currently enabled. */
    BURST_Process_Schedule();

    return 1;
  }

  return 0;
}

void BURST_StartCallback(void)
{
  BURST_Process_Schedule();
}

void TL_ProcessReqCallback(void)
{
  TM_Process_Schedule();
}

void TL_ResetReqCallback(void)
{
  RAM_VR.Reserved[0] = 0x01; // Remember to send a command complete after reset is completed.
  NVIC_SystemReset();
}

/** \endcond
 */
