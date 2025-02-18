/**
  ******************************************************************************
  * @file    stm32mp13xx_hal_ddr.c
  * @author  MCD Application Team
  * @brief   DDR HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Double Data Rate Synchronous Dynamic Random
  *          Access Memory (DDR-SDRAM) Peripheral, through its controller
  *          (DDRCTRL) and its physical interface controller (DDRPHYC).
  *           +
  *           +
  *           +
  *
  *
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
  @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp13xx_hal.h"

#ifdef HAL_DDR_MODULE_ENABLED

#include <stdbool.h>
#include <string.h>

#if defined DDR_TYPE_DDR3_4Gb
#include "stm32mp13xx-ddr3-4Gb.h"
#elif defined DDR_TYPE_DDR3_8Gb
#include "stm32mp13xx-ddr3-8Gb.h"
#elif defined DDR_TYPE_LPDDR2_4Gb
#include "stm32mp13xx-lpddr2-4Gb.h"
#elif defined DDR_TYPE_LPDDR3_4Gb
#include "stm32mp13xx-lpddr3-4Gb.h"
#else /* DDR_TYPE_DDR3_4Gb */
#error "no DDR settings defined."
#error "Please make sure that DDR_TYPE is set within those values:"
#error "  DDR_TYPE_DDR3_4Gb"
#error "  DDR_TYPE_DDR3_8Gb"
#error "  DDR_TYPE_LPDDR2_4Gb"
#error "  DDR_TYPE_LPDDR3_4Gb"
#error "Please refer to your HW platform capabilities."
#endif  /* DDR_TYPE_DDR3_4Gb */

/** @addtogroup STM32MP13xx_HAL_Driver
  * @{
  */

/** @defgroup DDR DDR
  * @brief HAL DDR module driver
  * @{
  */
#if defined (DDRCTRL) && defined (DDRPHYC)

/* Private typedef -----------------------------------------------------------*/

typedef struct
{
  uint16_t offset; /* Offset for base address */
  uint8_t par_offset; /* Offset for parameter array */
} reg_desc_t;

typedef enum
{
  BASE_DDRCTRL,
  BASE_DDRPHYC,
  BASE_NONE
} base_type;

typedef struct
{
  const char *name;
  const reg_desc_t *desc;
  uint8_t size;
  base_type base;
} ddr_reg_info_t;

typedef enum
{
  REG_REG,
  REG_TIMING,
  REG_PERF,
  REG_MAP,
  REGPHY_REG,
  REGPHY_TIMING,
  REG_TYPE_NB
} reg_type;

typedef struct
{
  uint32_t MSTR;
  uint32_t MRCTRL0;
  uint32_t MRCTRL1;
  uint32_t DERATEEN;
  uint32_t DERATEINT;
  uint32_t PWRCTL;
  uint32_t PWRTMG;
  uint32_t HWLPCTL;
  uint32_t RFSHCTL0;
  uint32_t RFSHCTL3;
  uint32_t CRCPARCTL0;
  uint32_t ZQCTL0;
  uint32_t DFITMG0;
  uint32_t DFITMG1;
  uint32_t DFILPCFG0;
  uint32_t DFIUPD0;
  uint32_t DFIUPD1;
  uint32_t DFIUPD2;
  uint32_t DFIPHYMSTR;
  uint32_t ODTMAP;
  uint32_t DBG0;
  uint32_t DBG1;
  uint32_t DBGCMD;
  uint32_t POISONCFG;
  uint32_t PCCFG;
} HAL_DDR_RegTypeDef;

typedef struct
{
  uint32_t RFSHTMG;
  uint32_t DRAMTMG0;
  uint32_t DRAMTMG1;
  uint32_t DRAMTMG2;
  uint32_t DRAMTMG3;
  uint32_t DRAMTMG4;
  uint32_t DRAMTMG5;
  uint32_t DRAMTMG6;
  uint32_t DRAMTMG7;
  uint32_t DRAMTMG8;
  uint32_t DRAMTMG14;
  uint32_t ODTCFG;
} HAL_DDR_TimingTypeDef;

typedef struct
{
  uint32_t ADDRMAP1;
  uint32_t ADDRMAP2;
  uint32_t ADDRMAP3;
  uint32_t ADDRMAP4;
  uint32_t ADDRMAP5;
  uint32_t ADDRMAP6;
  uint32_t ADDRMAP9;
  uint32_t ADDRMAP10;
  uint32_t ADDRMAP11;
} HAL_DDR_MapTypeDef;

typedef struct
{
  uint32_t SCHED;
  uint32_t SCHED1;
  uint32_t PERFHPR1;
  uint32_t PERFLPR1;
  uint32_t PERFWR1;
  uint32_t PCFGR_0;
  uint32_t PCFGW_0;
  uint32_t PCFGQOS0_0;
  uint32_t PCFGQOS1_0;
  uint32_t PCFGWQOS0_0;
  uint32_t PCFGWQOS1_0;
#ifdef DDR_DUAL_AXI_PORT
  uint32_t PCFGR_1;
  uint32_t PCFGW_1;
  uint32_t PCFGQOS0_1;
  uint32_t PCFGQOS1_1;
  uint32_t PCFGWQOS0_1;
  uint32_t PCFGWQOS1_1;
#endif /* DDR_DUAL_AXI_PORT */
} HAL_DDR_PerfTypeDef;

typedef struct
{
  uint32_t PGCR;
  uint32_t ACIOCR;
  uint32_t DXCCR;
  uint32_t DSGCR;
  uint32_t DCR;
  uint32_t ODTCR;
  uint32_t ZQ0CR1;
  uint32_t DX0GCR;
  uint32_t DX1GCR;
#ifdef DDR_32BIT_INTERFACE
  uint32_t DX2GCR;
  uint32_t DX3GCR;
#endif /* DDR_32BIT_INTERFACE */
} HAL_DDR_PhyRegTypeDef;

typedef struct
{
  uint32_t PTR0;
  uint32_t PTR1;
  uint32_t PTR2;
  uint32_t DTPR0;
  uint32_t DTPR1;
  uint32_t DTPR2;
  uint32_t MR0;
  uint32_t MR1;
  uint32_t MR2;
  uint32_t MR3;
} HAL_DDR_PhyTimingTypeDef;

typedef struct
{
  const char *name;
  uint32_t speed; /* in kHZ */
  uint32_t size; /* Memory size in byte = col * row * width */
} HAL_DDR_InfoTypeDef;

typedef struct
{
  HAL_DDR_InfoTypeDef      info;
  HAL_DDR_RegTypeDef       c_reg;
  HAL_DDR_TimingTypeDef    c_timing;
  HAL_DDR_MapTypeDef       c_map;
  HAL_DDR_PerfTypeDef      c_perf;
  HAL_DDR_PhyRegTypeDef    p_reg;
  HAL_DDR_PhyTimingTypeDef p_timing;
} HAL_DDR_ConfigTypeDef;

/* Private define ------------------------------------------------------------*/
/** @defgroup DDR_Private_Constants DDR Private Constants
  * @{
  */
#define INVALID_OFFSET 0xFFU

#define DDRCTL_REG(x, y) \
  { \
    .offset = offsetof(DDRCTRL_TypeDef, x), \
    .par_offset = offsetof(y, x) \
  }

#define DDRPHY_REG(x, y) \
  { \
    .offset = offsetof(DDRPHYC_TypeDef, x), \
    .par_offset = offsetof(y, x) \
  }

#define DDRCTL_REG_REG(x) DDRCTL_REG(x, HAL_DDR_RegTypeDef)
static const reg_desc_t ddr_reg_desc[] =
{
  DDRCTL_REG_REG(MSTR),
  DDRCTL_REG_REG(MRCTRL0),
  DDRCTL_REG_REG(MRCTRL1),
  DDRCTL_REG_REG(DERATEEN),
  DDRCTL_REG_REG(DERATEINT),
  DDRCTL_REG_REG(PWRCTL),
  DDRCTL_REG_REG(PWRTMG),
  DDRCTL_REG_REG(HWLPCTL),
  DDRCTL_REG_REG(RFSHCTL0),
  DDRCTL_REG_REG(RFSHCTL3),
  DDRCTL_REG_REG(CRCPARCTL0),
  DDRCTL_REG_REG(ZQCTL0),
  DDRCTL_REG_REG(DFITMG0),
  DDRCTL_REG_REG(DFITMG1),
  DDRCTL_REG_REG(DFILPCFG0),
  DDRCTL_REG_REG(DFIUPD0),
  DDRCTL_REG_REG(DFIUPD1),
  DDRCTL_REG_REG(DFIUPD2),
  DDRCTL_REG_REG(DFIPHYMSTR),
  DDRCTL_REG_REG(ODTMAP),
  DDRCTL_REG_REG(DBG0),
  DDRCTL_REG_REG(DBG1),
  DDRCTL_REG_REG(DBGCMD),
  DDRCTL_REG_REG(POISONCFG),
  DDRCTL_REG_REG(PCCFG),
};

#define DDRCTL_REG_TIMING(x) DDRCTL_REG(x, HAL_DDR_TimingTypeDef)
static const reg_desc_t ddr_timing_desc[] =
{
  DDRCTL_REG_TIMING(RFSHTMG),
  DDRCTL_REG_TIMING(DRAMTMG0),
  DDRCTL_REG_TIMING(DRAMTMG1),
  DDRCTL_REG_TIMING(DRAMTMG2),
  DDRCTL_REG_TIMING(DRAMTMG3),
  DDRCTL_REG_TIMING(DRAMTMG4),
  DDRCTL_REG_TIMING(DRAMTMG5),
  DDRCTL_REG_TIMING(DRAMTMG6),
  DDRCTL_REG_TIMING(DRAMTMG7),
  DDRCTL_REG_TIMING(DRAMTMG8),
  DDRCTL_REG_TIMING(DRAMTMG14),
  DDRCTL_REG_TIMING(ODTCFG),
};

#define DDRCTL_REG_MAP(x) DDRCTL_REG(x, HAL_DDR_MapTypeDef)
static const reg_desc_t ddr_map_desc[] =
{
  DDRCTL_REG_MAP(ADDRMAP1),
  DDRCTL_REG_MAP(ADDRMAP2),
  DDRCTL_REG_MAP(ADDRMAP3),
  DDRCTL_REG_MAP(ADDRMAP4),
  DDRCTL_REG_MAP(ADDRMAP5),
  DDRCTL_REG_MAP(ADDRMAP6),
  DDRCTL_REG_MAP(ADDRMAP9),
  DDRCTL_REG_MAP(ADDRMAP10),
  DDRCTL_REG_MAP(ADDRMAP11),
};

