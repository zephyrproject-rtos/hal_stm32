/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    RADIO_utils.c
  * @author  GPM WBL Application Team
  * @brief   Miscellaneous utilities for interfacing to  HW.
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
#include "RADIO_utils.h"
#include "stm32wb0x_ll_pwr.h"
#include "stm32wb0x_ll_gpio.h"
#include "ble.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TX_POWER_LEVELS                (32U)
#if defined(STM32WB09)
#define HP_TX_POWER_LEVELS             (TX_POWER_LEVELS+1)
#else
#define HP_TX_POWER_LEVELS             (TX_POWER_LEVELS)
#endif

#define LOWEST_TX_POWER_LEVEL_INDEX     (1U)
#if defined(STM32WB09)
#define HIGH_POWER_LEVEL_INDEX  (HP_TX_POWER_LEVELS - 1)
#endif

/** Minimum supported TX power in dBm. */
#define MIN_TX_POWER_LOW  (normal_pa_level_table[LOWEST_TX_POWER_LEVEL_INDEX]) /* high power mode disabled */
#define MIN_TX_POWER_HIGH (high_power_pa_level_table[LOWEST_TX_POWER_LEVEL_INDEX]) /* high power mode enabled */

/** Maximum supported TX power in dBm. */
#define MAX_TX_POWER_LOW  (normal_pa_level_table[TX_POWER_LEVELS-1]) /* high power mode disabled */
#define MAX_TX_POWER_HIGH (high_power_pa_level_table[HP_TX_POWER_LEVELS-1]) /* high power mode enabled */

/* Parameters of the RSSI Exponential Moving Average algorithm */
#define MAX_RSSI_FILTER_COEFF       (4U)
#define RSSI_EMA_SMOOTH_FACTOR_BITS (3)

#if defined(STM32WB09)
#define LDO_ANA_TST                             (*(&RRM->RXADC_ANA_USR + 0x02))
#define RRM_LDO_ANA_TST_RFD_LDO_TRANSFO_BYPASS_Msk                      0x08
#define RRM_LDO_ANA_TST_LDO_ANA_TST_SEL_Msk                             0x01
#endif
#define RRM_TEST                                (*(&RRM->RRM_CTRL + 0x01))

/* This macro can be set to avoid breaking communication by changing the function
  of pins with aci_set_antenna_switch_parameters().  */
#define RESERVED_GPIOS  0x00

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Expected TX output power (dBm) for each PA level when SMPS voltage is 1.4V */
static const int8_t normal_pa_level_table[TX_POWER_LEVELS] = {
    -54, -21, -20, -19, -17, -16, -15, -14,
    -13, -12, -11, -10,  -9,  -8,  -7,  -6,
     -6,  -4,  -3,  -3,  -2,  -2,  -1,  -1,
      0,   0,   1,   2,   3,   4,   5,   6
};

#if defined(STM32WB09)
static const int8_t high_power_pa_level_table[HP_TX_POWER_LEVELS] = {
    -54, -21, -20, -19, -17, -16, -15, -14,
    -13, -12, -11, -10,  -9,  -8,  -7,  -6,
     -6,  -4,  -3,  -3,  -2,  -2,  -1,  -1,
      0,   0,   1,   2,   3,   4,   5,   6,
      8
};
#else
/* Expected TX output power (dBm) for each PA level when SMPS voltage is 1.9V
   (high power mode). */
static const int8_t high_power_pa_level_table[HP_TX_POWER_LEVELS] = {
    -54, -19, -18, -17, -16, -15, -14, -13,
    -12, -11, -10,  -9,  -8,  -7,  -6,  -5,
     -4,  -3,  -3,  -2,  -1,   0,   1,   2,
      3,   8,   8,   8,   8,   8,   8,   8
};
#endif

struct antenna_conf_s {
  uint8_t Antenna_IDs;
  uint8_t Antenna_ID_Shift;
  uint8_t Default_Antenna_ID;
  uint8_t RF_Activity_Enable;
}antenna_conf = {0, ANTENNA_ID_BIT_SHIFT, 0, 0};

