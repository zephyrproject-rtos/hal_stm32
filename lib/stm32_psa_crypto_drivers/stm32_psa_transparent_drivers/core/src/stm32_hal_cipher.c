/**
  ******************************************************************************
  * @file    stm32_hal_cipher.c
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

#include "stm32_hal_aes.h"
#include "stm32_hal_aes_private.h"
#include "stm32_hal_cipher.h"
#include "stm32_hal_core_config.h"
#include "stm32_hal_private.h"
#include "stm32_soc_hal.h"

#include <psa/crypto_sizes.h>

#include <string.h>
#include <stdlib.h>

#ifdef STM32_HAL_AES_CIPHER_DRIVER_ENABLED

static STM32_HalStatusTypeDef stm32_hal_cipher_set_algo_id(stm32_hal_aes_ctx_t *ctx,
                                                           STM32_HalAesAlgTypeDef alg)
{
#ifdef STM32_AES_HAL_V2
  /* HALv2 may be configured with a reduced set of supported algorithms */
  switch (alg)
  {
 #if !defined(USE_HAL_AES_ECB_CBC_ALGO) || (USE_HAL_AES_ECB_CBC_ALGO != 1)
  case STM32_HAL_ALG_AES_ECB:
  case STM32_HAL_ALG_AES_CBC:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
 #endif
 #if !defined(USE_HAL_AES_CTR_ALGO) || (USE_HAL_AES_CTR_ALGO != 1)
  case STM32_HAL_ALG_AES_CTR:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
 #endif
  default:
    break;
  }
#endif /* STM32_AES_HAL_V2 */

  switch (alg)
  {
  case STM32_HAL_ALG_AES_ECB:
  case STM32_HAL_ALG_AES_CBC:
  case STM32_HAL_ALG_AES_CTR:
    break;
  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }

  ctx->algo_id = alg;

  return STM32_HAL_SUCCESS;
}

