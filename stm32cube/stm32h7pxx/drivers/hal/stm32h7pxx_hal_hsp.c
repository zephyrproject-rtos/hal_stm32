/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_hsp.c
  * @brief   HSP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Hardware Signal Processor (HSP) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Configuration functions
  *           + Peripheral State and Error functions
  *           + IRQ Handlers and Callback functions
  *           + Setter and Getter of the user data
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

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */
#if defined(HSP1)
#if defined(USE_HAL_HSP_MODULE) && (USE_HAL_HSP_MODULE == 1)

/** @addtogroup HSP
  * @{
  */
/** @defgroup HSP_Introduction HSP Introduction
  * @{

  - The Hardware Abstraction Layer (HAL) for HSP provides an efficient interface to the Hardware Signal Processor (HSP).
    The HSP is a dedicated signal-processing subsystem designed to offload computation-intensive and time-critical
    operations from the CPU. It accelerates functions commonly used in demanding embedded applications such as
    motor control, digital power, metering, audio processing, real-time signal conditioning,
    and small convolutional neural networks.

  - The HSP is built around a dedicated, high-performance Signal Processor Engine (SPE) capable of operating
    in 32-bit floating point or 8-bit integer modes.
    The Signal Processor Engine executes HSP-specific microcode (also referred to as Firmware), part of which is
    embedded in private ROM, while a second part (FW RAM) must be dynamically loaded into RAM during initialization.
    This Firmware RAM is delivered through the HSP_Engine middleware.

    The HSP also supports the loading of Plugins to:
      - patch or optimize existing processing function,
      - add new processing function.

  - The HAL HSP allows running processing functions in Accelerator mode or Sequencer mode.
    In Sequencer mode, it provides services to:
      - record a processing list (Sequence of processing functions)
      - attach a Processing List to a hardware trigger such as a DMA Transfer Complete, TIM Pulse...

  */

/**
  * @}
  */

/** @defgroup HSP_How_To_Use HSP How To Use
  * @{

# How to use the HSP HAL module driver

## Usage

1. Declare a hal_hsp_handle_t handle and initialize the HSP driver with an HSP instance by calling HAL_HSP_Init().
  The HSP clock is enabled inside HAL_HSP_Init() if USE_HAL_HSP_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

2. Configure the low-level hardware (CLOCK, NVIC...):
  - Enable the HSP clock if USE_HAL_HSP_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO.
  - HSPx pins configuration:
      - Enable the clock for the HSPx GPIOs
      - Configure HSPx pins as alternate function open - drain
  - NVIC configuration if you need to use HSP interrupt process:
      - Either use only the global IRQ line (hsp_it) as follows:
        - Configure the HSP interrupt priority by calling HAL_CORTEX_NVIC_SetPriority().
        - Enable the HSP IRQ handler by calling HAL_CORTEX_NVIC_EnableIRQ().
        - In HSP IRQ handler, call HAL_HSP_IRQHandler()
      - Or use the 3 HSP IRQ lines (hsp_err_it, hsp_evt_it and hsp_fwevt_it) as follows:
        - Configure the 3 HSP interrupts priority by calling HAL_CORTEX_NVIC_SetPriority().
        - Enable the 3 HSP IRQ handlers by calling HAL_CORTEX_NVIC_EnableIRQ().
        - In HSP Error IRQ handler, call HAL_HSP_ERR_IRQHandler(),
        - In HSP Event IRQ handler, call HAL_HSP_EVT_IRQHandler(),
        - In HSP FWEvent IRQ handler, call HAL_HSP_FWEVT_IRQHandler(),

3. Load the Firmware Code part & Data part with HAL_HSP_LoadFirmware().
  The Firmware is based on the Firmware Code Part version embedded in the CROM.
  The Firmwares are delivered through the Middleware HSP Engine.

4. Load Plugin with HAL_HSP_LoadPlugin() (Optional)
  This step requires one call per Plugin.
  The Plugins are delivered through the Middleware HSP Engine.

5. Boot the HSP with HAL_HSP_Boot()
  On success, the handle state is set to HAL_HSP_STATE_RUNNING. The HSP is ready to use.

  @warning On failure, the handle state is set to HAL_HSP_STATE_FAULT to prohibit any configuration or processing.
  HAL_HSP_DeInit() must be called and an HSP Hardware Reset is required with HAL_RCC_HSP<x>_Reset().

6. HSP Processing in Accelerator Mode
  - To process a processing function (Accelerator mode), call in order, the following APIs:
      - HAL_HSP_DCMD_WriteCommand(): to send the Processing Function Command ID
      - HAL_HSP_WriteParameter(): to send a parameter value (one call per parameter)
      - HAL_HSP_DCMD_WriteDataPointer(): to send a pointer of buffer (one call per pointer)

      Refer to the HSP Processing Functions User Manual(UM3360) to find all processing functions available
      for the Accelerator mode.

      The Middleware HSP Engine embeds API for each Processing Function available in Accelerator Mode.

7. HSP Processing in Sequencer Mode
  - Record a processing list

    1. Start the recording:
       - Run the Task HAL_HSP_TASK_SUPERVISOR with HAL_HSP_PRC_SWRequestLowestPriorityTask().
       - Write the Processing List ID with HAL_HSP_WriteParameter() using parameters
         (HAL_HSP_PARAM_0, pl_id).
       - Send the PROCFG_START command with HAL_HSP_MSGBOX_SendMessage().

    2. Record a processing function:
       - Prepare all parameters with HAL_HSP_WriteParameter() according to the Processing Function User Manual.

         Any buffer address set as parameter must be allocated in the ".HSP_DATA_BRAM" memory region defined in
         the linker file.
       - Send the Processing Function ID with HAL_HSP_MSGBOX_SendMessage().

    3. Iterate the previous step to record several processing functions.

    4. Stop the recording:
       - Send the PROCFG_END command with HAL_HSP_MSGBOX_SendMessage().

    The MSGBOX command identifiers are defined in the HSP Firmware definitions file provided by the MW HSP Engine.

  - Configure a trigger to run a processing list

      A trigger could be an HSP STREAM Buffer, a peripheral event(such as DMA Transfer Complete)...
      It must be attached to an HSP Event within the range [1..22].

      To attach a Processing List to an HSP Event, the Processing List ID must match the HSP Event ID.

      - To configure an HSP event with STREAM Buffer as source:
        - Configure the STREAM Buffer [y] with HAL_HSP_STREAM_SetMultiConfig().
        - If needed, enable the Integer-to-Float conversion with HAL_HSP_STREAM_EnableIntToFloat().
          This feature applies to all STREAM Buffers.
        - Configure the event [x] by calling HAL_HSP_PRC_SetMultiTaskConfig() with
          HAL_HSP_EVENT_[x]_STREAM[y] as trigger source.

      - To configure an HSP event with a Trigger Input as source:
        - Configure the Trigger Input [y] with HAL_HSP_TRGIN_SetConfigTriggers().
        - Configure the event [x] by calling HAL_HSP_PRC_SetMultiTaskConfig() with HAL_HSP_EVENT_[x]_TRGIN[y].

      - To configure an HSP event triggered by the CPU (CSEG interface):
        Configure event [x] by calling HAL_HSP_PRC_SetMultiTaskConfig() with HAL_HSP_EVENT_[x]_CSEG.

      - To configure an HSP event triggered by the Signal Processor Engine itself (HSEG interface):
        Configure event [x] by calling HAL_HSP_PRC_SetMultiTaskConfig() with HAL_HSP_EVENT_[x]_HSEG.

    In polling mode, the HAL provides these APIs:
      - HAL_HSP_TRGIN_EnableTriggers() to enable the Trigger Input
      - HAL_HSP_TRGIN_DisableTriggers() to disable the Trigger Input

    In interrupt mode, the HAL provides these APIs:
      - HAL_HSP_TRGIN_EnableIT() to enable the Trigger Input
      - HAL_HSP_TRGIN_DisableIT() to disable the Trigger Input

  - Execute a Processing List

    For all Processing List attached to HSP Event (except for CSEG interface), the Hardware will trig the HSP Event
    and the execution of the Processing List will be scheduled by the Signal Processor Engine.

      - For Processing list triggered by a STREAM Buffer
        The HAL provides these APIs:
          - HAL_HSP_STREAM_Start() to start all the STREAM Buffers with possibility to select the STREAM Buffer
            interrupts to enable.
          - HAL_HSP_STREAM_Stop() to stop all the STREAM Buffers and all STREAM interrupts.
          - HAL_HSP_STREAM_IsActiveFlag_Event() to get the STREAM Buffer Empty/Full Flag status
            (Respectively for RX/TX)

        When a STREAM Buffer event occurs (Empty or Full depending on the buffer direction), use these APIs:
          - Call HAL_HSP_STREAM_WriteBufferData() to write a data to a STREAM Buffer (configured with RX direction)
          - Call HAL_HSP_STREAM_ReadBufferData() to read a data from a STREAM Buffer (configured with TX direction)

        Use HAL_HSP_STREAM_GetDataRegAddress() to get the address of a STREAM Buffer to pass as parameter of
        a processing function during the record of a processing list.

      - For Processing list triggered by a TRIGGER INPUT signal
        The execution of the processing list is automatically triggered by the Hardware.

      - For Processing list attached to an HSP Event with CSEG interface:
        - Call HAL_HSP_PRC_SWRequestTask() to send a request.
        - Call HAL_HSP_PRC_PollForEvent() to know if the request is always pending.

      - Lowest Priority processing
        - Call HAL_HSP_PRC_SWRequestLowestPriorityTask() to execute any processing list.

          The processing list will be scheduled and executed with the lowest priority by the Signal Processor Engine.
        - Call HAL_HSP_PRC_GetSWRequestLowestPriorityStatusAndClearFlag()  to know if the request is always pending

8. HSP HAL Driver Performance & Monitoring
  - To synchronize the execution of a process list (attached to an event) by the end of another task:
      - When configuring the EVENT, configure the attribute "sync" and select one of the 4 Task Comparator
        (hal_hsp_event_hal_hsp_prc_task_sync_source_tsync_t)

      - Call HAL_HSP_TCU_StartComparator() to configure and Enable the selected Task Comparator Unit to start the
        monitoring of the end of a task

  - To reduce BRAM conflict access shared between CPU and HSP:
      - Call HAL_HSP_BRAM_EnableConflictAccessCounter() to enable the Conflict Access Counter
      - Run your processing sequence and call HAL_HSP_BRAM_GetConflictAccessCounter()
        to get the conflict counter value
      - Call HAL_HSP_BRAM_SetLatency() to change the BRAM Arbitration latency and try
        to reduce BRAM conflict access
      - Run again your processing sequence and get the conflict counter value
      - Check if the BRAM Arbitration changes reduce the number of conflict access
      - Iterate to find the best BRAM arbitration latency configuration for your application

  - To monitor the HSP with TimeStamp Capture feature:
      - Call HAL_HSP_TSC_SetConfig() to configure the TimeStamp Capture
      - Call HAL_HSP_TSC_Start() by specifying the capture mode to start the TimeStamp Capture

      In polling mode:
        - Call HAL_HSP_TSC_Start() by specifying the capture mode and setting the event and error interrupt parameters
          to HAL_HSP_IT_NONE
        - Call HAL_HSP_TSC_Stop() to stop the TimeStamp Capture
        - Call HAL_HSP_TSC_IsTimeStampReady() to know if a timestamp data is ready
        - Call HAL_HSP_TSC_GetTimeStamp() to get the last timestamp data

      In interrupt mode:
        - Call HAL_HSP_TSC_Start() by specifying the capture mode and setting the interrupt parameters to
          HAL_HSP_TSC_IT_DATA_READY and HAL_HSP_TSC_ERR_IT_OVR to start the TimeStamp Capture in interrupt mode
        - Call HAL_HSP_TSC_Stop() to stop the TimeStamp Capture and stop all TSC interrupts
        - When a timestamp data is ready, the TimestampReadyCallback callback is called
          (either user callback if registered with HAL_HSP_RegisterTSC_TimestampReadyCallback(),
           otherwise the default weak function is called).

  - To monitor the Signal Processor Engine activity
      - Call HAL_HSP_SNOOP_SetSignals() to observe key signals to ease application tuning.

      For this feature, HSP pins must be configured in Push-Pull mode. To do that:
        - Enable the clock for the HSP GPIOs
        - Configure HSP pins as alternate function

  - To manage the power consumption of HSP blocks call the following APIs:
      - HAL_HSP_SMARTCLOCKING_Enable() to enable the Smart Clocking of some clocks (Default mode)
      - HAL_HSP_SMARTCLOCKING_Disable() to disable the Smart Clocking of some clocks (increase the power consumption)

  - To debug a processing list
      - Call HAL_HSP_BREAK_SetDebugEvents() to select HSP events to freeze the Signal Processor Engine
      - Call HAL_HSP_BREAK_ResumeDebugEvents() to resume the Signal Processor Engine
      - Call HAL_HSP_BREAK_EnableDebugSingleStep() to enable the Single Step Debug mode. This allows to execute
        one instruction at a time and freeze the Signal Processor Engine after each instruction.

  - To stop sensitive peripheral, call HAL_HSP_BREAK_SetMultiConfigOutput() to configure the HSP Break output
      (which is interconnected with this peripheral) and select HSP errors considered critical event for
      the application.

9. Call HAL_HSP_DeInit() to deinitialize the HSP peripheral.
  @warning After the call of HAL_HSP_DeInit(), make an HSP Hardware reset with HAL_RCC_HSP<x>_Reset().

10. Optionally Call HAL_HSP_GetInstance() to retrieve the HSP instance.

11. Callback definition in Interrupt
  When the compilation define USE_HAL_HSP_REGISTER_CALLBACKS is set to 1, the user can dynamically configure the
  driver callbacks, via its own method:

Callback value                 | Default value                          | Callback registration function
------------------------------ | -------------------------------------- | ----------------------------------------------
PRC_TaskCpltCallback           | HAL_HSP_PRC_TaskCpltCallback()         | HAL_HSP_RegisterPRC_TaskCpltCallback()
SPE_FPUSaturationCallback      | HAL_HSP_SPE_FPUSaturationCallback()    | HAL_HSP_RegisterSPE_FPUSaturationCallback()
SPE_RunStateCallback           | HAL_HSP_SPE_RunStateCallback()         | HAL_HSP_RegisterSPE_RunStateCallback()
STREAM_BufferEmptyCallback     | HAL_HSP_STREAM_BufferEmptyCallback()   | HAL_HSP_RegisterSTREAM_BufferEmptyCallback()
STREAM_BufferFullCallback      | HAL_HSP_STREAM_BufferFullCallback()    | HAL_HSP_RegisterSTREAM_BufferFullCallback()
TCU_TaskStartedCallback        | HAL_HSP_TCU_TaskStartedCallback()      | HAL_HSP_RegisterTCU_TaskStartedCallback()
TCU_TaskEndedCallback          | HAL_HSP_TCU_TaskEndedCallback()        | HAL_HSP_RegisterTCU_TaskEndedCallback()
TCU_TaskOverlapCallback        | HAL_HSP_TCU_TaskOverlapCallback()      | HAL_HSP_RegisterTCU_TaskOverlapCallback()
TSC_TimestampReadyCallback     | HAL_HSP_TSC_TimestampReadyCallback()   | HAL_HSP_RegisterTSC_TimestampReadyCallback()
ErrorCallback                  | HAL_HSP_ErrorCallback()                | HAL_HSP_RegisterErrorCallback()
ProcessingEventCallback        | HAL_HSP_ProcessingEventCallback()      | HAL_HSP_RegisterProcessingEventCallback()

  To unregister a callback, re-register the corresponding default weak function via the registration function.

  By default, after the HAL_HSP_Init() and when the state is HAL_HSP_STATE_INIT, all callbacks are set to the
  corresponding default weak functions.

  Callbacks can be registered in handle global_state HAL_HSP_STATE_INIT, HAL_HSP_STATE_READY_TO_BOOT
  or HAL_HSP_STATE_RUNNING.

  When the compilation define USE_HAL_HSP_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
  feature is not available and weak callbacks are used, represented by the default value in the table above.
  */

/**
  * @}
  */

/** @defgroup HSP_Configuration_Table HSP Configuration Table
  * @{
  # Configuration inside the HSP driver

Software configuration defined in stm32h7pxx_hal_conf.h:
Preprocessor flags                   |   Default value   | Comment
------------------------------------ | ----------------- | ------------------------------------------------
USE_HAL_HSP_MODULE                   |         1         | Enable HAL HSP driver module
USE_HAL_HSP_REGISTER_CALLBACKS       |         0         | Allow the user to define their own callback
USE_HAL_CHECK_PARAM                  |         0         | Enable runtime parameter check
USE_HAL_HSP_CLK_ENABLE_MODEL         | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PROCESS_STATE          |         0         | Enable atomicity of process state check
USE_HAL_HSP_USER_DATA                |         0         | Add a user data inside HAL HSP handle
USE_HAL_HSP_GET_LAST_ERRORS          |         0         | Enable retrieval of last processes error codes
USE_HAL_HSP_MSGBOX_GET_LAST_ERROR    |         0         | Enable retrieval of last MSGBOX error code
USE_HAL_HSP_TRGIN_IT                 |         0         | Enable Trigger Input IT management
USE_HAL_HSP_STREAM_IT                |         0         | Enable STREAM Buffer IT management
USE_HAL_HSP_TCU_IT                   |         0         | Enable Task Comparator Unit IT management
USE_HAL_HSP_TSC_IT                   |         0         | Enable TimeStamp Capture IT management
USE_HAL_HSP_PROCLIST_NOTIFICATION_IT |         0         | Enable Processing List Notification IT management

@note
USE_HAL_HSP_TRGIN_IT to USE_HAL_HSP_PROCLIST_NOTIFICATION_IT are set to 0 by default to reduce the HAL handle
footprint when these features are not used by the application.

Software configuration defined in preprocessor environment:
Preprocessor flags   |  Default value  | Comment
-------------------- | --------------- | --------------------------
USE_ASSERT_DBG_PARAM |      None       | Enable check param for HAL
USE_ASSERT_DBG_STATE |      None       | Enable check state for HAL

  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/*! Prototype for a function that gets the status of a polled flags used by polling functions */
typedef uint32_t (*hsp_get_polled_flags_t)(const __IOM uint32_t *p_reg_addr, uint32_t mask);

/* Private constants ---------------------------------------------------------*/
/** @defgroup HSP_Private_Constants  HSP Private Constants
  * @{
  */
/**
  * @defgroup  HSP_Common_Constants  HSP Common Constants
  * @{
  */
/*! Pattern to close the Firmware CRAM */
#define HSP_FW_END_PATTERN  (0xFFFFFFFFUL)

/*! Keep only HDEG, HSEG and CDEG interfaces enabled in CNN Safe Mode */
#define HSP_CNN_SAFEMODE_ITFENR_MASK  (HSP_ITFENR_HDEGEN | HSP_ITFENR_HSEGEN | HSP_ITFENR_CDEGEN)

/*! HSP Boot Timeout in millisecond */
#define HSP_BOOT_TIMEOUT_MS  (1U)

/*! HSP Reset Request Timeout in millisecond */
#define HSP_RESET_TIMEOUT_MS  (1U)

/*! HSP Firmware Error Code Clean Timeout in millisecond */
#define HSP_CLEAN_FW_ERROR_CODE_TIMEOUT_MS  (1U)

/*! HSP Timestamp Capture Configuration CAPCR Mask */
#define HSP_TSC_CONFIG_CAPCR_MASK  (HSP_CAPCR_PRESC_Msk | HSP_CAPCR_FRCNTEN_Msk | HSP_CAPCR_TSKFLT_Msk)

/*! Event Priority bitfield mask in enumerate @ref hal_hsp_event_source_t */
#define HSP_EVENT_PRIO_MSK  (0x1FUL << HAL_HSP_EVENT_PRIO_POS)

/*! Event "Register Source bitfield Position" bitfield mask in enumerate @ref hal_hsp_event_source_t */
#define HSP_EVENT_REG_SRC_BITFIELD_POSITION_MSK  (0x1FUL << HAL_HSP_EVENT_REG_SRC_BITFIELD_POSITION_POS)

/*! Event Source bitfield mask in enumerate @ref hal_hsp_event_source_t */
#define HSP_EVENT_SOURCE_MSK  (0x7UL << HAL_HSP_EVENT_SOURCE_POS)

/*! Position of the first PFCTEVT flag used by BREAK logic */
#define HSP_BREAK_PFCTEVT_FIRST_FLAG_POS  (STM32_POSITION_VAL(HSP_PFCTEVT_IER_PFCTIE_28))

/*! HSP Mask of all STREAM Buffer Directions */
#define HSP_BUFFCFGR_BUFFDIR_MSK                    \
  (HSP_BUFFCFGR_BUFF0DIR   | HSP_BUFFCFGR_BUFF1DIR  \
   | HSP_BUFFCFGR_BUFF2DIR | HSP_BUFFCFGR_BUFF3DIR)

/**
  * @}
  */

/**
  * @defgroup  HSP_Interrupt_Constants  HSP Interrupt Constants
  * @{
  */
/*! HSP Mask of all TCU Start Of Task flags */
#define HSP_EVT_ISR_TCU_START_OF_TASK_FLAGS_MASK  \
  (HSP_EVT_ISR_SOTECP0F   | HSP_EVT_ISR_SOTECP1F  \
   | HSP_EVT_ISR_SOTECP2F | HSP_EVT_ISR_SOTECP3F)

/*! HSP Mask of all TCU End Of Task flags */
#define HSP_EVT_ISR_TCU_END_OF_TASK_FLAGS_MASK    \
  (HSP_EVT_ISR_EOTECP0F   | HSP_EVT_ISR_EOTECP1F  \
   | HSP_EVT_ISR_EOTECP2F | HSP_EVT_ISR_EOTECP3F)

/*! HSP Mask of all Event Interrupts */
#define HSP_IT_EVT_ALL                                                        \
  (HAL_HSP_PRC_IT_CDEG_READY  | HAL_HSP_TSC_IT_DATA_READY                     \
   | HAL_HSP_SPE_IT_ALL       | HAL_HSP_STREAM_EVT_IT_ALL                     \
   | HAL_HSP_TCU_IT_ALL                                                       \
   | HSP_EVT_IER_H2CMRDYIE    | HSP_EVT_IER_C2HMFREEIE | HSP_EVT_IER_DCDONEIE)

/*! HSP Mask of all Error Interrupts */
#define HSP_IT_ERR_ALL                                                               \
  (HAL_HSP_TRGIN_ERR_IT_ALL     | HAL_HSP_STREAM_ERR_IT_ALL | HAL_HSP_TSC_ERR_IT_ALL \
   | HAL_HSP_SPE_ERR_IT_FPU_ALL | HAL_HSP_SPE_ERR_IT_ALL)

/**
  * @}
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup HSP_Private_Macros  HSP Private Macros
  * @{
  */
/**
  * @brief Retrieve the HSP hardware CMSIS instance from the hal handle.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return  pointer to HSP_TypeDef structure.
  */
#define HSP_GET_INSTANCE(hhsp)  ((HSP_TypeDef *)((uint32_t)((hhsp)->instance)))

/**
  * @brief Retrieve the pointer to an HSP register.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  reg  Register name.
  * @return  uint32_t.
  */
#define HSP_GET_REG_PTR(hhsp, reg)  ((__IOM uint32_t *)&(HSP_GET_INSTANCE(hhsp)->reg))

/** @defgroup HSP_Private_Macros_Group1  HSP Private Macros for Hardware information
  * @{
  */
/**
  * @brief Retrieve the number of HSP STREAM Buffer.
  * @param  instance  HSP instance.
  * @return  uint32_t.
  */
#define HSP_STREAM_BUFFER_NBR(instance)  (HSP1_STREAM_BUFFER_NBR)

/**
  * @brief Retrieve the number of HSP PRC Event.
  * @param  instance  HSP instance.
  * @return  uint32_t.
  */
#define HSP_PRC_EVENT_NBR(instance)  (HSP1_PRC_EVENT_NBR)

/**
  * @brief Retrieve the number of HSP TRGO Output.
  * @param  instance  HSP instance.
  * @return  uint32_t.
  */
#define HSP_TRGO_NBR(instance)  (HSP1_TRGO_NBR)

/**
  * @brief Retrieve the number of HSP Break Output.
  * @param  instance  HSP instance.
  * @return  uint32_t.
  */
#define HSP_BREAK_OUTPUT_NBR(instance)  (HSP1_BREAK_OUTPUT_NBR)

/**
  * @brief Retrieve the HSP CRAM Base Address.
  * @param  instance  HSP instance.
  * @retval Address  If instance supported.
  * @retval NULL  If instance not supported.
  */
#define HSP_GET_CRAM_BASE_ADDRESS(instance)  (HSP1_CRAM_BASE)

/**
  * @brief Retrieve the HSP DRAM Base Address.
  * @param  instance  HSP instance.
  * @retval Address  If instance supported.
  * @retval NULL  If instance not supported.
  */
#define HSP_GET_DRAM_BASE_ADDRESS(instance)  (HSP1_DRAM_BASE)

/**
  * @brief Retrieve the size of HSP CRAM.
  * @param  instance  HSP instance.
  * @retval Size  CRAM size in byte if instance supported.
  * @retval 0  If instance not supported.
  */
#define HSP_GET_CRAM_SIZE_BYTE(instance)  (HSP1_CRAM_SIZE)

/**
  * @brief Retrieve the size of HSP DRAM.
  * @param  instance  HSP instance.
  * @retval Size  DRAM size in byte if instance supported.
  * @retval 0  If instance not supported.
  */
#define HSP_GET_DRAM_SIZE_BYTE(instance)  (HSP1_DRAM_SIZE)

/**
  * @}
  */

/** @defgroup HSP_Private_Macros_Group2  HSP Private Macros for Assertion Parameters
  * @{
  */
/**
  * @brief Verify a firmware binary buffer pointer and size.
  * @param  bin   Pointer to the firmware binary buffer.
  * @param  size  Size in bytes of the firmware binary buffer.
  * @retval SET    Buffer pointer and size are valid.
  * @retval RESET  Buffer pointer or size is invalid.
  */
#define IS_HSP_VALID_FW_BIN(bin, size)  \
  (((bin) != NULL) && ((((uint32_t)(bin) & 0x3UL) == 0UL)) && ((size) > 0UL) && (((size) & 0x3UL) == 0UL))

/**
  * @brief Verify the Performance Monitor State value.
  * @param  state  Value of Performance Monitor State (@ref hal_hsp_perf_monitor_state_t).
  * @retval SET    State value is valid.
  * @retval RESET  State value is invalid.
  */
#define IS_HSP_PERF_MONITOR_STATE(state)        \
  (((state) == HAL_HSP_PERF_MONITOR_DISABLE)    \
   || ((state) == HAL_HSP_PERF_MONITOR_ENABLE))

/**
  * @brief Verify the Stream Identifier.
  * @param  id  Stream ID (@ref hal_hsp_stream_buffer_t).
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_STREAM_BUFFER(id)         \
  (((id) == HAL_HSP_STREAM_BUFFER_0)     \
   || ((id) == HAL_HSP_STREAM_BUFFER_1)  \
   || ((id) == HAL_HSP_STREAM_BUFFER_2)  \
   || ((id) == HAL_HSP_STREAM_BUFFER_3))

/**
  * @brief Verify the Stream Buffer Direction.
  * @param  direction  Stream Direction (@ref hal_hsp_stream_buffer_direction_t).
  * @retval SET    direction value is valid.
  * @retval RESET  direction value is invalid.
  */
