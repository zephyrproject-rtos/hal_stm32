/**
  ******************************************************************************
  * @file    stm32mp2xx_hal_rif.h
  * @author  MCD Application Team
  * @brief   Header file of RIF HAL module.
  ******************************************************************************
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_HAL_RIF_H
#define STM32MP2xx_HAL_RIF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal_def.h"


/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */

/** @addtogroup RIF
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RIF_Exported_Types RIF Exported Types
  * @{
  */
typedef struct
{
  uint32_t PeriphId;
  uint32_t SecEnable;
  uint32_t PrivEnable;
  uint32_t CidEnable;
  uint32_t SemEnable;
  uint32_t Scid;
  uint32_t SemWl;
  uint32_t LockEnable;
} RIF_Periph_Desc;

#if defined(LPSRAM1_BASE) && defined(LPSRAM2_BASE) && defined(LPSRAM3_BASE)
typedef struct
{
  uint32_t Instance;
  uint32_t SubRegId;
  uint32_t SecEnable;
  uint32_t PrivEnable;
  uint32_t SubRegEnable;
  uint32_t Srcid;
  uint32_t SubRegStart;
  uint32_t SubRegLength;
  uint32_t LockEnable;
} RIF_MemRisal_Desc;

#endif /* LPSRAM1_BASE && LPSRAM2_BASE && LPSRAM3_BASE */
typedef struct
{
  uint32_t TDcid;
  uint32_t DAPcid;
} RIF_RIMC_TrustedDesc;

typedef struct
{
  uint32_t MasterId;
  uint32_t SecEnable;
  uint32_t PrivEnable;
  uint32_t CidEnable;
  uint32_t Mcid;
} RIF_RIMC_MasterDesc;

typedef struct
{
  uint32_t Instance;
  uint32_t SecAccessEnable;
  uint32_t PageSecEnable;
  uint32_t PagePrivEnable;
  uint32_t Cid;
  uint32_t CidPageEnable;
  uint32_t C2PagePrivEnable;
  uint32_t CidPagePrivEnable;
  uint32_t CidPageReadEnable;
  uint32_t CidPageWriteEnable;
  uint32_t DccidPageEnable;
  uint32_t Dccid;
  uint32_t PageLockEnable;
} RIF_MemRisab_Desc;

typedef struct
{
  uint32_t Instance;
  uint32_t RegEnable;
  uint32_t RegSecEnable;
  uint32_t RegEncEnable;
  uint32_t CidRegPriv;
  uint32_t CidRegRead;
  uint32_t CidRegWrite;
  uint32_t RegAddress;
  uint32_t RegSize;
} RIF_MemRisafReg_Desc;

typedef struct
{
  uint32_t Instance;
  uint32_t SubRegId;
  uint32_t SubRegEnable;
  uint32_t SubRegSecEnable;
  uint32_t SubRegPrivEnable;
  uint32_t SubRegReadEnable;
  uint32_t SubRegWriteEnable;
  uint32_t SubRegDCidEnable;
  uint32_t SubRegDccid;
  uint32_t SubRegSrcid;
  uint32_t SubRegAddress;
  uint32_t SubRegSize;
  uint32_t SubRegLockEnable;
} RIF_MemRisafSubReg_Desc;

typedef struct
{
  uint32_t Instance;
  uint32_t Key0;
  uint32_t Key1;
  uint32_t Key2;
  uint32_t Key3;
} RIF_MemRisafEncKey_Desc;
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/

/** @defgroup RIF_Private_Constants RIF Private Constants
  * @{
  */

/**
  * @brief  RIF structure definitions for IP identifier parameter (PeriphId)
  *         used in HAL_RISC_ConfigPeriphAttributes and
  *         HAL_RISC_GetConfigPeriphAttributes functions and also in all
  *         HAL_IAC related functions bitmap:
  *         bits[31:28] Field "register". Define the register an IP belongs to.
  *                     Each bit is dedicated to a single register.
  *         bit[5]      Field "all Ips". If this bit is set then the PeriphId
  *                     targets all Ips within register.
  *         bits[4:0]   Field "bit position". Define the bit position within
  *                     the register dedicated to the IP, value from 0 to 31.
  */

#define RIF_PERIPH_REG_Pos             (28U)
#define RIF_PERIPH_REG_Msk             (0xFUL << RIF_PERIPH_REG_Pos)      /*0xF0000000*/
#define RIF_PERIPH_REG0                (0x0UL << RIF_PERIPH_REG_Pos)      /*0x00000000*/
#define RIF_PERIPH_REG1                (0x1UL << RIF_PERIPH_REG_Pos)      /*0x10000000*/
#define RIF_PERIPH_REG2                (0x2UL << RIF_PERIPH_REG_Pos)      /*0x20000000*/
#define RIF_PERIPH_REG3                (0x3UL << RIF_PERIPH_REG_Pos)      /*0x30000000*/
#define RIF_PERIPH_REG4                (0x4UL << RIF_PERIPH_REG_Pos)      /*0x40000000*/
#define RIF_PERIPH_REG5                (0x5UL << RIF_PERIPH_REG_Pos)      /*0x50000000*/
#define RIF_PERIPH_ALLIP_Pos           (5U)
#define RIF_PERIPH_ALLIP_Msk           (0x1UL << RIF_PERIPH_ALLIP_Pos)    /*0x00000020*/
#define RIF_PERIPH_BITPOS_Pos          (0U)
#define RIF_PERIPH_BITPOS_Msk          (0x1FUL << RIF_PERIPH_BITPOS_Pos)  /*0x0000001F*/

/**
  * @brief RIF attribute mask and position definition
  */
