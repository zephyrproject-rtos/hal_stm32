/**
  ******************************************************************************
  * @file    stm32mp13xx_ll_bsec.h
  * @author  MCD Application Team
  * @brief   Header file of BSEC LL module.
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
#ifndef STM32MP13xx_LL_BSEC_H
#define STM32MP13xx_LL_BSEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx.h"

/** @addtogroup STM32MP13xx_LL_Driver
  * @{
  */

#if defined(BSEC)

/** @defgroup BSEC_LL BSEC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup BSEC_LL_Exported_Constants BSEC Exported Constants
  * @{
  */

/** Complement BSEC_OTP_CONTROL definitions not available in hw.h of IP block **/
#define BSEC_OTP_CONTROL_PROG_READ_VALUE      ((uint32_t)0)
#define BSEC_OTP_CONTROL_PROG_PROGRAM_VALUE   ((uint32_t)1)

#define BSEC_OTP_CONTROL_LOCK_NOTLOCKED_VALUE ((uint32_t)0)
#define BSEC_OTP_CONTROL_LOCK_LOCKED_VALUE    ((uint32_t)1)

/* Position of fdis_tk bit in OTP_DATA1 word */
#define BSEC_OTP_CFG1_FDIS_TK_BIT_POS           15

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/**
  * @brief  Write a value in a register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define BSEC_WRITE( __REG__, __VALUE__) WRITE_REG(BSEC->__REG__, __VALUE__)

/**
  * @brief  Read a value in a register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define BSEC_READ(__REG__) READ_REG(BSEC->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Read BSEC_OTP_STATUS register and return
  *         1 if sample is not OTP_INVALID
  *         0 if sample is OTP_INVALID
  *
  * @retval 1 if sample is not OTP_INVALID, 0 if sample is OTP_INVALID
  */
__STATIC_INLINE uint32_t LL_BSEC_IsOtpStatusNotOtpInvalid(void)
{
  return (((BSEC_READ(BSEC_OTP_STATUS) & BSEC_OTP_STATUS_INVALID) == 0U) ? 1U : 0U);
}

/**
  * @brief  Read OTP register in BSEC shadow registers
  *
  * @param  shadowNumber   : fuse number (from 0 to 95)
  *
  * @retval None
  */
__STATIC_INLINE uint32_t LL_BSEC_ReadOtpData(uint32_t shadowNumber)
{
  return BSEC_READ(BSEC_OTP_DATA[shadowNumber]);
}

/**
  * @brief  Write OTP register in BSEC shadow registers
  *
  * @param  shadowNumber    : fuse number (from 0 to 95)
  * @param  data            : BSEC_DATA register data
  *
  * @retval None
  */
__STATIC_INLINE void LL_BSEC_WriteOtpData(uint32_t shadowNumber, uint32_t data)
{
  BSEC_WRITE(BSEC_OTP_DATA[shadowNumber], data);
}

/**
  * @brief  Reload OTP fuse from safemem
  *
  * @param  fuseNumber     : fuse number (from 0 to 95)
  *
  * @retval None
  */
__STATIC_INLINE uint32_t LL_BSEC_ReloadOtp(uint32_t fuseNumber)
{
  BSEC->BSEC_OTP_CONTROL =
    (BSEC_OTP_CONTROL_PROG_READ_VALUE << BSEC_OTP_CONTROL_PROG_Pos) |
    ((fuseNumber & BSEC_OTP_CONTROL_ADDR) << BSEC_OTP_CONTROL_ADDR_Pos);

  while ((BSEC->BSEC_OTP_STATUS & BSEC_OTP_STATUS_BUSY) != 0U)
  {}

  return BSEC->BSEC_OTP_DATA[fuseNumber];
}

/**
  * @brief  Program OTP fuse
  *
  * @param  fuseNumber     : fuse number (from 0 to 95)
  * @param  value          : word value to program
  *
  * @retval None
  */
