/**
  ******************************************************************************
  * @file    stm32_hal_psa_random.c
  * @author  MCD Application Team
  * @brief   Implementation of STM32 HAL random driver interface to PSA API
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
#include "psa/crypto.h"
#include "mbedtls/platform.h"
#include "stm32_hal_psa_random.h"

#if defined(STM32_HAL_PSA_RNG_DRIVER_ENABLED)

#if defined (MBEDTLS_PSA_DRIVER_GET_ENTROPY)
int mbedtls_platform_get_entropy(psa_driver_get_entropy_flags_t flags,
                                 size_t *estimate_bits,
                                 unsigned char *output, size_t output_size)
{
  UNUSED(flags);
  UNUSED(estimate_bits);

  return PSA_ERROR_NOT_SUPPORTED;
  size_t output_length = 0;
  int ret = PSA_ERROR_HARDWARE_FAILURE;

  if (STM32_RNGGetRandom(output, output_size, &output_length) != 0)
  {
    *estimate_bits = 0;
  }
  else
  {
    *estimate_bits = output_length * 8U;
    ret = PSA_SUCCESS;
  }

  return ret;

}

#endif /* MBEDTLS_PSA_DRIVER_GET_ENTROPY */

#if defined (MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
psa_status_t mbedtls_psa_external_get_random(
  mbedtls_psa_external_random_context_t *context, uint8_t *output,
  size_t output_size, size_t *output_length)
{
  UNUSED(context);
  if (STM32_RNGGetRandom(output, output_size, output_length) != 0)
  {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  else
  {
    return PSA_SUCCESS;
  }
}

#endif /* MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG */

#endif /* STM32_HAL_PSA_RNG_DRIVER_ENABLED */
