/**
  ******************************************************************************
  * @file    stm32g5xx_hal_ucpd.c
  * @brief   UCPD HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the UCPD peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State and Errors functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */
#if defined (UCPD1)
#if defined (USE_HAL_UCPD_MODULE) && (USE_HAL_UCPD_MODULE == 1)

/** @addtogroup UCPD
  * @{
  */
/** @defgroup UCPD_Introduction UCPD Introduction
  * @{
  *
  * ## Overview
  *
  * The UCPD (USB Type-C Power Delivery) HAL driver provides a high-level interface
  * to configure and control the UCPD peripheral for USB Type-C and USB Power Delivery
  * communication on STM32 microcontrollers.
  *
  * ## Key Features
  *
  * - **USB Type-C Detection**: Detects CC line voltage states for role determination
  *   (source/sink) and attachment detection
  * - **USB Power Delivery Protocol**: Implements the physical layer for USB PD message
  *   transmission and reception using BMC (Biphase Mark Coding) encoding
  * - **DMA-Based Transfers**: Supports DMA mode for efficient non-blocking message
  *   transmission and reception with minimal CPU overhead
  * - **Configurable Clocking**: Provides flexible clock prescalers and dividers for
  *   ucpd_clk, half-bit clock, transition window, and inter-frame gap timing
  * - **Hardware CRC**: Automatic CRC calculation and verification for USB PD messages
  * - **GoodCRC Handling**: Hardware-assisted fast GoodCRC message transmission within
  *   the USB PD timing requirements
  * - **Ordered Set Detection**: Configurable detection of SOP, SOP', SOP'', Hard Reset,
  *   Cable Reset, and other USB PD ordered sets
  * - **Callbacks and Interrupts**: Event-driven architecture with callbacks for Tx/Rx
  *   completion, errors, Type-C events, and Fast Role Swap (FRS) detection
  * - **Low-Power Support**: Wake-up mode for low-power operation with CC event detection
  *
  * ## Typical Use Cases
  *
  * - USB Type-C source and sink devices (power adapters, battery chargers, laptops)
  * - USB Power Delivery controllers for negotiating power contracts
  * - USB Type-C Dual-Role Port (DRP) implementations
  * - USB Type-C alternate mode support (DisplayPort, Thunderbolt, etc.)
  * - Cable plug (VCONN-powered) USB PD communication
  *
  * @}
  */

/** @defgroup UCPD_How_To_Use UCPD How To Use
  * @{

# How to use the UCPD HAL module driver

## Usage

1. Declare a hal_ucpd_handle_t handle structure and initialize the UCPDx driver with a UCPD hardware instance
   by calling HAL_UCPD_Init().

   The UCPDx clock is enabled inside the HAL_UCPD_Init() if USE_HAL_UCPD_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

2. Initialize the UCPD low-level resources by implementing the UCPD_MspInit API:
   - Enable the UCPDx interface clock (if not enabled in HAL_UCPD_Init() when UCPD_CLK_ENABLE_MODEL
     is set to CLK_ENABLE_NO)
   - UCPD pins configuration:
     - Enable the clock for the UCPD GPIOs
       - Configure UCPD pins as alternate function open-drain
     - NVIC configuration if you need to use interrupt processing
       - Configure the UCPDx interrupt priority
       - Enable the NVIC UCPD IRQ channel
     - DMA Configuration
       - Declare a hal_dma_handle_t handle structure for the transmit or receive channel
       - Enable the DMAx interface clock
       - Configure the DMA handle parameters
       - Configure the DMA Tx or Rx channel
       - Associate the initialized DMA handle to the hucpd DMA Tx or Rx handle
       - Configure the priority and enable the NVIC for the transfer complete interrupt
         on the DMA Tx or Rx channel

3. Configure the ucpd_clk prescaler, half-bit clock, transition window clock, and inter-frame gap timer division ratios,
   as well as accepted ordered set types and CC line enabling by calling HAL_UCPD_SetConfig().

4. Configure and/or enable advanced static configuration features. For instance, HAL_UCPD_SetRxPreFilterSampling(),
   HAL_UCPD_EnableRxPreFilter(), HAL_UCPD_EnableWakeupMode(), etc.
   All these advanced configurations are optional (not mandatory), and can only be set before starting the driver with
   HAL_UCPD_Start().

5. End the static configuration and start the driver with HAL_UCPD_Start().

6. Apply any dynamic control and configuration function. For instance, HAL_UCPD_SetRole(), HAL_UCPD_SetRxMode(),
   HAL_UCPD_SetTxOrderedSet(), HAL_UCPD_ApplyTrimmingRp(), HAL_UCPD_ApplyTrimmingRd(), etc.

7. For UCPD IO operations, one operation mode is available within this driver:
    - DMA mode IO operation
      - Transmit an amount of data in non-blocking mode (DMA) using HAL_UCPD_Transmit_DMA().
        - At transmission end of transfer, HAL_UCPD_TxCpltCallback() is executed and users can add their own code
          by customization of function pointer HAL_UCPD_TxCpltCallback().

      - Receive an amount of data in non-blocking mode (DMA) using HAL_UCPD_Receive_DMA()
        - HAL_UCPD_Receive_DMA() also prepares Tx DMA to enable quick GoodCRC message transmission.
        - At reception completion, HAL_UCPD_RxCpltCallback() is executed and users can add their own code by
          customization of function pointer HAL_UCPD_RxCpltCallback(). At this point user must prepare the GoodCRC
          data to send by calling HAL_UCPD_SetGoodCRCData().
        - After HAL_UCPD_RxCpltCallback() returns, the ISR transmits the GoodCRC message in the
          interrupt context.
        - At GoodCRC transmission end of transfer, HAL_UCPD_TxGoodCRCCpltCallback() is executed and users can add their
          own code by customization of function pointer HAL_UCPD_TxGoodCRCCpltCallback().

      - In case of transfer Error, HAL_UCPD_ErrorCallback() function is executed and users can add their own code by
        customization of function pointer HAL_UCPD_ErrorCallback().

      - Abort an UCPD process communication in Interrupt mode using HAL_UCPD_Abort_IT()
        - At end of abort process, HAL_UCPD_AbortCpltCallback() is executed and users can add their own code by
          customization of function pointer HAL_UCPD_AbortCpltCallback().
        - During a Tx abort, the peripheral continues sending remaining bytes but forces an incorrect CRC
          so the receiver discards the message.

## Callback registration

  - When the compilation flag USE_HAL_UCPD_REGISTER_CALLBACKS is set to 1, it allows the user to configure dynamically
    the driver callbacks instead of weak functions.
    Functions allow registering callbacks:
      - HAL_UCPD_RegisterTxCpltCallback() for transmission end of transfer callback registration.
      - HAL_UCPD_RegisterRxCpltCallback() for reception end of transfer callback registration.
      - HAL_UCPD_RegisterErrorCallback() for error callback registration.
      - See the complete list in the callback registration function group.

## UCPD bus Acquire/Release

  - When the compilation flag USE_HAL_MUTEX is set to 1, it allows the user to acquire/reserve the UCPD bus
    for a transaction.
    The HAL Acquire/Release are based on the HAL OS abstraction layer:
      - HAL_UCPD_AcquireBus() acquires the bus or waits until it is available.
      - HAL_UCPD_ReleaseBus() releases the bus.

  - When the compilation flag USE_HAL_MUTEX is set to 0 or not defined, HAL_UCPD_AcquireBus() / HAL_UCPD_ReleaseBus()
    are not available.
  */

/**
  * @}
  */

/** @defgroup UCPD_Configuration_Table UCPD Configuration Table
  * @{

## UCPD driver configuration

Config defines                  | Where            | Default value     | Note
------------------------------- | ---------------- | ----------------- | --------------------------------------------
USE_HAL_UCPD_MODULE             | hal_conf.h       |        1U         | Enable HAL UCPD module
USE_HAL_UCPD_POWER_DELIVERY     | hal_conf.h       |        1U         | Enable the PD related functions in the driver
USE_HAL_UCPD_REGISTER_CALLBACKS | hal_conf.h       |        0U         | Enable the register callbacks assert
USE_HAL_UCPD_CLK_ENABLE_MODEL   | hal_conf.h       | HAL_CLK_ENABLE_NO | Enable peripheral clock in the HAL_UCPD_Init
USE_HAL_UCPD_USER_DATA          | hal_conf.h       |        0U         | Add a user data inside HAL UCPD handle
USE_HAL_UCPD_GET_LAST_ERRORS    | hal_conf.h       |        0U         | Add error member inside HAL UCPD handle
USE_HAL_CHECK_PARAM             | hal_conf.h       |        0U         | Enable checking of vital parameters at runtime
USE_HAL_MUTEX                   | hal_conf.h       |        0U         | Enable the use of semaphore in the HAL driver
USE_ASSERT_DBG_PARAM            | PreProcessor env |        NA         | Enable the params assert
USE_ASSERT_DBG_STATE            | PreProcessor env |        NA         | Enable the state assert
  */

/**
  * @}
  */

/* Private types -----------------------------------------------------------*/
/** @defgroup UCPD_Private_Types UCPD Private Types
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup UCPD_Private_Constants UCPD Private Constants
  * @{
  */

/**
  * @brief Receiver ordered set mask.
  * @details Applied to the UCPD_RX_ORDSET register to extract the received ordered set field.
  */
#define UCPD_RXORDSET_MASK ((uint32_t)0x1FF00000U)

/**
  * @brief Min size in bytes of a message transmission.
  * @details Minimum is 2 bytes: the message header only, with no data objects.
  */
#define UCPD_MIN_MESSAGE_SIZE (2U)

/**
  * @brief Size in bytes of a GoodCRC message.
  * @details A GoodCRC message carries no data objects, so its size equals @ref UCPD_MIN_MESSAGE_SIZE.
  */
#define UCPD_GOODCRC_SIZE (UCPD_MIN_MESSAGE_SIZE)

