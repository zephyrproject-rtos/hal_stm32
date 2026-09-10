/**
  ******************************************************************************
  * @file    stm32_hal_rng.c
  * @author  MCD Application Team
  * @brief   Implementation of STM32 hardware RNG core module
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
#include <psa/crypto_values.h>

#include "stm32_hal_rng.h"
#include "stm32_soc_hal.h"

#if defined(STM32_HAL_RNG_DRIVER_ENABLED)
static RNG_HandleTypeDef handle;
static uint8_t users = 0U;
uint8_t init_ctx = 0U;

#define COMPILER_BARRIER() __ASM __IO("" : : : "memory")

static uint8_t atomic_incr_u8(__IO uint8_t *valuePtr, uint8_t delta)
{
  COMPILER_BARRIER();
  uint8_t newValue;
  do
  {
    newValue = __LDREXB(valuePtr) + delta;
  } while (__STREXB(newValue, valuePtr));
  COMPILER_BARRIER();
  return newValue;
}

static psa_status_t RNG_DeInit(void)
{
  /*Disable the RNG peripheral */
  if (HAL_RNG_DeInit(&handle) != HAL_OK)
  {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  /* RNG Peripheral clock disable - assume we're the only users of RNG  */
  __HAL_RCC_RNG_CLK_DISABLE();

  users = 0;

  return PSA_SUCCESS;
}

static psa_status_t RNG_Init(void)
{
  psa_status_t status = PSA_ERROR_HARDWARE_FAILURE;
  uint32_t dummy;
  RNG_ConfigTypeDef rng_conf;

  /*  We're only supporting a single user of RNG */
  if (atomic_incr_u8(&users, 1U) > 1U)
  {
    return status;
  }

  /* Select RNG clock source */
  __HAL_RCC_RNG_CONFIG(RNGCLKSOURCE_HSI);

  /* RNG Peripheral clock enable */
  __HAL_RCC_RNG_CLK_ENABLE();

  /* Initialize RNG instance */
  handle.Instance = RNG;
  handle.State = HAL_RNG_STATE_RESET;
  handle.Lock = HAL_UNLOCKED;

  if (HAL_RNG_Init(&handle) != HAL_OK)
  {
    users = 0;
    return status;
  }

  /* Set NIST configuration for better security */
  rng_conf.Config1 = 0x0FUL;
  rng_conf.Config2 = 0UL;
  rng_conf.Config3 = 0x0DUL;
  rng_conf.ClockDivider = RNG_CLKDIV_BY_1;
  rng_conf.NistCompliance = RNG_NIST_COMPLIANT;
  rng_conf.AutoReset = RNG_ARDIS_ENABLE;
  rng_conf.HealthTest = 0x0000AEC7UL;
  if (HAL_RNGEx_SetConfig(&handle, &rng_conf) != HAL_OK)
  {
    goto exit;
  }

  /* first random number generated after setting the RNGEN bit should not be used */
  if (HAL_RNG_GenerateRandomNumber(&handle, &dummy) != HAL_OK)
  {
    /* Try to recover from a seed error */
    if(HAL_RNG_GetError(&handle) != HAL_RNG_ERROR_SEED)
    {
      goto exit;
    }
    if (HAL_RNGEx_RecoverSeedError(&handle) != HAL_OK)
    {
      goto exit;
    }
  }

  status = PSA_SUCCESS;

exit:
  if (status != PSA_SUCCESS)
  {
    RNG_DeInit();
  }
  return status;
}

static psa_status_t RNG_GetBytes(uint8_t *output, size_t length, size_t *output_length)
{
  psa_status_t status = PSA_SUCCESS;
  uint8_t try = 0U;
  __IO uint8_t random[4];
  *output_length = 0;

  /* Get Random byte */
  while ((*output_length < length) && (status == PSA_SUCCESS))
  {
    if (HAL_RNG_GenerateRandomNumber(&handle, (uint32_t *)random) != HAL_OK)
    {
      /* Try to recover from a seed error */
      if(HAL_RNG_GetError(&handle) != HAL_RNG_ERROR_SEED)
      {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      if (HAL_RNGEx_RecoverSeedError(&handle) != HAL_OK)
      {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      /* retry when random number generated are not immediately available */
      if (try < 3U)
      {
        try++;
      }
      else
      {
        status = PSA_ERROR_HARDWARE_FAILURE;
      }
    }
    else
    {
      for (uint8_t i = 0U; (i < 4U) && (*output_length < length) ; i++)
      {
        *output++ = random[i];
        *output_length += 1U;
        random[i] = 0;
      }
    }
  }
  /* Just be extra sure that we didn't do it wrong */
  if ((__HAL_RNG_GET_FLAG(&handle, (RNG_FLAG_CECS | RNG_FLAG_SECS))) != 0)
  {
    *output_length = 0;
  }

  return status;
}

psa_status_t STM32_RNGGetRandom(uint8_t *output, size_t output_size, size_t *output_length)
{
  if (init_ctx == 0U)
  {
    if (RNG_Init() != 0)
    {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    init_ctx = 1U;
  }

  if (RNG_GetBytes(output, output_size, output_length) != 0)
  {
    return PSA_SUCCESS;
  }

  if (*output_length != output_size)
  {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  if (init_ctx == 1U)
  {
    if (RNG_DeInit() != 0)
    {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    init_ctx = 0U;
  }

  return PSA_SUCCESS;
}
#endif /* STM32_HAL_RNG_DRIVER_ENABLED */
