/**
  ******************************************************************************
  * @file    stm32h5xx_hal_play.c
  * @brief   PLAY HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functions of the Programmable Logic Array (PLAY) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Configuration functions
  *           + Peripheral Operational functions
  *           + Peripheral State functions
  *           + Peripheral Access Control functions
  *           + IRQ handler management
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
    The PLAY HAL driver can be used as follows:

    (#) Declare a HAL_PLAY_HandleTypeDef handle structure (eg. HAL_PLAY_HandleTypeDef hplay).
    (#) Initialize the PLAY low level resources by implementing the HAL_PLAY_MspInit() API:
        (##) Select the PLAY kernel clock source with RCC API
        (##) Configure the PLAY kernel clock prescaler with RCC API
        (##) Enable the PLAY interface clock using __HAL_RCC_PLAYx_CLK_ENABLE()
        (##) PLAY pins configuration:
            (+++) Enable the clock for the PLAY GPIOs
            (+++) Configure these PLAY pins as alternate function
        (##) NVIC configuration if you need to use interrupt process:
            (+++) Configure the PLAY interrupt priority.
            (+++) Enable the NVIC PLAY IRQ handler.
        (##) Optionally, reset the peripheral either by a full reset of all registers or
             by an "application" reset for only the functional registers (refer to the RCC API)

    (#) Initialize PLAY registers by calling the HAL_PLAY_Init() API which calls HAL_PLAY_MspInit()

    (#) To configure PLAY, call the following APIs:
           - HAL_PLAY_INPUT_SetConfig() : to select the input signals and configure filters
           - HAL_PLAY_LUT_SetConfig() : to configure the Look-Up Tables

        Finalize the configuration by calling the API HAL_PLAY_OUTPUT_SetConfig.
        This one allows to output some Look-Up Table Outputs and
        indicates that the peripheral is ready to start (handle state = HAL_PLAY_STATE_READY).

    (#) After ending the configuration, start the PLAY with HAL_PLAY_Start() to:
          - lock the PLAYx configuration registers to prevent any accidental write access.
            The kernel clock becomes operational. Then LUT Synchronized Outputs, Filters, SW Triggers and Edge Triggers
            become functional.
          - set a first configuration of Edge Trigger on LUT Outputs.

        At this step, the PLAY Outputs can be connected to GPIOs or internal IPs.

    (#) Stop the PLAY with the API HAL_PLAY_Stop.
        This function disables all Look-Up Table Output ITs and unlocks the configuration.
        The handle state is back to HAL_PLAY_STATE_READY and allows the Application to update the peripheral.

        Before updating the PLAY configuration, it is strongly recommended to disconnect all peripherals connected
        to PLAY Outputs to avoid any glitches.

    (#) At then end of the PLAY processor User application, call the function HAL_PLAY_DeInit()
        to restore the default configuration which calls HAL_PLAY_MspDeInit().

  *** Look-Up Table Output ***
  ============================
  [..]
    (+) The Truth Table of a Look-Up table is composed of 16 combinations (with 4 inputs):
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

      There are several Truth Table values for a logic gate depending of the selected inputs.
      For example the Truth Table value for the logic 'AND' are (non-exhaustive list):
        - for IN1 & IN0: 0x8888
        - for IN2 & IN1: 0xC0C0
        - for IN3 & IN2: 0xF000
        - for IN2, IN1 & IN0: 0x8080
        - for IN3, IN2, IN1 & IN0: 0x8000
        - ...
    (+) A Look-Up Table generates a single output which can be stored with a register.
        Each output has a flag which is triggered on a Rising or Falling edge (depends of user configuration).

        The best way to use PLAY is to use the LUT Output interrupts to be advise when an output is changed.
        You can also configure the interrupt mode using the HAL_PLAY_OUTPUT_EnableIT() function.
        When an IT is triggered the callback HAL_PLAY_LUTOutputRisingCallback() or HAL_PLAY_LUTOutputFallingCallback()
        is called (depending of the edge trigger configuration).

        Otherwise, you can work in polling mode by using the HAL_PLAY_OUTPUT_PollForEdgeTrigger(), but the LUT output
        could changed in the time frame between the end of polling and the treatment to do for the related output.

  *** Callback registration ***
  =============================
  [..]
      The compilation define USE_HAL_PLAY_REGISTER_CALLBACKS, when set to 1,
      allows the user to configure dynamically the driver callbacks.

  [..]
      Use the function HAL_PLAY_RegisterCallback() to register a callback taking only the HAL peripheral handle
      as parameter.
      Use the function HAL_PLAY_RegisterLUTOutputCallback() to register a callback taking
      2 parameters (handle + uint32_t) and which is dedicated to perform action when almost a LUT Output state changed.

      Both HAL_PLAY_RegisterCallback() and HAL_PLAY_RegisterLUTOutputCallback() take as parameters:
        - the HAL peripheral handle,
        - the Callback ID,
        - the pointer to the user callback function.

  [..]
      Use function HAL_PLAY_UnRegisterCallback() and HAL_PLAY_UnRegisterLUTOutputCallback() to reset a callback
      to the default weak function.
      HAL_PLAY_UnRegisterCallback() and HAL_PLAY_UnRegisterLUTOutputCallback() takes as parameters the HAL peripheral
      handle and the Callback ID.

  [..]
      Use respectively, the functions HAL_PLAY_RegisterCallback() / HAL_PLAY_UnRegisterCallback(),
      to register / unregister following callbacks:
        (+) MspInitCallback              : PLAY MspInit.
        (+) MspDeInitCallback            : PLAY MspDeInit.
        (+) SWTriggerWriteCpltCallback   : Software Trigger Write Complete callback.
        (+) EdgeTriggerWriteCpltCallback : Edge Trigger Write Complete callback.

  [..]
      Use respectively, the functions HAL_PLAY_RegisterLUTOutputCallback() / HAL_PLAY_UnRegisterLUTOutputCallback(),
      to register / unregister following callbacks:
        (+) HAL_PLAY_LUTOutputRisingCallback()  : Look-Up Table Output Rising Edge triggered callback.
        (+) HAL_PLAY_LUTOutputFallingCallback() : Look-Up Table Output Falling Edge triggered callback.

  [..]
      By default, after the HAL_PLAY_Init and when the state is HAL_PLAY_STATE_RESET,
      all callbacks are reset to the corresponding legacy weak functions.

      Exception done for MspInit and MspDeInit callbacks that are respectively
      reset to the legacy weak function in the HAL_PLAY_Init() and HAL_PLAY_DeInit() only when
      these callbacks are NULL (not registered beforehand).
      If not, MspInit or MspDeInit are not NULL, the HAL_PLAY_Init() and HAL_PLAY_DeInit()
      keep and use the user MspInit/MspDeInit callbacks (registered beforehand).

  [..]
      Callbacks can be registered/unregistered in HAL_PLAY_STATE_READY state only.
      Exception done for MspInit/MspDeInit callbacks that can be registered/unregistered
      in HAL_PLAY_STATE_READY or HAL_PLAY_STATE_RESET state,
      thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
      In that case, first register the MspInit/MspDeInit user callbacks
      using HAL_PLAY_RegisterCallback before calling HAL_PLAY_DeInit() or HAL_PLAY_Init() function.

  [..]
      When the compilation define USE_HAL_PLAY_REGISTER_CALLBACKS is set to 0 or
      not defined, the callback registering feature is not available and all callbacks
      are set to the corresponding weak functions.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

/** @addtogroup PLAY
  * @{
  */

#ifdef HAL_PLAY_MODULE_ENABLED
#if defined(PLAY1)

/* Private types -------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/** @defgroup PLAY_Private_Constants  PLAY Private Constants
  * @{
  */

/**
  * @brief Definitions used to decode the @ref HAL_PLAY_IN_SourceTypeDef enumerated values
  */
#define PLAY_INSTANCE_ID_MASK  (0x3UL << HAL_PLAY_INSTANCE_ID_POS) /*!< Instance ID field mask                 */
#define PLAY_IN_MUX_MASK       (0x1FUL << HAL_PLAY_IN_MUX_POS)     /*!< Input multiplexer field mask           */
#define PLAY_IN_MUX_VALUE_POS  (0U)                                /*!< Input multiplexer value field position */
#define PLAY_IN_MUX_VALUE_MASK (0xFUL << PLAY_IN_MUX_VALUE_POS)    /*!< Input multiplexer value field mask     */

/**
  * @brief PLAY Interrupt Definition
  */
#define PLAY_IT_STATUS_SW_TRIGGER_WRITE_COMPLETE   LL_PLAY_IER_SWINWC_IEN  /*!< Interrupt Software Trigger write complete */
#define PLAY_IT_STATUS_EDGE_TRIGGER_WRITE_COMPLETE LL_PLAY_IER_FLCTLWC_IEN /*!< Interrupt Edge Trigger write complete     */

/**
  * @brief Maximum Timeout for any write on Software Trigger or Edge Trigger register.
  *
  * With a LSI as PLAY kernel clock source and a prescaler of 32768, the play_clk cycle is 1s.
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
  * @brief Retrieve the bit status in a given register.
  * @param  reg The register to check.
  * @param  bit The bit to check to check.
  * @retval 1   Bit is set.
  * @retval 0   Bit is reset.
  */
#define IS_PLAY_BIT_SET(reg, bit)  (((reg) & (bit)) == (bit))

/**
  * @brief Retrieve the PLAY hardware CMSIS instance from the hal handle.
  * @param handle specifies the peripheral Handle.
  */
#define PLAY_GET_INSTANCE(handle)  ((handle)->instance)

/**
  * @brief Retrieve the PLAYx instance ID from the HAL handle.
  * @param handle Specifies the peripheral Handle.
  */
#define PLAY_GET_INSTANCE_ID(handle)  \
  (HAL_PLAY1_INSTANCE_ID)

/**
  * @brief Verifies the PLAY TrustZone access control value.
  * @param  access Value of TZ access control.
  * @retval 1    access is a valid value.
  * @retval 0    access is an invalid value.
  */
#define IS_PLAY_TZ_ACCESS_CONTROL(access)            \
  (((access) == HAL_PLAY_TZ_REG_UNPROTECTED)         \
   || ((access) == HAL_PLAY_TZ_CONFIG_REG_PROTECTED) \
   || ((access) == HAL_PLAY_TZ_ALL_REG_PROTECTED))

/**
  * @brief Verifies the minimum pulse width value.
  * @param  width Value of pulse width.
  * @retval 1     width is a valid value.
  * @retval 0     width is an invalid value.
  */
#define IS_PLAY_MIN_PULSE_WIDTH(width)  ((width) <= (LL_PLAY_INPUT_FILTER_WIDTH_VALUE_MAX))