#define IS_HSP_STREAM_BUFFER_DIRECTION(direction)          \
  (((direction) == HAL_HSP_STREAM_BUFFER_DIR_RX)     \
   || ((direction) == HAL_HSP_STREAM_BUFFER_DIR_TX))

/**
  * @brief Verify the Stream Buffer Sync State.
  * @param  state  Stream Buffer Sync State (@ref hal_hsp_stream_buffer_sync_state_t).
  * @retval SET    state value is valid.
  * @retval RESET  state value is invalid.
  */
#define IS_HSP_STREAM_BUFFER_SYNC_STATE(state)         \
  (((state) == HAL_HSP_STREAM_BUFFER_SYNC_DISABLE)     \
   || ((state) == HAL_HSP_STREAM_BUFFER_SYNC_ENABLE))

/**
  * @brief Verify the STREAM Event Interrupts.
  * @param  interrupts  Event Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_STREAM_BUFFER_IT_EVENT(interrupts)  \
  (((interrupts) & HAL_HSP_STREAM_EVT_IT_ALL) == (interrupts))

/**
  * @brief Verify the STREAM Error Interrupts.
  * @param  interrupts  Error Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_STREAM_BUFFER_IT_ERROR(interrupts)  \
  (((interrupts) & HAL_HSP_STREAM_ERR_IT_ALL) == (interrupts))

/**
  * @brief Verify the Trigger Input Identifier.
  * @param  id  Trigger Input ID.
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_TRGIN(id)         \
  (((id) == HAL_HSP_TRGIN_0)     \
   || ((id) == HAL_HSP_TRGIN_1)  \
   || ((id) == HAL_HSP_TRGIN_2)  \
   || ((id) == HAL_HSP_TRGIN_3)  \
   || ((id) == HAL_HSP_TRGIN_4)  \
   || ((id) == HAL_HSP_TRGIN_5)  \
   || ((id) == HAL_HSP_TRGIN_6)  \
   || ((id) == HAL_HSP_TRGIN_7)  \
   || ((id) == HAL_HSP_TRGIN_8)  \
   || ((id) == HAL_HSP_TRGIN_9))

/**
  * @brief Verify the Trigger Input Identifiers.
  * @param  ids  Trigger Input IDs.
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_TRGIN_COMBINATION(ids)       \
  (((ids) > 0UL)                            \
   && (((ids) & HAL_HSP_TRGIN_ALL) == (ids)))

/**
  * @brief Verify the Trigger Input Polarity.
  * @param  polarity  Polarity value (@ref hal_hsp_trgin_polarity_t).
  * @retval SET    polarity is valid.
  * @retval RESET  polarity is invalid.
  */
#define IS_HSP_TRGIN_POLARITY(polarity)               \
  (((polarity) == HAL_HSP_TRGIN_POLARITY_FALLING)     \
   || ((polarity) == HAL_HSP_TRGIN_POLARITY_RISING))

/**
  * @brief Verify the value of TRGIN source for HSP1 instance.
  * @param  source  id of the trigger signal (@ref hal_hsp_trgin_source_t).
. * @retval SET   source is valid.
. * @retval RESET source is invalid.
  */
#define IS_HSP1_TRGIN_SOURCE(source)              \
  (((source) == HAL_HSP1_TRGIN_GPDMA_CH15_TC)     \
   || ((source) == HAL_HSP1_TRGIN_GPDMA_CH14_TC)  \
   || ((source) == HAL_HSP1_TRGIN_GPDMA_CH13_TC)  \
   || ((source) == HAL_HSP1_TRGIN_GPDMA_CH12_TC)  \
   || ((source) == HAL_HSP1_TRGIN_EXTI0)          \
   || ((source) == HAL_HSP1_TRGIN_NPU_HOST_INT_3) \
   || ((source) == HAL_HSP1_TRGIN_TIM1_TRGO)      \
   || ((source) == HAL_HSP1_TRGIN_TIM1_TRGO2)     \
   || ((source) == HAL_HSP1_TRGIN_TIM2_TRGO)      \
   || ((source) == HAL_HSP1_TRGIN_TIM3_TRGO)      \
   || ((source) == HAL_HSP1_TRGIN_TIM6_TRGO)      \
   || ((source) == HAL_HSP1_TRGIN_TIM7_TRGO)      \
   || ((source) == HAL_HSP1_TRGIN_TIM8_TRGO)      \
   || ((source) == HAL_HSP1_TRGIN_TIM8_TRGO2)     \
   || ((source) == HAL_HSP1_TRGIN_TIM15_TRGO)     \
   || ((source) == HAL_HSP1_TRGIN_HPDMA_CH15_TC)  \
   || ((source) == HAL_HSP1_TRGIN_HPDMA_CH14_TC)  \
   || ((source) == HAL_HSP1_TRGIN_HPDMA_CH13_TC)  \
   || ((source) == HAL_HSP1_TRGIN_HPDMA_CH12_TC)  \
   || ((source) == HAL_HSP1_TRGIN_ADF1_SAD_DET))

/**
  * @brief Verify the value of TRGIN source.
  * @param  instance HSPx instance (@ref hal_hsp_t).
  * @param  source  id of the trigger signal (@ref hal_hsp_trgin_source_t).
  * @retval SET   source is valid.
  * @retval RESET source is invalid.
  */
#define IS_HSP_TRGIN_SOURCE(instance, source)                                          \
  ((((hal_hsp_t)((uint32_t)(instance)) == HAL_HSP1) && IS_HSP1_TRGIN_SOURCE((source))))

/**
  * @brief Verify the Trigger Input Error Interrupts.
  * @param  interrupts  Error Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TRGIN_IT_ERR(interrupts)                            \
  (((interrupts) > 0UL)                                            \
   && ((((interrupts) & HAL_HSP_TRGIN_ERR_IT_ALL) == (interrupts))))

/**
  * @brief Verify the Processing Function Event Interrupts.
  * @param  interrupts  Event Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_PROCLIST_IT_PFCTEVT(interrupts)                     \
  (((interrupts) > 0UL)                                            \
   && ((((interrupts) & HAL_HSP_PROCLIST_IT_PFCTEVT_ALL) == (interrupts))))

/**
  * @brief Verify the Event Identifier.
  * @param  id  Event ID.
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_EVENT(id)          \
  (((id) == HAL_HSP_EVENT_1)      \
   || ((id) == HAL_HSP_EVENT_2)   \
   || ((id) == HAL_HSP_EVENT_3)   \
   || ((id) == HAL_HSP_EVENT_4)   \
   || ((id) == HAL_HSP_EVENT_5)   \
   || ((id) == HAL_HSP_EVENT_6)   \
   || ((id) == HAL_HSP_EVENT_7)   \
   || ((id) == HAL_HSP_EVENT_8)   \
   || ((id) == HAL_HSP_EVENT_9)   \
   || ((id) == HAL_HSP_EVENT_10)  \
   || ((id) == HAL_HSP_EVENT_11)  \
   || ((id) == HAL_HSP_EVENT_12)  \
   || ((id) == HAL_HSP_EVENT_13)  \
   || ((id) == HAL_HSP_EVENT_14)  \
   || ((id) == HAL_HSP_EVENT_15)  \
   || ((id) == HAL_HSP_EVENT_16)  \
   || ((id) == HAL_HSP_EVENT_17)  \
   || ((id) == HAL_HSP_EVENT_18)  \
   || ((id) == HAL_HSP_EVENT_19)  \
   || ((id) == HAL_HSP_EVENT_20)  \
   || ((id) == HAL_HSP_EVENT_21)  \
   || ((id) == HAL_HSP_EVENT_22))

/**
  * @brief Verify the mask of Event Identifiers.
  * @param  mask  Event IDs mask.
  * @retval SET    mask is valid.
  * @retval RESET  mask is invalid.
  */
#define IS_HSP_EVENTS_MASK(mask)  \
  (((mask) > 0U) && STM32_IS_BIT_SET(HAL_HSP_EVENT_ALL, (mask)))

/**
  * @brief Verify the Task Sync Source for PRC Event.
  * @param  source  Task Sync Source (@ref hal_hsp_prc_task_sync_source_t).
  * @retval SET    source is valid.
  * @retval RESET  source is invalid.
  */
#define IS_HSP_PRC_TASK_SYNC_SOURCE(source)             \
  (((source) == HAL_HSP_PRC_TASK_SYNC_TCU_0)     \
   || ((source) == HAL_HSP_PRC_TASK_SYNC_TCU_1)  \
   || ((source) == HAL_HSP_PRC_TASK_SYNC_TCU_2)  \
   || ((source) == HAL_HSP_PRC_TASK_SYNC_TCU_3)  \
   || ((source) == HAL_HSP_PRC_TASK_SYNC_NONE))

/**
  * @brief Verify the PRC SW Request interrupt.
  * @param  interrupt  Interrupt.
  * @retval SET    interrupt is valid.
  * @retval RESET  interrupt is invalid.
  */
#define IS_HSP_PRC_SWREQUEST_IT(interrupt)  \
  (((interrupt) == HAL_HSP_IT_NONE) || ((interrupt) == HAL_HSP_PRC_IT_CDEG_READY))

/**
  * @brief Verify the value of EVENT source.
  * @param  source  id of the trigger signal (@ref hal_hsp_event_source_t).
  * @retval SET   source is valid.
  * @retval RESET source is invalid.
  */
#define IS_HSP_EVENT_SOURCE(source)          \
  (((source) == HAL_HSP_EVENT_1_STREAM0)     \
   || ((source) == HAL_HSP_EVENT_1_TRGIN3)   \
   || ((source) == HAL_HSP_EVENT_1_TRGIN8)   \
   || ((source) == HAL_HSP_EVENT_1_HSEG)     \
   || ((source) == HAL_HSP_EVENT_1_CSEG)     \
   || ((source) == HAL_HSP_EVENT_2_STREAM1)  \
   || ((source) == HAL_HSP_EVENT_2_TRGIN4)   \
   || ((source) == HAL_HSP_EVENT_2_TRGIN9)   \
   || ((source) == HAL_HSP_EVENT_2_HSEG)     \
   || ((source) == HAL_HSP_EVENT_2_CSEG)     \
   || ((source) == HAL_HSP_EVENT_3_STREAM2)  \
   || ((source) == HAL_HSP_EVENT_3_TRGIN0)   \
   || ((source) == HAL_HSP_EVENT_3_TRGIN5)   \
   || ((source) == HAL_HSP_EVENT_3_HSEG)     \
   || ((source) == HAL_HSP_EVENT_3_CSEG)     \
   || ((source) == HAL_HSP_EVENT_4_STREAM3)  \
   || ((source) == HAL_HSP_EVENT_4_TRGIN1)   \
   || ((source) == HAL_HSP_EVENT_4_TRGIN6)   \
   || ((source) == HAL_HSP_EVENT_4_HSEG)     \
   || ((source) == HAL_HSP_EVENT_4_CSEG)     \
   || ((source) == HAL_HSP_EVENT_5_STREAM0)  \
   || ((source) == HAL_HSP_EVENT_5_TRGIN2)   \
   || ((source) == HAL_HSP_EVENT_5_TRGIN7)   \
   || ((source) == HAL_HSP_EVENT_5_HSEG)     \
   || ((source) == HAL_HSP_EVENT_5_CSEG)     \
   || ((source) == HAL_HSP_EVENT_6_STREAM1)  \
   || ((source) == HAL_HSP_EVENT_6_TRGIN3)   \
   || ((source) == HAL_HSP_EVENT_6_TRGIN8)   \
   || ((source) == HAL_HSP_EVENT_6_HSEG)     \
   || ((source) == HAL_HSP_EVENT_6_CSEG)     \
   || ((source) == HAL_HSP_EVENT_7_STREAM2)  \
   || ((source) == HAL_HSP_EVENT_7_TRGIN4)   \
   || ((source) == HAL_HSP_EVENT_7_TRGIN9)   \
   || ((source) == HAL_HSP_EVENT_7_HSEG)     \
   || ((source) == HAL_HSP_EVENT_7_CSEG)     \
   || ((source) == HAL_HSP_EVENT_8_STREAM3)  \
   || ((source) == HAL_HSP_EVENT_8_TRGIN0)   \
   || ((source) == HAL_HSP_EVENT_8_TRGIN5)   \
   || ((source) == HAL_HSP_EVENT_8_HSEG)     \
   || ((source) == HAL_HSP_EVENT_8_CSEG)     \
   || ((source) == HAL_HSP_EVENT_9_STREAM0)  \
   || ((source) == HAL_HSP_EVENT_9_TRGIN1)   \
   || ((source) == HAL_HSP_EVENT_9_TRGIN6)   \
   || ((source) == HAL_HSP_EVENT_9_HSEG)     \
   || ((source) == HAL_HSP_EVENT_9_CSEG)     \
   || ((source) == HAL_HSP_EVENT_10_STREAM1) \
   || ((source) == HAL_HSP_EVENT_10_TRGIN2)  \
   || ((source) == HAL_HSP_EVENT_10_TRGIN7)  \
   || ((source) == HAL_HSP_EVENT_10_HSEG)    \
   || ((source) == HAL_HSP_EVENT_10_CSEG)    \
   || ((source) == HAL_HSP_EVENT_11_STREAM2) \
   || ((source) == HAL_HSP_EVENT_11_TRGIN3)  \
   || ((source) == HAL_HSP_EVENT_11_TRGIN8)  \
   || ((source) == HAL_HSP_EVENT_11_HSEG)    \
   || ((source) == HAL_HSP_EVENT_11_CSEG)    \
   || ((source) == HAL_HSP_EVENT_12_STREAM3) \
   || ((source) == HAL_HSP_EVENT_12_TRGIN4)  \
   || ((source) == HAL_HSP_EVENT_12_TRGIN9)  \
   || ((source) == HAL_HSP_EVENT_12_HSEG)    \
   || ((source) == HAL_HSP_EVENT_12_CSEG)    \
   || ((source) == HAL_HSP_EVENT_13_STREAM0) \
   || ((source) == HAL_HSP_EVENT_13_TRGIN0)  \
   || ((source) == HAL_HSP_EVENT_13_TRGIN5)  \
   || ((source) == HAL_HSP_EVENT_13_HSEG)    \
   || ((source) == HAL_HSP_EVENT_13_CSEG)    \
   || ((source) == HAL_HSP_EVENT_14_STREAM1) \
   || ((source) == HAL_HSP_EVENT_14_TRGIN1)  \
   || ((source) == HAL_HSP_EVENT_14_TRGIN6)  \
   || ((source) == HAL_HSP_EVENT_14_HSEG)    \
   || ((source) == HAL_HSP_EVENT_14_CSEG)    \
   || ((source) == HAL_HSP_EVENT_15_STREAM2) \
   || ((source) == HAL_HSP_EVENT_15_TRGIN2)  \
   || ((source) == HAL_HSP_EVENT_15_TRGIN7)  \
   || ((source) == HAL_HSP_EVENT_15_HSEG)    \
   || ((source) == HAL_HSP_EVENT_15_CSEG)    \
   || ((source) == HAL_HSP_EVENT_16_STREAM3) \
   || ((source) == HAL_HSP_EVENT_16_TRGIN3)  \
   || ((source) == HAL_HSP_EVENT_16_TRGIN8)  \
   || ((source) == HAL_HSP_EVENT_16_HSEG)    \
   || ((source) == HAL_HSP_EVENT_16_CSEG)    \
   || ((source) == HAL_HSP_EVENT_17_STREAM0) \
   || ((source) == HAL_HSP_EVENT_17_TRGIN4)  \
   || ((source) == HAL_HSP_EVENT_17_TRGIN9)  \
   || ((source) == HAL_HSP_EVENT_17_HSEG)    \
   || ((source) == HAL_HSP_EVENT_17_CSEG)    \
   || ((source) == HAL_HSP_EVENT_18_STREAM1) \
   || ((source) == HAL_HSP_EVENT_18_TRGIN0)  \
   || ((source) == HAL_HSP_EVENT_18_TRGIN5)  \
   || ((source) == HAL_HSP_EVENT_18_HSEG)    \
   || ((source) == HAL_HSP_EVENT_18_CSEG)    \
   || ((source) == HAL_HSP_EVENT_19_STREAM2) \
   || ((source) == HAL_HSP_EVENT_19_TRGIN1)  \
   || ((source) == HAL_HSP_EVENT_19_TRGIN6)  \
   || ((source) == HAL_HSP_EVENT_19_HSEG)    \
   || ((source) == HAL_HSP_EVENT_19_CSEG)    \
   || ((source) == HAL_HSP_EVENT_20_STREAM3) \
   || ((source) == HAL_HSP_EVENT_20_TRGIN2)  \
   || ((source) == HAL_HSP_EVENT_20_TRGIN7)  \
   || ((source) == HAL_HSP_EVENT_20_HSEG)    \
   || ((source) == HAL_HSP_EVENT_20_CSEG)    \
   || ((source) == HAL_HSP_EVENT_21_STREAM0) \
   || ((source) == HAL_HSP_EVENT_21_TRGIN3)  \
   || ((source) == HAL_HSP_EVENT_21_TRGIN8)  \
   || ((source) == HAL_HSP_EVENT_21_HSEG)    \
   || ((source) == HAL_HSP_EVENT_21_CSEG)    \
   || ((source) == HAL_HSP_EVENT_22_STREAM1) \
   || ((source) == HAL_HSP_EVENT_22_TRGIN4)  \
   || ((source) == HAL_HSP_EVENT_22_TRGIN9)  \
   || ((source) == HAL_HSP_EVENT_22_HSEG)    \
   || ((source) == HAL_HSP_EVENT_22_CSEG))

/**
  * @brief Verify the SmartClocking Identifier.
  * @param  clock_id  SmartClocking ID.
  * @retval SET    clock_id is valid.
  * @retval RESET  clock_id is invalid.
  */
#define IS_HSP_SMARTCLOCKING(clock_id)  \
  (((clock_id) > 0U)                    \
   && (((clock_id) & HAL_HSP_SMARTCLOCKING_ALL) == (clock_id)))

/**
  * @brief Verify the Task Identifier.
  * @param  task_id  Task ID (@ref hal_hsp_task_t).
  * @retval SET    task_id is valid.
  * @retval RESET  task_id is invalid.
  */
#define IS_HSP_TASK(task_id)          \
  (((task_id) == HAL_HSP_TASK_0)      \
   || ((task_id) == HAL_HSP_TASK_1)   \
   || ((task_id) == HAL_HSP_TASK_2)   \
   || ((task_id) == HAL_HSP_TASK_3)   \
   || ((task_id) == HAL_HSP_TASK_4)   \
   || ((task_id) == HAL_HSP_TASK_5)   \
   || ((task_id) == HAL_HSP_TASK_6)   \
   || ((task_id) == HAL_HSP_TASK_7)   \
   || ((task_id) == HAL_HSP_TASK_8)   \
   || ((task_id) == HAL_HSP_TASK_9)   \
   || ((task_id) == HAL_HSP_TASK_10)  \
   || ((task_id) == HAL_HSP_TASK_11)  \
   || ((task_id) == HAL_HSP_TASK_12)  \
   || ((task_id) == HAL_HSP_TASK_13)  \
   || ((task_id) == HAL_HSP_TASK_14)  \
   || ((task_id) == HAL_HSP_TASK_15)  \
   || ((task_id) == HAL_HSP_TASK_16)  \
   || ((task_id) == HAL_HSP_TASK_17)  \
   || ((task_id) == HAL_HSP_TASK_18)  \
   || ((task_id) == HAL_HSP_TASK_19)  \
   || ((task_id) == HAL_HSP_TASK_20)  \
   || ((task_id) == HAL_HSP_TASK_21)  \
   || ((task_id) == HAL_HSP_TASK_22)  \
   || ((task_id) == HAL_HSP_TASK_23)  \
   || ((task_id) == HAL_HSP_TASK_24)  \
   || ((task_id) == HAL_HSP_TASK_25)  \
   || ((task_id) == HAL_HSP_TASK_26)  \
   || ((task_id) == HAL_HSP_TASK_27)  \
   || ((task_id) == HAL_HSP_TASK_28)  \
   || ((task_id) == HAL_HSP_TASK_29)  \
   || ((task_id) == HAL_HSP_TASK_30)  \
   || ((task_id) == HAL_HSP_TASK_31)  \
   || ((task_id) == HAL_HSP_TASK_32)  \
   || ((task_id) == HAL_HSP_TASK_33)  \
   || ((task_id) == HAL_HSP_TASK_34)  \
   || ((task_id) == HAL_HSP_TASK_35)  \
   || ((task_id) == HAL_HSP_TASK_36)  \
   || ((task_id) == HAL_HSP_TASK_SUPERVISOR))

/**
  * @brief Verify the Task Comparator Unit Identifier.
  * @param  id  TCU ID (@ref hal_hsp_task_comparator_t).
  * @retval SET    id is valid.
  * @retval RESET  id is invalid.
  */
#define IS_HSP_TCU(id)                     \
  (((id) == HAL_HSP_TASK_COMPARATOR_0)     \
   || ((id) == HAL_HSP_TASK_COMPARATOR_1)  \
   || ((id) == HAL_HSP_TASK_COMPARATOR_2)  \
   || ((id) == HAL_HSP_TASK_COMPARATOR_3))

/**
  * @brief Verify the Task Comparator Unit 0 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TCU0_IT(interrupts)  \
  (((interrupts) & HAL_HSP_TCU_IT_CMP_0_ALL) == (interrupts))

/**
  * @brief Verify the Task Comparator Unit 1 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TCU1_IT(interrupts)  \
  (((interrupts) & HAL_HSP_TCU_IT_CMP_1_ALL) == (interrupts))

/**
  * @brief Verify the Task Comparator Unit 2 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TCU2_IT(interrupts)  \
  (((interrupts) & HAL_HSP_TCU_IT_CMP_2_ALL) == (interrupts))

/**
  * @brief Verify the Task Comparator Unit 3 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TCU3_IT(interrupts)  \
  (((interrupts) & HAL_HSP_TCU_IT_CMP_3_ALL) == (interrupts))

/**
  * @brief Verify the TCU Interrupts.
  * @param  tcu_id      Task Comparator Unit ID.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TCU_IT(tcu_id, interrupts)                                        \
  ((((tcu_id) == HAL_HSP_TASK_COMPARATOR_0)    && IS_HSP_TCU0_IT((interrupts)))  \
   || (((tcu_id) == HAL_HSP_TASK_COMPARATOR_1) && IS_HSP_TCU1_IT((interrupts)))  \
   || (((tcu_id) == HAL_HSP_TASK_COMPARATOR_2) && IS_HSP_TCU2_IT((interrupts)))  \
   || (((tcu_id) == HAL_HSP_TASK_COMPARATOR_3) && IS_HSP_TCU3_IT((interrupts))))

/**
  * @brief Verify the TCU Flags.
  * @param  flags  Flags mask.
  * @retval SET    flags variable is valid.
  * @retval RESET  flags variable is invalid.
  */
#define IS_HSP_TCU_FLAGS(flags)  \
  (STM32_IS_BIT_SET(HAL_HSP_FLAG_TCU_ALL, (flags)) != 0U)

/**
  * @brief Verify the Task Overlap interrupts.
  * @param  interrupts  Interrupts mask.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TASK_OVERLAP_IT(interrupts)  \
  (((interrupts) == HAL_HSP_IT_NONE) || ((interrupts) == HAL_HSP_TCU_IT_TASK_OVL))

/**
  * @brief Verify the Trigger Output Identifier.
  * @param  id  Trigger Output Id (@ref hal_hsp_trgo_trigger_t).
  * @retval SET    id is valid.
  * @retval RESET  id is invalid.
  */
#define IS_HSP_TRGO_TRIGGER(id)         \
  (((id) == HAL_HSP_TRGO_TRIGGER_0)     \
   || ((id) == HAL_HSP_TRGO_TRIGGER_1)  \
   || ((id) == HAL_HSP_TRGO_TRIGGER_2)  \
   || ((id) == HAL_HSP_TRGO_TRIGGER_3))

/**
  * @brief Verify the Trigger Output Source Identifier.
  * @param  id  Trigger Output Source ID (@ref hal_hsp_trgo_source_t).
  * @retval SET    id is valid.
  * @retval RESET  id is invalid.
  */
#define IS_HSP_TRGO_SOURCE(id)                    \
  (((id) == HAL_HSP_TRGO_SRC_NONE)                \
   || ((id) == HAL_HSP_TRGO_SRC_STREAM)           \
   || ((id) == HAL_HSP_TRGO_SRC_SPE)              \
   || ((id) == HAL_HSP_TRGO_SRC_TIMESTAMPCAPTURE))

/**
  * @brief Verify the TimeStamp Capture Prescaler value.
  * @param  value  Prescaler value (@ref hal_hsp_tsc_prescaler_t).
  * @retval SET    value is valid.
  * @retval RESET  value is invalid.
  */
#define IS_HSP_TSC_PRESCALER(value)                \
  (((value) == HAL_HSP_TSC_PRESCALER_BYPASSED)     \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV2)      \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV4)      \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV8)      \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV16)     \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV32)     \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV64)     \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV128)    \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV256)    \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV512)    \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV1024)   \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV2048)   \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV4096)   \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV8192)   \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV16384)  \
   || ((value) == HAL_HSP_TSC_PRESCALER_DIV32768))

/**
  * @brief Verify the TimeStamp Capture Free Counter value.
  * @param  value  Free Counter value (@ref hal_hsp_tsc_free_running_counter_state_t).
  * @retval SET    value is valid.
  * @retval RESET  value is invalid.
  */
#define IS_HSP_TSC_FREE_COUNTER(value)              \
  (((value) == HAL_HSP_TSC_FREE_COUNTER_DISABLE)    \
   || ((value) == HAL_HSP_TSC_FREE_COUNTER_ENABLE))

/**
  * @brief Verify the TimeStamp Capture Filter.
  * @param  value  Filter value (@ref hal_hsp_tsc_task_filter_t).
  * @retval SET    value is valid.
  * @retval RESET  value is invalid.
  */
#define IS_HSP_TSC_FILTER(value)                    \
  (((value) == HAL_HSP_TSC_TASK_FILTER_NONE)        \
   || ((value) == HAL_HSP_TSC_TASK_FILTER_TSKCMP0))

/**
  * @brief Verify the TimeStamp Capture Mode.
  * @param  mode  Mode value (@ref hal_hsp_tsc_capture_mode_t).
  * @retval SET    mode is valid.
  * @retval RESET  mode is invalid.
  */
#define IS_HSP_TSC_CAPTURE_MODE(mode)                        \
  (((mode) == HAL_HSP_TSC_CAPTURE_MODE_SPE_BREAKS)           \
   || ((mode) == HAL_HSP_TSC_CAPTURE_MODE_TASK_NBR_CHANGES)  \
   || ((mode) == HAL_HSP_TSC_CAPTURE_MODE_PFCT_NBR_CHANGES))

