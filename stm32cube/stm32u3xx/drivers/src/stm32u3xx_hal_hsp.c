/**
  ******************************************************************************
  * @file    stm32u3xx_hal_hsp.c
  * @author  MCD Application Team
  * @brief   HSP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Hardware Signal Processor (HSP) peripheral:
  *           + Initialization and de-initialization functions
  *           + Peripheral Configuration functions
  *           + Peripheral State and Error functions
  *           + IRQ Handlers and Callbacks functions
  *           + Setter and Getter of the user data
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
    The HSP HAL driver can be used as follows:

    (#) Declare a HSP_HandleTypeDef handle structure (eg. HSP_HandleTypeDef hhsp).
    (#) Initialize the HSP low level resources by implementing the HAL_HSP_MspInit() API:
        (##) Enable the HSP interface clock.
        (##) Enable the SRAM related to the HSP (if not already enabled).
        (##) NVIC configuration if you need to use interrupt process:
            (+++) Configure the HSP interrupt priority.
            (+++) Enable the NVIC HSP IRQ handle.

    (#) Initialize the HSP handle by calling the HAL_HSP_Init() API which calls HAL_HSP_MspInit()

    (#) Load the Firmware Code part & Data part with HAL_HSP_LoadFirmware.
        The Firmware is based on the Firmware Code Part version embedded in the CROM.
        The Firmwares are delivered through the Middleware HSP Engine.

    (#) Load Plugin with HAL_HSP_LoadPlugin (Optional).
          This step requires one call per Plugin.
          Plugins are delivered through the Middleware HSP Engine.

    (#) Boot the HSP peripheral with HAL_HSP_Boot.
        If the boot fails, the handle state is set to HAL_HSP_STATE_FAULT to prohibit any configuration or processing.
        HAL_HSP_DeInit must be called, and an HSP Hardware Reset is required from RCC.

        If the boot succeeds, the handle state is set to HAL_HSP_STATE_RUNNING.
        The HSP peripheral is ready to be used.

    *** HSP HAL driver Processing List ***
    ======================================
    (#) To process a processing function (Accelerator mode), call in order, the following APIs:
          - HAL_HSP_DIRECT_WriteCommand(): to send the Processing Function Command ID
          - HAL_HSP_WriteParameter(): to send a parameter value (one call per parameter)
          - HAL_HSP_DIRECT_WriteCommandPointer() to send a pointer of buffer (one call per pointer)

        Refer to the HSP Processing Functions User Manual to find all processing functions available
        for the Accelerator mode.
        The Middleware HSP Engine embeds High level API for each Processing Function available in Accelerator Mode.

    (#) To record a processing list (Sequencer mode), use the following APIs:
          - HAL_HSP_RunTask(): to active the HSP Supervisor (HAL_HSP_TASK_SUPERVISOR)
          - HAL_HSP_MSGBOX_SendCommand(): to start/stop the recording
          - HAL_HSP_WriteParameter(): to send a parameter value (one call per parameter)

          1 - Start the recording:
              - Running the Task HAL_HSP_TASK_SUPERVISOR with HAL_HSP_RunTask
              - Send the Processing List ID with HAL_HSP_WriteParameter (HAL_HSP_PARAM_0)
              - Send the START command ID with HAL_HSP_MSGBOX_SendCommand() (The command ID is defined in the HSP FW)
          2 - Record a Processing function:
              - Prepare all the parameters with HAL_HSP_WriteParameter according to the Processing Function User Manual.
              - Send the Processing Function ID with HAL_HSP_MSGBOX_SendCommand() (The ID is defined in the HSP FW)
          3 - Stop the recording:
              - Send the STOP command ID with HAL_HSP_MSGBOX_SendCommand() (The command ID is defined in the HSP FW)

    *** HSP HAL driver Event configuration ***
    ==========================================
    [..]
    (#) To configure an event with STREAM Buffer as source:
          + Configure the STREAM Buffer <y> with the following API:
            - HAL_HSP_STREAM_EnableIntToFloat(/HAL_HSP_STREAM_DisableIntToFloat() to enable/disable the data conversion
              from Integer to Float
            - HAL_HSP_STREAM_SetConfig() to configure a STREAM Buffer

          + Configure an event <x> by calling HAL_HSP_EVENT_SetConfig() with HAL_HSP_EVENT_<x>_STREAM<y>

        When all STREAM Buffer are configured, enable the STREAM block with HAL_HSP_STREAM_Start().
        To change any STREAM Buffer configuration, first disable the STREAM block with HAL_HSP_STREAM_Stop.

    (#) To configure an event with a TRGIN trigger as source:
          + Configure the TRGIN <y> trigger with HAL_HSP_TRGIN_SetConfig()
          + Configure an event <x> by calling HAL_HSP_EVENT_SetConfig() with HAL_HSP_EVENT_<x>_TRGIN<y>

        When the TRGIN is configured, enable it with HAL_HSP_TRGIN_Enable().

        To change any TRGIN configuration, first disable it with HAL_HSP_TRGIN_Disable().

        In polling mode, the HAL provides these APIs:
          - HAL_HSP_TRGIN_IsActiveFlag_Overrun to get the Overrun Flag status
          - HAL_HSP_TRGIN_GetOverrun to get the mask of TRGINs in overrun
          - HAL_HSP_TRGIN_ClearFlag_Overrun to clear the Overrun Flag

        In interrupt mode, enable the TRGIN Event ITs with HAL_HSP_TRGIN_EnableIT().

    (#) To configure an event triggered by the CPU (CSEG interface):
          + Configure an event <x> by calling HAL_HSP_EVENT_SetConfig with HAL_HSP_EVENT_<x>_CSEG

    (#) To configure an event triggered by the SPE itself (HSEG interface):
          + Configure an event <x> by calling HAL_HSP_EVENT_SetConfig with HAL_HSP_EVENT_<x>_HSEG

        Note: a processing list will trig this event by calling the Processing Function SEND_EVENT (ref HSP Processing
              Function User Manual)

    *** HSP HAL driver processing list execution ***
    ================================================
    [..]
    (#) To execute a Processing List by software, call the following APIs:
          - HAL_HSP_TASK_Run: Post the Processing List ID in polling mode. The execution is scheduled with
                              the lowest priority.
          - HAL_HSP_TASK_Run_IT: Post the Processing List ID in interrupt mode. The execution is scheduled with
                                 the lowest priority. The callback HAL_HSP_EVT_SPE_TaskCpltCallback is called
                                 when the process is terminated.
          - HAL_HSP_EVENT_RequestSWTrigger: Post the trig of event linked to the Processing List ID. The execution is
                                 scheduled with the Event Level priority.
                                 The Processing List must have the same ID number than the Event to configure.
                                 The Event must be configured with HAL_HSP_Event_SetConfig and the source must be
                                 one of HAL_HSP_EVENT_x_CSEG.

                                 To wait the end of execution, call HAL_HSP_EVENT_PollForPending.

    (#) To execute a Processing List by external trigger, just ensure:
         - The trigger is well configured and enabled
         - The Event (related to the Processing List) linked to this trigger is well enabled also.

        If all conditions are done, the HW will trig the HSP Event. The execution of the Processing List
        will be scheduled by the SPE.

    (#) To execute a Processing List by the HSP itself (SPE), record the Processing Function SEND_EVENT
        in another Processing List (see HSP Processing Function User Manual)

        The execution of this Processing List with be scheduled by the SPE:
          - with a highest priority if HDEG interface is selected,
          - with the event priority level attached to the processing list if HSEG interface is selected.

    (#) To manage the HSP Outputs call the following APIs:
          - HAL_HSP_OUTPUT_SetConfigTrigger() to configure the source of each TRGOx output
          - HAL_HSP_OUTPUT_Enable() to enable all the TRGO & GPO Outputs
          - HAL_HSP_OUTPUT_Disable() to disable all the TRGO & GPO Outputs

    *** SPE Event in Interrupt mode ***
    ====================================
    [..]
      (#) To enable SPE Event ITs, call the HAL_HSP_SPE_EVENT_EnableIT()
      (#) To enable SPE Error ITs, call the HAL_HSP_SPE_ERROR_EnableIT()
          All selected SPE Error ITs will call the unique HAL_HSP_ErrorCallback callback

              (+) by selecting a Task Comparator Unit (@ref HAL_HSP_TASK_ComparatorTypeDef)
              (+) by setting HAL_HSP_EVENT_SYNC_ENABLE for the attribute "state"
            + Configure and Enable a Task Comparator Unit to select the Task to monitor and
             active the Start/End Of Task Event with the API HAL_HSP_TCU_EnableComparator

    *** HSP HAL Driver Performance & Debug ***
    ==========================================
    [..]
      (#) To synchronize the execution of a process list (linked to an event) by the end of another task:
            + When configuring the EVENT, configure the attribute "sync" (HAL_HSP_EVENT_SyncTypeDef):
              (+) by selecting a Task Comparator Unit (@ref HAL_HSP_TASK_ComparatorTypeDef)
              (+) by setting HAL_HSP_EVENT_SYNC_ENABLE for the attribute "state"
            + Configure and Enable a Task Comparator Unit to select the Task to monitor and
             active the Start/End Of Task Event with the API HAL_HSP_TCU_EnableComparator

      (#) To reduce BRAM conflict access shared between CPU and HSP:
            + Enable the Conflict Access Counter HAL_HSP_BRAM_EnableConflictAccessCounter()
            + Run your processing sequence and Get the counter value with HAL_HSP_BRAM_GetConflictAccessCounter()
            + Change the BRAM Arbitration with HAL_HSP_BRAM_SetBandwidthArbitration() to try
              to reduce BRAM conflict access
            + Run your processing sequence a second time and Get the counter value
              with HAL_HSP_BRAM_GetConflictAccessCounter()
            + Check if the BRAM Arbitration changes reduce the number of conflict access

      (#) To debug the processing lists execution, enable the TimeStamp Capture capability:
            + Configure the TimeStamp Capture with HAL_HSP_TSC_SetConfig()
            + Enable the TimeStamp Capture with:
                (+) HAL_HSP_TSC_Enable() for polling mode
                (+) HAL_HSP_TSC_Enable_IT() for interrupt mode

      (#) Use HAL_HSP_SNOOP_Enable() to observe key signals to ease application tuning.
          For this capability, HSP pins must be configured:
            (++) Enable the clock for the HSP GPIOs
            (++) Configure HSP pins as alternate function

      (#) To manage the power consumption of HSP blocks call the following APIs:
          + HAL_HSP_SMARTCLOCKING_Enable() enables the Smart Clocking of some clocks (Default mode)
          + HAL_HSP_SMARTCLOCKING_Disable() disables the Smart Clocking of some clocks (increase the power consumption)

      (#) Use HAL_HSP_BREAK_EnableFreezeEvent() to freeze the SPE when selected Events occurred.

    *** HSP HAL Driver Break feature ***
    ====================================
    [..]
      (+) Use HAL_HSP_BREAK_EnableCriticalEvent() to stop sensitive peripheral
          when a critical issue is detected in the HSP.

    *** Callback registration ***
    =============================
    [..]
        The compilation define USE_HAL_HSP_REGISTER_CALLBACKS, when set to 1,
        allows the user to configure dynamically the driver callbacks.

    [..]
        Use the HAL_HSP_Register<Xxxx>Callback() functions to register callbacks:
            (+) HAL_HSP_RegisterMspInitCallback               : HSP MspInit callback.
            (+) HAL_HSP_RegisterMspDeInitCallback             : HSP MspDeInit callback.
            (+) HAL_HSP_RegisterSPE_DirectCommandCpltCallback : HSP Direct Command Complete callback.
            (+) HAL_HSP_RegisterSPE_TaskCpltCallback          : HSP Task Complete callback.
            (+) HAL_HSP_RegisterSPE_FPUSaturationCallback     : HSP FPU Saturation callback.
            (+) HAL_HSP_RegisterSPE_RunStateCallback          : HSP SPE Running State callback.
            (+) HAL_HSP_RegisterSTREAM_BufferEmptyCallback    : HSP STREAM Buffer Empty callback.
            (+) HAL_HSP_RegisterSTREAM_BufferFullCallback     : HSP STREAM Buffer Full callback.
            (+) HAL_HSP_RegisterTCU_TaskOverlapCallback       : HSP Task Overlap callback.
            (+) HAL_HSP_RegisterTCU_TaskStartedCallback       : HSP Task Started callback.
            (+) HAL_HSP_RegisterTCU_TaskEndedCallback         : HSP Task Ended callback.
            (+) HAL_HSP_RegisterTSC_TimestampReadyCallback    : HSP TimeStamp Capture Ready callback.
            (+) HAL_HSP_RegisterErrorCallback                 : HSP Errors callback.
            (+) HAL_HSP_RegisterFWEVT_ProcessingEventCallback : HSP Processing Event callback.

    [..]
        Use the HAL_HSP_Register<xxx>Callback() function to unregister callback by passing
        the corresponding weak function.

    [..]
        By default, after the HAL_HSP_Init and when the state is HAL_HSP_STATE_RESET,
        all callbacks are reset to the corresponding legacy weak functions.

        Exception done for MspInit and MspDeInit callbacks that are respectively
        reset to the legacy weak function in the HAL_HSP_Init() and HAL_HSP_DeInit() only when
        these callbacks are NULL (not registered beforehand).
        If not, MspInit or MspDeInit are not NULL, the HAL_HSP_Init() and HAL_HSP_DeInit()
        keep and use the user MspInit/MspDeInit callbacks (registered beforehand).

    [..]
        Callbacks can be registered/unregistered in HAL_HSP_STATE_RUNNING state only.
        Exception done for MspInit/MspDeInit callbacks that can be registered/unregistered
        in HAL_HSP_STATE_RUNNING or HAL_HSP_STATE_RESET state,
        thus registered (user) MspInit/DeInit callbacks can be used during the Init/DeInit.
        In that case, first register the MspInit/MspDeInit user callbacks
        using HAL_HSP_RegisterCallback before calling HAL_HSP_DeInit() or HAL_HSP_Init() function.

    [..]
        When the compilation define USE_HAL_HSP_REGISTER_CALLBACKS is set to 0 or
        not defined, the callback registering feature is not available and all callbacks
        are set to the corresponding weak functions.

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u3xx_hal.h"

/** @addtogroup STM32U3xx_HAL_Driver
  * @{
  */

#if defined(HSP1)

/** @addtogroup HSP
  * @{
  */

