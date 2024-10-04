/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    miscutils.c
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
#include "miscutil.h"
#include "RADIO_utils.h"
#include "compiler.h"
#include "stm32wb0x_ll_system.h"
#include "stm32wb0x_ll_utils.h"
#include "stm32wb0x_ll_pwr.h"
#include "stm32wb0x_ll_bus.h"
#include "stm32wb0x_ll_usart.h"
#include "stm32wb0x_hal_conf.h"

NO_INIT_SECTION(crash_info_t CrashInfoRam, ".crash_info_ram_vr");

/** @addtogroup Miscellaneous_Utilities
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

void GetPartInfo(PartInfoType *partInfo)
{
  uint32_t jtag_id;

  partInfo->die_id = DIE_SW_ID_UNKOWN;

  jtag_id = LL_SYSCFG_GetDeviceJTAG_ID();

#if defined(STM32WB09)
  if(jtag_id == JTAG_ID_CODE_STM32WB09XX)
  {
    partInfo->die_id = DIE_SW_ID_STM32WB09XX;
  }
#elif defined(STM32WB07) || defined(STM32WB06)
  if(jtag_id == JTAG_ID_CODE_STM32WB07XX)
  {
    partInfo->die_id = DIE_SW_ID_STM32WB07XX;
  }
#elif defined(STM32WB05)
  if(jtag_id == JTAG_ID_CODE_STM32WB05XX)
  {
    partInfo->die_id = DIE_SW_ID_STM32WB05XX;
  }
#endif

  partInfo->die_major     =  LL_SYSCFG_GetDeviceVersion();
  partInfo->die_cut       =  LL_SYSCFG_GetDeviceRevision();
  partInfo->jtag_id_code  =  LL_SYSCFG_GetDeviceJTAG_ID(); // Duplicated
  partInfo->flash_size    =  (LL_GetFlashSize() + 1) * 4;

  if (LL_GetRAMSize() != LL_UTILS_RAMSIZE_24K)
  {
    partInfo->ram_size    =  (LL_GetRAMSize() + 1) * 16 * 1024;
  }
  else
  {
    partInfo->ram_size    =  24*1024;
  }

}

/**
 * @brief Get Crash Information utility
 */
void GetCrashInfo(crash_info_t *crashInfo)
{
  *crashInfo = CrashInfoRam;
  /* Reset crash info value */
  CrashInfoRam.signature = 0;
}
void CrashHandler(uint32_t msp, uint32_t signature)
{
  volatile uint32_t * crash_info = (volatile uint32_t *)&CrashInfoRam;
  register uint32_t reg_content;
  /* Init to zero the crash_info RAM locations */
  for (reg_content=0; reg_content<NMB_OF_EXCEP_RAM_WORD; reg_content++) {
    crash_info[reg_content] = 0;
  }
  /* Store Crash Signature */
  CrashInfoRam.signature = signature;
  /* Store SP register */
  CrashInfoRam.SP = msp;
  for (reg_content=2; reg_content<NMB_OF_EXCEP_RAM_WORD; reg_content++) {
    uint32_t *ptr = ((uint32_t *)msp)+(reg_content-2);
    if ((ptr >= ((uint32_t *)  _MEMORY_RAM_BEGIN_)) &&
        (ptr <= ((uint32_t *) _MEMORY_RAM_END_)))
      crash_info[reg_content] = *ptr;
  }
  NVIC_SystemReset();
}

uint8_t GetDemodCI(void)
{
    /* Read the CI from the demodulator register */
    uint8_t demod_ci = (RRM->DEMOD_DIG_OUT) & 0x03U;

    /* Remap to the standard compliant values */
    uint8_t std_ci = (demod_ci == 0x02U ? 0x01U : 0x00U);

    return std_ci;
}

/**
 *@
} */ /* End of group Miscellaneous_Utilities */

