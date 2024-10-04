/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    flash_driver.c
  * @author  MCD Application Team
  * @brief   The Flash Driver module is the interface layer between Flash
  *          management modules and HAL Flash drivers
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
#include "utilities_conf.h"
#include "flash_driver.h"
#include "stm32wb0x_hal_flash.h"
#include "ble.h"

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/

#define FD_CTRL_NO_BIT_SET   (0UL) /* value used to reset the Flash Control status */

#define WORD_WRITE_TIME_US       60                                               // In microsecond units
#define WORD_WRITE_TIME_SYS      ((int)(WORD_WRITE_TIME_US * 256 / 625) + 1)      // In system time units
#define QUAD_WORD_WRITE_TIME_US  180                                              // In microsecond units
#define QUAD_WORD_WRITE_TIME_SYS ((int)(QUAD_WORD_WRITE_TIME_US * 256 / 625) + 1)// In system time units
#define PAGE_ERASE_TIME_US       22000                                            // In microsecond units
#define PAGE_ERASE_TIME_SYS      ((int)(PAGE_ERASE_TIME_US * 256 / 625) + 1)      // In system time units

#define DEBUG_GPIO               0

/* Private macros ------------------------------------------------------------*/
#define ATOMIC_SECTION_BEGIN() uint32_t uwPRIMASK_Bit = __get_PRIMASK(); \
                                __disable_irq(); \
/* Must be called in the same scope of ATOMIC_SECTION_BEGIN */
#define ATOMIC_SECTION_END() __set_PRIMASK(uwPRIMASK_Bit)

#if DEBUG_GPIO
#define DEBUG_GPIO_HIGH()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET)
#define DEBUG_GPIO_LOW()    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET)
#else
#define DEBUG_GPIO_HIGH()
#define DEBUG_GPIO_LOW()
#endif
/* Private variables ---------------------------------------------------------*/

/**
 * @brief variable used to represent the Flash Control status
 */
static volatile FD_Flash_ctrl_bm_t FD_Flash_Control_status = FD_CTRL_NO_BIT_SET;

/* Private function prototypes -----------------------------------------------*/
static uint8_t FD_TimeCheck(int32_t time);

/* Functions Definition ------------------------------------------------------*/

/**
  * @brief  Update Flash Control status
  * @param  Flags_bm: Bit mask identifying the caller (1 bit per user)
  * @param  Status:   Action requested
  * @retval None
  */
void FD_SetStatus(FD_FlashAccess_bm_t Flags_bm, FD_FLASH_Status_t Status)
{
  UTILS_ENTER_CRITICAL_SECTION();

  switch (Status)
  {
    case FD_FLASH_ENABLE:
    {
      FD_Flash_Control_status |= (1u << Flags_bm);
      break;
    }
    case FD_FLASH_DISABLE:
    {
      FD_Flash_Control_status &= ~(1u << Flags_bm);
      break;
    }
    default :
    {
      break;
    }
  }

  UTILS_EXIT_CRITICAL_SECTION();
}

static uint8_t FD_TimeCheck(int32_t time)
{
  uint32_t current_time, next_radio_activity_time;

  current_time = HAL_RADIO_TIMER_GetCurrentSysTime();

  if(BLE_STACK_ReadNextRadioActivity(&next_radio_activity_time) == LL_IDLE)
    return TRUE;

  if((int32_t)(next_radio_activity_time - current_time) > time)
    return TRUE;

  return FALSE;
}

/**
  * @brief  Write a word (32-bit) in Flash
  * @param  Dest: Address where to write in Flash (128-bit aligned)
  * @param  Payload: Address of data to be written in Flash (32-bit aligned)
  * @retval FD_FlashOp_Status_t: Success or failure of Flash write operation
  */
FD_FlashOp_Status_t FD_WriteData32(uint32_t Dest, uint32_t *Payload)
{
  FD_FlashOp_Status_t status = FD_FLASHOP_FAILURE;

  ATOMIC_SECTION_BEGIN();

  DEBUG_GPIO_HIGH();

  if(FD_Flash_Control_status & (1u << FD_FLASHACCESS_RFTS_BYPASS) || FD_TimeCheck(QUAD_WORD_WRITE_TIME_SYS))
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Dest, *Payload) == HAL_OK)
    {
      status = FD_FLASHOP_SUCCESS;
    }
  }

  DEBUG_GPIO_LOW();

  ATOMIC_SECTION_END();

  return status;
}

/**
  * @brief  Write a block of 128 bits (4 32-bit words) in Flash
  * @param  Dest: Address where to write in Flash (128-bit aligned)
  * @param  Payload: Address of data to be written in Flash (32-bit aligned)
  * @retval FD_FlashOp_Status_t: Success or failure of Flash write operation
  */
FD_FlashOp_Status_t FD_WriteData128(uint32_t Dest, uint32_t *Payload)
{
  FD_FlashOp_Status_t status = FD_FLASHOP_FAILURE;

  ATOMIC_SECTION_BEGIN();

  DEBUG_GPIO_HIGH();

  if(FD_Flash_Control_status & (1u << FD_FLASHACCESS_RFTS_BYPASS) || FD_TimeCheck(QUAD_WORD_WRITE_TIME_SYS))
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BURST, Dest, (uint32_t) Payload) == HAL_OK)
    {
      status = FD_FLASHOP_SUCCESS;
    }
  }

  DEBUG_GPIO_LOW();

  ATOMIC_SECTION_END();

  return status;
}

/**
  * @brief  Erase one sector of Flash
  * @param  Sect: Identifier of the sector to erase
  * @retval FD_FlashOp_Status_t: Success or failure of Flash erase operation
  */
FD_FlashOp_Status_t FD_EraseSectors(uint32_t Sect)
{
  FD_FlashOp_Status_t status = FD_FLASHOP_FAILURE;
  uint32_t page_error;
  FLASH_EraseInitTypeDef p_erase_init;

  p_erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
  p_erase_init.Page = Sect;
  p_erase_init.NbPages = 1;

  ATOMIC_SECTION_BEGIN();

  DEBUG_GPIO_HIGH();

  if(FD_TimeCheck(PAGE_ERASE_TIME_SYS))
  {
    if (HAL_FLASHEx_Erase(&p_erase_init, &page_error) == HAL_OK)
    {
      status = FD_FLASHOP_SUCCESS;
    }
  }

  DEBUG_GPIO_LOW();

  ATOMIC_SECTION_END();

  return status;
}