#ifdef HAL_HSP_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup HSP_Private_Constants  HSP Private Constants
  * @{
  */
/**
  * @defgroup  HSP_Firmware_Constants HSP Firmware Constants
  * @{
  */
#define HSP_FW_STATUS_INIT             (0U)                      /*!< Firmware is in INIT phase                     */
#define HSP_FW_STATUS_WAIT_INIT_CMD    (1U << HSP_CR_BSTAT_Pos)  /*!< Firmware is waiting the Init command          */
#define HSP_FW_STATUS_RUN              (2U << HSP_CR_BSTAT_Pos)  /*!< Firmware is in RUN phase: SPE is in WFE state */
#define HSP_FW_STATUS_PROCFG           (3U << HSP_CR_BSTAT_Pos)  /*!< Firmware is recording a Processing list       */
#define HSP_FW_STATUS_RESET_ALL_PL     (4U << HSP_CR_BSTAT_Pos)  /*!< Firmware is resetting all the Processing list */
#define HSP_FW_STATUS_ADD_PLUGIN       (8U << HSP_CR_BSTAT_Pos)  /*!< Firmware is adding Plugin                     */

#define HSP_FW_END_PATTERN  0xFFFFFFFFUL  /*!< Pattern to close the Firmware CRAM */

/**
  * @}
  */

/**
  * @defgroup  HSP_Hardware_Constants HSP Hardware Constants
  * @{
  */
#define HSP_REG_TRGINSEL_CFG_NBR  4U  /*!< Number of TRGIN Config bitfield per TRGINSELRx register */
#define HSP_REG_TRGINSEL_SELECT_FIELD_SIZE  8U  /*!< Size in bit for Source Selection bitfield in TRGINSELRx register */
#define HSP_REG_EVTSRC_CFG_NBR  8U  /*!< Number of EVTSRC Config bitfield per HSP_EVTSRCxR register */
#define HSP_REG_EVTSRC_FIELD_SIZE  4U  /*!< Size in bit for Source Selection bitfield in HSP_EVTSRCxR register */
#define HSP_REG_TCUCFGR_BITFIELD_SIZE  8U  /*!< Size in bit for all bitfields of a TCU Config
                                                in HSP_TCUCFGR_TSKCMPx register */
#define HSP_REG_TRGOCFGR_BITFIELD_SRC_SIZE  2U  /*!< Size in bit for Source bitfield in HSP_TRGOCGGR register */

/**
  * @}
  */

/**
  * @defgroup  HSP_Interrupt_Constants HSP Interrupt Constants
  * @{
  */
/** HSP Mask of all TCU Start Of Task flags */
#define HSP_EVT_ISR_TCU_START_OF_TASK_FLAGS_MASK  \
  (HSP_EVT_ISR_SOTECP0F   | HSP_EVT_ISR_SOTECP1F  \
   | HSP_EVT_ISR_SOTECP2F | HSP_EVT_ISR_SOTECP3F)

/** HSP Mask of all TCU End Of Task flags */
#define HSP_EVT_ISR_TCU_END_OF_TASK_FLAGS_MASK    \
  (HSP_EVT_ISR_EOTECP0F   | HSP_EVT_ISR_EOTECP1F  \
   | HSP_EVT_ISR_EOTECP2F | HSP_EVT_ISR_EOTECP3F)

/** HSP Mask of all STREAM Buffer Event flags */
#define HSP_EVT_ISR_STREAM_READY_FLAGS_MASK   \
  (HSP_EVT_ISR_B0EVTF   | HSP_EVT_ISR_B1EVTF  \
   | HSP_EVT_ISR_B2EVTF | HSP_EVT_ISR_B3EVTF)

/** HSP Mask of all STREAM Buffer Directions */
#define HSP_BUFFCFGR_BUFFDIR_MSK                    \
  (HSP_BUFFCFGR_BUFF0DIR   | HSP_BUFFCFGR_BUFF1DIR  \
   | HSP_BUFFCFGR_BUFF2DIR | HSP_BUFFCFGR_BUFF3DIR)

/** HSP Mask of all Event Interrupts */
#define HSP_IT_EVT_ALL                                                         \
  (HAL_HSP_IT_EVT_CMD_DIRECT_COMMAND_DONE | HAL_HSP_IT_EVT_CMD_CDEG_READY      \
   | HAL_HSP_IT_EVT_TSC_DATA_READY        | HAL_HSP_IT_EVT_SPE_FPU_SATURATION  \
   | HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE      | HAL_HSP_IT_EVT_SPE_EXIT_FROM_WFE   \
   | HAL_HSP_IT_EVT_STREAM_ALL            | HAL_HSP_IT_EVT_TCU_ALL)

/** HSP Mask of all Error Interrupts */
#define HSP_IT_ERR_ALL                                                                             \
  (HAL_HSP_IT_ERR_TRGIN_OVR      | HAL_HSP_IT_ERR_STREAM_ALL         | HAL_HSP_IT_ERR_TSC_OVR      \
   | HAL_HSP_IT_ERR_SPE_FW       | HAL_HSP_IT_ERR_SPE_SCHEDULER      | HAL_HSP_IT_ERR_SPE_BREAK    \
   | HAL_HSP_IT_ERR_SPE_HDEG_OVR | HAL_HSP_IT_ERR_SPE_INVALID_OPCODE | HAL_HSP_IT_ERR_SPE_ACCESS   \
   | HAL_HSP_IT_ERR_SPE_FPU_UDF  | HAL_HSP_IT_ERR_SPE_FPU_OVF        | HAL_HSP_IT_ERR_SPE_FPU_DBZ  \
   | HAL_HSP_IT_ERR_SPE_FPU_INVALID | HAL_HSP_IT_ERR_SPE_FPU_DENORMAL)

/**
  * @}
  */

/** HSP Timestamp Capture Configuration CAPCR Mask */
#define HSP_TSC_CONFIG_CAPCR_MASK  (HSP_CAPCR_PRESC_Msk | HSP_CAPCR_FRCNTEN_Msk | HSP_CAPCR_TSKFLT_Msk)

/**
  * @defgroup  HSP_Common_Constants HSP Common Constants
  * @{
  */
/** HSP Reset Request Timeout in millisecond */
#define HSP_TIMEOUT_RESET_MS 1U

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
/** Alias to ASSERT_DBG_PARAM macro. */
#define ASSERT_DBG_PARAM  assert_param

/**
  * @brief Retrieve the HSP hardware CMSIS instance from the hal handle.
  * @param  handle  HSP Handle
  * @retval Address of the HSP instance
  */
#define HSP_GET_INSTANCE(handle)  ((handle)->Instance)

/** @defgroup HSP_Private_Macros_Group1  HSP Private Macros for BRAM
  * @{
  */

/**
  * @brief Get the HSP BRAMAB Base Address.
  * @param  instance_id  HSP instance.
  * @retval uint32_t.
  */
#define HSP_GET_BRAMAB_BASE_ADDRESS(instance_id)  \
  ((((uint32_t)(instance_id)) == (uint32_t)HSP1_BASE)?HSP1_BRAMAB_BASE: ((uint32_t)NULL))

/**
  * @brief Retrieve the HSP CRAM Base Address.
  * @param  instance  HSP instance.
  * @retval Address  If instance supported
  * @retval NULL  If instance not supported
  */
#define HSP_GET_CRAM_BASE_ADDRESS(instance)  (((instance) == HSP1)?HSP1_CRAM_BASE:((uint32_t)NULL))

/**
  * @brief Retrieve the HSP CRAM Base Address.
  * @param  instance  HSP instance.
  * @retval Address  If instance supported
  * @retval NULL  If instance not supported
  */
#define HSP_GET_DRAM_BASE_ADDRESS(instance)  (((instance) == HSP1)?HSP1_DRAM_BASE:((uint32_t)NULL))

/**
  * @brief Retrieve the size of HSP CRAM.
  * @param  instance  HSP instance.
  * @retval Size  CRAM size in word if instance supported
  * @retval NULL  If instance not supported
  */
#define HSP_GET_CRAM_SIZE_IN_WORD(instance)  (((instance) == HSP1)?(HSP1_CRAM_SIZE / 4U):0U)

/**
  * @brief Retrieve the size of HSP DRAM.
  * @param  instance  HSP instance.
  * @retval Size  DRAM size in word if instance supported
  * @retval NULL  If instance not supported
  */
#define HSP_GET_DRAM_SIZE_IN_WORD(instance)  (((instance) == HSP1)?(HSP1_DRAM_SIZE / 4U):0U)

/**
  * @}
  */

/**
  * @brief Check if the handle state is expected in val_condition
  */
#if defined(USE_HSP_ASSERT_DBG_STATE)
/**
  * @brief  The HSP_ASSERT_DBG_STATE macro is used for function's states check.
  * @param  __STATE__ the state filed within the PPP handle
  * @param  __VAL__ the authorized states value(s) to be checked
  *                 can be a combination of states
  * @note   if __STATE__ & __VAL__ is zero (unauthorized state) then
  * @note   assert_dbg_state_failed function is called which reports
  *         the name of the source file and the source line number of the call that failed.
  *         if __STATE__ & __VAL__ is zero (unauthorized state) then, the ASSERT_DBG_STATE macro returns no value.
  */
#define HSP_ASSERT_DBG_STATE(__STATE__,__VAL__)                                         \
  do {                                                                                  \
    if ((((uint32_t)(__STATE__)) & ((uint32_t)(__VAL__))) == 0U) { return HAL_ERROR; }  \
  } while(0U)
#else
#define HSP_ASSERT_DBG_STATE(__STATE__,__VAL__)  ((void)0U)
#endif /* USE_ASSERT_DBG_STATE  */

/** @defgroup HSP_Private_Macros_Group2  HSP Private Macros for Assertion Parameters
  * @{
  */
/**
  * @brief Verify the Performance Monitor State value.
  * @param  state  Value of Performance Monitor State (@ref HAL_HSP_PERF_MONITOR_StateTypeDef).
  * @retval SET    State value is valid.
  * @retval RESET  State value is invalid.
  */
#define IS_HSP_PERF_MONITOR_STATE(state)        \
  (((state) == HAL_HSP_PERF_MONITOR_DISABLE)    \
   || ((state) == HAL_HSP_PERF_MONITOR_ENABLE))

/**
  * @brief Verify the Stream Identifier.
  * @param  id  Stream ID (@ref HAL_HSP_STREAM_BufferTypeDef).
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
  * @param  direction  Stream Direction (@ref HAL_HSP_STREAM_Buffer_DirectionTypeDef).
  * @retval SET    direction value is valid.
  * @retval RESET  direction value is invalid.
  */
#define IS_HSP_STREAM_BUFFER_DIRECTION(direction)          \
  (((direction) == HAL_HSP_STREAM_BUFFER_DIRECTION_RX)     \
   || ((direction) == HAL_HSP_STREAM_BUFFER_DIRECTION_TX))

/**
  * @brief Verify the Stream Buffer Sync State.
  * @param  state  Stream Buffer Sync State (@ref HAL_HSP_STREAM_Buffer_Sync_StateTypeDef).
  * @retval SET    state value is valid.
  * @retval RESET  state value is invalid.
  */
#define IS_HSP_STREAM_BUFFER_SYNC_STATE(state)         \
  (((state) == HAL_HSP_STREAM_BUFFER_SYNC_DISABLE)     \
   || ((state) == HAL_HSP_STREAM_BUFFER_SYNC_ENABLE))

/**
  * @brief Verify the STREAM Event Interrupts.
  * @param  interrupts  Event Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
  */
#define IS_HSP_STREAM_BUFFER_IT_EVENT(interrupts)                 \
  (((interrupts) > 0UL)                                           \
   && (((interrupts) & HAL_HSP_IT_EVT_STREAM_ALL) == (interrupts)))

/**
  * @brief Verify the STREAM Error Interrupts.
  * @param  interrupts  Error Interrupt mask.
  * @retval SET    Mask value is valid.
  * @retval RESET  Mask value is invalid.
  */
#define IS_HSP_STREAM_BUFFER_IT_ERROR(interrupts)                 \
  (((interrupts) > 0UL)                                           \
   && (((interrupts) & HAL_HSP_IT_ERR_STREAM_ALL) == (interrupts)))

/**
  * @brief Verify the TRGIN Identifier.
  * @param  id  TRGIN ID.
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
  * @brief Verify the TRGIN Identifiers.
  * @param  ids  TRGIN IDs.
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_TRGIN_COMBINATION(ids)       \
  (((ids) > 0UL)                            \
   && (((ids) & HAL_HSP_TRGIN_ALL) == (ids)))

/**
  * @brief Verify the TRGIN Polarity.
  * @param  polarity  Polarity value (@ref HAL_HSP_TRGIN_PolarityTypeDef).
  * @retval SET    polarity is valid.
  * @retval RESET  polarity is invalid.
  */
#define IS_HSP_TRGIN_POLARITY(polarity)               \
  (((polarity) == HAL_HSP_TRGIN_POLARITY_FALLING)     \
   || ((polarity) == HAL_HSP_TRGIN_POLARITY_RISING))

/**
  * @brief Verify the value of TRGIN source.
  * @param  source  id of the trigger signal (@ref HAL_HSP_TRGIN_SourceTypeDef).
  * @retval SET (id is valid) or RESET (id is invalid)
  */
#define IS_HSP_TRGIN_SOURCE(source)             \
  (((source) == HAL_HSP_TRGIN_DMA1_CH1_TC)      \
   || ((source) == HAL_HSP_TRGIN_DMA1_CH2_TC)   \
   || ((source) == HAL_HSP_TRGIN_DMA1_CH3_TC)   \
   || ((source) == HAL_HSP_TRGIN_DMA1_CH4_TC)   \
   || ((source) == HAL_HSP_TRGIN_EXTI0)         \
   || ((source) == HAL_HSP_TRGIN_EXTI1)         \
   || ((source) == HAL_HSP_TRGIN_TIM1_TRGO)     \
   || ((source) == HAL_HSP_TRGIN_TIM1_TRGO2)    \
   || ((source) == HAL_HSP_TRGIN_TIM2_TRGO)     \
   || ((source) == HAL_HSP_TRGIN_TIM3_TRGO)     \
   || ((source) == HAL_HSP_TRGIN_TIM6_TRGO)     \
   || ((source) == HAL_HSP_TRGIN_TIM7_TRGO)     \
   || ((source) == HAL_HSP_TRGIN_TIM8_TRGO)     \
   || ((source) == HAL_HSP_TRGIN_TIM8_TRGO2)    \
   || ((source) == HAL_HSP_TRGIN_TIM15_TRGO)    \
   || ((source) == HAL_HSP_TRGIN_LPTIM1_CH1)    \
   || ((source) == HAL_HSP_TRGIN_LPTIM1_CH2)    \
   || ((source) == HAL_HSP_TRGIN_LPTIM2_CH1)    \
   || ((source) == HAL_HSP_TRGIN_LPTIM2_CH2)    \
   || ((source) == HAL_HSP_TRGIN_ADF1_SAD_DET))


/**
  * @brief Verify the STREAM Error Interrupts.
  * @param  interrupts  Error Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
  */
#define IS_HSP_TRGIN_IT_ERR(interrupts)                            \
  (((interrupts) > 0UL)                                            \
   && ((((interrupts) & HAL_HSP_IT_ERR_TRGIN_ALL) == (interrupts))))

/**
  * @brief Verify the Processing Function Event Interrupts.
  * @param  interrupts  Event Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
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
  * @param  mask  Event IDs mask
  * @retval SET    Mask is valid.
  * @retval RESET  Mask is invalid.
  */
#define IS_HSP_EVENTS_MASK(mask)              \
  (((mask) > 0U) && STM32_IS_BIT_SET(HAL_HSP_EVENT_ALL, (mask)))


/**
  * @brief Verify the Event Sync State.
  * @param  state  Event state (@ref HAL_HSP_EVENT_Sync_StateTypeDef)
  * @retval SET    state is valid.
  * @retval RESET  state is invalid.
  */
#define IS_HSP_EVENT_SYNC_STATE(state)        \
  (((state) == HAL_HSP_EVENT_SYNC_DISABLE)    \
   || ((state) == HAL_HSP_EVENT_SYNC_ENABLE))

/**
  * @brief Verify the value of EVENT source.
  * @param  source  id of the trigger signal (@ref HAL_HSP_EVENT_SourceTypeDef).
  * @retval SET (id is valid) or RESET (id is invalid)
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
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_SMARTCLOCKING(clock_id)  \
  (((clock_id) > 0U)                    \
   && (((clock_id) & HAL_HSP_SMARTCLOCKING_ALL) == (clock_id)))

/**
  * @brief Verify the Task Identifier.
  * @param  task_id  Task ID (@ref HAL_HSP_TaskTypeDef).
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
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
  * @param  id  TCU ID (@ref HAL_HSP_TASK_ComparatorTypeDef).
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_TCU(id)                     \
  (((id) == HAL_HSP_TASK_COMPARATOR_0)     \
   || ((id) == HAL_HSP_TASK_COMPARATOR_1)  \
   || ((id) == HAL_HSP_TASK_COMPARATOR_2)  \
   || ((id) == HAL_HSP_TASK_COMPARATOR_3))

/**
  * @brief Verify the Task Comparator Unit 0 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
  */
#define IS_HSP_TCU0_IT(interrupts)  \
  (((interrupts) & HAL_HSP_IT_EVT_TCU0_ALL) == (interrupts))

/**
  * @brief Verify the Task Comparator Unit 1 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
  */
#define IS_HSP_TCU1_IT(interrupts)  \
  (((interrupts) & HAL_HSP_IT_EVT_TCU1_ALL) == (interrupts))

/**
  * @brief Verify the Task Comparator Unit 2 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
  */
#define IS_HSP_TCU2_IT(interrupts)  \
  (((interrupts) & HAL_HSP_IT_EVT_TCU2_ALL) == (interrupts))

/**
  * @brief Verify the Task Comparator Unit 3 interrupts.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
  */
#define IS_HSP_TCU3_IT(interrupts)  \
  (((interrupts) & HAL_HSP_IT_EVT_TCU3_ALL) == (interrupts))

/**
  * @brief Verify the TCU Interrupts.
  * @param  tcu_id      Task Comparator Unit ID.
  * @param  interrupts  Interrupt mask.
  * @retval SET    interrupts is valid.
  * @retval RESET  interrupts is invalid.
  */
#define IS_HSP_TCU_IT(tcu_id, interrupts)                                        \
  ((((tcu_id) == HAL_HSP_TASK_COMPARATOR_0)    && IS_HSP_TCU0_IT((interrupts)))  \
   || (((tcu_id) == HAL_HSP_TASK_COMPARATOR_1) && IS_HSP_TCU1_IT((interrupts)))  \
   || (((tcu_id) == HAL_HSP_TASK_COMPARATOR_2) && IS_HSP_TCU2_IT((interrupts)))  \
   || (((tcu_id) == HAL_HSP_TASK_COMPARATOR_3) && IS_HSP_TCU3_IT((interrupts))))

/**
  * @brief Verify the TCU Flags.
  * @param  flags   Flags mask.
  * @retval SET     interrupts is valid.
  * @retval RESET   interrupts is invalid.
  */
#define IS_HSP_TCU_FLAGS(flags)  \
  (STM32_IS_BIT_SET(HAL_HSP_FLAG_EVT_TCU_ALL, (flags)) != 0U)

/**
  * @brief Verify the Task Overlap interrupts.
  * @param  interrupts  Interrupts mask.
  * @retval SET     interrupts is valid.
  * @retval RESET   interrupts is invalid.
  */
#define IS_HSP_TASK_OVERLAP_IT(interrupts)  \
  (((interrupts) == HAL_HSP_IT_NONE) || ((interrupts) == HAL_HSP_IT_EVT_TCU_TASK_OVL))

/**
  * @brief Verify the Trigger Output Identifier.
  * @param  id  Trigger Output Id (@ref HAL_HSP_OUTPUT_TriggerTypeDef).
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_OUTPUT_TRIGGER(id)         \
  (((id) == HAL_HSP_OUTPUT_TRIGGER_0)     \
   || ((id) == HAL_HSP_OUTPUT_TRIGGER_1)  \
   || ((id) == HAL_HSP_OUTPUT_TRIGGER_2)  \
   || ((id) == HAL_HSP_OUTPUT_TRIGGER_3))

/**
  * @brief Verify the Trigger Output Source Identifier.
  * @param  id  Trigger Output Source ID (@ref HAL_HSP_OUTPUT_TRIGGER_SourceTypeDef).
  * @retval SET    ID value is valid.
  * @retval RESET  ID value is invalid.
  */
#define IS_HSP_OUTPUT_TRIGGER_SOURCE(id)                \
  (((id) == HAL_HSP_OUTPUT_TRIGGER_NONE)                \
   || ((id) == HAL_HSP_OUTPUT_TRIGGER_STREAM)           \
   || ((id) == HAL_HSP_OUTPUT_TRIGGER_CORE)             \
   || ((id) == HAL_HSP_OUTPUT_TRIGGER_TIMESTAMPCAPTURE))

/**
  * @brief Verify the TimeStamp Capture Prescaler value.
  * @param  value  Prescaler value (@ref HAL_HSP_TSC_PrescalerTypeDef).
  * @retval SET    Prescaler value is valid.
  * @retval RESET  Prescaler value is invalid.
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
  * @param  value  Free Counter value (@ref HAL_HSP_TSC_FreeRunningCounterStateTypeDef).
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_TSC_FREE_COUNTER(value)              \
  (((value) == HAL_HSP_TSC_FREE_COUNTER_DISABLE)    \
   || ((value) == HAL_HSP_TSC_FREE_COUNTER_ENABLE))

/**
  * @brief Verify the TimeStamp Capture Filter.
  * @param  value  Filter value (@ref HAL_HSP_TSC_TaskFilterTypeDef).
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_TSC_FILTER(value)                    \
  (((value) == HAL_HSP_TSC_TASK_FILTER_NONE)        \
   || ((value) == HAL_HSP_TSC_TASK_FILTER_TSKCMP0))

/**
  * @brief Verify the TimeStamp Capture Mode.
  * @param  mode  Mode value (@ref HAL_HSP_TSC_Capture_ModeTypeDef).
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_TSC_CAPTURE_MODE(mode)                        \
  (((mode) == HAL_HSP_TSC_CAPTURE_MODE_SPE_BREAKS)           \
   || ((mode) == HAL_HSP_TSC_CAPTURE_MODE_TASK_NBR_CHANGES)  \
   || ((mode) == HAL_HSP_TSC_CAPTURE_MODE_PFCT_NBR_CHANGES))

/**
  * @brief Verify the BRAM Arbitration value.
  * @param  value  BRAM Arbitration (@ref HAL_HSP_BRAM_ArbitrationTypeDef).
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_BRAM_ARBITRATION(value)                        \
  (((value) == HAL_HSP_BRAM_ARBITRATION_LATENCY_16_CYCLES)    \
   || ((value) == HAL_HSP_BRAM_ARBITRATION_LATENCY_8_CYCLES)  \
   || ((value) == HAL_HSP_BRAM_ARBITRATION_LATENCY_4_CYCLES))

/**
  * @brief Verify the Polling mode value.
  * @param  mode  Polling mode (@ref HAL_HSP_POLLING_ModeTypeDef).
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_POLL_MODE(mode)                   \
  (((mode) == HAL_HSP_POLLING_FOR_ALL_EVENT)     \
   || ((mode) == HAL_HSP_POLLING_FOR_ANY_EVENT))

/**
  * @brief Verify the SNOOP Group.
  * @param  group  Group Indetifier.
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_SNOOP_GROUP(group)         \
  (((group) == HAL_HSP_SNOOP_GROUP_A)     \
   || ((group) == HAL_HSP_SNOOP_GROUP_B))

/**
  * @brief Verify the SNOOP Signal set.
  * @param  signal  Signal set.
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_SNOOP_SIGNAL(signal)                              \
  (((signal) == HAL_HSP_SNOOP_GRPA_TASK_2_1_0)                   \
   || ((signal) == HAL_HSP_SNOOP_GRPA_DMA_CH_2_1_0_IT)           \
   || ((signal) == HAL_HSP_SNOOP_GRPA_TRGIN_BUFF_ADC)            \
   || ((signal) == HAL_HSP_SNOOP_GRPA_TSC_PFCTNB_2_1_0)          \
   || ((signal) == HAL_HSP_SNOOP_GRPA_TSC_CMP_2_1_0)             \
   || ((signal) == HAL_HSP_SNOOP_GRPA_EVTCWKUP_SPEJUMP_SPEWFE)   \
   || ((signal) == HAL_HSP_SNOOP_GRPA_PE_2_1_0)                  \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TASK_5_4_3)                \
   || ((signal) == HAL_HSP_SNOOP_GRPB_PRC_25_24_23)              \
   || ((signal) == HAL_HSP_SNOOP_GRPB_DCMD_CDEG_HDEG)            \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TSC_PFCTNB_5_4_3)          \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TSC_CMP_3)                 \
   || ((signal) == HAL_HSP_SNOOP_GRPB_TSC_PULSE_CALL_IF_IFTRUE)  \
   || ((signal) == HAL_HSP_SNOOP_GRPB_PE_5_4_3))

/**
  * @brief Verify the Critical Event value.
  * @param  events  Critical Events mask.
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_BREAK_CRITICAL_EVENT(events)                          \
  (((events) != HAL_HSP_BREAK_CRITICAL_EVENT_ALL)                    \
   && (STM32_IS_BIT_SET(HAL_HSP_BREAK_CRITICAL_EVENT_ALL, (events))))

/**
  * @brief Verify the Freeze Event value.
  * @param  events  Freeze Events mask.
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_BREAK_FREEZE_EVENT(events)                          \
  (((events) != HAL_HSP_BREAK_FREEZE_EVENT_ALL)                    \
   && (STM32_IS_BIT_SET(HAL_HSP_BREAK_FREEZE_EVENT_ALL, (events))))

/**
  * @brief Verify the Break Output value.
  * @param  id  Break Output id (@ref HAL_HSP_BREAK_OutputTypeDef).
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_BREAK_OUTPUT(id)         \
  (((id) == HAL_HSP_BREAK_OUTPUT_0)     \
   || ((id) == HAL_HSP_BREAK_OUTPUT_1)  \
   || ((id) == HAL_HSP_BREAK_OUTPUT_2)  \
   || ((id) == HAL_HSP_BREAK_OUTPUT_3))

/**
  * @brief Verify the Polling Mode value.
  * @param  mode  Polling mode (@ref HAL_HSP_POLLING_ModeTypeDef).
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_POLLING_MODE(mode)                \
  (((mode) == HAL_HSP_POLLING_FOR_ALL_EVENT)     \
   || ((mode) == HAL_HSP_POLLING_FOR_ANY_EVENT))

/**
  * @brief Verify the SPE Error Interrupts.
  * @param  interrupts  Interrupts mask.
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_IT_ERR_SPE(interrupts)                                \
  (((interrupts) > 0U)                                               \
   && (STM32_IS_BIT_SET(HAL_HSP_IT_ERR_SPE_ALL, (interrupts)) != 0U))

/**
  * @brief Verify the SPE Event Interrupts.
  * @param  interrupts  Interrupts mask.
  * @retval SET    Value is valid.
  * @retval RESET  Value is invalid.
  */
#define IS_HSP_IT_EVT_SPE(interrupts)                                \
  (((interrupts) > 0U)                                               \
   && (STM32_IS_BIT_SET((HAL_HSP_IT_EVT_SPE_ALL | HAL_HSP_IT_EVT_CMD_DIRECT_COMMAND_DONE), (interrupts)) != 0U))


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
static HAL_StatusTypeDef HSP_Reset(const HSP_HandleTypeDef *hhsp);

static void HSP_STREAM_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);
static void HSP_TCU_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);
static void HSP_CMD_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);
static void HSP_SPE_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);
static void HSP_TSC_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr);

