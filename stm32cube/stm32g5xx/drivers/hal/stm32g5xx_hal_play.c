/**
  ******************************************************************************
  * @file    stm32g5xx_hal_play.c
  * @brief   PLAY HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functions of the Programmable Logic Array (PLAY) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Configuration functions
  *           + Peripheral Operational functions
  *           + Peripheral State functions
  *           + IRQ handler management
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

#if defined(PLAY1)
#if defined(USE_HAL_PLAY_MODULE) && (USE_HAL_PLAY_MODULE == 1)

/** @addtogroup PLAY
  * @{
  */
/** @defgroup PLAY_Introduction PLAY Introduction
  * @{

The PLAY hardware abstraction layer provides a comprehensive software interface to manage the Programmable Logic Array
peripheral on STM32 microcontrollers.
The programmable logic array allows the user to create custom logic and state machines without the need for external
programmable logic devices, such as FPGAs. The PLAY provides a number of programmable logic elements, in the form of
lookup tables (LUTs). The output can be programmed to be any logical function. More complex functions can be created
by cascading logic elements.

This HAL driver abstracts low-level hardware details, enabling configuration, operations, and interrupt handling,
thereby accelerating development and ensuring robust and scalable embedded applications leveraging the full
capabilities of the PLAY peripheral.

  */
/**
  * @}
  */

/** @defgroup PLAY_How_To_Use PLAY How To Use
  * @{

# How to use the PLAY HAL module driver

## Usage

1. Declare a hal_play_handle_t handle and initialize the PLAY driver with a PLAY instance by calling HAL_PLAY_Init().
  The PLAY clock is enabled inside HAL_PLAY_Init() if USE_HAL_PLAY_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

2. Configure the low-level hardware(CLOCK, NVIC...):
  - Enable the PLAY Bus clock if USE_HAL_PLAY_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO.
  - PLAYx pins configuration:
      - Enable the clock for the PLAYx GPIOs
      - Configure PLAYx pins as alternate function
  - NVIC configuration if you need to use PLAY interrupt process:
      - Configure the PLAY interrupt priority by calling HAL_NVIC_SetPriority().
      - Enable the PLAY IRQ by calling HAL_NVIC_EnableIRQ().
      - In PLAY IRQ handler, call HAL_PLAY_IRQHandler().

3. Configure the combinational and/or sequential logic functions in this order:
  - Configure the Input Multiplexers with HAL_PLAY_INPUT_SetConfig()
      Refer to the Input Interconnect Matrix in the Reference Manual and use the enum
      @ref hal_play_in_source_t to initialize the source signal field in the @ref hal_play_in_config_t structure.
  - Configure the lookup tables (LUTs) with HAL_PLAY_LUT_SetConfig()
    - When selecting a HAL_PLAY_LUT_CLK_GATE_FILTERx signal as the source for the lookup table clock gate, you must
      ensure that a filter is configured for the related Input Multiplexer.
      The clock gate signal must be synchronized with the PLAY kernel clock.
    - The truth table of a lookup table is composed of 16 combinations (with 4 inputs):
      Combination ID | IN3 | IN2 | IN1 | IN0 | OUT O(y)
      -------------- | --- | --- | --- | --- | --------
             0       |  0  |  0  |  0  |  0  |  O0
             1       |  0  |  0  |  0  |  1  |  O1
             2       |  0  |  0  |  1  |  0  |  O2
             3       |  0  |  0  |  1  |  1  |  O3
             4       |  0  |  1  |  0  |  0  |  O4
             5       |  0  |  1  |  0  |  1  |  O5
             6       |  0  |  1  |  1  |  0  |  O6
             7       |  0  |  1  |  1  |  1  |  O7
             8       |  1  |  0  |  0  |  0  |  O8
             9       |  1  |  0  |  0  |  1  |  O9
             10      |  1  |  0  |  1  |  0  |  O10
             11      |  1  |  0  |  1  |  1  |  O11
             12      |  1  |  1  |  0  |  0  |  O12
             13      |  1  |  1  |  0  |  1  |  O13
             14      |  1  |  1  |  1  |  0  |  O14
             15      |  1  |  1  |  1  |  1  |  O15
      An O(y) Output value is 0 or 1.
      The truth table value is calculated with this formula:

          (O0 * 2^0) + (O1 * 2^1) + (O2 * 2^2) + ... + ((O15 * 2^15))

      There are several Truth Table values for a logic gate depending on the selected inputs.
      For example the Truth Table value for the logic 'AND' are (non-exhaustive list):
        - for IN1 & IN0: 0x8888
        - for IN2 & IN1: 0xC0C0
        - for IN3 & IN2: 0xF000
        - for IN2, IN1 & IN0: 0x8080
        - for IN3, IN2, IN1 & IN0: 0x8000
        - ...
  - Configure the Output Multiplexers with HAL_PLAY_OUTPUT_SetConfig()

4. Call HAL_PLAY_Start() to perform the following actions:
  - Lock the PLAYx configuration registers to prevent any accidental write access.
    The kernel clock becomes operational. Then, the lookup table registered outputs, filters, Software Triggers and
    Edge Triggers become functional.
  - Set a first configuration of Edge Trigger on lookup table outputs.
    After this step, the PLAY Outputs can be connected to GPIOs or internal peripherals.

5. Use operating functions:
  - Polling mode:
    - HAL_PLAY_LUT_SetEdgeTrigger() allows to change lookup table Edge Trigger configuration
    - HAL_PLAY_LUT_GetEdgeTrigger() allows to retrieve the current lookup table Edge Trigger configuration
    - HAL_PLAY_LUT_PollForEdgeTrigger() allows to wait until selected lookup table output Edge Triggers are triggered
        - The 'ALL_EDGE' mode waits until all selected Edge Triggers are triggered
        - The 'ANY_EDGE' mode waits until one of selected Edge Triggers is triggered
    - HAL_PLAY_WriteSWTrigger() allows to change the state of Software Triggers
    - HAL_PLAY_ToggleSWTrigger() allows to toggle the state of Software Triggers
    - HAL_PLAY_ReadSWTrigger() allows to retrieve the current state of Software Triggers

  - Interrupt mode:
    - HAL_PLAY_LUT_SetEdgeTrigger_IT() allows to change lookup table Edge Trigger.
      The callback EdgeTriggerWriteCpltCallback is called when the write is completed.
    - HAL_PLAY_WriteSWTrigger_IT() allows to change the level of Software Trigger.
      The callback SWTriggerWriteCpltCallback is called when the write is completed.
    - HAL_PLAY_ToggleSWTrigger_IT() allows to toggle the level of Software Trigger.
      The callback SWTriggerWriteCpltCallback is called when the write is completed.
    - HAL_PLAY_LUT_EnableIT() allows to enable lookup table output interrupts.
    - HAL_PLAY_LUT_DisableIT() allows to disable lookup table output interrupts.
    - HAL_PLAY_LUT_GetIT() allows to retrieve the current lookup table output enabled interrupts.

6. Update PLAY Configuration (optional):
  To update the PLAY lookup table configurations, call HAL_PLAY_Stop() first.
  This API performs these actions:
    - disable all interrupts,
    - clear flags.
    - unlock the configuration registers.

  @warning before updating the lookup table configuration, it is strongly recommended to disconnect any GPIOs and/or
           peripherals to the PLAY Outputs to avoid any glitches:
             - Either immediately changing the output multiplexers configurations using HAL_PLAY_OUTPUT_SetSource() by
               selecting lookup table registered output (like @ref HAL_PLAY_LUT0_OUT_REGISTERED) as source.
             - Or disabling GPIO and disconnecting each peripheral taking the PLAY peripheral as inputs.

7. Call HAL_PLAY_DeInit() to deinitialize the PLAY peripheral.

## Callback registration
  When the preprocessor directive USE_HAL_PLAY_REGISTER_CALLBACKS is set to 1, the user can dynamically configure the
  driver callbacks, via its own method:

Callback name                | Default value                           | Callback registration function
---------------------------- | ------------------------------------    | ----------------------------------------------
SWTriggerWriteCpltCallback   | HAL_PLAY_SWTriggerWriteCpltCallback()   | HAL_PLAY_RegisterSWTriggerWriteCpltCallback()
EdgeTriggerWriteCpltCallback | HAL_PLAY_EdgeTriggerWriteCpltCallback() | HAL_PLAY_RegisterEdgeTriggerWriteCpltCallback()
LUTOutputRisingCallback      | HAL_PLAY_LUTOutputRisingCallback()      | HAL_PLAY_RegisterLUTOutputRisingCallback()
LUTOutputFallingCallback     | HAL_PLAY_LUTOutputFallingCallback()     | HAL_PLAY_RegisterLUTOutputFallingCallback()

  To unregister a callback, the default one must be registered.

  By default, after HAL_PLAY_Init() and when the state is HAL_PLAY_STATE_INIT, all callbacks are set to the
  corresponding weak functions.

  Callbacks can be registered in HAL_PLAY_STATE_INIT or HAL_PLAY_STATE_IDLE states.

  When the preprocessing directive USE_HAL_PLAY_REGISTER_CALLBACKS is set to 0 or is undefined,
  the callback registration feature is not available and callbacks are set to the corresponding weak functions.
  */
/**
  * @}
  */

/** @defgroup PLAY_Configuration_Table PLAY Configuration Table
  * @{
## PLAY driver configuration

Software configuration defined in stm32g5xx_hal_conf.h:
Preprocessor flags                |   Default value   | Comment
--------------------------------- | ----------------- | ------------------------------------------------
USE_HAL_PLAY_MODULE               |         1         | Enable HAL PLAY driver module
USE_HAL_PLAY_REGISTER_CALLBACKS   |         0         | Allow the user to define their own callback
USE_HAL_CHECK_PARAM               |         0         | Enable runtime parameter check
USE_HAL_PLAY_CLK_ENABLE_MODEL     | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PROCESS_STATE       |         0         | Enable atomicity of process state check
USE_HAL_PLAY_USER_DATA            |         0         | Add a user data inside HAL PLAY handle

Software configuration defined in preprocessor environment:
Preprocessor flags                |   Default value   | Comment
--------------------------------- | ----------------- | ------------------------------------------------
USE_ASSERT_DBG_PARAM              |    Not defined    | Enable check param for HAL and LL
USE_ASSERT_DBG_STATE              |    Not defined    | Enable check state for HAL

Software configuration defined in stm32g5xx.h:
Preprocessor flags                |   Default value   | Comment
--------------------------------- | ----------------- | ------------------------------------------------
CMSE_SECURE_EXECUTION_ENVIRONMENT |    Not defined    | Defined in secure context

  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup PLAY_Private_Constants  PLAY Private Constants
  * @{
  */

/**
  * @brief Definitions used to decode the @ref hal_play_in_source_t enumerated values
  */
#define PLAY_INSTANCE_ID_MASK  (0x3UL << HAL_PLAY_INSTANCE_ID_POS) /*!< Instance ID field mask                 */
#define PLAY_IN_MUX_MASK       (0x1FUL << HAL_PLAY_IN_MUX_POS)     /*!< Input multiplexer field mask           */
#define PLAY_IN_MUX_VALUE_POS  (0U)                                /*!< Input multiplexer value field position */
#define PLAY_IN_MUX_VALUE_MASK (0xFUL << PLAY_IN_MUX_VALUE_POS)    /*!< Input multiplexer value field mask     */

/**
  * @brief PLAY Interrupt Definition
  */
#define PLAY_IT_STATUS_SW_TRIGGER_WRITE_COMPLETE   LL_PLAY_IER_SWINWC_IEN  /*!< Software trigger write complete interrupt */
#define PLAY_IT_STATUS_EDGE_TRIGGER_WRITE_COMPLETE LL_PLAY_IER_FLCTLWC_IEN /*!< Edge trigger write complete interrupt     */

/**
  * @brief Maximum Timeout for any write on Software Trigger or Edge Trigger register.
  *
  * With LSI as PLAY kernel clock source and a prescaler of 32768, the play_clk cycle is 1s.
  * A write takes 3 cycles of play_clk + 2 cycles of PCLK, then a write can take almost 3s.
  */
