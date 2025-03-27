/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_ipcc.h
  * @author  MCD Application Team
  * @brief   Header file of IPCC LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_LL_IPCC_H
#define STM32MP2xx_LL_IPCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined(IPCC) || defined(IPCC1) || defined(IPCC2)

/** @defgroup IPCC_LL IPCC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup IPCC_LL_Exported_Constants IPCC Exported Constants
  * @{
  */

/** @defgroup IPCC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_IPCC_ReadReg function
  * @{
  */
#define LL_IPCC_C1TOC2SR_CH1F IPCC_C1TOC2SR_CH1F_Msk /*!< C1 transmit to C2 receive Channel1 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH2F IPCC_C1TOC2SR_CH2F_Msk /*!< C1 transmit to C2 receive Channel2 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH3F IPCC_C1TOC2SR_CH3F_Msk /*!< C1 transmit to C2 receive Channel3 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH4F IPCC_C1TOC2SR_CH4F_Msk /*!< C1 transmit to C2 receive Channel4 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH5F IPCC_C1TOC2SR_CH5F_Msk /*!< C1 transmit to C2 receive Channel5 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH6F IPCC_C1TOC2SR_CH6F_Msk /*!< C1 transmit to C2 receive Channel6 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH7F IPCC_C1TOC2SR_CH7F_Msk /*!< C1 transmit to C2 receive Channel7 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH8F IPCC_C1TOC2SR_CH8F_Msk /*!< C1 transmit to C2 receive Channel8 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH9F IPCC_C1TOC2SR_CH9F_Msk /*!< C1 transmit to C2 receive Channel9 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH10F IPCC_C1TOC2SR_CH10F_Msk /*!< C1 transmit to C2 receive Channel10 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH11F IPCC_C1TOC2SR_CH11F_Msk /*!< C1 transmit to C2 receive Channel11 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH12F IPCC_C1TOC2SR_CH12F_Msk /*!< C1 transmit to C2 receive Channel12 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH13F IPCC_C1TOC2SR_CH13F_Msk /*!< C1 transmit to C2 receive Channel13 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH14F IPCC_C1TOC2SR_CH14F_Msk /*!< C1 transmit to C2 receive Channel14 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH15F IPCC_C1TOC2SR_CH15F_Msk /*!< C1 transmit to C2 receive Channel15 status flag before masking */
#define LL_IPCC_C1TOC2SR_CH16F IPCC_C1TOC2SR_CH16F_Msk /*!< C1 transmit to C2 receive Channel16 status flag before masking */


#define LL_IPCC_C2TOC1SR_CH1F IPCC_C2TOC1SR_CH1F_Msk /*!< C2 transmit to C1 receive Channel1 status flag before masking */
#define LL_IPCC_C2TOC1SR_CH2F IPCC_C2TOC1SR_CH2F_Msk /*!< C2 transmit to C1 receive Channel2 status flag before masking */
#define LL_IPCC_C2TOC1SR_CH3F IPCC_C2TOC1SR_CH3F_Msk /*!< C2 transmit to C1 receive Channel3 status flag before masking */
#define LL_IPCC_C2TOC1SR_CH4F IPCC_C2TOC1SR_CH4F_Msk /*!< C2 transmit to C1 receive Channel4 status flag before masking */
#define LL_IPCC_C2TOC1SR_CH5F IPCC_C2TOC1SR_CH5F_Msk /*!< C2 transmit to C1 receive Channel5 status flag before masking */
#define LL_IPCC_C2TOC1SR_CH6F IPCC_C2TOC1SR_CH6F_Msk /*!< C2 transmit to C1 receive Channel6 status flag before masking */

/**
  * @}
  */

/** @defgroup IPCC_LL_EC_Channel Channel
  * @{
  */
