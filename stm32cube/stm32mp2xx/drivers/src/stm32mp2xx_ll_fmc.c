/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_fmc.c
  * @author  MCD Application Team
  * @brief   FMC Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the Flexible Memory Controller (FMC) peripheral memories:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                        ##### FMC peripheral features #####
  ==============================================================================
  [..] The Flexible memory controller (FMC) includes following memory controllers:
       (+) The NOR/PSRAM memory controller
     (+) The NAND memory controller

  [..] The FMC functional block makes the interface with synchronous and asynchronous static
       memories. Its main purposes are:
       (+) to translate AHB transactions into the appropriate external device protocol
       (+) to meet the access time requirements of the external memory devices

  [..] All external memories share the addresses, data and control signals with the controller.
       Each external device is accessed by means of a unique Chip Select. The FMC performs
       only one access at a time to an external device.
       The main features of the FMC controller are the following:
        (+) Interface with static-memory mapped devices including:
           (++) Static random access memory (SRAM)
           (++) Read-only memory (ROM)
           (++) NOR Flash memory/OneNAND Flash memory
           (++) PSRAM (4 memory banks)
           (++) Two banks of NAND Flash memory with ECC hardware to check up to 8 Kbytes of
                data
        (+) Independent Chip Select control for each memory bank
        (+) Independent configuration for each memory bank

  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx_hal.h"

/** @addtogroup STM32MP2xx_HAL_Driver
  * @{
  */
#if ((defined HAL_NOR_MODULE_ENABLED || defined HAL_SRAM_MODULE_ENABLED) || defined HAL_NAND_MODULE_ENABLED )

/** @defgroup FMC_LL  FMC Low Layer
  * @brief FMC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup FMC_LL_Private_Constants FMC Low Layer Private Constants
  * @{
  */

/* ----------------------- FMC registers bit mask --------------------------- */

/* --- BCR Register ---*/
/* BCR register clear mask */

/* --- BTR Register ---*/
/* BTR register clear mask */
#define BTR_CLEAR_MASK    ((uint32_t)(FMC_BTRx_ADDSET | FMC_BTRx_ADDHLD  |\
                                      FMC_BTRx_DATAST | FMC_BTRx_BUSTURN |\
                                      FMC_BTRx_CLKDIV | FMC_BTRx_DATLAT  |\
                                      FMC_BTRx_ACCMOD | FMC_BTRx_DATAHLD))

/* --- BWTR Register ---*/
/* BWTR register clear mask */
#if defined(FMC_BWTRx_BUSTURN)
#define BWTR_CLEAR_MASK   ((uint32_t)(FMC_BWTRx_ADDSET | FMC_BWTRx_ADDHLD  |\
                                      FMC_BWTRx_DATAST | FMC_BWTRx_BUSTURN |\
                                      FMC_BWTRx_ACCMOD | FMC_BWTRx_DATAHLD))
#else
#define BWTR_CLEAR_MASK   ((uint32_t)(FMC_BWTRx_ADDSET | FMC_BWTRx_ADDHLD  |\
                                      FMC_BWTRx_DATAST | FMC_BWTRx_ACCMOD  |\
                                      FMC_BWTRx_DATAHLD))
#endif /* FMC_BWTRx_BUSTURN */

/* --- PCR Register ---*/
/* PCR register clear mask */
#define PCR_CLEAR_MASK    ((uint32_t)(FMC_PCR_PWAITEN | FMC_PCR_PBKEN  | \
                                      FMC_PCR_PWID    | FMC_PCR_ECCEN  | \
                                      FMC_PCR_TCLR    | FMC_PCR_TAR    | \
                                      FMC_PCR_ECCSS))
/* --- PMEM Register ---*/
/* PMEM register clear mask */
#define PMEM_CLEAR_MASK   ((uint32_t)(FMC_PMEM_MEMSET  | FMC_PMEM_MEMWAIT |\
                                      FMC_PMEM_MEMHOLD | FMC_PMEM_MEMHIZ))

/* --- PATT Register ---*/
/* PATT register clear mask */
#define PATT_CLEAR_MASK   ((uint32_t)(FMC_PATT_ATTSET  | FMC_PATT_ATTWAIT |\
                                      FMC_PATT_ATTHOLD | FMC_PATT_ATTHIZ))


