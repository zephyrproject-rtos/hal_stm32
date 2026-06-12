/**
  ******************************************************************************
  * @file    mmu_stm32mp2xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-A35 Device Peripheral Access Layer MMU Setup source file.
  *
  *   This file provides one function called from SystemInit
  *      - MMU_CreateTranslationTable() : This function is called at startup
  *                      during system initialization to setup MMU Translation tables
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Memory map description STM32MP257Cxx
                                                     Memory Type
0xFFFFFFFF |--------------------------| ---------   ------------
           |           DDR            |  2G            Normal
0x80000000 |--------------------------| ---------   ------------
           |         FMC NOR          | 256M          Device RO
0x70000000 |--------------------------| ---------   ------------
           |        OCTOSPIx          | 256M          Device RO
0x60000000 |--------------------------| ---------   ------------
           |       Peripherals        | 512M        Device RW/RO
0x40000000 |--------------------------| ---------   ------------
           |          Fault           | 256M-384k      Fault
0x30060000 |--------------------------| ---------   ------------
           |          SRAM1           | 128k           Normal
0x30040000 |--------------------------| ---------   ------------
           |          Fault           | 256k           Fault
0x30000000 |--------------------------| ---------   ------------
           |          Fault           | 256M-256k      Fault
0x20040000 |--------------------------| ---------   ------------
           |    SYSRAM - Stacks       |              Normal RW
           |--------------------------|             ------------
           |    SYSRAM - TTB          |              Normal RW
           |--------------------------|             ------------
           |    SYSRAM - RW ZI Data   |              Normal RW
           |--------------------------| 256k        ------------
           |    SYSRAM - RW Data      |              Normal RW
           |--------------------------|             ------------
           |    SYSRAM - RO Data      |            Normal Exec RO
           |--------------------------|             ------------
           |    SYSRAM - RO Code      |            Normal Exec RO
0x20000000 |--------------------------| ---------   ------------
           |          Fault           | 512M           Fault
0x00000000 |--------------------------| ---------   ------------
*/

// L1 Cache info and restrictions about architecture of the caches (CCSIR register):
// Write-Through support *not* available
// Write-Back support available.
// Read allocation support available.
// Write allocation support available.

// Note: You should use the Shareable attribute carefully.
// For cores without coherency logic (such as SCU) marking a region as shareable forces the processor to not cache that region regardless of the inner cache settings.
// Cortex-A versions of RTX use LDREX/STREX instructions relying on Local monitors. Local monitors will be used only when the region gets cached, regions that are not cached will use the Global Monitor.
// Some Cortex-A implementations do not include Global Monitors, so wrongly setting the attribute Shareable may cause STREX to fail.

// Recall: When the Shareable attribute is applied to a memory region that is not Write-Back, Normal memory, data held in this region is treated as Non-cacheable.
// When SMP bit = 0, Inner WB/WA Cacheable Shareable attributes are treated as Non-cacheable.
// When SMP bit = 1, Inner WB/WA Cacheable Shareable attributes are treated as Cacheable.

// Following MMU configuration is expected
// SCTLR.AFE == 1 (Simplified access permissions model - AP[2:1] define access permissions, AP[0] is an access flag)
// SCTLR.TRE == 0 (TEX remap disabled, so memory type and attributes are described directly by bits in the descriptor)
// Domain 0 is always the Client domain
// Descriptors should place all memory in domain 0

#include "stm32mp2xx.h"

//--------------------- TTB sizes  -------------------
#define TTB_L1_SIZE                     0x4000
#define TTB_L2_1M_SIZE                  0x0400

//Import symbols from linker
extern uint32_t __TEXT_START__;     // Start of code section (RO+Executable)
extern uint32_t __TEXT_END__;       // End of code section (4096 bytes aligned)
extern uint32_t __RO_START__;       // Start of data RO section (RO + Non-Executable)
extern uint32_t __RO_END__;         // End of RO section (4096 bytes aligned)

extern uint32_t TTB;

// Level 2 table pointers
//-----------------------------------------------------
#define CODE_AND_DATA_TABLE_L2_BASE_4k ((uint32_t)&TTB + TTB_L1_SIZE)                 //Map 1M of 4k pages for code and data
#define SRAM_TABLE_L2_BASE_4k          (CODE_AND_DATA_TABLE_L2_BASE_4k + TTB_L2_1M_SIZE) //Map 1M of 4k pages for SRAM
#define GIC_TABLE_L2_BASE_4k           (SRAM_TABLE_L2_BASE_4k + TTB_L2_1M_SIZE)          //Map 1M of 4k pages for GIC peripheral access

