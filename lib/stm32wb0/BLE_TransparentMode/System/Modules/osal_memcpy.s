/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    osal_memcpy.s
  * @author  GPM WBL Application Team
  * @brief   osal memcpy utilities
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
                __EXPORT__ Osal_MemCpy

EXPORT_FUNC(Osal_MemCpy)
                LSLS	R3, R1, #30
                BEQ	    memcpy_1
LABEL(memcpy_byte) /* Copy bytes until src is aligned */
                SUBS	R2, R2, #1
                BCC	    memcpy_exit
                LDRB	R3, [R1]
      	        ADDS	R1, R1, #1
      	        STRB	R3, [R0]
                ADDS	R0, R0, #1
                LSLS	R3, R1, #30
                BNE	    memcpy_byte
LABEL(memcpy_1)
                LSLS	R3, R0, #30
                BEQ	    memcpy4
                CMN	    R3, R3
                BEQ	    memcpy_7
                SUBS	R0, R0, #1
                SUBS	R2, R2, #4
                BCC	    memcpy_3
LABEL(memcpy_2)  /* Load one word from src and write one byte, one half-word and another byte to dst */
                LDM	    R1!, {R3}
                STRB	R3, [R0, #1]
                LSRS	R3, R3, #8
                STRH	R3, [R0, #2]
                LSRS	R3, R3, #16
                STRB	R3, [R0, #4]
                ADDS	R0, R0, #4
                SUBS	R2, R2, #4
                BCS	    memcpy_2
LABEL(memcpy_3)
                LSLS	R2, R2, #31
                BCC	    memcpy_5
                LDRH	R3, [R1]
                STRB	R3, [R0, #1]
                BEQ	    memcpy_4
                LDRB	R2, [R1, #2]
                STRB	R2, [R0, #3]
LABEL(memcpy_4)
                LSRS	R3, R3, #8
                STRB	R3, [R0, #2]
                BX	    LR
LABEL(memcpy_5)
                BEQ	    memcpy_exit
                LDRB	R3, [R1]
                STRB	R3, [R0, #1]
LABEL(memcpy_exit)
                BX	    LR
LABEL(memcpy_7)
                SUBS	R2, R2, #4
                BCC	    memcpy_9
LABEL(memcpy_8)  /* Load one word from src and write half-words to dst */
                LDM	    R1!, {R3}
                STRH	R3, [R0]
                LSRS	R3, R3, #16
                STRH	R3, [R0, #2]
                ADDS	R0, R0, #4
                SUBS	R2, R2, #4
                BCS	    memcpy_8
LABEL(memcpy_9)
                LSLS	R2, R2, #31
                BCC	    memcpy_10
                LDRH	R3, [R1]
                STRH	R3, [R0]
                BEQ	    memcpy_11
                LDRB	R3, [R1, #2]
                STRB	R3, [R0, #2]
                BX	    LR
LABEL(memcpy_10)
                BEQ	    memcpy_11
                LDRB	R3, [R1]
                STRB	R3, [R0]
LABEL(memcpy_11)
                BX	    LR

LABEL(memcpy4)
                PUSH	{R4-R6}
                SUBS	R2, #16
                BCC	    memcpy4_2words
LABEL(memcpy4_4words)
                LDM 	R1!, {R3-R6}
                STM	    R0!, {R3-R6}
                SUBS	R2, #16
                BCS	    memcpy4_4words
LABEL(memcpy4_2words)
                LSLS	R3, R2, #29
                BCC	    memcpy4_word
                LDM	    R1!, {R3, R4}
                STM	    R0!, {R3, R4}
LABEL(memcpy4_word)
                BPL 	memcpy4_halfword
                LDM	    R1!, {R3}
                STM	    R0!, {R3}
LABEL(memcpy4_halfword)
                LSLS	R2, R2, #31
                BCC	    memcpy4_byte
                LDRH	R3, [R1]
                STRH	R3, [R0]
                ADDS	R0, R0, #2
                ADDS	R1, R1, #2
                CMP	    R2, #0
LABEL(memcpy4_byte)
                BPL	    memcpy4_exit
                LDRB	R3, [R1]
                STRB	R3, [R0]
LABEL(memcpy4_exit)
                POP	    {R4-R6}
                BX	    LR

                ENDFUNC

    ALIGN_MEM(4)
	__END__