#define LL_IPCC_CHANNEL_1    (0x00000001U) /*!< IPCC Channel 1  */
#define LL_IPCC_CHANNEL_2    (0x00000002U) /*!< IPCC Channel 2  */
#define LL_IPCC_CHANNEL_3    (0x00000004U) /*!< IPCC Channel 3  */
#define LL_IPCC_CHANNEL_4    (0x00000008U) /*!< IPCC Channel 4  */
#define LL_IPCC_CHANNEL_5    (0x00000010U) /*!< IPCC Channel 5  */
#define LL_IPCC_CHANNEL_6    (0x00000020U) /*!< IPCC Channel 6  */
#define LL_IPCC_CHANNEL_7    (0x00000040U) /*!< IPCC Channel 7  */
#define LL_IPCC_CHANNEL_8    (0x00000080U) /*!< IPCC Channel 8  */
#define LL_IPCC_CHANNEL_9    (0x00000100U) /*!< IPCC Channel 9  */
#define LL_IPCC_CHANNEL_10   (0x00000200U) /*!< IPCC Channel 10 */
#define LL_IPCC_CHANNEL_11   (0x00000400U) /*!< IPCC Channel 11 */
#define LL_IPCC_CHANNEL_12   (0x00000800U) /*!< IPCC Channel 12 */
#define LL_IPCC_CHANNEL_13   (0x00001000U) /*!< IPCC Channel 13 */
#define LL_IPCC_CHANNEL_14   (0x00002000U) /*!< IPCC Channel 14 */
#define LL_IPCC_CHANNEL_15   (0x00004000U) /*!< IPCC Channel 15 */
#define LL_IPCC_CHANNEL_16   (0x00008000U) /*!< IPCC Channel 16 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup IPCC_LL_Exported_Macros IPCC Exported Macros
  * @{
  */

/** @defgroup IPCC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in IPCC register
  * @param  __INSTANCE__ IPCC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_IPCC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in IPCC register
  * @param  __INSTANCE__ IPCC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_IPCC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup IPCC_LL_Exported_Functions IPCC Exported Functions
  * @{
  */

/** @defgroup IPCC_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable Transmit channel free interrupt for processor 1.
  * @rmtoll C1CR          TXFIE         LL_C1_IPCC_EnableIT_TXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_EnableIT_TXF(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C1CR, IPCC_C1CR_TXFIE);
}

/**
  * @brief  Disable Transmit channel free interrupt for processor 1.
  * @rmtoll C1CR          TXFIE         LL_C1_IPCC_DisableIT_TXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_DisableIT_TXF(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C1CR, IPCC_C1CR_TXFIE);
}

/**
  * @brief  Check if Transmit channel free interrupt for processor 1 is enabled.
  * @rmtoll C1CR          TXFIE         LL_C1_IPCC_IsEnabledIT_TXF
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledIT_TXF(IPCC_TypeDef const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C1CR, IPCC_C1CR_TXFIE) == (IPCC_C1CR_TXFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Transmit channel free secure interrupt for processor 1.
  * @rmtoll C1CR          SECTXFIE         LL_C1_IPCC_EnableIT_SECTXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_EnableIT_SECTXF(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C1CR, IPCC_C1CR_SECTXFIE);
}

/**
  * @brief  Disable Transmit channel free secure interrupt for processor 1.
  * @rmtoll C1CR          SECTXFIE         LL_C1_IPCC_DisableIT_SECTXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_DisableIT_SECTXF(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C1CR, IPCC_C1CR_SECTXFIE);
}

/**
  * @brief  Check if Transmit channel free secure interrupt for processor 1 is enabled.
  * @rmtoll C1CR          SECTXFIE         LL_C1_IPCC_IsEnabledIT_SECTXF
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledIT_SECTXF(IPCC_TypeDef const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C1CR, IPCC_C1CR_SECTXFIE) == (IPCC_C1CR_SECTXFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Receive channel occupied interrupt for processor 1.
  * @rmtoll C1CR          RXOIE         LL_C1_IPCC_EnableIT_RXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_EnableIT_RXO(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C1CR, IPCC_C1CR_RXOIE);
}

/**
  * @brief  Disable Receive channel occupied interrupt for processor 1.
  * @rmtoll C1CR          RXOIE         LL_C1_IPCC_DisableIT_RXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_DisableIT_RXO(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C1CR, IPCC_C1CR_RXOIE);
}

/**
  * @brief  Check if Receive channel occupied interrupt for processor 1 is enabled.
  * @rmtoll C1CR          RXOIE         LL_C1_IPCC_IsEnabledIT_RXO
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledIT_RXO(IPCC_TypeDef  const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C1CR, IPCC_C1CR_RXOIE) == (IPCC_C1CR_RXOIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Receive channel occupied secure interrupt for processor 1.
  * @rmtoll C1CR          SECRXOIE         LL_C1_IPCC_EnableIT_SECRXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_EnableIT_SECRXO(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C1CR, IPCC_C1CR_SECRXOIE);
}

/**
  * @brief  Disable Receive channel occupied secure interrupt for processor 1.
  * @rmtoll C1CR          SECRXOIE         LL_C1_IPCC_DisableIT_SECRXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_DisableIT_SECRXO(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C1CR, IPCC_C1CR_SECRXOIE);
}

/**
  * @brief  Check if Receive channel occupied secure interrupt for processor 1 is enabled.
  * @rmtoll C1CR          SECRXOIE         LL_C1_IPCC_IsEnabledIT_SECRXO
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledIT_SECRXO(IPCC_TypeDef  const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C1CR, IPCC_C1CR_SECRXOIE) == (IPCC_C1CR_SECRXOIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Transmit channel free interrupt for processor 2.
  * @rmtoll C2CR          TXFIE         LL_C2_IPCC_EnableIT_TXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_EnableIT_TXF(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C2CR, IPCC_C2CR_TXFIE);
}

/**
  * @brief  Disable Transmit channel free interrupt for processor 2.
  * @rmtoll C2CR          TXFIE         LL_C2_IPCC_DisableIT_TXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_DisableIT_TXF(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C2CR, IPCC_C2CR_TXFIE);
}

/**
  * @brief  Check if Transmit channel free interrupt for processor 2 is enabled.
  * @rmtoll C2CR          TXFIE         LL_C2_IPCC_IsEnabledIT_TXF
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledIT_TXF(IPCC_TypeDef  const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C2CR, IPCC_C2CR_TXFIE) == (IPCC_C2CR_TXFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Transmit channel free secure interrupt for processor 2.
  * @rmtoll C2CR          SECTXFIE         LL_C2_IPCC_EnableIT_SECTXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_EnableIT_SECTXF(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C2CR, IPCC_C2CR_SECTXFIE);
}

/**
  * @brief  Disable Transmit channel free secure interrupt for processor 2.
  * @rmtoll C2CR          SECTXFIE         LL_C2_IPCC_DisableIT_SECTXF
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_DisableIT_SECTXF(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C2CR, IPCC_C2CR_SECTXFIE);
}

/**
  * @brief  Check if Transmit channel free secure interrupt for processor 2 is enabled.
  * @rmtoll C2CR          SECTXFIE         LL_C2_IPCC_IsEnabledIT_SECTXF
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledIT_SECTXF(IPCC_TypeDef  const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C2CR, IPCC_C2CR_SECTXFIE) == (IPCC_C2CR_SECTXFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Receive channel occupied interrupt for processor 2.
  * @rmtoll C2CR          RXOIE         LL_C2_IPCC_EnableIT_RXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_EnableIT_RXO(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C2CR, IPCC_C2CR_RXOIE);
}

/**
  * @brief  Disable Receive channel occupied interrupt for processor 2.
  * @rmtoll C2CR          RXOIE         LL_C2_IPCC_DisableIT_RXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_DisableIT_RXO(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C2CR, IPCC_C2CR_RXOIE);
}

/**
  * @brief  Check if Receive channel occupied interrupt for processor 2 is enabled.
  * @rmtoll C2CR          RXOIE         LL_C2_IPCC_IsEnabledIT_RXO
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledIT_RXO(IPCC_TypeDef const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C2CR, IPCC_C2CR_RXOIE) == (IPCC_C2CR_RXOIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Receive channel occupied secure interrupt for processor 2.
  * @rmtoll C2CR          SECRXOIE         LL_C2_IPCC_EnableIT_SECRXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_EnableIT_SECRXO(IPCC_TypeDef *IPCCx)
{
  SET_BIT(IPCCx->C2CR, IPCC_C2CR_SECRXOIE);
}

/**
  * @brief  Disable Receive channel occupied secure interrupt for processor 2.
  * @rmtoll C2CR          SECRXOIE         LL_C2_IPCC_DisableIT_SECRXO
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_DisableIT_SECRXO(IPCC_TypeDef *IPCCx)
{
  CLEAR_BIT(IPCCx->C2CR, IPCC_C2CR_SECRXOIE);
}

/**
  * @brief  Check if Receive channel occupied secure interrupt for processor 2 is enabled.
  * @rmtoll C2CR          SECRXOIE         LL_C2_IPCC_IsEnabledIT_SECRXO
  * @param  IPCCx IPCC Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledIT_SECRXO(IPCC_TypeDef const *const IPCCx)
{
  return ((READ_BIT(IPCCx->C2CR, IPCC_C2CR_SECRXOIE) == (IPCC_C2CR_SECRXOIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup IPCC_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Unmask transmit channel free interrupt for processor 1.
  * @rmtoll C1MR        CH1FM           LL_C1_IPCC_EnableTransmitChannel\n
  *         C1MR        CH2FM           LL_C1_IPCC_EnableTransmitChannel\n
  *         C1MR        CH3FM           LL_C1_IPCC_EnableTransmitChannel\n
  *         C1MR        CH4FM           LL_C1_IPCC_EnableTransmitChannel\n
  *         C1MR        CH5FM           LL_C1_IPCC_EnableTransmitChannel\n
  *         C1MR        CH6FM           LL_C1_IPCC_EnableTransmitChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_EnableTransmitChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C1MR, Channel << IPCC_C1MR_CH1FM_Pos);
}

/**
  * @brief  Mask transmit channel free interrupt for processor 1.
  * @rmtoll C1MR        CH1FM           LL_C1_IPCC_DisableTransmitChannel\n
  *         ...\n
  *         C1MR        CH16FM          LL_C1_IPCC_DisableTransmitChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_DisableTransmitChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C1MR, Channel << IPCC_C1MR_CH1FM_Pos);
}

/**
  * @brief  Check if Transmit channel free interrupt for processor 1 is masked.
  * @rmtoll C1MR        CH1FM           LL_C1_IPCC_IsEnabledTransmitChannel\n
  *         ...\n
  *         C1MR        CH16FM          LL_C1_IPCC_IsEnabledTransmitChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledTransmitChannel(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C1MR, Channel << IPCC_C1MR_CH1FM_Pos) != (Channel << IPCC_C1MR_CH1FM_Pos)) ? 1UL : 0UL);
}

/**
  * @brief  Unmask receive channel occupied interrupt for processor 1.
  * @rmtoll C1MR        CH1OM           LL_C1_IPCC_EnableReceiveChannel\n
  *         ...\n
  *         C1MR        CH16OM          LL_C1_IPCC_EnableReceiveChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_EnableReceiveChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C1MR, Channel);
}

/**
  * @brief  Mask receive channel occupied interrupt for processor 1.
  * @rmtoll C1MR        CH1OM           LL_C1_IPCC_DisableReceiveChannel\n
  *         ...\n
  *         C1MR        CH16OM          LL_C1_IPCC_DisableReceiveChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_DisableReceiveChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C1MR, Channel);
}

/**
  * @brief  Check if Receive channel occupied interrupt for processor 1 is masked.
  * @rmtoll C1MR        CH1OM           LL_C1_IPCC_IsEnabledReceiveChannel\n
  *         ...\n
  *         C1MR        CH16OM          LL_C1_IPCC_IsEnabledReceiveChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledReceiveChannel(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C1MR, Channel) != (Channel)) ? 1UL : 0UL);
}

/**
  * @brief  Unmask transmit channel free interrupt for processor 2.
  * @rmtoll C2MR        CH1FM           LL_C2_IPCC_EnableTransmitChannel\n
  *         ...\n
  *         C2MR        CH16FM          LL_C2_IPCC_EnableTransmitChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_EnableTransmitChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C2MR, Channel << IPCC_C2MR_CH1FM_Pos);
}

/**
  * @brief  Mask transmit channel free interrupt for processor 2.
  * @rmtoll C2MR        CH1FM           LL_C2_IPCC_DisableTransmitChannel\n
  *         ...\n
  *         C2MR        CH16FM          LL_C2_IPCC_DisableTransmitChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_DisableTransmitChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C2MR, Channel << (IPCC_C2MR_CH1FM_Pos));
}

/**
  * @brief  Check if Transmit channel free interrupt for processor 2 is masked.
  * @rmtoll C2MR        CH1FM           LL_C2_IPCC_IsEnabledTransmitChannel\n
  *         ...\n
  *         C2MR        CH16FM          LL_C2_IPCC_IsEnabledTransmitChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         @arg @ref LL_IPCC_CHANNEL_2
  *         @arg @ref LL_IPCC_CHANNEL_3
  *         @arg @ref LL_IPCC_CHANNEL_4
  *         @arg @ref LL_IPCC_CHANNEL_5
  *         @arg @ref LL_IPCC_CHANNEL_6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledTransmitChannel(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C2MR, Channel << IPCC_C2MR_CH1FM_Pos) != (Channel << IPCC_C2MR_CH1FM_Pos)) ? 1UL : 0UL);
}

/**
  * @brief  Unmask receive channel occupied interrupt for processor 2.
  * @rmtoll C2MR        CH1OM           LL_C2_IPCC_EnableReceiveChannel\n
  *         ...\n
  *         C2MR        CH16OM          LL_C2_IPCC_EnableReceiveChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_EnableReceiveChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C2MR, Channel);
}

/**
  * @brief  Mask receive channel occupied interrupt for processor 1.
  * @rmtoll C2MR        CH1OM           LL_C2_IPCC_DisableReceiveChannel\n
  *         ...\n
  *         C2MR        CH16OM          LL_C2_IPCC_DisableReceiveChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_DisableReceiveChannel(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C2MR, Channel);
}

/**
  * @brief  Check if Receive channel occupied interrupt for processor 2 is masked.
  * @rmtoll C2MR        CH1OM           LL_C2_IPCC_IsEnabledReceiveChannel\n
  *         ...\n
  *         C2MR        CH16OM          LL_C2_IPCC_IsEnabledReceiveChannel
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledReceiveChannel(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C2MR, Channel) != (Channel)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup IPCC_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear IPCC receive channel status for processor 1.
  * @note   Associated with IPCC_C2TOC1SR.CHxF
  * @rmtoll C1SCR        CH1C           LL_C1_IPCC_ClearFlag_CHx\n
  *         ..\n
  *         C1SCR        CH16C          LL_C1_IPCC_ClearFlag_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_ClearFlag_CHx(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C1SCR, Channel);
}

/**
  * @brief  Set IPCC transmit channel status for processor 1.
  * @note   Associated with IPCC_C1TOC2SR.CHxF
  * @rmtoll C1SCR        CH1S           LL_C1_IPCC_SetFlag_CHx\n
  *         ...\n
  *         C1SCR        CH16S          LL_C1_IPCC_SetFlag_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_SetFlag_CHx(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C1SCR, Channel << IPCC_C1SCR_CH1S_Pos);
}

/**
  * @brief  Get channel status for processor 1.
  * @rmtoll C1TOC2SR        CH1F           LL_C1_IPCC_IsActiveFlag_CHx\n
  *         ...\n
  *         C1TOC2SR        CH16F          LL_C1_IPCC_IsActiveFlag_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsActiveFlag_CHx(IPCC_TypeDef  const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C1TOC2SR, Channel) == (Channel)) ? 1UL : 0UL);
}

/**
  * @brief  Clear IPCC receive channel status for processor 2.
  * @note   Associated with IPCC_C1TOC2SR.CHxF
  * @rmtoll C2SCR        CH1C           LL_C2_IPCC_ClearFlag_CHx\n
  *         ...\n
  *         C2SCR        CH16C          LL_C2_IPCC_ClearFlag_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_ClearFlag_CHx(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C2SCR, Channel);
}

/**
  * @brief  Set IPCC transmit channel status for processor 2.
  * @note   Associated with IPCC_C2TOC1SR.CHxF
  * @rmtoll C2SCR        CH1S           LL_C2_IPCC_SetFlag_CHx\n
  *         ...\n
  *         C2SCR        CH16S          LL_C2_IPCC_SetFlag_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_SetFlag_CHx(IPCC_TypeDef *IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C2SCR, Channel << IPCC_C2SCR_CH1S_Pos);
}

/**
  * @brief  Get channel status for processor 2.
  * @rmtoll C2TOC1SR        CH1F           LL_C2_IPCC_IsActiveFlag_CHx\n
  *         ...\n
  *         C2TOC1SR        CH16F          LL_C2_IPCC_IsActiveFlag_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsActiveFlag_CHx(IPCC_TypeDef  const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C2TOC1SR, Channel) == (Channel)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Privilege Configuration.
  * @rmtoll C1PRIVCFGR        CH1PRIV           LL_C1_IPCC_Enable_PRIVCFGR_CHx\n
  *         ...\n
  *         C1PRIVCFGR        CH16PRIV          LL_C1_IPCC_Enable_PRIVCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_Enable_PRIVCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C1PRIVCFGR, Channel);
}

/**
  * @brief  Disable Privilege Configuration.
  * @rmtoll C1PRIVCFGR        CH1PRIV           LL_C1_IPCC_Disable_PRIVCFGR_CHx\n
  *         ...\n
  *         C1PRIVCFGR        CH16PRIV          LL_C1_IPCC_Disable_PRIVCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_Disable_PRIVCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C1PRIVCFGR, Channel);
}

/**
  * @brief  Get channel Priv status for processor 1.
  * @rmtoll C1PRIVCFGR        CH1PRIV           LL_C1_IPCC_IsEnabledPriv_CHx\n
  *         ...\n
  *         C1PRIVCFGR        CH16PRIV          LL_C1_IPCC_IsEnabledPriv_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledPriv_CHx(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C1PRIVCFGR, Channel) == (Channel)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Privilege Configuration.
  * @rmtoll C2PRIVCFGR        CH1PRIV           LL_C2_IPCC_Enable_PRIVCFGR_CHx\n
  *         ...\n
  *         C2PRIVCFGR        CH16PRIV          LL_C2_IPCC_Enable_PRIVCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_Enable_PRIVCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C2PRIVCFGR, Channel);
}

/**
  * @brief  Disable Privilege Configuration.
  * @rmtoll C2PRIVCFGR        CH1PRIV           LL_C2_IPCC_Disable_PRIVCFGR_CHx\n
  *         ...\n
  *         C2PRIVCFGR        CH16PRIV          LL_C2_IPCC_Disable_PRIVCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_Disable_PRIVCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C2PRIVCFGR, Channel);
}

/**
  * @brief  Get channel Privilege status for processor 2.
  * @rmtoll C2PRIVCFGR        CH1PRIV           LL_C2_IPCC_IsEnabledPriv_CHx\n
  *         ...\n
  *         C2PRIVCFGR        CH16PRIV          LL_C2_IPCC_IsEnabledPriv_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledPriv_CHx(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C2PRIVCFGR, Channel) == (Channel)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Secure Configuration.
  * @rmtoll C1SECCFGR        CH1SEC           LL_C1_IPCC_Enable_SECCFGR_CHx\n
  *         ...\n
  *         C1SECCFGR        CH16SEC          LL_C1_IPCC_Enable_SECCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_Enable_SECCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C1SECCFGR, Channel);
}

/**
  * @brief  Disable Secure Configuration.
  * @rmtoll C1SECCFGR        CH1SEC           LL_C1_IPCC_Disable_SECCFGR_CHx\n
  *         ...\n
  *         C1SECCFGR        CH16SEC          LL_C1_IPCC_Disable_SECCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C1_IPCC_Disable_SECCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C1SECCFGR, Channel);
}

/**
  * @brief  Get channel Secure status for processor 1.
  * @rmtoll C1SECCFGR        CH1SEC           LL_C1_IPCC_IsEnabledSec_CHx\n
  *         ...\n
  *         C1SECCFGR        CH16SEC          LL_C1_IPCC_IsEnabledSec_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C1_IPCC_IsEnabledSec_CHx(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C1SECCFGR, Channel) == (Channel)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Secure configuration for processor 2.
  * @rmtoll C2SECCFGR        CH1SEC           LL_C2_IPCC_Enable_SECCFGR_CHx\n
  *         ...\n
  *         C2SECCFGR        CH16SEC          LL_C2_IPCC_Enable_SECCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_Enable_SECCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  SET_BIT(IPCCx->C2SECCFGR, Channel);
}

/**
  * @brief  Disable Secure configuration for processor 2.
  * @rmtoll C2SECCFGR        CH1SEC           LL_C2_IPCC_Disable_SECCFGR_CHx\n
  *         ...\n
  *         C2SECCFGR        CH16SEC          LL_C2_IPCC_Disable_SECCFGR_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE void LL_C2_IPCC_Disable_SECCFGR_CHx(IPCC_TypeDef *const IPCCx, uint32_t Channel)
{
  CLEAR_BIT(IPCCx->C2SECCFGR, Channel);
}

/**
  * @brief  Get channel Secure status for processor 2.
  * @rmtoll C2SECCFGR        CH1SEC           LL_C1_IPCC_IsEnabledPriv_CHx\n
  *         ...\n
  *         C2SECCFGR        CH16SEC          LL_C1_IPCC_IsEnabledPriv_CHx
  * @param  IPCCx IPCC Instance.
  * @param  Channel This parameter can be a combination of the following values:
  *         @arg @ref LL_IPCC_CHANNEL_1
  *         ...
  *         @arg @ref LL_IPCC_CHANNEL_16
  * @retval None
  */
__STATIC_INLINE uint32_t LL_C2_IPCC_IsEnabledSec_CHx(IPCC_TypeDef const *const IPCCx, uint32_t Channel)
{
  return ((READ_BIT(IPCCx->C2SECCFGR, Channel) == (Channel)) ? 1UL : 0UL);
}

/**
  * @brief  Disable Processor 1 CID filtering.
  * @rmtoll C1CIDCFGR         IPCC          LL_IPCC_Disable_C1_CID_Filtering
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_IPCC_Disable_C1_CID_Filtering(IPCC_TypeDef *const IPCCx)
{
  CLEAR_BIT(IPCCx->C1CIDCFGR, IPCC_C1CIDCFGR_CFEN);
}

/**
  * @brief  Configure CID filtering for Processor 1.
  * @rmtoll C1CIDCFGR         IPCC          LL_IPCC_Config_C1_CID_Filtering
  * @param  IPCCx IPCC Instance.
  * @param  CIDDomainId Value between Min_Data=0 and Max_Data=7
  * @retval None
  */
__STATIC_INLINE void LL_IPCC_Config_C1_CID_Filtering(IPCC_TypeDef *const IPCCx, uint32_t CIDDomainId)
{
  WRITE_REG(IPCCx->C1CIDCFGR, ((CIDDomainId << IPCC_C1CIDCFGR_CID_Pos) | IPCC_C1CIDCFGR_CFEN));
}

/**
  * @brief  Disable Processor 2 CID filtering.
  * @rmtoll C2CIDCFGR         IPCC          LL_IPCC_Disable_C2_CID_Filtering
  * @param  IPCCx IPCC Instance.
  * @retval None
  */
__STATIC_INLINE void LL_IPCC_Disable_C2_CID_Filtering(IPCC_TypeDef *const IPCCx)
{
  CLEAR_BIT(IPCCx->C2CIDCFGR, IPCC_C2CIDCFGR_CFEN);
}

/**
  * @brief  Configure CID filtering for Processor 2.
  * @rmtoll C2CIDCFGR         IPCC          LL_IPCC_Config_C2_CID_Filtering
  * @param  IPCCx IPCC Instance.
  * @param  CIDDomainId Value between Min_Data=0 and Max_Data=7
  * @retval None
  */
__STATIC_INLINE void LL_IPCC_Config_C2_CID_Filtering(IPCC_TypeDef *const IPCCx, uint32_t CIDDomainId)
{
  WRITE_REG(IPCCx->C2CIDCFGR, ((CIDDomainId << IPCC_C2CIDCFGR_CID_Pos) | IPCC_C2CIDCFGR_CFEN));
}

/**
  * @brief  Get the number of supported channels.
  * @rmtoll HWCFGR        CHANNELS         LL_IPCC_GetChannelNumber
  * @param  IPCCx IPCC Instance.
  * @retval Number of supported channels.
  */
__STATIC_INLINE uint32_t LL_IPCC_GetChannelNumber(IPCC_TypeDef *IPCCx)
{
  return READ_BIT(IPCCx->HWCFGR, IPCC_HWCFGR_CHANNELS) >> IPCC_HWCFGR_CHANNELS_Pos;
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#endif /* IPCC || IPCC1 || IPCC2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_LL_IPCC_H */
