/**
  ******************************************************************************
  * @file    system_stm32mp2xx_a35.c
  * @author  C.ICORD (Intropack Team)
  * @version $VERSION$
  * @date    $DATE$
  * @brief   CMSIS Cortex-A35 Device Peripheral Access Layer System Source File
  *
  *   This file provides one global variable and two functions to be used/called
  *   by user application:
  *
  *      - SystemInit(): Called at start-up just after reset before branching
  *                      to main program.
  *
  *      - SystemCoreClock variable: Manages the core clock frequency
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset, HSI clock is used as system clock source.
  *   Then, SystemInit() function is called, in "startup_stm32mp2xx_a35.c" file,
  *   to configure the system clock before branching to main program.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2022 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup STM32MP2xx_system
  * @{
  */

/** @addtogroup STM32MP2xx_System_Private_Includes
  * @{
  */
//#define DEBUG_TIMER
//#define DEBUG_IRQ_ERROR
//#define DEBUG_PPI2x

#include <stdint.h>
#if defined(DEBUG_IRQ_ERROR) || defined(DEBUG_PPI2x)
#include <stdio.h>
#endif
#include "stm32mp2xx_hal.h"
#include "irq_ctrl.h"
#include "system_stm32mp2xx.h"
#include "system_stm32mp2xx_a35_utils.h"

/**
  * @}
  */

/** @addtogroup STM32MP2xx_System_Private_TypesDefinitions
  * @{
  */
#if defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE)
typedef struct interrupt_infos
{
   uint16_t id;
   uint8_t  requested_cpu_id;
   uint8_t  group;
} interrupt_infos_t;
#endif /* defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE) */

/**
  * @}
  */

/** @addtogroup STM32MP2xx_System_Private_Defines
  * @{
  */
/* These defines are associated to GIC400 */
#define GIC_HIGHEST_INTERRUPT_VALUE 1020
#define GIC_HIGHEST_SGI_PPI_VALUE     31
#define GIC_HIGHEST_SGI_VALUE         15
/*
 * ID 1023. This value is returned to a processor,
 * in response to an interrupt acknowledge,
 * if there is no pending interrupt with sufficient priority
 * for it to be signalized to the processor.
 */
#define GIC_ACKNOWLEDGE_RESPONSE 1023

#if defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE)
#define MAX_LIMIT_VALID_IT_ID 1022
#define INVALID_IT_ID 0xFFFF
#endif /* defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE) */

/* IRQ Handling error values */
#define NO_IRQ_ERROR                 0x00000000UL
#define ERROR_IRQ_IDX_OUT_OF_RANGE   0x00BAD11DUL
#define ERROR_UNDEFINED_IRQ_HANDLER  0xDEAD11F0UL
#define ERROR_SPURIOUS_IRQ           0xFFFF1022UL

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x200. */
/******************************************************************************/
/**
  * @}
  */

/** @addtogroup STM32MP2xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32MP2xx_System_Private_Variables
  * @{
  */

uint32_t IRQHandlingError = NO_IRQ_ERROR;
uint32_t TimerPeriod = 0;
uint32_t A35SysTick_TimerSource = A35_SYSTICK_PHYSICALTIMERSOURCE;
#ifdef DEBUG_TIMER
uint32_t RELOAD_VAL = 0;
#endif
#ifdef DEBUG_TIMER2
uint32_t RELOAD_VAL2 = 0;
#endif
#ifdef DEBUG_PPI2x
uint32_t FIQ_count = 0;
uint32_t IRQ_count = 0;
uint32_t PPI27_count = 0;
uint32_t PPI29_count = 0;
uint32_t PPI30_count = 0;
#endif

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
/* The SystemCoreClock variable is updated in two ways:
    1) by calling CMSIS function SystemCoreClockUpdate()
    2) each time HAL_RCCEx_CA35SS_SetCA35SSClockSource() is called to configure
         the CA35 clock frequency
       Note: If you use this function to configure the system clock frequency
             then there is no need to call SystemCoreClockUpdate(), since
             SystemCoreClock variable is updated automatically.
*/
uint32_t SystemCoreClock = HSI_VALUE;

uint32_t Processing_IRQ_flag = 0xDEADBEEF;
uint32_t IRQ_current_index = 0;
uint32_t Processing_FIQ_flag = 0xDEADBEEF;
uint32_t FIQ_current_index = 0;
uint32_t Spurious_IT_count = 0;

#if defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE)
static interrupt_infos_t current_interrupt_infos[A35_NB_CORES];
#endif /* defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE) */

/**
  * @}
  */

/** @addtogroup STM32MP2xx_System_Private_FunctionPrototypes
  * @{
  */
#ifdef WA_CMSIS_ISSUE_IRQ_SETMODE
int32_t FIX_SetModeIssueOnInterruptGroup( IRQn_ID_t irqn,
                                          uint32_t  mode);
#endif /* WA_CMSIS_ISSUE_IRQ_SETMODE */
#ifdef CR_CMSIS_IT_GROUP_MANAGEMENT
interrupt_infos_t newIRQ_GetActiveInterrupt( void );
int32_t newIRQ_EndOfInterrupt( interrupt_infos_t current_interrupt_infos );
#endif /* CR_CMSIS_IT_GROUP_MANAGEMENT */
#ifdef WA_CMSIS_ISSUE_IRQ_GETACTIVE
interrupt_infos_t FIX_IRQ_GetActiveInterrupt( void );
int32_t newIRQ_EndOfInterrupt( interrupt_infos_t current_interrupt_infos );
#endif /* WA_CMSIS_ISSUE_IRQ_GETACTIVE */

/**
  * @}
  */

/** @addtogroup STM32MP2xx_System_Private_Functions
  * @{
  */
#ifdef WA_CMSIS_ISSUE_IRQ_SETMODE
int32_t FIX_SetModeIssueOnInterruptGroup( IRQn_ID_t irqn,
                                          uint32_t  mode)
{
  uint32_t val;
  uint8_t group;
  int32_t status = 0;

  // Check interrupt domain
  val = mode & IRQ_MODE_DOMAIN_Msk;

  // Check security extensions support
  if ( (GIC_DistributorInfo() & (1UL << 10U)) != 0U)
  {
     if (val == IRQ_MODE_DOMAIN_NONSECURE)
     {
        group = 1U;
     }
     else
     {
        group = 0U;
     }
  }
  else
  {
     if (val == IRQ_MODE_DOMAIN_NONSECURE)
     {
        group = 0U;
     }
     else
     {
        status = -1;
     }
  }
  if (status == 0)
  {
     GIC_SetGroup((IRQn_Type)irqn, group);
  }
  return status;
}
#endif /* WA_CMSIS_ISSUE_IRQ_SETMODE */

