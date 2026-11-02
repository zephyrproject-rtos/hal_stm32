/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_flash.c
  * @brief   This file provides FLASH memory services.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined (FLASH)
#if defined (USE_HAL_FLASH_MODULE) && (USE_HAL_FLASH_MODULE == 1)

/** @addtogroup FLASH
  * @{
  */
/** @defgroup FLASH_Introduction FLASH Introduction
  * @{

  The FLASH IO Hardware Abstraction Layer (HAL) provides high-level, user-friendly APIs for managing
  non-volatile memory (FLASH) operations on STM32 microcontrollers.

  This layer offers firmware functions to handle key FLASH functionalities, including:

    - Initialization and de-initialization of FLASH handling.
    - Programming operations across different FLASH memory areas.
    - Management of operation completion and error interrupt requests.
    - Retrieval of FLASH memory topology and configuration information.

  The abstraction provided by this layer ensures portability and simplifies application development
  across various STM32 microcontroller series.

  */
/**
  * @}
  */

/** @defgroup FLASH_How_To_Use FLASH How To Use
  * @{

The Flash memory interface manages CPU AHB C-Bus accesses to the Flash memory. It implements the erase and program Flash
memory operations and the read and write protection mechanisms.

# FLASH main features

The FLASH memory organization is based on a main area and an information block.
  - The main flash memory block organized as two banks of up to 1 Mbyte each containing up to 128 pages of 8 Kbytes.
  - The information block contains :
    - 112 Kbytes for system memory. It contains the bootloader that is used to reprogram the flash memory.
    - 1 kbyte OTP (one-time programmable). The OTP data cannot be erased and can be written only once.
    - Option bytes for user configuration. The FLASH_ITF module provides option bytes configuration functions.

## Programming operation
  - The flash memory program operation can be performed 128, 64, 32, 16 or 8 bits at a time within the flash user memory
    areas.
  - The flash memory program operation can be performed 32 or 16 bits at a time within the flash data and OTP memory
    areas.

## Erasing operation
  - The flash memory erase operation can be performed at page level.
  - The flash memory erase operation can be performed at bank level.
  - The flash memory erase operation can be performed on the whole flash memory.

# How to use the FLASH HAL module driver

## Initialization and De-initialization functions :

- For a given instance, use the HAL_FLASH_Init() function to initialize the FLASH handle and associate the physical
  instance.
- Use the HAL_FLASH_DeInit() function to de-initialize FLASH. When called, the FLASH must be in reset.

## Configuration functions

- Use the HAL_FLASH_SetProgrammingMode() function to set the programming mode for both banks.
- Use the HAL_FLASH_GetProgrammingMode() function to get the programming mode retrieved from bank 1,
    use HAL_FLASH_SetBankProgrammingMode()
    and HAL_FLASH_GetBankProgrammingMode() to use different programming modes per bank.
- Use the HAL_FLASH_SetBankProgrammingMode() function to set the programming mode for the selected bank.
- Use the HAL_FLASH_GetBankProgrammingMode() function to get the programming mode for the selected bank.
- Use the HAL_FLASH_SetCRCBurstSize() function to set the CRC burst size.
- Use the HAL_FLASH_GetCRCBurstSize() function to get the CRC burst size.

## Process operation functions :

### Polling mode operations :
- Use the HAL_FLASH_ProgramByAddr() function to program by address any area of FLASH USER memory in polling mode.
- Use the HAL_FLASH_ProgramByAddrAdapt() function to program by address using adaptive width any area of FLASH USER
  memory in polling mode.
- Use the HAL_FLASH_OTP_ProgramByAddr() function to program by address any area of OTP area in polling mode.
- Use the HAL_FLASH_OTP_ProgramByAddrAdapt() function to program by address using adaptive width any area of OTP area in
  polling mode.
- Use the HAL_FLASH_EraseByAddr() function to erase by address any area of FLASH USER memory in polling mode.
- Use the HAL_FLASH_ErasePage() function to erase a specific set of pages of FLASH USER memory in polling mode.
- Use the HAL_FLASH_EraseBank() function to erase a specific bank of FLASH memory in polling mode.
- Use the HAL_FLASH_MassErase() function to erase all the FLASH memory in polling mode.
- Use the HAL_FLASH_CalculateCRCByAddr() function to calculate the CRC by address in polling mode.
- Use the HAL_FLASH_CalculateCRCByPage() function to calculate the CRC by page in polling mode.
- Use the HAL_FLASH_CalculateCRCByBank() function to calculate the CRC by bank in polling mode.

### Interrupt mode operations
- Configure the FLASH interrupt priority using HAL_CORTEX_NVIC_SetPriority() function
- Enable the FLASH IRQ handler using HAL_CORTEX_NVIC_EnableIRQ() function

- Use the HAL_FLASH_ProgramByAddr_IT() function to program by address any area of FLASH USER memory in interrupt mode.
- Use the HAL_FLASH_ProgramByAddrAdapt_IT() function to program by address using adaptive width any area of FLASH USER
  memory in interrupt mode.
- Use the HAL_FLASH_OTP_ProgramByAddr_IT() function to program by address any area of OTP area in interrupt mode.
- Use the HAL_FLASH_OTP_ProgramByAddrAdapt_IT() function to program by address using adaptive width any area of OTP area
  in interrupt mode.
- Use the HAL_FLASH_EraseByAddr_IT() function to erase by address the FLASH USER memory in interrupt mode.
- Use the HAL_FLASH_ErasePage_IT() function to erase by page the FLASH USER memory in interrupt mode.
- Use the HAL_FLASH_EraseBank_IT() function to erase a bank of FLASH memory in interrupt mode.
- Use the HAL_FLASH_MassErase_IT() function to erase all the FLASH memory in interrupt mode.
- Use the HAL_FLASH_CalculateCRCByAddr_IT() function to calculate the CRC by address in interrupt mode.
- Use the HAL_FLASH_CalculateCRCByPage_IT() function to calculate the CRC by page in interrupt mode.
- Use the HAL_FLASH_CalculateCRCByBank_IT() function to calculate the CRC by bank in interrupt mode.

- Use the HAL_FLASH_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle any FLASH
  interrupt.
- Use the HAL_FLASH_ProgramByAddr_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH program interrupt.
- Use the HAL_FLASH_EraseByAddr_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH erase by address interrupt.
- Use the HAL_FLASH_ErasePage_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH erase page interrupt.
- Use the HAL_FLASH_EraseBank_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH erase bank interrupt.
- Use the HAL_FLASH_MassErase_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH mass erase interrupt.
- Use the HAL_FLASH_CalculateCRC_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH CRC calculation interrupt.
- Use the HAL_FLASH_ECC_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any ECC single error interrupt.
- Use the HAL_FLASH_BusFault_IRQHandler() function called under BusFault_Handler interrupt subroutine to handle
  any Bus Fault FLASH interrupt.

## Callback registration

When the compilation flag USE_HAL_FLASH_REGISTER_CALLBACKS is set to 1, the following functions allow to register
the different FLASH callbacks:
- Use the HAL_FLASH_RegisterProgramCpltCallback() function to register the FLASH program complete callback.
- Use the HAL_FLASH_RegisterEraseByAddrCpltCallback() function to register the FLASH erase by address complete callback.
- Use the HAL_FLASH_RegisterErasePageCpltCallback() function to register the FLASH erase by page complete callback.
- Use the HAL_FLASH_RegisterEraseBankCpltCallback() function to register the FLASH bank erase complete callback.
- Use the HAL_FLASH_RegisterMassEraseCpltCallback() function to register the FLASH mass erase complete callback.
- Use the HAL_FLASH_RegisterCalculateCRCCpltCallback() function to register the FLASH CRC calculation complete callback.
- Use the HAL_FLASH_RegisterErrorCallback() function to register the FLASH error callback.
- Use the HAL_FLASH_RegisterECCErrorCallback() function to register the FLASH ECC error callback.

When the compilation flag USE_HAL_FLASH_REGISTER_CALLBACKS is undefined or set to 0, the callback registration feature
is not available and all callbacks are set to the following weak functions:
- The HAL_FLASH_ProgramCpltCallback() function for the program complete callback.
- The HAL_FLASH_EraseByAddrCpltCallback() function for the erase by address complete callback.
- The HAL_FLASH_ErasePageCpltCallback() function for the erase by page complete callback.
- The HAL_FLASH_EraseBankCpltCallback() function for the erase bank complete callback.
- The HAL_FLASH_MassEraseCpltCallback() function for the mass erase complete callback.
- The HAL_FLASH_CalculateCRCCpltCallback() function for the CRC calculation complete callback.
- The HAL_FLASH_ErrorCallback() function for the error callback.
- The HAL_FLASH_ECC_ErrorCallback() function for the ECC error callback.

These weak functions can be redefined within user application if the callbacks are needed.

## Status functions

- Use the HAL_FLASH_GetCurrentOperation() function to get the current flash operation.
- Use the HAL_FLASH_GetCurrentProgrammedAddr() function to get the currently being programmed flash address.
- Use the HAL_FLASH_GetCurrentErasedAddr() function to get the currently being erased flash address.
- Use the HAL_FLASH_GetCurrentErasedPage() function to get the currently being erased flash page.
- Use the HAL_FLASH_GetInfo() function to get the FLASH information.
- Use the HAL_FLASH_GetSizeByte() function to get the FLASH total size.
- Use the HAL_FLASH_GetBankNbr() function to get the FLASH number of banks.
- Use the HAL_FLASH_GetBankSizeByte() function to get the FLASH bank size.
- Use the HAL_FLASH_GetUserFlashSizeByte() function to get the FLASH USER area size within a bank.
- Use the HAL_FLASH_GetUserFlashPageNbr() function to get the number of pages in FLASH USER area.
- Use the HAL_FLASH_GetUserFlashPageSizeByte() function to get the size of a given page in FLASH USER area.
- Use the HAL_FLASH_GetUserFlashAddrOffset() function to get the address offset of a specific page in FLASH USER area.
- Use the HAL_FLASH_ECC_GetInfo() function to get the FLASH ECC information.
- Use the HAL_FLASH_GetInstance() function to get the HAL FLASH instance.
- Use the HAL_FLASH_GetLLInstance() function to get the hardware FLASH instance.
- Use the HAL_FLASH_GetState() function to get the flash global state.
- Use the HAL_FLASH_GetBankState() function to get the flash bank state.
- Use the HAL_FLASH_GetLastErrorCodes() function to get the last error codes.
- Use the HAL_FLASH_SetUserData() function to set user data within the FLASH handle.
- Use the HAL_FLASH_GetUserData() function to get the user data from the FLASH handle.
  */
/**
  * @}
  */

/** @defgroup FLASH_Configuration_Table FLASH Configuration Table
  * @{
# Configuration inside the FLASH driver

Configuration defines           | Description     | Default value   | Note                                             |
--------------------------------| --------------- | --------------- | -------------------------------------------------|
PRODUCT                         | from IDE        |        NA       | The selected device (ex STM32H7P5xx)             |
USE_HAL_FLASH_MODULE            | from hal_conf.h |        1        | Allows to use HAL FLASH module.                  |
USE_ASSERT_DBG_PARAM            | from IDE        |      None       | Allows to use the assert check parameters.       |
USE_ASSERT_DBG_STATE            | from IDE        |      None       | Allows to use the assert check states.           |
USE_HAL_CHECK_PARAM             | from hal_conf.h |        0        | Allows to use the run-time checks parameters.    |
USE_HAL_CHECK_PROCESS_STATE     | from hal_conf.h |        0        | Allows to use the load and store exclusive.      |
USE_HAL_FLASH_REGISTER_CALLBACKS| from hal_conf.h |        0        | Allows to use the register callbacks             |
USE_HAL_FLASH_GET_LAST_ERRORS   | from hal_conf.h |        0        | Allows to use error code mechanism.              |
USE_HAL_FLASH_USER_DATA         | from hal_conf.h |        0        | Allows to use user data.                         |
USE_HAL_FLASH_PROGRAM_BY_ADDR   | from hal_conf.h |        1        | Allows to use program by address feature APIs    |
USE_HAL_FLASH_ERASE_BY_ADDR     | from hal_conf.h |        1        | Allows to use erase by address feature APIs      |
USE_HAL_FLASH_ERASE_PAGE        | from hal_conf.h |        1        | Allows to use erase by page feature APIs         |
USE_HAL_FLASH_ERASE_BANK        | from hal_conf.h |        1        | Allows to use erase by bank feature APIs         |
USE_HAL_FLASH_MASS_ERASE        | from hal_conf.h |        1        | Allows to use mass erase feature APIs            |
USE_HAL_FLASH_CALCULATE_CRC     | from hal_conf.h |        1        | Allows to use calculate CRC feature APIs         |
USE_HAL_FLASH_ECC               | from hal_conf.h |        1        | Allows to use ECC errors handling APIs           |
  */
/**
  * @}
  */

/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_OPERATION_MAX_TIMEOUT              1000U /*!< FLASH Operation maximum timeout in ms           */
#define FLASH_PROGRAM_OPERATION_QUADWORD_TIMEOUT 1U    /*!< FLASH Program operation quad-word timeout in ms */
#define FLASH_ERASE_PAGE_OPERATION_TIMEOUT       10U   /*!< FLASH Erase page operation timeout in ms        */

