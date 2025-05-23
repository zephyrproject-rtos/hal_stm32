/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_eth_ex.c
  * @author  MCD Application Team
  * @brief   ETH HAL Extended module driver.
  *
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

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

#ifdef HAL_ETH_MODULE_ENABLED

#if defined(ETH1) || defined(ETH2)

/** @defgroup ETHEx ETHEx
  * @brief ETH HAL Extended module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ETHEx_Private_Constants ETHEx Private Constants
  * @{
  */
#define ETH_MACL4CR_MASK     (ETH_MACL3L4C0R_L4PEN0 | ETH_MACL3L4C0R_L4SPM0 | \
                              ETH_MACL3L4C0R_L4SPIM0 | ETH_MACL3L4C0R_L4DPM0 | \
                              ETH_MACL3L4C0R_L4DPIM0)

#define ETH_MACL3CR_MASK     (ETH_MACL3L4C0R_L3PEN0 | ETH_MACL3L4C0R_L3SAM0 | \
                              ETH_MACL3L4C0R_L3SAIM0 | ETH_MACL3L4C0R_L3DAM0 | \
                              ETH_MACL3L4C0R_L3DAIM0 | ETH_MACL3L4C0R_L3HSBM0 | \
                              ETH_MACL3L4C0R_L3HDBM0)


#define ETH_MACRXVLAN_MASK (ETH_MACVTCR_EIVLRXS | ETH_MACVTCR_EIVLS | \
                            ETH_MACVTCR_ERIVLT | ETH_MACVTCR_EDVLP | \
                            ETH_MACVTCR_VTHM | ETH_MACVTCR_EVLRXS | \
                            ETH_MACVTCR_EVLS | ETH_MACVTCR_DOVLTC | \
                            ETH_MACVTCR_ERSVLM | ETH_MACVTCR_ESVL | \
                            ETH_MACVTCR_VTIM | ETH_MACVTCR_ETV)

#define ETH_MACTXVLAN_MASK (ETH_MACVIR_VLTI | ETH_MACVIR_CSVL | \
                            ETH_MACVIR_VLP | ETH_MACVIR_VLC)

#define ETH_MAC_L4_SRSP_MASK          0x0000FFFFU
#define ETH_MAC_L4_DSTP_MASK          0xFFFF0000U
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
/** @defgroup ETHEx_Exported_Functions ETH Extended Exported Functions
  * @{
  */

/** @defgroup ETHEx_Exported_Functions_Group1 Extended features functions
  * @brief    Extended features functions
  *
@verbatim
 ===============================================================================
                      ##### Extended features functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
      (+) Configure ARP offload module
      (+) Configure L3 and L4 filters
      (+) Configure Extended VLAN features
      (+) Configure Energy Efficient Ethernet module

@endverbatim
  * @{
  */

/**
  * @brief  Enables ARP Offload.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */

void HAL_ETHEx_EnableARPOffload(ETH_HandleTypeDef *heth)
{
  SET_BIT(heth->Instance->MACCR, ETH_MACCR_ARPEN);
}

/**
  * @brief  Disables ARP Offload.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
void HAL_ETHEx_DisableARPOffload(ETH_HandleTypeDef *heth)
{
  CLEAR_BIT(heth->Instance->MACCR, ETH_MACCR_ARPEN);
}

/**
  * @brief  Set the ARP Match IP address
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  IpAddress: IP Address to be matched for incoming ARP requests
  * @retval None
  */
void HAL_ETHEx_SetARPAddressMatch(ETH_HandleTypeDef *heth, uint32_t IpAddress)
{
  WRITE_REG(heth->Instance->MACARPAR, IpAddress);
}