#define DDRCTL_REG_PERF(x) DDRCTL_REG(x, HAL_DDR_PerfTypeDef)
static const reg_desc_t ddr_perf_desc[] =
{
  DDRCTL_REG_PERF(SCHED),
  DDRCTL_REG_PERF(SCHED1),
  DDRCTL_REG_PERF(PERFHPR1),
  DDRCTL_REG_PERF(PERFLPR1),
  DDRCTL_REG_PERF(PERFWR1),
  DDRCTL_REG_PERF(PCFGR_0),
  DDRCTL_REG_PERF(PCFGW_0),
  DDRCTL_REG_PERF(PCFGQOS0_0),
  DDRCTL_REG_PERF(PCFGQOS1_0),
  DDRCTL_REG_PERF(PCFGWQOS0_0),
  DDRCTL_REG_PERF(PCFGWQOS1_0),
#ifdef DDR_DUAL_AXI_PORT
  DDRCTL_REG_PERF(PCFGR_1),
  DDRCTL_REG_PERF(PCFGW_1),
  DDRCTL_REG_PERF(PCFGQOS0_1),
  DDRCTL_REG_PERF(PCFGQOS1_1),
  DDRCTL_REG_PERF(PCFGWQOS0_1),
  DDRCTL_REG_PERF(PCFGWQOS1_1),
#endif /* DDR_DUAL_AXI_PORT */
};

#define DDRPHY_REG_REG(x) DDRPHY_REG(x, HAL_DDR_PhyRegTypeDef)
static const reg_desc_t ddrphy_reg_desc[] =
{
  DDRPHY_REG_REG(PGCR),
  DDRPHY_REG_REG(ACIOCR),
  DDRPHY_REG_REG(DXCCR),
  DDRPHY_REG_REG(DSGCR),
  DDRPHY_REG_REG(DCR),
  DDRPHY_REG_REG(ODTCR),
  DDRPHY_REG_REG(ZQ0CR1),
  DDRPHY_REG_REG(DX0GCR),
  DDRPHY_REG_REG(DX1GCR),
#ifdef DDR_32BIT_INTERFACE
  DDRPHY_REG_REG(DX2GCR),
  DDRPHY_REG_REG(DX3GCR),
#endif /* DDR_32BIT_INTERFACE */
};

#define DDRPHY_REG_TIMING(x) DDRPHY_REG(x, HAL_DDR_PhyTimingTypeDef)
static const reg_desc_t ddrphy_timing_desc[] =
{
  DDRPHY_REG_TIMING(PTR0),
  DDRPHY_REG_TIMING(PTR1),
  DDRPHY_REG_TIMING(PTR2),
  DDRPHY_REG_TIMING(DTPR0),
  DDRPHY_REG_TIMING(DTPR1),
  DDRPHY_REG_TIMING(DTPR2),
  DDRPHY_REG_TIMING(MR0),
  DDRPHY_REG_TIMING(MR1),
  DDRPHY_REG_TIMING(MR2),
  DDRPHY_REG_TIMING(MR3),
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
static const ddr_reg_info_t ddr_registers[REG_TYPE_NB] =
{
  [REG_REG] = {
    .name = "static",
    .desc = ddr_reg_desc,
    .size = ARRAY_SIZE(ddr_reg_desc),
    .base = BASE_DDRCTRL
  },
  [REG_TIMING] = {
    .name = "timing",
    .desc = ddr_timing_desc,
    .size = ARRAY_SIZE(ddr_timing_desc),
    .base = BASE_DDRCTRL
  },
  [REG_PERF] = {
    .name = "perf",
    .desc = ddr_perf_desc,
    .size = ARRAY_SIZE(ddr_perf_desc),
    .base = BASE_DDRCTRL
  },
  [REG_MAP] = {
    .name = "map",
    .desc = ddr_map_desc,
    .size = ARRAY_SIZE(ddr_map_desc),
    .base = BASE_DDRCTRL
  },
  [REGPHY_REG] = {
    .name = "static",
    .desc = ddrphy_reg_desc,
    .size = ARRAY_SIZE(ddrphy_reg_desc),
    .base = BASE_DDRPHYC
  },
  [REGPHY_TIMING] = {
    .name = "timing",
    .desc = ddrphy_timing_desc,
    .size = ARRAY_SIZE(ddrphy_timing_desc),
    .base = BASE_DDRPHYC
  },
};

#define DDR_DELAY_1_US                       1U
#define DDR_TIMEOUT_1_US                     1U
#define DDR_DELAY_2_US                       2U * DDR_DELAY_1_US
#define DDR_DELAY_10_US                      10U * DDR_DELAY_1_US
#define DDR_DELAY_END_LOGIC_INIT_US          DDR_DELAY_2_US
#define DDR_DELAY_PHY_INIT_US                DDR_DELAY_10_US
#define DDR_TIMEOUT_10_US                    10U * DDR_TIMEOUT_1_US
#define DDR_TIMEOUT_50_US                    50U * DDR_TIMEOUT_1_US
#define DDR_TIMEOUT_500_US                   500U * DDR_TIMEOUT_1_US
#define DDR_TIMEOUT_200_MS                   200000U * DDR_TIMEOUT_1_US
#define DDR_TIMEOUT_1S                       1000000U * DDR_TIMEOUT_1_US

#define TIMESLOT_1US                         (__get_CNTFRQ() / 1000000U)

#define DDRCTRL_MSTR_DATA_BUS_WIDTH_HALF     DDRCTRL_MSTR_DATA_BUS_WIDTH_0
#define DDRCTRL_MSTR_DATA_BUS_WIDTH_QUARTER  DDRCTRL_MSTR_DATA_BUS_WIDTH_1
#define DDRCTRL_STAT_OPERATING_MODE_SR       (DDRCTRL_STAT_OPERATING_MODE_0 | \
                                              DDRCTRL_STAT_OPERATING_MODE_1)
#define DDRCTRL_STAT_OPERATING_MODE_NORMAL   DDRCTRL_STAT_OPERATING_MODE_0
#define DDRCTRL_STAT_SELFREF_TYPE_ASR        (DDRCTRL_STAT_SELFREF_TYPE_0 | \
                                              DDRCTRL_STAT_SELFREF_TYPE_1)
#define DDRCTRL_STAT_SELFREF_TYPE_SR         DDRCTRL_STAT_SELFREF_TYPE_1
#define DDRCTRL_MRCTRL0_MR_TYPE_WRITE        0U
#define DDRCTRL_MRCTRL0_MR_TYPE_READ         DDRCTRL_MRCTRL0_MR_TYPE
#define DDRCTRL_MRCTRL0_MR_RANK_ALL          DDRCTRL_MRCTRL0_MR_RANK
#define DDRCTRL_INIT0_SKIP_DRAM_INIT_NORMAL  DDRCTRL_INIT0_SKIP_DRAM_INIT_0
#define DDRCTRL_DBGCAM_DATA_PIPELINE_EMPTY \
  (DDRCTRL_DBGCAM_WR_DATA_PIPELINE_EMPTY | \
   DDRCTRL_DBGCAM_RD_DATA_PIPELINE_EMPTY)
#define DDRCTRL_DBG_Q_AND_DATA_PIPELINE_EMPTY \
  (DDRCTRL_DBGCAM_DBG_WR_Q_EMPTY | \
   DDRCTRL_DBGCAM_DBG_RD_Q_EMPTY | \
   DDRCTRL_DBGCAM_DATA_PIPELINE_EMPTY)
#define DDRCTRL_DBGCAM_DBG_Q_DEPTH \
  (DDRCTRL_DBGCAM_DBG_WR_Q_EMPTY | \
   DDRCTRL_DBGCAM_DBG_LPR_Q_DEPTH | \
   DDRCTRL_DBGCAM_DBG_HPR_Q_DEPTH)

#define DDR_BASE_ADDR                        0xC0000000U
#define DDR_MAX_SIZE                         0x40000000U
#define DDR_PATTERN                          0xAAAAAAAAU
#define DDR_ANTIPATTERN                      0x55555555U
#define DDR_TRAINING_AREA_SIZE               64U

#define RCC_DDRITFCR_DDRCKMOD_ASR1           RCC_DDRITFCR_DDRCKMOD_0
#define RCC_DDRITFCR_DDRCKMOD_HSR1           RCC_DDRITFCR_DDRCKMOD_1

#define BKPRAM_ZDATA_OFFSET                  0U

#define SCTLR_C_BIT                          (1U << 2)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static HAL_DDR_ConfigTypeDef static_ddr_config =
{
  .info = {
    .name = DDR_MEM_NAME,
    .speed = DDR_MEM_SPEED,
    .size = DDR_MEM_SIZE
  },

  .c_reg = {
    .MSTR = DDR_MSTR,
    .MRCTRL0 = DDR_MRCTRL0,
    .MRCTRL1 = DDR_MRCTRL1,
    .DERATEEN = DDR_DERATEEN,
    .DERATEINT = DDR_DERATEINT,
    .PWRCTL = DDR_PWRCTL,
    .PWRTMG = DDR_PWRTMG,
    .HWLPCTL = DDR_HWLPCTL,
    .RFSHCTL0 = DDR_RFSHCTL0,
    .RFSHCTL3 = DDR_RFSHCTL3,
    .CRCPARCTL0 = DDR_CRCPARCTL0,
    .ZQCTL0 = DDR_ZQCTL0,
    .DFITMG0 = DDR_DFITMG0,
    .DFITMG1 = DDR_DFITMG1,
    .DFILPCFG0 = DDR_DFILPCFG0,
    .DFIUPD0 = DDR_DFIUPD0,
    .DFIUPD1 = DDR_DFIUPD1,
    .DFIUPD2 = DDR_DFIUPD2,
    .DFIPHYMSTR = DDR_DFIPHYMSTR,
    .ODTMAP = DDR_ODTMAP,
    .DBG0 = DDR_DBG0,
    .DBG1 = DDR_DBG1,
    .DBGCMD = DDR_DBGCMD,
    .POISONCFG = DDR_POISONCFG,
    .PCCFG = DDR_PCCFG
  },

  .c_timing = {
    .RFSHTMG = DDR_RFSHTMG,
    .DRAMTMG0 = DDR_DRAMTMG0,
    .DRAMTMG1 = DDR_DRAMTMG1,
    .DRAMTMG2 = DDR_DRAMTMG2,
    .DRAMTMG3 = DDR_DRAMTMG3,
    .DRAMTMG4 = DDR_DRAMTMG4,
    .DRAMTMG5 = DDR_DRAMTMG5,
    .DRAMTMG6 = DDR_DRAMTMG6,
    .DRAMTMG7 = DDR_DRAMTMG7,
    .DRAMTMG8 = DDR_DRAMTMG8,
    .DRAMTMG14 = DDR_DRAMTMG14,
    .ODTCFG = DDR_ODTCFG
  },


  .c_map = {
    .ADDRMAP1 = DDR_ADDRMAP1,
    .ADDRMAP2 = DDR_ADDRMAP2,
    .ADDRMAP3 = DDR_ADDRMAP3,
    .ADDRMAP4 = DDR_ADDRMAP4,
    .ADDRMAP5 = DDR_ADDRMAP5,
    .ADDRMAP6 = DDR_ADDRMAP6,
    .ADDRMAP9 = DDR_ADDRMAP9,
    .ADDRMAP10 = DDR_ADDRMAP10,
    .ADDRMAP11 = DDR_ADDRMAP11
  },

  .c_perf = {
    .SCHED = DDR_SCHED,
    .SCHED1 = DDR_SCHED1,
    .PERFHPR1 = DDR_PERFHPR1,
    .PERFLPR1 = DDR_PERFLPR1,
    .PERFWR1 = DDR_PERFWR1,
    .PCFGR_0 = DDR_PCFGR_0,
    .PCFGW_0 = DDR_PCFGW_0,
    .PCFGQOS0_0 = DDR_PCFGQOS0_0,
    .PCFGQOS1_0 = DDR_PCFGQOS1_0,
    .PCFGWQOS0_0 = DDR_PCFGWQOS0_0,
    .PCFGWQOS1_0 = DDR_PCFGWQOS1_0,
#ifdef DDR_DUAL_AXI_PORT
    .PCFGR_1 = DDR_PCFGR_1,
    .PCFGW_1 = DDR_PCFGW_1,
    .PCFGQOS0_1 = DDR_PCFGQOS0_1,
    .PCFGQOS1_1 = DDR_PCFGQOS1_1,
    .PCFGWQOS0_1 = DDR_PCFGWQOS0_1,
    .PCFGWQOS1_1 = DDR_PCFGWQOS1_1
#endif /* DDR_DUAL_AXI_PORT */
  },

  .p_reg = {
    .PGCR = DDR_PGCR,
    .ACIOCR = DDR_ACIOCR,
    .DXCCR = DDR_DXCCR,
    .DSGCR = DDR_DSGCR,
    .DCR = DDR_DCR,
    .ODTCR = DDR_ODTCR,
    .ZQ0CR1 = DDR_ZQ0CR1,
    .DX0GCR = DDR_DX0GCR,
    .DX1GCR = DDR_DX1GCR,
#ifdef DDR_32BIT_INTERFACE
    .DX2GCR = DDR_DX2GCR,
    .DX3GCR = DDR_DX3GCR
#endif /* DDR_32BIT_INTERFACE */
  },

  .p_timing = {
    .PTR0 = DDR_PTR0,
    .PTR1 = DDR_PTR1,
    .PTR2 = DDR_PTR2,
    .DTPR0 = DDR_DTPR0,
    .DTPR1 = DDR_DTPR1,
    .DTPR2 = DDR_DTPR2,
    .MR0 = DDR_MR0,
    .MR1 = DDR_MR1,
    .MR2 = DDR_MR2,
    .MR3 = DDR_MR3
  }
};