/* Define global descriptors */
static uint32_t Sect_SO;                // Strongly ordered, shareable by default
static uint32_t Sect_Normal;            // outer & inner wb/wa, non-shareable, executable, rw, domain 0, base addr 0
static uint32_t Sect_Normal_Shared;     // outer & inner wb/wa, shareable, executable, rw, domain 0, base addr 0
static uint32_t Sect_Device_RO;         // device, non-shareable, non-executable, ro, domain 0, base addr 0
static uint32_t Sect_Device_RW;         // as Sect_Device_RO, but writeable
static uint32_t Sect_Device_RW_Shared;  // as Sect_Device_RO, but writeable, shareable

static uint32_t Page_L1_4k  = 0x0;      // generic
static uint32_t Page_4k_Normal_Cod;     // outer & inner wb/wa, shareable, executable, ro, domain 0, base addr 0
static uint32_t Page_4k_Normal_RO;      // outer & inner wb/wa, shareable, non-executable, ro, domain 0, base addr 0
static uint32_t Page_4k_Normal_RW;      // outer & inner wb/wa, shareable, rw, domain 0, base addr 0
static uint32_t Page_4k_Device_RW;      // shared device, not executable, rw, domain 0
static uint32_t Page_4k_Normal_RW_NonCacheable;   // outer & inner Non- Cacheable, shareable, rw, domain 0, base addr 0