#define RIF_ATTRIBUTE_SEC_Pos          (0U)
#define RIF_ATTRIBUTE_SEC_Msk          (0x1U << RIF_ATTRIBUTE_SEC_Pos)
#define RIF_ATTRIBUTE_PRIV_Pos         (1U)
#define RIF_ATTRIBUTE_PRIV_Msk         (0x1U << RIF_ATTRIBUTE_PRIV_Pos)

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RIF_Exported_Constants RIF Exported Constants
  * @{
  */

/* Definitions for RIF register values and constants */
#if defined (STM32MP25xxxx)|| defined(STM32MP21xxxx) || defined(STM32MP23xxxx)
#define RIF_PERIPH_REG_MAX             (6U)
#define RIF_COMP_MAX                   (8U)
#define RIF_CID_MAX                    (7U)
#define RIF_PAGE_MAX                   (32U)
#define RIF_BLOCK_MAX                  (8U)
#define RIF_MCID_MAX                   (15U)
#define RIF_REGION_MAX                 (15U)
#define RIF_SUBREGION_MAX              (2U)
#define RIF_KEY_REG_MAX                (4U)
#define RISAF1_BASE_REGION_MAX         (4U)
#define RISAF2_BASE_REGION_MAX         (4U)
#define RISAF4_BASE_REGION_MAX         (15U)
#define RISAF5_BASE_REGION_MAX         (2U)
#define RISAF1_WATERMARK_MAX           (256U)
#define RISAF2_WATERMARK_MAX           (4096U)
#define RISAF4_WATERMARK_MAX           (4096U)
#define RISAF5_WATERMARK_MAX           (4096U)
#define RIF_REG_ALL_Msk                (0xFFFFFFFFUL)
#define RISC_PERIPH_REG0_ALL_Msk       (0xFFFFFFFFUL)
#if defined(USE_UART4)
#define RISC_PERIPH_REG1_ALL_Msk       (0xBFDFFFFBUL)
#else
#define RISC_PERIPH_REG1_ALL_Msk       (0xBFDFFFFFUL)
#endif /* defined(USE_UART4) */
#define RISC_PERIPH_REG2_ALL_Msk       (0xF7D3FDFCUL)
#define RISC_PERIPH_REG3_ALL_Msk       (0x0FFDFDFFUL)
#define RISC_PERIPH_REG4_ALL_Msk       (0x00000000UL)
#define RISC_PERIPH_REG5_ALL_Msk       (0x00000000UL)
#endif /* defined (STM32MP25xxxx) || defined(STM32MP21xxxx) || defined(STM32MP23xxxx) */

/** @defgroup RIF_Attribute RIF Attribute
  *           bitmap: bit0 : Sec Attr (0 = Ns, 1 = Sec)
  *                   bit1 : PrivAttr (0 = NonPriv, 1 = Priv)
  * @{
  */
#define RIF_ATTRIBUTE_SEC              RIF_ATTRIBUTE_SEC_Msk
#define RIF_ATTRIBUTE_NSEC             (0U)
#define RIF_ATTRIBUTE_PRIV             RIF_ATTRIBUTE_PRIV_Msk
#define RIF_ATTRIBUTE_NPRIV            (0U)

/**
  * @}
  */


/** @defgroup RIF_Peripheral_Identification RIF Peripheral Identification
  *           user-oriented definition for each IP identifier parameter (PeriphId)
  *           used in HAL_RISC_ConfigPeriphAttributes and HAL_RISC_GetConfigPeriphAttributes
  *           functions and also in all HAL_IAC relative functions.
  * @note     user can also select all IPs using specific define
  * @note     that two maximum values are also defined here:
  *           - max number of securable AHB/APB peripherals or masters (used in
  *           RISC sub-block)
  *           - max number of securable and TrustZone-aware AHB/APB peripherals
  *           or masters (used in IAC sub-block)
  * @{
  */
#define RIF_PERIPH_TIM1                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC0_Pos)
#define RIF_PERIPH_TIM2                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC1_Pos)
#define RIF_PERIPH_TIM3                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC2_Pos)
#define RIF_PERIPH_TIM4                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC3_Pos)
#define RIF_PERIPH_TIM5                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC4_Pos)
#define RIF_PERIPH_TIM6                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC5_Pos)
#define RIF_PERIPH_TIM7                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC6_Pos)
#define RIF_PERIPH_TIM8                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC7_Pos)
#define RIF_PERIPH_TIM10               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC8_Pos)
#define RIF_PERIPH_TIM11               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC9_Pos)
#define RIF_PERIPH_TIM12               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC10_Pos)
#define RIF_PERIPH_TIM13               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC11_Pos)
#define RIF_PERIPH_TIM14               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC12_Pos)
#define RIF_PERIPH_TIM15               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC13_Pos)
#define RIF_PERIPH_TIM16               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC14_Pos)
#define RIF_PERIPH_TIM17               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC15_Pos)
#if defined(TIM20)
#define RIF_PERIPH_TIM20               (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC16_Pos)
#endif /* TIM20 */
#define RIF_PERIPH_LPTIM1              (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC17_Pos)
#define RIF_PERIPH_LPTIM2              (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC18_Pos)
#define RIF_PERIPH_LPTIM3              (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC19_Pos)
#define RIF_PERIPH_LPTIM4              (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC20_Pos)
#define RIF_PERIPH_LPTIM5              (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC21_Pos)
#define RIF_PERIPH_SPI1                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC22_Pos)
#define RIF_PERIPH_SPI2                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC23_Pos)
#define RIF_PERIPH_SPI3                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC24_Pos)
#define RIF_PERIPH_SPI4                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC25_Pos)
#define RIF_PERIPH_SPI5                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC26_Pos)
#if defined(SPI6)
#define RIF_PERIPH_SPI6                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC27_Pos)
#endif /* SPI6 */
#if defined(SPI7)
#define RIF_PERIPH_SPI7                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC28_Pos)
#endif /* SPI7 */
#define RIF_PERIPH_SPI8                (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC29_Pos)
#define RIF_PERIPH_SPDIFRX             (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC30_Pos)
#define RIF_PERIPH_USART1              (RIF_PERIPH_REG0 | RISC_SECCFGR0_SEC31_Pos)

#define RIF_PERIPH_USART2              (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC32_Pos)
#define RIF_PERIPH_USART3              (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC33_Pos)
#define RIF_PERIPH_UART4               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC34_Pos)
#define RIF_PERIPH_UART5               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC35_Pos)
#define RIF_PERIPH_USART6              (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC36_Pos)
#define RIF_PERIPH_UART7               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC37_Pos)
#if defined(UART8)
#define RIF_PERIPH_UART8               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC38_Pos)
#endif /* UART8 */
#if defined(UART9)
#define RIF_PERIPH_UART9               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC39_Pos)
#endif /* UART9 */
#define RIF_PERIPH_LPUART1             (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC40_Pos)
#define RIF_PERIPH_I2C1                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC41_Pos)
#define RIF_PERIPH_I2C2                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC42_Pos)
#if defined(I2C3)
#define RIF_PERIPH_I2C3                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC43_Pos)
#endif /* I2C3 */
#if defined(I2C4)
#define RIF_PERIPH_I2C4                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC44_Pos)
#endif /* I2C4 */
#if defined(I2C5)
#define RIF_PERIPH_I2C5                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC45_Pos)
#endif /* I2C5 */
#if defined(I2C6)
#define RIF_PERIPH_I2C6                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC46_Pos)
#endif /* I2C6 */
#define RIF_PERIPH_I2C7                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC47_Pos)
#define RIF_PERIPH_I2C8                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC48_Pos)
#define RIF_PERIPH_SAI1                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC49_Pos)
#define RIF_PERIPH_SAI2                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC50_Pos)
#define RIF_PERIPH_SAI3                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC51_Pos)
#define RIF_PERIPH_SAI4                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC52_Pos)
#define RIF_PERIPH_RES53               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC53_Pos)
#define RIF_PERIPH_MDF1                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC54_Pos)
#if defined(ADF1)
#define RIF_PERIPH_ADF1                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC55_Pos)
#endif
#define RIF_PERIPH_FDCAN               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC56_Pos)
#define RIF_PERIPH_HDP                 (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC57_Pos)
#define RIF_PERIPH_ADC12               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC58_Pos)
#define RIF_PERIPH_ADC3                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC59_Pos)
#define RIF_PERIPH_ETH1                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC60_Pos)
#define RIF_PERIPH_ETH2                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC61_Pos)
#define RIF_PERIPH_RES62               (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC62_Pos)
#define RIF_PERIPH_USBH                (RIF_PERIPH_REG1 | RISC_SECCFGR1_SEC63_Pos)

#define RIF_PERIPH_RES64               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC64_Pos)
#define RIF_PERIPH_RES65               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC65_Pos)
#define RIF_PERIPH_USB3DR              (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC66_Pos)
#define RIF_PERIPH_COMBOPHY            (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC67_Pos)
#define RIF_PERIPH_PCIE                (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC68_Pos)
#define RIF_PERIPH_UCPD1               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC69_Pos)
#define RIF_PERIPH_ETHSW_DEIP          (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC70_Pos)
#define RIF_PERIPH_ETHSW_ACM           (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC71_Pos)
#define RIF_PERIPH_ETHSW_ACM_MSG       (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC72_Pos)
#define RIF_PERIPH_STGEN               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC73_Pos)
#define RIF_PERIPH_OCTOSPI1            (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC74_Pos)
#define RIF_PERIPH_OCTOSPI2            (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC75_Pos)
#define RIF_PERIPH_SDMMC1              (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC76_Pos)
#define RIF_PERIPH_SDMMC2              (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC77_Pos)
#define RIF_PERIPH_SDMMC3              (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC78_Pos)
#if defined(GPU)
#define RIF_PERIPH_GPU                 (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC79_Pos)
#endif /* GPU */
#define RIF_PERIPH_LTDC_CMN            (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC80_Pos)
#define RIF_PERIPH_DSI_CMN             (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC81_Pos)
#define RIF_PERIPH_RES82               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC82_Pos)
#define RIF_PERIPH_RES83               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC83_Pos)
#define RIF_PERIPH_LDITX               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC84_Pos)
#define RIF_PERIPH_RES85               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC85_Pos)
#define RIF_PERIPH_CSI2HOST            (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC86_Pos)
#define RIF_PERIPH_DCMIPP              (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC87_Pos)
#define RIF_PERIPH_DCMI_PSSI           (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC88_Pos)
#if defined(VDEC)
#define RIF_PERIPH_VDEC                (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC89_Pos)
#endif /* VDEC */
#if defined(VENC)
#define RIF_PERIPH_VENC                (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC90_Pos)
#endif /* VENC */
#define RIF_PERIPH_RES91               (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC91_Pos)
#define RIF_PERIPH_RNG                 (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC92_Pos)
#define RIF_PERIPH_PKA                 (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC93_Pos)
#define RIF_PERIPH_SAES                (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC94_Pos)
#define RIF_PERIPH_HASH                (RIF_PERIPH_REG2 | RISC_SECCFGR2_SEC95_Pos)

#define RIF_PERIPH_CRYP1               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC96_Pos)
#define RIF_PERIPH_CRYP2               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC97_Pos)
#define RIF_PERIPH_IWDG1               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC98_Pos)
#define RIF_PERIPH_IWDG2               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC99_Pos)
#define RIF_PERIPH_IWDG3               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC100_Pos)
#define RIF_PERIPH_IWDG4               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC101_Pos)
#define RIF_PERIPH_IWDG5               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC102_Pos)
#define RIF_PERIPH_WWDG1               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC103_Pos)
#define RIF_PERIPH_WWDG2               (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC104_Pos)
#define RIF_PERIPH_RES105              (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC105_Pos)
#define RIF_PERIPH_VREFBUF             (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC106_Pos)
#define RIF_PERIPH_DTS                 (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC107_Pos)
#define RIF_PERIPH_RAMCFG              (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC108_Pos)
#define RIF_PERIPH_CRC                 (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC109_Pos)
#define RIF_PERIPH_SERC                (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC110_Pos)
#define RIF_PERIPH_OCTOSPIM            (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC111_Pos)
#define RIF_PERIPH_GICV2M              (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC112_Pos)
#define RIF_PERIPH_RES113              (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC113_Pos)
#define RIF_PERIPH_I3C1                (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC114_Pos)
#define RIF_PERIPH_I3C2                (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC115_Pos)
#if defined(I3C3)
#define RIF_PERIPH_I3C3                (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC116_Pos)
#endif /* I3C3 */
#define RIF_PERIPH_I3C4                (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC117_Pos)
#define RIF_PERIPH_ICACHE_DCACHE       (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC118_Pos)
#define RIF_PERIPH_LTDC_L1L2           (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC119_Pos)
#define RIF_PERIPH_LTDC_L3             (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC120_Pos)
#define RIF_PERIPH_LTDC_ROT            (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC121_Pos)
#define RIF_PERIPH_DSI_TRIG            (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC122_Pos)
#define RIF_PERIPH_DSI_RD              (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC123_Pos)
#define RIF_PERIPH_RES124              (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC124_Pos)
#define RIF_PERIPH_OTFDEC1             (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC125_Pos)
#define RIF_PERIPH_OTFDEC2             (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC126_Pos)
#define RIF_PERIPH_IAC                 (RIF_PERIPH_REG3 | RISC_SECCFGR3_SEC127_Pos)

#define RIF_PERIPH_RISAB1              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC128_Pos)
#define RIF_PERIPH_RISAB2              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC129_Pos)
#define RIF_PERIPH_RISAB3              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC130_Pos)
#if defined(RISAB4)
#define RIF_PERIPH_RISAB4              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC131_Pos)
#endif /* RISAB4 */
#define RIF_PERIPH_RISAB5              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC132_Pos)
#if defined(RISAB6)
#define RIF_PERIPH_RISAB6              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC133_Pos)
#endif /* RISAB6 */
#define RIF_PERIPH_RISAF1              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC134_Pos)
#define RIF_PERIPH_RISAF2              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC135_Pos)
#define RIF_PERIPH_RISAF3              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC136_Pos)
#define RIF_PERIPH_RISAF4              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC137_Pos)
#if defined(RISAF5)
#define RIF_PERIPH_RISAF5              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC138_Pos)
#endif /* RISAF5 */
#if defined(LPSRAM1_BASE)
#define RIF_PERIPH_RISAL1              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC139_Pos)
#endif /* LPSRAM1 */
#if defined(LPSRAM2_BASE)
#define RIF_PERIPH_RISAL2              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC140_Pos)
#endif /*LPSRAM2*/
#if defined(LPSRAM3_BASE)
#define RIF_PERIPH_RISAL3              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC141_Pos)
#endif /* LPSRAM3 */
#define RIF_PERIPH_RES142              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC142_Pos)
#define RIF_PERIPH_RES143              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC143_Pos)
#define RIF_PERIPH_IPCC1               (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC144_Pos)
#define RIF_PERIPH_IPCC2               (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC145_Pos)
#define RIF_PERIPH_HSEM                (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC146_Pos)
#define RIF_PERIPH_HPDMA1              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC147_Pos)
#define RIF_PERIPH_HPDMA2              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC148_Pos)
#define RIF_PERIPH_HPDMA3              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC149_Pos)
#define RIF_PERIPH_LPDMA               (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC150_Pos)
#define RIF_PERIPH_RTC                 (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC151_Pos)
#define RIF_PERIPH_TAMP                (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC152_Pos)
#define RIF_PERIPH_EXTI1               (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC153_Pos)
#define RIF_PERIPH_EXTI2               (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC154_Pos)
#define RIF_PERIPH_PWR                 (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC155_Pos)
#define RIF_PERIPH_RCC                 (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC156_Pos)
#define RIF_PERIPH_A35SSC              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC157_Pos)
#define RIF_PERIPH_RISC_RIMC           (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC158_Pos)
#define RIF_PERIPH_SYSCFG              (RIF_PERIPH_REG4 | RISC_SECCFGR4_SEC159_Pos)

#define RIF_PERIPH_GPIOA               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC160_Pos)
#define RIF_PERIPH_GPIOB               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC161_Pos)
#define RIF_PERIPH_GPIOC               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC162_Pos)
#define RIF_PERIPH_GPIOD               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC163_Pos)
#define RIF_PERIPH_GPIOE               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC164_Pos)
#define RIF_PERIPH_GPIOF               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC165_Pos)
#define RIF_PERIPH_GPIOG               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC166_Pos)
#define RIF_PERIPH_GPIOH               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC167_Pos)
#define RIF_PERIPH_GPIOI               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC168_Pos)
#if defined (GPIOJ)
#define RIF_PERIPH_GPIOJ               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC169_Pos)
#endif /* GPIOJ */
#if defined (GPIOK)
#define RIF_PERIPH_GPIOK               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC170_Pos)
#endif /* GPIOI */
#define RIF_PERIPH_GPIOZ               (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC171_Pos)
#define RIF_PERIPH_RES172              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC172_Pos)
#define RIF_PERIPH_RES173              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC173_Pos)
#define RIF_PERIPH_DDRCRTL             (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC174_Pos)
#define RIF_PERIPH_DDRPHYC             (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC175_Pos)
#define RIF_PERIPH_FMC                 (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC176_Pos)
#define RIF_PERIPH_BSEC                (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC177_Pos)
#define RIF_PERIPH_RES178              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC178_Pos)
#define RIF_PERIPH_RES179              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC179_Pos)
#define RIF_PERIPH_RES180              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC180_Pos)
#define RIF_PERIPH_RES181              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC181_Pos)
#define RIF_PERIPH_RES182              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC182_Pos)
#define RIF_PERIPH_RES183              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC183_Pos)
#define RIF_PERIPH_RES184              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC184_Pos)
#define RIF_PERIPH_RES185              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC185_Pos)
#define RIF_PERIPH_RES186              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC186_Pos)
#define RIF_PERIPH_RES187              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC187_Pos)
#define RIF_PERIPH_RES188              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC188_Pos)
#define RIF_PERIPH_RES189              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC189_Pos)
#define RIF_PERIPH_RES190              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC190_Pos)
#define RIF_PERIPH_RES191              (RIF_PERIPH_REG5 | RISC_SECCFGR5_SEC191_Pos)

#define RIF_NB_PERIPH_MAX              (RIF_GET_ARRAY_INDEX(RIF_PERIPH_OTFDEC2) + 1)
#define RIF_NB_PERIPH_LAST             (RIF_GET_ARRAY_INDEX(RIF_PERIPH_RES191) + 1U)

#define RIF_PERIPH_ALL                 (RIF_PERIPH_ALLIP_Msk)

#if defined(LPSRAM1_BASE)
#define RISAL1                         (RISC_BASE+0x900U)
#endif /* LPSRAM1 */
#if defined(LPSRAM2_BASE)
#define RISAL2                         (RISC_BASE+0x910U)
#endif /* LPSRAM2 */
#if defined(LPSRAM3_BASE)
#define RISAL3                         (RISC_BASE+0x920U)
#endif /* LPSRAM3 */

#define RIF_SYSRAMLOW                  ((uint32_t)RISAB1)
#define RIF_SYSRAMHIGH                 ((uint32_t)RISAB2)
#define RIF_SRAM1                      ((uint32_t)RISAB3)
#if defined(RISAB4)
#define RIF_SRAM2                      ((uint32_t)RISAB4)
#endif /* RISAB4 */
#define RIF_RETRAM                     ((uint32_t)RISAB5)
#define RIF_VDERAM                     ((uint32_t)RISAB6)
#define RIF_BCKRAM                     ((uint32_t)RISAF1)
#define RIF_OCTOSPI12                  ((uint32_t)RISAF2)
#define RIF_DDR                        ((uint32_t)RISAF4)
#if defined(RISAF5)
#define RIF_PCIE                       ((uint32_t)RISAF5)
#endif /* RISAF5 */
#if defined(LPSRAM1_BASE)
#define RIF_LPSRAM1                    ((uint32_t)RISAL1)
#endif /* LPSRAM1_BASE */
#if defined(LPSRAM2_BASE)
#define RIF_LPSRAM2                    ((uint32_t)RISAL2)
#endif /* LPSRAM2_BASE */
#if defined(LPSRAM3_BASE)
#define RIF_LPSRAM3                    ((uint32_t)RISAL3)
#endif /* LPSRAM3_BASE */

/** @defgroup RIF_Master_Identification RIF Master Identification
  * @{
  */
/* Master Fixed values */
#define RIF_MCID_CPU1                  (0x01U)
#define RIF_MCID_CPU2                  (0x02U)
#define RIF_MCID_CPU3                  (0x03U)

/* Master CID index */
#define RIF_MCID_TRACE                 (0U)
#define RIF_MCID_SDMMC1                (1U)
#define RIF_MCID_SDMMC2                (2U)
#define RIF_MCID_SDMMC3                (3U)
#define RIF_MCID_USB3DR                (4U)
#define RIF_MCID_USBH                  (5U)
#define RIF_MCID_ETH1                  (6U)
#define RIF_MCID_ETH2                  (7U)
#define RIF_MCID_PCIE                  (8U)
#define RIF_MCID_GPU                   (9U)
#define RIF_MCID_DCMIPP                (10U)
#define RIF_MCID_LTDC_L1_L2            (11U)
#define RIF_MCID_LTDC_L3               (12U)
#define RIF_MCID_LTDC_ROT              (13U)
#define RIF_MCID_VDEC                  (14U)
#define RIF_MCID_VENC                  (15U)

/* DAPCID specific value (highest level of debug access) */
#define DAPCID_MASTER                  (0x07U)
/**
  * @}
  */

/**
  * @}
  */

/* RIF user-oriented definition  */
#define RIF_HAL_ERROR                  ((uint32_t)-1)

/* PERIPH user-oriented definition  */
#define RIF_PERIPH_LOCK_OFF            (0U)
#define RIF_PERIPH_LOCK_ON             (1U)

#if defined(RIF_LPSRAM1) && defined(RIF_LPSRAM2) && defined(RIF_LPSRAM3)
/* RISAL user-oriented definitions */
#define RIF_RISAL_MEM_SUBREGA          (0U)
#define RIF_RISAL_MEM_SUBREGB          (1U)
#define RIF_RISAL_MEM_GRANULARITY      (8U)

#endif /* RIF_LPSRAM1 && RIF_LPSRAM2 && RIF_LPSRAM3 */
/* RIMC user-oriented definition  */
#define RIF_RIMC_LOCK_OFF              (0U)
#define RIF_RIMC_LOCK_ON               (1U)

/* RISAB user-oriented definitions */
#define RIF_RISAB_LOCK_OFF             (0U)
#define RIF_RISAB_LOCK_ON              (1U)

/* RISAF user-oriented definitions */
#define RIF_RISAF_LOCK_OFF             (0U)
#define RIF_RISAF_LOCK_ON              (1U)
#define RIF_RISAF_MEM_SUBREGA          (0U)
#define RIF_RISAF_MEM_SUBREGB          (1U)

/** @defgroup IAC_Flag RIF IAC flag values
  * @{
  */

/* user-oriented definitions for HAL_IAC_GetFlag() flag parameter */
#define IAC_NO_ILA_EVENT               (0U)
#define IAC_ILA_EVENT_PENDING          (1U)

/* user-oriented definitions for HAL_IAC_GetErrorStatus() flag parameter */
#define IAC_COMP_NO_ERROR              (0U)
#define IAC_COMP_ERROR                 (1U)
#define IAC_SEC_NO_ERROR               (0U)
#define IAC_SEC_ERROR                  (1U)
#define IAC_PRIV_NO_ERROR              (0U)
#define IAC_PRIV_ERROR                 (1U)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup RIF_Exported_Functions
  * @{
  */
#if defined(CORE_CM33) || defined(CORE_CA35)
/** @addtogroup RIF_Exported_Functions_Group1
  * @brief    RISC configuration functions
  * @{
  */
#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
HAL_StatusTypeDef HAL_RISC_ConfigPeriphAttributes(RIF_Periph_Desc *PeriphAttributes);
void HAL_RIF_PeriphGLock();
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */
HAL_StatusTypeDef HAL_RISC_GetConfigPeriphAttributes(uint32_t PeriphId, RIF_Periph_Desc *PeriphAttributes);
uint32_t HAL_RIF_GetPeriphGLock(void);

#if defined(RIF_LPSRAM1) && defined(RIF_LPSRAM2) && defined(RIF_LPSRAM3)
/**
  * @}
  */

/** @addtogroup RIF_Exported_Functions_Group2
  * @brief    RISAL configuration functions
  * @{
  */
#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
HAL_StatusTypeDef HAL_RISAL_ConfigMemAttributes(RIF_MemRisal_Desc *MemAttributes);
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */
HAL_StatusTypeDef HAL_RISAL_GetConfigMemAttributes(uint32_t Instance, uint32_t SubRegId, \
                                                   RIF_MemRisal_Desc *MemAttributes);

#endif /* RIF_LPSRAM1 && RIF_LPSRAM2 && RIF_LPSRAM3 */
/**
  * @}
  */

/** @addtogroup RIF_Exported_Functions_Group3
  * @brief    RIMC functions
  * @{
  */

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
HAL_StatusTypeDef HAL_RIMC_ConfigTrustedAttributes(RIF_RIMC_TrustedDesc *Attributes);
HAL_StatusTypeDef HAL_RIMC_ConfigMasterAttributes(RIF_RIMC_MasterDesc *Attributes);
void HAL_RIMC_GLock();
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */
HAL_StatusTypeDef HAL_RIMC_GetConfigTrustedAttributes(RIF_RIMC_TrustedDesc *Attributes);
HAL_StatusTypeDef HAL_RIMC_GetConfigMasterAttributes(uint32_t MasterId, RIF_RIMC_MasterDesc *Attributes);
uint32_t HAL_RIMC_GetGLock(void);

/**
  * @}
  */

/** @addtogroup RIF_Exported_Functions_Group4
  * @brief    RISAB functions
  * @{
  */

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
HAL_StatusTypeDef HAL_RISAB_ConfigMemAttributes(uint32_t PageId, RIF_MemRisab_Desc *MemAttributes);
void HAL_RISAB_MemGLock(uint32_t Instance);
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */
HAL_StatusTypeDef HAL_RISAB_GetConfigMemAttributes(uint32_t Instance, uint32_t PageId, \
                                                   uint32_t Cid, RIF_MemRisab_Desc *MemAttributes);
uint32_t HAL_RISAB_GetMemGLock(uint32_t Instance);

/**
  * @}
  */

/** @addtogroup RIF_Exported_Functions_Group5
  * @brief    RISAF functions
  * @{
  */

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
HAL_StatusTypeDef HAL_RISAF_ConfigMemRegionAttributes(uint32_t RegionId, RIF_MemRisafReg_Desc *MemAttributes);
HAL_StatusTypeDef HAL_RISAF_ConfigMemSubRegionAttributes(uint32_t RegionId, RIF_MemRisafSubReg_Desc *MemAttributes);
HAL_StatusTypeDef HAL_RISAF_ConfigMemEncryptAttributes(RIF_MemRisafEncKey_Desc *MemAttributes);
void HAL_RISAF_MemGLock(uint32_t Instance);
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */
HAL_StatusTypeDef HAL_RISAF_GetConfigMemRegionAttributes(uint32_t Instance, uint32_t RegionId, \
                                                         RIF_MemRisafReg_Desc *MemAttributes);
HAL_StatusTypeDef HAL_RISAF_GetConfigMemSubRegionAttributes(uint32_t Instance, uint32_t RegionId, \
                                                            uint32_t SubRegionId, \
                                                            RIF_MemRisafSubReg_Desc *MemAttributes);
uint32_t HAL_RISAF_GetMemGLock(uint32_t Instance);

/**
  * @}
  */

/** @addtogroup RIF_Exported_Functions_Group6
  * @brief    IAC functions
  * @{
  */

HAL_StatusTypeDef HAL_IAC_DisableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_IAC_EnableIT(uint32_t PeriphId);
HAL_StatusTypeDef HAL_IAC_GetFlag(uint32_t PeriphId, uint32_t *Flag);
HAL_StatusTypeDef HAL_IAC_ClearFlag(uint32_t PeriphId);

/**
  * @}
  */

/** @addtogroup RIF_Exported_Functions_Group7
  * @brief    IRQ related Functions
  * @{
  */

void HAL_RIF_IRQHandler(void);
void HAL_IAC_Callback(uint32_t PeriphId);
#endif /* defined(CORE_CM33) || defined(CORE_CA35) */

/**
  * @}
  */

/**
  * @}
  */

/* Private macro ------------------------------------------------------------*/
/** @defgroup RIF_Private_Macros RIF Private Macros
  * @{
  */
/**
  * @brief  RIF private macros usable to retrieve information to access register
  *         for a specific PeriphId
  */
#define RIF_GET_REG_INDEX(periphid)        (((periphid) & RIF_PERIPH_REG_Msk) >> RIF_PERIPH_REG_Pos)
#define RIF_GET_PERIPH_POS(periphid)       ((periphid) & (RIF_PERIPH_BITPOS_Msk))

/**
  * @brief  RIF private macro to get array index of a specific PeriphId
  *         in case of RIF_PERIPH_ALLIP_Msk usage in the two following functions:
  *         HAL_RISC_ConfigPeriphAttributes and HAL_RISC_GetConfigPeriphAttributes
  */
#define RIF_GET_ARRAY_INDEX(periphid)      (((RIF_GET_REG_INDEX(periphid))*32U) + (RIF_GET_PERIPH_POS(periphid)))


/**
  * @brief  RIF private macros to check function input parameters
  */
#define IS_RIF_ATTRIBUTE(__ATTRIBUTES__)   (((__ATTRIBUTES__) & ~(RIF_ATTRIBUTE_SEC | RIF_ATTRIBUTE_PRIV)) == 0x00u)

#define IS_RIF_PERIPHERAL(__PERIPHERAL__)  (((((__PERIPHERAL__) & ~\
                                               (RIF_PERIPH_REG_Msk | RIF_PERIPH_BITPOS_Msk)) == 0x00u) && \
                                             ((RIF_GET_ARRAY_INDEX(__PERIPHERAL__) < RIF_NB_PERIPH_LAST))) || \
                                            ((__PERIPHERAL__) == RIF_PERIPH_ALLIP_Msk))