/**
  * @brief Verifies the edge detection mode.
  * @param  mode Value of edge detection mode (@ref HAL_PLAY_EdgeDetectionModeTypeDef).
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
  * @param  mux Input multiplexer (@ref HAL_PLAY_INTypeDef).
  * @retval 1   mux is a valid value.
  * @retval 0   mux is an invalid value.
  */
#define IS_PLAY_IN_ID(mux)      \
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
  * @param  source Input signal (@ref HAL_PLAY_IN_SourceTypeDef).
  * @retval 1      source is a valid value.
  * @retval 0      source is an invalid value.
  */
#define IS_PLAY1_IN_SOURCE(source)                           \
  /* IO */                                                   \
  (((source) == HAL_PLAY1_IN_IN0_MUX0)                       \
   || ((source) == HAL_PLAY1_IN_IN1_MUX1)                    \
   || ((source) == HAL_PLAY1_IN_IN2_MUX2)                    \
   || ((source) == HAL_PLAY1_IN_IN3_MUX3)                    \
   || ((source) == HAL_PLAY1_IN_IN4_MUX4)                    \
   || ((source) == HAL_PLAY1_IN_IN5_MUX5)                    \
   || ((source) == HAL_PLAY1_IN_IN6_MUX6)                    \
   || ((source) == HAL_PLAY1_IN_IN7_MUX7)                    \
   || ((source) == HAL_PLAY1_IN_IN8_MUX8)                    \
   || ((source) == HAL_PLAY1_IN_IN9_MUX9)                    \
   || ((source) == HAL_PLAY1_IN_IN10_MUX10)                  \
   || ((source) == HAL_PLAY1_IN_IN11_MUX11)                  \
   || ((source) == HAL_PLAY1_IN_IN12_MUX12)                  \
   || ((source) == HAL_PLAY1_IN_IN13_MUX13)                  \
   || ((source) == HAL_PLAY1_IN_IN14_MUX14)                  \
   || ((source) == HAL_PLAY1_IN_IN15_MUX15)                  \
   /* ADC */                                                 \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD1_MUX3)              \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD1_MUX7)              \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD1_MUX9)              \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD1_MUX15)             \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD2_MUX0)              \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD2_MUX4)              \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD2_MUX8)              \
   || ((source) == HAL_PLAY1_IN_ADC1_AWD2_MUX10)             \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD1_MUX3)              \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD1_MUX7)              \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD1_MUX11)             \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD2_MUX4)              \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD2_MUX8)              \
   || ((source) == HAL_PLAY1_IN_ADC2_AWD2_MUX12)             \
   /* COMP */                                                \
   || ((source) == HAL_PLAY1_IN_COMP1_OUT_MUX1)              \
   || ((source) == HAL_PLAY1_IN_COMP1_OUT_MUX5)              \
   || ((source) == HAL_PLAY1_IN_COMP1_OUT_MUX7)              \
   || ((source) == HAL_PLAY1_IN_COMP1_OUT_MUX13)             \
   || ((source) == HAL_PLAY1_IN_COMP2_OUT_MUX1)              \
   || ((source) == HAL_PLAY1_IN_COMP2_OUT_MUX5)              \
   || ((source) == HAL_PLAY1_IN_COMP2_OUT_MUX9)              \
   /* EVENT_OUT */                                           \
   || ((source) == HAL_PLAY1_IN_EVENTOUT_MUX0)               \
   || ((source) == HAL_PLAY1_IN_EVENTOUT_MUX8)               \
   || ((source) == HAL_PLAY1_IN_EVENTOUT_MUX12)              \
   /* LOCKUP */                                              \
   || ((source) == HAL_PLAY1_IN_LOCKUP_MUX4)                 \
   || ((source) == HAL_PLAY1_IN_LOCKUP_MUX8)                 \
   || ((source) == HAL_PLAY1_IN_LOCKUP_MUX12)                \
   || ((source) == HAL_PLAY1_IN_LOCKUP_MUX14)                \
   /* LPTIM */                                               \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH1_MUX3)             \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH1_MUX5)             \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH1_MUX11)            \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH1_MUX15)            \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH2_MUX0)             \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH2_MUX4)             \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH2_MUX6)             \
   || ((source) == HAL_PLAY1_IN_LPTIM1_CH2_MUX12)            \
   || ((source) == HAL_PLAY1_IN_LPTIM2_CH1_MUX3)             \
   || ((source) == HAL_PLAY1_IN_LPTIM2_CH1_MUX7)             \
   || ((source) == HAL_PLAY1_IN_LPTIM2_CH1_MUX15)            \
   || ((source) == HAL_PLAY1_IN_LPTIM2_CH2_MUX0)             \
   || ((source) == HAL_PLAY1_IN_LPTIM2_CH2_MUX4)             \
   || ((source) == HAL_PLAY1_IN_LPTIM2_CH2_MUX8)             \
   /* MCO */                                                 \
   || ((source) == HAL_PLAY1_IN_RCC_MCO1_MUX2)               \
   || ((source) == HAL_PLAY1_IN_RCC_MCO1_MUX6)               \
   || ((source) == HAL_PLAY1_IN_RCC_MCO1_MUX8)               \
   || ((source) == HAL_PLAY1_IN_RCC_MCO1_MUX14)              \
   || ((source) == HAL_PLAY1_IN_RCC_MCO2_MUX2)               \
   || ((source) == HAL_PLAY1_IN_RCC_MCO2_MUX6)               \
   || ((source) == HAL_PLAY1_IN_RCC_MCO2_MUX10)              \
   /* NMI */                                                 \
   || ((source) == HAL_PLAY1_IN_NMI_MUX3)                    \
   || ((source) == HAL_PLAY1_IN_NMI_MUX7)                    \
   || ((source) == HAL_PLAY1_IN_NMI_MUX11)                   \
   || ((source) == HAL_PLAY1_IN_NMI_MUX13)                   \
   /* SPI */                                                 \
   || ((source) == HAL_PLAY1_IN_SPI1_MOSI_MUX0)              \
   || ((source) == HAL_PLAY1_IN_SPI1_MOSI_MUX6)              \
   || ((source) == HAL_PLAY1_IN_SPI1_MOSI_MUX10)             \
   || ((source) == HAL_PLAY1_IN_SPI1_MOSI_MUX14)             \
   || ((source) == HAL_PLAY1_IN_SPI1_NSS_MUX5)               \
   || ((source) == HAL_PLAY1_IN_SPI1_NSS_MUX9)               \
   || ((source) == HAL_PLAY1_IN_SPI1_NSS_MUX13)              \
   || ((source) == HAL_PLAY1_IN_SPI1_NSS_MUX15)              \
   || ((source) == HAL_PLAY1_IN_SPI1_SCLK_MUX1)              \
   || ((source) == HAL_PLAY1_IN_SPI1_SCLK_MUX7)              \
   || ((source) == HAL_PLAY1_IN_SPI1_SCLK_MUX11)             \
   || ((source) == HAL_PLAY1_IN_SPI1_SCLK_MUX15)             \
   || ((source) == HAL_PLAY1_IN_SPI2_MOSI_MUX2)              \
   || ((source) == HAL_PLAY1_IN_SPI2_MOSI_MUX10)             \
   || ((source) == HAL_PLAY1_IN_SPI2_MOSI_MUX14)             \
   || ((source) == HAL_PLAY1_IN_SPI2_NSS_MUX1)               \
   || ((source) == HAL_PLAY1_IN_SPI2_NSS_MUX9)               \
   || ((source) == HAL_PLAY1_IN_SPI2_NSS_MUX13)              \
   || ((source) == HAL_PLAY1_IN_SPI2_SCLK_MUX3)              \
   || ((source) == HAL_PLAY1_IN_SPI2_SCLK_MUX11)             \
   || ((source) == HAL_PLAY1_IN_SPI2_SCLK_MUX15)             \
   /* TIM */                                                 \
   || ((source) == HAL_PLAY1_IN_TIM2_OC3_MUX1)               \
   || ((source) == HAL_PLAY1_IN_TIM2_OC3_MUX3)               \
   || ((source) == HAL_PLAY1_IN_TIM2_OC3_MUX9)               \
   || ((source) == HAL_PLAY1_IN_TIM2_OC3_MUX13)              \
   || ((source) == HAL_PLAY1_IN_TIM2_OC4_MUX2)               \
   || ((source) == HAL_PLAY1_IN_TIM2_OC4_MUX4)               \
   || ((source) == HAL_PLAY1_IN_TIM2_OC4_MUX10)              \
   || ((source) == HAL_PLAY1_IN_TIM2_OC4_MUX14)              \
   || ((source) == HAL_PLAY1_IN_TIM2_TRGO_MUX0)              \
   || ((source) == HAL_PLAY1_IN_TIM2_TRGO_MUX2)              \
   || ((source) == HAL_PLAY1_IN_TIM2_TRGO_MUX8)              \
   || ((source) == HAL_PLAY1_IN_TIM2_TRGO_MUX12)             \
   || ((source) == HAL_PLAY1_IN_TIM3_OC3_MUX1)               \
   || ((source) == HAL_PLAY1_IN_TIM3_OC3_MUX5)               \
   || ((source) == HAL_PLAY1_IN_TIM3_OC3_MUX13)              \
   || ((source) == HAL_PLAY1_IN_TIM3_OC4_MUX2)               \
   || ((source) == HAL_PLAY1_IN_TIM3_OC4_MUX6)               \
   || ((source) == HAL_PLAY1_IN_TIM3_OC4_MUX14)              \
   || ((source) == HAL_PLAY1_IN_TIM3_TRGO_MUX0)              \
   || ((source) == HAL_PLAY1_IN_TIM3_TRGO_MUX4)              \
   || ((source) == HAL_PLAY1_IN_TIM3_TRGO_MUX12)             \
   /* USART */                                               \
   || ((source) == HAL_PLAY1_IN_USART1_CK_MUX2)              \
   || ((source) == HAL_PLAY1_IN_USART1_CK_MUX6)              \
   || ((source) == HAL_PLAY1_IN_USART1_CK_MUX10)             \
   || ((source) == HAL_PLAY1_IN_USART1_CK_MUX12)             \
   || ((source) == HAL_PLAY1_IN_USART1_TX_MUX1)              \
   || ((source) == HAL_PLAY1_IN_USART1_TX_MUX5)              \
   || ((source) == HAL_PLAY1_IN_USART1_TX_MUX9)              \
   || ((source) == HAL_PLAY1_IN_USART1_TX_MUX11)             \
   || ((source) == HAL_PLAY1_IN_USART2_CK_MUX6)              \
   || ((source) == HAL_PLAY1_IN_USART2_CK_MUX10)             \
   || ((source) == HAL_PLAY1_IN_USART2_CK_MUX14)             \
   || ((source) == HAL_PLAY1_IN_USART2_TX_MUX5)              \
   || ((source) == HAL_PLAY1_IN_USART2_TX_MUX9)              \
   || ((source) == HAL_PLAY1_IN_USART2_TX_MUX13))

