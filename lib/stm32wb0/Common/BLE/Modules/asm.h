/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    asm.h
  * @author  GPM WBL Application Team
  * @brief   ASM Compiler-dependent macros.
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

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __ASM_H__
#define __ASM_H__

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#if defined(__ICCARM__) || defined(__IAR_SYSTEMS_ASM__)
#define __CODE__                    SECTION .text:CODE:REORDER:NOROOT(2)
#define __BSS__                     SECTION .bss:DATA:NOROOT(2)
#define __EXPORT__                  EXPORT
#define __IMPORT__                  IMPORT
#define __THUMB__                   THUMB
#define EXPORT_FUNC(f)		            f:
#define __END__                     END
#define __SPACE__                   DS8
#define GLOBAL_VAR(val)               val:
#define ENDFUNC
#define ALIGN_MEM(n)
#define LABEL(label)                label:

#elif defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100))
#define __CODE__		    AREA	|.text|, CODE, READONLY
#define __THUMB__
#define EXPORT_FUNC(f)			    f PROC
#define __BSS__                     AREA	|.bss|, DATA, READWRITE, NOINIT
#define __EXPORT__                  EXPORT
#define __IMPORT__                  IMPORT
#define __SPACE__                   SPACE
#define GLOBAL_VAR(val)             val
#define __END__					END
#define ENDFUNC			    ENDP
#define ALIGN_MEM(n)			  ALIGN n
#define LABEL(label)                label

#elif defined(__GNUC__)
.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb
#define __CODE__                    .text
#define __BSS__                     .bss
#define __EXPORT__                  .global
#define __IMPORT__                  .extern
#define __THUMB__                   .thumb_func
#define __END__                     .end
#define __SPACE__                   .space
#define EXPORT_FUNC(f)		            f:
#define GLOBAL_VAR(val)               val:
#define ENDFUNC
#define ALIGN_MEM(n)				.align n>>1
#define LABEL(label)                label:

#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif /* __ASM_H__ */
