/**
  ******************************************************************************
  * @file    stm32g5xx_hal_hrtim.c
  * @brief   This file provides HRTIM (High Resolution Timer) peripheral services.
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

/** @addtogroup HRTIM
  * @{
  */
#if defined(HRTIM1)
#if defined (USE_HAL_HRTIM_MODULE) && (USE_HAL_HRTIM_MODULE == 1)

/** @defgroup HRTIM_Introduction HRTIM Introduction
  * @{

  - The HRTIM hardware abstraction layer (HAL) provides a set of APIs to interface with STM32 High-Resolution Timer
    (HRTIM).

  - The STM32 High-Resolution Timer (HRTIM) peripheral is primarily used for advanced power conversion and motor control
    applications, offering precise control of switching signals with high timing resolution and complex waveform
    generation.

  - The HRTIM HAL driver simplifies the configuration, initialization, and management of the high-resolution timer
    operations by supporting various modes such as polling, interrupt, and DMA, enabling flexible and efficient
    high-resolution timer control.

  - This abstraction layer ensures portability and ease of use across different STM32 series.
  */
/**
  * @}
  */

/** @defgroup HRTIM_How_To_Use HRTIM How To Use
  * @{

  # HRTIMER Main features

  High resolution timer (HRTIM) peripheral essentially addresses digital power applications, such as switch mode power\n
  supplies, that require high PWM switching frequencies. It can generate up to twelve signals and to handle a large   \n
  variety of input signals for control, synchronization or protection purposes. Its modular architecture makes        \n
  possible to address several conversion topologies and multiple parallel converters, with the possibility to         \n
  reconfigure them during run-time.

  Main HRTIM features are listed below:
    - 7 timers (7x16 bits counters)
      - One master timer providing synchronization signals to the 6 timing units (timers A to F).
      - 6 timing units working either independently or coupled with the other timers, including the master timer.
    - 12 outputs that can be controlled by any timer (including the master timer).
      A total of 32 set and reset events are available per output.
    - 16 external events, available for any timing unit. External event global conditioning is \n
      common to all timing units but additional filtering capabilities can be customized at timing unit level.
    - 8 fault inputs allowing to disable the outputs in case of an abnormal operation.
    - Direct connections to built-in peripherals (Comparators, ADCs, DACs, general purpose timers).
    - External synchronization input/output.
    - Versatile output stage allowing to:
      - configure the output polarity,
      - configure the PWM idle and safe state levels,
      - insert a deadtime between 2 complementary PWM signals,
      - add a chopper modulation.
    - Burst mode controller that can take over the control of one or multiple timers in case of light-load operation.

  # How to use the HAL HRTIM driver

  ## Initialization

   ### HRTIM clock initialization
       The HRTIM clock source must be enabled in the reset and clock control unit (RCC).

   ### HRTIM I/O's initialization
       Alternate function configuration of the GPIO's connected to the HRTIM inputs/outputs.

       - HRTIM inputs:
         - HRTIM_SYNCIN - synchronization input
         - HRTIM_EVTx - External events
         - HRTIM_FLTx - Fault inputs

       - HRTIM outputs:
         - HRTIM_SYNCOUT - synchronization output
         - HRTIM_CHxy - main HRTIM timer outputs

       The HRTIM inputs are initialized first, prior to the HRTIM registers.

       The HRTIM outputs must be initialized after the HRTIM control registers programming, and once the counters are\n
       enabled. This is to ensure that the outputs states are correctly defined inside the HRTIM before passing the\n
       control from the GPIO circuitry to the HRTIM.

   ### Other peripherals initialization
       As listed below, the HRTIM interacts with many of the MCU peripherals. It is not mandatory to have all of them\n
       initialized to have the HRTIM operating.
       - Nested vectored interrupt controller (NVIC)
         - One interrupt vector per timer
         - One interrupt vector for HRTIM fault signaling
       - DMA controller
         - One DMA channel per timer
       - Comparators
         - Comparator output can be connected to an HRTIM external event or an HRTIM fault input.
       - ADCs
          - Analog to digital conversion can be triggered by the HRTIM. Reversely, ADC analog watchdogs can be\n
            connected to HRTIM external events.
       - DACs
          - Digital to analog conversion can be synchronized with HRTIM operation by means of HRTIM DAC triggers.
       - PLAY
         - PLAY outputs can be connected to HRTIM external events, or the HRTIM synchronization input\n
           or they can trigger the HRTIM registers update or the burst mode controller.
       - General purpose timers
         - GP-Timer's output trigger can be connected to an HRTIM external event, or the HRTIM synchronization input\n
           or it can trigger the HRTIM registers update or the burst mode controller.

  ## HRTIM initialization
     First HAL_HRTIM_Init() must be called to associate the physical HRTIM peripheral to the HRTIM handle. When\n
     needed the HAL_HRTIM_SetDMA() function can be called to associate a DMA channel to a timer (including the master\n
     timer).

  ## HRTIM DLL initialization
     This DLL must be calibrated at least once before high resolution can be used. The function HAL_HRTIM_Calibrate()\n
     DLL starts the DLL calibration process. It can be called during HRTIM operation if voltage or temperature\n
     conditions have changed. HAL_HRTIM_StartPeriodicDLLCalibration() enables periodic calibration. End of DLL\n
     calibration process can be checked by calling the HAL_HRTIM_PollForDLLCalibration() function.

  ## Callback functions registration

     The compilation flag USE_HAL_HRTIM_REGISTER_CALLBACKS when set to 1 allows the user to configure dynamically the\n
     driver callbacks.

     Use Function HAL_HRTIM_Register<Callback_name>() to register a callback.

     It takes as parameters the HAL peripheral handle, and a pointer to the user callback function.

     These functions allow to register following callbacks:

     - HRTIM DMA related callback functions registration:

       - HAL_HRTIM_RegisterDMAHalfCallback()         : Registered callback function is invoked when a DMA transfer is\n
                                                       half completed.
       - HAL_HRTIM_RegisterDMACpltCallback()         : Registered callback function is invoked when a DMA transfer is\n
                                                       completed.
       - HAL_HRTIM_RegisterDMAStopCallback()         : Registered callback function is invoked when a DMA transfer is\n
                                                       stopped.
       - HAL_HRTIM_RegisterDMAErrorCallback()        : Registered callback function is invoked when a DMA transfer\n
                                                       error is reported by the DMA controller.

     - HRTIM related callback functions registration:

       - HAL_HRTIM_RegisterFaultCallback()           : Registered callback function is invoked upon fault event\n
                                                       generation. This function takes the fault input identifier\n
                                                       as input argument.
       - HAL_HRTIM_RegisterSystemFaultCallback()     : Registered callback function is invoked upon system fault\n
                                                       detection.
       - HAL_HRTIM_RegisterBurstModePeriodCallback() : Registered callback function is invoked when the burst mode\n
                                                       controller is enabled, every time the burst mode period\n
                                                       completes.
       - HAL_HRTIM_RegisterSynchroCallback()         : Registered callback function is invoked upon reception of a\n
                                                       synchronization event.
       - HAL_HRTIM_DLLCalibrationCallback()          : Registered callback function is invoked at the end of the DLL\n
                                                       calibration process.

     - Timers related callback functions:

       - HAL_HRTIM_RegisterUpdateCallback()          : Registered callback function is invoked upon generation of a\n
                                                       register update request. This function takes the timer\n
                                                       identifier as input argument.
       - HAL_HRTIM_RegisterRepetitionCallback()      : Registered callback function is invoked upon repetition event\n
                                                       generation. This function takes the timer identifier as input\n
                                                       argument.
       - HAL_HRTIM_RegisterResetCallback()           : Registered callback function is invoked upon reset or roll/over\n
                                                       event generation. This function takes the timer identifier as\n
                                                       input argument.
       - HAL_HRTIM_RegisterDelayedProtectionCallback() : Registered callback function is invoked when the protection\n
                                                       is triggered. This function takes the timer identifier as\n
                                                       input argument.
       - HAL_HRTIM_RegisterXbarOvrTriggerCallback()  : Registered callback function is invoked when the crossbar\n
                                                       mode is triggered. This function takes the timer identifier as\n
                                                       input argument.
       - HAL_HRTIM_RegisterXbarOvrRearmDelayCallback() : Registered callback function is invoked when the crossbar\n
                                                       override rearm delay elapsed when at least one of the 2 outputs\n
                                                       is configured to Delayed fault force mode
                                                       (see @ref HAL_HRTIM_OUT_SetXbarOvrForceMode and\n
                                                       @ref HAL_HRTIM_TIM_SetXbarOvrDelay). This function takes the \n
                                                       timer identifier as input argument.

     - Capture/compare related callback functions:

       - HAL_HRTIM_RegisterCompareMatchCallback()    : Registered callback function is invoked when a compare match\n
                                                       event is generated. This function takes the timer and the\n
                                                       compare unit identifiers as input arguments.
       - HAL_HRTIM_RegisterCaptureCallback()         : Registered callback function is invoked when a capture event\n
                                                       is generated. This function takes the timer and the capture\n
                                                       unit identifiers as input arguments.

     - HRTIM outputs related callback functions:

       - HAL_HRTIM_RegisterOutputSet_callback()      : Registered callback function is invoked when the output
                                                       transition from its INACTIVE to its ACTIVE level. This function\n
                                                       takes HRTIM output identifier as input argument.
       - HAL_HRTIM_RegisterOutputReset_callback()    : Registered callback function is invoked when the output\n
                                                       transition from its ACTIVE to its INACTIVE level. This function\n
                                                       takes HRTIM output identifier as input argument.

     The table below maps the callback names to their default handlers and registration functions:

     Callback name               | Default value                       | Callback registration function
     --------------------------- | ----------------------------------- | ---------------------------
     DMAHalfCallback             | HAL_HRTIM_DMAHalfCallback           | HAL_HRTIM_RegisterDMAHalfCallback
     DMACpltCallback             | HAL_HRTIM_DMACpltCallback           | HAL_HRTIM_RegisterDMACpltCallback
     DMAStopCallback             | HAL_HRTIM_DMAStopCallback           | HAL_HRTIM_RegisterDMAStopCallback
     DMAErrorCallback            | HAL_HRTIM_DMAErrorCallback          | HAL_HRTIM_RegisterDMAErrorCallback
     FaultCallback               | HAL_HRTIM_FaultCallback             | HAL_HRTIM_RegisterFaultCallback
     SystemFaultCallback         | HAL_HRTIM_SystemFaultCallback       | HAL_HRTIM_RegisterSystemFaultCallback
     BurstModePeriodCallback     | HAL_HRTIM_BurstModePeriodCallback   | HAL_HRTIM_RegisterBurstModePeriodCallback
     DLLCalibrationCallback      | HAL_HRTIM_DLLCalibrationCallback    | HAL_HRTIM_RegisterDLLCalibrationCallback
     UpdateCallback              | HAL_HRTIM_UpdateCallback            | HAL_HRTIM_RegisterUpdateCallback
     RepetitionCallback          | HAL_HRTIM_RepetitionCallback        | HAL_HRTIM_RegisterRepetitionCallback
     ResetCallback               | HAL_HRTIM_ResetCallback             | HAL_HRTIM_RegisterResetCallback
     DelayedProtectionCallback   | HAL_HRTIM_DelayedProtectionCallback | HAL_HRTIM_RegisterDelayedProtectionCallback
     XbarOvrTriggerCallback      | HAL_HRTIM_XbarOvrTriggerCallback    | HAL_HRTIM_RegisterXbarOvrTriggerCallback
     XbarOvrRearmDelayCallback   | HAL_HRTIM_XbarOvrRearmDelayCallback | HAL_HRTIM_RegisterXbarOvrRearmDelayCallback
     CompareMatchCallback        | HAL_HRTIM_CompareMatchCallback      | HAL_HRTIM_RegisterCompareMatchCallback
     CaptureCallback             | HAL_HRTIM_CaptureCallback           | HAL_HRTIM_RegisterCaptureCallback
     OutputSet_callback          | HAL_HRTIM_OutputSet_callback        | HAL_HRTIM_RegisterOutputSet_callback
     OutputReset_callback        | HAL_HRTIM_OutputReset_callback      | HAL_HRTIM_RegisterOutputReset_callback

     By default, after HAL_HRTIM_Init() has been called, all interrupt callbacks are set to the corresponding weak\n
     functions HAL_HRTIM_*Callback().

     Callbacks can be registered in HAL_HRTIM_STATE_INIT state only.

     When the compilation flag USE_HAL_HRTIM_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration\n
     feature is not available and all callbacks are set to the corresponding weak functions.

  ## HRTIM configuration
     This configuration step consists in configuring global HRTIM resources/features determining the overall HRTIM\n
     peripheral behavior.

   ### HRTIM global interrupts configuration
       Interrupt sources for the whole HRTIM:
         - System fault and fault 1 to 6,
         - Burst mode period completed.
         - End of DLL calibration.
       Interrupt sources for a timer:
         - Compare 1 to 4 event (master timer an timing units),
         - Registers update (master timer an timing units),
         - Repetition event update (master timer an timing units),
         - Synchronization event (master timer only),
         - Delayed protection triggered (timing units only),
         - Counter reset or roll-over event (timing units only),
         - Output 1 and output 2 reset (timing units only),
         - Output 1 and output 2 set (timing units only),
         - Capture 1 and 2 events.
         - Crossbar override triggered.
         - Crossbar override rearm delay elapsed.
        The HRTIM global interrupt sources and the timer related interrupt sources to enable\n
        are specified by calling HAL_HRTIM_SetConfigInterrupts(). The HRTIM global interrupt\n
        sources are enabled from within HAL_HRTIM_SetConfigInterrupts() while timer related interrupts sources\n
        are enabled when the timer is started in interrupt mode (see HAL_HRTIM_TIM_Start_IT()).\n

   ### HRTIM DMA configuration
       DMA requests for a timer:
         - Compare 1 to 4 event (master timer an timing units),
         - Registers update (master timer an timing units),
         - Repetition event update (master timer an timing units),
         - Synchronization event (master timer only),
         - Delayed protection triggered (timing units only),
         - Counter reset or roll-over event (timing units only),
         - Output 1 and output 2 reset (timing units only),
         - Output 1 and output 2 set (timing units only),
         - Capture 1 and 2 events.
         - Crossbar override triggered.
         - Crossbar override rearm delay elapsed.
       The individual DMA requests are ORed into 7 channels as follows:
         - 1 channel for the master timer,
         - 1 channel per timing unit.

       The handle of the DMA channel associated to a timer is registered in the HRTIM handle by calling\n
       HAL_HRTIM_SetDMA(). The information needed to configure a DMA channel when a timer is started in DMA mode,\n
       i.e. the DMA requests to enable the source address, the destination address and the size of the DMA transfer\n
       are stored inside a configuration structure housed by the application. The pointer to the DMA configuration of\n
       a timer is registered in the HRTIM handle by calling HAL_HRTIM_SetConfigDMA(). When the timer is started in\n
       DMA mode, this pointer is used to recover information needed to enable the DMA request(s) and start the DMA\n
       transfer.

   ### HRTIM external events
       The function HAL_HRTIM_EEV_SetConfig() configures the global settings for an external event, including the\n
       source, sensitivity, digital filter and fast mode.\n
       Here are the key points:\n
       - Filter choice is limited to HAL_HRTIM_FDIV1 for external events 6 to 10 and 11 to 13.
       - Mode choice is limited to HAL_HRTIM_EEV_SYNCHRONOUS for 1 to 5 and 14 to 16.
       - Sampling Clock Frequency: The frequency of the sampling clock used for digital filtering (fEEVS) is\n
                                   determined by a programmable prescaler, which can be configured using\n
                                   HAL_HRTIM_EEV_SetPrescaler().

   ### HRTIM Faults
       The function HAL_HRTIM_FLT_SetConfig() configures the global settings for a fault input, including the\n
       source, polarity, and digital filter. The frequency of the sampling clock used for digital filtering (fFLTS)\n
       is determined by a programmable prescaler, which can be configured using HAL_HRTIM_FLT_SetPrescaler().

   ### HRTIM outputs
       The function HAL_HRTIM_OUT_SetConfig() configures an HRTIM output, including set and reset events,\n
       polarity, and output levels (ACTIVE or INACTIVE) when the output is in IDLE or FAULT state. Outputs can be\n
       paired for deadtime insertion by calling HAL_HRTIM_TIM_EnableDeadtime(), which generates complementary\n
       signals on the two outputs from a single reference PWM waveform.

   ### HRTIM Synchronization
       The HRTIM can act as a slave unit, synchronized with other internal or external hardware resources.\n
       The synchronization input source is selected by calling HAL_HRTIM_SetSynchroInputSource(). You can choose\n
       how a timer reacts to a synchronization event (counter reset, counter start, or both) by calling
       HAL_HRTIM_TIM_SetSlaveMode().

       The HRTIM can also act as a master unit to synchronize on-chip or off-chip resources. The event triggering a\n
       pulse generation on the synchronization output and the pulse polarity are configured by calling\n
       HAL_HRTIM_SetSynchroOutput().

   ### ADC triggers
       The HRTIM supports 10 independent triggers for both the regular and injected sequencers of the ADCs.\n
       The function HAL_HRTIM_SetADCSynchro() allows you to select the source(s) of an ADC trigger. A post-scaling\n
       unit allows reducing the ADC trigger rate, which can be adjusted by calling HAL_HRTIM_SetADCPostscaler().

   ### DAC triggers
       The HRTIM offers DAC triggers, allowing DAC values to be updated synchronously with update events from the\n
       master and/or slave timers. For each timer, you can select the DAC trigger output where the timer update event\n
       is propagated by calling HAL_HRTIM_TIM_SetDACTrigger().

       Each timing unit (Timer A..F) features two DAC trigger outputs for synchronizing a sawtooth wave generated by a\n
       DAC with a PWM signal:
         - One trigger to reset the sawtooth.
         - Another trigger to decrease the DAC values.

       Both triggers can be configured by calling HAL_HRTIM_TIM_SetDualChannelDACTriggers(). Enable dual channel\n
       DAC triggers by calling HAL_HRTIM_TIM_EnableDualChannelDAC().

       @note The Dual channel DAC trigger mode must not be used simultaneously with other modes using CMP2 (auto\n
       delayed mode, interleaved and balanced idle modes).

  ## Timers configuration
     The following steps customize the functioning of a timer. Some steps apply to both the master timer and timing\n
     units, while others are specific to timing units (timers A..F).

   ### Time base (master and timers A..F)
       The function HAL_HRTIM_TIM_SetConfig() handles the configuration of a timer. This function must be called\n
       before any other timer-related configuration functions.

       The timer configuration structure specifies:
         - Counter period
         - Repetition counter value
         - Prescaler value
         - Timer operating mode (continuous or single shot)
         - Counter mode (up or up-down)

   ### Registers update (master and timers A..F)
       Some timer configuration registers are shadowed with preload registers, allowing on-the-fly waveform\n
       modifications without abnormal transients. Enable preload mode by calling HAL_HRTIM_TIM_EnablePreload().\n
       When enabled, write accesses to the timer's configuration registers are done to the preload registers, which\n
       are transferred to the active registers after an update request. Specify the update event source by calling\n
       HAL_HRTIM_TIM_SetUpdateSource().\n
       The update request generation can be synchronized with an update event, on-chip sources (general-purpose\n
       timers), or a DMA burst operation. The function HAL_HRTIM_TIM_SetUpdateGating() allows to select one or the\n
       other option the desired update request generation option.\n

       Generate an update event by calling HAL_HRTIM_Update(). Temporarily disable update event generation by\n
       calling HAL_HRTIM_TIM_DisablePreload() and re-enable it later by calling HAL_HRTIM_TIM_EnablePreload().

   ### Combined external events (timers A..F)
       External events can be combined and used for different purposes:
         - Output 1 and output 2 set / reset events (see @ref HAL_HRTIM_OUT_SetConfig),
         - Delayed protection configuration (see @ref HAL_HRTIM_TIM_SetConfigDelayedProtection),
         - Counter reset (see @ref HAL_HRTIM_TIM_SetResetSource),
         - Capture 1 & 2 triggers (see @ref HAL_HRTIM_TIM_SetCaptureTrigger),
         - Burst mode trigger (see @ref HAL_HRTIM_SetConfigBurstMode),
         - External event counter source (see @ref HAL_HRTIM_TIM_SetEventCounter),
         - Crossbar override trigger (see @ref HAL_HRTIM_TIM_SetConfigXbarOvr).

       The source(s) of combined external event can be configured differently  for each timing unit by calling\n
       HAL_HRTIM_TIM_SetCombinedEventSource().

   ### Counter reset (timers A..F)
       The timer's counter can be reset before reaching the period value (variable frequency operation). The events\n
       triggering the counter reset are specified by calling HAL_HRTIM_TIM_SetResetSource(). Note that counter can\n
       be reset by software anytime by calling HAL_HRTIM_TIM_Reset().

   ### Compare units (master and timers A..F)
       Compare match events can be used for various purposes:
         - Set or reset an output (HAL_HRTIM_OUT_SetConfig()),
         - Reset the counter of a timer (HAL_HRTIM_TIM_SetResetSource()),
         - Trigger a capture (HAL_HRTIM_TIM_SetCaptureTrigger()),
         - Trigger the burst mode controller (HAL_HRTIM_SetConfigBurstMode()),
         - Trigger an ADC conversion (HAL_HRTIM_SetADCSynchro())
         - Generate dual channel DAC trigger (HAL_HRTIM_TIM_SetDualChannelDACTriggers()).

       Set the compare value of a compare unit by calling HAL_HRTIM_TIM_SetCompareValue().

       @note Some compare units can be reserved by the hardware and become unavailable for other purposes.
       The table below lists such constraints:

       Reserved compare units       | Functioning mode    | Concerned HAL function
    ------------------------------- | ------------------- | ----------------------------------------------------------
       CMP1 and/or CMP2 and/or CMP3 | Interleaved mode    | HAL_HRTIM_TIM_SetInterleavedMode()
       CMP2                         | Triggered half mode | HAL_HRTIM_TIM_SetTriggeredHalfMode()
       CMP4                         | Balanced idle mode  | HAL_HRTIM_TIM_SetConfigDelayedProtection()
       CMP1 or CMP3                 | Autodelayed mode    | HAL_HRTIM_TIM_SetAutoDelayedMode()
       CMP2                         | Dual channel DAC    | HAL_HRTIM_TIM_EnableDualChannelDAC()

   ### Capture units (timers A..F)
       Specify the events triggering a capture by calling HAL_HRTIM_TIM_SetCaptureTrigger(). Retrieve captured\n
       information (capture value and direction) by calling HAL_HRTIM_TIM_GetCapture().

   ### Event filtering (timers A..F)
       Apply specific filtering schemes (blanking or windowing) to external events used in a timing unit by calling\n
       HAL_HRTIM_TIM_SetEventFilter(). Filter out events based on the number of occurrences using the external\n
       event counter, configured by calling HAL_HRTIM_TIM_SetEventCounter() and enabled by calling\n
       HAL_HRTIM_TIM_EnableEventCounter().

   ### Fault filtering (timers A..F)
       Filter out faults based on the number of occurrences using the fault counter, which allows the fault to be\n
       considered only after a programmable number of occurrences (1 to 32). Configure the fault counter by calling\n
       HAL_HRTIM_FLT_SetCounter().

   ### Deadtime (timers A..F)
       Insert deadtime to generate complementary signals on the two outputs from a single reference PWM waveform.\n
       Configure rising and falling deadtime values and signs by calling HAL_HRTIM_TIM_SetConfigDeadtime().\n
       Enable deadtime by calling HAL_HRTIM_TIM_EnableDeadtime(). For functional safety, write-protect the\n
       values or signs of the rising/falling deadtimes by calling HAL_HRTIM_TIM_LockDeadtime().
       Additionally to regular deadtime mode two alternative deadtime options are available to handle situations where\n
       the signals are independently defined. The desired deadtime mode is selected by calling
       HAL_HRTIM_TIM_SetDeadtimeMode(). If not called, regular deadtime insertion mode applies (when enabled).

  ## Specific modes
     The HRTIM offers specific modes and features to offload the CPU and to address various conversion topologies.

   ### Burst mode controller
       The burst mode controller can take over the control of any of the 10 PWM outputs.

       It is configured by calling HAL_HRTIM_SetConfigBurstMode(). The burst mode configuration consists of defining:
       - the source of the burst mode controller counter clock,
       - the number of periods during which output are forced to their INACTIVE level (idle period),
       - the burst repetition rate (period),
       - the events triggering the burst mode operation,
       - the burst mode prescaler (if the main HRTIM clock is selected as the burst mode clock).\n
         In this case the burst mode controller counter clock (fBRST) ranges from fHRTIM to fHRTIM / 32768.

       The timer output programming for burst mode is handled by HAL_HRTIM_OUT_SetBurstMode(). Following options\n
       are proposed:
         - output isn't affected by the burst mode operation,
         - output is immediately forced to its INACTIVE level every time during the burst idle period,
         - output is forced to its INACTIVE level after a deadtime (delayed entry) every time the burst idle period is\n
           entered. In that case deatime is specified by HAL_HRTIM_TIM_SetConfigDeadtime() and it must be enabled\n
           for the timing unit by calling HAL_HRTIM_TIM_EnableDeadtime().

       During the burst mode operation, the timer counter clock can be maintained or stopped and kept in reset state\n
       during the burst idle period. HAL_HRTIM_TIM_SetBurstMode() allows to select one or the other option.

   ### Interleaved modes
       Interleaved modes automatically update the compare registers when a new period is programmed\n
       (HAL_HRTIM_TIM_SetPeriod()).

       Select an interleaved mode by calling HAL_HRTIM_TIM_SetInterleavedMode():
         - Disabled,
         - Dual interleave (half-mode),
         - Triple interleaved,
         - Quad interleaved.

   ### Push-pull mode
       In push-pull mode, a timer's outputs are alternately enabled and put in idle state to maintain balance between\n
       the two PWM outputs. Enable push-pull mode by calling HAL_HRTIM_TIM_EnablePushPull().\n
       HAL_HRTIM_TIM_GetPushPullCurrentStatus() can be called to know on which output the signal is currently active.\n
       Note that both outputs must have identical waveforms for balanced operation (HAL_HRTIM_OUT_SetConfig()).\n
       In push-pull mode, HAL_HRTIM_TIM_SetPushPullAdcTrigger() can be called  to have the ADC triggers issued only\n
       when output 1 (resp. outpu2) is active.\n

   ### Auto delayed mode
       Auto delayed mode allows an output to change upon a capture event with a programmable delay or after a timeout.\n
       Compare unit 2 is associated with capture unit 1 and compare unit 4 is associated with capture unit 2.\n
       auto delayed mode by calling HAL_HRTIM_TIM_SetAutoDelayedMode(). Set compare values by calling\n
       Configure HAL_HRTIM_TIM_SetCompareValue().

       @note When compare unit 2 or compare unit 4 operate in autodelayed mode, some capture/compare units are\n
       reserved by the hardware and become unavailable for other purposes.

       The table below lists such constraints when autodelayed mode in enabled on compare unit 2:

       Reserved capture/compare units | Autodelayed mode
    --------------------------------- | ----------------------
       CPT1                           | Enabled
       CPT1 and CMP1                  | Enabled with timeout CMP1
       CPT2 and CMP3                  | Enabled with timeout CMP3

       The table below lists such constraints when autodelayed mode in enabled on compare unit 4:

       Reserved capture/compare units | Autodelayed mode
    --------------------------------- | ----------------------
       CPT2                           | Enabled
       CPT2 and CMP1                  | Enabled with timeout CMP1
       CPT2 and CMP3                  | Enabled with timeout CMP3

   ### Triggered-half mode
       Enable triggered-half mode by calling HAL_HRTIM_TIM_SetTriggeredHalfMode(). In this mode, the switching\n
       period of the timing unit acting as the master converter is captured, divided by 2, and stored in the compare 2\n
       register by hardware. The compare 2 event can then trigger a second timing unit managing the slave converter.

       @note The triggered-half mode must not be used simultaneously with other modes using CMP2 (dual channel DAC\n
       trigger, interleaved and balanced idle modes).

   ### Chopper mode
       When chopper mode is enabled, a programmable carrier waveform is superimposed on the active PWM signal.\n
       Configure the high-frequency carrier signal parameters by calling HAL_HRTIM_TIM_SetConfigChopper().\n
       Enable chopper mode by calling HAL_HRTIM_TIM_EnableChopper().

   ### DMA Burst
       The DMA burst mode is used to dynamically re-configure the HRTIM. The DMA burst operation is triggered by a\n
       DMA request generated by the timer used as DMA burst source.

       Typical sequence to configure and start a DMA burst:
         - Initialize the DMA channel of the timer used as the DMA burst source (HAL_DMA_Init()).
         - Configure the timer used as the DMA burst source (HAL_HRTIM_TIM_SetConfig().
         - Fill the memory buffer used to reconfigure the HRTIM registers.
         - Fill the DMA burst configuration structure:
            . Select the timer used as the DMA burst source.
            . Select the source of the DMA request triggering the DMA burst (e.g., HAL_HRTIM_DMA_UPDATE).
            . Select the HR-Timer register(s) to be written by the DMA.
         - Configure the DMA burst (HAL_HRTIM_SetConfigDMABurst()).
         - Initiate the DMA burst operation (HAL_HRTIM_StartDMABurst()).
         - Start the timer used as the DMA burst source (HAL_HRTIM_TIM_Start()).

         The DMA burst operation starts when the timer used as DMA burst source generates a DMA request. The transfer\n
         from the memory buffer to the HRTIM registers is then entirely managed by the HRTIM DMA burst controller.\n
         A callback function is invoked upon completion.

         The function HAL_HRTIM_TIM_SetUpdateGating() allows to select how the registers are updated versus a DMA\n
         burst operation when the preload mode is enabled (HAL_HRTIM_TIM_EnablePreload()). When the preload\n
         mode is disabled, HRTIM registers are updated as soon as they are written by the DMA.

  ## Delayed Protection
     The HRTIM features specific protection schemes for resonant converters, allowing delayed shutdown of PWM\n
     outputs either once the active pulse is completed (delayed idle mode) or once a push-pull period is completed\n
     (balanced idle mode).

     Protection is triggered by specific events (Events F or G for timers A, B, and C, \n
     and events H or I for timers D, E, and F). Configure and enable delayed protection mode by calling\n
     HAL_HRTIM_TIM_EnableDelayedProtection().

     ### Delayed idle mode:
         Delayed idle mode can be applied to a single output or both outputs. Configure it by calling\n
         HAL_HRTIM_TIM_SetConfigDelayedProtection().

         To exit from delayed idle:
           - Ensure the outputs are in their INACTIVE level (HAL_HRTIM_OUT_GetRawLevel()).
           - Re-enable the output by calling HAL_HRTIM_OUT_Enable().

     ### Balanced idle mode:
         Before enabling balanced idle mode at the output level (HAL_HRTIM_TIM_SetConfigDelayedProtection()):
           - Ensure the timer operates in continuous mode (HAL_HRTIM_TIM_SetConfig()).
           - Enable push-pull mode (HAL_HRTIM_TIM_EnablePushPull()).
           - Disable auto-delayed mode (HAL_HRTIM_TIM_SetAutoDelayedMode()).
           - Set compare 4 value to 0 (HAL_HRTIM_TIM_SetCompareValue()).

         To exit from Balanced idle:
         Assumption: protection was triggered while output 1 was active (HAL_HRTIM_TIM_GetPushPullIdleStatus()\n
         returns HAL_HRTIM_PUSHPULL_IDLE_OUT1_OUT2).\n
         Initiate the re-start sequence for output 1 first and re-enable outputs (HAL_HRTIM_OUT_Enable()) when the\n
         current push-pull status indicates the signal is applied on output 1\n
         (HAL_HRTIM_TIM_GetPushPullCurrentStatus() returns HAL_HRTIM_PUSHPULL_CURRENT_OUT1_OUT2).

  ## Crossbar override
     It is possible to override the output crossbar programming and take over the output control to force a level\n
     based on a fixed setting or based on a given external.

    At timing unit level, the crossbar override is configured by calling HAL_HRTIM_TIM_SetConfigXbarOvr(). Crossbar\n
    override mode is entered when one of the configured triggers is active.

    The crossbar override mode provides several options defined independently for each output by calling\n
    HAL_HRTIM_OUT_SetXbarOvrForceMode(). When Force on event mode is selected, the event(s) forcing the output level\n
    is(are) selected by calling HAL_HRTIM_OUT_SetXbarOvrForcingEvents(). When delayed fault operation is selected,\n
    delay 1 and delay 2 can be configured by calling HAL_HRTIM_TIM_SetXbarOvrDelay().

    Once configured, the crossbar override can be enabled by calling HAL_HRTIM_TIM_EnableXbarOvr() or disabled by\n
    calling HAL_HRTIM_TIM_DisableXbarOvr().

    When the crossbar override operates in latched mode, crossbar override mode is maintained until a software\n
    intervention to disengage it. This can be done when the triggering condition has disappeared by calling \n
    HAL_HRTIM_TIM_RearmXbarOvr(). The function HAL_HRTIM_TIM_GetXbarOvrTriggerStatus() can be called to check whether\n
    the crossbar override mode can be rearmed.

    It is also possible to have the DAC values updated synchronously with the crossbar override mode triggering\n
    when dual channel DAC crossbar override is enabled. This is achieved by calling\n
    HAL_HRTIM_TIM_EnableDualDACXbarOvr().

  ## HRTIM waveform generation control

   ### Enable/disable HRTIM outputs
       HRTIM outputs can be enabled and disabled at any time by calling HAL_HRTIM_OUT_Enable() or\n
       HAL_HRTIM_OUT_Disable() respectively. Both functions can control a single output or several outputs\n
       simultaneously.

   ### Start/stop Timers
       The timers can be started and stopped at any time by calling HAL_HRTIM_TIM_Start*() or HAL_HRTIM_TIM_Stop*()\n
       respectively. These functions can control a single timer or several timers simultaneously.

       Three execution modes are proposed:

       - Polling mode: timer's interrupt sources and DMA requests are disabled.

         - Control functions:
           - HAL_HRTIM_TIM_Start()
           - HAL_HRTIM_TIM_Stop()

       - Interrupt mode: timer's interrupt sources specified during the timer's configuration\n
         (@ref HAL_HRTIM_SetConfigInterrupts) are enabled.\n

         - Prerequisite:
           - Enable the Timer's interrupt vector (HAL_CORTEX_NVIC_EnableIRQ()).

         - Control functions:
           - HAL_HRTIM_TIM_Start_IT()
           - HAL_HRTIM_TIM_Stop_IT()

       - DMA mode: timer's DMA requests sources specified during the timer's configuration\n
         (@ref HAL_HRTIM_SetConfigDMA) are enabled.

         - Prerequisite:
           - Initialize the DMA channel(s) associated with the timer(s) (HAL_DMA_Init).
           - Enable the interrupt vector of the DMA channel associated with the timer (HAL_CORTEX_NVIC_EnableIRQ()).
           - Ensure the DMA configuration data is available.

         - Control functions:
           - HAL_HRTIM_TIM_Start_DMA()
           - HAL_HRTIM_TIM_Stop_DMA()

  ## On-the-fly changes

   ### Force output level
       Force an HRTIM output to its ACTIVE or INACTIVE level by calling HAL_HRTIM_OUT_Set()\n
        or HAL_HRTIM_OUT_Reset() respectively.

   ### Force registers update
       When preload mode is enabled (HAL_HRTIM_TIM_EnablePreload()), force an immediate update of the registers by\n
       calling HAL_HRTIM_Update(). This can be done for several timers simultaneously.

   ### Force counter reset
       Force a reset of the counter for one or several timers simultaneously by calling HAL_HRTIM_TIM_Reset().

   ### Force capture
       Trigger a capture on a capture unit by calling HAL_HRTIM_TIM_Capture().

   ### Trigger burst mode operation
       When burst mode is enabled (HAL_HRTIM_EnableBurstMode()), start the burst mode operation immediately by\n
       calling HAL_HRTIM_StartBurstMode().

   ### Swap outputs
       Swap the timer's outputs by calling HAL_HRTIM_TIM_EnableSwapMode(), connecting output 1 signal to the\n
       output 2 pin and vice versa.

   ### Period change
       To change the period of a PWM signal, use the function HAL_HRTIM_TIM_SetPeriod(). The new period value is\n
       applied based on the preload mode setting:\n
       - Immediate Application: If preload mode is disabled (HAL_HRTIM_TIM_DisablePreload()),\n
         the new period value is applied immediately.
       - Delayed Application: If preload mode is enabled (HAL_HRTIM_TIM_EnablePreload()),\n
         the new period value is applied at the next update request.

   ### Duty cycle change
       The function HAL_HRTIM_TIM_SetCompareValue() is used to change the duty cycle of a PWM signal. The new\n
       compare value is applied based on the preload mode setting:\n
       - Immediate Application: If preload mode is disabled (HAL_HRTIM_TIM_DisablePreload()),\n
         the new compare value is applied immediately.
       - Delayed Application: If preload mode is enabled (HAL_HRTIM_TIM_EnablePreload()),\n
         the new compare value is applied at the next update request.

   ### Disable update request
       When preload mode is enabled using HAL_HRTIM_TIM_EnablePreload(), it is possible to temporarily disable\n
       the transfer of data from preload registers to active registers by calling HAL_HRTIM_DisableUpdate().\n
       Call HAL_HRTIM_EnableUpdate() to re-enable this transfer later. This process allows to disable and\n
       resume updates for multiple timers simultaneously.

  ## Status and errors
     - HAL_HRTIM_GetState() returns the overall state of the HRTIM.
     - HAL_HRTIM_TIM_GetState() returns the state of a specific timer
     - HAL_HRTIM_OUT_GetStatus() returns the state of an HRTIM output.
     - HAL_HRTIM_GetBurstModeOperatingStatus() returns the state of the burst mode controller.
  */
/**
  * @}
  */

/** @defgroup HRTIM_Configuration_Table HRTIM Configuration Table
  * @{
# Configuration inside the HRTIM driver

Config defines                  | Where | Default value | Note
------------------------------- | ----- | ------------- | ----------------------------------------------------------
USE_HAL_HRTIM_MODULE                    | (1) | 1                 | HAL HRTIM module is enabled
USE_HAL_HRTIM_MODULE                    | (1) | 1                 | HAL HRTIM module is enabled
USE_HAL_HRTIM_DMA                       | (1) | 1                 | Enable the DMA code inside HRTIM
USE_HAL_HRTIM_REGISTER_CALLBACKS        | (1) | 0                 | Enable register callback feature
USE_HAL_HRTIM_CLK_ENABLE_MODEL          | (1) | HAL_CLK_ENABLE_NO | Enable the gating of the peripheral clock
USE_HAL_CHECK_PARAM                     | (1) | 0                 | Enable run time parameter check
USE_HAL_CHECK_PROCESS_STATE             | (1) | 0                 | Enable atomic access to process state check
USE_ASSERT_DBG_PARAM                    | (2) | NONE              | Enable the params assert
USE_ASSERT_DBG_STATE                    | (2) | NONE              | Enable the state assert
USE_HAL_HRTIM_GLOBAL_CALLBACKS          | (1) | 1 | Enable HRTIM global events  callback functions support
USE_HAL_HRTIM_TIMER_CALLBACKS           | (1) | 1 | Enable timer events callback functions support
USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS | (1) | 1 | Enable capture/compare unit events callback functions support
USE_HAL_HRTIM_OUTPUT_CALLBACKS          | (1) | 1 | Enable HRTIM output events callback functions support
USE_HAL_HRTIM_XBAR_OVR_CALLBACKS        | (1) | 1 | Enable crossbar override events callback functions support
(1) from hal_conf.h\n
(2) from PreProcessor env
  */
/**
  * @}
  */

/* Private typedefs ----------------------------------------------------------*/
/** @defgroup HRTIM_Private_Types HRTIM Private Types
  *  @{
  */
/** function pointer type matching the signature of the LL_HRTIM functions used to set the roll over mode */
typedef void (*hrtim_set_rollover_mode_func_t)(const HRTIM_TypeDef *, uint32_t, uint32_t);

/** function pointer type matching the signature of the LL_HRTIM functions used to get the roll over mode */
typedef uint32_t (*hrtim_get_rollover_mode_func_t)(const HRTIM_TypeDef *, uint32_t);
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup HRTIM_Private_Constants  HRTIM Private Constants
  *  @{
  */
/** Total number of timing units (Timer A to F) */
#define HRTIM_TIMING_UNITS_NB (HRTIM_TIMERS_NB - 1)

/** Number of external events */
#define HRTIM_EVENTS_NB 10U

/** All crossbar override forcing events */
#define TIM_ALL_XBAR_OVR_FORCING_EVENTS (HAL_HRTIM_XBAR_OVR_FORCING_EEVA   \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVB \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVC \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVD \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVE \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVF \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVG \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVH \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVI \
                                         | HAL_HRTIM_XBAR_OVR_FORCING_EEVJ)

/** All fault inputs */
#define HRTIM_ALL_FAULTS (HAL_HRTIM_FLT1        \
                          | HAL_HRTIM_FLT2      \
                          | HAL_HRTIM_FLT3      \
                          | HAL_HRTIM_FLT4      \
                          | HAL_HRTIM_FLT5      \
                          | HAL_HRTIM_FLT6      \
                          | HAL_HRTIM_FLT7      \
                          | HAL_HRTIM_FLT8      \
                          | HAL_HRTIM_FLT1_FLT2 \
                          | HAL_HRTIM_FLT2_FLT3 \
                          | HAL_HRTIM_FLT3_FLT4 \
                          | HAL_HRTIM_FLT4_FLT5 \
                          | HAL_HRTIM_FLT5_FLT6 \
                          | HAL_HRTIM_FLT6_FLT7 \
                          | HAL_HRTIM_FLT7_FLT8)

/** All HRTIM outputs inputs */
#define HRTIM_ALL_OUTPUTS (HAL_HRTIM_CHA1   \
                           | HAL_HRTIM_CHA2 \
                           | HAL_HRTIM_CHB1 \
                           | HAL_HRTIM_CHB2 \
                           | HAL_HRTIM_CHC1 \
                           | HAL_HRTIM_CHC2 \
                           | HAL_HRTIM_CHD1 \
                           | HAL_HRTIM_CHD2 \
                           | HAL_HRTIM_CHE1 \
                           | HAL_HRTIM_CHE2 \
                           | HAL_HRTIM_CHF1 \
                           | HAL_HRTIM_CHF2)

/** All timers (including the master timer) */
#define HRTIM_ALL_TIMERS (HAL_HRTIM_MASTER   \
                          | HAL_HRTIM_TIMA   \
                          | HAL_HRTIM_TIMB   \
                          | HAL_HRTIM_TIMC   \
                          | HAL_HRTIM_TIMD   \
                          | HAL_HRTIM_TIME   \
                          | HAL_HRTIM_TIMF)

/** All timing units (timers A to F) */
#define HRTIM_ALL_TIMING_UNITS (HAL_HRTIM_TIMA     \
                                | HAL_HRTIM_TIMB   \
                                | HAL_HRTIM_TIMC   \
                                | HAL_HRTIM_TIMD   \
                                | HAL_HRTIM_TIME   \
                                | HAL_HRTIM_TIMF)

/** HRTIM global interrupts */
#define HRTIM_CLOBAL_INTERRUPTS (HAL_HRTIM_OPT_IT_FLT1     \
                                 | HAL_HRTIM_OPT_IT_FLT2   \
                                 | HAL_HRTIM_OPT_IT_FLT3   \
                                 | HAL_HRTIM_OPT_IT_FLT4   \
                                 | HAL_HRTIM_OPT_IT_FLT5   \
                                 | HAL_HRTIM_OPT_IT_FLT6   \
                                 | HAL_HRTIM_OPT_IT_FLT7   \
                                 | HAL_HRTIM_OPT_IT_FLT8   \
                                 | HAL_HRTIM_OPT_IT_SYSFLT \
                                 | HAL_HRTIM_OPT_IT_BURST_MODE_PERIOD \
                                 | HAL_HRTIM_OPT_IT_DLL_CALIBRATION)

/** Master timer interrupts */
#define HRTIM_MASTER_INTERRUPTS (HAL_HRTIM_OPT_IT_CMP1         \
                                 | HAL_HRTIM_OPT_IT_CMP2       \
                                 | HAL_HRTIM_OPT_IT_CMP3       \
                                 | HAL_HRTIM_OPT_IT_CMP4       \
                                 | HAL_HRTIM_OPT_IT_REPETITION \
                                 | HAL_HRTIM_OPT_IT_SYNCHRO    \
                                 | HAL_HRTIM_OPT_IT_UPDATE)

/** Timing unit interrupts */
#define HRTIM_TIMING_UNIT_INTERRUPTS (HAL_HRTIM_OPT_IT_CMP1               \
                                      | HAL_HRTIM_OPT_IT_CMP2             \
                                      | HAL_HRTIM_OPT_IT_CMP3             \
                                      | HAL_HRTIM_OPT_IT_CMP4             \
                                      | HAL_HRTIM_OPT_IT_REPETITION       \
                                      | HAL_HRTIM_OPT_IT_UPDATE           \
                                      | HAL_HRTIM_OPT_IT_CPT1             \
                                      | HAL_HRTIM_OPT_IT_CPT2             \
                                      | HAL_HRTIM_OPT_IT_SET1             \
                                      | HAL_HRTIM_OPT_IT_RESET1           \
                                      | HAL_HRTIM_OPT_IT_SET2             \
                                      | HAL_HRTIM_OPT_IT_RESET2           \
                                      | HAL_HRTIM_OPT_IT_RESET            \
                                      | HAL_HRTIM_OPT_IT_DELAYED_PROT     \
                                      | HAL_HRTIM_OPT_IT_XBAR_OVR_TRIGGER \
                                      | HAL_HRTIM_OPT_IT_XBAR_OVR_REARM)

/** Master timer DMA requests */
#define HRTIM_MASTER_DMA_REQUESTS (HAL_HRTIM_OPT_DMA_CMP1         \
                                   | HAL_HRTIM_OPT_DMA_CMP2       \
                                   | HAL_HRTIM_OPT_DMA_CMP3       \
                                   | HAL_HRTIM_OPT_DMA_CMP4       \
                                   | HAL_HRTIM_OPT_DMA_REPETITION \
                                   | HAL_HRTIM_OPT_DMA_SYNCHRO    \
                                   | HAL_HRTIM_OPT_DMA_UPDATE)

/** Timing unit DMA requests */
#define HRTIM_TIMING_UNIT_DMA_REQUESTS (HAL_HRTIM_OPT_DMA_CMP1               \
                                        | HAL_HRTIM_OPT_DMA_CMP2             \
                                        | HAL_HRTIM_OPT_DMA_CMP3             \
                                        | HAL_HRTIM_OPT_DMA_CMP4             \
                                        | HAL_HRTIM_OPT_DMA_REPETITION       \
                                        | HAL_HRTIM_OPT_DMA_UPDATE           \
                                        | HAL_HRTIM_OPT_DMA_CPT1             \
                                        | HAL_HRTIM_OPT_DMA_CPT2             \
                                        | HAL_HRTIM_OPT_DMA_SET1             \
                                        | HAL_HRTIM_OPT_DMA_RESET1           \
                                        | HAL_HRTIM_OPT_DMA_SET2             \
                                        | HAL_HRTIM_OPT_DMA_RESET2           \
                                        | HAL_HRTIM_OPT_DMA_RESET            \
                                        | HAL_HRTIM_OPT_DMA_DELAYED_PROT     \
                                        | HAL_HRTIM_OPT_DMA_XBAR_OVR_TRIGGER \
                                        | HAL_HRTIM_OPT_DMA_XBAR_OVR_REARM)

/** Master timer registers that can be updated by a DMA burst operation*/
#define HRTIM_MASTER_DMA_BURST_REGISTERS (HAL_HRTIM_DMA_BURST_CR      \
                                          | HAL_HRTIM_DMA_BURST_ICR   \
                                          | HAL_HRTIM_DMA_BURST_DIER  \
                                          | HAL_HRTIM_DMA_BURST_CNT   \
                                          | HAL_HRTIM_DMA_BURST_PER   \
                                          | HAL_HRTIM_DMA_BURST_REP   \
                                          | HAL_HRTIM_DMA_BURST_CMP1  \
                                          | HAL_HRTIM_DMA_BURST_CMP2  \
                                          | HAL_HRTIM_DMA_BURST_CMP3  \
                                          | HAL_HRTIM_DMA_BURST_CMP4)

/** Timing unit registers that can be updated by a DMA burst operation*/
#define HRTIM_TIMING_UNIT_DMA_BURST_REGISTERS (HAL_HRTIM_DMA_BURST_CR       \
                                               | HAL_HRTIM_DMA_BURST_ICR    \
                                               | HAL_HRTIM_DMA_BURST_DIER   \
                                               | HAL_HRTIM_DMA_BURST_CNT    \
                                               | HAL_HRTIM_DMA_BURST_PER    \
                                               | HAL_HRTIM_DMA_BURST_REP    \
                                               | HAL_HRTIM_DMA_BURST_CMP1   \
                                               | HAL_HRTIM_DMA_BURST_CMP2   \
                                               | HAL_HRTIM_DMA_BURST_CMP3   \
                                               | HAL_HRTIM_DMA_BURST_CMP4   \
                                               | HAL_HRTIM_DMA_BURST_DTR    \
                                               | HAL_HRTIM_DMA_BURST_SET1R  \
                                               | HAL_HRTIM_DMA_BURST_RST1R  \
                                               | HAL_HRTIM_DMA_BURST_SET2R  \
                                               | HAL_HRTIM_DMA_BURST_RST2R  \
                                               | HAL_HRTIM_DMA_BURST_EEFR1  \
                                               | HAL_HRTIM_DMA_BURST_EEFR2  \
                                               | HAL_HRTIM_DMA_BURST_RSTR   \
                                               | HAL_HRTIM_DMA_BURST_CHPR   \
                                               | HAL_HRTIM_DMA_BURST_OUTR   \
                                               | HAL_HRTIM_DMA_BURST_FLTR   \
                                               | HAL_HRTIM_DMA_BURST_CR2    \
                                               | HAL_HRTIM_DMA_BURST_EEFR3  \
                                               | HAL_HRTIM_DMA_BURST_EESELR \
                                               | HAL_HRTIM_DMA_BURST_COTRGR \
                                               | HAL_HRTIM_DMA_BURST_COFER  \
                                               | HAL_HRTIM_DMA_BURST_CODER)

/** Combined event A sources */
#define HRTIM_EEVA_SOURCES (HAL_HRTIM_EEVA_SRC_EEV1          \
                            | HAL_HRTIM_EEVA_SRC_EEV11       \
                            | HAL_HRTIM_EEVA_SRC_EEV1_EEV2   \
                            | HAL_HRTIM_EEVA_SRC_EEV1_EEV11)

/** Combined event B sources */
#define HRTIM_EEVB_SOURCES (HAL_HRTIM_EEVB_SRC_EEV2          \
                            | HAL_HRTIM_EEVB_SRC_EEV12       \
                            | HAL_HRTIM_EEVB_SRC_EEV2_EEV3   \
                            | HAL_HRTIM_EEVB_SRC_EEV2_EEV12)

/** Combined event C sources */
#define HRTIM_EEVC_SOURCES (HAL_HRTIM_EEVC_SRC_EEV3          \
                            | HAL_HRTIM_EEVC_SRC_EEV13       \
                            | HAL_HRTIM_EEVC_SRC_EEV3_EEV4   \
                            | HAL_HRTIM_EEVC_SRC_EEV3_EEV13)

/** Combined event D sources */
#define HRTIM_EEVD_SOURCES (HAL_HRTIM_EEVD_SRC_EEV4          \
                            | HAL_HRTIM_EEVD_SRC_EEV14       \
                            | HAL_HRTIM_EEVD_SRC_EEV4_EEV5   \
                            | HAL_HRTIM_EEVD_SRC_EEV4_EEV14)

/** Combined event E sources */
#define HRTIM_EEVE_SOURCES (HAL_HRTIM_EEVE_SRC_EEV5          \
                            | HAL_HRTIM_EEVE_SRC_EEV15       \
                            | HAL_HRTIM_EEVE_SRC_EEV5_EEV6   \
                            | HAL_HRTIM_EEVE_SRC_EEV5_EEV15)

/** Combined event F sources */
#define HRTIM_EEVF_SOURCES (HAL_HRTIM_EEVF_SRC_EEV6          \
                            | HAL_HRTIM_EEVF_SRC_EEV16       \
                            | HAL_HRTIM_EEVF_SRC_EEV6_EEV7   \
                            | HAL_HRTIM_EEVF_SRC_EEV6_EEV16)

/** Combined event G sources */
#define HRTIM_EEVG_SOURCES (HAL_HRTIM_EEVG_SRC_EEV7          \
                            | HAL_HRTIM_EEVG_SRC_EEV11       \
                            | HAL_HRTIM_EEVG_SRC_EEV7_EEV8   \
                            | HAL_HRTIM_EEVG_SRC_EEV7_EEV11)

/** Combined event H sources */
#define HRTIM_EEVH_SOURCES (HAL_HRTIM_EEVH_SRC_EEV8          \
                            | HAL_HRTIM_EEVH_SRC_EEV12       \
                            | HAL_HRTIM_EEVH_SRC_EEV8_EEV9   \
                            | HAL_HRTIM_EEVH_SRC_EEV8_EEV12)

/** Combined event I sources */
#define HRTIM_EEVI_SOURCES (HAL_HRTIM_EEVI_SRC_EEV9          \
                            | HAL_HRTIM_EEVI_SRC_EEV13       \
                            | HAL_HRTIM_EEVI_SRC_EEV9_EEV10  \
                            | HAL_HRTIM_EEVI_SRC_EEV9_EEV13)

/** Combined event J sources */
#define HRTIM_EEVJ_SOURCES (HAL_HRTIM_EEVJ_SRC_EEV10         \
                            | HAL_HRTIM_EEVJ_SRC_EEV14       \
                            | HAL_HRTIM_EEVJ_SRC_EEV10_EEV11 \
                            | HAL_HRTIM_EEVJ_SRC_EEV10_EEV14)

/** Crossbar override hardware triggers */
#if defined(PLAY1)
#define HRTIM_XBAR_OVR_HARDWARE_TRIGGERS (HAL_HRTIM_XBAR_OVR_FLT1         \
                                          | HAL_HRTIM_XBAR_OVR_FLT2       \
                                          | HAL_HRTIM_XBAR_OVR_FLT3       \
                                          | HAL_HRTIM_XBAR_OVR_FLT4       \
                                          | HAL_HRTIM_XBAR_OVR_FLT5       \
                                          | HAL_HRTIM_XBAR_OVR_FLT6       \
                                          | HAL_HRTIM_XBAR_OVR_FLT7       \
                                          | HAL_HRTIM_XBAR_OVR_FLT8       \
                                          | HAL_HRTIM_XBAR_OVR_FLT1_FLT2  \
                                          | HAL_HRTIM_XBAR_OVR_FLT2_FLT3  \
                                          | HAL_HRTIM_XBAR_OVR_FLT3_FLT4  \
                                          | HAL_HRTIM_XBAR_OVR_FLT4_FLT5  \
                                          | HAL_HRTIM_XBAR_OVR_FLT5_FLT6  \
                                          | HAL_HRTIM_XBAR_OVR_FLT6_FLT7  \
                                          | HAL_HRTIM_XBAR_OVR_FLT7_FLT8  \
                                          | HAL_HRTIM_XBAR_OVR_EEVA       \
                                          | HAL_HRTIM_XBAR_OVR_EEVB       \
                                          | HAL_HRTIM_XBAR_OVR_EEVC       \
                                          | HAL_HRTIM_XBAR_OVR_EEVD       \
                                          | HAL_HRTIM_XBAR_OVR_EEVE       \
                                          | HAL_HRTIM_XBAR_OVR_EEVF       \
                                          | HAL_HRTIM_XBAR_OVR_EEVG       \
                                          | HAL_HRTIM_XBAR_OVR_EEVH       \
                                          | HAL_HRTIM_XBAR_OVR_EEVI       \
                                          | HAL_HRTIM_XBAR_OVR_EEVJ       \
                                          | HAL_HRTIM_XBAR_OVR_PLAY1_OUT1 \
                                          | HAL_HRTIM_XBAR_OVR_PLAY1_OUT2 \
                                          | HAL_HRTIM_XBAR_OVR_PLAY1_OUT3 \
                                          | HAL_HRTIM_XBAR_OVR_PLAY1_OUT4 \
                                          | HAL_HRTIM_XBAR_OVR_PLAY1_OUT5 \
                                          | HAL_HRTIM_XBAR_OVR_PLAY1_OUT6)
#else
#define HRTIM_XBAR_OVR_HARDWARE_TRIGGERS (HAL_HRTIM_XBAR_OVR_FLT1         \
                                          | HAL_HRTIM_XBAR_OVR_FLT2       \
                                          | HAL_HRTIM_XBAR_OVR_FLT3       \
                                          | HAL_HRTIM_XBAR_OVR_FLT4       \
                                          | HAL_HRTIM_XBAR_OVR_FLT5       \
                                          | HAL_HRTIM_XBAR_OVR_FLT6       \
                                          | HAL_HRTIM_XBAR_OVR_FLT7       \
                                          | HAL_HRTIM_XBAR_OVR_FLT8       \
                                          | HAL_HRTIM_XBAR_OVR_FLT1_FLT2  \
                                          | HAL_HRTIM_XBAR_OVR_FLT2_FLT3  \
                                          | HAL_HRTIM_XBAR_OVR_FLT3_FLT4  \
                                          | HAL_HRTIM_XBAR_OVR_FLT4_FLT5  \
                                          | HAL_HRTIM_XBAR_OVR_FLT5_FLT6  \
                                          | HAL_HRTIM_XBAR_OVR_FLT6_FLT7  \
                                          | HAL_HRTIM_XBAR_OVR_FLT7_FLT8  \
                                          | HAL_HRTIM_XBAR_OVR_EEVA       \
                                          | HAL_HRTIM_XBAR_OVR_EEVB       \
                                          | HAL_HRTIM_XBAR_OVR_EEVC       \
                                          | HAL_HRTIM_XBAR_OVR_EEVD       \
                                          | HAL_HRTIM_XBAR_OVR_EEVE       \
                                          | HAL_HRTIM_XBAR_OVR_EEVF       \
                                          | HAL_HRTIM_XBAR_OVR_EEVG       \
                                          | HAL_HRTIM_XBAR_OVR_EEVH       \
                                          | HAL_HRTIM_XBAR_OVR_EEVI       \
                                          | HAL_HRTIM_XBAR_OVR_EEVJ)
#endif /* PLAY1 */

/** Compare registers minimum value */
#define HRTIM_COMPARE_MIN_VALUE 0x3U

/** Compare registers maximum value */
#define HRTIM_COMPARE_MAX_VALUE 0xFFFD
/**
  *  @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup  HRTIM_Private_Macros HRTIM Private Macros
  *  @{
  */
/** Retrieve timer index from timer identifier (master timer, timer A to F) */
#define HRTIM_GET_TIMER_INDEX(timer) (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(HAL_HRTIM_MASTER))

/** Retrieve timing unit index from timing unit identifier (timer A to F) */
#define HRTIM_GET_TIMING_UNIT_INDEX(timing_unit) (uint8_t)(STM32_POSITION_VAL(timing_unit) \
                                                           - STM32_POSITION_VAL(HAL_HRTIM_TIMA))

/** Retrieve timer index from output identifier (CHxy) */
#define HRTIM_GET_TIMER_INDEX_FROM_OUTPUT(output) \
  (((output) & (HAL_HRTIM_CHA1 | HAL_HRTIM_CHA2)) ? HRTIM_GET_TIMER_INDEX(HAL_HRTIM_TIMA) :     \
   (((output) & (HAL_HRTIM_CHB1 | HAL_HRTIM_CHB2)) ? HRTIM_GET_TIMER_INDEX(HAL_HRTIM_TIMB) :    \
    (((output) & (HAL_HRTIM_CHC1 | HAL_HRTIM_CHC2)) ? HRTIM_GET_TIMER_INDEX(HAL_HRTIM_TIMC) :   \
     (((output) & (HAL_HRTIM_CHD1 | HAL_HRTIM_CHD2)) ? HRTIM_GET_TIMER_INDEX(HAL_HRTIM_TIMD) :  \
      (((output) & (HAL_HRTIM_CHE1 | HAL_HRTIM_CHE2)) ? HRTIM_GET_TIMER_INDEX(HAL_HRTIM_TIME) : \
       (((output) & (HAL_HRTIM_CHF1 | HAL_HRTIM_CHF2)) ? HRTIM_GET_TIMER_INDEX(HAL_HRTIM_TIMF) : 0U))))))

/** Access the HRTIM instance from the handle */
#define HRTIM_GET_INSTANCE(hhrtim) ((HRTIM_TypeDef *)((uint32_t)((hhrtim)->instance)))

/** Check the validity of a DMA source */
#define IS_HRTIM_DMA_SOURCE(index) (((index) == HAL_HRTIM_DMA_MASTER)  \
                                    || ((index) == HAL_HRTIM_DMA_TIMA) \
                                    || ((index) == HAL_HRTIM_DMA_TIMB) \
                                    || ((index) == HAL_HRTIM_DMA_TIMC) \
                                    || ((index) == HAL_HRTIM_DMA_TIMD) \
                                    || ((index) == HAL_HRTIM_DMA_TIME) \
                                    || ((index) == HAL_HRTIM_DMA_TIMF))

/** Check the validity of interrupts v.s. interrupt source */
#define IS_HRTIM_INTERRUPT(source, interrupts) \
  (((source) == HAL_HRTIM_INTERRUPT_COMMON) ? ((interrupts) & HRTIM_CLOBAL_INTERRUPTS)      == (interrupts) : \
   ((source) == HAL_HRTIM_INTERRUPT_MASTER) ? ((interrupts) & HRTIM_MASTER_INTERRUPTS)      == (interrupts) : \
   ((source) == HAL_HRTIM_INTERRUPT_TIMA)   ? ((interrupts) & HRTIM_TIMING_UNIT_INTERRUPTS) == (interrupts) : \
   ((source) == HAL_HRTIM_INTERRUPT_TIMB)   ? ((interrupts) & HRTIM_TIMING_UNIT_INTERRUPTS) == (interrupts) : \
   ((source) == HAL_HRTIM_INTERRUPT_TIMC)   ? ((interrupts) & HRTIM_TIMING_UNIT_INTERRUPTS) == (interrupts) : \
   ((source) == HAL_HRTIM_INTERRUPT_TIMD)   ? ((interrupts) & HRTIM_TIMING_UNIT_INTERRUPTS) == (interrupts) : \
   ((source) == HAL_HRTIM_INTERRUPT_TIME)   ? ((interrupts) & HRTIM_TIMING_UNIT_INTERRUPTS) == (interrupts) : \
   ((source) == HAL_HRTIM_INTERRUPT_TIMF)   ? ((interrupts) & HRTIM_TIMING_UNIT_INTERRUPTS) == (interrupts) : 0U)

/** Check the validity of DMA requests v.s. DMA source */
#define IS_HRTIM_DMA_REQUEST(source, dma_requests) \
  ((dma_requests == HAL_HRTIM_OPT_DMA_NONE) \
   || (((source) == HAL_HRTIM_DMA_MASTER) ? ((dma_requests) & HRTIM_MASTER_DMA_REQUESTS) == (dma_requests) :     \
       ((source) == HAL_HRTIM_DMA_TIMA)  ? ((dma_requests) & HRTIM_TIMING_UNIT_DMA_REQUESTS) == (dma_requests) : \
       ((source) == HAL_HRTIM_DMA_TIMB)  ? ((dma_requests) & HRTIM_TIMING_UNIT_DMA_REQUESTS) == (dma_requests) : \
       ((source) == HAL_HRTIM_DMA_TIMC)  ? ((dma_requests) & HRTIM_TIMING_UNIT_DMA_REQUESTS) == (dma_requests) : \
       ((source) == HAL_HRTIM_DMA_TIMD)  ? ((dma_requests) & HRTIM_TIMING_UNIT_DMA_REQUESTS) == (dma_requests) : \
       ((source) == HAL_HRTIM_DMA_TIME)  ? ((dma_requests) & HRTIM_TIMING_UNIT_DMA_REQUESTS) == (dma_requests) : \
       ((source) == HAL_HRTIM_DMA_TIMF)  ? ((dma_requests) & HRTIM_TIMING_UNIT_DMA_REQUESTS) == (dma_requests) : 0U))

/** Macros for the control of the timer parameter */
#define IS_HRTIM_TIMER(timer) (((timer) == HAL_HRTIM_MASTER)  \
                               || ((timer) == HAL_HRTIM_TIMA) \
                               || ((timer) == HAL_HRTIM_TIMB) \
                               || ((timer) == HAL_HRTIM_TIMC) \
                               || ((timer) == HAL_HRTIM_TIMD) \
                               || ((timer) == HAL_HRTIM_TIME) \
                               || ((timer) == HAL_HRTIM_TIMF))

/** Check the validity of a single timing unit (timer A to F) */
#define IS_HRTIM_TIMING_UNIT(timer) (((timer) == HAL_HRTIM_TIMA)    \
                                     || ((timer) == HAL_HRTIM_TIMB) \
                                     || ((timer) == HAL_HRTIM_TIMC) \
                                     || ((timer) == HAL_HRTIM_TIMD) \
                                     || ((timer) == HAL_HRTIM_TIME) \
                                     || ((timer) == HAL_HRTIM_TIMF))

/** Check the validity of a combination of timers (master timer, timer A to F) */
#define IS_HRTIM_COMBINED_TIMERS(timers) (((timers) != 0U) \
                                          && ((timers) & HRTIM_ALL_TIMERS) == (timers))

/** Check the validity of a combination of timing unit (timer A to F) */
#define IS_HRTIM_COMBINED_TIMING_UNITS(timing_units) (((timing_units) != 0U) \
                                                      && ((timing_units) & HRTIM_ALL_TIMING_UNITS) == (timing_units))

/** Macro for the control of the output parameter */
#define IS_HRTIM_OUTPUT(output) (((output) == HAL_HRTIM_CHA1)    \
                                 || ((output) == HAL_HRTIM_CHA2) \
                                 || ((output) == HAL_HRTIM_CHB1) \
                                 || ((output) == HAL_HRTIM_CHB2) \
                                 || ((output) == HAL_HRTIM_CHC1) \
                                 || ((output) == HAL_HRTIM_CHC2) \
                                 || ((output) == HAL_HRTIM_CHD1) \
                                 || ((output) == HAL_HRTIM_CHD2) \
                                 || ((output) == HAL_HRTIM_CHE1) \
                                 || ((output) == HAL_HRTIM_CHE2) \
                                 || ((output) == HAL_HRTIM_CHF1) \
                                 || ((output) == HAL_HRTIM_CHF2))

/** Check the validity of a combination of outputs */
#define IS_HRTIM_COMBINED_OUTPUTS(outputs) (((outputs) != 0U) \
                                            && ((outputs) & HRTIM_ALL_OUTPUTS) == (outputs))

/** Check the timer outputs */
#define IS_HRTIM_TIMER_OUTPUTS(timer_outputs)  (((timer_outputs) == HAL_HRTIM_TIM_OUT1)    \
                                                || ((timer_outputs) == HAL_HRTIM_TIM_OUT2) \
                                                || ((timer_outputs) == HAL_HRTIM_TIM_OUT1_OUT2))

/** Check the DLL calibration rate configuration */
#define IS_HRTIM_DLL_CALIBRATION_RATE(rate) (((rate) == HAL_HRTIM_DLL_CALIB_RATE_0)    \
                                             || ((rate) == HAL_HRTIM_DLL_CALIB_RATE_1) \
                                             || ((rate) == HAL_HRTIM_DLL_CALIB_RATE_2) \
                                             || ((rate) == HAL_HRTIM_DLL_CALIB_RATE_3))

/** Check the output synchronization source configuration */
#define IS_HRTIM_SYNC_OUTPUT_SOURCE(source) (((source) == HAL_HRTIM_SYNC_OUTPUT_MASTER_START)  \
                                             || ((source) == HAL_HRTIM_SYNC_OUTPUT_MASTER_CMP1) \
                                             || ((source) == HAL_HRTIM_SYNC_OUTPUT_TIMA_START)  \
                                             || ((source) == HAL_HRTIM_SYNC_OUTPUT_TIMA_CMP1))

/** Check the output synchronization pulse configuration */
#define IS_HRTIM_SYNC_OUTPUT_PULSE(pulse) (((pulse) == HAL_HRTIM_SYNC_OUTPUT_DISABLE)           \
                                           || ((pulse) == HAL_HRTIM_SYNC_OUTPUT_POSITIVE_PULSE) \
                                           || ((pulse) == HAL_HRTIM_SYNC_OUTPUT_NEGATIVE_PULSE))

/** Check the input synchronization source configuration */
#if defined(PLAY1)
#define IS_HRTIM_SYNC_INPUT_SOURCE(source) (((source) == HAL_HRTIM_SYNC_INPUT_DISABLE)       \
                                            || ((source) == HAL_HRTIM_SYNC_INPUT_GPIO)       \
                                            || ((source) == HAL_HRTIM_SYNC_INPUT_TIM1_TRGO)  \
                                            || ((source) == LL_HRTIM_SYNCIN_SRC_PLAY1_OUT15))
#else
#define IS_HRTIM_SYNC_INPUT_SOURCE(source) (((source) == HAL_HRTIM_SYNC_INPUT_DISABLE)  \
                                            || ((source) == HAL_HRTIM_SYNC_INPUT_GPIO)  \
                                            || ((source) == HAL_HRTIM_SYNC_INPUT_TIM1_TRGO))
#endif /* PLAY1 */

/** Check the timer slave mode configuration */
#define IS_HRTIM_TIM_SLAVE_MODE(slave_mode) (((slave_mode) == HAL_HRTIM_TIM_SLAVE_DISABLE)    \
                                             || ((slave_mode) == HAL_HRTIM_TIM_SLAVE_RESET)   \
                                             || ((slave_mode) == HAL_HRTIM_TIM_SLAVE_TRIGGER) \
                                             || ((slave_mode) == HAL_HRTIM_TIM_SLAVE_RESET_AND_TRIGGER))

/** Check the ADC trigger */
#define IS_HRTIM_ADC_TRIGGER(adc_trigger) (((adc_trigger) == HAL_HRTIM_ADC_TRIGGER1)    \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER2) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER3) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER4) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER5) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER6) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER7) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER8) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER9) \
                                           || ((adc_trigger) == HAL_HRTIM_ADC_TRIGGER10))

/** Check the ADC postscaler configuration */
#define IS_HRTIM_ADC_POSTSCALER(postscaler) ((postscaler) <= 0x1FU)

/** Check the ADC trigger source configuration */
#define IS_HRTIM_ADC_TRIGGER_SOURCE(adc_trigger, source) \
  (((adc_trigger) < HAL_HRTIM_ADC_TRIGGER5) ? (1u) : ((source) <= 0x1FU))

/** Check the DAC trigger configuration */
#define IS_HRTIM_DAC_TRIGGER(dac_trigger) (((dac_trigger) == HAL_HRTIM_DAC_TRIGGER_NONE) \
                                           || ((dac_trigger) == HAL_HRTIM_DAC_TRIGGER1) \
                                           || ((dac_trigger) == HAL_HRTIM_DAC_TRIGGER2) \
                                           || ((dac_trigger) == HAL_HRTIM_DAC_TRIGGER3))

/** Check the dual channel DAC reset trigger configuration */
#define IS_HRTIM_DUAL_CHANNEL_DAC_RESET_TRIGGER(reset_trigger) \
  (((reset_trigger) == HAL_HRTIM_DUAL_DAC_RESET_RESET) \
   || ((reset_trigger) == HAL_HRTIM_DUAL_DAC_RESET_OUT1_SET))

/** Check the dual channel DAC step trigger configuration */
#define IS_HRTIM_DUAL_CHANNEL_DAC_STEP_TRIGGER(step_trigger) (((step_trigger) == HAL_HRTIM_DUAL_DAC_STEP_CMP2) \
                                                              || ((step_trigger) == HAL_HRTIM_DUAL_DAC_STEP_OUT1_RESET))

/** Check the digital filter configuration */
#define IS_HRTIM_DIGITAL_FILTER(filter) (((filter) == HAL_HRTIM_FDIV1)       \
                                         || ((filter) == HAL_HRTIM_FDIV1_N2)  \
                                         || ((filter) == HAL_HRTIM_FDIV1_N4)  \
                                         || ((filter) == HAL_HRTIM_FDIV1_N8)  \
                                         || ((filter) == HAL_HRTIM_FDIV2_N6)  \
                                         || ((filter) == HAL_HRTIM_FDIV2_N8)  \
                                         || ((filter) == HAL_HRTIM_FDIV4_N6)  \
                                         || ((filter) == HAL_HRTIM_FDIV4_N8)  \
                                         || ((filter) == HAL_HRTIM_FDIV8_N6)  \
                                         || ((filter) == HAL_HRTIM_FDIV8_N8)  \
                                         || ((filter) == HAL_HRTIM_FDIV16_N5) \
                                         || ((filter) == HAL_HRTIM_FDIV16_N6) \
                                         || ((filter) == HAL_HRTIM_FDIV16_N8) \
                                         || ((filter) == HAL_HRTIM_FDIV32_N5) \
                                         || ((filter) == HAL_HRTIM_FDIV32_N6) \
                                         || ((filter) == HAL_HRTIM_FDIV32_N8))

/** Check the external event prescaler configuration */
#define IS_HRTIM_EEV_PRESCALER(prescaler) (((prescaler) == HAL_HRTIM_EEV_DIV1)    \
                                           || ((prescaler) == HAL_HRTIM_EEV_DIV2) \
                                           || ((prescaler) == HAL_HRTIM_EEV_DIV4) \
                                           || ((prescaler) == HAL_HRTIM_EEV_DIV8))

/** Check the external event identifier */
#define IS_HRTIM_EEV(event) (((event) == HAL_HRTIM_EEV1)     \
                             || ((event) == HAL_HRTIM_EEV2)  \
                             || ((event) == HAL_HRTIM_EEV3)  \
                             || ((event) == HAL_HRTIM_EEV4)  \
                             || ((event) == HAL_HRTIM_EEV5)  \
                             || ((event) == HAL_HRTIM_EEV6)  \
                             || ((event) == HAL_HRTIM_EEV7)  \
                             || ((event) == HAL_HRTIM_EEV8)  \
                             || ((event) == HAL_HRTIM_EEV9)  \
                             || ((event) == HAL_HRTIM_EEV10) \
                             || ((event) == HAL_HRTIM_EEV11) \
                             || ((event) == HAL_HRTIM_EEV12) \
                             || ((event) == HAL_HRTIM_EEV13) \
                             || ((event) == HAL_HRTIM_EEV14) \
                             || ((event) == HAL_HRTIM_EEV15) \
                             || ((event) == HAL_HRTIM_EEV16))

/** Check the combined event identifier */
#define IS_HRTIM_COMBINED_EEV(event) (((event) == HAL_HRTIM_EEVA)     \
                                      || ((event) == HAL_HRTIM_EEVB)  \
                                      || ((event) == HAL_HRTIM_EEVC)  \
                                      || ((event) == HAL_HRTIM_EEVD)  \
                                      || ((event) == HAL_HRTIM_EEVE)  \
                                      || ((event) == HAL_HRTIM_EEVF)  \
                                      || ((event) == HAL_HRTIM_EEVG)  \
                                      || ((event) == HAL_HRTIM_EEVH)  \
                                      || ((event) == HAL_HRTIM_EEVI)  \
                                      || ((event) == HAL_HRTIM_EEVJ))

/** Check the combined event source configuration */
#define IS_HRTIM_COMBINED_EEV_SOURCE(event, source) \
  ((source == 0u) ? 1u : \
   (event == HAL_HRTIM_EEVA) ? (((source) & HRTIM_EEVA_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVB) ? (((source) & HRTIM_EEVB_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVC) ? (((source) & HRTIM_EEVC_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVD) ? (((source) & HRTIM_EEVD_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVE) ? (((source) & HRTIM_EEVE_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVF) ? (((source) & HRTIM_EEVF_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVG) ? (((source) & HRTIM_EEVG_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVH) ? (((source) & HRTIM_EEVH_SOURCES) != 0u) : \
   (event == HAL_HRTIM_EEVI) ? (((source) & HRTIM_EEVI_SOURCES) != 0u) : \
   (((source) & HRTIM_EEVJ_SOURCES) != 0u))

/** Check the external event source configuration */
#define IS_HRTIM_EEV_SOURCE(event, source) \
  (STM32_IS_BIT_SET((source), \
                    ((event) &~(LL_HRTIM_EEV_FAST_MODE | LL_HRTIM_EEV_FILTER))))

/** Check external event sensitivity configuration */
#define IS_HRTIM_EEV_SENSITIVITY(sensitivity) (((sensitivity) == HAL_HRTIM_EEV_EDGE_RISING)            \
                                               || ((sensitivity) == HAL_HRTIM_EEV_EDGE_FALLING)        \
                                               || ((sensitivity) == HAL_HRTIM_EEV_EDGE_RISING_FALLING) \
                                               || ((sensitivity) == HAL_HRTIM_EEV_LEVEL_HIGH)          \
                                               || ((sensitivity) == HAL_HRTIM_EEV_LEVEL_LOW))

/** Tells whether or not the event supports the fast asynchronous mode */
#define IS_HRTIM_EEV_FAST_MODE_SUPPORTED(event) (STM32_IS_BIT_SET((event), LL_HRTIM_EEV_FAST_MODE))

/** Tells whether or not the event supports the digital filtering mode */
#define IS_HRTIM_EEV_FILTER_SUPPORTED(event) (STM32_IS_BIT_SET((event), LL_HRTIM_EEV_FILTER))

/** Check the external event fast mode configuration */
#define IS_HRTIM_EEV_FAST_MODE(mode) (((mode) == HAL_HRTIM_EEV_SYNCHRONOUS) \
                                      || ((mode) == HAL_HRTIM_EEV_ASYNCHRONOUS))

/** Check the external event filter configuration */
#define IS_HRTIM_EEV_FILTER(filter) (IS_HRTIM_DIGITAL_FILTER((filter)))

/** Check the external event filtering in timing units configuration */
#define IS_HRTIM_TIM_EVT_FILTER(filter) (((filter) == HAL_HRTIM_NO_FILTERING) \
                                         || (STM32_IS_BIT_SET(HRTIM_EEFxR1_EEAFLTR, (filter))))

/** Check the external event notification mode configuration */
#define IS_HRTIM_TIM_EVT_NOTIFICATION(mode) (((mode) == HAL_HRTIM_EEV_IMMEDIATE) \
                                             || ((mode) == HAL_HRTIM_EEV_POSTPONED))

/** Check if selected event filtering mode is blanking mode  */
#define IS_HRTIM_EEV_TIMFLTR_BLANKING(filter) (((filter) & HRTIM_TIM_EVTFLTR_TIMBLKSRC) != 0U)

/** Check if selected event filtering mode is windowing mode  */
#define IS_HRTIM_EEV_TIMFLTR_WINDOWING(filter) (((filter) & HRTIM_TIM_EVTFLTR_TIMWINSRC) != 0U)

/** Check the external event counter identifier */
#define IS_HRTIM_EEV_COUNTER(counter) (((counter) == HAL_HRTIM_EEV_COUNTER_Y) \
                                       || ((counter) == HAL_HRTIM_EEV_COUNTER_Z))

/** Check the external event counter threshold configuration */
#define IS_HRTIM_EEV_COUNTER_THRESHOLD(threshold) ((threshold) <= 0x3FU)

/** Check the external event counter reset mode configuration */
#define IS_HRTIM_EEV_COUNTER_RESET_MODE(mode) (((mode) == HAL_HRTIM_EEV_COUNTER_RESET_UNCONDITIONAL) \
                                               || ((mode) == HAL_HRTIM_EEV_COUNTER_RESET_CUMULATIVE))

/** Check the fault prescaler configuration */
#define IS_HRTIM_FLT_PRESCALER(prescaler) (((prescaler) == HAL_HRTIM_FLT_DIV1)    \
                                           || ((prescaler) == HAL_HRTIM_FLT_DIV2) \
                                           || ((prescaler) == HAL_HRTIM_FLT_DIV4) \
                                           || ((prescaler) == HAL_HRTIM_FLT_DIV8))

/** Check single fault input identifier */
#define IS_HRTIM_FLT(fault) (((fault) == HAL_HRTIM_FLT1)    \
                             || ((fault) == HAL_HRTIM_FLT2) \
                             || ((fault) == HAL_HRTIM_FLT3) \
                             || ((fault) == HAL_HRTIM_FLT4) \
                             || ((fault) == HAL_HRTIM_FLT5) \
                             || ((fault) == HAL_HRTIM_FLT6) \
                             || ((fault) == HAL_HRTIM_FLT7) \
                             || ((fault) == HAL_HRTIM_FLT8))

/** Check single fault input or combined fault inputs identifier */
#define IS_HRTIM_COMBINED_FLT(fault) (((fault) == HAL_HRTIM_FLT1)         \
                                      || ((fault) == HAL_HRTIM_FLT2)      \
                                      || ((fault) == HAL_HRTIM_FLT3)      \
                                      || ((fault) == HAL_HRTIM_FLT4)      \
                                      || ((fault) == HAL_HRTIM_FLT5)      \
                                      || ((fault) == HAL_HRTIM_FLT6)      \
                                      || ((fault) == HAL_HRTIM_FLT7)      \
                                      || ((fault) == HAL_HRTIM_FLT8)      \
                                      || ((fault) == HAL_HRTIM_FLT1_FLT2) \
                                      || ((fault) == HAL_HRTIM_FLT2_FLT3) \
                                      || ((fault) == HAL_HRTIM_FLT3_FLT4) \
                                      || ((fault) == HAL_HRTIM_FLT4_FLT5) \
                                      || ((fault) == HAL_HRTIM_FLT5_FLT6) \
                                      || ((fault) == HAL_HRTIM_FLT6_FLT7) \
                                      || ((fault) == HAL_HRTIM_FLT7_FLT8))

/** Check multiple fault inputs selection */
#define IS_HRTIM_COMBINED_FAULTS(faults) (((faults) != 0U) \
                                          && ((faults) & HRTIM_ALL_FAULTS) == (faults))

/** Check the fault source configuration */
#define IS_HRTIM_FLT_SOURCE(fault, source) (STM32_IS_BIT_SET((source), ((fault) &~(LL_HRTIM_FLT_SRC))))

/** Check the fault input polarity configuration */
#define IS_HRTIM_FLT_POLARITY(polarity) (((polarity) == HAL_HRTIM_FLT_LOW) \
                                         || ((polarity) == HAL_HRTIM_FLT_HIGH))

/** Check the fault input filter configuration */
#define IS_HRTIM_FLT_FILTER(filter) (IS_HRTIM_DIGITAL_FILTER((filter)))

/** check the fault blanking configuration */
#define IS_HRTIM_FLT_BLANKING(fault, blanking) (STM32_IS_BIT_SET((blanking), ((fault) &~(LL_HRTIM_FLTBLK_SEL))))

/** Check the fault counter threshold configuration */
#define IS_HRTIM_FLT_COUNTER_THRESHOLD(threshold)  ((threshold) <= 0xFU)

/** Check the fault counter reset mode configuration */
#define IS_HRTIM_FLT_COUNTER_RESET_MODE(mode) (((mode) == HAL_HRTIM_FLT_COUNTER_RESET_UNCONDITIONAL) \
                                               || ((mode) == HAL_HRTIM_FLT_COUNTER_RESET_CUMULATIVE))

/** Check the burst mode controller operatinf mode configuration */
#define IS_HRTIM_BM_MODE(mode) (((mode) == HAL_HRTIM_BURST_MODE_SINGLE_SHOT) \
                                || ((mode) == HAL_HRTIM_BURST_MODE_CONTINUOUS))

/** Check the burst mode controller clock source configuration */
#define IS_HRTIM_BM_CLOCK(clock) (((clock) == HAL_HRTIM_BURST_MODE_CLK_MASTER)   \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIMA)  \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIMB)  \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIMC)  \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIMD)  \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIME)  \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIMF)  \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIM12_OC1) \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIM13_OC1) \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIM7_TRGO) \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_TIM27_TRGO) \
                                  || ((clock) == HAL_HRTIM_BURST_MODE_CLK_HRTIM))

/** Check the burst mode controller prescaler configuration */
#define IS_HRTIM_BM_PRESCALER(prescaler) (((prescaler) >= HAL_HRTIM_BURST_MODE_DIV1) \
                                          && ((prescaler) <= HAL_HRTIM_BURST_MODE_DIV32768))

/** Check the timer burst mode configuration */
#define IS_HRTIM_TIMER_BURST_MODE(mode) (((mode) == HAL_HRTIM_TIM_BURST_MODE_MAINTAIN) \
                                         || ((mode) == HAL_HRTIM_TIM_BURST_MODE_STOP_AND_RESET))

/** Check the output burst mode configuration */
#define IS_HRTIM_OUTPUT_BURST_MODE(mode)  (((mode) == HAL_HRTIM_OUT_BURST_MODE_DISABLE)      \
                                           || ((mode) == HAL_HRTIM_OUT_BURST_MODE_IMMEDIATE) \
                                           || ((mode) == HAL_HRTIM_OUT_BURST_MODE_DELAYED))

#if defined(PLAY1)

/** Check the burst mode trigger input source */
#define IS_HRTIM_TIMER_BURST_TRIGGER_INPUT(source)  (((source) == HAL_HRTIM_BURST_MODE_TRIGGER_TIM26_TRGO) \
                                                     || ((source) == HAL_HRTIM_BURST_MODE_TRIGGER_PLAY1_OUT13))
#endif /* PLAY1 */

/** Check the validity of the master timer register update mask for a DMA burst operation */
#define IS_HRTIM_DMA_BURST_MASTER_UPDATE_REGISTERS(registers) \
  (((registers) == HAL_HRTIM_DMA_BURST_NONE) \
   || (STM32_IS_BIT_SET(HRTIM_MASTER_DMA_BURST_REGISTERS, (registers))))

/** Check the validity of the timing unit register update mask for a DMA burst operation */
#define IS_HRTIM_DMA_BURST_TIMING_UNIT_UPDATE_REGISTERS(registers) \
  (((registers) == HAL_HRTIM_DMA_BURST_NONE) \
   || (STM32_IS_BIT_SET(HRTIM_TIMING_UNIT_DMA_BURST_REGISTERS, (registers))))

/** Check the counter clock prescaler configuration */
#define IS_HRTIM_TIM_PRESCALER(prescaler) ((prescaler) <= HAL_HRTIM_TIM_PRESCALER_DIV4)

/** Check the period configuration */
#define IS_HRTIM_TIM_PERIOD(period) (((period) >= 0x0003) && ((period) <= 0xFFFD))

/** Check the repetition counter configuration */
#define IS_HRTIM_TIM_REPETITION(repetition)  ((repetition) <= 0xFF)

/** Check the timer operating mode configuration */
#define IS_HRTIM_TIM_OPERATING_MODE(mode) (((mode) == HAL_HRTIM_TIM_MODE_CONTINUOUS)    \
                                           || ((mode) == HAL_HRTIM_TIM_MODE_SINGLESHOT) \
                                           || ((mode) == HAL_HRTIM_TIM_MODE_SINGLESHOT_RETRIGGERABLE))

/** Check the timer counting mode configuration */
#define IS_HRTIM_TIM_COUNTING_MODE(mode) (((mode) == HAL_HRTIM_TIM_COUNTING_UP)  \
                                          || ((mode) == HAL_HRTIM_TIM_COUNTING_UP_DOWN))

/** Check the roll over destination selection */
#define IS_HRTIM_ROLL_OVER_DESTINATION(destination)  (((destination) == HAL_HRTIM_ROLL_OVER_UPDATE)        \
                                                      || ((destination) == HAL_HRTIM_ROLL_OVER_ADC)        \
                                                      || ((destination) == HAL_HRTIM_ROLL_OVER_FLT_EEV)    \
                                                      || ((destination) == HAL_HRTIM_ROLL_OVER_BURST_MODE) \
                                                      || ((destination) == HAL_HRTIM_ROLL_OVER_OUTPUT))

/** Check the roll over mode configuration */
#define IS_HRTIM_ROLL_OVER_MODE(mode) (((mode) == HAL_HRTIM_ROLL_OVER_VALLEY)   \
                                       || ((mode) == HAL_HRTIM_ROLL_OVER_CREST) \
                                       || ((mode) == HAL_HRTIM_ROLL_OVER_BOTH))

/** Check the update event source(s) configuration */
#define IS_HRTIM_UPDATE_SOURCE(timer, source)   \
  (((source) == HAL_HRTIM_UPDATE_SOURCE_NONE)          \
   || ((source) == HAL_HRTIM_UPDATE_SOURCE_REPETITION) \
   || (IS_HRTIM_TIMING_UNIT(timer)                    \
       && (STM32_READ_BIT((source) , \
                          HAL_HRTIM_UPDATE_SOURCE_REPETITION                                         \
                          | HAL_HRTIM_UPDATE_SOURCE_RESET                                            \
                          | HAL_HRTIM_UPDATE_SOURCE_MASTER_UPDATE                                    \
                          | (((timer) == HAL_HRTIM_TIMA) ? 0U : HAL_HRTIM_UPDATE_SOURCE_TIMA_UPDATE) \
                          | (((timer) == HAL_HRTIM_TIMB) ? 0U : HAL_HRTIM_UPDATE_SOURCE_TIMB_UPDATE) \
                          | (((timer) == HAL_HRTIM_TIMC) ? 0U : HAL_HRTIM_UPDATE_SOURCE_TIMC_UPDATE) \
                          | (((timer) == HAL_HRTIM_TIMD) ? 0U : HAL_HRTIM_UPDATE_SOURCE_TIMD_UPDATE) \
                          | (((timer) == HAL_HRTIM_TIME) ? 0U : HAL_HRTIM_UPDATE_SOURCE_TIME_UPDATE) \
                          | (((timer) == HAL_HRTIM_TIMF) ? 0U : HAL_HRTIM_UPDATE_SOURCE_TIMF_UPDATE)) == (source))))


/** Check the update gating configuration */
#define IS_HRTIM_UPDATE_GATING(timer, trigger)          \
  (((trigger) == HAL_HRTIM_UPDATE_DMABURST_INDEPENDENT) \
   || ((trigger) == HAL_HRTIM_UPDATE_DMABURST_COMPLETE) \
   || ((trigger) == HAL_HRTIM_UPDATE_DMABURST_UPDATE)   \
   || (IS_HRTIM_TIMING_UNIT(timer)                      \
       && (STM32_READ_BIT((trigger), \
                          HAL_HRTIM_UPDATE_TIM10_OC1          \
                          | HAL_HRTIM_UPDATE_TIM11_OC1        \
                          | HAL_HRTIM_UPDATE_TIM6_TRGO        \
                          | HAL_HRTIM_UPDATE_TIM10_OC1_UPDATE \
                          | HAL_HRTIM_UPDATE_TIM11_OC1_UPDATE \
                          | HAL_HRTIM_UPDATE_TIM6_TRGO_UPDATE) == trigger)))

/** Check output set crossbar configuration (must be different from software set trigger) */
#define IS_HRTIM_OUTPUT_SET(output_set) (output_set != 1U)

/** Check output reset crossbar configuration  (must be different from software reset trigger) */
#define IS_HRTIM_OUTPUT_RESET(output_reset) (output_reset != 1U)

/** Check HRTIM output polarity configuration */
#define IS_HRTIM_OUTPUT_POLARITY(polarity) (((polarity) == HAL_HRTIM_OUTPUT_ACTIVE_HIGH) \
                                            || ((polarity) == HAL_HRTIM_OUTPUT_ACTIVE_LOW))

/** Check HRTIM output idle level configuration */
#define IS_HRTIM_OUTPUT_IDLE_LEVEL(idle_level) (((idle_level) == HAL_HRTIM_OUTPUT_IDLE_INACTIVE) \
                                                || ((idle_level) == HAL_HRTIM_OUTPUT_IDLE_ACTIVE))

/** Check HRTIM output safety state configuration */
#define IS_HRTIM_OUTPUT_FAULT_LEVEL(fault_level) (((fault_level) == HAL_HRTIM_OUTPUT_FAULT_NONE)        \
                                                  || ((fault_level) == HAL_HRTIM_OUTPUT_FAULT_ACTIVE)   \
                                                  || ((fault_level) == HAL_HRTIM_OUTPUT_FAULT_INACTIVE) \
                                                  || ((fault_level) == HAL_HRTIM_OUTPUT_FAULT_HIGHZ))
/** Check compare unit identifier */
#define IS_HRTIM_COMPARE_UNIT(compare_unit) ((compare_unit) <= HAL_HRTIM_COMPARE_UNIT_4)

/** Check the compare value against the compare unit */
#define IS_HRTIM_COMPARE_VALUE(compare_unit, compare_value) \
  ((((compare_unit) == HAL_HRTIM_COMPARE_UNIT_1)            \
    || ((compare_unit) == HAL_HRTIM_COMPARE_UNIT_3)) ?      \
   (((compare_value) == 0x0000U)                         \
    || (((compare_value) >= HRTIM_COMPARE_MIN_VALUE)    \
        && ((compare_value) <= HRTIM_COMPARE_MAX_VALUE))) : \
   (((compare_value) >= HRTIM_COMPARE_MIN_VALUE)         \
    && ((compare_value) <= HRTIM_COMPARE_MAX_VALUE)))

/** Check whether compare unit supports the greater than comparison (GTCMP) mode */
#define IS_HRTIM_COMPARE_UNIT_GTCMP(compare_unit) (((compare_unit) == HAL_HRTIM_COMPARE_UNIT_1) \
                                                   || ((compare_unit) == HAL_HRTIM_COMPARE_UNIT_3))

/** Check triggered half mode configuration */
#define IS_HRTIM_TRIGGERED_HALF_MODE(mode) (((mode) == HAL_HRTIM_TRIG_HALF_DISABLE)   \
                                            || ((mode) == HAL_HRTIM_TRIG_HALF_ENABLE) \
                                            || ((mode) == HAL_HRTIM_TRIG_HALF_ENABLE_TIMEOUT))

/** Check whether compare unitsupports the auto-delayed mode */
#define IS_HRTIM_COMPARE_UNIT_DELCMP(compare_unit) (((compare_unit) == HAL_HRTIM_COMPARE_UNIT_2) \
                                                    || ((compare_unit) == HAL_HRTIM_COMPARE_UNIT_4))

/** Check interleaved mode configuration */
#define IS_HRTIM_INTERLEAVED_MODE(mode) (((mode) == HAL_HRTIM_INTERLEAVED_DISABLE)     \
                                         || ((mode) == HAL_HRTIM_INTERLEAVED_DUAL)     \
                                         || ((mode) == HAL_HRTIM_INTERLEAVED_TRIPLE)   \
                                         || ((mode) == HAL_HRTIM_INTERLEAVED_QUAD))

/** Check auto-delayed mode configuration */
#define IS_HRTIM_AUTO_DELAYED_MODE(mode) (((mode) == HAL_HRTIM_AUTODELAYED_DISABLE)         \
                                          || ((mode) == HAL_HRTIM_AUTODELAYED_TIMEOUT_NONE) \
                                          || ((mode) == HAL_HRTIM_AUTODELAYED_TIMEOUT_CMP1) \
                                          || ((mode) == HAL_HRTIM_AUTODELAYED_TIMEOUT_CMP3))

/** Check capture unit identifier */
#define IS_HRTIM_CAPTURE_UNIT(capture_unit) (((capture_unit) == HAL_HRTIM_CAPTURE_UNIT_1) \
                                             || ((capture_unit) == HAL_HRTIM_CAPTURE_UNIT_2))

/** Check capture trigger(s) configuration (must be different from software capture trigger)*/
#define IS_HRTIM_CAPTURE_TRIGGERS(triggers) (triggers != 1U)

/** Check the delayed protection mode configuration */
#define IS_HRTIM_DELAYED_PROTECTION_MODE(mode) (((mode) == HAL_HRTIM_DELAYED_IDLE)     \
                                                || ((mode) == HAL_HRTIM_BALANCED_IDLE) \
                                                || ((mode) == HAL_HRTIM_BALANCED_IDLE_AUTO_RESUME))

/** Check the delayed protection event configuration */
#define IS_HRTIM_DELAYED_PROTECTION_EVENT(timer, event) \
  ((((timer) & (HAL_HRTIM_TIMA | HAL_HRTIM_TIMB | HAL_HRTIM_TIMC)) == (timer)) ? \
   (((event) & (HAL_HRTIM_EEVF | HAL_HRTIM_EEVG)) == (event)) : \
   (((event) & (HAL_HRTIM_EEVH | HAL_HRTIM_EEVI)) == (event)))

/** Check the deadtime mode configuration */
#define IS_HRTIM_DEADTIME_MODE(mode)  (((mode) == HAL_HRTIM_DEADTIME_COMPLEMENTARY) \
                                       || ((mode) == HAL_HRTIM_DEADTIME_INSERTION)  \
                                       || ((mode) == HAL_HRTIM_DEADTIME_INSERTION_AND_DISARM))

/** Check the deadtime definition */
#define IS_HRTIM_DEADTIME(deadtime) (((deadtime) == HAL_HRTIM_DEADTIME_RISING) \
                                     || ((deadtime) == HAL_HRTIM_DEADTIME_FALLING))

/** Check the deadtime value configuration */
#define IS_HRTIM_DEADTIME_VALUE(value)  ((value) <= 0x1FFU)

/** Check the deadtime sign configuration */
#define IS_HRTIM_DEADTIME_SIGN(sign) (((sign) == HAL_HRTIM_DEADTIME_POSITIVE) \
                                      || ((sign) == HAL_HRTIM_DEADTIME_NEGATIVE))

/** Check the deadtime prescaler configuration */
#define IS_HRTIM_DEADTIME_PRESCALER(prescaler) (((prescaler) == HAL_HRTIM_DEADTIME_MUL16)    \
                                                || ((prescaler) == HAL_HRTIM_DEADTIME_MUL8) \
                                                || ((prescaler) == HAL_HRTIM_DEADTIME_MUL4) \
                                                || ((prescaler) == HAL_HRTIM_DEADTIME_MUL2) \
                                                || ((prescaler) == HAL_HRTIM_DEADTIME_DIV1) \
                                                || ((prescaler) == HAL_HRTIM_DEADTIME_DIV2) \
                                                || ((prescaler) == HAL_HRTIM_DEADTIME_DIV4) \
                                                || ((prescaler) == HAL_HRTIM_DEADTIME_DIV8))

/** Check the deadtime lock configuration */
#define IS_HRTIM_DEADTIME_LOCK(lock) (((lock) == HAL_HRTIM_DEADTIME_LOCK_SIGN) \
                                      || ((lock) == HAL_HRTIM_DEADTIME_LOCK_SIGN_AND_VALUE))

/** Check the chopper stage carrier frequency configuration*/
#define IS_HRTIM_CHOPPER_PRESCALER(prescaler) \
  (((prescaler) == HAL_HRTIM_CHOPPER_DIV16) ? 1U : \
   (((prescaler) >= HAL_HRTIM_CHOPPER_DIV32) && ((prescaler) <= HAL_HRTIM_CHOPPER_DIV256)))

/** Check the chopper stage first pulse width configuration */
#define IS_HRTIM_CHOPPER_PULSE(pulse) \
  (((pulse) == HAL_HRTIM_CHOPPER_MUL16) ? 1U : \
   (((pulse) >= HAL_HRTIM_CHOPPER_MUL32) && ((pulse) <= HAL_HRTIM_CHOPPER_MUL256)))

/** Check the chopper stage duty cycle configuration */
#define IS_HRTIM_CHOPPER_DUTY_CYCLE(duty_cycle) \
  (((duty_cycle) == LL_HRTIM_CHP_DUTYCYCLE_0) ? 1U : \
   (((duty_cycle) >= HAL_HRTIM_CHOPPER_DTY125) && ((duty_cycle) <= HAL_HRTIM_CHOPPER_DTY875)))

/** Check the push-pull ADC triggers configuration */
#define IS_HRTIM_PUSHPULL_ADC_TRIGGER(trigger) (((trigger) == HAL_HRTIM_PUSHPULL_ADC_OUT1)    \
                                                || ((trigger) == HAL_HRTIM_PUSHPULL_ADC_OUT2) \
                                                || ((trigger) == HAL_HRTIM_PUSHPULL_ADC_OUT1_OUT2))

/** Check the crossbar override triggers configuration */
#define IS_HRTIM_XBAR_OVR_TRIGGERS(triggers) (((triggers) & HRTIM_XBAR_OVR_HARDWARE_TRIGGERS) == (triggers))

/** Check the crossbar override mode configuration */
#define IS_HRTIM_XBAR_OVR_MODE(mode)  (((mode) == HAL_HRTIM_XBAR_OVR_CYCLE_BY_CYCLE) \
                                       || ((mode) == HAL_HRTIM_XBAR_OVR_LATCHED))

/** Check the crossbar override force mode configuration */
#define IS_HRTIM_XBAR_OVR_FORCE_MODE(mode) (((mode) == HAL_HRTIM_XBAR_OVR_FORCE_ACTIVE)      \
                                            || ((mode) == HAL_HRTIM_XBAR_OVR_FORCE_INACTIVE) \
                                            || ((mode) == HAL_HRTIM_XBAR_OVR_FORCE_DELAY1)   \
                                            || ((mode) == HAL_HRTIM_XBAR_OVR_FORCE_DELAY2)   \
                                            || ((mode) == HAL_HRTIM_XBAR_OVR_FORCE_EVENT))

/** Check the crossbar override forcing events configuration */
#define IS_HRTIM_XBAR_OVR_FORCING_EVENTS(events) (((events) & TIM_ALL_XBAR_OVR_FORCING_EVENTS) == (events))

/** Check the crossbar override delay option configuration */
#define IS_HRTIM_XBAR_OVR_DELAY_OPTION(option)  (((option) == HAL_HRTIM_XBAR_OVR_DELAY1) \
                                                 || ((option) == HAL_HRTIM_XBAR_OVR_DELAY2))

/** Check the crossbar override delay configuration */
#define IS_HRTIM_XBAR_OVR_DELAY_VALUE(value)  ((value) <= 0x1FFU)

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/** Retrieve the HRTIM handle from the dma channel handle */
#define HRTIM_GET_HDMA_PARENT(hdma) \
  ((hal_hrtim_handle_t *)((hdma)->p_parent))

/** Check if the DMA transfer operates in silent mode */
#define IS_HRTIM_ACTIVE_SILENT(timer_state) 0u
/* #warning "IS_HRTIM_ACTIVE_SILENT not defined!"*/

#endif  /* USE_HAL_HRTIM_DMA */

/**
  *  @}
  */

/* Private variables ---------------------------------------------------------*/
/** @addtogroup HRTIM_Private_Variables HRTIM Private Variables
  * @{
  */

/** lookup table to map timers and outputs to the corresponding LL output identifiers */
static const uint32_t HRTIM_OutputLookup[HRTIM_TIMING_UNITS_NB][2] =
{
  { LL_HRTIM_OUTPUT_CHA1, LL_HRTIM_OUTPUT_CHA2 }, /* Timer A */
  { LL_HRTIM_OUTPUT_CHB1, LL_HRTIM_OUTPUT_CHB2 }, /* Timer B */
  { LL_HRTIM_OUTPUT_CHC1, LL_HRTIM_OUTPUT_CHC2 }, /* Timer C */
  { LL_HRTIM_OUTPUT_CHD1, LL_HRTIM_OUTPUT_CHD2 }, /* Timer D */
  { LL_HRTIM_OUTPUT_CHE1, LL_HRTIM_OUTPUT_CHE2 }, /* Timer E */
  { LL_HRTIM_OUTPUT_CHF1, LL_HRTIM_OUTPUT_CHF2 }  /* Timer F */
};

/**
  *  @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup HRTIM_Private_Functions HRTIM Private Functions
  *  @{
  */
#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
/**
  * @brief  Callbacks initialization function.
  * @param hhrtim     Pointer to the HRTIM instance handle.
  */
__STATIC_FORCEINLINE void hrtim_init_callbacks(hal_hrtim_handle_t *hhrtim)
{
#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  hhrtim->dma_xfer_half_cplt_callback = HAL_HRTIM_DMAHalfCpltCallback;

  hhrtim->dma_xfer_cplt_callback = HAL_HRTIM_DMACpltCallback;

  hhrtim->dma_xfer_stop_callback = HAL_HRTIM_DMAStopCallback;

  hhrtim->dma_xfer_error_callback = HAL_HRTIM_DMAErrorCallback;
#endif /* USE_HAL_HRTIM_DMA && USE_HAL_HRTIM_TIMER_CALLBACKS */

#if defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
  /** HRTIM fault callback function pointer */
  hhrtim->fault_callback = HAL_HRTIM_FaultCallback;

  /** HRTIM system fault callback function pointer */
  hhrtim->system_fault_callback = HAL_HRTIM_SystemFaultCallback;

  /** HRTIM burst mode period callback function pointer */
  hhrtim->burst_mode_period_callback = HAL_HRTIM_BurstModePeriodCallback;

  /** HRTIM synchronization input callback function pointer */
  hhrtim->synchro_callback = HAL_HRTIM_SynchroCallback;

  /** HRTIM DLL calibration done callback function pointer */
  hhrtim->dll_calibration_callback = HAL_HRTIM_DLLCalibrationCallback;
#endif /* USE_HAL_HRTIM_GLOBAL_CALLBACKS */

#if defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  /** HRTIM timer registers update callback function pointer */
  hhrtim->update_callback = HAL_HRTIM_UpdateCallback;

  /** HRTIM timer repetition callback function pointer */
  hhrtim->repetition_callback = HAL_HRTIM_RepetitionCallback;

  /** HRTIM timer counter reset callback function pointer */
  hhrtim->reset_callback = HAL_HRTIM_ResetCallback;

  /** HRTIM timer delayed protection callback function pointer */
  hhrtim->delayed_protection_callback = HAL_HRTIM_DelayedProtectionCallback;
#endif /* USE_HAL_HRTIM_TIMER_CALLBACKS */

#if defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
  /** HRTIM compare Match callback function pointer */
  hhrtim->compare_match_callback = HAL_HRTIM_CompareMatchCallback;

  /** HRTIM capture callback function pointer */
  hhrtim->capture_callback = HAL_HRTIM_CaptureCallback;
#endif /* USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */

#if defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
  /** HRTIM output set callback function pointer */
  hhrtim->output_set_callback = HAL_HRTIM_OutputSetCallback;

  /** HRTIM output reset callback function pointer */
  hhrtim->output_reset_callback = HAL_HRTIM_OutputResetCallback;
#endif /* USE_HAL_HRTIM_OUTPUT_CALLBACKS */

#if defined(USE_HAL_HRTIM_XBAR_OVR_CALLBACKS) && (USE_HAL_HRTIM_XBAR_OVR_CALLBACKS == 1)
  /** HRTIM crossbar override trigger callback function pointer */
  hhrtim->xbar_ovr_trigger_callback = HAL_HRTIM_XbarOvrTriggerCallback;

  /** HRTIM crossbar override rearm delay function pointer */
  hhrtim->xbar_ovr_rearm_delay_callback = HAL_HRTIM_XbarOvrRearmDelayCallback;
#endif /* USE_HAL_HRTIM_XBAR_OVR_CALLBACKS */
}
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */

#if defined(USE_HAL_HRTIM_CLK_ENABLE_MODEL) && (USE_HAL_HRTIM_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
/**
  * @brief  Clock enabling for a particular instance.
  * @param  instance  HAL HRTIM instance
  */
__STATIC_FORCEINLINE void HRTIM_EnableClock(hal_hrtim_t instance)
{
  switch (instance)
  {
    case HAL_HRTIM1:
      HAL_RCC_HRTIM1_EnableClock();
      break;
    default:
      break;
  }
}
#endif /* USE_HAL_HRTIM_CLK_ENABLE_MODEL */

#if defined(USE_ASSERT_DBG_STATE)
/**
  * @brief  Check that one or several timers are in a given state.
  * @param hhrtim Pointer to the HRTIM instance handle.
  * @param timers Timers which state must be checks
  * @param state Timer state to check
  */
__STATIC_INLINE void hrtim_check_timers_state(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timers,
                                              uint32_t state)
{
  uint32_t bitmask = timers;
  uint32_t timer;

  timer = 1UL << STM32_POSITION_VAL(bitmask);

  while (bitmask != 0U)
  {
    ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], state);

    bitmask &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(bitmask);
  }
}
#endif /* USE_ASSERT_DBG_STATE */

/**
  * @brief  Convert constants from HAL to LL for fault input source.
  * @param fault_src fault input source HAL constant
  * @return Fault input source LL constant.
  */
__STATIC_INLINE uint32_t hrtim_hal_to_ll_fltsrc(hal_hrtim_flt_src_t fault_src)
{
  uint32_t fltsrc = 0;

  fltsrc = (uint32_t)(((uint32_t)fault_src & LL_HRTIM_FLT_SRC_MSK) >> LL_HRTIM_FLT_SRC_POS);

  return fltsrc;
}

/**
  * @brief  Convert constants from LL to HAL for fault input source.
  * @param fault fault input
  * @param fltsrc input source LL constant
  * @return Fault input source HAL constant.
  */
__STATIC_INLINE hal_hrtim_flt_src_t hrtim_ll_to_hal_fltsrc(uint32_t fault, uint32_t fltsrc)
{
  uint32_t fault_src = fault;

  fault_src |= (fltsrc << LL_HRTIM_FLT_SRC_POS);

  return (hal_hrtim_flt_src_t)fault_src;
}

/**
  * @brief  Convert constants from HAL to LL for fault blanking source.
  * @param fault_blanking fault blanking source LL constant
  * @return Fault blanking source LL constant.
  */
__STATIC_INLINE uint32_t hrtim_hal_to_ll_fltblks(hal_hrtim_flt_blk_t fault_blanking)
{
  uint32_t fltblks;

  fltblks = STM32_IS_BIT_SET((uint32_t)fault_blanking, LL_HRTIM_FLTBLK_SEL) ? LL_HRTIM_FLT_BLK_MOVING \
            : LL_HRTIM_FLT_BLK_RSTALIGNED;

  return fltblks;
}

/**
  * @brief  Convert constants from LL to HAL for fault blanking source.
  * @param fault fault input
  * @param fltblks fault blanking source LL constant
  * @return Fault blanking source HAL constant.
  */
__STATIC_INLINE hal_hrtim_flt_blk_t hrtim_ll_to_hal_fltblks(uint32_t fault, uint32_t fltblks)
{
  uint32_t fault_blanking = fault;

  (fltblks ==  LL_HRTIM_FLT_BLK_MOVING) ? STM32_SET_BIT(fault_blanking, LL_HRTIM_FLTBLK_SEL) \
  : STM32_CLEAR_BIT(fault_blanking, LL_HRTIM_FLTBLK_SEL);

  return (hal_hrtim_flt_blk_t)fault_blanking;
}

/**
  * @brief  Convert constants from HAL to LL for delayed protection.
  * @param timer_index  timing unit index
  * @param outputs  HRTIM output(s)
  * @param mode    delayed protection mode
  * @param event   external event
  * @return Delayed protection configuration LL constant.
  */
__STATIC_INLINE uint32_t hrtim_hal_to_ll_dlyprt(uint8_t timer_index,
                                                hal_hrtim_tim_outputs_t outputs,
                                                hal_hrtim_delayed_protection_mode_t mode,
                                                uint32_t event)
{
  uint32_t dlyprt = 0;
  uint8_t timx;
  uint8_t evtx;
  uint8_t outx;
  static const uint32_t delayed_idle_cfg[2][2][3] =
  {
    /* Timer A, B C */
    {
      /* EVT6 */
      {
        LL_HRTIM_DLYPRT_DELAYOUT1_EEVF, /* Output 1 */
        LL_HRTIM_DLYPRT_DELAYOUT2_EEVF, /* Output 2 */
        LL_HRTIM_DLYPRT_DELAYBOTH_EEVF  /* Output 1 and output 2 */
      },
      /* EVT7 */
      {
        LL_HRTIM_DLYPRT_DELAYOUT1_EEVG, /* Output 1 */
        LL_HRTIM_DLYPRT_DELAYOUT2_EEVG, /* Output 2 */
        LL_HRTIM_DLYPRT_DELAYBOTH_EEVG  /* Output 1 and output 2 */
      },
    },
    /* Timer D, E F */
    {
      /* EVT8 */
      {
        LL_HRTIM_DLYPRT_DELAYOUT1_EEVH, /* Output 1 */
        LL_HRTIM_DLYPRT_DELAYOUT2_EEVH, /* Output 2 */
        LL_HRTIM_DLYPRT_DELAYBOTH_EEVH  /* Output 1 and output 2 */
      },
      /* EVT9 */
      {
        LL_HRTIM_DLYPRT_DELAYOUT1_EEVI,  /* Output 1 */
        LL_HRTIM_DLYPRT_DELAYOUT2_EEVI,  /* Output 2 */
        LL_HRTIM_DLYPRT_DELAYBOTH_EEVI   /* Output 1 and output 2 */
      },
    }
  };

  static const uint32_t balanced_idle_cfg[2][2] =
  {
    /* Timer A, B C */
    {
      LL_HRTIM_DLYPRT_BALANCED_EEVF, /* EVTF */
      LL_HRTIM_DLYPRT_BALANCED_EEVG, /* EVTG */
    },
    /* Timer D, E F */
    {
      LL_HRTIM_DLYPRT_BALANCED_EEVH, /* EVTH */
      LL_HRTIM_DLYPRT_BALANCED_EEVI, /* EVTI */
    }
  };

  /* Calculate tim index */
  timx = (timer_index < 3U) ? 0U : 1U;

  /* Calculate evt index */
  evtx = (((event) & (HAL_HRTIM_EEVF | HAL_HRTIM_EEVH)) == event) ? 0U : 1U;

  if (mode == HAL_HRTIM_DELAYED_IDLE)
  {
    /* Calculate output index */
    if (outputs == HAL_HRTIM_TIM_OUT1)
    {
      outx = 0;
    }
    else if (outputs == HAL_HRTIM_TIM_OUT2)
    {
      outx = 1;
    }
    else
    {
      outx = 2;
    }

    dlyprt = delayed_idle_cfg[timx][evtx][outx];
  }
  else
  {
    dlyprt = balanced_idle_cfg[timx][evtx];
  }

  return dlyprt;
}

/**
  * @brief  Timer A to F interrupt handler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer  Timing unit (Timer A to F).
  */
static void HRTIM_TIMx_IRQHandler(hal_hrtim_handle_t *hhrtim,
                                  uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim = HRTIM_GET_INSTANCE(hhrtim);
  uint8_t timing_unit_index = HRTIM_GET_TIMING_UNIT_INDEX(timer);
  const uint32_t flag_status = LL_HRTIM_TIM_READ_REG(p_hrtim, timing_unit_index, TIMxISR);
  const uint32_t it_sources = LL_HRTIM_TIM_READ_REG(p_hrtim, timing_unit_index, TIMxDIER);
  const uint32_t flag_status_masked = flag_status & it_sources;
  const uint32_t output[HRTIM_OUTPUTS_NB] =
  {
    HAL_HRTIM_CHA1, HAL_HRTIM_CHA2,
    HAL_HRTIM_CHB1, HAL_HRTIM_CHB2,
    HAL_HRTIM_CHC1, HAL_HRTIM_CHC2,
    HAL_HRTIM_CHD1, HAL_HRTIM_CHD2,
    HAL_HRTIM_CHE1, HAL_HRTIM_CHE2,
    HAL_HRTIM_CHF1, HAL_HRTIM_CHF2
  };

  if ((flag_status_masked & LL_HRTIM_TIMISR_CMP1) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP1(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_1);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_1);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_CMP2) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP2(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_2);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_2);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_CMP3) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP3(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_3);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_3);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_CMP4) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP4(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_4);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, timer, HAL_HRTIM_COMPARE_UNIT_4);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_REP) != 0UL)
  {
    LL_HRTIM_ClearFlag_REP(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
    hhrtim->repetition_callback(hhrtim, timer);
#else
    HAL_HRTIM_RepetitionCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_UPD) != 0UL)
  {
    LL_HRTIM_ClearFlag_UPDATE(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
    hhrtim->update_callback(hhrtim, timer);
#else
    HAL_HRTIM_UpdateCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_CPT1) != 0UL)
  {
    LL_HRTIM_ClearFlag_CPT1(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->capture_callback(hhrtim, timer, HAL_HRTIM_CAPTURE_UNIT_1);
#else
    HAL_HRTIM_CaptureCallback(hhrtim, timer, HAL_HRTIM_CAPTURE_UNIT_1);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_CPT2) != 0UL)
  {
    LL_HRTIM_ClearFlag_CPT2(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->capture_callback(hhrtim, timer, HAL_HRTIM_CAPTURE_UNIT_2);
#else
    HAL_HRTIM_CaptureCallback(hhrtim, timer, HAL_HRTIM_CAPTURE_UNIT_2);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_SETA1) != 0UL)
  {
    LL_HRTIM_ClearFlag_SET1(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
    hhrtim->output_set_callback(hhrtim, output[2UL * timing_unit_index]);
#else
    HAL_HRTIM_OutputSetCallback(hhrtim, output[2UL * timing_unit_index]);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_OUTPUT_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_RSTA1) != 0UL)
  {
    LL_HRTIM_ClearFlag_RST1(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
    hhrtim->output_reset_callback(hhrtim, output[2UL * timing_unit_index]);
#else
    HAL_HRTIM_OutputResetCallback(hhrtim, output[2UL * timing_unit_index]);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_OUTPUT_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_SETA2) != 0UL)
  {
    LL_HRTIM_ClearFlag_SET2(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
    hhrtim->output_set_callback(hhrtim, output[(2UL * timing_unit_index) + 1UL]);
#else
    HAL_HRTIM_OutputSetCallback(hhrtim, output[(2UL * timing_unit_index) + 1UL]);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_OUTPUT_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_RSTA2) != 0UL)
  {
    LL_HRTIM_ClearFlag_RST2(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
    hhrtim->output_reset_callback(hhrtim, output[(2UL * timing_unit_index) + 1UL]);
#else
    HAL_HRTIM_OutputResetCallback(hhrtim, output[(2UL * timing_unit_index) + 1UL]);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_OUTPUT_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_RST) != 0UL)
  {
    LL_HRTIM_ClearFlag_RST(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
    hhrtim->reset_callback(hhrtim, timer);
#else
    HAL_HRTIM_ResetCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_DLYPRT) != 0UL)
  {
    LL_HRTIM_ClearFlag_DLYPRT(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
    hhrtim->delayed_protection_callback(hhrtim, timer);
#else
    HAL_HRTIM_DelayedProtectionCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_COT) != 0UL)
  {
    LL_HRTIM_ClearFlag_COT(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_XBAR_OVR_CALLBACKS) && (USE_HAL_HRTIM_XBAR_OVR_CALLBACKS == 1)
    hhrtim->xbar_ovr_trigger_callback(hhrtim, timer);
#else
    HAL_HRTIM_XbarOvrTriggerCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_XBAR_OVR_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_TIMISR_CORDE) != 0UL)
  {
    LL_HRTIM_ClearFlag_CORDE(p_hrtim, timer);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_XBAR_OVR_CALLBACKS) && (USE_HAL_HRTIM_XBAR_OVR_CALLBACKS == 1)
    hhrtim->xbar_ovr_rearm_delay_callback(hhrtim, timer);
#else
    HAL_HRTIM_XbarOvrRearmDelayCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_XBAR_OVR_CALLBACKS */
  }
}

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/**
  * @brief  return the timer identifier associated to the dma channel handle.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param hdma Pointer to DMA channel handle
  * @return HRTIM timer (master timer or timer A to F).
  */
__STATIC_INLINE uint32_t hrtim_dma_handle_to_timer(const hal_hrtim_handle_t *hhrtim,
                                                   const hal_dma_handle_t *hdma)
{
  uint32_t timer;

  if (hdma == hhrtim->hdma[HAL_HRTIM_DMA_TIMA])
  {
    timer = HAL_HRTIM_TIMA;
  }
  else if (hdma == hhrtim->hdma[HAL_HRTIM_DMA_TIMB])
  {
    timer = HAL_HRTIM_TIMB;
  }
  else if (hdma == hhrtim->hdma[HAL_HRTIM_DMA_TIMC])
  {
    timer = HAL_HRTIM_TIMC;
  }
  else if (hdma == hhrtim->hdma[HAL_HRTIM_DMA_TIMD])
  {
    timer = HAL_HRTIM_TIMD;
  }
  else if (hdma == hhrtim->hdma[HAL_HRTIM_DMA_TIME])
  {
    timer = HAL_HRTIM_TIME;
  }
  else if (hdma == hhrtim->hdma[HAL_HRTIM_DMA_TIMF])
  {
    timer = HAL_HRTIM_TIMF;
  }
  else
  {
    timer = HAL_HRTIM_MASTER;
  }

  return timer;
}

/**
  * @brief  callback function invoked when the DMA transfer is half completed.
  * @param hdma Pointer to DMA channel handle
  */
static void hrtim_dma_cb_half_cplt(hal_dma_handle_t *hdma)
{
  hal_hrtim_handle_t *hhrtim = HRTIM_GET_HDMA_PARENT(hdma);
  uint32_t timer;

  /* Retrieve the timer identifier from the DMA channel handle */
  timer = hrtim_dma_handle_to_timer(hhrtim, hdma);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  hhrtim->dma_xfer_half_cplt_callback(hhrtim, timer);
#else
  HAL_HRTIM_DMAHalfCpltCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
}

/**
  * @brief  callback function invoked when the DMA transfer is completed.
  * @param hdma Pointer to DMA channel handle
  */
static void hrtim_dma_cb_cplt(hal_dma_handle_t *hdma)
{
  hal_hrtim_handle_t *hhrtim = HRTIM_GET_HDMA_PARENT(hdma);
  uint32_t timer;

  /* Retrieve the timer identifier from the DMA channel handle */
  timer = hrtim_dma_handle_to_timer(hhrtim, hdma);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  hhrtim->dma_xfer_cplt_callback(hhrtim, timer);
#else
  HAL_HRTIM_DMACpltCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
}

/**
  * @brief  callback function invoked when the DMA transfer is aborted.
  * @param hdma Pointer to DMA channel handle
  */
static void hrtim_dma_cb_stop(hal_dma_handle_t *hdma)
{
  hal_hrtim_handle_t *hhrtim = HRTIM_GET_HDMA_PARENT(hdma);
  uint32_t timer;

  /* Retrieve the timer identifier from the DMA channel handle */
  timer = hrtim_dma_handle_to_timer(hhrtim, hdma);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  hhrtim->dma_xfer_stop_callback(hhrtim, timer);
#else
  HAL_HRTIM_DMAStopCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
}

/**
  * @brief  callback function invoked upon DMA transfer error.
  * @param hdma Pointer to DMA channel handle
  */
static void hrtim_dma_cb_error(hal_dma_handle_t *hdma)
{
  hal_hrtim_handle_t *hhrtim = HRTIM_GET_HDMA_PARENT(hdma);
  uint32_t timer;

  /* Retrieve the timer identifier from the DMA channel handle */
  timer = hrtim_dma_handle_to_timer(hhrtim, hdma);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
  hhrtim->dma_xfer_error_callback(hhrtim, timer);
#else
  HAL_HRTIM_DMAErrorCallback(hhrtim, timer);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
}

/**
  * @brief  Start the DMA transfer in interrupt mode.
  * @param hdma Pointer to DMA channel handle
  * @param p_config pointer to the DMA transfer configuration structure
  * @param interrupts DMA interrupts to enable
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_ERROR         Invalid DMA transfer mode.
  * @retval HAL_BUSY          DMA channel state is active when calling this API.
  */
static hal_status_t HRTIM_Start_DMA_Opt(hal_dma_handle_t *hdma,
                                        hal_hrtim_dma_config_t *p_config,
                                        uint32_t interrupts)
{
  hal_status_t status;

  ASSERT_DBG_PARAM((hdma != NULL));

  /* Set DMA channel callback function pointers */
  hdma->p_xfer_halfcplt_cb = hrtim_dma_cb_half_cplt;
  hdma->p_xfer_cplt_cb = hrtim_dma_cb_cplt;
  hdma->p_xfer_error_cb = hrtim_dma_cb_error;

  status = HAL_DMA_StartPeriphXfer_IT_Opt(hdma,
                                          p_config->src_addr,
                                          p_config->dest_addr,
                                          p_config->size_byte,
                                          interrupts);

  return status;
}

/**
  * @brief  Abort the DMA transfer associated to a timer (master timer or timer A to F).
  * @param hdma Pointer to DMA channel handle
  * @param timer_state Actual timer state
  * @retval HAL_OK            Operation completed successfully.
  */
static hal_status_t HRTIM_Abort_DMA(hal_dma_handle_t *hdma,
                                    hal_hrtim_timer_state_t timer_state)
{
  hal_status_t status = HAL_OK;

  if (timer_state == HAL_HRTIM_TIM_STATE_ACTIVE_SILENT)
  {
    (void)HAL_DMA_Abort(hdma);
    hrtim_dma_cb_stop(hdma);
  }
  else
  {
    hdma->p_xfer_abort_cb = hrtim_dma_cb_stop;

    if (HAL_DMA_Abort_IT(hdma) != HAL_OK)
    {
      hrtim_dma_cb_stop(hdma);
    }
  }

  return status;
}
#endif  /* USE_HAL_HRTIM_DMA */

/**
  *  @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup HRTIM_Exported_Functions
  *  @{
  */

/** @addtogroup HRTIM_Exported_Functions_Group1
  *  @{
  */

/**
  * @brief  Initialize the HRTIM instance handle and associate it to the hardware HRTIM instance.
  * @param  hhrtim     Pointer to the HRTIM instance handle.
  * @param  instance   Hardware HRTIM instance.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Input parameter is invalid (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_Init(hal_hrtim_handle_t *hhrtim, hal_hrtim_t instance)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_INSTANCE((HRTIM_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hhrtim == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the TIM instance */
  hhrtim->instance = instance;

#if defined(USE_HAL_HRTIM_CLK_ENABLE_MODEL) && (USE_HAL_HRTIM_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  HRTIM_EnableClock(instance);
#endif /* USE_HAL_HRTIM_CLK_ENABLE_MODEL */

#if defined (USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
  hrtim_init_callbacks(hhrtim);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */

  /* Init the handle internal parameters */

#if defined (USE_HAL_HRTIM_USER_DATA) && (USE_HAL_HRTIM_USER_DATA == 1)
  hhrtim->p_user_data = NULL;
#endif /* USE_HAL_HRTIM_USER_DATA */

  /* Reset interrupts configuration */
  for (uint32_t interrupts_source = (uint32_t)HAL_HRTIM_INTERRUPT_MASTER;
       interrupts_source <= (uint32_t)HAL_HRTIM_INTERRUPT_TIMF;
       interrupts_source++)
  {
    hhrtim->interrupts[interrupts_source] = HAL_HRTIM_OPT_IT_NONE;
  }

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
  /* Reset DMA configuration */
  for (uint32_t dma_source = (uint32_t)HAL_HRTIM_DMA_MASTER ;
       dma_source <= (uint32_t)HAL_HRTIM_DMA_TIMF;
       dma_source++)
  {
    hhrtim->hdma[dma_source] = NULL;
    hhrtim->p_dma_config[dma_source] = NULL;
  }
#endif /* USE_HAL_HRTIM_DMA */

  for (uint8_t timer = 0 ; timer < HRTIM_TIMERS_NB; timer ++)
  {
    hhrtim->timer_states[timer] = HAL_HRTIM_TIM_STATE_RESET;
  }

  hhrtim->global_state = HAL_HRTIM_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief      De-initialize the HRTIM instance handle.
  * @param      hhrtim      Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_DeInit(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_INSTANCE((HRTIM_TypeDef *)((uint32_t)hhrtim->instance)));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Stop on-going operations */
  LL_HRTIM_DisableOutput(p_hrtim, LL_HRTIM_OUTPUT_ALL);
  LL_HRTIM_TIM_CounterDisable(p_hrtim, LL_HRTIM_TIM_ALL);

  for (uint8_t timer = 0 ; timer < HRTIM_TIMERS_NB; timer ++)
  {
    hhrtim->timer_states[timer] = HAL_HRTIM_TIM_STATE_RESET;
  }

  hhrtim->global_state = HAL_HRTIM_STATE_RESET;
}

/**
  * @brief  Return the HAL HRTIM instance from the handle.
  * @param  hhrtim      Pointer to a hal_hrtim_handle_t.
  * @retval hal_hrtim_t HAL HRTIM instance.
  */
hal_hrtim_t HAL_HRTIM_GetInstance(const hal_hrtim_handle_t *hhrtim)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_INSTANCE((HRTIM_TypeDef *)((uint32_t)hhrtim->instance)));

  return hhrtim->instance;
}

/**
  * @brief  Return the CMSIS/LL HRTIM instance from the handle.
  * @param  hhrtim      Pointer to a @ref hal_hrtim_handle_t.
  * @retval HRTIM_TypeDef* CMSIS/LL HRTIM.
  */
HRTIM_TypeDef *HAL_HRTIM_GetLLInstance(const hal_hrtim_handle_t *hhrtim)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_INSTANCE((HRTIM_TypeDef *)((uint32_t)hhrtim->instance)));

  return HRTIM_GET_INSTANCE(hhrtim);
}

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/**
  * @brief Link a DMA handle to a timer.
  * @param hhrtim Pointer to the HRTIM instance handle.
  * @param dma_source DMA source
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_DMA_MASTER Master timer
  *         @arg @ref HAL_HRTIM_DMA_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_DMA_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_DMA_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_DMA_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_DMA_TIME   Timer E
  *         @arg @ref HAL_HRTIM_DMA_TIMF   Timer F
  * @param hdma Pointer to DMA channel handle
  * @note  Each timer (master, TIMA...F) has its own DMA channel.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Input parameter is invalid (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_SetDMA(hal_hrtim_handle_t *hhrtim,
                              hal_hrtim_dma_source_t dma_source,
                              hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_SOURCE(dma_source));
  ASSERT_DBG_PARAM((hdma != NULL));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* link the DMA handle to the HRTIM handle */
  hhrtim->hdma[(uint32_t)dma_source] = hdma;
  hdma->p_parent = hhrtim;

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_DMA */

/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group2
  *  @{
  */
/**
  * @brief Get the global HRTIM state.
  * @param hhrtim Pointer to the HRTIM instance handle.
  * @return hal_hrtim_state_t HAL HRTIM state.
  */
hal_hrtim_state_t HAL_HRTIM_GetState(const hal_hrtim_handle_t *hhrtim)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);

  return hhrtim->global_state;
}

/**
  * @brief  Get the HRTIM timer state.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return HRTIM timer state.
  */
hal_hrtim_timer_state_t HAL_HRTIM_TIM_GetState(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  return hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)];
}

/**
  * @brief  Get the HRTIM output status.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @return HRTIM output status.
  */
hal_hrtim_output_status_t HAL_HRTIM_OUT_GetStatus(const hal_hrtim_handle_t *hhrtim,
                                                  uint32_t output)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_output_status_t output_status = HAL_HRTIM_OUTPUT_DISABLED;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Check output status */
  if (LL_HRTIM_IsEnabledOutput(p_hrtim, output) != 0U)
  {
    output_status = HAL_HRTIM_OUTPUT_ENABLED;
  }
  else if (LL_HRTIM_GetOutputDisableState(p_hrtim, output) != 0u)
  {
    output_status = HAL_HRTIM_OUTPUT_FAULT;
  }
  else
  {
    output_status = HAL_HRTIM_OUTPUT_DISABLED;
  }

  return output_status;

}

/** @brief  Return the HRTIM main clock frequency (fHRTIM).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @note   All HTIM internal clocks are derived from the main HRTIM clock.
  * @return uint32_t  Frequency in Hz.
  *                   0 if the source clock of the HRTIM is not configured or not ready.
  */
uint32_t HAL_HRTIM_GetClockFreq(const hal_hrtim_handle_t *hhrtim)
{
#if !defined(USE_ASSERT_DBG_PARAM) && !defined(USE_ASSERT_DBG_STATE)
  STM32_UNUSED(hhrtim);
#endif /* &USE_ASSERT_DBG_PARAM && !USE_ASSERT_DBG_STATE */

  ASSERT_DBG_PARAM((hhrtim != NULL));
  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  return HAL_RCC_HRTIM1_GetKernelClkFreq();
}
/**
  * @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group3
  *  @{
  */
/**
  * @brief  Precise which interrupts will be used/enabled for the given TIMER when started in interrupt mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  source  Interrupt source.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_INTERRUPT_MASTER
  *         @arg @ref HAL_HRTIM_INTERRUPT_TIMA
  *         @arg @ref HAL_HRTIM_INTERRUPT_TIMB
  *         @arg @ref HAL_HRTIM_INTERRUPT_TIMC
  *         @arg @ref HAL_HRTIM_INTERRUPT_TIMD
  *         @arg @ref HAL_HRTIM_INTERRUPT_TIME
  *         @arg @ref HAL_HRTIM_INTERRUPT_TIMF
  *         @arg @ref HAL_HRTIM_INTERRUPT_COMMON
  * @param  interrupts Interrupt(s) to enable.
  *         It can be a combination of the following values:\n
  *         - For master timer:
  *         @arg @ref HAL_HRTIM_OPT_IT_UPDATE
  *         @arg @ref HAL_HRTIM_OPT_IT_SYNCHRO
  *         @arg @ref HAL_HRTIM_OPT_IT_REPETITION
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP1
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP2
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP3
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP4
  *         \n- For timer A to F:
  *         @arg @ref HAL_HRTIM_OPT_IT_DELAYED_PROT
  *         @arg @ref HAL_HRTIM_OPT_IT_RESET
  *         @arg @ref HAL_HRTIM_OPT_IT_SET1
  *         @arg @ref HAL_HRTIM_OPT_IT_RESET1
  *         @arg @ref HAL_HRTIM_OPT_IT_SET2
  *         @arg @ref HAL_HRTIM_OPT_IT_RESET2
  *         @arg @ref HAL_HRTIM_OPT_IT_CPT1
  *         @arg @ref HAL_HRTIM_OPT_IT_CPT2
  *         @arg @ref HAL_HRTIM_OPT_IT_UPDATE
  *         @arg @ref HAL_HRTIM_OPT_IT_REPETITION
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP1
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP2
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP3
  *         @arg @ref HAL_HRTIM_OPT_IT_CMP4
  *         @arg @ref HAL_HRTIM_OPT_IT_XBAR_OVR_TRIGGER
  *         @arg @ref HAL_HRTIM_OPT_IT_XBAR_OVR_REARM
  *         \n- For HRTIM:
  *         @arg @ref HAL_HRTIM_OPT_IT_BURST_MODE_PERIOD
  *         @arg @ref HAL_HRTIM_OPT_IT_DLL_CALIBRATION
  *         @arg @ref HAL_HRTIM_OPT_IT_SYSFLT
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT1
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT2
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT3
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT4
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT5
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT6
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT7
  *         @arg @ref HAL_HRTIM_OPT_IT_FLT8
  * @note   When the interrupt source is HAL_HRTIM_INTERRUPT_COMMON, this function\n
  *         enables or disables the HRTIM global interrupts as per\n
  *         interrupts configuration.
  * @note   When the interrupt source is the master timer or a timing unit,\n
  *         related interrupts are enabled from within @ref HAL_HRTIM_TIM_Start_IT.
  * @note Burst mode period completed interrupt is included in the master timer interrupt vector (hrtim_it1).
  * @note DLL calibration done interrupt is included in the master timer interrupt vector (hrtim_it1).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_SetConfigInterrupts(hal_hrtim_handle_t *hhrtim,
                                           hal_hrtim_interrupt_src_t source,
                                           uint32_t interrupts)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_INTERRUPT(source, interrupts));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  if (source == HAL_HRTIM_INTERRUPT_COMMON)
  {
    /* Enable or disable HRTIM global interrupts */
    p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

    if (interrupts != HAL_HRTIM_OPT_IT_NONE)
    {
      LL_HRTIM_EnableIT(p_hrtim, interrupts);
    }
    else
    {
      LL_HRTIM_DisableIT(p_hrtim, LL_HRTIM_IER_ALL_IT);
    }
  }
  else
  {
    /* Update interrupts configuration array */
    hhrtim->interrupts[source] = interrupts;
  }

  return HAL_OK;
}

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/**
  * @brief  Precise which DMA requests will be used/enabled for the given TIMER when started in DMA mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param dma_source DMA source
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_DMA_MASTER Master timer
  *         @arg @ref HAL_HRTIM_DMA_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_DMA_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_DMA_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_DMA_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_DMA_TIME   Timer E
  *         @arg @ref HAL_HRTIM_DMA_TIMF   Timer F
  * @param  p_config Pointer to the DMA configuration of the timer.
  * @note   DMA requests are enabled from within @ref HAL_HRTIM_TIM_Start_DMA.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_SetConfigDMA(hal_hrtim_handle_t *hhrtim,
                                    hal_hrtim_dma_source_t dma_source,
                                    hal_hrtim_dma_config_t *p_config)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_config == NULL)
      || ((p_config->requests != HAL_HRTIM_OPT_DMA_NONE)
          && ((p_config->src_addr == 0U)
              || (p_config->dest_addr == 0U)
              || (p_config->size_byte == 0U))))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_DMA_REQUEST(dma_source, p_config->requests));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  /* Update DMA requests configuration array */
  hhrtim->p_dma_config[dma_source] = p_config;

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_DMA */

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group30
  *  @{
  */
/**
  * @brief  Launch the DLL calibration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_ERROR         A periodic calibration operation is on going.
  */
hal_status_t HAL_HRTIM_CalibrateDLL(const hal_hrtim_handle_t *hhrtim)
{
  hal_status_t status = HAL_OK;
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  if (LL_HRTIM_IsEnabledPeriodicDLLCalibration(p_hrtim) != 0U)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Start DLL calibration */
    LL_HRTIM_StartDLLCalibration(p_hrtim);
  }

  return status;
}

/**
  * @brief  Start periodic DLL calibration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  calibration_rate DLL calibration rate.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_StartPeriodicDLLCalibration(const hal_hrtim_handle_t *hhrtim,
                                                   hal_hrtim_calibration_rate_t calibration_rate)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_DLL_CALIBRATION_RATE(calibration_rate));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure and enable periodic DLL calibration */
  LL_HRTIM_SetDLLCalibrationRate(p_hrtim, (uint32_t)calibration_rate);
  LL_HRTIM_EnablePeriodicDLLCalibration(p_hrtim);

  return HAL_OK;
}

/**
  * @brief  Stop periodic DLL calibration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_StopPeriodicDLLCalibration(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable periodic DLL calibration */
  LL_HRTIM_DisablePeriodicDLLCalibration(p_hrtim);

  return HAL_OK;
}

/**
  * @brief  Poll for DLL calibration end in blocking mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timeout_ms  Timeout duration in millisecond.
  * @note   This function clears the DLLRDY flag.
  * @retval HAL_OK      Operation completed successfully.
  * @retval HAL_TIMEOUT DLL calibration not completed within specified timeout.
  */
hal_status_t HAL_HRTIM_PollForDLLCalibration(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timeout_ms)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t tickstart;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get tick count */
  tickstart = HAL_GetTick();

  /* Wait until end of DLL calibration flag is raised */
  while (LL_HRTIM_IsActiveFlag_DLLRDY(p_hrtim) == 0UL)
  {
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (LL_HRTIM_IsActiveFlag_DLLRDY(p_hrtim) == 0UL)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Clear flag */
  LL_HRTIM_ClearFlag_DLLRDY(p_hrtim);

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group4
  *  @{
  */
/**
  * @brief  Configure the pulse generation on the HRTIM synchronization output pin (HRTIM_SCOUT).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  p_config pointer to a @ref hal_hrtim_sync_output_config_t structure that
  *                  contains the synchronization output configuration parameters.
  * @warning This function must not be called if the timer triggering the
  *          synchronization pulse generation is started.
  * @warning This function must be called before configuring the HRTIM_SCOUT GPIO.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_SetSynchroOutput(const hal_hrtim_handle_t *hhrtim,
                                        const hal_hrtim_sync_output_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_SYNC_OUTPUT_SOURCE(p_config->source));
  ASSERT_DBG_PARAM(IS_HRTIM_SYNC_OUTPUT_PULSE(p_config->mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure synchronization output */
  LL_HRTIM_ConfigSyncOut(p_hrtim, (uint32_t)p_config->mode, (uint32_t)p_config->source);

  return HAL_OK;
}

/**
  * @brief  Get the synchronization output configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  p_config  pointer to a @ref hal_hrtim_sync_output_config_t structure that
  *         contains the configuration information for the synchronization output.
  */
void HAL_HRTIM_GetSynchroOutput(const hal_hrtim_handle_t *hhrtim,
                                hal_hrtim_sync_output_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get synchronization output configuration */
  p_config->mode = (hal_hrtim_sync_output_mode_t)LL_HRTIM_GetSyncOutConfig(p_hrtim);
  p_config->source = (hal_hrtim_sync_output_src_t)LL_HRTIM_GetSyncOutSrc(p_hrtim);
}

/**
  * @brief  Set the synchronization input source.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  sync_input_source Synchronisation input source based on @ref hal_hrtim_sync_input_src_t
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_SetSynchroInputSource(const hal_hrtim_handle_t *hhrtim,
                                             hal_hrtim_sync_input_src_t sync_input_source)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  ASSERT_DBG_PARAM(IS_HRTIM_SYNC_INPUT_SOURCE(sync_input_source));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  /* Configure the synchronization input */
  LL_HRTIM_SetSyncInSrc(p_hrtim, (uint32_t)sync_input_source);

  return HAL_OK;
}

/**
  * @brief  Get the synchronization input source.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return Synchronization input source.
  */
hal_hrtim_sync_input_src_t HAL_HRTIM_GetSynchroInputSource(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_sync_input_src_t sync_input_source;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the synchronization input source */
  sync_input_source = (hal_hrtim_sync_input_src_t)LL_HRTIM_GetSyncInSrc(p_hrtim);

  return sync_input_source;
}

/**
  * @brief  Configure the timer's slave mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  slave_mode Slave mode configuration based on @ref hal_hrtim_tim_slave_mode_t
  * @note   The slave mode determines how the timer reacts to a synchronization
  *         input event.
  * @note   A rising edge on the synchronization input (HRTIM_SYNCIN) can start and/or reset the timer's counter.
  * @warning The effect of the synchronization event depends on the timer
  *          operating mode (see @ref HAL_HRTIM_TIM_SetConfig).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetSlaveMode(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_tim_slave_mode_t slave_mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_SLAVE_MODE(slave_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the synchronization mode */
  LL_HRTIM_TIM_SetSynchroMode(p_hrtim, timer, (uint32_t)slave_mode);

  return HAL_OK;
}

/**
  * @brief  Return the timer's slave mode configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Slave mode configuration.
  */
hal_hrtim_tim_slave_mode_t HAL_HRTIM_TIM_GetSlaveMode(const hal_hrtim_handle_t *hhrtim,
                                                      uint32_t timer)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_tim_slave_mode_t slave_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the synchronization mode configuration */
  slave_mode = (hal_hrtim_tim_slave_mode_t)LL_HRTIM_TIM_GetSynchroMode(p_hrtim, timer);

  return slave_mode;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group5
  *  @{
  */
/**
  * @brief  Configure an ADC trigger.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  adc_trigger ADC trigger based on @ref hal_hrtim_adc_trigger_t
  * @param  p_config pointer to a @ref hal_hrtim_adc_sync_config_t structure that
  *                  contains the ADC trigger configuration.
  * @note   The ADC trigger configuration registers support preload functionality,
  *         allowing them to be updated synchronously with their associated timer.
  *         To enable this behavior, preload must be activated for the relevant timer
  *         (see @ref HAL_HRTIM_TIM_EnablePreload).
  *         Additionally, the update event source is configured at the timer level
  *         (see @ref HAL_HRTIM_TIM_SetUpdateSource).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_SetADCSynchro(const hal_hrtim_handle_t *hhrtim,
                                     hal_hrtim_adc_trigger_t adc_trigger,
                                     const hal_hrtim_adc_sync_config_t *p_config)
{
  const HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_ADC_TRIGGER(adc_trigger));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(p_config->update));
  ASSERT_DBG_PARAM(IS_HRTIM_ADC_TRIGGER_SOURCE(adc_trigger, p_config->source));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure that ADC trigger */
  LL_HRTIM_ConfigADCTrig(p_hrtim, (uint32_t)adc_trigger, HRTIM_GET_TIMER_INDEX(p_config->update), p_config->source);

  return HAL_OK;
}

/**
  * @brief  Get the ADC trigger configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  adc_trigger ADC trigger.
  * @param  p_config  pointer to a @ref hal_hrtim_adc_sync_config_t structure that
  *         contains the configuration information for the ADC trigger.
  */
void HAL_HRTIM_GetADCSynchro(const hal_hrtim_handle_t *hhrtim,
                             hal_hrtim_adc_trigger_t adc_trigger,
                             hal_hrtim_adc_sync_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint8_t timer_index;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_ADC_TRIGGER(adc_trigger));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get ADC trigger configuration */
  timer_index = (uint8_t)LL_HRTIM_GetADCTrigUpdate(p_hrtim, (uint32_t)adc_trigger);
  p_config->update = HRTIM_MCR_MCEN << (timer_index & 0xFU);
  p_config->source = LL_HRTIM_GetADCTrigSrc(p_hrtim, (uint32_t)adc_trigger);
}

/**
  * @brief  Set the ADC trigger post-scaler ratio.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  adc_trigger ADC trigger based on @ref hal_hrtim_adc_trigger_t
  * @param  postscaler ADC trigger post-scaler value.
  *         This parameter must be a number between 0 and 31.
  * @note   ADC post-scaling allows to reduce the ADC trigger rate.
  * @note   In up-down mode ADC post-scaling is done as per ADC roll-over mode
  *         configuration (see @ref HAL_HRTIM_TIM_SetRollOverMode).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_SetADCPostscaler(const hal_hrtim_handle_t *hhrtim,
                                        hal_hrtim_adc_trigger_t adc_trigger,
                                        uint8_t postscaler)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_ADC_TRIGGER(adc_trigger));
  ASSERT_DBG_PARAM(IS_HRTIM_ADC_POSTSCALER(postscaler));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the ADC post-scaler */
  LL_HRTIM_SetADCPostScaler(p_hrtim, (uint32_t)adc_trigger, postscaler);

  return HAL_OK;
}

/**
  * @brief  Return the ADC trigger post-scaler ratio.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  adc_trigger ADC trigger based on @ref hal_hrtim_adc_trigger_t
  * @return ADC trigger post-scaler ratio.
  *         Number between 0 and 31.
  */
uint8_t HAL_HRTIM_GetADCPostscaler(const hal_hrtim_handle_t *hhrtim,
                                   hal_hrtim_adc_trigger_t adc_trigger)
{
  HRTIM_TypeDef *p_hrtim;
  uint8_t adc_post_scaler;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_ADC_TRIGGER(adc_trigger));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get ADC post-scaler configuration */
  adc_post_scaler = (uint8_t)LL_HRTIM_GetADCPostScaler(p_hrtim, (uint32_t)adc_trigger);

  return adc_post_scaler;
}
/**
  * @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group6
  *  @{
  */
/**
  * @brief  Configure the DAC trigger.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  dac_trigger DAC trigger based on @ref hal_hrtim_dac_trigger_t
  * @note   A pulse of 1 fHRTIM clock periods, triggered by the timer's update event,
  *         can be generated on one of the 3 hrtim_dac_trgx output.
  * @note   When the same DAC trigger is enabled in multiple timers, the
  *         hrtim_dac_trgx output consists of an OR of all timers update events.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetDACTrigger(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         hal_hrtim_dac_trigger_t dac_trigger)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_DAC_TRIGGER(dac_trigger));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the DAC trigger */
  LL_HRTIM_TIM_SetDACTrig(p_hrtim, timer, (uint32_t)dac_trigger);

  return HAL_OK;
}

/**
  * @brief  Get the DAC trigger configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return DAC trigger.
  */
hal_hrtim_dac_trigger_t HAL_HRTIM_TIM_GetDACTrigger(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_dac_trigger_t dac_trigger;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));
  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get DAC trigger configuration */
  dac_trigger = (hal_hrtim_dac_trigger_t)LL_HRTIM_TIM_GetDACTrig(p_hrtim, timer);

  return dac_trigger;
}

/**
  * @brief  Configure the dual channel DAC triggers (reset trigger and step trigger).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_dual_channel_dac_triggers_config_t structure that
  *                  contains the dual channel DAC triggers configuration.
  * @note   The 2 trigger outputs - hrtim_dac_reset_trgx and hrtim_dac_step_trgx
  *         of the timing unit are configured.
  * @warning Interleaved and balanced idle modes must be disabled when the step trigger
  *          is generated on compare 2 event.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetDualChannelDACTriggers(const hal_hrtim_handle_t *hhrtim,
                                                     uint32_t timer,
                                                     const hal_hrtim_dual_channel_dac_triggers_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_DUAL_CHANNEL_DAC_RESET_TRIGGER(p_config->reset_trigger));
  ASSERT_DBG_PARAM(IS_HRTIM_DUAL_CHANNEL_DAC_STEP_TRIGGER(p_config->step_trigger));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure dual-channel DAC triggers */
  LL_HRTIM_TIM_SetDualDacResetTrigger(p_hrtim, timer, (uint32_t)p_config->reset_trigger);
  LL_HRTIM_TIM_SetDualDacStepTrigger(p_hrtim, timer, (uint32_t)p_config->step_trigger);

  return HAL_OK;
}

/**
  * @brief  Get the dual channel DAC triggers configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config  pointer to a @ref hal_hrtim_dual_channel_dac_triggers_config_t structure that
  *         contains the configuration information for the dual channel DAC triggers.
  */
void HAL_HRTIM_TIM_GetDualChannelDACTriggers(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_dual_channel_dac_triggers_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get dual-channel DAC triggers configuration */
  p_config->reset_trigger =
    (hal_hrtim_dual_channel_dac_reset_trigger_t)LL_HRTIM_TIM_GetDualDacResetTrigger(p_hrtim, timer);

  p_config->step_trigger =
    (hal_hrtim_dual_channel_dac_step_trigger_t)LL_HRTIM_TIM_GetDualDacStepTrigger(p_hrtim, timer);
}

/**
  * @brief  Enable the dual channel DAC triggers.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning This function must not be called if the timer triggering the dual channel
  *          DAC trigger is started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableDualChannelDAC(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable dual-channel DAC triggers */
  LL_HRTIM_TIM_EnableDualDacTrigger(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Disable the dual channel DAC triggers.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableDualChannelDAC(const hal_hrtim_handle_t *hhrtim,
                                                 uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable dual-channel DAC triggers */
  LL_HRTIM_TIM_DisableDualDacTrigger(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Check if the dual channel DAC triggers are enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Dual channel DAC triggers enable status.
  */
hal_hrtim_dual_channel_dac_status_t HAL_HRTIM_TIM_IsEnabledDualChannelDAC(const hal_hrtim_handle_t *hhrtim,
                                                                          uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_dual_channel_dac_status_t dual_channel_dac_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  dual_channel_dac_status = (hal_hrtim_dual_channel_dac_status_t)LL_HRTIM_TIM_IsEnabledDualDacTrigger(p_hrtim, timer);

  return dual_channel_dac_status;
}

/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group7
  *  @{
  */
/**
  * @brief  Set the external event prescaler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  prescaler External event prescaler value based on @ref hal_hrtim_eev_prescaler_t
  * @note   The external event prescaler determines frequency of the external events
  *         sampling clock (fEEVS) used by the digital filters.
  * @note   Calling this function is meaningful only when if the digital noise filter is enabled
  *         for at least one external event.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_EEV_SetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                        hal_hrtim_eev_prescaler_t prescaler)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_PRESCALER(prescaler));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure external event prescaler */
  LL_HRTIM_EE_SetPrescaler(p_hrtim, (uint32_t)prescaler);

  return HAL_OK;
}

/**
  * @brief  Return the external event prescaler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return External event prescaler value.
  */
hal_hrtim_eev_prescaler_t HAL_HRTIM_EEV_GetPrescaler(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_eev_prescaler_t evt_prescaler;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get external event prescaler configuration */
  evt_prescaler = (hal_hrtim_eev_prescaler_t)LL_HRTIM_EE_GetPrescaler(p_hrtim);

  return evt_prescaler;
}

/**
  * @brief  Configure an external event (global configuration).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  event External event.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_EEV1  External event 1
  *         @arg @ref HAL_HRTIM_EEV2  External event 2
  *         @arg @ref HAL_HRTIM_EEV3  External event 3
  *         @arg @ref HAL_HRTIM_EEV4  External event 4
  *         @arg @ref HAL_HRTIM_EEV5  External event 5
  *         @arg @ref HAL_HRTIM_EEV6  External event 6
  *         @arg @ref HAL_HRTIM_EEV7  External event 7
  *         @arg @ref HAL_HRTIM_EEV8  External event 8
  *         @arg @ref HAL_HRTIM_EEV9  External event 9
  *         @arg @ref HAL_HRTIM_EEV10 External event 10
  *         @arg @ref HAL_HRTIM_EEV11 External event 11
  *         @arg @ref HAL_HRTIM_EEV12 External event 12
  *         @arg @ref HAL_HRTIM_EEV13 External event 13
  *         @arg @ref HAL_HRTIM_EEV14 External event 14
  *         @arg @ref HAL_HRTIM_EEV15 External event 15
  *         @arg @ref HAL_HRTIM_EEV16 External event 16
  * @param  p_config pointer to a @ref hal_hrtim_eev_config_t structure that
  *                  contains the external event global configuration.
  * @note   External event configuration is common to all timers.
  * @note   Filter choice is limited to HAL_HRTIM_FDIV1 for external events 6 to 10 and 11 to 13.
  * @note   Mode choice is limited to HAL_HRTIM_EEV_SYNCHRONOUS for 1 to 5 and 14 to 16.
  * @warning This function must not be called once any of the timers using the external event
  *          have been started.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_EEV_SetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t event,
                                     const hal_hrtim_eev_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t evt = (uint32_t)(event & LL_HRTIM_EEV_ID_MSK);
  uint32_t config;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_EEV(event));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_EEV_SOURCE(event, p_config->source));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_SENSITIVITY(p_config->sensitivity));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure event source and sensitivity */
  config = (uint32_t)(((uint32_t)p_config->source & LL_HRTIM_EEV_SRC) >> LL_HRTIM_EEV_SRC_POS) \
           | (uint32_t)p_config->sensitivity;
  LL_HRTIM_EE_Config(p_hrtim, evt, config);

  /* Configure event filter (if supported) */
  if (IS_HRTIM_EEV_FILTER_SUPPORTED(event))
  {
    /* Check the configuration parameters */
    ASSERT_DBG_PARAM(IS_HRTIM_EEV_FILTER(p_config->filter));

    LL_HRTIM_EE_SetFilter(p_hrtim, evt, (uint32_t)p_config->filter);
  }

  /* Configure event fast mode (if supported) */
  if (IS_HRTIM_EEV_FAST_MODE_SUPPORTED(event))
  {
    /* Check the configuration parameters */
    ASSERT_DBG_PARAM(IS_HRTIM_EEV_FAST_MODE(p_config->mode));

    LL_HRTIM_EE_SetFastMode(p_hrtim, evt, (uint32_t)p_config->mode);
  }

  return HAL_OK;
}

/**
  * @brief  Get the external event global configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  event External event.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_EEV1  External event 1
  *         @arg @ref HAL_HRTIM_EEV2  External event 2
  *         @arg @ref HAL_HRTIM_EEV3  External event 3
  *         @arg @ref HAL_HRTIM_EEV4  External event 4
  *         @arg @ref HAL_HRTIM_EEV5  External event 5
  *         @arg @ref HAL_HRTIM_EEV6  External event 6
  *         @arg @ref HAL_HRTIM_EEV7  External event 7
  *         @arg @ref HAL_HRTIM_EEV8  External event 8
  *         @arg @ref HAL_HRTIM_EEV9  External event 9
  *         @arg @ref HAL_HRTIM_EEV10 External event 10
  *         @arg @ref HAL_HRTIM_EEV11 External event 11
  *         @arg @ref HAL_HRTIM_EEV12 External event 12
  *         @arg @ref HAL_HRTIM_EEV13 External event 13
  *         @arg @ref HAL_HRTIM_EEV14 External event 14
  *         @arg @ref HAL_HRTIM_EEV15 External event 15
  *         @arg @ref HAL_HRTIM_EEV16 External event 16
  * @param  p_config pointer to a @ref hal_hrtim_eev_config_t structure that
  *                  contains the external event global configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_EEV_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t event,
                                     hal_hrtim_eev_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t evt = (uint32_t)(event & LL_HRTIM_EEV_ID_MSK);
  uint32_t evt_src;
  uint32_t evt_sns;
  uint32_t source;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_EEV(event));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get external event source configuration */
  evt_src = LL_HRTIM_EE_GetSrc(p_hrtim, evt);
  source = (evt_src << LL_HRTIM_EEV_SRC_POS) | event;
  p_config->source = (hal_hrtim_eev_src_t)source;

  /* Get external event sensitivity configuration */
  evt_sns = LL_HRTIM_EE_GetSensitivity(p_hrtim, evt);
  if (evt_sns == LL_HRTIM_EE_SENSITIVITY_LEVEL)
  {
    p_config->sensitivity = (hal_hrtim_eev_sensitivity_t)LL_HRTIM_EE_GetPolarity(p_hrtim, evt);
  }
  else
  {
    p_config->sensitivity = (hal_hrtim_eev_sensitivity_t)evt_sns;
  }

  /* Get external event filter configuration */
  p_config->filter = HAL_HRTIM_FDIV1;
  if (IS_HRTIM_EEV_FILTER_SUPPORTED(event))
  {
    p_config->filter = (hal_hrtim_filter_t)LL_HRTIM_EE_GetFilter(p_hrtim, evt);
  }

  /* Get external event fast mode configuration */
  p_config->mode = HAL_HRTIM_EEV_SYNCHRONOUS;
  if (IS_HRTIM_EEV_FAST_MODE_SUPPORTED(event))
  {
    p_config->mode = (hal_hrtim_eev_mode_t)LL_HRTIM_EE_GetFastMode(p_hrtim, evt);
  }

  return HAL_OK;
}

/**
  * @brief  Set the combined event source for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  event Combined event.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_EEVA  Combined event A
  *         @arg @ref HAL_HRTIM_EEVB  Combined event B
  *         @arg @ref HAL_HRTIM_EEVC  Combined event C
  *         @arg @ref HAL_HRTIM_EEVD  Combined event D
  *         @arg @ref HAL_HRTIM_EEVE  Combined event E
  *         @arg @ref HAL_HRTIM_EEVF  Combined event F
  *         @arg @ref HAL_HRTIM_EEVG  Combined event G
  *         @arg @ref HAL_HRTIM_EEVH  Combined event H
  *         @arg @ref HAL_HRTIM_EEVI  Combined event I
  *         @arg @ref HAL_HRTIM_EEVJ  Combined event J
  * @param  combined_event_source Combined event source based on @ref hal_hrtim_combined_eev_src_t
  * @warning This function must not be called when the timer is already started.
  * @warning Events can be combined only if they are both in the same mode (synchronous or asynchronous).
  * @warning When two events are combined, at least one of them must be level sensitive.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetCombinedEventSource(const hal_hrtim_handle_t *hhrtim,
                                                  uint32_t timer,
                                                  uint32_t event,
                                                  hal_hrtim_combined_eev_src_t combined_event_source)

{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_EEV(event));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_EEV_SOURCE(event, combined_event_source));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the combined event source */
  LL_HRTIM_TIM_SetCombinedEventSrc(p_hrtim, timer, event, (uint32_t)combined_event_source);

  return HAL_OK;
}

/**
  * @brief  Get the combined event source for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  event Combined event.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_EEVA  Combined event A
  *         @arg @ref HAL_HRTIM_EEVB  Combined event B
  *         @arg @ref HAL_HRTIM_EEVC  Combined event C
  *         @arg @ref HAL_HRTIM_EEVD  Combined event D
  *         @arg @ref HAL_HRTIM_EEVE  Combined event E
  *         @arg @ref HAL_HRTIM_EEVF  Combined event F
  *         @arg @ref HAL_HRTIM_EEVG  Combined event G
  *         @arg @ref HAL_HRTIM_EEVH  Combined event H
  *         @arg @ref HAL_HRTIM_EEVI  Combined event I
  *         @arg @ref HAL_HRTIM_EEVJ  Combined event J
  * @return Combined event source.
  */
hal_hrtim_combined_eev_src_t HAL_HRTIM_TIM_GetCombinedEventSource(const hal_hrtim_handle_t *hhrtim,
                                                                  uint32_t timer,
                                                                  uint32_t event)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_combined_eev_src_t combined_event_source;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_EEV(event));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the external event filter configuration */
  combined_event_source = (hal_hrtim_combined_eev_src_t)
                          LL_HRTIM_TIM_GetCombinedEventSrc(p_hrtim, timer, event);

  return combined_event_source;
}

/**
  * @brief  Configure the event filtering for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  event Combined event.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_EEVA  Combined event A
  *         @arg @ref HAL_HRTIM_EEVB  Combined event B
  *         @arg @ref HAL_HRTIM_EEVC  Combined event C
  *         @arg @ref HAL_HRTIM_EEVD  Combined event D
  *         @arg @ref HAL_HRTIM_EEVE  Combined event E
  *         @arg @ref HAL_HRTIM_EEVF  Combined event F
  *         @arg @ref HAL_HRTIM_EEVG  Combined event G
  *         @arg @ref HAL_HRTIM_EEVH  Combined event H
  *         @arg @ref HAL_HRTIM_EEVI  Combined event I
  *         @arg @ref HAL_HRTIM_EEVJ Combined event J
  * @param  p_config pointer to a @ref hal_hrtim_eev_filter_config_t structure that
  *                  contains the timer related event filtering configuration.
  * @note   Each timing unit provides programmable filter settings that can be
  *         configured separately for each event.
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetEventFilter(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          uint32_t event,
                                          const hal_hrtim_eev_filter_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t evt = (uint32_t)(event & LL_HRTIM_EEV_ID_MSK);

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_EEV(event));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_TIM_EVT_FILTER(p_config->filter));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_EVT_NOTIFICATION(p_config->notification));


  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the external event filter */
  LL_HRTIM_TIM_SetEventFilter(p_hrtim, timer, evt, p_config->filter);

  /* Configure external event postpone mode */
  LL_HRTIM_TIM_SetEventLatchStatus(p_hrtim, timer, evt, (uint32_t)p_config->notification);

  return HAL_OK;
}

/**
  * @brief  Get event filtering configuration for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  event Combined event.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_EEVA  Combined event A
  *         @arg @ref HAL_HRTIM_EEVB  Combined event B
  *         @arg @ref HAL_HRTIM_EEVC  Combined event C
  *         @arg @ref HAL_HRTIM_EEVD  Combined event D
  *         @arg @ref HAL_HRTIM_EEVE  Combined event E
  *         @arg @ref HAL_HRTIM_EEVF  Combined event F
  *         @arg @ref HAL_HRTIM_EEVG  Combined event G
  *         @arg @ref HAL_HRTIM_EEVH  Combined event H
  *         @arg @ref HAL_HRTIM_EEVI  Combined event I
  *         @arg @ref HAL_HRTIM_EEVJ Combined event J
  * @param  p_config pointer to a @ref hal_hrtim_eev_filter_config_t structure that
  *                  contains the timer related event filtering configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetEventFilter(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          uint32_t event,
                                          hal_hrtim_eev_filter_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t evt = (uint32_t)(event & LL_HRTIM_EEV_ID_MSK);

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_EEV(event));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the external event filter configuration */
  p_config->filter = LL_HRTIM_TIM_GetEventFilter(p_hrtim, timer, evt);

  /* Get the external event notification mode configuration */
  p_config->notification = (hal_hrtim_eev_notification_t)LL_HRTIM_TIM_GetEventLatchStatus(p_hrtim, timer, evt);

  return HAL_OK;
}

/**
  * @brief  Configure the event counter for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @param  p_config pointer to a @ref hal_hrtim_eev_counter_config_t structure that
  *                  contains the event counter configuration.
  * @warning This function must not be called when the event counter is enabled
  *          (see @ref HAL_HRTIM_TIM_EnableEventCounter).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetEventCounter(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_eev_counter_t counter,
                                           const hal_hrtim_eev_counter_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_EEV(p_config->event));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER_THRESHOLD(p_config->threshold));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER_RESET_MODE(p_config->reset_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the external event counter */
  LL_HRTIM_TIM_SetEventCounterSource(p_hrtim, timer, (uint32_t)counter, p_config->event);
  LL_HRTIM_TIM_SetEventCounterThreshold(p_hrtim, timer, (uint32_t)counter, p_config->threshold);
  LL_HRTIM_TIM_SetEventCounterResetMode(p_hrtim, timer, (uint32_t)counter, (uint32_t)p_config->reset_mode);

  return HAL_OK;
}

/**
  * @brief  Get the event counter configuration for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @param  p_config pointer to a @ref hal_hrtim_eev_counter_config_t structure that
  *                  contains the event counter configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetEventCounter(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_eev_counter_t counter,
                                           hal_hrtim_eev_counter_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the external event counter configuration */
  p_config->event = LL_HRTIM_TIM_GetEventCounterSource(p_hrtim, timer, (uint32_t)counter);
  p_config->threshold = (uint8_t)LL_HRTIM_TIM_GetEventCounterThreshold(p_hrtim, timer, (uint32_t)counter);
  p_config->reset_mode = (hal_hrtim_eev_counter_reset_mode_t)
                         LL_HRTIM_TIM_GetEventCounterResetMode(p_hrtim, timer, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Set the event counter threshold for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @param  threshold Event counter threshold value.
  *         This parameter must be a number between 0 and 63.
  * @note   The external event is propagated to the timer only when the number of
  *         active edges is greater than or equal to the configured threshold value plus one.
  * @note   After enabling the external event counter, the threshold value can be
  *         modified on-the-fly at any time.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetEventCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer,
                                                    hal_hrtim_eev_counter_t counter,
                                                    uint8_t threshold)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER_THRESHOLD(threshold));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the external event counter threshold */
  LL_HRTIM_TIM_SetEventCounterThreshold(p_hrtim, timer, (uint32_t)counter, threshold);

  return HAL_OK;
}

/**
  * @brief  Return the event counter threshold for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @return Event counter threshold value.
  *         Number between 0 and 63.
  */
uint8_t HAL_HRTIM_TIM_GetEventCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer,
                                               hal_hrtim_eev_counter_t counter)
{
  HRTIM_TypeDef *p_hrtim;
  uint8_t threshold;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the external event counter threshold configuration */
  threshold = (uint8_t)LL_HRTIM_TIM_GetEventCounterThreshold(p_hrtim, timer, (uint32_t)counter);

  return threshold;
}

/**
  * @brief  Enable the event counter for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableEventCounter(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_eev_counter_t counter)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable the external event counter */
  LL_HRTIM_TIM_EnableEventCounter(p_hrtim, timer, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Disable the event counter for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableEventCounter(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer,
                                               hal_hrtim_eev_counter_t counter)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable the external event counter */
  LL_HRTIM_TIM_DisableEventCounter(p_hrtim, timer, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @brief  Check if the event counter of a timing unit is enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @return Event counter enable status.
  */
hal_hrtim_eev_counter_status_t HAL_HRTIM_TIM_IsEnabledEventCounter(const hal_hrtim_handle_t *hhrtim,
                                                                   uint32_t timer,
                                                                   hal_hrtim_eev_counter_t counter)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_eev_counter_status_t evt_counter_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  evt_counter_status = (hal_hrtim_eev_counter_status_t)
                       LL_HRTIM_TIM_IsEnabledEventCounter(p_hrtim, timer, (uint32_t)counter);

  return evt_counter_status;
}

/**
  * @brief  Reset the event counter of a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter Event counter identifier based on @ref hal_hrtim_eev_counter_t.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_ResetEventCounter(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_eev_counter_t counter)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_EEV_COUNTER(counter));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Reset the external event counter */
  LL_HRTIM_TIM_ResetEventCounter(p_hrtim, timer, (uint32_t)counter);

  return HAL_OK;
}

/**
  * @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group8
  *  @{
  */
/**
  * @brief  Set the fault input prescaler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  prescaler Fault input prescaler value based on @ref hal_hrtim_flt_prescaler_t.
  * @note   The fault prescaler determines frequency of the fault inputs
  *         sampling clock (fFLTS) used by the digital filters.
  * @warning This function must be called before enabling any fault input
  *          (see @ref HAL_HRTIM_FLT_Enable).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_SetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                        hal_hrtim_flt_prescaler_t prescaler)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT_PRESCALER(prescaler));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set fault inputs prescaler */
  LL_HRTIM_FLT_SetPrescaler(p_hrtim, (uint32_t)prescaler);

  return HAL_OK;
}

/**
  * @brief  Return the external event prescaler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return Fault input prescaler value.
  */
hal_hrtim_flt_prescaler_t HAL_HRTIM_FLT_GetPrescaler(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_flt_prescaler_t fault_prescaler;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get fault inputs prescaler */
  fault_prescaler = (hal_hrtim_flt_prescaler_t)LL_HRTIM_FLT_GetPrescaler(p_hrtim);

  return fault_prescaler;
}

/**
  * @brief  Configure fault input (global configuration).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @param  p_config pointer to a @ref hal_hrtim_flt_config_t structure that
  *                  contains the fault input global configuration.
  * @note   Fault input configuration is common to all timers.
  * @note   For functional safety purpose fault input configuration can be
  *         frozen until the next HRTIM or system reset (see @ref HAL_HRTIM_FLT_Lock).
  * @warning This function must not be called if the fault input is enabled
  *          (see @ref HAL_HRTIM_FLT_Enable).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_FLT_SetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t fault,
                                     const hal_hrtim_flt_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t config;
  uint32_t fltsrc;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_FLT_SOURCE(fault, p_config->source));
  ASSERT_DBG_PARAM(IS_HRTIM_FLT_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_HRTIM_FLT_FILTER(p_config->filter));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the fault input source and polarity */
  fltsrc = hrtim_hal_to_ll_fltsrc(p_config->source);
  config = (uint32_t)(fltsrc | (uint32_t)p_config->polarity);
  LL_HRTIM_FLT_Config(p_hrtim, fault, config);

  /* Configure the fault input filter */
  LL_HRTIM_FLT_SetFilter(p_hrtim, fault, (uint32_t)p_config->filter);

  return HAL_OK;
}

/**
  * @brief  Get the fault input global configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @param  p_config pointer to a @ref hal_hrtim_flt_config_t structure that
  *                  contains the fault input global configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t fault,
                                     hal_hrtim_flt_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t fltsrc;
  uint32_t fltf;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get fault input source configuration */
  fltsrc = LL_HRTIM_FLT_GetSrc(p_hrtim, fault);
  p_config->source = (hal_hrtim_flt_src_t)hrtim_ll_to_hal_fltsrc(fault, fltsrc);

  /* Get fault input polarity configuration */
  p_config->polarity = (hal_hrtim_flt_polarity_t)LL_HRTIM_FLT_GetPolarity(p_hrtim, fault);

  /* Get fault input filter configuration */
  fltf = LL_HRTIM_FLT_GetFilter(p_hrtim, fault);
  p_config->filter = (hal_hrtim_filter_t)fltf;

  return HAL_OK;
}

/**
  * @brief  Set the fault blanking window.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @param blanking Fault blanking window selection based on @ref hal_hrtim_flt_blk_t.
  * @note   For functional safety purpose fault input configuration can be
  *         frozen until the next HRTIM or system reset (see @ref HAL_HRTIM_FLT_Lock).
  * @warning This function must not be called if the fault input is enabled
  *          (see @ref HAL_HRTIM_FLT_Enable).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_SetBlanking(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t fault,
                                       hal_hrtim_flt_blk_t blanking)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t fltblks;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));
  ASSERT_DBG_PARAM(IS_HRTIM_FLT_BLANKING(fault, blanking));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the fault blanking source */
  fltblks = hrtim_hal_to_ll_fltblks(blanking);
  LL_HRTIM_FLT_SetBlankingSrc(p_hrtim, fault, fltblks);

  return HAL_OK;
}

/**
  * @brief  Return the fault blanking window.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @return Fault blanking window selection.
  */
hal_hrtim_flt_blk_t HAL_HRTIM_FLT_GetBlanking(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_flt_blk_t fault_blanking;
  uint32_t fltblks;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get fault blanking source configuration */
  fltblks = LL_HRTIM_FLT_GetBlankingSrc(p_hrtim, fault);
  fault_blanking = hrtim_ll_to_hal_fltblks(fault, fltblks);

  return fault_blanking;
}

/**
  * @brief  Enable the fault blanking.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @warning This function must not be called if the fault input is enabled
  *          (see @ref HAL_HRTIM_FLT_Enable).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_EnableBlanking(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable fault blanking */
  LL_HRTIM_FLT_EnableBlanking(p_hrtim, fault);

  return HAL_OK;
}

/**
  * @brief  Disable the fault blanking.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @warning This function must not be called if the fault input is enabled
  *          (see @ref HAL_HRTIM_FLT_Enable).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_DisableBlanking(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable fault blanking */
  LL_HRTIM_FLT_DisableBlanking(p_hrtim, fault);

  return HAL_OK;
}

/**
  * @brief  Check if the fault blanking is enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @return Fault blanking enable status.
  */
hal_hrtim_flt_blk_status_t HAL_HRTIM_FLT_IsEnabledBlanking(const hal_hrtim_handle_t *hhrtim,
                                                           uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_flt_blk_status_t flt_blanking_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  flt_blanking_status = (hal_hrtim_flt_blk_status_t)LL_HRTIM_FLT_IsEnabledBlanking(p_hrtim, fault);

  return flt_blanking_status;
}

/**
  * @brief  Enable the fault input.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @note   For functional safety purpose fault input configuration can be
  *         frozen until the next HRTIM or system reset (see @ref HAL_HRTIM_FLT_Lock).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_Enable(const hal_hrtim_handle_t *hhrtim,
                                  uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable fault input */
  LL_HRTIM_FLT_Enable(p_hrtim, fault);

  return HAL_OK;
}

/**
  * @brief  Disable the fault input.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @note   For functional safety purpose fault input configuration can be
  *         frozen until the next HRTIM or system reset (see @ref HAL_HRTIM_FLT_Lock).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_Disable(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable fault input */
  LL_HRTIM_FLT_Disable(p_hrtim, fault);

  return HAL_OK;
}

/**
  * @brief  Check if the fault input is enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @return Fault input enable status.
  */
hal_hrtim_flt_status_t HAL_HRTIM_FLT_IsEnabled(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_flt_status_t flt_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  flt_status = (hal_hrtim_flt_status_t)LL_HRTIM_FLT_IsEnabled(p_hrtim, fault);

  return flt_status;
}

/**
  * @brief  Lock the fault input configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @note   This function protects the fault configuration against spurious
  *         write access.
  * @note   Once a fault configuration has been locked, it cannot be modified
  *         till the next HRTIM or system reset.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_Lock(const hal_hrtim_handle_t *hhrtim,
                                uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Lock the fault input configuration */
  LL_HRTIM_FLT_Lock(p_hrtim, fault);

  return HAL_OK;
}

/**
  * @brief  Configure the HRTIM fault input counter.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @param  p_config pointer to a @ref hal_hrtim_flt_counter_config_t structure that
  *                  contains the fault input counter configuration.
  * @warning This function must not be called if the fault input is enabled
  *          (see @ref HAL_HRTIM_FLT_Enable).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_FLT_SetCounter(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t fault,
                                      const hal_hrtim_flt_counter_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_FLT_COUNTER_THRESHOLD(p_config->threshold));
  ASSERT_DBG_PARAM(IS_HRTIM_FLT_COUNTER_RESET_MODE(p_config->reset_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the fault counter */
  LL_HRTIM_FLT_SetCounterThreshold(p_hrtim, fault, p_config->threshold);
  LL_HRTIM_FLT_SetResetMode(p_hrtim, fault, (uint32_t)p_config->reset_mode);

  return HAL_OK;
}

/**
  * @brief  Get the fault counter configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @param  p_config pointer to a @ref hal_hrtim_flt_counter_config_t structure that
  *                  contains the fault counter configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_GetCounter(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t fault,
                                      hal_hrtim_flt_counter_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the fault event counter configuration */
  p_config->threshold = (uint8_t)LL_HRTIM_FLT_GetCounterThreshold(p_hrtim, fault);
  p_config->reset_mode = (hal_hrtim_flt_counter_reset_mode_t)
                         LL_HRTIM_FLT_GetResetMode(p_hrtim, fault);

  return HAL_OK;
}

/**
  * @brief  Reset the HRTIM fault input counter.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_ResetCounter(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Reset the fault counter */
  LL_HRTIM_FLT_ResetCounter(p_hrtim, fault);

  return HAL_OK;
}

/**
  * @brief  Set the counter threshold for a fault input counter.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @param  threshold Fault input counter threshold value.
  *         This parameter must be a number between 0 and 7.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_FLT_SetCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t fault,
                                               uint8_t threshold)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));
  ASSERT_DBG_PARAM(IS_HRTIM_FLT_COUNTER_THRESHOLD(threshold));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the fault counter threshold*/
  LL_HRTIM_FLT_SetCounterThreshold(p_hrtim, fault, threshold);

  return HAL_OK;
}

/**
  * @brief  Return the counter threshold for a fault input.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1     Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2     Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3     Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4     Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5     Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6     Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7     Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8     Fault input 8
  * @return Fault counter threshold value.
  *         Number between 0 and 7.
  */
uint8_t HAL_HRTIM_FLT_GetCounterThreshold(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;
  uint8_t threshold;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the fault event counter configuration */
  threshold = (uint8_t)LL_HRTIM_FLT_GetCounterThreshold(p_hrtim, fault);

  return threshold;
}

/**
  * @brief  Enable fault input(s) at timing unit level.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  faults Fault input(s) to enable for the timing unit.
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_FLT1       Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2       Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3       Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4       Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5       Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6       Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7       Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8       Fault input 8
  *         @arg @ref HAL_HRTIM_FLT1_FLT2  Fault input 1 AND Fault input 2
  *         @arg @ref HAL_HRTIM_FLT2_FLT3  Fault input 2 AND Fault input 3
  *         @arg @ref HAL_HRTIM_FLT3_FLT4  Fault input 3 AND Fault input 4
  *         @arg @ref HAL_HRTIM_FLT4_FLT5  Fault input 4 AND Fault input 5
  *         @arg @ref HAL_HRTIM_FLT5_FLT6  Fault input 5 AND Fault input 6
  *         @arg @ref HAL_HRTIM_FLT6_FLT7  Fault input 6 AND Fault input 7
  *         @arg @ref HAL_HRTIM_FLT7_FLT8  Fault input 7 AND Fault input 8
  * @note   Multiple fault inputs can be ORed to disable the outputs protected
  *         by the fault mechanism.
  * @note   For functional safety purpose fault enabling/disabling at timing
  *         unit level can be frozen until the next HRTIM or system reset
  *         (see @ref HAL_HRTIM_TIM_LockFault).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableFault(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer,
                                       uint32_t faults)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_FAULTS(faults));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable the fault inputs at timing unit level */
  LL_HRTIM_TIM_EnableFault(p_hrtim, timer, faults);

  return HAL_OK;
}

/**
  * @brief  Disable fault input(s) at timing unit level.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  faults Fault input(s) to disable for the timing unit.
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_FLT1       Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2       Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3       Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4       Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5       Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6       Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7       Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8       Fault input 8
  *         @arg @ref HAL_HRTIM_FLT1_FLT2  Fault input 1 AND Fault input 2
  *         @arg @ref HAL_HRTIM_FLT2_FLT3  Fault input 2 AND Fault input 3
  *         @arg @ref HAL_HRTIM_FLT3_FLT4  Fault input 3 AND Fault input 4
  *         @arg @ref HAL_HRTIM_FLT4_FLT5  Fault input 4 AND Fault input 5
  *         @arg @ref HAL_HRTIM_FLT5_FLT6  Fault input 5 AND Fault input 6
  *         @arg @ref HAL_HRTIM_FLT6_FLT7  Fault input 6 AND Fault input 7
  *         @arg @ref HAL_HRTIM_FLT7_FLT8  Fault input 7 AND Fault input 8
  * @note   For functional safety purpose fault enabling/disabling at timing
  *         unit level can be frozen until the next HRTIM or system reset
  *         (see @ref HAL_HRTIM_TIM_LockFault).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableFault(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        uint32_t faults)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_FAULTS(faults));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable the fault inputs at timing unit level */
  LL_HRTIM_TIM_DisableFault(p_hrtim, timer, faults);

  return HAL_OK;
}

/**
  * @brief  Check if a fault input is enabled for a given timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  fault Fault input.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_FLT1       Fault input 1
  *         @arg @ref HAL_HRTIM_FLT2       Fault input 2
  *         @arg @ref HAL_HRTIM_FLT3       Fault input 3
  *         @arg @ref HAL_HRTIM_FLT4       Fault input 4
  *         @arg @ref HAL_HRTIM_FLT5       Fault input 5
  *         @arg @ref HAL_HRTIM_FLT6       Fault input 6
  *         @arg @ref HAL_HRTIM_FLT7       Fault input 7
  *         @arg @ref HAL_HRTIM_FLT8       Fault input 8
  *         @arg @ref HAL_HRTIM_FLT1_FLT2  Fault input 1 AND Fault input 2
  *         @arg @ref HAL_HRTIM_FLT2_FLT3  Fault input 2 AND Fault input 3
  *         @arg @ref HAL_HRTIM_FLT3_FLT4  Fault input 3 AND Fault input 4
  *         @arg @ref HAL_HRTIM_FLT4_FLT5  Fault input 4 AND Fault input 5
  *         @arg @ref HAL_HRTIM_FLT5_FLT6  Fault input 5 AND Fault input 6
  *         @arg @ref HAL_HRTIM_FLT6_FLT7  Fault input 6 AND Fault input 7
  *         @arg @ref HAL_HRTIM_FLT7_FLT8  Fault input 7 AND Fault input 8
  * @return Fault input enable status at timer level.
  */
hal_hrtim_flt_status_t HAL_HRTIM_TIM_IsEnabledFault(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer,
                                                    uint32_t fault)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_flt_status_t flt_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_FLT(fault));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  flt_status = (hal_hrtim_flt_status_t)LL_HRTIM_TIM_IsEnabledFault(p_hrtim, timer, fault);

  return flt_status;
}

/**
  * @brief  Lock the fault input configuration for a given timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Once a fault enabling/disabling at timing level has been locked,
  *         it cannot be modified till the next HRTIM or system reset.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_LockFault(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Lock the fault configuration at timing unit level */
  LL_HRTIM_TIM_LockFault(p_hrtim, timer);

  return HAL_OK;
}
/**
  * @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group9
  *  @{
  */
/**
  * @brief  Configure the burst mode controller.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  p_config pointer to a @ref hal_hrtim_burst_mode_config_t structure that
  *                  contains the burst mode controller configuration.
  * @note   The burst mode controller counter clock (fBRST) can be sourced from
  *         multiple options, including a frequency derived from fHRTIM,
  *         ranging from fHRTIM down to fHRTIM divided by 32768.
  * @note   Burst mode triggers can be combined to have multiple concurrent
  *         triggers.
  * @warning This function must not be called when the burst mode controller
  *          is enabled (see @ref HAL_HRTIM_EnableBurstMode).
  * @warning The number of idle periods cannot be set to 0 (idle_periods = 0)
  *          when fHRTIM is selected as the burst mode controller clock source
  *          (clock = HAL_HRTIM_BURST_MODE_CLK_HRTIM) without a prescaler
  *          (prescaler = HAL_HRTIM_BURST_MODE_DIV1)
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_SetConfigBurstMode(const hal_hrtim_handle_t *hhrtim,
                                          const hal_hrtim_burst_mode_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_burst_mode_prescaler_t prescaler = HAL_HRTIM_BURST_MODE_DIV1;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
  else if ((p_config->clock == HAL_HRTIM_BURST_MODE_CLK_HRTIM) \
           && (p_config->prescaler == HAL_HRTIM_BURST_MODE_DIV1)  \
           && (p_config->idle_periods == 0U))
  {
    return HAL_INVALID_PARAM;
  }
  else
  {
    /* MISRAC2012-Rule-15.7 */
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_BM_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_HRTIM_BM_CLOCK(p_config->clock));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the burst mode prescaler only if the burst mode controller counter
     is clocked the main HRTIM clock (fHRTIM) */
  if (p_config->clock == HAL_HRTIM_BURST_MODE_CLK_HRTIM)
  {
    /* Check the configuration parameters */
    ASSERT_DBG_PARAM(IS_HRTIM_BM_PRESCALER(p_config->prescaler));

    prescaler = p_config->prescaler;
  }

  /* Configure the Burst Mode (BM) controller */
  LL_HRTIM_BM_Config(p_hrtim, ((uint32_t)p_config->mode    \
                               | (uint32_t)p_config->clock \
                               | (uint32_t)prescaler));
  LL_HRTIM_BM_SetPeriod(p_hrtim, p_config->period);
  LL_HRTIM_BM_SetCompare(p_hrtim, p_config->idle_periods);
  LL_HRTIM_BM_SetTrig(p_hrtim, p_config->triggers);


  return HAL_OK;
}

/**
  * @brief  Get the burst mode controller configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  p_config pointer to a @ref hal_hrtim_burst_mode_config_t structure that
  *                  contains the burst mode controller configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_GetConfigBurstMode(const hal_hrtim_handle_t *hhrtim,
                                          hal_hrtim_burst_mode_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the burst mode controller configuration */
  p_config->mode  = (hal_hrtim_burst_mode_operating_mode_t)LL_HRTIM_BM_GetMode(p_hrtim);
  p_config->clock = (hal_hrtim_burst_mode_clock_src_t)LL_HRTIM_BM_GetClockSrc(p_hrtim);
  p_config->prescaler = (hal_hrtim_burst_mode_prescaler_t)LL_HRTIM_BM_GetPrescaler(p_hrtim);
  p_config->period = (uint16_t)LL_HRTIM_BM_GetPeriod(p_hrtim);
  p_config->idle_periods = (uint16_t)LL_HRTIM_BM_GetCompare(p_hrtim);
  p_config->triggers = LL_HRTIM_BM_GetTrig(p_hrtim);

  return HAL_OK;
}

#if defined(PLAY1)

/**
  * @brief  Set the burst mode trigger input source (hrtim_bm_trg).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  burst_mode_trigger_input burst mode trigger input (hrtim_bm_trg)
                                     based on @ref hal_hrtim_burst_mode_trigger_input_t.
  * @note   This function can be called to select the source or the burst mode trigger input (hrtim_bm_trg)
  *         when the on-chip event is selected as one of the burst mode trigger sources
  *         (see @ref HAL_HRTIM_SetConfigBurstMode).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_SetBurstModeTriggerInput(const hal_hrtim_handle_t *hhrtim,
                                                const hal_hrtim_burst_mode_trigger_input_t burst_mode_trigger_input)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER_BURST_TRIGGER_INPUT(burst_mode_trigger_input));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the burst mode controller trigger input source */
  LL_HRTIM_BM_SetTrigInputSrc(p_hrtim, (uint32_t)burst_mode_trigger_input);

  return HAL_OK;
}

/**
  * @brief  Return the burst mode trigger input source (hrtim_bm_trg).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return burst mode trigger input (hrtim_bm_trg) source.
  */
hal_hrtim_burst_mode_trigger_input_t HAL_HRTIM_GetBurstModeTriggerInput(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_burst_mode_trigger_input_t burst_mode_trigger_input;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the burst mode controller trigger input source */
  burst_mode_trigger_input = (hal_hrtim_burst_mode_trigger_input_t)
                             LL_HRTIM_BM_GetTrigInputSrc(p_hrtim);

  return burst_mode_trigger_input;
}
#endif /* PLAY1 */

/**
  * @brief  Set the burst mode controller period.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  period Overall burst mode period value.
  * @warning This function must not be called when the burst mode controller
  *          is enabled (see @ref HAL_HRTIM_EnableBurstMode).
  * @warning the burst mode controller period must not be null when the burst
  *          mode controller is enabled (see @ref HAL_HRTIM_EnableBurstMode).
  * @warning The burst mode period must not be less than or equal to the deadtime
  *          duration(see @ref HAL_HRTIM_TIM_SetConfigDeadtime).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_SetBurstModePeriod(const hal_hrtim_handle_t *hhrtim,
                                          uint16_t period)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the Burst Mode (BM) controller period */
  LL_HRTIM_BM_SetPeriod(p_hrtim, period);

  return HAL_OK;
}

/**
  * @brief  Return the overall burst mode controller period value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return Overall burst mode period value.
  */
uint16_t HAL_HRTIM_GetBurstModePeriod(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;
  uint16_t period;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the Burst Mode (BM) controller period configuration */
  period = (uint16_t)LL_HRTIM_BM_GetPeriod(p_hrtim);

  return period;
}

/**
  * @brief  Set the burst mode controller number of idle periods.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  idle_periods Number of idle periods.
  * @note   The burst mode  controller idle period corresponds to the number of
  *         timer periods during which the concerned outputs are in idle state
  *         (see @ref HAL_HRTIM_OUT_SetBurstMode).
  * @warning The number of idle periods cannot be set to 0 when fHRTIM is selected
  *          as the burst mode controller clock source (HAL_HRTIM_BURST_MODE_CLK_HRTIM)
  *          without a prescaler (HAL_HRTIM_BURST_MODE_DIV1).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_SetBurstModeIdlePeriods(hal_hrtim_handle_t *hhrtim,
                                               uint16_t idle_periods)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  hal_hrtim_burst_mode_clock_src_t clock;
  hal_hrtim_burst_mode_prescaler_t prescaler;

  clock = (hal_hrtim_burst_mode_clock_src_t)LL_HRTIM_BM_GetClockSrc(p_hrtim);
  prescaler = (hal_hrtim_burst_mode_prescaler_t)LL_HRTIM_BM_GetPrescaler(p_hrtim);

  if ((clock == HAL_HRTIM_BURST_MODE_CLK_HRTIM) \
      && (prescaler == HAL_HRTIM_BURST_MODE_DIV1)  \
      && (idle_periods == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  /* Configure the Burst Mode (BM) controller number of idle periods */
  LL_HRTIM_BM_SetCompare(p_hrtim, idle_periods);

  return HAL_OK;
}

/**
  * @brief  Return the burst mode controller number of idle periods.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return Burst mode idle period value.
  */
uint16_t HAL_HRTIM_GetBurstModeIdlePeriods(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;
  uint16_t idle_periods;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the Burst Mode (BM) controller number of idle periods configuration */
  idle_periods = (uint16_t)LL_HRTIM_BM_GetCompare(p_hrtim);

  return idle_periods;
}

/**
  * @brief  Set the burst mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  timer_burst_mode Timer burst mode based on @ref hal_hrtim_timer_burst_mode_t.
  * @note   Specifies how the timer behaves during a burst mode operation.
  * @warning This function must not be called when the burst mode controller
  *          is enabled (see @ref HAL_HRTIM_EnableBurstMode).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_timer_burst_mode_t timer_burst_mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER_BURST_MODE(timer_burst_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the timer burst mode */
  LL_HRTIM_TIM_SetBurstModeOption(p_hrtim, timer, (uint32_t)timer_burst_mode);

  return HAL_OK;
}

/**
  * @brief  Return the burst mode of a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return HRTIM timer burst mode.
  */
hal_hrtim_timer_burst_mode_t HAL_HRTIM_TIM_GetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_timer_burst_mode_t timer_burst_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the timer burst mode configuration */
  timer_burst_mode = (hal_hrtim_timer_burst_mode_t)
                     LL_HRTIM_TIM_GetBurstModeOption(p_hrtim, timer);

  return timer_burst_mode;
}

/**
  * @brief  Set the burst mode of an HRTIM output.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @param  output_burst_mode Output burst mode configuration based on @ref hal_hrtim_output_burst_mode_t.
  * @note   The table blow summarizes the programming of the IDLEMx and the DIDLx
  *         bits of the HRTIM_OUTxR register as per selected output burst mode.
  *
  *         output_burst_mode       | IDLEMx | DIDLx | Comment
  *        ------------------------ | ------ | ----- | --------
  *         BURST_MODE_DISABLED     |    0   |   x   | The output is not affected by the burst mode operation
  *         BURST_MODE_IMMEDIATE    |    1   |   0   | Configured IDLE state is applied immediately to the output
  *         BURST_MODE_DELAYED (*)  |    1   |   1   | Deadtime is inserted on output before entering the IDLE state
  *
  *       (*) When Delayed burst mode entry is selected, positive rising/falling
  *       deadtimes must be configured (see @ref HAL_HRTIM_TIM_SetConfigDeadtime).
  * @warning This function must not be called when the burst mode controller
  *          is enabled (see @ref HAL_HRTIM_EnableBurstMode) or when the timing
  *          unit controlling the outptut is started (see @ref HAL_HRTIM_OUT_Enable).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_SetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t output,
                                        hal_hrtim_output_burst_mode_t output_burst_mode)
{
  /*#warning "Deadtime insertion when entering the idle state during a
  burst mode operation is allowed only under the following conditions:
       - the outputs is active during the burst mode (IDLES=1U)
       - positive deadtimes (SDTR/SDTF set to 0U)"*/
  HRTIM_TypeDef *p_hrtim;
  uint32_t idlem = (uint32_t)output_burst_mode & HRTIM_OUTxR_IDLEM1;
  uint32_t didl = (uint32_t)output_burst_mode & HRTIM_OUTxR_DIDL1;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT_BURST_MODE(output_burst_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX_FROM_OUTPUT(output)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the output delayed burst mode entry */
  LL_HRTIM_OUT_SetBMEntryMode(p_hrtim, output, didl);

  /* Configure the output idle mode */
  LL_HRTIM_OUT_SetIdleMode(p_hrtim, output, idlem);

  return HAL_OK;
}

/**
  * @brief  Return the burst mode of an HRTIM output.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @return HRTIM output burst mode.
  */
hal_hrtim_output_burst_mode_t HAL_HRTIM_OUT_GetBurstMode(const hal_hrtim_handle_t *hhrtim,
                                                         uint32_t output)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t output_burst_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the output burst mode configuration */
  output_burst_mode = LL_HRTIM_OUT_GetBMEntryMode(p_hrtim, output);
  output_burst_mode |= LL_HRTIM_OUT_GetIdleMode(p_hrtim, output);

  return (hal_hrtim_output_burst_mode_t)output_burst_mode;
}

/**
  * @brief  Enable burst mode preload.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @note   Allows to have both the burst mode compare (BMCMPR) and period (BMPER)
  *         registers preloaded.
  * @note   When burst mode preload is enabled, the transfer from preload to active
  *         register happens:
  *           - when the burst mode is enabled (@ref HAL_HRTIM_EnableBurstMode),
  *           - at the end of the burst mode period.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_EnableBurstModePreload(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable HRTIM_BMCMPR and HRTIM_BMPER registers preload */
  LL_HRTIM_BM_EnablePreload(p_hrtim);

  return HAL_OK;
}

/**
  * @brief  Disable burst mode preload.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @note   When burst mode preload is disabled, write access into BMCMPR and BMPER
  *         directly updates the active register.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_DisableBurstModePreload(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable HRTIM_BMCMPR and HRTIM_BMPER registers preload */
  LL_HRTIM_BM_DisablePreload(p_hrtim);

  return HAL_OK;
}

/**
  * @brief  Check if burst mode preload is enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return Burst mode preload enable status.
  */
hal_hrtim_burst_mode_preload_status_t HAL_HRTIM_IsEnabledBurstModePreload(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_burst_mode_preload_status_t burst_mode_preload_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  burst_mode_preload_status = (hal_hrtim_burst_mode_preload_status_t)LL_HRTIM_BM_IsEnabledPreload(p_hrtim);

  return burst_mode_preload_status;
}

/**
  * @brief  Enable the burst mode controller.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @note   Once enabled, the burst mode controller is ready to receive the start trigger.
  * @warning It is necessary to have the counter enabled before using the burst
  *          mode on a given timing unit (see @ref HAL_HRTIM_TIM_Start).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_EnableBurstMode(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable the burst mode controller */
  LL_HRTIM_BM_Enable(p_hrtim);

  return HAL_OK;
}

/**
  * @brief  Disable the burst mode controller.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @note   This function can be called to terminate an on-going burst mode.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_DisableBurstMode(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable the burst mode controller */
  LL_HRTIM_BM_Disable(p_hrtim);

  return HAL_OK;
}

/**
  * @brief  Check if burst mode controller is enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return Burst mode controller enable status.
  */
hal_hrtim_burst_mode_status_t HAL_HRTIM_IsEnabledBurstMode(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  return (hal_hrtim_burst_mode_status_t)
         LL_HRTIM_BM_IsEnabled(p_hrtim);
}

/**
  * @brief  Start the burst mode operation immediately.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @warning This function has no effect if the burst mode controller isn't
  *          enabled (@ref HAL_HRTIM_EnableBurstMode).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_StartBurstMode(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Starts the burst mode operation */
  LL_HRTIM_BM_Start(p_hrtim);

  return HAL_OK;
}

/**
  * @brief  Stop the burst mode operation.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_StopBurstMode(const hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Burst mode early termination */
  LL_HRTIM_BM_Stop(p_hrtim);

  return HAL_OK;
}


/**
  * @brief  Return the burst mode operating status.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @return hal_hrtim_burst_mode_operating_status_t burst mode operating status.
  */
hal_hrtim_burst_mode_operating_status_t HAL_HRTIM_GetBurstModeOperatingStatus(const hal_hrtim_handle_t *hhrtim)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_burst_mode_operating_status_t burst_mode_operating_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  burst_mode_operating_status = (hal_hrtim_burst_mode_operating_status_t)LL_HRTIM_BM_GetStatus(p_hrtim);

  return burst_mode_operating_status;
}
/**
  *  @}
  */

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/** @addtogroup HRTIM_Exported_Functions_Group10
  *  @{
  */
/**
  * @brief  Configure the DMA burst operation.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  p_config pointer to a @ref hal_hrtim_dmaburst_config_t structure that
  *                  contains the DMA burst configuration.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_SetConfigDMABurst(const hal_hrtim_handle_t *hhrtim,
                                         const hal_hrtim_dmaburst_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /*  ASSERT_DBG_PARAM(IS_HRTIM_DMA_REQUEST(p_config->timer, p_config->requests));
  #warning "hal_hrtim_dmaburst_config_t: uint32_t timer => hal_hrtim_dma_source_t dma_source"*/
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_BURST_MASTER_UPDATE_REGISTERS(p_config->master_update));
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_BURST_TIMING_UNIT_UPDATE_REGISTERS(p_config->timer_a_update));
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_BURST_TIMING_UNIT_UPDATE_REGISTERS(p_config->timer_b_update));
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_BURST_TIMING_UNIT_UPDATE_REGISTERS(p_config->timer_c_update));
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_BURST_TIMING_UNIT_UPDATE_REGISTERS(p_config->timer_d_update));
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_BURST_TIMING_UNIT_UPDATE_REGISTERS(p_config->timer_e_update));
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_BURST_TIMING_UNIT_UPDATE_REGISTERS(p_config->timer_f_update));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Select the  of the DMA burst source */
  LL_HRTIM_SetDMABurstSource(p_hrtim, p_config->timer);

  /* Disable all timer DMA request(s) */
  LL_HRTIM_TIM_DisableDMAReq(p_hrtim, p_config->timer, (LL_HRTIM_MDIER_ALL_DMA | LL_HRTIM_TIMDIER_ALL_DMA));

  /* Enable timer DMA request(s) */
  LL_HRTIM_TIM_EnableDMAReq(p_hrtim, p_config->timer, p_config->requests);

  /* Configure the DMA burst update registers for each timer (master, timer A..F) */
  LL_HRTIM_TIM_ConfigBurstDMA(p_hrtim, LL_HRTIM_MASTER, p_config->master_update);
  LL_HRTIM_TIM_ConfigBurstDMA(p_hrtim, LL_HRTIM_TIMA, p_config->timer_a_update);
  LL_HRTIM_TIM_ConfigBurstDMA(p_hrtim, LL_HRTIM_TIMB, p_config->timer_b_update);
  LL_HRTIM_TIM_ConfigBurstDMA(p_hrtim, LL_HRTIM_TIMC, p_config->timer_c_update);
  LL_HRTIM_TIM_ConfigBurstDMA(p_hrtim, LL_HRTIM_TIMD, p_config->timer_d_update);
  LL_HRTIM_TIM_ConfigBurstDMA(p_hrtim, LL_HRTIM_TIME, p_config->timer_e_update);
  LL_HRTIM_TIM_ConfigBurstDMA(p_hrtim, LL_HRTIM_TIMF, p_config->timer_f_update);

  return HAL_OK;
}


/**
  * @brief  Start the DMA burst operation.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  dma_source DMA channel to be used for the burst DMA transfers.
  * @param  p_data Address of the buffer containing the data to be transferred
  *                by DMA into the HRTIM registers.
  * @param  size_byte Size (in bytes) of the data buffer.
  * @note   The DMA burst feature is only available for one DMA channel, but any
  *         of the 7 channels can be selected for DMA burst transfers.
  * @note   After calling this function, the DMA burst operation starts as soon as
  *         the timer selected as DMA burst source generates a DMA request.
  * @note   Each timer can have its own update strategy versus DMA burst
  *         operation (see @ref HAL_HRTIM_TIM_SetUpdateGating).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_StartDMABurst(hal_hrtim_handle_t *hhrtim,
                                     hal_hrtim_dma_source_t dma_source,
                                     const uint8_t *p_data,
                                     uint32_t size_byte)
{
  /*#warning "HAL_HRTIM_StartDMABurst: hal_hrtim_dma_source_t source => timer"*/
  hal_status_t hal_status;
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_dma_config_t dma_config;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_DMA_SOURCE(dma_source));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((hhrtim->hdma[dma_source] == NULL) || (p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Configure DMA transfer */
  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  dma_config.src_addr = (uint32_t)p_data;
  dma_config.dest_addr = (uint32_t) &(p_hrtim->sCommonRegs.BDMADR);
  dma_config.size_byte = size_byte;

  /* Start burst DMA operation */
  hal_status = HRTIM_Start_DMA_Opt(hhrtim->hdma[dma_source],
                                   &dma_config,
                                   HAL_HRTIM_OPT_DMA_IT_DEFAULT);

  return hal_status;
}

/**
  *  @}
  */
#endif /* USE_HAL_HRTIM_DMA */

/** @addtogroup HRTIM_Exported_Functions_Group11
  *  @{
  */
/**
  * @brief  Configure the time base unit of a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_timer_config_t structure that
  *                  contains the time base unit configuration.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetConfig(hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer,
                                     const hal_hrtim_timer_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint8_t timer_index = HRTIM_GET_TIMER_INDEX(timer);

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_TIM_PRESCALER(p_config->prescaler));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_PERIOD(p_config->period));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_REPETITION(p_config->repetition));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_OPERATING_MODE(p_config->operating_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_RESET | HAL_HRTIM_TIM_STATE_IDLE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Prescaler must be initialized first */
  LL_HRTIM_TIM_SetPrescaler(p_hrtim, timer, (uint32_t)p_config->prescaler);

  LL_HRTIM_TIM_SetPeriod(p_hrtim, timer, p_config->period);
  LL_HRTIM_TIM_SetRepetition(p_hrtim, timer, p_config->repetition);
  LL_HRTIM_TIM_SetCounterMode(p_hrtim, timer, (uint32_t)p_config->operating_mode);

  /* Set the counting mode for the timing unit (the master timer only works in up-counting mode) */
  if (IS_HRTIM_TIMING_UNIT(timer))
  {
    ASSERT_DBG_PARAM(IS_HRTIM_TIM_COUNTING_MODE(p_config->counting_mode));
    LL_HRTIM_TIM_SetCountingMode(p_hrtim, timer, (uint32_t)p_config->counting_mode);
  }

  hhrtim->timer_states[timer_index] = HAL_HRTIM_TIM_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Get the time base configuration of a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_timer_config_t structure that
  *                  contains the time base unit configuration configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer,
                                     hal_hrtim_timer_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));
  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get timer's time base configuration */
  p_config->prescaler = (hal_hrtim_timer_prescaler_t)LL_HRTIM_TIM_GetPrescaler(p_hrtim, timer);
  p_config->period = (uint16_t)LL_HRTIM_TIM_GetPeriod(p_hrtim, timer);
  p_config->repetition = (uint16_t)LL_HRTIM_TIM_GetRepetition(p_hrtim, timer);
  p_config->operating_mode = (hal_hrtim_timer_operating_mode_t)LL_HRTIM_TIM_GetCounterMode(p_hrtim, timer);

  if (IS_HRTIM_TIMING_UNIT(timer))
  {
    p_config->counting_mode = (hal_hrtim_timer_counting_mode_t)LL_HRTIM_TIM_GetCountingMode(p_hrtim, timer);
  }

  return HAL_OK;
}

/**
  * @brief  Set the timer's clock prescaler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  prescaler Timer clock prescaler value based on @ref hal_hrtim_timer_prescaler_t.
  * @warning Different prescaler values for the master and timers A..F are allowed
  *          only if the counter and output behavior do not depend on other timer signals or information.
  * @warning It is mandatory to configure identical prescaler values when
  *          one of the following event is propagated across multiple timers:
  *           - output set/reset event,
  *           - counter reset event,
  *           - update event,
  *           - external event filter,
  *           - capture triggers.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_timer_prescaler_t prescaler)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_PRESCALER(prescaler));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the timer clock prescaler */
  LL_HRTIM_TIM_SetPrescaler(p_hrtim, timer, (uint32_t)prescaler);

  return HAL_OK;
}

/**
  * @brief  Return the timer's clock prescaler value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Timer clock prescaler value.
  */
hal_hrtim_timer_prescaler_t HAL_HRTIM_TIM_GetPrescaler(const hal_hrtim_handle_t *hhrtim,
                                                       uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_timer_prescaler_t prescaler;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get timer clock prescaler configuration */
  prescaler = (hal_hrtim_timer_prescaler_t)LL_HRTIM_TIM_GetPrescaler(p_hrtim, timer);

  return prescaler;
}

/**
  * @brief  Set the timer's period.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  period Period value.
  *                This parameter must be a number between 0x3 and 0xFFFD.
  * @note   Period value must be above or equal to 3 periods of the fHRTIM clock.
  * @warning The period must be greater than or equal to 6 periods of the fHRTIM
  *          clock when the HALF mode is enabled (see @ref HAL_HRTIM_TIM_SetInterleavedMode).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetPeriod(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer,
                                     uint16_t period)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_PERIOD(period));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the timer's counter period */
  LL_HRTIM_TIM_SetPeriod(p_hrtim, timer, period);

  return HAL_OK;
}

/**
  * @brief  Return the timer's period.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Period value.
  */
uint16_t HAL_HRTIM_TIM_GetPeriod(const hal_hrtim_handle_t *hhrtim,
                                 uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  uint16_t period;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the timer's counter period configuration */
  period = (uint16_t)LL_HRTIM_TIM_GetPeriod(p_hrtim, timer);

  return period;
}

/**
  * @brief  Set the timer's repetition counter.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  repetition Repetition counter value.
  *                    This parameter must be a number between 0x0 and 0xFF.
  * @note   The repetition counter is decreased any time the counter is
  *         cleared, either due to a reset event or due to a counter roll-over.
  * @note   The roll-over event generation mode can be configured when the counter
  *         operates in up-down mode (see @ref HAL_HRTIM_TIM_SetRollOverMode).
  * @note   The repetition counter can't be read.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetRepetition(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         uint16_t repetition)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_REPETITION(repetition));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the timer's repetition counter value */
  LL_HRTIM_TIM_SetRepetition(p_hrtim, timer, repetition);

  return HAL_OK;
}

/**
  * @brief  Return the timer's repetition counter value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Repetition counter value.
  */
uint16_t HAL_HRTIM_TIM_GetRepetition(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  uint16_t repetition;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the timer's repetition counter configuration */
  repetition = (uint16_t)LL_HRTIM_TIM_GetRepetition(p_hrtim, timer);

  return repetition;
}

/**
  * @brief  Set the timer's counter operating mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  operating_mode Counter operating mode based on @ref hal_hrtim_timer_operating_mode_t.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetOperatingMode(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_timer_operating_mode_t operating_mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_OPERATING_MODE(operating_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the timer's operating mode */
  LL_HRTIM_TIM_SetCounterMode(p_hrtim, timer, (uint32_t)operating_mode);

  return HAL_OK;
}

/**
  * @brief  Return the timer's counter operating mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Counter operating mode.
  */
hal_hrtim_timer_operating_mode_t HAL_HRTIM_TIM_GetOperatingMode(const hal_hrtim_handle_t *hhrtim,
                                                                uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_timer_operating_mode_t operating_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the timer'operating mode configuration */
  operating_mode = (hal_hrtim_timer_operating_mode_t)LL_HRTIM_TIM_GetCounterMode(p_hrtim, timer);

  return operating_mode;
}

/**
  * @brief  Set the timer's counter mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counting_mode counting mode based on @ref hal_hrtim_timer_counting_mode_t.
  * @note   The master timer only works in up-counting mode.
  * @warning When the counter operates in up-down mode, the period can't be modified
  *          on the fly unless the preload is enabled. In that case the period is
  *          updated on period event or on counter reset.
  * @warning This function must not be called if the timer is started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetCountingMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_timer_counting_mode_t counting_mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIM_COUNTING_MODE(counting_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the timer's counter Up-Down mode */
  LL_HRTIM_TIM_SetCountingMode(p_hrtim, timer, (uint32_t)counting_mode);

  return HAL_OK;
}

/**
  * @brief  Return the timer's counter mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Counting mode.
  */
hal_hrtim_timer_counting_mode_t HAL_HRTIM_TIM_GetCountingMode(const hal_hrtim_handle_t *hhrtim,
                                                              uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_timer_counting_mode_t counting_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the timer's counter Up-Down mode configuration */
  counting_mode = (hal_hrtim_timer_counting_mode_t)LL_HRTIM_TIM_GetCountingMode(p_hrtim, timer);

  return counting_mode;
}

/**
  * @brief  Set the timer's counter value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  counter_value Counter value.
  * @warning This function must not be called if the timer is started.
  * @warning The timer behavior is not guaranteed if the counter value is above
  *          the period value.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetCounter(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer,
                                      uint16_t counter_value)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the timer's counter value */
  LL_HRTIM_TIM_SetCounter(p_hrtim, timer, counter_value);

  return HAL_OK;
}

/**
  * @brief  Return the timer's counter value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Counter value.
  */
uint16_t HAL_HRTIM_TIM_GetCounter(const hal_hrtim_handle_t *hhrtim,
                                  uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  uint16_t counter_value;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the timer's counter value */
  counter_value = (uint16_t)LL_HRTIM_TIM_GetCounter(p_hrtim, timer);

  return counter_value;
}

/**
  * @brief  Set the timer's roll-over mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  destination Destination feature based on @ref hal_hrtim_roll_over_destination_t.
  * @param  mode Roll-over event generation mode based on @ref hal_hrtim_roll_over_mode_t.
  * @note   The roll-over event generation mode can be programmed individually
  *         depending on the functionality it is destined to.
  * @note   The counter roll-over event is defined differently in-up-down
  *         counting mode to support various operating condition.
  *         It can be either generated:
  *         when the counter is equal to 0 (valley mode),
  *         when the counter reaches the period value (crest mode),
  *         when both conditions are met (either 0 or period value).
  * @warning This function must not be called if the timer is started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetRollOverMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_roll_over_destination_t destination,
                                           hal_hrtim_roll_over_mode_t mode)
{
  const HRTIM_TypeDef *p_hrtim;
  static  hrtim_set_rollover_mode_func_t hrtim_set_rollover_mode_funcs[5U] =
  {
    LL_HRTIM_TIM_SetRollOverMode,
    LL_HRTIM_TIM_SetOutputRollOverMode,
    LL_HRTIM_TIM_SetADCRollOverMode,
    LL_HRTIM_TIM_SetBMRollOverMode,
    LL_HRTIM_TIM_SetFaultEventRollOverMode
  };

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_ROLL_OVER_DESTINATION(destination));
  ASSERT_DBG_PARAM(IS_HRTIM_ROLL_OVER_MODE(mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the roll-over mode */
  hrtim_set_rollover_mode_funcs[(uint32_t)destination](p_hrtim, timer, (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Return the roll-over event generation mode for a given feature.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  destination Destination feature
  * @return Roll-over event generation mode.
  */
hal_hrtim_roll_over_mode_t HAL_HRTIM_TIM_GetRollOverMode(const hal_hrtim_handle_t *hhrtim,
                                                         uint32_t timer,
                                                         hal_hrtim_roll_over_destination_t destination)
{
  const HRTIM_TypeDef *p_hrtim;
  static hrtim_get_rollover_mode_func_t hrtim_get_rollover_mode_funcs[5U] =
  {
    LL_HRTIM_TIM_GetRollOverMode,
    LL_HRTIM_TIM_GetOutputRollOverMode,
    LL_HRTIM_TIM_GetADCRollOverMode,
    LL_HRTIM_TIM_GetBMRollOverMode,
    LL_HRTIM_TIM_GetFaultEventRollOverMode
  };
  uint32_t roll_over_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_ROLL_OVER_DESTINATION(destination));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the roll-over mode configuration */
  roll_over_mode = hrtim_get_rollover_mode_funcs[(uint32_t)destination](p_hrtim, timer);

  return (hal_hrtim_roll_over_mode_t)roll_over_mode;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group12
  *  @{
  */
/**
  * @brief  Enable the preload mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   When the preload mode is enabled, accessed registers are shadow registers.
  *         Their content is transferred into the active register after an update request,
  *         either software or synchronized with an event.
  * @warning The preload mode must be enabled when the timer's outputs are
  *          swapped (see @ref HAL_HRTIM_TIM_EnableSwapMode).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnablePreload(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable the registers preload */
  LL_HRTIM_TIM_EnablePreload(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Disable the preload mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   When the preload mode is disabled, any write directly updates the
  *         active registers.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisablePreload(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable the registers preload */
  LL_HRTIM_TIM_DisablePreload(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Check if the preload mode is enabled for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @retval Preload mode enable status.
  */
hal_hrtim_preload_status_t HAL_HRTIM_TIM_IsEnabledPreload(const hal_hrtim_handle_t *hhrtim,
                                                          uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_preload_status_t preload_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  preload_status = (hal_hrtim_preload_status_t)LL_HRTIM_TIM_IsEnabledPreload(p_hrtim, timer);

  return preload_status;
}

/**
  * @brief  Set the update event source(s) for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  update_source Update event source(s)
  *         \n
  *         For the master timer this parameter can be one of the following values:
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_NONE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_REPETITION
  *         \n
  *         For timer A..F this parameter can be:
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_NONE
  *         \n
  *         or a combination of the following values:
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_REPETITION
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_RESET
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_MASTER_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMA_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMB_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMC_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMD_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIME_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMF_UPDATE
  * @note   For the master timer, update event can be generated when the master
  *         timer repetition period is completed.
  * @note   For timers A..F, update event can be generated:
  *         - when the counter rolls over and the repetition counter is equal to 0,
  *         - when the counter is reset or rolls over in continuous mode,
  *         - with any other timer or master update.
  *         Multiple update event sources can be simultaneously selected.
  * @note   Update event can also be generated by software at anytime
  *         (see @ref HAL_HRTIM_Update).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetUpdateSource(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           uint32_t update_source)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_UPDATE_SOURCE(timer, update_source));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the update event source(s) */
  LL_HRTIM_TIM_SetUpdateTrig(p_hrtim, timer, update_source);

  return HAL_OK;
}

/**
  * @brief  Return the update event source(s) for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return uint32_t Update event source(s)
  *         \n
  *         For the master timer it can be one of the following values:
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_NONE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_REPETITION
  *         \n
  *         For timer A..F it can be:
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_NONE
  *         \n
  *         or a combination of the following values:
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_REPETITION
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_RESET
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_MASTER_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMA_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMB_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMC_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMD_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIME_UPDATE
  *         @arg @ref HAL_HRTIM_UPDATE_SOURCE_TIMF_UPDATE
  */
uint32_t HAL_HRTIM_TIM_GetUpdateSource(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t update_source;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the roll-over mode */
  update_source = LL_HRTIM_TIM_GetUpdateTrig(p_hrtim, timer);

  return update_source;
}

/**
  * @brief  Set the registers update gating option.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  update_gating  update gating option based on @ref hal_hrtim_update_gating_t.
  * @note   There are several options to trigger the transfer from shadow to
  *         active registers when preload is enabled (@ref HAL_HRTIM_TIM_EnablePreload).
  *         Thus it is possible to specify the register update strategy relatively to a
  *         DMA burst transaction (see @ref HAL_HRTIM_StartDMABurst) or when a
  *         pulse is detected on one of the update enable inputs (hrtim_upd_en).
  * @note   By default the registers update is triggered by the update event
  *         (see @ref HAL_HRTIM_TIM_SetUpdateSource).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetUpdateGating(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_update_gating_t update_gating)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_UPDATE_GATING(timer, update_gating));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* UPDGAT bitfield must be reset before programming a new value */
  LL_HRTIM_TIM_SetUpdateGating(p_hrtim, timer, (uint32_t)HAL_HRTIM_UPDATE_DMABURST_INDEPENDENT);

  /* Set the update gating configuration */
  LL_HRTIM_TIM_SetUpdateGating(p_hrtim, timer, (uint32_t)update_gating);

  return HAL_OK;
}

/**
  * @brief  Return the registers update gating option.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Update gating option.
  */
hal_hrtim_update_gating_t HAL_HRTIM_TIM_GetUpdateGating(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_update_gating_t update_gating;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the roll-over mode */
  update_gating = (hal_hrtim_update_gating_t)LL_HRTIM_TIM_GetUpdateGating(p_hrtim, timer);

  return update_gating;
}

/**
  * @brief  Enable update event generation for one or more timers.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Multiple timers can be updated simultaneously, even if unsynchronized.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_EnableUpdate(const hal_hrtim_handle_t *hhrtim,
                                    uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers,
                           (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable update event generation */
  LL_HRTIM_EnableUpdate(p_hrtim, timers);

  return HAL_OK;
}

/**
  * @brief  Disable update event generation for one or more timers.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Allow to temporarily disable the transfer from preload to active registers,
  *         whatever the selected update event. This allows to modify several registers
  *         in multiple timers. The regular update event takes place once the update
  *         event generation is re-enabled (see @ref HAL_HRTIM_EnableUpdate).
  * @note   The update of multiple timers (not necessarily synchronized) can be disabled
  *         simultaneously.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_DisableUpdate(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers,
                           (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable update event generation */
  LL_HRTIM_DisableUpdate(p_hrtim, timers);

  return HAL_OK;
}

/**
  * @brief  Check if the update event generation is enabled for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Update event generation enable status.
  */
hal_hrtim_update_status_t HAL_HRTIM_IsEnabledUpdate(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_update_status_t update_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  update_status = (hal_hrtim_update_status_t)LL_HRTIM_IsEnabledUpdate(p_hrtim, timer);

  return update_status;
}

/**
  * @brief  Force an immediate update of the registers for one or more timers.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   It is possible to force an update for several timers simultaneously.
  * @note   When re-synchronized update is enabled for timing unit (TimerA..F)
  *         the registers are updated on the next reset/roll-over event
  *         (see @ref HAL_HRTIM_TIM_EnableUpdateResync).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_Update(const hal_hrtim_handle_t *hhrtim,
                              uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers,
                           (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Force update event generation */
  LL_HRTIM_ForceUpdate(p_hrtim, timers);

  return HAL_OK;
}

/**
  * @brief  Enable the re-synchronized update mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   When re-synchronized update is enabled the update coming from adjacent
  *         timers or from a software update is re-synchronized with the timer's
  *         reset/roll-over event.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableUpdateResync(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Generate a software update prior to set the RSYNCU bit, so that the initial
     timer configuration is taken into account before actually starting the
     counters. */
  LL_HRTIM_ForceUpdate(p_hrtim, timer);

  /* Enable re-synchronized update */
  LL_HRTIM_TIM_EnableResyncUpdate(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Disable the re-synchronized update mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   When re-synchronized update is disabled for timing unit the update
  *         coming from adjacent timers or from a software update is taken into
  *         account immediately.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableUpdateResync(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable re-synchronized update */
  LL_HRTIM_TIM_DisableResyncUpdate(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Check if the re-synchronized update mode for a timer is enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Re-synchronized update enable status.
  */
hal_hrtim_update_resync_status_t HAL_HRTIM_TIM_IsEnabledUpdateResync(const hal_hrtim_handle_t *hhrtim,
                                                                     uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_update_resync_status_t update_resync_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  update_resync_status = (hal_hrtim_update_resync_status_t)LL_HRTIM_TIM_IsEnabledResyncUpdate(p_hrtim, timer);

  return update_resync_status;
}


/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group13
  *  @{
  */
/**
  * @brief  Start one or more timers in polling mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Several timers can be started simultaneously.
  * @note   The way the counting is started depends on the timer operating mode
  *         (@ref HAL_HRTIM_TIM_SetConfig):
  *         - when the timer operates in continuous mode the counter is started
  *           immediately.
  *         - when the timer operates in single-shot mode the counter is started
  *           by a reset event.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Start(hal_hrtim_handle_t *hhrtim,
                                 uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t timers_to_start = timers;
  uint32_t timer;
  uint8_t timer_index;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers, HAL_HRTIM_TIM_STATE_IDLE);
#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Start timers counter */
  LL_HRTIM_TIM_CounterEnable(p_hrtim, timers);

  /* Update timers state */
  timers_to_start = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_start);

  while (timers_to_start != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    hhrtim->timer_states[timer_index] = HAL_HRTIM_TIM_STATE_ACTIVE;

    timers_to_start &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_start);
  }

  return HAL_OK;
}

/**
  * @brief  Stop one or more timers in polling mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Several timers can be stopped simultaneously.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Stop(hal_hrtim_handle_t *hhrtim,
                                uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t timers_to_stop = timers;
  uint32_t timer;
  uint8_t timer_index;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers, HAL_HRTIM_TIM_STATE_ACTIVE);
#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Stop timers counter */
  LL_HRTIM_TIM_CounterDisable(p_hrtim, timers);

  /* Update timers state */
  timers_to_stop = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_stop);

  while (timers_to_stop != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    hhrtim->timer_states[timer_index] = HAL_HRTIM_TIM_STATE_IDLE;

    timers_to_stop &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_stop);
  }

  return HAL_OK;
}

/**
  * @brief  Start one or more timers in interrupt mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Several timers can be started simultaneously.
  * @note   Timers' interrupts to enable must be specified by calling @ref HAL_HRTIM_SetConfigInterrupts.
  * @note   The way the counting is started depends on the timer operating mode
  *         (@ref HAL_HRTIM_TIM_SetConfig):
  *         - when the timer operates in continuous mode the counter is started
  *           immediately.
  *         - when the timer operates in single-shot mode the counter is started
  *           by a reset event.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Start_IT(hal_hrtim_handle_t *hhrtim,
                                    uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t timers_to_start = timers;
  uint32_t timer;
  uint8_t timer_index;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers, HAL_HRTIM_TIM_STATE_IDLE);
#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable timers interrupts */
  timers_to_start = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_start);

  while (timers_to_start != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    /* Disable all timer interrupts sources */
    LL_HRTIM_TIM_DisableIT(p_hrtim, timer, (LL_HRTIM_MDIER_ALL_IT | LL_HRTIM_TIMDIER_ALL_IT));

    /* Enable requested timer interrupt sources */
    if (hhrtim->interrupts[timer_index] != HAL_HRTIM_OPT_IT_NONE)
    {
      LL_HRTIM_TIM_EnableIT(p_hrtim, timer, hhrtim->interrupts[timer_index]);
    }

    timers_to_start &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_start);
  }

  /* Start timers counter */
  LL_HRTIM_TIM_CounterEnable(p_hrtim, timers);

  /* Update timers state */
  timers_to_start = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_start);

  while (timers_to_start != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    hhrtim->timer_states[timer_index] = HAL_HRTIM_TIM_STATE_ACTIVE;

    timers_to_start &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_start);
  }

  return HAL_OK;
}

/**
  * @brief  Stop one or more timers in interrupt mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Several timers can be stopped simultaneously.
  * @note   Timers' interrupts are disabled from within this function.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Stop_IT(hal_hrtim_handle_t *hhrtim,
                                   uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t timers_to_stop = timers;
  uint32_t timer;
  uint8_t timer_index;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers, HAL_HRTIM_TIM_STATE_ACTIVE);
#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Stop timers counter */
  LL_HRTIM_TIM_CounterDisable(p_hrtim, timers);

  /* Disable timer interrupts sources and update timers state */
  timers_to_stop = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_stop);

  while (timers_to_stop != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    /* Disable all timer interrupts sources */
    LL_HRTIM_TIM_DisableIT(p_hrtim, timer, (LL_HRTIM_MDIER_ALL_IT | LL_HRTIM_TIMDIER_ALL_IT));

    hhrtim->timer_states[timer_index] = HAL_HRTIM_TIM_STATE_IDLE;

    timers_to_stop &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_stop);
  }

  return HAL_OK;
}

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/**
  * @brief  Start one or more timers in DMA mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Several timers can be started simultaneously.
  * @note   Timers' DMA requests to enable must be specified by calling @ref HAL_HRTIM_SetConfigDMA.
  * @note   As far as the DMA transfer is concerned, the following
  *         interrupts are implicitly enabled: half transfer, transfer completed
  *         and transfer error.
  * @note   The way the counting is started depends on the timer operating mode
  *         (@ref HAL_HRTIM_TIM_SetConfig):
  *         - when the timer operates in continuous mode the counter is started
  *           immediately.
  *         - when the timer operates in single-shot mode the counter is started
  *           by a reset event.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Start_DMA(hal_hrtim_handle_t *hhrtim,
                                     uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t timers_to_start = timers;
  uint32_t timer;
  uint8_t timer_index;
  hal_hrtim_dma_config_t *p_dma_config;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers, HAL_HRTIM_TIM_STATE_IDLE);
#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable timer DMA request(s) and start the DMA transfer */
  timers_to_start = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_start);

  while (timers_to_start != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    /* Disable all timer DMA requests */
    LL_HRTIM_TIM_DisableDMAReq(p_hrtim, timer, (LL_HRTIM_MDIER_ALL_DMA | LL_HRTIM_TIMDIER_ALL_DMA));

    p_dma_config = hhrtim->p_dma_config[timer_index];

    if (p_dma_config != NULL)
    {
      /* Enable timer DMA request(s) */
      LL_HRTIM_TIM_EnableDMAReq(p_hrtim, timer, p_dma_config->requests);

      /* Start the DMA transfer (if needed) */
      if (p_dma_config->requests !=  HAL_HRTIM_OPT_DMA_NONE)
      {
        (void)HRTIM_Start_DMA_Opt(hhrtim->hdma[timer_index],
                                  p_dma_config,
                                  HAL_HRTIM_OPT_DMA_IT_DEFAULT);
      }
    }

    timers_to_start &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_start);
  }

  /* Start timers counter */
  LL_HRTIM_TIM_CounterEnable(p_hrtim, timers);

  /* Update timers state */
  timers_to_start = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_start);

  while (timers_to_start != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    hhrtim->timer_states[timer_index] = HAL_HRTIM_TIM_STATE_ACTIVE;

    timers_to_start &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_start);
  }

  return HAL_OK;
}

/**
  * @brief  Stop one or more timers in DMA mode.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Several timers can be stopped simultaneously.
  * @note   All ongoing DMA transfers are aborted from within this
  *         function.
  * @note   Timers' DMA requests are disabled from within this function.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Stop_DMA(hal_hrtim_handle_t *hhrtim,
                                    uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t timers_to_stop = timers;
  uint32_t timer;
  uint8_t timer_index;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers, HAL_HRTIM_TIM_STATE_ACTIVE);
#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Abort ongoing DMA transfers and disable DMA requests */
  timers_to_stop = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_stop);

  while (timers_to_stop != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    /* The DMA controller must be disabled before disabling the DMA requests */
    (void)HRTIM_Abort_DMA(hhrtim->hdma[timer_index], hhrtim->timer_states[timer_index]);

    /* Disable all timer DMA requests */
    LL_HRTIM_TIM_DisableDMAReq(p_hrtim, timer, (LL_HRTIM_MDIER_ALL_DMA | LL_HRTIM_TIMDIER_ALL_DMA));

    timers_to_stop &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_stop);
  }

  /* Stop timers counter */
  LL_HRTIM_TIM_CounterDisable(p_hrtim, timers);

  /* Update timers state */
  timers_to_stop = timers;
  timer = 1UL << STM32_POSITION_VAL(timers_to_stop);

  while (timers_to_stop != 0U)
  {
    timer_index = HRTIM_GET_TIMER_INDEX(timer);

    hhrtim->timer_states[timer_index] = HAL_HRTIM_TIM_STATE_IDLE;

    timers_to_stop &= (~timer);
    timer = 1UL << STM32_POSITION_VAL(timers_to_stop);
  }

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_DMA */

/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group14
  *  @{
  */
/**
  * @brief  Set the counter reset source(s) for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  reset_sources Counter reset source(s)
  * @note   Multiple events can be selected simultaneously to handle various reset sources.
  * @note   Reset requests are considered only after the related timers have started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetResetSource(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          uint32_t reset_sources)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Select the counter reset trigger(s) */
  LL_HRTIM_TIM_SetResetTrig(p_hrtim, timer, reset_sources);

  return HAL_OK;
}

/**
  * @brief  Return the counter reset source(s) for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Counter reset source(s).
  */
uint32_t HAL_HRTIM_TIM_GetResetSource(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t reset_sources;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the timer counter reset configuration */
  reset_sources = LL_HRTIM_TIM_GetResetTrig(p_hrtim, timer);

  return reset_sources;
}

/**
  * @brief  Force a reset of the counter of one or more timers.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   It is possible to force counter reset for several timers simultaneously.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Reset(const hal_hrtim_handle_t *hhrtim,
                                 uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMERS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers,
                           HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE);
#endif /* USE_ASSERT_DBG_STATE */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Force a counter reset */
  LL_HRTIM_CounterReset(p_hrtim, timers);

  return HAL_OK;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group15
  *  @{
  */
/**
  * @brief  Configure an HRTIM output.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @param  p_config pointer to a @ref hal_hrtim_output_config_t structure that
  *                  contains the HRTIM output configuration.
  * @warning This function must be called before starting the HRTIM output.
  * @warning This function must not be called as long as the HRTIM output is
  *          in the FAULT state (see @ref HAL_HRTIM_OUT_GetStatus).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_OUT_SetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t output,
                                     const hal_hrtim_output_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT_SET(p_config->set));
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT_RESET(p_config->reset));
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT_IDLE_LEVEL(p_config->idle_level));
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT_FAULT_LEVEL(p_config->fault_level));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the output */
  LL_HRTIM_OUT_SetOutputSetSrc(p_hrtim, output, p_config->set);
  LL_HRTIM_OUT_SetOutputResetSrc(p_hrtim, output, p_config->reset);
  LL_HRTIM_OUT_SetPolarity(p_hrtim, output, (uint32_t)p_config->polarity);
  LL_HRTIM_OUT_SetIdleLevel(p_hrtim, output, (uint32_t)p_config->idle_level);
  LL_HRTIM_OUT_SetFaultState(p_hrtim, output, (uint32_t)p_config->fault_level);

  return HAL_OK;
}

/**
  * @brief  Get the HRTIM output configuration.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @param  p_config pointer to a @ref hal_hrtim_output_config_t structure that
  *                  contains the HRTIM output configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_GetConfig(const hal_hrtim_handle_t *hhrtim,
                                     uint32_t output,
                                     hal_hrtim_output_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the output configuration */
  p_config->set  = LL_HRTIM_OUT_GetOutputSetSrc(p_hrtim, output);
  p_config->reset = LL_HRTIM_OUT_GetOutputResetSrc(p_hrtim, output);;
  p_config->polarity = (hal_hrtim_output_polarity_t)LL_HRTIM_OUT_GetPolarity(p_hrtim, output);
  p_config->idle_level = (hal_hrtim_output_idle_level_t)LL_HRTIM_OUT_GetIdleLevel(p_hrtim, output);
  p_config->fault_level = (hal_hrtim_output_fault_level_t)LL_HRTIM_OUT_GetFaultState(p_hrtim, output);

  return HAL_OK;
}

/**
  * @brief  Enable one or more  HRTIM outputs.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  outputs HRTIM output(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @note   Multiple HRTIM outputs can be enabled simultaneously.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_Enable(const hal_hrtim_handle_t *hhrtim,
                                  uint32_t outputs)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_OUTPUTS(outputs));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable the HRTIM output(s) */
  LL_HRTIM_EnableOutput(p_hrtim, outputs);

  return HAL_OK;

}

/**
  * @brief  Disable one or more  HRTIM outputs.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  outputs HRTIM output(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @note   Multiple HRTIM outputs can be disabled simultaneously.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_Disable(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t outputs)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_OUTPUTS(outputs));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable the HRTIM output(s) */
  LL_HRTIM_DisableOutput(p_hrtim, outputs);

  return HAL_OK;
}

/**
  * @brief  Force a HRTIM output to its ACTIVE level.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_Set(const hal_hrtim_handle_t *hhrtim,
                               uint32_t output)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Force the output to its ACTIVE level */
  LL_HRTIM_OUT_ForceLevel(p_hrtim, output, LL_HRTIM_OUT_LEVEL_ACTIVE);

  return HAL_OK;
}

/**
  * @brief  Force a HRTIM output to its INACTIVE level.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_Reset(const hal_hrtim_handle_t *hhrtim,
                                 uint32_t output)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Force the output to its INACTIVE level */
  LL_HRTIM_OUT_ForceLevel(p_hrtim, output, LL_HRTIM_OUT_LEVEL_INACTIVE);

  return HAL_OK;
}

/**
  * @brief  Return the raw level of an HRTIM output.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @note   This function allows to check that an output is INACTIVE
  *         prior to exit from delayed idle mode
  *         (see @ref HAL_HRTIM_TIM_SetConfigDelayedProtection).
  * @return HRTIM output raw level.
  */
hal_hrtim_output_level_t HAL_HRTIM_OUT_GetRawLevel(const hal_hrtim_handle_t *hhrtim,
                                                   uint32_t output)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_output_level_t output_level;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the raw copy of the output (before the output stage) */
  output_level = (hal_hrtim_output_level_t)LL_HRTIM_OUT_GetLevel(p_hrtim, output);

  return output_level;
}

/**
  * @brief  Enable swap mode for one or more timers.
  * @param  hhrtim Pointer to the HRTIM instansce handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   The swap mode can be enabled for several timers simultaneously.
  * @note   When the swap mode is enabled, the output 1 signal is connected to the
  *         output 2 pin and the output 2 signal is connected to output 1 pin.
  * @note   The swap mode is ignored when the push-pull mode is enabled
  *         (see @ref HAL_HRTIM_TIM_EnablePushPull).
  * @warning The swap mode is only affecting the preload register,
  *          and not the active registers. Therefore, it is mandatory to enable
  *          preload mode (see @ref HAL_HRTIM_TIM_EnablePreload).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableSwapMode(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMING_UNITS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers,
                           HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE);
#endif /* HAL_HRTIM_TIM_EnableSwapMode */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable output swap */
  LL_HRTIM_EnableSwapOutputs(p_hrtim, timers);

  return HAL_OK;
}

/**
  * @brief  Disable swap mode for one or more timers.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timers HRTIM timer(s).
  *         It can be a combination of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   The swap mode can be disabled for several timers simultaneously.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableSwapMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timers)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_COMBINED_TIMING_UNITS(timers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
#if defined(USE_ASSERT_DBG_STATE)
  hrtim_check_timers_state(hhrtim, timers,
                           HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE);
#endif /* HAL_HRTIM_TIM_EnableSwapMode */

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable output swap */
  LL_HRTIM_DisableSwapOutputs(p_hrtim, timers);

  return HAL_OK;
}

/**
  * @brief  Check if the swap mode is enabled for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Swap mode enable status.
  */
hal_hrtim_swap_mode_status_t HAL_HRTIM_TIM_IsEnabledSwapMode(const hal_hrtim_handle_t *hhrtim,
                                                             uint32_t timer)
{
  const HRTIM_TypeDef *p_hrtim;
  hal_hrtim_swap_mode_status_t swap_mode_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  swap_mode_status = (hal_hrtim_swap_mode_status_t)LL_HRTIM_IsEnabledSwapOutputs(p_hrtim, timer);

  return swap_mode_status;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group16
  *  @{
  */
/**
  * @brief  Set the compare value of a compare unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer identifier
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  compare_unit  Compare unit based on @ref hal_hrtim_compare_unit_t.
  * @param  compare_value Compare value.
  * @note   The compare value must be above or equal to 3 periods of the fHRTIM
  *         clock. However, null value is allowed under certain conditions for
  *         compare units 1 and 3 to skip a PWM pulse.
  * @note   The compare event is generated when the timer's counter matches the
  *         compare value.
  * @warning A compare value greater than the period register value does not
  *          generate a compare match event.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetCompareValue(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_compare_unit_t compare_unit,
                                           uint16_t compare_value)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_UNIT(compare_unit));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_VALUE(compare_unit, compare_value));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set the compare value */
  LL_HRTIM_TIM_SetCompareValue(p_hrtim, timer, (uint32_t)compare_unit, compare_value);

  return HAL_OK;
}

/**
  * @brief  Get the compare value of a compare unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer identifier
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  compare_unit  Compare unit based on @ref hal_hrtim_compare_unit_t.
  * @return Compare value.
  */
uint16_t HAL_HRTIM_TIM_GetCompareValue(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer,
                                       hal_hrtim_compare_unit_t compare_unit)
{
  HRTIM_TypeDef *p_hrtim;
  uint16_t compare_value;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_UNIT(compare_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the compare value */
  compare_value = (uint16_t)LL_HRTIM_TIM_GetCompareValue(p_hrtim, timer, (uint32_t)compare_unit);

  return compare_value;
}

/**
  * @brief  Set the interleaved mode of a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer identifier
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param mode Selected interleaved mode based on @ref hal_hrtim_interleaved_mode_t.
  * @warning Triple and quad interleaved modes aren't supported by the master
  *          timer.
  * @warning When interleaved mode is enabled, the content of some compare
  *          registers are overridden by the hardware (see table below).
  *
  *            Compare unit |   Dual   |    Triple      |   Quad
  *           ------------- | -------- | -------------- | ----------------
  *            CMP1 value   | Period/2 |    Period/3    |    Period/4
  *            CMP2 value   |    NA    | 2 * (Period/3) |   Period/2
  *            CMP3 value   |    NA    |      NA        | 3 * (Period/4)
  *
  *          NA: Not Affected.
  * @warning Triple and quad interleaved modes must not be used simultaneously
  *          with other modes using CMP2:
  *          - Dual channel DAC trigger (see @ref HAL_HRTIM_TIM_EnableDualChannelDAC)
  *          - Triggered-half modes (see @ref HAL_HRTIM_TIM_SetTriggeredHalfMode).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetInterleavedMode(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_interleaved_mode_t mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_INTERLEAVED_MODE(mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));


  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the interleaved mode */
  LL_HRTIM_TIM_SetInterleavedMode(p_hrtim, timer, (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Get the interleaved mode of a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_MASTER Master timer identifier
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Interleaved mode.
  */
hal_hrtim_interleaved_mode_t HAL_HRTIM_TIM_GetInterleavedMode(const hal_hrtim_handle_t *hhrtim,
                                                              uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_interleaved_mode_t interleaved_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get the interleaved mode configuration */
  interleaved_mode = (hal_hrtim_interleaved_mode_t)LL_HRTIM_TIM_GetInterleavedMode(p_hrtim, timer);

  return interleaved_mode;
}

/**
  * @brief  Enable the "greater than" (GT) compare mode on compare unit 1 or compare unit 3.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  compare_unit  Compare unit.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_1 Compare unit 1
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_3 Compare unit 3
  * @note   When the greater than comparison is enabled, a new duty cycle value
  *         is applied as soon as possible within the PWM cycle, without having
  *         to wait the completion of the current PWM period
  * @warning Greater than compare mode must not be enabled if the interleaved
  *          mode is enabled (see @ref HAL_HRTIM_TIM_SetInterleavedMode).
  * @warning The preload mechanism is inactive for concerned compare unit when
  *          greater than comparison is enabled. Therefore, when a new compare value
  *          is set (see @ref HAL_HRTIM_TIM_SetCompareValue), it is directly written
  *          to the related active register.
  * @warning The greater than compare mode must only be used for the following
  *          configurations:
  *          - Fixed frequency configuration:
  *              . Output set event: period event.
  *              . Outptut reset event: "greater than" compare event.
  *          - Variable frequency configuration (counter can be reset before
  *            reaching the period):
  *              . Output set or reset event = counter reset event.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableGTCompare(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_compare_unit_t compare_unit)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_UNIT_GTCMP(compare_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable "greater than" comparison mode */
  switch (compare_unit)
  {
    case HAL_HRTIM_COMPARE_UNIT_1:
      LL_HRTIM_TIM_SetComp1Mode(p_hrtim, timer, LL_HRTIM_GTCMP1_GREATER);
      break;
    case HAL_HRTIM_COMPARE_UNIT_3:
      LL_HRTIM_TIM_SetComp3Mode(p_hrtim, timer, LL_HRTIM_GTCMP3_GREATER);
      break;
    default:
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the "greater than" (GT) compare mode on compare unit 1 or compare unit 3.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  compare_unit  Compare unit.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_1 Compare unit 1
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_3 Compare unit 3
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableGTCompare(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_compare_unit_t compare_unit)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_UNIT_GTCMP(compare_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable "greater than" comparison mode */
  switch (compare_unit)
  {
    case HAL_HRTIM_COMPARE_UNIT_1:
      LL_HRTIM_TIM_SetComp1Mode(p_hrtim, timer, LL_HRTIM_GTCMP1_EQUAL);
      break;
    case HAL_HRTIM_COMPARE_UNIT_3:
      LL_HRTIM_TIM_SetComp3Mode(p_hrtim, timer, LL_HRTIM_GTCMP3_EQUAL);
      break;
    default:
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Check if the "greater than" (GT) compare mode is enabled on compare unit 1 or compare unit 3.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  compare_unit  Compare unit.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_1 Compare unit 1
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_3 Compare unit 3
  * @return Greater than compare mode enable status.
  */
hal_hrtim_greater_than_compare_status_t HAL_HRTIM_TIM_IsEnabledGTCompare(const hal_hrtim_handle_t *hhrtim,
                                                                         uint32_t timer,
                                                                         hal_hrtim_compare_unit_t compare_unit)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_greater_than_compare_status_t greater_than_compare_status = HAL_HRTIM_GTCMP_DISABLED;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_UNIT_GTCMP(compare_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  switch (compare_unit)
  {
    case HAL_HRTIM_COMPARE_UNIT_1:
      greater_than_compare_status = (LL_HRTIM_TIM_GetComp1Mode(p_hrtim, timer) == LL_HRTIM_GTCMP1_EQUAL) ?
                                    HAL_HRTIM_GTCMP_DISABLED : HAL_HRTIM_GTCMP_ENABLED;
      break;
    case HAL_HRTIM_COMPARE_UNIT_3:
      greater_than_compare_status = (LL_HRTIM_TIM_GetComp3Mode(p_hrtim, timer) == LL_HRTIM_GTCMP3_EQUAL) ?
                                    HAL_HRTIM_GTCMP_DISABLED : HAL_HRTIM_GTCMP_ENABLED;
      break;
    default:
      break;
  }

  return greater_than_compare_status;
}

/**
  * @brief  Enable the triggered-half mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  mode triggered-half mode based on @ref hal_hrtim_trig_half_mode_t.
  * @note   When triggered-half mode is enabled, the switching period of the master
  *         converter is captured, divided by 2 and then stored in the compare 2
  *         register by hardware. The compare 2 event can then be used to trigger
  *         a second timing unit that manages the slave converter.
  * @note   In triggered-half with timeout mode, CMP2 register is set to period/2 value if
  *         no capture is triggered within the counting period.
  * @warning triggered-half mode isn't supported when the counter operates
  *          in up-down mode.
  * @warning This function must not be called when the timer is started.
  * @warning When the triggered-half mode is enabled, compare unit 2 is
  *          managed by the hardware. Therefore, triggered-half mode must no be
  *          enabled when:
  *          - Triple or quad interleaved mode is enabled (see @ref HAL_HRTIM_TIM_SetInterleavedMode).
  *          - Dual channel DAC is enabled (see @ref HAL_HRTIM_TIM_EnableDualChannelDAC).
  *          - Balanced idle mode is enabled for the timer output(s)
  *            (see @ref HAL_HRTIM_TIM_SetConfigDelayedProtection).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetTriggeredHalfMode(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer,
                                                hal_hrtim_trig_half_mode_t mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TRIGGERED_HALF_MODE(mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Set triggered-half mode */
  LL_HRTIM_TIM_SetTriggeredHalfMode(p_hrtim, timer, (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Check if the triggered-half mode is enabled for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Triggered-half mode.
  */
hal_hrtim_trig_half_mode_t HAL_HRTIM_TIM_GetTriggeredHalfMode(const hal_hrtim_handle_t *hhrtim,
                                                              uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_trig_half_mode_t trig_half_mode_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  trig_half_mode_status = (hal_hrtim_trig_half_mode_t)
                          LL_HRTIM_TIM_GetTriggeredHalfMode(p_hrtim, timer);

  return trig_half_mode_status;
}

/**
  * @brief  Set the auto-delayed mode on compare unit 2 or compare unit 4.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  compare_unit  Compare unit.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_2 Compare unit 2
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_4 Compare unit 4
  * @param  p_config pointer to a @ref hal_hrtim_auto_delayed_config_t structure that
  *                  contains the auto-delayed mode configuration.
  * @note   When auto-delayed mode is enabled, compare events are generated
  *         relatively to capture events, so that for instance an output change
  *         can happen with a programmed delay following a capture.
  * @note   Compare 2 value is recomputed and used for comparison with capture unit 1.
  *         Compare 4 value is recomputed and used for comparison with capture unit 2.
  * @note   As long as no capture is triggered, no compare event is generated
  *         when the counter value matches the compare value.
  * @note   A timeout can be specified to have a timeout function when no
  *         capture event occurs. In that case compare unit 1 or compare unit 3
  *         - as per selected auto-delayed mode - hold the timeout value.
  * @warning Auto-delayed mode isn't supported when the counter operates in up-down mode.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetAutoDelayedMode(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_compare_unit_t compare_unit,
                                              const hal_hrtim_auto_delayed_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t cmp;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_UNIT_DELCMP(compare_unit));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_AUTO_DELAYED_MODE(p_config->mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* compare unit id HAL to LL conversion */
  cmp = (compare_unit == HAL_HRTIM_COMPARE_UNIT_2) ? (uint32_t)LL_HRTIM_COMPARE_UNIT_2 \
        : (uint32_t)LL_HRTIM_COMPARE_UNIT_4;

  /* DELCMPx[1:0] bitfield must be reset when reprogrammed from one value
     to the other to re-initialize properly the auto-delayed mechanism. */
  if (p_config->mode != HAL_HRTIM_AUTODELAYED_DISABLE)
  {
    LL_HRTIM_TIM_SetCompareMode(p_hrtim, timer, cmp, LL_HRTIM_COMPAREMODE_REGULAR);
  }

  /* Configure the auto-delayed mode */
  LL_HRTIM_TIM_SetCompareMode(p_hrtim, timer, cmp, (uint32_t)p_config->mode);

  /* Configure the timeout (if needed) */
  switch (p_config->mode)
  {
    case LL_HRTIM_COMPAREMODE_DELAY_CMP1:
      LL_HRTIM_TIM_SetCompare1(p_hrtim, timer, p_config->timeout_cycles);
      break;
    case LL_HRTIM_COMPAREMODE_DELAY_CMP3:
      LL_HRTIM_TIM_SetCompare3(p_hrtim, timer, p_config->timeout_cycles);
      break;
    default:
      break;
  }

  return HAL_OK;
}

/**
  * @brief  Get the auto-delayed mode on compare unit 2 or compare unit 4.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  compare_unit  Compare unit.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_2 Compare unit 2
  *         @arg @ref HAL_HRTIM_COMPARE_UNIT_4 Compare unit 4
  * @param  p_config pointer to a @ref hal_hrtim_auto_delayed_config_t structure that
  *                  contains the auto-delayed mode configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetAutoDelayedMode(const hal_hrtim_handle_t *hhrtim,
                                              uint32_t timer,
                                              hal_hrtim_compare_unit_t compare_unit,
                                              hal_hrtim_auto_delayed_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t cmp;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_COMPARE_UNIT_DELCMP(compare_unit));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* compare unit id HAL to LL conversion */
  cmp = (compare_unit == HAL_HRTIM_COMPARE_UNIT_2) ? (uint32_t)LL_HRTIM_COMPARE_UNIT_2 \
        : (uint32_t)LL_HRTIM_COMPARE_UNIT_4;

  /* Get auto-delayed mode configuration*/
  p_config->mode = (hal_hrtim_auto_delayed_mode_t)
                   LL_HRTIM_TIM_GetCompareMode(p_hrtim, timer, cmp);

  /* Get the timeout configuration(if needed) */
  p_config->timeout_cycles = 0U;

  switch (p_config->mode)
  {
    case LL_HRTIM_COMPAREMODE_DELAY_CMP1:
      p_config->timeout_cycles = (uint16_t)LL_HRTIM_TIM_GetCompare1(p_hrtim, timer);
      break;
    case LL_HRTIM_COMPAREMODE_DELAY_CMP3:
      p_config->timeout_cycles = (uint16_t)LL_HRTIM_TIM_GetCompare3(p_hrtim, timer);
      break;
    default:
      break;
  }

  return HAL_OK;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group17
  *  @{
  */
/**
  * @brief  Set the capture trigger(s).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  capture_unit  Capture unit based on @ref hal_hrtim_capture_unit_t.
  * @param  triggers  Capture trigger(s).
  * @note   The capture of the timing unit counter can be triggered by up to 28
  *         events that can be selected simultaneously.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetCaptureTrigger(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_capture_unit_t capture_unit,
                                             uint64_t triggers)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_CAPTURE_UNIT(capture_unit));
  ASSERT_DBG_PARAM(IS_HRTIM_CAPTURE_TRIGGERS(triggers));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Select the capture trigger(s) */
  LL_HRTIM_TIM_SetCaptureTrig(p_hrtim, timer, (uint32_t)capture_unit, triggers);

  return HAL_OK;
}

/**
  * @brief  Return the capture trigger(s).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  capture_unit  Capture unit based on @ref hal_hrtim_capture_unit_t.
  * @return Capture trigger(s).
  */
uint64_t HAL_HRTIM_TIM_GetCaptureTrigger(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         hal_hrtim_capture_unit_t capture_unit)
{
  HRTIM_TypeDef *p_hrtim;
  uint64_t triggers;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_CAPTURE_UNIT(capture_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get capture trigger(s) configuration */
  triggers = LL_HRTIM_TIM_GetCaptureTrig(p_hrtim, timer, (uint32_t)capture_unit);

  return triggers;
}

/**
  * @brief  Force a capture.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  capture_unit  Capture unit based on @ref hal_hrtim_capture_unit_t.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_Capture(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t timer,
                                   hal_hrtim_capture_unit_t capture_unit)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_CAPTURE_UNIT(capture_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Trigger a capture */
  LL_HRTIM_TIM_SetCaptureTrig(p_hrtim, timer, (uint32_t)capture_unit, LL_HRTIM_CAPTURETRIG_SW);

  return HAL_OK;
}


/**
  * @brief  Get captured direction and captured value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  capture_unit  Capture unit based on @ref hal_hrtim_capture_unit_t.
  * @param  capture pointer to a @ref hal_hrtim_capture_t structure that
  *                  contains the capture related information.
  * @note   The direction status allows to discriminate the up-down phases when
  *         reading the captured value.
  * @note   In up/down mode, the captured value is referred to:
  *         - counting reset, when up-counting,
  *         - the PER event when down counting.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetCapture(const hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer,
                                      hal_hrtim_capture_unit_t capture_unit,
                                      hal_hrtim_capture_t *capture)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_CAPTURE_UNIT(capture_unit));
  ASSERT_DBG_PARAM((capture != NULL));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get captured value and counting direction */
  capture->value = (uint16_t)LL_HRTIM_TIM_GetCapturedValue(p_hrtim, timer, (uint32_t)capture_unit);
  capture->direction = (hal_hrtim_capture_direction_t)
                       LL_HRTIM_TIM_GetCapturedDirection(p_hrtim, timer, (uint32_t)capture_unit);

  return HAL_OK;
}

/**
  * @brief  Return the captured value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  capture_unit  Capture unit based on @ref hal_hrtim_capture_unit_t.
  * @note   In up/down mode, the captured value is referred to:
  *         - counting reset, when up-counting,
  *         - the PER event when down counting.
  * @return Captured value.
  */
uint16_t HAL_HRTIM_TIM_GetCapturedValue(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_capture_unit_t capture_unit)
{
  HRTIM_TypeDef *p_hrtim;
  uint16_t captured_value;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_CAPTURE_UNIT(capture_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get captured value */
  captured_value = (uint16_t)LL_HRTIM_TIM_GetCapturedValue(p_hrtim, timer, (uint32_t)capture_unit);
  return captured_value;
}

/**
  * @brief  Return the captured direction.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  capture_unit  Capture unit based on @ref hal_hrtim_capture_unit_t.
  * @note   The direction status allows to discriminate the up-down phases when
  *         reading the captured value.
  * @return Captured direction.
  */
hal_hrtim_capture_direction_t HAL_HRTIM_TIM_GetCapturedDirection(const hal_hrtim_handle_t *hhrtim,
                                                                 uint32_t timer,
                                                                 hal_hrtim_capture_unit_t capture_unit)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_capture_direction_t captured_direction;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_CAPTURE_UNIT(capture_unit));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get captured counting direction */
  captured_direction = (hal_hrtim_capture_direction_t)
                       LL_HRTIM_TIM_GetCapturedDirection(p_hrtim, timer, (uint32_t)capture_unit);

  return captured_direction;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group18
  *  @{
  */
/**
  * @brief  Configure the delayed protection of the HRTIM outputs.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_delayed_prot_config_t structure that
  *                  contains the delayed protection configuration.
  * @warning This function must not be called when the delayed protection is enabled
  *          (@ref HAL_HRTIM_TIM_EnableDelayedProtection).
  * @warning Balanced idle mode is only available in push-pull mode ().
  * @warning Balanced idle mode isn't supported when the counter operates in up-down mode.
  * @warning When the balanced Idle mode is enabled, the selected external event
  *          triggers a capture of the counter value into the compare 4 active register.
  *          Therefore, compare unit 4 is reserved and can't be used for another purpose.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetConfigDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                      uint32_t timer,
                                                      const hal_hrtim_delayed_prot_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t dlyprt;
  uint8_t timer_index;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_DELAYED_PROTECTION_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_HRTIM_DELAYED_PROTECTION_EVENT(timer, p_config->event));

#if defined(USE_ASSERT_DBG_PARAM)
  if (p_config->mode == HAL_HRTIM_DELAYED_IDLE)
  {
    ASSERT_DBG_PARAM(IS_HRTIM_TIMER_OUTPUTS(p_config->outputs));
  }
#endif /* USE_ASSERT_DBG_PARAM */

  timer_index = HRTIM_GET_TIMER_INDEX(timer);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the delayed protection mode */
  dlyprt = hrtim_hal_to_ll_dlyprt(timer_index, p_config->outputs, p_config->mode, p_config->event);

  LL_HRTIM_TIM_SetDLYPRTMode(p_hrtim, timer, dlyprt);

  /* Configure balanced idle automatic resuming as per selected mode */
  if (p_config->mode == HAL_HRTIM_BALANCED_IDLE_AUTO_RESUME)
  {
    LL_HRTIM_TIM_EnableBIAR(p_hrtim, timer);
  }
  else
  {
    LL_HRTIM_TIM_DisableBIAR(p_hrtim, timer);
  }

  return HAL_OK;
}

/**
  * @brief  Get the delayed protection configuration of the HRTIM outputs.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_delayed_prot_config_t structure that
  *                  contains the delayed protection configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetConfigDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                      uint32_t timer,
                                                      hal_hrtim_delayed_prot_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t dlyprt;
  uint32_t biar;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get delayed protection mode */
  dlyprt = LL_HRTIM_TIM_GetDLYPRTMode(p_hrtim, timer);
  biar = LL_HRTIM_TIM_IsEnabledBIAR(p_hrtim, timer);

  if ((timer == HAL_HRTIM_TIMA) \
      || (timer == HAL_HRTIM_TIMB) \
      || (timer == HAL_HRTIM_TIMC))
  {
    switch (dlyprt)
    {
      case LL_HRTIM_DLYPRT_DELAYOUT1_EEVF:
        p_config->event = HAL_HRTIM_EEVF;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1;
        break;
      case LL_HRTIM_DLYPRT_DELAYOUT2_EEVF:
        p_config->event = HAL_HRTIM_EEVF;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT2;
        break;
      case LL_HRTIM_DLYPRT_DELAYBOTH_EEVF:
        p_config->event = HAL_HRTIM_EEVF;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      case LL_HRTIM_DLYPRT_BALANCED_EEVF:
        p_config->event = HAL_HRTIM_EEVF;
        p_config->mode = (biar != 0U) ? HAL_HRTIM_BALANCED_IDLE_AUTO_RESUME : HAL_HRTIM_BALANCED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      case LL_HRTIM_DLYPRT_DELAYOUT1_EEVG:
        p_config->event = HAL_HRTIM_EEVG;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1;
        break;
      case LL_HRTIM_DLYPRT_DELAYOUT2_EEVG:
        p_config->event = HAL_HRTIM_EEVG;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT2;
        break;
      case LL_HRTIM_DLYPRT_DELAYBOTH_EEVG:
        p_config->event = HAL_HRTIM_EEVG;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      case LL_HRTIM_DLYPRT_BALANCED_EEVG:
        p_config->event = HAL_HRTIM_EEVG;
        p_config->mode = (biar != 0U) ? HAL_HRTIM_BALANCED_IDLE_AUTO_RESUME : HAL_HRTIM_BALANCED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      default:
        break;
    }
  }
  else
  {
    switch (dlyprt)
    {
      case LL_HRTIM_DLYPRT_DELAYOUT1_EEVH:
        p_config->event = HAL_HRTIM_EEVH;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1;
        break;
      case LL_HRTIM_DLYPRT_DELAYOUT2_EEVH:
        p_config->event = HAL_HRTIM_EEVH;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT2;
        break;
      case LL_HRTIM_DLYPRT_DELAYBOTH_EEVH:
        p_config->event = HAL_HRTIM_EEVH;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      case LL_HRTIM_DLYPRT_BALANCED_EEVH:
        p_config->event = HAL_HRTIM_EEVH;
        p_config->mode = (biar != 0U) ? HAL_HRTIM_BALANCED_IDLE_AUTO_RESUME : HAL_HRTIM_BALANCED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      case LL_HRTIM_DLYPRT_DELAYOUT1_EEVI:
        p_config->event = HAL_HRTIM_EEVI;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1;
        break;
      case LL_HRTIM_DLYPRT_DELAYOUT2_EEVI:
        p_config->event = HAL_HRTIM_EEVI;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT2;
        break;
      case LL_HRTIM_DLYPRT_DELAYBOTH_EEVI:
        p_config->event = HAL_HRTIM_EEVI;
        p_config->mode = HAL_HRTIM_DELAYED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      case LL_HRTIM_DLYPRT_BALANCED_EEVI:
        p_config->event = HAL_HRTIM_EEVI;
        p_config->mode = (biar != 0U) ? HAL_HRTIM_BALANCED_IDLE_AUTO_RESUME : HAL_HRTIM_BALANCED_IDLE;
        p_config->outputs = HAL_HRTIM_TIM_OUT1_OUT2;
        break;
      default:
        break;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Enable the delayed protection for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Before enabling the balanced idle mode the following configuration is needed:
  *           - The timer operates in continuous mode (see @ref HAL_HRTIM_TIM_SetConfig).
  *           - The push-pull mode is enabled (see @ref HAL_HRTIM_TIM_EnablePushPull).
  *           - The compare unit 4 is forced to 0 (see @ref HAL_HRTIM_TIM_SetCompareValue).
  *           - The auto-delayed mode is disabled (see @ref HAL_HRTIM_TIM_SetAutoDelayedMode).
  *           - Balanced idle mode is configured (see @ref HAL_HRTIM_TIM_SetConfigDelayedProtection).
  * @note   Once enabled, the selected delayed protection mode is applied to timer output 1,
  *         timer output 2 or both timer's outputs as per delayed protection mode configuration
  *         (see @ref HAL_HRTIM_TIM_SetConfigDelayedProtection).
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                   uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Delayed protection mode is enabled as per delayed protection configuration */
  LL_HRTIM_TIM_EnableDLYPRT(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Disable the delayed protection for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                    uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Delayed protection mode is disabled */
  LL_HRTIM_TIM_DisableDLYPRT(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Check if the delayed protection is enabled for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Delayed protection mode enable status.
  */
hal_hrtim_delayed_protection_status_t HAL_HRTIM_TIM_IsEnabledDelayedProtection(const hal_hrtim_handle_t *hhrtim,
                                                                               uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_delayed_protection_status_t delayed_protection_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  delayed_protection_status = (hal_hrtim_delayed_protection_status_t)LL_HRTIM_TIM_IsEnabledDLYPRT(p_hrtim, timer);

  return delayed_protection_status;
}

/**
  * @brief  Check if the output was active when delayed idle.
  *         protection was triggered.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @warning This function is relevant only when delayed protection is configured in
  *          delayed idle mode (see @ HAL_HRTIM_TIM_SetConfigDelayedProtection)
  * @return Level of the HRTIM output (INACTIVE or ACTIVE) when the delayed idle mode was triggered.
  */
hal_hrtim_output_level_t HAL_HRTIM_OUT_GetDelayedProtectionLevel(const hal_hrtim_handle_t *hhrtim,
                                                                 uint32_t output)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_output_level_t output_level = HAL_HRTIM_OUTPUT_INACTIVE;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX_FROM_OUTPUT(output)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  output_level = (hal_hrtim_output_level_t)LL_HRTIM_OUT_GetDLYPRTOutStatus(p_hrtim, output);

  return output_level;
}

/**
  * @brief  Enable balanced idle automatic resume.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   When balanced idle automatic resume is enabled, exit from balanced idle
  *         is automatic and concerned outputs are automatically re-enabled.
  * @warning This function must not be called when the timer is already started.
  * @warning In balanced idle automatic resuming mode, it is mandatory to set the
  *          IDLE state of the concerned outputs to INACTIVE (see @ref HAL_HRTIM_OUT_SetConfig).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableBalancedIdleAutoResume(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable balanced idle automatic resume */
  LL_HRTIM_TIM_EnableBIAR(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Disable balanced idle automatic resume.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableBalancedIdleAutoResume(const hal_hrtim_handle_t *hhrtim,
                                                         uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable balanced idle automatic resume */
  LL_HRTIM_TIM_DisableBIAR(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Check if balanced idle automatic resume is enabled.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Balanced idle automatic resume enable status.
  */
hal_hrtim_balanced_idle_auto_resume_status_t HAL_HRTIM_TIM_IsEnabledBalancedIdleAutoResume(
  const hal_hrtim_handle_t *hhrtim,
  uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_balanced_idle_auto_resume_status_t balanced_idle_auto_resume_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  balanced_idle_auto_resume_status =
    (hal_hrtim_balanced_idle_auto_resume_status_t)LL_HRTIM_TIM_IsEnabledBIAR(p_hrtim, timer);

  return balanced_idle_auto_resume_status;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group19
  *  @{
  */
/**
  * @brief  Set the deadtime mode for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param deadtime_mode Deadtime mode based on @ref hal_hrtim_deadtime_mode_t
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetDeadtimeMode(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_deadtime_mode_t deadtime_mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME_MODE(deadtime_mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the deatime mode */
  LL_HRTIM_DT_SetMode(p_hrtim, timer, (uint32_t)deadtime_mode);

  return HAL_OK;
}

/**
  * @brief  Get the deadtime mode for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Deadtime mode.
  */
hal_hrtim_deadtime_mode_t HAL_HRTIM_TIM_GetDeadtimeMode(const hal_hrtim_handle_t *hhrtim,
                                                        uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_deadtime_mode_t deadtime_mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get deadtime mode configuration */
  deadtime_mode = (hal_hrtim_deadtime_mode_t)LL_HRTIM_DT_GetMode(p_hrtim, timer);

  return deadtime_mode;
}

/**
  * @brief  Configure the deadtime for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  deadtime rising or falling deadtime.
  * @param  p_config pointer to a @ref hal_hrtim_deadtime_config_t structure that
  *                  contains the deadtime configuration.
  * @note   Two deadtimes can be defined in relationship with the rising edge
  *         and the falling edge of the reference waveform.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetConfigDeadtime(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_deadtime_t deadtime,
                                             const hal_hrtim_deadtime_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t ll_dt_falling_sign;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME(deadtime));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME_VALUE(p_config->value));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME_SIGN(p_config->sign));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the deatime */
  if (deadtime == HAL_HRTIM_DEADTIME_RISING)
  {
    LL_HRTIM_DT_SetRisingValue(p_hrtim, timer, p_config->value);
    LL_HRTIM_DT_SetRisingSign(p_hrtim, timer, (uint32_t)p_config->sign);
  }
  else
  {
    LL_HRTIM_DT_SetFallingValue(p_hrtim, timer, p_config->value);
    ll_dt_falling_sign = (p_config->sign ==  HAL_HRTIM_DEADTIME_POSITIVE) ? \
                         LL_HRTIM_DT_FALLING_POSITIVE : LL_HRTIM_DT_FALLING_NEGATIVE;
    LL_HRTIM_DT_SetFallingSign(p_hrtim, timer, ll_dt_falling_sign);
  }

  return HAL_OK;
}

/**
  * @brief  Get the deadtime configuration for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  deadtime rising or falling deadtime based on @ref hal_hrtim_deadtime_t.
  * @param  p_config pointer to a @ref hal_hrtim_deadtime_config_t structure that
  *                  contains the deadtime configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetConfigDeadtime(const hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer,
                                             hal_hrtim_deadtime_t deadtime,
                                             hal_hrtim_deadtime_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t ll_dt_falling_sign;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME(deadtime));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get deatime configuration */
  if (deadtime == HAL_HRTIM_DEADTIME_RISING)
  {
    p_config->value = (uint16_t)LL_HRTIM_DT_GetRisingValue(p_hrtim, timer);
    p_config->sign = (hal_hrtim_deadtime_sign_t)LL_HRTIM_DT_GetRisingSign(p_hrtim, timer);
  }
  else
  {
    p_config->value = (uint16_t)LL_HRTIM_DT_GetFallingValue(p_hrtim, timer);
    ll_dt_falling_sign = LL_HRTIM_DT_GetFallingSign(p_hrtim, timer);
    p_config->sign = (ll_dt_falling_sign == LL_HRTIM_DT_FALLING_POSITIVE) ? \
                     HAL_HRTIM_DEADTIME_POSITIVE : HAL_HRTIM_DEADTIME_NEGATIVE;
  }

  return HAL_OK;
}

/**
  * @brief  Set the deadtime prescaler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  prescaler Deadime prescaler value based on @ref hal_hrtim_deadtime_prescaler_t.
  * @note   The deadtime generator clock (fDTG) is based on a specific clock
  *         derived from the main HRTIM clock (fHRTIM).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetDeadtimePrescaler(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer,
                                                hal_hrtim_deadtime_prescaler_t prescaler)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME_PRESCALER(prescaler));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the deatime prescaler */
  LL_HRTIM_DT_SetPrescaler(p_hrtim, timer, (uint32_t)prescaler);

  return HAL_OK;
}

/**
  * @brief  Return the deadtime prescaler.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Deadtime prescaler value.
  */
hal_hrtim_deadtime_prescaler_t HAL_HRTIM_TIM_GetDeadtimePrescaler(const hal_hrtim_handle_t *hhrtim,
                                                                  uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_deadtime_prescaler_t prescaler;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get deadtime prescaler configuration */
  prescaler = (hal_hrtim_deadtime_prescaler_t)LL_HRTIM_DT_GetPrescaler(p_hrtim, timer);

  return prescaler;
}

/**
  * @brief  Lock the rising or falling deadtime value.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  deadtime rising or falling deadtime based on @ref hal_hrtim_deadtime_t.
  * @param  lock lock level based on @ref hal_hrtim_deadtime_lock_t.
  * @note   Once locked the rising or falling deadtime sign can't be changed
  *         until the next system reset.
  * @note   Once locked the rising or falling deadtime value can't be changed
  *         until the next system reset.
  * @note   Once locked the deadtime prescaler can't be changed until the next
  *         system reset.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_LockDeadtime(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer,
                                        hal_hrtim_deadtime_t deadtime,
                                        hal_hrtim_deadtime_lock_t lock)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME(deadtime));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME_LOCK(lock));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Lock the rising/falling deadtime configuration */
  if (deadtime == HAL_HRTIM_DEADTIME_RISING)
  {
    if (lock == HAL_HRTIM_DEADTIME_LOCK_SIGN)
    {
      LL_HRTIM_DT_LockRisingSign(p_hrtim, timer);
    }
    else
    {
      LL_HRTIM_DT_LockRising(p_hrtim, timer);
    }
  }
  else
  {
    if (lock == HAL_HRTIM_DEADTIME_LOCK_SIGN)
    {
      LL_HRTIM_DT_LockFallingSign(p_hrtim, timer);
    }
    else
    {
      LL_HRTIM_DT_LockFalling(p_hrtim, timer);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Return the rising or falling deadtime value lock status.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  deadtime rising or falling deadtime based on @ref hal_hrtim_deadtime_t.
  * @return Rising or falling deadtime lock.
  */
hal_hrtim_deadtime_lock_status_t HAL_HRTIM_TIM_GetLockDeadtime(const hal_hrtim_handle_t *hhrtim,
                                                               uint32_t timer,
                                                               hal_hrtim_deadtime_t deadtime)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_deadtime_lock_status_t deadtime_lock_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_DEADTIME(deadtime));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get rising/falling deadtime lock configuration */
  if (deadtime == HAL_HRTIM_DEADTIME_RISING)
  {
    if (LL_HRTIM_DT_GetLockRising(p_hrtim, timer) == 0U)
    {
      if (LL_HRTIM_DT_GetLockRisingSign(p_hrtim, timer) == 0U)
      {
        deadtime_lock_status = HAL_HRTIM_DEADTIME_UNLOCKED;
      }
      else
      {
        deadtime_lock_status = HAL_HRTIM_DEADTIME_LOCKED_SIGN;
      }
    }
    else
    {
      deadtime_lock_status = HAL_HRTIM_DEADTIME_LOCKED_SIGN_AND_VALUE;
    }
  }
  else
  {
    if (LL_HRTIM_DT_GetLockFalling(p_hrtim, timer) == 0U)
    {
      if (LL_HRTIM_DT_GetLockFallingSign(p_hrtim, timer) == 0U)
      {
        deadtime_lock_status = HAL_HRTIM_DEADTIME_UNLOCKED;
      }
      else
      {
        deadtime_lock_status = HAL_HRTIM_DEADTIME_LOCKED_SIGN;
      }
    }
    else
    {
      deadtime_lock_status = HAL_HRTIM_DEADTIME_LOCKED_SIGN_AND_VALUE;
    }
  }

  return deadtime_lock_status;
}

/**
  * @brief  Enable the deadtime for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   When deadtime is enabled, the concerned timer generates a couple
  *         of complementary signals based on the reference waveform defined
  *         for CHx1.
  * @warning This function must not be called when:
  *            - The timer is started.
  *            - The timer's output are set/reset by another timer (timer is stopped).
  * @warning When the deadtime is enabled , it is necessary to force the output
  *          state by software, to have the outputs in a complementary state as
  *          soon as the RUN mode is entered.
  * @warning For the particular case where deadtime must be enabled
  *          while the burst mode is enabled with a deadtime upon entry see
  *          (@ref HAL_HRTIM_EnableBurstMode and @ref HAL_HRTIM_OUT_SetBurstMode
  *          respectively), it is necessary to force the two outputs in their
  *          IDLE state by software before setting enabling the deadtime. This
  *          is to avoid any side effect resulting from a burst mode entry that
  *          might happen immediately before a deadtime enable.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableDeadtime(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable deadtime */
  LL_HRTIM_TIM_EnableDeadTime(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Disable the deadtime for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning This function must not be called when:
  *            - The timer is started.
  *            - The timer's output are set/reset by another timer (timer is stopped).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableDeadtime(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable deadtime */
  LL_HRTIM_TIM_DisableDeadTime(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Return the deadtime status for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Deadtime enable status.
  */
hal_hrtim_deadtime_status_t HAL_HRTIM_TIM_IsEnabledDeadtime(const hal_hrtim_handle_t *hhrtim,
                                                            uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_deadtime_status_t deadtime_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  deadtime_status = (hal_hrtim_deadtime_status_t)LL_HRTIM_TIM_IsEnabledDeadTime(p_hrtim, timer);

  return deadtime_status;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group20
  *  @{
  */
/**
  * @brief  Configure the chopper mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_chopper_config_t structure that
  *                  contains the chopper mode configuration.
  * @warning This function must not be called when the chopper mode is enabled
  *          (see @ref HAL_HRTIM_TIM_EnableChopper).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetConfigChopper(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            const hal_hrtim_chopper_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_CHOPPER_PRESCALER(p_config->prescaler));
  ASSERT_DBG_PARAM(IS_HRTIM_CHOPPER_PULSE(p_config->start_pulse_width));
  ASSERT_DBG_PARAM(IS_HRTIM_CHOPPER_DUTY_CYCLE(p_config->duty_cycle));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure chopper stage */
  LL_HRTIM_CHP_Config(p_hrtim, timer,
                      ((uint32_t)p_config->prescaler | \
                       (uint32_t)p_config->start_pulse_width | \
                       (uint32_t)p_config->duty_cycle));

  return HAL_OK;
}

/**
  * @brief  Get the chopper mode configuration of a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_chopper_config_t structure that
  *                  contains the chopper mode configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetConfigChopper(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_chopper_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get chopper stage configuration */
  p_config->prescaler = (hal_hrtim_chopper_prescaler_t)LL_HRTIM_CHP_GetPrescaler(p_hrtim, timer);
  p_config->start_pulse_width = (hal_hrtim_chopper_pulse_t)LL_HRTIM_CHP_GetPulseWidth(p_hrtim, timer);
  p_config->duty_cycle = (hal_hrtim_chopper_duty_cycle_t)LL_HRTIM_CHP_GetDutyCycle(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Enable the chopper mode for the timer output(s).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  outputs  Timer A...F output(s) based on @ref hal_hrtim_tim_outputs_t.
  * @note   When the chopper mode is enabled, high-frequency carrier is be
  *         added on top of the timing unit output signal.
  * @warning This function must not be called when the concerned outputs are
  *          already enabled.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableChopper(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer,
                                         hal_hrtim_tim_outputs_t outputs)
{
  HRTIM_TypeDef *p_hrtim;
  uint8_t timing_unit_index = HRTIM_GET_TIMING_UNIT_INDEX(timer);

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER_OUTPUTS(outputs));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable chopper mode on requested outputs using the lookup table */
  if (((uint32_t)outputs & (uint32_t)HAL_HRTIM_TIM_OUT1) != 0U)
  {
    LL_HRTIM_OUT_SetChopperMode(p_hrtim, HRTIM_OutputLookup[timing_unit_index][0], LL_HRTIM_OUT_CHOPPERMODE_ENABLE);
  }

  if (((uint32_t)outputs & (uint32_t)HAL_HRTIM_TIM_OUT2) != 0U)
  {
    LL_HRTIM_OUT_SetChopperMode(p_hrtim, HRTIM_OutputLookup[timing_unit_index][1], LL_HRTIM_OUT_CHOPPERMODE_ENABLE);
  }

  return HAL_OK;
}

/**
  * @brief  Disable the chopper mode for the timer output(s).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  outputs  Timer A...F output(s) based on @ref hal_hrtim_tim_outputs_t.
  * @warning This function must not be called when the concerned outputs are
  *          already enabled.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableChopper(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer,
                                          hal_hrtim_tim_outputs_t outputs)
{
  HRTIM_TypeDef *p_hrtim;
  uint8_t timing_unit_index = HRTIM_GET_TIMING_UNIT_INDEX(timer);

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER_OUTPUTS(outputs));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable chopper mode on requested outputs using the lookup table */
  if (((uint32_t)outputs & (uint32_t)HAL_HRTIM_TIM_OUT1) != 0U)
  {
    LL_HRTIM_OUT_SetChopperMode(p_hrtim, HRTIM_OutputLookup[timing_unit_index][0], LL_HRTIM_OUT_CHOPPERMODE_DISABLE);
  }

  if (((uint32_t)outputs & (uint32_t)HAL_HRTIM_TIM_OUT2) != 0U)
  {
    LL_HRTIM_OUT_SetChopperMode(p_hrtim, HRTIM_OutputLookup[timing_unit_index][1], LL_HRTIM_OUT_CHOPPERMODE_DISABLE);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the chopper mode is enabled for the timer output(s).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  outputs  Timer A...F output(s) based on @ref hal_hrtim_tim_outputs_t.
  * @return Chopper mode enable status.
  */
hal_hrtim_chopper_status_t HAL_HRTIM_TIM_IsEnabledChopper(const hal_hrtim_handle_t *hhrtim,
                                                          uint32_t timer,
                                                          hal_hrtim_tim_outputs_t outputs)
{
  const HRTIM_TypeDef *p_hrtim;
  uint8_t timing_unit_index = HRTIM_GET_TIMING_UNIT_INDEX(timer);
  hal_hrtim_chopper_status_t chopper_status = HAL_HRTIM_CHOPPER_ENABLED;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_TIMER_OUTPUTS(outputs));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Check OUT1 if requested */
  if (((uint32_t)outputs & (uint32_t)HAL_HRTIM_TIM_OUT1) != 0U)
  {
    if (LL_HRTIM_OUT_GetChopperMode(p_hrtim, HRTIM_OutputLookup[timing_unit_index][0])
        != LL_HRTIM_OUT_CHOPPERMODE_ENABLE)
    {
      chopper_status = HAL_HRTIM_CHOPPER_DISABLED;
    }
  }

  /* Check OUT2 if requested */
  if ((((uint32_t)outputs & (uint32_t)HAL_HRTIM_TIM_OUT2) != 0U) && (chopper_status == HAL_HRTIM_CHOPPER_ENABLED))
  {
    if (LL_HRTIM_OUT_GetChopperMode(p_hrtim, HRTIM_OutputLookup[timing_unit_index][1])
        != LL_HRTIM_OUT_CHOPPERMODE_ENABLE)
    {
      chopper_status = HAL_HRTIM_CHOPPER_DISABLED;
    }
  }

  return chopper_status;
}
/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group21
  *  @{
  */
/**
  * @brief  Enable the push-pull mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   When the push-pull mode is enabled, the two outputs of the timer
  *         are alternatively put in RUN and IDLE state to maintain the
  *         balance between the two PWM outputs.
  * @note   The push-pull period is twice the timer counting period.
  * @warning This function must not be called if the timer is started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnablePushPull(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable the push-pull mode */
  LL_HRTIM_TIM_EnablePushPullMode(p_hrtim, timer);

  return HAL_OK;
}
/**
  * @brief  Disable the push-pull mode for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning It is necessary to stop the timer to stop a push-pull operation
  *          and to reset the counter before re-starting the timer.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisablePushPull(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable the push-pull mode */
  LL_HRTIM_TIM_DisablePushPullMode(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Check if the push-pull mode is enabled for a timer.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Push-pull mode enable status.
  */
hal_hrtim_pushpull_status_t HAL_HRTIM_TIM_IsEnabledPushPull(const hal_hrtim_handle_t *hhrtim,
                                                            uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_pushpull_status_t pushpull_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  pushpull_status = (hal_hrtim_pushpull_status_t)LL_HRTIM_TIM_IsEnabledPushPullMode(p_hrtim, timer);

  return pushpull_status;
}

/**
  * @brief  Return the current push-pull status.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   The current push-pull status indicates on which output the signal is
  *         currently active.
  * @note   When balanced idle mode is enabled, this function can be used to
  *         know on which output the re-start sequence can be initiated.
  * @return Current push-pull status.
  */
hal_hrtim_pushpull_current_output_t HAL_HRTIM_TIM_GetPushPullCurrentStatus(const hal_hrtim_handle_t *hhrtim,
                                                                           uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_pushpull_current_output_t pushpull_current_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  pushpull_current_status = (hal_hrtim_pushpull_current_output_t)LL_HRTIM_TIM_GetCurrentPushPullStatus(p_hrtim, timer);

  return pushpull_current_status;
}

/**
  * @brief  Return the idle push-pull status.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   This information is significant only when delayed protection (delayed
  *         idle or balanced idle) is enabled together with push-pull mode.
  * @note   This function can be called when delayed Idle or balanced Idle mode
  *         has been entered to know during which period the delayed protection
  *         request was triggered.
  * @return Idle push-pull status.
  */
hal_hrtim_pushpull_idle_output_t HAL_HRTIM_TIM_GetPushPullIdleStatus(const hal_hrtim_handle_t *hhrtim,
                                                                     uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_pushpull_idle_output_t pushpull_idle_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  pushpull_idle_status = (hal_hrtim_pushpull_idle_output_t)LL_HRTIM_TIM_GetIdlePushPullStatus(p_hrtim, timer);

  return pushpull_idle_status;
}

/**
  * @brief  Set the push-pull ADC trigger for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  pushpull_adc_trigger  Push-pull ADC trigger based on @ref hal_hrtim_pushpull_adc_trigger_t.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetPushPullAdcTrigger(const hal_hrtim_handle_t *hhrtim,
                                                 uint32_t timer,
                                                 hal_hrtim_pushpull_adc_trigger_t pushpull_adc_trigger)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_PUSHPULL_ADC_TRIGGER(pushpull_adc_trigger));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure ADC trigger generation vs. push-pull mode */
  LL_HRTIM_TIM_SetADCTrigMode(p_hrtim, timer, (uint32_t)pushpull_adc_trigger);

  return HAL_OK;
}

/**
  * @brief  Get the push-pull ADC trigger of a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Push-pull ADC trigger.
  */
hal_hrtim_pushpull_adc_trigger_t HAL_HRTIM_TIM_GetPushPullAdcTrigger(const hal_hrtim_handle_t *hhrtim,
                                                                     uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_pushpull_adc_trigger_t pushpull_adc_trigger;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  pushpull_adc_trigger = (hal_hrtim_pushpull_adc_trigger_t)LL_HRTIM_TIM_GetADCTrigMode(p_hrtim, timer);

  return pushpull_adc_trigger;
}
/**
  *  @}
  */

/**  @addtogroup HRTIM_Exported_Functions_Group24
  * @{
  */
/**
  * @brief  Configure the crossbar override mode of a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_xbar_ovr_config_t structure that
  *                  contains the crossbar override mode configuration.
  * @note   When the crossbar override is configured in latched mode, crossbar override mode is maintained until a
  *         software intervention to disengage it (see @ref HAL_HRTIM_TIM_RearmXbarOvr).
  * @warning This function must not be called when the timer is already started.
  * @warning cycle-by-cycle mode is only applicable in force on event mode (see @ref HAL_HRTIM_OUT_SetXbarOvrForceMode).
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid configuration (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_TIM_SetConfigXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            const hal_hrtim_xbar_ovr_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_HRTIM_XBAR_OVR_TRIGGERS(p_config->triggers));
  ASSERT_DBG_PARAM(IS_HRTIM_XBAR_OVR_MODE(p_config->mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the crossbar override triggers */
  LL_HRTIM_CO_SetTrig(p_hrtim, timer, (uint32_t)p_config->triggers);

  /* Configure the crossbar override mode */
  LL_HRTIM_CO_SetMode(p_hrtim, timer, (uint32_t)p_config->mode);

  return HAL_OK;
}

/**
  * @brief  Get the crossbar override mode configuration of a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  p_config pointer to a @ref hal_hrtim_xbar_ovr_config_t structure that
  *                  contains the crossbar override mode configuration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_GetConfigXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                            uint32_t timer,
                                            hal_hrtim_xbar_ovr_config_t *p_config)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(p_config != NULL);

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Get crossbar override configuration */
  p_config->triggers = LL_HRTIM_CO_GetTrig(p_hrtim, timer);
  p_config->mode = (hal_hrtim_xbar_ovr_mode_t)LL_HRTIM_CO_GetMode(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Configure the crossbar override force mode of an HRTIM output.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @param  mode  crossbar override for mode based on @ref hal_hrtim_xbar_ovr_force_mode_t.
  * @warning Force on event mode can't be used with deadtime enabled (see @ref HAL_HRTIM_TIM_EnableDeadtime).
  * @warning Force on event mode requires the crossbar override mode to be configured in cycle-by-cycle mode
  *          (see @ref HAL_HRTIM_TIM_SetConfigXbarOvr).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_SetXbarOvrForceMode(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t output,
                                               hal_hrtim_xbar_ovr_force_mode_t mode)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));
  ASSERT_DBG_PARAM(IS_HRTIM_XBAR_OVR_FORCE_MODE(mode));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the output force mode */
  LL_HRTIM_CO_SetForceMode(p_hrtim, output, (uint32_t)mode);

  return HAL_OK;
}


/**
  * @brief  Return the crossbar override force mode of an HRTIM output.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @return Output crossbar override force mode.
  */
hal_hrtim_xbar_ovr_force_mode_t HAL_HRTIM_OUT_GetXbarOvrForceMode(const hal_hrtim_handle_t *hhrtim,
                                                                  uint32_t output)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_xbar_ovr_force_mode_t mode;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  mode = (hal_hrtim_xbar_ovr_force_mode_t)LL_HRTIM_CO_GetForceMode(p_hrtim, output);

  return mode;
}

/**
  * @brief  Select the event(s) forcing the output to its active state (when the output is configured in force on event
  *         mode).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @param  forcing_events Event(s) forcing the output to its active level.
  * @note   This function must be called if the output crossbar override force mode is configured in
  *         force on event mode (see @ref HAL_HRTIM_OUT_SetXbarOvrForceMode).
  * @note   When the crossbar override mode is active, the output is forced to its active level when the
  *         specified external event(s) is(are) active.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_OUT_SetXbarOvrForcingEvents(const hal_hrtim_handle_t *hhrtim,
                                                   uint32_t output,
                                                   uint32_t forcing_events)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));
  ASSERT_DBG_PARAM(IS_HRTIM_XBAR_OVR_FORCING_EVENTS(forcing_events));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the crossbar override forcing event(s) */
  LL_HRTIM_CO_SetForcingEvents(p_hrtim, output, forcing_events);

  return HAL_OK;
}

/**
  * @brief  Get the event(s) forcing the output to its active state.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  output HRTIM output.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_CHA1   Timer A - output 1
  *         @arg @ref HAL_HRTIM_CHA2   Timer A - output 2
  *         @arg @ref HAL_HRTIM_CHB1   Timer B - output 1
  *         @arg @ref HAL_HRTIM_CHB2   Timer B - output 2
  *         @arg @ref HAL_HRTIM_CHC1   Timer C - output 1
  *         @arg @ref HAL_HRTIM_CHC2   Timer C - output 2
  *         @arg @ref HAL_HRTIM_CHD1   Timer D - output 1
  *         @arg @ref HAL_HRTIM_CHD2   Timer D - output 2
  *         @arg @ref HAL_HRTIM_CHE1   Timer E - output 1
  *         @arg @ref HAL_HRTIM_CHE2   Timer E - output 2
  *         @arg @ref HAL_HRTIM_CHF1   Timer F - output 1
  *         @arg @ref HAL_HRTIM_CHF2   Timer F - output 2
  * @return Event(s) forcing the output to its active level.
  */
uint32_t HAL_HRTIM_OUT_GetXbarOvrForcingEvents(const hal_hrtim_handle_t *hhrtim,
                                               uint32_t output)
{
  HRTIM_TypeDef *p_hrtim;
  uint32_t forcing_events;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_OUTPUT(output));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  forcing_events = LL_HRTIM_CO_GetForcingEvents(p_hrtim, output);

  return forcing_events;
}

/**
  * @brief  Configure the delayed fault duration of an HRTIM output (when the output is configured in delayed
  *         fault mode).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  delay_option Delay selection.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_XBAR_OVR_DELAY1   Delay 1
  *         @arg @ref HAL_HRTIM_XBAR_OVR_DELAY2   Delay 2
  * @param  delay_value  Delay applied before entering in Fault mode .
  *                      This parameter must be a number between 0x0 and 0x1FF.
  * @note   This function must be called if the output crossbar override force mode is configured in
  *         delayed fault mode (see @ref HAL_HRTIM_OUT_SetXbarOvrForceMode).
  * @note   Once the crossbar override mode is entered, the output is forced to its inactive level after the specified
  *         delay expiration.
  * @warning Delay 2 duration must be greater than Delay 1 duration.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_SetXbarOvrDelay(const hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_xbar_ovr_delay_option_t delay_option,
                                           uint16_t delay_value)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_XBAR_OVR_DELAY_OPTION(delay_option));
  ASSERT_DBG_PARAM(IS_HRTIM_XBAR_OVR_DELAY_VALUE(delay_value));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Configure the output force mode */
  LL_HRTIM_CO_SetDelay(p_hrtim, timer, (uint32_t)delay_option, (uint32_t)delay_value);

  return HAL_OK;
}

/**
  * @brief  Return the delayed fault duration of an HRTIM output.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @param  delay_option Delayed fault identifier.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_XBAR_OVR_DELAY1   Delay 1
  *         @arg @ref HAL_HRTIM_XBAR_OVR_DELAY2   Delay 2
  * @return Delay duration .
  *         Number between 0x0 and 0x1FF.
  */
uint16_t HAL_HRTIM_TIM_GetXbarOvrDelay(const hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer,
                                       hal_hrtim_xbar_ovr_delay_option_t delay_option)
{
  HRTIM_TypeDef *p_hrtim;
  uint16_t delay_value;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));
  ASSERT_DBG_PARAM(IS_HRTIM_XBAR_OVR_DELAY_OPTION(delay_option));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  delay_value = (uint16_t)LL_HRTIM_CO_GetDelay(p_hrtim, timer, (uint32_t)delay_option);

  return delay_value;
}

/**
  * @brief  Enable the crossbar override mode for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable crossbar override */
  LL_HRTIM_CO_Enable(p_hrtim, timer);

  return HAL_OK;
}


/**
  * @brief  Disable the crossbar override mode for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Crossbar override function is disengaged as son as crossbar override mode is disabled.
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable crossbar override */
  LL_HRTIM_CO_Disable(p_hrtim, timer);

  return HAL_OK;
}


/**
  * @brief  Check if the crossbar override mode is enabled for a timig unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @retval HAL_HRTIM_XBAR_OVR_ENABLED   Crossbar override mode enable status.
  */
hal_hrtim_xbar_ovr_status_t HAL_HRTIM_TIM_IsEnabledXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                                           uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_xbar_ovr_status_t xbar_ovr_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  xbar_ovr_status = (hal_hrtim_xbar_ovr_status_t)LL_HRTIM_CO_IsEnabled(p_hrtim, timer);

  return xbar_ovr_status;
}

/**
  * @brief  Enable the dual channel DAC crossbar override mode for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_EnableDualDACXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Enable Dual channel DAC crossbar override */
  LL_HRTIM_CO_EnableDualChannelDac(p_hrtim, timer);

  return HAL_OK;
}


/**
  * @brief  Disable the dual channel DAC crossbar override mode for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @warning This function must not be called when the timer is already started.
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_DisableDualDACXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                                 uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)], HAL_HRTIM_TIM_STATE_IDLE);

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Disable Dual channel DAC crossbar override */
  LL_HRTIM_CO_DisableDualChannelDac(p_hrtim, timer);

  return HAL_OK;
}


/**
  * @brief  Check if the dual channel DAC crossbar override mode is enabled for a timig unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @return Dual channel DAC crossbar override mode enable status.
  */
hal_hrtim_dual_channel_dac_xbar_ovr_status_t HAL_HRTIM_TIM_IsEnabledDualDACXbarOvr(
  const hal_hrtim_handle_t *hhrtim,
  uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_dual_channel_dac_xbar_ovr_status_t dual_channel_dac_xbar_ovr_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  dual_channel_dac_xbar_ovr_status =
    (hal_hrtim_dual_channel_dac_xbar_ovr_status_t)LL_HRTIM_CO_IsEnabledDualChannelDac(p_hrtim, timer);

  return dual_channel_dac_xbar_ovr_status;
}

/**
  * @brief  Return the crossbar override state for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Crossbar override state indicates whether regular crossbar operation was interrupted and crossbar override
  *         mode is active.
  * @return hal_hrtim_xbar_ovr_mode_status_t crossbar override status.
  */
hal_hrtim_xbar_ovr_mode_status_t HAL_HRTIM_TIM_GetXbarOvrStatus(const hal_hrtim_handle_t *hhrtim,
                                                                uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_xbar_ovr_mode_status_t xbar_ovr_mode_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  xbar_ovr_mode_status = (hal_hrtim_xbar_ovr_mode_status_t)LL_HRTIM_CO_GetStatus(p_hrtim, timer);

  return xbar_ovr_mode_status;
}

/**
  * @brief  Return the crossbar override trigger state for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   Crossbar override trigger state can be polled to check whether the trigger is inactive prior rearming the
  *         crossbar override mode (see @ref HAL_HRTIM_TIM_RearmXbarOvr).
  * @return hal_hrtim_xbar_ovr_mode_status_t crossbar override status.
  */
hal_hrtim_xbar_ovr_trigger_status_t HAL_HRTIM_TIM_GetXbarOvrTriggerStatus(const hal_hrtim_handle_t *hhrtim,
                                                                          uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;
  hal_hrtim_xbar_ovr_trigger_status_t xbar_ovr_trigger_status;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  xbar_ovr_trigger_status = (hal_hrtim_xbar_ovr_trigger_status_t)LL_HRTIM_CO_GetTriggerStatus(p_hrtim, timer);

  return xbar_ovr_trigger_status;
}

/**
  * @brief  Rearm the crossbar override for a timing unit.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @note   This function must be called to disengage the crossbar override mode when it is configured in latched mode
  *         (see @ref HAL_HRTIM_TIM_SetConfigXbarOvr).
  * @note   The rearming will be effective only of the triggering condition has disappeared
  *         (see @ref HAL_HRTIM_TIM_GetXbarOvrTriggerStatus).
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_RearmXbarOvr(const hal_hrtim_handle_t *hhrtim,
                                        uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Resume standard crossbar operation */
  LL_HRTIM_CO_Rearm(p_hrtim, timer);

  return HAL_OK;
}

/**
  * @brief  Start the crossbar override mode for a timing unit (software trigger).
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @param  timer HRTIM timer.
  *         It can be one of the following values:
  *         @arg @ref HAL_HRTIM_TIMA   Timer A
  *         @arg @ref HAL_HRTIM_TIMB   Timer B
  *         @arg @ref HAL_HRTIM_TIMC   Timer C
  *         @arg @ref HAL_HRTIM_TIMD   Timer D
  *         @arg @ref HAL_HRTIM_TIME   Timer E
  *         @arg @ref HAL_HRTIM_TIMF   Timer F
  * @retval HAL_OK            Operation completed successfully.
  */
hal_status_t HAL_HRTIM_TIM_XbarOvr(const hal_hrtim_handle_t *hhrtim,
                                   uint32_t timer)
{
  HRTIM_TypeDef *p_hrtim;

  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(IS_HRTIM_TIMING_UNIT(timer));

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);
  ASSERT_DBG_STATE(hhrtim->timer_states[HRTIM_GET_TIMER_INDEX(timer)],
                   (HAL_HRTIM_TIM_STATE_IDLE | HAL_HRTIM_TIM_STATE_ACTIVE));

  p_hrtim = HRTIM_GET_INSTANCE(hhrtim);

  /* Crossbar override software trigger */
  LL_HRTIM_CO_SetTrig(p_hrtim, timer, LL_HRTIM_CO_TRIG_SW);

  return HAL_OK;
}

/**
  *  @}
  */


/** @addtogroup HRTIM_Exported_Functions_Group22
  *  @{
  */
/**
  * @brief  This function handles all the master timer related interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_M_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim = HRTIM_GET_INSTANCE(hhrtim);
  uint32_t flag_status;
  uint32_t it_sources;
  uint32_t flag_status_masked;

  /* Master timer interrupts (master update, sync Input, repetition, MCMP1..4) */

  flag_status = LL_HRTIM_MASTER_READ_REG(p_hrtim, MISR);
  it_sources = LL_HRTIM_MASTER_READ_REG(p_hrtim, MDIER);
  flag_status_masked = flag_status & it_sources;

  if ((flag_status_masked & LL_HRTIM_MISR_MCMP1) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP1(p_hrtim, HAL_HRTIM_MASTER);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_1);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_1);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_MISR_MCMP2) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP2(p_hrtim, HAL_HRTIM_MASTER);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_2);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_2);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_MISR_MCMP3) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP3(p_hrtim, HAL_HRTIM_MASTER);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_3);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_3);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_MISR_MCMP4) != 0UL)
  {
    LL_HRTIM_ClearFlag_CMP4(p_hrtim, HAL_HRTIM_MASTER);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
    hhrtim->compare_match_callback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_4);
#else
    HAL_HRTIM_CompareMatchCallback(hhrtim, HAL_HRTIM_MASTER, HAL_HRTIM_COMPARE_UNIT_4);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_MISR_SYNC) != 0UL)
  {
    LL_HRTIM_ClearFlag_SYNC(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->synchro_callback(hhrtim);
#else
    HAL_HRTIM_SynchroCallback(hhrtim);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_MISR_MREP) != 0UL)
  {
    LL_HRTIM_ClearFlag_REP(p_hrtim, HAL_HRTIM_MASTER);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)

    hhrtim->repetition_callback(hhrtim, HAL_HRTIM_MASTER);
#else
    HAL_HRTIM_RepetitionCallback(hhrtim, HAL_HRTIM_MASTER);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_MISR_MUPD) != 0UL)
  {
    LL_HRTIM_ClearFlag_UPDATE(p_hrtim, HAL_HRTIM_MASTER);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)

    hhrtim->update_callback(hhrtim, HAL_HRTIM_MASTER);
#else
    HAL_HRTIM_UpdateCallback(hhrtim, HAL_HRTIM_MASTER);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_TIMER_CALLBACKS */
  }


  /* Global interrupts except faults (burst mode period and end of DLL calibration interrupts) */

  flag_status = LL_HRTIM_READ_REG(p_hrtim, ISR);
  it_sources = LL_HRTIM_READ_REG(p_hrtim, IER);
  flag_status_masked = flag_status & it_sources;

  if ((flag_status_masked & LL_HRTIM_ISR_BMPER) != 0UL)
  {
    LL_HRTIM_ClearFlag_BMPER(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->burst_mode_period_callback(hhrtim);
#else
    HAL_HRTIM_BurstModePeriodCallback(hhrtim);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_ISR_DLLRDY) != 0UL)
  {
    LL_HRTIM_ClearFlag_DLLRDY(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->dll_calibration_callback(hhrtim);
#else
    HAL_HRTIM_DLLCalibrationCallback(hhrtim);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */
  }

}

/**
  * @brief  This function handles all the timer A related interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_TIMA_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TIMx_IRQHandler(hhrtim, HAL_HRTIM_TIMA);
}

/**
  * @brief  This function handles all the timer B related interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_TIMB_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TIMx_IRQHandler(hhrtim, HAL_HRTIM_TIMB);
}

/**
  * @brief  This function handles all the timer C related interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_TIMC_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TIMx_IRQHandler(hhrtim, HAL_HRTIM_TIMC);
}

/**
  * @brief  This function handles all the timer D related interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_TIMD_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TIMx_IRQHandler(hhrtim, HAL_HRTIM_TIMD);
}

/**
  * @brief  This function handles all the timer E related interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_TIME_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TIMx_IRQHandler(hhrtim, HAL_HRTIM_TIME);
}

/**
  * @brief  This function handles all the timer F related interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  */
void HAL_HRTIM_TIMF_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TIMx_IRQHandler(hhrtim, HAL_HRTIM_TIMF);
}

/**
  * @brief  This function handles all the HRTIM global interrupts.
  * @param  hhrtim Pointer to the HRTIM instance handle.
  * @note   All faults are grouped within a distinct vector that can
  *         be set with a very high priority.
  */
void HAL_HRTIM_FLT_IRQHandler(hal_hrtim_handle_t *hhrtim)
{
  HRTIM_TypeDef *p_hrtim = HRTIM_GET_INSTANCE(hhrtim);
  const uint32_t flag_status = LL_HRTIM_READ_REG(p_hrtim, ISR);
  const uint32_t it_sources = LL_HRTIM_READ_REG(p_hrtim, IER);
  const uint32_t flag_status_masked = flag_status & it_sources;

  if ((flag_status_masked & LL_HRTIM_ISR_FLT1) != 0UL)
  {
    LL_HRTIM_ClearFlag_FLT1(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->fault_callback(hhrtim, HAL_HRTIM_FLT1);
#else
    HAL_HRTIM_FaultCallback(hhrtim, HAL_HRTIM_FLT1);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_GLOBAL_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_ISR_FLT2) != 0UL)
  {
    LL_HRTIM_ClearFlag_FLT2(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->fault_callback(hhrtim, HAL_HRTIM_FLT2);
#else
    HAL_HRTIM_FaultCallback(hhrtim, HAL_HRTIM_FLT2);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_GLOBAL_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_ISR_FLT3) != 0UL)
  {
    LL_HRTIM_ClearFlag_FLT3(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->fault_callback(hhrtim, HAL_HRTIM_FLT3);
#else
    HAL_HRTIM_FaultCallback(hhrtim, HAL_HRTIM_FLT3);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_GLOBAL_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_ISR_FLT4) != 0UL)
  {
    LL_HRTIM_ClearFlag_FLT4(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->fault_callback(hhrtim, HAL_HRTIM_FLT4);
#else
    HAL_HRTIM_FaultCallback(hhrtim, HAL_HRTIM_FLT4);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_GLOBAL_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_ISR_FLT5) != 0UL)
  {
    LL_HRTIM_ClearFlag_FLT5(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->fault_callback(hhrtim, HAL_HRTIM_FLT5);
#else
    HAL_HRTIM_FaultCallback(hhrtim, HAL_HRTIM_FLT5);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_GLOBAL_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_ISR_FLT6) != 0UL)
  {
    LL_HRTIM_ClearFlag_FLT6(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->fault_callback(hhrtim, HAL_HRTIM_FLT6);
#else
    HAL_HRTIM_FaultCallback(hhrtim, HAL_HRTIM_FLT6);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_GLOBAL_CALLBACKS */
  }

  if ((flag_status_masked & LL_HRTIM_ISR_SYSFLT) != 0UL)
  {
    LL_HRTIM_ClearFlag_SYSFLT(p_hrtim);

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1) \
 && defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
    hhrtim->system_fault_callback(hhrtim);
#else
    HAL_HRTIM_SystemFaultCallback(hhrtim);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS && USE_HAL_HRTIM_GLOBAL_CALLBACKS */
  }

}

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)
/**
  * @brief DMA transfer half completed callback.\n
  *        This function is called to signal half completion of a DMA transfer
  *        for a particular timer.
  * @param  hhrtim  Pointer to the HRTIM instance handle.
  * @param  timer  Master timer or timing unit identifier.
  */
__WEAK void HAL_HRTIM_DMAHalfCpltCallback(hal_hrtim_handle_t *hhrtim,
                                          uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_DMAHalfCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief DMA transfer completed callback.\n
  *        This function is called to signal completion of a DMA transfer
  *        for a particular timer.
  * @param  hhrtim  Pointer to the HRTIM instance handle.
  * @param  timer  Master timer or timing unit identifier.
  */
__WEAK void HAL_HRTIM_DMACpltCallback(hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_DMACpltCallback can be implemented in the user file.
   */
}

/**
  * @brief DMA transfer stop callback.\n
  *        This function is called to signal that an on-going DMA transfer
  *        has been stopped for a particular timer.
  * @param  hhrtim  Pointer to the HRTIM instance handle.
  * @param  timer  Master timer or timing unit identifier.
  */
__WEAK void HAL_HRTIM_DMAStopCallback(hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_DMAStopCallback can be implemented in the user file.
   */
}

/**
  * @brief DMA transfer error callback.\n
  *        This function is called to signal that a DMA error has been detected
  *        for a particular timer.
  * @param  hhrtim  Pointer to the HRTIM instance handle.
  * @param  timer  Master timer or timing unit identifier.
  */
__WEAK void HAL_HRTIM_DMAErrorCallback(hal_hrtim_handle_t *hhrtim,
                                       uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_DMAErrorCallback can be implemented in the user file.
   */
}

#endif /* USE_HAL_HRTIM_DMA */

/**
  * @brief Fault callback.\n
  *        This function is called to signal a fault event.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fault  Fault input.
  */
__WEAK void HAL_HRTIM_FaultCallback(hal_hrtim_handle_t *hhrtim,
                                    uint32_t fault)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(fault);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_FaultCallback can be implemented in the user file.
   */
}

/**
  * @brief System fault callback.\n
  *        This function is called to signal a system fault.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  */
__WEAK void HAL_HRTIM_SystemFaultCallback(hal_hrtim_handle_t *hhrtim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_SystemFaultCallback can be implemented in the user file.
   */
}

/**
  * @brief Burst mode perdiod callback.\n
  *        This function is called to signal the end of the burst mode period.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  */
__WEAK void HAL_HRTIM_BurstModePeriodCallback(hal_hrtim_handle_t *hhrtim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_BurstModePeriodCallback can be implemented in the user file.
   */
}

/**
  * @brief Synchronization callback.\n
  *        This function is called to signal a synchronization event.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  */
__WEAK void HAL_HRTIM_SynchroCallback(hal_hrtim_handle_t *hhrtim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_SynchroCallback can be implemented in the user file.
   */
}

/**
  * @brief DLL calibration donen callback.\n
  *        This function is called to signal the end of the DLL calibration.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  */
__WEAK void HAL_HRTIM_DLLCalibrationCallback(hal_hrtim_handle_t *hhrtim)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_DLLCalibrationCallback can be implemented in the user file.
   */
}

/**
  * @brief Timer's registers update callback.\n
  *        This function is called to signal the timer's registers update event.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  Master timer or timing unit identifier.
  */
__WEAK void HAL_HRTIM_UpdateCallback(hal_hrtim_handle_t *hhrtim,
                                     uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_UpdateCallback can be implemented in the user file.
   */
}

/**
  * @brief Timer's repetition callback.\n
  *        This function is called to signal the timer's repetition event.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  Master timer or timing unit identifier.
  */
__WEAK void HAL_HRTIM_RepetitionCallback(hal_hrtim_handle_t *hhrtim,
                                         uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_RepetitionCallback can be implemented in the user file.
   */
}

/**
  * @brief Timer's counter reset callback.\n
  *        This function is called to signal the timer's counter reset event.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  iming unit identifier.
  */
__WEAK void HAL_HRTIM_ResetCallback(hal_hrtim_handle_t *hhrtim,
                                    uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_ResetCallback can be implemented in the user file.
   */
}

/**
  * @brief Delayed protection entry callback.\n
  *        This function is called to signal a new delayed protection entry.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  Timing unit identifier.
  */
__WEAK void HAL_HRTIM_DelayedProtectionCallback(hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_DelayedProtectionCallback can be implemented in the user file.
   */
}

/**
  * @brief Compare match callback.\n
  *        This function is called to signal a compare match event.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  Master timer or timing unit identifier.
  * @param  compare_unit  Compare unit identifier.
  */
__WEAK void HAL_HRTIM_CompareMatchCallback(hal_hrtim_handle_t *hhrtim,
                                           uint32_t timer,
                                           hal_hrtim_compare_unit_t compare_unit)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);
  STM32_UNUSED(compare_unit);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_CompareMatchCallback can be implemented in the user file.
   */
}

/**
  * @brief Capture callback.\n
  *        This function is called to signal a capture event.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  Master timer or timing unit identifier.
  * @param  capture_unit  Capture unit identifier.
  */
__WEAK void HAL_HRTIM_CaptureCallback(hal_hrtim_handle_t *hhrtim,
                                      uint32_t timer,
                                      hal_hrtim_capture_unit_t capture_unit)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);
  STM32_UNUSED(capture_unit);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_CaptureCallback can be implemented in the user file.
   */
}

/**
  * @brief Output set callback.\n
  *        This function is called when the output is forced to its ACTIVE level.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  output  HRTIM output.
  */
__WEAK void HAL_HRTIM_OutputSetCallback(hal_hrtim_handle_t *hhrtim,
                                        uint32_t output)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(output);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_OutputSetCallback can be implemented in the user file.
   */
}

/**
  * @brief Output set callback.\n
  *        This function is called when the output is forced to its INACTIVE level.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  output  HRTIM output.
  */
__WEAK void HAL_HRTIM_OutputResetCallback(hal_hrtim_handle_t *hhrtim,
                                          uint32_t output)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(output);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_OutputResetCallback can be implemented in the user file.
   */
}

/**
  * @brief Crossbar override trigger callback.\n
  *        This function is called when the crossbar override mode is entered.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  iming unit identifier.
  */
__WEAK void HAL_HRTIM_XbarOvrTriggerCallback(hal_hrtim_handle_t *hhrtim,
                                             uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_XbarOvrTriggerCallback can be implemented in the user file.
   */
}

/**
  * @brief crossbar override rearm delay callback.\n
  *        This function is called when the crossbar override rearm delay has expired.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  timer  iming unit identifier.
  */
__WEAK void HAL_HRTIM_XbarOvrRearmDelayCallback(hal_hrtim_handle_t *hhrtim,
                                                uint32_t timer)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hhrtim);
  STM32_UNUSED(timer);

  /*
   * @warning  This function must not be modified, when the callback is needed,
   *           HAL_HRTIM_XbarOvrRearmDelayCallback can be implemented in the user file.
   */
}

#if defined(USE_HAL_HRTIM_REGISTER_CALLBACKS) && (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)

#if defined(USE_HAL_HRTIM_DMA) && (USE_HAL_HRTIM_DMA == 1)

/**
  * @brief  Callback registration for the DMA transfer half complete callback.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterDMAHalfCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM((hhrtim != NULL));
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->dma_xfer_half_cplt_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the DMA transfer  complete callback.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterDMACpltCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM((hhrtim != NULL));
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->dma_xfer_cplt_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the DMA stop callback.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterDMAStopCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM((hhrtim != NULL));
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->dma_xfer_stop_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the DMA Error.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterDMAErrorCallback(hal_hrtim_handle_t *hhrtim,
                                                hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->dma_xfer_error_callback = fct;

  return HAL_OK;
}


#endif /* USE_HAL_HRTIM_DMA */

#if defined(USE_HAL_HRTIM_GLOBAL_CALLBACKS) && (USE_HAL_HRTIM_GLOBAL_CALLBACKS == 1)
/**
  * @brief  Callback registration for the fault detection notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterFaultCallback(hal_hrtim_handle_t *hhrtim,
                                             hal_hrtim_fault_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->fault_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the system fault detection notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterSystemFaultCallback(hal_hrtim_handle_t *hhrtim,
                                                   hal_hrtim_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->system_fault_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the end of burst mode period notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterBurstModePeriodCallback(hal_hrtim_handle_t *hhrtim,
                                                       hal_hrtim_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->burst_mode_period_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the HRTIM synchronization notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterSynchroCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->synchro_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the HRTIM end of DLL calibration notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterDLLCalibrationCallback(hal_hrtim_handle_t *hhrtim,
                                                      hal_hrtim_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->dll_calibration_callback = fct;

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_GLOBAL_CALLBACKS */

#if defined(USE_HAL_HRTIM_TIMER_CALLBACKS) && (USE_HAL_HRTIM_TIMER_CALLBACKS == 1)
/**
  * @brief  Callback registration for the timers update event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterUpdateCallback(hal_hrtim_handle_t *hhrtim,
                                              hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->update_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the timers repetition event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterRepetitionCallback(hal_hrtim_handle_t *hhrtim,
                                                  hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->repetition_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the timers reset event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterResetCallback(hal_hrtim_handle_t *hhrtim,
                                             hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->reset_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the timers delayed protection event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterDelayedProtectionCallback(hal_hrtim_handle_t *hhrtim,
                                                         hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->delayed_protection_callback = fct;

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_TIMER_CALLBACKS */

#if defined(USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS) && (USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS == 1)
/**
  * @brief  Callback registration for the compare match event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterCompareMatchCallback(hal_hrtim_handle_t *hhrtim,
                                                    hal_hrtim_cmp_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->compare_match_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the capture event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterCaptureCallback(hal_hrtim_handle_t *hhrtim,
                                               hal_hrtim_cpt_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->capture_callback = fct;

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_CAPTURE_COMPARE_CALLBACKS */

#if defined(USE_HAL_HRTIM_OUTPUT_CALLBACKS) && (USE_HAL_HRTIM_OUTPUT_CALLBACKS == 1)
/**
  * @brief  Callback registration for the output set event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterOutputSetCallback(hal_hrtim_handle_t *hhrtim,
                                                 hal_hrtim_output_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->output_set_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the output reset event notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterOutputResetCallback(hal_hrtim_handle_t *hhrtim,
                                                   hal_hrtim_output_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->output_reset_callback = fct;

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_OUTPUT_CALLBACKS */

#if (defined(USE_HAL_HRTIM_XBAR_OVR_CALLBACKS) && (USE_HAL_HRTIM_XBAR_OVR_CALLBACKS == 1))
/**
  * @brief  Callback registration for the crossbar override trigger notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterXbarOvrTriggerCallback(hal_hrtim_handle_t *hhrtim,
                                                      hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->xbar_ovr_trigger_callback = fct;

  return HAL_OK;
}

/**
  * @brief  Callback registration for the crossbar override rearm delay elapsed notification.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  fct   Function to register as callback.
  * @retval HAL_OK            Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid callback function pointer (only if USE_HAL_CHECK_PARAM == 1).
  */
hal_status_t HAL_HRTIM_RegisterXbarOvrRearmDelayCallback(hal_hrtim_handle_t *hhrtim,
                                                         hal_hrtim_timer_cb_t fct)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);
  ASSERT_DBG_PARAM(fct != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM ==1)
  if (fct == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(hhrtim->global_state, HAL_HRTIM_STATE_INIT);

  hhrtim->xbar_ovr_rearm_delay_callback = fct;

  return HAL_OK;
}
#endif /* USE_HAL_HRTIM_XBAR_OVR_CALLBACKS */

#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */
/**
  *  @}
  */


#if defined (USE_HAL_HRTIM_USER_DATA) && (USE_HAL_HRTIM_USER_DATA == 1)
/** @addtogroup HRTIM_Exported_Functions_Group23
  *  @{
  */
/**
  * @brief  Store User Data pointer into the handle.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_HRTIM_SetUserData(hal_hrtim_handle_t *hhrtim, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);

  hhrtim->p_user_data = p_user_data;
}

/**
  * @brief Retrieve User Data pointer from the handle.
  * @param  hhrtim  Pointer to the handle of the HRTIM instance.
  * @retval Pointer to the user data.
  */
const void *HAL_HRTIM_GetUserData(const hal_hrtim_handle_t *hhrtim)
{
  ASSERT_DBG_PARAM(hhrtim != NULL);

  return hhrtim->p_user_data;
}

/**
  *  @}
  */
#endif /* USE_HAL_HRTIM_USER_DATA */

/**
  * @}
  */

#endif /* USE_HAL_HRTIM_MODULE */

#endif /* HRTIM1 */
/**
  * @}
  */

/**
  * @}
  */