#define FLASH_QUADWORD_SIZE_BYTE   16U /*!< FLASH quad-word size in bytes   */
#define FLASH_DOUBLEWORD_SIZE_BYTE 8U  /*!< FLASH double-word size in bytes */
#define FLASH_WORD_SIZE_BYTE       4U  /*!< FLASH word size in bytes        */
#define FLASH_HALFWORD_SIZE_BYTE   2U  /*!< FLASH half-word size in bytes   */
/**
  * @}
  */

/* Private Macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */

/*! Macro to get the FLASH physical instance from the handle */
#define FLASH_GET_INSTANCE(hflash) ((FLASH_TypeDef *)((uint32_t)((hflash)->instance)))

/*! Macro to check FLASH instance */
#define IS_FLASH_INSTANCE(instance) ((instance) == FLASH)

/*! Macro to check FLASH memory programming mode type */
#define IS_FLASH_PROGRAM_MODE_TYPE(mode) (((mode) == HAL_FLASH_PROGRAM_QUADWORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_DOUBLEWORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_WORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_HALFWORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_BYTE))

/*! Macro to check FLASH memory bank */
#define IS_FLASH_BANK(value) (((value) == HAL_FLASH_BANK_1)    \
                              || ((value) == HAL_FLASH_BANK_2))

/*! Macro to check the FLASH user bank boundary cross */
#define IS_FLASH_NO_USER_CROSS_BANK(addr, size) (((addr) < (FLASH_BASE + FLASH_BANK_SIZE)) \
                                                 ? (((addr) + (size)) <= (FLASH_BASE + FLASH_BANK_SIZE)) \
                                                 : (((addr) + (size)) <= (FLASH_BASE + FLASH_SIZE)))

/*! Macro to check FLASH memory address granularity */
#define IS_FLASH_ADDRESS(value) (((value) >= FLASH_BASE) \
                                 ? (((value) % (uint32_t)HAL_FLASH_PROGRAM_QUADWORD) == 0U) : (0 == 1))

/*! Macro to check FLASH memory size_byte in range */
#define IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte) (((flash_addr) + (size_byte)) \
                                                       <= (FLASH_BASE + FLASH_SIZE_DEFAULT))

/*! Macro to check FLASH memory address granularity */
#define IS_FLASH_OTP_ADDRESS(value) (((value) >= OTP_AREA_BASE) && ((value) < (OTP_AREA_BASE + FLASH_OTP_SIZE)) \
                                     && (((value) % FLASH_HALFWORD_SIZE_BYTE) == 0U))

/*! Macro to check FLASH memory size_byte in range */
#define IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte) (((otp_addr) + (size_byte)) \
                                                         <= (OTP_AREA_BASE + FLASH_OTP_SIZE))

/*! Macro to check FLASH USER programming size */
#define IS_FLASH_USER_PROGRAM_SIZE(value) \
  ((((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == ((uint32_t) HAL_FLASH_PROGRAM_DOUBLEWORD)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == ((uint32_t) HAL_FLASH_PROGRAM_WORD)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == ((uint32_t) HAL_FLASH_PROGRAM_HALFWORD)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == (1U)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == (0U)))

/*! Macro to check FLASH memory start page and page number in range */
#define IS_FLASH_PAGE_IN_RANGE(page, page_nbr) (((page) + (page_nbr)) <= (uint32_t)FLASH_PAGE_NB)

/*! Macro to check FLASH CRC burst size */
#define IS_FLASH_CRC_BURST_SIZE(value) (((value) == HAL_FLASH_CRC_BURST_SIZE_4)    \
                                        || ((value) == HAL_FLASH_CRC_BURST_SIZE_16)\
                                        || ((value) == HAL_FLASH_CRC_BURST_SIZE_64)\
                                        || ((value) == HAL_FLASH_CRC_BURST_SIZE_256))
/**
  * @}
  */

/* Private Functions Prototypes --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)) \
    || (defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)) \
    || (defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1))
static hal_status_t     FLASH_IsReadyForOperation(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
          || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE || USE_HAL_FLASH_CALCULATE_CRC */

static hal_status_t     FLASH_WaitForEndOfOperation(hal_flash_handle_t *hflash,
                                                    hal_flash_bank_t bank,
                                                    uint32_t timeout_ms);

static uint32_t FLASH_GetBankReg(const hal_flash_handle_t *hflash, hal_flash_bank_t bank);

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
static uint32_t FLASH_GetProgramSize(hal_flash_program_mode_t programming_mode);
static hal_flash_program_unit_func_t FLASH_GetProgramUnitFunction(hal_flash_program_mode_t programming_mode);
static void             FLASH_UpdateAdaptiveProgMode(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
static hal_status_t     FLASH_Program(hal_flash_handle_t *hflash, uint32_t flash_addr, const uint32_t *p_data,
                                      uint32_t size_byte, uint32_t timeout_ms);
static hal_status_t FLASH_Program_IT(hal_flash_handle_t *hflash, uint32_t flash_addr, const uint32_t *p_data,
                                     uint32_t size_byte);
static void             FLASH_ProgramByWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
static void             FLASH_ProgramByHalfWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
static void             FLASH_ProgramByByte(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
static uint32_t         FLASH_GetPageIndexByAddr(uint32_t flash_addr);
static hal_status_t     FLASH_EraseAddr(hal_flash_handle_t *hflash,
                                        uint32_t flash_addr,
                                        uint32_t size_byte,
                                        uint32_t page_size,
                                        uint32_t timeout_ms);
static hal_status_t     FLASH_EraseAddr_IT(hal_flash_handle_t *hflash,
                                           uint32_t flash_addr,
                                           uint32_t size_byte);
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
static hal_status_t     FLASH_ErasePage(hal_flash_handle_t *hflash,
                                        hal_flash_bank_t bank,
                                        uint32_t start_page,
                                        uint32_t page_nbr,
                                        uint32_t timeout_ms);
static hal_status_t     FLASH_ErasePage_IT(hal_flash_handle_t *hflash,
                                           hal_flash_bank_t bank,
                                           uint32_t start_page,
                                           uint32_t page_nbr);
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1))
static hal_flash_bank_t FLASH_GetBank(const hal_flash_handle_t *hflash, uint32_t flash_addr);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_CALCULATE_CRC */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1))
static uint32_t         FLASH_IsFlashUSERAddr(uint32_t flash_addr, uint8_t check_program_alignment);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
static void             FLASH_FillErrorCode(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)) \
    || (defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)) \
    || (defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1))
static void FLASH_HandleErrorIT(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
          || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE || USE_HAL_FLASH_CALCULATE_CRC */

/**
  * @}
  */

/* Exported Functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and de-initialize the FLASH peripheral:
- Call the function HAL_FLASH_Init() to initialize the FLASH handle and associate a physical FLASH instance.

- Call the function HAL_FLASH_DeInit() to de-initialize the FLASH handle.
  */

/**
  * @brief  Initialize the FLASH handle and associate a physical FLASH instance.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  instance          Specifies the FLASH instance based on \ref hal_flash_t enumeration.
  * @retval HAL_INVALID_PARAM Invalid parameter when hflash pointer is NULL.
  * @retval HAL_OK            FLASH is successfully initialized.
  */
hal_status_t HAL_FLASH_Init(hal_flash_handle_t *hflash, hal_flash_t instance)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE((FLASH_TypeDef *)(uint32_t)instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hflash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->instance = instance;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
  hflash->p_program_cplt_cb       = HAL_FLASH_ProgramCpltCallback;
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
  hflash->p_erase_by_addr_cplt_cb = HAL_FLASH_EraseByAddrCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
  hflash->p_erase_page_cplt_cb    = HAL_FLASH_ErasePageCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_PAGE */
#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)
  hflash->p_erase_bank_cplt_cb    = HAL_FLASH_EraseBankCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)
  hflash->p_mass_erase_cplt_cb    = HAL_FLASH_MassEraseCpltCallback;
#endif /* USE_HAL_FLASH_MASS_ERASE */
#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
  hflash->p_calculate_crc_cplt_cb = HAL_FLASH_CalculateCRCCpltCallback;
#endif /* USE_HAL_FLASH_CALCULATE_CRC */
  hflash->p_error_cb              = HAL_FLASH_ErrorCallback;
#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
  hflash->p_ecc_error_cb          = HAL_FLASH_ECC_ErrorCallback;
#endif /* USE_HAL_FLASH_ECC */
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */

#if defined(USE_HAL_FLASH_USER_DATA) && (USE_HAL_FLASH_USER_DATA == 1)
  hflash->p_user_data = NULL;
#endif /* USE_HAL_FLASH_USER_DATA */

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes[0] = HAL_FLASH_ERROR_NONE;
  hflash->last_error_codes[1] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  hflash->ongoing_operation[0] = HAL_FLASH_NO_OPERATION;
  hflash->ongoing_operation[1] = HAL_FLASH_NO_OPERATION;

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
  hflash->programming_mode[0] = HAL_FLASH_PROGRAM_QUADWORD;
  hflash->programming_mode[1] = HAL_FLASH_PROGRAM_QUADWORD;
  hflash->prog_size_byte[0] = FLASH_QUADWORD_SIZE_BYTE;
  hflash->prog_size_byte[1] = FLASH_QUADWORD_SIZE_BYTE;
  hflash->p_prog_unit_func[0] = FLASH_ProgramByWord;
  hflash->p_prog_unit_func[1] = FLASH_ProgramByWord;
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1U)
  hflash->crc_burst_size = HAL_FLASH_CRC_BURST_SIZE_4;
#endif /* USE_HAL_FLASH_CALCULATE_CRC */

  hflash->global_state = HAL_FLASH_STATE_IDLE;
  hflash->bank_state[0] = HAL_FLASH_BANK_STATE_IDLE;
  hflash->bank_state[1] = HAL_FLASH_BANK_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  De-initialize the FLASH handle.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_DeInit(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(FLASH_GET_INSTANCE(hflash)));

  (void)FLASH_WaitForEndOfOperation(hflash, HAL_FLASH_BANK_1, FLASH_OPERATION_MAX_TIMEOUT);
  (void)FLASH_WaitForEndOfOperation(hflash, HAL_FLASH_BANK_2, FLASH_OPERATION_MAX_TIMEOUT);

  hflash->global_state = HAL_FLASH_STATE_RESET;
  hflash->bank_state[0] = HAL_FLASH_BANK_STATE_RESET;
  hflash->bank_state[1] = HAL_FLASH_BANK_STATE_RESET;
}
/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the FLASH peripheral:

- Call the function HAL_FLASH_SetProgrammingMode() to set the programming mode according to selected parameter within
  @ref hal_flash_program_mode_t enumeration for both banks.

- Call the function HAL_FLASH_GetProgrammingMode() to get the current configured programming mode retrieved
  from bank 1, use HAL_FLASH_SetBankProgrammingMode() and HAL_FLASH_GetBankProgrammingMode() to use different
  programming modes per bank.

- Call the function HAL_FLASH_SetBankProgrammingMode() to set the programming mode according to selected parameter
  within @ref hal_flash_program_mode_t enumeration for the selected bank.

- Call the function HAL_FLASH_GetBankProgrammingMode() to get the current configured programming mode
  for the selected bank.

- Call the function HAL_FLASH_SetCRCBurstSize() to set the CRC burst size according to selected parameter within
  @ref hal_flash_crc_burst_size_t enumeration.

- Call the function HAL_FLASH_GetCRCBurstSize() to get the current configured CRC burst size.
  */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
/**
  * @brief  Set the FLASH programming mode configuration for both banks.
  * @param  hflash           Pointer to a \ref hal_flash_handle_t structure.
  * @param  programming_mode This parameter is one element of \ref hal_flash_program_mode_t enumeration.
  * @retval HAL_OK           Programming mode is successfully configured.
  */
hal_status_t HAL_FLASH_SetProgrammingMode(hal_flash_handle_t *hflash, hal_flash_program_mode_t programming_mode)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(programming_mode));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[1], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  hflash->programming_mode[0] = programming_mode;
  hflash->programming_mode[1] = programming_mode;
  hflash->prog_size_byte[0] = FLASH_GetProgramSize(programming_mode);
  hflash->prog_size_byte[1] = hflash->prog_size_byte[0];
  hflash->p_prog_unit_func[0] = FLASH_GetProgramUnitFunction(programming_mode);
  hflash->p_prog_unit_func[1] = hflash->p_prog_unit_func[0];

  return HAL_OK;
}

/**
  * @brief  Get the FLASH programming mode configuration for the bank 1.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval hal_flash_program_mode_t Programming mode value.
  */
hal_flash_program_mode_t HAL_FLASH_GetProgrammingMode(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[1], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return (hflash->programming_mode[0]);
}

/**
  * @brief  Set the FLASH programming mode configuration for the selected bank.
  * @param  hflash           Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank             This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  programming_mode This parameter is one element of \ref hal_flash_program_mode_t enumeration.
  * @retval HAL_OK           Programming mode is successfully configured.
  */