/* Private function prototypes -----------------------------------------------*/
/** @defgroup DDR_Private_Functions DDR Private Functions
  * @{
  */

static void ddr_delay_us(uint32_t delay_us)
{
  __IO uint32_t wait_loop_index = 0U;

  wait_loop_index = (delay_us * (SystemCoreClock / (1000000UL * 2UL)));


  while (wait_loop_index != 0UL)
  {
    wait_loop_index--;
  }
}

/**
  * @brief  Initialize DDR timeout in us
  * @param  timeout_us timeout in us
  * @retval wait_loop_index
  */
static __IO uint32_t ddr_timeout_init_us(uint32_t timeout_us)
{
  __IO uint32_t wait_loop_index = 0U;

  wait_loop_index = timeout_us * (SystemCoreClock / (1000000UL * 2UL));


  return wait_loop_index;
}

/**
  * @brief  Check if timeout has expired
  * @param  timeout timeout in us
  * @retval Timeout status
  */
static bool ddr_timeout_elapsed(__IO uint32_t timeout)
{
  if (timeout == 0U)
  {
    return true;
  }

  return false;
}

/**
  * @brief  Save DDR training Area
  * @param  None
  * @retval Return status
  */
#if defined ( __ICCARM__ )
static bool __attribute__((unused)) save_ddr_training_area(void)
#else
static bool __unused save_ddr_training_area(void)
#endif /* __ICCARM__ */
{
  bool ret = true;

  SET_BIT(RCC->MP_AHB5ENSETR, RCC_MP_AHB5ENSETR_BKPSRAMEN);

  if (memcpy((uint32_t *)BKPSRAM_BASE, (uint32_t *)DDR_BASE_ADDR,
             DDR_TRAINING_AREA_SIZE) == NULL)
  {
    ret = false;
  }

  __DSB();

  CLEAR_BIT(RCC->MP_AHB5ENSETR, RCC_MP_AHB5ENSETR_BKPSRAMEN);

  return ret;
}

/**
  * @brief  Restore DDR training Area
  * @param  None
  * @retval Return status
  */
static bool restore_ddr_training_area(void)
{
  bool ret = true;

  SET_BIT(RCC->MP_AHB5ENSETR, RCC_MP_AHB5ENSETR_BKPSRAMEN);

  if (memcpy((uint32_t *)DDR_BASE_ADDR, (uint32_t *)BKPSRAM_BASE,
             DDR_TRAINING_AREA_SIZE) == NULL)
  {
    ret = false;
  }

  __DSB();

  CLEAR_BIT(RCC->MP_AHB5ENSETR, RCC_MP_AHB5ENSETR_BKPSRAMEN);

  return ret;
}

/* board-specific DDR power initializations. */
#if defined ( __ICCARM__ )
__weak int32_t HAL_DDR_MspInit(__attribute__((unused)) ddr_type type)
#else
__weak int32_t HAL_DDR_MspInit(__unused ddr_type type)
#endif /* __ICCARM__ */
{
  return 0;
}

/**
  * @brief  DDR Clock Register Enable
  * @param  None
  * @retval None
  */
static void ddr_enable_clock(void)
{
#ifdef DDR_DUAL_AXI_PORT
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1EN
                        | RCC_DDRITFCR_DDRC2EN
                        | RCC_DDRITFCR_DDRPHYCEN
                        | RCC_DDRITFCR_DDRPHYCAPBEN
                        | RCC_DDRITFCR_DDRCAPBEN);
#else /* DDR_DUAL_AXI_PORT */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1EN
                        | RCC_DDRITFCR_DDRPHYCEN
                        | RCC_DDRITFCR_DDRPHYCAPBEN
                        | RCC_DDRITFCR_DDRCAPBEN);
#endif /* DDR_DUAL_AXI_PORT */
}

/**
  * @brief  Set DDR Clock Speed
  * @param  mem_speed Memory Speed to be set
  * @retval HAL Status
  */
static int32_t ddr_clk_enable(uint32_t mem_speed)
{
  PLL2_ClocksTypeDef PLL2;
  uint32_t ddr_clk;
  uint32_t ddrphy_clk;
  uint32_t mem_speed_hz = mem_speed * 1000U;

  ddr_enable_clock();

  HAL_RCC_GetPLL2ClockFreq(&PLL2);
  ddrphy_clk = PLL2.PLL2_R_Frequency;

  /* Max 10% frequency delta */
  if (ddrphy_clk > mem_speed_hz)
  {
    ddr_clk = ddrphy_clk - mem_speed_hz;
  }
  else
  {
    ddr_clk = mem_speed_hz - ddrphy_clk;
  }

  if (ddr_clk > (mem_speed_hz / (uint32_t)10))
  {
    return -1; /* Return Error if  frequency deviation > 10% */
  }

  return 0;
}

/**
  * @brief  Get DDR Base Register Address
  * @param  base Base Register Type
  * @retval Return DDR Base Register Address
  */
static uint32_t get_base_addr(base_type base)
{
  if (base == BASE_DDRPHYC)
  {
    return (uint32_t)DDRPHYC_BASE;
  }
  else
  {
    return (uint32_t)DDRCTRL_BASE;
  }
}

/**
  * @brief  Set DDR Base Register Address
  * @param  base Base Register Type
  * @retval HAL Status
  */
static HAL_StatusTypeDef set_reg(reg_type type, uint32_t param)
{
  uint8_t i;
  uint32_t base_addr = get_base_addr(ddr_registers[type].base);
  const reg_desc_t *desc = ddr_registers[type].desc;

  for (i = 0; i < ddr_registers[type].size; i++)
  {
    if (desc[i].par_offset == INVALID_OFFSET)
    {
      return HAL_ERROR;
    }
    else
    {
      uint32_t address = param + (uint32_t)desc[i].par_offset;
      uint32_t *ptr = (uint32_t *)address;

      WRITE_REG(*(volatile uint32_t *)(base_addr + (uint32_t)desc[i].offset),
                *ptr);
    }
  }

  return HAL_OK;
}

static HAL_StatusTypeDef ddrphy_idone_wait(void)
{
  uint32_t pgsr;
  uint32_t error = 0U;
  uint32_t errormask = DDRPHYC_PGSR_DTERR | DDRPHYC_PGSR_DTIERR
                       | DDRPHYC_PGSR_DFTERR | DDRPHYC_PGSR_RVERR
                       | DDRPHYC_PGSR_RVEIRR;
  __IO uint32_t timeout = ddr_timeout_init_us(DDR_TIMEOUT_50_US);

  do
  {
    pgsr = READ_REG(DDRPHYC->PGSR);

    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT; /* Timeout initialising DRAM */
    }

    if ((pgsr & errormask) != 0U)
    {
      error++;
    }
  } while (((pgsr & DDRPHYC_PGSR_IDONE) == 0U) && (error == 0U));

  return HAL_OK;
}

static HAL_StatusTypeDef HAL_DDR_PHY_Init(uint32_t pir)
{
  uint32_t pir_init = pir | DDRPHYC_PIR_INIT;

  WRITE_REG(DDRPHYC->PIR, pir_init);

  /* Need to wait 10 configuration clock before start polling */
  ddr_delay_us(DDR_DELAY_PHY_INIT_US);

  /* Wait DRAM initialization and Gate Training Evaluation complete */
  return ddrphy_idone_wait();
}

static HAL_StatusTypeDef self_refresh_zcal(uint32_t zdata)
{
  /* sequence for PUBL I/O Data Retention during Power-Down */

  /* 10. Override ZQ calibration with previously (pre-retention)
   *     calibrated values. This is done by writing 1 to ZQ0CRN.ZDEN
   *     and the override data to ZQ0CRN.ZDATA.
   */
  SET_BIT(DDRPHYC->ZQ0CR0, DDRPHYC_ZQ0CR0_ZDEN);

  MODIFY_REG(DDRPHYC->ZQ0CR0,
             DDRPHYC_ZQ0CR0_ZDATA_Msk,
             zdata << DDRPHYC_ZQ0CR0_ZDATA_Pos);

  /* 11. De-assert the PHY_top data retention enable signals
   *     (ret_en or ret_en_i/ret_en_n_i).
   */
  SET_BIT(PWR->CR3, PWR_CR3_DDRSRDIS);
  CLEAR_BIT(PWR->CR3, PWR_CR3_DDRRETEN);

  /* 12. Remove ZQ calibration override by writing 0 to ZQ0CRN.ZDEN. */
  CLEAR_BIT(DDRPHYC->ZQ0CR0, DDRPHYC_ZQ0CR0_ZDEN);

  /* 13. Trigger ZQ calibration by writing 1 to PIR.INIT
   *     and '1' to PIR.ZCAL
   */
  /* 14. Wait for ZQ calibration to finish by polling a 1 status
   * on PGSR.IDONE.
   */
  return HAL_DDR_PHY_Init(DDRPHYC_PIR_ZCAL);
}