/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup FMC_LL_Exported_Functions FMC Low Layer Exported Functions
  * @{
  */

/** @addtogroup FMC_LL_Exported_Functions RIF protection configuration
  *  @brief   RIF protection configuration functions
  *
@verbatim
  ==============================================================================
            ##### RIF protection configuration functions #####
  ==============================================================================
    [..]
    This subsection allows to get/set the RIF protection configuration made of
    security, privilege, and cid (compartment id) attributes.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the RIF COMMON, NOR and NAND CID protection
  * @param  Item COMMON or NOR/PSRAM or NAND
  *           @arg FMC_COMMON (COMMON controller, FMC_CFGR)
  *           @arg FMC_NOR_PSRAM_1 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_2 (NOR/PSRAM controller for Chip Select NE2,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_3 (NOR/PSRAM controller for Chip Select NE3,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_4 (NOR/PSRAM controller for Chip Select NE4,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NAND (NAND controller, including registers and associated memory map region (4 Kbytes))
  * @param  Attributes RIF COMMON, NOR/PSRAM and NAND CID protection attribute
  *           @arg FMC_PRIV
  *           @arg FMC_NPRIV
  *           @arg FMC_SEC
  *           @arg FMC_NSEC
  *           @arg FMC_CID_DISABLE
  *           @arg FMC_CID_STATIC_0
  *           ...
  *           @arg FMC_CID_STATIC_3
  *           @arg FMC_CID_DYNAMIC_0
  *           ...
  *           @arg FMC_CID_DYNAMIC_3
  * @retval HAL_OK if the configuration is successfully set, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_FMC_ConfigAttributes(uint32_t Item, uint32_t Attributes)
{
  /* Check the parameters */
  assert_param(IS_FMC_ITEM_CID(Item));
  assert_param(IS_FMC_ATTRIBUTES_CID(Attributes));

  /* Configure PRIV attribute */
  if ((Attributes & FMC_PRIV_SELECT) == FMC_PRIV_SELECT)
  {
    if ((Attributes & FMC_PRIV) == FMC_PRIV)
    {
      FMC_Common_R->PRIVCFGR |= (1UL << Item);
    }
    else
    {
      FMC_Common_R->PRIVCFGR &= ~(1UL << Item);
    }
  }

  /* Configure SEC attribute */
  if ((Attributes & FMC_SEC_SELECT) == FMC_SEC_SELECT)
  {
    if ((Attributes & FMC_SEC) == FMC_SEC)
    {
      FMC_Common_R->SECCFGR |= (1UL << Item);
    }
    else
    {
      FMC_Common_R->SECCFGR &= ~(1UL << Item);
    }
  }

  /* Configure CID attribute */
  if (Item == FMC_COMMON)
  {
    FMC_Common_R->CIDCFGR0 = 0;  /* remove any CID filtering */
    /*if static CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_STATIC_SELECT)) == FMC_CID_STATIC_SELECT)
    {
      /* Write static CID configuration */
      FMC_Common_R->CIDCFGR0 |= (Attributes & FMC_CIDCFGR0_SCID_Msk) | FMC_CIDCFGR0_CFEN;
    }
    /*if shared CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_DYNAMIC_SELECT)) == FMC_CID_DYNAMIC_SELECT)
    {
      /* Write shared CID configuration */
      FMC_Common_R->CIDCFGR0 |= (Attributes & FMC_CID_DYNAMIC_MASK) | FMC_CIDCFGR0_CFEN | FMC_CIDCFGR0_SEMEN;
    }
  }
  else if (Item == FMC_NOR_PSRAM_1)
  {
    FMC_Common_R->CIDCFGR1 = 0;  /* remove any CID filtering */
    /*if static CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_STATIC_SELECT)) == FMC_CID_STATIC_SELECT)
    {
      /* Write static CID configuration */
      FMC_Common_R->CIDCFGR1 |= (Attributes & FMC_CIDCFGR1_SCID_Msk) | FMC_CIDCFGR1_CFEN;
    }
    /*if shared CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_DYNAMIC_SELECT)) == FMC_CID_DYNAMIC_SELECT)
    {
      /* Write shared CID configuration */
      FMC_Common_R->CIDCFGR1 |= (Attributes & FMC_CID_DYNAMIC_MASK) | FMC_CIDCFGR1_CFEN | FMC_CIDCFGR1_SEMEN;
    }
  }
  else if (Item == FMC_NOR_PSRAM_2)
  {
    FMC_Common_R->CIDCFGR2 = 0;  /* remove any CID filtering */
    /*if static CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_STATIC_SELECT)) == FMC_CID_STATIC_SELECT)
    {
      /* Write static CID configuration */
      FMC_Common_R->CIDCFGR2 |= (Attributes & FMC_CIDCFGR2_SCID_Msk) | FMC_CIDCFGR2_CFEN;
    }
    /*if shared CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_DYNAMIC_SELECT)) == FMC_CID_DYNAMIC_SELECT)
    {
      /* Write shared CID configuration */
      FMC_Common_R->CIDCFGR2 |= (Attributes & FMC_CID_DYNAMIC_MASK) | FMC_CIDCFGR2_CFEN | FMC_CIDCFGR2_SEMEN;
    }
  }
  else if (Item == FMC_NOR_PSRAM_3)
  {
    FMC_Common_R->CIDCFGR3 = 0;  /* remove any CID filtering */
    /*if static CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_STATIC_SELECT)) == FMC_CID_STATIC_SELECT)
    {
      /* Write static CID configuration */
      FMC_Common_R->CIDCFGR3 |= (Attributes & FMC_CIDCFGR3_SCID_Msk) | FMC_CIDCFGR3_CFEN;
    }
    /*if shared CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_DYNAMIC_SELECT)) == FMC_CID_DYNAMIC_SELECT)
    {
      /* Write shared CID configuration */
      FMC_Common_R->CIDCFGR3 |= (Attributes & FMC_CID_DYNAMIC_MASK) | FMC_CIDCFGR3_CFEN | FMC_CIDCFGR3_SEMEN;
    }
  }
  else if (Item == FMC_NOR_PSRAM_4)
  {
    FMC_Common_R->CIDCFGR4 = 0;  /* remove any CID filtering */
    /*if static CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_STATIC_SELECT)) == FMC_CID_STATIC_SELECT)
    {
      /* Write static CID configuration */
      FMC_Common_R->CIDCFGR4 |= (Attributes & FMC_CIDCFGR4_SCID_Msk) | FMC_CIDCFGR4_CFEN;
    }
    /*if shared CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_DYNAMIC_SELECT)) == FMC_CID_DYNAMIC_SELECT)
    {
      /* Write shared CID configuration */
      FMC_Common_R->CIDCFGR4 |= (Attributes & FMC_CID_DYNAMIC_MASK) | FMC_CIDCFGR4_CFEN | FMC_CIDCFGR4_SEMEN;
    }
  }
  else if (Item == FMC_NAND)
  {
    FMC_Common_R->CIDCFGR5 = 0;  /* remove any CID filtering */
    /*if static CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_STATIC_SELECT)) == FMC_CID_STATIC_SELECT)
    {
      /* Write static CID configuration */
      FMC_Common_R->CIDCFGR5 |= (Attributes & FMC_CIDCFGR5_SCID_Msk) | FMC_CIDCFGR5_CFEN;
    }
    /*if shared CID field value is used ONLY and CID filtering is not disable */
    if ((Attributes & (FMC_CID_DISABLE | FMC_CID_DYNAMIC_SELECT)) == FMC_CID_DYNAMIC_SELECT)
    {
      /* Write shared CID configuration */
      FMC_Common_R->CIDCFGR5 |= (Attributes & FMC_CID_DYNAMIC_MASK) | FMC_CIDCFGR5_CFEN | FMC_CIDCFGR5_SEMEN;
    }
  }
  else
  {
    /* Nothing to do */
  }

  return HAL_OK;
}