/**
  * @brief Verifies the value of input multiplexer source.
  * @param  instance PLAYx instance (@ref PLAY_TypeDef). (*)
  * @param  source   Input signal (@ref HAL_PLAY_IN_SourceTypeDef).
  * @retval 1        source is a valid value.
  * @retval 0        source is an invalid value.
  *
  *  (*) : available in stm32h5xxxx.h in cmsis device header file.
  */
#define IS_PLAY_IN_SOURCE(instance, source)                                              \
  ((((instance) == PLAY1_NS) || ((instance) == PLAY1_S)) && IS_PLAY1_IN_SOURCE((source)))

/**
  * @brief Verifies the Look-Up Table of PLAY1 instance.
  * @param  lut Look-Up Table (@ref HAL_PLAY_LUTTypeDef).
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
  * @param  instance PLAYx instance (@ref PLAY_TypeDef). (*)
  * @param  lut      Look-Up Table (@ref HAL_PLAY_LUTTypeDef).
  * @retval 1        lut is a valid value.
  * @retval 0        lut is an invalid value.
  *
  *  (*) : available in stm32h5xxxx.h in cmsis device header file.
  */
#define IS_PLAY_LUT(instance, lut)                                            \
  ((((instance) == PLAY1_NS) || ((instance) == PLAY1_S)) && IS_PLAY1_LUT(lut))

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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT0(input_source)      \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT0_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 1 for PLAY1 instance.
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT4(input_source)      \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT4_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 5 for PLAY1 instance.
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT8(input_source)      \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT8_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 9 for PLAY1 instance.
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  */
#define IS_PLAY1_LUT_INPUT_SOURCE_LUT12(input_source)      \
  (((input_source) == HAL_PLAY_LUT_INPUT_LUT12_OUT_DIRECT))

/**
  * @brief Verifies the "LUT direct output" input source of the Look-Up Table 13 for PLAY1 instance.
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @param  lut          Look-Up Table (@ref HAL_PLAY_LUTTypeDef).
  * @param  input_source Input signal value (@ref HAL_PLAY_LUT_InputSourceTypeDef).
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
  * @brief Verifies the input source of a look-up table
  * @param  instance     PLAYx instance (@ref PLAY_TypeDef). (*)
  * @param  lut          Look-Up Table (@ref HAL_PLAY_LUTTypeDef).
  * @param  input_source Value of input source (@ref HAL_PLAY_LUT_InputSourceTypeDef).
  * @retval 1            input_source is a valid value.
  * @retval 0            input_source is an invalid value.
  *
  *  (*) : available in stm32h5xxxx.h in cmsis device header file.
  */
#define IS_PLAY_LUT_INPUT_SOURCE(instance, lut, input_source)                                            \
  ((((instance) == PLAY1_NS) || ((instance) == PLAY1_S)) && IS_PLAY1_LUT_INPUT_SOURCE(lut, input_source))

/**
  * @brief Verifies the signal source as Clock Gate for PLAY1 instance.
  * @param  source Signal source (@ref HAL_PLAY_LUT_ClkGateSourceTypeDef).
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
  * @param  instance PLAYx instance (@ref PLAY_TypeDef). (*)
  * @param  source   Signal source for Clock Gate.
  * @retval 1        source is a valid value.
  * @retval 0        source is an invalid value.
  *
  *  (*): available in stm32h5xxxx.h in cmsis device header file.
  */
#define IS_PLAY_LUT_CLOCK_GATE_SOURCE(instance, source)                                            \
  ((((instance) == PLAY1_NS) || ((instance) == PLAY1_S)) && IS_PLAY1_LUT_CLOCK_GATE_SOURCE(source))

/**
  * @brief Verifies the lookup table value.
  * @param  lut   Value of lookup table.
  * @retval 1     lut is a valid value.
  * @retval 0     lut is an invalid value.
  */
#define IS_PLAY_LUT_TRUTH_TABLE_VALUE(lut)  ((lut) <= (HAL_PLAY_LUT_TRUTH_TABLE_VALUE_MAX))

/**
  * @brief Verifies the Output Multiplexer.
  * @param  mux Output Multiplexer (@ref HAL_PLAY_OUTTypeDef).
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
  * @param  instance PLAYx instance (@ref PLAY_TypeDef). (*)
  * @param  source   Value of output source.
  * @retval 1        source is a valid value.
  * @retval 0        source is an invalid value.
  *
  *  (*) : available in stm32h5xxxx.h in cmsis device header file.
  */
#define IS_PLAY_OUT_SOURCE(instance, source)                                            \
  ((((instance) == PLAY1_NS) || ((instance) == PLAY1_S)) && IS_PLAY1_OUT_SOURCE(source))

/**
  * @brief Verifies the polling mode.
  * @param  mode Value of mode (@ref HAL_PLAY_EdgeDetectionModeTypeDef).
  * @retval 1    mode is a valid value.
  * @retval 0    mode is an invalid value.
  */
#define IS_PLAY_POLL_MODE(mode)                  \
  (((mode) == HAL_PLAY_POLLING_FOR_ALL_EDGES)    \
   || ((mode) == HAL_PLAY_POLLING_FOR_ANY_EDGE))

/**
  * @brief Verifies the Software Trigger state value.
  * @param  state Value of state (@ref HAL_PLAY_SWTriggerStateTypeDef).
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
  ((((uint32_t)(swtrig_msk) & HAL_PLAY_SWTRIG_ALL) != 0x00U) \
   && (((uint32_t)(swtrig_msk) & ~HAL_PLAY_SWTRIG_ALL) == 0x00U))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup PLAY_Private_Functions  PLAY Private Functions
  * @{
  */

static HAL_StatusTypeDef PLAY_LUT_SetEdgeTrigger(const HAL_PLAY_HandleTypeDef *hplay,
                                                 const HAL_PLAY_EdgeTriggerConfTypeDef *p_config,
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
 - HAL_PLAY_Init() : initialize the selected device with the PLAY instance.
 - HAL_PLAY_DeInit() : de-initialize the selected PLAYx peripheral and reset the handle and status flags.
 - HAL_PLAY_MSPInit() : initialize the PLAY MSP (MCU Specific Package).
 - HAL_PLAY_MSPDeInit() : de-initialize the PLAY MSP.
  */

/**
  * @brief  Initialize the PLAY according to the associated handle.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @retval HAL_OK            PLAY instance has been correctly initialized.
  * @retval HAL_INVALID_PARAM PLAY handle is NULL
  */
HAL_StatusTypeDef HAL_PLAY_Init(HAL_PLAY_HandleTypeDef *hplay)
{
  const PLAY_TypeDef *p_playx;

  /* Check the PLAY handle allocation */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

  /* Init the peripheral */
  if (hplay->global_state == HAL_PLAY_STATE_RESET)
  {
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
    /* Register the default callback functions */
    hplay->SWTriggerWriteCpltCallback = HAL_PLAY_SWTriggerWriteCpltCallback;
    hplay->EdgeTriggerWriteCpltCallback = HAL_PLAY_EdgeTriggerWriteCpltCallback;
    hplay->LUTOutputRisingCallback = HAL_PLAY_LUTOutputRisingCallback;
    hplay->LUTOutputFallingCallback = HAL_PLAY_LUTOutputFallingCallback;

    if (NULL == hplay->MspInitCallback)
    {
      hplay->MspInitCallback = HAL_PLAY_MspInit;
    }

    if (NULL == hplay->MspDeInitCallback)
    {
      hplay->MspDeInitCallback = HAL_PLAY_MspDeInit;
    }

    /* Init the low level hardware */
    hplay->MspInitCallback(hplay);
#else
    /* Init the low level hardware */
    HAL_PLAY_MspInit(hplay);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
  }

  /* Reset error code */
  hplay->last_error_codes = HAL_PLAY_ERROR_NONE;

  hplay->global_state = HAL_PLAY_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief DeInitialize the PLAY peripheral.
  * @param hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @note  HAL_PLAY_DeInit does not reset all PLAY registers.
  *        The Application must call RCC API to force the reset of all PLAY registers.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_DeInit(HAL_PLAY_HandleTypeDef *hplay)
{
  PLAY_TypeDef *p_playx;

  /* Check the PLAY handle allocation */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Clear only interrupts & flags. The rest of configuration must be reset by the application with MspDeInit */
  LL_PLAY_LUT_DisableIT(p_playx, LL_PLAY_LUT_ALL_OUT_REGISTERED | LL_PLAY_LUT_ALL_OUT_DIRECT);
  LL_PLAY_LUT_DisableIT_EdgeTriggerWriteComplete(p_playx);
  LL_PLAY_LUT_ClearFlag(p_playx, LL_PLAY_LUT_ALL_OUT_REGISTERED | LL_PLAY_LUT_ALL_OUT_DIRECT);
  LL_PLAY_LUT_ClearFlag_EdgeTriggerWriteComplete(p_playx);
  LL_PLAY_DisableIT_SWTriggerWriteComplete(p_playx);
  LL_PLAY_ClearFlag_SWTriggerWriteComplete(p_playx);

  LL_PLAY_Unlock(p_playx);

#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
  /* Register the default callback functions */
  hplay->SWTriggerWriteCpltCallback = HAL_PLAY_SWTriggerWriteCpltCallback;
  hplay->EdgeTriggerWriteCpltCallback = HAL_PLAY_EdgeTriggerWriteCpltCallback;
  hplay->LUTOutputRisingCallback = HAL_PLAY_LUTOutputRisingCallback;
  hplay->LUTOutputFallingCallback = HAL_PLAY_LUTOutputFallingCallback;
  hplay->MspInitCallback = HAL_PLAY_MspInit;

  if (hplay->MspDeInitCallback == NULL)
  {
    /* DeInit Callback not initialized as expected then force it to default MspDeInit */
    hplay->MspDeInitCallback = HAL_PLAY_MspDeInit;
  }

  /* DeInit the low level hardware */
  hplay->MspDeInitCallback(hplay);
#else
  /* DeInit the low level hardware */
  HAL_PLAY_MspDeInit(hplay);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS == 1 */

  /* Reset error code */
  hplay->last_error_codes = HAL_PLAY_ERROR_NONE;

  hplay->global_state = HAL_PLAY_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief  Initialize the PLAY MSP.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  */
__weak void HAL_PLAY_MspInit(HAL_PLAY_HandleTypeDef *hplay)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);

  /* NOTE: This function must not be modified, when the callback is needed,
           the HAL_PLAY_MspInit can be implemented in the user file
   */
}

/**
  * @brief  DeInitialize the PLAY MSP.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  */
__weak void HAL_PLAY_MspDeInit(HAL_PLAY_HandleTypeDef *hplay)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);

  /* NOTE: This function must not be modified, when the callback is needed,
           the HAL_PLAY_MspDeInit can be implemented in the user file
   */
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
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config   Pointer to an array of @ref HAL_PLAY_IN_ConfTypeDef.
  * @param  array_size Number of configuration in the array.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Array pointer or handle is NULL.
  */
