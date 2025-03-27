/**
  **********************************************************************************************************************
  * @file    stm32mp2xx_hal_dma.h
  * @author  MCD Application Team
  * @brief   Header file of DMA HAL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32MP2xx_HAL_DMA_H
#define STM32MP2xx_HAL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */


/* Exported types ----------------------------------------------------------------------------------------------------*/

/** @defgroup DMA_Exported_Types DMA Exported Types
  * @brief    DMA Exported Types
  * @{
  */

/**
  * @brief DMA Transfer Configuration Structure definition.
  */
typedef struct
{
  uint32_t Request;               /*!< Specifies the DMA channel request.
                                       This parameter can be a value of @ref DMA_Request_Selection                    */

  uint32_t BlkHWRequest;          /*!< Specifies the Block hardware request mode for DMA channel.
                                       Block Hardware request feature can be used only with dedicated peripherals.
                                       This parameter can be a value of @ref DMA_Block_Request                        */

  uint32_t Direction;             /*!< Specifies the transfer direction for DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Direction                   */

  uint32_t SrcInc;                /*!< Specifies the source increment mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Source_Increment_Mode                */

  uint32_t DestInc;               /*!< Specifies the destination increment mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Destination_Increment_Mode           */

  uint32_t SrcDataWidth;          /*!< Specifies the source data width for the DMA channel.
                                       This parameter can be a value of @ref DMA_Source_Data_Width                    */

  uint32_t DestDataWidth;         /*!< Specifies the destination data width for the DMA channel.
                                       This parameter can be a value of @ref DMA_Destination_Data_Width               */

  uint32_t Priority;              /*!< Specifies the priority level for the DMA channel.
                                       This parameter can be a value of @ref DMA_Priority_Level                       */

  uint32_t SrcBurstLength;        /*!< Specifies the source burst length (number of beats within a burst) for the DMA
                                       channel.
                                       This parameter can be a value between 1 and 64                                 */

  uint32_t DestBurstLength;       /*!< Specifies the destination burst length (number of beats within a burst) for the
                                       DMA channel.
                                       This parameter can be a value between 1 and 64                                 */

  uint32_t TransferAllocatedPort; /*!< Specifies the transfer allocated ports.
                                       This parameter can be a combination of @ref DMA_Transfer_Allocated_Port        */

  uint32_t TransferEventMode;     /*!< Specifies the transfer event mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Event_Mode                  */

  uint32_t Mode;                  /*!< Specifies the transfer mode for the DMA channel.
                                       This parameter can be a value of @ref DMA_Transfer_Mode                        */

} DMA_InitTypeDef;

/**
  * @brief DMA Linked-List Configuration Structure Definition.
  */
typedef struct
{
  uint32_t Priority;          /*!< Specifies the priority level for the DMA channel.
                                   This parameter can be a value of @ref DMA_Priority_Level        */

  uint32_t LinkStepMode;      /*!< Specifies the link step mode for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_Link_Step_Mode      */

  uint32_t LinkAllocatedPort; /*!< Specifies the linked-list allocated port for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_Link_Allocated_Port */

  uint32_t TransferEventMode; /*!< Specifies the transfer event mode for the DMA channel.
                                   This parameter can be a value of @ref DMA_Transfer_Event_Mode   */

  uint32_t LinkedListMode;    /*!< Specifies linked-list transfer mode for the DMA channel.
                                   This parameter can be a value of @ref DMAEx_LinkedList_Mode     */

} DMA_InitLinkedListTypeDef;

/**
  * @brief  HAL DMA State Enumeration Definition.
  */
typedef enum
{
  HAL_DMA_STATE_RESET   = 0x00U, /*!< DMA not yet initialized or disabled */
  HAL_DMA_STATE_READY   = 0x01U, /*!< DMA initialized and ready for use   */
  HAL_DMA_STATE_BUSY    = 0x02U, /*!< DMA process is ongoing              */
  HAL_DMA_STATE_ERROR   = 0x03U, /*!< DMA error state                     */
  HAL_DMA_STATE_ABORT   = 0x04U, /*!< DMA Abort state                     */
  HAL_DMA_STATE_SUSPEND = 0x05U, /*!< DMA Suspend state                   */

} HAL_DMA_StateTypeDef;

/**
  * @brief  HAL DMA Level Complete Enumeration Definition.
  */
typedef enum
{
  HAL_DMA_FULL_TRANSFER = 0x00U, /*!< Full channel transfer */
  HAL_DMA_HALF_TRANSFER = 0x01U, /*!< Half channel transfer */

} HAL_DMA_LevelCompleteTypeDef;

/**
  * @brief  HAL DMA Callbacks IDs Enumeration Definition.
  */
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID     = 0x00U, /*!< Complete transfer callback ID      */
  HAL_DMA_XFER_HALFCPLT_CB_ID = 0x01U, /*!< Half complete transfer callback ID */
  HAL_DMA_XFER_ERROR_CB_ID    = 0x02U, /*!< Error transfer callback ID         */
  HAL_DMA_XFER_ABORT_CB_ID    = 0x03U, /*!< Abort transfer callback ID         */
  HAL_DMA_XFER_SUSPEND_CB_ID  = 0x04U, /*!< Suspend transfer callback ID       */
  HAL_DMA_XFER_ALL_CB_ID      = 0x05U  /*!< All callback ID                    */

} HAL_DMA_CallbackIDTypeDef;

/**
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef       *Instance;                             /*!< Register the DMA channel base address   */

  DMA_InitTypeDef           Init;                                  /*!< DMA channel init parameters             */

  DMA_InitLinkedListTypeDef InitLinkedList;                        /*!< DMA channel linked-list init parameters */

  HAL_LockTypeDef           Lock;                                  /*!< DMA locking object                      */

  uint32_t                  Mode;                                  /*!< DMA transfer mode                       */

  __IO HAL_DMA_StateTypeDef State;                                 /*!< DMA transfer state                      */

  __IO uint32_t             ErrorCode;                             /*!< DMA error code                          */

  void                      *Parent;                               /*!< Parent object state                     */

  void (* XferCpltCallback)(struct __DMA_HandleTypeDef *hdma);     /*!< DMA transfer complete callback          */

  void (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA half transfer complete callback     */

  void (* XferErrorCallback)(struct __DMA_HandleTypeDef *hdma);    /*!< DMA transfer error callback             */

  void (* XferAbortCallback)(struct __DMA_HandleTypeDef *hdma);    /*!< DMA transfer Abort callback             */

  void (* XferSuspendCallback)(struct __DMA_HandleTypeDef *hdma);  /*!< DMA transfer Suspend callback           */

  struct __DMA_QListTypeDef  *LinkedListQueue;                     /*!< DMA linked-list queue                   */

} DMA_HandleTypeDef;
/**
  * @}
  */