uint8_t high_power = FALSE;
uint8_t tone_started = FALSE;
uint8_t pa_level = DEFAULT_TX_PA_LEVEL;

uint8_t RADIO_DBmToPALevel(int8_t TX_dBm)
{
  uint8_t i;
  const int8_t *pa_level_table = high_power ? high_power_pa_level_table : normal_pa_level_table;
  const uint8_t tx_power_levels = high_power ? HP_TX_POWER_LEVELS : TX_POWER_LEVELS;

  for(i = 0; i < tx_power_levels; i++)
  {
    if(pa_level_table[i] >= TX_dBm)
      break;
  }
  if (((pa_level_table[i] > TX_dBm) && (i > LOWEST_TX_POWER_LEVEL_INDEX)) ||
      (i == tx_power_levels))
  {
    i--;
  }

  return i;
}

uint8_t RADIO_DBmToPALevelGe(int8_t TX_dBm)
{
  const int8_t *pa_level_table = high_power ? high_power_pa_level_table : normal_pa_level_table;
  const uint8_t tx_power_levels = high_power ? HP_TX_POWER_LEVELS : TX_POWER_LEVELS;
  uint8_t i;

  for(i = LOWEST_TX_POWER_LEVEL_INDEX; i < tx_power_levels; i++)
  {
    if (pa_level_table[i] >= TX_dBm)
      break;
  }

  if(i == tx_power_levels)
  {
    i--;
  }

  return i;
}

int8_t RADIO_PALevelToDBm(uint8_t PA_Level)
{
  const int8_t *pa_level_table = high_power ? high_power_pa_level_table : normal_pa_level_table;
  const uint8_t tx_power_levels = high_power ? HP_TX_POWER_LEVELS : TX_POWER_LEVELS;

  if(PA_Level < LOWEST_TX_POWER_LEVEL_INDEX || PA_Level >= tx_power_levels)
  {
    return 127;
  }

  return pa_level_table[PA_Level];
}

uint8_t RADIO_GetMaxPALevel(void)
{
  return HP_TX_POWER_LEVELS - 1;
}

uint8_t RADIO_GetDefaultPALevel(void)
{
  return DEFAULT_TX_PA_LEVEL;
}

void RADIO_ReadTransmitPower(int8_t *Min_Tx_Power, int8_t *Max_Tx_Power)
{
    if (high_power)
    {
        *Min_Tx_Power = MIN_TX_POWER_HIGH;
        *Max_Tx_Power = MAX_TX_POWER_HIGH;
    }
    else
    {
        *Min_Tx_Power = MIN_TX_POWER_LOW;
        *Max_Tx_Power = MAX_TX_POWER_LOW;
    }
}

void RADIO_SetHighPower(FunctionalState state)
{
  if(state != DISABLE)
  {
    if(high_power == FALSE)
    {
      high_power = TRUE;
#if defined(RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS)
      LL_APB0_GRP1_EnableClock(LL_APB0_GRP1_PERIPH_SYSCFG);
      LL_SYSCFG_BLERXTX_SetTrigger(LL_SYSCFG_BLERXTX_TRIGGER_BOTH_EDGE, LL_SYSCFG_BLE_TX_EVENT);
      LL_SYSCFG_BLERXTX_SetType(LL_SYSCFG_BLERXTX_DET_TYPE_EDGE, LL_SYSCFG_BLE_TX_EVENT);
      LL_SYSCFG_BLERXTX_EnableIT(LL_SYSCFG_BLE_TX_EVENT);
      LL_SYSCFG_BLERXTX_ClearInterrupt(LL_SYSCFG_BLE_TX_EVENT);
      NVIC_EnableIRQ(RADIO_TXRX_SEQ_IRQn);
#endif
    }
  }
  else
  {
    if(high_power == TRUE)
    {
      high_power = FALSE;
#if defined(RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS)
      LL_SYSCFG_BLERXTX_DisableIT(LL_SYSCFG_BLE_TX_EVENT);
      NVIC_DisableIRQ(RADIO_TXRX_SEQ_IRQn);
      LL_SYSCFG_BLERXTX_ClearInterrupt(LL_SYSCFG_BLE_TX_EVENT);
#endif
    }
  }

  if (LL_PWR_IsEnabledSMPSPrechargeMode() || (LL_PWR_GetSMPSMode() == LL_PWR_NO_SMPS))
    return;

  /* Bypass SMPS */
  LL_PWR_SetSMPSPrechargeMode(LL_PWR_SMPS_PRECHARGE);
  while(LL_PWR_IsSMPSReady());
  /* Change level */
  if(state != DISABLE)
  {
    LL_PWR_SMPS_SetOutputVoltageLevel(PWR_SMPS_OUTPUT_VOLTAGE_1V90);
  }
  else
  {
    LL_PWR_SMPS_SetOutputVoltageLevel(PWR_SMPS_OUTPUT_VOLTAGE_1V40);
  }
  /* Disable bypass*/
  LL_PWR_SetSMPSPrechargeMode(LL_PWR_NO_SMPS_PRECHARGE);
  while(!LL_PWR_IsSMPSReady());
}

