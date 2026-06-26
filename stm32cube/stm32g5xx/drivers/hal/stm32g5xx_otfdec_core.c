/**
  **********************************************************************************************************************
  * @file    stm32g5xx_otfdec_core.c
  * @brief   OTFDEC core driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the OTFDEC peripheral:
  *           + Configuration functions
  *           + Encryption functions
  *           + On the fly decryption functions
  *           + Peripheral state functions
  *
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
#include "stm32g5xx_otfdec_core.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */
#if defined(OTFDEC1)
/** @defgroup OTFDEC_CORE OTFDEC Core
  * @{
  */
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private Constants -------------------------------------------------------------------------------------------------*/
/*! OTFDEC region base address */
#define OTFDEC1_REGION4_ADDRESS   OTFDEC1_REGION4    /*!< OTFDEC1 region 4 base address */

/*! XSPI base address */
#define XSPI1_BASE_ADDRESS        XSPI1_BASE         /*!< XSPI1 base address            */

/*! Key region register numbers */
#define NB_KEY_REG                4U                 /*!< Number of key registers       */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup OTFDEC_Private_Functions OTFDEC private functions
  * @{
  */
static uint8_t OTFDEC_ComputeKeyCRC(const uint32_t *p_Key);
/**
  * @}
  */
/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup OTFDEC_CORE_Exported_Functions
  *  @{
  */

/** @addtogroup OTFDEC_CORE_Group3 OTFDEC region global configuration functions
  * @{
  */
/**
  * @brief  Set the region configuration.
  * @param  regionx           OTFDEC region instance.
  * @param  mode              OTFDEC region mode.
  * @param  p_key             Pointer to a set of keys.
  * @param  nonce_0           OTFDEC region nonce 0.
  * @param  nonce_1           OTFDEC region nonce 1.
  * @param  start_address     OTFDEC region start address.
  * @param  end_address       OTFDEC region end address.
  * @param  version           OTFDEC region firmware version.
  * @retval OTFDEC_CORE_ERROR The key region value is not set.
  * @retval OTFDEC_CORE_OK    The key region value is set.
  */
otfdec_core_status_t OTFDEC_SetConfigRegion(OTFDEC_Region_TypeDef *regionx, uint8_t mode, const uint8_t *p_key,
                                            uint32_t nonce_0, uint32_t nonce_1, uint32_t start_address,
                                            uint32_t end_address, uint16_t version)
{
  uint32_t keyval[NB_KEY_REG] = {0};
  volatile uint32_t *reg_keyr[NB_KEY_REG] =
  {
    &regionx->REG_KEYR0,
    &regionx->REG_KEYR1,
    &regionx->REG_KEYR2,
    &regionx->REG_KEYR3
  };

  /* Set the region mode */
  STM32_MODIFY_REG(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_MODE, mode);

  /* Set the 128-bit key */
  for (uint32_t counter = 0U; counter < NB_KEY_REG; counter++)
  {
    /* Aggregate four bytes from p_key into a 32-bit integer and store in keyval[counter] */
    keyval[counter]  = ((uint32_t)p_key[(counter * 4U) + 3U] << 24U);
    keyval[counter] |= ((uint32_t)p_key[(counter * 4U) + 2U] << 16U);
    keyval[counter] |= ((uint32_t)p_key[(counter * 4U) + 1U] << 8U);
    keyval[counter] |= ((uint32_t)p_key[(counter * 4U)]);

    STM32_WRITE_REG(*reg_keyr[counter], keyval[counter]);

    __DSB();
    __ISB();
  }

  /* Compute theoretically expected CRC and compare it with the CRC reported by the peripheral */
  if (OTFDEC_ComputeKeyCRC(keyval) != OTFDEC_GetRegionKeyCRC(regionx))
  {
    return OTFDEC_CORE_ERROR;
  }

  /* Set the region nonce_0 */
  STM32_WRITE_REG(regionx->REG_NONCER0, nonce_0);

  /* Set the region nonce_1 */
  STM32_WRITE_REG(regionx->REG_NONCER1, nonce_1);

  /* Set the region start address */
  STM32_WRITE_REG(regionx->REG_START_ADDR, start_address);

  /* Set the region end address */
  STM32_WRITE_REG(regionx->REG_END_ADDR, end_address);

  /* Set the region firmware version */
  STM32_MODIFY_REG(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_REG_VERSION,
                   ((uint32_t)version << OTFDEC_REG_CONFIGR_REG_VERSION_Pos));

  return OTFDEC_CORE_OK;
}

/**
  * @brief  Get the region configuration.
  * @param  regionx         OTFDEC region instance.
  * @param  p_mode          Pointer to region mode.
  * @param  p_nonce_0       Pointer to region nonce 0.
  * @param  p_nonce_1       Pointer to region nonce 1.
  * @param  p_start_address Pointer to region start address.
  * @param  p_end_address   Pointer to region end address.
  * @param  p_version       Pointer to region firmware version.
  */
void OTFDEC_GetConfigRegion(const OTFDEC_Region_TypeDef *regionx, uint8_t *p_mode, uint32_t *p_nonce_0,
                            uint32_t *p_nonce_1, uint32_t *p_start_address, uint32_t *p_end_address,
                            uint16_t *p_version)
{
  *p_mode          = (uint8_t)(STM32_READ_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_MODE));

  *p_nonce_0       = (uint32_t)STM32_READ_REG(regionx->REG_NONCER0);

  *p_nonce_1       = (uint32_t)STM32_READ_REG(regionx->REG_NONCER1);

  *p_start_address = (uint32_t)STM32_READ_REG(regionx->REG_START_ADDR) + XSPI1_BASE_ADDRESS;
  *p_end_address   = (uint32_t)STM32_READ_REG(regionx->REG_END_ADDR)   + XSPI1_BASE_ADDRESS;

  *p_version       = (uint16_t)(STM32_READ_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_REG_VERSION) \
                                >> OTFDEC_REG_CONFIGR_REG_VERSION_Pos);
}
/**
  * @}
  */

