/*******************************************************************************
 * @file    system_stm32mp2xx_a35_utils.c
 * @author  C.ICORD (Intropack Team)
 * @version $VERSION$
 * @date    $DATE$
 *
 * @brief   A35 cores management functions (Aarch32 & Aarch64 modes)
 *
 * Reference documents :
 *
 * . [A35_TRM]
 *   "Arm Cortex-A35 Processor"
 *   "Technical Reference Manual / 100236_0100_00_en"
 *   Revision: r1p0 / Issue 0100-00 / 28-Feb-2019
 *   (file cortex_a35_trm_100236_0100_00_en.pdf)
 *
 * . [ARM_DDI_0487B.a] ARM Architecture Reference Manual
 *   "ARMv8, for ARMv8-A architecture profile"
 *   ARM DDI 0487B.a -- 31-March-2017
 *   (file DDI0487B_a_armv8_arm.pdf)
 *
 *******************************************************************************
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
 *******************************************************************************
 */
/* Debug specific */
//#define DEBUG
//#define DEBUG_PMU
//#define DEBUG_FREQ

#include <string.h>
#include <stdio.h>

#include <stm32mp2xx.h>
#include "core_ca.h"
#include "system_stm32mp2xx_a35_utils.h"

/* Global variables ----------------------------------------------------------*/
static uint32_t gl_cpu_freq_in_Hz = 0;

////////////////////////////////////////////////////////////////////////////////
/* Aarch32 & Aarch64 handling functions : */
/* - processor identification */
////////////////////////////////////////////////////////////////////////////////
uint32_t a35_get_core_id( void )
{
   uint32_t val_reg;

#ifdef __AARCH64__
   /* Get value of Multiprocessor Affinity Register (EL1)         */
   /* (see #D7.2.74 in [ARM DDI 0487B.a] and #B2.84 in [A35_TRM]) */
   asm volatile("MRS %0, MPIDR_EL1"   :"=r" (val_reg) : /* no input regs */ : /* no clobbered regs */);
#else
   /* Get value of Multiprocessor Affinity Register                */
   /* (see #G6.2.105 in [ARM DDI 0487B.a] and #B1.97 in [A35_TRM]) */
   asm volatile("MRC p15, 0, %0, c0, c0, 5"   :"=r" (val_reg) : /* no input regs */ : /* no clobbered regs */);
#endif /* __AARCH64__ */
   val_reg = val_reg & 0xF;
   return (val_reg);
}


////////////////////////////////////////////////////////////////////////////////
/* - security management */
////////////////////////////////////////////////////////////////////////////////
#if defined(A35_NON_SECURE)
uint32_t a35ns_call_el3_monitor( uint32_t a_command, uint32_t a_param1, 
                                 uint32_t a_param2, uint32_t a_param3 )
{
   uint32_t status;

#ifndef __AARCH64__
   asm volatile("MOV    r0, %0" : : "r" (a_command));
   asm volatile("MOV    r1, %0" : : "r" (a_param1));
   asm volatile("MOV    r2, %0" : : "r" (a_param2));
   asm volatile("MOV    r3, %0" : : "r" (a_param3));
#endif /* __AARCH64__ */

   /* Request to read the security flag : Secure monitor call #2 */
   asm volatile("SMC  #2");
#ifndef __AARCH64__
   asm volatile("MOV    %0, r0" : "=r" (status) : : );
   asm volatile("MOV    %0, r1" : "=r" (a_param1) : : );
   asm volatile("MOV    %0, r2" : "=r" (a_param2) : : );
   asm volatile("MOV    %0, r3" : "=r" (a_param3) : : );
#endif /* __AARCH64__ */

   return status;   
}
#endif /* defined(A35_NON_SECURE) */


////////////////////////////////////////////////////////////////////////////////
/* - cache management */
////////////////////////////////////////////////////////////////////////////////
bool_t a35_instruction_cache_is_enable( void )
{
   /* Get bit 12 "I" (Instruction cache) in control register */
   return (bool_t)((a35_get_sctlr() & (1<<12))>>12);
}

void a35_enable_data_cache( void )
{
   uint32_t reg_val = a35_get_sctlr();

   /* ensure all data accesses are completed */
   asm volatile("dsb sy");

   /* Set bit 2 "C" (Data cache) in control register */
   reg_val |= (1<<2);
   a35_set_sctlr(reg_val);

   return;
}

void a35_disable_data_cache( void )
{
   uint32_t reg_val = a35_get_sctlr();

   /* ensure all data accesses are completed */
   asm volatile("dsb sy");

   /* Clear bit 2 "C" (Data cache) in control register */
   reg_val &= ~(1<<2);
   a35_set_sctlr(reg_val);

   return;
}

bool_t a35_data_cache_is_enable( void )
{
   /* Get bit 2 "C" (Data cache) in control register */
   return (bool_t)((a35_get_sctlr() & (1<<2))>>2);
}