#if defined(RIF_LPSRAM1) && defined(RIF_LPSRAM2) && defined(RIF_LPSRAM3)
#define IS_RISAL_INSTANCE(instance) \
  ( ( (uint32_t)(instance) == (uint32_t)(RIF_LPSRAM1) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_LPSRAM2) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_LPSRAM3) ) )

#define IS_RISAL_SUBREG(subreg) \
  ( ( (uint32_t)(subreg) == (uint32_t)(RIF_RISAL_MEM_SUBREGA) ) || \
    ( (uint32_t)(subreg) == (uint32_t)(RIF_RISAL_MEM_SUBREGB) ) )

#endif /* RIF_LPSRAM1 && RIF_LPSRAM2 && RIF_LPSRAM3 */
#define IS_RIMC_MASTERID(cid) \
  ( ( (uint32_t)(cid) == RIF_MCID_TRACE ) || \
    ( (uint32_t)(cid) == RIF_MCID_SDMMC1 ) || \
    ( (uint32_t)(cid) == RIF_MCID_SDMMC2 ) || \
    ( (uint32_t)(cid) == RIF_MCID_SDMMC3 ) || \
    ( (uint32_t)(cid) == RIF_MCID_USB3DR ) || \
    ( (uint32_t)(cid) == RIF_MCID_USBH ) || \
    ( (uint32_t)(cid) == RIF_MCID_ETH1 ) || \
    ( (uint32_t)(cid) == RIF_MCID_ETH2 ) || \
    ( (uint32_t)(cid) == RIF_MCID_PCIE ) || \
    ( (uint32_t)(cid) == RIF_MCID_GPU ) || \
    ( (uint32_t)(cid) == RIF_MCID_DCMIPP ) || \
    ( (uint32_t)(cid) == RIF_MCID_LTDC_L1_L2 ) || \
    ( (uint32_t)(cid) == RIF_MCID_LTDC_L3 ) || \
    ( (uint32_t)(cid) == RIF_MCID_LTDC_ROT ) || \
    ( (uint32_t)(cid) == RIF_MCID_VDEC ) || \
    ( (uint32_t)(cid) == RIF_MCID_VENC ) )

#define IS_RIMC_TDCID(cid) \
  ( ( (uint32_t)(cid) == RIMC_CR_TDCID0 ) || \
    ( (uint32_t)(cid) == RIMC_CR_TDCID1 ) || \
    ( (uint32_t)(cid) == RIMC_CR_TDCID2 ) || \
    ( (uint32_t)(cid) == RIMC_CR_TDCID3 ) || \
    ( (uint32_t)(cid) == RIMC_CR_TDCID4 ) || \
    ( (uint32_t)(cid) == RIMC_CR_TDCID5 ) || \
    ( (uint32_t)(cid) == RIMC_CR_TDCID6 ) || \
    ( (uint32_t)(cid) == RIMC_CR_TDCID7 ) )

#define IS_RIMC_DAPCID(cid) \
  ( ( (uint32_t)(cid) == RIMC_CR_DAPCID0 ) || \
    ( (uint32_t)(cid) == RIMC_CR_DAPCID1 ) || \
    ( (uint32_t)(cid) == RIMC_CR_DAPCID2 ) || \
    ( (uint32_t)(cid) == RIMC_CR_DAPCID3 ) || \
    ( (uint32_t)(cid) == RIMC_CR_DAPCID4 ) || \
    ( (uint32_t)(cid) == RIMC_CR_DAPCID5 ) || \
    ( (uint32_t)(cid) == RIMC_CR_DAPCID6 ) || \
    ( (uint32_t)(cid) == RIMC_CR_DAPCID7 ) )

