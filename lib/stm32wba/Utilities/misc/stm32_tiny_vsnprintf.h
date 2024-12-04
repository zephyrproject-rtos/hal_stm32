/**
  ******************************************************************************
  * @file    stm32_tiny_vsnprintf.h
  * @author  MCD Application Team
  * @brief   Header for tiny_vsnprintf.c module
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
#ifndef __STM32_TINY_VSNPRINTF_H__
#define __STM32_TINY_VSNPRINTF_H__

#ifdef __cplusplus
extern "C"
{
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <string.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
 * @brief  Tiny implementation of vsnprintf() like function
 *
 *         It has been adapted so that:
 *         - Tiny implementation, when defining TINY_PRINTF, is available. In such as case,
 *           not all the format are available. Instead, only %02X, %x, %d, %u, %s and %c are available.
 *           %f,, %+, %#, %- and others are excluded
 *         - Provide a snprintf like implementation. The size of the buffer is provided,
 *           and the length of the filled buffer is returned (not including the final '\0' char).
 *         The string may be truncated
 * @param  Pointer to a buffer where the resulting C-string is stored. The buffer should have a size of
 *         at least n characters.
 * @param  Maximum number of bytes to be used in the buffer. The generated string has a length of at
 *         most n-1, leaving space for the additional terminating null character.
 * @param  C string that contains a format string that follows the same specifications as format
 *         in printf (see printf for details).
 * @param  A value identifying a variable arguments list initialized with va_start.
 * @retval The number of written char (note that this is different from vsnprintf()
 */
int tiny_vsnprintf_like(char *buf, const int size, const char *fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif /* __STM32_TINY_VSNPRINTF_H__ */
