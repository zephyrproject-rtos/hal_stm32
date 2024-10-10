/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    cpu_context_switch.s
  * @author  GPM WBL Application Team
  * @brief   cpu_context_switch implements the CPU context switch
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

#include "../Modules/asm.h"

//------------------------------------------------------------------------------
//   void CS_contextSave(void)
//   void CS_contextRestore(void)
//
// These two functions are needed for the context switch during the power
// save procedure. The purpose of the CS_contextSave() function is to
// either save the current context and trigger sleeping through the 'WFI'
// instruction.
// The CS_contextRestore() function restores the context saved before
// to go in deep sleep.
// All the Cortex M0+ registers are saved and restored plus after wakeup
// -----------------------------------------------------------------------------
                __CODE__
                __THUMB__
                __EXPORT__ CPUcontextSave
                __EXPORT__ CPUcontextRestore
                __IMPORT__ RAM_VR
EXPORT_FUNC(CPUcontextSave)
                MRS    R2, CONTROL             /* load the CONTROL register into R2 */
                MRS    R1, PSP                 /* load the process stack pointer into R1 */
                LDR    R0, =0
                MSR    CONTROL, R0             /* Switch to Main Stack Pointer */
                ISB

                PUSH   { r4 - r7, lr }         /* store R4-R7 and LR (5 words) onto the stack */
                MOV    R3, R8                  /* mov thread {r8 - r12} to {r3 - r7} */
                MOV    R4, R9
                MOV    R5, R10
                MOV    R6, R11
                MOV    R7, R12
                PUSH   {R3-R7}                 /* store R8-R12 (5 words) onto the stack */

                LDR    R4, =RAM_VR             /* load address of struct RAM_VR into R4 */
                MRS    R3, MSP                 /* load the stack pointer into R3 */
                STR    R3, [R4,#4]             /* store the MSP into RAM_VR.SavedMSP (second word of the structure) */

                PUSH  { r1, r2 }               /*  store PSP, CONTROL */

                DSB
                WFI                            /* all saved, trigger deep sleep */

                NOP                            /* NOP instructions added if an interrupt (NOT WAKEUP SOURCE) is raised */
                NOP                            /* the device gates/stop the CPU clock 2 system clock cycles after this WFI */
                                               /* this can be a blind window */

                ENDFUNC

EXPORT_FUNC(CPUcontextRestore)
                /* Even if we fall through the WFI instruction, we will immediately
                 * execute a context restore and end up where we left off with no
                 * ill effects.  Normally at this point the core will either be
                 * powered off or reset (depending on the deep sleep level). */
                LDR    R4, =RAM_VR              /* load address of RAM_VR into R4 */
                LDR    R4, [R4,#4]              /* load the MSP from RAM_VR.SavedMSP (second word of the structure) */
                MSR    MSP, R4                  /* restore the MSP from R4 */

                SUB    SP, #0x8
                POP    { R0, R1 }               /* load PSP from the stack in R0, and  load CONTROL register from the stack in R1 */

                POP    { R3-R7 }                /* load R8-R12 (5 words) from the stack */
                MOV    R8, R3                   /* mov {r3 - r7} to {r8 - r12} */
                MOV    R9, R4
                MOV    R10, R5
                MOV    R11, R6
                MOV    R12, R7
                POP    { R4 - R7 }              /* load R4-R7 (4 words) from the stack */
                POP    { R2 }                   /* load LR from the stack */

                MSR   PSP, R0                   /* restore PSP from R0 */
                MSR   CONTROL , R1              /* restore CONTROL register from R1 */
                ISB

                BX  R2                          /*load PC (1 words) from the stack */

                ENDFUNC

    ALIGN_MEM(4)
	__END__