#ifdef CR_CMSIS_IT_GROUP_MANAGEMENT
interrupt_infos_t newIRQ_GetActiveInterrupt( void )
{
  interrupt_infos_t current_it = {INVALID_IT_ID, 0xFF, 0xFF};
  uint32_t gicc_regval;
  uint32_t pending_G0 = 0, pending_G1 = 0;

  /* Read index of pending interrupt with the highest priority in "Group0" */
  gicc_regval = GIC_GetHighPendingIRQ();
  pending_G0 = gicc_regval & 0x3FF;
  if (pending_G0 < MAX_LIMIT_VALID_IT_ID)
  {
     /* Acknowledge pending "Group0" interrupt (make it active)   */
     /* by getting GICC_IAR value (see #4.4.4 in [ARM IHI 0048B]) */
     /* NB : GIC_AcknowledgePending() from "CMSIS Core_A" v5.5.1  */
     /*      is not sufficient to manage GICC_IAR specifications  */
     /*      ("CPUID" field in SGI case).                         */
     gicc_regval = GICInterface->IAR;
     current_it.group = 0;
     current_it.requested_cpu_id = (uint8_t)((gicc_regval >> 10) & 0x7);
     current_it.id = (uint16_t)(gicc_regval & 0x3FF);
  }
  /* Check whether a "Group 1" interrupt is pending */
  else
  {
     gicc_regval = GICInterface->AHPPIR;
     pending_G1 = gicc_regval & 0x3FF;
     if (pending_G1 < MAX_LIMIT_VALID_IT_ID)
     {
        /* Acknowledge "Group1" pending interrupt (make it active)    */
        /* by getting GICC_AIAR value (see #4.4.4 in [ARM IHI 0048B]) */
        /* NB : This function doesn't exist in "CMSIS Core_A" v5.5.1  */
        gicc_regval = GICInterface->AIAR;
        current_it.group = 1;
        current_it.requested_cpu_id = (uint8_t)((gicc_regval >> 10) & 0x7);
        current_it.id = (uint16_t)(gicc_regval & 0x3FF);
     }
     else
        current_it.id = (uint16_t)(pending_G0 | pending_G1);
  }
  return current_it;
}

int32_t newIRQ_EndOfInterrupt( interrupt_infos_t current_interrupt_infos )
{
  int32_t status = -1;
  volatile uint32_t gicc_regval;

  /* Process end of acknowledged interrupt by writing values read        */
  /* in GICC_IAR resp. GICC_AIAR register according to interrupt Group : */
  /* - by setting "Interrupt ID" bits [9:0] */
  gicc_regval = (uint32_t)current_interrupt_infos.id;
  if ( gicc_regval < MAX_LIMIT_VALID_IT_ID )
  {
  /* - by setting "CPUID" bits [12:10] */
     gicc_regval |= (uint32_t)(current_interrupt_infos.requested_cpu_id << 10);
  /* ["Group 0" IT case] */
  /* - by writing value in GICC_EOIR "End of Interrupt Register" */
  /*   (see 4.4.5 (Table 4-36) in [ARM IHI 0048B])               */
     if (0 == current_interrupt_infos.group)
     {
       GICInterface->EOIR = gicc_regval;
       status = 0;
     }
  /* ["Group 1" IT case] */
  /* - by writing value in "Aliased End of Interrupt Register" */
  /*   (see 4.4.10 (Table 4-45) in [ARM IHI 0048B])            */
     else if (1 == current_interrupt_infos.group)
     {
       GICInterface->AEOIR = gicc_regval;
       status = 0;
     }
  }
  return status;
}
#endif /* CR_CMSIS_IT_GROUP_MANAGEMENT */

#ifdef WA_CMSIS_ISSUE_IRQ_GETACTIVE
interrupt_infos_t FIX_IRQ_GetActiveInterrupt( void )
{
  interrupt_infos_t current_it = {INVALID_IT_ID, 0xFF, 0xFF};
  uint32_t gicc_regval, pending_G1 = 0;

  /* Read index of pending interrupt with the highest priority in "Group1" */
  gicc_regval = GIC_GetHighPendingIRQ();
  pending_G1 = gicc_regval & 0x3FF;

  if (pending_G1 < MAX_LIMIT_VALID_IT_ID)
  {
     /* Acknowledge "Group1" pending interrupt (make it active)   */
     /* by getting GICC_IAR value (see #4.4.4 in [ARM IHI 0048B]) */
     /* NB : GIC_AcknowledgePending() from "CMSIS Core_A" v5.5.1  */
     /*      is not sufficient to manage GICC_IAR specifications  */
     /*      ("CPUID" field in SGI case).                         */
     gicc_regval = GICInterface->IAR;
     current_it.group = 1;
     current_it.requested_cpu_id = (uint8_t)((gicc_regval >> 10) & 0x7);
     current_it.id = (uint16_t)(gicc_regval & 0x3FF);
  }
  else
     current_it.id = (uint16_t)pending_G1;
  return current_it;
}

int32_t newIRQ_EndOfInterrupt( interrupt_infos_t current_interrupt_infos )
{
  int32_t status = -1;
  volatile uint32_t gicc_regval;

  /* Process end of acknowledged interrupt by writing values */
  /* read in GICC_IAR register : */
  /* - by setting "Interrupt ID" bits [9:0] */
  gicc_regval = (uint32_t)current_interrupt_infos.id;
  if ( gicc_regval < MAX_LIMIT_VALID_IT_ID )
  {
  /* - by setting "CPUID" bits [12:10] */
     gicc_regval |= (uint32_t)(current_interrupt_infos.requested_cpu_id << 10);
  /* ["Group 1" IT case] */
  /* - by writing value in GICC_EOIR "End of Interrupt Register" */
  /*   (see 4.4.5 (Table 4-36) in [ARM IHI 0048B])               */
     GICInterface->EOIR = gicc_regval;
     status = 0;
  }
  return status;
}
#endif /* WA_CMSIS_ISSUE_IRQ_GETACTIVE */

/**
  * @brief  Generic IRQ Error Handler
  * @param  None
  * @retval None
  */
static void SystemInit_IRQ_ErrorHandler(void)
{
  /* Loop indefinitely in case of IRQ handling Errors */
  //while(1);
  Spurious_IT_count += 1;
  if (Spurious_IT_count > 1000)
  {
#ifdef DEBUG_IRQ_ERROR
     printf("<E> TWO MANY SPURIOUS INTERRUPTS OCCURRED\n");
#endif /* DEBUG_IRQ_ERROR */
     while(1);
  }
}

/**
  * @brief  Generic IRQ Handler for (non-secure) SGI, PPI & SPI interrupts
  *         routed on IRQ line from GIC400 to CPU
  * @param  None
  * @retval None
  */
void __attribute__ ((interrupt ("IRQ")))IRQ_Handler(void)
{
  IRQHandler_t handler;
  uint32_t ItId;
#if defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE)
  uint32_t core_idx;
#endif /* defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE) */

  /* Process all pending IRQ interrupts */
  Processing_IRQ_flag = 1;
  while (1)
  {
#if defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE)
    /* Get core index by reading MPIDR bits [3:0] */
    __asm volatile("MRC p15, 0, %0, c0, c0, 5"   :"=r" (core_idx) : /* no input regs */ : /* no clobbered regs */);
    core_idx = core_idx & 0xF;

    /* Get current pending interrupt infos */
    #ifdef CR_CMSIS_IT_GROUP_MANAGEMENT
    current_interrupt_infos[core_idx] = newIRQ_GetActiveInterrupt();
    #else
    current_interrupt_infos[core_idx] = FIX_IRQ_GetActiveInterrupt();
    #endif /* CR_CMSIS_IT_GROUP_MANAGEMENT */
    ItId = current_interrupt_infos[core_idx].id;
#else
    /* Get highest pending interrupt index from GIC driver */
    ItId = IRQ_GetActiveIRQ();
#endif /* defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE) */
    IRQ_current_index = ItId;
    /* Check interrupt index */
    if (ItId <= GIC_HIGHEST_INTERRUPT_VALUE)
    {
      /* Check validity of interrupt index */
      if (ItId >= MAX_IRQ_n)
      {
        IRQHandlingError = ERROR_IRQ_IDX_OUT_OF_RANGE;
        SystemInit_IRQ_ErrorHandler();
      }
      else
      {
        /* Clear pending interrupt at GIC400 input,  */
        /* if it is in edge triggering mode to allow */
        /* source to send another.                   */
        if (IRQ_MODE_TRIG_EDGE == IRQ_GetMode(ItId))
        {
          IRQ_ClearPending(ItId);
        }
        /* Get and check corresponding interrupt handler */
        handler = IRQ_GetHandler(ItId);
        if (handler != (IRQHandler_t)Default_ITHandler)
        {
          /* Call IRQ Handler */
          handler();
        }
        else
        {
          /* Not configured handler case --> error ! */
          IRQHandlingError = ERROR_UNDEFINED_IRQ_HANDLER;
          SystemInit_IRQ_ErrorHandler();
        }
        /* Clear pending interrupt at GIC400 input,   */
        /* if it is in level triggering mode to allow */
        /* source to send another.                    */
        if (IRQ_MODE_TRIG_LEVEL == IRQ_GetMode(ItId))
        {
          IRQ_ClearPending(ItId);
        }
      }
      /* Complete processing of acknowledged interrupt */
#if defined(CR_CMSIS_IT_GROUP_MANAGEMENT) || defined(WA_CMSIS_ISSUE_IRQ_GETACTIVE)
      newIRQ_EndOfInterrupt(current_interrupt_infos[core_idx]);
#else
      IRQ_EndOfInterrupt(ItId);
#endif /* CR_CMSIS_IT_GROUP_MANAGEMENT */
    }
    else
    {
      /* Normal case: whenever there is no more pending interrupt, */
      /* IAR returns ACKNOWLEDGE special IRQ value */
      if (ItId == GIC_ACKNOWLEDGE_RESPONSE)
      {
        break;
      }
      /* Spurious IRQ Value (1022)  ... */
      else
      {
        IRQHandlingError = ERROR_SPURIOUS_IRQ;
        SystemInit_IRQ_ErrorHandler();
      }
    }
#ifdef DEBUG_PPI2x
    IRQ_count += 1;
#endif /* DEBUG_PPI2x */
  }
  Processing_IRQ_flag = 0;
}

