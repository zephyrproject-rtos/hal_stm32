/**
  ******************************************************************************
  * @file    stm32_mem.h
  * @author  MCD Application Team
  * @brief   standard memory operation
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_MEM_H__
#define __STM32_MEM_H__

#ifdef __cplusplus
extern "C"
{
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "utilities_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---- Memory mapping macros ----------------------------------------------- */
#define UTIL_MEM_PLACE_IN_SECTION( __x__ ) UTIL_PLACE_IN_SECTION( __x__ )
#define UTIL_MEM_ALIGN ALIGN

/* Exported functions ------------------------------------------------------- */
/**
* @brief  This API copies one buffer to another
* @param  dst: output buffer to be filled
* @param  src: input buffer
* @param  size: size of 8b data
* @retval None
*/
void UTIL_MEM_cpy_8( void *dst, const void *src, uint16_t size );

/**
* @brief  This API copies one buffer to another in reverse
* @param  dst: output buffer to be filled
* @param  src: input buffer
* @param  size: size of 8b data
* @retval None
*/
void UTIL_MEM_cpyr_8( void *dst, const void *src, uint16_t size );

/**
* @brief  This API fills a buffer with value
* @param  dst: output buffer to be filled
* @param  value: value
* @param  size: size of 8b data
* @retval None
*/
void UTIL_MEM_set_8( void *dst, uint8_t value, uint16_t size );

#ifdef __cplusplus
}
#endif

#endif /* __STM32_MEM_H__ */