/**
  * @brief Verify the TSC Event interrupts.
  * @param  interrupts  Mask of interrupts.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TSC_EVT_IT(interrupts)  \
  (((interrupts) == HAL_HSP_IT_NONE) || ((interrupts) == HAL_HSP_TSC_IT_DATA_READY))

/**
  * @brief Verify the TSC Error interrupts.
  * @param  interrupts  Mask of interrupts.
  * @retval SET    interrupts variable is valid.
  * @retval RESET  interrupts variable is invalid.
  */
#define IS_HSP_TSC_ERR_IT(interrupts)  \
  (((interrupts) == HAL_HSP_IT_NONE) || ((interrupts) == HAL_HSP_TSC_ERR_IT_OVR))

/**
  * @brief Verify the BRAM Arbitration latency value.
  * @param  value  BRAM Arbitration latency (@ref hal_hsp_bram_latency_t).
  * @retval SET    value is valid.
  * @retval RESET  value is invalid.
  */
#define IS_HSP_BRAM_LATENCY(value)                \
  (((value) == HAL_HSP_BRAM_LATENCY_16_CYCLES)    \
   || ((value) == HAL_HSP_BRAM_LATENCY_8_CYCLES)  \
   || ((value) == HAL_HSP_BRAM_LATENCY_4_CYCLES))

/**
  * @brief Verify the SNOOP Signal set for GroupA.
  * @param  signal  Signal set (@ref hal_hsp_snoop_grpa_signal_t).
  * @retval SET    signal is valid.
  * @retval RESET  signal is invalid.
  */
#define IS_HSP_SNOOP_GROUPA_SIGNAL(signal)                      \
  (((signal) == HAL_HSP_SNOOP_GRPA_SIGNAL_NONE)                 \
   || ((signal) == HAL_HSP_SNOOP_GRPA_TASK_2_1_0)               \
   || ((signal) == HAL_HSP_SNOOP_GRPA_TRGIN_BUFF_ADC)           \
   || ((signal) == HAL_HSP_SNOOP_GRPA_TSC_PFCTNB_2_1_0)         \
   || ((signal) == HAL_HSP_SNOOP_GRPA_TSC_CMP_2_1_0)            \
   || ((signal) == HAL_HSP_SNOOP_GRPA_EVTCWKUP_SPEJUMP_SPEWFE)  \
   || ((signal) == HAL_HSP_SNOOP_GRPA_PE_2_1_0))

/**
  * @brief Verify the SNOOP Signal set for GroupB.
  * @param  signal  Signal set (@ref hal_hsp_snoop_grpb_signal_t).
  * @retval SET    signal is valid.
  * @retval RESET  signal is invalid.
  */
#define IS_HSP_SNOOP_GROUPB_SIGNAL(signal)                       \
  (((signal) == HAL_HSP_SNOOP_GRPB_SIGNAL_NONE)                  \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TASK_5_4_3)                \
   || ((signal) == HAL_HSP_SNOOP_GRPB_DCMD_CDEG_HDEG)            \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TSC_PFCTNB_5_4_3)          \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TSC_CMP_3)                 \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TSC_PULSE_CALL_IF_IFTRUE)  \
   || ((signal) == HAL_HSP_SNOOP_GRPB_PE_5_4_3))

/**
  * @brief Verify the Break Output value.
  * @param  id  Break Output id (@ref hal_hsp_break_output_t).
  * @retval SET    id is valid.
  * @retval RESET  id is invalid.
  */
#define IS_HSP_BREAK_OUTPUT(id)         \
  (((id) == HAL_HSP_BREAK_OUTPUT_0)     \
   || ((id) == HAL_HSP_BREAK_OUTPUT_1)  \
   || ((id) == HAL_HSP_BREAK_OUTPUT_2)  \
   || ((id) == HAL_HSP_BREAK_OUTPUT_3))

/**
  * @brief Verify the Polling Mode value.
  * @param  mode  Polling mode (@ref hal_hsp_polling_mode_t).
  * @retval SET    mode is valid.
  * @retval RESET  mode is invalid.
  */
#define IS_HSP_POLLING_MODE(mode)                \
  (((mode) == HAL_HSP_POLLING_FOR_ALL_EVENT)     \
   || ((mode) == HAL_HSP_POLLING_FOR_ANY_EVENT))

/**
  * @brief Verify the Signal Processor Engine Errors including the Floating Point Unit Errors.
  * @param  errors  Error mask.
  * @retval SET    errors variable is valid.
  * @retval RESET  errors variable is invalid.
  */
#define IS_HSP_SPE_ERR_IT_WITH_FPU(errors)                                                     \
  (((errors) > 0U)                                                                             \
   && (STM32_IS_BIT_SET((HAL_HSP_SPE_ERR_IT_ALL | HAL_HSP_SPE_ERR_IT_FPU_ALL), (errors)) != 0U))

/**
  * @brief Verify the Signal Processor Engine Error.
  * @param  errors  Error mask.
  * @retval SET    errors variable is valid.
  * @retval RESET  errors variable is invalid.
  */
#define IS_HSP_SPE_ERR(errors)                                 \
  (((errors) > 0U)                                             \
   && (STM32_IS_BIT_SET(HAL_HSP_SPE_ERR_ALL, (errors)) != 0U))

/**
  * @brief Verify the Signal Processor Engine Event.
  * @param  evts  Events mask.
  * @retval SET    evts variable is valid.
  * @retval RESET  evts variable is invalid.
  */
#define IS_HSP_SPE_EVT(evts)                                   \
  (((evts) > 0U)                                               \
   && (STM32_IS_BIT_SET((HAL_HSP_SPE_IT_ALL), (evts)) != 0U))

/**
  * @brief Verify the Signal Processor Engine fault access error.
  * @param  error_info  SPE access error information.
  * @retval SET    SPE access error information is valid.
  * @retval RESET  SPE access error information is invalid.
  */
#define IS_HSP_FAULT_ERROR_SPE_ACCESS(error_info)                  \
  ((((error_info) & (HAL_HSP_ERROR_INFO_INTERNAL_AHB_ACCESS        \
                     | HAL_HSP_ERROR_INFO_CODE_MEM_ACCESS)) != 0U))

/**
  * @brief Get the HSP BRAMAB Base Address.
  * @param  instance_id  HSP instance (@ref hal_hsp_t).
  * @retval uint32_t.
  */
#define HSP_GET_BRAMAB_BASE_ADDRESS(instance_id)  (HSP1_BRAMAB_BASE)

/**
  * @}
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup HSP_Private_Functions HSP Private Functions
  * @{
  */
static hal_status_t HSP_Reset(const hal_hsp_handle_t *hhsp);
static hal_status_t HSP_MSGBOX_SendMessage(const hal_hsp_handle_t *hhsp, uint32_t message);

static void HSP_ERR_IRQHandler(hal_hsp_handle_t *hhsp);
static void HSP_EVT_IRQHandler(hal_hsp_handle_t *hhsp);
static void HSP_FWEVT_IRQHandler(hal_hsp_handle_t *hhsp);

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
static void HSP_STREAM_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr);
#endif /* USE_HAL_HSP_STREAM_IT */
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
static void HSP_TCU_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr);
#endif /* USE_HAL_HSP_TCU_IT */
static void HSP_PRC_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr);
static void HSP_SPE_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr);
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
static void HSP_TSC_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr);
#endif /* USE_HAL_HSP_TSC_IT */

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
static uint32_t HSP_STREAM_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr);
#endif /* USE_HAL_HSP_STREAM_IT */
#if defined(USE_HAL_HSP_TRGIN_IT) && (USE_HAL_HSP_TRGIN_IT == 1)
static uint32_t HSP_TRGIN_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr);
#endif /* USE_HAL_HSP_TRGIN_IT */
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
static uint32_t HSP_TSC_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr);
#endif /* USE_HAL_HSP_TSC_IT */
static uint32_t HSP_SPE_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr, uint32_t error_info);
static uint32_t HSP_GetPolledFlagsActiveHigh(const __IOM uint32_t *p_reg_addr, uint32_t mask);
static uint32_t HSP_GetPolledFlagsActiveLow(const __IOM uint32_t *p_reg_addr, uint32_t mask);
static hal_status_t HSP_PollRegisterFlags(hal_hsp_polling_mode_t poll_mode,
                                          const __IOM uint32_t *p_reg_addr, uint32_t mask,
                                          hsp_get_polled_flags_t p_get_polled_flags,
                                          uint32_t timeout_ms,
                                          uint32_t *p_status);

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HSP_Exported_Functions
  * @{
  */

/** @addtogroup HSP_Exported_Functions_Group1
  * @{
This section provides a set of functions allowing to initialize, boot and deinitialize the HSP peripheral:
  - HAL_HSP_Init()               : initialize the selected device with the HSP instance.
  - HAL_HSP_DeInit()             : restore the default configuration of the selected HSP peripheral.
  - HAL_HSP_LoadFirmware()       : load the HSP Firmware in CRAM & DRAM.
  - HAL_HSP_LoadPlugin()         : load any HSP Plugin in CRAM.
  - HAL_HSP_Boot()               : boot the HSP after having loaded almost the HSP Firmware.
  - HAL_HSP_GetFirmwareVersion() : return the Firmware version.
  - HAL_HSP_GetHWInfo()          : return HSP hardware information.
  - HAL_HSP_GetInstance()        : return the HAL HSP instance from the handle.
  */

/**
  * @brief  Initialize the HSP according to the associated handle.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  instance  HAL HSP instance.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM HSP handle is NULL.
  */
hal_status_t HAL_HSP_Init(hal_hsp_handle_t *hhsp, hal_hsp_t instance)
{
  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE((HSP_TypeDef *)(uint32_t)instance));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hhsp == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hhsp->instance = instance;

  /* Init the peripheral */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
  /* Register the default callback functions */
  hhsp->p_spe_run_state_cb = HAL_HSP_SPE_RunStateCallback;
  hhsp->p_spe_fpu_saturation_cb = HAL_HSP_SPE_FPUSaturationCallback;
  hhsp->p_prc_task_cplt_cb = HAL_HSP_PRC_TaskCpltCallback;
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  hhsp->p_tsc_timestamp_ready_cb = HAL_HSP_TSC_TimestampReadyCallback;
#endif /* USE_HAL_HSP_TSC_IT */
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  hhsp->p_tcu_task_started_cb = HAL_HSP_TCU_TaskStartedCallback;
  hhsp->p_tcu_task_ended_cb = HAL_HSP_TCU_TaskEndedCallback;
  hhsp->p_tcu_task_overlap_cb = HAL_HSP_TCU_TaskOverlapCallback;
#endif /* USE_HAL_HSP_TCU_IT */
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  hhsp->p_stream_buffer_empty_cb = HAL_HSP_STREAM_BufferEmptyCallback;
  hhsp->p_stream_buffer_full_cb = HAL_HSP_STREAM_BufferFullCallback;
#endif /* USE_HAL_HSP_STREAM_IT */
#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
  hhsp->p_processing_event_cb = HAL_HSP_ProcessingEventCallback;
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT*/
  hhsp->p_error_cb = HAL_HSP_ErrorCallback;
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */

#if defined (USE_HAL_HSP_USER_DATA) && (USE_HAL_HSP_USER_DATA == 1)
  hhsp->p_user_data = NULL;
#endif /* USE_HAL_HSP_USER_DATA */

#if defined(USE_HAL_HSP_CLK_ENABLE_MODEL) && (USE_HAL_HSP_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable HSPx peripheral clock and HSPx SRAM clock */
  HAL_RCC_HSP1_EnableClock();
  HAL_RCC_AHBSRAM3_EnableClock();
#endif /* USE_HAL_HSP_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

#if defined (USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
  /* Reset the last error codes */
  hhsp->last_error_codes = HAL_HSP_ERROR_NONE;
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
#if defined(USE_HAL_HSP_MSGBOX_GET_LAST_ERROR) && (USE_HAL_HSP_MSGBOX_GET_LAST_ERROR == 1)
  hhsp->msgbox_last_error_code  = 0U;
#endif /* USE_HAL_HSP_MSGBOX_GET_LAST_ERROR */

  /* Initialize CRAM & DRAM free sizes */
  hhsp->cram_free_size_byte = HSP_GET_CRAM_SIZE_BYTE(hhsp->instance);

  /* Reset miscellaneous parameters */
  hhsp->fwerr_dcmd_id = 0U;

  /* Reset CNN Safe mode */
  hhsp->backup_enabled_itfs = 0U;
  hhsp->backup_enabled_events = 0U;
  hhsp->backup_event_its = 0U;
  hhsp->backup_pfctevt_its = 0U;

  hhsp->global_state = HAL_HSP_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the HSP peripheral.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @warning  During the HAL_HSP_DeInit() call, an HSP reset request is sent to flush all pending HSP BRAM transactions.
  *           Before reinitializing the HAL HSP driver, the application must perform a hardware reset of the peripheral.
  */
void HAL_HSP_DeInit(hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE(HSP_GET_INSTANCE(hhsp)));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Disable all the Events, but if HSP Registers are locked, the disabling will fail */
  STM32_CLEAR_BIT(p_hspx->EVTENR, HSP_EVTENR_EVTEN_Msk);

  /* Disable all Interfaces, but if HSP Registers are locked, the disabling will fail */
  /* STM32_WRITE_REG allows to set the DCMDDIS bit and clear all others */
  STM32_WRITE_REG(p_hspx->ITFENR, HSP_ITFENR_DCMDDIS);

  /* Disable ITs & Clear Flags. */
  STM32_WRITE_REG(p_hspx->PFCTEVT_IER, 0U);                         /* Disable all PFCT Event Interrupts */
  STM32_WRITE_REG(p_hspx->PFCTEVT_ICR, HSP_PFCTEVT_ICR_PFCTC_Msk);  /* Clear all PFCT Event Flags        */

  STM32_CLEAR_BIT(p_hspx->EVT_IER, HSP_IT_EVT_ALL);  /* Disable all Event Interrupts */
  STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_IT_EVT_ALL);  /* Clear all Event Flags  */

  STM32_CLEAR_BIT(p_hspx->ERR_IER, HSP_IT_ERR_ALL);  /* Disable all Error Interrupts */
  STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_IT_ERR_ALL);  /* Clear all Error Flags  */

  /* Request the Reset of Signal Processor Engine - A HSP HW Reset must be done after */
  (void)HSP_Reset(hhsp);

  /* Reset HSP state */
  hhsp->global_state = HAL_HSP_STATE_RESET;
}

/* Firmware/Plugin functions **************************************************/
/**
  * @brief Load HSP Firmware in CRAM & DRAM.
  * @param hhsp            Pointer to a @ref  hal_hsp_handle_t.
  * @param p_cram_bin      Pointer to the CRAM Firmware binary.
  * @param cram_size_byte  Size in bytes of Firmware CRAM.
  * @param p_dram_bin      Pointer to the DRAM Firmware binary.
  * @param dram_size_byte  Size in bytes of Firmware DRAM.
  * @warning If the selected HSP is locked, loading firmware cannot be performed.
  *          To unlock the configuration, perform a system reset of the peripheral.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  * @retval HAL_ERROR Operation failed because HSP is locked.
  */
hal_status_t HAL_HSP_LoadFirmware(hal_hsp_handle_t *hhsp,
                                  const uint8_t *p_cram_bin, uint32_t cram_size_byte,
                                  const uint8_t *p_dram_bin, uint32_t dram_size_byte)
{
  const HSP_TypeDef *p_hspx;
  const uint32_t *p_src_addr32;
  volatile uint32_t *p_dst_addr32;
  uint32_t word_nbr;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_VALID_FW_BIN(p_cram_bin, cram_size_byte));
  ASSERT_DBG_PARAM(IS_HSP_VALID_FW_BIN(p_dram_bin, dram_size_byte));
  ASSERT_DBG_PARAM(cram_size_byte < hhsp->cram_free_size_byte);
  ASSERT_DBG_PARAM(dram_size_byte <= HSP_GET_DRAM_SIZE_BYTE(hhsp->instance));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((IS_HSP_VALID_FW_BIN(p_cram_bin, cram_size_byte) == 0U)
      || (IS_HSP_VALID_FW_BIN(p_dram_bin, dram_size_byte) == 0U)
      || (cram_size_byte >= hhsp->cram_free_size_byte)
      || (dram_size_byte > HSP_GET_DRAM_SIZE_BYTE(hhsp->instance)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, HAL_HSP_STATE_INIT);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Check if HSP CRAM & DRAM are write protected */
  if (STM32_READ_BIT(p_hspx->CR, HSP_CR_CDRLCK) != 0U)
  {
#if defined (USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
    hhsp->last_error_codes |= HAL_HSP_FAULT_ERROR_CRAM_WRITE_PROTECTED;
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
    hhsp->global_state = HAL_HSP_STATE_FAULT;
    return HAL_ERROR;
  }

  /* Write data in HSP CRAM --------------------------------------------------*/
  p_src_addr32 = (const uint32_t *)(uint32_t)p_cram_bin;
  p_dst_addr32 = (volatile uint32_t *)HSP_GET_CRAM_BASE_ADDRESS(hhsp->instance);
  word_nbr = cram_size_byte >> 2U; /* Div by 4 */

  /* Pointer arithmetic is safe: alignment and CRAM size bounds are verified by the ASSERT_DBG_PARAM checks above. */
  for (uint32_t i = 0U; i < word_nbr; i++)
  {
    *p_dst_addr32 = *p_src_addr32;
    p_dst_addr32++;
    p_src_addr32++;
  }

  /* Back to the last CRAM data */
  p_dst_addr32--;

  /* Check if End Firmware Pattern is loaded */
  if (*p_dst_addr32 != HSP_FW_END_PATTERN)
  {
    /* No "End" Pattern found. Then store the next cram address to load plugin */
    hhsp->cram_free_size_byte -= cram_size_byte;
  }
  else
  {
    /* Store the cram address of the pattern which is override when loading the first plugin */
    hhsp->cram_free_size_byte -= (cram_size_byte - 4UL); /* -4 to keep a word for End Pattern */
  }

  /* Write data in HSP DRAM --------------------------------------------------*/
  p_src_addr32 = (const uint32_t *)(uint32_t)p_dram_bin;
  p_dst_addr32 = (volatile uint32_t *)HSP_GET_DRAM_BASE_ADDRESS(hhsp->instance);
  word_nbr = dram_size_byte >> 2U; /* Div by 4 */

  /* Pointer arithmetic is safe: alignment and DRAM size bounds are verified by the ASSERT_DBG_PARAM checks above. */
  for (uint32_t i = 0U; i < word_nbr; i++)
  {
    *p_dst_addr32 = *p_src_addr32;
    p_dst_addr32++;
    p_src_addr32++;
  }

  hhsp->global_state = HAL_HSP_STATE_READY_TO_BOOT;

  return HAL_OK;
}

/**
  * @brief Load HSP Plugin in CRAM.
  * @param hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param p_plugin_bin  Pointer to the CRAM Firmware binary.
  * @param size_byte    Number of bytes to load in CRAM.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  */
hal_status_t HAL_HSP_LoadPlugin(hal_hsp_handle_t *hhsp, const uint8_t *p_plugin_bin, uint32_t size_byte)
{
  uint32_t tmp_cram_addr32;
  uint32_t offset;
  const uint32_t *p_src_addr32;
  volatile uint32_t *p_dst_addr32;
  uint32_t word_nbr;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_VALID_FW_BIN(p_plugin_bin, size_byte));
  ASSERT_DBG_PARAM((size_byte < hhsp->cram_free_size_byte));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_plugin_bin == NULL)
      || (((uint32_t)p_plugin_bin & 0x3UL) != 0U)
      || (size_byte == 0U) || ((size_byte & 0x3UL) != 0UL) || (size_byte >= hhsp->cram_free_size_byte))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, HAL_HSP_STATE_READY_TO_BOOT);

  /* Write data in HSP CRAM */
  tmp_cram_addr32 = HSP_GET_CRAM_BASE_ADDRESS(hhsp->instance);
  offset = (HSP_GET_CRAM_SIZE_BYTE(hhsp->instance) - hhsp->cram_free_size_byte);
  tmp_cram_addr32 += offset;
  p_src_addr32 = (const uint32_t *)(uint32_t)p_plugin_bin;
  p_dst_addr32 = (volatile uint32_t *)tmp_cram_addr32;
  word_nbr = size_byte >> 2U; /* Div by 4 */

  /* Pointer arithmetic is safe: alignment and CRAM size bounds are verified by the ASSERT_DBG_PARAM checks above. */
  for (uint32_t i = 0U; i < word_nbr; i++)
  {
    *p_dst_addr32 = *p_src_addr32;
    p_dst_addr32++;
    p_src_addr32++;
  }

  /* Compute the size of free CRAM */
  hhsp->cram_free_size_byte -= size_byte;

  return HAL_OK;
}

/* Boot functions *************************************************************/
/**
  * @brief Boot the HSP.
  * @param hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param p_config    Pointer to Boot configuration.
  * @param p_boot_error_code  Pointer to the Boot error code.
  * @retval HAL_OK Operation   Completed successfully.
  * @retval HAL_INVALID_PARAM  Boot Config pointer is NULL.
  * @retval HAL_ERROR          HSP Boot Failure.
  */
hal_status_t HAL_HSP_Boot(hal_hsp_handle_t *hhsp, const hal_hsp_boot_config_t *p_config, uint32_t *p_boot_error_code)
{
  volatile uint32_t *p_tmp_addr;
  uint32_t tmp_cram_address;
  uint32_t offset;
  HSP_TypeDef *p_hspx;
  hal_status_t hal_status = HAL_ERROR;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(p_boot_error_code != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL) || (p_boot_error_code == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HSP_PERF_MONITOR_STATE(p_config->perf_monitor_state));

  ASSERT_DBG_STATE(hhsp->global_state, HAL_HSP_STATE_READY_TO_BOOT);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Close the Firmware */
  tmp_cram_address = HSP_GET_CRAM_BASE_ADDRESS(hhsp->instance);
  offset = (HSP_GET_CRAM_SIZE_BYTE(hhsp->instance) - hhsp->cram_free_size_byte);
  p_tmp_addr = (uint32_t *)(tmp_cram_address + offset);
  *p_tmp_addr = HSP_FW_END_PATTERN;
  hhsp->cram_free_size_byte -= 4U;

  /* Boot the HSP */
  STM32_SET_BIT(p_hspx->CR, HSP_CR_BOOTEN);

  /* Get timeout */
  uint32_t tickstart = HAL_GetTick();

  do
  {
    *p_boot_error_code = STM32_READ_BIT(p_hspx->CR, HSP_CR_BSTAT_Msk);
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > HSP_BOOT_TIMEOUT_MS)
    {
      /* New check to avoid false timeout detection in case of preemption */
      *p_boot_error_code = STM32_READ_BIT(p_hspx->CR, HSP_CR_BSTAT_Msk);
      if (*p_boot_error_code != p_config->boot_success_code)
      {
#if defined(USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
        hhsp->last_error_codes |= HAL_HSP_FAULT_ERROR_BOOT;
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */

        hhsp->global_state = HAL_HSP_STATE_FAULT;
        return HAL_ERROR;
      }
    }
  } while (*p_boot_error_code != p_config->boot_success_code);

  /* Firmware needs to know this address at boot */
  uint32_t bramab_address = HSP_GET_BRAMAB_BASE_ADDRESS(hhsp->instance);
  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_0, bramab_address);
  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_1, (uint32_t)p_config->perf_monitor_state);

  if (HSP_MSGBOX_SendMessage(hhsp, p_config->boot_cmd_id) == HAL_BUSY)
  {
#if defined(USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
    hhsp->last_error_codes |= HAL_HSP_FAULT_ERROR_FW_INIT;
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
    hhsp->global_state = HAL_HSP_STATE_FAULT;
    return HAL_ERROR;
  }

  /* Wait the acknowledge from Signal Processor Engine */
  while (STM32_READ_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM) == 0U)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > HSP_BOOT_TIMEOUT_MS)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (STM32_READ_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM) == 0U)
      {
        hhsp->global_state = HAL_HSP_STATE_FAULT;
        return HAL_ERROR;
      }
    }
  }

  /* Read the Signal Processor Engine answer through the HSP_H2CMSGDR register (HSP to CPU message data register). */
  uint32_t status = STM32_READ_REG(p_hspx->H2CMSGDR);

  /* Acknowledge the HSP that the message is read by the CPU */
  /* When CPU writes the bit H2CSEM to 1, it clears it to 0 ! */
  STM32_WRITE_REG(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM);

  /* Even if ITs are not enabled, the driver must clear the following flags:                    */
  /*  - HSP_EVT_ISR_H2CMRDYF  indicating a message is available for the CPU                     */
  /*  - HSP_EVT_ICR_C2HMFREEF indicating the MSGBOX is free for CPU to Signal Processor Engine  */
  STM32_WRITE_REG(p_hspx->EVT_ICR, (HSP_EVT_ICR_H2CMRDYC | HSP_EVT_ICR_C2HMFREEC));

  /* Check the HSP status */
  if (status != 0U)
  {
#if defined(USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
    hhsp->last_error_codes |= HAL_HSP_FAULT_ERROR_FW_INIT;
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
#if defined(USE_HAL_HSP_MSGBOX_GET_LAST_ERROR) && (USE_HAL_HSP_MSGBOX_GET_LAST_ERROR == 1)
    hhsp->msgbox_last_error_code = status;
#endif /* USE_HAL_HSP_MSGBOX_GET_LAST_ERROR */
    hhsp->global_state = HAL_HSP_STATE_FAULT;
    hal_status = HAL_ERROR;
  }
  else
  {
    /* Store the firmware error direct command identifier in the handle */
    hhsp->fwerr_dcmd_id = p_config->fwerr_dcmd_id;

    /* Enable all event generators: CDEG, CSEG */
    STM32_SET_BIT(p_hspx->ITFENR, (HSP_ITFENR_CSEGEN | HSP_ITFENR_CDEGEN));

    /* Write Protection of CRAM & DRAM from any CPU access to prevent any corruption */
    /* CRAM & DRAM become read-only access */
    STM32_MODIFY_REG(p_hspx->CR, HSP_CR_CDRLCK_Msk, HSP_CR_CDRLCK_0);

    /* HSP is ready to be configured, record processing list or process direct command */
    hhsp->global_state = HAL_HSP_STATE_RUNNING;
    hal_status = HAL_OK;
  }

  return hal_status;
}

/* Hardware information *******************************************************/
/**
  * @brief  Retrieve the Firmware versions (ROM & RAM).
  * @param  hhsp       Pointer to a @ref hal_hsp_handle_t.
  * @note  Call this function only after a successful HAL_HSP_Boot().
  * @return Return the FWVERR register value
  *  Use the following HAL HSP macros to retrieve each firmware version component:
  *    HAL_HSP_GET_RAM_FW_MAJOR_VERSION(): get CRAM major version
  *    HAL_HSP_GET_RAM_FW_MINOR_VERSION(): get CRAM minor version
  *    HAL_HSP_GET_ROM_FW_MAJOR_VERSION(): get CROM major version
  *    HAL_HSP_GET_ROM_FW_MINOR_VERSION(): get CROM minor version
  */
uint32_t HAL_HSP_GetFirmwareVersion(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return STM32_READ_REG(p_hspx->FWVERR);
}