/** @addtogroup OTFDEC_CORE_Group4 OTFDEC region on the fly decryption functions
  * @{
  */
/**
  * @brief  Start the OTFDEC region decryption.
  * @param  otfdecx    OTFDEC instance.
  * @param  regionx    OTFDEC region instance.
  * @param  interrupts OTFDEC interrupt.
  */
void OTFDEC_StartRegionDecryption(OTFDEC_TypeDef *otfdecx, OTFDEC_Region_TypeDef *regionx, uint32_t interrupts)
{
  STM32_CLEAR_BIT(otfdecx->CR, OTFDEC_CR_ENC);
  STM32_SET_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_REG_EN);
  STM32_SET_BIT(otfdecx->IER, interrupts);
}
/**
  * @}
  */

/** @addtogroup OTFDEC_CORE_Group5 OTFDEC encryption functions
  * @{
  */
/**
  * @brief  Encrypt the OTFDEC region.
  * @param  otfdecx       OTFDEC instance.
  * @param  regionx       OTFDEC region instance.
  * @param  p_input       Pointer the plain data.
  * @param  p_output      Pointer to the ciphered data.
  * @param  size_byte     Plain data size in byte.
  * @param  start_address Starting address in the external memory area where the enciphered data will be eventually.
  * @param  interrupts    Specifies the OTFDEC interrupt sources to be enabled. This parameter can be a combination
  *                       of @ref OTFDEC_Interrupts group.
  */