/**
  * @brief  Get the configuration of the RIF COMMON, NOR and NAND CID protection
  * @param  Item COMMON or NOR/PSRAM or NAND
  *           @arg FMC_COMMON (COMMON controller, FMC_CFGR)
  *           @arg FMC_NOR_PSRAM_1 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_2 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_3 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_4 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NAND (NAND controller, including registers and associated memory map region (4 Kbytes))
  * @param  pAttributes RIF COMMON, NOR/PSRAM and NAND CID protection attribute
  *           @arg FMC_PRIV
  *           @arg FMC_NPRIV
  *           @arg FMC_SEC
  *           @arg FMC_NSEC
  *           @arg FMC_CID_DISABLE
  *           @arg FMC_CID_STATIC_0
  *           ...
  *           @arg FMC_CID_STATIC_3
  *           @arg FMC_CID_DYNAMIC_0
  *           ...
  *           @arg FMC_CID_DYNAMIC_3
  * @retval HAL_OK if the configuration is successfully read, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_FMC_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes)
{
  if (pAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_FMC_ITEM_CID(Item));

  *pAttributes = ((FMC_Common_R->PRIVCFGR & (1UL << Item)) == 0UL) ? FMC_NPRIV : FMC_PRIV;

  /* Get item security attribute */
  *pAttributes |= ((FMC_Common_R->SECCFGR & (1UL << Item)) == 0UL) ? FMC_NSEC : FMC_SEC;

  if (Item == FMC_COMMON)
  {
    /* Get item allocated CID(s) */
    if ((FMC_Common_R->CIDCFGR0 & FMC_CIDCFGR0_CFEN_Msk) == FMC_CIDCFGR0_CFEN)
    {
      if ((FMC_Common_R->CIDCFGR0 & FMC_CIDCFGR0_SEMEN_Msk) == FMC_CIDCFGR0_SEMEN)
      {
        /* Get CIDs value from Semaphore white list */
        *pAttributes |= ((FMC_CID_DYNAMIC_SELECT) |
                         ((READ_REG(FMC_Common_R->CIDCFGR0)) &
                          (FMC_CIDCFGR0_SEMWLC2_Msk |
                           FMC_CIDCFGR0_SEMWLC1_Msk |
                           FMC_CIDCFGR0_SEMWLC0_Msk)));
      }
      else
      {
        /* Get CIDs value from Static CID field */
        *pAttributes |= (FMC_CID_STATIC_SELECT | (READ_REG(FMC_Common_R->CIDCFGR0) & FMC_CIDCFGR0_SCID_Msk));
      }
    }
    else
    {
      *pAttributes |= FMC_CID_DISABLE;
    }
  }
  else if (Item == FMC_NOR_PSRAM_1)
  {
    /* Get item allocated CID(s) */
    if ((FMC_Common_R->CIDCFGR1 & FMC_CIDCFGR1_CFEN_Msk) == FMC_CIDCFGR1_CFEN)
    {
      if ((FMC_Common_R->CIDCFGR1 & FMC_CIDCFGR1_SEMEN_Msk) == FMC_CIDCFGR1_SEMEN)
      {
        /* Get CIDs value from Semaphore white list */
        *pAttributes |= ((FMC_CID_DYNAMIC_SELECT) |
                         ((READ_REG(FMC_Common_R->CIDCFGR1)) &
                          (FMC_CIDCFGR1_SEMWLC2_Msk |
                           FMC_CIDCFGR1_SEMWLC1_Msk |
                           FMC_CIDCFGR1_SEMWLC0_Msk)));
      }
      else
      {
        /* Get CIDs value from Static CID field */
        *pAttributes |= (FMC_CID_STATIC_SELECT | (READ_REG(FMC_Common_R->CIDCFGR1) & FMC_CIDCFGR1_SCID_Msk));
      }
    }
    else
    {
      *pAttributes |= FMC_CID_DISABLE;
    }
  }
  else if (Item == FMC_NOR_PSRAM_2)
  {
    /* Get item allocated CID(s) */
    if ((FMC_Common_R->CIDCFGR2 & FMC_CIDCFGR2_CFEN_Msk) == FMC_CIDCFGR2_CFEN)
    {
      if ((FMC_Common_R->CIDCFGR2 & FMC_CIDCFGR2_SEMEN_Msk) == FMC_CIDCFGR2_SEMEN)
      {
        /* Get CIDs value from Semaphore white list */
        *pAttributes |= ((FMC_CID_DYNAMIC_SELECT) |
                         ((READ_REG(FMC_Common_R->CIDCFGR2)) &
                          (FMC_CIDCFGR2_SEMWLC2_Msk |
                           FMC_CIDCFGR2_SEMWLC1_Msk |
                           FMC_CIDCFGR2_SEMWLC0_Msk)));
      }
      else
      {
        /* Get CIDs value from Static CID field */
        *pAttributes |= (FMC_CID_STATIC_SELECT | (READ_REG(FMC_Common_R->CIDCFGR2) & FMC_CIDCFGR2_SCID_Msk));
      }
    }
    else
    {
      *pAttributes |= FMC_CID_DISABLE;
    }
  }
  else if (Item == FMC_NOR_PSRAM_3)
  {
    /* Get item allocated CID(s) */
    if ((FMC_Common_R->CIDCFGR3 & FMC_CIDCFGR3_CFEN_Msk) == FMC_CIDCFGR3_CFEN)
    {
      if ((FMC_Common_R->CIDCFGR3 & FMC_CIDCFGR3_SEMEN_Msk) == FMC_CIDCFGR3_SEMEN)
      {
        /* Get CIDs value from Semaphore white list */
        *pAttributes |= ((FMC_CID_DYNAMIC_SELECT) |
                         ((READ_REG(FMC_Common_R->CIDCFGR3)) &
                          (FMC_CIDCFGR3_SEMWLC2_Msk |
                           FMC_CIDCFGR3_SEMWLC1_Msk |
                           FMC_CIDCFGR3_SEMWLC0_Msk)));
      }
      else
      {
        /* Get CIDs value from Static CID field */
        *pAttributes |= (FMC_CID_STATIC_SELECT | (READ_REG(FMC_Common_R->CIDCFGR3) & FMC_CIDCFGR3_SCID_Msk));
      }
    }
    else
    {
      *pAttributes |= FMC_CID_DISABLE;
    }
  }
  else if (Item == FMC_NOR_PSRAM_4)
  {
    /* Get item allocated CID(s) */
    if ((FMC_Common_R->CIDCFGR4 & FMC_CIDCFGR4_CFEN_Msk) == FMC_CIDCFGR4_CFEN)
    {
      if ((FMC_Common_R->CIDCFGR4 & FMC_CIDCFGR4_SEMEN_Msk) == FMC_CIDCFGR4_SEMEN)
      {
        /* Get CIDs value from Semaphore white list */
        *pAttributes |= ((FMC_CID_DYNAMIC_SELECT) |
                         ((READ_REG(FMC_Common_R->CIDCFGR4)) &
                          (FMC_CIDCFGR4_SEMWLC2_Msk |
                           FMC_CIDCFGR4_SEMWLC1_Msk |
                           FMC_CIDCFGR4_SEMWLC0_Msk)));
      }
      else
      {
        /* Get CIDs value from Static CID field */
        *pAttributes |= (FMC_CID_STATIC_SELECT | (READ_REG(FMC_Common_R->CIDCFGR4) & FMC_CIDCFGR4_SCID_Msk));
      }
    }
    else
    {
      *pAttributes |= FMC_CID_DISABLE;
    }
  }
  else if (Item == FMC_NAND)
  {
    /* Get channel allocated CID(s) */
    if ((FMC_Common_R->CIDCFGR5 & FMC_CIDCFGR5_CFEN_Msk) == FMC_CIDCFGR5_CFEN)
    {
      if ((FMC_Common_R->CIDCFGR5 & FMC_CIDCFGR5_SEMEN_Msk) == FMC_CIDCFGR5_SEMEN)
      {
        /* Get CIDs value from Semaphore white list */
        *pAttributes |= ((FMC_CID_DYNAMIC_SELECT) |
                         ((READ_REG(FMC_Common_R->CIDCFGR5)) &
                          (FMC_CIDCFGR5_SEMWLC2_Msk |
                           FMC_CIDCFGR5_SEMWLC1_Msk |
                           FMC_CIDCFGR5_SEMWLC0_Msk)));
      }
      else
      {
        /* Get CIDs value from Static CID field */
        *pAttributes |= (FMC_CID_STATIC_SELECT | (READ_REG(FMC_Common_R->CIDCFGR5) & FMC_CIDCFGR5_SCID_Msk));
      }
    }
    else
    {
      *pAttributes |= FMC_CID_DISABLE;
    }
  }
  else
  {
    /* Nothing to do */
  }

  return HAL_OK;
}