void HAL_RADIO_TxRxSeqCallback(void)
{
#if defined(RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS)
  if(high_power == FALSE)
    return;

  if(LL_SYSCFG_BLERXTX_IsInterruptPending(LL_SYSCFG_BLE_TX_EVENT)){
    if(RRM->FSM_STATUS_DIG_OUT & RRM_FSM_STATUS_DIG_OUT_STATUS_4)
    {
      // Rising edge
      MODIFY_REG_FIELD(RRM->LDO_ANA_ENG, RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS, 1);
    }
    else
    {
      // Falling edge
      MODIFY_REG_FIELD(RRM->LDO_ANA_ENG, RRM_LDO_ANA_ENG_RFD_LDO_TRANSFO_BYPASS, 0);
    }
    LL_SYSCFG_BLERXTX_ClearInterrupt(LL_SYSCFG_BLE_TX_EVENT);
  }
#endif
}

/* ------------ Section for tone generation functions ------------------------*/

void RADIO_ToneStart(uint8_t RF_Channel, uint8_t Offset, uint8_t PA_Level)
{
  uint8_t internal_pa_level = PA_Level;

  /* Calculate the synt divide factor for 16 MHz quarts and +250 kHz offset wrt the channel center frequency
  *  Algorithmically MAK = F_rf*(2^20)/35 = F_rf*(2^15)
  *  With F_rf = (2402+2*RF_Channel)+0.25 MHz
  *  K corresponds to b19-b0  of MAK
  *  A corresponds to b22-b20 of MAK
  *  M corresponds to b27-b23 of MAK
  */
  uint32_t kHz_250_scaled = 8192; /* = 0.250*2^20/32 */
  uint32_t MAK = ((2402UL + 2UL * RF_Channel) << 15);

  if (Offset == 1U)
  {
    MAK += kHz_250_scaled;
  }
  else if (Offset == 2U)
  {
    MAK -= kHz_250_scaled;
  }
  else
  {
    /* MISRAC2012-Rule-15.7: explicit else; no action required */
  }

  uint8_t M  = ((uint8_t)(MAK >> 23) & 0x1FU);
  uint8_t A  = ((uint8_t)(MAK >> 20) & 0x07U);
  uint32_t K = (MAK & 0x000FFFFFUL) + 1UL;

#if defined(STM32WB09)
  if(PA_Level == HIGH_POWER_LEVEL_INDEX)
  {
    internal_pa_level = HIGH_POWER_LEVEL_INDEX - 1;
    LDO_ANA_TST = RRM_LDO_ANA_TST_RFD_LDO_TRANSFO_BYPASS_Msk|RRM_LDO_ANA_TST_LDO_ANA_TST_SEL_Msk;
  }
#endif
  RRM->RADIO_FSM_USR = ((uint32_t)internal_pa_level << 3) | RRM_RADIO_FSM_USR_EN_CALIB_SYNTH_Msk | RRM_RADIO_FSM_USR_EN_CALIB_CBP_Msk;
  RRM->MOD3_DIG_TST = ((uint32_t)M << 3) | ((uint32_t)A & 0x7UL);
  RRM->MOD2_DIG_TST = (K >> 12) & 0xFFU;
  RRM->MOD1_DIG_TST = (K >> 4) & 0xFFU;
  RRM->MOD0_DIG_TST = ((K & 0x0FU) << 4) | 0x09U;

  /* Take control of the radio FSM through the test bus */
  RRM->DTB5_DIG_ENG = 0x09;
  RRM_TEST = 0x03;
  RRM->DTB5_DIG_ENG = 0x39;
  while (RRM->FSM_STATUS_DIG_OUT != 0x04UL);
  RRM->DTB5_DIG_ENG = 0x3B;
}

