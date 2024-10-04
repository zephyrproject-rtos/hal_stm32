/* USER CODE BEGIN Header */

/**
  ******************************************************************************
  * @file    dtm_burst.h
  * @author  GPM WBL Application Team
  * @brief   Header file for module implementing test burst commands
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

#ifndef _DTM_BURST_H_
#define _DTM_BURST_H_

#include "ble_status.h"

tBleStatus BURST_TXNotificationStart(uint16_t Connection_Handle, uint16_t Service_Handle,
                                      uint16_t Char_Handle, uint16_t Value_Length);

tBleStatus BURST_TXWriteCommandStart(uint16_t Connection_Handle, uint16_t Attr_Handle,
                                     uint16_t Value_Length);

tBleStatus BURST_RXStart(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint8_t Notifications_WriteCmds);

tBleStatus BURST_TXStop(void);

tBleStatus BURST_RXStop(void);

uint8_t BURST_NotificationReceived(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint16_t Value_Length, uint8_t Value[]);

uint8_t BURST_WriteReceived(uint16_t Connection_Handle, uint16_t Attribute_Handle, uint16_t Value_Length, uint8_t Value[]);

uint8_t BURST_BufferAvailableNotify(void);

uint32_t BURST_TXReport(void);

uint32_t BURST_RXReport(uint16_t *Data_Length, uint32_t *Sequence_Errors);

void BURST_Tick(void);

void BURST_StartCallback(void);

#endif /* _DTM_BURST_H_ */