/**
  * @brief  Get HSP hardware capability information.
  * @param hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param p_hw_info  Pointer to a @ref hal_hsp_hw_info_t.
  */
void HAL_HSP_GetHWInfo(const hal_hsp_handle_t *hhsp, hal_hsp_hw_info_t *p_hw_info)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_hw_info != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hw_info->bramab_base_address = HSP1_BRAMAB_BASE;
  p_hw_info->bramab_size_byte    = HSP1_BRAMAB_SIZE;
  p_hw_info->brama_base_address  = HSP1_BRAMA_BASE;
  p_hw_info->bramb_base_address  = HSP1_BRAMB_BASE;

  p_hw_info->p_dcmd_cmdid = HSP_GET_REG_PTR(hhsp, DCMDIDR);
  p_hw_info->p_dcmd_param = HSP_GET_REG_PTR(hhsp, PARAMR0);
  p_hw_info->p_dcmd_data  = HSP_GET_REG_PTR(hhsp, DCMDPTR0);
  p_hw_info->p_cdeg       = HSP_GET_REG_PTR(hhsp, CDEGR);
}

/**
  * @brief  Return the HAL HSP instance from the handle.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return HAL HSP instance.
  */
hal_hsp_t HAL_HSP_GetInstance(const hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE(HSP_GET_INSTANCE(hhsp)));

  return hhsp->instance;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group2
  * @{
This section provides a set of functions to manage HSP command exchanges:
  - HAL_HSP_DCMD_WriteCommand()         : (inline) write a command into the Direct Command interface.
  - HAL_HSP_DCMD_WriteDataPointer()     : (inline) write a data pointer into the Direct Command interface.
  - HAL_HSP_DCMD_GetStatus()            : (inline) get the Direct Command processing status.
  - HAL_HSP_MSGBOX_SendMessage()        : send a message to the HSP through the MSGBOX interface.
  - HAL_HSP_MSGBOX_IsMessageAvailable() : (inline) check whether a message is available through the MSGBOX interface.
  - HAL_HSP_MSGBOX_GetMessage()         : (inline) get the message sent by the Signal Processor Engine.
  - HAL_HSP_MSGBOX_AckSemaphore()       : (inline) acknowledge the MSGBOX semaphore.
  - HAL_HSP_WriteParameter()            : (inline) write a command parameter.
  - HAL_HSP_ReadParameter()             : (inline) read a command parameter.
  */
/**
  * @brief  Send a command by msgbox.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  message     Message for the HSP.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_BUSY  Send of Command is pending.
  */
hal_status_t HAL_HSP_MSGBOX_SendMessage(const hal_hsp_handle_t *hhsp, uint32_t message)
{
  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  if (HSP_MSGBOX_SendMessage(hhsp, message) == HAL_BUSY)
  {
    return HAL_BUSY;
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group3_2
  * @{
This section provides a set of functions to configure the HSP STREAM Buffer interface:
  - HAL_HSP_STREAM_SetMultiConfig()      : configure an HSP STREAM Buffer in RX or TX mode.
  - HAL_HSP_STREAM_GetMultiConfig()      : retrieve the STREAM Buffer configuration.
  - HAL_HSP_STREAM_EnableIntToFloat()    : enable the conversion of data in Float format.
  - HAL_HSP_STREAM_DisableIntToFloat()   : disable the conversion of data in Float format.
  - HAL_HSP_STREAM_IsEnabledIntToFloat() : check whether the conversion is enabled.
  - HAL_HSP_STREAM_Start()               : enable all HSP STREAM Buffers.
  - HAL_HSP_STREAM_Stop()                : disable all HSP STREAM Buffers.
  - HAL_HSP_STREAM_IsActiveFlag_Event()  : (inline) check whether a STREAM event flag is active.
  - HAL_HSP_STREAM_WriteBufferData()     : (inline) write data into a STREAM buffer.
  - HAL_HSP_STREAM_ReadBufferData()      : (inline) read data from a STREAM buffer.
  - HAL_HSP_STREAM_GetDataRegAddress()   : (inline) get a STREAM buffer address.
  */
/* STREAM Interface ----------------------------------------------------------*/
/**
  * @brief  Configure a set of STREAM Buffers.
  * @param  hhsp              Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array    Pointer to an array of @ref hal_hsp_stream_buffer_config_t.
  * @param  config_array_size Number of configuration in the array.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Config pointer is NULL.
  */
hal_status_t HAL_HSP_STREAM_SetMultiConfig(const hal_hsp_handle_t *hhsp,
                                           const hal_hsp_stream_buffer_config_t *p_config_array,
                                           uint32_t config_array_size)
{
  hal_hsp_stream_buffer_t buffer_id;
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_STREAM_BUFFER_NBR(p_hspx));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config_array == NULL) || (config_array_size > HSP_STREAM_BUFFER_NBR(p_hspx)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    const hal_hsp_stream_buffer_config_t *p_config = &p_config_array[idx];

    buffer_id = p_config->buffer_id;
    ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER(buffer_id));
    ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER_DIRECTION(p_config->direction));

    STM32_MODIFY_REG(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_BUFF0DIR_Msk << (uint32_t)(buffer_id)),
                     ((uint32_t)(p_config->direction) << (HSP_BUFFCFGR_BUFF0DIR_Pos + (uint32_t)(buffer_id))));

    if (buffer_id != HAL_HSP_STREAM_BUFFER_3)
    {
      ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER_SYNC_STATE(p_config->sync_state));
      STM32_MODIFY_REG(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_COMB0_Msk << (uint32_t)(buffer_id)),
                       ((uint32_t)(p_config->sync_state) << (HSP_BUFFCFGR_COMB0_Pos + (uint32_t)(buffer_id))));
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of a STREAM instance.
  * @param  hhsp               Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array     Pointer to an array of @ref hal_hsp_stream_buffer_config_t.
  * @param  config_array_size  Number of configuration in the array.
  */
void HAL_HSP_STREAM_GetMultiConfig(const hal_hsp_handle_t *hhsp,
                                   hal_hsp_stream_buffer_config_t *p_config_array, uint32_t config_array_size)
{
  const HSP_TypeDef *p_hspx;
  uint32_t reg_buffcfgr;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_STREAM_BUFFER_NBR(p_hspx));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  reg_buffcfgr = STM32_READ_REG(p_hspx->BUFFCFGR);

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    hal_hsp_stream_buffer_config_t *p_config = &p_config_array[idx];

    p_config->buffer_id = (hal_hsp_stream_buffer_t)idx;

    p_config->direction = (hal_hsp_stream_buffer_direction_t)(uint32_t)
                          ((reg_buffcfgr & (HSP_BUFFCFGR_BUFF0DIR_Msk << idx)) != 0U);

    if (idx != (uint32_t)HAL_HSP_STREAM_BUFFER_3)
    {
      p_config->sync_state = (hal_hsp_stream_buffer_sync_state_t)(uint32_t)
                             ((reg_buffcfgr & (HSP_BUFFCFGR_COMB0_Msk << idx)) != 0U);
    }
    else
    {
      p_config->sync_state = HAL_HSP_STREAM_BUFFER_SYNC_DISABLE;
    }
  }
}

/**
  * @brief  Enable the Integer to Float conversion for all STREAM Buffers.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_STREAM_EnableIntToFloat(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->BUFFCFGR, HSP_BUFFCFGR_I2FEN);

  return HAL_OK;
}

/**
  * @brief  Disable the Integer to Float conversion for all STREAM Buffers.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_STREAM_DisableIntToFloat(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->BUFFCFGR, HSP_BUFFCFGR_I2FEN);

  return HAL_OK;
}

/**
  * @brief  Return the Integer to Float conversion status.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_HSP_STREAM_INT_TO_FLOAT_DISABLED Conversion is disabled.
  * @retval HAL_HSP_STREAM_INT_TO_FLOAT_ENABLED  Conversion is enabled.
  */
hal_hsp_stream_int_to_float_status_t HAL_HSP_STREAM_IsEnabledIntToFloat(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return (hal_hsp_stream_int_to_float_status_t)(uint32_t)STM32_READ_BIT(p_hspx->BUFFCFGR, HSP_BUFFCFGR_I2FEN);
}

/**
  * @brief  Start all the STREAM Buffers.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  evt_interrupts  mask of event interrupts.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_STREAM_IT_BUFFER_0_READY
  *             @arg HAL_HSP_STREAM_IT_BUFFER_1_READY
  *             @arg HAL_HSP_STREAM_IT_BUFFER_2_READY
  *             @arg HAL_HSP_STREAM_IT_BUFFER_3_READY
  *             @arg HAL_HSP_STREAM_IT_ALL
  *             @arg HAL_HSP_IT_NONE
  * @param  err_interrupts  mask of error interrupts.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_STREAM_ERR_IT_BUFFER_0_OVR
  *             @arg HAL_HSP_STREAM_ERR_IT_BUFFER_1_OVR
  *             @arg HAL_HSP_STREAM_ERR_IT_BUFFER_2_OVR
  *             @arg HAL_HSP_STREAM_ERR_IT_BUFFER_3_OVR
  *             @arg HAL_HSP_STREAM_ERR_IT_ALL
  *             @arg HAL_HSP_IT_NONE
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_STREAM_Start(const hal_hsp_handle_t *hhsp,
                                  uint32_t evt_interrupts, uint32_t err_interrupts)
{
#if !defined(USE_HAL_HSP_STREAM_IT) || (USE_HAL_HSP_STREAM_IT != 1)
  STM32_UNUSED(evt_interrupts);
  STM32_UNUSED(err_interrupts);
#endif /* USE_HAL_HSP_STREAM_IT */

  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER_IT_EVENT(evt_interrupts));
  ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER_IT_ERROR(err_interrupts));
#endif /* USE_HAL_HSP_STREAM_IT */

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->ITFENR, HSP_ITFENR_STREAMEN);

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  STM32_SET_BIT(p_hspx->EVT_IER, evt_interrupts);
  STM32_SET_BIT(p_hspx->ERR_IER, err_interrupts);
#endif /* USE_HAL_HSP_STREAM_IT */

  return HAL_OK;
}

/**
  * @brief  Disable all the STREAM Buffer.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_STREAM_Stop(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ITFENR, HSP_ITFENR_STREAMEN);

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  STM32_CLEAR_BIT(p_hspx->EVT_IER, HAL_HSP_STREAM_EVT_IT_ALL);
  STM32_CLEAR_BIT(p_hspx->ERR_IER, HAL_HSP_STREAM_ERR_IT_ALL);
#endif /* USE_HAL_HSP_STREAM_IT */

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group3_3
  * @{
This section provides a set of functions to configure the HSP Trigger Input interface:
  - HAL_HSP_TRGIN_SetConfigTriggers() : configure an HSP Trigger input.
  - HAL_HSP_TRGIN_GetConfigTrigger()  : retrieve an HSP Trigger input configuration.
  - HAL_HSP_TRGIN_EnableTriggers()    : enable a set of HSP Trigger Input interfaces.
  - HAL_HSP_TRGIN_DisableTriggers()   : disable a set of HSP Trigger Input interfaces.
  - HAL_HSP_TRGIN_IsEnabledTrigger()  : check whether a Trigger Input interface is enabled.
  - HAL_HSP_TRGIN_EnableIT()          : enable some HSP Trigger Input error interrupts.
  - HAL_HSP_TRGIN_DisableIT()         : disable some HSP Trigger Input error interrupts.
  */
/* Trigger Input Interface ---------------------------------------------------*/
/**
  * @brief  Configure a set of Trigger Input interface.
  * @param  hhsp       Pointer to a @ref hal_hsp_handle_t.
  * @param  trgin_ids  Trigger Input interface identifiers.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_TRGIN_0
  *             @arg HAL_HSP_TRGIN_1
  *             @arg HAL_HSP_TRGIN_2
  *             @arg HAL_HSP_TRGIN_3
  *             @arg HAL_HSP_TRGIN_4
  *             @arg HAL_HSP_TRGIN_5
  *             @arg HAL_HSP_TRGIN_6
  *             @arg HAL_HSP_TRGIN_7
  *             @arg HAL_HSP_TRGIN_8
  *             @arg HAL_HSP_TRGIN_9
  *             @arg HAL_HSP_TRGIN_ALL
  * @param  p_config  Pointer to a @ref hal_hsp_trgin_config_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  */
hal_status_t HAL_HSP_TRGIN_SetConfigTriggers(const hal_hsp_handle_t *hhsp, uint32_t trgin_ids,
                                             const hal_hsp_trgin_config_t *p_config)
{
  HSP_TypeDef *p_hspx;
  uint32_t trgins_mask;
  uint32_t trgins_pol_mask;
  uint32_t remaining_trgins_mask;
  __IOM uint32_t *p_trginselr;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HSP_TRGIN_COMBINATION(trgin_ids));
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_SOURCE(hhsp->instance, p_config->source));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* configure the polarity */
  trgins_mask = (trgin_ids >> HSP_ITFENR_TRGI0EN_Pos);
  trgins_pol_mask = (trgins_mask << HSP_TRGINCFGR_TRG0POL_Pos);
  if (p_config->polarity == HAL_HSP_TRGIN_POLARITY_RISING)
  {
    STM32_CLEAR_BIT(p_hspx->TRGINCFGR, trgins_pol_mask);
  }
  else
  {
    STM32_SET_BIT(p_hspx->TRGINCFGR, trgins_pol_mask);
  }

  remaining_trgins_mask = trgins_mask;
  p_trginselr = &p_hspx->TRGINSELR0;

  for (uint32_t reg_idx = 0U; reg_idx < 3U; reg_idx++)
  {
    uint32_t trgin_mask = remaining_trgins_mask & 0xFU;

    /* Each TRGINSELR register configures one group of 4 trigger inputs. */
    if (reg_idx == 2U)
    {
      /* TRGINSELR2 only contains trigger inputs 8 and 9. */
      trgin_mask &= 0x3U;
    }

    remaining_trgins_mask >>= HSP_REG_TRGINSEL_CFG_NBR;

    if (trgin_mask != 0U)
    {
      uint32_t reg_mask = 0UL;
      uint32_t reg_value = 0UL;

      for (uint32_t bitfield_pos = 0U;
           bitfield_pos < (HSP_REG_TRGINSEL_CFG_NBR * HSP_REG_TRGINSEL_SELECT_FIELD_SIZE);
           bitfield_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE)
      {
        if ((trgin_mask & 0x1U) != 0U)
        {
          /* Fill only the selected trigger source fields. */
          reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfield_pos;
          reg_value |= (uint32_t)p_config->source << bitfield_pos;
        }

        trgin_mask >>= 1U;
      }

      STM32_MODIFY_REG(p_trginselr[reg_idx], reg_mask, reg_value);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of a Trigger Input interface.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  trgin_id  Trigger Input interface identifier.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_TRGIN_0
  *             @arg HAL_HSP_TRGIN_1
  *             @arg HAL_HSP_TRGIN_2
  *             @arg HAL_HSP_TRGIN_3
  *             @arg HAL_HSP_TRGIN_4
  *             @arg HAL_HSP_TRGIN_5
  *             @arg HAL_HSP_TRGIN_6
  *             @arg HAL_HSP_TRGIN_7
  *             @arg HAL_HSP_TRGIN_8
  *             @arg HAL_HSP_TRGIN_9
  * @param  p_config  Pointer to a @ref hal_hsp_trgin_config_t.
  */
void HAL_HSP_TRGIN_GetConfigTrigger(const hal_hsp_handle_t *hhsp, uint32_t trgin_id,
                                    hal_hsp_trgin_config_t *p_config)
{
  const HSP_TypeDef *p_hspx;
  const __IOM uint32_t *p_trginselr;
  uint32_t reg_idx;
  uint32_t reg_pos;
  uint32_t bitfield_idx;
  uint32_t reg_mask;
  uint32_t reg_value;
  uint32_t id;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN(trgin_id));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get the polarity */
  uint32_t trgin_mask = (trgin_id >> HSP_ITFENR_TRGI0EN_Pos);

  p_config->polarity = (hal_hsp_trgin_polarity_t)
                       (STM32_READ_BIT(p_hspx->TRGINCFGR, trgin_mask) != 0U);

  /* Get the trigger source */
  p_trginselr = &p_hspx->TRGINSELR0;

  id = STM32_POSITION_VAL(trgin_mask);
  reg_idx = ((uint32_t)id) / HSP_REG_TRGINSEL_CFG_NBR;
  bitfield_idx = ((uint32_t)id) % HSP_REG_TRGINSEL_CFG_NBR;
  reg_pos = HSP_TRGINSELR0_TRG0SEL_Pos + ((uint32_t)bitfield_idx * HSP_REG_TRGINSEL_SELECT_FIELD_SIZE);
  reg_mask = (HSP_TRGINSELR0_TRG0SEL_Msk << reg_pos);

  reg_value = (uint32_t)(STM32_READ_BIT(p_trginselr[reg_idx], reg_mask) >> reg_pos);

  p_config->source = (hal_hsp_trgin_source_t)reg_value;
}

/**
  * @brief  Enable a set of Trigger Input interfaces.
  * @param  hhsp       Pointer to a @ref hal_hsp_handle_t.
  * @param  trgin_ids  Trigger Input interface identifiers.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_TRGIN_0
  *             @arg HAL_HSP_TRGIN_1
  *             @arg HAL_HSP_TRGIN_2
  *             @arg HAL_HSP_TRGIN_3
  *             @arg HAL_HSP_TRGIN_4
  *             @arg HAL_HSP_TRGIN_5
  *             @arg HAL_HSP_TRGIN_6
  *             @arg HAL_HSP_TRGIN_7
  *             @arg HAL_HSP_TRGIN_8
  *             @arg HAL_HSP_TRGIN_9
  *             @arg HAL_HSP_TRGIN_ALL
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TRGIN_EnableTriggers(const hal_hsp_handle_t *hhsp, uint32_t trgin_ids)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_COMBINATION(trgin_ids));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->ITFENR, trgin_ids);

  return HAL_OK;
}

/**
  * @brief  Disable a set of Trigger Input interfaces.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  trgin_ids Set of Trigger Input interface identifiers.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_TRGIN_0
  *             @arg HAL_HSP_TRGIN_1
  *             @arg HAL_HSP_TRGIN_2
  *             @arg HAL_HSP_TRGIN_3
  *             @arg HAL_HSP_TRGIN_4
  *             @arg HAL_HSP_TRGIN_5
  *             @arg HAL_HSP_TRGIN_6
  *             @arg HAL_HSP_TRGIN_7
  *             @arg HAL_HSP_TRGIN_8
  *             @arg HAL_HSP_TRGIN_9
  *             @arg HAL_HSP_TRGIN_ALL
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TRGIN_DisableTriggers(const hal_hsp_handle_t *hhsp, uint32_t trgin_ids)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_COMBINATION(trgin_ids));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ITFENR, trgin_ids);

  return HAL_OK;
}

/**
  * @brief  Check if the Trigger Input x Interface is enabled.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  trgin_id  Trigger Input interface identifier.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_TRGIN_0
  *             @arg HAL_HSP_TRGIN_1
  *             @arg HAL_HSP_TRGIN_2
  *             @arg HAL_HSP_TRGIN_3
  *             @arg HAL_HSP_TRGIN_4
  *             @arg HAL_HSP_TRGIN_5
  *             @arg HAL_HSP_TRGIN_6
  *             @arg HAL_HSP_TRGIN_7
  *             @arg HAL_HSP_TRGIN_8
  *             @arg HAL_HSP_TRGIN_9
  * @retval HAL_HSP_TRGIN_DISABLED  The Trigger Input instance is disabled.
  * @retval HAL_HSP_TRGIN_ENABLED   The Trigger Input instance is enabled.
  */
hal_hsp_trgin_status_t HAL_HSP_TRGIN_IsEnabledTrigger(const hal_hsp_handle_t *hhsp, uint32_t trgin_id)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_TRGIN(trgin_id));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->ITFENR, trgin_id);

  return ((status == 0U) ? HAL_HSP_TRGIN_DISABLED : HAL_HSP_TRGIN_ENABLED);
}

#if defined(USE_HAL_HSP_TRGIN_IT) && (USE_HAL_HSP_TRGIN_IT == 1)
/**
  * @brief  Enable Trigger Input Error Interrupts.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  interrupts  Mask of Trigger Input Error Interrupts.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_ERR_TRGIN_OVR
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TRGIN_EnableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_IT_ERR(interrupts));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (interrupts != HAL_HSP_IT_NONE)
  {
    STM32_SET_BIT(p_hspx->ERR_IER, interrupts);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the Trigger Input Error Interrupts.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  interrupts  Mask of Trigger Input Error Interrupts.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_TRGIN_ERR_IT_OVR
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TRGIN_DisableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_IT_ERR(interrupts));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ERR_IER, interrupts);

  return HAL_OK;
}
#endif /* USE_HAL_HSP_TRGIN_IT */

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group3_4
  * @{
This section provides a set of functions to manage the Processing Request Control (PRC):
  - HAL_HSP_PRC_SetMultiTaskConfig()          : configure PRC task mapping.
  - HAL_HSP_PRC_GetMultiTaskConfig()          : retrieve PRC task mapping.
  - HAL_HSP_PRC_EnableEvents()                : enable a set of PRC events.
  - HAL_HSP_PRC_DisableEvents()               : disable a set of PRC events.
  - HAL_HSP_PRC_GetActiveEvents()             : get the currently active PRC events.
  - HAL_HSP_PRC_SWRequestTask()               : request task execution by software.
  - HAL_HSP_PRC_PollForEvent()                : poll for PRC events.
  - HAL_HSP_PRC_SWRequestLowestPriorityTask() : request lowest priority task execution.
  - HAL_HSP_PRC_GetSWRequestLowestPriorityStatusAndClearFlag() : get status and clear flag.
  */
/* Event Management ----------------------------------------------------------*/
/**
  * @brief  Configure a set of Task attached to a PRC event in the Processing Request Controller.
  * @param  hhsp               Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array     Pointer to a @ref hal_hsp_prc_task_config_t.
  * @param  config_array_size  Number of configuration in the array.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_INVALID_PARAM Pointer of configuration is NULL.
  * @retval HAL_ERROR  Failed to configure.
  */
hal_status_t HAL_HSP_PRC_SetMultiTaskConfig(const hal_hsp_handle_t *hhsp,
                                            const hal_hsp_prc_task_config_t *p_config_array, uint32_t config_array_size)
{
  HSP_TypeDef *p_hspx;
  __IOM uint32_t *p_evtsrcr;
  __IOM uint32_t *p_esyncsrcr;
  uint32_t event_id;
  uint32_t reg_idx;
  uint32_t bitfield_idx;
  uint32_t reg_pos;
  uint32_t reg_mask;
  uint32_t reg_value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_PRC_EVENT_NBR(p_hspx));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config_array == NULL) || (config_array_size > HSP_PRC_EVENT_NBR(p_hspx)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_evtsrcr = &(p_hspx->EVTSRC0R);
  p_esyncsrcr = &(p_hspx->ESYNC0SRCR);

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    ASSERT_DBG_PARAM(IS_HSP_EVENT_SOURCE(p_config_array[idx].source));
    ASSERT_DBG_PARAM(IS_HSP_PRC_TASK_SYNC_SOURCE(p_config_array[idx].sync));

    event_id = (((uint32_t)p_config_array[idx].source & HSP_EVENT_PRIO_MSK) >> HAL_HSP_EVENT_PRIO_POS);
    reg_idx = ((event_id - 1UL) / HSP_REG_EVTSRC_CFG_NBR);
    bitfield_idx = ((event_id - 1UL) % HSP_REG_EVTSRC_CFG_NBR);

    reg_pos = HSP_EVTSRC0R_EVT1SRC_Pos + (bitfield_idx * HSP_REG_EVTSRC_FIELD_SIZE);
    reg_mask = (HSP_EVTSRC0R_EVT1SRC_Msk << reg_pos);
    reg_value = (((((uint32_t)p_config_array[idx].source) & HSP_EVENT_SOURCE_MSK) >> HAL_HSP_EVENT_SOURCE_POS)
                 << reg_pos);

    /* Update Event source register */
    STM32_MODIFY_REG(p_evtsrcr[reg_idx], reg_mask, reg_value);

    /* Update Event synchronization register */
    if (p_config_array[idx].sync != HAL_HSP_PRC_TASK_SYNC_NONE)
    {
      reg_mask = (HSP_ESYNC0SRCR_EV1SSRC_Msk << reg_pos);
      reg_value = (((((uint32_t)p_config_array[idx].sync) & HSP_ESYNC0SRCR_EV1SSRC_Msk)
                    >> HSP_ESYNC0SRCR_EV1SSRC_Pos) << reg_pos);

      STM32_MODIFY_REG(p_esyncsrcr[reg_idx], reg_mask, reg_value);

      STM32_SET_BIT(p_hspx->ESYNCENR, (1UL << event_id));
    }
    else
    {
      STM32_CLEAR_BIT(p_hspx->ESYNCENR, (1UL << event_id));
    }
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the configuration of tasks attached to PRC events in the Processing Request Controller.
  * @param  hhsp               Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array     Pointer to an array of @ref hal_hsp_prc_task_config_t.
  * @param  config_array_size  Number of config to retrieve.
  */
void HAL_HSP_PRC_GetMultiTaskConfig(const hal_hsp_handle_t *hhsp,
                                    hal_hsp_prc_task_config_t *p_config_array, uint32_t config_array_size)
{
  const HSP_TypeDef *p_hspx;
  const __IOM uint32_t *p_evtsrcr;
  const __IOM uint32_t *p_esyncsrcr;
  uint32_t reg_idx;
  uint32_t bitfield_idx;
  uint32_t reg_pos;
  uint32_t reg_mask;
  uint32_t reg_value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_PRC_EVENT_NBR(p_hspx));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_evtsrcr = &(p_hspx->EVTSRC0R);
  p_esyncsrcr = &(p_hspx->ESYNC0SRCR);

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    reg_idx = (idx / HSP_REG_EVTSRC_CFG_NBR);
    bitfield_idx = (idx % HSP_REG_EVTSRC_CFG_NBR);

    reg_pos = HSP_EVTSRC0R_EVT1SRC_Pos + (bitfield_idx * HSP_REG_EVTSRC_FIELD_SIZE);
    reg_mask = (HSP_EVTSRC0R_EVT1SRC_Msk << reg_pos);

    /* Get Event source register */
    reg_value = STM32_READ_BIT(p_evtsrcr[reg_idx], reg_mask);

    p_config_array[idx].source = (hal_hsp_event_source_t)
                                 (((uint32_t)(reg_value >> reg_pos) << HAL_HSP_EVENT_SOURCE_POS)
                                  | (uint32_t)((reg_pos << HAL_HSP_EVENT_REG_SRC_BITFIELD_POSITION_POS))
                                  | (uint32_t)((idx + 1U) << HAL_HSP_EVENT_PRIO_POS));

    /* Get Event synchronization register */
    if (STM32_IS_BIT_SET(p_hspx->ESYNCENR, (1UL << (idx + 1U))))
    {
      reg_mask = (HSP_ESYNC0SRCR_EV1SSRC_Msk << reg_pos);

      reg_value = STM32_READ_BIT(p_esyncsrcr[reg_idx], reg_mask);

      p_config_array[idx].sync = (hal_hsp_prc_task_sync_source_t)(reg_value >> reg_pos);
    }
    else
    {
      p_config_array[idx].sync = HAL_HSP_PRC_TASK_SYNC_NONE;
    }
  }
}