#define PLAY_WRITE_TIMEOUT_MS (4000U) /*!< Maximum Write Timeout for Software Trigger or Edge Trigger register: 4000 ms */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup PLAY_Private_Macros  PLAY Private Macros
  * @{
  */

/**
  * @brief Retrieve the PLAY hardware CMSIS instance from the hal handle.
  * @param handle specifies the peripheral handle.
  */
#define PLAY_GET_INSTANCE(handle)  \
  ((PLAY_TypeDef *)((uint32_t)((handle)->instance)))

/**
  * @brief Retrieve the PLAYx instance ID from the HAL handle.
  * @param handle Specifies the peripheral handle.
  */
#define PLAY_GET_INSTANCE_ID(handle)  \
  (HAL_PLAY1_INSTANCE_ID)

/**
  * @brief Verifies the minimum pulse width value.
  * @param  width Value of pulse width.
  * @retval 1     width is a valid value.
  * @retval 0     width is an invalid value.
  */
#define IS_PLAY_MIN_PULSE_WIDTH(width)  ((width) <= (LL_PLAY_INPUT_FILTER_WIDTH_VALUE_MAX))

/**
  * @brief Verifies the edge detection mode.
  * @param  mode Value of edge detection mode (@ref hal_play_edge_detection_mode_t).
  * @retval 1    mode is a valid value.
  * @retval 0    mode is an invalid value.
  */
#define IS_PLAY_EDGE_DETECTION_MODE(mode)                 \
  (((mode) == HAL_PLAY_EDGE_DETECTION_BYPASSED)           \
   || ((mode) == HAL_PLAY_EDGE_DETECTION_RISING)          \
   || ((mode) == HAL_PLAY_EDGE_DETECTION_FALLING)         \
   || ((mode) == HAL_PLAY_EDGE_DETECTION_RISING_FALLING))

/**
  * @brief Verifies the input multiplexer.
  * @param  mux Input multiplexer (@ref hal_play_in_t).
  * @retval 1   mux is a valid value.
  * @retval 0   mux is an invalid value.
  */
#define IS_PLAY_IN(mux)         \
  (((mux) == HAL_PLAY_IN0)      \
   || ((mux) == HAL_PLAY_IN1)   \
   || ((mux) == HAL_PLAY_IN2)   \
   || ((mux) == HAL_PLAY_IN3)   \
   || ((mux) == HAL_PLAY_IN4)   \
   || ((mux) == HAL_PLAY_IN5)   \
   || ((mux) == HAL_PLAY_IN6)   \
   || ((mux) == HAL_PLAY_IN7)   \
   || ((mux) == HAL_PLAY_IN8)   \
   || ((mux) == HAL_PLAY_IN9)   \
   || ((mux) == HAL_PLAY_IN10)  \
   || ((mux) == HAL_PLAY_IN11)  \
   || ((mux) == HAL_PLAY_IN12)  \
   || ((mux) == HAL_PLAY_IN13)  \
   || ((mux) == HAL_PLAY_IN14)  \
   || ((mux) == HAL_PLAY_IN15))

/**
  * @brief Verifies the value of input multiplexer source for PLAY1 instance.
  * @param  source Input signal (@ref hal_play_in_source_t).
  * @retval 1      source is a valid value.
  * @retval 0      source is an invalid value.
  */
#define IS_PLAY1_IN_SOURCE(source)                          \
  (((source) == HAL_PLAY1_IN_ADC1_AWD1_MUX7)                \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD1_MUX9)             \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD2_MUX8)             \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD1_MUX7)             \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD1_MUX11)            \
   || ((source) == HAL_PLAY1_IN_COMP1_OUT_MUX0)             \
   || ((source) == HAL_PLAY1_IN_COMP1_OUT_MUX1)             \
   || ((source) == HAL_PLAY1_IN_COMP2_OUT_MUX1)             \
   || ((source) == HAL_PLAY1_IN_COMP2_OUT_MUX15)            \
   || ((source) == HAL_PLAY1_IN_COMP3_OUT_MUX3)             \
   || ((source) == HAL_PLAY1_IN_COMP3_OUT_MUX5)             \
   || ((source) == HAL_PLAY1_IN_COMP4_OUT_MUX5)             \
   || ((source) == HAL_PLAY1_IN_COMP5_OUT_MUX7)             \
   || ((source) == HAL_PLAY1_IN_COMP6_OUT_MUX9)             \
   || ((source) == HAL_PLAY1_IN_COMP7_OUT_MUX11)            \
   || ((source) == HAL_PLAY1_IN_COMP8_OUT_MUX13)            \
   || ((source) == HAL_PLAY1_IN_EVENTOUT_MUX0)              \
   || ((source) == HAL_PLAY1_IN_HRTIM1_ADC_TRG1_MUX1)       \
   || ((source) == HAL_PLAY1_IN_HRTIM1_ADC_TRG2_MUX2)       \
   || ((source) == HAL_PLAY1_IN_HRTIM1_CHA1_MUX10)          \
   || ((source) == HAL_PLAY1_IN_HRTIM1_CHB1_MUX11)          \
   || ((source) == HAL_PLAY1_IN_HRTIM1_CHC1_MUX12)          \
   || ((source) == HAL_PLAY1_IN_HRTIM1_CHD1_MUX13)          \
   || ((source) == HAL_PLAY1_IN_HRTIM1_CHE1_MUX14)          \
   || ((source) == HAL_PLAY1_IN_HRTIM1_CHF1_MUX15)          \
   || ((source) == HAL_PLAY1_IN_HRTIM1_DAC_RESET_TRG1_MUX0) \
   || ((source) == HAL_PLAY1_IN_HRTIM1_DAC_STEP_TRG1_MUX4)  \
   || ((source) == HAL_PLAY1_IN_HRTIM1_OUT_SYNC2_MUX5)      \
   || ((source) == HAL_PLAY1_IN_LOCKUP_MUX12)               \
   || ((source) == HAL_PLAY1_IN_LOCKUP_MUX15)               \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH1_MUX3)            \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH1_MUX11)           \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH2_MUX4)            \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH2_MUX12)           \
   || ((source) == HAL_PLAY1_IN_MCO1_MUX6)                  \
   || ((source) == HAL_PLAY1_IN_MCO2_MUX4)                  \
   || ((source) == HAL_PLAY1_IN_NMI_MUX11)                  \
   || ((source) == HAL_PLAY1_IN_NMI_MUX13)                  \
   || ((source) == HAL_PLAY1_IN_IN0_MUX0)                   \
   || ((source) == HAL_PLAY1_IN_IN1_MUX1)                   \
   || ((source) == HAL_PLAY1_IN_IN2_MUX2)                   \
   || ((source) == HAL_PLAY1_IN_IN3_MUX3)                   \
   || ((source) == HAL_PLAY1_IN_IN4_MUX4)                   \
   || ((source) == HAL_PLAY1_IN_IN5_MUX5)                   \
   || ((source) == HAL_PLAY1_IN_IN6_MUX6)                   \
   || ((source) == HAL_PLAY1_IN_IN7_MUX7)                   \
   || ((source) == HAL_PLAY1_IN_IN8_MUX8)                   \
   || ((source) == HAL_PLAY1_IN_IN9_MUX9)                   \
   || ((source) == HAL_PLAY1_IN_IN10_MUX10)                 \
   || ((source) == HAL_PLAY1_IN_IN11_MUX11)                 \
   || ((source) == HAL_PLAY1_IN_IN12_MUX12)                 \
   || ((source) == HAL_PLAY1_IN_IN13_MUX13)                 \
   || ((source) == HAL_PLAY1_IN_IN14_MUX14)                 \
   || ((source) == HAL_PLAY1_IN_IN15_MUX15)                 \
   || ((source) == HAL_PLAY1_IN_SPI1_MOSI_MUX6)             \
   || ((source) == HAL_PLAY1_IN_SPI1_MOSI_MUX14)            \
   || ((source) == HAL_PLAY1_IN_SPI1_NSS_MUX5)              \
   || ((source) == HAL_PLAY1_IN_SPI1_NSS_MUX13)             \
   || ((source) == HAL_PLAY1_IN_SPI1_SCLK_MUX7)             \
   || ((source) == HAL_PLAY1_IN_SPI1_SCLK_MUX15)            \
   || ((source) == HAL_PLAY1_IN_SPI2_MOSI_MUX2)             \
   || ((source) == HAL_PLAY1_IN_SPI2_MOSI_MUX10)            \
   || ((source) == HAL_PLAY1_IN_SPI2_NSS_MUX1)              \
   || ((source) == HAL_PLAY1_IN_SPI2_NSS_MUX9)              \
   || ((source) == HAL_PLAY1_IN_SPI2_SCLK_MUX3)             \
   || ((source) == HAL_PLAY1_IN_SPI2_SCLK_MUX11)            \
   || ((source) == HAL_PLAY1_IN_TIM1_OC1_MUX6)              \
   || ((source) == HAL_PLAY1_IN_TIM1_OC5_MUX9)              \
   || ((source) == HAL_PLAY1_IN_TIM1_OC6_MUX10)             \
   || ((source) == HAL_PLAY1_IN_TIM1_TRGO_CKTIM_MUX8)       \
   || ((source) == HAL_PLAY1_IN_TIM2_OC3_MUX1)              \
   || ((source) == HAL_PLAY1_IN_TIM2_OC4_MUX2)              \
   || ((source) == HAL_PLAY1_IN_TIM2_TRGO_CKTIM_MUX0)       \
   || ((source) == HAL_PLAY1_IN_TIM3_OC3_MUX1)              \
   || ((source) == HAL_PLAY1_IN_TIM3_OC3_MUX5)              \
   || ((source) == HAL_PLAY1_IN_TIM3_OC4_MUX2)              \
   || ((source) == HAL_PLAY1_IN_TIM3_OC4_MUX6)              \
   || ((source) == HAL_PLAY1_IN_TIM3_TRGO_CKTIM_MUX0)       \
   || ((source) == HAL_PLAY1_IN_TIM3_TRGO_CKTIM_MUX4)       \
   || ((source) == HAL_PLAY1_IN_TIM4_OC4_MUX8)              \
   || ((source) == HAL_PLAY1_IN_TIM4_TRGO_CKTIM_MUX7)       \
   || ((source) == HAL_PLAY1_IN_TIM6_TRGO_CKTIM_MUX7)       \
   || ((source) == HAL_PLAY1_IN_TIM8_OC1_MUX10)             \
   || ((source) == HAL_PLAY1_IN_TIM8_OC5_MUX13)             \
   || ((source) == HAL_PLAY1_IN_TIM8_OC6_MUX14)             \
   || ((source) == HAL_PLAY1_IN_TIM8_TRGO_CKTIM_MUX12)      \
   || ((source) == HAL_PLAY1_IN_TIM9_TRGO_CKTIM_MUX0)       \
   || ((source) == HAL_PLAY1_IN_TIM10_OC1_MUX12)            \
   || ((source) == HAL_PLAY1_IN_TIM12_TRGO_CKTIM_MUX10)     \
   || ((source) == HAL_PLAY1_IN_TIM15_OC2_MUX6)             \
   || ((source) == HAL_PLAY1_IN_TIM15_TRGO_CKTIM_MUX15)     \
   || ((source) == HAL_PLAY1_IN_TIM20_OC1_MUX8)             \
   || ((source) == HAL_PLAY1_IN_TIM20_OC5_MUX3)             \
   || ((source) == HAL_PLAY1_IN_TIM20_OC6_MUX4)             \
   || ((source) == HAL_PLAY1_IN_TIM20_TRGO_CKTIM_MUX2)      \
   || ((source) == HAL_PLAY1_IN_USART1_CK_MUX10)            \
   || ((source) == HAL_PLAY1_IN_USART1_CK_MUX12)            \
   || ((source) == HAL_PLAY1_IN_USART1_TX_OUT_MUX9)         \
   || ((source) == HAL_PLAY1_IN_USART1_TX_OUT_MUX11)        \
   || ((source) == HAL_PLAY1_IN_USART2_CK_MUX14)            \
   || ((source) == HAL_PLAY1_IN_USART2_TX_OUT_MUX13))

/**
  * @brief Verifies the value of input multiplexer source.
  * @param  instance PLAYx instance (@ref hal_play_t).
  * @param  source   Input signal (@ref hal_play_in_source_t).
  * @retval 1        source is a valid value.
  * @retval 0        source is an invalid value.
  */
#define IS_PLAY_IN_SOURCE(instance, source)                                            \
  ((((hal_play_t)((uint32_t)(instance)) == HAL_PLAY1) && IS_PLAY1_IN_SOURCE((source))))

/**
  * @brief Verifies the Look-Up Table of PLAY1 instance.
  * @param  lut Look-Up Table (@ref hal_play_lut_t).
  * @retval 1   lut is a valid value.
  * @retval 0   lut is an invalid value.
  */
#define IS_PLAY1_LUT(lut)        \
  (((lut) == HAL_PLAY_LUT0)      \
   || ((lut) == HAL_PLAY_LUT1)   \
   || ((lut) == HAL_PLAY_LUT2)   \
   || ((lut) == HAL_PLAY_LUT3)   \
   || ((lut) == HAL_PLAY_LUT4)   \
   || ((lut) == HAL_PLAY_LUT5)   \
   || ((lut) == HAL_PLAY_LUT6)   \
   || ((lut) == HAL_PLAY_LUT7)   \
   || ((lut) == HAL_PLAY_LUT8)   \
   || ((lut) == HAL_PLAY_LUT9)   \
   || ((lut) == HAL_PLAY_LUT10)  \
   || ((lut) == HAL_PLAY_LUT11)  \
   || ((lut) == HAL_PLAY_LUT12)  \
   || ((lut) == HAL_PLAY_LUT13)  \
   || ((lut) == HAL_PLAY_LUT14)  \
   || ((lut) == HAL_PLAY_LUT15))

/**
  * @brief Verifies the Look-Up Table.
  * @param  instance PLAYx instance (@ref hal_play_t).
  * @param  lut      Look-Up Table (@ref hal_play_lut_t).
  * @retval 1        lut is a valid value.
  * @retval 0        lut is an invalid value.
  */
#define IS_PLAY_LUT(instance, lut)                                          \
  ((((hal_play_t)((uint32_t)(instance)) == HAL_PLAY1) && IS_PLAY1_LUT(lut)))

/**
  * @brief Verifies the lookup table input.
  * @param  lut_input Lookup table input.
  * @retval 1         lut_input is a valid value.
  * @retval 0         lut_input is an invalid value.
  */
#define IS_PLAY_LUT_INPUT(lut_input)       \
  (((lut_input) == HAL_PLAY_LUT_INPUT0)    \
   || ((lut_input) == HAL_PLAY_LUT_INPUT1) \
   || ((lut_input) == HAL_PLAY_LUT_INPUT2) \
   || ((lut_input) == HAL_PLAY_LUT_INPUT3))