void OTFDEC_Encrypt(OTFDEC_TypeDef *otfdecx, OTFDEC_Region_TypeDef *regionx, const uint32_t *p_input,
                    uint32_t *p_output, uint32_t size_byte, uint32_t start_address, uint32_t interrupts)
{
  uint32_t size_word;
  __IO uint32_t *ext_mem_ptr = (uint32_t *)start_address;
  const uint32_t *in_ptr  = p_input;
  uint32_t *out_ptr = p_output;

  size_word = (size_byte + 3U) / 4U;

  STM32_SET_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_REG_EN);
  STM32_SET_BIT(otfdecx->CR, OTFDEC_CR_ENC);
  STM32_SET_BIT(otfdecx->IER, interrupts);

  /* Encrypt the input data */
  while (size_word > 0U)
  {
    *ext_mem_ptr = *in_ptr;
    in_ptr++;
    *out_ptr = *ext_mem_ptr;
    out_ptr++;
    ext_mem_ptr++;
    size_word-- ;
  }

  STM32_CLEAR_BIT(regionx->REG_CONFIGR, OTFDEC_REG_CONFIGR_REG_EN);
  STM32_CLEAR_BIT(otfdecx->CR, OTFDEC_CR_ENC);
}
/**
  * @}
  */
/** @addtogroup OTFDEC_CORE_Group6 OTFDEC privileged access level attributes management functions
  * @{
  */
/**
  * @brief  Set the privileged access level attribute .
  * @param  otfdecx    OTFDEC instance.
  * @param  priv_attr This parameter can be one of the following values:
  *         @arg @ref OTFDEC_NPRIV
  *         @arg @ref OTFDEC_PRIV
  * @retval OTFDEC_CORE_OK      Privileged attribute has been set successfully
  * @retval OTFDEC_CORE_ERROR   Non-privileged write to a privileged-only register
  */
otfdec_core_status_t OTFDEC_SetPrivAttr(OTFDEC_TypeDef *otfdecx, uint32_t priv_attr)
{
  if (STM32_IS_PRIVILEGED_EXECUTION() == 0U)
  {
    return OTFDEC_CORE_ERROR;
  }

  STM32_MODIFY_REG(otfdecx->PRIVCFGR, OTFDEC_PRIVCFGR_PRIV, priv_attr);

  return OTFDEC_CORE_OK;
}
/**
  * @brief  Get the privileged access level attribute.
  * @param  otfdecx    OTFDEC instance.
  * @retval The returned value can be one of the following values:
  *         @arg @ref OTFDEC_PRIV
  *         @arg @ref OTFDEC_NPRIV
  */
uint32_t OTFDEC_GetPrivAttr(const OTFDEC_TypeDef *otfdecx)
{
  return ((STM32_READ_BIT(otfdecx->PRIVCFGR, OTFDEC_PRIVCFGR_PRIV) == OTFDEC_PRIVCFGR_PRIV)
          ? OTFDEC_PRIV : OTFDEC_NPRIV);
}
/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup OTFDEC_Private_Functions OTFDEC private functions
  * @{
  */
/**
  * @brief  Compute Key CRC.
  * @param  p_key pointer to a set of keys.
  * @retval CRC value.
  */
static uint8_t OTFDEC_ComputeKeyCRC(const uint32_t *p_key)
{
  uint8_t crc7_poly = 0x7;
  uint8_t crc = 0;
  const uint32_t key_strobe[4] = {0xAA55AA55U, 0x3U, 0x18U, 0xC0U};
  uint32_t keyval;
  uint32_t k;
  const uint32_t *temp = p_key;

  for (uint8_t j = 0U; j < 4U; j++)
  {
    keyval = *temp;
    temp++;
    if (j == 0U)
    {
      keyval ^= key_strobe[0];
    }
    else
    {
      keyval ^= (key_strobe[j] << 24) | ((uint32_t)crc << 16) | (key_strobe[j] << 8) | crc;
    }

    crc = 0;
    for (uint8_t i = 0U; i < (uint8_t)32; i++)
    {
      k = ((((uint32_t)crc >> 7) ^ ((keyval >> ((uint8_t)31 - i)) & ((uint8_t)0xF)))) & 1U;
      crc <<= 1;
      if (k != 0U)
      {
        crc ^= crc7_poly;
      }
    }

    crc ^= (uint8_t)0x55;
  }

  return (uint8_t)crc;
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* OTFDEC1 */
/**
  * @}
  */