/**
  * @brief  Enable a set of Events in the Processing Request Controller.
  * @param  hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param  events Mask of Event to enable.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_EVENT_1:   PRC Event number 1
  *             @arg HAL_HSP_EVENT_2:   PRC Event number 2
  *             @arg HAL_HSP_EVENT_3:   PRC Event number 3
  *             @arg HAL_HSP_EVENT_4:   PRC Event number 4
  *             @arg HAL_HSP_EVENT_5:   PRC Event number 5
  *             @arg HAL_HSP_EVENT_6:   PRC Event number 6
  *             @arg HAL_HSP_EVENT_7:   PRC Event number 7
  *             @arg HAL_HSP_EVENT_8:   PRC Event number 8
  *             @arg HAL_HSP_EVENT_9:   PRC Event number 9
  *             @arg HAL_HSP_EVENT_10:  PRC Event number 10
  *             @arg HAL_HSP_EVENT_11:  PRC Event number 11
  *             @arg HAL_HSP_EVENT_12:  PRC Event number 12
  *             @arg HAL_HSP_EVENT_13:  PRC Event number 13
  *             @arg HAL_HSP_EVENT_14:  PRC Event number 14
  *             @arg HAL_HSP_EVENT_15:  PRC Event number 15
  *             @arg HAL_HSP_EVENT_16:  PRC Event number 16
  *             @arg HAL_HSP_EVENT_17:  PRC Event number 17
  *             @arg HAL_HSP_EVENT_18:  PRC Event number 18
  *             @arg HAL_HSP_EVENT_19:  PRC Event number 19
  *             @arg HAL_HSP_EVENT_20:  PRC Event number 20
  *             @arg HAL_HSP_EVENT_21:  PRC Event number 21
  *             @arg HAL_HSP_EVENT_22:  PRC Event number 22
  *             @arg HAL_HSP_EVENT_ALL: ALL PRC Event
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_PRC_EnableEvents(const hal_hsp_handle_t *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->EVTENR, events);

  return HAL_OK;
}

/**
  * @brief  Disable a set of Events in the Processing Request Controller.
  * @param  hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param  events Mask of Event to disable.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_EVENT_1:   PRC Event number 1
  *             @arg HAL_HSP_EVENT_2:   PRC Event number 2
  *             @arg HAL_HSP_EVENT_3:   PRC Event number 3
  *             @arg HAL_HSP_EVENT_4:   PRC Event number 4
  *             @arg HAL_HSP_EVENT_5:   PRC Event number 5
  *             @arg HAL_HSP_EVENT_6:   PRC Event number 6
  *             @arg HAL_HSP_EVENT_7:   PRC Event number 7
  *             @arg HAL_HSP_EVENT_8:   PRC Event number 8
  *             @arg HAL_HSP_EVENT_9:   PRC Event number 9
  *             @arg HAL_HSP_EVENT_10:  PRC Event number 10
  *             @arg HAL_HSP_EVENT_11:  PRC Event number 11
  *             @arg HAL_HSP_EVENT_12:  PRC Event number 12
  *             @arg HAL_HSP_EVENT_13:  PRC Event number 13
  *             @arg HAL_HSP_EVENT_14:  PRC Event number 14
  *             @arg HAL_HSP_EVENT_15:  PRC Event number 15
  *             @arg HAL_HSP_EVENT_16:  PRC Event number 16
  *             @arg HAL_HSP_EVENT_17:  PRC Event number 17
  *             @arg HAL_HSP_EVENT_18:  PRC Event number 18
  *             @arg HAL_HSP_EVENT_19:  PRC Event number 19
  *             @arg HAL_HSP_EVENT_20:  PRC Event number 20
  *             @arg HAL_HSP_EVENT_21:  PRC Event number 21
  *             @arg HAL_HSP_EVENT_22:  PRC Event number 22
  *             @arg HAL_HSP_EVENT_ALL: ALL PRC Event
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_PRC_DisableEvents(const hal_hsp_handle_t *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->EVTENR, events);

  return HAL_OK;
}

/**
  * @brief  Return the Status of each Event interface.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @note   The returned value can be a combination of following values:
  *             @arg HAL_HSP_EVENT_1:   PRC Event number 1
  *             @arg HAL_HSP_EVENT_2:   PRC Event number 2
  *             @arg HAL_HSP_EVENT_3:   PRC Event number 3
  *             @arg HAL_HSP_EVENT_4:   PRC Event number 4
  *             @arg HAL_HSP_EVENT_5:   PRC Event number 5
  *             @arg HAL_HSP_EVENT_6:   PRC Event number 6
  *             @arg HAL_HSP_EVENT_7:   PRC Event number 7
  *             @arg HAL_HSP_EVENT_8:   PRC Event number 8
  *             @arg HAL_HSP_EVENT_9:   PRC Event number 9
  *             @arg HAL_HSP_EVENT_10:  PRC Event number 10
  *             @arg HAL_HSP_EVENT_11:  PRC Event number 11
  *             @arg HAL_HSP_EVENT_12:  PRC Event number 12
  *             @arg HAL_HSP_EVENT_13:  PRC Event number 13
  *             @arg HAL_HSP_EVENT_14:  PRC Event number 14
  *             @arg HAL_HSP_EVENT_15:  PRC Event number 15
  *             @arg HAL_HSP_EVENT_16:  PRC Event number 16
  *             @arg HAL_HSP_EVENT_17:  PRC Event number 17
  *             @arg HAL_HSP_EVENT_18:  PRC Event number 18
  *             @arg HAL_HSP_EVENT_19:  PRC Event number 19
  *             @arg HAL_HSP_EVENT_20:  PRC Event number 20
  *             @arg HAL_HSP_EVENT_21:  PRC Event number 21
  *             @arg HAL_HSP_EVENT_22:  PRC Event number 22
  * @return Bitmask of active PRC events. This value can combine one or more
  *         HAL_HSP_EVENT_x values.
  */
uint32_t HAL_HSP_PRC_GetActiveEvents(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return STM32_READ_BIT(p_hspx->EVTENR, HSP_EVTENR_EVTEN_Msk);
}

/**
  * @brief  Request the triggering of events to the Processing Request Controller.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  events  Mask of Events to trigger.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_EVENT_1:   PRC Event number 1
  *             @arg HAL_HSP_EVENT_2:   PRC Event number 2
  *             @arg HAL_HSP_EVENT_3:   PRC Event number 3
  *             @arg HAL_HSP_EVENT_4:   PRC Event number 4
  *             @arg HAL_HSP_EVENT_5:   PRC Event number 5
  *             @arg HAL_HSP_EVENT_6:   PRC Event number 6
  *             @arg HAL_HSP_EVENT_7:   PRC Event number 7
  *             @arg HAL_HSP_EVENT_8:   PRC Event number 8
  *             @arg HAL_HSP_EVENT_9:   PRC Event number 9
  *             @arg HAL_HSP_EVENT_10:  PRC Event number 10
  *             @arg HAL_HSP_EVENT_11:  PRC Event number 11
  *             @arg HAL_HSP_EVENT_12:  PRC Event number 12
  *             @arg HAL_HSP_EVENT_13:  PRC Event number 13
  *             @arg HAL_HSP_EVENT_14:  PRC Event number 14
  *             @arg HAL_HSP_EVENT_15:  PRC Event number 15
  *             @arg HAL_HSP_EVENT_16:  PRC Event number 16
  *             @arg HAL_HSP_EVENT_17:  PRC Event number 17
  *             @arg HAL_HSP_EVENT_18:  PRC Event number 18
  *             @arg HAL_HSP_EVENT_19:  PRC Event number 19
  *             @arg HAL_HSP_EVENT_20:  PRC Event number 20
  *             @arg HAL_HSP_EVENT_21:  PRC Event number 21
  *             @arg HAL_HSP_EVENT_22:  PRC Event number 22
  * @note  The selected events must be configured with CSEG interface as source.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_PRC_SWRequestTask(const hal_hsp_handle_t *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Use CSEG and the PRC must be configured as well */
  STM32_SET_BIT(p_hspx->CSEGR, events);

  return HAL_OK;
}

/**
  * @brief  Wait the end of processing of events triggered by the CPU.
  * @param  hhsp       Pointer to a @ref hal_hsp_handle_t.
  * @param  poll_mode  Polling mode.
  * @param  events     Mask of Event to poll.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_EVENT_1:   PRC Event number 1
  *             @arg HAL_HSP_EVENT_2:   PRC Event number 2
  *             @arg HAL_HSP_EVENT_3:   PRC Event number 3
  *             @arg HAL_HSP_EVENT_4:   PRC Event number 4
  *             @arg HAL_HSP_EVENT_5:   PRC Event number 5
  *             @arg HAL_HSP_EVENT_6:   PRC Event number 6
  *             @arg HAL_HSP_EVENT_7:   PRC Event number 7
  *             @arg HAL_HSP_EVENT_8:   PRC Event number 8
  *             @arg HAL_HSP_EVENT_9:   PRC Event number 9
  *             @arg HAL_HSP_EVENT_10:  PRC Event number 10
  *             @arg HAL_HSP_EVENT_11:  PRC Event number 11
  *             @arg HAL_HSP_EVENT_12:  PRC Event number 12
  *             @arg HAL_HSP_EVENT_13:  PRC Event number 13
  *             @arg HAL_HSP_EVENT_14:  PRC Event number 14
  *             @arg HAL_HSP_EVENT_15:  PRC Event number 15
  *             @arg HAL_HSP_EVENT_16:  PRC Event number 16
  *             @arg HAL_HSP_EVENT_17:  PRC Event number 17
  *             @arg HAL_HSP_EVENT_18:  PRC Event number 18
  *             @arg HAL_HSP_EVENT_19:  PRC Event number 19
  *             @arg HAL_HSP_EVENT_20:  PRC Event number 20
  *             @arg HAL_HSP_EVENT_21:  PRC Event number 21
  *             @arg HAL_HSP_EVENT_22:  PRC Event number 22
  * @param  timeout_ms       Timeout duration (in ms).
  * @param  p_events_status  Pointer to return the ended event.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  */
hal_status_t HAL_HSP_PRC_PollForEvent(const hal_hsp_handle_t *hhsp, hal_hsp_polling_mode_t poll_mode,
                                      uint32_t events, uint32_t timeout_ms,
                                      uint32_t *p_events_status)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_events_status != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_events_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HSP_POLLING_MODE(poll_mode));
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return HSP_PollRegisterFlags(poll_mode, &p_hspx->PEVTLR,
                               events, HSP_GetPolledFlagsActiveLow,
                               timeout_ms, p_events_status);
}

/**
  * @brief  Request the execution of task with a lowest priority.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  task_id     Task Number.
  * @param  sync        Task synchronization source.
  * @param  interrupts  Interrupt mask.
  *         This parameter can be a combination of the following values:
  *             @arg HAL_HSP_IT_NONE: No interrupt
  *             @arg HAL_HSP_PRC_IT_CDEG_READY: The IT of CDEG interface
  * @note   If a task is already pending, the function will return HAL_BUSY.
  * @retval HAL_OK    Operation completed successfully.
  * @retval HAL_BUSY  A request is pending.
  */
hal_status_t HAL_HSP_PRC_SWRequestLowestPriorityTask(const hal_hsp_handle_t *hhsp,
                                                     hal_hsp_task_t task_id, hal_hsp_prc_task_sync_source_t sync,
                                                     uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TASK(task_id));
  ASSERT_DBG_PARAM(IS_HSP_PRC_TASK_SYNC_SOURCE(sync));
  ASSERT_DBG_PARAM(IS_HSP_PRC_SWREQUEST_IT(interrupts));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Check if a task is in progress */
  if (STM32_READ_BIT(p_hspx->CDEGR, HSP_CDEGR_CDEGBSY) == HSP_CDEGR_CDEGBSY)
  {
    return HAL_BUSY;
  }

  /* Initialize the task Synchronization */
  if (sync == HAL_HSP_PRC_TASK_SYNC_NONE)
  {
    STM32_CLEAR_BIT(p_hspx->ESYNCENR, HSP_ESYNCENR_CDEGSYNCEN);
  }
  else
  {
    STM32_MODIFY_REG(p_hspx->ESYNC2SRCR, HSP_ESYNC2SRCR_CDEGSSRC_Msk, (uint32_t)sync << HSP_ESYNC2SRCR_CDEGSSRC_Pos);
    STM32_SET_BIT(p_hspx->ESYNCENR, HSP_ESYNCENR_CDEGSYNCEN);
  }

  /* Enable the interrupts */
  if (interrupts != HAL_HSP_IT_NONE)
  {
    STM32_SET_BIT(p_hspx->EVT_IER, interrupts);
  }

  /* Post the Task to execute with lowest priority */
  STM32_MODIFY_REG(p_hspx->CDEGR, HSP_CDEGR_CTSKN, ((uint32_t)task_id) << HSP_CDEGR_CTSKN_Pos);

  return HAL_OK;
}

/**
  * @brief  Get the SW Request status for the task execution with a lowest priority and clear the flag.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_HSP_PRC_LOWEST_PRIO_TASK_NONE  CPU can request a task with lowest priority.
  * @retval HAL_HSP_PRC_LOWEST_PRIO_TASK_ONGOING  A request is pending.
  */
hal_hsp_prc_lowest_priority_task_status_t HAL_HSP_PRC_GetSWRequestLowestPriorityStatusAndClearFlag(
  const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Check if a task is in progress */
  if (STM32_IS_BIT_SET(p_hspx->CDEGR, HSP_CDEGR_CDEGBSY))
  {
    return HAL_HSP_PRC_LOWEST_PRIO_TASK_ONGOING;
  }
  else
  {
    STM32_SET_BIT(p_hspx->EVT_ICR, HSP_EVT_ICR_CDEGRDYC);
  }

  return HAL_HSP_PRC_LOWEST_PRIO_TASK_NONE;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group4
  * @{
This section provides a set of functions to manage the SmartClocking of some HSP blocks:
  - HAL_HSP_SMARTCLOCKING_Enable()    : enable SmartClocking capability of some HSP blocks.
  - HAL_HSP_SMARTCLOCKING_Disable()   : disable SmartClocking capability of some HSP blocks.
  - HAL_HSP_SMARTCLOCKING_IsEnabled() : check whether SmartClocking is enabled for a given block.
  */
/**
  * @brief  Enable the Smart Clocking of some HSP blocks.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  clocks  Mask of clocks to enable.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SMARTCLOCKING_CTRL
  *             @arg HAL_HSP_SMARTCLOCKING_SPE
  *             @arg HAL_HSP_SMARTCLOCKING_MMC
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_SMARTCLOCKING_Enable(const hal_hsp_handle_t *hhsp, uint32_t clocks)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SMARTCLOCKING(clocks));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->CR, clocks);

  return HAL_OK;
}

/**
  * @brief  Disable the Smart Clocking of some HSP blocks.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  clocks  Mask of clocks to disable.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SMARTCLOCKING_CTRL
  *             @arg HAL_HSP_SMARTCLOCKING_SPE
  *             @arg HAL_HSP_SMARTCLOCKING_MMC
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_SMARTCLOCKING_Disable(const hal_hsp_handle_t *hhsp, uint32_t clocks)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SMARTCLOCKING(clocks));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->CR, clocks);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the specified SmartClocking block is set.
  * @param  hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param  clock  Clock.
  *         This parameter can be one of the following values:
  *             @arg HAL_HSP_SMARTCLOCKING_CTRL
  *             @arg HAL_HSP_SMARTCLOCKING_SPE
  *             @arg HAL_HSP_SMARTCLOCKING_MMC
  * @retval HAL_HSP_SMARTCLOCKING_DISABLED.
  * @retval HAL_HSP_SMARTCLOCKING_ENABLED.
  */
hal_hsp_smartclocking_status_t HAL_HSP_SMARTCLOCKING_IsEnabled(const hal_hsp_handle_t *hhsp, uint32_t clock)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SMARTCLOCKING(clock));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Note: if the bitfield is set to 0, it means the SmartClocking is enabled ! */
  return (((STM32_IS_BIT_SET(p_hspx->CR, clock)) ?
           HAL_HSP_SMARTCLOCKING_DISABLED : HAL_HSP_SMARTCLOCKING_ENABLED));
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group5
  * @{
This section provides a set of functions to manage the Task Comparators:
  - HAL_HSP_TCU_StartComparator()      : configure and start a task comparator.
  - HAL_HSP_TCU_StopComparator()       : stop a task comparator.
  - HAL_HSP_TCU_StartOverlapDetector() : start the task overlap detector.
  - HAL_HSP_TCU_StopOverlapDetector()  : stop the task overlap detector.
  - HAL_HSP_TCU_PollForEvent()         : poll for Task Comparator Unit events.
  */
/**
  * @brief  Start the Task Comparator Unit.
  * @param  hhsp     Pointer to a @ref hal_hsp_handle_t.
  * @param  tcu_id   Task Comparator Unit ID.
  * @param  task_id  Task ID to monitor.
  * @param  interrupts  Mask of Task Comparator Unit Interrupts.
  *         This parameter can be one of following values:
  *            @arg @ref  HAL_HSP_IT_NONE
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_0_TASK_STARTED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_1_TASK_STARTED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_2_TASK_STARTED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_3_TASK_STARTED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_0_TASK_ENDED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_1_TASK_ENDED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_2_TASK_ENDED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_3_TASK_ENDED
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_0_ALL
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_1_ALL
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_2_ALL
  *            @arg @ref  HAL_HSP_TCU_IT_CMP_3_ALL
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TCU_StartComparator(const hal_hsp_handle_t *hhsp,
                                         hal_hsp_task_comparator_t tcu_id, hal_hsp_task_t task_id,
                                         uint32_t interrupts)
{
#if !defined(USE_HAL_HSP_TCU_IT) || (USE_HAL_HSP_TCU_IT != 1)
  STM32_UNUSED(interrupts);
#endif /* USE_HAL_HSP_TCU_IT */

  HSP_TypeDef *p_hspx;
  uint32_t reg_pos;
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  uint32_t its_mask;
#endif /* USE_HAL_HSP_TCU_IT */

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TCU(tcu_id));
  ASSERT_DBG_PARAM(IS_HSP_TASK(task_id));
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  ASSERT_DBG_PARAM(IS_HSP_TCU_IT(tcu_id, interrupts));
#else
  ASSERT_DBG_PARAM(interrupts == HAL_HSP_IT_NONE);
#endif /* USE_HAL_HSP_TCU_IT */

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_pos = ((uint32_t)tcu_id) * HSP_REG_TCUCFGR_BITFIELD_SIZE;
  STM32_SET_BIT(p_hspx->TCUCFGR, (HSP_TCUCFGR_TC0EN_Msk << reg_pos));
  STM32_MODIFY_REG(p_hspx->TCUCFGR, (HSP_TCUCFGR_TSKCMP0_Msk << reg_pos), ((uint32_t)task_id) << reg_pos);

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  if (interrupts != HAL_HSP_IT_NONE)
  {
    its_mask = (HAL_HSP_TCU_IT_CMP_0_ALL << (uint32_t)tcu_id);
    STM32_MODIFY_REG(p_hspx->EVT_IER, its_mask, interrupts);
  }
#endif /*USE_HAL_HSP_TCU_IT */

  return HAL_OK;
}

/**
  * @brief  Stop the Task Comparator Unit.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  tcu_id   Task Comparator Unit ID.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TCU_StopComparator(const hal_hsp_handle_t *hhsp, hal_hsp_task_comparator_t tcu_id)
{
  HSP_TypeDef *p_hspx;
  uint32_t reg_pos;
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  uint32_t its_mask;
#endif /* USE_HAL_HSP_TCU_IT */

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TCU(tcu_id));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_pos = ((uint32_t)tcu_id) * HSP_REG_TCUCFGR_BITFIELD_SIZE;
  STM32_CLEAR_BIT(p_hspx->TCUCFGR, (HSP_TCUCFGR_TC0EN_Msk << reg_pos));

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  its_mask = (HAL_HSP_TCU_IT_CMP_0_ALL << (uint32_t)tcu_id);
  STM32_CLEAR_BIT(p_hspx->EVT_IER, its_mask);
#endif /*USE_HAL_HSP_TCU_IT */

  return HAL_OK;
}

/**
  * @brief  Start the Task Overlap feature in polling mode.
  * @param  hhsp     Pointer to a @ref hal_hsp_handle_t.
  * @param  lower_task_id   Lower Task ID.
  * @param  higher_task_id  Higher Task ID.
  * @param  interrupts      Mask of Task Comparator Overlap Interrupts.
  *         This parameter can be one of following values:
  *            @arg @ref  HAL_HSP_IT_NONE
  *            @arg @ref  HAL_HSP_TCU_IT_TASK_OVL
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_TCU_StartOverlapDetector(const hal_hsp_handle_t *hhsp,
                                              hal_hsp_task_t lower_task_id, hal_hsp_task_t higher_task_id,
                                              uint32_t interrupts)
{
#if !defined(USE_HAL_HSP_TCU_IT) || (USE_HAL_HSP_TCU_IT != 1)
  STM32_UNUSED(interrupts);
#endif /* USE_HAL_HSP_TCU_IT */

  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TASK(lower_task_id));
  ASSERT_DBG_PARAM(IS_HSP_TASK(higher_task_id));
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  ASSERT_DBG_PARAM(IS_HSP_TASK_OVERLAP_IT(interrupts));
#endif /* USE_HAL_HSP_TCU_IT */

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->TOVLPCR, HSP_TOVLPCR_TOVLPEN);
  STM32_MODIFY_REG(p_hspx->TOVLPCR, HSP_TOVLPCR_LTNB_Msk, ((uint32_t)lower_task_id) << HSP_TOVLPCR_LTNB_Pos);
  STM32_MODIFY_REG(p_hspx->TOVLPCR, HSP_TOVLPCR_HTNB_Msk, ((uint32_t)higher_task_id) << HSP_TOVLPCR_HTNB_Pos);

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  if (interrupts != HAL_HSP_IT_NONE)
  {
    STM32_MODIFY_REG(p_hspx->EVT_IER, HSP_EVT_IER_TOVLPIE_Msk, interrupts);
  }
#endif /* USE_HAL_HSP_TCU_IT */

  return HAL_OK;
}

/**
  * @brief  Stop the Task Overlap feature in polling mode.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_TCU_StopOverlapDetector(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->TOVLPCR, HSP_TOVLPCR_TOVLPEN);

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  STM32_CLEAR_BIT(p_hspx->EVT_IER, HSP_EVT_IER_TOVLPIE);
#endif /* USE_HAL_HSP_TCU_IT */

  return HAL_OK;
}

/**
  * @brief  Poll until specified flags are raised.
  * @param  hhsp       Pointer to a @ref hal_hsp_handle_t.
  * @param  poll_mode  Polling mode.
  * @param  flags      Mask of event flags to poll.
  *         This parameter can be a combination of following values:
  *            @arg @ref HAL_HSP_FLAG_TCU_TASK_OVL
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_0_TASK_STARTED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_1_TASK_STARTED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_2_TASK_STARTED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_3_TASK_STARTED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_0_TASK_ENDED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_1_TASK_ENDED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_2_TASK_ENDED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_3_TASK_ENDED
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_0_ALL
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_1_ALL
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_2_ALL
  *            @arg @ref HAL_HSP_FLAG_TCU_CMP_3_ALL
  *            @arg @ref HAL_HSP_FLAG_TCU_TASK_OVL
  *            @arg @ref HAL_HSP_FLAG_TCU_ALL
  * @param  timeout_ms Timeout duration (in ms).
  * @param  p_flags_status Pointer to return the raised flags.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  * @retval HAL_TIMEOUT  Timeout occurred.
  */
hal_status_t HAL_HSP_TCU_PollForEvent(const hal_hsp_handle_t *hhsp,
                                      hal_hsp_polling_mode_t poll_mode, uint32_t flags,
                                      uint32_t timeout_ms, uint32_t *p_flags_status)
{
  HSP_TypeDef *p_hspx;
  hal_status_t status;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_flags_status != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_flags_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HSP_POLLING_MODE(poll_mode));
  ASSERT_DBG_PARAM(IS_HSP_TCU_FLAGS(flags));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = HSP_PollRegisterFlags(poll_mode, &p_hspx->EVT_ISR,
                                 flags, HSP_GetPolledFlagsActiveHigh,
                                 timeout_ms, p_flags_status);

  if (status == HAL_OK)
  {
    /* Clear selected flags */
    STM32_WRITE_REG(p_hspx->EVT_ICR, *p_flags_status);
  }

  return status;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group6
  * @{
This section provides a set of functions to manage the HSP Trigger Outputs:
  - HAL_HSP_TRGO_SetMultiConfig() : configure HSP TRGO sources.
  - HAL_HSP_TRGO_GetMultiConfig() : retrieve HSP TRGO configuration.
  - HAL_HSP_TRGO_Enable()         : enable HSP Trigger Outputs.
  - HAL_HSP_TRGO_Disable()        : disable HSP Trigger Outputs.
  - HAL_HSP_TRGO_IsEnabled()      : check whether Trigger Outputs are enabled.
  */
/**
  * @brief  Configure a set of Trigger Output.
  * @param  hhsp               Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array     Pointer to an array of @ref hal_hsp_trgo_config_t.
  * @param  config_array_size  Number of configuration in the array.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_TRGO_SetMultiConfig(const hal_hsp_handle_t *hhsp,
                                         const hal_hsp_trgo_config_t *p_config_array, uint32_t config_array_size)
{
  HSP_TypeDef *p_hspx;
  uint32_t bitfld_mask;
  uint32_t bitfld_pos;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_TRGO_NBR(p_hspx));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config_array == NULL) || (config_array_size > HSP_TRGO_NBR(p_hspx)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    ASSERT_DBG_PARAM(IS_HSP_TRGO_TRIGGER((p_config_array[idx].trigger_id)));
    ASSERT_DBG_PARAM(IS_HSP_TRGO_SOURCE((p_config_array[idx].source)));
    bitfld_pos = HSP_TRGOCFGR_TRGO0SRC_Pos
                 + (((uint32_t)(p_config_array[idx].trigger_id)) * HSP_REG_TRGOCFGR_BITFIELD_SRC_SIZE);
    bitfld_mask = HSP_TRGOCFGR_TRGO0SRC << bitfld_pos;
    STM32_MODIFY_REG(p_hspx->TRGOCFGR, bitfld_mask, (uint32_t)(p_config_array[idx].source) << bitfld_pos);
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the TRGO configurations.
  * @param  hhsp              Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array    Pointer to an array of @ref hal_hsp_trgo_config_t.
  * @param  config_array_size  Number of configuration in the array.
  */
void HAL_HSP_TRGO_GetMultiConfig(const hal_hsp_handle_t *hhsp,
                                 hal_hsp_trgo_config_t *p_config_array, uint32_t config_array_size)
{
  const HSP_TypeDef *p_hspx;
  uint32_t bitfld_mask;
  uint32_t bitfld_pos;
  uint32_t reg_value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_TRGO_NBR(p_hspx));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    bitfld_pos = HSP_TRGOCFGR_TRGO0SRC_Pos + (idx * HSP_REG_TRGOCFGR_BITFIELD_SRC_SIZE);
    bitfld_mask = HSP_TRGOCFGR_TRGO0SRC << bitfld_pos;
    reg_value = STM32_READ_BIT(p_hspx->TRGOCFGR, bitfld_mask);
    p_config_array[idx].trigger_id = (hal_hsp_trgo_trigger_t)idx;
    p_config_array[idx].source = (hal_hsp_trgo_source_t)(reg_value >> bitfld_pos);
  }
}