/**
  * @brief Verifies the "LUT registered output" input source of a look-up table for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT_OUT_REGISTERED(input_source) \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_REGISTERED)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT2_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT3_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT6_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT7_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_REGISTERED)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT10_OUT_REGISTERED)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT11_OUT_REGISTERED)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_REGISTERED)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_REGISTERED)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT14_OUT_REGISTERED)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT15_OUT_REGISTERED))

/**
  * @brief Verifies the "Input Multiplexer" input source of a look-up table.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY_LUT_INPUT_SOURCE_FILTER(input_source)  \
  (((input_source) == HAL_PLAY_LUT_INPUT_FILTER0)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER1)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER2)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER3)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER4)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER5)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER6)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER7)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER8)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER9)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER10)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER11)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER12)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER13)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER14)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_FILTER15))

/**
  * @brief Verifies the "SW Trigger" input source of a look-up table.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY_LUT_INPUT_SOURCE_SWTRIG(input_source)  \
  (((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG0)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG1)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG2)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG3)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG4)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG5)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG6)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG7)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG8)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG9)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG10)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG11)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG12)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG13)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG14)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_SWTRIG15))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 0 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT0(input_source)       \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 1 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT1(input_source)           \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 2 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT2(input_source)           \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT2_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 3 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT3(input_source)           \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT2_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT3_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT6_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT10_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT14_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 4 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT4(input_source)       \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 5 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT5(input_source)           \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 6 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT6(input_source)           \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT6_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 7 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT7(input_source)           \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT2_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT6_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT7_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT10_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT14_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 8 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT8(input_source)       \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 9 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT9(input_source)           \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 10 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT10(input_source)          \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT10_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 11 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT11(input_source)          \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT2_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT6_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT10_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT11_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT14_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 12 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT12(input_source)       \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 13 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT13(input_source)          \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 14 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT14(input_source)          \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT14_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 15 for PLAY1 instance.
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT15(input_source)          \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT)      \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT1_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT2_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT5_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT6_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT9_OUT_DIRECT)   \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT10_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT13_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT14_OUT_DIRECT)  \
   || ((input_source) == HAL_PLAY_LUT_INPUT_LUT15_OUT_DIRECT))

/**
  * @brief Verifies the input source of a look-up table for PLAY1 instance.
  * @param  lut          Look-Up Table (@ref hal_play_lut_t).
  * @param  input_source Input signal value (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE(lut, input_source)                                \
  ((IS_PLAY1_LUT_INPUT_SOURCE_LUT_OUT_REGISTERED(input_source))                     \
   || (IS_PLAY_LUT_INPUT_SOURCE_FILTER(input_source))                               \
   || (IS_PLAY_LUT_INPUT_SOURCE_SWTRIG(input_source))                               \
   || (((lut) == HAL_PLAY_LUT0) && IS_PLAY1_LUT_INPUT_SOURCE_LUT0(input_source))    \
   || (((lut) == HAL_PLAY_LUT1) && IS_PLAY1_LUT_INPUT_SOURCE_LUT1(input_source))    \
   || (((lut) == HAL_PLAY_LUT2) && IS_PLAY1_LUT_INPUT_SOURCE_LUT2(input_source))    \
   || (((lut) == HAL_PLAY_LUT3) && IS_PLAY1_LUT_INPUT_SOURCE_LUT3(input_source))    \
   || (((lut) == HAL_PLAY_LUT4) && IS_PLAY1_LUT_INPUT_SOURCE_LUT4(input_source))    \
   || (((lut) == HAL_PLAY_LUT5) && IS_PLAY1_LUT_INPUT_SOURCE_LUT5(input_source))    \
   || (((lut) == HAL_PLAY_LUT6) && IS_PLAY1_LUT_INPUT_SOURCE_LUT6(input_source))    \
   || (((lut) == HAL_PLAY_LUT7) && IS_PLAY1_LUT_INPUT_SOURCE_LUT7(input_source))    \
   || (((lut) == HAL_PLAY_LUT8) && IS_PLAY1_LUT_INPUT_SOURCE_LUT8(input_source))    \
   || (((lut) == HAL_PLAY_LUT9) && IS_PLAY1_LUT_INPUT_SOURCE_LUT9(input_source))    \
   || (((lut) == HAL_PLAY_LUT10) && IS_PLAY1_LUT_INPUT_SOURCE_LUT10(input_source))  \
   || (((lut) == HAL_PLAY_LUT11) && IS_PLAY1_LUT_INPUT_SOURCE_LUT11(input_source))  \
   || (((lut) == HAL_PLAY_LUT12) && IS_PLAY1_LUT_INPUT_SOURCE_LUT12(input_source))  \
   || (((lut) == HAL_PLAY_LUT13) && IS_PLAY1_LUT_INPUT_SOURCE_LUT13(input_source))  \
   || (((lut) == HAL_PLAY_LUT14) && IS_PLAY1_LUT_INPUT_SOURCE_LUT14(input_source))  \
   || (((lut) == HAL_PLAY_LUT15) && IS_PLAY1_LUT_INPUT_SOURCE_LUT15(input_source)))

/**
  * @brief Verifies the input source of a look-up table.
  * @param  instance     PLAYx instance (@ref hal_play_t).
  * @param  lut          Look-Up Table (@ref hal_play_lut_t).
  * @param  input_source Value of input input_source (@ref hal_play_lut_input_source_t).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY_LUT_INPUT_SOURCE(instance, lut, input_source)                                           \
  ((((hal_play_t)((uint32_t)(instance)) == HAL_PLAY1) && IS_PLAY1_LUT_INPUT_SOURCE(lut, input_source)))

/**
  * @brief Verifies the signal source as Clock Gate for PLAY1 instance.
  * @param  source Signal source (@ref hal_play_lut_clk_gate_source_t).
  * @retval 1      source is a valid value.
  * @retval 0      source is an invalid value.
  */
#define IS_PLAY1_LUT_CLOCK_GATE_SOURCE(source)                 \
  (((source) == HAL_PLAY_LUT_CLK_GATE_OFF)                     \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_ON)                   \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SW_ACK)               \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT0_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT1_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT2_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT3_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT4_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT5_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT6_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT7_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT8_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT9_OUT_REGISTERED)  \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT10_OUT_REGISTERED) \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT11_OUT_REGISTERED) \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT12_OUT_REGISTERED) \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT13_OUT_REGISTERED) \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT14_OUT_REGISTERED) \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_LUT15_OUT_REGISTERED) \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER0)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER1)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER2)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER3)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER4)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER5)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER6)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER7)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER8)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER9)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER10)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER11)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER12)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER13)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER14)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_FILTER15)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG0)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG1)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG2)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG3)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG4)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG5)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG6)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG7)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG8)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG9)              \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG10)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG11)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG12)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG13)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG14)             \
   || ((source) == HAL_PLAY_LUT_CLK_GATE_SWTRIG15))

/**
  * @brief Verifies the Clock Gate value.
  * @param  instance PLAYx instance (@ref hal_play_t).
  * @param  source   Signal source for Clock Gate.
  * @retval 1        source is a valid value.
  * @retval 0        source is an invalid value.
  */
#define IS_PLAY_LUT_CLOCK_GATE_SOURCE(instance, source)                                            \
  (((((hal_play_t)((uint32_t)(instance)) == HAL_PLAY1)) && IS_PLAY1_LUT_CLOCK_GATE_SOURCE(source)))

/**
  * @brief Verifies the lookup table value.
  * @param  lut   Value of lookup table.
  * @retval 1     lut is a valid value.
  * @retval 0     lut is an invalid value.
  */
#define IS_PLAY_LUT_TRUTH_TABLE_VALUE(lut)  ((lut) <= (HAL_PLAY_LUT_TRUTH_TABLE_VALUE_MAX))

/**
  * @brief Verifies the Output Multiplexer.
  * @param  mux Output Multiplexer (@ref hal_play_out_t).
  * @retval 1   mux is a valid value.
  * @retval 0   mux is an invalid value.
  */
#define IS_PLAY_OUT(mux)         \
  (((mux) == HAL_PLAY_OUT0)      \
   || ((mux) == HAL_PLAY_OUT1)   \
   || ((mux) == HAL_PLAY_OUT2)   \
   || ((mux) == HAL_PLAY_OUT3)   \
   || ((mux) == HAL_PLAY_OUT4)   \
   || ((mux) == HAL_PLAY_OUT5)   \
   || ((mux) == HAL_PLAY_OUT6)   \
   || ((mux) == HAL_PLAY_OUT7)   \
   || ((mux) == HAL_PLAY_OUT8)   \
   || ((mux) == HAL_PLAY_OUT9)   \
   || ((mux) == HAL_PLAY_OUT10)  \
   || ((mux) == HAL_PLAY_OUT11)  \
   || ((mux) == HAL_PLAY_OUT12)  \
   || ((mux) == HAL_PLAY_OUT13)  \
   || ((mux) == HAL_PLAY_OUT14)  \
   || ((mux) == HAL_PLAY_OUT15))

/**
  * @brief Verifies the Output Multiplexer source for PLAY1 instance.
  * @param  source Value of output source.
  * @retval 1      source is a valid value.
  * @retval 0      source is an invalid value.
  */
#define IS_PLAY1_OUT_SOURCE(source)                          \
  (((source) == (uint32_t)HAL_PLAY_LUT0_OUT_DIRECT)          \
   || ((source) == (uint32_t)HAL_PLAY_LUT1_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT2_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT3_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT4_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT5_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT6_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT7_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT8_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT9_OUT_DIRECT)       \
   || ((source) == (uint32_t)HAL_PLAY_LUT10_OUT_DIRECT)      \
   || ((source) == (uint32_t)HAL_PLAY_LUT11_OUT_DIRECT)      \
   || ((source) == (uint32_t)HAL_PLAY_LUT12_OUT_DIRECT)      \
   || ((source) == (uint32_t)HAL_PLAY_LUT13_OUT_DIRECT)      \
   || ((source) == (uint32_t)HAL_PLAY_LUT14_OUT_DIRECT)      \
   || ((source) == (uint32_t)HAL_PLAY_LUT15_OUT_DIRECT)      \
   || ((source) == (uint32_t)HAL_PLAY_LUT0_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT1_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT2_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT3_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT4_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT5_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT6_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT7_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT8_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT9_OUT_REGISTERED)   \
   || ((source) == (uint32_t)HAL_PLAY_LUT10_OUT_REGISTERED)  \
   || ((source) == (uint32_t)HAL_PLAY_LUT11_OUT_REGISTERED)  \
   || ((source) == (uint32_t)HAL_PLAY_LUT12_OUT_REGISTERED)  \
   || ((source) == (uint32_t)HAL_PLAY_LUT13_OUT_REGISTERED)  \
   || ((source) == (uint32_t)HAL_PLAY_LUT14_OUT_REGISTERED)  \
   || ((source) == (uint32_t)HAL_PLAY_LUT15_OUT_REGISTERED))

/**
  * @brief Verifies the Output Multiplexer source.
  * @param  instance PLAYx instance (@ref hal_play_t).
  * @param  source   Value of output source.
  * @retval 1        source is a valid value.
  * @retval 0        source is an invalid value.
  */
#define IS_PLAY_OUT_SOURCE(instance, source)                                          \
  ((((hal_play_t)((uint32_t)(instance)) == HAL_PLAY1) && IS_PLAY1_OUT_SOURCE(source)))

/**
  * @brief Verifies the polling mode.
  * @param  mode Value of mode (@ref hal_play_edge_detection_mode_t).
  * @retval 1    mode is a valid value.
  * @retval 0    mode is an invalid value.
  */
#define IS_PLAY_POLL_MODE(mode)                  \
  (((mode) == HAL_PLAY_POLLING_FOR_ALL_EDGES)    \
   || ((mode) == HAL_PLAY_POLLING_FOR_ANY_EDGE))

/**
  * @brief Verifies the Software Trigger state value.
  * @param  state Value of state (@ref hal_play_sw_trigger_state_t).
  * @retval 1     state is a valid value.
  * @retval 0     state is an invalid value.
  */
#define IS_PLAY_SWTRIGGER_STATE(state)      \
  (((state) == HAL_PLAY_SW_TRIGGER_RESET)   \
   || ((state) == HAL_PLAY_SW_TRIGGER_SET))

/**
  * @brief Verifies the Software Trigger.
  * @param  swtrig Software Trigger.
  * @retval 1      swtrig is a valid value.
  * @retval 0      swtrig is an invalid value.
  */
#define IS_PLAY_SWTRIGGER(swtrig)      \
  (((swtrig) == HAL_PLAY_SWTRIG0)      \
   || ((swtrig) == HAL_PLAY_SWTRIG1)   \
   || ((swtrig) == HAL_PLAY_SWTRIG2)   \
   || ((swtrig) == HAL_PLAY_SWTRIG3)   \
   || ((swtrig) == HAL_PLAY_SWTRIG4)   \
   || ((swtrig) == HAL_PLAY_SWTRIG5)   \
   || ((swtrig) == HAL_PLAY_SWTRIG6)   \
   || ((swtrig) == HAL_PLAY_SWTRIG7)   \
   || ((swtrig) == HAL_PLAY_SWTRIG8)   \
   || ((swtrig) == HAL_PLAY_SWTRIG9)   \
   || ((swtrig) == HAL_PLAY_SWTRIG10)  \
   || ((swtrig) == HAL_PLAY_SWTRIG11)  \
   || ((swtrig) == HAL_PLAY_SWTRIG12)  \
   || ((swtrig) == HAL_PLAY_SWTRIG13)  \
   || ((swtrig) == HAL_PLAY_SWTRIG14)  \
   || ((swtrig) == HAL_PLAY_SWTRIG15))

/**
  * @brief Verifies the Software Trigger mask.
  * @param  swtrig_msk Software Trigger mask.
  * @retval 1      swtrig is a valid value.
  * @retval 0      swtrig is an invalid value.
  */
#define IS_PLAY_SWTRIGGER_MSK(swtrig_msk) \
  ((((uint32_t)(swtrig_msk) & HAL_PLAY_SWTRIG_ALL) != 0x00U)      \
   && (((uint32_t)(swtrig_msk) & ~HAL_PLAY_SWTRIG_ALL) == 0x00U))

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief Verifies the security access level attribute for item.
  * @param  attribute Security attribute.
  * @retval 1         attribute is a valid value.
  * @retval 0         attribute is an invalid value.
  */
#define IS_PLAY_ITEM_SEC_ATTR(attribute) ((attribute == HAL_PLAY_SEC) || (attribute == HAL_PLAY_NSEC))
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief Verifies the privilege access level attribute for item.
  * @param  attribute Privilege attribute.
  * @retval 1         attribute is a valid value.
  * @retval 0         attribute is an invalid value.
  */
#define IS_PLAY_ITEM_PRIV_ATTR(attribute) ((attribute == HAL_PLAY_PRIV) || (attribute == HAL_PLAY_NPRIV))

/**
  * @brief Verifies the PLAY security item.
  * @param  item PLAY item.
  * @retval 1    item is a valid value.
  * @retval 0    item is an invalid value.
  */
#define IS_PLAY_SEC_ITEM(item) (((item) == HAL_PLAY_SEC_ITEM_CONFIG) || ((item) == HAL_PLAY_SEC_ITEM_ALL))

/**
  * @brief Verifies the PLAY privileged item.
  * @param  item PLAY item.
  * @retval 1    item is a valid value.
  * @retval 0    item is an invalid value.
  */
