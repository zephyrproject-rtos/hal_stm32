/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart_if.c
  * @author  GPM WBL Application Team
  * @brief : Source file for interfacing the stm32_adv_trace to hardware
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32_adv_trace.h"
#include "usart_if.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RECEIVE_AFTER_TRANSMIT  0 /* Whether the UART should be in RX after a Transmit */

/* USER CODE END PD */

/* External variables --------------------------------------------------------*/
/**
  * @brief USART1 handle
  */
extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/

/**
 *  @brief  trace tracer definition.
 *
 *  list all the driver interface used by the trace application.
 */
const UTIL_ADV_TRACE_Driver_s UTIL_TraceDriver =
{
  UART_Init,
  UART_DeInit,
  UART_StartRx,
  UART_TransmitDMA
};

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Private variables ---------------------------------------------------------*/

#if (CFG_DEBUG_APP_ADV_TRACE != 0)

/**
  * @brief buffer to receive 1 character
  */
uint8_t charRx;

/**
  * @brief  TX complete callback
  * @return none
  */
static void (*TxCpltCallback)(void *);
static void (*RxCpltCallback)(uint8_t *pdata, uint16_t size, uint8_t error);

#endif /* (CFG_DEBUG_APP_ADV_TRACE != 0) */

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Private function prototypes -----------------------------------------------*/

#if (CFG_DEBUG_APP_ADV_TRACE != 0)

static void USART1_DMA_MspDeInit(void);

#endif /* (CFG_DEBUG_APP_ADV_TRACE != 0) */

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UTIL_ADV_TRACE_Status_t UART_Init(  void (*cb)(void *))
{

#if (CFG_DEBUG_APP_ADV_TRACE != 0)

  /* USER CODE BEGIN UART_Init 1 */

  /* USER CODE END UART_Init 1 */

  /* Init done in main : GPIO */
  HAL_UART_MspInit(&huart1);
  MX_USART1_UART_Init();

  /* USER CODE BEGIN UART_Init 2 */

  /* USER CODE END UART_Init 2 */

  TxCpltCallback = cb;

  /* USER CODE BEGIN UART_Init 3 */

  /* USER CODE END UART_Init 3 */

#endif /* (CFG_DEBUG_APP_ADV_TRACE != 0) */

  return UTIL_ADV_TRACE_OK;

  /* USER CODE BEGIN UART_Init 4 */

  /* USER CODE END UART_Init 4 */
}

UTIL_ADV_TRACE_Status_t UART_DeInit( void )
{
#if (CFG_DEBUG_APP_ADV_TRACE != 0)

  /* USER CODE BEGIN UART_DeInit 1 */

  /* USER CODE END UART_DeInit 1 */

  HAL_StatusTypeDef result;

  USART1_DMA_MspDeInit();

  /* USER CODE BEGIN UART_DeInit 2 */

  /* USER CODE END UART_DeInit 2 */

  result = HAL_UART_DeInit(&huart1);
  if (result != HAL_OK)
  {
    TxCpltCallback = NULL;
    return UTIL_ADV_TRACE_UNKNOWN_ERROR;
  }

  /* USER CODE BEGIN UART_DeInit 3 */

  /* USER CODE END UART_DeInit 3 */

  if(huart1.hdmatx)
  {
    result = HAL_DMA_DeInit(huart1.hdmatx);
    if (result != HAL_OK)
    {
      return UTIL_ADV_TRACE_UNKNOWN_ERROR;
    }
  }

  /* USER CODE BEGIN UART_DeInit 4 */

  /* USER CODE END UART_DeInit 4 */

  if(huart1.hdmarx)
  {
    result = HAL_DMA_DeInit(huart1.hdmarx);
    if (result != HAL_OK)
    {
      return UTIL_ADV_TRACE_UNKNOWN_ERROR;
    }
  }

  /* USER CODE BEGIN UART_DeInit 5 */

  /* USER CODE END UART_DeInit 5 */

#endif /* (CFG_DEBUG_APP_ADV_TRACE != 0) */

  return UTIL_ADV_TRACE_OK;

  /* USER CODE BEGIN UART_DeInit 6 */

  /* USER CODE END UART_DeInit 6 */
}