HAL_StatusTypeDef HAL_PLAY_INPUT_SetConfig(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_IN_ConfTypeDef *p_config,
                                           uint32_t array_size)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  /* Check the parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(((array_size > 0U) && (array_size <= PLAY_INPUT_MUX_NBR(p_playx))));

  /* Check the peripheral state */
  if ((hplay->global_state != HAL_PLAY_STATE_INIT) && (hplay->global_state != HAL_PLAY_STATE_READY))
  {
    return HAL_ERROR;
  }

  /* UnLock the configuration if not already done */
  is_locked = LL_PLAY_IsLocked(p_playx);
  if (is_locked == 1U)
  {
    LL_PLAY_Unlock(p_playx);
  }

  /* Write the configurations */
  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    assert_param(IS_PLAY_MIN_PULSE_WIDTH(p_config[idx].min_pulse_width));
    assert_param(IS_PLAY_EDGE_DETECTION_MODE(p_config[idx].mode));
    assert_param(IS_PLAY_IN_SOURCE(p_playx, p_config[idx].source));

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
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config   Pointer to an array of @ref HAL_PLAY_IN_ConfTypeDef to be filled.
  * @param  array_size Number of configuration in the array.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_INPUT_GetConfig(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_IN_ConfTypeDef *p_config,
                                           uint32_t array_size)
{
  const PLAY_TypeDef *p_playx;

  /* Check the parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(((array_size > 0U) && (array_size <= PLAY_INPUT_MUX_NBR(p_playx))));

  /* Rebuild the input source signal */
  uint32_t instance_id = (uint32_t)PLAY_GET_INSTANCE_ID(hplay);
  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    uint32_t mux_sel = (uint32_t)idx << HAL_PLAY_IN_MUX_POS;
    uint32_t source = LL_PLAY_INPUT_GetSource(p_playx, (uint32_t)idx);

    uint32_t in_source = (instance_id | mux_sel | source);

    p_config[idx].source = (HAL_PLAY_IN_SourceTypeDef)in_source;
    p_config[idx].min_pulse_width = LL_PLAY_INPUT_GetMinimumPulseWidth(p_playx, idx);
    p_config[idx].mode = (HAL_PLAY_EdgeDetectionModeTypeDef)LL_PLAY_INPUT_GetEdgeDetectionMode(p_playx, idx);
  }

  return HAL_OK;
}

/**
  * @brief  Configure multiple lookup tables for the PLAY peripheral.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config  Pointer to an array of HAL_PLAY_LUT_ConfTypeDef.
  * @param  array_size Number of configuration in the array.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_SetConfig(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_LUT_ConfTypeDef *p_config,
                                         uint32_t array_size)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  /* Check handle parameter */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(((array_size > 0UL) && (array_size <= PLAY_LUT_NBR(p_playx))));

  /* Check the peripheral state */
  if ((hplay->global_state != HAL_PLAY_STATE_INIT) && (hplay->global_state != HAL_PLAY_STATE_READY))
  {
    return HAL_ERROR;
  }

  /* UnLock the configuration if not already done */
  is_locked = LL_PLAY_IsLocked(p_playx);
  if (is_locked == 1U)
  {
    LL_PLAY_Unlock(p_playx);
  }

  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    assert_param(IS_PLAY_LUT(p_playx, p_config[idx].lut));
    assert_param(IS_PLAY_LUT_TRUTH_TABLE_VALUE(p_config[idx].truth_table));
    assert_param(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                          p_config[idx].input_source[LL_PLAY_LUT_INPUT0]));
    assert_param(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                          p_config[idx].input_source[LL_PLAY_LUT_INPUT1]));
    assert_param(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                          p_config[idx].input_source[LL_PLAY_LUT_INPUT2]));
    assert_param(IS_PLAY_LUT_INPUT_SOURCE(p_playx, p_config[idx].lut,
                                          p_config[idx].input_source[LL_PLAY_LUT_INPUT3]));
    assert_param(IS_PLAY_LUT_CLOCK_GATE_SOURCE(p_playx, p_config[idx].clk_gate_source));

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
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config  Pointer to an array of @ref HAL_PLAY_LUT_ConfTypeDef.
  * @param  array_size Number of configuration in the array.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_GetConfig(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUT_ConfTypeDef *p_config,
                                         uint32_t array_size)
{
  const PLAY_TypeDef *p_playx;

  /* Check handle parameter */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  /* Check parameter setting */
  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(((array_size > 0UL) && (array_size <= PLAY_LUT_NBR(p_playx))));

  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    p_config[idx].lut = (HAL_PLAY_LUTTypeDef)idx;
    p_config[idx].truth_table = LL_PLAY_LUT_GetTruthTable(p_playx, idx);
    p_config[idx].clk_gate_source = (HAL_PLAY_LUT_ClkGateSourceTypeDef)LL_PLAY_LUT_GetClockGate(p_playx, idx);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT0] =
      (HAL_PLAY_LUT_InputSourceTypeDef)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT0);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT1] =
      (HAL_PLAY_LUT_InputSourceTypeDef)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT1);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT2] =
      (HAL_PLAY_LUT_InputSourceTypeDef)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT2);
    p_config[idx].input_source[LL_PLAY_LUT_INPUT3] =
      (HAL_PLAY_LUT_InputSourceTypeDef)LL_PLAY_LUT_GetSource(p_playx, idx, LL_PLAY_LUT_INPUT3);
  }

  return HAL_OK;
}

/**
  * @brief  Configure a set of Output Multiplexer.
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config   Pointer to an array of @ref HAL_PLAY_OUT_ConfTypeDef.
  * @param  array_size Number of configuration in the array.
  * @return HAL status.
  */
HAL_StatusTypeDef HAL_PLAY_OUTPUT_SetConfig(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_OUT_ConfTypeDef *p_config,
                                            uint32_t array_size)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  /* Check the parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(((array_size > 0UL) && (array_size <= PLAY_OUTPUT_MUX_NBR(p_playx))));

  /* Check the peripheral state */
  if ((hplay->global_state != HAL_PLAY_STATE_INIT) && (hplay->global_state != HAL_PLAY_STATE_READY))
  {
    return HAL_ERROR;
  }

  /* UnLock the configuration if not already done */
  is_locked = LL_PLAY_IsLocked(p_playx);
  if (is_locked == 1U)
  {
    LL_PLAY_Unlock(p_playx);
  }

  /* Configure the Logic Array Output */
  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    assert_param(IS_PLAY_OUT(p_config[idx].output_mux));
    assert_param(IS_PLAY_OUT_SOURCE(p_playx, p_config[idx].lut_output));

    LL_PLAY_OUTPUT_SetSource(p_playx, (uint32_t)p_config[idx].output_mux, (uint32_t)p_config[idx].lut_output);
  }

  hplay->global_state = HAL_PLAY_STATE_READY;

  return HAL_OK;
}

/**
  * @brief Retrieve the output multiplexer configurations of the PLAY peripheral in order from 0 to (array_size - 1),
  *        where array_size specifies the number of configurations.
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config   Pointer to an array of @ref HAL_PLAY_OUT_ConfTypeDef.
  * @param  array_size Number of configuration in the array.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_OUTPUT_GetConfig(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_OUT_ConfTypeDef *p_config,
                                            uint32_t array_size)
{
  const PLAY_TypeDef *p_playx;

  /* Check the parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(((array_size > 0UL) && (array_size <= PLAY_OUTPUT_MUX_NBR(p_playx))));

  for (uint32_t idx = 0; idx < array_size; idx++)
  {
    p_config[idx].output_mux = (HAL_PLAY_OUTTypeDef)idx;
    p_config[idx].lut_output = LL_PLAY_OUTPUT_GetSource(p_playx, idx);
  }

  return HAL_OK;
}

/* PLAY Configuration - Unitary functions ***************************************/

/**
  * @brief  Set the signal source for an input multiplexer of the PLAY peripheral.
  * @param  hplay  Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  source Input source signal.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter or current state is not @ref HAL_PLAY_STATE_READY.
  */
HAL_StatusTypeDef HAL_PLAY_INPUT_SetSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_IN_SourceTypeDef source)
{
  PLAY_TypeDef *p_playx;

  /* Check the parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes = HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_IN_SOURCE(p_playx, source));

  uint32_t src_u32 = (uint32_t)source;

  /* Retrieve the input mux */
  uint32_t input_mux = (src_u32 & PLAY_IN_MUX_MASK) >> HAL_PLAY_IN_MUX_POS;
  uint32_t mux_sel = src_u32 & PLAY_IN_MUX_VALUE_MASK;

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  /* Set the source signal */
  LL_PLAY_INPUT_SetSource(p_playx, input_mux, mux_sel);

  return HAL_OK;
}

/**
  * @brief  Retrieve the signal source for an input multiplexer of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  input_mux Input multiplexer.
  * @return Input source signal.
  * @note   Function will return @ref HAL_PLAY_IN_SOURCE_INVALID if the parameters are invalid.
  */
HAL_PLAY_IN_SourceTypeDef HAL_PLAY_INPUT_GetSource(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef input_mux)
{
  const PLAY_TypeDef *p_playx;

  /* Check the parameters */
  if (hplay == NULL)
  {
    /* Return 0 as default value */
    return HAL_PLAY_IN_SOURCE_INVALID;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    /* Return 0 as default value */
    return HAL_PLAY_IN_SOURCE_INVALID;
  }

  assert_param(IS_PLAY_IN_ID(input_mux));

  /* Rebuild the source signal */
  uint32_t instance_id = (uint32_t)PLAY_GET_INSTANCE_ID(hplay);
  uint32_t mux_sel = (uint32_t)input_mux << HAL_PLAY_IN_MUX_POS;
  uint32_t source = LL_PLAY_INPUT_GetSource(p_playx, (uint32_t)input_mux);

  uint32_t ret = (instance_id | mux_sel | source);

  return (HAL_PLAY_IN_SourceTypeDef)ret;
}

/**
  * @brief  Set the minimum pulse width for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  input_mux Input multiplexer.
  * @param  width     Pulse width in play_clk clock cycles, in range [0..255].
  *                   Value 0 means that the filter is bypassed.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter or current state is not @ref HAL_PLAY_STATE_READY.
  */
HAL_StatusTypeDef HAL_PLAY_INPUT_SetMinPulseWidth(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef input_mux,
                                                  uint32_t width)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_IN_ID(input_mux));
  assert_param(IS_PLAY_MIN_PULSE_WIDTH(width));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  LL_PLAY_INPUT_SetMinimumPulseWidth(p_playx, (uint32_t)input_mux, width);

  return HAL_OK;
}