void a35_clean_data_cache( void )
{
#ifdef __AARCH64__
  asm volatile (
    "  dmb   sy                      \n\t" /* ensure ordering with previous memory accesses */
    "  mrs   x0, clidr_el1           \n\t" /* read clidr */
    "  and   x3, x0, #0x7000000      \n\t" /* extract loc from clidr */
    "  lsr   x3, x3, #23             \n\t" /* left align loc bit field */
    "  cbz   x3, c_finished          \n\t" /* if loc is 0, then no need to clean */
    "  mov   x10, #0                 \n\t" /* start clean at cache level 0 */
    "c_loop1:                        \n\t"
    "  add   x2, x10, x10, lsr #1    \n\t" /* work out 3x current cache level */
    "  lsr   x1, x0, x2              \n\t" /* extract cache type bits from clidr */
    "  and   x1, x1, #7              \n\t" /* mask of the bits for current cache only */
    "  cmp   x1, #2                  \n\t" /* see what cache we have at this level */
    "  b.lt  c_skip                  \n\t" /* skip if no cache, or just i-cache */
    "  msr   csselr_el1, x10         \n\t" /* select current cache level in csselr */
    "  isb                           \n\t" /* isb to sych the new cssr&csidr */
    "  mrs    x1, ccsidr_el1         \n\t" /* read the new ccsidr */
    "  and    x2, x1, #7             \n\t" /* extract the length of the cache lines */
    "  add    x2, x2, #4             \n\t" /* add 4 (line length offset) */
    "  mov    x4, #0x3ff             \n\t"
    "  and    x4, x4, x1, lsr #3     \n\t" /* find maximum number on the way size */
    "  clz    w5, w4                 \n\t" /* find bit position of way size increment */
    "  mov    x7, #0x7fff            \n\t"
    "  and    x7, x7, x1, lsr #13    \n\t" /* extract max number of the index size */
    "c_loop2:                        \n\t"
    "  mov    x9, x4                 \n\t" /* create working copy of max way size */
    "c_loop3:                        \n\t"
    "  lsl    x6, x9, x5             \n\t"
    "  orr    x11, x10, x6           \n\t" /* factor way and cache number into x11 */
    "  lsl    x6, x7, x2             \n\t"
    "  orr    x11, x11, x6           \n\t" /* factor index number into x11 */
    "  dc     csw, x11               \n\t" /* clean by set/way */
    "  subs   x9, x9, #1             \n\t" /* decrement the way */
    "  b.ge   c_loop3                \n\t"
    "  subs   x7, x7, #1             \n\t" /* decrement the index */
    "  b.ge   c_loop2                \n\t"
    "c_skip:                         \n\t"
    "  add    x10, x10, #2           \n\t" /* increment cache number */
    "  cmp    x3, x10                \n\t"
    "  b.gt   ci_loop1               \n\t"
    "c_finished:                     \n\t"
    "  mov    x10, #0                \n\t" /* switch back to cache level 0 */
    "  msr    csselr_el1, x10        \n\t" /* select current cache level in csselr */
    "  dsb    sy                     \n\t"
    "  isb                           \n\t"
  );
#else
//  L1C_CleanDCacheAll();
  asm volatile (
    "  PUSH   {r0-r11}               \n\t" /* Save Context */
    "  DMB                           \n\t" /* ensure ordering with previous memory accesses */
    "  MRC    p15, 1, r0, c0, c0, 1  \n\t" /* read clidr */
    "  ANDs   r3, r0, #0x7000000     \n\t" /* extract loc from clidr */
    "  MOV    r3, r3, lsr #23        \n\t" /* left align loc bit field */
    "  BEQ    c_finished             \n\t" /* if loc is 0, then no need to clean */
    "  MOV    r10, #0                \n\t" /* start clean at cache level 0 */
    "c_levels:                       \n\t"
    "  ADD    r2, r10, r10, lsr #1   \n\t" /* work out 3x current cache level */
    "  MOV    r1, r0, lsr r2         \n\t" /* extract cache type bits from clidr */
    "  AND    r1, r1, #7             \n\t" /* mask of the bits for current cache only */
    "  CMP    r1, #2                 \n\t" /* see what cache we have at this level */
    "  BLT    c_skip                 \n\t" /* skip if no cache, or just i-cache */
    "  MCR    p15, 2, r10, c0, c0, 0 \n\t" /* select current cache level in cssr */
    "  ISB                           \n\t" /* isb to sych the new cssr&csidr */
    "  MRC    p15, 1, r1, c0, c0, 0  \n\t" /* read the new csidr */
    "  AND    r2, r1, #7             \n\t" /* extract the length of the cache lines */
    "  ADD    r2, r2, #4             \n\t" /* add 4 (line length offset) */
    "  LDR    r4, =0x3ff             \n\t"
    "  ANDS   r4, r4, r1, lsr #3     \n\t" /* find maximum number on the way size */
    "  CLZ    r5, r4                 \n\t" /* find bit position of way size increment */
    "  LDR    r7, =0x7fff            \n\t"
    "  ANDS   r7, r7, r1, lsr #13    \n\t" /* extract max number of the index size */
    "c_loop1:                        \n\t"
    "  MOV    r9, r7                 \n\t" /* create working copy of max index */
    "c_loop2:                        \n\t"
    "  LSL    r6, r9, r5             \n\t"
    "  ORR    r11, r10, r6           \n\t" /* factor way and cache number into r11 */
    "  LSL    r6, r7, r2             \n\t"
    "  ORR    r11, r11, r6           \n\t" /* factor index number into r11 */
    "  MCR    p15, 0, r11, c7, c10,2 \n\t" /* clean by set/way */
    "  SUBS   r9, r9, #1             \n\t" /* decrement the index */
    "  BGE    c_loop2                \n\t"
    "  SUBS   r4, r4, #1             \n\t" /* decrement the way */
    "  BGE    c_loop1                \n\t"
    "c_skip:                         \n\t"
    "  ADD    r10, r10, #2           \n\t" /* increment cache number */
    "  CMP    r3, r10                \n\t"
    "  BGT    c_levels               \n\t"
    "c_finished:                     \n\t"
    "  MOV    r10, #0                \n\t" /* switch back to cache level 0 */
    "  MCR    p15, 2, r10, c0, c0, 0 \n\t" /* select current cache level in cssr */
    "  DSB    st                     \n\t"
    "  ISB                           \n\t"
    "  POP    {r0-r11}               \n\t" /* Restore Context */
  );
#endif /* __AARCH64__ */
  return;
}