/* Start quasi dynamic register update */
static void start_sw_done(void)
{
  CLEAR_BIT(DDRCTRL->SWCTL, DDRCTRL_SWCTL_SW_DONE);
}

/* Wait quasi dynamic register update */
static HAL_StatusTypeDef wait_sw_done_ack(void)
{
  uint32_t swstat;
  __IO uint32_t timeout = ddr_timeout_init_us(DDR_TIMEOUT_1_US);

  SET_BIT(DDRCTRL->SWCTL, DDRCTRL_SWCTL_SW_DONE);

  do
  {
    swstat = READ_REG(DDRCTRL->SWSTAT);

    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT; /* Timeout initialising DRAM */
    }
  } while ((swstat & DDRCTRL_SWSTAT_SW_DONE_ACK) == 0U);

  return HAL_OK;
}

/* Wait quasi dynamic register update */
static HAL_StatusTypeDef wait_operating_mode(uint32_t mode)
{
  uint32_t stat;
  uint32_t break_loop = 0U;
  __IO uint32_t timeout = ddr_timeout_init_us(DDR_TIMEOUT_1_US);

  for (; ;)
  {
    uint32_t operating_mode;
    uint32_t selref_type;

    stat = READ_REG(DDRCTRL->STAT);
    operating_mode = stat & DDRCTRL_STAT_OPERATING_MODE_Msk;
    selref_type = stat & DDRCTRL_STAT_SELFREF_TYPE_Msk;

    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT; /* Timeout initialising DRAM */
    }

    if (mode == DDRCTRL_STAT_OPERATING_MODE_SR)
    {
      /*
       * Self-refresh due to software
       * => checking also STAT.selfref_type.
       */
      if ((operating_mode == DDRCTRL_STAT_OPERATING_MODE_SR)
          && (selref_type == DDRCTRL_STAT_SELFREF_TYPE_SR))
      {
        break_loop = 1U;
      }
    }
    else if (operating_mode == mode)
    {
      break_loop = 1U;
    }
    else if ((mode == DDRCTRL_STAT_OPERATING_MODE_NORMAL)
             && (operating_mode == DDRCTRL_STAT_OPERATING_MODE_SR)
             && (selref_type == DDRCTRL_STAT_SELFREF_TYPE_ASR))
    {
      /* Normal mode: handle also automatic self refresh */
      break_loop = 1U;
    }
    else
    {
      /* Continue loop */
    }

    if (break_loop == 1U)
    {
      break;
    }
  }

  return HAL_OK;
}

static void enable_axi_port(void)
{
  /* Enable uMCTL2 AXI port 0 */
  SET_BIT(DDRCTRL->PCTRL_0, DDRCTRL_PCTRL_0_PORT_EN);

#ifdef DDR_DUAL_AXI_PORT
  /* Enable uMCTL2 AXI port 1 */
  SET_BIT(DDRCTRL->PCTRL_1, DDRCTRL_PCTRL_0_PORT_EN);
#endif /* DDR_DUAL_AXI_PORT */
}

static int32_t disable_axi_port(void)
{
  __IO uint32_t timeout;

  /* Disable uMCTL2 AXI port 0 */
  CLEAR_BIT(DDRCTRL->PCTRL_0, DDRCTRL_PCTRL_0_PORT_EN);
#ifdef DDR_DUAL_AXI_PORT
  CLEAR_BIT(DDRCTRL->PCTRL_1, DDRCTRL_PCTRL_0_PORT_EN);
#endif  /* DDR_DUAL_AXI_PORT */

  /* Waits unit all AXI ports are idle
   * Poll PSTAT.rd_port_busy_n = 0
   * Poll PSTAT.wr_port_busy_n = 0
   */
  timeout = ddr_timeout_init_us(DDR_TIMEOUT_1S);
  while (READ_REG(DDRCTRL->PSTAT) != 0U)
  {
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return -1;
    }
  }

  return 0;
}

static void enable_host_interface(void)
{
  CLEAR_BIT(DDRCTRL->DBG1, DDRCTRL_DBG1_DIS_HIF);
}

static int32_t disable_host_interface(void)
{
  __IO uint32_t timeout;
  uint32_t dbgcam;
  uint32_t count = 0;

  SET_BIT(DDRCTRL->DBG1, DDRCTRL_DBG1_DIS_HIF);

  /*
   * Waits until all queues and pipelines are empty
   * Poll DBGCAM.dbg_wr_q_empty = 1
   * Poll DBGCAM.dbg_rd_q_empty = 1
   * Poll DBGCAM.dbg_wr_data_pipeline_empty = 1
   * Poll DBGCAM.dbg_rd_data_pipeline_empty = 1
   *
   * data_pipeline fields must be polled twice to ensure
   * value propoagation, so count is added to loop condition.
   */
  timeout = ddr_timeout_init_us(DDR_TIMEOUT_1S);
  do
  {
    dbgcam = READ_REG(DDRCTRL->DBGCAM);
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return -1;
    }
    count++;
  } while (((dbgcam & DDRCTRL_DBG_Q_AND_DATA_PIPELINE_EMPTY) !=
            DDRCTRL_DBG_Q_AND_DATA_PIPELINE_EMPTY) || (count < 2U));

  return 0;
}

static int32_t sw_selfref_entry(void)
{
  __IO uint32_t timeout;
  uint32_t stat;
  uint32_t operating_mode;
  uint32_t selref_type;

  /* SW Self-Refresh entry */
  SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_SW);

  /* Wait operating mode change in self-refresh mode
   * with STAT.operating_mode[1:0]==11.
   * Ensure transition to self-refresh was due to software
   * by checking also that STAT.selfref_type[1:0]=2.
   */
  timeout = ddr_timeout_init_us(DDR_TIMEOUT_500_US);

  while (!ddr_timeout_elapsed(timeout))
  {
    stat = READ_REG(DDRCTRL->STAT);
    operating_mode = stat & DDRCTRL_STAT_OPERATING_MODE_Msk;
    selref_type = stat & DDRCTRL_STAT_SELFREF_TYPE_Msk;
    timeout--;

    if ((operating_mode == DDRCTRL_STAT_OPERATING_MODE_SR)
        && (selref_type == DDRCTRL_STAT_SELFREF_TYPE_SR))
    {
      return 0;
    }
  }

  return -1;
}

static void sw_selfref_exit(void)
{
  CLEAR_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_SW);
}

static int32_t set_qd3_update_conditions(void)
{
  if (disable_axi_port() != 0)
  {
    return -1;
  }
  if (disable_host_interface() != 0)
  {
    return -1;
  }
  start_sw_done();

  return 0;
}

static HAL_StatusTypeDef unset_qd3_update_conditions(void)
{
  HAL_StatusTypeDef ret;

  ret = wait_sw_done_ack();
  if (ret != HAL_OK)
  {
    return ret;
  }
  enable_host_interface();
  enable_axi_port();

  return ret;
}

static int32_t wait_refresh_update_done_ack(void)
{
  __IO uint32_t timeout;
  uint32_t rfshctl3;
  uint32_t refresh_update_level  = DDRCTRL_RFSHCTL3_REFRESH_UPDATE_LEVEL;

  /* Toggle rfshctl3.refresh_update_level */
  rfshctl3 = READ_REG(DDRCTRL->RFSHCTL3);
  if ((rfshctl3 & refresh_update_level) == refresh_update_level)
  {
    SET_BIT(DDRCTRL->RFSHCTL3, refresh_update_level);
  }
  else
  {
    CLEAR_BIT(DDRCTRL->RFSHCTL3, refresh_update_level);
    refresh_update_level = 0U;
  }

  timeout = ddr_timeout_init_us(DDR_TIMEOUT_1S);
  do
  {
    rfshctl3 = READ_REG(DDRCTRL->RFSHCTL3);
    timeout--;

    if (ddr_timeout_elapsed(timeout))
    {
      return -1;
    }
  } while ((rfshctl3 & DDRCTRL_RFSHCTL3_REFRESH_UPDATE_LEVEL) !=
           refresh_update_level);

  return 0;
}