/**
  * @brief  Enable the HSP Output.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TRGO_Enable(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->ITFENR, HSP_ITFENR_TRGOEN);

  return HAL_OK;
}

/**
  * @brief  Disable the HSP Output.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TRGO_Disable(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ITFENR, HSP_ITFENR_TRGOEN);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the Trigger Output is enabled.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_HSP_TRGO_ENABLED   Output is enabled.
  * @retval HAL_HSP_TRGO_DISABLED  Output is disabled.
  */
hal_hsp_trgo_status_t HAL_HSP_TRGO_IsEnabled(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return (hal_hsp_trgo_status_t)(uint32_t)STM32_READ_BIT(p_hspx->ITFENR, HSP_ITFENR_TRGOEN);
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group7
  * @{
This section provides a set of functions to manage the Timestamp Capture:
  - HAL_HSP_TSC_SetConfig()        : configure the Timestamp Capture.
  - HAL_HSP_TSC_GetConfig()        : retrieve the Timestamp Capture configuration.
  - HAL_HSP_TSC_Start()            : start the Timestamp Capture.
  - HAL_HSP_TSC_Stop()             : stop the Timestamp Capture.
  - HAL_HSP_TSC_IsTimeStampReady() : check whether a timestamp is ready.
  - HAL_HSP_TSC_GetTimeStamp()     : get the last captured timestamp.
  */
/**
  * @brief  Configure the TimeStamp Capture.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config  Pointer to a @ref hal_hsp_tsc_config_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  */
hal_status_t HAL_HSP_TSC_SetConfig(const hal_hsp_handle_t *hhsp, const hal_hsp_tsc_config_t *p_config)
{
  HSP_TypeDef *p_hspx;
  uint32_t reg_value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM((p_config != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HSP_TSC_PRESCALER(p_config->prescaler));
  ASSERT_DBG_PARAM(IS_HSP_TSC_FREE_COUNTER(p_config->counter));
  ASSERT_DBG_PARAM(IS_HSP_TSC_FILTER(p_config->filter));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_value = ((uint32_t)(p_config->prescaler) | (uint32_t)(p_config->counter) | (uint32_t)(p_config->filter));
  STM32_MODIFY_REG(p_hspx->CAPCR, HSP_TSC_CONFIG_CAPCR_MASK, reg_value);

  return HAL_OK;
}

/**
  * @brief  Get the configuration of the TimeStamp Capture.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config  Pointer to a @ref hal_hsp_tsc_config_t.
  */
void HAL_HSP_TSC_GetConfig(const hal_hsp_handle_t *hhsp, hal_hsp_tsc_config_t *p_config)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM((p_config != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  p_config->prescaler = (hal_hsp_tsc_prescaler_t)(uint32_t)STM32_READ_BIT(p_hspx->CAPCR, HSP_CAPCR_PRESC_Msk);
  p_config->counter = (hal_hsp_tsc_free_running_counter_state_t)(uint32_t)STM32_READ_BIT(p_hspx->CAPCR,
                      HSP_CAPCR_FRCNTEN_Msk);
  p_config->filter = (hal_hsp_tsc_task_filter_t)(uint32_t)STM32_READ_BIT(p_hspx->CAPCR, HSP_CAPCR_TSKFLT_Msk);
}

/**
  * @brief  Enable the TimeStamp Capture.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  cap_mode  Capture Mode.
  * @param  evt_its  Mask of TSC event interrupts to enable.
  *         This parameter can be a combination of following values:
  *            @arg @ref  HAL_HSP_IT_NONE
  *            @arg @ref  HAL_HSP_TSC_IT_DATA_READY
  * @param  err_its  Mask of TSC error interrupts to enable.
  *         This parameter can be a combination of following values:
  *            @arg @ref  HAL_HSP_IT_NONE
  *            @arg @ref  HAL_HSP_TSC_ERR_IT_OVR
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_TSC_Start(const hal_hsp_handle_t *hhsp, hal_hsp_tsc_capture_mode_t cap_mode,
                               uint32_t evt_its, uint32_t err_its)
{
#if !defined(USE_HAL_HSP_TSC_IT) || (USE_HAL_HSP_TSC_IT != 1)
  STM32_UNUSED(evt_its);
  STM32_UNUSED(err_its);
#endif /* USE_HAL_HSP_TSC_IT */

  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TSC_CAPTURE_MODE(cap_mode));
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  ASSERT_DBG_PARAM(IS_HSP_TSC_EVT_IT(evt_its));
  ASSERT_DBG_PARAM(IS_HSP_TSC_ERR_IT(err_its));
#endif /* USE_HAL_HSP_TSC_IT */

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  if (evt_its != 0U)
  {
    STM32_SET_BIT(p_hspx->EVT_IER, evt_its);
  }

  if (err_its != 0U)
  {
    STM32_SET_BIT(p_hspx->ERR_IER, err_its);
  }
#endif /* USE_HAL_HSP_TSC_IT */

  STM32_MODIFY_REG(p_hspx->CAPCR, HSP_CAPCR_CAPMOD_Msk, (((uint32_t)cap_mode) << HSP_CAPCR_CAPMOD_Pos));

  return HAL_OK;
}

/**
  * @brief  Disable the TimeStamp Capture.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_TSC_Stop(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->CAPCR, HSP_CAPCR_CAPMOD_Msk);

#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  STM32_CLEAR_BIT(p_hspx->EVT_IER, HAL_HSP_TSC_IT_DATA_READY);
  STM32_CLEAR_BIT(p_hspx->ERR_IER, HAL_HSP_TSC_ERR_IT_OVR);
#endif /* USE_HAL_HSP_TSC_IT */

  return HAL_OK;
}

/**
  * @brief Indicates if the TimeStamp Data Ready Interrupt Flag is set or not.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_HSP_TSC_CAPTURE_DATA_READY.
  * @retval HAL_HSP_TSC_CAPTURE_DATA_NOT_READY.
  */
hal_hsp_tsc_capture_data_status_t HAL_HSP_TSC_IsTimeStampReady(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);
  return (hal_hsp_tsc_capture_data_status_t)(uint32_t)STM32_READ_BIT(p_hspx->EVT_ISR, HSP_EVT_ISR_CAPRDYF);
}

/**
  * @brief  Get the last captured TimeStamp.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @note Reading the CAPDR register clears automatically the timestamp capture ready flag.
  * @return hal_hsp_tsc_timestamp_t  The last captured timestamp.
  */
hal_hsp_tsc_timestamp_t HAL_HSP_TSC_GetTimeStamp(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;
  hal_hsp_tsc_timestamp_t timestamp;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* The read of CAPDR register clears automatically the HSP_EVT_ISR_CAPRDYF flag */
  timestamp.raw = STM32_READ_REG(p_hspx->CAPDR);

  return timestamp;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group8
  * @{
This section provides a set of functions to manage the BRAM access and Signal Processor Engine interrupts:
  - HAL_HSP_BRAM_EnableConflictAccessCounter()    : enable the BRAM Conflict Access counter.
  - HAL_HSP_BRAM_DisableConflictAccessCounter()   : disable the BRAM Conflict Access counter.
  - HAL_HSP_BRAM_IsEnabledConflictAccessCounter() : check whether the Conflict Access counter is enabled.
  - HAL_HSP_BRAM_GetConflictAccessCounter()       : get the last value of Conflict Access counter.
  - HAL_HSP_BRAM_SetLatency()                     : allow tuning BRAM arbitration latency between CPU & HSP.
  - HAL_HSP_BRAM_GetLatency()                     : get current BRAM arbitration latency.
  - HAL_HSP_SPE_EnableEventInterrupts()           : allow to enable some Signal Processor Engine Event interrupts.
  - HAL_HSP_SPE_DisableEventInterrupts()          : allow to disable some Signal Processor Engine Event interrupts.
  - HAL_HSP_SPE_IsEnabledEventInterrupts()        : check whether some Signal Processor Engine Event interrupts are
                                                    enabled.
  - HAL_HSP_SPE_GetEventStatusAndClearFlag()      : get Signal Processor Engine event status and clear flag.
  - HAL_HSP_SPE_EnableErrorInterrupts()           : allow to enable some Signal Processor Engine Error interrupts.
  - HAL_HSP_SPE_DisableErrorInterrupts()          : allow to disable some Signal Processor Engine Error interrupts.
  - HAL_HSP_SPE_IsEnabledErrorInterrupts()        : check whether some Signal Processor Engine Error interrupts are
                                                    enabled.
  - HAL_HSP_ExecErrorHandler()                    : check Signal Processor Engine error status, clear flags and on fault
                                                    error change state to HAL_HSP_FAULT.
  - HAL_HSP_CleanFirmwareErrorCode()              : clear firmware error code.
  - HAL_HSP_GetFirmwareErrorCode()                : get firmware error code.
  */
/**
  * @brief  Enable the BRAM Conflict Access Counter.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_BRAM_EnableConflictAccessCounter(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->CAPCR, HSP_CAPCR_CCNTREN);

  return HAL_OK;
}

/**
  * @brief  Disable the BRAM Conflict Access Counter.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_BRAM_DisableConflictAccessCounter(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->CAPCR, HSP_CAPCR_CCNTREN);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the BRAM Conflict Access Counter is enabled.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return Current status of bram conflict access counter.
  */
hal_hsp_bram_conflict_access_counter_status_t HAL_HSP_BRAM_IsEnabledConflictAccessCounter(const hal_hsp_handle_t *hhsp)
{
  uint32_t bit_val;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  bit_val = STM32_READ_BIT(((HSP_TypeDef *)(uint32_t)(hhsp->instance))->CAPCR, HSP_CAPCR_CCNTREN_Msk);
  return (hal_hsp_bram_conflict_access_counter_status_t)(bit_val);
}

/**
  * @brief  Get the BRAM Conflict Access Counter value.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return Counter value
  */
uint32_t HAL_HSP_BRAM_GetConflictAccessCounter(const hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  return STM32_READ_REG(((HSP_TypeDef *)(uint32_t)(hhsp->instance))->CCNTR);
}

/**
  * @brief  Set the BRAM Bandwidth Arbitration latency.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  latency  Max arbitration latency.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_BRAM_SetLatency(const hal_hsp_handle_t *hhsp, hal_hsp_bram_latency_t latency)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_BRAM_LATENCY(latency));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_MODIFY_REG(p_hspx->CR, HSP_CR_BARB_Msk, (uint32_t)latency);

  return HAL_OK;
}

/**
  * @brief  Get the BRAM Bandwidth Arbitration latency.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return Current bram latency
  */
hal_hsp_bram_latency_t HAL_HSP_BRAM_GetLatency(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;
  uint32_t reg_value;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_value = STM32_READ_BIT(p_hspx->CR, HSP_CR_BARB_Msk);
  return ((hal_hsp_bram_latency_t)reg_value);
}

/* Signal Processor Engine Error Interrupt -------------------------------------------------------*/
/**
  * @brief  Enable the Signal Processor Engine Event Interrupts.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @param  events  Event Interrupts mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SPE_IT_ENTER_IN_WFE
  *             @arg HAL_HSP_SPE_IT_EXIT_FROM_WFE
  *             @arg HAL_HSP_SPE_IT_FPU_SATURATION
  *             @arg HAL_HSP_SPE_IT_ALL: All Signal Processor Engine Event Interrupts
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_SPE_EnableEventInterrupts(const hal_hsp_handle_t *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SPE_EVT(events));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->EVT_IER, events);

  return HAL_OK;
}

/**
  * @brief  Disable Signal Processor Engine Event Interrupts.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  events  Event Interrupts mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SPE_IT_ENTER_IN_WFE
  *             @arg HAL_HSP_SPE_IT_EXIT_FROM_WFE
  *             @arg HAL_HSP_SPE_IT_FPU_SATURATION
  *             @arg HAL_HSP_SPE_IT_ALL: All Signal Processor Engine Events
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_SPE_DisableEventInterrupts(const hal_hsp_handle_t *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SPE_EVT(events));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->EVT_IER, events);

  return HAL_OK;
}

/**
  * @brief  Return the Signal Processor Engine Event Interrupt status.
  * @param  hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param  event  Event identifier.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_SPE_IT_ENTER_IN_WFE
  *             @arg HAL_HSP_SPE_IT_EXIT_FROM_WFE
  *             @arg HAL_HSP_SPE_IT_FPU_SATURATION
  * @return Current Signal Processor Engine Event Interrupt status.
  */
hal_hsp_spe_it_status_t HAL_HSP_SPE_IsEnabledEventInterrupts(const hal_hsp_handle_t *hhsp, uint32_t event)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_SPE_EVT(event));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->EVT_IER, event);
  return ((status != 0U) ? HAL_HSP_SPE_IT_ENABLED : HAL_HSP_SPE_IT_DISABLED);
}

/**
  * @brief  Return the Signal Processor Engine Event status and clear the flag.
  * @param  hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param  event  Event identifier.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_SPE_IT_ENTER_IN_WFE
  *             @arg HAL_HSP_SPE_IT_EXIT_FROM_WFE
  *             @arg HAL_HSP_SPE_IT_FPU_SATURATION
  * @return Current Signal Processor Engine Flag status.
  */
hal_hsp_spe_event_status_t HAL_HSP_SPE_GetEventStatusAndClearFlag(const hal_hsp_handle_t *hhsp, uint32_t event)
{
  HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_SPE_EVT(event));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->EVT_ISR, event);

  STM32_SET_BIT(p_hspx->EVT_ICR, event);

  return ((status != 0U) ? HAL_HSP_SPE_EVENT_SET : HAL_HSP_SPE_EVENT_RESET);
}

/**
  * @brief  Enable the Signal Processor Engine Error Interrupts.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  errors  Errors mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SPE_ERR_IT_FW
  *             @arg HAL_HSP_SPE_ERR_IT_SCHEDULER
  *             @arg HAL_HSP_SPE_ERR_IT_HDEG_OVR
  *             @arg HAL_HSP_SPE_ERR_IT_INVALID_OPCODE
  *             @arg HAL_HSP_SPE_ERR_IT_ACCESS
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_UDF
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_OVF
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_DBZ
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_INVALID
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_DENORMAL
  *             @arg HAL_HSP_SPE_ERR_IT_BREAKINPUT
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_ALL
  *             @arg HAL_HSP_SPE_ERR_IT_ALL: All Signal Processor Engine Error
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_SPE_EnableErrorInterrupts(const hal_hsp_handle_t *hhsp, uint32_t errors)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SPE_ERR_IT_WITH_FPU(errors));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->ERR_IER, errors);

  return HAL_OK;
}

/**
  * @brief  Disable Signal Processor Engine Error Interrupts.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  errors  Errors mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SPE_ERR_IT_FW
  *             @arg HAL_HSP_SPE_ERR_IT_SCHEDULER
  *             @arg HAL_HSP_SPE_ERR_IT_HDEG_OVR
  *             @arg HAL_HSP_SPE_ERR_IT_INVALID_OPCODE
  *             @arg HAL_HSP_SPE_ERR_IT_ACCESS
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_UDF
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_OVF
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_DBZ
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_INVALID
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_DENORMAL
  *             @arg HAL_HSP_SPE_ERR_IT_BREAKINPUT
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_ALL
  *             @arg HAL_HSP_SPE_ERR_IT_ALL: All Signal Processor Engine Error Interrupts
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_SPE_DisableErrorInterrupts(const hal_hsp_handle_t *hhsp, uint32_t errors)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SPE_ERR_IT_WITH_FPU(errors));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ERR_IER, errors);

  return HAL_OK;
}

/**
  * @brief  Return the Signal Processor Engine Error interrupt status.
  * @param  hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param  error  Error to check.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_SPE_ERR_IT_FW
  *             @arg HAL_HSP_SPE_ERR_IT_SCHEDULER
  *             @arg HAL_HSP_SPE_ERR_IT_HDEG_OVR
  *             @arg HAL_HSP_SPE_ERR_IT_INVALID_OPCODE
  *             @arg HAL_HSP_SPE_ERR_IT_ACCESS
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_UDF
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_OVF
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_DBZ
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_INVALID
  *             @arg HAL_HSP_SPE_ERR_IT_FPU_DENORMAL
  *             @arg HAL_HSP_SPE_ERR_IT_BREAKINPUT
  * @return Current Signal Processor Engine Error Interrupt status.
  */
hal_hsp_spe_it_status_t HAL_HSP_SPE_IsEnabledErrorInterrupts(const hal_hsp_handle_t *hhsp, uint32_t error)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_SPE_ERR_IT_WITH_FPU(error));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->ERR_IER, error);
  return ((status != 0U) ? HAL_HSP_SPE_IT_ENABLED : HAL_HSP_SPE_IT_DISABLED);
}

/**
  * @brief  Return the global HSP Error status and clear the flags.
  * @param  hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param  p_error_info  Pointer to variable to get detailed error information.
  * @note If a Fault error is detected, the global state of HSP is updated to HAL_HSP_STATE_FAULT.
  * @retval HAL_HSP_HW_ERROR_NONE   No Error.
  * @retval HAL_HSP_HW_ERROR_MINOR  Minor Error detected.
  * @retval HAL_HSP_HW_ERROR_FAULT  Fault Error detected.
  */