UTIL_ADV_TRACE_Status_t UART_StartRx(void (*cb)(uint8_t *pdata, uint16_t size, uint8_t error))
{
#if (CFG_DEBUG_APP_ADV_TRACE != 0)

  /* USER CODE BEGIN UART_StartRx 1 */

  /* USER CODE END UART_StartRx 1 */

  /* Configure USART1 in Receive mode */
  HAL_UART_Receive_IT(&huart1, &charRx, 1);

  if (cb != NULL)
  {
    RxCpltCallback = cb;
  }

  /* USER CODE BEGIN UART_StartRx 2 */

  /* USER CODE END UART_StartRx 2 */

#endif /* (CFG_DEBUG_APP_ADV_TRACE != 0) */

  return UTIL_ADV_TRACE_OK;

  /* USER CODE BEGIN UART_StartRx 3 */

  /* USER CODE END UART_StartRx 3 */
}

UTIL_ADV_TRACE_Status_t UART_TransmitDMA ( uint8_t *pdata, uint16_t size )
{
  /* USER CODE BEGIN UART_TransmitDMA 1 */

  /* USER CODE END UART_TransmitDMA 1 */

  UTIL_ADV_TRACE_Status_t status = UTIL_ADV_TRACE_OK;

#if (CFG_DEBUG_APP_ADV_TRACE != 0)

  /* USER CODE BEGIN UART_TransmitDMA 2 */

  /* USER CODE END UART_TransmitDMA 2 */

  HAL_StatusTypeDef result;

  if(huart1.hdmatx)
  {
    result = HAL_UART_Transmit_DMA(&huart1, pdata, size);
  }
  else
  {
    result = HAL_UART_Transmit_IT(&huart1, pdata, size);
  }

  if (result != HAL_OK)
  {
    status = UTIL_ADV_TRACE_HW_ERROR;
  }

#if RECEIVE_AFTER_TRANSMIT
    HAL_UART_Receive_IT(&huart1, &charRx, 1);
#endif

  /* USER CODE BEGIN UART_TransmitDMA 3 */

  /* USER CODE END UART_TransmitDMA 3 */

#endif /* (CFG_DEBUG_APP_ADV_TRACE != 0) */

  return status;

  /* USER CODE BEGIN UART_TransmitDMA 4 */

  /* USER CODE END UART_TransmitDMA 4 */
}

#if (CFG_DEBUG_APP_ADV_TRACE != 0)

static void USART1_DMA_MspDeInit(void)
{
  /* USER CODE BEGIN USART1_DMA_MspDeInit 1 */

  /* USER CODE END USART1_DMA_MspDeInit 1 */

  /* Disable USART1 clock */
  __HAL_RCC_USART1_CLK_DISABLE();

  /* Disable interrupts for USART1 */
  HAL_NVIC_DisableIRQ(USART1_IRQn);

  /* GPDMA1 controller clock disable */
  __HAL_RCC_DMA_CLK_DISABLE();

  /* DMA interrupt init */
  HAL_NVIC_DisableIRQ(DMA_IRQn);

  /* USER CODE BEGIN USART1_DMA_MspDeInit 2 */

  /* USER CODE END USART1_DMA_MspDeInit 2 */
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* USER CODE BEGIN UsartIf_TxCpltCallback 1 */

  /* USER CODE END UsartIf_TxCpltCallback 1 */

  /* ADV Trace callback */
  if(TxCpltCallback)
    TxCpltCallback(NULL);

  /* USER CODE BEGIN UsartIf_TxCpltCallback 2 */

  /* USER CODE END UsartIf_TxCpltCallback 2 */

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* USER CODE BEGIN UsartIf_RxCpltCallback 1 */

  /* USER CODE END UsartIf_RxCpltCallback 1 */

  RxCpltCallback(&charRx, 1, 0);
  HAL_UART_Receive_IT(&huart1, &charRx, 1);

  /* USER CODE BEGIN UsartIf_RxCpltCallback 2 */

  /* USER CODE END UsartIf_RxCpltCallback 2 */
}

#endif /* (CFG_DEBUG_APP_ADV_TRACE != 0) */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