static STM32_HalStatusTypeDef stm32_aes_cipher_hal_configure(stm32_hal_aes_ctx_t *ctx)
{
  uint32_t hal_key_size_id;
  STM32_HalStatusTypeDef status;
#if defined(STM32_AES_HAL_V2)
  hal_status_t hal_status;
#endif
#if !defined(STM32_AES_HAL_V2) && !defined(STM32_AES_HAL_V1_L4)
  CRYP_ConfigTypeDef conf;
#endif /* STM32_AES_HAL_V2 */

  (void)memset(&ctx->hal_handle, 0, sizeof(ctx->hal_handle));

  status = STM32_HalAesInit(ctx);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  status = stm32_hal_aes_key_size_id(ctx->key_byte_size, &hal_key_size_id);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

#ifdef STM32_AES_HAL_V2
  if (HAL_AES_SetNormalKey(&ctx->hal_handle, hal_key_size_id, ctx->key) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  /* HALv2 does not expose algorithm IDs, hence use the PSA Crypto IDs */
  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_ECB:
    hal_status = HAL_AES_ECB_SetConfig(&ctx->hal_handle);
    break;
  case STM32_HAL_ALG_AES_CBC:
    hal_status = HAL_AES_CBC_SetConfig(&ctx->hal_handle, ctx->iv);
    break;
  case STM32_HAL_ALG_AES_CTR:
    hal_status = HAL_AES_CTR_SetConfig(&ctx->hal_handle, ctx->iv);
    break;
  default:
    return STM32_HAL_ERROR_NOT_SUPPORTED;
  }
  if (hal_status != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  if (HAL_AES_SetDataSwapping(&ctx->hal_handle, HAL_AES_DATA_SWAPPING_BYTE) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

#elif defined(STM32_AES_HAL_V1_L4)
  if (HAL_CRYP_DeInit(&ctx->hal_handle))
  {
    return STM32_HAL_ERROR;
  }

  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_ECB:
    ctx->hal_handle.Init.ChainingMode = CRYP_CHAINMODE_AES_ECB;
    break;
  case STM32_HAL_ALG_AES_CBC:
    ctx->hal_handle.Init.ChainingMode = CRYP_CHAINMODE_AES_CBC;
    ctx->hal_handle.Init.pInitVect = (uint8_t *)ctx->iv;
    break;
  case STM32_HAL_ALG_AES_CTR:
    ctx->hal_handle.Init.ChainingMode = CRYP_CHAINMODE_AES_CTR;
    ctx->hal_handle.Init.pInitVect = (uint8_t *)ctx->iv;
    break;
  default:
    break;
  }

  if (ctx->encrypt)
  {
    ctx->hal_handle.Init.OperatingMode = CRYP_ALGOMODE_ENCRYPT;
  }
  else if (ctx->algo_id == STM32_HAL_ALG_AES_CTR)
  {
    ctx->hal_handle.Init.OperatingMode = CRYP_ALGOMODE_DECRYPT;
  }
  else
  {
    ctx->hal_handle.Init.OperatingMode = CRYP_ALGOMODE_KEYDERIVATION_DECRYPT;
  }

  ctx->hal_handle.Init.pKey = (uint8_t *)ctx->key;
  ctx->hal_handle.Init.KeySize = hal_key_size_id;

  ctx->hal_handle.Init.KeyWriteFlag = CRYP_KEY_WRITE_ENABLE;
  ctx->hal_handle.Init.DataType = CRYP_DATATYPE_8B;

  if (HAL_CRYP_Init(&ctx->hal_handle) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }
#else /* STM32_AES_HAL_V2 */
  if (HAL_CRYP_GetConfig(&ctx->hal_handle, &conf) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  conf.pKey = ctx->key;
  conf.KeySize = hal_key_size_id;

  switch (ctx->algo_id)
  {
  case STM32_HAL_ALG_AES_ECB:
    conf.Algorithm = CRYP_AES_ECB;
    break;
  case STM32_HAL_ALG_AES_CBC:
  case STM32_HAL_ALG_AES_CTR:
    conf.Algorithm = (ctx->algo_id == STM32_HAL_ALG_AES_CBC) ?
      CRYP_AES_CBC : CRYP_AES_CTR;
    conf.pInitVect = ctx->iv;
 #ifdef CRYP_IVCONFIG_ONCE
    conf.KeyIVConfigSkip = CRYP_IVCONFIG_ONCE;
 #else
    conf.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ONCE;
 #endif /* CRYP_IVCONFIG_ONCE */
    break;
  default:
    break;
  }

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

  if (HAL_CRYP_SetConfig(&ctx->hal_handle, &conf) != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

#endif /* STM32_AES_HAL_V2 */

  return STM32_HAL_SUCCESS;
}

static STM32_HalStatusTypeDef process_buffer(stm32_hal_aes_ctx_t *ctx,
                                             const uint8_t *input,
                                             uint8_t *output,
                                             size_t length)
{
  stm32_hal_status_t hal_status;
  STM32_HalStatusTypeDef status;

  status = stm32_hal_aes_get_hal_hw(ctx, stm32_aes_cipher_hal_configure);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

#if defined(STM32_AES_HAL_V2)
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
  hal_status = HAL_CRYPEx_AES(&ctx->hal_handle, (uint8_t *)input, length, output,
                              ST_HAL_AES_TIMEOUT);
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

  stm32_hal_aes_put_hal_hw();

  if (hal_status != HAL_OK)
  {
    return STM32_HAL_ERROR;
  }

  return STM32_HAL_SUCCESS;
}

/*
 * Local helper to register an opration
 * If so, increment refcount and ensure HW is clocked.
 */
static STM32_HalStatusTypeDef stm32_cipher_register_context(stm32_hal_aes_ctx_t *ctx,
                                                            const uint8_t *key,
                                                            size_t key_size,
                                                            STM32_HalAesAlgTypeDef alg)
{
  STM32_HalStatusTypeDef status;

  status = stm32_hal_cipher_set_algo_id(ctx, alg);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  status = stm32_hal_aes_key_size_id(key_size, NULL);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  ctx->key_byte_size = key_size;
#if defined(STM32_AES_HAL_V1_L4)
  memcpy(ctx->key, key, key_size);
#else
  /* Key key data in big-endian format */
  read_u32_swapped(ctx->key, key, key_size);
#endif /* STM32_AES_HAL_V1_L4 */

  return STM32_HAL_SUCCESS;
}

/*
 * Local helper to unregister an opration context and release
 * related resources.
 */
static void stm32_cipher_release_context(stm32_hal_aes_ctx_t *ctx)
{
  stm32_hal_aes_release_hal_hw(ctx);

  memset(ctx, 0, sizeof(*ctx));
}

/*
 * Hanlder functions exposed the PSA Crypto Driver wrapper layer
 */

/* PSA Crypto Driver handler for cipher_encrypt_setup() */
STM32_HalStatusTypeDef STM32_HalCipherEncryptSetup(stm32_hal_aes_ctx_t *ctx,
                                                   const uint8_t *key_buffer, size_t key_buffer_size,
                                                   STM32_HalAesAlgTypeDef alg)
{
  ctx->encrypt = true;

  return stm32_cipher_register_context(ctx, key_buffer, key_buffer_size, alg);
}

/* PSA Crypto Driver handler for cipher_decrypt_setup() */
STM32_HalStatusTypeDef STM32_HalCipherDecryptSetup(stm32_hal_aes_ctx_t *ctx,
                                                   const uint8_t *key_buffer, size_t key_buffer_size,
                                                   STM32_HalAesAlgTypeDef alg)
{
  ctx->encrypt = false;

  return stm32_cipher_register_context(ctx, key_buffer, key_buffer_size, alg);
}

/* PSA Crypto Driver handler for cipher_seet_iv() */
STM32_HalStatusTypeDef STM32_HalCipherSetIV(stm32_hal_aes_ctx_t *ctx,
                                            const uint8_t *iv, size_t iv_length)
{
  if (iv == NULL)
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  switch (ctx->algo_id)
  {
    case STM32_HAL_ALG_AES_CBC:
    case STM32_HAL_ALG_AES_CTR:
      break;
    default:
      return STM32_HAL_INVALID_ARGUMENT;
  }

  if (iv_length != sizeof(ctx->iv))
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

#if defined(STM32_AES_HAL_V1_L4)
  memcpy(ctx->iv, iv, iv_length);
#else
  /* Set Initialization vector (IV) in big-endian format */
  read_u32_swapped(ctx->iv, iv, iv_length);
#endif /* STM32_AES_HAL_V1_L4 */

  return STM32_HAL_SUCCESS;
}

/* PSA Crypto Driver handler for cipher_update() */
STM32_HalStatusTypeDef STM32_HalCipherUpdate(stm32_hal_aes_ctx_t *ctx,
                                             const uint8_t *input, size_t input_length,
                                             uint8_t *output, size_t output_size,
                                             size_t *output_length )
{
  size_t remaining_input_size = input_length;
  size_t updated_output_size = 0;
  size_t proc_size;
  STM32_HalStatusTypeDef status;

  /* On non-CTR, Output buffer should at least the size of both the pending and new input data */

  if ((output_size < input_length) ||
      ((ctx->algo_id != STM32_HAL_ALG_AES_CTR) && (output_size < (input_length + ctx->sbuf_len))))
  {
    return STM32_HAL_BUFFER_TOO_SMALL;
  }

  if (input_length == 0)
  {
    *output_length = 0;
    return STM32_HAL_SUCCESS;
  }

  if (ctx->algo_id == STM32_HAL_ALG_AES_CTR)
  {
    /* Consume available masks */
    if (ctx->sbuf_len != 0)
    {
      size_t n;

      proc_size = ctx->sbuf_len;
      if (proc_size > remaining_input_size)
      {
        proc_size = remaining_input_size;
      }

      for (n = 0; n < proc_size; n++)
      {
        output[n] = input[n] ^ ctx->sbuf[n];
      }
      input += proc_size;
      output += proc_size;
      updated_output_size += proc_size;
      remaining_input_size -= proc_size;
      ctx->sbuf_len -= proc_size;

      if (remaining_input_size == 0)
      {
        memmove(ctx->sbuf, ctx->sbuf + proc_size, ctx->sbuf_len);
        *output_length = updated_output_size;
        return STM32_HAL_SUCCESS;
      }
    }
  }
  else
  {
    /*
     * STM32 AES operates on full block size: accumulate input bytes until a
     * block is filled. Unfilled block can obnly be proceed from
     * psa_cipher_finish(), see STM32_HalCipherFinish().
     */
    if (input_length < (STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len))
    {
      memcpy((uint8_t *)ctx->sbuf + ctx->sbuf_len, input, input_length);
      ctx->sbuf_len += input_length;
      *output_length = 0;

      return STM32_HAL_SUCCESS;
    }
  }

  if ((ctx->sbuf_len != 0) && (ctx->algo_id != STM32_HAL_ALG_AES_CTR))
  {
    /* Fill context buffer until STM32_CIPHER_BLOCK_SIZE bytes, and process it */
    memcpy((uint8_t *)ctx->sbuf + ctx->sbuf_len, input, STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len);
    remaining_input_size -= STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len;
    input += STM32_CIPHER_BLOCK_SIZE - ctx->sbuf_len;
    ctx->sbuf_len = 0;

    status = process_buffer(ctx, ctx->sbuf, output, STM32_CIPHER_BLOCK_SIZE);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    updated_output_size += STM32_CIPHER_BLOCK_SIZE;
    output += STM32_CIPHER_BLOCK_SIZE;
  }

  /* Process the next blocks */
  proc_size = (remaining_input_size / STM32_CIPHER_BLOCK_SIZE) * STM32_CIPHER_BLOCK_SIZE;

  if (proc_size != 0)
  {
    status = process_buffer(ctx, input, output, proc_size);
    if (status != STM32_HAL_SUCCESS)
    {
      return status;
    }

    remaining_input_size -= proc_size;
    updated_output_size += proc_size;
    input += proc_size;
    output += proc_size;
  }

  /* Save trailing input data to feed a full block */
  if (remaining_input_size != 0)
  {
    memcpy(ctx->sbuf, input, remaining_input_size);
    memset(ctx->sbuf + remaining_input_size, 0, STM32_CIPHER_BLOCK_SIZE - remaining_input_size);

    if (ctx->algo_id == STM32_HAL_ALG_AES_CTR)
    {
      uint8_t temp_out[STM32_CIPHER_BLOCK_SIZE];

      status = process_buffer(ctx, ctx->sbuf, temp_out, STM32_CIPHER_BLOCK_SIZE);
      if (status != STM32_HAL_SUCCESS)
      {
        return status;
      }

      memcpy(output, temp_out, remaining_input_size);
      updated_output_size += remaining_input_size;

      /* Save unconsumed masks for the next input data */
      ctx->sbuf_len = STM32_CIPHER_BLOCK_SIZE - remaining_input_size;
      memcpy(ctx->sbuf, temp_out + remaining_input_size, ctx->sbuf_len);
    }
    else
    {
      ctx->sbuf_len = remaining_input_size;
    }
  }

  *output_length = updated_output_size;

  return STM32_HAL_SUCCESS;
}

/* PSA Crypto Driver handler for cipher_finish() */
STM32_HalStatusTypeDef STM32_HalCipherFinish(stm32_hal_aes_ctx_t *ctx,
                                             uint8_t *output, size_t output_size,
                                             size_t *output_length)
{
  if ((ctx->algo_id != STM32_HAL_ALG_AES_CTR) && (ctx->sbuf_len != 0))
  {
    return STM32_HAL_INVALID_ARGUMENT;
  }

  *output_length = 0;
  ctx->sbuf_len = 0;

  return STM32_HAL_SUCCESS;
}

/* PSA Crypto Driver handler for cipher_abort() */
STM32_HalStatusTypeDef STM32_HalCipherAbort(stm32_hal_aes_ctx_t *ctx)
{
  stm32_cipher_release_context(ctx);

  return STM32_HAL_SUCCESS;
}

/* PSA Crypto Driver handler for cipher_encrypt() */
STM32_HalStatusTypeDef STM32_HalAesEncrypt(STM32_HalAesAlgTypeDef alg,
                                           const uint8_t *p_key_buffer,
                                           size_t key_buffer_size,
                                           const uint8_t *p_iv, size_t iv_length,
                                           const uint8_t *p_plaintext, size_t plaintext_length,
                                           uint8_t *p_ciphertext, size_t ciphertext_size,
                                           size_t *p_ciphertext_length)
{
  stm32_hal_aes_ctx_t ctx = {0};
  STM32_HalStatusTypeDef status;
  size_t out_len;

  status = STM32_HalCipherEncryptSetup(&ctx, p_key_buffer, key_buffer_size, alg);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  if (plaintext_length == 0)
  {
    *p_ciphertext_length = 0;
    status = STM32_HAL_SUCCESS;
    goto cleanup;
  }

  /* Supported ECB, CBC and CTR expect block aligned input data */
  if ((alg != STM32_HAL_ALG_AES_CTR) && ((plaintext_length % STM32_CIPHER_BLOCK_SIZE) != 0))
  {
    status = STM32_HAL_INVALID_ARGUMENT;
    goto cleanup;
  }

  if ((alg == STM32_HAL_ALG_AES_CBC) || (alg == STM32_HAL_ALG_AES_CTR))
  {
    status = STM32_HalCipherSetIV(&ctx, p_iv, iv_length);
    if (status != STM32_HAL_SUCCESS)
    {
      goto cleanup;
    }
  }

  status = STM32_HalCipherUpdate(&ctx, p_plaintext, plaintext_length,
                                 p_ciphertext, ciphertext_size,
                                 p_ciphertext_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto cleanup;
  }

  status = STM32_HalCipherFinish(&ctx, p_ciphertext, 0, &out_len);
  if (status != STM32_HAL_SUCCESS)
  {
    goto cleanup;
  }
  if (out_len != 0)
  {
    status = STM32_HAL_ERROR;
  }

cleanup:
  stm32_cipher_release_context(&ctx);

  return status;
}

/*
 * PSA Crypto Driver handler for cipher_decrypt()
 * For CBC and CTR, IV is located at the begining of the input data buffer.
 */
STM32_HalStatusTypeDef STM32_HalAesDecrypt(STM32_HalAesAlgTypeDef alg,
                                           const uint8_t *p_key_buffer, size_t key_buffer_size,
                                           const uint8_t *p_ciphertext, size_t ciphertext_length,
                                           uint8_t *p_plaintext, size_t plaintext_size,
                                           size_t *p_plaintext_length)
{
  size_t input_size = ciphertext_length;
  const uint8_t *input = p_ciphertext;
  stm32_hal_aes_ctx_t ctx = {0};
  STM32_HalStatusTypeDef status;
  size_t out_len;

  status = STM32_HalCipherDecryptSetup(&ctx, p_key_buffer, key_buffer_size, alg);
  if (status != STM32_HAL_SUCCESS)
  {
    return status;
  }

  /* Supported ECB, CBC and CTR expect block aligned intpu data */
  if ((alg != STM32_HAL_ALG_AES_CTR) && ((ciphertext_length % STM32_CIPHER_BLOCK_SIZE) != 0))
  {
    status = STM32_HAL_INVALID_ARGUMENT;
    goto cleanup;
  }

  if ((alg == STM32_HAL_ALG_AES_CBC) || (alg == STM32_HAL_ALG_AES_CTR))
  {
    if (ciphertext_length <= STM32_CIPHER_BLOCK_SIZE)
    {
      status = STM32_HAL_INVALID_ARGUMENT;
      goto cleanup;
    }

    status = STM32_HalCipherSetIV(&ctx, p_ciphertext, STM32_CIPHER_BLOCK_SIZE);
    if (status != STM32_HAL_SUCCESS)
    {
      goto cleanup;
    }

    input_size -= STM32_CIPHER_BLOCK_SIZE;
    input += STM32_CIPHER_BLOCK_SIZE;
  }

  if (ciphertext_length == 0)
  {
    *p_plaintext_length = 0;
    status = STM32_HAL_SUCCESS;
    goto cleanup;
  }

  status = STM32_HalCipherUpdate(&ctx, input, input_size, p_plaintext, plaintext_size,
                                 p_plaintext_length);
  if (status != STM32_HAL_SUCCESS)
  {
    goto cleanup;
  }

  status = STM32_HalCipherFinish(&ctx, p_plaintext, 0, &out_len);
  if (status != STM32_HAL_SUCCESS)
  {
    goto cleanup;
  }
  if (out_len != 0)
  {
    status = STM32_HAL_ERROR;
  }

cleanup:
  stm32_cipher_release_context(&ctx);

  return status;
}

#endif /* STM32_HAL_AES_CIPHER_DRIVER_ENABLED */