#define IS_PLAY_PRIV_ITEM(item) (((item) == HAL_PLAY_PRIV_ITEM_CONFIG) || ((item) == HAL_PLAY_PRIV_ITEM_ALL))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup PLAY_Private_Functions  PLAY Private Functions
  * @{
  */

static hal_status_t PLAY_LUT_SetEdgeTrigger(const hal_play_handle_t *hplay,
                                            const hal_play_edge_trigger_config_t *p_config,
                                            uint32_t timeout_ms);

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PLAY_Exported_Functions
  * @{
  */

/** @addtogroup PLAY_Exported_Functions_Group1
  * @{
A set of functions allowing to initialize and deinitialize the PLAYx peripheral:
 - HAL_PLAY_Init()   Initialize the selected device with the PLAY instance.
 - HAL_PLAY_DeInit() De-initialize the selected PLAYx peripheral and reset the handle and status flags.
 - HAL_PLAY_GetInstance() Return the PLAY instance from the handle.
 - HAL_PLAY_GetLLInstance() Return the LL PLAY instance from the handle.
  */

/**
  * @brief  Initialize the PLAY according to the associated handle.
  * @param  hplay    Pointer to a @ref hal_play_handle_t.
  * @param  instance HAL PLAY instance.
  * @retval HAL_OK            PLAY instance has been correctly initialized.
  * @retval HAL_INVALID_PARAM PLAY handle is NULL.
  */
hal_status_t HAL_PLAY_Init(hal_play_handle_t *hplay, hal_play_t instance)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE((PLAY_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hplay == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hplay->instance = instance;

#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
  /* Register the default callback functions */
  hplay->p_sw_trigger_write_cplt_cb   = HAL_PLAY_SWTriggerWriteCpltCallback;
  hplay->p_edge_trigger_write_cplt_cb = HAL_PLAY_EdgeTriggerWriteCpltCallback;
  hplay->p_lut_output_rising_cb       = HAL_PLAY_LUTOutputRisingCallback;
  hplay->p_lut_output_falling_cb      = HAL_PLAY_LUTOutputFallingCallback;
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */

#if defined (USE_HAL_PLAY_USER_DATA) && (USE_HAL_PLAY_USER_DATA == 1)
  hplay->p_user_data = (void *)NULL;
#endif /* USE_HAL_PLAY_USER_DATA */

#if defined(USE_HAL_PLAY_CLK_ENABLE_MODEL) && (USE_HAL_PLAY_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HAL_RCC_PLAY1_EnableClock();
#endif /* USE_HAL_PLAY_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

  hplay->global_state = HAL_PLAY_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief DeInitialize the PLAY peripheral.
  * @param hplay Pointer to a @ref hal_play_handle_t.
  * @note  HAL_PLAY_DeInit does not reset all PLAY registers.
  *        The Application must call RCC API to force the reset of all PLAY registers.
  */
void HAL_PLAY_DeInit(hal_play_handle_t *hplay)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE(PLAY_GET_INSTANCE(hplay)));

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Clear only interrupts & flags. The rest of configuration must be reset by the application */
  LL_PLAY_LUT_DisableIT(p_playx, LL_PLAY_LUT_ALL_OUT_REGISTERED | LL_PLAY_LUT_ALL_OUT_DIRECT);
  LL_PLAY_LUT_DisableIT_EdgeTriggerWriteComplete(p_playx);
  LL_PLAY_LUT_ClearFlag(p_playx, LL_PLAY_LUT_ALL_OUT_REGISTERED | LL_PLAY_LUT_ALL_OUT_DIRECT);
  LL_PLAY_LUT_ClearFlag_EdgeTriggerWriteComplete(p_playx);
  LL_PLAY_DisableIT_SWTriggerWriteComplete(p_playx);
  LL_PLAY_ClearFlag_SWTriggerWriteComplete(p_playx);

  LL_PLAY_Unlock(p_playx);

  hplay->global_state = HAL_PLAY_STATE_RESET;
}

/**
  * @brief  Return the HAL PLAY instance from the handle.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @return PLAY instance.
  */
hal_play_t HAL_PLAY_GetInstance(const hal_play_handle_t *hplay)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE(PLAY_GET_INSTANCE(hplay)));

  return hplay->instance;
}

/**
  * @brief  Return the LL PLAY instance from the handle.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @return Pointer to PLAY_TypeDef instance.
  */
PLAY_TypeDef *HAL_PLAY_GetLLInstance(const hal_play_handle_t *hplay)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE(PLAY_GET_INSTANCE(hplay)));

  return PLAY_GET_INSTANCE(hplay);
}

/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group2
  * @{
A set of functions allowing to configure the PLAYx peripheral:

- Global configuration:
  - HAL_PLAY_INPUT_SetConfig()
  - HAL_PLAY_INPUT_GetConfig()
  - HAL_PLAY_LUT_SetConfig()
  - HAL_PLAY_LUT_GetConfig()
  - HAL_PLAY_OUTPUT_SetConfig()
  - HAL_PLAY_OUTPUT_GetConfig()

- Unitary configuration:
  - HAL_PLAY_INPUT_SetSource()
  - HAL_PLAY_INPUT_GetSource()
  - HAL_PLAY_INPUT_SetMinPulseWidth()
  - HAL_PLAY_INPUT_GetMinPulseWidth()
  - HAL_PLAY_INPUT_SetEdgeDetectionMode()
  - HAL_PLAY_INPUT_GetEdgeDetectionMode()
  - HAL_PLAY_LUT_SetTruthTable()
  - HAL_PLAY_LUT_GetTruthTable()
  - HAL_PLAY_LUT_SetSource()
  - HAL_PLAY_LUT_GetSource()
  - HAL_PLAY_LUT_SetClockGateSource()
  - HAL_PLAY_LUT_GetClockGateSource()
  - HAL_PLAY_OUTPUT_SetSource()
  - HAL_PLAY_OUTPUT_GetSource()
  */

/* PLAY Configuration functions ***********************************************/
/**
  * @brief  Configure multiple input multiplexers for the PLAY peripheral.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_config   Pointer to an array of @ref hal_play_in_config_t.
  * @param  array_size Number of configurations in the array.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  */
hal_status_t HAL_PLAY_INPUT_SetConfig(const hal_play_handle_t *hplay, const hal_play_in_config_t *p_config,
                                      uint32_t array_size)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((array_size > 0U) && (array_size <= PLAY_INPUT_MUX_NBR(p_playx))));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT | (uint32_t)HAL_PLAY_STATE_IDLE));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL) || (array_size == 0U) || (array_size > PLAY_INPUT_MUX_NBR(p_playx)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Unlock the configuration if not already done */
  is_locked = LL_PLAY_IsLocked(p_playx);
  if (is_locked != 0U)
  {
    LL_PLAY_Unlock(p_playx);
  }

  /* Write the configurations */
  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    ASSERT_DBG_PARAM(IS_PLAY_MIN_PULSE_WIDTH(p_config[idx].min_pulse_width));
    ASSERT_DBG_PARAM(IS_PLAY_EDGE_DETECTION_MODE(p_config[idx].mode));
    ASSERT_DBG_PARAM(IS_PLAY_IN_SOURCE(p_playx, p_config[idx].source));

    uint32_t premuxsel_value =
      ((uint32_t)p_config[idx].source & PLAY_IN_MUX_VALUE_MASK) >> PLAY_IN_MUX_VALUE_POS;
    uint32_t input_mux = ((uint32_t)p_config[idx].source & PLAY_IN_MUX_MASK) >> HAL_PLAY_IN_MUX_POS;

    LL_PLAY_INPUT_Config(p_playx, input_mux, premuxsel_value,
                         (uint32_t)p_config[idx].mode, p_config[idx].min_pulse_width);
  }

  return HAL_OK;
}

/**
  * @brief Retrieve the input multiplexer configurations of the PLAY peripheral in order from 0 to (array_size - 1),
  *        where array_size specifies the number of configurations.
  * @param hplay      Pointer to a @ref hal_play_handle_t.
  * @param p_config   Pointer to an array of @ref hal_play_in_config_t to be filled.
  * @param array_size Number of configurations in the array.
  */
void HAL_PLAY_INPUT_GetConfig(const hal_play_handle_t *hplay, hal_play_in_config_t *p_config, uint32_t array_size)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((array_size > 0U) && (array_size <= PLAY_INPUT_MUX_NBR(p_playx))));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  /* Rebuild the input source signal */
  uint32_t instance_id = (uint32_t)PLAY_GET_INSTANCE_ID(hplay);
  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    uint32_t mux_sel = (uint32_t)idx << HAL_PLAY_IN_MUX_POS;
    uint32_t source = LL_PLAY_INPUT_GetSource(p_playx, (uint32_t)idx);

    uint32_t in_source = (instance_id | mux_sel | source);

    p_config[idx].source = (hal_play_in_source_t)in_source;
    p_config[idx].min_pulse_width = LL_PLAY_INPUT_GetMinimumPulseWidth(p_playx, idx);
    p_config[idx].mode = (hal_play_edge_detection_mode_t)LL_PLAY_INPUT_GetEdgeDetectionMode(p_playx, idx);
  }
}

/**
  * @brief  Configure multiple lookup tables for the PLAY peripheral.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_config   Pointer to an array of @ref hal_play_lut_config_t.
  * @param  array_size Number of configurations in the array.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  */
hal_status_t HAL_PLAY_LUT_SetConfig(const hal_play_handle_t *hplay, const hal_play_lut_config_t *p_config,
                                    uint32_t array_size)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((array_size > 0U) && (array_size <= PLAY_LUT_NBR(p_playx))));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT | (uint32_t)HAL_PLAY_STATE_IDLE));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL) || (array_size == 0U) || (array_size > PLAY_LUT_NBR(p_playx)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Unlock the configuration if not already done */
  is_locked = LL_PLAY_IsLocked(p_playx);
  if (is_locked != 0U)
  {
    LL_PLAY_Unlock(p_playx);
  }

  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    ASSERT_DBG_PARAM(IS_PLAY_LUT(p_playx, p_config[idx].lut));
    ASSERT_DBG_PARAM(IS_PLAY_LUT_TRUTH_TABLE_VALUE(p_config[idx].truth_table));
    ASSERT_DBG_PARAM(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                              p_config[idx].input_source[LL_PLAY_LUT_INPUT0]));
    ASSERT_DBG_PARAM(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                              p_config[idx].input_source[LL_PLAY_LUT_INPUT1]));
    ASSERT_DBG_PARAM(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                              p_config[idx].input_source[LL_PLAY_LUT_INPUT2]));
    ASSERT_DBG_PARAM(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                              p_config[idx].input_source[LL_PLAY_LUT_INPUT3]));
    ASSERT_DBG_PARAM(IS_PLAY_LUT_CLOCK_GATE_SOURCE(p_playx, p_config[idx].clk_gate_source));

    LL_PLAY_LUT_SetTruthTable(p_playx, (uint32_t)p_config[idx].lut, p_config[idx].truth_table);
    LL_PLAY_LUT_ConfigInputs(p_playx, (uint32_t)p_config[idx].lut,
                             (uint32_t)p_config[idx].input_source[LL_PLAY_LUT_INPUT0],
                             (uint32_t)p_config[idx].input_source[LL_PLAY_LUT_INPUT1],
                             (uint32_t)p_config[idx].input_source[LL_PLAY_LUT_INPUT2],
                             (uint32_t)p_config[idx].input_source[LL_PLAY_LUT_INPUT3],
                             (uint32_t)p_config[idx].clk_gate_source);
  }

  return HAL_OK;
}

/**
  * @brief Retrieve the lookup table configurations of the PLAY peripheral in order from 0 to (array_size - 1),
  *        where array_size specifies the number of configurations.
  * @param hplay      Pointer to a @ref hal_play_handle_t.
  * @param p_config   Pointer to an array of @ref hal_play_lut_config_t to be filled.
  * @param array_size Number of configurations in the array.
  */
void HAL_PLAY_LUT_GetConfig(const hal_play_handle_t *hplay, hal_play_lut_config_t *p_config, uint32_t array_size)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((array_size > 0U) && (array_size <= PLAY_LUT_NBR(p_playx))));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    p_config[idx].lut = (hal_play_lut_t)idx;
    p_config[idx].truth_table = LL_PLAY_LUT_GetTruthTable(p_playx, idx);
    p_config[idx].clk_gate_source = (hal_play_lut_clk_gate_source_t)LL_PLAY_LUT_GetClockGate(p_playx, idx);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT0] =
      (hal_play_lut_input_source_t)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT0);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT1] =
      (hal_play_lut_input_source_t)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT1);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT2] =
      (hal_play_lut_input_source_t)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT2);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT3] =
      (hal_play_lut_input_source_t)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT3);
  }
}

/**
  * @brief  Configure a set of output multiplexers for the PLAY peripheral.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_config   Pointer to an array of @ref hal_play_out_config_t.
  * @param  array_size Number of configurations in the array.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  */
hal_status_t HAL_PLAY_OUTPUT_SetConfig(hal_play_handle_t *hplay, const hal_play_out_config_t *p_config,
                                       uint32_t array_size)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((array_size > 0U) && (array_size <= PLAY_OUTPUT_MUX_NBR(p_playx))));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT | (uint32_t)HAL_PLAY_STATE_IDLE));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL) || (array_size == 0U) || (array_size > PLAY_OUTPUT_MUX_NBR(p_playx)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Unlock the configuration if not already done */
  is_locked = LL_PLAY_IsLocked(p_playx);
  if (is_locked != 0U)
  {
    LL_PLAY_Unlock(p_playx);
  }

  /* Configure the Logic Array Output */
  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    ASSERT_DBG_PARAM(IS_PLAY_OUT(p_config[idx].output_mux));
    ASSERT_DBG_PARAM(IS_PLAY_OUT_SOURCE(p_playx, p_config[idx].lut_output));

    LL_PLAY_OUTPUT_SetSource(p_playx, (uint32_t)p_config[idx].output_mux, (uint32_t)p_config[idx].lut_output);
  }

  hplay->global_state = HAL_PLAY_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Retrieve the output multiplexer configurations of the PLAY peripheral in order from 0 to (array_size - 1),
  *        where array_size specifies the number of configurations.
  * @param hplay      Pointer to a @ref hal_play_handle_t.
  * @param p_config   Pointer to an array of @ref hal_play_out_t to be filled.
  * @param array_size Number of configurations in the array.
  */