hal_status_t HAL_FLASH_SetBankProgrammingMode(hal_flash_handle_t *hflash,
                                              hal_flash_bank_t bank,
                                              hal_flash_program_mode_t programming_mode)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(programming_mode));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  hflash->programming_mode[(uint32_t)bank] = programming_mode;
  hflash->prog_size_byte[(uint32_t)bank] = FLASH_GetProgramSize(programming_mode);
  hflash->p_prog_unit_func[(uint32_t)bank] = FLASH_GetProgramUnitFunction(programming_mode);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH programming mode configuration for the selected bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_program_mode_t Programming mode value.
  */
hal_flash_program_mode_t HAL_FLASH_GetBankProgrammingMode(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return (hflash->programming_mode[(uint32_t)bank]);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
/**
  * @brief  Set the FLASH CRC Burst size.
  * @param  hflash     Pointer to a \ref hal_flash_handle_t structure.
  * @param  burst_size This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @retval HAL_OK     CRC burst size is successfully configured.
  */
hal_status_t HAL_FLASH_SetCRCBurstSize(hal_flash_handle_t *hflash, hal_flash_crc_burst_size_t burst_size)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(burst_size));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  hflash->crc_burst_size = burst_size;

  return HAL_OK;
}

/**
  * @brief  Get the FLASH CRC Burst size.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval hal_flash_crc_burst_size_t CRC burst size value.
  */
hal_flash_crc_burst_size_t HAL_FLASH_GetCRCBurstSize(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  return hflash->crc_burst_size;
}
#endif /* USE_HAL_FLASH_CALCULATE_CRC */
/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to program and erase the FLASH memory:
- Call the function HAL_FLASH_ProgramByAddr() to program the FLASH USER memory by address in polling mode.

- Call the function HAL_FLASH_ProgramByAddr_IT() to program the FLASH USER memory by address in interrupt mode.

- Call the function HAL_FLASH_ProgramByAddrAdapt() to program the FLASH USER memory by address using adaptive width in
  polling mode.

- Call the function HAL_FLASH_ProgramByAddrAdapt_IT() to program the FLASH USER memory by address using adaptive width
  in interrupt mode.

- Call the function HAL_FLASH_OTP_ProgramByAddr() to program the OTP area by address in polling mode.

- Call the function HAL_FLASH_OTP_ProgramByAddr_IT() to program the OTP area by address in interrupt mode.

- Call the function HAL_FLASH_OTP_ProgramByAddrAdapt() to program the OTP Area by address using adaptive width in
  polling mode.

- Call the function HAL_FLASH_OTP_ProgramByAddrAdapt_IT() to program the OTP Area by address using adaptive width in
  interrupt mode.

- Call the function HAL_FLASH_EraseByAddr() to erase the FLASH USER memory by address in polling mode.

- Call the function HAL_FLASH_EraseByAddr_IT() to erase the FLASH USER memory by address in interrupt mode.

- Call the function HAL_FLASH_ErasePage() to erase the FLASH USER memory by page in polling mode.

- Call the function HAL_FLASH_ErasePage_IT() to erase the FLASH USER memory by page in interrupt mode.

- Call the function HAL_FLASH_EraseBank() to erase the FLASH memory by bank in polling mode.

- Call the function HAL_FLASH_EraseBank_IT() to erase the FLASH memory by bank in interrupt mode.

- Call the function HAL_FLASH_MassErase() to mass erase the complete FLASH memory in polling mode.

- Call the function HAL_FLASH_MassErase_IT() to mass erase the complete FLASH memory in interrupt mode.

- Call the function HAL_FLASH_CalculateCRCByAddr() to calculate the CRC by address in polling mode.

- Call the function HAL_FLASH_CalculateCRCByAddr_IT() to calculate the CRC by address in interrupt mode.

- Call the function HAL_FLASH_CalculateCRCByPage() to calculate the CRC by page in polling mode.

- Call the function HAL_FLASH_CalculateCRCByPage_IT() to calculate the CRC by page in interrupt mode.

- Call the function HAL_FLASH_CalculateCRCByBank() to calculate the CRC by bank in polling mode.

- Call the function HAL_FLASH_CalculateCRCByBank_IT() to calculate the CRC by bank in interrupt mode.

- Call the function HAL_FLASH_IRQHandler() to handle any enabled interrupt and call its corresponding callback.

- Call the function HAL_FLASH_ProgramByAddr_IRQHandler() to handle any enabled FLASH program interrupt and call
  its corresponding callback.

- Call the function HAL_FLASH_EraseByAddr_IRQHandler() to handle any enabled FLASH erase by address interrupt and call
  its corresponding callback.

- Call the function HAL_FLASH_ErasePage_IRQHandler() to handle any enabled FLASH erase page interrupt and call
  its corresponding callback.

- Call the function HAL_FLASH_EraseBank_IRQHandler() to handle any enabled FLASH erase bank interrupt and call
  its corresponding callback.

- Call the function HAL_FLASH_MassErase_IRQHandler() to handle any enabled FLASH mass erase interrupt and call
  its corresponding callback.

- Call the function HAL_FLASH_CalculateCRC_IRQHandler() to handle any enabled FLASH CRC calculation interrupt and call
  its corresponding callback.

- Call the function HAL_FLASH_ECC_IRQHandler() to handle any enabled interrupt and call its corresponding
  callback.

- Call the function HAL_FLASH_BusFault_IRQHandler() to handle any bus fault interrupt and call its corresponding
  callback.
  */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
/**
  * @brief  Program the FLASH memory at specified user address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_ms        Timeout value for programming.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddr(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte,
                                     uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(hflash->programming_mode[(uint32_t)FLASH_GetBank(hflash, flash_addr)]));
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM((size_byte \
                    % FLASH_GetProgramSize(hflash->programming_mode[(uint32_t)FLASH_GetBank(hflash, flash_addr)])) \
                   == 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)FLASH_GetBank(hflash, flash_addr)], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[(uint32_t)FLASH_GetBank(hflash, flash_addr)] = 0U;

  return FLASH_Program(hflash, flash_addr, p_data, size_byte, timeout_ms);
}

/**
  * @brief  Program the FLASH memory at specified address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                        uint32_t flash_addr,
                                        const uint32_t *p_data,
                                        uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(hflash->programming_mode[(uint32_t)FLASH_GetBank(hflash, flash_addr)]));
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM((size_byte \
                    % FLASH_GetProgramSize(hflash->programming_mode[(uint32_t)FLASH_GetBank(hflash, flash_addr)])) \
                   == 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)FLASH_GetBank(hflash, flash_addr)], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[(uint32_t)FLASH_GetBank(hflash, flash_addr)] = 0U;

  return FLASH_Program_IT(hflash, flash_addr, p_data, size_byte);
}

/**
  * @brief  Program the FLASH memory at specified user address using adaptive width in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_ms        Timeout value for programming.
  * @note   The adaptive mode optimizes FLASH programming access based on the remaining data size,
  *         ignoring the programming mode selected by the HAL_FLASH_SetProgrammingMode()
  *         or HAL_FLASH_SetBankProgrammingMode() APIs.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                          uint32_t flash_addr,
                                          const uint32_t *p_data,
                                          uint32_t size_byte,
                                          uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)FLASH_GetBank(hflash, flash_addr)], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[(uint32_t)FLASH_GetBank(hflash, flash_addr)] = 1U;

  return FLASH_Program(hflash, flash_addr, p_data, size_byte, timeout_ms);
}

/**
  * @brief  Program the FLASH memory at specified address using adaptive width in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @note   The adaptive mode optimizes FLASH programming access based on the remaining data size,
  *         ignoring the programming mode selected by the HAL_FLASH_SetProgrammingMode()
  *         or HAL_FLASH_SetBankProgrammingMode() APIs.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                             uint32_t flash_addr,
                                             const uint32_t *p_data,
                                             uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)FLASH_GetBank(hflash, flash_addr)], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[(uint32_t)FLASH_GetBank(hflash, flash_addr)] = 1U;

  return FLASH_Program_IT(hflash, flash_addr, p_data, size_byte);
}

/**
  * @brief  Program the OTP area at specified address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_ms        Timeout value for programming.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddr(hal_flash_handle_t *hflash,
                                         uint32_t otp_addr,
                                         const uint32_t *p_data,
                                         uint32_t size_byte,
                                         uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((hflash->programming_mode[0] == HAL_FLASH_PROGRAM_HALFWORD) \
                   || (hflash->programming_mode[0] == HAL_FLASH_PROGRAM_WORD));
  ASSERT_DBG_PARAM((size_byte != 0U) && ((size_byte % FLASH_GetProgramSize(hflash->programming_mode[0])) == 0U));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_FLASH_OTP_ADDRESS(otp_addr) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[0] = 0U;

  return FLASH_Program(hflash, otp_addr, p_data, size_byte,  timeout_ms);
}

/**
  * @brief  Program the OTP area at specified address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                            uint32_t otp_addr,
                                            const uint32_t *p_data,
                                            uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((hflash->programming_mode[0] == HAL_FLASH_PROGRAM_HALFWORD) \
                   || (hflash->programming_mode[0] == HAL_FLASH_PROGRAM_WORD));
  ASSERT_DBG_PARAM((size_byte != 0U) && ((size_byte % FLASH_GetProgramSize(hflash->programming_mode[0])) == 0U));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_FLASH_OTP_ADDRESS(otp_addr) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[0] = 0U;

  return FLASH_Program_IT(hflash, otp_addr, p_data, size_byte);
}

/**
  * @brief  Program the OTP area at specified address using adaptive width in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_ms        Timeout value for programming.
  * @note   The adaptive mode optimizes FLASH programming access based on the remaining data size,
  *         ignoring the programming mode selected by the HAL_FLASH_SetProgrammingMode()
  *         or HAL_FLASH_SetBankProgrammingMode() APIs.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                              uint32_t otp_addr,
                                              const uint32_t *p_data,
                                              uint32_t size_byte,
                                              uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((size_byte != 0U) && ((size_byte % FLASH_HALFWORD_SIZE_BYTE) == 0U));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_FLASH_OTP_ADDRESS(otp_addr) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[0] = 1U;

  return FLASH_Program(hflash, otp_addr, p_data, size_byte, timeout_ms);
}

/**
  * @brief  Program the OTP area at specified address using adaptive width in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @note   The adaptive mode optimizes FLASH programming access based on the remaining data size,
  *         ignoring the programming mode selected by the HAL_FLASH_SetProgrammingMode()
  *         or HAL_FLASH_SetBankProgrammingMode() APIs.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                                 uint32_t otp_addr,
                                                 const uint32_t *p_data,
                                                 uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((size_byte != 0U) && ((size_byte % FLASH_HALFWORD_SIZE_BYTE) == 0U));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_FLASH_OTP_ADDRESS(otp_addr) == 0U) || (p_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }

  if ((IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->is_adaptive_prog[0] = 1U;

  return FLASH_Program_IT(hflash, otp_addr, p_data, size_byte);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
/**
  * @brief  Erase the FLASH memory at specified address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash page to be erased.
  *                           This parameter must be aligned with the start of a page.
  * @param  size_byte         Size of the area to be erased (in bytes).
  *                           This parameter must be a multiple of the page size.
  * @param  timeout_ms        Timeout value for erasing.
  * @warning Since the smallest erase granularity is at page level, this function will erase a greater area than the one
  *          defined by flash_addr and size_byte if these parameters do not represent an area aligned with the start
  *          and the end of flash pages.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseByAddr(hal_flash_handle_t *hflash,
                                   uint32_t flash_addr,
                                   uint32_t size_byte,
                                   uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr  + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)FLASH_GetBank(hflash, flash_addr)], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U) || (!IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte)))
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_EraseAddr(hflash, flash_addr, size_byte, FLASH_PAGE_SIZE, timeout_ms);
}

/**
  * @brief  Erase the FLASH memory at specified address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash page to be erased.
  *                           This parameter must be aligned with the start of a page.
  * @param  size_byte         Size of the data to be erased (in bytes).
  *                           This parameter must be a multiple of the page size.
  * @warning Since the smallest erase granularity is at page level, this function will erase a greater area than the one
  *          defined by flash_addr and size_byte if these parameters do not represent an area aligned with the start
  *          and the end of flash pages.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseByAddr_IT(hal_flash_handle_t *hflash,
                                      uint32_t flash_addr,
                                      uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr  + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)FLASH_GetBank(hflash, flash_addr)], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U) || (!IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte)))
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_EraseAddr_IT(hflash, flash_addr, size_byte);
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
/**
  * @brief  Erase the FLASH memory by page in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page              First page to be erased.
  * @param  page_nbr          Number of pages to be erased.
  * @param  timeout_ms        Timeout value for page erasing.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_ErasePage(hal_flash_handle_t *hflash,
                                 hal_flash_bank_t bank,
                                 uint32_t page,
                                 uint32_t page_nbr,
                                 uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return FLASH_ErasePage(hflash, bank, page, page_nbr, timeout_ms);
}

/**
  * @brief  Erase the FLASH memory by page in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page              First page to be erased.
  * @param  page_nbr          Number of pages to be erased.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_ErasePage_IT(hal_flash_handle_t *hflash,
                                    hal_flash_bank_t bank,
                                    uint32_t page,
                                    uint32_t page_nbr)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return FLASH_ErasePage_IT(hflash, bank, page, page_nbr);
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)
/**
  * @brief   Erase the FLASH memory by bank in polling mode.
  * @param   hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param   bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param   timeout_ms        Timeout value for bank erasing.
  * @warning This function will erase a specific Flash bank, thus it must not be mapped in this bank.
  * @retval  HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval  HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval  HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval  HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseBank(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t timeout_ms)
{
  hal_status_t status;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  bank_reg = FLASH_GetBankReg(hflash, bank);
  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_BANK_ERASE;

    LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), bank_reg);

    status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_ms);

    LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), bank_reg);

    if (status == HAL_OK)
    {
      hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_NO_OPERATION;
    }

    hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief   Erase the FLASH memory by bank in interrupt mode.
  * @param   hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param   bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @warning This function will erase a specific Flash bank, thus it must not be mapped in this bank.
  * @retval  HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval  HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval  HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseBank_IT(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  hal_status_t status;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  bank_reg = FLASH_GetBankReg(hflash, bank);
  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank]  = HAL_FLASH_BANK_ERASE;

    LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
    LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  return status;
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)
/**
  * @brief   Mass erase the FLASH memory in polling mode.
  * @param   hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param   timeout_ms        Timeout value for mass erasing.
  * @warning This function will erase the whole Flash, thus it must not be mapped in the Flash area.
  * @retval  HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval  HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval  HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval  HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_MassErase(hal_flash_handle_t *hflash, uint32_t timeout_ms)
{
  hal_status_t status1, status2;
  uint32_t     bank_idx;
  uint32_t     bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[1], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  status1 = FLASH_IsReadyForOperation(hflash, HAL_FLASH_BANK_1);
  status2 = FLASH_IsReadyForOperation(hflash, HAL_FLASH_BANK_2);

  if (status1 != HAL_OK)
  {
    return status1;
  }
  else if (status2 != HAL_OK)
  {
    return status2;
  }
  else
  {
    for (bank_idx = 0U; bank_idx <= 1U; bank_idx ++)
    {
      HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      hflash->ongoing_operation[bank_idx] = HAL_FLASH_MASS_ERASE;
    }

    LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_1);
    LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_2);

    for (bank_idx = 0U; bank_idx <= 1U; bank_idx ++)
    {
      bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

      status2 = FLASH_WaitForEndOfOperation(hflash, (hal_flash_bank_t)bank_idx, timeout_ms);

      LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), bank_reg);

      if (status2 == HAL_OK)
      {
        hflash->ongoing_operation[(uint32_t)bank_idx] = HAL_FLASH_NO_OPERATION;
      }

      hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

      if ((status1 != HAL_ERROR) && (status2 != HAL_OK))
      {
        status1 = status2;
      }
    }

    return status1;
  }
}

/**
  * @brief   Mass erase the FLASH memory in interrupt mode.
  * @param   hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @warning This function will erase the whole Flash, thus it must not be mapped in the Flash area.
  * @retval  HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval  HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval  HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_MassErase_IT(hal_flash_handle_t *hflash)
{
  hal_status_t status1, status2;
  uint32_t     bank_idx;
  uint32_t     bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[1], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  status1 = FLASH_IsReadyForOperation(hflash, HAL_FLASH_BANK_1);
  status2 = FLASH_IsReadyForOperation(hflash, HAL_FLASH_BANK_2);

  if (status1 != HAL_OK)
  {
    return status1;
  }
  else if (status2 != HAL_OK)
  {
    return status2;
  }
  else
  {
    for (bank_idx = 0U; bank_idx <= 1U; bank_idx ++)
    {
      bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

      HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      hflash->ongoing_operation[bank_idx]  = HAL_FLASH_MASS_ERASE;

      LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
    }

    LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_1);
    LL_FLASH_StartEraseBank(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_2);

    return HAL_OK;
  }
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
/**
  * @brief  Perform CRC calculation on an address range in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of the CRC calculation area.
  * @param  size_byte         Size of the region, in bytes, on which the CRC will be calculated.
  * @param  p_result          Pointer to a variable that will receive the CRC result.
  * @param  timeout_ms        Timeout value for CRC calculationg.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the CRC calculation operation complete successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByAddr(hal_flash_handle_t *hflash,
                                          uint32_t flash_addr,
                                          uint32_t size_byte,
                                          uint32_t *p_result,
                                          uint32_t timeout_ms)
{
  hal_status_t     status;
  hal_flash_bank_t bank;
  uint32_t         bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  bank = FLASH_GetBank(hflash, flash_addr);
  bank_reg = FLASH_GetBankReg(hflash, bank);

  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));
  ASSERT_DBG_PARAM(hflash->ongoing_operation[(uint32_t)bank ^ 1U] != HAL_FLASH_CALCULATE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U)
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_CALCULATE_CRC;

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), bank_reg, (uint32_t)hflash->crc_burst_size);
    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCStartAddr(FLASH_GET_INSTANCE(hflash), bank_reg, flash_addr);
    LL_FLASH_SetCRCEndAddr(FLASH_GET_INSTANCE(hflash), bank_reg, flash_addr + (size_byte - 1U));

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), bank_reg);

    status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_ms);

    *p_result = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash));

    LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;

  if (status == HAL_OK)
  {
    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_NO_OPERATION;
  }

  return status;
}

/**
  * @brief  Perform CRC calculation on an address range in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of the CRC calculation area.
  * @param  size_byte         Size of the region, in bytes, on which the CRC will be calculated.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers are locked.
  * @retval HAL_OK            Returned when the CRC calculation operation is successfully started.
  */
