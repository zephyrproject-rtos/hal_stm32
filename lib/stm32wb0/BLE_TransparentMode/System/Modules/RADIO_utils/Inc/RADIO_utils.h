/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    RADIO_utils.h
  * @author  GPM WBL Application Team
  * @brief   Header file for HW miscellaneous utilities.
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

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __RADIO_UTILS_H__
#define __RADIO_UTILS_H__

#include "stm32wb0x.h"
#include "ble_status.h"

#define RSSI_INVALID          127
#define DEFAULT_TX_PA_LEVEL    31

#ifndef ANTENNA_ID_BIT_SHIFT
#define ANTENNA_ID_BIT_SHIFT (0)
#endif

/**
  * @brief  Convert power level expressed in dBm into driver
  *           coded PALevel
  * @param  TX_dBm value of Tx power in dBm unit
  * @retval PA Level table index
  */
uint8_t RADIO_DBmToPALevel(int8_t TX_dBm);

/**
  * @brief  Convert power level expressed in dBm into driver
  *           coded PALevel
  * @param  TX_dBm value of Tx power in dBm unit
  * @retval PA Level table index
  */
uint8_t RADIO_DBmToPALevelGe(int8_t TX_dBm);

/**
  * @brief  Convert power level index into dBm unit tx power
  * @param  PA Level table index (0 to 31)
  * @retval power in dBm unit
  */
int8_t RADIO_PALevelToDBm(uint8_t PA_Level);

/**
  * @brief  Get Max PA Level index
  * @param  None
  * @retval power level index
  */
uint8_t RADIO_GetMaxPALevel(void);

/**
  * @brief  Get default PA Level set into the driver
  * @param  None
  * @retval power level index
  */
uint8_t RADIO_GetDefaultPALevel(void);

/**
  * @brief  Get minimum and maximum transmission power in dBm
  * @param  [out] Min_Tx_Power minimum transmission power in dBm
  * @param  [out] Max_Tx_Power maximum transmission power in dBm
  * @retval None
  */
void RADIO_ReadTransmitPower(int8_t *Min_Tx_Power, int8_t *Max_Tx_Power);

int8_t RADIO_UpdateAvgRSSI(int8_t avg_rssi, int8_t rssi, uint8_t rssi_filter_coeff);

/**
  * @brief  Configure the radio to be able to reach 8dbm output power
  * @note   This function should not be called by the the application if the
  *         BLE stack is used. Instead, user must call
  *         aci_hal_set_tx_power_level() to change output power mode.
  *         This function enables RADIO_TXRX_SEQ_IRQn interrupt: HAL_RADIO_TXRX_SEQ_IRQHandler()
  *         must be called by RADIO_TXRX_SEQ_IRQHandler().
  * @param  state Enable or disable the ability to reach 8 dBm. This parameter
  *               can be set either to ENABLE or DISABLE.
  * @retval None
  */
void RADIO_SetHighPower(FunctionalState state);

/**
  * @brief  Executes antenna id pattern remap
  * @param  AntPattLen Antenna ID pattern length
  * @param  pAntRamTable Antenna ID Ram table reference
  * @param  pAntPatt Antenna ID pattern
  * @retval None
  */
void RADIO_AntIdxRemap(uint8_t AntPattLen, uint8_t *pAntRamTable, const uint8_t* pAntPatt);

void RADIO_ToneStart(uint8_t RF_Channel, uint8_t Offset, uint8_t PA_Level);
void RADIO_ToneStop(void);
tBleStatus aci_hal_set_tx_power_level_preprocess(uint8_t En_High_Power, uint8_t PA_Level);

/**
 * @brief This command is used to enable ANTENNA_ID signal by enabling the
 *        Alternate Function on the corresponding pins. Some IOs may not be
 *        enabled, depending on resources availability (e.g. IOs used for
 *        communication).
 * @param Antenna_IDs ANTENNA_ID pins to be enabled. Each bit in the mask
 *        enables the corresponding bit of the ANTENNA_ID signal, which is
 *        output on PB[0:7].
 *        Flags:
 *        - 0x01: ANTENNA_ID_0
 *        - 0x02: ANTENNA_ID_1
 *        - 0x04: ANTENNA_ID_2
 *        - 0x08: ANTENNA_ID_3
 *        - 0x10: ANTENNA_ID_4
 *        - 0x20: ANTENNA_ID_5
 *        - 0x40: ANTENNA_ID_6
 * @param Antenna_ID_Shift This parameter can be set to a value different from
 *        zero to shift the ANTENNA_ID signal by the given number of bits. This
 *        number does not affect the pin selected by Antenna_IDs parameter. E.g.
 *        to have the ANTENNA_ID signal output on PB[2:4], set Antenna_IDs to
 *        enable ANTENNA_ID[2:4] (Antenna_IDs = 0x1C) and Antenna_ID_Shift to 2.
 *        Values:
 *        - 0 ... 6
 * @param Default_Antenna_ID The ID of antenna that the controller will select
 *        for regular communication. The antenna to be used when sending or
 *        receiving the CTE field needs to be specified through the Antenna_IDs
 *        parameter of the dedicated HCI commands (i.e.
 *        hci_le_set_connectionless_cte_transmit_parameters,
 *        hci_le_set_connectionless_iq_sampling_enable,
 *        hci_le_set_connection_cte_receive_parameters and
 *        hci_le_set_connection_cte_transmit_parameters).
 *        Values:
 *        - 0x00 ... 0x7F
 * @param RF_Activity_Enable Enable or disable the RF Activity signal, if
 *        supported by the device. This signal can be used to enable the antenna
 *        switch only when necessary.
 *        Values:
 *        - 0x00: DISABLED
 *        - 0x01: ENABLED
 * @retval Value indicating success or error code.
 */
tBleStatus aci_hal_set_antenna_switch_parameters(uint8_t Antenna_IDs,
                                                 uint8_t Antenna_ID_Shift,
                                                 uint8_t Default_Antenna_ID,
                                                 uint8_t RF_Activity_Enable);

/**
 * @brief This command starts a carrier frequency, i.e. a tone, on a specific
 *        channel. The frequency sine wave at the specific channel may be used
 *        for debugging purpose only. The channel ID is a parameter from 0x00 to
 *        0x27 for the 40 BLE channels, e.g. 0x00 for 2.402 GHz, 0x01 for 2.404
 *        GHz etc. This command should not be used when normal Bluetooth
 *        activities are ongoing. The tone should be stopped by @ref
 *        aci_hal_tone_stop command.
 * @param RF_Channel BLE Channel ID, from 0x00 to 0x27 meaning (2.402 + 2*0xXX)
 *        GHz.
 *        Values:
 *        - 0x00 ... 0x27
 * @param Offset Specify if the tone must be emitted with an offset from the
 *        channel center frequency.  If 0, the tone is emitted at the channel
 *        center frequency. If 1 or 2, the device will continuously emit the
 *        tone at the center frequency plus or minus 250 kHz respectively.
 *        Values:
 *        - 0x00: 0 kHz offset
 *        - 0x01: +250 kHz offset
 *        - 0x02: -250 kHz offset
 * @retval Value indicating success or error code.
 */
tBleStatus aci_hal_tone_start(uint8_t RF_Channel,
                              uint8_t Offset);
/**
 * @brief This command is used to stop the previously started @ref
 *        aci_hal_tone_start command.
 * @retval Value indicating success or error code.
 */
tBleStatus aci_hal_tone_stop(void);

#endif /* __RADIO_UTILS_H__ */