static void HSP_STREAM_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);
static void HSP_TRGIN_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);
static void HSP_TSC_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);
static void HSP_SPE_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors);

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HSP_Exported_Functions
  * @{
  */

/** @addtogroup HSP_Exported_Functions_Group1
  * @brief  Initialization and De-Initialization functions.
  *
@verbatim
 ===============================================================================
            ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the HSP peripheral and the associated handle
      (+) DeInitialize the HSP peripheral
      (+) Initialize the HSP MSP (MCU Specific Package)
      (+) DeInitialize the HSP MSP

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the HSP according to the associated handle.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @note   If the selected HSP is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset of the peripheral.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR HSP handle or instance is NULL.
  */
HAL_StatusTypeDef HAL_HSP_Init(HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;
  HAL_HSP_StateTypeDef state;

  /* Check the HSP handle allocation */
  if (hhsp == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  if (hhsp->Instance == NULL)
  {
    hhsp->last_error_codes = HAL_HSP_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  if (hhsp->global_state == HAL_HSP_STATE_FAULT)
  {
    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE(hhsp->Instance));

  /* Init the peripheral */
  if (hhsp->global_state == HAL_HSP_STATE_RESET)
  {
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    /* Register the default callback functions */
    hhsp->EVT_SPE_RunStateCallback = HAL_HSP_EVT_SPE_RunStateCallback;
    hhsp->EVT_SPE_TaskCpltCallback = HAL_HSP_EVT_SPE_TaskCpltCallback;
    hhsp->EVT_SPE_DirectCommandCpltCallback = HAL_HSP_EVT_SPE_DirectCommandCpltCallback;
    hhsp->EVT_SPE_FPUSaturationCallback = HAL_HSP_EVT_SPE_FPUSaturationCallback;
    hhsp->EVT_TSC_TimestampReadyCallback = HAL_HSP_EVT_TSC_TimestampReadyCallback;
    hhsp->EVT_TCU_TaskStartedCallback = HAL_HSP_EVT_TCU_TaskStartedCallback;
    hhsp->EVT_TCU_TaskEndedCallback = HAL_HSP_EVT_TCU_TaskEndedCallback;
    hhsp->EVT_TCU_TaskOverlapCallback = HAL_HSP_EVT_TCU_TaskOverlapCallback;
    hhsp->EVT_STREAM_BufferEmptyCallback = HAL_HSP_EVT_STREAM_BufferEmptyCallback;
    hhsp->EVT_STREAM_BufferFullCallback = HAL_HSP_EVT_STREAM_BufferFullCallback;
    hhsp->FWEVT_ProcessingEventCallback = HAL_HSP_FWEVT_ProcessingEventCallback;
    hhsp->ErrorCallback = HAL_HSP_ErrorCallback;

    if (NULL == hhsp->MspInitCallback)
    {
      hhsp->MspInitCallback = HAL_HSP_MspInit;
    }

    if (NULL == hhsp->MspDeInitCallback)
    {
      hhsp->MspDeInitCallback = HAL_HSP_MspDeInit;
    }

    /* Init the low level hardware */
    hhsp->MspInitCallback(hhsp);
#else
    /* Init the low level hardware */
    HAL_HSP_MspInit(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }

  /* Reset the last error codes */
  hhsp->last_error_codes = HAL_HSP_ERROR_NONE;
  hhsp->boot_error_code = 0U;
  hhsp->last_msgbox_error_code  = 0U;

  /* Reset pointer of HSP Performance Counter */
  hhsp->p_perf_counter = NULL;

  /* Reset CNN Safe mode */
  hhsp->backup_enabled_itfs = 0U;
  hhsp->backup_enabled_events = 0U;
  hhsp->backup_event_its = 0U;
  hhsp->backup_pfctevt_its = 0U;

  /* Reset Sub-Routine for IRQ Handlers */
  hhsp->stream_handler = NULL;
  hhsp->tcu_handler = NULL;
  hhsp->spe_handler = NULL;
  hhsp->tsc_handler = NULL;
  hhsp->cmd_handler = NULL;
  hhsp->stream_err_handler = NULL;
  hhsp->trgin_err_handler = NULL;
  hhsp->tsc_err_handler = NULL;
  hhsp->spe_err_handler = NULL;
  hhsp->fwevt_handler = NULL;

  /* Check Register Lock Status and set the Handle State as expected */
  p_hspx = HSP_GET_INSTANCE(hhsp);
  state = hhsp->global_state;
  if (STM32_IS_BIT_SET(p_hspx->CR, HSP_CR_REGLCK) || (state == HAL_HSP_STATE_RUNNING))
  {
    hhsp->global_state = HAL_HSP_STATE_RUNNING;
  }
  else
  {
    hhsp->global_state = HAL_HSP_STATE_INIT;

    /* Initialize CRAM & DRAM free sizes */
    hhsp->cram_free_size_in_word = HSP_GET_CRAM_SIZE_IN_WORD(hhsp->Instance);
    hhsp->dram_free_size_in_word = HSP_GET_DRAM_SIZE_IN_WORD(hhsp->Instance);

    /* Reset Plugin address */
    hhsp->cram_address_for_plugin = 0U;
  }

  return HAL_OK;
}

/**
  * @brief  DeInitialize the HSP peripheral.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @note  HAL_HSP_DeInit does not reset all registers.
  *        The Application must call RCC API to force the reset of all registers
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR wrong parameter.
  */
HAL_StatusTypeDef HAL_HSP_DeInit(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  /* Check the HSP handle allocation */
  if (hhsp == NULL)
  {
    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE(hhsp->Instance));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Disable all the Events, but if HSP Registers are locked, the disabling will failed */
  STM32_CLEAR_BIT(p_hspx->EVTENR, HSP_EVTENR_EVTEN_Msk);

  /* Disable all Interfaces, but if HSP Registers are locked, the disabling will failed */
  /* STM32_WRITE_REG allows to set the DCMDDIS bit and clear all others */
  STM32_WRITE_REG(p_hspx->ITFENR, HSP_ITFENR_DCMDDIS);

  /* Disable ITs & Clear Flags. */
  STM32_CLEAR_BIT(p_hspx->PFCTEVT_IER, HSP_PFCTEVT_IER_PFCTIE_Msk); /* Disable all PFCT Event Interrupts */
  STM32_WRITE_REG(p_hspx->PFCTEVT_ICR, HSP_PFCTEVT_ICR_PFCTC_Msk);  /* Clear all PFCT Event Flags        */

  STM32_CLEAR_BIT(p_hspx->EVT_IER, HSP_IT_EVT_ALL);  /* Disable all Event Interrupts */
  STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_IT_EVT_ALL);  /* Clear all Event Flags        */

  STM32_CLEAR_BIT(p_hspx->ERR_IER, HSP_IT_ERR_ALL);  /* Disable all Error Interrupts */
  STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_IT_ERR_ALL);  /* Clear all Error Flags        */

  /* Request the Reset of SPE - A HSP HW Reset must be done after */
  (void)HSP_Reset(hhsp);

#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
  /* Register the default callback functions */
  if (hhsp->MspDeInitCallback == NULL)
  {
    /* DeInit Callback not initialized as expected then force it to default MspDeInit */
    hhsp->MspDeInitCallback = HAL_HSP_MspDeInit;
  }

  /* DeInit the low level hardware */
  hhsp->MspDeInitCallback(hhsp);
#else
  /* DeInit the low level hardware */
  HAL_HSP_MspDeInit(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS == 1 */

  /* Reset error codes */
  hhsp->last_error_codes = HAL_HSP_ERROR_NONE;
  hhsp->boot_error_code = 0U;
  hhsp->last_msgbox_error_code = 0U;

  /* Reset CRAM & DRAM data */
  hhsp->cram_free_size_in_word = 0U;
  hhsp->dram_free_size_in_word = 0U;
  hhsp->cram_address_for_plugin = 0U;

  /* Reset HSP state */
  hhsp->global_state = HAL_HSP_STATE_RESET;

  return HAL_OK;
}

/**
  * @brief  Initialize the HSP MSP.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval None
  */
__weak void HAL_HSP_MspInit(HSP_HandleTypeDef *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);

  /* NOTE : This function should not be modified, when the callback is needed,
          the HAL_HSP_MspInit could be implemented in the user file
  */
}

/**
  * @brief  DeInitialize the HSP MSP.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval None
  */
__weak void HAL_HSP_MspDeInit(HSP_HandleTypeDef *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);

  /* NOTE : This function should not be modified, when the callback is needed,
          the HAL_HSP_MspDeInit could be implemented in the user file
  */
}

/* Firmware/Plugin functions **************************************************/
/**
  * @brief Load HSP Firmware in CRAM & DRAM.
  * @param hhsp             Pointer to a @ref HSP_HandleTypeDef.
  * @param p_cram_bin       Pointer to the CRAM Firmware binary.
  * @param cram_size_bytes  Size in bytes of FW CRAM.
  * @param p_dram_bin       Pointer to the DRAM Firmware binary.
  * @param dram_size_bytes  Size in bytes of FW DRAM.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  * @retval HAL_ERROR wrong parameter.
  */
HAL_StatusTypeDef HAL_HSP_LoadFirmware(HSP_HandleTypeDef *hhsp,
                                       const uint8_t *p_cram_bin, uint32_t cram_size_bytes,
                                       const uint8_t *p_dram_bin, uint32_t dram_size_bytes)
{
  ASSERT_DBG_PARAM(hhsp != NULL);

  if ((p_cram_bin == NULL) || (p_dram_bin == NULL))
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM((cram_size_bytes > 0UL));
  ASSERT_DBG_PARAM((cram_size_bytes < (hhsp->cram_free_size_in_word * 4U)));
  ASSERT_DBG_PARAM((dram_size_bytes > 0UL));
  ASSERT_DBG_PARAM((dram_size_bytes < (hhsp->dram_free_size_in_word * 4U)));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, HAL_HSP_STATE_INIT);

  /* Write data in HSP CRAM --------------------------------------------------*/
  volatile uint8_t *tmpAddr = (uint8_t *)HSP_GET_CRAM_BASE_ADDRESS(hhsp->Instance);

  for (uint32_t i = 0; i < cram_size_bytes; i++)
  {
    *tmpAddr = p_cram_bin[i];
    tmpAddr++;
  }

  /* Back to the last CRAM data */
  uint32_t *tmpAddr32 = ((uint32_t *)(uint32_t)tmpAddr);
  tmpAddr32--;

  /* Check if End FW Pattern is loaded */
  if (*tmpAddr32 != HSP_FW_END_PATTERN)
  {
    /* No "End" Pattern found. Then store the next cram address to load plugin */
    tmpAddr32++;
    hhsp->cram_free_size_in_word -= (cram_size_bytes / 4UL);
  }
  else
  {
    /* Store the cram address of the pattern which is override when loading the first plugin */
    hhsp->cram_free_size_in_word -= ((cram_size_bytes / 4UL) - 1UL); /* -1 to keep a word for End Pattern */
  }

  hhsp->cram_address_for_plugin = (uint32_t)tmpAddr32;

  /* Write data in HSP DRAM --------------------------------------------------*/
  tmpAddr = (uint8_t *)HSP_GET_DRAM_BASE_ADDRESS(hhsp->Instance);
  for (uint32_t i = 0; i < dram_size_bytes; i++)
  {
    *tmpAddr = p_dram_bin[i];
    tmpAddr++;
  }

  /* Compute the size of free DRAM */
  hhsp->dram_free_size_in_word -= (dram_size_bytes / 4UL);

  hhsp->global_state = HAL_HSP_STATE_READY_TO_BOOT;

  return HAL_OK;
}

/**
  * @brief Load HSP Plugin in CRAM.
  * @param hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param p_plugin_bin  Pointer to the CRAM FW binary.
  * @param size_bytes    Number of bytes to load in CRAM.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Array pointer is NULL.
  * @retval HAL_ERROR wrong parameter.
  */
HAL_StatusTypeDef HAL_HSP_LoadPlugin(HSP_HandleTypeDef *hhsp, const uint8_t *p_plugin_bin, uint32_t size_bytes)
{
  ASSERT_DBG_PARAM(hhsp != NULL);

  if (p_plugin_bin == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM((size_bytes > 0UL));
  ASSERT_DBG_PARAM((size_bytes < (hhsp->cram_free_size_in_word * 4U)));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, HAL_HSP_STATE_READY_TO_BOOT);

  /* Write data in HSP CRAM */
  volatile uint8_t *tmpAddr = (uint8_t *)(hhsp->cram_address_for_plugin);

  for (uint32_t i = 0; i < size_bytes; i++)
  {
    *tmpAddr = p_plugin_bin[i];
    tmpAddr++;
  }

  /* Compute the size of free CRAM */
  hhsp->cram_free_size_in_word -= (size_bytes / 4UL);

  /* Store the free CRAM address to load the next plugin */
  hhsp->cram_address_for_plugin = (uint32_t)tmpAddr;

  return HAL_OK;
}

/* Boot functions *************************************************************/
/**
  * @brief Boot the HSP.
  * @param hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param p_config    Pointer to Boot configuration.
  * @param timeout_ms  Timeout in millisecond
  * @retval HAL_OK             Operation Completed successfully.
  * @retval HAL_INVALID_PARAM  Boot Config pointer is NULL.
  * @retval HAL_ERROR          HSP Boot Failure.
  */
HAL_StatusTypeDef HAL_HSP_Boot(HSP_HandleTypeDef *hhsp, const HAL_HSP_Boot_ConfigTypeDef *p_config,
                               uint32_t timeout_ms)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  /* Check the parameters */
  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_PERF_MONITOR_STATE(p_config->perf_mon));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, HAL_HSP_STATE_READY_TO_BOOT);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Close the FW */
  *((__IO uint32_t *)(hhsp->cram_address_for_plugin)) = HSP_FW_END_PATTERN;
  hhsp->dram_free_size_in_word--;

  /* Boot the HSP */
  STM32_SET_BIT(p_hspx->CR, HSP_CR_BOOTEN);

  /* Get timeout */
  uint32_t tickstart = HAL_GetTick();

  while (STM32_READ_BIT(p_hspx->CR, HSP_CR_BSTAT_Msk) != p_config->boot_success_code)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      /* New check to avoid false timeout detection in case of preemption */
      uint32_t bstat = STM32_READ_BIT(p_hspx->CR, HSP_CR_BSTAT_Msk);
      if (bstat != p_config->boot_success_code)
      {
        hhsp->last_error_codes |= HAL_HSP_ERROR_BOOT;
        hhsp->boot_error_code = bstat;
        hhsp->global_state = HAL_HSP_STATE_FAULT;
        return HAL_ERROR;
      }
    }
  }

  /* The Boot is OK, but before to transmit the BRAM address and the performance monitor state */
  /* to finalize the boot, we put the handle state to READY to allow the call of HAL_HSP_MSGBOX_SendCommand */
  hhsp->global_state = HAL_HSP_STATE_RUNNING;

  /* FW need to know this address at boot */
  uint32_t bramab_address = HSP_GET_BRAMAB_BASE_ADDRESS((uint32_t)(hhsp->Instance));
  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_0, bramab_address);
  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_1, (uint32_t)p_config->perf_mon);

  if (HAL_HSP_MSGBOX_SendCommand(hhsp, p_config->boot_cmd_id, timeout_ms) != HAL_OK)
  {
    hhsp->global_state = HAL_HSP_STATE_FAULT;
    return HAL_ERROR;
  }

  /* Retrieve the Performance Cycle Counter */
  hhsp->p_perf_counter = (((uint32_t *)bramab_address) + p_config->perf_counter_offset);

  /* Enable all event generators: CDEG, CSEG */
  STM32_SET_BIT(p_hspx->ITFENR, (HSP_ITFENR_CSEGEN | HSP_ITFENR_CDEGEN));

  /* HSP is ready to be configured, record processing list or process direct command */
  hhsp->global_state = HAL_HSP_STATE_RUNNING;

  /* Write Protection of CRAM & DRAM from any CPU access to prevent any corruption */
  /* CRAM & DRAM become read-only access */
  STM32_MODIFY_REG(p_hspx->CR, HSP_CR_CDRLCK_Msk, HSP_CR_CDRLCK_0);

  return HAL_OK;
}

/* Capabilities ***************************************************************/
/**
  * @brief  Retrieve the Firmware versions (ROM & RAM).
  * @param  hhsp       Pointer to a @ref HSP_HandleTypeDef.
  * @note  The call of this function must be done after booting the HSP
  * @return Return the FWVERR register value
  */
uint32_t HAL_HSP_GetFirmwareVersion(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return STM32_READ_REG(p_hspx->FWVERR);
}

/**
  * @brief Get the HSP capabilities.
  * @param hhsp            Pointer to a @ref HSP_HandleTypeDef.
  * @param p_capabilities  Pointer to capabilities structure.
  * @retval HAL_OK     Operation Completed successfully.
  * @retval HAL_ERROR  Invalid parameter.
  */
HAL_StatusTypeDef HAL_HSP_GetCapabilities(HSP_HandleTypeDef *hhsp, HAL_HSP_CapabilitiesTypeDef *p_capabilities)
{
  ASSERT_DBG_PARAM(hhsp != NULL);

  /* Check the parameters */
  if (p_capabilities == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;
    return HAL_ERROR;
  }

  switch ((uint32_t)hhsp->Instance)
  {
    case (uint32_t)HSP1_BASE:
      p_capabilities->bramab_base_address = HSP1_BRAMAB_BASE;
      p_capabilities->bramab_size_byte = HSP1_BRAMAB_SIZE;
      p_capabilities->brama_base_address = HSP1_BRAMA_BASE;
      p_capabilities->bramb_base_address = HSP1_BRAMB_BASE;
      break;
    default:
      p_capabilities->bramab_base_address = 0UL;
      p_capabilities->bramab_size_byte = 0UL;
      p_capabilities->brama_base_address = 0UL;
      p_capabilities->bramb_base_address = 0UL;
      break;
  }

  return HAL_OK;
}


/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group2
  *
@verbatim
  ==============================================================================
                  ##### HSP Processing List configuration #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Start configuration sequence of a processing list
    (+) End configuration sequence of a processing list
    (+) Trig a processing list
    (+) Reset a processing list