/**
  * @brief  Attempt to acquire semaphore(s) of the RIF COMMON, NOR and NAND CID protection
  * @param  Item COMMON or NOR/PSRAM or NAND
  *           @arg FMC_COMMON (COMMON controller, FMC_CFGR)
  *           @arg FMC_NOR_PSRAM_1 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_2 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_3 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_4 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NAND (NAND controller, including registers and associated memory map region (4 Kbytes))
  * @retval HAL_OK if the configuration is successfully read, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_FMC_TakeSemaphore(uint32_t Item)
{
  uint32_t cidcurrent;

  /* Check the parameters */
  assert_param(IS_FMC_ITEM_CID(Item));

#if defined(CORE_CM0PLUS)
  cidcurrent = RIF_CID_CPU3_CM0;
#endif /* CORE_CM0PLUS */
#if defined(CORE_CM33)
  cidcurrent = RIF_CID_CPU2_CM33;
#endif /* CORE_CM33 */
#if defined(CORE_CA35)
  cidcurrent = RIF_CID_CPU1_CA35;
#endif /* CORE_CA35 */

  /* Take Semaphore */
  if (Item == FMC_COMMON)
  {
    FMC_Common_R->SEMCR0 |= FMC_SEMCR0_SEM_MUTEX;

    if ((FMC_Common_R->SEMCR0 & FMC_SEMCR0_SEMCID_Msk) != (cidcurrent << FMC_SEMCR0_SEMCID_Pos))
    {
      /* Mutex not taken with current CID - it means that other authorized CID has control,
        previous acquired semaphore shall be released and status error is returned */
      (void)HAL_FMC_ReleaseSemaphore(Item);
      return HAL_ERROR;
    }
  }
  else if (Item == FMC_NOR_PSRAM_1)
  {
    FMC_Common_R->SEMCR1 |= FMC_SEMCR1_SEM_MUTEX;

    if ((FMC_Common_R->SEMCR1 & FMC_SEMCR1_SEMCID_Msk) != (cidcurrent << FMC_SEMCR1_SEMCID_Pos))
    {
      /* Mutex not taken with current CID - it means that other authorized CID has control,
        previous acquired semaphore shall be released and status error is returned */
      (void)HAL_FMC_ReleaseSemaphore(Item);
      return HAL_ERROR;
    }
  }
  else if (Item == FMC_NOR_PSRAM_2)
  {
    FMC_Common_R->SEMCR2 |= FMC_SEMCR2_SEM_MUTEX;

    if ((FMC_Common_R->SEMCR2 & FMC_SEMCR2_SEMCID_Msk) != (cidcurrent << FMC_SEMCR2_SEMCID_Pos))
    {
      /* Mutex not taken with current CID - it means that other authorized CID has control,
        previous acquired semaphore shall be released and status error is returned */
      (void)HAL_FMC_ReleaseSemaphore(Item);
      return HAL_ERROR;
    }
  }
  else if (Item == FMC_NOR_PSRAM_3)
  {
    FMC_Common_R->SEMCR3 |= FMC_SEMCR3_SEM_MUTEX;

    if ((FMC_Common_R->SEMCR3 & FMC_SEMCR3_SEMCID_Msk) != (cidcurrent << FMC_SEMCR3_SEMCID_Pos))
    {
      /* Mutex not taken with current CID - it means that other authorized CID has control,
        previous acquired semaphore shall be released and status error is returned */
      (void)HAL_FMC_ReleaseSemaphore(Item);
      return HAL_ERROR;
    }
  }
  else if (Item == FMC_NOR_PSRAM_4)
  {
    FMC_Common_R->SEMCR4 |= FMC_SEMCR4_SEM_MUTEX;

    if ((FMC_Common_R->SEMCR4 & FMC_SEMCR4_SEMCID_Msk) != (cidcurrent << FMC_SEMCR4_SEMCID_Pos))
    {
      /* Mutex not taken with current CID - it means that other authorized CID has control,
        previous acquired semaphore shall be released and status error is returned */
      (void)HAL_FMC_ReleaseSemaphore(Item);
      return HAL_ERROR;
    }
  }
  else if (Item == FMC_NAND)
  {
    FMC_Common_R->SEMCR5 |= FMC_SEMCR5_SEM_MUTEX;

    if ((FMC_Common_R->SEMCR5 & FMC_SEMCR5_SEMCID_Msk) != (cidcurrent << FMC_SEMCR5_SEMCID_Pos))
    {
      /* Mutex not taken with current CID - it means that other authorized CID has control,
        previous acquired semaphore shall be released and status error is returned */
      (void)HAL_FMC_ReleaseSemaphore(Item);
      return HAL_ERROR;
    }
  }
  else
  {
    /* Nothing to do */
  }

  return HAL_OK;
}