/**
  * @brief  Generic FIQ Handler for (secure) SGI, PPI & SPI interrupts
  *         routed on FIQ line from GIC400 to CPU
  * @param  None
  * @retval None
  */
void __attribute__ ((interrupt ("FIQ")))FIQ_Handler(void)
{
  uint32_t ItId;
  IRQHandler_t handler;
#ifdef CR_CMSIS_IT_GROUP_MANAGEMENT
  uint32_t core_idx;
#endif /* CR_CMSIS_IT_GROUP_MANAGEMENT */

  /* Process all pending interrupts on FIQ line */
  Processing_FIQ_flag = 1;
  while (1)
  {
#ifdef CR_CMSIS_IT_GROUP_MANAGEMENT
    /* Get core index by reading MPIDR bits [3:0] */
    __asm volatile("MRC p15, 0, %0, c0, c0, 5"   :"=r" (core_idx) : /* no input regs */ : /* no clobbered regs */);
    core_idx = core_idx & 0xF;

    /* Get current pending interrupt infos */
    current_interrupt_infos[core_idx] = newIRQ_GetActiveInterrupt();
    ItId = current_interrupt_infos[core_idx].id;
#else
    /* Get highest pending interrupt index from GIC driver */
    ItId = IRQ_GetActiveIRQ();
#endif /* CR_CMSIS_IT_GROUP_MANAGEMENT */
    FIQ_current_index = ItId;

    if (ItId <= GIC_HIGHEST_INTERRUPT_VALUE) /* Highest value of GIC valid interrupt */
    {
      /* Check validity of IRQ */
      if (ItId >= MAX_IRQ_n)
      {
        IRQHandlingError = ERROR_IRQ_IDX_OUT_OF_RANGE;
        SystemInit_IRQ_ErrorHandler();
      }
      else
      {
        /* Clear pending interrupt at GIC400 input,  */
        /* if it is in edge triggering mode to allow */
        /* source to send another.                   */
        if (IRQ_MODE_TRIG_EDGE == IRQ_GetMode(ItId))
        {
          IRQ_ClearPending(ItId);
        }

        /* Get and check corresponding interrupt handler */
        handler = IRQ_GetHandler(ItId);
        if (handler != (IRQHandler_t)Default_ITHandler)
        {
          /* Call interrupt handler */
          handler();
        }
        else
        {
          /* Not configured handler case --> error ! */
          IRQHandlingError = ERROR_UNDEFINED_IRQ_HANDLER;
          SystemInit_IRQ_ErrorHandler();
        }
        /* Clear pending interrupt at GIC400 input,   */
        /* if it is in level triggering mode to allow */
        /* source to send another.                    */
        if (IRQ_MODE_TRIG_LEVEL == IRQ_GetMode(ItId))
        {
          IRQ_ClearPending(ItId);
        }
      }
      /* Complete processing of acknowledged interrupt */
#ifdef CR_CMSIS_IT_GROUP_MANAGEMENT
      newIRQ_EndOfInterrupt(current_interrupt_infos[core_idx]);
#else
      IRQ_EndOfInterrupt(ItId);
#endif /* CR_CMSIS_IT_GROUP_MANAGEMENT */
    }
    else
    {
      /* Normal case: whenever there is no more pending IRQ , IAR returns ACKNOWLEDGE special IRQ value */
      if (ItId == GIC_ACKNOWLEDGE_RESPONSE)
      {
        break;
      }
      /* Spurious IRQ Value (1022)  ... */
      else
      {
        IRQHandlingError = ERROR_SPURIOUS_IRQ;
        SystemInit_IRQ_ErrorHandler();
      }
    }
#ifdef DEBUG_PPI2x
    FIQ_count += 1;
#endif /* DEBUG_PPI2x */
  }
  Processing_FIQ_flag = 0;
}

/**
  * @brief  Ensure all BSS part of code is initialized with zeros
  * @param  None
  * @retval None
  */
void __attribute__((noinline)) ZeroBss(void)
{
    __asm volatile(
      "PUSH {R4-R11}          \n"
      "LDR r2, =ZI_DATA       \n"
      "b LoopFillZerobss      \n"
      /* Zero fill the bss segment. */
      "FillZerobss:           \n"
      "MOVS r3, #0            \n"
      "STR  r3, [r2]          \n"
      "adds r2, r2, #4        \n"

      "LoopFillZerobss:       \n"
      "LDR r3, = __BSS_END__  \n"
      "CMP r2, r3             \n"
      "BCC FillZerobss        \n"

      "DSB                    \n"
      "POP    {R4-R11}        "
    );
}

/**
  * @brief  Initialize Processor : FPU, vector table, ...
  *         IMPORTANT ! IMPLEMENTED TO BE RUN IN SECURE STATE ONLY
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  /* Fill BSS Section with '0' */
  ZeroBss();

#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  /* Enable FPU */
  __FPU_Enable();
#endif

#ifdef MMU_USE
  /* Create Translation Table */
#ifdef LPAE_USE
  MMU_CreateTranslationTable_LPAE();
#else /* LPAE_USE */
  MMU_CreateTranslationTable();
#endif /* LPAE_USE */

  /* Enable MMU */
  MMU_Enable();
#endif /* MMU_USE */

#ifdef CACHE_USE
  /* Enable Caches */
  L1C_EnableCaches();
  L1C_EnableBTAC();
#endif /* CACHE_USE */