@endverbatim
  * @{
  */
/**
  * @brief  Wait the end of a direct command.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  timeout_ms  Timeout in millisecond.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_TIMEOUT Timeout occurred.
  */
HAL_StatusTypeDef HAL_HSP_DIRECT_WaitEndOfCommand(const HSP_HandleTypeDef *hhsp, uint32_t timeout_ms)
{
  const HSP_TypeDef *p_hspx;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hhsp != NULL);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Check if timeout is disabled (set to infinite wait) */
  if (timeout_ms != HAL_MAX_DELAY)
  {
    /* Get tick count */
    tickstart = HAL_GetTick();

    do
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0UL))
      {
        return HAL_TIMEOUT;
      }
    } while (STM32_READ_BIT(p_hspx->DCMDSR, HSP_DCMDSR_DCBSY) != 0U);
  }
  else
  {
    while (STM32_READ_BIT(p_hspx->DCMDSR, HSP_DCMDSR_DCBSY) != 0U)
    {}
  }

  return HAL_OK;
}

/**
  * @brief  Send a command by msgbox.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  cmd_id      Command ID
  * @param  timeout_ms  Timeout in millisecond.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Failed to send the command.
  * @retval HAL_BUSY  Send of Command is pending
  * @retval HAL_TIMEOUT Timeout occurred.
  */
HAL_StatusTypeDef HAL_HSP_MSGBOX_SendCommand(HSP_HandleTypeDef *hhsp, uint32_t cmd_id, uint32_t timeout_ms)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Read the HSP_C2HSEM bit via the CPU to HSP message control register (HSP_C2HSEMR)           */
  /* Wait until HSP_C2HSEM = 0. It indicates that the previous message has been read by the HSP, */
  /* and the content of C2HDATA can be overwrite. */
  if (STM32_READ_BIT(p_hspx->C2HSEMR, HSP_C2HSEMR_C2HSEM) == HSP_C2HSEMR_C2HSEM)
  {
    return HAL_BUSY;
  }

  /* Write command in mailbox */
  STM32_WRITE_REG(p_hspx->C2HMSGDR, cmd_id);
  STM32_SET_BIT(p_hspx->C2HSEMR, HSP_C2HSEMR_C2HSEM);

  /* Wait the answer of SPE */
  uint32_t tickstart = HAL_GetTick();

  while (STM32_READ_BIT(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM) == 0U)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      return HAL_TIMEOUT;
    }
  }

  /* Read the SPE answer via HSP_H2CMSGDR register (HSP to CPU message data register). */
  uint32_t status = STM32_READ_REG(p_hspx->H2CMSGDR);

  /* Indicate to the HSP that the message is read */
  /* When CPU writes the bit H2CSEM to 1, it clears it to 0 ! */
  STM32_WRITE_REG(p_hspx->H2CSEMR, HSP_H2CSEMR_H2CSEM);

  /* Even if ITs are not enabled, the driver must clear the folowwings flags: */
  /*  - HSP_EVT_ISR_H2CMRDYF  indicating a message is available for the CPU   */
  /*  - HSP_EVT_ICR_C2HMFREEF indicating the MSGB is free for CPU to SPE      */
  STM32_WRITE_REG(p_hspx->EVT_ICR, (HSP_EVT_ICR_H2CMRDYC | HSP_EVT_ICR_C2HMFREEC));

  /* Check the HSP status */
  if (status != 0U)
  {
    hhsp->last_msgbox_error_code = status;
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group3_2
  * @{
  */
/* STREAM Interface ----------------------------------------------------------*/
/**
  * @brief  Configure a STREAM instance.
  * @param  hhsp       Pointer to a @ref HSP_HandleTypeDef.
  * @param  stream_id  STREAM Buffer id.
  * @param  p_config   Pointer to a @ref HAL_HSP_STREAM_Buffer_ConfigTypeDef.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Config pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_STREAM_SetConfig(HSP_HandleTypeDef *hhsp, HAL_HSP_STREAM_BufferTypeDef stream_id,
                                           const HAL_HSP_STREAM_Buffer_ConfigTypeDef *p_config)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER(stream_id));
  ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER_DIRECTION(p_config->direction));
  ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER_SYNC_STATE(p_config->sync_state));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (p_config->direction == HAL_HSP_STREAM_BUFFER_DIRECTION_RX)
  {
    STM32_CLEAR_BIT(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_BUFF0DIR << (uint32_t)(stream_id)));
  }
  else
  {
    STM32_SET_BIT(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_BUFF0DIR << (uint32_t)(stream_id)));
  }

  if (p_config->sync_state == HAL_HSP_STREAM_BUFFER_SYNC_DISABLE)
  {
    STM32_CLEAR_BIT(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_COMB0 << (uint32_t)(stream_id)));
  }
  else
  {
    STM32_SET_BIT(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_COMB0 << (uint32_t)(stream_id)));
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of a STREAM instance.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  stream_id  STREAM Buffer id.
  * @param  p_config  Pointer to a @ref HAL_HSP_STREAM_Buffer_ConfigTypeDef.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Config pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_STREAM_GetConfig(HSP_HandleTypeDef *hhsp, HAL_HSP_STREAM_BufferTypeDef stream_id,
                                           HAL_HSP_STREAM_Buffer_ConfigTypeDef *p_config)
{
  const HSP_TypeDef *p_hspx;
  uint32_t value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER(stream_id));

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get the Direction */
  value = STM32_READ_BIT(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_BUFF0DIR << (uint32_t)(stream_id)));
  if (value == 0U)
  {
    p_config->direction = HAL_HSP_STREAM_BUFFER_DIRECTION_RX;
  }
  else
  {
    p_config->direction = HAL_HSP_STREAM_BUFFER_DIRECTION_TX;
  }

  /* Get the Sync State */
  value = STM32_READ_BIT(p_hspx->BUFFCFGR, (HSP_BUFFCFGR_COMB0 << (uint32_t)(stream_id)));
  if (value == 0U)
  {
    p_config->sync_state = HAL_HSP_STREAM_BUFFER_SYNC_DISABLE;
  }
  else
  {
    p_config->sync_state = HAL_HSP_STREAM_BUFFER_SYNC_ENABLE;
  }

  return HAL_OK;
}

/**
  * @brief  Enable the Integer to Float conversion for all STREAM interfaces.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_STREAM_EnableIntToFloat(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->BUFFCFGR, HSP_BUFFCFGR_I2FEN);

  return HAL_OK;
}

/**
  * @brief  Disable the Integer to Float conversion for all STREAM interfaces.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_STREAM_DisableIntToFloat(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->BUFFCFGR, HSP_BUFFCFGR_I2FEN);

  return HAL_OK;
}

/**
  * @brief  Return the Integer to Float conversion status.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_HSP_STREAM_INT_TO_FLOAT_DISABLED Conversion is disabled.
  * @retval HAL_HSP_STREAM_INT_TO_FLOAT_ENABLED  Conversion is enabled.
  */
HAL_HSP_STREAM_IntToFloat_StatusTypeDef HAL_HSP_STREAM_IsEnabledIntToFloat(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->BUFFCFGR, HSP_BUFFCFGR_I2FEN);
  return ((status == 0U) ? HAL_HSP_STREAM_INT_TO_FLOAT_DISABLED : HAL_HSP_STREAM_INT_TO_FLOAT_ENABLED);
}

/**
  * @brief  Start all the STREAM Buffers.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  evt_interrupts  mask of event interrupts
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_EVT_STREAM0_READY
  *             @arg HAL_HSP_IT_EVT_STREAM1_READY
  *             @arg HAL_HSP_IT_EVT_STREAM2_READY
  *             @arg HAL_HSP_IT_EVT_STREAM3_READY
  *             @arg HAL_HSP_IT_EVT_STREAM_ALL
  * @param  err_interrupts  mask of error interrupts
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_ERR_STREAM0_OVR
  *             @arg HAL_HSP_IT_ERR_STREAM1_OVR
  *             @arg HAL_HSP_IT_ERR_STREAM2_OVR
  *             @arg HAL_HSP_IT_ERR_STREAM3_OVR
  *             @arg HAL_HSP_IT_ERR_STREAM_ALL
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_STREAM_Start(HSP_HandleTypeDef *hhsp,
                                       uint32_t evt_interrupts, uint32_t err_interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->ITFENR, HSP_ITFENR_STREAMEN);

  if (evt_interrupts != 0U)
  {
    hhsp->stream_handler = HSP_STREAM_Handler;
    STM32_SET_BIT(p_hspx->EVT_IER, evt_interrupts);
  }

  if (err_interrupts != 0U)
  {
    hhsp->stream_err_handler = HSP_STREAM_Error_Handler;
    STM32_SET_BIT(p_hspx->ERR_IER, err_interrupts);
  }

  return HAL_OK;
}

/**
  * @brief  Disable all the STREAM Buffer.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_STREAM_Stop(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ITFENR, HSP_ITFENR_STREAMEN);
  STM32_CLEAR_BIT(p_hspx->EVT_IER, HAL_HSP_IT_EVT_STREAM_ALL);
  STM32_CLEAR_BIT(p_hspx->ERR_IER, HAL_HSP_IT_ERR_STREAM_ALL);

  hhsp->stream_handler = NULL;
  hhsp->stream_err_handler = NULL;

  return HAL_OK;
}

/**
  * @brief  Get a STREAM Buffer address.
  * @param  hhsp       Pointer to a HSP_HandleTypeDef.
  * @param  stream_id  Stream buffer id.
  * @retval Stream Buffer Address
  */
volatile uint32_t *HAL_HSP_STREAM_GetBufferAddress(const HSP_HandleTypeDef *hhsp,
                                                   HAL_HSP_STREAM_BufferTypeDef stream_id)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_STREAM_BUFFER(stream_id));

  return (volatile uint32_t *) & (hhsp->Instance->BUFFDR[(uint32_t)stream_id]);
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group3_3 HSP TRGIN Interface
  * @{
  */
/* TRGIN Interface -----------------------------------------------------------*/
/**
  * @brief  Configure a TRGIN instance.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  trgin_ids        TRGIN instance id
  *         This parameter can be a combination of following values:
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
  * @param  p_config  Pointer to a @ref HAL_HSP_TRGIN_ConfigTypeDef.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Config pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_TRGIN_SetConfig(HSP_HandleTypeDef *hhsp, uint32_t trgin_ids,
                                          const HAL_HSP_TRGIN_ConfigTypeDef *p_config)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_TRGIN_COMBINATION(trgin_ids));
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_SOURCE(p_config->source));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* configure the polarity */
  uint32_t trgins_mask = (trgin_ids >> HSP_ITFENR_TRGI0EN_Pos);
  uint32_t trgins_pol_mask = (trgins_mask << HSP_TRGINCFGR_TRG0POL_Pos);
  if (p_config->polarity == HAL_HSP_TRGIN_POLARITY_RISING)
  {
    STM32_CLEAR_BIT(p_hspx->TRGINCFGR, trgins_pol_mask);
  }
  else
  {
    STM32_SET_BIT(p_hspx->TRGINCFGR, trgins_pol_mask);
  }

  /* Check if TRGIN 0 to 3 must be configured */
  uint32_t trgin_mask = (trgins_mask & 0xFU);
  if (trgin_mask != 0U)
  {
    uint32_t reg_value = 0UL;
    uint32_t bitfiled_pos = 0UL;
    uint32_t reg_mask = 0UL;
    if ((trgin_mask & 0x1U) != 0U)
    {
      reg_mask = HSP_TRGINSELR0_TRG0SEL_Msk;
      reg_value = (uint32_t)p_config->source;
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x2U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x4U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x8U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    STM32_MODIFY_REG(p_hspx->TRGINSELR0, reg_mask, reg_value);
  }

  /* Check if TRGIN 4 to 7 must be configure */
  trgin_mask = (trgins_mask & 0xF0U) >> 4U;
  if (trgin_mask != 0U)
  {
    uint32_t reg_value = 0UL;
    uint32_t bitfiled_pos = 0UL;
    uint32_t reg_mask = 0UL;
    if ((trgin_mask & 0x1U) != 0U)
    {
      reg_mask = HSP_TRGINSELR0_TRG0SEL_Msk;
      reg_value = (uint32_t)p_config->source;
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x2U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x4U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x8U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    STM32_MODIFY_REG(p_hspx->TRGINSELR1, reg_mask, reg_value);
  }

  /* Check if TRGIN 8 to 9 must be configure */
  trgin_mask = (trgins_mask & 0xF00U) >> 8U;
  if (trgin_mask != 0U)
  {
    uint32_t reg_value = 0UL;
    uint32_t bitfiled_pos = 0UL;
    uint32_t reg_mask = 0UL;
    if ((trgin_mask & 0x1U) != 0U)
    {
      reg_mask = HSP_TRGINSELR0_TRG0SEL_Msk;
      reg_value = (uint32_t)p_config->source;
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x2U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x4U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    bitfiled_pos += HSP_REG_TRGINSEL_SELECT_FIELD_SIZE;
    if ((trgin_mask & 0x8U) != 0U)
    {
      reg_mask |= HSP_TRGINSELR0_TRG0SEL_Msk << bitfiled_pos;
      reg_value |= ((uint32_t)p_config->source << bitfiled_pos);
    }

    STM32_MODIFY_REG(p_hspx->TRGINSELR2, reg_mask, reg_value);
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of a TRGIN instance.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  trgin_id  TRGIN instance id.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_TRGIN_1
  *             @arg HAL_HSP_TRGIN_2
  *             @arg HAL_HSP_TRGIN_3
  *             @arg HAL_HSP_TRGIN_4
  *             @arg HAL_HSP_TRGIN_5
  *             @arg HAL_HSP_TRGIN_6
  *             @arg HAL_HSP_TRGIN_7
  *             @arg HAL_HSP_TRGIN_8
  *             @arg HAL_HSP_TRGIN_9
  * @param  p_config  Pointer to a @ref HAL_HSP_TRGIN_ConfigTypeDef.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Config pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_TRGIN_GetConfig(HSP_HandleTypeDef *hhsp, uint32_t trgin_id,
                                          HAL_HSP_TRGIN_ConfigTypeDef *p_config)
{
  const HSP_TypeDef *p_hspx;
  uint32_t reg_idx;
  uint32_t reg_pos;
  uint32_t bitfield_idx;
  uint32_t reg_mask;
  uint32_t reg_value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN(trgin_id));

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get the polarity */
  uint32_t trgin_mask = (trgin_id >> HSP_ITFENR_TRGI0EN_Pos);

  if (STM32_READ_BIT(p_hspx->TRGINCFGR, trgin_mask) == 0U)
  {
    p_config->polarity = HAL_HSP_TRGIN_POLARITY_RISING;
  }
  else
  {
    p_config->polarity = HAL_HSP_TRGIN_POLARITY_FALLING;
  }

  /* Get the trigger source */
  uint32_t id = STM32_POSITION_VAL(trgin_mask);
  reg_idx = ((uint32_t)id) / HSP_REG_TRGINSEL_CFG_NBR;
  bitfield_idx = ((uint32_t)id) % HSP_REG_TRGINSEL_CFG_NBR;
  reg_pos = HSP_TRGINSELR0_TRG0SEL_Pos + ((uint32_t)bitfield_idx * HSP_REG_TRGINSEL_SELECT_FIELD_SIZE);
  reg_mask = (HSP_TRGINSELR0_TRG0SEL_Msk << reg_pos);

  switch (reg_idx)
  {
    case 0:
    {
      reg_value = STM32_READ_BIT(p_hspx->TRGINSELR0, reg_mask) >> reg_pos;
      break;
    }
    case 1:
    {
      reg_value = STM32_READ_BIT(p_hspx->TRGINSELR1, reg_mask) >> reg_pos;
      break;
    }
    case 2:
    {
      reg_value = STM32_READ_BIT(p_hspx->TRGINSELR2, reg_mask) >> reg_pos;
      break;
    }
    default:
    {
      return HAL_ERROR;
      break;
    }
  }

  p_config->source = (HAL_HSP_TRGIN_SourceTypeDef)reg_value;

  return HAL_OK;
}

/**
  * @brief  Enable a TRGIN instance.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  trgin_ids    TRGIN instance id.
  *         This parameter can be a combination of following values:
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
HAL_StatusTypeDef HAL_HSP_TRGIN_Enable(HSP_HandleTypeDef *hhsp, uint32_t trgin_ids)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_COMBINATION(trgin_ids));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->ITFENR, trgin_ids);

  return HAL_OK;
}

/**
  * @brief  Disable a TRGIN instance.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  trgin_ids Set of TRGIN instance
  *         This parameter can be a combination of following values:
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
HAL_StatusTypeDef HAL_HSP_TRGIN_Disable(HSP_HandleTypeDef *hhsp, uint32_t trgin_ids)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_COMBINATION(trgin_ids));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ITFENR, trgin_ids);

  return HAL_OK;
}

/**
  * @brief  Check if the TRGIN x Interface is enabled.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  trgin_id  TRGIN instance id.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_TRGIN_1
  *             @arg HAL_HSP_TRGIN_2
  *             @arg HAL_HSP_TRGIN_3
  *             @arg HAL_HSP_TRGIN_4
  *             @arg HAL_HSP_TRGIN_5
  *             @arg HAL_HSP_TRGIN_6
  *             @arg HAL_HSP_TRGIN_7
  *             @arg HAL_HSP_TRGIN_8
  *             @arg HAL_HSP_TRGIN_9
  * @retval HAL_HSP_TRGIN_DISABLED  The TRGIN instance is disabled
  * @retval HAL_HSP_TRGIN_ENABLED   The TRGIN instance is enabled
  */
HAL_HSP_TRGIN_StatusTypeDef HAL_HSP_TRGIN_IsEnabled(const HSP_HandleTypeDef *hhsp, uint32_t trgin_id)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_TRGIN(trgin_id));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->ITFENR, trgin_id);

  return ((status == 0U) ? HAL_HSP_TRGIN_DISABLED : HAL_HSP_TRGIN_ENABLED);
}

/**
  * @brief  Enable TRGIN Error Interrupts.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Mask of TRGIN Error Interrupts
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_ERR_TRGIN_OVR
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TRGIN_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_IT_ERR(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (interrupts != HAL_HSP_IT_NONE)
  {
    hhsp->trgin_err_handler = HSP_TRGIN_Error_Handler;
    STM32_SET_BIT(p_hspx->ERR_IER, interrupts);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the TRGIN Error Interrupts.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Mask of TRGIN Error Interrupts
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_ERR_TRGIN_OVR
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TRGIN_DisableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_IT_ERR(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ERR_IER, interrupts);
  if (STM32_READ_BIT(p_hspx->ERR_IER, HAL_HSP_IT_ERR_TRGIN_ALL) == 0U)
  {
    hhsp->trgin_err_handler = NULL;
  }

  return HAL_OK;
}

/**
  * @brief  Check whether or not the specified HSP TRGIN Error interrupt is set.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Mask of TRGIN Error Interrupts
  *         This parameter can be one the following values:
  *             @arg HAL_HSP_IT_ERR_TRGIN_OVR
  * @retval The state of HSP interrupt (0 or 1)
  */
uint32_t HAL_HSP_TRGIN_IsEnabledIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_TRGIN_IT_ERR(interrupts));

  return (((STM32_READ_BIT(((HSP_TypeDef *)(uint32_t)(hhsp->Instance))->ERR_IER, interrupts) != 0U)) ? 1U : 0U);
}

/** @brief  Retrieve the TRGIN Overrun status.
  * @param  hhsp specifies the HSP Handle.
  * @note  Use the HAL_HSP_TRGIN_<x> defines to check the overrun status of each TRGIN.
  * @retval Overrun status of all TRGIN
  */