/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @brief    DMA Exported constants
  * @{
  */

/** @defgroup DMA_Error_Codes DMA Error Codes
  * @brief    DMA Error Codes
  * @{
  */
#define HAL_DMA_ERROR_NONE             (0x0000U) /*!< No error                      */
#define HAL_DMA_ERROR_DTE              (0x0001U) /*!< Data transfer error           */
#define HAL_DMA_ERROR_ULE              (0x0002U) /*!< Update linked-list item error */
#define HAL_DMA_ERROR_USE              (0x0004U) /*!< User setting error            */
#define HAL_DMA_ERROR_TO               (0x0008U) /*!< Trigger overrun error         */
#define HAL_DMA_ERROR_TIMEOUT          (0x0010U) /*!< Timeout error                 */
#define HAL_DMA_ERROR_NO_XFER          (0x0020U) /*!< No transfer ongoing error     */
#define HAL_DMA_ERROR_BUSY             (0x0040U) /*!< Busy error                    */
#define HAL_DMA_ERROR_INVALID_CALLBACK (0x0080U) /*!< Invalid callback error        */
#define HAL_DMA_ERROR_NOT_SUPPORTED    (0x0100U) /*!< Not supported mode            */
/**
  * @}
  */

/** @defgroup DMA_Interrupt_Enable_Definition DMA Interrupt Enable Definition
  * @brief    DMA Interrupt Enable Definition
  * @{
  */
#define DMA_IT_TC   DMA_CCR_TCIE   /*!< Transfer complete interrupt             */
#define DMA_IT_HT   DMA_CCR_HTIE   /*!< Half transfer complete interrupt        */
#define DMA_IT_DTE  DMA_CCR_DTEIE  /*!< Data transfer error interrupt           */
#define DMA_IT_ULE  DMA_CCR_ULEIE  /*!< Update linked-list item error interrupt */
#define DMA_IT_USE  DMA_CCR_USEIE  /*!< User eetting error interrupt            */
#define DMA_IT_SUSP DMA_CCR_SUSPIE /*!< Completed suspension interrupt          */
#define DMA_IT_TO   DMA_CCR_TOIE   /*!< Trigger overrun interrupt               */
/**
  * @}
  */

/** @defgroup DMA_Flag_Definition DMA Flag Definition
  * @brief    DMA Flag Definition
  * @{
  */
#define DMA_FLAG_IDLE DMA_CSR_IDLEF /*!< Idle flag                          */
#define DMA_FLAG_TC   DMA_CSR_TCF   /*!< Transfer complete flag             */
#define DMA_FLAG_HT   DMA_CSR_HTF   /*!< Half transfer complete flag        */
#define DMA_FLAG_DTE  DMA_CSR_DTEF  /*!< Data transfer error flag           */
#define DMA_FLAG_ULE  DMA_CSR_ULEF  /*!< Update linked-list item error flag */
#define DMA_FLAG_USE  DMA_CSR_USEF  /*!< User setting error flag            */
#define DMA_FLAG_SUSP DMA_CSR_SUSPF /*!< Completed suspension flag          */
#define DMA_FLAG_TO   DMA_CSR_TOF   /*!< Trigger overrun flag               */
/**
  * @}
  */

/** @defgroup DMA_Request_Selection DMA Request Selection
  * @brief    DMA Request Selection
  * @{
  */
/* HPDMA requests */
#if defined (LPDMA)
#define HPDMA_REQUEST_FMC_TXRX   (0U)   /*!< HPDMA HW request is FMC_TXRX      */
#define HPDMA_REQUEST_FMC_BCH    (1U)   /*!< HPDMA HW request is FMC_BCH       */
#define HPDMA_REQUEST_OCTOSPI1   (2U)   /*!< HPDMA HW request is OCTOSPI1      */
#define HPDMA_REQUEST_OCTOSPI2   (3U)   /*!< HPDMA HW request is OCTOSPI2      */
#define HPDMA_REQUEST_CRYP1_IN   (4U)   /*!< HPDMA HW request is CRYP1_IN      */
#define HPDMA_REQUEST_CRYP1_OUT  (5U)   /*!< HPDMA HW request is CRYP1_OUT     */
#define HPDMA_REQUEST_HASH       (6U)   /*!< HPDMA HW request is HASH          */
#define HPDMA_REQUEST_SAES_OUT   (7U)   /*!< HPDMA HW request is SAES_OUT      */
#define HPDMA_REQUEST_SAES_IN    (8U)   /*!< HPDMA HW request is SAES_IN       */
#define HPDMA_REQUEST_USART1_RX  (9U)   /*!< HPDMA HW request is USART1_RX     */
#define HPDMA_REQUEST_USART1_TX  (10U)  /*!< HPDMA HW request is USART1_TX     */
#define HPDMA_REQUEST_USART2_RX  (11U)  /*!< HPDMA HW request is USART2_RX     */
#define HPDMA_REQUEST_USART2_TX  (12U)  /*!< HPDMA HW request is USART2_TX     */
#define HPDMA_REQUEST_USART3_RX  (13U)  /*!< HPDMA HW request is USART3_RX     */
#define HPDMA_REQUEST_USART3_TX  (14U)  /*!< HPDMA HW request is USART3_TX     */
#define HPDMA_REQUEST_UART4_RX   (15U)  /*!< HPDMA HW request is UART4_RX      */
#define HPDMA_REQUEST_UART4_TX   (16U)  /*!< HPDMA HW request is UART4_TX      */
#define HPDMA_REQUEST_UART5_RX   (17U)  /*!< HPDMA HW request is UART5_RX      */
#define HPDMA_REQUEST_UART5_TX   (18U)  /*!< HPDMA HW request is UART5_TX      */
#define HPDMA_REQUEST_USART6_RX  (19U)  /*!< HPDMA HW request is USART6_RX     */
#define HPDMA_REQUEST_USART6_TX  (20U)  /*!< HPDMA HW request is USART6_TX     */
#define HPDMA_REQUEST_UART7_RX   (21U)  /*!< HPDMA HW request is UART7_RX      */
#define HPDMA_REQUEST_UART7_TX   (22U)  /*!< HPDMA HW request is UART7_TX      */
#define HPDMA_REQUEST_UART8_RX   (23U)  /*!< HPDMA HW request is UART8_RX      */
#define HPDMA_REQUEST_UART8_TX   (24U)  /*!< HPDMA HW request is UART8_TX      */
#define HPDMA_REQUEST_UART9_RX   (25U)  /*!< HPDMA HW request is UART9_RX      */
#define HPDMA_REQUEST_UART9_TX   (26U)  /*!< HPDMA HW request is UART9_TX      */
#define HPDMA_REQUEST_I2C1_RX    (27U)  /*!< HPDMA HW request is I2C1_RX       */
#define HPDMA_REQUEST_I2C1_TX    (28U)  /*!< HPDMA HW request is I2C1_TX       */
#define HPDMA_REQUEST_I2C1_EVC   (29U)  /*!< HPDMA HW request is I2C1_EVC      */
#define HPDMA_REQUEST_I2C2_RX    (30U)  /*!< HPDMA HW request is I2C2_RX       */
#define HPDMA_REQUEST_I2C2_TX    (31U)  /*!< HPDMA HW request is I2C2_TX       */
#define HPDMA_REQUEST_I2C2_EVC   (32U)  /*!< HPDMA HW request is I2C2_EVC      */
#define HPDMA_REQUEST_I2C3_RX    (33U)  /*!< HPDMA HW request is I2C3_RX       */
#define HPDMA_REQUEST_I2C3_TX    (34U)  /*!< HPDMA HW request is I2C3_TX       */
#define HPDMA_REQUEST_I2C3_EVC   (35U)  /*!< HPDMA HW request is I2C3_EVC      */
#define HPDMA_REQUEST_I2C4_RX    (36U)  /*!< HPDMA HW request is I2C4_RX       */
#define HPDMA_REQUEST_I2C4_TX    (37U)  /*!< HPDMA HW request is I2C4_TX       */
#define HPDMA_REQUEST_I2C4_EVC   (38U)  /*!< HPDMA HW request is I2C4_EVC      */
#define HPDMA_REQUEST_I2C5_RX    (39U)  /*!< HPDMA HW request is I2C5_RX       */
#define HPDMA_REQUEST_I2C5_TX    (40U)  /*!< HPDMA HW request is I2C5_TX       */
#define HPDMA_REQUEST_I2C5_EVC   (41U)  /*!< HPDMA HW request is I2C5_EVC      */
#define HPDMA_REQUEST_I2C6_RX    (42U)  /*!< HPDMA HW request is I2C6_RX       */
#define HPDMA_REQUEST_I2C6_TX    (43U)  /*!< HPDMA HW request is I2C6_TX       */
#define HPDMA_REQUEST_I2C6_EVC   (44U)  /*!< HPDMA HW request is I2C6_EVC      */
#define HPDMA_REQUEST_I2C7_RX    (45U)  /*!< HPDMA HW request is I2C7_RX       */
#define HPDMA_REQUEST_I2C7_TX    (46U)  /*!< HPDMA HW request is I2C7_TX       */
#define HPDMA_REQUEST_I2C7_EVC   (47U)  /*!< HPDMA HW request is I2C7_EVC      */
#define HPDMA_REQUEST_RESERVED48 (48U)  /*!< HPDMA HW request is RESERVED      */
#define HPDMA_REQUEST_SPI1_RX    (49U)  /*!< HPDMA HW request is SPI1_RX       */
#define HPDMA_REQUEST_SPI1_TX    (50U)  /*!< HPDMA HW request is SPI1_TX       */
#define HPDMA_REQUEST_SPI2_RX    (51U)  /*!< HPDMA HW request is SPI2_RX       */
#define HPDMA_REQUEST_SPI2_TX    (52U)  /*!< HPDMA HW request is SPI2_TX       */
#define HPDMA_REQUEST_SPI3_RX    (53U)  /*!< HPDMA HW request is SPI3_RX       */
#define HPDMA_REQUEST_SPI3_TX    (54U)  /*!< HPDMA HW request is SPI3_TX       */
#define HPDMA_REQUEST_SPI4_RX    (55U)  /*!< HPDMA HW request is SPI4_RX       */
#define HPDMA_REQUEST_SPI4_TX    (56U)  /*!< HPDMA HW request is SPI4_TX       */
#define HPDMA_REQUEST_SPI5_RX    (57U)  /*!< HPDMA HW request is SPI5_RX       */
#define HPDMA_REQUEST_SPI5_TX    (58U)  /*!< HPDMA HW request is SPI5_TX       */
#define HPDMA_REQUEST_SPI6_RX    (59U)  /*!< HPDMA HW request is SPI6_RX       */
#define HPDMA_REQUEST_SPI6_TX    (60U)  /*!< HPDMA HW request is SPI6_TX       */
#define HPDMA_REQUEST_SPI7_RX    (61U)  /*!< HPDMA HW request is SPI7_RX       */
#define HPDMA_REQUEST_SPI7_TX    (62U)  /*!< HPDMA HW request is SPI7_TX       */
#define HPDMA_REQUEST_MDF1_FLT0  (63U)  /*!< HPDMA HW request is MDF1_FLT0     */
#define HPDMA_REQUEST_MDF1_FLT1  (64U)  /*!< HPDMA HW request is MDF1_FLT1     */
#define HPDMA_REQUEST_MDF1_FLT2  (65U)  /*!< HPDMA HW request is MDF1_FLT2     */
#define HPDMA_REQUEST_MDF1_FLT3  (66U)  /*!< HPDMA HW request is MDF1_FLT3     */
#define HPDMA_REQUEST_MDF1_FLT4  (67U)  /*!< HPDMA HW request is MDF1_FLT4     */
#define HPDMA_REQUEST_MDF1_FLT5  (68U)  /*!< HPDMA HW request is MDF1_FLT5     */
#define HPDMA_REQUEST_MDF1_FLT6  (69U)  /*!< HPDMA HW request is MDF1_FLT6     */
#define HPDMA_REQUEST_MDF1_FLT7  (70U)  /*!< HPDMA HW request is MDF1_FLT7     */
#define HPDMA_REQUEST_SPDIFRX_DT (71U)  /*!< HPDMA HW request is SPDIFRX_DT    */
#define HPDMA_REQUEST_SPDIFRX_CS (72U)  /*!< HPDMA HW request is SPDIFRX_CS    */
#define HPDMA_REQUEST_SAI1_A     (73U)  /*!< HPDMA HW request is SAI1_A        */
#define HPDMA_REQUEST_SAI1_B     (74U)  /*!< HPDMA HW request is SAI1_B        */
#define HPDMA_REQUEST_SAI2_A     (75U)  /*!< HPDMA HW request is SAI2_A        */
#define HPDMA_REQUEST_SAI2_B     (76U)  /*!< HPDMA HW request is SAI2_B        */
#define HPDMA_REQUEST_SAI3_A     (77U)  /*!< HPDMA HW request is SAI3_A        */
#define HPDMA_REQUEST_SAI3_B     (78U)  /*!< HPDMA HW request is SAI3_B        */
#define HPDMA_REQUEST_SAI4_A     (79U)  /*!< HPDMA HW request is SAI4_A        */
#define HPDMA_REQUEST_SAI4_B     (80U)  /*!< HPDMA HW request is SAI4_B        */
#define HPDMA_REQUEST_ADC1       (81U)  /*!< HPDMA HW request is ADC1          */
#define HPDMA_REQUEST_ADC2       (82U)  /*!< HPDMA HW request is ADC2          */
#define HPDMA_REQUEST_ADC3       (83U)  /*!< HPDMA HW request is ADC3          */
#define HPDMA_REQUEST_TIM1_CH1   (84U)  /*!< HPDMA HW request is TIM1_CH1      */
#define HPDMA_REQUEST_TIM1_CH2   (85U)  /*!< HPDMA HW request is TIM1_CH2      */
#define HPDMA_REQUEST_TIM1_CH3   (86U)  /*!< HPDMA HW request is TIM1_CH3      */
#define HPDMA_REQUEST_TIM1_CH4   (87U)  /*!< HPDMA HW request is TIM1_CH4      */
#define HPDMA_REQUEST_TIM1_UP    (88U)  /*!< HPDMA HW request is TIM1_UP       */
#define HPDMA_REQUEST_TIM1_TRIG  (89U)  /*!< HPDMA HW request is TIM1_TRIG     */
#define HPDMA_REQUEST_TIM1_COM   (90U)  /*!< HPDMA HW request is TIM1_COM      */
#define HPDMA_REQUEST_TIM2_CH1   (91U)  /*!< HPDMA HW request is TIM2_CH1      */
#define HPDMA_REQUEST_TIM2_CH2   (92U)  /*!< HPDMA HW request is TIM2_CH2      */
#define HPDMA_REQUEST_TIM2_CH3   (93U)  /*!< HPDMA HW request is TIM2_CH3      */
#define HPDMA_REQUEST_TIM2_CH4   (94U)  /*!< HPDMA HW request is TIM2_CH4      */
#define HPDMA_REQUEST_TIM2_UP    (95U)  /*!< HPDMA HW request is TIM2_UP       */
#define HPDMA_REQUEST_TIM3_CH1   (96U)  /*!< HPDMA HW request is TIM3_CH1      */
#define HPDMA_REQUEST_TIM3_CH2   (97U)  /*!< HPDMA HW request is TIM3_CH2      */
#define HPDMA_REQUEST_TIM3_CH3   (98U)  /*!< HPDMA HW request is TIM3_CH3      */
#define HPDMA_REQUEST_TIM3_CH4   (99U)  /*!< HPDMA HW request is TIM3_CH4      */
#define HPDMA_REQUEST_TIM3_UP    (100U) /*!< HPDMA HW request is TIM3_UP       */
#define HPDMA_REQUEST_TIM3_TRIG  (101U) /*!< HPDMA HW request is TIM3_TRIG     */
#define HPDMA_REQUEST_TIM4_CH1   (102U) /*!< HPDMA HW request is TIM4_CH1      */
#define HPDMA_REQUEST_TIM4_CH2   (103U) /*!< HPDMA HW request is TIM4_CH2      */
#define HPDMA_REQUEST_TIM4_CH3   (104U) /*!< HPDMA HW request is TIM4_CH3      */
#define HPDMA_REQUEST_TIM4_UP    (105U) /*!< HPDMA HW request is TIM4_UP       */
#define HPDMA_REQUEST_TIM5_CH1   (106U) /*!< HPDMA HW request is TIM5_CH1      */
#define HPDMA_REQUEST_TIM5_CH2   (107U) /*!< HPDMA HW request is TIM5_CH2      */
#define HPDMA_REQUEST_TIM5_CH3   (108U) /*!< HPDMA HW request is TIM5_CH3      */
#define HPDMA_REQUEST_TIM5_CH4   (109U) /*!< HPDMA HW request is TIM5_CH4      */
#define HPDMA_REQUEST_TIM5_UP    (110U) /*!< HPDMA HW request is TIM5_UP       */
#define HPDMA_REQUEST_TIM5_TRIG  (111U) /*!< HPDMA HW request is TIM5_TRIG     */
#define HPDMA_REQUEST_TIM6_UP    (112U) /*!< HPDMA HW request is TIM6_UP       */
#define HPDMA_REQUEST_TIM7_UP    (113U) /*!< HPDMA HW request is TIM7_UP       */
#define HPDMA_REQUEST_TIM8_CH1   (114U) /*!< HPDMA HW request is TIM8_CH1      */
#define HPDMA_REQUEST_TIM8_CH2   (115U) /*!< HPDMA HW request is TIM8_CH2      */
#define HPDMA_REQUEST_TIM8_CH3   (116U) /*!< HPDMA HW request is TIM8_CH3      */
#define HPDMA_REQUEST_TIM8_CH4   (117U) /*!< HPDMA HW request is TIM8_CH4      */
#define HPDMA_REQUEST_TIM8_UP    (118U) /*!< HPDMA HW request is TIM8_UP       */
#define HPDMA_REQUEST_TIM8_TRIG  (119U) /*!< HPDMA HW request is TIM8_TRIG     */
#define HPDMA_REQUEST_TIM8_COM   (120U) /*!< HPDMA HW request is TIM8_COM      */
#define HPDMA_REQUEST_TIM15_CH1  (121U) /*!< HPDMA HW request is TIM15_CH1     */
#define HPDMA_REQUEST_TIM15_UP   (122U) /*!< HPDMA HW request is TIM15_UP      */
#define HPDMA_REQUEST_TIM15_TRIG (123U) /*!< HPDMA HW request is TIM15_TRIG    */
#define HPDMA_REQUEST_TIM15_COM  (124U) /*!< HPDMA HW request is TIM15_COM     */
#define HPDMA_REQUEST_TIM16_CH1  (125U) /*!< HPDMA HW request is TIM16_CH1     */
#define HPDMA_REQUEST_TIM16_UP   (126U) /*!< HPDMA HW request is TIM16_UP      */
#define HPDMA_REQUEST_TIM17_CH1  (127U) /*!< HPDMA HW request is TIM17_CH1     */
#define HPDMA_REQUEST_TIM17_UP   (128U) /*!< HPDMA HW request is TIM17_UP      */
#define HPDMA_REQUEST_TIM20_CH1  (129U) /*!< HPDMA HW request is TIM20_CH1     */
#define HPDMA_REQUEST_TIM20_CH2  (130U) /*!< HPDMA HW request is TIM20_CH2     */
#define HPDMA_REQUEST_TIM20_CH3  (131U) /*!< HPDMA HW request is TIM20_CH3     */
#define HPDMA_REQUEST_TIM20_CH4  (132U) /*!< HPDMA HW request is TIM20_CH4     */
#define HPDMA_REQUEST_TIM20_UP   (133U) /*!< HPDMA HW request is TIM20_UP      */
#define HPDMA_REQUEST_TIM20_TRIG (134U) /*!< HPDMA HW request is TIM20_TRIG    */
#define HPDMA_REQUEST_TIM20_COM  (135U) /*!< HPDMA HW request is TIM20_COM     */
#define HPDMA_REQUEST_PCIE       (136U) /*!< HPDMA HW request is PCIE          */
#define HPDMA_REQUEST_DCMI       (137U) /*!< HPDMA HW request is DCMI          */
#define HPDMA_REQUEST_UCPD_TX    (138U) /*!< HPDMA HW request is UCPD_TX       */
#define HPDMA_REQUEST_UCPD_RX    (139U) /*!< HPDMA HW request is UCPD_RX       */
#define HPDMA_REQUEST_CRYP2_IN   (140U) /*!< HPDMA HW request is CRYP2_IN      */
#define HPDMA_REQUEST_CRYP2_OUT  (141U) /*!< HPDMA HW request is CRYP2_OUT     */
#define HPDMA_REQUEST_TIM4_CH4   (142U) /*!< HPDMA HW request is TIM4_CH4      */
#define HPDMA_REQUEST_LPTIM1_IC1 (143U) /*!< HPDMA HW request is LPTIM1_IC1    */
#define HPDMA_REQUEST_LPTIM1_IC2 (144U) /*!< HPDMA HW request is LPTIM1_IC2    */
#define HPDMA_REQUEST_LPTIM1_UE  (145U) /*!< HPDMA HW request is LPTIM1_UE     */
#define HPDMA_REQUEST_LPTIM2_IC1 (146U) /*!< HPDMA HW request is LPTIM2_IC1    */
#define HPDMA_REQUEST_LPTIM2_IC2 (147U) /*!< HPDMA HW request is LPTIM2_IC2    */
#define HPDMA_REQUEST_LPTIM2_UE  (148U) /*!< HPDMA HW request is LPTIM2_UE     */
#define HPDMA_REQUEST_TIM2_TRIG  (149U) /*!< HPDMA HW request is TIM2_TRIG     */
#define HPDMA_REQUEST_TIM4_TRIG  (150U) /*!< HPDMA HW request is TIM4_TRIG     */
#define HPDMA_REQUEST_TIM15_CH2  (151U) /*!< HPDMA HW request is TIM15_CH2     */
#define HPDMA_REQUEST_TIM16_COM  (152U) /*!< HPDMA HW request is TIM16_COM     */
#define HPDMA_REQUEST_TIM17_COM  (153U) /*!< HPDMA HW request is TIM17_COM     */
#define HPDMA_REQUEST_I3C1_RX    (154U) /*!< HPDMA HW request is I3C1_RX       */
#define HPDMA_REQUEST_I3C1_TX    (155U) /*!< HPDMA HW request is I3C1_TX       */
#define HPDMA_REQUEST_I3C1_CMD   (156U) /*!< HPDMA HW request is I3C1_CMD      */
#define HPDMA_REQUEST_I3C1_STAT  (157U) /*!< HPDMA HW request is I3C1_STAT     */
#define HPDMA_REQUEST_I3C2_RX    (158U) /*!< HPDMA HW request is I3C2_RX       */
#define HPDMA_REQUEST_I3C2_TX    (159U) /*!< HPDMA HW request is I3C2_TX       */
#define HPDMA_REQUEST_I3C2_CMD   (160U) /*!< HPDMA HW request is I3C2_CMD      */
#define HPDMA_REQUEST_I3C2_STAT  (161U) /*!< HPDMA HW request is I3C2_STAT     */
#define HPDMA_REQUEST_I3C3_RX    (162U) /*!< HPDMA HW request is I3C3_RX       */
#define HPDMA_REQUEST_I3C3_TX    (163U) /*!< HPDMA HW request is I3C3_TX       */
#define HPDMA_REQUEST_I3C3_CMD   (164U) /*!< HPDMA HW request is I3C3_CMD      */
#define HPDMA_REQUEST_I3C3_STAT  (165U) /*!< HPDMA HW request is I3C3_STAT     */
#if !defined(STM32MP25XX_SI_CUT1_X)
#define HPDMA_REQUEST_LPUART1_RX (166U) /*!< HPDMA HW request is LPUART1_RX    */
#define HPDMA_REQUEST_LPUART1_TX (167U) /*!< HPDMA HW request is LPUART1_TX    */
#define HPDMA_REQUEST_I2C8_RX    (168U) /*!< HPDMA HW request is I2C8_RX       */
#define HPDMA_REQUEST_I2C8_TX    (169U) /*!< HPDMA HW request is I2C8_TX       */
#define HPDMA_REQUEST_I2C8_EVC   (170U) /*!< HPDMA HW request is I2C8_EVC      */
#define HPDMA_REQUEST_SPI8_RX    (171U) /*!< HPDMA HW request is SPI8_RX       */
#define HPDMA_REQUEST_SPI8_TX    (172U) /*!< HPDMA HW request is SPI8_TX       */
#define HPDMA_REQUEST_ADF1_FLT0  (173U) /*!< HPDMA HW request is ADF1_FLT0     */
#define HPDMA_REQUEST_LPTIM3_IC1 (174U) /*!< HPDMA HW request is LPTIM3_IC1    */
#define HPDMA_REQUEST_LPTIM3_IC2 (175U) /*!< HPDMA HW request is LPTIM3_IC2    */
#define HPDMA_REQUEST_LPTIM3_UE  (176U) /*!< HPDMA HW request is LPTIM3_UE     */
#define HPDMA_REQUEST_LPTIM4_IC1 (177U) /*!< HPDMA HW request is LPTIM4_IC1    */
#define HPDMA_REQUEST_LPTIM4_IC2 (178U) /*!< HPDMA HW request is LPTIM4_IC2    */
#define HPDMA_REQUEST_LPTIM4_UE  (179U) /*!< HPDMA HW request is LPTIM4_UE     */
#define HPDMA_REQUEST_I3C4_RX    (180U) /*!< HPDMA HW request is I3C4_RX       */
#define HPDMA_REQUEST_I3C4_TX    (181U) /*!< HPDMA HW request is I3C4_TX       */
#define HPDMA_REQUEST_I3C4_CMD   (182U) /*!< HPDMA HW request is I3C4_CMD      */
#define HPDMA_REQUEST_I3C4_STAT  (183U) /*!< HPDMA HW request is I3C4_STAT     */
#endif /* ! STM32MP25XX_SI_CUT1_X */

/* LPDMA requests */
#define LPDMA_REQUEST_LPUART1_RX (0U)   /*!< LPDMA HW request is LPUART1_RX    */
#define LPDMA_REQUEST_LPUART1_TX (1U)   /*!< LPDMA HW request is LPUART1_TX    */
#define LPDMA_REQUEST_I2C8_RX    (2U)   /*!< LPDMA HW request is I2C8_RX       */
#define LPDMA_REQUEST_I2C8_TX    (3U)   /*!< LPDMA HW request is I2C8_TX       */
#define LPDMA_REQUEST_I2C8_EVC   (4U)   /*!< LPDMA HW request is I2C8_EVC      */
#define LPDMA_REQUEST_SPI8_RX    (5U)   /*!< LPDMA HW request is SPI8_RX       */
#define LPDMA_REQUEST_SPI8_TX    (6U)   /*!< LPDMA HW request is SPI8_TX       */
#define LPDMA_REQUEST_ADF1_FLT0  (7U)   /*!< LPDMA HW request is ADF1_FLT0     */
#define LPDMA_REQUEST_LPTIM3_IC1 (8U)   /*!< LPDMA HW request is LPTIM3_IC1    */
#define LPDMA_REQUEST_LPTIM3_IC2 (9U)   /*!< LPDMA HW request is LPTIM3_IC2    */
#define LPDMA_REQUEST_LPTIM3_UE  (10U)  /*!< LPDMA HW request is LPTIM3_UE     */
#define LPDMA_REQUEST_LPTIM4_IC1 (11U)  /*!< LPDMA HW request is LPTIM4_IC1    */
#define LPDMA_REQUEST_LPTIM4_IC2 (12U)  /*!< LPDMA HW request is LPTIM4_IC2    */
#define LPDMA_REQUEST_LPTIM4_UE  (13U)  /*!< LPDMA HW request is LPTIM4_UE     */
#define LPDMA_REQUEST_I3C4_RX    (15U)  /*!< LPDMA HW request is I3C4_RX       */
#define LPDMA_REQUEST_I3C4_TX    (16U)  /*!< LPDMA HW request is I3C4_TX       */
#define LPDMA_REQUEST_I3C4_CMD   (17U)  /*!< LPDMA HW request is I3C4_CMD      */
#define LPDMA_REQUEST_I3C4_STAT  (18U)  /*!< LPDMA HW request is I3C4_STAT     */

/* Software request */
#define DMA_REQUEST_SW            DMA_CTR2_SWREQ /*!< DMA SW request           */

#else

#define HPDMA_REQUEST_FMC_TXRX   (0U)   /*!< HPDMA HW request is FMC_TXRX      */
#define HPDMA_REQUEST_FMC_BCH    (1U)   /*!< HPDMA HW request is FMC_BCH       */
#define HPDMA_REQUEST_OCTOSPI1   (2U)   /*!< HPDMA HW request is OCTOSPI1      */
#define HPDMA_REQUEST_RESERVED3  (3U)   /*!< HPDMA HW request is RESERVED      */
#define HPDMA_REQUEST_CRYP1_IN   (4U)   /*!< HPDMA HW request is CRYP1_IN      */
#define HPDMA_REQUEST_CRYP1_OUT  (5U)   /*!< HPDMA HW request is CRYP1_OUT     */
#define HPDMA_REQUEST_HASH1      (6U)   /*!< HPDMA HW request is HASH1          */
#define HPDMA_REQUEST_SAES_OUT   (7U)   /*!< HPDMA HW request is SAES_OUT      */
#define HPDMA_REQUEST_SAES_IN    (8U)   /*!< HPDMA HW request is SAES_IN       */
#define HPDMA_REQUEST_USART1_RX  (9U)   /*!< HPDMA HW request is USART1_RX     */
#define HPDMA_REQUEST_USART1_TX  (10U)  /*!< HPDMA HW request is USART1_TX     */
#define HPDMA_REQUEST_USART2_RX  (11U)  /*!< HPDMA HW request is USART2_RX     */
#define HPDMA_REQUEST_USART2_TX  (12U)  /*!< HPDMA HW request is USART2_TX     */
#define HPDMA_REQUEST_USART3_RX  (13U)  /*!< HPDMA HW request is USART3_RX     */
#define HPDMA_REQUEST_USART3_TX  (14U)  /*!< HPDMA HW request is USART3_TX     */
#define HPDMA_REQUEST_UART4_RX   (15U)  /*!< HPDMA HW request is UART4_RX      */
#define HPDMA_REQUEST_UART4_TX   (16U)  /*!< HPDMA HW request is UART4_TX      */
#define HPDMA_REQUEST_UART5_RX   (17U)  /*!< HPDMA HW request is UART5_RX      */
#define HPDMA_REQUEST_UART5_TX   (18U)  /*!< HPDMA HW request is UART5_TX      */
#define HPDMA_REQUEST_USART6_RX  (19U)  /*!< HPDMA HW request is USART6_RX     */
#define HPDMA_REQUEST_USART6_TX  (20U)  /*!< HPDMA HW request is USART6_TX     */
#define HPDMA_REQUEST_UART7_RX   (21U)  /*!< HPDMA HW request is UART7_RX      */
#define HPDMA_REQUEST_UART7_TX   (22U)  /*!< HPDMA HW request is UART7_TX      */
#define HPDMA_REQUEST_I2C1_RX    (23U)  /*!< HPDMA HW request is I2C1_RX       */
#define HPDMA_REQUEST_I2C1_TX    (24U)  /*!< HPDMA HW request is I2C1_TX       */
#define HPDMA_REQUEST_I2C1_EVC   (25U)  /*!< HPDMA HW request is I2C1_EVC      */
#define HPDMA_REQUEST_I2C2_RX    (26U)  /*!< HPDMA HW request is I2C2_RX       */
#define HPDMA_REQUEST_I2C2_TX    (27U)  /*!< HPDMA HW request is I2C2_TX       */
#define HPDMA_REQUEST_I2C2_EVC   (28U)  /*!< HPDMA HW request is I2C2_EVC      */
#define HPDMA_REQUEST_I2C3_RX    (29U)  /*!< HPDMA HW request is I2C3_RX       */
#define HPDMA_REQUEST_I2C3_TX    (30U)  /*!< HPDMA HW request is I2C3_TX       */
#define HPDMA_REQUEST_I2C3_EVC   (31U)  /*!< HPDMA HW request is I2C3_EVC      */
#define HPDMA_REQUEST_SPI1_RX    (32U)  /*!< HPDMA HW request is SPI1_RX       */
#define HPDMA_REQUEST_SPI1_TX    (33U)  /*!< HPDMA HW request is SPI1_TX       */
#define HPDMA_REQUEST_SPI2_RX    (34U)  /*!< HPDMA HW request is SPI2_RX       */
#define HPDMA_REQUEST_SPI2_TX    (35U)  /*!< HPDMA HW request is SPI2_TX       */
#define HPDMA_REQUEST_SPI3_RX    (36U)  /*!< HPDMA HW request is SPI3_RX       */
#define HPDMA_REQUEST_SPI3_TX    (37U)  /*!< HPDMA HW request is SPI3_TX       */
#define HPDMA_REQUEST_SPI4_RX    (38U)  /*!< HPDMA HW request is SPI4_RX       */
#define HPDMA_REQUEST_SPI4_TX    (39U)  /*!< HPDMA HW request is SPI4_TX       */
#define HPDMA_REQUEST_SPI5_RX    (40U)  /*!< HPDMA HW request is SPI5_RX       */
#define HPDMA_REQUEST_SPI5_TX    (41U)  /*!< HPDMA HW request is SPI5_TX       */
#define HPDMA_REQUEST_SPI6_RX    (42U)  /*!< HPDMA HW request is SPI6_RX       */
#define HPDMA_REQUEST_SPI6_TX    (43U)  /*!< HPDMA HW request is SPI6_TX       */
#define HPDMA_REQUEST_MDF1_FLT0  (44U)  /*!< HPDMA HW request is MDF1_FLT0     */
#define HPDMA_REQUEST_MDF1_FLT1  (45U)  /*!< HPDMA HW request is MDF1_FLT1     */
#define HPDMA_REQUEST_MDF1_FLT2  (46U)  /*!< HPDMA HW request is MDF1_FLT2     */
#define HPDMA_REQUEST_MDF1_FLT3  (47U)  /*!< HPDMA HW request is MDF1_FLT3     */
#define HPDMA_REQUEST_SPDIFRX_DT (48U)  /*!< HPDMA HW request is SPDIFRX_DT    */
#define HPDMA_REQUEST_SPDIFRX_CS (49U)  /*!< HPDMA HW request is SPDIFRX_CS    */
#define HPDMA_REQUEST_SAI1_A     (50U)  /*!< HPDMA HW request is SAI1_A        */
#define HPDMA_REQUEST_SAI1_B     (51U)  /*!< HPDMA HW request is SAI1_B        */
#define HPDMA_REQUEST_SAI2_A     (52U)  /*!< HPDMA HW request is SAI2_A        */
#define HPDMA_REQUEST_SAI2_B     (53U)  /*!< HPDMA HW request is SAI2_B        */
#define HPDMA_REQUEST_SAI3_A     (54U)  /*!< HPDMA HW request is SAI3_A        */
#define HPDMA_REQUEST_SAI3_B     (55U)  /*!< HPDMA HW request is SAI3_B        */
#define HPDMA_REQUEST_SAI4_A     (56U)  /*!< HPDMA HW request is SAI4_A        */
#define HPDMA_REQUEST_SAI4_B     (57U)  /*!< HPDMA HW request is SAI4_B        */
#define HPDMA_REQUEST_ADC1       (58U)  /*!< HPDMA HW request is ADC1          */
#define HPDMA_REQUEST_ADC2       (59U)  /*!< HPDMA HW request is ADC2          */
#define HPDMA_REQUEST_TIM1_CH1   (60U)  /*!< HPDMA HW request is TIM1_CH1      */
#define HPDMA_REQUEST_TIM1_CH2   (61U)  /*!< HPDMA HW request is TIM1_CH2      */
#define HPDMA_REQUEST_TIM1_CH3   (62U)  /*!< HPDMA HW request is TIM1_CH3      */
#define HPDMA_REQUEST_TIM1_CH4   (63U)  /*!< HPDMA HW request is TIM1_CH4      */
#define HPDMA_REQUEST_TIM1_UP    (64U)  /*!< HPDMA HW request is TIM1_UP       */
#define HPDMA_REQUEST_TIM1_TRIG  (65U)  /*!< HPDMA HW request is TIM1_TRIG     */
#define HPDMA_REQUEST_TIM1_COM   (66U)  /*!< HPDMA HW request is TIM1_COM      */
#define HPDMA_REQUEST_TIM2_CH1   (67U)  /*!< HPDMA HW request is TIM2_CH1      */
#define HPDMA_REQUEST_TIM2_CH2   (68U)  /*!< HPDMA HW request is TIM2_CH2      */
#define HPDMA_REQUEST_TIM2_CH3   (69U)  /*!< HPDMA HW request is TIM2_CH3      */
#define HPDMA_REQUEST_TIM2_CH4   (70U)  /*!< HPDMA HW request is TIM2_CH4      */
#define HPDMA_REQUEST_TIM2_UP    (71U)  /*!< HPDMA HW request is TIM2_UP       */
#define HPDMA_REQUEST_TIM3_CH1   (72U)  /*!< HPDMA HW request is TIM3_CH1      */
#define HPDMA_REQUEST_TIM3_CH2   (73U)  /*!< HPDMA HW request is TIM3_CH2      */
#define HPDMA_REQUEST_TIM3_CH3   (74U)  /*!< HPDMA HW request is TIM3_CH3      */
#define HPDMA_REQUEST_TIM3_CH4   (75U)  /*!< HPDMA HW request is TIM3_CH4      */
#define HPDMA_REQUEST_TIM3_UP    (76U) /*!< HPDMA HW request is TIM3_UP       */
#define HPDMA_REQUEST_TIM3_TRIG  (77U) /*!< HPDMA HW request is TIM3_TRIG     */
#define HPDMA_REQUEST_TIM4_CH1   (78U) /*!< HPDMA HW request is TIM4_CH1      */
#define HPDMA_REQUEST_TIM4_CH2   (79U) /*!< HPDMA HW request is TIM4_CH2      */
#define HPDMA_REQUEST_TIM4_CH3   (80U) /*!< HPDMA HW request is TIM4_CH3      */
#define HPDMA_REQUEST_TIM4_UP    (81U) /*!< HPDMA HW request is TIM4_UP       */
#define HPDMA_REQUEST_TIM5_CH1   (82U) /*!< HPDMA HW request is TIM5_CH1      */
#define HPDMA_REQUEST_TIM5_CH2   (83U) /*!< HPDMA HW request is TIM5_CH2      */
#define HPDMA_REQUEST_TIM5_CH3   (84U) /*!< HPDMA HW request is TIM5_CH3      */
#define HPDMA_REQUEST_TIM5_CH4   (85U) /*!< HPDMA HW request is TIM5_CH4      */
#define HPDMA_REQUEST_TIM5_UP    (86U) /*!< HPDMA HW request is TIM5_UP       */
#define HPDMA_REQUEST_TIM5_TRIG  (87U) /*!< HPDMA HW request is TIM5_TRIG     */
#define HPDMA_REQUEST_TIM6_UP    (88U) /*!< HPDMA HW request is TIM6_UP       */
#define HPDMA_REQUEST_TIM7_UP    (89U) /*!< HPDMA HW request is TIM7_UP       */
#define HPDMA_REQUEST_TIM8_CH1   (90U) /*!< HPDMA HW request is TIM8_CH1      */
#define HPDMA_REQUEST_TIM8_CH2   (91U) /*!< HPDMA HW request is TIM8_CH2      */
#define HPDMA_REQUEST_TIM8_CH3   (92U) /*!< HPDMA HW request is TIM8_CH3      */
#define HPDMA_REQUEST_TIM8_CH4   (93U) /*!< HPDMA HW request is TIM8_CH4      */
#define HPDMA_REQUEST_TIM8_UP    (94U) /*!< HPDMA HW request is TIM8_UP       */
#define HPDMA_REQUEST_TIM8_TRIG  (95U) /*!< HPDMA HW request is TIM8_TRIG     */
#define HPDMA_REQUEST_TIM8_COM   (96U) /*!< HPDMA HW request is TIM8_COM      */
#define HPDMA_REQUEST_TIM15_CH1  (97U) /*!< HPDMA HW request is TIM15_CH1     */
#define HPDMA_REQUEST_TIM15_UP   (98U) /*!< HPDMA HW request is TIM15_UP      */
#define HPDMA_REQUEST_TIM15_TRIG (99U) /*!< HPDMA HW request is TIM15_TRIG    */
#define HPDMA_REQUEST_TIM15_COM  (100U) /*!< HPDMA HW request is TIM15_COM     */
#define HPDMA_REQUEST_TIM16_CH1  (101U) /*!< HPDMA HW request is TIM16_CH1     */
#define HPDMA_REQUEST_TIM16_UP   (102U) /*!< HPDMA HW request is TIM16_UP      */
#define HPDMA_REQUEST_TIM17_CH1  (103U) /*!< HPDMA HW request is TIM17_CH1     */
#define HPDMA_REQUEST_TIM17_UP   (104U) /*!< HPDMA HW request is TIM17_UP      */
#define HPDMA_REQUEST_DCMI       (105U) /*!< HPDMA HW request is DCMI          */
#define HPDMA_REQUEST_RESERVED106 (106U)  /*!< HPDMA HW request is RESERVED      */
#define HPDMA_REQUEST_RESERVED107 (107U)  /*!< HPDMA HW request is RESERVED      */
#define HPDMA_REQUEST_CRYP2_IN   (108U) /*!< HPDMA HW request is CRYP2_IN      */
#define HPDMA_REQUEST_CRYP2_OUT  (109U) /*!< HPDMA HW request is CRYP2_OUT     */
#define HPDMA_REQUEST_TIM4_CH4   (110U) /*!< HPDMA HW request is TIM4_CH4      */
#define HPDMA_REQUEST_LPTIM1_IC1 (111U) /*!< HPDMA HW request is LPTIM1_IC1    */
#define HPDMA_REQUEST_LPTIM1_IC2 (112U) /*!< HPDMA HW request is LPTIM1_IC2    */
#define HPDMA_REQUEST_LPTIM1_UE  (113U) /*!< HPDMA HW request is LPTIM1_UE     */
#define HPDMA_REQUEST_LPTIM2_IC1 (115U) /*!< HPDMA HW request is LPTIM2_IC1    */
#define HPDMA_REQUEST_LPTIM2_IC2 (115U) /*!< HPDMA HW request is LPTIM2_IC2    */
#define HPDMA_REQUEST_LPTIM2_UE  (116U) /*!< HPDMA HW request is LPTIM2_UE     */
#define HPDMA_REQUEST_TIM2_TRIG  (117U) /*!< HPDMA HW request is TIM2_TRIG     */
#define HPDMA_REQUEST_TIM4_TRIG  (118U) /*!< HPDMA HW request is TIM4_TRIG     */
#define HPDMA_REQUEST_TIM15_CH2  (119U) /*!< HPDMA HW request is TIM15_CH2     */
#define HPDMA_REQUEST_TIM16_COM  (120U) /*!< HPDMA HW request is TIM16_COM     */
#define HPDMA_REQUEST_TIM17_COM  (121U) /*!< HPDMA HW request is TIM17_COM     */
#define HPDMA_REQUEST_I3C1_RX    (122U) /*!< HPDMA HW request is I3C1_RX       */
#define HPDMA_REQUEST_I3C1_TX    (123U) /*!< HPDMA HW request is I3C1_TX       */
#define HPDMA_REQUEST_I3C1_CMD   (124U) /*!< HPDMA HW request is I3C1_CMD      */
#define HPDMA_REQUEST_I3C1_STAT  (125U) /*!< HPDMA HW request is I3C1_STAT     */
#define HPDMA_REQUEST_I3C2_RX    (126U) /*!< HPDMA HW request is I3C2_RX       */
#define HPDMA_REQUEST_I3C2_TX    (127U) /*!< HPDMA HW request is I3C2_TX       */
#define HPDMA_REQUEST_I3C2_CMD   (128U) /*!< HPDMA HW request is I3C2_CMD      */
#define HPDMA_REQUEST_I3C2_STAT  (129U) /*!< HPDMA HW request is I3C2_STAT     */
#define HPDMA_REQUEST_I3C3_RX    (130U) /*!< HPDMA HW request is I3C3_RX       */
#define HPDMA_REQUEST_I3C3_TX    (131U) /*!< HPDMA HW request is I3C3_TX       */
#define HPDMA_REQUEST_I3C3_CMD   (132U) /*!< HPDMA HW request is I3C3_CMD      */
#define HPDMA_REQUEST_I3C3_STAT  (133U) /*!< HPDMA HW request is I3C3_STAT     */
#define HPDMA_REQUEST_LPUART1_RX (134U) /*!< HPDMA HW request is LPUART1_RX    */
#define HPDMA_REQUEST_LPUART1_TX (135U) /*!< HPDMA HW request is LPUART1_TX    */
#define HPDMA_REQUEST_LPTIM3_IC1 (136U) /*!< HPDMA HW request is LPTIM3_IC1    */
#define HPDMA_REQUEST_LPTIM3_IC2 (137U) /*!< HPDMA HW request is LPTIM3_IC2    */
#define HPDMA_REQUEST_LPTIM3_UE  (138U) /*!< HPDMA HW request is LPTIM3_UE     */
#define HPDMA_REQUEST_LPTIM4_IC1 (139U) /*!< HPDMA HW request is LPTIM4_IC1    */
#define HPDMA_REQUEST_LPTIM4_IC2 (140U) /*!< HPDMA HW request is LPTIM4_IC2    */
#define HPDMA_REQUEST_LPTIM4_UE  (141U) /*!< HPDMA HW request is LPTIM4_UE     */
#define HPDMA_REQUEST_HASH2      (142U) /*!< HPDMA HW request is HASH1          */


/* Software request */
#define DMA_REQUEST_SW            DMA_CTR2_SWREQ /*!< DMA SW request           */

#endif /* LPDMA */
/**
  * @}
  */

/** @defgroup DMA_Block_Request DMA Block Request
  * @brief    DMA Block Request
  * @{
  */
#define DMA_BREQ_SINGLE_BURST          0x00000000U     /*!< Hardware request protocol at a single / burst level */
#define DMA_BREQ_BLOCK                 DMA_CTR2_BREQ   /*!< Hardware request protocol at a block level          */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Direction DMA Transfer Direction
  * @brief    DMA transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY 0x00000000U             /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH DMA_CTR2_DREQ           /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY DMA_CTR2_SWREQ          /*!< Memory to memory direction     */
/**
  * @}
  */

/** @defgroup DMA_Source_Increment_Mode DMA Source Increment Mode
  * @brief    DMA Source Increment Mode
  * @{
  */
#define DMA_SINC_FIXED       0x00000000U   /*!< Source fixed       single / burst */
#define DMA_SINC_INCREMENTED DMA_CTR1_SINC /*!< Source incremented single / burst */
/**
  * @}
  */

/** @defgroup DMA_Destination_Increment_Mode DMA Destination Increment Mode
  * @brief    DMA Destination Increment Mode
  * @{
  */
#define DMA_DINC_FIXED       0x00000000U   /*!< Destination fixed       single / burst */
#define DMA_DINC_INCREMENTED DMA_CTR1_DINC /*!< Destination incremented single / burst */
/**
  * @}
  */

/** @defgroup DMA_Source_Data_Width DMA Source Data Width
  * @brief    DMA Source Data Width
  * @{
  */
#define DMA_SRC_DATAWIDTH_BYTE       0x00000000U           /*!< Source data width : Byte       */
#define DMA_SRC_DATAWIDTH_HALFWORD   DMA_CTR1_SDW_LOG2_0   /*!< Source data width : HalfWord   */
#define DMA_SRC_DATAWIDTH_WORD       DMA_CTR1_SDW_LOG2_1   /*!< Source data width : Word       */
#define DMA_SRC_DATAWIDTH_DOUBLEWORD DMA_CTR1_SDW_LOG2     /*!< Source data width : DoubleWord */
/**
  * @}
  */

/** @defgroup DMA_Destination_Data_Width DMA destination Data Width
  * @brief    DMA destination Data Width
  * @{
  */
#define DMA_DEST_DATAWIDTH_BYTE       0x00000000U          /*!< Destination data width : Byte       */
#define DMA_DEST_DATAWIDTH_HALFWORD   DMA_CTR1_DDW_LOG2_0  /*!< Destination data width : HalfWord   */
#define DMA_DEST_DATAWIDTH_WORD       DMA_CTR1_DDW_LOG2_1  /*!< Destination data width : Word       */
#define DMA_DEST_DATAWIDTH_DOUBLEWORD DMA_CTR1_DDW_LOG2    /*!< Destination data width : DoubleWord */

/**
  * @}
  */

/** @defgroup DMA_Priority_Level DMA Priority Level
  * @brief    DMA Priority Level
  * @{
  */
#define DMA_LOW_PRIORITY_LOW_WEIGHT  0x00000000U    /*!< Priority level : Low Priority, Low weight  */
#define DMA_LOW_PRIORITY_MID_WEIGHT  DMA_CCR_PRIO_0 /*!< Priority level : Low Priority, Mid weight  */
#define DMA_LOW_PRIORITY_HIGH_WEIGHT DMA_CCR_PRIO_1 /*!< Priority level : Low Priority, High weight */
#define DMA_HIGH_PRIORITY            DMA_CCR_PRIO   /*!< Priority level : HIGH Priority             */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Allocated_Port DMA Transfer Allocated Port
  * @brief    DMA Transfer Allocated Port
  * @{
  */
#define DMA_SRC_ALLOCATED_PORT0  0x00000000U  /*!< Source allocated Port 0      */
#define DMA_SRC_ALLOCATED_PORT1  DMA_CTR1_SAP /*!< Source allocated Port 1      */
#define DMA_DEST_ALLOCATED_PORT0 0x00000000U  /*!< Destination allocated Port 0 */
#define DMA_DEST_ALLOCATED_PORT1 DMA_CTR1_DAP /*!< Destination allocated Port 1 */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Event_Mode DMA Transfer Event Mode
  * @brief    DMA Transfer Event Mode
  * @{
  */
#define DMA_TCEM_BLOCK_TRANSFER          0x00000000U     /*!< The TC event is generated at the end of each block and the
                                                              HT event is generated at the half of each block         */
#define DMA_TCEM_REPEATED_BLOCK_TRANSFER DMA_CTR2_TCEM_0 /*!< The TC event is generated at the end of the repeated block
                                                              and the HT event is generated at the half of the repeated
                                                              block                                                   */
#define DMA_TCEM_EACH_LL_ITEM_TRANSFER   DMA_CTR2_TCEM_1 /*!< The TC event is generated at the end of each linked-list
                                                              item and the HT event is generated at the half of each
                                                              linked-list item                                        */
#define DMA_TCEM_LAST_LL_ITEM_TRANSFER   DMA_CTR2_TCEM   /*!< The TC event is generated at the end of the last
                                                              linked-list item and the HT event is generated at the half
                                                              of the last linked-list item                            */
/**
  * @}
  */

/** @defgroup DMA_Transfer_Mode DMA Transfer Mode
  * @brief    DMA Transfer Mode
  * @{
  */
#define DMA_NORMAL                           (0x00U)     /*!< Normal DMA transfer                    */
#define DMA_PFCTRL                    DMA_CTR2_PFREQ     /*!< HW request peripheral flow control mode */
/**
  * @}
  */

/** @defgroup DMA_Channel_Attributes DMA Channel Attributes
  * @brief    DMA Channel Security and Privilege Attributes
  * @note     Secure and non-secure attributes are only available from the secure world when TZEN = 1
  * @{
  */

#define DMA_CHANNEL_CID_DISABLE              (0x80000000U)

#define DMA_CHANNEL_PRIV                     (DMA_CHANNEL_ATTR_PRIV_MASK | (1U<<DMA_CHANNEL_PRIV_VAL_POS))           /*!< channel is privileged             */
#define DMA_CHANNEL_NPRIV                    (DMA_CHANNEL_ATTR_PRIV_MASK)                                            /*!< channel is unprivileged           */

#define DMA_CHANNEL_SEC                      (DMA_CHANNEL_ATTR_SEC_MASK | (1U<<DMA_CHANNEL_SEC_VAL_POS))             /*!< channel is secure                 */
#define DMA_CHANNEL_NSEC                     (DMA_CHANNEL_ATTR_SEC_MASK)                                             /*!< channel is non-secure             */

#define DMA_CHANNEL_SRC_SEC                  (DMA_CHANNEL_ATTR_SEC_SRC_MASK | (1U<<DMA_CHANNEL_SRC_SEC_VAL_POS))     /*!< src is secure                 */
#define DMA_CHANNEL_SRC_NSEC                 (DMA_CHANNEL_ATTR_SEC_SRC_MASK)                                         /*!< src is non-secure             */

#define DMA_CHANNEL_DEST_SEC                 (DMA_CHANNEL_ATTR_SEC_DEST_MASK | (1U<<DMA_CHANNEL_DEST_SEC_VAL_POS))   /*!< dest is secure                */
#define DMA_CHANNEL_DEST_NSEC                (DMA_CHANNEL_ATTR_SEC_DEST_MASK)                                        /*!< dest is non-secure            */

#define DMA_CHANNEL_ATTRIBUTE_UNLOCKED (0x00U)                                                                       /*!< Channel attribute is unlocked     */
#define DMA_CHANNEL_ATTRIBUTE_LOCKED   (0x01U)                                                                       /*!< Channel attribute is locked       */

#define DMA_CHANNEL_CID_DYNAMIC_0            (DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT | DMA_CCIDCFGR_WLISTCID0)          /*!< Enable CID filtering (shared mode) and give pin control  to CID0 */
#define DMA_CHANNEL_CID_DYNAMIC_1            (DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT | DMA_CCIDCFGR_WLISTCID1)          /*!< Enable CID filtering (shared mode) and give pin control  to CID1 */
#define DMA_CHANNEL_CID_DYNAMIC_2            (DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT | DMA_CCIDCFGR_WLISTCID2)          /*!< Enable CID filtering (shared mode) and give pin control  to CID2 */

#define DMA_CHANNEL_CID_STATIC_0             (DMA_CHANNEL_ATTR_CID_STATIC_SELECT|(0<<DMA_CCIDCFGR_SCID_Pos))         /*!< Enable CID filtering (static mode) and give pin control  to CID0 */
#define DMA_CHANNEL_CID_STATIC_1             (DMA_CHANNEL_ATTR_CID_STATIC_SELECT|(1U<<DMA_CCIDCFGR_SCID_Pos))         /*!< Enable CID filtering (static mode) and give pin control  to CID1 */
#define DMA_CHANNEL_CID_STATIC_2             (DMA_CHANNEL_ATTR_CID_STATIC_SELECT|(2U<<DMA_CCIDCFGR_SCID_Pos))         /*!< Enable CID filtering (static mode) and give pin control  to CID2 */
#define DMA_CHANNEL_CID_STATIC_3             (DMA_CHANNEL_ATTR_CID_STATIC_SELECT|(3U<<DMA_CCIDCFGR_SCID_Pos))         /*!< Enable CID filtering (static mode) and give pin control  to CID3 */

/**
  * @}
  */


/**
  * @}
  */


/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Macros DMA Exported Macros
  * @brief    DMA Exported Macros
  * @{
  */

/** @brief  Reset DMA handle state.
  * @param  __HANDLE__ : DMA handle.
  * @retval None.
  */
#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) \
  ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

/**
  * @brief  Enable the specified DMA Channel.
  * @param  __HANDLE__ : DMA handle.
  * @retval None
  */
#define __HAL_DMA_ENABLE(__HANDLE__) \
  ((__HANDLE__)->Instance->CCR |=  DMA_CCR_EN)

/**
  * @brief  Disable the specified DMA Channel.
  * @param  __HANDLE__ : DMA handle.
  * @retval None
  */
#define __HAL_DMA_DISABLE(__HANDLE__) \
  ((__HANDLE__)->Instance->CCR |= (DMA_CCR_SUSP | DMA_CCR_RESET))

/**
  * @brief  Get the DMA channel pending flags.
  * @param  __HANDLE__ : DMA handle.
  * @param  __FLAG__   : Get the specified flag.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TC    : Transfer Complete flag.
  *            @arg DMA_FLAG_HT    : Half Transfer Complete flag.
  *            @arg DMA_FLAG_DTE   : Data Transfer Error flag.
  *            @arg DMA_FLAG_ULE   : Update linked-list Error flag.
  *            @arg DMA_FLAG_USE   : User Setting Error flag.
  *            @arg DMA_FLAG_TO    : Trigger Overrun flag.
  *            @arg DMA_FLAG_SUSP  : Completed Suspension flag.
  *            @arg DMA_FLAG_IDLEF : Idle flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__) \
  ((__HANDLE__)->Instance->CSR & (__FLAG__))

/**
  * @brief  Clear the DMA Channel pending flags.
  * @param  __HANDLE__ : DMA handle.
  * @param  __FLAG__   : Specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_FLAG_TC   : Transfer Complete flag.
  *            @arg DMA_FLAG_HT   : Half Transfer Complete flag.
  *            @arg DMA_FLAG_DTE  : Data Transfer Error flag.
  *            @arg DMA_FLAG_ULE  : Update Linked-List Error flag.
  *            @arg DMA_FLAG_USE  : User Setting Error flag.
  *            @arg DMA_FLAG_TO   : Trigger Overrun flag.
  *            @arg DMA_FLAG_SUSP : Completed Suspension flag.
  * @retval None
  */
#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
  ((__HANDLE__)->Instance->CFCR = (__FLAG__))

/**
  * @brief  Enable the specified DMA Channel interrupts.
  * @param  __HANDLE__    : DMA handle.
  * @param  __INTERRUPT__ : Specifies the DMA interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC   : Transfer Complete interrupt.
  *            @arg DMA_IT_HT   : Half Transfer Complete interrupt.
  *            @arg DMA_IT_DTE  : Data Transfer Error interrupt.
  *            @arg DMA_IT_ULE  : Update Linked-List Error interrupt.
  *            @arg DMA_IT_USE  : User Setting Error interrupt.
  *            @arg DMA_IT_TO   : Trigger Overrun interrupt.
  *            @arg DMA_IT_SUSP : Completed Suspension interrupt.
  * @retval None
  */
#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
  ((__HANDLE__)->Instance->CCR |= (__INTERRUPT__))

/**
  * @brief  Disable the specified DMA Channel interrupts.
  * @param  __HANDLE__   : DMA handle.
  * @param __INTERRUPT__ : specifies the DMA interrupt sources to be disabled.
  *          This parameter can be any combination of the following values:
  *            @arg DMA_IT_TC   : Transfer Complete interrupt.
  *            @arg DMA_IT_HT   : Half Transfer Complete interrupt.
  *            @arg DMA_IT_DTE  : Data Transfer Error interrupt.
  *            @arg DMA_IT_ULE  : Update Linked-List Error interrupt.
  *            @arg DMA_IT_USE  : User Setting Error interrupt.
  *            @arg DMA_IT_TO   : Trigger Overrun interrupt.
  *            @arg DMA_IT_SUSP : Completed Suspension interrupt.
  * @retval None
  */
#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__) \
  ((__HANDLE__)->Instance->CCR &= ~(__INTERRUPT__))

/**
  * @brief  Checks whether the specified DMA Channel interrupt is enabled or not.
  * @param  __HANDLE__    : DMA handle.
  * @param  __INTERRUPT__ : specifies the DMA interrupt source to check.
  *            @arg DMA_IT_TC   : Transfer Complete interrupt.
  *            @arg DMA_IT_HT   : Half Transfer Complete interrupt.
  *            @arg DMA_IT_DTE  : Data Transfer Error interrupt.
  *            @arg DMA_IT_ULE  : Update Linked-List Error interrupt.
  *            @arg DMA_IT_USE  : User Setting Error interrupt.
  *            @arg DMA_IT_TO   : Trigger Overrun interrupt.
  *            @arg DMA_IT_SUSP : Completed Suspension interrupt.
  * @retval The state of DMA_IT (SET or RESET).
  */
#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
  (((__HANDLE__)->Instance->CCR & (__INTERRUPT__)))

/**
  * @brief  Writes the block number of bytes to be transferred from the source on the DMA Channel.
  * @param  __HANDLE__  : DMA handle.
  * @param  __COUNTER__ : Number of data bytes to be transferred from the source (from 0 to 65535).
  */
#define __HAL_DMA_SET_COUNTER(__HANDLE__, __COUNTER__) \
  MODIFY_REG((__HANDLE__)->Instance->CBR1, DMA_CBR1_BNDT, (__COUNTER__))

/**
  * @brief  Returns the number of remaining data bytes in the current DMA Channel transfer.
  * @param  __HANDLE__ : DMA handle.
  * @retval The number of remaining data units in the current DMA Stream transfer.
  */
#define __HAL_DMA_GET_COUNTER(__HANDLE__) \
  (((__HANDLE__)->Instance->CBR1) & DMA_CBR1_BNDT)
/**
  * @}
  */


/* Include DMA HAL Extension module */
#include "stm32mp2xx_hal_dma_ex.h"


/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Exported_Functions DMA Exported Functions
  * @brief    DMA Exported Functions
  * @{
  */

/** @defgroup DMA_Exported_Functions_Group1 Initialization and De-Initialization Functions
  * @brief    Initialization and De-Initialization Functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *const hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group2 I/O Operation Functions
  * @brief    I/O Operation Functions
  * @{
  */
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *const hdma,
                                uint32_t SrcAddress,
                                uint32_t DstAddress,
                                uint32_t SrcDataSize);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *const hdma,
                                   uint32_t SrcAddress,
                                   uint32_t DstAddress,
                                   uint32_t SrcDataSize);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *const hdma,
                                          HAL_DMA_LevelCompleteTypeDef CompleteLevel,
                                          uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *const hdma,
                                           HAL_DMA_CallbackIDTypeDef CallbackID,
                                           void (*const  pCallback)(DMA_HandleTypeDef *const _hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *const hdma,
                                             HAL_DMA_CallbackIDTypeDef CallbackID);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group3 State and Error Functions
  * @brief    State and Error Functions
  * @{
  */
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef const *const hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef const *const hdma);
/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Group4 DMA Attributes Functions
  * @brief    DMA Attributes Functions
  * @{
  */

HAL_StatusTypeDef HAL_DMA_ConfigChannelAttributes(DMA_HandleTypeDef *const hdma,
                                                  uint32_t ChannelAttributes);
HAL_StatusTypeDef HAL_DMA_GetConfigChannelAttributes(DMA_HandleTypeDef const *const hdma,
                                                     uint32_t *const pChannelAttributes);

#if defined CORTEX_IN_SECURE_STATE
HAL_StatusTypeDef HAL_DMA_LockChannelAttributes(DMA_HandleTypeDef const *const hdma);
#endif /* CORTEX_IN_SECURE_STATE */
HAL_StatusTypeDef HAL_DMA_GetLockChannelAttributes(DMA_HandleTypeDef const *const hdma,
                                                   uint32_t *const pLockState);


HAL_StatusTypeDef HAL_DMA_TakeChannelSemaphore(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_ReleaseChannelSemaphore(DMA_HandleTypeDef *hdma);
/**
  * @}
  */

/**
  * @}
  */


/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Constants DMA Private Constants
  * @brief    DMA Private Constants
  * @{
  */
#define HAL_TIMEOUT_DMA_ABORT          (0x00000005U) /* DMA channel abort timeout 5 milli-second */
#define HAL_DMA_CHANNEL_START          (0x00000050U) /* DMA channel offset                       */
#define HAL_DMA_CHANNEL_SIZE           (0x00000080U) /* DMA channel size                         */
#define HAL_DMA_OFFSET_MASK            (0x00000FFFU) /* DMA channel offset mask                  */
#define DMA_CHANNEL_ATTR_PRIV_MASK     (0x01000000U) /* DMA channel privilege                    */
#define DMA_CHANNEL_ATTR_SEC_MASK      (0x02000000U) /* DMA channel secure                       */
#define DMA_CHANNEL_ATTR_SEC_SRC_MASK  (0x04000000U) /* DMA channel source secure                */
#define DMA_CHANNEL_ATTR_SEC_DEST_MASK (0x08000000U) /* DMA channel destination secure           */


#define DMA_CHANNEL_ATTR_CID_DYNAMIC_MASK   (DMA_CCIDCFGR_WLISTCID2 | DMA_CCIDCFGR_WLISTCID1 | DMA_CCIDCFGR_WLISTCID0)

#define DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT (0x10000000U)
#define DMA_CHANNEL_ATTR_CID_STATIC_SELECT  (0x20000000U)

#define DMA_CHANNEL_PRIV_VAL_POS       0
#define DMA_CHANNEL_SEC_VAL_POS        1
#define DMA_CHANNEL_SRC_SEC_VAL_POS    2
#define DMA_CHANNEL_DEST_SEC_VAL_POS   3

#define DMA_CHANNEL_BURST_MIN          (0x00000001U) /* DMA channel minimum burst size           */
#define DMA_CHANNEL_BURST_MAX          (0x00000040U) /* DMA channel maximum burst size           */


#if defined CORTEX_IN_SECURE_STATE

#define DMA_CHANNEL_INVALID_ATTR_VALUE_MASK  (0x4080FF80U)
#define DMA_CHANNEL_VALID_ATTR_VALUE_MASK    (0xBF7F007FU)

#else

#define DMA_CHANNEL_INVALID_ATTR_VALUE_MASK  (0x4E80FF8EU)
#define DMA_CHANNEL_VALID_ATTR_VALUE_MASK    (0xB17F0071U)

#endif /* CORTEX_IN_SECURE_STATE */

/**
  * @}
  */


/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Macros DMA Private Macros
  * @brief    DMA Private Macros
  * @{
  */
#define GET_DMA_INSTANCE(__HANDLE__) \
  ((DMA_TypeDef *)((uint32_t)((__HANDLE__)->Instance) & (~HAL_DMA_OFFSET_MASK)))

#define GET_DMA_CHANNEL(__HANDLE__) \
  ((((uint32_t)((__HANDLE__)->Instance) & HAL_DMA_OFFSET_MASK) - HAL_DMA_CHANNEL_START) / HAL_DMA_CHANNEL_SIZE)

#define IS_DMA_MODE(MODE) \
  (((MODE) == DMA_NORMAL) || \
   ((MODE) == DMA_PFCTRL))

#define IS_DMA_DIRECTION(DIRECTION)         \
  (((DIRECTION) == DMA_PERIPH_TO_MEMORY) || \
   ((DIRECTION) == DMA_MEMORY_TO_PERIPH) || \
   ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_LEVEL_COMPLETE(LEVEL)     \
  (((LEVEL) == HAL_DMA_FULL_TRANSFER) || \
   ((LEVEL) == HAL_DMA_HALF_TRANSFER))

#define IS_DMA_SOURCE_INC(INC)  \
  (((INC) == DMA_SINC_FIXED) || \
   ((INC) == DMA_SINC_INCREMENTED))

#define IS_DMA_DESTINATION_INC(INC) \
  (((INC) == DMA_DINC_FIXED)     || \
   ((INC) == DMA_DINC_INCREMENTED))

#define IS_DMA_SOURCE_DATA_WIDTH(WIDTH)       \
  (((WIDTH) == DMA_SRC_DATAWIDTH_BYTE)     || \
   ((WIDTH) == DMA_SRC_DATAWIDTH_HALFWORD) || \
   ((WIDTH) == DMA_SRC_DATAWIDTH_WORD)     || \
   ((WIDTH) == DMA_SRC_DATAWIDTH_DOUBLEWORD))

#define IS_DMA_DESTINATION_DATA_WIDTH(WIDTH)   \
  (((WIDTH) == DMA_DEST_DATAWIDTH_BYTE)     || \
   ((WIDTH) == DMA_DEST_DATAWIDTH_HALFWORD) || \
   ((WIDTH) == DMA_DEST_DATAWIDTH_WORD)     || \
   ((WIDTH) == DMA_DEST_DATAWIDTH_DOUBLEWORD))

#define IS_DMA_BURST_LENGTH(LENGTH)       \
  (((LENGTH) >= DMA_CHANNEL_BURST_MIN) && \
   ((LENGTH) <= DMA_CHANNEL_BURST_MAX))

#define IS_DMA_PRIORITY(PRIORITY)                  \
  (((PRIORITY) == DMA_LOW_PRIORITY_LOW_WEIGHT)  || \
   ((PRIORITY) == DMA_LOW_PRIORITY_MID_WEIGHT)  || \
   ((PRIORITY) == DMA_LOW_PRIORITY_HIGH_WEIGHT) || \
   ((PRIORITY) == DMA_HIGH_PRIORITY))

#define  IS_DMA_TRANSFER_ALLOCATED_PORT(ALLOCATED_PORT) \
  (((ALLOCATED_PORT) & (~(DMA_CTR1_SAP | DMA_CTR1_DAP))) == 0U)

#if  defined(I3C4)
#define IS_DMA_REQUEST(REQUEST)     \
  (((REQUEST) == DMA_REQUEST_SW) || \
   ((REQUEST) <= HPDMA_REQUEST_I3C4_STAT))
#else /* I3C4 */
#define IS_DMA_REQUEST(REQUEST)     \
  (((REQUEST) == DMA_REQUEST_SW) || \
   ((REQUEST) <= HPDMA_REQUEST_HASH2))
#endif /* I3C4 */

#define IS_DMA_BLOCK_HW_REQUEST(MODE)   \
  (((MODE) == DMA_BREQ_SINGLE_BURST) || \
   ((MODE) == DMA_BREQ_BLOCK))

#define IS_DMA_TCEM_EVENT_MODE(MODE)               \
  (((MODE) == DMA_TCEM_BLOCK_TRANSFER)          || \
   ((MODE) == DMA_TCEM_REPEATED_BLOCK_TRANSFER) || \
   ((MODE) == DMA_TCEM_EACH_LL_ITEM_TRANSFER)   || \
   ((MODE) == DMA_TCEM_LAST_LL_ITEM_TRANSFER))

#define IS_DMA_BLOCK_SIZE(SIZE) \
  (((SIZE) > 0U) && ((SIZE) <= DMA_CBR1_BNDT))

#if defined CORTEX_IN_SECURE_STATE
#define IS_DMA_ATTRIBUTES(ATTRIBUTE)  \
  (((((ATTRIBUTE) & DMA_CHANNEL_INVALID_ATTR_VALUE_MASK) == 0U)                                       && \
    (((ATTRIBUTE) & DMA_CHANNEL_VALID_ATTR_VALUE_MASK) != 0U))                                         ? \
   ((((ATTRIBUTE) & DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT) == DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT)   || \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_CID_STATIC_SELECT ) == DMA_CHANNEL_ATTR_CID_STATIC_SELECT)    || \
    (((ATTRIBUTE) & DMA_CHANNEL_CID_DISABLE            ) == DMA_CHANNEL_CID_DISABLE)               || \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_SEC_MASK          ) == DMA_CHANNEL_ATTR_SEC_MASK)             || \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_SEC_SRC_MASK      ) == DMA_CHANNEL_ATTR_SEC_SRC_MASK)         || \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_SEC_DEST_MASK     ) == DMA_CHANNEL_ATTR_SEC_DEST_MASK)        || \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_PRIV_MASK         ) == DMA_CHANNEL_ATTR_PRIV_MASK))            : \
   RESET)