void RADIO_ToneStop(void)
{
  /* Release control of the radio FSM through the test bus */
  RRM->DTB5_DIG_ENG = 0x00;
  volatile uint32_t *rrm_udra_test = &RRM->RRM_CTRL + 0x01;
  *rrm_udra_test = 0x00;
  RRM->MOD0_DIG_TST = 0;
#if defined(STM32WB09)
  LDO_ANA_TST = 0;
#endif
}

/* Review with the use of linear values instead of dBm values to have more precision */
static const int8_t rssi_ema_smoothing_factor_table[MAX_RSSI_FILTER_COEFF + 1] = {
    7, 5, 3, 2, 1
};

int8_t RADIO_UpdateAvgRSSI(int8_t avg_rssi, int8_t rssi, uint8_t rssi_filter_coeff)
{
    if (avg_rssi == RSSI_INVALID)
    {
        return rssi;
    }

    if ((rssi == RSSI_INVALID) || (rssi_filter_coeff > MAX_RSSI_FILTER_COEFF))
    {
        return avg_rssi;
    }

    return (avg_rssi +
            (((rssi - avg_rssi) * rssi_ema_smoothing_factor_table[rssi_filter_coeff])
             >> RSSI_EMA_SMOOTH_FACTOR_BITS));
}

/* ---------- Utility functions for antenna switching ------------------------*/

void RADIO_AntIdxRemap(uint8_t AntPattLen, uint8_t *pAntRamTable, const uint8_t* pAntPatt)
{
#if defined(STM32WB07) || defined(STM32WB06) || defined(STM32WB09)
    for (uint8_t i=0; i<AntPattLen; i++)
    {
        pAntRamTable[i] = (pAntPatt[i] << antenna_conf.Antenna_ID_Shift);
    }
#endif
}

#if defined(STM32WB05) || defined(STM32WB09)
tBleStatus aci_hal_set_antenna_switch_parameters(uint8_t Antenna_IDs,
                                                 uint8_t Antenna_ID_Shift,
                                                 uint8_t Default_Antenna_ID,
                                                 uint8_t RF_Activity_Enable)
{
  GPIO_InitTypeDef GPIO_Init = {
    .Pin = Antenna_IDs, // With this we assume that Antenna_IDs bitmask is equal to the pin bitmask.
    .Mode = GPIO_MODE_AF_PP,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_FREQ_VERY_HIGH,
    .Alternate = LL_GPIO_AF_6
  };

  if(Antenna_IDs > 0x7F || Antenna_IDs & RESERVED_GPIOS || Antenna_ID_Shift > 7 ||
     Default_Antenna_ID > 0x7F || RF_Activity_Enable > 1)
  {
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
  }

  antenna_conf.Antenna_IDs = Antenna_IDs;
  antenna_conf.Antenna_ID_Shift = Antenna_ID_Shift;
  antenna_conf.Default_Antenna_ID = Default_Antenna_ID;
  antenna_conf.RF_Activity_Enable = RF_Activity_Enable;

  LL_RADIO_SetDefaultAntennaID(Default_Antenna_ID);

  if(RF_Activity_Enable)
  {
    GPIO_Init.Pin |= GPIO_PIN_7;
  }

  HAL_GPIO_Init(GPIOB, &GPIO_Init);
  HAL_GPIO_WritePin(GPIOB, Antenna_IDs, GPIO_PIN_RESET);

  return BLE_STATUS_SUCCESS;
}
#else
tBleStatus aci_hal_set_antenna_switch_parameters(uint8_t Antenna_IDs,
                                                 uint8_t Antenna_ID_Shift,
                                                 uint8_t Default_Antenna_ID,
                                                 uint8_t RF_Activity_Enable)
{
  return BLE_ERROR_UNKNOWN_HCI_COMMAND;
}
#endif