void HAL_PLAY_OUTPUT_GetConfig(const hal_play_handle_t *hplay, hal_play_out_config_t *p_config, uint32_t array_size)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((array_size > 0U) && (array_size <= PLAY_OUTPUT_MUX_NBR(p_playx))));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    p_config[idx].output_mux = (hal_play_out_t)idx;
    p_config[idx].lut_output = LL_PLAY_OUTPUT_GetSource(p_playx, idx);
  }
}

/* PLAY Configuration - Unitary functions ***************************************/

/**
  * @brief  Set the signal source for an input multiplexer of the PLAY peripheral.
  * @param  hplay  Pointer to a @ref hal_play_handle_t.
  * @param  source Input source signal.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_INPUT_SetSource(const hal_play_handle_t *hplay, hal_play_in_source_t source)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_IN_SOURCE(p_playx, source));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_IDLE));

  uint32_t src_u32 = (uint32_t)source;

  /* Retrieve the input mux */
  uint32_t input_mux = (src_u32 & PLAY_IN_MUX_MASK) >> HAL_PLAY_IN_MUX_POS;
  uint32_t mux_sel = src_u32 & PLAY_IN_MUX_VALUE_MASK;

  LL_PLAY_INPUT_SetSource(p_playx, input_mux, mux_sel);

  return HAL_OK;
}

/**
  * @brief  Retrieve the signal source for an input multiplexer of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref hal_play_handle_t.
  * @param  input_mux Input multiplexer.
  * @return Input source signal.
  */
hal_play_in_source_t HAL_PLAY_INPUT_GetSource(const hal_play_handle_t *hplay, hal_play_in_t input_mux)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_IN(input_mux));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  /* Rebuild the source signal */
  uint32_t instance_id = (uint32_t)PLAY_GET_INSTANCE_ID(hplay);
  uint32_t mux_sel = (uint32_t)input_mux << HAL_PLAY_IN_MUX_POS;
  uint32_t source = LL_PLAY_INPUT_GetSource(p_playx, (uint32_t)input_mux);

  uint32_t ret = (instance_id | mux_sel | source);

  return (hal_play_in_source_t)ret;
}

/**
  * @brief  Set the minimum pulse width for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref hal_play_handle_t.
  * @param  input_mux Input multiplexer.
  * @param  width     Pulse width in play_clk clock cycles, in range [0..255].
  *                   Value 0 means that the filter is bypassed.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_INPUT_SetMinPulseWidth(const hal_play_handle_t *hplay, hal_play_in_t input_mux, uint32_t width)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_IN(input_mux));
  ASSERT_DBG_PARAM(IS_PLAY_MIN_PULSE_WIDTH(width));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_IDLE));

  LL_PLAY_INPUT_SetMinimumPulseWidth(p_playx, (uint32_t)input_mux, width);

  return HAL_OK;
}

/**
  * @brief  Retrieve the minimum pulse width configured for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref hal_play_handle_t.
  * @param  input_mux Input multiplexer.
  * @return Pulse width in play_clk clock cycles, in range [0..255]. Value 0 means that the filter is bypassed.
  */
uint32_t HAL_PLAY_INPUT_GetMinPulseWidth(const hal_play_handle_t *hplay, hal_play_in_t input_mux)
{
  const PLAY_TypeDef *p_playx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_IN(input_mux));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return LL_PLAY_INPUT_GetMinimumPulseWidth(p_playx, (uint32_t)input_mux);
}

/**
  * @brief  Configure the edge detection mode for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref hal_play_handle_t.
  * @param  input_mux Input multiplexer.
  * @param  mode      Mode of Edge Detection.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_INPUT_SetEdgeDetectionMode(const hal_play_handle_t *hplay, hal_play_in_t input_mux,
                                                 hal_play_edge_detection_mode_t mode)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_IN(input_mux));
  ASSERT_DBG_PARAM(IS_PLAY_EDGE_DETECTION_MODE(mode));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_IDLE));

  LL_PLAY_INPUT_SetEdgeDetectionMode(p_playx, (uint32_t)input_mux, (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Retrieve the edge detection mode configured for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref hal_play_handle_t.
  * @param  input_mux Input multiplexer.
  * @return Edge Detection mode.
  */
hal_play_edge_detection_mode_t HAL_PLAY_INPUT_GetEdgeDetectionMode(const hal_play_handle_t *hplay,
                                                                   hal_play_in_t input_mux)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_IN(input_mux));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return (hal_play_edge_detection_mode_t)LL_PLAY_INPUT_GetEdgeDetectionMode(p_playx, (uint32_t)input_mux);
}

/* PLAY Configuration - Unitary functions for lookup table *********************/

/**
  * @brief  Set the truth table value for a lookup table in the PLAY peripheral.
  * @param  hplay             Pointer to a @ref hal_play_handle_t.
  * @param  lut               Lookup table.
  * @param  truth_table_value The value can be in range [0..0xFFFF].
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_LUT_SetTruthTable(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                        uint32_t truth_table_value)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_LUT(p_playx, lut));
  ASSERT_DBG_PARAM(IS_PLAY_LUT_TRUTH_TABLE_VALUE(truth_table_value));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_IDLE));

  LL_PLAY_LUT_SetTruthTable(p_playx, (uint32_t)lut, truth_table_value);

  return HAL_OK;
}

/**
  * @brief  Retrieve the truth table value for a lookup table in the PLAY peripheral.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @param  lut   Lookup table.
  * @return Value in range [0..0xFFFF].
  */
uint32_t HAL_PLAY_LUT_GetTruthTable(const hal_play_handle_t *hplay, hal_play_lut_t lut)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_LUT(hplay->instance, lut));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return LL_PLAY_LUT_GetTruthTable(PLAY_GET_INSTANCE(hplay), (uint32_t)lut);
}

/**
  * @brief  Set the signal source for a lookup table input in the PLAY peripheral.
  * @param  hplay        Pointer to a @ref hal_play_handle_t.
  * @param  lut          Lookup table.
  * @param  lut_input    Lookup table Input.
  * @param  input_source Signal source.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_LUT_SetSource(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                    hal_play_lut_input_t lut_input, hal_play_lut_input_source_t input_source)
{
  PLAY_TypeDef *p_playx;
  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_LUT(p_playx, lut));
  ASSERT_DBG_PARAM(IS_PLAY_LUT_INPUT(lut_input));
  ASSERT_DBG_PARAM(IS_PLAY_LUT_INPUT_SOURCE(p_playx, lut, input_source));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_IDLE));

  LL_PLAY_LUT_SetSource(p_playx, (uint32_t)lut, (uint32_t)lut_input, (uint32_t)input_source);

  return HAL_OK;
}

/**
  * @brief  Retrieve the signal source for a lookup table input in the PLAY peripheral.
  * @param  hplay     Pointer to a @ref hal_play_handle_t.
  * @param  lut       Lookup table.
  * @param  lut_input Lookup table Input.
  * @return Lookup table input source.
  */
hal_play_lut_input_source_t HAL_PLAY_LUT_GetSource(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                                   hal_play_lut_input_t lut_input)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);
  ASSERT_DBG_PARAM(IS_PLAY_LUT(p_playx, lut));
  ASSERT_DBG_PARAM(IS_PLAY_LUT_INPUT(lut_input));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return (hal_play_lut_input_source_t)LL_PLAY_LUT_GetSource(p_playx, (uint32_t)lut, (uint32_t)lut_input);
}

/**
  * @brief  Set the clock gate source for a lookup table in the PLAY peripheral.
  * @param  hplay  Pointer to a @ref hal_play_handle_t.
  * @param  lut    Lookup table.
  * @param  source Signal source.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_LUT_SetClockGateSource(const hal_play_handle_t *hplay, hal_play_lut_t lut,
                                             hal_play_lut_clk_gate_source_t source)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_LUT(p_playx, lut));
  ASSERT_DBG_PARAM(IS_PLAY_LUT_CLOCK_GATE_SOURCE(p_playx, source));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_IDLE));

  LL_PLAY_LUT_SetClockGate(p_playx, (uint32_t)lut, (uint32_t)source);

  return HAL_OK;
}

/**
  * @brief  Retrieve the clock gate source for a lookup table in the PLAY peripheral.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @param  lut   Lookup table.
  * @return Lookup table clock gate source.
  */
hal_play_lut_clk_gate_source_t HAL_PLAY_LUT_GetClockGateSource(const hal_play_handle_t *hplay, hal_play_lut_t lut)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_LUT(p_playx, lut));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return (hal_play_lut_clk_gate_source_t)LL_PLAY_LUT_GetClockGate(p_playx, (uint32_t)lut);
}

/* PLAY Configuration - Unitary functions for output ****************************/

/**
  * @brief  Set the source signal for an output multiplexer of the PLAY peripheral.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  output_mux Output multiplexer.
  * @param  source     Lookup table output. This parameter can be one of the following values:
  *                    @arg @ref HAL_PLAY_LUT0_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT1_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT2_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT3_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT4_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT5_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT6_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT7_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT8_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT9_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT10_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT11_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT12_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT13_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT14_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT15_OUT_DIRECT
  *                    @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED
  *                    @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_OUTPUT_SetSource(const hal_play_handle_t *hplay, hal_play_out_t output_mux,
                                       uint32_t source)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_OUT(output_mux));
  ASSERT_DBG_PARAM(IS_PLAY_OUT_SOURCE(p_playx, source));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_IDLE));

  LL_PLAY_OUTPUT_SetSource(p_playx, (uint32_t)output_mux, source);

  return HAL_OK;
}

/**
  * @brief  Retrieve the source signal configured for an output multiplexer of the PLAY peripheral.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  output_mux Output multiplexer.
  * @return Returned value can be one of the following values:
  *         @arg @ref HAL_PLAY_LUT0_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT1_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT2_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT3_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT4_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT5_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT6_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT7_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT8_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT9_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT10_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT11_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT12_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT13_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT14_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT15_OUT_DIRECT
  *         @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED
  *         @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED
  */
uint32_t HAL_PLAY_OUTPUT_GetSource(const hal_play_handle_t *hplay, hal_play_out_t output_mux)
{
  const PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_OUT(output_mux));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return LL_PLAY_OUTPUT_GetSource(p_playx, (uint32_t)output_mux);
}

/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group3
  * @{
A set of functions allowing to start/stop the PLAYx peripheral:
- HAL_PLAY_Start()
- HAL_PLAY_Stop()
  */

/**
  * @brief  Start the PLAY peripheral.
  * @param  hplay    Pointer to a @ref hal_play_handle_t.
  * @param  p_config Pointer to a @ref hal_play_edge_trigger_config_t structure for the Edge Triggers configuration.
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_BUSY          Current global state does not allow to start the peripheral.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_PLAY_Start(hal_play_handle_t *hplay, const hal_play_edge_trigger_config_t *p_config)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM((p_config->lut_out_falling_mask & p_config->lut_out_rising_mask) == 0U);

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_IDLE));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hplay, global_state, (uint32_t)HAL_PLAY_STATE_IDLE, HAL_PLAY_STATE_ACTIVE);

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Lock the configuration only if it is currently unlocked.
     In context where configuration register requires a privilege and/or secure write access:
     - this check prevents generating an unexpected illegal access (ilac) event if the caller does not have
       the required permissions.
    - if the configuration is unlocked and the caller lacks write access, attempting to lock will fail and
      generate an expected illegal access (ilac) event.
  */
  is_locked = LL_PLAY_IsLocked(p_playx);
  if (is_locked == 0U)
  {
    LL_PLAY_Lock(p_playx);
  }

  return PLAY_LUT_SetEdgeTrigger(hplay, p_config, PLAY_WRITE_TIMEOUT_MS);
}