hal_status_t HAL_FLASH_CalculateCRCByAddr_IT(hal_flash_handle_t *hflash, uint32_t flash_addr, uint32_t size_byte)
{
  hal_status_t     status;
  hal_flash_bank_t bank;
  uint32_t         bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(size_byte != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  bank = FLASH_GetBank(hflash, flash_addr);
  bank_reg = FLASH_GetBankReg(hflash, bank);

  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));
  ASSERT_DBG_PARAM(hflash->ongoing_operation[(uint32_t)bank ^ 1U] != HAL_FLASH_CALCULATE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (FLASH_IsFlashUSERAddr(flash_addr, 1U) == 0U)
  {
    return HAL_INVALID_PARAM;
  }

  if ((FLASH_IsFlashUSERAddr(flash_addr + size_byte - 1U, 0U) == 0U) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_CALCULATE_CRC;

    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), bank_reg, (uint32_t)hflash->crc_burst_size);
    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCStartAddr(FLASH_GET_INSTANCE(hflash), bank_reg, flash_addr);
    LL_FLASH_SetCRCEndAddr(FLASH_GET_INSTANCE(hflash), bank_reg, flash_addr + (size_byte - 1U));
    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  return status;
}

/**
  * @brief  Perform CRC calculation on a page range in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page              Start page number of the CRC calculation area.
  * @param  page_nbr          Number of pages on which the CRC will be calculated.
  * @param  p_result          Pointer to a variable that will receive the CRC result.
  * @param  timeout_ms        Timeout value for CRC calculation.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers are locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the CRC calculation operation completes successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByPage(hal_flash_handle_t *hflash,
                                          hal_flash_bank_t bank,
                                          uint32_t page,
                                          uint32_t page_nbr,
                                          uint32_t *p_result,
                                          uint32_t timeout_ms)
{
  hal_status_t status;
  uint32_t     bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));
  ASSERT_DBG_PARAM(hflash->ongoing_operation[(uint32_t)bank ^ 1U] != HAL_FLASH_CALCULATE_CRC);
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  bank_reg = FLASH_GetBankReg(hflash, bank);
  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_CALCULATE_CRC;

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), bank_reg, (uint32_t)hflash->crc_burst_size);
    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);

    for (uint32_t page_idx = page; page_idx < (page + page_nbr); page_idx++)
    {
      LL_FLASH_SetCRCPage(FLASH_GET_INSTANCE(hflash), bank_reg, page_idx);
      LL_FLASH_AddCRCPageToList(FLASH_GET_INSTANCE(hflash), bank_reg);
    }

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), bank_reg);

    status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_ms);

    *p_result = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash));

    LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;

  if (status == HAL_OK)
  {
    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_NO_OPERATION;
  }

  return status;
}

/**
  * @brief  Start CRC calculation on a page range in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page              Start page number of the CRC calculation area.
  * @param  page_nbr          Number of pages on which the CRC will be calculated.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers are locked.
  * @retval HAL_OK            Returned when the CRC calculation operation is successfully started.
  */
hal_status_t HAL_FLASH_CalculateCRCByPage_IT(hal_flash_handle_t *hflash,
                                             hal_flash_bank_t bank,
                                             uint32_t page,
                                             uint32_t page_nbr)
{
  hal_status_t status;
  uint32_t     bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));
  ASSERT_DBG_PARAM(hflash->ongoing_operation[(uint32_t)bank ^ 1U] != HAL_FLASH_CALCULATE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  bank_reg = FLASH_GetBankReg(hflash, bank);
  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_CALCULATE_CRC;

    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), bank_reg, (uint32_t)hflash->crc_burst_size);
    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);

    for (uint32_t page_idx = page; page_idx < (page + page_nbr); page_idx++)
    {
      LL_FLASH_SetCRCPage(FLASH_GET_INSTANCE(hflash), bank_reg, page_idx);
      LL_FLASH_AddCRCPageToList(FLASH_GET_INSTANCE(hflash), bank_reg);
    }

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  return status;
}

/**
  * @brief  Perform CRC calculation on a full bank in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  p_result          Pointer to a variable that will receive the CRC result.
  * @param  timeout_ms        Timeout value for CRC calculation.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers are locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the CRC calculation operation completes successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByBank(hal_flash_handle_t *hflash,
                                          hal_flash_bank_t bank,
                                          uint32_t *p_result,
                                          uint32_t timeout_ms)
{
  hal_status_t status;
  uint32_t     bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));
  ASSERT_DBG_PARAM(hflash->ongoing_operation[(uint32_t)bank ^ 1U] != HAL_FLASH_CALCULATE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  bank_reg = FLASH_GetBankReg(hflash, bank);
  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_CALCULATE_CRC;

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), bank_reg, (uint32_t)hflash->crc_burst_size);
    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_EnableCRCAllBank(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), bank_reg);

    status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_ms);

    *p_result = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash));

    LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;

  if (status == HAL_OK)
  {
    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_NO_OPERATION;
  }

  return status;
}

/**
  * @brief  Start CRC calculation on a full bank in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter is selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers are locked.
  * @retval HAL_OK            Returned when the CRC calculation operation is successfully started.
  */
hal_status_t HAL_FLASH_CalculateCRCByBank_IT(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  hal_status_t status;
  uint32_t     bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));
  ASSERT_DBG_PARAM(hflash->ongoing_operation[(uint32_t)bank ^ 1U] != HAL_FLASH_CALCULATE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  bank_reg = FLASH_GetBankReg(hflash, bank);
  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_CALCULATE_CRC;

    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), bank_reg, (uint32_t)hflash->crc_burst_size);
    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_EnableCRCAllBank(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  return status;
}
#endif /* USE_HAL_FLASH_CALCULATE_CRC */

/**
  * @brief  Handle the FLASH interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_IRQHandler(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
  HAL_FLASH_ProgramByAddr_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
  HAL_FLASH_EraseByAddr_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
  HAL_FLASH_ErasePage_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)
  HAL_FLASH_EraseBank_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)
  HAL_FLASH_MassErase_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
  HAL_FLASH_ECC_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_ECC */

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
  HAL_FLASH_CalculateCRC_IRQHandler(hflash);
#endif /* USE_HAL_FLASH_CALCULATE_CRC */

#if (!defined(USE_HAL_FLASH_PROGRAM_BY_ADDR) || (USE_HAL_FLASH_PROGRAM_BY_ADDR != 1)) \
    && (!defined(USE_HAL_FLASH_ERASE_BY_ADDR) || (USE_HAL_FLASH_ERASE_BY_ADDR != 1)) \
    && (!defined(USE_HAL_FLASH_ERASE_PAGE) || (USE_HAL_FLASH_ERASE_PAGE != 1)) \
    && (!defined(USE_HAL_FLASH_ERASE_BANK) || (USE_HAL_FLASH_ERASE_BANK != 1)) \
    && (!defined(USE_HAL_FLASH_MASS_ERASE) || (USE_HAL_FLASH_MASS_ERASE != 1))

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