/**
  * @brief  Release semaphore(s) of the RIF COMMON, NOR and NAND CID protection
  * @param  Item COMMON or NOR/PSRAM or NAND
  *           @arg FMC_COMMON (COMMON controller, FMC_CFGR)
  *           @arg FMC_NOR_PSRAM_1 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_2 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_3 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NOR_PSRAM_4 (NOR/PSRAM controller for Chip Select NE1,
                  including registers and associated memory map region (64 Mbytes))
  *           @arg FMC_NAND (NAND controller, including registers and associated memory map region (4 Kbytes))
  * @retval HAL_OK if the configuration is successfully read, HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_FMC_ReleaseSemaphore(uint32_t Item)
{
  /* Check the parameters */
  assert_param(IS_FMC_ITEM_CID(Item));

  /* Release Semaphore */
  if (Item == FMC_COMMON)
  {
    FMC_Common_R->SEMCR0 &= ~FMC_SEMCR0_SEM_MUTEX;
  }
  else if (Item == FMC_NOR_PSRAM_1)
  {
    FMC_Common_R->SEMCR1 &= ~FMC_SEMCR1_SEM_MUTEX;
  }
  else if (Item == FMC_NOR_PSRAM_2)
  {
    FMC_Common_R->SEMCR2 &= ~FMC_SEMCR2_SEM_MUTEX;
  }
  else if (Item == FMC_NOR_PSRAM_3)
  {
    FMC_Common_R->SEMCR3 &= ~FMC_SEMCR3_SEM_MUTEX;
  }
  else if (Item == FMC_NOR_PSRAM_4)
  {
    FMC_Common_R->SEMCR4 &= ~FMC_SEMCR4_SEM_MUTEX;
  }
  else if (Item == FMC_NAND)
  {
    FMC_Common_R->SEMCR5 &= ~FMC_SEMCR5_SEM_MUTEX;
  }
  else
  {
    /* Nothing to do */
  }

  return HAL_OK;
}


/** @defgroup FMC_LL_Exported_Functions_NORSRAM FMC Low Layer NOR SRAM Exported Functions
  * @brief  NORSRAM Controller functions
  *
  @verbatim
  ==============================================================================
                   ##### How to use NORSRAM device driver #####
  ==============================================================================

  [..]
    This driver contains a set of APIs to interface with the FMC NORSRAM banks in order
    to run the NORSRAM external devices.

    (+) FMC NORSRAM bank reset using the function FMC_NORSRAM_DeInit()
    (+) FMC NORSRAM bank control configuration using the function FMC_NORSRAM_Init()
    (+) FMC NORSRAM bank timing configuration using the function FMC_NORSRAM_Timing_Init()
    (+) FMC NORSRAM bank extended timing configuration using the function
        FMC_NORSRAM_Extended_Timing_Init()
    (+) FMC NORSRAM bank enable/disable write operation using the functions
        FMC_NORSRAM_WriteOperation_Enable()/FMC_NORSRAM_WriteOperation_Disable()

@endverbatim
  * @{
  */

/** @defgroup FMC_LL_NORSRAM_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FMC NORSRAM interface
    (+) De-initialize the FMC NORSRAM interface
    (+) Configure the FMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the FMC_NORSRAM device according to the specified
  *         control parameters in the FMC_NORSRAM_InitTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Init Pointer to NORSRAM Initialization structure
  * @retval HAL status
  */