/**
  * @brief  Retrieve the minimum pulse width configured for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  input_mux Input multiplexer.
  * @return Pulse width in play_clk clock cycles, in range [0..255]. Value 0 means that the filter is bypassed.
  * @note   Function will return 0 if the parameters are invalid.
  */
uint32_t HAL_PLAY_INPUT_GetMinPulseWidth(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef input_mux)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return 0U;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    return 0U;
  }

  assert_param(IS_PLAY_IN_ID(input_mux));

  return LL_PLAY_INPUT_GetMinimumPulseWidth(p_playx, (uint32_t)input_mux);
}

/**
  * @brief  Configure the edge detection mode for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  input_mux Input multiplexer.
  * @param  mode      Mode of Edge Detection.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter or current state is not @ref HAL_PLAY_STATE_READY.
  */
HAL_StatusTypeDef HAL_PLAY_INPUT_SetEdgeDetectionMode(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_INTypeDef input_mux,
                                                      HAL_PLAY_EdgeDetectionModeTypeDef mode)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_IN_ID(input_mux));
  assert_param(IS_PLAY_EDGE_DETECTION_MODE(mode));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  LL_PLAY_INPUT_SetEdgeDetectionMode(p_playx, (uint32_t)input_mux, (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Retrieve the edge detection mode configured for an input filter of the PLAY peripheral.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  input_mux Input multiplexer.
  * @return Edge Detection mode.
  * @note   Function will return @ref HAL_PLAY_EDGE_DETECTION_BYPASSED if the parameters are invalid.
  */
HAL_PLAY_EdgeDetectionModeTypeDef HAL_PLAY_INPUT_GetEdgeDetectionMode(const HAL_PLAY_HandleTypeDef *hplay,
                                                                      HAL_PLAY_INTypeDef input_mux)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return HAL_PLAY_EDGE_DETECTION_BYPASSED as default value */
    return HAL_PLAY_EDGE_DETECTION_BYPASSED;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    /* Return HAL_PLAY_EDGE_DETECTION_BYPASSED as default value */
    return HAL_PLAY_EDGE_DETECTION_BYPASSED;
  }

  assert_param(IS_PLAY_IN_ID(input_mux));

  return (HAL_PLAY_EdgeDetectionModeTypeDef)LL_PLAY_INPUT_GetEdgeDetectionMode(p_playx, (uint32_t)input_mux);
}

/* PLAY Configuration - Unitary functions for lookup table *********************/

/**
  * @brief  Set the truth table value for a lookup table in the PLAY peripheral.
  * @param  hplay             Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  lut               Lookup table.
  * @param  truth_table_value The value can be in range [0..0xFFFF].
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter or current state is not @ref HAL_PLAY_STATE_READY.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_SetTruthTable(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                             uint32_t truth_table_value)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_LUT(p_playx, lut));
  assert_param(IS_PLAY_LUT_TRUTH_TABLE_VALUE(truth_table_value));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  /* Set the LUT value */
  LL_PLAY_LUT_SetTruthTable(p_playx, (uint32_t)lut, truth_table_value);

  return HAL_OK;
}

/**
  * @brief  Retrieve the truth table value for a lookup table in the PLAY peripheral.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  lut   Lookup table.
  * @return Value in range [0..0xFFFF].
  * @note   Function will return 0 if the parameters are invalid.
  */
uint32_t HAL_PLAY_LUT_GetTruthTable(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return 0 as default value */
    return 0U;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    /* Return 0 as default value */
    return 0U;
  }

  assert_param(IS_PLAY_LUT(p_playx, lut));

  return LL_PLAY_LUT_GetTruthTable(p_playx, (uint32_t)lut);
}

/**
  * @brief  Set the signal source for a lookup table input in the PLAY peripheral.
  * @param  hplay        Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  lut          Lookup table.
  * @param  lut_input    Lookup table Input.
  * @param  input_source Signal source.
  * @retval HAL_OK       Operation completed successfully.
  * @retval HAL_ERROR    Invalid parameter or current state is not @ref HAL_PLAY_STATE_READY.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_SetSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                         HAL_PLAY_LUT_InputTypeDef lut_input,
                                         HAL_PLAY_LUT_InputSourceTypeDef input_source)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_LUT(p_playx, lut));
  assert_param(IS_PLAY_LUT_INPUT(lut_input));
  assert_param(IS_PLAY_LUT_INPUT_SOURCE(p_playx, lut, input_source));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  LL_PLAY_LUT_SetSource(p_playx, (uint32_t)lut, (uint32_t)lut_input, (uint32_t)input_source);

  return HAL_OK;
}

/**
  * @brief  Retrieve the signal source for a lookup table input in the PLAY peripheral.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  lut       Lookup table.
  * @param  lut_input Lookup table Input.
  * @return Lookup table input source.
  * @note   Function will return @ref HAL_PLAY_LUT_INPUT_DEFAULT if the parameters are invalid.
  */
HAL_PLAY_LUT_InputSourceTypeDef HAL_PLAY_LUT_GetSource(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                                       HAL_PLAY_LUT_InputTypeDef lut_input)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return HAL_PLAY_LUT_INPUT_DEFAULT as default value */
    return HAL_PLAY_LUT_INPUT_DEFAULT;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    /* Return HAL_PLAY_LUT_INPUT_DEFAULT as default value */
    return HAL_PLAY_LUT_INPUT_DEFAULT;
  }

  assert_param(IS_PLAY_LUT(p_playx, lut));
  assert_param(IS_PLAY_LUT_INPUT(lut_input));

  return (HAL_PLAY_LUT_InputSourceTypeDef)LL_PLAY_LUT_GetSource(p_playx, (uint32_t)lut, (uint32_t)lut_input);
}

/**
  * @brief  Set the clock gate source for a lookup table in the PLAY peripheral.
  * @param  hplay  Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  lut    Lookup table.
  * @param  source Signal source.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter or current state is not @ref HAL_PLAY_STATE_READY.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_SetClockGateSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_LUTTypeDef lut,
                                                  HAL_PLAY_LUT_ClkGateSourceTypeDef source)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_LUT(p_playx, lut));
  assert_param(IS_PLAY_LUT_CLOCK_GATE_SOURCE(p_playx, source));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  LL_PLAY_LUT_SetClockGate(p_playx, (uint32_t)lut, (uint32_t)source);

  return HAL_OK;
}

/**
  * @brief  Retrieve the clock gate source for a lookup table in the PLAY peripheral.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  lut   Lookup table.
  * @return Lookup table clock gate source.
  * @note   Function will return @ref HAL_PLAY_LUT_CLK_GATE_OFF if the parameters are invalid.
  */
HAL_PLAY_LUT_ClkGateSourceTypeDef HAL_PLAY_LUT_GetClockGateSource(const HAL_PLAY_HandleTypeDef *hplay,
                                                                  HAL_PLAY_LUTTypeDef lut)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return HAL_PLAY_LUT_CLK_GATE_OFF as default value */
    return HAL_PLAY_LUT_CLK_GATE_OFF;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    /* Return HAL_PLAY_LUT_CLK_GATE_OFF as default value */
    return HAL_PLAY_LUT_CLK_GATE_OFF;
  }

  assert_param(IS_PLAY_LUT(p_playx, lut));

  return (HAL_PLAY_LUT_ClkGateSourceTypeDef)LL_PLAY_LUT_GetClockGate(p_playx, (uint32_t)lut);
}

/* PLAY Configuration - Unitary functions for output ****************************/

/**
  * @brief  Set the source signal for an output multiplexer of the PLAY peripheral.
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  output_mux Output multiplexer.
  * @param  source     Lookup table output. This parameter can be one of the following values:
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
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter or current state is not @ref HAL_PLAY_STATE_READY.
  */
HAL_StatusTypeDef HAL_PLAY_OUTPUT_SetSource(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_OUTTypeDef output_mux,
                                            uint32_t source)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_OUT(output_mux));
  assert_param(IS_PLAY_OUT_SOURCE(p_playx, source));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  LL_PLAY_OUTPUT_SetSource(p_playx, (uint32_t)output_mux, source);

  return HAL_OK;
}

/**
  * @brief  Retrieve the source signal configured for an output multiplexer of the PLAY peripheral.
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  output_mux Output multiplexer.
  * @note   Function will return 0 if the parameters are invalid.
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
uint32_t HAL_PLAY_OUTPUT_GetSource(const HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_OUTTypeDef output_mux)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return 0 as default value */
    return 0U;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    /* Return 0 as default value */
    return 0U;
  }

  assert_param(IS_PLAY_OUT(output_mux));

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
  * @param  hplay    Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config Pointer to a @ref HAL_PLAY_EdgeTriggerConfTypeDef.
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_Start(HAL_PLAY_HandleTypeDef *hplay, const HAL_PLAY_EdgeTriggerConfTypeDef *p_config)
{
  PLAY_TypeDef *p_playx;
  uint32_t is_locked;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param((p_config->lut_out_falling_mask & p_config->lut_out_rising_mask) == 0U);

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_READY)
  {
    return HAL_ERROR;
  }

  /* Lock the configuration only if already done.
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

  hplay->global_state = HAL_PLAY_STATE_BUSY;

  return PLAY_LUT_SetEdgeTrigger(hplay, p_config, PLAY_WRITE_TIMEOUT_MS);
}

/**
  * @brief  Stop the PLAY peripheral.
  *         The API disables all the lookup table output Interrupts and unlocks the configuration registers.
  *         All features having a dependency with the kernel clock are held in reset.
  * @param  hplay  Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter or wrong state.
  */
HAL_StatusTypeDef HAL_PLAY_Stop(HAL_PLAY_HandleTypeDef *hplay)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

  /* Disable all lookup table Output Interrupts */
  LL_PLAY_LUT_DisableIT(p_playx, LL_PLAY_LUT_ALL_OUT_REGISTERED | LL_PLAY_LUT_ALL_OUT_DIRECT);

  LL_PLAY_Unlock(p_playx);

  hplay->global_state = HAL_PLAY_STATE_READY;

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
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config   Pointer to a @ref HAL_PLAY_EdgeTriggerConfTypeDef structure for the Edge Triggers configuration.
  * @param  timeout_ms Timeout duration (in ms).
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter.
  * @retval HAL_BUSY  A write is pending.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_SetEdgeTrigger(HAL_PLAY_HandleTypeDef *hplay,
                                              const HAL_PLAY_EdgeTriggerConfTypeDef *p_config,
                                              uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param((p_config->lut_out_falling_mask & p_config->lut_out_rising_mask) == 0U);

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

  return PLAY_LUT_SetEdgeTrigger(hplay, p_config, timeout_ms);
}