#define IS_RIMC_MASTERCID(cid) \
  ( ( (uint32_t)(cid) == RIMC_ATTR_MCID0 ) || \
    ( (uint32_t)(cid) == RIMC_ATTR_MCID1 ) || \
    ( (uint32_t)(cid) == RIMC_ATTR_MCID2 ) || \
    ( (uint32_t)(cid) == RIMC_ATTR_MCID3 ) || \
    ( (uint32_t)(cid) == RIMC_ATTR_MCID4 ) || \
    ( (uint32_t)(cid) == RIMC_ATTR_MCID5 ) || \
    ( (uint32_t)(cid) == RIMC_ATTR_MCID6 ) || \
    ( (uint32_t)(cid) == RIMC_ATTR_MCID7 ) )

#if defined(RIF_SRAM2)
#define IS_RISAB_INSTANCE(instance) \
  ( ( (uint32_t)(instance) == (uint32_t)(RIF_SYSRAMLOW) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_SYSRAMHIGH) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_SRAM1) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_SRAM2) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_RETRAM) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_VDERAM) ) )
#else
#define IS_RISAB_INSTANCE(instance) \
  ( ( (uint32_t)(instance) == (uint32_t)(RIF_SYSRAMLOW) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_SYSRAMHIGH) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_SRAM1) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_RETRAM) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_VDERAM) ) )
#endif /* RIF_SRAM2 */

#define IS_RISAB_CID(cid) \
  ( ( (uint32_t)(cid) == RIF_MCID_CPU1 ) || \
    ( (uint32_t)(cid) == RIF_MCID_CPU2 ) || \
    ( (uint32_t)(cid) == RIF_MCID_CPU3 ) )

#define IS_RISAB_PAGEID(pageid) \
  ( ( (uint32_t)(pageid) >= 0U ) && \
    ( (uint32_t)(pageid) < RIF_PAGE_MAX ) )

#define IS_RISAB_DCCID(cid) \
  ( ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC0 ) || \
    ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC1 ) || \
    ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC2 ) || \
    ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC3 ) || \
    ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC4 ) || \
    ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC5 ) || \
    ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC6 ) || \
    ( (uint32_t)(cid) == RISAB_PGCIDCFGR_DCCIDC7 ) )

#if defined(RIF_PCIE)
#define IS_RISAF_INSTANCE(instance) \
  ( ( (uint32_t)(instance) == (uint32_t)(RIF_BCKRAM) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_OCTOSPI12) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_DDR) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_PCIE) ) )
#else
#define IS_RISAF_INSTANCE(instance) \
  ( ( (uint32_t)(instance) == (uint32_t)(RIF_BCKRAM) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_OCTOSPI12) ) || \
    ( (uint32_t)(instance) == (uint32_t)(RIF_DDR) ) )


#endif /* RIF_PCIE */
#define IS_RISAF_REGIONID(regionid) \
  ( ( (uint32_t)(regionid) >= 0U ) && \
    ( (uint32_t)(regionid) < RIF_REGION_MAX ) )

#define IS_RISAF_SUBREGID(subreg) \
  ( ( (uint32_t)(subreg) == (uint32_t)(RIF_RISAF_MEM_SUBREGA) ) || \
    ( (uint32_t)(subreg) == (uint32_t)(RIF_RISAF_MEM_SUBREGB) ) )

#define IS_RISAF_CIDPRIV(cid) \
  ( ( (uint32_t)(cid & RISAF_REGCFGR_PRIV_Msk) == cid ) )

#define IS_RISAF_CIDREAD(cid) \
  ( ( (uint32_t)(cid & RISAF_REGCIDCFGR_RDEN_Msk) == cid ) )

#define IS_RISAF_CIDWRITE(cid) \
  ( ( (uint32_t)(cid & RISAF_REGCIDCFGR_WREN_Msk) == cid ) )

#define IS_RISAF_DCCID(cid) \
  ( ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID0 ) || \
    ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID1 ) || \
    ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID2 ) || \
    ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID3 ) || \
    ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID4 ) || \
    ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID5 ) || \
    ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID6 ) || \
    ( (uint32_t)(cid) == RISAF_REGZNESTR_DCCID7 ) )

#define IS_RISAF_SRCID(cid) \
  ( ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID0 ) || \
    ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID1 ) || \
    ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID2 ) || \
    ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID3 ) || \
    ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID4 ) || \
    ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID5 ) || \
    ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID6 ) || \
    ( (uint32_t)(cid) == RISAF_REGZCFGR_SRCID7 ) )

#if defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE)
#define SEC_SET_BIT(REG, BIT)                   SET_BIT(REG, BIT)
#define SEC_CLEAR_BIT(REG, BIT)                 CLEAR_BIT(REG, BIT)
#define SEC_READ_BIT(REG, BIT)                  READ_BIT(REG, BIT)
#define SEC_CLEAR_REG(REG)                      CLEAR_REG(REG)
#define SEC_WRITE_REG(REG, VAL)                 WRITE_REG(REG, VAL)
#define SEC_READ_REG(REG)                       READ_REG(REG)
#define SEC_MODIFY_REG(REG, CLEARMASK, SETMASK) MODIFY_REG(REG, CLEARMASK, SETMASK)
#else
#define SEC_SET_BIT(REG, BIT)
#define SEC_CLEAR_BIT(REG, BIT)
#define SEC_READ_BIT(REG, BIT)                  READ_BIT(REG, BIT)
#define SEC_CLEAR_REG(REG)
#define SEC_WRITE_REG(REG, VAL)
#define SEC_READ_REG(REG)                       READ_REG(REG)
#define SEC_MODIFY_REG(REG, CLEARMASK, SETMASK)
#endif /* defined(CORE_CA35) || defined(CORTEX_IN_SECURE_STATE) */

/**
  * @brief  RIF private macros to configure RISC
  */
#define HAL_RIF_IS_RISC_CFEN(periphid)      (SEC_READ_BIT\
                                             ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid) & 0x7FU].CIDCFGR)\
                                              , RISC_PERCIDCFGR_CFEN))
#define HAL_RIF_IS_RISC_SEMEN(periphid)     (SEC_READ_BIT\
                                             ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid) & 0x7FU].CIDCFGR)\
                                              , RISC_PERCIDCFGR_SEMEN))
#define HAL_RIF_IS_RISC_SEMMUTEX(periphid)  (READ_BIT\
                                             (RISC->PER[RIF_GET_ARRAY_INDEX(periphid) & 0x7FU].SEMCR\
                                              , RISC_PERSEMCR_SEMMUTEX))
#define HAL_RIF_IS_RISC_RLOCK(periphid)     (SEC_READ_BIT\
                                             ((RISC->RCFGLOCKR[RIF_GET_REG_INDEX(periphid)\
                                                               % (sizeof(RISC->RCFGLOCKR)/sizeof(RISC->RCFGLOCKR[0]))])\
                                              , (1UL<<RIF_GET_PERIPH_POS(periphid))))
#define HAL_RIF_IS_RISC_SEC(periphid)       (SEC_READ_BIT\
                                             ((RISC->SECCFGR[RIF_GET_REG_INDEX(periphid)\
                                                             % (sizeof(RISC->SECCFGR)/sizeof(RISC->SECCFGR[0]))])\
                                              , (1UL<<RIF_GET_PERIPH_POS(periphid))))
#define HAL_RIF_IS_RISC_PRIV(periphid)      (SEC_READ_BIT\
                                             ((RISC->PRIVCFGR[RIF_GET_REG_INDEX(periphid)\
                                                              % (sizeof(RISC->PRIVCFGR)/sizeof(RISC->PRIVCFGR[0]))])\
                                              , (1UL<<RIF_GET_PERIPH_POS(periphid))))
#define HAL_RIF_IS_RISC_GLOCK()             (SEC_READ_BIT((RISC->CR), RISC_CR_GLOCK))

#define HAL_RIF_SET_RISC_CFEN(periphid)            (SEC_SET_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_CFEN))
#define HAL_RIF_SET_RISC_SEMEN(periphid)           (SEC_SET_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_SEMEN))
#define HAL_RIF_SET_RISC_RLOCK(periphid)           (SEC_SET_BIT\
                                                    ((RISC->RCFGLOCKR[RIF_GET_REG_INDEX(periphid)])\
                                                     , 1<<RIF_GET_PERIPH_POS(periphid)))
#define HAL_RIF_SET_RISC_SEC(periphid)             (SEC_SET_BIT\
                                                    ((RISC->SECCFGR[RIF_GET_REG_INDEX(periphid)])\
                                                     , 1<<RIF_GET_PERIPH_POS(periphid)))
#define HAL_RIF_SET_RISC_PRIV(periphid)            (SEC_SET_BIT\
                                                    ((RISC->PRIVCFGR[RIF_GET_REG_INDEX(periphid)])\
                                                     , 1<<RIF_GET_PERIPH_POS(periphid)))
#define HAL_RIF_SET_RISC_GLOCK()                   (SEC_SET_BIT((RISC->CR), RISC_CR_GLOCK))

#define HAL_RIF_CLEAR_RISC_CFEN(periphid)          (SEC_CLEAR_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_CFEN))
#define HAL_RIF_CLEAR_RISC_SEMEN(periphid)         (SEC_CLEAR_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_SEMEN))
#define HAL_RIF_CLEAR_RISC_RLOCK(periphid)         (SEC_CLEAR_BIT\
                                                    ((RISC->RCFGLOCKR[RIF_GET_REG_INDEX(periphid)])\
                                                     , 1<<RIF_GET_PERIPH_POS(periphid)))
#define HAL_RIF_CLEAR_RISC_SEC(periphid)           (SEC_CLEAR_BIT\
                                                    ((RISC->SECCFGR[RIF_GET_REG_INDEX(periphid)])\
                                                     , 1<<RIF_GET_PERIPH_POS(periphid)))
#define HAL_RIF_CLEAR_RISC_PRIV(periphid)          (SEC_CLEAR_BIT\
                                                    ((RISC->PRIVCFGR[RIF_GET_REG_INDEX(periphid)])\
                                                     , 1<<RIF_GET_PERIPH_POS(periphid)))

/* SCID */
#define HAL_RIF_READ_RISC_SCID(periphid)           (SEC_READ_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)& 0x7FU].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_SCID))
#define HAL_RIF_SET_RISC_SCID(periphid,scid)       (SEC_MODIFY_REG\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_SCID_Msk, scid & RISC_PERCIDCFGR_SCID_Msk))
#define HAL_RIF_IS_RISC_SCIDCX(periphid,scid)      (HAL_RIF_READ_RISC_SCID(periphid) == scid ? 1 : 0)
#define HAL_RIF_CLEAR_RISC_SCID(periphid)          (SEC_CLEAR_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_SCID))
/* SEMWL */
#define HAL_RIF_READ_RISC_SEMWL(periphid)          (SEC_READ_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid) & 0x7FU].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_SEMWL))
#define HAL_RIF_IS_RISC_SEMWLCX(periphid,cid)      (SEC_READ_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR), cid))
#define HAL_RIF_SET_RISC_SEMWLCX(periphid,cid)     (SEC_MODIFY_REG\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid )].CIDCFGR)\
                                                     , RISC_PERCIDCFGR_SEMWL_Msk, cid & RISC_PERCIDCFGR_SEMWL_Msk))
#define HAL_RIF_RESET_RISC_SEMWLCX(periphid,cid)   (SEC_CLEAR_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].CIDCFGR), cid))
/* SEMCID */
#define HAL_RIF_READ_RISC_SEMCID(periphid)         (SEC_READ_BIT\
                                                    ((RISC->PER[RIF_GET_ARRAY_INDEX(periphid)].SEMCR)\
                                                     , RISC_PERSEMCR_SEMCID))
#define HAL_RIF_IS_RISC_SEMCIDCX(periphid,semcid)  (HAL_RIF_READ_RISC_SEMCID(periphid) == semcid  ? 1 : 0)
/* SEMMUTEX */
#define HAL_RIF_TAKE_RISC_SEM(periphid)            (SET_BIT(RISC->PER\
                                                            [RIF_GET_ARRAY_INDEX(periphid)].SEMCR\
                                                            , RISC_PERSEMCR_SEMMUTEX))
#define HAL_RIF_RELEASE_RISC_SEM(periphid)         (CLEAR_BIT(RISC->PER\
                                                              [RIF_GET_ARRAY_INDEX(periphid)].SEMCR\
                                                              , RISC_PERSEMCR_SEMMUTEX))

#if defined(RIF_LPSRAM1) && defined(RIF_LPSRAM2) && defined(RIF_LPSRAM3)
/**
  * @brief  RIF private macros to configure RISAL
  */
#define HAL_RIF_IS_RISAL1_SUBREGA_SREN()                  (SEC_READ_BIT((RISC->REG1ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_IS_RISAL1_SUBREGA_RLOCK()                 (SEC_READ_BIT((RISC->REG1ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_IS_RISAL1_SUBREGA_SEC()                   (SEC_READ_BIT((RISC->REG1ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_IS_RISAL1_SUBREGA_PRIV()                  (SEC_READ_BIT((RISC->REG1ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_IS_RISAL1_SUBREGB_SREN()                  (SEC_READ_BIT((RISC->REG1BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_IS_RISAL1_SUBREGB_RLOCK()                 (SEC_READ_BIT((RISC->REG1BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_IS_RISAL1_SUBREGB_SEC()                   (SEC_READ_BIT((RISC->REG1BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_IS_RISAL1_SUBREGB_PRIV()                  (SEC_READ_BIT((RISC->REG1BCFGR), RISC_REGCFGR_PRIV))