bool_t a35_is_data_in_cached_sysram( void *ap_data )
{
#define ADDR_MASK32          0xF0000000UL
#define CACHED_SYSRAM_MASK32 0x30000000UL
   bool_t data_in_cached_sysram;

   if (((uint32_t)ap_data & ADDR_MASK32) == CACHED_SYSRAM_MASK32)
      data_in_cached_sysram = TRUE;
   else
      data_in_cached_sysram = FALSE;

   return data_in_cached_sysram;
}

////////////////////////////////////////////////////////////////////////////////
/* - memory unit (MMU) management */
////////////////////////////////////////////////////////////////////////////////
bool_t a35_memory_unit_is_enable()
{
   /* Get bit 0 "M" (Memory Management Unit) in control register */
   return (bool_t)(a35_get_sctlr() & (1<<0));
}

////////////////////////////////////////////////////////////////////////////////
/* - processor state management */
////////////////////////////////////////////////////////////////////////////////
#ifdef __AARCH64__
uint32_t a35_aa64_get_current_el( void )
{
   uint32_t reg_val;

   /* Get Current Exception Level        */
   /* (see #C5.2.1 in [ARM DDI 0487B.a]) */
   asm volatile ("MRS    %0,CurrentEL" :"=r" (reg_val));
   /* Extract EL, bits [3:2] */
   return(reg_val>>2);
}
#endif /* __AARCH64__ */


uint32_t a35_get_sctlr( void )
{
   uint32_t reg_val;
#ifdef __AARCH64__
   /* In Aarch64, read SCTLR_ELx according to current Exception Level */
   uint32_t current_el = a35_aa64_get_current_el() & 0x3UL;
   switch (current_el)
   {
      case 3 :
         /* Get Control Register for exception level 3                  */
         /* (see #D7.2.90 in [ARM DDI 0487B.a] and #B2.92 in [A35_TRM]) */
         asm volatile ("MRS    %0,SCTLR_EL3" :"=r" (reg_val));
         break;
      case 2 :
         /* Get Control Register for exception level 2                  */
         /* (see #D7.2.89 in [ARM DDI 0487B.a] and #B2.91 in [A35_TRM]) */
         asm volatile ("MRS    %0,SCTLR_EL2" :"=r" (reg_val));
         break;
      case 1 :
         /* Get Control Register for exception level 1                  */
         /* (see #D7.2.88 in [ARM DDI 0487B.a] and #B2.90 in [A35_TRM]) */
         asm volatile ("MRS    %0,SCTLR_EL1" :"=r" (reg_val));
         break;
      case 0 :
      default :
         /* NO Control Register for exception level 0 */
         reg_val = 0xDEADBEEFUL;
         break;
   }
#else
   /* In Aarch32, get Control Register SCTLR                        */
   /* (see #G6.2.118 in [ARM DDI 0487B.a] and #B1.105 in [A35_TRM]) */
   asm volatile("MRC p15, 0, %0, c1, c0, 0" : "=r"(reg_val) : : );
#endif /* __AARCH64__ */
   return(reg_val);
}

void a35_set_sctlr( uint32_t a_sctlr_val )
{
#ifdef __AARCH64__
   /* In Aarch64, write SCTLR_ELx according to current Exception Level */
   uint32_t current_el = a35_aa64_get_current_el() & 0x3UL;
   switch (current_el)
   {
      case 3 :
         /* Set Control Register for exception level 3                  */
         /* (see #D7.2.90 in [ARM DDI 0487B.a] and #B2.92 in [A35_TRM]) */
         asm volatile ("MSR    SCTLR_EL3,%0" : : "r" (a_sctlr_val) : );
         break;
      case 2 :
         /* Set Control Register for exception level 2                  */
         /* (see #D7.2.89 in [ARM DDI 0487B.a] and #B2.91 in [A35_TRM]) */
         asm volatile ("MSR    SCTLR_EL2,%0" : : "r" (a_sctlr_val) : );
         break;
      case 1 :
         /* Set Control Register for exception level 1                  */
         /* (see #D7.2.88 in [ARM DDI 0487B.a] and #B2.90 in [A35_TRM]) */
         asm volatile ("MSR    SCTLR_EL1,%0" : : "r" (a_sctlr_val) : );
         break;
      case 0 :
      default :
         /* NO Control Register for exception level 0 : do nothing */
         break;
   }
#else
   /* In Aarch32, set Control Register SCTLR                        */
   /* (see #G6.2.118 in [ARM DDI 0487B.a] and #B1.105 in [A35_TRM]) */
   asm volatile("MCR p15, 0, %0, c1, c0, 0" : : "r"(a_sctlr_val) : );
#endif /* __AARCH64__ */
   return;
}