/* Mode Register Writes (MRW or MRS) */
static HAL_StatusTypeDef mode_register_write(uint32_t addr, uint32_t data)
{
  uint32_t mrctrl0;
  __IO uint32_t timeout = ddr_timeout_init_us(DDR_TIMEOUT_200_MS);

  /*
   * 1. Poll MRSTAT.mr_wr_busy until it is '0'.
   *    This checks that there is no outstanding MR transaction.
   *    No write should be performed to MRCTRL0 and MRCTRL1
   *    if MRSTAT.mr_wr_busy = 1.
   */
  while ((READ_REG(DDRCTRL->MRSTAT) & DDRCTRL_MRSTAT_MR_WR_BUSY) != 0U)
  {
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT;
    }
  }

  /*
   * 2. Write the MRCTRL0.mr_type, MRCTRL0.mr_addr, MRCTRL0.mr_rank
   *    and (for MRWs) MRCTRL1.mr_data to define the MR transaction.
   */
  mrctrl0 = DDRCTRL_MRCTRL0_MR_TYPE_WRITE
            | DDRCTRL_MRCTRL0_MR_RANK_ALL
            | ((addr << DDRCTRL_MRCTRL0_MR_ADDR_Pos)
               & DDRCTRL_MRCTRL0_MR_ADDR_Msk);

  WRITE_REG(DDRCTRL->MRCTRL0, mrctrl0);
  WRITE_REG(DDRCTRL->MRCTRL1, data);

  /*
   * 3. In a separate APB transaction, write the MRCTRL0.mr_wr to 1. This
   *    bit is self-clearing, and triggers the MR transaction.
   *    The uMCTL2 then asserts the MRSTAT.mr_wr_busy while it performs
   *    the MR transaction to SDRAM, and no further access can be
   *    initiated until it is deasserted.
   */
  mrctrl0 |= DDRCTRL_MRCTRL0_MR_WR;
  WRITE_REG(DDRCTRL->MRCTRL0, mrctrl0);

  timeout = ddr_timeout_init_us(DDR_TIMEOUT_200_MS);
  while ((READ_REG(DDRCTRL->MRSTAT) & DDRCTRL_MRSTAT_MR_WR_BUSY) != 0U)
  {
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/* Switch DDR3 from DLL-on to DLL-off */
static HAL_StatusTypeDef ddr3_dll_off(void)
{
  HAL_StatusTypeDef ret;
  uint32_t mr1 = READ_REG(DDRPHYC->MR1);
  uint32_t mr2 = READ_REG(DDRPHYC->MR2);
  uint32_t dbgcam;
  __IO uint32_t timeout = ddr_timeout_init_us(DDR_TIMEOUT_200_MS);

  /*
   * 1. Set the DBG1.dis_hif = 1.
   *    This prevents further reads/writes being received on the HIF.
   */
  SET_BIT(DDRCTRL->DBG1, DDRCTRL_DBG1_DIS_HIF);

  /*
   * 2. Ensure all commands have been flushed from the uMCTL2 by polling
   *    DBGCAM.wr_data_pipeline_empty = 1,
   *    DBGCAM.rd_data_pipeline_empty = 1,
   *    DBGCAM.dbg_wr_q_depth = 0 ,
   *    DBGCAM.dbg_lpr_q_depth = 0, and
   *    DBGCAM.dbg_hpr_q_depth = 0.
   */
  do
  {
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT;
    }

    dbgcam = READ_REG(DDRCTRL->DBGCAM);
  } while ((((dbgcam & DDRCTRL_DBGCAM_DATA_PIPELINE_EMPTY)
             == DDRCTRL_DBGCAM_DATA_PIPELINE_EMPTY))
           && ((dbgcam & DDRCTRL_DBGCAM_DBG_Q_DEPTH) == 0U));

  /*
   * 3. Perform an MRS command (using MRCTRL0 and MRCTRL1 registers)
   *    to disable RTT_NOM:
   *    a. DDR3: Write to MR1[9], MR1[6] and MR1[2]
   *    b. DDR4: Write to MR1[10:8]
   */
  mr1 &= ~(DDRPHYC_MR1_RTT0 | DDRPHYC_MR1_RTT1
           | DDRPHYC_MR1_RTT2);
  ret = mode_register_write(1U, mr1);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   * 4. For DDR4 only: Perform an MRS command
   *    (using MRCTRL0 and MRCTRL1 registers) to write to MR5[8:6]
   *    to disable RTT_PARK
   */

  /*
   * 5. Perform an MRS command (using MRCTRL0 and MRCTRL1 registers)
   *    to write to MR2[10:9], to disable RTT_WR
   *    (and therefore disable dynamic ODT).
   *    This applies for both DDR3 and DDR4.
   */
  mr2 &= ~DDRPHYC_MR2_RTTWR_Msk;
  ret = mode_register_write(2U, mr2);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   * 6. Perform an MRS command (using MRCTRL0 and MRCTRL1 registers)
   *    to disable the DLL. The timing of this MRS is automatically
   *    handled by the uMCTL2.
   *    a. DDR3: Write to MR1[0]
   *    b. DDR4: Write to MR1[0]
   */
  mr1 |= DDRPHYC_MR1_DE;
  ret = mode_register_write(1U, mr1);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   * 7. Put the SDRAM into self-refresh mode by setting
   *    PWRCTL.selfref_sw = 1, and polling STAT.operating_mode to ensure
   *    the DDRC has entered self-refresh.
   */
  SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_SW);

  /*
   * 8. Wait until STAT.operating_mode[1:0]==11 indicating that the
   *    DWC_ddr_umctl2 core is in self-refresh mode.
   *    Ensure transition to self-refresh was due to software
   *    by checking that STAT.selfref_type[1:0]=2.
   */
  ret = wait_operating_mode(DDRCTRL_STAT_OPERATING_MODE_SR);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   * 9. Set the MSTR.dll_off_mode = 1.
   *    warning: MSTR.dll_off_mode is a quasi-dynamic type 2 field
   */
  start_sw_done();

  SET_BIT(DDRCTRL->MSTR, DDRCTRL_MSTR_DLL_OFF_MODE);

  ret = wait_sw_done_ack();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* 10. Change the clock frequency to the desired value. */

  /*
   * 11. Update any registers which may be required to change for the new
   *     frequency. This includes static and dynamic registers.
   *     This includes both uMCTL2 registers and PHY registers.
   */

  /* Change Bypass Mode Frequency Range (depends on DDRPHYC_CLK_RATE) */
  if (static_ddr_config.info.speed < 100000U)
  {
    CLEAR_BIT(DDRPHYC->DLLGCR, DDRPHYC_DLLGCR_BPS200);
  }
  else
  {
    SET_BIT(DDRPHYC->DLLGCR, DDRPHYC_DLLGCR_BPS200);
  }

  SET_BIT(DDRPHYC->ACDLLCR, DDRPHYC_ACDLLCR_DLLDIS);

  SET_BIT(DDRPHYC->DX0DLLCR, DDRPHYC_DX0DLLCR_DLLDIS);
  SET_BIT(DDRPHYC->DX1DLLCR, DDRPHYC_DX1DLLCR_DLLDIS);
#ifdef DDR_32BIT_INTERFACE
  SET_BIT(DDRPHYC->DX2DLLCR, DDRPHYC_DX2DLLCR_DLLDIS);
  SET_BIT(DDRPHYC->DX3DLLCR, DDRPHYC_DX3DLLCR_DLLDIS);
#endif /* DDR_32BIT_INTERFACE */

  /* 12. Exit the self-refresh state by setting PWRCTL.selfref_sw = 0. */
  CLEAR_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_SW);
  ret = wait_operating_mode(DDRCTRL_STAT_OPERATING_MODE_NORMAL);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   * 13. If ZQCTL0.dis_srx_zqcl = 0, the uMCTL2 performs a ZQCL command
   *     at this point.
   */

  /*
   * 14. Perform MRS commands as required to re-program timing registers
   *     in the SDRAM for the new frequency
   *     (in particular, CL, CWL and WR may need to be changed).
   */

  /* 15. Write DBG1.dis_hif = 0 to re-enable reads and writes. */
  CLEAR_BIT(DDRCTRL->DBG1, DDRCTRL_DBG1_DIS_HIF);

  return ret;
}

static HAL_StatusTypeDef HAL_DDR_Refresh_Disable(void)
{
  HAL_StatusTypeDef ret;

  /*
   * manage quasi-dynamic registers modification
   * dfimisc.dfi_init_complete_en : Group 3
   * AXI ports not yet enabled, don't disable them
   */
  if (disable_host_interface() != 0)
  {
    return HAL_ERROR;
  }

  start_sw_done();

  /* Quasi-dynamic register update*/
  SET_BIT(DDRCTRL->RFSHCTL3, DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH);

  if (wait_refresh_update_done_ack() != 0)
  {
    return HAL_ERROR;
  }

  CLEAR_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_POWERDOWN_EN
                            | DDRCTRL_PWRCTL_SELFREF_EN);
  CLEAR_BIT(DDRCTRL->DFIMISC, DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN);

  ret = wait_sw_done_ack();
  if (ret != HAL_OK)
  {
    return ret;
  }

  enable_host_interface();

  return HAL_OK;
}

static HAL_StatusTypeDef HAL_DDR_Refresh_Restore(uint32_t rfshctl3, uint32_t pwrctl)
{
  HAL_StatusTypeDef ret;

  /*
   * manage quasi-dynamic registers modification
   * dfimisc.dfi_init_complete_en : Group 3
   * AXI ports not yet enabled, don't disable them
   */
  if (disable_host_interface() != 0)
  {
    return HAL_ERROR;
  }

  start_sw_done();

  if ((rfshctl3 & DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH) == 0U)
  {
    CLEAR_BIT(DDRCTRL->RFSHCTL3, DDRCTRL_RFSHCTL3_DIS_AUTO_REFRESH);
    if (wait_refresh_update_done_ack() != 0)
    {
      return HAL_ERROR;
    }
  }

  if ((pwrctl & DDRCTRL_PWRCTL_POWERDOWN_EN) != 0U)
  {
    SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_POWERDOWN_EN);
  }

  if ((pwrctl & DDRCTRL_PWRCTL_SELFREF_EN) != 0U)
  {
    SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_EN);
  }

  SET_BIT(DDRCTRL->DFIMISC, DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN);

  ret = wait_sw_done_ack();
  if (ret != HAL_OK)
  {
    return ret;
  }

  enable_host_interface();

  return HAL_OK;
}

static uint32_t get_timer(uint32_t base)
{
  return (uint32_t)PL1_GetCurrentPhysicalValue() - base;
}

static HAL_StatusTypeDef refresh_cmd(void)
{
  uint32_t dbgstat;
  __IO uint32_t timeout = ddr_timeout_init_us(DDR_TIMEOUT_200_MS);

  do
  {
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT;
    }

    dbgstat = READ_REG(DDRCTRL->DBGSTAT);
  } while ((dbgstat & DDRCTRL_DBGSTAT_RANK0_REFRESH_BUSY) != 0U);

  SET_BIT(DDRCTRL->DBGCMD, DDRCTRL_DBGCMD_RANK0_REFRESH);

  return HAL_OK;
}

/* Refresh compensation by forcing refresh command
 * Rule1: Tref should be always < tREFW ? R x tREBW/8
 * Rule2: refcomp = RU(Tref/tREFI)  = RU(RxTref/tREFW)
 */
static HAL_StatusTypeDef refresh_compensation(uint32_t start)
{
  HAL_StatusTypeDef res = HAL_OK;
  uint32_t tck_ps;
  uint32_t tref;
  uint32_t trefi;
  uint32_t refcomp;
  uint32_t i;
  uint32_t time;
  uint32_t time_us;

  time = get_timer(start);
  time_us = time / TIMESLOT_1US;

  tck_ps = 1000000000U / static_ddr_config.info.speed;
  if (tck_ps == 0U)
  {
    return res;
  }

  /* ref = refresh time in tck */
  tref = time_us * 1000000U / tck_ps;

  trefi = ((READ_REG(DDRCTRL->RFSHTMG) & DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Msk)
           >> DDRCTRL_RFSHTMG_T_RFC_NOM_X1_X32_Pos) * 32U;
  if (trefi == 0U)
  {
    return res;
  }

  /* div round up : number of refresh to compensate */
  refcomp = (tref + trefi - 1U) / trefi;

  for (i = 0U; i < refcomp; i++)
  {
    res = refresh_cmd();
    if (res != HAL_OK)
    {
      return res;
    }
  }

  return res;
}