HAL_StatusTypeDef  FMC_NORSRAM_Init(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_InitTypeDef *Init)
{
  uint32_t flashaccess;
  uint32_t btcr_reg;
  uint32_t mask;

  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_BANK(Init->NSBank));
  assert_param(IS_FMC_MUX(Init->DataAddressMux));
  assert_param(IS_FMC_MEMORY(Init->MemoryType));
  assert_param(IS_FMC_NORSRAM_MEMORY_WIDTH(Init->MemoryDataWidth));
  assert_param(IS_FMC_BURSTMODE(Init->BurstAccessMode));
  assert_param(IS_FMC_WAIT_POLARITY(Init->WaitSignalPolarity));
  assert_param(IS_FMC_WAIT_SIGNAL_ACTIVE(Init->WaitSignalActive));
  assert_param(IS_FMC_WRITE_OPERATION(Init->WriteOperation));
  assert_param(IS_FMC_WAITE_SIGNAL(Init->WaitSignal));
  assert_param(IS_FMC_EXTENDED_MODE(Init->ExtendedMode));
  assert_param(IS_FMC_ASYNWAIT(Init->AsynchronousWait));
  assert_param(IS_FMC_WRITE_BURST(Init->WriteBurst));
  assert_param(IS_FMC_CONTINOUS_CLOCK(Init->ContinuousClock));
  assert_param(IS_FMC_PAGESIZE(Init->PageSize));
  assert_param(IS_FMC_NBL_SETUPTIME(Init->NBLSetupTime));

  /* Disable NORSRAM Device */
  __FMC_NORSRAM_DISABLE(Device, Init->NSBank);

  /* Set NORSRAM device control parameters */
  if (Init->MemoryType == FMC_MEMORY_TYPE_NOR)
  {
    flashaccess = FMC_NORSRAM_FLASH_ACCESS_ENABLE;
  }
  else
  {
    flashaccess = FMC_NORSRAM_FLASH_ACCESS_DISABLE;
  }

  btcr_reg = (flashaccess                   | \
              Init->DataAddressMux          | \
              Init->MemoryType              | \
              Init->MemoryDataWidth         | \
              Init->BurstAccessMode         | \
              Init->WaitSignalPolarity      | \
              Init->WaitSignalActive        | \
              Init->WriteOperation          | \
              Init->WaitSignal              | \
              Init->ExtendedMode            | \
              Init->AsynchronousWait        | \
              Init->WriteBurst);

  btcr_reg |= Init->ContinuousClock;
  btcr_reg |= Init->NBLSetupTime;
  btcr_reg |= Init->PageSize;

  mask = (FMC_BCRx_MBKEN                |
          FMC_BCRx_MUXEN                |
          FMC_BCRx_MTYP                 |
          FMC_BCRx_MWID                 |
          FMC_BCRx_FACCEN               |
          FMC_BCRx_BURSTEN              |
          FMC_BCRx_WAITPOL              |
          FMC_BCRx_WAITCFG              |
          FMC_BCRx_WREN                 |
          FMC_BCRx_WAITEN               |
          FMC_BCRx_EXTMOD               |
          FMC_BCRx_ASYNCWAIT            |
          FMC_BCRx_CBURSTRW);

  mask |= FMC_CFGR_CCLKEN;
  mask |= FMC_BCRx_NBLSET;
  mask |= FMC_BCRx_CPSIZE;

  MODIFY_REG(Device->BTCR[Init->NSBank], mask, btcr_reg);

  /* Configure synchronous mode when Continuous clock is enabled for bank2..4 */
  if ((Init->ContinuousClock == FMC_CONTINUOUS_CLOCK_SYNC_ASYNC) && (Init->NSBank != FMC_NORSRAM_BANK1))
  {
    MODIFY_REG(Device->BTCR[FMC_NORSRAM_BANK1], FMC_CFGR_CCLKEN, Init->ContinuousClock);
  }

  return HAL_OK;
}

/**
  * @brief  DeInitialize the FMC_NORSRAM peripheral
  * @param  Device Pointer to NORSRAM device instance
  * @param  ExDevice Pointer to NORSRAM extended mode device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_DeInit(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_EXTENDED_TypeDef *ExDevice, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_EXTENDED_DEVICE(ExDevice));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Disable the FMC_NORSRAM device */
  __FMC_NORSRAM_DISABLE(Device, Bank);

  /* De-initialize the FMC_NORSRAM device */
  /* FMC_NORSRAM_BANK1 */
  if (Bank == FMC_NORSRAM_BANK1)
  {
    Device->BTCR[Bank] = 0x000030DBU;
  }
  /* FMC_NORSRAM_BANK2, FMC_NORSRAM_BANK3 or FMC_NORSRAM_BANK4 */
  else
  {
    Device->BTCR[Bank] = 0x000030D2U;
  }

  Device->BTCR[Bank + 1U] = 0x0FFFFFFFU;
  ExDevice->BWTR[Bank]   = 0x0FFFFFFFU;

  return HAL_OK;
}

/**
  * @brief  Initialize the FMC_NORSRAM Timing according to the specified
  *         parameters in the FMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_Timing_Init(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank)
{
  uint32_t tmpr;

  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
  assert_param(IS_FMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
  assert_param(IS_FMC_DATAHOLD_DURATION(Timing->DataHoldTime));
  assert_param(IS_FMC_DATASETUP_TIME(Timing->DataSetupTime));
  assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
  assert_param(IS_FMC_CLK_DIV(Timing->CLKDivision));
  assert_param(IS_FMC_DATA_LATENCY(Timing->DataLatency));
  assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Set FMC_NORSRAM device timing parameters */
  MODIFY_REG(Device->BTCR[Bank + 1U], BTR_CLEAR_MASK, (Timing->AddressSetupTime                                  |
                                                       ((Timing->AddressHoldTime)        << FMC_BTRx_ADDHLD_Pos)  |
                                                       ((Timing->DataSetupTime)          << FMC_BTRx_DATAST_Pos)  |
                                                       ((Timing->DataHoldTime)           << FMC_BTRx_DATAHLD_Pos) |
                                                       ((Timing->BusTurnAroundDuration)  << FMC_BTRx_BUSTURN_Pos) |
                                                       (((Timing->CLKDivision) - 1U)     << FMC_BTRx_CLKDIV_Pos)  |
                                                       (((Timing->DataLatency) - 2U)     << FMC_BTRx_DATLAT_Pos)  |
                                                       (Timing->AccessMode)));

  /* Configure Clock division value (in NORSRAM bank 1) when continuous clock is enabled */
  if (HAL_IS_BIT_SET(Device->BTCR[FMC_NORSRAM_BANK1], FMC_CFGR_CCLKEN))
  {
    tmpr = (uint32_t)(Device->BTCR[FMC_NORSRAM_BANK1 + 1U] & ~(((uint32_t)0x0F) << FMC_BTRx_CLKDIV_Pos));
    tmpr |= (uint32_t)(((Timing->CLKDivision) - 1U) << FMC_BTRx_CLKDIV_Pos);
    MODIFY_REG(Device->BTCR[FMC_NORSRAM_BANK1 + 1U], FMC_BTRx_CLKDIV, tmpr);
  }

  return HAL_OK;
}