/**
  * @brief  Configures the L4 Filter, this function allow to:
  *         set the layer 4 protocol to be matched (TCP or UDP)
  *         enable/disable L4 source/destination port perfect/inverse match.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  Filter: L4 filter to configured, this parameter must be one of the following
  *           ETH_L4_FILTER_0
  *           ETH_L4_FILTER_1
  * @param  pL4FilterConfig: pointer to a ETH_L4FilterConfigTypeDef structure
  *         that contains L4 filter configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETHEx_SetL4FilterConfig(ETH_HandleTypeDef *heth, uint32_t Filter,
                                              const ETH_L4FilterConfigTypeDef *pL4FilterConfig)
{
  if (pL4FilterConfig == NULL)
  {
    return HAL_ERROR;
  }

  if (Filter == ETH_L4_FILTER_0)
  {
    /* Write configuration to MACL3L4C0R register */
    MODIFY_REG(heth->Instance->MACL3L4C0R, ETH_MACL4CR_MASK, (pL4FilterConfig->Protocol |
                                                              pL4FilterConfig->SrcPortFilterMatch |
                                                              pL4FilterConfig->DestPortFilterMatch));

    /* Write configuration to MACL4A0R register */
    WRITE_REG(heth->Instance->MACL4A0R, (pL4FilterConfig->SourcePort | (pL4FilterConfig->DestinationPort << 16)));

  }
  else /* Filter == ETH_L4_FILTER_1 */
  {
    /* Write configuration to MACL3L4C1R register */
    MODIFY_REG(heth->Instance->MACL3L4C1R, ETH_MACL4CR_MASK, (pL4FilterConfig->Protocol |
                                                              pL4FilterConfig->SrcPortFilterMatch |
                                                              pL4FilterConfig->DestPortFilterMatch));

    /* Write configuration to MACL4A1R register */
    WRITE_REG(heth->Instance->MACL4A1R, (pL4FilterConfig->SourcePort | (pL4FilterConfig->DestinationPort << 16)));
  }

  /* Enable L4 filter */
  SET_BIT(heth->Instance->MACPFR, ETH_MACPFR_IPFE);

  return HAL_OK;
}

/**
  * @brief  Configures the L4 Filter, this function allow to:
  *         set the layer 4 protocol to be matched (TCP or UDP)
  *         enable/disable L4 source/destination port perfect/inverse match.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  Filter: L4 filter to configured, this parameter must be one of the following
  *           ETH_L4_FILTER_0
  *           ETH_L4_FILTER_1
  * @param  pL4FilterConfig: pointer to a ETH_L4FilterConfigTypeDef structure
  *         that contains L4 filter configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETHEx_GetL4FilterConfig(const ETH_HandleTypeDef *heth, uint32_t Filter,
                                              ETH_L4FilterConfigTypeDef *pL4FilterConfig)
{
  if (pL4FilterConfig == NULL)
  {
    return HAL_ERROR;
  }

  if (Filter == ETH_L4_FILTER_0)
  {
    /* Get configuration from MACL3L4C0R register */
    pL4FilterConfig->Protocol = READ_BIT(heth->Instance->MACL3L4C0R, ETH_MACL3L4C0R_L4PEN0);
    pL4FilterConfig->DestPortFilterMatch = READ_BIT(heth->Instance->MACL3L4C0R,
                                                    (ETH_MACL3L4C0R_L4DPM0 | ETH_MACL3L4C0R_L4DPIM0));
    pL4FilterConfig->SrcPortFilterMatch = READ_BIT(heth->Instance->MACL3L4C0R,
                                                   (ETH_MACL3L4C0R_L4SPM0 | ETH_MACL3L4C0R_L4SPIM0));

    /* Get configuration from MACL4A0R register */
    pL4FilterConfig->DestinationPort = (READ_BIT(heth->Instance->MACL4A0R, ETH_MAC_L4_DSTP_MASK) >> 16);
    pL4FilterConfig->SourcePort = READ_BIT(heth->Instance->MACL4A0R, ETH_MAC_L4_SRSP_MASK);
  }
  else /* Filter == ETH_L4_FILTER_1 */
  {
    /* Get configuration from MACL3L4C1R register */
    pL4FilterConfig->Protocol = READ_BIT(heth->Instance->MACL3L4C1R, ETH_MACL3L4C0R_L4PEN0);
    pL4FilterConfig->DestPortFilterMatch = READ_BIT(heth->Instance->MACL3L4C1R,
                                                    (ETH_MACL3L4C0R_L4DPM0 | ETH_MACL3L4C0R_L4DPIM0));
    pL4FilterConfig->SrcPortFilterMatch = READ_BIT(heth->Instance->MACL3L4C1R,
                                                   (ETH_MACL3L4C0R_L4SPM0 | ETH_MACL3L4C0R_L4SPIM0));

    /* Get configuration from MACL4A1R register */
    pL4FilterConfig->DestinationPort = (READ_BIT(heth->Instance->MACL4A1R, ETH_MAC_L4_DSTP_MASK) >> 16);
    pL4FilterConfig->SourcePort = READ_BIT(heth->Instance->MACL4A1R, ETH_MAC_L4_SRSP_MASK);
  }

  return HAL_OK;
}