/**
  * @brief  Configure the Edge Triggers in  mode: flag transition of lookup table outputs.
  * @param  hplay    Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config Pointer to a @ref HAL_PLAY_EdgeTriggerConfTypeDef structure for the Edge Triggers configuration.
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter.
  * @retval HAL_BUSY  A write is pending.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_SetEdgeTrigger_IT(HAL_PLAY_HandleTypeDef *hplay,
                                                 const HAL_PLAY_EdgeTriggerConfTypeDef *p_config)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param((p_config->lut_out_falling_mask & p_config->lut_out_rising_mask) == 0U);

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

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
  * @param  hplay    Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config Pointer to a @ref HAL_PLAY_EdgeTriggerConfTypeDef structure to be filled.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_GetEdgeTrigger(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_EdgeTriggerConfTypeDef *p_config)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

  /* Retrieve the configuration */
  p_config->lut_out_rising_mask = LL_PLAY_LUT_GetEdgeTrigger(p_playx);
  p_config->lut_out_falling_mask = ~p_config->lut_out_rising_mask;

  return HAL_OK;
}

/**
  * @brief  Poll on Lookup table Output Flags.
  * @param  hplay                   Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  poll_mode               Polling mode of type @ref HAL_PLAY_PollingEdgeTriggerTypeDef.
  * @param  edge_trig_mask          Mask of flags to poll.
  *                                 This parameter can be a combination of the following values:
  *                                 @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :        The Flag of LUT0 direct output
  *                                 @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :        The Flag of LUT1 direct output
  *                                 @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :        The Flag of LUT2 direct output
  *                                 @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :        The Flag of LUT3 direct output
  *                                 @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :        The Flag of LUT4 direct output
  *                                 @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :        The Flag of LUT5 direct output
  *                                 @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :        The Flag of LUT6 direct output
  *                                 @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :        The Flag of LUT7 direct output
  *                                 @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :        The Flag of LUT8 direct output
  *                                 @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :        The Flag of LUT9 direct output
  *                                 @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :       The Flag of LUT10 direct output
  *                                 @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :       The Flag of LUT11 direct output
  *                                 @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :       The Flag of LUT12 direct output
  *                                 @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :       The Flag of LUT13 direct output
  *                                 @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :       The Flag of LUT14 direct output
  *                                 @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :       The Flag of LUT15 direct output
  *                                 @arg @ref HAL_PLAY_LUT_ALL_OUT_DIRECT :     All Flags of LUTs direct outputs
  *                                 @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :    The Flag of LUT0 registered output
  *                                 @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :    The Flag of LUT1 registered output
  *                                 @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :    The Flag of LUT2 registered output
  *                                 @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :    The Flag of LUT3 registered output
  *                                 @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :    The Flag of LUT4 registered output
  *                                 @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :    The Flag of LUT5 registered output
  *                                 @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :    The Flag of LUT6 registered output
  *                                 @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :    The Flag of LUT7 registered output
  *                                 @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :    The Flag of LUT8 registered output
  *                                 @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :    The Flag of LUT9 registered output
  *                                 @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED :   The Flag of LUT10 registered output
  *                                 @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED :   The Flag of LUT11 registered output
  *                                 @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED :   The Flag of LUT12 registered output
  *                                 @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED :   The Flag of LUT13 registered output
  *                                 @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED :   The Flag of LUT14 registered output
  *                                 @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED :   The Flag of LUT15 registered output
  *                                 @arg @ref HAL_PLAY_LUT_ALL_OUT_REGISTERED : All Flags of LUTs registered outputs
  * @param  timeout_ms              Timeout duration (in ms).
  * @param  p_edge_trig_mask_status Pointer to return the triggered lookup table output flags.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_TIMEOUT Operation timed out.
  * @retval HAL_ERROR   Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_PollForEdgeTrigger(HAL_PLAY_HandleTypeDef *hplay,
                                                  HAL_PLAY_PollingEdgeTriggerTypeDef poll_mode,
                                                  uint32_t edge_trig_mask, uint32_t *p_edge_trig_mask_status,
                                                  uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;
  uint32_t tickstart;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;


    /* Return error status */
    return HAL_ERROR;
  }

  assert_param(IS_PLAY_POLL_MODE(poll_mode));
  assert_param((edge_trig_mask != 0U));
  assert_param((p_edge_trig_mask_status != NULL));

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

  /* Check the peripheral state */
  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

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
  * @param  hplay    Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  its_mask Mask of lookup table output interrupt to enable.
  *                  This parameter can be a combination of the following values:
  *                  @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :        The Interrupt of LUT0 direct output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :        The Interrupt of LUT1 direct output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :        The Interrupt of LUT2 direct output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :        The Interrupt of LUT3 direct output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :        The Interrupt of LUT4 direct output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :        The Interrupt of LUT5 direct output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :        The Interrupt of LUT6 direct output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :        The Interrupt of LUT7 direct output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :        The Interrupt of LUT8 direct output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :        The Interrupt of LUT9 direct output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :       The Interrupt of LUT10 direct output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :       The Interrupt of LUT11 direct output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :       The Interrupt of LUT12 direct output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :       The Interrupt of LUT13 direct output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :       The Interrupt of LUT14 direct output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :       The Interrupt of LUT15 direct output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_DIRECT :     All Interrupts of LUTs direct outputs
  *                  @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :    The Interrupt of LUT0 registered output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :    The Interrupt of LUT1 registered output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :    The Interrupt of LUT2 registered output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :    The Interrupt of LUT3 registered output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :    The Interrupt of LUT4 registered output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :    The Interrupt of LUT5 registered output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :    The Interrupt of LUT6 registered output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :    The Interrupt of LUT7 registered output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :    The Interrupt of LUT8 registered output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :    The Interrupt of LUT9 registered output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED :   The Interrupt of LUT10 registered output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED :   The Interrupt of LUT11 registered output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED :   The Interrupt of LUT12 registered output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED :   The Interrupt of LUT13 registered output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED :   The Interrupt of LUT14 registered output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED :   The Interrupt of LUT15 registered output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_REGISTERED : All Interrupts of LUTs registered outputs
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_EnableIT(HAL_PLAY_HandleTypeDef *hplay, uint32_t its_mask)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param((its_mask != 0U));

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

  LL_PLAY_LUT_EnableIT(p_playx, its_mask);

  return HAL_OK;
}

/**
  * @brief  Disable a set of lookup table output Interrupts.
  * @param  hplay    Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  its_mask Mask of lookup table output interrupt to disable
  *                  This parameter can be a combination of the following values:
  *                  @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :        The Interrupt of LUT0 direct output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :        The Interrupt of LUT1 direct output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :        The Interrupt of LUT2 direct output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :        The Interrupt of LUT3 direct output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :        The Interrupt of LUT4 direct output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :        The Interrupt of LUT5 direct output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :        The Interrupt of LUT6 direct output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :        The Interrupt of LUT7 direct output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :        The Interrupt of LUT8 direct output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :        The Interrupt of LUT9 direct output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :       The Interrupt of LUT10 direct output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :       The Interrupt of LUT11 direct output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :       The Interrupt of LUT12 direct output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :       The Interrupt of LUT13 direct output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :       The Interrupt of LUT14 direct output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :       The Interrupt of LUT15 direct output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_DIRECT :     All Interrupts of LUTs direct outputs
  *                  @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :    The Interrupt of LUT0 registered output
  *                  @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :    The Interrupt of LUT1 registered output
  *                  @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :    The Interrupt of LUT2 registered output
  *                  @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :    The Interrupt of LUT3 registered output
  *                  @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :    The Interrupt of LUT4 registered output
  *                  @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :    The Interrupt of LUT5 registered output
  *                  @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :    The Interrupt of LUT6 registered output
  *                  @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :    The Interrupt of LUT7 registered output
  *                  @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :    The Interrupt of LUT8 registered output
  *                  @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :    The Interrupt of LUT9 registered output
  *                  @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED :   The Interrupt of LUT10 registered output
  *                  @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED :   The Interrupt of LUT11 registered output
  *                  @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED :   The Interrupt of LUT12 registered output
  *                  @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED :   The Interrupt of LUT13 registered output
  *                  @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED :   The Interrupt of LUT14 registered output
  *                  @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED :   The Interrupt of LUT15 registered output
  *                  @arg @ref HAL_PLAY_LUT_ALL_OUT_REGISTERED : All Interrupts of LUTs registered outputs
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_ERROR Invalid parameter.
  */
HAL_StatusTypeDef HAL_PLAY_LUT_DisableIT(HAL_PLAY_HandleTypeDef *hplay, uint32_t its_mask)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

  LL_PLAY_LUT_DisableIT(p_playx, its_mask);

  return HAL_OK;
}

/**
  * @brief  Get the enabled lookup table output interrupts.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @return Mask of enabled lookup table output interrupts.
  *         This returned parameter can be a combination of the following values:
  *         @arg @ref HAL_PLAY_LUT0_OUT_DIRECT :      The Interrupt of LUT0 direct output
  *         @arg @ref HAL_PLAY_LUT1_OUT_DIRECT :      The Interrupt of LUT1 direct output
  *         @arg @ref HAL_PLAY_LUT2_OUT_DIRECT :      The Interrupt of LUT2 direct output
  *         @arg @ref HAL_PLAY_LUT3_OUT_DIRECT :      The Interrupt of LUT3 direct output
  *         @arg @ref HAL_PLAY_LUT4_OUT_DIRECT :      The Interrupt of LUT4 direct output
  *         @arg @ref HAL_PLAY_LUT5_OUT_DIRECT :      The Interrupt of LUT5 direct output
  *         @arg @ref HAL_PLAY_LUT6_OUT_DIRECT :      The Interrupt of LUT6 direct output
  *         @arg @ref HAL_PLAY_LUT7_OUT_DIRECT :      The Interrupt of LUT7 direct output
  *         @arg @ref HAL_PLAY_LUT8_OUT_DIRECT :      The Interrupt of LUT8 direct output
  *         @arg @ref HAL_PLAY_LUT9_OUT_DIRECT :      The Interrupt of LUT9 direct output
  *         @arg @ref HAL_PLAY_LUT10_OUT_DIRECT :     The Interrupt of LUT10 direct output
  *         @arg @ref HAL_PLAY_LUT11_OUT_DIRECT :     The Interrupt of LUT11 direct output
  *         @arg @ref HAL_PLAY_LUT12_OUT_DIRECT :     The Interrupt of LUT12 direct output
  *         @arg @ref HAL_PLAY_LUT13_OUT_DIRECT :     The Interrupt of LUT13 direct output
  *         @arg @ref HAL_PLAY_LUT14_OUT_DIRECT :     The Interrupt of LUT14 direct output
  *         @arg @ref HAL_PLAY_LUT15_OUT_DIRECT :     The Interrupt of LUT15 direct output
  *         @arg @ref HAL_PLAY_LUT0_OUT_REGISTERED :  The Interrupt of LUT0 registered output
  *         @arg @ref HAL_PLAY_LUT1_OUT_REGISTERED :  The Interrupt of LUT1 registered output
  *         @arg @ref HAL_PLAY_LUT2_OUT_REGISTERED :  The Interrupt of LUT2 registered output
  *         @arg @ref HAL_PLAY_LUT3_OUT_REGISTERED :  The Interrupt of LUT3 registered output
  *         @arg @ref HAL_PLAY_LUT4_OUT_REGISTERED :  The Interrupt of LUT4 registered output
  *         @arg @ref HAL_PLAY_LUT5_OUT_REGISTERED :  The Interrupt of LUT5 registered output
  *         @arg @ref HAL_PLAY_LUT6_OUT_REGISTERED :  The Interrupt of LUT6 registered output
  *         @arg @ref HAL_PLAY_LUT7_OUT_REGISTERED :  The Interrupt of LUT7 registered output
  *         @arg @ref HAL_PLAY_LUT8_OUT_REGISTERED :  The Interrupt of LUT8 registered output
  *         @arg @ref HAL_PLAY_LUT9_OUT_REGISTERED :  The Interrupt of LUT9 registered output
  *         @arg @ref HAL_PLAY_LUT10_OUT_REGISTERED : The Interrupt of LUT10 registered output
  *         @arg @ref HAL_PLAY_LUT11_OUT_REGISTERED : The Interrupt of LUT11 registered output
  *         @arg @ref HAL_PLAY_LUT12_OUT_REGISTERED : The Interrupt of LUT12 registered output
  *         @arg @ref HAL_PLAY_LUT13_OUT_REGISTERED : The Interrupt of LUT13 registered output
  *         @arg @ref HAL_PLAY_LUT14_OUT_REGISTERED : The Interrupt of LUT14 registered output
  *         @arg @ref HAL_PLAY_LUT15_OUT_REGISTERED : The Interrupt of LUT15 registered output
  */