#if (__GIC_PRESENT == 1)
  uint32_t i;

  /* Initialize GIC400 and interrupts by using default CMSIS settings */
  IRQ_Initialize();

  /****************************************************************************/
  /* !!! WARNING !!!                                                          */
  /* GIC400 is used on MP2 for routing interrupts to A35 cores.               */
  /* On May 2019, CMSIS latest version 5.5.1 still doesn't support Axx cores  */
  /* based on ARMv8-A architecture, and GIC driver still support only         */
  /* one group of interrupts (No Security Extension case).                    */
  /*                                                                          */
  /* For validation reasons, in present "CMSIS Device ST STM32MP2",           */
  /* we've chosen to manage interrupts by allocating secure ones to FIQ line  */
  /* and non-secure ones to IRQ line (see #3.9.1 in [ARM IHI 0048B]).         */
  /* This means, that we have not only to configure GIC400 in a specific way, */
  /* but also to handle pending interrupts by using functions other than      */
  /* the ones available in latest "CMSIS Core_A".                             */
  /* Otherwise, we've decided to use same interrupt handler table             */
  /* (the one set within "CMSIS Core_A" for IRQ and FIQ interrupt handling.   */
  /* (see implementation of IRQ_Handler and FIQ_Handler vectors)              */
  /****************************************************************************/
  /* Tune GIC400 configuration in a specific way :                       */
  /* - Disable Priority Masking by setting GICC_PMR with a secure access */
  /*   to its highest value (see #4.4.2 in [ARM IHI 0048B])              */
#if defined(A35_NON_SECURE)
  a35ns_call_el3_monitor( CMD_WRITE_DATA, (uint32_t)&GICInterface->PMR,
                          0x000000FFUL, UNUSED_PARAM );
#else
  IRQ_SetPriorityMask(0xFFU);
#endif /* defined(A35_NON_SECURE) */

  /* - Disable Sub-Priority by setting GICC_BPR value according to       */
  /*   GIC_PRIO_BITS value (see #4.4.3 and Table 3-7 in [ARM IHI 0048B]) */
  IRQ_SetPriorityGroupBits(GIC_PRIO_BITS);

  /* On A35 secure cores,                                              */
#if !defined(A35_NON_SECURE)
  /* - Secure (aka "Group0") interrupts are routed on FIQ line,        */
  /* - Non-secure (aka "Group1") interrupts are routed on IRQ line.    */
  /*  (see #3.4 in [ARM IHI 0048B])                                    */
  /*  . by setting GICD_CTLR accordingly                               */
  /*    => "EnableGrp0" + "EnableGrp1" (see #4.3.1 in [ARM IHI 0048B]) */
  GICDistributor->CTLR = 3U;
  /*  . by setting secure GICC_CTLR (for current core) accordingly     */
  /*    => "EnableGrp0" + "EnableGrp1" + "FIQEn" + "CBPR"              */
  /*      (see #4.4.1 Table 4-31 in [ARM IHI 0048B])                   */
  GICInterface->CTLR = 0x1B;
  /* On A35 non-secure cores,                                          */
#else
  /* - Non-secure (aka "Group1") interrupts are routed on IRQ line.    */
  /*  (see #3.4 in [ARM IHI 0048B])                                    */
  /*  . by setting non-secure GICD_CTLR accordingly                    */
  /*    => "Enable" (see #4.3.1 in [ARM IHI 0048B])                    */
  GICDistributor->CTLR = 1U;
  /*  . by setting non-secure GICC_CTLR (for current core) accordingly */
  /*    => bit 0 "Enable" (see #4.4.1 Table 4-30 in [ARM IHI 0048B])   */
  GICInterface->CTLR = 1U;
#endif /* !defined(A35_NON_SECURE) */

  /* Copy table of interrupt handlers into CMSIS Core_A reference one */
  for (i = 0U; i < MAX_IRQ_n ; i++)
  {
    IRQ_SetHandler(i, Interrupt_Handlers_Table[i]);
  }
#endif
  return;
}

typedef struct
{
  uint32_t PLLSource;   /*!< The new source of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Clock_Source                */
  uint8_t  PLLState;    /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_State                       */
  uint8_t  FREFDIV;
  uint16_t FBDIV;
  uint32_t FRACIN;
  uint32_t POSTDIV1;
  uint32_t POSTDIV2;
} PLLInitTypeDef;

static void GetPLLxConfig(PLLInitTypeDef  *pll_config, uint32_t PLL_num)
{
  switch (PLL_num)
  {
    case 1:
      pll_config->PLLState = ((CA35SSC->PLL_ENABLE_RW & CA35SSC_PLL_ENABLE_RW_PLL_EN) == CA35SSC_PLL_ENABLE_RW_PLL_EN ? RCC_PLL_ON : RCC_PLL_OFF);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL5_Msk) >> RCC_MUXSELCFGR_MUXSEL5_Pos;
      pll_config->FREFDIV = (CA35SSC->PLL_FREQ1_RW & CA35SSC_PLL_FREQ1_RW_REFDIV_Msk) >> CA35SSC_PLL_FREQ1_RW_REFDIV_Pos;
      pll_config->FBDIV = (CA35SSC->PLL_FREQ1_RW & CA35SSC_PLL_FREQ1_RW_FBDIV_Msk) >> CA35SSC_PLL_FREQ1_RW_FBDIV_Pos;
      pll_config->FRACIN = 0;
      pll_config->POSTDIV1 = (CA35SSC->PLL_FREQ2_RW & CA35SSC_PLL_FREQ2_RW_POSTDIV1_Msk) >> CA35SSC_PLL_FREQ2_RW_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (CA35SSC->PLL_FREQ2_RW & CA35SSC_PLL_FREQ2_RW_POSTDIV2_Msk) >> CA35SSC_PLL_FREQ2_RW_POSTDIV2_Pos;
      break;
    case 4:
      pll_config->PLLState = ((RCC->PLL4CFGR1 & RCC_PLL4CFGR1_PLLEN) == RCC_PLL4CFGR1_PLLEN ? RCC_PLL_ON : RCC_PLL_OFF);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (RCC->PLL4CFGR2 & RCC_PLL4CFGR2_FREFDIV_Msk) >> RCC_PLL4CFGR2_FREFDIV_Pos;
      pll_config->FBDIV = (RCC->PLL4CFGR2 & RCC_PLL4CFGR2_FBDIV_Msk) >> RCC_PLL4CFGR2_FBDIV_Pos;
      pll_config->FRACIN = (RCC->PLL4CFGR3 & RCC_PLL4CFGR3_FRACIN_Msk) >> RCC_PLL4CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL4CFGR6 & RCC_PLL4CFGR6_POSTDIV1_Msk) >> RCC_PLL4CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL4CFGR7 & RCC_PLL4CFGR7_POSTDIV2_Msk) >> RCC_PLL4CFGR7_POSTDIV2_Pos;
      break;
    case 5:
      pll_config->PLLState = ((RCC->PLL5CFGR1 & RCC_PLL5CFGR1_PLLEN) == RCC_PLL5CFGR1_PLLEN ? RCC_PLL_ON : RCC_PLL_OFF);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (RCC->PLL5CFGR2 & RCC_PLL5CFGR2_FREFDIV_Msk) >> RCC_PLL5CFGR2_FREFDIV_Pos;
      pll_config->FBDIV = (RCC->PLL5CFGR2 & RCC_PLL5CFGR2_FBDIV_Msk) >> RCC_PLL5CFGR2_FBDIV_Pos;
      pll_config->FRACIN = (RCC->PLL5CFGR3 & RCC_PLL5CFGR3_FRACIN_Msk) >> RCC_PLL5CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL5CFGR6 & RCC_PLL5CFGR6_POSTDIV1_Msk) >> RCC_PLL5CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL5CFGR7 & RCC_PLL5CFGR7_POSTDIV2_Msk) >> RCC_PLL5CFGR7_POSTDIV2_Pos;
      break;
    case 6:
      pll_config->PLLState = ((RCC->PLL6CFGR1 & RCC_PLL6CFGR1_PLLEN) == RCC_PLL6CFGR1_PLLEN ? RCC_PLL_ON : RCC_PLL_OFF);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (RCC->PLL6CFGR2 & RCC_PLL6CFGR2_FREFDIV_Msk) >> RCC_PLL6CFGR2_FREFDIV_Pos;
      pll_config->FBDIV = (RCC->PLL6CFGR2 & RCC_PLL6CFGR2_FBDIV_Msk) >> RCC_PLL6CFGR2_FBDIV_Pos;
      pll_config->FRACIN = (RCC->PLL6CFGR3 & RCC_PLL6CFGR3_FRACIN_Msk) >> RCC_PLL6CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL6CFGR6 & RCC_PLL6CFGR6_POSTDIV1_Msk) >> RCC_PLL6CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL6CFGR7 & RCC_PLL6CFGR7_POSTDIV2_Msk) >> RCC_PLL6CFGR7_POSTDIV2_Pos;
      break;
    case 7:
      pll_config->PLLState = ((RCC->PLL7CFGR1 & RCC_PLL7CFGR1_PLLEN) == RCC_PLL7CFGR1_PLLEN ? RCC_PLL_ON : RCC_PLL_OFF);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (RCC->PLL7CFGR2 & RCC_PLL7CFGR2_FREFDIV_Msk) >> RCC_PLL7CFGR2_FREFDIV_Pos;
      pll_config->FBDIV = (RCC->PLL7CFGR2 & RCC_PLL7CFGR2_FBDIV_Msk) >> RCC_PLL7CFGR2_FBDIV_Pos;
      pll_config->FRACIN = (RCC->PLL7CFGR3 & RCC_PLL7CFGR3_FRACIN_Msk) >> RCC_PLL7CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL7CFGR6 & RCC_PLL7CFGR6_POSTDIV1_Msk) >> RCC_PLL7CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL7CFGR7 & RCC_PLL7CFGR7_POSTDIV2_Msk) >> RCC_PLL7CFGR7_POSTDIV2_Pos;
      break;
    case 8:
      pll_config->PLLState = ((RCC->PLL8CFGR1 & RCC_PLL8CFGR1_PLLEN) == RCC_PLL8CFGR1_PLLEN ? RCC_PLL_ON : RCC_PLL_OFF);
      pll_config->PLLSource = (RCC->MUXSELCFGR & RCC_MUXSELCFGR_MUXSEL0_Msk) >> RCC_MUXSELCFGR_MUXSEL0_Pos;
      pll_config->FREFDIV = (RCC->PLL8CFGR2 & RCC_PLL8CFGR2_FREFDIV_Msk) >> RCC_PLL8CFGR2_FREFDIV_Pos;
      pll_config->FBDIV = (RCC->PLL8CFGR2 & RCC_PLL8CFGR2_FBDIV_Msk) >> RCC_PLL8CFGR2_FBDIV_Pos;
      pll_config->FRACIN = (RCC->PLL8CFGR3 & RCC_PLL8CFGR3_FRACIN_Msk) >> RCC_PLL8CFGR3_FRACIN_Pos;
      pll_config->POSTDIV1 = (RCC->PLL8CFGR6 & RCC_PLL8CFGR6_POSTDIV1_Msk) >> RCC_PLL8CFGR6_POSTDIV1_Pos;
      pll_config->POSTDIV2 = (RCC->PLL8CFGR7 & RCC_PLL8CFGR7_POSTDIV2_Msk) >> RCC_PLL8CFGR7_POSTDIV2_Pos;
      break;
    default:
      pll_config->PLLState = 0;
      pll_config->PLLSource = 0;
      pll_config->FREFDIV = 0;
      pll_config->FBDIV = 0;
      pll_config->FRACIN = 0;
      pll_config->POSTDIV1 = 0;
      pll_config->POSTDIV2 = 0;
      break;
  }
}

