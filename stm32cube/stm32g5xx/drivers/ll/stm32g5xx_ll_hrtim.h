/**
  ******************************************************************************
  * @file    stm32g5xx_ll_hrtim.h
  * @brief   Header file of HRTIM LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G5XX_LL_HRTIM_H
#define STM32G5XX_LL_HRTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx.h"

/** @addtogroup STM32G5xx_LL_Driver
  * @{
  */
#if defined (HRTIM1)

/** @defgroup HRTIM_LL HRTIM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup HRTIM_LL_Private_Variables HRTIM Private Variables
  * @{
  */
static const uint16_t LL_HRTIM_REG_OFFSET_TAB_TIMER[] =
{
  0x00U,   /* 0: MASTER  */
  0x100U,  /* 1: TIMER A */
  0x200U,  /* 2: TIMER B */
  0x300U,  /* 3: TIMER C */
  0x400U,  /* 4: TIMER D */
  0x500U,  /* 5: TIMER E */
  0x600U,  /* 6: TIMER F */
};

static const uint8_t LL_HRTIM_REG_OFFSET_TAB_ADCxR[] =
{
  0x00U,    /* LL_HRTIM_ADCTRIG1: HRTIM_ADC1R */
  0x04U,    /* LL_HRTIM_ADCTRIG2: HRTIM_ADC2R */
  0x08U,    /* LL_HRTIM_ADCTRIG3: HRTIM_ADC3R */
  0x0CU,    /* LL_HRTIM_ADCTRIG4: HRTIM_ADC4R */
  0x3CU,    /* LL_HRTIM_ADCTRIG5:  HRTIM_ADCER */
  0x3CU,    /* LL_HRTIM_ADCTRIG6:  HRTIM_ADCER */
  0x3CU,    /* LL_HRTIM_ADCTRIG7:  HRTIM_ADCER */
  0x3CU,    /* LL_HRTIM_ADCTRIG8:  HRTIM_ADCER */
  0x3CU,    /* LL_HRTIM_ADCTRIG9:  HRTIM_ADCER */
  0x3CU,    /* LL_HRTIM_ADCTRIG10: HRTIM_ADCER */
};

static const uint8_t LL_HRTIM_REG_OFFSET_TAB_ADCUR[] =
{
  0x00U,    /* LL_HRTIM_ADCTRIG1:  HRTIM_CR1   */
  0x00U,    /* LL_HRTIM_ADCTRIG2:  HRTIM_CR1   */
  0x00U,    /* LL_HRTIM_ADCTRIG3:  HRTIM_CR1   */
  0x00U,    /* LL_HRTIM_ADCTRIG4:  HRTIM_CR1   */
  0x7CU,    /* LL_HRTIM_ADCTRIG5:  HRTIM_ADCUR */
  0x7CU,    /* LL_HRTIM_ADCTRIG6:  HRTIM_ADCUR */
  0x7CU,    /* LL_HRTIM_ADCTRIG7:  HRTIM_ADCUR */
  0x7CU,    /* LL_HRTIM_ADCTRIG8:  HRTIM_ADCUR */
  0x7CU,    /* LL_HRTIM_ADCTRIG9:  HRTIM_ADCUR */
  0x7CU,    /* LL_HRTIM_ADCTRIG10: HRTIM_ADCUR */
};

static const uint8_t LL_HRTIM_REG_OFFSET_TAB_CMPxR[] =
{
  0x00U,    /* LL_HRTIM_COMPARE_UNIT_1: HRTIM_CMP1xR */
  0x08U,    /* LL_HRTIM_COMPARE_UNIT_2: HRTIM_CMP2xR */
  0x0CU,    /* LL_HRTIM_COMPARE_UNIT_3: HRTIM_CMP3xR */
  0x10U,    /* LL_HRTIM_COMPARE_UNIT_4: HRTIM_CMP4xR */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_ADCER[] =
{
  0,   /* LL_HRTIM_ADCTRIG1  */
  0,   /* LL_HRTIM_ADCTRIG2  */
  0,   /* LL_HRTIM_ADCTRIG3  */
  0,   /* LL_HRTIM_ADCTRIG4  */
  0,   /* LL_HRTIM_ADCTRIG5  */
  5,   /* LL_HRTIM_ADCTRIG6  */
  10,  /* LL_HRTIM_ADCTRIG7  */
  16,  /* LL_HRTIM_ADCTRIG8  */
  21,  /* LL_HRTIM_ADCTRIG9  */
  26,  /* LL_HRTIM_ADCTRIG10 */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_ADCUR[] =
{
  16,   /* LL_HRTIM_ADCTRIG1  */
  19,   /* LL_HRTIM_ADCTRIG2  */
  22,   /* LL_HRTIM_ADCTRIG3  */
  25,   /* LL_HRTIM_ADCTRIG4  */
  0,    /* LL_HRTIM_ADCTRIG5  */
  4,    /* LL_HRTIM_ADCTRIG6  */
  8,    /* LL_HRTIM_ADCTRIG7  */
  12,   /* LL_HRTIM_ADCTRIG8  */
  16,   /* LL_HRTIM_ADCTRIG9  */
  20,   /* LL_HRTIM_ADCTRIG10 */
};

static const uint32_t LL_HRTIM_REG_MASK_TAB_ADCER[] =
{
  0xFFFFFFFFU,   /* LL_HRTIM_ADCTRIG1  */
  0xFFFFFFFFU,   /* LL_HRTIM_ADCTRIG2  */
  0xFFFFFFFFU,   /* LL_HRTIM_ADCTRIG3  */
  0xFFFFFFFFU,   /* LL_HRTIM_ADCTRIG4  */
  0x0000001FU,   /* LL_HRTIM_ADCTRIG5  */
  0x000003E0U,   /* LL_HRTIM_ADCTRIG6  */
  0x00007C00U,   /* LL_HRTIM_ADCTRIG7  */
  0x001F0000U,   /* LL_HRTIM_ADCTRIG8  */
  0x03E00000U,   /* LL_HRTIM_ADCTRIG9  */
  0x7C000000U,   /* LL_HRTIM_ADCTRIG10 */
};

static const uint32_t LL_HRTIM_REG_MASK_TAB_ADCUR[] =
{
  0x00070000U,   /* LL_HRTIM_ADCTRIG1  */
  0x00380000U,   /* LL_HRTIM_ADCTRIG2  */
  0x01C00000U,   /* LL_HRTIM_ADCTRIG3  */
  0x0E000000U,   /* LL_HRTIM_ADCTRIG4  */
  0x00000007U,   /* LL_HRTIM_ADCTRIG5  */
  0x00000070U,   /* LL_HRTIM_ADCTRIG6  */
  0x00000700U,   /* LL_HRTIM_ADCTRIG7  */
  0x00007000U,   /* LL_HRTIM_ADCTRIG8  */
  0x00070000U,   /* LL_HRTIM_ADCTRIG9  */
  0x00700000U,   /* LL_HRTIM_ADCTRIG10 */
};

static const uint8_t REG_OFFSET_TAB_ADCPSx[] =
{
  0U,    /* 0: HRTIM_ADC1R  */
  6U,    /* 1: HRTIM_ADC2R  */
  12U,   /* 2: HRTIM_ADC3R  */
  18U,   /* 3: HRTIM_ADC4R  */
  24U,   /* 4: HRTIM_ADC5R  */
  32U,   /* 5: HRTIM_ADC6R  */
  38U,   /* 6: HRTIM_ADC7R  */
  44U,   /* 7: HRTIM_ADC8R  */
  50U,   /* 8: HRTIM_ADC9R  */
  56U,   /* 9: HRTIM_ADC10R */
};

static const uint16_t LL_HRTIM_REG_OFFSET_TAB_SETxR[] =
{
  0x00U,   /* 0: TA1 */
  0x08U,   /* 1: TA2 */
  0x100U,  /* 2: TB1 */
  0x108U,  /* 3: TB2 */
  0x200U,  /* 4: TC1 */
  0x208U,  /* 5: TC2 */
  0x300U,  /* 6: TD1 */
  0x308U,  /* 7: TD2 */
  0x400U,  /* 8: TE1 */
  0x408U,  /* 9: TE2 */
  0x500U,  /* 10: TF1 */
  0x508U,  /* 11: TF2 */
};

static const uint16_t LL_HRTIM_REG_OFFSET_TAB_OUTxR[] =
{
  0x00U,   /*  0: TA1 */
  0x00U,   /*  1: TA2 */
  0x100U,  /*  2: TB1 */
  0x100U,  /*  3: TB2 */
  0x200U,  /*  4: TC1 */
  0x200U,  /*  5: TC2 */
  0x300U,  /*  6: TD1 */
  0x300U,  /*  7: TD2 */
  0x400U,  /*  8: TE1 */
  0x400U,  /*  9: TE2 */
  0x500U,  /* 10: TF1 */
  0x500U,  /* 11: TF2 */
};

static const uint8_t LL_HRTIM_REG_OFFSET_TAB_EECR[] =
{
  0x00U, /* LL_HRTIM_EEV1 */
  0x00U, /* LL_HRTIM_EEV2 */
  0x00U, /* LL_HRTIM_EEV3 */
  0x00U, /* LL_HRTIM_EEV4 */
  0x00U, /* LL_HRTIM_EEV5 */
  0x04U, /* LL_HRTIM_EEV6 */
  0x04U, /* LL_HRTIM_EEV7 */
  0x04U, /* LL_HRTIM_EEV8 */
  0x04U, /* LL_HRTIM_EEV9 */
  0x04U, /* LL_HRTIM_EEV10 */
  0x70U, /* LL_HRTIM_EEV11 */
  0x70U, /* LL_HRTIM_EEV12 */
  0x70U, /* LL_HRTIM_EEV13 */
  0x74U, /* LL_HRTIM_EEV14 */
  0x74U, /* LL_HRTIM_EEV15 */
  0x74U, /* LL_HRTIM_EEV16 */
};

static const uint8_t LL_HRTIM_REG_OFFSET_TAB_FLTINR[] =
{
  0x00U, /* LL_HRTIM_FLT1 */
  0x00U, /* LL_HRTIM_FLT2 */
  0x00U, /* LL_HRTIM_FLT3 */
  0x00U, /* LL_HRTIM_FLT4 */
  0x04U, /* LL_HRTIM_FLT5 */
  0x04U, /* LL_HRTIM_FLT6 */
  0x40U, /* LL_HRTIM_FLT7 */
  0x40U, /* LL_HRTIM_FLT8 */
};

static const uint32_t LL_HRTIM_REG_MASK_TAB_UPDATETRIG[] =
{
  0x20000000U,  /* 0: MASTER  */
  0x01FF0000U,  /* 1: TIMER A */
  0x01FF0000U,  /* 2: TIMER B */
  0x01FF0000U,  /* 3: TIMER C */
  0x01FF0000U,  /* 4: TIMER D */
  0x01FF0000U,  /* 5: TIMER E */
  0x01FF0000U,  /* 5: TIMER E */
  0x01FF0000U,  /* 6: TIMER F */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_UPDATETRIG[] =
{
  12U, /* 0: MASTER  */
  0U,  /* 1: TIMER A */
  0U,  /* 2: TIMER B  */
  0U,  /* 3: TIMER C */
  0U,  /* 4: TIMER D  */
  0U,  /* 5: TIMER E */
  0U,  /* 6: TIMER F */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_EExSRC[] =
{
  0U,  /* LL_HRTIM_EEV1  */
  6U,  /* LL_HRTIM_EEV2  */
  12U, /* LL_HRTIM_EEV3  */
  18U, /* LL_HRTIM_EEV4  */
  24U, /* LL_HRTIM_EEV5  */
  0U,  /* LL_HRTIM_EEV6  */
  6U,  /* LL_HRTIM_EEV7  */
  12U, /* LL_HRTIM_EEV8  */
  18U, /* LL_HRTIM_EEV9  */
  24U, /* LL_HRTIM_EEV10 */
  0U,  /* LL_HRTIM_EEV11 */
  6U,  /* LL_HRTIM_EEV12 */
  12U, /* LL_HRTIM_EEV13 */
  0U,  /* LL_HRTIM_EEV14 */
  6U,  /* LL_HRTIM_EEV15 */
  12U, /* LL_HRTIM_EEV16 */
};

static const uint32_t REG_MASK_TAB_UPDATEGAT[] =
{
  HRTIM_MCR_BRSTDMA,    /* 0: MASTER  */
  HRTIM_TIMxCR_UPDGAT,  /* 1: TIMER A */
  HRTIM_TIMxCR_UPDGAT,  /* 2: TIMER B */
  HRTIM_TIMxCR_UPDGAT,  /* 3: TIMER C */
  HRTIM_TIMxCR_UPDGAT,  /* 4: TIMER D */
  HRTIM_TIMxCR_UPDGAT,  /* 5: TIMER E */
  HRTIM_TIMxCR_UPDGAT,  /* 6: TIMER F */
};

static const uint8_t REG_SHIFT_TAB_UPDATEGAT[] =
{
  2U, /* 0: MASTER  */
  0U, /* 1: TIMER A */
  0U, /* 2: TIMER B */
  0U, /* 3: TIMER C */
  0U, /* 4: TIMER D */
  0U, /* 5: TIMER E */
  0U, /* 6: TIMER F */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_OUTxR[] =
{
  0U,  /* 0: TA1 */
  16U, /* 1: TA2 */
  0U,  /* 2: TB1 */
  16U, /* 3: TB2 */
  0U,  /* 4: TC1 */
  16U, /* 5: TC2 */
  0U,  /* 6: TD1 */
  16U, /* 7: TD2 */
  0U,  /* 8: TE1 */
  16U, /* 9: TE2 */
  0U,  /* 10: TF1 */
  16U, /* 11: TF2 */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_OxSTAT[] =
{
  0U,  /* 0: TA1 */
  1U,  /* 1: TA2 */
  0U,  /* 2: TB1 */
  1U,  /* 3: TB2 */
  0U,  /* 4: TC1 */
  1U,  /* 5: TC2 */
  0U,  /* 6: TD1 */
  1U,  /* 7: TD2 */
  0U,  /* 8: TE1 */
  1U,  /* 9: TE2 */
  0U,  /* 10: TF1 */
  1U,  /* 11: TF2 */
};

static const uint8_t LL_REG_SHIFT_TAB_FLTxE[] =
{
  0U,   /* LL_HRTIM_FLT1 */
  8U,   /* LL_HRTIM_FLT2 */
  16U,  /* LL_HRTIM_FLT3 */
  24U,  /* LL_HRTIM_FLT4 */
  0U,   /* LL_HRTIM_FLT5 */
  8U,   /* LL_HRTIM_FLT6 */
  0U,   /* LL_HRTIM_FLT7 */
  8U,   /* LL_HRTIM_FLT8 */
};

static const uint8_t LL_REG_SHIFT_TAB_FLTxF[] =
{
  0U,   /* LL_HRTIM_FLT1 */
  8U,   /* LL_HRTIM_FLT2 */
  16U,  /* LL_HRTIM_FLT3 */
  24U,  /* LL_HRTIM_FLT4 */
  32U,  /* LL_HRTIM_FLT5 */
  40U,  /* LL_HRTIM_FLT6 */
  0U,   /* LL_HRTIM_FLT7 */
  8U,   /* LL_HRTIM_FLT8 */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_FLTxCNT[] =
{
  2U,   /* LL_HRTIM_FLT1 */
  10U,  /* LL_HRTIM_FLT2 */
  18U,  /* LL_HRTIM_FLT3 */
  26U,  /* LL_HRTIM_FLT4 */
  2U,   /* LL_HRTIM_FLT5 */
  10U,  /* LL_HRTIM_FLT6 */
  18U,  /* LL_HRTIM_FLT7 */
  26U,  /* LL_HRTIM_FLT8 */
};

static const uint8_t REG_SHIFT_TAB_FLTxBLKE[] =
{
  0U,   /* LL_HRTIM_FLT1 */
  8U,   /* LL_HRTIM_FLT2 */
  16U,  /* LL_HRTIM_FLT3 */
  24U,  /* LL_HRTIM_FLT4 */
  0U,   /* LL_HRTIM_FLT5 */
  8U,   /* LL_HRTIM_FLT6 */
  16U,  /* LL_HRTIM_FLT7 */
  24U,  /* LL_HRTIM_FLT8 */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_INTLVD[] =
{
  0U,  /* 0: MASTER  */
  1U,  /* 1: TIMER A */
  1U,  /* 2: TIMER B */
  1U,  /* 3: TIMER C */
  1U,  /* 4: TIMER D */
  1U,  /* 5: TIMER E */
  1U,  /* 6: TIMER F */
};

static const uint32_t LL_HRTIM_REG_MASK_TAB_INTLVD[] =
{
  0x000000E0U,  /* 0: MASTER  */
  0x000001A0U,  /* 1: TIMER A */
  0x000001A0U,  /* 2: TIMER B */
  0x000001A0U,  /* 3: TIMER C */
  0x000001A0U,  /* 4: TIMER D */
  0x000001A0U,  /* 5: TIMER E */
  0x000001A0U,  /* 6: TIMER F */
};

static const uint8_t LL_HRTIM_REG_SHIFT_TAB_CPT[] =
{
  12U,  /* 1: TIMER A */
  16U,  /* 2: TIMER B */
  20U,  /* 3: TIMER C */
  24U,  /* 4: TIMER D */
  28U,  /* 5: TIMER E */
  0U,   /* 6: TIMER F */
};

static const uint32_t LL_HRTIM_REG_MASK_TAB_CPT[] =
{
  0xFFFF0000U,  /* 1: TIMER A */
  0xFFF0F000U,  /* 2: TIMER B */
  0xFF0FF000U,  /* 3: TIMER C */
  0xF0FFF000U,  /* 4: TIMER D */
  0x0FFFF000U,  /* 5: TIMER E */
  0xFFFFF000U,  /* 6: TIMER F */
};

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/** @defgroup HRTIM_LL_Private_Constants HRTIM Private Constants
  * @{
  */

/**
  * @brief Bit masks used to address multiple bit-fields.
  * @{
  */
#define LL_HRTIM_CR1_UDIS_MASK   ((uint32_t)(HRTIM_CR1_MUDIS  |\
                                             HRTIM_CR1_TAUDIS |\
                                             HRTIM_CR1_TBUDIS |\
                                             HRTIM_CR1_TCUDIS |\
                                             HRTIM_CR1_TDUDIS |\
                                             HRTIM_CR1_TEUDIS |\
                                             HRTIM_CR1_TFUDIS))

#define LL_HRTIM_CR2_SWUPD_MASK   ((uint32_t)(HRTIM_CR2_MSWU |\
                                              HRTIM_CR2_TASWU |\
                                              HRTIM_CR2_TBSWU |\
                                              HRTIM_CR2_TCSWU |\
                                              HRTIM_CR2_TDSWU |\
                                              HRTIM_CR2_TESWU |\
                                              HRTIM_CR2_TFSWU))

#define LL_HRTIM_CR2_SWAP_MASK   ((uint32_t)(HRTIM_CR2_SWPA |\
                                             HRTIM_CR2_SWPB |\
                                             HRTIM_CR2_SWPC |\
                                             HRTIM_CR2_SWPD |\
                                             HRTIM_CR2_SWPE |\
                                             HRTIM_CR2_SWPF))

#define LL_HRTIM_CR2_SWRST_MASK   ((uint32_t)(HRTIM_CR2_MRST |\
                                              HRTIM_CR2_TARST |\
                                              HRTIM_CR2_TBRST |\
                                              HRTIM_CR2_TCRST |\
                                              HRTIM_CR2_TDRST |\
                                              HRTIM_CR2_TERST |\
                                              HRTIM_CR2_TFRST))

#define LL_HRTIM_OENR_OEN_MASK   ((uint32_t)(HRTIM_OENR_TA1OEN |\
                                             HRTIM_OENR_TA2OEN |\
                                             HRTIM_OENR_TB1OEN |\
                                             HRTIM_OENR_TB2OEN |\
                                             HRTIM_OENR_TC1OEN |\
                                             HRTIM_OENR_TC2OEN |\
                                             HRTIM_OENR_TD1OEN |\
                                             HRTIM_OENR_TD2OEN |\
                                             HRTIM_OENR_TE1OEN |\
                                             HRTIM_OENR_TE2OEN |\
                                             HRTIM_OENR_TF1OEN |\
                                             HRTIM_OENR_TF2OEN))

#define LL_HRTIM_OENR_ODIS_MASK  ((uint32_t)(HRTIM_ODISR_TA1ODIS  |\
                                             HRTIM_ODISR_TA2ODIS  |\
                                             HRTIM_ODISR_TB1ODIS  |\
                                             HRTIM_ODISR_TB2ODIS  |\
                                             HRTIM_ODISR_TC1ODIS  |\
                                             HRTIM_ODISR_TC2ODIS  |\
                                             HRTIM_ODISR_TD1ODIS  |\
                                             HRTIM_ODISR_TD2ODIS  |\
                                             HRTIM_ODISR_TE1ODIS  |\
                                             HRTIM_ODISR_TE2ODIS  |\
                                             HRTIM_ODISR_TF1ODIS  |\
                                             HRTIM_ODISR_TF2ODIS))

#define LL_HRTIM_OUT_CONFIG_MASK  ((uint32_t)(HRTIM_OUTxR_POL1   |\
                                              HRTIM_OUTxR_IDLEM1  |\
                                              HRTIM_OUTxR_IDLES1 |\
                                              HRTIM_OUTxR_FAULT1 |\
                                              HRTIM_OUTxR_CHP1   |\
                                              HRTIM_OUTxR_DIDL1))

#define LL_HRTIM_EE_CONFIG_MASK   ((uint32_t)(HRTIM_EECR1_EE1SRC |\
                                              HRTIM_EECR1_EE1POL |\
                                              HRTIM_EECR1_EE1SNS |\
                                              HRTIM_EECR1_EE1FAST))

#define LL_HRTIM_FLT_CONFIG_MASK   ((uint32_t)(HRTIM_FLTINR1_FLT1P |\
                                               HRTIM_FLTINR1_FLT1SRC ))

#define LL_HRTIM_FLT_SRC_1_MASK   ((uint32_t)(HRTIM_FLTINR2_FLT1SRC |\
                                              HRTIM_FLTINR2_FLT2SRC |\
                                              HRTIM_FLTINR2_FLT3SRC |\
                                              HRTIM_FLTINR2_FLT4SRC |\
                                              HRTIM_FLTINR2_FLT5SRC_1 |\
                                              HRTIM_FLTINR2_FLT6SRC_1 |\
                                              HRTIM_FLTINR2_FLT7SRC_1 |\
                                              HRTIM_FLTINR2_FLT8SRC_1))

#define LL_HRTIM_BM_CONFIG_MASK   ((uint32_t)( HRTIM_BMCR_BMPRSC |\
                                               HRTIM_BMCR_BMCLK  |\
                                               HRTIM_BMCR_BMOM))

#define LL_HRTIM_COFEXR_EEVFRC_MASK   ((uint32_t)(HRTIM_COFExR_EEVAFRCA |\
                                                  HRTIM_COFExR_EEVBFRCA |\
                                                  HRTIM_COFExR_EEVCFRCA |\
                                                  HRTIM_COFExR_EEVDFRCA |\
                                                  HRTIM_COFExR_EEVEFRCA |\
                                                  HRTIM_COFExR_EEVFFRCA |\
                                                  HRTIM_COFExR_EEVGFRCA |\
                                                  HRTIM_COFExR_EEVHFRCA |\
                                                  HRTIM_COFExR_EEVIFRCA |\
                                                  HRTIM_COFExR_EEVJFRCA))
/**
  * @}
  */

/**
  * @brief Remap of the Timer F related capture trigger bit-fields.
  * @{
  */
#define HRTIM_CPT1XCR_TF1SET_REMAP 0x1UL    /*!< TF1SET: 0x00000001 */
#define HRTIM_CPT1XCR_TF1RST_REMAP 0x2UL    /*!< TF1RST: 0x00000002 */
#define HRTIM_CPT1XCR_TFCMP1_REMAP 0x4UL    /*!< TF1RST: 0x00000004 */
#define HRTIM_CPT1XCR_TFCMP2_REMAP 0x8UL    /*!< TF1RST: 0x00000008 */
/**
  * @}
  */

/**
  * @brief Event source selection extra bit definition (EExSRC[2]).
  * @note   The event configuration mask is constructed as follows:
  *           Bits 1:0 EExSRC[1:0] : External event x source
  *           Bit 2 EExPOL         : External event x polarity
  *           Bits 4:3 EExSNS[1:0] : External event x sensitivity
  *           Bit 5 EExFAST        : External event x fast mode
  *           Bit 6 EExSRC[2]      : External event x source (combined with EExSRC[1:0])
  * @{
  */
#define HRTIM_EEV_SRC_2_POS              (6U)
#define HRTIM_EEV_SRC_2_MASK             (0x1UL << HRTIM_EEV_SRC_2_POS)
#define HRTIM_EEV_SRC_2                  HRTIM_EEV_SRC_2_MASK
/**
  * @}
  */

/**
  * @brief Bit-fields making up external events mapping and associated features related constants.
  * @{
  */
#define LL_HRTIM_EEV_ID_POS          (0U)                                  /*!< Bit position: 0 */
#define LL_HRTIM_EEV_ID_MSK          (0xFFFFUL << LL_HRTIM_EEV_ID_POS)     /*!< 0x0000FFFF */
#define LL_HRTIM_EEV_ID              LL_HRTIM_EEV_ID_MSK                   /*!< External event identifier */
#define LL_HRTIM_EEV_SRC_POS         (16U)                                 /*!< Bit position: 16 */
#define LL_HRTIM_EEV_SRC_MSK         (0x43UL << LL_HRTIM_EEV_SRC_POS)      /*!< 0x00430000 */
#define LL_HRTIM_EEV_SRC             LL_HRTIM_EEV_SRC_MSK                  /*!< External event source */
#define LL_HRTIM_EEV_SRC_0           (0x1UL << LL_HRTIM_EEV_SRC_POS)       /*!< 0x00010000 */
#define LL_HRTIM_EEV_SRC_1           (0x2UL << LL_HRTIM_EEV_SRC_POS)       /*!< 0x00020000 */
#define LL_HRTIM_EEV_SRC_2           (0x40UL << LL_HRTIM_EEV_SRC_POS)      /*!< 0x00400000 */
#define LL_HRTIM_EEV_FAST_MODE_POS   (30U)                                 /*!< Bit position: 30 */
#define LL_HRTIM_EEV_FAST_MODE_MSK   (0x1UL << LL_HRTIM_EEV_FAST_MODE_POS) /*!< 0x40000000 */
#define LL_HRTIM_EEV_FAST_MODE       LL_HRTIM_EEV_FAST_MODE_MSK            /*!< Fast mode support */
#define LL_HRTIM_EEV_FILTER_POS      (31U)                                 /*!< Bit position: 31 */
#define LL_HRTIM_EEV_FILTER_MSK      (0x1UL << LL_HRTIM_EEV_FILTER_POS)    /*!< 0x80000000 */
#define LL_HRTIM_EEV_FILTER          LL_HRTIM_EEV_FILTER_MSK               /*!< Filtering support */
/**
  * @}
  */

/**
  * @brief Bit-fields making up fault input source related constants.
  * @{
  */
#define LL_HRTIM_FLT_ID_POS          (0U)                                  /*!< Bit position: 0 */
#define LL_HRTIM_FLT_ID_MSK          (0xFFFFUL << LL_HRTIM_FLT_ID_POS)     /*!< 0x0000FFFF */
#define LL_HRTIM_FLT_ID              LL_HRTIM_FLT_ID_MSK                   /*!< Fault identifier */
#define LL_HRTIM_FLT_SRC_POS         (8U)                                  /*!< Bit position: 8 */
#define LL_HRTIM_FLT_SRC_MSK         (0x10004UL << LL_HRTIM_FLT_SRC_POS)   /*!< 0x01000400 */
#define LL_HRTIM_FLT_SRC             LL_HRTIM_FLT_SRC_MSK                  /*!< Fault source */
#define LL_HRTIM_FLT_SRC_0           (0x4UL << LL_HRTIM_FLT_SRC_POS)       /*!< 0x00000400 */
#define LL_HRTIM_FLT_SRC_1           (0x10000UL << LL_HRTIM_FLT_SRC_POS)   /*!< 0x01000000 */
/**
  * @}
  */

/**
  * @brief Bit-fields making up fault blanking related constants.
  * @{
  */
#define LL_HRTIM_FLTBLK_ID_POS       (0U)                                  /*!< Bit position: 0 */
#define LL_HRTIM_FLTBLK_ID_MSK       (0xFFFFUL << LL_HRTIM_FLTBLK_ID_POS)  /*!< 0x0000FFFF */
#define LL_HRTIM_FLTBLK_ID           LL_HRTIM_FLTBLK_ID_MSK                /*!< Fault blanking mode */
#define LL_HRTIM_FLTBLK_SEL_POS      (16U)                                 /*!< Bit position: 16 */
#define LL_HRTIM_FLTBLK_SEL_MSK      (0x1UL << LL_HRTIM_FLTBLK_SEL_POS)    /*!< 0x00010000 */
#define LL_HRTIM_FLTBLK_SEL          LL_HRTIM_FLTBLK_SEL_MSK               /*!< Fault blanking source */
/**
  * @}
  */

/**
  * @}
  */


/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup HRTIM_LL_Exported_Constants LL HRTIM Constants
  * @{
  */

/** @defgroup HRTIM_LL_EC_GET_FLAG HRTIM interrupt flags
  * @brief    Flags defines which can be used with LL_HRTIM_ReadReg function.
  * @{
  */
#define LL_HRTIM_ISR_FLT1                  HRTIM_ISR_FLT1
#define LL_HRTIM_ISR_FLT2                  HRTIM_ISR_FLT2
#define LL_HRTIM_ISR_FLT3                  HRTIM_ISR_FLT3
#define LL_HRTIM_ISR_FLT4                  HRTIM_ISR_FLT4
#define LL_HRTIM_ISR_FLT5                  HRTIM_ISR_FLT5
#define LL_HRTIM_ISR_FLT6                  HRTIM_ISR_FLT6
#define LL_HRTIM_ISR_FLT7                  HRTIM_ISR_FLT7
#define LL_HRTIM_ISR_FLT8                  HRTIM_ISR_FLT8
#define LL_HRTIM_ISR_SYSFLT                HRTIM_ISR_SYSFLT
#define LL_HRTIM_ISR_DLLRDY                HRTIM_ISR_DLLRDY
#define LL_HRTIM_ISR_BMPER                 HRTIM_ISR_BMPER

#define LL_HRTIM_MISR_MCMP1                HRTIM_MISR_MCMP1
#define LL_HRTIM_MISR_MCMP2                HRTIM_MISR_MCMP2
#define LL_HRTIM_MISR_MCMP3                HRTIM_MISR_MCMP3
#define LL_HRTIM_MISR_MCMP4                HRTIM_MISR_MCMP4
#define LL_HRTIM_MISR_MREP                 HRTIM_MISR_MREP
#define LL_HRTIM_MISR_SYNC                 HRTIM_MISR_SYNC
#define LL_HRTIM_MISR_MUPD                 HRTIM_MISR_MUPD

#define LL_HRTIM_TIMISR_CMP1               HRTIM_TIMxISR_CMP1
#define LL_HRTIM_TIMISR_CMP2               HRTIM_TIMxISR_CMP2
#define LL_HRTIM_TIMISR_CMP3               HRTIM_TIMxISR_CMP3
#define LL_HRTIM_TIMISR_CMP4               HRTIM_TIMxISR_CMP4
#define LL_HRTIM_TIMISR_REP                HRTIM_TIMxISR_REP
#define LL_HRTIM_TIMISR_UPD                HRTIM_TIMxISR_UPD
#define LL_HRTIM_TIMISR_CPT1               HRTIM_TIMxISR_CPT1
#define LL_HRTIM_TIMISR_CPT2               HRTIM_TIMxISR_CPT2
#define LL_HRTIM_TIMISR_SETA1              HRTIM_TIMxISR_SET1
#define LL_HRTIM_TIMISR_RSTA1              HRTIM_TIMxISR_RST1
#define LL_HRTIM_TIMISR_SETA2              HRTIM_TIMxISR_SET2
#define LL_HRTIM_TIMISR_RSTA2              HRTIM_TIMxISR_RST2
#define LL_HRTIM_TIMISR_RST                HRTIM_TIMxISR_RST
#define LL_HRTIM_TIMISR_DLYPRT             HRTIM_TIMxISR_DLYPRT
#define LL_HRTIM_TIMISR_COT                HRTIM_TIMxISR_COT
#define LL_HRTIM_TIMISR_CORDE              HRTIM_TIMxISR_CORDE
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_IT IT HRTIM interrupts enable
  * @brief    IT defines which can be used with LL_HRTIM_ReadReg and LL_HRTIM_WriteReg functions.
  * @{
  */
#define LL_HRTIM_IER_FLT1IE                HRTIM_IER_FLT1IE
#define LL_HRTIM_IER_FLT2IE                HRTIM_IER_FLT2IE
#define LL_HRTIM_IER_FLT3IE                HRTIM_IER_FLT3IE
#define LL_HRTIM_IER_FLT4IE                HRTIM_IER_FLT4IE
#define LL_HRTIM_IER_FLT5IE                HRTIM_IER_FLT5IE
#define LL_HRTIM_IER_FLT6IE                HRTIM_IER_FLT6IE
#define LL_HRTIM_IER_FLT7IE                HRTIM_IER_FLT7IE
#define LL_HRTIM_IER_FLT8IE                HRTIM_IER_FLT8IE
#define LL_HRTIM_IER_SYSFLTIE              HRTIM_IER_SYSFLTIE
#define LL_HRTIM_IER_DLLRDYIE              HRTIM_IER_DLLRDYIE
#define LL_HRTIM_IER_BMPERIE               HRTIM_IER_BMPERIE

#define LL_HRTIM_IER_ALL_IT                (HRTIM_IER_FLT1IE     \
                                            | HRTIM_IER_FLT2IE   \
                                            | HRTIM_IER_FLT3IE   \
                                            | HRTIM_IER_FLT4IE   \
                                            | HRTIM_IER_FLT5IE   \
                                            | HRTIM_IER_FLT6IE   \
                                            | HRTIM_IER_FLT7IE   \
                                            | HRTIM_IER_FLT8IE   \
                                            | HRTIM_IER_SYSFLTIE \
                                            | HRTIM_IER_BMPERIE)

#define LL_HRTIM_MDIER_MCMP1IE             HRTIM_MDIER_MCMP1IE
#define LL_HRTIM_MDIER_MCMP2IE             HRTIM_MDIER_MCMP2IE
#define LL_HRTIM_MDIER_MCMP3IE             HRTIM_MDIER_MCMP3IE
#define LL_HRTIM_MDIER_MCMP4IE             HRTIM_MDIER_MCMP4IE
#define LL_HRTIM_MDIER_MREPIE              HRTIM_MDIER_MREPIE
#define LL_HRTIM_MDIER_SYNCIE              HRTIM_MDIER_SYNCIE
#define LL_HRTIM_MDIER_MUPDIE              HRTIM_MDIER_MUPDIE

#define LL_HRTIM_MDIER_ALL_IT              (HRTIM_MDIER_MCMP1IE   \
                                            | HRTIM_MDIER_MCMP2IE \
                                            | HRTIM_MDIER_MCMP3IE \
                                            | HRTIM_MDIER_MCMP4IE \
                                            | HRTIM_MDIER_MREPIE  \
                                            | HRTIM_MDIER_SYNCIE  \
                                            | HRTIM_MDIER_MUPDIE)

#define LL_HRTIM_TIMDIER_CMP1IE            HRTIM_TIMxDIER_CMP1IE
#define LL_HRTIM_TIMDIER_CMP2IE            HRTIM_TIMxDIER_CMP2IE
#define LL_HRTIM_TIMDIER_CMP3IE            HRTIM_TIMxDIER_CMP3IE
#define LL_HRTIM_TIMDIER_CMP4IE            HRTIM_TIMxDIER_CMP4IE
#define LL_HRTIM_TIMDIER_REPIE             HRTIM_TIMxDIER_REPIE
#define LL_HRTIM_TIMDIER_UPDIE             HRTIM_TIMxDIER_UPDIE
#define LL_HRTIM_TIMDIER_CPT1IE            HRTIM_TIMxDIER_CPT1IE
#define LL_HRTIM_TIMDIER_CPT2IE            HRTIM_TIMxDIER_CPT2IE
#define LL_HRTIM_TIMDIER_SET1IE            HRTIM_TIMxDIER_SET1IE
#define LL_HRTIM_TIMDIER_RST1IE            HRTIM_TIMxDIER_RST1IE
#define LL_HRTIM_TIMDIER_SET2IE            HRTIM_TIMxDIER_SET2IE
#define LL_HRTIM_TIMDIER_RST2IE            HRTIM_TIMxDIER_RST2IE
#define LL_HRTIM_TIMDIER_RSTIE             HRTIM_TIMxDIER_RSTIE
#define LL_HRTIM_TIMDIER_DLYPRTIE          HRTIM_TIMxDIER_DLYPRTIE
#define LL_HRTIM_TIMDIER_COTIE             HRTIM_TIMxDIER_COTIE
#define LL_HRTIM_TIMDIER_CORDEIE           HRTIM_TIMxDIER_CORDEIE

#define LL_HRTIM_TIMDIER_ALL_IT           (HRTIM_TIMxDIER_CMP1IE     \
                                           | HRTIM_TIMxDIER_CMP2IE   \
                                           | HRTIM_TIMxDIER_CMP3IE   \
                                           | HRTIM_TIMxDIER_CMP4IE   \
                                           | HRTIM_TIMxDIER_REPIE    \
                                           | HRTIM_TIMxDIER_UPDIE    \
                                           | HRTIM_TIMxDIER_CPT1IE   \
                                           | HRTIM_TIMxDIER_CPT2IE   \
                                           | HRTIM_TIMxDIER_SET1IE   \
                                           | HRTIM_TIMxDIER_RST1IE   \
                                           | HRTIM_TIMxDIER_SET2IE   \
                                           | HRTIM_TIMxDIER_RST2IE   \
                                           | HRTIM_TIMxDIER_RSTIE    \
                                           | HRTIM_TIMxDIER_DLYPRTIE \
                                           | HRTIM_TIMxDIER_COTIE    \
                                           | HRTIM_TIMxDIER_CORDEIE)
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DMA HRTIM DMA requests enable
  * @brief    DMA requests defines which can be used with LL_HRTIM_ReadReg and LL_HRTIM_WriteReg functions.
  * @{
  */
#define LL_HRTIM_MDIER_MCMP1DE             HRTIM_MDIER_MCMP1DE
#define LL_HRTIM_MDIER_MCMP2DE             HRTIM_MDIER_MCMP2DE
#define LL_HRTIM_MDIER_MCMP3DE             HRTIM_MDIER_MCMP3DE
#define LL_HRTIM_MDIER_MCMP4DE             HRTIM_MDIER_MCMP4DE
#define LL_HRTIM_MDIER_MREPDE              HRTIM_MDIER_MREPDE
#define LL_HRTIM_MDIER_SYNCDE              HRTIM_MDIER_SYNCDE
#define LL_HRTIM_MDIER_MUPDDE              HRTIM_MDIER_MUPDDE

#define LL_HRTIM_MDIER_ALL_DMA             (HRTIM_MDIER_MCMP1DE   \
                                            | HRTIM_MDIER_MCMP2DE \
                                            | HRTIM_MDIER_MCMP3DE \
                                            | HRTIM_MDIER_MCMP4DE \
                                            | HRTIM_MDIER_MREPDE  \
                                            | HRTIM_MDIER_SYNCDE  \
                                            | HRTIM_MDIER_MUPDDE)

#define LL_HRTIM_TIMDIER_CMP1DE            HRTIM_TIMxDIER_CMP1DE
#define LL_HRTIM_TIMDIER_CMP2DE            HRTIM_TIMxDIER_CMP2DE
#define LL_HRTIM_TIMDIER_CMP3DE            HRTIM_TIMxDIER_CMP3DE
#define LL_HRTIM_TIMDIER_CMP4DE            HRTIM_TIMxDIER_CMP4DE
#define LL_HRTIM_TIMDIER_REPDE             HRTIM_TIMxDIER_REPDE
#define LL_HRTIM_TIMDIER_UPDDE             HRTIM_TIMxDIER_UPDDE
#define LL_HRTIM_TIMDIER_CPT1DE            HRTIM_TIMxDIER_CPT1DE
#define LL_HRTIM_TIMDIER_CPT2DE            HRTIM_TIMxDIER_CPT2DE
#define LL_HRTIM_TIMDIER_SET1DE            HRTIM_TIMxDIER_SET1DE
#define LL_HRTIM_TIMDIER_RST1DE            HRTIM_TIMxDIER_RST1DE
#define LL_HRTIM_TIMDIER_SET2DE            HRTIM_TIMxDIER_SET2DE
#define LL_HRTIM_TIMDIER_RST2DE            HRTIM_TIMxDIER_RST2DE
#define LL_HRTIM_TIMDIER_RSTDE             HRTIM_TIMxDIER_RSTDE
#define LL_HRTIM_TIMDIER_DLYPRTDE          HRTIM_TIMxDIER_DLYPRTDE
#define LL_HRTIM_TIMDIER_COTDE             HRTIM_TIMxDIER_COTDE
#define LL_HRTIM_TIMDIER_CORDEDE           HRTIM_TIMxDIER_CORDEDE

#define LL_HRTIM_TIMDIER_ALL_DMA           (HRTIM_TIMxDIER_CMP1DE     \
                                            | HRTIM_TIMxDIER_CMP2DE   \
                                            | HRTIM_TIMxDIER_CMP3DE   \
                                            | HRTIM_TIMxDIER_CMP4DE   \
                                            | HRTIM_TIMxDIER_REPDE    \
                                            | HRTIM_TIMxDIER_UPDDE    \
                                            | HRTIM_TIMxDIER_CPT1DE   \
                                            | HRTIM_TIMxDIER_CPT2DE   \
                                            | HRTIM_TIMxDIER_SET1DE   \
                                            | HRTIM_TIMxDIER_RST1DE   \
                                            | HRTIM_TIMxDIER_SET2DE   \
                                            | HRTIM_TIMxDIER_RST2DE   \
                                            | HRTIM_TIMxDIER_RSTDE    \
                                            | HRTIM_TIMxDIER_DLYPRTDE \
                                            | LL_HRTIM_TIMDIER_COTDE \
                                            | LL_HRTIM_TIMDIER_CORDEDE)
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_SYNCIN_SRC HRTIM synchronization input source
  * @{
  * @brief Constants defining the synchronization input source.
  */
#define LL_HRTIM_SYNCIN_SRC_NONE            0x00000000U                                                     /*!< HRTIM is not synchronized and runs in standalone mode */
#define LL_HRTIM_SYNCIN_SRC_TIM1_TRGO      (HRTIM_MCR_SYNCIN_1)                                             /*!< The HRTIM is synchronized with TIM1 TRGO signal */
#define LL_HRTIM_SYNCIN_SRC_GPIO           (HRTIM_MCR_SYNCIN_1 | HRTIM_MCR_SYNCIN_0)                        /*!< The HRTIM is synchronized with HRTIM_SYNCIN input */
#if defined(PLAY1)
#define LL_HRTIM_SYNCIN_SRC_PLAY1_OUT15    (HRTIM_MCR_SYNCIN_1 | HRTIM_MCR_SYNCIN_0 | HRTIM_OR_INSYNCSEL)   /*!< The HRTIM is synchronized with the PLAY1 output 15 signal */
#endif /* PLAY1 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_SYNCOUT_SRC HRTIM synchronization output source
  * @{
  * @brief Constants defining the source and event to be sent on the synchronization output.
  */
#define LL_HRTIM_SYNCOUT_SRC_MASTER_START  0x00000000U                                  /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon master timer start event      */
#define LL_HRTIM_SYNCOUT_SRC_MASTER_CMP1   (HRTIM_MCR_SYNCSRC_0)                        /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon master timer compare 1 event  */
#define LL_HRTIM_SYNCOUT_SRC_TIMA_START    (HRTIM_MCR_SYNCSRC_1)                        /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon timer A start or reset events */
#define LL_HRTIM_SYNCOUT_SRC_TIMA_CMP1     (HRTIM_MCR_SYNCSRC_1 | HRTIM_MCR_SYNCSRC_0)  /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon timer A compare 1 event       */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_SYNCOUT_MODE HRTIM synchronization output mode
  * @{
  * @brief Constants defining the routing and conditioning of the synchronization output event.
  */
#define LL_HRTIM_SYNCOUT_DISABLE         0x00000000U                                /*!< Synchronization output event is disabled */
#define LL_HRTIM_SYNCOUT_POSITIVE_PULSE (HRTIM_MCR_SYNCOUT_1)                       /*!< SCOUT pin has a low idle level and issues a positive pulse of 16 fHRTIM clock cycles length for the synchronization */
#define LL_HRTIM_SYNCOUT_NEGATIVE_PULSE (HRTIM_MCR_SYNCOUT_1 | HRTIM_MCR_SYNCOUT_0) /*!< SCOUT pin has a high idle level and issues a negative pulse of 16 fHRTIM clock cycles length for the synchronization */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_SYNCHRO_MODE  Synchronization mode
  * @{
  * @brief Constants defining the timer's counter reacts to a rising edge on the HRTIM_SCIN input.
  */
#define LL_HRTIM_SYNCHRO_DISABLE          0x00000000U                                 /*!< A rising edge on the HRTIM_SCIN input has no effect of the timer's counter  */
#define LL_HRTIM_SYNCHRO_START            HRTIM_MCR_SYNCSTRTM                         /*!< A rising edge on the HRTIM_SCIN input starts the timer's counter  */
#define LL_HRTIM_SYNCHRO_RESET            HRTIM_MCR_SYNCRSTM                          /*!< A rising edge on the HRTIM_SCIN input resets the timer's counter  */
#define LL_HRTIM_SYNCHRO_RESET_AND_START  (HRTIM_MCR_SYNCSTRTM | HRTIM_MCR_SYNCRSTM)  /*!< A rising edge on the HRTIM_SCIN input resets the timer's counter  */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_TIMER HRTIM timer id
  * @{
  * @brief Constants identifying a timing unit.
  */
#define LL_HRTIM_TIM_NONE                  0x00000000U        /*!< Neither Master timer or timing unit */
#define LL_HRTIM_MASTER                   (HRTIM_MCR_MCEN)    /*!< Master timer identifier */
#define LL_HRTIM_TIMA                     (HRTIM_MCR_TACEN)   /*!< Timer A identifier */
#define LL_HRTIM_TIMB                     (HRTIM_MCR_TBCEN)   /*!< Timer B identifier */
#define LL_HRTIM_TIMC                     (HRTIM_MCR_TCCEN)   /*!< Timer C identifier */
#define LL_HRTIM_TIMD                     (HRTIM_MCR_TDCEN)   /*!< Timer D identifier */
#define LL_HRTIM_TIME                     (HRTIM_MCR_TECEN)   /*!< Timer E identifier */
#define LL_HRTIM_TIMF                     (HRTIM_MCR_TFCEN)   /*!< Timer F identifier */

#define LL_HRTIM_TIMX                     (HRTIM_MCR_TACEN | HRTIM_MCR_TBCEN |\
                                           HRTIM_MCR_TCCEN | HRTIM_MCR_TDCEN |\
                                           HRTIM_MCR_TECEN | HRTIM_MCR_TFCEN )
#define LL_HRTIM_TIM_ALL                (LL_HRTIM_MASTER | LL_HRTIM_TIMX)

/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUTPUT HRTIM output id
  * @{
  * @brief Constants identifying an HRTIM output.
  */
#define LL_HRTIM_OUTPUT_CHA1                HRTIM_OENR_TA1OEN  /*!< Timer A - Output 1 identifier */
#define LL_HRTIM_OUTPUT_CHA2                HRTIM_OENR_TA2OEN  /*!< Timer A - Output 2 identifier */
#define LL_HRTIM_OUTPUT_CHB1                HRTIM_OENR_TB1OEN  /*!< Timer B - Output 1 identifier */
#define LL_HRTIM_OUTPUT_CHB2                HRTIM_OENR_TB2OEN  /*!< Timer B - Output 2 identifier */
#define LL_HRTIM_OUTPUT_CHC1                HRTIM_OENR_TC1OEN  /*!< Timer C - Output 1 identifier */
#define LL_HRTIM_OUTPUT_CHC2                HRTIM_OENR_TC2OEN  /*!< Timer C - Output 2 identifier */
#define LL_HRTIM_OUTPUT_CHD1                HRTIM_OENR_TD1OEN  /*!< Timer D - Output 1 identifier */
#define LL_HRTIM_OUTPUT_CHD2                HRTIM_OENR_TD2OEN  /*!< Timer D - Output 2 identifier */
#define LL_HRTIM_OUTPUT_CHE1                HRTIM_OENR_TE1OEN  /*!< Timer E - Output 1 identifier */
#define LL_HRTIM_OUTPUT_CHE2                HRTIM_OENR_TE2OEN  /*!< Timer E - Output 2 identifier */
#define LL_HRTIM_OUTPUT_CHF1                HRTIM_OENR_TF1OEN  /*!< Timer F - Output 1 identifier */
#define LL_HRTIM_OUTPUT_CHF2                HRTIM_OENR_TF2OEN  /*!< Timer F - Output 2 identifier */

#define LL_HRTIM_OUTPUT_ALL                (LL_HRTIM_OUTPUT_CHA1 | LL_HRTIM_OUTPUT_CHA2 \
                                            | LL_HRTIM_OUTPUT_CHB1 | LL_HRTIM_OUTPUT_CHB2 \
                                            | LL_HRTIM_OUTPUT_CHC1 | LL_HRTIM_OUTPUT_CHC2 \
                                            | LL_HRTIM_OUTPUT_CHD1 | LL_HRTIM_OUTPUT_CHD2 \
                                            | LL_HRTIM_OUTPUT_CHE1 | LL_HRTIM_OUTPUT_CHE2 \
                                            | LL_HRTIM_OUTPUT_CHF1 | LL_HRTIM_OUTPUT_CHF2)
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_COMPARE_UNIT HRTIM compare unit id
  * @{
  * @brief Constants identifying a compare unit.
  */
#define LL_HRTIM_COMPARE_UNIT_1             0U  /*!< Compare unit 2 identifier */
#define LL_HRTIM_COMPARE_UNIT_2             1U  /*!< Compare unit 2 identifier */
#define LL_HRTIM_COMPARE_UNIT_3             2U  /*!< Compare unit 4 identifier */
#define LL_HRTIM_COMPARE_UNIT_4             3U  /*!< Compare unit 4 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CAPTURE_UNIT HRTIM capture unit id
  * @{
  * @brief Constants identifying a capture unit.
  */
#define LL_HRTIM_CAPTURE_UNIT_1             0U  /*!< Capture unit 1 identifier */
#define LL_HRTIM_CAPTURE_UNIT_2             1U  /*!< Capture unit 2 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_FAULT HRTIM fault id
  * @{
  * @brief Constants identifying a fault channel.
  */
#define LL_HRTIM_FLT1      HRTIM_FLTxR_FLT1EN     /*!< Fault channel 1 identifier */
#define LL_HRTIM_FLT2      HRTIM_FLTxR_FLT2EN     /*!< Fault channel 2 identifier */
#define LL_HRTIM_FLT3      HRTIM_FLTxR_FLT3EN     /*!< Fault channel 3 identifier */
#define LL_HRTIM_FLT4      HRTIM_FLTxR_FLT4EN     /*!< Fault channel 4 identifier */
#define LL_HRTIM_FLT5      HRTIM_FLTxR_FLT5EN     /*!< Fault channel 5 identifier */
#define LL_HRTIM_FLT6      HRTIM_FLTxR_FLT6EN     /*!< Fault channel 6 identifier */
#define LL_HRTIM_FLT7      HRTIM_FLTxR_FLT7EN     /*!< Fault channel 7 identifier */
#define LL_HRTIM_FLT8      HRTIM_FLTxR_FLT8EN     /*!< Fault channel 8 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_COMBINED_FAULTS HRTIM combined_faults
  * @{
  * @brief Constants identifying combined faults.
  */
#define LL_HRTIM_FLT1_FLT2      HRTIM_FLTxR_FLT1A2EN     /*!< Fault 1 AND Fault 2 */
#define LL_HRTIM_FLT2_FLT3      HRTIM_FLTxR_FLT2A3EN     /*!< Fault 2 AND Fault 3 */
#define LL_HRTIM_FLT3_FLT4      HRTIM_FLTxR_FLT3A4EN     /*!< Fault 3 AND Fault 4 */
#define LL_HRTIM_FLT4_FLT5      HRTIM_FLTxR_FLT4A5EN     /*!< Fault 4 AND Fault 5 */
#define LL_HRTIM_FLT5_FLT6      HRTIM_FLTxR_FLT5A6EN     /*!< Fault 5 AND Fault 6 */
#define LL_HRTIM_FLT6_FLT7      HRTIM_FLTxR_FLT6A7EN     /*!< Fault 6 AND Fault 7 */
#define LL_HRTIM_FLT7_FLT8      HRTIM_FLTxR_FLT7A8EN     /*!< Fault 7 AND Fault 8 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EVENT HRTIM external event id
  * @{
  * @brief Constants identifying an external event channel.
  */
#define LL_HRTIM_EEV1        0x00000001U     /*!< External event channel 1 identifier */
#define LL_HRTIM_EEV2        0x00000002U     /*!< External event channel 2 identifier */
#define LL_HRTIM_EEV3        0x00000004U     /*!< External event channel 3 identifier */
#define LL_HRTIM_EEV4        0x00000008U     /*!< External event channel 4 identifier */
#define LL_HRTIM_EEV5        0x00000010U     /*!< External event channel 5 identifier */
#define LL_HRTIM_EEV6        0x00000020U     /*!< External event channel 6 identifier */
#define LL_HRTIM_EEV7        0x00000040U     /*!< External event channel 7 identifier */
#define LL_HRTIM_EEV8        0x00000080U     /*!< External event channel 8 identifier */
#define LL_HRTIM_EEV9        0x00000100U     /*!< External event channel 9 identifier */
#define LL_HRTIM_EEV10       0x00000200U     /*!< External event channel 10 identifier */
#define LL_HRTIM_EEV11       0x00000400U     /*!< External event channel 11 identifier */
#define LL_HRTIM_EEV12       0x00000800U     /*!< External event channel 12 identifier */
#define LL_HRTIM_EEV13       0x00001000U     /*!< External event channel 13 identifier */
#define LL_HRTIM_EEV14       0x00002000U     /*!< External event channel 14 identifier */
#define LL_HRTIM_EEV15       0x00004000U     /*!< External event channel 15 identifier */
#define LL_HRTIM_EEV16       0x00008000U     /*!< External event channel 16 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_COMBINED_EVENT HRTIM combined event id
  * @{
  * @brief Constants identifying a combined event.
  */
#define LL_HRTIM_EEVA        0x00000001U     /*!< Combined event A identifier */
#define LL_HRTIM_EEVB        0x00000002U     /*!< Combined event B identifier */
#define LL_HRTIM_EEVC        0x00000004U     /*!< Combined event C identifier */
#define LL_HRTIM_EEVD        0x00000008U     /*!< Combined event D identifier */
#define LL_HRTIM_EEVE        0x00000010U     /*!< Combined event E identifier */
#define LL_HRTIM_EEVF        0x00000020U     /*!< Combined event F identifier */
#define LL_HRTIM_EEVG        0x00000040U     /*!< Combined event G identifier */
#define LL_HRTIM_EEVH        0x00000080U     /*!< Combined event H identifier */
#define LL_HRTIM_EEVI        0x00000100U     /*!< Combined event I identifier */
#define LL_HRTIM_EEVJ        0x00000200U     /*!< Combined event J identifier */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_COMBINED_EVENT_SRC HRTIM combined event source
  * @{
  * @brief Constants identifying the source of a combined event.
  */
/* Combined event A */
#define LL_HRTIM_EEVA_SRC_EEV1         0x00000000U                                          /*!< Combined event A is connected to external event 1 */
#define LL_HRTIM_EEVA_SRC_EEV11        HRTIM_EESELxR_EEVASEL_0                               /*!< Combined event A is connected to external event 11 */
#define LL_HRTIM_EEVA_SRC_EEV1_EEV2    HRTIM_EESELxR_EEVASEL_1                               /*!< Combined event A is connected to external events 1 and 2 */
#define LL_HRTIM_EEVA_SRC_EEV1_EEV11   (HRTIM_EESELxR_EEVASEL_1 | HRTIM_EESELxR_EEVASEL_0)    /*!< Combined event A is connected to external events 1 and 11 */
/* Combined event B */
#define LL_HRTIM_EEVB_SRC_EEV2         0x00000000U                                          /*!< Combined event B is connected to external event 2 */
#define LL_HRTIM_EEVB_SRC_EEV12        HRTIM_EESELxR_EEVBSEL_0                               /*!< Combined event B is connected to external event 12 */
#define LL_HRTIM_EEVB_SRC_EEV2_EEV3    HRTIM_EESELxR_EEVBSEL_1                               /*!< Combined event B is connected to external events 2 and 3 */
#define LL_HRTIM_EEVB_SRC_EEV2_EEV12   (HRTIM_EESELxR_EEVBSEL_1 | HRTIM_EESELxR_EEVBSEL_0)    /*!< Combined event B is connected to external events 2 and 12 */
/* Combined event C */
#define LL_HRTIM_EEVC_SRC_EEV3         0x00000000U                                          /*!< Combined event C is connected to external event 3 */
#define LL_HRTIM_EEVC_SRC_EEV13        HRTIM_EESELxR_EEVCSEL_0                               /*!< Combined event C is connected to external event 13 */
#define LL_HRTIM_EEVC_SRC_EEV3_EEV4    HRTIM_EESELxR_EEVCSEL_1                               /*!< Combined event C is connected to external events 3 and 4 */
#define LL_HRTIM_EEVC_SRC_EEV3_EEV13   (HRTIM_EESELxR_EEVCSEL_1 | HRTIM_EESELxR_EEVCSEL_0)    /*!< Combined event C is connected to external events 3 and 13 */
/* Combined event D */
#define LL_HRTIM_EEVD_SRC_EEV4         0x00000000U                                          /*!< Combined event D is connected to external event 4 */
#define LL_HRTIM_EEVD_SRC_EEV14        HRTIM_EESELxR_EEVDSEL_0                               /*!< Combined event D is connected to external event 14 */
#define LL_HRTIM_EEVD_SRC_EEV4_EEV5    HRTIM_EESELxR_EEVDSEL_1                               /*!< Combined event D is connected to external events 4 and 5 */
#define LL_HRTIM_EEVD_SRC_EEV4_EEV14   (HRTIM_EESELxR_EEVDSEL_1 | HRTIM_EESELxR_EEVDSEL_0)    /*!< Combined event D is connected to external events 4 and 14 */
/* Combined event E */
#define LL_HRTIM_EEVE_SRC_EEV5         0x00000000U                                          /*!< Combined event E is connected to external event 5 */
#define LL_HRTIM_EEVE_SRC_EEV15        HRTIM_EESELxR_EEVESEL_0                               /*!< Combined event E is connected to external event 15 */
#define LL_HRTIM_EEVE_SRC_EEV5_EEV6    HRTIM_EESELxR_EEVESEL_1                               /*!< Combined event E is connected to external events 5 and 6 */
#define LL_HRTIM_EEVE_SRC_EEV5_EEV15   (HRTIM_EESELxR_EEVESEL_1 | HRTIM_EESELxR_EEVESEL_0)    /*!< Combined event E is connected to external events 5 and 15 */
/* Combined event F */
#define LL_HRTIM_EEVF_SRC_EEV6         0x00000000U                                          /*!< Combined event F is connected to external event 6 */
#define LL_HRTIM_EEVF_SRC_EEV16        HRTIM_EESELxR_EEVFSEL_0                               /*!< Combined event F is connected to external event 16 */
#define LL_HRTIM_EEVF_SRC_EEV6_EEV7    HRTIM_EESELxR_EEVFSEL_1                               /*!< Combined event F is connected to external events 6 and 7 */
#define LL_HRTIM_EEVF_SRC_EEV6_EEV16   (HRTIM_EESELxR_EEVFSEL_1 | HRTIM_EESELxR_EEVFSEL_0)    /*!< Combined event F is connected to external events 6 and 16 */
/* Combined event G */
#define LL_HRTIM_EEVG_SRC_EEV7         0x00000000U                                          /*!< Combined event G is connected to external event 7 */
#define LL_HRTIM_EEVG_SRC_EEV11        HRTIM_EESELxR_EEVGSEL_0                               /*!< Combined event G is connected to external event 11 */
#define LL_HRTIM_EEVG_SRC_EEV7_EEV8    HRTIM_EESELxR_EEVGSEL_1                               /*!< Combined event G is connected to external events 7 and 8 */
#define LL_HRTIM_EEVG_SRC_EEV7_EEV11   (HRTIM_EESELxR_EEVGSEL_1 | HRTIM_EESELxR_EEVGSEL_0)    /*!< Combined event G is connected to external events 7 and 11 */
/* Combined event H */
#define LL_HRTIM_EEVH_SRC_EEV8         0x00000000U                                          /*!< Combined event H is connected to external event 8 */
#define LL_HRTIM_EEVH_SRC_EEV12        HRTIM_EESELxR_EEVHSEL_0                               /*!< Combined event H is connected to external event 12 */
#define LL_HRTIM_EEVH_SRC_EEV8_EEV9    HRTIM_EESELxR_EEVHSEL_1                               /*!< Combined event H is connected to external events 8 and 9 */
#define LL_HRTIM_EEVH_SRC_EEV8_EEV12   (HRTIM_EESELxR_EEVHSEL_1 | HRTIM_EESELxR_EEVHSEL_0)    /*!< Combined event H is connected to external events 8 and 12 */
/* Combined event I */
#define LL_HRTIM_EEVI_SRC_EEV9         0x00000000U                                          /*!< Combined event I is connected to external event 9 */
#define LL_HRTIM_EEVI_SRC_EEV13        HRTIM_EESELxR_EEVISEL_0                               /*!< Combined event I is connected to external event 13 */
#define LL_HRTIM_EEVI_SRC_EEV9_EEV10   HRTIM_EESELxR_EEVISEL_1                               /*!< Combined event I is connected to external events 9 and 10 */
#define LL_HRTIM_EEVI_SRC_EEV9_EEV13   (HRTIM_EESELxR_EEVISEL_1 | HRTIM_EESELxR_EEVISEL_0)    /*!< Combined event I is connected to external events 9 and 13 */
/* Combined event J */
#define LL_HRTIM_EEVJ_SRC_EEV10        0x00000000U                                          /*!< Combined event J is connected to external event 10 */
#define LL_HRTIM_EEVJ_SRC_EEV14        HRTIM_EESELxR_EEVJSEL_0                               /*!< Combined event J is connected to external event 14 */
#define LL_HRTIM_EEVJ_SRC_EEV10_EEV11  HRTIM_EESELxR_EEVJSEL_1                               /*!< Combined event J is connected to external events 10 and 11 */
#define LL_HRTIM_EEVJ_SRC_EEV10_EEV14  (HRTIM_EESELxR_EEVJSEL_1 | HRTIM_EESELxR_EEVJSEL_0)    /*!< Combined event J is connected to external events 10 and 14 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUTPUTSTATE HRTIM output state
  * @{
  * @brief Constants defining the state of an HRTIM output.
  */
#define LL_HRTIM_OUTPUTSTATUS_DISABLED     0x00000001U /*!< Main operating mode, where the output can take the active or inactive level as programmed in the crossbar unit */
#define LL_HRTIM_OUTPUTSTATUS_ENABLED      0x00000002U /*!< Default operating state (e.g. after an HRTIM reset, when the outputs are disabled by software or during a burst mode operation) */
#define LL_HRTIM_OUTPUTSTATUS_FAULT        0x00000003U /*!< Safety state, entered in case of a shut-down request on FAULTx inputs */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_ADCTRIG HRTIM adc trigger
  * @{
  * @brief Constants identifying an ADC trigger.
  */
#define LL_HRTIM_ADCTRIG1              0x00000000U  /*!< ADC trigger 1 identifier */
#define LL_HRTIM_ADCTRIG2              0x00000001U  /*!< ADC trigger 2 identifier */
#define LL_HRTIM_ADCTRIG3              0x00000002U  /*!< ADC trigger 3 identifier */
#define LL_HRTIM_ADCTRIG4              0x00000003U  /*!< ADC trigger 4 identifier */
#define LL_HRTIM_ADCTRIG5              0x00000004U  /*!< ADC trigger 5 identifier */
#define LL_HRTIM_ADCTRIG6              0x00000005U  /*!< ADC trigger 6 identifier */
#define LL_HRTIM_ADCTRIG7              0x00000006U  /*!< ADC trigger 7 identifier */
#define LL_HRTIM_ADCTRIG8              0x00000007U  /*!< ADC trigger 8 identifier */
#define LL_HRTIM_ADCTRIG9              0x00000008U  /*!< ADC trigger 9 identifier */
#define LL_HRTIM_ADCTRIG10             0x00000009U  /*!< ADC trigger 10 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_ADCTRIG_UPDATE HRTIM adc trigger update
  * @{
  * @brief constants defining the source triggering the update of the HRTIM_ADCxR register
  *       (transfer from preload to active register).
  */
#define LL_HRTIM_ADCTRIG_UPDATE_MASTER  0x00000000U  /*!< HRTIM_ADCxR register update is triggered by the Master timer */
#define LL_HRTIM_ADCTRIG_UPDATE_TIMA 0x00000001U     /*!< HRTIM_ADCxR register update is triggered by the Timer A */
#define LL_HRTIM_ADCTRIG_UPDATE_TIMB 0x00000002U     /*!< HRTIM_ADCxR register update is triggered by the Timer B */
#define LL_HRTIM_ADCTRIG_UPDATE_TIMC 0x00000003U     /*!< HRTIM_ADCxR register update is triggered by the Timer C */
#define LL_HRTIM_ADCTRIG_UPDATE_TIMD 0x00000004U     /*!< HRTIM_ADCxR register update is triggered by the Timer D */
#define LL_HRTIM_ADCTRIG_UPDATE_TIME 0x00000005U     /*!< HRTIM_ADCxR register update is triggered by the Timer E */
#define LL_HRTIM_ADCTRIG_UPDATE_TIMF 0x00000006U     /*!< HRTIM_ADCxR register update is triggered by the Timer F */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_ADCTRIG_SRC13 HRTIM ADC trigger 1/3 source
  * @{
  * @brief constants defining the events triggering ADC conversion for ADC Triggers 1 and 3.
  */
#define LL_HRTIM_ADCTRIG_SRC13_NONE              0x00000000U               /*!< No ADC trigger event */
#define LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP1       HRTIM_ADC1R_ADC1MC1       /*!< ADC Trigger on master compare 1 */
#define LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP2       HRTIM_ADC1R_ADC1MC2       /*!< ADC Trigger on master compare 2 */
#define LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP3       HRTIM_ADC1R_ADC1MC3       /*!< ADC Trigger on master compare 3 */
#define LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP4       HRTIM_ADC1R_ADC1MC4       /*!< ADC Trigger on master compare 4 */
#define LL_HRTIM_ADCTRIG_SRC13_MASTER_PERIOD     HRTIM_ADC1R_ADC1MPER      /*!< ADC Trigger on master period */
#define LL_HRTIM_ADCTRIG_SRC13_EEV1              HRTIM_ADC1R_ADC1EEV1      /*!< ADC Trigger on external event 1 */
#define LL_HRTIM_ADCTRIG_SRC13_EEV2              HRTIM_ADC1R_ADC1EEV2      /*!< ADC Trigger on external event 2 */
#define LL_HRTIM_ADCTRIG_SRC13_EEV3              HRTIM_ADC1R_ADC1EEV3      /*!< ADC Trigger on external event 3 */
#define LL_HRTIM_ADCTRIG_SRC13_EEV4              HRTIM_ADC1R_ADC1EEV4      /*!< ADC Trigger on external event 4 */
#define LL_HRTIM_ADCTRIG_SRC13_EEV5              HRTIM_ADC1R_ADC1EEV5      /*!< ADC Trigger on external event 5 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP3         HRTIM_ADC1R_ADC1TAC3      /*!< ADC Trigger on Timer A compare 3 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP4         HRTIM_ADC1R_ADC1TAC4      /*!< ADC Trigger on Timer A compare 4 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMA_PERIOD       HRTIM_ADC1R_ADC1TAPER     /*!< ADC Trigger on Timer A period */
#define LL_HRTIM_ADCTRIG_SRC13_TIMA_RESET        HRTIM_ADC1R_ADC1TARST     /*!< ADC Trigger on Timer A reset */
#define LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP3         HRTIM_ADC1R_ADC1TBC3      /*!< ADC Trigger on Timer B compare 3 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP4         HRTIM_ADC1R_ADC1TBC4      /*!< ADC Trigger on Timer B compare 4 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMB_PERIOD       HRTIM_ADC1R_ADC1TBPER     /*!< ADC Trigger on Timer B period */
#define LL_HRTIM_ADCTRIG_SRC13_TIMB_RESET        HRTIM_ADC1R_ADC1TBRST     /*!< ADC Trigger on Timer B reset */
#define LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP3         HRTIM_ADC1R_ADC1TCC3      /*!< ADC Trigger on Timer C compare 3 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP4         HRTIM_ADC1R_ADC1TCC4      /*!< ADC Trigger on Timer C compare 4 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMC_PERIOD       HRTIM_ADC1R_ADC1TCPER     /*!< ADC Trigger on Timer C period */
#define LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP3         HRTIM_ADC1R_ADC1TDC3      /*!< ADC Trigger on Timer D compare 3 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP4         HRTIM_ADC1R_ADC1TDC4      /*!< ADC Trigger on Timer D compare 4 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMD_PERIOD       HRTIM_ADC1R_ADC1TDPER     /*!< ADC Trigger on Timer D period */
#define LL_HRTIM_ADCTRIG_SRC13_TIME_CMP3         HRTIM_ADC1R_ADC1TEC3      /*!< ADC Trigger on Timer E compare 3 */
#define LL_HRTIM_ADCTRIG_SRC13_TIME_CMP4         HRTIM_ADC1R_ADC1TEC4      /*!< ADC Trigger on Timer E compare 4 */
#define LL_HRTIM_ADCTRIG_SRC13_TIME_PERIOD       HRTIM_ADC1R_ADC1TEPER     /*!< ADC Trigger on Timer E period */
#define LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP2         HRTIM_ADC1R_ADC1TFC2      /*!< ADC Trigger on Timer F compare 2 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP3         HRTIM_ADC1R_ADC1TFC3      /*!< ADC Trigger on Timer F compare 3 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP4         HRTIM_ADC1R_ADC1TFC4      /*!< ADC Trigger on Timer F compare 4 */
#define LL_HRTIM_ADCTRIG_SRC13_TIMF_PERIOD       HRTIM_ADC1R_ADC1TFPER     /*!< ADC Trigger on Timer F period */
#define LL_HRTIM_ADCTRIG_SRC13_TIMF_RESET        HRTIM_ADC1R_ADC1TFRST     /*!< ADC Trigger on Timer F reset */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_ADCTRIG_SRC24 HRTIM ADC trigger 2/4 source
  * @{
  * @brief constants defining the events triggering ADC conversion for ADC Triggers 2 and 4.
  */
#define LL_HRTIM_ADCTRIG_SRC24_NONE              0x00000000U             /*!< No ADC trigger event */
#define LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP1       HRTIM_ADC2R_ADC2MC1     /*!< ADC Trigger on master compare 1 */
#define LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP2       HRTIM_ADC2R_ADC2MC2     /*!< ADC Trigger on master compare 2 */
#define LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP3       HRTIM_ADC2R_ADC2MC3     /*!< ADC Trigger on master compare 3 */
#define LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP4       HRTIM_ADC2R_ADC2MC4     /*!< ADC Trigger on master compare 4 */
#define LL_HRTIM_ADCTRIG_SRC24_MASTER_PERIOD     HRTIM_ADC2R_ADC2MPER    /*!< ADC Trigger on master period */
#define LL_HRTIM_ADCTRIG_SRC24_EEV6              HRTIM_ADC2R_ADC2EEV6    /*!< ADC Trigger on external event 6 */
#define LL_HRTIM_ADCTRIG_SRC24_EEV7              HRTIM_ADC2R_ADC2EEV7    /*!< ADC Trigger on external event 7 */
#define LL_HRTIM_ADCTRIG_SRC24_EEV8              HRTIM_ADC2R_ADC2EEV8    /*!< ADC Trigger on external event 8 */
#define LL_HRTIM_ADCTRIG_SRC24_EEV9              HRTIM_ADC2R_ADC2EEV9    /*!< ADC Trigger on external event 9 */
#define LL_HRTIM_ADCTRIG_SRC24_EEV10             HRTIM_ADC2R_ADC2EEV10   /*!< ADC Trigger on external event 10 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP2         HRTIM_ADC2R_ADC2TAC2    /*!< ADC Trigger on Timer A compare 2 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP4         HRTIM_ADC2R_ADC2TAC4    /*!< ADC Trigger on Timer A compare 4 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMA_PERIOD       HRTIM_ADC2R_ADC2TAPER   /*!< ADC Trigger on Timer A period */
#define LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP2         HRTIM_ADC2R_ADC2TBC2    /*!< ADC Trigger on Timer B compare 2 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP4         HRTIM_ADC2R_ADC2TBC4    /*!< ADC Trigger on Timer B compare 4 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMB_PERIOD       HRTIM_ADC2R_ADC2TBPER   /*!< ADC Trigger on Timer B period */
#define LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP2         HRTIM_ADC2R_ADC2TCC2    /*!< ADC Trigger on Timer C compare 2 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP4        HRTIM_ADC2R_ADC2TCC4     /*!< ADC Trigger on Timer C compare 4 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMC_PERIOD      HRTIM_ADC2R_ADC2TCPER    /*!< ADC Trigger on Timer C period */
#define LL_HRTIM_ADCTRIG_SRC24_TIMC_RESET       HRTIM_ADC2R_ADC2TCRST    /*!< ADC Trigger on Timer C reset */
#define LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP2        HRTIM_ADC2R_ADC2TDC2     /*!< ADC Trigger on Timer D compare 2 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP4        HRTIM_ADC2R_ADC2TDC4     /*!< ADC Trigger on Timer D compare 4 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMD_PERIOD      HRTIM_ADC2R_ADC2TDPER    /*!< ADC Trigger on Timer D period */
#define LL_HRTIM_ADCTRIG_SRC24_TIMD_RESET       HRTIM_ADC2R_ADC2TDRST    /*!< ADC Trigger on Timer D reset */
#define LL_HRTIM_ADCTRIG_SRC24_TIME_CMP2        HRTIM_ADC2R_ADC2TEC2     /*!< ADC Trigger on Timer E compare 2 */
#define LL_HRTIM_ADCTRIG_SRC24_TIME_CMP3        HRTIM_ADC2R_ADC2TEC3     /*!< ADC Trigger on Timer E compare 3 */
#define LL_HRTIM_ADCTRIG_SRC24_TIME_CMP4        HRTIM_ADC2R_ADC2TEC4     /*!< ADC Trigger on Timer E compare 4 */
#define LL_HRTIM_ADCTRIG_SRC24_TIME_RESET       HRTIM_ADC2R_ADC2TERST    /*!< ADC Trigger on Timer E reset */
#define LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP2        HRTIM_ADC2R_ADC2TFC2     /*!< ADC Trigger on Timer F compare 2 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP3        HRTIM_ADC2R_ADC2TFC3     /*!< ADC Trigger on Timer F compare 3 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP4        HRTIM_ADC2R_ADC2TFC4     /*!< ADC Trigger on Timer F compare 4 */
#define LL_HRTIM_ADCTRIG_SRC24_TIMF_PERIOD      HRTIM_ADC2R_ADC2TFPER    /*!< ADC Trigger on Timer F period */
/**
  * @}
  */

/** @defgroup HRTIM_ADC_TRIG_SRC6810 HRTIM ADC trigger 6/8/10 source
  * @{
  * @brief Constants defining the selection that can be used as ADC trigger source for extended ADC 6, 8 ,10.
  */
#define LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP1    0x00000000U              /*!<  ADC Trigger on Master Compare 1 */
#define LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP2    0x00000001U              /*!<  ADC Trigger on Master Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP3    0x00000002U              /*!<  ADC Trigger on Master Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP4    0x00000003U              /*!<  ADC Trigger on Master Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC6810_MASTER_PERIOD  0x00000004U              /*!<  ADC Trigger on Master Period */
#define LL_HRTIM_ADCTRIG_SRC6810_EEV6           0x00000005U              /*!<  ADC Trigger on External Event 6 */
#define LL_HRTIM_ADCTRIG_SRC6810_EEV7           0x00000006U              /*!<  ADC Trigger on External Event 7 */
#define LL_HRTIM_ADCTRIG_SRC6810_EEV8           0x00000007U              /*!<  ADC Trigger on External Event 8 */
#define LL_HRTIM_ADCTRIG_SRC6810_EEV9           0x00000008U              /*!<  ADC Trigger on External Event 9 */
#define LL_HRTIM_ADCTRIG_SRC6810_EEV10          0x00000009U              /*!<  ADC Trigger on External Event 10 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP2      0x0000000AU              /*!<  ADC Trigger on Timer A Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP4      0x0000000BU              /*!<  ADC Trigger on Timer A Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMA_PERIOD    0x0000000CU              /*!<  ADC Trigger on Timer A Period */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP2      0x0000000DU              /*!<  ADC Trigger on Timer B Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP4      0x0000000EU              /*!<  ADC Trigger on Timer B Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMB_PERIOD    0x0000000FU              /*!<  ADC Trigger on Timer B Period */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP2      0x00000010U              /*!<  ADC Trigger on Timer C Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP4      0x00000011U              /*!<  ADC Trigger on Timer C Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMC_PERIOD    0x00000012U              /*!<  ADC Trigger on Timer C Period */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMC_RESET     0x00000013U              /*!<  ADC Trigger on Timer C Reset */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP2      0x00000014U              /*!<  ADC Trigger on Timer D Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP4      0x00000015U              /*!<  ADC Trigger on Timer D Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMD_PERIOD    0x00000016U              /*!<  ADC Trigger on Timer D Period */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMD_RESET     0x00000017U              /*!<  ADC Trigger on Timer D Reset */
#define LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP2      0x00000018U              /*!<  ADC Trigger on Timer E Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP3      0x00000019U              /*!<  ADC Trigger on Timer E Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP4      0x0000001AU              /*!<  ADC Trigger on Timer E Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIME_RESET     0x0000001BU              /*!<  ADC Trigger on Timer E Reset */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP2      0x0000001CU              /*!<  ADC Trigger on Timer F Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP3      0x0000001DU              /*!<  ADC Trigger on Timer F Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP4      0x0000001EU              /*!<  ADC Trigger on Timer F Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC6810_TIMF_PERIOD    0x0000001FU              /*!<  ADC Trigger on Timer F Period */
/**
  * @}
  */

/** @defgroup HRTIM_ADC_TRIG_SRC579 HRTIM ADC trigger 5/7/9 source
  * @{
  * @brief Constants defining the selection that can be used as ADC trigger source for extended ADC 5, 7 ,9.
  */
#define LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP1     0x00000000U              /*!<  ADC Trigger on Master Compare 1 */
#define LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP2     0x00000001U              /*!<  ADC Trigger on Master Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP3     0x00000002U              /*!<  ADC Trigger on Master Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP4     0x00000003U              /*!<  ADC Trigger on Master Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC579_MASTER_PERIOD   0x00000004U              /*!<  ADC Trigger on Master Period */
#define LL_HRTIM_ADCTRIG_SRC579_EEV1            0x00000005U              /*!<  ADC Trigger on External Event 1 */
#define LL_HRTIM_ADCTRIG_SRC579_EEV2            0x00000006U              /*!<  ADC Trigger on External Event 2 */
#define LL_HRTIM_ADCTRIG_SRC579_EEV3            0x00000007U              /*!<  ADC Trigger on External Event 3 */
#define LL_HRTIM_ADCTRIG_SRC579_EEV4            0x00000008U              /*!<  ADC Trigger on External Event 4 */
#define LL_HRTIM_ADCTRIG_SRC579_EEV5            0x00000009U              /*!<  ADC Trigger on External Event 5 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP3       0x0000000AU              /*!<  ADC Trigger on Timer A Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP4       0x0000000BU              /*!<  ADC Trigger on Timer A Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMA_PERIOD     0x0000000CU              /*!<  ADC Trigger on Timer A Period */
#define LL_HRTIM_ADCTRIG_SRC579_TIMA_RESET      0x0000000DU              /*!<  ADC Trigger on Timer A Period */
#define LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP3       0x0000000EU              /*!<  ADC Trigger on Timer B Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP4       0x0000000FU              /*!<  ADC Trigger on Timer B Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMB_PERIOD     0x00000010U              /*!<  ADC Trigger on Timer B Period */
#define LL_HRTIM_ADCTRIG_SRC579_TIMB_RESET      0x00000011U              /*!<  ADC Trigger on Timer B Reset*/
#define LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP3       0x00000012U              /*!<  ADC Trigger on Timer C Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP4       0x00000013U              /*!<  ADC Trigger on Timer C Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMC_PERIOD     0x00000014U              /*!<  ADC Trigger on Timer C Period */
#define LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP3       0x00000015U              /*!<  ADC Trigger on Timer D Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP4       0x00000016U              /*!<  ADC Trigger on Timer D Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMD_PERIOD     0x00000017U              /*!<  ADC Trigger on Timer D Period */
#define LL_HRTIM_ADCTRIG_SRC579_TIME_CMP3       0x00000018U              /*!<  ADC Trigger on Timer E Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC579_TIME_CMP4       0x00000019U              /*!<  ADC Trigger on Timer E Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC579_TIME_PERIOD     0x0000001AU              /*!<  ADC Trigger on Timer E Period */
#define LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP2       0x0000001BU              /*!<  ADC Trigger on Timer F Compare 2 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP3       0x0000001CU              /*!<  ADC Trigger on Timer F Compare 3 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP4       0x0000001DU              /*!<  ADC Trigger on Timer F Compare 4 */
#define LL_HRTIM_ADCTRIG_SRC579_TIMF_PERIOD     0x0000001EU              /*!<  ADC Trigger on Timer F Period */
#define LL_HRTIM_ADCTRIG_SRC579_TIMF_RESET      0x0000001FU              /*!<  ADC Trigger on Timer F Reset */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CALIBRATIONRATE HRTIM DLL calibration rate
  * @{
  * @brief Constants defining the DLL calibration periods (in micro seconds).
  */
#define LL_HRTIM_DLLCALIBRATION_RATE_0         0x00000000U                                    /*!< Periodic DLL calibration: T = 1048576U * tHRTIM */
#define LL_HRTIM_DLLCALIBRATION_RATE_1         (HRTIM_DLLCR_CALRTE_0)                         /*!< Periodic DLL calibration: T = 131072U * tHRTIM */
#define LL_HRTIM_DLLCALIBRATION_RATE_2         (HRTIM_DLLCR_CALRTE_1)                         /*!< Periodic DLL calibration: T = 16384U * tHRTIM */
#define LL_HRTIM_DLLCALIBRATION_RATE_3         (HRTIM_DLLCR_CALRTE_1 | HRTIM_DLLCR_CALRTE_0)  /*!< Periodic DLL calibration: T = 2048U * tHRTIM */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_PRESCALERRATIO HRTIM prescaler ratio
  * @{
  * @brief Constants defining timer high-resolution clock prescaler ratio.
  */
#define LL_HRTIM_PRESCALERRATIO_MUL32      0x00000000U              /*!< fHRCK: fHRTIM x 32  */
#define LL_HRTIM_PRESCALERRATIO_MUL16      0x00000001U              /*!< fHRCK: fHRTIM x 16  */
#define LL_HRTIM_PRESCALERRATIO_MUL8       0x00000002U              /*!< fHRCK: fHRTIM x 8   */
#define LL_HRTIM_PRESCALERRATIO_MUL4       0x00000003U              /*!< fHRCK: fHRTIM x 4   */
#define LL_HRTIM_PRESCALERRATIO_MUL2       0x00000004U              /*!< fHRCK: fHRTIM x 2   */
#define LL_HRTIM_PRESCALERRATIO_DIV1       0x00000005U              /*!< fHRCK: fHRTIM       */
#define LL_HRTIM_PRESCALERRATIO_DIV2       0x00000006U              /*!< fHRCK: fHRTIM / 2   */
#define LL_HRTIM_PRESCALERRATIO_DIV4       0x00000007U              /*!< fHRCK: fHRTIM / 4   */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_MODE HRTIM counter operating mode
  * @{
  * @brief Constants defining timer counter operating mode.
  */
#define LL_HRTIM_MODE_CONTINUOUS                0x00000008U  /*!< The timer operates in continuous (free-running) mode */
#define LL_HRTIM_MODE_SINGLESHOT                0x00000000U  /*!< The timer operates in non retriggerable single-shot mode */
#define LL_HRTIM_MODE_SINGLESHOT_RETRIGGERABLE  0x00000010U  /*!< The timer operates in retriggerable single-shot mode */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DACTRIG HRTIM DAC trigger
  * @{
  * @brief Constants defining on which output the DAC synchronization event is sent.
  */
#define LL_HRTIM_DACTRIG_NONE           0x00000000U                                /*!< No DAC synchronization event generated */
#define LL_HRTIM_DACTRIG_DACTRIGOUT1   (HRTIM_MCR_DACSYNC_0)                       /*!< DAC synchronization event generated on DACTrigOut1 output upon timer update */
#define LL_HRTIM_DACTRIG_DACTRIGOUT2   (HRTIM_MCR_DACSYNC_1)                       /*!< DAC synchronization event generated on DACTrigOut2 output upon timer update */
#define LL_HRTIM_DACTRIG_DACTRIGOUT3   (HRTIM_MCR_DACSYNC_1 | HRTIM_MCR_DACSYNC_0) /*!< DAC synchronization event generated on DACTrigOut3 output upon timer update */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_ADCTRIG_MODE HRTIM ADC trigger mode
  * @{
  * @brief Constants defining when the ADC triggers are generated in push-pull mode.
  */
#define LL_HRTIM_ADCTRIG_OUT1_OUT2 0x00000000U                       /*!< ADC triggers generated for both Channel 1 and Channel 2 active phases */
#define LL_HRTIM_ADCTRIG_OUT1         (HRTIM_TIMxCR2_ADCTRGCH1)      /*!< ADC triggers generated only when Channel 1 is active */
#define LL_HRTIM_ADCTRIG_OUT2         (HRTIM_TIMxCR2_ADCTRGCH2)      /*!< ADC triggers generated only when Channel 2 is active*/
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_UPDATETRIG HRTIM update trigger
  * @{
  * @brief Constants defining whether the registers update is done synchronously with any other timer or master update.
  */
#define LL_HRTIM_UPDATETRIG_NONE           0x00000000U               /*!< Register update is disabled */
#define LL_HRTIM_UPDATETRIG_MASTER_UPDATE  (HRTIM_TIMxCR_MSTU)       /*!< Register update is triggered by the master timer update */
#define LL_HRTIM_UPDATETRIG_TIMA_UPDATE    (HRTIM_TIMxCR_TAU)        /*!< Register update is triggered by the timer A update */
#define LL_HRTIM_UPDATETRIG_TIMB_UPDATE    (HRTIM_TIMxCR_TBU)        /*!< Register update is triggered by the timer B update */
#define LL_HRTIM_UPDATETRIG_TIMC_UPDATE    (HRTIM_TIMxCR_TCU)        /*!< Register update is triggered by the timer C update*/
#define LL_HRTIM_UPDATETRIG_TIMD_UPDATE    (HRTIM_TIMxCR_TDU)        /*!< Register update is triggered by the timer D update */
#define LL_HRTIM_UPDATETRIG_TIME_UPDATE    (HRTIM_TIMxCR_TEU)        /*!< Register update is triggered by the timer E update */
#define LL_HRTIM_UPDATETRIG_TIMF_UPDATE    (HRTIM_TIMxCR_TFU)        /*!< Register update is triggered by the timer F update */
#define LL_HRTIM_UPDATETRIG_REPETITION     (HRTIM_TIMxCR_TREPU)     /*!< Register update is triggered when the counter rolls over and HRTIM_REPx = 0*/
#define LL_HRTIM_UPDATETRIG_RESET          (HRTIM_TIMxCR_TRSTU)     /*!< Register update is triggered by counter reset or roll-over to 0 after reaching the period value in continuous mode */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_UPDATEGAT HRTIM update gating
  * @{
  * @brief Constants defining how the update occurs relatively to the burst DMA transaction and the external update
  *        request on update enable inputs 1 to 3.
  */
#define LL_HRTIM_UPDATEGAT_INDEPENDENT           0x00000000U                                                              /*!< Update done independently from the DMA burst transfer completion */
#define LL_HRTIM_UPDATEGAT_DMABURST_COMPLETE     (HRTIM_TIMxCR_UPDGAT_0)                                                  /*!< Update done when the DMA burst transfer is completed */
#define LL_HRTIM_UPDATEGAT_DMABURST_UPDATE       (HRTIM_TIMxCR_UPDGAT_1)                                                  /*!< Update done on timer roll-over following a DMA burst transfer completion*/
#define LL_HRTIM_UPDATEGAT_TIM10_OC1             (HRTIM_TIMxCR_UPDGAT_1 | HRTIM_TIMxCR_UPDGAT_0)                           /*!< Slave timer only - Update done on a rising edge of TIM10 OC1 signal */
#define LL_HRTIM_UPDATEGAT_TIM11_OC1             (HRTIM_TIMxCR_UPDGAT_2)                                                   /*!< Slave timer only - Update done on a rising edge of TIM11 OC1 signal */
#define LL_HRTIM_UPDATEGAT_TIM6_TRGO             (HRTIM_TIMxCR_UPDGAT_2 | HRTIM_TIMxCR_UPDGAT_0)                          /*!< Slave timer only - Update done on a rising edge of TIM6 TRGO signal */
#if defined(PLAY1)
#define LL_HRTIM_UPDATEGAT_PLAY1_OUT14           (HRTIM_TIMxCR_UPDGAT_1 | HRTIM_TIMxCR_UPDGAT_0 | HRTIM_OR_UPDENSEL)      /*!< Slave timer only - Update done on a rising edge of PLAY1 output 14 signal */
#endif /* PLAY1 */
#define LL_HRTIM_UPDATEGAT_TIM10_OC1_UPDATE      (HRTIM_TIMxCR_UPDGAT_2 | HRTIM_TIMxCR_UPDGAT_1)                           /*!< Slave timer only -  Update done on the update event following a rising edge of TIM10 OC1 signal */
#define LL_HRTIM_UPDATEGAT_TIM11_OC1_UPDATE      (HRTIM_TIMxCR_UPDGAT_2 | HRTIM_TIMxCR_UPDGAT_1 | HRTIM_TIMxCR_UPDGAT_0)   /*!< Slave timer only - Update done on the update event following a rising edge of TIM11 OC1 signal */
#define LL_HRTIM_UPDATEGAT_TIM6_TRGO_UPDATE      (HRTIM_TIMxCR_UPDGAT_3)                                                  /*!< Slave timer only - Update done on the update event following a rising edge of TIM6 TRGO signal */
#if defined(PLAY1)
#define LL_HRTIM_UPDATEGAT_PLAY1_OUT14_UPDATE    (HRTIM_TIMxCR_UPDGAT_2 | HRTIM_TIMxCR_UPDGAT_1 | HRTIM_OR_UPDENSEL)      /*!< Slave timer only - Update done on the update event following a rising edge of PLAY1 output 14 signal signal */
#endif /* PLAY1 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_COMPAREMODE HRTIM compare mode
  * @{
  * @brief Constants defining whether the compare register is behaving in regular mode (compare match issued as soon as
  *        counter equal compare) or in auto-delayed mode.
  */
#define LL_HRTIM_COMPAREMODE_REGULAR          0x00000000U                                       /*!< standard compare mode */
#define LL_HRTIM_COMPAREMODE_DELAY_NOTIMEOUT  (HRTIM_TIMxCR_DELCMP2_0)                          /*!< Compare event generated only if a capture has occurred */
#define LL_HRTIM_COMPAREMODE_DELAY_CMP1       (HRTIM_TIMxCR_DELCMP2_1)                          /*!< Compare event generated if a capture has occurred or after a Compare 1 match (timeout if capture event is missing) */
#define LL_HRTIM_COMPAREMODE_DELAY_CMP3       (HRTIM_TIMxCR_DELCMP2_1 | HRTIM_TIMxCR_DELCMP2_0) /*!< Compare event generated if a capture has occurred or after a Compare 3 match (timeout if capture event is missing) */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_RESETTRIG HRTIM reset trigger
  * @{
  * @brief Constants defining the events that can be selected to trigger the reset of the timer counter.
  */
#define LL_HRTIM_RESETTRIG_NONE           0x00000000U            /*!< No counter reset trigger */
#define LL_HRTIM_RESETTRIG_UPDATE         HRTIM_RSTxR_UPDT       /*!< The timer counter is reset upon update event */
#define LL_HRTIM_RESETTRIG_CMP2           HRTIM_RSTxR_CMP2       /*!< The timer counter is reset upon Timer Compare 2 event */
#define LL_HRTIM_RESETTRIG_CMP4           HRTIM_RSTxR_CMP4       /*!< The timer counter is reset upon Timer Compare 4 event */
#define LL_HRTIM_RESETTRIG_MASTER_PERIOD  HRTIM_RSTxR_MSTPER     /*!< The timer counter is reset upon master timer period event */
#define LL_HRTIM_RESETTRIG_MASTER_CMP1    HRTIM_RSTxR_MSTCMP1    /*!< The timer counter is reset upon master timer Compare 1 event */
#define LL_HRTIM_RESETTRIG_MASTER_CMP2    HRTIM_RSTxR_MSTCMP2    /*!< The timer counter is reset upon master timer Compare 2 event */
#define LL_HRTIM_RESETTRIG_MASTER_CMP3    HRTIM_RSTxR_MSTCMP3    /*!< The timer counter is reset upon master timer Compare 3 event */
#define LL_HRTIM_RESETTRIG_MASTER_CMP4    HRTIM_RSTxR_MSTCMP4    /*!< The timer counter is reset upon master timer Compare 4 event */
#define LL_HRTIM_RESETTRIG_EEVA           HRTIM_RSTxR_EXTEVNTA   /*!< The timer counter is reset upon external event A */
#define LL_HRTIM_RESETTRIG_EEVB           HRTIM_RSTxR_EXTEVNTB   /*!< The timer counter is reset upon external event B */
#define LL_HRTIM_RESETTRIG_EEVC           HRTIM_RSTxR_EXTEVNTC   /*!< The timer counter is reset upon external event C */
#define LL_HRTIM_RESETTRIG_EEVD           HRTIM_RSTxR_EXTEVNTD   /*!< The timer counter is reset upon external event D */
#define LL_HRTIM_RESETTRIG_EEVE           HRTIM_RSTxR_EXTEVNTE   /*!< The timer counter is reset upon external event E */
#define LL_HRTIM_RESETTRIG_EEVF           HRTIM_RSTxR_EXTEVNTF   /*!< The timer counter is reset upon external event F */
#define LL_HRTIM_RESETTRIG_EEVG           HRTIM_RSTxR_EXTEVNTG   /*!< The timer counter is reset upon external event G */
#define LL_HRTIM_RESETTRIG_EEVH           HRTIM_RSTxR_EXTEVNTH   /*!< The timer counter is reset upon external event H */
#define LL_HRTIM_RESETTRIG_EEVI           HRTIM_RSTxR_EXTEVNTI   /*!< The timer counter is reset upon external event I */
#define LL_HRTIM_RESETTRIG_EEVJ           HRTIM_RSTxR_EXTEVNTJ   /*!< The timer counter is reset upon external event J */
/* Events from other timing units that can be used to reset Timer A counter */
#define LL_HRTIM_RESETTRIG_TIMA_TBCMP1    HRTIM_RSTxR_TIMBCMP1   /*!< The timer A counter is reset upon Timer B compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMA_TBCMP2    HRTIM_RSTxR_TIMBCMP2   /*!< The timer A counter is reset upon Timer B compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMA_TBCMP4    HRTIM_RSTxR_TIMBCMP4   /*!< The timer A counter is reset upon Timer B compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMA_TCCMP1    HRTIM_RSTxR_TIMCCMP1   /*!< The timer A counter is reset upon Timer C compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMA_TCCMP2    HRTIM_RSTxR_TIMCCMP2   /*!< The timer A counter is reset upon Timer C compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMA_TCCMP4    HRTIM_RSTxR_TIMCCMP4   /*!< The timer A counter is reset upon Timer C compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMA_TDCMP1    HRTIM_RSTxR_TIMDCMP1   /*!< The timer A counter is reset upon Timer D compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMA_TDCMP2    HRTIM_RSTxR_TIMDCMP2   /*!< The timer A counter is reset upon Timer D compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMA_TDCMP4    HRTIM_RSTxR_TIMDCMP4   /*!< The timer A counter is reset upon Timer D compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMA_TECMP1    HRTIM_RSTxR_TIMECMP1   /*!< The timer A counter is reset upon Timer E compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMA_TECMP2    HRTIM_RSTxR_TIMECMP2   /*!< The timer A counter is reset upon Timer E compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMA_TECMP4    HRTIM_RSTxR_TIMECMP4   /*!< The timer A counter is reset upon Timer E compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMA_TFCMP1    HRTIM_RSTxR_TIMFCMP1   /*!< The timer A counter is reset upon Timer F compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMA_TFCMP2    HRTIM_RSTxR_TIMFCMP2   /*!< The timer A counter is reset upon Timer F compare 2 event */
/* Events from other timing units that can be used to reset Timer B counter */
#define LL_HRTIM_RESETTRIG_TIMB_TACMP1    HRTIM_RSTxR_TIMBCMP1   /*!< The timer B counter is reset upon Timer A compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMB_TACMP2    HRTIM_RSTxR_TIMBCMP2   /*!< The timer B counter is reset upon Timer A compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMB_TACMP4    HRTIM_RSTxR_TIMBCMP4   /*!< The timer B counter is reset upon Timer A compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMB_TCCMP1    HRTIM_RSTxR_TIMCCMP1   /*!< The timer B counter is reset upon Timer C compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMB_TCCMP2    HRTIM_RSTxR_TIMCCMP2   /*!< The timer B counter is reset upon Timer C compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMB_TCCMP4    HRTIM_RSTxR_TIMCCMP4   /*!< The timer B counter is reset upon Timer C compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMB_TDCMP1    HRTIM_RSTxR_TIMDCMP1   /*!< The timer B counter is reset upon Timer D compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMB_TDCMP2    HRTIM_RSTxR_TIMDCMP2   /*!< The timer B counter is reset upon Timer D compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMB_TDCMP4    HRTIM_RSTxR_TIMDCMP4   /*!< The timer B counter is reset upon Timer D compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMB_TECMP1    HRTIM_RSTxR_TIMECMP1   /*!< The timer B counter is reset upon Timer E compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMB_TECMP2    HRTIM_RSTxR_TIMECMP2   /*!< The timer B counter is reset upon Timer E compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMB_TECMP4    HRTIM_RSTxR_TIMECMP4   /*!< The timer B counter is reset upon Timer E compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMB_TFCMP1    HRTIM_RSTxR_TIMFCMP1   /*!< The timer B counter is reset upon Timer F compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMB_TFCMP2    HRTIM_RSTxR_TIMFCMP2   /*!< The timer B counter is reset upon Timer F compare 2 event */
/* Events from other timing units that can be used to reset Timer C counter */
#define LL_HRTIM_RESETTRIG_TIMC_TACMP1    HRTIM_RSTxR_TIMBCMP1   /*!< The timer C counter is reset upon Timer A compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMC_TACMP2    HRTIM_RSTxR_TIMBCMP2   /*!< The timer C counter is reset upon Timer A compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMC_TACMP4    HRTIM_RSTxR_TIMBCMP4   /*!< The timer C counter is reset upon Timer A compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMC_TBCMP1    HRTIM_RSTxR_TIMCCMP1   /*!< The timer C counter is reset upon Timer B compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMC_TBCMP2    HRTIM_RSTxR_TIMCCMP2   /*!< The timer C counter is reset upon Timer B compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMC_TBCMP4    HRTIM_RSTxR_TIMCCMP4   /*!< The timer C counter is reset upon Timer B compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMC_TDCMP1    HRTIM_RSTxR_TIMDCMP1   /*!< The timer C counter is reset upon Timer D compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMC_TDCMP2    HRTIM_RSTxR_TIMDCMP2   /*!< The timer C counter is reset upon Timer D compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMC_TDCMP4    HRTIM_RSTxR_TIMDCMP4   /*!< The timer C counter is reset upon Timer D compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMC_TECMP1    HRTIM_RSTxR_TIMECMP1   /*!< The timer C counter is reset upon Timer E compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMC_TECMP2    HRTIM_RSTxR_TIMECMP2   /*!< The timer C counter is reset upon Timer E compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMC_TECMP4    HRTIM_RSTxR_TIMECMP4   /*!< The timer C counter is reset upon Timer E compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMC_TFCMP1    HRTIM_RSTxR_TIMFCMP1   /*!< The timer C counter is reset upon Timer F compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMC_TFCMP2    HRTIM_RSTxR_TIMFCMP2   /*!< The timer C counter is reset upon Timer F compare 2 event */
/* Events from other timing units that can be used to reset Timer D counter */
#define LL_HRTIM_RESETTRIG_TIMD_TACMP1    HRTIM_RSTxR_TIMBCMP1   /*!< The timer D counter is reset upon Timer A compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMD_TACMP2    HRTIM_RSTxR_TIMBCMP2   /*!< The timer D counter is reset upon Timer A compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMD_TACMP4    HRTIM_RSTxR_TIMBCMP4   /*!< The timer D counter is reset upon Timer A compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMD_TBCMP1    HRTIM_RSTxR_TIMCCMP1   /*!< The timer D counter is reset upon Timer B compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMD_TBCMP2    HRTIM_RSTxR_TIMCCMP2   /*!< The timer D counter is reset upon Timer B compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMD_TBCMP4    HRTIM_RSTxR_TIMCCMP4   /*!< The timer D counter is reset upon Timer B compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMD_TCCMP1    HRTIM_RSTxR_TIMDCMP1   /*!< The timer D counter is reset upon Timer C compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMD_TCCMP2    HRTIM_RSTxR_TIMDCMP2   /*!< The timer D counter is reset upon Timer C compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMD_TCCMP4    HRTIM_RSTxR_TIMDCMP4   /*!< The timer D counter is reset upon Timer C compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMD_TECMP1    HRTIM_RSTxR_TIMECMP1   /*!< The timer D counter is reset upon Timer E compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMD_TECMP2    HRTIM_RSTxR_TIMECMP2   /*!< The timer D counter is reset upon Timer E compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMD_TECMP4    HRTIM_RSTxR_TIMECMP4   /*!< The timer D counter is reset upon Timer E compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMD_TFCMP1    HRTIM_RSTxR_TIMFCMP1   /*!< The timer D counter is reset upon Timer F compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMD_TFCMP2    HRTIM_RSTxR_TIMFCMP2   /*!< The timer D counter is reset upon Timer F compare 2 event */
/* Events from other timing units that can be used to reset Timer E counter */
#define LL_HRTIM_RESETTRIG_TIME_TACMP1    HRTIM_RSTxR_TIMBCMP1   /*!< The timer E counter is reset upon Timer A compare 1 event */
#define LL_HRTIM_RESETTRIG_TIME_TACMP2    HRTIM_RSTxR_TIMBCMP2   /*!< The timer E counter is reset upon Timer A compare 2 event */
#define LL_HRTIM_RESETTRIG_TIME_TACMP4    HRTIM_RSTxR_TIMBCMP4   /*!< The timer E counter is reset upon Timer A compare 4 event */
#define LL_HRTIM_RESETTRIG_TIME_TBCMP1    HRTIM_RSTxR_TIMCCMP1   /*!< The timer E counter is reset upon Timer B compare 1 event */
#define LL_HRTIM_RESETTRIG_TIME_TBCMP2    HRTIM_RSTxR_TIMCCMP2   /*!< The timer E counter is reset upon Timer B compare 2 event */
#define LL_HRTIM_RESETTRIG_TIME_TBCMP4    HRTIM_RSTxR_TIMCCMP4   /*!< The timer E counter is reset upon Timer B compare 4 event */
#define LL_HRTIM_RESETTRIG_TIME_TCCMP1    HRTIM_RSTxR_TIMDCMP1   /*!< The timer E counter is reset upon Timer C compare 1 event */
#define LL_HRTIM_RESETTRIG_TIME_TCCMP2    HRTIM_RSTxR_TIMDCMP2   /*!< The timer E counter is reset upon Timer C compare 2 event */
#define LL_HRTIM_RESETTRIG_TIME_TCCMP4    HRTIM_RSTxR_TIMDCMP4   /*!< The timer E counter is reset upon Timer C compare 4 event */
#define LL_HRTIM_RESETTRIG_TIME_TDCMP1    HRTIM_RSTxR_TIMECMP1   /*!< The timer E counter is reset upon Timer D compare 1 event */
#define LL_HRTIM_RESETTRIG_TIME_TDCMP2    HRTIM_RSTxR_TIMECMP2   /*!< The timer E counter is reset upon Timer D compare 2 event */
#define LL_HRTIM_RESETTRIG_TIME_TDCMP4    HRTIM_RSTxR_TIMECMP4   /*!< The timer E counter is reset upon Timer D compare 4 event */
#define LL_HRTIM_RESETTRIG_TIME_TFCMP1    HRTIM_RSTxR_TIMFCMP1   /*!< The timer E counter is reset upon Timer F compare 1 event */
#define LL_HRTIM_RESETTRIG_TIME_TFCMP2    HRTIM_RSTxR_TIMFCMP2   /*!< The timer E counter is reset upon Timer F compare 2 event */
/* Events from other timing units that can be used to reset Timer F counter */
#define LL_HRTIM_RESETTRIG_TIMF_TACMP1    HRTIM_RSTxR_TIMBCMP1   /*!< The timer F counter is reset upon Timer A compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMF_TACMP2    HRTIM_RSTxR_TIMBCMP2   /*!< The timer F counter is reset upon Timer A compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMF_TACMP4    HRTIM_RSTxR_TIMBCMP4   /*!< The timer F counter is reset upon Timer A compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMF_TBCMP1    HRTIM_RSTxR_TIMCCMP1   /*!< The timer F counter is reset upon Timer B compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMF_TBCMP2    HRTIM_RSTxR_TIMCCMP2   /*!< The timer F counter is reset upon Timer B compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMF_TBCMP4    HRTIM_RSTxR_TIMCCMP4   /*!< The timer F counter is reset upon Timer B compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMF_TCCMP1    HRTIM_RSTxR_TIMDCMP1   /*!< The timer F counter is reset upon Timer C compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMF_TCCMP2    HRTIM_RSTxR_TIMDCMP2   /*!< The timer F counter is reset upon Timer C compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMF_TCCMP4    HRTIM_RSTxR_TIMDCMP4   /*!< The timer F counter is reset upon Timer C compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMF_TDCMP1    HRTIM_RSTxR_TIMECMP1   /*!< The timer F counter is reset upon Timer D compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMF_TDCMP2    HRTIM_RSTxR_TIMECMP2   /*!< The timer F counter is reset upon Timer D compare 2 event */
#define LL_HRTIM_RESETTRIG_TIMF_TDCMP4    HRTIM_RSTxR_TIMECMP4   /*!< The timer F counter is reset upon Timer D compare 4 event */
#define LL_HRTIM_RESETTRIG_TIMF_TECMP1    HRTIM_RSTxR_TIMFCMP1   /*!< The timer F counter is reset upon Timer E compare 1 event */
#define LL_HRTIM_RESETTRIG_TIMF_TECMP2    HRTIM_RSTxR_TIMFCMP2   /*!< The timer F counter is reset upon Timer E compare 2 event */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CAPTURETRIG HRTIM capture trigger
  * @{
  * @brief Constants defining the events that can be selected to trigger the capture of the timing unit counter.
  */
#define LL_HRTIM_CAPTURETRIG_NONE       (uint64_t)0                                        /*!< Capture trigger is disabled */
#define LL_HRTIM_CAPTURETRIG_SW         (uint64_t)HRTIM_CPT1xCR_SWCPT                      /*!< The sw event triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_UPDATE     (uint64_t)HRTIM_CPT1xCR_UPDCPT                     /*!< The update event triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVA       (uint64_t)HRTIM_CPT1xCR_EXEVACPT                   /*!< The external event A triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVB       (uint64_t)HRTIM_CPT1xCR_EXEVBCPT                   /*!< The external event B triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVC       (uint64_t)HRTIM_CPT1xCR_EXEVCCPT                   /*!< The external event C triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVD       (uint64_t)HRTIM_CPT1xCR_EXEVDCPT                   /*!< The external event D triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVE       (uint64_t)HRTIM_CPT1xCR_EXEVECPT                   /*!< The external event E triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVF       (uint64_t)HRTIM_CPT1xCR_EXEVFCPT                   /*!< The external event F triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVG       (uint64_t)HRTIM_CPT1xCR_EXEVGCPT                   /*!< The external event G triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVH       (uint64_t)HRTIM_CPT1xCR_EXEVHCPT                   /*!< The external event H triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVI       (uint64_t)HRTIM_CPT1xCR_EXEVICPT                   /*!< The external event I triggers the Capture */
#define LL_HRTIM_CAPTURETRIG_EEVJ       (uint64_t)HRTIM_CPT1xCR_EXEVJCPT                   /*!< The external event J triggers the Capture */
/* Events from other timing units that can be used to trigger a capture on Timer A */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHB1_SET    (uint64_t)(HRTIM_CPT1xCR_TB1SET) <<32        /*!< Capture is triggered by TB1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHB1_RESET  (uint64_t)(HRTIM_CPT1xCR_TB1RST) <<32        /*!< Capture is triggered by TB1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_TBCMP1      (uint64_t)(HRTIM_CPT1xCR_TBCMP1) <<32        /*!< Capture is triggered by Timer B Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMA_TBCMP2      (uint64_t)(HRTIM_CPT1xCR_TBCMP2) <<32        /*!< Capture is triggered by Timer B Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHC1_SET    (uint64_t)(HRTIM_CPT1xCR_TC1SET) <<32        /*!< Capture is triggered by TC1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHC1_RESET  (uint64_t)(HRTIM_CPT1xCR_TC1RST) <<32        /*!< Capture is triggered by TC1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_TCCMP1      (uint64_t)(HRTIM_CPT1xCR_TCCMP1) <<32        /*!< Capture is triggered by Timer C Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMA_TCCMP2      (uint64_t)(HRTIM_CPT1xCR_TCCMP2) <<32        /*!< Capture is triggered by Timer C Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHD1_SET    (uint64_t)(HRTIM_CPT1xCR_TD1SET) <<32        /*!< Capture is triggered by TD1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHD1_RESET  (uint64_t)(HRTIM_CPT1xCR_TD1RST) <<32        /*!< Capture is triggered by TD1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_TDCMP1      (uint64_t)(HRTIM_CPT1xCR_TDCMP1) <<32        /*!< Capture is triggered by Timer D Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMA_TDCMP2      (uint64_t)(HRTIM_CPT1xCR_TDCMP2) <<32        /*!< Capture is triggered by Timer D Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHE1_SET    (uint64_t)(HRTIM_CPT1xCR_TE1SET) <<32        /*!< Capture is triggered by TE1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHE1_RESET  (uint64_t)(HRTIM_CPT1xCR_TE1RST) <<32        /*!< Capture is triggered by TE1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_TECMP1      (uint64_t)(HRTIM_CPT1xCR_TECMP1) <<32        /*!< Capture is triggered by Timer E Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMA_TECMP2      (uint64_t)(HRTIM_CPT1xCR_TECMP2) <<32        /*!< Capture is triggered by Timer E Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHF1_SET    (uint64_t)(HRTIM_CPT1XCR_TF1SET_REMAP) <<32  /*!< Capture is triggered by TF1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_CHF1_RESET  (uint64_t)(HRTIM_CPT1XCR_TF1RST_REMAP) <<32  /*!< Capture is triggered by TF1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMA_TFCMP1      (uint64_t)(HRTIM_CPT1XCR_TFCMP1_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMA_TFCMP2      (uint64_t)(HRTIM_CPT1XCR_TFCMP2_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 2 */
/* Events from other timing units that can be used to trigger a capture on Timer B */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHA1_SET    (uint64_t)(HRTIM_CPT1xCR_TF1SET) <<32        /*!< Capture is triggered by TA1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHA1_RESET  (uint64_t)(HRTIM_CPT1xCR_TF1RST) <<32        /*!< Capture is triggered by TA1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_TACMP1      (uint64_t)(HRTIM_CPT1xCR_TFCMP1) <<32        /*!< Capture is triggered by Timer A Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMB_TACMP2      (uint64_t)(HRTIM_CPT1xCR_TFCMP2) <<32        /*!< Capture is triggered by Timer A Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHC1_SET    (uint64_t)(HRTIM_CPT1xCR_TC1SET) <<32        /*!< Capture is triggered by TC1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHC1_RESET  (uint64_t)(HRTIM_CPT1xCR_TC1RST) <<32        /*!< Capture is triggered by TC1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_TCCMP1      (uint64_t)(HRTIM_CPT1xCR_TCCMP1) <<32        /*!< Capture is triggered by Timer C Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMB_TCCMP2      (uint64_t)(HRTIM_CPT1xCR_TCCMP2) <<32        /*!< Capture is triggered by Timer C Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHD1_SET    (uint64_t)(HRTIM_CPT1xCR_TD1SET) <<32        /*!< Capture is triggered by TD1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHD1_RESET  (uint64_t)(HRTIM_CPT1xCR_TD1RST) <<32        /*!< Capture is triggered by TD1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_TDCMP1      (uint64_t)(HRTIM_CPT1xCR_TDCMP1) <<32        /*!< Capture is triggered by Timer D Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMB_TDCMP2      (uint64_t)(HRTIM_CPT1xCR_TDCMP2) <<32        /*!< Capture is triggered by Timer D Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHE1_SET    (uint64_t)(HRTIM_CPT1xCR_TE1SET) <<32        /*!< Capture is triggered by TE1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHE1_RESET  (uint64_t)(HRTIM_CPT1xCR_TE1RST) <<32        /*!< Capture is triggered by TE1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_TECMP1      (uint64_t)(HRTIM_CPT1xCR_TECMP1) <<32        /*!< Capture is triggered by Timer E Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMB_TECMP2      (uint64_t)(HRTIM_CPT1xCR_TECMP2) <<32        /*!< Capture is triggered by Timer E Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHF1_SET    (uint64_t)(HRTIM_CPT1XCR_TF1SET_REMAP) <<32  /*!< Capture is triggered by TF1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_CHF1_RESET  (uint64_t)(HRTIM_CPT1XCR_TF1RST_REMAP) <<32  /*!< Capture is triggered by TF1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMB_TFCMP1      (uint64_t)(HRTIM_CPT1XCR_TFCMP1_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMB_TFCMP2      (uint64_t)(HRTIM_CPT1XCR_TFCMP2_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 2 */
/* Events from other timing units that can be used to trigger a capture on Timer C */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHA1_SET    (uint64_t)(HRTIM_CPT1xCR_TF1SET) <<32        /*!< Capture is triggered by TA1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHA1_RESET  (uint64_t)(HRTIM_CPT1xCR_TF1RST) <<32        /*!< Capture is triggered by TA1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_TACMP1      (uint64_t)(HRTIM_CPT1xCR_TFCMP1) <<32        /*!< Capture is triggered by Timer A Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMC_TACMP2      (uint64_t)(HRTIM_CPT1xCR_TFCMP2) <<32        /*!< Capture is triggered by Timer A Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHB1_SET    (uint64_t)(HRTIM_CPT1xCR_TB1SET) <<32        /*!< Capture is triggered by TB1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHB1_RESET  (uint64_t)(HRTIM_CPT1xCR_TB1RST) <<32        /*!< Capture is triggered by TB1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_TBCMP1      (uint64_t)(HRTIM_CPT1xCR_TBCMP1) <<32        /*!< Capture is triggered by Timer B Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMC_TBCMP2      (uint64_t)(HRTIM_CPT1xCR_TBCMP2) <<32        /*!< Capture is triggered by Timer B Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHD1_SET    (uint64_t)(HRTIM_CPT1xCR_TD1SET) <<32        /*!< Capture is triggered by TD1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHD1_RESET  (uint64_t)(HRTIM_CPT1xCR_TD1RST) <<32        /*!< Capture is triggered by TD1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_TDCMP1      (uint64_t)(HRTIM_CPT1xCR_TDCMP1) <<32        /*!< Capture is triggered by Timer D Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMC_TDCMP2      (uint64_t)(HRTIM_CPT1xCR_TDCMP2) <<32        /*!< Capture is triggered by Timer D Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHE1_SET    (uint64_t)(HRTIM_CPT1xCR_TE1SET) <<32        /*!< Capture is triggered by TE1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHE1_RESET  (uint64_t)(HRTIM_CPT1xCR_TE1RST) <<32        /*!< Capture is triggered by TE1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_TECMP1      (uint64_t)(HRTIM_CPT1xCR_TECMP1) <<32        /*!< Capture is triggered by Timer E Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMC_TECMP2      (uint64_t)(HRTIM_CPT1xCR_TECMP2) <<32        /*!< Capture is triggered by Timer E Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHF1_SET    (uint64_t)(HRTIM_CPT1XCR_TF1SET_REMAP) <<32  /*!< Capture is triggered by TF1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_CHF1_RESET  (uint64_t)(HRTIM_CPT1XCR_TF1RST_REMAP) <<32  /*!< Capture is triggered by TF1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMC_TFCMP1      (uint64_t)(HRTIM_CPT1XCR_TFCMP1_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMC_TFCMP2      (uint64_t)(HRTIM_CPT1XCR_TFCMP2_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 2 */
/* Events from other timing units that can be used to trigger a capture on Timer D */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHA1_SET    (uint64_t)(HRTIM_CPT1xCR_TF1SET) <<32        /*!< Capture is triggered by TA1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHA1_RESET  (uint64_t)(HRTIM_CPT1xCR_TF1RST) <<32        /*!< Capture is triggered by TA1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_TACMP1      (uint64_t)(HRTIM_CPT1xCR_TFCMP1) <<32        /*!< Capture is triggered by Timer A Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMD_TACMP2      (uint64_t)(HRTIM_CPT1xCR_TFCMP2) <<32        /*!< Capture is triggered by Timer A Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHB1_SET    (uint64_t)(HRTIM_CPT1xCR_TB1SET) <<32        /*!< Capture is triggered by TB1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHB1_RESET  (uint64_t)(HRTIM_CPT1xCR_TB1RST) <<32        /*!< Capture is triggered by TB1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_TBCMP1      (uint64_t)(HRTIM_CPT1xCR_TBCMP1) <<32        /*!< Capture is triggered by Timer B Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMD_TBCMP2      (uint64_t)(HRTIM_CPT1xCR_TBCMP2) <<32        /*!< Capture is triggered by Timer B Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHC1_SET    (uint64_t)(HRTIM_CPT1xCR_TC1SET) <<32        /*!< Capture is triggered by TC1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHC1_RESET  (uint64_t)(HRTIM_CPT1xCR_TC1RST) <<32        /*!< Capture is triggered by TC1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_TCCMP1      (uint64_t)(HRTIM_CPT1xCR_TCCMP1) <<32        /*!< Capture is triggered by Timer C Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMD_TCCMP2      (uint64_t)(HRTIM_CPT1xCR_TCCMP2) <<32        /*!< Capture is triggered by Timer C Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHE1_SET    (uint64_t)(HRTIM_CPT1xCR_TE1SET) <<32        /*!< Capture is triggered by TF1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHE1_RESET  (uint64_t)(HRTIM_CPT1xCR_TE1RST) <<32        /*!< Capture is triggered by TF1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_TECMP1      (uint64_t)(HRTIM_CPT1xCR_TECMP1) <<32        /*!< Capture is triggered by Timer F Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMD_TECMP2      (uint64_t)(HRTIM_CPT1xCR_TECMP2) <<32        /*!< Capture is triggered by Timer F Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHF1_SET    (uint64_t)(HRTIM_CPT1XCR_TF1SET_REMAP) <<32  /*!< Capture is triggered by TF1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_CHF1_RESET  (uint64_t)(HRTIM_CPT1XCR_TF1RST_REMAP) <<32  /*!< Capture is triggered by TF1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMD_TFCMP1      (uint64_t)(HRTIM_CPT1XCR_TFCMP1_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMD_TFCMP2      (uint64_t)(HRTIM_CPT1XCR_TFCMP2_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 2 */
/* Events from other timing units that can be used to trigger a capture on Timer E */
#define LL_HRTIM_CAPTURETRIG_TIME_CHA1_SET    (uint64_t)(HRTIM_CPT1xCR_TF1SET) <<32        /*!< Capture is triggered by TA1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIME_CHA1_RESET  (uint64_t)(HRTIM_CPT1xCR_TF1RST) <<32        /*!< Capture is triggered by TA1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIME_TACMP1      (uint64_t)(HRTIM_CPT1xCR_TFCMP1) <<32        /*!< Capture is triggered by Timer A Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIME_TACMP2      (uint64_t)(HRTIM_CPT1xCR_TFCMP2) <<32        /*!< Capture is triggered by Timer A Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIME_CHB1_SET    (uint64_t)(HRTIM_CPT1xCR_TB1SET) <<32        /*!< Capture is triggered by TB1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIME_CHB1_RESET  (uint64_t)(HRTIM_CPT1xCR_TB1RST) <<32        /*!< Capture is triggered by TB1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIME_TBCMP1      (uint64_t)(HRTIM_CPT1xCR_TBCMP1) <<32        /*!< Capture is triggered by Timer B Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIME_TBCMP2      (uint64_t)(HRTIM_CPT1xCR_TBCMP2) <<32        /*!< Capture is triggered by Timer B Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIME_CHC1_SET    (uint64_t)(HRTIM_CPT1xCR_TC1SET) <<32        /*!< Capture is triggered by TC1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIME_CHC1_RESET  (uint64_t)(HRTIM_CPT1xCR_TC1RST) <<32        /*!< Capture is triggered by TC1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIME_TCCMP1      (uint64_t)(HRTIM_CPT1xCR_TCCMP1) <<32        /*!< Capture is triggered by Timer C Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIME_TCCMP2      (uint64_t)(HRTIM_CPT1xCR_TCCMP2) <<32        /*!< Capture is triggered by Timer C Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIME_CHD1_SET    (uint64_t)(HRTIM_CPT1xCR_TD1SET) <<32        /*!< Capture is triggered by TD1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIME_CHD1_RESET  (uint64_t)(HRTIM_CPT1xCR_TD1RST) <<32        /*!< Capture is triggered by TD1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIME_TDCMP1      (uint64_t)(HRTIM_CPT1xCR_TDCMP1) <<32        /*!< Capture is triggered by Timer D Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIME_TDCMP2      (uint64_t)(HRTIM_CPT1xCR_TDCMP2) <<32        /*!< Capture is triggered by Timer D Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIME_CHF1_SET    (uint64_t)(HRTIM_CPT1XCR_TF1SET_REMAP) <<32  /*!< Capture is triggered by TF1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIME_CHF1_RESET  (uint64_t)(HRTIM_CPT1XCR_TF1RST_REMAP) <<32  /*!< Capture is triggered by TF1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIME_TFCMP1      (uint64_t)(HRTIM_CPT1XCR_TFCMP1_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIME_TFCMP2      (uint64_t)(HRTIM_CPT1XCR_TFCMP2_REMAP) <<32  /*!< Capture is triggered by Timer F Compare 2 */
/* Events from other timing units that can be used to trigger a capture on Timer F */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHA1_SET    (uint64_t)(HRTIM_CPT1xCR_TF1SET) <<32        /*!< Capture is triggered by TA1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHA1_RESET  (uint64_t)(HRTIM_CPT1xCR_TF1RST) <<32        /*!< Capture is triggered by TA1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_TACMP1      (uint64_t)(HRTIM_CPT1xCR_TFCMP1) <<32        /*!< Capture is triggered by Timer A Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMF_TACMP2      (uint64_t)(HRTIM_CPT1xCR_TFCMP2) <<32        /*!< Capture is triggered by Timer A Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHB1_SET    (uint64_t)(HRTIM_CPT1xCR_TB1SET) <<32        /*!< Capture is triggered by TB1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHB1_RESET  (uint64_t)(HRTIM_CPT1xCR_TB1RST) <<32        /*!< Capture is triggered by TB1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_TBCMP1      (uint64_t)(HRTIM_CPT1xCR_TBCMP1) <<32        /*!< Capture is triggered by Timer B Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMF_TBCMP2      (uint64_t)(HRTIM_CPT1xCR_TBCMP2) <<32        /*!< Capture is triggered by Timer B Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHC1_SET    (uint64_t)(HRTIM_CPT1xCR_TC1SET) <<32        /*!< Capture is triggered by TC1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHC1_RESET  (uint64_t)(HRTIM_CPT1xCR_TC1RST) <<32        /*!< Capture is triggered by TC1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_TCCMP1      (uint64_t)(HRTIM_CPT1xCR_TCCMP1) <<32        /*!< Capture is triggered by Timer A Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMF_TCCMP2      (uint64_t)(HRTIM_CPT1xCR_TCCMP2) <<32        /*!< Capture is triggered by Timer A Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHD1_SET    (uint64_t)(HRTIM_CPT1xCR_TD1SET) <<32        /*!< Capture is triggered by TD1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHD1_RESET  (uint64_t)(HRTIM_CPT1xCR_TD1RST) <<32        /*!< Capture is triggered by TD1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_TDCMP1      (uint64_t)(HRTIM_CPT1xCR_TDCMP1) <<32        /*!< Capture is triggered by Timer D Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMF_TDCMP2      (uint64_t)(HRTIM_CPT1xCR_TDCMP2) <<32        /*!< Capture is triggered by Timer D Compare 2 */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHE1_SET    (uint64_t)(HRTIM_CPT1xCR_TE1SET) <<32        /*!< Capture is triggered by TE1 output inactive to active transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_CHE1_RESET  (uint64_t)(HRTIM_CPT1xCR_TE1RST) <<32        /*!< Capture is triggered by TE1 output active to inactive transition */
#define LL_HRTIM_CAPTURETRIG_TIMF_TECMP1      (uint64_t)(HRTIM_CPT1xCR_TECMP1) <<32        /*!< Capture is triggered by Timer E Compare 1 */
#define LL_HRTIM_CAPTURETRIG_TIMF_TECMP2      (uint64_t)(HRTIM_CPT1xCR_TECMP2) <<32        /*!< Capture is triggered by Timer E Compare 2 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DLYPRT HRTIM delayed protection (DLYPRT) mode
  * @{
  * @brief Constants defining all possible delayed protection modes for a timer (also define the source and outputs on
  *        which the delayed protection schemes are applied).
  */
#define LL_HRTIM_DLYPRT_DELAYOUT1_EEVF  0x00000000U                                                          /*!< Timers A, B, C: Output 1 delayed Idle on external event F */
#define LL_HRTIM_DLYPRT_DELAYOUT2_EEVF  (HRTIM_OUTxR_DLYPRT_0)                                               /*!< Timers A, B, C: Output 2 delayed Idle on external event F */
#define LL_HRTIM_DLYPRT_DELAYBOTH_EEVF  (HRTIM_OUTxR_DLYPRT_1)                                               /*!< Timers A, B, C: Output 1 and output 2 delayed Idle on external Event F */
#define LL_HRTIM_DLYPRT_BALANCED_EEVF   (HRTIM_OUTxR_DLYPRT_1 | HRTIM_OUTxR_DLYPRT_0)                        /*!< Timers A, B, C: Balanced Idle on external event F */
#define LL_HRTIM_DLYPRT_DELAYOUT1_EEVG  (HRTIM_OUTxR_DLYPRT_2)                                               /*!< Timers A, B, C: Output 1 delayed Idle on external event G */
#define LL_HRTIM_DLYPRT_DELAYOUT2_EEVG  (HRTIM_OUTxR_DLYPRT_2 | HRTIM_OUTxR_DLYPRT_0)                        /*!< Timers A, B, C: Output 2 delayed Idle on external event G */
#define LL_HRTIM_DLYPRT_DELAYBOTH_EEVG  (HRTIM_OUTxR_DLYPRT_2 | HRTIM_OUTxR_DLYPRT_1)                        /*!< Timers A, B, C: Output 1 and output2 delayed Idle on external event G */
#define LL_HRTIM_DLYPRT_BALANCED_EEVG   (HRTIM_OUTxR_DLYPRT_2 | HRTIM_OUTxR_DLYPRT_1 | HRTIM_OUTxR_DLYPRT_0) /*!< Timers A, B, C: Balanced Idle on external event G */

#define LL_HRTIM_DLYPRT_DELAYOUT1_EEVH  0x00000000U                                                          /*!< Timers D, E, F: Output 1 delayed Idle on external event H */
#define LL_HRTIM_DLYPRT_DELAYOUT2_EEVH  (HRTIM_OUTxR_DLYPRT_0)                                               /*!< Timers D, E, F: Output 2 delayed Idle on external event H */
#define LL_HRTIM_DLYPRT_DELAYBOTH_EEVH  (HRTIM_OUTxR_DLYPRT_1)                                               /*!< Timers D, E, F: Output 1 and output 2 delayed Idle on external event H */
#define LL_HRTIM_DLYPRT_BALANCED_EEVH   (HRTIM_OUTxR_DLYPRT_1 | HRTIM_OUTxR_DLYPRT_0)                        /*!< Timers D, E, F: Balanced Idle on external event H */
#define LL_HRTIM_DLYPRT_DELAYOUT1_EEVI  (HRTIM_OUTxR_DLYPRT_2)                                               /*!< Timers D, E, F: Output 1 delayed Idle on external event I */
#define LL_HRTIM_DLYPRT_DELAYOUT2_EEVI  (HRTIM_OUTxR_DLYPRT_2 | HRTIM_OUTxR_DLYPRT_0)                        /*!< Timers D, E, F: Output 2 delayed Idle on external event I */
#define LL_HRTIM_DLYPRT_DELAYBOTH_EEVI  (HRTIM_OUTxR_DLYPRT_2 | HRTIM_OUTxR_DLYPRT_1)                        /*!< Timers D, E, F: Output 1 and output2 delayed Idle on external event I */
#define LL_HRTIM_DLYPRT_BALANCED_EEVI   (HRTIM_OUTxR_DLYPRT_2 | HRTIM_OUTxR_DLYPRT_1 | HRTIM_OUTxR_DLYPRT_0) /*!< Timers D, E, F: Balanced Idle on external event I */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_BURSTMODE HRTIM burst mode
  * @{
  * @brief Constants defining how the timer behaves during a burst mode operation.
  */
#define LL_HRTIM_BURSTMODE_MAINTAINCLOCK 0x0000000U         /*!< Timer counter clock is maintained and the timer operates normally */
#define LL_HRTIM_BURSTMODE_RESETCOUNTER  (HRTIM_BMCR_MTBM)  /*!< Timer counter clock is stopped and the counter is reset */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_BURSTDMA HRTIM burst DMA update
  * @{
  * @brief Constants defining the registers that can be written during a burst DMA operation.
  */
#define LL_HRTIM_BURSTDMA_NONE       0x00000000U                 /*!< No register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MCR        (HRTIM_BDMUPR_MCR)          /*!< MCR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MICR       (HRTIM_BDMUPR_MICR)         /*!< MICR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MDIER      (HRTIM_BDMUPR_MDIER)        /*!< MDIER register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MCNT       (HRTIM_BDMUPR_MCNT)         /*!< MCNTR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MPER       (HRTIM_BDMUPR_MPER)         /*!< MPER register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MREP       (HRTIM_BDMUPR_MREP)         /*!< MREPR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MCMP1      (HRTIM_BDMUPR_MCMP1)        /*!< MCMP1R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MCMP2      (HRTIM_BDMUPR_MCMP2)        /*!< MCMP2R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MCMP3      (HRTIM_BDMUPR_MCMP3)        /*!< MCMP3R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_MCMP4      (HRTIM_BDMUPR_MCMP4)        /*!< MCMP4R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCR      (HRTIM_BDTAUPR_TIMACR)      /*!< TIMxCR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMICR     (HRTIM_BDTAUPR_TIMAICR)     /*!< TIMxICR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMDIER    (HRTIM_BDTAUPR_TIMADIER)    /*!< TIMxDIER register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCNT     (HRTIM_BDTAUPR_TIMACNT)     /*!< CNTxCR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMPER     (HRTIM_BDTAUPR_TIMAPER)     /*!< PERxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMREP     (HRTIM_BDTAUPR_TIMAREP)     /*!< REPxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCMP1    (HRTIM_BDTAUPR_TIMACMP1)    /*!< CMP1xR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCMP2    (HRTIM_BDTAUPR_TIMACMP2)    /*!< CMP2xR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCMP3    (HRTIM_BDTAUPR_TIMACMP3)    /*!< CMP3xR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCMP4    (HRTIM_BDTAUPR_TIMACMP4)    /*!< CMP4xR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMDTR     (HRTIM_BDTAUPR_TIMADTR)     /*!< DTxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMSET1R   (HRTIM_BDTAUPR_TIMASET1R)   /*!< SET1R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMRST1R   (HRTIM_BDTAUPR_TIMARST1R)   /*!< RST1R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMSET2R   (HRTIM_BDTAUPR_TIMASET2R)   /*!< SET2R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMRST2R   (HRTIM_BDTAUPR_TIMARST2R)   /*!< RST1R register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMEEFR1   (HRTIM_BDTAUPR_TIMAEEFR1)   /*!< EEFxR1 register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMEEFR2   (HRTIM_BDTAUPR_TIMAEEFR2)   /*!< EEFxR2 register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMRSTR    (HRTIM_BDTAUPR_TIMARSTR)    /*!< RSTxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCHPR    (HRTIM_BDTAUPR_TIMACHPR)    /*!< CHPxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMOUTR    (HRTIM_BDTAUPR_TIMAOUTR)    /*!< OUTxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMFLTR    (HRTIM_BDTAUPR_TIMAFLTR)    /*!< FLTxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCR2     (HRTIM_BDTAUPR_TIMACR2)     /*!< TIMxCR2 register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMEEFR3   (HRTIM_BDTAUPR_TIMAEEFR3)   /*!< TIMxEEFR3 register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMEESELR  (HRTIM_BDTAUPR_TIMAEESELR)    /*!< EESELxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCOTRGR  (HRTIM_BDTAUPR_TIMACOTRGR)    /*!< COTRGxR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCOFER   (HRTIM_BDTAUPR_TIMACOFER)     /*!< COFExR register is updated by Burst DMA accesses */
#define LL_HRTIM_BURSTDMA_TIMCODER   (HRTIM_BDTAUPR_TIMACODER)     /*!< CODExR register is updated by Burst DMA accesses */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CPPSTAT HRTIM current push-pull status
  * @{
  * @brief Constants defining on which output the signal is currently applied in push-pull mode.
  */
#define LL_HRTIM_CPPSTAT_OUT1   0x00000000U              /*!< Signal applied on output 1 and output 2 forced inactive */
#define LL_HRTIM_CPPSTAT_OUT2   (HRTIM_TIMxISR_CPPSTAT)  /*!< Signal applied on output 2 and output 1 forced inactive */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_IPPSTAT HRTIM idle push-pull status
  * @{
  * @brief Constants defining on which output the signal was applied, in push-pull mode balanced fault mode or delayed
  *        idle mode, when the protection was triggered.
  */
#define LL_HRTIM_IPPSTAT_OUT1   0x00000000U                 /*!< Protection occurred when the output 1 was active and output 2 forced inactive */
#define LL_HRTIM_IPPSTAT_OUT2   (HRTIM_TIMxISR_IPPSTAT)     /*!< Protection occurred when the output 2 was active and output 1 forced inactive */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_TIM_EEFLTR HRTIM timer external event filter
  * @{
  * @brief Constants defining the event filtering applied to external events by a timer.
  */
#define LL_HRTIM_NO_FILTERING              0x00000000U                                                                                      /*!< No filtering */
#define LL_HRTIM_BLK_RST_CMP1             (HRTIM_EEFxR1_EEAFLTR_0)                                                                          /*!< Blanking from counter reset/roll-over to Compare 1 */
#define LL_HRTIM_BLK_RST_CMP2             (HRTIM_EEFxR1_EEAFLTR_1)                                                                          /*!< Blanking from counter reset/roll-over to Compare 2 */
#define LL_HRTIM_BLK_RST_CMP3             (HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from counter reset/roll-over to Compare 3 */
#define LL_HRTIM_BLK_RST_CMP4             (HRTIM_EEFxR1_EEAFLTR_2)                                                                          /*!< Blanking from counter reset/roll-over to Compare 4 */
#define LL_HRTIM_BLK_CMP1_RST             (HRTIM_EEFxR1_EEAFLTR_4)                                                                             /*!< Blanking from compare 1 to counter reset/roll-over */
#define LL_HRTIM_BLK_CMP2_RST             (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_0)                                                    /*!< Blanking from compare 2 to counter reset/roll-over */
#define LL_HRTIM_BLK_CMP1_CMP2            (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_1)                                                    /*!< Blanking from compare 1 to compare 2 */
#define LL_HRTIM_BLK_CMP3_CMP4            (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                           /*!< Blanking from compare 3 to compare 4 */
#define LL_HRTIM_BLK_PER_CMP1             (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1)                           /*!< Blanking from Period Event to Compare 1 */
#define LL_HRTIM_BLK_PER_CMP2             (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)  /*!< Blanking from Period Event to Compare 2 */
#define LL_HRTIM_BLK_RST_CMP1_CPPSTAT     (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2)                           /*!< Blanking from counter reset/roll-over to cmp1 when CPPSTAT = 0
                                           and unconditional blanking when CPPSTAT = 1 */
/* Blanking Filter for TIMER A */
#define LL_HRTIM_BLK_TIMA_TBRST_TBCMP1    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR1 source */
#define LL_HRTIM_BLK_TIMA_TBRST_TBCMP4    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR2 source */
#define LL_HRTIM_BLK_TIMA_CHB2            (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR3 source */
#define LL_HRTIM_BLK_TIMA_TCRST_TCCMP1    (HRTIM_EEFxR1_EEAFLTR_3)                                                                           /*!< Blanking from another timing unit: TIMFLTR4 source */
#define LL_HRTIM_BLK_TIMA_TCRST_TCCMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR5 source */
#define LL_HRTIM_BLK_TIMA_TFRST_TFCMP1    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR6 source */
#define LL_HRTIM_BLK_TIMA_TDRST_TDCMP1    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR7 source */
#define LL_HRTIM_BLK_TIMA_TERST_TECMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2)                                                 /*!< Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER B */
#define LL_HRTIM_BLK_TIMB_TARST_TACMP1    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR1 source */
#define LL_HRTIM_BLK_TIMB_TARST_TACMP4    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR2 source */
#define LL_HRTIM_BLK_TIMB_CHA2            (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR3 source */
#define LL_HRTIM_BLK_TIMB_TCRST_TCCMP1    (HRTIM_EEFxR1_EEAFLTR_3)                                                                          /*!< Blanking from another timing unit: TIMFLTR4 source */
#define LL_HRTIM_BLK_TIMB_TCRST_TCCMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR5 source */
#define LL_HRTIM_BLK_TIMB_TFRST_TFCMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR6 source */
#define LL_HRTIM_BLK_TIMB_TDRST_TDCMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR7 source */
#define LL_HRTIM_BLK_TIMB_TERST_TECMP1    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2)                                                 /*!< Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER C */
#define LL_HRTIM_BLK_TIMC_TARST_TACMP2    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR1 source */
#define LL_HRTIM_BLK_TIMC_TBRST_TBCMP1    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR2 source */
#define LL_HRTIM_BLK_TIMC_TBRST_TBCMP4    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR3 source */
#define LL_HRTIM_BLK_TIMC_TFRST_TFCMP1    (HRTIM_EEFxR1_EEAFLTR_3)                                                                          /*!< Blanking from another timing unit: TIMFLTR4 source */
#define LL_HRTIM_BLK_TIMC_TDRST_TDCMP1    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR5 source */
#define LL_HRTIM_BLK_TIMC_TDRST_TDCMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR6 source */
#define LL_HRTIM_BLK_TIMC_CHD2            (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR7 source */
#define LL_HRTIM_BLK_TIMC_TERST_TECMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2)                                                 /*!< Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER D */
#define LL_HRTIM_BLK_TIMD_TARST_TACMP1    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR1 source */
#define LL_HRTIM_BLK_TIMD_TBRST_TBCMP2    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR2 source */
#define LL_HRTIM_BLK_TIMD_TCRST_TCCMP1    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR3 source */
#define LL_HRTIM_BLK_TIMD_TCRST_TCCMP2    (HRTIM_EEFxR1_EEAFLTR_3)                                                                           /*!< Blanking from another timing unit: TIMFLTR4 source */
#define LL_HRTIM_BLK_TIMD_CHC2            (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR5 source */
#define LL_HRTIM_BLK_TIMD_TERST_TECMP1    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR6 source */
#define LL_HRTIM_BLK_TIMD_TERST_TECMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                         /*!< Blanking from another timing unit: TIMFLTR7 source */
#define LL_HRTIM_BLK_TIMD_TFRST_TFCMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2)                                                  /*!< Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER E */
#define LL_HRTIM_BLK_TIME_TARST_TACMP2    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR1 source */
#define LL_HRTIM_BLK_TIME_TBRST_TBCMP1    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR2 source */
#define LL_HRTIM_BLK_TIME_TCRST_TCCMP1    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR3 source */
#define LL_HRTIM_BLK_TIME_TFRST_TFCMP4    (HRTIM_EEFxR1_EEAFLTR_3)                                                                          /*!< Blanking from another timing unit: TIMFLTR4 source */
#define LL_HRTIM_BLK_TIME_CHF2            (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR5 source */
#define LL_HRTIM_BLK_TIME_TDRST_TDCMP1    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR6 source */
#define LL_HRTIM_BLK_TIME_TDRST_TDCMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR7 source */
#define LL_HRTIM_BLK_TIME_CHD2            (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2)                                                 /*!< Blanking from another timing unit: TIMFLTR8 source */
/* Blanking Filter for TIMER F */
#define LL_HRTIM_BLK_TIMF_TARST_TACMP4    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR1 source */
#define LL_HRTIM_BLK_TIMF_TBRST_TBCMP2    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR2 source */
#define LL_HRTIM_BLK_TIMF_TCRST_TCCMP4    (HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR3 source */
#define LL_HRTIM_BLK_TIMF_TDRST_TDCMP2    (HRTIM_EEFxR1_EEAFLTR_3)                                                                          /*!< Blanking from another timing unit: TIMFLTR4 source */
#define LL_HRTIM_BLK_TIMF_TDRST_TDCMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Blanking from another timing unit: TIMFLTR5 source */
#define LL_HRTIM_BLK_TIMF_TERST_TECMP1    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1)                                                 /*!< Blanking from another timing unit: TIMFLTR6 source */
#define LL_HRTIM_BLK_TIMF_TERST_TECMP4    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                        /*!< Blanking from another timing unit: TIMFLTR7 source */
#define LL_HRTIM_BLK_TIMF_CHE2            (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2)                                                 /*!< Blanking from another timing unit: TIMFLTR8 source */

#define LL_HRTIM_WIN_RST_CMP2      (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                               /*!< Windowing from counter reset/roll-over to Compare 2 */
#define LL_HRTIM_WIN_RST_CMP3      (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                               /*!< Windowing from counter reset/roll-over to Compare 3 */
#define LL_HRTIM_WIN_CMP1_RST      (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_2)                                                   /*!< Windowing from counter compare 1 to counter reset/roll-over */
#define LL_HRTIM_WIN_CMP2_RST      (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_0)                          /*!< Windowing from counter compare 2 to counter reset/roll-over */
#define LL_HRTIM_WIN_CMP1_CMP2     (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1)                          /*!< Windowing from counter compare 1 to compare 2 */
#define LL_HRTIM_WIN_CMP3_CMP4     (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_2 | HRTIM_EEFxR1_EEAFLTR_1| HRTIM_EEFxR1_EEAFLTR_0)  /*!< Windowing from counter compare 3 to compare 4 */

/* Windowing Filter for TIMER A */
#define LL_HRTIM_WIN_TIMA_TBRST_TBCMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 |\
                                           HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Windowing from another timing unit: TIMWIN source */
#define LL_HRTIM_WIN_TIMA_TBCMP2_TBRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3)                                                 /*!< Windowing from another timing unit: TIMWIN1 source */
#define LL_HRTIM_WIN_TIMA_TBCMP1_TBRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                         /*!< Windowing from another timing unit: TIMWIN2 source */
/* Windowing Filter for TIMER B */
#define LL_HRTIM_WIN_TIMB_TARST_TACMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 |\
                                           HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Windowing from another timing unit: TIMWIN source */
#define LL_HRTIM_WIN_TIMB_TACMP2_TARST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3)                                                 /*!< Windowing from another timing unit: TIMWIN1 source */
#define LL_HRTIM_WIN_TIMB_TACMP1_TARST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                         /*!< Windowing from another timing unit: TIMWIN2 source */
/* Windowing Filter for TIMER C */
#define LL_HRTIM_WIN_TIMC_TDRST_TDCMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 |\
                                           HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Windowing from another timing unit: TIMWIN source */
#define LL_HRTIM_WIN_TIMC_TDCMP2_TDRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3)                                                 /*!< Windowing from another timing unit: TIMWIN1 source */
#define LL_HRTIM_WIN_TIMC_TDCMP1_TDRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                         /*!< Windowing from another timing unit: TIMWIN2 source */
/* Windowing Filter for TIMER D */
#define LL_HRTIM_WIN_TIMD_TCRST_TCCMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 |\
                                           HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Windowing from another timing unit: TIMWIN source */
#define LL_HRTIM_WIN_TIMD_TCCMP2_TCRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3)                                                 /*!< Windowing from another timing unit: TIMWIN1 source */
#define LL_HRTIM_WIN_TIMD_TCCMP1_TCRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                         /*!< Windowing from another timing unit: TIMWIN2 source */
/* Windowing Filter for TIMER E */
#define LL_HRTIM_WIN_TIME_TFRST_TFCMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 |\
                                           HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Windowing from another timing unit: TIMWIN source */
#define LL_HRTIM_WIN_TIME_TFCMP2_TFRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3)                                                 /*!< Windowing from another timing unit: TIMWIN1 source */
#define LL_HRTIM_WIN_TIME_TFCMP1_TFRST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                         /*!< Windowing from another timing unit: TIMWIN2 source */
/* Windowing Filter for TIMER F */
#define LL_HRTIM_WIN_TIMF_TERST_TECMP2    (HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_2 |\
                                           HRTIM_EEFxR1_EEAFLTR_1 | HRTIM_EEFxR1_EEAFLTR_0)                                                 /*!< Windowing from another timing unit: TIMWIN source */
#define LL_HRTIM_WIN_TIMF_TECMP2_TERST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3)                                                 /*!< Windowing from another timing unit: TIMWIN1 source */
#define LL_HRTIM_WIN_TIMF_TECMP1_TERST    (HRTIM_EEFxR1_EEAFLTR_4 | HRTIM_EEFxR1_EEAFLTR_3 | HRTIM_EEFxR1_EEAFLTR_0)                         /*!< Windowing from another timing unit: TIMWIN2 source */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_TIM_LATCHSTATUS HRTIM timer external event latch status
  * @{
  * @brief Constants defining whether or not the external event is memorized (latched) and generated as soon as the
  *        blanking period is completed or the window ends.
  */
#define LL_HRTIM_EELATCH_DISABLE    0x00000000U              /*!< Event is ignored if it happens during a blank, or passed through during a window */
#define LL_HRTIM_EELATCH_ENABLE     (HRTIM_EEFxR1_EEALTCH)   /*!< Event is latched and delayed till the end of the blanking or windowing period */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DT_PRESCALER HRTIM deadtime prescaler
  * @{
  * @brief Constants defining the prescaler value for the deadtime generator time step (tDTG) relative to the
  *        HR-Timer clock period (tHRTIM).
  */
#define LL_HRTIM_DT_PRESCALER_DIV8    0x00000000U                                                      /*!< tDTG = tHRTIM / 8 */
#define LL_HRTIM_DT_PRESCALER_DIV4    (HRTIM_DTxR_DTPRSC_0)                                            /*!< tDTG = tHRTIM / 4 */
#define LL_HRTIM_DT_PRESCALER_DIV2    (HRTIM_DTxR_DTPRSC_1)                                            /*!< tDTG = tHRTIM / 2 */
#define LL_HRTIM_DT_PRESCALER_DIV1    (HRTIM_DTxR_DTPRSC_1 | HRTIM_DTxR_DTPRSC_0)                       /*!< tDTG = tHRTIM */
#define LL_HRTIM_DT_PRESCALER_MUL2    (HRTIM_DTxR_DTPRSC_2)                                             /*!< tDTG = tHRTIM * 2 */
#define LL_HRTIM_DT_PRESCALER_MUL4    (HRTIM_DTxR_DTPRSC_2 | HRTIM_DTxR_DTPRSC_0)                       /*!< tDTG = tHRTIM * 4 */
#define LL_HRTIM_DT_PRESCALER_MUL8    (HRTIM_DTxR_DTPRSC_2 | HRTIM_DTxR_DTPRSC_1)                       /*!< tDTG = tHRTIM * 8 */
#define LL_HRTIM_DT_PRESCALER_MUL16   (HRTIM_DTxR_DTPRSC_2 | HRTIM_DTxR_DTPRSC_1 | HRTIM_DTxR_DTPRSC_0) /*!< tDTG = tHRTIM * 16 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DT_RISING_SIGN HRTIM deadtime rising sign
  * @{
  * @brief Constants defining whether the deadtime is positive or negative (overlapping signal) on rising edge.
  */
#define LL_HRTIM_DT_RISING_POSITIVE    0x00000000U             /*!< Positive deadtime on rising edge */
#define LL_HRTIM_DT_RISING_NEGATIVE    (HRTIM_DTxR_SDTR)      /*!< Negative deadtime on rising edge */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DT_FALLING_SIGN HRTIM deadtime falling sign
  * @{
  * @brief Constants defining whether the deadtime is positive or negative (overlapping signal) on falling edge.
  */
#define LL_HRTIM_DT_FALLING_POSITIVE    0x00000000U             /*!< Positive deadtime on falling edge */
#define LL_HRTIM_DT_FALLING_NEGATIVE    (HRTIM_DTxR_SDTF)      /*!< Negative deadtime on falling edge */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DT_MODE HRTIM deadtime mode
  * @{
  * @brief Constants defining the deadtime modes.
  */
#define LL_HRTIM_DT_MODE_COMPLEMENTARY         0x00000000U              /*!< Regular deadtime generation (complementary signals) */
#define LL_HRTIM_DT_MODE_INSERTION             (HRTIM_DTxR_DTM_0)        /*!< Deadtime insertion (not Complementary signals) */
#define LL_HRTIM_DT_MODE_INSERTION_AND_DISARM  (HRTIM_DTxR_DTM_1)        /*!< Deadtime insertion and disarm (not Complementary signals) */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CHP_PRESCALER HRTIM chopper mode prescaler
  * @{
  * @brief Constants defining the frequency of the generated high frequency carrier (fCHPFRQ).
  */
#define LL_HRTIM_CHP_PRESCALER_DIV16  0x00000000U                                                                                  /*!< fCHPFRQ = fHRTIM / 16  */
#define LL_HRTIM_CHP_PRESCALER_DIV32  (HRTIM_CHPxR_CARFRQ_0)                                                                       /*!< fCHPFRQ = fHRTIM / 32  */
#define LL_HRTIM_CHP_PRESCALER_DIV48  (HRTIM_CHPxR_CARFRQ_1)                                                                       /*!< fCHPFRQ = fHRTIM / 48  */
#define LL_HRTIM_CHP_PRESCALER_DIV64  (HRTIM_CHPxR_CARFRQ_1 | HRTIM_CHPxR_CARFRQ_0)                                                /*!< fCHPFRQ = fHRTIM / 64  */
#define LL_HRTIM_CHP_PRESCALER_DIV80  (HRTIM_CHPxR_CARFRQ_2)                                                                       /*!< fCHPFRQ = fHRTIM / 80  */
#define LL_HRTIM_CHP_PRESCALER_DIV96  (HRTIM_CHPxR_CARFRQ_2 | HRTIM_CHPxR_CARFRQ_0)                                                /*!< fCHPFRQ = fHRTIM / 96  */
#define LL_HRTIM_CHP_PRESCALER_DIV112 (HRTIM_CHPxR_CARFRQ_2 | HRTIM_CHPxR_CARFRQ_1)                                                /*!< fCHPFRQ = fHRTIM / 112  */
#define LL_HRTIM_CHP_PRESCALER_DIV128 (HRTIM_CHPxR_CARFRQ_2 | HRTIM_CHPxR_CARFRQ_1 | HRTIM_CHPxR_CARFRQ_0)                         /*!< fCHPFRQ = fHRTIM / 128  */
#define LL_HRTIM_CHP_PRESCALER_DIV144 (HRTIM_CHPxR_CARFRQ_3)                                                                       /*!< fCHPFRQ = fHRTIM / 144  */
#define LL_HRTIM_CHP_PRESCALER_DIV160 (HRTIM_CHPxR_CARFRQ_3 | HRTIM_CHPxR_CARFRQ_0)                                                /*!< fCHPFRQ = fHRTIM / 160  */
#define LL_HRTIM_CHP_PRESCALER_DIV176 (HRTIM_CHPxR_CARFRQ_3 | HRTIM_CHPxR_CARFRQ_1)                                                /*!< fCHPFRQ = fHRTIM / 176  */
#define LL_HRTIM_CHP_PRESCALER_DIV192 (HRTIM_CHPxR_CARFRQ_3 | HRTIM_CHPxR_CARFRQ_1 | HRTIM_CHPxR_CARFRQ_0)                         /*!< fCHPFRQ = fHRTIM / 192  */
#define LL_HRTIM_CHP_PRESCALER_DIV208 (HRTIM_CHPxR_CARFRQ_3 | HRTIM_CHPxR_CARFRQ_2)                                                /*!< fCHPFRQ = fHRTIM / 208  */
#define LL_HRTIM_CHP_PRESCALER_DIV224 (HRTIM_CHPxR_CARFRQ_3 | HRTIM_CHPxR_CARFRQ_2 | HRTIM_CHPxR_CARFRQ_0)                         /*!< fCHPFRQ = fHRTIM / 224  */
#define LL_HRTIM_CHP_PRESCALER_DIV240 (HRTIM_CHPxR_CARFRQ_3 | HRTIM_CHPxR_CARFRQ_2 | HRTIM_CHPxR_CARFRQ_1)                         /*!< fCHPFRQ = fHRTIM / 240  */
#define LL_HRTIM_CHP_PRESCALER_DIV256 (HRTIM_CHPxR_CARFRQ_3 | HRTIM_CHPxR_CARFRQ_2 | HRTIM_CHPxR_CARFRQ_1 | HRTIM_CHPxR_CARFRQ_0)  /*!< fCHPFRQ = fHRTIM / 256  */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CHP_DUTYCYCLE HRTIM chopper mode duty cycle
  * @{
  * @brief Constants defining the duty cycle of the generated high frequency carrier. Duty cycle can be adjusted by
  *        1/8 step (from 0/8 up to 7/8).
  */
#define LL_HRTIM_CHP_DUTYCYCLE_0    0x00000000U                                                          /*!< Only 1st pulse is present */
#define LL_HRTIM_CHP_DUTYCYCLE_125  (HRTIM_CHPxR_CARDTY_0)                                               /*!< Duty cycle of the carrier signal is 12.5 % */
#define LL_HRTIM_CHP_DUTYCYCLE_250  (HRTIM_CHPxR_CARDTY_1)                                               /*!< Duty cycle of the carrier signal is 25 % */
#define LL_HRTIM_CHP_DUTYCYCLE_375  (HRTIM_CHPxR_CARDTY_1 | HRTIM_CHPxR_CARDTY_0)                        /*!< Duty cycle of the carrier signal is 37.5 % */
#define LL_HRTIM_CHP_DUTYCYCLE_500  (HRTIM_CHPxR_CARDTY_2)                                               /*!< Duty cycle of the carrier signal is 50 % */
#define LL_HRTIM_CHP_DUTYCYCLE_625  (HRTIM_CHPxR_CARDTY_2 | HRTIM_CHPxR_CARDTY_0)                        /*!< Duty cycle of the carrier signal is 62.5 % */
#define LL_HRTIM_CHP_DUTYCYCLE_750  (HRTIM_CHPxR_CARDTY_2 | HRTIM_CHPxR_CARDTY_1)                        /*!< Duty cycle of the carrier signal is 75 % */
#define LL_HRTIM_CHP_DUTYCYCLE_875  (HRTIM_CHPxR_CARDTY_2 | HRTIM_CHPxR_CARDTY_1 | HRTIM_CHPxR_CARDTY_0) /*!< Duty cycle of the carrier signal is 87.5 % */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CHP_PULSEWIDTH HRTIM chopper mode pulse width
  * @{
  * @brief Constants defining the pulse width of the first pulse of the generated high frequency carrier.
  */
#define LL_HRTIM_CHP_PULSEWIDTH_16   0x00000000U                                                                                  /*!< tSTPW = tHRTIM x 16  */
#define LL_HRTIM_CHP_PULSEWIDTH_32   (HRTIM_CHPxR_STRTPW_0)                                                                       /*!< tSTPW = tHRTIM x 32  */
#define LL_HRTIM_CHP_PULSEWIDTH_48   (HRTIM_CHPxR_STRTPW_1)                                                                       /*!< tSTPW = tHRTIM x 48  */
#define LL_HRTIM_CHP_PULSEWIDTH_64   (HRTIM_CHPxR_STRTPW_1 | HRTIM_CHPxR_STRTPW_0)                                                /*!< tSTPW = tHRTIM x 64  */
#define LL_HRTIM_CHP_PULSEWIDTH_80   (HRTIM_CHPxR_STRTPW_2)                                                                       /*!< tSTPW = tHRTIM x 80  */
#define LL_HRTIM_CHP_PULSEWIDTH_96   (HRTIM_CHPxR_STRTPW_2 | HRTIM_CHPxR_STRTPW_0)                                                /*!< tSTPW = tHRTIM x 96  */
#define LL_HRTIM_CHP_PULSEWIDTH_112  (HRTIM_CHPxR_STRTPW_2 | HRTIM_CHPxR_STRTPW_1)                                                /*!< tSTPW = tHRTIM x 112  */
#define LL_HRTIM_CHP_PULSEWIDTH_128  (HRTIM_CHPxR_STRTPW_2 | HRTIM_CHPxR_STRTPW_1 | HRTIM_CHPxR_STRTPW_0)                         /*!< tSTPW = tHRTIM x 128  */
#define LL_HRTIM_CHP_PULSEWIDTH_144  (HRTIM_CHPxR_STRTPW_3)                                                                       /*!< tSTPW = tHRTIM x 144  */
#define LL_HRTIM_CHP_PULSEWIDTH_160  (HRTIM_CHPxR_STRTPW_3 | HRTIM_CHPxR_STRTPW_0)                                                /*!< tSTPW = tHRTIM x 160  */
#define LL_HRTIM_CHP_PULSEWIDTH_176  (HRTIM_CHPxR_STRTPW_3 | HRTIM_CHPxR_STRTPW_1)                                                /*!< tSTPW = tHRTIM x 176  */
#define LL_HRTIM_CHP_PULSEWIDTH_192  (HRTIM_CHPxR_STRTPW_3 | HRTIM_CHPxR_STRTPW_1 | HRTIM_CHPxR_STRTPW_0)                         /*!< tSTPW = tHRTIM x 192  */
#define LL_HRTIM_CHP_PULSEWIDTH_208  (HRTIM_CHPxR_STRTPW_3 | HRTIM_CHPxR_STRTPW_2)                                                /*!< tSTPW = tHRTIM x 208  */
#define LL_HRTIM_CHP_PULSEWIDTH_224  (HRTIM_CHPxR_STRTPW_3 | HRTIM_CHPxR_STRTPW_2 | HRTIM_CHPxR_STRTPW_0)                         /*!< tSTPW = tHRTIM x 224  */
#define LL_HRTIM_CHP_PULSEWIDTH_240  (HRTIM_CHPxR_STRTPW_3 | HRTIM_CHPxR_STRTPW_2 | HRTIM_CHPxR_STRTPW_1)                         /*!< tSTPW = tHRTIM x 240  */
#define LL_HRTIM_CHP_PULSEWIDTH_256  (HRTIM_CHPxR_STRTPW_3 | HRTIM_CHPxR_STRTPW_2 | HRTIM_CHPxR_STRTPW_1 | HRTIM_CHPxR_STRTPW_0)  /*!< tSTPW = tHRTIM x 256  */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUTPUTSET_INPUT HRTIM output set source
  * @{
  * @brief Constants defining the events that can be selected to configure the set/reset crossbar of a timer output.
  */
#define LL_HRTIM_OUTPUTSET_NONE             0x00000000U                 /*!< Reset the output set crossbar */
#define LL_HRTIM_OUTPUTSET_RESYNC           (HRTIM_SETx1R_RESYNC)       /*!< Timer reset event coming solely from software or SYNC input forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_PERIOD           (HRTIM_SETx1R_PER)          /*!< Timer period event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_CMP1             (HRTIM_SETx1R_CMP1)         /*!< Timer compare 1 event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_CMP2             (HRTIM_SETx1R_CMP2)         /*!< Timer compare 2 event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_CMP3             (HRTIM_SETx1R_CMP3)         /*!< Timer compare 3 event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_CMP4             (HRTIM_SETx1R_CMP4)         /*!< Timer compare 4 event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_MASTER_PERIOD    (HRTIM_SETx1R_MSTPER)       /*!< The master timer period event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_MASTER_CMP1      (HRTIM_SETx1R_MSTCMP1)      /*!< Master Timer compare 1 event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_MASTER_CMP2      (HRTIM_SETx1R_MSTCMP2)      /*!< Master Timer compare 2 event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_MASTER_CMP3      (HRTIM_SETx1R_MSTCMP3)      /*!< Master Timer compare 3 event forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_MASTER_CMP4      (HRTIM_SETx1R_MSTCMP4)      /*!< Master Timer compare 4 event forces the output to its active state */
/* Timer Events mapping for Timer A */
#define LL_HRTIM_OUTPUTSET_TIMA_TBCMP1      (HRTIM_SETx1R_TIMEVNT1)     /*!< Timer event 1 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TBCMP2      (HRTIM_SETx1R_TIMEVNT2)     /*!< Timer event 2 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TCCMP2      (HRTIM_SETx1R_TIMEVNT3)     /*!< Timer event 3 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TCCMP3      (HRTIM_SETx1R_TIMEVNT4)     /*!< Timer event 4 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TDCMP1      (HRTIM_SETx1R_TIMEVNT5)     /*!< Timer event 5 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TDCMP2      (HRTIM_SETx1R_TIMEVNT6)     /*!< Timer event 6 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TECMP3      (HRTIM_SETx1R_TIMEVNT7)     /*!< Timer event 7 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TECMP4      (HRTIM_SETx1R_TIMEVNT8)     /*!< Timer event 8 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMA_TFCMP4      (HRTIM_SETx1R_TIMEVNT9)     /*!< Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer B */
#define LL_HRTIM_OUTPUTSET_TIMB_TACMP1      (HRTIM_SETx1R_TIMEVNT1)     /*!< Timer event 1 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TACMP2      (HRTIM_SETx1R_TIMEVNT2)     /*!< Timer event 2 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TCCMP3      (HRTIM_SETx1R_TIMEVNT3)     /*!< Timer event 3 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TCCMP4      (HRTIM_SETx1R_TIMEVNT4)     /*!< Timer event 4 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TDCMP3      (HRTIM_SETx1R_TIMEVNT5)     /*!< Timer event 5 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TDCMP4      (HRTIM_SETx1R_TIMEVNT6)     /*!< Timer event 6 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TECMP1      (HRTIM_SETx1R_TIMEVNT7)     /*!< Timer event 7 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TECMP2      (HRTIM_SETx1R_TIMEVNT8)     /*!< Timer event 8 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMB_TFCMP3      (HRTIM_SETx1R_TIMEVNT9)     /*!< Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer C */
#define LL_HRTIM_OUTPUTSET_TIMC_TACMP2      (HRTIM_SETx1R_TIMEVNT1)     /*!< Timer event 1 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TACMP3      (HRTIM_SETx1R_TIMEVNT2)     /*!< Timer event 2 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TBCMP2      (HRTIM_SETx1R_TIMEVNT3)     /*!< Timer event 3 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TBCMP3      (HRTIM_SETx1R_TIMEVNT4)     /*!< Timer event 4 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TDCMP2      (HRTIM_SETx1R_TIMEVNT5)     /*!< Timer event 5 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TDCMP4      (HRTIM_SETx1R_TIMEVNT6)     /*!< Timer event 6 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TECMP3      (HRTIM_SETx1R_TIMEVNT7)     /*!< Timer event 7 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TECMP4      (HRTIM_SETx1R_TIMEVNT8)     /*!< Timer event 8 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMC_TFCMP2      (HRTIM_SETx1R_TIMEVNT9)     /*!< Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer D */
#define LL_HRTIM_OUTPUTSET_TIMD_TACMP1      (HRTIM_SETx1R_TIMEVNT1)     /*!< Timer event 1 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TACMP4      (HRTIM_SETx1R_TIMEVNT2)     /*!< Timer event 2 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TBCMP2      (HRTIM_SETx1R_TIMEVNT3)     /*!< Timer event 3 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TBCMP4      (HRTIM_SETx1R_TIMEVNT4)     /*!< Timer event 4 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TCCMP4      (HRTIM_SETx1R_TIMEVNT5)     /*!< Timer event 5 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TECMP1      (HRTIM_SETx1R_TIMEVNT6)     /*!< Timer event 6 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TECMP4      (HRTIM_SETx1R_TIMEVNT7)     /*!< Timer event 7 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TFCMP1      (HRTIM_SETx1R_TIMEVNT8)     /*!< Timer event 8 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMD_TFCMP3      (HRTIM_SETx1R_TIMEVNT9)     /*!< Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer E */
#define LL_HRTIM_OUTPUTSET_TIME_TACMP4      (HRTIM_SETx1R_TIMEVNT1)     /*!< Timer event 1 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TBCMP3      (HRTIM_SETx1R_TIMEVNT2)     /*!< Timer event 2 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TBCMP4      (HRTIM_SETx1R_TIMEVNT3)     /*!< Timer event 3 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TCCMP1      (HRTIM_SETx1R_TIMEVNT4)     /*!< Timer event 4 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TCCMP2      (HRTIM_SETx1R_TIMEVNT5)     /*!< Timer event 5 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TDCMP1      (HRTIM_SETx1R_TIMEVNT6)     /*!< Timer event 6 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TDCMP2      (HRTIM_SETx1R_TIMEVNT7)     /*!< Timer event 7 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TFCMP3      (HRTIM_SETx1R_TIMEVNT8)     /*!< Timer event 8 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIME_TFCMP4      (HRTIM_SETx1R_TIMEVNT9)     /*!< Timer event 9 forces the output to its active state */
/* Timer Events mapping for Timer F _*/
#define LL_HRTIM_OUTPUTSET_TIMF_TACMP3      (HRTIM_SETx1R_TIMEVNT1)     /*!< Timer event 1 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TBCMP1      (HRTIM_SETx1R_TIMEVNT2)     /*!< Timer event 2 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TBCMP4      (HRTIM_SETx1R_TIMEVNT3)     /*!< Timer event 3 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TCCMP1      (HRTIM_SETx1R_TIMEVNT4)     /*!< Timer event 4 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TCCMP4      (HRTIM_SETx1R_TIMEVNT5)     /*!< Timer event 5 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TDCMP3      (HRTIM_SETx1R_TIMEVNT6)     /*!< Timer event 6 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TDCMP4      (HRTIM_SETx1R_TIMEVNT7)     /*!< Timer event 7 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TECMP2      (HRTIM_SETx1R_TIMEVNT8)     /*!< Timer event 8 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_TIMF_TECMP3      (HRTIM_SETx1R_TIMEVNT9)     /*!< Timer event 9 forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVA             (HRTIM_SETx1R_EXTEVNTA)     /*!< External event A forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVB             (HRTIM_SETx1R_EXTEVNTB)     /*!< External event B forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVC             (HRTIM_SETx1R_EXTEVNTC)     /*!< External event C forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVD             (HRTIM_SETx1R_EXTEVNTD)     /*!< External event D forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVE             (HRTIM_SETx1R_EXTEVNTE)     /*!< External event E forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVF             (HRTIM_SETx1R_EXTEVNTF)     /*!< External event F forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVG             (HRTIM_SETx1R_EXTEVNTG)     /*!< External event G forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVH             (HRTIM_SETx1R_EXTEVNTH)     /*!< External event H forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVI             (HRTIM_SETx1R_EXTEVNTI)     /*!< External event I forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_EEVJ             (HRTIM_SETx1R_EXTEVNTJ)  /*!< External event J forces the output to its active state */
#define LL_HRTIM_OUTPUTSET_UPDATE           (HRTIM_SETx1R_UPDATE)       /*!< Timer register update event forces the output to its active state */
/**
  * @}
  */

/** @defgroup HRTIM_Output_Reset_Source  HRTIM output reset source
  * @{
  * @brief Constants defining the events that can be selected to configure the
  *        set crossbar of a timer output.
  */
#define LL_HRTIM_OUTPUTRESET_NONE            0x00000000U                  /*!< Reset the output reset crossbar */
#define LL_HRTIM_OUTPUTRESET_RESYNC          (HRTIM_RSTx1R_RESYNC)        /*!< Timer reset event coming solely from software or SYNC input forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_PERIOD          (HRTIM_RSTx1R_PER)           /*!< Timer period event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_CMP1            (HRTIM_RSTx1R_CMP1)          /*!< Timer compare 1 event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_CMP2            (HRTIM_RSTx1R_CMP2)          /*!< Timer compare 2 event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_CMP3            (HRTIM_RSTx1R_CMP3)          /*!< Timer compare 3 event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_CMP4            (HRTIM_RSTx1R_CMP4)          /*!< Timer compare 4 event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_MASTER_PERIOD   (HRTIM_RSTx1R_MSTPER)        /*!< The master timer period event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_MASTER_CMP1     (HRTIM_RSTx1R_MSTCMP1)       /*!< Master Timer compare 1 event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_MASTER_CMP2     (HRTIM_RSTx1R_MSTCMP2)       /*!< Master Timer compare 2 event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_MASTER_CMP3     (HRTIM_RSTx1R_MSTCMP3)       /*!< Master Timer compare 3 event forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_MASTER_CMP4     (HRTIM_RSTx1R_MSTCMP4)       /*!< Master Timer compare 4 event forces the output to its inactive state */
/* Timer Events mapping for Timer A */
#define LL_HRTIM_OUTPUTRESET_TIMA_TBCMP1    (HRTIM_RSTx1R_TIMEVNT1)       /*!< Timer event 1 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TBCMP2    (HRTIM_RSTx1R_TIMEVNT2)       /*!< Timer event 2 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TCCMP2    (HRTIM_RSTx1R_TIMEVNT3)       /*!< Timer event 3 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TCCMP3    (HRTIM_RSTx1R_TIMEVNT4)       /*!< Timer event 4 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TDCMP1    (HRTIM_RSTx1R_TIMEVNT5)       /*!< Timer event 5 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TDCMP2    (HRTIM_RSTx1R_TIMEVNT6)       /*!< Timer event 6 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TECMP3    (HRTIM_RSTx1R_TIMEVNT7)       /*!< Timer event 7 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TECMP4    (HRTIM_RSTx1R_TIMEVNT8)       /*!< Timer event 8 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMA_TFCMP4    (HRTIM_RSTx1R_TIMEVNT9)       /*!< Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer B */
#define LL_HRTIM_OUTPUTRESET_TIMB_TACMP1    (HRTIM_RSTx1R_TIMEVNT1)       /*!< Timer event 1 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TACMP2    (HRTIM_RSTx1R_TIMEVNT2)       /*!< Timer event 2 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TCCMP3    (HRTIM_RSTx1R_TIMEVNT3)       /*!< Timer event 3 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TCCMP4    (HRTIM_RSTx1R_TIMEVNT4)       /*!< Timer event 4 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TDCMP3    (HRTIM_RSTx1R_TIMEVNT5)       /*!< Timer event 5 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TDCMP4    (HRTIM_RSTx1R_TIMEVNT6)       /*!< Timer event 6 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TECMP1    (HRTIM_RSTx1R_TIMEVNT7)       /*!< Timer event 7 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TECMP2    (HRTIM_RSTx1R_TIMEVNT8)       /*!< Timer event 8 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMB_TFCMP3    (HRTIM_RSTx1R_TIMEVNT9)       /*!< Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer C */
#define LL_HRTIM_OUTPUTRESET_TIMC_TACMP2    (HRTIM_RSTx1R_TIMEVNT1)       /*!< Timer event 1 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TACMP3    (HRTIM_RSTx1R_TIMEVNT2)       /*!< Timer event 2 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TBCMP2    (HRTIM_RSTx1R_TIMEVNT3)       /*!< Timer event 3 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TBCMP3    (HRTIM_RSTx1R_TIMEVNT4)       /*!< Timer event 4 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TDCMP2    (HRTIM_RSTx1R_TIMEVNT5)       /*!< Timer event 5 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TDCMP4    (HRTIM_RSTx1R_TIMEVNT6)       /*!< Timer event 6 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TECMP3    (HRTIM_RSTx1R_TIMEVNT7)       /*!< Timer event 7 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TECMP4    (HRTIM_RSTx1R_TIMEVNT8)       /*!< Timer event 8 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMC_TFCMP2    (HRTIM_RSTx1R_TIMEVNT9)       /*!< Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer D */
#define LL_HRTIM_OUTPUTRESET_TIMD_TACMP1    (HRTIM_RSTx1R_TIMEVNT1)       /*!< Timer event 1 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TACMP4    (HRTIM_RSTx1R_TIMEVNT2)       /*!< Timer event 2 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TBCMP2    (HRTIM_RSTx1R_TIMEVNT3)       /*!< Timer event 3 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TBCMP4    (HRTIM_RSTx1R_TIMEVNT4)       /*!< Timer event 4 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TCCMP4    (HRTIM_RSTx1R_TIMEVNT5)       /*!< Timer event 5 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TECMP1    (HRTIM_RSTx1R_TIMEVNT6)       /*!< Timer event 6 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TECMP4    (HRTIM_RSTx1R_TIMEVNT7)       /*!< Timer event 7 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TFCMP1    (HRTIM_RSTx1R_TIMEVNT8)       /*!< Timer event 8 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMD_TFCMP3    (HRTIM_RSTx1R_TIMEVNT9)       /*!< Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer E */
#define LL_HRTIM_OUTPUTRESET_TIME_TACMP4    (HRTIM_RSTx1R_TIMEVNT1)       /*!< Timer event 1 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TBCMP3    (HRTIM_RSTx1R_TIMEVNT2)       /*!< Timer event 2 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TBCMP4    (HRTIM_RSTx1R_TIMEVNT3)       /*!< Timer event 3 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TCCMP1    (HRTIM_RSTx1R_TIMEVNT4)       /*!< Timer event 4 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TCCMP2    (HRTIM_RSTx1R_TIMEVNT5)       /*!< Timer event 5 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TDCMP1    (HRTIM_RSTx1R_TIMEVNT6)       /*!< Timer event 6 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TDCMP2    (HRTIM_RSTx1R_TIMEVNT7)       /*!< Timer event 7 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TFCMP3    (HRTIM_RSTx1R_TIMEVNT8)       /*!< Timer event 8 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIME_TFCMP4    (HRTIM_RSTx1R_TIMEVNT9)       /*!< Timer event 9 forces the output to its inactive state */
/* Timer Events mapping for Timer F */
#define LL_HRTIM_OUTPUTRESET_TIMF_TACMP3    (HRTIM_RSTx1R_TIMEVNT1)       /*!< Timer event 1 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TBCMP1    (HRTIM_RSTx1R_TIMEVNT2)       /*!< Timer event 2 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TBCMP4    (HRTIM_RSTx1R_TIMEVNT3)       /*!< Timer event 3 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TCCMP1    (HRTIM_RSTx1R_TIMEVNT4)       /*!< Timer event 4 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TCCMP4    (HRTIM_RSTx1R_TIMEVNT5)       /*!< Timer event 5 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TDCMP3    (HRTIM_RSTx1R_TIMEVNT6)       /*!< Timer event 6 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TDCMP4    (HRTIM_RSTx1R_TIMEVNT7)       /*!< Timer event 7 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TECMP2    (HRTIM_RSTx1R_TIMEVNT8)       /*!< Timer event 8 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_TIMF_TECMP3    (HRTIM_RSTx1R_TIMEVNT9)       /*!< Timer event 9 forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVA           (HRTIM_RSTx1R_EXTEVNTA)     /*!< External event A forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVB           (HRTIM_RSTx1R_EXTEVNTB)     /*!< External event B forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVC           (HRTIM_RSTx1R_EXTEVNTC)     /*!< External event C forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVD           (HRTIM_RSTx1R_EXTEVNTD)     /*!< External event D forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVE           (HRTIM_RSTx1R_EXTEVNTE)     /*!< External event E forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVF           (HRTIM_RSTx1R_EXTEVNTF)     /*!< External event F forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVG           (HRTIM_RSTx1R_EXTEVNTG)     /*!< External event G forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVH           (HRTIM_RSTx1R_EXTEVNTH)     /*!< External event H forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVI           (HRTIM_RSTx1R_EXTEVNTI)     /*!< External event I forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_EEVJ           (HRTIM_RSTx1R_EXTEVNTJ)  /*!< External event J forces the output to its inactive state */
#define LL_HRTIM_OUTPUTRESET_UPDATE         (HRTIM_RSTx1R_UPDATE)         /*!< Timer register update event forces the output to its inactive state */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUT_POLARITY HRTIM output_polarity
  * @{
  * @brief Constants defining the polarity of a timer output.
  */
#define LL_HRTIM_OUT_POSITIVE_POLARITY    0x00000000U              /*!< Output is active HIGH */
#define LL_HRTIM_OUT_NEGATIVE_POLARITY    (HRTIM_OUTxR_POL1)       /*!< Output is active LOW */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUT_IDLEMODE HRTIM output idle mode
  * @{
  * @brief Constants defining whether or not the timer output transition to its IDLE state when burst mode is entered.
  */
#define LL_HRTIM_OUT_NO_IDLE             0x00000000U              /*!< The output is not affected by the burst mode operation */
#define LL_HRTIM_OUT_IDLE_WHEN_BURST     (HRTIM_OUTxR_IDLEM1)     /*!< The output is in idle state when requested by the burst mode controller */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_INTLVD_MODE HRTIM interleaved mode
  * @{
  * @brief Constants defining the interleaved mode of an HRTIM Timer instance.
  */
#define LL_HRTIM_INTERLEAVED_MODE_DISABLE    0x00000000U         /*!< HRTIM interleaved Mode is disabled */
#define LL_HRTIM_INTERLEAVED_MODE_DUAL       HRTIM_MCR_HALF      /*!< HRTIM interleaved Mode is Dual */
#define LL_HRTIM_INTERLEAVED_MODE_TRIPLE     HRTIM_MCR_INTLVD_0  /*!< HRTIM interleaved Mode is Triple */
#define LL_HRTIM_INTERLEAVED_MODE_QUAD       HRTIM_MCR_INTLVD_1  /*!< HRTIM interleaved Mode is Quad */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUT_IDLELEVEL HRTIM output idle level
  * @{
  * @brief Constants defining the output level when output is in IDLE state.
  */
#define LL_HRTIM_OUT_IDLELEVEL_INACTIVE   0x00000000U            /*!< Output at inactive level when in IDLE state */
#define LL_HRTIM_OUT_IDLELEVEL_ACTIVE     (HRTIM_OUTxR_IDLES1)   /*!< Output at active level when in IDLE state */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUT_FAULTSTATE HRTIM output fault state
  * @{
  * @brief Constants defining the output level when output is in FAULT state.
  */
#define LL_HRTIM_OUT_FAULTSTATE_NONE 0x00000000U                                         /*!< The output is not affected by the fault input */
#define LL_HRTIM_OUT_FAULTSTATE_ACTIVE    (HRTIM_OUTxR_FAULT1_0)                         /*!< Output at active level when in FAULT state */
#define LL_HRTIM_OUT_FAULTSTATE_INACTIVE  (HRTIM_OUTxR_FAULT1_1)                         /*!< Output at inactive level when in FAULT state */
#define LL_HRTIM_OUT_FAULTSTATE_HIGHZ     (HRTIM_OUTxR_FAULT1_1 | HRTIM_OUTxR_FAULT1_0)  /*!< Output is tri-stated when in FAULT state */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUT_CHOPPERMODE HRTIM output chopper mode
  * @{
  * @brief Constants defining whether or not chopper mode is enabled for a timer output.
  */
#define LL_HRTIM_OUT_CHOPPERMODE_DISABLE   0x00000000U              /*!< Output signal is not altered  */
#define LL_HRTIM_OUT_CHOPPERMODE_ENABLE    (HRTIM_OUTxR_CHP1)       /*!< Output signal is chopped by a carrier signal  */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_OUT_BM_ENTRYMODE HRTIM output burst mode entry mode
  * @{
  * @brief Constants defining the idle state entry mode during a burst mode operation. It is possible to delay the
  *        burst mode entry and force the output to an inactive state during a programmable period before the output
  *        takes its idle state.
  */
#define LL_HRTIM_OUT_BM_ENTRYMODE_REGULAR   0x00000000U              /*!< The programmed Idle state is applied immediately to the Output */
#define LL_HRTIM_OUT_BM_ENTRYMODE_DELAYED   (HRTIM_OUTxR_DIDL1)     /*!< Deadtime is inserted on output before entering the idle mode */
/**
  * @}
  */
/** @defgroup HRTIM_LL_EC_OUT_LEVEL HRTIM output level
  * @{
  * @brief Constants defining the level of a timer output.
  */
#define LL_HRTIM_OUT_LEVEL_INACTIVE   0x00000000U            /*!< Corresponds to a logic level 0 for a positive polarity (High) and to a logic level 1 for a negative polarity (Low) */
#define LL_HRTIM_OUT_LEVEL_ACTIVE     0x00000001U            /*!< Corresponds to a logic level 1 for a positive polarity (High) and to a logic level 0 for a negative polarity (Low) */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_DIGITAL_FILTER HRTIM digital filter
  * @{
  * @brief Constants defining the sampling frequency (fSAMPLING) for an external event or a fault input and the length
  *        (N) of the applied digital filter.
  */
#define LL_HRTIM_FDIV1          0x00000000U                                                                           /*!< Filter disabled */
#define LL_HRTIM_FDIV1_N2       (HRTIM_EECR3_EE6F_0)                                                                  /*!< fSAMPLING = fHRTIM, N=2 */
#define LL_HRTIM_FDIV1_N4       (HRTIM_EECR3_EE6F_1)                                                                  /*!< fSAMPLING = fHRTIM, N=4 */
#define LL_HRTIM_FDIV1_N8       (HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING = fHRTIM, N=8 */
#define LL_HRTIM_FDIV2_N6       (HRTIM_EECR3_EE6F_2)                                                                  /*!< fSAMPLING = fEEVS/2 or fFLTS/2, N=6 */
#define LL_HRTIM_FDIV2_N8       (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING = fEEVS/2 or fFLTS/2, N=8 */
#define LL_HRTIM_FDIV4_N6       (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_1)                                             /*!< fSAMPLING = fEEVS/4 or fFLTS/4, N=6 */
#define LL_HRTIM_FDIV4_N8       (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                        /*!< fSAMPLING = fEEVS/4 or fFLTS/4, N=8 */
#define LL_HRTIM_FDIV8_N6       (HRTIM_EECR3_EE6F_3)                                                                  /*!< fSAMPLING = fEEVS/8 or fFLTS/8, N=6 */
#define LL_HRTIM_FDIV8_N8       (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING = fEEVS/8 or fFLTS/8, N=8 */
#define LL_HRTIM_FDIV16_N5      (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_1)                                             /*!< fSAMPLING = fEEVS/16 or fFLTS/16, N=5 */
#define LL_HRTIM_FDIV16_N6      (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                        /*!< fSAMPLING = fEEVS/16 or fFLTS/16, N=6 */
#define LL_HRTIM_FDIV16_N8      (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2)                                             /*!< fSAMPLING = fEEVS/16 or fFLTS/16, N=8 */
#define LL_HRTIM_FDIV32_N5      (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_0)                       /*!< fSAMPLING = fEEVS/32 or fFLTS/32, N=5 */
#define LL_HRTIM_FDIV32_N6      (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_1)                       /*!< fSAMPLING = fEEVS/32 or fFLTS/32, N=6 */
#define LL_HRTIM_FDIV32_N8      (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)  /*!< fSAMPLING = fEEVS/32 or fFLTS/32, N=8 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EE_SRC HRTIM external event source
  * @{
  * @brief Constants defining available sources associated to external events.
  */
#define LL_HRTIM_EEV1SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 1 */
#define LL_HRTIM_EEV1SRC_COMP2       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 1 */
#define LL_HRTIM_EEV1SRC_TIM1_TRGO   (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 1 */
#define LL_HRTIM_EEV1SRC_ADC1_AWD1   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 1 */
#if defined(PLAY1)
#define LL_HRTIM_EEV1SRC_PLAY1_OUT0  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 1 */
#endif /* PLAY1 */
#define LL_HRTIM_EEV1SRC_TIM1_BKIN2  (HRTIM_EEV_SRC_2 | HRTIM_EECR1_EE1SRC_0)       /*!< External event source 6 for External Event 1 */

#define LL_HRTIM_EEV2SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 2 */
#define LL_HRTIM_EEV2SRC_COMP4       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 2 */
#define LL_HRTIM_EEV2SRC_TIM2_TRGO   (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 2 */
#define LL_HRTIM_EEV2SRC_ADC1_AWD2   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 2 */
#if defined(PLAY1)
#define LL_HRTIM_EEV2SRC_PLAY1_OUT1  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 2 */
#endif /* PLAY1 */
#define LL_HRTIM_EEV2SRC_TIM8_BKIN2  (HRTIM_EEV_SRC_2 | HRTIM_EECR1_EE1SRC_0)       /*!< External event source 6 for External Event 2 */

#define LL_HRTIM_EEV3SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 3 */
#define LL_HRTIM_EEV3SRC_COMP6       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 3 */
#define LL_HRTIM_EEV3SRC_TIM3_TRGO   (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 3 */
#define LL_HRTIM_EEV3SRC_ADC1_AWD3   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 3 */
#if defined(PLAY1)
#define LL_HRTIM_EEV3SRC_PLAY1_OUT2  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 3 */
#endif /* PLAY1 */
#if defined(TIM20)
#define LL_HRTIM_EEV3SRC_TIM20_BKIN2 (HRTIM_EEV_SRC_2 | HRTIM_EECR1_EE1SRC_0)       /*!< External event source 6 for External Event 3 */
#endif /* TIM20 */

#define LL_HRTIM_EEV4SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 4 */
#define LL_HRTIM_EEV4SRC_COMP1       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 4 */
#define LL_HRTIM_EEV4SRC_COMP5       (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 4 */
#define LL_HRTIM_EEV4SRC_ADC2_AWD1   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 4 */
#if defined(PLAY1)
#define LL_HRTIM_EEV4SRC_PLAY1_OUT3  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 4 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV5SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 5 */
#define LL_HRTIM_EEV5SRC_COMP3       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 5 */
#define LL_HRTIM_EEV5SRC_COMP7       (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 5 */
#define LL_HRTIM_EEV5SRC_ADC2_AWD2   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 5 */
#if defined(PLAY1)
#define LL_HRTIM_EEV5SRC_PLAY1_OUT4  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 5 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV6SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 6 */
#define LL_HRTIM_EEV6SRC_COMP2       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 6 */
#define LL_HRTIM_EEV6SRC_COMP1       (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 6 */
#define LL_HRTIM_EEV6SRC_ADC2_AWD3   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 6 */
#if defined(PLAY1)
#define LL_HRTIM_EEV6SRC_PLAY1_OUT5  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 6 */
#endif /* PLAY1 */
#define LL_HRTIM_EEV6SRC_TIM1_BKIN1  (HRTIM_EEV_SRC_2 | HRTIM_EECR1_EE1SRC_0)       /*!< External event source 6 for External Event 6 */

#define LL_HRTIM_EEV7SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 7 */
#define LL_HRTIM_EEV7SRC_COMP4       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 7 */
#define LL_HRTIM_EEV7SRC_COMP7       (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 7 */
#if defined(ADC3)
#define LL_HRTIM_EEV7SRC_ADC3_AWD1   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 7 */
#endif /* ACD3 */
#if defined(PLAY1)
#define LL_HRTIM_EEV7SRC_PLAY1_OUT6  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 7 */
#endif /* PLAY1 */
#define LL_HRTIM_EEV7SRC_TIM8_BKIN1  (HRTIM_EEV_SRC_2 | HRTIM_EECR1_EE1SRC_0)       /*!< External event source 6 for External Event 7 */

#define LL_HRTIM_EEV8SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 8 */
#define LL_HRTIM_EEV8SRC_COMP6       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 8 */
#define LL_HRTIM_EEV8SRC_COMP3       (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 8 */
#if defined(ADC3)
#define LL_HRTIM_EEV8SRC_ADC3_AWD2   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 8 */
#endif /* ADC3 */
#if defined(PLAY1)
#define LL_HRTIM_EEV8SRC_PLAY1_OUT7  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 8 */
#endif /* PLAY1 */
#if defined(TIM20)
#define LL_HRTIM_EEV8SRC_TIM20_BKIN1 (HRTIM_EEV_SRC_2 | HRTIM_EECR1_EE1SRC_0)       /*!< External event source 6 for External Event 8 */
#endif /* TIM20 */

#define LL_HRTIM_EEV9SRC_GPIO        0x00000000U                                    /*!< External event source 1 for External Event 9 */
#define LL_HRTIM_EEV9SRC_COMP5       (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2 for External Event 9 */
#define LL_HRTIM_EEV9SRC_COMP8       (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3 for External Event 9 */
#define LL_HRTIM_EEV9SRC_COMP4       (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4 for External Event 9 */
#if defined(PLAY1)
#define LL_HRTIM_EEV9SRC_PLAY1_OUT8  (HRTIM_EEV_SRC_2)                              /*!< External event source 5 for External Event 9 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV10SRC_GPIO        0x00000000U                                   /*!< External event source 1 for External Event 10 */
#define LL_HRTIM_EEV10SRC_COMP7       (HRTIM_EECR1_EE1SRC_0)                        /*!< External event source 2 for External Event 10 */
#define LL_HRTIM_EEV10SRC_TIM6_TRGO   (HRTIM_EECR1_EE1SRC_1)                        /*!< External event source 3 for External Event 10 */
#if defined(ADC3)
#define LL_HRTIM_EEV10SRC_ADC3_AWD3   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0) /*!< External event source 4 for External Event 10 */
#endif /* ADC3 */
#if defined(PLAY1)
#define LL_HRTIM_EEV10SRC_PLAY1_OUT9  (HRTIM_EEV_SRC_2)                             /*!< External event source 5 for External Event 10 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV11SRC_GPIO        0x00000000U                                   /*!< External event source 1 for External Event 11 */
#define LL_HRTIM_EEV11SRC_COMP7       (HRTIM_EECR1_EE1SRC_0)                        /*!< External event source 2 for External Event 11 */
#define LL_HRTIM_EEV11SRC_TIM9_TRGO   (HRTIM_EECR1_EE1SRC_1)                        /*!< External event source 3 for External Event 11 */
#define LL_HRTIM_EEV11SRC_ADC2_AWD1   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0) /*!< External event source 4 for External Event 11 */
#if defined(PLAY1)
#define LL_HRTIM_EEV11SRC_PLAY1_OUT10 (HRTIM_EEV_SRC_2)                             /*!< External event source 5 for External Event 11 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV12SRC_GPIO        0x00000000U                                   /*!< External event source 1 for External Event 12 */
#define LL_HRTIM_EEV12SRC_COMP8       (HRTIM_EECR1_EE1SRC_0)                        /*!< External event source 2 for External Event 12 */
#define LL_HRTIM_EEV12SRC_TIM12_TRGO  (HRTIM_EECR1_EE1SRC_1)                        /*!< External event source 3 for External Event 12 */
#define LL_HRTIM_EEV12SRC_ADC2_AWD2   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0) /*!< External event source 4 for External Event 12 */
#if defined(PLAY1)
#define LL_HRTIM_EEV12SRC_PLAY1_OUT11 (HRTIM_EEV_SRC_2)                             /*!< External event source 5 for External Event 12 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV13SRC_GPIO        0x00000000U                                   /*!< External event source 1 for External Event 13 */
#define LL_HRTIM_EEV13SRC_COMP5       (HRTIM_EECR1_EE1SRC_0)                        /*!< External event source 2 for External Event 13 */
#define LL_HRTIM_EEV13SRC_TIM15_TRGO  (HRTIM_EECR1_EE1SRC_1)                        /*!< External event source 3 for External Event 13 */
#define LL_HRTIM_EEV13SRC_ADC2_AWD3   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0) /*!< External event source 4 for External Event 13 */
#if defined(PLAY1)
#define LL_HRTIM_EEV13SRC_PLAY1_OUT12 (HRTIM_EEV_SRC_2)                             /*!< External event source 5 for External Event 13 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV14SRC_GPIO        0x00000000U                                   /*!< External event source 1 for External Event 14 */
#define LL_HRTIM_EEV14SRC_COMP8       (HRTIM_EECR1_EE1SRC_0)                        /*!< External event source 2 for External Event 14 */
#define LL_HRTIM_EEV14SRC_TIM1_TRGO   (HRTIM_EECR1_EE1SRC_1)                        /*!< External event source 3 for External Event 14 */
#define LL_HRTIM_EEV14SRC_ADC1_AWD1   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0) /*!< External event source 4 for External Event 14 */
#if defined(PLAY1)
#define LL_HRTIM_EEV14SRC_PLAY1_OUT13 (HRTIM_EEV_SRC_2)                             /*!< External event source 5 for External Event 14 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV15SRC_GPIO        0x00000000U                                   /*!< External event source 1 for External Event 15 */
#define LL_HRTIM_EEV15SRC_COMP1       (HRTIM_EECR1_EE1SRC_0)                        /*!< External event source 2 for External Event 15 */
#define LL_HRTIM_EEV15SRC_TIM8_TRGO   (HRTIM_EECR1_EE1SRC_1)                        /*!< External event source 3 for External Event 15 */
#define LL_HRTIM_EEV15SRC_ADC1_AWD2   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0) /*!< External event source 4 for External Event 15 */
#if defined(PLAY1)
#define LL_HRTIM_EEV15SRC_PLAY1_OUT14 (HRTIM_EEV_SRC_2)                             /*!< External event source 5 for External Event 15 */
#endif /* PLAY1 */

#define LL_HRTIM_EEV16SRC_GPIO        0x00000000U                                   /*!< External event source 1 for External Event 16 */
#define LL_HRTIM_EEV16SRC_COMP3       (HRTIM_EECR1_EE1SRC_0)                        /*!< External event source 2 for External Event 16 */
#define LL_HRTIM_EEV16SRC_TIM20_TRGO  (HRTIM_EECR1_EE1SRC_1)                        /*!< External event source 3 for External Event 16 */
#define LL_HRTIM_EEV16SRC_ADC1_AWD3   (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0) /*!< External event source 4 for External Event 16 */
#if defined(PLAY1)
#define LL_HRTIM_EEV16SRC_PLAY1_OUT15 (HRTIM_EEV_SRC_2)                             /*!< External event source 5 for External Event 16 */
#endif /* PLAY1 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EE_POLARITY HRTIM external event polarity
  * @{
  * @brief Constants defining the polarity of an external event.
  */
#define LL_HRTIM_EE_POLARITY_HIGH    0x00000000U             /*!< External event is active high */
#define LL_HRTIM_EE_POLARITY_LOW     (HRTIM_EECR1_EE1POL)    /*!< External event is active low */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EE_SENSITIVITY HRTIM external event sensitivity
  * @{
  * @brief Constants defining the sensitivity (level-sensitive or edge-sensitive) of an external event.
  */
#define LL_HRTIM_EE_SENSITIVITY_LEVEL            0x00000000U                                   /*!< External event is active on level */
#define LL_HRTIM_EE_SENSITIVITY_RISING          (HRTIM_EECR1_EE1SNS_0)                         /*!< External event is active on Rising edge */
#define LL_HRTIM_EE_SENSITIVITY_FALLING         (HRTIM_EECR1_EE1SNS_1)                         /*!< External event is active on Falling edge */
#define LL_HRTIM_EE_SENSITIVITY_RISING_FALLING  (HRTIM_EECR1_EE1SNS_1 | HRTIM_EECR1_EE1SNS_0)  /*!< External event is active on Rising and Falling edges */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EE_FASTMODE HRTIM external event fast mode
  * @{
  * @brief Constants defining whether or not an external event is programmed in fast mode.
  */
#define LL_HRTIM_EE_FASTMODE_DISABLE         0x00000000U              /*!< External Event is re-synchronized by the HRTIM logic before acting on outputs */
#define LL_HRTIM_EE_FASTMODE_ENABLE          (HRTIM_EECR1_EE1FAST)    /*!< External Event is acting asynchronously on outputs (low latency mode) */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EE_PRESCALER HRTIM external event prescaler
  * @{
  * @brief Constants defining division ratio between the timer clock frequency (fHRTIM) and the external event signal
  *        sampling clock (fEEVS) used by the digital filters.
  */
#define LL_HRTIM_EE_PRESCALER_DIV1    0x00000000U                                 /*!< fEEVS = fHRTIM */
#define LL_HRTIM_EE_PRESCALER_DIV2    (HRTIM_EECR3_EEVSD_0)                       /*!< fEEVS = fHRTIM / 2 */
#define LL_HRTIM_EE_PRESCALER_DIV4    (HRTIM_EECR3_EEVSD_1)                       /*!< fEEVS = fHRTIM / 4 */
#define LL_HRTIM_EE_PRESCALER_DIV8    (HRTIM_EECR3_EEVSD_1 | HRTIM_EECR3_EEVSD_0) /*!< fEEVS = fHRTIM / 8 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EE_COUNTER HRTIM external event Y or Z counter
  * @{
  * @brief Constants defining the external event counter.
  */
#define LL_HRTIM_EE_COUNTER_Y    0x00000000U                    /*!< External Event Y Counter */
#define LL_HRTIM_EE_COUNTER_Z    0x00000010U                    /*!< External Event Z Counter */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_EE_COUNTERRSTMODE  HRTIM EXTERNAL event Y or Z reset mode
  * @{
  * @brief Constants defining the external event reset mode.
  */
#define LL_HRTIM_EE_COUNTER_RSTMODE_UNCONDITIONAL   0x00000000U                 /*!< External Event counter is reset on each reset / roll-over event */
#define LL_HRTIM_EE_COUNTER_RSTMODE_CONDITIONAL     HRTIM_TIMxEEFR3_EEVYRSTM    /*!< External Event counter is reset on each reset / roll-over event only if no event occurs during last counting period */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_FLT_SRC HRTIM fault source
  * @{
  * @brief Constants defining whether a faults is be triggered by any external or internal fault source.
  */
#define LL_HRTIM_FLT1SRC_GPIO        0x00000000U                                      /*!< Fault input 1 is connected to GPIO */
#define LL_HRTIM_FLT1SRC_COMP2       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 1 is connected to COMP2 output */
#define LL_HRTIM_FLT1SRC_EEV1        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 1 is connected to External Event 1 */
#if defined(PLAY1)
#define LL_HRTIM_FLT1SRC_PLAY1_OUT0  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 1 is connected to PLAY1 output 0 */
#endif /* PLAY1 */

#define LL_HRTIM_FLT2SRC_GPIO        0x00000000U                                      /*!< Fault input 2 is connected to GPIO */
#define LL_HRTIM_FLT2SRC_COMP4       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 2 is connected to COMP4 output */
#define LL_HRTIM_FLT2SRC_EEV2        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 2 is connected to External Event 1 */
#if defined(PLAY1)
#define LL_HRTIM_FLT2SRC_PLAY1_OUT1  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 2 is connected to PLAY1 output 1 */
#endif /* PLAY1 */

#define LL_HRTIM_FLT3SRC_GPIO        0x00000000U                                      /*!< Fault input 3 is connected to GPIO */
#define LL_HRTIM_FLT3SRC_COMP6       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 3 is connected to COMP6 output */
#define LL_HRTIM_FLT3SRC_EEV3        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 3 is connected to External Event 3 */
#if defined(PLAY1)
#define LL_HRTIM_FLT3SRC_PLAY1_OUT2  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 3 is connected to PLAY1 output 2 */
#endif /* PLAY1 */

#define LL_HRTIM_FLT4SRC_GPIO        0x00000000U                                      /*!< Fault input 4 is connected to GPIO */
#define LL_HRTIM_FLT4SRC_COMP1       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 4 is connected to COMP1 output */
#define LL_HRTIM_FLT4SRC_EEV4        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 4 is connected to External Event 4 */
#if defined(PLAY1)
#define LL_HRTIM_FLT4SRC_PLAY1_OUT3  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 4 is connected to PLAY1 output 3 */
#endif /* PLAY1 */

#define LL_HRTIM_FLT5SRC_GPIO        0x00000000U                                      /*!< Fault input 5 is connected to GPIO */
#define LL_HRTIM_FLT5SRC_COMP3       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 5 is connected to COMP3 output */
#define LL_HRTIM_FLT5SRC_EEV5        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 5 is connected to External Event 5 */
#if defined(PLAY1)
#define LL_HRTIM_FLT5SRC_PLAY1_OUT4  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 5 is connected to PLAY1 output 4 */
#endif /* PLAY1 */

#define LL_HRTIM_FLT6SRC_GPIO        0x00000000U                                      /*!< Fault input 6 is connected to GPIO */
#define LL_HRTIM_FLT6SRC_COMP5       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 6 is connected to COMP5 output */
#define LL_HRTIM_FLT6SRC_EEV6        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 6 is connected to External Event 6 */
#if defined(PLAY1)
#define LL_HRTIM_FLT6SRC_PLAY1_OUT5  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 6 is connected to PLAY1 output 5 */
#endif /* PLAY1 */

#define LL_HRTIM_FLT7SRC_GPIO        0x00000000U                                      /*!< Fault input 7 is connected to GPIO */
#define LL_HRTIM_FLT7SRC_COMP7       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 7 is connected to COMP7 output */
#define LL_HRTIM_FLT7SRC_EEV7        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 7 is connected to External Event 7 */
#if defined(PLAY1)
#define LL_HRTIM_FLT7SRC_PLAY1_OUT6  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 7 is connected to PLAY1 output 6 */
#endif /* PLAY1 */

#define LL_HRTIM_FLT8SRC_GPIO        0x00000000U                                      /*!< Fault input 8 is connected to GPIO */
#define LL_HRTIM_FLT8SRC_COMP8       (HRTIM_FLTINR1_FLT1SRC)                          /*!< Fault input 8 is connected to COMP8 output */
#define LL_HRTIM_FLT8SRC_EEV8        (HRTIM_FLTINR2_FLT1SRC)                          /*!< Fault input 8 is connected to External Event 8 */
#if defined(PLAY1)
#define LL_HRTIM_FLT8SRC_PLAY1_OUT7  (HRTIM_FLTINR2_FLT1SRC | HRTIM_FLTINR1_FLT1SRC)  /*!< Fault input 8 is connected to PLAY1 output 7 */
#endif /* PLAY1 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_FLT_POLARITY HRTIM fault polarity
  * @{
  * @brief Constants defining the polarity of a fault event.
  */
#define LL_HRTIM_FLT_POLARITY_LOW     0x00000000U                /*!< Fault input is active low */
#define LL_HRTIM_FLT_POLARITY_HIGH    (HRTIM_FLTINR1_FLT1P)      /*!< Fault input is active high */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_FLT_PRESCALER HRTIM fault prescaler
  * @{
  * @brief Constants defining the division ratio between the timer clock frequency (fHRTIM) and the fault signal
  *        sampling clock (fFLTS) used  by the digital filters.
  */
#define LL_HRTIM_FLT_PRESCALER_DIV1    0x00000000U                                     /*!< fFLTS = fHRTIM */
#define LL_HRTIM_FLT_PRESCALER_DIV2    (HRTIM_FLTINR2_FLTSD_0)                         /*!< fFLTS = fHRTIM / 2 */
#define LL_HRTIM_FLT_PRESCALER_DIV4    (HRTIM_FLTINR2_FLTSD_1)                         /*!< fFLTS = fHRTIM / 4 */
#define LL_HRTIM_FLT_PRESCALER_DIV8    (HRTIM_FLTINR2_FLTSD_1 | HRTIM_FLTINR2_FLTSD_0) /*!< fFLTS = fHRTIM / 8 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_FLT_BLKS HRTIM fault blanking source
  * @{
  * @brief Constants defining the Blanking Source of a fault event.
  */
#define LL_HRTIM_FLT_BLK_RSTALIGNED            0x00000000U                /*!< Fault blanking source is Reset-aligned  */
#define LL_HRTIM_FLT_BLK_MOVING                (HRTIM_FLTINR3_FLT1BLKS)   /*!< Fault blanking source is Moving window */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_FLT_RSTM HRTIM fault counter reset mode
  * @{
  * @brief Constants defining the Counter RESet Mode of a fault event.
  */
#define LL_HRTIM_FLT_COUNTERRST_UNCONDITIONAL    0x00000000U                    /*!< Fault counter is reset on each reset / roll-over event */
#define LL_HRTIM_FLT_COUNTERRST_CONDITIONAL      (HRTIM_FLTINR3_FLT1RSTM)       /*!< Fault counter is reset on each reset / roll-over event only if no fault occurred during last counting
period. */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_BM_MODE HRTIM burst mode operating mode
  * @{
  * @brief Constants defining if the burst mode is entered once or if it is continuously operating.
  */
#define LL_HRTIM_BM_MODE_SINGLE_SHOT  0x00000000U            /*!< Burst mode operates in single shot mode */
#define LL_HRTIM_BM_MODE_CONTINUOUS   (HRTIM_BMCR_BMOM)      /*!< Burst mode operates in continuous mode */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_BM_CLKSRC HRTIM burst mode clock source
  * @{
  * @brief Constants defining the clock source for the burst mode counter.
  */
#define LL_HRTIM_BM_CLKSRC_MASTER     0x00000000U                                                     /*!< Master timer counter reset/roll-over is used as clock source for the burst mode counter */
#define LL_HRTIM_BM_CLKSRC_TIMA       (HRTIM_BMCR_BMCLK_0)                                            /*!< Timer A counter reset/roll-over is used as clock source for the burst mode counter */
#define LL_HRTIM_BM_CLKSRC_TIMB       (HRTIM_BMCR_BMCLK_1)                                            /*!< Timer B counter reset/roll-over is used as clock source for the burst mode counter */
#define LL_HRTIM_BM_CLKSRC_TIMC       (HRTIM_BMCR_BMCLK_1 | HRTIM_BMCR_BMCLK_0)                       /*!< Timer C counter reset/roll-over is used as clock source for the burst mode counter */
#define LL_HRTIM_BM_CLKSRC_TIMD       (HRTIM_BMCR_BMCLK_2)                                            /*!< Timer D counter reset/roll-over is used as clock source for the burst mode counter */
#define LL_HRTIM_BM_CLKSRC_TIME       (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_0)                       /*!< Timer E counter reset/roll-over is used as clock source for the burst mode counter */
#define LL_HRTIM_BM_CLKSRC_TIMF    (HRTIM_BMCR_BMCLK_3 | HRTIM_BMCR_BMCLK_1 | HRTIM_BMCR_BMCLK_0)     /*!< Timer F counter reset/roll-over is used as clock source for the burst mode counter */
#define LL_HRTIM_BM_CLKSRC_TIM12_OC1   (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_1)                       /*!< On-chip Event 1 (BMClk[1]), acting as a burst mode counter clock */
#define LL_HRTIM_BM_CLKSRC_TIM13_OC1   (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_1 | HRTIM_BMCR_BMCLK_0)  /*!< On-chip Event 2 (BMClk[2]), acting as a burst mode counter clock */
#define LL_HRTIM_BM_CLKSRC_TIM7_TRGO  (HRTIM_BMCR_BMCLK_3)                                            /*!< On-chip Event 3 (BMClk[3]), acting as a burst mode counter clock */
#define LL_HRTIM_BM_CLKSRC_TIM27_TRGO  (HRTIM_BMCR_BMCLK_3 | HRTIM_BMCR_BMCLK_0)                       /*!< On-chip Event 4 (BMClk[4]), acting as a burst mode counter clock */
#define LL_HRTIM_BM_CLKSRC_HRTIM      (HRTIM_BMCR_BMCLK_3 | HRTIM_BMCR_BMCLK_1)                        /*!< Prescaled fHRTIM clock is used as clock source for the burst mode counter */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_BM_PRESCALER HRTIM burst mode prescaler
  * @{
  * @brief Constants defining the prescaling ratio of the fHRTIM clock for the burst mode controller (fBRST).
  */
#define LL_HRTIM_BM_PRESCALER_DIV1     0x00000000U                                                                             /*!< fBRST = fHRTIM */
#define LL_HRTIM_BM_PRESCALER_DIV2     (HRTIM_BMCR_BMPRSC_0)                                                                   /*!< fBRST = fHRTIM/2 */
#define LL_HRTIM_BM_PRESCALER_DIV4     (HRTIM_BMCR_BMPRSC_1)                                                                   /*!< fBRST = fHRTIM/4 */
#define LL_HRTIM_BM_PRESCALER_DIV8     (HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0)                                             /*!< fBRST = fHRTIM/8 */
#define LL_HRTIM_BM_PRESCALER_DIV16    (HRTIM_BMCR_BMPRSC_2)                                                                   /*!< fBRST = fHRTIM/16 */
#define LL_HRTIM_BM_PRESCALER_DIV32    (HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_0)                                             /*!< fBRST = fHRTIM/32 */
#define LL_HRTIM_BM_PRESCALER_DIV64    (HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1)                                             /*!< fBRST = fHRTIM/64 */
#define LL_HRTIM_BM_PRESCALER_DIV128   (HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0)                       /*!< fBRST = fHRTIM/128 */
#define LL_HRTIM_BM_PRESCALER_DIV256   (HRTIM_BMCR_BMPRSC_3)                                                                   /*!< fBRST = fHRTIM/256 */
#define LL_HRTIM_BM_PRESCALER_DIV512   (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_0)                                             /*!< fBRST = fHRTIM/512 */
#define LL_HRTIM_BM_PRESCALER_DIV1024  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_1)                                             /*!< fBRST = fHRTIM/1024 */
#define LL_HRTIM_BM_PRESCALER_DIV2048  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0)                       /*!< fBRST = fHRTIM/2048*/
#define LL_HRTIM_BM_PRESCALER_DIV4096  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2)                                             /*!< fBRST = fHRTIM/4096 */
#define LL_HRTIM_BM_PRESCALER_DIV8192  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_0)                       /*!< fBRST = fHRTIM/8192 */
#define LL_HRTIM_BM_PRESCALER_DIV16384 (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1)                       /*!< fBRST = fHRTIM/16384 */
#define LL_HRTIM_BM_PRESCALER_DIV32768 (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0) /*!< fBRST = fHRTIM/32768 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_BM_TRIG HRTIM HRTIM burst mode trigger
  * @{
  * @brief Constants defining the events that can be used to trig the burst mode operation.
  */
#define LL_HRTIM_BM_TRIG_NONE               0x00000000U           /*!<  No trigger */
#define LL_HRTIM_BM_TRIG_MASTER_RESET       HRTIM_BMTRGR_MSTRST   /*!<  Master timer reset event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_MASTER_REPETITION  HRTIM_BMTRGR_MSTREP   /*!<  Master timer repetition event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_MASTER_CMP1        HRTIM_BMTRGR_MSTCMP1  /*!<  Master timer compare 1 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_MASTER_CMP2        HRTIM_BMTRGR_MSTCMP2  /*!<  Master timer compare 2 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_MASTER_CMP3        HRTIM_BMTRGR_MSTCMP3  /*!<  Master timer compare 3 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_MASTER_CMP4        HRTIM_BMTRGR_MSTCMP4  /*!<  Master timer compare 4 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMA_RESET         HRTIM_BMTRGR_TARST    /*!< Timer A reset event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMA_REPETITION    HRTIM_BMTRGR_TAREP    /*!< Timer A repetition event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMA_CMP1          HRTIM_BMTRGR_TACMP1   /*!< Timer A compare 1 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMA_CMP2          HRTIM_BMTRGR_TACMP2   /*!< Timer A compare 2 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMB_RESET         HRTIM_BMTRGR_TBRST    /*!< Timer B reset event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMB_REPETITION    HRTIM_BMTRGR_TBREP    /*!< Timer B repetition event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMB_CMP1          HRTIM_BMTRGR_TBCMP1   /*!< Timer B compare 1 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMB_CMP2          HRTIM_BMTRGR_TBCMP2   /*!< Timer B compare 2 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMC_RESET         HRTIM_BMTRGR_TCRST    /*!< Timer C resetevent is starting the burst mode operation  */
#define LL_HRTIM_BM_TRIG_TIMC_REPETITION    HRTIM_BMTRGR_TCREP    /*!< Timer C repetition event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMC_CMP1          HRTIM_BMTRGR_TCCMP1   /*!< Timer C compare 1 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMD_RESET         HRTIM_BMTRGR_TDRST    /*!< Timer D reset event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMD_REPETITION    HRTIM_BMTRGR_TDREP    /*!< Timer D repetition event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMD_CMP2          HRTIM_BMTRGR_TDCMP2   /*!< Timer D compare 2 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIME_REPETITION    HRTIM_BMTRGR_TEREP    /*!< Timer E repetition event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIME_CMP1          HRTIM_BMTRGR_TECMP1   /*!< Timer E compare 1 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIME_CMP2          HRTIM_BMTRGR_TECMP2   /*!< Timer E compare 2 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMF_RESET         HRTIM_BMTRGR_TFRST    /*!< Timer F reset event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMF_REPETITION    HRTIM_BMTRGR_TFREP    /*!< Timer F repetition event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMF_CMP1          HRTIM_BMTRGR_TFCMP1   /*!< Timer F compare 1 event is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_TIMA_EEVG          HRTIM_BMTRGR_TAEEVG   /*!< Timer A period following an external event G (conditioned by TIMA filters) is starting the burst mode operation  */
#define LL_HRTIM_BM_TRIG_TIMD_EEVH          HRTIM_BMTRGR_TDEEVH   /*!< Timer D period following an external event H (conditioned by TIMD filters) is starting the burst mode operation  */
#define LL_HRTIM_BM_TRIG_EEVG               HRTIM_BMTRGR_EEVG     /*!< External event G conditioned by TIMA filters is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_EEVH               HRTIM_BMTRGR_EEVH     /*!< External event H conditioned by TIMD filters is starting the burst mode operation */
#define LL_HRTIM_BM_TRIG_ONCHIP             HRTIM_BMTRGR_OCHPEV   /*!< A rising edge on an on-chip Event (for instance from GP timer or comparator) triggers the burst mode operation */
/**
  * @}
  */
#if defined(PLAY1)

/** @defgroup LL_HRTIM_BM_TRG_SEL HRTIM HRTIM burst mode trigger source
  * @{
  * @brief Constants defining the operating state of the burst mode controller.
  */
#define LL_HRTIM_BM_TRIG_SRC_TIM26_TRGO        0x00000000U        /*!< hrtim_bm_trg input is connected to TIM26 TRGO signal */
#define LL_HRTIM_BM_TRIG_SRC_PLAY1_OUT13       HRTIM_OR_BMTRGSEL  /*!< hrtim_bm_trg input is connected to PLAY1 output 13 signal */
/**
  * @}
  */
#endif /* PLAY1 */

/** @defgroup HRTIM_LL_EC_BM_STATUS HRTIM burst mode status
  * @{
  * @brief Constants defining the operating state of the burst mode controller.
  */
#define LL_HRTIM_BM_STATUS_NORMAL             0x00000000U           /*!< Normal operation */
#define LL_HRTIM_BM_STATUS_BURST_ONGOING      HRTIM_BMCR_BMSTAT     /*!< Burst operation on-going */
/**
  * @}
  */

/** @defgroup HRTIM_LL_COUNTER_MODE HRTIM counter mode
  * @{
  * @brief Constants defining the Counter Up Down Mode.
  */
#define LL_HRTIM_COUNTING_MODE_UP                    0x00000000U                                     /*!< counter is operating in up-counting mode */
#define LL_HRTIM_COUNTING_MODE_UP_DOWN               HRTIM_TIMxCR2_UDM                               /*!< counter is operating in up-down counting mode  */
/**
  * @}
  */

/** @defgroup HRTIM_LL_COUNTER_Roll-Over HRTIM roll-over mode
  * @{
  * @brief Constants defining the roll-over mode.
  */
#define LL_HRTIM_ROLLOVER_MODE_PER            0x00000002U                        /*!< Event generated when counter reaches period value  ('crest' mode) */
#define LL_HRTIM_ROLLOVER_MODE_RST            0x00000001U                        /*!< Event generated when counter equals 0 ('valley' mode) */
#define LL_HRTIM_ROLLOVER_MODE_BOTH           0x00000000U                        /*!< Event generated when counter reach both conditions (0 or HRTIM_PERxR value) */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_TrigHalf_Mode HRTIM triggered-half mode
  * @{
  * @brief Constants defining the triggered-half modes.
  */
#define LL_HRTIM_TRIGHALF_DISABLE         0x00000000U                                     /*!< Timer Compare 2 register is behaving in standard mode */
#define LL_HRTIM_TRIGHALF_ENABLE          HRTIM_TIMxCR2_TRGHLF                            /*!< Timer Compare 2 register is behaving in triggered-half mode  */
#define LL_HRTIM_TRIGHALF_ENABLE_TIMEOUT  (HRTIM_TIMxCR2_TRGHLFT | HRTIM_TIMxCR2_TRGHLF)  /*!< Timer Compare 2 register is behaving in triggered-half mode with timeout */
/**
  * @}
  */

/** @defgroup HRTIM_LL_COUNTER_Compare HRTIM PWM mode with greater than comparison
  * @{
  * @brief Constants defining the greater than compare 1 or 3 PWM Mode.
  */
#define LL_HRTIM_GTCMP1_EQUAL             0x00000000U            /*!< event is generated when counter is equal to compare value */
#define LL_HRTIM_GTCMP1_GREATER           HRTIM_TIMxCR2_GTCMP1   /*!< event is generated when counter is greater than compare value */
#define LL_HRTIM_GTCMP3_EQUAL             0x00000000U            /*!< event is generated when counter is equal to compare value */
#define LL_HRTIM_GTCMP3_GREATER           HRTIM_TIMxCR2_GTCMP3   /*!< event is generated when counter is greater than compare value */
/**
  * @}
  */

/** @defgroup HRTIM_LL_COUNTER_DCDE HRTIM dual channel DAC enable
  * @{
  * @brief Constants enabling the Dual Channel DAC Reset trigger mechanism.
  */
#define LL_HRTIM_DCDE_DISABLED      0x00000000U               /*!<  Dual Channel DAC trigger is generated on counter reset or roll-over event */
#define LL_HRTIM_DCDE_ENABLED       HRTIM_TIMxCR2_DCDE        /*!<  Dual Channel DAC trigger is generated on output 1 set  event */
/**
  * @}
  */

/** @defgroup HRTIM_LL_COUNTER_DCDR HRTIM dual channel DAC reset trigger
  * @{
  * @brief Constants defining the Dual Channel DAC Reset trigger.
  */
#define LL_HRTIM_DCDR_RESET         0x00000000U               /*!< Dual Channel DAC trigger is generated on counter reset or roll-over event */
#define LL_HRTIM_DCDR_OUT1_SET      HRTIM_TIMxCR2_DCDR        /*!< Dual Channel DAC trigger is generated on output 1 set  event */
/**
  * @}
  */

/** @defgroup HRTIM_LL_COUNTER_DCDS HRTIM dual channel DAC step trigger
  * @{
  * @brief Constants defining the Dual Channel DAC Step trigger.
  */
#define LL_HRTIM_DCDS_CMP2          0x00000000U               /*!< trigger is generated on compare 2 event */
#define LL_HRTIM_DCDS_OUT1_RESET    HRTIM_TIMxCR2_DCDS        /*!< trigger is generated on output 1 reset event */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CO_MODE HRTIM crossbar override mode
  * @{
  * @brief Constants defining the Crossbar Override Modes.
  */
#define LL_HRTIM_CO_MODE_CYCLE_BY_CYCLE  0x00000000U              /*!< Crossbar operation is automatically resumed */
#define LL_HRTIM_CO_MODE_LATCHED         HRTIM_TIMxCR2_COM        /*!< Crossbar override mode is entered only once */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CO_TRIGGERS HRTIM crossbar override triggers
  * @{
  * @brief Constants defining the Crossbar Override Triggers.
  */
#define LL_HRTIM_CO_TRIG_NONE             0x00000000U                    /*!< All crossbar override triggers are ignored */
#define LL_HRTIM_CO_TRIG_SW               HRTIM_COTRGxR_SWT               /*!< Crossbar override software trigger */
#define LL_HRTIM_CO_TRIG_FLT1             HRTIM_COTRGxR_FLT1              /*!< Fault 1 input trigger */
#define LL_HRTIM_CO_TRIG_FLT2             HRTIM_COTRGxR_FLT2              /*!< Fault 2 input trigger */
#define LL_HRTIM_CO_TRIG_FLT3             HRTIM_COTRGxR_FLT3              /*!< Fault 3 input trigger */
#define LL_HRTIM_CO_TRIG_FLT4             HRTIM_COTRGxR_FLT4              /*!< Fault 4 input trigger */
#define LL_HRTIM_CO_TRIG_FLT5             HRTIM_COTRGxR_FLT5              /*!< Fault 5 input trigger */
#define LL_HRTIM_CO_TRIG_FLT6             HRTIM_COTRGxR_FLT6              /*!< Fault 6 input trigger */
#define LL_HRTIM_CO_TRIG_FLT7             HRTIM_COTRGxR_FLT7              /*!< Fault 7 input trigger */
#define LL_HRTIM_CO_TRIG_FLT8             HRTIM_COTRGxR_FLT8              /*!< Fault 8 input trigger */
#define LL_HRTIM_CO_TRIG_FLT1_FLT2        HRTIM_COTRGxR_FLT1A2            /*!< Fault 1 and Fault 2 trigger */
#define LL_HRTIM_CO_TRIG_FLT2_FLT3        HRTIM_COTRGxR_FLT2A3            /*!< Fault 2 and Fault 3 trigger */
#define LL_HRTIM_CO_TRIG_FLT3_FLT4        HRTIM_COTRGxR_FLT3A4            /*!< Fault 3 and Fault 4 trigger */
#define LL_HRTIM_CO_TRIG_FLT4_FLT5        HRTIM_COTRGxR_FLT4A5            /*!< Fault 4 and Fault 5 trigger */
#define LL_HRTIM_CO_TRIG_FLT5_FLT6        HRTIM_COTRGxR_FLT5A6            /*!< Fault 5 and Fault 6 trigger */
#define LL_HRTIM_CO_TRIG_FLT6_FLT7        HRTIM_COTRGxR_FLT6A7            /*!< Fault 6 and Fault 7 trigger */
#define LL_HRTIM_CO_TRIG_FLT7_FLT8        HRTIM_COTRGxR_FLT7A8            /*!< Fault 7 and Fault 8 trigger */
#define LL_HRTIM_CO_TRIG_EEVA             HRTIM_COTRGxR_EEVA              /*!< External event A trigger */
#define LL_HRTIM_CO_TRIG_EEVB             HRTIM_COTRGxR_EEVB              /*!< External event B trigger */
#define LL_HRTIM_CO_TRIG_EEVC             HRTIM_COTRGxR_EEVC              /*!< External event C trigger */
#define LL_HRTIM_CO_TRIG_EEVD             HRTIM_COTRGxR_EEVD              /*!< External event D trigger */
#define LL_HRTIM_CO_TRIG_EEVE             HRTIM_COTRGxR_EEVE              /*!< External event E trigger */
#define LL_HRTIM_CO_TRIG_EEVF             HRTIM_COTRGxR_EEVF              /*!< External event F trigger */
#define LL_HRTIM_CO_TRIG_EEVG             HRTIM_COTRGxR_EEVG              /*!< External event G trigger */
#define LL_HRTIM_CO_TRIG_EEVH             HRTIM_COTRGxR_EEVH              /*!< External event H trigger */
#define LL_HRTIM_CO_TRIG_EEVI             HRTIM_COTRGxR_EEVI              /*!< External event I trigger */
#define LL_HRTIM_CO_TRIG_EEVJ             HRTIM_COTRGxR_EEVJ              /*!< External event J trigger */
#if defined(PLAY1)
#define LL_HRTIM_CO_TRIG_PLAY1_OUT1       HRTIM_COTRGxR_EXT_TRG0          /*!< PLAY1 Output 1 (external trigger 0) */
#define LL_HRTIM_CO_TRIG_PLAY1_OUT2       HRTIM_COTRGxR_EXT_TRG1          /*!< PLAY1 Output 2 (external trigger 1) */
#define LL_HRTIM_CO_TRIG_PLAY1_OUT3       HRTIM_COTRGxR_EXT_TRG2          /*!< PLAY1 Output 3 (external trigger 2) */
#define LL_HRTIM_CO_TRIG_PLAY1_OUT4       HRTIM_COTRGxR_EXT_TRG3          /*!< PLAY1 Output 4 (external trigger 3) */
#define LL_HRTIM_CO_TRIG_PLAY1_OUT5       HRTIM_COTRGxR_EXT_TRG4          /*!< PLAY1 Output 5 (external trigger 4) */
#define LL_HRTIM_CO_TRIG_PLAY1_OUT6       HRTIM_COTRGxR_EXT_TRG5          /*!< PLAY1 Output 6 (external trigger 5) */
#endif /* PLAY1 */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CO_FORCEMODE HRTIM crossbar override force mode
  * @{
  * @brief Constants defining the Crossbar Override Force Modes.
  */
#define LL_HRTIM_CO_FORCEMODE_DELAY1     0x00000000U                                  /*!< Output forced to inactive level after Delay 1 */
#define LL_HRTIM_CO_FORCEMODE_DELAY2     HRTIM_COFExR_COFMA_0                          /*!< Output forced to inactive level after Delay 2 */
#define LL_HRTIM_CO_FORCEMODE_INACTIVE   HRTIM_COFExR_COFMA_1                          /*!< Output forced to inactive level */
#define LL_HRTIM_CO_FORCEMODE_ACTIVE     (HRTIM_COFExR_COFMA_1 | HRTIM_COFExR_COFMA_0)  /*!< Output forced to active level */
#define LL_HRTIM_CO_FORCEMODE_EVENT      HRTIM_COFExR_COFMA_2                          /*!< Output forced to inactive level on events */
/**
  * @}
  */

/** @defgroup HRTIM_LL_EC_CO_FORCEON HRTIM crossbar override force on event
  * @{
  * @brief Constants defining the events forcing an output to its active level when
  *        the crossbar override is triggered.
  */
#define LL_HRTIM_CO_FORCEON_NONE    0x00000000U                 /*!< No external event force the output to its active level */
#define LL_HRTIM_CO_FORCEON_EEVA    HRTIM_COFExR_EEVAFRCA        /*!< Output level is forced active on external event A */
#define LL_HRTIM_CO_FORCEON_EEVB    HRTIM_COFExR_EEVBFRCA        /*!< Output level is forced active on external event B */
#define LL_HRTIM_CO_FORCEON_EEVC    HRTIM_COFExR_EEVCFRCA        /*!< Output level is forced active on external event C */
#define LL_HRTIM_CO_FORCEON_EEVD    HRTIM_COFExR_EEVDFRCA        /*!< Output level is forced active on external event D */
#define LL_HRTIM_CO_FORCEON_EEVE    HRTIM_COFExR_EEVEFRCA        /*!< Output level is forced active on external event E */
#define LL_HRTIM_CO_FORCEON_EEVF    HRTIM_COFExR_EEVFFRCA        /*!< Output level is forced active on external event F */
#define LL_HRTIM_CO_FORCEON_EEVG    HRTIM_COFExR_EEVGFRCA        /*!< Output level is forced active on external event G */
#define LL_HRTIM_CO_FORCEON_EEVH    HRTIM_COFExR_EEVHFRCA        /*!< Output level is forced active on external event H */
#define LL_HRTIM_CO_FORCEON_EEVI    HRTIM_COFExR_EEVIFRCA        /*!< Output level is forced active on external event I */
#define LL_HRTIM_CO_FORCEON_EEVJ    HRTIM_COFExR_EEVJFRCA        /*!< Output level is forced active on external event J */
/**
  * @}
  */

/** @defgroup RTIM_LL_EC_CO_STATUS HRTIM crossbar override status
  * @{
  * @brief Constants defining the crossbar override status.
  */
#define LL_HRTIM_CO_STATUS_INACTIVE   0x00000000U              /*!< Crossbar override is inactive (crossbar is active) */
#define LL_HRTIM_CO_STATUS_ACTIVE     HRTIM_TIMxISR_COS        /*!< Crossbar override is active */
/**
  * @}
  */

/** @defgroup RTIM_LL_EC_CO_TRIGGER HRTIM crossbar override trigger
  * @{
  * @brief Constants defining the crossbar override trigger status.
  */
#define LL_HRTIM_CO_TRIGGER_INACTIVE   0x00000000U              /*!< Crossbar override trigger is inactive */
#define LL_HRTIM_CO_TRIGGER_ACTIVE     HRTIM_TIMxISR_COTS       /*!< Crossbar override trigger is active */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HRTIM_LL_Exported_Macros LL HRTIM Macros
  * @{
  */

/** @defgroup HRTIM_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in HRTIM register.
  * @param  __INSTANCE__ HRTIM Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_HRTIM_WRITE_REG(__INSTANCE__, __REG__, __VALUE__) \
  STM32_WRITE_REG((__INSTANCE__)->sCommonRegs.__REG__, (__VALUE__))

/**
  * @brief  Read a value in HRTIM register.
  * @param  __INSTANCE__ HRTIM Instance
  * @param  __REG__ Register to be read
  * @retval Register value.
  */
#define LL_HRTIM_READ_REG(__INSTANCE__, __REG__) \
  STM32_READ_REG((__INSTANCE__)->sCommonRegs.__REG__)
/**
  * @}
  */

/** @defgroup HRTIM_LL_EM_MASTER_WRITE_READ Master timer Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in HRTIM register.
  * @param  __INSTANCE__ HRTIM Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_HRTIM_MASTER_WRITE_REG(__INSTANCE__, __REG__, __VALUE__) \
  STM32_WRITE_REG((__INSTANCE__)->sMasterRegs.__REG__, (__VALUE__))

/**
  * @brief  Read a value in HRTIM register.
  * @param  __INSTANCE__ HRTIM Instance
  * @param  __REG__ Register to be read
  * @retval Register value.
  */
#define LL_HRTIM_MASTER_READ_REG(__INSTANCE__, __REG__) \
  STM32_READ_REG((__INSTANCE__)->sMasterRegs.__REG__)
/**
  * @}
  */

/** @defgroup HRTIM_LL_EM_TIM_WRITE_READ Timer A to F Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in HRTIM register.
  * @param  __INSTANCE__ HRTIM Instance
  * @param  __TIM__ timing unit (timer A to F)
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  */
#define LL_HRTIM_TIM_WRITE_REG(__INSTANCE__, __TIM__, __REG__, __VALUE__) \
  STM32_WRITE_REG((__INSTANCE__)->sTimerxRegs[(__TIM__)].__REG__, (__VALUE__))

/**
  * @brief  Read a value in HRTIM register.
  * @param  __INSTANCE__ HRTIM Instance
  * @param  __TIM__ timing unit (timer A to F)
  * @param  __REG__ Register to be read
  * @retval Register value.
  */
#define LL_HRTIM_TIM_READ_REG(__INSTANCE__, __TIM__, __REG__) \
  STM32_READ_REG((__INSTANCE__)->sTimerxRegs[(__TIM__)].__REG__)
/**
  * @}
  */

/** @defgroup HRTIM_LL_EM_Exported_Macros Exported_Macros
  * @{
  */
/**
  * @brief  HELPER macro returning the output status from output enable/disable status.
  * @param  __OUTPUT_STATUS_EN__ output enable status
  * @param  __OUTPUT_STATUS_DIS__ output Disable status
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUTSTATUS_DISABLED
  *         @arg @ref LL_HRTIM_OUTPUTSTATUS_ENABLED
  *         @arg @ref LL_HRTIM_OUTPUTSTATUS_FAULT
  */
#define LL_HRTIM_GET_OUTPUT_STATUS(__OUTPUT_STATUS_EN__, __OUTPUT_STATUS_DIS__) \
  (((__OUTPUT_STATUS_EN__) == 1) ?  LL_HRTIM_OUTPUTSTATUS_ENABLED :\
   ((__OUTPUT_STATUS_DIS__) == 0) ? LL_HRTIM_OUTPUTSTATUS_DISABLED : LL_HRTIM_OUTPUTSTATUS_FAULT)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HRTIM_LL_Exported_Functions LL HRTIM Functions
  * @{
  */
/** @defgroup HRTIM_LL_EF_HRTIM_Control HRTIM_Control
  * @{
  */

/**
  * @brief  Select the HRTIM synchronization input source.
  * @rmtoll
  *  MCR          SYNCIN        LL_HRTIM_SetSyncInSrc \n
  *  OR           INSYNCSEL     LL_HRTIM_SetSyncInSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  sync_in_src This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_NONE
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_GPIO
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_TIM1_TRGO
  * @if PLAY1
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_PLAY1_OUT15 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  * @note This function must not be called when  the concerned timer(s) is (are) enabled .
  */
__STATIC_INLINE void LL_HRTIM_SetSyncInSrc(HRTIM_TypeDef *hrtimx, uint32_t sync_in_src)
{
#if defined(PLAY1)
  STM32_MODIFY_REG(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCIN, (sync_in_src & ~HRTIM_OR_INSYNCSEL));
  STM32_MODIFY_REG(hrtimx->sCommonRegs.OR, HRTIM_OR_INSYNCSEL, (sync_in_src & HRTIM_OR_INSYNCSEL));
#else
  STM32_MODIFY_REG(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCIN, sync_in_src);
#endif /* PLAY1 */
}

/**
  * @brief  Get actual HRTIM synchronization input source.
  * @rmtoll
  *  MCR          SYNCIN        LL_HRTIM_SetSyncInSrc \n
  *  OR           INSYNCSEL     LL_HRTIM_SetSyncInSrc
  * @param  hrtimx High Resolution Timer instance
  * @retval sync_in_src Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_NONE
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_GPIO
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_TIM1_TRGO
  * @if PLAY1
  *         @arg @ref LL_HRTIM_SYNCIN_SRC_PLAY1_OUT15 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetSyncInSrc(const HRTIM_TypeDef *hrtimx)
{
#if defined(PLAY1)
  uint32_t syncin = STM32_READ_BIT(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCIN);
  uint32_t insyncsel = STM32_READ_BIT(hrtimx->sCommonRegs.OR, HRTIM_OR_INSYNCSEL);
  return (syncin | insyncsel);
#else
  return (STM32_READ_BIT(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCIN));
#endif /* PLAY1 */
}

/**
  * @brief  Configure the HRTIM synchronization output.
  * @rmtoll
  *  MCR          SYNCSRC      LL_HRTIM_ConfigSyncOut \n
  *  MCR          SYNCOUT      LL_HRTIM_ConfigSyncOut
  * @param  hrtimx High Resolution Timer instance
  * @param  sync_out_config This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCOUT_DISABLE
  *         @arg @ref LL_HRTIM_SYNCOUT_POSITIVE_PULSE
  *         @arg @ref LL_HRTIM_SYNCOUT_NEGATIVE_PULSE
  * @param  sync_out_src This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_MASTER_START
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_MASTER_CMP1
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_TIMA_START
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_TIMA_CMP1
  */
__STATIC_INLINE void LL_HRTIM_ConfigSyncOut(HRTIM_TypeDef *hrtimx, uint32_t sync_out_config, uint32_t sync_out_src)
{
  STM32_MODIFY_REG(hrtimx->sMasterRegs.MCR, (HRTIM_MCR_SYNCOUT | HRTIM_MCR_SYNCSRC),
                   (sync_out_config | sync_out_src));
}

/**
  * @brief  Set the routing and conditioning of the synchronization output event.
  * @rmtoll
  *  MCR          SYNCOUT      LL_HRTIM_SetSyncOutConfig
  * @param  hrtimx High Resolution Timer instance
  * @param  sync_out_config This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCOUT_DISABLE
  *         @arg @ref LL_HRTIM_SYNCOUT_POSITIVE_PULSE
  *         @arg @ref LL_HRTIM_SYNCOUT_NEGATIVE_PULSE
  * @note This function can be called only when the master timer is enabled.
  */
__STATIC_INLINE void LL_HRTIM_SetSyncOutConfig(HRTIM_TypeDef *hrtimx, uint32_t sync_out_config)
{
  STM32_MODIFY_REG(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCOUT, sync_out_config);
}

/**
  * @brief  Get actual routing and conditioning of the synchronization output event.
  * @rmtoll
  *  MCR          SYNCOUT      LL_HRTIM_GetSyncOutConfig
  * @param  hrtimx High Resolution Timer instance
  * @retval sync_out_config Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCOUT_DISABLE
  *         @arg @ref LL_HRTIM_SYNCOUT_POSITIVE_PULSE
  *         @arg @ref LL_HRTIM_SYNCOUT_NEGATIVE_PULSE
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetSyncOutConfig(const HRTIM_TypeDef *hrtimx)
{
  return (STM32_READ_BIT(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCOUT));
}

/**
  * @brief  Set the source and event to be sent on the HRTIM synchronization output.
  * @rmtoll
  *  MCR          SYNCSRC      LL_HRTIM_SetSyncOutSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  sync_out_src This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_MASTER_START
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_MASTER_CMP1
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_TIMA_START
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_TIMA_CMP1
  */
__STATIC_INLINE void LL_HRTIM_SetSyncOutSrc(HRTIM_TypeDef *hrtimx, uint32_t sync_out_src)
{
  STM32_MODIFY_REG(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCSRC, sync_out_src);
}

/**
  * @brief  Get actual  source and event sent on the HRTIM synchronization output.
  * @rmtoll
  *  MCR          SYNCSRC      LL_HRTIM_GetSyncOutSrc
  * @param  hrtimx High Resolution Timer instance
  * @retval sync_out_src Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_MASTER_START
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_MASTER_CMP1
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_TIMA_START
  *         @arg @ref LL_HRTIM_SYNCOUT_SRC_TIMA_CMP1
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetSyncOutSrc(const HRTIM_TypeDef *hrtimx)
{
  return (STM32_READ_BIT(hrtimx->sMasterRegs.MCR, HRTIM_MCR_SYNCSRC));
}

/**
  * @brief  Enable update event generation.
  * @rmtoll
  *  CR1          MUDIS         LL_HRTIM_EnableUpdate \n
  *  CR1          TAUDIS        LL_HRTIM_EnableUpdate \n
  *  CR1          TBUDIS        LL_HRTIM_EnableUpdate \n
  *  CR1          TCUDIS        LL_HRTIM_EnableUpdate \n
  *  CR1          TDUDIS        LL_HRTIM_EnableUpdate \n
  *  CR1          TEUDIS        LL_HRTIM_EnableUpdate \n
  *  CR1          TFUDIS        LL_HRTIM_EnableUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  *         @arg @ref LL_HRTIM_TIM_ALL
  * @note The regular update event takes place.
  */
__STATIC_INLINE void LL_HRTIM_EnableUpdate(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.CR1, ((timers >> HRTIM_MCR_MCEN_Pos) & LL_HRTIM_CR1_UDIS_MASK));
}

/**
  * @brief  Disable (temporarily) update event generation.
  * @rmtoll
  *  CR1          MUDIS         LL_HRTIM_DisableUpdate \n
  *  CR1          TAUDIS        LL_HRTIM_DisableUpdate \n
  *  CR1          TBUDIS        LL_HRTIM_DisableUpdate \n
  *  CR1          TCUDIS        LL_HRTIM_DisableUpdate \n
  *  CR1          TDUDIS        LL_HRTIM_DisableUpdate \n
  *  CR1          TEUDIS        LL_HRTIM_DisableUpdate \n
  *  CR1          TFUDIS        LL_HRTIM_DisableUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  *         @arg @ref LL_HRTIM_TIM_ALL
  * @note Allow to temporarily disable the transfer from preload to active
  *       registers, whatever the selected update event. This allows to modify
  *       several registers in multiple timers. The regular update event takes
  *       place once the update event is re-enabled.
  */
__STATIC_INLINE void LL_HRTIM_DisableUpdate(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.CR1, ((timers >> HRTIM_MCR_MCEN_Pos) & LL_HRTIM_CR1_UDIS_MASK));
}

/**
  * @brief  Indicate whether the update event is enabled for the timer(s).
  * @rmtoll
  *  CR1          MUDIS         LL_HRTIM_IsEnabledUpdate \n
  *  CR1          TAUDIS        LL_HRTIM_IsEnabledUpdate \n
  *  CR1          TBUDIS        LL_HRTIM_IsEnabledUpdate \n
  *  CR1          TCUDIS        LL_HRTIM_IsEnabledUpdate \n
  *  CR1          TDUDIS        LL_HRTIM_IsEnabledUpdate \n
  *  CR1          TEUDIS        LL_HRTIM_IsEnabledUpdate \n
  *  CR1          TFUDIS        LL_HRTIM_IsEnabledUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  *         @arg @ref LL_HRTIM_TIM_ALL
  * @retval 0U  At least one of the specified timers has update events disabled.
  * @retval 1U  Update events are enabled for all specified timers.
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledUpdate(const HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  uint32_t mask = (timers >> HRTIM_MCR_MCEN_Pos) & LL_HRTIM_CR1_UDIS_MASK;
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.CR1, mask) != 0U) ? 0UL : 1UL);
}

/**
  * @brief  Force an immediate transfer from the preload to the active register .
  * @rmtoll
  *  CR2          MSWU          LL_HRTIM_ForceUpdate \n
  *  CR2          TASWU         LL_HRTIM_ForceUpdate \n
  *  CR2          TBSWU         LL_HRTIM_ForceUpdate \n
  *  CR2          TCSWU         LL_HRTIM_ForceUpdate \n
  *  CR2          TDSWU         LL_HRTIM_ForceUpdate \n
  *  CR2          TESWU         LL_HRTIM_ForceUpdate \n
  *  CR2          TFSWU         LL_HRTIM_ForceUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  *         @arg @ref LL_HRTIM_TIM_ALL
  * @note Any pending update request is cancelled.
  */
__STATIC_INLINE void LL_HRTIM_ForceUpdate(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.CR2, ((timers >> HRTIM_MCR_MCEN_Pos) & LL_HRTIM_CR2_SWUPD_MASK));
}

/**
  * @brief  Reset the HRTIM timer(s) counter.
  * @rmtoll
  *  CR2          MRST          LL_HRTIM_CounterReset \n
  *  CR2          TARST         LL_HRTIM_CounterReset \n
  *  CR2          TBRST         LL_HRTIM_CounterReset \n
  *  CR2          TCRST         LL_HRTIM_CounterReset \n
  *  CR2          TDRST         LL_HRTIM_CounterReset \n
  *  CR2          TERST         LL_HRTIM_CounterReset \n
  *  CR2          TFRST         LL_HRTIM_CounterReset
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  *         @arg @ref LL_HRTIM_TIM_ALL
  */
__STATIC_INLINE void LL_HRTIM_CounterReset(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.CR2,
                (((timers >> HRTIM_MCR_MCEN_Pos) << HRTIM_CR2_MRST_Pos) & LL_HRTIM_CR2_SWRST_MASK));
}

/**
  * @brief  enable the swap of the Timer output.
  * @rmtoll
  *  CR2          SWPA         LL_HRTIM_EnableSwapOutputs \n
  *  CR2          SWPB         LL_HRTIM_EnableSwapOutputs \n
  *  CR2          SWPC         LL_HRTIM_EnableSwapOutputs \n
  *  CR2          SWPD         LL_HRTIM_EnableSwapOutputs \n
  *  CR2          SWPE         LL_HRTIM_EnableSwapOutputs \n
  *  CR2          SWPF         LL_HRTIM_EnableSwapOutputs
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This bit is not significant when the Push-pull mode is enabled (PSHPLL = 1)
  * @note   The HRTIM_SETA1R and HRTIM_RSTA1R are coding for the output 2.
  *         The HRTIM_SETA2R and HRTIM_RSTA2R are coding for the output 1.
  */
__STATIC_INLINE void LL_HRTIM_EnableSwapOutputs(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.CR2,
                (((timers >> HRTIM_MCR_TACEN_Pos) << HRTIM_CR2_SWPA_Pos) & LL_HRTIM_CR2_SWAP_MASK));
}

/**
  * @brief  disable the swap of the Timer output.
  * @rmtoll
  *  CR2          SWPA         LL_HRTIM_DisableSwapOutputs\n
  *         CR2          SWPB         LL_HRTIM_DisableSwapOutputs \n
  *         CR2          SWPC         LL_HRTIM_DisableSwapOutputs \n
  *         CR2          SWPD         LL_HRTIM_DisableSwapOutputs \n
  *         CR2          SWPE         LL_HRTIM_DisableSwapOutputs \n
  *         CR2          SWPF         LL_HRTIM_DisableSwapOutputs
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This bit is not significant when the Push-pull mode is enabled (PSHPLL = 1)
  * @note   The HRTIM_SETA1R and HRTIM_RSTA1R are coding for the output 1.
  *         The the HRTIM_SETA2R and HRTIM_RSTA2R are coding for the output 2.
  */
__STATIC_INLINE void LL_HRTIM_DisableSwapOutputs(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.CR2,
                  (((timers >> HRTIM_MCR_TACEN_Pos) << HRTIM_CR2_SWPA_Pos) & LL_HRTIM_CR2_SWAP_MASK));
}

/**
  * @brief  reports the Timer Outputs swap position.
  * @rmtoll
  *  CR2          SWPA         LL_HRTIM_IsEnabledSwapOutputs \n
  *  CR2          SWPB         LL_HRTIM_IsEnabledSwapOutputs \n
  *  CR2          SWPC         LL_HRTIM_IsEnabledSwapOutputs \n
  *  CR2          SWPD         LL_HRTIM_IsEnabledSwapOutputs \n
  *  CR2          SWPE         LL_HRTIM_IsEnabledSwapOutputs \n
  *  CR2          SWPF         LL_HRTIM_IsEnabledSwapOutputs
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This bit is not significant when the Push-pull mode is enabled (PSHPLL = 1)
  * @retval
  *         0: HRTIM_SETA1R and HRTIM_RSTA1R are coding for the output 1,
  *            HRTIM_SETA2R and HRTIM_RSTA2R are coding for the output 2
  *         1: HRTIM_SETA1R and HRTIM_RSTA1R are coding for the output 2,
  *            HRTIM_SETA2R and HRTIM_RSTA2R are coding for the output 1
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledSwapOutputs(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = ((STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos) & 0x7U);

  return (STM32_READ_BIT(hrtimx->sCommonRegs.CR2,
                         (uint32_t)(HRTIM_CR2_SWPA) << itim) >> ((HRTIM_CR2_SWPA_Pos + itim)));
}

/**
  * @brief  Enable the HRTIM timer(s) output(s) .
  * @rmtoll
  *  OENR         TA1OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TA2OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TB1OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TB2OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TC1OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TC2OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TD1OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TD2OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TE1OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TE2OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TF1OEN        LL_HRTIM_EnableOutput \n
  *  OENR         TF2OEN        LL_HRTIM_EnableOutput
  * @param  hrtimx High Resolution Timer instance
  * @param  outputs This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  *         @arg @ref LL_HRTIM_OUTPUT_ALL
  */
__STATIC_INLINE void LL_HRTIM_EnableOutput(HRTIM_TypeDef *hrtimx, uint32_t outputs)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.OENR, (outputs & LL_HRTIM_OENR_OEN_MASK));
}

/**
  * @brief  Disable the HRTIM timer(s) output(s) .
  * @rmtoll
  *  OENR         TA1OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TA2OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TB1OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TB2OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TC1OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TC2OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TD1OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TD2OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TE1OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TE2OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TF1OEN        LL_HRTIM_DisableOutput \n
  *  OENR         TF2OEN        LL_HRTIM_DisableOutput
  * @param  hrtimx High Resolution Timer instance
  * @param  outputs This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  *         @arg @ref LL_HRTIM_OUTPUT_ALL
  */
__STATIC_INLINE void LL_HRTIM_DisableOutput(HRTIM_TypeDef *hrtimx, uint32_t outputs)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ODISR, (outputs & LL_HRTIM_OENR_ODIS_MASK));
}

/**
  * @brief  Indicates whether the HRTIM timer output is enabled.
  * @rmtoll
  *  OENR         TA1OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TA2OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TB1OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TB2OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TC1OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TC2OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TD1OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TD2OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TE1OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TE2OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TF1OEN        LL_HRTIM_IsEnabledOutput \n
  *  OENR         TF2OEN        LL_HRTIM_IsEnabledOutput
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval State of TxyOEN bit in HRTIM_OENR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledOutput(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.OENR, output) == output) ? 1UL : 0UL);
}

/**
  * @brief  Get the output disable state.
  * @rmtoll
  *  ODSR        TA1ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TA2ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TB1ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TB2ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TC1ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TC2ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TD1ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TD2ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TE1ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TE2ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TF1ODS        LL_HRTIM_GetOutputDisableState \n
  *  ODSR        TF2ODS        LL_HRTIM_GetOutputDisableState
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval State of TxyODS bit in HRTIM_ODSR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetOutputDisableState(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ODSR, output) == output) ? 1UL : 0UL);
}

/**
  * @brief  Configure an ADC trigger.
  * @rmtoll
  *  CR1          ADC1USRC        LL_HRTIM_ConfigADCTrig \n
  *  CR1          ADC2USRC        LL_HRTIM_ConfigADCTrig \n
  *  CR1          ADC3USRC        LL_HRTIM_ConfigADCTrig \n
  *  CR1          ADC4USRC        LL_HRTIM_ConfigADCTrig \n
  *  ADCUR        AD5USRC         LL_HRTIM_ConfigADCTrig \n
  *  ADCUR        AD6USRC         LL_HRTIM_ConfigADCTrig \n
  *  ADCUR        AD7USRC         LL_HRTIM_ConfigADCTrig \n
  *  ADCUR        AD8USRC         LL_HRTIM_ConfigADCTrig \n
  *  ADCUR        AD9USRC         LL_HRTIM_ConfigADCTrig \n
  *  ADCUR        AD10USRC        LL_HRTIM_ConfigADCTrig \n
  *  ADCER        ADC5TRG         LL_HRTIM_ConfigADCTrig \n
  *  ADCER        ADC6TRG         LL_HRTIM_ConfigADCTrig \n
  *  ADCER        ADC7TRG         LL_HRTIM_ConfigADCTrig \n
  *  ADCER        ADC8TRG         LL_HRTIM_ConfigADCTrig \n
  *  ADCER        ADC9TRG         LL_HRTIM_ConfigADCTrig \n
  *  ADCER        ADC10TRG        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1MC1         LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1MC2         LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1MC3         LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1MC4         LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1MPER        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1EEV1        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1EEV2        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1EEV3        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1EEV4        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1EEV5        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TFC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TAC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TAC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TAPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TARST       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TFC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TBC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TBC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TBPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TBRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TFC4        LL_HRTIM_ConfigADCTrig  \n
  *  ADC1R        ADC1TCC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TCC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TCPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TFPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TDC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TDC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TDPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TFRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TEC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TEC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC1R        ADC1TEPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2MC1         LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2MC2         LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2MC3         LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2MC4         LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2MPER        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2EEV6        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2EEV7        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2EEV8        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2EEV9        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2EEV10       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TAC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TFC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TAC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TAPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TBC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TFC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TBC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TBPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TCC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TFC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TCC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TCPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TCRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TDC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TFPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TDC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TDPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TDRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TEC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TEC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TEC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC2R        ADC2TERST       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3MC1         LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3MC2         LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3MC3         LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3MC4         LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3MPER        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3EEV1        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3EEV2        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3EEV3        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3EEV4        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3EEV5        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TFC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TAC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TAC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TAPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TARST       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TFC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TBC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TBC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TBPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TBRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TFC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TCC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TCC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TCPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TFPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TDC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TDC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TDPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TFRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TEC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TEC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC3R        ADC3TEPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4MC1         LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4MC2         LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4MC3         LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4MC4         LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4MPER        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4EEV6        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4EEV7        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4EEV8        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4EEV9        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4EEV10       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TAC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TFC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TAC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TAPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TBC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TFC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TBC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TBPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TCC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TFC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TCC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TCPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TCRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TDC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TFPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TDC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TDPER       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TDRST       LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TEC2        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TEC3        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TEC4        LL_HRTIM_ConfigADCTrig \n
  *  ADC4R        ADC4TERST       LL_HRTIM_ConfigADCTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  adc_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG1
  *         @arg @ref LL_HRTIM_ADCTRIG2
  *         @arg @ref LL_HRTIM_ADCTRIG3
  *         @arg @ref LL_HRTIM_ADCTRIG4
  *         @arg @ref LL_HRTIM_ADCTRIG5
  *         @arg @ref LL_HRTIM_ADCTRIG6
  *         @arg @ref LL_HRTIM_ADCTRIG7
  *         @arg @ref LL_HRTIM_ADCTRIG8
  *         @arg @ref LL_HRTIM_ADCTRIG9
  *         @arg @ref LL_HRTIM_ADCTRIG10
  * @param  update_source This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_MASTER
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMA
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMB
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMC
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMD
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIME
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMF
  * @param  trigger_src This parameter can be a combination of the following values:
  *
  *         For ADC trigger 1 and ADC trigger 3:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_NONE
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV5
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIME_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_RESET
  *
  *         For ADC trigger 2 and ADC trigger 4:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_NONE
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV6
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV7
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV8
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV9
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV10
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_PERIOD
  *
  *         For ADC trigger 5, ADC trigger 7 and ADC trigger 9 this parameter
  *         can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV5
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIME_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_RESET
  *
  *         For ADC trigger 6, ADC trigger 8 and ADC trigger 10 this parameter
  *         can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV6
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV7
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV8
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV9
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV10
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_PERIOD
  */
__STATIC_INLINE void LL_HRTIM_ConfigADCTrig(const HRTIM_TypeDef *hrtimx, uint32_t adc_trigger, uint32_t update_source,
                                            uint32_t trigger_src)
{
  __IOM uint32_t *padcur = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.CR1) +
                                                         LL_HRTIM_REG_OFFSET_TAB_ADCUR[adc_trigger]));
  __IOM uint32_t *padcer = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.ADC1R) +
                                                         LL_HRTIM_REG_OFFSET_TAB_ADCxR[adc_trigger]));
  STM32_MODIFY_REG(*padcur,
                   LL_HRTIM_REG_MASK_TAB_ADCUR[adc_trigger],
                   (update_source << LL_HRTIM_REG_SHIFT_TAB_ADCUR[adc_trigger]));
  STM32_MODIFY_REG(*padcer,
                   LL_HRTIM_REG_MASK_TAB_ADCER[adc_trigger],
                   (trigger_src << LL_HRTIM_REG_SHIFT_TAB_ADCER[adc_trigger]));
}

/**
  * @brief  Associate the ADCx trigger to a timer triggering the update of the HRTIM_ADCxR register.
  * @rmtoll
  *  CR1          ADC1USRC         LL_HRTIM_SetADCTrigUpdate \n
  *  CR1          ADC2USRC         LL_HRTIM_SetADCTrigUpdate \n
  *  CR1          ADC3USRC         LL_HRTIM_SetADCTrigUpdate \n
  *  CR1          ADC4USRC         LL_HRTIM_SetADCTrigUpdate \n
  *  ADCUR        AD5USRC          LL_HRTIM_SetADCTrigUpdate \n
  *  ADCUR        AD6USRC          LL_HRTIM_SetADCTrigUpdate \n
  *  ADCUR        AD7USRC          LL_HRTIM_SetADCTrigUpdate \n
  *  ADCUR        AD8USRC          LL_HRTIM_SetADCTrigUpdate \n
  *  ADCUR        AD9USRC          LL_HRTIM_SetADCTrigUpdate \n
  *  ADCUR        AD10USRC         LL_HRTIM_SetADCTrigUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  adc_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG1
  *         @arg @ref LL_HRTIM_ADCTRIG2
  *         @arg @ref LL_HRTIM_ADCTRIG3
  *         @arg @ref LL_HRTIM_ADCTRIG4
  *         @arg @ref LL_HRTIM_ADCTRIG5
  *         @arg @ref LL_HRTIM_ADCTRIG6
  *         @arg @ref LL_HRTIM_ADCTRIG7
  *         @arg @ref LL_HRTIM_ADCTRIG8
  *         @arg @ref LL_HRTIM_ADCTRIG9
  *         @arg @ref LL_HRTIM_ADCTRIG10
  * @param  update_source This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_MASTER
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMA
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMB
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMC
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMD
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIME
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMF
  * @note When the preload is disabled in the source timer, the HRTIM_ADCxR
  *       registers are not preloaded either: a write access will result in an
  *       immediate update of the trigger source.
  */
__STATIC_INLINE void LL_HRTIM_SetADCTrigUpdate(const HRTIM_TypeDef *hrtimx, uint32_t adc_trigger,
                                               uint32_t update_source)
{
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.CR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_ADCUR[adc_trigger]));
  STM32_MODIFY_REG(*preg,
                   LL_HRTIM_REG_MASK_TAB_ADCUR[adc_trigger],
                   (update_source << LL_HRTIM_REG_SHIFT_TAB_ADCUR[adc_trigger]));
}

/**
  * @brief  Get the source timer triggering the update of the HRTIM_ADCxR register.
  * @rmtoll
  *  ADCUR        AD5USRC         LL_HRTIM_GetADCTrigUpdate \n
  *  ADCUR        AD6USRC         LL_HRTIM_GetADCTrigUpdate \n
  *  ADCUR        AD7USRC         LL_HRTIM_GetADCTrigUpdate \n
  *  ADCUR        AD8USRC         LL_HRTIM_GetADCTrigUpdate \n
  *  ADCUR        AD9USRC         LL_HRTIM_GetADCTrigUpdate \n
  *  ADCUR        AD10USRC        LL_HRTIM_GetADCTrigUpdate \n
  *  CR1          ADC1USRC        LL_HRTIM_GetADCTrigUpdate \n
  *  CR1          ADC2USRC        LL_HRTIM_GetADCTrigUpdate \n
  *  CR1          ADC3USRC        LL_HRTIM_GetADCTrigUpdate \n
  *  CR1          ADC4USRC        LL_HRTIM_GetADCTrigUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  adc_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG1
  *         @arg @ref LL_HRTIM_ADCTRIG2
  *         @arg @ref LL_HRTIM_ADCTRIG3
  *         @arg @ref LL_HRTIM_ADCTRIG4
  *         @arg @ref LL_HRTIM_ADCTRIG5
  *         @arg @ref LL_HRTIM_ADCTRIG6
  *         @arg @ref LL_HRTIM_ADCTRIG7
  *         @arg @ref LL_HRTIM_ADCTRIG8
  *         @arg @ref LL_HRTIM_ADCTRIG9
  *         @arg @ref LL_HRTIM_ADCTRIG10
  * @retval update_source Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_MASTER
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMA
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMB
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMC
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMD
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIME
  *         @arg @ref LL_HRTIM_ADCTRIG_UPDATE_TIMF
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetADCTrigUpdate(const HRTIM_TypeDef *hrtimx, uint32_t adc_trigger)
{
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.CR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_ADCUR[adc_trigger]));
  return (STM32_READ_BIT(*preg,
                         (LL_HRTIM_REG_MASK_TAB_ADCUR[adc_trigger])) >> LL_HRTIM_REG_SHIFT_TAB_ADCUR[adc_trigger]);
}

/**
  * @brief  Specify which events (timer events and/or external events) are used as triggers for ADC conversion.
  * @rmtoll
  * ADCER        ADC5TRG         LL_HRTIM_SetADCTrigSrc \n
  * ADCER        ADC6TRG         LL_HRTIM_SetADCTrigSrc \n
  * ADCER        ADC7TRG         LL_HRTIM_SetADCTrigSrc \n
  * ADCER        ADC8TRG         LL_HRTIM_SetADCTrigSrc \n
  * ADCER        ADC9TRG         LL_HRTIM_SetADCTrigSrc \n
  * ADCER        ADC10TRG        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1MC1         LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1MC2         LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1MC3         LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1MC4         LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1MPER        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1EEV1        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1EEV2        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1EEV3        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1EEV4        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1EEV5        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TFC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TAC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TAC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TAPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TARST       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TFC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TBC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TBC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TBPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TBRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TFC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TCC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TCC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TCPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TFPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TDC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TDC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TDPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TFRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TEC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TEC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC1R        ADC1TEPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2MC1         LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2MC2         LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2MC3         LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2MC4         LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2MPER        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2EEV6        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2EEV7        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2EEV8        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2EEV9        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2EEV10       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TAC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TFC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TAC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TAPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TBC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TFC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TBC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TBPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TCC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TFC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TCC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TCPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TCRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TDC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TFPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TDC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TDPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TDRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TEC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TEC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TEC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC2R        ADC2TERST       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3MC1         LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3MC2         LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3MC3         LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3MC4         LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3MPER        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3EEV1        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3EEV2        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3EEV3        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3EEV4        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3EEV5        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TFC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TAC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TAC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TAPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TARST       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TFC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TBC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TBC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TBPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TBRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TFC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TCC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TCC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TCPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TFPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TDC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TDC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TDPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TFRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TEC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TEC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC3R        ADC3TEPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4MC1         LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4MC2         LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4MC3         LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4MC4         LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4MPER        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4EEV6        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4EEV7        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4EEV8        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4EEV9        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4EEV10       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TAC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TFC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TAC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TAPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TBC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TFC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TBC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TBPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TCC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TFC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TCC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TCPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TCRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TDC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TFPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TDC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TDPER       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TDRST       LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TEC2        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TEC3        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TEC4        LL_HRTIM_SetADCTrigSrc \n
  * ADC4R        ADC4TERST       LL_HRTIM_SetADCTrigSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  adc_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG1
  *         @arg @ref LL_HRTIM_ADCTRIG2
  *         @arg @ref LL_HRTIM_ADCTRIG3
  *         @arg @ref LL_HRTIM_ADCTRIG4
  *         @arg @ref LL_HRTIM_ADCTRIG5
  *         @arg @ref LL_HRTIM_ADCTRIG6
  *         @arg @ref LL_HRTIM_ADCTRIG7
  *         @arg @ref LL_HRTIM_ADCTRIG8
  *         @arg @ref LL_HRTIM_ADCTRIG9
  *         @arg @ref LL_HRTIM_ADCTRIG10
  * @param  trigger_src
  *         For ADC trigger 1 and ADC trigger 3 this parameter can be a
  *         combination of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_NONE
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV5
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMA_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMB_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIME_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMF_RESET
  *
  *         For ADC trigger 2 and ADC trigger 4 this parameter can be a
  *         combination of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_NONE
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV6
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV7
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV8
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV9
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV10
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMC_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMD_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIME_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMF_PERIOD
  *
  *         For ADC trigger 5, ADC trigger 7 and ADC trigger 9 this parameter
  *         can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV5
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMA_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMB_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIME_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMF_RESET
  *
  *         For ADC trigger 6, ADC trigger 8 and ADC trigger 10 this parameter
  *         can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV6
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV7
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV8
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV9
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV10
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMA_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMA_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMB_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMB_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMC_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMD_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIME_RESET
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMF_PERIOD
  */
__STATIC_INLINE void LL_HRTIM_SetADCTrigSrc(const HRTIM_TypeDef *hrtimx, uint32_t adc_trigger, uint32_t trigger_src)
{
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.ADC1R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_ADCxR[adc_trigger]));
  STM32_MODIFY_REG(*preg,
                   LL_HRTIM_REG_MASK_TAB_ADCER[adc_trigger],
                   (trigger_src << LL_HRTIM_REG_SHIFT_TAB_ADCER[adc_trigger]));
}

/**
  * @brief  Indicate which events (timer events and/or external events) are currently used as triggers for ADC
  *         conversion.
  * @rmtoll
  *  ADC1R        ADC1MC1         LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1MC2         LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1MC3         LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1MC4         LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1MPER        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1EEV1        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1EEV2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1EEV3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1EEV4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1EEV5        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TFC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TAC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TAC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TAPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TARST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TFC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TBC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TBC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TBPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TBRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TFC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TCC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TCC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TCPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TFPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TDC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TDC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TDPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TFRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TEC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TEC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC1R        ADC1TEPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2MC1         LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2MC2         LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2MC3         LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2MC4         LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2MPER        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2EEV6        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2EEV7        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2EEV8        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2EEV9        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2EEV10       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TAC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TFC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TAC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TAPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TBC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TFC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TBC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TBPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TCC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TFC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TCC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TCPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TCRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TDC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TFPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TDC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TDPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TDRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TEC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TEC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TEC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC2R        ADC2TERST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3MC1         LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3MC2         LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3MC3         LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3MC4         LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3MPER        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3EEV1        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3EEV2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3EEV3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3EEV4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3EEV5        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TFC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TAC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TAC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TAPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TARST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TFC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TBC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TBC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TBPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TBRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TFC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TCC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TCC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TCPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TFPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TDC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TDC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TDPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TFRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TEC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TEC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC3R        ADC3TEPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4MC1         LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4MC2         LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4MC3         LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4MC4         LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4MPER        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4EEV6        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4EEV7        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4EEV8        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4EEV9        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4EEV10       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TAC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TFC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TAC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TAPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TBC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TFC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TBC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TBPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TCC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TFC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TCC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TCPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TCRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TDC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TFPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TDC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TDPER       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TDRST       LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TEC2        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TEC3        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TEC4        LL_HRTIM_GetADCTrigSrc \n
  *  ADC4R        ADC4TERST       LL_HRTIM_GetADCTrigSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  adc_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG1
  *         @arg @ref LL_HRTIM_ADCTRIG2
  *         @arg @ref LL_HRTIM_ADCTRIG3
  *         @arg @ref LL_HRTIM_ADCTRIG4
  *         @arg @ref LL_HRTIM_ADCTRIG5
  *         @arg @ref LL_HRTIM_ADCTRIG6
  *         @arg @ref LL_HRTIM_ADCTRIG7
  *         @arg @ref LL_HRTIM_ADCTRIG8
  *         @arg @ref LL_HRTIM_ADCTRIG9
  *         @arg @ref LL_HRTIM_ADCTRIG10
  * @retval trigger_src This parameter can be a combination of the following values:
  *
  *         For ADC trigger 1 and ADC trigger 3 this parameter can be a
  *         combination of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_NONE
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_EEV5
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMACMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMACMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMAPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMARST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMBCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMBCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMBPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMBRST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMCCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMCCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMCPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMDCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMDCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMDPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMECMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMECMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMEPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMFCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMFCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMFCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMFPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC13_TIMFRST
  *
  *         For ADC trigger 2 and ADC trigger 4 this parameter can be a
  *         combination of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_NONE
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV6
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV7
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV8
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV9
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_EEV10
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMACMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMACMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMAPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMBCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMBCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMBPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMCCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMCCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMCPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMCRST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMDCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMDCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMDPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMDRST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMECMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMECMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMECMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMERST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMFCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMFCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMFCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC24_TIMFPER
  *
  *         For ADC trigger 5, ADC trigger 7 and ADC trigger 9 this parameter
  *         can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_EEV5
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMACMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMACMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMAPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMARST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMBCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMBCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMBPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMBRST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMCCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMCCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMCPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMDCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMDCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMDPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMECMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMECMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMEPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMFCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMFCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMFCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMFPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC579_TIMFRST
  *
  *         For ADC trigger 6, ADC trigger 8 and ADC trigger 10 this parameter
  *         can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP1
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_CMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV6
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV7
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV8
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV9
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_EEV10
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMACMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMACMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMAPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMBCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMBCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMBPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMCCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMCCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMCPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMCRST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMDCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMDCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMDPER
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMDRST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMECMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMECMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMECMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMERST
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMFCMP2
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMFCMP3
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMFCMP4
  *         @arg @ref LL_HRTIM_ADCTRIG_SRC6810_TIMFPER
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetADCTrigSrc(const HRTIM_TypeDef *hrtimx, uint32_t adc_trigger)
{
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.ADC1R) +
                                                             LL_HRTIM_REG_OFFSET_TAB_ADCxR[adc_trigger]));
  return (STM32_READ_BIT(*preg,
                         (LL_HRTIM_REG_MASK_TAB_ADCER[adc_trigger])) >> LL_HRTIM_REG_SHIFT_TAB_ADCER[adc_trigger]);
}

/**
  * @brief  Select the ADC post scaler.
  * @rmtoll
  *  ADCPS2       ADC10PSC        LL_HRTIM_SetADCPostScaler \n
  *  ADCPS2       ADC9PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS2       ADC8PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS2       ADC7PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS2       ADC6PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS1       ADC5PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS1       ADC4PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS1       ADC3PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS1       ADC2PSC         LL_HRTIM_SetADCPostScaler \n
  *  ADCPS1       ADC1PSC         LL_HRTIM_SetADCPostScaler
  * @param  hrtimx High Resolution Timer instance
  * @param  adc_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG1
  *         @arg @ref LL_HRTIM_ADCTRIG2
  *         @arg @ref LL_HRTIM_ADCTRIG3
  *         @arg @ref LL_HRTIM_ADCTRIG4
  *         @arg @ref LL_HRTIM_ADCTRIG5
  *         @arg @ref LL_HRTIM_ADCTRIG6
  *         @arg @ref LL_HRTIM_ADCTRIG7
  *         @arg @ref LL_HRTIM_ADCTRIG8
  *         @arg @ref LL_HRTIM_ADCTRIG9
  *         @arg @ref LL_HRTIM_ADCTRIG10
  * @param  adc_post_scaler This parameter can be a number between Min_Data=0 and Max_Data=31
  * @note This function allows to adjust each ADC trigger rate individually.
  * @note In center-aligned mode, the ADC trigger rate is also dependent on
  *       ADROM[1:0] bitfield, programmed in the source timer
  *       (see function @ref LL_HRTIM_TIM_SetADCRollOverMode)
  * @note This function allows to adjust each ADC trigger rate individually.
  * @note In center-aligned mode, the ADC trigger rate is also dependent on
  *       ADROM[1:0] bitfield, programmed in the source timer
  *       (see function @ref LL_HRTIM_TIM_SetADCRollOverMode)
  */
__STATIC_INLINE void LL_HRTIM_SetADCPostScaler(HRTIM_TypeDef *hrtimx, uint32_t adc_trigger, uint32_t adc_post_scaler)
{

  uint64_t mask = (uint64_t)(HRTIM_ADCPS1_ADC1PSC) << (REG_OFFSET_TAB_ADCPSx[adc_trigger]);
  uint64_t ratio = (uint64_t)(adc_post_scaler) << (REG_OFFSET_TAB_ADCPSx[adc_trigger]);

  STM32_MODIFY_REG(hrtimx->sCommonRegs.ADCPS1, (uint32_t)mask, (uint32_t)ratio);
  STM32_MODIFY_REG(hrtimx->sCommonRegs.ADCPS2, (uint32_t)(mask >> 32U), (uint32_t)(ratio >> 32U));

}

/**
  * @brief  Get the selected ADC post scaler.
  * @rmtoll
  *  ADCPS2       ADC10PSC        LL_HRTIM_GetADCPostScaler \n
  *  ADCPS2       ADC9PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS2       ADC8PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS2       ADC7PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS2       ADC6PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS1       ADC5PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS1       ADC4PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS1       ADC3PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS1       ADC2PSC         LL_HRTIM_GetADCPostScaler \n
  *  ADCPS1       ADC1PSC         LL_HRTIM_GetADCPostScaler
  * @param  hrtimx High Resolution Timer instance
  * @param  adc_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG1
  *         @arg @ref LL_HRTIM_ADCTRIG2
  *         @arg @ref LL_HRTIM_ADCTRIG3
  *         @arg @ref LL_HRTIM_ADCTRIG4
  *         @arg @ref LL_HRTIM_ADCTRIG5
  *         @arg @ref LL_HRTIM_ADCTRIG6
  *         @arg @ref LL_HRTIM_ADCTRIG7
  *         @arg @ref LL_HRTIM_ADCTRIG8
  *         @arg @ref LL_HRTIM_ADCTRIG9
  *         @arg @ref LL_HRTIM_ADCTRIG10
  * @retval  adc_post_scaler This parameter can be a number between Min_Data=0 and Max_Data=31.
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetADCPostScaler(const HRTIM_TypeDef *hrtimx, uint32_t adc_trigger)
{

  uint32_t reg1 = STM32_READ_REG(hrtimx->sCommonRegs.ADCPS1);
  uint32_t reg2 = STM32_READ_REG(hrtimx->sCommonRegs.ADCPS2);

  uint64_t mask = (uint64_t)(HRTIM_ADCPS1_ADC1PSC) << (REG_OFFSET_TAB_ADCPSx[adc_trigger]);
  uint64_t ratio = (uint64_t)(reg1) | ((uint64_t)(reg2) << 32U);

  return (uint32_t)((ratio & mask) >> (REG_OFFSET_TAB_ADCPSx[adc_trigger])) ;

}

/**
  * @brief  Configure the DLL calibration rate.
  * @rmtoll
  *  DLLCR        CALRTE        LL_HRTIM_SetDLLCalibrationRate
  * @param  hrtimx High Resolution Timer instance
  * @param  calibration_rate This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DLLCALIBRATION_RATE_0
  *         @arg @ref LL_HRTIM_DLLCALIBRATION_RATE_1
  *         @arg @ref LL_HRTIM_DLLCALIBRATION_RATE_2
  *         @arg @ref LL_HRTIM_DLLCALIBRATION_RATE_3
  */
__STATIC_INLINE void LL_HRTIM_SetDLLCalibrationRate(HRTIM_TypeDef *hrtimx, uint32_t calibration_rate)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.DLLCR, HRTIM_DLLCR_CALRTE, calibration_rate);
}

/**
  * @brief  Enable DLL periodic calibration.
  * @rmtoll
  *  DLLCR        CALEN         LL_HRTIM_EnablePeriodicDLLCalibration
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnablePeriodicDLLCalibration(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.DLLCR, HRTIM_DLLCR_CALEN);
}

/**
  * @brief  Disable DLL periodic calibration.
  * @rmtoll
  *  DLLCR        CALEN         LL_HRTIM_DisablePeriodicDLLCalibration
  * @param  hrtimx High Resolution Timer instance

  */
__STATIC_INLINE void LL_HRTIM_DisablePeriodicDLLCalibration(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.DLLCR, HRTIM_DLLCR_CALEN);
}

/**
  * @brief  Indicate whether DLL periodic calibration is enabled.
  * @rmtoll
  *  DLLCR        CALEN         LL_HRTIM_IsEnabledPeriodicDLLCalibration
  * @param  hrtimx High Resolution Timer instance
  * @retval State of CALEN bit in HRTIM_DLLCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledPeriodicDLLCalibration(const HRTIM_TypeDef *hrtimx)
{
  return ((hrtimx->sCommonRegs.DLLCR == (HRTIM_DLLCR_CALEN)) ? 1UL : 0UL);
}

/**
  * @brief  Launch DLL calibration.
  * @rmtoll
  *  DLLCR        CAL           LL_HRTIM_StartDLLCalibration
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_StartDLLCalibration(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.DLLCR, HRTIM_DLLCR_CAL);
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_HRTIM_Timer_Control HRTIM_Timer_Control
  * @{
  */

/**
  * @brief  Enable timer(s) counter.
  * @rmtoll
  *  MDIER        TFCEN         LL_HRTIM_TIM_CounterEnable \n
  *  MDIER        TECEN         LL_HRTIM_TIM_CounterEnable \n
  *  MDIER        TDCEN         LL_HRTIM_TIM_CounterEnable \n
  *  MDIER        TCCEN         LL_HRTIM_TIM_CounterEnable \n
  *  MDIER        TBCEN         LL_HRTIM_TIM_CounterEnable \n
  *  MDIER        TACEN         LL_HRTIM_TIM_CounterEnable \n
  *  MDIER        MCEN          LL_HRTIM_TIM_CounterEnable
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  *         @arg @ref LL_HRTIM_TIM_ALL
  */
__STATIC_INLINE void LL_HRTIM_TIM_CounterEnable(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_SET_BIT(hrtimx->sMasterRegs.MCR, timers);
}

/**
  * @brief  Disable timer(s) counter.
  * @rmtoll
  *  MDIER        TFCEN         LL_HRTIM_TIM_CounterDisable \n
  *  MDIER        TECEN         LL_HRTIM_TIM_CounterDisable \n
  *  MDIER        TDCEN         LL_HRTIM_TIM_CounterDisable \n
  *  MDIER        TCCEN         LL_HRTIM_TIM_CounterDisable \n
  *  MDIER        TBCEN         LL_HRTIM_TIM_CounterDisable \n
  *  MDIER        TACEN         LL_HRTIM_TIM_CounterDisable \n
  *  MDIER        MCEN          LL_HRTIM_TIM_CounterDisable
  * @param  hrtimx High Resolution Timer instance
  * @param  timers This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  *         @arg @ref LL_HRTIM_TIM_ALL
  */
__STATIC_INLINE void LL_HRTIM_TIM_CounterDisable(HRTIM_TypeDef *hrtimx, uint32_t timers)
{
  STM32_CLEAR_BIT(hrtimx->sMasterRegs.MCR, timers);
}

/**
  * @brief  Indicate whether the timer counter is enabled.
  * @rmtoll
  *  MDIER        TFCEN         LL_HRTIM_TIM_IsCounterEnabled \n
  *  MDIER        TECEN         LL_HRTIM_TIM_IsCounterEnabled \n
  *  MDIER        TDCEN         LL_HRTIM_TIM_IsCounterEnabled \n
  *  MDIER        TCCEN         LL_HRTIM_TIM_IsCounterEnabled \n
  *  MDIER        TBCEN         LL_HRTIM_TIM_IsCounterEnabled \n
  *  MDIER        TACEN         LL_HRTIM_TIM_IsCounterEnabled \n
  *  MDIER        MCEN          LL_HRTIM_TIM_IsCounterEnabled
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCEN or TxCEN bit HRTIM_MCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsCounterEnabled(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  return ((STM32_READ_BIT(hrtimx->sMasterRegs.MCR, timer) == (timer)) ? 1UL : 0UL);
}

/**
  * @brief  Set the timer clock prescaler ratio.
  * @rmtoll
  *  MCR        CKPSC         LL_HRTIM_TIM_SetPrescaler \n
  *  TIMxCR     CKPSC         LL_HRTIM_TIM_SetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL32
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL16
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL8
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL4
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL2
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_DIV1
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_DIV2
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_DIV4
  * @note The counter clock equivalent frequency (CK_CNT) is equal to fHRCK / 2^CKPSC[2:0].
  * @note The prescaling ratio cannot be modified once the timer counter is enabled.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetPrescaler(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t prescaler)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR)
                                                       + LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_MCR_CKPSC, prescaler);
}

/**
  * @brief  Get the timer clock prescaler ratio.
  * @rmtoll
  *  MCR        CKPSC         LL_HRTIM_TIM_GetPrescaler \n
  *  TIMxCR     CKPSC         LL_HRTIM_TIM_GetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval prescaler Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL32
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL16
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL8
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL4
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_MUL2
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_DIV1
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_DIV2
  *         @arg @ref LL_HRTIM_PRESCALERRATIO_DIV4
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetPrescaler(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MCR_CKPSC));
}

/**
  * @brief  Set the counter operating mode mode (single-shot, continuous or re-triggerable).
  * @rmtoll
  *  MCR        CONT         LL_HRTIM_TIM_SetCounterMode \n
  *  MCR        RETRIG       LL_HRTIM_TIM_SetCounterMode \n
  *  TIMxCR     CONT         LL_HRTIM_TIM_SetCounterMode \n
  *  TIMxCR     RETRIG       LL_HRTIM_TIM_SetCounterMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  counter_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MODE_CONTINUOUS
  *         @arg @ref LL_HRTIM_MODE_SINGLESHOT
  *         @arg @ref LL_HRTIM_MODE_SINGLESHOT_RETRIGGERABLE
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCounterMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t counter_mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, (HRTIM_TIMxCR_RETRIG | HRTIM_MCR_CONT), counter_mode);
}

/**
  * @brief  Get the counter operating mode mode.
  * @rmtoll
  *  MCR        CONT         LL_HRTIM_TIM_GetCounterMode \n
  *  MCR        RETRIG       LL_HRTIM_TIM_GetCounterMode \n
  *  TIMxCR     CONT         LL_HRTIM_TIM_GetCounterMode \n
  *  TIMxCR     RETRIG       LL_HRTIM_TIM_GetCounterMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval counter_mode Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_MODE_CONTINUOUS
  *         @arg @ref LL_HRTIM_MODE_SINGLESHOT
  *         @arg @ref LL_HRTIM_MODE_SINGLESHOT_RETRIGGERABLE
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCounterMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, (HRTIM_MCR_RETRIG | HRTIM_MCR_CONT)));
}

/**
  * @brief  Enable the half duty-cycle mode.
  * @rmtoll
  *  MCR        HALF         LL_HRTIM_TIM_EnableHalfMode \n
  *  TIMxCR     HALF         LL_HRTIM_TIM_EnableHalfMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note When the half mode is enabled, HRTIM_MCMP1R (or HRTIM_CMP1xR)
  *       active register is automatically updated with HRTIM_MPER/2
  *       (or HRTIM_PERxR/2) value when HRTIM_MPER (or HRTIM_PERxR) register is written.
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableHalfMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MCR_HALF);
}

/**
  * @brief  Disable the half duty-cycle mode.
  * @rmtoll
  *  MCR        HALF         LL_HRTIM_TIM_DisableHalfMode \n
  *  TIMxCR     HALF         LL_HRTIM_TIM_DisableHalfMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableHalfMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MCR_HALF);
  STM32_CLEAR_BIT(*preg, HRTIM_MCR_INTLVD << LL_HRTIM_REG_SHIFT_TAB_INTLVD[itim]);
}

/**
  * @brief  Indicate whether half duty-cycle mode is enabled for a given timer.
  * @rmtoll
  *  MCR        HALF         LL_HRTIM_TIM_IsEnabledHalfMode \n
  *  TIMxCR     HALF         LL_HRTIM_TIM_IsEnabledHalfMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of HALF bit in HRTIM_MCR or HRTIM_TIMxCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledHalfMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MCR_HALF) == (HRTIM_MCR_HALF)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Re-Syncronisation Update.
  * @rmtoll
  *  TIMxCR     RSYNCU         LL_HRTIM_TIM_EnableResyncUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   The update coming from adjacent timers (when MSTU, TAU, TBU, TCU, TDU, TEU, TFU bit is set)
  *         or from a software update (TxSWU bit) is taken into account on the following reset/roll-over.
  * @note   LL_HRTIM_ForceUpdate must be called prior programming the synchronization mode to force
  *         immediate update of the slave timer registers.
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableResyncUpdate(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxCR_RSYNCU);
  /* This bit is significant only when UPDGAT[3:0] = 0000, it is ignored otherwise */
}

/**
  * @brief  Disable the Re-Syncronisation Update.
  * @rmtoll
  *  TIMxCR     RSYNCU         LL_HRTIM_TIM_DisableResyncUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   The update coming from adjacent timers (when MSTU, TAU, TBU, TCU, TDU, TEU, TFU bit is set)
  *         or from a software update (TxSWU bit) is taken into account immediately.
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableResyncUpdate(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  STM32_CLEAR_BIT(*preg, HRTIM_TIMxCR_RSYNCU);
  /* This bit is significant only when UPDGAT[3:0] = 0000, it is ignored otherwise */
}

/**
  * @brief  Indicate whether the Re-Syncronisation Update is enabled.
  * @rmtoll
  *  TIMxCR     RSYNCU         LL_HRTIM_TIM_IsEnabledResyncUpdate
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This bit specifies whether update source coming outside
  *         from the timing unit must be synchronized
  * @retval State of RSYNC bit in HRTIM_TIMxCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledResyncUpdate(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxCR_RSYNCU) == (HRTIM_TIMxCR_RSYNCU)) ? 1UL : 0UL);
  /* This bit is significant only when UPDGAT[3:0] = 0000, it is ignored otherwise */
}

/**
  * @brief  set the Interleaved mode.
  * @rmtoll
  *  MCR        HALF      LL_HRTIM_TIM_SetInterleavedMode \n
  *  MCR        INTLVD    LL_HRTIM_TIM_SetInterleavedMode \n
  *  TIMxCR     HALF      LL_HRTIM_TIM_SetInterleavedMode \n
  *  TIMxCR     INTLVD    LL_HRTIM_TIM_SetInterleavedMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  interleaved_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_DISABLE
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_DUAL
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_TRIPLE
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_QUAD
  * @note Interleaved mode complements the Half mode and helps the implementation of interleaved topologies.
  * @note When interleaved mode is enabled, the content of the compare registers is overridden.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetInterleavedMode(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                     uint32_t interleaved_mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  STM32_MODIFY_REG(*preg, LL_HRTIM_REG_MASK_TAB_INTLVD[itim],
                   ((interleaved_mode & HRTIM_MCR_HALF)
                    | ((interleaved_mode & HRTIM_MCR_INTLVD) << LL_HRTIM_REG_SHIFT_TAB_INTLVD[itim])));
}

/**
  * @brief  get the Interleaved configuration.
  * @rmtoll
  *  MCR        INTLVD         LL_HRTIM_TIM_GetInterleavedMode \n
  *  TIMxCR     INTLVD         LL_HRTIM_TIM_GetInterleavedMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note The interleaved Mode is Triple or Quad if HALF bit is disabled
  *              the interleaved Mode is dual if HALF bit is set,
  *              HRTIM_MCMP1R (or HRTIM_CMP1xR) active register is automatically updated
  *              with HRTIM_MPER/2 or HRTIM_MPER/4
  *       (or HRTIM_PERxR/2) value when HRTIM_MPER (or HRTIM_PERxR) register is written.
  * @retval interleaved_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_DISABLE
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_DUAL
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_TRIPLE
  *         @arg @ref LL_HRTIM_INTERLEAVED_MODE_QUAD
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetInterleavedMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  uint32_t Mode = STM32_READ_BIT(*preg, (LL_HRTIM_REG_MASK_TAB_INTLVD[itim]));
  return ((Mode & HRTIM_MCR_HALF) | ((Mode  >> LL_HRTIM_REG_SHIFT_TAB_INTLVD[itim]) &  HRTIM_MCR_INTLVD));
}

/**
  * @brief  Configure how the timer's counter reacts to a rising edge on the HRTIM_SCIN input.
  * @rmtoll
  *  MCR        SYNCSTRTM        LL_HRTIM_TIM_SetSynchroModeMode \n
  *  MCR        SYNCRSTM         LL_HRTIM_TIM_SetSynchroMode \n
  *  TIMxCR     SYNSTRTA         LL_HRTIM_TIM_SetSynchroMode \n
  *  TIMxCR     SYNSTRTA         LL_HRTIM_TIM_SetSynchroMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  synchro_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCHRO_DISABLE
  *         @arg @ref LL_HRTIM_SYNCHRO_START
  *         @arg @ref LL_HRTIM_SYNCHRO_RESET
  *         @arg @ref LL_HRTIM_SYNCHRO_RESET_AND_START
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetSynchroMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t synchro_mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IO uint32_t *preg = (__IO uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR)
                                                     + LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, (HRTIM_MCR_SYNCRSTM | HRTIM_MCR_SYNCSTRTM), synchro_mode);
}

/**
  * @brief  Configure how the timer's counter reacts to a rising edge on the HRTIM_SCIN input.
  * @rmtoll
  *  MCR        SYNCSTRTM        LL_HRTIM_TIM_GetSynchroModeMode \n
  *  MCR        SYNCRSTM         LL_HRTIM_TIM_GetSynchroMode \n
  *  TIMxCR     SYNSTRTA         LL_HRTIM_TIM_GetSynchroMode \n
  *  TIMxCR     SYNSTRTA         LL_HRTIM_TIM_GetSynchroMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval synchro This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_SYNCHRO_DISABLE
  *         @arg @ref LL_HRTIM_SYNCHRO_START
  *         @arg @ref LL_HRTIM_SYNCHRO_RESET
  *         @arg @ref LL_HRTIM_SYNCHRO_RESET_AND_START
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetSynchroMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IO uint32_t *preg = (__IO uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR)
                                                           + LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return STM32_READ_BIT(*preg, (HRTIM_MCR_SYNCRSTM | HRTIM_MCR_SYNCSTRTM));
}

/**
  * @brief  Enable the timer start when receiving a synchronization input event.
  * @rmtoll
  *  MCR        SYNCSTRTM        LL_HRTIM_TIM_EnableStartOnSync \n
  *  TIMxCR     SYNSTRTA         LL_HRTIM_TIM_EnableStartOnSync
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableStartOnSync(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR)
                                                       + LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MCR_SYNCSTRTM);
}

/**
  * @brief  Disable the timer start when receiving a synchronization input event.
  * @rmtoll
  *  MCR        SYNCSTRTM        LL_HRTIM_TIM_DisableStartOnSync \n
  *  TIMxCR     SYNSTRTA         LL_HRTIM_TIM_DisableStartOnSync
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableStartOnSync(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR)
                                                       + LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MCR_SYNCSTRTM);
}

/**
  * @brief  Indicate whether the timer start when receiving a synchronization input event.
  * @rmtoll
  *  MCR        SYNCSTRTM        LL_HRTIM_TIM_IsEnabledStartOnSync \n
  *  TIMxCR     SYNSTRTA         LL_HRTIM_TIM_IsEnabledStartOnSync
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of SYNCSTRTx bit in HRTIM_MCR or HRTIM_TIMxCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledStartOnSync(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MCR_SYNCSTRTM) == (HRTIM_MCR_SYNCSTRTM)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the timer reset when receiving a synchronization input event.
  * @rmtoll
  *  MCR        SYNCRSTM        LL_HRTIM_TIM_EnableResetOnSync \n
  *  TIMxCR     SYNCRSTA        LL_HRTIM_TIM_EnableResetOnSync
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableResetOnSync(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MCR_SYNCRSTM);
}

/**
  * @brief  Disable the timer reset when receiving a synchronization input event.
  * @rmtoll
  *  MCR        SYNCRSTM        LL_HRTIM_TIM_DisableResetOnSync \n
  *  TIMxCR     SYNCRSTA        LL_HRTIM_TIM_DisableResetOnSync
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableResetOnSync(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MCR_SYNCRSTM);
}

/**
  * @brief  Indicate whether the timer reset when receiving a synchronization input event.
  * @rmtoll
  *  MCR        SYNCRSTM        LL_HRTIM_TIM_IsEnabledResetOnSync \n
  *  TIMxCR     SYNCRSTA        LL_HRTIM_TIM_IsEnabledResetOnSync
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledResetOnSync(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MCR_SYNCRSTM) == (HRTIM_MCR_SYNCRSTM)) ? 1UL : 0UL);
}

/**
  * @brief  Set the HRTIM output the DAC synchronization event is generated on (DACtrigOutx).
  * @rmtoll
  *  MCR        DACSYNC        LL_HRTIM_TIM_SetDACTrig \n
  *  TIMxCR     DACSYNC        LL_HRTIM_TIM_SetDACTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  dac_trigger This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DACTRIG_NONE
  *         @arg @ref LL_HRTIM_DACTRIG_DACTRIGOUT1
  *         @arg @ref LL_HRTIM_DACTRIG_DACTRIGOUT2
  *         @arg @ref LL_HRTIM_DACTRIG_DACTRIGOUT3
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetDACTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t dac_trigger)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_MCR_DACSYNC, dac_trigger);
}

/**
  * @brief  Get the HRTIM output the DAC synchronization event is generated on (DACtrigOutx).
  * @rmtoll
  *  MCR        DACSYNC        LL_HRTIM_TIM_GetDACTrig \n
  *  TIMxCR     DACSYNC        LL_HRTIM_TIM_GetDACTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval dac_trigger Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_DACTRIG_NONE
  *         @arg @ref LL_HRTIM_DACTRIG_DACTRIGOUT1
  *         @arg @ref LL_HRTIM_DACTRIG_DACTRIGOUT2
  *         @arg @ref LL_HRTIM_DACTRIG_DACTRIGOUT3
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetDACTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MCR_DACSYNC));
}

/**
  * @brief  Set ADC trigger generation mode for a given timer.
  * @rmtoll
  *  TIMxCR2    ADCTRGCH1      LL_HRTIM_TIM_SetADCTrigMode \n
  *  TIMxCR2    ADCTRGCH2      LL_HRTIM_TIM_SetADCTrigMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_OUT1_OUT2
  *         @arg @ref LL_HRTIM_ADCTRIG_OUT1
  *         @arg @ref LL_HRTIM_ADCTRIG_OUT2
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetADCTrigMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, (HRTIM_TIMxCR2_ADCTRGCH2 | HRTIM_TIMxCR2_ADCTRGCH1), mode);
}

/**
  * @brief  Get ADC trigger generation mode for a given timer.
  * @rmtoll
  *  TIMxCR2    ADCTRGCH1      LL_HRTIM_TIM_GetADCTrigMode \n
  *  TIMxCR2    ADCTRGCH2      LL_HRTIM_TIM_GetADCTrigMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ADCTRIG_OUT1_OUT2
  *         @arg @ref LL_HRTIM_ADCTRIG_OUT1
  *         @arg @ref LL_HRTIM_ADCTRIG_OUT2
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetADCTrigMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(* preg, (HRTIM_TIMxCR2_ADCTRGCH2 | HRTIM_TIMxCR2_ADCTRGCH1)));
}

/**
  * @brief  Enable the timer registers preload mechanism.
  * @rmtoll
  *  MCR        PREEN        LL_HRTIM_TIM_EnablePreload \n
  *  TIMxCR     PREEN        LL_HRTIM_TIM_EnablePreload
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note When the preload mode is enabled, accessed registers are shadow registers.
  *       Their content is transferred into the active register after an update request,
  *       either software or synchronized with an event.
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnablePreload(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MCR_PREEN);
}

/**
  * @brief  Disable the timer registers preload mechanism.
  * @rmtoll
  *  MCR        PREEN        LL_HRTIM_TIM_DisablePreload \n
  *  TIMxCR     PREEN        LL_HRTIM_TIM_DisablePreload
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisablePreload(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MCR_PREEN);
}

/**
  * @brief  Indicate whether the timer registers preload mechanism is enabled.
  * @rmtoll
  *  MCR        PREEN        LL_HRTIM_TIM_IsEnabledPreload \n
  *  TIMxCR     PREEN        LL_HRTIM_TIM_IsEnabledPreload
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of PREEN bit in HRTIM_MCR or HRTIM_TIMxCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledPreload(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MCR_PREEN) == (HRTIM_MCR_PREEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the timer register update trigger.
  * @rmtoll
  *  MCR           MREPU      LL_HRTIM_TIM_SetUpdateTrig \n
  *  TIMxCR        TAU        LL_HRTIM_TIM_SetUpdateTrig \n
  *  TIMxCR        TBU        LL_HRTIM_TIM_SetUpdateTrig \n
  *  TIMxCR        TCU        LL_HRTIM_TIM_SetUpdateTrig \n
  *  TIMxCR        TDU        LL_HRTIM_TIM_SetUpdateTrig \n
  *  TIMxCR        TEU        LL_HRTIM_TIM_SetUpdateTrig \n
  *  TIMxCR        TFU        LL_HRTIM_TIM_SetUpdateTrig \n
  *  TIMxCR        MSTU       LL_HRTIM_TIM_SetUpdateTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  update_trigger This parameter can be one of the following values:
  *
  *         For the master timer this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_UPDATETRIG_NONE
  *         @arg @ref LL_HRTIM_UPDATETRIG_REPETITION
  *
  *         For timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_UPDATETRIG_NONE
  *         or a combination of the following values:
  *         @arg @ref LL_HRTIM_UPDATETRIG_MASTER_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMA_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMB_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMC_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMD_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIME_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMF_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_REPETITION
  *         @arg @ref LL_HRTIM_UPDATETRIG_RESET
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetUpdateTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t update_trigger)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg,
                   LL_HRTIM_REG_MASK_TAB_UPDATETRIG[itim],
                   update_trigger << LL_HRTIM_REG_SHIFT_TAB_UPDATETRIG[itim]);
}

/**
  * @brief  Get the timer register update trigger.
  * @rmtoll
  *  MCR           MREPU      LL_HRTIM_TIM_GetUpdateTrig \n
  *  TIMxCR        TAU        LL_HRTIM_TIM_GetUpdateTrig \n
  *  TIMxCR        TBU        LL_HRTIM_TIM_GetUpdateTrig \n
  *  TIMxCR        TCU        LL_HRTIM_TIM_GetUpdateTrig \n
  *  TIMxCR        TDU        LL_HRTIM_TIM_GetUpdateTrig \n
  *  TIMxCR        TEU        LL_HRTIM_TIM_GetUpdateTrig \n
  *  TIMxCR        TFU        LL_HRTIM_TIM_GetUpdateTrig \n
  *  TIMxCR        MSTU       LL_HRTIM_TIM_GetUpdateTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval update_trigger Returned value can be one of the following values:
  *
  *         For the master timer this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_UPDATETRIG_NONE
  *         @arg @ref LL_HRTIM_UPDATETRIG_REPETITION
  *
  *         For timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_UPDATETRIG_NONE
  *         or a combination of the following values:
  *         @arg @ref LL_HRTIM_UPDATETRIG_MASTER_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMA_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMB_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMC_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMD_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIME_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_TIMF_UPDATE
  *         @arg @ref LL_HRTIM_UPDATETRIG_REPETITION
  *         @arg @ref LL_HRTIM_UPDATETRIG_RESET
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetUpdateTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, LL_HRTIM_REG_MASK_TAB_UPDATETRIG[itim]) >>  LL_HRTIM_REG_SHIFT_TAB_UPDATETRIG[itim]);
}

/**
  * @brief  Set  the timer registers update condition (how the registers update occurs relatively to the burst DMA
  *         transaction or an external update request received on one of the update enable inputs (UPD_EN[3:1])).
  * @rmtoll
  *  MCR           BRSTDMA      LL_HRTIM_TIM_SetUpdateGating \n
  *  TIMxCR        UPDGAT       LL_HRTIM_TIM_SetUpdateGating \n
  *  OR            UPDENSEL     LL_HRTIM_TIM_SetUpdateGating
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  update_gating This parameter can be one of the following values:
  *
  *         For the master timer this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_UPDATEGAT_INDEPENDENT
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_COMPLETE
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_UPDATE
  *
  *         For the timer A..F this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_UPDATEGAT_INDEPENDENT
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_COMPLETE
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM10_OC1
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM11_OC1
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM6_TRGO
  *         @arg @ref LL_HRTIM_UPDATEGAT_PLAY1_OUT14 (*)
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM10_OC1_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM11_OC1_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM6_TRGO_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_PLAY1_OUT14_UPDATE (*)
  *         (*)  Value not defined in all devices. \n
  */
#if defined(PLAY1)
__STATIC_INLINE void LL_HRTIM_TIM_SetUpdateGating(HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t update_gating)
#else
__STATIC_INLINE void LL_HRTIM_TIM_SetUpdateGating(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t update_gating)
#endif /* PLAY1 */
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
#if defined(PLAY1)
  STM32_MODIFY_REG(*preg, REG_MASK_TAB_UPDATEGAT[itim], ((update_gating << REG_SHIFT_TAB_UPDATEGAT[itim])
                                                         & ~HRTIM_OR_UPDENSEL));
  STM32_MODIFY_REG(hrtimx->sCommonRegs.OR, HRTIM_OR_UPDENSEL, (update_gating & HRTIM_OR_UPDENSEL));
#else
  STM32_MODIFY_REG(*preg, REG_MASK_TAB_UPDATEGAT[itim], (update_gating << REG_SHIFT_TAB_UPDATEGAT[itim]));
#endif /* PLAY1 */
}

/**
  * @brief  Get  the timer registers update condition.
  * @rmtoll
  *  MCR           BRSTDMA      LL_HRTIM_TIM_GetUpdateGating \n
  *  TIMxCR        UPDGAT       LL_HRTIM_TIM_GetUpdateGating \n
  *  OR            UPDENSEL     LL_HRTIM_TIM_GetUpdateGating
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval update_gating Returned value can be one of the following values:
  *
  *         For the master timer this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_UPDATEGAT_INDEPENDENT
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_COMPLETE
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_UPDATE
  *
  *         For the timer A..F this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_UPDATEGAT_INDEPENDENT
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_COMPLETE
  *         @arg @ref LL_HRTIM_UPDATEGAT_DMABURST_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM10_OC1
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM11_OC1
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM6_TRGO
  *         @arg @ref LL_HRTIM_UPDATEGAT_PLAY1_OUT14 (*)
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM10_OC1_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM11_OC1_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_TIM6_TRGO_UPDATE
  *         @arg @ref LL_HRTIM_UPDATEGAT_PLAY1_OUT14_UPDATE (*)
  *         (*)  Value not defined in all devices.  \n
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetUpdateGating(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
#if defined(PLAY1)
  uint32_t updgat = STM32_READ_BIT(*preg, REG_MASK_TAB_UPDATEGAT[itim]) >>  REG_SHIFT_TAB_UPDATEGAT[itim];
  uint32_t updensel = STM32_READ_BIT(hrtimx->sCommonRegs.OR, HRTIM_OR_UPDENSEL);;
  return (updgat | updensel);
#else
  return (STM32_READ_BIT(*preg, REG_MASK_TAB_UPDATEGAT[itim]) >>  REG_SHIFT_TAB_UPDATEGAT[itim]);
#endif /* PLAY1 */
}

/**
  * @brief  Enable the push-pull mode.
  * @rmtoll
  *  TIMxCR        PSHPLL       LL_HRTIM_TIM_EnablePushPullMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnablePushPullMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxCR_PSHPLL);
}

/**
  * @brief  Disable the push-pull mode.
  * @rmtoll
  *  TIMxCR        PSHPLL       LL_HRTIM_TIM_DisablePushPullMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisablePushPullMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxCR_PSHPLL);
}

/**
  * @brief  Indicate whether the push-pull mode is enabled.
  * @rmtoll
  *  TIMxCR        PSHPLL       LL_HRTIM_TIM_IsEnabledPushPullMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of PSHPLL bit in HRTIM_TIMxCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledPushPullMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_TIMxCR_PSHPLL) == (HRTIM_TIMxCR_PSHPLL)) ? 1UL : 0UL);
}

/**
  * @brief  Set the functioning mode of the compare unit (CMP2 or CMP4 can operate in standard mode or in
  *         auto delayed mode).
  * @rmtoll
  *  TIMxCR        DELCMP2       LL_HRTIM_TIM_SetCompareMode \n
  *  TIMxCR        DELCMP4       LL_HRTIM_TIM_SetCompareMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  compare_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_2
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_4
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_COMPAREMODE_REGULAR
  *         @arg @ref LL_HRTIM_COMPAREMODE_DELAY_NOTIMEOUT
  *         @arg @ref LL_HRTIM_COMPAREMODE_DELAY_CMP1
  *         @arg @ref LL_HRTIM_COMPAREMODE_DELAY_CMP3
  * @note In auto-delayed mode the compare match occurs independently from the timer counter value.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCompareMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t compare_unit,
                                                 uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  uint32_t shift = (compare_unit == LL_HRTIM_COMPARE_UNIT_2) ? 0U : 2U;
  STM32_MODIFY_REG(* preg, (HRTIM_TIMxCR_DELCMP2 << shift), (Mode << shift));
}

/**
  * @brief  Get the functioning mode of the compare unit.
  * @rmtoll
  *  TIMxCR        DELCMP2       LL_HRTIM_TIM_GetCompareMode \n
  *  TIMxCR        DELCMP4       LL_HRTIM_TIM_GetCompareMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  compare_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_2
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_4
  * @retval Mode Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_COMPAREMODE_REGULAR
  *         @arg @ref LL_HRTIM_COMPAREMODE_DELAY_NOTIMEOUT
  *         @arg @ref LL_HRTIM_COMPAREMODE_DELAY_CMP1
  *         @arg @ref LL_HRTIM_COMPAREMODE_DELAY_CMP3
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCompareMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t compare_unit)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  uint32_t shift = (compare_unit == LL_HRTIM_COMPARE_UNIT_2) ? 0U : 2U;
  return (STM32_READ_BIT(*preg, (HRTIM_TIMxCR_DELCMP2 << shift)) >>  shift);
}

/**
  * @brief  Set the compare value of a compare unit.
  * @rmtoll
  *  CMP1xR        CMP1       LL_HRTIM_TIM_SetCompareValue \n
  *  CMP2xR        CMP2       LL_HRTIM_TIM_SetCompareValue \n
  *  CMP3xR        CMP3       LL_HRTIM_TIM_SetCompareValue \n
  *  CMP4xR        CMP4       LL_HRTIM_TIM_SetCompareValue
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  compare_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_1
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_2
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_3
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_4
  * @param compare_value Maximum value is 0xFFFD
  * @note In auto-delayed mode the compare match occurs independently from the timer counter value.
  * @note  For compare units 1 or 3, the compare value must be either null or above or equal to 3 periods of the
  *        fHRTIM clock.
  * @note  For compare units 2 or 4, the compare value must be above or equal to 3 periods of the fHRTIM clock.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCompareValue(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t compare_unit,
                                                  uint32_t compare_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP1R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] +
                                                       LL_HRTIM_REG_OFFSET_TAB_CMPxR[compare_unit]));
  STM32_WRITE_REG(*preg, compare_value);
}

/**
  * @brief  Get the compare value of a compare unit.
  * @rmtoll
  *  CMP1xR        CMP1       LL_HRTIM_TIM_GetCompareValue \n
  *  CMP2xR        CMP2       LL_HRTIM_TIM_GetCompareValue \n
  *  CMP3xR        CMP3       LL_HRTIM_TIM_GetCompareValue \n
  *  CMP4xR        CMP4       LL_HRTIM_TIM_GetCompareValue
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  compare_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_1
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_2
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_3
  *         @arg @ref LL_HRTIM_COMPARE_UNIT_4
  * @retval Compare value of the selected compare unit.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCompareValue(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                      uint32_t compare_unit)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP1R) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] +
                                                   LL_HRTIM_REG_OFFSET_TAB_CMPxR[compare_unit]));
  return (STM32_READ_REG(*preg));
}

/**
  * @brief  Set the timer counter value.
  * @rmtoll
  *  MCNTR        MCNT       LL_HRTIM_TIM_SetCounter \n
  *  CNTxR        CNTx       LL_HRTIM_TIM_SetCounter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  counter_value Value between 0 and 0xFFFF
  * @note  This function can only be called when the timer is stopped.
  * @note  For HR clock prescaling ratio below 32 (CKPSC[2:0] < 5), the least
  *        significant bits of the counter are not significant. They cannot be
  *        written and return 0 when read.
  * @note The timer behavior is not guaranteed if the counter value is set above
  *       the period.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCounter(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t counter_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCNTR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_MCNTR_MCNT, counter_value);
}

/**
  * @brief  Get actual timer counter value.
  * @rmtoll
  *  MCNTR        MCNT       LL_HRTIM_TIM_GetCounter \n
  *  CNTxR        CNTx       LL_HRTIM_TIM_GetCounter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval counter_value Value between 0 and 0xFFFD.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCounter(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCNTR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MCNTR_MCNT));
}

/**
  * @brief  Set the timer period value.
  * @rmtoll
  *  MPER        MPER       LL_HRTIM_TIM_SetPeriod \n
  *  PERxR       PERx       LL_HRTIM_TIM_SetPeriod
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  counting_period Value between 0 and 0xFFFD
  * @note   The period value must be above or equal to 3 periods of the fHRTIM clock.
 */
__STATIC_INLINE void LL_HRTIM_TIM_SetPeriod(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t counting_period)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MPER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_MPER_MPER, counting_period);
}

/**
  * @brief  Get actual timer period value.
  * @rmtoll
  *  MPER        MPER       LL_HRTIM_TIM_GetPeriod \n
  *  PERxR       PERx       LL_HRTIM_TIM_GetPeriod
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Timer period value.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetPeriod(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MPER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MPER_MPER));
}

/**
  * @brief  Set the timer repetition period value.
  * @rmtoll
  *  MREP        MREP       LL_HRTIM_TIM_SetRepetition \n
  *  REPxR       REPx       LL_HRTIM_TIM_SetRepetition
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  repetition_value Value between 0 and 0xFF
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetRepetition(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t repetition_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MREP) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_MREP_MREP, repetition_value);
}

/**
  * @brief  Get actual timer repetition period value.
  * @rmtoll
  *  MREP        MREP       LL_HRTIM_TIM_GetRepetition \n
  *  REPxR       REPx       LL_HRTIM_TIM_GetRepetition
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval repetition_value Value between 0 and 0xFF.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetRepetition(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MREP) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MREP_MREP));
}

/**
  * @brief  Set the compare value of the compare unit 1.
  * @rmtoll
  *  MCMP1R      MCMP1       LL_HRTIM_TIM_SetCompare1 \n
  *  CMP1xR      CMP1x       LL_HRTIM_TIM_SetCompare1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param compare_value Maximum value is 0xFFFD
  * @note  The compare value must be either null or above or equal to 3 periods of the fHRTIM clock.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCompare1(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t compare_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP1R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_MCMP1R_MCMP1, compare_value);
}

/**
  * @brief  Get actual compare value of the compare unit 1.
  * @rmtoll
  *  MCMP1R      MCMP1       LL_HRTIM_TIM_GetCompare1 \n
  *  CMP1xR      CMP1x       LL_HRTIM_TIM_GetCompare1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Compare value of the compare unit 1.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCompare1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP1R) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MCMP1R_MCMP1));
}

/**
  * @brief  Set the compare value of the compare unit 2.
  * @rmtoll
  *  MCMP2R      MCMP2       LL_HRTIM_TIM_SetCompare2 \n
  *  CMP2xR      CMP2x       LL_HRTIM_TIM_SetCompare2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  compare_value Maximum value is 0xFFFD
  * @note  The compare value must be above or equal to 3 periods of the fHRTIM clock.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCompare2(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t compare_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP2R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_MCMP2R_MCMP2, compare_value);
}

/**
  * @brief  Get actual compare value of the compare unit 2.
  * @rmtoll
  *  MCMP2R      MCMP2       LL_HRTIM_TIM_GetCompare2 \n
  *  CMP2xR      CMP2x       LL_HRTIM_TIM_GetCompare2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Compare value of the compare unit 2.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCompare2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP2R) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MCMP2R_MCMP2));
}

/**
  * @brief  Set the compare value of the compare unit 3.
  * @rmtoll
  *  MCMP3R      MCMP3       LL_HRTIM_TIM_SetCompare3 \n
  *  CMP3xR      CMP3x       LL_HRTIM_TIM_SetCompare3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param compare_value Maximum value is 0xFFFD
  * @note  The compare value must be either null or above or equal to 3 periods of the fHRTIM clock.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCompare3(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t compare_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP3R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_MCMP3R_MCMP3, compare_value);
}

/**
  * @brief  Get actual compare value of the compare unit 3.
  * @rmtoll
  *  MCMP3R      MCMP3       LL_HRTIM_TIM_GetCompare3 \n
  *  CMP3xR      CMP3x       LL_HRTIM_TIM_GetCompare3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Compare value of the compare unit 3.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCompare3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP3R) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MCMP3R_MCMP3));
}

/**
  * @brief  Set the compare value of the compare unit 4.
  * @rmtoll
  *  MCMP4R      MCMP4       LL_HRTIM_TIM_SetCompare4 \n
  *  CMP4xR      CMP4x       LL_HRTIM_TIM_SetCompare4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  compare_value Maximum value is 0xFFFD
  * @note  The compare value must be above or equal to 3 periods of the fHRTIM clock.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCompare4(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t compare_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP4R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_MCMP4R_MCMP4, compare_value);
}

/**
  * @brief  Get actual compare value of the compare unit 4.
  * @rmtoll
  *  MCMP4R      MCMP4       LL_HRTIM_TIM_GetCompare4 \n
  *  CMP4xR      CMP4x       LL_HRTIM_TIM_GetCompare4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Compare value of the compare unit 4.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCompare4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MCMP4R) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_MCMP4R_MCMP4));
}

/**
  * @brief  Set the reset trigger of a timer counter.
  * @rmtoll
  *  RSTxR      UPDT                  LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      CMP2                  LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      CMP4                  LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      MSTPER                LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      MSTCMP1               LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      MSTCMP2               LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      MSTCMP3               LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      MSTCMP4               LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTA       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTB       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTC       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTD       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTE       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTF       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTG       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTH       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTI       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      EXTEVNTJ       LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMBCMP1              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMBCMP2              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMBCMP4              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMCCMP1              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMCCMP2              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMCCMP4              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMDCMP1              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMDCMP2              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMDCMP4              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMECMP1              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMECMP2              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMECMP4              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMFCMP1              LL_HRTIM_TIM_SetResetTrig \n
  *  RSTxR      TIMFCMP2              LL_HRTIM_TIM_SetResetTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  reset_trigger This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_RESETTRIG_NONE
  *         @arg @ref LL_HRTIM_RESETTRIG_UPDATE
  *         @arg @ref LL_HRTIM_RESETTRIG_CMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_CMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP3
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVA
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVB
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVC
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVD
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVE
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVF
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVG
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVH
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVI
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVJ
  *         For timer A:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TFCMP2
  *         For timer B:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TFCMP2
  *         For timer C:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TFCMP2
  *         For timer E:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TFCMP2
  *         For timer F:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TECMP2
  * @note The reset of the timer counter can be triggered by up to 30 events
  *       that can be selected among the following sources:
  *         @arg The timing unit: Compare 2, Compare 4 and Update (3 events).
  *         @arg The master timer: Reset and Compare 1..4 (5 events).
  *         @arg The external events EXTEVNT1..10 (10 events).
  *         @arg All other timing units (e.g. Timer B..F for timer A): Compare 1, 2 and 4 (12 events).
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetResetTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t reset_trigger)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].RSTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_WRITE_REG(*preg, reset_trigger);
}

/**
  * @brief  Get actual reset trigger of a timer counter.
  * @rmtoll
  *  RSTxR      UPDT                  LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      CMP2                  LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      CMP4                  LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      MSTPER                LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      MSTCMP1               LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      MSTCMP2               LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      MSTCMP3               LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      MSTCMP4               LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTA       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTB       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTC       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTD       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTE       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTF       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTG       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTH       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTI       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      EXTEVNTJ       LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMBCMP1              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMBCMP2              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMBCMP4              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMCCMP1              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMCCMP2              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMCCMP4              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMDCMP1              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMDCMP2              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMDCMP4              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMECMP1              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMECMP2              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMECMP4              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMFCMP1              LL_HRTIM_TIM_GetResetTrig \n
  *  RSTxR      TIMFCMP2              LL_HRTIM_TIM_GetResetTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval reset_trigger Returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_RESETTRIG_NONE
  *         @arg @ref LL_HRTIM_RESETTRIG_UPDATE
  *         @arg @ref LL_HRTIM_RESETTRIG_CMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_CMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP3
  *         @arg @ref LL_HRTIM_RESETTRIG_MASTER_CMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVA
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVB
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVC
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVD
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVE
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVF
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVG
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVH
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVI
  *         @arg @ref LL_HRTIM_RESETTRIG_EEVJ
  *         For timer A:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMA_TFCMP2
  *         For timer B:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMB_TFCMP2
  *         For timer C:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TECMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TECMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMD_TFCMP2
  *         For timer E:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TFCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIME_TFCMP2
  *         For timer F:
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TACMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TACMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TACMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TBCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TBCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TCCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TCCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TDCMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TDCMP2
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TDCMP4
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TECMP1
  *         @arg @ref LL_HRTIM_RESETTRIG_TIMF_TECMP2
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetResetTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].RSTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_REG(*preg));
}

/**
  * @brief  Get the value hold by a capture unit.
  * @rmtoll
  *  CPT1xR      CPT1x           LL_HRTIM_TIM_GetCapturedValue \n
  *  CPT2xR      CPT2x           LL_HRTIM_TIM_GetCapturedValue
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  capture_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_1
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_2
  * @retval Captured value.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCapturedValue(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                       uint32_t capture_unit)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0U].CPT1xR) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] + (capture_unit * 4U)));
  return (STM32_READ_REG(*preg));
}

/**
  * @brief  Get the counting direction hold by a capture unit.
  * @rmtoll
  *  CPT1xR      DIR           LL_HRTIM_TIM_GetCapturedDirection \n
  *  CPT2xR      DIR           LL_HRTIM_TIM_GetCapturedDirection
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  capture_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_1
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_2
  * @retval filter This parameter can be one of the following values:
  *         @arg @ref  LL_HRTIM_COUNTING_MODE_UP
  *         @arg @ref  LL_HRTIM_COUNTING_MODE_UP_DOWN
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCapturedDirection(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                           uint32_t capture_unit)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0U].CPT1xR) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] + (capture_unit * 4U)));

  return ((STM32_READ_BIT(*preg, HRTIM_CPT1xR_DIR) >> HRTIM_CPT1xR_DIR_Pos) << HRTIM_TIMxCR2_UDM_Pos);
}

/**
  * @brief  Get captured value for capture unit 1.
  * @rmtoll
  *  CPT1xR      CPT1x           LL_HRTIM_TIM_GetCapture1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Captured value.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCapture1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CPT1xR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_REG(*preg));
}

/**
  * @brief  Get the counting direction when capture 1 event occurred.
  * @rmtoll
  *  CPT1xR      DIR           LL_HRTIM_TIM_GetCapture1Direction
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval filter This parameter can be one of the following values:
  *         @arg @ref  LL_HRTIM_COUNTING_MODE_UP
  *         @arg @ref  LL_HRTIM_COUNTING_MODE_UP_DOWN
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCapture1Direction(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CPT1xR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_CPT1xR_DIR) >> HRTIM_CPT1xR_DIR_Pos) << HRTIM_TIMxCR2_UDM_Pos);
}

/**
  * @brief  Get captured value for capture unit 2.
  * @rmtoll
  *  CPT2xR      CPT2x           LL_HRTIM_TIM_GetCapture2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Captured value.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCapture2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CPT2xR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_REG(*preg));
}

/**
  * @brief  Get the counting direction when capture 2 event occurred.
  * @rmtoll
  *  CPT2xR      DIR           LL_HRTIM_TIM_GetCapture2Direction
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval filter This parameter can be one of the following values:
  *         @arg @ref  LL_HRTIM_COUNTING_MODE_UP
  *         @arg @ref  LL_HRTIM_COUNTING_MODE_UP_DOWN
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCapture2Direction(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CPT2xR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_CPT2xR_DIR) >> HRTIM_CPT2xR_DIR_Pos) << HRTIM_TIMxCR2_UDM_Pos);
}

/**
  * @brief  Set the trigger of a capture unit for a given timer.
  * @rmtoll
  *  CPT1xCR      SWCPT            LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      UPDCPT           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVACPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVBCPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVCCPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVDCPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVECPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVFCPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVGCPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVHCPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVICPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      EXEVJCPT         LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TA1SET           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TA1RST           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TACMP1           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TACMP2           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TB1SET           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TB1RST           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TBCMP1           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TBCMP2           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TC1SET           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TC1RST           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TCCMP1           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TCCMP2           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TD1SET           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TD1RST           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TDCMP1           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TDCMP2           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TE1SET           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TE1RST           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TECMP1           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TECMP2           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TF1SET           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TF1RST           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TFCMP1           LL_HRTIM_TIM_SetCaptureTrig \n
  *  CPT1xCR      TFCMP2           LL_HRTIM_TIM_SetCaptureTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  capture_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_1
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_2
  * @param  trigger_source This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_NONE
  *         @arg @ref LL_HRTIM_CAPTURETRIG_SW
  *         @arg @ref LL_HRTIM_CAPTURETRIG_UPDATE
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVA
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVB
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVC
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVD
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVE
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVF
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVG
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVH
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVI
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVJ
  *         For timer A:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TFCMP2
  *         For timer B:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TFCMP2
  *         For timer C:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TFCMP2
  *         For timer E:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TFCMP2
  *         For timer F:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TECMP2
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCaptureTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t capture_unit,
                                                 uint64_t trigger_source)
{
  uint32_t itim;
  __IOM uint32_t *preg;
  uint32_t cfg1;
  uint32_t cfg2;

  /* Calculate timer index - ensure it is within valid range */
  itim = (uint32_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);

  if (itim < (sizeof(LL_HRTIM_REG_SHIFT_TAB_CPT) / sizeof(LL_HRTIM_REG_SHIFT_TAB_CPT[0])))
  {
    /* Calculate the register address */
    preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0U].CPT1xCR) +
                                         LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] + (capture_unit * 4U)));

    /* Extract lower 12 bits for cfg1 */
    cfg1 = (uint32_t)(trigger_source & 0xFFFU);

    /* Extract bits [51:32] for cfg2 */
    cfg2 = (uint32_t)((trigger_source >> 32U) & 0xFFFFF00FU);

    /* Compose cfg2 with proper masking and shifting */
    cfg2 = (cfg2 & LL_HRTIM_REG_MASK_TAB_CPT[itim]) | ((cfg2 & 0xFU) << LL_HRTIM_REG_SHIFT_TAB_CPT[itim]);

    /* Write combined configuration to register */
    STM32_WRITE_REG(*preg, (cfg1 | cfg2));
  }
}

/**
  * @brief  Get actual trigger of a capture unit for a given timer.
  * @rmtoll
  *  CPT1xCR      SWCPT            LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      UPDCPT           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVACPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVBCPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVCCPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVDCPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVECPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVFCPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVGCPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVHCPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVICPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      EXEVJCPT         LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TA1SET           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TA1RST           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TACMP1           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TACMP2           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TB1SET           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TB1RST           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TBCMP1           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TBCMP2           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TC1SET           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TC1RST           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TCCMP1           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TCCMP2           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TD1SET           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TD1RST           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TDCMP1           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TDCMP2           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TE1SET           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TE1RST           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TECMP1           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TECMP2           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TF1SET           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TF1RST           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TFCMP1           LL_HRTIM_TIM_GetCaptureTrig \n
  *  CPT1xCR      TFCMP2           LL_HRTIM_TIM_GetCaptureTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  capture_unit This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_1
  *         @arg @ref LL_HRTIM_CAPTURE_UNIT_2
  * @retval trigger_source This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_NONE
  *         @arg @ref LL_HRTIM_CAPTURETRIG_SW
  *         @arg @ref LL_HRTIM_CAPTURETRIG_UPDATE
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVA
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVB
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVC
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVD
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVE
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVF
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVG
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVH
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVI
  *         @arg @ref LL_HRTIM_CAPTURETRIG_EEVJ
  *         For timer A:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMA_TFCMP2
  *         For timer B:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMB_TFCMP2
  *         For timer C:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TECMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMD_TFCMP2
  *         For timer E:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHF1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_CHF1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TFCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIME_TFCMP2
  *         For timer F:
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHA1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHA1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TACMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TACMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHB1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHB1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TBCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHC1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHC1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TCCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHD1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHD1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TDCMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TDCMP2
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHE1_SET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_CHE1_RESET
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TECMP1
  *         @arg @ref LL_HRTIM_CAPTURETRIG_TIMF_TECMP2
  */
__STATIC_INLINE uint64_t LL_HRTIM_TIM_GetCaptureTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t capture_unit)
{
  uint32_t itim;
  const __IOM uint32_t *preg;
  uint32_t trigger_source;
  uint64_t cfg = 0ULL;

  /* Calculate timer index */
  itim = (uint32_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);

  /* Ensure index is within bounds */
  if (itim < (sizeof(LL_HRTIM_REG_SHIFT_TAB_CPT) / sizeof(LL_HRTIM_REG_SHIFT_TAB_CPT[0])))
  {
    /* Calculate the register address */
    preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0U].CPT1xCR) +
                                         LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] + (capture_unit * 4U)));

    /* Read capture trigger register */
    trigger_source = STM32_READ_REG(*preg);

    /* Compose cfg from upper bits */
    uint32_t lower_part = trigger_source & 0x00000FFFU;
    uint32_t upper_part = trigger_source & 0xFFFFF000U;
    uint32_t masked_upper = upper_part & LL_HRTIM_REG_MASK_TAB_CPT[itim];
    uint32_t shifted_upper = (upper_part & ~LL_HRTIM_REG_MASK_TAB_CPT[itim]) >> LL_HRTIM_REG_SHIFT_TAB_CPT[itim];
    uint32_t combined_upper = masked_upper | shifted_upper;

    cfg = (((uint64_t)combined_upper << 32U) | ((uint64_t)lower_part));
  }

  return cfg;
}

/**
  * @brief  Enable deadtime insertion for a given timer.
  * @rmtoll
  *  OUTxR      DTEN           LL_HRTIM_TIM_EnableDeadTime
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableDeadTime(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_OUTxR_DTEN);
}

/**
  * @brief  Disable deadtime insertion for a given timer.
  * @rmtoll
  *  OUTxR      DTEN           LL_HRTIM_TIM_DisableDeadTime
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableDeadTime(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_OUTxR_DTEN);
}

/**
  * @brief  Indicate whether deadtime insertion is enabled for a given timer.
  * @rmtoll
  *  OUTxR      DTEN           LL_HRTIM_TIM_IsEnabledDeadTime
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DTEN bit in HRTIM_OUTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledDeadTime(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_OUTxR_DTEN) == (HRTIM_OUTxR_DTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the delayed protection (DLYPRT) mode.
  * @rmtoll
  *  OUTxR      DLYPRT         LL_HRTIM_TIM_SetDLYPRTMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  delayed_protection_mode delayed protection (DLYPRT) mode
  *
  *         For timers A, B and C this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVG
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVG
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVG
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVG
  *
  *         For timers D, E and F this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVI
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVI
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVI
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVI
  * @note   This function must be called prior enabling the delayed protection
  * @note   Balanced Idle mode is only available in push-pull mode
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetDLYPRTMode(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                uint32_t delayed_protection_mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_OUTxR_DLYPRT, delayed_protection_mode);
}

/**
  * @brief  Get the delayed protection (DLYPRT) mode.
  * @rmtoll
  *  OUTxR      DLYPRT         LL_HRTIM_TIM_GetDLYPRTMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval delayed_protection_mode delayed protection (DLYPRT) mode.
  *
  *         For timers A, B and C this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVF
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVG
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVG
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVG
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVG
  *
  *         For timers D, E and F this parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVH
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT1_EEVI
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYOUT2_EEVI
  *         @arg @ref LL_HRTIM_DLYPRT_DELAYBOTH_EEVI
  *         @arg @ref LL_HRTIM_DLYPRT_BALANCED_EEVI
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetDLYPRTMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_OUTxR_DLYPRT));
}

/**
  * @brief  Enable delayed protection (DLYPRT) for a given timer.
  * @rmtoll
  *  OUTxR      DLYPRTEN       LL_HRTIM_TIM_EnableDLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This function must not be called once the concerned timer is enabled
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableDLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_OUTxR_DLYPRTEN);
}

/**
  * @brief  Disable delayed protection (DLYPRT) for a given timer.
  * @rmtoll
  *  OUTxR      DLYPRTEN       LL_HRTIM_TIM_DisableDLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This function must not be called once the concerned timer is enabled
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableDLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_OUTxR_DLYPRTEN);
}

/**
  * @brief  Indicate whether delayed protection (DLYPRT) is enabled for a given timer.
  * @rmtoll
  *  OUTxR      DLYPRTEN       LL_HRTIM_TIM_IsEnabledDLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DLYPRTEN bit in HRTIM_OUTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledDLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_OUTxR_DLYPRTEN) == (HRTIM_OUTxR_DLYPRTEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Balanced Idle Automatic Resume (BIAR) for a given timer.
  * @rmtoll
  *  OUTxR      BIAR       LL_HRTIM_TIM_EnableBIAR
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This function must not be called once the concerned timer is enabled
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableBIAR(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_OUTxR_BIAR);
}

/**
  * @brief  Disable the Balanced Idle Automatic Resume (BIAR) for a given timer.
  * @rmtoll
  *  OUTxR      BIAR       LL_HRTIM_TIM_DisableBIAR
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This function must not be called once the concerned timer is enabled
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableBIAR(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0U].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_OUTxR_BIAR);
}

/**
  * @brief  Indicate whether the Balanced Idle Automatic Resume (BIAR) is enabled for a given timer.
  * @rmtoll
  *  OUTxR      BIAR       LL_HRTIM_TIM_IsEnabledBIAR
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DLYPRTEN bit in HRTIM_OUTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledBIAR(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_OUTxR_BIAR) == (HRTIM_OUTxR_BIAR)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault channel(s) for a given timer.
  * @rmtoll
  *  FLTxR      FLT1EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT2EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT3EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT4EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT5EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT6EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT7EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT8EN       LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT1A2EN     LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT2A3EN     LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT3A4EN     LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT4A5EN     LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT5A6EN     LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT6A7EN     LL_HRTIM_TIM_EnableFault \n
  *  FLTxR      FLT7A8EN     LL_HRTIM_TIM_EnableFault
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  faults This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  *         @arg @ref LL_HRTIM_FLT1_FLT2
  *         @arg @ref LL_HRTIM_FLT2_FLT3
  *         @arg @ref LL_HRTIM_FLT3_FLT4
  *         @arg @ref LL_HRTIM_FLT4_FLT5
  *         @arg @ref LL_HRTIM_FLT5_FLT6
  *         @arg @ref LL_HRTIM_FLT6_FLT7
  *         @arg @ref LL_HRTIM_FLT7_FLT8
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableFault(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t faults)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].FLTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, faults);
}

/**
  * @brief  Disable the fault channel(s) for a given timer.
  * @rmtoll
  *  FLTxR      FLT1EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT2EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT3EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT4EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT5EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT6EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT7EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT8EN       LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT1A2EN     LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT2A3EN     LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT3A4EN     LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT4A5EN     LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT5A6EN     LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT6A7EN     LL_HRTIM_TIM_DisableFault \n
  *  FLTxR      FLT7A8EN     LL_HRTIM_TIM_DisableFault
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  faults This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  *         @arg @ref LL_HRTIM_FLT1_FLT2
  *         @arg @ref LL_HRTIM_FLT2_FLT3
  *         @arg @ref LL_HRTIM_FLT3_FLT4
  *         @arg @ref LL_HRTIM_FLT4_FLT5
  *         @arg @ref LL_HRTIM_FLT5_FLT6
  *         @arg @ref LL_HRTIM_FLT6_FLT7
  *         @arg @ref LL_HRTIM_FLT7_FLT8
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableFault(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t faults)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].FLTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, faults);
}

/**
  * @brief  Indicate whether the fault channel is enabled for a given timer.
  * @rmtoll
  *  FLTxR      FLT1EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT2EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT3EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT4EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT5EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT6EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT7EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT8EN       LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT1A2EN     LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT2A3EN     LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT3A4EN     LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT4A5EN     LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT5A6EN     LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT6A7EN     LL_HRTIM_TIM_IsEnabledFault \n
  *  FLTxR      FLT7A8EN     LL_HRTIM_TIM_IsEnabledFault
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  *         @arg @ref LL_HRTIM_FLT1_FLT2
  *         @arg @ref LL_HRTIM_FLT2_FLT3
  *         @arg @ref LL_HRTIM_FLT3_FLT4
  *         @arg @ref LL_HRTIM_FLT4_FLT5
  *         @arg @ref LL_HRTIM_FLT5_FLT6
  *         @arg @ref LL_HRTIM_FLT6_FLT7
  *         @arg @ref LL_HRTIM_FLT7_FLT8
  * @retval State of FLTxEN bit in HRTIM_FLTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledFault(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t fault)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].FLTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, fault) == (fault)) ? 1UL : 0UL);
}

/**
  * @brief  Lock the fault conditioning set-up for a given timer.
  * @rmtoll
  *  FLTxR      FLTLCK       LL_HRTIM_TIM_LockFault
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note Timer fault-related set-up is frozen until the next HRTIM or system reset
  */
__STATIC_INLINE void LL_HRTIM_TIM_LockFault(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].FLTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_FLTxR_FLTLCK);
}

/**
  * @brief  Define how the timer behaves during a burst mode operation.
  * @rmtoll
  *  BMCR      MTBM       LL_HRTIM_TIM_SetBurstModeOption \n
  *  BMCR      TABM       LL_HRTIM_TIM_SetBurstModeOption \n
  *  BMCR      TBBM       LL_HRTIM_TIM_SetBurstModeOption \n
  *  BMCR      TCBM       LL_HRTIM_TIM_SetBurstModeOption \n
  *  BMCR      TDBM       LL_HRTIM_TIM_SetBurstModeOption \n
  *  BMCR      TEBM       LL_HRTIM_TIM_SetBurstModeOption \n
  *  BMCR      TFBM       LL_HRTIM_TIM_SetBurstModeOption
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  timer_burst_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BURSTMODE_MAINTAINCLOCK
  *         @arg @ref LL_HRTIM_BURSTMODE_RESETCOUNTER
  * @note This function must not be called when the burst mode is enabled
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetBurstModeOption(HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t timer_burst_mode)
{
  uint32_t itim = (uint8_t)((STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos) & 0x1FU);
  STM32_MODIFY_REG(hrtimx->sCommonRegs.BMCR, timer, timer_burst_mode << itim);
}

/**
  * @brief  Retrieve how the timer behaves during a burst mode operation.
  * @rmtoll
  *  BMCR      MCR        LL_HRTIM_TIM_GetBurstModeOption \n
  *  BMCR      TABM       LL_HRTIM_TIM_GetBurstModeOption \n
  *  BMCR      TBBM       LL_HRTIM_TIM_GetBurstModeOption \n
  *  BMCR      TCBM       LL_HRTIM_TIM_GetBurstModeOption \n
  *  BMCR      TDBM       LL_HRTIM_TIM_GetBurstModeOption \n
  *  BMCR      TEBM       LL_HRTIM_TIM_GetBurstModeOption \n
  *  BMCR      TFBM       LL_HRTIM_TIM_GetBurstModeOption
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval timer_burst_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BURSTMODE_MAINTAINCLOCK
  *         @arg @ref LL_HRTIM_BURSTMODE_RESETCOUNTER
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetBurstModeOption(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)((STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos) & 0x1FU);
  return (STM32_READ_BIT(hrtimx->sCommonRegs.BMCR, timer) >> itim);
}

/**
  * @brief  Select the source of the DMA burst.
  * @rmtoll
  *  CR2    DBSS      LL_HRTIM_SetDMABurstSource
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_SetDMABurstSource(HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t dma_burst_source = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  STM32_MODIFY_REG(hrtimx->sCommonRegs.CR2, HRTIM_CR2_DBSS, (dma_burst_source + 1U) << HRTIM_CR2_DBSS_Pos);
}

/**
  * @brief  Indicate the source of the DMA burst.
  * @rmtoll
  *  CR2    DBSS      LL_HRTIM_GetDMABurstSource
  * @param  hrtimx High Resolution Timer instance
  * @retval  Timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE uint32_t LL_HRTIM_GetDMABurstSource(const HRTIM_TypeDef *hrtimx)
{
  uint32_t dbss = STM32_READ_BIT(hrtimx->sCommonRegs.CR2, HRTIM_CR2_DBSS) >> HRTIM_CR2_DBSS_Pos;
  uint32_t dma_burst_source = (dbss != 0U) ? (HRTIM_MCR_MCEN << (dbss - 1U)) : dbss;
  return dma_burst_source;
}

/**
  * @brief  Program which registers are to be written by Burst DMA transfers.
  * @rmtoll
  *  BDMUPDR      MTBM        LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MICR        LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MDIER       LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MCNT        LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MPER        LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MREP        LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MCMP1       LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MCMP2       LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MCMP3       LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDMUPDR      MCMP4       LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCR      LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxICR     LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxDIER    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCNT     LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxPER     LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxREP     LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCMP1    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCMP2    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCMP3    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCMP4    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxDTR     LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxSET1R   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxRST1R   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxSET2R   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxRST2R   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxEEFR1   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxEEFR2   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxRSTR    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCHPR    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxOUTR    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxFLTR    LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCR2     LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxEEFR3   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxEESELR  LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCOTRGR  LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCOFER   LL_HRTIM_TIM_ConfigBurstDMA \n
  *  BDTxUPDR     TIMxCODER   LL_HRTIM_TIM_ConfigBurstDMA
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  registers HRTIM registers to be updated by the DMA request
  *
  *         For Master timer this parameter can be can be a combination of the following values:
  *         @arg @ref LL_HRTIM_BURSTDMA_NONE
  *         @arg @ref LL_HRTIM_BURSTDMA_MCR
  *         @arg @ref LL_HRTIM_BURSTDMA_MICR
  *         @arg @ref LL_HRTIM_BURSTDMA_MDIER
  *         @arg @ref LL_HRTIM_BURSTDMA_MCNT
  *         @arg @ref LL_HRTIM_BURSTDMA_MPER
  *         @arg @ref LL_HRTIM_BURSTDMA_MREP
  *         @arg @ref LL_HRTIM_BURSTDMA_MCMP1
  *         @arg @ref LL_HRTIM_BURSTDMA_MCMP2
  *         @arg @ref LL_HRTIM_BURSTDMA_MCMP3
  *         @arg @ref LL_HRTIM_BURSTDMA_MCMP4
  *
  *         For Timers A..F this parameter can be can be a combination of the following values:
  *         @arg @ref LL_HRTIM_BURSTDMA_NONE
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMICR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMDIER
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCNT
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMPER
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMREP
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCMP1
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCMP2
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCMP3
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCMP4
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMDTR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMSET1R
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMRST1R
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMSET2R
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMRST2R
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMEEFR1
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMEEFR2
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMRSTR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCHPR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMOUTR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMFLTR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCR2
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMEEFR3
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMEESELR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCOTRGR
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCOFER
  *         @arg @ref LL_HRTIM_BURSTDMA_TIMCODER
  */
__STATIC_INLINE void LL_HRTIM_TIM_ConfigBurstDMA(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t registers)
{
  const uint8_t LL_HRTIM_REG_OFFSET_TAB_BDTUPR[] =
  {
    0x00U,   /* BDMUPR ; offset = 0x000 */
    0x04U,   /* BDAUPR ; offset = 0x05C */
    0x08U,   /* BDBUPR ; offset = 0x060 */
    0x0CU,   /* BDCUPR ; offset = 0x064 */
    0x10U,   /* BDDUPR ; offset = 0x068 */
    0x14U,   /* BDEUPR ; offset = 0x06C */
    0x1CU    /* BDFUPR ; offset = 0x074 */
  };

  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.BDMUPR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_BDTUPR[itim]));
  STM32_WRITE_REG(*preg, registers);
}

/**
  * @brief  Indicate on which output the signal is currently applied.
  * @rmtoll
  *  TIMxISR      CPPSTAT        LL_HRTIM_TIM_GetCurrentPushPullStatus
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note Only significant when the timer operates in push-pull mode.
  * @retval CPPSTAT This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CPPSTAT_OUT1
  *         @arg @ref LL_HRTIM_CPPSTAT_OUT2
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCurrentPushPullStatus(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxISR_CPPSTAT));
}

/**
  * @brief  Indicate on which output the signal was applied, in push-pull mode, balanced fault mode or delayed
  *         idle mode, when the protection was triggered.
  * @rmtoll
  *  TIMxISR      IPPSTAT        LL_HRTIM_TIM_GetIdlePushPullStatus
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval IPPSTAT This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_IPPSTAT_OUT1
  *         @arg @ref LL_HRTIM_IPPSTAT_OUT2
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetIdlePushPullStatus(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxISR_IPPSTAT));
}

/**
  * @brief  Set the source of a combined event for a given timer.
  * @rmtoll
  *  EESELxR     EEVASEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVBSEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVCSEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVDSEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVESEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVFSEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVGSEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVHSEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVISEL        LL_HRTIM_TIM_SetCombinedEventSrc \n
  *  EESELxR     EEVJSEL        LL_HRTIM_TIM_SetCombinedEventSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  * @param  source This parameter can be one of the following values:
  *         For combined event A:
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV1
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV11
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV1_EEV2
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV1_EEV11
  *         For combined event B:
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV2
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV12
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV2_EEV3
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV2_EEV12
  *         For combined event C:
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV3
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV13
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV3_EEV4
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV3_EEV13
  *         For combined event D:
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4_EEV5
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4_EEV14
  *         For combined event E:
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV5
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV15
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV5_EEV6
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV5_EEV15
  *         For combined event F:
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV6
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV16
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV6_EEV7
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV6_EEV16
  *         For combined event G:
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV7
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV11
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV7_EEV8
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV7_EEV11
  *         For combined event H:
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV8
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV12
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV8_EEV9
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV8_EEV12
  *         For combined event I:
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV9
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV13
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV9_EEV10
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV9_EEV13
  *         For combined event J:
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV10
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV14
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV10_EEV11
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV10_EEV14
  * @note This function must not be called when the timer counter is enabled.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCombinedEventSrc(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t event,
                                                      uint32_t source)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  uint32_t shift = (event < LL_HRTIM_EEVF) ? \
                   (HRTIM_EESELxR_EEVBSEL_Pos * (uint32_t)(STM32_POSITION_VAL(event)
                                                           - STM32_POSITION_VAL(LL_HRTIM_EEVA))) : \
                   (HRTIM_EESELxR_EEVFSEL_Pos + (HRTIM_EESELxR_EEVBSEL_Pos
                                                 * (uint32_t)(STM32_POSITION_VAL(event)
                                                              - STM32_POSITION_VAL(LL_HRTIM_EEVF))));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].EESELxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, (HRTIM_EESELxR_EEVASEL << shift), source);
}

/**
  * @brief  Get the source of a combined event for a given timer.
  * @rmtoll
  *  EESELxR     EEVASEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVBSEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVCSEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVDSEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVESEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVFSEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVGSEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVHSEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVISEL        LL_HRTIM_TIM_GetCombinedEventSrc \n
  *  EESELxR     EEVJSEL        LL_HRTIM_TIM_GetCombinedEventSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  * @retval source This parameter can be one of the following values:
  *         For combined event A:
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV1
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV11
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV1_EEV2
  *         @arg @ref LL_HRTIM_EEVA_SRC_EEV1_EEV11
  *         For combined event B:
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV2
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV12
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV2_EEV3
  *         @arg @ref LL_HRTIM_EEVB_SRC_EEV2_EEV12
  *         For combined event C:
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV3
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV13
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV3_EEV4
  *         @arg @ref LL_HRTIM_EEVC_SRC_EEV3_EEV13
  *         For combined event D:
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4_EEV5
  *         @arg @ref LL_HRTIM_EEVD_SRC_EEV4_EEV14
  *         For combined event E:
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV5
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV15
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV5_EEV6
  *         @arg @ref LL_HRTIM_EEVE_SRC_EEV5_EEV15
  *         For combined event F:
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV6
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV16
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV6_EEV7
  *         @arg @ref LL_HRTIM_EEVF_SRC_EEV6_EEV16
  *         For combined event G:
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV7
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV11
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV7_EEV8
  *         @arg @ref LL_HRTIM_EEVG_SRC_EEV7_EEV11
  *         For combined event H:
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV8
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV12
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV8_EEV9
  *         @arg @ref LL_HRTIM_EEVH_SRC_EEV8_EEV12
  *         For combined event I:
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV9
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV13
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV9_EEV10
  *         @arg @ref LL_HRTIM_EEVI_SRC_EEV9_EEV13
  *         For combined event J:
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV10
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV14
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV10_EEV11
  *         @arg @ref LL_HRTIM_EEVJ_SRC_EEV10_EEV14
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCombinedEventSrc(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t event)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  uint32_t shift = (event < LL_HRTIM_EEVF) ? \
                   (HRTIM_EESELxR_EEVBSEL_Pos * (uint32_t)(STM32_POSITION_VAL(event)
                                                           - STM32_POSITION_VAL(LL_HRTIM_EEVA))) : \
                   (HRTIM_EESELxR_EEVFSEL_Pos + (HRTIM_EESELxR_EEVBSEL_Pos *
                                                 (uint32_t)(STM32_POSITION_VAL(event)
                                                            - STM32_POSITION_VAL(LL_HRTIM_EEVF))));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].EESELxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_EESELxR_EEVASEL << shift)));
}

/**
  * @brief  Set the event filter for a given timer.
  * @rmtoll
  *  EEFxR1      EEAFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR1      EEBFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR1      EECFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR1      EEDFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR1      EEEFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR2      EEFFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR2      EEGFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR2      EEHFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR2      EEIFLTR        LL_HRTIM_TIM_SetEventFilter \n
  *  EEFxR2      EEJFLTR        LL_HRTIM_TIM_SetEventFilter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  * @param  filter This parameter can be one of the following values:
  *         For all timing units:
  *         @arg @ref LL_HRTIM_NO_FILTERING
  *         @arg @ref LL_HRTIM_BLK_RST_CMP1
  *         @arg @ref LL_HRTIM_BLK_RST_CMP2
  *         @arg @ref LL_HRTIM_BLK_RST_CMP3
  *         @arg @ref LL_HRTIM_BLK_RST_CMP4
  *         @arg @ref LL_HRTIM_BLK_CMP1_RST
  *         @arg @ref LL_HRTIM_BLK_CMP2_RST
  *         @arg @ref LL_HRTIM_BLK_CMP1_CMP2
  *         @arg @ref LL_HRTIM_BLK_CMP3_CMP4
  *         @arg @ref LL_HRTIM_BLK_PER_CMP1
  *         @arg @ref LL_HRTIM_BLK_PER_CMP2
  *         @arg @ref LL_HRTIM_BLK_RST_CMP1_CPPSTAT
  *         @arg @ref LL_HRTIM_WIN_RST_CMP2
  *         @arg @ref LL_HRTIM_WIN_RST_CMP3
  *         @arg @ref LL_HRTIM_WIN_CMP1_RST
  *         @arg @ref LL_HRTIM_WIN_CMP2_RST
  *         @arg @ref LL_HRTIM_WIN_CMP1_CMP2
  *         @arg @ref LL_HRTIM_WIN_CMP3_CMP4
  *         For timer A:
  *         @arg @ref LL_HRTIM_BLK_TIMA_TBRST_TBCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TBRST_TBCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMA_CHB2
  *         @arg @ref LL_HRTIM_BLK_TIMA_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TCRST_TCCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMA_TFRST_TFCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TDRST_TDCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TERST_TECMP2
  *         @arg @ref LL_HRTIM_WIN_TIMA_TBRST_TBCMP2
  *         @arg @ref LL_HRTIM_WIN_TIMA_TBCMP2_TBRST
  *         @arg @ref LL_HRTIM_WIN_TIMA_TBCMP1_TBRST
  *         For timer B:
  *         @arg @ref LL_HRTIM_BLK_TIMB_TARST_TACMP1
  *         @arg @ref LL_HRTIM_BLK_TIMB_TARST_TACMP4
  *         @arg @ref LL_HRTIM_BLK_TIMB_CHA2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMB_TCRST_TCCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TFRST_TFCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TDRST_TDCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TERST_TECMP1
  *         @arg @ref LL_HRTIM_WIN_TIMB_TARST_TACMP2
  *         @arg @ref LL_HRTIM_WIN_TIMB_TACMP2_TARST
  *         @arg @ref LL_HRTIM_WIN_TIMB_TACMP1_TARST
  *         For timer C:
  *         @arg @ref LL_HRTIM_BLK_TIMC_TARST_TACMP2
  *         @arg @ref LL_HRTIM_BLK_TIMC_TBRST_TBCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMC_TBRST_TBCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMC_TFRST_TFCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMC_TDRST_TDCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMC_TDRST_TDCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMC_CHD2
  *         @arg @ref LL_HRTIM_BLK_TIMC_TERST_TECMP4
  *         @arg @ref LL_HRTIM_WIN_TIMC_TDRST_TDCMP2
  *         @arg @ref LL_HRTIM_WIN_TIMC_TDCMP2_TDRST
  *         @arg @ref LL_HRTIM_WIN_TIMC_TDCMP1_TDRST
  *         For timer D:
  *         @arg @ref LL_HRTIM_BLK_TIMD_TARST_TACMP1
  *         @arg @ref LL_HRTIM_BLK_TIMD_TBRST_TBCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMD_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMD_TCRST_TCCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMD_CHC2
  *         @arg @ref LL_HRTIM_BLK_TIMD_TERST_TECMP1
  *         @arg @ref LL_HRTIM_BLK_TIMD_TERST_TECMP4
  *         @arg @ref LL_HRTIM_BLK_TIMD_TFRST_TFCMP4
  *         @arg @ref LL_HRTIM_WIN_TIMD_TCRST_TCCMP2
  *         @arg @ref LL_HRTIM_WIN_TIMD_TCCMP2_TCRST
  *         @arg @ref LL_HRTIM_WIN_TIMD_TCCMP1_TCRST
  *         For timer E:
  *         @arg @ref LL_HRTIM_BLK_TIME_TARST_TACMP2
  *         @arg @ref LL_HRTIM_BLK_TIME_TBRST_TBCMP1
  *         @arg @ref LL_HRTIM_BLK_TIME_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIME_TFRST_TFCMP4
  *         @arg @ref LL_HRTIM_BLK_TIME_CHF2
  *         @arg @ref LL_HRTIM_BLK_TIME_TDRST_TDCMP1
  *         @arg @ref LL_HRTIM_BLK_TIME_TDRST_TDCMP4
  *         @arg @ref LL_HRTIM_BLK_TIME_CHD2
  *         @arg @ref LL_HRTIM_WIN_TIME_TFRST_TFCMP2
  *         @arg @ref LL_HRTIM_WIN_TIME_TFCMP2_TFRST
  *         @arg @ref LL_HRTIM_WIN_TIME_TFCMP1_TFRST
  *         For timer F:
  *         @arg @ref LL_HRTIM_BLK_TIMF_TARST_TACMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_TBRST_TBCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMF_TCRST_TCCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_TDRST_TDCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMF_TDRST_TDCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_TERST_TECMP1
  *         @arg @ref LL_HRTIM_BLK_TIMF_TERST_TECMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_CHE2
  *         @arg @ref LL_HRTIM_WIN_TIMF_TERST_TECMP2
  *         @arg @ref LL_HRTIM_WIN_TIMF_TECMP2_TERST
  *         @arg @ref LL_HRTIM_WIN_TIMF_TECMP1_TERST
  * @note This function must not be called when the timer counter is enabled.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetEventFilter(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t event,
                                                 uint32_t filter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].EEFxR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] +
                                                       LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_EEFxR1_EEAFLTR << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   (filter << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
}

/**
  * @brief  Get actual event filter settings for a given timer.
  * @rmtoll
  *  EEFxR1      EEAFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR1      EEBFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR1      EECFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR1      EEDFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR1      EEEFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR2      EEFFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR2      EEGFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR2      EEHFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR2      EEIFLTR        LL_HRTIM_TIM_GetEventFilter \n
  *  EEFxR2      EEJFLTR        LL_HRTIM_TIM_GetEventFilter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  * @retval filter This parameter can be one of the following values:
  *         For all timing units:
  *         @arg @ref LL_HRTIM_NO_FILTERING
  *         @arg @ref LL_HRTIM_BLK_RST_CMP1
  *         @arg @ref LL_HRTIM_BLK_RST_CMP2
  *         @arg @ref LL_HRTIM_BLK_RST_CMP3
  *         @arg @ref LL_HRTIM_BLK_RST_CMP4
  *         @arg @ref LL_HRTIM_BLK_CMP1_RST
  *         @arg @ref LL_HRTIM_BLK_CMP2_RST
  *         @arg @ref LL_HRTIM_BLK_CMP1_CMP2
  *         @arg @ref LL_HRTIM_BLK_CMP3_CMP4
  *         @arg @ref LL_HRTIM_BLK_PER_CMP1
  *         @arg @ref LL_HRTIM_BLK_PER_CMP2
  *         @arg @ref LL_HRTIM_BLK_RST_CMP1_CPPSTAT
  *         @arg @ref LL_HRTIM_WIN_RST_CMP2
  *         @arg @ref LL_HRTIM_WIN_RST_CMP3
  *         @arg @ref LL_HRTIM_WIN_CMP1_RST
  *         @arg @ref LL_HRTIM_WIN_CMP2_RST
  *         @arg @ref LL_HRTIM_WIN_CMP1_CMP2
  *         @arg @ref LL_HRTIM_WIN_CMP3_CMP4
  *         For timer A:
  *         @arg @ref LL_HRTIM_BLK_TIMA_TBRST_TBCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TBRST_TBCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMA_CHB2
  *         @arg @ref LL_HRTIM_BLK_TIMA_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TCRST_TCCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMA_TFRST_TFCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TDRST_TDCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMA_TERST_TECMP2
  *         @arg @ref LL_HRTIM_WIN_TIMA_TBRST_TBCMP2
  *         @arg @ref LL_HRTIM_WIN_TIMA_TBCMP2_TBRST
  *         @arg @ref LL_HRTIM_WIN_TIMA_TBCMP1_TBRST
  *         For timer B:
  *         @arg @ref LL_HRTIM_BLK_TIMB_TARST_TACMP1
  *         @arg @ref LL_HRTIM_BLK_TIMB_TARST_TACMP4
  *         @arg @ref LL_HRTIM_BLK_TIMB_CHA2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMB_TCRST_TCCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TFRST_TFCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TDRST_TDCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMB_TERST_TECMP1
  *         @arg @ref LL_HRTIM_WIN_TIMB_TARST_TACMP2
  *         @arg @ref LL_HRTIM_WIN_TIMB_TACMP2_TARST
  *         @arg @ref LL_HRTIM_WIN_TIMB_TACMP1_TARST
  *         For timer C:
  *         @arg @ref LL_HRTIM_BLK_TIMC_TARST_TACMP2
  *         @arg @ref LL_HRTIM_BLK_TIMC_TBRST_TBCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMC_TBRST_TBCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMC_TFRST_TFCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMC_TDRST_TDCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMC_TDRST_TDCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMC_CHD2
  *         @arg @ref LL_HRTIM_BLK_TIMC_TERST_TECMP4
  *         @arg @ref LL_HRTIM_WIN_TIMC_TDRST_TDCMP2
  *         @arg @ref LL_HRTIM_WIN_TIMC_TDCMP2_TDRST
  *         @arg @ref LL_HRTIM_WIN_TIMC_TDCMP1_TDRST
  *         For timer D:
  *         @arg @ref LL_HRTIM_BLK_TIMD_TARST_TACMP1
  *         @arg @ref LL_HRTIM_BLK_TIMD_TBRST_TBCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMD_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIMD_TCRST_TCCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMD_CHC2
  *         @arg @ref LL_HRTIM_BLK_TIMD_TERST_TECMP1
  *         @arg @ref LL_HRTIM_BLK_TIMD_TERST_TECMP4
  *         @arg @ref LL_HRTIM_BLK_TIMD_TFRST_TFCMP4
  *         @arg @ref LL_HRTIM_WIN_TIMD_TCRST_TCCMP2
  *         @arg @ref LL_HRTIM_WIN_TIMD_TCCMP2_TCRST
  *         @arg @ref LL_HRTIM_WIN_TIMD_TCCMP1_TCRST
  *         For timer E:
  *         @arg @ref LL_HRTIM_BLK_TIME_TARST_TACMP2
  *         @arg @ref LL_HRTIM_BLK_TIME_TBRST_TBCMP1
  *         @arg @ref LL_HRTIM_BLK_TIME_TCRST_TCCMP1
  *         @arg @ref LL_HRTIM_BLK_TIME_TFRST_TFCMP4
  *         @arg @ref LL_HRTIM_BLK_TIME_CHF2
  *         @arg @ref LL_HRTIM_BLK_TIME_TDRST_TDCMP1
  *         @arg @ref LL_HRTIM_BLK_TIME_TDRST_TDCMP4
  *         @arg @ref LL_HRTIM_BLK_TIME_CHD2
  *         @arg @ref LL_HRTIM_WIN_TIME_TFRST_TFCMP2
  *         @arg @ref LL_HRTIM_WIN_TIME_TFCMP2_TFRST
  *         @arg @ref LL_HRTIM_WIN_TIME_TFCMP1_TFRST
  *         For timer F:
  *         @arg @ref LL_HRTIM_BLK_TIMF_TARST_TACMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_TBRST_TBCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMF_TCRST_TCCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_TDRST_TDCMP2
  *         @arg @ref LL_HRTIM_BLK_TIMF_TDRST_TDCMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_TERST_TECMP1
  *         @arg @ref LL_HRTIM_BLK_TIMF_TERST_TECMP4
  *         @arg @ref LL_HRTIM_BLK_TIMF_CHE2
  *         @arg @ref LL_HRTIM_WIN_TIMF_TERST_TECMP2
  *         @arg @ref LL_HRTIM_WIN_TIMF_TECMP2_TERST
  *         @arg @ref LL_HRTIM_WIN_TIMF_TECMP1_TERST
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetEventFilter(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t event)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].EEFxR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] +
                                                             LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_EEFxR1_EEAFLTR) << (LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent])) >>
          LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]);
}

/**
  * @brief  Enable or disable event latch mechanism for a given timer.
  * @rmtoll
  *  EEFxR1      EEALTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR1      EEBLTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR1      EECLTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR1      EEDLTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR1      EEELTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR2      EEFLTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR2      EEGLTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR2      EEHLTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR2      EEILTCH        LL_HRTIM_TIM_SetEventLatchStatus \n
  *  EEFxR2      EEJLTCH        LL_HRTIM_TIM_SetEventLatchStatus
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  * @param  LatchStatus This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EELATCH_DISABLE
  *         @arg @ref LL_HRTIM_EELATCH_ENABLE
  * @note This function must not be called when the timer counter is enabled.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetEventLatchStatus(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t event,
                                                      uint32_t LatchStatus)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].EEFxR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] +
                                                       LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_EEFxR1_EEALTCH << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   (LatchStatus << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
}

/**
  * @brief  Get actual event latch status for a given timer.
  * @rmtoll
  *  EEFxR1      EEALTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR1      EEBLTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR1      EECLTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR1      EEDLTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR1      EEELTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR2      EEFLTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR2      EEGLTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR2      EEHLTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR2      EEILTCH        LL_HRTIM_TIM_GetEventLatchStatus \n
  *  EEFxR2      EEJLTCH        LL_HRTIM_TIM_GetEventLatchStatus
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  * @retval LatchStatus This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EELATCH_DISABLE
  *         @arg @ref LL_HRTIM_EELATCH_ENABLE
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetEventLatchStatus(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t event)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].EEFxR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim] +
                                                             LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_EEFxR1_EEALTCH) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]) >>
          LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]);
}

/**
  * @brief  Select the Trigger-Half operating mode for a given timer.
  * @rmtoll
  *  TIMxCR2    TRGHLF       LL_HRTIM_TIM_SetTriggeredHalfMode \n
  *  TIMxCR2    TRGHLFT      LL_HRTIM_TIM_SetTriggeredHalfMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TRIGHALF_ENABLE
  *         @arg @ref LL_HRTIM_TRIGHALF_DISABLE
  *         @arg @ref LL_HRTIM_TRIGHALF_ENABLE_TIMEOUT
  * @note   This bitfield defines whether the compare 2 register is
  *         behaving in standard mode (compare match issued as soon
  *         as counter equals compare value) or in triggered-half mode.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetTriggeredHalfMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, (HRTIM_TIMxCR2_TRGHLFT | HRTIM_TIMxCR2_TRGHLF), Mode);
}

/**
  * @brief  Get the Trigger-Half operating mode for a given timer.
  * @rmtoll
  *  TIMxCR2    TRGHLF       LL_HRTIM_TIM_GetTriggeredHalfMode \n
  *  TIMxCR2    TRGHLFT      LL_HRTIM_TIM_GetTriggeredHalfMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   indicates whether the compare 2 register behaves
  *         in standard mode (compare match issued as soon as counter
  *         equals compare value) or in triggered-half mode.
  * @retval Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TRIGHALF_ENABLE
  *         @arg @ref LL_HRTIM_TRIGHALF_DISABLE
  *         @arg @ref LL_HRTIM_TRIGHALF_ENABLE_TIMEOUT
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetTriggeredHalfMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(* preg, (HRTIM_TIMxCR2_TRGHLFT | HRTIM_TIMxCR2_TRGHLF)));
}

/**
  * @brief  Select the compare 1 operating mode.
  * @rmtoll
  *  TIMxCR2    GTCMP1      LL_HRTIM_TIM_SetComp1Mode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_GTCMP1_EQUAL
  *         @arg @ref LL_HRTIM_GTCMP1_GREATER
  * @note   This bit defines the compare 1 operating mode:
  * @note   0: the compare 1 event is generated when the counter is equal to the compare value
  * @note   1: the compare 1 event is generated when the counter is greater than the compare value
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetComp1Mode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_GTCMP1, Mode);
}

/**
  * @brief  Get the selected compare 1 operating mode.
  * @rmtoll
  *  TIMxCR2    GTCMP1      LL_HRTIM_TIM_GetComp1Mode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This bit reports the compare 1 operating mode:
  * @note   0: the compare 1 event is generated when the counter is equal to the compare value
  * @note   1: the compare 1 event is generated when the counter is greater than the compare value
  * @retval  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_GTCMP1_EQUAL
  *         @arg @ref LL_HRTIM_GTCMP1_GREATER
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetComp1Mode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(* preg, HRTIM_TIMxCR2_GTCMP1));
}

/**
  * @brief  Select the compare 3 operating mode.
  * @rmtoll
  *  TIMxCR2    GTCMP3      LL_HRTIM_TIM_SetComp3Mode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_GTCMP3_EQUAL
  *         @arg @ref LL_HRTIM_GTCMP3_GREATER
  * @note   This bit defines the compare 3 operating mode:
  * @note   0: the compare 3 event is generated when the counter is equal to the compare value
  * @note   1: the compare 3 event is generated when the counter is greater than the compare value
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetComp3Mode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_GTCMP3, (Mode));
}

/**
  * @brief  Get the selected compare 3 operating mode.
  * @rmtoll
  *  TIMxCR2    GTCMP3      LL_HRTIM_TIM_GetComp1Mode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note   This bit reports the compare 3 operating mode:
  * @note   0: the compare 3 event is generated when the counter is equal to the compare value
  * @note   1: the compare 3 event is generated when the counter is greater than the compare value
  * @retval Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_GTCMP3_EQUAL
  *         @arg @ref LL_HRTIM_GTCMP3_GREATER
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetComp3Mode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0U].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(* preg, HRTIM_TIMxCR2_GTCMP3));
}

/**
  * @brief  Select the roll-over mode.
  * @rmtoll
  *  TIMxCR2    ROM      LL_HRTIM_TIM_SetRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  * @note Only significant in up-down counting mode (see function @ref LL_HRTIM_TIM_SetCountingMode()).
  * @note Only concerns the Roll-over event with the following destinations: Update trigger, IRQ
  *      and DMA requests, repetition counter decrement and External event filtering.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_ROM, (Mode << HRTIM_TIMxCR2_ROM_Pos));
}

/**
  * @brief  Get selected the roll-over mode.
  * @rmtoll
  *  TIMxCR2    ROM      LL_HRTIM_TIM_GetRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Mode returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_ROM) >> HRTIM_TIMxCR2_ROM_Pos);
}

/**
  * @brief  Select fault and event roll-over mode.
  * @rmtoll
  *  TIMxCR2    FEROM      LL_HRTIM_TIM_SetFaultEventRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  * @note Only significant in up-down counting mode (see function @ref LL_HRTIM_TIM_SetCountingMode()).
  * @note only concerns the Roll-over event used by the fault and event counters.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetFaultEventRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_FEROM, (Mode << HRTIM_TIMxCR2_FEROM_Pos));
}

/**
  * @brief  Get selected fault and event role-over mode.
  * @rmtoll
  *  TIMxCR2    FEROM      LL_HRTIM_TIM_GetFaultEventRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  Mode returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetFaultEventRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_FEROM) >> HRTIM_TIMxCR2_FEROM_Pos);
}

/**
  * @brief  Select the Burst mode roll-over mode.
  * @rmtoll
  *  TIMxCR2    BMROM      LL_HRTIM_TIM_SetBMRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  * @note Only significant in up-down counting mode (see function @ref LL_HRTIM_TIM_SetCountingMode()).
  * @note Only concerns the Roll-over event used in the Burst mode controller, as clock as as burst mode trigger.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetBMRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_BMROM, (Mode << HRTIM_TIMxCR2_BMROM_Pos));
}

/**
  * @brief  Get selected Burst mode roll-over mode.
  * @rmtoll
  *  TIMxCR2    ROM      LL_HRTIM_TIM_GetBMRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  Mode returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetBMRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_BMROM) >> HRTIM_TIMxCR2_BMROM_Pos);
}

/**
  * @brief  Select the ADC roll-over mode.
  * @rmtoll
  *  TIMxCR2    ADROM      LL_HRTIM_TIM_SetADCRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  * @note Only significant in up-down counting mode (see function @ref LL_HRTIM_TIM_SetCountingMode()).
  * @note Only concerns the Roll-over event used to trigger the ADC.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetADCRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_ADROM, (Mode << HRTIM_TIMxCR2_ADROM_Pos));
}

/**
  * @brief  Get selected ADC roll-over mode.
  * @rmtoll
  *  TIMxCR2    ADROM      LL_HRTIM_TIM_GetADCRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  Mode returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetADCRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_ADROM) >> HRTIM_TIMxCR2_ADROM_Pos);
}

/**
  * @brief  Select the output roll-over mode.
  * @rmtoll
  *  TIMxCR2    OUTROM      LL_HRTIM_TIM_SetOutputRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  * @note Only significant in up-down counting mode (see function @ref LL_HRTIM_TIM_SetCountingMode()).
  * @note Only concerns concerns the Roll-over event which sets and/or resets the outputs,
  *       as per HRTIM_SETxyR and HRTIM_RSTxyR settings (see function @ref LL_HRTIM_OUT_SetOutputSetSrc()
  *       and function @ref LL_HRTIM_OUT_SetOutputResetSrc() respectively).
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetOutputRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_OUTROM, (Mode << HRTIM_TIMxCR2_OUTROM_Pos));
}

/**
  * @brief  Get selected output roll-over mode.
  * @rmtoll
  *  TIMxCR2    OUTROM      LL_HRTIM_TIM_GetOutputRollOverMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  Mode returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_PER
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_RST
  *         @arg @ref LL_HRTIM_ROLLOVER_MODE_BOTH
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetOutputRollOverMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_OUTROM) >> HRTIM_TIMxCR2_OUTROM_Pos);
}

/**
  * @brief  Select the counting mode.
  * @rmtoll
  *  TIMxCR2    UDM      LL_HRTIM_TIM_SetCountingMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_COUNTING_MODE_UP
  *         @arg @ref LL_HRTIM_COUNTING_MODE_UP_DOWN
  * @note The up-down counting mode is available for both continuous and single-shot
  *       (retriggerable and nonretriggerable) operating modes
  *       (see function @ref LL_HRTIM_TIM_SetCounterMode()).
  * @note The counter roll-over event is defined differently in-up-down counting mode to
  *       support various operating condition.
  *       See @ref LL_HRTIM_TIM_SetCounterMode()
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetCountingMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_UDM, Mode);
}

/**
  * @brief  Get selected counting mode.
  * @rmtoll
  *  TIMxCR2    UDM      LL_HRTIM_TIM_GetCountingMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  Mode returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_COUNTING_MODE_UP
  *         @arg @ref LL_HRTIM_COUNTING_MODE_UP_DOWN
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetCountingMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_UDM));
}

/**
  * @brief  Select Dual Channel DAC Reset trigger.
  * @rmtoll
  *  TIMxCR2    DCDR      LL_HRTIM_TIM_SetDualDacResetTrigger
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DCDR_RESET
  *         @arg @ref LL_HRTIM_DCDR_OUT1_SET
  * @note Significant only when Dual channel DAC trigger is enabled
  *       (see function @ref LL_HRTIM_TIM_EnableDualDacTrigger()).
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetDualDacResetTrigger(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_DCDR, Mode);
}

/**
  * @brief  Get selected Dual Channel DAC Reset trigger.
  * @rmtoll
  *  TIMxCR2    DCDR      LL_HRTIM_TIM_GetDualDacResetTrigger
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  Trigger returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_DCDR_RESET
  *         @arg @ref LL_HRTIM_DCDR_OUT1_SET
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetDualDacResetTrigger(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_DCDR));
}

/**
  * @brief  Select Dual Channel DAC Reset trigger.
  * @rmtoll
  *  TIMxCR2    DCDS      LL_HRTIM_TIM_SetDualDacStepTrigger
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DCDS_CMP2
  *         @arg @ref LL_HRTIM_DCDS_OUT1_RESET
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetDualDacStepTrigger(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(* preg, HRTIM_TIMxCR2_DCDS, Mode);
}

/**
  * @brief  Get selected Dual Channel DAC Reset trigger.
  * @rmtoll
  *  TIMxCR2    DCDS      LL_HRTIM_TIM_GetDualDacStepTrigger
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  Trigger returned value can be one of the following values:
  *         @arg @ref LL_HRTIM_DCDS_CMP2
  *         @arg @ref LL_HRTIM_DCDS_OUT1_RESET
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetDualDacStepTrigger(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_TIMxCR2_DCDS));
}

/**
  * @brief  Enable Dual Channel DAC trigger.
  * @rmtoll
  *  TIMxCR2      DCDE      LL_HRTIM_TIM_EnableDualDacTrigger
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note Only significant when balanced Idle mode is enabled (see function @ref LL_HRTIM_TIM_SetDLYPRTMode()).
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableDualDacTrigger(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(* preg, HRTIM_TIMxCR2_DCDE);
}

/**
  * @brief  Disable Dual Channel DAC trigger.
  * @rmtoll
  *  TIMxCR2      DCDE      LL_HRTIM_TIM_DisableDualDacTrigger
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableDualDacTrigger(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(* preg, HRTIM_TIMxCR2_DCDE);
}

/**
  * @brief  Indicate whether Dual Channel DAC trigger is enabled for a given timer.
  * @rmtoll
  *  TIMxCR2      DCDE      LL_HRTIM_TIM_IsEnabledDualDacTrigger
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DCDE bit in HRTIM_TIMxCR2 register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledDualDacTrigger(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(* preg, HRTIM_TIMxCR2_DCDE) == (HRTIM_TIMxCR2_DCDE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the external event counter threshold.
  * @rmtoll
  *  TIMxEEFR3    EEVYCNT      LL_HRTIM_TIM_SetEventCounterThreshold \n
  *  TIMxEEFR3    EEVZCNT      LL_HRTIM_TIM_SetEventCounterThreshold
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  * @param  threshold This parameter can be a number between Min_Data=0 and Max_Data=63
  * @note The external event is propagated to the timer only if the number
  *       of active edges is greater than the external event counter threshold.
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetEventCounterThreshold(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                           uint32_t event_counter, uint32_t threshold)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  STM32_MODIFY_REG(*preg,
                   (HRTIM_TIMxEEFR3_EEVYCNT << event_counter),
                   threshold << (HRTIM_TIMxEEFR3_EEVYCNT_Pos + event_counter));
}

/**
  * @brief  Get the programmed external event counter threshold.
  * @rmtoll
  *  TIMxEEFR3    EEVYCNT      LL_HRTIM_TIM_GetEventCounterThreshold \n
  *  TIMxEEFR3    EEVZCNT      LL_HRTIM_TIM_GetEventCounterThreshold
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  * @retval threshold Value between Min_Data=0 and Max_Data=63.
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetEventCounterThreshold(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                               uint32_t event_counter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  return ((STM32_READ_BIT(*preg, (uint32_t)(HRTIM_TIMxEEFR3_EEVYCNT) << event_counter)) >>
          ((HRTIM_TIMxEEFR3_EEVYCNT_Pos + event_counter)));
}

/**
  * @brief  Select the external event counter source.
  * @rmtoll
  *  TIMxEEFR3    EEVYSEL      LL_HRTIM_TIM_SetEventCounterSource \n
  *  TIMxEEFR3    EEVZSEL      LL_HRTIM_TIM_SetEventCounterSource
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  * @note External event counting is only valid for edge-sensitive
  *       external events (See function LL_HRTIM_EE_Config() and function
  *       LL_HRTIM_EE_SetSensitivity()).
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetEventCounterSource(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                        uint32_t event_counter, uint32_t event)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));
  uint32_t ievent = (uint32_t)(STM32_POSITION_VAL(event));

  STM32_MODIFY_REG(*preg,
                   (HRTIM_TIMxEEFR3_EEVYSEL << event_counter),
                   ievent << (HRTIM_TIMxEEFR3_EEVYSEL_Pos + event_counter));
}

/**
  * @brief  get the selected external event counter source.
  *       LL_HRTIM_EE_SetSensitivity()).
  * @rmtoll
  *  TIMxEEFR3    EEVYSEL      LL_HRTIM_TIM_GetEventCounterSource \n
  *  TIMxEEFR3    EEVZSEL      LL_HRTIM_TIM_GetEventCounterSource
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  * @retval  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEVA
  *         @arg @ref LL_HRTIM_EEVB
  *         @arg @ref LL_HRTIM_EEVC
  *         @arg @ref LL_HRTIM_EEVD
  *         @arg @ref LL_HRTIM_EEVE
  *         @arg @ref LL_HRTIM_EEVF
  *         @arg @ref LL_HRTIM_EEVG
  *         @arg @ref LL_HRTIM_EEVH
  *         @arg @ref LL_HRTIM_EEVI
  *         @arg @ref LL_HRTIM_EEVJ
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetEventCounterSource(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                            uint32_t event_counter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  uint32_t ievent = (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_TIMxEEFR3_EEVYSEL) << (event_counter))) >>
                    ((HRTIM_TIMxEEFR3_EEVYSEL_Pos + event_counter));

  return ((uint32_t)0x1U << ievent)  ;
}

/**
  * @brief  Select the external event counter reset mode.
  * @rmtoll
  *  TIMxEEFR3    EEVYRSTM      LL_HRTIM_TIM_SetEventCounterResetMode \n
  *  TIMxEEFR3    EEVZRSTM      LL_HRTIM_TIM_SetEventCounterResetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_RSTMODE_UNCONDITIONAL
  *         @arg @ref LL_HRTIM_EE_COUNTER_RSTMODE_CONDITIONAL
  */
__STATIC_INLINE void LL_HRTIM_TIM_SetEventCounterResetMode(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                           uint32_t event_counter, uint32_t mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  STM32_MODIFY_REG(*preg, (HRTIM_TIMxEEFR3_EEVYRSTM << (event_counter)), mode << (event_counter));
}

/**
  * @brief  Get selected external event counter reset mode.
  * @rmtoll
  *  TIMxEEFR3    EEVYRSTM      LL_HRTIM_TIM_GetEventCounterResetMode \n
  *  TIMxEEFR3    EEVZRSTM      LL_HRTIM_TIM_GetEventCounterResetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  * @retval  mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_RSTMODE_UNCONDITIONAL
  *         @arg @ref LL_HRTIM_EE_COUNTER_RSTMODE_CONDITIONAL
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_GetEventCounterResetMode(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                               uint32_t event_counter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  return ((STM32_READ_BIT(*preg, (uint32_t)(HRTIM_TIMxEEFR3_EEVYRSTM) << (event_counter))) >> (event_counter))  ;
}

/**
  * @brief  Reset the external event counter.
  * @rmtoll
  *  TIMxEEFR3    EEVYCRES      LL_HRTIM_TIM_ResetEventCounter \n
  *  TIMxEEFR3    EEVZCRES      LL_HRTIM_TIM_ResetEventCounter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  */
__STATIC_INLINE void LL_HRTIM_TIM_ResetEventCounter(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t event_counter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  STM32_SET_BIT(*preg, (uint32_t)(HRTIM_TIMxEEFR3_EEVYCRES) << event_counter);
}

/**
  * @brief  Enable the external event counter.
  * @rmtoll
  *  TIMxEEFR3    EEVYCE      LL_HRTIM_TIM_EnableEventCounter \n
  *  TIMxEEFR3    EEVZCE      LL_HRTIM_TIM_EnableEventCounter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableEventCounter(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                     uint32_t event_counter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  STM32_SET_BIT(*preg, (uint32_t)(HRTIM_TIMxEEFR3_EEVYCE) << event_counter);
}

/**
  * @brief  Disable the external event counter.
  * @rmtoll
  *  TIMxEEFR3    EEVYCE      LL_HRTIM_TIM_DisableEventCounter \n
  *  TIMxEEFR3    EEVZCE      LL_HRTIM_TIM_DisableEventCounter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableEventCounter(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                      uint32_t event_counter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  STM32_CLEAR_BIT(*preg, (HRTIM_TIMxEEFR3_EEVYCE << event_counter));
}


/**
  * @brief  Indicate whether the external event counter is enabled for a given timer.
  * @rmtoll
  *  TIMxEEFR3    EEVYCE      LL_HRTIM_TIM_IsEnabledEventCounter \n
  *  TIMxEEFR3    EEVZCE      LL_HRTIM_TIM_IsEnabledEventCounter
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  event_counter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_COUNTER_Y
  *         @arg @ref LL_HRTIM_EE_COUNTER_Z
  * @retval State of EEVxCE bit in RTIM_TIMxEEFR3 register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledEventCounter(const HRTIM_TypeDef *hrtimx, uint32_t timer,
                                                            uint32_t event_counter)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - STM32_POSITION_VAL(LL_HRTIM_TIMA));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[itim].TIMxEEFR3)));

  uint32_t temp; /* MISRAC-2012 compliance */
  temp = STM32_READ_BIT(*preg, (uint32_t)(HRTIM_TIMxEEFR3_EEVYCE) << event_counter);

  return ((temp == ((uint32_t)(HRTIM_TIMxEEFR3_EEVYCE) << event_counter)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_Dead_Time_Configuration Dead_Time_Configuration
  * @{
  */

/**
  * @brief  Configure the dead time insertion feature for a given timer.
  * @rmtoll
  *  DTxR      DTPRSC     LL_HRTIM_DT_Config \n
  *  DTxR      SDTF       LL_HRTIM_DT_Config \n
  *  DTxR      SDRT       LL_HRTIM_DT_Config
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL16 or ... or @ref LL_HRTIM_DT_PRESCALER_DIV8
  *         @arg @ref LL_HRTIM_DT_RISING_POSITIVE or @ref LL_HRTIM_DT_RISING_NEGATIVE
  *         @arg @ref LL_HRTIM_DT_FALLING_POSITIVE or @ref LL_HRTIM_DT_FALLING_NEGATIVE
  */
__STATIC_INLINE void LL_HRTIM_DT_Config(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t configuration)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_DTxR_SDTF | HRTIM_DTxR_DTPRSC | HRTIM_DTxR_SDTR, configuration);
}

/**
  * @brief  Set the deadtime prescaler value.
  * @rmtoll
  *  DTxR      DTPRSC     LL_HRTIM_DT_SetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL16
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL8
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL4
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL2
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV8
  */
__STATIC_INLINE void LL_HRTIM_DT_SetPrescaler(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t prescaler)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_DTxR_DTPRSC, prescaler);
}

/**
  * @brief  Get actual deadtime prescaler value.
  * @rmtoll
  *  DTxR      DTPRSC     LL_HRTIM_DT_GetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL16
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL8
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL4
  *         @arg @ref LL_HRTIM_DT_PRESCALER_MUL2
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_DT_PRESCALER_DIV8
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetPrescaler(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_DTxR_DTPRSC));
}

/**
  * @brief  Set the deadtime rising value.
  * @rmtoll
  *  DTxR      DTR       LL_HRTIM_DT_SetRisingValue
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  rising_value Value between 0 and 0x1FF
  */
__STATIC_INLINE void LL_HRTIM_DT_SetRisingValue(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t rising_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_DTxR_DTR, rising_value);
}

/**
  * @brief  Get actual deadtime rising value.
  * @rmtoll
  *  DTxR      DTR       LL_HRTIM_DT_GetRisingValue
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval rising_value Value between 0 and 0x1FF.
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetRisingValue(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_DTxR_DTR));
}

/**
  * @brief  Set the deadtime sign on rising edge.
  * @rmtoll
  *  DTxR      SDTR       LL_HRTIM_DT_SetRisingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  rising_sign This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_RISING_POSITIVE
  *         @arg @ref LL_HRTIM_DT_RISING_NEGATIVE
  */
__STATIC_INLINE void LL_HRTIM_DT_SetRisingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t rising_sign)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_DTxR_SDTR, rising_sign);
}

/**
  * @brief  Get actual deadtime sign on rising edge.
  * @rmtoll
  *  DTxR      SDTR       LL_HRTIM_DT_GetRisingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval rising_sign This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_RISING_POSITIVE
  *         @arg @ref LL_HRTIM_DT_RISING_NEGATIVE
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetRisingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_DTxR_SDTR));
}

/**
  * @brief  Set the deadime falling value.
  * @rmtoll
  *  DTxR      DTF       LL_HRTIM_DT_SetFallingValue
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  falling_value Value between 0 and 0x1FF
  */
__STATIC_INLINE void LL_HRTIM_DT_SetFallingValue(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t falling_value)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_DTxR_DTF, falling_value << HRTIM_DTxR_DTF_Pos);
}

/**
  * @brief  Get actual deadtime falling value.
  * @rmtoll
  *  DTxR      DTF       LL_HRTIM_DT_GetFallingValue
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval falling_value Value between 0 and 0x1FF.
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetFallingValue(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_DTxR_DTF)) >> HRTIM_DTxR_DTF_Pos);
}

/**
  * @brief  Set the deadtime sign on falling edge.
  * @rmtoll
  *  DTxR      SDTF       LL_HRTIM_DT_SetFallingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  falling_sign This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_FALLING_POSITIVE
  *         @arg @ref LL_HRTIM_DT_FALLING_NEGATIVE
  */
__STATIC_INLINE void LL_HRTIM_DT_SetFallingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t falling_sign)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_DTxR_SDTF, falling_sign);
}

/**
  * @brief  Get actual deadtime sign on falling edge.
  * @rmtoll
  *  DTxR      SDTF       LL_HRTIM_DT_GetFallingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval falling_sign This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_FALLING_POSITIVE
  *         @arg @ref LL_HRTIM_DT_FALLING_NEGATIVE
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetFallingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_DTxR_SDTF));
}

/**
  * @brief  Lock the deadtime value and sign on rising edge.
  * @rmtoll
  *  DTxR      DTRLK       LL_HRTIM_DT_LockRising
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DT_LockRising(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_DTxR_DTRLK);
}

/**
  * @brief  Get the deadtime value and sign on rising edge lock.
  * @rmtoll
  *  DTxR      DTRLK       LL_HRTIM_DT_GetLockRising
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DTRLK bit in HRTIM_DTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetLockRising(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_DTxR_DTRLK) == (HRTIM_DTxR_DTRLK)) ? 1UL : 0UL);
}

/**
  * @brief  Lock the deadtime sign on rising edge.
  * @rmtoll
  *  DTxR      DTRSLK       LL_HRTIM_DT_LockRisingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DT_LockRisingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_DTxR_DTRSLK);
}

/**
  * @brief  Get the deadtime sign on rising edge lock.
  * @rmtoll
  *  DTxR      DTRSLK       LL_HRTIM_DT_GetLockRisingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DTRSLK bit in HRTIM_DTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetLockRisingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_DTxR_DTRSLK) == (HRTIM_DTxR_DTRSLK)) ? 1UL : 0UL);
}

/**
  * @brief  Lock the deadtime value and sign on falling edge.
  * @rmtoll
  *  DTxR      DTFLK       LL_HRTIM_DT_LockFalling
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DT_LockFalling(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_DTxR_DTFLK);
}

/**
  * @brief  Get the deadtime value and sign on falling edge lock.
  * @rmtoll
  *  DTxR      DTFLK       LL_HRTIM_DT_GetLockFalling
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DTFLK bit in HRTIM_DTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetLockFalling(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_DTxR_DTFLK) == (HRTIM_DTxR_DTFLK)) ? 1UL : 0UL);
}

/**
  * @brief  Lock the deadtime sign on falling edge.
  * @rmtoll
  *  DTxR      DTFSLK       LL_HRTIM_DT_LockFallingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DT_LockFallingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_DTxR_DTFSLK);
}

/**
  * @brief  Get the deadtime sign on falling edge lock.
  * @rmtoll
  *  DTxR      DTFSLK       LL_HRTIM_DT_GetLockFallingSign
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DTFSLK bit in HRTIM_DTxR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetLockFallingSign(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return ((STM32_READ_BIT(*preg, HRTIM_DTxR_DTFSLK) == (HRTIM_DTxR_DTFSLK)) ? 1UL : 0UL);
}

/**
  * @brief  Set the deadtime mode.
  * @rmtoll
  *  DTxR      DTM       LL_HRTIM_DT_SetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_MODE_COMPLEMENTARY
  *         @arg @ref LL_HRTIM_DT_MODE_INSERTION
  *         @arg @ref LL_HRTIM_DT_MODE_INSERTION_AND_DISARM
  */
__STATIC_INLINE void LL_HRTIM_DT_SetMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t Mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_DTxR_DTM, Mode);
}

/**
  * @brief  Get the deadtime mode.
  * @rmtoll
  *  DTxR      DTM       LL_HRTIM_DT_GetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval Mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_DT_MODE_COMPLEMENTARY
  *         @arg @ref LL_HRTIM_DT_MODE_INSERTION
  *         @arg @ref LL_HRTIM_DT_MODE_INSERTION_AND_DISARM
  */
__STATIC_INLINE uint32_t LL_HRTIM_DT_GetMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __I uint32_t *preg = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].DTxR) +
                                                   LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_DTxR_DTM));
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_Chopper_Mode_Configuration Chopper_Mode_Configuration
  * @{
  */

/**
  * @brief  Configure the chopper stage for a given timer.
  * @rmtoll
  *  CHPxR      CARFRQ       LL_HRTIM_CHP_Config \n
  *  CHPxR      CARDTY       LL_HRTIM_CHP_Config \n
  *  CHPxR      STRTPW       LL_HRTIM_CHP_Config
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  configuration This parameter must be a combination of all the following values:
  *         Prescaler
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV16
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV32
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV48
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV64
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV80
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV96
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV112
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV128
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV144
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV160
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV176
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV192
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV208
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV224
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV240
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV256
  *
  *         Duty cycle
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_0
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_125
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_250
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_375
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_500
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_625
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_750
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_875
  *
  *         Start pulse width
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_16
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_32
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_48
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_64
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_80
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_96
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_112
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_128
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_144
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_160
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_176
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_192
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_208
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_224
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_240
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_256
  * @note This function must not be called if the chopper mode is already
  *       enabled for one of the timer outputs.
  */
__STATIC_INLINE void LL_HRTIM_CHP_Config(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t configuration)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CHPxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_CHPxR_STRTPW | HRTIM_CHPxR_CARDTY | HRTIM_CHPxR_CARFRQ, configuration);
}

/**
  * @brief  Set prescaler determining the carrier frequency to be added on top
  *         of the timer output signals when chopper mode is enabled.
  * @rmtoll
  *  CHPxR      CARFRQ       LL_HRTIM_CHP_SetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV16
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV32
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV48
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV64
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV80
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV96
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV112
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV128
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV144
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV160
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV176
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV192
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV208
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV224
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV240
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV256
  * @note This function must not be called if the chopper mode is already
  *       enabled for one of the timer outputs.
  */
__STATIC_INLINE void LL_HRTIM_CHP_SetPrescaler(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t prescaler)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CHPxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_CHPxR_CARFRQ, prescaler);
}

/**
  * @brief  Get actual chopper stage prescaler value.
  * @rmtoll
  *  CHPxR      CARFRQ       LL_HRTIM_CHP_GetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV16
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV32
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV48
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV64
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV80
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV96
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV112
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV128
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV144
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV160
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV176
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV192
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV208
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV224
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV240
  *         @arg @ref LL_HRTIM_CHP_PRESCALER_DIV256
  */
__STATIC_INLINE uint32_t LL_HRTIM_CHP_GetPrescaler(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CHPxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_CHPxR_CARFRQ));
}

/**
  * @brief  Set the chopper duty cycle.
  * @rmtoll
  *  CHPxR      CARDTY       LL_HRTIM_CHP_SetDutyCycle
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  duty_cycle This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_0
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_125
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_250
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_375
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_500
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_625
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_750
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_875
  * @note Duty cycle can be adjusted by 1/8 step (from 0/8 up to 7/8)
  * @note This function must not be called if the chopper mode is already
  *       enabled for one of the timer outputs.
  */
__STATIC_INLINE void LL_HRTIM_CHP_SetDutyCycle(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t duty_cycle)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CHPxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_CHPxR_CARDTY, duty_cycle);
}

/**
  * @brief  Get actual chopper duty cycle.
  * @rmtoll
  *  CHPxR      CARDTY       LL_HRTIM_CHP_GetDutyCycle
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval duty_cycle This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_0
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_125
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_250
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_375
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_500
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_625
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_750
  *         @arg @ref LL_HRTIM_CHP_DUTYCYCLE_875
  */
__STATIC_INLINE uint32_t LL_HRTIM_CHP_GetDutyCycle(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CHPxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_CHPxR_CARDTY));
}

/**
  * @brief  Set the start pulse width.
  * @rmtoll
  *  CHPxR      STRPW       LL_HRTIM_CHP_SetPulseWidth
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  pulse_width This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_16
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_32
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_48
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_64
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_80
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_96
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_112
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_128
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_144
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_160
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_176
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_192
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_208
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_224
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_240
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_256
  * @note This function must not be called if the chopper mode is already
  *       enabled for one of the timer outputs.
  */
__STATIC_INLINE void LL_HRTIM_CHP_SetPulseWidth(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t pulse_width)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CHPxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_MODIFY_REG(*preg, HRTIM_CHPxR_STRTPW, pulse_width);
}

/**
  * @brief  Get actual start pulse width.
  * @rmtoll
  *  CHPxR      STRPW       LL_HRTIM_CHP_GetPulseWidth
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval pulse_width This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_16
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_32
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_48
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_64
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_80
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_96
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_112
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_128
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_144
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_160
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_176
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_192
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_208
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_224
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_240
  *         @arg @ref LL_HRTIM_CHP_PULSEWIDTH_256
  */
__STATIC_INLINE uint32_t LL_HRTIM_CHP_GetPulseWidth(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CHPxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_BIT(*preg, HRTIM_CHPxR_STRTPW));
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_Output_Management Output_Management
  * @{
  */

/**
  * @brief  Set the timer output set source.
  * @rmtoll
  *  SETx1R      SST          LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      RESYNC       LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      PER          LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      CMP1         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      CMP2         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      CMP3         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      CMP4         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      MSTPER       LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      MSTCMP1      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      MSTCMP2      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      MSTCMP3      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      MSTCMP4      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT1     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT2     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT3     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT4     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT5     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT6     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT7     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT8     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      TIMEVNT9     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTA      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTB      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTC      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTD      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTE      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTF      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTG      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTH      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTI      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      EXEVNTJ      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx1R      UPDATE       LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      SST          LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      RESYNC       LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      PER          LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      CMP1         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      CMP2         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      CMP3         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      CMP4         LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      MSTPER       LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      MSTCMP1      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      MSTCMP2      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      MSTCMP3      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      MSTCMP4      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT1     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT2     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT3     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT4     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT5     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT6     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT7     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT8     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      TIMEVNT9     LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTA      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTB      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTC      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTD      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTE      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTF      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTG      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTH      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTI      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      EXEVNTJ      LL_HRTIM_OUT_SetOutputSetSrc \n
  *  SETx2R      UPDATE       LL_HRTIM_OUT_SetOutputSetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param set_src This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_OUTPUTSET_NONE
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVA
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVB
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVC
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVD
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVE
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVF
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVG
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVH
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVI
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVJ
  *         @arg @ref LL_HRTIM_OUTPUTSET_RESYNC
  *         @arg @ref LL_HRTIM_OUTPUTSET_UPDATE
  *         @arg @ref LL_HRTIM_OUTPUTSET_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP4
  *         For timer A:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TFCMP4
  *         For timer B:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TFCMP3
  *         For timer C:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TFCMP3
  *         For timer E:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TFCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TFCMP4
  *         For timer F:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TECMP3
  *         (source = TIMy and destination = TIMx, Compare Unit = CMPz).
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetOutputSetSrc(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t set_src)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].SETx1R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_SETxR[iOutput]));
  STM32_WRITE_REG(*preg, set_src);
}

/**
  * @brief  Get the timer output set source.
  * @rmtoll
  *  SETx1R      SST          LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      RESYNC       LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      PER          LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      CMP1         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      CMP2         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      CMP3         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      CMP4         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      MSTPER       LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      MSTCMP1      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      MSTCMP2      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      MSTCMP3      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      MSTCMP4      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT1     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT2     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT3     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT4     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT5     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT6     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT7     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT8     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      TIMEVNT9     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTA      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTB      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTC      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTD      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTE      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTF      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTG      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTH      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTI      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      EXEVNTJ      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx1R      UPDATE       LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      SST          LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      RESYNC       LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      PER          LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      CMP1         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      CMP2         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      CMP3         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      CMP4         LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      MSTPER       LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      MSTCMP1      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      MSTCMP2      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      MSTCMP3      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      MSTCMP4      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT1     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT2     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT3     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT4     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT5     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT6     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT7     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT8     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      TIMEVNT9     LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTA      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTB      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTC      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTD      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTE      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTF      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTG      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTH      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTI      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      EXEVNTJ      LL_HRTIM_OUT_GetOutputSetSrc \n
  *  SETx2R      UPDATE       LL_HRTIM_OUT_GetOutputSetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval set_src This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_OUTPUTSET_NONE
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVA
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVB
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVC
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVD
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVE
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVF
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVG
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVH
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVI
  *         @arg @ref LL_HRTIM_OUTPUTSET_EEVJ
  *         @arg @ref LL_HRTIM_OUTPUTSET_RESYNC
  *         @arg @ref LL_HRTIM_OUTPUTSET_UPDATE
  *         @arg @ref LL_HRTIM_OUTPUTSET_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_CMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_MASTER_CMP4
  *         For timer A:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMA_TFCMP4
  *         For timer B:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMB_TFCMP3
  *         For timer C:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMD_TFCMP3
  *         For timer E:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TFCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIME_TFCMP4
  *         For timer F:
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTSET_TIMF_TECMP3
  *         (source = TIMy and destination = TIMx, Compare Unit = CMPz).
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetOutputSetSrc(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].SETx1R) +
                                                             LL_HRTIM_REG_OFFSET_TAB_SETxR[iOutput]));
  return (uint32_t) STM32_READ_REG(*preg);
}

/**
  * @brief  Set the timer output reset source.
  * @rmtoll
  *  RSTx1R      SRT          LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      RESYNC       LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      PER          LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      CMP1         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      CMP2         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      CMP3         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      CMP4         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      MSTPER       LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      MSTCMP1      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      MSTCMP2      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      MSTCMP3      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      MSTCMP4      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT1     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT2     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT3     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT4     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT5     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT6     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT7     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT8     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      TIMEVNT9     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTA      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTB      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTC      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTD      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTE      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTF      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTG      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTH      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTI      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      EXEVNTJ      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx1R      UPDATE       LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      SRT          LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      RESYNC       LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      PER          LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      CMP1         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      CMP2         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      CMP3         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      CMP4         LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      MSTPER       LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      MSTCMP1      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      MSTCMP2      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      MSTCMP3      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      MSTCMP4      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT1     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT2     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT3     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT4     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT5     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT6     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT7     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT8     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      TIMEVNT9     LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTA      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTB      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTC      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTD      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTE      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTF      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTG      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTH      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTI      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      EXEVNTJ      LL_HRTIM_OUT_SetOutputResetSrc \n
  *  RSTx2R      UPDATE       LL_HRTIM_OUT_SetOutputResetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param reset_src This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_NONE
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVA
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVB
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVC
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVD
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVE
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVF
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVG
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVH
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVI
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVJ
  *         @arg @ref LL_HRTIM_OUTPUTRESET_RESYNC
  *         @arg @ref LL_HRTIM_OUTPUTRESET_UPDATE
  *         @arg @ref LL_HRTIM_OUTPUTRESET_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP4
  *         For timer A:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TFCMP4
  *         For timer B:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TFCMP3
  *         For timer C:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TFCMP3
  *         For timer E:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TFCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TFCMP4
  *         For timer F:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TECMP3
  *         (source = TIMy and destination = TIMx, Compare Unit = CMPz).
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetOutputResetSrc(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t reset_src)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].RSTx1R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_SETxR[iOutput]));
  STM32_WRITE_REG(*preg, reset_src);
}

/**
  * @brief  Get the timer output set source.
  * @rmtoll
  *  RSTx1R      SRT          LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      RESYNC       LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      PER          LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      CMP1         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      CMP2         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      CMP3         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      CMP4         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      MSTPER       LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      MSTCMP1      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      MSTCMP2      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      MSTCMP3      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      MSTCMP4      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT1     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT2     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT3     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT4     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT5     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT6     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT7     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT8     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      TIMEVNT9     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTA      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTB      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTC      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTD      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTE      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTF      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTG      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTH      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTI      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      EXEVNTJ      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx1R      UPDATE       LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      SRT          LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      RESYNC       LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      PER          LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      CMP1         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      CMP2         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      CMP3         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      CMP4         LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      MSTPER       LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      MSTCMP1      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      MSTCMP2      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      MSTCMP3      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      MSTCMP4      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT1     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT2     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT3     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT4     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT5     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT6     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT7     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT8     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      TIMEVNT9     LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTA      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTB      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTC      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTD      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTE      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTF      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTG      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTH      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTI      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      EXEVNTJ      LL_HRTIM_OUT_GetOutputResetSrc \n
  *  RSTx2R      UPDATE       LL_HRTIM_OUT_GetOutputResetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval reset_src This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_NONE
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVA
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVB
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVC
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVD
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVE
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVF
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVG
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVH
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVI
  *         @arg @ref LL_HRTIM_OUTPUTRESET_EEVJ
  *         @arg @ref LL_HRTIM_OUTPUTRESET_RESYNC
  *         @arg @ref LL_HRTIM_OUTPUTRESET_UPDATE
  *         @arg @ref LL_HRTIM_OUTPUTRESET_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_CMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_PERIOD
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_MASTER_CMP4
  *         For timer A:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMA_TFCMP4
  *         For timer B:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TCCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMB_TFCMP3
  *         For timer C:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TACMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TECMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMC_TFCMP2
  *         For timer D:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TACMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TBCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TECMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TECMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TFCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMD_TFCMP3
  *         For timer E:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TACMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TBCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TCCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TDCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TDCMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TFCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIME_TFCMP4
  *         For timer F:
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TACMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TBCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TBCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TCCMP1
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TCCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TDCMP3
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TDCMP4
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TECMP2
  *         @arg @ref LL_HRTIM_OUTPUTRESET_TIMF_TECMP3
  *         (source = TIMy and destination = TIMx, Compare Unit = CMPz).
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetOutputResetSrc(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].RSTx1R) +
                                                             LL_HRTIM_REG_OFFSET_TAB_SETxR[iOutput]));
  return (uint32_t) STM32_READ_REG(*preg);
}

/**
  * @brief  Configure a timer output.
  * @rmtoll
  *  OUTxR      POL1          LL_HRTIM_OUT_Config \n
  *  OUTxR      IDLEM1        LL_HRTIM_OUT_Config \n
  *  OUTxR      IDLES1        LL_HRTIM_OUT_Config \n
  *  OUTxR      FAULT1        LL_HRTIM_OUT_Config \n
  *  OUTxR      CHP1          LL_HRTIM_OUT_Config \n
  *  OUTxR      DIDL1         LL_HRTIM_OUT_Config \n
  *  OUTxR      POL2          LL_HRTIM_OUT_Config \n
  *  OUTxR      IDLEM2        LL_HRTIM_OUT_Config \n
  *  OUTxR      IDLES2        LL_HRTIM_OUT_Config \n
  *  OUTxR      FAULT2        LL_HRTIM_OUT_Config \n
  *  OUTxR      CHP2          LL_HRTIM_OUT_Config \n
  *  OUTxR      DIDL2         LL_HRTIM_OUT_Config
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  configuration This parameter must be a combination of all the following values:
  *         Polarity
  *         @arg @ref LL_HRTIM_OUT_POSITIVE_POLARITY
  *         @arg @ref LL_HRTIM_OUT_NEGATIVE_POLARITY
  *
  *         Idle level
  *         @arg @ref LL_HRTIM_OUT_IDLELEVEL_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_IDLELEVEL_ACTIVE
  *
  *         Fault state
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_NONE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_ACTIVE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_HIGHZ
  *
  *         Burst mode
  *         @arg @ref LL_HRTIM_OUT_NO_IDLE
  *         @arg @ref LL_HRTIM_OUT_IDLE_WHEN_BURST
  *
  *         Chopper mode
  *         @arg @ref LL_HRTIM_OUT_CHOPPERMODE_DISABLE
  *         @arg @ref LL_HRTIM_OUT_CHOPPERMODE_ENABLE
  *
  *         Deadtime upon burst mode idle entry
  *         @arg @ref LL_HRTIM_OUT_BM_ENTRYMODE_REGULAR
  *         @arg @ref LL_HRTIM_OUT_BM_ENTRYMODE_DELAYED
  */
__STATIC_INLINE void LL_HRTIM_OUT_Config(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t configuration)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg, (LL_HRTIM_OUT_CONFIG_MASK << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   (configuration << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]));
}

/**
  * @brief  Set the polarity of a timer output.
  * @rmtoll
  *  OUTxR      POL1          LL_HRTIM_OUT_SetPolarity \n
  *  OUTxR      POL2          LL_HRTIM_OUT_SetPolarity
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_POSITIVE_POLARITY
  *         @arg @ref LL_HRTIM_OUT_NEGATIVE_POLARITY
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetPolarity(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t polarity)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_OUTxR_POL1 << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   (polarity << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]));
}

/**
  * @brief  Get actual polarity of the timer output.
  * @rmtoll
  *  OUTxR      POL1          LL_HRTIM_OUT_GetPolarity \n
  *  OUTxR      POL2          LL_HRTIM_OUT_GetPolarity
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval polarity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_POSITIVE_POLARITY
  *         @arg @ref LL_HRTIM_OUT_NEGATIVE_POLARITY
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetPolarity(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return (STM32_READ_BIT(*preg,
                         (uint32_t)(HRTIM_OUTxR_POL1) << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]) >>
          LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Set the output IDLE mode.
  * @rmtoll
  *  OUTxR      IDLEM1          LL_HRTIM_OUT_SetIdleMode \n
  *  OUTxR      IDLEM2          LL_HRTIM_OUT_SetIdleMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  idle_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_NO_IDLE
  *         @arg @ref LL_HRTIM_OUT_IDLE_WHEN_BURST
  * @note This function must not be called when the burst mode is active
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetIdleMode(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t idle_mode)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_OUTxR_IDLEM1 << (LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput])),
                   (idle_mode << (LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput])));
}

/**
  * @brief  Get actual output IDLE mode.
  * @rmtoll
  *  OUTxR      IDLEM1          LL_HRTIM_OUT_GetIdleMode \n
  *  OUTxR      IDLEM2          LL_HRTIM_OUT_GetIdleMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval idle_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_NO_IDLE
  *         @arg @ref LL_HRTIM_OUT_IDLE_WHEN_BURST
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetIdleMode(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_OUTxR_IDLEM1) << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]) >>
          LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Set the output IDLE level.
  * @rmtoll
  *  OUTxR      IDLES1          LL_HRTIM_OUT_SetIdleLevel \n
  *  OUTxR      IDLES2          LL_HRTIM_OUT_SetIdleLevel
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  idle_level This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_IDLELEVEL_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_IDLELEVEL_ACTIVE
  * @note This function must be called prior enabling the timer.
  * @note Idle level isn't relevant when the output idle mode is set to LL_HRTIM_OUT_NO_IDLE.
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetIdleLevel(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t idle_level)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_OUTxR_IDLES1 << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   (idle_level << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]));
}

/**
  * @brief  Get actual output IDLE level.
  * @rmtoll
  *  OUTxR      IDLES1          LL_HRTIM_OUT_GetIdleLevel \n
  *  OUTxR      IDLES2          LL_HRTIM_OUT_GetIdleLevel
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval idle_level This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_IDLELEVEL_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_IDLELEVEL_ACTIVE
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetIdleLevel(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_OUTxR_IDLES1) << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]) >>
          LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Set the output FAULT state.
  * @rmtoll
  *  OUTxR      FAULT1          LL_HRTIM_OUT_SetFaultState \n
  *  OUTxR      FAULT2          LL_HRTIM_OUT_SetFaultState
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  fault_state This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_NONE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_ACTIVE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_HIGHZ
  * @note This function must not called when the timer is enabled and a fault
  *       channel is enabled at timer level.
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetFaultState(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t fault_state)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_OUTxR_FAULT1 << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   (fault_state << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]));
}

/**
  * @brief  Get actual FAULT state.
  * @rmtoll
  *  OUTxR      FAULT1          LL_HRTIM_OUT_GetFaultState \n
  *  OUTxR      FAULT2          LL_HRTIM_OUT_GetFaultState
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval fault_state This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_NONE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_ACTIVE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_FAULTSTATE_HIGHZ
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetFaultState(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_OUTxR_FAULT1) << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]) >>
          LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Set the output chopper mode.
  * @rmtoll
  *  OUTxR      CHP1          LL_HRTIM_OUT_SetChopperMode \n
  *  OUTxR      CHP2          LL_HRTIM_OUT_SetChopperMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  chopper_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_CHOPPERMODE_DISABLE
  *         @arg @ref LL_HRTIM_OUT_CHOPPERMODE_ENABLE
  * @note This function must not called when the timer is enabled.
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetChopperMode(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t chopper_mode)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_OUTxR_CHP1 << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   (chopper_mode << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]));
}

/**
  * @brief  Get actual output chopper mode.
  * @rmtoll
  *  OUTxR      CHP1          LL_HRTIM_OUT_GetChopperMode \n
  *  OUTxR      CHP2          LL_HRTIM_OUT_GetChopperMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval chopper_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_CHOPPERMODE_DISABLE
  *         @arg @ref LL_HRTIM_OUT_CHOPPERMODE_ENABLE
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetChopperMode(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return (STM32_READ_BIT(*preg,
                         (uint32_t)(HRTIM_OUTxR_CHP1) << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]) >>
          LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Set the output burst mode entry mode.
  * @rmtoll
  *  OUTxR      DIDL1          LL_HRTIM_OUT_SetBMEntryMode \n
  *  OUTxR      DIDL2          LL_HRTIM_OUT_SetBMEntryMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  burst_mode_entry_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_BM_ENTRYMODE_REGULAR
  *         @arg @ref LL_HRTIM_OUT_BM_ENTRYMODE_DELAYED
  * @note This function must not called when the timer is enabled.
  */
__STATIC_INLINE void LL_HRTIM_OUT_SetBMEntryMode(const HRTIM_TypeDef *hrtimx, uint32_t output,
                                                 uint32_t burst_mode_entry_mode)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_OUTxR_DIDL1 << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   (burst_mode_entry_mode << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]));
}

/**
  * @brief  Get actual output burst mode entry mode.
  * @rmtoll
  *  OUTxR      DIDL1          LL_HRTIM_OUT_GetBMEntryMode \n
  *  OUTxR      DIDL2          LL_HRTIM_OUT_GetBMEntryMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval burst_mode_entry_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_BM_ENTRYMODE_REGULAR
  *         @arg @ref LL_HRTIM_OUT_BM_ENTRYMODE_DELAYED
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetBMEntryMode(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].OUTxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_OUTxR_DIDL1) << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]) >>
          LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Get the level (active or inactive) of the designated output when the
  *         delayed protection was triggered.
  * @rmtoll
  *  TIMxISR      O1STAT          LL_HRTIM_OUT_GetDLYPRTOutStatus \n
  *  TIMxISR      O2STAT          LL_HRTIM_OUT_GetDLYPRTOutStatus
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval output_level This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_LEVEL_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_LEVEL_ACTIVE
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetDLYPRTOutStatus(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxISR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return ((STM32_READ_BIT(*preg, (uint32_t)(HRTIM_TIMxISR_O1STAT) << LL_HRTIM_REG_SHIFT_TAB_OxSTAT[iOutput]) >>
           LL_HRTIM_REG_SHIFT_TAB_OxSTAT[iOutput]) >> HRTIM_TIMxISR_O1STAT_Pos);
}

/**
  * @brief  Force the timer output to its active or inactive level.
  * @rmtoll
  *  SETx1R      SST          LL_HRTIM_OUT_ForceLevel \n
  *  RSTx1R      SRT          LL_HRTIM_OUT_ForceLevel \n
  *  SETx2R      SST          LL_HRTIM_OUT_ForceLevel \n
  *  RSTx2R      SRT          LL_HRTIM_OUT_ForceLevel
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  output_level This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_LEVEL_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_LEVEL_ACTIVE
  */
__STATIC_INLINE void LL_HRTIM_OUT_ForceLevel(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t output_level)
{
  const uint8_t REG_OFFSET_TAB_OUT_LEVEL[] =
  {
    0x04U,   /* 0: LL_HRTIM_OUT_LEVEL_INACTIVE  */
    0x00U    /* 1: LL_HRTIM_OUT_LEVEL_ACTIVE  */
  };

  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].SETx1R) +
                                                       LL_HRTIM_REG_OFFSET_TAB_SETxR[iOutput] +
                                                       REG_OFFSET_TAB_OUT_LEVEL[output_level]));
  STM32_SET_BIT(*preg, HRTIM_SETx1R_SST);
}

/**
  * @brief  Get actual output level, before the output stage (chopper, polarity).
  * @rmtoll
  *  TIMxISR     O1CPY          LL_HRTIM_OUT_GetLevel \n
  *  TIMxISR     O2CPY          LL_HRTIM_OUT_GetLevel
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval output_level This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUT_LEVEL_INACTIVE
  *         @arg @ref LL_HRTIM_OUT_LEVEL_ACTIVE
  */
__STATIC_INLINE uint32_t LL_HRTIM_OUT_GetLevel(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxISR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  return ((STM32_READ_BIT(*preg, (uint32_t)(HRTIM_TIMxISR_O1CPY) << LL_HRTIM_REG_SHIFT_TAB_OxSTAT[iOutput]) >>
           LL_HRTIM_REG_SHIFT_TAB_OxSTAT[iOutput]) >>
          HRTIM_TIMxISR_O1CPY_Pos);
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_External_Event_management External_Event_management
  * @{
  */

/**
  * @brief  Configure external event conditioning.
  * @rmtoll
  *  EECR1     EE1SRC          LL_HRTIM_EE_Config \n
  *  EECR1     EE1POL          LL_HRTIM_EE_Config \n
  *  EECR1     EE1SNS          LL_HRTIM_EE_Config \n
  *  EECR1     EE1FAST         LL_HRTIM_EE_Config \n
  *  EECR1     EE2SRC          LL_HRTIM_EE_Config \n
  *  EECR1     EE2POL          LL_HRTIM_EE_Config \n
  *  EECR1     EE2SNS          LL_HRTIM_EE_Config \n
  *  EECR1     EE2FAST         LL_HRTIM_EE_Config \n
  *  EECR1     EE3SRC          LL_HRTIM_EE_Config \n
  *  EECR1     EE3POL          LL_HRTIM_EE_Config \n
  *  EECR1     EE3SNS          LL_HRTIM_EE_Config \n
  *  EECR1     EE3FAST         LL_HRTIM_EE_Config \n
  *  EECR1     EE4SRC          LL_HRTIM_EE_Config \n
  *  EECR1     EE4POL          LL_HRTIM_EE_Config \n
  *  EECR1     EE4SNS          LL_HRTIM_EE_Config \n
  *  EECR1     EE4FAST         LL_HRTIM_EE_Config \n
  *  EECR1     EE5SRC          LL_HRTIM_EE_Config \n
  *  EECR1     EE5POL          LL_HRTIM_EE_Config \n
  *  EECR1     EE5SNS          LL_HRTIM_EE_Config \n
  *  EECR1     EE5FAST         LL_HRTIM_EE_Config \n
  *  EECR2     EE6SRC          LL_HRTIM_EE_Config \n
  *  EECR2     EE6POL          LL_HRTIM_EE_Config \n
  *  EECR2     EE6SNS          LL_HRTIM_EE_Config \n
  *  EECR2     EE7SRC          LL_HRTIM_EE_Config \n
  *  EECR2     EE7POL          LL_HRTIM_EE_Config \n
  *  EECR2     EE7SNS          LL_HRTIM_EE_Config \n
  *  EECR2     EE8SRC          LL_HRTIM_EE_Config \n
  *  EECR2     EE8POL          LL_HRTIM_EE_Config \n
  *  EECR2     EE8SNS          LL_HRTIM_EE_Config \n
  *  EECR2     EE9SRC          LL_HRTIM_EE_Config \n
  *  EECR2     EE9POL          LL_HRTIM_EE_Config \n
  *  EECR2     EE9SNS          LL_HRTIM_EE_Config \n
  *  EECR2     EE10SRC         LL_HRTIM_EE_Config \n
  *  EECR2     EE10POL         LL_HRTIM_EE_Config \n
  *  EECR2     EE10SNS         LL_HRTIM_EE_Config \n
  *  EECR4     EE11SRC         LL_HRTIM_EE_Config \n
  *  EECR4     EE11POL         LL_HRTIM_EE_Config \n
  *  EECR4     EE11SNS         LL_HRTIM_EE_Config \n
  *  EECR4     EE11FAST        LL_HRTIM_EE_Config \n
  *  EECR4     EE12SRC         LL_HRTIM_EE_Config \n
  *  EECR4     EE12POL         LL_HRTIM_EE_Config \n
  *  EECR4     EE12SNS         LL_HRTIM_EE_Config \n
  *  EECR4     EE12FAST        LL_HRTIM_EE_Config \n
  *  EECR4     EE13SRC         LL_HRTIM_EE_Config \n
  *  EECR4     EE13POL         LL_HRTIM_EE_Config \n
  *  EECR4     EE13SNS         LL_HRTIM_EE_Config \n
  *  EECR4     EE13FAST        LL_HRTIM_EE_Config \n
  *  EECR5     EE14SRC         LL_HRTIM_EE_Config \n
  *  EECR5     EE14POL         LL_HRTIM_EE_Config \n
  *  EECR5     EE14SNS         LL_HRTIM_EE_Config \n
  *  EECR5     EE15SRC         LL_HRTIM_EE_Config \n
  *  EECR5     EE15POL         LL_HRTIM_EE_Config \n
  *  EECR5     EE15SNS         LL_HRTIM_EE_Config \n
  *  EECR5     EE16SRC         LL_HRTIM_EE_Config \n
  *  EECR5     EE16POL         LL_HRTIM_EE_Config \n
  *  EECR5     EE16SNS         LL_HRTIM_EE_Config \n
  *  EECR7     EE1SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE2SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE3SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE4SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE5SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE6SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE7SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE8SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE9SRC2         LL_HRTIM_EE_Config \n
  *  EECR7     EE10SRC2        LL_HRTIM_EE_Config \n
  *  EECR7     EE11SRC2        LL_HRTIM_EE_Config \n
  *  EECR7     EE12SRC2        LL_HRTIM_EE_Config \n
  *  EECR7     EE13SRC2        LL_HRTIM_EE_Config \n
  *  EECR7     EE14SRC2        LL_HRTIM_EE_Config \n
  *  EECR7     EE15SRC2        LL_HRTIM_EE_Config \n
  *  EECR7     EE16SRC2        LL_HRTIM_EE_Config
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @param  configuration This parameter must be a combination of all the following values:
  *         Source (EExSrc1..EExSrc8)
  *         For external event 1:
  *         @arg @ref LL_HRTIM_EEV1SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV1SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV1SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV1SRC_PLAY1_OUT0 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_BKIN2
  *         For external event 2:
  *         @arg @ref LL_HRTIM_EEV2SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV2SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM2_TRGO
  *         @arg @ref LL_HRTIM_EEV2SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV2SRC_PLAY1_OUT1 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM8_BKIN2
  *         For external event 3:
  *         @arg @ref LL_HRTIM_EEV3SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV3SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM3_TRGO
  *         @arg @ref LL_HRTIM_EEV3SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV3SRC_PLAY1_OUT2 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM20_BKIN2 (*)
  * @endif
  *         For external event 4:
  *         @arg @ref LL_HRTIM_EEV4SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV4SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV4SRC_PLAY1_OUT3 (*)
  * @endif
  *         For external event 5:
  *         @arg @ref LL_HRTIM_EEV5SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP3
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV5SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV5SRC_PLAY1_OUT4 (*)
  * @endif
  *         For external event 6:
  *         @arg @ref LL_HRTIM_EEV6SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV6SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV6SRC_PLAY1_OUT5 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV6SRC_TIM1_BKIN1
  *         For external event 7:
  *         @arg @ref LL_HRTIM_EEV7SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP7
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV7SRC_ADC3_AWD1 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV7SRC_PLAY1_OUT6 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV7SRC_TIM8_BKIN1
  *         For external event 8:
  *         @arg @ref LL_HRTIM_EEV8SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP3
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV8SRC_ADC3_AWD2 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV8SRC_PLAY1_OUT7 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV8SRC_TIM20_BKIN1 (*)
  * @endif
  *         For external event 9:
  *         @arg @ref LL_HRTIM_EEV9SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP4
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV9SRC_PLAY1_OUT8 (*)
  * @endif
  *         For external event 10:
  *         @arg @ref LL_HRTIM_EEV10SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV10SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV10SRC_TIM6_TRGO
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV10SRC_ADC3_AWD3 (*)
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV10SRC_PLAY1_OUT9 (*)
  * @endif
  * @endif
  *         For external event 11:
  *         @arg @ref LL_HRTIM_EEV11SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV11SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV11SRC_TIM9_TRGO
  *         @arg @ref LL_HRTIM_EEV11SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV11SRC_PLAY1_OUT10 (*)
  * @endif
  *         For external event 12:
  *         @arg @ref LL_HRTIM_EEV12SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV12SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV12SRC_TIM12_TRGO
  *         @arg @ref LL_HRTIM_EEV12SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV12SRC_PLAY1_OUT11 (*)
  * @endif
  *         For external event 13:
  *         @arg @ref LL_HRTIM_EEV13SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV13SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV13SRC_TIM15_TRGO
  *         @arg @ref LL_HRTIM_EEV13SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV13SRC_PLAY1_OUT12 (*)
  * @endif
  *         For external event 14:
  *         @arg @ref LL_HRTIM_EEV14SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV14SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV14SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV14SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV14SRC_PLAY1_OUT13 (*)
  * @endif
  *         For external event 15:
  *         @arg @ref LL_HRTIM_EEV15SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV15SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV15SRC_TIM8_TRGO
  *         @arg @ref LL_HRTIM_EEV15SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV15SRC_PLAY1_OUT14 (*)
  * @endif
  *         For external event 16:
  *         @arg @ref LL_HRTIM_EEV16SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV16SRC_COMP3
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV16SRC_TIM20_TRGO
  * @endif
  *         @arg @ref LL_HRTIM_EEV16SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV16SRC_PLAY1_OUT15 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  *
  *         Polarity
  *         @arg @ref LL_HRTIM_EE_POLARITY_HIGH
  *         @arg @ref LL_HRTIM_EE_POLARITY_LOW
  *
  *         Sentitivity
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_LEVEL
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_RISING
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_FALLING
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_RISING_FALLING
  *
  *         Fast mode
  *         @arg @ref LL_HRTIM_EE_FASTMODE_DISABLE
  *         @arg @ref LL_HRTIM_EE_FASTMODE_ENABLE
  *
  * @note This function must not be called when the timer counter is enabled.
  * @note Fast mode is available only for LL_HRTIM_EVENT_1..5, 11..13.
  */
__STATIC_INLINE void LL_HRTIM_EE_Config(HRTIM_TypeDef *hrtimx, uint32_t event, uint32_t configuration)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  uint32_t shift_count = ievent << 1U;
  uint32_t eexsrc_2 = (configuration & HRTIM_EEV_SRC_2) >> HRTIM_EEV_SRC_2_POS;

  STM32_MODIFY_REG(*preg,
                   (LL_HRTIM_EE_CONFIG_MASK << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   ((configuration & ~(HRTIM_EEV_SRC_2)) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
  STM32_MODIFY_REG(hrtimx->sCommonRegs.EECR7,
                   (uint32_t)(HRTIM_EECR7_EE1SRC << shift_count),
                   (eexsrc_2 == 0U) ? (uint32_t)0U : ((uint32_t)1U << (uint32_t)shift_count));
}

/**
  * @brief  Set the external event source.
  * @rmtoll
  *  EECR1     EE1SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR1     EE2SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR1     EE3SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR1     EE4SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR1     EE5SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR2     EE6SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR2     EE7SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR2     EE8SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR2     EE9SRC          LL_HRTIM_EE_SetSrc \n
  *  EECR2     EE10SRC         LL_HRTIM_EE_SetSrc \n
  *  EECR4     EE11SRC         LL_HRTIM_EE_SetSrc \n
  *  EECR4     EE12SRC         LL_HRTIM_EE_SetSrc \n
  *  EECR4     EE13SRC         LL_HRTIM_EE_SetSrc \n
  *  EECR5     EE14SRC         LL_HRTIM_EE_SetSrc \n
  *  EECR5     EE15SRC         LL_HRTIM_EE_SetSrc \n
  *  EECR5     EE16SRC         LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE1SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE2SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE3SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE4SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE5SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE6SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE7SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE8SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE9SRC[2]       LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE10SRC[2]      LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE11SRC[2]      LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE12SRC[2]      LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE13SRC[2]      LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE14SRC[2]      LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE15SRC[2]      LL_HRTIM_EE_SetSrc \n
  *  EECR7     EE16SRC[2]      LL_HRTIM_EE_SetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @param  src This parameter can be a one of the following values:
  *         For external event 1:
  *         @arg @ref LL_HRTIM_EEV1SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV1SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV1SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV1SRC_PLAY1_OUT0 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_BKIN2
  *         For external event 2:
  *         @arg @ref LL_HRTIM_EEV2SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV2SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM2_TRGO
  *         @arg @ref LL_HRTIM_EEV2SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV2SRC_PLAY1_OUT1 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM8_BKIN2
  *         For external event 3:
  *         @arg @ref LL_HRTIM_EEV3SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV3SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM3_TRGO
  *         @arg @ref LL_HRTIM_EEV3SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV3SRC_PLAY1_OUT2 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM20_BKIN2 (*)
  * @endif
  *         For external event 4:
  *         @arg @ref LL_HRTIM_EEV4SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV4SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV4SRC_PLAY1_OUT3 (*)
  * @endif
  *         For external event 5:
  *         @arg @ref LL_HRTIM_EEV5SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP3
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV5SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV5SRC_PLAY1_OUT4 (*)
  * @endif
  *         For external event 6:
  *         @arg @ref LL_HRTIM_EEV6SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV6SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV6SRC_PLAY1_OUT5 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV6SRC_TIM1_BKIN1
  *         For external event 7:
  *         @arg @ref LL_HRTIM_EEV7SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP7
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV7SRC_ADC3_AWD1 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV7SRC_PLAY1_OUT6 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV7SRC_TIM8_BKIN1
  *         For external event 8:
  *         @arg @ref LL_HRTIM_EEV8SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP3
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV8SRC_ADC3_AWD2 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV8SRC_PLAY1_OUT7 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV8SRC_TIM20_BKIN1 (*)
  * @endif
  *         For external event 9:
  *         @arg @ref LL_HRTIM_EEV9SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP4
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV9SRC_PLAY1_OUT8 (*)
  * @endif
  *         For external event 10:
  *         @arg @ref LL_HRTIM_EEV10SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV10SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV10SRC_TIM6_TRGO
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV10SRC_ADC3_AWD3 (*)
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV10SRC_PLAY1_OUT9 (*)
  * @endif
  * @endif
  *         For external event 11:
  *         @arg @ref LL_HRTIM_EEV11SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV11SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV11SRC_TIM9_TRGO
  *         @arg @ref LL_HRTIM_EEV11SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV11SRC_PLAY1_OUT10 (*)
  * @endif
  *         For external event 12:
  *         @arg @ref LL_HRTIM_EEV12SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV12SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV12SRC_TIM12_TRGO
  *         @arg @ref LL_HRTIM_EEV12SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV12SRC_PLAY1_OUT11 (*)
  * @endif
  *         For external event 13:
  *         @arg @ref LL_HRTIM_EEV13SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV13SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV13SRC_TIM15_TRGO
  *         @arg @ref LL_HRTIM_EEV13SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV13SRC_PLAY1_OUT12 (*)
  * @endif
  *         For external event 14:
  *         @arg @ref LL_HRTIM_EEV14SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV14SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV14SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV14SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV14SRC_PLAY1_OUT13 (*)
  * @endif
  *         For external event 15:
  *         @arg @ref LL_HRTIM_EEV15SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV15SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV15SRC_TIM8_TRGO
  *         @arg @ref LL_HRTIM_EEV15SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV15SRC_PLAY1_OUT14 (*)
  * @endif
  *         For external event 16:
  *         @arg @ref LL_HRTIM_EEV16SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV16SRC_COMP3
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV16SRC_TIM20_TRGO
  * @endif
  *         @arg @ref LL_HRTIM_EEV16SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV16SRC_PLAY1_OUT15 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  */
__STATIC_INLINE void LL_HRTIM_EE_SetSrc(HRTIM_TypeDef *hrtimx, uint32_t event, uint32_t src)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  uint32_t shift_count = (uint32_t)((uint32_t)(ievent) << 1U);
  uint32_t eexsrc_2 = (src & HRTIM_EEV_SRC_2) >> HRTIM_EEV_SRC_2_POS;

  STM32_MODIFY_REG(*preg,
                   (HRTIM_EECR1_EE1SRC << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   ((src & ~(HRTIM_EEV_SRC_2)) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
  STM32_MODIFY_REG(hrtimx->sCommonRegs.EECR7,
                   (uint32_t)(HRTIM_EECR7_EE1SRC << shift_count),
                   (eexsrc_2 == 0U) ? (uint32_t)0U : ((uint32_t)1U << (uint32_t)shift_count));
}

/**
  * @brief  Get actual external event source.
  * @rmtoll
  *  EECR1     EE1SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR1     EE2SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR1     EE3SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR1     EE4SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR1     EE5SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR2     EE6SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR2     EE7SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR2     EE8SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR2     EE9SRC          LL_HRTIM_EE_GetSrc \n
  *  EECR2     EE10SRC         LL_HRTIM_EE_GetSrc \n
  *  EECR4     EE11SRC         LL_HRTIM_EE_GetSrc \n
  *  EECR4     EE12SRC         LL_HRTIM_EE_GetSrc \n
  *  EECR4     EE13SRC         LL_HRTIM_EE_GetSrc \n
  *  EECR5     EE14SRC         LL_HRTIM_EE_GetSrc \n
  *  EECR5     EE15SRC         LL_HRTIM_EE_GetSrc \n
  *  EECR5     EE16SRC         LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE1SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE2SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE3SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE4SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE5SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE6SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE7SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE8SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE9SRC[2]       LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE10SRC[2]      LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE11SRC[2]      LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE12SRC[2]      LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE13SRC[2]      LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE14SRC[2]      LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE15SRC[2]      LL_HRTIM_EE_GetSrc \n
  *  EECR7     EE16SRC[2]      LL_HRTIM_EE_GetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @retval src This parameter can be one of the following values:
  *         For external event 1:
  *         @arg @ref LL_HRTIM_EEV1SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV1SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV1SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV1SRC_PLAY1_OUT0 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_BKIN2
  *         For external event 2:
  *         @arg @ref LL_HRTIM_EEV2SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV2SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM2_TRGO
  *         @arg @ref LL_HRTIM_EEV2SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV2SRC_PLAY1_OUT1 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM8_BKIN2
  *         For external event 3:
  *         @arg @ref LL_HRTIM_EEV3SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV3SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM3_TRGO
  *         @arg @ref LL_HRTIM_EEV3SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV3SRC_PLAY1_OUT2 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM20_BKIN2 (*)
  * @endif
  *         For external event 4:
  *         @arg @ref LL_HRTIM_EEV4SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV4SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV4SRC_PLAY1_OUT3 (*)
  * @endif
  *         For external event 5:
  *         @arg @ref LL_HRTIM_EEV5SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP3
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV5SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV5SRC_PLAY1_OUT4 (*)
  * @endif
  *         For external event 6:
  *         @arg @ref LL_HRTIM_EEV6SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV6SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV6SRC_PLAY1_OUT5 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV6SRC_TIM1_BKIN1
  *         For external event 7:
  *         @arg @ref LL_HRTIM_EEV7SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP7
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV7SRC_ADC3_AWD1 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV7SRC_PLAY1_OUT6 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV7SRC_TIM8_BKIN1
  *         For external event 8:
  *         @arg @ref LL_HRTIM_EEV8SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP3
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV8SRC_ADC3_AWD2 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV8SRC_PLAY1_OUT7 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV8SRC_TIM20_BKIN1 (*)
  * @endif
  *         For external event 9:
  *         @arg @ref LL_HRTIM_EEV9SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP4
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV9SRC_PLAY1_OUT8 (*)
  * @endif
  *         For external event 10:
  *         @arg @ref LL_HRTIM_EEV10SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV10SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV10SRC_TIM6_TRGO
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV10SRC_ADC3_AWD3 (*)
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV10SRC_PLAY1_OUT9 (*)
  * @endif
  * @endif
  *         For external event 11:
  *         @arg @ref LL_HRTIM_EEV11SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV11SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV11SRC_TIM9_TRGO
  *         @arg @ref LL_HRTIM_EEV11SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV11SRC_PLAY1_OUT10 (*)
  * @endif
  *         For external event 12:
  *         @arg @ref LL_HRTIM_EEV12SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV12SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV12SRC_TIM12_TRGO
  *         @arg @ref LL_HRTIM_EEV12SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV12SRC_PLAY1_OUT11 (*)
  * @endif
  *         For external event 13:
  *         @arg @ref LL_HRTIM_EEV13SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV13SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV13SRC_TIM15_TRGO
  *         @arg @ref LL_HRTIM_EEV13SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV13SRC_PLAY1_OUT12 (*)
  * @endif
  *         For external event 14:
  *         @arg @ref LL_HRTIM_EEV14SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV14SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV14SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV14SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV14SRC_PLAY1_OUT13 (*)
  * @endif
  *         For external event 15:
  *         @arg @ref LL_HRTIM_EEV15SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV15SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV15SRC_TIM8_TRGO
  *         @arg @ref LL_HRTIM_EEV15SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV15SRC_PLAY1_OUT14 (*)
  * @endif
  *         For external event 16:
  *         @arg @ref LL_HRTIM_EEV16SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV16SRC_COMP3
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV16SRC_TIM20_TRGO
  * @endif
  *         @arg @ref LL_HRTIM_EEV16SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV16SRC_PLAY1_OUT15 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  */
__STATIC_INLINE uint32_t LL_HRTIM_EE_GetSrc(const HRTIM_TypeDef *hrtimx, uint32_t event)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  uint32_t src10 = STM32_READ_BIT(*preg, (uint32_t)(HRTIM_EECR1_EE1SRC) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]) >>
                   LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent];
  uint32_t src2 = STM32_READ_BIT(hrtimx->sCommonRegs.EECR7, HRTIM_EECR7_EE1SRC << (ievent << 1)) >> (ievent << 1);
  return ((src2 << HRTIM_EEV_SRC_2_POS) | src10);
}

/**
  * @brief  Set the polarity of an external event.
  * @rmtoll
  *  EECR1     EE1POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR1     EE2POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR1     EE3POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR1     EE4POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR1     EE5POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR2     EE6POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR2     EE7POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR2     EE8POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR2     EE9POL          LL_HRTIM_EE_SetPolarity \n
  *  EECR2     EE10POL         LL_HRTIM_EE_SetPolarity \n
  *  EECR4     EE11POL         LL_HRTIM_EE_SetPolarity \n
  *  EECR4     EE12POL         LL_HRTIM_EE_SetPolarity \n
  *  EECR4     EE13POL         LL_HRTIM_EE_SetPolarity \n
  *  EECR5     EE14POL         LL_HRTIM_EE_SetPolarity \n
  *  EECR5     EE15POL         LL_HRTIM_EE_SetPolarity \n
  *  EECR5     EE16POL         LL_HRTIM_EE_SetPolarity
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_POLARITY_HIGH
  *         @arg @ref LL_HRTIM_EE_POLARITY_LOW
  * @note This function must not be called when the timer counter is enabled.
  * @note event polarity is only significant when event detection is level-sensitive.
  */
__STATIC_INLINE void LL_HRTIM_EE_SetPolarity(const HRTIM_TypeDef *hrtimx, uint32_t event, uint32_t polarity)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_EECR1_EE1POL << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   (polarity << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
}

/**
  * @brief  Get actual polarity setting of an external event.
  * @rmtoll
  *  EECR1     EE1POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR1     EE2POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR1     EE3POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR1     EE4POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR1     EE5POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR2     EE6POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR2     EE7POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR2     EE8POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR2     EE9POL          LL_HRTIM_EE_GetPolarity \n
  *  EECR2     EE10POL         LL_HRTIM_EE_GetPolarity \n
  *  EECR4     EE11POL         LL_HRTIM_EE_GetPolarity \n
  *  EECR4     EE12POL         LL_HRTIM_EE_GetPolarity \n
  *  EECR4     EE13POL         LL_HRTIM_EE_GetPolarity \n
  *  EECR5     EE14POL         LL_HRTIM_EE_GetPolarity \n
  *  EECR5     EE15POL         LL_HRTIM_EE_GetPolarity \n
  *  EECR5     EE16POL         LL_HRTIM_EE_GetPolarity
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @retval polarity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_POLARITY_HIGH
  *         @arg @ref LL_HRTIM_EE_POLARITY_LOW
  */
__STATIC_INLINE uint32_t LL_HRTIM_EE_GetPolarity(const HRTIM_TypeDef *hrtimx, uint32_t event)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_EECR1_EE1POL) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]) >>
          LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]);
}

/**
  * @brief  Set the sensitivity of an external event.
  * @rmtoll
  *  EECR1     EE1SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR1     EE2SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR1     EE3SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR1     EE4SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR1     EE5SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR2     EE6SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR2     EE7SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR2     EE8SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR2     EE9SNS          LL_HRTIM_EE_SetSensitivity \n
  *  EECR2     EE10SNS         LL_HRTIM_EE_SetSensitivity \n
  *  EECR4     EE11SNS         LL_HRTIM_EE_SetSensitivity \n
  *  EECR4     EE12SNS         LL_HRTIM_EE_SetSensitivity \n
  *  EECR4     EE13SNS         LL_HRTIM_EE_SetSensitivity \n
  *  EECR5     EE14SNS         LL_HRTIM_EE_SetSensitivity \n
  *  EECR5     EE15SNS         LL_HRTIM_EE_SetSensitivity \n
  *  EECR5     EE16SNS         LL_HRTIM_EE_SetSensitivity
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @param  sensitivity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_LEVEL
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_RISING
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_FALLING
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_RISING_FALLING
  */

__STATIC_INLINE void LL_HRTIM_EE_SetSensitivity(const HRTIM_TypeDef *hrtimx, uint32_t event, uint32_t sensitivity)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_EECR1_EE1SNS << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   (sensitivity << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
}

/**
  * @brief  Get actual sensitivity setting of an external event.
  * @rmtoll
  *  EECR1     EE1SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR1     EE2SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR1     EE3SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR1     EE4SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR1     EE5SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR2     EE6SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR2     EE7SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR2     EE8SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR2     EE9SNS          LL_HRTIM_EE_GetSensitivity \n
  *  EECR2     EE10SNS         LL_HRTIM_EE_GetSensitivity \n
  *  EECR2     EE10SNS         LL_HRTIM_EE_GetSensitivity \n
  *  EECR4     EE11SNS         LL_HRTIM_EE_GetSensitivity \n
  *  EECR4     EE12SNS         LL_HRTIM_EE_GetSensitivity \n
  *  EECR4     EE13SNS         LL_HRTIM_EE_GetSensitivity \n
  *  EECR5     EE14SNS         LL_HRTIM_EE_GetSensitivity \n
  *  EECR5     EE15SNS         LL_HRTIM_EE_GetSensitivity \n
  *  EECR5     EE16SNS         LL_HRTIM_EE_GetSensitivity
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @retval sensitivity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_LEVEL
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_RISING
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_FALLING
  *         @arg @ref LL_HRTIM_EE_SENSITIVITY_RISING_FALLING
  */
__STATIC_INLINE uint32_t LL_HRTIM_EE_GetSensitivity(const HRTIM_TypeDef *hrtimx, uint32_t event)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_EECR1_EE1SNS) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]) >>
          LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]);
}

/**
  * @brief  Set the fast mode of an external event.
  * @rmtoll
  *  EECR1     EE1FAST         LL_HRTIM_EE_SetFastMode \n
  *  EECR1     EE2FAST         LL_HRTIM_EE_SetFastMode \n
  *  EECR1     EE3FAST         LL_HRTIM_EE_SetFastMode \n
  *  EECR1     EE4FAST         LL_HRTIM_EE_SetFastMode \n
  *  EECR1     EE5FAST         LL_HRTIM_EE_SetFastMode \n
  *  EECR2     EE11FAST        LL_HRTIM_EE_SetFastMode \n
  *  EECR2     EE12FAST        LL_HRTIM_EE_SetFastMode \n
  *  EECR2     EE13FAST        LL_HRTIM_EE_SetFastMode
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  * @param  fast_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_FASTMODE_DISABLE
  *         @arg @ref LL_HRTIM_EE_FASTMODE_ENABLE
  * @note This function must not be called when the timer counter is enabled.
  */
__STATIC_INLINE void LL_HRTIM_EE_SetFastMode(const HRTIM_TypeDef *hrtimx, uint32_t event, uint32_t fast_mode)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  STM32_MODIFY_REG(*preg,
                   (HRTIM_EECR1_EE1FAST << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   (fast_mode << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
}

/**
  * @brief  Get actual fast mode setting of an external event.
  * @rmtoll
  *  EECR1     EE1FAST         LL_HRTIM_EE_GetFastMode \n
  *  EECR1     EE2FAST         LL_HRTIM_EE_GetFastMode \n
  *  EECR1     EE3FAST         LL_HRTIM_EE_GetFastMode \n
  *  EECR1     EE4FAST         LL_HRTIM_EE_GetFastMode \n
  *  EECR1     EE5FAST         LL_HRTIM_EE_GetFastMode \n
  *  EECR2     EE11FAST        LL_HRTIM_EE_GetFastMode \n
  *  EECR2     EE12FAST        LL_HRTIM_EE_GetFastMode \n
  *  EECR2     EE13FAST        LL_HRTIM_EE_GetFastMode
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV1
  *         @arg @ref LL_HRTIM_EEV2
  *         @arg @ref LL_HRTIM_EEV3
  *         @arg @ref LL_HRTIM_EEV4
  *         @arg @ref LL_HRTIM_EEV5
  *         @arg @ref LL_HRTIM_EEV11
  *         @arg @ref LL_HRTIM_EEV12
  *         @arg @ref LL_HRTIM_EEV13
  * @retval fast_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_FASTMODE_DISABLE
  *         @arg @ref LL_HRTIM_EE_FASTMODE_ENABLE
  */
__STATIC_INLINE uint32_t LL_HRTIM_EE_GetFastMode(const HRTIM_TypeDef *hrtimx, uint32_t event)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_EECR[ievent]));
  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_EECR1_EE1FAST) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]) >>
          LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]);
}

/**
  * @brief  Set the digital noise filter of a external event.
  * @rmtoll
  *  EECR3     EE6F         LL_HRTIM_EE_SetFilter \n
  *  EECR3     EE7F         LL_HRTIM_EE_SetFilter \n
  *  EECR3     EE8F         LL_HRTIM_EE_SetFilter \n
  *  EECR3     EE9F         LL_HRTIM_EE_SetFilter \n
  *  EECR3     EE10F        LL_HRTIM_EE_SetFilter \n
  *  EECR6     EE14F        LL_HRTIM_EE_SetFilter \n
  *  EECR6     EE15F        LL_HRTIM_EE_SetFilter \n
  *  EECR6     EE16F        LL_HRTIM_EE_SetFilter
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @param  filter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FDIV1
  *         @arg @ref LL_HRTIM_FDIV1_N2
  *         @arg @ref LL_HRTIM_FDIV1_N4
  *         @arg @ref LL_HRTIM_FDIV1_N8
  *         @arg @ref LL_HRTIM_FDIV2_N6
  *         @arg @ref LL_HRTIM_FDIV2_N8
  *         @arg @ref LL_HRTIM_FDIV4_N6
  *         @arg @ref LL_HRTIM_FDIV4_N8
  *         @arg @ref LL_HRTIM_FDIV8_N6
  *         @arg @ref LL_HRTIM_FDIV8_N8
  *         @arg @ref LL_HRTIM_FDIV16_N5
  *         @arg @ref LL_HRTIM_FDIV16_N6
  *         @arg @ref LL_HRTIM_FDIV16_N8
  *         @arg @ref LL_HRTIM_FDIV32_N5
  *         @arg @ref LL_HRTIM_FDIV32_N6
  *         @arg @ref LL_HRTIM_FDIV32_N8
  */
__STATIC_INLINE void LL_HRTIM_EE_SetFilter(const HRTIM_TypeDef *hrtimx, uint32_t event, uint32_t filter)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __IOM uint32_t *preg = (event < LL_HRTIM_EEV14) ? \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR3))) : \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR6)));

  STM32_MODIFY_REG(*preg, (HRTIM_EECR3_EE6F << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]),
                   (filter << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]));
}

/**
  * @brief  Get actual digital noise filter setting of a external event.
  * @rmtoll
  *  EECR3     EE6F         LL_HRTIM_EE_GetFilter \n
  *  EECR3     EE7F         LL_HRTIM_EE_GetFilter \n
  *  EECR3     EE8F         LL_HRTIM_EE_GetFilter \n
  *  EECR3     EE9F         LL_HRTIM_EE_GetFilter \n
  *  EECR3     EE10F        LL_HRTIM_EE_GetFilter \n
  *  EECR6     EE14F        LL_HRTIM_EE_GetFilter \n
  *  EECR6     EE15F        LL_HRTIM_EE_GetFilter \n
  *  EECR6     EE16F        LL_HRTIM_EE_GetFilter
  * @param  hrtimx High Resolution Timer instance
  * @param  event This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EEV6
  *         @arg @ref LL_HRTIM_EEV7
  *         @arg @ref LL_HRTIM_EEV8
  *         @arg @ref LL_HRTIM_EEV9
  *         @arg @ref LL_HRTIM_EEV10
  *         @arg @ref LL_HRTIM_EEV14
  *         @arg @ref LL_HRTIM_EEV15
  *         @arg @ref LL_HRTIM_EEV16
  * @retval filter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FDIV1
  *         @arg @ref LL_HRTIM_FDIV1_N2
  *         @arg @ref LL_HRTIM_FDIV1_N4
  *         @arg @ref LL_HRTIM_FDIV1_N8
  *         @arg @ref LL_HRTIM_FDIV2_N6
  *         @arg @ref LL_HRTIM_FDIV2_N8
  *         @arg @ref LL_HRTIM_FDIV4_N6
  *         @arg @ref LL_HRTIM_FDIV4_N8
  *         @arg @ref LL_HRTIM_FDIV8_N6
  *         @arg @ref LL_HRTIM_FDIV8_N8
  *         @arg @ref LL_HRTIM_FDIV16_N5
  *         @arg @ref LL_HRTIM_FDIV16_N6
  *         @arg @ref LL_HRTIM_FDIV16_N8
  *         @arg @ref LL_HRTIM_FDIV32_N5
  *         @arg @ref LL_HRTIM_FDIV32_N6
  *         @arg @ref LL_HRTIM_FDIV32_N8
  */
__STATIC_INLINE uint32_t LL_HRTIM_EE_GetFilter(const HRTIM_TypeDef *hrtimx, uint32_t event)
{
  uint32_t ievent = (uint8_t)(STM32_POSITION_VAL(event) - STM32_POSITION_VAL(LL_HRTIM_EEV1));
  __I uint32_t *preg = (event < LL_HRTIM_EEV14) ? \
                       (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR3))) : \
                       (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.EECR6)));

  return (STM32_READ_BIT(*preg,
                         (uint32_t)(HRTIM_EECR3_EE6F) << LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]) >>
          LL_HRTIM_REG_SHIFT_TAB_EExSRC[ievent]);
}

/**
  * @brief  Set the external event prescaler.
  * @rmtoll
  *  EECR3     EEVSD        LL_HRTIM_EE_SetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV8
  */
__STATIC_INLINE void LL_HRTIM_EE_SetPrescaler(HRTIM_TypeDef *hrtimx, uint32_t prescaler)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.EECR3, HRTIM_EECR3_EEVSD, prescaler);
}

/**
  * @brief  Get actual external event prescaler setting.
  * @rmtoll
  *  EECR3     EEVSD        LL_HRTIM_EE_GetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @retval prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_EE_PRESCALER_DIV8
  */
__STATIC_INLINE uint32_t LL_HRTIM_EE_GetPrescaler(const HRTIM_TypeDef *hrtimx)
{
  return (STM32_READ_BIT(hrtimx->sCommonRegs.EECR3, HRTIM_EECR3_EEVSD));
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_Fault_management Fault_management
  * @{
  */
/**
  * @brief  Configure fault signal conditioning polarity and source.
  * @rmtoll
  *  FLTINR1     FLT1P        LL_HRTIM_FLT_Config \n
  *  FLTINR1     FLT1SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT1SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR1     FLT2P        LL_HRTIM_FLT_Config \n
  *  FLTINR1     FLT2SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT2SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR1     FLT3P        LL_HRTIM_FLT_Config \n
  *  FLTINR1     FLT3SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT3SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR1     FLT4P        LL_HRTIM_FLT_Config \n
  *  FLTINR1     FLT4SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT4SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT5P        LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT5SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT6P        LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT6SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR5     FLT7P        LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT7SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR5     FLT7SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR5     FLT8P        LL_HRTIM_FLT_Config \n
  *  FLTINR2     FLT8SRC      LL_HRTIM_FLT_Config \n
  *  FLTINR5     FLT8SRC      LL_HRTIM_FLT_Config
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @param  configuration This parameter must be a combination of all the following values:
  *         Source (FltxSrc1..FltxSrc4)
  *         For fault input 1:
  *         @arg @ref LL_HRTIM_FLT1SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT1SRC_COMP2
  *         @arg @ref LL_HRTIM_FLT1SRC_EEV1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT1SRC_PLAY1_OUT0 (*)
  * @endif
  *         For fault input 2:
  *         @arg @ref LL_HRTIM_FLT2SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT2SRC_COMP4
  *         @arg @ref LL_HRTIM_FLT2SRC_EEV2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT2SRC_PLAY1_OUT1 (*)
  * @endif
  *         For fault input 3:
  *         @arg @ref LL_HRTIM_FLT3SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT3SRC_COMP6
  *         @arg @ref LL_HRTIM_FLT3SRC_EEV3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT3SRC_PLAY1_OUT2 (*)
  * @endif
  *         For fault input 4:
  *         @arg @ref LL_HRTIM_FLT4SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT4SRC_COMP1
  *         @arg @ref LL_HRTIM_FLT4SRC_EEV4
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT4SRC_PLAY1_OUT3 (*)
  * @endif
  *         For fault input 5:
  *         @arg @ref LL_HRTIM_FLT5SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT5SRC_COMP3
  *         @arg @ref LL_HRTIM_FLT5SRC_EEV5
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT5SRC_PLAY1_OUT4 (*)
  * @endif
  *         For fault input 6:
  *         @arg @ref LL_HRTIM_FLT6SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT6SRC_COMP5
  *         @arg @ref LL_HRTIM_FLT6SRC_EEV6
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT6SRC_PLAY1_OUT5 (*)
  * @endif
  *         For fault input 7:
  *         @arg @ref LL_HRTIM_FLT7SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT7SRC_COMP7
  *         @arg @ref LL_HRTIM_FLT7SRC_EEV7
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT7SRC_PLAY1_OUT6 (*)
  * @endif
  *         For fault input 8:
  *         @arg @ref LL_HRTIM_FLT8SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT8SRC_COMP8
  *         @arg @ref LL_HRTIM_FLT8SRC_EEV8
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT8SRC_PLAY1_OUT7 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  *
  *         Polarity
  *         @arg @ref LL_HRTIM_FLT_POLARITY_LOW
  *         @arg @ref LL_HRTIM_FLT_POLARITY_HIGH
  *
  * @note This function must not be called when the fault channel is enabled.
  */
__STATIC_INLINE void LL_HRTIM_FLT_Config(const HRTIM_TypeDef *hrtimx, uint32_t fault, uint32_t configuration)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg1 = (fault < LL_HRTIM_FLT7) ? \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1))) : \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR5)));
  __IOM uint32_t *preg2 = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR2)));

  uint64_t cfg;
  uint64_t mask;

  /* FLTxSRC[0] and FLTxP programming */
  /* FLTxSRC[1] programming */
  cfg = ((uint64_t)((uint64_t)configuration & (uint64_t)LL_HRTIM_FLT_CONFIG_MASK) << LL_REG_SHIFT_TAB_FLTxF[ifault]) |
        (((uint64_t)((uint64_t)configuration & (uint64_t)LL_HRTIM_FLT_SRC_1_MASK) << ifault) << 32U);

  /* FLTxSRC[0] and FLTxP programming */
  /* FLTxSRC[1] programming */
  mask = ((uint64_t)(HRTIM_FLTINR1_FLT1P | HRTIM_FLTINR1_FLT1SRC) << LL_REG_SHIFT_TAB_FLTxF[ifault]) |
         ((uint64_t)(LL_HRTIM_FLT_SRC_1_MASK) << 32U);

  STM32_MODIFY_REG(*preg1, (uint32_t)(mask), (uint32_t)(cfg));
  STM32_MODIFY_REG(*preg2, (uint32_t)(mask >> 32U), (uint32_t)(cfg  >> 32U));
}

/**
  * @brief  Set the source of a fault signal.
  * @rmtoll
  *  FLTINR1     FLT1SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT1SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR1     FLT2SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT2SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR1     FLT3SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT3SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR1     FLT4SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT4SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT5SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT6SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT7SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR5     FLT7SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR2     FLT8SRC      LL_HRTIM_FLT_SetSrc \n
  *  FLTINR5     FLT8SRC      LL_HRTIM_FLT_SetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @param  src This parameter can be a one of the following values:
  *         For fault input 1:
  *         @arg @ref LL_HRTIM_FLT1SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT1SRC_COMP2
  *         @arg @ref LL_HRTIM_FLT1SRC_EEV1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT1SRC_PLAY1_OUT0 (*)
  * @endif
  *         For fault input 2:
  *         @arg @ref LL_HRTIM_FLT2SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT2SRC_COMP4
  *         @arg @ref LL_HRTIM_FLT2SRC_EEV2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT2SRC_PLAY1_OUT1 (*)
  * @endif
  *         For fault input 3:
  *         @arg @ref LL_HRTIM_FLT3SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT3SRC_COMP6
  *         @arg @ref LL_HRTIM_FLT3SRC_EEV3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT3SRC_PLAY1_OUT2 (*)
  * @endif
  *         For fault input 4:
  *         @arg @ref LL_HRTIM_FLT4SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT4SRC_COMP1
  *         @arg @ref LL_HRTIM_FLT4SRC_EEV4
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT4SRC_PLAY1_OUT3 (*)
  * @endif
  *         For fault input 5:
  *         @arg @ref LL_HRTIM_FLT5SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT5SRC_COMP3
  *         @arg @ref LL_HRTIM_FLT5SRC_EEV5
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT5SRC_PLAY1_OUT4 (*)
  * @endif
  *         For fault input 6:
  *         @arg @ref LL_HRTIM_FLT6SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT6SRC_COMP5
  *         @arg @ref LL_HRTIM_FLT6SRC_EEV6
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT6SRC_PLAY1_OUT5 (*)
  * @endif
  *         For fault input 7:
  *         @arg @ref LL_HRTIM_FLT7SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT7SRC_COMP7
  *         @arg @ref LL_HRTIM_FLT7SRC_EEV7
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT7SRC_PLAY1_OUT6 (*)
  * @endif
  *         For fault input 8:
  *         @arg @ref LL_HRTIM_FLT8SRC_GPIO
  *         @arg @ref LL_HRTIM_FLT8SRC_COMP8
  *         @arg @ref LL_HRTIM_FLT8SRC_EEV8
  * @if PLAY1
  *         @arg @ref LL_HRTIM_FLT8SRC_PLAY1_OUT7 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  * @note This function must not be called when the fault channel is enabled.
  */
__STATIC_INLINE void LL_HRTIM_FLT_SetSrc(const HRTIM_TypeDef *hrtimx, uint32_t fault, uint32_t src)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg1 = (fault < LL_HRTIM_FLT7) ? \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1))) : \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR5)));
  __IOM uint32_t *preg2 = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR2)));

  /* FLTxSRC[0] programming */
  /* FLTxSRC[1] programming */
  uint64_t cfg = ((uint64_t)((uint64_t)src & (uint64_t)HRTIM_FLTINR1_FLT1SRC) << LL_REG_SHIFT_TAB_FLTxF[ifault]) |
                 (((uint64_t)((uint64_t)src & (uint64_t)LL_HRTIM_FLT_SRC_1_MASK) << ifault) << 32U);

  /* FLTxSRC[0] programming */
  /* FLTxSRC[1] programming */
  uint64_t mask = ((uint64_t)(HRTIM_FLTINR1_FLT1SRC) << LL_REG_SHIFT_TAB_FLTxF[ifault]) |
                  (((uint64_t)(HRTIM_FLTINR2_FLT1SRC) << ifault) << 32U);

  STM32_MODIFY_REG(*preg1, (uint32_t)(mask), (uint32_t)(cfg));
  STM32_MODIFY_REG(*preg2, (uint32_t)(mask >> 32U), (uint32_t)(cfg  >> 32U));
}

/**
  * @brief  Get actual source of a fault signal.
  * @rmtoll
  *  FLTINR1     FLT1SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT1SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR1     FLT2SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT2SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR1     FLT3SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT3SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR1     FLT4SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT4SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT5SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT6SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR5     FLT7SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT7SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR2     FLT8SRC      LL_HRTIM_FLT_GetSrc \n
  *  FLTINR5     FLT8SRC      LL_HRTIM_FLT_GetSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval src This parameter can be one of the following values:
  *         For external event 1:
  *         @arg @ref LL_HRTIM_EEV1SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV1SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV1SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV1SRC_PLAY1_OUT0 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV1SRC_TIM1_BKIN2
  *         For external event 2:
  *         @arg @ref LL_HRTIM_EEV2SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV2SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM2_TRGO
  *         @arg @ref LL_HRTIM_EEV2SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV2SRC_PLAY1_OUT1 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV2SRC_TIM8_BKIN2
  *         For external event 3:
  *         @arg @ref LL_HRTIM_EEV3SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV3SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM3_TRGO
  *         @arg @ref LL_HRTIM_EEV3SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV3SRC_PLAY1_OUT2 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV3SRC_TIM20_BKIN2 (*)
  * @endif
  *         For external event 4:
  *         @arg @ref LL_HRTIM_EEV4SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV4SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV4SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV4SRC_PLAY1_OUT3 (*)
  * @endif
  *         For external event 5:
  *         @arg @ref LL_HRTIM_EEV5SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP3
  *         @arg @ref LL_HRTIM_EEV5SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV5SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV5SRC_PLAY1_OUT4 (*)
  * @endif
  *         For external event 6:
  *         @arg @ref LL_HRTIM_EEV6SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP2
  *         @arg @ref LL_HRTIM_EEV6SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV6SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV6SRC_PLAY1_OUT5 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV6SRC_TIM1_BKIN1
  *         For external event 7:
  *         @arg @ref LL_HRTIM_EEV7SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP4
  *         @arg @ref LL_HRTIM_EEV7SRC_COMP7
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV7SRC_ADC3_AWD1 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV7SRC_PLAY1_OUT6 (*)
  * @endif
  *         @arg @ref LL_HRTIM_EEV7SRC_TIM8_BKIN1
  *         For external event 8:
  *         @arg @ref LL_HRTIM_EEV8SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP6
  *         @arg @ref LL_HRTIM_EEV8SRC_COMP3
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV8SRC_ADC3_AWD2 (*)
  * @endif
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV8SRC_PLAY1_OUT7 (*)
  * @endif
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV8SRC_TIM20_BKIN1 (*)
  * @endif
  *         For external event 9:
  *         @arg @ref LL_HRTIM_EEV9SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV9SRC_COMP4
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV9SRC_PLAY1_OUT8 (*)
  * @endif
  *         For external event 10:
  *         @arg @ref LL_HRTIM_EEV10SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV10SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV10SRC_TIM6_TRGO
  * @if ADC3
  *         @arg @ref LL_HRTIM_EEV10SRC_ADC3_AWD3 (*)
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV10SRC_PLAY1_OUT9 (*)
  * @endif
  * @endif
  *         For external event 11:
  *         @arg @ref LL_HRTIM_EEV11SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV11SRC_COMP7
  *         @arg @ref LL_HRTIM_EEV11SRC_TIM9_TRGO
  *         @arg @ref LL_HRTIM_EEV11SRC_ADC2_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV11SRC_PLAY1_OUT10 (*)
  * @endif
  *         For external event 12:
  *         @arg @ref LL_HRTIM_EEV12SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV12SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV12SRC_TIM12_TRGO
  *         @arg @ref LL_HRTIM_EEV12SRC_ADC2_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV12SRC_PLAY1_OUT11 (*)
  * @endif
  *         For external event 13:
  *         @arg @ref LL_HRTIM_EEV13SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV13SRC_COMP5
  *         @arg @ref LL_HRTIM_EEV13SRC_TIM15_TRGO
  *         @arg @ref LL_HRTIM_EEV13SRC_ADC2_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV13SRC_PLAY1_OUT12 (*)
  * @endif
  *         For external event 14:
  *         @arg @ref LL_HRTIM_EEV14SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV14SRC_COMP8
  *         @arg @ref LL_HRTIM_EEV14SRC_TIM1_TRGO
  *         @arg @ref LL_HRTIM_EEV14SRC_ADC1_AWD1
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV14SRC_PLAY1_OUT13 (*)
  * @endif
  *         For external event 15:
  *         @arg @ref LL_HRTIM_EEV15SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV15SRC_COMP1
  *         @arg @ref LL_HRTIM_EEV15SRC_TIM8_TRGO
  *         @arg @ref LL_HRTIM_EEV15SRC_ADC1_AWD2
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV15SRC_PLAY1_OUT14 (*)
  * @endif
  *         For external event 16:
  *         @arg @ref LL_HRTIM_EEV16SRC_GPIO
  *         @arg @ref LL_HRTIM_EEV16SRC_COMP3
  * @if TIM20
  *         @arg @ref LL_HRTIM_EEV16SRC_TIM20_TRGO
  * @endif
  *         @arg @ref LL_HRTIM_EEV16SRC_ADC1_AWD3
  * @if PLAY1
  *         @arg @ref LL_HRTIM_EEV16SRC_PLAY1_OUT15 (*)
  * @endif
  *         (*)  Value not defined in all devices. \n
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_GetSrc(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  uint32_t mask1 = (fault < LL_HRTIM_FLT7) ? \
                   (uint32_t)(HRTIM_FLTINR1_FLT1SRC
                              | HRTIM_FLTINR1_FLT2SRC
                              | HRTIM_FLTINR1_FLT3SRC
                              | HRTIM_FLTINR1_FLT4SRC) : \
                   (uint32_t)(HRTIM_FLTINR5_FLT7SRC | HRTIM_FLTINR5_FLT8SRC);
  __I uint32_t *preg1 = (fault < LL_HRTIM_FLT7) ? \
                        (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1))) : \
                        (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR5)));
  __I uint32_t *preg2 = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR2)));

  uint64_t Src0;
  uint32_t Src1;
  uint32_t temp1; /* MISRA C:2012 compliance */
  uint32_t temp2; /* MISRA C:2012 compliance */

  /* Get actual FLTxSRC[0] programming */
  temp1 = STM32_READ_BIT(*preg2, (uint32_t)(HRTIM_FLTINR2_FLT5SRC | HRTIM_FLTINR2_FLT6SRC));
  temp2 = STM32_READ_BIT(*preg1, mask1);

  Src0 = (uint64_t)temp1 << 32U;
  Src0 |= (uint64_t)temp2;
  Src0 = (Src0 >> LL_REG_SHIFT_TAB_FLTxF[ifault]) ;

  /* Get actual FLTxSRC[1] programming */
  Src1 = STM32_READ_BIT(*preg2, LL_HRTIM_FLT_SRC_1_MASK) >> ifault;

  return ((uint32_t)(Src1 | Src0));
}

/**
  * @brief  Set the polarity of a fault signal.
  * @rmtoll
  *  FLTINR1     FLT1P        LL_HRTIM_FLT_SetPolarity \n
  *  FLTINR1     FLT2P        LL_HRTIM_FLT_SetPolarity \n
  *  FLTINR1     FLT3P        LL_HRTIM_FLT_SetPolarity \n
  *  FLTINR1     FLT4P        LL_HRTIM_FLT_SetPolarity \n
  *  FLTINR2     FLT5P        LL_HRTIM_FLT_SetPolarity \n
  *  FLTINR2     FLT6P        LL_HRTIM_FLT_SetPolarity \n
  *  FLTINR5     FLT7P        LL_HRTIM_FLT_SetPolarity \n
  *  FLTINR5     FLT8P        LL_HRTIM_FLT_SetPolarity
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_POLARITY_LOW
  *         @arg @ref LL_HRTIM_FLT_POLARITY_HIGH
  * @note This function must not be called when the fault channel is enabled.
  */
__STATIC_INLINE void LL_HRTIM_FLT_SetPolarity(const HRTIM_TypeDef *hrtimx, uint32_t fault, uint32_t polarity)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg1 = (fault < LL_HRTIM_FLT7) ? \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1))) : \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR5)));
  __IOM uint32_t *preg2 = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR2)));

  uint64_t cfg = (uint64_t)((uint64_t)polarity & (uint64_t)(HRTIM_FLTINR1_FLT1P)) << LL_REG_SHIFT_TAB_FLTxF[ifault];
  uint64_t mask = (uint64_t)(HRTIM_FLTINR1_FLT1P) << LL_REG_SHIFT_TAB_FLTxF[ifault];

  /* for polarity bit */
  STM32_MODIFY_REG(*preg1, (uint32_t)(mask), (uint32_t)(cfg));
  STM32_MODIFY_REG(*preg2, (uint32_t)(mask >> 32U), (uint32_t)(cfg  >> 32U));
}

/**
  * @brief  Get actual polarity of a fault signal.
  * @rmtoll
  *  FLTINR1     FLT1P        LL_HRTIM_FLT_GetPolarity \n
  *  FLTINR1     FLT2P        LL_HRTIM_FLT_GetPolarity \n
  *  FLTINR1     FLT3P        LL_HRTIM_FLT_GetPolarity \n
  *  FLTINR1     FLT4P        LL_HRTIM_FLT_GetPolarity \n
  *  FLTINR2     FLT5P        LL_HRTIM_FLT_GetPolarity \n
  *  FLTINR2     FLT6P        LL_HRTIM_FLT_GetPolarity \n
  *  FLTINR5     FLT7P        LL_HRTIM_FLT_GetPolarity \n
  *  FLTINR5     FLT8P        LL_HRTIM_FLT_GetPolarity
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval polarity This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_POLARITY_LOW
  *         @arg @ref LL_HRTIM_FLT_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_GetPolarity(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __I uint32_t *preg1 = (fault < LL_HRTIM_FLT7) ? \
                        (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1))) : \
                        (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR5)));
  __I uint32_t *preg2 = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR2)));
  uint32_t temp1;  /* MISRA C:2012 compliance */
  uint32_t temp2;  /* MISRA C:2012 compliance */
  uint64_t polarity;

  temp1 = STM32_READ_BIT(*preg2, (uint32_t)(HRTIM_FLTINR2_FLT5P | HRTIM_FLTINR2_FLT6P));
  temp2 = STM32_READ_BIT(*preg1, (uint32_t)(HRTIM_FLTINR1_FLT1P | HRTIM_FLTINR1_FLT2P
                                            | HRTIM_FLTINR1_FLT3P | HRTIM_FLTINR1_FLT4P));

  polarity = (uint64_t)temp1 << 32 ;
  polarity |= (uint64_t)temp2;
  polarity = (polarity >> LL_REG_SHIFT_TAB_FLTxF[ifault]) ;

  return (uint32_t)(polarity);
}

/**
  * @brief  Set the digital noise filter of a fault signal.
  * @rmtoll
  *  FLTINR1     FLT1F      LL_HRTIM_FLT_SetFilter \n
  *  FLTINR1     FLT2F      LL_HRTIM_FLT_SetFilter \n
  *  FLTINR1     FLT3F      LL_HRTIM_FLT_SetFilter \n
  *  FLTINR1     FLT4F      LL_HRTIM_FLT_SetFilter \n
  *  FLTINR2     FLT5F      LL_HRTIM_FLT_SetFilter \n
  *  FLTINR2     FLT6F      LL_HRTIM_FLT_SetFilter \n
  *  FLTINR5     FLT7F      LL_HRTIM_FLT_SetFilter \n
  *  FLTINR5     FLT8F      LL_HRTIM_FLT_SetFilter
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @param  filter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FDIV1
  *         @arg @ref LL_HRTIM_FDIV1_N2
  *         @arg @ref LL_HRTIM_FDIV1_N4
  *         @arg @ref LL_HRTIM_FDIV1_N8
  *         @arg @ref LL_HRTIM_FDIV2_N6
  *         @arg @ref LL_HRTIM_FDIV2_N8
  *         @arg @ref LL_HRTIM_FDIV4_N6
  *         @arg @ref LL_HRTIM_FDIV4_N8
  *         @arg @ref LL_HRTIM_FDIV8_N6
  *         @arg @ref LL_HRTIM_FDIV8_N8
  *         @arg @ref LL_HRTIM_FDIV16_N5
  *         @arg @ref LL_HRTIM_FDIV16_N6
  *         @arg @ref LL_HRTIM_FDIV16_N8
  *         @arg @ref LL_HRTIM_FDIV32_N5
  *         @arg @ref LL_HRTIM_FDIV32_N6
  *         @arg @ref LL_HRTIM_FDIV32_N8
  * @note This function must not be called when the fault channel is enabled.
  */
__STATIC_INLINE void LL_HRTIM_FLT_SetFilter(const HRTIM_TypeDef *hrtimx, uint32_t fault, uint32_t filter)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg1 = (fault < LL_HRTIM_FLT7) ? \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1))) : \
                          (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR5)));
  __IOM uint32_t *preg2 = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR2)));

  uint32_t fltxf = filter << HRTIM_FLTINR1_FLT1F_Pos;
  uint64_t cfg = (uint64_t)((uint64_t)fltxf & (uint64_t)HRTIM_FLTINR1_FLT1F)
                 <<  LL_REG_SHIFT_TAB_FLTxF[ifault];
  uint64_t mask = (uint64_t)(HRTIM_FLTINR1_FLT1F) << LL_REG_SHIFT_TAB_FLTxF[ifault];

  STM32_MODIFY_REG(*preg1, (uint32_t)(mask), (uint32_t)(cfg));
  STM32_MODIFY_REG(*preg2, (uint32_t)(mask >> 32U), (uint32_t)(cfg  >> 32U));
}

/**
  * @brief  Get actual digital noise filter setting of a fault signal.
  * @rmtoll
  *  FLTINR1     FLT1F      LL_HRTIM_FLT_GetFilter \n
  *  FLTINR1     FLT2F      LL_HRTIM_FLT_GetFilter \n
  *  FLTINR1     FLT3F      LL_HRTIM_FLT_GetFilter \n
  *  FLTINR1     FLT4F      LL_HRTIM_FLT_GetFilter \n
  *  FLTINR2     FLT5F      LL_HRTIM_FLT_GetFilter \n
  *  FLTINR2     FLT6F      LL_HRTIM_FLT_GetFilter \n
  *  FLTINR5     FLT7F      LL_HRTIM_FLT_GetFilter \n
  *  FLTINR5     FLT8F      LL_HRTIM_FLT_GetFilter
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval filter This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FDIV1
  *         @arg @ref LL_HRTIM_FDIV1_N2
  *         @arg @ref LL_HRTIM_FDIV1_N4
  *         @arg @ref LL_HRTIM_FDIV1_N8
  *         @arg @ref LL_HRTIM_FDIV2_N6
  *         @arg @ref LL_HRTIM_FDIV2_N8
  *         @arg @ref LL_HRTIM_FDIV4_N6
  *         @arg @ref LL_HRTIM_FDIV4_N8
  *         @arg @ref LL_HRTIM_FDIV8_N6
  *         @arg @ref LL_HRTIM_FDIV8_N8
  *         @arg @ref LL_HRTIM_FDIV16_N5
  *         @arg @ref LL_HRTIM_FDIV16_N6
  *         @arg @ref LL_HRTIM_FDIV16_N8
  *         @arg @ref LL_HRTIM_FDIV32_N5
  *         @arg @ref LL_HRTIM_FDIV32_N6
  *         @arg @ref LL_HRTIM_FDIV32_N8
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_GetFilter(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __I uint32_t *preg1 = (fault < LL_HRTIM_FLT7) ? \
                        (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1))) : \
                        (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR5)));
  __I uint32_t *preg2 = (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR2)));
  uint32_t temp1;  /* MISRA C:2012 compliance */
  uint32_t temp2;  /* MISRA C:2012 compliance */
  uint64_t filter;
  temp1 = STM32_READ_BIT(*preg2, (uint32_t)(HRTIM_FLTINR2_FLT5F | HRTIM_FLTINR2_FLT6F));
  temp2 = STM32_READ_BIT(*preg1, (uint32_t)(HRTIM_FLTINR1_FLT1F | HRTIM_FLTINR1_FLT2F
                                            | HRTIM_FLTINR1_FLT3F | HRTIM_FLTINR1_FLT4F));

  filter = (uint64_t)temp1 << 32U;
  filter |= (uint64_t)temp2;
  filter = (filter >> (LL_REG_SHIFT_TAB_FLTxF[ifault] + HRTIM_FLTINR1_FLT1F_Pos));

  return (uint32_t)(filter);
}

/**
  * @brief  Set the fault circuitry prescaler.
  * @rmtoll
  *  FLTINR2     FLTSD      LL_HRTIM_FLT_SetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV8
  */
__STATIC_INLINE void LL_HRTIM_FLT_SetPrescaler(HRTIM_TypeDef *hrtimx, uint32_t prescaler)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.FLTINR2, HRTIM_FLTINR2_FLTSD, prescaler);
}

/**
  * @brief  Get actual fault circuitry prescaler setting.
  * @rmtoll
  *  FLTINR2     FLTSD      LL_HRTIM_FLT_GetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @retval prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_FLT_PRESCALER_DIV8
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_GetPrescaler(const HRTIM_TypeDef *hrtimx)
{
  return (STM32_READ_BIT(hrtimx->sCommonRegs.FLTINR2, HRTIM_FLTINR2_FLTSD));
}

/**
  * @brief  Lock the fault signal conditioning settings.
  * @rmtoll
  *  FLTINR1     FLT1LCK      LL_HRTIM_FLT_Lock \n
  *  FLTINR1     FLT2LCK      LL_HRTIM_FLT_Lock \n
  *  FLTINR1     FLT3LCK      LL_HRTIM_FLT_Lock \n
  *  FLTINR1     FLT4LCK      LL_HRTIM_FLT_Lock \n
  *  FLTINR2     FLT5LCK      LL_HRTIM_FLT_Lock \n
  *  FLTINR2     FLT6LCK      LL_HRTIM_FLT_Lock \n
  *  FLTINR5     FLT7LCK      LL_HRTIM_FLT_Lock \n
  *  FLTINR5     FLT8LCK      LL_HRTIM_FLT_Lock
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  */
__STATIC_INLINE void LL_HRTIM_FLT_Lock(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_FLTINR[ifault]));
  STM32_SET_BIT(*preg, (HRTIM_FLTINR1_FLT1LCK << LL_REG_SHIFT_TAB_FLTxE[ifault]));
}

/**
  * @brief  Enable the fault circuitry for the designated fault input.
  * @rmtoll
  *  FLTINR1     FLT1E      LL_HRTIM_FLT_Enable \n
  *  FLTINR1     FLT2E      LL_HRTIM_FLT_Enable \n
  *  FLTINR1     FLT3E      LL_HRTIM_FLT_Enable \n
  *  FLTINR1     FLT4E      LL_HRTIM_FLT_Enable \n
  *  FLTINR2     FLT5E      LL_HRTIM_FLT_Enable \n
  *  FLTINR2     FLT6E      LL_HRTIM_FLT_Enable \n
  *  FLTINR5     FLT7E      LL_HRTIM_FLT_Enable \n
  *  FLTINR5     FLT8E      LL_HRTIM_FLT_Enable
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  */
__STATIC_INLINE void LL_HRTIM_FLT_Enable(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_FLTINR[ifault]));
  STM32_SET_BIT(*preg, (HRTIM_FLTINR1_FLT1E << LL_REG_SHIFT_TAB_FLTxE[ifault]));
}

/**
  * @brief  Disable the fault circuitry for for the designated fault input.
  * @rmtoll
  *  FLTINR1     FLT1E      LL_HRTIM_FLT_Disable \n
  *  FLTINR1     FLT2E      LL_HRTIM_FLT_Disable \n
  *  FLTINR1     FLT3E      LL_HRTIM_FLT_Disable \n
  *  FLTINR1     FLT4E      LL_HRTIM_FLT_Disable \n
  *  FLTINR2     FLT5E      LL_HRTIM_FLT_Disable \n
  *  FLTINR2     FLT6E      LL_HRTIM_FLT_Disable \n
  *  FLTINR5     FLT7E      LL_HRTIM_FLT_Disable \n
  *  FLTINR5     FLT8E      LL_HRTIM_FLT_Disable
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  */
__STATIC_INLINE void LL_HRTIM_FLT_Disable(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1) +
                                                       LL_HRTIM_REG_OFFSET_TAB_FLTINR[ifault]));
  STM32_CLEAR_BIT(*preg, (HRTIM_FLTINR1_FLT1E << LL_REG_SHIFT_TAB_FLTxE[ifault]));
}

/**
  * @brief  Indicate whether the fault circuitry is enabled for a given fault input.
  * @rmtoll
  *  FLTINR1     FLT1E      LL_HRTIM_FLT_IsEnabled \n
  *  FLTINR1     FLT2E      LL_HRTIM_FLT_IsEnabled \n
  *  FLTINR1     FLT3E      LL_HRTIM_FLT_IsEnabled \n
  *  FLTINR1     FLT4E      LL_HRTIM_FLT_IsEnabled \n
  *  FLTINR2     FLT5E      LL_HRTIM_FLT_IsEnabled \n
  *  FLTINR2     FLT6E      LL_HRTIM_FLT_IsEnabled \n
  *  FLTINR5     FLT7E      LL_HRTIM_FLT_IsEnabled \n
  *  FLTINR5     FLT8E      LL_HRTIM_FLT_IsEnabled
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval State of FLTxEN bit in HRTIM_FLTINRx register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_IsEnabled(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR1) +
                                                             LL_HRTIM_REG_OFFSET_TAB_FLTINR[ifault]));
  return (((STM32_READ_BIT(*preg,
                           (HRTIM_FLTINR1_FLT1E << LL_REG_SHIFT_TAB_FLTxE[ifault]))
            >> LL_REG_SHIFT_TAB_FLTxE[ifault])
           == (HRTIM_FLTINR1_FLT1E)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Blanking of the fault circuitry for the designated fault input.
  * @rmtoll
  *  FLTINR3     FLT1BLKE      LL_HRTIM_FLT_EnableBlanking \n
  *  FLTINR3     FLT2BLKE      LL_HRTIM_FLT_EnableBlanking \n
  *  FLTINR3     FLT3BLKE      LL_HRTIM_FLT_EnableBlanking \n
  *  FLTINR3     FLT4BLKE      LL_HRTIM_FLT_EnableBlanking \n
  *  FLTINR4     FLT5BLKE      LL_HRTIM_FLT_EnableBlanking \n
  *  FLTINR4     FLT6BLKE      LL_HRTIM_FLT_EnableBlanking \n
  *  FLTINR4     FLT7BLKE      LL_HRTIM_FLT_EnableBlanking \n
  *  FLTINR4     FLT8BLKE      LL_HRTIM_FLT_EnableBlanking
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  */
__STATIC_INLINE void LL_HRTIM_FLT_EnableBlanking(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  STM32_SET_BIT(*preg, (uint32_t)(HRTIM_FLTINR3_FLT1BLKE) << REG_SHIFT_TAB_FLTxBLKE[ifault]);
}

/**
  * @brief  Disable the Blanking of the fault circuitry for the designated fault input.
  * @rmtoll
  *  FLTINR3     FLT1BLKE      LL_HRTIM_FLT_DisableBlanking \n
  *  FLTINR3     FLT2BLKE      LL_HRTIM_FLT_DisableBlanking \n
  *  FLTINR3     FLT3BLKE      LL_HRTIM_FLT_DisableBlanking \n
  *  FLTINR3     FLT4BLKE      LL_HRTIM_FLT_DisableBlanking \n
  *  FLTINR4     FLT5BLKE      LL_HRTIM_FLT_DisableBlanking \n
  *  FLTINR4     FLT6BLKE      LL_HRTIM_FLT_DisableBlanking \n
  *  FLTINR4     FLT7BLKE      LL_HRTIM_FLT_DisableBlanking \n
  *  FLTINR4     FLT8BLKE      LL_HRTIM_FLT_DisableBlanking
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  */
__STATIC_INLINE void LL_HRTIM_FLT_DisableBlanking(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  STM32_CLEAR_BIT(*preg, (HRTIM_FLTINR3_FLT1BLKE << REG_SHIFT_TAB_FLTxBLKE[ifault]));
}

/**
  * @brief  Indicate whether the Blanking of the fault circuitry is enabled for a given fault input.
  * @rmtoll
  *  FLTINR3     FLT1BLKE      LL_HRTIM_FLT_IsEnabledBlanking \n
  *  FLTINR3     FLT2BLKE      LL_HRTIM_FLT_IsEnabledBlanking \n
  *  FLTINR3     FLT3BLKE      LL_HRTIM_FLT_IsEnabledBlanking \n
  *  FLTINR3     FLT4BLKE      LL_HRTIM_FLT_IsEnabledBlanking \n
  *  FLTINR4     FLT5BLKE      LL_HRTIM_FLT_IsEnabledBlanking \n
  *  FLTINR4     FLT6BLKE      LL_HRTIM_FLT_IsEnabledBlanking \n
  *  FLTINR4     FLT7BLKE      LL_HRTIM_FLT_IsEnabledBlanking \n
  *  FLTINR4     FLT8BLKE      LL_HRTIM_FLT_IsEnabledBlanking
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval State of FLTxBLKE bit in HRTIM_FLTINRx register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_IsEnabledBlanking(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __I uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                       (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                       (__I uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));
  uint32_t temp; /* MISRA C:2012 compliance */

  temp = STM32_READ_BIT(*preg, (uint32_t)(HRTIM_FLTINR3_FLT1BLKE) << REG_SHIFT_TAB_FLTxBLKE[ifault]) >>
         REG_SHIFT_TAB_FLTxBLKE[ifault];

  return ((temp == (HRTIM_FLTINR3_FLT1BLKE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Blanking source of the fault circuitry  for a given fault input.
  * @rmtoll
  *  FLTINR3     FLT1BLKS      LL_HRTIM_FLT_SetBlankingSrc \n
  *  FLTINR3     FLT2BLKS      LL_HRTIM_FLT_SetBlankingSrc \n
  *  FLTINR3     FLT3BLKS      LL_HRTIM_FLT_SetBlankingSrc \n
  *  FLTINR3     FLT4BLKS      LL_HRTIM_FLT_SetBlankingSrc \n
  *  FLTINR4     FLT5BLKS      LL_HRTIM_FLT_SetBlankingSrc \n
  *  FLTINR4     FLT6BLKS      LL_HRTIM_FLT_SetBlankingSrc \n
  *  FLTINR4     FLT7BLKS      LL_HRTIM_FLT_SetBlankingSrc \n
  *  FLTINR4     FLT8BLKS      LL_HRTIM_FLT_SetBlankingSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @param  source parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_BLK_RSTALIGNED
  *         @arg @ref LL_HRTIM_FLT_BLK_MOVING
  * @note fault inputs can be temporary disabled to blank spurious fault events.
  * @note This function allows for selection amongst 2 possible blanking sources.
  * @note events triggering blanking window start and blanking window end depend
  *       on both the selected blanking source and the fault input.
  */
__STATIC_INLINE void LL_HRTIM_FLT_SetBlankingSrc(const HRTIM_TypeDef *hrtimx, uint32_t fault, uint32_t source)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  STM32_MODIFY_REG(*preg,
                   (HRTIM_FLTINR3_FLT1BLKS << REG_SHIFT_TAB_FLTxBLKE[ifault]),
                   (source << REG_SHIFT_TAB_FLTxBLKE[ifault]));
}

/**
  * @brief  Get the Blanking source of the fault circuitry is enabled for a given fault input.
  * @rmtoll
  *  FLTINR3     FLT1BLKS      LL_HRTIM_FLT_GetBlankingSrc \n
  *  FLTINR3     FLT2BLKS      LL_HRTIM_FLT_GetBlankingSrc \n
  *  FLTINR3     FLT3BLKS      LL_HRTIM_FLT_GetBlankingSrc \n
  *  FLTINR3     FLT4BLKS      LL_HRTIM_FLT_GetBlankingSrc \n
  *  FLTINR4     FLT5BLKS      LL_HRTIM_FLT_GetBlankingSrc \n
  *  FLTINR4     FLT6BLKS      LL_HRTIM_FLT_GetBlankingSrc \n
  *  FLTINR4     FLT7BLKS      LL_HRTIM_FLT_GetBlankingSrc \n
  *  FLTINR4     FLT8BLKS      LL_HRTIM_FLT_GetBlankingSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval Configured blanking source. Can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_BLK_RSTALIGNED
  *         @arg @ref LL_HRTIM_FLT_BLK_MOVING
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_GetBlankingSrc(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  const __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                               (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                               (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  return ((STM32_READ_BIT(*preg, (uint32_t)(HRTIM_FLTINR3_FLT1BLKS) << REG_SHIFT_TAB_FLTxBLKE[ifault]) >>
           REG_SHIFT_TAB_FLTxBLKE[ifault]));
}

/**
  * @brief  Set the Counter threshold value of a fault counter.
  * @rmtoll
  *  FLTINR3     FLT1CNT      LL_HRTIM_FLT_SetCounterThreshold \n
  *  FLTINR3     FLT2CNT      LL_HRTIM_FLT_SetCounterThreshold \n
  *  FLTINR3     FLT3CNT      LL_HRTIM_FLT_SetCounterThreshold \n
  *  FLTINR3     FLT4CNT      LL_HRTIM_FLT_SetCounterThreshold \n
  *  FLTINR4     FLT5CNT      LL_HRTIM_FLT_SetCounterThreshold \n
  *  FLTINR4     FLT6CNT      LL_HRTIM_FLT_SetCounterThreshold \n
  *  FLTINR4     FLT7CNT      LL_HRTIM_FLT_SetCounterThreshold \n
  *  FLTINR4     FLT8CNT      LL_HRTIM_FLT_SetCounterThreshold
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @param  threshold This parameter can be a number between Min_Data=0 and Max_Data=15
  * @note This function must not be called when the fault channel is enabled.
  */
__STATIC_INLINE void LL_HRTIM_FLT_SetCounterThreshold(const HRTIM_TypeDef *hrtimx, uint32_t fault, uint32_t threshold)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  STM32_MODIFY_REG(*preg,
                   (HRTIM_FLTINR3_FLT1CNT << REG_SHIFT_TAB_FLTxBLKE[ifault]),
                   (threshold << LL_HRTIM_REG_SHIFT_TAB_FLTxCNT[ifault]));
}

/**
  * @brief  Get actual the Counter threshold value of a fault counter.
  * @rmtoll
  *  FLTINR3     FLT1CNT      LL_HRTIM_FLT_GetCounterThreshold \n
  *  FLTINR3     FLT2CNT      LL_HRTIM_FLT_GetCounterThreshold \n
  *  FLTINR3     FLT3CNT      LL_HRTIM_FLT_GetCounterThreshold \n
  *  FLTINR3     FLT4CNT      LL_HRTIM_FLT_GetCounterThreshold \n
  *  FLTINR4     FLT5CNT      LL_HRTIM_FLT_GetCounterThreshold \n
  *  FLTINR4     FLT6CNT      LL_HRTIM_FLT_GetCounterThreshold \n
  *  FLTINR4     FLT7CNT      LL_HRTIM_FLT_GetCounterThreshold \n
  *  FLTINR4     FLT8CNT      LL_HRTIM_FLT_GetCounterThreshold
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval threshold This parameter can be a number between Min_Data=0 and Max_Data=15.
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_GetCounterThreshold(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  const __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                               (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                               (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_FLTINR3_FLT1CNT) << REG_SHIFT_TAB_FLTxBLKE[ifault]) >>
          LL_HRTIM_REG_SHIFT_TAB_FLTxCNT[ifault]);
}

/**
  * @brief  Set the reset mode of a fault counter.
  * @rmtoll
  *  FLTINR3     FLT1RSTM      LL_HRTIM_FLT_SetResetMode \n
  *  FLTINR3     FLT2RSTM      LL_HRTIM_FLT_SetResetMode \n
  *  FLTINR3     FLT3RSTM      LL_HRTIM_FLT_SetResetMode \n
  *  FLTINR3     FLT4RSTM      LL_HRTIM_FLT_SetResetMode \n
  *  FLTINR4     FLT5RSTM      LL_HRTIM_FLT_SetResetMode \n
  *  FLTINR4     FLT6RSTM      LL_HRTIM_FLT_SetResetMode \n
  *  FLTINR4     FLT7RSTM      LL_HRTIM_FLT_SetResetMode \n
  *  FLTINR4     FLT8RSTM      LL_HRTIM_FLT_SetResetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @param  reset_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_COUNTERRST_UNCONDITIONAL
  *         @arg @ref LL_HRTIM_FLT_COUNTERRST_CONDITIONAL
  */
__STATIC_INLINE void LL_HRTIM_FLT_SetResetMode(const HRTIM_TypeDef *hrtimx, uint32_t fault, uint32_t reset_mode)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  STM32_MODIFY_REG(*preg,
                   (HRTIM_FLTINR3_FLT1RSTM << REG_SHIFT_TAB_FLTxBLKE[ifault]),
                   reset_mode << REG_SHIFT_TAB_FLTxBLKE[ifault]);
}

/**
  * @brief  Get the reset mode of a fault counter.
  * @rmtoll
  *  FLTINR3     FLT1RSTM      LL_HRTIM_FLT_GetResetMode \n
  *  FLTINR3     FLT2RSTM      LL_HRTIM_FLT_GetResetMode \n
  *  FLTINR3     FLT3RSTM      LL_HRTIM_FLT_GetResetMode \n
  *  FLTINR3     FLT4RSTM      LL_HRTIM_FLT_GetResetMode \n
  *  FLTINR4     FLT5RSTM      LL_HRTIM_FLT_GetResetMode \n
  *  FLTINR4     FLT6RSTM      LL_HRTIM_FLT_GetResetMode \n
  *  FLTINR4     FLT7RSTM      LL_HRTIM_FLT_GetResetMode \n
  *  FLTINR4     FLT8RSTM      LL_HRTIM_FLT_GetResetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  * @retval  reset_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT_COUNTERRST_UNCONDITIONAL
  *         @arg @ref LL_HRTIM_FLT_COUNTERRST_CONDITIONAL
  */
__STATIC_INLINE uint32_t LL_HRTIM_FLT_GetResetMode(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  const __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                               (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                               (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  return (STM32_READ_BIT(*preg, (uint32_t)(HRTIM_FLTINR3_FLT1RSTM) << REG_SHIFT_TAB_FLTxBLKE[ifault]) >>
          REG_SHIFT_TAB_FLTxBLKE[ifault]);
}

/**
  * @brief  Reset the fault counter for a fault circuitry.
  * @rmtoll
  *  FLTINR3     FLT1CRES      LL_HRTIM_FLT_ResetCounter \n
  *  FLTINR3     FLT2CRES      LL_HRTIM_FLT_ResetCounter \n
  *  FLTINR3     FLT3CRES      LL_HRTIM_FLT_ResetCounter \n
  *  FLTINR3     FLT4CRES      LL_HRTIM_FLT_ResetCounter \n
  *  FLTINR4     FLT5CRES      LL_HRTIM_FLT_ResetCounter \n
  *  FLTINR4     FLT6CRES      LL_HRTIM_FLT_ResetCounter \n
  *  FLTINR4     FLT7CRES      LL_HRTIM_FLT_ResetCounter \n
  *  FLTINR4     FLT8CRES      LL_HRTIM_FLT_ResetCounter
  * @param  hrtimx High Resolution Timer instance
  * @param  fault This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_FLT1
  *         @arg @ref LL_HRTIM_FLT2
  *         @arg @ref LL_HRTIM_FLT3
  *         @arg @ref LL_HRTIM_FLT4
  *         @arg @ref LL_HRTIM_FLT5
  *         @arg @ref LL_HRTIM_FLT6
  *         @arg @ref LL_HRTIM_FLT7
  *         @arg @ref LL_HRTIM_FLT8
  */
__STATIC_INLINE void LL_HRTIM_FLT_ResetCounter(const HRTIM_TypeDef *hrtimx, uint32_t fault)
{
  uint32_t ifault = STM32_POSITION_VAL(fault);
  __IOM uint32_t *preg = (fault < LL_HRTIM_FLT5) ? \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR3))) : \
                         (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sCommonRegs.FLTINR4)));

  STM32_SET_BIT(*preg, (uint32_t)(HRTIM_FLTINR3_FLT1CRES) << REG_SHIFT_TAB_FLTxBLKE[ifault]);
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_Burst_Mode_management Burst_Mode_management
  * @{
  */

/**
  * @brief  Configure the burst mode controller.
  * @rmtoll
  *  BMCR     BMOM        LL_HRTIM_BM_Config \n
  *  BMCR     BMCLK       LL_HRTIM_BM_Config \n
  *  BMCR     BMPRSC      LL_HRTIM_BM_Config
  * @param  hrtimx High Resolution Timer instance
  * @param  burst_mode_config This parameter must be a combination of all the following values:
  *         Mode
  *         @arg @ref LL_HRTIM_BM_MODE_SINGLE_SHOT
  *         @arg @ref LL_HRTIM_BM_MODE_CONTINUOUS
  *
  *         Clock source
  *         @arg @ref LL_HRTIM_BM_CLKSRC_MASTER
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMA
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMB
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMC
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMD
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIME
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMF
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM12_OC1
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM13_OC1
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM7_TRGO
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM27_TRGO
  *         @arg @ref LL_HRTIM_BM_CLKSRC_HRTIM
  *
  *         Prescaler
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV8
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV16
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV32
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV64
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV128
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV256
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV512
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV1024
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV2048
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV4096
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV8192
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV16384
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV32768
  */
__STATIC_INLINE void LL_HRTIM_BM_Config(HRTIM_TypeDef *hrtimx, uint32_t burst_mode_config)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.BMCR, LL_HRTIM_BM_CONFIG_MASK, burst_mode_config);
}

/**
  * @brief  Set the burst mode controller operating mode.
  * @rmtoll
  *  BMCR     BMOM        LL_HRTIM_BM_SetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  operating_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BM_MODE_SINGLE_SHOT
  *         @arg @ref LL_HRTIM_BM_MODE_CONTINUOUS
  */
__STATIC_INLINE void LL_HRTIM_BM_SetMode(HRTIM_TypeDef *hrtimx, uint32_t operating_mode)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMOM, operating_mode);
}

/**
  * @brief  Get actual burst mode controller operating mode.
  * @rmtoll
  *  BMCR     BMOM        LL_HRTIM_BM_GetMode
  * @param  hrtimx High Resolution Timer instance
  * @retval operating_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BM_MODE_SINGLE_SHOT
  *         @arg @ref LL_HRTIM_BM_MODE_CONTINUOUS
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetMode(const HRTIM_TypeDef *hrtimx)
{
  return (uint32_t)STM32_READ_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMOM);
}

/**
  * @brief  Set the burst mode controller clock source.
  * @rmtoll
  *  BMCR     BMCLK       LL_HRTIM_BM_SetClockSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  clock_src This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BM_CLKSRC_MASTER
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMA
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMB
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMC
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMD
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIME
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMF
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM12_OC1
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM13_OC1
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM7_TRGO
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM27_TRGO
  *         @arg @ref LL_HRTIM_BM_CLKSRC_HRTIM
  */
__STATIC_INLINE void LL_HRTIM_BM_SetClockSrc(HRTIM_TypeDef *hrtimx, uint32_t clock_src)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMCLK, clock_src);
}

/**
  * @brief  Get actual burst mode controller clock source.
  * @rmtoll
  *  BMCR     BMCLK       LL_HRTIM_BM_GetClockSrc
  * @param  hrtimx High Resolution Timer instance
  * @retval clock_src This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BM_CLKSRC_MASTER
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMA
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMB
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMC
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMD
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIME
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIMF
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM12_OC1
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM13_OC1
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM7_TRGO
  *         @arg @ref LL_HRTIM_BM_CLKSRC_TIM27_TRGO
  *         @arg @ref LL_HRTIM_BM_CLKSRC_HRTIM
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetClockSrc(const HRTIM_TypeDef *hrtimx)
{
  return (uint32_t)STM32_READ_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMCLK);
}

/**
  * @brief  Set the burst mode controller prescaler.
  * @rmtoll
  *  BMCR     BMPRSC      LL_HRTIM_BM_SetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV8
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV16
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV32
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV64
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV128
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV256
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV512
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV1024
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV2048
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV4096
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV8192
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV16384
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV32768
  */
__STATIC_INLINE void LL_HRTIM_BM_SetPrescaler(HRTIM_TypeDef *hrtimx, uint32_t prescaler)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMPRSC, prescaler);
}

/**
  * @brief  Get actual burst mode controller prescaler setting.
  * @rmtoll
  *  BMCR     BMPRSC      LL_HRTIM_BM_GetPrescaler
  * @param  hrtimx High Resolution Timer instance
  * @retval prescaler This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV1
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV2
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV4
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV8
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV16
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV32
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV64
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV128
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV256
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV512
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV1024
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV2048
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV4096
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV8192
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV16384
  *         @arg @ref LL_HRTIM_BM_PRESCALER_DIV32768
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetPrescaler(const HRTIM_TypeDef *hrtimx)
{
  return (uint32_t)STM32_READ_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMPRSC);
}

/**
  * @brief  Enable burst mode compare and period registers preload.
  * @rmtoll
  *  BMCR     BMPREN      LL_HRTIM_BM_EnablePreload
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_BM_EnablePreload(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMPREN);
}

/**
  * @brief  Disable burst mode compare and period registers preload.
  * @rmtoll
  *  BMCR     BMPREN      LL_HRTIM_BM_DisablePreload
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_BM_DisablePreload(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMPREN);
}

/**
  * @brief  Indicate whether burst mode compare and period registers are preloaded.
  * @rmtoll
  *  BMCR     BMPREN      LL_HRTIM_BM_IsEnabledPreload
  * @param  hrtimx High Resolution Timer instance
  * @retval State of BMPREN bit in HRTIM_BMCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_IsEnabledPreload(const HRTIM_TypeDef *hrtimx)
{
  uint32_t temp;  /* MISRA C:2012 compliance */
  temp = STM32_READ_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMPREN);

  return ((temp == (HRTIM_BMCR_BMPREN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the burst mode controller trigger.
  * @rmtoll
  *  BMTRGR     SW           LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     MSTRST       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     MSTREP       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     MSTCMP1      LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     MSTCMP2      LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     MSTCMP3      LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     MSTCMP4      LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TARST        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TAREP        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TACMP1       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TACMP2       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TBRST        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TBREP        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TBCMP1       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TBCMP2       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TCRST        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TCREP        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TCCMP1       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TDRST        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TDREP        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TDCMP2       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TEREP        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TECMP1       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TECMP2       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TFREP        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TFRST        LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TFCMP1       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TAEEV7       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     TAEEV8       LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     EEV7         LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     EEV8         LL_HRTIM_BM_SetTrig \n
  *  BMTRGR     OCHIPEV      LL_HRTIM_BM_SetTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  trigger_source This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_BM_TRIG_NONE
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP3
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP4
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMC_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMC_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMC_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIME_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIME_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIME_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMF_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMF_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMF_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_EEVG
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_EEVH
  *         @arg @ref LL_HRTIM_BM_TRIG_EEVG
  *         @arg @ref LL_HRTIM_BM_TRIG_EEVH
  *         @arg @ref LL_HRTIM_BM_TRIG_ONCHIP
    */
__STATIC_INLINE void LL_HRTIM_BM_SetTrig(HRTIM_TypeDef *hrtimx, uint32_t trigger_source)
{
  STM32_WRITE_REG(hrtimx->sCommonRegs.BMTRGR, trigger_source);
}

/**
  * @brief  Get actual burst mode controller trigger.
  * @rmtoll
  *  BMTRGR     SW           LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     MSTRST       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     MSTREP       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     MSTCMP1      LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     MSTCMP2      LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     MSTCMP3      LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     MSTCMP4      LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TARST        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TAREP        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TACMP1       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TACMP2       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TBRST        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TBREP        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TBCMP1       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TBCMP2       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TCRST        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TCREP        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TCCMP1       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TDRST        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TDREP        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TDCMP2       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TEREP        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TECMP1       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TECMP2       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TFREP        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TFRST        LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TFCMP1       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TAEEV7       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     TAEEV8       LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     EEV7         LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     EEV8         LL_HRTIM_BM_GetTrig \n
  *  BMTRGR     OCHIPEV      LL_HRTIM_BM_GetTrig
  * @param  hrtimx High Resolution Timer instance
  * @retval trigger_source This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_BM_TRIG_NONE
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP3
  *         @arg @ref LL_HRTIM_BM_TRIG_MASTER_CMP4
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMB_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMC_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMC_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMC_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIME_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIME_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIME_CMP2
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMF_RESET
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMF_REPETITION
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMF_CMP1
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMA_EEVG
  *         @arg @ref LL_HRTIM_BM_TRIG_TIMD_EEVH
  *         @arg @ref LL_HRTIM_BM_TRIG_EEVG
  *         @arg @ref LL_HRTIM_BM_TRIG_EEVH
  *         @arg @ref LL_HRTIM_BM_TRIG_ONCHIP
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetTrig(const HRTIM_TypeDef *hrtimx)
{
  return (uint32_t)STM32_READ_REG(hrtimx->sCommonRegs.BMTRGR);
}
#if defined(PLAY1)

/**
  * @brief  Set the burst mode controller trigger input source.
  * @rmtoll
  *  OR     BMTRGSEL      LL_HRTIM_BM_SetTrigInputSrc
  * @param  hrtimx High Resolution Timer instance
  * @param  trigger_source This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_BM_TRIG_SRC_TIM26_TRGO
  *         @arg @ref LL_HRTIM_BM_TRIG_SRC_PLAY1_OUT13
    */
__STATIC_INLINE void LL_HRTIM_BM_SetTrigInputSrc(HRTIM_TypeDef *hrtimx, uint32_t trigger_source)
{
  STM32_MODIFY_REG(hrtimx->sCommonRegs.OR, HRTIM_OR_BMTRGSEL, trigger_source);
}

/**
  * @brief  Set the burst mode controller trigger input source.
  * @rmtoll
  *  OR     BMTRGSEL      LL_HRTIM_BM_GetTrigInputSrc
  * @param  hrtimx High Resolution Timer instance
  * @retval trigger_source This parameter can be a combination of the following values:
  *         @arg @ref LL_HRTIM_BM_TRIG_SRC_TIM26_TRGO
  *         @arg @ref LL_HRTIM_BM_TRIG_SRC_PLAY1_OUT13
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetTrigInputSrc(const HRTIM_TypeDef *hrtimx)
{
  return (uint32_t)STM32_READ_REG(hrtimx->sCommonRegs.OR);
}
#endif /* PLAY1 */

/**
  * @brief  Set the burst mode controller compare value.
  * @rmtoll
  *  BMCMPR     BMCMP      LL_HRTIM_BM_SetCompare
  * @param  hrtimx High Resolution Timer instance
  * @param  compare_value Value between 0 and 0xFFFF
  */
__STATIC_INLINE void LL_HRTIM_BM_SetCompare(HRTIM_TypeDef *hrtimx, uint32_t compare_value)
{
  STM32_WRITE_REG(hrtimx->sCommonRegs.BMCMPR, compare_value);
}

/**
  * @brief  Get actual burst mode controller compare value.
  * @rmtoll
  *  BMCMPR     BMCMP      LL_HRTIM_BM_GetCompare
  * @param  hrtimx High Resolution Timer instance
  * @retval compare_value Value between 0 and 0xFFFF.
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetCompare(const HRTIM_TypeDef *hrtimx)
{
  return (uint32_t)STM32_READ_REG(hrtimx->sCommonRegs.BMCMPR);
}

/**
  * @brief  Set the burst mode controller period.
  * @rmtoll
  *  BMPER     BMPER      LL_HRTIM_BM_SetPeriod
  * @param  hrtimx High Resolution Timer instance
  * @param  period Value between 0 and 0xFFFF
  */
__STATIC_INLINE void LL_HRTIM_BM_SetPeriod(HRTIM_TypeDef *hrtimx, uint32_t period)
{
  STM32_WRITE_REG(hrtimx->sCommonRegs.BMPER, period);
}

/**
  * @brief  Get actual burst mode controller period.
  * @rmtoll
  *  BMPER     BMPER      LL_HRTIM_BM_GetPeriod
  * @param  hrtimx High Resolution Timer instance
  * @retval period Value between 0 and 0xFFFF.
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetPeriod(const HRTIM_TypeDef *hrtimx)
{
  return (uint32_t)STM32_READ_REG(hrtimx->sCommonRegs.BMPER);
}

/**
  * @brief  Enable the burst mode controller.
  * @rmtoll
  *  BMCR     BME      LL_HRTIM_BM_Enable
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_BM_Enable(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BME);
}

/**
  * @brief  Disable the burst mode controller.
  * @rmtoll
  *  BMCR     BME      LL_HRTIM_BM_Disable
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_BM_Disable(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BME);
}

/**
  * @brief  Indicate whether the burst mode controller is enabled.
  * @rmtoll
  *  BMCR     BME      LL_HRTIM_BM_IsEnabled
  * @param  hrtimx High Resolution Timer instance
  * @retval State of BME bit in HRTIM_BMCR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_IsEnabled(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BME) == (HRTIM_BMCR_BME)) ? 1UL : 0UL);
}

/**
  * @brief  Trigger the burst operation (software trigger).
  * @rmtoll
  *  BMTRGR     SW           LL_HRTIM_BM_Start
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_BM_Start(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.BMTRGR, HRTIM_BMTRGR_SW);
}

/**
  * @brief  Stop the burst mode operation.
  * @rmtoll
  *  BMCR     BMSTAT           LL_HRTIM_BM_Stop
  * @param  hrtimx High Resolution Timer instance
  * @note Causes a burst mode early termination.
  */
__STATIC_INLINE void LL_HRTIM_BM_Stop(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMSTAT);
}

/**
  * @brief  Get actual burst mode status.
  * @rmtoll
  *  BMCR     BMSTAT           LL_HRTIM_BM_GetStatus
  * @param  hrtimx High Resolution Timer instance
  * @retval Status This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_BM_STATUS_NORMAL
  *         @arg @ref LL_HRTIM_BM_STATUS_BURST_ONGOING
  */
__STATIC_INLINE uint32_t LL_HRTIM_BM_GetStatus(const HRTIM_TypeDef *hrtimx)
{
  return (STM32_READ_BIT(hrtimx->sCommonRegs.BMCR, HRTIM_BMCR_BMSTAT));
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_Crossbar_Override Crossbar_Override
  * @{
  */
/**
  * @brief  Enable crossbar override.
  * @rmtoll
  *  TIMxCR2     COE      LL_HRTIM_CO_Enable
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_CO_Enable(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxCR2_COE);
}

/**
  * @brief  Disable crossbar override.
  * @rmtoll
  *  TIMxCR2     COE      LL_HRTIM_CO_Disable
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_CO_Disable(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxCR2_COE);
}

/**
  * @brief  Indicate whether the crossbar override is enabled.
  * @rmtoll
  *  TIMxCR2     COE      LL_HRTIM_CO_IsEnabled
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_IsEnabled(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxCR2_COE) == (HRTIM_TIMxCR2_COE)) ? 1UL : 0UL);
}

/**
  * @brief  Rearm the crossbar override.
  * @rmtoll
  *  TIMxCR2     COR      LL_HRTIM_CO_Rearm
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note This function disengage the crossbar override mode when
  *       it operates in latched mode (see @ref LL_HRTIM_CO_SetMode).
  * @note The rearming will be effective only if the triggering condition has
  *       disappeared (see @ref LL_HRTIM_CO_GetTriggerStatus).
  */
__STATIC_INLINE void LL_HRTIM_CO_Rearm(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxCR2_COR);
}

/**
  * @brief  Return the corssbar override status.
  * @rmtoll
  *  TIMxISR      COS        LL_HRTIM_CO_GetStatus
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval cos This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_STATUS_INACTIVE
  *         @arg @ref LL_HRTIM_CO_STATUS_ACTIVE
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_GetStatus(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxISR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return (STM32_READ_BIT(*preg, HRTIM_TIMxISR_COS));
}

/**
  * @brief  Return the corssbar override trigger status.
  * @rmtoll
  *  TIMxISR      COTS       LL_HRTIM_CO_GetTriggerStatus
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @note This function can be called to poll the override trigger status
  *       before rearming the crossbar override mode (see @ref LL_HRTIM_CO_Rearm).
  * @retval cots This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_TRIGGER_INACTIVE
  *         @arg @ref LL_HRTIM_CO_TRIGGER_ACTIVE
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_GetTriggerStatus(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxISR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return (STM32_READ_BIT(*preg, HRTIM_TIMxISR_COTS));
}

/**
  * @brief  Set the crossbar override mode.
  * @rmtoll
  *  TIMxCR2     COM      LL_HRTIM_CO_SetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  crossbar_override_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_MODE_CYCLE_BY_CYCLE
  *         @arg @ref LL_HRTIM_CO_MODE_LATCHED
  */
__STATIC_INLINE void LL_HRTIM_CO_SetMode(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t crossbar_override_mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  STM32_MODIFY_REG(*preg, HRTIM_TIMxCR2_COM, crossbar_override_mode);
}

/**
  * @brief  Get the crossbar override mode.
  * @rmtoll
  *  TIMxCR2     COM      LL_HRTIM_CO_GetMode
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  crossbar_override_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_MODE_CYCLE_BY_CYCLE
  *         @arg @ref LL_HRTIM_CO_MODE_LATCHED
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_GetMode(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return (uint32_t)STM32_READ_BIT(*preg, HRTIM_TIMxCR2_COM);
}

/**
  * @brief  Get the crossbar override trigger(s).
  * @rmtoll
  *  COTRGxR     SWT       LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT1      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT2      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT3      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT4      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT5      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT6      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT7      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT8      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT1A2    LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT2A3    LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT3A4    LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT4A5    LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT5A6    LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT6A7    LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     FLT7A8    LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVA      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVB      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVC      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVD      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVE      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVF      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVG      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVH      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVI      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EEVJ      LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EXT_TRG0  LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EXT_TRG1  LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EXT_TRG2  LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EXT_TRG3  LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EXT_TRG4  LL_HRTIM_CO_SetTrig \n
  *  COTRGxR     EXT_TRG5  LL_HRTIM_CO_SetTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  trigger_source This parameter must one of the following values:
  *         @arg @ref LL_HRTIM_CO_TRIG_NONE can be used to disable all the
  *                   crossbar override triggers.
  *         @arg @ref LL_HRTIM_CO_TRIG_SW can be used to trigger a crossbar
  *                   override by software.
  *         Or a combination of all the following values:
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT1
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT2
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT3
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT4
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT5
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT6
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT7
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT8
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT1_FLT2
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT2_FLT3
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT3_FLT4
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT4_FLT5
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT5_FLT6
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT6_FLT7
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT7_FLT8
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVA
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVB
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVC
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVD
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVE
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVF
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVG
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVH
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVI
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVJ
  * @if PLAY1
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT1 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT2 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT3 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT4 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT5 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT6 (*)
  * @endif
  *         (*)  Value not defined in all devices.  \n
  */
__STATIC_INLINE void LL_HRTIM_CO_SetTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t trigger_source)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].COTRGxR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_WRITE_REG(*preg, trigger_source);
}

/**
  * @brief  Get the crossbar override trigger(s).
  * @rmtoll
  *  COTRGxR     SWT       LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT1      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT2      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT3      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT4      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT5      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT6      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT7      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT8      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT1A2    LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT2A3    LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT3A4    LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT4A5    LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT5A6    LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT6A7    LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     FLT7A8    LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVA      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVB      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVC      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVD      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVE      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVF      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVG      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVH      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVI      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EEVJ      LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EXT_TRG0  LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EXT_TRG1  LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EXT_TRG2  LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EXT_TRG3  LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EXT_TRG4  LL_HRTIM_CO_GetTrig \n
  *  COTRGxR     EXT_TRG5  LL_HRTIM_CO_GetTrig
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval  trig This parameter must one of the following values:
  *         @arg @ref LL_HRTIM_CO_TRIG_NONE can be used to disable all the
  *                   crossbar override triggers.
  *         @arg @ref LL_HRTIM_CO_TRIG_SW can be used to trigger a crossbar
  *                   override by software.
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT1
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT2
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT3
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT4
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT5
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT6
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT7
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT8
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT1_FLT2
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT2_FLT3
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT3_FLT4
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT4_FLT5
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT5_FLT6
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT6_FLT7
  *         @arg @ref LL_HRTIM_CO_TRIG_FLT7_FLT8
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVA
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVB
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVC
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVD
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVE
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVF
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVG
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVH
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVI
  *         @arg @ref LL_HRTIM_CO_TRIG_EEVJ
  * @if PLAY1
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT1 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT2 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT3 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT4 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT5 (*)
  *         @arg @ref LL_HRTIM_CO_TRIG_PLAY1_OUT6 (*)
  * @endif
  *         (*)  Value not defined in all devices.  \n
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_GetTrig(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].COTRGxR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  return (STM32_READ_REG(*preg));
}

/**
  * @brief  Set the crossbar override force mode for an output.
  * @rmtoll
  *  COFExR     COFMA      LL_HRTIM_CO_SetForceMode \n
  *  COFExR     COFMB      LL_HRTIM_CO_SetForceMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  force_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY1
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY2
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_INACTIVE
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_ACTIVE
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_EVENT
  */
__STATIC_INLINE void LL_HRTIM_CO_SetForceMode(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t force_mode)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].COFExR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   HRTIM_COFExR_COFMA << (LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   force_mode  << (LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]));
}

/**
  * @brief  Get the crossbar override force mode for an output.
  * @rmtoll
  *  COFExR     COFMA      LL_HRTIM_CO_GetForceMode \n
  *  COFExR     COFMB      LL_HRTIM_CO_GetForceMode
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval force_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY1
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY2
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_INACTIVE
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_ACTIVE
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_EVENT
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_GetForceMode(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].COFExR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));

  return (uint32_t)(STM32_READ_BIT(*preg, HRTIM_COFExR_COFMA << (LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput])) >>
                    LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Set the crossbar override force mode for an output.
  * @rmtoll
  *  COFExR     EEVAFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVBFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVCFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVDFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVEFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVFFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVGFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVHFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVIFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVJFRCA      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVAFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVBFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVCFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVDFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVEFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVFFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVGFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVHFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVIFRCB      LL_HRTIM_CO_SetForcingEvents \n
  *  COFExR     EEVJFRCB      LL_HRTIM_CO_SetForcingEvents
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @param  events This parameter must one of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEON_NONE
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVA
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVB
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVC
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVD
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVE
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVF
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVG
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVH
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVI
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVJ
  */
__STATIC_INLINE void LL_HRTIM_CO_SetForcingEvents(const HRTIM_TypeDef *hrtimx, uint32_t output, uint32_t events)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].COFExR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));
  STM32_MODIFY_REG(*preg,
                   LL_HRTIM_COFEXR_EEVFRC_MASK << (LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]),
                   events  << LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Get the crossbar override force mode for an output.
  * @rmtoll
  *  COFExR     EEVAFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVBFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVCFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVDFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVEFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVFFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVGFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVHFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVIFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVJFRCA      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVAFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVBFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVCFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVDFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVEFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVFFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVGFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVHFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVIFRCB      LL_HRTIM_CO_GetForcingEvents \n
  *  COFExR     EEVJFRCB      LL_HRTIM_CO_GetForcingEvents
  * @param  hrtimx High Resolution Timer instance
  * @param  output This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_OUTPUT_CHA1
  *         @arg @ref LL_HRTIM_OUTPUT_CHA2
  *         @arg @ref LL_HRTIM_OUTPUT_CHB1
  *         @arg @ref LL_HRTIM_OUTPUT_CHB2
  *         @arg @ref LL_HRTIM_OUTPUT_CHC1
  *         @arg @ref LL_HRTIM_OUTPUT_CHC2
  *         @arg @ref LL_HRTIM_OUTPUT_CHD1
  *         @arg @ref LL_HRTIM_OUTPUT_CHD2
  *         @arg @ref LL_HRTIM_OUTPUT_CHE1
  *         @arg @ref LL_HRTIM_OUTPUT_CHE2
  *         @arg @ref LL_HRTIM_OUTPUT_CHF1
  *         @arg @ref LL_HRTIM_OUTPUT_CHF2
  * @retval events This parameter must one of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEON_NONE
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVA
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVB
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVC
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVD
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVE
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVF
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVG
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVH
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVI
  *         @arg @ref LL_HRTIM_CO_FORCEON_EEVJ
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_GetForcingEvents(const HRTIM_TypeDef *hrtimx, uint32_t output)
{
  uint32_t iOutput = (uint8_t)(STM32_POSITION_VAL(output) - STM32_POSITION_VAL(LL_HRTIM_OUTPUT_CHA1));
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].COFExR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_OUTxR[iOutput]));

  return (uint32_t)(STM32_READ_BIT(*preg, LL_HRTIM_COFEXR_EEVFRC_MASK << (LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput])) >>
                    LL_HRTIM_REG_SHIFT_TAB_OUTxR[iOutput]);
}

/**
  * @brief  Set the delay duration for the delayed faults.
  * @rmtoll
  *  CODExR     DLY1FLTD      LL_HRTIM_CO_SetDelay \n
  *  CODExR     DLY2FLTD      LL_HRTIM_CO_SetDelay
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  force_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY1
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY2
  * @param  delay This parameter can be a number between Min_Data=0x0 and Max_Data=0x1FF
  * @note  It is mandatory to program a delay 2 duration above the
  *        delay 1 duration.
  */
__STATIC_INLINE void LL_HRTIM_CO_SetDelay(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t force_mode,
                                          uint32_t delay)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CODExR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  STM32_MODIFY_REG(*preg,
                   HRTIM_CODExR_DLY1FLTD << (force_mode * HRTIM_CODExR_DLY2FLTD_Pos),
                   delay  << (force_mode * HRTIM_CODExR_DLY2FLTD_Pos));
}

/**
  * @brief  Get the delay duration for the delayed faults.
  * @rmtoll
  *  CODExR     DLY1FLTD      LL_HRTIM_CO_GetDelay \n
  *  CODExR     DLY2FLTD      LL_HRTIM_CO_GetDelay
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  force_mode This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY1
  *         @arg @ref LL_HRTIM_CO_FORCEMODE_DELAY2
  * @note  It is mandatory to program a delay 2 duration above the
  *        delay 1 duration.
  * @retval delay This parameter can be a number between Min_Data=0x0 and Max_Data=0x1FF.
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_GetDelay(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t force_mode)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].CODExR) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return (uint32_t)(STM32_READ_BIT(*preg, HRTIM_CODExR_DLY1FLTD << (force_mode * HRTIM_CODExR_DLY2FLTD_Pos)) >>
                    (force_mode * HRTIM_CODExR_DLY2FLTD_Pos));
}

/**
  * @brief  Enable dual channel DAC crossbar override.
  * @rmtoll
  *  TIMxCR2     DCDCOE      LL_HRTIM_CO_EnableDualChannelDac
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_CO_EnableDualChannelDac(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxCR2_DCDCOE);
}

/**
  * @brief  Disable dual channel DAC crossbar override.
  * @rmtoll
  *  TIMxCR2     DCDCOE      LL_HRTIM_CO_DisableDualChannelDac
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_CO_DisableDualChannelDac(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxCR2_DCDCOE);
}

/**
  * @brief  Indicate whether the dual channel DAC crossbar override is enabled.
  * @rmtoll
  *  TIMxCR2     DCDCOE      LL_HRTIM_CO_IsEnabledDualChannelDac
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE uint32_t LL_HRTIM_CO_IsEnabledDualChannelDac(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_TACEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sTimerxRegs[0].TIMxCR2) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxCR2_DCDCOE) == (HRTIM_TIMxCR2_DCDCOE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear the fault 1 interrupt flag.
  * @rmtoll
  *  ICR     FLT1C           LL_HRTIM_ClearFlag_FLT1
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT1(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT1C);
}

/**
  * @brief  Indicate whether fault 1 interrupt occurred.
  * @rmtoll
  *  ICR     FLT1           LL_HRTIM_IsActiveFlag_FLT1
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT1 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT1(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT1) == (HRTIM_ISR_FLT1)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the fault 2 interrupt flag.
  * @rmtoll
  *  ICR     FLT2C           LL_HRTIM_ClearFlag_FLT2
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT2(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT2C);
}

/**
  * @brief  Indicate whether fault 2 interrupt occurred.
  * @rmtoll
  *  ICR     FLT2           LL_HRTIM_IsActiveFlag_FLT2
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT2 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT2(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT2) == (HRTIM_ISR_FLT2)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the fault 3 interrupt flag.
  * @rmtoll
  *  ICR     FLT3C           LL_HRTIM_ClearFlag_FLT3
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT3(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT3C);
}

/**
  * @brief  Indicate whether fault 3 interrupt occurred.
  * @rmtoll
  *  ICR     FLT3           LL_HRTIM_IsActiveFlag_FLT3
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT3 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT3(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT3) == (HRTIM_ISR_FLT3)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the fault 4 interrupt flag.
  * @rmtoll
  *  ICR     FLT4C           LL_HRTIM_ClearFlag_FLT4
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT4(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT4C);
}

/**
  * @brief  Indicate whether fault 4 interrupt occurred.
  * @rmtoll
  *  ICR     FLT4           LL_HRTIM_IsActiveFlag_FLT4
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT4 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT4(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT4) == (HRTIM_ISR_FLT4)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the fault 5 interrupt flag.
  * @rmtoll
  *  ICR     FLT5C           LL_HRTIM_ClearFlag_FLT5
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT5(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT5C);
}

/**
  * @brief  Indicate whether fault 5 interrupt occurred.
  * @rmtoll
  *  ICR     FLT5           LL_HRTIM_IsActiveFlag_FLT5
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT5 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT5(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT5) == (HRTIM_ISR_FLT5)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the fault 6 interrupt flag.
  * @rmtoll
  *  ICR     FLT6C           LL_HRTIM_ClearFlag_FLT6
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT6(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT6C);
}

/**
  * @brief  Indicate whether fault 6 interrupt occurred.
  * @rmtoll
  *  ICR     FLT6           LL_HRTIM_IsActiveFlag_FLT6
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT6 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT6(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT6) == (HRTIM_ISR_FLT6)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the fault 7 interrupt flag.
  * @rmtoll
  *  ICR     FLT7C           LL_HRTIM_ClearFlag_FLT7
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT7(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT7C);
}

/**
  * @brief  Indicate whether fault 7 interrupt occurred.
  * @rmtoll
  *  ICR     FLT7           LL_HRTIM_IsActiveFlag_FLT7
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT7 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT7(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT7) == (HRTIM_ISR_FLT7)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the fault 8 interrupt flag.
  * @rmtoll
  *  ICR     FLT8C           LL_HRTIM_ClearFlag_FLT8
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_FLT8(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_FLT8C);
}

/**
  * @brief  Indicate whether fault 8 interrupt occurred.
  * @rmtoll
  *  ICR     FLT8           LL_HRTIM_IsActiveFlag_FLT8
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT8 bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_FLT8(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_FLT8) == (HRTIM_ISR_FLT8)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the System fault interrupt flag.
  * @rmtoll
  *  ICR     SYSFLTC           LL_HRTIM_ClearFlag_SYSFLT
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_SYSFLT(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_SYSFLTC);
}

/**
  * @brief  Indicate whether System fault interrupt occurred.
  * @rmtoll
  *  ISR     SYSFLT           LL_HRTIM_IsActiveFlag_SYSFLT
  * @param  hrtimx High Resolution Timer instance
  * @retval State of SYSFLT bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_SYSFLT(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_SYSFLT) == (HRTIM_ISR_SYSFLT)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the DLL ready interrupt flag.
  * @rmtoll
  *  ICR     DLLRDYC           LL_HRTIM_ClearFlag_DLLRDY
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_DLLRDY(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_DLLRDYC);
}

/**
  * @brief  Indicate whether DLL ready  interrupt occurred.
  * @rmtoll
  *  ISR     DLLRDY           LL_HRTIM_IsActiveFlag_DLLRDY
  * @param  hrtimx High Resolution Timer instance
  * @retval State of DLLRDY bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_DLLRDY(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_DLLRDY) == (HRTIM_ISR_DLLRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Burst Mode period interrupt flag.
  * @rmtoll
  *  ICR     BMPERC           LL_HRTIM_ClearFlag_BMPER
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_BMPER(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.ICR, HRTIM_ICR_BMPERC);
}

/**
  * @brief  Indicate whether Burst Mode period interrupt occurred.
  * @rmtoll
  *  ISR     BMPER           LL_HRTIM_IsActiveFlag_BMPER
  * @param  hrtimx High Resolution Timer instance
  * @retval State of BMPER bit in HRTIM_ISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_BMPER(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.ISR, HRTIM_ISR_BMPER) == (HRTIM_ISR_BMPER)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the Synchronization Input interrupt flag.
  * @rmtoll
  *  MICR     SYNCC           LL_HRTIM_ClearFlag_SYNC
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_SYNC(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sMasterRegs.MICR, HRTIM_MICR_SYNCC);
}

/**
  * @brief  Indicate whether the Synchronization Input interrupt occurred.
  * @rmtoll
  *  MISR     SYNC           LL_HRTIM_IsActiveFlag_SYNC
  * @param  hrtimx High Resolution Timer instance
  * @retval State of SYNC bit in HRTIM_MISR register  (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_SYNC(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sMasterRegs.MISR, HRTIM_MISR_SYNC) == (HRTIM_MISR_SYNC)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the update interrupt flag for a given timer (including the master timer).
  * @rmtoll
  *  MICR        MUPDC          LL_HRTIM_ClearFlag_UPDATE \n
  *  TIMxICR     UPDC           LL_HRTIM_ClearFlag_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MICR_MUPDC);
}

/**
  * @brief  Indicate whether the update interrupt has occurred for a given timer (including the master timer).
  * @rmtoll
  *  MISR        MUPD          LL_HRTIM_IsActiveFlag_UPDATE \n
  *  TIMxISR     UPD           LL_HRTIM_IsActiveFlag_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MUPD/UPD bit in HRTIM_MISR/HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MISR_MUPD) == (HRTIM_MISR_MUPD)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the repetition interrupt flag for a given timer (including the master timer).
  * @rmtoll
  *  MICR        MREPC          LL_HRTIM_ClearFlag_REP \n
  *  TIMxICR     REPC           LL_HRTIM_ClearFlag_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MICR_MREPC);

}

/**
  * @brief  Indicate whether the repetition  interrupt has occurred for a given timer (including the master timer).
  * @rmtoll
  *  MISR        MREP          LL_HRTIM_IsActiveFlag_REP \n
  *  TIMxISR     REP           LL_HRTIM_IsActiveFlag_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MREP/REP bit in HRTIM_MISR/HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MISR_MREP) == (HRTIM_MISR_MREP)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the compare 1 match interrupt for a given timer (including the master timer).
  * @rmtoll
  *  MICR        MCMP1C          LL_HRTIM_ClearFlag_CMP1 \n
  *  TIMxICR     CMP1C           LL_HRTIM_ClearFlag_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MICR_MCMP1C);
}

/**
  * @brief  Indicate whether the compare match 1  interrupt has occurred for a given timer (including the master timer).
  * @rmtoll
  *  MISR        MCMP1          LL_HRTIM_IsActiveFlag_CMP1 \n
  *  TIMxISR     CMP1           LL_HRTIM_IsActiveFlag_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP1/CMP1 bit in HRTIM_MISR/HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MISR_MCMP1) == (HRTIM_MISR_MCMP1)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the compare 2 match interrupt for a given timer (including the master timer).
  * @rmtoll
  *  MICR        MCMP2C          LL_HRTIM_ClearFlag_CMP2 \n
  *  TIMxICR     CMP2C           LL_HRTIM_ClearFlag_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MICR_MCMP2C);
}

/**
  * @brief  Indicate whether the compare match 2  interrupt has occurred for a given timer (including the master timer).
  * @rmtoll
  *  MISR        MCMP2          LL_HRTIM_IsActiveFlag_CMP2 \n
  *  TIMxISR     CMP2           LL_HRTIM_IsActiveFlag_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP2/CMP2 bit in HRTIM_MISR/HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MISR_MCMP2) == (HRTIM_MISR_MCMP2)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the compare 3 match interrupt for a given timer (including the master timer).
  * @rmtoll
  *  MICR        MCMP3C          LL_HRTIM_ClearFlag_CMP3 \n
  *  TIMxICR     CMP3C           LL_HRTIM_ClearFlag_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MICR_MCMP3C);
}

/**
  * @brief  Indicate whether the compare match 3  interrupt has occurred for a given timer (including the master timer).
  * @rmtoll
  *  MISR        MCMP3          LL_HRTIM_IsActiveFlag_CMP3 \n
  *  TIMxISR     CMP3           LL_HRTIM_IsActiveFlag_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP3/CMP3 bit in HRTIM_MISR/HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MISR_MCMP3) == (HRTIM_MISR_MCMP3)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the compare 4 match interrupt for a given timer (including the master timer).
  * @rmtoll
  *  MICR        MCMP4C          LL_HRTIM_ClearFlag_CMP4 \n
  *  TIMxICR     CMP4C           LL_HRTIM_ClearFlag_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MICR_MCMP4C);
}

/**
  * @brief  Indicate whether the compare match 4  interrupt has occurred for a given timer (including the master timer).
  * @rmtoll
  *  MISR        MCMP4          LL_HRTIM_IsActiveFlag_CMP4 \n
  *  TIMxISR     CMP4           LL_HRTIM_IsActiveFlag_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP4/CMP4 bit in HRTIM_MISR/HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MISR_MCMP4) == (HRTIM_MISR_MCMP4)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the capture 1 interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     CPT1C           LL_HRTIM_ClearFlag_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_CPT1C);
}

/**
  * @brief  Indicate whether the capture 1 interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     CPT1           LL_HRTIM_IsActiveFlag_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CPT1 bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_CPT1) == (HRTIM_TIMxISR_CPT1)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the capture 2 interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     CPT2C           LL_HRTIM_ClearFlag_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_CPT2C);
}

/**
  * @brief  Indicate whether the capture 2 interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     CPT2           LL_HRTIM_IsActiveFlag_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CPT2 bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_CPT2) == (HRTIM_TIMxISR_CPT2)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the output 1 set interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     SET1C           LL_HRTIM_ClearFlag_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_SET1C);
}

/**
  * @brief  Indicate whether the output 1 set interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     SET1           LL_HRTIM_IsActiveFlag_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of SETx1 bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_SET1) == (HRTIM_TIMxISR_SET1)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the output 1 reset interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     RST1C           LL_HRTIM_ClearFlag_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_RST1C);
}

/**
  * @brief  Indicate whether the output 1 reset interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     RST1           LL_HRTIM_IsActiveFlag_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RSTx1 bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_RST1) == (HRTIM_TIMxISR_RST1)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the output 2 set interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     SET2C           LL_HRTIM_ClearFlag_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_SET2C);
}

/**
  * @brief  Indicate whether the output 2 set interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     SET2           LL_HRTIM_IsActiveFlag_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of SETx2 bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_SET2) == (HRTIM_TIMxISR_SET2)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the output 2reset interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     RST2C           LL_HRTIM_ClearFlag_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_RST2C);
}

/**
  * @brief  Indicate whether the output 2 reset interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     RST2           LL_HRTIM_IsActiveFlag_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RSTx2 bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_RST2) == (HRTIM_TIMxISR_RST2)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the reset and/or roll-over interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     RSTC           LL_HRTIM_ClearFlag_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_RSTC);
}

/**
  * @brief  Indicate whether the  reset and/or roll-over interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     RST           LL_HRTIM_IsActiveFlag_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RST bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_RST) == (HRTIM_TIMxISR_RST)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the delayed protection interrupt flag for a given timer.
  * @rmtoll
  *  TIMxICR     DLYPRTC           LL_HRTIM_ClearFlag_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_DLYPRTC);
}

/**
  * @brief  Indicate whether the  delayed protection interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     DLYPRT           LL_HRTIM_IsActiveFlag_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DLYPRT bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_DLYPRT) == (HRTIM_TIMxISR_DLYPRT)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the crossbar override trigger flag for a given timer.
  * @rmtoll
  *  TIMxICR     COTC           LL_HRTIM_ClearFlag_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_COTC);
}

/**
  * @brief  Indicate whether the crossbar override trigger interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     COT           LL_HRTIM_IsActiveFlag_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of COT bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_COT) == (HRTIM_TIMxISR_COT)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the crossbar override rearm delay elapsed flag for a given timer.
  * @rmtoll
  *  TIMxICR     CORDEC           LL_HRTIM_ClearFlag_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_ClearFlag_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MICR) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxICR_CORDEC);
}

/**
  * @brief  Indicate whether the crossbar override rearm delay elapsed interrupt occurred for a given timer.
  * @rmtoll
  *  TIMxISR     CORDE           LL_HRTIM_IsActiveFlag_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CORDE bit in HRTIM_TIMxISR register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsActiveFlag_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IM uint32_t *preg = (__IM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MISR) +
                                                     LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxISR_CORDE) == (HRTIM_TIMxISR_CORDE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable HRTIM global interrupts.
  * @rmtoll
  *  IER      FLT1IE          LL_HRTIM_EnableIT \n
  *  IER      FLT2IE          LL_HRTIM_EnableIT \n
  *  IER      FLT3IE          LL_HRTIM_EnableIT \n
  *  IER      FLT4IE          LL_HRTIM_EnableIT \n
  *  IER      FLT5IE          LL_HRTIM_EnableIT \n
  *  IER      FLT6IE          LL_HRTIM_EnableIT \n
  *  IER      FLT7IE          LL_HRTIM_EnableIT \n
  *  IER      FLT8IE          LL_HRTIM_EnableIT \n
  *  IER      SYSFLTIE        LL_HRTIM_EnableIT \n
  *  IER      BMPERIE         LL_HRTIM_EnableIT
  * @param  hrtimx High Resolution Timer instance
  * @param  mask Interrupts to enable.
  *         This parameter can be:
  *         @arg @ref LL_HRTIM_IER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_IER_FLT1IE
  *         @arg @ref LL_HRTIM_IER_FLT2IE
  *         @arg @ref LL_HRTIM_IER_FLT3IE
  *         @arg @ref LL_HRTIM_IER_FLT4IE
  *         @arg @ref LL_HRTIM_IER_FLT5IE
  *         @arg @ref LL_HRTIM_IER_FLT6IE
  *         @arg @ref LL_HRTIM_IER_FLT7IE
  *         @arg @ref LL_HRTIM_IER_FLT8IE
  *         @arg @ref LL_HRTIM_IER_SYSFLTIE
  *         @arg @ref LL_HRTIM_IER_BMPERIE
  */
__STATIC_INLINE void LL_HRTIM_EnableIT(HRTIM_TypeDef *hrtimx, uint32_t mask)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, mask);
}

/**
  * @brief  Disable HRTIM global interrupts.
  * @rmtoll
  *  IER      FLT1IE          LL_HRTIM_DisableIT \n
  *  IER      FLT2IE          LL_HRTIM_DisableIT \n
  *  IER      FLT3IE          LL_HRTIM_DisableIT \n
  *  IER      FLT4IE          LL_HRTIM_DisableIT \n
  *  IER      FLT5IE          LL_HRTIM_DisableIT \n
  *  IER      FLT6IE          LL_HRTIM_DisableIT \n
  *  IER      FLT7IE          LL_HRTIM_DisableIT \n
  *  IER      FLT8IE          LL_HRTIM_DisableIT \n
  *  IER      SYSFLTIE        LL_HRTIM_DisableIT \n
  *  IER      BMPERIE         LL_HRTIM_DisableIT
  * @param  hrtimx High Resolution Timer instance
  * @param  mask Interrupts to disable.
  *         This parameter can be:
  *         @arg @ref LL_HRTIM_IER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_IER_FLT1IE
  *         @arg @ref LL_HRTIM_IER_FLT2IE
  *         @arg @ref LL_HRTIM_IER_FLT3IE
  *         @arg @ref LL_HRTIM_IER_FLT4IE
  *         @arg @ref LL_HRTIM_IER_FLT5IE
  *         @arg @ref LL_HRTIM_IER_FLT6IE
  *         @arg @ref LL_HRTIM_IER_SYSFLTIE
  *         @arg @ref LL_HRTIM_IER_BMPERIE
  */
__STATIC_INLINE void LL_HRTIM_DisableIT(HRTIM_TypeDef *hrtimx, uint32_t mask)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, mask);
}

/**
  * @brief  Check whether the specified HRTIM global interrupts are enabled or not.
  * @rmtoll
  *  IER      FLT1IE          LL_HRTIM_IsEnabledIT \n
  *  IER      FLT2IE          LL_HRTIM_IsEnabledIT \n
  *  IER      FLT3IE          LL_HRTIM_IsEnabledIT \n
  *  IER      FLT4IE          LL_HRTIM_IsEnabledIT \n
  *  IER      FLT5IE          LL_HRTIM_IsEnabledIT \n
  *  IER      FLT6IE          LL_HRTIM_IsEnabledIT \n
  *  IER      FLT7IE          LL_HRTIM_IsEnabledIT \n
  *  IER      FLT8IE          LL_HRTIM_IsEnabledIT \n
  *  IER      SYSFLTIE        LL_HRTIM_IsEnabledIT \n
  *  IER      BMPERIE         LL_HRTIM_IsEnabledIT
  * @param  hrtimx High Resolution Timer instance
  * @param  mask Interrupts to check.
  *         This parameter can be:
  *         @arg @ref LL_HRTIM_IER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_IER_FLT1IE
  *         @arg @ref LL_HRTIM_IER_FLT2IE
  *         @arg @ref LL_HRTIM_IER_FLT3IE
  *         @arg @ref LL_HRTIM_IER_FLT4IE
  *         @arg @ref LL_HRTIM_IER_FLT5IE
  *         @arg @ref LL_HRTIM_IER_FLT6IE
  *         @arg @ref LL_HRTIM_IER_SYSFLTIE
  *         @arg @ref LL_HRTIM_IER_BMPERIE
  * @retval State of interrupts sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT(const HRTIM_TypeDef *hrtimx, uint32_t mask)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, mask) == (mask)) ? 1UL : 0UL);
}

/**
  * @brief  Enable timer interrupts.
  * @rmtoll
  *  MDIER        MCMP1IE          LL_HRTIM_TIM_EnableIT \n
  *  MDIER        MCMP2IE          LL_HRTIM_TIM_EnableIT \n
  *  MDIER        MCMP3IE          LL_HRTIM_TIM_EnableIT \n
  *  MDIER        MCMP4IE          LL_HRTIM_TIM_EnableIT \n
  *  MDIER        MREPIE           LL_HRTIM_TIM_EnableIT \n
  *  MDIER        MSYNCIE          LL_HRTIM_TIM_EnableIT \n
  *  MDIER        MUPDIE           LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     CMP1IE           LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     CMP2IE           LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     CMP3IE           LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     CMP4IE           LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     REPIE            LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     UPDIE            LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     CPT1IE           LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     CPT2IE           LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     SETx1IE          LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     RTSx1IE          LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     SETx2IE          LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     RTSx2IE          LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     RSTIE            LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     DLYPRTIE         LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     COTIE            LL_HRTIM_TIM_EnableIT \n
  *  TIMxDIER     CORDEIE          LL_HRTIM_TIM_EnableIT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  mask Timer interrupts to enable.
  *         For the master timer this parameter can be:
  *         @arg @ref LL_HRTIM_MDIER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_MDIER_MCMP1IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP2IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP3IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP4IE
  *         @arg @ref LL_HRTIM_MDIER_MREPIE
  *         @arg @ref LL_HRTIM_MDIER_SYNCIE
  *         @arg @ref LL_HRTIM_MDIER_MUPDIE
  *
  *         For the timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_TIMDIER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMDIER_CMP1IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP2IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP3IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP4IE
  *         @arg @ref LL_HRTIM_TIMDIER_REPIE
  *         @arg @ref LL_HRTIM_TIMDIER_UPDIE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT1IE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT2IE
  *         @arg @ref LL_HRTIM_TIMDIER_SET1IE
  *         @arg @ref LL_HRTIM_TIMDIER_RST1IE
  *         @arg @ref LL_HRTIM_TIMDIER_SET2IE
  *         @arg @ref LL_HRTIM_TIMDIER_RST2IE
  *         @arg @ref LL_HRTIM_TIMDIER_RSTIE
  *         @arg @ref LL_HRTIM_TIMDIER_DLYPRTIE
  *         @arg @ref LL_HRTIM_TIMDIER_COTIE
  *         @arg @ref LL_HRTIM_TIMDIER_CORDEIE
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableIT(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t mask)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, mask);
}

/**
  * @brief  Disable timer interrupts.
  * @rmtoll
  *  MDIER        MCMP1IE          LL_HRTIM_TIM_DisableIT \n
  *  MDIER        MCMP2IE          LL_HRTIM_TIM_DisableIT \n
  *  MDIER        MCMP3IE          LL_HRTIM_TIM_DisableIT \n
  *  MDIER        MCMP4IE          LL_HRTIM_TIM_DisableIT \n
  *  MDIER        MREPIE           LL_HRTIM_TIM_DisableIT \n
  *  MDIER        MSYNCIE          LL_HRTIM_TIM_DisableIT \n
  *  MDIER        MUPDIE           LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     CMP1IE           LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     CMP2IE           LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     CMP3IE           LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     CMP4IE           LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     REPIE            LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     UPDIE            LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     CPT1IE           LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     CPT2IE           LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     SETx1IE          LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     RTSx1IE          LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     SETx2IE          LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     RTSx2IE          LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     RSTIE            LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     DLYPRTIE         LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     COTIE            LL_HRTIM_TIM_DisableIT \n
  *  TIMxDIER     CORDEIE          LL_HRTIM_TIM_DisableIT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  mask Timer interrupts to disable.
  *         For the master timer this parameter can be:
  *         @arg @ref LL_HRTIM_MDIER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_MDIER_MCMP1IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP2IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP3IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP4IE
  *         @arg @ref LL_HRTIM_MDIER_MREPIE
  *         @arg @ref LL_HRTIM_MDIER_SYNCIE
  *         @arg @ref LL_HRTIM_MDIER_MUPDIE
  *
  *         For the timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_TIMDIER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMDIER_CMP1IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP2IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP3IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP4IE
  *         @arg @ref LL_HRTIM_TIMDIER_REPIE
  *         @arg @ref LL_HRTIM_TIMDIER_UPDIE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT1IE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT2IE
  *         @arg @ref LL_HRTIM_TIMDIER_SET1IE
  *         @arg @ref LL_HRTIM_TIMDIER_RST1IE
  *         @arg @ref LL_HRTIM_TIMDIER_SET2IE
  *         @arg @ref LL_HRTIM_TIMDIER_RST2IE
  *         @arg @ref LL_HRTIM_TIMDIER_RSTIE
  *         @arg @ref LL_HRTIM_TIMDIER_DLYPRTIE
  *         @arg @ref LL_HRTIM_TIMDIER_COTIE
  *         @arg @ref LL_HRTIM_TIMDIER_CORDEIE
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableIT(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t mask)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, mask);
}

/**
  * @brief  Check whether the specified timer interrupts are enabled or not.
  * @rmtoll
  *  MDIER        MCMP1IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  MDIER        MCMP2IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  MDIER        MCMP3IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  MDIER        MCMP4IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  MDIER        MREPIE           LL_HRTIM_TIM_IsEnabledIT \n
  *  MDIER        MSYNCIE          LL_HRTIM_TIM_IsEnabledIT \n
  *  MDIER        MUPDIE           LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     CMP1IE           LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     CMP2IE           LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     CMP3IE           LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     CMP4IE           LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     REPIE            LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     UPDIE            LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     CPT1IE           LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     CPT2IE           LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     SETx1IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     RTSx1IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     SETx2IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     RTSx2IE          LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     RSTIE            LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     DLYPRTIE         LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     COTIE            LL_HRTIM_TIM_IsEnabledIT \n
  *  TIMxDIER     CORDEIE          LL_HRTIM_TIM_IsEnabledIT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  mask Timer interrupts to check.
  *         For the master timer this parameter can be:
  *         @arg @ref LL_HRTIM_MDIER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_MDIER_MCMP1IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP2IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP3IE
  *         @arg @ref LL_HRTIM_MDIER_MCMP4IE
  *         @arg @ref LL_HRTIM_MDIER_MREPIE
  *         @arg @ref LL_HRTIM_MDIER_SYNCIE
  *         @arg @ref LL_HRTIM_MDIER_MUPDIE
  *
  *         For the timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_TIMDIER_ALL_IT
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMDIER_CMP1IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP2IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP3IE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP4IE
  *         @arg @ref LL_HRTIM_TIMDIER_REPIE
  *         @arg @ref LL_HRTIM_TIMDIER_UPDIE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT1IE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT2IE
  *         @arg @ref LL_HRTIM_TIMDIER_SET1IE
  *         @arg @ref LL_HRTIM_TIMDIER_RST1IE
  *         @arg @ref LL_HRTIM_TIMDIER_SET2IE
  *         @arg @ref LL_HRTIM_TIMDIER_RST2IE
  *         @arg @ref LL_HRTIM_TIMDIER_RSTIE
  *         @arg @ref LL_HRTIM_TIMDIER_DLYPRTIE
  *         @arg @ref LL_HRTIM_TIMDIER_COTIE
  *         @arg @ref LL_HRTIM_TIMDIER_CORDEIE
  * @retval State of interrupts sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledIT(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t mask)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, mask) == mask) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 1 interrupt.
  * @rmtoll
  *  IER     FLT1IE           LL_HRTIM_EnableIT_FLT1
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT1(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT1IE);
}

/**
  * @brief  Disable the fault 1 interrupt.
  * @rmtoll
  *  IER     FLT1IE           LL_HRTIM_DisableIT_FLT1
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT1(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT1IE);
}

/**
  * @brief  Indicate whether the fault 1 interrupt is enabled.
  * @rmtoll
  *  IER     FLT1IE           LL_HRTIM_IsEnabledIT_FLT1
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT1IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT1(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT1IE) == (HRTIM_IER_FLT1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 2 interrupt.
  * @rmtoll
  *  IER     FLT2IE           LL_HRTIM_EnableIT_FLT2
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT2(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT2IE);
}

/**
  * @brief  Disable the fault 2 interrupt.
  * @rmtoll
  *  IER     FLT2IE           LL_HRTIM_DisableIT_FLT2
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT2(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT2IE);
}

/**
  * @brief  Indicate whether the fault 2 interrupt is enabled.
  * @rmtoll
  *  IER     FLT2IE           LL_HRTIM_IsEnabledIT_FLT2
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT2IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT2(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT2IE) == (HRTIM_IER_FLT2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 3 interrupt.
  * @rmtoll
  *  IER     FLT3IE           LL_HRTIM_EnableIT_FLT3
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT3(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT3IE);
}

/**
  * @brief  Disable the fault 3 interrupt.
  * @rmtoll
  *  IER     FLT3IE           LL_HRTIM_DisableIT_FLT3
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT3(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT3IE);
}

/**
  * @brief  Indicate whether the fault 3 interrupt is enabled.
  * @rmtoll
  *  IER     FLT3IE           LL_HRTIM_IsEnabledIT_FLT3
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT3IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT3(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT3IE) == (HRTIM_IER_FLT3IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 4 interrupt.
  * @rmtoll
  *  IER     FLT4IE           LL_HRTIM_EnableIT_FLT4
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT4(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT4IE);
}

/**
  * @brief  Disable the fault 4 interrupt.
  * @rmtoll
  *  IER     FLT4IE           LL_HRTIM_DisableIT_FLT4
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT4(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT4IE);
}

/**
  * @brief  Indicate whether the fault 4 interrupt is enabled.
  * @rmtoll
  *  IER     FLT4IE           LL_HRTIM_IsEnabledIT_FLT4
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT4IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT4(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT4IE) == (HRTIM_IER_FLT4IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 5 interrupt.
  * @rmtoll
  *  IER     FLT5IE           LL_HRTIM_EnableIT_FLT5
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT5(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT5IE);
}

/**
  * @brief  Disable the fault 5 interrupt.
  * @rmtoll
  *  IER     FLT5IE           LL_HRTIM_DisableIT_FLT5
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT5(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT5IE);
}

/**
  * @brief  Indicate whether the fault 5 interrupt is enabled.
  * @rmtoll
  *  IER     FLT5IE           LL_HRTIM_IsEnabledIT_FLT5
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT5IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT5(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT5IE) == (HRTIM_IER_FLT5IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 6 interrupt.
  * @rmtoll
  *  IER     FLT6IE           LL_HRTIM_EnableIT_FLT6
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT6(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT6IE);
}

/**
  * @brief  Disable the fault 6 interrupt.
  * @rmtoll
  *  IER     FLT6IE           LL_HRTIM_DisableIT_FLT6
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT6(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT6IE);
}

/**
  * @brief  Indicate whether the fault 6 interrupt is enabled.
  * @rmtoll
  *  IER     FLT6IE           LL_HRTIM_IsEnabledIT_FLT6
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT6IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT6(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT6IE) == (HRTIM_IER_FLT6IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 7 interrupt.
  * @rmtoll
  *  IER     FLT7IE           LL_HRTIM_EnableIT_FLT7
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT7(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT7IE);
}

/**
  * @brief  Disable the fault 7 interrupt.
  * @rmtoll
  *  IER     FLT7IE           LL_HRTIM_DisableIT_FLT7
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT7(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT7IE);
}

/**
  * @brief  Indicate whether the fault 7 interrupt is enabled.
  * @rmtoll
  *  IER     FLT7IE           LL_HRTIM_IsEnabledIT_FLT7
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT7IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT7(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT7IE) == (HRTIM_IER_FLT7IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the fault 8 interrupt.
  * @rmtoll
  *  IER     FLT8IE           LL_HRTIM_EnableIT_FLT8
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_FLT8(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT8IE);
}

/**
  * @brief  Disable the fault 8 interrupt.
  * @rmtoll
  *  IER     FLT8IE           LL_HRTIM_DisableIT_FLT8
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_FLT8(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT8IE);
}

/**
  * @brief  Indicate whether the fault 8 interrupt is enabled.
  * @rmtoll
  *  IER     FLT8IE           LL_HRTIM_IsEnabledIT_FLT8
  * @param  hrtimx High Resolution Timer instance
  * @retval State of FLT8IE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_FLT8(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_FLT8IE) == (HRTIM_IER_FLT8IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the system fault interrupt.
  * @rmtoll
  *  IER     SYSFLTIE           LL_HRTIM_EnableIT_SYSFLT
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_SYSFLT(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_SYSFLTIE);
}

/**
  * @brief  Disable the system fault interrupt.
  * @rmtoll
  *  IER     SYSFLTIE           LL_HRTIM_DisableIT_SYSFLT
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_SYSFLT(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_SYSFLTIE);
}

/**
  * @brief  Indicate whether the system fault interrupt is enabled.
  * @rmtoll
  *  IER     SYSFLTIE           LL_HRTIM_IsEnabledIT_SYSFLT
  * @param  hrtimx High Resolution Timer instance
  * @retval State of SYSFLTIE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_SYSFLT(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_SYSFLTIE) == (HRTIM_IER_SYSFLTIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the DLL ready interrupt.
  * @rmtoll
  *  IER     DLLRDYIE           LL_HRTIM_EnableIT_DLLRDY
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_DLLRDY(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_DLLRDYIE);
}

/**
  * @brief  Disable the DLL ready interrupt.
  * @rmtoll
  *  IER     DLLRDYIE           LL_HRTIM_DisableIT_DLLRDY
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_DLLRDY(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_DLLRDYIE);
}

/**
  * @brief  Indicate whether the DLL ready interrupt is enabled.
  * @rmtoll
  *  IER     DLLRDYIE           LL_HRTIM_IsEnabledIT_DLLRDY
  * @param  hrtimx High Resolution Timer instance
  * @retval State of DLLRDYIE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_DLLRDY(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_DLLRDYIE) == (HRTIM_IER_DLLRDYIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the burst mode period interrupt.
  * @rmtoll
  *  IER     BMPERIE           LL_HRTIM_EnableIT_BMPER
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_BMPER(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_BMPERIE);
}

/**
  * @brief  Disable the burst mode period interrupt.
  * @rmtoll
  *  IER     BMPERIE           LL_HRTIM_DisableIT_BMPER
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_BMPER(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_BMPERIE);
}

/**
  * @brief  Indicate whether the burst mode period interrupt is enabled.
  * @rmtoll
  *  IER     BMPERIE           LL_HRTIM_IsEnabledIT_BMPER
  * @param  hrtimx High Resolution Timer instance
  * @retval State of BMPERIE bit in HRTIM_IER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_BMPER(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sCommonRegs.IER, HRTIM_IER_BMPERIE) == (HRTIM_IER_BMPERIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the synchronization input interrupt.
  * @rmtoll
  *  MDIER     SYNCIE           LL_HRTIM_EnableIT_SYNC
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_SYNC(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sMasterRegs.MDIER, HRTIM_MDIER_SYNCIE);
}

/**
  * @brief  Disable the synchronization input interrupt.
  * @rmtoll
  *  MDIER     SYNCIE           LL_HRTIM_DisableIT_SYNC
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_SYNC(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sMasterRegs.MDIER, HRTIM_MDIER_SYNCIE);
}

/**
  * @brief  Indicate whether the synchronization input interrupt is enabled.
  * @rmtoll
  *  MDIER     SYNCIE           LL_HRTIM_IsEnabledIT_SYNC
  * @param  hrtimx High Resolution Timer instance
  * @retval State of SYNCIE bit in HRTIM_MDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_SYNC(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sMasterRegs.MDIER, HRTIM_MDIER_SYNCIE) == (HRTIM_MDIER_SYNCIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the update interrupt for a given timer.
  * @rmtoll
  *  MDIER        MUPDIE           LL_HRTIM_EnableIT_UPDATE \n
  *  TIMxDIER     UPDIE            LL_HRTIM_EnableIT_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MUPDIE);
}

/**
  * @brief  Disable the update interrupt for a given timer.
  * @rmtoll
  *  MDIER        MUPDIE           LL_HRTIM_DisableIT_UPDATE \n
  *  TIMxDIER     UPDIE            LL_HRTIM_DisableIT_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MUPDIE);
}

/**
  * @brief  Indicate whether the update interrupt is enabled for a given timer.
  * @rmtoll
  *  MDIER        MUPDIE           LL_HRTIM_IsEnabledIT_UPDATE \n
  *  TIMxDIER     UPDIE            LL_HRTIM_IsEnabledIT_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MUPDIE/UPDIE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MUPDIE) == (HRTIM_MDIER_MUPDIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the repetition interrupt for a given timer.
  * @rmtoll
  *  MDIER        MREPIE           LL_HRTIM_EnableIT_REP \n
  *  TIMxDIER     REPIE            LL_HRTIM_EnableIT_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MREPIE);
}

/**
  * @brief  Disable the repetition interrupt for a given timer.
  * @rmtoll
  *  MDIER        MREPIE           LL_HRTIM_DisableIT_REP \n
  *  TIMxDIER     REPIE            LL_HRTIM_DisableIT_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MREPIE);
}

/**
  * @brief  Indicate whether the repetition interrupt is enabled for a given timer.
  * @rmtoll
  *  MDIER        MREPIE           LL_HRTIM_IsEnabledIT_REP \n
  *  TIMxDIER     REPIE            LL_HRTIM_IsEnabledIT_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MREPIE/REPIE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MREPIE) == (HRTIM_MDIER_MREPIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 1 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP1IE           LL_HRTIM_EnableIT_CMP1 \n
  *  TIMxDIER     CMP1IE            LL_HRTIM_EnableIT_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP1IE);
}

/**
  * @brief  Disable the compare 1 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP1IE           LL_HRTIM_DisableIT_CMP1 \n
  *  TIMxDIER     CMP1IE            LL_HRTIM_DisableIT_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP1IE);
}

/**
  * @brief  Indicate whether the compare 1 interrupt is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP1IE           LL_HRTIM_IsEnabledIT_CMP1 \n
  *  TIMxDIER     CMP1IE            LL_HRTIM_IsEnabledIT_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP1IE/CMP1IE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP1IE) == (HRTIM_MDIER_MCMP1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 2 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP2IE           LL_HRTIM_EnableIT_CMP2 \n
  *  TIMxDIER     CMP2IE            LL_HRTIM_EnableIT_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP2IE);
}

/**
  * @brief  Disable the compare 2 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP2IE           LL_HRTIM_DisableIT_CMP2 \n
  *  TIMxDIER     CMP2IE            LL_HRTIM_DisableIT_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP2IE);
}

/**
  * @brief  Indicate whether the compare 2 interrupt is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP2IE           LL_HRTIM_IsEnabledIT_CMP2 \n
  *  TIMxDIER     CMP2IE            LL_HRTIM_IsEnabledIT_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP2IE/CMP2IE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP2IE) == (HRTIM_MDIER_MCMP2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 3 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP3IE           LL_HRTIM_EnableIT_CMP3 \n
  *  TIMxDIER     CMP3IE            LL_HRTIM_EnableIT_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP3IE);
}

/**
  * @brief  Disable the compare 3 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP3IE           LL_HRTIM_DisableIT_CMP3 \n
  *  TIMxDIER     CMP3IE            LL_HRTIM_DisableIT_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP3IE);
}

/**
  * @brief  Indicate whether the compare 3 interrupt is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP3IE           LL_HRTIM_IsEnabledIT_CMP3 \n
  *  TIMxDIER     CMP3IE            LL_HRTIM_IsEnabledIT_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP3IE/CMP3IE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP3IE) == (HRTIM_MDIER_MCMP3IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 4 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP4IE           LL_HRTIM_EnableIT_CMP4 \n
  *  TIMxDIER     CMP4IE            LL_HRTIM_EnableIT_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP4IE);
}

/**
  * @brief  Disable the compare 4 interrupt for a given timer.
  * @rmtoll
  *  MDIER        MCMP4IE           LL_HRTIM_DisableIT_CMP4 \n
  *  TIMxDIER     CMP4IE            LL_HRTIM_DisableIT_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP4IE);
}

/**
  * @brief  Indicate whether the compare 4 interrupt is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP4IE           LL_HRTIM_IsEnabledIT_CMP4 \n
  *  TIMxDIER     CMP4IE            LL_HRTIM_IsEnabledIT_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP4IE/CMP4IE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP4IE) == (HRTIM_MDIER_MCMP4IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the capture 1 interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT1IE            LL_HRTIM_EnableIT_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_CPT1IE);
}

/**
  * @brief  Enable the capture 1 interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT1IE            LL_HRTIM_DisableIT_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_CPT1IE);
}

/**
  * @brief  Indicate whether the capture 1 interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT1IE            LL_HRTIM_IsEnabledIT_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CPT1IE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_CPT1IE) == (HRTIM_TIMxDIER_CPT1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the capture 2 interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT2IE            LL_HRTIM_EnableIT_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_CPT2IE);
}

/**
  * @brief  Enable the capture 2 interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT2IE            LL_HRTIM_DisableIT_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_CPT2IE);
}

/**
  * @brief  Indicate whether the capture 2 interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT2IE            LL_HRTIM_IsEnabledIT_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CPT2IE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_CPT2IE) == (HRTIM_TIMxDIER_CPT2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 1 set interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     SET1IE            LL_HRTIM_EnableIT_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_SET1IE);
}

/**
  * @brief  Disable the output 1 set interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     SET1IE            LL_HRTIM_DisableIT_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_SET1IE);
}

/**
  * @brief  Indicate whether the output 1 set interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     SET1IE            LL_HRTIM_IsEnabledIT_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of SET1xIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_SET1IE) == (HRTIM_TIMxDIER_SET1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 1 reset interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     RST1IE            LL_HRTIM_EnableIT_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_RST1IE);
}

/**
  * @brief  Disable the output 1 reset interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     RST1IE            LL_HRTIM_DisableIT_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_RST1IE);
}

/**
  * @brief  Indicate whether the output 1 reset interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     RST1IE            LL_HRTIM_IsEnabledIT_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RST1xIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_RST1IE) == (HRTIM_TIMxDIER_RST1IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 2 set interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     SET2IE            LL_HRTIM_EnableIT_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_SET2IE);
}

/**
  * @brief  Disable the output 2 set interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     SET2IE            LL_HRTIM_DisableIT_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_SET2IE);
}

/**
  * @brief  Indicate whether the output 2 set interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     SET2IE            LL_HRTIM_IsEnabledIT_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of SET2xIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_SET2IE) == (HRTIM_TIMxDIER_SET2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 2 reset interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     RST2IE            LL_HRTIM_EnableIT_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_RST2IE);
}

/**
  * @brief  Disable the output 2 reset interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     RST2IE            LL_HRTIM_DisableIT_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_RST2IE);
}

/**
  * @brief  Indicate whether the output 2 reset LL_HRTIM_IsEnabledIT_RST2 is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     RST2IE            LL_HRTIM_DisableIT_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RST2xIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_RST2IE) == (HRTIM_TIMxDIER_RST2IE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the reset/roll-over interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     RSTIE            LL_HRTIM_EnableIT_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_RSTIE);
}

/**
  * @brief  Disable the reset/roll-over interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     RSTIE            LL_HRTIM_DisableIT_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_RSTIE);
}

/**
  * @brief  Indicate whether the reset/roll-over interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     RSTIE            LL_HRTIM_IsEnabledIT_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RSTIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_RSTIE) == (HRTIM_TIMxDIER_RSTIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the delayed protection interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     DLYPRTIE            LL_HRTIM_EnableIT_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_DLYPRTIE);
}

/**
  * @brief  Disable the delayed protection interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     DLYPRTIE            LL_HRTIM_DisableIT_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_DLYPRTIE);
}

/**
  * @brief  Indicate whether the delayed protection interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     DLYPRTIE            LL_HRTIM_IsEnabledIT_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DLYPRTIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_DLYPRTIE) == (HRTIM_TIMxDIER_DLYPRTIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the crossbar override trigger interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     COTIE            LL_HRTIM_EnableIT_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_COTIE);
}

/**
  * @brief  Disable the crossbar override trigger interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     COTIE            LL_HRTIM_DisableIT_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_COTIE);
}

/**
  * @brief  Indicate whether the crossbar override trigger interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     COTIE            LL_HRTIM_IsEnabledIT_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of COTIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_COTIE) == (HRTIM_TIMxDIER_COTIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the crossbar override rearm delay elapsed interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     CORDEIE            LL_HRTIM_EnableIT_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableIT_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_CORDEIE);
}

/**
  * @brief  Disable the crossbar override rearm delay elapsed interrupt for a given timer.
  * @rmtoll
  *  TIMxDIER     CORDEIE            LL_HRTIM_DisableIT_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableIT_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_CORDEIE);
}

/**
  * @brief  Indicate whether the crossbar override rearm delay elapsed interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     CORDEIE            LL_HRTIM_IsEnabledIT_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CORDEIE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledIT_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_CORDEIE) == (HRTIM_TIMxDIER_CORDEIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup HRTIM_LL_EF_DMA_Management DMA_Management
  * @{
  */

/**
  * @brief  Enable timer DMA requests.
  * @rmtoll
  *  MDIER        MCMP1DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  MDIER        MCMP2DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  MDIER        MCMP3DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  MDIER        MCMP4DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  MDIER        MREPID           LL_HRTIM_TIM_EnableDMAReq \n
  *  MDIER        MSYNCDE          LL_HRTIM_TIM_EnableDMAReq \n
  *  MDIER        MUPDDE           LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     CMP1DE           LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     CMP2DE           LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     CMP3DE           LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     CMP4DE           LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     REPDE            LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     UPDDE            LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     CPT1DE           LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     CPT2DE           LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     SETx1DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     RTSx1DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     SETx2DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     RTSx2DE          LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     RSTDE            LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     DLYPRTDE         LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     COTDE            LL_HRTIM_TIM_EnableDMAReq \n
  *  TIMxDIER     CORDEDE          LL_HRTIM_TIM_EnableDMAReq
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  mask Timer DMA requests to enable.
  *         For the master timer this parameter can be:
  *         @arg @ref LL_HRTIM_MDIER_ALL_DMA
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_MDIER_MCMP1DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP2DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP3DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP4DE
  *         @arg @ref LL_HRTIM_MDIER_MREPDE
  *         @arg @ref LL_HRTIM_MDIER_SYNCDE
  *         @arg @ref LL_HRTIM_MDIER_MUPDDE
  *
  *         For the timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_TIMDIER_ALL_DMA
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMDIER_CMP1DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP2DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP3DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP4DE
  *         @arg @ref LL_HRTIM_TIMDIER_REPDE
  *         @arg @ref LL_HRTIM_TIMDIER_UPDDE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT1DE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT2DE
  *         @arg @ref LL_HRTIM_TIMDIER_SET1DE
  *         @arg @ref LL_HRTIM_TIMDIER_RST1DE
  *         @arg @ref LL_HRTIM_TIMDIER_SET2DE
  *         @arg @ref LL_HRTIM_TIMDIER_RST2DE
  *         @arg @ref LL_HRTIM_TIMDIER_RSTDE
  *         @arg @ref LL_HRTIM_TIMDIER_DLYPRTDE
  *         @arg @ref LL_HRTIM_TIMDIER_COTDE
  *         @arg @ref LL_HRTIM_TIMDIER_CORDEDE
  */
__STATIC_INLINE void LL_HRTIM_TIM_EnableDMAReq(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t mask)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, mask);
}

/**
  * @brief  Disable timer DMA requests.
  * @rmtoll
  *  MDIER        MCMP1DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  MDIER        MCMP2DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  MDIER        MCMP3DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  MDIER        MCMP4DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  MDIER        MREPID           LL_HRTIM_TIM_DisableDMAReq \n
  *  MDIER        MSYNCDE          LL_HRTIM_TIM_DisableDMAReq \n
  *  MDIER        MUPDDE           LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     CMP1DE           LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     CMP2DE           LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     CMP3DE           LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     CMP4DE           LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     REPDE            LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     UPDDE            LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     CPT1DE           LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     CPT2DE           LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     SETx1DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     RTSx1DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     SETx2DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     RTSx2DE          LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     RSTDE            LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     DLYPRTDE         LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     COTDE            LL_HRTIM_TIM_DisableDMAReq \n
  *  TIMxDIER     CORDEDE          LL_HRTIM_TIM_DisableDMAReq
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  mask Timer DMA requests to disable.
  *         For the master timer this parameter can be:
  *         @arg @ref LL_HRTIM_MDIER_ALL_DMA
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_MDIER_MCMP1DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP2DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP3DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP4DE
  *         @arg @ref LL_HRTIM_MDIER_MREPDE
  *         @arg @ref LL_HRTIM_MDIER_SYNCDE
  *         @arg @ref LL_HRTIM_MDIER_MUPDDE
  *
  *         For the timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_TIMDIER_ALL_DMA
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMDIER_CMP1DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP2DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP3DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP4DE
  *         @arg @ref LL_HRTIM_TIMDIER_REPDE
  *         @arg @ref LL_HRTIM_TIMDIER_UPDDE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT1DE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT2DE
  *         @arg @ref LL_HRTIM_TIMDIER_SET1DE
  *         @arg @ref LL_HRTIM_TIMDIER_RST1DE
  *         @arg @ref LL_HRTIM_TIMDIER_SET2DE
  *         @arg @ref LL_HRTIM_TIMDIER_RST2DE
  *         @arg @ref LL_HRTIM_TIMDIER_RSTDE
  *         @arg @ref LL_HRTIM_TIMDIER_DLYPRTDE
  *         @arg @ref LL_HRTIM_TIMDIER_COTDE
  *         @arg @ref LL_HRTIM_TIMDIER_CORDEDE
  */
__STATIC_INLINE void LL_HRTIM_TIM_DisableDMAReq(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t mask)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, mask);
}

/**
  * @brief  Check whether the specified timer DMA requests are enabled or not.
  * @rmtoll
  *  MDIER        MCMP1DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  MDIER        MCMP2DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  MDIER        MCMP3DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  MDIER        MCMP4DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  MDIER        MREPID           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  MDIER        MSYNCDE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  MDIER        MUPDDE           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     CMP1DE           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     CMP2DE           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     CMP3DE           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     CMP4DE           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     REPDE            LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     UPDDE            LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     CPT1DE           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     CPT2DE           LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     SETx1DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     RTSx1DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     SETx2DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     RTSx2DE          LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     RSTDE            LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     DLYPRTDE         LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     COTDE            LL_HRTIM_TIM_IsEnabledDMAReq \n
  *  TIMxDIER     CORDEDE          LL_HRTIM_TIM_IsEnabledDMAReq
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @param  mask Timer DMA requests to check.
  *         For the master timer this parameter can be:
  *         @arg @ref LL_HRTIM_MDIER_ALL_DMA
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_MDIER_MCMP1DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP2DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP3DE
  *         @arg @ref LL_HRTIM_MDIER_MCMP4DE
  *         @arg @ref LL_HRTIM_MDIER_MREPDE
  *         @arg @ref LL_HRTIM_MDIER_SYNCDE
  *         @arg @ref LL_HRTIM_MDIER_MUPDDE
  *
  *         For the timer A..F this parameter can be:
  *         @arg @ref LL_HRTIM_TIMDIER_ALL_DMA
  *         Or a combination of the following values:
  *         @arg @ref LL_HRTIM_TIMDIER_CMP1DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP2DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP3DE
  *         @arg @ref LL_HRTIM_TIMDIER_CMP4DE
  *         @arg @ref LL_HRTIM_TIMDIER_REPDE
  *         @arg @ref LL_HRTIM_TIMDIER_UPDDE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT1DE
  *         @arg @ref LL_HRTIM_TIMDIER_CPT2DE
  *         @arg @ref LL_HRTIM_TIMDIER_SET1DE
  *         @arg @ref LL_HRTIM_TIMDIER_RST1DE
  *         @arg @ref LL_HRTIM_TIMDIER_SET2DE
  *         @arg @ref LL_HRTIM_TIMDIER_RST2DE
  *         @arg @ref LL_HRTIM_TIMDIER_RSTDE
  *         @arg @ref LL_HRTIM_TIMDIER_DLYPRTDE
  *         @arg @ref LL_HRTIM_TIMDIER_COTDE
  *         @arg @ref LL_HRTIM_TIMDIER_CORDEDE
  * @retval State of interrupts sources (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_TIM_IsEnabledDMAReq(const HRTIM_TypeDef *hrtimx, uint32_t timer, uint32_t mask)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, mask) == mask) ? 1UL : 0UL);
}

/**
  * @brief  Enable the synchronization input DMA request.
  * @rmtoll
  *  MDIER     SYNCDE            LL_HRTIM_EnableDMAReq_SYNC
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_SYNC(HRTIM_TypeDef *hrtimx)
{
  STM32_SET_BIT(hrtimx->sMasterRegs.MDIER, HRTIM_MDIER_SYNCDE);
}

/**
  * @brief  Disable the synchronization input DMA request.
  * @rmtoll
  *  MDIER     SYNCDE            LL_HRTIM_DisableDMAReq_SYNC
  * @param  hrtimx High Resolution Timer instance
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_SYNC(HRTIM_TypeDef *hrtimx)
{
  STM32_CLEAR_BIT(hrtimx->sMasterRegs.MDIER, HRTIM_MDIER_SYNCDE);
}

/**
  * @brief  Indicate whether the synchronization input DMA request is enabled.
  * @rmtoll
  *  MDIER     SYNCDE            LL_HRTIM_IsEnabledDMAReq_SYNC
  * @param  hrtimx High Resolution Timer instance
  * @retval State of SYNCDE bit in HRTIM_MDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_SYNC(const HRTIM_TypeDef *hrtimx)
{
  return ((STM32_READ_BIT(hrtimx->sMasterRegs.MDIER, HRTIM_MDIER_SYNCDE) == (HRTIM_MDIER_SYNCDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the update DMA request for a given timer.
  * @rmtoll
  *  MDIER        MUPDDE            LL_HRTIM_EnableDMAReq_UPDATE \n
  *  TIMxDIER     UPDDE             LL_HRTIM_EnableDMAReq_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MUPDDE);
}

/**
  * @brief  Disable the update DMA request for a given timer.
  * @rmtoll
  *  MDIER        MUPDDE            LL_HRTIM_DisableDMAReq_UPDATE \n
  *  TIMxDIER     UPDDE             LL_HRTIM_DisableDMAReq_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MUPDDE);
}

/**
  * @brief  Indicate whether the update DMA request is enabled for a given timer.
  * @rmtoll
  *  MDIER        MUPDDE            LL_HRTIM_IsEnabledDMAReq_UPDATE \n
  *  TIMxDIER     UPDDE             LL_HRTIM_IsEnabledDMAReq_UPDATE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MUPDDE/UPDDE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_UPDATE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MUPDDE) == (HRTIM_MDIER_MUPDDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the repetition DMA request for a given timer.
  * @rmtoll
  *  MDIER        MREPDE            LL_HRTIM_EnableDMAReq_REP \n
  *  TIMxDIER     REPDE             LL_HRTIM_EnableDMAReq_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MREPDE);
}

/**
  * @brief  Disable the repetition DMA request for a given timer.
  * @rmtoll
  *  MDIER        MREPDE            LL_HRTIM_DisableDMAReq_REP \n
  *  TIMxDIER     REPDE             LL_HRTIM_DisableDMAReq_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MREPDE);
}

/**
  * @brief  Indicate whether the repetition DMA request is enabled for a given timer.
  * @rmtoll
  *  MDIER        MREPDE            LL_HRTIM_IsEnabledDMAReq_REP \n
  *  TIMxDIER     REPDE             LL_HRTIM_IsEnabledDMAReq_REP
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MREPDE/REPDE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_REP(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MREPDE) == (HRTIM_MDIER_MREPDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 1 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP1DE            LL_HRTIM_EnableDMAReq_CMP1 \n
  *  TIMxDIER     CMP1DE             LL_HRTIM_EnableDMAReq_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP1DE);
}

/**
  * @brief  Disable the compare 1 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP1DE            LL_HRTIM_DisableDMAReq_CMP1 \n
  *  TIMxDIER     CMP1DE             LL_HRTIM_DisableDMAReq_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP1DE);
}

/**
  * @brief  Indicate whether the compare 1 DMA request is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP1DE            LL_HRTIM_IsEnabledDMAReq_CMP1 \n
  *  TIMxDIER     CMP1DE             LL_HRTIM_IsEnabledDMAReq_CMP1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP1DE/CMP1DE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_CMP1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP1DE) == (HRTIM_MDIER_MCMP1DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 2 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP2DE            LL_HRTIM_EnableDMAReq_CMP2 \n
  *  TIMxDIER     CMP2DE             LL_HRTIM_EnableDMAReq_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP2DE);
}

/**
  * @brief  Disable the compare 2 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP2DE            LL_HRTIM_DisableDMAReq_CMP2 \n
  *  TIMxDIER     CMP2DE             LL_HRTIM_DisableDMAReq_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP2DE);
}

/**
  * @brief  Indicate whether the compare 2 DMA request is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP2DE            LL_HRTIM_IsEnabledDMAReq_CMP2 \n
  *  TIMxDIER     CMP2DE             LL_HRTIM_IsEnabledDMAReq_CMP2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP2DE/CMP2DE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_CMP2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP2DE) == (HRTIM_MDIER_MCMP2DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 3 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP3DE            LL_HRTIM_EnableDMAReq_CMP3 \n
  *  TIMxDIER     CMP3DE             LL_HRTIM_EnableDMAReq_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP3DE);
}

/**
  * @brief  Disable the compare 3 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP3DE            LL_HRTIM_DisableDMAReq_CMP3 \n
  *  TIMxDIER     CMP3DE             LL_HRTIM_DisableDMAReq_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP3DE);
}

/**
  * @brief  Indicate whether the compare 3 DMA request is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP3DE            LL_HRTIM_IsEnabledDMAReq_CMP3 \n
  *  TIMxDIER     CMP3DE             LL_HRTIM_IsEnabledDMAReq_CMP3
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP3DE/CMP3DE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_CMP3(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP3DE) == (HRTIM_MDIER_MCMP3DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the compare 4 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP4DE            LL_HRTIM_EnableDMAReq_CMP4 \n
  *  TIMxDIER     CMP4DE             LL_HRTIM_EnableDMAReq_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_MDIER_MCMP4DE);
}

/**
  * @brief  Disable the compare 4 DMA request for a given timer.
  * @rmtoll
  *  MDIER        MCMP4DE            LL_HRTIM_DisableDMAReq_CMP4 \n
  *  TIMxDIER     CMP4DE             LL_HRTIM_DisableDMAReq_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_MDIER_MCMP4DE);
}

/**
  * @brief  Indicate whether the compare 4 DMA request is enabled for a given timer.
  * @rmtoll
  *  MDIER        MCMP4DE            LL_HRTIM_IsEnabledDMAReq_CMP4 \n
  *  TIMxDIER     CMP4DE             LL_HRTIM_IsEnabledDMAReq_CMP4
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_MASTER
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of MCMP4DE/CMP4DE bit in HRTIM_MDIER/HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_CMP4(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_MDIER_MCMP4DE) == (HRTIM_MDIER_MCMP4DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the capture 1 DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT1DE             LL_HRTIM_EnableDMAReq_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_CPT1DE);
}

/**
  * @brief  Disable the capture 1 DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT1DE             LL_HRTIM_DisableDMAReq_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_CPT1DE);
}

/**
  * @brief  Indicate whether the capture 1 DMA request is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT1DE             LL_HRTIM_IsEnabledDMAReq_CPT1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CPT1DE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_CPT1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_CPT1DE) == (HRTIM_TIMxDIER_CPT1DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the capture 2 DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT2DE             LL_HRTIM_EnableDMAReq_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_CPT2DE);
}

/**
  * @brief  Disable the capture 2 DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT2DE             LL_HRTIM_DisableDMAReq_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_CPT2DE);
}

/**
  * @brief  Indicate whether the capture 2 DMA request is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     CPT2DE             LL_HRTIM_IsEnabledDMAReq_CPT2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CPT2DE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_CPT2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_CPT2DE) == (HRTIM_TIMxDIER_CPT2DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 1 set  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     SET1DE             LL_HRTIM_EnableDMAReq_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_SET1DE);
}

/**
  * @brief  Disable the output 1 set  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     SET1DE             LL_HRTIM_DisableDMAReq_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_SET1DE);
}

/**
  * @brief  Indicate whether the output 1 set  DMA request is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     SET1DE             LL_HRTIM_IsEnabledDMAReq_SET1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of SET1xDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_SET1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_SET1DE) == (HRTIM_TIMxDIER_SET1DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 1 reset  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     RST1DE             LL_HRTIM_EnableDMAReq_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_RST1DE);
}

/**
  * @brief  Disable the output 1 reset  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     RST1DE             LL_HRTIM_DisableDMAReq_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_RST1DE);
}

/**
  * @brief  Indicate whether the output 1 reset interrupt is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     RST1DE             LL_HRTIM_IsEnabledDMAReq_RST1
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RST1xDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_RST1(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_RST1DE) == (HRTIM_TIMxDIER_RST1DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 2 set  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     SET2DE             LL_HRTIM_EnableDMAReq_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_SET2DE);
}

/**
  * @brief  Disable the output 2 set  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     SET2DE             LL_HRTIM_DisableDMAReq_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_SET2DE);
}

/**
  * @brief  Indicate whether the output 2 set  DMA request is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     SET2DE             LL_HRTIM_IsEnabledDMAReq_SET2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of SET2xDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_SET2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_SET2DE) == (HRTIM_TIMxDIER_SET2DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the output 2 reset  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     RST2DE             LL_HRTIM_EnableDMAReq_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_RST2DE);
}

/**
  * @brief  Disable the output 2 reset  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     RST2DE             LL_HRTIM_DisableDMAReq_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_RST2DE);
}

/**
  * @brief  Indicate whether the output 2 reset  DMA request is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     RST2DE             LL_HRTIM_IsEnabledDMAReq_RST2
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RST2xDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_RST2(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_RST2DE) == (HRTIM_TIMxDIER_RST2DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the reset/roll-over DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     RSTDE             LL_HRTIM_EnableDMAReq_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_RSTDE);
}

/**
  * @brief  Disable the reset/roll-over DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     RSTDE             LL_HRTIM_DisableDMAReq_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_RSTDE);
}

/**
  * @brief  Indicate whether the reset/roll-over DMA request is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     RSTDE             LL_HRTIM_IsEnabledDMAReq_RST
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of RSTDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_RST(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_RSTDE) == (HRTIM_TIMxDIER_RSTDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the delayed protection DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     DLYPRTDE             LL_HRTIM_EnableDMAReq_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_DLYPRTDE);
}

/**
  * @brief  Disable the delayed protection DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     DLYPRTDE             LL_HRTIM_DisableDMAReq_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_DLYPRTDE);
}

/**
  * @brief  Indicate whether the delayed protection DMA request is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     DLYPRTDE             LL_HRTIM_IsEnabledDMAReq_DLYPRT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of DLYPRTDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_DLYPRT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_DLYPRTDE) == (HRTIM_TIMxDIER_DLYPRTDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the crossbar override trigger  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     COTDE             LL_HRTIM_EnableDMAReq_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_COTDE);
}

/**
  * @brief  Disable the crossbar override trigger DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     COTDE             LL_HRTIM_DisableDMAReq_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_COTDE);
}

/**
  * @brief  Indicate whether the crossbar override trigger is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     COTDE             LL_HRTIM_IsEnabledDMAReq_COT
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of COTxDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_COT(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_COTDE) == (HRTIM_TIMxDIER_COTDE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the crossbar override rearm delay elapsed  DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     CORDEDE             LL_HRTIM_EnableDMAReq_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_EnableDMAReq_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_SET_BIT(*preg, HRTIM_TIMxDIER_CORDEDE);
}

/**
  * @brief  Disable the crossbar override rearm delay elapsed DMA request for a given timer.
  * @rmtoll
  *  TIMxDIER     CORDEDE             LL_HRTIM_DisableDMAReq_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  */
__STATIC_INLINE void LL_HRTIM_DisableDMAReq_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                       LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));
  STM32_CLEAR_BIT(*preg, HRTIM_TIMxDIER_CORDEDE);
}

/**
  * @brief  Indicate whether the crossbar override rearm delay elapsed is enabled for a given timer.
  * @rmtoll
  *  TIMxDIER     CORDEDE             LL_HRTIM_IsEnabledDMAReq_CORDE
  * @param  hrtimx High Resolution Timer instance
  * @param  timer This parameter can be one of the following values:
  *         @arg @ref LL_HRTIM_TIMA
  *         @arg @ref LL_HRTIM_TIMB
  *         @arg @ref LL_HRTIM_TIMC
  *         @arg @ref LL_HRTIM_TIMD
  *         @arg @ref LL_HRTIM_TIME
  *         @arg @ref LL_HRTIM_TIMF
  * @retval State of CORDExDE bit in HRTIM_TIMxDIER register (1 or 0).
  */
__STATIC_INLINE uint32_t LL_HRTIM_IsEnabledDMAReq_CORDE(const HRTIM_TypeDef *hrtimx, uint32_t timer)
{
  uint32_t itim = (uint8_t)(STM32_POSITION_VAL(timer) - HRTIM_MCR_MCEN_Pos);
  const __IOM uint32_t *preg = (__IOM uint32_t *)((uint32_t)((uint32_t)(&hrtimx->sMasterRegs.MDIER) +
                                                             LL_HRTIM_REG_OFFSET_TAB_TIMER[itim]));

  return ((STM32_READ_BIT(*preg, HRTIM_TIMxDIER_CORDEDE) == (HRTIM_TIMxDIER_CORDEDE)) ? 1UL : 0UL);
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

#endif /* HRTIM1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_LL_HRTIM_H */