#define HAL_RIF_IS_RISAL2_SUBREGA_SREN()                  (SEC_READ_BIT((RISC->REG2ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_IS_RISAL2_SUBREGA_RLOCK()                 (SEC_READ_BIT((RISC->REG2ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_IS_RISAL2_SUBREGA_SEC()                   (SEC_READ_BIT((RISC->REG2ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_IS_RISAL2_SUBREGA_PRIV()                  (SEC_READ_BIT((RISC->REG2ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_IS_RISAL2_SUBREGB_SREN()                  (SEC_READ_BIT((RISC->REG2BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_IS_RISAL2_SUBREGB_RLOCK()                 (SEC_READ_BIT((RISC->REG2BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_IS_RISAL2_SUBREGB_SEC()                   (SEC_READ_BIT((RISC->REG2BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_IS_RISAL2_SUBREGB_PRIV()                  (SEC_READ_BIT((RISC->REG2BCFGR), RISC_REGCFGR_PRIV))

#define HAL_RIF_IS_RISAL3_SUBREGA_SREN()                  (SEC_READ_BIT((RISC->REG3ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_IS_RISAL3_SUBREGA_RLOCK()                 (SEC_READ_BIT((RISC->REG3ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_IS_RISAL3_SUBREGA_SEC()                   (SEC_READ_BIT((RISC->REG3ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_IS_RISAL3_SUBREGA_PRIV()                  (SEC_READ_BIT((RISC->REG3ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_IS_RISAL3_SUBREGB_SREN()                  (SEC_READ_BIT((RISC->REG3BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_IS_RISAL3_SUBREGB_RLOCK()                 (SEC_READ_BIT((RISC->REG3BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_IS_RISAL3_SUBREGB_SEC()                   (SEC_READ_BIT((RISC->REG3BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_IS_RISAL3_SUBREGB_PRIV()                  (SEC_READ_BIT((RISC->REG3BCFGR), RISC_REGCFGR_PRIV))

#define HAL_RIF_SET_RISAL1_SUBREGA_SREN()                 (SEC_SET_BIT((RISC->REG1ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_SET_RISAL1_SUBREGA_RLOCK()                (SEC_SET_BIT((RISC->REG1ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_SET_RISAL1_SUBREGA_SEC()                  (SEC_SET_BIT((RISC->REG1ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_SET_RISAL1_SUBREGA_PRIV()                 (SEC_SET_BIT((RISC->REG1ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_SET_RISAL1_SUBREGB_SREN()                 (SEC_SET_BIT((RISC->REG1BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_SET_RISAL1_SUBREGB_RLOCK()                (SEC_SET_BIT((RISC->REG1BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_SET_RISAL1_SUBREGB_SEC()                  (SEC_SET_BIT((RISC->REG1BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_SET_RISAL1_SUBREGB_PRIV()                 (SEC_SET_BIT((RISC->REG1BCFGR), RISC_REGCFGR_PRIV))

#define HAL_RIF_SET_RISAL2_SUBREGA_SREN()                 (SEC_SET_BIT((RISC->REG2ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_SET_RISAL2_SUBREGA_RLOCK()                (SEC_SET_BIT((RISC->REG2ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_SET_RISAL2_SUBREGA_SEC()                  (SEC_SET_BIT((RISC->REG2ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_SET_RISAL2_SUBREGA_PRIV()                 (SEC_SET_BIT((RISC->REG2ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_SET_RISAL2_SUBREGB_SREN()                 (SEC_SET_BIT((RISC->REG2BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_SET_RISAL2_SUBREGB_RLOCK()                (SEC_SET_BIT((RISC->REG2BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_SET_RISAL2_SUBREGB_SEC()                  (SEC_SET_BIT((RISC->REG2BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_SET_RISAL2_SUBREGB_PRIV()                 (SEC_SET_BIT((RISC->REG2BCFGR), RISC_REGCFGR_PRIV))

#define HAL_RIF_SET_RISAL3_SUBREGA_SREN()                 (SEC_SET_BIT((RISC->REG3ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_SET_RISAL3_SUBREGA_RLOCK()                (SEC_SET_BIT((RISC->REG3ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_SET_RISAL3_SUBREGA_SEC()                  (SEC_SET_BIT((RISC->REG3ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_SET_RISAL3_SUBREGA_PRIV()                 (SEC_SET_BIT((RISC->REG3ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_SET_RISAL3_SUBREGB_SREN()                 (SEC_SET_BIT((RISC->REG3BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_SET_RISAL3_SUBREGB_RLOCK()                (SEC_SET_BIT((RISC->REG3BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_SET_RISAL3_SUBREGB_SEC()                  (SEC_SET_BIT((RISC->REG3BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_SET_RISAL3_SUBREGB_PRIV()                 (SEC_SET_BIT((RISC->REG3BCFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_SET_RISAL3_SUBREGA_SUBSTART(val)          (SEC_MODIFY_REG((RISC->REG3AADDR),\
                                                                          RISC_REG3ADDR_SUBSTART_Msk,\
                                                                          val << RISC_REG3ADDR_SUBSTART_Pos))
#define HAL_RIF_SET_RISAL3_SUBREGA_SUBLENGTH(val)         (SEC_MODIFY_REG((RISC->REG3AADDR),\
                                                                          RISC_REG3ADDR_SUBLENGTH_Msk,\
                                                                          val << RISC_REG3ADDR_SUBLENGTH_Pos))
#define HAL_RIF_SET_RISAL3_SUBREGB_SUBSTART(val)          (SEC_MODIFY_REG((RISC->REG3BADDR),\
                                                                          RISC_REG3ADDR_SUBSTART_Msk,\
                                                                          val << RISC_REG3ADDR_SUBSTART_Pos))
#define HAL_RIF_SET_RISAL3_SUBREGB_SUBLENGTH(val)         (SEC_MODIFY_REG((RISC->REG3BADDR),\
                                                                          RISC_REG3ADDR_SUBLENGTH_Msk,\
                                                                          val << RISC_REG3ADDR_SUBLENGTH_Pos))

#define HAL_RIF_READ_RISAL3_SUBREGA_SUBSTART()            (SEC_READ_BIT((RISC->REG3AADDR),\
                                                                        RISC_REG3ADDR_SUBSTART_Msk)\
                                                           >> RISC_REG3ADDR_SUBSTART_Pos)
#define HAL_RIF_READ_RISAL3_SUBREGA_SUBLENGTH()           (SEC_READ_BIT((RISC->REG3AADDR),\
                                                                        RISC_REG3ADDR_SUBLENGTH_Msk)\
                                                           >> RISC_REG3ADDR_SUBLENGTH_Pos)
#define HAL_RIF_READ_RISAL3_SUBREGB_SUBSTART()            (SEC_READ_BIT((RISC->REG3BADDR),\
                                                                        RISC_REG3ADDR_SUBSTART_Msk)\
                                                           >> RISC_REG3ADDR_SUBSTART_Pos)
#define HAL_RIF_READ_RISAL3_SUBREGB_SUBLENGTH()           (SEC_READ_BIT((RISC->REG3BADDR),\
                                                                        RISC_REG3ADDR_SUBLENGTH_Msk)\
                                                           >> RISC_REG3ADDR_SUBLENGTH_Pos)

#define HAL_RIF_CLEAR_RISAL1_SUBREGA_SREN()               (SEC_CLEAR_BIT((RISC->REG1ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_CLEAR_RISAL1_SUBREGA_RLOCK()              (SEC_CLEAR_BIT((RISC->REG1ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_CLEAR_RISAL1_SUBREGA_SEC()                (SEC_CLEAR_BIT((RISC->REG1ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_CLEAR_RISAL1_SUBREGA_PRIV()               (SEC_CLEAR_BIT((RISC->REG1ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAL1_SUBREGB_SREN()               (SEC_CLEAR_BIT((RISC->REG1BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_CLEAR_RISAL1_SUBREGB_RLOCK()              (SEC_CLEAR_BIT((RISC->REG1BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_CLEAR_RISAL1_SUBREGB_SEC()                (SEC_CLEAR_BIT((RISC->REG1BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_CLEAR_RISAL1_SUBREGB_PRIV()               (SEC_CLEAR_BIT((RISC->REG1BCFGR), RISC_REGCFGR_PRIV))

#define HAL_RIF_CLEAR_RISAL2_SUBREGA_SREN()               (SEC_CLEAR_BIT((RISC->REG2ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_CLEAR_RISAL2_SUBREGA_RLOCK()              (SEC_CLEAR_BIT((RISC->REG2ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_CLEAR_RISAL2_SUBREGA_SEC()                (SEC_CLEAR_BIT((RISC->REG2ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_CLEAR_RISAL2_SUBREGA_PRIV()               (SEC_CLEAR_BIT((RISC->REG2ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAL2_SUBREGB_SREN()               (SEC_CLEAR_BIT((RISC->REG2BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_CLEAR_RISAL2_SUBREGB_RLOCK()              (SEC_CLEAR_BIT((RISC->REG2BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_CLEAR_RISAL2_SUBREGB_SEC()                (SEC_CLEAR_BIT((RISC->REG2BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_CLEAR_RISAL2_SUBREGB_PRIV()               (SEC_CLEAR_BIT((RISC->REG2BCFGR), RISC_REGCFGR_PRIV))

#define HAL_RIF_CLEAR_RISAL3_SUBREGA_SREN()               (SEC_CLEAR_BIT((RISC->REG3ACFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_CLEAR_RISAL3_SUBREGA_RLOCK()              (SEC_CLEAR_BIT((RISC->REG3ACFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_CLEAR_RISAL3_SUBREGA_SEC()                (SEC_CLEAR_BIT((RISC->REG3ACFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_CLEAR_RISAL3_SUBREGA_PRIV()               (SEC_CLEAR_BIT((RISC->REG3ACFGR), RISC_REGCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAL3_SUBREGB_SREN()               (SEC_CLEAR_BIT((RISC->REG3BCFGR), RISC_REGCFGR_SREN))
#define HAL_RIF_CLEAR_RISAL3_SUBREGB_RLOCK()              (SEC_CLEAR_BIT((RISC->REG3BCFGR), RISC_REGCFGR_RLOCK))
#define HAL_RIF_CLEAR_RISAL3_SUBREGB_SEC()                (SEC_CLEAR_BIT((RISC->REG3BCFGR), RISC_REGCFGR_SEC))
#define HAL_RIF_CLEAR_RISAL3_SUBREGB_PRIV()               (SEC_CLEAR_BIT((RISC->REG3BCFGR), RISC_REGCFGR_PRIV))

/* SRCID */
#define HAL_RIF_READ_RISAL1_SUBREGA_SRCID()               (SEC_READ_BIT((RISC->REG1ACFGR), RISC_REGCFGR_SRCID))
#define HAL_RIF_READ_RISAL1_SUBREGB_SRCID()               (SEC_READ_BIT((RISC->REG1BCFGR), RISC_REGCFGR_SRCID))
#define HAL_RIF_READ_RISAL2_SUBREGA_SRCID()               (SEC_READ_BIT((RISC->REG2ACFGR), RISC_REGCFGR_SRCID))
#define HAL_RIF_READ_RISAL2_SUBREGB_SRCID()               (SEC_READ_BIT((RISC->REG2BCFGR), RISC_REGCFGR_SRCID))
#define HAL_RIF_READ_RISAL3_SUBREGA_SRCID()               (SEC_READ_BIT((RISC->REG3ACFGR), RISC_REGCFGR_SRCID))
#define HAL_RIF_READ_RISAL3_SUBREGB_SRCID()               (SEC_READ_BIT((RISC->REG3BCFGR), RISC_REGCFGR_SRCID))
#define HAL_RIF_IS_RISAL1_SUBREGA_SRCID(srcid)            (HAL_RIF_READ_RISAL1_SUBREGA_SRCID() == srcid ? 1 : 0)
#define HAL_RIF_IS_RISAL1_SUBREGB_SRCID(srcid)            (HAL_RIF_READ_RISAL1_SUBREGB_SRCID() == srcid ? 1 : 0)
#define HAL_RIF_IS_RISAL2_SUBREGA_SRCID(srcid)            (HAL_RIF_READ_RISAL2_SUBREGA_SRCID() == srcid ? 1 : 0)
#define HAL_RIF_IS_RISAL2_SUBREGB_SRCID(srcid)            (HAL_RIF_READ_RISAL2_SUBREGB_SRCID() == srcid ? 1 : 0)
#define HAL_RIF_IS_RISAL3_SUBREGA_SRCID(srcid)            (HAL_RIF_READ_RISAL3_SUBREGA_SRCID() == srcid ? 1 : 0)
#define HAL_RIF_IS_RISAL3_SUBREGB_SRCID(srcid)            (HAL_RIF_READ_RISAL3_SUBREGB_SRCID() == srcid ? 1 : 0)
#define HAL_RIF_SET_RISAL1_SUBREGA_SRCID(srcid)           (SEC_MODIFY_REG((RISC->REG1ACFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk, srcid))
#define HAL_RIF_SET_RISAL1_SUBREGB_SRCID(srcid)           (SEC_MODIFY_REG((RISC->REG1BCFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk, srcid))
#define HAL_RIF_SET_RISAL2_SUBREGA_SRCID(srcid)           (SEC_MODIFY_REG((RISC->REG2ACFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk, srcid))
#define HAL_RIF_SET_RISAL2_SUBREGB_SRCID(srcid)           (SEC_MODIFY_REG((RISC->REG2BCFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk, srcid))
#define HAL_RIF_SET_RISAL3_SUBREGA_SRCID(srcid)           (SEC_MODIFY_REG((RISC->REG3ACFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk, srcid))
#define HAL_RIF_SET_RISAL3_SUBREGB_SRCID(srcid)           (SEC_MODIFY_REG((RISC->REG3BCFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk, srcid))
#define HAL_RIF_CLEAR_RISAL1_SUBREGA_SRCID()              (SEC_MODIFY_REG((RISC->REG1ACFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk,\
                                                                          RISC_REGCFGR_SRCID0))