/**
  * @brief  Stop the PLAY peripheral.
  *         The API disables all the lookup table output Interrupts and unlocks the configuration registers.
  *         All features having a dependency with the kernel clock are held in reset.
  * @param  hplay  Pointer to a @ref hal_play_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_Stop(hal_play_handle_t *hplay)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_ACTIVE);

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Disable all lookup table Output Interrupts */
  LL_PLAY_LUT_DisableIT(p_playx, LL_PLAY_LUT_ALL_OUT_REGISTERED | LL_PLAY_LUT_ALL_OUT_DIRECT);

  LL_PLAY_Unlock(p_playx);

  hplay->global_state = HAL_PLAY_STATE_IDLE;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group4
  * @{
A set of functions allowing to manage the lookup table Output of PLAYx peripheral:
- HAL_PLAY_LUT_SetEdgeTrigger()
- HAL_PLAY_LUT_SetEdgeTrigger_IT()
- HAL_PLAY_LUT_GetEdgeTrigger()
- HAL_PLAY_LUT_PollForEdgeTrigger()
- HAL_PLAY_LUT_EnableIT()
- HAL_PLAY_LUT_DisableIT()
- HAL_PLAY_LUT_GetIT()
  */

/**
  * @brief  Configure the Edge Triggers: flag transition of lookup table outputs.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_config   Pointer to a @ref hal_play_edge_trigger_config_t structure for the Edge Triggers configuration.
  * @param  timeout_ms Timeout duration (in ms).
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          A write is pending.
  */
hal_status_t HAL_PLAY_LUT_SetEdgeTrigger(const hal_play_handle_t *hplay, const hal_play_edge_trigger_config_t *p_config,
                                         uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM((p_config->lut_out_falling_mask & p_config->lut_out_rising_mask) == 0U);

  ASSERT_DBG_STATE(hplay->global_state, HAL_PLAY_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return PLAY_LUT_SetEdgeTrigger(hplay, p_config, timeout_ms);
}

/**
  * @brief  Configure the Edge Triggers in interrupt mode: flag transition of lookup table outputs.
  * @param  hplay    Pointer to a @ref hal_play_handle_t.
  * @param  p_config Pointer to a @ref hal_play_edge_trigger_config_t structure for the Edge Triggers configuration.
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  * @retval HAL_BUSY          A write is pending.
  */
hal_status_t HAL_PLAY_LUT_SetEdgeTrigger_IT(const hal_play_handle_t *hplay,
                                            const hal_play_edge_trigger_config_t *p_config)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM((p_config->lut_out_falling_mask & p_config->lut_out_rising_mask) == 0U);

  ASSERT_DBG_STATE(hplay->global_state, HAL_PLAY_STATE_ACTIVE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Check if a write access is available */
  if (LL_PLAY_LUT_IsEdgeTriggerWriteBusy(p_playx) != 0U)
  {
    return HAL_BUSY;
  }

  LL_PLAY_LUT_EnableIT_EdgeTriggerWriteComplete(p_playx);

  /* Update Transition */
  LL_PLAY_LUT_SetEdgeTrigger(p_playx, p_config->lut_out_falling_mask, p_config->lut_out_rising_mask);

  return HAL_OK;
}

/**
  * @brief  Get the Edge Triggers configuration of all lookup table outputs.
  * @param  hplay    Pointer to a @ref hal_play_handle_t.
  * @param  p_config Pointer to a @ref hal_play_edge_trigger_config_t structure to be filled.
  */
void HAL_PLAY_LUT_GetEdgeTrigger(const hal_play_handle_t *hplay, hal_play_edge_trigger_config_t *p_config)
{
  uint32_t valid_mask;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  /* Retrieve the configuration */
  valid_mask = (uint32_t)(LL_PLAY_LUT_ALL_OUT_DIRECT | LL_PLAY_LUT_ALL_OUT_REGISTERED);

  p_config->lut_out_rising_mask = (uint32_t)(LL_PLAY_LUT_GetEdgeTrigger(PLAY_GET_INSTANCE(hplay)) & valid_mask);
  p_config->lut_out_falling_mask = (uint32_t)(valid_mask & (~p_config->lut_out_rising_mask));
}

/**
  * @brief  Poll on Lookup table Output Flags.
  * @param  hplay                   Pointer to a @ref hal_play_handle_t.
  * @param  poll_mode               Polling mode of type @ref hal_play_polling_edge_trigger_t.
  * @param  edge_trig_mask          Mask of flags to poll.
  *                                 This parameter can be a combination of the following values:
  *                                 @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :        The flag of LUT0 direct output
  *                                 @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :        The flag of LUT1 direct output
  *                                 @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :        The flag of LUT2 direct output
  *                                 @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :        The flag of LUT3 direct output
  *                                 @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :        The flag of LUT4 direct output
  *                                 @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :        The flag of LUT5 direct output
  *                                 @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :        The flag of LUT6 direct output
  *                                 @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :        The flag of LUT7 direct output
  *                                 @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :        The flag of LUT8 direct output
  *                                 @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :        The flag of LUT9 direct output
  *                                 @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :       The flag of LUT10 direct output
  *                                 @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :       The flag of LUT11 direct output
  *                                 @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :       The flag of LUT12 direct output
  *                                 @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :       The flag of LUT13 direct output
  *                                 @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :       The flag of LUT14 direct output
  *                                 @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :       The flag of LUT15 direct output
  *                                 @arg @ref HAL_PLAY_LUT_ALL_OUT_DIRECT :     All flags of LUTs direct outputs
  *                                 @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :    The flag of LUT0 registered output
  *                                 @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :    The flag of LUT1 registered output
  *                                 @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :    The flag of LUT2 registered output
  *                                 @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :    The flag of LUT3 registered output
  *                                 @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :    The flag of LUT4 registered output
  *                                 @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :    The flag of LUT5 registered output
  *                                 @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :    The flag of LUT6 registered output
  *                                 @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :    The flag of LUT7 registered output
  *                                 @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :    The flag of LUT8 registered output
  *                                 @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :    The flag of LUT9 registered output
  *                                 @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED :   The flag of LUT10 registered output
  *                                 @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED :   The flag of LUT11 registered output
  *                                 @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED :   The flag of LUT12 registered output
  *                                 @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED :   The flag of LUT13 registered output
  *                                 @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED :   The flag of LUT14 registered output
  *                                 @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED :   The flag of LUT15 registered output
  *                                 @arg @ref HAL_PLAY_LUT_ALL_OUT_REGISTERED : All flags of LUTs registered outputs
  * @param  timeout_ms              Timeout duration (in ms).
  * @param  p_edge_trig_mask_status Pointer to return the triggered lookup table output flags.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_TIMEOUT       Operation timed out.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_PLAY_LUT_PollForEdgeTrigger(const hal_play_handle_t *hplay, hal_play_polling_edge_trigger_t poll_mode,
                                             uint32_t edge_trig_mask, uint32_t *p_edge_trig_mask_status,
                                             uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;
  uint32_t tickstart;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_POLL_MODE(poll_mode));
  ASSERT_DBG_PARAM((edge_trig_mask != 0U));
  ASSERT_DBG_PARAM((p_edge_trig_mask_status != NULL));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)(HAL_PLAY_STATE_ACTIVE));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_edge_trig_mask_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Get tick count */
  tickstart = HAL_GetTick();

  /* Check selected event flag */
  *p_edge_trig_mask_status = 0U;
  do
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        /* Before returning timeout, re-check if p_edge_trig_mask_status is still 0 */
        if (*p_edge_trig_mask_status == 0U)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    uint32_t current_flag_status = LL_PLAY_LUT_GetFlags(p_playx) & edge_trig_mask;
    if (poll_mode == HAL_PLAY_POLLING_FOR_ANY_EDGE)
    {
      *p_edge_trig_mask_status = current_flag_status;
    }
    else
    {
      *p_edge_trig_mask_status = (((current_flag_status & edge_trig_mask) == edge_trig_mask) ?
                                  current_flag_status : 0U);
    }
  } while (*p_edge_trig_mask_status == 0U);

  /* Clear flags triggered */
  LL_PLAY_LUT_ClearFlag(p_playx, edge_trig_mask);

  return HAL_OK;
}

/**
  * @brief  Enable a set of lookup table output interrupts.
  * @param  hplay    Pointer to a @ref hal_play_handle_t.
  * @param  its_mask Mask of lookup table output interrupt to enable.
  *                  This parameter can be a combination of the following values:
  *                  @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :        The interrupt of LUT0 direct output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :        The interrupt of LUT1 direct output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :        The interrupt of LUT2 direct output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :        The interrupt of LUT3 direct output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :        The interrupt of LUT4 direct output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :        The interrupt of LUT5 direct output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :        The interrupt of LUT6 direct output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :        The interrupt of LUT7 direct output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :        The interrupt of LUT8 direct output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :        The interrupt of LUT9 direct output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :       The interrupt of LUT10 direct output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :       The interrupt of LUT11 direct output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :       The interrupt of LUT12 direct output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :       The interrupt of LUT13 direct output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :       The interrupt of LUT14 direct output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :       The interrupt of LUT15 direct output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_DIRECT :     All interrupts of LUTs direct outputs
  *                  @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :    The interrupt of LUT0 registered output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :    The interrupt of LUT1 registered output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :    The interrupt of LUT2 registered output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :    The interrupt of LUT3 registered output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :    The interrupt of LUT4 registered output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :    The interrupt of LUT5 registered output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :    The interrupt of LUT6 registered output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :    The interrupt of LUT7 registered output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :    The interrupt of LUT8 registered output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :    The interrupt of LUT9 registered output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED :   The interrupt of LUT10 registered output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED :   The interrupt of LUT11 registered output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED :   The interrupt of LUT12 registered output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED :   The interrupt of LUT13 registered output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED :   The interrupt of LUT14 registered output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED :   The interrupt of LUT15 registered output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_REGISTERED : All interrupts of LUTs registered outputs
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_LUT_EnableIT(const hal_play_handle_t *hplay, uint32_t its_mask)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((its_mask != 0U));

  ASSERT_DBG_STATE(hplay->global_state, HAL_PLAY_STATE_ACTIVE);

  LL_PLAY_LUT_EnableIT(PLAY_GET_INSTANCE(hplay), its_mask);

  return HAL_OK;
}

/**
  * @brief  Disable a set of lookup table output Interrupts.
  * @param  hplay    Pointer to a @ref hal_play_handle_t.
  * @param  its_mask Mask of lookup table output interrupt to disable
  *                  This parameter can be a combination of the following values:
  *                  @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :        The interrupt of LUT0 direct output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :        The interrupt of LUT1 direct output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :        The interrupt of LUT2 direct output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :        The interrupt of LUT3 direct output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :        The interrupt of LUT4 direct output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :        The interrupt of LUT5 direct output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :        The interrupt of LUT6 direct output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :        The interrupt of LUT7 direct output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :        The interrupt of LUT8 direct output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :        The interrupt of LUT9 direct output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :       The interrupt of LUT10 direct output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :       The interrupt of LUT11 direct output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :       The interrupt of LUT12 direct output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :       The interrupt of LUT13 direct output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :       The interrupt of LUT14 direct output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :       The interrupt of LUT15 direct output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_DIRECT :     All interrupts of LUTs direct outputs
  *                  @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :    The interrupt of LUT0 registered output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :    The interrupt of LUT1 registered output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :    The interrupt of LUT2 registered output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :    The interrupt of LUT3 registered output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :    The interrupt of LUT4 registered output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :    The interrupt of LUT5 registered output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :    The interrupt of LUT6 registered output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :    The interrupt of LUT7 registered output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :    The interrupt of LUT8 registered output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :    The interrupt of LUT9 registered output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED :   The interrupt of LUT10 registered output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED :   The interrupt of LUT11 registered output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED :   The interrupt of LUT12 registered output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED :   The interrupt of LUT13 registered output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED :   The interrupt of LUT14 registered output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED :   The interrupt of LUT15 registered output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_REGISTERED : All interrupts of LUTs registered outputs
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_PLAY_LUT_DisableIT(const hal_play_handle_t *hplay, uint32_t its_mask)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((its_mask != 0U));

  ASSERT_DBG_STATE(hplay->global_state, HAL_PLAY_STATE_ACTIVE);

  LL_PLAY_LUT_DisableIT(PLAY_GET_INSTANCE(hplay), its_mask);

  return HAL_OK;
}

/**
  * @brief  Get the enabled lookup table output interrupts.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @return Mask of enabled lookup table output interrupts.
  *         This returned parameter can be a combination of the following values:
  *         @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :      The interrupt of LUT0 direct output
  *         @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :      The interrupt of LUT1 direct output
  *         @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :      The interrupt of LUT2 direct output
  *         @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :      The interrupt of LUT3 direct output
  *         @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :      The interrupt of LUT4 direct output
  *         @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :      The interrupt of LUT5 direct output
  *         @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :      The interrupt of LUT6 direct output
  *         @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :      The interrupt of LUT7 direct output
  *         @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :      The interrupt of LUT8 direct output
  *         @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :      The interrupt of LUT9 direct output
  *         @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :     The interrupt of LUT10 direct output
  *         @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :     The interrupt of LUT11 direct output
  *         @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :     The interrupt of LUT12 direct output
  *         @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :     The interrupt of LUT13 direct output
  *         @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :     The interrupt of LUT14 direct output
  *         @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :     The interrupt of LUT15 direct output
  *         @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :  The interrupt of LUT0 registered output
  *         @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :  The interrupt of LUT1 registered output
  *         @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :  The interrupt of LUT2 registered output
  *         @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :  The interrupt of LUT3 registered output
  *         @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :  The interrupt of LUT4 registered output
  *         @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :  The interrupt of LUT5 registered output
  *         @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :  The interrupt of LUT6 registered output
  *         @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :  The interrupt of LUT7 registered output
  *         @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :  The interrupt of LUT8 registered output
  *         @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :  The interrupt of LUT9 registered output
  *         @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED : The interrupt of LUT10 registered output
  *         @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED : The interrupt of LUT11 registered output
  *         @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED : The interrupt of LUT12 registered output
  *         @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED : The interrupt of LUT13 registered output
  *         @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED : The interrupt of LUT14 registered output
  *         @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED : The interrupt of LUT15 registered output
  */
uint32_t HAL_PLAY_LUT_GetIT(const hal_play_handle_t *hplay)
{
  ASSERT_DBG_PARAM((hplay != NULL));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return LL_PLAY_LUT_GetIT(PLAY_GET_INSTANCE(hplay));
}