/**
  * @brief  Configures the L3 Filter, this function allow to:
  *         set the layer 3 protocol to be matched (IPv4 or IPv6)
  *         enable/disable L3 source/destination port perfect/inverse match.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  Filter: L3 filter to configured, this parameter must be one of the following
  *           ETH_L3_FILTER_0
  *           ETH_L3_FILTER_1
  * @param  pL3FilterConfig: pointer to a ETH_L3FilterConfigTypeDef structure
  *         that contains L3 filter configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETHEx_SetL3FilterConfig(ETH_HandleTypeDef *heth, uint32_t Filter,
                                              const ETH_L3FilterConfigTypeDef *pL3FilterConfig)
{
  if (pL3FilterConfig == NULL)
  {
    return HAL_ERROR;
  }

  if (Filter == ETH_L3_FILTER_0)
  {
    /* Write configuration to MACL3L4C0R register */
    MODIFY_REG(heth->Instance->MACL3L4C0R, ETH_MACL3CR_MASK, (pL3FilterConfig->Protocol |
                                                              pL3FilterConfig->SrcAddrFilterMatch |
                                                              pL3FilterConfig->DestAddrFilterMatch |
                                                              (pL3FilterConfig->SrcAddrHigherBitsMatch << 6) |
                                                              (pL3FilterConfig->DestAddrHigherBitsMatch << 11)));
  }
  else  /* Filter == ETH_L3_FILTER_1 */
  {
    /* Write configuration to MACL3L4C1R register */
    MODIFY_REG(heth->Instance->MACL3L4C1R, ETH_MACL3CR_MASK, (pL3FilterConfig->Protocol |
                                                              pL3FilterConfig->SrcAddrFilterMatch |
                                                              pL3FilterConfig->DestAddrFilterMatch |
                                                              (pL3FilterConfig->SrcAddrHigherBitsMatch << 6) |
                                                              (pL3FilterConfig->DestAddrHigherBitsMatch << 11)));
  }

  if (Filter == ETH_L3_FILTER_0)
  {
    /* Check if IPv6 protocol is selected */
    if (pL3FilterConfig->Protocol != ETH_L3_IPV4_MATCH)
    {
      /* Set the IPv6 address match */
      /* Set Bits[31:0] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A00R, pL3FilterConfig->Ip6Addr[0]);
      /* Set Bits[63:32] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A10R, pL3FilterConfig->Ip6Addr[1]);
      /* update Bits[95:64] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A20, pL3FilterConfig->Ip6Addr[2]);
      /* update Bits[127:96] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A30, pL3FilterConfig->Ip6Addr[3]);
    }
    else /* IPv4 protocol is selected */
    {
      /* Set the IPv4 source address match */
      WRITE_REG(heth->Instance->MACL3A00R, pL3FilterConfig->Ip4SrcAddr);
      /* Set the IPv4 destination address match */
      WRITE_REG(heth->Instance->MACL3A10R, pL3FilterConfig->Ip4DestAddr);
    }
  }
  else  /* Filter == ETH_L3_FILTER_1 */
  {
    /* Check if IPv6 protocol is selected */
    if (pL3FilterConfig->Protocol != ETH_L3_IPV4_MATCH)
    {
      /* Set the IPv6 address match */
      /* Set Bits[31:0] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A01R, pL3FilterConfig->Ip6Addr[0]);
      /* Set Bits[63:32] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A11R, pL3FilterConfig->Ip6Addr[1]);
      /* update Bits[95:64] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A21R, pL3FilterConfig->Ip6Addr[2]);
      /* update Bits[127:96] of 128-bit IP addr */
      WRITE_REG(heth->Instance->MACL3A31R, pL3FilterConfig->Ip6Addr[3]);
    }
    else /* IPv4 protocol is selected */
    {
      /* Set the IPv4 source address match */
      WRITE_REG(heth->Instance->MACL3A01R, pL3FilterConfig->Ip4SrcAddr);
      /* Set the IPv4 destination address match */
      WRITE_REG(heth->Instance->MACL3A11R, pL3FilterConfig->Ip4DestAddr);
    }
  }

  /* Enable L3 filter */
  SET_BIT(heth->Instance->MACPFR, ETH_MACPFR_IPFE);

  return HAL_OK;
}

