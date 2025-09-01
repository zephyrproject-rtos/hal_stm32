/**
  **********************************************************************************************************************
  * @file    stm32c5xx_hal_eth.c
  * @brief   This file provides ETH (Ethernet) peripheral services.
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


/** @addtogroup STM32C5XX_HAL_Driver
  * @{
  */

#if defined(ETH1)

/** @addtogroup ETH
  * @{
  */
/** @defgroup ETH_Introduction ETH Introduction
  * @{
The Ethernet peripheral enables devices to transmit and receive data over Ethernet in
compliance with the IEEE 802.3-2002 standard.<br/>
The Ethernet peripheral provides a configurable, flexible interface to meet the needs of various
applications and customers.
It supports two industry-standard interfaces to the external physical layer (PHY): the default media-independent
interface (MII) defined in the IEEE 802.3 specifications and the reduced media-independent interface (RMII).
It can be used in a number of applications such as switches and network interface cards.<br />
In addition to the default interfaces defined in the IEEE 802.3 specifications, the Ethernet peripheral supports several
industry-standard interfaces to the PHY.
It is compliant with the following standards:<br/>
  - IEEE 802.3-2015 for Ethernet MAC and media independent interface (MII)
  - IEEE 1588-2008 for precision networked clock synchronization (PTP)
  - IEEE 802.1AS-2011 and 802.1-Qav-2009 for Audio Video (AV) traffic
  - IEEE 802.3az-2010 for Energy Efficient Ethernet (EEE)
  - AMBA 2.0 for AHB slave port
  - AMBA4 for AXI master port
  - RGMII specification version 2.6 from HP/Marvell
  - RMII specification version 1.2 from RMII consortium

# Main features
The software allows use of all features offered by the Ethernet hardware IP.<br/>
The main features supported by the Ethernet HAL driver are summarized below:
- Configure MAC, MTL and DMA parameters
- Transmit packets in polling and interrupt mode
- Receive packets in polling and interrupt mode
- Configure and enable MAC filters
- Configure and enable PTP
- Configure and enable ARP offload
- Manage multi-queuing in transmission and reception if supported.
    - Manage queue priorities
- Configure and enable Audio/Video (AV) features if supported:
     - Select AV Queues
     - IEEE 802.1-Qav: Credit-Based Shaper (CBS) algorithm
- Configure and enable TSN features if supported:
     - IEEE 802.1Qbv-2015: Enhancements to Scheduling Traffic
     - IEEE 802.1Qbu/802.3br: Frame preemption and Interspersing Express Traffic
     - Time-based scheduling (TBS)
- Detect and manage errors.
  */
/**
  * @}
  */

/** @defgroup ETH_How_To_Use ETH How To Use
  * @{
# The HAL ETH driver can be used as follows:

## Initialization and Configuration:
- Declare a hal_eth_handle_t handle structure, for example:
  @verbatim
  hal_eth_handle_t  heth;
  @endverbatim
- Set the ETH instance number to initialize in the heth handle.
- Initialize the ETH low level resources:
  - Enable the Ethernet interface clock using
    + HAL_RCC_ETH1_EnableClock()
    + HAL_RCC_ETH1TX_EnableClock()
    + HAL_RCC_ETH1RX_EnableClock()
    + HAL_RCC_ETH1CK_EnableClock()
  - Initialize the related GPIO clocks.
  - Configure Ethernet pinout.
  - Configure Ethernet NVIC interrupt (in Interrupt mode).
- Call HAL_ETH_Init() API to initialize the Ethernet peripheral (MAC, DMA, MTL and MDIO).
- Declare a hal_eth_config_t configuration structure, for example:
  @verbatim
  hal_eth_config_t  eth_config;
  @endverbatim
- Set the ETH global configuration parameters in the eth_config structure.
  * Set the MAC Address.
  * Select the MII/RMII/RGMII interface to use.
- Call HAL_ETH_SetConfig() API to configure the Ethernet peripheral (MAC, MTL and DMA). Default MAC, MTL and
  DMA configurations are applied.
## Channel Configuration:
- Configure and start each Rx and Tx Channel separately. The steps below apply to any Ethernet channel type
  (Rx or Tx).
- All HAL ETH Channel APIs take the channel identifier argument @ref ETH_Channel_Identifiers
- Configure and start the HAL ETH Tx/Rx Channel as follows:
  - Declare a hal_eth_tx_channel_config_t / hal_eth_rx_channel_config_t channel configuration structure, for example:
    @verbatim
    hal_eth_tx_channel_config_t / hal_eth_rx_channel_config_t ch_config;
    @endverbatim
  - Call HAL_ETH_GetConfigTxChannel()/HAL_ETH_GetConfigRxChannel() API to retrieve selected Tx/Rx Channel parameters.
  - Update the ETH Tx/Rx Channel configuration parameters in the ch_config structure.
    + Set the maximum number of application buffers to be held in the DMA FIFO.
    + Update the Tx/Rx DMA Channel Configuration.
    + Update the Tx/Rx MTL Queue Configuration.
    + Update the Tx/Rx FIFO Event Configuration.
  - Call HAL_ETH_SetConfigTxChannel()/HAL_ETH_SetConfigRxChannel() API to configure the selected Tx/Rx Channel.
  - Retrieve memory allocation requirements to allocate memory for descriptors and application buffers to be used for
    reception and/or transmission.
    + Declare a hal_eth_channel_alloc_needs_t channel allocation info structure, for example:
      @verbatim
      hal_eth_channel_alloc_needs_t  alloc_needs;
      @endverbatim
    + Call HAL_ETH_GetChannelAllocNeeds() API to retrieve selected channel allocation information.
    + Use the allocation information to start the selected channel. The information includes:
      - The minimum memory size in bytes required by the driver for the selected channel.
      - The minimum address alignment for memory to be used by the driver.
## Frame Reception:
Ethernet data reception is asynchronous, so call the following API to start the listening mode for each initialized
Rx Channel(s):
  - HAL_ETH_StartChannel():
    + This API starts the MAC and DMA reception process. Configure the interrupt management mode and arguments.
    + Provide memory buffers to transfer the received frame data.
    + The ETH Rx Allocate Callback `p_rx_allocate_cb` is called to allocate buffers for reception.
      @note Ensure buffer(s) respect memory allocation requirements (alignment) provided
            by HAL_ETH_GetChannelAllocNeeds() API call.
  - When data is received, the ETH Data Callback `p_data_cb` (or `HAL_ETH_DataCallback`) is invoked if the channel is
    configured in interrupt mode.
  - Call the HAL_ETH_ExecDataHandler() API to get the received data (in Thread execution mode).
  - The `p_rx_complete_cb` and `p_rx_allocate_cb` callbacks are called during `HAL_ETH_ExecDataHandler` execution to
    notify about a received frame and request memory for the next frame reception.
    @note Do not call any blocking service(s) while running in handler execution mode.
  - Call HAL_ETH_ExecDataHandler() API to retrieve received data at any time in the context of the application thread.
    @note Do not call HAL_ETH_ExecDataHandler() API in the Handler execution mode. This breaks driver behaviour.
    Implement a dedicated worker thread and trigger it to retrieve the received data (in Thread execution mode).
## Communication with an external PHY device:
  - HAL_ETH_MDIO_UpdateClockRange(): Update the MDIO clock range.
  - HAL_ETH_MDIO_SetOpAttributes(): Configure Ethernet MDIO command attributes.
  - HAL_ETH_MDIO_C22ReadData(): Read a register from an external PHY using Clause 22 method.
  - HAL_ETH_MDIO_C22WriteData(): Write data to an external PHY register using Clause 22 method.
  - HAL_ETH_MDIO_C45ReadData(): Read a register from an external PHY using Clause 45 method.
  - HAL_ETH_MDIO_C45WriteData(): Write data to an external PHY register using Clause 45 method.
  - HAL_ETH_MDIO_C45ReadDataRange(): Read a range of registers from an external PHY using Clause 45 method.
  - HAL_ETH_UpdateConfigLink(): Apply MAC link speed/duplex using hal_eth_link_config_t after link configuration
    change. It can result from auto-negotiation between PHYs, or from a manual or managed change of settings.
## Advanced Ethernet Configurations:
### Configure the Ethernet MAC after ETH peripheral configuration is done:
  - HAL_ETH_MAC_GetConfig(): Get MAC current configuration into hal_eth_mac_config_t.
  - HAL_ETH_MAC_SetConfig(): Set MAC configuration based on hal_eth_mac_config_t.
### Configure the Ethernet DMA after ETH peripheral configuration is done:
  - HAL_ETH_DMA_GetConfig(): Get DMA current configuration into hal_eth_dma_config_t.
  - HAL_ETH_DMA_SetConfig(): Set DMA configuration based on hal_eth_dma_config_t.
### Configure the Ethernet MTL after ETH peripheral configuration is done:
  - HAL_ETH_MTL_GetConfig(): Get MTL current configuration into hal_eth_mtl_config_t.
  - HAL_ETH_MTL_SetConfig(): Set MTL configuration based on hal_eth_mtl_config_t.
### Configure ARP offload module after ETH peripheral configuration is done:
  - HAL_ETH_EnableARPOffload(): Enable ARP offload.
  - HAL_ETH_DisableARPOffload(): Disable ARP offload.
  - HAL_ETH_IsEnabledARPOffload(): Check whether ARP offloading is enabled.
  - HAL_ETH_SetARPTargetIP(): Set the ARP Target IP address.
### Configure MAC power down module:
  - HAL_ETH_EnterPowerDownMode(): Enter the Power down mode.
  - HAL_ETH_ExitPowerDownMode(): Exit from the Power down mode.
  - HAL_ETH_SetRemoteWakeUpPcktFilter(): Set the Remote WakeUp filter.
### Configure Energy Efficient Ethernet module:
  - HAL_ETH_EnterLPIMode(): Enter the Low Power Idle (LPI) mode.
  - HAL_ETH_ExitLPIMode(): Exit the Low Power Idle (LPI) mode.

## Callback registration:
The ETH HAL driver supports two distinct sets of callbacks:

1. **Mandatory callbacks**
   Register these callbacks in the application.
   These callbacks are not delimited by the `USE_HAL_ETH_REGISTER_CALLBACKS` compilation flag and have no weak default
   implementations.

2. **Optional callbacks**
   These callbacks are delimited by the `USE_HAL_ETH_REGISTER_CALLBACKS` compilation flag and are optional.
   When this flag is enabled, the integration can override the default weak implementations by registering
   its own callbacks.

By default, after a call to `HAL_ETH_Init()` and while the state is `HAL_ETH_STATE_INIT`, all callbacks that provide
weak default implementations are mapped to their corresponding weak functions (for example `HAL_ETH_ErrorCallback()`,
`HAL_ETH_WakeUpCallback()`).

Register or unregister callbacks only when the driver is in `HAL_ETH_STATE_CONFIGURED` state.

If `USE_HAL_ETH_REGISTER_CALLBACKS` is set to `0` or not defined, the callback registration mechanism (for the callbacks
guarded by this compile switch) is disabled and these callbacks remain bound to their weak implementations.

> **Note:**
> The following channel-related callbacks do not have weak default implementations and their registration is
> therefore mandatory:
> - `HAL_ETH_RegisterChannelRxAllocateCallback()`
> - `HAL_ETH_RegisterChannelRxCptCallback()`
> - `HAL_ETH_RegisterChannelTxCptCallback()`
>
> Their implementation is not delimited by the `USE_HAL_ETH_REGISTER_CALLBACKS` compilation flag. Register appropriate
> callbacks for each used channel.

The HAL ETH driver provides the following callback registration functions:

- `HAL_ETH_RegisterChannelRxAllocateCallback()` : Register RX buffer allocation callback for a specific channel
  (mandatory, no weak default).
- `HAL_ETH_RegisterChannelRxCptCallback()`      : Register RX complete callback for a specific channel
  (mandatory, no weak default).
- `HAL_ETH_RegisterChannelTxCptCallback()`      : Register TX complete callback for a specific channel
  (mandatory, no weak default).
- `HAL_ETH_RegisterDataCallback()`              : Register data transfer/processing callback.
- `HAL_ETH_RegisterWKUPCallback()`              : Register Ethernet wake-up (power management) callback.
- `HAL_ETH_RegisterPMTCallback()`               : Register Power Management Trigger (PMT) callback.
- `HAL_ETH_RegisterEEECallback()`               : Register Energy Efficient Ethernet (EEE) callback.
- `HAL_ETH_RegisterErrorCallback()`             : Register error notification callback.
- `HAL_ETH_RegisterEventCallback()`             : Register generic Ethernet event callback.
- `HAL_ETH_RegisterCacheInvalidateCallback()`   : Register cache invalidate operation callback.
- `HAL_ETH_RegisterCacheFlushCallback()`        : Register cache flush operation callback.
- `HAL_ETH_RegisterChannelRxEventCallback()`    : Register generic RX event callback for a specific channel.
- `HAL_ETH_RegisterChannelTxEventCallback()`    : Register generic TX event callback for a specific channel.

## HAL ETH Driver State and Errors:

- Use HAL_ETH_GetState() function to return the global HAL ETH driver state.
- Use HAL_ETH_GetChannelState() function to return the state of a specific ETH channel.
- When enabled, use HAL_ETH_GetLastErrorCodes() to retrieve the last recorded ETH error codes.

If the compilation flag `USE_HAL_ETH_GET_LAST_ERRORS` is set to 1, the function
`HAL_ETH_GetLastErrorCodes()` is available and allows the application to read back the last error codes
recorded internally by the ETH driver.

If `USE_HAL_ETH_GET_LAST_ERRORS` is set to 0 or not defined, this function is not compiled and
the last error history feature is not available.
  */
/**
  * @}
  */

/** @defgroup ETH_Configuration_Table ETH Configuration Table
  * @{
# Configuration inside the ETH driver

Config defines                  | Description     | Default value   | Note
--------------------------------| --------------- | --------------- | ------------------------------------------------
PRODUCT                         | from IDE        |        NA       | The selected device (e.g. STM32C5XXxx)
USE_HAL_ETH_MODULE              | from hal_conf.h |        1        | Allows use of the HAL ETH module.
USE_ASSERT_DBG_PARAM            | from IDE        |      None       | Allows use of the assert check parameters.
USE_ASSERT_DBG_STATE            | from IDE        |      None       | Allows use of the assert check states.
USE_HAL_CHECK_PARAM             | from hal_conf.h |        0        | Allows use of the run-time checks parameters.
USE_HAL_CHECK_PROCESS_STATE     | from hal_conf.h |        0        | Enables atomic access to process state check.
USE_HAL_ETH_CLK_ENABLE_MODEL    | from hal_conf.h |HAL_CLK_ENABLE_NO| Enables gating of the peripheral clock.
USE_HAL_ETH_GET_LAST_ERRORS     | from hal_conf.h |        0        | Allows use of the error code mechanism.
USE_HAL_ETH_USER_DATA           | from hal_conf.h |        0        | Allows use of user data.
USE_HAL_ETH_ATOMIC_CHANNEL_LOCK | from hal_conf.h |        0        | Enables atomic access to channel resources.
USE_HAL_ETH_REGISTER_CALLBACKS  | from hal_conf.h |        0        | Enables the registration of callbacks.
USE_HAL_ETH_MAX_TX_CH_NB        | from hal_conf.h |     Defined     | User-defined number of Transmit Channels.
USE_HAL_ETH_MAX_RX_CH_NB        | from hal_conf.h |     Defined     | User-defined number of Receive Channels.
  */
/**
  * @}
  */

#if defined (USE_HAL_ETH_MODULE) && (USE_HAL_ETH_MODULE == 1U)
/* Private define ------------------------------------------------------------*/
/** @defgroup ETH_Private_Constants ETH Private Constants
  * @{
  */
#define ETH_MACQTXFCR_MASK              0xFFFF00F2U      /*!< ETH_MACQTXFCR Register Mask value */
#define ETH_GIANT_PKT_SIZE_LIMIT_BYTE    (1518U)                /*!< Rx Giant Packet received size limit */
#define ETH_CHANNEL_STATE_UNLOCKED       (0x00000000UL)         /*!< Channel is unlocked and available for access */
#define ETH_CHANNEL_STATE_LOCKED         (0x00000001U)          /*!< Channel is locked and being accessed */

#ifndef ETH_SWRESET_TIMEOUT
#define ETH_SWRESET_TIMEOUT_MS           (1000UL)               /*!< Timeout value for ETH software reset
                                                                     - unit: milliseconds. */
#endif /* ETH_SWRESET_TIMEOUT */

#ifndef ETH_TX_Q_FLUSH_TIMEOUT
#define ETH_TX_Q_FLUSH_TIMEOUT           (1000UL)               /*!< Timeout value for Tx queue flush operation
                                                                     - unit: milliseconds. */
#endif /* ETH_TX_Q_FLUSH_TIMEOUT */

#ifndef ETH_TX_DMA_STOP_TIMEOUT
#define ETH_TX_DMA_STOP_TIMEOUT          (1000UL)               /*!< Timeout value for Tx DMA stop operation
                                                                     - unit: milliseconds. */
#endif /* ETH_TX_DMA_STOP_TIMEOUT */

#ifndef ETH_RX_DMA_STOP_TIMEOUT
#define ETH_RX_DMA_STOP_TIMEOUT          (1000UL)               /*!< Timeout value for Rx DMA stop operation
                                                                     - unit: milliseconds. */
#endif /* ETH_RX_DMA_STOP_TIMEOUT */

#ifndef ETH_MDIO_BUS_TIMEOUT
#define ETH_MDIO_BUS_TIMEOUT             (1000UL)               /*!< Timeout value for MDIO bus operations
                                                                     - unit: milliseconds. */
#endif /* ETH_MDIO_BUS_TIMEOUT */

#ifndef ETH_DMA_RX_BUFFER_SIZE_BYTE
#define ETH_DMA_RX_BUFFER_SIZE_BYTE      (1520UL)               /*!< ETH receive buffer size in bytes. */
#endif /* ETH_DMA_RX_BUFFER_SIZE_BYTE */

/** Minimum MDC clock frequency: 1 MHz */
#define ETH_MDC_CLK_MIN_HZ                   (1000000UL)
/** Maximum MDC clock frequency: 2.5 MHz */
#define ETH_MDC_CLK_MAX_HZ                   (2500000UL)

/*!< HAL ETH MAC MDC Clock Range selection defines */
#define ETH_MDIOAR_CSR_CR_SEL_0          (0x00000000UL)        /*!< MDC Clock Range LOW SPEED 0 */
#define ETH_MDIOAR_CSR_CR_SEL_1          (0x00000100UL)        /*!< MDC Clock Range LOW SPEED 1 */
#define ETH_MDIOAR_CSR_CR_SEL_2          (0x00000200UL)        /*!< MDC Clock Range LOW SPEED 2 */
#define ETH_MDIOAR_CSR_CR_SEL_3          (0x00000300UL)        /*!< MDC Clock Range LOW SPEED 3 */
#define ETH_MDIOAR_CSR_CR_SEL_4          (0x00000400UL)        /*!< MDC Clock Range LOW SPEED 4 */
#define ETH_MDIOAR_CSR_CR_SEL_5          (0x00000500UL)        /*!< MDC Clock Range LOW SPEED 5 */
#define ETH_MDIOAR_CSR_CR_SEL_6          (0x00000600UL)        /*!< MDC Clock Range LOW SPEED 6 */
#define ETH_MDIOAR_CSR_CR_SEL_7          (0x00000700UL)        /*!< MDC Clock Range LOW SPEED 7 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_0     (0x00000800UL)        /*!< MDC Clock Range HIGH SPEED 0 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_1     (0x00000900UL)        /*!< MDC Clock Range HIGH SPEED 1 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_2     (0x00000A00UL)        /*!< MDC Clock Range HIGH SPEED 2 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_3     (0x00000B00UL)        /*!< MDC Clock Range HIGH SPEED 3 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_4     (0x00000C00UL)        /*!< MDC Clock Range HIGH SPEED 4 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_5     (0x00000D00UL)        /*!< MDC Clock Range HIGH SPEED 5 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_6     (0x00000E00UL)        /*!< MDC Clock Range HIGH SPEED 6 */
#define ETH_MDIOAR_CSR_CR_FAST_SEL_7    (ETH_MACMDIOAR_CR)    /*!< MDC Clock Range HIGH SPEED 7 */

/*!< HAL ETH MAC MDC ETH Clock divider defines */
#define ETH_MDC_CLK_DIV_42                (42UL)         /*!< MDC Clock Range DIV 42   */
#define ETH_MDC_CLK_DIV_62                (62UL)         /*!< MDC Clock Range DIV 62   */
#define ETH_MDC_CLK_DIV_16                (16UL)         /*!< MDC Clock Range DIV 16   */
#define ETH_MDC_CLK_DIV_26                (26UL)         /*!< MDC Clock Range DIV 26   */
#define ETH_MDC_CLK_DIV_102               (102UL)        /*!< MDC Clock Range DIV 102   */
#define ETH_MDC_CLK_DIV_124               (124UL)        /*!< MDC Clock Range DIV 124   */
#define ETH_MDC_CLK_DIV_204               (204UL)        /*!< MDC Clock Range DIV 204   */
#define ETH_MDC_CLK_DIV_324               (324UL)        /*!< MDC Clock Range DIV 324   */

#define ETH_GOC_OPERATION_WRITE           (0x00000004UL)        /*!< GOC operation: write transaction (used to initiate
                                                                     a write access to the targeted PHY register) */
#define ETH_GOC_OPERATION_PRIAC45         (0x00000008UL)        /*!< GOC operation: post-read with address increment
                                                                     (Clause 45 MDIO post-read with auto-incremented
                                                                     address) */
#define ETH_GOC_OPERATION_READ            (0x0000000CUL)        /*!< GOC operation: read transaction (used to initiate
                                                                     a read access from the targeted PHY register) */

/** ETH_MACCR Register Mask value */
#define ETH_MACCR_MASK                    (ETH_MACCR_DM | ETH_MACCR_FES                              \
                                           | ETH_MACCR_LM | ETH_MACCR_SARC | ETH_MACCR_IPG           \
                                           | ETH_MACCR_BL | ETH_MACCR_PRELEN | ETH_MACCR_GPSLCE      \
                                           | ETH_MACCR_S2KP | ETH_MACCR_CST | ETH_MACCR_ACS          \
                                           | ETH_MACCR_JD | ETH_MACCR_ECRSFD | ETH_MACCR_DCRS        \
                                           | ETH_MACCR_DR | ETH_MACCR_WD | ETH_MACCR_JE              \
                                           | ETH_MACCR_IPC | ETH_MACCR_DO | ETH_MACCR_DC)

/** ETH_MACECR Register Mask value */
#define ETH_MACECR_MASK                  (ETH_MACECR_GPSL | ETH_MACECR_DCRCC | ETH_MACECR_SPEN      \
                                          | ETH_MACECR_USP | ETH_MACECR_EIPGEN | ETH_MACECR_EIPG)
/** ETH_MACWJBTR Register Mask value */
#define ETH_MACWJBTR_MASK                (ETH_MACWJBTR_PWE | ETH_MACWJBTR_WTO)
/** ETH_MACRXFCR Register Mask value */
#define ETH_MACRXFCR_MASK                (ETH_MACRXFCR_UP | ETH_MACRXFCR_RFE)

/** ETH Error Mask */
#define ETH_ERROR_DMA_MASK                (ETH_DMACSR_FBE | ETH_DMACSR_CDE  \
                                           | ETH_DMACSR_REB | ETH_DMACSR_TEB)

/** ETH_MTLRXQOMR Register Mask value */
#define ETH_MTLRXQXOMR_MASK               (ETH_MTLRXQOMR_DIS_TCP_EF \
                                           | ETH_MTLRXQOMR_FEP | ETH_MTLRXQOMR_FUP \
                                           | ETH_MTLRXQOMR_RSF | ETH_MTLRXQOMR_RTC)
/** ETH_MTLTXQOMR Register Mask value */
#define ETH_MTLTXQXOMR_MASK               (ETH_MTLTXQOMR_TSF | ETH_MTLTXQOMR_TTC)
/** ETH_MTLOMR Register Mask value */
#define ETH_MTLOMR_MASK                   (ETH_MTLOMR_DTXSTS)
/** ETH_DMAMR Register Mask value */
#define ETH_DMAMR_MASK                    (ETH_DMAMR_TXPR)
/** ETH_DMASBMR Register Mask value */
#define ETH_DMASBMR_MASK                  (ETH_DMASBMR_AAL | ETH_DMASBMR_FB | ETH_DMASBMR_MB | ETH_DMASBMR_RB)
/** ETH RX DMA Channel Event Mask */
#define ETH_RX_DMA_CH_EVENT_MASK          (ETH_DMACSR_RBU | ETH_DMACSR_RWT)
/** ETH RX MTL Channel Event Mask */
#define ETH_RX_MTL_CH_EVENT_MASK          (ETH_MTLQICSR_RXOVFIS)
/** ETH TX DMA Channel Event Mask */
#define ETH_TX_DMA_CH_EVENT_MASK          (ETH_DMACSR_TBU)
/** ETH TX MTL Channel Event Mask */
#define ETH_TX_MTL_CH_EVENT_MASK          (ETH_MTLQICSR_TXUNFIS)

/** ETH MAC event mask */
#define ETH_MAC_EVENT_MASK                (ETH_MACRXTXSR_RWT | ETH_MACRXTXSR_EXCOL | ETH_MACRXTXSR_LCOL \
                                           | ETH_MACRXTXSR_EXDEF | ETH_MACRXTXSR_LCARR | ETH_MACRXTXSR_NCARR \
                                           | ETH_MACRXTXSR_TJT)

/** PMT control bits mask: RWKPFE | GLBLUCAST | RWKPKTEN | MGKPKTEN */
#define ETH_PMT_CTRL_MASK               (ETH_MACPCSR_RWKPFE | ETH_MACPCSR_GLBLUCAST   \
                                         | ETH_MACPCSR_RWKPKTEN | ETH_MACPCSR_MGKPKTEN)
/** MAC link configuration mask: speed and duplex */
#define ETH_MAC_LINK_CONFIG_MASK        (ETH_MACCR_FES | ETH_MACCR_DM)
/** LPI transmit clock control mask: LPITCSE | LPITXA */
#define ETH_LPI_TX_CLK_MASK              (ETH_MACLCSR_LPITCSE | ETH_MACLCSR_LPITXA)
/** PMT event mask: Magic Packet received | Remote Wakeup received */
#define ETH_PMT_EVENT_MASK               (ETH_MACPCSR_MGKPRCVD | ETH_MACPCSR_RWKPRCVD)
/** LPI event mask: Tx/Rx LPI enable/exit/status bits */
#define ETH_LPI_EVENT_MASK               (ETH_MACLCSR_TLPIEN | ETH_MACLCSR_TLPIEX \
                                          | ETH_MACLCSR_RLPIEN | ETH_MACLCSR_RLPIEX \
                                          | ETH_MACLCSR_TLPIST | ETH_MACLCSR_RLPIST)
#define ETH_RWK_CMD_MASK                 (0x0FUL)          /*!< RWK command field mask (4 bits) */
#define ETH_RWK_OFFSET_MASK              (0xFFUL)          /*!< RWK offset field mask (8 bits) */
#define ETH_RWK_CRC16_MASK               (0xFFFFUL)        /*!< RWK CRC16 field mask (16 bits) */

#define ETH_MIN_DESC_CNT                 (4U)              /*!< ETH Minimum requested desc number */
#define ETH_RX_CHANNEL_ID_POS            (16U)             /*!< ETH the Bit position of RX channel */

#define ETH_TPS_FIELD_WIDTH_BITS         (8U)              /*!< TX DMA process state field: width in bits and
                                                                channel mapping helpers */
#define ETH_TX_DMA_CH_STATE_MAX_IDX      (2U)              /*!< Channels 0..2 in ETH_DMADSR */
#define ETH_RPS_FIELD_WIDTH_BITS         (8U)              /*!< RX DMA process state field: width in bits
                                                                and channel mapping helpers */


#define ETH_DMA_TX_DESC_RF_IOC           0x80000000UL      /*!< TDES2 RF : Interrupt on Completion */
#define ETH_DMA_TX_DESC_RF_B1L           0x00003FFFUL      /*!< TDES2 RF : Buffer 1 Length MASK */
#define ETH_DMA_TX_DESC_RF_VTIR          0x0000C000UL      /*!< TDES2 RF : VLAN Tag Insertion or Replacement mask */

#define ETH_DMA_TX_DESC_RF_OWN           0x80000000UL      /*!< TDES3 RF : descriptor is owned by DMA engine */
#define ETH_DMA_TX_DESC_RF_FD            0x20000000UL      /*!< TDES3 RF : First Descriptor */
#define ETH_DMA_TX_DESC_RF_LD            0x10000000UL      /*!< TDES3 RF : Last Descriptor */
#define ETH_DMA_TX_DESC_RF_CPC           0x0C000000UL      /*!< TDES3 RF : CRC Pad Control mask  */
#define ETH_DMA_TX_DESC_RF_CIC           0x00030000UL      /*!< TDES3 RF : Checksum Insertion Control: 4 cases */
#define ETH_DMA_TX_DESC_RF_SAIC          0x03800000UL      /*!< TDES3 RF : SA Insertion Control mask */

#define ETH_DMA_RX_DESC_WBF_OWN          0x80000000UL      /*!< RDES3 WBF : descriptor is owned by DMA engine */
#define ETH_DMA_RX_DESC_WBF_CTXT         0x40000000UL      /*!< RDES3 WBF : Receive Context Descriptor */
#define ETH_DMA_RX_DESC_WBF_PL           0x00007FFFUL      /*!< RDES3 WBF : Packet Length */

#define ETH_DMA_RX_DESC_RF_OWN           0x80000000UL      /*!< RDES3 RF : descriptor is owned by DMA engine */
#define ETH_DMA_RX_DESC_RF_IOC           0x40000000U       /*!< RDES3 RF : Interrupt Enabled on Completion */
#define ETH_DMA_RX_DESC_RF_BUF1V         0x01000000UL      /*!< RDES3 RF : Buffer 1 Address Valid */
#define ETH_DMA_TX_DESC_CTXT_OWN         0x80000000UL      /*!< RDES3 RF : descriptor is owned by DMA engine */
#define ETH_DMA_TX_DESC_CTXT_CTXT        0x40000000UL      /*!< RDES3 RF : Context Type */

#define ETH_DMA_TX_DESC_CTXT_IVTIR       0x000C0000UL      /*!< TDES3 CTXT : Inner VLAN Tag Insert or Replace Mask */
#define ETH_DMA_TX_DESC_CTXT_IVLTV       0x00020000UL      /*!< TDES3 CTXT : Inner VLAN Tag Valid */
#define ETH_DMA_TX_DESC_CTXT_VLTV        0x00010000UL      /*!< TDES3 CTXT : VLAN Tag Valid */
#define ETH_DMA_TX_DESC_CTXT_VT          0x0000FFFFUL      /*!< TDES3 CTXT : VLAN Tag */
#define ETH_DMA_TX_DESC_CTXT_IVT         0xFFFF0000UL      /*!< TDES2 CTXT : Inner VLAN Tag Mask */

#define ETH_MACMDIOAR_BUSY               ETH_MACMDIOAR_MB  /*!< MII Busy.
                                                                The application sets this bit to instruct the SMA to
                                                                initiate a Read or Write access to the MDIOS. The MAC
                                                                clears this bit after the MDIO frame transfer is
                                                                completed. */
#define ETH_MACMDIODR_DATA               ETH_MACMDIODR_MD  /*!< MII Data */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup ETH_Private_Macros ETH Private Macros
  * @{
  */
/**
  * @brief  Retrieve ETH peripheral instance from HAL handle.
  * @param  heth  Pointer to a hal_eth_handle_t structure
  * @retval Pointer to the ETH register base (ETH_TypeDef *)
  */
#define ETH_GET_INSTANCE(heth) ((ETH_TypeDef *)((uint32_t)(heth)->instance))

/**
  * @brief  Compute and return pointer to the ETH DMA channel registers for a channel index.
  * @param  heth   Pointer to a hal_eth_handle_t structure
  * @param  index  Channel index (zero-based)
  * @retval Pointer to the ETH DMA channel registers (ETH_DMA_Channel_TypeDef *)
  */
#define ETH_GET_DMA_CHANNEL(heth, index) ((ETH_DMA_Channel_TypeDef *)(((uint32_t)(heth)->instance) + \
                                                                      ETH_DMA_CHANNEL_UNIT_OFFSET +\
                                                                      (ETH_DMA_CHANNEL_UNIT_SIZE * (uint32_t)(index))))

/**
  * @brief  Compute and return pointer to the ETH MTL queue registers for a queue index.
  * @param  heth   Pointer to a hal_eth_handle_t structure
  * @param  index  MTL queue index (zero-based)
  * @retval Pointer to the ETH MTL queue registers (ETH_MTL_Queue_TypeDef *)
  */
#define ETH_GET_MTL_QUEUE(heth, index) ((ETH_MTL_Queue_TypeDef *)(((uint32_t)(heth)->instance) + \
                                                                  ETH_MTL_QUEUE_UNIT_OFFSET\
                                                                  + (ETH_MTL_QUEUE_UNIT_SIZE * (uint32_t)(index))))
/**
  * @brief  Gets the ETHERNET DMA TX Instance for selected Channel.
  * @param  heth    ETH Handle
  * @param  channel specifies the ETH Channel Index. @ref ETH_Channel_Identifiers
  * @retval The ETH DMA Instance pointer (ETH_DMA_Channel_TypeDef *).
  */
#define ETH_DMA_GET_TX_INSTANCE(heth,channel) \
  (((ETH_DMA_Channel_TypeDef *)((heth)->tx_channels[channel].p_dma_instance)))

/**
  * @brief  Gets the ETHERNET DMA RX Instance for selected Channel.
  * @param  heth    ETH Handle
  * @param  channel specifies the ETH Channel Index. @ref ETH_Channel_Identifiers
  * @retval The ETH DMA Instance pointer (ETH_DMA_Channel_TypeDef *).
  */
#define ETH_DMA_GET_RX_INSTANCE(heth,channel) \
  (((ETH_DMA_Channel_TypeDef *)((heth)->rx_channels[channel].p_dma_instance)))

/**
  * @brief  Gets the ETHERNET TX Queue MTL Instance for selected Channel.
  * @param  heth   ETH Handle
  * @param  queue  specifies the MTL Queue Index. @ref ETH_Queue_Indexes
  * @retval The ETH MTL Instance pointer (ETH_MTL_Queue_TypeDef *).
  */
#define ETH_MTL_GET_TX_INSTANCE(heth,queue) \
  (((ETH_MTL_Queue_TypeDef *)((heth)->tx_channels[queue].p_mtl_instance)))

/**
  * @brief  Gets the ETHERNET RX Queue MTL Instance for selected Channel.
  * @param  heth   ETH Handle
  * @param  queue  specifies the MTL Queue Index. @ref ETH_Queue_Indexes
  * @retval The ETH MTL Instance pointer (ETH_MTL_Queue_TypeDef *).
  */
#define ETH_MTL_GET_RX_INSTANCE(heth,queue) \
  (((ETH_MTL_Queue_TypeDef *)((heth)->rx_channels[queue].p_mtl_instance)))

/**
  * @brief  Check for a Channel Identifier is valid or not.
  * @param  index : Channel identifier to check
  * @retval True if valid. False otherwise
  */
#define IS_ETH_CHANNEL_INDEX(index) ((IS_ETH_CHANNEL_TX_INDEX(index))          \
                                     || (IS_ETH_CHANNEL_RX_INDEX(index)))

/**
  * @brief  Check for TX Channel Identifier is valid or not.
  * @param  index : Channel identifier to check
  * @retval True if valid. False otherwise
  */
#define IS_ETH_CHANNEL_TX_INDEX(index) (((index) == HAL_ETH_TX_CHANNEL_0) && (USE_HAL_ETH_MAX_TX_CH_NB >= 1U))

/**
  * @brief  Check for RX Channel Identifier is valid or not.
  * @param  index : Channel identifier to check
  * @retval True if valid. False otherwise
  */
#define IS_ETH_CHANNEL_RX_INDEX(index)  (((index) == HAL_ETH_RX_CHANNEL_0) && (USE_HAL_ETH_MAX_RX_CH_NB >= 1U))

/** @brief Validates input channel mask (TX/RX). */
#define IS_ETH_CHANNEL_MASK(mask) (((mask) & ~(HAL_ETH_TX_CHANNEL_ALL | HAL_ETH_RX_CHANNEL_ALL)) == 0U)

/** @brief Validates Remote Wake-Up byte mask: bit 31 must be zero. */
#define IS_ETH_RWK_BYTE_MASK(mask) (((mask) & 0x80000000UL) == 0UL)

/** @brief Validates MDIO command attributes: only allow defined HAL MDIO flags/NTC values. */
#define IS_ETH_MDIO_CMD_ATTR(attr) \
  ((((attr)) & ~(ETH_MACMDIOAR_PSE | ETH_MACMDIOAR_BTB | ETH_MACMDIOAR_NTC)) == 0U)

/** @brief Validates media interface selection. */
#define IS_ETH_MEDIA_INTERFACE(media_interface) (((media_interface) == HAL_ETH_MEDIA_IF_MII) \
                                                 || ((media_interface) == HAL_ETH_MEDIA_IF_RMII))

/** @brief Validates MAC speed value. */
#define IS_ETH_MAC_SPEED(speed) (((speed) == HAL_ETH_MAC_SPEED_10M) || ((speed) == HAL_ETH_MAC_SPEED_100M))

/** @brief Validates MAC duplex mode. */
#define IS_ETH_MAC_DUPLEX_MODE(duplex) (((duplex) == HAL_ETH_MAC_FULL_DUPLEX_MODE)                                   \
                                        || ((duplex) == HAL_ETH_MAC_HALF_DUPLEX_MODE))
/** @brief Validates MAC loopback control. */
#define IS_ETH_MAC_LOOPBACK_CTRL(loopback) (((loopback) == HAL_ETH_MAC_LOOPBACK_DISABLE)                             \
                                            || ((loopback) == HAL_ETH_MAC_LOOPBACK_ENABLE))
/** @brief Validates MAC source address control. */
#define IS_ETH_MAC_SRC_ADDR_CTRL(srcaddr) (((srcaddr) == HAL_ETH_MAC_SA_DISABLE)                               \
                                           || ((srcaddr) == HAL_ETH_MAC_SA_MAC0_INS)                       \
                                           || ((srcaddr) == HAL_ETH_MAC_SA_MAC1_INS)                       \
                                           || ((srcaddr) == HAL_ETH_MAC_SA_MAC0_REP)                      \
                                           || ((srcaddr) == HAL_ETH_MAC_SA_MAC1_REP))
/** @brief Validates MAC inter-packet gap. */
#define IS_ETH_MAC_INTER_PKT_GAP(ipg) (((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_96_BIT)                                   \
                                       || ((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_88_BIT)                                \
                                       || ((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_80_BIT)                                \
                                       || ((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_72_BIT)                                \
                                       || ((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_64_BIT)                                \
                                       || ((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_56_BIT)                                \
                                       || ((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_48_BIT)                                \
                                       || ((ipg) == HAL_ETH_MAC_INTER_PKT_GAP_40_BIT))
/** @brief Validates MAC back-off limit. */
#define IS_ETH_MAC_BACK_OFF_LIMIT(backoff) (((backoff) == HAL_ETH_MAC_BACK_OFF_LIMIT_10)                             \
                                            || ((backoff) == HAL_ETH_MAC_BACK_OFF_LIMIT_8)                           \
                                            || ((backoff) == HAL_ETH_MAC_BACK_OFF_LIMIT_4)                           \
                                            || ((backoff) == HAL_ETH_MAC_BACK_OFF_LIMIT_1))
/** @brief Validates MAC preamble length. */
#define IS_ETH_MAC_PREAMBLE_LENGTH(preamble) (((preamble) == HAL_ETH_MAC_PREAMBLE_LENGTH_7)                          \
                                              || ((preamble) == HAL_ETH_MAC_PREAMBLE_LENGTH_5)                       \
                                              || ((preamble) == HAL_ETH_MAC_PREAMBLE_LENGTH_3))
/** @brief Validates MAC giant packet size limit control. */
#define IS_ETH_MAC_GPKT_SZ_LIMIT_CTRL(giantlimit) (((giantlimit) == HAL_ETH_MAC_GPKT_SZ_LIMIT_DISABLE)               \
                                                   || ((giantlimit) == HAL_ETH_MAC_GPKT_SZ_LIMIT_ENABLE))
/** @brief Validates MAC 2K packet length control. */
#define IS_ETH_MAC_2K_PKT_LEN_CTRL(pkt2k) (((pkt2k) == HAL_ETH_MAC_2K_PKT_LEN_DISABLE)                               \
                                           || ((pkt2k) == HAL_ETH_MAC_2K_PKT_LEN_ENABLE))
/** @brief Validates MAC CRC strip control. */
#define IS_ETH_MAC_CRC_STRIP_PKT_CTRL(crcstrip) (((crcstrip) == HAL_ETH_MAC_CRC_STRIP_PKT_DISABLE)                   \
                                                 || ((crcstrip) == HAL_ETH_MAC_CRC_STRIP_PKT_ENABLE))
/** @brief Validates MAC auto pad CRC/s control. */
#define IS_ETH_MAC_AUTO_PAD_CRC_S_CTRL(autopadcrc) (((autopadcrc) == HAL_ETH_MAC_AUTO_PAD_CRC_S_DISABLE)             \
                                                    || ((autopadcrc) == HAL_ETH_MAC_AUTO_PAD_CRC_S_ENABLE))
/** @brief Validates MAC TX jabber timer control. */
#define IS_ETH_MAC_TX_JABBER_TIM_CTRL(jabber) (((jabber) == HAL_ETH_MAC_TX_JABBER_TIM_DISABLE)                       \
                                               || ((jabber) == HAL_ETH_MAC_TX_JABBER_TIM_ENABLE))
/** @brief Validates MAC carrier-sense before transmit control. */
#define IS_ETH_MAC_CS_BEFORE_TR_CTRL(csbefore) (((csbefore) == HAL_ETH_MAC_CS_BEFORE_TR_DISABLE)                     \
                                                || ((csbefore) == HAL_ETH_MAC_CS_BEFORE_TR_ENABLE))
/** @brief Validates MAC carrier-sense during transmit control. */
#define IS_ETH_MAC_CS_DURING_TR_CTRL(csduring) (((csduring) == HAL_ETH_MAC_CS_DURING_TR_DISABLE)                     \
                                                || ((csduring) == HAL_ETH_MAC_CS_DURING_TR_ENABLE))
/** @brief Validates MAC retry transmit control. */
#define IS_ETH_MAC_RETRY_TR_CTRL(retry) (((retry) == HAL_ETH_MAC_RETRY_TR_DISABLE)                                   \
                                         || ((retry) == HAL_ETH_MAC_RETRY_TR_ENABLE))
/** @brief Validates MAC RX watchdog timer control. */
#define IS_ETH_MAC_RX_WD_TIM_CTRL(rxwatchdog) (((rxwatchdog) == HAL_ETH_MAC_RX_WD_TIM_DISABLE)                       \
                                               || ((rxwatchdog) == HAL_ETH_MAC_RX_WD_TIM_ENABLE))
/** @brief Validates MAC RX jumbo packet control. */
#define IS_ETH_MAC_RX_JUMBO_PKT_CTRL(jumbo) (((jumbo) == HAL_ETH_MAC_RX_JUMBO_PKT_DISABLE)                           \
                                             || ((jumbo) == HAL_ETH_MAC_RX_JUMBO_PKT_ENABLE))
/** @brief Validates MAC RX checksum control. */
#define IS_ETH_MAC_RX_CSUM_PKT_CTRL(rxcsum) (((rxcsum) == HAL_ETH_MAC_RX_CSUM_PKT_DISABLE)                           \
                                             || ((rxcsum) == HAL_ETH_MAC_RX_CSUM_PKT_ENABLE))
/** @brief Validates MAC RX receive own control. */
#define IS_ETH_MAC_RX_RECEIVE_OWN_CTRL(rxown) (((rxown) == HAL_ETH_MAC_RX_RECEIVE_OWN_DISABLE)                       \
                                               || ((rxown) == HAL_ETH_MAC_RX_RECEIVE_OWN_ENABLE))
/** @brief Validates MAC RX CRC packet check control. */
#define IS_ETH_MAC_RX_CRC_PKT_CHK_CTRL(rxcrc) (((rxcrc) == HAL_ETH_MAC_RX_CRC_PKT_CHK_DISABLE)                       \
                                               || ((rxcrc) == HAL_ETH_MAC_RX_CRC_PKT_CHK_ENABLE))
/** @brief Validates MAC deferral check control. */
#define IS_ETH_MAC_DEFERRAL_CHECK_CTRL(deferral) (((deferral) == HAL_ETH_MAC_DEFERRAL_CHECK_DISABLE)                 \
                                                  || ((deferral) == HAL_ETH_MAC_DEFERRAL_CHECK_ENABLE))
/** @brief Validates MAC unicast slow protocol control. */
#define IS_ETH_MAC_UC_SLOW_PROTO_CTRL(ucslow) (((ucslow) == HAL_ETH_MAC_UC_SLOW_PROTO_DISABLE)                       \
                                               || ((ucslow) == HAL_ETH_MAC_UC_SLOW_PROTO_ENABLE))
/** @brief Validates MAC slow protocol control. */
#define IS_ETH_MAC_SLOW_PROTO_CTRL(slowproto) (((slowproto) == HAL_ETH_MAC_SLOW_PROTO_DISABLE)                       \
                                               || ((slowproto) == HAL_ETH_MAC_SLOW_PROTO_ENABLE))
/** @brief Validates MAC extended inter-packet gap control. */
#define IS_ETH_MAC_EX_INT_PKT_GAP_CTRL(extipg) (((extipg) == HAL_ETH_MAC_E_INTER_PKT_GAP_DISABLE)                    \
                                                || ((extipg) == HAL_ETH_MAC_E_INTER_PKT_GAP_ENABLE))
/** @brief Validates MAC programmable watchdog control. */
#define IS_ETH_MAC_PROG_WD_CTRL(progwd) (((progwd) == HAL_ETH_MAC_PROG_WD_DISABLE)                                   \
                                         || ((progwd) == HAL_ETH_MAC_PROG_WD_ENABLE))
/** @brief Validates MAC zero-quanta pause control. */
#define IS_ETH_MAC_ZERO_Q_PAUSE_CTRL(zeroquanta) (((zeroquanta) == HAL_ETH_MAC_ZERO_Q_PAUSE_DISABLE)                 \
                                                  || ((zeroquanta) == HAL_ETH_MAC_ZERO_Q_PAUSE_ENABLE))
/** @brief Validates MAC transmit flow control. */
#define IS_ETH_MAC_TR_FLOW_CTRL(txflow) (((txflow) == HAL_ETH_MAC_TR_FLOW_CTRL_DISABLE)                              \
                                         || ((txflow) == HAL_ETH_MAC_TR_FLOW_CTRL_ENABLE))
/** @brief Validates MAC unicast pause packet control. */
#define IS_ETH_MAC_UC_PAUSE_PKT_CTRL(ucpause) (((ucpause) == HAL_ETH_MAC_UC_PAUSE_PKT_DISABLE)                       \
                                               || ((ucpause) == HAL_ETH_MAC_UC_PAUSE_PKT_ENABLE))
/** @brief Validates MAC receive flow control. */
#define IS_ETH_MAC_RECEIVE_FLOW_CTRL(rxflow) (((rxflow) == HAL_ETH_MAC_RECEIVE_FLOW_DISABLE)                         \
                                              || ((rxflow) == HAL_ETH_MAC_RECEIVE_FLOW_ENABLE))
/** @brief Validates MAC pause low threshold. */
#define IS_ETH_MAC_PAUSE_LOW_THR(pausethr) ( ((pausethr) == HAL_ETH_MAC_PLT_MINUS_4_SLOT_TIME)                        \
                                             || ((pausethr) == HAL_ETH_MAC_PLT_MINUS_28_SLOT_TIME)                   \
                                             || ((pausethr) == HAL_ETH_MAC_PLT_MINUS_36_SLOT_TIME)                   \
                                             || ((pausethr) == HAL_ETH_MAC_PLT_MINUS_144_SLOT_TIME)                  \
                                             || ((pausethr) == HAL_ETH_MAC_PLT_MINUS_256_SLOT_TIME)                  \
                                             || ((pausethr) == HAL_ETH_MAC_PLT_MINUS_512_SLOT_TIME) )

/** @brief Validates MTL TX forward status control. */
#define IS_ETH_MTL_TX_FWD_STATUS_CTRL(txfwd)   ( ((txfwd) == HAL_ETH_MTL_TX_FWD_STATUS_DISABLE)                     \
                                                 || ((txfwd) == HAL_ETH_MTL_TX_FWD_STATUS_ENABLE) )
/** @brief Validates MAC giant packet size limit value. */
#define IS_ETH_MAC_GIANT_PKT_SIZE_LIMIT(giantsize) (((giantsize) >= ETH_GIANT_PKT_SIZE_LIMIT_BYTE) \
                                                    && ((giantsize) <= 0x00003FFFUL))
/** @brief Validates MAC extended inter-packet gap value. */
#define IS_ETH_MAC_EXT_INTER_PKT_GAP(extipgval)    (((extipgval) <= 0x000000FFUL))
/** @brief Validates MAC RX watchdog timeout value (bytes). */
#define IS_ETH_MAC_RX_WD_TIMEOUT_BYTE(rxwdtimeout)    (((rxwdtimeout) <= HAL_ETH_MAC_RX_WDT_16KB))
/** @brief Validates MAC TX pause time value. */
#define IS_ETH_MAC_TX_PAUSE_TIME(pausetime)         (((pausetime) <= 0x0000FFFFUL))

/** @brief Validates DMA address aligned beats configuration. */
#define IS_ETH_DMA_ADDR_ALIGNED_BEATS(alignedbeats) (((alignedbeats) == HAL_ETH_DMA_ADDR_ALIGN_DISABLE) \
                                                     || ((alignedbeats) == HAL_ETH_DMA_ADDR_ALIGN_ENABLE))
/** @brief Validates DMA burst length mode. */
#define IS_ETH_DMA_BURST_LEN_MODE(burstmode) (((burstmode) == HAL_ETH_DMA_BURST_LEN_FIXED) \
                                              || ((burstmode) == HAL_ETH_DMA_BURST_LEN_MAX_ALLOWED))

/** @brief Validates DMA mixed burst control. */
#define IS_ETH_DMA_MIXED_BURST_CTRL(mixedburst) (((mixedburst) == HAL_ETH_DMA_MIXED_BURST_MODE_DISABLED) \
                                                 || ((mixedburst) == HAL_ETH_DMA_MIXED_BURST_MODE_ENABLED))

/** @brief Validates DMA rebuild increment burst control. */
#define IS_ETH_DMA_REBUILD_INC_CTRL(rebuildinc) (((rebuildinc) == HAL_ETH_DMA_REBUILD_INC_BURST_DISABLED) \
                                                 || ((rebuildinc) == HAL_ETH_DMA_REBUILD_INC_BURST_ENABLED))
/** @brief Validates DMA transfer priority control. */
#define IS_ETH_DMA_TR_PRIO_CTRL(trprio) (((trprio) == HAL_ETH_DMA_TR_PRIO_DISABLE) \
                                         || ((trprio) == HAL_ETH_DMA_TR_PRIO_ENABLE))
/** @brief Validates DMA Tx PBL x8 mode. */
#define IS_ETH_DMA_TX_PBL_X8_MODE(pblx8mode) ( ((pblx8mode) == HAL_ETH_DMA_TX_PBL_X8_DISABLE)                      \
                                               || ((pblx8mode) == HAL_ETH_DMA_TX_PBL_X8_ENABLE) )
/** @brief Validates DMA Tx burst length. */
#define IS_ETH_DMA_TX_BURST_LENGTH(txburst)  ( ((txburst) == HAL_ETH_DMA_TX_BLEN_1_BEAT)                           \
                                               || ((txburst) == HAL_ETH_DMA_TX_BLEN_2_BEAT)                        \
                                               || ((txburst) == HAL_ETH_DMA_TX_BLEN_4_BEAT)                        \
                                               || ((txburst) == HAL_ETH_DMA_TX_BLEN_8_BEAT)                        \
                                               || ((txburst) == HAL_ETH_DMA_TX_BLEN_16_BEAT)                       \
                                               || ((txburst) == HAL_ETH_DMA_TX_BLEN_32_BEAT) )
/** @brief Validates DMA Tx second packet operation control. */
#define IS_ETH_DMA_TX_SEC_PKT_OP_CTRL(secpktop) ( ((secpktop) == HAL_ETH_DMA_TX_SEC_PKT_OP_DISABLE)                \
                                                  || ((secpktop) == HAL_ETH_DMA_TX_SEC_PKT_OP_ENABLE) )
/** @brief Validates MTL Tx queue operating mode. */
#define IS_ETH_MTL_TX_OPS_MODE(qopmode) ( ((qopmode) == HAL_ETH_MTL_TX_QUEUE_ENABLED) )
/** @brief Validates MTL Tx queue size. */
#define IS_ETH_MTL_TX_QUEUE_SIZE(qsize) ( ((qsize) == HAL_ETH_MTL_TX_QUEUE_SZ_2048_BYTE) )
/** @brief Validates MTL Tx transmit mode. */
#define IS_ETH_MTL_TX_TRANSMIT_MODE(txmode) ( ((txmode) == HAL_ETH_MTL_TX_Q_STORE_AND_FORWARD)                     \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_32_BYTE)                  \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_64_BYTE)                  \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_96_BYTE)                  \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_128_BYTE)                 \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_192_BYTE)                 \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_256_BYTE)                 \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_384_BYTE)                 \
                                              || ((txmode) == HAL_ETH_MTL_TX_Q_THRESHOLD_512_BYTE) )
/** @brief Validates FIFO event mode. */
#define IS_ETH_FIFO_EVENT_MODE(evmode) ( ((evmode) == HAL_ETH_FIFO_EVENT_NONE)                                      \
                                         || ((evmode) == HAL_ETH_FIFO_EVENT_ALWAYS)                                 \
                                         || ((evmode) == HAL_ETH_FIFO_EVENT_CYCLIC) )
/** @brief Validates FIFO event parameters. */
#define IS_ETH_FIFO_EVENT_PARAMS(evmode, evparams) ( ((evmode) == HAL_ETH_FIFO_EVENT_CYCLIC)                       \
                                                     ? ((uint32_t)(evparams) > 0U)                                 \
                                                     : (1U) )
/** @brief Validates PMT control flags mask. */
#define IS_ETH_PMT_CTRL_FLAGS(pmtctrl) ( (((uint32_t)(pmtctrl)) & ~(uint32_t)ETH_PMT_CTRL_MASK) == 0U )
/** @brief Validates LPI control flags mask. */
#define IS_ETH_LPI_CTRL_FLAGS(lpictrl) ( (((uint32_t)(lpictrl)) & ~(uint32_t)ETH_LPI_TX_CLK_MASK) == 0U )
/** @brief Validates DMA Rx burst length. */
#define IS_ETH_DMA_RX_BURST_LENGTH(rxburst)  ( ((rxburst) == HAL_ETH_DMA_RX_BLEN_1_BEAT)                           \
                                               || ((rxburst) == HAL_ETH_DMA_RX_BLEN_2_BEAT)                        \
                                               || ((rxburst) == HAL_ETH_DMA_RX_BLEN_4_BEAT)                        \
                                               || ((rxburst) == HAL_ETH_DMA_RX_BLEN_8_BEAT)                        \
                                               || ((rxburst) == HAL_ETH_DMA_RX_BLEN_16_BEAT)                       \
                                               || ((rxburst) == HAL_ETH_DMA_RX_BLEN_32_BEAT) )

/** @brief Validates DMA Rx buffer length alignment. */
#define IS_ETH_DMA_RX_BUFFER_LEN_ALIGNED(rxbuflen) ( (((rxbuflen) % ETH_BUS_DATA_WIDTH_BYTE) == 0U) )
/** @brief Validates max application buffers number (inclusive range: 0x2..0x1FF). */
#define IS_ETH_MAX_APP_BUFFERS_NUM(maxbuf) ( (((maxbuf) >= 0x2U) && ((maxbuf) <= 0x400U)) )
/** @brief Validates descriptor size: >0 and multiple of configured TX descriptor length. */
#define IS_ETH_DESC_SIZE_BYTE_VALID(desc_size, desc_len_byte ) \
  (((desc_size) > 0U) && (((desc_size) % (desc_len_byte)) == 0U))
/** @brief Validates MTL Rx queue operating mode. */
#define IS_ETH_MTL_RX_OPS_MODE(qopmode) ( ((qopmode) == HAL_ETH_MTL_RX_QUEUE_ENABLED) )
/** @brief Validates MTL Rx queue size. */
#define IS_ETH_MTL_RX_QUEUE_SIZE(qsize) ( ((qsize) == HAL_ETH_MTL_RX_QUEUE_SZ_2048_BYTE) )
/** @brief Validates MTL Rx drop checksum error control. */
#define IS_ETH_MTL_RX_DROP_CS_ERR_CTRL(dropcs) ( ((dropcs) == HAL_ETH_MTL_RX_DROP_CS_ERR_DISABLE)                   \
                                                 || ((dropcs) == HAL_ETH_MTL_RX_DROP_CS_ERR_ENABLE) )
/** @brief Validates MTL Rx forward error packet control. */
#define IS_ETH_MTL_RX_FWD_ERR_PKT_CTRL(fwderr) ( ((fwderr) == HAL_ETH_MTL_RX_FWD_ERR_PKT_DISABLE)                   \
                                                 || ((fwderr) == HAL_ETH_MTL_RX_FWD_ERR_PKT_ENABLE) )
/** @brief Validates MTL Rx forward undersized packet control. */
#define IS_ETH_MTL_RX_FWD_USZ_PKT_CTRL(fwdusz) ( ((fwdusz) == HAL_ETH_MTL_RX_FWD_USZ_PKT_DISABLE)                   \
                                                 || ((fwdusz) == HAL_ETH_MTL_RX_FWD_USZ_PKT_ENABLE) )
/** @brief Validates MTL Rx queue mode. */
#define IS_ETH_MTL_RX_QUEUE_MODE(rxmode) ( ((rxmode) == HAL_ETH_MTL_RX_Q_STORE_AND_FORWARD)                          \
                                           || ((rxmode) == HAL_ETH_MTL_RX_Q_THRESHOLD_32)                            \
                                           || ((rxmode) == HAL_ETH_MTL_RX_Q_THRESHOLD_64)                            \
                                           || ((rxmode) == HAL_ETH_MTL_RX_Q_THRESHOLD_96)                            \
                                           || ((rxmode) == HAL_ETH_MTL_RX_Q_THRESHOLD_128) )

/**
  * @brief  Return the RX channel identifier bit mask for a given zero-based index.
  * @param  ch  Zero-based RX channel index (0 .. USE_HAL_ETH_MAX_RX_CH_NB-1).
  * @retval uint32_t Channel identifier mask (HAL_ETH_RX_CHANNEL_0 shifted by ch).
  */
#define ETH_GET_RX_CH_ID(ch) \
  (((uint32_t)HAL_ETH_RX_CHANNEL_0) << (ch))

/**
  * @brief  Return the TX channel identifier bit mask for a given zero-based index.
  * @param  ch  Zero-based TX channel index (0 .. USE_HAL_ETH_MAX_TX_CH_NB-1).
  * @retval uint32_t Channel identifier mask (HAL_ETH_TX_CHANNEL_0 shifted by ch).
  */
#define ETH_GET_TX_CH_ID(ch) \
  (((uint32_t)HAL_ETH_TX_CHANNEL_0) << (ch))

/**
  * @brief  Enables the specified ETHERNET DMA interrupts for selected Channel.
  * @param  instance : ETH DMA Instance
  * @param  interrupts: specifies the ETHERNET DMA interrupt sources to be
  *   enabled
  */
#define ETH_DMA_CHX_ENABLE_IT(instance, interrupts) ((instance)->DMACXIER \
                                                     |= (interrupts))
/**
  * @brief  Clears the ETHERNET DMA IT pending bit for selected Channel.
  * @param  instance : ETH DMA Instance
  * @param  interrupts: specifies the interrupt pending bit to clear.
  */
#define ETH_DMA_CHX_CLEAR_IT(instance, interrupts) ((instance)->DMACXSR \
                                                    = (interrupts))
/**
  * @brief  Disables the specified ETHERNET DMA interrupts for selected Channel.
  * @param  instance : ETH DMA Instance
  * @param  interrupts: specifies the ETHERNET DMA interrupt sources to be
  *   disabled.
  */
#define ETH_DMA_CHX_DISABLE_IT(instance, interrupts) ((instance)->DMACXIER \
                                                      &= ~(interrupts))
/**
  * @brief  Gets the ETHERNET DMA Descriptor by index from descriptors list.
  * @param  desc_list : Descriptors list address
  * @param  index : Descriptor's index to get
  * @retval The ETH DMA descriptor pointer
  */
#define ETH_GET_DESC_INDEX(desc_list, index) \
  ((eth_dma_descriptor_t *)((uint32_t)(desc_list).p_desc_list_addr + \
                            (((uint32_t)(index)) * ((uint32_t)(desc_list).desc_len_byte))))
/**
  * @brief  Increment FIFO event counter modulo configured offset.
  * @param  fifo_event_cnt Variable that holds the FIFO event counter (in/out).
  * @param  offset         Modulo value / offset used to wrap the counter.
  * @note   Used to track FIFO events with a bounded counter.
  */
#define ETH_INCR_FIFO_EVENT_CNT(fifo_event_cnt, offset) \
  do {\
    (fifo_event_cnt) = (uint32_t)(((uint32_t)(fifo_event_cnt) + 1U) % (uint32_t)(offset));\
  } while (0)
/**
  * @brief  Increment a descriptor index, wrapping to zero when reaching offset.
  * @param  inx    Descriptor index variable (in/out).
  * @param  offset Total number of descriptors in the list (modulus).
  * @note   Safe for ring buffer index updates.
  */
#define ETH_INCR_DESC_INDEX(inx, offset) \
  do {\
    (inx) = (uint32_t)(((uint32_t)(inx) + 1U) % (uint32_t)(offset));\
  } while (0)

/**
  * @brief  Convert a pointer value to a 32-bit unsigned integer representation.
  * @param  addr Pointer value to be converted.
  */
#define ETH_CAST_PTR_TO_U32(addr) ((uint32_t)((uint32_t*)(addr)))

/**
  * @brief  Compute the bit shift for a Remote Wakeup (RWK) command field.
  *
  * This macro returns the bit shift applied to the RWK command field
  * corresponding to the given @p index. Each command field occupies
  * 8 bits, so the shift is calculated as:
  * - @c index * 8
  *
  * @param[in] index
  *         Index of the RWK command field (0-based).
  *
  * @retval uint32_t
  *         Bit shift value for the command field at the given @p index.
  *
  * @note Typical usage is when encoding/decoding RWK command fields into
  *       a 32-bit register where each field is one byte wide.
  */
#define ETH_RWK_CMD_SHIFT(index)                         ((index) * 8U)

/**
  * @brief  Compute the bit shift for a Remote Wakeup (RWK) offset field.
  *
  * This macro returns the bit shift applied to the RWK offset field
  * corresponding to the given @p index. Each offset field occupies
  * 8 bits, so the shift is calculated as:
  * - @c index * 8
  *
  * @param[in] index
  *         Index of the RWK offset field (0-based).
  *
  * @retval uint32_t
  *         Bit shift value for the offset field at the given @p index.
  *
  * @note Typical usage is when encoding/decoding RWK offset fields into
  *       a 32-bit register where each field is one byte wide.
  */
#define ETH_RWK_OFFSET_SHIFT(index)                      ((index) * 8U)

/**
  * @brief  Compute the bit shift for a Remote Wakeup (RWK) CRC16 low word.
  *
  * This macro returns the bit shift applied to the low 16-bit word of a
  * RWK CRC16 value corresponding to the given @p index. Each CRC16 field
  * occupies 16 bits, so the shift is calculated as:
  * - @c index * 16
  *
  * @param[in] index
  *         Index of the RWK CRC16 low-word field (0-based).
  *
  * @retval uint32_t
  *         Bit shift value for the low 16-bit CRC field at the given @p index.
  *
  * @note This is typically used when packing multiple CRC16 values into
  *       a 32-bit or wider register.
  */
#define ETH_RWK_CRC16_SHIFT_LOW(index)                   ((index) * 16U)

/**
  * @brief  Compute the bit shift for a Remote Wakeup (RWK) CRC16 high word.
  *
  * This macro returns the bit shift applied to the high 16-bit word of a
  * RWK CRC16 value corresponding to the given @p index. The shift is
  * calculated as:
  * - @c (index - 2) * 16
  *
  * @param[in] index
  *         Index of the RWK CRC16 high-word field. Expected to be greater
  *         than or equal to 2 so that the expression @c (index - 2) is valid
  *         in the context of the underlying layout.
  *
  * @retval uint32_t
  *         Bit shift value for the high 16-bit CRC field at the given @p index.
  *
  * @note The subtraction by 2 reflects the placement of the high-word CRC16
  *       fields in the register layout (e.g. indexes 2 and 3 can correspond
  *       to the high words of CRC entries 0 and 1).
  */
#define ETH_RWK_CRC16_SHIFT_HIGH(index)                  (((index) - 2U) * 16U)

/**
  * @brief  Get number of descriptors that fit in the provided memory region.
  * @param  total_mem_size Size in bytes of the descriptor memory region.
  * @param  desc_list      Descriptor list information structure (provides desc_len_byte).
  * @retval Number of descriptors that fit in total_mem_size.
  */
#define ETH_GET_DESC_CNT(total_mem_size,desc_list) \
  ((total_mem_size) / (desc_list).desc_len_byte)
/**
  * @brief  Return the greater of two values.
  * @param  value_a First comparison value (must be side-effect free).
  * @param  value_b Second comparison value (must be side-effect free).
  * @retval The maximum of value_a and value_b.
  */
#define ETH_GET_MAX_VALUE(value_a,value_b) (((value_a) > (value_b)) ? (value_a) : (value_b))
/**
  * @brief  Compute skip length size field for DMA descriptor according to bus width.
  * @param  req_desc_size  Requested descriptor size in bytes.
  * @param  curr_desc_size Current descriptor size in bytes.
  * @retval Encoded skip length value shifted to DSL field position.
  */
#define ETH_GET_SKIPLEN_SIZE(req_desc_size, curr_desc_size) \
  ( (uint32_t)(( (uint32_t)(req_desc_size) - (uint32_t)(curr_desc_size) + 8U ) \
               / (uint32_t)ETH_BUS_DATA_WIDTH_BYTE) << (uint32_t)ETH_DMACCR_DSL_Pos )

/**
  * @brief  Copy selected bits from a source value into a destination variable.
  *
  * This macro updates @p dest by copying only the bits selected by @p mask
  * from @p src, leaving all other bits in @p dest unchanged.
  *
  * The operation performed is:
  * - Clear in @p dest all bits that are set in @p mask.
  * - OR in the bits from @p src that are set in @p mask.
  *
  * @param[in,out] dest
  *        Destination variable to be updated. Must be an lvalue of a type
  *        compatible with @c uint32_t.
  * @param[in]     mask
  *        Bit mask that selects which bits must be copied from @p src to
  *        @p dest. Only bits set to 1 in @p mask are affected.
  * @param[in]     src
  *        Source value from which bits are copied according to @p mask.
  */
#define ETH_COPY_BITS(dest,mask, src) \
  do { \
    (dest) = (uint32_t)(((uint32_t)(dest) & ~(uint32_t)(mask)) | ((uint32_t)(src) & (uint32_t)(mask))); \
  } while (0)

#if defined(USE_HAL_CHECK_PROCESS_STATE) && (USE_HAL_CHECK_PROCESS_STATE == 1)
/**
  * @brief  Updates ETH state with atomic protection (using LDREX/STREX).
  * @param  state_field  Field containing the state to update
  * @param  ppp_conditional_states  valid current state
  * @param  ppp_new_state  New state to set if current state matches conditions
  *
  * @note   This macro uses exclusive access instructions for atomic state updates
  * @retval HAL_BUSY if state could not be updated, no action performed
  */
#define ETH_STATES_CHECK_UPDATE(state_field, ppp_conditional_states, ppp_new_state)                              \
  do {                                                                                                           \
    __DMB();                                                                                                     \
    do {                                                                                                         \
      if ((__LDREXW((uint32_t *)((uint32_t)&(state_field))) & (uint32_t)(ppp_conditional_states)) == 0UL)        \
      {                                                                                                          \
        STM32_CLREX_TO_DEPRECATE(); /* Workaround linked to CMSIS IAR issue EWARM-11901 correction fix */        \
        return HAL_BUSY;                                                                                         \
      }                                                                                                          \
    } while (__STREXW((uint32_t)(ppp_new_state), (uint32_t *)((uint32_t)&((state_field)))) != 0UL);              \
    __DMB();                                                                                                     \
  } while (0)

#else /* USE_HAL_CHECK_PROCESS_STATE */

/**
  * @brief  Updates ETH state.
  * @param  state_field           Field containing the state to update
  * @param  ppp_conditional_states  valid current state
  * @param  ppp_new_state            New state to set if current state matches conditions
  * @retval HAL_BUSY if state could not be updated, no action performed
  */
#define ETH_STATES_CHECK_UPDATE(state_field, ppp_conditional_states, ppp_new_state)                             \
  do {                                                                                                          \
    (state_field) = (ppp_new_state);                                                                            \
  } while(0)

#endif /* USE_HAL_CHECK_PROCESS_STATE == 1 */

/**
  * @}
  */

/* Private types -----------------------------------------------*/
/** @defgroup ETH_Private_Types ETH Private Types Definitions
  * @{
  */
/**
  * @brief  ETH DMA Descriptor structure definition
  */
typedef struct
{
  volatile uint32_t DESC0;       /*!< ETH Descriptor Word 0      */
  volatile uint32_t DESC1;       /*!< ETH Descriptor Word 1      */
  volatile uint32_t DESC2;       /*!< ETH Descriptor Word 2      */
  volatile uint32_t DESC3;       /*!< ETH Descriptor Word 3      */
  void *p_pkt_addr;              /*!< Buffer Backup Address */
  void *p_app_data;              /*!< Application data   */
} eth_dma_descriptor_t;

/**
  * @brief MDIO clock range configuration item.
  *
  * Provides precomputed values for selecting the MDIO CSR clock range.
  * - `clk_range_sel`: range selection value to write into `ETH_MACMDIOAR.CR`
  * - `clk_range_div`: divider value used to derive MDC from HCLK for the range selection
  *
  * Used by MDIO clock helpers to map system HCLK to the appropriate MDC divider
  * and CSR encoding.
  */
typedef struct
{
  uint32_t clk_range_sel; /*!< HAL ETH MAC MDC clock range selection */
  uint32_t clk_range_div; /*!< HAL ETH MAC MDC clock range divider   */
} eth_mdio_clk_div_t;

/**
  * @brief  Tx DMA process state.
  */
typedef enum
{
  ETH_TX_DMA_PROCESS_STOPPED                 = 0x0UL,   /*!< DMA stopped: no Tx activity */
  ETH_TX_DMA_PROCESS_FETCHING_DESC           = 0x1UL,   /*!< Fetching next Tx descriptor */
  ETH_TX_DMA_PROCESS_WAITING_STATUS          = 0x2UL,   /*!< Waiting for status writeback */
  ETH_TX_DMA_PROCESS_READING_DATA            = 0x3UL,   /*!< Reading frame data from memory */
  ETH_TX_DMA_PROCESS_TIMESTAMP_WRITE_STATE   = 0x4UL,   /*!< Writing timestamp to descriptor */
  ETH_TX_DMA_PROCESS_SUSPENDED               = 0x6UL,   /*!< Suspended by software or error */
  ETH_TX_DMA_PROCESS_CLOSING_TX_DESC         = 0x7UL,   /*!< Closing Tx descriptor and updating ring */
  ETH_TX_DMA_PROCESS_UNKNOWN                 = 0xFFUL,  /*!< Unknown/invalid state (defensive default) */
} eth_tx_dma_process_state_t;

/**
  * @brief  Rx DMA process state.
  */
typedef enum
{
  ETH_RX_DMA_PROCESS_STOPPED                = 0x0UL,   /*!< DMA stopped: no Rx activity */
  ETH_RX_DMA_PROCESS_FETCHING_DESC          = 0x1UL,   /*!< Fetching next Rx descriptor */
  ETH_RX_DMA_PROCESS_WAITING_PKT            = 0x3UL,   /*!< Waiting for incoming packet */
  ETH_RX_DMA_PROCESS_SUSPENDED              = 0x4UL,   /*!< Suspended by software or error */
  ETH_RX_DMA_PROCESS_CLOSING_DESC           = 0x5UL,   /*!< Closing Rx descriptor and updating ring */
  ETH_RX_DMA_PROCESS_TIMESTAMPING           = 0x6UL,   /*!< Timestamping received packet */
  ETH_RX_DMA_PROCESS_TRANSFERING_DATA       = 0x7UL,   /*!< Transferring data to memory */
  ETH_RX_DMA_PROCESS_UNKNOWN                = 0xFFUL   /*!< Unknown/invalid state (defensive default) */
} eth_rx_dma_process_state_t;

/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup ETH_Private_Variables  ETH Private Variables
  * @{
  */
/**
  * @}
  */
/* Private function prototypes -----------------------------------------------*/
/** @defgroup ETH_Private_Functions ETH Private Functions
  * @{
  */
static void ETH_MAC_Init(struct hal_eth_handle_s *heth);
static void ETH_SetMACConfig(const hal_eth_handle_t *heth, const hal_eth_mac_config_t *macconf);
static void ETH_SetMDIOClockRange(hal_eth_handle_t *heth);
static uint32_t ETH_GetMDIOClockRange(uint32_t eth_hclk_freq);
static void ETH_MTL_Init(struct hal_eth_handle_s *heth);
static void ETH_SetMTLConfig(hal_eth_handle_t *heth, const hal_eth_mtl_config_t *mtlconf);
static void ETH_DMA_Init(struct hal_eth_handle_s *heth);
static void ETH_SetDMAConfig(hal_eth_handle_t *heth, const hal_eth_dma_config_t *dmaconf);
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
static void ETH_InitCommonCallbacksToDefault(hal_eth_handle_t *heth);
static void ETH_InitTxCallbacksToDefault(hal_eth_tx_channel_handle_t *hchannel);
static void ETH_InitRxCallbacksToDefault(hal_eth_rx_channel_handle_t *hchannel);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
static void ETH_ChannelTxInit(hal_eth_handle_t *heth, uint32_t channel);
static void ETH_SetDMATxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_dma_tx_channel_config_t *dmachconf);
static void ETH_GetDMATxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_dma_tx_channel_config_t *dmachconf);
static void ETH_SetMtlTxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_mtl_tx_queue_config_t *mtlchconf);
static void ETH_GetMtlTxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_mtl_tx_queue_config_t *mtlchconf);
static hal_status_t ETH_RequestTxDMA(hal_eth_handle_t *heth, uint32_t ch, hal_eth_buffer_t *p_eth_buffer,
                                     uint32_t buffer_count, hal_eth_tx_pkt_config_t *p_tx_conf);
static void ETH_SetTxFifoEven(hal_eth_handle_t *heth, uint32_t ch, eth_dma_descriptor_t *dmatxdesc,
                              hal_eth_tx_pkt_notify_ctrl_t pkt_notify);
static eth_tx_dma_process_state_t ETH_DMA_GetTxProcessState(const ETH_TypeDef *p_eth, uint32_t ch);
static void ETH_DMATxDescListInit(hal_eth_handle_t *heth, uint32_t ch, uint32_t *p_desc_mem,
                                  uint32_t total_mem_size_byte);
static hal_status_t ETH_StopTxChannel(hal_eth_handle_t *heth, uint32_t ch);
static void ETH_AbortTxChannel(hal_eth_handle_t *heth, uint32_t ch);
static void ETH_RecycleTxDesc(hal_eth_handle_t *heth, uint32_t ch);
static void ETH_ChannelRxInit(hal_eth_handle_t *heth, uint32_t channel);
static void ETH_SetDMARxChannelConfig(hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_dma_rx_channel_config_t *dmachconf);
static void ETH_GetDMARxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_dma_rx_channel_config_t *dmachconf);
static void ETH_SetMtlRxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_mtl_rx_queue_config_t *mtlchconf);
static void ETH_GetMtlRxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_mtl_rx_queue_config_t *mtlchconf);
static hal_status_t ETH_StopRxChannel(hal_eth_handle_t *heth, uint32_t ch);
static void ETH_AbortRxChannel(hal_eth_handle_t *heth, uint32_t ch);
static void ETH_ResetDMADesc(eth_dma_descriptor_t *p_dma_txDesc);
static void ETH_UpdateRxDesc(hal_eth_handle_t *heth, uint32_t ch);
static void ETH_SetRxFifoEvent(hal_eth_handle_t *heth, uint32_t ch, eth_dma_descriptor_t *p_dma_rx_desc);
static void ETH_DMARxDescListInit(hal_eth_handle_t *heth, uint32_t ch, uint32_t *p_desc_mem,
                                  uint32_t total_mem_size_byte);
static void ETH_RecycleRxDesc(hal_eth_handle_t *heth, uint32_t ch);
static eth_rx_dma_process_state_t ETH_DMA_GetRxProcessState(const ETH_TypeDef *p_eth, uint32_t ch);
static hal_status_t ETH_AlignDescSize(uint32_t app_req_size, uint32_t *desc_size);
__STATIC_INLINE void ETH_GetTXChIndex(uint32_t *p_TxCh, uint32_t channel);
__STATIC_INLINE void ETH_GetRXChIndex(uint32_t *p_RxCh, uint32_t channel);
__STATIC_INLINE hal_status_t ETH_LockChannel(volatile uint32_t *channel_lock_state);
__STATIC_INLINE void ETH_UnlockChannel(volatile uint32_t *channel_lock_state);
__STATIC_INLINE uint32_t ETH_WakeupGetPendingIT(void);
__STATIC_INLINE void ETH_WakeupClearPendingIT(uint32_t edge);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @addtogroup ETH_Exported_Functions
  * @{
  */

/** @addtogroup ETH_Exported_Functions_Group1
  * @{
This subsection provides functions allowing to initialize and de-initialize the ETHx instance:
  - HAL_ETH_Init(): Initialize the selected ETHx instance
    - All software resources are initialized
    - No hardware initialization is performed at this level.
  - HAL_ETH_DeInit(): Restore the default configuration of the selected ETHx instance.
  */
/**
  * @brief  Initialize the Ethernet HAL handle and peripheral instance.
  *
  * This function initializes the Ethernet HAL context referenced by @p heth
  * for the given Ethernet peripheral @p instance. It:
  * - Stores the hardware instance in the handle.
  * - Enables the Ethernet clocks (if the clock enable model requires it).
  * - Initializes common, TX, and RX callbacks to their default implementations
  *   (when callback registration is enabled).
  * - Creates the OS semaphore used for bus protection (when mutex support
  *   is enabled).
  * - Clears optional user data and last error codes.
  * - Initializes all TX/RX channels to the reset/unlocked state.
  * - Sets the global state to @ref HAL_ETH_STATE_INIT.
  *
  * This function does not configure pins, descriptors, or low-level MAC, DMA or MTL
  * parameters; those are typically handled by separate configuration APIs.
  *
  * @pre The system clock tree must be fully configured and provide a valid
  *      clock to the Ethernet peripheral before calling this function.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that will be
  *         initialized. On successful return, its fields (instance, channels,
  *         callbacks, semaphore, state, etc.) are prepared for further
  *         configuration and use.
  * @param[in]     instance
  *         Ethernet peripheral instance identifier. Must correspond to a
  *         valid ETH_TypeDef instance and satisfy IS_ETH_ALL_INSTANCE.
  *
  * @retval HAL_OK
  *         Initialization succeeded; the handle is now in
  *         @ref HAL_ETH_STATE_INIT state.
  * @retval HAL_ERROR
  *         OS semaphore creation failed (when @c USE_HAL_MUTEX == 1).
  * @retval HAL_INVALID_PARAM
  *         @p heth is @c NULL (only when parameter checking is enabled via
  *         @c USE_HAL_CHECK_PARAM).
  *
  * @note When @c USE_HAL_ETH_CLK_ENABLE_MODEL is configured to be greater
  *       than or equal to @c HAL_CLK_ENABLE_PERIPH_ONLY, this function
  *       enables the Ethernet clocks via HAL_RCC_ETH1_EnableClock and
  *       related functions.
  * @note When @c USE_HAL_ETH_REGISTER_CALLBACKS is enabled, this function
  *       sets common, TX, and RX callbacks to their default handlers.
  * @note The caller must perform further configuration (descriptors, DMA,
  *       MAC, MTL, interrupts, pins) before starting traffic.
  *
  * @sa HAL_ETH_DeInit
  * @sa ETH_InitCommonCallbacksToDefault
  * @sa ETH_InitTxCallbacksToDefault
  * @sa ETH_InitRxCallbacksToDefault
  */
hal_status_t HAL_ETH_Init(hal_eth_handle_t *heth, hal_eth_t instance)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_ALL_INSTANCE((ETH_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (heth == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->instance = instance;

#if defined(USE_HAL_ETH_CLK_ENABLE_MODEL) && (USE_HAL_ETH_CLK_ENABLE_MODEL >= HAL_CLK_ENABLE_PERIPH_ONLY)
  HAL_RCC_ETH1_EnableClock();
  HAL_RCC_ETH1TX_EnableClock();
  HAL_RCC_ETH1RX_EnableClock();
  HAL_RCC_ETH1CK_EnableClock();
#endif /* USE_HAL_ETH_CLK_ENABLE_MODEL */

#if defined(USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
  ETH_InitCommonCallbacksToDefault(heth);
#endif /* (USE_HAL_ETH_REGISTER_CALLBACKS) */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  if (HAL_OS_SemaphoreCreate(&heth->semaphore) != HAL_OS_OK)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_ETH_USER_DATA) && (USE_HAL_ETH_USER_DATA == 1)
  heth->p_user_data = NULL;
#endif /* USE_HAL_ETH_USER_DATA */


#if defined (USE_HAL_ETH_GET_LAST_ERRORS) && (USE_HAL_ETH_GET_LAST_ERRORS == 1)
  heth->last_error_codes = HAL_ETH_ERROR_NONE;
#endif /* USE_HAL_ETH_GET_LAST_ERRORS */

  /* Init Tx channels */
  for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_TX_CH_NB; ch++)
  {
    heth->tx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_RESET;
    heth->tx_channels[ch].channel_lock_state = ETH_CHANNEL_STATE_UNLOCKED;
    heth->tx_channels[ch].p_tx_complete_cb = NULL;

#if defined(USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    ETH_InitTxCallbacksToDefault(&heth->tx_channels[ch]);
#endif /* (USE_HAL_ETH_REGISTER_CALLBACKS) */
  }

  /* Init Rx channels */
  for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_RX_CH_NB; ch++)
  {
    heth->rx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_RESET;
    heth->rx_channels[ch].channel_lock_state = ETH_CHANNEL_STATE_UNLOCKED;
    heth->rx_channels[ch].p_rx_complete_cb = NULL;
    heth->rx_channels[ch].p_rx_allocate_cb = NULL;

#if defined(USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    ETH_InitRxCallbacksToDefault(&heth->rx_channels[ch]);
#endif /* (USE_HAL_ETH_REGISTER_CALLBACKS) */
  }

  heth->global_state     = HAL_ETH_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  De-initialize the Ethernet peripheral.
  *
  * This function de-initializes the Ethernet HAL context referenced by @p heth
  * and resets the software state of all TX/RX channels. It also disables the
  * Ethernet peripheral clocks and deletes the associated OS semaphore if these
  * features are enabled.
  *
  * The function performs the following actions:
  * - Clears optional user data and last error codes stored in the handle.
  * - Iterates over all TX channels:
  *   - Stops any channel that is in @ref HAL_ETH_CHANNEL_STATE_ACTIVE or
  *     @ref HAL_ETH_CHANNEL_STATE_SUSPENDED using @ref ETH_StopTxChannel().
  *   - Resets the channel state to @ref HAL_ETH_CHANNEL_STATE_RESET.
  *   - Unlocks the channel (@ref ETH_CHANNEL_STATE_UNLOCKED).
  *   - Clears the TX-complete callback pointer.
  * - Iterates over all RX channels:
  *   - Stops any channel that is in @ref HAL_ETH_CHANNEL_STATE_ACTIVE or
  *     @ref HAL_ETH_CHANNEL_STATE_SUSPENDED using @ref ETH_StopRxChannel().
  *   - Resets the channel state to @ref HAL_ETH_CHANNEL_STATE_RESET.
  *   - Unlocks the channel (@ref ETH_CHANNEL_STATE_UNLOCKED).
  *   - Clears the RX-complete and RX-allocate callback pointers.
  * - Sets the global state of the handle to @ref HAL_ETH_STATE_RESET.
  * - Disables the Ethernet clocks if @c USE_HAL_ETH_CLK_ENABLE_MODEL is
  *   configured to at least @c HAL_CLK_ENABLE_PERIPH_ONLY.
  * - Deletes the OS semaphore associated with the handle if @c USE_HAL_MUTEX
  *   is enabled.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and runtime state for the Ethernet
  *         peripheral. Its internal fields (channels, callbacks, user data,
  *         error codes, semaphore, clocks) are reset/de-initialized by this
  *         function.
  *
  * @note This function does not free user-allocated memory for descriptors or
  *       buffers; it only resets the HAL state and disables clocks and
  *       synchronization primitives tied to the handle.
  * @note After this function returns, @p heth is in the
  *       @ref HAL_ETH_STATE_RESET state and must be reinitialized via the
  *       dedicated initialization function before being used again.
  */
void HAL_ETH_DeInit(hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);

#if defined (USE_HAL_ETH_USER_DATA) && (USE_HAL_ETH_USER_DATA == 1)
  heth->p_user_data = NULL;
#endif /* USE_HAL_ETH_USER_DATA */

#if defined (USE_HAL_ETH_GET_LAST_ERRORS) && (USE_HAL_ETH_GET_LAST_ERRORS == 1)
  heth->last_error_codes = HAL_ETH_ERROR_NONE;
#endif /* USE_HAL_ETH_GET_LAST_ERRORS */

  /* Reset Tx channels */
  for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_TX_CH_NB; ch++)
  {
    ETH_AbortTxChannel(heth, ch);
    heth->tx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_RESET;
    heth->tx_channels[ch].channel_lock_state = ETH_CHANNEL_STATE_UNLOCKED;
    heth->tx_channels[ch].p_tx_complete_cb = NULL;
  }

  /* Reset Rx channels */
  for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_RX_CH_NB; ch++)
  {
    ETH_AbortRxChannel(heth, ch);
    heth->rx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_RESET;
    heth->rx_channels[ch].channel_lock_state = ETH_CHANNEL_STATE_UNLOCKED;
    heth->rx_channels[ch].p_rx_complete_cb = NULL;
    heth->rx_channels[ch].p_rx_allocate_cb = NULL;
  }

  heth->global_state = HAL_ETH_STATE_RESET;

#if defined(USE_HAL_ETH_CLK_ENABLE_MODEL) && (USE_HAL_ETH_CLK_ENABLE_MODEL >= HAL_CLK_ENABLE_PERIPH_ONLY)
  HAL_RCC_ETH1TX_DisableClock();
  HAL_RCC_ETH1RX_DisableClock();
  HAL_RCC_ETH1CK_DisableClock();
  HAL_RCC_ETH1_DisableClock();
#endif /* USE_HAL_ETH_CLK_ENABLE_MODEL */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  /* Delete HAL ETH Semaphore*/
  (void)HAL_OS_SemaphoreDelete(&heth->semaphore);
#endif /* USE_HAL_MUTEX  */
}

/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group2
  * @{
This subsection provides functions allowing to configure the Ethernet peripheral:
  - HAL_ETH_SetConfig(): Configure the selected ETHx instance.
  - HAL_ETH_GetConfig(): Retrieve the current configuration of the selected ETHx instance.
  */
/**
  * @brief  Configure the Ethernet MAC, MTL and DMA according to the given settings.
  *
  * This function applies a complete basic configuration of the Ethernet
  * peripheral using the parameters provided in @p p_config and the handle
  * @p heth. It:
  * - Checks that the handle is in a valid state
  *   (@ref HAL_ETH_STATE_INIT or @ref HAL_ETH_STATE_CONFIGURED).
  * - Selects and configures the media interface (MII/RMII/RGMII) through RCC/SBS.
  * - Performs a software reset of the MAC subsystem and waits for completion.
  * - Configures the MDIO clock range according to the current HCLK.
  * - Initializes MAC, MTL and DMA blocks with default settings.
  * - Initializes all TX and RX DMA/MTL channels with default configuration.
  * - Programs the primary MAC address (MACA0) from @p p_config->mac_addr.
  * - Masks MMC TX/RX interrupts.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information for the Ethernet peripheral. Its
  *         @c global_state is updated to @ref HAL_ETH_STATE_CONFIGURED on
  *         success or reverted to @ref HAL_ETH_STATE_INIT on SW reset failure.
  * @param[in]     p_config
  *         Pointer to a constant @ref hal_eth_config_t structure containing:
  *         - @c media_interface : media interface selection
  *           (@ref hal_eth_media_interface_t for supported values).
  *         - @c mac_addr[6]     : 6-byte MAC address to be programmed into
  *           MACA0 register (index 0 = lowest byte).
  *
  * @retval HAL_OK
  *         Configuration completed successfully.
  * @retval HAL_ERROR
  *         Timeout occurred while waiting for the software reset bit to clear.
  * @retval HAL_INVALID_PARAM
  *         @p heth or @p p_config is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @pre
  * - @p heth must have been initialized with @ref HAL_ETH_Init.
  * - @p heth->global_state must be either @ref HAL_ETH_STATE_INIT or
  *   @ref HAL_ETH_STATE_CONFIGURED (checked with debug and optional
  *   runtime checks).
  *
  * @note This function performs a MAC software reset; any previous runtime
  *       configuration in MAC/MTL/DMA registers is lost.
  * @note The function masks a set of MMC TX/RX interrupts by default.
  *
  * @sa HAL_ETH_Init
  * @sa ETH_SetMDIOClockRange
  * @sa ETH_MAC_Init
  * @sa ETH_MTL_Init
  * @sa ETH_DMA_Init
  * @sa ETH_ChannelTxInit
  * @sa ETH_ChannelRxInit
  */
hal_status_t HAL_ETH_SetConfig(hal_eth_handle_t *heth, const hal_eth_config_t *p_config)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ETH_MEDIA_INTERFACE(p_config->media_interface));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_INIT | (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t tickstart;
  ETH_TypeDef *p_Ethx;

  heth->global_state = HAL_ETH_STATE_CONFIGURED;

  /*--------------------- Media Interface Configuration ----------------*/
  if (p_config->media_interface == HAL_ETH_MEDIA_IF_MII)
  {
    LL_SBS_SetETHPHYInterface(LL_SBS_PERIPH_ETH1, LL_SBS_ETHPHY_ITF_GMII_MII);
  }
  else
  {
    LL_SBS_SetETHPHYInterface(LL_SBS_PERIPH_ETH1, LL_SBS_ETHPHY_ITF_RMII);
  }

  /* Ensure that Media Interface Configuration is performed */
  __DSB();

  /* Get Ethernet Instance */
  p_Ethx = ETH_GET_INSTANCE(heth);

  /* Ethernet Software reset */
  /* Set the SWR bit: resets all MAC subsystem internal registers and logic */
  /* After reset all the registers holds their respective reset values */
  STM32_SET_BIT(p_Ethx->DMAMR, ETH_DMAMR_SWR);

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait for software reset */
  while (STM32_READ_BIT(p_Ethx->DMAMR, ETH_DMAMR_SWR) > 0UL)
  {
    if (((HAL_GetTick() - tickstart) > ETH_SWRESET_TIMEOUT_MS))
    {
      heth->global_state = HAL_ETH_STATE_INIT;
      return HAL_ERROR;
    }
  }

  /*------------------ Set MDIO clock --------------------*/
  ETH_SetMDIOClockRange(heth);

  /*------------------ MAC, MTL and DMA default Configurations -------------*/
  ETH_MAC_Init(heth);
  ETH_MTL_Init(heth);
  ETH_DMA_Init(heth);

  /* Apply All DMA and MTL Tx channels Default configurations */
  for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_TX_CH_NB; ch++)
  {
    ETH_ChannelTxInit(heth, ch);
  }

  /* Apply All DMA and MTL Rx channels Default configurations */
  for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_RX_CH_NB; ch++)
  {
    ETH_ChannelRxInit(heth, ch);
  }

  /*--------------------- Ethernet MAC Address Configuration ------------------*/
  /* Set MAC addr bits 32 to 47 */
  STM32_WRITE_REG(p_Ethx->MACA0HR,
                  (((uint32_t)p_config->mac_addr[5] << 8) |
                   (uint32_t)p_config->mac_addr[4]));

  /* Set MAC addr bits 0 to 31 */
  STM32_WRITE_REG(p_Ethx->MACA0LR,
                  (((uint32_t)p_config->mac_addr[3] << 24) |
                   ((uint32_t)p_config->mac_addr[2] << 16) |
                   ((uint32_t)p_config->mac_addr[1] << 8)  |
                   (uint32_t)p_config->mac_addr[0]));

  /* Mask Rx MMC Interrupts */
  STM32_SET_BIT(p_Ethx->MMC_RX_INTERRUPT_MASK,
                ETH_MMC_RX_INTERRUPT_MASK_RXLPITRCIM  |
                ETH_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM  |
                ETH_MMC_RX_INTERRUPT_MASK_RXUCGPIM    |
                ETH_MMC_RX_INTERRUPT_MASK_RXALGNERPIM |
                ETH_MMC_RX_INTERRUPT_MASK_RXCRCERPIM);

  /* Mask Tx MMC Interrupts */
  STM32_SET_BIT(p_Ethx->MMC_TX_INTERRUPT_MASK,
                ETH_MMC_TX_INTERRUPT_MASK_TXLPITRCIM  |
                ETH_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM  |
                ETH_MMC_TX_INTERRUPT_MASK_TXGPKTIM    |
                ETH_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM  |
                ETH_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM);

  return HAL_OK;
}

/**
  * @brief  Retrieve the current Ethernet configuration (media interface and MAC address).
  *
  * This function reads back the hardware configuration of the Ethernet
  * peripheral associated with @p heth and fills the @ref hal_eth_config_t
  * structure pointed to by @p p_config.
  *
  * It:
  * - Reads the media interface configuration from RCC or SBS (depending on
  *   the product) and sets @c p_config->media_interface to one of supported
  *   values in @ref hal_eth_media_interface_t.
  * - Reads the primary MAC address (MACA0) from @c MACA0LR and @c MACA0HR
  *   registers and writes it into @c p_config->mac_addr[0..5].
  *
  * @param[in]  heth
  *         Pointer to a constant @ref hal_eth_handle_t structure that contains
  *         the Ethernet peripheral instance and state. Its @c global_state
  *         must be @ref HAL_ETH_STATE_CONFIGURED.
  * @param[out] p_config
  *         Pointer to a @ref hal_eth_config_t structure where the current
  *         configuration will be stored (media interface and MAC address).
  *
  * @pre
  * - @p heth must not be @c NULL.
  * - @p p_config must not be @c NULL.
  * - @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED
  *   (checked with debug and optional runtime checks).
  *
  * @note This function does not perform any hardware reconfiguration; it only
  *       reads the current registers and copies their values into @p p_config.
  * @note The content of @c p_config can later be passed to
  *       @ref HAL_ETH_SetConfig() to re-apply or modify the configuration.
  *
  * @sa HAL_ETH_SetConfig
  */
void HAL_ETH_GetConfig(const hal_eth_handle_t *heth, hal_eth_config_t *p_config)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  if (LL_SBS_GetETHPHYInterface(LL_SBS_PERIPH_ETH1) == LL_SBS_ETHPHY_ITF_GMII_MII)
  {
    p_config->media_interface = HAL_ETH_MEDIA_IF_MII;
  }
  else
  {
    p_config->media_interface = HAL_ETH_MEDIA_IF_RMII;
  }

  /*--------------------- ETHERNET MAC Address Configuration ------------------*/
  /* Get MAC addr bits 0 to 31 */
  uint32_t macaddrlr = STM32_READ_REG(ETH_GET_INSTANCE(heth)->MACA0LR);
  /* Get MAC addr bits 32 to 47 */
  uint32_t macaddrhr = STM32_READ_REG(ETH_GET_INSTANCE(heth)->MACA0HR);

  /* Fill MAC address (mac_addr[0] = lowest byte) */
  p_config->mac_addr[0] = (uint8_t)((macaddrlr >> 0U)  & 0xFFU);
  p_config->mac_addr[1] = (uint8_t)((macaddrlr >> 8U)  & 0xFFU);
  p_config->mac_addr[2] = (uint8_t)((macaddrlr >> 16U) & 0xFFU);
  p_config->mac_addr[3] = (uint8_t)((macaddrlr >> 24U) & 0xFFU);
  p_config->mac_addr[4] = (uint8_t)((macaddrhr >> 0U)  & 0xFFU);
  p_config->mac_addr[5] = (uint8_t)((macaddrhr >> 8U)  & 0xFFU);
}

/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group3
  * @{
This subsection provides functions allowing to configure the Ethernet Sub-Blocks:
  - MAC sub-block:
    - HAL_ETH_MAC_SetConfig(): Configure the MAC sub-block for selected ETHx instance.
    - HAL_ETH_MAC_GetConfig(): Retrieve the current configuration of MAC sub-block for selected ETHx instance.
  - DMA sub-block:
    - HAL_ETH_DMA_SetConfig(): Configure the DMA sub-block for selected ETHx instance.
    - HAL_ETH_DMA_GetConfig(): Retrieve the current configuration of DMA sub-block for selected ETHx instance.
  - MTL sub-block:
    - HAL_ETH_MTL_SetConfig(): Configure the MTL sub-block for selected ETHx instance.
    - HAL_ETH_MTL_GetConfig(): Retrieve the current configuration of MTL sub-block for selected ETHx instance.
  */
/**
  * @brief  Retrieve the current MAC configuration from the ETH peripheral.
  *
  * This function reads the MAC control and extended control registers of the
  * Ethernet peripheral associated to @p heth and fills the @p p_macconf
  * structure with the current hardware configuration.
  *
  * The retrieved configuration includes, but is not limited to:
  * - Link configuration: speed and duplex mode.
  * - Loopback mode.
  * - Source address control.
  * - Inter-packet gap (IPG) settings.
  * - Back-off limit.
  * - Preamble length.
  * - Giant packet size limit and related control.
  * - 2K packet support.
  * - CRC strip and pad/CRC strip controls.
  * - TX jabber timer control.
  * - Carrier sense (CS) before/during transmit controls.
  * - Retry transmission control.
  * - RX watchdog timer, RX jumbo packet, and RX checksum offload controls.
  * - RX receive own control.
  * - RX CRC checking control.
  * - Deferral check control.
  * - Slow protocol (unicast and general) detection controls.
  * - Extended inter-packet gap control and value.
  * - Programmable watchdog control and timeout.
  * - Flow control configuration (TX pause time, zero-quanta pause, pause.
  *   low threshold, TX/RX flow control, unicast pause packet detection).
  * - Optional packet burst mode (when not in fast-only operation).
  *
  * @param[in]  heth      Pointer to a @ref hal_eth_handle_t structure that
  *                       contains the configuration information for the
  *                       specified Ethernet peripheral.
  * @param[out] p_macconf Pointer to a @ref hal_eth_mac_config_t structure
  *                       that will be filled with the current MAC configuration
  *                       read from the hardware registers.
  *
  * @note This API only queries the hardware registers. It does not modify
  *       any MAC configuration.
  * @note The Ethernet HAL handle @p heth must be in the @ref HAL_ETH_STATE_CONFIGURED
  *       state when calling this function; otherwise an assertion can be raised
  *       in debug builds.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_macconf must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  */
void HAL_ETH_MAC_GetConfig(const hal_eth_handle_t *heth, hal_eth_mac_config_t *p_macconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_macconf != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  const ETH_TypeDef *p_eth_instance = ETH_GET_INSTANCE(heth);

  /* Get MAC parameters */
  p_macconf->link_config.speed = (hal_eth_mac_speed_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                                (ETH_MACCR_FES)));
  p_macconf->link_config.duplex_mode = (hal_eth_mac_duplex_mode_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                   ETH_MACCR_DM));
  p_macconf->loopback_mode = (hal_eth_mac_loopback_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                           ETH_MACCR_LM));
  p_macconf->src_addr_ctrl = (hal_eth_mac_src_addr_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                           ETH_MACCR_SARC));
  p_macconf->inter_pkt_gap_value = (hal_eth_mac_inter_pkt_gap_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                 ETH_MACCR_IPG));
  p_macconf->back_off_limit = (hal_eth_mac_back_off_limit_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                             ETH_MACCR_BL));
  p_macconf->preamble_length = (hal_eth_mac_preeamble_length_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                ETH_MACCR_PRELEN));
  p_macconf->giant_pkt_size_limit_ctrl = (hal_eth_mac_gpkt_sz_limit_ctrl_t)
                                         ((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR, ETH_MACCR_GPSLCE));
  p_macconf->support_2K_pkt = (hal_eth_mac_2k_pkt_len_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                              ETH_MACCR_S2KP));
  p_macconf->crc_strip_type_pkt = (hal_eth_mac_crc_strip_pkt_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                     ETH_MACCR_CST));
  p_macconf->auto_pad_crc_strip = (hal_eth_mac_auto_pad_crc_s_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                      ETH_MACCR_ACS));
  p_macconf->tx_jabber = (hal_eth_mac_tx_jabber_tim_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                            ETH_MACCR_JD));
  p_macconf->cs_before_transmit = (hal_eth_mac_cs_before_tr_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                    ETH_MACCR_ECRSFD));
  p_macconf->cs_during_transmit = (hal_eth_mac_cs_during_tr_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                    ETH_MACCR_DCRS));
  p_macconf->retry_transmission = (hal_eth_mac_retry_tr_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                ETH_MACCR_DR));
  p_macconf->rx_watchdog = (hal_eth_mac_rx_wd_tim_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                          ETH_MACCR_WD));
  p_macconf->rx_jumbo_pkt = (hal_eth_mac_rx_jumbo_pkt_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                              ETH_MACCR_JE));
  p_macconf->rx_csum_offload = (hal_eth_mac_rx_csum_pkt_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                ETH_MACCR_IPC));
  p_macconf->rx_receive_own = (hal_eth_mac_rx_receive_own_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                  ETH_MACCR_DO));
  p_macconf->crc_checking_rx_pkts = (hal_eth_mac_rx_crc_pkt_chk_ctrl_t)
                                    ((uint32_t)STM32_READ_BIT(p_eth_instance->MACECR,
                                                              ETH_MACECR_DCRCC));
  p_macconf->deferral_check = (hal_eth_mac_deferral_check_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACCR,
                                                                  ETH_MACCR_DC));
  p_macconf->uc_slow_proto_detect = (hal_eth_mac_uc_slow_proto_ctrl_t)
                                    ((uint32_t)STM32_READ_BIT(p_eth_instance->MACECR,
                                                              ETH_MACECR_USP));
  p_macconf->slow_proto_detect = (hal_eth_mac_slow_proto_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACECR,
                                                                 ETH_MACECR_SPEN));
  p_macconf->giant_pkt_size_limit = STM32_READ_BIT(p_eth_instance->MACECR, ETH_MACECR_GPSL);
  p_macconf->ext_inter_pkt_gap_ctrl = (hal_eth_mac_ex_int_pkt_gap_ctrl_t)((uint32_t)STM32_READ_BIT(
                                                                            p_eth_instance->MACECR, ETH_MACECR_EIPGEN));
  p_macconf->ext_inter_pkt_gap = (uint32_t)(STM32_READ_BIT(p_eth_instance->MACECR, ETH_MACECR_EIPG)
                                            >> ETH_MACECR_EIPG_Pos);
  p_macconf->programmable_wd = (hal_eth_mac_prog_wd_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACWJBTR,
                                                            ETH_MACWJBTR_PWE));
  p_macconf->rx_wd_timeout_byte = (hal_eth_mac_rx_wd_timeout_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACWJBTR,
                                                                ETH_MACWJBTR_WTO));
  p_macconf->tx_pause_time = (uint32_t)(STM32_READ_BIT(p_eth_instance->MACQTXFCR, ETH_MACQTXFCR_PT)
                                        >> ETH_MACQTXFCR_PT_Pos);
  p_macconf->zero_quanta_pause = (hal_eth_mac_zero_q_pause_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACQTXFCR,
                                                                   ETH_MACQTXFCR_DZPQ));
  p_macconf->pause_low_threshold = (hal_eth_mac_pause_low_thr_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACQTXFCR,
                                                                 ETH_MACQTXFCR_PLT));
  p_macconf->tr_flow_ctrl = (hal_eth_mac_tr_flow_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACQTXFCR,
                                                                                  ETH_MACQTXFCR_TFE));
  p_macconf->uc_pause_pkt_detect = (hal_eth_mac_uc_pause_pkt_ctrl_t)((uint32_t)STM32_READ_BIT(
                                                                       p_eth_instance->MACRXFCR, ETH_MACRXFCR_UP));
  p_macconf->receive_flow_ctrl = (hal_eth_mac_receive_flow_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MACRXFCR,
                                                                   ETH_MACRXFCR_RFE));
}

/**
  * @brief  Set the MAC configuration for the ETH peripheral.
  *
  * This function programs the Ethernet MAC configuration registers of the
  * peripheral associated with @p heth according to the parameters provided
  * in @p p_macconf.
  *
  * The configuration covers, among others:
  * - Link configuration: speed and duplex mode.
  * - Loopback mode.
  * - Source address control.
  * - Inter-packet gap (IPG) settings.
  * - Back-off limit.
  * - Preamble length.
  * - Giant packet size limit and related control.
  * - 2K packet support.
  * - CRC strip and pad/CRC strip controls.
  * - TX jabber timer control.
  * - Carrier sense (CS) before/during transmit controls.
  * - Retry transmission control.
  * - RX watchdog timer, RX jumbo packet, and RX checksum offload controls.
  * - RX receive own control.
  * - RX CRC checking control.
  * - Deferral check control.
  * - Slow protocol (unicast and general) detection controls.
  * - Extended inter-packet gap control and value.
  * - Programmable watchdog control and timeout.
  * - Flow control configuration (TX pause time, zero-quanta pause, pause.
  *   low threshold, TX/RX flow control, unicast pause packet detection).
  * - Optional packet burst mode (when not in fast-only operation).
  *
  * All fields of @p p_macconf are checked for validity using the corresponding
  * parameter-check macros (e.g. @c IS_ETH_MAC_SPEED, @c IS_ETH_MAC_DUPLEX_MODE,
  * etc.) in debug builds. If any field is invalid, an assertion can be raised.
  *
  * This API requires that the Ethernet HAL handle is already in the
  * @ref HAL_ETH_STATE_CONFIGURED state. It does not change the global state
  * of @p heth and does not start or stop the MAC; it only updates the
  * configuration registers.
  *
  * @param[in,out] heth      Pointer to a @ref hal_eth_handle_t structure that
  *                          contains the configuration information for the
  *                          specified Ethernet peripheral.
  * @param[in]     p_macconf Pointer to a constant @ref hal_eth_mac_config_t
  *                          structure that holds the MAC configuration to be
  *                          applied to the hardware.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_macconf must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  *
  * @retval HAL_OK           MAC configuration has been successfully applied.
  * @retval HAL_INVALID_PARAM
  *         - @p p_macconf is @c NULL when `USE_HAL_CHECK_PARAM` is enabled, or
  *         - One or more fields of @p p_macconf are invalid (only if your
  *           implementation uses this status in addition to assertions).
  *
  * @note In this implementation, invalid parameters are primarily handled
  *       via debug assertions. When `USE_HAL_CHECK_PARAM` is enabled,
  *       a `HAL_INVALID_PARAM` status can be returned when @p p_macconf
  *       is @c NULL.
  */
hal_status_t HAL_ETH_MAC_SetConfig(hal_eth_handle_t *heth, const hal_eth_mac_config_t *p_macconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_macconf != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_macconf == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ETH_MAC_SPEED(p_macconf->link_config.speed));
  ASSERT_DBG_PARAM(IS_ETH_MAC_DUPLEX_MODE(p_macconf->link_config.duplex_mode));
  ASSERT_DBG_PARAM(IS_ETH_MAC_LOOPBACK_CTRL(p_macconf->loopback_mode));
  ASSERT_DBG_PARAM(IS_ETH_MAC_SRC_ADDR_CTRL(p_macconf->src_addr_ctrl));
  ASSERT_DBG_PARAM(IS_ETH_MAC_INTER_PKT_GAP(p_macconf->inter_pkt_gap_value));
  ASSERT_DBG_PARAM(IS_ETH_MAC_BACK_OFF_LIMIT(p_macconf->back_off_limit));
  ASSERT_DBG_PARAM(IS_ETH_MAC_PREAMBLE_LENGTH(p_macconf->preamble_length));
  ASSERT_DBG_PARAM(IS_ETH_MAC_GPKT_SZ_LIMIT_CTRL(p_macconf->giant_pkt_size_limit_ctrl));
  ASSERT_DBG_PARAM(IS_ETH_MAC_2K_PKT_LEN_CTRL(p_macconf->support_2K_pkt));
  ASSERT_DBG_PARAM(IS_ETH_MAC_CRC_STRIP_PKT_CTRL(p_macconf->crc_strip_type_pkt));
  ASSERT_DBG_PARAM(IS_ETH_MAC_AUTO_PAD_CRC_S_CTRL(p_macconf->auto_pad_crc_strip));
  ASSERT_DBG_PARAM(IS_ETH_MAC_TX_JABBER_TIM_CTRL(p_macconf->tx_jabber));
  ASSERT_DBG_PARAM(IS_ETH_MAC_CS_BEFORE_TR_CTRL(p_macconf->cs_before_transmit));
  ASSERT_DBG_PARAM(IS_ETH_MAC_CS_DURING_TR_CTRL(p_macconf->cs_during_transmit));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RETRY_TR_CTRL(p_macconf->retry_transmission));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RX_WD_TIM_CTRL(p_macconf->rx_watchdog));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RX_JUMBO_PKT_CTRL(p_macconf->rx_jumbo_pkt));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RX_CSUM_PKT_CTRL(p_macconf->rx_csum_offload));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RX_RECEIVE_OWN_CTRL(p_macconf->rx_receive_own));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RX_CRC_PKT_CHK_CTRL(p_macconf->crc_checking_rx_pkts));
  ASSERT_DBG_PARAM(IS_ETH_MAC_DEFERRAL_CHECK_CTRL(p_macconf->deferral_check));
  ASSERT_DBG_PARAM(IS_ETH_MAC_UC_SLOW_PROTO_CTRL(p_macconf->uc_slow_proto_detect));
  ASSERT_DBG_PARAM(IS_ETH_MAC_SLOW_PROTO_CTRL(p_macconf->slow_proto_detect));
  ASSERT_DBG_PARAM(IS_ETH_MAC_GIANT_PKT_SIZE_LIMIT(p_macconf->giant_pkt_size_limit));
  ASSERT_DBG_PARAM(IS_ETH_MAC_EX_INT_PKT_GAP_CTRL(p_macconf->ext_inter_pkt_gap_ctrl));
  ASSERT_DBG_PARAM(IS_ETH_MAC_EXT_INTER_PKT_GAP(p_macconf->ext_inter_pkt_gap));
  ASSERT_DBG_PARAM(IS_ETH_MAC_PROG_WD_CTRL(p_macconf->programmable_wd));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RX_WD_TIMEOUT_BYTE(p_macconf->rx_wd_timeout_byte));
  ASSERT_DBG_PARAM(IS_ETH_MAC_TX_PAUSE_TIME(p_macconf->tx_pause_time));
  ASSERT_DBG_PARAM(IS_ETH_MAC_ZERO_Q_PAUSE_CTRL(p_macconf->zero_quanta_pause));
  ASSERT_DBG_PARAM(IS_ETH_MAC_PAUSE_LOW_THR(p_macconf->pause_low_threshold));
  ASSERT_DBG_PARAM(IS_ETH_MAC_TR_FLOW_CTRL(p_macconf->tr_flow_ctrl));
  ASSERT_DBG_PARAM(IS_ETH_MAC_UC_PAUSE_PKT_CTRL(p_macconf->uc_pause_pkt_detect));
  ASSERT_DBG_PARAM(IS_ETH_MAC_RECEIVE_FLOW_CTRL(p_macconf->receive_flow_ctrl));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Set the MAC configuration */
  ETH_SetMACConfig(heth, p_macconf);

  return HAL_OK;
}

/**
  * @brief  Get the DMA configuration of the ETH peripheral.
  *
  * This function reads the DMA-related registers of the Ethernet peripheral
  * associated with @p heth and fills the @p p_dmaconf structure with the
  * current hardware configuration.
  *
  * The retrieved configuration includes (depending on the build-time
  * options and system bus type):
  * - TX/RX transfer arbitration algorithm.
  * - Address-aligned beats enable/disable.
  * - DMA burst mode configuration.
  * - Maximum bus burst length (in beats).
  * - System Bus configurations (OSR limits or Mixed burst and rebuild increment
  *   burst).
  * - DMA transfer priority configuration.
  *
  * @param[in]  heth      Pointer to a @ref hal_eth_handle_t structure that
  *                       contains the configuration information for the
  *                       specified Ethernet peripheral.
  * @param[out] p_dmaconf Pointer to a @ref hal_eth_dma_config_t structure
  *                       that will be filled with the current DMA configuration
  *                       read from the hardware registers.
  *
  * @note This API only queries the DMA configuration registers. It does not
  *       modify any configuration or DMA state.
  * @note The Ethernet HAL handle @p heth must be in the
  *       @ref HAL_ETH_STATE_CONFIGURED state when calling this function;
  *       otherwise an assertion is raised in debug builds.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_dmaconf must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  */
void HAL_ETH_DMA_GetConfig(const hal_eth_handle_t *heth, hal_eth_dma_config_t *p_dmaconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_dmaconf != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  const ETH_TypeDef *p_eth_instance = ETH_GET_INSTANCE(heth);

  p_dmaconf->addr_aligned_beats = (hal_eth_dma_addr_align_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->DMASBMR,
                                                                  ETH_DMASBMR_AAL));
  p_dmaconf->burst_mode = (hal_eth_dma_burst_len_mode_t)((uint32_t)STM32_READ_BIT(p_eth_instance->DMASBMR,
                                                                                  ETH_DMASBMR_FB));
  p_dmaconf->mixed_burst = (hal_eth_dma_mixed_burst_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->DMASBMR,
                                                            ETH_DMASBMR_MB));
  p_dmaconf->rebuild_inc_burst = (hal_eth_dma_rebuild_inc_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->DMASBMR,
                                                                  ETH_DMASBMR_RB));
  p_dmaconf->tr_priority = (hal_eth_dma_tr_prio_ctrl_t)((uint32_t)STM32_READ_BIT(
                                                          p_eth_instance->DMAMR, ETH_DMAMR_TXPR));
}

/**
  * @brief  Set the DMA configuration of the ETH peripheral.
  *
  * This function programs the DMA-related registers of the Ethernet peripheral
  * associated with @p heth according to the parameters provided in @p p_dmaconf.
  *
  * The configuration can include (depending on the build-time options and
  * system bus type):
  * - TX/RX transfer arbitration algorithm.
  * - Address-aligned beats control.
  * - DMA burst length mode.
  * - Maximum bus burst length (in beats).
  * - System Bus configurations (OSR limits or Mixed burst and rebuild increment
  *   burst).
  * - DMA transfer priority configuration.
  *
  * All fields of @p p_dmaconf are checked for validity using the corresponding
  * parameter-check macros (for example, @c IS_ETH_DMA_TR_ARBITRATION_ALGO,
  * @c IS_ETH_DMA_ADDR_ALIGNED_BEATS, @c IS_ETH_DMA_BURST_LEN_MODE, etc.) in
  * debug builds. If any field is invalid, an assertion is raised.
  *
  * This API requires that the Ethernet HAL handle is already in the
  * @ref HAL_ETH_STATE_CONFIGURED state. It does not change the global state
  * of @p heth and does not start or stop the DMA; it only updates the DMA
  * configuration registers.
  *
  * @param[in,out] heth      Pointer to a @ref hal_eth_handle_t structure that
  *                          contains the configuration information for the
  *                          specified Ethernet peripheral.
  * @param[in]     p_dmaconf Pointer to a constant @ref hal_eth_dma_config_t
  *                          structure that holds the DMA configuration to be
  *                          applied to the hardware.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_dmaconf must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  *
  * @retval HAL_OK           DMA configuration has been successfully applied.
  * @retval HAL_INVALID_PARAM
  *         - @p p_dmaconf is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *
  * @note In this implementation, most invalid parameters are handled via
  *       debug assertions. When `USE_HAL_CHECK_PARAM` is enabled, a
  *       `HAL_INVALID_PARAM` status is returned if @p p_dmaconf is @c NULL.
  */
hal_status_t HAL_ETH_DMA_SetConfig(hal_eth_handle_t *heth, const hal_eth_dma_config_t *p_dmaconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_dmaconf != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_dmaconf == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ETH_DMA_ADDR_ALIGNED_BEATS(p_dmaconf->addr_aligned_beats));
  ASSERT_DBG_PARAM(IS_ETH_DMA_BURST_LEN_MODE(p_dmaconf->burst_mode));
  ASSERT_DBG_PARAM(IS_ETH_DMA_MIXED_BURST_CTRL(p_dmaconf->mixed_burst));
  ASSERT_DBG_PARAM(IS_ETH_DMA_REBUILD_INC_CTRL(p_dmaconf->rebuild_inc_burst));
  ASSERT_DBG_PARAM(IS_ETH_DMA_TR_PRIO_CTRL(p_dmaconf->tr_priority));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Set the DMA configuration */
  ETH_SetDMAConfig(heth, p_dmaconf);

  return HAL_OK;
}

/**
  * @brief  Get the MTL configuration of the ETH peripheral.
  *
  * This function reads the MTL (MAC Transmission Layer) related registers of
  * the Ethernet peripheral associated with @p heth and fills the @p p_mtlconf
  * structure with the current hardware configuration.
  *
  * The retrieved configuration can include (depending on the build-time
  * options):
  * - TX scheduling algorithm configuration.
  * - RX arbitration algorithm configuration.
  * - TX forward status control (forwarding behavior when store-and-forward
  *   conditions are not fully met).
  *
  * @param[in]  heth      Pointer to a @ref hal_eth_handle_t structure that
  *                       contains the configuration information for the
  *                       specified Ethernet peripheral.
  * @param[out] p_mtlconf Pointer to a @ref hal_eth_mtl_config_t structure
  *                       that will be filled with the current MTL configuration
  *                       read from the hardware registers.
  *
  * @note This API only queries the MTL configuration registers. It does not
  *       modify any configuration or MTL state.
  * @note The Ethernet HAL handle @p heth must be in the
  *       @ref HAL_ETH_STATE_CONFIGURED state when calling this function;
  *       otherwise an assertion can be raised in debug builds.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_mtlconf must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  */
void HAL_ETH_MTL_GetConfig(const hal_eth_handle_t *heth, hal_eth_mtl_config_t *p_mtlconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_mtlconf != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  const ETH_TypeDef *p_eth_instance = ETH_GET_INSTANCE(heth);
  p_mtlconf->tx_fwd_status = (hal_eth_mtl_tx_fwd_status_ctrl_t)((uint32_t)STM32_READ_BIT(p_eth_instance->MTLOMR,
                                                                ETH_MTLOMR_DTXSTS));
}

/**
  * @brief  Set the MTL configuration of the ETH peripheral.
  *
  * This function programs the MTL (MAC Transmission Layer) related registers
  * of the Ethernet peripheral associated with @p heth according to the
  * parameters provided in @p p_mtlconf.
  *
  * The configuration can include (depending on the build-time options):
  * - TX scheduling algorithm configuration.
  * - RX arbitration algorithm configuration.
  * - TX forward status control (forwarding behavior when store-and-forward
  *   conditions are not fully met).
  *
  * All fields of @p p_mtlconf are checked for validity using the corresponding
  * parameter-check macros (for example, @c IS_ETH_MTL_TX_SCHEDULING_ALGO,
  * @c IS_ETH_MTL_RX_ARBITRATION_ALGO, @c IS_ETH_MTL_TX_FWD_STATUS_CTRL) in
  * debug builds. If any field is invalid, an assertion can be raised.
  *
  * This API requires that the Ethernet HAL handle is already in the
  * @ref HAL_ETH_STATE_CONFIGURED state. It does not change the global state
  * of @p heth and does not start or stop the MTL; it only updates the MTL
  * configuration registers.
  *
  * @param[in,out] heth      Pointer to a @ref hal_eth_handle_t structure that
  *                          contains the configuration information for the
  *                          specified Ethernet peripheral.
  * @param[in]     p_mtlconf Pointer to a constant @ref hal_eth_mtl_config_t
  *                          structure that holds the MTL configuration to be
  *                          applied to the hardware.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_mtlconf must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  *
  * @retval HAL_OK           MTL configuration has been successfully applied.
  * @retval HAL_INVALID_PARAM
  *         - @p p_mtlconf is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *
  * @note In this implementation, most invalid parameters are handled via
  *       debug assertions. When `USE_HAL_CHECK_PARAM` is enabled, a
  *       `HAL_INVALID_PARAM` status is returned if @p p_mtlconf is @c NULL.
  */
hal_status_t HAL_ETH_MTL_SetConfig(hal_eth_handle_t *heth, const hal_eth_mtl_config_t *p_mtlconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_mtlconf != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_mtlconf == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ETH_MTL_TX_FWD_STATUS_CTRL(p_mtlconf->tx_fwd_status));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Set the MTL configuration */
  ETH_SetMTLConfig(heth, p_mtlconf);

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group4
  * @{
This subsection provides functions allowing to configure the Ethernet Channels:
  - HAL_ETH_SetConfigTxChannel(): Configure the selected Tx ETHx Channel.
  - HAL_ETH_SetConfigRxChannel(): Configure the selected Rx ETHx Channel.
  - HAL_ETH_GetConfigTxChannel(): Retrieve the current configuration of the selected Tx ETHx Channel.
  - HAL_ETH_GetConfigRxChannel(): Retrieve the current configuration of the selected Rx ETHx Channel.
  - HAL_ETH_GetChannelAllocNeeds(): Retrieve Memory Allocation Needs (requirements) for the selected
    Tx/Rx ETHx Channel.
  */
/**
  * @brief  Set the configuration for a Tx channel.
  *
  * This function configures a given Ethernet Tx channel and its associated
  * MTL Tx queue and DMA Tx channel according to the parameters provided in
  * @p p_chconf.
  *
  * The configuration includes:
  * - DMA Tx channel configuration (PBL x8 mode, burst length, second-packet
  *   operate control, and descriptor alignment requirements).
  * - MTL Tx queue configuration (operating mode, queue size, transmit mode,
  *   and, when supported, queue average (AV) algorithm).
  * - FIFO event configuration (event mode and event parameters).
  * - Maximum number of application buffers associated with this channel.
  *
  * The function also:
  * - Validates the @p channel index and Tx channel parameters.
  * - Checks and aligns the descriptor size to the requested alignment.
  * - Updates the internal Tx channel state to
  *   @ref HAL_ETH_CHANNEL_STATE_CONFIGURED when successful.
  *
  * @param[in,out] heth     Pointer to a @ref hal_eth_handle_t structure that
  *                         contains the configuration information for the
  *                         specified Ethernet peripheral.
  * @param[in]     channel  Channel index to be configured, as defined by
  *                         @ref IS_ETH_CHANNEL_TX_INDEX.
  * @param[in]     p_chconf Pointer to a constant @ref hal_eth_tx_channel_config_t
  *                         structure that holds the Tx channel configuration
  *                         to be applied.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_chconf must not be @c NULL.
  * @pre @p channel must be a valid Tx channel index (see @ref IS_ETH_CHANNEL_TX_INDEX).
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  * @pre The Tx channel state must be @ref HAL_ETH_CHANNEL_STATE_RESET or
  *      @ref HAL_ETH_CHANNEL_STATE_CONFIGURED.
  *
  * @retval HAL_OK           Tx channel configuration has been successfully applied.
  * @retval HAL_INVALID_PARAM
  *         - @p p_chconf is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *         - @p channel is invalid when `USE_HAL_CHECK_PARAM` is enabled.
  *         - The requested descriptor alignment cannot be satisfied by
  *           @ref ETH_AlignDescSize.
  *
  * @note In this implementation, most invalid parameters are handled via
  *       debug assertions. When `USE_HAL_CHECK_PARAM` is enabled, a
  *       `HAL_INVALID_PARAM` status is returned if @p p_chconf is @c NULL
  *       or @p channel is invalid, or if descriptor alignment fails.
  */
hal_status_t HAL_ETH_SetConfigTxChannel(hal_eth_handle_t *heth, uint32_t channel,
                                        const hal_eth_tx_channel_config_t *p_chconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_chconf != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_TX_INDEX(channel));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_chconf == NULL) || (IS_ETH_CHANNEL_TX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);
  ASSERT_DBG_PARAM(IS_ETH_DMA_TX_PBL_X8_MODE(p_chconf->dma_channel_config.tx_pbl_x8_mode));
  ASSERT_DBG_PARAM(IS_ETH_DMA_TX_BURST_LENGTH(p_chconf->dma_channel_config.tx_dma_burst_length));
  ASSERT_DBG_PARAM(IS_ETH_DMA_TX_SEC_PKT_OP_CTRL(p_chconf->dma_channel_config.tx_second_pkt_operate));
  ASSERT_DBG_PARAM(IS_ETH_MTL_TX_OPS_MODE(p_chconf->mtl_queue_config.queue_op_mode));
  ASSERT_DBG_PARAM(IS_ETH_MAX_APP_BUFFERS_NUM(p_chconf->max_app_buffers_num));
  ASSERT_DBG_PARAM(IS_ETH_MTL_TX_QUEUE_SIZE(p_chconf->mtl_queue_config.queue_size_byte));
  ASSERT_DBG_PARAM(IS_ETH_MTL_TX_TRANSMIT_MODE(p_chconf->mtl_queue_config.transmit_queue_mode));
  ASSERT_DBG_PARAM(IS_ETH_FIFO_EVENT_MODE(p_chconf->fifo_event_config.event_mode));
  ASSERT_DBG_PARAM(IS_ETH_FIFO_EVENT_PARAMS(p_chconf->fifo_event_config.event_mode,
                                            p_chconf->fifo_event_config.event_params));

  uint32_t ch = 0;
  uint32_t desc_size_aligned = 0;

  /* Retrieve the Channel Id. */
  ETH_GetTXChIndex(&ch, channel);

  ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_RESET |
                   (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED);

  /* Compute aligned descriptor size and ensure hardware skip-length constraints are respected. */
  if (ETH_AlignDescSize(p_chconf->req_desc_size_align_byte, &desc_size_aligned) != HAL_OK)
  {
    return HAL_INVALID_PARAM;
  }

  /* Move Tx channel state to configured. */
  heth->tx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_CONFIGURED;
  /* Align the eth_dma_descriptor_t size to the requested alignment size. */
  heth->tx_channels[ch].tx_desc_list.desc_len_byte = desc_size_aligned;

  /* Get the max buffer number requested. */
  heth->tx_channels[ch].tx_desc_list.total_desc_cnt = p_chconf->max_app_buffers_num * 2UL;
  /* Get the requested event mode. */
  heth->tx_channels[ch].fifo_event_config.event_mode       = p_chconf->fifo_event_config.event_mode;
  heth->tx_channels[ch].fifo_event_config.event_params     = p_chconf->fifo_event_config.event_params;

  /*------------------ Set DMA Tx Descriptors Configuration ----------------------*/
  ETH_SetDMATxChannelConfig(heth, ch, &p_chconf->dma_channel_config);

  /*------------------ Set MTL Tx Queue Configuration ---------------------------*/
  ETH_SetMtlTxChannelConfig(heth, ch, &p_chconf->mtl_queue_config);

  return HAL_OK;
}

/**
  * @brief  Set the configuration for a Rx channel.
  *
  * This function configures a given Ethernet Rx channel and its associated
  * MTL Rx queue and DMA Rx channel according to the parameters provided in
  * @p p_chconf.
  *
  * The configuration includes:
  * - DMA Rx channel configuration (burst length, buffer length, and descriptor
  *   alignment requirements).
  * - MTL Rx queue configuration (operating mode, queue size, checksum error
  *   drop behavior, forwarding of error and undersized packets, and receive
  *   queue mode).
  * - Mapping of the MTL Rx queue to a DMA channel when multiple Rx channels
  *   are supported.
  * - FIFO event configuration (event mode and event parameters).
  * - Maximum number of application buffers associated with this channel.
  *
  * The function also:
  * - Validates the @p channel index and Rx channel parameters.
  * - Ensures the Rx buffer length is aligned to the bus data width
  *   (`ETH_BUS_DATA_WIDTH_BYTE`).
  * - Checks and aligns the descriptor size to the requested alignment
  *   using @ref ETH_AlignDescSize.
  * - Updates the internal Rx channel state to
  *   @ref HAL_ETH_CHANNEL_STATE_CONFIGURED when successful.
  *
  * @param[in,out] heth     Pointer to a @ref hal_eth_handle_t structure that
  *                         contains the configuration information for the
  *                         specified Ethernet peripheral.
  * @param[in]     channel  Channel index to be configured, as defined by
  *                         @ref IS_ETH_CHANNEL_RX_INDEX.
  * @param[in]     p_chconf Pointer to a constant @ref hal_eth_rx_channel_config_t
  *                         structure that holds the Rx channel configuration
  *                         to be applied.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_chconf must not be @c NULL.
  * @pre @p channel must be a valid Rx channel index (see @ref IS_ETH_CHANNEL_RX_INDEX).
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  * @pre The Rx channel state must be @ref HAL_ETH_CHANNEL_STATE_RESET or
  *      @ref HAL_ETH_CHANNEL_STATE_CONFIGURED.
  *
  * @retval HAL_OK           Rx channel configuration has been successfully applied.
  * @retval HAL_INVALID_PARAM
  *         - @p p_chconf is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *         - @p channel is invalid when `USE_HAL_CHECK_PARAM` is enabled.
  *         - The Rx buffer length is not aligned to `ETH_BUS_DATA_WIDTH_BYTE`.
  *         - The requested descriptor alignment cannot be satisfied by
  *           @ref ETH_AlignDescSize.
  *
  * @note In this implementation, most invalid parameters are handled via
  *       debug assertions. When `USE_HAL_CHECK_PARAM` is enabled, a
  *       `HAL_INVALID_PARAM` status is returned if @p p_chconf is @c NULL,
  *       @p channel is invalid, or if buffer or descriptor alignment checks fail.
  */
hal_status_t HAL_ETH_SetConfigRxChannel(hal_eth_handle_t *heth, uint32_t channel,
                                        const hal_eth_rx_channel_config_t *p_chconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_chconf != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_RX_INDEX(channel));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_chconf == NULL) || (IS_ETH_CHANNEL_RX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);
  ASSERT_DBG_PARAM(IS_ETH_DMA_RX_BURST_LENGTH(p_chconf->dma_channel_config.rx_dma_burst_length));
  ASSERT_DBG_PARAM(IS_ETH_DMA_RX_BUFFER_LEN_ALIGNED(p_chconf->dma_channel_config.rx_buffer_len_byte));
  ASSERT_DBG_PARAM(IS_ETH_MTL_RX_OPS_MODE(p_chconf->mtl_queue_config.queue_op_mode));
  ASSERT_DBG_PARAM(IS_ETH_MTL_RX_QUEUE_SIZE(p_chconf->mtl_queue_config.queue_size_byte));
  ASSERT_DBG_PARAM(IS_ETH_MTL_RX_DROP_CS_ERR_CTRL(p_chconf->mtl_queue_config.drop_tcp_ip_csum_error_pkt));
  ASSERT_DBG_PARAM(IS_ETH_MTL_RX_FWD_ERR_PKT_CTRL(p_chconf->mtl_queue_config.fwd_error_pkt));
  ASSERT_DBG_PARAM(IS_ETH_MTL_RX_FWD_USZ_PKT_CTRL(p_chconf->mtl_queue_config.fwd_undersized_good_pkt));
  ASSERT_DBG_PARAM(IS_ETH_MTL_RX_QUEUE_MODE(p_chconf->mtl_queue_config.receive_queue_mode));
  ASSERT_DBG_PARAM(IS_ETH_MAX_APP_BUFFERS_NUM(p_chconf->max_app_buffers_num));
  ASSERT_DBG_PARAM(IS_ETH_FIFO_EVENT_MODE(p_chconf->fifo_event_config.event_mode));
  ASSERT_DBG_PARAM(IS_ETH_FIFO_EVENT_PARAMS(p_chconf->fifo_event_config.event_mode,
                                            p_chconf->fifo_event_config.event_params));
  uint32_t ch = 0;
  uint32_t desc_size_aligned = 0;

  /* Retrieve the Channel Id. */
  ETH_GetRXChIndex(&ch, channel);

  /* Assert on Channel State. */
  ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_RESET |
                   (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED);

  /* Rx buffer length must be aligned to the `ETH_BUS_DATA_WIDTH_BYTE`. */
  if (((p_chconf->dma_channel_config.rx_buffer_len_byte) % ((uint32_t)ETH_BUS_DATA_WIDTH_BYTE)) != 0UL)
  {
    return HAL_INVALID_PARAM;
  }

  /* Compute aligned descriptor size and ensure hardware skip-length constraints are respected. */
  if (ETH_AlignDescSize(p_chconf->req_desc_size_align_byte, &desc_size_aligned) != HAL_OK)
  {
    return HAL_INVALID_PARAM;
  }

  /* Move Rx channel state to configured. */
  heth->rx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_CONFIGURED;
  /* Align the eth_dma_descriptor_t size to the requested alignment size. */
  heth->rx_channels[ch].rx_desc_list.desc_len_byte = desc_size_aligned;
  /* Get the max buffer number requested. */
  heth->rx_channels[ch].rx_desc_list.total_desc_cnt = p_chconf->max_app_buffers_num * 2UL;
  /* Get the requested event mode. */
  heth->rx_channels[ch].fifo_event_config.event_mode       = p_chconf->fifo_event_config.event_mode;
  heth->rx_channels[ch].fifo_event_config.event_params     = p_chconf->fifo_event_config.event_params;

  /*------------------ Set DMA Rx Descriptors Configuration ----------------------*/
  ETH_SetDMARxChannelConfig(heth, ch, &p_chconf->dma_channel_config);

  /*------------------ Set MTL Rx Queue Configuration ---------------------------*/
  ETH_SetMtlRxChannelConfig(heth, ch, &p_chconf->mtl_queue_config);

  return HAL_OK;
}

/**
  * @brief  Get the configuration for a Tx channel.
  *
  * This function retrieves the configuration of a given Ethernet Tx channel,
  * including the associated MTL Tx queue and DMA Tx channel, and stores it
  * in the structure pointed to by @p p_chconf.
  *
  * The retrieved configuration includes:
  * - Descriptor-related settings (maximum number of application buffers and
  *   descriptor size alignment).
  * - FIFO event configuration (event mode and event parameters).
  * - DMA Tx channel configuration.
  * - MTL Tx queue configuration.
  *
  * @param[in]  heth     Pointer to a @ref hal_eth_handle_t structure that
  *                      contains the configuration information for the
  *                      specified Ethernet peripheral.
  * @param[in]  channel  Channel index whose configuration is requested, as
  *                      defined by @ref IS_ETH_CHANNEL_TX_INDEX.
  * @param[out] p_chconf Pointer to a @ref hal_eth_tx_channel_config_t
  *                      structure that will be filled with the current Tx
  *                      channel configuration.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_chconf must not be @c NULL.
  * @pre @p channel must be a valid Tx channel index (see @ref IS_ETH_CHANNEL_TX_INDEX).
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  */
void HAL_ETH_GetConfigTxChannel(const hal_eth_handle_t *heth, uint32_t channel,
                                hal_eth_tx_channel_config_t *p_chconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_TX_INDEX(channel));
  ASSERT_DBG_PARAM(p_chconf != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t ch = 0;

  /* Retrieve the Tx Channel Id. */
  ETH_GetTXChIndex(&ch, channel);

  /*------------------ Get Tx Descriptors Configuration -------------------------*/
  p_chconf->max_app_buffers_num       = heth->tx_channels[ch].tx_desc_list.total_desc_cnt;
  p_chconf->req_desc_size_align_byte  = heth->tx_channels[ch].tx_desc_list.desc_len_byte;
  p_chconf->fifo_event_config.event_mode   = heth->tx_channels[ch].fifo_event_config.event_mode;
  p_chconf->fifo_event_config.event_params = heth->tx_channels[ch].fifo_event_config.event_params;

  /*------------------ Get DMA Tx Descriptors Configuration ---------------------*/
  ETH_GetDMATxChannelConfig(heth, ch, &p_chconf->dma_channel_config);

  /*------------------ Get MTL Tx Queue Configuration ---------------------------*/
  ETH_GetMtlTxChannelConfig(heth, ch, &p_chconf->mtl_queue_config);
}

/**
  * @brief  Get the configuration for a Rx channel.
  *
  * This function retrieves the configuration of a given Ethernet Rx channel,
  * including the associated MTL Rx queue and DMA Rx channel, and stores it
  * in the structure pointed to by @p p_chconf.
  *
  * The retrieved configuration includes:
  * - Descriptor-related settings (maximum number of application buffers and
  *   descriptor size alignment).
  * - FIFO event configuration (event mode and event parameters).
  * - DMA Rx channel configuration.
  * - MTL Rx queue configuration.
  *
  * @param[in]  heth     Pointer to a @ref hal_eth_handle_t structure that
  *                      contains the configuration information for the
  *                      specified Ethernet peripheral.
  * @param[in]  channel  Channel index whose configuration is requested, as
  *                      defined by @ref IS_ETH_CHANNEL_RX_INDEX.
  * @param[out] p_chconf Pointer to a @ref hal_eth_rx_channel_config_t
  *                      structure that will be filled with the current Rx
  *                      channel configuration.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_chconf must not be @c NULL.
  * @pre @p channel must be a valid Rx channel index (see @ref IS_ETH_CHANNEL_RX_INDEX).
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  */
void HAL_ETH_GetConfigRxChannel(const hal_eth_handle_t *heth, uint32_t channel,
                                hal_eth_rx_channel_config_t *p_chconf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_chconf != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_RX_INDEX(channel));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t ch = 0;

  /* Retrieve the Rx Channel Id. */
  ETH_GetRXChIndex(&ch, channel);

  /*------------------ Get Rx Descriptors Configuration -------------------------*/
  p_chconf->max_app_buffers_num      = heth->rx_channels[ch].rx_desc_list.total_desc_cnt;
  p_chconf->req_desc_size_align_byte = heth->rx_channels[ch].rx_desc_list.desc_len_byte;
  p_chconf->fifo_event_config.event_mode   = heth->rx_channels[ch].fifo_event_config.event_mode;
  p_chconf->fifo_event_config.event_params = heth->rx_channels[ch].fifo_event_config.event_params;

  /*------------------ Get DMA Rx Descriptors Configuration ---------------------*/
  ETH_GetDMARxChannelConfig(heth, ch, &p_chconf->dma_channel_config);

  /*------------------ Get MTL Rx Queue Configuration ---------------------------*/
  ETH_GetMtlRxChannelConfig(heth, ch, &p_chconf->mtl_queue_config);
}

/**
  * @brief  Get the memory allocation requirements for a channel.
  *
  * This function returns the memory size and alignment requirements for the
  * descriptor ring associated with a given Ethernet channel (Tx or Rx), and
  * stores them in the structure pointed to by @p p_ch_alloc_req.
  *
  * The function determines whether the specified @p channel is a Tx or Rx
  * channel, retrieves the corresponding internal channel context, and computes:
  * - The total memory size in bytes required for the descriptor ring.
  * - The required memory address alignment in bytes.
  *
  * The size is computed as:
  * @code
  * mem_size_byte = total_desc_cnt * desc_len_byte.
  * @endcode
  * and the alignment is set to `ETH_BUS_DATA_WIDTH_BYTE`.
  *
  * @param[in]  heth           Pointer to a @ref hal_eth_handle_t structure that
  *                            contains the configuration information for the
  *                            specified Ethernet peripheral.
  * @param[in]  channel        Channel index, as defined by @ref IS_ETH_CHANNEL_INDEX.
  *                            The function automatically distinguishes between
  *                            Tx and Rx channels using @ref HAL_ETH_TX_CHANNEL_ALL.
  * @param[out] p_ch_alloc_req Pointer to a @ref hal_eth_channel_alloc_needs_t
  *                            structure that will be filled with the memory
  *                            allocation requirements.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_ch_alloc_req must not be @c NULL.
  * @pre @p channel must be a valid channel index (see @ref IS_ETH_CHANNEL_INDEX).
  * @pre The corresponding Tx or Rx channel state must be
  *      @ref HAL_ETH_CHANNEL_STATE_CONFIGURED.
  *
  * @note The values of `desc_len_byte` and `total_desc_cnt` depend on the channel configuration,
  *       in particular on whether the extended format and/or context descriptors are expected
  *       to be used.
  */
void HAL_ETH_GetChannelAllocNeeds(const hal_eth_handle_t *heth, uint32_t channel,
                                  hal_eth_channel_alloc_needs_t *p_ch_alloc_req)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_ch_alloc_req != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_INDEX(channel));

  uint32_t ch;

  if ((channel & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    /* Retrieve Tx Channel Id. */
    ETH_GetTXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED);

    p_ch_alloc_req->mem_size_byte       = heth->tx_channels[ch].tx_desc_list.total_desc_cnt *
                                          heth->tx_channels[ch].tx_desc_list.desc_len_byte;
    p_ch_alloc_req->mem_addr_align_byte = ETH_BUS_DATA_WIDTH_BYTE;
  }
  else
  {
    /* Retrieve Rx Channel Id. */
    ETH_GetRXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED);

    p_ch_alloc_req->mem_size_byte       = heth->rx_channels[ch].rx_desc_list.total_desc_cnt *
                                          heth->rx_channels[ch].rx_desc_list.desc_len_byte;
    p_ch_alloc_req->mem_addr_align_byte = ETH_BUS_DATA_WIDTH_BYTE;
  }
}
/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group5
  * @{
This subsection provides functions allowing the control of the Ethernet Peripheral Features:
  - MAC Update Link Config : provides functions allowing update the speed/duplex without resetting the MAC.
    - HAL_ETH_UpdateConfigLink(): Update the MAC speed and duplex mode.
  - MAC ARP offload Feature: provides functions allowing the control of the Ethernet ARP Offloading Feature.
    - HAL_ETH_EnableARPOffload(): Enable ARP offload.
    - HAL_ETH_DisableARPOffload(): Disable ARP offload.
    - HAL_ETH_IsEnabledARPOffload(): Check if the ETH ARP offload is enabled.
    - HAL_ETH_SetARPTargetIP(): Set ARP target IP address.
  - MAC LPM Feature: provides functions allowing the control of the Ethernet LPM Feature.
    - HAL_ETH_EnterPowerDownMode(): Enters Ethernet Power Down mode with specified PMT control flags.
    - HAL_ETH_ExitPowerDownMode(): Exit power down mode.
    - HAL_ETH_SetRemoteWakeUpPcktFilter(): Configures the Remote Wake-Up Packet Filter LUT for Ethernet.
  - EEE Features: provides functions allowing the control of the Ethernet EEE Feature.
    - HAL_ETH_EnterLPIMode(): Configures Ethernet LPI (Low Power Idle) control flags.
    - HAL_ETH_ExitLPIMode(): Exit LPI (Low Power Idle) mode.
  */
/**
  * @brief  Update the Ethernet MAC link configuration (speed and duplex mode).
  *
  * This function updates the Ethernet MAC configuration register (MACCR) with
  * the link configuration provided in @p p_config, specifically the link speed
  * and duplex mode. It assumes that the Ethernet handle has already been
  * properly initialized and is in the @ref HAL_ETH_STATE_CONFIGURED state.
  *
  * The function:
  * - Validates input parameters (when @c USE_HAL_CHECK_PARAM is enabled).
  * - Composes the link configuration value from @ref hal_eth_link_config_t.
  * - Updates the MACCR link-related bits.
  *
  * @param[in] heth
  *        Pointer to an @ref hal_eth_handle_t structure that contains the
  *        configuration information for the Ethernet peripheral.
  * @param[in] p_config
  *        Pointer to a @ref hal_eth_link_config_t structure that contains
  *        the new link configuration parameters (e.g. @c speed and
  *        @c duplex_mode).
  *
  * @retval HAL_OK
  *         Link configuration was successfully updated.
  * @retval HAL_INVALID_PARAM
  *         One or more input parameters are invalid (only when parameter
  *         checking is enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @pre
  * - @p heth must not be @c NULL.
  * - @p p_config must not be @c NULL.
  * - @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  *
  * @note This function only updates link configuration bits in the MACCR
  *       register (speed and duplex). It does not initiate any PHY
  *       negotiation or check link status.
  *
  * @sa hal_eth_handle_t
  * @sa hal_eth_link_config_t
  */
hal_status_t HAL_ETH_UpdateConfigLink(hal_eth_handle_t *heth, const hal_eth_link_config_t *p_config)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM(IS_ETH_MAC_SPEED(p_config->speed));
  ASSERT_DBG_PARAM(IS_ETH_MAC_DUPLEX_MODE(p_config->duplex_mode));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t linkregval;
  linkregval = ((uint32_t)p_config->speed |
                (uint32_t)p_config->duplex_mode);
  /*update link config bits */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACCR, ETH_MAC_LINK_CONFIG_MASK, linkregval);

  return HAL_OK;
}

/**
  * @brief  Enable ARP offload.
  *
  * This function enables the ARP offload feature in the Ethernet MAC by
  * setting the ARP enable bit in the MAC configuration register. When ARP
  * offload is enabled, the MAC hardware can autonomously process ARP frames
  * according to the device-specific implementation, potentially reducing CPU
  * involvement in ARP handling.
  *
  * @param[in,out] heth Pointer to a @ref hal_eth_handle_t structure that
  *                     contains the configuration information for the
  *                     specified Ethernet peripheral.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  *
  * @note The exact behavior of ARP offload (such as which ARP requests are
  *       answered and how IP/MAC mapping is managed) is hardware-dependent
  *       and must be checked in the device reference manual.
  */
void HAL_ETH_EnableARPOffload(hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Enable ARP Offloading */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_ARPEN);
}

/**
  * @brief  Disable ARP offload.
  *
  * This function disables the ARP offload feature in the Ethernet MAC by
  * clearing the ARP enable bit in the MAC configuration register. When ARP
  * offload is disabled, ARP processing is fully handled by the software
  * network stack rather than by the MAC hardware.
  *
  * @param[in,out] heth Pointer to a @ref hal_eth_handle_t structure that
  *                     contains the configuration information for the
  *                     specified Ethernet peripheral.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  */
void HAL_ETH_DisableARPOffload(hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Disable ARP Offloading */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_ARPEN);
}

/**
  * @brief  Check if the ETH ARP offload is enabled.
  *
  * This function checks the ARP offload enable bit in the MAC configuration
  * register and returns the current ARP offload status.
  *
  * @param[in] heth Pointer to a @ref hal_eth_handle_t structure that
  *                 contains the configuration information for the
  *                 specified Ethernet peripheral.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  *
  * @retval hal_eth_arp_offload_status_t Current ARP offload status
  *         (see @ref hal_eth_arp_offload_status_t).
  */
hal_eth_arp_offload_status_t HAL_ETH_IsEnabledARPOffload(const hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  return (hal_eth_arp_offload_status_t)((uint32_t)STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_ARPEN));
}

/**
  * @brief  Set the ARP target IP address.
  *
  * This function programs the ARP target protocol address (TPA) used by
  * the Ethernet MAC ARP offload logic. The @p tpa value is typically an
  * IPv4 address encoded as a 32-bit value in network byte order.
  *
  * @param[in,out] heth Pointer to a @ref hal_eth_handle_t structure that
  *                     contains the configuration information for the
  *                     specified Ethernet peripheral.
  * @param[in]     tpa  Target protocol (IP) address encoded as a 32-bit value.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  *
  * @note The exact encoding and usage of the target protocol address are
  *       hardware-dependent and must be checked in the device reference manual.
  */
void HAL_ETH_SetARPTargetIP(hal_eth_handle_t *heth, uint32_t tpa)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACARPAR, tpa);
}

/**
  * @brief  Enter Ethernet MAC Power-Down mode with PMT configuration.
  *
  * This function configures the Power Management and Timer (PMT) features of
  * the Ethernet MAC and initiates the MAC Power-Down sequence. It can enable
  * Remote Wakeup (RWK) and Magic Packet detection based on @p pmt_ctrl.
  *
  * The function:
  * - Checks that the handle is valid and in @ref HAL_ETH_STATE_CONFIGURED.
  * - Checks and Updates the global state from @ref HAL_ETH_STATE_CONFIGURED to
  *   @ref HAL_ETH_STATE_POWER_DOWN.
  * - Programs the PMT control/status register @c MACPCSR with @p pmt_ctrl
  *   (masked by @ref ETH_PMT_CTRL_MASK).
  * - If any PMT trigger is enabled in @p pmt_ctrl:
  *   - Enables the MAC receiver.
  *   - Enables the PMT interrupt.
  * - Sets the Power-Down bit in @c MACPCSR to start the Power-Down sequence.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and state for the Ethernet peripheral.
  *         Its @c global_state is updated to @ref HAL_ETH_STATE_POWER_DOWN
  *         on success.
  * @param[in]     pmt_ctrl
  *         PMT control bitmask to be written into @c MACPCSR (masked with
  *         @ref ETH_PMT_CTRL_MASK). This typically includes:
  *         - Remote wakeup filters (RWK)
  *         - Magic Packet enable
  *         - Other PMT-related control bits as defined by ETH_PMT_CTRL_MASK.
  *
  * @retval HAL_OK
  *         Power-Down sequence initiated successfully.
  * @retval HAL_INVALID_PARAM
  *         @p heth is @c NULL (only when parameter checking is enabled via
  *         @c USE_HAL_CHECK_PARAM).
  *
  * @pre
  * - @p heth must be in @ref HAL_ETH_STATE_CONFIGURED
  *   (checked with debug and optional runtime checks).
  *
  * @note When @p pmt_ctrl is 0, the MAC still enters Power-Down but no
  *       PMT wake-up source is enabled.
  * @note The system clock and other peripheral clocks would need to remain
  *       enabled as required by the PMT and wake-up scheme.
  *
  * @sa HAL_ETH_ExitPowerDownMode
  * @sa HAL_ETH_PMT_CTRL_FWD_WAKEUP_PKT
  * @sa HAL_ETH_PMT_CTRL_TRIG_MAGIC_PKT
  * @sa HAL_ETH_PMT_CTRL_TRIG_RWKUP_PKT
  * @sa HAL_ETH_PMT_CTRL_TRIG_GLBL_UCAST
  * @sa HAL_ETH_PMT_CTRL_TRIG_ALL
  */
hal_status_t HAL_ETH_EnterPowerDownMode(hal_eth_handle_t *heth, uint32_t pmt_ctrl)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_PMT_CTRL_FLAGS(pmt_ctrl));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  HAL_CHECK_UPDATE_STATE(heth, global_state, HAL_ETH_STATE_CONFIGURED, HAL_ETH_STATE_POWER_DOWN);

  /* Configure remote wake-up and magic packet sources */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACPCSR, ETH_PMT_CTRL_MASK, pmt_ctrl);

  if ((pmt_ctrl & ETH_PMT_CTRL_MASK) != 0UL)
  {
    /* Enable MAC receiver */
    STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_RE);
    /* Enable PMTIE Interrupt */
    STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACIER, ETH_MACIER_PMTIE);
  }
  /* Initiate the Power-Down sequence */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACPCSR, ETH_MACPCSR_PWRDWN);
  return HAL_OK;
}

/**
  * @brief  Exit Ethernet MAC Power-Down mode.
  *
  * This function restores the Ethernet MAC from Power-Down mode back to the
  * configured state. It clears PMT configuration and PMT interrupt, performs
  * dummy writes to key MAC registers as required by the hardware, and clears
  * the Power-Down bit.
  *
  * The function:
  * - Checks that the handle is valid and in @ref HAL_ETH_STATE_POWER_DOWN.
  * - Checks and Updates the global state from @ref HAL_ETH_STATE_POWER_DOWN to
  *   @ref HAL_ETH_STATE_CONFIGURED.
  * - Disables the PMT interrupt.
  * - Clears PMT control bits in @c MACPCSR (masked by @ref ETH_PMT_CTRL_MASK).
  * - Performs write operations to:
  *   - @c ETH_MACCR
  *   - @c ETH_MACA0HR
  *   - @c ETH_MACA0LR
  *   to satisfy hardware requirements when exiting Power-Down.
  * - Clears the Power-Down bit to exit Power-Down.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and state for the Ethernet peripheral.
  *         Its @c global_state is updated back to
  *         @ref HAL_ETH_STATE_CONFIGURED on success.
  *
  * @retval HAL_OK
  *         Power-Down mode exited successfully.
  * @retval HAL_INVALID_PARAM
  *         @p heth is @c NULL (only when parameter checking is enabled via
  *         @c USE_HAL_CHECK_PARAM).
  *
  * @pre
  * - @p heth must be in @ref HAL_ETH_STATE_POWER_DOWN
  *   (checked with debug and optional runtime checks).
  *
  * @note After calling this function, the MAC configuration (MACCR and
  *       MACA0 registers) would need to be revalidated or updated depending
  *       on the hardware behavior and application requirements.
  *
  * @sa HAL_ETH_EnterPowerDownMode
  */
hal_status_t HAL_ETH_ExitPowerDownMode(hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_POWER_DOWN);

  HAL_CHECK_UPDATE_STATE(heth, global_state, HAL_ETH_STATE_POWER_DOWN, HAL_ETH_STATE_CONFIGURED);

  /* Disable PMTIE Interrupt */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACIER, ETH_MACIER_PMTIE);

  /* Clear PMT control status register */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACPCSR, ETH_PMT_CTRL_MASK);

  /* Perform required write operations when exiting power-down */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACCR, 0UL, 0UL);
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACA0HR, 0UL, 0UL);
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACA0LR, 0UL, 0UL);

  /* Exit Power-Down mode */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACPCSR, ETH_MACPCSR_PWRDWN);

  return HAL_OK;
}

/**
  * @brief  Configure the Remote Wake-Up Packet Filter LUT for Ethernet.
  *
  * This function programs the Remote Wake-Up (RWK) packet filter lookup table
  * (LUT) for the Ethernet peripheral. Each filter entry in the LUT can be
  * configured to match specific packet patterns and control the filter logic
  * using the following command constants:
  *   - @ref HAL_ETH_RWK_FLT_CMD_ENABLE.
  *   - @ref HAL_ETH_RWK_FLT_CMD_AND_PREVIOUS.
  *   - @ref HAL_ETH_RWK_FLT_CMD_INVERSE_MODE.
  *   - @ref HAL_ETH_RWK_FLT_CMD_MULTICAST.
  *
  * These constants are used in the filter command field to define the behavior
  * of each filter, such as enabling the filter, chaining filters for complex
  * logic, inverting match logic, and specifying the address type
  * (unicast/multicast).
  * The maximum number of filter blocks supported by the hardware is defined by
  * @ref HAL_ETH_RWK_FILT_BLOCK_NUM.
  *
  * The function performs the following operations:
  * - Validates the filter LUT pointer when parameter checking is enabled.
  * - Resets the internal RWK filter write pointer.
  * - Writes the byte-mask words for each filter entry.
  * - Accumulates and writes command, offset, and CRC16 fields into the
  *   dedicated RWK programming registers.
  *
  * @param[in] heth         Pointer to a @ref hal_eth_handle_t structure that
  *                         contains the configuration information for the
  *                         specified Ethernet peripheral.
  * @param[in] p_filter_lut Pointer to a @ref hal_eth_rwk_filter_lut_t structure
  *                         that contains the filter entries and their command
  *                         configurations. The number of filter blocks in this
  *                         structure is equal to @ref HAL_ETH_RWK_FILT_BLOCK_NUM.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_filter_lut must not be @c NULL.
  *
  * @retval HAL_OK          Filter LUT configured successfully.
  * @retval HAL_INVALID_PARAM
  *         - @p p_filter_lut is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *
  * @see hal_eth_rwk_filter_lut_t.
  * @see hal_eth_rwk_pkt_filter_t.
  * @see HAL_ETH_RWK_FLT_CMD_ENABLE.
  * @see HAL_ETH_RWK_FLT_CMD_AND_PREVIOUS.
  * @see HAL_ETH_RWK_FLT_CMD_INVERSE_MODE.
  * @see HAL_ETH_RWK_FLT_CMD_MULTICAST.
  * @see HAL_ETH_RWK_FILT_BLOCK_NUM.
  */
hal_status_t HAL_ETH_SetRemoteWakeUpPcktFilter(const hal_eth_handle_t *heth,
                                               const hal_eth_rwk_filter_lut_t *p_filter_lut)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_filter_lut != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_filter_lut == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  const hal_eth_rwk_filter_block_t *p_filter_block = &(p_filter_lut->block0);
  uint32_t commands_reg  = 0UL;
  uint32_t offsets_reg   = 0UL;
  uint32_t crc16_1_reg   = 0UL;
  uint32_t crc16_2_reg   = 0UL;
  ETH_TypeDef *p_Ethx = ETH_GET_INSTANCE(heth);

  /* Reset internal write pointer for remote wake-up filter programming. */
  STM32_SET_BIT(p_Ethx->MACPCSR, ETH_MACPCSR_RWKFILTRST);

  /* Write byte mask words then accumulate command/offset/CRC fields. */
  for (uint32_t index = 0UL; index < ETH_NB_OF_RWK_FILT_PER_BLOCK; index++)
  {
    ASSERT_DBG_PARAM(IS_ETH_RWK_BYTE_MASK(p_filter_block->filter[index].byte_mask));
    STM32_WRITE_REG(p_Ethx->MACRWKPFR, p_filter_block->filter[index].byte_mask);

    commands_reg  |= ((((uint32_t)p_filter_block->filter[index].commands) & ETH_RWK_CMD_MASK)
                      << ETH_RWK_CMD_SHIFT(index));
    offsets_reg |= ((((uint32_t)p_filter_block->filter[index].offsets) & ETH_RWK_OFFSET_MASK)
                    << ETH_RWK_OFFSET_SHIFT(index));

    if (index < 2U)
    {
      crc16_1_reg |= ((((uint32_t)p_filter_block->filter[index].crc16) & ETH_RWK_CRC16_MASK)
                      << ETH_RWK_CRC16_SHIFT_LOW(index));
    }
    else
    {
      crc16_2_reg |= ((((uint32_t)p_filter_block->filter[index].crc16) & ETH_RWK_CRC16_MASK)
                      << ETH_RWK_CRC16_SHIFT_HIGH(index));
    }
  }

  /* Write command, offset, and CRC registers sequence. */
  STM32_WRITE_REG(p_Ethx->MACRWKPFR, commands_reg);
  STM32_WRITE_REG(p_Ethx->MACRWKPFR, offsets_reg);
  STM32_WRITE_REG(p_Ethx->MACRWKPFR, crc16_1_reg);
  STM32_WRITE_REG(p_Ethx->MACRWKPFR, crc16_2_reg);

  return HAL_OK;
}

/**
  * @brief  Configure Ethernet LPI (Low Power Idle) control flags and enter LPI mode.
  *
  * This function sets the LPI control flags for the Ethernet peripheral and
  * enables Low Power Idle (LPI) mode. The @p lpi_ctrl parameter is a bitwise
  * OR combination of the supported LPI control flags, which define the LPI
  * behavior.
  *
  * Supported LPI control flags are:
  * - @ref HAL_ETH_LPI_CTRL_TX_CLK_STOP_ENABLE.
  * - @ref HAL_ETH_LPI_CTRL_TX_AUTOMATE_ENABLE.
  *
  * The function performs the following operations:
  * - Configures the LPI control register with the specified control flags.
  * - Enables the LPI interrupt.
  * - Enables LPI mode in the MAC.
  *
  * @param[in,out] heth     Pointer to a @ref hal_eth_handle_t structure that
  *                         contains the configuration information for the
  *                         specified Ethernet peripheral.
  * @param[in]     lpi_ctrl Bitwise OR combination of LPI control flags that
  *                         specifies the desired LPI behavior. This must be
  *                         a valid combination as checked by
  *                         @ref IS_ETH_LPI_CTRL_FLAGS.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  * @pre @p lpi_ctrl must satisfy @ref IS_ETH_LPI_CTRL_FLAGS.
  *
  * @see HAL_ETH_LPI_CTRL_TX_CLK_STOP_ENABLE.
  * @see HAL_ETH_LPI_CTRL_TX_AUTOMATE_ENABLE.
  */
void HAL_ETH_EnterLPIMode(hal_eth_handle_t *heth, uint32_t lpi_ctrl)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_LPI_CTRL_FLAGS(lpi_ctrl));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Write to LPI Control register: Enter low power mode. */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACLCSR, ETH_LPI_TX_CLK_MASK, lpi_ctrl);
  /* Enable LPI Interrupt. */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACIER, ETH_MACIER_LPIIE);
  /* Enable LPI mode. */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACLCSR, ETH_MACLCSR_LPIEN);
}

/**
  * @brief  Exit Ethernet LPI (Low Power Idle) mode.
  *
  * This function exits Low Power Idle (LPI) mode for the Ethernet MAC and
  * restores normal operation by clearing the LPI-related configuration and
  * disabling LPI interrupts.
  *
  * The function performs the following operations:
  * - Clears the LPI control bits that manage TX clock behavior in LPI mode.
  * - Disables the LPI interrupt.
  * - Disables LPI mode in the MAC.
  *
  * @param[in,out] heth Pointer to a @ref hal_eth_handle_t structure that
  *                     contains the configuration information for the
  *                     specified Ethernet peripheral.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  */
void HAL_ETH_ExitLPIMode(hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Clear the LPI configuration. */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACLCSR, ETH_LPI_TX_CLK_MASK);
  /* Disable LPI interrupt. */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACIER, ETH_MACIER_LPIIE);
  /* Disable LPI mode. */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACLCSR, ETH_MACLCSR_LPIEN);
}

/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group6
  * @{
This subsection provides functions allowing the registration of the Ethernet Channel Callbacks.
  - HAL_ETH_RegisterChannelRxAllocateCallback(): Register Rx allocate callback for a channel.
  - HAL_ETH_RegisterChannelRxCptCallback(): Register Rx complete callback for a channel.
  - HAL_ETH_RegisterChannelTxCptCallback(): Register Tx complete callback for a channel.
  - HAL_ETH_RegisterDataCallback(): Register data callback.
  - HAL_ETH_RegisterWKUPCallback(): Register wakeup callback.
  - HAL_ETH_RegisterPMTCallback(): Register PMT callback.
  - HAL_ETH_RegisterEEECallback(): Register EEE callback.
  - HAL_ETH_RegisterErrorCallback(): Register error callback.
  - HAL_ETH_RegisterEventCallback(): Register event callback.
  - HAL_ETH_RegisterCacheInvalidateCallback(): Register cache invalidate callback.
  - HAL_ETH_RegisterCacheFlushCallback(): Register cache flush callback.
  - HAL_ETH_RegisterChannelRxEventCallback(): Register Rx channel events callback.
  - HAL_ETH_RegisterChannelTxEventCallback(): Register Tx channel events callback.
  */
/**
  * @brief  Register an Rx allocate callback for a channel.
  *
  * This function registers a user-provided Rx allocate callback function for
  * the specified Ethernet Rx channel. The callback is typically invoked by
  * the HAL when a new buffer needs to be allocated for received data on the
  * corresponding channel.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     channel    Channel index for which the callback is to be
  *                           registered, as defined by @ref IS_ETH_CHANNEL_RX_INDEX.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_rx_allocate_cb_t to be associated
  *                           with the specified Rx channel.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  * @pre @p channel must be a valid Rx channel index (see @ref IS_ETH_CHANNEL_RX_INDEX).
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *         - @p channel is invalid when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterChannelRxAllocateCallback(hal_eth_handle_t *heth, uint32_t channel,
                                                       hal_eth_rx_allocate_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_RX_INDEX(channel));

  uint32_t ch;

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_callback == NULL) || (IS_ETH_CHANNEL_RX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Retrieve the Rx Channel Id. */
  ETH_GetRXChIndex(&ch, channel);
  heth->rx_channels[ch].p_rx_allocate_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register an Rx complete callback for a channel.
  *
  * This function registers a user-provided Rx complete callback function for
  * the specified Ethernet Rx channel. The callback is typically invoked by
  * the HAL when a receive operation has completed on the corresponding
  * channel.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     channel    Channel index for which the callback is to be
  *                           registered, as defined by @ref IS_ETH_CHANNEL_RX_INDEX.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_rx_complete_cb_t to be associated
  *                           with the specified Rx channel.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  * @pre @p channel must be a valid Rx channel index (see @ref IS_ETH_CHANNEL_RX_INDEX).
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *         - @p channel is invalid when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterChannelRxCptCallback(hal_eth_handle_t *heth, uint32_t channel,
                                                  hal_eth_rx_complete_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_RX_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_callback == NULL) || (IS_ETH_CHANNEL_RX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t ch;

  /* Retrieve the Rx Channel Id. */
  ETH_GetRXChIndex(&ch, channel);
  heth->rx_channels[ch].p_rx_complete_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a Tx complete callback for a channel.
  *
  * This function registers a user-provided Tx complete callback function for
  * the specified Ethernet Tx channel. The callback is typically invoked by
  * the HAL when a transmit operation has completed on the corresponding
  * channel.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     channel    Channel index for which the callback is to be
  *                           registered, as defined by @ref IS_ETH_CHANNEL_TX_INDEX.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_tx_complete_cb_t to be associated
  *                           with the specified Tx channel.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  * @pre @p channel must be a valid Tx channel index (see @ref IS_ETH_CHANNEL_TX_INDEX).
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  *         - @p channel is invalid when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterChannelTxCptCallback(hal_eth_handle_t *heth, uint32_t channel,
                                                  hal_eth_tx_complete_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_TX_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_callback == NULL) || (IS_ETH_CHANNEL_TX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t ch;

  /* Retrieve the Tx Channel Id. */
  ETH_GetTXChIndex(&ch, channel);
  heth->tx_channels[ch].p_tx_complete_cb = p_callback;

  return HAL_OK;
}

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a data callback.
  *
  * This function registers a user-provided data callback function for the
  * Ethernet peripheral. The callback is typically invoked by the HAL when
  * data-related events occur (for example, reception of new data or completion
  * of a transmit operation), depending on the driver implementation.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_cb_t to be associated with the
  *                           Ethernet handle.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterDataCallback(hal_eth_handle_t *heth, hal_eth_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_data_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a wakeup callback.
  *
  * This function registers a user-provided wakeup callback function for the
  * Ethernet peripheral. The callback is typically invoked by the HAL when a
  * wakeup event occurs, such as a remote wakeup packet or other low-power
  * exit condition, depending on the driver implementation.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_wakeup_cb_t to be associated with
  *                           the Ethernet handle.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterWKUPCallback(hal_eth_handle_t *heth, hal_eth_wakeup_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_wake_up_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a PMT (Power Management Trigger) callback.
  *
  * This function registers a user-provided PMT callback function for the
  * Ethernet peripheral. The callback is typically invoked by the HAL when
  * a power management related event occurs (for example, Magic Packet or
  * wake-up frame), depending on the driver implementation.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_cb_t to be associated with the
  *                           Ethernet handle for PMT events.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterPMTCallback(hal_eth_handle_t *heth, hal_eth_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_pmt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register an EEE (Energy Efficient Ethernet) callback.
  *
  * This function registers a user-provided EEE callback function for the
  * Ethernet peripheral. The callback is typically invoked by the HAL when
  * an EEE-related event occurs (for example, entry or exit from low power
  * idle states), depending on the driver implementation.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_cb_t to be associated with the
  *                           Ethernet handle for EEE events.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterEEECallback(hal_eth_handle_t *heth, hal_eth_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_eee_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register an error callback.
  *
  * This function registers a user-provided error callback function for the
  * Ethernet peripheral. The callback is typically invoked by the HAL when
  * an error condition is detected on the Ethernet MAC, DMA, or related
  * subsystems, depending on the driver implementation.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_cb_t to be associated with the
  *                           Ethernet handle for error events.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterErrorCallback(hal_eth_handle_t *heth, hal_eth_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_error_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register an event callback.
  *
  * This function registers a user-provided generic event callback function
  * for the Ethernet peripheral. The callback is typically invoked by the HAL
  * when non-error, non-PMT, non-EEE events occur, depending on the driver
  * implementation (for example, link status changes or other notifications).
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_cb_t to be associated with the
  *                           Ethernet handle for generic events.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterEventCallback(hal_eth_handle_t *heth, hal_eth_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_event_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a cache invalidate callback.
  *
  * This function registers a user-provided cache invalidate callback function
  * for the Ethernet peripheral. The callback is typically invoked by the HAL
  * to invalidate data cache lines associated with Ethernet buffers before
  * performing DMA operations or processing received data, depending on the
  * system cache architecture and driver implementation.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_cache_cb_t to be associated with
  *                           the Ethernet handle for cache invalidation.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterCacheInvalidateCallback(hal_eth_handle_t *heth, hal_eth_cache_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_cache_invalidate_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a cache flush callback.
  *
  * This function registers a user-provided cache flush callback function
  * for the Ethernet peripheral. The callback is typically invoked by the HAL
  * to flush (clean) data cache lines associated with Ethernet buffers before
  * they are used by the DMA engine, depending on the system cache architecture
  * and driver implementation.
  *
  * @param[in,out] heth       Pointer to a @ref hal_eth_handle_t structure that
  *                           contains the configuration information for the
  *                           specified Ethernet peripheral.
  * @param[in]     p_callback Pointer to a callback function of type
  *                           @ref hal_eth_cache_cb_t to be associated with
  *                           the Ethernet handle for cache flushing.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_callback must not be @c NULL.
  *
  * @retval HAL_OK           Callback has been successfully registered.
  * @retval HAL_INVALID_PARAM
  *         - @p p_callback is @c NULL when `USE_HAL_CHECK_PARAM` is enabled.
  */
hal_status_t HAL_ETH_RegisterCacheFlushCallback(hal_eth_handle_t *heth, hal_eth_cache_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  heth->p_cache_flush_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a callback for Ethernet RX channel events.
  *
  * This function associates a user-provided callback @p p_callback with the
  * RX channel identified by @p channel in the Ethernet handle @p heth. The
  * callback will be invoked by the HAL when an RX channel event occurs
  * (e.g. packet reception, error, etc. depending on implementation).
  *
  * The function:
  * - Validates @p heth, @p p_callback, and @p channel (with debug and optional
  *   runtime checks).
  * - Converts the RX channel bitmask @p channel into a channel index via
  *   @ref ETH_GetRXChIndex.
  * - Stores the callback pointer into
  *   @c heth->rx_channels[index].p_ch_event_cb.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and runtime state for the Ethernet
  *         peripheral.
  * @param[in]     channel
  *         RX channel identifier (bitmask) that must satisfy
  *         @ref IS_ETH_CHANNEL_RX_INDEX. If multiple bits are set, the first
  *         valid RX channel index is used.
  * @param[in]     p_callback
  *         Pointer to a function of type @ref hal_eth_channel_cb_t that will
  *         be called on RX channel events.
  *
  * @retval HAL_OK
  *         Callback successfully registered for the selected RX channel.
  * @retval HAL_ERROR
  *         RX channel index could not be derived from @p channel
  *         (i.e. @ref ETH_GetRXChIndex returned an error).
  * @retval HAL_INVALID_PARAM
  *         - @p heth or @p p_callback is @c NULL, or
  *         - @p channel is invalid (IS_ETH_CHANNEL_RX_INDEX() returns 0),
  *         and parameter checking is enabled via @c USE_HAL_CHECK_PARAM.
  *
  * @note This function only registers the callback; the user must ensure that
  *       RX channel events are properly enabled and handled in the interrupt
  *       or polling layer that triggers the callback.
  *
  * @sa ETH_GetRXChIndex
  * @sa HAL_ETH_RegisterChannelTxEventCallback
  */
hal_status_t HAL_ETH_RegisterChannelRxEventCallback(hal_eth_handle_t *heth, uint32_t channel,
                                                    hal_eth_channel_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_RX_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_callback == NULL) || (IS_ETH_CHANNEL_RX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t ch;

  ETH_GetRXChIndex(&ch, channel);
  heth->rx_channels[ch].p_ch_event_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register a callback for Ethernet TX channel events.
  *
  * This function associates a user-provided callback @p p_callback with the
  * TX channel identified by @p channel in the Ethernet handle @p heth. The
  * callback will be invoked by the HAL when a TX channel event occurs
  * (e.g. transmit complete, error, etc., depending on implementation).
  *
  * The function:
  * - Validates @p heth, @p p_callback, and @p channel (with debug and optional
  *   runtime checks).
  * - Converts the TX channel bitmask @p channel into a channel index via
  *   @ref ETH_GetTXChIndex.
  * - Stores the callback pointer into
  *   @c heth->tx_channels[index].p_ch_event_cb.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and runtime state for the Ethernet
  *         peripheral.
  * @param[in]     channel
  *         TX channel identifier (bitmask) that must satisfy
  *         @ref IS_ETH_CHANNEL_TX_INDEX. If multiple bits are set, the first
  *         valid TX channel index is used.
  * @param[in]     p_callback
  *         Pointer to a function of type @ref hal_eth_channel_cb_t that will
  *         be called on TX channel events.
  *
  * @retval HAL_OK
  *         Callback successfully registered for the selected TX channel.
  * @retval HAL_ERROR
  *         TX channel index could not be derived from @p channel
  *         (i.e. @ref ETH_GetTXChIndex returned an error).
  * @retval HAL_INVALID_PARAM
  *         - @p heth or @p p_callback is @c NULL, or
  *         - @p channel is invalid (IS_ETH_CHANNEL_TX_INDEX() returns 0),
  *         and parameter checking is enabled via @c USE_HAL_CHECK_PARAM.
  *
  * @note This function only registers the callback; the user must ensure that
  *       TX channel events are properly enabled and handled in the interrupt
  *       or polling layer that triggers the callback.
  *
  * @sa ETH_GetTXChIndex
  * @sa HAL_ETH_RegisterChannelRxEventCallback
  */
hal_status_t HAL_ETH_RegisterChannelTxEventCallback(hal_eth_handle_t *heth, uint32_t channel,
                                                    hal_eth_channel_cb_t p_callback)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_TX_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_callback == NULL) || (IS_ETH_CHANNEL_TX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t ch;

  /* Retrieve the Rx Channel Id */
  ETH_GetTXChIndex(&ch, channel);
  heth->tx_channels[ch].p_ch_event_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS && USE_HAL_ETH_REGISTER_CALLBACKS = 1 */
/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group7
  * @{
This subsection provides Interrupts management functions.
  - HAL_ETH_WKUP_IRQHandler(): Ethernet wakeup IRQ handler.
  - HAL_ETH_IRQHandler(): Register Rx allocate callback for a channel.
  */
/**
  * @brief  Ethernet global interrupt handler.
  *
  * This function handles all Ethernet-related interrupt sources, including
  * MAC, DMA, MTL, PMT, EEE, data, event, wakeup, and error conditions.
  * It reads and decodes the interrupt status of each DMA channel and MTL
  * queue, updates internal state, clears the corresponding interrupt flags,
  * and invokes the registered user callbacks or the weak default callbacks.
  *
  * The handler performs the following main actions.
  * - Iterates over all configured DMA channels and:
  *   - Detects Tx and Rx data completion events and accumulates a channel
  *     data-event bitmap.
  *   - Detects DMA/MTL channel error and status events and calls the
  *     corresponding per-channel event callbacks.
  *   - Clears the DMA channel interrupt status flags.
  * - If any Tx/Rx data event is detected, invokes the global data callback
  *   (registered via @ref HAL_ETH_RegisterDataCallback or default
  *   @ref HAL_ETH_DataCallback).
  * - Processes MAC-level event flags (for example, link or status events)
  *   and invokes the event callback (registered via
  *   @ref HAL_ETH_RegisterEventCallback or default
  *   @ref HAL_ETH_EventCallback).
  * - Checks for PMT events and calls the PMT callback
  *   (@ref HAL_ETH_RegisterPMTCallback or @ref HAL_ETH_PMTCallback).
  * - Checks for EEE (Energy Efficient Ethernet) events and calls the EEE
  *   callback (@ref HAL_ETH_RegisterEEECallback or @ref HAL_ETH_EEECallback).
  * - Optionally handles external wakeup (EXTI-based) events when enabled,
  *   and calls the wakeup callback (@ref HAL_ETH_RegisterWKUPCallback or
  *   @ref HAL_ETH_WakeUpCallback).
  * - If a DMA error is detected, updates the global Ethernet state to
  *   @ref HAL_ETH_STATE_FAULT, optionally stores the last error codes, and
  *   invokes the error callback (@ref HAL_ETH_RegisterErrorCallback or
  *   @ref HAL_ETH_ErrorCallback).
  *
  * @param[in,out] heth Pointer to a @ref hal_eth_handle_t structure that
  *                     contains the configuration information for the
  *                     specified Ethernet peripheral and associated channels.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p heth must have been properly initialized and configured before
  *      this handler is called (typically from the Ethernet IRQ vector).
  *
  * @note This function is intended to be called from the Ethernet interrupt
  *       service routine. It must not be called directly from non-interrupt
  *       context unless the same preconditions and mutual exclusion
  *       requirements are guaranteed by the caller.
  */
void HAL_ETH_IRQHandler(hal_eth_handle_t *heth)
{
  uint32_t ch_data_event = 0UL;
  uint32_t dma_error_code = 0UL;
  uint32_t mac_event_code = STM32_READ_REG(ETH_GET_INSTANCE(heth)->MACRXTXSR);
  uint32_t max_ch_nb = ETH_GET_MAX_VALUE(USE_HAL_ETH_MAX_TX_CH_NB, USE_HAL_ETH_MAX_RX_CH_NB);

  /* Get MAC status register. */
  uint32_t mac_status_flag = STM32_READ_REG(ETH_GET_INSTANCE(heth)->MACISR);

  for (uint32_t dma_ch_id = 0; dma_ch_id < max_ch_nb; dma_ch_id++)
  {
    /* Get DMA Channel interrupt status and source registers. */
    ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_GET_DMA_CHANNEL(heth, dma_ch_id);
    const ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_GET_MTL_QUEUE(heth, dma_ch_id);
    uint32_t dma_ch_flag = STM32_READ_REG(p_dma_instance->DMACXSR);
    uint32_t dma_ch_itsource = STM32_READ_REG(p_dma_instance->DMACXIER);
    uint32_t mtl_ch_event = STM32_READ_REG(p_mtl_instance->MTLQXICSR);
    uint32_t rx_ch_event = 0UL;
    uint32_t tx_ch_event = 0UL;

    /* Packet transmitted by DMA Channel. */
    if ((dma_ch_id < USE_HAL_ETH_MAX_TX_CH_NB)
        && (STM32_IS_BIT_SET(dma_ch_flag, ETH_DMACSR_TI))
        && (STM32_IS_BIT_SET(dma_ch_itsource, ETH_DMACIER_TIE)))
    {
      /* Set Tx data event. */
      ch_data_event |= ETH_GET_TX_CH_ID(dma_ch_id);
    }

    /* Packet received in DMA Channel. */
    if ((dma_ch_id < USE_HAL_ETH_MAX_RX_CH_NB)
        && (STM32_IS_BIT_SET(dma_ch_flag, ETH_DMACSR_RI))
        && (STM32_IS_BIT_SET(dma_ch_itsource, ETH_DMACIER_RIE)))
    {
      /* Set Rx data event. */
      ch_data_event |= ETH_GET_RX_CH_ID(dma_ch_id);
    }

    /* ETH DMA Channel Error / event. */
    if ((((dma_ch_flag & ETH_DMACSR_AIS) != 0UL) && ((dma_ch_itsource & ETH_DMACIER_AIE) != 0UL))
        || (((dma_ch_flag & ETH_DMACSR_NIS) != 0UL) && ((dma_ch_itsource & ETH_DMACIER_NIE) != 0UL)))
    {
      /* If fatal error occurred. */
      if ((dma_ch_flag & ETH_ERROR_DMA_MASK) != 0UL)
      {
        /* Set error code. */
        ETH_COPY_BITS(dma_error_code, ETH_ERROR_DMA_MASK, dma_ch_flag);
        /* Disable channel interrupts. */
        ETH_DMA_CHX_DISABLE_IT(p_dma_instance,  ETH_DMACIER_NIE | ETH_DMACIER_AIE);
      }

      /* If RX channel event occurred. */
      if ((dma_ch_id < USE_HAL_ETH_MAX_RX_CH_NB)
          && (((dma_ch_flag & ETH_RX_DMA_CH_EVENT_MASK) != 0UL) || ((mtl_ch_event & ETH_RX_MTL_CH_EVENT_MASK) != 0UL)))
      {
        /* Set event code. */
        ETH_COPY_BITS(rx_ch_event, ETH_RX_DMA_CH_EVENT_MASK, dma_ch_flag);
        ETH_COPY_BITS(rx_ch_event, ETH_RX_MTL_CH_EVENT_MASK, mtl_ch_event);

        /* Call Rx channel event callback. */
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
        heth->rx_channels[dma_ch_id].p_ch_event_cb(heth, ETH_GET_RX_CH_ID(dma_ch_id), rx_ch_event);
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
        HAL_ETH_RxEventCallback(heth, ETH_GET_RX_CH_ID(dma_ch_id), rx_ch_event);
#endif  /* USE_HAL_ETH_REGISTER_CALLBACKS */
      }

      /* If TX channel event occurred. */
      if ((dma_ch_id < USE_HAL_ETH_MAX_TX_CH_NB)
          && (((dma_ch_flag & ETH_TX_DMA_CH_EVENT_MASK) != 0UL) || ((mtl_ch_event & ETH_TX_MTL_CH_EVENT_MASK) != 0UL)))
      {
        /* Set event code. */
        ETH_COPY_BITS(tx_ch_event, ETH_TX_DMA_CH_EVENT_MASK, dma_ch_flag);
        ETH_COPY_BITS(tx_ch_event, ETH_TX_MTL_CH_EVENT_MASK, mtl_ch_event);

        /* Call Tx channel event callback. */
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
        heth->tx_channels[dma_ch_id].p_ch_event_cb(heth, ETH_GET_TX_CH_ID(dma_ch_id), tx_ch_event);
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
        HAL_ETH_TxEventCallback(heth, ETH_GET_TX_CH_ID(dma_ch_id), tx_ch_event);
#endif  /* USE_HAL_ETH_REGISTER_CALLBACKS */
      }
    }

    /* Clear the ETH DMA interrupt pending bits. */
    ETH_DMA_CHX_CLEAR_IT(p_dma_instance, dma_ch_flag);
  }

  /* Call global data callback if any Tx/Rx data event occurred. */
  if (ch_data_event != 0UL)
  {
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_data_cb(heth, ch_data_event);
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_DataCallback(heth, ch_data_event);
#endif  /* USE_HAL_ETH_REGISTER_CALLBACKS */
  }

  /* Call MAC event callback if any MAC event occurred. */
  if ((mac_event_code & ETH_MAC_EVENT_MASK) != 0UL)
  {
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_event_cb(heth, (mac_event_code & ETH_MAC_EVENT_MASK));
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_EventCallback(heth, (mac_event_code & ETH_MAC_EVENT_MASK));
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
  }

  /* Check for PMT event interrupt. */
  if ((mac_status_flag & ETH_MACISR_PMTIS) != 0UL)
  {
    uint32_t mac_pmt_csr = STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACPCSR, ETH_PMT_EVENT_MASK);
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_pmt_cb(heth, mac_pmt_csr);
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_PMTCallback(heth, mac_pmt_csr);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
  }

  /* Check for EEE event interrupt. */
  if ((mac_status_flag & ETH_MACISR_LPIIS) != 0UL)
  {
    uint32_t mac_eee_csr = STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACLCSR, ETH_LPI_EVENT_MASK);
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_eee_cb(heth, mac_eee_csr);
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_EEECallback(heth, mac_eee_csr);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
  }


  /* Call error callback if any DMA error occurred. */
  if (dma_error_code != 0UL)
  {
    heth->global_state = HAL_ETH_STATE_FAULT;

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_error_cb(heth, dma_error_code);
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_ErrorCallback(heth, dma_error_code);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

#if defined (USE_HAL_ETH_GET_LAST_ERRORS) && (USE_HAL_ETH_GET_LAST_ERRORS == 1)
    heth->last_error_codes = dma_error_code;
#endif /* USE_HAL_ETH_GET_LAST_ERRORS */
  }
}

/**
  * @brief  Ethernet wakeup interrupt handler.
  *
  * This function handles Ethernet wakeup events when the wakeup source is
  * connected to an EXTI line. It checks the EXTI pending bits associated
  * with the Ethernet wakeup source, clears them, and invokes the registered
  * wakeup callback or the default @ref HAL_ETH_WakeUpCallback.
  *
  * @param[in] heth Pointer to a @ref hal_eth_handle_t structure that
  *                 contains the configuration information for the
  *                 specified Ethernet peripheral.
  *
  * @pre @p heth must not be @c NULL.
  *
  * @note This handler is intended to be used when the Ethernet wakeup
  *       interrupt is mapped to a dedicated EXTI line, separate from the
  *       main Ethernet IRQ.
  */
void HAL_ETH_WKUP_IRQHandler(const hal_eth_handle_t *heth)
{
  /* Check for EXTI line interrupt. */
  uint32_t exti_event = ETH_WakeupGetPendingIT();
  if (exti_event != 0UL)
  {
    ETH_WakeupClearPendingIT(exti_event);
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_wake_up_cb(heth);
#else /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_WakeUpCallback(heth);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
  }
}
/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group8
  * @{
This subsection provides Weak callback functions.
  - HAL_ETH_DataCallback(): Ethernet Data callback.
  - HAL_ETH_ErrorCallback(): Ethernet Error callback.
  - HAL_ETH_EventCallback(): Ethernet Event callback.
  - HAL_ETH_PMTCallback(): Ethernet PMT callback.
  - HAL_ETH_EEECallback(): Ethernet EEE callback.
  - HAL_ETH_WakeUpCallback(): Ethernet Wakeup callback.
  - HAL_ETH_CacheInvalidateCallback(): Ethernet Cache Clean callback.
  - HAL_ETH_CacheFlushCallback(): Ethernet Cache Flush callback.
  - HAL_ETH_TxEventCallback(): Ethernet Tx Channel Event callback.
  - HAL_ETH_RxEventCallback(): Ethernet Rx Channel Event callback.
  */
/**
  * @brief  Ethernet Data callback (weak implementation).
  *
  * This weak function is called by the HAL to notify the application that
  * data is available or has been processed on one or more Ethernet channels.
  * The channels are indicated by the bitmask @p channels_mask.
  *
  * Typical usages include:
  * - Notification that RX data is ready to be processed for one or more
  *   channels.
  * - Notification that TX data has been processed/completed on specific
  *   channels.
  *
  * The default implementation is empty and simply marks its parameters as
  * unused. To handle such data-related events, the user application must
  * provide a strong implementation with the same prototype and decode the
  * @p channels_mask bitmask.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral.
  * @param[in] channels_mask
  *         Bitmask indicating the channel(s) for which a data event occurred.
  *         The meaning of each bit depends on the HAL channel definitions
  *         (e.g. RX/TX channel indices).
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note It can be used as a central notification for data-related activity
  *       in addition to more specific per-channel callbacks.
  */
__weak void HAL_ETH_DataCallback(hal_eth_handle_t *heth, uint32_t channels_mask)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(channels_mask);
}

/**
  * @brief  Ethernet Peripheral error callback (weak implementation).
  *
  * This weak function is called by the HAL when one or more Ethernet-related
  * errors are detected. The specific error conditions are encoded in the
  * @p errors bitmask (e.g. DMA errors, descriptor errors, fatal bus
  * errors, etc., depending on the HAL error definitions).
  *
  * The default implementation is empty and simply marks its parameters as
  * unused. To handle Ethernet errors (e.g. log them, attempt recovery,
  * notify upper layers), the user application must provide a strong
  * implementation with the same prototype and decode the @p errors bitmask.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral where the
  *         error occurred.
  * @param[in] errors
  *         Bitmask describing the error conditions that occurred. The exact
  *         meaning of each bit depends on the Ethernet HAL error code
  *         definitions (e.g. @c HAL_ETH_ERROR_xxx).
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note It can be used together with @ref HAL_ETH_GetLastErrorCodes (when
  *       enabled) to retrieve and interpret accumulated error codes.
  * @note The following Errors are supported:
  *
  *   | Event                        | Description                                         |
  *   |------------------------------|-----------------------------------------------------|
  *   | HAL_ETH_ERROR_NONE           | No error.                                           |
  *   | HAL_ETH_ERROR_FBE            | Fatal Bus Error.                                    |
  *   | HAL_ETH_ERROR_CDE            | Context Descriptor Error.                           |
  *   | HAL_ETH_ERROR_FBE_DMA_TX_RD  | Bus Fault Error during read transfer by Tx DMA      |
  *   | HAL_ETH_ERROR_FBE_DMA_TX_WR  | Bus Fault Error during write transfer by Tx DMA     |
  *   | HAL_ETH_ERROR_FBE_DMA_TX_AC  | Bus Fault Error during descriptor access by Tx DMA  |
  *   | HAL_ETH_ERROR_FBE_DMA_RX_RD  | Bus Fault Error during read transfer by Rx DMA      |
  *   | HAL_ETH_ERROR_FBE_DMA_RX_WR  | Bus Fault Error during write transfer by Rx DMA     |
  *   | HAL_ETH_ERROR_FBE_DMA_RX_AC  | Bus Fault Error during descriptor access by Rx DMA  |
  */
__weak void HAL_ETH_ErrorCallback(hal_eth_handle_t *heth, uint32_t errors)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(errors);
}

/**
  * @brief  Ethernet Peripheral event callback (weak implementation).
  *
  * This weak function is called by the HAL to notify the application about
  * global Ethernet events represented by the bitmask @p events.
  *
  * The default implementation is empty and simply marks its parameters as
  * unused. To react to these global Ethernet events, the user application
  * must provide a strong implementation with the same prototype and decode
  * the @p events bitmask.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral.
  * @param[in] events
  *         Bitmask of Ethernet events that occurred. The exact meaning of
  *         each bit is defined by the Ethernet HAL event definitions.
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note The following Ethernet Peripheral Events are supported:
  *
  *   | Event                        | Description                 |
  *   |------------------------------|-----------------------------|
  *   | HAL_ETH_EVENT_MAC_RWT    | Receive Watchdog Timeout Event. |
  *   | HAL_ETH_EVENT_MAC_EXCOL  | Excessive Collisions Event.     |
  *   | HAL_ETH_EVENT_MAC_LCOL   | Late Collision Event.           |
  *   | HAL_ETH_EVENT_MAC_EXDEF  | Excessive Deferral Event.       |
  *   | HAL_ETH_EVENT_MAC_LCARR  | Loss of Carrier Event.          |
  *   | HAL_ETH_EVENT_MAC_NCARR  | No Carrier Event.               |
  *   | HAL_ETH_EVENT_MAC_TJT    | Transmit Jabber Timeout Event.  |
  */
__weak void HAL_ETH_EventCallback(hal_eth_handle_t *heth, uint32_t events)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(events);
}

/**
  * @brief  Ethernet Power Management and Timer (PMT) wake-up event callback (weak implementation).
  *
  * This weak function is called by the HAL to notify the application that a
  * PMT-related wake-up event has occurred on the Ethernet MAC layer. Typical
  * wake-up sources include:
  * - Magic Packet reception
  * - Remote wake-up frame match
  * - Other PMT triggers, depending on the hardware configuration.
  *
  * The default implementation is empty and simply marks its parameters as
  * unused. To handle PMT wake-up events (e.g. restore configuration, restart
  * traffic, notify upper layers), the user application must provide a
  * strong implementation with the same prototype and react to the
  * @p wake_up_event bitmask.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral that triggered
  *         the wake-up.
  * @param[in] wake_up_event
  *         Bitmask describing the PMT wake-up event(s) that occurred.
  *         The exact meaning of each bit depends on the Ethernet HAL PMT
  *         event definitions.
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note It is typically used together with power management APIs such as
  *       @ref HAL_ETH_EnterPowerDownMode and @ref HAL_ETH_ExitPowerDownMode.
  * @note The following Ethernet Peripheral PMT Events are supported:
  *
  *   | Event                           | Description                     |
  *   |---------------------------------|---------------------------------|
  *   | HAL_ETH_EVENT_PMT_MAGIC_PACKET  | Magic Packet Received.          |
  *   | HAL_ETH_EVENT_PMT_RWK_PACKET    | Remote wake-up Packet Received. |
  */
__weak void HAL_ETH_PMTCallback(hal_eth_handle_t *heth, uint32_t wake_up_event)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(wake_up_event);
}

/**
  * @brief  Ethernet Energy Efficient Ethernet (EEE) / LPI event callback (weak implementation).
  *
  * This weak function is called by the HAL to notify the application about
  * Energy Efficient Ethernet (EEE) / Low Power Idle (LPI) related events.
  * The specific event is encoded in @p lpi_event as a bitmask (for example,
  * LPI entry, LPI exit, error conditions, etc., depending on the HAL
  * definitions).
  *
  * The default implementation is empty and simply marks its parameters as
  * unused. To handle EEE/LPI events (e.g. update power statistics, adapt
  * traffic scheduling, logging), the user application must provide a strong
  * implementation with the same prototype.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral.
  * @param[in] lpi_event
  *         Bitmask describing the EEE / LPI event that occurred. The exact
  *         meaning of each bit depends on the Ethernet HAL EEE/LPI event
  *         definitions.
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note It is typically used when EEE support is enabled in the MAC/PHY and
  *       LPI events are monitored by the application together with low power
  *       interface APIs such as @ref HAL_ETH_EnterLPIMode and
  *       @ref HAL_ETH_ExitLPIMode.
  * @note The following Peripheral EEE/LPI Events are supported:
  *
  *   | Event                        | Description                          |
  *   |------------------------------|--------------------------------------|
  *   | HAL_ETH_EVENT_LPI_PLS_DOWN   | PHY Link Status is Down.             |
  *   | HAL_ETH_EVENT_LPI_PLS_UP     | PHY Link Status is Up.               |
  *   | HAL_ETH_EVENT_LPI_TX_LPI_ST  | Transmit LPI State Active.           |
  *   | HAL_ETH_EVENT_LPI_RX_LPI_ST  | Receive LPI State Active.            |
  *   | HAL_ETH_EVENT_LPI_TX_LPI_EN  | Transmit LPI State Entry performed.  |
  *   | HAL_ETH_EVENT_LPI_RX_LPI_EN  | Receive LPI State Entry performed.   |
  *   | HAL_ETH_EVENT_LPI_TX_LPI_EX  | Transmit LPI State Entry performed.  |
  *   | HAL_ETH_EVENT_LPI_RX_LPI_EX  | Receive LPI State Entry performed.   |
  */
__weak void HAL_ETH_EEECallback(hal_eth_handle_t *heth, uint32_t lpi_event)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(lpi_event);
}

/**
  * @brief  Ethernet wake-up event callback (weak implementation).
  *
  * This weak function is called by the HAL when the Ethernet MAC/PHY causes
  * a wake-up event, typically after exiting a power-down or low-power mode
  * due to a PMT trigger (e.g. Magic Packet, Remote Wakeup frame).
  *
  * The default implementation is empty and simply marks @p heth as unused.
  * To react to Ethernet wake-up events (e.g. reconfigure the interface,
  * restart transmissions, notify upper layers), the user application must
  * provide a strong implementation with the same prototype.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral that triggered
  *         the wake-up.
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note It is typically used in conjunction with power management APIs such
  *       as @ref HAL_ETH_EnterPowerDownMode and @ref HAL_ETH_ExitPowerDownMode.
  */
__weak void HAL_ETH_WakeUpCallback(const hal_eth_handle_t *heth)
{
  STM32_UNUSED(heth);
}

/**
  * @brief  Cache invalidate callback for Ethernet buffer regions (weak implementation).
  *
  * This weak function is intended to be overridden by the user application
  * when cache maintenance is required for the memory used by theEthernet peripheral.
  * It is typically called by the HAL before accessing data in memory regions that
  * can be cached, so that the CPU view of memory remains coherent with what
  * DMA has written or will read.
  *
  * The default implementation is empty and simply marks all parameters as
  * unused. If cache maintenance is needed on the target system, the user
  * must provide a strong implementation with the same prototype to perform
  * the appropriate cache invalidate operation on the buffer range
  * [@p p_addr, @p p_addr + @p size).
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral.
  * @param[in] channel
  *         Ethernet channel identifier associated with the buffer. This can be
  *         used by the user implementation to distinguish per-channel
  *         handling if needed.
  * @param[in] p_addr
  *         Pointer to the start of the memory region (buffer) to be
  *         invalidated from the CPU data cache.
  * @param[in] size
  *         Size in bytes of the memory region to be invalidated.
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note On systems without data cache, this callback can remain unimplemented.
  *
  * @sa HAL_ETH_CacheFlushCallback
  */
__weak void HAL_ETH_CacheInvalidateCallback(hal_eth_handle_t *heth, uint32_t channel, void *p_addr,
                                            uint32_t size)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(channel);
  STM32_UNUSED(p_addr);
  STM32_UNUSED(size);
}

/**
  * @brief  Cache flush (clean) callback for Ethernet buffer regions (weak implementation).
  *
  * This weak function is intended to be overridden by the user application
  * when cache maintenance is required for Ethernet RX/TX buffers before DMA
  * accesses. It is typically called by the HAL to ensure that any modified
  * data in the CPU data cache is written back to memory so that the Ethernet
  * DMA sees the latest data.
  *
  * The default implementation is empty and simply marks all parameters as
  * unused. If cache maintenance is needed on the target system, the user
  * must provide a strong implementation with the same prototype to perform
  * the appropriate cache clean/flush operation on the buffer range
  * [@p p_addr, @p p_addr + @p size).
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral.
  * @param[in] channel
  *         Ethernet channel identifier associated with the buffer. This can be
  *         used by the user implementation to distinguish per-channel
  *         handling if needed.
  * @param[in] p_addr
  *         Pointer to the start of the memory region (buffer) to be flushed
  *         (cleaned) from the CPU data cache to main memory.
  * @param[in] size
  *         Size in bytes of the memory region to be flushed.
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note On systems without data cache, this callback can remain unimplemented.
  *
  * @sa HAL_ETH_CacheInvalidateCallback
  */
__weak void HAL_ETH_CacheFlushCallback(hal_eth_handle_t *heth, uint32_t channel, void *p_addr,
                                       uint32_t size)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(channel);
  STM32_UNUSED(p_addr);
  STM32_UNUSED(size);
}

/**
  * @brief  Ethernet Transmit (TX) event callback (weak implementation).
  *
  * This weak function is invoked by the HAL to notify the application about
  * TX-related events on a given Ethernet channel. Typical events include
  * transmit complete, transmit errors, or other channel-specific conditions,
  * encoded in @p events as a bitmask.
  *
  * The default implementation is empty and simply marks all parameters as
  * unused. To handle TX events, the user application must provide a strong
  * implementation with the same prototype and perform the desired processing
  * based on the @p channel and @p events values.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral.
  * @param[in] channel
  *         TX channel identifier on which the event occurred.
  * @param[in] events
  *         Bitmask of TX events that occurred on the specified channel.
  *         The exact meaning of each bit depends on the Ethernet HAL event
  *         definitions (e.g. TX complete, TX error, etc.).
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note The HAL can also provide per-channel callbacks (registered via
  *       @ref HAL_ETH_RegisterChannelTxEventCallback) which can be used
  *       instead of this global callback.
  * @note
  *   The following events are supported:
  *
  *   | Event                       | Description                   |
  *   |-----------------------------|-------------------------------|
  *   | HAL_ETH_CH_EVENT_DMA_RBU    | Receive Buffer Unavailable.   |
  *   | HAL_ETH_CH_EVENT_DMA_TBU    | Transmit Buffer Unavailable.  |
  *   | HAL_ETH_CH_EVENT_DMA_RWT    | Receive Watchdog Timeout.     |
  *   | HAL_ETH_CH_EVENT_MTL_RX_OF  | MTL Receive Queue Overflow.   |
  *   | HAL_ETH_CH_EVENT_MTL_TX_OF  | MTL Transmit Queue Underflow. |
  *
  * @note
  *   - The callback function can be invoked in handler mode; therefore, it must
  *     execute quickly and must not perform any blocking operations.
  *   - If additional processing is required, it is recommended to defer such
  *     operations to a separate task or thread.
  *
  * @sa hal_eth_handle_t
  * @sa ETH_Channel_Event_Codes
  * @sa HAL_ETH_RegisterChannelTxEventCallback
  * @sa hal_eth_channel_cb_t
  */
__weak void HAL_ETH_TxEventCallback(hal_eth_handle_t *heth, uint32_t channel, uint32_t events)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(channel);
  STM32_UNUSED(events);
}

/**
  * @brief  Ethernet reception (RX) event callback (weak implementation).
  *
  * This weak function is invoked by the HAL to notify the application about
  * RX-related events on a given Ethernet channel. Typical events include
  * reception complete, reception errors, or other channel-specific conditions,
  * encoded in @p events as a bitmask.
  *
  * The default implementation is empty and simply marks all parameters as
  * unused. To handle RX events, the user application must provide a strong
  * implementation with the same prototype and perform the desired processing
  * based on the @p channel and @p events values.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration and state of the Ethernet peripheral.
  * @param[in] channel
  *         RX channel identifier on which the event occurred.
  * @param[in] events
  *         Bitmask of RX events that occurred on the specified channel.
  *         The exact meaning of each bit depends on the Ethernet HAL event
  *         definitions (e.g. RX complete, RX error, etc.).
  *
  * @note This function is declared as @c __weak so that it can be overridden
  *       by a user-defined implementation without modifying the HAL sources.
  * @note The HAL can also provide per-channel callbacks (registered via
  *       @ref HAL_ETH_RegisterChannelRxEventCallback) which can be used
  *       instead of this global callback.
  * @note
  *   The following events are supported:
  *
  *   | Event                       | Description                   |
  *   |-----------------------------|-------------------------------|
  *   | HAL_ETH_CH_EVENT_DMA_RBU    | Receive Buffer Unavailable.   |
  *   | HAL_ETH_CH_EVENT_DMA_TBU    | Transmit Buffer Unavailable.  |
  *   | HAL_ETH_CH_EVENT_DMA_RWT    | Receive Watchdog Timeout.     |
  *   | HAL_ETH_CH_EVENT_MTL_RX_OF  | MTL Receive Queue Overflow.   |
  *   | HAL_ETH_CH_EVENT_MTL_TX_OF  | MTL Transmit Queue Underflow. |
  *
  * @note
  *   - The callback function can be invoked in handler mode; therefore, it must
  *     execute quickly and must not perform any blocking operations.
  *   - If additional processing is required, it is recommended to defer such
  *     operations to a separate task or thread.
  *
  * @sa hal_eth_handle_t
  * @sa ETH_Channel_Event_Codes
  * @sa HAL_ETH_RegisterChannelRxEventCallback
  * @sa hal_eth_channel_cb_t
  */
__weak void HAL_ETH_RxEventCallback(hal_eth_handle_t *heth, uint32_t channel, uint32_t events)
{
  STM32_UNUSED(heth);
  STM32_UNUSED(channel);
  STM32_UNUSED(events);
}

/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group9
  * @{
  */
/**
  * @brief  Execute Ethernet TX/RX data handlers for the specified channels.
  *
  * This function processes pending TX and/or RX descriptors for the channels
  * selected by @p input_channel_mask. It walks through each selected channel,
  * locks it, inspects its descriptor list, calls user callbacks for completed
  * packets, updates descriptor state and counters, and then unlocks the
  * channel. Channels that could not be processed (locked or callback failure)
  * are reported via @p p_output_channel_mask.
  *
  * The data execution handler starts by scanning all requested Tx channels in
  * the @p input_channel_mask list, then proceeds with all Rx channels in the list.
  *
  * **TX path:**
  * - For each TX channel bit set in @p input_channel_mask:
  *   - Ensure the channel state is @ref HAL_ETH_CHANNEL_STATE_ACTIVE or
  *     @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  *   - Lock the TX channel with @ref ETH_LockChannel.
  *     - If lock fails, set the corresponding bit in @p *p_output_channel_mask
  *       and continue with the next channel.
  *   - Iterate the used TX descriptors (from
  *     @c heth->tx_channels[ch].tx_desc_list.built_desc_id):
  *     - Invalidate cache for the descriptor.
  *     - If descriptor is still owned by DMA (@ref ETH_DMA_TX_DESC_RF_OWN):
  *       stop processing this channel.
  *     - If no packet is attached (@c p_pkt_addr == NULL):
  *       - Treat it as a context descriptor and reset it.
  *     - Otherwise:
  *       - Build a @ref hal_eth_tx_cb_pkt_data_t structure with:
  *         - Status bits (FD/LD).
  *         - Error bits (IH, ED, EC, LC, NC, LOC, PC, JT).
  *         - Application context pointer (@c p_app_data).
  *       - Call the TX complete callback
  *         @c p_tx_complete_cb(heth, channel_id, p_pkt_addr, tx_cb_pkt_data).
  *         - If it returns not HAL_OK, set the channel bit in
  *           @p *p_output_channel_mask, keep the descriptor, and stop
  *           processing this channel.
  *       - If callback succeeds, reset the descriptor.
  *     - Flush cache for the descriptor.
  *     - Move to the next descriptor and decrement @c buff_in_use.
  *   - Store updated descriptor index and used count in the handle.
  *   - Unlock the TX channel with @ref ETH_UnlockChannel.
  *
  * **RX path:**
  * - For each RX channel bit set in @p input_channel_mask:
  *   - Ensure the channel state is @ref HAL_ETH_CHANNEL_STATE_ACTIVE or
  *     @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  *   - Lock the RX channel with @ref ETH_LockChannel.
  *     - If lock fails, set the channel bit in @p *p_output_channel_mask
  *       and continue with the next channel.
  *   - Iterate the used RX descriptors (from
  *     @c heth->rx_channels[ch].rx_desc_list.built_desc_id):
  *     - Invalidate cache for the descriptor.
  *     - If descriptor is still owned by DMA (@ref ETH_DMA_RX_DESC_WBF_OWN):
  *       stop processing this channel.
  *     - If descriptor is a context descriptor
  *       (@ref ETH_DMA_RX_DESC_WBF_CTXT set):
  *       - Clear its fields (backup address & context).
  *     - Otherwise:
  *       - Build a @ref hal_eth_rx_cb_pkt_data_t structure:
  *         - Read packet length from @ref ETH_DMA_RX_DESC_WBF_PL.
  *         - Set status bits (FD/LD).
  *         - If LD is set:
  *           - Copy additional status bits (IPCB, IPv4, IPv6, ARPNR, VLAN)
  *             from DESC1/DESC2/DESC3.
  *           - If VLAN present:
  *             - Copy VLAN tag value from DESC0 into @c vlan_tag_ids.
  *         - Set error bits using DESC1/DESC3 (IPH, IPC, DB, REC, OFL,
  *           RWT, GP, CRC).
  *         - Set application context from @c p_app_data.
  *       - Call the RX complete callback
  *         @c p_rx_complete_cb(heth, channel_id, p_pkt_addr, rec_pkt_size,
  *                             rx_pkt_data).
  *         - If it returns not HAL_OK, set the channel bit in
  *           @p *p_output_channel_mask, keep the descriptor, and stop
  *           processing this channel.
  *       - If callback succeeds, reset the descriptor.
  *     - Flush cache for the descriptor.
  *     - Move to the next descriptor and decrement @c buff_in_use.
  *   - Store updated descriptor index and used count in the handle.
  *   - Call \c ETH_updateRxDesc to replenish RX descriptors.
  *   - Unlock the RX channel with @ref ETH_UnlockChannel.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure containing the
  *         configuration and runtime state for the Ethernet peripheral.
  *         Its @c tx_channels[] and @c rx_channels[] descriptor lists are
  *         updated by this function.
  * @param[in]     input_channel_mask
  *         Bitmask indicating which channels to process. It can contain:
  *         - TX channel bits (subset of @ref HAL_ETH_TX_CHANNEL_ALL).
  *         - RX channel bits (subset of @ref HAL_ETH_RX_CHANNEL_ALL).
  *         Both TX and RX handling are performed if both groups are present.
  * @param[in,out] p_output_channel_mask
  *         Pointer to a bitmask used to report channels that could not be
  *         fully processed. On input, the value can contain an initial mask
  *         (typically 0). On output, bits are set for channels where:
  *         - The channel is locked (could not be acquired).
  *         - The user TX/RX complete callback returned an error
  *           (descriptor kept for next execution).
  *
  * @retval HAL_OK
  *         Data handler executed; channels requiring further processing are
  *         indicated via @p *p_output_channel_mask.
  * @retval HAL_INVALID_PARAM
  *         @p heth or @p p_output_channel_mask is @c NULL (only when
  *         parameter checking is enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @pre
  * - @p heth must not be @c NULL.
  * - @p p_output_channel_mask must not be @c NULL.
  * - @p heth->global_state must be @ref HAL_ETH_STATE_CONFIGURED (checked
  *   with debug and optional runtime checks).
  *
  * @note Cache maintenance is performed either via user-registered callbacks
  *       (@c p_cache_invalidate_cb, @c p_cache_flush_cb) when
  *       @c USE_HAL_ETH_REGISTER_CALLBACKS is enabled, or via the weak
  *       default implementations @ref HAL_ETH_CacheInvalidateCallback and
  *       @ref HAL_ETH_CacheFlushCallback otherwise.
  * @note This function does not start or stop channels; it only processes
  *       descriptors for channels that are already active or suspended.
  * @note This function is not intended to be called from a handler execution
  *       mode (interrupt context). In a bare-metal integration, the application
  *       must implement a deferred call mechanism so that it is invoked later
  *      from thread mode (process context).
  */
hal_status_t HAL_ETH_ExecDataHandler(hal_eth_handle_t *heth, uint32_t input_channel_mask,
                                     uint32_t *p_output_channel_mask)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_output_channel_mask != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_MASK(input_channel_mask));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_output_channel_mask == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /*------------------ Exec Tx Handler ----------------------*/
  if ((input_channel_mask & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_TX_CH_NB; ch++)
    {
      if ((input_channel_mask & ETH_GET_TX_CH_ID(ch)) != 0UL)
      {
        ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE |
                         (uint32_t)HAL_ETH_CHANNEL_STATE_SUSPENDED);
        /* lock the Tx Channel */
        if (ETH_LockChannel(&heth->tx_channels[ch].channel_lock_state) != HAL_OK)
        {
          /* Channel is locked, return channel ID */
          *p_output_channel_mask |= ETH_GET_TX_CH_ID(ch);
          continue;
        }

        eth_dma_descriptor_t *p_dma_txDesc;
        uint32_t tx_desc_idx        = heth->tx_channels[ch].tx_desc_list.built_desc_id;
        uint32_t tx_total_used_desc = heth->tx_channels[ch].tx_desc_list.buff_in_use;
        uint32_t tx_process_completed = 0UL;

        while ((tx_total_used_desc != 0UL) && (tx_process_completed == 0UL))
        {
          /* get current built dma descriptor*/
          p_dma_txDesc = ETH_GET_DESC_INDEX(heth->tx_channels[ch].tx_desc_list, tx_desc_idx);

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
          /* cache invalidate descriptor */
          heth->p_cache_invalidate_cb(heth, ETH_GET_TX_CH_ID(ch),
                                      p_dma_txDesc, heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
          HAL_ETH_CacheInvalidateCallback(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                                          heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

          /* Determine if the packet transmitted */
          if ((p_dma_txDesc->DESC3 & ETH_DMA_TX_DESC_RF_OWN) == 0UL)
          {
            /*If No Packet attached,  reset descriptor and pass to next one .  */
            if (p_dma_txDesc->p_pkt_addr == NULL)
            {
              /*Context Descriptor, reset Desc */
              ETH_ResetDMADesc(p_dma_txDesc);
            }
            else
            {
              hal_eth_tx_cb_pkt_data_t tx_cb_pkt_data = {0};

              /* Set Desc status */
              ETH_COPY_BITS(tx_cb_pkt_data.status, HAL_ETH_TX_STATUS_FD | HAL_ETH_TX_STATUS_LD, p_dma_txDesc->DESC3);

              /* Set Desc errors */
              ETH_COPY_BITS(tx_cb_pkt_data.errors, (HAL_ETH_TX_ERROR_IH | HAL_ETH_TX_ERROR_ED |
                                                    HAL_ETH_TX_ERROR_EC | HAL_ETH_TX_ERROR_LC |
                                                    HAL_ETH_TX_ERROR_NC | HAL_ETH_TX_ERROR_LOC |
                                                    HAL_ETH_TX_ERROR_PC | HAL_ETH_TX_ERROR_JT), p_dma_txDesc->DESC3);
              /* Set Application context */
              STM32_WRITE_REG(tx_cb_pkt_data.p_data, p_dma_txDesc->p_app_data);

              /* Call channel Tx complete callback */
              if (heth->tx_channels[ch].p_tx_complete_cb(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc->p_pkt_addr,
                                                         tx_cb_pkt_data) != HAL_OK)
              {
                /* tx_complete fail, return channel ID and keep the descriptor for the next iteration */
                *p_output_channel_mask |= ETH_GET_TX_CH_ID(ch);
                break;
              }
              /* p_tx_complete_cb succeeded, reset Desc */
              ETH_ResetDMADesc(p_dma_txDesc);
            }
            /* Cache flush descriptor */
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
            heth->p_cache_flush_cb(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                                   heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
            HAL_ETH_CacheFlushCallback(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                                       heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

            /* Pass to next desc */
            ETH_INCR_DESC_INDEX(tx_desc_idx, heth->tx_channels[ch].tx_desc_list.total_desc_cnt);

            /* Decriment total used desc */
            tx_total_used_desc--;
          }
          else
          {
            /* Still owned by DMA, exit the loop */
            tx_process_completed = 1UL;
          }
        }

        /* Write back total used buffers */
        heth->tx_channels[ch].tx_desc_list.buff_in_use = tx_total_used_desc;
        heth->tx_channels[ch].tx_desc_list.built_desc_id = tx_desc_idx;

        /* Unlock the Tx Channel */
        ETH_UnlockChannel(&heth->tx_channels[ch].channel_lock_state);
      }
    }
  }
  /*------------------ Exec Rx Handler ----------------------*/
  if ((input_channel_mask & HAL_ETH_RX_CHANNEL_ALL) != 0UL)
  {
    for (uint32_t ch = 0; ch < USE_HAL_ETH_MAX_RX_CH_NB; ch++)
    {
      if ((input_channel_mask & ETH_GET_RX_CH_ID(ch)) != 0UL)
      {
        ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE |
                         (uint32_t)HAL_ETH_CHANNEL_STATE_SUSPENDED);
        /* Lock the Rx Channel */
        if (ETH_LockChannel(&heth->rx_channels[ch].channel_lock_state) != HAL_OK)
        {
          /* Channel is locked, return channel ID */
          *p_output_channel_mask |= ETH_GET_RX_CH_ID(ch);
          continue;
        }

        eth_dma_descriptor_t *p_dma_RxDesc;
        uint32_t rx_desc_idx        = heth->rx_channels[ch].rx_desc_list.built_desc_id;
        uint32_t rx_total_used_desc = heth->rx_channels[ch].rx_desc_list.buff_in_use;
        uint32_t rx_process_completed = 0UL;

        while ((rx_total_used_desc != 0UL) && (rx_process_completed == 0UL))
        {
          /* Get current built Rx dma descriptor*/
          p_dma_RxDesc = ETH_GET_DESC_INDEX(heth->rx_channels[ch].rx_desc_list, rx_desc_idx);
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
          /* Cache invalidate descriptor */
          heth->p_cache_invalidate_cb(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                                      heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
          HAL_ETH_CacheInvalidateCallback(heth, ETH_GET_RX_CH_ID(ch),
                                          p_dma_RxDesc, heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

          /* Determine if the packet Received */
          if (STM32_READ_BIT(p_dma_RxDesc->DESC3, ETH_DMA_RX_DESC_WBF_OWN) == 0UL)
          {
            /* Determine if a context descriptor */
            if (STM32_READ_BIT(p_dma_RxDesc->DESC3, ETH_DMA_RX_DESC_WBF_CTXT) != 0UL)
            {
              /* context descriptor keep the backup address and application context */
              STM32_WRITE_REG(p_dma_RxDesc->DESC0, 0x0UL);
              STM32_WRITE_REG(p_dma_RxDesc->DESC1, 0x0UL);
              STM32_WRITE_REG(p_dma_RxDesc->DESC2, 0x0UL);
              STM32_WRITE_REG(p_dma_RxDesc->DESC3, 0x0UL);
            }
            else
            {
              hal_eth_rx_cb_pkt_data_t rx_pkt_data = {0};

              /* Write received pkt size */
              uint32_t rec_pkt_size = STM32_READ_BIT(p_dma_RxDesc->DESC3, ETH_DMA_RX_DESC_WBF_PL);

              /* set the received packet status */
              ETH_COPY_BITS(rx_pkt_data.status, (HAL_ETH_RX_STATUS_FD | HAL_ETH_RX_STATUS_LD), p_dma_RxDesc->DESC3);

              /* Determine if a last descriptor */
              if (STM32_READ_BIT(p_dma_RxDesc->DESC3, HAL_ETH_RX_STATUS_LD) != 0UL)
              {
                ETH_COPY_BITS(rx_pkt_data.status, (HAL_ETH_RX_STATUS_IPCB | HAL_ETH_RX_STATUS_IPV4 |
                                                   HAL_ETH_RX_STATUS_IPV6), p_dma_RxDesc->DESC1);

                ETH_COPY_BITS(rx_pkt_data.status, HAL_ETH_RX_STATUS_ARPNR, p_dma_RxDesc->DESC2);
                ETH_COPY_BITS(rx_pkt_data.status, HAL_ETH_RX_STATUS_VLAN, p_dma_RxDesc->DESC3);

                /* Last Descriptor check if VLAN Tag received*/
                if (STM32_READ_BIT(p_dma_RxDesc->DESC3, HAL_ETH_RX_STATUS_VLAN) != 0UL)
                {
                  /* set vlan tag present status*/
                  ETH_COPY_BITS(rx_pkt_data.status, HAL_ETH_RX_STATUS_VLAN, p_dma_RxDesc->DESC3);
                  /* copy vlan tag value */
                  STM32_WRITE_REG(rx_pkt_data.vlan_tag_ids, p_dma_RxDesc->DESC0);
                }
              }

              /* set the received packet errors */
              if (STM32_READ_BIT(p_dma_RxDesc->DESC1, (HAL_ETH_RX_STATUS_IPV4 | HAL_ETH_RX_STATUS_IPV6)) != 0UL)
              {
                if (STM32_READ_BIT(p_dma_RxDesc->DESC1, HAL_ETH_RX_ERROR_IPH) != 0UL)
                {
                  /* set IP header error */
                  ETH_COPY_BITS(rx_pkt_data.errors, HAL_ETH_RX_ERROR_IPH, p_dma_RxDesc->DESC1);
                }
              }
              /* set Errors*/
              ETH_COPY_BITS(rx_pkt_data.errors, HAL_ETH_RX_ERROR_IPC, p_dma_RxDesc->DESC1);
              ETH_COPY_BITS(rx_pkt_data.errors, (HAL_ETH_RX_ERROR_DB | HAL_ETH_RX_ERROR_REC
                                                 | HAL_ETH_RX_ERROR_OFL | HAL_ETH_RX_ERROR_RWT
                                                 | HAL_ETH_RX_ERROR_GP | HAL_ETH_RX_ERROR_CRC), p_dma_RxDesc->DESC3);
              /* Set Application context */
              STM32_WRITE_REG(rx_pkt_data.p_data, p_dma_RxDesc->p_app_data);
              /*call channel Rx complete callback */
              if (heth->rx_channels[ch].p_rx_complete_cb(heth, ETH_GET_RX_CH_ID(ch),
                                                         p_dma_RxDesc->p_pkt_addr, rec_pkt_size,
                                                         rx_pkt_data) != HAL_OK)
              {
                /* rx_complete fail, return channel ID and keep the descriptor for the next iteration*/
                *p_output_channel_mask |= ETH_GET_RX_CH_ID(ch);
                break;
              }
              /* p_rx_complete_cb succeeded, resetle Desc */
              ETH_ResetDMADesc(p_dma_RxDesc);
            }
            /* cache flush descriptor */
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
            heth->p_cache_flush_cb(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                                   heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
            HAL_ETH_CacheFlushCallback(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                                       heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

            /* pass to next desc */
            ETH_INCR_DESC_INDEX(rx_desc_idx, heth->rx_channels[ch].rx_desc_list.total_desc_cnt);
            /* decriment total used desc*/
            rx_total_used_desc--;
          }
          else
          {
            /* no more packet to process */
            rx_process_completed = 1UL;
          }
        }

        /* write back total used buffers */
        heth->rx_channels[ch].rx_desc_list.buff_in_use = rx_total_used_desc;
        heth->rx_channels[ch].rx_desc_list.built_desc_id = rx_desc_idx;
        /* update Rx Descriptors */
        ETH_UpdateRxDesc(heth, ch);
        /* lock the Rx Channel */
        ETH_UnlockChannel(&heth->rx_channels[ch].channel_lock_state);
      }
    }
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Request transmission of a packet on the specified TX channel.
  *
  * This function prepares and queues one Ethernet packet for transmission
  * on a given TX channel by configuring the corresponding DMA descriptors.
  * The packet is described by an array of buffers @p p_buff_array and
  * a TX configuration structure @p p_tx_conf.
  *
  * The function:
  * - Validates parameters and channel index.
  * - Translates the @p channel bitmask into a TX channel index via
  *   @ref ETH_GetTXChIndex.
  * - Checks that the TX channel state is
  *   @ref HAL_ETH_CHANNEL_STATE_ACTIVE or
  *   @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  * - Locks the TX channel using @ref ETH_LockChannel; if the channel is
  *   already locked, it returns HAL_BUSY.
  * - Prepare DMA TX descriptors for the
  *   specified buffers and configuration.
  * - Unlocks the TX channel and returns the status.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains
  *         the configuration and runtime state of the Ethernet peripheral.
  * @param[in]     channel
  *         TX channel identifier (bitmask), must satisfy
  *         @ref IS_ETH_CHANNEL_TX_INDEX. If multiple bits are set, only the
  *         resolved channel index returned by @ref ETH_GetTXChIndex is used.
  * @param[in]     p_buff_array
  *         Pointer to an array of @ref hal_eth_buffer_t structures describing
  *         the buffer(s) that make up the packet to transmit (address and size).
  * @param[in]     buf_count
  *         Number of elements in @p p_buff_array.
  * @param[in]     p_tx_conf
  *         Pointer to a @ref hal_eth_tx_pkt_config_t structure that contains
  *         per-packet TX configuration (e.g. checksums, VLAN tagging, etc.).
  *
  * @retval HAL_OK
  *         The packet was successfully queued for transmission via DMA.
  * @retval HAL_BUSY
  *         - The specified TX channel is currently locked and cannot accept
  *         a new transmission request.
  *         - Not enough free descriptors available to queue the packet.
  * @retval HAL_INVALID_PARAM
  *         - @p heth, @p p_buff_array, or @p p_tx_conf is @c NULL, or
  *         - @p channel is invalid (IS_ETH_CHANNEL_TX_INDEX() returns 0),
  *         and parameter checking is enabled via @c USE_HAL_CHECK_PARAM.
  *
  * @pre
  * - @p heth must have been initialized and configured
  *   (@ref HAL_ETH_Init + @ref HAL_ETH_SetConfig).
  * - @p heth->global_state must be @ref HAL_ETH_STATE_CONFIGURED
  *   (checked with debug and optional runtime checks).
  * - The TX channel must be in
  *   @ref HAL_ETH_CHANNEL_STATE_ACTIVE or
  *   @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  *
  * @note This function only prepares the DMA descriptors; the current start
  *       of transmission depends on the number of already queued packets
  *       which are still pending for execution by the Ethernet DMA engine.
  *
  * @sa HAL_ETH_ExecDataHandler
  */
hal_status_t HAL_ETH_RequestTx(hal_eth_handle_t *heth, uint32_t channel, hal_eth_buffer_t *p_buff_array,
                               uint32_t buf_count, hal_eth_tx_pkt_config_t *p_tx_conf)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_buff_array != NULL);
  ASSERT_DBG_PARAM(p_tx_conf != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_TX_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_buff_array == NULL) || (p_tx_conf == NULL) || (IS_ETH_CHANNEL_TX_INDEX(channel) == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  hal_status_t return_status;
  uint32_t ch;
  /* Retrieve the Channel Id */
  ETH_GetTXChIndex(&ch, channel);

  ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE |
                   (uint32_t)HAL_ETH_CHANNEL_STATE_SUSPENDED);
  /* Lock Tx Channel */
  if (ETH_LockChannel(&heth->tx_channels[ch].channel_lock_state) != HAL_OK)
  {
    /* Channel is locked */
    return HAL_BUSY;
  }

  /* Prepare DMA Tx descriptors for transmission */
  return_status = ETH_RequestTxDMA(heth, ch, p_buff_array, buf_count, p_tx_conf);

  /* Unlock Tx Channel */
  ETH_UnlockChannel(&heth->tx_channels[ch].channel_lock_state);

  return return_status;
}

/**
  * @brief  Start an Ethernet TX or RX channel.
  *
  * This function initializes the descriptor list and starts either a TX or RX
  * channel, depending on the @p channel identifier. It configures DMA and MTL
  * for the selected channel, enables the required DMA/MAC interrupts, and
  * starts the corresponding DMA and MAC data path.
  *
  * The descriptor memory @p p_desc_mem must be aligned on the bus data width
  * (ETH_BUS_DATA_WIDTH_BYTE) and large enough to hold all descriptors for
  * the selected channel.
  *
  * **TX channel start:**
  * - Derive TX channel index via @ref ETH_GetTXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_CONFIGURED.
  * - Check mandatory TX callback @c p_tx_complete_cb is registered.
  * - Move channel state to @ref HAL_ETH_CHANNEL_STATE_ACTIVE using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Initialize TX descriptor list with @ref ETH_DMATxDescListInit.
  * - Enable TX DMA interrupts (NIE, AIE, CDEE, FBEE, TIE).
  * - Flush TX FIFO, start DMA TX, clear TX stopped status, enable MAC TX.
  *
  * **RX channel start:**
  * - Derive RX channel index via @ref ETH_GetRXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_CONFIGURED.
  * - Check mandatory RX callbacks @c p_rx_complete_cb and
  *   @c p_rx_allocate_cb are registered.
  * - Move channel state to @ref HAL_ETH_CHANNEL_STATE_ACTIVE using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Initialize RX descriptor list with @ref ETH_DMARxDescListInit.
  * - Enable RX DMA interrupts (NIE, AIE, CDEE, FBEE, RIE, RBUE).
  * - Start DMA RX and enable MAC RX.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and runtime state for the Ethernet
  *         peripheral.
  * @param[in]     channel
  *         Channel identifier that must satisfy
  *         @ref IS_ETH_CHANNEL_INDEX. If it matches any bit in
  *         @ref HAL_ETH_TX_CHANNEL_ALL, a TX channel is started; otherwise
  *         an RX channel is started.
  * @param[in]     p_desc_mem
  *         Pointer to the descriptor memory area for the selected channel.
  *         Must be aligned on @c ETH_BUS_DATA_WIDTH_BYTE.
  * @param[in]     desc_size_byte
  *         Size in bytes of the descriptor memory region pointed to by
  *         @p p_desc_mem.
  *
  * @retval HAL_OK
  *         The channel was successfully started.
  * @retval HAL_INVALID_PARAM
  *         - @p heth or @p p_desc_mem is @c NULL, or
  *         - @p channel is invalid (IS_ETH_CHANNEL_INDEX() returns 0), or
  *         - @p p_desc_mem is not aligned to ETH_BUS_DATA_WIDTH_BYTE, or
  *         - Mandatory @p p_tx_complete_cb callback for the selected channel
  *         is not set.
  *
  * @pre
  * - @p heth must have been initialized and configured
  *   (@ref HAL_ETH_Init + @ref HAL_ETH_SetConfig).
  * - @p heth->global_state must be @ref HAL_ETH_STATE_CONFIGURED
  *   (checked with debug and optional runtime checks).
  * - The selected channel must be in @ref HAL_ETH_CHANNEL_STATE_CONFIGURED.
  *
  * @note This function does not allocate data buffers; it only initializes
  *       descriptor lists and starts the hardware for the given channel.
  * @note For RX channels, the @c p_rx_allocate_cb callback is expected to
  *       allocate and attach buffers to the RX descriptors during operation.
  *
  * @sa ETH_GetTXChIndex
  * @sa ETH_GetRXChIndex
  * @sa ETH_DMATxDescListInit
  * @sa ETH_DMARxDescListInit
  */
hal_status_t HAL_ETH_StartChannel(hal_eth_handle_t *heth, uint32_t channel, uint32_t *p_desc_mem,
                                  uint32_t desc_size_byte)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_desc_mem != NULL);
  ASSERT_DBG_PARAM(((uint32_t)p_desc_mem % ETH_BUS_DATA_WIDTH_BYTE) == 0UL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_desc_mem == NULL) || (IS_ETH_CHANNEL_INDEX(channel) == 0U)
      || (((uint32_t)p_desc_mem % ETH_BUS_DATA_WIDTH_BYTE) != 0))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t ch;

  if ((channel & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    /*--------------------- Start Tx Channel --------------------------*/
    /* Retrieve the Channel Id */
    ETH_GetTXChIndex(&ch, channel);

    ASSERT_DBG_PARAM(IS_ETH_DESC_SIZE_BYTE_VALID(desc_size_byte, heth->tx_channels[ch].tx_desc_list.desc_len_byte));
    ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED);

    if (heth->tx_channels[ch].p_tx_complete_cb == NULL)
    {
      return HAL_INVALID_PARAM;
    }

    /* Move channel state to active */
    ETH_STATES_CHECK_UPDATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED,
                            HAL_ETH_CHANNEL_STATE_ACTIVE);

    ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);
    ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_MTL_GET_TX_INSTANCE(heth, ch);

    /* Initialize DMA TX Descriptors list */
    ETH_DMATxDescListInit(heth, ch, p_desc_mem, desc_size_byte);

    /* DSB instruction to avoid race condition */
    __DSB();

    /* Enable ETH DMA interrupts:*/
    ETH_DMA_CHX_ENABLE_IT(p_dma_instance, (ETH_DMACIER_NIE | ETH_DMACIER_AIE | ETH_DMACIER_CDEE
                                           | ETH_DMACIER_FBEE | ETH_DMACIER_TIE));

    /* Set the Flush Transmit FIFO bit */
    STM32_SET_BIT(p_mtl_instance->MTLTXQXOMR, ETH_MTLTXQOMR_FTQ);

    /* Enable the DMA transmission */
    STM32_SET_BIT(p_dma_instance->DMACXTXCR, ETH_DMACTXCR_ST);

    /* Clear Tx process stopped flags */
    STM32_CLEAR_BIT(p_dma_instance->DMACXSR, (ETH_DMACSR_TPS));

    /* Enable the MAC transmission */
    STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_TE);
  }
  else
  {
    /*--------------------- Start Rx Channel --------------------------*/
    /* Retrieve the Channel Id */
    ETH_GetRXChIndex(&ch, channel);

    ASSERT_DBG_PARAM(IS_ETH_DESC_SIZE_BYTE_VALID(desc_size_byte, heth->rx_channels[ch].rx_desc_list.desc_len_byte));
    ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED);

    /* Check for registered Rx mandatory callbacks */
    if ((heth->rx_channels[ch].p_rx_complete_cb == NULL) || (heth->rx_channels[ch].p_rx_allocate_cb == NULL))
    {
      return HAL_INVALID_PARAM;
    }

    /* Move channel state to started */
    ETH_STATES_CHECK_UPDATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED,
                            HAL_ETH_CHANNEL_STATE_ACTIVE);

    ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);

    /* Initialize DMA TX Descriptors list */
    ETH_DMARxDescListInit(heth, ch, p_desc_mem, desc_size_byte);

    /* Enable ETH DMA interrupts */
    ETH_DMA_CHX_ENABLE_IT(p_dma_instance, (ETH_DMACIER_NIE | ETH_DMACIER_AIE
                                           | ETH_DMACIER_CDEE | ETH_DMACIER_FBEE
                                           | ETH_DMACIER_RIE | ETH_DMACIER_RBUE));

    /* Enable the DMA reception */
    STM32_SET_BIT(p_dma_instance->DMACXRXCR, ETH_DMACRXCR_SR);
    /* Enable the MAC reception */
    STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_RE);
  }

  return HAL_OK;
}

/**
  * @brief  Stop an Ethernet TX or RX channel.
  *
  * This function stops either a TX or RX channel, depending on the
  * @p channel identifier. It updates the channel state, acquires the channel
  * lock, calls the appropriate low-level stop routine, and then releases
  * the lock.
  *
  * **TX channel stop:**
  * - Determine TX channel index via @ref ETH_GetTXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  * - Move channel state to @ref HAL_ETH_CHANNEL_STATE_CONFIGURED using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Lock the TX channel via @ref ETH_LockChannel;
  *   - On failure, restore state to @ref HAL_ETH_CHANNEL_STATE_ACTIVE and
  *     return HAL_BUSY.
  * - Call @ref ETH_StopTxChannel to stop DMA/MTL/MAC on this TX channel.
  * - Unlock the channel.
  *
  * **RX channel stop:**
  * - Determine RX channel index via @ref ETH_GetRXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  * - Move channel state to @ref HAL_ETH_CHANNEL_STATE_CONFIGURED using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Lock the RX channel via @ref ETH_LockChannel;
  *   - On failure, restore state to @ref HAL_ETH_CHANNEL_STATE_ACTIVE and
  *     return HAL_BUSY.
  * - Call @ref ETH_StopRxChannel to stop DMA/MTL/MAC on this RX channel.
  * - Unlock the channel.
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and runtime state for the Ethernet
  *         peripheral.
  * @param[in]     channel
  *         Channel identifier (bitmask) that must satisfy
  *         @ref IS_ETH_CHANNEL_INDEX. If it intersects
  *         @ref HAL_ETH_TX_CHANNEL_ALL, a TX channel is stopped;
  *         otherwise an RX channel is stopped.
  *
  * @retval HAL_OK
  *         The selected channel was successfully stopped.
  * @retval HAL_BUSY
  *         The selected channel could not be locked for stopping; its state
  *         is restored to @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  * @retval HAL_ERROR
  *         Channel index could not be derived from @p channel
  *         (@ref ETH_GetTXChIndex / @ref ETH_GetRXChIndex failed).
  * @retval HAL_INVALID_PARAM
  *         - @p heth is @c NULL, or
  *         - @p channel is invalid (IS_ETH_CHANNEL_INDEX() returns 0),
  *         and parameter checking is enabled via @c USE_HAL_CHECK_PARAM.
  *
  * @pre
  * - The selected channel must be in @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  * - @p heth must have been initialized and configured.
  *
  * @note This function does not de-initialize the descriptor lists; it only
  *       stops the DMA/MAC activity for the specified channel. Descriptors
  *       can be reused after restarting the channel.
  *
  * @sa HAL_ETH_StartChannel
  * @sa ETH_StopTxChannel
  * @sa ETH_StopRxChannel
  */
hal_status_t HAL_ETH_StopChannel(hal_eth_handle_t *heth, uint32_t channel)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (IS_ETH_CHANNEL_INDEX(channel) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t    ch;
  hal_status_t return_status;

  if ((channel & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    /*--------------------- Stop Tx Channel --------------------------*/
    /* Retrieve Tx Channel Id */
    ETH_GetTXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE);
    /* move channel state to Configured */
    ETH_STATES_CHECK_UPDATE(heth->tx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE,
                            HAL_ETH_CHANNEL_STATE_CONFIGURED);

    /* Lock the Tx Channel */
    if (ETH_LockChannel(&heth->tx_channels[ch].channel_lock_state) != HAL_OK)
    {
      heth->tx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_ACTIVE;
      return HAL_BUSY;
    }
    /* Stop Tx Channel */
    return_status = ETH_StopTxChannel(heth, ch);

    /* Unlock the Tx Channel */
    ETH_UnlockChannel(&heth->tx_channels[ch].channel_lock_state);
  }
  else
  {
    /*--------------------- Stop Rx Channel --------------------------*/
    /* Retrieve Rx Channel Id */
    ETH_GetRXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE);
    /* move channel state to configured */
    ETH_STATES_CHECK_UPDATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE,
                            HAL_ETH_CHANNEL_STATE_CONFIGURED);
    /* lock the Rx Channel */
    if (ETH_LockChannel(&heth->rx_channels[ch].channel_lock_state) != HAL_OK)
    {
      heth->rx_channels[ch].channel_state = HAL_ETH_CHANNEL_STATE_ACTIVE;
      return HAL_BUSY;
    }

    /* Stop Rx Channel */
    return_status = ETH_StopRxChannel(heth, ch);

    /* Unlock the Rx Channel */
    ETH_UnlockChannel(&heth->rx_channels[ch].channel_lock_state);
  }

  return return_status;
}

/**
  * @brief  Suspend an Ethernet TX or RX channel.
  *
  * This function suspends activity on either a TX or RX channel, depending on
  * the @p channel bitmask. For TX channels, it stops the DMA transmission and
  * waits for the queue to drain; for RX channels, it stops the DMA reception.
  * The channel state is updated from @ref HAL_ETH_CHANNEL_STATE_ACTIVE to
  * @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  *
  * **TX channel suspend:**
  * - Determine TX channel index via @ref ETH_GetTXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  * - Update channel state to @ref HAL_ETH_CHANNEL_STATE_SUSPENDED using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Disable TX DMA transmission (clear @c TXCR_ST).
  * - Wait for the MTL TX queue to finish the current transfer by polling
  *   @c MTLTXQXDR until the queue status bits (e.g. @c TXQSTS) are cleared or
  *   @ref ETH_TX_DMA_STOP_TIMEOUT elapses.
  *
  * **RX channel suspend:**
  * - Determine RX channel index via @ref ETH_GetRXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  * - Update channel state to @ref HAL_ETH_CHANNEL_STATE_SUSPENDED using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Disable RX DMA reception (clear @c RXCR_SR).
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and runtime state for the Ethernet
  *         peripheral.
  * @param[in]     channel
  *         Channel identifier (bitmask) that must satisfy
  *         @ref IS_ETH_CHANNEL_INDEX. If it intersects
  *         @ref HAL_ETH_TX_CHANNEL_ALL, a TX channel is suspended;
  *         otherwise an RX channel is suspended.
  *
  * @retval HAL_OK
  *         The selected channel was successfully suspended.
  * @retval HAL_ERROR
  *         - Channel index could not be derived from @p channel, or
  *         - Timeout occurred while waiting for the TX queue to drain.
  * @retval HAL_INVALID_PARAM
  *         - @p heth is @c NULL, or
  *         - @p channel is invalid (IS_ETH_CHANNEL_INDEX() returns 0),
  *         and parameter checking is enabled via @c USE_HAL_CHECK_PARAM.
  *
  * @pre
  * - The selected channel must be in @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  * - @p heth must have been initialized and configured.
  *
  * @note This API only suspends the DMA path; descriptors and channel
  *       configuration are preserved and can be resumed later by a dedicated
  *       resume/start API.
  *
  * @sa HAL_ETH_StartChannel
  * @sa HAL_ETH_StopChannel
  */
hal_status_t HAL_ETH_SuspendChannel(hal_eth_handle_t *heth, uint32_t channel)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (IS_ETH_CHANNEL_INDEX(channel) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t tickstart;
  uint32_t ch;

  if ((channel & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    /*--------------------- Suspend Tx Channel --------------------------*/
    /* Retrieve Tx Channel Id */
    ETH_GetTXChIndex(&ch, channel);

    ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state, HAL_ETH_CHANNEL_STATE_ACTIVE);

    /* Move channel state to SUSPENDED */
    ETH_STATES_CHECK_UPDATE(heth->tx_channels[ch].channel_state,
                            (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE,
                            HAL_ETH_CHANNEL_STATE_SUSPENDED);

    ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);

    /* Stop Tx DMA transmission */
    STM32_CLEAR_BIT(p_dma_instance->DMACXTXCR, ETH_DMACTXCR_ST);

    /* Wait for the DMA TX process to stop */
    tickstart = HAL_GetTick();
    while (ETH_DMA_GetTxProcessState(ETH_GET_INSTANCE(heth), ch) != ETH_TX_DMA_PROCESS_STOPPED)
    {
      if ((HAL_GetTick() - tickstart) > ETH_TX_DMA_STOP_TIMEOUT)
      {
        return HAL_ERROR;
      }
    }
  }
  else
  {
    /*--------------------- Suspend Rx Channel --------------------------*/
    /* Retrieve Rx Channel Id */
    ETH_GetRXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE);
    /* move channel state to suspended */
    ETH_STATES_CHECK_UPDATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE,
                            HAL_ETH_CHANNEL_STATE_SUSPENDED);

    ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);
    /* Disable Rx DMA reception */
    STM32_CLEAR_BIT(p_dma_instance->DMACXRXCR, ETH_DMACRXCR_SR);

    /* Wait for the DMA RX process to stop */
    tickstart = HAL_GetTick();
    while (ETH_DMA_GetRxProcessState(ETH_GET_INSTANCE(heth), ch) != ETH_RX_DMA_PROCESS_STOPPED)
    {
      if ((HAL_GetTick() - tickstart) > ETH_RX_DMA_STOP_TIMEOUT)
      {
        return HAL_ERROR;
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Resume a previously suspended Ethernet TX or RX channel.
  *
  * This function resumes DMA activity on either a TX or RX channel, depending
  * on the @p channel bitmask. It updates the channel state from
  * @ref HAL_ETH_CHANNEL_STATE_SUSPENDED back to
  * @ref HAL_ETH_CHANNEL_STATE_ACTIVE and reenables the corresponding DMA
  * control bit.
  *
  * **TX channel resume:**
  * - Determine TX channel index via @ref ETH_GetTXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  * - Update channel state to @ref HAL_ETH_CHANNEL_STATE_ACTIVE using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Enable TX DMA transmission (set @c TXCR_ST).
  *
  * **RX channel resume:**
  * - Determine RX channel index via @ref ETH_GetRXChIndex.
  * - Check channel state is @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  * - Update channel state to @ref HAL_ETH_CHANNEL_STATE_ACTIVE using
  *   @ref ETH_STATES_CHECK_UPDATE.
  * - Enable RX DMA reception (set @c RXCR_SR).
  *
  * @param[in,out] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         configuration information and runtime state for the Ethernet
  *         peripheral.
  * @param[in]     channel
  *         Channel identifier (bitmask) that must satisfy
  *         @ref IS_ETH_CHANNEL_INDEX. If it intersects
  *         @ref HAL_ETH_TX_CHANNEL_ALL, a TX channel is resumed;
  *         otherwise an RX channel is resumed.
  *
  * @retval HAL_OK
  *         The selected channel was successfully resumed.
  * @retval HAL_ERROR
  *         Channel index could not be derived from @p channel
  *         (@ref ETH_GetTXChIndex / @ref ETH_GetRXChIndex failed).
  * @retval HAL_INVALID_PARAM
  *         - @p heth is @c NULL, or
  *         - @p channel is invalid (IS_ETH_CHANNEL_INDEX() returns 0),
  *         and parameter checking is enabled via @c USE_HAL_CHECK_PARAM.
  *
  * @pre
  * - The selected channel must be in @ref HAL_ETH_CHANNEL_STATE_SUSPENDED.
  * - @p heth must have been initialized, configured, and the channel
  *   previously started and suspended.
  *
  * @note This function only resumes DMA activity; descriptor lists and other
  *       channel settings are assumed to be valid from prior configuration.
  *
  * @sa HAL_ETH_SuspendChannel
  * @sa HAL_ETH_StartChannel
  */
hal_status_t HAL_ETH_ResumeChannel(hal_eth_handle_t *heth, uint32_t channel)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_INDEX(channel));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (IS_ETH_CHANNEL_INDEX(channel) == 0U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t ch;

  if ((channel & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    /*--------------------- Resume Tx Channel --------------------------*/
    /* Retrieve Tx Channel Id */
    ETH_GetTXChIndex(&ch, channel);

    ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state,
                     (uint32_t)HAL_ETH_CHANNEL_STATE_SUSPENDED);

    /* Move channel state to ACTIVE */
    ETH_STATES_CHECK_UPDATE(heth->tx_channels[ch].channel_state,
                            (uint32_t)HAL_ETH_CHANNEL_STATE_SUSPENDED,
                            HAL_ETH_CHANNEL_STATE_ACTIVE);

    ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);

    /* Enable Tx DMA transmission */
    STM32_SET_BIT(p_dma_instance->DMACXTXCR, ETH_DMACTXCR_ST);
  }
  else
  {
    /*--------------------- Resume Rx Channel --------------------------*/
    /* Retrieve Rx Channel Id */
    ETH_GetRXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_SUSPENDED);
    /* move channel state to Active */
    ETH_STATES_CHECK_UPDATE(heth->rx_channels[ch].channel_state, (uint32_t)HAL_ETH_CHANNEL_STATE_SUSPENDED,
                            HAL_ETH_CHANNEL_STATE_ACTIVE);
    ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);

    /* Enable Rx DMA reception */
    STM32_SET_BIT(p_dma_instance->DMACXRXCR, ETH_DMACRXCR_SR);
  }
  return HAL_OK;
}

/**
  * @brief  Get the number of buffers in use (owned by the hardware) for a channel.
  *
  * This function returns the current number of buffers in use (owned by the
  * hardware) for the specified Ethernet channel (Tx or Rx). The channel type
  * is inferred from @p channel using the @ref HAL_ETH_TX_CHANNEL_ALL mask.
  *
  * @param[in]  heth       Pointer to a @ref hal_eth_handle_t structure that
  *                        contains the configuration information for the
  *                        specified Ethernet peripheral.
  * @param[in]  channel    Channel index, as defined by @ref IS_ETH_CHANNEL_INDEX.
  *                        The function automatically distinguishes between Tx
  *                        and Rx channels using @ref HAL_ETH_TX_CHANNEL_ALL.
  *
  * @pre @p heth must not be @c NULL.
  * @pre @p p_buf_cnt must not be @c NULL.
  * @pre @p channel must be a valid channel index (see @ref IS_ETH_CHANNEL_INDEX).
  * @pre @p heth->global_state must be equal to @ref HAL_ETH_STATE_CONFIGURED.
  * @pre The corresponding channel state must be
  *      @ref HAL_ETH_CHANNEL_STATE_CONFIGURED or
  *      @ref HAL_ETH_CHANNEL_STATE_ACTIVE.
  *
  * @return Number of buffers currently in use (owned by the hardware) for the
            specified channel.
  */
uint32_t HAL_ETH_GetChannelBufferInUseCount(const hal_eth_handle_t *heth, uint32_t channel)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_INDEX(channel));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t ch;
  uint32_t ch_Buff_InUse;

  if ((channel & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    /* Retrieve Tx Channel Id. */
    ETH_GetTXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->tx_channels[ch].channel_state,
                     (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED | (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE);
    ch_Buff_InUse = heth->tx_channels[ch].tx_desc_list.buff_in_use;
  }
  else
  {
    /* Retrieve Rx Channel Id. */
    ETH_GetRXChIndex(&ch, channel);
    ASSERT_DBG_STATE(heth->rx_channels[ch].channel_state,
                     (uint32_t)HAL_ETH_CHANNEL_STATE_CONFIGURED | (uint32_t)HAL_ETH_CHANNEL_STATE_ACTIVE);
    ch_Buff_InUse = heth->rx_channels[ch].rx_desc_list.buff_in_use;
  }

  return ch_Buff_InUse;
}
/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group10
  * @{
This subsection provides the Ethernet Multi-Queue Functions.
  - HAL_ETH_GetRxDMAChNumber(): Get the number of Rx DMA channels.
  */
/**
  * @brief  Get the number of Rx DMA channels.
  *
  * This function returns the maximum number of Rx DMA channels supported
  * by the Ethernet HAL configuration, as defined by
  * @ref USE_HAL_ETH_MAX_RX_CH_NB.
  *
  * @param[in] heth Pointer to a @ref hal_eth_handle_t structure.
  *                This parameter is currently unused.
  *
  * @return Number of Rx DMA channels.
  */
uint32_t HAL_ETH_GetRxDMAChNumber(const hal_eth_handle_t *heth)
{
  STM32_UNUSED(heth);
  return USE_HAL_ETH_MAX_RX_CH_NB;
}

/**
  * @brief  Get the number of Tx DMA channels.
  *
  * This function returns the maximum number of Tx DMA channels supported
  * by the Ethernet HAL configuration, as defined by
  * @ref USE_HAL_ETH_MAX_TX_CH_NB.
  *
  * @param[in] heth Pointer to a @ref hal_eth_handle_t structure.
  *                This parameter is currently unused.
  *
  * @return Number of Tx DMA channels.
  */
uint32_t HAL_ETH_GetTxDMAChNumber(const hal_eth_handle_t *heth)
{
  STM32_UNUSED(heth);
  return USE_HAL_ETH_MAX_TX_CH_NB;
}

/**
  * @brief  Get the number of Rx MTL queues.
  *
  * This function returns the maximum number of Rx MTL queues supported
  * by the Ethernet HAL configuration. In this implementation, the number
  * of Rx MTL queues is equal to @ref USE_HAL_ETH_MAX_RX_CH_NB.
  *
  * @param[in] heth Pointer to a @ref hal_eth_handle_t structure.
  *                This parameter is currently unused.
  *
  * @return Number of Rx MTL queues.
  */
uint32_t HAL_ETH_GetRxMTLQNumber(const hal_eth_handle_t *heth)
{
  STM32_UNUSED(heth);
  return USE_HAL_ETH_MAX_RX_CH_NB;
}

/**
  * @brief  Get the number of Tx MTL queues.
  *
  * This function returns the maximum number of Tx MTL queues supported
  * by the Ethernet HAL configuration. In this implementation, the number
  * of Tx MTL queues is equal to @ref USE_HAL_ETH_MAX_TX_CH_NB.
  *
  * @param[in] heth Pointer to a @ref hal_eth_handle_t structure.
  *                This parameter is currently unused.
  *
  * @return Number of Tx MTL queues.
  */
uint32_t HAL_ETH_GetTxMTLQNumber(const hal_eth_handle_t *heth)
{
  STM32_UNUSED(heth);
  return USE_HAL_ETH_MAX_TX_CH_NB;
}
/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group11
  * @{
This subsection provides the Ethernet Peripheral and Channel State and Error Functions.
  - HAL_ETH_GetState(): Get the global state of the Ethernet peripheral.
  - HAL_ETH_GetChannelState(): Get the state of a channel.
  - HAL_ETH_GetLastErrorCodes(): Get the last error codes.
  */
/**
  * @brief  Return the global state of the Ethernet HAL driver.
  *
  * This function retrieves the current global state of the Ethernet HAL
  * associated with the given handle @p heth. The state reflects the overall
  * lifecycle of the peripheral (e.g. reset, initialized, ready, busy, error).
  *
  * @param[in] heth
  *         Pointer to a constant @ref hal_eth_handle_t structure that holds
  *         the Ethernet configuration and runtime state.
  *
  * @retval hal_eth_state_t
  *         The current global Ethernet state, typically one of:
  *         - @ref HAL_ETH_STATE_RESET
  *         - @ref HAL_ETH_STATE_INIT
  *         - @ref HAL_ETH_STATE_CONFIGURED
  *         - @ref HAL_ETH_STATE_POWER_DOWN
  *         - @ref HAL_ETH_STATE_FAULT
  *         (Exact values depend on the @ref hal_eth_state_t enumeration.)
  * @retval HAL_ETH_STATE_RESET
  *         Returned if @p heth is @c NULL and parameter checking is enabled
  *         (@c USE_HAL_CHECK_PARAM == 1).
  *
  * @note This function does not perform any synchronization; it simply
  *       returns the current value of @c heth->global_state.
  */
hal_eth_state_t HAL_ETH_GetState(const hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);

  return heth->global_state;
}

/**
  * @brief  Get the current state of an Ethernet TX or RX channel.
  *
  * This function returns the current state of the Ethernet channel specified
  * by @p channel. The channel identifier can correspond to either a TX or RX
  * channel; the function determines the direction and returns the associated
  * @ref hal_eth_channel_state_t value from the handle.
  *
  * The function:
  * - Validates @p heth and @p channel (with debug and optional runtime checks).
  * - If @p channel matches any TX channel bit (@ref HAL_ETH_TX_CHANNEL_ALL),
  *   it uses @ref ETH_GetTXChIndex to obtain the TX channel index and returns
  *   @c heth->tx_channels[index].channel_state.
  * - Otherwise, it uses @ref ETH_GetRXChIndex to obtain the RX channel index
  *   and returns @c heth->rx_channels[index].channel_state.
  * - On any error (invalid index, parameter check failure), it returns
  *   @ref HAL_ETH_CHANNEL_STATE_RESET.
  *
  * @param[in] heth
  *         Pointer to a constant @ref hal_eth_handle_t structure that holds
  *         the Ethernet configuration and channel runtime states.
  * @param[in] channel
  *         Channel identifier (bitmask) selecting the desired TX or RX channel.
  *         Must satisfy @ref IS_ETH_CHANNEL_INDEX. If the bitmask intersects
  *         @ref HAL_ETH_TX_CHANNEL_ALL, a TX channel state is returned;
  *         otherwise an RX channel state is returned.
  *
  * @retval hal_eth_channel_state_t
  *         The current state of the selected channel, typically one of:
  *         - @ref HAL_ETH_CHANNEL_STATE_RESET
  *         - @ref HAL_ETH_CHANNEL_STATE_CONFIGURED
  *         - @ref HAL_ETH_CHANNEL_STATE_ACTIVE
  *         - @ref HAL_ETH_CHANNEL_STATE_SUSPENDED
  *         (Actual values depend on the @ref hal_eth_channel_state_t enum.)
  *
  * @note If @p channel contains multiple channel bits, the helper functions
  *       @ref ETH_GetTXChIndex or @ref ETH_GetRXChIndex will use the first
  *       matching channel (lowest index).
  * @note If parameter checking is enabled and @p heth is @c NULL or
  *       @p channel is invalid, the function returns
  *       @ref HAL_ETH_CHANNEL_STATE_RESET.
  *
  * @sa ETH_GetTXChIndex
  * @sa ETH_GetRXChIndex
  */
hal_eth_channel_state_t HAL_ETH_GetChannelState(const hal_eth_handle_t *heth, uint32_t channel)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_CHANNEL_INDEX(channel));

  hal_eth_channel_state_t channel_state;
  uint32_t ch;

  if ((channel & HAL_ETH_TX_CHANNEL_ALL) != 0UL)
  {
    /* Retrieve Tx Channel Id */
    ETH_GetTXChIndex(&ch, channel);
    channel_state = heth->tx_channels[ch].channel_state;
  }
  else
  {
    /* Retrieve Rx Channel Id */
    ETH_GetRXChIndex(&ch, channel);
    channel_state = heth->rx_channels[ch].channel_state;
  }

  return channel_state;
}

#if defined (USE_HAL_ETH_GET_LAST_ERRORS) && (USE_HAL_ETH_GET_LAST_ERRORS == 1)
/**
  * @brief  Retrieve the last recorded Ethernet error codes.
  *
  * This function returns the content of the @c last_error_codes field of the
  * given Ethernet handle @p heth. The field is typically updated internally
  * by the HAL when errors occur on the Ethernet peripheral (e.g. DMA errors,
  * descriptor errors, protocol errors).
  *
  * @param[in] heth
  *         Pointer to a constant @ref hal_eth_handle_t structure that contains
  *         the runtime state of the Ethernet peripheral, including the
  *         @c last_error_codes field.
  *
  * @retval uint32_t
  *         Bitmask containing the last error codes recorded for this handle.
  *         The exact meaning of each bit depends on the Ethernet HAL error
  *         definitions (e.g. @c HAL_ETH_ERROR_xxx).
  * @retval HAL_INVALID_PARAM
  *         If @p heth is @c NULL and parameter checking is enabled
  *         (@c USE_HAL_CHECK_PARAM == 1).
  *
  * @note This API is available only when @c USE_HAL_ETH_GET_LAST_ERRORS is
  *       defined and set to 1.
  * @note The @c last_error_codes field is read-only from the user point of view
  *       and is updated by the HAL internal error handling logic.
  */
uint32_t HAL_ETH_GetLastErrorCodes(const hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);

  return heth->last_error_codes;
}
#endif /* USE_HAL_ETH_GET_LAST_ERRORS && USE_HAL_ETH_GET_LAST_ERRORS = 1 */
/**
  * @}
  */

/** @addtogroup ETH_Exported_Functions_Group12
  * @{
This subsection provides the Ethernet MDIO Control and PHY I/O Operations Functions.
  - HAL_ETH_MDIO_UpdateClockRange(): Update the MDIO clock range.
  - HAL_ETH_MDIO_SetOpAttributes(): Configures Ethernet MDIO command attributes.
  - HAL_ETH_MDIO_C22ReadData(): Read a register from an external PHY using Clause 22 method.
  - HAL_ETH_MDIO_C22WriteData(): Write data to an external RHY register using Clause 22 method.
  - HAL_ETH_MDIO_C45ReadData(): Read a register from an external PHY using Clause 45 method.
  - HAL_ETH_MDIO_C45WriteData(): Write data to an external RHY register using Clause 45 method.
  - HAL_ETH_MDIO_C45ReadDataRange(): Read a range of registers from an external PHY using Clause 45 method.
  */
/**
  * @brief  Update the MDIO clock range according to the current HCLK frequency.
  *
  * This function recalculates and updates the MDIO clock divider (CSR Clock
  * Range) in the @c MACMDIOAR register based on the current AHB bus (HCLK)
  * frequency returned by HAL_RCC_GetHCLKFreq().
  *
  * It:
  * - Reads the current @c MACMDIOAR register value.
  * - Clears the CSR Clock Range (CR) bits.
  * - Computes the appropriate divider (e.g. @ref ETH_MDC_CLK_DIV_16,
  *   @ref ETH_MDC_CLK_DIV_26, etc.) according to the HCLK range.
  * - Writes back the new value into @c MACMDIOAR.
  *
  * The mapping between HCLK frequency and divider is:
  * - @c hclk < 35 MHz             --> @ref ETH_MDC_CLK_DIV_16
  * -  35 MHz <= @c hclk <  60 MHz --> @ref ETH_MDC_CLK_DIV_26
  * -  60 MHz <= @c hclk < 100 MHz --> @ref ETH_MDC_CLK_DIV_42
  * - 100 MHz <= @c hclk < 150 MHz --> @ref ETH_MDC_CLK_DIV_62
  * - 150 MHz <= @c hclk < 250 MHz --> @ref ETH_MDC_CLK_DIV_102
  * - 250 MHz <= @c hclk < 300 MHz --> @ref ETH_MDC_CLK_DIV_124
  * - 300 MHz <= @c hclk < 500 MHz --> @ref ETH_MDC_CLK_DIV_204
  * - @c hclk >= 500 MHz           --> @ref ETH_MDC_CLK_DIV_324
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains
  *         the configuration information for the Ethernet peripheral.
  *
  * @note This function is similar in purpose to the internal helper used
  *       during initialization, but can be called at runtime if the HCLK
  *       configuration changes (e.g. change of system clock).
  * @note The MDIO clock must respect the maximum clock allowed by the PHY
  *       (typically around 2.5 MHz); this function selects a divider that
  *       ensures compliance based on HCLK.
  * @note It is strongly recommended to call this function immediately after
  *       any change to the system clock tree that affects HCLK, before
  *       performing further MDIO transactions, to avoid violating the
  *       external device or the Ethernet MAC maximum MDC clock specification.
  */
void HAL_ETH_MDIO_UpdateClockRange(hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t hclk;
  uint32_t tmpreg;

  /* Get the ETHERNET MACMDIOAR value */
  tmpreg = STM32_READ_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR);

  /* Clear CSR Clock Range bits */
  tmpreg &= ~ETH_MACMDIOAR_CR;

  /* Get hclk frequency value */
  hclk = HAL_RCC_GetHCLKFreq();

  tmpreg |= ETH_GetMDIOClockRange(hclk);

  /* Configure the CSR Clock Range */
  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, tmpreg);
}

/**
  * @brief  Configure MDIO operation attributes in the MACMDIOAR register.
  *
  * This function sets specific MDIO operation attributes for subsequent
  * Clause 22/45 MDIO transactions by updating the corresponding bits in
  * the @c MACMDIOAR register.
  *
  * MDIO read/write operations performed by the HAL are synchronous: the calling
  * context is blocked until the corresponding MDIO transaction has fully
  * completed on the bus, or until the @ref ETH_MDIO_BUS_TIMEOUT duration is reached.
  *
  * The attributes updated are:
  * - @ref HAL_ETH_MDIO_FEAT_PSE : Preamble Suppression Enable.
  * - @ref HAL_ETH_MDIO_FEAT_BTB : Back-to-Back transaction mode.
  * - @ref HAL_ETH_MDIO_NTC_1_CYCLE  : 1 Trailing clock cycle.
  * - @ref HAL_ETH_MDIO_NTC_2_CYCLES : 2 Trailing clock cycles.
  * - @ref HAL_ETH_MDIO_NTC_3_CYCLES : 3 Trailing clock cycles.
  * - @ref HAL_ETH_MDIO_NTC_4_CYCLES : 4 Trailing clock cycles.
  * - @ref HAL_ETH_MDIO_NTC_5_CYCLES : 5 Trailing clock cycles.
  * - @ref HAL_ETH_MDIO_NTC_6_CYCLES : 6 Trailing clock cycles.
  * - @ref HAL_ETH_MDIO_NTC_7_CYCLES : 7 Trailing clock cycles.
  *
  * The caller provides @p cmd_attributes, which must contain the desired
  * combination of these bits (and only these bits). The function then
  * updates @c MACMDIOAR accordingly.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains
  *         the configuration information for the Ethernet peripheral.
  * @param[in] cmd_attributes
  *         Bitmask of MDIO operation attributes to be applied. This value
  *         is typically composed of one or more of:
  *         - @ref HAL_ETH_MDIO_FEAT_PSE : Preamble Suppression Enable.
  *         - @ref HAL_ETH_MDIO_FEAT_BTB : Back-to-Back transaction mode.
  *         - @ref HAL_ETH_MDIO_NTC_1_CYCLE  : 1 Trailing clock cycle.
  *         - @ref HAL_ETH_MDIO_NTC_2_CYCLES : 2 Trailing clock cycles.
  *         - @ref HAL_ETH_MDIO_NTC_3_CYCLES : 3 Trailing clock cycles.
  *         - @ref HAL_ETH_MDIO_NTC_4_CYCLES : 4 Trailing clock cycles.
  *         - @ref HAL_ETH_MDIO_NTC_5_CYCLES : 5 Trailing clock cycles.
  *         - @ref HAL_ETH_MDIO_NTC_6_CYCLES : 6 Trailing clock cycles.
  *         - @ref HAL_ETH_MDIO_NTC_7_CYCLES : 7 Trailing clock cycles.
  *
  * @note This function does not start any MDIO transaction; it only configures
  *       the attributes used by subsequent MDIO read/write operations.
  * @note The caller must ensure that @p heth is valid and that the Ethernet
  *       peripheral has been initialized before calling this function.
  * @note IMPORTANT: When performing a complete / full configuration or update
  *       sequence of an external device over MDIO, the user must ensure that
  *       the whole MDIO transaction sequence is executed in a protected,
  *       non-interleaved way. In particular, it must not be interrupted or
  *       interleaved with other MDIO accesses targeting the same or any other
  *       device on the MDIO bus. This protection must be implemented at the
  *       upper (application) level, typically by using a mutual exclusion or
  *       equivalent locking mechanism around the full MDIO access sequence.
  */
void HAL_ETH_MDIO_SetOpAttributes(hal_eth_handle_t *heth, uint32_t cmd_attributes)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(IS_ETH_MDIO_CMD_ATTR(cmd_attributes));
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  /* Write the cmd_attributes value into the MDIO Address register */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, (ETH_MACMDIOAR_PSE | ETH_MACMDIOAR_BTB | ETH_MACMDIOAR_NTC),
                   cmd_attributes);
}

/**
  * @brief  Write a single PHY register using MDIO Clause 22.
  *
  * This function performs one Clause 22 MDIO write operation to the register
  * @p reg_addr of the PHY device @p phy_dev_addr, writing the 16-bit value
  * @p data.
  *
  * MDIO write operations performed by the HAL are synchronous: the calling context is
  * blocked until the corresponding MDIO transaction has fully completed on the bus,
  * or until the @ref ETH_MDIO_BUS_TIMEOUT duration is reached.
  *
  * The procedure is:
  * - Check that the MDIO controller is not busy.
  * - Disable Clause 45 mode (enable Clause 22) by clearing
  *   @c MACMDIOAR C45E bit.
  * - Load the data to be written into @c MACMDIODR (DATA field).
  * - Load @c MACMDIOAR with:
  *   - PHY address (@p phy_dev_addr),
  *   - Register address (@p reg_addr),
  *   - Write command (@ref ETH_GOC_OPERATION_WRITE).
  * - Set the @ref ETH_MACMDIOAR_BUSY bit to start the write operation.
  * - Poll on @ref ETH_MACMDIOAR_BUSY until cleared or until
  *   @ref ETH_MDIO_BUS_TIMEOUT elapses.
  *
  * @param[in] heth
  *         Pointer to a constant @ref hal_eth_handle_t structure that
  *         contains the configuration information for the Ethernet peripheral.
  *         The handle itself is not modified by this function.
  * @param[in] phy_dev_addr
  *         PHY device address on the MDIO bus (Clause 22 PHY address).
  * @param[in] reg_addr
  *         Register address (0..31) within the selected PHY device.
  * @param[in] data
  *         16-bit data value to write into the specified register.
  *
  * @retval HAL_OK
  *         The register has been successfully written.
  * @retval HAL_ERROR
  *         - The MDIO controller was busy at the beginning of the operation.
  *         - A timeout occurred while waiting for the @ref ETH_MACMDIOAR_BUSY
  *           flag to clear.
  * @retval HAL_INVALID_PARAM
  *         The @p heth parameter is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @note Clause 22 mode is selected by clearing @c MACMDIOAR C45E bit.
  * @note IMPORTANT: When performing a complete / full configuration or update
  *       sequence of an external device over MDIO, the user must ensure that
  *       the whole MDIO transaction sequence is executed in a protected,
  *       non-interleaved way. In particular, it must not be interrupted or
  *       interleaved with other MDIO accesses targeting the same or any other
  *       device on the MDIO bus. This protection must be implemented at the
  *       upper (application) level, typically by using a mutual exclusion or
  *       equivalent locking mechanism around the full MDIO access sequence.
  *
  * @sa HAL_ETH_MDIO_C22ReadData
  * @sa HAL_ETH_MDIO_C45WriteData
  */
hal_status_t HAL_ETH_MDIO_C22WriteData(const hal_eth_handle_t *heth, uint8_t phy_dev_addr, uint8_t reg_addr,
                                       uint16_t data)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t tickstart;
  uint32_t tmpreg;

  /* Check for the Busy flag */
  if (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) != 0UL)
  {
    return HAL_ERROR;
  }

  /* Enable Clause 22 (disable Clause 45) */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_C45E);

  /* Write the data to the MDIO Data Register */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACMDIODR, ETH_MACMDIODR_DATA, data);

  /* Get the MACMDIOAR value */
  STM32_WRITE_REG(tmpreg, ETH_GET_INSTANCE(heth)->MACMDIOAR);

  /* Prepare the MDIO Address Register value:
     - Set the PHY device address
     - Set the PHY register address
     - Set the write mode */
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_PA, (((uint32_t)phy_dev_addr) << ETH_MACMDIOAR_PA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_RDA, (((uint32_t)reg_addr) << ETH_MACMDIOAR_RDA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_GOC, ETH_GOC_OPERATION_WRITE);

  /* Write the result value into the MDIO Address Register */
  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, tmpreg);

  /* Initialize a write access to MDIO */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY);

  tickstart = HAL_GetTick();

  /* Wait for the Busy flag to clear */
  while (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) > 0UL)
  {
    if (((HAL_GetTick() - tickstart) > ETH_MDIO_BUS_TIMEOUT))
    {
      return HAL_ERROR;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Read a single PHY register using MDIO Clause 22.
  *
  * This function performs one Clause 22 MDIO read operation of the register
  * @p reg_addr located in the specified PHY device @p phy_dev_addr, and
  * returns the 16-bit register content through @p p_data.
  *
  * MDIO read operations performed by the HAL are synchronous: the calling context is
  * blocked until the corresponding MDIO transaction has fully completed on the bus,
  * or until the @ref ETH_MDIO_BUS_TIMEOUT duration is reached.
  *
  * The procedure is:
  * - Check that the MDIO controller is not busy.
  * - Disable Clause 45 mode (enable Clause 22) by clearing
  *   @c MACMDIOAR C45E bit.
  * - Load @c MACMDIOAR with:
  *   - PHY address (@p phy_dev_addr),
  *   - Register address (@p reg_addr),
  *   - Read command (@ref ETH_GOC_OPERATION_READ).
  * - Set the @ref ETH_MACMDIOAR_BUSY bit to start the read operation.
  * - Poll on @ref ETH_MACMDIOAR_BUSY until cleared or until
  *   @ref ETH_MDIO_BUS_TIMEOUT elapses.
  * - Read the data from @c MACMDIODR into @p p_data.
  *
  * @param[in]  heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains
  *         the configuration information for the Ethernet peripheral.
  * @param[in]  phy_dev_addr
  *         PHY device address on the MDIO bus (Clause 22 PHY address).
  * @param[in]  reg_addr
  *         Register address (0..31) within the selected PHY device.
  * @param[out] p_data
  *         Pointer to a @c uint16_t variable where the read register value
  *         will be stored.
  *
  * @retval HAL_OK
  *         The register has been successfully read and @p *p_data updated.
  * @retval HAL_ERROR
  *         - The MDIO controller was busy at the beginning of the operation.
  *         - A timeout occurred while waiting for the @ref ETH_MACMDIOAR_BUSY
  *           flag to clear.
  * @retval HAL_INVALID_PARAM
  *         @p heth or @p p_data is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @note Clause 22 mode is selected by clearing @c MACMDIOAR C45E bit.
  * @note IMPORTANT: When performing a complete / full configuration or update
  *       sequence of an external device over MDIO, the user must ensure that
  *       the whole MDIO transaction sequence is executed in a protected,
  *       non-interleaved way. In particular, it must not be interrupted or
  *       interleaved with other MDIO accesses targeting the same or any other
  *       device on the MDIO bus. This protection must be implemented at the
  *       upper (application) level, typically by using a mutual exclusion or
  *       equivalent locking mechanism around the full MDIO access sequence.
  *
  * @sa HAL_ETH_MDIO_C22WriteData
  * @sa HAL_ETH_MDIO_C45ReadData
  */
hal_status_t HAL_ETH_MDIO_C22ReadData(hal_eth_handle_t *heth, uint8_t phy_dev_addr, uint8_t reg_addr, uint16_t *p_data)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t tickstart;
  uint32_t tmpreg;

  /* Check for the Busy flag */
  if (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) != 0UL)
  {
    return HAL_ERROR;
  }

  /* Enable Clause 22 (disable Clause 45) */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_C45E);

  /* Get the MACMDIOAR value */
  STM32_WRITE_REG(tmpreg, ETH_GET_INSTANCE(heth)->MACMDIOAR);

  /* Prepare the MDIO Address Register value:
     - Set the PHY device address
     - Set the PHY register address
     - Set the read mode */
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_PA, (((uint32_t)phy_dev_addr) << ETH_MACMDIOAR_PA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_RDA, (((uint32_t)reg_addr) << ETH_MACMDIOAR_RDA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_GOC, ETH_GOC_OPERATION_READ);

  /* Write the result value into the MDIO Address Register */
  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, tmpreg);

  /* Initialize a read access to MDIO */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY);

  tickstart = HAL_GetTick();

  /* Wait for the Busy flag to clear */
  while (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) > 0UL)
  {
    if (((HAL_GetTick() - tickstart) > ETH_MDIO_BUS_TIMEOUT))
    {
      return HAL_ERROR;
    }
  }

  /* Read access completed, get the data value */
  STM32_WRITE_REG(*p_data, (uint16_t)ETH_GET_INSTANCE(heth)->MACMDIODR);

  return HAL_OK;
}

/**
  * @brief  Write a single PHY register using MDIO Clause 45.
  *
  * This function performs one Clause 45 MDIO write operation to the register
  * @p reg_addr located in the specified PHY device (@p phy_addr, @p dev_addr),
  * writing the 16-bit value @p data.
  *
  * MDIO write operations performed by the HAL are synchronous: the calling context is
  * blocked until the corresponding MDIO transaction has fully completed on the bus,
  * or until the @ref ETH_MDIO_BUS_TIMEOUT duration is reached.
  *
  * The procedure is:
  * - Check that the MDIO controller is not busy.
  * - Enable Clause 45 access in @c MACMDIOAR.
  * - Program the target register address into @c MACMDIODR (RA field).
  * - Program the data to be written into @c MACMDIODR (DATA field).
  * - Configure @c MACMDIOAR with:
  *   - PHY address (@p phy_addr),
  *   - Device (MMD) address (@p dev_addr),
  *   - Write command (@ref ETH_GOC_OPERATION_WRITE).
  * - Set the @ref ETH_MACMDIOAR_BUSY bit to start the write.
  * - Poll on @ref ETH_MACMDIOAR_BUSY until cleared or until
  *   @ref ETH_MDIO_BUS_TIMEOUT elapses.
  *
  * @param[in] heth
  *         Pointer to a constant @ref hal_eth_handle_t structure that
  *         contains the configuration information for the Ethernet peripheral.
  *         The handle itself is not modified by this function.
  * @param[in] phy_addr
  *         PHY address on the MDIO bus (Clause 45 PHY address field).
  * @param[in] dev_addr
  *         PHY device (MMD) address for Clause 45 access.
  * @param[in] reg_addr
  *         Register address (within the selected device) to be written.
  * @param[in] data
  *         16-bit data value to write into the specified register.
  *
  * @retval HAL_OK
  *         The register has been successfully written.
  * @retval HAL_ERROR
  *         - The MDIO controller was busy at the beginning of the operation.
  *         - A timeout occurred while waiting for the @ref ETH_MACMDIOAR_BUSY
  *           flag to clear.
  * @retval HAL_INVALID_PARAM
  *         The @p heth parameter is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @note Clause 45 mode is enabled during this function through the
  *       @c MACMDIOAR C45E bit.
  * @note IMPORTANT: When performing a complete / full configuration or update
  *       sequence of an external device over MDIO, the user must ensure that
  *       the whole MDIO transaction sequence is executed in a protected,
  *       non-interleaved way. In particular, it must not be interrupted or
  *       interleaved with other MDIO accesses targeting the same or any other
  *       device on the MDIO bus. This protection must be implemented at the
  *       upper (application) level, typically by using a mutual exclusion or
  *       equivalent locking mechanism around the full MDIO access sequence.
  *
  * @sa HAL_ETH_MDIO_C45ReadData
  * @sa HAL_ETH_MDIO_C45ReadDataRange
  */
hal_status_t HAL_ETH_MDIO_C45WriteData(const hal_eth_handle_t *heth, uint8_t phy_addr, uint8_t dev_addr,
                                       uint16_t reg_addr, uint16_t data)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

  uint32_t tickstart;
  uint32_t tmpreg;

  /* Check for the Busy flag */
  if (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) != 0UL)
  {
    return HAL_ERROR;
  }

  /* Enable Clause 45 */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_C45E);

  /* Write register address to MDIO Data Register */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACMDIODR, ETH_MACMDIODR_RA,
                   (((uint32_t)reg_addr) << ETH_MACMDIODR_RA_Pos));

  /* Write data to MDIO Data Register */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACMDIODR, ETH_MACMDIODR_DATA, data);

  /* Get the MACMDIOAR value */
  STM32_WRITE_REG(tmpreg, ETH_GET_INSTANCE(heth)->MACMDIOAR);

  /* Prepare the MDIO Address Register value:
     - Set the PHY address
     - Set the device (MMD) address
     - Set the write access operation */
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_PA, (((uint32_t)phy_addr) << ETH_MACMDIOAR_PA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_RDA, (((uint32_t)dev_addr) << ETH_MACMDIOAR_RDA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_GOC, ETH_GOC_OPERATION_WRITE);

  /* Write back the tmpreg value into the MDIO Address Register */
  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, tmpreg);

  /* Initialize a write operation */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY);

  tickstart = HAL_GetTick();

  /* Wait for the Busy flag to clear */
  while (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) > 0UL)
  {
    if (((HAL_GetTick() - tickstart) > ETH_MDIO_BUS_TIMEOUT))
    {
      return HAL_ERROR;
    }
  }

  /* Write operation done */
  return HAL_OK;
}

/**
  * @brief  Read a single PHY register using MDIO Clause 45.
  *
  * This function performs one Clause 45 MDIO read operation of the register
  * @p reg_addr located in the specified PHY device (@p phy_addr, @p dev_addr),
  * and returns the 16-bit register content through @p p_data.
  *
  * MDIO read operations performed by the HAL are synchronous: the calling context is
  * blocked until the corresponding MDIO transaction has fully completed on the bus,
  * or until the @ref ETH_MDIO_BUS_TIMEOUT duration is reached.
  *
  * The procedure is:
  * - Check that the MDIO controller is not busy.
  * - Enable Clause 45 access in @c MACMDIOAR.
  * - Program the target register address into @c MACMDIODR.
  * - Configure @c MACMDIOAR with:
  *   - PHY address (@p phy_addr),
  *   - Device (MMD) address (@p dev_addr),
  *   - Read command (@ref ETH_GOC_OPERATION_READ).
  * - Set the @ref ETH_MACMDIOAR_BUSY bit to start the read.
  * - Poll on @ref ETH_MACMDIOAR_BUSY until cleared or until
  *   @ref ETH_MDIO_BUS_TIMEOUT elapses.
  * - Read the data from @c MACMDIODR into @p p_data.
  *
  * @param[in]  heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains
  *         the configuration information for the Ethernet peripheral.
  * @param[in]  phy_addr
  *         PHY address on the MDIO bus (Clause 45 PHY address field).
  * @param[in]  dev_addr
  *         PHY device (MMD) address for Clause 45 access.
  * @param[in]  reg_addr
  *         Register address (within the selected device) to be read.
  * @param[out] p_data
  *         Pointer to a @c uint16_t variable where the read register value
  *         will be stored.
  *
  * @retval HAL_OK
  *         The register has been successfully read and @p *p_data updated.
  * @retval HAL_ERROR
  *         - The MDIO controller was busy at the beginning of the operation.
  *         - A timeout occurred while waiting for the @ref ETH_MACMDIOAR_BUSY
  *           flag to clear.
  * @retval HAL_INVALID_PARAM
  *         The @p heth parameter is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @note Clause 45 mode is enabled during this function through the
  *       @c MACMDIOAR C45E bit.
  * @note IMPORTANT: When performing a complete / full configuration or update
  *       sequence of an external device over MDIO, the user must ensure that
  *       the whole MDIO transaction sequence is executed in a protected,
  *       non-interleaved way. In particular, it must not be interrupted or
  *       interleaved with other MDIO accesses targeting the same or any other
  *       device on the MDIO bus. This protection must be implemented at the
  *       upper (application) level, typically by using a mutual exclusion or
  *       equivalent locking mechanism around the full MDIO access sequence.
  *
  * @sa HAL_ETH_MDIO_C45ReadDataRange
  */
hal_status_t HAL_ETH_MDIO_C45ReadData(hal_eth_handle_t *heth, uint8_t phy_addr, uint8_t dev_addr, uint16_t reg_addr,
                                      uint16_t *p_data)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t tickstart;
  uint32_t tmpreg;

  /* Check for the Busy flag */
  if (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) != 0UL)
  {
    return HAL_ERROR;
  }

  /* Enable Clause 45 */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_C45E);

  /* Write register address to MDIO Data Register */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACMDIODR, ETH_MACMDIODR_RA,
                   (((uint32_t)reg_addr) << ETH_MACMDIODR_RA_Pos));

  /* Get the MACMDIOAR value */
  STM32_WRITE_REG(tmpreg, ETH_GET_INSTANCE(heth)->MACMDIOAR);

  /* Prepare the MDIO Address Register value:
     - Set the PHY address
     - Set the device (MMD) address
     - Set the Read access operation */
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_PA, (((uint32_t)phy_addr) << ETH_MACMDIOAR_PA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_RDA, (((uint32_t)dev_addr) << ETH_MACMDIOAR_RDA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_GOC, ETH_GOC_OPERATION_READ);

  /* Write back the tmpreg value into the MDIO Address Register */
  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, tmpreg);

  /* Initialize a read operation */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY);

  tickstart = HAL_GetTick();

  /* Wait for the Busy flag to clear */
  while (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) > 0UL)
  {
    if (((HAL_GetTick() - tickstart) > ETH_MDIO_BUS_TIMEOUT))
    {
      return HAL_ERROR;
    }
  }

  /* Read access operation completed, get the data value */
  STM32_WRITE_REG(*p_data, (uint16_t)ETH_GET_INSTANCE(heth)->MACMDIODR);

  return HAL_OK;
}

/**
  * @brief  Read a range of PHY registers using MDIO Clause 45 post-increment access.
  *
  * This function performs a sequence of Clause 45 MDIO read operations starting
  * from @p start_reg_addr and reads @p count consecutive registers into the
  * buffer pointed to by @p p_data.
  *
  * MDIO read operations performed by the HAL are synchronous: the calling context is
  * blocked until the corresponding MDIO transaction has fully completed on the bus,
  * or until the @ref ETH_MDIO_BUS_TIMEOUT duration is reached.
  *
  * The procedure is:
  * - Check that the MDIO controller is not busy.
  * - Enable Clause 45 access in @c MACMDIOAR.
  * - Configure @c MACMDIOAR with:
  *   - PHY address (@p phy_addr),
  *   - Device address (@p dev_addr),
  *   - Post-read increment access command (@ref ETH_GOC_OPERATION_PRIAC45).
  * - Program the starting register address in @c MACMDIODR.
  * - For each element to read:
  *   - Set the @ref ETH_MACMDIOAR_BUSY bit to start a post-increment read.
  *   - Wait for the @ref ETH_MACMDIOAR_BUSY bit to clear or until
  *     @ref ETH_MDIO_BUS_TIMEOUT elapses.
  *   - Read the data from @c MACMDIODR into @p p_data[index].
  *
  * @param[in]  heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains
  *         the configuration information for the Ethernet peripheral.
  * @param[in]  phy_addr
  *         PHY address on the MDIO bus (Clause 45 PHY address field).
  * @param[in]  dev_addr
  *         PHY device (MMD) address for Clause 45 access.
  * @param[in]  start_reg_addr
  *         First PHY register address to read (Clause 45 register address).
  * @param[out] p_data
  *         Pointer to a buffer of @c uint16_t where the received register
  *         values will be stored. Must have room for @p count entries.
  * @param[in]  count
  *         Number of consecutive registers to read starting from
  *         @p start_reg_addr.
  *
  * @retval HAL_OK
  *         All requested registers have been successfully read.
  * @retval HAL_ERROR
  *         - The MDIO controller was busy at the beginning of the operation.
  *         - A timeout occurred while waiting for the @ref ETH_MACMDIOAR_BUSY
  *           flag to clear for any of the read operations.
  * @retval HAL_INVALID_PARAM
  *         @p heth or @p p_data is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @note Clause 45 mode is enabled for the duration of this function through
  *       the @c MACMDIOAR C45E bit.
  * @note IMPORTANT: When performing a complete / full configuration or update
  *       sequence of an external device over MDIO, the user must ensure that
  *       the whole MDIO transaction sequence is executed in a protected,
  *       non-interleaved way. In particular, it must not be interrupted or
  *       interleaved with other MDIO accesses targeting the same or any other
  *       device on the MDIO bus. This protection must be implemented at the
  *       upper (application) level, typically by using a mutual exclusion or
  *       equivalent locking mechanism around the full MDIO access sequence.
  */
hal_status_t HAL_ETH_MDIO_C45ReadDataRange(hal_eth_handle_t *heth, uint8_t phy_addr, uint8_t dev_addr,
                                           uint16_t start_reg_addr,
                                           uint16_t *p_data, uint16_t count)
{
  ASSERT_DBG_PARAM(heth != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_STATE(heth->global_state, (uint32_t)HAL_ETH_STATE_CONFIGURED);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  uint32_t tickstart;
  uint32_t tmpreg;

  /* Check for the Busy flag */
  if (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) != 0UL)
  {
    return HAL_ERROR;
  }

  /* Enable Clause 45 */
  STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_C45E);

  /* Get the MACMDIOAR value */
  STM32_WRITE_REG(tmpreg, ETH_GET_INSTANCE(heth)->MACMDIOAR);

  /* Prepare the MDIO Address Register value:
     - Set the PHY address
     - Set the device (MMD) address
     - Set the Post Read Increment Address for Clause 45 PHY */
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_PA, (((uint32_t)phy_addr) << ETH_MACMDIOAR_PA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_RDA, (((uint32_t)dev_addr) << ETH_MACMDIOAR_RDA_Pos));
  STM32_MODIFY_REG(tmpreg, ETH_MACMDIOAR_GOC, ETH_GOC_OPERATION_PRIAC45);

  /* Write back the tmpreg value into the MDIO Address Register */
  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, tmpreg);

  /* Write starting register address to MDIO Data Register */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MACMDIODR, ETH_MACMDIODR_RA,
                   (((uint32_t)start_reg_addr) << ETH_MACMDIODR_RA_Pos));

  /* Initialize a read data range access to MDIO */
  for (uint32_t index = 0; index < count; index++)
  {
    /* Start a post Read Increment Address Clause 45 PHY operation */
    STM32_SET_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY);

    tickstart = HAL_GetTick();

    /* Wait for the Busy flag to clear */
    while (STM32_READ_BIT(ETH_GET_INSTANCE(heth)->MACMDIOAR, ETH_MACMDIOAR_BUSY) > 0UL)
    {
      if (((HAL_GetTick() - tickstart) > ETH_MDIO_BUS_TIMEOUT))
      {
        return HAL_ERROR;
      }
    }

    /* Read access operation completed, get the data value */
    p_data[index] = (uint16_t) STM32_READ_REG(ETH_GET_INSTANCE(heth)->MACMDIODR);
  }

  return HAL_OK;
}
/**
  * @}
  */

#if defined (USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @addtogroup ETH_Exported_Functions_Group13
  * @{
This subsection provides the Ethernet Bus Operation Function.
  - HAL_ETH_AcquireBus(): Acquire the Ethernet bus.
  - HAL_ETH_ReleaseBus(): Release the Ethernet bus.
  */
/**
  * @brief  Acquire exclusive access to the Ethernet bus (semaphore take).
  *
  * This function attempts to take the OS semaphore associated with the
  * Ethernet handle, in order to gain exclusive access to the Ethernet
  * peripheral (bus protection / mutual exclusion).
  *
  * The function:
  * - Verifies that @p heth is not @c NULL (with debug and optional runtime checks).
  * - Calls HAL_OS_SemaphoreTake() on @p heth->semaphore with the given
  *   timeout.
  * - Returns HAL_OK if the semaphore is successfully taken, or
  *   HAL_ERROR otherwise (e.g. timeout, OS error).
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         Ethernet configuration and the OS semaphore used for bus protection.
  * @param[in] timeout_ms
  *         Timeout value in milliseconds for acquiring the semaphore.
  *         The special values (e.g. blocking forever) depend on the
  *         underlying OS implementation of HAL_OS_SemaphoreTake.
  *
  * @retval HAL_OK
  *         The bus semaphore was successfully acquired within @p timeout_ms.
  * @retval HAL_ERROR
  *         The semaphore could not be acquired (e.g. timeout occurred or
  *         OS reported an error).
  * @retval HAL_INVALID_PARAM
  *         The @p heth parameter is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @note The caller must ensure that the Ethernet handle @p heth has been
  *       properly initialized and its @c semaphore member correctly created.
  * @note This function does not modify the hardware state of the Ethernet
  *       peripheral; it only manages synchronization via an OS semaphore.
  *
  * @sa HAL_ETH_ReleaseBus
  */
hal_status_t HAL_ETH_AcquireBus(hal_eth_handle_t *heth, uint32_t timeout_ms)
{
  ASSERT_DBG_PARAM((heth != NULL));

  hal_status_t status = HAL_ERROR;
  /* Take the semaphore */
  if (HAL_OS_SemaphoreTake(&heth->semaphore, timeout_ms) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Release the Ethernet bus access semaphore.
  *
  * This function releases the OS semaphore associated with the Ethernet
  * handle, allowing other tasks/contexts to acquire the bus. It is typically
  * used to unlock access to the Ethernet peripheral after a protected
  * operation is completed.
  *
  * The function:
  * - Verifies that @p heth is not @c NULL (with debug and optional runtime checks).
  * - Calls HAL_OS_SemaphoreRelease() on @p heth->semaphore.
  * - Returns HAL_OK if the semaphore release succeeds, or HAL_ERROR
  *   otherwise.
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains the
  *         Ethernet configuration and the OS semaphore used for bus protection.
  *
  * @retval HAL_OK
  *         The bus semaphore was successfully released.
  * @retval HAL_ERROR
  *         Error while releasing the semaphore (e.g. OS call failed).
  * @retval HAL_INVALID_PARAM
  *         The @p heth parameter is @c NULL (only when parameter checking is
  *         enabled via @c USE_HAL_CHECK_PARAM).
  *
  * @note The caller must ensure that the Ethernet handle @p heth has been
  *       properly initialized and its @c semaphore member correctly created.
  * @note This function does not change the hardware state of the Ethernet
  *       peripheral; it only manages synchronization via an OS semaphore.
  *
  * @sa HAL_ETH_AcquireBus
  */
hal_status_t HAL_ETH_ReleaseBus(hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);

  hal_status_t status = HAL_ERROR;
  /* Release the semaphore */
  if (HAL_OS_SemaphoreRelease(&heth->semaphore) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}
/**
  * @}
  */
#endif /* USE_HAL_MUTEX && USE_HAL_MUTEX = 1 */

#if defined (USE_HAL_ETH_USER_DATA) && (USE_HAL_ETH_USER_DATA == 1)
/** @addtogroup ETH_Exported_Functions_Group14
  * @{
This subsection provides the Ethernet User Data Functions.
  - HAL_ETH_SetUserData(): Set user data pointer.
  - HAL_ETH_GetUserData(): Get user data pointer.
  */
/**
  * @brief  Set the user data pointer.
  *
  * This function associates an opaque user data pointer with the specified
  * Ethernet handle. The HAL does not interpret or modify the user data; it
  * is provided for application use (for example, to store context or state
  * information related to the Ethernet instance).
  *
  * @param[in,out] heth        Pointer to a @ref hal_eth_handle_t structure that
  *                            contains the configuration information for the
  *                            specified Ethernet peripheral.
  * @param[in]     p_user_data Pointer to user data to be associated with the
  *                            Ethernet handle. This pointer can be @c NULL.
  *
  * @pre @p heth must not be @c NULL.
  */
void HAL_ETH_SetUserData(hal_eth_handle_t *heth, const void *p_user_data)
{
  ASSERT_DBG_PARAM(heth != NULL);

  heth->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data pointer.
  *
  * This function returns the user data pointer previously associated with
  * the specified Ethernet handle via @ref HAL_ETH_SetUserData.
  *
  * @param[in] heth Pointer to a @ref hal_eth_handle_t structure that
  *                 contains the configuration information for the
  *                 specified Ethernet peripheral.
  *
  * @pre @p heth must not be @c NULL.
  *
  * @return Pointer to user data associated with the Ethernet handle, or
  *         @c NULL if no user data has been set.
  */
const void *HAL_ETH_GetUserData(const hal_eth_handle_t *heth)
{
  ASSERT_DBG_PARAM(heth != NULL);

  return heth->p_user_data;
}
/**
  * @}
  */
#endif /* USE_HAL_ETH_USER_DATA && USE_HAL_ETH_USER_DATA = 1 */

/** @addtogroup ETH_Private_Functions ETH Private Functions
  * @{
  */
/**
  * @brief  Initialize MAC registers with driver default values.
  * @param  heth Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  */
static void ETH_MAC_Init(struct hal_eth_handle_s *heth)
{
  hal_eth_mac_config_t macDefaultConf;

  /*--------------- ETHERNET MAC registers default Configuration --------------*/

  macDefaultConf.link_config.speed = HAL_ETH_MAC_SPEED_100M;
  macDefaultConf.link_config.duplex_mode = HAL_ETH_MAC_FULL_DUPLEX_MODE;
  macDefaultConf.loopback_mode = HAL_ETH_MAC_LOOPBACK_DISABLE;
  macDefaultConf.src_addr_ctrl = HAL_ETH_MAC_SA_MAC0_REP;
  macDefaultConf.inter_pkt_gap_value = HAL_ETH_MAC_INTER_PKT_GAP_96_BIT;
  macDefaultConf.back_off_limit = HAL_ETH_MAC_BACK_OFF_LIMIT_10;
  macDefaultConf.preamble_length = HAL_ETH_MAC_PREAMBLE_LENGTH_7;
  macDefaultConf.giant_pkt_size_limit_ctrl = HAL_ETH_MAC_GPKT_SZ_LIMIT_DISABLE;
  macDefaultConf.support_2K_pkt = HAL_ETH_MAC_2K_PKT_LEN_DISABLE;
  macDefaultConf.crc_strip_type_pkt = HAL_ETH_MAC_CRC_STRIP_PKT_ENABLE;
  macDefaultConf.auto_pad_crc_strip = HAL_ETH_MAC_AUTO_PAD_CRC_S_ENABLE;
  macDefaultConf.tx_jabber = HAL_ETH_MAC_TX_JABBER_TIM_DISABLE;
  macDefaultConf.cs_before_transmit = HAL_ETH_MAC_CS_BEFORE_TR_DISABLE;
  macDefaultConf.cs_during_transmit = HAL_ETH_MAC_CS_DURING_TR_DISABLE;
  macDefaultConf.retry_transmission = HAL_ETH_MAC_RETRY_TR_ENABLE;
  macDefaultConf.rx_watchdog = HAL_ETH_MAC_RX_WD_TIM_DISABLE;
  macDefaultConf.rx_jumbo_pkt = HAL_ETH_MAC_RX_JUMBO_PKT_DISABLE;
  macDefaultConf.rx_csum_offload = HAL_ETH_MAC_RX_CSUM_PKT_ENABLE;
  macDefaultConf.rx_receive_own = HAL_ETH_MAC_RX_RECEIVE_OWN_ENABLE;
  macDefaultConf.crc_checking_rx_pkts = HAL_ETH_MAC_RX_CRC_PKT_CHK_ENABLE;
  macDefaultConf.deferral_check = HAL_ETH_MAC_DEFERRAL_CHECK_DISABLE;
  macDefaultConf.uc_slow_proto_detect = HAL_ETH_MAC_UC_SLOW_PROTO_DISABLE;
  macDefaultConf.slow_proto_detect = HAL_ETH_MAC_SLOW_PROTO_DISABLE;
  macDefaultConf.giant_pkt_size_limit = ETH_GIANT_PKT_SIZE_LIMIT_BYTE;
  macDefaultConf.ext_inter_pkt_gap_ctrl = HAL_ETH_MAC_E_INTER_PKT_GAP_DISABLE;
  macDefaultConf.ext_inter_pkt_gap = 0UL;
  macDefaultConf.programmable_wd = HAL_ETH_MAC_PROG_WD_DISABLE;
  macDefaultConf.rx_wd_timeout_byte = HAL_ETH_MAC_RX_WDT_2KB;
  macDefaultConf.tx_pause_time = 0UL;
  macDefaultConf.zero_quanta_pause = HAL_ETH_MAC_ZERO_Q_PAUSE_ENABLE;
  macDefaultConf.pause_low_threshold = HAL_ETH_MAC_PLT_MINUS_4_SLOT_TIME;
  macDefaultConf.tr_flow_ctrl = HAL_ETH_MAC_TR_FLOW_CTRL_DISABLE;
  macDefaultConf.uc_pause_pkt_detect = HAL_ETH_MAC_UC_PAUSE_PKT_DISABLE;
  macDefaultConf.receive_flow_ctrl = HAL_ETH_MAC_RECEIVE_FLOW_DISABLE;

  /* MAC default configuration */
  ETH_SetMACConfig(heth, &macDefaultConf);
}

/**
  * @brief  Apply MAC configuration to hardware registers.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  macconf Pointer to a hal_eth_mac_config_t structure containing MAC settings.
  */
static void ETH_SetMACConfig(const hal_eth_handle_t *heth, const hal_eth_mac_config_t *macconf)
{
  uint32_t macregval;
  ETH_TypeDef *p_eth_instance = ETH_GET_INSTANCE(heth);

  /*------------------------ MACCR Configuration --------------------*/
  macregval = ((uint32_t)macconf->link_config.speed |
               (uint32_t)macconf->link_config.duplex_mode |
               (uint32_t)macconf->loopback_mode |
               (uint32_t)macconf->src_addr_ctrl |
               (uint32_t)macconf->inter_pkt_gap_value |
               (uint32_t)macconf->back_off_limit |
               (uint32_t)macconf->preamble_length |
               (uint32_t)macconf->giant_pkt_size_limit_ctrl |
               (uint32_t)macconf->support_2K_pkt |
               (uint32_t)macconf->crc_strip_type_pkt |
               (uint32_t)macconf->auto_pad_crc_strip |
               (uint32_t)macconf->tx_jabber |
               (uint32_t)macconf->cs_before_transmit |
               (uint32_t)macconf->cs_during_transmit |
               (uint32_t)macconf->retry_transmission |
               (uint32_t)macconf->rx_watchdog |
               (uint32_t)macconf->rx_jumbo_pkt |
               (uint32_t)macconf->rx_csum_offload |
               (uint32_t)macconf->rx_receive_own |
               (uint32_t)macconf->deferral_check);

  /* Write to MACCR */
  STM32_MODIFY_REG(p_eth_instance->MACCR, ETH_MACCR_MASK, macregval);

  /*------------------------ MACECR Configuration --------------------*/
  macregval = ((uint32_t)macconf->crc_checking_rx_pkts |
               (uint32_t)macconf->uc_slow_proto_detect |
               (uint32_t)macconf->slow_proto_detect |
               (uint32_t)macconf->giant_pkt_size_limit |
               (uint32_t)macconf->ext_inter_pkt_gap_ctrl |
               (uint32_t)(macconf->ext_inter_pkt_gap << ETH_MACECR_EIPG_Pos));

  /* Write to MACECR */
  STM32_MODIFY_REG(p_eth_instance->MACECR, ETH_MACECR_MASK, macregval);

  /*------------------------ MACWJBTR Configuration --------------------*/
  macregval = ((uint32_t)macconf->programmable_wd |
               (uint32_t)macconf->rx_wd_timeout_byte);

  /* Write to MACWJBTR */
  STM32_MODIFY_REG(p_eth_instance->MACWJBTR, ETH_MACWJBTR_MASK, macregval);

  /*------------------------ MACQ0TXFCR Configuration --------------------*/
  macregval = ((uint32_t)(macconf->tx_pause_time << ETH_MACQTXFCR_PT_Pos) |
               (uint32_t)macconf->zero_quanta_pause |
               (uint32_t)macconf->pause_low_threshold |
               (uint32_t)macconf->tr_flow_ctrl);

  /* Write to ETH_MACQTXFCR */
  STM32_MODIFY_REG(p_eth_instance->MACQTXFCR, ETH_MACQTXFCR_MASK, macregval);

  /*------------------------ MACRXFCR Configuration --------------------*/
  macregval = ((uint32_t)macconf->uc_pause_pkt_detect |
               (uint32_t)macconf->receive_flow_ctrl);

  /* Write to MACRXFCR */
  STM32_MODIFY_REG(p_eth_instance->MACRXFCR, ETH_MACRXFCR_MASK, macregval);

  /* Enable vlan tag on Rx status */
  STM32_SET_BIT(p_eth_instance->MACVTR, ETH_MACVTR_EVLRXS);
}

/**
  * @brief  Initialize MTL registers with driver default values.
  * @param  heth Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  */
static void ETH_MTL_Init(struct hal_eth_handle_s *heth)
{
  hal_eth_mtl_config_t mtlDefaultConf;

  /*--------------- ETHERNET MTL registers default Configuration --------------*/
  /* Common configuration for Q0 and Q1*/
  mtlDefaultConf.tx_fwd_status = HAL_ETH_MTL_TX_FWD_STATUS_ENABLE;

  /* MTL default configuration */
  ETH_SetMTLConfig(heth, &mtlDefaultConf);
}

/**
  * @brief  Apply MTL configuration to hardware registers.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  mtlconf Pointer to a hal_eth_mtl_config_t structure containing MTL settings.
  */
static void ETH_SetMTLConfig(hal_eth_handle_t *heth, const hal_eth_mtl_config_t *mtlconf)
{
  uint32_t mtlregval;

  /*------------------------ MTLOMR Configuration --------------------*/
  mtlregval = ((uint32_t) mtlconf->tx_fwd_status);


  /* Write to MTLOMR */
  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->MTLOMR, ETH_MTLOMR_MASK, mtlregval);
}

/**
  * @brief  Initialize DMA registers with driver default values.
  * @param  heth Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  */
static void ETH_DMA_Init(struct hal_eth_handle_s *heth)
{
  hal_eth_dma_config_t dmaDefaultConf;

  /*--------------- ETHERNET DMA registers default Configuration --------------*/
  /* Common DMA configuration */
  dmaDefaultConf.addr_aligned_beats = HAL_ETH_DMA_ADDR_ALIGN_ENABLE;
  dmaDefaultConf.burst_mode = HAL_ETH_DMA_BURST_LEN_FIXED;
  dmaDefaultConf.mixed_burst = HAL_ETH_DMA_MIXED_BURST_MODE_ENABLED;
  dmaDefaultConf.rebuild_inc_burst = HAL_ETH_DMA_REBUILD_INC_BURST_ENABLED;
  dmaDefaultConf.tr_priority = HAL_ETH_DMA_TR_PRIO_ENABLE;

  /* DMA default configuration */
  ETH_SetDMAConfig(heth, &dmaDefaultConf);
}

/**
  * @brief  Apply DMA configuration to hardware registers.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  dmaconf Pointer to a hal_eth_dma_config_t structure containing DMA settings.
  */
static void ETH_SetDMAConfig(hal_eth_handle_t *heth, const hal_eth_dma_config_t *dmaconf)
{
  uint32_t dmaregval;

  /*------------------------ DMAMR Configuration --------------------*/
  dmaregval = (uint32_t) dmaconf->tr_priority;

  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->DMAMR, ETH_DMAMR_MASK, dmaregval);

  /*------------------------ DMASBMR Configuration --------------------*/
  dmaregval = ((uint32_t) dmaconf->addr_aligned_beats |
               (uint32_t) dmaconf->mixed_burst |
               (uint32_t) dmaconf->rebuild_inc_burst |
               (uint32_t) dmaconf->burst_mode);

  STM32_MODIFY_REG(ETH_GET_INSTANCE(heth)->DMASBMR, ETH_DMASBMR_MASK, dmaregval);
}

/**
  * @brief  Initialize a Tx channel with default DMA and MTL settings.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  channel Channel index (zero-based)
  */
static void ETH_ChannelTxInit(hal_eth_handle_t *heth, uint32_t channel)
{
  hal_eth_dma_tx_channel_config_t dmaTxChannelDefaultConf;
  hal_eth_mtl_tx_queue_config_t   mtlTxQueueDefaultConf;

  /* set default desc alignment */
  heth->tx_channels[channel].tx_desc_list.desc_len_byte = sizeof(eth_dma_descriptor_t);

  /*------------------ DMA Tx Descriptors Configuration ----------------------*/
  /* Get the Tx DMA Channel Instance */
  heth->tx_channels[channel].p_dma_instance = ETH_GET_DMA_CHANNEL(heth, channel);

  /* Tx Queues configuration */
  dmaTxChannelDefaultConf.tx_pbl_x8_mode = HAL_ETH_DMA_TX_PBL_X8_DISABLE;
  dmaTxChannelDefaultConf.tx_dma_burst_length = HAL_ETH_DMA_TX_BLEN_4_BEAT;
  dmaTxChannelDefaultConf.tx_second_pkt_operate = HAL_ETH_DMA_TX_SEC_PKT_OP_DISABLE;

  ETH_SetDMATxChannelConfig(heth, channel, &dmaTxChannelDefaultConf);

  /*------------------ MTL Tx Descriptors Configuration ----------------------*/
  /* Get the Tx MTL Channel Instance */
  heth->tx_channels[channel].p_mtl_instance = ETH_GET_MTL_QUEUE(heth, channel);

  /* Tx Queues configuration */
  mtlTxQueueDefaultConf.transmit_queue_mode = HAL_ETH_MTL_TX_Q_STORE_AND_FORWARD;
  mtlTxQueueDefaultConf.queue_op_mode = HAL_ETH_MTL_TX_QUEUE_ENABLED;
  mtlTxQueueDefaultConf.queue_size_byte = HAL_ETH_MTL_TX_QUEUE_SZ_2048_BYTE;

  ETH_SetMtlTxChannelConfig(heth, channel, &mtlTxQueueDefaultConf);
}

/**
  * @brief  Configure DMA registers for a Tx channel.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  ch      Channel index (zero-based)
  * @param  dmachconf Pointer to hal_eth_dma_tx_channel_config_t containing channel DMA settings.
  */
static void ETH_SetDMATxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_dma_tx_channel_config_t *dmachconf)
{
  uint32_t dmaregval;
  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);

  /*------------------------ DMAC0CR Configuration --------------------*/
  dmaregval = ((uint32_t)dmachconf->tx_pbl_x8_mode);

  STM32_MODIFY_REG(p_dma_instance->DMACXCR, ETH_DMACCR_PBLX8, dmaregval);


  /*------------------------ DMAC0TXCR Configuration --------------------*/
  dmaregval = ((uint32_t) dmachconf->tx_dma_burst_length         |
               (uint32_t) dmachconf->tx_second_pkt_operate);

  STM32_MODIFY_REG(p_dma_instance->DMACXTXCR, (ETH_DMACTXCR_TXPBL | ETH_DMACTXCR_OSF), dmaregval);
}

/**
  * @brief  Retrieve current DMA Tx channel configuration from hardware registers.
  * @param  heth       Pointer to a hal_eth_handle_t structure (ETH handle)
  * @param  ch         Channel index
  * @param  dmachconf  Pointer to a hal_eth_dma_tx_channel_config_t structure to fill
  */
static void ETH_GetDMATxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_dma_tx_channel_config_t *dmachconf)
{
  const ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);

  /*------------------------ Get DMACXCR Configuration --------------------*/
  dmachconf->tx_pbl_x8_mode          = (hal_eth_dma_tx_pbl_x8_mode_ctrl_t)((uint32_t)STM32_READ_BIT(
                                                                             p_dma_instance->DMACXCR,
                                                                             ETH_DMACCR_PBLX8));
  /*------------------------ DMACXTXCR Configuration --------------------*/
  dmachconf->tx_dma_burst_length    = (hal_eth_dma_tx_burst_length_t)((uint32_t)STM32_READ_BIT(
                                                                        p_dma_instance->DMACXTXCR,
                                                                        ETH_DMACTXCR_TXPBL));
  dmachconf->tx_second_pkt_operate  = (hal_eth_dma_tx_sec_pkt_op_ctrl_t)((uint32_t)STM32_READ_BIT(
                                                                           p_dma_instance->DMACXTXCR,
                                                                           ETH_DMACTXCR_OSF));
}

/**
  * @brief  Configure MTL registers for a Tx queue.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  ch      Queue index (zero-based)
  * @param  mtlchconf Pointer to hal_eth_mtl_tx_queue_config_t containing queue settings.
  */
static void ETH_SetMtlTxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_mtl_tx_queue_config_t *mtlchconf)
{
  uint32_t mtlregval;

  ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_MTL_GET_TX_INSTANCE(heth, ch);

  /*------------------------ MTLTXQXOMR Configuration ----------------------*/
  mtlregval = ((uint32_t) mtlchconf->queue_op_mode)       |
              ((uint32_t) mtlchconf->transmit_queue_mode) |
              ((uint32_t) mtlchconf->queue_size_byte);

  /* Write to MTLTXQ3OMR */
  STM32_MODIFY_REG(p_mtl_instance->MTLTXQXOMR, ETH_MTLTXQXOMR_MASK, mtlregval);

}

/**
  * @brief  Retrieve current MTL Tx queue configuration from hardware registers.
  * @param  heth      Pointer to a hal_eth_handle_t structure (ETH handle)
  * @param  ch        Queue index
  * @param  mtlchconf Pointer to a hal_eth_mtl_tx_queue_config_t structure to fill
  */
static void ETH_GetMtlTxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_mtl_tx_queue_config_t *mtlchconf)
{

  const ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_MTL_GET_TX_INSTANCE(heth, ch);

  /*------------------------ Get DMACXCR Configuration --------------------*/
  mtlchconf->queue_op_mode        = (hal_eth_mtl_tx_ops_mode_t)((uint32_t)STM32_READ_BIT(p_mtl_instance->MTLTXQXOMR,
                                                                ETH_MTLTXQOMR_TXQEN));
  mtlchconf->queue_size_byte      = (hal_eth_mtl_tx_queue_size_t)((uint32_t)STM32_READ_BIT(p_mtl_instance->MTLTXQXOMR,
                                                                  ETH_MTLTXQOMR_TQS));
  mtlchconf->transmit_queue_mode  = (hal_eth_mtl_tx_transmit_mode_t)
                                    ((uint32_t)STM32_READ_BIT(p_mtl_instance->MTLTXQXOMR,
                                                              (ETH_MTLTXQOMR_TSF | ETH_MTLTXQOMR_TTC)));

}

/**
  * @brief  Initialize an Rx channel with default DMA and MTL settings.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  channel Channel index (zero-based)
  */
static void ETH_ChannelRxInit(hal_eth_handle_t *heth, uint32_t channel)
{
  hal_eth_dma_rx_channel_config_t dmaRxChannelDefaultConf;
  hal_eth_mtl_rx_queue_config_t   mtlRxQueueDefaultConf;

  /* set default desc alignments */
  heth->rx_channels[channel].rx_desc_list.desc_len_byte = sizeof(eth_dma_descriptor_t);

  /*------------------ DMA Tx Descriptors Configuration ----------------------*/
  /* Get the Rx DMA Channel Instance */
  heth->rx_channels[channel].p_dma_instance = (void *)ETH_GET_DMA_CHANNEL(heth, channel);

  /* Rx Queues configuration */
  dmaRxChannelDefaultConf.rx_dma_burst_length = HAL_ETH_DMA_RX_BLEN_4_BEAT;
  dmaRxChannelDefaultConf.rx_buffer_len_byte = ETH_DMA_RX_BUFFER_SIZE_BYTE;

  ETH_SetDMARxChannelConfig(heth, channel, &dmaRxChannelDefaultConf);

  /*------------------ MTL Rx Descriptors Configuration ----------------------*/
  /* Get the Rx MTL Channel Instance */
  heth->rx_channels[channel].p_mtl_instance = (void *)ETH_GET_MTL_QUEUE(heth, channel);

  /* Rx Queues configuration */
  mtlRxQueueDefaultConf.queue_op_mode = HAL_ETH_MTL_RX_QUEUE_ENABLED;
  mtlRxQueueDefaultConf.queue_size_byte = HAL_ETH_MTL_RX_QUEUE_SZ_2048_BYTE;
  mtlRxQueueDefaultConf.drop_tcp_ip_csum_error_pkt = HAL_ETH_MTL_RX_DROP_CS_ERR_ENABLE;
  mtlRxQueueDefaultConf.fwd_error_pkt = HAL_ETH_MTL_RX_FWD_ERR_PKT_DISABLE;
  mtlRxQueueDefaultConf.fwd_undersized_good_pkt = HAL_ETH_MTL_RX_FWD_USZ_PKT_ENABLE;
  mtlRxQueueDefaultConf.receive_queue_mode = HAL_ETH_MTL_RX_Q_STORE_AND_FORWARD;
  ETH_SetMtlRxChannelConfig(heth, channel, &mtlRxQueueDefaultConf);
}

/**
  * @brief  Configure DMA registers for an Rx channel.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  ch      Channel index (zero-based)
  * @param  dmachconf Pointer to hal_eth_dma_rx_channel_config_t containing channel DMA settings.
  */
static void ETH_SetDMARxChannelConfig(hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_dma_rx_channel_config_t *dmachconf)
{
  uint32_t dmaregval;
  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);

  /*------------------------ set Channel Rx buffer size --------------------*/
  heth->rx_channels[ch].rx_buff_size_byte = dmachconf->rx_buffer_len_byte;

  /*------------------------ DMACXRXCR Configuration --------------------*/
  dmaregval = ((uint32_t)(dmachconf->rx_dma_burst_length) |
               (uint32_t)(dmachconf->rx_buffer_len_byte << ETH_DMACRXCR_RBSZ_Pos));

  STM32_MODIFY_REG(p_dma_instance->DMACXRXCR,
                   (ETH_DMACRXCR_RXPBL | ETH_DMACRXCR_RPF | ETH_DMACRXCR_RBSZ),
                   dmaregval);
}

/**
  * @brief  Retrieve current DMA Rx channel configuration from hardware registers.
  * @param  heth       Pointer to a hal_eth_handle_t structure (ETH handle)
  * @param  ch         Channel index
  * @param  dmachconf  Pointer to a hal_eth_dma_rx_channel_config_t structure to fill
  */
static void ETH_GetDMARxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_dma_rx_channel_config_t *dmachconf)
{
  const ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);

  /*------------------------ Get DMACXRXCR Configuration --------------------*/
  dmachconf->rx_dma_burst_length = (hal_eth_dma_rx_burst_length_t)((uint32_t)STM32_READ_BIT(p_dma_instance->DMACXRXCR,
                                                                   ETH_DMACRXCR_RXPBL));
  dmachconf->rx_buffer_len_byte = (uint32_t)(STM32_READ_BIT(p_dma_instance->DMACXRXCR, ETH_DMACRXCR_RBSZ) >>
                                             ETH_DMACRXCR_RBSZ_Pos);
}

/**
  * @brief  Configure MTL registers for an Rx queue.
  * @param  heth    Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  * @param  ch      Queue index (zero-based)
  * @param  mtlchconf Pointer to hal_eth_mtl_rx_queue_config_t containing queue settings.
  */
static void ETH_SetMtlRxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      const hal_eth_mtl_rx_queue_config_t *mtlchconf)
{
  uint32_t mtlregval;

  ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_MTL_GET_RX_INSTANCE(heth, ch);


  /*------------------------ MTLRXQXOMR Configuration ----------------------*/
  mtlregval = ((uint32_t) mtlchconf->queue_size_byte)       |
              ((uint32_t) mtlchconf->drop_tcp_ip_csum_error_pkt) |
              ((uint32_t) mtlchconf->fwd_error_pkt) |
              ((uint32_t) mtlchconf->fwd_undersized_good_pkt) |
              ((uint32_t) mtlchconf->receive_queue_mode);

  /* Write to MTLRXQXOMR */
  STM32_MODIFY_REG(p_mtl_instance->MTLRXQXOMR, ETH_MTLRXQXOMR_MASK, mtlregval);
}

/**
  * @brief  Retrieve current MTL Rx queue configuration from hardware registers.
  * @param  heth      Pointer to a hal_eth_handle_t structure (ETH handle)
  * @param  ch        Queue index (zero-based)
  * @param  mtlchconf Pointer to a hal_eth_mtl_rx_queue_config_t structure to fill
  */
static void ETH_GetMtlRxChannelConfig(const hal_eth_handle_t *heth, uint32_t ch,
                                      hal_eth_mtl_rx_queue_config_t *mtlchconf)
{
  const ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_MTL_GET_RX_INSTANCE(heth, ch);

  /* Rx Queue is always enabled */
  mtlchconf->queue_op_mode = HAL_ETH_MTL_RX_QUEUE_ENABLED;

  /*------------------------ Get MTLRXQXOMR Configuration ----------------------*/
  mtlchconf->queue_size_byte = (hal_eth_mtl_rx_queue_size_t)((uint32_t)STM32_READ_BIT(p_mtl_instance->MTLRXQXOMR,
                                                             ETH_MTLRXQOMR_RQS));
  mtlchconf->drop_tcp_ip_csum_error_pkt = (hal_eth_mtl_rx_drop_cs_err_ctrl_t)
                                          ((uint32_t)STM32_READ_BIT(p_mtl_instance->MTLRXQXOMR,
                                                                    ETH_MTLRXQOMR_DIS_TCP_EF));
  mtlchconf->fwd_error_pkt = (hal_eth_mtl_rx_fwd_err_pkt_ctrl_t)((uint32_t)STM32_READ_BIT(p_mtl_instance->MTLRXQXOMR,
                                                                 ETH_MTLRXQOMR_FEP));
  mtlchconf->fwd_undersized_good_pkt = (hal_eth_mtl_rx_fwd_usz_pkt_ctrl_t)((uint32_t)STM32_READ_BIT(
                                                                             p_mtl_instance->MTLRXQXOMR,
                                                                             ETH_MTLRXQOMR_FUP));
  mtlchconf->receive_queue_mode = (hal_eth_mtl_rx_queue_mode_t)
                                  ((uint32_t)STM32_READ_BIT(p_mtl_instance->MTLRXQXOMR,
                                                            (ETH_MTLRXQOMR_RSF | ETH_MTLRXQOMR_RTC)));

}

/**
  * @brief  Stop an Rx DMA channel and disable MAC Rx if applicable.
  *
  * This routine disables the Rx DMA for the specified channel, recycles all
  * associated Rx descriptors, and if all Rx channels are stopped, it disables
  * the MAC receiver.
  *
  * @param  heth Pointer to a hal_eth_handle_t structure.
  * @param  ch   Zero-based Rx channel index.
  * @retval HAL_OK Channel stopped successfully.
  */
static hal_status_t ETH_StopRxChannel(hal_eth_handle_t *heth, uint32_t ch)
{
  uint32_t tickstart;
  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);

  /* Disable the DMA transmission for Rx Channel */
  STM32_CLEAR_BIT(p_dma_instance->DMACXRXCR, ETH_DMACRXCR_SR);

  /* Wait for the receive process to stop */
  tickstart = HAL_GetTick();
  while (ETH_DMA_GetRxProcessState(ETH_GET_INSTANCE(heth), ch) != ETH_RX_DMA_PROCESS_STOPPED)
  {
    if ((HAL_GetTick() - tickstart) > ETH_RX_DMA_STOP_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  /* Recycle all Rx descriptors */
  ETH_RecycleRxDesc(heth, ch);

  /* Reset Rx desc list */
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.p_desc_list_addr, NULL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.total_desc_cnt, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.curr_desc_id, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.built_desc_id, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.buff_in_use, 0UL);

  /* Stop the MAC receiver */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_RE);
  return HAL_OK;
}

/**
  * @brief  Stop a Tx DMA channel and flush its transmit queue.
  *
  * This routine disables the Tx DMA for the specified channel, waits for the
  * corresponding MTL Tx queue to become empty within the configured timeout,
  * then recycles all Tx descriptors. If all Tx channels are stopped after this
  * operation, the MAC transmitter is also disabled.
  *
  * @param  heth Pointer to a hal_eth_handle_t structure.
  * @param  ch   Zero-based Tx channel index.
  * @retval HAL_OK    Channel stopped successfully.
  * @retval HAL_ERROR Timeout occurred while flushing the Tx queue.
  */
static hal_status_t ETH_StopTxChannel(hal_eth_handle_t *heth, uint32_t ch)
{
  uint32_t tickstart;
  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);
  ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_MTL_GET_TX_INSTANCE(heth, ch);

  /* Stop the Tx DMA transmission */
  STM32_CLEAR_BIT(p_dma_instance->DMACXTXCR, ETH_DMACTXCR_ST);

  /* Wait for the transmit process to stop */
  tickstart = HAL_GetTick();
  while (ETH_DMA_GetTxProcessState(ETH_GET_INSTANCE(heth), ch) != ETH_TX_DMA_PROCESS_STOPPED)
  {
    if ((HAL_GetTick() - tickstart) > ETH_TX_DMA_STOP_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  /* Flush Tx Queue */
  STM32_SET_BIT(p_mtl_instance->MTLTXQXOMR, ETH_MTLTXQOMR_FTQ);
  /* Wait for the flush operation */
  tickstart = HAL_GetTick();
  while (STM32_READ_BIT(p_mtl_instance->MTLTXQXOMR, ETH_MTLTXQOMR_FTQ) != 0UL)
  {
    if ((HAL_GetTick() - tickstart) > ETH_TX_Q_FLUSH_TIMEOUT)
    {
      return HAL_ERROR;
    }
  }

  /* Recycle all Tx descriptors */
  ETH_RecycleTxDesc(heth, ch);

  /* Reset Tx desc list */
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.p_desc_list_addr, NULL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.total_desc_cnt, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.curr_desc_id, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.built_desc_id, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.buff_in_use, 0UL);

  /* Stop the MAC transmitter */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_TE);
  return HAL_OK;
}


/**
  * @brief  Retrieve Tx DMA process state for a channel.
  * @param  p_eth Pointer to ETH peripheral instance.
  * @param  ch    Zero-based Tx channel index.
  * @retval eth_tx_dma_process_state_t Current Tx DMA process state.
  */
static eth_tx_dma_process_state_t ETH_DMA_GetTxProcessState(const ETH_TypeDef *p_eth, uint32_t ch)
{
  uint32_t process_masked;
  uint32_t process_pos;
  eth_tx_dma_process_state_t state = ETH_TX_DMA_PROCESS_UNKNOWN;

  if (ch <= ETH_TX_DMA_CH_STATE_MAX_IDX)
  {
    /* Read raw Tx process field for channel `ch` */
    process_masked = (uint32_t)STM32_READ_BIT(p_eth->DMADSR,
                                              (ETH_DMADSR_TPS0 << (ETH_TPS_FIELD_WIDTH_BITS * (ch))));
    /* Compute bit position for the selected channel field */
    process_pos = (ETH_DMADSR_TPS0_Pos + (ETH_TPS_FIELD_WIDTH_BITS * (ch)));

    /* Extract and cast to @ref eth_tx_dma_process_state_t */
    state = (eth_tx_dma_process_state_t)((uint32_t)(process_masked >> process_pos));
  }
  return state;
}

/**
  * @brief  Retrieve Rx DMA process state for a channel.
  * @param  p_eth Pointer to ETH peripheral instance.
  * @param  ch    Zero-based Rx channel index.
  * @retval eth_rx_dma_process_state_t Current Rx DMA process state.
  */
static eth_rx_dma_process_state_t ETH_DMA_GetRxProcessState(const ETH_TypeDef *p_eth, uint32_t ch)
{
  uint32_t process_masked;
  uint32_t process_pos;
  eth_rx_dma_process_state_t state;

  /* Read raw Rx process field for channel `ch` */
  process_masked = (uint32_t)STM32_READ_BIT(p_eth->DMADSR,
                                            (ETH_DMADSR_RPS0 << (ETH_RPS_FIELD_WIDTH_BITS * (ch))));

  /* Compute bit position for the selected channel field */
  process_pos = (ETH_DMADSR_RPS0_Pos + (ETH_RPS_FIELD_WIDTH_BITS * (ch)));

  /* Extract and cast to @ref eth_rx_dma_process_state_t */
  state = (eth_rx_dma_process_state_t)((uint32_t)(process_masked >> process_pos));

  return state;
}

/**
  * @brief  Abort and reset an Rx DMA channel.
  *
  * Stops the Rx DMA engine for the specified channel, recycles all
  * channel descriptors and clears the software descriptor bookkeeping.
  *
  * @param  heth Pointer to the HAL ETH handle. Must not be NULL.
  * @param  ch   Rx channel identifier
  */
static void ETH_AbortRxChannel(hal_eth_handle_t *heth, uint32_t ch)
{
  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);

  hal_eth_channel_state_t rx_state = heth->rx_channels[ch].channel_state;
  if ((rx_state != HAL_ETH_CHANNEL_STATE_ACTIVE)
      && (rx_state != HAL_ETH_CHANNEL_STATE_SUSPENDED))
  {
    return;
  }
  /* Disable the DMA transmission for Rx Channel */
  STM32_CLEAR_BIT(p_dma_instance->DMACXRXCR, ETH_DMACRXCR_SR);

  /* Recycle all Rx descriptors */
  ETH_RecycleRxDesc(heth, ch);

  /* Reset Rx desc list */
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.p_desc_list_addr, NULL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.total_desc_cnt, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.curr_desc_id, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.built_desc_id, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.buff_in_use, 0UL);
  /* Stop the MAC receiver */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_RE);
}
/**
  * @brief  Abort and reset a Tx DMA channel.
  *
  * Stops the Tx DMA engine for the specified channel, flushes the MTL
  * transmit queue, recycles all channel descriptors and clears the software
  * descriptor bookkeeping.
  * @param  heth Pointer to the HAL ETH handle.
  * @param  ch   Tx channel identifier
  */
static void ETH_AbortTxChannel(hal_eth_handle_t *heth, uint32_t ch)
{
  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);
  ETH_MTL_Queue_TypeDef *p_mtl_instance = ETH_MTL_GET_TX_INSTANCE(heth, ch);

  hal_eth_channel_state_t tx_state = heth->tx_channels[ch].channel_state;
  if ((tx_state != HAL_ETH_CHANNEL_STATE_ACTIVE)
      && (tx_state != HAL_ETH_CHANNEL_STATE_SUSPENDED))
  {
    return;
  }

  /* Stop the Tx DMA transmission */
  STM32_CLEAR_BIT(p_dma_instance->DMACXTXCR, ETH_DMACTXCR_ST);
  /* Flush Tx Queue */
  STM32_SET_BIT(p_mtl_instance->MTLTXQXOMR, ETH_MTLTXQOMR_FTQ);

  /* Recycle all Tx descriptors */
  ETH_RecycleTxDesc(heth, ch);

  /* Reset Tx desc list */
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.p_desc_list_addr, NULL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.total_desc_cnt, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.curr_desc_id, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.built_desc_id, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.buff_in_use, 0UL);
  /* Stop the MAC transmitter */
  STM32_CLEAR_BIT(ETH_GET_INSTANCE(heth)->MACCR, ETH_MACCR_TE);
}

/**
  * @brief  Reset a DMA descriptor to its default state.
  *
  * This clears descriptor words and backup pointers so the descriptor can be
  * reused by the driver or re-initialized prior to programming for DMA.
  *
  * @param  p_dma_txDesc Pointer to the DMA descriptor to reset
  */
static void ETH_ResetDMADesc(eth_dma_descriptor_t *p_dma_txDesc)
{
  STM32_WRITE_REG(p_dma_txDesc->DESC0, 0x0UL);
  STM32_WRITE_REG(p_dma_txDesc->DESC1, 0x0UL);
  STM32_WRITE_REG(p_dma_txDesc->DESC2, 0x0UL);
  STM32_WRITE_REG(p_dma_txDesc->DESC3, 0x0UL);
  STM32_WRITE_REG(p_dma_txDesc->p_pkt_addr, NULL);
  STM32_WRITE_REG(p_dma_txDesc->p_app_data, NULL);
}

/**
  * @brief  Update RX descriptor attach application buffers.
  * @param  heth Pointer to HAL ETH handle
  * @param  ch   RX channel index
  */
static void ETH_UpdateRxDesc(hal_eth_handle_t *heth, uint32_t ch)
{
  eth_dma_descriptor_t *p_dma_RxDesc;
  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);

  uint32_t rx_desc_idx        = heth->rx_channels[ch].rx_desc_list.curr_desc_id;
  uint32_t rx_total_used_desc = heth->rx_channels[ch].rx_desc_list.buff_in_use;

  while (rx_total_used_desc < heth->rx_channels[ch].rx_desc_list.total_desc_cnt)
  {
    p_dma_RxDesc = ETH_GET_DESC_INDEX(heth->rx_channels[ch].rx_desc_list, rx_desc_idx);

    if (p_dma_RxDesc->p_pkt_addr == NULL)
    {
      void *p_RxBuffer = NULL;
      void *p_AppContext = NULL;

      /* Get App Rx buffer and App context*/
      heth->rx_channels[ch].p_rx_allocate_cb(heth, ETH_GET_RX_CH_ID(ch),
                                             heth->rx_channels[ch].rx_buff_size_byte, &p_RxBuffer,
                                             &p_AppContext);
      if (p_RxBuffer != NULL)
      {
        /* Set Rx Buffer Address */
        STM32_WRITE_REG(p_dma_RxDesc->DESC0, ETH_CAST_PTR_TO_U32(p_RxBuffer));

        /* Save Buffer reference in backup*/
        STM32_WRITE_REG(p_dma_RxDesc->p_pkt_addr, p_RxBuffer);
        /* Save Application Context*/
        STM32_WRITE_REG(p_dma_RxDesc->p_app_data, p_AppContext);
      }
      else
      {
        /* No buffer available, stop the allocation */
        break;
      }
    }
    else
    {
      /* Descriptor was used as a context descriptor, buffer still unused */
      STM32_WRITE_REG(p_dma_RxDesc->DESC0, ETH_CAST_PTR_TO_U32(p_dma_RxDesc->p_pkt_addr));
    }
    /* Set buffer 1 valid bit */
    STM32_SET_BIT(p_dma_RxDesc->DESC3, ETH_DMA_RX_DESC_RF_BUF1V);
    ETH_SetRxFifoEvent(heth, ch, p_dma_RxDesc);
    /* Ensure completion of descriptor preparation before reception start */
    __DSB();

    /* Move Desc to DMA */
    STM32_SET_BIT(p_dma_RxDesc->DESC3, ETH_DMA_RX_DESC_RF_OWN);

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_cache_flush_cb(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                           heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_CacheFlushCallback(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                               heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

    /* pass to next desc */
    ETH_INCR_DESC_INDEX(rx_desc_idx, heth->rx_channels[ch].rx_desc_list.total_desc_cnt);
    rx_total_used_desc++;
  }
  /* Set Receive Descriptor Tail pointer Address for DMA Channel */
  STM32_WRITE_REG(p_dma_instance->DMACXRXDTPR, 0UL);

  /* incr built desc id */
  heth->rx_channels[ch].rx_desc_list.curr_desc_id = rx_desc_idx;
  /* incr Buffer in use cnt*/
  heth->rx_channels[ch].rx_desc_list.buff_in_use = rx_total_used_desc;
}

/**
  * @brief  Request and program DMA descriptors for a TX packet.
  *
  * Prepares one or more DMA TX descriptors for the provided packet buffers
  * and notifies the DMA engine to start transmission.
  *
  * @param  heth         Pointer to HAL ETH handle
  * @param  ch           TX channel index (zero-based)
  * @param  p_eth_buffer Pointer to an array of buffer descriptors containing data pointers and lengths
  * @param  buffer_count Number of buffers in p_eth_buffer
  * @param  p_tx_conf    Pointer to TX packet configuration (VLAN/CSUM/notify etc.)
  * @retval HAL_OK       Descriptors programmed and DMA notified successfully
  * @retval HAL_BUSY     Not enough free descriptors available to queue the packet
  */
static hal_status_t ETH_RequestTxDMA(hal_eth_handle_t *heth, uint32_t ch, hal_eth_buffer_t *p_eth_buffer,
                                     uint32_t buffer_count, hal_eth_tx_pkt_config_t *p_tx_conf)
{
  eth_dma_descriptor_t *p_dma_txDesc;
  uint32_t desc_idx;
  ETH_DMA_Channel_TypeDef *p_dma_instance;
  uint32_t needed_desc_cnt = buffer_count;

  /* Get Channel DMA instance */
  p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);
  /* Get ETH Instance */
  ETH_TypeDef *p_eth_instance = ETH_GET_INSTANCE(heth);

  /* Get total needed descriptors for transmission */
  if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_VLANTAG | HAL_ETH_TX_PKT_CTRL_INNERVLANTAG) != 0UL)
  {
    needed_desc_cnt++;
  }
  /* Check for available descriptors*/
  if (needed_desc_cnt >
      (heth->tx_channels[ch].tx_desc_list.total_desc_cnt - heth->tx_channels[ch].tx_desc_list.buff_in_use))
  {
    /* No Free Descriptors available */
    return HAL_BUSY;
  }
  /* Get Current available Tx Descriptor */
  desc_idx = heth->tx_channels[ch].tx_desc_list.curr_desc_id;
  /* Get Descriptor Address */
  p_dma_txDesc = ETH_GET_DESC_INDEX(heth->tx_channels[ch].tx_desc_list, desc_idx);

  /*****************    Context descriptor configuration *****************************/
  /* check for VLAN Tag feature */
  if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_VLANTAG) != 0UL)
  {
    /* Set vlan tag value */
    STM32_MODIFY_REG(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_CTXT_VT, p_tx_conf->vlan_tag_id);
    /* Set vlan tag valid bit */
    STM32_SET_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_CTXT_VLTV);
    /* Set Vlan Tag input */
    STM32_SET_BIT(p_eth_instance->MACVIR, ETH_MACVIR_VLTI);
  }
  /* if inner VLAN is enabled */
  if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_INNERVLANTAG) != 0UL)
  {
    /* Set inner vlan tag value */
    STM32_MODIFY_REG(p_dma_txDesc->DESC2, ETH_DMA_TX_DESC_CTXT_IVT, (p_tx_conf->inner_vlan_tag_id << 16));
    /* Set inner vlan tag valid bit */
    STM32_SET_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_CTXT_IVLTV);
    /* Set Vlan Tag control */
    STM32_MODIFY_REG(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_CTXT_IVTIR, (uint32_t)p_tx_conf->inner_vlan_ctrl);
    /* Set the descriptor as the inner vlan input source */
    STM32_SET_BIT(p_eth_instance->MACIVIR, ETH_MACIVIR_VLTI);
    /* Enable double VLAN processing */
    STM32_SET_BIT(p_eth_instance->MACVTR, ETH_MACVTR_EDVLP);
  }
  if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_VLANTAG | HAL_ETH_TX_PKT_CTRL_INNERVLANTAG) != 0UL)
  {
    /* Set as context descriptor */
    STM32_SET_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_CTXT_CTXT);
    /* Ensure rest of descriptor is written to RAM before the OWN bit */
    __DMB();
    /* Set own bit */
    STM32_SET_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_CTXT_OWN);
    __DSB();
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_cache_flush_cb(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                           heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_CacheFlushCallback(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                               heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
    /* Increment total used desc */
    heth->tx_channels[ch].tx_desc_list.buff_in_use++;
    /* Increment current tx descriptor index */
    ETH_INCR_DESC_INDEX(desc_idx, heth->tx_channels[ch].tx_desc_list.total_desc_cnt);
    /* Get current descriptor address */
    p_dma_txDesc = ETH_GET_DESC_INDEX(heth->tx_channels[ch].tx_desc_list, desc_idx);
  }

  /*****************    Normal descriptors configuration     ******************************/
  /* Mark it as First Descriptor */
  STM32_SET_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_RF_FD);
  /* Check for CRC Padding feature, Valid only for first descriptor */
  if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_CRCPAD) != 0UL)
  {
    /* Set CRC Padding control */
    STM32_MODIFY_REG(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_RF_CPC, (uint32_t)p_tx_conf->crc_pad_ctrl);
  }
  for (uint32_t index = 0; index < buffer_count; index++)
  {
    /* Set packet address */
    STM32_WRITE_REG(p_dma_txDesc->DESC0, ETH_CAST_PTR_TO_U32(p_eth_buffer[index].p_buffer));
    /* Set packet Length */
    STM32_MODIFY_REG(p_dma_txDesc->DESC2, ETH_DMA_TX_DESC_RF_B1L, p_eth_buffer[index].len_byte);
    /* Save packet reference in backup*/
    STM32_WRITE_REG(p_dma_txDesc->p_pkt_addr, p_eth_buffer[index].p_buffer);
    /* Save Application context */
    STM32_WRITE_REG(p_dma_txDesc->p_app_data, p_tx_conf->p_data);
    /* Check CSUM feature */
    if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_CSUM) != 0UL)
    {
      /* Set csum config */
      STM32_MODIFY_REG(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_RF_CIC, (uint32_t)p_tx_conf->csum_ctrl);
    }
    /* Check source address insertion/replacement */
    if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_SAIC) != 0UL)
    {
      STM32_MODIFY_REG(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_RF_SAIC, (uint32_t)p_tx_conf->src_addr_ctrl);
    }
    /* Check for VLAN Tag feature */
    if (STM32_READ_BIT(p_tx_conf->attributes, HAL_ETH_TX_PKT_CTRL_VLANTAG) != 0UL)
    {
      /* Set Vlan Tag control */
      STM32_MODIFY_REG(p_dma_txDesc->DESC2, ETH_DMA_TX_DESC_RF_VTIR, (uint32_t)p_tx_conf->vlan_ctrl);
    }
    /* Check if Last Buffer to send */
    if (index == (buffer_count - 1UL))
    {
      /* Mark it as LAST descriptor */
      STM32_SET_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_RF_LD);
      /* Set the fifo event interruption for last descriptor */
      ETH_SetTxFifoEven(heth, ch, p_dma_txDesc, p_tx_conf->notify);
    }
    __DMB();
    /* Set Own bit */
    STM32_SET_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_RF_OWN);
    __DSB();

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_cache_flush_cb(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                           heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_CacheFlushCallback(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                               heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

    /* Move to Next descriptor id */
    ETH_INCR_DESC_INDEX(desc_idx, heth->tx_channels[ch].tx_desc_list.total_desc_cnt);
    p_dma_txDesc = ETH_GET_DESC_INDEX(heth->tx_channels[ch].tx_desc_list, desc_idx);

    /* issue a poll command to Tx DMA by writing address of the last valid descriptor */
    STM32_WRITE_REG(p_dma_instance->DMACXTXDTPR, 0UL);
    /* Increment total used desc */
    heth->tx_channels[ch].tx_desc_list.buff_in_use++;
  }
  /* Set new Tx index */
  heth->tx_channels[ch].tx_desc_list.curr_desc_id = desc_idx;
  return HAL_OK;
}

/**
  * @brief  Configure RX descriptor FIFO event (interrupt) conditions.
  *
  * Depending on the channel FIFO event mode this will set the IOC bit on the
  * descriptor to generate an interrupt on completion or implement cyclic
  * counting behavior.
  *
  * @param  heth         Pointer to HAL ETH handle
  * @param  ch           RX channel index (zero-based)
  * @param  p_dma_rx_desc Pointer to the DMA RX descriptor to update
  */
static void ETH_SetRxFifoEvent(hal_eth_handle_t *heth, uint32_t ch, eth_dma_descriptor_t *p_dma_rx_desc)
{
  switch (heth->rx_channels[ch].fifo_event_config.event_mode)
  {
    case HAL_ETH_FIFO_EVENT_ALWAYS :
    {
      /* Set Interrupt Enabled on Completion */
      STM32_SET_BIT(p_dma_rx_desc->DESC3, ETH_DMA_RX_DESC_RF_IOC);
      break;
    }
    case HAL_ETH_FIFO_EVENT_CYCLIC :
    {
      if (heth->rx_channels[ch].event_cnt >= heth->rx_channels[ch].fifo_event_config.event_params)
      {
        /* Set Interrupt Enabled on Completion */
        STM32_SET_BIT(p_dma_rx_desc->DESC3, ETH_DMA_RX_DESC_RF_IOC);
      }
      ETH_INCR_FIFO_EVENT_CNT(heth->rx_channels[ch].event_cnt, heth->rx_channels[ch].fifo_event_config.event_params);
      break;
    }
    case HAL_ETH_FIFO_EVENT_NONE :
    default:
      break;
  }
}

/**
  * @brief  Configure TX descriptor FIFO event (interrupt) conditions.
  *
  * Depending on the channel FIFO event mode this will set the IOC bit on the
  * descriptor or force an interrupt when the packet requests notification.
  *
  * @param  heth       Pointer to HAL ETH handle
  * @param  ch         TX channel index (zero-based)
  * @param  dmatxdesc  Pointer to the DMA TX descriptor to update
  * @param  pkt_notify Packet notification control flags
  */
static void ETH_SetTxFifoEven(hal_eth_handle_t *heth, uint32_t ch, eth_dma_descriptor_t *dmatxdesc,
                              hal_eth_tx_pkt_notify_ctrl_t pkt_notify)
{
  switch (heth->tx_channels[ch].fifo_event_config.event_mode)
  {
    case HAL_ETH_FIFO_EVENT_ALWAYS :
    {
      /* Set Interrupt Enabled on Completion */
      STM32_SET_BIT(dmatxdesc->DESC2, ETH_DMA_TX_DESC_RF_IOC);
      break;
    }
    case HAL_ETH_FIFO_EVENT_CYCLIC :
    {
      if ((heth->tx_channels[ch].event_cnt >= heth->tx_channels[ch].fifo_event_config.event_params)
          || (pkt_notify == HAL_ETH_TX_PKT_NOTIFY_ENABLE))
      {
        /* Set Interrupt Enabled on Completion */
        STM32_SET_BIT(dmatxdesc->DESC2, ETH_DMA_TX_DESC_RF_IOC);
        heth->tx_channels[ch].event_cnt = 0;
      }
      ETH_INCR_FIFO_EVENT_CNT(heth->tx_channels[ch].event_cnt, heth->tx_channels[ch].fifo_event_config.event_params);
      break;
    }
    case HAL_ETH_FIFO_EVENT_NONE :
    default:
      break;
  }
}

/**
  * @brief  Initialize the DMA TX descriptor list for a channel.
  *
  * Sets the descriptor list address, computes the ring size, resets each
  * descriptor and programs the DMA channel descriptor pointers.
  *
  * @param  heth           Pointer to HAL ETH handle
  * @param  ch             TX channel index (zero-based)
  * @param  p_desc_mem     Pointer to the descriptor memory area
  * @param  total_mem_size_byte Size in bytes of the total descriptor memory area
  */
static void ETH_DMATxDescListInit(hal_eth_handle_t *heth, uint32_t ch, uint32_t *p_desc_mem,
                                  uint32_t total_mem_size_byte)
{
  eth_dma_descriptor_t *p_dma_txdesc;
  uint32_t i;

  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_TX_INSTANCE(heth, ch);

  /* Initialize the DMA Tx descriptor list */
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.p_desc_list_addr, p_desc_mem);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.total_desc_cnt,
                  ETH_GET_DESC_CNT(total_mem_size_byte, heth->tx_channels[ch].tx_desc_list));
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.curr_desc_id, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.built_desc_id, 0UL);
  STM32_WRITE_REG(heth->tx_channels[ch].tx_desc_list.buff_in_use, 0UL);

  /* Set the Skip Length */
  uint32_t SkipLength = ETH_GET_SKIPLEN_SIZE(heth->tx_channels[ch].tx_desc_list.desc_len_byte,
                                             sizeof(eth_dma_descriptor_t));
  STM32_MODIFY_REG(p_dma_instance->DMACXCR, ETH_DMACCR_DSL, SkipLength);

  /* Recycle DMATxDesc descriptors */
  for (i = 0; i < heth->tx_channels[ch].tx_desc_list.total_desc_cnt; i++)
  {
    p_dma_txdesc = ETH_GET_DESC_INDEX(heth->tx_channels[ch].tx_desc_list, i);
    ETH_ResetDMADesc(p_dma_txdesc);
  }

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
  heth->p_cache_flush_cb(heth, ETH_GET_TX_CH_ID(ch),
                         heth->tx_channels[ch].tx_desc_list.p_desc_list_addr, total_mem_size_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
  HAL_ETH_CacheFlushCallback(heth, ETH_GET_TX_CH_ID(ch),
                             heth->tx_channels[ch].tx_desc_list.p_desc_list_addr, total_mem_size_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

  /* Set Transmit Descriptor Ring Length for DMA Channel  */
  STM32_WRITE_REG(p_dma_instance->DMACXTXRLR, (heth->tx_channels[ch].tx_desc_list.total_desc_cnt - 1U));

  /* Set Transmit Descriptor List Address for DMA Channel */
  STM32_WRITE_REG(p_dma_instance->DMACXTXDLAR, (uint32_t) heth->tx_channels[ch].tx_desc_list.p_desc_list_addr);

  /* Set Transmit Descriptor Tail pointer for DMA Channel  */
  STM32_WRITE_REG(p_dma_instance->DMACXTXDTPR, (uint32_t) heth->tx_channels[ch].tx_desc_list.p_desc_list_addr);
}

/**
  * @brief  Initialize the DMA RX descriptor list for a channel.
  *
  * Sets the descriptor list address, computes the ring size, resets each
  * descriptor, updates RX descriptors with application buffers and programs
  * the DMA channel descriptor pointers.
  *
  * @param  heth           Pointer to HAL ETH handle
  * @param  ch             RX channel index (zero-based)
  * @param  p_desc_mem     Pointer to the descriptor memory area
  * @param  total_mem_size_byte Size in bytes of the total descriptor memory area
  */
static void ETH_DMARxDescListInit(hal_eth_handle_t *heth, uint32_t ch, uint32_t *p_desc_mem,
                                  uint32_t total_mem_size_byte)
{
  eth_dma_descriptor_t *p_dma_rxdesc;
  uint32_t i;

  ETH_DMA_Channel_TypeDef *p_dma_instance = ETH_DMA_GET_RX_INSTANCE(heth, ch);
  /* Initialize the DMA Rx descriptor list */
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.p_desc_list_addr, p_desc_mem);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.total_desc_cnt,
                  ETH_GET_DESC_CNT(total_mem_size_byte, heth->rx_channels[ch].rx_desc_list));
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.curr_desc_id, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.built_desc_id, 0UL);
  STM32_WRITE_REG(heth->rx_channels[ch].rx_desc_list.buff_in_use, 0UL);

  /* Set the Skip Length */
  uint32_t SkipLength = ETH_GET_SKIPLEN_SIZE(heth->rx_channels[ch].rx_desc_list.desc_len_byte,
                                             sizeof(eth_dma_descriptor_t));
  STM32_MODIFY_REG(p_dma_instance->DMACXCR, ETH_DMACCR_DSL, SkipLength);

  for (i = 0; i < heth->rx_channels[ch].rx_desc_list.total_desc_cnt; i++)
  {
    p_dma_rxdesc = ETH_GET_DESC_INDEX(heth->rx_channels[ch].rx_desc_list, i);
    ETH_ResetDMADesc(p_dma_rxdesc);
  }

  /* Update Rx descriptor with attached app buffer */
  ETH_UpdateRxDesc(heth, ch);

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
  /* Cache clean Rx descriptor */
  heth->p_cache_flush_cb(heth, ETH_GET_RX_CH_ID(ch),
                         heth->rx_channels[ch].rx_desc_list.p_desc_list_addr, total_mem_size_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
  HAL_ETH_CacheFlushCallback(heth, ETH_GET_RX_CH_ID(ch),
                             heth->rx_channels[ch].rx_desc_list.p_desc_list_addr, total_mem_size_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

  /* Set Receive Descriptor Ring Length for DMA Channel */
  STM32_WRITE_REG(p_dma_instance->DMACXRXRLR, (heth->rx_channels[ch].rx_desc_list.total_desc_cnt - 1UL));

  /* Set Receive Descriptor List Address for DMA Channel */
  STM32_WRITE_REG(p_dma_instance->DMACXRXDLAR, (uint32_t) heth->rx_channels[ch].rx_desc_list.p_desc_list_addr);

  /* Set Receive Descriptor Tail pointer Address for DMA Channel */
  STM32_WRITE_REG(p_dma_instance->DMACXRXDTPR,
                  (uint32_t)(ETH_GET_DESC_INDEX((heth->rx_channels[ch].rx_desc_list),
                                                (heth->rx_channels[ch].rx_desc_list.total_desc_cnt - 1UL))));
}

/**
  * @brief  Recycle RX descriptors and invoke RX complete callbacks.
  *
  * This function walks the list of built RX descriptors, invokes the
  * channel RX complete callback for each received packet (or context), then
  * resets the descriptor so it can be reused by the DMA engine.
  *
  * @param  heth Pointer to HAL ETH handle
  * @param  ch   RX channel index (zero-based)
  */
static void ETH_RecycleRxDesc(hal_eth_handle_t *heth, uint32_t ch)
{
  eth_dma_descriptor_t *p_dma_RxDesc;
  uint32_t pkt_size = 0;

  /* Get dma desc index */
  uint32_t rx_desc_idx        = heth->rx_channels[ch].rx_desc_list.built_desc_id;
  uint32_t rx_total_used_desc = heth->rx_channels[ch].rx_desc_list.buff_in_use;

  /* Recycle all used desc */
  while (rx_total_used_desc != 0UL)
  {
    hal_eth_rx_cb_pkt_data_t rx_pkt_data = {0};
    /* Get current built Rx dma descriptor */
    p_dma_RxDesc = ETH_GET_DESC_INDEX(heth->rx_channels[ch].rx_desc_list, rx_desc_idx);
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    /* Cache invalidate descriptor */
    heth->p_cache_invalidate_cb(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                                heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_CacheInvalidateCallback(heth, ETH_GET_RX_CH_ID(ch),
                                    p_dma_RxDesc, heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

    /* Determine if the packet Received  or a context descriptor */
    if (STM32_READ_BIT(p_dma_RxDesc->DESC3, (ETH_DMA_RX_DESC_WBF_OWN | ETH_DMA_RX_DESC_WBF_CTXT)) != 0UL)
    {
      /* Mark attached Rx Buffer as invalid */
      STM32_SET_BIT(rx_pkt_data.status, HAL_ETH_RX_STATUS_INVALID);
      pkt_size = heth->rx_channels[ch].rx_buff_size_byte;
    }
    else
    {
      /* Write received pkt size */
      pkt_size = STM32_READ_BIT(p_dma_RxDesc->DESC3, ETH_DMA_RX_DESC_WBF_PL);

      /* Determine if a last descriptor */
      if (STM32_READ_BIT(p_dma_RxDesc->DESC3, HAL_ETH_RX_STATUS_LD) != 0UL)
      {
        ETH_COPY_BITS(rx_pkt_data.status, (HAL_ETH_RX_STATUS_IPCB | HAL_ETH_RX_STATUS_IPV4 |
                                           HAL_ETH_RX_STATUS_IPV6), p_dma_RxDesc->DESC1);
        ETH_COPY_BITS(rx_pkt_data.status, HAL_ETH_RX_STATUS_ARPNR, p_dma_RxDesc->DESC2);
        ETH_COPY_BITS(rx_pkt_data.status, HAL_ETH_RX_STATUS_VLAN, p_dma_RxDesc->DESC3);

        /* Last Descriptor check if VLAN Tag received*/
        if (STM32_READ_BIT(p_dma_RxDesc->DESC3, HAL_ETH_RX_STATUS_VLAN) != 0UL)
        {
          /* Set vlan tag present status */
          ETH_COPY_BITS(rx_pkt_data.status, HAL_ETH_RX_STATUS_VLAN, p_dma_RxDesc->DESC3);
          /* Copy vlan tag value */
          STM32_WRITE_REG(rx_pkt_data.vlan_tag_ids, p_dma_RxDesc->DESC0);
        }
      }

      /* Set the received packet errors */
      if (STM32_READ_BIT(p_dma_RxDesc->DESC1, (HAL_ETH_RX_STATUS_IPV4 | HAL_ETH_RX_STATUS_IPV6)) != 0UL)
      {
        if (STM32_READ_BIT(p_dma_RxDesc->DESC1, HAL_ETH_RX_ERROR_IPH) != 0UL)
        {
          /* set IP header error */
          ETH_COPY_BITS(rx_pkt_data.errors, HAL_ETH_RX_ERROR_IPH, p_dma_RxDesc->DESC1);
        }
      }
      /* Set Errors */
      ETH_COPY_BITS(rx_pkt_data.errors, HAL_ETH_RX_ERROR_IPC, p_dma_RxDesc->DESC1);
      ETH_COPY_BITS(rx_pkt_data.errors, (HAL_ETH_RX_ERROR_DB | HAL_ETH_RX_ERROR_REC
                                         | HAL_ETH_RX_ERROR_OFL | HAL_ETH_RX_ERROR_RWT
                                         | HAL_ETH_RX_ERROR_GP | HAL_ETH_RX_ERROR_CRC), p_dma_RxDesc->DESC3);
    }
    /* Set Application context */
    STM32_WRITE_REG(rx_pkt_data.p_data, p_dma_RxDesc->p_app_data);
    /* Call channel Rx complete callback */
    heth->rx_channels[ch].p_rx_complete_cb(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc->p_pkt_addr,
                                           pkt_size, rx_pkt_data);
    /* Reset descriptor */
    ETH_ResetDMADesc(p_dma_RxDesc);

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_cache_flush_cb(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                           heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_CacheFlushCallback(heth, ETH_GET_RX_CH_ID(ch), p_dma_RxDesc,
                               heth->rx_channels[ch].rx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

    /* Pass to next desc */
    ETH_INCR_DESC_INDEX(rx_desc_idx, heth->rx_channels[ch].rx_desc_list.total_desc_cnt);
    /* Decriment total used desc */
    rx_total_used_desc--;
  }
  /* Reset total used buffers and desc id */
  heth->rx_channels[ch].rx_desc_list.buff_in_use = 0UL;
  heth->rx_channels[ch].rx_desc_list.built_desc_id = 0UL;
  heth->rx_channels[ch].rx_desc_list.curr_desc_id = 0UL;
}

/**
  * @brief  Recycle TX descriptors and invoke TX complete callbacks.
  *
  * This function walks the list of built TX descriptors, invokes the
  * channel TX complete callback for each transmitted packet, then
  * resets the descriptor so it can be reused by the DMA engine.
  *
  * @param  heth Pointer to HAL ETH handle
  * @param  ch   TX channel index (zero-based)
  */
static void ETH_RecycleTxDesc(hal_eth_handle_t *heth, uint32_t ch)
{
  eth_dma_descriptor_t *p_dma_txDesc;
  uint32_t tx_desc_idx        = heth->tx_channels[ch].tx_desc_list.built_desc_id;
  uint32_t tx_total_used_desc = heth->tx_channels[ch].tx_desc_list.buff_in_use;

  while (tx_total_used_desc != 0UL)
  {
    /* Get current built dma descriptor */
    p_dma_txDesc = ETH_GET_DESC_INDEX(heth->tx_channels[ch].tx_desc_list, tx_desc_idx);

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    /* Cache invalidate descriptor */
    heth->p_cache_invalidate_cb(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                                heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_CacheInvalidateCallback(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                                    heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

    if (p_dma_txDesc->p_pkt_addr == NULL)
    {
      /*No Packet attached,  recycle descriptor and pass to next one .  */
      ETH_ResetDMADesc(p_dma_txDesc);
    }
    else
    {
      hal_eth_tx_cb_pkt_data_t tx_cb_pkt_data = {0};

      /* Determine if the packet has been transmitted.  */
      if (STM32_READ_BIT(p_dma_txDesc->DESC3, ETH_DMA_TX_DESC_RF_OWN) != 0UL)
      {
        /* Packet not transmitted, declare it as invalid */
        STM32_SET_BIT(tx_cb_pkt_data.status, HAL_ETH_TX_STATUS_INVALID);
      }
      else
      {
        /* Set Desc status */
        ETH_COPY_BITS(tx_cb_pkt_data.status, HAL_ETH_TX_STATUS_FD | HAL_ETH_TX_STATUS_LD, p_dma_txDesc->DESC3);
        /* Set Desc errors */
        ETH_COPY_BITS(tx_cb_pkt_data.errors, (HAL_ETH_TX_ERROR_IH | HAL_ETH_TX_ERROR_ED
                                              | HAL_ETH_TX_ERROR_EC | HAL_ETH_TX_ERROR_LC
                                              | HAL_ETH_TX_ERROR_NC | HAL_ETH_TX_ERROR_LOC
                                              | HAL_ETH_TX_ERROR_PC | HAL_ETH_TX_ERROR_JT), p_dma_txDesc->DESC3);
      }
      /* Set Application context */
      STM32_WRITE_REG(tx_cb_pkt_data.p_data, p_dma_txDesc->p_app_data);
      /* Call channel Tx complete callback */
      heth->tx_channels[ch].p_tx_complete_cb(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc->p_pkt_addr, tx_cb_pkt_data);

      /* Reset dma desc */
      ETH_ResetDMADesc(p_dma_txDesc);
    }

#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
    heth->p_cache_flush_cb(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                           heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#else  /* USE_HAL_ETH_REGISTER_CALLBACKS */
    HAL_ETH_CacheFlushCallback(heth, ETH_GET_TX_CH_ID(ch), p_dma_txDesc,
                               heth->tx_channels[ch].tx_desc_list.desc_len_byte);
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */

    /* Pass to next desc */
    ETH_INCR_DESC_INDEX(tx_desc_idx, heth->tx_channels[ch].tx_desc_list.total_desc_cnt);
    /* Decriment total used desc */
    tx_total_used_desc--;
  }
  /* Reset total used buffers and desc id */
  heth->tx_channels[ch].tx_desc_list.buff_in_use = 0UL;
  heth->tx_channels[ch].tx_desc_list.built_desc_id = 0UL;
  heth->tx_channels[ch].tx_desc_list.curr_desc_id = 0UL;
}

/**
  * @brief  Configure the MDIO clock range according to the AHB bus (HCLK) frequency.
  *
  * This static helper sets the MDIO clock divider in the @c MACMDIOAR register so that
  * the resulting MDIO clock stays within the valid range for the Ethernet PHY.
  *
  * The function:
  * - Reads the current @c MACMDIOAR register value.
  * - Clears the CSR Clock Range (CR) bits.
  * - Retrieves the current HCLK frequency via HAL_RCC_GetHCLKFreq().
  * - Selects the appropriate divider (e.g. @ref ETH_MDC_CLK_DIV_16, @ref ETH_MDC_CLK_DIV_26, ...)
  *   depending on the HCLK range.
  * - Writes back the updated value to @c MACMDIOAR.
  *
  * The mapping between HCLK frequency and divider is:
  * - @c hclk < 35 MHz             --> @ref ETH_MDC_CLK_DIV_16
  * -  35 MHz <= @c hclk < 60 MHz  --> @ref ETH_MDC_CLK_DIV_26
  * -  60 MHz <= @c hclk < 100 MHz --> @ref ETH_MDC_CLK_DIV_42
  * - 100 MHz <= @c hclk < 150 MHz --> @ref ETH_MDC_CLK_DIV_62
  * - 150 MHz <= @c hclk < 250 MHz --> @ref ETH_MDC_CLK_DIV_102
  * - 250 MHz <= @c hclk < 300 MHz --> @ref ETH_MDC_CLK_DIV_124
  * - 300 MHz <= @c hclk < 500 MHz --> @ref ETH_MDC_CLK_DIV_204
  * - @c hclk >= 500 MHz           --> @ref ETH_MDC_CLK_DIV_324
  *
  * @param[in] heth
  *         Pointer to an @ref hal_eth_handle_t structure that contains
  *         the configuration information for the Ethernet peripheral.
  *
  * @note The MDIO clock must not exceed the maximum frequency specified
  *       in the PHY datasheet (typically around 2.5 MHz). This function
  *       chooses the divider to satisfy that requirement based on HCLK.
  * @note The caller must ensure that @p heth is valid and that the
  *       Ethernet peripheral clock configuration is already set.
  */
static void ETH_SetMDIOClockRange(hal_eth_handle_t *heth)
{
  uint32_t hclk;
  uint32_t tmpreg;

  /* Get the ETHERNET MACMDIOAR value */
  tmpreg = STM32_READ_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR);

  /* Clear CSR Clock Range bits */
  tmpreg &= ~ETH_MACMDIOAR_CR;

  /* Get hclk frequency value */
  hclk = HAL_RCC_GetHCLKFreq();

  tmpreg |= ETH_GetMDIOClockRange(hclk);

  /* Configure the CSR Clock Range */
  STM32_WRITE_REG(ETH_GET_INSTANCE(heth)->MACMDIOAR, tmpreg);
}

/**
  * @brief Get the MDIO clock range (ETH_MACMDIOAR.CR) for a given HCLK frequency.
  *
  * Computes the CSR clock range field (CR) that configures the MDC frequency
  * derived from the system HCLK. The selected configuration targets the
  * highest possible MDC frequency within the allowed bounds
  * [ETH_MDC_CLK_MIN_HZ .. ETH_MDC_CLK_MAX_HZ].
  *
  * @param eth_hclk_freq HCLK frequency in Hz.
  * @retval MDIO CSR clock range encoding to be OR-ed into ETH_MACMDIOAR.
  */
static uint32_t ETH_GetMDIOClockRange(uint32_t eth_hclk_freq)
{
  /* Lookup table used by the MDIO clock-range selection */
  const eth_mdio_clk_div_t eth_mdio_clk_div_lut[] =
  {
    {ETH_MDIOAR_CSR_CR_SEL_2,   ETH_MDC_CLK_DIV_16},
    {ETH_MDIOAR_CSR_CR_SEL_3,   ETH_MDC_CLK_DIV_26},
    {ETH_MDIOAR_CSR_CR_SEL_0,   ETH_MDC_CLK_DIV_42},
    {ETH_MDIOAR_CSR_CR_SEL_1,   ETH_MDC_CLK_DIV_62},
    {ETH_MDIOAR_CSR_CR_SEL_4,   ETH_MDC_CLK_DIV_102},
    {ETH_MDIOAR_CSR_CR_SEL_5,   ETH_MDC_CLK_DIV_124},
    {ETH_MDIOAR_CSR_CR_SEL_6,   ETH_MDC_CLK_DIV_204},
    {ETH_MDIOAR_CSR_CR_SEL_7,   ETH_MDC_CLK_DIV_324}
  };

  uint32_t mdc_cr_sel = ETH_MDIOAR_CSR_CR_SEL_0;

  /* Get the size of the clock configuration table */
  const uint32_t clk_lut_size = (uint32_t)(sizeof(eth_mdio_clk_div_lut) / sizeof(eth_mdio_clk_div_lut[0]));

  for (uint32_t clk_index = 0; clk_index < clk_lut_size; clk_index++)
  {
    /* Derive the resulting MDC frequency for this divider. */
    uint32_t mdc_clk = eth_hclk_freq / eth_mdio_clk_div_lut[clk_index].clk_range_div;

    /* Check if the mdc clock is within the allowed range */
    if ((mdc_clk >= ETH_MDC_CLK_MIN_HZ) && (mdc_clk <= ETH_MDC_CLK_MAX_HZ))
    {
      mdc_cr_sel = eth_mdio_clk_div_lut[clk_index].clk_range_sel;
      /* Found a valid MDC clock range */
      break;
    }
  }

  return mdc_cr_sel;
}

/**
  * @brief  Retrieve the zero-based TX channel index corresponding to a channel bitmask.
  *
  * @param  p_TxCh      Pointer that will receive the channel index (output).
  * @param  channel Channel mask containing the selected TX channel bit(s) (input).
  *
  * @note   channel parameter must be a single TX channel bitmask of @ref ETH_Channel_Identifiers.
  */
__STATIC_INLINE void ETH_GetTXChIndex(uint32_t *p_TxCh, uint32_t channel)
{
  *p_TxCh = HAL_ETH_TX_Q0;
  for (uint32_t ch_index = 0; ch_index < USE_HAL_ETH_MAX_TX_CH_NB; ch_index++)
  {
    if ((channel & ETH_GET_TX_CH_ID(ch_index)) != 0UL)
    {
      *p_TxCh = ch_index;
      break;
    }
  }
}
/**
  * @brief  Retrieve the zero-based RX channel index corresponding to a channel mask.
  *
  * @param  p_RxCh      Pointer that will receive the channel index (output).
  * @param  channel Channel mask containing the selected RX channel bit(s) (input).
  *
  * @note   channel parameter must be a single RX channel bitmask of @ref ETH_Channel_Identifiers.
  */
__STATIC_INLINE void ETH_GetRXChIndex(uint32_t *p_RxCh, uint32_t channel)
{
  *p_RxCh = HAL_ETH_RX_Q0;
  for (uint32_t ch_index = 0; ch_index < USE_HAL_ETH_MAX_RX_CH_NB; ch_index++)
  {
    if (((channel) & ETH_GET_RX_CH_ID(ch_index)) != 0UL)
    {
      *p_RxCh = ch_index;
      break;
    }
  }
}

/**
  * @brief  Acquire channel lock (spinlock) for exclusive access.
  *
  * Attempts to set the lock state to `ETH_CHANNEL_STATE_LOCKED`. When
  * `USE_HAL_ETH_ATOMIC_CHANNEL_LOCK` is enabled, atomic exclusive access
  * (LDREX/STREX) and memory barriers are used to protect the update.
  *
  * @param  channel_lock_state Pointer to the channel lock state variable.
  * @retval HAL_OK   Lock acquired.
  * @retval HAL_BUSY Lock already held by another context.
  */
__STATIC_INLINE hal_status_t ETH_LockChannel(volatile uint32_t *channel_lock_state)
{
#if defined(USE_HAL_ETH_ATOMIC_CHANNEL_LOCK) && (USE_HAL_ETH_ATOMIC_CHANNEL_LOCK == 1)
  __DMB();
  do
  {
    if (__LDREXW(channel_lock_state) == ETH_CHANNEL_STATE_LOCKED)
    {
      /* Clear the lock before exiting */
      STM32_CLREX_TO_DEPRECATE(); /* Workaround linked to CMSIS IAR issue EWARM-11901 correction fix */
      return HAL_BUSY;
    }
  } while (__STREXW(ETH_CHANNEL_STATE_LOCKED, channel_lock_state) != 0UL);
  __DMB();
#else /* USE_HAL_ETH_ATOMIC_CHANNEL_LOCK */
  STM32_UNUSED(channel_lock_state);
#endif /* USE_HAL_ETH_ATOMIC_CHANNEL_LOCK */

  return HAL_OK;
}

/**
  * @brief  Release channel lock (spinlock).
  *
  * Sets the lock state back to `ETH_CHANNEL_STATE_UNLOCKED` when atomic
  * locking is enabled. When `USE_HAL_ETH_ATOMIC_CHANNEL_LOCK` is disabled,
  * this function is a no-op.
  * @param  channel_lock_state Pointer to the channel lock state variable.
  */
__STATIC_INLINE void ETH_UnlockChannel(volatile uint32_t *channel_lock_state)
{
#if defined(USE_HAL_ETH_ATOMIC_CHANNEL_LOCK) && (USE_HAL_ETH_ATOMIC_CHANNEL_LOCK == 1)
  *channel_lock_state = ETH_CHANNEL_STATE_UNLOCKED;
#else /* USE_HAL_ETH_ATOMIC_CHANNEL_LOCK */
  STM32_UNUSED(channel_lock_state);
#endif /* USE_HAL_ETH_ATOMIC_CHANNEL_LOCK */

}

/**
  * @brief  Align descriptor size to an application-requested alignment.
  *
  * Computes the smallest descriptor size, in bytes, that is a multiple of
  * @p app_req_size and large enough to contain one `eth_dma_descriptor_t`.
  * The additional padding must not exceed the hardware skip-length capability
  * derived from `ETH_DMACCR_DSL`.
  *
  * @param  app_req_size Requested alignment in bytes. Must be non-zero and a multiple
  *                      of `ETH_BUS_DATA_WIDTH_BYTE`.
  * @param  desc_size    Output pointer that receives the aligned descriptor size in bytes.
  *
  * @retval HAL_OK       Alignment computed successfully and stored in @p desc_size.
  * @retval HAL_ERROR    Invalid @p app_req_size or alignment would exceed the DMA
  *                      skip-length limit.
  */
static hal_status_t ETH_AlignDescSize(uint32_t app_req_size, uint32_t *desc_size)
{
  uint32_t num_blocks;
  uint32_t skiplen_size;
  uint32_t total_desc_size;
  const uint32_t desc_struct_size = (uint32_t)sizeof(eth_dma_descriptor_t);

  /* Validate requested alignment: must be non-zero and a multiple of the bus data width */
  if ((app_req_size == 0UL) || (((app_req_size % ((uint32_t)ETH_BUS_DATA_WIDTH_BYTE)) != 0UL)
                                && (app_req_size != 1UL)))
  {
    return HAL_ERROR;
  }
  /* Compute number of alignment quanta needed to fully contain one descriptor structure */
  num_blocks = (desc_struct_size + app_req_size - 1UL) / app_req_size;
  /* Compute the aligned total descriptor size in bytes */
  total_desc_size = num_blocks * app_req_size;
  /* Ensure the extra padding does not exceed the hardware skip-length capability */
  skiplen_size = ETH_GET_SKIPLEN_SIZE(total_desc_size, desc_struct_size);
  if ((skiplen_size & ((uint32_t)~(ETH_DMACCR_DSL))) != 0UL)
  {
    return HAL_ERROR;
  }
  /* Return the aligned descriptor size */
  *desc_size = total_desc_size;

  return HAL_OK;
}
/**
  * @brief  Get the interrupt pending bit for the Ethernet Wakeup External line.
  *
  * This function checks the External Rising Pending Register 2 (RPR2) and
  * Falling Pending Register 2 (FPR2) to determine which edge(s) have
  * triggered a pending interrupt for the Ethernet Wakeup External line.
  *
  * @note   The function returns one of the following values:
  *         - LL_EXTI_TRIGGER_NONE: No pending trigger.
  *         - LL_EXTI_TRIGGER_RISING: Rising edge trigger is pending.
  *         - LL_EXTI_TRIGGER_FALLING: Falling edge trigger is pending.
  *         - LL_EXTI_TRIGGER_RISING_FALLING: Both rising and falling edge triggers are pending.
  *
  * @retval hal_eth_wakeup_trigger_t
  *         The pending trigger flag(s) for the Ethernet Wakeup External line.
  */
__STATIC_INLINE uint32_t ETH_WakeupGetPendingIT(void)
{
  uint32_t pending_edge = LL_EXTI_TRIGGER_NONE;

  if (LL_EXTI_IsActiveRisingFlag_32_63(ETH_WAKEUP_EXTI_LINE) != 0UL)
  {
    /* ETH EXTI Rising edge trigger is pending */
    pending_edge = LL_EXTI_TRIGGER_RISING;
  }

  if (LL_EXTI_IsActiveFallingFlag_32_63(ETH_WAKEUP_EXTI_LINE) != 0UL)
  {
    pending_edge |= LL_EXTI_TRIGGER_FALLING;
  }
  return pending_edge;
}
/**
  * @brief  Clear the pending interrupt flag(s) for the Ethernet Wakeup External line.
  *
  * This function clears the pending interrupt flag(s) for the Ethernet Wakeup External line
  * based on the specified edge(s). It writes to the External Rising Pending Register 2 (RPR2)
  * and/or Falling Pending Register 2 (FPR2) to clear the corresponding pending bits.
  *
  * @param  edge  Specifies which edge(s) to clear pending flags for.
  *               This parameter can be one or a combination of the following values:
  *               - LL_EXTI_TRIGGER_RISING:   Clear rising edge pending flag.
  *               - LL_EXTI_TRIGGER_FALLING:  Clear falling edge pending flag.
  *               - LL_EXTI_TRIGGER_RISING_FALLING: Clear both rising and falling edge pending flags.
  */
__STATIC_INLINE void ETH_WakeupClearPendingIT(uint32_t edge)
{
  if ((edge & LL_EXTI_TRIGGER_RISING) != 0UL)
  {
    /* Clear rising edge trigger pending bit */
    LL_EXTI_ClearRisingFlag_32_63(ETH_WAKEUP_EXTI_LINE);
  }

  if ((edge & LL_EXTI_TRIGGER_FALLING) != 0UL)
  {
    /* Clear falling edge trigger pending bit */
    LL_EXTI_ClearFallingFlag_32_63(ETH_WAKEUP_EXTI_LINE);
  }
}
#if defined (USE_HAL_ETH_REGISTER_CALLBACKS) && (USE_HAL_ETH_REGISTER_CALLBACKS == 1)
/**
  * @brief  Initialize the callbacks to their default values.
  * @param  heth Pointer to a hal_eth_handle_t structure which contains the ETH instance.
  */
static void ETH_InitCommonCallbacksToDefault(hal_eth_handle_t *heth)
{
  /* Init the ETH Callback settings */
  heth->p_data_cb                 = HAL_ETH_DataCallback;             /* Legacy weak Data callback   */
  heth->p_error_cb                = HAL_ETH_ErrorCallback;            /* Legacy weak ErrorCallback   */
  heth->p_event_cb                = HAL_ETH_EventCallback;            /* Legacy weak EventCallback   */
  heth->p_pmt_cb                  = HAL_ETH_PMTCallback;              /* Legacy weak PMTCallback      */
  heth->p_eee_cb                  = HAL_ETH_EEECallback;              /* Legacy weak EEECallback      */
  heth->p_wake_up_cb              = HAL_ETH_WakeUpCallback;           /* Legacy weak WakeUpCallback   */
  heth->p_cache_invalidate_cb     = HAL_ETH_CacheInvalidateCallback;  /* Legacy weak CacheInvalidateCallback   */
  heth->p_cache_flush_cb          = HAL_ETH_CacheFlushCallback;       /* Legacy weak CachecleanCallback   */
}

/**
  * @brief  Initialize the Tx channel callbacks to their default values.
  * @param  hchannel Pointer to a hal_eth_tx_channel_handle_t structure which contains the Tx channel instance.
  */
static void ETH_InitTxCallbacksToDefault(hal_eth_tx_channel_handle_t *hchannel)
{
  /* Init the ETH Callback settings */
  hchannel->p_ch_event_cb      = HAL_ETH_TxEventCallback;   /* Legacy weak ErrorCallback    */
}

/**
  * @brief  Initialize the Rx channel callbacks to their default values.
  * @param  hchannel Pointer to a hal_eth_rx_channel_handle_t structure which contains the Rx channel instance.
  */
static void ETH_InitRxCallbacksToDefault(hal_eth_rx_channel_handle_t *hchannel)
{
  /* Init the ETH Callback settings */
  hchannel->p_ch_event_cb      = HAL_ETH_RxEventCallback;   /* Legacy weak ErrorCallback    */
}
#endif /* USE_HAL_ETH_REGISTER_CALLBACKS */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_ETH_MODULE */
#endif /* ETH1 */

/**
  * @}
  */