static int32_t ddr_sw_self_refresh_in(void)
{
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_AXIDCGEN);

  if (disable_axi_port() != 0)
  {
    /* pstat failed */
    enable_axi_port();

    return -1;
  }

  /* SW Self-Refresh entry */
  if (sw_selfref_entry() != 0)
  {
    /* selfref_sw_failed: restore DDR in its previous state */
    sw_selfref_exit();

    enable_axi_port();

    return -1;
  }

  /* IOs powering down (PUBL registers) */
  SET_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_ACPDD);
  SET_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_ACPDR);
  MODIFY_REG(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_CKPDD_Msk, DDRPHYC_ACIOCR_CKPDD_0);
  MODIFY_REG(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_CKPDR_Msk, DDRPHYC_ACIOCR_CKPDR_0);
  SET_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_CSPDD);

  /* Disable command/address output driver */
  CLEAR_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_ACOE);
  SET_BIT(DDRPHYC->DXCCR, DDRPHYC_DXCCR_DXPDD);
  SET_BIT(DDRPHYC->DXCCR, DDRPHYC_DXCCR_DXPDR);
  SET_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_ODTPDD);
  SET_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_NL2PD);
  SET_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_CKEPDD);

  /* Disable PZQ cell (PUBL register) */
  SET_BIT(DDRPHYC->ZQ0CR0, DDRPHYC_ZQ0CR0_ZQPD);

  /* Set latch */
  CLEAR_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_CKOE);

  /* Additional delay to avoid early latch, 10us */
  ddr_delay_us(DDR_DELAY_10_US);

  /* Activate sw retention in PWRCTRL */
  SET_BIT(PWR->CR3, PWR_CR3_DDRRETEN);

  /* Switch controller clocks (uMCTL2/PUBL) to DLL ref clock */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_GSKPCTRL);

  /* Disable all DLLs: GLITCH window */
  SET_BIT(DDRPHYC->ACDLLCR, DDRPHYC_ACDLLCR_DLLDIS);
  SET_BIT(DDRPHYC->DX0DLLCR, DDRPHYC_DX0DLLCR_DLLDIS);
  SET_BIT(DDRPHYC->DX1DLLCR, DDRPHYC_DX1DLLCR_DLLDIS);
#ifdef DDR_32BIT_INTERFACE
  SET_BIT(DDRPHYC->DX2DLLCR, DDRPHYC_DX2DLLCR_DLLDIS);
  SET_BIT(DDRPHYC->DX3DLLCR, DDRPHYC_DX3DLLCR_DLLDIS);
#endif /* DDR_32BIT_INTERFACE */

  /* Switch controller clocks (uMCTL2/PUBL) to DLL output clock */
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_GSKPCTRL);

  /* Deactivate all DDR clocks */
#ifdef DDR_DUAL_AXI_PORT
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1EN
                          | RCC_DDRITFCR_DDRC2EN
                          | RCC_DDRITFCR_DDRCAPBEN
                          | RCC_DDRITFCR_DDRPHYCAPBEN);
#else /* DDR_DUAL_AXI_PORT */
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1EN
                          | RCC_DDRITFCR_DDRCAPBEN
                          | RCC_DDRITFCR_DDRPHYCAPBEN);
#endif /* DDR_DUAL_AXI_PORT */

  return 0;
}

/*******************************************************************************
  * This function tests a simple read/write access to the DDR.
  * Note that the previous content is restored after test.
  * Returns 0 if success, and address value else.
  ******************************************************************************/
static uint32_t ddr_test_rw_access(void)
{
  uint32_t saved_value = READ_REG(*(volatile uint32_t *)DDR_BASE_ADDR);

  WRITE_REG(*(volatile uint32_t *)DDR_BASE_ADDR, DDR_PATTERN);

  if (READ_REG(*(volatile uint32_t *)DDR_BASE_ADDR) != DDR_PATTERN)
  {
    return (uint32_t)DDR_BASE_ADDR;
  }

  WRITE_REG(*(volatile uint32_t *)DDR_BASE_ADDR, saved_value);

  return 0U;
}

/*******************************************************************************
  * This function tests the DDR data bus wiring.
  * This is inspired from the Data Bus Test algorithm written by Michael Barr
  * in "Programming Embedded Systems in C and C++" book.
  * resources.oreilly.com/examples/9781565923546/blob/master/Chapter6/
  * File: memtest.c - This source code belongs to Public Domain.
  * Returns 0 if success, and address value else.
  ******************************************************************************/
static uint32_t ddr_test_data_bus(void)
{
  uint32_t i;
  uint32_t pattern;

  for (i = 0U; i < 32U; i++)
  {
    pattern = (uint32_t)1 << i;

    WRITE_REG(*(volatile uint32_t *)DDR_BASE_ADDR, pattern);

    if (READ_REG(*(volatile uint32_t *)DDR_BASE_ADDR) != pattern)
    {
      return (uint32_t)DDR_BASE_ADDR;
    }
  }

  return 0U;
}

/*******************************************************************************
  * This function tests the DDR address bus wiring.
  * This is inspired from the Data Bus Test algorithm written by Michael Barr
  * in "Programming Embedded Systems in C and C++" book.
  * resources.oreilly.com/examples/9781565923546/blob/master/Chapter6/
  * File: memtest.c - This source code belongs to Public Domain.
  * Returns 0 if success, and address value else.
  ******************************************************************************/
static uint32_t ddr_test_addr_bus(void)
{
  uint32_t addressmask = (static_ddr_config.info.size - 1U);
  uint32_t offset;
  uint32_t testoffset = 0;

  /* Write the default pattern at each of the power-of-two offsets. */
  for (offset = sizeof(uint32_t); (offset & addressmask) != 0U; offset <<= 1)
  {
    WRITE_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + (uint32_t)offset),
              DDR_PATTERN);
  }

  /* Check for address bits stuck high. */
  WRITE_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + (uint32_t)testoffset),
            DDR_ANTIPATTERN);

  for (offset = sizeof(uint32_t); (offset & addressmask) != 0U; offset <<= 1)
  {
    if (READ_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + (uint32_t)offset))
        != DDR_PATTERN)
    {
      return (uint32_t)(DDR_BASE_ADDR + offset);
    }
  }

  WRITE_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + (uint32_t)testoffset),
            DDR_PATTERN);

  /* Check for address bits stuck low or shorted. */
  for (testoffset = sizeof(uint32_t); (testoffset & addressmask) != 0U;
       testoffset <<= 1)
  {
    WRITE_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + (uint32_t)testoffset),
              DDR_ANTIPATTERN);

    if (READ_REG(*(volatile uint32_t *)DDR_BASE_ADDR) != DDR_PATTERN)
    {
      return DDR_BASE_ADDR;
    }

    for (offset = sizeof(uint32_t); (offset & addressmask) != 0U;
         offset <<= 1)
    {
      if ((READ_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + (uint32_t)offset))
           != DDR_PATTERN)
          && (offset != testoffset))
      {
        return (uint32_t)(DDR_BASE_ADDR + offset);
      }
    }

    WRITE_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + (uint32_t)testoffset),
              DDR_PATTERN);
  }

  return 0U;
}

/*******************************************************************************
  * This function checks the DDR size. It has to be run with Data Cache off.
  * This test is run before data have been put in DDR, and is only done for
  * cold boot. The DDR data can then be overwritten, and it is not useful to
  * restore its content.
  * Returns DDR computed size.
  ******************************************************************************/
static uint32_t ddr_check_size(void)
{
  uint32_t offset = sizeof(uint32_t);

  WRITE_REG(*(volatile uint32_t *)DDR_BASE_ADDR, DDR_PATTERN);

  while (offset < DDR_MAX_SIZE)
  {
    WRITE_REG(*(volatile uint32_t *)(DDR_BASE_ADDR + offset), DDR_ANTIPATTERN);
    __DSB();

    if (READ_REG(*(volatile uint32_t *)DDR_BASE_ADDR) != DDR_PATTERN)
    {
      break;
    }

    offset <<= 1;
  }

  return offset;
}

static bool ddr_supports_ssr_asr(void)
{
  uint32_t mstr = READ_REG(DDRCTRL->MSTR);

  return (mstr & DDRCTRL_MSTR_LPDDR2) != 0U;
}

static HAL_StatusTypeDef ddr_sr_mode_ssr(void)
{
  HAL_StatusTypeDef ret;

  if (!ddr_supports_ssr_asr())
  {
    return HAL_OK;
  }

  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1LPEN);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1EN);
#ifdef DDR_DUAL_AXI_PORT
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC2LPEN);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC2EN);
#endif /* DDR_DUAL_AXI_PORT */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCAPBLPEN);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRPHYCAPBLPEN);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCAPBEN);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRPHYCAPBEN);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRPHYCEN);
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_AXIDCGEN);
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCKMOD_Msk);

  /**
    * manage quasi-dynamic registers modification
    * hwlpctl.hw_lp_en : Group 3
    * pwrtmg.selfref_to_x32 & powerdown_to_x32 : Group 4
    * Group 3 is the most restrictive, apply its conditions for all
    */
  if (set_qd3_update_conditions() != 0)
  {
    return HAL_ERROR;
  }

  /* Disable HW LP interface of uMCTL2 */
  CLEAR_BIT(DDRCTRL->HWLPCTL, DDRCTRL_HWLPCTL_HW_LP_EN);

  /* Configure Automatic LP modes of uMCTL2 */
  MODIFY_REG(DDRCTRL->PWRTMG, DDRCTRL_PWRTMG_SELFREF_TO_X32_Msk,
             DDRCTRL_PWRTMG_SELFREF_TO_X32_0);

  ret = unset_qd3_update_conditions();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /**
    * Disable Clock disable with LP modes
    * (used in RUN mode for LPDDR2 with specific timing).
    */
  CLEAR_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE);

  /* Disable automatic Self-Refresh mode */
  CLEAR_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_EN);

  return ret;
}

static HAL_StatusTypeDef ddr_sr_mode_asr(void)
{
  HAL_StatusTypeDef ret;

  if (!ddr_supports_ssr_asr())
  {
    return HAL_OK;
  }

  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_AXIDCGEN);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1LPEN);
#ifdef DDR_DUAL_AXI_PORT
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC2LPEN);
#endif /* DDR_DUAL_AXI_PORT */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRPHYCLPEN);
  MODIFY_REG(RCC->DDRITFCR, RCC_DDRITFCR_DDRCKMOD_Msk,
             RCC_DDRITFCR_DDRCKMOD_ASR1);

  /**
    * manage quasi-dynamic registers modification
    * hwlpctl.hw_lp_en : Group 3
    * pwrtmg.selfref_to_x32 & powerdown_to_x32 : Group 4
    * Group 3 is the most restrictive, apply its conditions for all
    */
  if (set_qd3_update_conditions() != 0)
  {
    return HAL_ERROR;
  }

  /* Enable HW LP interface of uMCTL2 */
  SET_BIT(DDRCTRL->HWLPCTL, DDRCTRL_HWLPCTL_HW_LP_EN);

  /* Configure Automatic LP modes of uMCTL2 */
  MODIFY_REG(DDRCTRL->PWRTMG, DDRCTRL_PWRTMG_SELFREF_TO_X32_Msk,
             DDRCTRL_PWRTMG_SELFREF_TO_X32_0);

  ret = unset_qd3_update_conditions();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /**
    * Enable Clock disable with LP modes
    * (used in RUN mode for LPDDR2 with specific timing).
    */
  SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE);

  /* Enable automatic Self-Refresh for ASR mode */
  SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_EN);

  return ret;
}