#define HAL_RIF_CLEAR_RISAL1_SUBREGB_SRCID()              (SEC_MODIFY_REG((RISC->REG1BCFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk,\
                                                                          RISC_REGCFGR_SRCID0))
#define HAL_RIF_CLEAR_RISAL2_SUBREGA_SRCID()              (SEC_MODIFY_REG((RISC->REG2ACFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk,\
                                                                          RISC_REGCFGR_SRCID0))
#define HAL_RIF_CLEAR_RISAL2_SUBREGB_SRCID()              (SEC_MODIFY_REG((RISC->REG2BCFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk,\
                                                                          RISC_REGCFGR_SRCID0))
#define HAL_RIF_CLEAR_RISAL3_SUBREGA_SRCID()              (SEC_MODIFY_REG((RISC->REG3ACFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk,\
                                                                          RISC_REGCFGR_SRCID0))
#define HAL_RIF_CLEAR_RISAL3_SUBREGB_SRCID()              (SEC_MODIFY_REG((RISC->REG3BCFGR),\
                                                                          RISC_REGCFGR_SRCID_Msk,\
                                                                          RISC_REGCFGR_SRCID0))

#endif /* RIF_LPSRAM && RIF_LPSRAM2 && RIF_LPSRAM3 */
/**
  * @brief  RIF private macros to configure RIMC
  */
#define HAL_RIF_READ_RIMC_TDCID()                         (SEC_READ_BIT((RIMC->CR), RIMC_CR_TDCID))
#define HAL_RIF_READ_RIMC_DAPCID()                        (SEC_READ_BIT((RIMC->CR), RIMC_CR_DAPCID))
#define HAL_RIF_READ_RIMC_MCID(masterid)                  (SEC_READ_BIT((RIMC->ATTR[masterid]), RIMC_ATTR_MCID))
#define HAL_RIF_SET_RIMC_TDCID(val)                       (SEC_MODIFY_REG((RIMC->CR), RIMC_CR_TDCID_Msk, val))
#define HAL_RIF_SET_RIMC_DAPCID(val)                      (SEC_MODIFY_REG((RIMC->CR), RIMC_CR_DAPCID_Msk, val))
#define HAL_RIF_SET_RIMC_MCID(masterid,val)               (SEC_MODIFY_REG\
                                                           ((RIMC->ATTR[masterid]), RIMC_ATTR_MCID_Msk, val))
#define HAL_RIF_SET_RIMC_GLOCK()                          (SEC_SET_BIT((RIMC->CR), RIMC_CR_GLOCK))
#define HAL_RIF_SET_RIMC_SEC(masterid)                    (SEC_SET_BIT((RIMC->ATTR[masterid]), RIMC_ATTR_MSEC))
#define HAL_RIF_SET_RIMC_PRIV(masterid)                   (SEC_SET_BIT((RIMC->ATTR[masterid]), RIMC_ATTR_MPRIV))
#define HAL_RIF_SET_RIMC_CIDSEL(masterid)                 (SEC_SET_BIT((RIMC->ATTR[masterid]), RIMC_ATTR_CIDSEL))

#define HAL_RIF_IS_RIMC_SEC(masterid)                     (SEC_READ_BIT((RIMC->ATTR[masterid]), RIMC_ATTR_MSEC))
#define HAL_RIF_IS_RIMC_PRIV(masterid)                    (SEC_READ_BIT((RIMC->ATTR[masterid]), RIMC_ATTR_MPRIV))
#define HAL_RIF_IS_RIMC_CIDSEL(masterid)                  (SEC_READ_BIT((RIMC->ATTR[masterid]), RIMC_ATTR_CIDSEL))
#define HAL_RIF_IS_RIMC_GLOCK()                           (SEC_READ_BIT((RIMC->CR), RIMC_CR_GLOCK))
#define HAL_RIF_IS_RIMC_DDEN()                            (SEC_READ_BIT((RIMC->CR), RIMC_CR_DDEN))

#define HAL_RIF_IS_TRUSTED_DOMAIN(cpu)                    ((HAL_RIF_READ_RIMC_TDCID()) == cpu)
#define HAL_RIF_IS_DEBUG_DOMAIN(cpu)                      (HAL_RIF_IS_RIMC_DDEN() &&\
                                                           ((HAL_RIF_READ_RIMC_DAPCID()) == cpu))

/**
  * @brief  RIF private macros to configure RISAB
  */
/* INSTANCE */
#define HAL_RIF_IS_RISAB_GLOCK(Instance)                            (SEC_READ_BIT\
                                                                     ((((RISAB_TypeDef*)Instance)->CR),\
                                                                      RISAB_CR_GLOCK))
#define HAL_RIF_IS_RISAB_SRWIAD(Instance)                           (SEC_READ_BIT\
                                                                     ((((RISAB_TypeDef*)Instance)->CR),\
                                                                      RISAB_CR_SRWIAD))
/* PAGEID then BLOCKID */
#define HAL_RIF_IS_RISAB_PG_BLOCK_SEC(Instance,pageid,blockid)      (SEC_READ_BIT\
                                                                     ((((RISAB_TypeDef*)Instance)->PGSECCFGR[pageid])\
                                                                      , (1U << blockid) & RISAB_PGSECCFGR_SEC))
#define HAL_RIF_IS_RISAB_PG_BLOCK_PRIV(Instance,pageid,blockid)     (SEC_READ_BIT\
                                                                     ((((RISAB_TypeDef*)Instance)->PGPRIVCFGR[pageid])\
                                                                      , (1U << blockid) & RISAB_PGPRIVCFGR_PRIV))
#define HAL_RIF_IS_RISAB_PG_C2_BLOCK_PRIV(Instance,pageid,blockid)  (SEC_READ_BIT((\
                                                                     ((RISAB_TypeDef*)Instance)->PGC2PRIVCFGR[pageid]),\
                                                                     (1U << blockid) & RISAB_PGC2PRIVCFGR_PRIV))
/* CID then PAGEID */
#define HAL_RIF_IS_RISAB_PG_CX_PRIV(Instance,cid,pageid)    (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)(Instance))->CID[(cid)].PRIVCFGR),\
                                                              (1UL << (pageid))))
#define HAL_RIF_IS_RISAB_PG_CX_READ(Instance,cid,pageid)    (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)(Instance))->CID[(cid)].RDCFGR),\
                                                              (1UL << (pageid))))
#define HAL_RIF_IS_RISAB_PG_CX_WRITE(Instance,cid,pageid)   (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)(Instance))->CID[(cid)].WRCFGR),\
                                                              (1UL << (pageid))))
/* PAGEID */
#define HAL_RIF_IS_RISAB_PG_CFEN(Instance,pageid)           (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                              RISAB_PGCIDCFGR_CFEN))
#define HAL_RIF_IS_RISAB_PG_DCEN(Instance,pageid)           (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                              RISAB_PGCIDCFGR_DCEN))
#define HAL_RIF_IS_RISAB_PG_LOCK(Instance,pageid)           (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)(Instance))->RIFLOCKR),\
                                                              (1UL << (pageid))))

/* INSTANCE */
#define HAL_RIF_SET_RISAB_GLOCK(Instance)                                 (SEC_SET_BIT\
                                                                           ((((RISAB_TypeDef*)Instance)->CR),\
                                                                            RISAB_CR_GLOCK))
#define HAL_RIF_SET_RISAB_SRWIAD(Instance)                                (SEC_SET_BIT\
                                                                           ((((RISAB_TypeDef*)Instance)->CR),\
                                                                            RISAB_CR_SRWIAD))
#define HAL_RIF_SET_RISAB_LOCK(Instance)                                  (SEC_SET_BIT\
                                                                           ((((RISAB_TypeDef*)Instance)->RIFLOCKR),\
                                                                            RISAB_RIFLOCKR_RLOCK))
/* PAGEID then BLOCKID */
#define HAL_RIF_SET_RISAB_PG_BLOCK_SEC(Instance,pageid,blockid)     (SEC_SET_BIT(((\
                                                                     (RISAB_TypeDef*)Instance)->PGSECCFGR[pageid]),\
                                                                     ((1U << blockid) & RISAB_PGSECCFGR_SEC))
#define HAL_RIF_SET_RISAB_PG_BLOCK_PRIV(Instance,pageid,blockid)    (SEC_SET_BIT((\
                                                                     ((RISAB_TypeDef*)Instance)->PGPRIVCFGR[pageid]),\
                                                                     ((1U << blockid) & RISAB_PGPRIVCFGR_PRIV))
#define HAL_RIF_SET_RISAB_PG_C2_BLOCK_PRIV(Instance,pageid,blockid) (SEC_SET_BIT(((\
                                                                     (RISAB_TypeDef*)Instance)->PGC2PRIVCFGR[pageid]),\
                                                                     ((1U << blockid) & RISAB_PGC2PRIVCFGR_PRIV))
/* PAGEID */
#define HAL_RIF_SET_RISAB_PG_SEC(Instance,pageid)               (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGSECCFGR[pageid]),\
                                                                  RISAB_PGSECCFGR_SEC))
#define HAL_RIF_SET_RISAB_PG_PRIV(Instance,pageid)              (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGPRIVCFGR[pageid]),\
                                                                  RISAB_PGPRIVCFGR_PRIV))
#define HAL_RIF_SET_RISAB_PG_C2_PRIV(Instance,pageid)           (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGC2PRIVCFGR[pageid]),\
                                                                  RISAB_PGC2PRIVCFGR_PRIV))
#define HAL_RIF_SET_RISAB_PG_CFEN(Instance,pageid)              (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                                  RISAB_PGCIDCFGR_CFEN))
#define HAL_RIF_SET_RISAB_PG_DCEN(Instance,pageid)              (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                                  RISAB_PGCIDCFGR_DCEN))
#define HAL_RIF_SET_RISAB_PG_LOCK(Instance,pageid)              (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->RIFLOCKR),\
                                                                  (1U << pageid)))
/* CID */
#define HAL_RIF_SET_RISAB_CX_PRIV(Instance,cid)                 (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].PRIVCFGR),\
                                                                  RISAB_CIDPRIVCFGR_PPRIV))
#define HAL_RIF_SET_RISAB_CX_READ(Instance,cid)                 (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].RDCFGR),\
                                                                  RISAB_CIDRDCFGR_PRDEN))
#define HAL_RIF_SET_RISAB_CX_WRITE(Instance,cid)                (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].WRCFGR),\
                                                                  RISAB_CIDRDCFGR_PWREN))
/* CID then PAGEID */
#define HAL_RIF_SET_RISAB_PG_CX_PRIV(Instance,cid,pageid)       (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].PRIVCFGR),\
                                                                  (1U << pageid)))
#define HAL_RIF_SET_RISAB_PG_CX_READ(Instance,cid,pageid)       (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].RDCFGR),\
                                                                  (1U << pageid)))
#define HAL_RIF_SET_RISAB_PG_CX_WRITE(Instance,cid,pageid)      (SEC_SET_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].WRCFGR),\
                                                                  (1U << pageid)))

/* INSTANCE */
#define HAL_RIF_CLEAR_RISAB_SRWIAD(Instance)                          (SEC_CLEAR_BIT\
                                                                       ((((RISAB_TypeDef*)Instance)->CR),\
                                                                        RISAB_CR_SRWIAD))
#define HAL_RIF_CLEAR_RISAB_LOCK(Instance)                            (SEC_CLEAR_BIT\
                                                                       ((((RISAB_TypeDef*)Instance)->RIFLOCKR),\
                                                                        RISAB_RIFLOCKR_RLOCK))
/* PAGEID then BLOCKID */
#define HAL_RIF_CLEAR_RISAB_PG_BLOCK_SEC(Instance,pageid,blockid)     (SEC_CLEAR_BIT(((\
                                                                       (RISAB_TypeDef*)Instance)->PGSECCFGR[pageid]),\
                                                                       (1U << blockid) & RISAB_PGSECCFGR_SEC))
#define HAL_RIF_CLEAR_RISAB_PG_BLOCK_PRIV(Instance,pageid,blockid)    (SEC_CLEAR_BIT(((\
                                                                       (RISAB_TypeDef*)Instance)->PGPRIVCFGR[pageid]),\
                                                                       (1U << blockid) & RISAB_PGPRIVCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAB_PG_C2_BLOCK_PRIV(Instance,pageid,blockid) (SEC_CLEAR_BIT\
                                                                       ((((RISAB_TypeDef*)Instance)\
                                                                         ->PGC2PRIVCFGR[pageid]), \
                                                                        (1U << blockid) & RISAB_PGC2PRIVCFGR_PRIV))