/**
  * @brief  Initialize the FMC_NORSRAM Extended mode Timing according to the specified
  *         parameters in the FMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  * @param  ExtendedMode FMC Extended Mode
  *          This parameter can be one of the following values:
  *            @arg FMC_EXTENDED_MODE_DISABLE
  *            @arg FMC_EXTENDED_MODE_ENABLE
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_Extended_Timing_Init(FMC_NORSRAM_EXTENDED_TypeDef *Device,
                                                   FMC_NORSRAM_TimingTypeDef *Timing,
                                                   uint32_t Bank,
                                                   uint32_t ExtendedMode)
{
  /* Check the parameters */
  assert_param(IS_FMC_EXTENDED_MODE(ExtendedMode));

  /* Set NORSRAM device timing register for write configuration, if extended mode is used */
  if (ExtendedMode == FMC_EXTENDED_MODE_ENABLE)
  {
    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_EXTENDED_DEVICE(Device));
    assert_param(IS_FMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
    assert_param(IS_FMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
    assert_param(IS_FMC_DATASETUP_TIME(Timing->DataSetupTime));
    assert_param(IS_FMC_DATAHOLD_DURATION(Timing->DataHoldTime));
#if defined(FMC_BWTRx_BUSTURN)
    assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
#endif /* FMC_BWTRx_BUSTURN */
    assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));
    assert_param(IS_FMC_NORSRAM_BANK(Bank));

    /* Set NORSRAM device timing register for write configuration, if extended mode is used */
    MODIFY_REG(Device->BWTR[Bank], BWTR_CLEAR_MASK, (Timing->AddressSetupTime                                    |
                                                     ((Timing->AddressHoldTime)        << FMC_BWTRx_ADDHLD_Pos)  |
                                                     ((Timing->DataSetupTime)          << FMC_BWTRx_DATAST_Pos)  |
                                                     ((Timing->DataHoldTime)           << FMC_BWTRx_DATAHLD_Pos) |
#if defined(FMC_BWTRx_BUSTURN)
                                                     Timing->AccessMode                                          |
                                                     ((Timing->BusTurnAroundDuration)  << FMC_BWTRx_BUSTURN_Pos)));
#else
                                                     Timing->AccessMode));
#endif /* FMC_BWTRx_BUSTURN */
  }
  else
  {
    Device->BWTR[Bank] = 0x0FFFFFFFU;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup FMC_LL_NORSRAM_Private_Functions_Group2
  *  @brief   management functions
  *
@verbatim
  ==============================================================================
                      ##### FMC_NORSRAM Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FMC NORSRAM interface.

@endverbatim
  * @{
  */

/**
  * @brief  Enables dynamically FMC_NORSRAM write operation.
  * @param  Device Pointer to NORSRAM device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_WriteOperation_Enable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Enable write operation */
  SET_BIT(Device->BTCR[Bank], FMC_WRITE_OPERATION_ENABLE);

  return HAL_OK;
}

/**
  * @brief  Disables dynamically FMC_NORSRAM write operation.
  * @param  Device Pointer to NORSRAM device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_WriteOperation_Disable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Disable write operation */
  CLEAR_BIT(Device->BTCR[Bank], FMC_WRITE_OPERATION_ENABLE);

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup FMC_LL_Exported_Functions_NAND FMC Low Layer NAND Exported Functions
  * @brief    NAND Controller functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use NAND device driver #####
  ==============================================================================
  [..]
    This driver contains a set of APIs to interface with the FMC NAND banks in order
    to run the NAND external devices.

    (+) FMC NAND bank reset using the function FMC_NAND_DeInit()
    (+) FMC NAND bank control configuration using the function FMC_NAND_Init()
    (+) FMC NAND bank common space timing configuration using the function
        FMC_NAND_CommonSpace_Timing_Init()
    (+) FMC NAND bank attribute space timing configuration using the function
        FMC_NAND_AttributeSpace_Timing_Init()
    (+) FMC NAND bank enable/disable ECC correction feature using the functions
        FMC_NAND_ECC_Enable()/FMC_NAND_ECC_Disable()
    (+) FMC NAND bank get ECC correction code using the function FMC_NAND_GetECC()

@endverbatim
  * @{
  */

/** @defgroup FMC_LL_NAND_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FMC NAND interface
    (+) De-initialize the FMC NAND interface
    (+) Configure the FMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the FMC_NAND device according to the specified
  *         control parameters in the FMC_NAND_HandleTypeDef
  * @param  Device Pointer to NAND device instance
  * @param  Init Pointer to NAND Initialization structure
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NAND_Init(FMC_NAND_TypeDef *Device, FMC_NAND_InitTypeDef *Init)
{
  /* Check the parameters */
  assert_param(IS_FMC_NAND_DEVICE(Device));
  assert_param(IS_FMC_NAND_BANK(Init->NandBank));
  assert_param(IS_FMC_WAIT_FEATURE(Init->Waitfeature));
  assert_param(IS_FMC_NAND_MEMORY_WIDTH(Init->MemoryDataWidth));
  assert_param(IS_FMC_ECC_STATE(Init->EccComputation));
  assert_param(IS_FMC_ECCPAGE_SIZE(Init->ECCPageSize));
  assert_param(IS_FMC_TCLR_TIME(Init->TCLRSetupTime));
  assert_param(IS_FMC_TAR_TIME(Init->TARSetupTime));

  /* NAND bank 3 registers configuration */
  MODIFY_REG(Device->PCR, PCR_CLEAR_MASK, (Init->Waitfeature                            |
                                           FMC_PCR_MEMORY_TYPE_NAND                     |
                                           Init->MemoryDataWidth                        |
                                           Init->EccComputation                         |
                                           Init->ECCPageSize                            |
                                           ((Init->TCLRSetupTime) << FMC_PCR_TCLR_Pos)  |
                                           ((Init->TARSetupTime)  << FMC_PCR_TAR_Pos)));

  return HAL_OK;
}

/**
  * @brief  Initializes the FMC_NAND Common space Timing according to the specified
  *         parameters in the FMC_NAND_PCC_TimingTypeDef
  * @param  Device Pointer to NAND device instance
  * @param  Timing Pointer to NAND timing structure
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NAND_CommonSpace_Timing_Init(FMC_NAND_TypeDef *Device, FMC_NAND_PCC_TimingTypeDef *Timing,
                                                   uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NAND_DEVICE(Device));
  assert_param(IS_FMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FMC_HIZ_TIME(Timing->HiZSetupTime));
  assert_param(IS_FMC_NAND_BANK(Bank));

  /* Prevent unused argument(s) compilation warning if no assert_param check */
  UNUSED(Bank);

  /* NAND bank 3 registers configuration */
  MODIFY_REG(Device->PMEM, PMEM_CLEAR_MASK, (Timing->SetupTime                                 |
                                             ((Timing->WaitSetupTime) << FMC_PMEM_MEMWAIT_Pos) |
                                             ((Timing->HoldSetupTime) << FMC_PMEM_MEMHOLD_Pos) |
                                             ((Timing->HiZSetupTime)  << FMC_PMEM_MEMHIZ_Pos)));

  return HAL_OK;
}