static uint32_t ComputePLLClockFreq(PLLInitTypeDef *pll)
{
  uint32_t source_freq;
  uint64_t pll_output;

#if defined(USE_STM32MP257CXX_FPGA) || defined (USE_STM32MP215FXX_FPGA)
  source_freq = 32000000UL;
#else /* USE_STM32MP257CXX_FPGA */
  switch (pll->PLLSource)
  {
    case 0 : /* HSI */
      source_freq = HSI_VALUE;
      break;
    case 1 : /* HSE */
      source_freq = HSE_VALUE;
      break;
    case 2 : /* MSI */
      source_freq = MSI_VALUE;
      break;
    default:
      source_freq = 0;
      break;
  }
#endif /* else USE_STM32MP257CXX_FPGA || USE_STM32MP215FXX_FPGA*/

  /* Compute PLL frequency from PLL parameters according to fractional mode selection */
  /* Note : keep maximum computing precision by doubling integer resolution */
  /*        and process numerator before applying dividers */
  if (0 == pll->FRACIN)
    pll_output = (uint64_t)source_freq * (uint64_t)pll->FBDIV;
  else
  {
    pll_output = (uint64_t)source_freq * ((1<<24)*(uint64_t)pll->FBDIV + (uint64_t)pll->FRACIN);
    pll_output /= (1<<24);
  }
  pll_output /= (uint64_t)(pll->FREFDIV * pll->POSTDIV1 * pll->POSTDIV2);

  return (uint32_t)pll_output;
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the Cortex-A35 clock.
  *         This clock can be ck_cpu1_ext2f, ck_cpu1_ext2f/2 or PLL1
  *         CAUTION: A35 SYSTICK is not based on the clock of Cortex-A35.
  *           It is based on STGEN IP which has it is own clock
  *           (ck_ker_stgen flexgen channel) based on HSI by default
  *
  * @note   Each time the Cortex-A35 clock changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t        xbar_source;
  uint32_t        xbar_source_freq;
  PLLInitTypeDef  pll_config;
  uint32_t        source_clock;

  /* Check CA35 source (can be EXT2F or PLL1) */
  source_clock = CA35SSC->CHGCLKREQ_RW & CA35SSC_CHGCLKREQ_RW_ARM_CHGCLKREQ;

  if (source_clock == 0)
  {
    /* Return PLL1 frequency */
    GetPLLxConfig(&pll_config, 1);
    SystemCoreClock = ComputePLLClockFreq(&pll_config);
  }
  else
  {
    /* Identify xbar source for ck_cpu1_ext2f flexgen channel (channel 63) */
    xbar_source = (uint32_t)(READ_BIT(RCC->XBARxCFGR[63], RCC_XBARxCFGR_XBARxSEL_Msk));

    /* Then retrieve the source frequency */
    switch (xbar_source)
    {
      case 0: /* PLL4 */
        GetPLLxConfig(&pll_config, 4);
        xbar_source_freq = ComputePLLClockFreq(&pll_config);
        break;

      case 1 : /* PLL5 */
        GetPLLxConfig(&pll_config, 5);
        xbar_source_freq = ComputePLLClockFreq(&pll_config);
        break;

      case 2 :/* PLL6 */
        GetPLLxConfig(&pll_config, 6);
        xbar_source_freq = ComputePLLClockFreq(&pll_config);
        break;

      case 3 : /* PLL7 */
        GetPLLxConfig(&pll_config, 7);
        xbar_source_freq = ComputePLLClockFreq(&pll_config);
        break;

      case 4 : /* PLL8 */
        GetPLLxConfig(&pll_config, 8);
        xbar_source_freq = ComputePLLClockFreq(&pll_config);
        break;

      case 5 : /* HSI */
      case 8 : /* HSI_KER */
        xbar_source_freq = HSI_VALUE;
        break;

      case 7 : /* MSI */
      case 10 : /* MSI_KER */
        xbar_source_freq = MSI_VALUE;
        break;

      case 6 : /* HSE */
      case 9 : /* HSE_KER */
        xbar_source_freq = HSE_VALUE;
        break;

      case 13 : /* LSI */
        xbar_source_freq = LSI_VALUE;
        break;

      case 14 : /* LSE */
        xbar_source_freq = LSE_VALUE;
        break;

      default:
        xbar_source_freq = 0;
        break;
    }

    SystemCoreClock = xbar_source_freq / (((RCC->FINDIVxCFGR[63] & RCC_FINDIVxCFGR_FINDIVx_Msk) + 1) * ((RCC->PREDIVxCFGR[63] & RCC_PREDIVxCFGR_PREDIVx_Msk) + 1));
    if ((CA35SSC->CHGCLKREQ_RW & CA35SSC_CHGCLKREQ_RW_ARM_DIVSELACK) != CA35SSC_CHGCLKREQ_RW_ARM_DIVSELACK)
    {
      SystemCoreClock /= 2;
    }
  }
}