/* PAGEID */
#define HAL_RIF_CLEAR_RISAB_PG_SEC(Instance,pageid)             (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGSECCFGR[pageid]),\
                                                                  RISAB_PGSECCFGR_SEC))
#define HAL_RIF_CLEAR_RISAB_PG_PRIV(Instance,pageid)            (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGPRIVCFGR[pageid]),\
                                                                  RISAB_PGPRIVCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAB_PG_C2_PRIV(Instance,pageid)         (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGC2PRIVCFGR[pageid]),\
                                                                  RISAB_PGC2PRIVCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAB_PG_CFEN(Instance,pageid)            (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                                  RISAB_PGCIDCFGR_CFEN))
#define HAL_RIF_CLEAR_RISAB_PG_DCEN(Instance,pageid)            (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                                  RISAB_PGCIDCFGR_DCEN))
#define HAL_RIF_CLEAR_RISAB_PG_LOCK(Instance,pageid)            (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->RIFLOCKR),\
                                                                  (1U << pageid)))
/* CID */
#define HAL_RIF_CLEAR_RISAB_CX_PRIV(Instance,cid)               (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].PRIVCFGR),\
                                                                  RISAB_CIDPRIVCFGR_PPRIV))
#define HAL_RIF_CLEAR_RISAB_CX_READ(Instance,cid)               (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].RDCFGR),\
                                                                  RISAB_CIDRDCFGR_PRDEN))
#define HAL_RIF_CLEAR_RISAB_CX_WRITE(Instance,cid)              (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].WRCFGR),\
                                                                  RISAB_CIDRDCFGR_PWREN))
/* CID then PAGEID */
#define HAL_RIF_CLEAR_RISAB_PG_CX_PRIV(Instance,cid,pageid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].PRIVCFGR),\
                                                                  (1U << pageid)))
#define HAL_RIF_CLEAR_RISAB_PG_CX_READ(Instance,cid,pageid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].RDCFGR),\
                                                                  (1U << pageid)))
#define HAL_RIF_CLEAR_RISAB_PG_CX_WRITE(Instance,cid,pageid)    (SEC_CLEAR_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].WRCFGR),\
                                                                  (1U << pageid)))

/* PAGEID */
#define HAL_RIF_READ_RISAB_PG_SEC(Instance,pageid)              (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGSECCFGR[pageid]),\
                                                                  RISAB_PGSECCFGR_SEC))
#define HAL_RIF_READ_RISAB_PG_PRIV(Instance,pageid)             (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGPRIVCFGR[pageid]),\
                                                                  RISAB_PGPRIVCFGR_PRIV))
#define HAL_RIF_READ_RISAB_PG_C2_PRIV(Instance,pageid)          (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->PGC2PRIVCFGR[pageid]),\
                                                                  RISAB_PGC2PRIVCFGR_PRIV))
/* CID */
#define HAL_RIF_READ_RISAB_CX_PRIV(Instance,cid)                (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].PRIVCFGR),\
                                                                  RISAB_CIDPRIVCFGR_PPRIV))
#define HAL_RIF_READ_RISAB_CX_READ(Instance,cid)                (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].RDCFGR),\
                                                                  RISAB_CIDRDCFGR_PRDEN))
#define HAL_RIF_READ_RISAB_CX_WRITE(Instance,cid)               (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].WRCFGR),\
                                                                  RISAB_CIDRDCFGR_PWREN))
/* Per CID then PAGEID */
#define HAL_RIF_READ_RISAB_PG_CX_PRIV(Instance,cid,pageid)      (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].PRIVCFGR),\
                                                                  (1U << pageid)))
#define HAL_RIF_READ_RISAB_PG_CX_READ(Instance,cid,pageid)      (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].RDCFGR),\
                                                                  (1U << pageid)))
#define HAL_RIF_READ_RISAB_PG_CX_WRITE(Instance,cid,pageid)     (SEC_READ_BIT\
                                                                 ((((RISAB_TypeDef*)Instance)->CID[cid].WRCFGR),\
                                                                  (1U << pageid)))

/* DCCID */
#define HAL_RIF_READ_RISAB_PG_DCCID(Instance,pageid)        (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                              RISAB_PGCIDCFGR_DCCID))
#define HAL_RIF_IS_RISAB_PG_DCCID(Instance,pageid,cid)      (HAL_RIF_READ_RISAB_PG_DCCID\
                                                             (Instance,pageid) == cid ? 1 : 0)
#define HAL_RIF_SET_RISAB_PG_DCCID(Instance,pageid,val)     (SEC_MODIFY_REG\
                                                             ((((RISAB_TypeDef*)Instance)->PGCIDCFGR[pageid]),\
                                                              RISAB_PGCIDCFGR_DCCID_Msk, val))

/* ILLEGAL ACCESS */
#define HAL_RIF_READ_RISAB_IASR(Instance)                   (SEC_READ_REG\
                                                             ((((RISAB_TypeDef*)Instance)->IASR)))
#define HAL_RIF_READ_RISAB_IAESR(Instance)                  (SEC_READ_REG\
                                                             ((((RISAB_TypeDef*)Instance)->IAESR)))
#define HAL_RIF_READ_RISAB_IADDR(Instance)                  (SEC_READ_REG\
                                                             ((((RISAB_TypeDef*)Instance)->IADDR)))
#define HAL_RIF_CLEAR_RISAB_IACR_CAEF(Instance)             (SEC_SET_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IACR),\
                                                              RISAB_IACR_CAEF))
#define HAL_RIF_CLEAR_RISAB_IACR_IAEF(Instance)             (SEC_SET_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IACR),\
                                                              RISAB_IACR_IAEF))
#define HAL_RIF_CLEAR_RISAB_IACR(Instance)                  (SEC_SET_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IACR),\
                                                              RISAB_IACR_CAEF|RISAB_IACR_IAEF))
#define HAL_RIF_IS_RISAB_IASR_CAEF(Instance)                (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IASR), RISAB_IASR_CAEF))
#define HAL_RIF_IS_RISAB_IASR_IAEF(Instance)                (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IASR), RISAB_IASR_IAEF))
#define HAL_RIF_IS_RISAB_IAESR_IAPRIV(Instance)             (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IAESR), RISAB_IAESR_IAPRIV))
#define HAL_RIF_IS_RISAB_IAESR_IASEC(Instance)              (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IAESR), RISAB_IAESR_IASEC))
#define HAL_RIF_IS_RISAB_IAESR_IANRW(Instance)              (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IAESR), RISAB_IAESR_IANRW))
#define HAL_RIF_READ_RISAB_IAESR_IACID(Instance)            (SEC_READ_BIT\
                                                             ((((RISAB_TypeDef*)Instance)->IAESR),\
                                                              RISAB_IAESR_IACID) >> RISAB_IAESR_IACID_Pos)

/**
  * @brief  RIF private macros to configure RISAF
  */
/* INSTANCE */
#define HAL_RIF_IS_RISAF_GLOCK(Instance)                                  (SEC_READ_BIT\
                                                                           ((((RISAF_TypeDef*)Instance)->CR),\
                                                                            RISAF_CR_GLOCK))
#define HAL_RIF_IS_RISAF_KEYRDY(Instance)                                 (SEC_READ_BIT\
                                                                           ((((RISAF_TypeDef*)Instance)->SR),\
                                                                            RISAF_SR_KEYRDY))
#define HAL_RIF_IS_RISAF_KEYVALID(Instance)                               (SEC_READ_BIT\
                                                                           ((((RISAF_TypeDef*)Instance)->SR),\
                                                                            RISAF_SR_KEYVALID))

#define HAL_RIF_SET_RISAF_GLOCK(Instance)                                 (SEC_SET_BIT\
                                                                           ((((RISAF_TypeDef*)Instance)->CR),\
                                                                            RISAF_CR_GLOCK))

#define HAL_RIF_READ_RISAF_CR(Instance)                                   (SEC_READ_REG\
                                                                           ((((RISAF_TypeDef*)Instance)->CR)))
#define HAL_RIF_READ_RISAF_SR(Instance)                                   (SEC_READ_REG\
                                                                           ((((RISAF_TypeDef*)Instance)->SR)))

/* REGIONID */
#define HAL_RIF_SET_RISAF_REG_BREN(Instance,regionid)           (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_BREN))
#define HAL_RIF_SET_RISAF_REG_SEC(Instance,regionid)            (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_SEC))
#define HAL_RIF_SET_RISAF_REG_ENC(Instance,regionid)            (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_ENC))
#define HAL_RIF_SET_RISAF_REG_CIDPRIV(Instance,regionid,cid)    (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  cid))
#define HAL_RIF_SET_RISAF_REG_CIDREAD(Instance,regionid,cid)    (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CIDCFGR),\
                                                                  cid))
#define HAL_RIF_SET_RISAF_REG_CIDWRITE(Instance,regionid,cid)   (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CIDCFGR),\
                                                                  cid))
#define HAL_RIF_SET_RISAF_REG_STARTR(Instance,regionid,addr)    (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].STARTR),\
                                                                  addr))
#define HAL_RIF_SET_RISAF_REG_ENDR(Instance,regionid,addr)      (SEC_SET_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ENDR),\
                                                                  addr))

#define HAL_RIF_CLEAR_RISAF_REG_BREN(Instance,regionid)         (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_BREN))
#define HAL_RIF_CLEAR_RISAF_REG_SEC(Instance,regionid)          (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_SEC))
#define HAL_RIF_CLEAR_RISAF_REG_ENC(Instance,regionid)          (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_ENC))
#define HAL_RIF_CLEAR_RISAF_REG_CIDPRIV(Instance,regionid,cid)  (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  cid))
#define HAL_RIF_CLEAR_RISAF_REG_CIDREAD(Instance,regionid,cid)  (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CIDCFGR),\
                                                                  cid))
#define HAL_RIF_CLEAR_RISAF_REG_CIDWRITE(Instance,regionid,cid) (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CIDCFGR),\
                                                                  cid))

#define HAL_RIF_READ_RISAF_CFGR(Instance,regionid)              (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR)))
#define HAL_RIF_READ_RISAF_STARTR(Instance,regionid)            (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].STARTR)))
#define HAL_RIF_READ_RISAF_ENDR(Instance,regionid)              (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ENDR)))
#define HAL_RIF_READ_RISAF_CIDCFGR(Instance,regionid)           (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CIDCFGR)))
#define HAL_RIF_READ_RISAF_REG_CIDPRIV(Instance,regionid)       (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_PRIV))
#define HAL_RIF_READ_RISAF_REG_CIDREAD(Instance,regionid)       (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CIDCFGR),\
                                                                  RISAF_REGCIDCFGR_RDEN))
#define HAL_RIF_READ_RISAF_REG_CIDWRITE(Instance,regionid)      (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CIDCFGR),\
                                                                  RISAF_REGCIDCFGR_WREN))

#define HAL_RIF_IS_RISAF_REG_BREN(Instance,regionid)            (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_BREN))
#define HAL_RIF_IS_RISAF_REG_SEC(Instance,regionid)             (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_SEC))
#define HAL_RIF_IS_RISAF_REG_ENC(Instance,regionid)             (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].CFGR),\
                                                                  RISAF_REGCFGR_ENC))
#define HAL_RIF_IS_RISAF_REG_CIDPRIV(Instance,regionid,cid)     ((HAL_RIF_READ_RISAF_REG_CIDPRIV\
                                                                  (Instance,regionid)&cid) == cid ? 1 : 0)
#define HAL_RIF_IS_RISAF_REG_CIDREAD(Instance,regionid,cid)     ((HAL_RIF_READ_RISAF_REG_CIDREAD\
                                                                  (Instance,regionid)&cid) == cid ? 1 : 0)
#define HAL_RIF_IS_RISAF_REG_CIDWRITE(Instance,regionid,cid)    ((HAL_RIF_READ_RISAF_REG_CIDWRITE\
                                                                  (Instance,regionid)&cid) == cid ? 1 : 0)

/* SUBREGION */
#define HAL_RIF_IS_RISAF_SUBREGA_SREN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_SREN))
#define HAL_RIF_IS_RISAF_SUBREGA_RLOCK(Instance,regionid)       (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_RLOCK))
#define HAL_RIF_IS_RISAF_SUBREGA_SEC(Instance,regionid)         (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_SEC))
#define HAL_RIF_IS_RISAF_SUBREGA_PRIV(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_PRIV))
#define HAL_RIF_IS_RISAF_SUBREGA_RDEN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_RDEN))
#define HAL_RIF_IS_RISAF_SUBREGA_WREN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_WREN))
#define HAL_RIF_IS_RISAF_SUBREGA_ENC(Instance,regionid)         (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_ENC))
#define HAL_RIF_IS_RISAF_SUBREGA_DCEN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ANESTR),\
                                                                  RISAF_REGZNESTR_DCEN))
