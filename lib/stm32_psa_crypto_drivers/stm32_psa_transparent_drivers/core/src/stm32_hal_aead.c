/**
  ******************************************************************************
  * @file    stm32_hal_aead.c
  * @author  MCD Application Team
  * @brief   Implementation of STM32 AES Middleware Core module
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

#include <mbedtls/constant_time.h>

#include "stm32_hal_aes.h"
#include "stm32_hal_aead.h"
#include "stm32_hal_aes_private.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_private.h"
#include "stm32_soc_hal.h"

#include <string.h>
#include <stdlib.h>

/*
 * PSA Crypto API specification says that for CCM operations psa_set_lengths() must be
 * called before psa_set_nonce(). However, the tf-psa-crypto tests does not expect this behavior
 * and there are no strong reason why it should be enforced but possibly slightly optimizing
 * memory footprint for PSA Crypto drivers.
 * Enable definition of macro ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS to
 * strictly follow PSA Crypto API specification on this topic.
 *
 * The config is disabled by default.
 */
#ifndef ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS
#define ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS     0
#endif /* ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS */

/*
 * PSA Crypto tests expects psa_aead_update() to compute and output all output
 * data when last bytes are reached. This breaks the PSA Crypto API since a
 * call to psa_aead_update() may not generate all output bytes and rely on
 * psa_aead_finish() or psa_aead_verify() to output the last bytes.
 * See for example test_suite_psa_crypto, case starting with string ID
 * "PSA Multipart AEAD encrypt: AES - CCM,".
 *
 * ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES can be enabled to
 * conform this the test behavior (not waiting psa_aead_finish()/verify() to
 * output the message mast bytes).
 *
 * The config is enabled by default.
 */
#ifndef ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES
#define ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES        1
#endif /* ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES */

#ifdef STM32_HAL_AES_AEAD_DRIVER_ENABLED

