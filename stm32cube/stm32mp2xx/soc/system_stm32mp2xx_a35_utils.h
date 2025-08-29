/*******************************************************************************
 * @file    system_stm32mp2xx_a35_utils.h
 * @author  C.ICORD (Intropack Team)
 * @version $VERSION$
 * @date    $DATE$
 *
 * @brief   A35 cores management functions (Aarch32 & Aarch64 modes)
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
//#define DEBUG_PMU

#ifndef __SYSTEM_STM32MP2XX_A35_UTILS_INC
#define __SYSTEM_STM32MP2XX_A35_UTILS_INC

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>


/*---------------------------------------------------------------------------*
 * Defines                                                                   *
 *---------------------------------------------------------------------------*/
/* Boolean values */
#define TRUE             0x01
#define FALSE            0x00

/* Number of A35_x cores */
#define NUMBER_OF_CORE   2

/* Codes for interface with EL3 Monitor */
#define CMD_NON_SECURE_ALL_GIC_INTERRUPTS 0x61CA1105UL
#define CMD_READ_SYSREG                   0x5511F00DUL
#define CMD_READ_DATA                     0xDA7AF00DUL
#define CMD_WRITE_DATA                    0xFEEDDA7AUL
#define CMD_CLEARBITS_IN_DATA             0xCB54DA7AUL
#define CMD_SETBITS_IN_DATA               0x5B54DA7AUL
#define GICD_IGROUPR0                     0x4AC10080UL
#define SCR_EL3_REG                       0x31620C11UL
#define UNUSED_PARAM                      0xDEAFC0DEUL

#if 0 /* TO BE IMPLEMENTED IN Aarch32 & Aarch64 */
/* PMU event management */
#define PMU_EVENT_MAX_COUNTER  5
#define PMU_EVENT_NB_COUNTER   PMU_EVENT_MAX_COUNTER+1
/* - PMU "implemented interesting events" */
/*   defined in Performance Monitors Common Event Identification Register 0 */
/*   see #?.?.? [A35_TRM]      */
/*   . "L1 Data cache memory error"   */
#define PMU_EVENT_L1D_CACHE_MEMORY_ERROR 0xD1
/*   . "Local memory error"   */
#define PMU_EVENT_MEMORY_ERROR 0x1A
/*   . "L2 Data cache access" */
#define PMU_EVENT_L2D_CACHE    0x16
/*   . "Data memory access"   */
#define PMU_EVENT_MEM_ACCESS   0x13
/*   . "L1 Data cache access" */
#define PMU_EVENT_L1D_CACHE    0x04
#endif

/*---------------------------------------------------------------------------*
 * Types                                                                     *
 *---------------------------------------------------------------------------*/
typedef unsigned char bool_t;


/*---------------------------------------------------------------------------*
 * Prototypes                                                                *
 *---------------------------------------------------------------------------*/
/* Aarch32 & Aarch64 handling functions : */
/* - processor identification */
uint32_t a35_get_core_id( void );
/* - security management */
#if defined(A35_NON_SECURE)
uint32_t a35ns_call_el3_monitor( uint32_t a_command, uint32_t a_param1, 
                                 uint32_t a_param2, uint32_t a_param3 );
#endif /* defined(A35_NON_SECURE) */
/* - cache management */
bool_t   a35_instruction_cache_is_enable( void );
void     a35_enable_data_cache( void );
void     a35_disable_data_cache( void );
bool_t   a35_data_cache_is_enable( void );
void     a35_clean_data_cache( void );
bool_t   a35_is_data_in_cached_sysram( void *ap_data );
/* - memory unit (MMU) management */
bool_t   a35_memory_unit_is_enable( void );
/* - processor state management */
#ifdef __AARCH64__
uint32_t a35_aa64_get_current_el( void );
#endif /* __AARCH64__ */
uint32_t a35_get_sctlr( void );
void     a35_set_sctlr( uint32_t a_sctlr_val );

/* - performance monitor unit (PMU) management */
void     a35_pmu_cycle_count_start( uint32_t count_div_by_64 );
void     a35_pmu_cycle_count_stop( void );
uint64_t a35_pmu_cycle_count_read( void );
long     a35_get_time_in_second( void );

#if 0 /* TO BE IMPLEMENTED IN Aarch32 & Aarch64 */
void     a35_pmu_program_cycle_count_overflow_interrupt(bool_t a_force_it_flag);
void     a35_pmu_stop_pmu_interrupt( void );
void     a35_pmu_output_registers( void );
void     a35_pmu_enable_counters( void );
void     a35_pmu_reset_event_counters( void );
void     a35_pmu_configure_event( uint32_t a_counter_idx,
                                  uint32_t a_event_type_val );
void     a35_pmu_start_event_counter( uint32_t a_counter_idx );
void     a35_pmu_read_event_counter( uint32_t a_counter_idx );
void     a35_pmu_stop_event_counter( uint32_t a_counter_idx );
void     a35_pmu_start_all_event_counters( void );
void     a35_pmu_stop_all_event_counters( void );
void     a35_pmu_output_external_registers( uint32_t a_core_idx );
#endif

uint32_t a35_measure_cpu_freq( void );
uint32_t a35_get_cpu_freq_in_Hz( void );

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_STM32MP2XX_A35_UTILS_INC */
