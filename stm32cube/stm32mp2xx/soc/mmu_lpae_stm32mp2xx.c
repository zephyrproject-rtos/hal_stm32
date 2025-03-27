/**
  ******************************************************************************
  * @file    mmu_lpae_stm32mp2xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-A35 Device Peripheral Access Layer MMU Setup source file.
  *
  *   This file provides one function called from SystemInit
  *      - MMU_CreateTranslationTable_LPAE() : This function is called at startup
  *                      during system initialization to setup MMU Translation tables
  *
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT 2023 STMicroelectronics</center></h2>
  *
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

// Configure MMU with Large Physical Address Extension0

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "stm32mp2xx_hal.h"
#include "stm32mp2xx.h"

//Import symbols from linker
extern uint32_t TTB;

#define LPAE_DEVICE_DESCRIPTOR 0x0060000000000441ULL	/* ATTRindex 0 */
#define LPAE_NORMAL_DESCRIPTOR 0x0000000000000645ULL	/* ATTRindex 1 */

void MMU_CreateTranslationTable_LPAE (void)
{
	  uint64_t *aMMU_Translation_Table = NULL;
	  uint64_t ttbr0;

	  /* Translation table points to address reserved in linker  */
	  aMMU_Translation_Table = &TTB;

	  /* ---------------------------------------------
	  * Enable SMP mode (mandatory for using caches)
	  * ---------------------------------------------
	  */
	  #define ACTLR_SMP_BIT           (1 << 6)
	  asm volatile ("mrc p15, 0, r1, c1, c0, 1");
	  asm volatile ("orr r1, r1, %0" :: "i" ACTLR_SMP_BIT);
	  asm volatile ("mcr p15, 0, r1, c1, c0, 1");

	  {
		  aMMU_Translation_Table[0] = LPAE_NORMAL_DESCRIPTOR | (0x0ULL << 30);	/* 1st Gbyte, Normal */
		  aMMU_Translation_Table[1] = LPAE_DEVICE_DESCRIPTOR | (0x1ULL << 30);	/* 2nd Gbyte, Device */
		  aMMU_Translation_Table[2] = LPAE_NORMAL_DESCRIPTOR | (0x2ULL << 30);	/* 3rd Gbyte, Normal */
		  aMMU_Translation_Table[3] = LPAE_NORMAL_DESCRIPTOR | (0x3ULL << 30);	/* 4th Gbyte, Normal */
		  aMMU_Translation_Table[4] = LPAE_NORMAL_DESCRIPTOR | (0x4ULL << 30);	/* 5th Gbyte, Normal */
		  aMMU_Translation_Table[5] = LPAE_NORMAL_DESCRIPTOR | (0x5ULL << 30);	/* 6th Gbyte, Normal */
	  }

	  /* write MAIR0 */
	  /* value for Attr0 = DEVICE, Attr1 = NORMAL inner and outer write-back, read/write */
	  asm volatile ("mcr p15, 0, %0, c10, c2, 0"::"r" (0x0000FF04));

	  /* write TTBCR with EAE=1, long descriptor mode */
	  asm volatile ("mcr p15, 0, %0, c2, c0, 2"::"r" (0x80002500):"memory");
	  __ISB();

	  /* Set TTBR0 64 bits */
	  /* T0SZ = 0b000, so bits 39 to 5 used for translation table, i.e. 0x000000FFFFFFFFE0  */
	  ttbr0 = (uint64_t) aMMU_Translation_Table & 0x000000FFFFFFFFE0ULL;
	  ttbr0 |= (0x0ULL << 48);    /* ASID[7:0] = 0 ? */

	  /* write TTBR0 64 bits*/
	  uint32_t ttbr0_lsb = (uint32_t)(ttbr0);
	  uint32_t ttbr0_msb = (uint32_t)(ttbr0>>32);
	  asm volatile ("mcrr p15, 0, %0, %1, c2"::"r" (ttbr0_lsb), "r" (ttbr0_msb):"memory");

	  /* write DACR: Enable only Domain 0 */
	  asm volatile ("mcr p15, 0, %0, c3, c0, 0"::"r" (3));
	  __ISB();
}