uint32_t HAL_PLAY_LUT_GetIT(const HAL_PLAY_HandleTypeDef *hplay)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return 0U;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    return 0U;
  }

  return LL_PLAY_LUT_GetIT(p_playx);
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
  * @param  hplay       Pointer to a @ref HAL_PLAY_HandleTypeDef.
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
  * @param  state       State to set of type @ref HAL_PLAY_SWTriggerStateTypeDef.
  * @param  timeout_ms  Timeout duration (in ms).
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_ERROR   Invalid parameter.
  * @retval HAL_BUSY    A write is pending.
  * @retval HAL_TIMEOUT Timeout reached.
  */
HAL_StatusTypeDef HAL_PLAY_WriteSWTrigger(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers,
                                          HAL_PLAY_SWTriggerStateTypeDef state, uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(IS_PLAY_SWTRIGGER_MSK(sw_triggers));

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

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
  * @param  hplay       Pointer to a @ref HAL_PLAY_HandleTypeDef.
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
  * @param  state       State to set of type @ref HAL_PLAY_SWTriggerStateTypeDef.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_ERROR   Invalid parameter.
  * @retval HAL_BUSY    A write is pending.
  */
HAL_StatusTypeDef HAL_PLAY_WriteSWTrigger_IT(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers,
                                             HAL_PLAY_SWTriggerStateTypeDef state)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(IS_PLAY_SWTRIGGER_MSK(sw_triggers));

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

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
  * @param  hplay       Pointer to a @ref HAL_PLAY_HandleTypeDef.
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
  * @retval HAL_ERROR   Invalid parameter.
  * @retval HAL_BUSY    A write is pending.
  * @retval HAL_TIMEOUT Timeout reached.
  */
HAL_StatusTypeDef HAL_PLAY_ToggleSWTrigger(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers, uint32_t timeout_ms)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(IS_PLAY_SWTRIGGER_MSK(sw_triggers));

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

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
  * @param  hplay       Pointer to a @ref HAL_PLAY_HandleTypeDef.
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
  * @retval HAL_ERROR   Invalid parameter.
  * @retval HAL_BUSY    A write is pending.
  */
HAL_StatusTypeDef HAL_PLAY_ToggleSWTrigger_IT(HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_triggers)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(IS_PLAY_SWTRIGGER_MSK(sw_triggers));

  if (hplay->global_state != HAL_PLAY_STATE_BUSY)
  {
    return HAL_ERROR;
  }

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
  * @param  hplay   Pointer to a @ref HAL_PLAY_HandleTypeDef.
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
  * @note   This function will return HAL_PLAY_SW_TRIGGER_RESET in case of wrong parameter.
  * @return State of Software Trigger.
  */
HAL_PLAY_SWTriggerStateTypeDef HAL_PLAY_ReadSWTrigger(const HAL_PLAY_HandleTypeDef *hplay, uint32_t sw_trig)
{
  const PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return HAL_PLAY_SW_TRIGGER_RESET as default value */
    return HAL_PLAY_SW_TRIGGER_RESET;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_playx == NULL)
  {
    /* Return HAL_PLAY_SW_TRIGGER_RESET as default value */
    return HAL_PLAY_SW_TRIGGER_RESET;
  }

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(hplay->instance));

  /* Read the SW Trigger values */
  return ((LL_PLAY_IsSWTriggerSet(p_playx, sw_trig) != 0U) ? HAL_PLAY_SW_TRIGGER_SET : HAL_PLAY_SW_TRIGGER_RESET);
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
  - Depending on the process function used, different callback might be triggered:

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
  - HAL_PLAY_RegisterCallback()
  - HAL_PLAY_RegisterLUTOutputCallback()
  - HAL_PLAY_UnRegisterCallback()
  - HAL_PLAY_UnRegisterLUTOutputCallback()
  */

/**
  * @brief Handle PLAY interrupt request.
  * @param hplay  Pointer to a @ref HAL_PLAY_HandleTypeDef.
  */
void HAL_PLAY_IRQHandler(HAL_PLAY_HandleTypeDef *hplay)
{
  PLAY_TypeDef *p_playx;

  p_playx = PLAY_GET_INSTANCE(hplay);
  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

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
  if (IS_PLAY_BIT_SET(reg_misr, PLAY_IT_STATUS_SW_TRIGGER_WRITE_COMPLETE))
  {
    LL_PLAY_ClearFlag_SWTriggerWriteComplete(p_playx);

    LL_PLAY_DisableIT_SWTriggerWriteComplete(p_playx);

    /* Call the callback */
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
    hplay->SWTriggerWriteCpltCallback(hplay);
#else
    HAL_PLAY_SWTriggerWriteCpltCallback(hplay);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
  }

  /* Check Edge Trigger write complete interrupt */
  if (IS_PLAY_BIT_SET(reg_misr, PLAY_IT_STATUS_EDGE_TRIGGER_WRITE_COMPLETE))
  {
    LL_PLAY_LUT_ClearFlag_EdgeTriggerWriteComplete(p_playx);

    LL_PLAY_LUT_DisableIT_EdgeTriggerWriteComplete(p_playx);

    /* Call the callback */
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
    hplay->EdgeTriggerWriteCpltCallback(hplay);
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
      hplay->LUTOutputRisingCallback(hplay, mask_flag_rising);
#else
      HAL_PLAY_LUTOutputRisingCallback(hplay, mask_flag_rising);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
    }

    if (mask_flag_falling > 0U)
    {
#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
      hplay->LUTOutputFallingCallback(hplay, mask_flag_falling);
#else
      HAL_PLAY_LUTOutputFallingCallback(hplay, mask_flag_falling);
#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS */
    }

  }
}

/**
  * @brief   Callback for Software Trigger write complete.
  * @param   hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_PLAY_SWTriggerWriteCpltCallback(HAL_PLAY_HandleTypeDef *hplay)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_PLAY_SWTriggerWriteCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief   Callback for Edge Trigger write complete.
  * @param   hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_PLAY_EdgeTriggerWriteCpltCallback(HAL_PLAY_HandleTypeDef *hplay)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_PLAY_EdgeTriggerWriteCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief   Callback for lookup table output rising edge.
  * @param   hplay                 Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param   edge_trig_mask_status Mask of lookup table output triggered on a rising edge.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__weak void HAL_PLAY_LUTOutputRisingCallback(HAL_PLAY_HandleTypeDef *hplay, uint32_t edge_trig_mask_status)
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
  * @param   hplay                 Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param   edge_trig_mask_status Mask of lookup table output triggered on a falling edge
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_PLAY_LUTOutputFallingCallback(HAL_PLAY_HandleTypeDef *hplay, uint32_t edge_trig_mask_status)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hplay);
  UNUSED(edge_trig_mask_status);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_PLAY_LUTOutputFallingCallback must be implemented in the user file.
   */
}

#if (USE_HAL_PLAY_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register an User PLAY Callback.
  * @note   The User PLAY Callback is to be used instead of the weak predefined callback.
  * @param  hplay  Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  CallbackID  ID of the callback to be registered.
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_PLAY_SW_TRIGGER_WRITE_CPLT_CB_ID SWIN Write Complete callback ID
  *          @arg @ref HAL_PLAY_EDGE_TRIGGER_WRITE_CPLT_CB_ID Edge Trigger Write Complete callback ID
  *          @arg @ref HAL_PLAY_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_PLAY_MSPDEINIT_CB_ID MspDeInit callback ID
  * @param  pCallback  Pointer to the callback function.
  * @note   The HAL_PLAY_RegisterCallback() may be called before HAL_PLAY_Init() in HAL_PLAY_STATE_RESET
  *         to register callbacks for HAL_PLAY_MSPINIT_CB_ID and HAL_PLAY_MSPDEINIT_CB_ID only.
  * @return HAL status.
  */
HAL_StatusTypeDef HAL_PLAY_RegisterCallback(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_CallbackIDTypeDef CallbackID,
                                            pPLAY_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the PLAY handle allocation */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(hplay->instance));

  if (pCallback == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (hplay->global_state == HAL_PLAY_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_PLAY_SW_TRIGGER_WRITE_CPLT_CB_ID:
        hplay->SWTriggerWriteCpltCallback = pCallback;
        break;

      case HAL_PLAY_EDGE_TRIGGER_WRITE_CPLT_CB_ID:
        hplay->EdgeTriggerWriteCpltCallback = pCallback;
        break;

      case HAL_PLAY_MSPINIT_CB_ID:
        hplay->MspInitCallback = pCallback;
        break;

      case HAL_PLAY_MSPDEINIT_CB_ID:
        hplay->MspDeInitCallback = pCallback;
        break;

      default :
        hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;

        status = HAL_ERROR;
        break;
    }
  }
  else if (hplay->global_state == HAL_PLAY_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_PLAY_MSPINIT_CB_ID:
        hplay->MspInitCallback = pCallback;
        break;

      case HAL_PLAY_MSPDEINIT_CB_ID:
        hplay->MspDeInitCallback = pCallback;
        break;

      default :
        hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;

        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;

    status = HAL_ERROR;
  }

  /* Return error status */
  return status;
}