static HAL_StatusTypeDef ddr_sr_mode_hsr(void)
{
  HAL_StatusTypeDef ret;

  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_AXIDCGEN);
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC1LPEN);
#ifdef DDR_DUAL_AXI_PORT
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRC2LPEN);
#endif /* DDR_DUAL_AXI_PORT */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRPHYCLPEN);
  MODIFY_REG(RCC->DDRITFCR, RCC_DDRITFCR_DDRCKMOD_Msk,
             RCC_DDRITFCR_DDRCKMOD_HSR1);

  /**
    * manage quasi-dynamic registers modification
    * hwlpctl.hw_lp_en : Group 3
    * pwrtmg.selfref_to_x32 & powerdown_to_x32 : Group 4
    * Group 3 is the most restrictive, apply its conditions for all
    */
  if (set_qd3_update_conditions() != 0)
  {
    return HAL_ERROR;
  }

  /* Enable HW LP interface of uMCTL2 */
  SET_BIT(DDRCTRL->HWLPCTL, DDRCTRL_HWLPCTL_HW_LP_EN);

  /* Configure Automatic LP modes of uMCTL2 */
  MODIFY_REG(DDRCTRL->PWRTMG, DDRCTRL_PWRTMG_SELFREF_TO_X32_Msk,
             DDRCTRL_PWRTMG_SELFREF_TO_X32_0);

  ret = unset_qd3_update_conditions();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /**
    * Enable Clock disable with LP modes
    * (used in RUN mode for LPDDR2 with specific timing).
    */
  SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE);

  return ret;
}

static HAL_DDR_SelfRefreshModeTypeDef ddr_sr_read_mode(void)
{
  uint32_t pwrctl = READ_REG(DDRCTRL->PWRCTL);
  HAL_DDR_SelfRefreshModeTypeDef ret;

  switch (pwrctl & (DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE |
                    DDRCTRL_PWRCTL_SELFREF_EN))
  {
    case 0U:
      ret = HAL_DDR_SW_SELF_REFRESH_MODE;
      break;
    case DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE:
      ret = HAL_DDR_HW_SELF_REFRESH_MODE;
      break;
    case DDRCTRL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE | DDRCTRL_PWRCTL_SELFREF_EN:
      ret = HAL_DDR_AUTO_SELF_REFRESH_MODE;
      break;
    default:
      ret = HAL_DDR_INVALID_MODE;
      break;
  }

  return ret;
}

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup DDR_Exported_Functions DDR Exported Functions
  * @{
  */


/**
  * @brief  DDR init sequence, including
  *         - reset/clock/power management (i.e. access to other IPs),
  *         - DDRCTRL and DDRPHY configuration and initialization,
  *         - self-refresh mode setup,
  *         - data/addr tests execution after training.
  * @param  iddr DDR initialisation structure
  * @retval None.
  */
HAL_StatusTypeDef HAL_DDR_Init(DDR_InitTypeDef *iddr)
{
  HAL_StatusTypeDef ret;
  int32_t iret;
  uint32_t ddr_reten;
  uint32_t pir;
  uint32_t uret;
  uint32_t time;
  uint32_t bus_width;

  iddr->self_refresh = false;

  if (iddr->wakeup_from_standby)
  {
    iddr->self_refresh = true;
  }

  /* Disable axidcg clock gating during init */
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_AXIDCGEN);

  switch (static_ddr_config.c_reg.MSTR & DDRCTRL_MSTR_DATA_BUS_WIDTH)
  {
    case DDRCTRL_MSTR_DATA_BUS_WIDTH_QUARTER:
      bus_width = 8U;
      break;
    case DDRCTRL_MSTR_DATA_BUS_WIDTH_HALF:
      bus_width = 16U;
      break;
    default:
      bus_width = 32U;
      break;
  }


  if ((static_ddr_config.c_reg.MSTR & DDRCTRL_MSTR_DDR3) != 0U)
  {
    iret = HAL_DDR_MspInit(STM32MP_DDR3);
  }
  else if ((static_ddr_config.c_reg.MSTR & DDRCTRL_MSTR_LPDDR2) != 0U)
  {
    if (bus_width == 32U)
    {
      iret = HAL_DDR_MspInit(STM32MP_LPDDR2_32);
    }
    else
    {
      iret = HAL_DDR_MspInit(STM32MP_LPDDR2_16);
    }
  }
  else if ((static_ddr_config.c_reg.MSTR & DDRCTRL_MSTR_LPDDR3) != 0U)
  {
    if (bus_width == 32U)
    {
      iret = HAL_DDR_MspInit(STM32MP_LPDDR3_32);
    }
    else
    {
      iret = HAL_DDR_MspInit(STM32MP_LPDDR3_16);
    }
  }
  else
  {
    /*  Unsupported DDR type */
    return HAL_ERROR;
  }

  if (iret != 0)
  {
    return HAL_ERROR;
  }

  /* Check DDR PHY pads retention */
  ddr_reten = READ_REG(PWR->CR3) & PWR_CR3_DDRRETEN;
  if (iddr->self_refresh)
  {
    if (ddr_reten == 0U)
    {
      iddr->self_refresh = false;
    }
  }
  else
  {
    if (ddr_reten != 0U)
    {
      SET_BIT(PWR->CR3, PWR_CR3_DDRSRDIS);
      CLEAR_BIT(PWR->CR3, PWR_CR3_DDRRETEN);
    }
  }

  /* DDR INIT SEQUENCE */

  /*
   * 1. Program the DWC_ddr_umctl2 registers
   *     nota: check DFIMISC.dfi_init_complete = 0
   */

  /* 1.1 RESETS: presetn, core_ddrc_rstn, aresetn */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCAPBRST);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCAXIRST);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCORERST);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DPHYAPBRST);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DPHYRST);
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DPHYCTLRST);

  /* 1.2. start CLOCK */
  if (ddr_clk_enable(static_ddr_config.info.speed) != 0)
  {
    return HAL_ERROR;
  }

  /* 1.3. deassert reset */
  /* De-assert PHY rstn and ctl_rstn via DPHYRST and DPHYCTLRST. */
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DPHYRST);
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DPHYCTLRST);
  /*
   * De-assert presetn once the clocks are active
   * and stable via DDRCAPBRST bit.
   */
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCAPBRST);

  /* 1.4. wait 128 cycles to permit initialization of end logic */
  /* For PCLK = 133MHz => 1 us is enough, 2 to allow lower frequency */
  ddr_delay_us(DDR_DELAY_END_LOGIC_INIT_US);

  /* 1.5. initialize registers ddr_umctl2 */
  /* Stop uMCTL2 before PHY is ready */
  CLEAR_BIT(DDRCTRL->DFIMISC, DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN);

  ret = set_reg(REG_REG, (uint32_t)&static_ddr_config.c_reg);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* DDR3 = don't set DLLOFF for init mode */
  if ((static_ddr_config.c_reg.MSTR
       & (DDRCTRL_MSTR_DDR3 | DDRCTRL_MSTR_DLL_OFF_MODE))
      == (DDRCTRL_MSTR_DDR3 | DDRCTRL_MSTR_DLL_OFF_MODE))
  {
    CLEAR_BIT(DDRCTRL->MSTR, DDRCTRL_MSTR_DLL_OFF_MODE);
  }

  ret = set_reg(REG_TIMING, (uint32_t)&static_ddr_config.c_timing);
  if (ret != HAL_OK)
  {
    return ret;
  }
  ret = set_reg(REG_MAP, (uint32_t)&static_ddr_config.c_map);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* Keep the controller in self-refresh mode */
  if (iddr->self_refresh)
  {
    SET_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_SW);
  }

  /* Skip CTRL init, SDRAM init is done by PHY PUBL */
  MODIFY_REG(DDRCTRL->INIT0, DDRCTRL_INIT0_SKIP_DRAM_INIT_Msk,
             DDRCTRL_INIT0_SKIP_DRAM_INIT_NORMAL);

  ret = set_reg(REG_PERF, (uint32_t)&static_ddr_config.c_perf);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*  2. deassert reset signal core_ddrc_rstn, aresetn and presetn */
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCORERST);
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DDRCAXIRST);
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_DPHYAPBRST);

  /*
   * 3. start PHY init by accessing relevant PUBL registers
   *    (DXGCR, DCR, PTR*, MR*, DTPR*)
   */
  ret = set_reg(REGPHY_REG, (uint32_t)&static_ddr_config.p_reg);
  if (ret != HAL_OK)
  {
    return ret;
  }
  ret = set_reg(REGPHY_TIMING, (uint32_t)&static_ddr_config.p_timing);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* DDR3 = don't set DLLOFF for init mode */
  if ((static_ddr_config.c_reg.MSTR
       & (DDRCTRL_MSTR_DDR3 | DDRCTRL_MSTR_DLL_OFF_MODE))
      == (DDRCTRL_MSTR_DDR3 | DDRCTRL_MSTR_DLL_OFF_MODE))
  {
    CLEAR_BIT(DDRPHYC->MR1, DDRPHYC_MR1_DE);
  }

  /*
   *  4. Monitor PHY init status by polling PUBL register PGSR.IDONE
   *     Perform DDR PHY DRAM initialization and Gate Training Evaluation
   */
  ret = ddrphy_idone_wait();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   *  5. Indicate to PUBL that controller performs SDRAM initialization
   *     by setting PIR.INIT and PIR CTLDINIT and pool PGSR.IDONE
   *     DRAM init is done by PHY, init0.skip_dram.init = 1
   */

  pir = DDRPHYC_PIR_DLLSRST | DDRPHYC_PIR_DLLLOCK | DDRPHYC_PIR_ZCAL
        | DDRPHYC_PIR_ITMSRST | DDRPHYC_PIR_DRAMINIT | DDRPHYC_PIR_ICPC;

  if ((static_ddr_config.c_reg.MSTR & DDRCTRL_MSTR_DDR3) != 0U)
  {
    pir |= DDRPHYC_PIR_DRAMRST; /* Only for DDR3 */
  }


  /* Treat self-refresh exit : hot boot */
  if (iddr->self_refresh)
  {
    /* DDR in self refresh mode, remove zcal & reset & init */
    pir &= ~(DDRPHYC_PIR_ZCAL & DDRPHYC_PIR_DRAMRST
             & DDRPHYC_PIR_DRAMINIT);
    pir |= DDRPHYC_PIR_ZCALBYP;
  }

  ret = HAL_DDR_PHY_Init(pir);
  if (ret != HAL_OK)
  {
    return ret;
  }

  if (iddr->self_refresh)
  {
    ret = self_refresh_zcal(iddr->zdata);
    if (ret != HAL_OK)
    {
      return ret;
    }
  }

  /*
   *  6. SET DFIMISC.dfi_init_complete_en to 1
   *  Enable quasi-dynamic register programming.
   */
  start_sw_done();

  SET_BIT(DDRCTRL->DFIMISC, DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN);

  ret = wait_sw_done_ack();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   *  7. Wait for DWC_ddr_umctl2 to move to normal operation mode
   *     by monitoring STAT.operating_mode signal
  */

  /* Wait uMCTL2 ready */

  /* Trigger self-refresh exit */
  if (iddr->self_refresh)
  {
    CLEAR_BIT(DDRCTRL->PWRCTL, DDRCTRL_PWRCTL_SELFREF_SW);
  }

  ret = wait_operating_mode(DDRCTRL_STAT_OPERATING_MODE_NORMAL);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* Switch to DLL OFF mode */
  if ((static_ddr_config.c_reg.MSTR & DDRCTRL_MSTR_DLL_OFF_MODE) != 0U)
  {
    ret = ddr3_dll_off();
    if (ret != HAL_OK)
    {
      return ret;
    }
  }


  /* DDR DQS training done */

  time = get_timer(0U);

  /*
   *  8. Disable Auto refresh and power down by setting
   *    - RFSHCTL3.dis_au_refresh = 1
   *    - PWRCTL.powerdown_en = 0
   *    - DFIMISC.dfiinit_complete_en = 0
   */
  ret = HAL_DDR_Refresh_Disable();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /*
   *  9. Program PUBL PGCR to enable refresh during training
   *     and rank to train
   *     not done => keep the programmed value in PGCR
   */

  /*
   * 10. configure PUBL PIR register to specify which training
   *     step to run
   *     RVTRN is executed only on LPDDR2/LPDDR3
   */
  pir = DDRPHYC_PIR_QSTRN;
  if ((static_ddr_config.c_reg.MSTR & DDRCTRL_MSTR_DDR3) == 0U)
  {
    pir |= DDRPHYC_PIR_RVTRN;
  }

  ret = HAL_DDR_PHY_Init(pir);
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* 11. monitor PUB PGSR.IDONE to poll cpmpletion of training
   *     sequence
   */
  ret = ddrphy_idone_wait();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* Refresh compensation: forcing refresh command */
  if (iddr->self_refresh)
  {
    ret = refresh_compensation(time);
    if (ret != HAL_OK)
    {
      return ret;
    }
  }

  /*
   * 12. set back registers in step 8 to the original values
   *     if desidered
   */
  ret = HAL_DDR_Refresh_Restore(static_ddr_config.c_reg.RFSHCTL3,
                                static_ddr_config.c_reg.PWRCTL);
  if (ret != HAL_OK)
  {
    return ret;
  }


  enable_axi_port();

  /* Enable axidcg clock gating */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_AXIDCGEN);

  /* check if DDR content is lost (self-refresh aborted) */
  if ((iddr->wakeup_from_standby) && !iddr->self_refresh)
  {
    iddr->clear_bkp = true;
  }