uint32_t HAL_HSP_TRGIN_GetOverrun(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return STM32_READ_BIT(p_hspx->ERRINFR, HSP_ERRINFR_TRGIERR_Msk);
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group3_4 HSP Event Common management
  * @{
  */
/* Event Management ----------------------------------------------------------*/
/**
  * @brief  Configure an Event in the Processing Request Controller.
  * @param  hhsp       Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_config   Pointer to a @ref HAL_HSP_EVENT_ConfigTypeDef.
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_ERROR  Pointer of configuration is NULL.
  */
HAL_StatusTypeDef HAL_HSP_EVENT_SetConfig(HSP_HandleTypeDef *hhsp,
                                          const HAL_HSP_EVENT_ConfigTypeDef *p_config)
{
  HSP_TypeDef *p_hspx;
  uint32_t event_id;
  uint32_t reg_idx;
  uint32_t bitfield_idx;
  uint32_t reg_pos;
  uint32_t reg_mask;
  uint32_t reg_value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_EVENT_SOURCE(p_config->source));
  ASSERT_DBG_PARAM(IS_HSP_TCU(p_config->sync.tcu));
  ASSERT_DBG_PARAM(IS_HSP_EVENT_SYNC_STATE(p_config->sync.state));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  event_id = ((uint32_t)p_config->source >> HAL_HSP_EVENT_PRIO_POS);
  reg_idx = ((event_id - 1UL) / HSP_REG_EVTSRC_CFG_NBR);
  bitfield_idx = ((event_id - 1UL) % HSP_REG_EVTSRC_CFG_NBR);

  reg_pos = HSP_EVTSRC0R_EVT1SRC_Pos + (bitfield_idx * HSP_REG_EVTSRC_FIELD_SIZE);
  reg_mask = (HSP_EVTSRC0R_EVT1SRC_Msk << reg_pos);
  reg_value = ((((uint32_t)p_config->source) & HAL_HSP_EVENT_SOURCE_MSK) >> HAL_HSP_EVENT_SOURCE_POS) << reg_pos;

  /* Update Event source register */
  switch (reg_idx)
  {
    case 0:
      STM32_MODIFY_REG(p_hspx->EVTSRC0R, reg_mask, reg_value);
      break;
    case 1:
      STM32_MODIFY_REG(p_hspx->EVTSRC1R, reg_mask, reg_value);
      break;
    case 2:
      STM32_MODIFY_REG(p_hspx->EVTSRC2R, reg_mask, reg_value);
      break;
    default:
      return HAL_ERROR;
      break;
  }

  /* Update Event synchronisation register */
  reg_mask = (HSP_ESYNC0SRCR_EV1SSRC_Msk << reg_pos);
  reg_value = ((((uint32_t)p_config->sync.tcu) & HAL_HSP_EVENT_SOURCE_MSK) >> HAL_HSP_EVENT_SOURCE_POS) << reg_pos;
  switch (reg_idx)
  {
    case 0:
      STM32_MODIFY_REG(p_hspx->ESYNC0SRCR, reg_mask, reg_value);
      break;
    case 1:
      STM32_MODIFY_REG(p_hspx->ESYNC1SRCR, reg_mask, reg_value);
      break;
    case 2:
      STM32_MODIFY_REG(p_hspx->ESYNC2SRCR, reg_mask, reg_value);
      break;
    default:
      return HAL_ERROR;
      break;
  }

  if (p_config->sync.state == HAL_HSP_EVENT_SYNC_ENABLE)
  {
    STM32_SET_BIT(p_hspx->ESYNCENR, (1UL << event_id));
  }
  else
  {
    STM32_CLEAR_BIT(p_hspx->ESYNCENR, (1UL << event_id));
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of an Event in the Processing Request Controller.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  event_id  Event ID
  *         This parameter can be one of the following values:
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
  * @param  p_config  Pointer to a @ref HAL_HSP_EVENT_ConfigTypeDef.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Config pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_EVENT_GetConfig(HSP_HandleTypeDef *hhsp, uint32_t event_id,
                                          HAL_HSP_EVENT_ConfigTypeDef *p_config)
{
  const HSP_TypeDef *p_hspx;
  uint32_t priority;
  uint32_t reg_idx;
  uint32_t bitfield_idx;
  uint32_t reg_pos;
  uint32_t reg_mask;
  uint32_t reg_src_value;
  uint32_t reg_tcu_value;

  ASSERT_DBG_PARAM(hhsp != NULL);

  ASSERT_DBG_PARAM(IS_HSP_EVENT(event_id));

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  uint32_t evt_id = (STM32_POSITION_VAL(event_id) - 1UL);
  reg_idx = (evt_id / HSP_REG_EVTSRC_CFG_NBR);
  bitfield_idx = (evt_id % HSP_REG_EVTSRC_CFG_NBR);
  reg_pos = HSP_EVTSRC0R_EVT1SRC_Pos + (bitfield_idx * HSP_REG_EVTSRC_FIELD_SIZE);
  reg_mask = (HSP_EVTSRC0R_EVT1SRC_Msk << reg_pos);

  switch (reg_idx)
  {
    case 0:
      reg_src_value = STM32_READ_BIT(p_hspx->EVTSRC0R, reg_mask);
      reg_tcu_value = STM32_READ_BIT(p_hspx->ESYNC0SRCR, reg_mask);
      break;
    case 1:
      reg_src_value = STM32_READ_BIT(p_hspx->EVTSRC1R, reg_mask);
      reg_tcu_value = STM32_READ_BIT(p_hspx->ESYNC1SRCR, reg_mask);
      break;
    case 2:
      reg_src_value = STM32_READ_BIT(p_hspx->EVTSRC2R, reg_mask);
      reg_tcu_value = STM32_READ_BIT(p_hspx->ESYNC2SRCR, reg_mask);
      break;
    default:
      return HAL_ERROR;
      break;
  }

  priority = (STM32_POSITION_VAL(event_id) << HAL_HSP_EVENT_PRIO_POS);

  p_config->source = (HAL_HSP_EVENT_SourceTypeDef)(uint32_t)(priority | (reg_src_value >> reg_pos));
  p_config->sync.tcu = (HAL_HSP_TASK_ComparatorTypeDef)reg_tcu_value;

  if (STM32_READ_BIT(p_hspx->ESYNCENR, event_id) != 0U)
  {
    p_config->sync.state = HAL_HSP_EVENT_SYNC_ENABLE;
  }
  else
  {
    p_config->sync.state = HAL_HSP_EVENT_SYNC_DISABLE;
  }

  return HAL_OK;
}

/**
  * @brief  Enable Events in the Processing Request Controller.
  * @param  hhsp   Pointer to a @ref HSP_HandleTypeDef.
  * @param  events Mask of Event to enable
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
HAL_StatusTypeDef HAL_HSP_EVENT_Enable(HSP_HandleTypeDef *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->EVTENR, events);

  return HAL_OK;
}

/**
  * @brief  Disable Events in the Processing Request Controller.
  * @param  hhsp   Pointer to a @ref HSP_HandleTypeDef.
  * @param  events Mask of Event to disable
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
HAL_StatusTypeDef HAL_HSP_EVENT_Disable(HSP_HandleTypeDef *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->EVTENR, events);

  return HAL_OK;
}

/**
  * @brief  Return the Status of each Event interface
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
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
  * @retval  status
  */
uint32_t HAL_HSP_EVENT_GetStatus(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return STM32_READ_BIT(p_hspx->EVTENR, HSP_EVTENR_EVTEN_Msk);
}

/**
  * @brief  Request the trig of an event to the Processing Request Controller.
  * @param  hhsp   Pointer to a @ref HSP_HandleTypeDef.
  * @param  events Mask of Events to trig
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
  * @note  The selected events must be configured with CSEG interface as source
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_EVENT_RequestSWTrigger(HSP_HandleTypeDef *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Use CSEG and the PRC must be configured as well */
  STM32_SET_BIT(p_hspx->CSEGR, events);

  return HAL_OK;
}

/**
  * @brief  Wait the end of processing of events triggered by the CPU.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  poll_mode   Polling mode.
  * @param  events Mask of Event to poll
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
  * @param  timeout_ms Timeout duration (in ms).
  * @param  p_events_status  Pointer to return the ended event.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_TIMEOUT  Timeout occurred.
  * @retval HAL_ERROR  Invalid parameter.
  */
HAL_StatusTypeDef HAL_HSP_EVENT_PollForPending(HSP_HandleTypeDef *hhsp, HAL_HSP_POLLING_ModeTypeDef poll_mode,
                                               uint32_t events, uint32_t timeout_ms,
                                               uint32_t *p_events_status)
{
  const HSP_TypeDef *p_hspx;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hhsp != NULL);

  if (p_events_status == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_POLLING_MODE(poll_mode));
  ASSERT_DBG_PARAM(IS_HSP_EVENTS_MASK(events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get tick count */
  tickstart = HAL_GetTick();

  /* Check selected event flag */
  *p_events_status = 0U;
  do
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0UL))
      {
        return HAL_TIMEOUT;
      }
    }

    uint32_t current_status = ~(STM32_READ_BIT(p_hspx->PEVTLR, events));
    if (poll_mode == HAL_HSP_POLLING_FOR_ANY_EVENT)
    {
      *p_events_status = current_status;
    }
    else
    {
      *p_events_status = ((STM32_IS_BIT_SET(current_status, events) == 1U) ? current_status : 0U);
    }
  } while (*p_events_status == 0U);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group4
  * @{
  */
/**
  * @brief  Enable the Smart Clocking of some HSP blocks.
  * @param  hhsp         Pointer to a @ref HSP_HandleTypeDef.
  * @param  clocks_mask  Mask of clocks to enable.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SMARTCLOCKING_CTRL
  *             @arg HAL_HSP_SMARTCLOCKING_SPE
  *             @arg HAL_HSP_SMARTCLOCKING_MMC
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SMARTCLOCKING_Enable(HSP_HandleTypeDef *hhsp, uint32_t clocks_mask)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SMARTCLOCKING(clocks_mask));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->CR, clocks_mask);

  return HAL_OK;
}

/**
  * @brief  Disable the Smart Clocking of some HSP blocks.
  * @param  hhsp         Pointer to a @ref HSP_HandleTypeDef.
  * @param  clocks_mask  Mask of clocks to disable.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_SMARTCLOCKING_CTRL
  *             @arg HAL_HSP_SMARTCLOCKING_SPE
  *             @arg HAL_HSP_SMARTCLOCKING_MMC
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SMARTCLOCKING_Disable(HSP_HandleTypeDef *hhsp, uint32_t clocks_mask)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SMARTCLOCKING(clocks_mask));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->CR, clocks_mask);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the specified SmartClocking block is set.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  clock  Clock.
  *         This parameter can be one of the following values:
  *             @arg HAL_HSP_SMARTCLOCKING_CTRL
  *             @arg HAL_HSP_SMARTCLOCKING_SPE
  *             @arg HAL_HSP_SMARTCLOCKING_MMC
  * @retval The state of SmartClocking (0 or 1)
  */
uint32_t HAL_HSP_SMARTCLOCKING_IsEnabled(const HSP_HandleTypeDef *hhsp, uint32_t clock)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SMARTCLOCKING(clock));

  /* Note: if the bitfield is set to 0, it means the SmartClocking is enabled ! */
  return (((STM32_READ_BIT(((HSP_TypeDef *)(uint32_t)(hhsp->Instance))->CR, clock) != 0U) ? 1U : 0U));
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group5
  * @{
  */
/**
  * @brief  Start the Task Comparator Unit.
  * @param  hhsp     Pointer to a @ref HSP_HandleTypeDef.
  * @param  tcu_id   Task Comparator Unit ID.
  * @param  task_id  Task ID to monitor.
  * @param  interrupts  Mask of Task Comparator Unit Interrupts.
  *         This parameter can be one of following values:
  *            @arg @ref  HAL_HSP_IT_NONE
  *            @arg @ref  HAL_HSP_IT_EVT_TCU0_TASK_STARTED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU1_TASK_STARTED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU2_TASK_STARTED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU3_TASK_STARTED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU0_TASK_ENDED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU1_TASK_ENDED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU2_TASK_ENDED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU3_TASK_ENDED
  *            @arg @ref  HAL_HSP_IT_EVT_TCU0_ALL
  *            @arg @ref  HAL_HSP_IT_EVT_TCU1_ALL
  *            @arg @ref  HAL_HSP_IT_EVT_TCU2_ALL
  *            @arg @ref  HAL_HSP_IT_EVT_TCU3_ALL
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TCU_StartComparator(HSP_HandleTypeDef *hhsp,
                                              HAL_HSP_TASK_ComparatorTypeDef tcu_id, HAL_HSP_TaskTypeDef task_id,
                                              uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;
  uint32_t reg_pos;
  uint32_t its_mask;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TCU(tcu_id));
  ASSERT_DBG_PARAM(IS_HSP_TASK(task_id));
  ASSERT_DBG_PARAM(IS_HSP_TCU_IT(tcu_id, interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_pos = ((uint32_t)tcu_id) * HSP_REG_TCUCFGR_BITFIELD_SIZE;
  STM32_SET_BIT(p_hspx->TCUCFGR, (HSP_TCUCFGR_TC0EN_Msk << reg_pos));
  STM32_MODIFY_REG(p_hspx->TCUCFGR, (HSP_TCUCFGR_TSKCMP0_Msk << reg_pos), ((uint32_t)task_id) << reg_pos);

  if (interrupts != HAL_HSP_IT_NONE)
  {
    hhsp->tcu_handler = HSP_TCU_Handler;

    its_mask = ((HAL_HSP_IT_EVT_TCU0_TASK_STARTED | HAL_HSP_IT_EVT_TCU0_TASK_ENDED) << (uint32_t)tcu_id);
    STM32_MODIFY_REG(p_hspx->EVT_IER, its_mask, interrupts);
  }

  return HAL_OK;
}

/**
  * @brief  Stop the Task Comparator Unit.
  * @param  hhsp     Pointer to a @ref HSP_HandleTypeDef.
  * @param  tcu_id   Task Comparator Unit ID.
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TCU_StopComparator(HSP_HandleTypeDef *hhsp, HAL_HSP_TASK_ComparatorTypeDef tcu_id)
{
  HSP_TypeDef *p_hspx;
  uint32_t reg_pos;
  uint32_t its_mask;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TCU(tcu_id));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_pos = ((uint32_t)tcu_id) * HSP_REG_TCUCFGR_BITFIELD_SIZE;
  STM32_CLEAR_BIT(p_hspx->TCUCFGR, (HSP_TCUCFGR_TC0EN_Msk << reg_pos));

  its_mask = ((HAL_HSP_IT_EVT_TCU0_TASK_STARTED | HAL_HSP_IT_EVT_TCU0_TASK_ENDED) << (uint32_t)tcu_id);
  STM32_CLEAR_BIT(p_hspx->EVT_IER, its_mask);

  if (STM32_IS_BIT_SET(p_hspx->EVT_IER, HAL_HSP_IT_EVT_TCU_ALL) == 0U)
  {
    hhsp->tcu_handler = NULL;
  }

  return HAL_OK;
}

/**
  * @brief  Start the Task Overlap feature in polling mode.
  * @param  hhsp            Pointer to a @ref HSP_HandleTypeDef.
  * @param  lower_task_id   Lower Task ID.
  * @param  higher_task_id  Higher Task ID.
  * @param  interrupts      Mask of Task Comparator Overlap Interrupts.
  *         This parameter can be one of following values:
  *            @arg @ref  HAL_HSP_IT_NONE
  *            @arg @ref  HAL_HSP_IT_EVT_TCU_TASK_OVL
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TCU_StartOverlapDetector(HSP_HandleTypeDef *hhsp,
                                                   HAL_HSP_TaskTypeDef lower_task_id,
                                                   HAL_HSP_TaskTypeDef higher_task_id,
                                                   uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TASK(lower_task_id));
  ASSERT_DBG_PARAM(IS_HSP_TASK(higher_task_id));
  ASSERT_DBG_PARAM(IS_HSP_TASK_OVERLAP_IT(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->TOVLPCR, HSP_TOVLPCR_TOVLPEN);
  STM32_MODIFY_REG(p_hspx->TOVLPCR, HSP_TOVLPCR_LTNB_Msk, ((uint32_t)lower_task_id) << HSP_TOVLPCR_LTNB_Pos);
  STM32_MODIFY_REG(p_hspx->TOVLPCR, HSP_TOVLPCR_HTNB_Msk, ((uint32_t)higher_task_id) << HSP_TOVLPCR_HTNB_Pos);

  if (interrupts != HAL_HSP_IT_NONE)
  {
    hhsp->tcu_handler = HSP_TCU_Handler;

    STM32_MODIFY_REG(p_hspx->EVT_IER, HSP_EVT_IER_TOVLPIE_Msk, interrupts);
  }

  return HAL_OK;
}

/**
  * @brief  Stop the Task Overlap feature in polling mode.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TCU_StopOverlapDetector(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->TOVLPCR, HSP_TOVLPCR_TOVLPEN);
  STM32_CLEAR_BIT(p_hspx->EVT_IER, HSP_EVT_IER_TOVLPIE);

  if (STM32_IS_BIT_SET(p_hspx->EVT_IER, HAL_HSP_IT_EVT_TCU_ALL) == 0U)
  {
    hhsp->tcu_handler = NULL;
  }

  return HAL_OK;
}

/**
  * @brief  Poll until specified flags are raised.
  * @param  hhsp       Pointer to a @ref HSP_HandleTypeDef.
  * @param  poll_mode  Polling mode.
  * @param  flags      Mask of event flags to poll
  *         This parameter can be a combination of following values:
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_OVERLAP
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP0_START_OF_TASK
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP1_START_OF_TASK
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP2_START_OF_TASK
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP3_START_OF_TASK
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP0_END_OF_TASK
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP1_END_OF_TASK
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP2_END_OF_TASK
  *            @arg @ref  HAL_HSP_FLAG_EVT_TCU_COMP3_END_OF_TASK
  * @param  timeout_ms Timeout duration (in ms).
  * @param  p_flags_status Pointer to return the raised flags.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Event pointer is NULL.
  * @retval HAL_TIMEOUT  Timeout occurred.
  */
HAL_StatusTypeDef HAL_HSP_TCU_PollForEvent(HSP_HandleTypeDef *hhsp,
                                           HAL_HSP_POLLING_ModeTypeDef poll_mode,
                                           uint32_t flags, uint32_t timeout_ms,
                                           uint32_t *p_flags_status)
{
  HSP_TypeDef *p_hspx;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_flags_status != NULL);

  if (p_flags_status == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_POLLING_MODE(poll_mode));
  ASSERT_DBG_PARAM(IS_HSP_TCU_FLAGS(flags));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get tick count */
  tickstart = HAL_GetTick();

  /* Check selected event flag */
  *p_flags_status = 0U;
  do
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0UL))
      {
        return HAL_TIMEOUT;
      }
    }

    uint32_t current_status = STM32_READ_BIT(p_hspx->EVT_ISR, flags);
    if (poll_mode == HAL_HSP_POLLING_FOR_ANY_EVENT)
    {
      *p_flags_status = current_status;
    }
    else
    {
      *p_flags_status = ((STM32_IS_BIT_SET(current_status, flags) == 1U) ? current_status : 0U);
    }
  } while (*p_flags_status == 0U);

  /* Clear selected flags */
  STM32_WRITE_REG(p_hspx->EVT_ICR, *p_flags_status);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group6
  * @{
  */
/**
  * @brief  Configure a Trigger Output.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @param  id      Trigger Output id.
  * @param  source  Trigger source.
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_OUTPUT_SetConfigTrigger(HSP_HandleTypeDef *hhsp,
                                                  HAL_HSP_OUTPUT_TriggerTypeDef id,
                                                  HAL_HSP_OUTPUT_TRIGGER_SourceTypeDef source)
{
  HSP_TypeDef *p_hspx;
  uint32_t bitfield_mask;
  uint32_t bitfield_pos;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_OUTPUT_TRIGGER(id));
  ASSERT_DBG_PARAM(IS_HSP_OUTPUT_TRIGGER_SOURCE(source));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  bitfield_pos = HSP_TRGOCFGR_TRGO0SRC_Pos + (((uint32_t)id) * HSP_REG_TRGOCFGR_BITFIELD_SRC_SIZE);
  bitfield_mask = HSP_TRGOCFGR_TRGO0SRC << bitfield_pos;
  STM32_MODIFY_REG(p_hspx->TRGOCFGR, bitfield_mask, (uint32_t)source << bitfield_pos);

  return HAL_OK;
}

/**
  * @brief  Get the configuration of a Trigger Output.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @param  id      Trigger Output id.
  * @retval Trigger Output source.
  */
HAL_HSP_OUTPUT_TRIGGER_SourceTypeDef HAL_HSP_OUTPUT_GetConfigTrigger(const HSP_HandleTypeDef *hhsp,
                                                                     HAL_HSP_OUTPUT_TriggerTypeDef id)
{
  const HSP_TypeDef *p_hspx;

  uint32_t bitfield_mask;
  uint32_t bitfield_pos;
  uint32_t source;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_OUTPUT_TRIGGER(id));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  bitfield_pos = HSP_TRGOCFGR_TRGO0SRC_Pos + (((uint32_t)id) * HSP_REG_TRGOCFGR_BITFIELD_SRC_SIZE);
  bitfield_mask = HSP_TRGOCFGR_TRGO0SRC << bitfield_pos;
  source = STM32_READ_BIT(p_hspx->TRGOCFGR, bitfield_mask) >> bitfield_pos;

  return ((HAL_HSP_OUTPUT_TRIGGER_SourceTypeDef)source);
}