hal_hsp_hw_error_status_t HAL_HSP_ExecErrorHandler(hal_hsp_handle_t *hhsp, uint32_t *p_error_info)
{
  const HSP_TypeDef *p_hspx;
  hal_hsp_hw_error_status_t status;
  uint32_t reg_err_isr;
  uint32_t tmp_error_code;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM((p_error_info != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  tmp_error_code = HAL_HSP_ERROR_NONE;
  reg_err_isr = STM32_READ_REG(p_hspx->ERR_ISR);
  *p_error_info = STM32_READ_REG(p_hspx->ERRINFR);

  /* STREAM Interface --------------------------------------------------------*/
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  tmp_error_code |= HSP_STREAM_ErrorHandler(hhsp, reg_err_isr);
#endif /* USE_HAL_HSP_STREAM_IT */

  /* Trigger Input Interface -------------------------------------------------*/
#if defined(USE_HAL_HSP_TRGIN_IT) && (USE_HAL_HSP_TRGIN_IT == 1)
  tmp_error_code |= HSP_TRGIN_ErrorHandler(hhsp, reg_err_isr);
#endif /* USE_HAL_HSP_TRGIN_IT */

  /* TSC Interface -----------------------------------------------------------*/
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  tmp_error_code |= HSP_TSC_ErrorHandler(hhsp, reg_err_isr);
#endif /* USE_HAL_HSP_TSC_IT */

  /* Signal Processor Engine -------------------------------------------------*/
  if ((*p_error_info & HAL_HSP_ERROR_INFO_FPU_ALL) != 0U)
  {
    /* Complete the ERR ISR for Floating Point Unit Error while this FPUERRF is raised only if IT is enabled */
    reg_err_isr |= HSP_ERR_ISR_FPUERRF;
  }

  tmp_error_code |= HSP_SPE_ErrorHandler(hhsp, reg_err_isr, *p_error_info);

  if (tmp_error_code != HAL_HSP_ERROR_NONE)
  {
    if ((tmp_error_code & HAL_HSP_FAULT_ERROR_ALL) != 0U)
    {
      hhsp->global_state = HAL_HSP_STATE_FAULT;
      status = HAL_HSP_HW_ERROR_FAULT;
    }
    else
    {
      status = HAL_HSP_HW_ERROR_MINOR;
    }

#if defined(USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
    hhsp->last_error_codes |= tmp_error_code;
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
  }
  else
  {
    status = HAL_HSP_HW_ERROR_NONE;
  }

  return status;
}

/**
  * @brief  Clean the Firmware Error Code and its flag.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_BUSY A Direct Command is ongoing.
  * @retval HAL_ERROR Too long to reset the error code.
  */
hal_status_t HAL_HSP_CleanFirmwareErrorCode(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Send the command to clean the Firmware Error Code */
  if (STM32_IS_BIT_SET(p_hspx->DCMDSR, HSP_DCMDSR_DCBSY))
  {
    /* Previous command is still being processed */
    return HAL_BUSY;
  }

  STM32_WRITE_REG(p_hspx->DCMDIDR, hhsp->fwerr_dcmd_id);

  uint32_t tickstart = HAL_GetTick();
  while (STM32_IS_BIT_SET(p_hspx->DCMDSR, HSP_DCMDSR_DCBSY))
  {
    if ((HAL_GetTick() - tickstart) > HSP_CLEAN_FW_ERROR_CODE_TIMEOUT_MS)
    {
      return HAL_ERROR;
    }
  }

  STM32_SET_BIT(p_hspx->ERR_ICR, HSP_ERR_ICR_FWERRC);

  return HAL_OK;
}

/**
  * @brief  Get the Firmware Error Code.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return Firmware Error code
  */
uint32_t HAL_HSP_GetFirmwareErrorCode(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return (uint32_t)(STM32_READ_BIT(p_hspx->FWERR, HSP_FWERR_FWERRN_Msk) >> HSP_FWERR_FWERRN_Pos);
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group9
  * @{
This section provides functions allowing to debug a Processing List by enabling the output of some HSP signals on GPIO:
  - HAL_HSP_SNOOP_SetSignals() : select the internal HSP signals to observe.
  */
/**
  * @brief  Select the internal signals to observe.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config  Pointer to a @ref hal_hsp_snoop_config_t.
  * @retval HAL_OK  Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  */
hal_status_t HAL_HSP_SNOOP_SetSignals(const hal_hsp_handle_t *hhsp,
                                      const hal_hsp_snoop_config_t *p_config)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HSP_SNOOP_GROUPA_SIGNAL(p_config->grpa_signal));
  ASSERT_DBG_PARAM(IS_HSP_SNOOP_GROUPB_SIGNAL(p_config->grpb_signal));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_MODIFY_REG(p_hspx->SNPR, (HSP_SNPR_SNPSELB_Msk | HSP_SNPR_SNPSELA_Msk),
                   ((uint32_t)p_config->grpa_signal | (uint32_t)p_config->grpb_signal));

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group10
  * @{
This section provides functions to:
  - HAL_HSP_BREAK_SetMultiConfigOutput()     : configure multiple HSP break output.
  - HAL_HSP_BREAK_GetMultiConfigOutput()     : retrieve multiple HSP break output configuration.
  - HAL_HSP_BREAK_SetDebugEvents()           : configure HSP debug events.
  - HAL_HSP_BREAK_GetDebugEvents()           : retrieve HSP debug events.
  - HAL_HSP_BREAK_EnableDebugSingleStep()    : enable debug single step.
  - HAL_HSP_BREAK_DisableDebugSingleStep()   : disable debug single step.
  - HAL_HSP_BREAK_IsEnabledDebugSingleStep() : check whether debug single step is enabled.
  - HAL_HSP_BREAK_ResumeDebugEvents()        : resume debug events after a break condition.
  */
/**
  * @brief  Configure multiple HSP break outputs.
  * @param  hhsp               Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array     Configuration array pointer.
  * @param  config_array_size  Number of elements in the array.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Config pointer is NULL or config_array_size is too large.
  */
hal_status_t HAL_HSP_BREAK_SetMultiConfigOutput(const hal_hsp_handle_t *hhsp,
                                                const hal_hsp_break_output_config_t *p_config_array,
                                                uint32_t config_array_size)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_BREAK_OUTPUT_NBR(p_hspx));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config_array == NULL) || (config_array_size > HSP_BREAK_OUTPUT_NBR(p_hspx)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    const hal_hsp_break_output_config_t *p_config = &p_config_array[idx];

    ASSERT_DBG_PARAM(IS_HSP_BREAK_OUTPUT(p_config->output_id));
    ASSERT_DBG_PARAM(STM32_IS_BIT_SET(HAL_HSP_BREAK_OUTPUT_EVENT_ALL, p_config->critical_events));
    STM32_MODIFY_REG(p_hspx->BKOCFGR[(uint32_t)(p_config->output_id)],
                     HAL_HSP_BREAK_OUTPUT_EVENT_ALL, p_config->critical_events);
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the configuration of multiple HSP break outputs.
  * @param  hhsp               Pointer to a @ref hal_hsp_handle_t.
  * @param  p_config_array     Configuration array pointer.
  * @param  config_array_size  Number of elements in the array.
  */
void HAL_HSP_BREAK_GetMultiConfigOutput(const hal_hsp_handle_t *hhsp,
                                        hal_hsp_break_output_config_t *p_config_array, uint32_t config_array_size)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config_array != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  ASSERT_DBG_PARAM(config_array_size <= HSP_BREAK_OUTPUT_NBR(p_hspx));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    hal_hsp_break_output_config_t *p_config = &p_config_array[idx];

    p_config->output_id = (hal_hsp_break_output_t)idx;
    p_config->critical_events = STM32_READ_BIT(p_hspx->BKOCFGR[idx], HAL_HSP_BREAK_OUTPUT_EVENT_ALL);
  }
}

/**
  * @brief  Enable Events to freeze the Signal Processor Engine from internal error or error
  *         reported by an external block.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param  events  Mask of Freeze Event to enable.
  *         This parameter can be a combination of following values:
  *           @arg @ref HAL_HSP_BREAK_EVENT_MEMORY_ACCESS
  *           @arg @ref HAL_HSP_BREAK_EVENT_FPU
  *           @arg @ref HAL_HSP_BREAK_EVENT_OPCODE
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_28
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_29
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_30
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_31
  *           @arg @ref HAL_HSP_BREAK_EVENT_FIRMWARE
  *           @arg @ref HAL_HSP_BREAK_EVENT_SPE_OVR
  *           @arg @ref HAL_HSP_BREAK_EVENT_FPU_SATURATION
  *           @arg @ref HAL_HSP_BREAK_EVENT_SINGLE_STEP
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_ALL
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_HSP_BREAK_SetDebugEvents(const hal_hsp_handle_t *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(STM32_IS_BIT_SET(HAL_HSP_BREAK_FREEZE_EVENT_ALL, events));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_MODIFY_REG(p_hspx->BKICFGR, HAL_HSP_BREAK_FREEZE_EVENT_ALL, events);

  return HAL_OK;
}

/**
  * @brief  Get the events configured to freeze the Signal Processor Engine.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @return Mask of enabled freeze Event.
  *         This mask can be a combination of following values:
  *           @arg @ref HAL_HSP_BREAK_EVENT_MEMORY_ACCESS
  *           @arg @ref HAL_HSP_BREAK_EVENT_FPU
  *           @arg @ref HAL_HSP_BREAK_EVENT_OPCODE
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_28
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_29
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_30
  *           @arg @ref HAL_HSP_BREAK_EVENT_PFCT_31
  *           @arg @ref HAL_HSP_BREAK_EVENT_FIRMWARE
  *           @arg @ref HAL_HSP_BREAK_EVENT_SPE_OVR
  *           @arg @ref HAL_HSP_BREAK_EVENT_FPU_SATURATION
  *           @arg @ref HAL_HSP_BREAK_EVENT_SINGLE_STEP
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_ALL
  * @return Bitmask of enabled debug break events. This value can combine one or more
  *         HAL_HSP_BREAK_EVENT_x values.
  */
uint32_t HAL_HSP_BREAK_GetDebugEvents(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return STM32_READ_REG(p_hspx->BKICFGR);
}

/**
  * @brief  Enable the Single Step Debugging mode for processing function.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_BREAK_EnableDebugSingleStep(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->BKICFGR, HSP_BKICFGR_SSEN);

  return HAL_OK;
}

/**
  * @brief  Disable the Single Step Debugging mode for processing function.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_BREAK_DisableDebugSingleStep(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->BKICFGR, HSP_BKICFGR_SSEN);

  return HAL_OK;
}

/**
  * @brief  Get the Single Step Debugging mode status.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_HSP_BREAK_DBG_SINGLE_STEP_DISABLED.
  * @retval HAL_HSP_BREAK_DBG_SINGLE_STEP_ENABLED.
  */
hal_hsp_break_dbg_single_step_status_t HAL_HSP_BREAK_IsEnabledDebugSingleStep(const hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return (hal_hsp_break_dbg_single_step_status_t)(uint32_t)STM32_READ_BIT(p_hspx->BKICFGR, HSP_BKICFGR_SSEN);
}


/**
  * @brief  Resume the frozen Signal Processor Engine.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_BREAK_ResumeDebugEvents(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;
  uint32_t bkicfgr;
  uint32_t tmp_reg_icr = 0U;
  uint32_t tmp_reg;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  bkicfgr = STM32_READ_REG(p_hspx->BKICFGR);

  /* Clear Event Flags */
  if (STM32_IS_BIT_SET(bkicfgr, HAL_HSP_BREAK_EVENT_FPU_SATURATION))
  {
    STM32_WRITE_REG(p_hspx->EVT_ICR, HAL_HSP_SPE_IT_FPU_SATURATION);
  }

  tmp_reg = STM32_READ_BIT(bkicfgr, HAL_HSP_BREAK_EVENT_PFCT_ALL) >> HSP_BKOCFGR_PFCT28EN_Pos;
  if (tmp_reg > 0U)
  {
    STM32_WRITE_REG(p_hspx->PFCTEVT_ICR, tmp_reg << HSP_BREAK_PFCTEVT_FIRST_FLAG_POS);
  }

  /* Clear Error Flags */
  if (STM32_IS_BIT_SET(bkicfgr, HAL_HSP_BREAK_EVENT_MEMORY_ACCESS))
  {
    tmp_reg_icr |= HAL_HSP_SPE_ERR_IT_ACCESS;
  }

  if (STM32_IS_BIT_SET(bkicfgr, HAL_HSP_BREAK_EVENT_FPU))
  {
    tmp_reg_icr |= HSP_ERR_ICR_FPUERRC;
  }

  if (STM32_IS_BIT_SET(bkicfgr, HAL_HSP_BREAK_EVENT_OPCODE))
  {
    tmp_reg_icr |= HAL_HSP_SPE_ERR_IT_INVALID_OPCODE;
  }

  if (STM32_IS_BIT_SET(bkicfgr, HAL_HSP_BREAK_EVENT_FIRMWARE))
  {
    tmp_reg_icr |= HAL_HSP_SPE_ERR_IT_FW;
  }

  if (STM32_IS_BIT_SET(bkicfgr, HAL_HSP_BREAK_EVENT_SPE_OVR))
  {
    tmp_reg_icr |= HAL_HSP_SPE_ERR_IT_HDEG_OVR;
  }

  if (STM32_IS_BIT_SET(p_hspx->ERR_ISR, HSP_ERR_ISR_BKINF))
  {
    tmp_reg_icr |= HSP_ERR_ICR_BKINC;
  }

  if (tmp_reg_icr != 0U)
  {
    STM32_WRITE_REG(p_hspx->ERR_ICR, tmp_reg_icr);
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group11
  * @{
This section provides function to protect the HSP configuration.
  - HAL_HSP_Lock() : lock the HSP configuration.
  */
/**
  * @brief  Lock the configuration.
  * @param  hhsp Pointer to a @ref hal_hsp_handle_t.
  * @note   Once locked, HSP configuration cannot be changed (use case: safety purpose).
  * @note   HSP can be unlocked with a system reset.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_Lock(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_RUNNING));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->CR, HSP_CR_REGLCK_Msk);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group12
  * @{
This section provides a set of functions dedicated to CNN Safe Mode execution:
  - HAL_HSP_CNN_EnterSafeMode() : backup interrupt/event states and disable non-error interrupts.
  - HAL_HSP_CNN_ExitSafeMode()  : restore interrupt/event states.
  */
/**
  * @brief  Backup all interrupt and event activation states.
  * @param  hhsp  Pointer to a hal_hsp_handle_t.
  * @note   This function is dedicated for CNN function usage.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_CNN_EnterSafeMode(hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Save some registers status */
  hhsp->backup_enabled_itfs = STM32_READ_REG(p_hspx->ITFENR);
  hhsp->backup_enabled_events = STM32_READ_REG(p_hspx->EVTENR);
  hhsp->backup_event_its = STM32_READ_REG(p_hspx->EVT_IER);
  hhsp->backup_pfctevt_its = STM32_READ_REG(p_hspx->PFCTEVT_IER);

  /* Disable all interrupts except Error ITs */
  STM32_WRITE_REG(p_hspx->EVT_IER, 0U);
  STM32_WRITE_REG(p_hspx->PFCTEVT_IER, 0U);

  /* Disable all events */
  STM32_WRITE_REG(p_hspx->EVTENR, 0U);

  /* Disable all interfaces except HDEG, HSEG, CDEG */
  STM32_WRITE_REG(p_hspx->ITFENR, HSP_CNN_SAFEMODE_ITFENR_MASK);

  return HAL_OK;
}

/**
  * @brief  Restore all interrupt and event activation states.
  * @param  hhsp  Pointer to a hal_hsp_handle_t.
  * @note   This function is dedicated for CNN function usage.
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_CNN_ExitSafeMode(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Restore interrupts */
  STM32_WRITE_REG(p_hspx->EVT_IER, hhsp->backup_event_its);
  STM32_WRITE_REG(p_hspx->PFCTEVT_IER, hhsp->backup_pfctevt_its);

  /* Restore events */
  STM32_WRITE_REG(p_hspx->EVTENR, hhsp->backup_enabled_events);

  /* Restore interfaces */
  STM32_WRITE_REG(p_hspx->ITFENR, hhsp->backup_enabled_itfs);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group13
  * @{
This section provides a set of functions to manage Processing Lists:
 - HAL_HSP_PROCLIST_PollForNotification() : poll for Processing Function Event notifications.
 - HAL_HSP_PROCLIST_EnableIT()            : enable Processing Function Event interrupts.
 - HAL_HSP_PROCLIST_DisableIT()           : disable Processing Function Event interrupts.
 - HAL_HSP_PROCLIST_IsEnabledIT()         : check whether an interrupt is enabled.
  */
/**
  * @brief  Poll on Processing Function Event Flags.
  * @param  hhsp         Pointer to a @ref hal_hsp_handle_t.
  * @param  poll_mode    Polling mode.
  * @param  pfct_events  Mask of events to poll.
  *         This parameter can be a combination of the following values:
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_0:   The Flag of Processing Function Event 0
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_1:   The Flag of Processing Function Event 1
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_2:   The Flag of Processing Function Event 2
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_3:   The Flag of Processing Function Event 3
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_4:   The Flag of Processing Function Event 4
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_5:   The Flag of Processing Function Event 5
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_6:   The Flag of Processing Function Event 6
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_7:   The Flag of Processing Function Event 7
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_8:   The Flag of Processing Function Event 8
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_9:   The Flag of Processing Function Event 9
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_10:  The Flag of Processing Function Event 10
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_11:  The Flag of Processing Function Event 11
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_12:  The Flag of Processing Function Event 12
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_13:  The Flag of Processing Function Event 13
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_14:  The Flag of Processing Function Event 14
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_15:  The Flag of Processing Function Event 15
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_16:  The Flag of Processing Function Event 16
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_17:  The Flag of Processing Function Event 17
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_18:  The Flag of Processing Function Event 18
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_19:  The Flag of Processing Function Event 19
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_20:  The Flag of Processing Function Event 20
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_21:  The Flag of Processing Function Event 21
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_22:  The Flag of Processing Function Event 22
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_23:  The Flag of Processing Function Event 23
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_24:  The Flag of Processing Function Event 24
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_25:  The Flag of Processing Function Event 25
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_26:  The Flag of Processing Function Event 26
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_27:  The Flag of Processing Function Event 27
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_28:  The Flag of Processing Function Event 28
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_29:  The Flag of Processing Function Event 29
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_30:  The Flag of Processing Function Event 30
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_31:  The Flag of Processing Function Event 31
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_ALL: All Flags of Processing Function Event
  * @param  timeout_ms  Timeout duration (in ms).
  * @param  p_pfct_evts_status  Pointer to return the Processing Function Event flags.
  * @retval HAL_OK  Operation completed successfully.
  * @retval HAL_TIMEOUT Operation timed out.
  * @retval HAL_INVALID_PARAM  Invalid parameter.
  */
hal_status_t HAL_HSP_PROCLIST_PollForNotification(const hal_hsp_handle_t *hhsp,
                                                  hal_hsp_polling_mode_t poll_mode, uint32_t pfct_events,
                                                  uint32_t timeout_ms, uint32_t *p_pfct_evts_status)
{
  HSP_TypeDef *p_hspx;
  hal_status_t status;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_POLLING_MODE(poll_mode));
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(pfct_events));
  ASSERT_DBG_PARAM(p_pfct_evts_status != NULL);

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_pfct_evts_status == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = HSP_PollRegisterFlags(poll_mode, &p_hspx->PFCTEVT_ISR,
                                 pfct_events, HSP_GetPolledFlagsActiveHigh,
                                 timeout_ms, p_pfct_evts_status);

  if (status == HAL_OK)
  {
    /* Clear triggered flags */
    STM32_WRITE_REG(p_hspx->PFCTEVT_ICR, *p_pfct_evts_status);
  }

  return status;
}

#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
/**
  * @brief  Enable Processing Function Event Interrupts.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  interrupts  Mask of Processing Function Event Interrupts.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_0:   The Interrupt of Processing Function Event 0
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_1:   The Interrupt of Processing Function Event 1
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_2:   The Interrupt of Processing Function Event 2
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_3:   The Interrupt of Processing Function Event 3
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_4:   The Interrupt of Processing Function Event 4
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_5:   The Interrupt of Processing Function Event 5
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_6:   The Interrupt of Processing Function Event 6
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_7:   The Interrupt of Processing Function Event 7
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_8:   The Interrupt of Processing Function Event 8
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_9:   The Interrupt of Processing Function Event 9
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_10:  The Interrupt of Processing Function Event 10
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_11:  The Interrupt of Processing Function Event 11
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_12:  The Interrupt of Processing Function Event 12
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_13:  The Interrupt of Processing Function Event 13
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_14:  The Interrupt of Processing Function Event 14
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_15:  The Interrupt of Processing Function Event 15
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_16:  The Interrupt of Processing Function Event 16
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_17:  The Interrupt of Processing Function Event 17
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_18:  The Interrupt of Processing Function Event 18
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_19:  The Interrupt of Processing Function Event 19
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_20:  The Interrupt of Processing Function Event 20
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_21:  The Interrupt of Processing Function Event 21
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_22:  The Interrupt of Processing Function Event 22
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_23:  The Interrupt of Processing Function Event 23
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_24:  The Interrupt of Processing Function Event 24
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_25:  The Interrupt of Processing Function Event 25
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_26:  The Interrupt of Processing Function Event 26
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_27:  The Interrupt of Processing Function Event 27
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_28:  The Interrupt of Processing Function Event 28
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_29:  The Interrupt of Processing Function Event 29
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_30:  The Interrupt of Processing Function Event 30
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_31:  The Interrupt of Processing Function Event 31
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_ALL: All Interrupts of Processing Function Event
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_PROCLIST_EnableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(interrupts));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->PFCTEVT_IER, interrupts);

  return HAL_OK;
}

/**
  * @brief  Disable Processing Function Event Interrupts.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @param  interrupts  Mask of Processing Function Event Interrupts.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_0:   The Interrupt of Processing Function Event 0
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_1:   The Interrupt of Processing Function Event 1
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_2:   The Interrupt of Processing Function Event 2
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_3:   The Interrupt of Processing Function Event 3
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_4:   The Interrupt of Processing Function Event 4
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_5:   The Interrupt of Processing Function Event 5
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_6:   The Interrupt of Processing Function Event 6
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_7:   The Interrupt of Processing Function Event 7
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_8:   The Interrupt of Processing Function Event 8
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_9:   The Interrupt of Processing Function Event 9
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_10:  The Interrupt of Processing Function Event 10
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_11:  The Interrupt of Processing Function Event 11
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_12:  The Interrupt of Processing Function Event 12
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_13:  The Interrupt of Processing Function Event 13
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_14:  The Interrupt of Processing Function Event 14
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_15:  The Interrupt of Processing Function Event 15
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_16:  The Interrupt of Processing Function Event 16
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_17:  The Interrupt of Processing Function Event 17
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_18:  The Interrupt of Processing Function Event 18
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_19:  The Interrupt of Processing Function Event 19
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_20:  The Interrupt of Processing Function Event 20
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_21:  The Interrupt of Processing Function Event 21
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_22:  The Interrupt of Processing Function Event 22
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_23:  The Interrupt of Processing Function Event 23
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_24:  The Interrupt of Processing Function Event 24
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_25:  The Interrupt of Processing Function Event 25
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_26:  The Interrupt of Processing Function Event 26
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_27:  The Interrupt of Processing Function Event 27
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_28:  The Interrupt of Processing Function Event 28
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_29:  The Interrupt of Processing Function Event 29
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_30:  The Interrupt of Processing Function Event 30
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_31:  The Interrupt of Processing Function Event 31
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_ALL: All Interrupts of Processing Function Event
  * @retval HAL_OK  Operation completed successfully.
  */
hal_status_t HAL_HSP_PROCLIST_DisableIT(const hal_hsp_handle_t *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(interrupts));

  ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->PFCTEVT_IER, interrupts);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the specified Processing Function Event interrupt is set.
  * @param  hhsp       Pointer to a @ref hal_hsp_handle_t.
  * @param  interrupt  Mask of Processing Function Event Interrupt.
  *         It can be one of the following values:
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_0:   The Interrupt of Processing Function Event 0
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_1:   The Interrupt of Processing Function Event 1
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_2:   The Interrupt of Processing Function Event 2
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_3:   The Interrupt of Processing Function Event 3
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_4:   The Interrupt of Processing Function Event 4
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_5:   The Interrupt of Processing Function Event 5
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_6:   The Interrupt of Processing Function Event 6
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_7:   The Interrupt of Processing Function Event 7
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_8:   The Interrupt of Processing Function Event 8
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_9:   The Interrupt of Processing Function Event 9
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_10:  The Interrupt of Processing Function Event 10
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_11:  The Interrupt of Processing Function Event 11
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_12:  The Interrupt of Processing Function Event 12
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_13:  The Interrupt of Processing Function Event 13
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_14:  The Interrupt of Processing Function Event 14
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_15:  The Interrupt of Processing Function Event 15
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_16:  The Interrupt of Processing Function Event 16
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_17:  The Interrupt of Processing Function Event 17
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_18:  The Interrupt of Processing Function Event 18
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_19:  The Interrupt of Processing Function Event 19
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_20:  The Interrupt of Processing Function Event 20
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_21:  The Interrupt of Processing Function Event 21
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_22:  The Interrupt of Processing Function Event 22
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_23:  The Interrupt of Processing Function Event 23
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_24:  The Interrupt of Processing Function Event 24
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_25:  The Interrupt of Processing Function Event 25
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_26:  The Interrupt of Processing Function Event 26
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_27:  The Interrupt of Processing Function Event 27
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_28:  The Interrupt of Processing Function Event 28
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_29:  The Interrupt of Processing Function Event 29
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_30:  The Interrupt of Processing Function Event 30
  *             @arg HAL_HSP_PROCLIST_IT_PFCTEVT_31:  The Interrupt of Processing Function Event 31
  * @return Current interrupt status.
  */
hal_hsp_proclist_it_status_t HAL_HSP_PROCLIST_IsEnabledIT(const hal_hsp_handle_t *hhsp,
                                                          uint32_t interrupt)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(interrupt));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT      | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return ((STM32_READ_BIT(p_hspx->PFCTEVT_IER, interrupt) != 0U) ? HAL_HSP_PROCLIST_IT_ENABLED
          : HAL_HSP_PROCLIST_IT_DISABLED);
}
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group14
  * @{
  This subsection provides the HSP IRQ handlers, weak callbacks, and callback registration functions.

  The public IRQ handlers are:
    - HAL_HSP_IRQHandler() to handle the main HSP IRQ line.
    - HAL_HSP_EVT_IRQHandler() to handle the HSP Event IRQ line.
    - HAL_HSP_ERR_IRQHandler() to handle the HSP Error IRQ line.
    - HAL_HSP_FWEVT_IRQHandler() to handle the HSP Firmware Event IRQ line.

  HAL_HSP_IRQHandler() dispatches the processing to HAL_HSP_ERR_IRQHandler(), HAL_HSP_EVT_IRQHandler(),
  and HAL_HSP_FWEVT_IRQHandler().

  There are two ways to use callbacks:

  Override weak callbacks functions:
    - HAL_HSP_PRC_TaskCpltCallback()
    - HAL_HSP_SPE_FPUSaturationCallback()
    - HAL_HSP_SPE_RunStateCallback()
    - HAL_HSP_STREAM_BufferEmptyCallback()
    - HAL_HSP_STREAM_BufferFullCallback()
    - HAL_HSP_TCU_TaskStartedCallback()
    - HAL_HSP_TCU_TaskEndedCallback()
    - HAL_HSP_TCU_TaskOverlapCallback()
    - HAL_HSP_TSC_TimestampReadyCallback()
    - HAL_HSP_ErrorCallback()
    - HAL_HSP_ProcessingEventCallback()

  Or register user callbacks:
    - HAL_HSP_RegisterPRC_TaskCpltCallback()
    - HAL_HSP_RegisterSPE_FPUSaturationCallback()
    - HAL_HSP_RegisterSPE_RunStateCallback()
    - HAL_HSP_RegisterSTREAM_BufferEmptyCallback()
    - HAL_HSP_RegisterSTREAM_BufferFullCallback()
    - HAL_HSP_RegisterTCU_TaskStartedCallback()
    - HAL_HSP_RegisterTCU_TaskEndedCallback()
    - HAL_HSP_RegisterTCU_TaskOverlapCallback()
    - HAL_HSP_RegisterTSC_TimestampReadyCallback()
    - HAL_HSP_RegisterErrorCallback()
    - HAL_HSP_RegisterProcessingEventCallback()

  Depending on the API used to enable interrupts or request processing, different callbacks might be triggered:

  | Process API \n \ \n Callbacks      | HAL_HSP_STREAM_Start | HAL_HSP_TRGIN_EnableIT |
  |------------------------------------|:--------------------:|:----------------------:|
  | HAL_HSP_STREAM_BufferEmptyCallback |           x          |                        |
  | HAL_HSP_STREAM_BufferFullCallback  |           x          |                        |
  | HAL_HSP_ErrorCallback              |           x          |           x            |

  | Process API \n \ \n Callbacks      | HAL_HSP_PRC_SWRequestLowestPriorityTask |
  |------------------------------------|:---------------------------------------:|
  | HAL_HSP_PRC_TaskCpltCallback       |                    x                    |

  | Process API \n \ \n Callbacks      | HAL_HSP_SPE_EnableEventInterrupts | HAL_HSP_SPE_EnableErrorInterrupts |
  |------------------------------------|:---------------------------------:|:---------------------------------:|
  | HAL_HSP_SPE_RunStateCallback       |                 x                 |                                   |
  | HAL_HSP_SPE_FPUSaturationCallback  |                 x                 |                                   |
  | HAL_HSP_ErrorCallback              |                                   |                 x                 |

  | Process API \n \ \n Callbacks   | HAL_HSP_TCU_StartComparator | HAL_HSP_TCU_StartOverlapDetector |
  |---------------------------------|:---------------------------:|:--------------------------------:|
  | HAL_HSP_TCU_TaskStartedCallback |              x              |                                  |
  | HAL_HSP_TCU_TaskEndedCallback   |              x              |                                  |
  | HAL_HSP_TCU_TaskOverlapCallback |                             |                 x                |

  | Process API \n \ \n Callbacks      | HAL_HSP_TSC_Start |
  |------------------------------------|:-----------------:|
  | HAL_HSP_TSC_TimestampReadyCallback |          x        |
  | HAL_HSP_ErrorCallback              |          x        |

  | Process API \n \ \n Callbacks   | HAL_HSP_PROCLIST_EnableIT |
  |---------------------------------|:-------------------------:|
  | HAL_HSP_ProcessingEventCallback |              x            |

  */
/* Global IRQ Handler *********************************************************/
/**
  * @brief  Handle all HSP interrupt request.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  */
void HAL_HSP_IRQHandler(hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE((HSP_TypeDef *)(uint32_t)(hhsp->instance)));

  HSP_ERR_IRQHandler(hhsp);
  HSP_EVT_IRQHandler(hhsp);
  HSP_FWEVT_IRQHandler(hhsp);
}

/* Event IRQ Handlers and Callbacks *******************************************/
/**
  * @brief  Handle all HSP Event interrupt request.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  */
void HAL_HSP_EVT_IRQHandler(hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE((HSP_TypeDef *)(uint32_t)(hhsp->instance)));

  HSP_EVT_IRQHandler(hhsp);
}

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
/**
  * @brief  Callback for STREAM Buffer Empty.
  * @param hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param buffer_ids  Buffer ID mask.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_STREAM_BufferEmptyCallback(hal_hsp_handle_t *hhsp, uint32_t buffer_ids)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(buffer_ids);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_STREAM_BufferEmptyCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for STREAM Buffer Full.
  * @param hhsp Pointer to a @ref hal_hsp_handle_t.
  * @param buffer_ids  Buffer ID mask.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_STREAM_BufferFullCallback(hal_hsp_handle_t *hhsp, uint32_t buffer_ids)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(buffer_ids);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_STREAM_BufferFullCallback must be implemented in the user file.
   */
}
#endif /* USE_HAL_HSP_STREAM_IT */

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
/**
  * @brief  Callback for Start Of Task Interrupts.
  * @param hhsp     Pointer to a @ref hal_hsp_handle_t.
  * @param tcu_ids  TCU IDs mask.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_TCU_TaskStartedCallback(hal_hsp_handle_t *hhsp, uint32_t tcu_ids)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(tcu_ids);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_TCU_TaskStartedCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for End Of Task Interrupts.
  * @param hhsp     Pointer to a @ref hal_hsp_handle_t.
  * @param tcu_ids  TCU IDs mask.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_TCU_TaskEndedCallback(hal_hsp_handle_t *hhsp, uint32_t tcu_ids)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(tcu_ids);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_TCU_TaskEndedCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for Task Overlap Event.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_TCU_TaskOverlapCallback(hal_hsp_handle_t *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_TCU_TaskOverlapCallback must be implemented in the user file.
   */
}
#endif /* USE_HAL_HSP_TCU_IT */

/**
  * @brief  Callback for Task Execution Complete.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_PRC_TaskCpltCallback(hal_hsp_handle_t *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_PRC_TaskCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for Signal Processor Engine Run State change.
  * @param hhsp   Pointer to a @ref hal_hsp_handle_t.
  * @param state  Signal Processor Engine State.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_SPE_RunStateCallback(hal_hsp_handle_t *hhsp, uint32_t state)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(state);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_SPE_RunStateCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for Floating Point Unit Saturation Event.
  * @param hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_SPE_FPUSaturationCallback(hal_hsp_handle_t *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_SPE_FPUSaturationCallback must be implemented in the user file.
   */
}

#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
/**
  * @brief  Callback for TimeStamp Capture Data Ready.
  * @param hhsp       Pointer to a @ref hal_hsp_handle_t.
  * @param timestamp  Raw TimeStamp data.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_TSC_TimestampReadyCallback(hal_hsp_handle_t *hhsp, hal_hsp_tsc_timestamp_t timestamp)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(timestamp);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_TSC_TimestampReadyCallback must be implemented in the user file.
   */
}
#endif /* USE_HAL_HSP_TSC_IT */

/* Error IRQ Handlers and Callbacks *******************************************/
/**
  * @brief  Handle all HSP Error interrupt request.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  */
void HAL_HSP_ERR_IRQHandler(hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE((HSP_TypeDef *)(uint32_t)(hhsp->instance)));

  HSP_ERR_IRQHandler(hhsp);
}

/* Firmware Event IRQ Handlers and Callbacks **********************************/
#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
/**
  * @brief  Handle all HSP Firmware Event interrupt request.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  */
void HAL_HSP_FWEVT_IRQHandler(hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE((HSP_TypeDef *)((uint32_t)hhsp->instance)));

  HSP_FWEVT_IRQHandler(hhsp);
}

/**
  * @brief  Callback for Processing Function Events.
  * @param hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param events  Processing Function Events mask.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_ProcessingEventCallback(hal_hsp_handle_t *hhsp, uint32_t events)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(events);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_ProcessingEventCallback must be implemented in the user file.
   */
}
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */

/**
  * @brief  Callback for any Error.
  * @param hhsp            Pointer to a @ref hal_hsp_handle_t.
  * @param error_status    HSP Error Status.
  * @param fw_error_code   Firmware Error Code.
  * @param error_inf_mask  Signal Processor Engine Errors mask.
  * @warning This weak function must not be modified. When the callback is needed,
  *          it must be implemented in the user file.
  */
__WEAK void HAL_HSP_ErrorCallback(hal_hsp_handle_t *hhsp, hal_hsp_hw_error_status_t error_status,
                                  uint32_t fw_error_code, uint32_t error_inf_mask)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhsp);
  STM32_UNUSED(error_status);
  STM32_UNUSED(fw_error_code);
  STM32_UNUSED(error_inf_mask);

  /* WARNING: This function must not be modified. When the callback is needed,
              function HAL_HSP_ErrorCallback must be implemented in the user file.
   */
}