/**
  * @brief  Configures the L3 Filter, this function allow to:
  *         set the layer 3 protocol to be matched (IPv4 or IPv6)
  *         enable/disable L3 source/destination port perfect/inverse match.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  Filter: L3 filter to configured, this parameter must be one of the following
  *           ETH_L3_FILTER_0
  *           ETH_L3_FILTER_1
  * @param  pL3FilterConfig: pointer to a ETH_L3FilterConfigTypeDef structure
  *         that will contain the L3 filter configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETHEx_GetL3FilterConfig(const ETH_HandleTypeDef *heth, uint32_t Filter,
                                              ETH_L3FilterConfigTypeDef *pL3FilterConfig)
{
  if (pL3FilterConfig == NULL)
  {
    return HAL_ERROR;
  }
  pL3FilterConfig->Protocol = READ_BIT(*((__IO uint32_t *)(&(heth->Instance->MACL3L4C0R) + Filter)),
                                       ETH_MACL3L4C0R_L3PEN0);
  pL3FilterConfig->SrcAddrFilterMatch = READ_BIT(*((__IO uint32_t *)(&(heth->Instance->MACL3L4C0R) + Filter)),
                                                 (ETH_MACL3L4C0R_L3SAM0 | ETH_MACL3L4C0R_L3SAIM0));
  pL3FilterConfig->DestAddrFilterMatch = READ_BIT(*((__IO uint32_t *)(&(heth->Instance->MACL3L4C0R) + Filter)),
                                                  (ETH_MACL3L4C0R_L3DAM0 | ETH_MACL3L4C0R_L3DAIM0));
  pL3FilterConfig->SrcAddrHigherBitsMatch = (READ_BIT(*((__IO uint32_t *)(&(heth->Instance->MACL3L4C0R) + Filter)),
                                                      ETH_MACL3L4C0R_L3HSBM0) >> 6);
  pL3FilterConfig->DestAddrHigherBitsMatch = (READ_BIT(*((__IO uint32_t *)(&(heth->Instance->MACL3L4C0R) + Filter)),
                                                       ETH_MACL3L4C0R_L3HDBM0) >> 11);


  if (Filter == ETH_L3_FILTER_0)
  {
    if (pL3FilterConfig->Protocol != ETH_L3_IPV4_MATCH)
    {
      WRITE_REG(pL3FilterConfig->Ip6Addr[0], heth->Instance->MACL3A00R);
      WRITE_REG(pL3FilterConfig->Ip6Addr[1], heth->Instance->MACL3A10R);
      WRITE_REG(pL3FilterConfig->Ip6Addr[2], heth->Instance->MACL3A20);
      WRITE_REG(pL3FilterConfig->Ip6Addr[3], heth->Instance->MACL3A30);
    }
    else
    {
      WRITE_REG(pL3FilterConfig->Ip4SrcAddr, heth->Instance->MACL3A00R);
      WRITE_REG(pL3FilterConfig->Ip4DestAddr, heth->Instance->MACL3A10R);
    }
  }
  else  /* ETH_L3_FILTER_1 */
  {
    if (pL3FilterConfig->Protocol != ETH_L3_IPV4_MATCH)
    {
      WRITE_REG(pL3FilterConfig->Ip6Addr[0], heth->Instance->MACL3A01R);
      WRITE_REG(pL3FilterConfig->Ip6Addr[1], heth->Instance->MACL3A11R);
      WRITE_REG(pL3FilterConfig->Ip6Addr[2], heth->Instance->MACL3A21R);
      WRITE_REG(pL3FilterConfig->Ip6Addr[3], heth->Instance->MACL3A31R);
    }
    else
    {
      WRITE_REG(pL3FilterConfig->Ip4SrcAddr, heth->Instance->MACL3A01R);
      WRITE_REG(pL3FilterConfig->Ip4DestAddr, heth->Instance->MACL3A11R);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Enables L3 and L4 filtering process.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None.
  */
void HAL_ETHEx_EnableL3L4Filtering(ETH_HandleTypeDef *heth)
{
  /* Enable L3/L4 filter */
  SET_BIT(heth->Instance->MACPFR, ETH_MACPFR_IPFE);
}

/**
  * @brief  Disables L3 and L4 filtering process.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None.
  */
void HAL_ETHEx_DisableL3L4Filtering(ETH_HandleTypeDef *heth)
{
  /* Disable L3/L4 filter */
  CLEAR_BIT(heth->Instance->MACPFR, ETH_MACPFR_IPFE);
}

/**
  * @brief  Get the VLAN Configuration for Receive Packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pVlanConfig: pointer to a ETH_RxVLANConfigTypeDef structure
  *         that will contain the VLAN filter configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETHEx_GetRxVLANConfig(const ETH_HandleTypeDef *heth, ETH_RxVLANConfigTypeDef *pVlanConfig)
{
  if (pVlanConfig == NULL)
  {
    return HAL_ERROR;
  }

  pVlanConfig->InnerVLANTagInStatus = ((READ_BIT(heth->Instance->MACVTCR,
                                                 ETH_MACVTCR_EIVLRXS) >> 31) == 0U) ? DISABLE : ENABLE;
  pVlanConfig->StripInnerVLANTag  = READ_BIT(heth->Instance->MACVTCR, ETH_MACVTCR_EIVLS);
  pVlanConfig->InnerVLANTag = ((READ_BIT(heth->Instance->MACVTCR,
                                         ETH_MACVTCR_ERIVLT) >> 27) == 0U) ? DISABLE : ENABLE;
  pVlanConfig->DoubleVLANProcessing = ((READ_BIT(heth->Instance->MACVTCR,
                                                 ETH_MACVTCR_EDVLP) >> 26) == 0U) ? DISABLE : ENABLE;
  pVlanConfig->VLANTagHashTableMatch = ((READ_BIT(heth->Instance->MACVTCR,
                                                  ETH_MACVTCR_VTHM) >> 25) == 0U) ? DISABLE : ENABLE;
  pVlanConfig->VLANTagInStatus = ((READ_BIT(heth->Instance->MACVTCR,
                                            ETH_MACVTCR_EVLRXS) >> 24) == 0U) ? DISABLE : ENABLE;
  pVlanConfig->StripVLANTag = READ_BIT(heth->Instance->MACVTCR, ETH_MACVTCR_EVLS);
  pVlanConfig->VLANTypeCheck = READ_BIT(heth->Instance->MACVTCR,
                                        (ETH_MACVTCR_DOVLTC | ETH_MACVTCR_ERSVLM | ETH_MACVTCR_ESVL));
  pVlanConfig->VLANTagInverceMatch = ((READ_BIT(heth->Instance->MACVTCR, ETH_MACVTCR_VTIM) >> 17) == 0U)
                                     ? DISABLE : ENABLE;

  return HAL_OK;
}

/**
  * @brief  Set the VLAN Configuration for Receive Packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  pVlanConfig: pointer to a ETH_RxVLANConfigTypeDef structure
  *         that contains VLAN filter configuration.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ETHEx_SetRxVLANConfig(ETH_HandleTypeDef *heth, ETH_RxVLANConfigTypeDef *pVlanConfig)
{
  if (pVlanConfig == NULL)
  {
    return HAL_ERROR;
  }

  /* Write config to MACVTR */
  MODIFY_REG(heth->Instance->MACVTCR, ETH_MACRXVLAN_MASK, (((uint32_t)pVlanConfig->InnerVLANTagInStatus << 31) |
                                                           pVlanConfig->StripInnerVLANTag |
                                                           ((uint32_t)pVlanConfig->InnerVLANTag << 27) |
                                                           ((uint32_t)pVlanConfig->DoubleVLANProcessing << 26) |
                                                           ((uint32_t)pVlanConfig->VLANTagHashTableMatch << 25) |
                                                           ((uint32_t)pVlanConfig->VLANTagInStatus << 24) |
                                                           pVlanConfig->StripVLANTag |
                                                           pVlanConfig->VLANTypeCheck |
                                                           ((uint32_t)pVlanConfig->VLANTagInverceMatch << 17)));

  return HAL_OK;
}

/**
  * @brief  Set the VLAN Hash Table
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  VLANHashTable: VLAN hash table 16 bit value
  * @retval None
  */
void HAL_ETHEx_SetVLANHashTable(ETH_HandleTypeDef *heth, uint32_t VLANHashTable)
{
  MODIFY_REG(heth->Instance->MACVHTR, ETH_MACVHTR_VLHT, VLANHashTable);
}

/**
  * @brief  Get the VLAN Configuration for Transmit Packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  VLANTag: Selects the vlan tag, this parameter must be one of the following
  *                 ETH_OUTER_TX_VLANTAG
  *                 ETH_INNER_TX_VLANTAG
  * @param  pVlanConfig: pointer to a ETH_TxVLANConfigTypeDef structure
  *         that will contain the Tx VLAN filter configuration.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_ETHEx_GetTxVLANConfig(const ETH_HandleTypeDef *heth, uint32_t VLANTag,
                                            ETH_TxVLANConfigTypeDef *pVlanConfig)
{
  if (pVlanConfig == NULL)
  {
    return HAL_ERROR;
  }

  if (VLANTag == ETH_INNER_TX_VLANTAG)
  {
    pVlanConfig->SourceTxDesc = ((READ_BIT(heth->Instance->MACIVIR, ETH_MACVIR_VLTI) >> 20) == 0U) ? DISABLE : ENABLE;
    pVlanConfig->SVLANType = ((READ_BIT(heth->Instance->MACIVIR, ETH_MACVIR_CSVL) >> 19) == 0U) ? DISABLE : ENABLE;
    pVlanConfig->VLANTagControl = READ_BIT(heth->Instance->MACIVIR, (ETH_MACVIR_VLP | ETH_MACVIR_VLC));
  }
  else
  {
    pVlanConfig->SourceTxDesc = ((READ_BIT(heth->Instance->MACVIR, ETH_MACVIR_VLTI) >> 20) == 0U) ? DISABLE : ENABLE;
    pVlanConfig->SVLANType = ((READ_BIT(heth->Instance->MACVIR, ETH_MACVIR_CSVL) >> 19) == 0U) ? DISABLE : ENABLE;
    pVlanConfig->VLANTagControl = READ_BIT(heth->Instance->MACVIR, (ETH_MACVIR_VLP | ETH_MACVIR_VLC));
  }

  return HAL_OK;;
}

/**
  * @brief  Set the VLAN Configuration for Transmit Packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  VLANTag: Selects the vlan tag, this parameter must be one of the following
  *                 ETH_OUTER_TX_VLANTAG
  *                 ETH_INNER_TX_VLANTAG
  * @param  pVlanConfig: pointer to a ETH_TxVLANConfigTypeDef structure
  *         that contains Tx VLAN filter configuration.
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_ETHEx_SetTxVLANConfig(ETH_HandleTypeDef *heth, uint32_t VLANTag,
                                            const ETH_TxVLANConfigTypeDef *pVlanConfig)
{
  if (VLANTag == ETH_INNER_TX_VLANTAG)
  {
    MODIFY_REG(heth->Instance->MACIVIR, ETH_MACTXVLAN_MASK, (((uint32_t)pVlanConfig->SourceTxDesc << 20) |
                                                             ((uint32_t)pVlanConfig->SVLANType << 19) |
                                                             pVlanConfig->VLANTagControl));
    /* Enable Double VLAN processing */
    SET_BIT(heth->Instance->MACVTCR, ETH_MACVTCR_EDVLP);
  }
  else
  {
    MODIFY_REG(heth->Instance->MACVIR, ETH_MACTXVLAN_MASK, (((uint32_t)pVlanConfig->SourceTxDesc << 20) |
                                                            ((uint32_t)pVlanConfig->SVLANType << 19) |
                                                            pVlanConfig->VLANTagControl));
  }

  return HAL_OK;
}