__weak void SecurePhysicalTimer_IRQHandler_CallBack(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the SecurePhysicalTimer_IRQHandler_CallBack could be implemented in the user file
   */
}

void SecurePhysicalTimer_IRQHandler(void)
{
   /* Reload Timer according to elapsed time since IT was triggered */
   /***************************************************************************/
   /* WARNING ! Some adjustment may be needed to be more accurate on applying */
   /*           timer period value by taking into account time deviation      */
   /*           between reading CNTP_TVAL value and setting it back           */
   /*           to its computed corrected value.                              */
   /* NOTE : In DEBUG_TIMER mode, a time deviation is added to write          */
   /*        the corrected value in a readable variable.                      */
   /***************************************************************************/
#ifdef DEBUG_TIMER
   RELOAD_VAL = TimerPeriod + PL1_GetCurrentValue();
   PL1_SetLoadValue(RELOAD_VAL);
#else
   PL1_SetLoadValue(TimerPeriod + PL1_GetCurrentValue());
#endif
   /* Increment Tick value and call user CB */
   HAL_IncTick();
   SecurePhysicalTimer_IRQHandler_CallBack();
#ifdef DEBUG_PPI2x
   /* Debug mode : Increment PPI29 counter */
   PPI29_count += 1;
#endif

   return;
}

__weak void NonSecurePhysicalTimer_IRQHandler_CallBack(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the NonSecurePhysicalTimer_IRQHandler_CallBack could be implemented in the user file
   */
}

void NonSecurePhysicalTimer_IRQHandler(void)
{
   /* Reload Timer according to elapsed time since IT was triggered */
   /***************************************************************************/
   /* WARNING ! Some adjustment may be needed to be more accurate on applying */
   /*           timer period value by taking into account time deviation      */
   /*           between reading CNTP_TVAL value and setting it back           */
   /*           to its computed corrected value.                              */
   /* NOTE : In DEBUG_TIMER mode, a time deviation is added to write          */
   /*        the corrected value in a readable variable.                      */
   /***************************************************************************/
   /* WARNING ! In Aarch32, Non-secure physical timer is only reachable */
   /*           by A35 core in non-secure state. */
#ifdef DEBUG_TIMER
   RELOAD_VAL = TimerPeriod + PL1_GetCurrentValue();
   PL1_SetLoadValue(RELOAD_VAL);
#else
   PL1_SetLoadValue(TimerPeriod + PL1_GetCurrentValue());
#endif
   /* Increment Tick value and call user CB */
   HAL_IncTick();
   NonSecurePhysicalTimer_IRQHandler_CallBack();

#ifdef DEBUG_PPI2x
   /* Debug mode : Increment PPI30 counter */
   PPI30_count += 1;
#endif

   return;
}

__weak void VirtualTimer_IRQHandler_CallBack(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the VirtualTimer_IRQHandler_CallBack could be implemented in the user file
   */
}
void VirtualTimer_IRQHandler(void)
{
   /* Reload Timer according to elapsed time since IT was triggered */
   /***************************************************************************/
   /* WARNING ! Some adjustment may be needed to be more accurate on applying */
   /*           timer period value by taking into account time deviation      */
   /*           between reading CNTV_TVAL value and setting it back           */
   /*           to its computed corrected value.                              */
   /* NOTE : In DEBUG_TIMER2 mode, a time deviation is added to write         */
   /*        the corrected value in a readable variable.                      */
   /***************************************************************************/
#ifdef DEBUG_TIMER2
   RELOAD_VAL2 = TimerPeriod + VL1_GetCurrentTimerValue();
   VL1_SetCurrentTimerValue(RELOAD_VAL2);
#else
   VL1_SetCurrentTimerValue(TimerPeriod + VL1_GetCurrentTimerValue());
#endif
   /* Increment Tick value and call user CB */
   HAL_IncTick();
   VirtualTimer_IRQHandler_CallBack();

#ifdef DEBUG_PPI2x
   /* Debug mode : Increment PPI27 counter */
   PPI27_count += 1;
#endif

   return;
}

/**
    @verbatim
    ==============================================================================
    *** How to configure SysTick, a system timestamp, equivalent to the one
    *** set by HAL CORTEX on M33 by using present SYSTEM A35 driver
    ==============================================================================
    [..]
    Setup Secure/Non-secure Physical Timer or Virtual Timer as a timebase.

    (+) The SystemA35_SYSTICK_TimerSourceConfig() function permits to select
        among different timer source to clock A35 SysTick :
        (++) Secure/Non-secure Physical Timer
        (++) Virtual Timer

   (+) The SystemA35_SYSTICK_Config() function calls the Cortex-A CMSIS
       and Device-ST CMSIS functions to :
        (++) Clock and starts the System Timestamp Generator (STGEN) (in secure mode only)
        (++) Configures the selected Timer with value passed as function parameter
        (++) Configures the selected Timer IRQ priority to the lowest value
        (++) Enables the select Timer Interrupt

   (+) You can change the selected Timer IRQ priority by calling the
       IRQ_SetPriority(SecurePhysicalTimer_IRQn, ...) or IRQ_SetPriority(NonSecurePhysicalTimer_IRQn, ...)
       or IRQ_SetPriority(VirtualTimer_IRQn, ...)
       function just after the SystemA35_SYSTICK_Config() function call.

   (+) To adjust selected Timer as a timebase, use the following formula:

       Period Value = System Timestamp Generator Clock (Hz) x Desired Timebase (s)
       (++) Period Value is the parameter to be passed to SystemA35_SYSTICK_Config() function
       (++) Period Value should not exceed 0x7FFFFFFF
  @endverbatim
  ******************************************************************************/

/**
  * @brief  xxx
  *
  * @note   xxx
  *
  * @param  xxx
  * @retval xxx
  */

/******** FUNCTIONS FOR SECURE STATE ONLY ********/

/**************************************************************/
/* WARNING ! STGENC IS ONLY ACCESSIBLE BY A35 IN SECURE STATE */
/**************************************************************/
uint32_t SystemA35_TZ_STGEN_Start( uint32_t ck_ker_clk_freq )
{
   uint32_t reg_val;

   /* CHECK SECURE STATE : NOT IMPLEMENTED YET ! */

   /* Start Timestamp generator */
   /* (clock source of A35 secure/non-secure physical timers) */
   /* - if it has not been done already, enable STGENRW/STGENRO clock */
   /*   by setting RCC_STGENCFGR bit 1 "STGENEN" */
   if ((RCC->STGENCFGR & 0x2) != 0x2)
   {
      reg_val = RCC->STGENCFGR | 0x2;
      RCC->STGENCFGR = reg_val;
   }

   /* Set STGEN frequency value in dedicated register */
   STGENC->CNTFID0 = ck_ker_clk_freq;

   /* Set DBGMCU_CRA35 to halt timestamp generation on debug */
   /* by setting its bit 1 "DBG_STGEN_STOP" */
   DBGMCU->CRA35 |= DBGMCU_CRA35_DBG_STGEN_STOP;

   /* - if it has not been done already, start STGENC */
   /*   by setting CNTCR bit 0 "EN" */
   /*   and bit 1 "HDBG" (to halt timestamp generation on debug) */
   if ((STGENC->CNTCR & 0x3) != 0x3)
   {
      reg_val = STGENC->CNTCR | 0x3;
      STGENC->CNTCR = reg_val;
   }
   return 0;
}