#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions ************************************/
/**
  * @brief  Register a User HSP callback for Priority Encoder Controller Event: Ready For New Task in Lowest Priority.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterPRC_TaskCpltCallback(hal_hsp_handle_t *hhsp,
                                                  hal_hsp_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_prc_task_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for Signal Processor Engine Event: Floating Point Unit Saturation.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterSPE_FPUSaturationCallback(hal_hsp_handle_t *hhsp,
                                                       hal_hsp_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_spe_fpu_saturation_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for Signal Processor Engine Event: Run State Changed.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterSPE_RunStateCallback(hal_hsp_handle_t *hhsp,
                                                  hal_hsp_one_param_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_spe_run_state_cb = p_callback;

  return HAL_OK;
}

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
/**
  * @brief  Register a User HSP callback for STREAM Buffer Event: Buffer Empty.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterSTREAM_BufferEmptyCallback(hal_hsp_handle_t *hhsp,
                                                        hal_hsp_one_param_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_stream_buffer_empty_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for STREAM Buffer Event: Buffer Full.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterSTREAM_BufferFullCallback(hal_hsp_handle_t *hhsp,
                                                       hal_hsp_one_param_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_stream_buffer_full_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_HSP_STREAM_IT */

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
/**
  * @brief  Register a User HSP callback for Task Comparator Event: Task Overlap.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterTCU_TaskOverlapCallback(hal_hsp_handle_t *hhsp,
                                                     hal_hsp_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_tcu_task_overlap_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for Task Comparator Events: Start Of Task.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterTCU_TaskStartedCallback(hal_hsp_handle_t *hhsp,
                                                     hal_hsp_one_param_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_tcu_task_started_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for Task Comparator Events: End Of Task.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterTCU_TaskEndedCallback(hal_hsp_handle_t *hhsp,
                                                   hal_hsp_one_param_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;

  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_tcu_task_ended_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_HSP_TCU_IT */

#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
/**
  * @brief  Register a User HSP callback for TimeStamp Capture Event: Timestamp Ready.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterTSC_TimestampReadyCallback(hal_hsp_handle_t *hhsp, hal_hsp_tsc_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;

  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_tsc_timestamp_ready_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_HSP_TSC_IT */

/**
  * @brief  Register a User HSP callback for any Error Event.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterErrorCallback(hal_hsp_handle_t *hhsp, hal_hsp_error_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_error_cb = p_callback;

  return HAL_OK;
}

#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
/**
  * @brief  Register a User HSP callback for any Processing Function Event.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK             Registering completed successfully.
  * @retval HAL_INVALID_PARAM  p_callback pointer is NULL.
  */
hal_status_t HAL_HSP_RegisterProcessingEventCallback(hal_hsp_handle_t *hhsp,
                                                     hal_hsp_one_param_cb_t p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;

  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->p_processing_event_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */

#endif /* (USE_HAL_HSP_REGISTER_CALLBACKS) */
/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group15
  * @{
A set of functions allowing to retrieve peripheral state and error information.
 - HAL_HSP_GetState()               : return the HSP handle state.
 - HAL_HSP_GetCRAMFreeSizeByte()    : return the free size in bytes of CRAM.
 - HAL_HSP_GetLastErrorCodes()      : return errors limited to the last process.
 - HAL_HSP_GetMsgBoxLastErrorCode() : return the MSGBOX last error code.
  */
/**
  * @brief  Return the HSP handle state.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return hal_hsp_state_t enum value.
  */
hal_hsp_state_t HAL_HSP_GetState(const hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  return hhsp->global_state;
}

/**
  * @brief  Get the free size in bytes of CRAM.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @return uint32_t  size in bytes.
  */
uint32_t HAL_HSP_GetCRAMFreeSizeByte(const hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  return hhsp->cram_free_size_byte;
}

#if defined (USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
/**
  * @brief  Get the HSP last error codes.
  * @param  hhsp      Pointer to a @ref hal_hsp_handle_t.
  * @return uint32_t  This return value can be a combination of the following values:
  *         @arg @ref HAL_HSP_ERROR_NONE
  */
uint32_t HAL_HSP_GetLastErrorCodes(const hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                        | (uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  return hhsp->last_error_codes;
}
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */
#if defined (USE_HAL_HSP_MSGBOX_GET_LAST_ERROR) && (USE_HAL_HSP_MSGBOX_GET_LAST_ERROR == 1)
/**
  * @brief  Get the HSP MsgBox last error code.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  * @retval HSP Error Code.
  */
uint32_t HAL_HSP_GetMsgBoxLastErrorCode(const hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  return hhsp->msgbox_last_error_code;
}
#endif /* USE_HAL_HSP_MSGBOX_GET_LAST_ERROR */

/**
  * @}
  */

#if defined (USE_HAL_HSP_USER_DATA) && (USE_HAL_HSP_USER_DATA == 1)
/** @addtogroup HSP_Exported_Functions_Group16
  * @{
A set of functions allowing to manage a user data pointer stored to the HSP handle:
 - HAL_HSP_SetUserData() : set the user data into the handle.
 - HAL_HSP_GetUserData() : get the user data from the handle.
  */

/**
  * @brief Set the user data pointer into the handle.
  * @param  hhsp Pointer to a @ref hal_hsp_handle_t.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_HSP_SetUserData(hal_hsp_handle_t *hhsp, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hhsp != NULL);

  hhsp->p_user_data = p_user_data;
}

/**
  * @brief Get the user data pointer from the handle.
  * @param  hhsp Pointer to a @ref hal_hsp_handle_t.
  * @return Pointer to the user data.
  */
const void *HAL_HSP_GetUserData(const hal_hsp_handle_t *hhsp)
{
  ASSERT_DBG_PARAM(hhsp != NULL);

  return hhsp->p_user_data;
}

/**
  * @}
  */
#endif /* USE_HAL_HSP_USER_DATA */

/**
  * @}
  */

/** @addtogroup HSP_Private_Functions
  * @{
  */
/**
  * @brief HSP Firmware reset request.
  * @param hhsp  HSP handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Timeout elapsed.
  */
static hal_status_t HSP_Reset(const hal_hsp_handle_t *hhsp)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Request the HSP Reset*/
  STM32_SET_BIT(p_hspx->CR, HSP_CR_RSTREQ);

  /* Get timeout */
  uint32_t tickstart = HAL_GetTick();

  while (!STM32_IS_BIT_SET(p_hspx->CR, HSP_CR_RSTOK))
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > HSP_RESET_TIMEOUT_MS)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (!STM32_IS_BIT_SET(p_hspx->CR, HSP_CR_RSTOK))
      {
        return HAL_ERROR;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Send a message by msgbox.
  * @param  hhsp        Pointer to a @ref hal_hsp_handle_t.
  * @param  message     Message for the HSP.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_BUSY  Send of Command is pending.
  */
static hal_status_t HSP_MSGBOX_SendMessage(const hal_hsp_handle_t *hhsp, uint32_t message)
{
  HSP_TypeDef *p_hspx;
  uint32_t c2hsem_reg;
  uint32_t h2csem_reg;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Read the HSP_C2HSEM bit via the CPU to HSP message control register (HSP_C2HSEMR)                        */
  /* Read the HSP_H2CSEM bit via the HSP to CPU message control register (HSP_H2CSEMR)                        */
  /* If set to 1, it indicates that the previous message was not yet read (and then acknowledged) by the HSP  */
  /* or a message was not read by the CPU */
  /* then the function returned BUSY to avoid an overwrite in C2HMSGDR register.             */
  c2hsem_reg = STM32_READ_BIT(p_hspx->C2HSEMR, HSP_C2HSEMR_C2HSEM);
  h2csem_reg = STM32_READ_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM);
  if ((c2hsem_reg == HSP_C2HSEMR_C2HSEM) || (h2csem_reg == HSP_H2CSEMR_H2CSEM))
  {
    return HAL_BUSY;
  }

  /* Write the message in mailbox and trigger the C2H semaphore to */
  STM32_WRITE_REG(p_hspx->C2HMSGDR, message);
  STM32_SET_BIT(p_hspx->C2HSEMR, HSP_C2HSEMR_C2HSEM);

  return HAL_OK;
}

/**
  * @brief  Get active-high flags from a register.
  * @param  p_reg_addr  Pointer to the register that contains the flags.
  * @param  mask        Mask of flags to get.
  * @return  Active-high flags.
  */
static uint32_t HSP_GetPolledFlagsActiveHigh(const __IOM uint32_t *p_reg_addr, uint32_t mask)
{
  return STM32_READ_REG(*p_reg_addr) & mask;
}

/**
  * @brief  Get active-low flags from a register.
  * @param  p_reg_addr  Pointer to the register that contains the flags.
  * @param  mask        Mask of flags to get.
  * @return  Active-low flags.
  */
static uint32_t HSP_GetPolledFlagsActiveLow(const __IOM uint32_t *p_reg_addr, uint32_t mask)
{
  return (~STM32_READ_REG(*p_reg_addr)) & mask;
}

/**
  * @brief  Poll register flags until the requested condition is met.
  * @param  poll_mode   Polling mode.
  * @param  p_reg_addr  Pointer to the register that contains the flags.
  * @param  mask        Mask of flags to poll.
  * @param  p_get_polled_flags  Function that gets the active flags.
  * @param  timeout_ms  Timeout duration in milliseconds.
  * @param  p_status    Pointer to the detected flags.
  * @retval HAL_OK      Requested flags are detected.
  * @retval HAL_TIMEOUT Timeout elapsed before detecting the requested flags.
  */
static hal_status_t HSP_PollRegisterFlags(hal_hsp_polling_mode_t poll_mode,
                                          const __IOM uint32_t *p_reg_addr, uint32_t mask,
                                          hsp_get_polled_flags_t p_get_polled_flags,
                                          uint32_t timeout_ms,
                                          uint32_t *p_status)
{
  uint32_t tickstart = 0U;

  if (timeout_ms != HAL_MAX_DELAY)
  {
    tickstart = HAL_GetTick();
  }

  *p_status = 0U;
  do
  {
    *p_status = p_get_polled_flags(p_reg_addr, mask);

    if (poll_mode != HAL_HSP_POLLING_FOR_ANY_EVENT)
    {
      *p_status = (STM32_IS_BIT_SET(*p_status, mask) != 0U) ? *p_status : 0U;
    }

    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        /* Read once more to avoid a false timeout when an interrupt preempts this function */
        *p_status = p_get_polled_flags(p_reg_addr, mask);

        if (poll_mode != HAL_HSP_POLLING_FOR_ANY_EVENT)
        {
          *p_status = (STM32_IS_BIT_SET(*p_status, mask) != 0U) ? *p_status : 0U;
        }

        if (*p_status == 0U)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  } while (*p_status == 0U);

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles the Signal Processor Engine Errors in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @param  error_info    Error Information register value.
  * @warning An ACCERRF error is qualified as a fault when one of the following error information bits is set:
  *            @arg HAL_HSP_ERROR_INFO_INTERNAL_AHB_ACCESS
  *            @arg HAL_HSP_ERROR_INFO_CODE_MEM_ACCESS
  * @retval uint32_t  Accumulated errors code.
  */
static uint32_t HSP_SPE_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr, uint32_t error_info)
{
  HSP_TypeDef *p_hspx;
  uint32_t errors = HAL_HSP_ERROR_NONE;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Signal Processor Engine Interface -----------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_FWERRF))
  {
    /* Clear flag: Firmware Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_FWERRC);

    errors |= HAL_HSP_ERROR_FIRMWARE;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_SCHERRF))
  {
    /* Clear flag: Scheduler Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_SCHERRC);

    errors |= HAL_HSP_FAULT_ERROR_SPE_SCHEDULER;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_BKINF))
  {
    /* Clear flag: Break Input */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_BKINC);

    errors |= HAL_HSP_ERROR_BREAK_IN;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_HDEGOVRF))
  {
    /* Clear flag: Signal Processor Engine Event Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_HDEGOVRC);

    errors |= HAL_HSP_ERROR_HDEG_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_OPCOERRF))
  {
    /* Clear flag: Invalid OpCode */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_OPCOERRC);

    errors |= HAL_HSP_FAULT_ERROR_SPE_OPCODE_INVALID;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_ACCERRF))
  {
    /* Clear flag: MMC Access Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_ACCERRC);

    /* Check if it is a fault or an error */
    if (IS_HSP_FAULT_ERROR_SPE_ACCESS(error_info))
    {
      errors |= HAL_HSP_FAULT_ERROR_SPE_ACCESS;
    }
    else
    {
      errors |= HAL_HSP_ERROR_SPE_ACCESS;
    }
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_FPUERRF))
  {
    /* Clear flag: Computation Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_FPUERRC);

    errors |= HAL_HSP_ERROR_FPU;
  }


  return errors;
}

/**
  * @brief  Subroutine IRQHandler for all HSP Error interrupt request.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  */
static void HSP_ERR_IRQHandler(hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;
  uint32_t errors = 0U;
  hal_hsp_hw_error_status_t error_status = HAL_HSP_HW_ERROR_NONE;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get Processing Status */
  uint32_t reg_err_ier = STM32_READ_REG(p_hspx->ERR_IER);
  uint32_t reg_err_isr = STM32_READ_REG(p_hspx->ERR_ISR);
  uint32_t reg_err_misr = reg_err_ier & reg_err_isr;

  /* Adjust value of reg_err_misr for Floating Point Unit ITs where there is only one FPU_ERR Flag */
  if ((reg_err_ier & HAL_HSP_SPE_ERR_IT_FPU_ALL) != 0U)
  {
    /* Complete the MISR for Floating Point Unit Error */
    reg_err_misr |= (reg_err_isr & HSP_ERR_ISR_FPUERRF);
  }

  /* Read FWERR and ERRINFR before processing each interrupt. These registers are reset by the hardware
     when the interrupt flags are cleared.
  */
  uint32_t fw_error_code = STM32_READ_BIT(p_hspx->FWERR, HSP_FWERR_FWERRN_Msk);
  uint32_t spe_error_inf = STM32_READ_REG(p_hspx->ERRINFR);

  /* STREAM Interface --------------------------------------------------------*/
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  errors |= HSP_STREAM_ErrorHandler(hhsp, reg_err_misr);
#endif /* USE_HAL_HSP_STREAM_IT */

  /* Trigger Input Interface -------------------------------------------------*/
#if defined(USE_HAL_HSP_TRGIN_IT) && (USE_HAL_HSP_TRGIN_IT == 1)
  errors |= HSP_TRGIN_ErrorHandler(hhsp, reg_err_misr);
#endif /* USE_HAL_HSP_TRGIN_IT */

  /* TSC Interface -----------------------------------------------------------*/
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  errors |= HSP_TSC_ErrorHandler(hhsp, reg_err_misr);
#endif /* USE_HAL_HSP_TSC_IT */

  /* Signal Processor Engine ---------------------------------------------------------------------*/
  errors |= HSP_SPE_ErrorHandler(hhsp, reg_err_misr, spe_error_inf);

  /* Call the Error Callback in case of Error detected */
  if ((errors & HAL_HSP_ERROR_HW_ALL) != HAL_HSP_ERROR_NONE)
  {
    if ((errors & HAL_HSP_FAULT_ERROR_ALL) != 0U)
    {
      hhsp->global_state = HAL_HSP_STATE_FAULT;
      error_status = HAL_HSP_HW_ERROR_FAULT;
    }
    else
    {
      error_status = HAL_HSP_HW_ERROR_MINOR;
    }

#if defined(USE_HAL_HSP_GET_LAST_ERRORS) && (USE_HAL_HSP_GET_LAST_ERRORS == 1)
    hhsp->last_error_codes |= errors;
#endif /* USE_HAL_HSP_GET_LAST_ERRORS */

    /* Call the corresponding callback to inform upper layer of Error */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_error_cb(hhsp, error_status, fw_error_code, spe_error_inf);
#else
    HAL_HSP_ErrorCallback(hhsp, error_status, fw_error_code, spe_error_inf);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Subroutine IRQHandler for all HSP Event interrupt request.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  */
static void HSP_EVT_IRQHandler(hal_hsp_handle_t *hhsp)
{
  const HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get Processing Status */
  uint32_t reg_evt_ier = STM32_READ_REG(p_hspx->EVT_IER);
  uint32_t reg_evt_isr = STM32_READ_REG(p_hspx->EVT_ISR);
  uint32_t reg_evt_misr = reg_evt_ier & reg_evt_isr;

  /* STREAM Interface --------------------------------------------------------*/
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
  HSP_STREAM_Handler(hhsp, reg_evt_misr);
#endif /* USE_HAL_HSP_STREAM_IT */

  /* Task Comparator Interface -----------------------------------------------*/
#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
  HSP_TCU_Handler(hhsp, reg_evt_misr);
#endif /* USE_HAL_HSP_TCU_IT */

  /* TimeStamp Ready ---------------------------------------------------------*/
#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
  HSP_TSC_Handler(hhsp, reg_evt_misr);
#endif /* USE_HAL_HSP_TSC_IT */

  /* Miscellaneous Signal Processor Engine Events ------------------------------------------------*/
  HSP_SPE_Handler(hhsp, reg_evt_misr);

  /* Command Interface -------------------------------------------------------*/
  HSP_PRC_Handler(hhsp, reg_evt_misr);
}

/**
  * @brief  Handle all HSP Firmware Event interrupt request.
  * @param  hhsp  Pointer to a @ref hal_hsp_handle_t.
  */
static void HSP_FWEVT_IRQHandler(hal_hsp_handle_t *hhsp)
{
#if defined(USE_HAL_HSP_PROCLIST_NOTIFICATION_IT) && (USE_HAL_HSP_PROCLIST_NOTIFICATION_IT == 1)
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get Processing Status */
  uint32_t reg_processing_ier = STM32_READ_REG(p_hspx->PFCTEVT_IER);
  uint32_t reg_processing_isr = STM32_READ_REG(p_hspx->PFCTEVT_ISR);
  uint32_t reg_processing_misr = reg_processing_ier & reg_processing_isr;

  if (reg_processing_misr != 0U)
  {
    /* Clear Flags: Processing Status */
    STM32_WRITE_REG(p_hspx->PFCTEVT_ICR, reg_processing_misr);

    /* Call the callback */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_processing_event_cb(hhsp, reg_processing_misr);
#else
    HAL_HSP_ProcessingEventCallback(hhsp, reg_processing_misr);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
#else
  STM32_UNUSED(hhsp);
#endif /* USE_HAL_HSP_PROCLIST_NOTIFICATION_IT */
}

#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
/**
  * @brief  Interrupt Sub-Routine which handles the STREAM Buffers in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_STREAM_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr)
{
  uint32_t stream_evts_status = (STM32_READ_BIT(reg_evt_misr, HAL_HSP_STREAM_EVT_IT_ALL) >> HSP_EVT_IER_B0EVTIE_Pos);

  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (stream_evts_status != 0U)
  {
    uint32_t stream_buff_reg = STM32_READ_REG(p_hspx->BUFFCFGR);
    uint32_t rx_buff_mask = (STM32_READ_BIT(~stream_buff_reg, HSP_BUFFCFGR_BUFFDIR_MSK) >> HSP_BUFFCFGR_BUFF0DIR_Pos);
    uint32_t tx_buff_mask = (STM32_READ_BIT(stream_buff_reg, HSP_BUFFCFGR_BUFFDIR_MSK) >> HSP_BUFFCFGR_BUFF0DIR_Pos);

    uint32_t stream_buffer_rx_ready = (rx_buff_mask & stream_evts_status);
    uint32_t stream_buffer_tx_ready = (tx_buff_mask & stream_evts_status);

    if (stream_buffer_rx_ready != 0U)
    {
      /* Some RX Buffers are empty */
      /* Disable ITs before the callback */
      STM32_CLEAR_BIT(p_hspx->EVT_IER, stream_buffer_rx_ready << HSP_EVT_IER_B0EVTIE_Pos);

#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
      hhsp->p_stream_buffer_empty_cb(hhsp, stream_buffer_rx_ready);
#else
      HAL_HSP_STREAM_BufferEmptyCallback(hhsp, stream_buffer_rx_ready);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
    }

    if (stream_buffer_tx_ready != 0U)
    {
      /* Some TX Buffers are full */
      /* Disable ITs before the callback */
      STM32_CLEAR_BIT(p_hspx->EVT_IER, stream_buffer_tx_ready << HSP_EVT_IER_B0EVTIE_Pos);

#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
      hhsp->p_stream_buffer_full_cb(hhsp, stream_buffer_tx_ready);
#else
      HAL_HSP_STREAM_BufferFullCallback(hhsp, stream_buffer_tx_ready);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
    }
  }
}
#endif /* USE_HAL_HSP_STREAM_IT */

#if defined(USE_HAL_HSP_TCU_IT) && (USE_HAL_HSP_TCU_IT == 1)
/**
  * @brief  Interrupt Sub-Routine which handles the Task Comparator Unit in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_TCU_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr)
{
  uint32_t tcu_start_flags = STM32_READ_BIT(reg_evt_misr, HSP_EVT_ISR_TCU_START_OF_TASK_FLAGS_MASK);
  uint32_t tcu_end_flags = STM32_READ_BIT(reg_evt_misr, HSP_EVT_ISR_TCU_END_OF_TASK_FLAGS_MASK);
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (tcu_start_flags != 0U)
  {
    /* Clear flag: Start of Task for Task Comparator Units */
    STM32_WRITE_REG(p_hspx->EVT_ICR, tcu_start_flags);

    /* Call the corresponding callback to inform upper layer of Start of Tasks */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_tcu_task_started_cb(hhsp, tcu_start_flags);
#else
    HAL_HSP_TCU_TaskStartedCallback(hhsp, tcu_start_flags);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }

  if (tcu_end_flags != 0U)
  {
    /* Clear flag: End of Task for Task Comparator Units */
    STM32_WRITE_REG(p_hspx->EVT_ICR, tcu_end_flags);

    /* Call the corresponding callback to inform upper layer of End of Tasks */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_tcu_task_ended_cb(hhsp, tcu_end_flags);
#else
    HAL_HSP_TCU_TaskEndedCallback(hhsp, tcu_end_flags);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }

  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_TOVLPF))
  {
    /* Clear flag: Task Overlap */
    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ISR_TOVLPF);

    /* Call the corresponding callback to inform upper layer of a Task Overlapping */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_tcu_task_overlap_cb(hhsp);
#else
    HAL_HSP_TCU_TaskOverlapCallback(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}
#endif /* USE_HAL_HSP_TCU_IT */

/**
  * @brief  Interrupt Sub-Routine which handles the Command Events in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_PRC_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* CDEG Event --------------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_CDEGRDYF))
  {
    /* Disable the IT enabled by HAL_HSP_TASK_Run_IT */
    STM32_CLEAR_BIT(p_hspx->EVT_IER, HSP_EVT_IER_CDEGRDYIE);

    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ICR_CDEGRDYC);

    /* Call the corresponding callback to inform upper layer of CDEG is Ready */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_prc_task_cplt_cb(hhsp);
#else
    HAL_HSP_PRC_TaskCpltCallback(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the Signal Processor Engine Events in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_SPE_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Signal Processor Engine State Events --------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_SOFWFEF))
  {
    /* Clear flag: Start Of WFE */
    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ISR_SOFWFEF);

    /* Call the corresponding callback to inform upper layer of Signal Processor Engine enters in WFE mode */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_spe_run_state_cb(hhsp, HAL_HSP_SPE_RUN_STATE_WFE);
#else
    HAL_HSP_SPE_RunStateCallback(hhsp, HAL_HSP_SPE_RUN_STATE_WFE);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
  else if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_EOFWFEF))
  {
    /* Clear flag: End Of WFE */
    STM32_SET_BIT(p_hspx->EVT_ICR, HSP_EVT_ISR_EOFWFEF);

    /* Call the corresponding callback to inform upper layer of Signal Processor Engine exits from WFE mode */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_spe_run_state_cb(hhsp, HAL_HSP_SPE_RUN_STATE_ACTIVE);
#else
    HAL_HSP_SPE_RunStateCallback(hhsp, HAL_HSP_SPE_RUN_STATE_ACTIVE);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
  else
  {
    /* No action to perform */
  }

  /* Floating Point Unit Saturation Event ------------------------------------*/
  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_FPUSATF))
  {
    /* Clear flag: Floating Point Unit Saturation */
    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ISR_FPUSATF);

    /* Call the corresponding callback to inform Floating Point Unit Saturation */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_spe_fpu_saturation_cb(hhsp);
#else
    HAL_HSP_SPE_FPUSaturationCallback(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
/**
  * @brief  Interrupt Sub-Routine which handles the TimeStamp Capture Events in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_TSC_Handler(hal_hsp_handle_t *hhsp, uint32_t reg_evt_misr)
{
  const HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_CAPRDYF))
  {
    hal_hsp_tsc_timestamp_t timestamp;

    timestamp.raw = STM32_READ_REG(p_hspx->CAPDR);

    /* Note: No need to clear the flag HSP_EVT_ISR_CAPRDYF. It is done by HW when CAPDR register is read */

    /* Call the corresponding callback to inform upper layer of a Task Overlapping */
#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->p_tsc_timestamp_ready_cb(hhsp, timestamp);
#else
    HAL_HSP_TSC_TimestampReadyCallback(hhsp, timestamp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}
#endif /* USE_HAL_HSP_TSC_IT */
#if defined(USE_HAL_HSP_STREAM_IT) && (USE_HAL_HSP_STREAM_IT == 1)
/**
  * @brief  Interrupt Sub-Routine which handles the STREAM Error in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @retval uint32_t      Accumulated errors code.
  */
static uint32_t HSP_STREAM_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr)
{
  HSP_TypeDef *p_hspx;
  uint32_t errors = HAL_HSP_ERROR_NONE;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* STREAM Interface --------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B0ERRF))
  {
    /* Clear flag: H2CBUFF0 Underrun or C2HBUFF0 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B0ERRC);

    errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B1ERRF))
  {
    /* Clear flag: H2CBUFF1 Underrun or C2HBUFF1 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B1ERRC);

    errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B2ERRF))
  {
    /* Clear flag: H2CBUFF2 Underrun or C2HBUFF2 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B2ERRC);

    errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B3ERRF))
  {
    /* Clear flag: H2CBUFF3 Underrun or C2HBUFF3 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B3ERRC);

    errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }

  return errors;
}
#endif /* USE_HAL_HSP_STREAM_IT */

#if defined(USE_HAL_HSP_TRGIN_IT) && (USE_HAL_HSP_TRGIN_IT == 1)
/**
  * @brief  Interrupt Sub-Routine which handles the Trigger Input Error in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @retval uint32_t      Accumulated errors code.
  */
static uint32_t HSP_TRGIN_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr)
{
  HSP_TypeDef *p_hspx;
  uint32_t errors = HAL_HSP_ERROR_NONE;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Trigger Input Interface ---------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_TRGIOVRF))
  {
    /* Clear flag: TRGITF Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_TRGIOVRC);

    errors |= HAL_HSP_ERROR_TRGIN_OVR;
  }

  return errors;
}
#endif /* USE_HAL_HSP_TRGIN_IT */

#if defined(USE_HAL_HSP_TSC_IT) && (USE_HAL_HSP_TSC_IT == 1)
/**
  * @brief  Interrupt Sub-Routine which handles the TimeStamp Capture Errors in interrupt mode.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @retval uint32_t      Accumulated errors code.
  */
static uint32_t HSP_TSC_ErrorHandler(const hal_hsp_handle_t *hhsp, uint32_t reg_err_misr)
{
  HSP_TypeDef *p_hspx;
  uint32_t errors = HAL_HSP_ERROR_NONE;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* TSC Interface -----------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_CAPOVRF))
  {
    /* Clear flag: Capture register Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_CAPOVRC);

    errors |= HAL_HSP_ERROR_CAPTURE_OVR;
  }

  return errors;
}
#endif /* USE_HAL_HSP_TSC_IT */

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_HSP_MODULE */
#endif /* HSP1 */
/**
  * @}
  */