#else
#define IS_DMA_ATTRIBUTES(ATTRIBUTE)  \
  (((((ATTRIBUTE) & DMA_CHANNEL_INVALID_ATTR_VALUE_MASK) == 0U)                                       && \
    (((ATTRIBUTE) & DMA_CHANNEL_VALID_ATTR_VALUE_MASK) != 0U))                                        ? \
   ((((ATTRIBUTE) & DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT) == DMA_CHANNEL_ATTR_CID_DYNAMIC_SELECT)   || \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_CID_STATIC_SELECT ) == DMA_CHANNEL_ATTR_CID_STATIC_SELECT)    || \
    (((ATTRIBUTE) & DMA_CHANNEL_CID_DISABLE            ) == DMA_CHANNEL_CID_DISABLE)               || \
    (((ATTRIBUTE) & DMA_CHANNEL_ATTR_PRIV_MASK         ) == DMA_CHANNEL_ATTR_PRIV_MASK))            : \
   RESET)
#endif /* CORTEX_IN_SECURE_STATE */

#if defined CORTEX_IN_SECURE_STATE
#define IS_DMA_GLOBAL_ACTIVE_FLAG_S(INSTANCE, GLOBAL_FLAG) \
  (((INSTANCE)->SMISR & (GLOBAL_FLAG)))
#endif /* CORTEX_IN_SECURE_STATE */
#define IS_DMA_GLOBAL_ACTIVE_FLAG_NS(INSTANCE, GLOBAL_FLAG) \
  (((INSTANCE)->MISR & (GLOBAL_FLAG)))

/**
  * @}
  */


/* Private functions -------------------------------------------------------------------------------------------------*/
/** @defgroup DMA_Private_Functions DMA Private Functions
  * @brief    DMA Private Functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_DMA_H */
