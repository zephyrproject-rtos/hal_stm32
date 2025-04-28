/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_nand.c
  * @author  MCD Application Team
  * @brief   NAND HAL module driver.
  *          This file provides a generic firmware to drive NAND memories mounted
  *          as external device.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                         ##### How to use this driver #####
  ==============================================================================
    [..]
      This driver is a generic layered driver which contains a set of APIs used to
      control NAND flash memories. It uses the FMC layer functions to interface
      with NAND devices. This driver is used as follows:

      (+) NAND flash memory configuration sequence using the function HAL_NAND_Init()
          with control and timing parameters for both common and attribute spaces.

      (+) Read NAND flash memory maker and device IDs using the function
          HAL_NAND_Read_ID(). The read information is stored in the NAND_ID_TypeDef
          structure declared by the function caller.

      (+) Access NAND flash memory by read/write operations using the functions
          HAL_NAND_Read_Page_8b()/HAL_NAND_Read_SpareArea_8b(),
          HAL_NAND_Write_Page_8b()/HAL_NAND_Write_SpareArea_8b(),
          HAL_NAND_Read_Page_16b()/HAL_NAND_Read_SpareArea_16b(),
          HAL_NAND_Write_Page_16b()/HAL_NAND_Write_SpareArea_16b()
          to read/write page(s)/spare area(s). These functions use specific device
          information (Block, page size..) predefined by the user in the NAND_DeviceConfigTypeDef
          structure. The read/write address information is contained by the Nand_Address_Typedef
          structure passed as parameter.

      (+) Perform NAND flash Reset chip operation using the function HAL_NAND_Reset().

      (+) Perform NAND flash erase block operation using the function HAL_NAND_Erase_Block().
          The erase block address information is contained in the Nand_Address_Typedef
          structure passed as parameter.

      (+) Read the NAND flash status operation using the function HAL_NAND_Read_Status().

      (+) You can also control the NAND device by calling the control APIs HAL_NAND_ECC_Enable()/
          HAL_NAND_ECC_Disable() to respectively enable/disable the ECC code correction
          feature or the function HAL_NAND_GetECC() to get the ECC correction code.

      (+) You can monitor the NAND device HAL state by calling the function
          HAL_NAND_GetState()

    [..]
      (@) This driver is a set of generic APIs which handle standard NAND flash operations.
          If a NAND flash device contains different operations and/or implementations,
          it should be implemented separately.

    *** Callback registration ***
    =============================================
    [..]
      The compilation define  USE_HAL_NAND_REGISTER_CALLBACKS when set to 1
      allows the user to configure dynamically the driver callbacks.

      Use Functions @ref HAL_NAND_RegisterCallback() to register a user callback,
      it allows to register following callbacks:
        (+) MspInitCallback    : NAND MspInit.
        (+) MspDeInitCallback  : NAND MspDeInit.
      This function takes as parameters the HAL peripheral handle, the Callback ID
      and a pointer to the user callback function.

      Use function @ref HAL_NAND_UnRegisterCallback() to reset a callback to the default
      weak (surcharged) function. It allows to reset following callbacks:
        (+) MspInitCallback    : NAND MspInit.
        (+) MspDeInitCallback  : NAND MspDeInit.
      This function) takes as parameters the HAL peripheral handle and the Callback ID.

      By default, after the @ref HAL_NAND_Init and if the state is HAL_NAND_STATE_RESET
      all callbacks are reset to the corresponding legacy weak (surcharged) functions.
      Exception done for MspInit and MspDeInit callbacks that are respectively
      reset to the legacy weak (surcharged) functions in the @ref HAL_NAND_Init
      and @ref  HAL_NAND_DeInit only when these callbacks are null (not registered beforehand).
      If not, MspInit or MspDeInit are not null, the @ref HAL_NAND_Init and @ref HAL_NAND_DeInit
      keep and use the user MspInit/MspDeInit callbacks (registered beforehand)

      Callbacks can be registered/unregistered in READY state only.
      Exception done for MspInit/MspDeInit callbacks that can be registered/unregistered
      in READY or RESET state, thus registered (user) MspInit/DeInit callbacks can be used
      during the Init/DeInit.
      In that case first register the MspInit/MspDeInit user callbacks
      using @ref HAL_NAND_RegisterCallback before calling @ref HAL_NAND_DeInit
      or @ref HAL_NAND_Init function.

      When The compilation define USE_HAL_NAND_REGISTER_CALLBACKS is set to 0 or
      not defined, the callback registering feature is not available
      and weak (surcharged) callbacks are used.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>


/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

#ifdef HAL_NAND_MODULE_ENABLED

/** @defgroup NAND NAND
  * @brief NAND HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private Constants ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define NAND_BUS_WIDTH_8 FMC_NAND_MEM_BUS_WIDTH_8

#define NAND_PAGE_SIZE_512 512U
#define NAND_MAX_PAGES_FOR_16BIT_ADDRESS 65535U

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static inline uint32_t HAL_NAND_GetDeviceAddress(NAND_HandleTypeDef *hnand)
{
  UNUSED(hnand);
  return NAND_DEVICE | hnand->ChipSelect;
}

/* Exported functions ---------------------------------------------------------*/

/** @defgroup NAND_Exported_Functions NAND Exported Functions
  * @{
  */

/** @defgroup NAND_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### NAND Initialization and de-initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to initialize/de-initialize
    the NAND memory

@endverbatim
  * @{
  */

/**
  * @brief  Perform NAND memory Initialization sequence
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  ComSpace_Timing pointer to Common space timing structure
  * @param  AttSpace_Timing pointer to Attribute space timing structure
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_Init(NAND_HandleTypeDef *hnand, FMC_NAND_PCC_TimingTypeDef *ComSpace_Timing,
                                 FMC_NAND_PCC_TimingTypeDef *AttSpace_Timing)
{
  /* Check the NAND handle state */
  if (hnand == NULL)
  {
    return HAL_ERROR;
  }

  if (hnand->State == HAL_NAND_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hnand->Lock = HAL_UNLOCKED;

    /* Default TimeOut for most operations in milliseconds */
    hnand->TimeOut = HAL_NAND_DEFAULT_TIMEOUT;

    /* Default chip select */
    hnand->ChipSelect = NAND_NCE1_OFFSET;

#if (USE_HAL_NAND_REGISTER_CALLBACKS == 1)
    if (hnand->MspInitCallback == NULL)
    {
      hnand->MspInitCallback = HAL_NAND_MspInit;
    }
    hnand->ItCallback = HAL_NAND_ITCallback;

    /* Init the low level hardware */
    hnand->MspInitCallback(hnand);
#else
    /* Initialize the low level hardware (MSP) */
    HAL_NAND_MspInit(hnand);
#endif /* USE_HAL_NAND_REGISTER_CALLBACKS */

    /* Compute the device address using the bank and the chip select */
    hnand->DeviceAddress = HAL_NAND_GetDeviceAddress(hnand);
  }

  /* Initialize NAND control Interface */
  (void)FMC_NAND_Init(hnand->Instance, &(hnand->Init));

  /* Initialize NAND common space timing Interface */
  (void)FMC_NAND_CommonSpace_Timing_Init(hnand->Instance, ComSpace_Timing, hnand->Init.NandBank);

  /* Initialize NAND attribute space timing Interface */
  (void)FMC_NAND_AttributeSpace_Timing_Init(hnand->Instance, AttSpace_Timing, hnand->Init.NandBank);

  /* Enable the NAND device */
  __FMC_NAND_ENABLE(hnand->Instance);

  /* Enable FMC Peripheral */
  __FMC_ENABLE();

  /* Update the NAND controller state */
  hnand->State = HAL_NAND_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  Perform NAND memory De-Initialization sequence
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_DeInit(NAND_HandleTypeDef *hnand)
{
#if (USE_HAL_NAND_REGISTER_CALLBACKS == 1)
  if (hnand->MspDeInitCallback == NULL)
  {
    hnand->MspDeInitCallback = HAL_NAND_MspDeInit;
  }

  /* DeInit the low level hardware */
  hnand->MspDeInitCallback(hnand);
#else
  /* Initialize the low level hardware (MSP) */
  HAL_NAND_MspDeInit(hnand);
#endif /* USE_HAL_NAND_REGISTER_CALLBACKS */

  /* Configure the NAND registers with their reset values */
  (void)FMC_NAND_DeInit(hnand->Instance, hnand->Init.NandBank);

  /* Reset the NAND controller state */
  hnand->State = HAL_NAND_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hnand);

  return HAL_OK;
}

/**
  * @brief  NAND MSP Init
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval None
  */
__weak void HAL_NAND_MspInit(NAND_HandleTypeDef *hnand)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hnand);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_NAND_MspInit could be implemented in the user file
   */
}

/**
  * @brief  NAND MSP DeInit
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval None
  */
__weak void HAL_NAND_MspDeInit(NAND_HandleTypeDef *hnand)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hnand);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_NAND_MspDeInit could be implemented in the user file
   */
}


/**
  * @brief  This function handles NAND device interrupt request.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
void HAL_NAND_IRQHandler(NAND_HandleTypeDef *hnand)
{
  /* Check NAND interrupt Rising edge flag */
  if (__FMC_NAND_GET_FLAG(hnand->Instance, hnand->Init.NandBank, FMC_FLAG_RISING_EDGE))
  {
    /* NAND interrupt callback*/
#if (USE_HAL_NAND_REGISTER_CALLBACKS == 1)
    hnand->ItCallback(hnand);
#else
    HAL_NAND_ITCallback(hnand);
#endif /* USE_HAL_NAND_REGISTER_CALLBACKS */

    /* Clear NAND interrupt Rising edge pending bit */
    __FMC_NAND_CLEAR_FLAG(hnand->Instance, FMC_FLAG_RISING_EDGE);
  }

  /* Check NAND interrupt Level flag */
  if (__FMC_NAND_GET_FLAG(hnand->Instance, hnand->Init.NandBank, FMC_FLAG_LEVEL))
  {
    /* NAND interrupt callback*/
#if (USE_HAL_NAND_REGISTER_CALLBACKS == 1)
    hnand->ItCallback(hnand);
#else
    HAL_NAND_ITCallback(hnand);
#endif /* USE_HAL_NAND_REGISTER_CALLBACKS */

    /* Clear NAND interrupt Level pending bit */
    __FMC_NAND_CLEAR_FLAG(hnand->Instance, FMC_FLAG_LEVEL);
  }

  /* Check NAND interrupt Falling edge flag */
  if (__FMC_NAND_GET_FLAG(hnand->Instance, hnand->Init.NandBank, FMC_FLAG_FALLING_EDGE))
  {
    /* NAND interrupt callback*/
#if (USE_HAL_NAND_REGISTER_CALLBACKS == 1)
    hnand->ItCallback(hnand);
#else
    HAL_NAND_ITCallback(hnand);
#endif /* USE_HAL_NAND_REGISTER_CALLBACKS */

    /* Clear NAND interrupt Falling edge pending bit */
    __FMC_NAND_CLEAR_FLAG(hnand->Instance, FMC_FLAG_FALLING_EDGE);
  }

  /* Check NAND interrupt FIFO empty flag */
  if (__FMC_NAND_GET_FLAG(hnand->Instance, hnand->Init.NandBank, FMC_FLAG_FEMPT))
  {
    /* NAND interrupt callback*/
#if (USE_HAL_NAND_REGISTER_CALLBACKS == 1)
    hnand->ItCallback(hnand);
#else
    HAL_NAND_ITCallback(hnand);
#endif /* USE_HAL_NAND_REGISTER_CALLBACKS */

    /* Clear NAND interrupt FIFO empty pending bit */
    __FMC_NAND_CLEAR_FLAG(hnand->Instance, FMC_FLAG_FEMPT);
  }

}