uint32_t SystemA35_TriggerInterruptAtGICInput( gic_interrupt_config_t interrupt_config )
{
   uint32_t gicd_regval, line;
   uint32_t gicd_reg_idx;

   /* Force interrupt by software action at GIC400 input according to interrupt index : */
   line = interrupt_config.it_idx;
   /* . SGI case : */
   if (line <= SGI15_IRQn)
   {
      /* Set GICD_SGIR (see #4.3.15 in [ARM IHI 0048B]) according to : */
      /* - selected interrupt index */
      gicd_regval = line & 0xF;
      /* - selected CPU target list */
      /*   by setting "TargetListFilter" bits [25:24] to 0b00      */
      /*   and by setting "CPUTargetList" bits [23:16] accordingly */
      gicd_regval |= (interrupt_config.it_a35_targets & 0xFFUL) << 16U;
      /* - selected security mode */
      /*   NB : In CMSIS v5.5.1, "CMSIS Core_A" functions GIC_SendSGI()         */
      /*        and GIC_SetPendingIRQ() don't take into account security mode ! */
      /* - in non-secure case, */
      if (A35_IT_NON_SECURE == interrupt_config.it_security_mode)
      {
      /*   set GICD_SGIR "NSATT" bit 15 set to 1  */
         gicd_regval |= 0x1 << 15;
      }
      /* - in secure case, set GICD_SGIR "NSATT" bit 15 set (let) to 0 */
      /* Send SGI by writing GICD_SGIR register */
      GICDistributor->SGIR = gicd_regval;
      /* Complete SGI sending by writing GICD_SPENDSGIRn register ? */
      /* (see #4.3.17 in [ARM IHI 0048B]) */
      /* TO BE IMPLEMENTED ? */
   }
   /* . PPI and SPI cases : */
   /*   Set GICD_ISPENDRn register (see #4.3.7 in [ARM IHI 0048B]) */
   else if (line < MAX_IRQ_n)
   {
       /* According to selected interrupt index by : */
       /* - computing GICD_ISPENDRn register index   */
       gicd_reg_idx = line >> 5;
       /* - computing GICD_ISPENDRn register value   */
       gicd_regval = 1 << (line & 0x1f);
       /* Send PPI/SPI by writing GICD_ISPENDRn register */
       GICDistributor->ISPENDR[gicd_reg_idx] = gicd_regval;
   }
   return 0;
}

/* Retrieve A35 secure state by reading registers GICC_ABPR */
/* (see #4.4.8 in [ARM IHI 0048B])                          */
uint32_t SystemA35_IsA35InSecureState( void )
{
   uint32_t secure_flag = 0xDEADBEEF;

   if (0 == GICInterface->ABPR)
   {
       secure_flag = 0;
   }
   else
   {
       secure_flag = 1;
   }
   return secure_flag;
}

uint32_t SystemA35_RouteInterrupt( gic_interrupt_config_t interrupt_config )
{
   uint32_t gicd_priority_val, priority_left_shifting = 0;
   uint32_t mode_config_for_gicd_settings;
   uint32_t f_status = 0;

   /* Check input parameters [TO BE DONE] to set output status */
   /* - it_idx           : interrupt index in range [0;Max_IRQn] */
   /* - it_priority      : interrupt priority in range [0;(1<<(GIC_PRIO_BITS-1))-1] */
   /*                      A shift of one-bit left will be applied in non-secure interrupt case */
   /* - it_trigger_mode  : interrupt trigger mode check done by IRQ_SetMode function */
   /* - it_security_mode : interrupt security mode among {A35_IT_SECURE; A35_IT_NON_SECURE} */
   /* - it_a35_targets   : A35 CPU target among {IT_TARGETS_A35_0; IT_TARGETS_A35_1; IT_TARGETS_A35_X} */

   /* Disable selected interrupt */
   IRQ_Disable(interrupt_config.it_idx);
   /* Clear pending selected interrupt */
   IRQ_ClearPending(interrupt_config.it_idx);

   /* Set interrupt request mode */
   /* according to selected trigger mode, security mode and A35 CPU target */
   /* and by setting interrupt type to IRQ_MODE_TYPE_IRQ (to pass IRQ_SetMode checks) */
   /* - IRQ_MODE_TRIG bits[2:0] */
   mode_config_for_gicd_settings = interrupt_config.it_trigger_mode & IRQ_MODE_TRIG_Msk;
   /* - IRQ_MODE_TYPE bit 3 */
   mode_config_for_gicd_settings &= ~IRQ_MODE_TYPE_Msk;
   mode_config_for_gicd_settings |= IRQ_MODE_TYPE_IRQ;
   /* - IRQ_MODE_DOMAIN bit 4 */
   mode_config_for_gicd_settings &= ~IRQ_MODE_DOMAIN_Msk;
   if (A35_IT_SECURE == interrupt_config.it_security_mode)
   {
      mode_config_for_gicd_settings |= IRQ_MODE_DOMAIN_SECURE;
      priority_left_shifting = 0;
   }
   else
   {
      mode_config_for_gicd_settings |= IRQ_MODE_DOMAIN_NONSECURE;
      priority_left_shifting = 1;
   }
   /* - IRQ_MODE_CPU bits [12:5] */
   mode_config_for_gicd_settings &= ~IRQ_MODE_CPU_Msk;
   if (IT_TARGETS_A35_0 == interrupt_config.it_a35_targets)
   {
      mode_config_for_gicd_settings |= IRQ_MODE_CPU_0;
   }
   else if (IT_TARGETS_A35_1 == interrupt_config.it_a35_targets)
   {
      mode_config_for_gicd_settings |= IRQ_MODE_CPU_1;
   }
   else
   {
      mode_config_for_gicd_settings |= (IRQ_MODE_CPU_0 | IRQ_MODE_CPU_1);
   }
   IRQ_SetMode(interrupt_config.it_idx, mode_config_for_gicd_settings);
#ifdef WA_CMSIS_ISSUE_IRQ_SETMODE
   /* Fix incorrect setting of register GICD_IGROUPn for current interrupt */
   FIX_SetModeIssueOnInterruptGroup(interrupt_config.it_idx, mode_config_for_gicd_settings);
#endif /* WA_CMSIS_ISSUE_IRQ_SETMODE */

   /* Set GICD priority of selected interrupt */
   /* according to input value, GIC_PRIO_BITS value and security mode */
   /* Apply "Non-cooperative" scheme for managing interrupt priority */
   /* (see #3.6.3 [ARM IHI 0048B]) */
   gicd_priority_val = interrupt_config.it_priority << (8U - GIC_PRIO_BITS);
   gicd_priority_val = gicd_priority_val << priority_left_shifting;
   IRQ_SetPriority(interrupt_config.it_idx, gicd_priority_val);

   /* Enable selected interrupt */
   IRQ_Enable(interrupt_config.it_idx);

   return f_status;
}