#endif /* (!defined(USE_HAL_FLASH_PROGRAM_BY_ADDR) || (USE_HAL_FLASH_PROGRAM_BY_ADDR != 1)) \
    && (!defined(USE_HAL_FLASH_ERASE_BY_ADDR) || (USE_HAL_FLASH_ERASE_BY_ADDR != 1)) \
    && (!defined(USE_HAL_FLASH_ERASE_PAGE) || (USE_HAL_FLASH_ERASE_PAGE != 1)) \
    && (!defined(USE_HAL_FLASH_ERASE_BANK) || (USE_HAL_FLASH_ERASE_BANK != 1)) \
    && (!defined(USE_HAL_FLASH_MASS_ERASE) || (USE_HAL_FLASH_MASS_ERASE != 1)) */
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
/**
  * @brief  Handle the FLASH program by address interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_ProgramByAddr_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t prog_size;
  uint32_t prog_flash_addr;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_PROGRAM)
    {
      flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL | LL_FLASH_FLAG_EOPF);

      prog_flash_addr = hflash->prog_flash_addr[bank_idx];

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_EOPF) != 0U)
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);
        prog_size = hflash->prog_size_byte[bank_idx];

        /* Check if there are still data to program */
        if (hflash->count[bank_idx] > prog_size)
        {
          hflash->count[bank_idx]          -= prog_size;
          hflash->prog_data_addr[bank_idx] += prog_size;
          prog_flash_addr                  += prog_size;

          if (hflash->is_adaptive_prog[bank_idx] != 0U)
          {
            FLASH_UpdateAdaptiveProgMode(hflash, (hal_flash_bank_t)bank_idx);
          }

          hflash->p_prog_unit_func[bank_idx](hflash, (hal_flash_bank_t)bank_idx);
        }
        else
        {
          LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);

          if (IS_FLASH_OTP_ADDRESS(prog_flash_addr))
          {
            LL_FLASH_DisableOTPProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);
          }
          else
          {
            LL_FLASH_DisableProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);
          }

          hflash->count[bank_idx]           = 0;
          hflash->prog_data_addr[bank_idx] += (prog_size - 1U);
          prog_flash_addr                  += (prog_size - 1U);

          hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
          hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_program_cplt_cb(hflash, (prog_flash_addr - hflash->size[bank_idx] + 1U), hflash->size[bank_idx]);
#else
          HAL_FLASH_ProgramCpltCallback(hflash, (prog_flash_addr - hflash->size[bank_idx] + 1U),
                                        hflash->size[bank_idx]);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
      {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
        FLASH_FillErrorCode(hflash, (hal_flash_bank_t)bank_idx, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

        FLASH_HandleErrorIT(hflash, FLASH_GetBank(hflash, prog_flash_addr));
      }

      hflash->prog_flash_addr[bank_idx] = prog_flash_addr;
    }
  }
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
/**
  * @brief  Handle the FLASH erase by address interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_EraseByAddr_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t page_size;
  uint32_t erased_size;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_ADDR_ERASE)
    {
      flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL | LL_FLASH_FLAG_EOPF);

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_EOPF) != 0U)
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);

        /* Update erase count */
        page_size = FLASH_PAGE_SIZE;
        erased_size = page_size - (hflash->erase_page[bank_idx] % page_size);

        /* Check if there are still pages to erase */
        if (hflash->count[bank_idx] > erased_size)
        {
          /* Prepare and call next erase operation */
          hflash->count[bank_idx] -=  erased_size;
          hflash->erase_page[bank_idx] += erased_size;
          LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), bank_reg,
                                  FLASH_GetPageIndexByAddr(hflash->erase_page[bank_idx]));
        }
        else
        {
          LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
          LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), bank_reg);
          erased_size = hflash->count[bank_idx];
          hflash->erase_page[bank_idx] += erased_size - 1U;
          hflash->count[bank_idx] = 0U;
          hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
          hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_erase_by_addr_cplt_cb(hflash,
                                          (hflash->erase_page[bank_idx] - hflash->size[bank_idx] + 1U),
                                          hflash->size[bank_idx]);
#else
          HAL_FLASH_EraseByAddrCpltCallback(hflash,
                                            (hflash->erase_page[bank_idx] - hflash->size[bank_idx] + 1U),
                                            hflash->size[bank_idx]);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
      {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
        FLASH_FillErrorCode(hflash, (hal_flash_bank_t)bank_idx, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

        FLASH_HandleErrorIT(hflash, (hal_flash_bank_t)bank_idx);
      }
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
/**
  * @brief  Handle the FLASH erase page interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_ErasePage_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_PAGE_ERASE)
    {
      flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL | LL_FLASH_FLAG_EOPF);

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_EOPF) != 0U)
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);

        hflash->count[bank_idx]--;

        /* Check if there are still pages to erase */
        if (hflash->count[bank_idx] > 0U)
        {
          /* Prepare and call next erase operation */
          hflash->erase_page[bank_idx]++;
          LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), bank_reg, (hflash->erase_page[bank_idx] % FLASH_PAGE_NB));
        }
        else /* No more pages to erase */
        {
          LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
          LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), bank_reg);

          hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
          hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_erase_page_cplt_cb(hflash,
                                       (hal_flash_bank_t)bank_idx,
                                       ((hflash->erase_page[bank_idx] - hflash->size[bank_idx] + 1UL) % FLASH_PAGE_NB),
                                       hflash->size[bank_idx]);
#else
          HAL_FLASH_ErasePageCpltCallback(hflash,
                                          (hal_flash_bank_t)bank_idx, \
                                          ((hflash->erase_page[bank_idx] - hflash->size[bank_idx] + 1UL) \
                                           % FLASH_PAGE_NB),
                                          hflash->size[bank_idx]);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
      {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
        FLASH_FillErrorCode(hflash, (hal_flash_bank_t)bank_idx, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

        FLASH_HandleErrorIT(hflash, (hal_flash_bank_t)bank_idx);
      }
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)
/**
  * @brief  Handle the FLASH erase bank interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_EraseBank_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_BANK_ERASE)
    {
      flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL | LL_FLASH_FLAG_EOPF);

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_EOPF) != 0U)
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);
        LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
        LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), bank_reg);

        hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
        hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_erase_bank_cplt_cb(hflash, (hal_flash_bank_t)bank_idx);
#else
        HAL_FLASH_EraseBankCpltCallback(hflash, (hal_flash_bank_t)bank_idx);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
      {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
        FLASH_FillErrorCode(hflash, (hal_flash_bank_t)bank_idx, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

        FLASH_HandleErrorIT(hflash, (hal_flash_bank_t)bank_idx);
      }
    }
  }
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)
/**
  * @brief  Handle the FLASH mass erase interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_MassErase_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_MASS_ERASE)
    {
      bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

      flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL | LL_FLASH_FLAG_EOPF);

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_EOPF) != 0U)
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);
        LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
        LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), bank_reg);

        hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
        hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

        if (hflash->ongoing_operation[bank_idx ^ 1U] == HAL_FLASH_NO_OPERATION)
        {
#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_mass_erase_cplt_cb(hflash);
#else
          HAL_FLASH_MassEraseCpltCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
      {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
        FLASH_FillErrorCode(hflash, (hal_flash_bank_t)bank_idx, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

        FLASH_HandleErrorIT(hflash, (hal_flash_bank_t)bank_idx);
      }
    }
  }
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
/**
  * @brief  Handle the FLASH calculate CRC interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_CalculateCRC_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t crc_result;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_CALCULATE_CRC)
    {
      flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL | LL_FLASH_FLAG_CRCENDF);

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_CRCENDF) != 0U)
      {
        crc_result = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash));
        LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), bank_reg);
        LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
        LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), bank_reg);
        LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), bank_reg);

        hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
        hflash->bank_state[bank_idx]        = HAL_FLASH_BANK_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_calculate_crc_cplt_cb(hflash, (hal_flash_bank_t)bank_idx, crc_result);
#else
        HAL_FLASH_CalculateCRCCpltCallback(hflash, (hal_flash_bank_t)bank_idx, crc_result);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }

      if (STM32_READ_BIT(flags, LL_FLASH_FLAG_ERRORS_ALL) != 0U)
      {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
        FLASH_FillErrorCode(hflash, (hal_flash_bank_t)bank_idx, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

        FLASH_HandleErrorIT(hflash, (hal_flash_bank_t)bank_idx);
      }
    }
  }
}
#endif /* USE_HAL_FLASH_CALCULATE_CRC */

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/**
  * @brief  Handle the FLASH ECC correction interrupt request.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  */
void HAL_FLASH_ECC_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t its;
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

    its   = LL_FLASH_IsEnabledIT_SNECCERR(FLASH_GET_INSTANCE(hflash), bank_reg);
    flags = LL_FLASH_IsActiveFlag_SNECCERRF(FLASH_GET_INSTANCE(hflash), bank_reg);

    if ((flags == 1U) && (its == 1U))
    {
#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_ecc_error_cb(hflash, (hal_flash_bank_t)bank_idx);
#else
      HAL_FLASH_ECC_ErrorCallback(hflash, (hal_flash_bank_t)bank_idx);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */

      LL_FLASH_ClearFlag_SNECCERRF(FLASH_GET_INSTANCE(hflash), bank_reg);
    }
  }
}

/**
  * @brief  Handle the FLASH BUS interrupt request.
  * @param  hflash    Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_ERROR Returned when the BUS interrupt has not been handled by this function.
  * @retval HAL_OK    Returned when the BUS interrupt has been handled by this function.
  */
hal_status_t HAL_FLASH_BusFault_IRQHandler(hal_flash_handle_t *hflash)
{
  hal_status_t cb_status = HAL_ERROR;
  uint32_t     bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank_idx);

    if (LL_FLASH_IsActiveFlag_DBECCERRF(FLASH_GET_INSTANCE(hflash), bank_reg) == 1U)
    {
      /* Double ECC flag is only cleared if the callback returns HAL_OK,
      i.e. if the NMI is specifically handled in the callback. */
#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      if (hflash->p_ecc_error_cb(hflash, (hal_flash_bank_t)bank_idx) == HAL_OK)
#else
      if (HAL_FLASH_ECC_ErrorCallback(hflash, (hal_flash_bank_t)bank_idx) == HAL_OK)
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      {
        LL_FLASH_ClearFlag_DBECCERRF(FLASH_GET_INSTANCE(hflash), bank_reg);

        cb_status = HAL_OK;
      }
    }
  }

  return cb_status;
}

#endif /* USE_HAL_FLASH_ECC */
/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to register the FLASH callbacks:

- The weak function HAL_FLASH_ProgramCpltCallback() can be redefined within user application for the program complete
  callback.

- The weak function HAL_FLASH_EraseByAddrCpltCallback() can be redefined within user application for the erase by
  address complete callback.

- The weak function HAL_FLASH_ErasePageCpltCallback() can be redefined within user application for the erase by page
  complete callback.

- The weak function HAL_FLASH_EraseBankCpltCallback() can be redefined within user application for the bank erase
  complete callback.

- The weak function HAL_FLASH_MassEraseCpltCallback() can be redefined within user application for the mass erase
  complete callback.

- The weak function HAL_FLASH_CalculateCRCCpltCallback() can be redefined within user application for the CRC
  calculation complete callback.

- The weak function HAL_FLASH_ErrorCallback() can be redefined within user application for the error callback.

- The weak function HAL_FLASH_ECC_ErrorCallback() can be redefined within user application for the ECC error callback.

- Call the function HAL_FLASH_RegisterProgramCpltCallback() to register the FLASH program complete callback.

- Call the function HAL_FLASH_RegisterEraseByAddrCpltCallback() to register the FLASH erase by address complete
  callback.

- Call the function HAL_FLASH_RegisterErasePageCpltCallback() to register the FLASH erase by page complete callback.

- Call the function HAL_FLASH_RegisterEraseBankCpltCallback() to register the FLASH bank erase complete callback.

- Call the function HAL_FLASH_RegisterMassEraseCpltCallback() to register the FLASH as erase complete callback.

- Call the function HAL_FLASH_RegisterCalculateCRCCpltCallback() to register the FLASH CRC calculation complete
  callback.

- Call the function HAL_FLASH_RegisterErrorCallback() to register the FLASH error callback.

- Call the function HAL_FLASH_RegisterECCErrorCallback() to register the FLASH ECC error callback.
  */
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
/**
  * @brief FLASH program complete callback.
  * @param hflash     Pointer to a \ref hal_flash_handle_t structure.
  * @param flash_addr Programmed address.
  * @param size_byte  Programmed size in byte.
  */
__WEAK void HAL_FLASH_ProgramCpltCallback(hal_flash_handle_t *hflash, uint32_t flash_addr, uint32_t size_byte)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(flash_addr);
  STM32_UNUSED(size_byte);

  /*! <b>WARNING:</b> When the HAL_FLASH_ProgramCpltCallback() callback is needed, it must be implemented within
                      user application for the program complete callback. */
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
/**
  * @brief FLASH erase by address complete callback.
  * @param hflash     Pointer to a \ref hal_flash_handle_t structure.
  * @param flash_addr Erased address.
  * @param size_byte  Erased size in byte.
  */
__WEAK void HAL_FLASH_EraseByAddrCpltCallback(hal_flash_handle_t *hflash,
                                              uint32_t flash_addr,
                                              uint32_t size_byte)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(flash_addr);
  STM32_UNUSED(size_byte);

  /*! <b>WARNING:</b> When the HAL_FLASH_EraseByAddrCpltCallback() callback is needed, it must be implemented within
                      user application for the erase by address complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
/**
  * @brief FLASH erase by page complete callback.
  * @param hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param page     Index of erased page.
  * @param page_nbr Number of erased pages.
  */