__STATIC_INLINE void LL_BSEC_ProgOtp(uint32_t fuseNumber, uint32_t value)
{
  BSEC->BSEC_OTP_WRDATA = value;

  BSEC->BSEC_OTP_CONTROL =
    (BSEC_OTP_CONTROL_PROG_PROGRAM_VALUE << BSEC_OTP_CONTROL_PROG_Pos) |
    (BSEC_OTP_CONTROL_LOCK_NOTLOCKED_VALUE << BSEC_OTP_CONTROL_LOCK_Pos) |
    ((fuseNumber & BSEC_OTP_CONTROL_ADDR) << BSEC_OTP_CONTROL_ADDR_Pos);

  while ((BSEC->BSEC_OTP_STATUS & BSEC_OTP_STATUS_BUSY) != 0U) {}
  }

/**
  * @brief  Set power on
  *
  * @retval None
  */
__STATIC_INLINE void LL_BSEC_SetPowerON(void)
{
  BSEC->BSEC_OTP_CONFIG |= ((uint32_t)1 << BSEC_OTP_CONFIG_PWRUP_Pos);
  while ((BSEC->BSEC_OTP_STATUS & BSEC_OTP_STATUS_PWRON) == 0U) {}
  }


/**
  * @brief  Set power off
  *
  * @retval None
  */
__STATIC_INLINE void LL_BSEC_SetPowerOFF(void)
{
  BSEC->BSEC_OTP_CONFIG &= ~((uint32_t)1 << BSEC_OTP_CONFIG_PWRUP_Pos);
  while ((BSEC->BSEC_OTP_STATUS & BSEC_OTP_STATUS_PWRON) != 0U) {}
  }

/**
  * @brief  Get secure debug enable bits
  *
  * @retval secure debug enable bits
  */
__STATIC_INLINE uint32_t LL_BSEC_GetSecureDebugEnableBits(void)
{
  uint32_t regVal;
  uint32_t retVal;

  /* read DENABLE register */
  regVal = BSEC_READ(BSEC_DENABLE);

  /* get value of secure debug enable bits */
  retVal = regVal & (BSEC_DENABLE_SPIDEN | BSEC_DENABLE_SPNIDEN);

  return retVal;
}

/**
  * @brief  Set secure debug enable bits
  *
  * @param  mask : re debug enable bits mask
  *
  * @retval None
  */
__STATIC_INLINE void LL_BSEC_SetSecureDebugEnableBits(uint32_t mask)
{
  uint32_t regVal;

  /* read DENABLE register */
  regVal = BSEC_READ(BSEC_DENABLE);

  /* ensure mask contains only secure debug enable bits */
  uint32_t temp;
  temp = mask & (BSEC_DENABLE_SPIDEN | BSEC_DENABLE_SPNIDEN);

  /* force these bits in regVal */
  regVal &= ~(BSEC_DENABLE_SPIDEN | BSEC_DENABLE_SPNIDEN);
  regVal |= temp;

  /* update DENABLE reg */
  BSEC_WRITE(BSEC_DENABLE, regVal);
}

/**
  * @brief  Close secure debug
  *
  * @retval State of secure debug enable bits before closing it.
  */
__STATIC_INLINE uint32_t LL_BSEC_CloseSecureDebug(void)
{
  uint32_t regVal;
  uint32_t retVal;

  /* read DENABLE register */
  regVal = BSEC_READ(BSEC_DENABLE);

  /* get value of secure debug enable bits for return value */
  retVal = regVal & (BSEC_DENABLE_SPIDEN | BSEC_DENABLE_SPNIDEN);

  /* force these bits to 0 in regVal */
  regVal &= ~(BSEC_DENABLE_SPIDEN | BSEC_DENABLE_SPNIDEN);

  /* update DENABLE reg with bits forced to 0 */
  BSEC_WRITE(BSEC_DENABLE, regVal);

  /* return previous velue of secure debug enable bits */
  return retVal;
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup BSEC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined(BSEC) */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP13xx_LL_BSEC_H */