void MMU_CreateTranslationTable(void)
{
  mmu_region_attributes_Type region;

  // Create faulting entries for full 4GB address space to ensure any access to incorrect memory location will be trapped
  // Further sections and pages setup will overwrite these default table entries
  MMU_TTSection (&TTB, 0, 4096U, DESCRIPTOR_FAULT);

  /*
   * Generate descriptors. Refer to core_ca.h to get information about attributes
   *
   */
  // Create descriptors for Vectors, RO, RW, ZI sections
  section_so(Sect_SO, region);
  section_normal(Sect_Normal, region);

  Sect_Normal_Shared = Sect_Normal;
  MMU_SharedSection(&Sect_Normal_Shared, SHARED);

  // Create descriptors for peripherals
  section_device_ro(Sect_Device_RO, region);
  section_device_rw(Sect_Device_RW, region);

  Sect_Device_RW_Shared = Sect_Device_RW;
  MMU_SharedSection(&Sect_Device_RW_Shared, SHARED);

  // Create descriptors for 4k pages
  page4k_device_rw(Page_L1_4k, Page_4k_Device_RW, region);

  region.rg_t = PAGE_4k;
  region.domain = 0x0;
  region.e_t = ECC_DISABLED;
  region.g_t = GLOBAL;
  region.inner_norm_t = WB_WA;
  region.outer_norm_t = WB_WA;
  region.mem_t = NORMAL;
  region.sec_t = SECURE;
  region.xn_t = EXECUTE;
  /* This should be READ but SW4STM32/GDB/OpenOCD is not able to step in a read-only code section ... */
  /* So set it RW */
  region.priv_t = RW;
  region.user_t = RW;
  region.sh_t = SHARED;
  MMU_GetPageDescriptor(&Page_L1_4k, &Page_4k_Normal_Cod, region);

  region.rg_t = PAGE_4k;
  region.domain = 0x0;
  region.e_t = ECC_DISABLED;
  region.g_t = GLOBAL;
  region.inner_norm_t = WB_WA;
  region.outer_norm_t = WB_WA;
  region.mem_t = NORMAL;
  region.sec_t = SECURE;
  region.xn_t = NON_EXECUTE;
  region.priv_t = READ;
  region.user_t = READ;
  region.sh_t = SHARED;
  MMU_GetPageDescriptor(&Page_L1_4k, &Page_4k_Normal_RO, region);

  region.rg_t = PAGE_4k;
  region.domain = 0x0;
  region.e_t = ECC_DISABLED;
  region.g_t = GLOBAL;
  region.inner_norm_t = WB_WA;
  region.outer_norm_t = WB_WA;
  region.mem_t = NORMAL;
  region.sec_t = SECURE;
  region.xn_t = NON_EXECUTE;
  region.priv_t = RW;
  region.user_t = RW;
  region.sh_t = SHARED;
  MMU_GetPageDescriptor(&Page_L1_4k, &Page_4k_Normal_RW, region);

  region.rg_t = PAGE_4k;
  region.domain = 0x0;
  region.e_t = ECC_DISABLED;
  region.g_t = GLOBAL;
  region.inner_norm_t = NON_CACHEABLE;
  region.outer_norm_t = NON_CACHEABLE;
  region.mem_t = NORMAL;
  region.sec_t = SECURE;
  region.xn_t = NON_EXECUTE;
  region.priv_t = RW;
  region.user_t = RW;
  region.sh_t = SHARED;
  MMU_GetPageDescriptor(&Page_L1_4k, &Page_4k_Normal_RW_NonCacheable, region);

  /*
   *  Define MMU flat-map regions and attributes
   *
   */
  // Define 256M OSPI memory as device, non-shareable, non-executable, ro
  MMU_TTSection (&TTB, (uint32_t)OSPI1_MEM_BASE  , ((FMC_NOR_MEM_BASE - OSPI1_MEM_BASE) >> 20 ),
		 Sect_Device_RO);

  // Define 256M FMC NOR memory as device, non-shareable, non-executable, ro
  MMU_TTSection (&TTB, (uint32_t)FMC_NOR_MEM_BASE, ((DDR_MEM_BASE - FMC_NOR_MEM_BASE) >> 20 )  ,
		 Sect_Device_RO);

  // All DDR (2GB) Executable, Cacheable & RW - applications may choose to divide memory into RO executable
  MMU_TTSection (&TTB, (uint32_t)DDR_MEM_BASE    , 2048U                                       ,
		 Sect_Normal_Shared);

  //-------------------- SYSRAM ------------------
  // Create (256 * 4k)=1MB faulting entries to cover SYSRAM 1M aligned range
  MMU_TTPage4k (&TTB, SYSRAM_BASE & 0xFFF00000, 1024U/4U, Page_L1_4k,
		(uint32_t *)CODE_AND_DATA_TABLE_L2_BASE_4k, DESCRIPTOR_FAULT);
  // Create (64 * 4k)=256k Normal entries to cover full SYSRAM (includes RW_data, ZI_Data, TTB, Stacks, heap)
  MMU_TTPage4k (&TTB, SYSRAM_BASE             , 256U/4U , Page_L1_4k,
		(uint32_t *)CODE_AND_DATA_TABLE_L2_BASE_4k, Page_4k_Normal_RW);

  //-------------------- Code and data ------------------
  // Assuming that Code and Data fits in a single 1 Mbytes section
  if ( (uint32_t)&__TEXT_START__ >= DDR_MEM_BASE ) /* Code in DDR */
  {
    // Create 4k pages Normal, RW, shared entries to cover DDR Code and RO data 1M aligned range
    uint32_t aligned_CodeStart   = (uint32_t)&__TEXT_START__ & 0xFFF00000;
    uint32_t aligned_RO_Data_End = ((uint32_t)&__RO_END__ + 0x000FFFFF) & 0xFFF00000;

    // Ensure Code and RO data can fit in single 1M section
    // because this is the size of Level to CODE_AND_DATA_TABLE_L2_BASE_4k Table
    if (aligned_RO_Data_End-aligned_CodeStart > 0x00100000)
    {
      /* Infinite loop */
      while (1)
      {
      }
    }
    MMU_TTPage4k (&TTB, aligned_CodeStart, ((aligned_RO_Data_End - aligned_CodeStart)) / 4096,
		  Page_L1_4k, (uint32_t *)CODE_AND_DATA_TABLE_L2_BASE_4k, Page_4k_Normal_RW);
  }

  // Create Normal, executable+RO entries to cover Code
  MMU_TTPage4k (&TTB, (uint32_t)&__TEXT_START__,
		((uint32_t)&__TEXT_END__ - (uint32_t)&__TEXT_START__ + 4095) / 4096,
		Page_L1_4k, (uint32_t *)CODE_AND_DATA_TABLE_L2_BASE_4k, Page_4k_Normal_Cod);

  // Create Normal, non-executable+RO entries to cover RO data range
  MMU_TTPage4k (&TTB, (uint32_t)&__RO_START__  ,
		((uint32_t)&__RO_END__ - (uint32_t)&__RO_START__ + 4095) / 4096    ,
		Page_L1_4k, (uint32_t *)CODE_AND_DATA_TABLE_L2_BASE_4k, Page_4k_Normal_RO);

  //-------------------- RETRAM ------------------
  // Create (32 * 4k)=128k Normal entries to cover RETRAM
  MMU_TTPage4k (&TTB, RETRAM_BASE              , 128U/4U , Page_L1_4k,
		(uint32_t *)CODE_AND_DATA_TABLE_L2_BASE_4k, Page_4k_Normal_RW);

  //--------------------- PERIPHERALS -------------------
  // Define Peripheral memory as Strongly ordered, shareable, RW , Non Cacheable
  MMU_TTSection (&TTB, (uint32_t)PERIPH_BASE, ((OSPI1_MEM_BASE - PERIPH_BASE) >> 20 )    , Sect_SO);

  /* Set location of level 1 page table
  ; 31:14 - Translation table base addr (31:14-TTBCR.N, TTBCR.N is 0 out of reset)
  ; 13:7  - 0x0
  ; 6     - IRGN[0] 0x0 (Inner WB WA)
  ; 5     - NOS     0x0 (Non-shared)
  ; 4:3   - RGN     0x1 (Outer WB WA)
  ; 2     - IMP     0x0 (Implementation Defined)
  ; 1     - S       0x0 (Non-shared)
  ; 0     - IRGN[1] 0x1 (Inner WB WA) */
  __set_TTBR0(((uint32_t)&TTB) | 9U);
  __ISB();

  /* Set up domain access control register
  ; We set domain 0 to Client and all other domains to No Access.
  ; All translation table entries specify domain 0 */
  __set_DACR(1);
  __ISB();
}