static STM32_HalStatusTypeDef stm32_hal_aead_set_algo_id(stm32_hal_aes_ctx_t *ctx,
                                                         STM32_HalAesAlgTypeDef alg)
{
  switch (alg)
  {
  case STM32_HAL_ALG_AES_GCM:
  case STM32_HAL_ALG_AES_CCM:
    break;
  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  ctx->algo_id = alg;

  return STM32_HAL_SUCCESS;
}

static STM32_HalStatusTypeDef stm32_hal_aead_set_tag_size(stm32_hal_aes_ctx_t *ctx,
                                                          size_t tag_size)
{
  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_GCM:
    if ((tag_size < 4) || (tag_size > 16))
    {
      return STM32_HAL_INVALID_ARGUMENT;
    }
    break;
  case STM32_HAL_ALG_AES_CCM:
    if (((tag_size % 2) != 0) || (tag_size < 4) || (tag_size > 16))
    {
      return STM32_HAL_INVALID_ARGUMENT;
    }
    break;
  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  ctx->aead_config.tag_size = tag_size;

  return STM32_HAL_SUCCESS;
}

/*
 * Prepare CCM B0 data (stored in SoC IVR registers)
 * This requires message length, nonce length and addition data length are known.
 */
static STM32_HalStatusTypeDef prepare_ccm_b0(stm32_hal_aes_ctx_t *ctx)
{
  uint32_t iv_data[STM32_CIPHER_BLOCK_SIZE / sizeof(uint32_t)] = {0};
  size_t nonce_size = ctx->aead_config.nonce_size;
  uint8_t *iv_byte_ptr = (uint8_t *)iv_data;
  size_t len_left;
  uint32_t i;
  uint8_t q;

  ASSERT(ctx->algo_id == STM32_HAL_ALG_AES_CCM);
  ASSERT((nonce_size >= 7) && (nonce_size <= 13));

  /* Nonce was stored in ctx->iv[] first bytes */
  (void)memcpy(iv_byte_ptr + 1, ctx->iv, nonce_size);

  q = 15 - nonce_size;

  iv_byte_ptr[0] = ((ctx->aead_config.tag_size - 2U) / 2U) << 3U;
  iv_byte_ptr[0] |= q - 1U;
  if (ctx->aead_config.aad_size != 0)
  {
    iv_byte_ptr[0] |= 1U << 6U;
  }

  for (i = 0, len_left = ctx->aead_config.message_size; i < q; i++, len_left >>= 8)
  {
    iv_byte_ptr[15 - i] = (uint8_t)(len_left & 0xff);
  }

  if (len_left > 0U)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  /* First authentication block in little-endian format */
#ifdef STM32_AES_HAL_V1_L4
  memcpy(ctx->iv, iv_byte_ptr, sizeof(iv_data));
#else
  read_u32_swapped(ctx->iv, iv_byte_ptr, sizeof(iv_data));
#endif

  return STM32_HAL_SUCCESS;
}

/*
 * Prepare CCM B1 data buffer (headered buffer for additional data).
 * Requires the number of additional data is known.
 */
static STM32_HalStatusTypeDef prepare_ccm_b1_buffer(stm32_hal_aes_ctx_t *ctx)
{
  uint8_t *b1_padded_addr;
  size_t b1_header_size;
  size_t b1_length;
  size_t ad_length;

  ASSERT(ctx->algo_id == STM32_HAL_ALG_AES_CCM);
  ASSERT(ctx->aead_config.aad_size_set);

  ad_length = ctx->aead_config.aad_size;

  if ((uint64_t)ad_length > 0xff00)
  {
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  /* Currently support only length below 0xff00 hence a header of 2 bytes */
  b1_header_size = 2;

  /* Round up buffer length to 32bit words */
  b1_length = ((ad_length + b1_header_size + 3U) / 4U) * 4U;

  b1_padded_addr = calloc(1, b1_length);
  if (b1_padded_addr == NULL)
  {
    return STM32_HAL_OUT_OF_MEMORY;
  }

  /* Header: additional data length */
  b1_padded_addr[0] = (uint8_t)((ad_length >> 8) & 0xFF);
  b1_padded_addr[1] = (uint8_t)(ad_length & 0xFF);

  /* blocks (B) associated to the Associated Data (A) */
  ctx->aead_config.aad_b1 = (uint32_t *)b1_padded_addr;
  ctx->aead_config.b1_size = b1_length;

  return STM32_HAL_SUCCESS;
}

/*
 * Finalize setup of CCM B0/B1 buffers once message size, additional data size
 * and tag size are known.
 */
static STM32_HalStatusTypeDef stm32_aead_hal_finalize_ccm_config(stm32_hal_aes_ctx_t *ctx)
{
  STM32_HalStatusTypeDef status;

  status = prepare_ccm_b0(ctx);
  if (status == STM32_HAL_SUCCESS)
  {
    status = prepare_ccm_b1_buffer(ctx);
  }

  return status;
}

/*
 * Load operation configuration in the HAL driver.
 * This function requires that the device access mutex is locked.
 */
static STM32_HalStatusTypeDef stm32_aead_hal_configure(stm32_hal_aes_ctx_t *ctx)
{
  uint32_t hal_key_size_id;
  STM32_HalStatusTypeDef status;

  if (ctx->aead_config.nonce_size == 0)
  {
    return STM32_HAL_BAD_STATE;
  }

  /*
   * Before configuring the HAL, finalize the configuration for CCM
   * oprations.
   */
  if (ctx->algo_id == STM32_HAL_ALG_AES_CCM)
  {
    if (!ctx->aead_config.message_size_set || !ctx->aead_config.aad_size_set)
    {
      return STM32_HAL_BAD_STATE;
    }

    /*
     * If no additional data, stm32_aead_hal_finalize_ccm_config() has not
     * been called yet.
     */
    if (ctx->aead_config.aad_size == 0)
    {
      status = stm32_aead_hal_finalize_ccm_config(ctx);
      if (status != STM32_HAL_SUCCESS)
      {
        return status;
      }
    }
  }

  status = stm32_hal_aes_key_size_id(ctx->key_byte_size, &hal_key_size_id);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

#ifdef STM32_AES_HAL_V2
  /*
   * HAL2 sequence to initialize and configure the HAL driver:
   * - Call HAL_AES_Init() with the device reference,
   *   already done by STM32_HalAesInit() above.
   * - Call HAL_AES_SetXxxlKey() to register target key references
   * - Call HAL_AES_xxx_SetConfig() with the configuration data
   * - Call HAL_AES_SetDataSwapping() last, if needed
   */
  if (HAL_AES_SetNormalKey(&ctx->hal_handle, hal_key_size_id, ctx->key) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  if (ctx->algo_id == STM32_HAL_ALG_AES_GCM)
  {
    hal_aes_gcm_config_t conf = {
      .p_init_vect = ctx->iv,
      .p_header = ctx->aead_config.aad_b1,
      .header_size_byte = ctx->aead_config.b1_size,
    };

    if (HAL_AES_GCM_GMAC_SetConfig(&ctx->hal_handle, &conf) != HAL_OK)
    {
      return STM32_HAL_ERROR;
    }
  }
  else
  {
    hal_aes_ccm_config_t conf = {
      .p_b0 = ctx->iv,
      .p_header = ctx->aead_config.aad_b1,
      .header_size_byte = ctx->aead_config.b1_size,
    };

    if (HAL_AES_CCM_SetConfig(&ctx->hal_handle, &conf) != HAL_OK)
    {
      return STM32_HAL_ERROR;
    }
  }

  if (HAL_AES_SetDataSwapping(&ctx->hal_handle, HAL_AES_DATA_SWAPPING_BYTE) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }
#elif defined(STM32_AES_HAL_V1_L4)
  /*
   * HAL sequence for stm32l4/l1/l0 to initialize and configure the HAL driver:
   * - Set .Instance field in device handle and call HAL_CRYP_DeInit(),
   *   already done by STM32_HalAesInit() above.
   * - Set all needed field in the .Init struct of the device handl
   * - Set init phase ID in .Init struct and run init phase with HAL_CRYPEx_AES_Auth()
   * - Set header phase ID in .Init struct and run header phase with HAL_CRYPEx_AES_Auth()
   *   Needed only if thre are Authentication Additional Data
   * - Set payload phase ID in .Init struct to be ready to process input data
   */

  if (HAL_CRYP_DeInit(&ctx->hal_handle))
  {
    return STM32_HAL_ERROR;
  }

  ctx->hal_handle.Init.pKey = (uint8_t *)ctx->key;
  ctx->hal_handle.Init.KeySize = hal_key_size_id;
  ctx->hal_handle.Init.DataType = CRYP_DATATYPE_8B;
  ctx->hal_handle.Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  ctx->hal_handle.Init.Header = (uint8_t *)ctx->aead_config.aad_b1;
  ctx->hal_handle.Init.HeaderSize = ctx->aead_config.b1_size;
  ctx->hal_handle.Init.pInitVect = (uint8_t *)ctx->iv;

  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_GCM:
    ctx->hal_handle.Init.ChainingMode = CRYP_CHAINMODE_AES_GCM_GMAC;
    break;
  case STM32_HAL_ALG_AES_CCM:
#ifdef CRYP_CHAINMODE_AES_CCM
    ctx->hal_handle.Init.ChainingMode = CRYP_CHAINMODE_AES_CCM;
#else
    ctx->hal_handle.Init.ChainingMode = CRYP_CHAINMODE_AES_CMAC;
#endif
    break;
  default:
    break;
  }

  if (ctx->encrypt)
  {
    ctx->hal_handle.Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  }
  else
  {
    ctx->hal_handle.Init.OperatingMode = CRYP_ALGOMODE_DECRYPT;
  }

  if (HAL_CRYP_Init(&ctx->hal_handle) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  ctx->hal_handle.Init.GCMCMACPhase = CRYP_INIT_PHASE;
  if (HAL_CRYPEx_AES_Auth(&ctx->hal_handle, NULL, 0, NULL, ST_HAL_AES_TIMEOUT) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  if (ctx->hal_handle.Init.HeaderSize != 0)
  {
    ctx->hal_handle.Init.GCMCMACPhase = CRYP_HEADER_PHASE;
    if (HAL_CRYPEx_AES_Auth(&ctx->hal_handle, NULL, 0, NULL, ST_HAL_AES_TIMEOUT) != HAL_OK)
    {
      return STM32_HAL_ERROR;
    }
  }

  /* Next are the payload data, if any */
  ctx->hal_handle.Init.GCMCMACPhase = CRYP_PAYLOAD_PHASE;

#else
  /*
   * HAL sequence for remaining AES/CRYP devices to initialize and configure the HAL driver:
   * - Set .Instance field in device handle and call HAL_CRYP_Init(),
   *   already done by STM32_HalAesInit() above.
   * - Set configuraition with a CRYP_ConfigTypeDef struct pass to HAL_CRYP_SetConfig()
   */
  CRYP_ConfigTypeDef conf;

  if (HAL_CRYP_GetConfig(&ctx->hal_handle, &conf) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  conf.pKey = ctx->key;
  conf.KeySize = hal_key_size_id;
  conf.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
#ifdef CRYP_BYTE_SWAP
  conf.DataType = CRYP_BYTE_SWAP;
#else
  conf.DataType = CRYP_DATATYPE_8B;
#endif /* CRYP_BYTE_SWAP */
#ifdef CRYP_KEYMODE_NORMAL
  conf.KeyMode = CRYP_KEYMODE_NORMAL;
  conf.KeySelect = CRYP_KEYSEL_NORMAL;
#endif /* CRYP_KEYMODE_NORMAL */
  conf.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ONCE;

  if (ctx->algo_id == STM32_HAL_ALG_AES_GCM)
  {
#ifdef CRYP_AES_GCM_GMAC
    conf.Algorithm = CRYP_AES_GCM_GMAC;
#else
    conf.Algorithm = CRYP_AES_GCM;
#endif /* CRYP_AES_GCM_GMAC */
    conf.pInitVect = ctx->iv;
  }
  else
  {
    conf.Algorithm = CRYP_AES_CCM;
    conf.B0 = ctx->iv;
  }

  conf.Header = ctx->aead_config.aad_b1;
  conf.HeaderSize = ctx->aead_config.b1_size;

#ifdef CRYP_HEADERWIDTHUNIT_BYTE
  conf.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_BYTE;

  /*
   * A few SoC series (H7RS, N6, MP13, MP2) integrate a CRYP and an SAES instances.
   * They define CRYP_HEADERWIDTHUNIT_BYTE but only the SAES intance supports byte
   * header unit. When using CRYP, the header width unit must be 32bit words.
   * For these SoCs, there exists a IS_CRYP_INSTANCE() macro. Note that the buffer allocated
   * for ctx->aead_config.aad_b1 is 32bit word aligned, as well as ctx->aead_config.b1_size.
   */
#ifdef IS_CRYP_INSTANCE
  if (IS_CRYP_INSTANCE(ctx->hal_handle.Instance))
  {
    ASSERT((conf.HeaderSize % sizeof(uint32_t)) == 0);
    conf.HeaderSize /= 4U;
    conf.HeaderWidthUnit = CRYP_HEADERWIDTHUNIT_WORD;
  }
#endif /* IS_CRYP_INSTANCE */
#endif /* CRYP_HEADERWIDTHUNIT_BYTE */

  if (HAL_CRYP_SetConfig(&ctx->hal_handle, &conf) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }
#endif /* STM32_AES_HAL_V2 */

  return STM32_HAL_SUCCESS;
}

static STM32_HalStatusTypeDef stm32_aead_process_buffer(stm32_hal_aes_ctx_t *ctx,
                                                        const uint8_t *input,
                                                        uint8_t *output,
                                                        size_t length)
{
  stm32_hal_status_t hal_status = HAL_OK;
  STM32_HalStatusTypeDef status;

  status = stm32_hal_aes_get_hal_hw(ctx, stm32_aead_hal_configure);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

#ifdef STM32_AES_HAL_V2
  if (ctx->encrypt)
  {
    hal_status = HAL_AES_Encrypt(&ctx->hal_handle, (uint8_t *)input, length,
                                 output, ST_HAL_AES_TIMEOUT);
  }
  else
  {
    hal_status = HAL_AES_Decrypt(&ctx->hal_handle, (uint8_t *)input, length,
                                 output, ST_HAL_AES_TIMEOUT);
  }
#elif defined(STM32_AES_HAL_V1_L4)
  if (length != 0)
  {
    hal_status = HAL_CRYPEx_AES_Auth(&ctx->hal_handle, (uint8_t *)input, length,
                                     output, ST_HAL_AES_TIMEOUT);
  }
#else
  if (ctx->encrypt)
  {
    hal_status = HAL_CRYP_Encrypt(&ctx->hal_handle, (uint32_t *)input, length,
                                  (uint32_t *)output, ST_HAL_AES_TIMEOUT);
  }
  else
  {
    hal_status = HAL_CRYP_Decrypt(&ctx->hal_handle, (uint32_t *)input, length,
                                  (uint32_t *)output, ST_HAL_AES_TIMEOUT);
  }
#endif /* STM32_AES_HAL_V2 */

  if (hal_status == HAL_OK)
  {
    ctx->aead_config.current_message_size += length;
  }
  else
  {
    status = STM32_HAL_ERROR;
  }

  stm32_hal_aes_put_hal_hw();

  return status;
}

static STM32_HalStatusTypeDef stm32_aead_generate_tag(stm32_hal_aes_ctx_t *ctx,
                                                      uint32_t *tag)
{
  stm32_hal_status_t hal_status;
  STM32_HalStatusTypeDef status;

  /*
   * If no data, ensure the HAL is informed (process 0 bytes).
   * NOTE: stm32_aead_process_buffer() locks HW mutex itself
   * so we must not acquire it yet.
   */
  if (ctx->aead_config.current_message_size == 0)
  {
    status = stm32_aead_process_buffer(ctx, NULL, NULL, 0);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }
  }

  status = stm32_hal_aes_get_hal_hw(ctx, stm32_aead_hal_configure);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  if (ctx->algo_id == STM32_HAL_ALG_AES_GCM)
  {
    /* Generate GCM tag */
#ifdef STM32_AES_HAL_V2
    hal_status = HAL_AES_GCM_GenerateAuthTAG(&ctx->hal_handle, tag, ST_HAL_AES_TIMEOUT);
#elif defined(STM32_AES_HAL_V1_L4)
    ctx->hal_handle.Init.GCMCMACPhase = CRYP_FINAL_PHASE;
    hal_status = HAL_CRYPEx_AES_Auth(&ctx->hal_handle, NULL,
                                     ctx->aead_config.current_message_size,
                                     (uint8_t *)tag, ST_HAL_AES_TIMEOUT);
#else
    hal_status = HAL_CRYPEx_AESGCM_GenerateAuthTAG(&ctx->hal_handle, tag, ST_HAL_AES_TIMEOUT);
#endif /* STM32_AES_HAL_V2 */
  }
  else
  {
    /* Generate CCM tag */
#ifdef STM32_AES_HAL_V2
    hal_status = HAL_AES_CCM_GenerateAuthTAG(&ctx->hal_handle, tag, ST_HAL_AES_TIMEOUT);
#elif defined(STM32_AES_HAL_V1_L4)
    ctx->hal_handle.Init.GCMCMACPhase = CRYP_FINAL_PHASE;
    hal_status = HAL_CRYPEx_AES_Auth(&ctx->hal_handle, NULL, 0, (uint8_t *)tag, ST_HAL_AES_TIMEOUT);
#else
    hal_status = HAL_CRYPEx_AESCCM_GenerateAuthTAG(&ctx->hal_handle, tag, ST_HAL_AES_TIMEOUT);
#endif /* STM32_AES_HAL_V2 */
  }

  if (hal_status != HAL_OK)
  {
    status = STM32_HAL_ERROR;
  }

  stm32_hal_aes_put_hal_hw();

  return status;
}

/*
 * Local helper to register an opration
 * If so, increment refcount and ensure HW is clocked.
 */
static STM32_HalStatusTypeDef stm32_aead_prepare_key(stm32_hal_aes_ctx_t *ctx,
                                                     const uint8_t *key, size_t key_size)
{
  STM32_HalStatusTypeDef status;

  status = stm32_hal_aes_key_size_id(key_size, NULL);
  if (status == STM32_HAL_SUCCESS)
  {
    ctx->key_byte_size = key_size;
#if defined(STM32_AES_HAL_V1_L4)
    memcpy(ctx->key, key, key_size);
#else
    /* Key data in big-endian format */
    read_u32_swapped(ctx->key, key, key_size);
#endif /* STM32_AES_HAL_V1_L4 */
  }

  return status;
}

/*
 * Local helper to unregister an opration context and release
 * related resources.
 */
static void stm32_aead_release_context(stm32_hal_aes_ctx_t *ctx)
{
  stm32_hal_aes_release_hal_hw(ctx);

  free(ctx->aead_config.aad_b1);
  memset(ctx, 0, sizeof(*ctx));
}

/*
 * Driver API functions exposed the PSA Crypto Drivers API
 */

STM32_HalStatusTypeDef STM32_HalAeadEncryptSetup(stm32_hal_aes_ctx_t *ctx,
                                                 const uint8_t *key_buffer,
                                                 size_t key_buffer_size,
                                                 STM32_HalAesAlgTypeDef alg,
                                                 size_t tag_length)
{
  STM32_HalStatusTypeDef status;

  status = stm32_hal_aead_set_algo_id(ctx, alg);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  status = stm32_hal_aead_set_tag_size(ctx, tag_length);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  status = stm32_aead_prepare_key(ctx, key_buffer, key_buffer_size);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  ctx->encrypt = true;

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadDecryptSetup(stm32_hal_aes_ctx_t *ctx,
                                                 const uint8_t *key_buffer,
                                                 size_t key_buffer_size,
                                                 STM32_HalAesAlgTypeDef alg,
                                                 size_t tag_length)
{
  STM32_HalStatusTypeDef status;

  status = stm32_hal_aead_set_algo_id(ctx, alg);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  status = stm32_hal_aead_set_tag_size(ctx, tag_length);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  status = stm32_aead_prepare_key(ctx, key_buffer, key_buffer_size);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  ctx->encrypt = false;

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadSetNonce(stm32_hal_aes_ctx_t *ctx,
                                             const uint8_t *nonce, size_t nonce_length)
{
  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_GCM:
    if (nonce_length != 12)
    {
      return STM32_HAL_ERROR_NOT_SUPPORTED;
    }

    ctx->aead_config.nonce_size = nonce_length;

#if defined(STM32_AES_HAL_V1_L4)
    /* Set Initialization vector (IV) in big-endian format, with counter = 2 */
    memcpy(ctx->iv, nonce, nonce_length);
    ctx->iv[3] = 0x02000000;
#else
    /* Set Initialization vector (IV) in little-endian, with counter = 2*/
    read_u32_swapped(ctx->iv, nonce, nonce_length);
    ctx->iv[3] = 0x00000002;
#endif /* STM32_AES_HAL_V1_L4 */
    break;

  case STM32_HAL_ALG_AES_CCM:
#if ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS
    if (!ctx->aead_config.message_size_set || !ctx->aead_config.aad_size_set)
    {
      return STM32_HAL_INVALID_ARGUMENT;
    }
#endif /* ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS */

    /* Nonce size constraints regarding q range */
    if ((nonce_length < 7) || (nonce_length > 13))
    {
      return STM32_HAL_INVALID_ARGUMENT;
    }

    /*
     * Save nonce in ct->iv[] fist bytes. It will be preprocess later to
     * generate CCM B0 data.
     */
    memcpy(ctx->iv, nonce, nonce_length);
    ctx->aead_config.nonce_size = nonce_length;
    break;

  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadSetLengths(stm32_hal_aes_ctx_t *ctx,
                                               size_t ad_length,
                                               size_t plaintext_length)
{
  /*
   * Nonce/IV shall not be set yet.
   * Can't change AAD size once additional data are received.
   */
  if ((ctx->aead_config.current_aad_size != 0) ||
      (ctx->aead_config.current_message_size != 0))
  {
    return STM32_HAL_BAD_STATE;
  }

  /*
   * PSA Crypto spec: this function can be called multiple times.
   * If so, discard previous config.
   */
  if (ctx->aead_config.aad_b1 != NULL)
  {
    free(ctx->aead_config.aad_b1);
    ctx->aead_config.aad_b1 = NULL;
    ctx->aead_config.b1_size = 0;
  }

  ctx->aead_config.message_size_set = true;
  ctx->aead_config.message_size = plaintext_length;
  ctx->aead_config.aad_size_set = true;
  ctx->aead_config.aad_size = ad_length;

  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_GCM:
    if (ad_length > 0)
    {
      ctx->aead_config.aad_b1 = calloc(1, ad_length);
      if (ctx->aead_config.aad_b1 == NULL)
      {
        return STM32_HAL_OUT_OF_MEMORY;
      }
    }

    ctx->aead_config.b1_size = ad_length;
    break;

  case STM32_HAL_ALG_AES_CCM:
#if ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS
    if (ctx->aead_config.nonce_size != 0)
    {
      return STM32_HAL_BAD_STATE;
    }
#endif /* ENFORCE_PSA_CRYPTO_CCM_NONCE_AFTER_LENGTHS */
    /* Maybe nonce size will be known later, prepare B0/B1 later */
    break;

  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadUpdateAd(stm32_hal_aes_ctx_t *ctx,
                                             const uint8_t *input, size_t input_length)
{
  STM32_HalStatusTypeDef status;
  uint8_t *aad_b1;

  if (input_length == 0)
  {
    return STM32_HAL_SUCCESS;
  }

  if (input == NULL)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  /* Protect from overlow */
  if ((ctx->aead_config.current_aad_size + input_length) < input_length)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_GCM:
    /*
     * GCM allows to not have the AAD size pre-defined with psa_aead_set_lengths().
     * In such cases, allow concatenating any added additional data.
     */
    if (ctx->aead_config.current_aad_size + input_length > ctx->aead_config.aad_size)
    {
      size_t aad_size;

      if (ctx->aead_config.aad_size_set)
      {
        return STM32_HAL_INVALID_ARGUMENT;
      }

      aad_size = ctx->aead_config.current_aad_size + input_length;
      aad_b1 = realloc(ctx->aead_config.aad_b1, aad_size);
      if (aad_b1 == NULL)
      {
        return STM32_HAL_OUT_OF_MEMORY;
      }

      /* Update AAD and B1 buffer sizes */
      ctx->aead_config.aad_size = aad_size;
      ctx->aead_config.b1_size = aad_size;
      ctx->aead_config.aad_b1 = (uint32_t *)aad_b1;
    }
    else
    {
      aad_b1 = (uint8_t *)ctx->aead_config.aad_b1;
    }
    break;

  case STM32_HAL_ALG_AES_CCM:
    /* CCM requires message and AAD sizes are defined */
    if (!ctx->aead_config.aad_size_set || !ctx->aead_config.message_size_set ||
        ((ctx->aead_config.current_aad_size + input_length) > ctx->aead_config.aad_size))
    {
      return STM32_HAL_INVALID_ARGUMENT;
    }

    if (ctx->aead_config.current_aad_size == 0)
    {
      /*
       * Now that nonce, message size and additional data size are known
       * prepare B0/B1 buffers before we store additional data in
       * B1 buffer.
       * */
      status = stm32_aead_hal_finalize_ccm_config(ctx);
      if (status != STM32_HAL_SUCCESS)
      {
        return status;
      }
    }

    aad_b1 = (uint8_t *)ctx->aead_config.aad_b1;

    /* Skip header bytes */
    if ((aad_b1[0] == 0xFF) && (aad_b1[1] == 0xFE))
    {
      aad_b1 += 6;
    }
    else
    {
      aad_b1 += 2;
    }
    break;

  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  memcpy(aad_b1 + ctx->aead_config.current_aad_size, input, input_length);

  ctx->aead_config.current_aad_size += input_length;

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadUpdate(stm32_hal_aes_ctx_t *ctx,
                                           const uint8_t *input, size_t input_length,
                                           uint8_t *output, size_t output_size,
                                           size_t *output_length)
{
  size_t remaining_input_size = input_length;
  size_t updated_output_size = 0;
  STM32_HalStatusTypeDef status;
  size_t proc_size;

  /* PSA Crypto specification: additional data are fed before ciphered data */
  if (ctx->aead_config.current_aad_size != ctx->aead_config.aad_size)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  /* Protect from overflow in sizes addition */
  if ((ctx->aead_config.current_message_size + ctx->sbuf_len + input_length) < input_length)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  /* PSA Crypto specification: if message size was set, it must not exceed */
  if (ctx->aead_config.message_size_set &&
      ((ctx->aead_config.current_message_size + ctx->sbuf_len + input_length) >
       ctx->aead_config.message_size))
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  /*
   * For consistency, expect output buffer is large enough to store all ciphered input data.
   * This is checked by some PSA tests from test_suite_psa_crypto.data.
   * This should be taken care from the generic TF PSA crypto driver framework.
   *
   * Below, when generating the output bytes, we check again the output buffer size
   * in case some input data were previosuly stored in ctx->sbuf[] and would be output
   * now.
   */
  if (output_size < input_length)
  {
    return STM32_HAL_BUFFER_TOO_SMALL;
  }

  /*
   * If not enough data to process a block yet, store data in ctx->sbuf,
   * we will processed later.
   */
  if (input_length < (STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len))
  {
    memcpy((uint8_t *)ctx->sbuf + ctx->sbuf_len, input, input_length);
    ctx->sbuf_len += input_length;

#if ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES == 0
    *output_length = 0;

    return STM32_HAL_SUCCESS;
#else
    if ((ctx->aead_config.current_message_size + ctx->sbuf_len) ==
        ctx->aead_config.message_size)
    {
      /* Don't return now, have these last byte processed. */
      remaining_input_size = 0;
    }
    else
    {
      *output_length = 0;

      return STM32_HAL_SUCCESS;
    }
#endif /* ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES */
  }

  /*
   * Process data:
   * - first a full block made of the previously saved data and input data first bytes
   * - then each available full blocks from input data
   * - last, save trailling input data byte for later processing
   *   Possibly process them if last message bytes.
   *
   * Note: only call stm32_aead_process_buffer() if there are data to
   * be processed. Finish and Veerify sequence will take care of informing
   * the HAL when the message is empty.
   */

  if ((ctx->sbuf_len + remaining_input_size >= STM32_CIPHER_BLOCK_SIZE))
  {
    /* Fill context buffer until STM32_CIPHER_BLOCK_SIZE bytes, and process it */
    memcpy((uint8_t *)ctx->sbuf + ctx->sbuf_len, input, STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len);
    remaining_input_size -= STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len;
    input += STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len;
    ctx->sbuf_len = 0;

    if (output_size < STM32_CIPHER_BLOCK_SIZE)
    {
      return STM32_HAL_BUFFER_TOO_SMALL;
    }

    status = stm32_aead_process_buffer(ctx, ctx->sbuf, output, STM32_CIPHER_BLOCK_SIZE);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    updated_output_size += STM32_CIPHER_BLOCK_SIZE;
    output += STM32_CIPHER_BLOCK_SIZE;
  }

  proc_size = (remaining_input_size / STM32_CIPHER_BLOCK_SIZE) * STM32_CIPHER_BLOCK_SIZE;

  if ((output_size - updated_output_size) < proc_size)
  {
    return STM32_HAL_BUFFER_TOO_SMALL;
  }

  if (proc_size != 0)
  {
    status = stm32_aead_process_buffer(ctx, input, output, proc_size);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    remaining_input_size -= proc_size;
    updated_output_size += proc_size;
    input += proc_size;
    output += proc_size;
  }

  if (remaining_input_size != 0)
  {
    memcpy(ctx->sbuf, input, remaining_input_size);
    ctx->sbuf_len = remaining_input_size;
  }

#if ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES != 3
  /* Process now the last bytes if the output buffer is large enough */
  if ((ctx->sbuf_len != 0) &&
      ((output_size - updated_output_size) >= ctx->sbuf_len) &&
      ((ctx->aead_config.current_message_size + ctx->sbuf_len) ==
       ctx->aead_config.message_size))
  {
    /* Use local full block buffers to prevent HAL to overflow caller buffers */
    uint32_t temp_out[STM32_CIPHER_BLOCK_SIZE / sizeof(uint32_t)];

    memset(ctx->sbuf + ctx->sbuf_len, 0, sizeof(ctx->sbuf) - ctx->sbuf_len);

    status = stm32_aead_process_buffer(ctx, ctx->sbuf, (uint8_t *)temp_out, ctx->sbuf_len);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    memcpy(output, temp_out, ctx->sbuf_len);
    updated_output_size += ctx->sbuf_len;
    ctx->sbuf_len = 0;
  }
#endif /* ENFORCE_PSA_CRYPTO_AEAD_UPDATE_OUTPUT_LAST_BYTES */

  *output_length = updated_output_size;

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadFinish(stm32_hal_aes_ctx_t *ctx,
                                           uint8_t *ciphertext, size_t ciphertext_size,
                                           size_t *ciphertext_length,
                                           uint8_t *tag, size_t tag_size,
                                           size_t *tag_length)
{
  uint32_t local_tag[STM32_CIPHER_BLOCK_SIZE / sizeof(uint32_t)];
  STM32_HalStatusTypeDef status;

  if (tag_size < ctx->aead_config.tag_size)
  {
      return STM32_HAL_BUFFER_TOO_SMALL;
  }

  /* PSA Crypto specification: additional data are fed before ciphered data */
  if (ctx->aead_config.current_aad_size != ctx->aead_config.aad_size)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  /* PSA Crypto specification: if message size was set, it must match */
  if (ctx->aead_config.message_size_set &&
      (ctx->aead_config.current_message_size + ctx->sbuf_len != ctx->aead_config.message_size))
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  if ((tag == NULL) || (tag_length == NULL))
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  if (ctx->sbuf_len != 0)
  {
    if (ciphertext_size < ctx->sbuf_len)
    {
      return STM32_HAL_BUFFER_TOO_SMALL;
    }
    if (ciphertext == NULL)
    {
      return STM32_HAL_INVALID_ARGUMENT;
    }
  }

  /* Process last bytes if any */
  if (ctx->sbuf_len != 0)
  {
    /* Use local full block buffers to prevent HAL to overflow caller buffers */
    uint32_t temp_out[STM32_CIPHER_BLOCK_SIZE / sizeof(uint32_t)];

    memset(ctx->sbuf + ctx->sbuf_len, 0, sizeof(ctx->sbuf) - ctx->sbuf_len);

    status = stm32_aead_process_buffer(ctx, ctx->sbuf, (uint8_t *)temp_out, ctx->sbuf_len);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    memcpy(ciphertext, temp_out, ctx->sbuf_len);
  }

  *ciphertext_length = ctx->sbuf_len;

  /* Generate tag */
  status = stm32_aead_generate_tag(ctx, local_tag);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  *tag_length = ctx->aead_config.tag_size;
  memcpy(tag, local_tag, ctx->aead_config.tag_size);

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadVerify(stm32_hal_aes_ctx_t *ctx,
                                           uint8_t *plaintext, size_t plaintext_size,
                                           size_t *plaintext_length,
                                           const uint8_t *tag, size_t tag_length)
{
  uint32_t local_tag[STM32_CIPHER_BLOCK_SIZE / sizeof(uint32_t)];
  STM32_HalStatusTypeDef status;

  /* PSA Crypto specification: additional data are fed before ciphered data */
  if (ctx->aead_config.current_aad_size != ctx->aead_config.aad_size)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  /* PSA Crypto specification: if message size was set, it must match */
  if (ctx->aead_config.message_size_set &&
      ((ctx->aead_config.current_message_size + ctx->sbuf_len) != ctx->aead_config.message_size))
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  if (ctx->sbuf_len != 0)
  {
    if (plaintext_size < ctx->sbuf_len)
    {
      return STM32_HAL_BUFFER_TOO_SMALL;
    }
    if (plaintext == NULL)
    {
      return STM32_HAL_INVALID_ARGUMENT;
    }
  }

  if (tag_length != ctx->aead_config.tag_size)
  {
    return STM32_HAL_INVALID_SIGNATURE;
  }

  /* Process last bytes if any */
  if (ctx->sbuf_len != 0)
  {
    /* Use local full block buffers to prevent HAL to overflow caller buffers */
    uint32_t temp_out[STM32_CIPHER_BLOCK_SIZE / sizeof(uint32_t)];

    memset(ctx->sbuf + ctx->sbuf_len, 0, sizeof(ctx->sbuf) - ctx->sbuf_len);

    status = stm32_aead_process_buffer(ctx, ctx->sbuf, (uint8_t *)temp_out, ctx->sbuf_len);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    memcpy(plaintext, temp_out, ctx->sbuf_len);
  }

  *plaintext_length = ctx->sbuf_len;

  /* Generate and check tag */
  status = stm32_aead_generate_tag(ctx, local_tag);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  if (mbedtls_ct_memcmp(tag, local_tag, tag_length) != 0)
  {
    return STM32_HAL_INVALID_SIGNATURE;
  }

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAeadAbort(stm32_hal_aes_ctx_t *ctx)
{
  stm32_aead_release_context(ctx);

  return STM32_HAL_SUCCESS;
}

STM32_HalStatusTypeDef STM32_HalAesAeadEncrypt(
  STM32_HalAesAlgTypeDef alg,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data, size_t additional_data_length,
  const uint8_t *p_plaintext, size_t plaintext_length,
  uint8_t *p_ciphertext, size_t ciphertext_size, size_t *p_ciphertext_length,
  size_t tag_length)
{
  STM32_HalStatusTypeDef status = STM32_HAL_ERROR;
  stm32_hal_aes_ctx_t ctx = {0};
  size_t cipher_length1;
  size_t cipher_length2;
  size_t tag_length_out;

  status = STM32_HalAeadEncryptSetup(&ctx, p_key_buffer, key_buffer_size, alg, tag_length);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  /*
   * Passed this point, we must release the context resource (its refcount)
   * before exiting, e.g. with stm32_aead_release_context().
   */

  /* Sanitize the input lengths */
  if ((plaintext_length + tag_length) < plaintext_length)
  {
    status = STM32_HAL_INVALID_ARGUMENT;
    goto exit;
  }

  if (ciphertext_size < (plaintext_length + tag_length))
  {
    status = STM32_HAL_BUFFER_TOO_SMALL;
    goto exit;
  }

  status = STM32_HalAeadSetLengths(&ctx, additional_data_length, plaintext_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = STM32_HalAeadSetNonce(&ctx, p_nonce, nonce_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = STM32_HalAeadUpdateAd(&ctx, p_additional_data, additional_data_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = STM32_HalAeadUpdate(&ctx, p_plaintext, plaintext_length,
                               p_ciphertext, ciphertext_size, &cipher_length1);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = STM32_HalAeadFinish(&ctx, p_ciphertext + cipher_length1,
                               ciphertext_size - cipher_length1, &cipher_length2,
                               p_ciphertext + plaintext_length, tag_length, &tag_length_out);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  if ((cipher_length1 + cipher_length2 != plaintext_length) || (tag_length_out != tag_length))
  {
    status = STM32_HAL_ERROR;
    goto exit;
  }

  *p_ciphertext_length = plaintext_length + tag_length;

  status = STM32_HAL_SUCCESS;

exit:
  stm32_aead_release_context(&ctx);

  return status;
}

STM32_HalStatusTypeDef STM32_HalAesAeadDecrypt(
  STM32_HalAesAlgTypeDef alg,
  const uint8_t *p_key_buffer, size_t key_buffer_size,
  const uint8_t *p_nonce, size_t nonce_length,
  const uint8_t *p_additional_data,
  size_t additional_data_length,
  const uint8_t *p_ciphertext, size_t ciphertext_length,
  uint8_t *p_plaintext, size_t plaintext_size, size_t *p_plaintext_length,
  size_t tag_length)
{
  STM32_HalStatusTypeDef status = STM32_HAL_ERROR;
  stm32_hal_aes_ctx_t ctx = {0};
  size_t plaintext_length1;
  size_t plaintext_length2;
  size_t cipher_length;

  ctx.encrypt = false;
  status = STM32_HalAeadDecryptSetup(&ctx, p_key_buffer, key_buffer_size, alg, tag_length);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  /*
   * Passed this point, we must release the context resource (its refcount)
   * before exiting, e.g. with stm32_aead_release_context().
   */

  /* Sanitize the input lengths */
  if (ciphertext_length < tag_length)
  {
    status = STM32_HAL_INVALID_ARGUMENT;
    goto exit;
  }

  cipher_length = ciphertext_length - tag_length;

  if (plaintext_size < cipher_length)
  {
    status = STM32_HAL_BUFFER_TOO_SMALL;
    goto exit;
  }

  if ((cipher_length == 0) && (ctx.algo_id == STM32_HAL_ALG_AES_CCM))
  {
    status = STM32_HAL_INVALID_SIGNATURE;
    goto exit;
  }

  status = STM32_HalAeadSetLengths(&ctx, additional_data_length, cipher_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = STM32_HalAeadSetNonce(&ctx, p_nonce, nonce_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = STM32_HalAeadUpdateAd(&ctx, p_additional_data, additional_data_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  status = STM32_HalAeadUpdate(&ctx, p_ciphertext, cipher_length,
                               p_plaintext, plaintext_size, &plaintext_length1);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  /* Generate and check tag */
  status = STM32_HalAeadVerify(&ctx, p_plaintext + plaintext_length1,
                               plaintext_size - plaintext_length1, &plaintext_length2,
                               p_ciphertext + cipher_length, tag_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto exit;
  }

  if ((plaintext_length1 + plaintext_length2) != cipher_length)
  {
    status = STM32_HAL_ERROR;
    goto exit;
  }

  *p_plaintext_length = cipher_length;

  status = STM32_HAL_SUCCESS;

exit:
  stm32_aead_release_context(&ctx);

  return status;
}

#endif /* STM32_HAL_AES_AEAD_DRIVER_ENABLED */