/**
  * @brief  Initializes the FMC_NAND Attribute space Timing according to the specified
  *         parameters in the FMC_NAND_PCC_TimingTypeDef
  * @param  Device Pointer to NAND device instance
  * @param  Timing Pointer to NAND timing structure
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NAND_AttributeSpace_Timing_Init(FMC_NAND_TypeDef *Device, FMC_NAND_PCC_TimingTypeDef *Timing,
                                                      uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NAND_DEVICE(Device));
  assert_param(IS_FMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FMC_HIZ_TIME(Timing->HiZSetupTime));
  assert_param(IS_FMC_NAND_BANK(Bank));

  /* Prevent unused argument(s) compilation warning if no assert_param check */
  UNUSED(Bank);

  /* NAND bank 3 registers configuration */
  MODIFY_REG(Device->PATT, PATT_CLEAR_MASK, (Timing->SetupTime                                 |
                                             ((Timing->WaitSetupTime) << FMC_PATT_ATTWAIT_Pos) |
                                             ((Timing->HoldSetupTime) << FMC_PATT_ATTHOLD_Pos) |
                                             ((Timing->HiZSetupTime)  << FMC_PATT_ATTHIZ_Pos)));

  return HAL_OK;
}

/**
  * @brief  DeInitializes the FMC_NAND device
  * @param  Device Pointer to NAND device instance
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NAND_DeInit(FMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NAND_DEVICE(Device));
  assert_param(IS_FMC_NAND_BANK(Bank));

  /* Disable the NAND Bank */
  __FMC_NAND_DISABLE(Device, Bank);

  /* De-initialize the NAND Bank */
  /* Prevent unused argument(s) compilation warning if no assert_param check */
  UNUSED(Bank);

  /* Set the FMC_NAND_BANK3 registers to their reset values */
  WRITE_REG(Device->PCR,  0x0007FE08U);
  WRITE_REG(Device->SR,   0x00015753U);
  WRITE_REG(Device->PMEM, 0x0A0A0A0AU);
  WRITE_REG(Device->PATT, 0x0A0A0A0AU);

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HAL_FMC_NAND_Group2 Peripheral Control functions
  *  @brief   management functions
  *
@verbatim
  ==============================================================================
                       ##### FMC_NAND Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FMC NAND interface.

@endverbatim
  * @{
  */


/**
  * @brief  Enables dynamically FMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NAND_ECC_Enable(FMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NAND_DEVICE(Device));
  assert_param(IS_FMC_NAND_BANK(Bank));

  /* Enable ECC feature */
  /* Prevent unused argument(s) compilation warning if no assert_param check */
  UNUSED(Bank);

  SET_BIT(Device->PCR, FMC_PCR_ECCEN);

  return HAL_OK;
}


/**
  * @brief  Disables dynamically FMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NAND_ECC_Disable(FMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NAND_DEVICE(Device));
  assert_param(IS_FMC_NAND_BANK(Bank));

  /* Disable ECC feature */
  /* Prevent unused argument(s) compilation warning if no assert_param check */
  UNUSED(Bank);

  CLEAR_BIT(Device->PCR, FMC_PCR_ECCEN);

  return HAL_OK;
}

/**
  * @brief  Disables dynamically FMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  * @param  ECCval Pointer to ECC value
  * @param  Bank NAND bank number
  * @param  Timeout Timeout wait value
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NAND_GetECC(FMC_NAND_TypeDef *Device, uint32_t *ECCval, uint32_t Bank, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_FMC_NAND_DEVICE(Device));
  assert_param(IS_FMC_NAND_BANK(Bank));

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until FIFO is empty */
  while (__FMC_NAND_GET_FLAG(Device, Bank, FMC_FLAG_FEMPT) == RESET)
  {
    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* Prevent unused argument(s) compilation warning if no assert_param check */
  UNUSED(Bank);

  /* Get the ECCR register value */
  *ECCval = (uint32_t)Device->HECCR;

  return HAL_OK;
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

#endif /* HAL_NOR_MODULE_ENABLED */
/**
  * @}
  */