/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup UCPD_Private_Macros UCPD Private Macros
  * @{
  */

/** @brief Check the current peripheral handle state and move it to new state, and save the previous state
  *        in an atomic way.
  * @param handle Specifies the Peripheral Handle.
  * @param state_field Specifies the state field within the Handle.
  * @param ucpd_conditional_state State to be checked to authorize moving to the new state.
  * @param ucpd_new_state New state to be set.
  * @param old_state_field Specifies the previous state field within the Handle.
  * @note  This macro can be used for the following purpose:
  *        - When the define USE_HAL_CHECK_PROCESS_STATE is set to "1", this macro allows checking the current
  *          handle state versus a conditional state and if true set to the desired new state, and save the previous
  *          state.
  *          The check and update of the state and previous state is done using exclusive Load/store instruction making
  *          the operation atomic.
  *        - When the define USE_HAL_CHECK_PROCESS_STATE is not set to "1", this macro simply assigns the new
  *          handle state field to the new desired state and sets the previous state without any check.
  * @retval HAL_BUSY if the define USE_HAL_CHECK_PROCESS_STATE is set to "1" and the current state doesn't match
  *         conditional_state.
  */
#if defined (USE_HAL_CHECK_PROCESS_STATE) && (USE_HAL_CHECK_PROCESS_STATE == 1)
#define UCPD_CHECK_UPDATE_STATE(handle, state_field, ucpd_conditional_state, ucpd_new_state, old_state_field)        \
  do                                                                                                                 \
  {                                                                                                                  \
    uint32_t ucpd_current_state;                                                                                     \
    do                                                                                                               \
    {                                                                                                                \
      ucpd_current_state = __LDREXW((volatile uint32_t *)((uint32_t)&(handle)->state_field));                       \
      if ((ucpd_current_state & (uint32_t)(ucpd_conditional_state)) == 0U)                                           \
      {                                                                                                              \
        __CLREX();                                                                                                   \
        return HAL_BUSY;                                                                                             \
      }                                                                                                              \
    } while (__STREXW((uint32_t)(ucpd_new_state), (volatile uint32_t *)((uint32_t)&((handle)->state_field))) != 0U); \
    (handle)->old_state_field = (hal_ucpd_state_t)ucpd_current_state;                                                \
    __DMB();                                                                                                         \
  } while (0U)
#else
#define UCPD_CHECK_UPDATE_STATE(handle, state_field, ucpd_conditional_state, ucpd_new_state, old_state_field)        \
  do                                                                                                                 \
  {                                                                                                                  \
    (handle)->old_state_field = (handle)->state_field;                                                               \
    (handle)->state_field     = (ucpd_new_state);                                                                    \
  } while (0U)
#endif /* USE_HAL_CHECK_PROCESS_STATE == 1 */

/**
  * @brief  Check UCPD clock prescaler value.
  * @param  psc Prescaler for producing ucpd_clk from ucpd_ker_ck
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_PSC(psc) (((psc) == HAL_UCPD_PSC_DIV1)     \
                          || ((psc) == HAL_UCPD_PSC_DIV2)  \
                          || ((psc) == HAL_UCPD_PSC_DIV4)  \
                          || ((psc) == HAL_UCPD_PSC_DIV8)  \
                          || ((psc) == HAL_UCPD_PSC_DIV16))

/**
  * @brief  Check transition window clock divider value.
  * @param  transwin_div Divider for producing transition window clock from half-bit clock (hbit_clk)
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_TRANSWIN_DIV(transwin_div) (((transwin_div) == HAL_UCPD_TRANSWIN_DIV2)      \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV3)   \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV4)   \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV5)   \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV6)   \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV7)   \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV8)   \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV9)   \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV10)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV11)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV12)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV13)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV14)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV15)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV16)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV17)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV18)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV19)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV20)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV21)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV22)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV23)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV24)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV25)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV26)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV27)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV28)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV29)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV30)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV31)  \
                                            || ((transwin_div) == HAL_UCPD_TRANSWIN_DIV32))

/**
  * @brief  Check inter-frame gap timer clock divider value.
  * @param  ifrgap_div Divider for producing inter-frame gap timer clock from ucpd_clk
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_IFRGAP_DIV(ifrgap_div) (((ifrgap_div) == HAL_UCPD_IFRGAP_DIV2)      \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV3)   \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV4)   \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV5)   \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV6)   \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV7)   \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV8)   \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV9)   \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV10)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV11)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV12)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV13)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV14)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV15)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV16)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV17)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV18)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV19)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV20)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV21)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV22)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV23)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV24)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV25)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV26)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV27)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV28)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV29)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV30)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV31)  \
                                        || ((ifrgap_div) == HAL_UCPD_IFRGAP_DIV32))

/**
  * @brief  Check Tx mode value.
  * @param  txmode Tx mode
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_TX_MODE(txmode) (((txmode) == HAL_UCPD_TX_MODE_NORMAL)         \
                                 || ((txmode) == HAL_UCPD_TX_MODE_CABLE_RESET) \
                                 || ((txmode) == HAL_UCPD_TX_MODE_BIST))

/**
  * @brief  Check Rx mode value.
  * @param  rxmode Rx mode
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_RX_MODE(rxmode) (((rxmode) == HAL_UCPD_RX_MODE_NORMAL)   \
                                 || ((rxmode) == HAL_UCPD_RX_MODE_BIST))

/**
  * @brief  Check role value.
  * @param  role Analog PHY operating role
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_ROLE(role) (((role) == HAL_UCPD_ROLE_SOURCE)   \
                            || ((role) == HAL_UCPD_ROLE_SINK))

/**
  * @brief  Check Rp resistor value.
  * @param  rp Rp resistor values
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_RP_VALUE(rp) (((rp) == HAL_UCPD_RP_DEFAULT)  \
                              || ((rp) == HAL_UCPD_RP_1_5A)  \
                              || ((rp) == HAL_UCPD_RP_3_0A)  \
                              || ((rp) == HAL_UCPD_RP_NONE))

/**
  * @brief  Check Rx ordered set value.
  * @param  rxordset Rx ordered set
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_RXORDSET_TYPE(rxordset) (((rxordset) & (UCPD_RXORDSET_MASK)) == (rxordset))

/**
  * @brief  Check Tx ordered set value.
  * @param  txordset Tx ordered set
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_TXORDSET_TYPE(txordset) (((txordset) == HAL_UCPD_TX_ORDERED_SET_SOP)           \
                                         || ((txordset) == HAL_UCPD_TX_ORDERED_SET_SOP1)       \
                                         || ((txordset) == HAL_UCPD_TX_ORDERED_SET_SOP2)       \
                                         || ((txordset) == HAL_UCPD_TX_ORDERED_SET_SOP1_DEBUG) \
                                         || ((txordset) == HAL_UCPD_TX_ORDERED_SET_SOP2_DEBUG) \
                                         || ((txordset) == HAL_UCPD_TX_ORDERED_SET_HARD_RST)   \
                                         || ((txordset) == HAL_UCPD_TX_ORDERED_SET_CABLE_RST))

/**
  * @brief  Check CC line enable value.
  * @param  cc_en CC line enable value
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_CC_LINE_EN(cc_en) (((cc_en) == HAL_UCPD_CC_ENABLE_NONE)       \
                                   || ((cc_en) == HAL_UCPD_CC_ENABLE_CC1)     \
                                   || ((cc_en) == HAL_UCPD_CC_ENABLE_CC2)     \
                                   || ((cc_en) == HAL_UCPD_CC_ENABLE_CC1CC2))

/**
  * @brief  Check CC line.
  * @param  cc_line CC line
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_CC_LINE(cc_line) (((cc_line) == HAL_UCPD_LINE_CC1)     \
                                  || ((cc_line) == HAL_UCPD_LINE_CC2))

/**
  * @brief  Check BMC decoder Rx pre-filter sampling method.
  * @param  rx_prefilt_samples BMC decoder Rx pre-filter sampling method
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_RX_PREFILT_SAMPLE(rx_prefilt_samples) (((rx_prefilt_samples) == HAL_UCPD_RX_PREFILTER_3SAMPLES)     \
                                                       || ((rx_prefilt_samples) == HAL_UCPD_RX_PREFILTER_2SAMPLES))

/**
  * @brief  Check Rp value for trimming.
  * @param  trim_rp_value Rp value to apply trimming to.
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_TRIM_RP(trim_rp_value) (((trim_rp_value) == HAL_UCPD_TRIM_RP_1_5A)     \
                                        || ((trim_rp_value) == HAL_UCPD_TRIM_RP_3_0A))


/**
  * @brief  Check if the transfer size is valid.
  * @param  size_byte Number of bytes for the transfer
  * @retval true (valid) or false (invalid)
  */
#define IS_UCPD_TRANSFER_SIZE(size_byte)        (((size_byte) < 0xFFFFU) && (size_byte) >= UCPD_MIN_MESSAGE_SIZE)

/**
  * @brief Retrieve UCPD instance from handle.
  */
#define UCPD_GET_INSTANCE(handle) \
  ((UCPD_TypeDef *)((uint32_t)((handle)->instance)))

/* Bits definition for UCPD Trimming register */
#define UCPD_VALUE_TRIM_CC1_RP_3A0_POS  (4U)                                      /*!< Trim data position for Rp 3.0A (CC1)          */
#define UCPD_VALUE_TRIM_CC1_RP_3A0_MSK  (0xFUL << UCPD_VALUE_TRIM_CC1_RP_3A0_POS) /*!< Trim data mask for Rp 3.0A (CC1) - 0x000000F0 */
#define UCPD_VALUE_TRIM_CC1_RP_3A0      UCPD_VALUE_TRIM_CC1_RP_3A0_MSK            /*!< Trim data value for Rp 3.0A (CC1)             */
#define UCPD_VALUE_TRIM_CC1_RP_1A5_POS  (0U)                                      /*!< Trim data position for Rp 1.5A (CC1)          */
#define UCPD_VALUE_TRIM_CC1_RP_1A5_MSK  (0xFUL << UCPD_VALUE_TRIM_CC1_RP_1A5_POS) /*!< Trim data mask for Rp 1.5A (CC1) - 0x0000000F */
#define UCPD_VALUE_TRIM_CC1_RP_1A5      UCPD_VALUE_TRIM_CC1_RP_1A5_MSK            /*!< Trim data value for Rp 1.5A (CC1)             */
#define UCPD_VALUE_TRIM_CC1_RD_POS      (0U)                                      /*!< Trim data position for Rd (CC1)               */
#define UCPD_VALUE_TRIM_CC1_RD_MSK      (0xFUL << UCPD_VALUE_TRIM_CC1_RD_POS)     /*!< Trim data mask for Rd (CC1)      - 0x0000000F */
#define UCPD_VALUE_TRIM_CC1_RD          UCPD_VALUE_TRIM_CC1_RD_MSK                /*!< Trim data value for Rd (CC1)                  */
#define UCPD_VALUE_TRIM_CC2_RP_3A0_POS  (12U)                                     /*!< Trim data position for Rp 3.0A (CC2)          */
#define UCPD_VALUE_TRIM_CC2_RP_3A0_MSK  (0xFUL << UCPD_VALUE_TRIM_CC2_RP_3A0_POS) /*!< Trim data mask for Rp 3.0A (CC2) - 0x0000F000 */
#define UCPD_VALUE_TRIM_CC2_RP_3A0      UCPD_VALUE_TRIM_CC2_RP_3A0_MSK            /*!< Trim data value for Rp 3.0A (CC2)             */
#define UCPD_VALUE_TRIM_CC2_RP_1A5_POS  (0U)                                      /*!< Trim data position for Rp 1.5A (CC2)          */
#define UCPD_VALUE_TRIM_CC2_RP_1A5_MSK  (0xFUL << UCPD_VALUE_TRIM_CC2_RP_1A5_POS) /*!< Trim data mask for Rp 1.5A (CC2) - 0x0000000F */
#define UCPD_VALUE_TRIM_CC2_RP_1A5      UCPD_VALUE_TRIM_CC2_RP_1A5_MSK            /*!< Trim data value for Rp 1.5A (CC2)             */
#define UCPD_VALUE_TRIM_CC2_RD_POS      (8U)                                      /*!< Trim data position for Rd (CC2)               */
#define UCPD_VALUE_TRIM_CC2_RD_MSK      (0xFUL << UCPD_VALUE_TRIM_CC2_RD_POS)     /*!< Trim data mask for Rd (CC2)      - 0x00000F00 */
#define UCPD_VALUE_TRIM_CC2_RD          UCPD_VALUE_TRIM_CC2_RD_MSK                /*!< Trim data value for Rd (CC2)                  */


/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup UCPD_Private_Functions UCPD Private Functions
  * @{
  */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
static void UCPD_EndTxTransfer(hal_ucpd_handle_t *hucpd);
static void UCPD_EndRxTransfer(hal_ucpd_handle_t *hucpd);

static void UCPD_DMATransmitCplt(hal_dma_handle_t *hdma);
static void UCPD_DMAReceiveCplt(hal_dma_handle_t *hdma);
static void UCPD_DMAError(hal_dma_handle_t *hdma);

static void UCPD_DMATxAbortCallback(hal_dma_handle_t *hdma);
static void UCPD_DMARxAbortCallback(hal_dma_handle_t *hdma);

static void UCPD_DMAEndTxMsgAbortCallback(hal_dma_handle_t *hdma);
static void UCPD_DMAEndTxMsgDiscardCallback(hal_dma_handle_t *hdma);
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup UCPD_Private_Variables UCPD Private Variables
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup UCPD_Exported_Functions
  * @{
  */

/** @addtogroup UCPD_Exported_Functions_Group1
  * @{

A set of functions allowing to initialize and deinitialize the UCPDx peripheral:
  - HAL_UCPD_Init() to initialize the selected UCPDx handle and associate an instance.
  - HAL_UCPD_DeInit() to restore the default configuration of the selected UCPDx peripheral.
  */

/**
  * @brief  Initialize the UCPD according to the associated handle.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  instance UCPD instance.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         UCPD instance is already initialized and cannot be modified
  *                           or semaphore creation failed (USE_HAL_MUTEX is set to 1).
  * @retval HAL_OK            UCPD instance has been correctly initialized.
  */
hal_status_t HAL_UCPD_Init(hal_ucpd_handle_t *hucpd, hal_ucpd_t instance)
{
  ASSERT_DBG_PARAM(hucpd != NULL);
  ASSERT_DBG_PARAM(IS_UCPD_ALL_INSTANCE((UCPD_TypeDef *)((uint32_t)instance)));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hucpd->instance = instance;

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->hdma_tx = NULL;
  hucpd->hdma_rx = NULL;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

#if defined (USE_HAL_UCPD_CLK_ENABLE_MODEL) && (USE_HAL_UCPD_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  if (hucpd->instance == HAL_UCPD1)
  {
    HAL_RCC_UCPD1_EnableClock();
  }

#endif /* USE_HAL_UCPD_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
  /* Init the UCPD Callback settings */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->p_tx_cplt_cb          = HAL_UCPD_TxCpltCallback;        /* Tx message sent callback               */
  hucpd->p_tx_goodcrc_cplt_cb  = HAL_UCPD_TxGoodCRCCpltCallback; /* Tx GoodCRC message sent callback       */
  hucpd->p_tx_discard_cb       = HAL_UCPD_TxDiscardCallback;     /* Tx message discarded callback          */
  hucpd->p_tx_abort_cb         = HAL_UCPD_TxAbortCallback;       /* Tx message aborted callback            */
  hucpd->p_rx_cplt_cb          = HAL_UCPD_RxCpltCallback;        /* Rx complete callback                   */
  hucpd->p_rx_ord_set_cb       = HAL_UCPD_RxOrdDetCallback;      /* Rx ordered set detected callback       */
  hucpd->p_hrst_sent_cb        = HAL_UCPD_HRstSentCallback;      /* Hard reset sent callback               */
  hucpd->p_hrst_rx_cb          = HAL_UCPD_HRstRxCallback;        /* Hard reset received callback           */
  hucpd->p_hrst_discard_cb     = HAL_UCPD_HRstDiscardCallback;   /* Hard reset discarded callback          */
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hucpd->p_type_c_event_ccx_cb = HAL_UCPD_TypeCEventCCxCallback; /* Type-C event on CCx callback           */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->p_frs_evt_cb          = HAL_UCPD_FRSEvtCallback;        /* Fast Role Swap event detected callback */
  hucpd->p_abort_cplt_cb       = HAL_UCPD_AbortCpltCallback;     /* Abort complete callback                */
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hucpd->p_error_cb            = HAL_UCPD_ErrorCallback;         /* Error callback                         */
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */

#if defined (USE_HAL_UCPD_USER_DATA) && (USE_HAL_UCPD_USER_DATA == 1)
  hucpd->p_user_data = NULL;
#endif /* USE_HAL_UCPD_USER_DATA */

#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
  hucpd->last_error_codes = HAL_UCPD_ERROR_NONE;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  if (HAL_OS_SemaphoreCreate(&hucpd->semaphore) != HAL_OS_OK)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->previous_state = HAL_UCPD_STATE_RESET;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hucpd->global_state = HAL_UCPD_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  Deinitialize the UCPD peripheral.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            UCPD instance has been correctly initialized.
  */
void HAL_UCPD_DeInit(hal_ucpd_handle_t *hucpd)
{
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  UCPD_TypeDef *p_ucpdx;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

  /* Check the UCPD handle allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Check if any transfer ongoing */
  if (((uint32_t)hucpd->global_state & ((uint32_t)HAL_UCPD_STATE_TX | (uint32_t)HAL_UCPD_STATE_RX)) != 0U)
  {
    /* Disable all UCPD interrupts */
    uint32_t interrupts = LL_UCPD_IMR_TYPECEVT2 | LL_UCPD_IMR_TYPECEVT1 | LL_UCPD_IMR_RXMSGEND
                          | LL_UCPD_IMR_RXOVR | LL_UCPD_IMR_RXHRSTDET | LL_UCPD_IMR_RXORDDET
                          | LL_UCPD_IMR_TXUND | LL_UCPD_IMR_HRSTSENT | LL_UCPD_IMR_HRSTDISC
                          | LL_UCPD_IMR_TXMSGABT | LL_UCPD_IMR_TXMSGSENT | LL_UCPD_IMR_TXMSGDISC;
    interrupts |= LL_UCPD_IMR_FRSEVT;
    LL_UCPD_DisableIT(p_ucpdx, interrupts);

    /* Stop current process/operation(s) */
    if (LL_UCPD_IsEnabledTxDMA(p_ucpdx) == 1U)
    {
      if (hucpd->hdma_tx != NULL)
      {
        if (hucpd->hdma_tx->global_state == HAL_DMA_STATE_ACTIVE)
        {
          hucpd->hdma_tx->p_xfer_abort_cb = UCPD_DMATxAbortCallback;

          /* Abort DMA Tx */
          (void)HAL_DMA_Abort_IT(hucpd->hdma_tx);
        }
      }
    }

    if (LL_UCPD_IsEnabledRxDMA(p_ucpdx) == 1U)
    {
      if (hucpd->hdma_rx != NULL)
      {
        if (hucpd->hdma_rx->global_state == HAL_DMA_STATE_ACTIVE)
        {
          hucpd->hdma_rx->p_xfer_abort_cb = UCPD_DMARxAbortCallback;

          /* Abort DMA Rx */
          (void)HAL_DMA_Abort_IT(hucpd->hdma_rx);
        }
      }
    }
  }
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

  LL_UCPD_Disable(UCPD_GET_INSTANCE(hucpd));

#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  (void)HAL_OS_SemaphoreDelete(&hucpd->semaphore);
#endif /* USE_HAL_MUTEX */

  hucpd->global_state = HAL_UCPD_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup UCPD_Exported_Functions_Group2
  * @{

A set of functions allowing to configure the UCPDx peripheral:

- Global configuration
  - HAL_UCPD_SetConfig()
  - HAL_UCPD_GetConfig()

- Rx ordered sets
  - HAL_UCPD_SetRxOrderedSet()
  - HAL_UCPD_GetRxOrderedSet()

- Rx/Tx DMA management
  - HAL_UCPD_SetRxDMA()
  - HAL_UCPD_SetTxDMA()

- Wake-up from Stop mode
  - HAL_UCPD_EnableWakeupMode()
  - HAL_UCPD_DisableWakeupMode()
  - HAL_UCPD_IsEnabledWakeupMode()

- Software trimming
  - HAL_UCPD_ApplyTrimmingRp()
  - HAL_UCPD_ApplyTrimmingRd()

- Start/Stop
  - HAL_UCPD_Start()
  - HAL_UCPD_Stop()

  */

/**
  * @brief  Configure the UCPD according to the user parameters.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_config Pointer to a @ref hal_ucpd_config_t structure that contains the UCPD configuration.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_OK            UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetConfig(hal_ucpd_handle_t *hucpd, const hal_ucpd_config_t *p_config)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the configuration pointer */
  if ((hucpd == NULL) || (p_config == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_UCPD_PSC(p_config->clk_psc));
  ASSERT_DBG_PARAM(p_config->hbitclk_div <= HAL_UCPD_HBITCLK_DIV64);
  ASSERT_DBG_PARAM(IS_UCPD_TRANSWIN_DIV(p_config->transwin_div));
  ASSERT_DBG_PARAM(IS_UCPD_IFRGAP_DIV(p_config->ifrgap_div));
  ASSERT_DBG_PARAM(IS_UCPD_RXORDSET_TYPE(p_config->rx_ordered_set));

  /* Disable the UCPD peripheral */
  LL_UCPD_Disable(p_ucpdx);

  LL_UCPD_Config(p_ucpdx,
                 (uint32_t)p_config->clk_psc,
                 (uint32_t)p_config->hbitclk_div,
                 (uint32_t)p_config->transwin_div,
                 (uint32_t)p_config->ifrgap_div,
                 (uint32_t)p_config->rx_ordered_set);

  /* Go to idle state */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->previous_state = hucpd->global_state;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hucpd->global_state = HAL_UCPD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the UCPD configuration.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_config Pointer to a @ref hal_ucpd_config_t structure that contains the UCPD configuration.
  */
void HAL_UCPD_GetConfig(const hal_ucpd_handle_t *hucpd, hal_ucpd_config_t *p_config)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Set the clock prescaler */
  p_config->clk_psc = (hal_ucpd_clk_prescaler_t)LL_UCPD_GetPSCClk(p_ucpdx);

  /* Set the half-bit clock divider */
  p_config->hbitclk_div = (hal_ucpd_half_bit_clk_divider_t)LL_UCPD_GetHbitClockDiv(p_ucpdx);

  /* Set the transition window clock divider */
  p_config->transwin_div = (hal_ucpd_transition_window_divider_t)LL_UCPD_GetTransWin(p_ucpdx);

  /* Set the inter-frame gap timer clock divider */
  p_config->ifrgap_div = (hal_ucpd_inter_frame_gap_divider_t)LL_UCPD_GetIfrGap(p_ucpdx);

  /* Set the receiver accepted ordered set types */
  p_config->rx_ordered_set = (uint32_t)LL_UCPD_GetRxOrderSet(p_ucpdx);
}

/**
  * @brief  Set the type(s) of ordered set(s) that the receiver must detect.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  rx_ordered_set Type(s) of ordered set(s) that the receiver must detect.
  *         This parameter can be any combination of the following values:
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_NONE
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP1
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP2
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_HARD_RST
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_CABLE_RST
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP1_DEBUG
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP2_DEBUG
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP_EXT1
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP_EXT2
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetRxOrderedSet(const hal_ucpd_handle_t *hucpd, uint32_t rx_ordered_set)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_UCPD_RXORDSET_TYPE(rx_ordered_set));

  /* Set the receiver accepted ordered set types */
  LL_UCPD_SetRxOrderSet(p_ucpdx, rx_ordered_set);

  if (rx_ordered_set != HAL_UCPD_RX_ORDERED_SET_NONE)
  {
    /* Enable the Rx ordered set interrupt */
    LL_UCPD_EnableIT_RxOrderSet(p_ucpdx);
  }
  else
  {
    /* Disable the Rx ordered set interrupt */
    LL_UCPD_DisableIT_RxOrderSet(p_ucpdx);
  }

  return HAL_OK;
}

/**
  * @brief  Get the types of ordered sets that the receiver must detect.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval Enabled ordered sets. This can be any combination of the following values:
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP1
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP2
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_HARD_RST
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_CABLE_RST
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP1_DEBUG
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP2_DEBUG
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP_EXT1
  *         @arg @ref HAL_UCPD_RX_ORDERED_SET_SOP_EXT2
  */
uint32_t HAL_UCPD_GetRxOrderedSet(hal_ucpd_handle_t *hucpd)
{
  uint32_t rx_ordered_set;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the receiver accepted ordered set types */
  rx_ordered_set = (uint32_t)LL_UCPD_GetRxOrderSet(UCPD_GET_INSTANCE(hucpd));

  return rx_ordered_set;
}

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Set DMA channel for reception.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure which contains the UCPD instance.
  * @param  hdma_rx Pointer to a hal_dma_handle_t structure which contains the DMA instance
  * @retval HAL_OK            DMA channel has been correctly set.
  * @retval HAL_INVALID_PARAM hucpd or hdma_rx is NULL.
  */
hal_status_t HAL_UCPD_SetRxDMA(hal_ucpd_handle_t *hucpd, hal_dma_handle_t *hdma_rx)
{
  ASSERT_DBG_PARAM(hucpd != NULL);
  ASSERT_DBG_PARAM(hdma_rx != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameter */
  if ((hucpd == NULL) || (hdma_rx == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE);

  hucpd->hdma_rx = hdma_rx;
  hdma_rx->p_parent = hucpd;

  return HAL_OK;
}

/**
  * @brief  Set DMA channel for transmission.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure which contains the UCPD instance.
  * @param  hdma_tx Pointer to a hal_dma_handle_t structure which contains the DMA instance
  * @retval HAL_OK            DMA channel has been correctly set.
  * @retval HAL_INVALID_PARAM hucpd or hdma_tx is NULL.
  */
hal_status_t HAL_UCPD_SetTxDMA(hal_ucpd_handle_t *hucpd, hal_dma_handle_t *hdma_tx)
{
  ASSERT_DBG_PARAM(hucpd != NULL);
  ASSERT_DBG_PARAM(hdma_tx != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameter */
  if ((hucpd == NULL) || (hdma_tx == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE);

  hucpd->hdma_tx = hdma_tx;
  hdma_tx->p_parent = hucpd;

  return HAL_OK;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Enable the UCPD receiver hardware analog filter.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableRxAnalogFilter(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Enable the Rx analog filter */
  LL_UCPD_EnableRxAnalogFilter(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Disable the UCPD receiver hardware analog filter.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableRxAnalogFilter(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Disable the Rx analog filter */
  LL_UCPD_DisableRxAnalogFilter(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Return the UCPD receiver hardware analog filter.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_rx_analog_filter_status_t Receiver hardware analog filter status.
  */
hal_ucpd_rx_analog_filter_status_t HAL_UCPD_IsEnabledRxAnalogFilter(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_rx_analog_filter_status_t status;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the Rx analog filter status */
  status = (hal_ucpd_rx_analog_filter_status_t)LL_UCPD_IsEnabledRxAnalogFilter(UCPD_GET_INSTANCE(hucpd));

  return status;
}

/**
  * @brief  Enable UCPD wake-up from Stop mode.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableWakeupMode(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Enable wake-up from Stop mode */
  LL_UCPD_EnableWakeUp(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Disable UCPD wake-up from Stop mode.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableWakeupMode(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Disable wake-up from Stop mode */
  LL_UCPD_DisableWakeUp(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Return UCPD wake-up from Stop mode status.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_wakeup_mode_status_t Wake-up from stop mode status.
  */
hal_ucpd_wakeup_mode_status_t HAL_UCPD_IsEnabledWakeupMode(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_wakeup_mode_status_t status;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get wake-up mode status */
  status = (hal_ucpd_wakeup_mode_status_t)LL_UCPD_IsEnabledWakeUp(UCPD_GET_INSTANCE(hucpd));

  return status;
}

/**
  * @brief  Enable UCPD ClkReq clock request forcing.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableForceClock(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Enable ClkReq clock request forcing */
  LL_UCPD_EnableForceClock(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Disable UCPD ClkReq clock request forcing.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableForceClock(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Disable ClkReq clock request forcing */
  LL_UCPD_DisableForceClock(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Return UCPD ClkReq clock request forcing status.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_force_clk_status_t ClkReq clock request forcing status.
  */
hal_ucpd_force_clk_status_t HAL_UCPD_IsEnabledForceClock(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_force_clk_status_t status;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get ClkReq clock request forcing status */
  status = (hal_ucpd_force_clk_status_t)LL_UCPD_IsEnabledForceClock(UCPD_GET_INSTANCE(hucpd));

  return status;
}

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Set the BMC decoder Rx pre-filter sampling method.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  rx_prefilter_samples BMC decoder Rx pre-filter sampling method.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetRxPreFilterSampling(hal_ucpd_handle_t *hucpd,
                                             hal_ucpd_rx_prefilter_samples_t rx_prefilter_samples)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_UCPD_RX_PREFILT_SAMPLE(rx_prefilter_samples));

  /* Apply Rx pre-filter sampling method */
  LL_UCPD_SetRxPreFilterSampling(UCPD_GET_INSTANCE(hucpd), (uint32_t)rx_prefilter_samples);

  return HAL_OK;
}

/**
  * @brief  Get the BMC decoder Rx pre-filter sampling method.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_rx_prefilter_samples_t BMC decoder Rx pre-filter sampling method.
  */
hal_ucpd_rx_prefilter_samples_t HAL_UCPD_GetRxPreFilterSampling(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_rx_prefilter_samples_t rx_prefilter_samples;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get Rx pre-filter sampling method */
  rx_prefilter_samples = (hal_ucpd_rx_prefilter_samples_t)LL_UCPD_GetRxPreFilterSampling(UCPD_GET_INSTANCE(hucpd));

  return rx_prefilter_samples;
}

/**
  * @brief  Enable UCPD Rx pre-filter.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableRxPreFilter(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Enable Rx pre-filter */
  LL_UCPD_EnableRxPreFilter(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Disable UCPD Rx pre-filter.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @warning This function modifies a static configuration, and therefore must not be called after HAL_UCPD_Start().
  * @retval HAL_OK    UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableRxPreFilter(hal_ucpd_handle_t *hucpd)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Disable Rx pre-filter */
  LL_UCPD_DisableRxPreFilter(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Return UCPD Rx pre-filter status.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_rx_prefilter_status_t Rx pre-filter status.
  */
hal_ucpd_rx_prefilter_status_t HAL_UCPD_IsEnabledRxPreFilter(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_rx_prefilter_status_t status;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get Rx pre-filter status */
  status = (hal_ucpd_rx_prefilter_status_t)LL_UCPD_IsEnabledRxPreFilter(UCPD_GET_INSTANCE(hucpd));

  return status;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Apply the Rp current sources trimming on both CC lines.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  trim_rp_value Rp value to apply trimming to.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_ApplyTrimmingRp(hal_ucpd_handle_t *hucpd, hal_ucpd_trim_rp_value_t trim_rp_value)
{
  UCPD_TypeDef *p_ucpdx;
  uint32_t trim_val_cc1;
  uint32_t trim_val_cc2;

  /* UCPD software trimming data pointers - Non-volatile memory location */
  static const __IO uint32_t *pUCPD_TRIM_3A0_CC1 = (uint32_t *)(0x4002242CUL); /* Trimming data for Rp 3.0A CC1 */
  static const __IO uint32_t *pUCPD_TRIM_3A0_CC2 = (uint32_t *)(0x4002242CUL); /* Trimming data for Rp 3.0A CC2 */
  static const __IO uint16_t *pUCPD_TRIM_1A5_CC1 = (uint16_t *)(0x08FFF844UL); /* Trimming data for Rp 1.5A CC1 */
  static const __IO uint16_t *pUCPD_TRIM_1A5_CC2 = (uint16_t *)(0x08FFF846UL); /* Trimming data for Rp 1.5A CC2 */

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_UCPD_TRIM_RP(trim_rp_value));

  /* Retrieve trimming value to apply depending on Rp value */
  if (trim_rp_value == HAL_UCPD_TRIM_RP_3_0A)
  {
    trim_val_cc1 = (((*pUCPD_TRIM_3A0_CC1) & UCPD_VALUE_TRIM_CC1_RP_3A0_MSK) >> UCPD_VALUE_TRIM_CC1_RP_3A0_POS);
    trim_val_cc2 = (((*pUCPD_TRIM_3A0_CC2) & UCPD_VALUE_TRIM_CC2_RP_3A0_MSK) >> UCPD_VALUE_TRIM_CC2_RP_3A0_POS);
    /* Apply Rp3A0 trimming on both CC lines */
    LL_UCPD_SetTrimCC1_Rp3A0(p_ucpdx, trim_val_cc1);
    LL_UCPD_SetTrimCC2_Rp3A0(p_ucpdx, trim_val_cc2);
  }
  else
  {
    trim_val_cc1 = (((*pUCPD_TRIM_1A5_CC1) & UCPD_VALUE_TRIM_CC1_RP_1A5_MSK) >> UCPD_VALUE_TRIM_CC1_RP_1A5_POS);
    trim_val_cc2 = (((*pUCPD_TRIM_1A5_CC2) & UCPD_VALUE_TRIM_CC2_RP_1A5_MSK) >> UCPD_VALUE_TRIM_CC2_RP_1A5_POS);

    /* Apply Rp1A5 trimming on both CC lines */
    LL_UCPD_SetTrimCC1_Rp1A5(p_ucpdx, trim_val_cc1);
    LL_UCPD_SetTrimCC2_Rp1A5(p_ucpdx, trim_val_cc2);
  }

  return HAL_OK;
}

/**
  * @brief  Apply the Rd resistors trimming on both CC lines.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_ApplyTrimmingRd(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;
  uint32_t trim_val_cc1;
  uint32_t trim_val_cc2;

  /* UCPD software trimming data pointers - Non-volatile memory location */
  static const __IO uint32_t *pUCPD_TRIM_Rd_CC1 = (uint32_t *)(0x4002242CUL); /* Trimming data for Rd CC1      */
  static const __IO uint32_t *pUCPD_TRIM_Rd_CC2 = (uint32_t *)(0x4002242CUL); /* Trimming data for Rd CC2      */

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Retrieve trimming value to apply */
  trim_val_cc1 = (((*pUCPD_TRIM_Rd_CC1) & UCPD_VALUE_TRIM_CC1_RD_MSK) >> UCPD_VALUE_TRIM_CC1_RD_POS);
  trim_val_cc2 = (((*pUCPD_TRIM_Rd_CC2) & UCPD_VALUE_TRIM_CC2_RD_MSK) >> UCPD_VALUE_TRIM_CC2_RD_POS);

  /* Apply Rd trimming on both CC lines */
  LL_UCPD_SetTrimCC1_Rd(p_ucpdx, trim_val_cc1);
  LL_UCPD_SetTrimCC2_Rd(p_ucpdx, trim_val_cc2);

  return HAL_OK;
}

/**
  * @brief  Start the UCPD peripheral.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_Start(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_IDLE);

  /* Switch state */
  UCPD_CHECK_UPDATE_STATE(hucpd, global_state, (uint32_t)HAL_UCPD_STATE_IDLE, HAL_UCPD_STATE_ACTIVE, previous_state);

  /* Enable the UCPD peripheral - Static configuration can no longer be modified */
  LL_UCPD_Enable(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Stop the UCPD peripheral.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_Stop(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Disable the UCPD peripheral - Static configuration can now be modified. Control configuration resets */
  LL_UCPD_Disable(p_ucpdx);

  /* Go to idle state */
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->previous_state = hucpd->global_state;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hucpd->global_state = HAL_UCPD_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup UCPD_Exported_Functions_Group3
  * @{

A set of functions allowing to control the UCPDx peripheral:

- Rx PHY enabling
  - HAL_UCPD_EnableRx()
  - HAL_UCPD_DisableRx()
  - HAL_UCPD_IsEnabledRx()

- Type-C detector
  - HAL_UCPD_EnableTypeCDetectorCCx()
  - HAL_UCPD_DisableTypeCDetectorCCx()
  - HAL_UCPD_IsEnabledTypeCDetectorCCx()

- Vconn discharge
  - HAL_UCPD_EnableVconnDischarge()
  - HAL_UCPD_DisableVconnDischarge()
  - HAL_UCPD_IsEnabledVconnDischarge()

- Tx ordered set
  - HAL_UCPD_SetTxOrderedSet()
  - HAL_UCPD_GetTxOrderedSet()

- Rx/Tx modes
  - HAL_UCPD_SetTxMode()
  - HAL_UCPD_GetTxMode()
  - HAL_UCPD_SetRxMode()
  - HAL_UCPD_GetRxMode()

- PHY operating role
  - HAL_UCPD_SetRole()
  - HAL_UCPD_GetRole()

- Pull-ups (Rp) resistors
  - HAL_UCPD_SetRp()
  - HAL_UCPD_GetRp()

- CC lines
  - HAL_UCPD_SetCCLines()
  - HAL_UCPD_GetCCLines()
  - HAL_UCPD_SetActiveCC()
  - HAL_UCPD_GetActiveCC()

- Fast Role Swap
  - HAL_UCPD_EnableFRS_Rx()
  - HAL_UCPD_DisableFRS_Rx()
  - HAL_UCPD_IsEnabledFRS_Rx()
  - HAL_UCPD_SendFRS()

- Cable reset
  - HAL_UCPD_SendCableReset()

- Hard reset
  - HAL_UCPD_SendHardReset()
  - HAL_UCPD_EnableHardReset_Rx()
  - HAL_UCPD_DisableHardReset_Rx()
  - HAL_UCPD_IsEnabledHardReset_Rx()

  */

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Enable the UCPD PHY receiver.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableRx(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Enable the PHY receiver */
  LL_UCPD_EnableRx(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Disable the UCPD PHY receiver.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableRx(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Disable the PHY receiver */
  LL_UCPD_DisableRx(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Return the UCPD PHY receiver status.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_rx_phy_status_t UCPD PHY receiver status.
  */
hal_ucpd_rx_phy_status_t HAL_UCPD_IsEnabledRx(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_rx_phy_status_t status;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Return the PHY receiver status */
  status = (hal_ucpd_rx_phy_status_t)LL_UCPD_IsEnabledRx(UCPD_GET_INSTANCE(hucpd));

  return status;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Enable the UCPD Type-C detector of the given CC line.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  cc_line CC line on which to enable the Type-C detector.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableTypeCDetectorCCx(const hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_CC_LINE(cc_line));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Enable Type-C detector and interrupt depending on selected CCx pin */
  if (cc_line == HAL_UCPD_LINE_CC1)
  {
    LL_UCPD_EnableTypeCDetectionCC1(p_ucpdx);
    LL_UCPD_EnableIT_TypeCEventCC1(p_ucpdx);
  }
  else
  {
    LL_UCPD_EnableTypeCDetectionCC2(p_ucpdx);
    LL_UCPD_EnableIT_TypeCEventCC2(p_ucpdx);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the UCPD Type-C detector of the given CC line.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  cc_line CC line on which to disable the Type-C detector.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableTypeCDetectorCCx(const hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_CC_LINE(cc_line));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Disable Type-C detector and interrupt depending on selected CCx pin */
  if (cc_line == HAL_UCPD_LINE_CC1)
  {
    LL_UCPD_DisableTypeCDetectionCC1(p_ucpdx);
    LL_UCPD_DisableIT_TypeCEventCC1(p_ucpdx);
  }
  else
  {
    LL_UCPD_DisableTypeCDetectionCC2(p_ucpdx);
    LL_UCPD_DisableIT_TypeCEventCC2(p_ucpdx);
  }

  return HAL_OK;
}

/**
  * @brief  Return the UCPD Type-C detector status of the given CC line.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  cc_line CC line on which to check the status of the Type-C detector.
  * @return @ref hal_ucpd_type_c_detector_status_t UCPD Type-C detector status.
  */
hal_ucpd_type_c_detector_status_t HAL_UCPD_IsEnabledTypeCDetectorCCx(const hal_ucpd_handle_t *hucpd,
                                                                     hal_ucpd_cc_line_t cc_line)
{
  UCPD_TypeDef *p_ucpdx;
  hal_ucpd_type_c_detector_status_t status;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_CC_LINE(cc_line));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Return Type-C detector status depending on selected CCx pin */
  if (cc_line == HAL_UCPD_LINE_CC1)
  {
    status = (hal_ucpd_type_c_detector_status_t)LL_UCPD_IsEnabledTypeCDetectionCC1(p_ucpdx);
  }
  else
  {
    status = (hal_ucpd_type_c_detector_status_t)LL_UCPD_IsEnabledTypeCDetectionCC2(p_ucpdx);
  }

  return status;
}

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Enable the UCPD Vconn discharge.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableVconnDischarge(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Enable Vconn discharge */
  LL_UCPD_EnableVconnDischarge(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Disable the UCPD Vconn discharge.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableVconnDischarge(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Disable Vconn discharge */
  LL_UCPD_DisableVconnDischarge(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Return the UCPD Vconn discharge status.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_vconn_discharge_status_t UCPD Type-C detector status.
  */
hal_ucpd_vconn_discharge_status_t HAL_UCPD_IsEnabledVconnDischarge(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_vconn_discharge_status_t status;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Return Vconn discharge status */
  status = (hal_ucpd_vconn_discharge_status_t)LL_UCPD_IsEnabledVconnDischarge(UCPD_GET_INSTANCE(hucpd));

  return status;
}

/**
  * @brief  Set the type of ordered set to transmit.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  tx_ordered_set Ordered set type to transmit.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetTxOrderedSet(hal_ucpd_handle_t *hucpd, hal_ucpd_tx_ordered_set_t tx_ordered_set)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_TXORDSET_TYPE(tx_ordered_set));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_ACTIVE | HAL_UCPD_STATE_RX);

  /* Set the Tx message type */
  LL_UCPD_WriteTxOrderSet(UCPD_GET_INSTANCE(hucpd), (uint32_t)tx_ordered_set);

  return HAL_OK;
}

/**
  * @brief  Get the type of ordered set to transmit.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_tx_ordered_set_t The ordered set type to transmit.
  */
hal_ucpd_tx_ordered_set_t HAL_UCPD_GetTxOrderedSet(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_tx_ordered_set_t tx_ordered_set;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Set the Tx message type */
  tx_ordered_set = (hal_ucpd_tx_ordered_set_t)LL_UCPD_ReadTxOrderSet(UCPD_GET_INSTANCE(hucpd));

  return tx_ordered_set;
}

/**
  * @brief  Set the transmission mode.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  tx_mode Transmission mode.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetTxMode(hal_ucpd_handle_t *hucpd, hal_ucpd_tx_mode_t tx_mode)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_TX_MODE(tx_mode));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Set the transmission mode */
  LL_UCPD_SetTxMode(UCPD_GET_INSTANCE(hucpd), (uint32_t)tx_mode);

  return HAL_OK;
}

/**
  * @brief  Get the transmission mode.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_tx_mode_t Transmission mode.
  */
hal_ucpd_tx_mode_t HAL_UCPD_GetTxMode(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the transmission mode */
  return (hal_ucpd_tx_mode_t)LL_UCPD_GetTxMode(UCPD_GET_INSTANCE(hucpd));
}

/**
  * @brief  Set the reception mode.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  rx_mode Reception mode.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetRxMode(hal_ucpd_handle_t *hucpd, hal_ucpd_rx_mode_t rx_mode)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_RX_MODE(rx_mode));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Set the reception mode */
  LL_UCPD_SetRxMode(UCPD_GET_INSTANCE(hucpd), (uint32_t)rx_mode);

  return HAL_OK;
}

/**
  * @brief  Get the reception mode.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_rx_mode_t Reception mode.
  */
hal_ucpd_rx_mode_t HAL_UCPD_GetRxMode(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_rx_mode_t mode;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the reception mode */
  mode = (hal_ucpd_rx_mode_t)LL_UCPD_GetRxMode(UCPD_GET_INSTANCE(hucpd));

  return mode;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Set the analog PHY operating role.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  role Source or sink role.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetRole(hal_ucpd_handle_t *hucpd, hal_ucpd_role_t role)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_ROLE(role));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Set the analog PHY operating role */
  LL_UCPD_SetRole(UCPD_GET_INSTANCE(hucpd), (uint32_t)role);

  return HAL_OK;
}

/**
  * @brief  Get the analog PHY operating role.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_role_t Analog PHY operating role.
  */
hal_ucpd_role_t HAL_UCPD_GetRole(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_role_t role;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the analog PHY operating role */
  role = (hal_ucpd_role_t)LL_UCPD_GetRole(UCPD_GET_INSTANCE(hucpd));

  return role;
}

/**
  * @brief  Set Rp resistors to signal the device's power requirements to the host.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  rp_value Rp value to set.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetRp(hal_ucpd_handle_t *hucpd, hal_ucpd_rp_value_t rp_value)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_RP_VALUE(rp_value));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Set the Rp resistors */
  LL_UCPD_SetRpResistor(UCPD_GET_INSTANCE(hucpd), (uint32_t)rp_value);

  return HAL_OK;
}

/**
  * @brief  Get the Rp resistors value.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_rp_value_t Rp value.
  */
hal_ucpd_rp_value_t HAL_UCPD_GetRp(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_rp_value_t rp_value;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the Rp resistors value */
  rp_value = (hal_ucpd_rp_value_t)LL_UCPD_GetRpResistor(UCPD_GET_INSTANCE(hucpd));

  return rp_value;
}

/**
  * @brief  Set which CC line(s) is(are) enabled.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  cc_enable CC line(s) to enable.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetCCLines(hal_ucpd_handle_t *hucpd, const hal_ucpd_cc_enable_t cc_enable)
{
  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Check function parameters */
  ASSERT_DBG_PARAM(IS_UCPD_CC_LINE_EN(cc_enable));

  /* Enable or disable the CC line */
  LL_UCPD_SetCCEnable(UCPD_GET_INSTANCE(hucpd), (uint32_t)cc_enable);

  return HAL_OK;
}

/**
  * @brief  Get which CC line(s) is(are) enabled.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_cc_enable_t Enabled CC line(s).
  */
hal_ucpd_cc_enable_t HAL_UCPD_GetCCLines(const hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_cc_enable_t cc_enable;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the CC line enable status */
  cc_enable = (hal_ucpd_cc_enable_t)LL_UCPD_GetCCEnable(UCPD_GET_INSTANCE(hucpd));

  return cc_enable;
}

/**
  * @brief  Set the active CC line.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  cc_line Active CC line to set.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_SetActiveCC(hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_CC_LINE(cc_line));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Set the active CC line */
  LL_UCPD_SetCCPin(UCPD_GET_INSTANCE(hucpd), (uint32_t)cc_line);

  return HAL_OK;
}

/**
  * @brief  Get the active CC line.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_cc_line_t Active CC line.
  */
hal_ucpd_cc_line_t HAL_UCPD_GetActiveCC(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_cc_line_t cc_line;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get the active CC line */
  cc_line = (hal_ucpd_cc_line_t)LL_UCPD_GetCCPin(UCPD_GET_INSTANCE(hucpd));

  return cc_line;
}

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Enable the detection of Fast Role Swap reception.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableFRS_Rx(const hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Enable Fast Role Swap Rx detection */
  LL_UCPD_EnableFRSDetection(p_ucpdx);

  /* Enable FRS interrupt */
  LL_UCPD_EnableIT_FRS(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Disable the detection of Fast Role Swap reception.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableFRS_Rx(const hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Disable Fast Role Swap Rx detection */
  LL_UCPD_DisableFRSDetection(p_ucpdx);

  /* Disable FRS interrupt */
  LL_UCPD_DisableIT_FRS(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Return the detection of Fast Role Swap reception status.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_frs_rx_status_t Fast Role Swap reception status.
  */
hal_ucpd_frs_rx_status_t HAL_UCPD_IsEnabledFRS_Rx(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_frs_rx_status_t status;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  status = (hal_ucpd_frs_rx_status_t)LL_UCPD_IsEnabledFRSDetection(UCPD_GET_INSTANCE(hucpd));

  return status;
}

/**
  * @brief  Send a Fast Role Swap to the port partner.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD Fast Role Swap has been correctly initiated.
  */
hal_status_t HAL_UCPD_SendFRS(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Send Fast Role Swap */
  LL_UCPD_SignalFRSTX(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Send a cable reset to the cable.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD cable reset has been correctly initiated.
  */
hal_status_t HAL_UCPD_SendCableReset(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_ACTIVE | HAL_UCPD_STATE_RX);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Switch state */
  UCPD_CHECK_UPDATE_STATE(hucpd, global_state, ((uint32_t)HAL_UCPD_STATE_ACTIVE | (uint32_t)HAL_UCPD_STATE_RX),
                          HAL_UCPD_STATE_TX, previous_state);

  /* Enable required interrupt */
  LL_UCPD_EnableIT_TxMSGSENT(p_ucpdx);

  /* Change Tx mode to cable reset */
  LL_UCPD_SetTxMode(p_ucpdx, LL_UCPD_TXMODE_CABLE_RESET);

  /* Send the cable reset */
  LL_UCPD_SendMessage(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Send a hard reset to the port partner.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD hard reset has been correctly initiated.
  */
hal_status_t HAL_UCPD_SendHardReset(const hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Enable hard reset sent and discarded interrupts */
  LL_UCPD_EnableIT(p_ucpdx, UCPD_IMR_HRSTSENTIE | UCPD_IMR_HRSTDISCIE);

  /* Send hard reset */
  LL_UCPD_SendHardReset(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Enable hard reset reception.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_EnableHardReset_Rx(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Enable the PHY receiver */
  LL_UCPD_EnableRx(UCPD_GET_INSTANCE(hucpd));

  /* Enable hard reset received interrupt */
  LL_UCPD_EnableIT_RxHRST(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Enable hard reset reception.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD instance has been correctly configured.
  */
hal_status_t HAL_UCPD_DisableHardReset_Rx(hal_ucpd_handle_t *hucpd)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Disable the PHY receiver */
  LL_UCPD_DisableRx(UCPD_GET_INSTANCE(hucpd));

  /* Disable hard reset received interrupt */
  LL_UCPD_DisableIT_RxHRST(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}

/**
  * @brief  Return hard reset reception status.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_hard_reset_rx_status_t Hard reset reception status.
  */
hal_ucpd_hard_reset_rx_status_t HAL_UCPD_IsEnabledHardReset_Rx(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_hard_reset_rx_status_t status;

  /* Check the UCPD handle and parameters allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Get hard reset reception status */
  status = (hal_ucpd_hard_reset_rx_status_t)LL_UCPD_IsEnabledIT_RxHRST(UCPD_GET_INSTANCE(hucpd));

  return status;
}

/**
  * @brief  Start sending a BIST test sequence (BIST Carrier Mode 2).
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK   UCPD test sequence has been correctly initiated.
  */
hal_status_t HAL_UCPD_SendBIST(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_ACTIVE);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Switch state */
  UCPD_CHECK_UPDATE_STATE(hucpd, global_state, (uint32_t)HAL_UCPD_STATE_ACTIVE, HAL_UCPD_STATE_TX, previous_state);

  /* Set Tx mode */
  LL_UCPD_SetTxMode(p_ucpdx, LL_UCPD_TXMODE_BIST_CARRIER2);

  /* Start BIST sequence */
  LL_UCPD_SendMessage(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Stop BIST test sequence (BIST Carrier Mode 2) sending.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval HAL_OK UCPD test sequence has been correctly stopped.
  */
hal_status_t HAL_UCPD_StopBIST(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;
  uint32_t reg_cr;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_TX);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Save context - except TXMODE and TXSEND */
  reg_cr = LL_UCPD_READ_REG(p_ucpdx, CR);
  STM32_CLEAR_BIT(reg_cr, (UCPD_CR_TXMODE | UCPD_CR_TXSEND));

  /* Stop BIST sequence */
  LL_UCPD_Disable(p_ucpdx);

  /* Restore context */
  LL_UCPD_Enable(p_ucpdx);
  LL_UCPD_WRITE_REG(p_ucpdx, CR, reg_cr);

  /* Switch state */
  hucpd->previous_state = hucpd->global_state;
  hucpd->global_state   = HAL_UCPD_STATE_ACTIVE;

  return HAL_OK;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @}
  */

/** @addtogroup UCPD_Exported_Functions_Group4
  * @{

A set of functions related to UCPDx peripheral status:

- CC line voltage status
  - HAL_UCPD_GetTypeCVoltageLevelCCx()

- Detected Rx ordered set
  - HAL_UCPD_GetDetectedRxOrderedSet()

  */

/**
  * @brief  Get the voltage state on CCx line.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  cc_line CC line of type @ref hal_ucpd_cc_line_t structure.
  * @return @ref hal_ucpd_vstate_t Voltage state on given CC line.
  */
hal_ucpd_vstate_t HAL_UCPD_GetTypeCVoltageLevelCCx(const hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line)
{
  UCPD_TypeDef *p_ucpdx;
  hal_ucpd_vstate_t vstate;
  uint32_t ll_vstate;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM(IS_UCPD_CC_LINE(cc_line));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Get the voltage level on the given CC line */
  if (cc_line == HAL_UCPD_LINE_CC1)
  {
    ll_vstate = LL_UCPD_GetTypeCVstateCC1(p_ucpdx);

    /* Interpret the corresponding resistor connected to the CC line depending on the current role */
    if (ll_vstate == LL_UCPD_CC1_VSTATE_LOWEST)
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ? HAL_UCPD_VSTATE_SRC_VRA : HAL_UCPD_VSTATE_SNK_VRA;
    }
    else if (ll_vstate == LL_UCPD_CC1_VSTATE_LOW)
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ? HAL_UCPD_VSTATE_SRC_VRD : HAL_UCPD_VSTATE_SNK_VRPDFLT;
    }
    else if (ll_vstate == LL_UCPD_CC1_VSTATE_HIGH)
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ? HAL_UCPD_VSTATE_SRC_VOPEN : HAL_UCPD_VSTATE_SNK_VRP15A;
    }
    else /* ll_vstate == LL_UCPD_CC1_VSTATE_HIGHEST */
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ?
               HAL_UCPD_VSTATE_SRC_INVALID : HAL_UCPD_VSTATE_SNK_VRP30A;
    }
  }
  else
  {
    ll_vstate = LL_UCPD_GetTypeCVstateCC2(p_ucpdx);

    /* Interpret the corresponding resistor connected to the CC line depending on the current role */
    if (ll_vstate == LL_UCPD_CC2_VSTATE_LOWEST)
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ? HAL_UCPD_VSTATE_SRC_VRA : HAL_UCPD_VSTATE_SNK_VRA;
    }
    else if (ll_vstate == LL_UCPD_CC2_VSTATE_LOW)
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ? HAL_UCPD_VSTATE_SRC_VRD : HAL_UCPD_VSTATE_SNK_VRPDFLT;
    }
    else if (ll_vstate == LL_UCPD_CC2_VSTATE_HIGH)
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ? HAL_UCPD_VSTATE_SRC_VOPEN : HAL_UCPD_VSTATE_SNK_VRP15A;
    }
    else /* ll_vstate == LL_UCPD_CC2_VSTATE_HIGHEST */
    {
      vstate = (LL_UCPD_GetRole(p_ucpdx) == LL_UCPD_ROLE_SRC) ?
               HAL_UCPD_VSTATE_SRC_INVALID : HAL_UCPD_VSTATE_SNK_VRP30A;
    }
  }

  /* Return the interpreted voltage state */
  return vstate;
}


#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Get the detected type of received ordered set.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @return @ref hal_ucpd_detected_rx_ordered_set_t The detected ordered set.
  */
hal_ucpd_detected_rx_ordered_set_t HAL_UCPD_GetDetectedRxOrderedSet(hal_ucpd_handle_t *hucpd)
{
  hal_ucpd_detected_rx_ordered_set_t rx_ordered_set;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Read the detected Rx message type */
  rx_ordered_set = (hal_ucpd_detected_rx_ordered_set_t)LL_UCPD_ReadRxOrderSet(UCPD_GET_INSTANCE(hucpd));

  return rx_ordered_set;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @}
  */

/** @addtogroup UCPD_Exported_Functions_Group5
  * @{

A set of functions allowing to manage data transfer:

- DMA operations
  - HAL_UCPD_Transmit_DMA()
  - HAL_UCPD_Receive_DMA()

- Abort
  - HAL_UCPD_Abort_IT()

- GoodCRC preparation
  - HAL_UCPD_SetGoodCRCData()

  */

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Send an amount of data in DMA mode.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_data Pointer to data buffer.
  * @param  size_byte Amount of bytes to be sent (min 2).
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         Tx DMA handle not set.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_UCPD_Transmit_DMA(hal_ucpd_handle_t *hucpd, const void *p_data, uint32_t size_byte)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hucpd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_UCPD_TRANSFER_SIZE(size_byte));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameters */
  if ((hucpd == NULL) || (p_data == NULL) || (size_byte < UCPD_MIN_MESSAGE_SIZE))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (hucpd->hdma_tx == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_ACTIVE | HAL_UCPD_STATE_RX);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Switch state */
  UCPD_CHECK_UPDATE_STATE(hucpd, global_state, ((uint32_t)HAL_UCPD_STATE_ACTIVE | (uint32_t)HAL_UCPD_STATE_RX),
                          HAL_UCPD_STATE_TX, previous_state);

  /* Set the transfer information */
  hucpd->p_buf_tx          = (const uint8_t *)p_data;
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
  hucpd->last_error_codes  = HAL_UCPD_ERROR_NONE;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

  /* Set the UCPD DMA transfer complete callback */
  hucpd->hdma_tx->p_xfer_cplt_cb = UCPD_DMATransmitCplt;

  /* Unused DMA half transfer complete callback */
  hucpd->hdma_tx->p_xfer_halfcplt_cb = NULL;

  /* Set the DMA error callback */
  hucpd->hdma_tx->p_xfer_error_cb = UCPD_DMAError;

  /* Set the DMA abort callback */
  hucpd->hdma_tx->p_xfer_abort_cb = UCPD_DMATxAbortCallback;

  /* Start DMA */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hucpd->hdma_tx, (uint32_t)hucpd->p_buf_tx,
                                     LL_UCPD_GetTxDataAddress(p_ucpdx), size_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
    /* Handle the error */
    hucpd->previous_state = hucpd->global_state;
    hucpd->global_state = HAL_UCPD_STATE_ACTIVE;
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
    hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Enable UCPD Tx DMA */
  LL_UCPD_EnableTxDMA(p_ucpdx);

  /* Enable required interrupts */
  LL_UCPD_EnableIT(p_ucpdx, LL_UCPD_IMR_TXMSGDISC | LL_UCPD_IMR_TXMSGABT | LL_UCPD_IMR_TXUND);

  /* Write payload size to transmit */
  LL_UCPD_WriteTxPaySize(p_ucpdx, size_byte);

  /* Send message */
  LL_UCPD_SendMessage(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Receive an amount of data in DMA mode, and send GoodCRC message after end of reception.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_data Pointer to data buffer.
  * @param  size_byte Amount of bytes to be received (min 2).
  * @note   This procedure also configure the Tx DMA to be ready for GoodCRC transmission after the end of reception.
  *         At reception completion, HAL_UCPD_RxCpltCallback() is executed and users can add their own code by
  *         customization of function pointer HAL_UCPD_RxCpltCallback(). At this point user must prepare the GoodCRC
  *         data to send by calling HAL_UCPD_SetGoodCRCData().
  *         After HAL_UCPD_RxCpltCallback() returns, the ISR transmits the GoodCRC message in the
  *         interrupt context.
  *         At GoodCRC transmission end of transfer, HAL_UCPD_TxGoodCRCCpltCallback() is executed and users can add
  *         their own code by customization of function pointer HAL_UCPD_TxGoodCRCCpltCallback().
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         Rx DMA handle not set.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_UCPD_Receive_DMA(hal_ucpd_handle_t *hucpd, void *p_data, uint32_t size_byte)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hucpd != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_UCPD_TRANSFER_SIZE(size_byte));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check input parameters */
  if ((hucpd == NULL) || (p_data == NULL) || (size_byte < UCPD_MIN_MESSAGE_SIZE))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (hucpd->hdma_rx == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state, HAL_UCPD_STATE_ACTIVE);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Switch state */
  UCPD_CHECK_UPDATE_STATE(hucpd, global_state, (uint32_t)HAL_UCPD_STATE_ACTIVE, HAL_UCPD_STATE_RX, previous_state);

  hucpd->p_buf_rx = (uint8_t *)p_data;

  /* Set the UCPD DMA transfer complete callback */
  hucpd->hdma_rx->p_xfer_cplt_cb = UCPD_DMAReceiveCplt;

  /* Unused DMA half transfer complete callback */
  hucpd->hdma_rx->p_xfer_halfcplt_cb = NULL;

  /* Set the DMA error callback */
  hucpd->hdma_rx->p_xfer_error_cb = UCPD_DMAError;

  /* Set the DMA abort callback */
  hucpd->hdma_rx->p_xfer_abort_cb = UCPD_DMARxAbortCallback;

  /* Start DMA */
  if (HAL_DMA_StartPeriphXfer_IT_Opt(hucpd->hdma_rx, LL_UCPD_GetRxDataAddress(p_ucpdx),
                                     (uint32_t)hucpd->p_buf_rx, size_byte, HAL_DMA_OPT_IT_NONE) != HAL_OK)
  {
    /* Handle the error */
    hucpd->previous_state = hucpd->global_state;
    hucpd->global_state = HAL_UCPD_STATE_ACTIVE;
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
    hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Prepare future transmission of GoodCRC if not done previously */
  if (hucpd->hdma_tx != NULL)
  {
    /* Set the UCPD DMA transfer complete callback */
    hucpd->hdma_tx->p_xfer_cplt_cb = UCPD_DMATransmitCplt;

    /* Unused DMA half transfer complete callback */
    hucpd->hdma_tx->p_xfer_halfcplt_cb = NULL;

    /* Set the DMA error callback */
    hucpd->hdma_tx->p_xfer_error_cb = UCPD_DMAError;

    /* Set the DMA abort callback */
    hucpd->hdma_tx->p_xfer_abort_cb = UCPD_DMATxAbortCallback;

    /* Start DMA */
    if (HAL_DMA_StartPeriphXfer_IT_Opt(hucpd->hdma_tx,
                                       (uint32_t)&hucpd->buff_goodcrc,
                                       LL_UCPD_GetTxDataAddress(p_ucpdx),
                                       UCPD_GOODCRC_SIZE,
                                       HAL_DMA_OPT_IT_NONE) != HAL_OK)
    {
      /* Handle the error */
      hucpd->previous_state = hucpd->global_state;
      hucpd->global_state = HAL_UCPD_STATE_ACTIVE;
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
      hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    /* Enable required interrupts */
    LL_UCPD_EnableIT(p_ucpdx, LL_UCPD_IMR_TXMSGDISC | LL_UCPD_IMR_TXMSGABT | LL_UCPD_IMR_TXUND);
  }

  /* Enable UCPD Rx DMA */
  LL_UCPD_EnableRxDMA(p_ucpdx);

  /* Enable required interrupts */
  LL_UCPD_EnableIT(p_ucpdx, LL_UCPD_IMR_RXOVR | LL_UCPD_IMR_RXMSGEND);

  /* Enable the PHY receiver */
  LL_UCPD_EnableRx(p_ucpdx);

  return HAL_OK;
}

/**
  * @brief  Abort ongoing transfers (Interrupt mode).
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @note   This procedure could be used for aborting any ongoing transfer started in DMA mode.
  *         This procedure performs following operations:
  *           - Disable UCPD interrupts (Tx and Rx)
  *           - Enable UCPD message sent interrupt (Tx)
  *           - Disable the DMA transfer in the peripheral register (if enabled)
  *           - Abort DMA transfer by calling HAL_DMA_Abort_IT() (in case of transfer in DMA mode)
  * @note   This procedure is executed in Interrupt mode, meaning that abort procedure could be
  *         considered as completed only when user abort complete callback is executed (not when exiting function).
  * @note   In case of Tx abort, the UCPD peripheral continues to send the remaining data but forces an incorrect CRC,
  *         is incorrect, so that the receiver can end the reception and discard the message.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_UCPD_Abort_IT(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;
  uint32_t abort_cplt = 1U;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Disable Rx and Tx UCPD interrupts */
  LL_UCPD_DisableIT(p_ucpdx, LL_UCPD_IMR_RXOVR | LL_UCPD_IMR_RXMSGEND | LL_UCPD_IMR_TXUND
                    | LL_UCPD_IMR_TXMSGABT | LL_UCPD_IMR_TXMSGDISC);

  /* Enable TXMGSENT interrupt to signal end of abort */
  LL_UCPD_EnableIT_TxMSGSENT(p_ucpdx);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->previous_state = hucpd->global_state;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

  hucpd->global_state = HAL_UCPD_STATE_ABORT;

  if (hucpd->hdma_tx != NULL)
  {
    LL_UCPD_DisableTxDMA(p_ucpdx);
    if (hucpd->hdma_tx->global_state == HAL_DMA_STATE_ACTIVE)
    {
      hucpd->hdma_tx->p_xfer_abort_cb = UCPD_DMATxAbortCallback;

      /* Abort DMA Tx */
      if (HAL_DMA_Abort_IT(hucpd->hdma_tx) == HAL_OK)
      {
        abort_cplt = 0U;
      }
    }
  }

  if (hucpd->hdma_rx != NULL)
  {
    LL_UCPD_DisableRxDMA(p_ucpdx);
    if (hucpd->hdma_rx->global_state == HAL_DMA_STATE_ACTIVE)
    {
      hucpd->hdma_rx->p_xfer_abort_cb = UCPD_DMARxAbortCallback;

      /* Abort DMA Rx */
      if (HAL_DMA_Abort_IT(hucpd->hdma_rx) == HAL_OK)
      {
        abort_cplt = 0U;
      }
    }
  }

  /* If no DMA abort complete callback execution is required => call user abort complete callback */
  if (abort_cplt != 0U)
  {
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
    hucpd->previous_state = hucpd->global_state;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

    hucpd->global_state = HAL_UCPD_STATE_ACTIVE;

#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
    hucpd->last_error_codes = HAL_UCPD_ERROR_NONE;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

    /* As no DMA to be aborted, call directly user abort complete callback */
#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered abort complete callback */
    hucpd->p_abort_cplt_cb(hucpd);
#else
    /* Call legacy weak abort complete callback */
    HAL_UCPD_AbortCpltCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Set the GoodCRC buffer data to transmit after a reception.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure which contains the UCPD instance.
  * @param  goodcrc_data GoodCRC data to transmit (little-endian).
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_ERROR         Tx DMA handle not set.
  * @retval HAL_OK buffer has been correctly set.
  */
hal_status_t HAL_UCPD_SetGoodCRCData(hal_ucpd_handle_t *hucpd, uint16_t goodcrc_data)
{
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (hucpd->hdma_tx == NULL)
  {
    return HAL_ERROR;
  }

  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  hucpd->buff_goodcrc = goodcrc_data;

  LL_UCPD_EnableTxDMA(UCPD_GET_INSTANCE(hucpd));

  return HAL_OK;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @}
  */

/** @addtogroup UCPD_Exported_Functions_Group6
  * @{

A set of functions allowing interrupts request and callbacks management:

- Interrupt requests
  - HAL_UCPD_IRQHandler()

- Callbacks
  - HAL_UCPD_TxCpltCallback()
  - HAL_UCPD_TxGoodCRCCpltCallback()
  - HAL_UCPD_TxDiscardCallback()
  - HAL_UCPD_TxAbortCallback()
  - HAL_UCPD_RxCpltCallback()
  - HAL_UCPD_RxOrdDetCallback()
  - HAL_UCPD_HRstSentCallback()
  - HAL_UCPD_HRstRxCallback()
  - HAL_UCPD_HRstDiscardCallback()
  - HAL_UCPD_TypeCEventCCxCallback()
  - HAL_UCPD_FRSEvtCallback()
  - HAL_UCPD_AbortCpltCallback()
  - HAL_UCPD_ErrorCallback()

- Callback registering
  - HAL_UCPD_RegisterTxCpltCallback()
  - HAL_UCPD_RegisterTxGoodCRCCpltCallback()
  - HAL_UCPD_RegisterTxDiscardCallback()
  - HAL_UCPD_RegisterTxAbortCallback()
  - HAL_UCPD_RegisterRxCpltCallback()
  - HAL_UCPD_RegisterRxOrdDetCallback()
  - HAL_UCPD_RegisterHRstSentCallback()
  - HAL_UCPD_RegisterHRstRxCallback()
  - HAL_UCPD_RegisterHRstDiscardCallback()
  - HAL_UCPD_RegisterTypeCEventCCxCallback()
  - HAL_UCPD_RegisterFRSEvtCallback()
  - HAL_UCPD_AbortCpltCallback()
  - HAL_UCPD_RegisterErrorCallback()

  */

/**
  * @brief  Handler of the UCPD interrupt request.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
void HAL_UCPD_IRQHandler(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  /* Check the handle allocation */
  ASSERT_DBG_PARAM(hucpd != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Get current interrupt flags and interrupt sources value */
  uint32_t it_flags_sources = LL_UCPD_READ_REG(p_ucpdx, SR);

  /* Mask the disabled interrupts - including RXERR which is not present in IMR */
  it_flags_sources &= (LL_UCPD_READ_REG(p_ucpdx, IMR) | UCPD_SR_RXERR);

  /* Exit IRQHandler if no active interrupts were raised */
  if (it_flags_sources == 0U)
  {
    return;
  }

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  /* Message transmission discarded --------------------------------------*/
  if ((it_flags_sources & UCPD_SR_TXUND) != 0U)
  {
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
    hucpd->last_error_codes |= HAL_UCPD_ERROR_TXUND;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

    /* Disable TXUND IT */
    LL_UCPD_DisableIT_TxUND(p_ucpdx);

    /* Clear pending flag */
    LL_UCPD_ClearFlag_TxUND(p_ucpdx);

    /* Enable TXMSGSENT IT as an erroneous message is sent in case of underrun */
    LL_UCPD_EnableIT_TxMSGSENT(p_ucpdx);
  }

  /* Rx overrun ----------------------------------------------------------*/
  if ((it_flags_sources & UCPD_SR_RXOVR) != 0U)
  {
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
    hucpd->last_error_codes |= HAL_UCPD_ERROR_RXOVR;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

    /* Clear pending flag */
    LL_UCPD_ClearFlag_RxOvr(p_ucpdx);
  }

  /* Rx message received -------------------------------------------------*/
  if ((it_flags_sources & UCPD_SR_RXMSGEND) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_RxMsgEnd(p_ucpdx);

    /* Rx error ------------------------------------------------------------*/
    if ((it_flags_sources & UCPD_SR_RXERR) != 0U)
    {
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
      hucpd->last_error_codes |= HAL_UCPD_ERROR_RXERR;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */
    }
    /* Discard the message if an error was raised */
    else
    {
#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
      /* Call registered Rx complete callback */
      hucpd->p_rx_cplt_cb(hucpd);
#else
      /* Call legacy weak Rx complete callback */
      HAL_UCPD_RxCpltCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */

      /* Send GoodCRC if received message is correct */
      if ((LL_UCPD_IsEnabledTxDMA(p_ucpdx) == 1U)
          && (hucpd->hdma_tx != NULL) && ((it_flags_sources & UCPD_SR_RXERR) == 0U))
      {
        /* Write payload size to transmit */
        LL_UCPD_WriteTxPaySize(p_ucpdx, UCPD_GOODCRC_SIZE);

        /* Send message */
        LL_UCPD_SendMessage(p_ucpdx);
      }
      else
      {
        if (hucpd->hdma_tx != NULL)
        {
          hucpd->hdma_tx->p_xfer_abort_cb = UCPD_DMATxAbortCallback;

          /* HAL_UCPD_SetGoodCRCData was not called: Abort DMA TX */
          if (HAL_DMA_Abort_IT(hucpd->hdma_tx) != HAL_OK)
          {
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
            /* DMA error */
            hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

            /* Call Directly hucpd->hdma_tx->p_xfer_abort_cb function in case of error */
            hucpd->hdma_tx->p_xfer_abort_cb(hucpd->hdma_tx);
          }
        }
      }
    }
  }

  /* Message transmission discarded --------------------------------------*/
  if ((it_flags_sources & UCPD_SR_TXMSGDISC) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_TxMSGDISC(p_ucpdx);

    /* Abort the current Tx DMA process */
    if (hucpd->hdma_tx != NULL)
    {
      /* Set the UCPD DMA Abort callback :
          leads to HAL_UCPD_TxMsgDiscardCallback() at end of DMA abort procedure */
      hucpd->hdma_tx->p_xfer_abort_cb = UCPD_DMAEndTxMsgDiscardCallback;

      /* Abort DMA TX */
      if (HAL_DMA_Abort_IT(hucpd->hdma_tx) != HAL_OK)
      {
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
        /* DMA error */
        hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

        /* Call Directly hucpd->hdma_tx->p_xfer_abort_cb function in case of error */
        hucpd->hdma_tx->p_xfer_abort_cb(hucpd->hdma_tx);
      }
    }
  }

  /* Message transmission completed --------------------------------------*/
  if ((it_flags_sources & UCPD_SR_TXMSGSENT) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_TxMSGSENT(p_ucpdx);

    /* End of abort case */
    if (hucpd->global_state == HAL_UCPD_STATE_ABORT)
    {
      /* Clear error flag */
      LL_UCPD_ClearFlag_TxUND(p_ucpdx);

      hucpd->previous_state = HAL_UCPD_STATE_ABORT;
      hucpd->global_state = HAL_UCPD_STATE_ACTIVE;

#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
      hucpd->last_error_codes = HAL_UCPD_ERROR_NONE;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

      /* Check if a Rx Abort process is still ongoing */
      if (hucpd->hdma_rx != NULL)
      {
        if ((hucpd->hdma_rx->global_state != HAL_DMA_STATE_ABORT) || (hucpd->hdma_rx->p_xfer_abort_cb == NULL))
        {
          /* Call user abort complete callback */
#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
          /* Call registered abort complete callback */
          hucpd->p_abort_cplt_cb(hucpd);
#else
          /* Call legacy weak abort complete callback */
          HAL_UCPD_AbortCpltCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
        }
      }
    }

    /* End of GoodCRC transmission case */
    else if (hucpd->global_state == HAL_UCPD_STATE_RX)
    {
      /* Return to previous state */
      hucpd->global_state = hucpd->previous_state;
      hucpd->previous_state = HAL_UCPD_STATE_RX;

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
      /* Call registered Tx GoodCRC Complete callback */
      hucpd->p_tx_goodcrc_cplt_cb(hucpd);
#else
      /* Call legacy weak Tx GoodCRC Complete callback */
      HAL_UCPD_TxGoodCRCCpltCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
    }
    /* End of transmission case */
    else
    {
      /* Clear error flag in case of previous underrun. TXMSGSENT marks the end of the underrun error */
      LL_UCPD_ClearFlag_TxUND(p_ucpdx);

      /* Reset Tx mode */
      LL_UCPD_SetTxMode(p_ucpdx, LL_UCPD_TXMODE_NORMAL);

      /* Return to previous state */
      hal_ucpd_state_t prev_state = hucpd->previous_state;
      hucpd->previous_state = hucpd->global_state;
      hucpd->global_state = prev_state;

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
      /* Call registered Tx Complete callback */
      hucpd->p_tx_cplt_cb(hucpd);
#else
      /* Call legacy weak Tx Complete callback */
      HAL_UCPD_TxCpltCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
    }
  }

  /* Message transmission abort ------------------------------------------*/
  if ((it_flags_sources & UCPD_SR_TXMSGABT) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_TxMSGABT(p_ucpdx);

    /* Abort the current Tx DMA process */
    if (hucpd->hdma_tx != NULL)
    {
      /* Set the UCPD DMA Abort callback :
          leads to HAL_UCPD_TxAbortCallback() at end of DMA abort procedure */
      hucpd->hdma_tx->p_xfer_abort_cb = UCPD_DMAEndTxMsgAbortCallback;

      /* Abort DMA Tx */
      if (HAL_DMA_Abort_IT(hucpd->hdma_tx) != HAL_OK)
      {
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
        /* DMA error */
        hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

        /* Call Directly hucpd->hdma_tx->p_xfer_abort_cb function in case of error */
        hucpd->hdma_tx->p_xfer_abort_cb(hucpd->hdma_tx);
      }
    }
  }

  /* Hard reset discarded ------------------------------------------------*/
  if ((it_flags_sources & UCPD_SR_HRSTDISC) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_TxHRSTDISC(p_ucpdx);

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered hard reset discarded callback */
    hucpd->p_hrst_discard_cb(hucpd);
#else
    /* Call legacy weak hard reset discarded callback */
    HAL_UCPD_HRstDiscardCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }

  /* Hard reset sent -----------------------------------------------------*/
  if ((it_flags_sources & UCPD_SR_HRSTSENT) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_TxHRSTSENT(p_ucpdx);

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered hard reset sent callback */
    hucpd->p_hrst_sent_cb(hucpd);
#else
    /* Call legacy weak hard reset sent callback */
    HAL_UCPD_HRstSentCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }

  /* Receive data register not empty -------------------------------------*/
  /* Not treated as all transfers are done by DMA and RXNE flag is cleared automatically */

  /* Rx ordered set (4 K-codes) detection --------------------------------*/
  if ((it_flags_sources & UCPD_SR_RXORDDET) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_RxOrderSet(p_ucpdx);

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered Rx ordered set code detected callback */
    hucpd->p_rx_ord_set_cb(hucpd);
#else
    /* Call legacy weak Rx ordered set code detected callback */
    HAL_UCPD_RxOrdDetCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }

  /* Rx hard reset detection ---------------------------------------------*/
  if ((it_flags_sources & UCPD_SR_RXHRSTDET) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_RxHRST(p_ucpdx);

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered Rx hard reset received callback */
    hucpd->p_hrst_rx_cb(hucpd);
#else
    /* Call legacy weak Rx hard reset received callback */
    HAL_UCPD_HRstRxCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

  /* Type-C event detected on CCx ----------------------------------------*/
  if (((it_flags_sources & UCPD_SR_TYPECEVT1) != 0U) || ((it_flags_sources & UCPD_SR_TYPECEVT2) != 0U))
  {
    hal_ucpd_cc_line_t line;

    /* If coming from CC1 */
    if ((it_flags_sources & UCPD_SR_TYPECEVT1) != 0U)
    {
      /* If also coming from CC2 */
      if ((it_flags_sources & UCPD_SR_TYPECEVT2) != 0U)
      {
        line = HAL_UCPD_LINE_CC1CC2;
      }
      else
      {
        line = HAL_UCPD_LINE_CC1;
      }
    }
    /* Else coming from CC2 */
    else
    {
      line = HAL_UCPD_LINE_CC2;
    }

    /* Clear pending flag */
    LL_UCPD_ClearFlag(p_ucpdx, UCPD_ICR_TYPECEVT1CF | UCPD_ICR_TYPECEVT2CF);

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered Type-C event on CC1 callback */
    hucpd->p_type_c_event_ccx_cb(hucpd, line);
#else
    /* Call legacy weak Type-C event on CC1 callback */
    HAL_UCPD_TypeCEventCCxCallback(hucpd, line);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)

  /* Fast Role Swap detection --------------------------------------------*/
  if ((it_flags_sources & UCPD_SR_FRSEVT) != 0U)
  {
    /* Clear pending flag */
    LL_UCPD_ClearFlag_FRS(p_ucpdx);

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered Fast Role Swap detection callback */
    hucpd->p_frs_evt_cb(hucpd);
#else
    /* Call legacy weak Fast Role Swap detection callback */
    HAL_UCPD_FRSEvtCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

  /* Error handling ------------------------------------------------------*/
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
  if (hucpd->last_error_codes != HAL_UCPD_ERROR_NONE)
  {
#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
    /* Call registered error callback */
    hucpd->p_error_cb(hucpd);
#else
    /* Call legacy weak error callback */
    HAL_UCPD_ErrorCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
  }
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */
}

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Callback for Tx message sent.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_TxCpltCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_TxCpltCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for Tx GoodCRC message sent.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_TxGoodCRCCpltCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_TxGoodCRCCpltCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for Tx message discarded.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_TxDiscardCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_TxDiscardCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for Tx message aborted.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_TxAbortCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_TxAbortCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for Rx message received.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_RxCpltCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_RxCpltCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for Rx ordered set (4 K-codes) detected.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_RxOrdDetCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_RxOrdDetCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for hard reset sent.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_HRstSentCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_HRstSentCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for Rx hard reset received.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_HRstRxCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_HRstRxCallback() can be implemented in the user file.
   */
}

/**
  * @brief  Callback for hard reset discarded.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_HRstDiscardCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_HRstDiscardCallback() can be implemented in the user file.
   */
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Callback for Type-C event detection on CCx.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  cc_line CC line of type @ref hal_ucpd_cc_line_t structure.
  */
__WEAK void HAL_UCPD_TypeCEventCCxCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cc_line_t cc_line)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);
  STM32_UNUSED(cc_line);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_TypeCEventCCxCallback() can be implemented in the user file.
   */
}

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Callback for Fast Role Swap event detection.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_FRSEvtCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_FRSEvtCallback() can be implemented in the user file.
   */
}


/**
  * @brief  Abort complete callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_AbortCpltCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_AbortCpltCallback() can be implemented in the user file.
   */
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Error callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
__WEAK void HAL_UCPD_ErrorCallback(hal_ucpd_handle_t *hucpd)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hucpd);

  /** @note This function must not be modified, when the callback is needed,
            HAL_UCPD_ErrorCallback() can be implemented in the user file.
   */

  /** @note The hucpd handle's last_error_codes parameter is updated by the UCPD processes,
            and the user can use the HAL_UCPD_GetLastErrorCodes() API to verify the most recent error that occurred.
   */
}

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Register the UCPD Tx message sent callback to be used instead of
  *         the weak HAL_UCPD_TxCpltCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Tx message sent callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterTxCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_tx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD Tx GoodCRC message sent callback to be used instead of
  *         the weak HAL_UCPD_TxGoodCRCCpltCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Tx message sent callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterTxGoodCRCCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_tx_goodcrc_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD Tx message discarded callback to be used instead of
  *         the weak HAL_UCPD_TxDiscardCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Tx message discarded callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterTxDiscardCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_tx_discard_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD Tx message aborted callback to be used instead of
  *         the weak HAL_UCPD_TxAbortCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Tx message aborted callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterTxAbortCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_tx_abort_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD Rx complete callback to be used instead of
  *         the weak HAL_UCPD_RegisterRxCpltCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Rx complete callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterRxCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_rx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD Rx ordered set detected callback to be used instead of
  *         the weak HAL_UCPD_RegisterRxOrdDetCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Rx ordered set detected callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterRxOrdDetCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_rx_ord_set_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD hard reset sent callback to be used instead of
  *         the weak HAL_UCPD_HRstSentCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t hard reset sent callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterHRstSentCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_hrst_sent_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD hard reset received callback to be used instead of
  *         the weak HAL_UCPD_RegisterHRstRxCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t hard reset received callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterHRstRxCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_hrst_rx_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD hard reset discarded callback to be used instead of
  *         the weak HAL_UCPD_HRstDiscardCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t hard reset discarded callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterHRstDiscardCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_hrst_discard_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Register the UCPD Type-C event on CCx callback to be used instead of
  *         the weak HAL_UCPD_RegisterTypeCEventCCxCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Type-C event on CCx callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterTypeCEventCCxCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cc_event_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_type_c_event_ccx_cb = p_callback;

  return HAL_OK;
}

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  Register the UCPD Fast Role Swap event detected callback to be used instead of
  *         the weak HAL_UCPD_RegisterFRSEvtCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Fast Role Swap event detected callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterFRSEvtCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_frs_evt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the UCPD abort complete Callback to be used instead of
  *         the weak HAL_UCPD_AbortCpltCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t abort complete Callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterAbortCpltCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_abort_cplt_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @brief  Register the UCPD Error Callback to be used instead of
  *         the weak HAL_UCPD_ErrorCallback() predefined callback.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @param  p_callback Pointer to the @ref hal_ucpd_cb_t Error Callback function.
  * @retval HAL_INVALID_PARAM p_callback is NULL.
  * @retval HAL_OK            Register completed successfully.
  */
hal_status_t HAL_UCPD_RegisterErrorCallback(hal_ucpd_handle_t *hucpd, hal_ucpd_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hucpd == NULL) || (p_callback == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_INIT |
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE);

  hucpd->p_error_cb = p_callback;

  return HAL_OK;
}

#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @addtogroup UCPD_Exported_Functions_Group7
  * @{

A set of functions allowing to manage peripheral states and errors:

- HAL_UCPD_GetState()
- HAL_UCPD_GetLastErrorCodes()

  */

/**
  * @brief  Retrieve the HAL UCPD global state.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval hal_ucpd_state_t HAL UCPD global state
  */
hal_ucpd_state_t HAL_UCPD_GetState(const hal_ucpd_handle_t *hucpd)
{
  ASSERT_DBG_PARAM((hucpd != NULL));

  return hucpd->global_state;
}


#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
/**
  * @brief  Retrieve the HAL UCPD last error codes.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  * @retval uint32_t HAL UCPD bit mapped last errors.
  */
uint32_t HAL_UCPD_GetLastErrorCodes(const hal_ucpd_handle_t *hucpd)
{
  ASSERT_DBG_PARAM((hucpd != NULL));

  return hucpd->last_error_codes;
}
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

/**
  * @}
  */


#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @addtogroup UCPD_Exported_Functions_Group8
  * @{

A set of functions allowing to Acquire/Release the bus based on the HAL OS abstraction layer (if USE_HAL_MUTEX == 1):

 - HAL_UCPD_AcquireBus()
 - HAL_UCPD_ReleaseBus()

  */

/**
  * @brief  Acquire the UCPD bus thanks to the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t.
  * @param  timeout_ms Timeout duration in milliseconds.
  * @warning This function must be called from thread mode only (not from handler mode i.e from ISR).
  * @retval HAL_ERROR Operation completed with error.
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_UCPD_AcquireBus(hal_ucpd_handle_t *hucpd, uint32_t timeout_ms)
{
  hal_status_t status = HAL_ERROR;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Take the semaphore */
  if (HAL_OS_SemaphoreTake(&hucpd->semaphore, timeout_ms) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Release the UCPD bus thanks to the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t.
  * @note   This function can be called from thread mode or from handler mode i.e from ISR.
  * @retval HAL_ERROR Operation completed with error.
  * @retval HAL_OK    Operation completed successfully.
  */
hal_status_t HAL_UCPD_ReleaseBus(hal_ucpd_handle_t *hucpd)
{
  hal_status_t status = HAL_ERROR;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hucpd != NULL));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the state */
  ASSERT_DBG_STATE(hucpd->global_state,
                   HAL_UCPD_STATE_IDLE |
                   HAL_UCPD_STATE_ACTIVE |
                   HAL_UCPD_STATE_TX |
                   HAL_UCPD_STATE_RX |
                   HAL_UCPD_STATE_ABORT);

  /* Release the semaphore */
  if (HAL_OS_SemaphoreRelease(&hucpd->semaphore) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_UCPD_USER_DATA) && (USE_HAL_UCPD_USER_DATA == 1)
/** @addtogroup UCPD_Exported_Functions_Group9
  * @{

A set of functions allowing to manage a user data pointer stored to the UCPD handle:

 - HAL_UCPD_SetUserData()
 - HAL_UCPD_GetUserData()

  */

/**
  * @brief  Set the user data pointer into the handle.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_UCPD_SetUserData(hal_ucpd_handle_t *hucpd, const void *p_user_data)
{

  /* Check the parameters */
  ASSERT_DBG_PARAM(hucpd != NULL);

  hucpd->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data pointer from the handle.
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t.
  * @retval Pointer to the user data.
  */
const void *HAL_UCPD_GetUserData(const hal_ucpd_handle_t *hucpd)
{

  /* Check the parameters */
  ASSERT_DBG_PARAM(hucpd != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hucpd == NULL)
  {
    return NULL;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return (hucpd->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_UCPD_USER_DATA */

/**
  * @}
  */

/** @defgroup UCPD_Private_Functions UCPD Private Functions
  * @{
  */

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
/**
  * @brief  End ongoing Tx transfer on UCPD peripheral (following error detection or Transmit completion).
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
static void UCPD_EndTxTransfer(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Disable UCPD Tx interrupts */
  LL_UCPD_DisableIT(p_ucpdx, LL_UCPD_IMR_TXUND | LL_UCPD_IMR_HRSTSENT | LL_UCPD_IMR_HRSTDISC
                    | LL_UCPD_IMR_TXMSGABT | LL_UCPD_IMR_TXMSGSENT | LL_UCPD_IMR_TXMSGDISC);

  hucpd->previous_state = hucpd->global_state;
  hucpd->global_state = HAL_UCPD_STATE_ACTIVE;
}

/**
  * @brief  End ongoing Rx transfer on UCPD peripheral (following error detection or Reception completion).
  * @param  hucpd Pointer to a @ref hal_ucpd_handle_t structure.
  */
static void UCPD_EndRxTransfer(hal_ucpd_handle_t *hucpd)
{
  UCPD_TypeDef *p_ucpdx;

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Disable UCPD Rx interrupts */
  LL_UCPD_DisableIT(p_ucpdx, LL_UCPD_IMR_RXMSGEND | LL_UCPD_IMR_RXOVR | LL_UCPD_IMR_RXHRSTDET
                    | LL_UCPD_IMR_RXORDDET);

  hucpd->previous_state = hucpd->global_state;
  hucpd->global_state = HAL_UCPD_STATE_ACTIVE;
}

/**
  * @brief  DMA UCPD transmit process complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  */
static void UCPD_DMATransmitCplt(hal_dma_handle_t *hdma)
{
  UCPD_TypeDef *p_ucpdx;

  const hal_dma_handle_t *p_hdma = hdma;
  const hal_ucpd_handle_t *hucpd = (const hal_ucpd_handle_t *)p_hdma->p_parent;
  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Enable Tx message sent interrupt */
  LL_UCPD_EnableIT_TxMSGSENT(p_ucpdx);

  /* Disable Tx DMA link */
  LL_UCPD_DisableTxDMA(p_ucpdx);
}

/**
  * @brief  DMA UCPD receive process complete callback.
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  */
static void UCPD_DMAReceiveCplt(hal_dma_handle_t *hdma)
{
  UCPD_TypeDef *p_ucpdx;

  const hal_dma_handle_t *p_hdma = hdma;
  hal_ucpd_handle_t *hucpd = (hal_ucpd_handle_t *)p_hdma->p_parent;
  const hal_ucpd_handle_t *p_hucpd = hucpd;
  p_ucpdx = UCPD_GET_INSTANCE(p_hucpd);

  /* Disable Rx DMA link */
  LL_UCPD_DisableRxDMA(p_ucpdx);

  /* Return to ACTIVE state */
  hucpd->global_state = HAL_UCPD_STATE_ACTIVE;
}

/**
  * @brief  DMA UCPD communication error callback.
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  */
static void UCPD_DMAError(hal_dma_handle_t *hdma)
{
  const hal_dma_handle_t *p_hdma = hdma;
  hal_ucpd_handle_t *hucpd = (hal_ucpd_handle_t *)p_hdma->p_parent;
  hal_ucpd_state_t prev_state;
  UCPD_TypeDef *p_ucpdx;

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Stop UCPD DMA Tx request if ongoing */
  const uint32_t isTxDMAEnabled = LL_UCPD_IsEnabledTxDMA(p_ucpdx);
  if ((hucpd->global_state == HAL_UCPD_STATE_TX) && (isTxDMAEnabled != 0U))
  {
    UCPD_EndTxTransfer(hucpd);
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
    hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */
  }

  /* Check if Rx DMA is enabled */
  const uint32_t isRxDMAEnabled = LL_UCPD_IsEnabledRxDMA(p_ucpdx);
  if ((hucpd->global_state == HAL_UCPD_STATE_RX) && (isRxDMAEnabled != 0U))
  {
    UCPD_EndRxTransfer(hucpd);
#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
    hucpd->last_error_codes |= HAL_UCPD_ERROR_DMA;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */
  }

  /* Return to previous state */
  prev_state = hucpd->previous_state;
  hucpd->previous_state = hucpd->global_state;
  hucpd->global_state = prev_state;

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
  /* Call registered error callback */
  hucpd->p_error_cb(hucpd);
#else
  /* Call legacy weak error callback */
  HAL_UCPD_ErrorCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA UCPD Tx communication abort callback, when initiated by user
  *         (To be called at end of DMA Tx Abort procedure following user abort request).
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  * @note   When this callback is executed, User Abort complete callback is called only if no
  *         Abort still ongoing for Rx DMA Handle.
  */
static void UCPD_DMATxAbortCallback(hal_dma_handle_t *hdma)
{
  const hal_dma_handle_t *p_hdma = hdma;
  const hal_ucpd_handle_t *hucpd = (const hal_ucpd_handle_t *)p_hdma->p_parent;
  UCPD_TypeDef *p_ucpdx;

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Clear error flags */
  LL_UCPD_ClearFlag(p_ucpdx, UCPD_ICR_TXUNDCF | UCPD_ICR_HRSTDISCCF | UCPD_ICR_TXMSGABTCF | UCPD_ICR_TXMSGDISCCF);

  /* Disable Tx DMA link */
  LL_UCPD_DisableTxDMA(p_ucpdx);

  /* The abort completes when TXMSGSENT interrupt asserts */
}


/**
  * @brief  DMA UCPD Rx communication abort callback, when initiated by user
  *         (To be called at end of DMA Rx Abort procedure following user abort request).
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  * @note   When this callback is executed, User Abort complete callback is called only if no
  *         Abort still ongoing for Tx DMA Handle.
  */
static void UCPD_DMARxAbortCallback(hal_dma_handle_t *hdma)
{
  const hal_dma_handle_t *p_hdma = hdma;
  hal_ucpd_handle_t *hucpd = (hal_ucpd_handle_t *)p_hdma->p_parent;
  UCPD_TypeDef *p_ucpdx;

  /* Check if an Abort process is still ongoing */
  if (hucpd->hdma_tx != NULL)
  {
    if ((hucpd->hdma_tx->global_state == HAL_DMA_STATE_ABORT) && (hucpd->hdma_tx->p_xfer_abort_cb != NULL))
    {
      return;
    }
  }

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Clear error flags */
  LL_UCPD_ClearFlag_RxOvr(p_ucpdx);

  /* Disable Rx DMA link */
  LL_UCPD_DisableRxDMA(p_ucpdx);

#if defined (USE_HAL_UCPD_POWER_DELIVERY) && (USE_HAL_UCPD_POWER_DELIVERY == 1)
  hucpd->previous_state = HAL_UCPD_STATE_ACTIVE;
#endif /* USE_HAL_UCPD_POWER_DELIVERY */
  hucpd->global_state = HAL_UCPD_STATE_ACTIVE;

#if defined (USE_HAL_UCPD_GET_LAST_ERRORS) && (USE_HAL_UCPD_GET_LAST_ERRORS == 1)
  hucpd->last_error_codes = HAL_UCPD_ERROR_NONE;
#endif /* USE_HAL_UCPD_GET_LAST_ERRORS */

  /* Call user abort complete callback */
#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
  /* Call registered abort complete callback */
  hucpd->p_abort_cplt_cb(hucpd);
#else
  /* Call legacy weak abort complete callback */
  HAL_UCPD_AbortCpltCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
}

/**
  * @brief  End ongoing Tx message abort on UCPD peripheral (following TXMSGABT detection).
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  */
static void UCPD_DMAEndTxMsgAbortCallback(hal_dma_handle_t *hdma)
{
  hal_ucpd_handle_t *hucpd = (hal_ucpd_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);
  UCPD_TypeDef *p_ucpdx;

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Disable UCPD Tx interrupts */
  LL_UCPD_DisableIT(p_ucpdx, LL_UCPD_IMR_TXUND | LL_UCPD_IMR_TXMSGABT | LL_UCPD_IMR_TXMSGSENT
                    | LL_UCPD_IMR_TXMSGDISC);

  /* Return to previous state */
  hal_ucpd_state_t prev_state = hucpd->previous_state;
  hucpd->previous_state = hucpd->global_state;
  hucpd->global_state = prev_state;

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
  /* Call registered Tx Abort callback */
  hucpd->p_tx_abort_cb(hucpd);
#else
  /* Call legacy weak Tx Abort callback */
  HAL_UCPD_TxAbortCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
}

/**
  * @brief  End ongoing Tx message discard on UCPD peripheral (following TXMSGDISC detection).
  * @param  hdma Pointer to a hal_dma_handle_t structure which contains a DMA instance.
  */
static void UCPD_DMAEndTxMsgDiscardCallback(hal_dma_handle_t *hdma)
{
  hal_ucpd_handle_t *hucpd = (hal_ucpd_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);
  UCPD_TypeDef *p_ucpdx;

  p_ucpdx = UCPD_GET_INSTANCE(hucpd);

  /* Disable UCPD Tx interrupts */
  LL_UCPD_DisableIT(p_ucpdx, LL_UCPD_IMR_TXUND | LL_UCPD_IMR_TXMSGABT | LL_UCPD_IMR_TXMSGSENT
                    | LL_UCPD_IMR_TXMSGDISC);

  /* Return to previous state */
  hal_ucpd_state_t prev_state = hucpd->previous_state;
  hucpd->previous_state = hucpd->global_state;
  hucpd->global_state = prev_state;

#if defined (USE_HAL_UCPD_REGISTER_CALLBACKS) && (USE_HAL_UCPD_REGISTER_CALLBACKS == 1U)
  /* Call registered Tx Discard callback */
  hucpd->p_tx_discard_cb(hucpd);
#else
  /* Call legacy weak Tx Discard callback */
  HAL_UCPD_TxDiscardCallback(hucpd);
#endif /* USE_HAL_UCPD_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_UCPD_POWER_DELIVERY */

/**
  * @}
  */
/**
  * @}
  */
#endif /* USE_HAL_UCPD_MODULE */
#endif /* defined(UCPD1) */

/**
  * @}
  */