/**
  * @brief  Enable the HSP Output.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_OUTPUT_Enable(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->ITFENR, HSP_ITFENR_TRGOEN);

  return HAL_OK;
}

/**
  * @brief  Disable the HSP Output.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_OUTPUT_Disable(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ITFENR, HSP_ITFENR_TRGOEN);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the Trigger Output is enabled.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_HSP_OUTPUT_ENABLED   Output is enabled.
  * @retval HAL_HSP_OUTPUT_DISABLED  Output is disabled.
  */
HAL_HSP_OUTPUT_StatusTypeDef HAL_HSP_OUTPUT_IsEnabled(const HSP_HandleTypeDef *hhsp)
{
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));

  status = STM32_READ_BIT(((HSP_TypeDef *)(uint32_t)(hhsp->Instance))->ITFENR, HSP_ITFENR_TRGOEN);
  return ((status == 0U) ? HAL_HSP_OUTPUT_DISABLED : HAL_HSP_OUTPUT_ENABLED);
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group7
  * @{
  */
/**
  * @brief  Configure the TimeStamp Capture
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_config  Pointer to a @ref HAL_HSP_TSC_ConfigTypeDef.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Config pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_TSC_SetConfig(HSP_HandleTypeDef *hhsp, const HAL_HSP_TSC_ConfigTypeDef *p_config)
{
  HSP_TypeDef *p_hspx;
  uint32_t reg_value;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM((p_config != NULL));

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  ASSERT_DBG_PARAM(IS_HSP_TSC_PRESCALER(p_config->prescaler));
  ASSERT_DBG_PARAM(IS_HSP_TSC_FREE_COUNTER(p_config->counter));
  ASSERT_DBG_PARAM(IS_HSP_TSC_FILTER(p_config->filter));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_value = ((uint32_t)(p_config->prescaler) | (uint32_t)(p_config->counter) | (uint32_t)(p_config->filter));
  STM32_MODIFY_REG(p_hspx->CAPCR, HSP_TSC_CONFIG_CAPCR_MASK, reg_value);

  return HAL_OK;
}

/**
  * @brief  Get the configuration of the TimeStamp Capture
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_config  Pointer to a @ref HAL_HSP_TSC_ConfigTypeDef.
  * @retval HAL_OK  Operation completed successfully.
  * @retval HAL_ERROR  Config pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_TSC_GetConfig(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_ConfigTypeDef *p_config)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM((p_config != NULL));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_RUNNING | (uint32_t)HAL_HSP_STATE_FAULT));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (p_config == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  p_config->prescaler = (HAL_HSP_TSC_PrescalerTypeDef)(uint32_t)STM32_READ_BIT(p_hspx->CAPCR, HSP_CAPCR_PRESC_Msk);
  p_config->counter = (HAL_HSP_TSC_FreeRunningCounterStateTypeDef)(uint32_t)STM32_READ_BIT(p_hspx->CAPCR,
                      HSP_CAPCR_FRCNTEN_Msk);
  p_config->filter = (HAL_HSP_TSC_TaskFilterTypeDef)(uint32_t)STM32_READ_BIT(p_hspx->CAPCR, HSP_CAPCR_TSKFLT_Msk);

  return HAL_OK;
}

/**
  * @brief  Enable the TimeStamp Capture.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  cap_mode  Capture Mode (@ref HAL_HSP_TSC_Capture_ModeTypeDef)
  * @retval HAL_OK     Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TSC_Enable(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_Capture_ModeTypeDef cap_mode)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TSC_CAPTURE_MODE(cap_mode));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_MODIFY_REG(p_hspx->CAPCR, HSP_CAPCR_CAPMOD_Msk, (((uint32_t)cap_mode) << HSP_CAPCR_CAPMOD_Pos));

  return HAL_OK;
}

/**
  * @brief  Disable the TimeStamp Capture.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK     Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TSC_Disable(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->CAPCR, HSP_CAPCR_CAPMOD_Msk);

  return HAL_OK;
}

/**
  * @brief Indicates if the TimeStamp Data Ready Interrupt Flag is set or not.
  * @param hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval State of bit (1 or 0).
  */
uint32_t HAL_HSP_TSC_IsActiveFlag(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  p_hspx = HSP_GET_INSTANCE(hhsp);
  return ((STM32_READ_BIT(p_hspx->EVT_ISR, HSP_EVT_ISR_CAPRDYF) == (HSP_EVT_ISR_CAPRDYF)) ? 1UL : 0UL);
}

/**
  * @brief  Get the last captured TimeStamp.
  * @param  hhsp         Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_timestamp  Pointer to a @ref HAL_HSP_TSC_TimeStampTypeDef.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Wrong parameter.
  */
HAL_StatusTypeDef HAL_HSP_TSC_GetTimeStamp(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_TimeStampTypeDef *p_timestamp)
{
  const HSP_TypeDef *p_hspx;
  uint32_t reg_value;

  ASSERT_DBG_PARAM((hhsp != NULL));

  if (p_timestamp == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* The read of CAPDR register clears automatically the HSP_EVT_ISR_CAPRDYF flal */
  reg_value = STM32_READ_REG(p_hspx->CAPDR);

  if (STM32_IS_BIT_SET(p_hspx->CAPCR, HSP_CAPCR_FRCNTEN))
  {
    p_timestamp->task_number = (STM32_READ_BIT(reg_value, HSP_CAPDR_TSKNB_Msk) >> HSP_CAPDR_TSKNB_Pos);
    p_timestamp->if_counter = (STM32_READ_BIT(reg_value, HSP_CAPDR_IFCNT_Msk) >> HSP_CAPDR_IFCNT_Pos);
    p_timestamp->if_history = (STM32_READ_BIT(reg_value, HSP_CAPDR_IFHIST_Msk) >> HSP_CAPDR_IFHIST_Pos);
    p_timestamp->timestamp = (STM32_READ_BIT(p_hspx->CAPDR, HSP_CAPDR_TSTAMP_Msk) >> HSP_CAPDR_TSTAMP_Pos);
    p_timestamp->pfct_number = 0U;
  }
  else
  {
    p_timestamp->task_number = (STM32_READ_BIT(reg_value, HSP_CAPDR_ALT_TSKNB_Msk) >> HSP_CAPDR_ALT_TSKNB_Pos);
    p_timestamp->if_counter = (STM32_READ_BIT(reg_value, HSP_CAPDR_ALT_IFCNT_Msk) >> HSP_CAPDR_ALT_IFCNT_Pos);
    p_timestamp->if_history = (STM32_READ_BIT(reg_value, HSP_CAPDR_ALT_IFHIST_Msk) >> HSP_CAPDR_ALT_IFHIST_Pos);
    p_timestamp->timestamp = 0U;
    p_timestamp->pfct_number = (STM32_READ_BIT(reg_value, HSP_CAPDR_ALT_PFCTNB_Msk) >> HSP_CAPDR_ALT_PFCTNB_Pos);
  }

  return HAL_OK;
}

/**
  * @brief  Enable the TimeStamp Capture in interrupt mode.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  cap_mode  Capture mode.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TSC_Enable_IT(HSP_HandleTypeDef *hhsp, HAL_HSP_TSC_Capture_ModeTypeDef cap_mode)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TSC_CAPTURE_MODE(cap_mode));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_MODIFY_REG(p_hspx->CAPCR, HSP_CAPCR_CAPMOD_Msk, (((uint32_t)cap_mode) << HSP_CAPCR_CAPMOD_Pos));

  hhsp->tsc_handler = HSP_TSC_Handler;
  STM32_SET_BIT(p_hspx->EVT_IER, HSP_EVT_IER_CAPRDYIE);

  hhsp->tsc_err_handler = HSP_TSC_Error_Handler;
  STM32_SET_BIT(p_hspx->ERR_IER, HSP_ERR_IER_CAPOVRIE);

  return HAL_OK;
}

/**
  * @brief  Disable the TimeStamp Capture in interrupt mode.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_TSC_Disable_IT(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->CAPCR, HSP_CAPCR_CAPMOD_Msk);

  STM32_CLEAR_BIT(p_hspx->EVT_IER, HSP_EVT_IER_CAPRDYIE);
  hhsp->tsc_handler = NULL;

  STM32_CLEAR_BIT(p_hspx->ERR_IER, HSP_ERR_IER_CAPOVRIE);
  hhsp->tsc_err_handler = NULL;

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group8
  * @{
  */
/**
  * @brief  Enable the BRAM Conflict Access Counter.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_BRAM_EnableConflictAccessCounter(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->CAPCR, HSP_CAPCR_CCNTREN);

  return HAL_OK;
}

/**
  * @brief  Disable the BRAM Conflict Access Counter.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_BRAM_DisableConflictAccessCounter(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->CAPCR, HSP_CAPCR_CCNTREN);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the BRAM Conflict Access Counter is enabled.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval The state of enabling (0 or 1)
  */
uint32_t HAL_HSP_BRAM_IsEnabledConflictAccessCounter(const HSP_HandleTypeDef *hhsp)
{
  uint32_t bit_val;

  ASSERT_DBG_PARAM((hhsp != NULL));

  bit_val = STM32_READ_BIT(((HSP_TypeDef *)(uint32_t)(hhsp->Instance))->CAPCR, HSP_CAPCR_CCNTREN_Msk);
  return (uint32_t)(((bit_val == HSP_CAPCR_CCNTREN) != 0U) ? 1U : 0U);
}

/**
  * @brief  Get the BRAM Conflict Access Counter value.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @return Counter value
  */
uint32_t HAL_HSP_BRAM_GetConflictAccessCounter(const HSP_HandleTypeDef *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  return STM32_READ_REG(((HSP_TypeDef *)(uint32_t)(hhsp->Instance))->CAPDR);
}

/**
  * @brief  Set the BRAM Bandwidth Arbitration.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  mode  Max abritration latency
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_BRAM_SetBandwidthArbitration(const HSP_HandleTypeDef *hhsp,
                                                       HAL_HSP_BRAM_ArbitrationTypeDef mode)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_BRAM_ARBITRATION(mode));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_MODIFY_REG(p_hspx->CR, HSP_CR_BARB_Msk, (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Get the BRAM Bandwidth Arbitration.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HAL_HSP_BRAM_ARBITRATION_LATENCY_16_CYCLES
  * @retval HAL_HSP_BRAM_ARBITRATION_LATENCY_8_CYCLES
  * @retval HAL_HSP_BRAM_ARBITRATION_LATENCY_4_CYCLES
  */
HAL_HSP_BRAM_ArbitrationTypeDef HAL_HSP_BRAM_GetBandwidthArbitration(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;
  uint32_t reg_value;

  ASSERT_DBG_PARAM((hhsp != NULL));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  reg_value = STM32_READ_BIT(p_hspx->CR, HSP_CR_BARB_Msk);
  return ((HAL_HSP_BRAM_ArbitrationTypeDef)reg_value);
}

/* SPE Performance Monitoring *************************************************/
/**
  * @brief  Get the Performance Cycle counter.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @return Counter value
  */
uint32_t HAL_HSP_GetPerformanceCycleCount(const HSP_HandleTypeDef *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  if (hhsp->p_perf_counter == NULL)
  {
    return 0U;
  }

  return *(hhsp->p_perf_counter);
}

/**
  * @brief  Get the Firmware Error.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @return Error code
  */
uint32_t HAL_HSP_GetFirmwareError(const HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return (uint32_t)(STM32_READ_BIT(p_hspx->FWERR, HSP_FWERR_FWERRN_Msk) >> HSP_FWERR_FWERRN_Pos);
}

/* SPE Error Interrupt -------------------------------------------------------*/
/**
  * @brief  Enable the SPE Event Interrupts.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Event Interrupts mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_EVT_CMD_DIRECT_COMMAND_DONE
  *             @arg HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE
  *             @arg HAL_HSP_IT_EVT_SPE_EXIT_FROM_WFE
  *             @arg HAL_HSP_IT_EVT_SPE_FPU_SATURATION
  *             @arg HAL_HSP_IT_EVT_SPE_ALL: All SPE Event Interrupts
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SPE_EVENT_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_IT_EVT_SPE(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  hhsp->spe_handler = HSP_SPE_Handler;
  STM32_SET_BIT(p_hspx->EVT_IER, interrupts);

  return HAL_OK;
}

/**
  * @brief  Disable SPE Event Interrupts.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Event Interrupts mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_EVT_CMD_DIRECT_COMMAND_DONE
  *             @arg HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE
  *             @arg HAL_HSP_IT_EVT_SPE_EXIT_FROM_WFE
  *             @arg HAL_HSP_IT_EVT_SPE_FPU_SATURATION
  *             @arg HAL_HSP_IT_EVT_SPE_ALL: All SPE Event Interrupts
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SPE_EVENT_DisableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_IT_EVT_SPE(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->EVT_IER, interrupts);

  if (STM32_READ_BIT(p_hspx->EVT_IER, HSP_IT_EVT_ALL) == HAL_HSP_IT_NONE)
  {
    /* All SPE Event Interrupts are disabled */
    hhsp->spe_handler = NULL;
  }

  return HAL_OK;
}

/**
  * @brief  Return the SPE Event Interrupt status.
  * @param  hhsp       Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupt  Interrupt mask.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_IT_EVT_CMD_DIRECT_COMMAND_DONE
  *             @arg HAL_HSP_IT_EVT_SPE_ENTER_IN_WFE
  *             @arg HAL_HSP_IT_EVT_SPE_EXIT_FROM_WFE
  *             @arg HAL_HSP_IT_EVT_SPE_FPU_SATURATION
  * @retval HAL_HSP_SPE_IT_ENABLED   Interrupt is enabled.
  * @retval HAL_HSP_SPE_IT_DISABLED  Interrupt is disabled.
  */
HAL_HSP_SPE_IT_StatusTypeDef HAL_HSP_SPE_EVENT_IsEnabledIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupt)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_IT_EVT_SPE(interrupt));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->EVT_IER, interrupt);
  return ((status != 0U) ? HAL_HSP_SPE_IT_ENABLED : HAL_HSP_SPE_IT_DISABLED);
}

/**
  * @brief  Enable the SPE Error Interrupts.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Error Interrupts mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_ERR_SPE_FW
  *             @arg HAL_HSP_IT_ERR_SPE_SCHEDULER
  *             @arg HAL_HSP_IT_ERR_SPE_BREAK
  *             @arg HAL_HSP_IT_ERR_SPE_HDEG_OVR
  *             @arg HAL_HSP_IT_ERR_SPE_INVALID_OPCODE
  *             @arg HAL_HSP_IT_ERR_SPE_ACCESS
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_UDF
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_OVF
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_DBZ
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_INVALID
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_DENORMAL
  *             @arg HAL_HSP_IT_ERR_SPE_ALL: All SPE Error Interrupts
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SPE_ERROR_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_IT_ERR_SPE(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  hhsp->spe_err_handler = HSP_SPE_Error_Handler;
  STM32_SET_BIT(p_hspx->ERR_IER, interrupts);

  return HAL_OK;
}

/**
  * @brief  Disable SPE Error Interrupts.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Error Interrupts mask.
  *         This parameter can be a combination of following values:
  *             @arg HAL_HSP_IT_ERR_SPE_FW
  *             @arg HAL_HSP_IT_ERR_SPE_SCHEDULER
  *             @arg HAL_HSP_IT_ERR_SPE_BREAK
  *             @arg HAL_HSP_IT_ERR_SPE_HDEG_OVR
  *             @arg HAL_HSP_IT_ERR_SPE_INVALID_OPCODE
  *             @arg HAL_HSP_IT_ERR_SPE_ACCESS
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_UDF
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_OVF
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_DBZ
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_INVALID
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_DENORMAL
  *             @arg HAL_HSP_IT_ERR_SPE_ALL: All SPE Error Interrupts
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SPE_ERROR_DisableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_IT_ERR_SPE(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->ERR_IER, interrupts);

  if (STM32_READ_BIT(p_hspx->ERR_IER, HSP_IT_ERR_ALL) == HAL_HSP_IT_NONE)
  {
    /* All SPE Error Interrupts are disabled */
    hhsp->spe_err_handler = NULL;
  }

  return HAL_OK;
}

/**
  * @brief  Return the SPE Error Interrupt status.
  * @param  hhsp       Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupt  Interrupt.
  *         This parameter can be one of following values:
  *             @arg HAL_HSP_IT_ERR_SPE_FW
  *             @arg HAL_HSP_IT_ERR_SPE_SCHEDULER
  *             @arg HAL_HSP_IT_ERR_SPE_BREAK
  *             @arg HAL_HSP_IT_ERR_SPE_HDEG_OVR
  *             @arg HAL_HSP_IT_ERR_SPE_INVALID_OPCODE
  *             @arg HAL_HSP_IT_ERR_SPE_ACCESS
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_UDF
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_OVF
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_DBZ
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_INVALID
  *             @arg HAL_HSP_IT_ERR_SPE_FPU_DENORMAL
  * @retval HAL_HSP_SPE_IT_ENABLED   Interrupt is enabled.
  * @retval HAL_HSP_SPE_IT_DISABLED  Interrupt is disabled.
  */