/**
  * @brief  Set the VLAN Tag Identifier for Transmit Packets.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  VLANTag: Selects the vlan tag, this parameter must be one of the following
  *                 ETH_OUTER_TX_VLANTAG
  *                 ETH_INNER_TX_VLANTAG
  * @param  VLANIdentifier: VLAN Identifier 16 bit value
  * @retval None
  */
void HAL_ETHEx_SetTxVLANIdentifier(ETH_HandleTypeDef *heth, uint32_t VLANTag, uint32_t VLANIdentifier)
{
  if (VLANTag == ETH_INNER_TX_VLANTAG)
  {
    MODIFY_REG(heth->Instance->MACIVIR, ETH_MACVIR_VLT, VLANIdentifier);
  }
  else
  {
    MODIFY_REG(heth->Instance->MACVIR, ETH_MACVIR_VLT, VLANIdentifier);
  }
}

/**
  * @brief  Enables the VLAN Tag Filtering process.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None.
  */
void HAL_ETHEx_EnableVLANProcessing(ETH_HandleTypeDef *heth)
{
  /* Enable VLAN processing */
  SET_BIT(heth->Instance->MACPFR, ETH_MACPFR_VTFE);
}

/**
  * @brief  Disables the VLAN Tag Filtering process.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None.
  */