__WEAK void HAL_FLASH_ErasePageCpltCallback(hal_flash_handle_t *hflash,
                                            hal_flash_bank_t bank,
                                            uint32_t page,
                                            uint32_t page_nbr)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);
  STM32_UNUSED(page);
  STM32_UNUSED(page_nbr);

  /*! <b>WARNING:</b> When the HAL_FLASH_ErasePageCpltCallback() callback is needed, it must be implemented within
                      user application for the erase page complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)
/**
  * @brief FLASH bank erase complete callback.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  */
__WEAK void HAL_FLASH_EraseBankCpltCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> When the HAL_FLASH_EraseBankCpltCallback() callback is needed, it must be implemented within
                      user application for the erase bank complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)
/**
  * @brief FLASH mass erase complete callback.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  */
__WEAK void HAL_FLASH_MassEraseCpltCallback(hal_flash_handle_t *hflash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

  /*! <b>WARNING:</b> When the HAL_FLASH_MassEraseCpltCallback() callback is needed, it must be implemented within
                      user application for the mass erase complete callback. */
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
/**
  * @brief FLASH calculate CRC complete callback.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param result Result of the CRC calculation.
  */
__WEAK void HAL_FLASH_CalculateCRCCpltCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t result)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);
  STM32_UNUSED(result);

  /*! <b>WARNING:</b> When the HAL_FLASH_ComputeCRCCpltCallback() callback is needed, it must be implemented within
                      user application for the calculate CRC complete callback. */
}
#endif /* USE_HAL_FLASH_CALCULATE_CRC */

/**
  * @brief FLASH error callback.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  */
__WEAK void HAL_FLASH_ErrorCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> When the HAL_FLASH_ErrorCallback() callback is needed, it must be implemented within
                      user application for the error callback. */
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/**
  * @brief  FLASH error code correction callback.
  * @param  hflash    Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_ERROR Returned when this callback did not manage the ECC interrupt.
  * @retval HAL_OK    Returned when this callback managed the ECC interrupt.
  */
__WEAK hal_status_t HAL_FLASH_ECC_ErrorCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ECC_ErrorCallback() could be implemented in the user file */

  return HAL_ERROR;
}
#endif /* USE_HAL_FLASH_ECC */

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
/**
  * @brief  Register the FLASH program complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the program complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterProgramCpltCallback(hal_flash_handle_t *hflash, hal_flash_program_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_program_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
/**
  * @brief  Register the FLASH erase by address complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the erase by address complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterEraseByAddrCpltCallback(hal_flash_handle_t *hflash,
                                                       hal_flash_erase_by_addr_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_erase_by_addr_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
/**
  * @brief  Register the FLASH erase by page complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the erase by page complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterErasePageCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_erase_page_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_erase_page_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)
/**
  * @brief  Register the FLASH bank erase complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the bank erase complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterEraseBankCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_erase_bank_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_erase_bank_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BANK */

#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)
/**
  * @brief  Register the FLASH mass erase complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the mass erase complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterMassEraseCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_mass_erase_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_mass_erase_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_MASS_ERASE */

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
/**
  * @brief  Register the FLASH calculate CRC complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the calculateCRC complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterCalculateCRCCpltCallback(hal_flash_handle_t *hflash,
                                                        hal_flash_calculate_crc_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_calculate_crc_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_CALCULATE_CRC */

/**
  * @brief  Register the FLASH error callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the error callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterErrorCallback(hal_flash_handle_t *hflash, hal_flash_error_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_error_cb = callback;
  return HAL_OK;
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/**
  * @brief  Register the FLASH ECC error callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the error callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterECCErrorCallback(hal_flash_handle_t *hflash, hal_flash_ecc_error_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the FLASH error callback  */
  hflash->p_ecc_error_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ECC */
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to get the FLASH data information and status:

- Call the function HAL_FLASH_GetCurrentOperation() to get the current flash operation.

- Call the function HAL_FLASH_GetCurrentProgrammedAddr() to get the currently being programmed flash address.

- Call the function HAL_FLASH_GetCurrentErasedAddr() to get the currently being erased flash address.

- Call the function HAL_FLASH_GetCurrentErasedPage() to get the currently being erased flash page.

- Call the function HAL_FLASH_GetInfo() to get the FLASH information.

- Call the function HAL_FLASH_GetSizeByte() to get the FLASH total size.

- Call the function HAL_FLASH_GetBankNbr() to get the FLASH number of banks.

- Call the function HAL_FLASH_GetBankSizeByte() to get the FLASH bank size.

- Call the function HAL_FLASH_GetUserFlashSizeByte() to get the FLASH USER area size within a bank.

- Call the function HAL_FLASH_GetUserFlashPageNbr() to get the number of pages in FLASH USER area.


- Call the function HAL_FLASH_GetUserFlashPageSizeByte() to get the FLASH size of a given page in FLASH USER area.


- Call the function HAL_FLASH_GetUserFlashAddrOffset() to get the address offset of a specific page in FLASH USER area.


- Call the function HAL_FLASH_ECC_GetInfo() to get the FLASH ECC information.

- Call the function HAL_FLASH_GetInstance() to get the HAL FLASH instance.

- Call the function HAL_FLASH_GetLLInstance() to get the hardware FLASH instance.

- Call the function HAL_FLASH_GetState() to get the FLASH current state.

- Call the function HAL_FLASH_GetBankState() to get the FLASH current bank state.

- Call the function HAL_FLASH_GetLastErrorCodes() to get the FLASH last errors codes.

- Call the function HAL_FLASH_SetUserData() to set a user data in the FLASH handle.

- Call the function HAL_FLASH_GetUserData() to get a user data from the FLASH handle.
  */

/**
  * @brief  Get the current operation on the given bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_operation_t Operation ongoing.
  */
hal_flash_operation_t HAL_FLASH_GetCurrentOperation(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  return (hflash->ongoing_operation[(uint32_t)bank]);
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
/**
  * @brief  Get the last programming operation information.
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @note   This function must be called during or directly after a ProgramByAddr operation, otherwise the returned
  *         information could not be true anymore.
  * @retval uint32_t FLASH address currently being programmed.
  *                  0xFFFFFFFF if no program by address operation is ongoing on the given bank.
  */
uint32_t HAL_FLASH_GetCurrentProgrammedAddr(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  if ((hflash->ongoing_operation[(uint32_t)bank] != HAL_FLASH_PROGRAM))
  {
    return 0xFFFFFFFFU;
  }

  return hflash->prog_flash_addr[(uint32_t)bank];
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
/**
  * @brief  Get the last address erase operation information.
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @note   This function must be called during or directly after a EraseByAddr operation, otherwise the returned
  *         information could not be true anymore.
  * @retval uint32_t Address of the FLASH page currently being erased.
  *                  0xFFFFFFFF if no erase page by address operation is ongoing on the given bank.
  */
uint32_t HAL_FLASH_GetCurrentErasedAddr(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  if ((hflash->ongoing_operation[(uint32_t)bank] != HAL_FLASH_ADDR_ERASE))
  {
    return 0xFFFFFFFFU;
  }

  return hflash->erase_page[(uint32_t)bank];
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
/**
  * @brief  Get the last page erase operation information.
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @note   This function must be called during or directly after an ErasePage operation, otherwise the returned
  *         information could not be true anymore.
  * @retval uint32_t FLASH page currently being erased.
  *                  0xFFFFFFFF if no erase page operation is ongoing on the given bank.
  */
uint32_t HAL_FLASH_GetCurrentErasedPage(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  if ((hflash->ongoing_operation[(uint32_t)bank] != HAL_FLASH_PAGE_ERASE))
  {
    return 0xFFFFFFFFU;
  }

  return (hflash->erase_page[(uint32_t)bank] % FLASH_PAGE_NB);
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

/**
  * @brief  Get the user FLASH info (size, number and size of banks, number and size of pages).
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_info Pointer to a \ref hal_flash_info_t structure.
  */
void HAL_FLASH_GetInfo(const hal_flash_handle_t *hflash, hal_flash_info_t *p_info)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  p_info->flash_size_byte = FLASH_SIZE;
  p_info->bank_nbr        = FLASH_BANK_NB;

  for (uint32_t bank = 0; bank < FLASH_BANK_NB; bank++)
  {
    bank_reg = FLASH_GetBankReg(hflash, (hal_flash_bank_t)bank);

    p_info->bank[bank].area_nbr                  = 2;
    p_info->bank[bank].bank_size_byte            = FLASH_BANK_SIZE;
    p_info->bank[bank].user_flash.base_addr      = FLASH_BASE + (bank_reg * FLASH_BANK_SIZE);
    p_info->bank[bank].user_flash.area_size_byte = FLASH_BANK_SIZE;
    p_info->bank[bank].user_flash.page_nbr       = (uint16_t)FLASH_PAGE_NB;
  }

  STM32_UNUSED(hflash);
}

/**
  * @brief  Get the total FLASH size.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval The size in bytes of total FLASH.
  */
uint32_t HAL_FLASH_GetSizeByte(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  STM32_UNUSED(hflash);

  return (FLASH_SIZE);
}

/**
  * @brief  Get the number of FLASH banks.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval The number of bank.
  */
uint8_t HAL_FLASH_GetBankNbr(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

  STM32_UNUSED(hflash);

  return (uint8_t)FLASH_BANK_NB;
}

/**
  * @brief  Get the total size in bytes of the given FLASH bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval The total size in bytes of the given bank.
  */
uint32_t HAL_FLASH_GetBankSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return (FLASH_BANK_SIZE);
}

/**
  * @brief  Get the size in bytes of the user flash area of the given bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval The size in bytes of the user flash area of the given bank.
  */
uint32_t HAL_FLASH_GetUserFlashSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return FLASH_BANK_SIZE;
}

/**
  * @brief  Get the number of pages of the user flash area of the given bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval The number of pages of the user flash area of the given bank.
  */
uint16_t HAL_FLASH_GetUserFlashPageNbr(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return (uint16_t)FLASH_PAGE_NB;
}

/**
  * @brief  Get the size in bytes of the given user area page.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page   Selected page
  * @retval The size in bytes of the given user area page.
  */
uint32_t HAL_FLASH_GetUserFlashPageSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t page)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(page < FLASH_PAGE_NB);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);
  STM32_UNUSED(page);

  return FLASH_PAGE_SIZE;
}

/**
  * @brief  Get the offset address of the given user area page.
  * @param  hflash  Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank    This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page    This parameter is the page within the selected bank.
  * @retval Address The offset address of the given user area page.
  */
uint32_t HAL_FLASH_GetUserFlashAddrOffset(const hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t page)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(page < FLASH_PAGE_NB);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);

  return ((uint32_t)bank * FLASH_BANK_SIZE) + (page * FLASH_PAGE_SIZE);
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/**
  * @brief Get the ECC fail information.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param p_info Pointer to a \ref hal_flash_ecc_info_t structure.
  */
void HAL_FLASH_ECC_GetInfo(const hal_flash_handle_t *hflash, hal_flash_bank_t bank, hal_flash_ecc_info_t *p_info)
{
  uint32_t bank_reg;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  bank_reg = FLASH_GetBankReg(hflash, bank);
  STM32_UNUSED(hflash);

  if (LL_FLASH_IsActiveFlag_SNECCERRF(FLASH_GET_INSTANCE(hflash), bank_reg) != 0U)
  {
    p_info->type   = HAL_FLASH_ECC_SINGLE;
    p_info->status = HAL_FLASH_ECC_CORRECTED;
    p_info->addr   = LL_FLASH_GetECCCFailAddress(FLASH_GET_INSTANCE(hflash), bank_reg) ;
  }
  else if (LL_FLASH_IsActiveFlag_DBECCERRF(FLASH_GET_INSTANCE(hflash), bank_reg) != 0U)
  {
    p_info->type   = HAL_FLASH_ECC_DOUBLE;
    p_info->status = HAL_FLASH_ECC_NOT_CORRECTED;
    p_info->addr   = LL_FLASH_GetECCDFailAddress(FLASH_GET_INSTANCE(hflash), bank_reg) ;
  }
  else /* No ECC */
  {
    p_info->type = HAL_FLASH_ECC_NONE;
  }
}
#endif /* USE_HAL_FLASH_ECC */

/**
  * @brief  Get the HAL FLASH instance.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval The HAL FLASH instance.
  */
hal_flash_t HAL_FLASH_GetInstance(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(FLASH_GET_INSTANCE(hflash)));

  return (hflash->instance);
}

/**
  * @brief  Get the hardware FLASH instance.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval The hardware FLASH instance.
  */
FLASH_TypeDef *HAL_FLASH_GetLLInstance(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(FLASH_GET_INSTANCE(hflash)));

  return ((FLASH_TypeDef *)((uint32_t)((hflash)->instance)));
}

/**
  * @brief  Get the FLASH current state.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval hal_flash_state_t The FLASH global state.
  */
hal_flash_state_t HAL_FLASH_GetState(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->global_state);
}

/**
  * @brief  Get the FLASH current bank state.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_bank_state_t The FLASH bank state.
  */
hal_flash_bank_state_t HAL_FLASH_GetBankState(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  return (hflash->bank_state[(uint32_t)bank]);
}

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
/**
  * @brief  Get the FLASH last error codes.
  * @param  hflash      Pointer to a \ref hal_flash_handle_t structure.
  * @retval Error codes The FLASH last error codes.
  */
