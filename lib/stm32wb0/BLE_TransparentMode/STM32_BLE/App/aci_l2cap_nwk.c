/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    aci_l2cap_nwk.c
  * @author  GPM WBL Application Team
  * @brief   Adaptation layer from L2CAP native interface to network
  *                      processor interface
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

#include "app_common.h"
#include "ble.h"
#include "aci_l2cap_nwk.h"
#include "dtm_preprocess_events.h"

#if (CFG_BLE_L2CAP_COS_ENABLED == 1) && (BLESTACK_CONTROLLER_ONLY == 0)

#define RX_SDU_BUFFER_SIZE                      600

int aci_l2cap_cos_sdu_data_rx_event_preprocess(uint16_t Connection_Handle,
                                               uint16_t CID,
                                               uint16_t RX_Credit_Balance,
                                               uint16_t SDU_Length)
{
  tBleStatus ret;

  uint8_t SDU_Data_Buffer[RX_SDU_BUFFER_SIZE]; /* Probably need to move outside of CSTACK. */
  uint16_t SDU_Length_extracted = 0x0000;

  ret = aci_l2cap_cos_sdu_data_extract(Connection_Handle, CID, sizeof(SDU_Data_Buffer), SDU_Data_Buffer, &SDU_Length_extracted);

  if(ret == BLE_STATUS_SUCCESS)
  {
    aci_l2cap_cos_sdu_data_rx_nwk_event(Connection_Handle, CID, RX_Credit_Balance, SDU_Length_extracted, SDU_Data_Buffer);
  }

  /* Discard event */
  return 1;
}

#endif