HAL_HSP_SPE_IT_StatusTypeDef HAL_HSP_SPE_ERROR_IsEnabledIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupt)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_IT_ERR_SPE(interrupt));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->ERR_IER, interrupt);
  return ((status != 0U) ? HAL_HSP_SPE_IT_ENABLED : HAL_HSP_SPE_IT_DISABLED);
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group9
  * @{
  */
/**
  * @brief  Select the internal signals to observe.
  * @param  hhsp     Pointer to a @ref HSP_HandleTypeDef.
  * @param  signals  Mask of signals to output.
  *         This parameter can be a combination of following values:
  *         @arg @ref  HAL_HSP_SNOOP_GRPA_TASK_2_1_0
  *         @arg @ref  HAL_HSP_SNOOP_GRPA_DMA_CH_2_1_0_IT
  *         @arg @ref  HAL_HSP_SNOOP_GRPA_TRGIN_BUFF_ADC
  *         @arg @ref  HAL_HSP_SNOOP_GRPA_TSC_PFCTNB_2_1_0
  *         @arg @ref  HAL_HSP_SNOOP_GRPA_TSC_CMP_2_1_0
  *         @arg @ref  HAL_HSP_SNOOP_GRPA_EVTCWKUP_SPEJUMP_SPEWFE
  *         @arg @ref  HAL_HSP_SNOOP_GRPA_PE_2_1_0
  *         @arg @ref  HAL_HSP_SNOOP_GRPB_TASK_5_4_3
  *         @arg @ref  HAL_HSP_SNOOP_GRPB_PRC_25_24_23
  *         @arg @ref  HAL_HSP_SNOOP_GRPB_DCMD_CDEG_HDEG
  *         @arg @ref  HAL_HSP_SNOOP_GRPB_TSC_PFCTNB_5_4_3
  *         @arg @ref  HAL_HSP_SNOOP_GRPB_TSC_CMP_3
  *         @arg @ref  HAL_HSP_SNOOP_GRPB_TSC_PULSE_CALL_IF_IFTRUE
  *         @arg @ref  HAL_HSP_SNOOP_GRPB_PE_5_4_3
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SNOOP_Enable(const HSP_HandleTypeDef *hhsp, uint32_t signals)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SNOOP_SIGNAL(signals));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_MODIFY_REG(p_hspx->SNPR, (HSP_SNPR_SNPSELB_Msk | HSP_SNPR_SNPSELA_Msk), signals);

  return HAL_OK;
}

/**
  * @brief  Select the internal signals to observe.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @param  groups  Mask of groups to disable.
  *         This parameter can be a combination of following values:
  *         @arg @ref  HAL_HSP_SNOOP_GROUP_A
  *         @arg @ref  HAL_HSP_SNOOP_GROUP_B
  *         @arg @ref  HAL_HSP_SNOOP_GROUP_ALL
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_SNOOP_Disable(const HSP_HandleTypeDef *hhsp, uint32_t groups)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_SNOOP_SIGNAL(groups));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->SNPR, groups);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group10
  * @{
  */
/**
  * @brief  Enable Critical Events to warn sensitive peripherals when a critical issue is detected by HSP.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @param  output_id  ID of Break Output.
  * @param  events  Mask of Critical Event to enable.
  *         This parameter can be a combination of following values:
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_MEMORY_ACCESS
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_FPU
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_OPCODE
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT28
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT29
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT30
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT31
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_FIRMWARE
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_SPE_OVR
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_ALL
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_BREAK_EnableCriticalEvent(const HSP_HandleTypeDef *hhsp,
                                                    HAL_HSP_BREAK_OutputTypeDef output_id, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_BREAK_OUTPUT(output_id));
  ASSERT_DBG_PARAM(STM32_IS_BIT_SET(HAL_HSP_BREAK_CRITICAL_EVENT_ALL, events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->BKOCFGR[(uint32_t)output_id], events);

  return HAL_OK;
}

/**
  * @brief  Disable Critical Events used to warn sensitive peripherals when a critical issue is detected by HSP.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @param  output_id  ID of Break Output.
  * @param  events  Mask of Critical Event to disable.
  *         This parameter can be a combination of following values:
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_MEMORY_ACCESS
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_FPU
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_OPCODE
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT28
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT29
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT30
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT31
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_FIRMWARE
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_SPE_OVR
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_ALL
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_BREAK_DisableCriticalEvent(const HSP_HandleTypeDef *hhsp,
                                                     HAL_HSP_BREAK_OutputTypeDef output_id, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_BREAK_OUTPUT(output_id));
  ASSERT_DBG_PARAM(STM32_IS_BIT_SET(HAL_HSP_BREAK_CRITICAL_EVENT_ALL, events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->BKOCFGR[(uint32_t)output_id], events);

  return HAL_OK;
}

/**
  * @brief  Get the enabling status of Critical Event used.
  * @param  hhsp   Pointer to a @ref HSP_HandleTypeDef.
  * @param  output_id  ID of Break Output.
  * @param  event  Mask of Critical Event to disable.
  *         This parameter can be one of following values:
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_MEMORY_ACCESS
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_FPU
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_OPCODE
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT28
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT29
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT30
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_PFCT31
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_FIRMWARE
  *         @arg @ref  HAL_HSP_BREAK_CRITICAL_EVENT_SPE_OVR
  * @retval HAL_HSP_BREAK_CRITICAL_EVENT_DISABLED Critical Event is disabled.
  * @retval HAL_HSP_BREAK_CRITICAL_EVENT_ENABLED  Critical Event is enabled.
  */
HAL_HSP_BREAK_Critical_Event_StatusTypeDef HAL_HSP_BREAK_IsEnabledCriticalEvent(const HSP_HandleTypeDef *hhsp,
                                                                                HAL_HSP_BREAK_OutputTypeDef output_id,
                                                                                uint32_t event)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_BREAK_OUTPUT(output_id));
  ASSERT_DBG_PARAM(IS_HSP_BREAK_CRITICAL_EVENT(event));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->BKOCFGR[(uint32_t)output_id], event);

  return (((status == 0U) ? HAL_HSP_BREAK_CRITICAL_EVENT_DISABLED : HAL_HSP_BREAK_CRITICAL_EVENT_ENABLED));
}

/**
  * @brief  Enable Events to freeze the SPE from internal error or error reported by an external block.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @param  events  Mask of Freeze Event to enable.
  *         This parameter can be a combination of following values:
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_MEMORY_ACCESS
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FPU
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_OPCODE
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT28
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT29
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT30
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT31
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FIRMWARE
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_SPE_OVR
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FPU_SATURATION
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_ALL
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_BREAK_EnableFreezeEvent(const HSP_HandleTypeDef *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(STM32_IS_BIT_SET(HAL_HSP_BREAK_FREEZE_EVENT_ALL, events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->BKICFGR, events);

  return HAL_OK;
}

/**
  * @brief  Disable Events used to freeze the SPE from internal error
  *         or error reported by an external block.
  * @param  hhsp    Pointer to a @ref HSP_HandleTypeDef.
  * @param  events  Mask of Freeze Event to enable.
  *         This parameter can be a combination of following values:
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_MEMORY_ACCESS
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FPU
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_OPCODE
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT28
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT29
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT30
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT31
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FIRMWARE
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_SPE_OVR
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FPU_SATURATION
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_ALL
  * @retval HAL_OK Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_BREAK_DisableFreezeEvent(const HSP_HandleTypeDef *hhsp, uint32_t events)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(STM32_IS_BIT_SET(HAL_HSP_BREAK_FREEZE_EVENT_ALL, events));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->BKICFGR, events);

  return HAL_OK;
}

/**
  * @brief  Get the enabling status of SPE Freeze Event used.
  * @param  hhsp   Pointer to a @ref HSP_HandleTypeDef.
  * @param  event  Mask of Critical Event to check.
  *         This parameter can be one of following values:
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_MEMORY_ACCESS
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FPU
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_OPCODE
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT28
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT29
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT30
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_PFCT31
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FIRMWARE
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_SPE_OVR
  *           @arg @ref HAL_HSP_BREAK_FREEZE_EVENT_FPU_SATURATION
  * @retval HAL_HSP_BREAK_FREEZE_EVENT_DISABLED Critical Event is disabled.
  * @retval HAL_HSP_BREAK_FREEZE_EVENT_ENABLED  Critical Event is enabled.
  */
HAL_HSP_BREAK_Freeze_Event_StatusTypeDef HAL_HSP_BREAK_IsEnabledFreezeEvent(const HSP_HandleTypeDef *hhsp,
                                                                            uint32_t event)
{
  const HSP_TypeDef *p_hspx;
  uint32_t status;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_BREAK_FREEZE_EVENT(event));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  status = STM32_READ_BIT(p_hspx->BKICFGR, event);

  return (((status == 0U) ? HAL_HSP_BREAK_FREEZE_EVENT_DISABLED : HAL_HSP_BREAK_FREEZE_EVENT_ENABLED));
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group11
  * @{
  */
/**
  * @brief  Lock the configuration.
  * @param  hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @note   Once locked, HSP configuration cannot be changed (use case: safety purpose).
  * @note   HSP can be unlocked with a system reset.
  * @retval HAL_OK     Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_Lock(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->CR, HSP_CR_REGLCK_Msk);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group11_1
  * @{
  */
/**
  * @brief  Backup all interrupt and event activation states.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  * @note   This function is dedicated for CNN function usage.
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_CNN_EnterSafeMode(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

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
  STM32_WRITE_REG(p_hspx->ITFENR, 0xE0000000U);

  return HAL_OK;
}

/**
  * @brief  Restore all interrupt and event activation states.
  * @param  hhsp  Pointer to a HSP_HandleTypeDef.
  * @note   This function is dedicated for CNN function usage.
  * @retval HAL_OK  Operation completed successfully.
  */
HAL_StatusTypeDef HAL_HSP_CNN_ExitSafeMode(const HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

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

/** @addtogroup HSP_Exported_Functions_Group12
  * @{
  */
/**
  * @brief  Run a task in Polling mode.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  task_id     Task Number.
  * @param  timeout_ms  Timeout duration (in ms).
  * @note   The task will be execute with the lower priority
  * @note   If a task is not linked to a processing list, the function will return an error
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_BUSY   A running Task is going.
  * @retval HAL_TIMEOUT   Timeout occurred.
  */
HAL_StatusTypeDef HAL_HSP_TASK_Run(const HSP_HandleTypeDef *hhsp, HAL_HSP_TaskTypeDef task_id, uint32_t timeout_ms)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TASK(task_id));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Check if a task is in progress */
  if (STM32_READ_BIT(p_hspx->CDEGR, HSP_CDEGR_CDEGBSY) == HSP_CDEGR_CDEGBSY)
  {
    return HAL_BUSY;
  }

  STM32_MODIFY_REG(p_hspx->CDEGR, HSP_CDEGR_CTSKN, ((uint32_t)task_id) << HSP_CDEGR_CTSKN_Pos);

  /* Wait until the CDEG is ready to accept the generation of a new event */
  uint32_t tick_start = HAL_GetTick();
  while (STM32_READ_BIT(p_hspx->CDEGR, HSP_CDEGR_CDEGBSY) != 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if ((HAL_GetTick() - tick_start) > timeout_ms)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Run a task in IT mode.
  * @param  hhsp     Pointer to a @ref HSP_HandleTypeDef.
  * @param  task_id  Task Number
  * @note   The task will be execute with the lower priority
  * @note   If a task is not linked to a processing list, the function will return an error
  * @retval HAL_OK     Operation completed successfully.
  * @retval HAL_BUSY   A task execution is ongoing.
  */
HAL_StatusTypeDef HAL_HSP_TASK_Run_IT(HSP_HandleTypeDef *hhsp, HAL_HSP_TaskTypeDef task_id)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_TASK(task_id));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Check if a task is in progress */
  if (STM32_READ_BIT(p_hspx->CDEGR, HSP_CDEGR_CDEGBSY) == HSP_CDEGR_CDEGBSY)
  {
    return HAL_BUSY;
  }

  /* Initialize the IRQ subroutine to process miscelleanous SPE IT */
  hhsp->cmd_handler = HSP_CMD_Handler;

  STM32_SET_BIT(p_hspx->EVT_IER, HAL_HSP_IT_EVT_CMD_CDEG_READY);

  STM32_MODIFY_REG(p_hspx->CDEGR, HSP_CDEGR_CTSKN, ((uint32_t)task_id) << HSP_CDEGR_CTSKN_Pos);

  return HAL_OK;
}

/**
  * @brief  Poll on Processing Function Event Flags.
  * @param  hhsp       Pointer to a @ref HSP_HandleTypeDef.
  * @param  poll_mode  Polling mode.
  * @param  pfct_events  Mask of events to poll.
  *         This parameter can be a combination of the following values:
  *             @arg HAL_HSP_PROCLIST_EVT_0:   The Flag of Processing Function Event 0
  *             @arg HAL_HSP_PROCLIST_EVT_1:   The Flag of Processing Function Event 1
  *             @arg HAL_HSP_PROCLIST_EVT_2:   The Flag of Processing Function Event 2
  *             @arg HAL_HSP_PROCLIST_EVT_3:   The Flag of Processing Function Event 3
  *             @arg HAL_HSP_PROCLIST_EVT_4:   The Flag of Processing Function Event 4
  *             @arg HAL_HSP_PROCLIST_EVT_5:   The Flag of Processing Function Event 5
  *             @arg HAL_HSP_PROCLIST_EVT_6:   The Flag of Processing Function Event 6
  *             @arg HAL_HSP_PROCLIST_EVT_7:   The Flag of Processing Function Event 7
  *             @arg HAL_HSP_PROCLIST_EVT_8:   The Flag of Processing Function Event 8
  *             @arg HAL_HSP_PROCLIST_EVT_9:   The Flag of Processing Function Event 9
  *             @arg HAL_HSP_PROCLIST_EVT_10:  The Flag of Processing Function Event 10
  *             @arg HAL_HSP_PROCLIST_EVT_11:  The Flag of Processing Function Event 11
  *             @arg HAL_HSP_PROCLIST_EVT_12:  The Flag of Processing Function Event 12
  *             @arg HAL_HSP_PROCLIST_EVT_13:  The Flag of Processing Function Event 13
  *             @arg HAL_HSP_PROCLIST_EVT_14:  The Flag of Processing Function Event 14
  *             @arg HAL_HSP_PROCLIST_EVT_15:  The Flag of Processing Function Event 15
  *             @arg HAL_HSP_PROCLIST_EVT_16:  The Flag of Processing Function Event 16
  *             @arg HAL_HSP_PROCLIST_EVT_17:  The Flag of Processing Function Event 17
  *             @arg HAL_HSP_PROCLIST_EVT_18:  The Flag of Processing Function Event 18
  *             @arg HAL_HSP_PROCLIST_EVT_19:  The Flag of Processing Function Event 19
  *             @arg HAL_HSP_PROCLIST_EVT_20:  The Flag of Processing Function Event 20
  *             @arg HAL_HSP_PROCLIST_EVT_21:  The Flag of Processing Function Event 21
  *             @arg HAL_HSP_PROCLIST_EVT_22:  The Flag of Processing Function Event 22
  *             @arg HAL_HSP_PROCLIST_EVT_23:  The Flag of Processing Function Event 23
  *             @arg HAL_HSP_PROCLIST_EVT_24:  The Flag of Processing Function Event 24
  *             @arg HAL_HSP_PROCLIST_EVT_25:  The Flag of Processing Function Event 25
  *             @arg HAL_HSP_PROCLIST_EVT_26:  The Flag of Processing Function Event 26
  *             @arg HAL_HSP_PROCLIST_EVT_27:  The Flag of Processing Function Event 27
  *             @arg HAL_HSP_PROCLIST_EVT_28:  The Flag of Processing Function Event 28
  *             @arg HAL_HSP_PROCLIST_EVT_29:  The Flag of Processing Function Event 29
  *             @arg HAL_HSP_PROCLIST_EVT_30:  The Flag of Processing Function Event 30
  *             @arg HAL_HSP_PROCLIST_EVT_31:  The Flag of Processing Function Event 31
  *             @arg HAL_HSP_PROCLIST_EVT_ALL: All Flags of Processing Function Event
  * @param  timeout_ms           Timeout duration (in ms).
  * @param  p_pfct_events_status  Pointer to return the Processing Function Event flags.
  * @retval HAL_OK  Operation completed successfully.
  * @retval HAL_TIMEOUT Operation timed out.
  * @retval HAL_ERROR   Invalid parameter.
  */
HAL_StatusTypeDef HAL_HSP_PROCLIST_PollForNotification(HSP_HandleTypeDef *hhsp,
                                                       HAL_HSP_POLLING_ModeTypeDef poll_mode,
                                                       uint32_t pfct_events, uint32_t timeout_ms,
                                                       uint32_t *p_pfct_events_status)
{
  HSP_TypeDef *p_hspx;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_POLLING_MODE(poll_mode));
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(pfct_events));
  ASSERT_DBG_PARAM(p_pfct_events_status != NULL);

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  if (p_pfct_events_status == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get tick count */
  tickstart = HAL_GetTick();

  /* Check selected event flag */
  *p_pfct_events_status = 0U;
  do
  {
    /* Check if timeout is disabled (set to infinite wait) */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0UL))
      {
        return HAL_TIMEOUT;
      }
    }

    uint32_t current_flag_status = STM32_READ_BIT(p_hspx->PFCTEVT_ISR, pfct_events);
    if (poll_mode == HAL_HSP_POLLING_FOR_ANY_EVENT)
    {
      *p_pfct_events_status = current_flag_status;
    }
    else
    {
      *p_pfct_events_status = ((STM32_IS_BIT_SET(current_flag_status, pfct_events) == 1U) ? current_flag_status : 0U);
    }
  } while (*p_pfct_events_status == 0U);

  /* Clear flags triggered */
  STM32_WRITE_REG(p_hspx->PFCTEVT_ICR, *p_pfct_events_status);

  return HAL_OK;
}

/**
  * @brief  Enable Processing Function Event Interrupts.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Mask of Processing Function Event Interrupts
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
HAL_StatusTypeDef HAL_HSP_PROCLIST_EnableIT(HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_SET_BIT(p_hspx->PFCTEVT_IER, interrupts);

  return HAL_OK;
}

/**
  * @brief  Disable Processing Function Event Interrupts.
  * @param  hhsp      Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupts  Mask of Processing Function Event Interrupts
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
HAL_StatusTypeDef HAL_HSP_PROCLIST_DisableIT(const HSP_HandleTypeDef *hhsp, uint32_t interrupts)
{
  HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(interrupts));

  HSP_ASSERT_DBG_STATE(hhsp->global_state, (uint32_t)HAL_HSP_STATE_RUNNING);

  p_hspx = HSP_GET_INSTANCE(hhsp);

  STM32_CLEAR_BIT(p_hspx->PFCTEVT_IER, interrupts);

  return HAL_OK;
}

/**
  * @brief  Check whether or not the specified Processing Function Event interrupt is set.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @param  interrupt  Mask of Processing Function Event Interrupt
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
  * @retval The state of HSP interrupt (0 or 1)
  */
uint32_t HAL_HSP_PROCLIST_IsEnabledIT(const HSP_HandleTypeDef *hhsp,
                                      uint32_t interrupt)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM((hhsp != NULL));
  ASSERT_DBG_PARAM(IS_HSP_PROCLIST_IT_PFCTEVT(interrupt));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  return ((STM32_READ_BIT(p_hspx->PFCTEVT_IER, interrupt) != 0U) ? 1U : 0U);
}

/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group13
  * @{
  */
/* Global IRQ Handler *********************************************************/
/**
  * @brief  Handle all HSP interrupt request.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  */
void HAL_HSP_IRQHandler(HSP_HandleTypeDef *hhsp)
{
  ASSERT_DBG_PARAM(hhsp != NULL);

  HAL_HSP_ERR_IRQHandler(hhsp);
  HAL_HSP_EVT_IRQHandler(hhsp);
  HAL_HSP_FWEVT_IRQHandler(hhsp);
}

/* Event IRQ Handlers and Callbacks *******************************************/
/**
  * @brief  Handle all HSP Event interrupt request.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  */
void HAL_HSP_EVT_IRQHandler(HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;

  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE(hhsp->Instance));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get Processing Status */
  uint32_t reg_evt_ier = STM32_READ_REG(p_hspx->EVT_IER);
  uint32_t reg_evt_isr = STM32_READ_REG(p_hspx->EVT_ISR);
  uint32_t reg_evt_misr = reg_evt_ier & reg_evt_isr;

  /* STREAM Interface --------------------------------------------------------*/
  if (hhsp->stream_handler != NULL)
  {
    hhsp->stream_handler(hhsp, reg_evt_misr);
  }

  /* Task Comparator Interface -----------------------------------------------*/
  if (hhsp->tcu_handler != NULL)
  {
    hhsp->tcu_handler(hhsp, reg_evt_misr);
  }

  /* Miscelleanous SPE Events ------------------------------------------------*/
  if (hhsp->spe_handler != NULL)
  {
    hhsp->spe_handler(hhsp, reg_evt_misr);
  }

  /* TimeStamp Ready ---------------------------------------------------------*/
  if (hhsp->tsc_handler != NULL)
  {
    hhsp->tsc_handler(hhsp, reg_evt_misr);
  }

  /* Command Interface -------------------------------------------------------*/
  if (hhsp->cmd_handler != NULL)
  {
    hhsp->cmd_handler(hhsp, reg_evt_misr);
  }
}

/**
  * @brief  Callback for STREAM Buffer Empty.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param buffer_ids  Buffer ID mask.
  */
__WEAK void HAL_HSP_EVT_STREAM_BufferEmptyCallback(HSP_HandleTypeDef *hhsp, uint32_t buffer_ids)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(buffer_ids);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_STREAM_BufferEmptyCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for STREAM Buffer Full.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param buffer_ids  Buffer ID mask.
  */
__WEAK void HAL_HSP_EVT_STREAM_BufferFullCallback(HSP_HandleTypeDef *hhsp, uint32_t buffer_ids)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(buffer_ids);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_STREAM_BufferFullCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for Start Of Task Interrupts.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param tcu_ids  TCU IDs mask.
  */
__WEAK void HAL_HSP_EVT_TCU_TaskStartedCallback(HSP_HandleTypeDef *hhsp, uint32_t tcu_ids)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(tcu_ids);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_TCU_TaskStartedCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for End Of Task Interrupts.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param tcu_ids  TCU IDs mask.
  */