/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group5
  * @{
A set of functions allowing to manage the Software Triggers:
- HAL_PLAY_WriteSWTrigger()
- HAL_PLAY_WriteSWTrigger_IT()
- HAL_PLAY_ToggleSWTrigger()
- HAL_PLAY_ToggleSWTrigger_IT()
- HAL_PLAY_ReadSWTrigger()
  */

/**
  * @brief  Set the Software Trigger states in polling mode.
  * @param  hplay       Pointer to a @ref hal_play_handle_t.
  * @param  sw_triggers Mask of Software Trigger.
  *                     This parameter can be a combination of the following values:
  *                     @arg @ref HAL_PLAY_SWTRIG0 :    Software trigger 0
  *                     @arg @ref HAL_PLAY_SWTRIG1 :    Software trigger 1
  *                     @arg @ref HAL_PLAY_SWTRIG2 :    Software trigger 2
  *                     @arg @ref HAL_PLAY_SWTRIG3 :    Software trigger 3
  *                     @arg @ref HAL_PLAY_SWTRIG4 :    Software trigger 4
  *                     @arg @ref HAL_PLAY_SWTRIG5 :    Software trigger 5
  *                     @arg @ref HAL_PLAY_SWTRIG6 :    Software trigger 6
  *                     @arg @ref HAL_PLAY_SWTRIG7 :    Software trigger 7
  *                     @arg @ref HAL_PLAY_SWTRIG8 :    Software trigger 8
  *                     @arg @ref HAL_PLAY_SWTRIG9 :    Software trigger 9
  *                     @arg @ref HAL_PLAY_SWTRIG10 :   Software trigger 10
  *                     @arg @ref HAL_PLAY_SWTRIG11 :   Software trigger 11
  *                     @arg @ref HAL_PLAY_SWTRIG12 :   Software trigger 12
  *                     @arg @ref HAL_PLAY_SWTRIG13 :   Software trigger 13
  *                     @arg @ref HAL_PLAY_SWTRIG14 :   Software trigger 14
  *                     @arg @ref HAL_PLAY_SWTRIG15 :   Software trigger 15
  *                     @arg @ref HAL_PLAY_SWTRIG_ALL : All software triggers
  * @param  state       State to set of type @ref hal_play_sw_trigger_state_t.
  * @param  timeout_ms  Timeout duration (in ms).
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_BUSY    A write is pending.
  * @retval HAL_TIMEOUT Timeout reached.
  */
hal_status_t HAL_PLAY_WriteSWTrigger(const hal_play_handle_t *hplay, uint32_t sw_triggers,
                                     hal_play_sw_trigger_state_t state, uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_SWTRIGGER_MSK(sw_triggers));
  ASSERT_DBG_PARAM(IS_PLAY_SWTRIGGER_STATE(state));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_ACTIVE);

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Check if a write access is available */
  if (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
  {
    return HAL_BUSY;
  }

  /* Set selected Software Triggers */
  if (state == HAL_PLAY_SW_TRIGGER_RESET)
  {
    LL_PLAY_ResetSWTrigger(p_playx, sw_triggers);
  }
  else
  {
    LL_PLAY_SetSWTrigger(p_playx, sw_triggers);
  }

  /* Wait until the write is completed */
  /* The Software Trigger write complete flag cannot be checked here because it is available only in interrupt mode */
  uint32_t tick_start = HAL_GetTick();
  while (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tick_start) > timeout_ms) || (timeout_ms == 0U))
      {
        /* Before returning timeout, re-check if the flag has cleared */
        if (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Set the Software Trigger states in interrupt Mode.
  * @param  hplay       Pointer to a @ref hal_play_handle_t.
  * @param  sw_triggers Mask of Software Triggers.
  *                     This parameter can be a combination of the following values:
  *                     @arg @ref HAL_PLAY_SWTRIG0 :    Software trigger 0
  *                     @arg @ref HAL_PLAY_SWTRIG1 :    Software trigger 1
  *                     @arg @ref HAL_PLAY_SWTRIG2 :    Software trigger 2
  *                     @arg @ref HAL_PLAY_SWTRIG3 :    Software trigger 3
  *                     @arg @ref HAL_PLAY_SWTRIG4 :    Software trigger 4
  *                     @arg @ref HAL_PLAY_SWTRIG5 :    Software trigger 5
  *                     @arg @ref HAL_PLAY_SWTRIG6 :    Software trigger 6
  *                     @arg @ref HAL_PLAY_SWTRIG7 :    Software trigger 7
  *                     @arg @ref HAL_PLAY_SWTRIG8 :    Software trigger 8
  *                     @arg @ref HAL_PLAY_SWTRIG9 :    Software trigger 9
  *                     @arg @ref HAL_PLAY_SWTRIG10 :   Software trigger 10
  *                     @arg @ref HAL_PLAY_SWTRIG11 :   Software trigger 11
  *                     @arg @ref HAL_PLAY_SWTRIG12 :   Software trigger 12
  *                     @arg @ref HAL_PLAY_SWTRIG13 :   Software trigger 13
  *                     @arg @ref HAL_PLAY_SWTRIG14 :   Software trigger 14
  *                     @arg @ref HAL_PLAY_SWTRIG15 :   Software trigger 15
  *                     @arg @ref HAL_PLAY_SWTRIG_ALL : All software triggers
  * @param  state       State to set of type @ref hal_play_sw_trigger_state_t.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_BUSY    A write is pending.
  */
hal_status_t HAL_PLAY_WriteSWTrigger_IT(const hal_play_handle_t *hplay, uint32_t sw_triggers,
                                        hal_play_sw_trigger_state_t state)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_SWTRIGGER_MSK(sw_triggers));
  ASSERT_DBG_PARAM(IS_PLAY_SWTRIGGER_STATE(state));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_ACTIVE);

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Check if a write access is available */
  if (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
  {
    return HAL_BUSY;
  }

  /* Enable Software Trigger write complete interrupt */
  LL_PLAY_EnableIT_SWTriggerWriteComplete(p_playx);

  /* Set selected Software Triggers */
  if (state == HAL_PLAY_SW_TRIGGER_RESET)
  {
    LL_PLAY_ResetSWTrigger(p_playx, sw_triggers);
  }
  else
  {
    LL_PLAY_SetSWTrigger(p_playx, sw_triggers);
  }

  return HAL_OK;
}

/**
  * @brief  Toggle the Software Trigger State in polling mode.
  * @param  hplay       Pointer to a @ref hal_play_handle_t.
  * @param  sw_triggers Mask of Software Triggers.
  *                     This parameter can be a combination of the following values:
  *                     @arg @ref HAL_PLAY_SWTRIG0 :    Software trigger 0
  *                     @arg @ref HAL_PLAY_SWTRIG1 :    Software trigger 1
  *                     @arg @ref HAL_PLAY_SWTRIG2 :    Software trigger 2
  *                     @arg @ref HAL_PLAY_SWTRIG3 :    Software trigger 3
  *                     @arg @ref HAL_PLAY_SWTRIG4 :    Software trigger 4
  *                     @arg @ref HAL_PLAY_SWTRIG5 :    Software trigger 5
  *                     @arg @ref HAL_PLAY_SWTRIG6 :    Software trigger 6
  *                     @arg @ref HAL_PLAY_SWTRIG7 :    Software trigger 7
  *                     @arg @ref HAL_PLAY_SWTRIG8 :    Software trigger 8
  *                     @arg @ref HAL_PLAY_SWTRIG9 :    Software trigger 9
  *                     @arg @ref HAL_PLAY_SWTRIG10 :   Software trigger 10
  *                     @arg @ref HAL_PLAY_SWTRIG11 :   Software trigger 11
  *                     @arg @ref HAL_PLAY_SWTRIG12 :   Software trigger 12
  *                     @arg @ref HAL_PLAY_SWTRIG13 :   Software trigger 13
  *                     @arg @ref HAL_PLAY_SWTRIG14 :   Software trigger 14
  *                     @arg @ref HAL_PLAY_SWTRIG15 :   Software trigger 15
  *                     @arg @ref HAL_PLAY_SWTRIG_ALL : All software triggers
  * @param  timeout_ms  Timeout duration (in ms).
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_BUSY    A write is pending.
  * @retval HAL_TIMEOUT Timeout reached.
  */
hal_status_t HAL_PLAY_ToggleSWTrigger(const hal_play_handle_t *hplay, uint32_t sw_triggers, uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_SWTRIGGER_MSK(sw_triggers));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_ACTIVE);

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Check if a write access is available */
  if (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
  {
    return HAL_BUSY;
  }

  /* Toggle the selected Software Triggers */
  LL_PLAY_ToggleSWTrigger(p_playx, sw_triggers);

  /* Wait until the write is completed */
  /* The Software Trigger write complete flag cannot be checked here because it is available only in interrupt mode */
  uint32_t tick_start = HAL_GetTick();
  while (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tick_start) > timeout_ms) || (timeout_ms == 0U))
      {
        /* Before returning timeout, re-check if the flag has cleared */
        if (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Toggle the Software Trigger State in interrupt Mode.
  * @param  hplay       Pointer to a @ref hal_play_handle_t.
  * @param  sw_triggers Mask of Software Triggers.
  *                     This parameter can be a combination of the following values:
  *                     @arg @ref HAL_PLAY_SWTRIG0 :    Software trigger 0
  *                     @arg @ref HAL_PLAY_SWTRIG1 :    Software trigger 1
  *                     @arg @ref HAL_PLAY_SWTRIG2 :    Software trigger 2
  *                     @arg @ref HAL_PLAY_SWTRIG3 :    Software trigger 3
  *                     @arg @ref HAL_PLAY_SWTRIG4 :    Software trigger 4
  *                     @arg @ref HAL_PLAY_SWTRIG5 :    Software trigger 5
  *                     @arg @ref HAL_PLAY_SWTRIG6 :    Software trigger 6
  *                     @arg @ref HAL_PLAY_SWTRIG7 :    Software trigger 7
  *                     @arg @ref HAL_PLAY_SWTRIG8 :    Software trigger 8
  *                     @arg @ref HAL_PLAY_SWTRIG9 :    Software trigger 9
  *                     @arg @ref HAL_PLAY_SWTRIG10 :   Software trigger 10
  *                     @arg @ref HAL_PLAY_SWTRIG11 :   Software trigger 11
  *                     @arg @ref HAL_PLAY_SWTRIG12 :   Software trigger 12
  *                     @arg @ref HAL_PLAY_SWTRIG13 :   Software trigger 13
  *                     @arg @ref HAL_PLAY_SWTRIG14 :   Software trigger 14
  *                     @arg @ref HAL_PLAY_SWTRIG15 :   Software trigger 15
  *                     @arg @ref HAL_PLAY_SWTRIG_ALL : All software triggers
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_BUSY    A write is pending.
  */
hal_status_t HAL_PLAY_ToggleSWTrigger_IT(const hal_play_handle_t *hplay, uint32_t sw_triggers)
{
  PLAY_TypeDef *p_playx;

  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_SWTRIGGER_MSK(sw_triggers));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_ACTIVE);

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Check if a write access is available */
  if (LL_PLAY_IsSWTriggerWriteBusy(p_playx) != 0U)
  {
    return HAL_BUSY;
  }

  LL_PLAY_EnableIT_SWTriggerWriteComplete(p_playx);

  LL_PLAY_ToggleSWTrigger(p_playx, sw_triggers);

  return HAL_OK;
}

/**
  * @brief  Read the State of a Software Trigger.
  * @param  hplay   Pointer to a @ref hal_play_handle_t.
  * @param  sw_trig Software Trigger.
  *                 This parameter can be one of the following values:
  *                 @arg @ref HAL_PLAY_SWTRIG0 :  Software trigger 0
  *                 @arg @ref HAL_PLAY_SWTRIG1 :  Software trigger 1
  *                 @arg @ref HAL_PLAY_SWTRIG2 :  Software trigger 2
  *                 @arg @ref HAL_PLAY_SWTRIG3 :  Software trigger 3
  *                 @arg @ref HAL_PLAY_SWTRIG4 :  Software trigger 4
  *                 @arg @ref HAL_PLAY_SWTRIG5 :  Software trigger 5
  *                 @arg @ref HAL_PLAY_SWTRIG6 :  Software trigger 6
  *                 @arg @ref HAL_PLAY_SWTRIG7 :  Software trigger 7
  *                 @arg @ref HAL_PLAY_SWTRIG8 :  Software trigger 8
  *                 @arg @ref HAL_PLAY_SWTRIG9 :  Software trigger 9
  *                 @arg @ref HAL_PLAY_SWTRIG10 : Software trigger 10
  *                 @arg @ref HAL_PLAY_SWTRIG11 : Software trigger 11
  *                 @arg @ref HAL_PLAY_SWTRIG12 : Software trigger 12
  *                 @arg @ref HAL_PLAY_SWTRIG13 : Software trigger 13
  *                 @arg @ref HAL_PLAY_SWTRIG14 : Software trigger 14
  *                 @arg @ref HAL_PLAY_SWTRIG15 : Software trigger 15
  * @return State of Software Trigger.
  */
hal_play_sw_trigger_state_t HAL_PLAY_ReadSWTrigger(const hal_play_handle_t *hplay, uint32_t sw_trig)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM(IS_PLAY_SWTRIGGER(sw_trig));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return ((LL_PLAY_IsSWTriggerSet(PLAY_GET_INSTANCE(hplay), sw_trig) != 0U) ?
          HAL_PLAY_SW_TRIGGER_SET : HAL_PLAY_SW_TRIGGER_RESET);
}

/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group6
  * @{
A set of functions allowing to handle the PLAY interrupts in asynchronous mode.

- IRQ handler:
  - HAL_PLAY_IRQHandler()

- Callback functions:
  - Depending on the process function used, different callbacks might be triggered:

  | Process API \n \ \n Callbacks           | HAL_PLAY_WriteSWTrigger_IT() | HAL_PLAY_ToggleSWTrigger_IT() |
  |-----------------------------------------|:----------------------------:|:-----------------------------:|
  | HAL_PLAY_SWTriggerWriteCpltCallback()   |               x              |              x                |

  | Process API \n \ \n Callbacks           | HAL_PLAY_LUT_SetEdgeTrigger_IT() |
  |-----------------------------------------|:--------------------------------:|
  | HAL_PLAY_EdgeTriggerWriteCpltCallback() |                 x                |

- Additionally, the following callbacks are available for lookup table output flags if interrupts were enabled
  with @ref HAL_PLAY_LUT_EnableIT():
  - HAL_PLAY_LUTOutputRisingCallback(): When one of the lookup table output flags is triggered on a rising edge.
  - HAL_PLAY_LUTOutputFallingCallback(): When one of the lookup table output flags is triggered on a falling edge.

- Callback registering functions:
  - HAL_PLAY_RegisterSWTriggerWriteCpltCallback()
  - HAL_PLAY_RegisterEdgeTriggerWriteCpltCallback()
  - HAL_PLAY_RegisterLUTOutputRisingCallback()
  - HAL_PLAY_RegisterLUTOutputFallingCallback()
  */

/**
  * @brief Handle PLAY interrupt request.
  * @param hplay  Pointer to a @ref hal_play_handle_t.
  */
void HAL_PLAY_IRQHandler(hal_play_handle_t *hplay)
{
  PLAY_TypeDef *p_playx;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hplay != NULL));

  p_playx = PLAY_GET_INSTANCE(hplay);

  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE(p_playx));

  /* Get status of general interrupts */
  uint32_t reg_ier = LL_PLAY_READ_REG(p_playx, IER);
  uint32_t reg_isr = LL_PLAY_READ_REG(p_playx, ISR);
  uint32_t reg_misr = reg_ier & reg_isr;

  /**
    * Retrieve the status of lookup table output interrupts.
    * Reading only the ISR_FLAGS is not sufficient to indicate that an interrupt has occurred.
    * If the interrupt for a lookup table output is disabled and the flag is set,
    * the IRQ handler does not recognize it as the source of the interrupt.
    * To avoid this situation, a logical AND operation is performed between the FLIER and
    * FLSTAT registers to identify the actual interrupt flags.
    */
  uint32_t reg_flier = LL_PLAY_LUT_GetIT(p_playx);
  uint32_t reg_flstat = LL_PLAY_LUT_GetFlags(p_playx);
  uint32_t reg_flmisr = reg_flier & reg_flstat;

  /* Check SWTrigger write complete interrupt */
  if (STM32_IS_BIT_SET(reg_misr, PLAY_IT_STATUS_SW_TRIGGER_WRITE_COMPLETE))
  {
    LL_PLAY_ClearFlag_SWTriggerWriteComplete(p_playx);

    LL_PLAY_DisableIT_SWTriggerWriteComplete(p_playx);

    /* Call the callback */
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
    hplay->p_sw_trigger_write_cplt_cb(hplay);
#else
    HAL_PLAY_SWTriggerWriteCpltCallback(hplay);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
  }

  /* Check Edge Trigger write complete interrupt */
  if (STM32_IS_BIT_SET(reg_misr, PLAY_IT_STATUS_EDGE_TRIGGER_WRITE_COMPLETE))
  {
    LL_PLAY_LUT_ClearFlag_EdgeTriggerWriteComplete(p_playx);

    LL_PLAY_LUT_DisableIT_EdgeTriggerWriteComplete(p_playx);

    /* Call the callback */
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
    hplay->p_edge_trigger_write_cplt_cb(hplay);
#else
    HAL_PLAY_EdgeTriggerWriteCpltCallback(hplay);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
  }

  /* Check lookup table output interrupts */
  if (reg_flmisr > 0U)
  {
    LL_PLAY_LUT_ClearFlag(p_playx, reg_flmisr);

    /* Extract the status of Flags on rising and falling edges */
    uint32_t reg_edgetrig = LL_PLAY_LUT_GetEdgeTrigger(p_playx);
    uint32_t mask_flag_rising = reg_flmisr & reg_edgetrig;
    uint32_t mask_flag_falling = reg_flmisr & (~reg_edgetrig);

    if (mask_flag_rising > 0U)
    {
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
      hplay->p_lut_output_rising_cb(hplay, mask_flag_rising);
#else
      HAL_PLAY_LUTOutputRisingCallback(hplay, mask_flag_rising);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
    }

    if (mask_flag_falling > 0U)
    {
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
      hplay->p_lut_output_falling_cb(hplay, mask_flag_falling);
#else
      HAL_PLAY_LUTOutputFallingCallback(hplay, mask_flag_falling);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
    }

  }
}