void HAL_ETHEx_DisableVLANProcessing(ETH_HandleTypeDef *heth)
{
  /* Disable VLAN processing */
  CLEAR_BIT(heth->Instance->MACPFR, ETH_MACPFR_VTFE);
}

/**
  * @brief  Enters the Low Power Idle (LPI) mode
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @param  TxAutomate: Enable/Disable automate enter/exit LPI mode.
  * @param  TxClockStop: Enable/Disable Tx clock stop in LPI mode.
  * @retval None
  */
void HAL_ETHEx_EnterLPIMode(ETH_HandleTypeDef *heth, FunctionalState TxAutomate, FunctionalState TxClockStop)
{
  /* Enable LPI Interrupts */
  __HAL_ETH_MAC_ENABLE_IT(heth, ETH_MACIER_LPIIE);

  /* Write to LPI Control register: Enter low power mode */
  MODIFY_REG(heth->Instance->MACLCSR, (ETH_MACLCSR_LPIEN | ETH_MACLCSR_LPITXA | ETH_MACLCSR_LPITCSE),
             (((uint32_t)TxAutomate << 19) |
              ((uint32_t)TxClockStop << 21) |
              ETH_MACLCSR_LPIEN));
}

/**
  * @brief  Exits the Low Power Idle (LPI) mode.
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval None
  */
void HAL_ETHEx_ExitLPIMode(ETH_HandleTypeDef *heth)
{
  /* Clear the LPI Config and exit low power mode */
  CLEAR_BIT(heth->Instance->MACLCSR, (ETH_MACLCSR_LPIEN | ETH_MACLCSR_LPITXA | ETH_MACLCSR_LPITCSE));

  /* Enable LPI Interrupts */
  __HAL_ETH_MAC_DISABLE_IT(heth, ETH_MACIER_LPIIE);
}

/**
  * @brief  Returns the ETH MAC LPI event
  * @param  heth: pointer to a ETH_HandleTypeDef structure that contains
  *         the configuration information for ETHERNET module
  * @retval ETH MAC WakeUp event
  */
uint32_t HAL_ETHEx_GetMACLPIEvent(const ETH_HandleTypeDef *heth)
{
  return heth->MACLPIEvent;
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

#endif /* ETH1 || ETH2 */

#endif /* HAL_ETH_MODULE_ENABLED */
/**
  * @}
  */