/**
  * @brief  NAND interrupt feature callback
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval None
  */
__weak void HAL_NAND_ITCallback(NAND_HandleTypeDef *hnand)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hnand);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_NAND_ITCallback could be implemented in the user file
   */
}

/**
  * @}
  */

/** @defgroup NAND_Exported_Functions_Group2 Input and Output functions
  * @brief    Input Output and memory control functions
  *
  @verbatim
  ==============================================================================
                    ##### NAND Input and Output functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to use and control the NAND
    memory

@endverbatim
  * @{
  */

#define NAND_AREA_USER 0
#define NAND_AREA_SPARE 1

static uint32_t HAL_NAND_ComputeWordsToBytes(uint32_t ColumnAddressInWords, uint32_t MemoryDataWidth)
{
  return (MemoryDataWidth == NAND_BUS_WIDTH_8) ? ColumnAddressInWords : ColumnAddressInWords * 2U;
}

static void HAL_NAND_WriteCommand(NAND_HandleTypeDef *restrict hnand, uint8_t Data)
{
  *(__IO uint8_t *)((uint32_t)(hnand->DeviceAddress | NAND_CMD_OFFSET)) = Data;
  __DSB();
}

static void HAL_NAND_WriteAddress(NAND_HandleTypeDef *restrict hnand, uint8_t Data)
{
  *(__IO uint8_t *)((uint32_t)(hnand->DeviceAddress | NAND_ADDR_OFFSET)) = Data;
  __DSB();
}

static uint32_t HAL_NAND_ReadData8(NAND_HandleTypeDef *restrict hnand)
{
  uint32_t data = *(__IO uint8_t *)(hnand->DeviceAddress);
  __DSB();
  return data;
}

static uint32_t HAL_NAND_ReadData32(NAND_HandleTypeDef *restrict hnand)
{
  uint32_t data = *(__IO uint32_t *)(hnand->DeviceAddress);
  __DSB();
  return data;
}

static uint32_t HAL_NAND_Read_Status_Internal(NAND_HandleTypeDef *hnand)
{
  uint32_t nandStatus;
  uint32_t data;

  /* Send Read status operation command */
  HAL_NAND_WriteCommand(hnand, NAND_CMD_STATUS);

  /* Read status register data */
  data = HAL_NAND_ReadData8(hnand);

  /* Return the status */
  if ((data & NAND_ERROR) == NAND_ERROR)
  {
    nandStatus = NAND_ERROR;
  }
  else if ((data & NAND_READY) == NAND_READY)
  {
    nandStatus = NAND_READY;
  }
  else
  {
    nandStatus = NAND_BUSY;
  }

  return nandStatus;
}

static HAL_StatusTypeDef HAL_NAND_WaitReady(NAND_HandleTypeDef *hnand, uint32_t TimeOut)
{
  uint32_t nandStatus;
  /* Get tick */
  uint32_t tickstart = HAL_GetTick();

  /* Read status until NAND is ready */
  do
  {
    nandStatus = HAL_NAND_Read_Status_Internal(hnand);
    if (nandStatus != NAND_BUSY)
    {
      if (nandStatus == NAND_READY)
      {
        return HAL_OK;
      }
      else
      {
        return HAL_ERROR;
      }
    }
  } while ((HAL_GetTick() - tickstart) <= TimeOut);

  hnand->State = HAL_NAND_STATE_ERROR;
  hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
  return HAL_TIMEOUT;
}

static void HAL_NAND_SetAddress(NAND_HandleTypeDef *restrict hnand, uint32_t NandAddress, uint32_t ColumnAddress)
{
  uint32_t totalPageNumber = hnand->Config.BlockSize * hnand->Config.BlockNbr;
  uint32_t columnAddressInBytes = HAL_NAND_ComputeWordsToBytes(ColumnAddress, hnand->Init.MemoryDataWidth);

  /* Cards with page size <= 512 bytes */
  if ((hnand->Config.PageSize) <= NAND_PAGE_SIZE_512)
  {
    HAL_NAND_WriteAddress(hnand, 0x00U);
    HAL_NAND_WriteAddress(hnand, ADDR_1ST_CYCLE(NandAddress));
    HAL_NAND_WriteAddress(hnand, ADDR_2ND_CYCLE(NandAddress));
    if (totalPageNumber > NAND_MAX_PAGES_FOR_16BIT_ADDRESS)
    {
      HAL_NAND_WriteAddress(hnand, ADDR_3RD_CYCLE(NandAddress));
    }
  }
  else /* (hnand->Config.PageSize) > 512 */
  {
    HAL_NAND_WriteAddress(hnand, COLUMN_1ST_CYCLE(columnAddressInBytes));
    HAL_NAND_WriteAddress(hnand, COLUMN_2ND_CYCLE(columnAddressInBytes));
    HAL_NAND_WriteAddress(hnand, ADDR_1ST_CYCLE(NandAddress));
    HAL_NAND_WriteAddress(hnand, ADDR_2ND_CYCLE(NandAddress));
    if (totalPageNumber > NAND_MAX_PAGES_FOR_16BIT_ADDRESS)
    {
      HAL_NAND_WriteAddress(hnand, ADDR_3RD_CYCLE(NandAddress));
    }
  }
}

static HAL_StatusTypeDef HAL_NAND_ReadBegin(NAND_HandleTypeDef *restrict hnand, uint32_t NandAddress,
                                            uint32_t ColumnAddress)
{
  HAL_StatusTypeDef status;

  HAL_NAND_WriteCommand(hnand, NAND_CMD_AREA_A);
  HAL_NAND_SetAddress(hnand, NandAddress, ColumnAddress);
  HAL_NAND_WriteCommand(hnand, NAND_CMD_AREA_TRUE1);

  if (hnand->Config.ExtraCommandEnable == ENABLE)
  {
    status = HAL_NAND_WaitReady(hnand, NAND_READ_BEGIN_TIMEOUT);
    if ((status != HAL_OK) && (status != HAL_ERROR))
    {
      return status;
    }

    /* Go back to read mode */
    HAL_NAND_WriteCommand(hnand, NAND_CMD_AREA_A);
  }

  return HAL_OK;
}

static void HAL_NAND_WriteBegin(NAND_HandleTypeDef *restrict hnand, uint32_t NandAddress, uint32_t ColumnAddress,
                                uint32_t Area)
{
  /* The following line is not needed for recent NANDs. */
  HAL_NAND_WriteCommand(hnand, (Area == (uint32_t)NAND_AREA_SPARE) && (hnand->Config.PageSize <= NAND_PAGE_SIZE_512) ?
                        NAND_CMD_AREA_C : NAND_CMD_AREA_A);

  HAL_NAND_WriteCommand(hnand, NAND_CMD_WRITE0);
  HAL_NAND_SetAddress(hnand, NandAddress, ColumnAddress);
}

static HAL_StatusTypeDef HAL_NAND_WriteEnd(NAND_HandleTypeDef *restrict hnand)
{
  HAL_NAND_WriteCommand(hnand, NAND_CMD_WRITE_TRUE1);
  return HAL_NAND_WaitReady(hnand, NAND_WRITE_END_TIMEOUT);
}

static void HAL_NAND_ChangeReadColumn(NAND_HandleTypeDef *restrict hnand, uint32_t ColumnAddress)
{
  uint32_t columnAddressInBytes = HAL_NAND_ComputeWordsToBytes(ColumnAddress, hnand->Init.MemoryDataWidth);
  HAL_NAND_WriteCommand(hnand, NAND_CMD_RANDOM_OUTPUT_0);
  HAL_NAND_WriteAddress(hnand, COLUMN_1ST_CYCLE(columnAddressInBytes));
  HAL_NAND_WriteAddress(hnand, COLUMN_2ND_CYCLE(columnAddressInBytes));
  HAL_NAND_WriteCommand(hnand, NAND_CMD_RANDOM_OUTPUT_1);
}

static void HAL_NAND_ChangeWriteColumn(NAND_HandleTypeDef *restrict hnand, uint32_t ColumnAddress)
{
  uint32_t columnAddressInBytes = HAL_NAND_ComputeWordsToBytes(ColumnAddress, hnand->Init.MemoryDataWidth);
  HAL_NAND_WriteCommand(hnand, NAND_CMD_RANDOM_INPUT);
  HAL_NAND_WriteAddress(hnand, COLUMN_1ST_CYCLE(columnAddressInBytes));
  HAL_NAND_WriteAddress(hnand, COLUMN_2ND_CYCLE(columnAddressInBytes));
}

static void HAL_NAND_ReadFromDevice8(uint32_t DeviceAddress, uint32_t Size, uint8_t *pBuffer)
{
  uint32_t index;
  for (index = 0U; index < Size; index++)
  {
    pBuffer[index] = *(__IO uint8_t *)DeviceAddress;
    __DSB();
  }
}

static void HAL_NAND_ReadFromDevice16(uint32_t DeviceAddress, uint32_t Size, uint16_t *pBuffer)
{
  uint32_t index;
  for (index = 0U; index < Size; index++)
  {
    pBuffer[index] = *(__IO uint16_t *)DeviceAddress;
    __DSB();
  }
}

static void HAL_NAND_ReadFromDevice(NAND_HandleTypeDef *restrict hnand, uint32_t Size, void *pBuffer, uint32_t Offset)
{
  if (hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8)
  {
    HAL_NAND_ReadFromDevice8(hnand->DeviceAddress, Size, &((uint8_t *)pBuffer)[Offset]);
  }
  else
  {
    HAL_NAND_ReadFromDevice16(hnand->DeviceAddress, Size, &((uint16_t *)pBuffer)[Offset]);
  }
}

static void HAL_NAND_WriteToDevice8(uint32_t DeviceAddress, uint32_t Size, uint8_t *pBuffer)
{
  uint32_t index;
  for (index = 0U; index < Size; index++)
  {
    *(__IO uint8_t *)DeviceAddress = pBuffer[index];
    __DSB();
  }
}

static void HAL_NAND_WriteToDevice16(uint32_t DeviceAddress, uint32_t Size, uint16_t *pBuffer)
{
  uint32_t index;
  for (index = 0U; index < Size; index++)
  {
    *(__IO uint16_t *)DeviceAddress = pBuffer[index];
    __DSB();
  }
}

static void HAL_NAND_WriteToDevice(NAND_HandleTypeDef *restrict hnand, uint32_t Size, void *pBuffer, uint32_t Offset)
{
  if (hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8)
  {
    HAL_NAND_WriteToDevice8(hnand->DeviceAddress, Size, &((uint8_t *)pBuffer)[Offset]);
  }
  else
  {
    HAL_NAND_WriteToDevice16(hnand->DeviceAddress, Size, &((uint16_t *)pBuffer)[Offset]);
  }
}