__WEAK void HAL_HSP_EVT_TCU_TaskEndedCallback(HSP_HandleTypeDef *hhsp, uint32_t tcu_ids)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(tcu_ids);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_TCU_TaskEndedCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for Task Overlap Event.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  */
__WEAK void HAL_HSP_EVT_TCU_TaskOverlapCallback(HSP_HandleTypeDef *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_TCU_TaskOverlapCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for Direct Command Execution Complete.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  */
__WEAK void HAL_HSP_EVT_SPE_DirectCommandCpltCallback(HSP_HandleTypeDef *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_SPE_DirectCommandCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for Task Execution Complete.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  */
__WEAK void HAL_HSP_EVT_SPE_TaskCpltCallback(HSP_HandleTypeDef *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_SPE_TaskCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for SPE Run  State change.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param state  SPE State.
  */
__WEAK void HAL_HSP_EVT_SPE_RunStateCallback(HSP_HandleTypeDef *hhsp, uint32_t state)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(state);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_SPE_RunStateCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for FPU Saturation Event.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  */
__WEAK void HAL_HSP_EVT_SPE_FPUSaturationCallback(HSP_HandleTypeDef *hhsp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_SPE_FPUSaturationCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for TimeStamp Capture Date Ready.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param timestamp  Timestamp data.
  */
__WEAK void HAL_HSP_EVT_TSC_TimestampReadyCallback(HSP_HandleTypeDef *hhsp, uint32_t timestamp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(timestamp);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_EVT_TSC_TimestampReadyCallback must be implemented in the user file.
   */
}

/* Error IRQ Handlers and Callbacks *******************************************/
/**
  * @brief  Handle all HSP Error interrupt request.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  */
void HAL_HSP_ERR_IRQHandler(HSP_HandleTypeDef *hhsp)
{
  const HSP_TypeDef *p_hspx;
  uint32_t errors = 0U;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE(hhsp->Instance));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get Processing Status */
  uint32_t reg_err_ier = STM32_READ_REG(p_hspx->ERR_IER);
  uint32_t reg_err_isr = STM32_READ_REG(p_hspx->ERR_ISR);
  uint32_t reg_err_misr = reg_err_ier & reg_err_isr;

  /* Adjust value of reg_err_misr for FPU ITs where there is only one FPU_ERR Flag */
  if ((reg_err_ier & HAL_HSP_IT_ERR_SPE_FPU_ALL) != 0U)
  {
    /* Complete the MISR for FPU Error */
    reg_err_misr |= (reg_err_isr & HAL_HSP_FLAG_ERR_SPE_FPU);
  }

  /* Read FWERR & ERRINFR before to process each IT while there are reset
     when the IT flags were cleared
  */
  uint32_t fw_error_code = STM32_READ_REG(p_hspx->FWERR);
  uint32_t spe_error_inf = STM32_READ_REG(p_hspx->ERRINFR);

  /* STREAM Interface --------------------------------------------------------*/
  if (hhsp->stream_err_handler != NULL)
  {
    hhsp->stream_err_handler(hhsp, reg_err_misr, &errors);
  }

  /* TRGIN Interface ---------------------------------------------------------*/
  if (hhsp->trgin_err_handler != NULL)
  {
    hhsp->trgin_err_handler(hhsp, reg_err_misr, &errors);
  }

  /* TSC Interface -----------------------------------------------------------*/
  if (hhsp->tsc_err_handler != NULL)
  {
    hhsp->tsc_err_handler(hhsp, reg_err_misr, &errors);
  }

  /* SPE ---------------------------------------------------------------------*/
  if (hhsp->spe_err_handler != NULL)
  {
    hhsp->spe_err_handler(hhsp, reg_err_misr, &errors);
  }

  /* Store current volatile hhsp->last_error_codes, misra rule */
  hhsp->last_error_codes |= errors;
  uint32_t tmperror = (hhsp->last_error_codes) & HAL_HSP_ERROR_HW_ALL;

  /* Call the Error Callback in case of Error detected */
  if (tmperror != HAL_HSP_ERROR_NONE)
  {
    /* Call the corresponding callback to inform upper layer of Error */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->ErrorCallback(hhsp, fw_error_code, spe_error_inf);
#else
    HAL_HSP_ErrorCallback(hhsp, fw_error_code, spe_error_inf);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/* Firmware Event IRQ Handlers and Callbacks **********************************/
/**
  * @brief  Handle all HSP Firmware Event interrupt request.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  */
void HAL_HSP_FWEVT_IRQHandler(HSP_HandleTypeDef *hhsp)
{
  HSP_TypeDef *p_hspx;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(IS_HSP_ALL_INSTANCE(hhsp->Instance));

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* Get Processing Status */
  uint32_t reg_processing_ier = STM32_READ_REG(p_hspx->PFCTEVT_IER);
  uint32_t reg_processing_isr = STM32_READ_REG(p_hspx->PFCTEVT_ISR);
  uint32_t reg_processing_misr = reg_processing_ier & reg_processing_isr;

  if (reg_processing_misr > 0U)
  {
    /* Clear Flags: Processing Status */
    STM32_WRITE_REG(p_hspx->PFCTEVT_ICR, reg_processing_misr);

    /* Call the callback */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->FWEVT_ProcessingEventCallback(hhsp, reg_processing_misr);
#else
    HAL_HSP_FWEVT_ProcessingEventCallback(hhsp, reg_processing_misr);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Callback for Processing Function Events.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param events  Processing Function Events mask.
  */
__WEAK void HAL_HSP_FWEVT_ProcessingEventCallback(HSP_HandleTypeDef *hhsp, uint32_t events)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(events);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_FWEVT_ProcessingEventCallback must be implemented in the user file.
   */
}

/**
  * @brief  Callback for any Error.
  * @param hhsp Pointer to a @ref HSP_HandleTypeDef.
  * @param fw_error_code  Firmware Error Code
  * @param error_inf_mask  SPE Errors mask
  */
__WEAK void HAL_HSP_ErrorCallback(HSP_HandleTypeDef *hhsp, uint32_t fw_error_code, uint32_t error_inf_mask)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hhsp);
  UNUSED(fw_error_code);
  UNUSED(error_inf_mask);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HAL_HSP_ErrorCallback must be implemented in the user file.
   */
}

#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions ************************************/
/**
  * @brief  Register a User HSP callback for MSP Init.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterMspInitCallback(HSP_HandleTypeDef *hhsp, pHSP_CallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  /* Store the callback function within handle */
  hhsp->MspInitCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for MSP DeInit.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterMspDeInitCallback(HSP_HandleTypeDef *hhsp, pHSP_CallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  /* Store the callback function within handle */
  hhsp->MspDeInitCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for SPE Event: Direct Command Complete.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterSPE_DirectCommandCpltCallback(HSP_HandleTypeDef *hhsp,
                                                                pHSP_CallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_SPE_DirectCommandCpltCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for SPE Event: Ready For New Task in Lowest Priority.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterSPE_TaskCpltCallback(HSP_HandleTypeDef *hhsp,
                                                       pHSP_CallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_SPE_TaskCpltCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for SPE Event: FPU Saturation.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterSPE_FPUSaturationCallback(HSP_HandleTypeDef *hhsp,
                                                            pHSP_CallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_SPE_FPUSaturationCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for SPE Event: Run State Changed.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterSPE_RunStateCallback(HSP_HandleTypeDef *hhsp,
                                                       pHSP_OneParamCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_SPE_RunStateCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for STREAM Buffer Event: Buffer Empty.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterSTREAM_BufferEmptyCallback(HSP_HandleTypeDef *hhsp,
                                                             pHSP_OneParamCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_STREAM_BufferEmptyCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for STREAM Buffer Event: Buffer Full.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterSTREAM_BufferFullCallback(HSP_HandleTypeDef *hhsp,
                                                            pHSP_OneParamCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_STREAM_BufferFullCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for Task Comparator Event: Task Overlap.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterTCU_TaskOverlapCallback(HSP_HandleTypeDef *hhsp,
                                                          pHSP_CallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_TCU_TaskOverlapCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for Task Comparator Events: Start Of Task.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterTCU_TaskStartedCallback(HSP_HandleTypeDef *hhsp,
                                                          pHSP_OneParamCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_TCU_TaskStartedCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for Task Comparator Events: End Of Task.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterTCU_TaskEndedCallback(HSP_HandleTypeDef *hhsp,
                                                        pHSP_OneParamCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_TCU_TaskEndedCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for TimeStamp Capture Event: Timestamp Ready.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterTSC_TimestampReadyCallback(HSP_HandleTypeDef *hhsp,
                                                             pHSP_OneParamCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->EVT_TSC_TimestampReadyCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for any Error Event.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterErrorCallback(HSP_HandleTypeDef *hhsp, pHSP_TwoParamsCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->ErrorCallback = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a User HSP callback for any Processing Function Event.
  * @param  hhsp        Pointer to a @ref HSP_HandleTypeDef.
  * @param  p_callback  Pointer to the callback function.
  * @retval HAL_OK      Registering completed successfully.
  * @retval HAL_ERROR   p_callback pointer is NULL.
  */
HAL_StatusTypeDef HAL_HSP_RegisterFWEVT_ProcessingEventCallback(HSP_HandleTypeDef *hhsp,
                                                                pHSP_OneParamCallbackTypeDef p_callback)
{
  ASSERT_DBG_PARAM(hhsp != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  if (p_callback == NULL)
  {
    hhsp->last_error_codes |= HAL_HSP_ERROR_INVALID_PARAM;

    return HAL_ERROR;
  }

  HSP_ASSERT_DBG_STATE(hhsp->global_state, ((uint32_t)HAL_HSP_STATE_INIT | (uint32_t)HAL_HSP_STATE_READY_TO_BOOT
                                            | (uint32_t)HAL_HSP_STATE_RUNNING));

  /* Store the callback function within handle */
  hhsp->FWEVT_ProcessingEventCallback = p_callback;

  return HAL_OK;
}

#endif /* USE_HAL_HSP_REGISTER_CALLBACKS == 1 */
/**
  * @}
  */

/** @addtogroup HSP_Exported_Functions_Group14
  * @brief   Peripheral State, Mode and Error functions
  *
@verbatim
 ===============================================================================
            ##### Peripheral State, Mode and Error functions #####
 ===============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */
/**
  * @brief  Return the HSP handle state.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HSP State
  */
HAL_HSP_StateTypeDef HAL_HSP_GetState(const HSP_HandleTypeDef *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  return hhsp->global_state;
}

/**
  * @brief  Get the HSP last error codes.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @return uint32_t  This return value can be a combination of the following values:
  *         @arg @ref HAL_HSP_ERROR_NONE
  */
uint32_t HAL_HSP_GetError(const HSP_HandleTypeDef *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  return hhsp->last_error_codes;
}

/**
  * @brief  Get the HSP Boot error code.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HSP Error Code
  */
uint32_t HAL_HSP_GetBootErrorCode(const HSP_HandleTypeDef *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  return hhsp->boot_error_code;
}

/**
  * @brief  Get the HSP MsgBox last error code.
  * @param  hhsp  Pointer to a @ref HSP_HandleTypeDef.
  * @retval HSP Error Code
  */
uint32_t HAL_HSP_GetMsgBoxErrorCode(const HSP_HandleTypeDef *hhsp)
{
  ASSERT_DBG_PARAM((hhsp != NULL));

  return hhsp->last_msgbox_error_code;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup HSP_Private_Functions HSP Private Functions
  * @{
  */
/**
  * @brief HSP Firmware reset request.
  * @param hhsp  HSP handle.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_TIMEOUT Timeout elapsed !
  *                   No ensure that HSP reset does not disturb the activity of
  *                   other components of the product
  */
static HAL_StatusTypeDef HSP_Reset(const HSP_HandleTypeDef *hhsp)
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
    if ((HAL_GetTick() - tickstart) > HSP_TIMEOUT_RESET_MS)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (!STM32_IS_BIT_SET(p_hspx->CR, HSP_CR_RSTOK))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles the STREAM Buffers in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_STREAM_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr)
{
  uint32_t stream_evts_status = (STM32_READ_BIT(reg_evt_misr, HAL_HSP_IT_EVT_STREAM_ALL) >> HSP_EVT_IER_B0EVTIE_Pos);

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
      hhsp->EVT_STREAM_BufferEmptyCallback(hhsp, stream_buffer_rx_ready);
#else
      HAL_HSP_EVT_STREAM_BufferEmptyCallback(hhsp, stream_buffer_rx_ready);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
    }

    if (stream_buffer_tx_ready != 0U)
    {
      /* Some TX Buffers are full */
      /* Disable ITs before the callback */
      STM32_CLEAR_BIT(p_hspx->EVT_IER, stream_buffer_tx_ready << HSP_EVT_IER_B0EVTIE_Pos);

#if defined(USE_HAL_HSP_REGISTER_CALLBACKS) && (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
      hhsp->EVT_STREAM_BufferFullCallback(hhsp, stream_buffer_tx_ready);
#else
      HAL_HSP_EVT_STREAM_BufferFullCallback(hhsp, stream_buffer_tx_ready);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the Task Comparator Unit in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_TCU_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr)
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
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_TCU_TaskStartedCallback(hhsp, tcu_start_flags);
#else
    HAL_HSP_EVT_TCU_TaskStartedCallback(hhsp, tcu_start_flags);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }

  if (tcu_end_flags != 0U)
  {
    /* Clear flag: End of Task for Task Comparator Units */
    STM32_WRITE_REG(p_hspx->EVT_ICR, tcu_end_flags);

    /* Call the corresponding callback to inform upper layer of End of Tasks */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_TCU_TaskEndedCallback(hhsp, tcu_end_flags);
#else
    HAL_HSP_EVT_TCU_TaskEndedCallback(hhsp, tcu_end_flags);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }

  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_TOVLPF))
  {
    /* Clear flag: Task Overlap */
    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ISR_TOVLPF);

    /* Call the corresponding callback to inform upper layer of a Task Overlapping */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_TCU_TaskOverlapCallback(hhsp);
#else
    HAL_HSP_EVT_TCU_TaskOverlapCallback(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the Command Events in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_CMD_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* DCMD Event --------------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_DCDONEF))
  {
    /* Clear flag: Direct Command done */
    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ISR_DCDONEF);

    /* Call the corresponding callback to inform upper layer of the end of Direct Command processing */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_SPE_DirectCommandCpltCallback(hhsp);
#else
    HAL_HSP_EVT_SPE_DirectCommandCpltCallback(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }

  /* CDEG Event --------------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_CDEGRDYF))
  {
    /* Disable the IT enabled by HAL_HSP_TASK_Run_IT */
    STM32_CLEAR_BIT(p_hspx->EVT_IER, HSP_EVT_IER_CDEGRDYIE);

    /* Note: No need to clear the flag. It will be done when sending a new Task */

    /* Call the corresponding callback to inform upper layer of CDEG is Ready */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_SPE_TaskCpltCallback(hhsp);
#else
    HAL_HSP_EVT_SPE_TaskCpltCallback(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the SPE Events in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_SPE_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* SPE State Events --------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_SOFWFEF))
  {
    /* Clear flag: Start Of WFE */
    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ISR_SOFWFEF);

    /* Call the corresponding callback to inform upper layer of SPE enters in WFE mode */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_SPE_RunStateCallback(hhsp, HAL_HSP_SPE_RUN_STATE_WFE);
#else
    HAL_HSP_EVT_SPE_RunStateCallback(hhsp, HAL_HSP_SPE_RUN_STATE_WFE);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
  else if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_EOFWFEF))
  {
    /* Clear flag: End Of WFE */
    STM32_SET_BIT(p_hspx->EVT_ICR, HSP_EVT_ISR_EOFWFEF);

    /* Call the corresponding callback to inform upper layer of SPE exits from WFE mode */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_SPE_RunStateCallback(hhsp, HAL_HSP_SPE_RUN_STATE_ACTIVE);
#else
    HAL_HSP_EVT_SPE_RunStateCallback(hhsp, HAL_HSP_SPE_RUN_STATE_ACTIVE);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
  else
  {
    /* No action to performed */
  }

  /* FPU Saturation Event ----------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_FPUSATF))
  {
    /* Clear flag: FPU Saturation */
    STM32_WRITE_REG(p_hspx->EVT_ICR, HSP_EVT_ISR_FPUSATF);

    /* Call the corresponding callback to inform upper layer of a Task Overlapping */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_SPE_FPUSaturationCallback(hhsp);
#else
    HAL_HSP_EVT_SPE_FPUSaturationCallback(hhsp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the TimeStamp Capture Events in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_evt_misr  Event Interrupt Status to handle.
  */
static void HSP_TSC_Handler(HSP_HandleTypeDef *hhsp, uint32_t reg_evt_misr)
{
  const HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  if (STM32_IS_BIT_SET(reg_evt_misr, HSP_EVT_ISR_CAPRDYF))
  {
    uint32_t timestamp = STM32_READ_REG(p_hspx->CAPDR);

    /* Note: No need to clear the flag HSP_EVT_ISR_CAPRDYF. It is node by HW when CAPDR register is read */

    /* Call the corresponding callback to inform upper layer of a Task Overlapping */
#if (USE_HAL_HSP_REGISTER_CALLBACKS == 1)
    hhsp->EVT_TSC_TimestampReadyCallback(hhsp, timestamp);
#else
    HAL_HSP_EVT_TSC_TimestampReadyCallback(hhsp, timestamp);
#endif /* USE_HAL_HSP_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the STREAM Error in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @param  p_errors      Pointer to error codes variable to be updated.
  */
static void HSP_STREAM_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* STREAM Interface --------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B0ERRF))
  {
    /* Clear flag: H2CBUFF0 Underrun or C2HBUFF0 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B0ERRC);

    *p_errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B1ERRF))
  {
    /* Clear flag: H2CBUFF1 Underrun or C2HBUFF1 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B1ERRC);

    *p_errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B2ERRF))
  {
    /* Clear flag: H2CBUFF2 Underrun or C2HBUFF2 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B2ERRC);

    *p_errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_B3ERRF))
  {
    /* Clear flag: H2CBUFF3 Underrun or C2HBUFF3 Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_B3ERRC);

    *p_errors |= HAL_HSP_ERROR_BUFFER_UDR_OR_OVR;
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the TRGIN Error in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @param  p_errors      Pointer to error codes variable to be updated.
  */
static void HSP_TRGIN_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* TRGIN Interface ---------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_TRGIOVRF))
  {
    /* Clear flag: TRGITF Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_TRGIOVRC);

    *p_errors |= HAL_HSP_ERROR_TRGIN_OVR;
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the TimeStamp Capture Errors in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @param  p_errors      Pointer to error codes variable to be updated.
  */
static void HSP_TSC_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* TSC Interface -----------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_CAPOVRF))
  {
    /* Clear flag: Capture register Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_CAPOVRC);

    *p_errors |= HAL_HSP_ERROR_CAPTURE_OVR;
  }
}

/**
  * @brief  Interrupt Sub-Routine which handles the SPE Errors in interrupt mode.
  * @param  hhsp          Pointer to a @ref HSP_HandleTypeDef.
  * @param  reg_err_misr  Error Interrupt Status to handle.
  * @param  p_errors      Pointer to error codes variable to be updated.
  */
static void HSP_SPE_Error_Handler(const HSP_HandleTypeDef *hhsp, uint32_t reg_err_misr, uint32_t *p_errors)
{
  HSP_TypeDef *p_hspx;

  p_hspx = HSP_GET_INSTANCE(hhsp);

  /* SPE Interface -----------------------------------------------------------*/
  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_FWERRF))
  {
    /* Clear flag: Firmware Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_FWERRC);

    *p_errors |= HAL_HSP_ERROR_FIRMWARE;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_SCHERRF))
  {
    /* Clear flag: Scheduler Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_SCHERRC);

    *p_errors |= HAL_HSP_ERROR_SCHEDULER;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_BKINF))
  {
    /* Clear flag: Break Input */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_BKINC);

    *p_errors |= HAL_HSP_ERROR_BREAK_IN;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_HDEGOVRF))
  {
    /* Clear flag: SPE Event Overrun */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_HDEGOVRC);

    *p_errors |= HAL_HSP_ERROR_HDEG_OVR;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_OPCOERRF))
  {
    /* Clear flag: Invalid OpCode */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_OPCOERRC);

    *p_errors |= HAL_HSP_ERROR_OPCODE_INVALID;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_ACCERRF))
  {
    /* Clear flag: SPE Access Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_ACCERRC);

    *p_errors |= HAL_HSP_ERROR_SPE_ACCESS;
  }

  if (STM32_IS_BIT_SET(reg_err_misr, HSP_ERR_ISR_FPUERRF))
  {
    /* Clear flag: Computation Error */
    STM32_WRITE_REG(p_hspx->ERR_ICR, HSP_ERR_ICR_FPUERRC);

    *p_errors |= HAL_HSP_ERROR_FPU;
  }

}

/**
  * @}
  */

#endif /* HAL_HSP_MODULE_ENABLED */

/**
  * @}
  */

#endif /* HSP1 */

/**
  * @}
  */