uint32_t HAL_FLASH_GetLastErrorCodes(const hal_flash_handle_t *hflash)
{
  uint32_t last_error_codes;

  ASSERT_DBG_PARAM(hflash != NULL);

  last_error_codes = hflash->last_error_codes[0];
  last_error_codes |= hflash->last_error_codes[1];

  return last_error_codes;
}
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

#if defined (USE_HAL_FLASH_USER_DATA) && (USE_HAL_FLASH_USER_DATA == 1)
/**
  * @brief  Store User Data pointer within the FLASH handle.
  * @param  hflash      Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_FLASH_SetUserData(hal_flash_handle_t *hflash, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  hflash->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data pointer from the FLASH handle.
  * @param  hflash  Pointer to a \ref hal_flash_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_FLASH_GetUserData(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->p_user_data);
}
#endif /* USE_HAL_FLASH_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FLASH_Private_Functions
  * @{
  */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)) \
    || (defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)) \
    || (defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1))
/**
  * @brief  Check if the FLASH operation for a new operation.
  * @param  hflash    Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank      This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_BUSY  FLASH is busy.
  * @retval HAL_ERROR FLASH is locked or an error is pending.
  * @retval HAL_OK    FLASH is ready.
  */
static hal_status_t FLASH_IsReadyForOperation(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  uint32_t bank_reg     = FLASH_GetBankReg(hflash, bank);
  uint32_t errors_flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL);
  uint32_t status_flags = LL_FLASH_IsActiveFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_STATUS_ALL);

  if ((LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), bank_reg) != 0U) \
      || ((errors_flags & LL_FLASH_FLAG_ERRORS_ALL) != 0U))
  {
    return HAL_ERROR;
  }
  else if (status_flags != 0U)
  {
    return HAL_BUSY;
  }
  else
  {
    return HAL_OK;
  }
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
          || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE || USE_HAL_FLASH_CALCULATE_CRC */

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  hflash       Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank         This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  timeout_ms   Maximum flash operation timeout.
  * @retval HAL_ERROR    There is an operation in progress.
  * @retval HAL_OK       No operation to be waiting.
  */
static hal_status_t FLASH_WaitForEndOfOperation(hal_flash_handle_t *hflash,
                                                hal_flash_bank_t bank,
                                                uint32_t timeout_ms)
{
  uint32_t tickstart;
  uint32_t error_code;
  uint32_t bank_reg = FLASH_GetBankReg(hflash, bank);

  tickstart = HAL_GetTick();
  while (LL_FLASH_IsActiveFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_STATUS_ALL) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      if (LL_FLASH_IsActiveFlag(FLASH_GET_INSTANCE(hflash), bank_reg,  LL_FLASH_FLAG_STATUS_ALL) != 0U)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  error_code = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL);

  if (error_code != 0U)
  {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    FLASH_FillErrorCode(hflash, bank, error_code);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Check error flags */
    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL);

    return HAL_ERROR;
  }

  /* Clear FLASH End of Operation pending bit */
  LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);

  /* If no error flag is set */
  return HAL_OK;
}

/**
  * @brief Get the bank register of the given bank.
  * @param hflash Pointer to a @ref hal_flash_handle_t structure.
  * @param bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval uint32_t return the bank register to be modified.
  */
static uint32_t FLASH_GetBankReg(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  if (LL_FLASH_OB_IsBankSwapped(FLASH_GET_INSTANCE(hflash)) == 0U)
  {
    return (uint32_t)bank;
  }
  else
  {
    return ((uint32_t)bank ^ 1U);
  }
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)

/**
  * @brief  Get the program size of the selected program mode.
  * @param  programming_mode This parameter can be one element of the \ref hal_flash_program_mode_t enumeration.
  * @retval uint32_t The program size in byte.
  */
static uint32_t FLASH_GetProgramSize(hal_flash_program_mode_t programming_mode)
{
  if (programming_mode == HAL_FLASH_PROGRAM_QUADWORD)
  {
    return FLASH_QUADWORD_SIZE_BYTE;
  }
  else if (programming_mode == HAL_FLASH_PROGRAM_DOUBLEWORD)
  {
    return FLASH_DOUBLEWORD_SIZE_BYTE;
  }
  else if (programming_mode == HAL_FLASH_PROGRAM_WORD)
  {
    return FLASH_WORD_SIZE_BYTE;
  }
  else if (programming_mode == HAL_FLASH_PROGRAM_HALFWORD)
  {
    return FLASH_HALFWORD_SIZE_BYTE;
  }
  else
  {
    return 1U;
  }
}

/**
  * @brief  Get the program unit function according to given programming mode.
  * @param  programming_mode This parameter can be one element of the \ref hal_flash_program_mode_t enumeration.
  * @retval Pointer to the program unit function.
  */
static hal_flash_program_unit_func_t FLASH_GetProgramUnitFunction(hal_flash_program_mode_t programming_mode)
{
  hal_flash_program_unit_func_t p_prog_unit_func;
  if (FLASH_GetProgramSize(programming_mode) >= FLASH_WORD_SIZE_BYTE)
  {
    /* Program by successive 32-bit accesses */
    p_prog_unit_func = FLASH_ProgramByWord;
  }
  else if (programming_mode == HAL_FLASH_PROGRAM_HALFWORD)
  {
    /* Program by successive 16-bit accesses */
    p_prog_unit_func = FLASH_ProgramByHalfWord;
  }
  else
  {
    /* Program by successive 8-bit accesses */
    p_prog_unit_func = FLASH_ProgramByByte;
  }

  return p_prog_unit_func;
}

/**
  * @brief Update the adaptive programming mode and compute the number of elementary writes to perform.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  */
static void FLASH_UpdateAdaptiveProgMode(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  hal_flash_program_mode_t      programming_mode;
  hal_flash_program_unit_func_t p_prog_unit_func;
  uint32_t                      count = hflash->count[(uint32_t)bank];

  if (FLASH_IsFlashUSERAddr(hflash->prog_flash_addr[(uint32_t)bank], 1U) != 0U)
  {
    if (count >= FLASH_QUADWORD_SIZE_BYTE)
    {
      programming_mode = HAL_FLASH_PROGRAM_QUADWORD;
      count = FLASH_QUADWORD_SIZE_BYTE;
      p_prog_unit_func = FLASH_ProgramByWord;
    }
    else
    {
      programming_mode = (((count % FLASH_DOUBLEWORD_SIZE_BYTE) == 0U) ? HAL_FLASH_PROGRAM_DOUBLEWORD :
                          (((count % FLASH_WORD_SIZE_BYTE) == 0U) ? HAL_FLASH_PROGRAM_WORD :
                           (((count % FLASH_HALFWORD_SIZE_BYTE) == 0U) ? HAL_FLASH_PROGRAM_HALFWORD :
                            HAL_FLASH_PROGRAM_BYTE)));
      p_prog_unit_func = FLASH_GetProgramUnitFunction(programming_mode);
    }
  }
  else
  {
    if ((count % FLASH_WORD_SIZE_BYTE) == 0U)
    {
      programming_mode = HAL_FLASH_PROGRAM_WORD;
      count = FLASH_WORD_SIZE_BYTE;
      p_prog_unit_func = FLASH_ProgramByWord;
    }
    else
    {
      programming_mode = HAL_FLASH_PROGRAM_HALFWORD;
      count = FLASH_HALFWORD_SIZE_BYTE;
      p_prog_unit_func = FLASH_ProgramByHalfWord;
    }
  }

  hflash->programming_mode[(uint32_t)bank] = programming_mode;
  hflash->prog_size_byte[(uint32_t)bank] = count;
  hflash->p_prog_unit_func[(uint32_t)bank] = p_prog_unit_func;
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive write operations in polling mode.
  * @param  hflash           Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr       FLASH address to program.
  * @param  p_data           Pointer to the data to be programmed.
  * @param  size_byte        Size of the data to be programmed.
  * @param  timeout_ms       Maximum user timeout value for program operation in milliseconds.
  * @retval HAL_ERROR        Error during programming.
  * @retval HAL_TIMEOUT      User timeout.
  * @retval HAL_BUSY         FLASH is busy and cannot start a new program operation.
  * @retval HAL_OK           No operation to be waiting.
  */
static hal_status_t FLASH_Program(hal_flash_handle_t *hflash,
                                  uint32_t flash_addr,
                                  const uint32_t *p_data,
                                  uint32_t size_byte,
                                  uint32_t timeout_ms)
{
  hal_flash_bank_t bank = FLASH_GetBank(hflash, flash_addr);
  uint32_t prog_size;
  uint32_t tickstart = HAL_GetTick();
  uint32_t bank_reg = FLASH_GetBankReg(hflash, bank);

  hal_status_t status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information in the handle */
    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_PROGRAM;
    hflash->prog_data_addr[(uint32_t)bank]    = (uint32_t)p_data;
    hflash->prog_flash_addr[(uint32_t)bank]   = flash_addr;
    hflash->count[(uint32_t)bank]             = size_byte;
    hflash->size[(uint32_t)bank]              = size_byte;

    while ((hflash->count[(uint32_t)bank] > 0U) && (status == HAL_OK))
    {
      if (hflash->is_adaptive_prog[(uint32_t)bank] != 0U)
      {
        FLASH_UpdateAdaptiveProgMode(hflash, bank);
      }

      hflash->p_prog_unit_func[(uint32_t)bank](hflash, bank);

      status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_PROGRAM_OPERATION_QUADWORD_TIMEOUT);

      /* Update handle programming elements and reset programming flags if no error occurred */
      if (status == HAL_OK)
      {
        prog_size = hflash->prog_size_byte[(uint32_t)bank];

        if (hflash->count[(uint32_t)bank] > prog_size)
        {
          hflash->count[(uint32_t)bank]           -= prog_size;
          hflash->prog_data_addr[(uint32_t)bank]  += prog_size;
          hflash->prog_flash_addr[(uint32_t)bank] += prog_size;
        }
        else
        {
          hflash->count[(uint32_t)bank] = 0U;
          hflash->prog_data_addr[(uint32_t)bank]  += (prog_size - 1U);
          hflash->prog_flash_addr[(uint32_t)bank] += (prog_size - 1U);
        }

        if (((HAL_GetTick() - tickstart) > timeout_ms) && (status == HAL_OK))
        {
          status = HAL_TIMEOUT;
        }
      }
    }

    if (hflash->prog_flash_addr[(uint32_t)bank] >= OTP_AREA_BASE)
    {
      LL_FLASH_DisableOTPProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);
    }
    else
    {
      LL_FLASH_DisableProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);
    }

    if (status == HAL_OK)
    {
      hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_NO_OPERATION;
    }

    hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive write operations.
  * @param  hflash          Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr      FLASH address to program.
  * @param  p_data          Pointer to the data to be programmed.
  * @param  size_byte       Size of the data to be programmed.
  * @retval HAL_ERROR       Error before starting program operation.
  * @retval HAL_BUSY        FLASH is busy and cannot start a new program operation.
  * @retval HAL_OK          Program operation started.
  */
static hal_status_t FLASH_Program_IT(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte)
{
  hal_flash_bank_t bank     = FLASH_GetBank(hflash, flash_addr);
  hal_status_t     status   = FLASH_IsReadyForOperation(hflash, bank);
  uint32_t         bank_reg = FLASH_GetBankReg(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information structure */
    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_PROGRAM;
    hflash->prog_data_addr[(uint32_t)bank]    = (uint32_t)p_data;
    hflash->prog_flash_addr[(uint32_t)bank]   = flash_addr;
    hflash->count[(uint32_t)bank]             = size_byte;
    hflash->size[(uint32_t)bank]              = size_byte;

    if (hflash->is_adaptive_prog[(uint32_t)bank] != 0U)
    {
      FLASH_UpdateAdaptiveProgMode(hflash, bank);
    }

    LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);

    hflash->p_prog_unit_func[(uint32_t)bank](hflash, bank);
  }

  return status;
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive word write operations.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  */
static void FLASH_ProgramByWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  uint32_t bank_reg        = FLASH_GetBankReg(hflash, bank);
  uint32_t increment_index = hflash->prog_size_byte[(uint32_t)bank] / 4U;
  uint32_t *dest_addr      = (uint32_t *)(hflash->prog_flash_addr[(uint32_t)bank]);
  uint32_t *src_addr       = (uint32_t *)(hflash->prog_data_addr[(uint32_t)bank]);
  uint32_t primask_bit;

  LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit when less than a quad-word is written */
  if (hflash->programming_mode[(uint32_t)bank] != HAL_FLASH_PROGRAM_QUADWORD)
  {
    LL_FLASH_EnableForceWrite(FLASH_GET_INSTANCE(hflash), bank_reg);
  }
  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive word write operations.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  */