/**
  * @brief  Read the NAND memory electronic signature
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pNAND_ID NAND ID structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_ID(NAND_HandleTypeDef *hnand, NAND_IDTypeDef *pNAND_ID)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t data = 0;
  uint32_t data1 = 0;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Send Read ID command sequence */
    HAL_NAND_WriteCommand(hnand, NAND_CMD_READID);
    HAL_NAND_WriteAddress(hnand, 0x00);

    /* Read the electronic signature from NAND flash */
    if (hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8)
    {
      data = HAL_NAND_ReadData32(hnand);

      /* Return the data read */
      pNAND_ID->Maker_Id   = ADDR_1ST_CYCLE(data);
      pNAND_ID->Device_Id  = ADDR_2ND_CYCLE(data);
      pNAND_ID->Third_Id   = ADDR_3RD_CYCLE(data);
      pNAND_ID->Fourth_Id  = ADDR_4TH_CYCLE(data);
    }
    else
    {
      data = HAL_NAND_ReadData32(hnand);
      data1 = HAL_NAND_ReadData32(hnand);

      /* Return the data read */
      pNAND_ID->Maker_Id   = ADDR_1ST_CYCLE(data);
      pNAND_ID->Device_Id  = ADDR_3RD_CYCLE(data);
      pNAND_ID->Third_Id   = ADDR_1ST_CYCLE(data1);
      pNAND_ID->Fourth_Id  = ADDR_3RD_CYCLE(data1);
    }

    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  NAND memory reset
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Reset(NAND_HandleTypeDef *hnand)
{
  HAL_StatusTypeDef status;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Send NAND reset command */
    HAL_NAND_WriteCommand(hnand, NAND_CMD_RESET);

    status = HAL_NAND_WaitReady(hnand, NAND_RESET_TIMEOUT);
    if (status == HAL_OK)
    {
      /* Update the NAND controller state */
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Configure the device: Enter the physical parameters of the device
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pDeviceConfig  pointer to NAND_DeviceConfigTypeDef structure
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ConfigDevice(NAND_HandleTypeDef *hnand, NAND_DeviceConfigTypeDef *pDeviceConfig)
{
  hnand->Config.PageSize           = pDeviceConfig->PageSize;
  hnand->Config.SpareAreaSize      = pDeviceConfig->SpareAreaSize;
  hnand->Config.BlockSize          = pDeviceConfig->BlockSize;
  hnand->Config.BlockNbr           = pDeviceConfig->BlockNbr;
  hnand->Config.PlaneSize          = pDeviceConfig->PlaneSize;
  hnand->Config.PlaneNbr           = pDeviceConfig->PlaneNbr;
  hnand->Config.ExtraCommandEnable = pDeviceConfig->ExtraCommandEnable;

  return HAL_OK;
}

/**
  * @brief  Read Page(s) from NAND memory block
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  NumPagesToRead  number of pages to read from block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                     uint32_t NumPagesToRead)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t bufferOffset = 0;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  uint32_t numPagesRead = 0;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Page(s) read loop */
    while ((numPagesRead < NumPagesToRead) && (nandAddress < nandAddressMax))
    {
      /* Begin reading */
      status = HAL_NAND_ReadBegin(hnand, nandAddress, 0);
      if (status != HAL_OK)
      {
        break;
      }

      /* Get data into Buffer */
      HAL_NAND_ReadFromDevice(hnand, hnand->Config.PageSize, pBuffer, bufferOffset);
      bufferOffset += hnand->Config.PageSize;

      /* Increment read pages number */
      numPagesRead++;

      /* Increment the NAND address */
      nandAddress = (uint32_t)(nandAddress + 1U);
    }

    if (status == HAL_OK)
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Read Page(s) from NAND memory block (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  NumPagesToRead  number of pages to read from block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                        uint32_t NumPagesToRead)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_Page(hnand, pAddress, pBuffer, NumPagesToRead);
}

/**
  * @brief  Read Page(s) from NAND memory block (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer. pBuffer should be 16-bit aligned
  * @param  NumPagesToRead  number of pages to read from block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint16_t *pBuffer,
                                         uint32_t NumPagesToRead)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_Page(hnand, pAddress, pBuffer, NumPagesToRead);
}

/**
  * @brief  Read in a single page from NAND memory block
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  Offset  offset in the page
  * @param  Length  length to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SinglePage(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                           uint32_t Offset, uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  assert_param((Offset + Length) <= hnand->Config.PageSize);

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Page(s) read loop */
    if (nandAddress < nandAddressMax)
    {
      /* Begin reading */
      status = HAL_NAND_ReadBegin(hnand, nandAddress, Offset);
      if (status == HAL_OK)
      {
        /* Get data into buffer */
        HAL_NAND_ReadFromDevice(hnand, Length, pBuffer, 0);
      }
    }

    if (status == HAL_OK)
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Read in a single page from NAND memory block (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  Offset  offset in the page
  * @param  Length  length to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SinglePage_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                              uint8_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_SinglePage(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  Read in a single page from NAND memory block (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer. pBuffer should be 16-bit aligned
  * @param  Offset  offset in the page
  * @param  Length  length to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SinglePage_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                               uint16_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_SinglePage(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  Write Page(s) to NAND memory block
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumPagesToWrite  number of pages to write to block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                      uint32_t NumPagesToWrite)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t bufferOffset = 0;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  uint32_t numPagesWritten = 0;

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Page(s) write loop */
    while ((numPagesWritten < NumPagesToWrite) && (nandAddress < nandAddressMax))
    {
      /* Begin writing */
      HAL_NAND_WriteBegin(hnand, nandAddress, 0, NAND_AREA_USER);

      /* Write data to memory */
      HAL_NAND_WriteToDevice(hnand, hnand->Config.PageSize, pBuffer, bufferOffset);
      bufferOffset += hnand->Config.PageSize;

      /* End writing */
      status = HAL_NAND_WriteEnd(hnand);
      if (status == HAL_ERROR)
      {
        hnand->State = HAL_NAND_STATE_READY;
        break;
      }
      else if (status != HAL_OK)
      {
        break;
      }

      /* Increment written pages number */
      numPagesWritten++;

      /* Increment the NAND address */
      nandAddress = (uint32_t)(nandAddress + 1U);
    }

    if (status == HAL_OK)
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Write Page(s) to NAND memory block (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumPagesToWrite  number of pages to write to block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                         uint32_t NumPagesToWrite)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_Page(hnand, pAddress, pBuffer, NumPagesToWrite);
}

/**
  * @brief  Write Page(s) to NAND memory block (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write. pBuffer should be 16-bit aligned
  * @param  NumPagesToWrite   number of pages to write to block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint16_t *pBuffer,
                                          uint32_t NumPagesToWrite)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_Page(hnand, pAddress, pBuffer, NumPagesToWrite);
}

/**
  * @brief  Write in a single page to NAND memory block
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  Offset  offset in the page
  * @param  Length  length to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SinglePage(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                            uint32_t Offset, uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  assert_param((Offset + Length) <= hnand->Config.PageSize);

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Page(s) write loop */
    if (nandAddress < nandAddressMax)
    {
      /* Begin writing */
      HAL_NAND_WriteBegin(hnand, nandAddress, Offset, NAND_AREA_USER);

      /* Write data to memory */
      HAL_NAND_WriteToDevice(hnand, Length, pBuffer, 0);

      /* End writing */
      status = HAL_NAND_WriteEnd(hnand);
    }

    if ((status == HAL_OK) || (status == HAL_ERROR))
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Write in a single page to NAND memory block (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  Offset  offset in the page
  * @param  Length  length to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SinglePage_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                               uint8_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_SinglePage(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  Write in a single page to NAND memory block (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write. pBuffer should be 16-bit aligned
  * @param  Offset  offset in the page
  * @param  Length  length to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SinglePage_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                uint16_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_SinglePage(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  Read Spare area(s) from NAND memory
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer pointer to source buffer to write
  * @param  NumSpareAreasToRead Number of spare area to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SpareArea(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                          uint32_t NumSpareAreasToRead)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t bufferOffset = 0;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  uint32_t numSpareAreaRead = 0;

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Spare area(s) read loop */
    while ((numSpareAreaRead < NumSpareAreasToRead) && (nandAddress < nandAddressMax))
    {
      /* Begin reading */
      status = HAL_NAND_ReadBegin(hnand, nandAddress, SPARE_AREA_COLUMN_ADDRESS(hnand));
      if (status != HAL_OK)
      {
        break;
      }

      /* Get data into Buffer */
      HAL_NAND_ReadFromDevice(hnand, hnand->Config.SpareAreaSize, pBuffer, bufferOffset);
      bufferOffset += hnand->Config.SpareAreaSize;

      /* Increment read spare areas number */
      numSpareAreaRead++;

      /* Increment the NAND address */
      nandAddress = (uint32_t)(nandAddress + 1U);
    }

    if (status == HAL_OK)
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Read Spare area(s) from NAND memory (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer pointer to source buffer to write
  * @param  NumSpareAreasToRead Number of spare area to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SpareArea_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                             uint32_t NumSpareAreasToRead)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_SpareArea(hnand, pAddress, pBuffer, NumSpareAreasToRead);
}

/**
  * @brief  Read spare area(s) from NAND memory (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer pointer to source buffer to write. pBuffer should be 16-bit aligned.
  * @param  NumSpareAreasToRead Number of spare area to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SpareArea_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                              uint16_t *pBuffer, uint32_t NumSpareAreasToRead)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_SpareArea(hnand, pAddress, pBuffer, NumSpareAreasToRead);
}

/**
  * @brief  Read in a single spare area from NAND memory block
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer pointer to source buffer to write
  * @param  Offset  offset in the page
  * @param  Length  length to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SingleSpareArea(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                                uint32_t Offset, uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  assert_param((Offset + Length) <= hnand->Config.PageSize);

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Spare area(s) read loop */
    if (nandAddress < nandAddressMax)
    {
      /* Begin reading */
      status = HAL_NAND_ReadBegin(hnand, nandAddress, SPARE_AREA_COLUMN_ADDRESS(hnand) + Offset);
      if (status == HAL_OK)
      {
        /* Get data into Buffer */
        HAL_NAND_ReadFromDevice(hnand, Length, pBuffer, 0);
      }
    }

    if (status == HAL_OK)
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Read in a single spare area from NAND memory block (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer pointer to source buffer to write
  * @param  Offset  offset in the page
  * @param  Length  length to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SingleSpareArea_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                   uint8_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_SingleSpareArea(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  Read in a single spare area from NAND memory block (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer pointer to source buffer to write. pBuffer should be 16-bit aligned.
  * @param  Offset  offset in the page
  * @param  Length  length to read
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Read_SingleSpareArea_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                    uint16_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Read_SingleSpareArea(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  Write Spare area(s) to NAND memory
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumSpareAreasTowrite   number of spare areas to write to block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SpareArea(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                           uint32_t NumSpareAreasTowrite)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t bufferOffset = 0;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  uint32_t numSpareAreasWritten = 0;

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Page address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Spare area(s) write loop */
    while ((numSpareAreasWritten < NumSpareAreasTowrite) && (nandAddress < nandAddressMax))
    {
      /* Begin writing */
      HAL_NAND_WriteBegin(hnand, nandAddress, SPARE_AREA_COLUMN_ADDRESS(hnand), NAND_AREA_SPARE);

      /* Write data to memory */
      HAL_NAND_WriteToDevice(hnand, hnand->Config.SpareAreaSize, pBuffer, bufferOffset);
      bufferOffset += hnand->Config.SpareAreaSize;

      /* End writing */
      status = HAL_NAND_WriteEnd(hnand);
      if (status == HAL_ERROR)
      {
        hnand->State = HAL_NAND_STATE_READY;
        break;
      }
      else if (status != HAL_OK)
      {
        break;
      }

      /* Increment written spare areas number */
      numSpareAreasWritten++;

      /* Increment the NAND address */
      nandAddress = (uint32_t)(nandAddress + 1U);
    }

    if (status == HAL_OK)
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Write Spare area(s) to NAND memory (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumSpareAreasTowrite   number of spare areas to write to block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SpareArea_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                              uint8_t *pBuffer, uint32_t NumSpareAreasTowrite)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_SpareArea(hnand, pAddress, pBuffer, NumSpareAreasTowrite);
}

/**
  * @brief  Write Spare area(s) to NAND memory (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write. pBuffer should be 16-bit aligned.
  * @param  NumSpareAreasTowrite   number of spare areas to write to block
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SpareArea_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                               uint16_t *pBuffer, uint32_t NumSpareAreasTowrite)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_SpareArea(hnand, pAddress, pBuffer, NumSpareAreasTowrite);
}

/**
  * @brief  Write in a single spare area to NAND memory block
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  Offset  offset in the page
  * @param  Length  length to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SingleSpareArea(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                 void *pBuffer, uint32_t Offset, uint32_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  assert_param((Offset + Length) <= hnand->Config.SpareAreaSize);

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Page address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Spare area(s) write loop */
    if (nandAddress < nandAddressMax)
    {
      /* Begin writing */
      HAL_NAND_WriteBegin(hnand, nandAddress, SPARE_AREA_COLUMN_ADDRESS(hnand) + Offset, NAND_AREA_SPARE);

      /* Write data to memory */
      HAL_NAND_WriteToDevice(hnand, Length, pBuffer, 0);

      /* End writing */
      status = HAL_NAND_WriteEnd(hnand);
    }

    if ((status == HAL_OK) || (status == HAL_ERROR))
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Write in a single spare area to NAND memory block (8-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  Offset  offset in the page
  * @param  Length  length to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SingleSpareArea_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                    uint8_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_SingleSpareArea(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  Write in a single spare area to NAND memory block (16-bit addressing)
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write. pBuffer should be 16-bit aligned.
  * @param  Offset  offset in the page
  * @param  Length  length to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Write_SingleSpareArea_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                     uint16_t *pBuffer, uint32_t Offset, uint32_t Length)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Write_SingleSpareArea(hnand, pAddress, pBuffer, Offset, Length);
}

/**
  * @brief  NAND memory Block erase
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Erase_Block(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress)
{
  HAL_StatusTypeDef status;
  uint32_t nandAddress;

  /* Process locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);

    /* Send Erase block command sequence */
    HAL_NAND_WriteCommand(hnand, NAND_CMD_ERASE0);
    HAL_NAND_WriteAddress(hnand, ADDR_1ST_CYCLE(nandAddress));
    HAL_NAND_WriteAddress(hnand, ADDR_2ND_CYCLE(nandAddress));
    HAL_NAND_WriteAddress(hnand, ADDR_3RD_CYCLE(nandAddress));
    HAL_NAND_WriteCommand(hnand, NAND_CMD_ERASE1);

    /* Wait end of erase */
    status = HAL_NAND_WaitReady(hnand, NAND_ERASE_BLOCK_TIMEOUT);
    if ((status == HAL_OK) || (status == HAL_ERROR))
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Increment the NAND memory address
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param pAddress pointer to NAND address structure
  * @retval The new status of the increment address operation. It can be:
  *           - NAND_VALID_ADDRESS: When the new address is valid address
  *           - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t HAL_NAND_Address_Inc(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress)
{
  uint32_t status = NAND_VALID_ADDRESS;

  /* Increment page address */
  pAddress->Page++;

  /* Check NAND address is valid */
  if (pAddress->Page == hnand->Config.BlockSize)
  {
    pAddress->Page = 0;
    pAddress->Block++;

    if (pAddress->Block == hnand->Config.PlaneSize)
    {
      pAddress->Block = 0;
      pAddress->Plane++;

      if (pAddress->Plane == (hnand->Config.PlaneNbr))
      {
        status = NAND_INVALID_ADDRESS;
      }
    }
  }

  return status;
}

#if (USE_HAL_NAND_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User NAND Callback
  *         To be used instead of the weak (surcharged) predefined callback
  * @param hnand : NAND handle
  * @param CallbackId : ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_NAND_MSP_INIT_CB_ID       NAND MspInit callback ID
  *          @arg @ref HAL_NAND_MSP_DEINIT_CB_ID     NAND MspDeInit callback ID
  *          @arg @ref HAL_NAND_IT_CB_ID             NAND IT callback ID
  * @param pCallback : pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_NAND_RegisterCallback(NAND_HandleTypeDef *hnand, HAL_NAND_CallbackIDTypeDef CallbackId,
                                            pNAND_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    switch (CallbackId)
    {
      case HAL_NAND_MSP_INIT_CB_ID :
        hnand->MspInitCallback = pCallback;
        break;
      case HAL_NAND_MSP_DEINIT_CB_ID :
        hnand->MspDeInitCallback = pCallback;
        break;
      case HAL_NAND_IT_CB_ID :
        hnand->ItCallback = pCallback;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hnand->State == HAL_NAND_STATE_RESET)
  {
    switch (CallbackId)
    {
      case HAL_NAND_MSP_INIT_CB_ID :
        hnand->MspInitCallback = pCallback;
        break;
      case HAL_NAND_MSP_DEINIT_CB_ID :
        hnand->MspDeInitCallback = pCallback;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Unregister a User NAND Callback
  *         NAND Callback is redirected to the weak (surcharged) predefined callback
  * @param hnand : NAND handle
  * @param CallbackId : ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_NAND_MSP_INIT_CB_ID       NAND MspInit callback ID
  *          @arg @ref HAL_NAND_MSP_DEINIT_CB_ID     NAND MspDeInit callback ID
  *          @arg @ref HAL_NAND_IT_CB_ID             NAND IT callback ID
  * @retval status
  */
HAL_StatusTypeDef HAL_NAND_UnRegisterCallback(NAND_HandleTypeDef *hnand, HAL_NAND_CallbackIDTypeDef CallbackId)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    switch (CallbackId)
    {
      case HAL_NAND_MSP_INIT_CB_ID :
        hnand->MspInitCallback = HAL_NAND_MspInit;
        break;
      case HAL_NAND_MSP_DEINIT_CB_ID :
        hnand->MspDeInitCallback = HAL_NAND_MspDeInit;
        break;
      case HAL_NAND_IT_CB_ID :
        hnand->ItCallback = HAL_NAND_ITCallback;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else if (hnand->State == HAL_NAND_STATE_RESET)
  {
    switch (CallbackId)
    {
      case HAL_NAND_MSP_INIT_CB_ID :
        hnand->MspInitCallback = HAL_NAND_MspInit;
        break;
      case HAL_NAND_MSP_DEINIT_CB_ID :
        hnand->MspDeInitCallback = HAL_NAND_MspDeInit;
        break;
      default :
        /* update return status */
        status =  HAL_ERROR;
        break;
    }
  }
  else
  {
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hnand);

  return status;
}
#endif /* USE_HAL_NAND_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup NAND_Exported_Functions_Group3 Peripheral Control functions
  *  @brief   management functions
  *
@verbatim
  ==============================================================================
                         ##### NAND Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the NAND interface.

@endverbatim
  * @{
  */


/**
  * @brief  Enables dynamically NAND ECC feature.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_Enable(NAND_HandleTypeDef *hnand)
{
  HAL_StatusTypeDef status;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Enable ECC feature */
    (void)FMC_NAND_ECC_Enable(hnand->Instance, hnand->Init.NandBank);

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Disables dynamically FMC_NAND ECC feature.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_ECC_Disable(NAND_HandleTypeDef *hnand)
{
  HAL_StatusTypeDef status;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Disable ECC feature */
    (void)FMC_NAND_ECC_Disable(hnand->Instance, hnand->Init.NandBank);

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Gets computed Hamming ECC value.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  ECCval pointer to ECC value
  * @param  Timeout maximum timeout to wait
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_GetECC(NAND_HandleTypeDef *hnand, uint32_t *ECCval, uint32_t Timeout)
{
  HAL_StatusTypeDef status;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Get NAND ECC value */
    status = FMC_NAND_GetECC(hnand->Instance, ECCval, hnand->Init.NandBank, Timeout);
    if (status != HAL_OK)
    {
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
    }

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Sets dynamically the ECC algorithm.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  Algorithm Algorithm to use for the ECC: FMC_NAND_ECC_ALGO_HAMMING or FMC_NAND_ECC_ALGO_BCH
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_ECC_SetAlgorithm(NAND_HandleTypeDef *hnand, uint32_t Algorithm)
{
  HAL_StatusTypeDef status = HAL_OK;
  assert_param(IS_FMC_ECC_ALGORITHM(Algorithm));

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Sets the ECC algorithm */
    (void)FMC_NAND_ECC_SetAlgorithm(hnand->Instance, Algorithm);
    hnand->Init.EccAlgorithm = Algorithm;

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Sets dynamically the BCH mode.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  Mode Mode to use for the BCH ECC: FMC_NAND_BCH_4BIT or FMC_NAND_BCH_8BIT
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_ECC_SetBCHMode(NAND_HandleTypeDef *hnand, uint32_t Mode)
{
  HAL_StatusTypeDef status = HAL_OK;
  assert_param(IS_FMC_BCH_MODE(Mode));

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Sets the BCH mode */
    (void)FMC_NAND_ECC_SetBCHMode(hnand->Instance, Mode);
    hnand->Init.EccAlgorithm = Mode;

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Sets dynamically the access mode.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  Mode Access mode to use for the ECC: FMC_NAND_ECC_ACCESS_MODE_READ or
                 FMC_NAND_ECC_ACCESS_MODE_WRITE
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_ECC_SetAccessMode(NAND_HandleTypeDef *hnand, uint32_t Mode)
{
  HAL_StatusTypeDef status = HAL_OK;
  assert_param(IS_FMC_ECC_ACCESS_MODE(Mode));

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Sets the ECC access mode */
    (void)FMC_NAND_ECC_SetAccessMode(hnand->Instance, Mode);
    hnand->Init.EccAccessMode = Mode;

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Gets the BCH ECC value that was computed while writing.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  ECCval Pointer to ECC value
  * @param  Timeout Timeout wait value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_ECC_GetBCH(NAND_HandleTypeDef *hnand, uint32_t *ECCval, uint32_t Timeout)
{
  HAL_StatusTypeDef status;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Sets the ECC algorithm */
    status = FMC_NAND_ECC_GetBCH(hnand->Instance, ECCval, Timeout);
    if (status != HAL_OK)
    {
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
    }

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Gets the bit positions where an error occurred while reading.
  * After the call:
  * - If no error was found, ErrorCount is set to 0
  * - If too many errors were found (more than 4 or 8 depending of BCH configuration), ErrorCount is set to -1
  * - Otherwise ErrorCount is set to the number of errors found (up to 8),
  * and Positions if filled with the error positions
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  Positions Pointer to an array of up to 8 error positions
  * @param  ErrorCount Pointer to a value giving the number of errors
  * @param  Timeout Timeout wait value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_ECC_GetErrorsBCH(NAND_HandleTypeDef *hnand, uint16_t *Positions, int32_t *ErrorCount,
                                            uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t BCHDSRx[5];

  /* Process Locked */
  __HAL_LOCK(hnand);

  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* Sets the ECC algorithm */
    status = FMC_NAND_ECC_GetBCHResult(hnand->Instance, BCHDSRx, Timeout);
    if (status == HAL_OK)
    {
      FMC_NAND_ECC_DecodeBCHResult(BCHDSRx, Positions, ErrorCount);
    }
    else
    {
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
    }

    /* Update the NAND state */
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_ERROR;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @}
  */


/** @defgroup NAND_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions
  *
@verbatim
  ==============================================================================
                         ##### NAND State functions #####
  ==============================================================================
  [..]
    This subsection permits to get in run-time the status of the NAND controller
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  return the NAND state
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL state
  */
HAL_NAND_StateTypeDef HAL_NAND_GetState(NAND_HandleTypeDef *hnand)
{
  return hnand->State;
}

/**
  * @brief  NAND memory read status
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval NAND status
  */
HAL_StatusTypeDef HAL_NAND_Read_Status(NAND_HandleTypeDef *hnand, uint32_t *NandStatus)
{
  /* Process Locked */
  __HAL_LOCK(hnand);

  *NandStatus = HAL_NAND_Read_Status_Internal(hnand);

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return HAL_OK;
}

/**
  * @}
  */


/** @defgroup NAND_Exported_Functions_Group5 Input and Output functions with error correction
  *  @brief   Peripheral State functions
  *
@verbatim
  ==============================================================================
                 ##### NAND Input and Output with ECC functions #####
  ==============================================================================
  [..]
    This subsection permits to get in run-time the status of the NAND controller
    and the data flow.

@endverbatim
  * @{
  */

#define ECC_LENGTH_FOR_BCH4 (7 * 8)
#define ECC_LENGTH_FOR_BCH8 (13 * 8)

/**
  * @brief  Perform NAND memory initialization sequence for ECC support
  * This function must be called after HAL_NAND_Init() only.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  Config pointer to ECC configuration structure
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_Init(NAND_HandleTypeDef *hnand, const NAND_EccConfigTypeDef *Config)
{
  uint32_t sectorSizeIndex = hnand->Init.EccSectorSize >> FMC_PCR_ECCSS_Pos;

  hnand->EccConfig = *Config;

  hnand->EccState.SectorSize = (uint16_t)(1 << (8 + sectorSizeIndex));

  if (hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_BCH)
  {
    if (hnand->Init.BCHMode == FMC_NAND_BCH_4BIT)
    {
      hnand->EccState.EccLength = ECC_LENGTH_FOR_BCH4;
    }
    else
    {
      hnand->EccState.EccLength = ECC_LENGTH_FOR_BCH8;
    }
  }
  else
  {
    hnand->EccState.EccLength = (uint8_t)(22 + (2 * sectorSizeIndex));
  }

  if (hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8)
  {
    hnand->EccState.EccSize = (uint8_t)((hnand->EccState.EccLength + 7u) >> 3);
  }
  else
  {
    hnand->EccState.SectorSize >>= 1;
    hnand->EccState.EccSize = (uint8_t)((hnand->EccState.EccLength + 15u) >> 4);
  }

  hnand->EccState.SectorCount = (uint8_t)(hnand->Config.PageSize / hnand->EccState.SectorSize);

  return HAL_OK;
}

/**
  * @brief  Perform NAND memory De-Initialization sequence for ECC support
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_DeInit(NAND_HandleTypeDef *hnand)
{
  UNUSED(hnand);
  return HAL_OK;
}

static void HAL_NAND_ECC_ResetErrorCounters(NAND_HandleTypeDef *hnand)
{
  hnand->EccStatistics.CorrectibleErrorTotal = 0;
  hnand->EccStatistics.CorrectibleErrorMax = 0;
  hnand->EccStatistics.CorrectibleSectorCount = 0;
  hnand->EccStatistics.BadSectorCount = 0;
}

static void HAL_NAND_ECC_UpdateErrorCounters(NAND_HandleTypeDef *hnand, int32_t ErrorCount)
{
  if (ErrorCount > 0)
  {
    hnand->EccStatistics.CorrectibleErrorTotal += (uint16_t)ErrorCount;
    if (hnand->EccStatistics.CorrectibleErrorMax < ErrorCount)
    {
      hnand->EccStatistics.CorrectibleErrorMax = ErrorCount;
    }
    hnand->EccStatistics.CorrectibleSectorCount++;
  }
  else if (ErrorCount < 0)
  {
    hnand->EccStatistics.BadSectorCount++;
  }
}
static void HAL_NAND_ECC_flipBit(NAND_HandleTypeDef *hnand, void *Data, uint32_t DataOffset, uint32_t BitPosition)
{
  uint32_t byte = BitPosition >> 3;
  uint32_t bit = BitPosition & 0x7u;
  uint8_t *data8 = (uint8_t *)Data + (hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8 ? DataOffset : DataOffset * 2U);
  data8[byte] ^= (1u << bit);
}

/**
  * @brief Correct the error (single bit) found by Hamming algorithm, if any.
  *
  * The length of the ECC (given in ecc_length) depends on the sector size:
  * - 256 bytes sector -> 22 bits ECC
  * - 512 bytes sector -> 24 bits ECC
  * - 1024 bytes sector -> 26 bits ECC
  * - 2048 bytes sector -> 28 bits ECC
  * - 4096 bytes sector -> 30 bits ECC
  * - 8192 bytes sector -> 32 bits ECC
  *
  * @param SectorData sector data
  * @param EccLength length of the ECC bits in both EccWhenWriting and EccWhenReading
  * @param EccWhenWriting ECC computed when writing
  * @param EccWhenReading ECC computed when reading
  * @retval 0 if no error was detected,
  *         1 if one error has been found and corrected,
  *        -1 if more than one error was detected (it cannot be corrected)
  */
static int32_t HAL_NAND_ECC_CorrectHamming(NAND_HandleTypeDef *hnand, void *SectorData, uint32_t SectorOffset,
                                           uint32_t EccLength, uint32_t EccWhenWriting, uint32_t EccWhenReading)
{
  uint32_t length = EccLength;
  uint32_t bitPosition;
  uint32_t shifting;
  uint32_t xoredEcc;

  /* Indicate which bit and byte is faulty (if any) */
  xoredEcc = EccWhenWriting ^ EccWhenReading;
  if (xoredEcc == 0)
  {
    /* No error */
    return 0;
  }

  /* Calculate bit position */
  bitPosition = 0;
  shifting = 1;
  do
  {
    switch (xoredEcc % 4u)
    {
      default:
        return -1;
      case 2:
        bitPosition += shifting;
        break;
      case 1:
        break;
    }
    shifting <<= 1;
    xoredEcc >>= 2;
    length -= 2u;
  } while (length > 0u);

  /* Flip the bit */
  HAL_NAND_ECC_flipBit(hnand, SectorData, SectorOffset, bitPosition);

  return 1;
}

/**
  * @brief Correct the errors found by BCH algorithm, if any.
  *
  * @param SectorData sector data
  * @param ErrorCount number of errors found (up to 8)
  * @param Positions position of each error (bit index in the sector)
  * @retval 0 if no error was detected,
  *         1 if one error has been found and corrected,
  *         -1 if more than one error was detected (it cannot be corrected)
  */
static void HAL_NAND_ECC_CorrectBCH(NAND_HandleTypeDef *hnand, void *SectorData, uint32_t SectorOffset,
                                    int32_t ErrorCount, const uint16_t *Positions)
{
  int32_t errorIndex;
  uint32_t bitPosition;
  uint32_t sectorSizeInBits = hnand->EccState.SectorSize * (hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8 ? \
                                                            8U : 16U); /* Sector size in bits */
  for (errorIndex = 0; errorIndex < ErrorCount; errorIndex++)
  {
    bitPosition = Positions[errorIndex];
    if (bitPosition < sectorSizeInBits)
    {
      /* Flip the bit */
      HAL_NAND_ECC_flipBit(hnand, SectorData, SectorOffset, bitPosition);
    }
  }
}

static HAL_StatusTypeDef HAL_NAND_ECC_Read_Sector(NAND_HandleTypeDef *hnand, uint32_t SectorOffset, uint32_t EccOffset,
                                                  void *Buff, uint32_t BuffOffset)
{
  HAL_StatusTypeDef status;
  uint32_t eccWhenWriting[4] = {0x00U};
  uint32_t eccWhenReading[4] = {0x00U};
  uint32_t BCHDSRx[5]        = {0x00U};
  uint16_t errorPositions[8] = {0x00U};
  int32_t errorCount = 0;

  /* Change read position (column) to sector data */
  HAL_NAND_ChangeReadColumn(hnand, SectorOffset);

  /* Read the NAND page sector */
  HAL_NAND_ReadFromDevice(hnand, hnand->EccState.SectorSize, Buff, BuffOffset);

  /* Change read position (column) to ECC data */
  HAL_NAND_ChangeReadColumn(hnand, EccOffset);

  /* Read the corresponding ECC (automatically copied in registers for BCH) */
  HAL_NAND_ReadFromDevice(hnand, hnand->EccState.EccSize, eccWhenWriting, 0);

  /* The ECC is automatically computed by hardware, now try to correct errors if any */
  if (hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_BCH)
  {
    /* For BCH, the read ECC and the computed ECC are automatically used to compute error positions */
    status = FMC_NAND_ECC_GetBCHResult(hnand->Instance, BCHDSRx, hnand->TimeOut);
    if (status == HAL_OK)
    {
      FMC_NAND_ECC_DecodeBCHResult(BCHDSRx, errorPositions, &errorCount);
      HAL_NAND_ECC_CorrectBCH(hnand, Buff, BuffOffset, errorCount, errorPositions);
    }
    else
    {
      hnand->State = HAL_NAND_STATE_ERROR;
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
    }
  }
  else
  {
    /* For Hamming, we must retrieve the computed ECC and find ourselves the error position */
    status = FMC_NAND_GetECC(hnand->Instance, eccWhenReading, hnand->Init.NandBank, hnand->TimeOut);
    if (status == HAL_OK)
    {
      errorCount = HAL_NAND_ECC_CorrectHamming(hnand, Buff, BuffOffset, hnand->EccState.EccLength,
                                               eccWhenWriting[0], eccWhenReading[0]);
    }
    else
    {
      hnand->State = HAL_NAND_STATE_ERROR;
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
    }
  }

  if (status == HAL_OK)
  {
    HAL_NAND_ECC_UpdateErrorCounters(hnand, errorCount);
  }

  return status;
}

static HAL_StatusTypeDef HAL_NAND_ECC_Read_SinglePage(NAND_HandleTypeDef *hnand, uint32_t NandAddress, void *Buff,
                                                      uint32_t BuffOffset)
{
  HAL_StatusTypeDef status;
  uint32_t sectorOffset;
  uint32_t eccOffset;

  HAL_NAND_ECC_ResetErrorCounters(hnand);

  sectorOffset = 0;
  eccOffset = hnand->Config.PageSize + hnand->EccConfig.Offset;

  /* Begin reading */
  status = HAL_NAND_ReadBegin(hnand, NandAddress, 0);
  if (status == HAL_OK)
  {
    do
    {
      /* Enable ECC computations */
      (void)FMC_NAND_ECC_Enable(hnand->Instance, hnand->Init.NandBank);
      /* Read sector */
      status = HAL_NAND_ECC_Read_Sector(hnand, sectorOffset, eccOffset, Buff, BuffOffset + sectorOffset);
      /* Reset ECC computations */
      (void)FMC_NAND_ECC_Disable(hnand->Instance, hnand->Init.NandBank);
      if (status != HAL_OK)
      {
        break;
      }

      sectorOffset += hnand->EccState.SectorSize;
      eccOffset += hnand->EccState.EccSize;
    } while (sectorOffset < hnand->Config.PageSize);
  }

  return status;
}

/**
  * @brief  Read Page(s) from NAND memory block with error correction
  * If no error occurred, HAL_OK is returned and NumPagesRead is equal to NumPagesToRead.
  * If read errors cannot be corrected with ECC, HAL_OK is returned and NumPagesRead indicates
  *   the index of the concerned page.
  * If a non-ECC error occurred, a value different of HAL_OK is returned and NumPagesRead indicates
  *   the index of the concerned page.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  NumPageToRead  number of pages to read
  * @param  NumPageRead  number of pages effectively read
  * @retval HAL status
  */
static HAL_StatusTypeDef HAL_NAND_ECC_Read_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                                uint32_t NumPagesToRead, uint32_t *NumPagesRead)
{
  HAL_StatusTypeDef status;
  uint32_t bufferOffset = 0;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  uint32_t numPagesRead = 0U;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Reset ECC computations */
    (void)FMC_NAND_ECC_Disable(hnand->Instance, hnand->Init.NandBank);

    /* Set read mode for ECC computation */
    if (hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_BCH)
    {
      (void)FMC_NAND_ECC_SetAccessMode(hnand->Instance, FMC_NAND_ECC_ACCESS_MODE_READ);
    }

    /* Page read loop */
    while ((numPagesRead < NumPagesToRead) && (nandAddress < nandAddressMax))
    {
      status = HAL_NAND_ECC_Read_SinglePage(hnand, nandAddress, pBuffer, bufferOffset);
      if (status != HAL_OK)
      {
        hnand->State = HAL_NAND_STATE_ERROR;
        break;
      }

      if ((status != HAL_OK) || (hnand->EccStatistics.BadSectorCount > 0))
      {
        break;
      }

      /* Next page in the destination buffer */
      bufferOffset += hnand->Config.PageSize;

      /* Increment read pages number */
      numPagesRead++;

      /* Increment the NAND address */
      nandAddress = (uint32_t)(nandAddress + 1U);
    }

    *NumPagesRead = numPagesRead;

    if (status == HAL_OK)
    {
      /* Update the NAND controller state */
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Read Page(s) from NAND memory block with error correction (8-bit addressing)
  * If no error occurred, HAL_OK is returned and NumPagesRead is equal to NumPagesToRead.
  * If read errors cannot be corrected with ECC, HAL_OK is returned and NumPagesRead indicates
  *   the index of the concerned page.
  * If a non-ECC error occurred, a value different of HAL_OK is returned and NumPagesRead indicates
  *   the index of the concerned page.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  NumPageToRead  number of pages to read
  * @param  NumPageRead  number of pages effectively read
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_Read_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, uint8_t *pBuffer,
                                             uint32_t NumPagesToRead, uint32_t *NumPagesRead)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_ECC_Read_Page(hnand, pAddress, pBuffer, NumPagesToRead, NumPagesRead);
}

/**
  * @brief  Read Page(s) from NAND memory block with error correction (16-bit addressing)
  * If no error occurred, HAL_OK is returned and NumPagesRead is equal to NumPagesToRead.
  * If read errors cannot be corrected with ECC, HAL_OK is returned and NumPagesRead indicates
  *   the index of the concerned page.
  * If a non-ECC error occurred, a value different of HAL_OK is returned and NumPagesRead indicates
  *   the index of the concerned page.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @param  NumPageToRead  number of pages to read
  * @param  NumPageRead  number of pages effectively read
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_Read_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                              uint16_t *pBuffer, uint32_t NumPagesToRead, uint32_t *NumPagesRead)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_ECC_Read_Page(hnand, pAddress, pBuffer, NumPagesToRead, NumPagesRead);
}

static HAL_StatusTypeDef HAL_NAND_ECC_Write_Sector(NAND_HandleTypeDef *hnand, uint32_t SectorOffset, uint32_t EccOffset,
                                                   void *Buff, uint32_t BuffOffset)
{
  HAL_StatusTypeDef status;
  uint32_t EccWhenWriting[4];

  /* Change write position (column) to sector data */
  HAL_NAND_ChangeWriteColumn(hnand, SectorOffset);

  /* Write the NAND sector */
  HAL_NAND_WriteToDevice(hnand, hnand->EccState.SectorSize, Buff, BuffOffset);

  if (hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_BCH)
  {
    status = FMC_NAND_ECC_GetBCH(hnand->Instance, EccWhenWriting, hnand->TimeOut);
  }
  else
  {
    status = FMC_NAND_GetECC(hnand->Instance, EccWhenWriting, hnand->Init.NandBank, hnand->TimeOut);
  }
  if (status == HAL_OK)
  {
    /* Change write position (column) to ECC data */
    HAL_NAND_ChangeWriteColumn(hnand, EccOffset);

    /* Write the corresponding ECC */
    HAL_NAND_WriteToDevice(hnand, hnand->EccState.EccSize, EccWhenWriting, 0);
  }
  else
  {
    hnand->State = HAL_NAND_STATE_ERROR;
    hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
  }

  return status;
}

static HAL_StatusTypeDef HAL_NAND_ECC_Write_SinglePage(NAND_HandleTypeDef *hnand, uint32_t NandAddress, void *Buff,
                                                       uint32_t BuffOffset)
{
  HAL_StatusTypeDef status;
  uint32_t sectorOffset;
  uint32_t eccOffset;

  HAL_NAND_ECC_ResetErrorCounters(hnand);

  sectorOffset = 0;
  eccOffset = hnand->Config.PageSize + hnand->EccConfig.Offset;

  /* Begin writing */
  HAL_NAND_WriteBegin(hnand, NandAddress, 0, NAND_AREA_USER);

  do
  {
    /* Enable ECC computations */
    (void)FMC_NAND_ECC_Enable(hnand->Instance, hnand->Init.NandBank);
    /* Write sector */
    status = HAL_NAND_ECC_Write_Sector(hnand, sectorOffset, eccOffset, Buff, BuffOffset + sectorOffset);
    /* Reset ECC computations */
    (void)FMC_NAND_ECC_Disable(hnand->Instance, hnand->Init.NandBank);
    if (status != HAL_OK)
    {
      return status;
    }

    sectorOffset += hnand->EccState.SectorSize;
    eccOffset += hnand->EccState.EccSize;
  } while (sectorOffset < hnand->Config.PageSize);

  status = HAL_NAND_WriteEnd(hnand);

  return status;
}

/**
  * @brief  Write Page(s) to NAND memory block with error correction
  * If no error occurred, HAL_OK is returned and NumPagesWritten is equal to NumPagesToWrite.
  * If an error occurred, a value different of HAL_OK is returned and NumPagesWritten indicates
  *   the index of the concerned page.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumPagesToWrite  number of pages to write to block
  * @param  NumPagesWritten  number of pages effectively written
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_Write_Page(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress, void *pBuffer,
                                           uint32_t NumPagesToWrite, uint32_t *NumPagesWritten)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t nandAddressMax;
  uint32_t nandAddress;
  uint32_t numPagesWritten = 0U;
  uint32_t bufferOffset = 0;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    /* Reset ECC computations */
    (void)FMC_NAND_ECC_Disable(hnand->Instance, hnand->Init.NandBank);

    /* Set write mode for ECC computation */
    if (hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_BCH)
    {
      (void)FMC_NAND_ECC_SetAccessMode(hnand->Instance, FMC_NAND_ECC_ACCESS_MODE_WRITE);
    }

    /* Page(s) write loop */
    while ((numPagesWritten < NumPagesToWrite) && (nandAddress < nandAddressMax))
    {
      status = HAL_NAND_ECC_Write_SinglePage(hnand, nandAddress, pBuffer, bufferOffset);
      if (status == HAL_ERROR)
      {
        hnand->State = HAL_NAND_STATE_READY;
        break;
      }
      if (status != HAL_OK)
      {
        break;
      }

      /* Next page in the destination buffer */
      bufferOffset += hnand->Config.PageSize;

      /* Increment written pages number */
      numPagesWritten++;

      /* Increment the NAND address */
      nandAddress = (uint32_t)(nandAddress + 1U);
    }

    *NumPagesWritten = numPagesWritten;

    /* Update the NAND controller state */
    if (status == HAL_OK)
    {
      hnand->State = HAL_NAND_STATE_READY;
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    status = HAL_BUSY;
  }

  /* Process unlocked */
  __HAL_UNLOCK(hnand);

  return status;
}

/**
  * @brief  Write Page(s) to NAND memory with error correction
  * If no error occurred, HAL_OK is returned and NumPagesWritten is equal to NumPagesToWrite.
  * If an error occurred, a value different of HAL_OK is returned and NumPagesWritten indicates
  *   the index of the concerned page.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumPagesToWrite  number of pages to write to block
  * @param  NumPagesWritten  number of pages effectively written
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_Write_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                              uint8_t *pBuffer,
                                              uint32_t NumPagesToWrite, uint32_t *NumPagesWritten)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_ECC_Write_Page(hnand, pAddress, pBuffer, NumPagesToWrite, NumPagesWritten);
}

/**
  * @brief  Write Page(s) to NAND memory with error correction
  * If no error occurred, HAL_OK is returned and NumPagesWritten is equal to NumPagesToWrite.
  * If an error occurred, a value different of HAL_OK is returned and NumPagesWritten indicates
  *   the index of the concerned page.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @param  NumPagesToWrite  number of pages to write to block
  * @param  NumPagesWritten  number of pages effectively written
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_ECC_Write_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                               uint16_t *pBuffer,
                                               uint32_t NumPagesToWrite, uint32_t *NumPagesWritten)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_ECC_Write_Page(hnand, pAddress, pBuffer, NumPagesToWrite, NumPagesWritten);
}

/**
  * @brief  Get the ECC statistics about the page read
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *               the configuration information for NAND module.
  * @param  Stat  pointer to ECC statistics structure
  */
void HAL_NAND_ECC_GetStatistics(NAND_HandleTypeDef *hnand, NAND_EccStatisticsTypeDef *Stat)
{
  *Stat = hnand->EccStatistics;
}

/**
  * @}
  */


/** @defgroup NAND_Exported_Functions_Group6 Input and Output functions with error correction
  *  @brief   Peripheral State functions
  *
@verbatim
  ==============================================================================
                 ##### NAND Input and Output with sequencer functions #####
  ==============================================================================
  [..]

@endverbatim
  * @{
  */

#ifdef HAL_MDMA_MODULE_ENABLED

/**
  * @brief  Compute the number of 32-bit words needed by the sequencer to store the ECC of a sector
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *               the configuration information for NAND module.
  * @retval Number of words needed to store ECC for a sector
  */
uint32_t HAL_NAND_Sequencer_GetEccWordsPerSector(NAND_HandleTypeDef *hnand)
{
  return hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_HAMMING ? 1 : 5; /* HECCR or BCHDSR0 to BCHDSR4 */
}

/**
  * @brief  Compute the size of the buffer needed by the sequencer to store the ECC of a page
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval Size of the buffer needed to store ECC for a page
  */
uint32_t HAL_NAND_Sequencer_ComputeEccBufferSize(NAND_HandleTypeDef *hnand)
{
  uint32_t wordsPerSector = HAL_NAND_Sequencer_GetEccWordsPerSector(hnand);
  return hnand->EccState.SectorCount * wordsPerSector * 4;
}

/**
  * @brief  Perform NAND memory initialization sequence for sequencer support
  * This function must be called after HAL_NAND_ECC_Init() only.
  * This function calls the weak function HAL_NAND_Sequencer_MspInit() which allows to setup the 3 DMA channels.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  Config pointer to sequencer configuration structure
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_Init(NAND_HandleTypeDef *hnand, const NAND_SequencerConfigTypeDef *Config)
{
  hnand->SequencerConfig = *Config;
  hnand->SequencerState.EccBufferSize = HAL_NAND_Sequencer_ComputeEccBufferSize(hnand);
  hnand->SequencerState.TransferPending = false;
  return HAL_NAND_Sequencer_MspInit(hnand);
}

/**
  * @brief  Perform NAND memory De-Initialization sequence for sequencer support
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_DeInit(NAND_HandleTypeDef *hnand)
{
  HAL_NAND_Sequencer_MspDeInit(hnand);
  hnand->SequencerConfig.HdmaRead = NULL;
  hnand->SequencerConfig.HdmaWrite = NULL;
  hnand->SequencerConfig.HdmaReadEcc = NULL;
  hnand->SequencerConfig.EccBuffer = NULL;
  hnand->SequencerState.EccBufferSize = 0;
  hnand->SequencerState.TransferPending = false;
  return HAL_OK;
}

/**
  * @brief  Initialize the NAND sequencer MSP.
  * @param  hnand: NAND handle.
  * @retval None
  */
__weak HAL_StatusTypeDef HAL_NAND_Sequencer_MspInit(NAND_HandleTypeDef *hnand)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hnand);

  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_NAND_Sequencer_MspInit() can be implemented in the user file.
   */
  return HAL_OK;
}

/**
  * @brief  DeInitialize the NAND sequencer MSP.
  * @param  hnand: NAND handle.
  * @retval None
  */
__weak void HAL_NAND_Sequencer_MspDeInit(NAND_HandleTypeDef *hnand)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hnand);

  /* NOTE : This function should not be modified; when the callback is needed,
            HAL_NAND_Sequencer_MspDeInit() can be implemented in the user file.
   */
}

static void HAL_NAND_Sequencer_setup(NAND_HandleTypeDef *hnand, uint32_t NandAddress, bool WriteFlag, bool RawFlag)
{
  uint32_t csqcfr1;
  uint32_t csqcfr2;
  uint32_t csqcfr3;
  uint32_t csqar1;
  uint32_t csqar2;
  uint32_t totalPageNumber = hnand->Config.BlockSize * hnand->Config.BlockNbr;
  bool attUsed = true;

  /* Reset ECC computations */
  (void)FMC_NAND_ECC_Disable(hnand->Instance, hnand->Init.NandBank);

  /* Set read or write mode for ECC computation */
  (void)FMC_NAND_ECC_SetAccessMode(hnand->Instance, WriteFlag ? FMC_NAND_ECC_ACCESS_MODE_WRITE :
                                   FMC_NAND_ECC_ACCESS_MODE_READ);

  /*
   * - Set Program Page/Page Read command
   * - Enable DMA request data
   * - Set timings
   */
  csqcfr1 = FMC_CSQCFGR1_DMADEN;
  if (attUsed)
  {
    csqcfr1 |= FMC_CSQCFGR1_CMD1T;
  }
  if (WriteFlag)
  {
    csqcfr1 |= NAND_CMD_WRITE0 << FMC_CSQCFGR1_CMD1_Pos;
  }
  else
  {
    csqcfr1 |=
      (NAND_CMD_AREA_A << FMC_CSQCFGR1_CMD1_Pos) |
      FMC_CSQCFGR1_CMD2EN |
      (NAND_CMD_AREA_TRUE1 << FMC_CSQCFGR1_CMD2_Pos);
    if (attUsed)
    {
      csqcfr1 |= FMC_CSQCFGR1_CMD2T;
    }
  }

  /*
   * - Set Random Data Input/Random Data Read command
   * - Enable the sequencer to access the Spare data area
   * - Enable  DMA request status decoding for read
   * - Set timings
   */
  if (WriteFlag)
  {
    csqcfr2 = NAND_CMD_RANDOM_INPUT << FMC_CSQCFGR2_RCMD1_Pos;
  }
  else
  {
    csqcfr2 =
      (NAND_CMD_RANDOM_OUTPUT_0 << FMC_CSQCFGR2_RCMD1_Pos) |
      FMC_CSQCFGR2_RCMD2EN |
      (NAND_CMD_RANDOM_OUTPUT_1 << FMC_CSQCFGR2_RCMD2_Pos);
    if (attUsed)
    {
      csqcfr2 |= FMC_CSQCFGR2_RCMD1T | FMC_CSQCFGR2_RCMD2T;
    }
  }
  if (!RawFlag)
  {
    if (!WriteFlag)
    {
      csqcfr2 |= FMC_CSQCFGR2_DMASEN;
    }
    csqcfr2 |= FMC_CSQCFGR2_SQSDTEN;
  }

  /*
   * - Set the number of sectors to be written
   * - Set timings
   */
  csqcfr3 = (hnand->EccState.SectorCount - 1) << FMC_CSQCFGR3_SNBR_Pos;
  if (WriteFlag && attUsed)
  {
    csqcfr3 |= FMC_CSQCFGR3_RAC2T;
    if (totalPageNumber > NAND_MAX_PAGES_FOR_16BIT_ADDRESS)
    {
      csqcfr3 |= FMC_CSQCFGR3_AC5T;
    }
    else
    {
      csqcfr3 |= FMC_CSQCFGR3_AC4T;
    }
  }

  /*
   * Set the fourth first address cycles
   * Byte 1 and byte 2 => column, we start at 0x0
   * Byte 3 and byte 4 => page
   */
  csqar1 = NandAddress << FMC_CSQAR1_ADDC3_Pos;

  /*
   * - Set chip enable number
   * - Set ECC byte offset in the spare area
   * - Calculate the number of address cycles to be issued
   * - Set byte 5 of address cycle if needed
   */

  csqar2 = hnand->ChipSelect == NAND_NCE1_OFFSET ? FMC_CSQAR2_NANDCEN_0 : FMC_CSQAR2_NANDCEN_1;
  csqar2 |= (hnand->Config.PageSize + hnand->EccConfig.Offset) << FMC_CSQAR2_SAO_Pos;
  if (totalPageNumber > NAND_MAX_PAGES_FOR_16BIT_ADDRESS)
  {
    csqcfr1 |= 5 << FMC_CSQCFGR1_ACYNBR_Pos;
    csqar2 |= ((NandAddress >> 16) & 0xff) << FMC_CSQAR2_ADDC5_Pos;
  }
  else
  {
    csqcfr1 |= 4 << FMC_CSQCFGR1_ACYNBR_Pos;
  }

  MODIFY_REG(hnand->Instance->CSQCFGR1, FMC_CSQCFGR1_CMD2EN_Msk | FMC_CSQCFGR1_DMADEN_Msk | FMC_CSQCFGR1_ACYNBR_Msk |
             FMC_CSQCFGR1_CMD1_Msk | FMC_CSQCFGR1_CMD2_Msk | FMC_CSQCFGR1_CMD1T_Msk |
             FMC_CSQCFGR1_CMD2T_Msk, csqcfr1);
  MODIFY_REG(hnand->Instance->CSQCFGR2, FMC_CSQCFGR2_SQSDTEN_Msk | FMC_CSQCFGR2_RCMD2EN_Msk | FMC_CSQCFGR2_DMASEN_Msk |
             FMC_CSQCFGR2_RCMD1_Msk | FMC_CSQCFGR2_RCMD2_Msk | FMC_CSQCFGR2_RCMD1T_Msk |
             FMC_CSQCFGR2_RCMD2T_Msk, csqcfr2);
  MODIFY_REG(hnand->Instance->CSQCFGR3, FMC_CSQCFGR3_SNBR_Msk | FMC_CSQCFGR3_AC1T_Msk | FMC_CSQCFGR3_AC2T_Msk |
             FMC_CSQCFGR3_AC3T_Msk | FMC_CSQCFGR3_AC4T_Msk | FMC_CSQCFGR3_AC5T_Msk |
             FMC_CSQCFGR3_SDT_Msk | FMC_CSQCFGR3_RAC1T_Msk | FMC_CSQCFGR3_RAC2T_Msk,
             csqcfr3);
  MODIFY_REG(hnand->Instance->CSQAR1, FMC_CSQAR1_ADDC1_Msk | FMC_CSQAR1_ADDC2_Msk | FMC_CSQAR1_ADDC3_Msk |
             FMC_CSQAR1_ADDC4_Msk, csqar1);
  MODIFY_REG(hnand->Instance->CSQAR2, FMC_CSQAR2_ADDC5_Msk | FMC_CSQAR2_NANDCEN_Msk | FMC_CSQAR2_SAO_Msk, csqar2);
}

#define HAL_NAND_SEQUENCER_TIMEOUT 5000

HAL_StatusTypeDef HAL_NAND_Sequencer_Abort(NAND_HandleTypeDef *hnand)
{
  HAL_StatusTypeDef status;

  if (hnand->State == HAL_NAND_STATE_BUSY)
  {
    /* FIXME: No information has been found on how to abort the sequencer.
       But the word 'abort' is evoked in 22.9.8 and for "TCF: Transfer Complete flag". */

    if (HAL_MDMA_GetState(hnand->SequencerConfig.HdmaRead) == HAL_MDMA_STATE_BUSY)
    {
      status = HAL_MDMA_Abort(hnand->SequencerConfig.HdmaRead);
      if (status != HAL_OK)
      {
        hnand->State = HAL_NAND_STATE_ERROR;
        hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
        __HAL_UNLOCK(hnand);
        return HAL_ERROR;
      }
    }

    if (HAL_MDMA_GetState(hnand->SequencerConfig.HdmaWrite) == HAL_MDMA_STATE_BUSY)
    {
      status = HAL_MDMA_Abort(hnand->SequencerConfig.HdmaWrite);
      if (status != HAL_OK)
      {
        hnand->State = HAL_NAND_STATE_ERROR;
        hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
        __HAL_UNLOCK(hnand);
        return HAL_ERROR;
      }
    }

    if (HAL_MDMA_GetState(hnand->SequencerConfig.HdmaReadEcc) == HAL_MDMA_STATE_BUSY)
    {
      status = HAL_MDMA_Abort(hnand->SequencerConfig.HdmaReadEcc);
      if (status != HAL_OK)
      {
        hnand->State = HAL_NAND_STATE_ERROR;
        hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
        __HAL_UNLOCK(hnand);
        return HAL_ERROR;
      }
    }

    hnand->State = HAL_NAND_STATE_READY;
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;
    hnand->SequencerState.TransferPending = false;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_NO_XFER;
    status = HAL_ERROR;
  }

  __HAL_UNLOCK(hnand);

  return status;
}

static HAL_StatusTypeDef HAL_NAND_Sequencer_WaitTransferCompletion(NAND_HandleTypeDef *hnand, uint32_t TimeOut)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tickstart;

  /* Read status until NAND is ready */
  tickstart = HAL_GetTick();
  while (!READ_BIT(hnand->Instance->CSQISR, FMC_CSQISR_TCF))
  {
    if ((TimeOut != HAL_MAX_DELAY) && ((TimeOut == 0U) || ((HAL_GetTick() - tickstart) > TimeOut)))
    {
      /* If timeout then abort the current transfer. No need to check return value: as in this case we will return
         HAL_ERROR with HAL_MDMA_ERROR_TIMEOUT error code */
      (void)HAL_NAND_Sequencer_Abort(hnand);

      hnand->State = HAL_NAND_STATE_ERROR;
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
      status = HAL_ERROR;
      break;
    }
  }

  return status;
}

static uint32_t HAL_NAND_ECC_ReadHamming(uint32_t EccSize, const uint8_t *Buffer)
{
  uint32_t ecc = 0;
  uint32_t i;
  for (i = 0; i < EccSize; i++)
  {
    ecc = (ecc << 8) | Buffer[i];
  }
  return ecc;
}

static void HAL_NAND_Sequencer_Correct(NAND_HandleTypeDef *hnand)
{
  uint32_t sectorMap = hnand->Instance->CSQEMSR & FMC_CSQEMSR_SEM_Msk;
  if (sectorMap)
  {
    uint32_t sectorCount = hnand->EccState.SectorCount, sectorIndex;
    uint32_t eccSize = hnand->EccState.EccSize;
    uint32_t eccTotalSize = eccSize * sectorCount;
    uint8_t eccWhenWritingBuffer[eccTotalSize];

    /* Change read position (column) to ECC data */
    HAL_NAND_ChangeReadColumn(hnand, hnand->Config.PageSize + hnand->EccConfig.Offset);

    /* Read the corresponding ECC (automatically copied in registers for BCH) */
    HAL_NAND_ReadFromDevice(hnand, eccTotalSize, eccWhenWritingBuffer, 0);

    for (sectorIndex = 0; sectorIndex < sectorCount; sectorIndex++)
    {
      if (sectorMap & (1 << sectorIndex))
      {
        uint32_t dataOffset = sectorIndex * hnand->EccState.SectorSize;
        int32_t errorCount;
        if (hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_HAMMING)
        {
          uint32_t eccWhenWriting = HAL_NAND_ECC_ReadHamming(eccSize, &eccWhenWritingBuffer[sectorIndex * eccSize]);
          uint32_t eccWhenReading = hnand->SequencerConfig.EccBuffer[sectorIndex];
          errorCount = HAL_NAND_ECC_CorrectHamming(hnand, hnand->SequencerState.Data, dataOffset,
                                                   hnand->EccState.EccLength, eccWhenWriting, eccWhenReading);
        }
        else
        {
          uint32_t *BCHDSRx = &hnand->SequencerConfig.EccBuffer[sectorIndex * 5];
          uint16_t errorPositions[8];
          FMC_NAND_ECC_DecodeBCHResult(BCHDSRx, errorPositions, &errorCount);
          HAL_NAND_ECC_CorrectBCH(hnand, hnand->SequencerState.Data, dataOffset, errorCount, errorPositions);
        }
        HAL_NAND_ECC_UpdateErrorCounters(hnand, errorCount);
      }
    }
  }
}

HAL_StatusTypeDef HAL_NAND_Sequencer_WaitCompletion(NAND_HandleTypeDef *hnand, uint32_t TimeOut)
{
  HAL_StatusTypeDef status;

  if (hnand->State == HAL_NAND_STATE_BUSY)
  {
    assert(hnand->SequencerState.TransferPending);

    /* Wait sequencer completion. */
    status = HAL_NAND_Sequencer_WaitTransferCompletion(hnand, TimeOut);
    if (status != HAL_OK)
    {
      __HAL_UNLOCK(hnand);
      return status;
    }

    /* Wait DMA read data transfer completion. */
    status = HAL_MDMA_PollForTransfer(hnand->SequencerConfig.HdmaRead, HAL_MDMA_FULL_TRANSFER, TimeOut);
    if (status != HAL_OK && hnand->SequencerConfig.HdmaRead->ErrorCode != HAL_MDMA_ERROR_NO_XFER)
    {
      hnand->State = HAL_NAND_STATE_ERROR;
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
      __HAL_UNLOCK(hnand);
      return status;
    }

    /* Wait DMA write data transfer completion. */
    status = HAL_MDMA_PollForTransfer(hnand->SequencerConfig.HdmaWrite, HAL_MDMA_FULL_TRANSFER, TimeOut);
    if (status != HAL_OK && hnand->SequencerConfig.HdmaWrite->ErrorCode != HAL_MDMA_ERROR_NO_XFER)
    {
      hnand->State = HAL_NAND_STATE_ERROR;
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
      __HAL_UNLOCK(hnand);
      return status;
    }

    /* Wait DMA ECC transfer completion. */
    status = HAL_MDMA_PollForTransfer(hnand->SequencerConfig.HdmaReadEcc, HAL_MDMA_FULL_TRANSFER, TimeOut);
    if (status != HAL_OK && hnand->SequencerConfig.HdmaReadEcc->ErrorCode != HAL_MDMA_ERROR_NO_XFER)
    {
      hnand->State = HAL_NAND_STATE_ERROR;
      hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
      __HAL_UNLOCK(hnand);
      return status;
    }

    if (!hnand->SequencerState.WriteFlag && !hnand->SequencerState.RawFlag)
    {
      HAL_NAND_Sequencer_Correct(hnand);
    }
    hnand->SequencerState.TransferPending = false;

    if (hnand->SequencerState.WriteFlag)
    {
      status = HAL_NAND_WriteEnd(hnand);
      if (status != HAL_OK)
      {
        hnand->State = HAL_NAND_STATE_ERROR;
        hnand->ErrorCode = HAL_NAND_ERROR_TIMEOUT;
        __HAL_UNLOCK(hnand);
        return status;
      }
    }

    status = HAL_OK;
    hnand->State = HAL_NAND_STATE_READY;
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_NO_XFER;
    status = HAL_ERROR;
  }

  __HAL_UNLOCK(hnand);

  return status;
}

static HAL_StatusTypeDef HAL_NAND_Sequencer_startTransfer(NAND_HandleTypeDef *hnand, void *Buffer, bool WriteFlag,
                                                          bool RawFlag)
{
  HAL_StatusTypeDef status;
  MDMA_HandleTypeDef *hdmaData;
  MDMA_HandleTypeDef *hdmaEcc = NULL;
  uint32_t srcAddress;
  uint32_t dstAddress;
  uint32_t size;

  /* Configure DMA channel for reading or writing data. */
  if (WriteFlag)
  {
    hdmaData = hnand->SequencerConfig.HdmaWrite;
    srcAddress = (uint32_t)Buffer;
    dstAddress = hnand->DeviceAddress;
  }
  else
  {
    hdmaData = hnand->SequencerConfig.HdmaRead;
    srcAddress = hnand->DeviceAddress;
    dstAddress = (uint32_t)Buffer;
  }
  size = HAL_NAND_ComputeWordsToBytes(hnand->EccState.SectorSize, hnand->Init.MemoryDataWidth);
  status = HAL_MDMA_Start(hdmaData, srcAddress, dstAddress, size, hnand->EccState.SectorCount);
  if (status != HAL_OK)
  {
    hnand->State = HAL_ERROR;
    hnand->ErrorCode = HAL_NAND_ERROR_DMA;
    return status;
  }

  /* Configure DMA channel for reading ECC if needed. */
  if (!WriteFlag && !RawFlag)
  {
    hdmaEcc = hnand->SequencerConfig.HdmaReadEcc;
    srcAddress = hnand->Init.EccAlgorithm == FMC_NAND_ECC_ALGO_HAMMING ? (uint32_t)&hnand->Instance->HECCR :
                 (uint32_t)&hnand->Instance->BCHDSR0;
    dstAddress = (uint32_t)hnand->SequencerConfig.EccBuffer;
    size = HAL_NAND_Sequencer_GetEccWordsPerSector(hnand) * 4;
    status = HAL_MDMA_Start(hdmaEcc, srcAddress, dstAddress, size, hnand->EccState.SectorCount);
    if (status != HAL_OK)
    {
      hnand->State = HAL_ERROR;
      hnand->ErrorCode = HAL_NAND_ERROR_DMA;
      return status;
    }
  }

  /* Clear all sequencer interrupt flags. */
  WRITE_REG(hnand->Instance->CSQICR, FMC_CSQICR_CTCF | FMC_CSQICR_CSCF | FMC_CSQICR_CSEF | FMC_CSQICR_CSUEF |
            FMC_CSQICR_CCMDTCF);
  /* Start the sequencer. */
  MODIFY_REG(hnand->Instance->CSQCR, FMC_CSQCR_CSQSTART, FMC_CSQCR_CSQSTART);

  return status;
}

static HAL_StatusTypeDef HAL_NAND_Sequencer_transferPage(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                         void *pBuffer, bool WriteFlag, bool RawFlag)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t nandAddressMax;
  uint32_t nandAddress;

  /* Process Locked */
  __HAL_LOCK(hnand);

  /* Check the NAND controller state */
  if (hnand->State == HAL_NAND_STATE_READY)
  {
    /* Update the NAND controller state */
    hnand->State = HAL_NAND_STATE_BUSY;

    /* Initialize the error code */
    hnand->ErrorCode = HAL_NAND_ERROR_NONE;

    hnand->SequencerState.TransferPending = true;
    hnand->SequencerState.WriteFlag = WriteFlag;
    hnand->SequencerState.RawFlag = RawFlag;
    hnand->SequencerState.Data = pBuffer;

    HAL_NAND_ECC_ResetErrorCounters(hnand);

    /* NAND raw address calculation */
    nandAddress = ARRAY_ADDRESS(pAddress, hnand);
    nandAddressMax = hnand->Config.BlockSize * hnand->Config.BlockNbr;

    if (nandAddress < nandAddressMax)
    {
      HAL_NAND_Sequencer_setup(hnand, nandAddress, WriteFlag, RawFlag);

      status = HAL_NAND_Sequencer_startTransfer(hnand, pBuffer, WriteFlag, RawFlag);
      if (status != HAL_OK)
      {
        __HAL_UNLOCK(hnand);
      }
    }
  }
  else
  {
    hnand->ErrorCode = HAL_NAND_ERROR_BUSY;
    __HAL_UNLOCK(hnand);
    status = HAL_BUSY;
  }

  return status;
}

/**
  * @brief  Read Page(s) from NAND memory block with error correction using the sequencer (8-bit addressing)
  * If no error occurred, HAL_OK is returned.
  * If an error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_Read_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                  uint8_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, false, true);
}

/**
  * @brief  Read Page(s) from NAND memory block with error correction using the sequencer (16-bit addressing)
  * If no error occurred, HAL_OK is returned.
  * If an error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_Read_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                   uint16_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, false, true);
}

/**
  * @brief  Read Page(s) from NAND memory block with error correction using the sequencer (8-bit addressing)
  * If no error occurred, HAL_OK is returned.
  * If read errors cannot be corrected with ECC, HAL_OK is returned and hnand->EccState.ErrorCount gives the number of
  * error found.
  * If a non-ECC error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @retval HAL status
  */
HAL_StatusTypeDef  HAL_NAND_Sequencer_ECC_Read_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                       uint8_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, false, false);
}

/**
  * @brief  Read one page from NAND memory with error correction using the sequencer (16-bit addressing)
  * If no error occurred, HAL_OK is returned.
  * If read errors cannot be corrected with ECC, HAL_OK is returned and hnand->EccState.ErrorCount gives the number of
  * error found.
  * If a non-ECC error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to destination read buffer
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_ECC_Read_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                       uint16_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, false, false);
}

/**
  * @brief  Write one page to NAND memory using the sequencer
  * If no error occurred, HAL_OK is returned.
  * If an error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_Write_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                   uint8_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, true, true);
}

/**
  * @brief  Write page to NAND memory using the sequencer
  * If no error occurred, HAL_OK is returned.
  * If an error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_Write_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                    uint16_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, true, true);
}

/**
  * @brief  Write one page to NAND memory with error correction using the sequencer
  * If no error occurred, HAL_OK is returned.
  * If an error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_ECC_Write_Page_8b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                       uint8_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth == NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, true, false);
}

/**
  * @brief  Write one page to NAND memory with error correction using the sequencer
  * If no communication error occurred, HAL_OK is returned and hnand->EccState.ErrorCount gives the number of
  * error found.
  * If an error occurred, a value different of HAL_OK is returned.
  * @param  hnand pointer to a NAND_HandleTypeDef structure that contains
  *                the configuration information for NAND module.
  * @param  pAddress  pointer to NAND address structure
  * @param  pBuffer  pointer to source buffer to write
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_NAND_Sequencer_ECC_Write_Page_16b(NAND_HandleTypeDef *hnand, NAND_AddressTypeDef *pAddress,
                                                        uint16_t *pBuffer)
{
  assert(hnand->Init.MemoryDataWidth != NAND_BUS_WIDTH_8);
  return HAL_NAND_Sequencer_transferPage(hnand, pAddress, pBuffer, true, false);
}

#endif /* HAL_MDMA_MODULE_ENABLED  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_NAND_MODULE_ENABLED  */

/**
  * @}
  */

