/* USER CODE BEGIN Header */

/**
  ******************************************************************************
  * @file    dtm_cmds.h
  * @author  GPM WBL Application Team
  * @brief   Header file for module implementing come ACI commands outside of BLE Stack
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef DTM_CMDS_H
#define DTM_CMDS_H

void DTM_CMDS_TxEnd(void);

void DTM_CMDS_TxTestStopRequest(void);

void DTM_CMDS_TxTestStop(void);

#endif /* DTM_CMDS_H */