///////////////////////////////////////////////////////////////////////////////

#if 0
/* - timer management */
uint64_t a35_get_generic_timestamp( void )
{
   uint64_t val_reg64;

   asm volatile ("MRS    %0,CNTPCT_EL0" :"=r" (val_reg64));
   return val_reg64;
}

uint32_t a35_get_generic_timestamp_lsb( void )
{
   uint64_t val_reg64;

   asm volatile ("MRS    %0,CNTPCT_EL0" :"=r" (val_reg64));
   return (uint32_t)val_reg64;
}

uint32_t a35_get_generic_timestamp_msb( void )
{
   uint64_t val_reg64;

   asm volatile ("MRS    %0,CNTPCT_EL0" :"=r" (val_reg64));
   return (uint32_t)(val_reg64>>32);
}
#endif

/* - performance monitor unit (PMU) management */
void a35_pmu_cycle_count_start( uint32_t count_div_by_64 )
{
#ifdef __AARCH64__
   uint64_t reg64_val;
#else
   uint32_t reg32_val;
#endif /* __AARCH64__ */

   /* complete all data transactions */
   asm volatile("dsb sy");

   /* configure the 64-bit cycle counter : */
   /* - reset it by setting bit 2 "C" "clock counter reset" */
#ifdef __AARCH64__
   /* . in Aarch64, via register PMCR_EL0                          */
   /*   (see #D7.4.7 in [ARM DDI 0487B.a] and #C10.6 in [A35_TRM]) */
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg64_val) : : );
   reg64_val |= (1<<2);
   asm volatile("MSR PMCR_EL0, %0" : : "r"(reg64_val) : );
#else
   /* . in Aarch32, via register PMCR                              */
   /*   (see #G6.4.9 in [ARM DDI 0487B.a] and #C10.2 in [A35_TRM]) */
   asm volatile("MRC p15, 0, %0, c9, c12, 0" : "=r"(reg32_val) : : );
   reg32_val |= (1<<2);
   asm volatile("MCR p15, 0, %0, c9, c12, 0" : : "r"(reg32_val) : );
#endif /* __AARCH64__ */
   asm volatile("isb");

#ifdef DEBUG_PMU
#ifdef __AARCH64__
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg64_val) : : );
   printf("<D> PMCR_EL0 = 0x%016llx\n", reg64_val);
#else
   asm volatile("MRC p15, 0, %0, c9, c12, 0" : "=r"(reg32_val) : : );
   printf("<D> PMCR = 0x%08x\n", reg32_val);
#endif /* __AARCH64__ */
#endif /* DEBUG_PMU */

   /* configure the 64-bit cycle counter : */
#ifdef __AARCH64__
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg64_val) : : );
#else
   asm volatile("MRC p15, 0, %0, c9, c12, 0" : "=r"(reg32_val) : : );
#endif /* __AARCH64__ */
   /* - divide 64-bit cycle counter by 64 if requested */
   if (1 == count_div_by_64)
   {
   /*   by setting bit 3 "D" "clock divider" */
#ifdef __AARCH64__
        reg64_val |= (1<<3);
#else
        reg32_val |= (1<<3);
#endif /* __AARCH64__ */
   /*   and then disable long cycle count (set overflow on 32-bit counting) */
   /*   by clearing bit 6 "LC" "Long cycle count enable" */
   /*   BECAUSE THIS BIT SETTING KILLS BIT 3 EFFECT : PMU AARCH64 BUG !!? */
#ifdef __AARCH64__
        reg64_val &= ~(1<<6);
#else
        reg32_val &= ~(1<<6);
#endif /* __AARCH64__ */
   /*   if not requested, */
   }
   else
   {
   /*   by clearing bit 3 "D" "clock divider" */
#ifdef __AARCH64__
        reg64_val &= ~(1<<3);
#else
        reg32_val &= ~(1<<3);
#endif /* __AARCH64__ */
   /*   and then enable long cycle count (set overflow on 64-bit counting) */
   /*   by setting bit 6 "LC" "Long cycle count enable" */
#ifdef __AARCH64__
        reg64_val |= (1<<6);
#else
        reg32_val |= (1<<6);
#endif /* __AARCH64__ */
   }
#ifdef __AARCH64__
   asm volatile("MSR PMCR_EL0, %0" : : "r"(reg64_val) : );
#else
   asm volatile("MCR p15, 0, %0, c9, c12, 0" : : "r"(reg32_val) : );
#endif /* __AARCH64__ */
   asm volatile("isb");

#ifdef DEBUG_PMU
#ifdef __AARCH64__
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg64_val) : : );
   printf("<D> PMCR_EL0 = 0x%016llx\n", reg64_val);
#else
   asm volatile("MRC p15, 0, %0, c9, c12, 0" : "=r"(reg32_val) : : );
   printf("<D> PMCR = 0x%08x\n", reg32_val);
#endif /* __AARCH64__ */
#endif /* DEBUG_PMU */

   /* configure the 64-bit cycle counter : */
   /* - enable all counters (cycle counter included) */
   /*   by setting bit 0 "E" "Enable" */