/**
  * @brief  Register a User PLAY LUT Output Callback.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  CallbackID  ID of the callback to be registered.
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_PLAY_LUT_OUTPUT_RISING_CB_ID LUT output rising callback ID
  *          @arg @ref HAL_PLAY_LUT_OUTPUT_FALLING_CB_ID LUT output falling callback ID
  * @param  pCallback  Pointer to the callback function.
  * @note   The User PLAY Callback is to be used instead of the weak predefined callback.
  * @return HAL status.
  */
HAL_StatusTypeDef HAL_PLAY_RegisterLUTOutputCallback(HAL_PLAY_HandleTypeDef *hplay,
                                                     HAL_PLAY_CallbackIDTypeDef CallbackID,
                                                     pPLAY_LUTOutputCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the PLAY handle allocation */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(PLAY_GET_INSTANCE(hplay)));

  if (pCallback == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  if (hplay->global_state == HAL_PLAY_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_PLAY_LUT_OUTPUT_RISING_CB_ID:
        hplay->LUTOutputRisingCallback = pCallback;
        break;

      case HAL_PLAY_LUT_OUTPUT_FALLING_CB_ID:
        hplay->LUTOutputFallingCallback = pCallback;
        break;

      default :

        hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;

        status = HAL_ERROR;
        break;
    }
  }
  else
  {

    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;

    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Unregister an User PLAY Callback.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  CallbackID  ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_PLAY_SW_TRIGGER_WRITE_CPLT_CB_ID SW trigger write complete callback ID
  *          @arg @ref HAL_PLAY_EDGE_TRIGGER_WRITE_CPLT_CB_ID Edge trigger write complete callback ID
  *          @arg @ref HAL_PLAY_MSPINIT_CB_ID MspInit callback ID
  *          @arg @ref HAL_PLAY_MSPDEINIT_CB_ID MspDeInit callback ID
  * @note   The PLAY callback is redirected to the weak predefined callback.
  * @note   The HAL_PLAY_UnRegisterCallback() can be called before HAL_PLAY_Init() in HAL_PLAY_STATE_RESET
  *         to unregister callbacks for HAL_PLAY_MSPINIT_CB_ID and HAL_PLAY_MSPDEINIT_CB_ID only.
  * @return HAL status.
  */
HAL_StatusTypeDef HAL_PLAY_UnRegisterCallback(HAL_PLAY_HandleTypeDef *hplay, HAL_PLAY_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the PLAY handle allocation */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(PLAY_GET_INSTANCE(hplay)));

  if (hplay->global_state == HAL_PLAY_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_PLAY_SW_TRIGGER_WRITE_CPLT_CB_ID:
        hplay->SWTriggerWriteCpltCallback = HAL_PLAY_SWTriggerWriteCpltCallback;
        break;

      case HAL_PLAY_EDGE_TRIGGER_WRITE_CPLT_CB_ID:
        hplay->EdgeTriggerWriteCpltCallback = HAL_PLAY_EdgeTriggerWriteCpltCallback;
        break;

      case HAL_PLAY_MSPINIT_CB_ID:
        hplay->MspInitCallback = HAL_PLAY_MspInit;      /* Legacy weak MspInit   */
        break;

      case HAL_PLAY_MSPDEINIT_CB_ID:
        hplay->MspDeInitCallback = HAL_PLAY_MspDeInit;  /* Legacy weak MspDeInit */
        break;

      default:
        /* Update the error code */
        hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;
        status = HAL_ERROR;
        break;
    }
  }
  else if (hplay->global_state == HAL_PLAY_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_PLAY_MSPINIT_CB_ID:
        hplay->MspInitCallback = HAL_PLAY_MspInit;      /* Legacy weak MspInit   */
        break;

      case HAL_PLAY_MSPDEINIT_CB_ID:
        hplay->MspDeInitCallback = HAL_PLAY_MspDeInit;  /* Legacy weak MspDeInit */
        break;

      default:
        /* Update the error code */
        hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Unregister a User PLAY LUT Output Callback.
  * @note   The PLAY callback is redirected to the weak predefined callback.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  CallbackID  ID of the callback to be unregistered
  *         This parameter can be one of the following values:
  *          @arg @ref HAL_PLAY_LUT_OUTPUT_RISING_CB_ID LUT output rising callback ID
  *          @arg @ref HAL_PLAY_LUT_OUTPUT_FALLING_CB_ID LUT output falling callback ID
  * @return HAL status.
  */
HAL_StatusTypeDef HAL_PLAY_UnRegisterLUTOutputCallback(HAL_PLAY_HandleTypeDef *hplay,
                                                       HAL_PLAY_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the PLAY handle allocation */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_PLAY_ALL_INSTANCE(PLAY_GET_INSTANCE(hplay)));

  if (hplay->global_state == HAL_PLAY_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_PLAY_LUT_OUTPUT_RISING_CB_ID:
        hplay->LUTOutputRisingCallback = HAL_PLAY_LUTOutputRisingCallback;
        break;

      case HAL_PLAY_LUT_OUTPUT_FALLING_CB_ID:
        hplay->LUTOutputFallingCallback = HAL_PLAY_LUTOutputFallingCallback;
        break;

      default :
        hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_CALLBACK;
    status = HAL_ERROR;
  }

  return status;
}

#endif /* USE_HAL_PLAY_REGISTER_CALLBACKS == 1 */
/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group7
  * @{
A set of functions allowing to retrieve peripheral state,last process errors and kernel clock frequency.
- HAL_PLAY_GetState() : Return the PLAY handle state.
- HAL_PLAY_GetError() : Returns errors limited to the last process.
  */
/**
  * @brief  Return the HAL PLAY handle state.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @return Current PLAY state.
  * @note   This function will return HAL_PLAY_STATE_RESET in case of wrong parameter.
  */
HAL_PLAY_StateTypeDef HAL_PLAY_GetState(const HAL_PLAY_HandleTypeDef *hplay)
{
  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return HAL_PLAY_STATE_RESET in case of wrong parameter */
    return HAL_PLAY_STATE_RESET;
  }

  return hplay->global_state;
}

/**
  * @brief  Get the HAL PLAY last error codes.
  * @param  hplay Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @note   This function will return 0 in case of wrong parameter.
  * @return PLAY Error Code.
  */
uint32_t HAL_PLAY_GetError(const HAL_PLAY_HandleTypeDef *hplay)
{
  /* Check parameters */
  if (hplay == NULL)
  {
    /* Return 0 in case of wrong parameter */
    return 0U;
  }

  return hplay->last_error_codes;
}

/**
  * @}
  */

/** @addtogroup PLAY_Exported_Functions_Group8
  * @{
  */
/**
  * @brief  Configure the Secure & Privilege attributes.
  * @param  hplay     Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config  Pointer to a @ref HAL_PLAY_AccessControlConfTypeDef structure
  * @return HAL status.
  */
HAL_StatusTypeDef HAL_PLAY_ConfigAttributes(HAL_PLAY_HandleTypeDef *hplay,
                                            const HAL_PLAY_AccessControlConfTypeDef *p_config)
{
  PLAY_TypeDef *p_playx;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  p_playx = PLAY_GET_INSTANCE(hplay);

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));
  assert_param(IS_PLAY_TZ_ACCESS_CONTROL(p_config->SecureAccess));
  assert_param(IS_PLAY_TZ_ACCESS_CONTROL(p_config->PrivilegeAccess));

  if (hplay->global_state != HAL_PLAY_STATE_RESET)
  {
    return HAL_ERROR;
  }

  /* Set Secure access */
  uint32_t reg_value = (uint32_t)(p_config->SecureAccess) << PLAY_SECCFGR_SEC_Pos;
  ATOMIC_MODIFY_REG(p_playx->SECCFGR, PLAY_SECCFGR_SEC, reg_value);

  /* Set Privilege access */
  reg_value = (uint32_t)(p_config->PrivilegeAccess) << PLAY_PRIVCFGR_PRIV_Pos;
  ATOMIC_MODIFY_REG(p_playx->PRIVCFGR, PLAY_PRIVCFGR_PRIV, reg_value);

  return HAL_OK;
}

/**
  * @brief  Get the Secure & Privilege attributes configuration.
  * @param  hplay    Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config Pointer to a @ref HAL_PLAY_AccessControlConfTypeDef structure.
  * @return HAL status.
  */
HAL_StatusTypeDef HAL_PLAY_GetConfigAttributes(HAL_PLAY_HandleTypeDef *hplay,
                                               HAL_PLAY_AccessControlConfTypeDef *p_config)
{
  const PLAY_TypeDef *p_playx;
  uint32_t reg_value;
  uint32_t sec_value;
  uint32_t priv_value;

  /* Check parameters */
  if (hplay == NULL)
  {
    return HAL_ERROR;
  }
  p_playx = PLAY_GET_INSTANCE(hplay);

  if (p_config == NULL)
  {
    hplay->last_error_codes |= HAL_PLAY_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  assert_param(IS_PLAY_ALL_INSTANCE(p_playx));

  /* Read Secure access */
  reg_value = READ_REG(p_playx->SECCFGR);
  sec_value = (reg_value & PLAY_SECCFGR_SEC_Msk) >> PLAY_SECCFGR_SEC_Pos;
  p_config->SecureAccess = (HAL_PLAY_TrustZone_AccessControlTypeDef)(sec_value);

  /* Read Privilege access */
  reg_value = READ_REG(p_playx->PRIVCFGR);
  priv_value = (reg_value & PLAY_PRIVCFGR_PRIV_Msk) >> PLAY_PRIVCFGR_PRIV_Pos;
  p_config->PrivilegeAccess = (HAL_PLAY_TrustZone_AccessControlTypeDef)(priv_value);

  return HAL_OK;
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
  * @param  hplay      Pointer to a @ref HAL_PLAY_HandleTypeDef.
  * @param  p_config   Pointer to a @ref HAL_PLAY_EdgeTriggerConfTypeDef structure for the Edge Triggers configuration.
  * @param  timeout_ms Timeout duration (in ms).
  * @note   The falling and rising edge configuration is exclusive and thus, a lookup table output cannot be
  *         configured for both rising and falling edges at the same time.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_BUSY    A write is pending.
  * @retval HAL_TIMEOUT Operation timed-out.
  */
static HAL_StatusTypeDef PLAY_LUT_SetEdgeTrigger(const HAL_PLAY_HandleTypeDef *hplay,
                                                 const HAL_PLAY_EdgeTriggerConfTypeDef *p_config,
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

#endif /* PLAY1 */
#endif /* HAL_PLAY_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