#define HAL_RIF_IS_RISAF_SUBREGB_SREN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_SREN))
#define HAL_RIF_IS_RISAF_SUBREGB_RLOCK(Instance,regionid)       (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_RLOCK))
#define HAL_RIF_IS_RISAF_SUBREGB_SEC(Instance,regionid)         (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_SEC))
#define HAL_RIF_IS_RISAF_SUBREGB_PRIV(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_PRIV))
#define HAL_RIF_IS_RISAF_SUBREGB_RDEN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_RDEN))
#define HAL_RIF_IS_RISAF_SUBREGB_WREN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_WREN))
#define HAL_RIF_IS_RISAF_SUBREGB_ENC(Instance,regionid)         (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_ENC))
#define HAL_RIF_IS_RISAF_SUBREGB_DCEN(Instance,regionid)        (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BNESTR),\
                                                                  RISAF_REGZNESTR_DCEN))

#define HAL_RIF_SET_RISAF_SUBREGA_SREN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                   RISAF_REGZCFGR_SREN))
#define HAL_RIF_SET_RISAF_SUBREGA_RLOCK(Instance,regionid)       (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                   RISAF_REGZCFGR_RLOCK))
#define HAL_RIF_SET_RISAF_SUBREGA_SEC(Instance,regionid)         (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                   RISAF_REGZCFGR_SEC))
#define HAL_RIF_SET_RISAF_SUBREGA_PRIV(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                   RISAF_REGZCFGR_PRIV))
#define HAL_RIF_SET_RISAF_SUBREGA_RDEN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                   RISAF_REGZCFGR_RDEN))
#define HAL_RIF_SET_RISAF_SUBREGA_WREN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                   RISAF_REGZCFGR_WREN))
#define HAL_RIF_SET_RISAF_SUBREGA_DCEN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ANESTR),\
                                                                   RISAF_REGZNESTR_DCEN))
#define HAL_RIF_SET_RISAF_SUBREGA_STARTR(Instance,regionid,addr) (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].ASTARTR)\
                                                                   , addr))
#define HAL_RIF_SET_RISAF_SUBREGA_ENDR(Instance,regionid,addr)   (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].AENDR),\
                                                                   addr))
#define HAL_RIF_SET_RISAF_SUBREGB_SREN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                   RISAF_REGZCFGR_SREN))
#define HAL_RIF_SET_RISAF_SUBREGB_RLOCK(Instance,regionid)       (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                   RISAF_REGZCFGR_RLOCK))
#define HAL_RIF_SET_RISAF_SUBREGB_SEC(Instance,regionid)         (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                   RISAF_REGZCFGR_SEC))
#define HAL_RIF_SET_RISAF_SUBREGB_PRIV(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                   RISAF_REGZCFGR_PRIV))
#define HAL_RIF_SET_RISAF_SUBREGB_RDEN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                   RISAF_REGZCFGR_RDEN))
#define HAL_RIF_SET_RISAF_SUBREGB_WREN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                   RISAF_REGZCFGR_WREN))
#define HAL_RIF_SET_RISAF_SUBREGB_ENC(Instance,regionid)         (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                   RISAF_REGZCFGR_ENC))
#define HAL_RIF_SET_RISAF_SUBREGB_DCEN(Instance,regionid)        (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BNESTR),\
                                                                   RISAF_REGZNESTR_DCEN))
#define HAL_RIF_SET_RISAF_SUBREGB_STARTR(Instance,regionid,addr) (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BSTARTR),\
                                                                   addr))
#define HAL_RIF_SET_RISAF_SUBREGB_ENDR(Instance,regionid,addr)   (SEC_SET_BIT\
                                                                  ((((RISAF_TypeDef*)Instance)->REG[regionid].BENDR),\
                                                                   addr))

#define HAL_RIF_CLEAR_RISAF_SUBREGA_SREN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_SREN))
#define HAL_RIF_CLEAR_RISAF_SUBREGA_SEC(Instance,regionid)      (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_SEC))
#define HAL_RIF_CLEAR_RISAF_SUBREGA_PRIV(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAF_SUBREGA_RDEN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_RDEN))
#define HAL_RIF_CLEAR_RISAF_SUBREGA_WREN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_WREN))
#define HAL_RIF_CLEAR_RISAF_SUBREGA_ENC(Instance,regionid)      (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_ENC))
#define HAL_RIF_CLEAR_RISAF_SUBREGA_DCEN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ANESTR),\
                                                                  RISAF_REGZNESTR_DCEN))
#define HAL_RIF_CLEAR_RISAF_SUBREGB_SREN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_SREN))
#define HAL_RIF_CLEAR_RISAF_SUBREGB_SEC(Instance,regionid)      (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_SEC))
#define HAL_RIF_CLEAR_RISAF_SUBREGB_PRIV(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_PRIV))
#define HAL_RIF_CLEAR_RISAF_SUBREGB_RDEN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_RDEN))
#define HAL_RIF_CLEAR_RISAF_SUBREGB_WREN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_WREN))
#define HAL_RIF_CLEAR_RISAF_SUBREGB_ENC(Instance,regionid)      (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_ENC))
#define HAL_RIF_CLEAR_RISAF_SUBREGB_DCEN(Instance,regionid)     (SEC_CLEAR_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BNESTR),\
                                                                  RISAF_REGZNESTR_DCEN))

#define HAL_RIF_READ_RISAF_ACFGR(Instance,regionid)             (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR)))
#define HAL_RIF_READ_RISAF_ASTARTR(Instance,regionid)           (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ASTARTR)))
#define HAL_RIF_READ_RISAF_AENDR(Instance,regionid)             (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].AENDR)))
#define HAL_RIF_READ_RISAF_ANESTR(Instance,regionid)            (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ANESTR)))
#define HAL_RIF_READ_RISAF_BCFGR(Instance,regionid)             (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR)))
#define HAL_RIF_READ_RISAF_BSTARTR(Instance,regionid)           (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BSTARTR)))
#define HAL_RIF_READ_RISAF_BENDR(Instance,regionid)             (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BENDR)))
#define HAL_RIF_READ_RISAF_BNESTR(Instance,regionid)            (SEC_READ_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BNESTR)))

/* #define HAL_RIF_READ_RISAF_SUBREGA_DCCID(Instance,regionid)  (SEC_READ_BIT\
   ((((RISAF_TypeDef*)Instance)->REG[regionid].ANESTR),\
   RISAF_REGZNESTR_DCCID) >> RISAF_REGZNESTR_DCCID_Pos) */
#define HAL_RIF_READ_RISAF_SUBREGA_DCCID(Instance,regionid)     (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ANESTR),\
                                                                  RISAF_REGZNESTR_DCCID))
#define HAL_RIF_IS_RISAF_SUBREGA_DCCID(Instance,regionid,cid)   (HAL_RIF_READ_RISAF_SUBREGA_DCCID\
                                                                 (Instance,regionid) == cid ? 1 : 0)
#define HAL_RIF_SET_RISAF_SUBREGA_DCCID(Instance,regionid,val)  (SEC_MODIFY_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ANESTR),\
                                                                  RISAF_REGZNESTR_DCCID_Msk, val))
/* #define HAL_RIF_READ_RISAF_SUBREGB_DCCID(Instance,regionid)     (SEC_READ_BIT\
     ((((RISAF_TypeDef*)Instance)->REG[regionid].BNESTR),\
   RISAF_REGZNESTR_DCCID) >> RISAF_REGZNESTR_DCCID_Pos) */
#define HAL_RIF_READ_RISAF_SUBREGB_DCCID(Instance,regionid)     (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BNESTR),\
                                                                  RISAF_REGZNESTR_DCCID))
#define HAL_RIF_IS_RISAF_SUBREGB_DCCID(Instance,regionid,cid)   (HAL_RIF_READ_RISAF_SUBREGB_DCCID\
                                                                 (Instance,regionid) == cid ? 1 : 0)
#define HAL_RIF_SET_RISAF_SUBREGB_DCCID(Instance,regionid,val)  (SEC_MODIFY_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BNESTR),\
                                                                  RISAF_REGZNESTR_DCCID_Msk, val))

/* #define HAL_RIF_READ_RISAF_SUBREGA_SRCID(Instance,regionid)     (SEC_READ_BIT\
   ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
   RISAF_REGZCFGR_SRCID) >> RISAF_REGZCFGR_SRCID_Pos) */
#define HAL_RIF_READ_RISAF_SUBREGA_SRCID(Instance,regionid)     (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_SRCID))
#define HAL_RIF_IS_RISAF_SUBREGA_SRCID(Instance,regionid,cid)   (HAL_RIF__READ_RISAF_SUBREGA_SRCID\
                                                                 (Instance,regionid) == cid ? 1 : 0)
#define HAL_RIF_SET_RISAF_SUBREGA_SRCID(Instance,regionid,val)  (SEC_MODIFY_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].ACFGR),\
                                                                  RISAF_REGZCFGR_SRCID_Msk, val))
/* #define HAL_RIF_READ_RISAF_SUBREGB_SRCID(Instance,regionid)     (SEC_READ_BIT\
   ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
   RISAF_REGZCFGR_SRCID) >> RISAF_REGZCFGR_SRCID_Pos) */
#define HAL_RIF_READ_RISAF_SUBREGB_SRCID(Instance,regionid)     (SEC_READ_BIT\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_SRCID))
#define HAL_RIF_IS_RISAF_SUBREGB_SRCID(Instance,regionid,cid)   (HAL_RIF__READ_RISAF_SUBREGB_SRCID\
                                                                 (Instance,regionid) == cid ? 1 : 0)
#define HAL_RIF_SET_RISAF_SUBREGB_SRCID(Instance,regionid,val)  (SEC_MODIFY_REG\
                                                                 ((((RISAF_TypeDef*)Instance)->REG[regionid].BCFGR),\
                                                                  RISAF_REGZCFGR_SRCID_Msk, val))

/* ENCRYPTION KEY */
#define HAL_RIF_SET_RISAF_KEYR(Instance,keyid,val)          (SEC_WRITE_REG\
                                                             ((((RISAF_TypeDef*)Instance)->KEYR[keyid]), val))

/* ILLEGAL ACCESS */
#define HAL_RIF_READ_RISAF_IASR(Instance)                   (SEC_READ_REG\
                                                             ((((RISAF_TypeDef*)Instance)->IASR)))
#define HAL_RIF_READ_RISAF_IAESR0(Instance)                 (SEC_READ_REG\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[0].IAESR)))
#define HAL_RIF_READ_RISAF_IAESR1(Instance)                 (SEC_READ_REG\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[1].IAESR)))
#define HAL_RIF_READ_RISAF_IADDR0(Instance)                 (SEC_READ_REG\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[0].IADDR)))
#define HAL_RIF_READ_RISAF_IADDR1(Instance)                 (SEC_READ_REG\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[1].IADDR)))

#define HAL_RIF_CLEAR_RISAF_IACR_CAEF(Instance)             (SEC_SET_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IACR), RISAF_IACR_CAEF))
#define HAL_RIF_CLEAR_RISAF_IACR_IAEF0(Instance)            (SEC_SET_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IACR), RISAF_IACR_IAEF0))
#define HAL_RIF_CLEAR_RISAF_IACR_IAEF1(Instance)            (SEC_SET_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IACR), RISAF_IACR_IAEF1))
#define HAL_RIF_CLEAR_RISAF_IACR(Instance)                  (SEC_SET_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IACR),\
                                                              RISAF_IACR_CAEF|RISAF_IACR_IAEF0|RISAF_IACR_IAEF1))

#define HAL_RIF_IS_RISAF_IASR_CAEF(Instance)                (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IASR), RISAF_IASR_CAEF))
#define HAL_RIF_IS_RISAF_IASR_IAEF0(Instance)               (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IASR), RISAF_IASR_IAEF0))
#define HAL_RIF_IS_RISAF_IASR_IAEF1(Instance)               (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IASR), RISAF_IASR_IAEF1))
#define HAL_RIF_IS_RISAF_IAESR0_IAPRIV(Instance)            (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[0].IAESR),\
                                                              RISAF_IAESR_IAPRIV))
#define HAL_RIF_IS_RISAF_IAESR0_IASEC(Instance)             (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[0].IAESR),\
                                                              RISAF_IAESR_IASEC))
#define HAL_RIF_IS_RISAF_IAESR0_IANRW(Instance)             (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[0].IAESR),\
                                                              RISAF_IAESR_IANRW))
#define HAL_RIF_IS_RISAF_IAESR1_IAPRIV(Instance)            (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[1].IAESR),\
                                                              RISAF_IAESR_IAPRIV))
#define HAL_RIF_IS_RISAF_IAESR1_IASEC(Instance)             (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[1].IAESR),\
                                                              RISAF_IAESR_IASEC))
#define HAL_RIF_IS_RISAF_IAESR1_IANRW(Instance)             (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[1].IAESR),\
                                                              RISAF_IAESR_IANRW))

#define HAL_RIF_READ_RISAF_IAESR0_IACID(Instance)           (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[0].IAESR),\
                                                              RISAF_IAESR_IACID) >> RISAF_IAESR_IACID_Pos)
#define HAL_RIF_READ_RISAF_IAESR1_IACID(Instance)           (SEC_READ_BIT\
                                                             ((((RISAF_TypeDef*)Instance)->IAR[1].IAESR),\
                                                              RISAF_IAESR_IACID) >> RISAF_IAESR_IACID_Pos)

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_HAL_RIF_H */