tBleStatus aci_hal_set_tx_power_level_preprocess(uint8_t En_High_Power,
                                      uint8_t PA_Level)
{
  if((PA_Level > RADIO_GetMaxPALevel()) || (En_High_Power > 1))
  {
    return BLE_ERROR_INVALID_HCI_CMD_PARAMS;
  }

  pa_level = PA_Level;

  return BLE_STATUS_SUCCESS;
}

/* ---------- Utility functions for star ttone ------------------------*/

static bool LL_busy(void)
{
  uint8_t n_banks = ((CFG_BLE_NUM_RADIO_TASKS-1)/8+1);
  uint8_t link_status[8];
  uint16_t link_connection_handles[8];

  for(int i = 0; i < n_banks; i++)
  {
    aci_hal_get_link_status(i, link_status, link_connection_handles);

    for(int j = 0; j < 8; j++)
    {
      if(link_status[j] != LL_IDLE)
      {
        return TRUE;
      }
    }
  }

  return FALSE;
}

tBleStatus aci_hal_tone_start(uint8_t RF_Channel, uint8_t Offset)
{
  tBleStatus status;

  if (tone_started)          /* already started before */
  {
    status = BLE_ERROR_COMMAND_DISALLOWED;
  }
  else
  {
    if ((RF_Channel >= 40U) || (Offset > 2U))
    {    /* channel ID must be from 0-39 */
      status = BLE_ERROR_INVALID_HCI_CMD_PARAMS;
    }
    else
    {
      if (LL_busy() == FALSE)
      {

#if defined(STM32WB07) || defined(STM32WB06) || defined(STM32WB09)
        /* Set GPIOs for antenna switch in output mode. */
        GPIO_InitTypeDef GPIO_Init = {
          .Pin = antenna_conf.Antenna_IDs,
          .Mode = GPIO_MODE_OUTPUT_PP,
          .Pull = GPIO_NOPULL,
          .Speed = GPIO_SPEED_FREQ_LOW,
        };

        if(antenna_conf.RF_Activity_Enable)
        {
          GPIO_Init.Pin |= GPIO_PIN_7;
        }

        HAL_GPIO_Init(GPIOB, &GPIO_Init);

        HAL_GPIO_WritePin(GPIOB, antenna_conf.Antenna_IDs, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, antenna_conf.Default_Antenna_ID & antenna_conf.Antenna_IDs, GPIO_PIN_SET);

        if(antenna_conf.RF_Activity_Enable)
        {
          /* Drive RF activity pin to enable the antenna switch. */
          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
        }
#endif

        RADIO_ToneStart(RF_Channel, Offset, pa_level);
        tone_started = TRUE;

        status = BLE_STATUS_SUCCESS;
      }else
      {
        status = BLE_ERROR_COMMAND_DISALLOWED;
      }
    }
  }

  return status;
}

tBleStatus aci_hal_tone_stop()
{
  tBleStatus status;

  if (tone_started)
  {
    RADIO_ToneStop();
    tone_started = FALSE;

#if defined(STM32WB07) || defined(STM32WB06) || defined(STM32WB09)
    aci_hal_set_antenna_switch_parameters(antenna_conf.Antenna_IDs,
                                          antenna_conf.Antenna_ID_Shift,
                                          antenna_conf.Default_Antenna_ID,
                                          antenna_conf.RF_Activity_Enable);
#endif
    status = BLE_STATUS_SUCCESS;
  }
  else
  {
    status = BLE_ERROR_COMMAND_DISALLOWED;
  }

  return status;
}