/* Unroute ... */
/* Managing called functions returned status : TO BE DONE LATER */
uint32_t SystemA35_UnrouteInterrupt( uint32_t interrupt_index )
{
   uint32_t gicd_priority_val;
   uint32_t mode_config_for_gicd_settings;
   uint32_t f_status = 0;

   /* Check input parameters [TO BE DONE] to set output status   */
   /* - it_idx           : interrupt index in range [0;Max_IRQn] */

   /* Disable selected interrupt */
   IRQ_Disable(interrupt_index);

   /* Reset interrupt request mode (defined in "CMSIS CORE_A")  */
   /* to default trigger mode, security mode and A35 CPU target */
   /* and by setting interrupt type to IRQ_MODE_TYPE_IRQ */
   /* (to pass IRQ_SetMode checks). */
   /* - IRQ_MODE_TRIG bits[2:0] reset to IRQ_MODE_TRIG_EDGE */
   mode_config_for_gicd_settings = IRQ_MODE_TRIG_EDGE;
   /* - IRQ_MODE_TYPE bit 3 set to IRQ_MODE_TYPE_IRQ */
   mode_config_for_gicd_settings &= ~IRQ_MODE_TYPE_Msk;
   mode_config_for_gicd_settings |= IRQ_MODE_TYPE_IRQ;
   /* - IRQ_MODE_DOMAIN bit 4 reset to IRQ_MODE_DOMAIN_SECURE */
   mode_config_for_gicd_settings &= ~IRQ_MODE_DOMAIN_Msk;
   mode_config_for_gicd_settings |= IRQ_MODE_DOMAIN_SECURE;
   /* - IRQ_MODE_CPU bits [12:5] reset to 0x00 (no CPU target) */
   mode_config_for_gicd_settings &= ~IRQ_MODE_CPU_Msk;
   IRQ_SetMode(interrupt_index, mode_config_for_gicd_settings);
#ifdef WA_CMSIS_ISSUE_IRQ_SETMODE
   /* Fix incorrect setting of register GICD_IGROUPn for current interrupt */
   FIX_SetModeIssueOnInterruptGroup(interrupt_index, mode_config_for_gicd_settings);
#endif /* WA_CMSIS_ISSUE_IRQ_SETMODE */
   /* Set GICD priority of disabled interrupt to (secure) lowest priority */
   /* according to GIC_PRIO_BITS value */
   gicd_priority_val = ((1<<(GIC_PRIO_BITS-1))-1) << (8U - GIC_PRIO_BITS);
   IRQ_SetPriority(interrupt_index, gicd_priority_val);

   return f_status;
}

/**
  * @brief  xxx
  *
  * @note   xxx
  *
  * @param  xxx
  * @retval xxx
  */

uint32_t SystemA35_SYSTICK_Config( uint32_t timer_priority )
{
   uint32_t gicd_priority_val, ref_freq_val = 0;
   IRQn_Type sourcetimer_irq;

   /* Stop Timers */
   PL1_SetControl(0x0);
   VL1_SetControl(0x0);

   /* Reset Timers */
   PL1_SetLoadValue(0);
   PL1_SetPhysicalCompareValue(0);
   VL1_SetCurrentTimerValue(0);
   VL1_SetTimerCompareValue(0);

#ifdef DEBUG_PPI2x
   FIQ_count = 0;
   IRQ_count = 0;
#endif

   /* Set Counter Frequency according to frequency of STGEN source clock */
#if defined(A35_NON_SECURE)
   ref_freq_val
      = a35ns_call_el3_monitor( CMD_READ_DATA, (uint32_t)&STGENC->CNTFID0,
                                UNUSED_PARAM, UNUSED_PARAM );
#else
   ref_freq_val = STGENC->CNTFID0;
#endif /* defined(A35_NON_SECURE) */
   if (__get_CNTFRQ() != ref_freq_val)
   {
      PL1_SetCounterFrequency(ref_freq_val);
   }
   /* Initialize Timer to get a 1ms-period */
   TimerPeriod = ref_freq_val / 1000;
   if (A35_SYSTICK_PHYSICALTIMERSOURCE == A35SysTick_TimerSource)
   {
      /* Secure vs non-secure Physical Timer case */
      /* according to Aarch32 Exception level */
      if (1 == g_isAarch32inEL3_flag)
      {
         sourcetimer_irq = SecurePhysicalTimer_IRQn;
      }
      else
      {
         sourcetimer_irq = NonSecurePhysicalTimer_IRQn;
      }
   }
   else
   {
      sourcetimer_irq = VirtualTimer_IRQn;
   }
   /* Disable corresponding IRQ */
   IRQ_Disable(sourcetimer_irq);
   IRQ_ClearPending(sourcetimer_irq);

   /* Set timer priority according to input value and GIC_PRIO_BITS value */
   gicd_priority_val = timer_priority << (8U - GIC_PRIO_BITS);
   IRQ_SetPriority(sourcetimer_irq, gicd_priority_val);

   /* Set IRQ to level-triggered mode */
   IRQ_SetMode(sourcetimer_irq, IRQ_MODE_TRIG_LEVEL);

   /* Enable corresponding interrupt */
   IRQ_Enable(sourcetimer_irq);

   /* Start and Load Timer */
   if (A35_SYSTICK_PHYSICALTIMERSOURCE == A35SysTick_TimerSource)
   {
      PL1_SetLoadValue(TimerPeriod);
      PL1_SetControl(0x1);
   }
   else
   {
      VL1_SetCurrentTimerValue(TimerPeriod);
      VL1_SetControl(0x1);
   }
   return 0;
}

uint32_t SystemA35_ManageTick( uint32_t suspend_resume_stop_tick )
{
   IRQn_Type sourcetimer_irq;
   uint32_t status = 1, tick;

   switch(A35SysTick_TimerSource)
   {
      case A35_SYSTICK_VIRTUALTIMERSOURCE :
         sourcetimer_irq = VirtualTimer_IRQn;
         break;

      case A35_SYSTICK_PHYSICALTIMERSOURCE :
      default :
         /* Secure vs non-secure Physical Timer case */
         /* according to Aarch32 Exception level */
         if (1 == g_isAarch32inEL3_flag)
         {
            sourcetimer_irq = SecurePhysicalTimer_IRQn;
         }
         else
         {
            sourcetimer_irq = NonSecurePhysicalTimer_IRQn;
         }
         break;
   }
   /* Process input command for current SysTick source */
   switch(suspend_resume_stop_tick)
   {
      case A35_RESUME_SYSTICK :
#ifdef DEBUG_PPI2x
         printf("<D> PPI27/PPI29/PPI30 counts = %ld / %ld / %ld vs Tick count = %ld vs FIQ/IRQ counts = %ld / %ld\n",
                PPI27_count, PPI29_count, PPI30_count, HAL_GetTick(), FIQ_count, IRQ_count );
#endif
         tick = HAL_GetTick();
         /* Enable corresponding interrupt */
         IRQ_Enable(sourcetimer_irq);
         /* Check & retime tick occurrence by waiting tick value to be modified */
         while (tick == HAL_GetTick()){};
         status = 0;
         break;

      case A35_STOP_SYSTICK :
         /* Stop Timers */
         PL1_SetControl(0x0);
         VL1_SetControl(0x0);
      case A35_SUSPEND_SYSTICK :
         /* Disable corresponding interrupt and clear it if pending */
         IRQ_Disable(sourcetimer_irq);
         IRQ_ClearPending(sourcetimer_irq);
#ifdef DEBUG_PPI2x
         printf("<D> PPI27/PPI29/PPI30 counts = %ld / %ld / %ld vs Tick count = %ld vs FIQ/IRQ counts = %ld / %ld\n",
                PPI27_count, PPI29_count, PPI30_count, HAL_GetTick(), FIQ_count, IRQ_count );
#endif
         status = 0;
         break;

      default :
         break;
   }
   return status;
}

uint32_t SystemA35_SYSTICK_TimerSourceConfig( uint32_t timer_source )
{
   switch(timer_source)
   {
      case A35_SYSTICK_VIRTUALTIMERSOURCE :
         A35SysTick_TimerSource = A35_SYSTICK_VIRTUALTIMERSOURCE;
         break;

      case A35_SYSTICK_PHYSICALTIMERSOURCE :
      default :
         A35SysTick_TimerSource = A35_SYSTICK_PHYSICALTIMERSOURCE;
         break;
   }
   return 0;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