#ifndef DCACHE_OFF
  __set_SCTLR(__get_SCTLR() & ~SCTLR_C_BIT);
#endif /* DCACHE_OFF */

  if (iddr->self_refresh)
  {
    uret = ddr_test_rw_access();
    if (uret != 0U)
    {
      return HAL_ERROR;
    }

    /* Restore area overwritten by training */
    if (!restore_ddr_training_area())
    {
      return HAL_ERROR;
    }
  }
  else
  {
    uret = ddr_test_data_bus();
    if (uret != 0U)
    {
      return HAL_ERROR;
    }

    uret = ddr_test_addr_bus();
    if (uret != 0U)
    {
      return HAL_ERROR;
    }

    uret = ddr_check_size();
    if (uret < static_ddr_config.info.size)
    {
      return HAL_ERROR;
    }
  }

  /* Switch to Self-Refresh mode defined by the settings */
  if (HAL_DDR_SR_SetMode(ddr_sr_read_mode()) != HAL_OK)
  {
    /* Unable to switch to the predefined self-refresh mode */
    return HAL_ERROR;
  }

#ifndef DCACHE_OFF
  __set_SCTLR(__get_SCTLR() | SCTLR_C_BIT);
#endif /* DCACHE_OFF */

  return ret;
}

/**
  * @brief  Enable DDR Self-Refresh, in low power cases (when entering in CSTOP
  *         or before shutting down).
  * @param  zq0cr0_zdata IO calibration value.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DDR_SR_Entry(uint32_t *zq0cr0_zdata)
{
  /* Save IOs calibration values */
  if (zq0cr0_zdata != NULL)
  {
    *zq0cr0_zdata = READ_REG(DDRPHYC->ZQ0CR0) & DDRPHYC_ZQ0CR0_ZDATA_Msk;
  }

  /* Put DDR in Self-Refresh */
  if (ddr_sw_self_refresh_in() != 0)
  {
    return HAL_ERROR;
  }

  /* Enable I/O retention mode in standby */
  SET_BIT(PWR->CR3, PWR_CR3_DDRSREN);

  return HAL_OK;
}

/**
  * @brief  Remove DDR Self-Refresh on low power cases (when exiting from
  *         CSTOP).
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DDR_SR_Exit(void)
{
  HAL_StatusTypeDef ret;
  __IO uint32_t timeout;

  /* Enable all clocks */
  ddr_enable_clock();

  /*
   * manage quasi-dynamic registers modification
   * dfimisc.dfi_init_complete_en : Group 3
   */
  if (set_qd3_update_conditions() != 0)
  {
    return HAL_ERROR;
  }

  /* Mask dfi_init_complete_en */
  CLEAR_BIT(DDRCTRL->DFIMISC, DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN);

  ret = unset_qd3_update_conditions();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* Switch controller clocks (uMCTL2/PUBL) to DLL ref clock */
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_GSKPCTRL);

  /* Enable all DLLs: GLITCH window */
  CLEAR_BIT(DDRPHYC->ACDLLCR, DDRPHYC_ACDLLCR_DLLDIS);
  CLEAR_BIT(DDRPHYC->DX0DLLCR, DDRPHYC_DX0DLLCR_DLLDIS);
  CLEAR_BIT(DDRPHYC->DX1DLLCR, DDRPHYC_DX1DLLCR_DLLDIS);
#ifdef DDR_32BIT_INTERFACE
  CLEAR_BIT(DDRPHYC->DX2DLLCR, DDRPHYC_DX2DLLCR_DLLDIS);
  CLEAR_BIT(DDRPHYC->DX3DLLCR, DDRPHYC_DX3DLLCR_DLLDIS);
#endif /* DDR_32BIT_INTERFACE */

  /* Additional delay to avoid early DLL clock switch */
  ddr_delay_us(DDR_DELAY_10_US);

  /* Switch controller clocks (uMCTL2/PUBL) to DLL ref clock */
  CLEAR_BIT(RCC->DDRITFCR, RCC_DDRITFCR_GSKPCTRL);

  CLEAR_BIT(DDRPHYC->ACDLLCR, DDRPHYC_ACDLLCR_DLLSRST);

  ddr_delay_us(DDR_DELAY_10_US);

  SET_BIT(DDRPHYC->ACDLLCR, DDRPHYC_ACDLLCR_DLLSRST);

  /* PHY partial init: (DLL lock and ITM reset) */
  WRITE_REG(DDRPHYC->PIR, DDRPHYC_PIR_DLLSRST | DDRPHYC_PIR_DLLLOCK
                        | DDRPHYC_PIR_ITMSRST | DDRPHYC_PIR_INIT);

  /* Need to wait at least 10 clock cycles before accessing PGSR */
  ddr_delay_us(DDR_DELAY_1_US);

  /* Pool end of init */
  timeout = ddr_timeout_init_us(DDR_TIMEOUT_500_US);

  while ((READ_REG(DDRPHYC->PGSR) & DDRPHYC_PGSR_IDONE) == 0U)
  {
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT;
    }
  }

  /*
   * manage quasi-dynamic registers modification
   * dfimisc.dfi_init_complete_en : Group 3
   */
  if (set_qd3_update_conditions() != 0)
  {
    return HAL_ERROR;
  }

  /* Unmask dfi_init_complete_en to uMCTL2 */
  SET_BIT(DDRCTRL->DFIMISC, DDRCTRL_DFIMISC_DFI_INIT_COMPLETE_EN);

  ret = unset_qd3_update_conditions();
  if (ret != HAL_OK)
  {
    return ret;
  }

  /* Deactivate sw retention in PWR */
  CLEAR_BIT(PWR->CR3, PWR_CR3_DDRRETEN);

  /* Enable PZQ cell (PUBL register) */
  CLEAR_BIT(DDRPHYC->ZQ0CR0, DDRPHYC_ZQ0CR0_ZQPD);

  /* Enable pad drivers */
  CLEAR_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_ACPDD);

  /* Enable command/address output driver */
  SET_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_ACOE);
  CLEAR_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_CKPDD_Msk);
  CLEAR_BIT(DDRPHYC->ACIOCR, DDRPHYC_ACIOCR_CSPDD_Msk);
  CLEAR_BIT(DDRPHYC->DXCCR, DDRPHYC_DXCCR_DXPDD);
  CLEAR_BIT(DDRPHYC->DXCCR, DDRPHYC_DXCCR_DXPDR);

  /* Release latch */
  SET_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_CKOE);
  CLEAR_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_ODTPDD_Msk);
  CLEAR_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_NL2PD);
  CLEAR_BIT(DDRPHYC->DSGCR, DDRPHYC_DSGCR_CKEPDD_Msk);

  /* Remove selfrefresh */
  sw_selfref_exit();

  /* Wait operating_mode == normal */
  timeout = ddr_timeout_init_us(DDR_TIMEOUT_500_US);

  while ((READ_REG(DDRCTRL->STAT) & DDRCTRL_STAT_OPERATING_MODE_Msk)
         != DDRCTRL_STAT_OPERATING_MODE_NORMAL)
  {
    timeout--;
    if (ddr_timeout_elapsed(timeout))
    {
      return HAL_TIMEOUT;
    }
  }

  /* AXI ports are no longer blocked from taking transactions */
  enable_axi_port();
  SET_BIT(RCC->DDRITFCR, RCC_DDRITFCR_AXIDCGEN);

  return ret;
}

/**
  * @brief  Activate either HW, or SW or automatic self-refresh, in low power
  *         cases (when entering in or exiting from CSTOP).
  * @param  mode Self-refresh mode.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DDR_SR_SetMode(HAL_DDR_SelfRefreshModeTypeDef mode)
{
  HAL_StatusTypeDef ret;

  switch (mode)
  {
    case HAL_DDR_SW_SELF_REFRESH_MODE:
      ret = ddr_sr_mode_ssr();
      break;
    case HAL_DDR_AUTO_SELF_REFRESH_MODE:
      ret = ddr_sr_mode_asr();
      break;
    case HAL_DDR_HW_SELF_REFRESH_MODE:
      ret = ddr_sr_mode_hsr();
      break;
    default:
      ret = HAL_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Read current self-refresh mode, in low power
  *         cases (when entering in or exiting from CSTOP).
  * @retval Self-refresh mode.
  */
HAL_DDR_SelfRefreshModeTypeDef HAL_DDR_SR_ReadMode(void)
{
  return ddr_sr_read_mode();
}

/**
  * @}
  */
#endif /* DDRCTRL & DDRPHYC */
#endif /* HAL_DDR_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