#ifdef __AARCH64__
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg64_val) : : );
   reg64_val |= (1<<0);
   asm volatile("MSR PMCR_EL0, %0" : : "r"(reg64_val) : );
#else
   asm volatile("MRC p15, 0, %0, c9, c12, 0" : "=r"(reg32_val) : : );
   reg32_val |= (1<<0);
   asm volatile("MCR p15, 0, %0, c9, c12, 0" : : "r"(reg32_val) : );
#endif /* __AARCH64__ */
   asm volatile("isb");

#ifdef DEBUG_PMU
#ifdef __AARCH64__
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg64_val) : : );
   printf("<D> PMCR_EL0 = 0x%016llx\n", reg64_val);
#else
   asm volatile("MRC p15, 0, %0, c9, c12, 0" : "=r"(reg32_val) : : );
   printf("<D> PMCR = 0x%08x\n", reg32_val);
#endif /* __AARCH64__ */
#endif /* DEBUG_PMU */

   /* start the cycle counter by setting bit 31 "C" of : */
#ifdef __AARCH64__
   /* - PMCNTENSET_EL0 register in Aarch64 (see #D7.4.6 in [ARM DDI 0487B.a]) */
   asm volatile("MRS %0, PMCNTENSET_EL0" : "=r"(reg64_val) : : );
   reg64_val |= (1<<31);
   asm volatile("MSR PMCNTENSET_EL0, %0" : : "r"(reg64_val) : );
#else
   /* - PMCNTENSET register in Aarch32 (see #G6.4.9 in [ARM DDI 0487B.a]) */
   asm volatile("MRC p15, 0, %0, c9, c12, 1" : "=r"(reg32_val) : : );
   reg32_val |= (1<<31);
   asm volatile("MCR p15, 0, %0, c9, c12, 1" : : "r"(reg32_val) : );
#endif /* __AARCH64__ */
   asm volatile("isb");

   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_cycle_count_stop()
{
#ifdef __AARCH64__
   uint64_t reg64_val;
#else
   uint32_t reg32_val;
#endif /* __AARCH64__ */

   /* complete all data transactions */
   asm volatile("dsb sy");
   /* disable all counters */
#ifdef __AARCH64__
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg64_val) : : );
   reg64_val &= ~(1<<0);
   asm volatile("MSR PMCR_EL0, %0" : : "r"(reg64_val) : );
#else
   asm volatile("MRC p15, 0, %0, c9, c12, 0" : "=r"(reg32_val) : : );
   reg32_val &= ~(1<<0);
   asm volatile("MCR p15, 0, %0, c9, c12, 0" : : "r"(reg32_val) : );
#endif /* __AARCH64__ */
   return;
}

////////////////////////////////////////////////////////////////////////////////
uint64_t a35_pmu_cycle_count_read()
{
   uint64_t reg_val;

   /* ensure the execution flow is completed */
   asm volatile("isb");
   /* ensure the data accesses are completed */
   asm volatile("dsb sy");
   /* get cycle counter value (width = 64) */
#ifdef __AARCH64__
   /* . in Aarch64, from register PMCCNTR_EL0 */
   /*   (see #D7.4.2 in [ARM DDI 0487B.a])    */
   asm volatile("MRS %0, PMCCNTR_EL0" : "=r"(reg_val) : : );
#else
   /* . in Aarch32, from register PMCCNTR  */
   /*   (see #G6.4.2 in [ARM DDI 0487B.a]) */
   uint32_t reg32_val;
   asm volatile("MRC p15, 0, %0, c9, c13, 0" : "=r"(reg32_val) : : );
   reg_val = (uint64_t)reg32_val;
#endif /* __AARCH64__ */

   return reg_val;
}

////////////////////////////////////////////////////////////////////////////////
long a35_get_time_in_second( void )
{
   return (long)(a35_pmu_cycle_count_read()/(uint64_t)gl_cpu_freq_in_Hz);
}


#if 0 /* TO BE IMPLEMENTED IN Aarch32 & Aarch64 */
////////////////////////////////////////////////////////////////////////////////
void a35_pmu_program_cycle_count_overflow_interrupt( bool_t a_force_it_flag )
{
#ifdef DEBUG_PMU
   uint32_t reg_val;
#endif
   /* complete all data transactions */
   asm volatile("dsb sy");

   /* configure the 64-bit cycle counter (register PMCR_EL0) : */
   asm volatile("MRS x0, PMCR_EL0");
   /* - reset it by setting bit 2 "C" "clock counter reset" */
   asm volatile("ORR x0,x0, #1<<2");
   asm volatile("MSR PMCR_EL0, x0");
   asm volatile("isb");

#ifdef DEBUG_PMU
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg_val) : /* no input regs */ : /* no clobbered regs */);
   printf("<D> PMCR_EL0 = 0x%08x\n", reg_val);
#endif

   /* configure the 64-bit cycle counter (register PMCR_EL0) : */
   asm volatile("MRS x0, PMCR_EL0");
   /* - DO NOT divide 64-bit cycle counter by 64 if requested */
   /*   by clearing bit 3 "D" "clock divider" */
        asm volatile("BIC x0,x0, #1<<3");
   /* - Disable long cycle count (set overflow on 32-bit counting) */
   /*   by clearing bit 6 "LC" "Long cycle count enable" */
        asm volatile("BIC x0,x0, #1<<6");

   asm volatile("MSR PMCR_EL0, x0");
   asm volatile("isb");