/**
  * @brief   Callback for Software Trigger write complete.
  * @param   hplay Pointer to a @ref hal_play_handle_t.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_PLAY_SWTriggerWriteCpltCallback(hal_play_handle_t *hplay)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_PLAY_SWTriggerWriteCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief   Callback for Edge Trigger write complete.
  * @param   hplay Pointer to a @ref hal_play_handle_t.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_PLAY_EdgeTriggerWriteCpltCallback(hal_play_handle_t *hplay)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_PLAY_EdgeTriggerWriteCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief   Callback for lookup table output rising edge.
  * @param   hplay                 Pointer to a @ref hal_play_handle_t.
  * @param   edge_trig_mask_status Mask of lookup table output triggered on a rising edge.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_PLAY_LUTOutputRisingCallback(hal_play_handle_t *hplay, uint32_t edge_trig_mask_status)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);
  UNUSED(edge_trig_mask_status);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_PLAY_LUTOutputRisingCallback must be implemented in the user file.
   */
}

/**
  * @brief   Callback for lookup table output falling edge.
  * @param   hplay                 Pointer to a @ref hal_play_handle_t.
  * @param   edge_trig_mask_status Mask of lookup table output triggered on a falling edge
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_PLAY_LUTOutputFallingCallback(hal_play_handle_t *hplay, uint32_t edge_trig_mask_status)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);
  UNUSED(edge_trig_mask_status);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_PLAY_LUTOutputFallingCallback must be implemented in the user file.
   */
}

#if defined(USE_HAL_PLAY_REGISTER_CALLBACKS) && (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a user PLAY callback for Software Trigger write complete.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Registering completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_PLAY_RegisterSWTriggerWriteCpltCallback(hal_play_handle_t *hplay, hal_play_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_INIT | (uint32_t)HAL_PLAY_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hplay->p_sw_trigger_write_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user PLAY callback for Edge Trigger write complete.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Registering completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_PLAY_RegisterEdgeTriggerWriteCpltCallback(hal_play_handle_t *hplay, hal_play_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_INIT | (uint32_t)HAL_PLAY_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hplay->p_edge_trigger_write_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user PLAY callback for lookup table output rising.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Registering completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_PLAY_RegisterLUTOutputRisingCallback(hal_play_handle_t *hplay, hal_play_lut_output_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_INIT | (uint32_t)HAL_PLAY_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hplay->p_lut_output_rising_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a user PLAY callback for lookup table output falling.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_callback Pointer to the callback function.
  * @retval HAL_OK            Registering completed successfully.
  * @retval HAL_INVALID_PARAM p_callback pointer is NULL.
  */
hal_status_t HAL_PLAY_RegisterLUTOutputFallingCallback(hal_play_handle_t *hplay, hal_play_lut_output_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hplay != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));

  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)HAL_PLAY_STATE_INIT | (uint32_t)HAL_PLAY_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  /* Check the p_callback pointer */
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hplay->p_lut_output_falling_cb = p_callback;

  return HAL_OK;
}

#endif /* (USE_HAL_PLAY_REGISTER_CALLBACKS) */
/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group7
  * @{
  A set of functions allowing to retrieve the PLAY state and kernel clock frequency.
  - HAL_PLAY_GetState()      Return the HAL PLAY handle state.
  - HAL_PLAY_GetClockFreq()  Retrieve the PLAY instance kernel clock frequency.
  */

/**
  * @brief  Return the HAL PLAY handle state.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @return Current PLAY state.
  */
hal_play_state_t HAL_PLAY_GetState(const hal_play_handle_t *hplay)
{
  ASSERT_DBG_PARAM((hplay != NULL));

  return hplay->global_state;
}

/** @brief  Return the peripheral clock frequency for PLAY.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @retval Frequency in Hz.
  * @retval 0 Source clock of the hplay not configured or not ready.
  */
uint32_t HAL_PLAY_GetClockFreq(const hal_play_handle_t *hplay)
{
  ASSERT_DBG_PARAM((hplay != NULL));

  return HAL_RCC_PLAY_GetKernelClkFreq(PLAY_GET_INSTANCE(hplay));
}

/**
  * @}
  */

#if defined (USE_HAL_PLAY_USER_DATA) && (USE_HAL_PLAY_USER_DATA == 1)
/** @addtogroup PLAY_Exported_Functions_Group8
  * @{
A set of functions allowing to manage a user data pointer stored to the HAL PLAY handle:
- HAL_PLAY_SetUserData() Set the user data into the handle.
- HAL_PLAY_GetUserData() Get the user data from the handle.
  */

/**
  * @brief  Set the user data pointer into the handle.
  * @param  hplay       Pointer to a @ref hal_play_handle_t.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_PLAY_SetUserData(hal_play_handle_t *hplay, const void *p_user_data)
{
  ASSERT_DBG_PARAM((hplay != NULL));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  hplay->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data pointer from the handle.
  * @param  hplay Pointer to a @ref hal_play_handle_t.
  * @return Pointer to the user data
  */
const void *HAL_PLAY_GetUserData(const hal_play_handle_t *hplay)
{
  ASSERT_DBG_PARAM((hplay != NULL));

  /* All states are valid except reset */
  ASSERT_DBG_STATE(hplay->global_state, (uint32_t)((uint32_t)HAL_PLAY_STATE_INIT
                                                   | (uint32_t)HAL_PLAY_STATE_IDLE
                                                   | (uint32_t)HAL_PLAY_STATE_ACTIVE));

  return hplay->p_user_data;
}

/**
  * @}
  */

#endif /* USE_HAL_PLAY_USER_DATA */

/** @addtogroup PLAY_Exported_Functions_Group9
  * @{
A set of functions allowing to manage security and privileged access levels attributes
- HAL_PLAY_SetSecAttr() Set the security access level attribute.
- HAL_PLAY_GetSecAttr() Get the security access level attribute.
- HAL_PLAY_SetPrivAttr() Set the privileged access level attribute.
- HAL_PLAY_GetPrivAttr() Get the privileged access level attribute.
  */

#if defined(CMSE_SECURE_EXECUTION_ENVIRONMENT)
/**
  * @brief  Set the security access level attribute for item(s).
  * @param  instance PLAY instance.
  * @param  item     This parameter can be one or a combination of the following values:
  *                  @arg @ref HAL_PLAY_SEC_ITEM_CONFIG
  *                  @arg @ref HAL_PLAY_SEC_ITEM_ALL
  * @param  sec_attr This parameter can be one of the following values:
  *                  @arg @ref HAL_PLAY_SEC
  *                  @arg @ref HAL_PLAY_NSEC
  * @note   Only available from secure and privileged state.
  * @retval HAL_OK    Security attribute has been set successfully.
  * @retval HAL_ERROR Non-privileged write to a privileged-only register.
  */
hal_status_t HAL_PLAY_SetSecAttr(hal_play_t instance, uint32_t item, hal_play_sec_attr_t sec_attr)
{
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE((PLAY_TypeDef *)(uint32_t)instance));
  ASSERT_DBG_PARAM(IS_PLAY_SEC_ITEM(item));
  ASSERT_DBG_PARAM(IS_PLAY_ITEM_SEC_ATTR(sec_attr));

  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }

  LL_PLAY_SetSecAttr((PLAY_TypeDef *)(uint32_t)instance, item, (uint32_t)sec_attr);

  return HAL_OK;
}
#endif /* CMSE_SECURE_EXECUTION_ENVIRONMENT */

/**
  * @brief  Get the security access level attribute of an item.
  * @param  instance PLAY instance.
  * @param  item This parameter can be one of the following values:
  *              @arg @ref HAL_PLAY_SEC_ITEM_CONFIG
  *              @arg @ref HAL_PLAY_SEC_ITEM_ALL
  * @return The security attribute.
  */
hal_play_sec_attr_t HAL_PLAY_GetSecAttr(hal_play_t instance, uint32_t item)
{
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE((PLAY_TypeDef *)(uint32_t)instance));
  ASSERT_DBG_PARAM(IS_PLAY_SEC_ITEM(item));

  return ((hal_play_sec_attr_t)LL_PLAY_GetSecAttr((PLAY_TypeDef *)(uint32_t)instance, item));
}

/**
  * @brief  Set the privileged access level attribute for item(s).
  * @param  instance PLAY instance.
  * @param  item      This parameter can be one or a combination of the following values:
  *                   @arg @ref HAL_PLAY_PRIV_ITEM_CONFIG
  *                   @arg @ref HAL_PLAY_PRIV_ITEM_ALL
  * @param  priv_attr This parameter can be one of the following values:
  *                   @arg @ref HAL_PLAY_PRIV
  *                   @arg @ref HAL_PLAY_NPRIV
  * @retval HAL_OK    Privileged attribute has been set successfully
  * @retval HAL_ERROR Non-privileged write to a privileged-only register
  */
hal_status_t HAL_PLAY_SetPrivAttr(hal_play_t instance, uint32_t item, hal_play_priv_attr_t priv_attr)
{
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE((PLAY_TypeDef *)(uint32_t)instance));
  ASSERT_DBG_PARAM(IS_PLAY_PRIV_ITEM(item));
  ASSERT_DBG_PARAM(IS_PLAY_ITEM_PRIV_ATTR(priv_attr));

  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return HAL_ERROR;
  }

  LL_PLAY_SetPrivAttr((PLAY_TypeDef *)(uint32_t)instance, item, (uint32_t)priv_attr);

  return HAL_OK;
}

/**
  * @brief  Get the privileged access level attribute of an item.
  * @param  instance PLAY instance.
  * @param  item This parameter can be one of the following values:
  *              @arg @ref HAL_PLAY_PRIV_ITEM_CONFIG
  *              @arg @ref HAL_PLAY_PRIV_ITEM_ALL
  * @return The privileged attribute.
  */
hal_play_priv_attr_t HAL_PLAY_GetPrivAttr(hal_play_t instance, uint32_t item)
{
  ASSERT_DBG_PARAM(IS_PLAY_ALL_INSTANCE((PLAY_TypeDef *)(uint32_t)instance));
  ASSERT_DBG_PARAM(IS_PLAY_PRIV_ITEM(item));

  return ((hal_play_priv_attr_t)LL_PLAY_GetPrivAttr((PLAY_TypeDef *)(uint32_t)instance, item));
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup PLAY_Private_Functions PLAY Private Functions
  * @{
  */

/**
  * @brief  Configure the Edge Triggers: flag transition of lookup table outputs.
  * @param  hplay      Pointer to a @ref hal_play_handle_t.
  * @param  p_config   Pointer to a @ref hal_play_edge_trigger_config_t structure for the Edge Triggers configuration.
  * @param  timeout_ms Timeout duration (in ms).
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_BUSY    A write is pending.
  * @retval HAL_TIMEOUT Operation timed-out.
  */
static hal_status_t PLAY_LUT_SetEdgeTrigger(const hal_play_handle_t *hplay,
                                            const hal_play_edge_trigger_config_t *p_config,
                                            uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Check if write access available */
  if (LL_PLAY_LUT_IsEdgeTriggerWriteBusy(p_playx) != 0U)
  {
    return HAL_BUSY;
  }

  /* Update Transition */
  LL_PLAY_LUT_SetEdgeTrigger(p_playx, p_config->lut_out_falling_mask, p_config->lut_out_rising_mask);

  /* Wait until the write is completed */
  /* The Edge Trigger write complete flag cannot be checked here, as it is only available in interrupt mode */
  uint32_t tick_start = HAL_GetTick();
  while (LL_PLAY_LUT_IsEdgeTriggerWriteBusy(p_playx) != 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tick_start) > timeout_ms) || (timeout_ms == 0U))
      {
        /* Before returning timeout, re-check if the flag has cleared */
        if (LL_PLAY_LUT_IsEdgeTriggerWriteBusy(p_playx) != 0U)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }
  return HAL_OK;
}

/**
  * @}
  */

#endif /* USE_HAL_PLAY_MODULE */
#endif /* PLAY1 */

/**
  * @}
  */

/**
  * @}
  */
