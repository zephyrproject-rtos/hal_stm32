/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    blue_unit_conversion.s
  * @author  GPM WBL Application Team
  * @brief   blue_unit_conversion implements the conversion from low speed oscillator
  * independent units (STU) to low speed oscillator dependent units (MTU) and
  * vice-versa according to the input parameters.
  * The first parameter is the quantity to be translated expressed in STU or MTU.
  * The second parameter is the frequency or the period.
  * The third parameter is a threshold to switch to 32 bit multiplication.
  * This routine avoids floating divisions exploiting only integer math, maintaining
  * a good rounding error as well.
  * It embeds a long multiplication algorithm suited for this purpose.
  * The threshold passed as parameter allows performing a simple 32bit multiplication
  * instead of long multiplication, saving computational time for small quantities
  * (when it is needed that the conversion is done as fast as possible).
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "asm.h"

                __CODE__
                __THUMB__
                __EXPORT__ blue_unit_conversion

EXPORT_FUNC(blue_unit_conversion)
                  PUSH    {r4, lr}
                  CMP     r0, r2
                  BLS     mul32
                  UXTH    r2, r1
                  LSRS    r3, r0, #16
                  LSRS    r1, r1, #16
                  MOV     r4, r1
                  MULS    r1, r3, r1
                  UXTH    r0, r0
                  MULS    r3, r2, r3
                  MULS    r4, r0, r4
                  MULS    r0, r2, r0
                  ADDS    r3, r3, r4
                  LSLS    r2, r3, #16
                  LSRS    r3, r3, #16
                  ADDS    r0, r2, r0
                  ADCS    r1, r3

                  MOVS    r2, #128
                  LSLS    r2, r2, #13
                  MOVS    r3, #0
                  ADDS    r2, r2, r0
                  ADCS    r3, r1
                  LSRS    r2, r2, #21
                  LSLS    r0, r3, #11
                  ORRS    r0, r2

                  POP {r4, pc}

                  ENDFUNC

EXPORT_FUNC(mul32)
                  MULS    r0, r1, r0
                  MOVS    r2, #128
                  LSLS    r2, r2, #13
                  ADDS    r2, r2, r0
                  LSRS    r2, r2, #21
                  MOV     r0, r2

                  POP {r4, pc}

                  ENDFUNC

    ALIGN_MEM(4)
	__END__