#ifdef DEBUG_PMU
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg_val) : /* no input regs */ : /* no clobbered regs */);
   printf("<D> PMCR_EL0 = 0x%08x\n", reg_val);
#endif

   /* set the Performance Monitors Cycle Counter for limiting delay           */
   /* before PUIRQn emission : from about 6 seconds (cycle clock at 690MHz),  */
   /* when starting from 0x0 to about 1 second when starting from 0xD000_0000 */
   asm volatile("LDR x0, =0xD0000000");
   asm volatile("MSR PMCCNTR_EL0, x0");
   asm volatile("isb");

   /* configure the 64-bit cycle counter (register PMCR_EL0) : */
   asm volatile("MRS x0, PMCR_EL0");
   /* - enable all counters (cycle counter included) */
   /*   by setting bit 0 "E" "Enable" */
   asm volatile("ORR x0,x0, #1");
   asm volatile("MSR PMCR_EL0, x0");
   asm volatile("isb");

#ifdef DEBUG_PMU
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg_val) : /* no input regs */ : /* no clobbered regs */);
   printf("<D> PMCR_EL0 = 0x%08x\n", reg_val);
#endif

   /* clear Performance Monitors Overflow Flag Status */
   asm volatile("LDR x0, =0x80000000");
   asm volatile("MSR PMOVSCLR_EL0, x0");
   asm volatile("isb");

   /* enable PMCCNTR_EL0 overflow interrupt request */
   asm volatile("MRS x0, PMINTENSET_EL1");
   asm volatile("ORR x0,x0, #1<<31");
   asm volatile("MSR PMINTENSET_EL1, x0");
   asm volatile("isb");

   if (TRUE == a_force_it_flag)
   {
      /* set Performance Monitors Overflow Flag Status */
      asm volatile("LDR x0, =0x80000000");
      asm volatile("MSR PMOVSSET_EL0, x0");
      asm volatile("isb");
   }
   else
   {
      /* start the cycle counter */
      asm volatile("MRS x0, PMCNTENSET_EL0");
      asm volatile("ORR x0,x0, #1<<31");
      asm volatile("MSR PMCNTENSET_EL0, x0");
      asm volatile("isb");
   }
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_stop_pmu_interrupt( void )
{
   /* Stop PMUIRQn : */
   /* - by setting Performance Monitors Overflow Flag Status Clear */
   /*   see [ARM DDI 0487B.a] #D7.4.12 */
   asm volatile("LDR x0, =0x80000000");
   asm volatile("MSR PMOVSCLR_EL0, x0");
   /* - by setting Performance Monitors Interrupt Enable Clear */
   /*   see [ARM DDI 0487B.a] #D7.4.10 */
   asm volatile("LDR x0, =0x80000000");
   asm volatile("MSR PMINTENCLR_EL1, x0");
   /* - by stopping/disabling cycle counter */
   asm volatile("MRS x0, PMCR_EL0");
   asm volatile("BIC x0,x0, #1");
   asm volatile("MSR PMCR_EL0, x0");

   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_output_registers( void )
{
   uint32_t reg_val32, i, reg2_val32;

   /* Read Performance Monitors Common Event Identification Register 0 */
   /* (see #C10.7 [A35_TRM]) */
   asm volatile("MRS %0, PMCEID0_EL0" : "=r"(reg_val32) : /* no input regs */ : /* no clobbered regs */);
   printf("<PMU> PMCEID0_EL0    = 0x%08x\n", reg_val32);
   /* Read Performance Monitors Control Register           */
   /* (see #D7.4.7 [ARM DDI 0487B.a] and #C10.6 [A35_TRM]) */
   asm volatile("MRS %0, PMCR_EL0" : "=r"(reg_val32) : /* no input regs */ : /* no clobbered regs */);
   printf("<PMU> PMCR_EL0       = 0x%08x\n", reg_val32);

   /* Read Performance Monitors Count Enable Set register */
   /* (see #D7.4.6 [ARM DDI 0487B.a])                     */
   asm volatile("MRS %0, PMCNTENSET_EL0" : "=r"(reg_val32) : /* no input regs */ : /* no clobbered regs */);
   printf("<PMU> PMCNTENSET_EL0 = 0x%08x\n", reg_val32);
   /* Read Performance Monitors Count Enable Clear register */
   /* (see #D7.4.5 [ARM DDI 0487B.a])                       */
   asm volatile("MRS %0, PMCNTENCLR_EL0" : "=r"(reg_val32) : /* no input regs */ : /* no clobbered regs */);
   printf("<PMU> PMCNTENCLR_EL0 = 0x%08x\n", reg_val32);

   /* Read all event counters with their corresponding types */
   for (i = 0; i < PMU_EVENT_NB_COUNTER; i++)
   {
      asm volatile("MSR PMSELR_EL0,%0"::"r" (i));
      asm volatile("ISB");
      asm volatile("MRS %0, PMXEVCNTR_EL0" : "=r"(reg_val32) : /* no input regs */ : /* no clobbered regs */);
      asm volatile("MRS %0, PMXEVTYPER_EL0" : "=r"(reg2_val32) : /* no input regs */ : /* no clobbered regs */);
      printf("<PMU> PMXEVCNTR%d_EL0 (type 0x%02X) = 0x%08x\n",
             i, reg2_val32, reg_val32);
   }
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_enable_counters( void )
{
   /* Enable all counters (events and cycle) */
   /* - by reading Performance Monitors Control Register     */
   /*   (see #D7.4.7 [ARM DDI 0487B.a] and #C10.6 [A35_TRM]) */
   asm volatile("MRS x0, PMCR_EL0");
   /* - by setting bit 0 "E" "Enable" */
   asm volatile("ORR x0,x0, #1");
   /* - by writing back Performance Monitors Control Register */
   asm volatile("MSR PMCR_EL0, x0");
   asm volatile("ISB");
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_reset_event_counters( void )
{
   /* Reset all event counters */
   /* - by reading Performance Monitors Control Register     */
   /*   (see #D7.4.7 [ARM DDI 0487B.a] and #C10.6 [A35_TRM]) */
   asm volatile("MRS x0, PMCR_EL0");
   /* - by setting bit 1 "P" "Event counter reset" */
   asm volatile("ORR x0,x0, #2");
   /* - by writing back Performance Monitors Control Register */
   asm volatile("MSR PMCR_EL0, x0");
   asm volatile("ISB");
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_configure_event( uint32_t a_counter_idx,
                              uint32_t a_event_type_val )
{
   /* Configure event type to selected value according to selected counter index */
   if (a_counter_idx <= PMU_EVENT_MAX_COUNTER)
   {
   /* - by setting Performance Monitors Event Counter Selection Register */
   /*   see #D7.4.14 [ARM DDI 0487B.a] */
   /*   to selected counter index */
      asm volatile("MSR PMSELR_EL0,%0"::"r" (a_counter_idx));
   /* - by synchronizing context (with an Instruction Synchronization Barrier) */
      asm volatile("ISB");
   /* - by setting Performance Monitors Selected Event Type Register */
   /*   see #D7.4.18 [ARM DDI 0487B.a] */
   /*   to selected event type value */
      asm volatile("MSR PMXEVTYPER_EL0,%0"::"r" (a_event_type_val));
   }
   else
   {
      printf("<E> a35_pmu_configure_event - ERROR : invalid event counter index %d\n",
             a_counter_idx);
   }
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_start_event_counter( uint32_t a_counter_idx )
{
   uint32_t reg_val32;

   /* Start event counter according to selected counter index */
   if (a_counter_idx <= PMU_EVENT_MAX_COUNTER)
   {
   /* - by setting Performance Monitors Count Enable Set register */
   /*   see #D7.4.6 [ARM DDI 0487B.a] */
   /*   bit <n> for counter index <n> */
      reg_val32 = 1 << a_counter_idx;
      asm volatile("MSR PMCNTENSET_EL0,%0"::"r" (reg_val32));
   }
   else
   {
      printf("<E> a35_pmu_start_event_counter - ERROR : invalid event counter index %d\n",
             a_counter_idx);
   }
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_read_event_counter( uint32_t a_counter_idx )
{
   uint32_t reg_val32, reg2_val32;

   /* Read event count and event type according to selected counter index */
   if (a_counter_idx <= PMU_EVENT_MAX_COUNTER)
   {
      asm volatile("MSR PMSELR_EL0,%0"::"r" (a_counter_idx));
      asm volatile("ISB");
      asm volatile("MRS %0, PMXEVCNTR_EL0" : "=r"(reg_val32) : /* no input regs */ : /* no clobbered regs */);
      asm volatile("MRS %0, PMXEVTYPER_EL0" : "=r"(reg2_val32) : /* no input regs */ : /* no clobbered regs */);
      printf("<PMU> PMXEVCNTR%d_EL0 (type 0x%02X) = 0x%08x\n",
             a_counter_idx, reg2_val32, reg_val32);
   }
   else
   {
      printf("<E> a35_pmu_read_event_counter - ERROR : invalid event counter index %d\n",
             a_counter_idx);
   }
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_stop_event_counter( uint32_t a_counter_idx )
{
   uint32_t reg_val32;

   /* Stop event counter according to selected counter index */
   if (a_counter_idx <= PMU_EVENT_MAX_COUNTER)
   {
   /* - by setting Performance Monitors Count Enable Clear register */
   /*   see #D7.4.5 [ARM DDI 0487B.a] */
   /*   bit <n> for counter index <n> */
      reg_val32 = 1 << a_counter_idx;
      asm volatile("MSR PMCNTENCLR_EL0,%0"::"r" (reg_val32));
   }
   else
   {
      printf("<E> a35_pmu_stop_event_counter - ERROR : invalid event counter index %d\n",
             a_counter_idx);
   }
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_start_all_event_counters( void )
{
   uint32_t reg_val32;
   /* Stop all (six) event counters */
   /* - by setting Performance Monitors Count Enable Set register */
   /*   see #D7.4.6 [ARM DDI 0487B.a] */
   /*   to value 0x3F (bit <n> for counter index <n>) */
   reg_val32 = 0x3FUL;
   asm volatile("MSR PMCNTENSET_EL0,%0"::"r" (reg_val32));
   return;
}

////////////////////////////////////////////////////////////////////////////////
void a35_pmu_stop_all_event_counters( void )
{
   uint32_t reg_val32;
   /* Stop all (six) event counters */
   /* - by setting Performance Monitors Count Enable Clear register */
   /*   see #D7.4.5 [ARM DDI 0487B.a] */
   /*   to value 0x3F (bit <n> for counter index <n>) */
   reg_val32 = 0x3FUL;
   asm volatile("MSR PMCNTENCLR_EL0,%0"::"r" (reg_val32));
   return;
}

////////////////////////////////////////////////////////////////////////////////
void  a35_pmu_output_external_registers( uint32_t a_core_idx )
{
   uint32_t pmu_reg_base_addr, reg32_addr, i, reg32_addr2;
   bool_t output_flag = TRUE;

   /* set PMU external registers base address according to selected core index */
   switch(a_core_idx)
   {
      case 0 :
	     pmu_reg_base_addr = A35MP4_PMU_CPU0_BaseAddr;
	     break;
      case 1 :
	     pmu_reg_base_addr = A35MP4_PMU_CPU1_BaseAddr;
	     break;
      default :
	     output_flag = FALSE;
		 printf("<E> a35_pmu_output_external_registers - ERROR : invalid core index %d\n",
                a_core_idx);
	     break;
   }
   if (TRUE == output_flag)
   {
   /* Read Performance Monitors Common Event Identification Register 0 : see #I3.4.4 [ARM DDI 0487B.a] */
      printf("<PMU> CPU%d-PMUCEID0       = 0x%08x\n",
	         a_core_idx, REG_READ32(pmu_reg_base_addr+PMCEID0_offset) );
   /* Read Performance Monitors Control Register : see #I3.4.17 [ARM DDI 0487B.a] */
      printf("<PMU> CPU%d-PMCR_EL0       = 0x%08x\n",
	         a_core_idx, REG_READ32(pmu_reg_base_addr+PMCR_EL0_offset) );
   /* Read Performance Monitors Count Enable Set register : see #I3.4.16 [ARM DDI 0487B.a] */
      printf("<PMU> CPU%d-PMCNTENSET_EL0 = 0x%08x\n",
	         a_core_idx, REG_READ32(pmu_reg_base_addr+PMCNTENSET_EL0_offset) );
   /* Read Performance Monitors Count Enable Clear register : see #I3.4.15 [ARM DDI 0487B.a] */
      printf("<PMU> CPU%d-PMCNTENCLR_EL0 = 0x%08x\n",
	         a_core_idx, REG_READ32(pmu_reg_base_addr+PMCNTENCLR_EL0_offset) );

   /* Read all event counters with their corresponding types */
      for (i = 0; i < PMU_EVENT_NB_COUNTER; i++)
      {
   /* Read Performance Monitors Event Count Registers, n = 0 - 30 : see #I3.4.23 [ARM DDI 0487B.a] */
         reg32_addr = pmu_reg_base_addr + PMEVCNTR0_EL0_offset + 0x8*i;
   /* Read Performance Monitors Event Type Registers,  n = 0 - 30 : see #I3.4.24 [ARM DDI 0487B.a] */
         reg32_addr2 = pmu_reg_base_addr + PMEVTYPER0_EL0_offset + 0x4*i;
         printf("<PMU> CPU%d-PMXEVCNTR%d_EL0 (type 0x%02X) = 0x%08x\n",
                a_core_idx, i, REG_READ32((uint64_t)reg32_addr2),
				REG_READ32((uint64_t)reg32_addr) );
      }
   }
   return;
}
#endif

/***********************************************************************/
/* Function to measure CPU frequency in respect to Timestamp generator */
/* at 32 or 64MHz by using STGEN and Cycle counters                    */
/* - function a35_measure_cpu_freq() :                                 */
uint32_t a35_measure_cpu_freq( void )
{
   volatile unsigned int reg_val;
   volatile uint32_t cycle_count0, cycle_count1, cycle_count_duration;

/*   . getting cycle counter at "STGEN counter ref value"    */
   reg_val = STGENR->CNTCVL;
   cycle_count0 = a35_pmu_cycle_count_read();
/*   . set "STGEN counter end value" = ref + 1000 ms         */
   reg_val += STGENC->CNTFID0;
/*   . waiting until STGEN reaches "STGEN counter end value" */
   while (STGENR->CNTCVL < reg_val) {};
/*   . stopping cycle counter                                */
   cycle_count1 = a35_pmu_cycle_count_read();
   a35_pmu_cycle_count_stop();
/*   . computed frequency is PMU counted value during 1000ms */
   cycle_count_duration = cycle_count1 - cycle_count0;
/*   . set value to global variable */
   gl_cpu_freq_in_Hz = cycle_count_duration;

#ifdef DEBUG_FREQ
   printf("<D> Measure_CPU_Frequency : t0 = %d - t1 = %d --> cycle_count_duration = %d\n",
          cycle_count0, cycle_count1, cycle_count_duration);
#endif
   return cycle_count_duration;
}

/* - function a35_get_cpu_freq_in_Hz() : */
uint32_t a35_get_cpu_freq_in_Hz( void )
{
   return gl_cpu_freq_in_Hz;
}