static void FLASH_ProgramByHalfWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  uint32_t primask_bit;
  uint32_t bank_reg        = FLASH_GetBankReg(hflash, bank);
  uint32_t increment_index = hflash->prog_size_byte[(uint32_t)bank];
  uint16_t *dest_addr      = (uint16_t *)(hflash->prog_flash_addr[(uint32_t)bank]);
  uint16_t *src_addr       = (uint16_t *)(hflash->prog_data_addr[(uint32_t)bank]);

  if (IS_FLASH_OTP_ADDRESS((uint32_t)dest_addr))
  {
    LL_FLASH_EnableOTPProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);
  }
  else
  {
    LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);
  }

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit when less than a quad-word is written */
  if ((FLASH_IsFlashUSERAddr(hflash->prog_flash_addr[(uint32_t)bank], 1U) != 0U))
  {
    LL_FLASH_EnableForceWrite(FLASH_GET_INSTANCE(hflash), bank_reg);
  }
  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive byte write operations.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  */
static void FLASH_ProgramByByte(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  uint32_t primask_bit;
  uint32_t bank_reg        = FLASH_GetBankReg(hflash, bank);
  uint32_t increment_index = hflash->prog_size_byte[(uint32_t)bank];
  uint8_t *dest_addr       = (uint8_t *)(hflash->prog_flash_addr[(uint32_t)bank]);
  uint8_t *src_addr        = (uint8_t *)(hflash->prog_data_addr[(uint32_t)bank]);

  LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash), bank_reg);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit when less than a quad-word is written */
  LL_FLASH_EnableForceWrite(FLASH_GET_INSTANCE(hflash), bank_reg);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)
/**
  * @brief Get the page index associated to the given flash address.
  * @param flash_addr Flash Address.
  * @retval uint32_t The index of the page containing the given address.
  */
static uint32_t FLASH_GetPageIndexByAddr(uint32_t flash_addr)
{
  return (((flash_addr - FLASH_BASE) / FLASH_PAGE_SIZE) % FLASH_PAGE_NB);
}

/**
  * @brief  Erase pages of FLASH memory by address in polling mode.
  * @param  hflash         Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr     FLASH address to erase.
  * @param  size_byte      Size of the data to be erased.
  * @param  page_size      Page size of the erased area.
  * @param  timeout_ms     Maximum user timeout value for erase operation in milliseconds.
  * @retval HAL_ERROR      Error during erasing.
  * @retval HAL_TIMEOUT    User timeout.
  * @retval HAL_OK         No operation to be waiting.
  */
static hal_status_t FLASH_EraseAddr(hal_flash_handle_t *hflash,
                                    uint32_t flash_addr,
                                    uint32_t size_byte,
                                    uint32_t page_size,
                                    uint32_t timeout_ms)
{
  hal_status_t     status;
  hal_flash_bank_t bank     = FLASH_GetBank(hflash, flash_addr);
  uint32_t         bank_reg = FLASH_GetBankReg(hflash, bank);
  uint32_t         tickstart;
  uint32_t         count;

  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_ADDR_ERASE;
    hflash->erase_page[(uint32_t)bank]        = flash_addr;
    count                               = size_byte;
    hflash->size[(uint32_t)bank]              = size_byte;

    while ((count > 0U) && (status == HAL_OK))
    {
      tickstart = HAL_GetTick();

      LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), bank_reg,
                              FLASH_GetPageIndexByAddr(hflash->erase_page[(uint32_t)bank]));

      status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

      if (status == HAL_OK)
      {
        if (count > page_size)
        {
          count -= page_size;
          hflash->erase_page[(uint32_t)bank] += page_size;
        }
        else
        {
          hflash->erase_page[(uint32_t)bank] += count - 1U;
          count = 0U;
        }

        if (((HAL_GetTick() - tickstart) > timeout_ms))
        {
          if ((count > 0U) && (status == HAL_OK))
          {
            status = HAL_TIMEOUT;
          }
        }
      }
    }

    LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), bank_reg);

    hflash->count[(uint32_t)bank] = count;

    if (status == HAL_OK)
    {
      hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_NO_OPERATION;
    }

    hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Erase pages of FLASH memory by address in interrupt mode.
  * @param  hflash         Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr     FLASH address to erase.
  * @param  size_byte      Size of the data to be erased.
  * @retval HAL_ERROR      Error during erasing.
  * @retval HAL_OK         No operation to be waiting.
  */
static hal_status_t FLASH_EraseAddr_IT(hal_flash_handle_t *hflash,
                                       uint32_t flash_addr,
                                       uint32_t size_byte)
{
  hal_status_t     status;
  hal_flash_bank_t bank     = FLASH_GetBank(hflash, flash_addr);
  uint32_t         bank_reg = FLASH_GetBankReg(hflash, bank);

  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    hflash->ongoing_operation[(uint32_t)bank]  = HAL_FLASH_ADDR_ERASE;
    hflash->erase_page[(uint32_t)bank]         = flash_addr;
    hflash->count[(uint32_t)bank]              = size_byte;
    hflash->size[(uint32_t)bank]               = size_byte;

    LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
    LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), bank_reg,
                            FLASH_GetPageIndexByAddr(hflash->erase_page[(uint32_t)bank]));
  }

  return status;
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)
/**
  * @brief  Erase pages of FLASH memory by address in polling mode.
  * @param  hflash       Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank         Bank to erase. This parameter can be one element of the \ref hal_flash_bank_t enumeration.
  * @param  start_page   Index of the first page to erase.
  * @param  page_nbr     The number of pages to erase.
  * @param  timeout_ms   Maximum user timeout value for erase operation in milliseconds.
  * @retval HAL_ERROR    Error during erasing.
  * @retval HAL_TIMEOUT  User timeout.
  * @retval HAL_OK       No operation to be waiting.
  */
static hal_status_t FLASH_ErasePage(hal_flash_handle_t *hflash,
                                    hal_flash_bank_t bank,
                                    uint32_t start_page,
                                    uint32_t page_nbr,
                                    uint32_t timeout_ms)
{
  hal_status_t status;
  uint32_t     tickstart;
  uint32_t     bank_reg = FLASH_GetBankReg(hflash, bank);

  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information structure */
    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_PAGE_ERASE;
    hflash->erase_page[(uint32_t)bank]        = start_page;
    hflash->count[(uint32_t)bank]             = page_nbr;
    hflash->size[(uint32_t)bank]              = page_nbr;

    while ((hflash->count[(uint32_t)bank] > 0U) && (status == HAL_OK))
    {
      tickstart = HAL_GetTick();
      LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), bank_reg,
                              (hflash->erase_page[(uint32_t)bank] % FLASH_PAGE_NB));

      status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

      if (status == HAL_OK)
      {
        hflash->count[(uint32_t)bank]--;
        if (hflash->count[(uint32_t)bank] > 0U)
        {
          hflash->erase_page[(uint32_t)bank]++;

          if (timeout_ms != HAL_MAX_DELAY)
          {
            if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
            {
              status = HAL_TIMEOUT;
            }
          }
        }
      }
    }

    LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), bank_reg);

    if (status == HAL_OK)
    {
      hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_NO_OPERATION;
    }

    hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Erase pages of FLASH memory by address in interrupt mode.
  * @param  hflash       Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank         Bank to erase. This parameter can be one element of the \ref hal_flash_bank_t enumeration.
  * @param  start_page   Index of the first page to erase.
  * @param  page_nbr     Number of pages to erase.
  * @retval HAL_ERROR    Error during erasing.
  * @retval HAL_BUSY     FLASH is busy and cannot start a new erase operation.
  * @retval HAL_OK       No operation to be waiting.
  */
static hal_status_t FLASH_ErasePage_IT(hal_flash_handle_t *hflash,
                                       hal_flash_bank_t bank,
                                       uint32_t start_page,
                                       uint32_t page_nbr)
{
  hal_status_t status;
  uint32_t     bank_reg = FLASH_GetBankReg(hflash, bank);

  status = FLASH_IsReadyForOperation(hflash, bank);

  if (status == HAL_OK)
  {
    HAL_CHECK_UPDATE_STATE(hflash, bank_state[(uint32_t)bank], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[(uint32_t)bank] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information structure */
    hflash->ongoing_operation[(uint32_t)bank] = HAL_FLASH_PAGE_ERASE;
    hflash->erase_page[(uint32_t)bank]        = start_page;
    hflash->count[(uint32_t)bank]             = page_nbr;
    hflash->size[(uint32_t)bank]              = page_nbr;

    LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), bank_reg);
    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);
    LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), bank_reg,
                            (hflash->erase_page[(uint32_t)bank] % FLASH_PAGE_NB));
  }

  return status;
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1))
/**
  * @brief Get the bank which contains the given flash address.
  * @param hflash Pointer to a @ref hal_flash_handle_t structure.
  * @param flash_addr Flash Address
  * @retval hal_flash_bank_t the bank containing the given address.
  *                    This parameter is one element of @ref hal_flash_bank_t enumeration.
  */
static hal_flash_bank_t FLASH_GetBank(const hal_flash_handle_t *hflash, uint32_t flash_addr)
{
  hal_flash_bank_t low_addr_range_bank, high_addr_range_bank;

  if (LL_FLASH_OB_IsBankSwapped(FLASH_GET_INSTANCE(hflash)) == 0U)
  {
    low_addr_range_bank = HAL_FLASH_BANK_1;
    high_addr_range_bank = HAL_FLASH_BANK_2;
  }
  else
  {
    low_addr_range_bank = HAL_FLASH_BANK_2;
    high_addr_range_bank = HAL_FLASH_BANK_1;
  }

  if ((flash_addr >= OTP_AREA_BASE) && (flash_addr < (OTP_AREA_BASE + OTP_SIZE)))
  {
    return HAL_FLASH_BANK_1;
  }
  else
  {
    return (((flash_addr - FLASH_BASE) < FLASH_BANK_SIZE) ? low_addr_range_bank : high_addr_range_bank);
  }
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_CALCULATE_CRC */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1))
/**
  * @brief  Check if a FLASH address is part of the user FLASH area.
  * @param  flash_addr The FLASH address to check.
  * @param  check_program_alignment The flag indicating if the address must be aligned for programming.
  * @retval The status of the FLASH address test (1: address is in user FLASH, 0: otherwise)
  */
static uint32_t FLASH_IsFlashUSERAddr(uint32_t flash_addr, uint8_t check_program_alignment)
{
  uint32_t user_flash = ((flash_addr >= FLASH_BASE) && (flash_addr < (FLASH_BASE + FLASH_SIZE))) ? 1U : 0U;

  return (((user_flash == 1U) && ((check_program_alignment == 0U) ? (1U == 1U) : (((flash_addr) % 16U) == 0U))) \
          ? 1U : 0U);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
/**
  * @brief  Update last error element of FLASH handle.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  flags  Bitfield containing the error flags.
  */
static void FLASH_FillErrorCode(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t flags)
{
  uint32_t error_codes = 0U;

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)
  if ((flags & LL_FLASH_FLAG_STRBERR) != 0U)
  {
    error_codes |= (HAL_FLASH_BANK_1_ERROR_STRB << ((uint32_t)bank * 16U));
  }

  if ((flags & LL_FLASH_FLAG_INCERR) != 0U)
  {
    error_codes |= (HAL_FLASH_BANK_1_ERROR_INC << ((uint32_t)bank * 16U));
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)) \
    || (defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1))
  if ((flags & LL_FLASH_FLAG_WRPERR) != 0U)
  {
    error_codes |= (HAL_FLASH_BANK_1_ERROR_WRP << ((uint32_t)bank * 16U));
  }

  if ((flags & LL_FLASH_FLAG_PGSERR) != 0U)
  {
    error_codes |= (HAL_FLASH_BANK_1_ERROR_PGS << ((uint32_t)bank * 16U));
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
          || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

  if ((flags & LL_FLASH_FLAG_RDSERR) != 0U)
  {
    error_codes |= (HAL_FLASH_BANK_1_ERROR_RDS << ((uint32_t)bank * 16U));
  }

#if defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1)
  if ((flags & LL_FLASH_FLAG_CRCRDERR) != 0U)
  {
    error_codes |= (HAL_FLASH_BANK_1_ERROR_CRC << ((uint32_t)bank * 16U));
  }
#endif /* USE_HAL_FLASH_CALCULATE_CRC */

  hflash->last_error_codes[(uint32_t)bank] |= error_codes;
}
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1)) \
    || (defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1)) \
    || (defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1)) \
    || (defined (USE_HAL_FLASH_CALCULATE_CRC) && (USE_HAL_FLASH_CALCULATE_CRC == 1))
/**
  * @brief Handle the FLASH error interrupt.
  * @param hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param bank   Bank where the error occurred.
  *               This parameter can be one element of the \ref hal_flash_bank_t enumeration.
  */
static void FLASH_HandleErrorIT(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  uint32_t bank_reg = FLASH_GetBankReg(hflash, bank);

  LL_FLASH_DisableAllOperation(FLASH_GET_INSTANCE(hflash), bank_reg);

  LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_IT_ALL);

  LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), bank_reg, LL_FLASH_FLAG_ERRORS_ALL);

  hflash->bank_state[(uint32_t)bank] = HAL_FLASH_BANK_STATE_IDLE;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
  hflash->p_error_cb(hflash, bank);
#else
  HAL_FLASH_ErrorCallback(hflash, bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
          || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */
/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_FLASH_MODULE */
#endif /* FLASH */

/**
  * @}
  */
