/**
  ******************************************************************************
  * @file    stm32mp2xx_ll_bus.h
  * @author  MCD Application Team
  * @version $VERSION$
  * @date    $DATE$
  * @brief   Header file of BUS LL module.

  @verbatim
                      ##### RCC Limitations #####
  ==============================================================================
    [..]
      A delay between an RCC peripheral clock enable and the effective peripheral
      enabling should be taken into account in order to manage the peripheral read/write
      from/to registers.
      (+) This delay depends on the peripheral mapping.
        (++) AHB & APB peripherals, 1 dummy read is necessary

    [..]
      Workarounds:
      (#) For AHB & APB peripherals, a dummy read to the peripheral register has been
          inserted in each LL_{BUS}_GRP{x}_EnableClock() function.

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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP2xx_LL_BUS_H
#define STM32MP2xx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp2xx.h"

/** @addtogroup STM32MP2xx_LL_Driver
  * @{
  */

#if defined(RCC)
/** @defgroup BUS_LL BUS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup BUS_LL_Exported_Functions BUS Exported Functions
  * @{
  */

/** @defgroup BUS_LL_EF_AHB2 AHB2
  * @{
  */

/**
  * @brief  Enable HPDMA1  peripheral clock
  * @rmtoll HPDMA1         HPDMA1EN         LL_RCC_HPDMA1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA1_EnableClock(void)
{
  SET_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1EN);
}

/**
  * @brief  Enable HPDMA2  peripheral clock
  * @rmtoll HPDMA2         HPDMA2EN         LL_RCC_HPDMA2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA2_EnableClock(void)
{
  SET_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2EN);
}

/**
  * @brief  Enable HPDMA3  peripheral clock
  * @rmtoll HPDMA3         HPDMA3EN         LL_RCC_HPDMA3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA3_EnableClock(void)
{
  SET_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3EN);
}

#if defined(RCC_ADC1CFGR_ADC1EN) || defined(RCC_ADC2CFGR_ADC2EN)
/**
  * @brief  Enable ADC1  peripheral clock
  * @rmtoll ADC1         ADC1EN         LL_RCC_ADC1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC1_EnableClock(void)
{
  SET_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1EN);
}

/**
  * @brief  Enable ADC2  peripheral clock
  * @rmtoll ADC2         ADC2EN         LL_RCC_ADC2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC2_EnableClock(void)
{
  SET_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2EN);
}
#endif /* RCC_ADC1CFGR_ADC1EN || RCC_ADC2CFGR_ADC2EN*/

#if defined(RCC_ADC3CFGR_ADC3EN)
/**
  * @brief  Enable ADC3  peripheral clock
  * @rmtoll ADC3         ADC3EN         LL_RCC_ADC3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC3_EnableClock(void)
{
  SET_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3EN);
}
#endif /* RCC_ADC3CFGR_ADC3EN */

#if defined(RCC_ADC12CFGR_ADC12EN)
/**
  * @brief  Enable ADC12  peripheral clock
  * @rmtoll ADC12         ADC12EN         LL_RCC_ADC12_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC12_EnableClock(void)
{
  SET_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12EN);
}
#endif /* RCC_ADC12CFGR_ADC12EN */

/**
  * @brief  Enable MDF1  peripheral clock
  * @rmtoll MDF1         MDF1EN         LL_RCC_MDF1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MDF1_EnableClock(void)
{
  SET_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1EN);
}

/**
  * @brief  Enable IPCC1  peripheral clock
  * @rmtoll IPCC1         IPCC1EN         LL_RCC_IPCC1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC1_EnableClock(void)
{
  SET_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1EN);
}

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
/**
  * @brief  Enable DCMIPSSI  peripheral clock
  * @rmtoll DCMIPSSI         DCMIPSSIEN         LL_RCC_DCMIPSSI_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPSSI_EnableClock(void)
{
  SET_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIEN);
}
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIEN */

/**
  * @brief  Enable DCMIPP  peripheral clock
  * @rmtoll DCMIPP         DCMIPPEN         LL_RCC_DCMIPP_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPP_EnableClock(void)
{
  SET_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPEN);
}

/**
  * @brief  Enable CRC  peripheral clock
  * @rmtoll CRC         CRCEN         LL_RCC_CRC_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRC_EnableClock(void)
{
  SET_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCEN);
}

/**
  * @brief  Disable HPDMA1  peripheral clock
  * @rmtoll HPDMA1         HPDMA1EN         LL_RCC_HPDMA1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA1_DisableClock(void)
{
  CLEAR_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1EN);
}

/**
  * @brief  Disable HPDMA2  peripheral clock
  * @rmtoll HPDMA2         HPDMA2EN         LL_RCC_HPDMA2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA2_DisableClock(void)
{
  CLEAR_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2EN);
}

/**
  * @brief  Disable HPDMA3  peripheral clock
  * @rmtoll HPDMA3         HPDMA3EN         LL_RCC_HPDMA3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA3_DisableClock(void)
{
  CLEAR_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3EN);
}

#if defined(RCC_ADC1CFGR_ADC1EN) || defined(RCC_ADC2CFGR_ADC2EN)
/**
  * @brief  Disable ADC1  peripheral clock
  * @rmtoll ADC1         ADC1EN         LL_RCC_ADC1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC1_DisableClock(void)
{
  CLEAR_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1EN);
}

/**
  * @brief  Disable ADC2  peripheral clock
  * @rmtoll ADC2         ADC2EN         LL_RCC_ADC2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC2_DisableClock(void)
{
  CLEAR_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2EN);
}
#endif /* RCC_ADC1CFGR_ADC1EN || RCC_ADC2CFGR_ADC2EN*/

#if defined(RCC_ADC3CFGR_ADC3EN)
/**
  * @brief  Disable ADC3  peripheral clock
  * @rmtoll ADC3         ADC3EN         LL_RCC_ADC3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC3_DisableClock(void)
{
  CLEAR_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3EN);
}
#endif /* RCC_ADC3CFGR_ADC3EN */

#if defined(RCC_ADC12CFGR_ADC12EN)
/**
  * @brief  Disable ADC12  peripheral clock
  * @rmtoll ADC12         ADC12EN         LL_RCC_ADC12_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC12_DisableClock(void)
{
  CLEAR_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12EN);
}
#endif /* RCC_ADC12CFGR_ADC12EN */

/**
  * @brief  Disable MDF1  peripheral clock
  * @rmtoll MDF1         MDF1EN         LL_RCC_MDF1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MDF1_DisableClock(void)
{
  CLEAR_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1EN);
}

/**
  * @brief  Disable IPCC1  peripheral clock
  * @rmtoll IPCC1         IPCC1EN         LL_RCC_IPCC1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC1_DisableClock(void)
{
  CLEAR_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1EN);
}

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIEN)
/**
  * @brief  Disable DCMIPSSI  peripheral clock
  * @rmtoll DCMIPSSI         DCMIPSSIEN         LL_RCC_DCMIPSSI_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPSSI_DisableClock(void)
{
  CLEAR_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIEN);
}
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIEN */

/**
  * @brief  Disable DCMIPP  peripheral clock
  * @rmtoll DCMIPP         DCMIPPEN         LL_RCC_DCMIPP_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPP_DisableClock(void)
{
  CLEAR_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPEN);
}

/**
  * @brief  Disable CRC  peripheral clock
  * @rmtoll CRC         CRCEN         LL_RCC_CRC_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRC_DisableClock(void)
{
  CLEAR_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCEN);
}

/**
  * @brief  Enable HPDMA1 peripheral clocks enable during CSleep mode
  * @rmtoll HPDMA1         HPDMA1LPEN         LL_RCC_HPDMA1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA1_EnableClockSleep(void)
{
  SET_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1LPEN);
}

/**
  * @brief  Enable HPDMA2 peripheral clocks enable during CSleep mode
  * @rmtoll HPDMA2         HPDMA2LPEN         LL_RCC_HPDMA2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA2_EnableClockSleep(void)
{
  SET_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2LPEN);
}

/**
  * @brief  Enable HPDMA3 peripheral clocks enable during CSleep mode
  * @rmtoll HPDMA3         HPDMA3LPEN         LL_RCC_HPDMA3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA3_EnableClockSleep(void)
{
  SET_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3LPEN);
}

#if defined(RCC_ADC1CFGR_ADC1LPEN) || defined(RCC_ADC2CFGR_ADC2LPEN)
/**
  * @brief  Enable ADC1 peripheral clocks enable during CSleep mode
  * @rmtoll ADC1         ADC1LPEN         LL_RCC_ADC1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC1_EnableClockSleep(void)
{
  SET_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1LPEN);
}

/**
  * @brief  Enable ADC2 peripheral clocks enable during CSleep mode
  * @rmtoll ADC2         ADC2LPEN         LL_RCC_ADC2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC2_EnableClockSleep(void)
{
  SET_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2LPEN);
}
#endif /* RCC_ADC1CFGR_ADC1LPEN || RCC_ADC2CFGR_ADC2LPEN*/

#if defined(RCC_ADC3CFGR_ADC3LPEN)
/**
  * @brief  Enable ADC3 peripheral clocks enable during CSleep mode
  * @rmtoll ADC3         ADC3LPEN         LL_RCC_ADC3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC3_EnableClockSleep(void)
{
  SET_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3LPEN);
}
#endif /* RCC_ADC3CFGR_ADC3LPEN */

#if defined(RCC_ADC12CFGR_ADC12LPEN)
/**
  * @brief  Enable ADC12 peripheral clocks enable during CSleep mode
  * @rmtoll ADC12         ADC12LPEN         LL_RCC_ADC12_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC12_EnableClockSleep(void)
{
  SET_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12LPEN);
}
#endif /* RCC_ADC12CFGR_ADC12LPEN */

/**
  * @brief  Enable MDF1 peripheral clocks enable during CSleep mode
  * @rmtoll MDF1         MDF1LPEN         LL_RCC_MDF1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MDF1_EnableClockSleep(void)
{
  SET_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1LPEN);
}

/**
  * @brief  Enable IPCC1 peripheral clocks enable during CSleep mode
  * @rmtoll IPCC1         IPCC1LPEN         LL_RCC_IPCC1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC1_EnableClockSleep(void)
{
  SET_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1LPEN);
}

/**
  * @brief  Enable DCMIPP peripheral clocks enable during CSleep mode
  * @rmtoll DCMIPP         DCMIPPLPEN         LL_RCC_DCMIPP_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPP_EnableClockSleep(void)
{
  SET_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPLPEN);
}

#if defined(RCC_DCMIPSSICFGR_DCMIPSSILPEN)
/**
  * @brief  Enable DCMIPSSI peripheral clocks enable during CSleep mode
  * @rmtoll DCMIPSSI         DCMIPSSILPEN         LL_RCC_DCMIPSSI_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPSSI_EnableClockSleep(void)
{
  SET_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSILPEN);
}
#endif /* RCC_DCMIPSSICFGR_DCMIPSSILPEN */

/**
  * @brief  Enable CRC peripheral clocks enable during CSleep mode
  * @rmtoll CRC         CRCLPEN         LL_RCC_CRC_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRC_EnableClockSleep(void)
{
  SET_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCLPEN);
}

/**
  * @brief  Disable HPDMA1 peripheral clocks during CSleep mode
  * @rmtoll HPDMA1         HPDMA1LPEN         LL_RCC_HPDMA1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1LPEN);
}

/**
  * @brief  Disable HPDMA2 peripheral clocks during CSleep mode
  * @rmtoll HPDMA2         HPDMA2LPEN         LL_RCC_HPDMA2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2LPEN);
}

/**
  * @brief  Disable HPDMA3 peripheral clocks during CSleep mode
  * @rmtoll HPDMA3         HPDMA3LPEN         LL_RCC_HPDMA3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3LPEN);
}

#if defined(RCC_ADC1CFGR_ADC1LPEN) || defined(RCC_ADC2CFGR_ADC2LPEN)
/**
  * @brief  Disable ADC1 peripheral clocks during CSleep mode
  * @rmtoll ADC1         ADC1LPEN         LL_RCC_ADC1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1LPEN);
}


/**
  * @brief  Disable ADC2 peripheral clocks during CSleep mode
  * @rmtoll ADC2         ADC2LPEN         LL_RCC_ADC2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2LPEN);
}
#endif /* RCC_ADC1CFGR_ADC1LPEN || RCC_ADC2CFGR_ADC2LPEN */

#if defined(RCC_ADC3CFGR_ADC3LPEN) || defined(RCC_ADC12CFGR_ADC12LPEN)
/**
  * @brief  Disable ADC3 peripheral clocks during CSleep mode
  * @rmtoll ADC3         ADC3LPEN         LL_RCC_ADC3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3LPEN);
}

/**
  * @brief  Disable ADC12 peripheral clocks during CSleep mode
  * @rmtoll ADC12         ADC12LPEN         LL_RCC_ADC12_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC12_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12LPEN);
}
#endif /* RCC_ADC3CFGR_ADC3LPEN || RCC_ADC12CFGR_ADC12LPEN */
/**
  * @brief  Disable MDF1 peripheral clocks during CSleep mode
  * @rmtoll MDF1         MDF1LPEN         LL_RCC_MDF1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MDF1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1LPEN);
}

/**
  * @brief  Disable IPCC1 peripheral clocks during CSleep mode
  * @rmtoll IPCC1         IPCC1LPEN         LL_RCC_IPCC1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1LPEN);
}

/**
  * @brief  Disable DCMIPP peripheral clocks during CSleep mode
  * @rmtoll DCMIPP         DCMIPPLPEN         LL_RCC_DCMIPP_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPP_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPLPEN);
}

#if defined(RCC_DCMIPSSICFGR_DCMIPSSILPEN)
/**
  * @brief  Disable DCMIPSSI peripheral clocks during CSleep mode
  * @rmtoll DCMIPSSI         DCMIPSSILPEN         LL_RCC_DCMIPSSI_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPSSI_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSILPEN);
}
#endif /* RCC_DCMIPSSICFGR_DCMIPSSILPEN */

/**
  * @brief  Disable CRC peripheral clocks during CSleep mode
  * @rmtoll CRC         CRCLPEN         LL_RCC_CRC_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRC_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCLPEN);
}

/**
  * @brief  Assert HPDMA1 reset
  * @rmtoll HPDMA1         HPDMA1RST         LL_RCC_HPDMA1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA1_ForceReset(void)
{
  SET_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1RST);
}

/**
  * @brief  Assert HPDMA2 reset
  * @rmtoll HPDMA2         HPDMA2RST         LL_RCC_HPDMA2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA2_ForceReset(void)
{
  SET_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2RST);
}

/**
  * @brief  Assert HPDMA3 reset
  * @rmtoll HPDMA3         HPDMA3RST         LL_RCC_HPDMA3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA3_ForceReset(void)
{
  SET_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3RST);
}

#if defined(RCC_ADC1CFGR_ADC1RST) || defined(RCC_ADC2CFGR_ADC2RST)
/**
  * @brief  Assert ADC1 reset
  * @rmtoll ADC1         ADC1RST         LL_RCC_ADC1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC1_ForceReset(void)
{
  SET_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1RST);
}

/**
  * @brief  Assert ADC2 reset
  * @rmtoll ADC2         ADC2RST         LL_RCC_ADC2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC2_ForceReset(void)
{
  SET_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2RST);
}
#endif /* RCC_ADC1CFGR_ADC1RST || RCC_ADC2CFGR_ADC2RST*/

#if defined(RCC_ADC3CFGR_ADC3RST) || defined(RCC_ADC12CFGR_ADC12RST)
/**
  * @brief  Assert ADC3 reset
  * @rmtoll ADC3         ADC3RST         LL_RCC_ADC3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC3_ForceReset(void)
{
  SET_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3RST);
}

/**
  * @brief  Assert ADC12 reset
  * @rmtoll ADC12         ADC12RST         LL_RCC_ADC12_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC12_ForceReset(void)
{
  SET_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12RST);
}
#endif /* RCC_ADC3CFGR_ADC3RST ||  RCC_ADC12CFGR_ADC12RST */

/**
  * @brief  Assert MDF1 reset
  * @rmtoll MDF1         MDF1RST         LL_RCC_MDF1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MDF1_ForceReset(void)
{
  SET_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1RST);
}

/**
  * @brief  Assert IPCC1 reset
  * @rmtoll IPCC1         IPCC1RST         LL_RCC_IPCC1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC1_ForceReset(void)
{
  SET_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1RST);
}

/**
  * @brief  Assert DCMIPP reset
  * @rmtoll DCMIPP         DCMIPPRST         LL_RCC_DCMIPP_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPP_ForceReset(void)
{
  SET_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPRST);
}

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIRST)
/**
  * @brief  Assert DCMIPSSI reset
  * @rmtoll DCMIPSSI         DCMIPSSIRST         LL_RCC_DCMIPSSI_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPSSI_ForceReset(void)
{
  SET_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIRST);
}
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIRST */

/**
  * @brief  Assert CRC reset
  * @rmtoll CRC         CRCRST         LL_RCC_CRC_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRC_ForceReset(void)
{
  SET_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCRST);
}

/**
  * @brief  Release HPDMA1 reset
  * @rmtoll HPDMA1         HPDMA1RST         LL_RCC_HPDMA1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HPDMA1CFGR, RCC_HPDMA1CFGR_HPDMA1RST);
}

/**
  * @brief  Release HPDMA2 reset
  * @rmtoll HPDMA2         HPDMA2RST         LL_RCC_HPDMA2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HPDMA2CFGR, RCC_HPDMA2CFGR_HPDMA2RST);
}

/**
  * @brief  Release HPDMA3 reset
  * @rmtoll HPDMA3         HPDMA3RST         LL_RCC_HPDMA3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HPDMA3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HPDMA3CFGR, RCC_HPDMA3CFGR_HPDMA3RST);
}

#if defined(RCC_ADC1CFGR_ADC1RST) || defined(RCC_ADC2CFGR_ADC2RST)
/**
  * @brief  Release ADC1 reset
  * @rmtoll ADC1         ADC1RST         LL_RCC_ADC1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->ADC1CFGR, RCC_ADC1CFGR_ADC1RST);
}

/**
  * @brief  Release ADC2 reset
  * @rmtoll ADC2         ADC2RST         LL_RCC_ADC2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->ADC2CFGR, RCC_ADC2CFGR_ADC2RST);
}
#endif /* RCC_ADC1CFGR_ADC1RST || RCC_ADC2CFGR_ADC2RST */

#if defined(RCC_ADC3CFGR_ADC3RST) || defined(RCC_ADC12CFGR_ADC12RST)
/**
  * @brief  Release ADC3 reset
  * @rmtoll ADC3         ADC3RST         LL_RCC_ADC3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->ADC3CFGR, RCC_ADC3CFGR_ADC3RST);
}

/**
  * @brief  Release ADC12 reset
  * @rmtoll ADC12         ADC12RST         LL_RCC_ADC12_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADC12_ReleaseReset(void)
{
  CLEAR_BIT(RCC->ADC12CFGR, RCC_ADC12CFGR_ADC12RST);
}
#endif /* RCC_ADC3CFGR_ADC3RST || RCC_ADC12CFGR_ADC12RST */

/**
  * @brief  Release MDF1 reset
  * @rmtoll MDF1         MDF1RST         LL_RCC_MDF1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_MDF1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->MDF1CFGR, RCC_MDF1CFGR_MDF1RST);
}

/**
  * @brief  Release IPCC1 reset
  * @rmtoll IPCC1         IPCC1RST         LL_RCC_IPCC1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->IPCC1CFGR, RCC_IPCC1CFGR_IPCC1RST);
}

/**
  * @brief  Release DCMIPP reset
  * @rmtoll DCMIPP         DCMIPPRST         LL_RCC_DCMIPP_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPP_ReleaseReset(void)
{
  CLEAR_BIT(RCC->DCMIPPCFGR, RCC_DCMIPPCFGR_DCMIPPRST);
}

#if defined(RCC_DCMIPSSICFGR_DCMIPSSIRST)
/**
  * @brief  Release DCMIPSSI reset
  * @rmtoll DCMIPSSI         DCMIPSSIRST         LL_RCC_DCMIPSSI_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_DCMIPSSI_ReleaseReset(void)
{
  CLEAR_BIT(RCC->DCMIPSSICFGR, RCC_DCMIPSSICFGR_DCMIPSSIRST);
}
#endif /* RCC_DCMIPSSICFGR_DCMIPSSIRST */

/**
  * @brief  Release CRC reset
  * @rmtoll CRC         CRCRST         LL_RCC_CRC_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRC_ReleaseReset(void)
{
  CLEAR_BIT(RCC->CRCCFGR, RCC_CRCCFGR_CRCRST);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB3 AHB3
  * @{
  */
/**
  * @brief  Enable SYSRAM  peripheral clock
  * @rmtoll SYSRAM         SYSRAMEN         LL_RCC_SYSRAM_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSRAM_EnableClock(void)
{
  SET_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMEN);
}

/**
  * @brief  Enable PKA  peripheral clock
  * @rmtoll PKA         PKAEN         LL_RCC_PKA_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PKA_EnableClock(void)
{
  SET_BIT(RCC->PKACFGR, RCC_PKACFGR_PKAEN);
}

/**
  * @brief  Enable SAES  peripheral clock
  * @rmtoll SAES         SAESEN         LL_RCC_SAES_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAES_EnableClock(void)
{
  SET_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESEN);
}
#if defined(RCC_CRYP2CFGR_CRYP2EN)
/**
  * @brief  Enable CRYP2  peripheral clock
  * @rmtoll CRYP2         CRYP2EN         LL_RCC_CRYP2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP2_EnableClock(void)
{
  SET_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2EN);
}
#endif /* RCC_CRYP2CFGR_CRYP2EN */

#if defined(RCC_CRYP1CFGR_CRYP1EN)
/**
  * @brief  Enable CRYP1  peripheral clock
  * @rmtoll CRYP1         CRYP1EN         LL_RCC_CRYP1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP1_EnableClock(void)
{
  SET_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1EN);
}
#endif /* RCC_CRYP1CFGR_CRYP1EN */
#if defined(RCC_RNGCFGR_RNGEN)
/**
  * @brief  Enable RNG  peripheral clock
  * @rmtoll RNG         RNGEN         LL_RCC_RNG_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG_EnableClock(void)
{
  SET_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGEN);
}
#endif /* RCC_RNGCFGR_RNGEN */

#if defined(RCC_RNG1CFGR_RNG1EN) || defined(RCC_RNG2CFGR_RNG2EN)
/**
  * @brief  Enable RNG1  peripheral clock
  * @rmtoll RNG1         RNG1EN         LL_RCC_RNG1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG1_EnableClock(void)
{
  SET_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1EN);
}

/**
  * @brief  Enable RNG2  peripheral clock
  * @rmtoll RNG2         RNG2EN         LL_RCC_RNG2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG2_EnableClock(void)
{
  SET_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2EN);
}
#endif /* RCC_RNG1CFGR_RNG1EN || RCC_RNG2CFGR_RNG2EN */

#if defined(RCC_HASHCFGR_HASHEN)
/**
  * @brief  Enable HASH  peripheral clock
  * @rmtoll HASH         HASHEN         LL_RCC_HASH_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH_EnableClock(void)
{
  SET_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHEN);
}
#endif /* RCC_HASHCFGR_HASHEN */

#if defined(RCC_HASH1CFGR_HASH1EN) || defined(RCC_HASH2CFGR_HASH2EN)
/**
  * @brief  Enable HASH1  peripheral clock
  * @rmtoll HASH1         HASH1EN         LL_RCC_HASH1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH1_EnableClock(void)
{
  SET_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1EN);
}

/**
  * @brief  Enable HASH2  peripheral clock
  * @rmtoll HASH2         HASH2EN         LL_RCC_HASH2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH2_EnableClock(void)
{
  SET_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2EN);
}
#endif /* RCC_HASH1CFGR_HASH1EN  || RCC_HASH2CFGR_HASH2EN*/

/**
  * @brief  Enable BKPSRAM  peripheral clock
  * @rmtoll BKPSRAM         BKPSRAMEN         LL_RCC_BKPSRAM_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BKPSRAM_EnableClock(void)
{
  SET_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMEN);
}

/**
  * @brief  Disable SYSRAM  peripheral clock
  * @rmtoll SYSRAM         SYSRAMEN         LL_RCC_SYSRAM_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSRAM_DisableClock(void)
{
  CLEAR_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMEN);
}

/**
  * @brief  Disable PKA  peripheral clock
  * @rmtoll PKA         PKAEN         LL_RCC_PKA_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PKA_DisableClock(void)
{
  CLEAR_BIT(RCC->PKACFGR, RCC_PKACFGR_PKAEN);
}

/**
  * @brief  Disable SAES  peripheral clock
  * @rmtoll SAES         SAESEN         LL_RCC_SAES_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAES_DisableClock(void)
{
  CLEAR_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESEN);
}
#if defined(RCC_CRYP2CFGR_CRYP2EN)
/**
  * @brief  Disable CRYP2  peripheral clock
  * @rmtoll CRYP2         CRYP2EN         LL_RCC_CRYP2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP2_DisableClock(void)
{
  CLEAR_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2EN);
}
#endif /* RCC_CRYP2CFGR_CRYP2EN */

#if defined(RCC_CRYP1CFGR_CRYP1EN)
/**
  * @brief  Disable CRYP1  peripheral clock
  * @rmtoll CRYP1         CRYP1EN         LL_RCC_CRYP1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP1_DisableClock(void)
{
  CLEAR_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1EN);
}
#endif /* RCC_CRYP1CFGR_CRYP1EN */
#if defined(RCC_RNGCFGR_RNGEN)
/**
  * @brief  Disable RNG  peripheral clock
  * @rmtoll RNG         RNGEN         LL_RCC_RNG_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG_DisableClock(void)
{
  CLEAR_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGEN);
}
#endif /* RCC_RNGCFGR_RNGEN */

#if defined(RCC_HASHCFGR_HASHEN)
/**
  * @brief  Disable HASH  peripheral clock
  * @rmtoll HASH         HASHEN         LL_RCC_HASH_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH_DisableClock(void)
{
  CLEAR_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHEN);
}
#endif /* RCC_HASHCFGR_HASHEN */

#if defined(RCC_RNG1CFGR_RNG1EN)
/**
  * @brief  Disable RNG1  peripheral clock
  * @rmtoll RNG1         RNG1EN         LL_RCC_RNG1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG1_DisableClock(void)
{
  CLEAR_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1EN);
}
#endif /* RCC_RNG1CFGR_RNG1EN */

#if defined(RCC_RNG2CFGR_RNG2EN)
/**
  * @brief  Disable RNG2  peripheral clock
  * @rmtoll RNG         RNG2EN         LL_RCC_RNG2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG2_DisableClock(void)
{
  CLEAR_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2EN);
}
#endif /* RCC_RNG2CFGR_RNG2EN */

#if defined(RCC_HASH1CFGR_HASH1EN)
/**
  * @brief  Disable HASH1  peripheral clock
  * @rmtoll HASH1         HASH1EN         LL_RCC_HASH1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH1_DisableClock(void)
{
  CLEAR_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1EN);
}
#endif /*RCC_HASH1CFGR_HASH1EN */

#if defined(RCC_RNG2CFGR_RNG2EN)
/**
  * @brief  Disable HASH2  peripheral clock
  * @rmtoll HASH2         HASH2EN         LL_RCC_HASH2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH2_DisableClock(void)
{
  CLEAR_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2EN);
}
#endif /* RCC_HASH2CFGR_HASH2EN */

/**
  * @brief  Disable BKPSRAM  peripheral clock
  * @rmtoll BKPSRAM         BKPSRAMEN         LL_RCC_BKPSRAM_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BKPSRAM_DisableClock(void)
{
  CLEAR_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMEN);
}

/**
  * @brief  Enable SYSRAM peripheral clocks enable during CSleep mode
  * @rmtoll SYSRAM         SYSRAMLPEN         LL_RCC_SYSRAM_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSRAM_EnableClockSleep(void)
{
  SET_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMLPEN);
}

/**
  * @brief  Enable PKA peripheral clocks enable during CSleep mode
  * @rmtoll PKA         PKALPEN         LL_RCC_PKA_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PKA_EnableClockSleep(void)
{
  SET_BIT(RCC->PKACFGR, RCC_PKACFGR_PKALPEN);
}

/**
  * @brief  Enable SAES peripheral clocks enable during CSleep mode
  * @rmtoll SAES         SAESLPEN         LL_RCC_SAES_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAES_EnableClockSleep(void)
{
  SET_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESLPEN);
}
#if defined(RCC_CRYP2CFGR_CRYP2LPEN)
/**
  * @brief  Enable CRYP2 peripheral clocks enable during CSleep mode
  * @rmtoll CRYP2         CRYP2LPEN         LL_RCC_CRYP2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP2_EnableClockSleep(void)
{
  SET_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2LPEN);
}
#endif /* RCC_CRYP2CFGR_CRYP2LPEN */

#if defined(RCC_CRYP1CFGR_CRYP1LPEN)
/**
  * @brief  Enable CRYP1 peripheral clocks enable during CSleep mode
  * @rmtoll CRYP1         CRYP1LPEN         LL_RCC_CRYP1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP1_EnableClockSleep(void)
{
  SET_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1LPEN);
}
#endif /* RCC_CRYP1CFGR_CRYP1LPEN */

#if defined(RCC_RNGCFGR_RNGLPEN)
/**
  * @brief  Enable RNG peripheral clocks enable during CSleep mode
  * @rmtoll RNG         RNGLPEN         LL_RCC_RNG_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG_EnableClockSleep(void)
{
  SET_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGLPEN);
}
#endif /* RCC_RNGCFGR_RNGLPEN */

#if defined(RCC_RNG1CFGR_RNG1LPEN)
/**
  * @brief  Enable RNG1 peripheral clocks enable during CSleep mode
  * @rmtoll RNG         RNG1LPEN         LL_RCC_RNG1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG1_EnableClockSleep(void)
{
  SET_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1LPEN);
}
#endif /* RCC_RNG1CFGR_RNG1LPEN */

#if defined(RCC_RNG2CFGR_RNG2LPEN)
/**
  * @brief  Enable RNG2 peripheral clocks enable during CSleep mode
  * @rmtoll RNG2         RNG2LPEN         LL_RCC_RNG2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG2_EnableClockSleep(void)
{
  SET_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2LPEN);
}
#endif /* RCC_RNG2CFGR_RNG2LPEN */

#if defined(RCC_HASHCFGR_HASHLPEN)
/**
  * @brief  Enable HASH peripheral clocks enable during CSleep mode
  * @rmtoll HASH         HASHLPEN         LL_RCC_HASH_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH_EnableClockSleep(void)
{
  SET_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHLPEN);
}
#endif /* RCC_HASHCFGR_HASHLPEN */

#if defined(RCC_HASH1CFGR_HASH1LPEN)
/**
  * @brief  Enable HASH1 peripheral clocks enable during CSleep mode
  * @rmtoll HASH1         HASH1LPEN         LL_RCC_HASH1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH1_EnableClockSleep(void)
{
  SET_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1LPEN);
}
#endif /* RCC_HASH1CFGR_HASH1LPEN */

#if defined(RCC_HASH2CFGR_HASH2LPEN)
/**
  * @brief  Enable HASH2 peripheral clocks enable during CSleep mode
  * @rmtoll HASH2         HASH2LPEN         LL_RCC_HASH2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH2_EnableClockSleep(void)
{
  SET_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2LPEN);
}
#endif /* RCC_HASH2CFGR_HASH2LPEN */

/**
  * @brief  Enable BKPSRAM peripheral clocks enable during CSleep mode
  * @rmtoll BKPSRAM         BKPSRAMLPEN         LL_RCC_BKPSRAM_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BKPSRAM_EnableClockSleep(void)
{
  SET_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMLPEN);
}

/**
  * @brief  Disable SYSRAM peripheral clocks during CSleep mode
  * @rmtoll SYSRAM         SYSRAMLPEN         LL_RCC_SYSRAM_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSRAM_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SYSRAMCFGR, RCC_SYSRAMCFGR_SYSRAMLPEN);
}

/**
  * @brief  Disable PKA peripheral clocks during CSleep mode
  * @rmtoll PKA         PKALPEN         LL_RCC_PKA_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PKA_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->PKACFGR, RCC_PKACFGR_PKALPEN);
}

/**
  * @brief  Disable SAES peripheral clocks during CSleep mode
  * @rmtoll SAES         SAESLPEN         LL_RCC_SAES_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAES_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESLPEN);
}

#if defined(RCC_CRYP2CFGR_CRYP2LPEN)
/**
  * @brief  Disable CRYP2 peripheral clocks during CSleep mode
  * @rmtoll CRYP2         CRYP2LPEN         LL_RCC_CRYP2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2LPEN);
}
#endif /* RCC_CRYP2CFGR_CRYP2LPEN */

#if defined(RCC_CRYP1CFGR_CRYP1LPEN)
/**
  * @brief  Disable CRYP1 peripheral clocks during CSleep mode
  * @rmtoll CRYP1         CRYP1LPEN         LL_RCC_CRYP1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1LPEN);
}
#endif /* RCC_CRYP1CFGR_CRYP1LPEN */

#if defined(RCC_RNGCFGR_RNGLPEN)
/**
  * @brief  Disable RNG peripheral clocks during CSleep mode
  * @rmtoll RNG         RNGLPEN         LL_RCC_RNG_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGLPEN);
}
#endif /* RCC_RNGCFGR_RNGLPEN  */

#if defined(RCC_RNG1CFGR_RNG1LPEN)
/**
  * @brief  Disable RNG1 peripheral clocks during CSleep mode
  * @rmtoll RNG1         RNG1LPEN         LL_RCC_RNG1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1LPEN);
}
#endif /* RCC_RNG1CFGR_RNG1LPEN  */

#if defined(RCC_RNG2CFGR_RNG2LPEN)
/**
  * @brief  Disable RNG2 peripheral clocks during CSleep mode
  * @rmtoll RNG2         RNG2LPEN         LL_RCC_RNG2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2LPEN);
}
#endif /* RCC_RNG2CFGR_RNG2LPEN  */

#if defined(RCC_HASHCFGR_HASHLPEN)
/**
  * @brief  Disable HASH peripheral clocks during CSleep mode
  * @rmtoll HASH         HASHLPEN         LL_RCC_HASH_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHLPEN);
}
#endif /* RCC_HASHCFGR_HASHLPEN  */

#if defined(RCC_HASH2CFGR_HASH2LPEN)
/**
  * @brief  Disable HASH2 peripheral clocks during CSleep mode
  * @rmtoll HASH2         HASH2LPEN         LL_RCC_HASH2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2LPEN);
}
#endif /* RCC_HASH2CFGR_HASH2LPEN  */

#if defined(RCC_HASH1CFGR_HASH1LPEN)
/**
  * @brief  Disable HASH1 peripheral clocks during CSleep mode
  * @rmtoll HASH1         HASH1LPEN         LL_RCC_HASH1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1LPEN);
}
#endif /*  RCC_HASH1CFGR_HASH1LPEN */

/**
  * @brief  Disable BKPSRAM peripheral clocks during CSleep mode
  * @rmtoll BKPSRAM         BKPSRAMLPEN         LL_RCC_BKPSRAM_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BKPSRAM_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->BKPSRAMCFGR, RCC_BKPSRAMCFGR_BKPSRAMLPEN);
}

/**
  * @brief  Assert PKA reset
  * @rmtoll PKA         PKARST         LL_RCC_PKA_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PKA_ForceReset(void)
{
  SET_BIT(RCC->PKACFGR, RCC_PKACFGR_PKARST);
}

/**
  * @brief  Assert SAES reset
  * @rmtoll SAES         SAESRST         LL_RCC_SAES_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAES_ForceReset(void)
{
  SET_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESRST);
}
#if defined(RCC_CRYP2CFGR_CRYP2RST)
/**
  * @brief  Assert CRYP2 reset
  * @rmtoll CRYP2         CRYP2RST         LL_RCC_CRYP2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP2_ForceReset(void)
{
  SET_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2RST);
}
#endif /* RCC_CRYP2CFGR_CRYP2RST */

#if defined(RCC_CRYP1CFGR_CRYP1RST)
/**
  * @brief  Assert CRYP1 reset
  * @rmtoll CRYP1         CRYP1RST         LL_RCC_CRYP1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP1_ForceReset(void)
{
  SET_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1RST);
}
#endif /* RCC_CRYP1CFGR_CRYP1RST */
#if defined(RCC_RNGCFGR_RNGRST)
/**
  * @brief  Assert RNG reset
  * @rmtoll RNG         RNGRST         LL_RCC_RNG_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG_ForceReset(void)
{
  SET_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGRST);
}
#endif /* RCC_RNGCFGR_RNGRST */

#if defined(RCC_RNG1CFGR_RNG1RST)
/**
  * @brief  Assert RNG1 reset
  * @rmtoll RNG1         RNG1RST         LL_RCC_RNG1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG1_ForceReset(void)
{
  SET_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1RST);
}
#endif /* RCC_RNG1CFGR_RNG1RST */

#if defined(RCC_RNG2CFGR_RNG2RST)
/**
  * @brief  Assert RNG2 reset
  * @rmtoll RNG2         RNG2RST         LL_RCC_RNG2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG2_ForceReset(void)
{
  SET_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2RST);
}
#endif /* RCC_RNG2CFGR_RNG2RST */

#if defined(RCC_HASHCFGR_HASHRST)
/**
  * @brief  Assert HASH reset
  * @rmtoll HASH         HASHRST         LL_RCC_HASH_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH_ForceReset(void)
{
  SET_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHRST);
}
#endif /* RCC_HASHCFGR_HASHRST */

#if defined(RCC_HASH1CFGR_HASH1RST)
/**
  * @brief  Assert HASH1 reset
  * @rmtoll HASH1         HASH1RST         LL_RCC_HASH1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH1_ForceReset(void)
{
  SET_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1RST);
}
#endif /* RCC_HASH1CFGR_HASH1RST */

#if defined(RCC_HASH2CFGR_HASH2RST)
/**
  * @brief  Assert HASH2 reset
  * @rmtoll HASH2         HASH2RST         LL_RCC_HASH2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH2_ForceReset(void)
{
  SET_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2RST);
}
#endif /* RCC_HASH2CFGR_HASH2RST */

/**
  * @brief  Release PKA reset
  * @rmtoll PKA         PKARST         LL_RCC_PKA_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PKA_ReleaseReset(void)
{
  CLEAR_BIT(RCC->PKACFGR, RCC_PKACFGR_PKARST);
}

/**
  * @brief  Release SAES reset
  * @rmtoll SAES         SAESRST         LL_RCC_SAES_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAES_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SAESCFGR, RCC_SAESCFGR_SAESRST);
}
#if defined(RCC_CRYP2CFGR_CRYP2RST)
/**
  * @brief  Release CRYP2 reset
  * @rmtoll CRYP2         CRYP2RST         LL_RCC_CRYP2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->CRYP2CFGR, RCC_CRYP2CFGR_CRYP2RST);
}
#endif /* RCC_CRYP2CFGR_CRYP2RST */

#if defined(RCC_CRYP1CFGR_CRYP1RST)
/**
  * @brief  Release CRYP1 reset
  * @rmtoll CRYP1         CRYP1RST         LL_RCC_CRYP1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CRYP1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->CRYP1CFGR, RCC_CRYP1CFGR_CRYP1RST);
}
#endif /* RCC_CRYP1CFGR_CRYP1RST */
#if defined(RCC_RNGCFGR_RNGRST)
/**
  * @brief  Release RNG reset
  * @rmtoll RNG         RNGRST         LL_RCC_RNG_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG_ReleaseReset(void)
{
  CLEAR_BIT(RCC->RNGCFGR, RCC_RNGCFGR_RNGRST);
}
#endif /* RCC_RNGCFGR_RNGRST */

#if defined(RCC_RNG1CFGR_RNG1RST)
/**
  * @brief  Release RNG1 reset
  * @rmtoll RNG1         RNG1RST         LL_RCC_RNG1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->RNG1CFGR, RCC_RNG1CFGR_RNG1RST);
}
#endif /* RCC_RNG1CFGR_RNG1RST */

#if defined(RCC_RNG2CFGR_RNG2RST)
/**
  * @brief  Release RNG2 reset
  * @rmtoll RNG2         RNG2RST         LL_RCC_RNG2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RNG2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->RNG2CFGR, RCC_RNG2CFGR_RNG2RST);
}
#endif /* RCC_RNG2CFGR_RNG2RST */

#if defined(RCC_HASHCFGR_HASHRST)
/**
  * @brief  Release HASH reset
  * @rmtoll HASH         HASHRST         LL_RCC_HASH_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HASHCFGR, RCC_HASHCFGR_HASHRST);
}
#endif /* RCC_HASHCFGR_HASHRST */

#if defined(RCC_HASH1CFGR_HASH1RST)
/**
  * @brief  Release HASH1 reset
  * @rmtoll HASH1         HASH1RST         LL_RCC_HASH1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HASH1CFGR, RCC_HASH1CFGR_HASH1RST);
}
#endif /* RCC_HASH1CFGR_HASH1RST */

#if defined(RCC_HASH2CFGR_HASH2RST)
/**
  * @brief  Release HASH2 reset
  * @rmtoll HASH2         HASH2RST         LL_RCC_HASH2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HASH2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HASH2CFGR, RCC_HASH2CFGR_HASH2RST);
}
#endif /* RCC_HASH2CFGR_HASH2RST */

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB4 AHB4
  * @{
  */
#if defined(RCC_GPIOKCFGR_GPIOxEN)
/**
  * @brief  Enable GPIOK  peripheral clock
  * @rmtoll GPIOK         GPIOKEN         LL_RCC_GPIOK_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOK_EnableClock(void)
{
  SET_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxEN);
}
#endif /* RCC_GPIOKCFGR_GPIOxEN */

#if defined(RCC_GPIOJCFGR_GPIOxEN)
/**
  * @brief  Enable GPIOJ  peripheral clock
  * @rmtoll GPIOJ         GPIOJEN         LL_RCC_GPIOJ_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOJ_EnableClock(void)
{
  SET_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxEN);
}
#endif /* RCC_GPIOJCFGR_GPIOxEN */

/**
  * @brief  Enable GPIOI  peripheral clock
  * @rmtoll GPIOI         GPIOIEN         LL_RCC_GPIOI_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOI_EnableClock(void)
{
  SET_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOH  peripheral clock
  * @rmtoll GPIOH         GPIOHEN         LL_RCC_GPIOH_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOH_EnableClock(void)
{
  SET_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOG  peripheral clock
  * @rmtoll GPIOG         GPIOGEN         LL_RCC_GPIOG_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOG_EnableClock(void)
{
  SET_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOF  peripheral clock
  * @rmtoll GPIOF         GPIOFEN         LL_RCC_GPIOF_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOF_EnableClock(void)
{
  SET_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOE  peripheral clock
  * @rmtoll GPIOE         GPIOEEN         LL_RCC_GPIOE_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOE_EnableClock(void)
{
  SET_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOD  peripheral clock
  * @rmtoll GPIOD         GPIODEN         LL_RCC_GPIOD_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOD_EnableClock(void)
{
  SET_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOC  peripheral clock
  * @rmtoll GPIOC         GPIOCEN         LL_RCC_GPIOC_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOC_EnableClock(void)
{
  SET_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOB  peripheral clock
  * @rmtoll GPIOB         GPIOBEN         LL_RCC_GPIOB_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOB_EnableClock(void)
{
  SET_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxEN);
}

/**
  * @brief  Enable GPIOA  peripheral clock
  * @rmtoll GPIOA         GPIOAEN         LL_RCC_GPIOA_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOA_EnableClock(void)
{
  SET_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxEN);
}

#if defined(RCC_GPIOKCFGR_GPIOxEN)
/**
  * @brief  Disable GPIOK  peripheral clock
  * @rmtoll GPIOK         GPIOKEN         LL_RCC_GPIOK_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOK_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxEN);
}
#endif /* RCC_GPIOKCFGR_GPIOxEN */

#if defined(RCC_GPIOJCFGR_GPIOxEN)

/**
  * @brief  Disable GPIOJ  peripheral clock
  * @rmtoll GPIOJ         GPIOJEN         LL_RCC_GPIOJ_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOJ_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxEN);
}
#endif /* RCC_GPIOJCFGR_GPIOxEN */

/**
  * @brief  Disable GPIOI  peripheral clock
  * @rmtoll GPIOI         GPIOIEN         LL_RCC_GPIOI_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOI_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOH  peripheral clock
  * @rmtoll GPIOH         GPIOHEN         LL_RCC_GPIOH_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOH_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOG  peripheral clock
  * @rmtoll GPIOG         GPIOGEN         LL_RCC_GPIOG_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOG_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOF  peripheral clock
  * @rmtoll GPIOF         GPIOFEN         LL_RCC_GPIOF_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOF_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOE  peripheral clock
  * @rmtoll GPIOE         GPIOEEN         LL_RCC_GPIOE_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOE_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOD  peripheral clock
  * @rmtoll GPIOD         GPIODEN         LL_RCC_GPIOD_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOD_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOC  peripheral clock
  * @rmtoll GPIOC         GPIOCEN         LL_RCC_GPIOC_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOC_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOB  peripheral clock
  * @rmtoll GPIOB         GPIOBEN         LL_RCC_GPIOB_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOB_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxEN);
}

/**
  * @brief  Disable GPIOA  peripheral clock
  * @rmtoll GPIOA         GPIOAEN         LL_RCC_GPIOA_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOA_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxEN);
}

#if defined(RCC_GPIOKCFGR_GPIOxLPEN)
/**
  * @brief  Enable GPIOK peripheral clocks enable during CSleep mode
  * @rmtoll GPIOK         GPIOKLPEN         LL_RCC_GPIOK_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOK_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxLPEN);
}
#endif /* RCC_GPIOKCFGR_GPIOxLPEN */

#if defined(RCC_GPIOJCFGR_GPIOxLPEN)
/**
  * @brief  Enable GPIOJ peripheral clocks enable during CSleep mode
  * @rmtoll GPIOJ         GPIOJLPEN         LL_RCC_GPIOJ_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOJ_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxLPEN);
}
#endif /* RCC_GPIOJCFGR_GPIOxLPEN */

/**
  * @brief  Enable GPIOI peripheral clocks enable during CSleep mode
  * @rmtoll GPIOI         GPIOILPEN         LL_RCC_GPIOI_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOI_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOH peripheral clocks enable during CSleep mode
  * @rmtoll GPIOH         GPIOHLPEN         LL_RCC_GPIOH_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOH_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOG peripheral clocks enable during CSleep mode
  * @rmtoll GPIOG         GPIOGLPEN         LL_RCC_GPIOG_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOG_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOF peripheral clocks enable during CSleep mode
  * @rmtoll GPIOF         GPIOFLPEN         LL_RCC_GPIOF_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOF_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOE peripheral clocks enable during CSleep mode
  * @rmtoll GPIOE         GPIOELPEN         LL_RCC_GPIOE_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOE_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOD peripheral clocks enable during CSleep mode
  * @rmtoll GPIOD         GPIODLPEN         LL_RCC_GPIOD_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOD_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOC peripheral clocks enable during CSleep mode
  * @rmtoll GPIOC         GPIOCLPEN         LL_RCC_GPIOC_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOC_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOB peripheral clocks enable during CSleep mode
  * @rmtoll GPIOB         GPIOBLPEN         LL_RCC_GPIOB_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOB_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxLPEN);
}

/**
  * @brief  Enable GPIOA peripheral clocks enable during CSleep mode
  * @rmtoll GPIOA         GPIOALPEN         LL_RCC_GPIOA_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOA_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxLPEN);
}

#if defined(RCC_GPIOKCFGR_GPIOxLPEN)
/**
  * @brief  Disable GPIOK peripheral clocks during CSleep mode
  * @rmtoll GPIOK         GPIOKLPEN         LL_RCC_GPIOK_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOK_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxLPEN);
}
#endif /* RCC_GPIOKCFGR_GPIOxLPEN */

#if defined(RCC_GPIOJCFGR_GPIOxLPEN)
/**
  * @brief  Disable GPIOJ peripheral clocks during CSleep mode
  * @rmtoll GPIOJ         GPIOJLPEN         LL_RCC_GPIOJ_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOJ_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxLPEN);
}
#endif /* RCC_GPIOJCFGR_GPIOxLPEN */

/**
  * @brief  Disable GPIOI peripheral clocks during CSleep mode
  * @rmtoll GPIOI         GPIOILPEN         LL_RCC_GPIOI_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOI_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOH peripheral clocks during CSleep mode
  * @rmtoll GPIOH         GPIOHLPEN         LL_RCC_GPIOH_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOH_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOG peripheral clocks during CSleep mode
  * @rmtoll GPIOG         GPIOGLPEN         LL_RCC_GPIOG_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOG_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOF peripheral clocks during CSleep mode
  * @rmtoll GPIOF         GPIOFLPEN         LL_RCC_GPIOF_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOF_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOE peripheral clocks during CSleep mode
  * @rmtoll GPIOE         GPIOELPEN         LL_RCC_GPIOE_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOE_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOD peripheral clocks during CSleep mode
  * @rmtoll GPIOD         GPIODLPEN         LL_RCC_GPIOD_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOD_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOC peripheral clocks during CSleep mode
  * @rmtoll GPIOC         GPIOCLPEN         LL_RCC_GPIOC_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOC_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOB peripheral clocks during CSleep mode
  * @rmtoll GPIOB         GPIOBLPEN         LL_RCC_GPIOB_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOB_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxLPEN);
}

/**
  * @brief  Disable GPIOA peripheral clocks during CSleep mode
  * @rmtoll GPIOA         GPIOALPEN         LL_RCC_GPIOA_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOA_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxLPEN);
}

#if defined(RCC_GPIOKCFGR_GPIOxRST)
/**
  * @brief  Assert GPIOK reset
  * @rmtoll GPIOK         GPIOKRST         LL_RCC_GPIOK_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOK_ForceReset(void)
{
  SET_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxRST);
}
#endif /* RCC_GPIOKCFGR_GPIOxRST */

#if defined(RCC_GPIOJCFGR_GPIOxRST)
/**
  * @brief  Assert GPIOJ reset
  * @rmtoll GPIOJ         GPIOJRST         LL_RCC_GPIOJ_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOJ_ForceReset(void)
{
  SET_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxRST);
}
#endif /* RCC_GPIOJCFGR_GPIOxRST */

/**
  * @brief  Assert GPIOI reset
  * @rmtoll GPIOI         GPIOIRST         LL_RCC_GPIOI_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOI_ForceReset(void)
{
  SET_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOH reset
  * @rmtoll GPIOH         GPIOHRST         LL_RCC_GPIOH_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOH_ForceReset(void)
{
  SET_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOG reset
  * @rmtoll GPIOG         GPIOGRST         LL_RCC_GPIOG_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOG_ForceReset(void)
{
  SET_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOF reset
  * @rmtoll GPIOF         GPIOFRST         LL_RCC_GPIOF_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOF_ForceReset(void)
{
  SET_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOE reset
  * @rmtoll GPIOE         GPIOERST         LL_RCC_GPIOE_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOE_ForceReset(void)
{
  SET_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOD reset
  * @rmtoll GPIOD         GPIODRST         LL_RCC_GPIOD_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOD_ForceReset(void)
{
  SET_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOC reset
  * @rmtoll GPIOC         GPIOCRST         LL_RCC_GPIOC_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOC_ForceReset(void)
{
  SET_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOB reset
  * @rmtoll GPIOB         GPIOBRST         LL_RCC_GPIOB_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOB_ForceReset(void)
{
  SET_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxRST);
}

/**
  * @brief  Assert GPIOA reset
  * @rmtoll GPIOA         GPIOARST         LL_RCC_GPIOA_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOA_ForceReset(void)
{
  SET_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxRST);
}

#if defined(RCC_GPIOKCFGR_GPIOxRST)
/**
  * @brief  Release GPIOK reset
  * @rmtoll GPIOK         GPIOKRST         LL_RCC_GPIOK_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOK_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOKCFGR, RCC_GPIOKCFGR_GPIOxRST);
}
#endif /* RCC_GPIOKCFGR_GPIOxRST */

#if defined(RCC_GPIOJCFGR_GPIOxRST)
/**
  * @brief  Release GPIOJ reset
  * @rmtoll GPIOJ         GPIOJRST         LL_RCC_GPIOJ_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOJ_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOJCFGR, RCC_GPIOJCFGR_GPIOxRST);
}
#endif /* RCC_GPIOJCFGR_GPIOxRST */

/**
  * @brief  Release GPIOI reset
  * @rmtoll GPIOI         GPIOIRST         LL_RCC_GPIOI_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOI_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOICFGR, RCC_GPIOICFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOH reset
  * @rmtoll GPIOH         GPIOHRST         LL_RCC_GPIOH_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOH_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOHCFGR, RCC_GPIOHCFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOG reset
  * @rmtoll GPIOG         GPIOGRST         LL_RCC_GPIOG_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOG_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOGCFGR, RCC_GPIOGCFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOF reset
  * @rmtoll GPIOF         GPIOFRST         LL_RCC_GPIOF_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOF_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOFCFGR, RCC_GPIOFCFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOE reset
  * @rmtoll GPIOE         GPIOERST         LL_RCC_GPIOE_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOE_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOECFGR, RCC_GPIOECFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOD reset
  * @rmtoll GPIOD         GPIODRST         LL_RCC_GPIOD_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOD_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIODCFGR, RCC_GPIODCFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOC reset
  * @rmtoll GPIOC         GPIOCRST         LL_RCC_GPIOC_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOC_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOCCFGR, RCC_GPIOCCFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOB reset
  * @rmtoll GPIOB         GPIOBRST         LL_RCC_GPIOB_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOB_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOBCFGR, RCC_GPIOBCFGR_GPIOxRST);
}

/**
  * @brief  Release GPIOA reset
  * @rmtoll GPIOA         GPIOARST         LL_RCC_GPIOA_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOA_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOACFGR, RCC_GPIOACFGR_GPIOxRST);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB5 AHB5
  * @{
  */
/**
  * @brief  Enable SDMMC1  peripheral clock
  * @rmtoll SDMMC1         SDMMC1EN         LL_RCC_SDMMC1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC1_EnableClock(void)
{
  SET_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1EN);
}

/**
  * @brief  Enable SDMMC2  peripheral clock
  * @rmtoll SDMMC2         SDMMC2EN         LL_RCC_SDMMC2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC2_EnableClock(void)
{
  SET_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2EN);
}

/**
  * @brief  Enable SDMMC3  peripheral clock
  * @rmtoll SDMMC3         SDMMC3EN         LL_RCC_SDMMC3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC3_EnableClock(void)
{
  SET_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3EN);
}

#if defined(RCC_USB3DRDCFGR_USB3DRDEN)
/**
  * @brief  Enable USB3DRD  peripheral clock
  * @rmtoll USB3DRD         USB3DRDEN         LL_RCC_USB3DRD_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3DRD_EnableClock(void)
{
  SET_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDEN);
}
#endif /* RCC_USB3DRDCFGR_USB3DRDEN */


/**
  * @brief  Enable USB2PHY  peripheral clock
  * @rmtoll USB2PHY         USB2PHYEN         LL_RCC_USB2PHY_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY1_EnableClock(void)
{
  SET_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1EN);
}

/**
  * @brief  Enable USB2PHY  peripheral clock
  * @rmtoll USB2PHY         USB2PHYEN         LL_RCC_USB2PHY_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY2_EnableClock(void)
{
  SET_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2EN);
}

/**
  * @brief  Enable FMC  peripheral clock
  * @rmtoll FMC         FMCEN         LL_RCC_FMC_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FMC_EnableClock(void)
{
  SET_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCEN);
}

/**
  * @brief  Enable ETH1  peripheral clock
  * @rmtoll ETH1         ETH1EN         LL_RCC_ETH1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH1_EnableClock(void)
{
  SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1EN);
}

/**
  * @brief  Enable ETH2  peripheral clock
  * @rmtoll ETH2         ETH2EN         LL_RCC_ETH2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH2_EnableClock(void)
{
  SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2EN);
}
#if defined(RCC_GPUCFGR_GPUEN)
/**
  * @brief  Enable GPU  peripheral clock
  * @rmtoll GPU         GPUEN         LL_RCC_GPU_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPU_EnableClock(void)
{
  SET_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPUEN);
}
#endif /* RCC_GPUCFGR_GPUEN */
/**
  * @brief  Disable SDMMC1  peripheral clock
  * @rmtoll SDMMC1         SDMMC1EN         LL_RCC_SDMMC1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC1_DisableClock(void)
{
  CLEAR_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1EN);
}

/**
  * @brief  Disable SDMMC2  peripheral clock
  * @rmtoll SDMMC2         SDMMC2EN         LL_RCC_SDMMC2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC2_DisableClock(void)
{
  CLEAR_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2EN);
}

/**
  * @brief  Disable SDMMC3  peripheral clock
  * @rmtoll SDMMC3         SDMMC3EN         LL_RCC_SDMMC3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC3_DisableClock(void)
{
  CLEAR_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3EN);
}

#if defined(RCC_USB3DRDCFGR_USB3DRDEN)
/**
  * @brief  Disable USB3DRD  peripheral clock
  * @rmtoll USB3DRD         USB3DRDEN         LL_RCC_USB3DRD_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3DRD_DisableClock(void)
{
  CLEAR_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDEN);
}
#endif /* RCC_USB3DRDCFGR_USB3DRDEN */


/**
  * @brief  Disable USB2PHY  peripheral clock
  * @rmtoll USB2PHY         USB2PHYEN         LL_RCC_USB2PHY_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY1_DisableClock(void)
{
  CLEAR_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1EN);
}

/**
  * @brief  Disable USB2PHY  peripheral clock
  * @rmtoll USB2PHY         USB2PHYEN         LL_RCC_USB2PHY_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY2_DisableClock(void)
{
  CLEAR_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2EN);
}

/**
  * @brief  Disable FMC  peripheral clock
  * @rmtoll FMC         FMCEN         LL_RCC_FMC_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FMC_DisableClock(void)
{
  CLEAR_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCEN);
}

/**
  * @brief  Disable ETH1  peripheral clock
  * @rmtoll ETH1         ETH1EN         LL_RCC_ETH1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH1_DisableClock(void)
{
  CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1EN);
}

/**
  * @brief  Disable ETH2  peripheral clock
  * @rmtoll ETH2         ETH2EN         LL_RCC_ETH2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH2_DisableClock(void)
{
  CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2EN);
}
#if defined(RCC_GPUCFGR_GPUEN)
/**
  * @brief  Disable GPU  peripheral clock
  * @rmtoll GPU         GPUEN         LL_RCC_GPU_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPU_DisableClock(void)
{
  CLEAR_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPUEN);
}
#endif /* RCC_GPUCFGR_GPUEN */
/**
  * @brief  Enable SDMMC1 peripheral clocks enable during CSleep mode
  * @rmtoll SDMMC1         SDMMC1LPEN         LL_RCC_SDMMC1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC1_EnableClockSleep(void)
{
  SET_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1LPEN);
}

/**
  * @brief  Enable SDMMC2 peripheral clocks enable during CSleep mode
  * @rmtoll SDMMC2         SDMMC2LPEN         LL_RCC_SDMMC2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC2_EnableClockSleep(void)
{
  SET_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2LPEN);
}

/**
  * @brief  Enable SDMMC3 peripheral clocks enable during CSleep mode
  * @rmtoll SDMMC3         SDMMC3LPEN         LL_RCC_SDMMC3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC3_EnableClockSleep(void)
{
  SET_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3LPEN);
}

#if defined(RCC_USB3DRDCFGR_USB3DRDLPEN)
/**
  * @brief  Enable USB3DRD peripheral clocks enable during CSleep mode
  * @rmtoll USB3DRD         USB3DRDLPEN         LL_RCC_USB3DRD_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3DRD_EnableClockSleep(void)
{
  SET_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDLPEN);
}
#endif /* RCC_USB3DRDCFGR_USB3DRDLPEN */


/**
  * @brief  Enable USB2PHY peripheral clocks enable during CSleep mode
  * @rmtoll USB2PHY         USB2PHYLPEN         LL_RCC_USB2PHY_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY1_EnableClockSleep(void)
{
  SET_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1LPEN);
}

/**
  * @brief  Enable USB2PHY peripheral clocks enable during CSleep mode
  * @rmtoll USB2PHY         USB2PHYLPEN         LL_RCC_USB2PHY_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY2_EnableClockSleep(void)
{
  SET_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2LPEN);
}

/**
  * @brief  Enable FMC peripheral clocks enable during CSleep mode
  * @rmtoll FMC         FMCLPEN         LL_RCC_FMC_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FMC_EnableClockSleep(void)
{
  SET_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCLPEN);
}

/**
  * @brief  Enable ETH1 peripheral clocks enable during CSleep mode
  * @rmtoll ETH1         ETH1LPEN         LL_RCC_ETH1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH1_EnableClockSleep(void)
{
  SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1LPEN);
}

/**
  * @brief  Enable ETH2 peripheral clocks enable during CSleep mode
  * @rmtoll ETH2         ETH2LPEN         LL_RCC_ETH2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH2_EnableClockSleep(void)
{
  SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2LPEN);
}
#if defined(RCC_GPUCFGR_GPULPEN)
/**
  * @brief  Enable GPU peripheral clocks enable during CSleep mode
  * @rmtoll GPU         GPULPEN         LL_RCC_GPU_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPU_EnableClockSleep(void)
{
  SET_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPULPEN);
}
#endif /* RCC_GPUCFGR_GPULPEN */
/**
  * @brief  Disable SDMMC1 peripheral clocks during CSleep mode
  * @rmtoll SDMMC1         SDMMC1LPEN         LL_RCC_SDMMC1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1LPEN);
}

/**
  * @brief  Disable SDMMC2 peripheral clocks during CSleep mode
  * @rmtoll SDMMC2         SDMMC2LPEN         LL_RCC_SDMMC2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2LPEN);
}

/**
  * @brief  Disable SDMMC3 peripheral clocks during CSleep mode
  * @rmtoll SDMMC3         SDMMC3LPEN         LL_RCC_SDMMC3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3LPEN);
}

#if defined(RCC_USB3DRDCFGR_USB3DRDLPEN)
/**
  * @brief  Disable USB3DRD peripheral clocks during CSleep mode
  * @rmtoll USB3DRD         USB3DRDLPEN         LL_RCC_USB3DRD_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3DRD_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDLPEN);
}
#endif /* RCC_USB3DRDCFGR_USB3DRDLPEN */

/**
  * @brief  Disable USB2PHY peripheral clocks during CSleep mode
  * @rmtoll USB2PHY         USB2PHYLPEN         LL_RCC_USB2PHY_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1LPEN);
}

/**
  * @brief  Disable USB2PHY peripheral clocks during CSleep mode
  * @rmtoll USB2PHY         USB2PHYLPEN         LL_RCC_USB2PHY_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2LPEN);
}

/**
  * @brief  Disable FMC peripheral clocks during CSleep mode
  * @rmtoll FMC         FMCLPEN         LL_RCC_FMC_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FMC_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCLPEN);
}

/**
  * @brief  Disable ETH1 peripheral clocks during CSleep mode
  * @rmtoll ETH1         ETH1LPEN         LL_RCC_ETH1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1LPEN);
}

/**
  * @brief  Disable ETH2 peripheral clocks during CSleep mode
  * @rmtoll ETH2         ETH2LPEN         LL_RCC_ETH2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2LPEN);
}
#if defined(RCC_GPUCFGR_GPULPEN)
/**
  * @brief  Disable GPU peripheral clocks during CSleep mode
  * @rmtoll GPU         GPULPEN         LL_RCC_GPU_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPU_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPULPEN);
}
#endif /* RCC_GPUCFGR_GPULPEN */
/**
  * @brief  Assert SDMMC1 reset
  * @rmtoll SDMMC1         SDMMC1RST         LL_RCC_SDMMC1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC1_ForceReset(void)
{
  SET_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1RST);
}

/**
  * @brief  Assert SDMMC2 reset
  * @rmtoll SDMMC2         SDMMC2RST         LL_RCC_SDMMC2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC2_ForceReset(void)
{
  SET_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2RST);
}

/**
  * @brief  Assert SDMMC3 reset
  * @rmtoll SDMMC3         SDMMC3RST         LL_RCC_SDMMC3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC3_ForceReset(void)
{
  SET_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3RST);
}

#if defined(RCC_USB3DRDCFGR_USB3DRDRST)
/**
  * @brief  Assert USB3DRD reset
  * @rmtoll USB3DRD         USB3DRDRST         LL_RCC_USB3DRD_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3DRD_ForceReset(void)
{
  SET_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDRST);
}
#endif /* RCC_USB3DRDCFGR_USB3DRDRST */


/**
  * @brief  Assert USB2PHY reset
  * @rmtoll USB2PHY         USB2PHYRST         LL_RCC_USB2PHY_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY1_ForceReset(void)
{
  SET_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1RST);
}

/**
  * @brief  Assert USB2PHY reset
  * @rmtoll USB2PHY         USB2PHYRST         LL_RCC_USB2PHY_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY2_ForceReset(void)
{
  SET_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2RST);
}

/**
  * @brief  Assert FMC reset
  * @rmtoll FMC         FMCRST         LL_RCC_FMC_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FMC_ForceReset(void)
{
  SET_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCRST);
}

/**
  * @brief  Assert ETH1 reset
  * @rmtoll ETH1         ETH1RST         LL_RCC_ETH1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH1_ForceReset(void)
{
  SET_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RST);
}

/**
  * @brief  Assert ETH2 reset
  * @rmtoll ETH2         ETH2RST         LL_RCC_ETH2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH2_ForceReset(void)
{
  SET_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RST);
}
#if defined(RCC_GPUCFGR_GPURST)
/**
  * @brief  Assert GPU reset
  * @rmtoll GPU         GPURST         LL_RCC_GPU_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPU_ForceReset(void)
{
  SET_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPURST);
}
#endif /* RCC_GPUCFGR_GPURST */
/**
  * @brief  Release SDMMC1 reset
  * @rmtoll SDMMC1         SDMMC1RST         LL_RCC_SDMMC1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SDMMC1CFGR, RCC_SDMMC1CFGR_SDMMC1RST);
}

/**
  * @brief  Release SDMMC2 reset
  * @rmtoll SDMMC2         SDMMC2RST         LL_RCC_SDMMC2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SDMMC2CFGR, RCC_SDMMC2CFGR_SDMMC2RST);
}

/**
  * @brief  Release SDMMC3 reset
  * @rmtoll SDMMC3         SDMMC3RST         LL_RCC_SDMMC3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SDMMC3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SDMMC3CFGR, RCC_SDMMC3CFGR_SDMMC3RST);
}

#if defined(RCC_USB3DRDCFGR_USB3DRDRST)
/**
  * @brief  Release USB3DRD reset
  * @rmtoll USB3DRD         USB3DRDRST         LL_RCC_USB3DRD_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3DRD_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USB3DRDCFGR, RCC_USB3DRDCFGR_USB3DRDRST);
}
#endif /* RCC_USB3DRDCFGR_USB3DRDRST */


/**
  * @brief  Release USB2PHY reset
  * @rmtoll USB2PHY         USB2PHYRST         LL_RCC_USB2PHY_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USB2PHY1CFGR, RCC_USB2PHY1CFGR_USB2PHY1RST);
}

/**
  * @brief  Release USB2PHY reset
  * @rmtoll USB2PHY         USB2PHYRST         LL_RCC_USB2PHY_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB2PHY2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USB2PHY2CFGR, RCC_USB2PHY2CFGR_USB2PHY2RST);
}

/**
  * @brief  Release FMC reset
  * @rmtoll FMC         FMCRST         LL_RCC_FMC_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FMC_ReleaseReset(void)
{
  CLEAR_BIT(RCC->FMCCFGR, RCC_FMCCFGR_FMCRST);
}

/**
  * @brief  Release ETH1 reset
  * @rmtoll ETH1         ETH1RST         LL_RCC_ETH1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->ETH1CFGR, RCC_ETH1CFGR_ETH1RST);
}

/**
  * @brief  Release ETH2 reset
  * @rmtoll ETH2         ETH2RST         LL_RCC_ETH2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETH2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->ETH2CFGR, RCC_ETH2CFGR_ETH2RST);
}
#if defined(RCC_GPUCFGR_GPURST)
/**
  * @brief  Release GPU reset
  * @rmtoll GPU         GPURST         LL_RCC_GPU_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPU_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPUCFGR, RCC_GPUCFGR_GPURST);
}
#endif /* RCC_GPUCFGR_GPURST */
/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHB6 AHB6
  * @{
  */

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AHSMARTRUN AHB Smartrun
  * @{
  */
#if defined(RCC_C3CFGR_C3EN)
/**
  * @brief  Enable C3CFGR,  peripheral clock
  * @rmtoll C3         C3EN         LL_RCC_C3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_C3_EnableClock(void)
{
  SET_BIT(RCC->C3CFGR, RCC_C3CFGR_C3EN);
}
#endif /* RCC_C3CFGR_C3EN */

#if defined(RCC_LPDMACFGR_LPDMAEN)
/**
  * @brief  Enable LPDMA  peripheral clock
  * @rmtoll LPDMA         LPDMAEN         LL_RCC_LPDMA_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_EnableClock(void)
{
  SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAEN);
}
#endif /* RCC_LPDMACFGR_LPDMAEN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2EN)
/**
  * @brief  Enable LPSRAM2  peripheral clock
  * @rmtoll LPSRAM2         LPSRAM2EN         LL_RCC_LPSRAM2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM2_EnableClock(void)
{
  SET_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2EN);
}
#endif /* RCC_LPSRAM2CFGR_LPSRAM2EN */

#if defined(RCC_LPSRAM1CFGR_LPSRAM1EN)
/**
  * @brief  Enable LPSRAM1  peripheral clock
  * @rmtoll LPSRAM1         LPSRAM1EN         LL_RCC_LPSRAM1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM1_EnableClock(void)
{
  SET_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1EN);
}
#endif /* RCC_LPSRAM1CFGR_LPSRAM1EN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3EN)
/**
  * @brief  Enable LPSRAM3  peripheral clock
  * @rmtoll LPSRAM3         LPSRAM3EN         LL_RCC_LPSRAM3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM3_EnableClock(void)
{
  SET_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3EN);
}
#endif /* RCC_LPSRAM3CFGR_LPSRAM3EN */

#if defined(RCC_IPCC2CFGR_IPCC2EN)
/**
  * @brief  Enable IPCC2  peripheral clock
  * @rmtoll IPCC2         IPCC2EN         LL_RCC_IPCC2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC2_EnableClock(void)
{
  SET_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2EN);
}
#endif /*RCC_IPCC2CFGR_IPCC2EN*/

#if defined(RCC_HSEMCFGR_HSEMEN)
/**
  * @brief  Enable HSEM  peripheral clock
  * @rmtoll HSEM         HSEMEN         LL_RCC_HSEM_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEM_EnableClock(void)
{
  SET_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMEN);
}
#endif /* RCC_HSEMCFGR_HSEMEN */

#if defined(RCC_ADF1CFGR_ADF1EN)
/**
  * @brief  Enable ADF1  peripheral clock
  * @rmtoll ADF1         ADF1EN         LL_RCC_ADF1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADF1_EnableClock(void)
{
  SET_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1EN);
}
#endif /* RCC_ADF1CFGR_ADF1EN */
/**
  * @brief  Enable GPIOZ  peripheral clock
  * @rmtoll GPIOZ         GPIOZEN         LL_RCC_GPIOZ_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOZ_EnableClock(void)
{
  SET_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZEN);
}

#if defined(RCC_C3CFGR_C3EN)
/**
  * @brief  Disable C3CFGR,  peripheral clock
  * @rmtoll C3         C3EN         LL_RCC_C3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_C3_DisableClock(void)
{
  CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_C3EN);
}
#endif /* RCC_C3CFGR_C3EN */

#if defined(RCC_LPDMACFGR_LPDMAEN)
/**
  * @brief  Disable LPDMA  peripheral clock
  * @rmtoll LPDMA         LPDMAEN         LL_RCC_LPDMA_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_DisableClock(void)
{
  CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAEN);
}
#endif /* RCC_LPDMACFGR_LPDMAEN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2EN)
/**
  * @brief  Disable LPSRAM2  peripheral clock
  * @rmtoll LPSRAM2         LPSRAM2EN         LL_RCC_LPSRAM2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM2_DisableClock(void)
{
  CLEAR_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2EN);
}
#endif /* RCC_LPSRAM2CFGR_LPSRAM2EN */

#if defined(RCC_LPSRAM1CFGR_LPSRAM1EN)
/**
  * @brief  Disable LPSRAM1  peripheral clock
  * @rmtoll LPSRAM1         LPSRAM1EN         LL_RCC_LPSRAM1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM1_DisableClock(void)
{
  CLEAR_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1EN);
}
#endif /* RCC_LPSRAM1CFGR_LPSRAM1EN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3EN)
/**
  * @brief  Disable LPSRAM3  peripheral clock
  * @rmtoll LPSRAM3         LPSRAM3EN         LL_RCC_LPSRAM3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM3_DisableClock(void)
{
  CLEAR_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3EN);
}
#endif /* RCC_LPSRAM3CFGR_LPSRAM3EN */

#if defined(RCC_IPCC2CFGR_IPCC2EN)
/**
  * @brief  Disable IPCC2  peripheral clock
  * @rmtoll IPCC2         IPCC2EN         LL_RCC_IPCC2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC2_DisableClock(void)
{
  CLEAR_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2EN);
}
#endif /* RCC_IPCC2CFGR_IPCC2EN */

#if defined(RCC_HSEMCFGR_HSEMEN)
/**
  * @brief  Disable HSEM  peripheral clock
  * @rmtoll HSEM         HSEMEN         LL_RCC_HSEM_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEM_DisableClock(void)
{
  CLEAR_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMEN);
}
#endif /* RCC_HSEMCFGR_HSEMEN */

#if defined(RCC_ADF1CFGR_ADF1EN)
/**
  * @brief  Disable ADF1  peripheral clock
  * @rmtoll ADF1         ADF1EN         LL_RCC_ADF1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADF1_DisableClock(void)
{
  CLEAR_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1EN);
}
#endif /* RCC_ADF1CFGR_ADF1EN */
/**
  * @brief  Disable GPIOZ  peripheral clock
  * @rmtoll GPIOZ         GPIOZEN         LL_RCC_GPIOZ_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOZ_DisableClock(void)
{
  CLEAR_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZEN);
}

#if defined(RCC_C3CFGR_C3LPEN)
/**
  * @brief  Enable C3CFGR, peripheral clocks enable during CSleep mode
  * @rmtoll C3         C3LPEN         LL_RCC_C3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_C3_EnableClockSleep(void)
{
  SET_BIT(RCC->C3CFGR, RCC_C3CFGR_C3LPEN);
}
#endif /* RCC_C3CFGR_C3LPEN */

#if defined(RCC_LPDMACFGR_LPDMALPEN)
/**
  * @brief  Enable LPDMA peripheral clocks enable during CSleep mode
  * @rmtoll LPDMA         LPDMALPEN         LL_RCC_LPDMA_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_EnableClockSleep(void)
{
  SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMALPEN);
}
#endif /* RCC_LPDMACFGR_LPDMALPEN  */

#if defined(RCC_LPDMACFGR_LPDMAAMEN)
/**
  * @brief  Enable LPDMA peripheral clocks during Autonomous mode
  * @rmtoll LPDMA         LPDMAAMEN         LL_RCC_LPDMA_EnableClockAutonomous
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_EnableClockAutonomous(void)
{
  SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAAMEN);
}
#endif /* RCC_LPDMACFGR_LPDMAAMEN */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2LPEN)
/**
  * @brief  Enable LPSRAM2 peripheral clocks enable during CSleep mode
  * @rmtoll LPSRAM2         LPSRAM2LPEN         LL_RCC_LPSRAM2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM2_EnableClockSleep(void)
{
  SET_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2LPEN);
}
#endif /* RCC_LPSRAM2CFGR_LPSRAM2LPEN */

#if defined(RCC_LPSRAM1CFGR_LPSRAM1LPEN)
/**
  * @brief  Enable LPSRAM1 peripheral clocks enable during CSleep mode
  * @rmtoll LPSRAM1         LPSRAM1LPEN         LL_RCC_LPSRAM1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM1_EnableClockSleep(void)
{
  SET_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1LPEN);
}
#endif /* RCC_LPSRAM1CFGR_LPSRAM1LPEN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3LPEN )
/**
  * @brief  Enable LPSRAM3 peripheral clocks enable during CSleep mode
  * @rmtoll LPSRAM3         LPSRAM3LPEN         LL_RCC_LPSRAM3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM3_EnableClockSleep(void)
{
  SET_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3LPEN);
}
#endif /* RCC_LPSRAM3CFGR_LPSRAM3LPEN */

#if defined(RCC_IPCC2CFGR_IPCC2LPEN)
/**
  * @brief  Enable IPCC2 peripheral clocks enable during CSleep mode
  * @rmtoll IPCC2         IPCC2LPEN         LL_RCC_IPCC2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC2_EnableClockSleep(void)
{
  SET_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2LPEN);
}
#endif /* RCC_IPCC2CFGR_IPCC2LPEN */

#if defined(RCC_HSEMCFGR_HSEMLPEN)
/**
  * @brief  Enable HSEM peripheral clocks enable during CSleep mode
  * @rmtoll HSEM         HSEMLPEN         LL_RCC_HSEM_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEM_EnableClockSleep(void)
{
  SET_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMLPEN);
}
#endif /* RCC_HSEMCFGR_HSEMLPEN */

#if defined(RCC_ADF1CFGR_ADF1LPEN)
/**
  * @brief  Enable ADF1 peripheral clocks enable during CSleep mode
  * @rmtoll ADF1         ADF1LPEN         LL_RCC_ADF1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADF1_EnableClockSleep(void)
{
  SET_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1LPEN);
}
#endif /* RCC_ADF1CFGR_ADF1LPEN */
/**
  * @brief  Enable GPIOZ peripheral clocks enable during CSleep mode
  * @rmtoll GPIOZ         GPIOZLPEN         LL_RCC_GPIOZ_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOZ_EnableClockSleep(void)
{
  SET_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZLPEN);
}

#if defined(RCC_C3CFGR_C3LPEN)
/**
  * @brief  Disable C3CFGR, peripheral clocks during CSleep mode
  * @rmtoll C3         C3LPEN         LL_RCC_C3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_C3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_C3LPEN);
}
#endif /*  RCC_C3CFGR_C3LPEN */

#if defined(RCC_LPDMACFGR_LPDMALPEN)
/**
  * @brief  Disable LPDMA peripheral clocks during CSleep mode
  * @rmtoll LPDMA         LPDMALPEN         LL_RCC_LPDMA_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMALPEN);
}
#endif /* RCC_LPDMACFGR_LPDMALPEN  */

#if defined(RCC_LPDMACFGR_LPDMAAMEN)
/**
  * @brief  Disable LPDMA peripheral clocks during Autonomous mode
  * @rmtoll LPDMA         LPDMAAMEN         LL_RCC_LPDMA_EnableClockAutonomous
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_DisableClockAutonomous(void)
{
  CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMAAMEN);
}
#endif /* RCC_LPDMACFGR_LPDMAAMEN  */

#if defined(RCC_LPSRAM2CFGR_LPSRAM2LPEN)
/**
  * @brief  Disable LPSRAM2 peripheral clocks during CSleep mode
  * @rmtoll LPSRAM2         LPSRAM2LPEN         LL_RCC_LPSRAM2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPSRAM2CFGR, RCC_LPSRAM2CFGR_LPSRAM2LPEN);
}
#endif /*  RCC_LPSRAM2CFGR_LPSRAM2LPEN */

#if defined(RCC_LPSRAM1CFGR_LPSRAM1LPEN)
/**
  * @brief  Disable LPSRAM1 peripheral clocks during CSleep mode
  * @rmtoll LPSRAM1         LPSRAM1LPEN         LL_RCC_LPSRAM1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPSRAM1CFGR, RCC_LPSRAM1CFGR_LPSRAM1LPEN);
}
#endif /*  RCC_LPSRAM1CFGR_LPSRAM1LPEN */

#if defined(RCC_LPSRAM3CFGR_LPSRAM3LPEN)
/**
  * @brief  Disable LPSRAM3 peripheral clocks during CSleep mode
  * @rmtoll LPSRAM3         LPSRAM3LPEN         LL_RCC_LPSRAM3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPSRAM3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPSRAM3CFGR, RCC_LPSRAM3CFGR_LPSRAM3LPEN);
}
#endif /* RCC_LPSRAM3CFGR_LPSRAM3LPEN  */

#if defined(RCC_IPCC2CFGR_IPCC2LPEN)
/**
  * @brief  Disable IPCC2 peripheral clocks during CSleep mode
  * @rmtoll IPCC2         IPCC2LPEN         LL_RCC_IPCC2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2LPEN);
}
#endif /* RCC_IPCC2CFGR_IPCC2LPEN  */

#if defined(RCC_HSEMCFGR_HSEMLPEN)
/**
  * @brief  Disable HSEM peripheral clocks during CSleep mode
  * @rmtoll HSEM         HSEMLPEN         LL_RCC_HSEM_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEM_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMLPEN);
}
#endif /*  RCC_HSEMCFGR_HSEMLPEN */

#if defined(RCC_ADF1CFGR_ADF1LPEN)
/**
  * @brief  Disable ADF1 peripheral clocks during CSleep mode
  * @rmtoll ADF1         ADF1LPEN         LL_RCC_ADF1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADF1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1LPEN);
}
#endif /* RCC_ADF1CFGR_ADF1LPEN */
/**
  * @brief  Disable GPIOZ peripheral clocks during CSleep mode
  * @rmtoll GPIOZ         GPIOZLPEN         LL_RCC_GPIOZ_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOZ_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZLPEN);
}

#if defined(RCC_C3CFGR_C3RST)
/**
  * @brief  Assert C3CFGR, reset
  * @rmtoll C3         C3RST         LL_RCC_C3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_C3_ForceReset(void)
{
  SET_BIT(RCC->C3CFGR, RCC_C3CFGR_C3RST);
}
#endif /* RCC_C3CFGR_C3RST */

#if defined(RCC_LPDMACFGR_LPDMARST)
/**
  * @brief  Assert LPDMA reset
  * @rmtoll LPDMA         LPDMARST         LL_RCC_LPDMA_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_ForceReset(void)
{
  SET_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMARST);
}
#endif /* RCC_LPDMACFGR_LPDMARST */

#if defined(RCC_IPCC2CFGR_IPCC2RST)
/**
  * @brief  Assert IPCC2 reset
  * @rmtoll IPCC2         IPCC2RST         LL_RCC_IPCC2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC2_ForceReset(void)
{
  SET_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2RST);
}
#endif /* RCC_IPCC2CFGR_IPCC2RST */

#if defined(RCC_HSEMCFGR_HSEMRST)
/**
  * @brief  Assert HSEM reset
  * @rmtoll HSEM         HSEMRST         LL_RCC_HSEM_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEM_ForceReset(void)
{
  SET_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMRST);
}
#endif /* RCC_HSEMCFGR_HSEMRST */

#if defined(RCC_ADF1CFGR_ADF1RST)
/**
  * @brief  Assert ADF1 reset
  * @rmtoll ADF1         ADF1RST         LL_RCC_ADF1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADF1_ForceReset(void)
{
  SET_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1RST);
}
#endif /* RCC_ADF1CFGR_ADF1RST */
/**
  * @brief  Assert GPIOZ reset
  * @rmtoll GPIOZ         GPIOZRST         LL_RCC_GPIOZ_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOZ_ForceReset(void)
{
  SET_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZRST);
}

#if defined(RCC_C3CFGR_C3RST)
/**
  * @brief  Release C3CFGR, reset
  * @rmtoll C3         C3RST         LL_RCC_C3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_C3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->C3CFGR, RCC_C3CFGR_C3RST);
}
#endif /*  RCC_C3CFGR_C3RST */

#if defined(RCC_LPDMACFGR_LPDMARST)
/**
  * @brief  Release LPDMA reset
  * @rmtoll LPDMA         LPDMARST         LL_RCC_LPDMA_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPDMA_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LPDMACFGR, RCC_LPDMACFGR_LPDMARST);
}
#endif /* RCC_LPDMACFGR_LPDMARST  */

#if defined(RCC_IPCC2CFGR_IPCC2RST)
/**
  * @brief  Release IPCC2 reset
  * @rmtoll IPCC2         IPCC2RST         LL_RCC_IPCC2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IPCC2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->IPCC2CFGR, RCC_IPCC2CFGR_IPCC2RST);
}
#endif /*  RCC_IPCC2CFGR_IPCC2RST */

#if defined(RCC_HSEMCFGR_HSEMRST)
/**
  * @brief  Release HSEM reset
  * @rmtoll HSEM         HSEMRST         LL_RCC_HSEM_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HSEM_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HSEMCFGR, RCC_HSEMCFGR_HSEMRST);
}
#endif /* RCC_HSEMCFGR_HSEMRST  */

#if defined(RCC_ADF1CFGR_ADF1RST)
/**
  * @brief  Release ADF1 reset
  * @rmtoll ADF1         ADF1RST         LL_RCC_ADF1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ADF1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->ADF1CFGR, RCC_ADF1CFGR_ADF1RST);
}
#endif /* RCC_ADF1CFGR_ADF1RST */
/**
  * @brief  Release GPIOZ reset
  * @rmtoll GPIOZ         GPIOZRST         LL_RCC_GPIOZ_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GPIOZ_ReleaseReset(void)
{
  CLEAR_BIT(RCC->GPIOZCFGR, RCC_GPIOZCFGR_GPIOZRST);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_AXI AXI
  * @{
  */
#if defined(RCC_STMCFGR_STMEN)
/**
  * @brief  Enable STM  peripheral clock
  * @rmtoll STM         STMEN         LL_RCC_STM_EnableClock
  * @retval None
 */
__STATIC_INLINE void LL_RCC_STM_EnableClock(void)
{
  SET_BIT(RCC->STMCFGR, RCC_STMCFGR_STMEN);
}
#endif /* RCC_STMCFGR_STMEN */

#if defined(RCC_PCIECFGR_PCIEEN)
/**
  * @brief  Enable PCIE  peripheral clock
  * @rmtoll PCIE         PCIEEN         LL_RCC_PCIE_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PCIE_EnableClock(void)
{
  SET_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIEEN);
}
#endif /* RCC_PCIECFGR_PCIEEN */

#if defined(RCC_CSICFGR_CSIEN)
/**
  * @brief  Enable CSI  peripheral clock
  * @rmtoll CSI         CSIEN         LL_RCC_CSI_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_EnableClock(void)
{
  SET_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIEN);
}
#endif /* RCC_CSICFGR_CSIEN */

#if defined(RCC_CSI2CFGR_CSI2EN)
/**
  * @brief  Enable CSI2  peripheral clock
  * @rmtoll CSI2         CSI2EN         LL_RCC_CSI2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI2_EnableClock(void)
{
  SET_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2EN);
}
#endif /* RCC_CSI2CFGR_CSI2EN */

#if defined(RCC_STMCFGR_STMEN)
/**
  * @brief  Disable STM  peripheral clock
  * @rmtoll STM         STMEN         LL_RCC_STM_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_STM_DisableClock(void)
{
  CLEAR_BIT(RCC->STMCFGR, RCC_STMCFGR_STMEN);
}
#endif /* RCC_STMCFGR_STMEN */

#if defined(RCC_PCIECFGR_PCIEEN)
/**
  * @brief  Disable PCIE  peripheral clock
  * @rmtoll PCIE         PCIEEN         LL_RCC_PCIE_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PCIE_DisableClock(void)
{
  CLEAR_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIEEN);
}
#endif /* RCC_PCIECFGR_PCIEEN */

#if defined(RCC_CSICFGR_CSIEN)
/**
  * @brief  Disable CSI  peripheral clock
  * @rmtoll CSI         CSIEN         LL_RCC_CSI_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_DisableClock(void)
{
  CLEAR_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIEN);
}
#endif /* RCC_CSICFGR_CSIEN */

#if defined(RCC_CSI2CFGR_CSI2EN)
/**
  * @brief  Disable CSI2  peripheral clock
  * @rmtoll CSI2         CSI2EN         LL_RCC_CSI2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI2_DisableClock(void)
{
  CLEAR_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2EN);
}
#endif /* RCC_CSI2CFGR_CSI2EN */

#if defined(RCC_STMCFGR_STMLPEN)
/**
  * @brief  Enable STM peripheral clocks enable during CSleep mode
  * @rmtoll STM         STMLPEN         LL_RCC_STM_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_STM_EnableClockSleep(void)
{
  SET_BIT(RCC->STMCFGR, RCC_STMCFGR_STMLPEN);
}
#endif /* RCC_STMCFGR_STMLPEN */

#if defined(RCC_PCIECFGR_PCIELPEN)
/**
  * @brief  Enable PCIE peripheral clocks enable during CSleep mode
  * @rmtoll PCIE         PCIELPEN         LL_RCC_PCIE_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PCIE_EnableClockSleep(void)
{
  SET_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIELPEN);
}
#endif /* RCC_PCIECFGR_PCIELPEN */

#if defined(RCC_CSICFGR_CSILPEN)
/**
  * @brief  Enable CSI peripheral clocks enable during CSleep mode
  * @rmtoll CSI         CSILPEN         LL_RCC_CSI_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_EnableClockSleep(void)
{
  SET_BIT(RCC->CSICFGR, RCC_CSICFGR_CSILPEN);
}
#endif /* RCC_CSICFGR_CSILPEN */

#if defined(RCC_CSI2CFGR_CSI2LPEN)
/**
  * @brief  Enable CSI2 peripheral clocks enable during CSleep mode
  * @rmtoll CSI2         CSI2LPEN         LL_RCC_CSI2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI2_EnableClockSleep(void)
{
  SET_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2LPEN);
}
#endif /* RCC_CSI2CFGR_CSI2LPEN */

#if defined(RCC_STMCFGR_STMLPEN)
/**
  * @brief  Disable STM peripheral clocks during CSleep mode
  * @rmtoll STM         STMLPEN         LL_RCC_STM_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_STM_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->STMCFGR, RCC_STMCFGR_STMLPEN);
}
#endif /* RCC_STMCFGR_STMLPEN */

#if defined(RCC_PCIECFGR_PCIELPEN)
/**
  * @brief  Disable PCIE peripheral clocks during CSleep mode
  * @rmtoll PCIE         PCIELPEN         LL_RCC_PCIE_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PCIE_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIELPEN);
}
#endif /* RCC_PCIECFGR_PCIELPEN */

#if defined(RCC_CSICFGR_CSILPEN)
/**
  * @brief  Disable CSI peripheral clocks during CSleep mode
  * @rmtoll CSI         CSILPEN         LL_RCC_CSI_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->CSICFGR, RCC_CSICFGR_CSILPEN);
}
#endif /* RCC_CSICFGR_CSILPEN */

#if defined(RCC_CSI2CFGR_CSI2LPEN)
/**
  * @brief  Disable CSI2 peripheral clocks during CSleep mode
  * @rmtoll CSI2         CSI2LPEN         LL_RCC_CSI2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2LPEN);
}
#endif /* RCC_CSI2CFGR_CSI2LPEN */

#if defined(RCC_PCIECFGR_PCIERST)
/**
  * @brief  Assert PCIE reset
  * @rmtoll PCIE         PCIERST         LL_RCC_PCIE_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PCIE_ForceReset(void)
{
  SET_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIERST);
}
#endif /* RCC_PCIECFGR_PCIERST */

#if defined(RCC_CSICFGR_CSIRST)
/**
  * @brief  Assert CSI reset
  * @rmtoll CSI         CSIRST         LL_RCC_CSI_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_ForceReset(void)
{
  SET_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIRST);
}
#endif /* RCC_CSICFGR_CSIRST */

#if defined(RCC_CSI2CFGR_CSI2RST)
/**
  * @brief  Assert CSI2 reset
  * @rmtoll CSI2         CSI2RST         LL_RCC_CSI2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI2_ForceReset(void)
{
  SET_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2RST);
}
#endif /* RCC_CSI2CFGR_CSI2RST */

#if defined(RCC_PCIECFGR_PCIERST)
/**
  * @brief  Release PCIE reset
  * @rmtoll PCIE         PCIERST         LL_RCC_PCIE_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_PCIE_ReleaseReset(void)
{
  CLEAR_BIT(RCC->PCIECFGR, RCC_PCIECFGR_PCIERST);
}
#endif /* RCC_PCIECFGR_PCIERST */

#if defined(RCC_CSICFGR_CSIRST)
/**
  * @brief  Release CSI reset
  * @rmtoll CSI         CSIRST         LL_RCC_CSI_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI_ReleaseReset(void)
{
  CLEAR_BIT(RCC->CSICFGR, RCC_CSICFGR_CSIRST);
}
#endif /* RCC_CSICFGR_CSIRST */

#if defined(RCC_CSI2CFGR_CSI2RST)
/**
  * @brief  Release CSI2 reset
  * @rmtoll CSI2         CSI2RST         LL_RCC_CSI2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CSI2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->CSI2CFGR, RCC_CSI2CFGR_CSI2RST);
}
#endif /* RCC_CSI2CFGR_CSI2RST */

/**
  * @}
  */

/** @defgroup BUS_LL_EF_MLAHB MLAHB
  * @{
  */
/**
  * @brief  Enable SRAM1  peripheral clock
  * @rmtoll SRAM1         SRAM1EN         LL_RCC_SRAM1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM1_EnableClock(void)
{
  SET_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1EN);
}

#if defined(RCC_SRAM2CFGR_SRAM2EN)
/**
  * @brief  Enable SRAM2  peripheral clock
  * @rmtoll SRAM2         SRAM2EN         LL_RCC_SRAM2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM2_EnableClock(void)
{
  SET_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2EN);
}
#endif /* RCC_SRAM2CFGR_SRAM2EN */

/**
  * @brief  Enable RETRAM  peripheral clock
  * @rmtoll RETRAM         RETRAMEN         LL_RCC_RETRAM_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RETRAM_EnableClock(void)
{
  SET_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMEN);
}

/**
  * @brief  Enable OSPI1  peripheral clock
  * @rmtoll OSPI1         OSPI1EN         LL_RCC_OSPI1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI1_EnableClock(void)
{
  SET_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1EN);
}
#if defined(RCC_OSPI2CFGR_OSPI2EN)
/**
  * @brief  Enable OSPI2  peripheral clock
  * @rmtoll OSPI2         OSPI2EN         LL_RCC_OSPI2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI2_EnableClock(void)
{
  SET_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2EN);
}
#endif /* RCC_OSPI2CFGR_OSPI2EN */
/**
  * @brief  Disable SRAM1  peripheral clock
  * @rmtoll SRAM1         SRAM1EN         LL_RCC_SRAM1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM1_DisableClock(void)
{
  CLEAR_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1EN);
}

#if defined(RCC_SRAM2CFGR_SRAM2EN)
/**
  * @brief  Disable SRAM2  peripheral clock
  * @rmtoll SRAM2         SRAM2EN         LL_RCC_SRAM2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM2_DisableClock(void)
{
  CLEAR_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2EN);
}
#endif /* RCC_SRAM2CFGR_SRAM2EN */

/**
  * @brief  Disable RETRAM  peripheral clock
  * @rmtoll RETRAM         RETRAMEN         LL_RCC_RETRAM_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RETRAM_DisableClock(void)
{
  CLEAR_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMEN);
}

/**
  * @brief  Disable OSPI1  peripheral clock
  * @rmtoll OSPI1         OSPI1EN         LL_RCC_OSPI1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI1_DisableClock(void)
{
  CLEAR_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1EN);
}
#if defined(RCC_OSPI2CFGR_OSPI2EN)
/**
  * @brief  Disable OSPI2  peripheral clock
  * @rmtoll OSPI2         OSPI2EN         LL_RCC_OSPI2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI2_DisableClock(void)
{
  CLEAR_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2EN);
}
#endif /* RCC_OSPI2CFGR_OSPI2EN */
/**
  * @brief  Enable SRAM1 peripheral clocks enable during CSleep mode
  * @rmtoll SRAM1         SRAM1LPEN         LL_RCC_SRAM1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM1_EnableClockSleep(void)
{
  SET_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1LPEN);
}

#if defined(RCC_SRAM2CFGR_SRAM2LPEN)
/**
  * @brief  Enable SRAM2 peripheral clocks enable during CSleep mode
  * @rmtoll SRAM2         SRAM2LPEN         LL_RCC_SRAM2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM2_EnableClockSleep(void)
{
  SET_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2LPEN);
}
#endif /* RCC_SRAM2CFGR_SRAM2LPEN */

/**
  * @brief  Enable RETRAM peripheral clocks enable during CSleep mode
  * @rmtoll RETRAM         RETRAMLPEN         LL_RCC_RETRAM_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RETRAM_EnableClockSleep(void)
{
  SET_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMLPEN);
}

/**
  * @brief  Enable OSPI1 peripheral clocks enable during CSleep mode
  * @rmtoll OSPI1         OSPI1LPEN         LL_RCC_OSPI1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI1_EnableClockSleep(void)
{
  SET_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1LPEN);
}
#if defined(RCC_OSPI2CFGR_OSPI2LPEN)
/**
  * @brief  Enable OSPI2 peripheral clocks enable during CSleep mode
  * @rmtoll OSPI2         OSPI2LPEN         LL_RCC_OSPI2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI2_EnableClockSleep(void)
{
  SET_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2LPEN);
}
#endif /* RCC_OSPI2CFGR_OSPI2LPEN */
/**
  * @brief  Disable SRAM1 peripheral clocks during CSleep mode
  * @rmtoll SRAM1         SRAM1LPEN         LL_RCC_SRAM1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SRAM1CFGR, RCC_SRAM1CFGR_SRAM1LPEN);
}

#if defined(RCC_SRAM2CFGR_SRAM2LPEN)
/**
  * @brief  Disable SRAM2 peripheral clocks during CSleep mode
  * @rmtoll SRAM2         SRAM2LPEN         LL_RCC_SRAM2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SRAM2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SRAM2CFGR, RCC_SRAM2CFGR_SRAM2LPEN);
}
#endif /* RCC_SRAM2CFGR_SRAM2LPEN */

/**
  * @brief  Disable RETRAM peripheral clocks during CSleep mode
  * @rmtoll RETRAM         RETRAMLPEN         LL_RCC_RETRAM_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RETRAM_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->RETRAMCFGR, RCC_RETRAMCFGR_RETRAMLPEN);
}

/**
  * @brief  Disable OSPI1 peripheral clocks during CSleep mode
  * @rmtoll OSPI1         OSPI1LPEN         LL_RCC_OSPI1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1LPEN);
}
#if defined(RCC_OSPI2CFGR_OSPI2LPEN)
/**
  * @brief  Disable OSPI2 peripheral clocks during CSleep mode
  * @rmtoll OSPI2         OSPI2LPEN         LL_RCC_OSPI2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2LPEN);
}
#endif /* RCC_OSPI2CFGR_OSPI2LPEN */
/**
  * @brief  Assert OSPI1 reset
  * @rmtoll OSPI1         OSPI1RST         LL_RCC_OSPI1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI1_ForceReset(void)
{
  SET_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1RST);
}
#if defined(RCC_OSPI2CFGR_OSPI2RST)
/**
  * @brief  Assert OSPI2 reset
  * @rmtoll OSPI2         OSPI2RST         LL_RCC_OSPI2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI2_ForceReset(void)
{
  SET_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2RST);
}
#endif /* RCC_OSPI2CFGR_OSPI2RST */
/**
  * @brief  Release OSPI1 reset
  * @rmtoll OSPI1         OSPI1RST         LL_RCC_OSPI1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->OSPI1CFGR, RCC_OSPI1CFGR_OSPI1RST);
}
#if defined(RCC_OSPI2CFGR_OSPI2RST)
/**
  * @brief  Release OSPI2 reset
  * @rmtoll OSPI2         OSPI2RST         LL_RCC_OSPI2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_OSPI2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->OSPI2CFGR, RCC_OSPI2CFGR_OSPI2RST);
}
#endif /* RCC_OSPI2CFGR_OSPI2RST */
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB1 APB1
  * @{
  */
/**
  * @brief  Enable TIM11  peripheral clock
  * @rmtoll TIM11         TIM11EN         LL_RCC_TIM11_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM11_EnableClock(void)
{
  SET_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11EN);
}

/**
  * @brief  Enable TIM10  peripheral clock
  * @rmtoll TIM10         TIM10EN         LL_RCC_TIM10_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM10_EnableClock(void)
{
  SET_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10EN);
}

/**
  * @brief  Enable I3C2  peripheral clock
  * @rmtoll I3C2         I3C2EN         LL_RCC_I3C2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C2_EnableClock(void)
{
  SET_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2EN);
}

#if defined(RCC_I3C3CFGR_I3C3EN)
/**
  * @brief  Enable I3C3  peripheral clock
  * @rmtoll I3C3         I3C3EN         LL_RCC_I3C3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C3_EnableClock(void)
{
  SET_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3EN);
}
#endif /* RCC_I3C3CFGR_I3C3EN */

#if defined(RCC_I2C7CFGR_I2C7EN)
/**
  * @brief  Enable I2C7  peripheral clock
  * @rmtoll I2C7         I2C7EN         LL_RCC_I2C7_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C7_EnableClock(void)
{
  SET_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7EN);
}
#endif /* RCC_I2C7CFGR_I2C7EN */

/**
  * @brief  Enable I3C1  peripheral clock
  * @rmtoll I3C1         I3C1EN         LL_RCC_I3C1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C1_EnableClock(void)
{
  SET_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1EN);
}

#if defined(RCC_I2C5CFGR_I2C5EN)
/**
  * @brief  Enable I2C5  peripheral clock
  * @rmtoll I2C5         I2C5EN         LL_RCC_I2C5_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C5_EnableClock(void)
{
  SET_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5EN);
}
#endif /* RCC_I2C5CFGR_I2C5EN */

#if defined(RCC_I2C6CFGR_I2C6EN)
/**
  * @brief  Enable I2C6  peripheral clock
  * @rmtoll I2C6         I2C6EN         LL_RCC_I2C6_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C6_EnableClock(void)
{
  SET_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6EN);
}
#endif /* RCC_I2C6CFGR_I2C6EN */

#if defined(RCC_I2C3CFGR_I2C3EN)
/**
  * @brief  Enable I2C3  peripheral clock
  * @rmtoll I2C3         I2C3EN         LL_RCC_I2C3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C3_EnableClock(void)
{
  SET_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3EN);
}
#endif /* RCC_I2C3CFGR_I2C3EN */

#if defined(RCC_I2C4CFGR_I2C4EN)
/**
  * @brief  Enable I2C4  peripheral clock
  * @rmtoll I2C4         I2C4EN         LL_RCC_I2C4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C4_EnableClock(void)
{
  SET_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4EN);
}
#endif /* RCC_I2C4CFGR_I2C4EN */

/**
  * @brief  Enable I2C1  peripheral clock
  * @rmtoll I2C1         I2C1EN         LL_RCC_I2C1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C1_EnableClock(void)
{
  SET_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1EN);
}

/**
  * @brief  Enable I2C2  peripheral clock
  * @rmtoll I2C2         I2C2EN         LL_RCC_I2C2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C2_EnableClock(void)
{
  SET_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2EN);
}

/**
  * @brief  Enable UART4  peripheral clock
  * @rmtoll UART4         UART4EN         LL_RCC_UART4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART4_EnableClock(void)
{
  SET_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4EN);
}

/**
  * @brief  Enable UART5  peripheral clock
  * @rmtoll UART5         UART5EN         LL_RCC_UART5_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART5_EnableClock(void)
{
  SET_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5EN);
}

/**
  * @brief  Enable USART2  peripheral clock
  * @rmtoll USART2         USART2EN         LL_RCC_USART2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART2_EnableClock(void)
{
  SET_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2EN);
}

/**
  * @brief  Enable USART3  peripheral clock
  * @rmtoll USART3         USART3EN         LL_RCC_USART3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART3_EnableClock(void)
{
  SET_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3EN);
}

/**
  * @brief  Enable SPI3  peripheral clock
  * @rmtoll SPI3         SPI3EN         LL_RCC_SPI3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI3_EnableClock(void)
{
  SET_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3EN);
}

/**
  * @brief  Enable SPDIFRX  peripheral clock
  * @rmtoll SPDIFRX         SPDIFRXEN         LL_RCC_SPDIFRX_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPDIFRX_EnableClock(void)
{
  SET_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXEN);
}

/**
  * @brief  Enable LPTIM2  peripheral clock
  * @rmtoll LPTIM2         LPTIM2EN         LL_RCC_LPTIM2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM2_EnableClock(void)
{
  SET_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2EN);
}

/**
  * @brief  Enable SPI2  peripheral clock
  * @rmtoll SPI2         SPI2EN         LL_RCC_SPI2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI2_EnableClock(void)
{
  SET_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2EN);
}

/**
  * @brief  Enable TIM14  peripheral clock
  * @rmtoll TIM14         TIM14EN         LL_RCC_TIM14_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM14_EnableClock(void)
{
  SET_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14EN);
}

/**
  * @brief  Enable LPTIM1  peripheral clock
  * @rmtoll LPTIM1         LPTIM1EN         LL_RCC_LPTIM1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM1_EnableClock(void)
{
  SET_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1EN);
}

/**
  * @brief  Enable TIM12  peripheral clock
  * @rmtoll TIM12         TIM12EN         LL_RCC_TIM12_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM12_EnableClock(void)
{
  SET_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12EN);
}

/**
  * @brief  Enable TIM13  peripheral clock
  * @rmtoll TIM13         TIM13EN         LL_RCC_TIM13_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM13_EnableClock(void)
{
  SET_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13EN);
}

/**
  * @brief  Enable TIM6  peripheral clock
  * @rmtoll TIM6         TIM6EN         LL_RCC_TIM6_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM6_EnableClock(void)
{
  SET_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6EN);
}

/**
  * @brief  Enable TIM7  peripheral clock
  * @rmtoll TIM7         TIM7EN         LL_RCC_TIM7_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM7_EnableClock(void)
{
  SET_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7EN);
}

/**
  * @brief  Enable TIM4  peripheral clock
  * @rmtoll TIM4         TIM4EN         LL_RCC_TIM4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM4_EnableClock(void)
{
  SET_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4EN);
}

/**
  * @brief  Enable TIM5  peripheral clock
  * @rmtoll TIM5         TIM5EN         LL_RCC_TIM5_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM5_EnableClock(void)
{
  SET_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5EN);
}

/**
  * @brief  Enable TIM2  peripheral clock
  * @rmtoll TIM2         TIM2EN         LL_RCC_TIM2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM2_EnableClock(void)
{
  SET_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2EN);
}

/**
  * @brief  Enable TIM3  peripheral clock
  * @rmtoll TIM3         TIM3EN         LL_RCC_TIM3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM3_EnableClock(void)
{
  SET_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3EN);
}

/**
  * @brief  Disable TIM11  peripheral clock
  * @rmtoll TIM11         TIM11EN         LL_RCC_TIM11_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM11_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11EN);
}

/**
  * @brief  Disable TIM10  peripheral clock
  * @rmtoll TIM10         TIM10EN         LL_RCC_TIM10_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM10_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10EN);
}

/**
  * @brief  Disable I3C2  peripheral clock
  * @rmtoll I3C2         I3C2EN         LL_RCC_I3C2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C2_DisableClock(void)
{
  CLEAR_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2EN);
}

#if defined(RCC_I3C3CFGR_I3C3EN)
/**
  * @brief  Disable I3C3  peripheral clock
  * @rmtoll I3C3         I3C3EN         LL_RCC_I3C3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C3_DisableClock(void)
{
  CLEAR_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3EN);
}
#endif /* RCC_I3C3CFGR_I3C3EN */

#if defined(RCC_I2C7CFGR_I2C7EN)
/**
  * @brief  Disable I2C7  peripheral clock
  * @rmtoll I2C7         I2C7EN         LL_RCC_I2C7_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C7_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7EN);
}
#endif /* RCC_I2C7CFGR_I2C7EN */

/**
  * @brief  Disable I3C1  peripheral clock
  * @rmtoll I3C1         I3C1EN         LL_RCC_I3C1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C1_DisableClock(void)
{
  CLEAR_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1EN);
}

#if defined(RCC_I2C5CFGR_I2C5EN)
/**
  * @brief  Disable I2C5  peripheral clock
  * @rmtoll I2C5         I2C5EN         LL_RCC_I2C5_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C5_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5EN);
}
#endif /* RCC_I2C5CFGR_I2C5EN */

#if defined(RCC_I2C6CFGR_I2C6EN)
/**
  * @brief  Disable I2C6  peripheral clock
  * @rmtoll I2C6         I2C6EN         LL_RCC_I2C6_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C6_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6EN);
}
#endif /* RCC_I2C6CFGR_I2C6EN */

#if defined(RCC_I2C3CFGR_I2C3EN)
/**
  * @brief  Disable I2C3  peripheral clock
  * @rmtoll I2C3         I2C3EN         LL_RCC_I2C3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C3_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3EN);
}
#endif /* RCC_I2C3CFGR_I2C3EN */

#if defined(RCC_I2C4CFGR_I2C4EN)
/**
  * @brief  Disable I2C4  peripheral clock
  * @rmtoll I2C4         I2C4EN         LL_RCC_I2C4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C4_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4EN);
}
#endif /* RCC_I2C4CFGR_I2C4EN */

/**
  * @brief  Disable I2C1  peripheral clock
  * @rmtoll I2C1         I2C1EN         LL_RCC_I2C1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C1_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1EN);
}

/**
  * @brief  Disable I2C2  peripheral clock
  * @rmtoll I2C2         I2C2EN         LL_RCC_I2C2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C2_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2EN);
}

/**
  * @brief  Disable UART4  peripheral clock
  * @rmtoll UART4         UART4EN         LL_RCC_UART4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART4_DisableClock(void)
{
  CLEAR_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4EN);
}

/**
  * @brief  Disable UART5  peripheral clock
  * @rmtoll UART5         UART5EN         LL_RCC_UART5_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART5_DisableClock(void)
{
  CLEAR_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5EN);
}

/**
  * @brief  Disable USART2  peripheral clock
  * @rmtoll USART2         USART2EN         LL_RCC_USART2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART2_DisableClock(void)
{
  CLEAR_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2EN);
}

/**
  * @brief  Disable USART3  peripheral clock
  * @rmtoll USART3         USART3EN         LL_RCC_USART3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART3_DisableClock(void)
{
  CLEAR_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3EN);
}

/**
  * @brief  Disable SPI3  peripheral clock
  * @rmtoll SPI3         SPI3EN         LL_RCC_SPI3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI3_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3EN);
}

/**
  * @brief  Disable SPDIFRX  peripheral clock
  * @rmtoll SPDIFRX         SPDIFRXEN         LL_RCC_SPDIFRX_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPDIFRX_DisableClock(void)
{
  CLEAR_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXEN);
}

/**
  * @brief  Disable LPTIM2  peripheral clock
  * @rmtoll LPTIM2         LPTIM2EN         LL_RCC_LPTIM2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM2_DisableClock(void)
{
  CLEAR_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2EN);
}

/**
  * @brief  Disable SPI2  peripheral clock
  * @rmtoll SPI2         SPI2EN         LL_RCC_SPI2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI2_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2EN);
}

/**
  * @brief  Disable TIM14  peripheral clock
  * @rmtoll TIM14         TIM14EN         LL_RCC_TIM14_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM14_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14EN);
}

/**
  * @brief  Disable LPTIM1  peripheral clock
  * @rmtoll LPTIM1         LPTIM1EN         LL_RCC_LPTIM1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM1_DisableClock(void)
{
  CLEAR_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1EN);
}

/**
  * @brief  Disable TIM12  peripheral clock
  * @rmtoll TIM12         TIM12EN         LL_RCC_TIM12_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM12_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12EN);
}

/**
  * @brief  Disable TIM13  peripheral clock
  * @rmtoll TIM13         TIM13EN         LL_RCC_TIM13_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM13_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13EN);
}

/**
  * @brief  Disable TIM6  peripheral clock
  * @rmtoll TIM6         TIM6EN         LL_RCC_TIM6_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM6_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6EN);
}

/**
  * @brief  Disable TIM7  peripheral clock
  * @rmtoll TIM7         TIM7EN         LL_RCC_TIM7_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM7_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7EN);
}

/**
  * @brief  Disable TIM4  peripheral clock
  * @rmtoll TIM4         TIM4EN         LL_RCC_TIM4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM4_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4EN);
}

/**
  * @brief  Disable TIM5  peripheral clock
  * @rmtoll TIM5         TIM5EN         LL_RCC_TIM5_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM5_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5EN);
}

/**
  * @brief  Disable TIM2  peripheral clock
  * @rmtoll TIM2         TIM2EN         LL_RCC_TIM2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM2_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2EN);
}

/**
  * @brief  Disable TIM3  peripheral clock
  * @rmtoll TIM3         TIM3EN         LL_RCC_TIM3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM3_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3EN);
}

/**
  * @brief  Enable TIM11 peripheral clocks enable during CSleep mode
  * @rmtoll TIM11         TIM11LPEN         LL_RCC_TIM11_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM11_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11LPEN);
}

/**
  * @brief  Enable TIM10 peripheral clocks enable during CSleep mode
  * @rmtoll TIM10         TIM10LPEN         LL_RCC_TIM10_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM10_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10LPEN);
}

/**
  * @brief  Enable I3C2 peripheral clocks enable during CSleep mode
  * @rmtoll I3C2         I3C2LPEN         LL_RCC_I3C2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C2_EnableClockSleep(void)
{
  SET_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2LPEN);
}

#if defined(RCC_I3C3CFGR_I3C3LPEN)
/**
  * @brief  Enable I3C3 peripheral clocks enable during CSleep mode
  * @rmtoll I3C3         I3C3LPEN         LL_RCC_I3C3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C3_EnableClockSleep(void)
{
  SET_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3LPEN);
}
#endif /* RCC_I3C3CFGR_I3C3LPEN */

#if defined(RCC_I2C7CFGR_I2C7LPEN)
/**
  * @brief  Enable I2C7 peripheral clocks enable during CSleep mode
  * @rmtoll I2C7         I2C7LPEN         LL_RCC_I2C7_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C7_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7LPEN);
}
#endif /* RCC_I2C7CFGR_I2C7LPEN */

/**
  * @brief  Enable I3C1 peripheral clocks enable during CSleep mode
  * @rmtoll I3C1         I3C1LPEN         LL_RCC_I3C1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C1_EnableClockSleep(void)
{
  SET_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1LPEN);
}

#if defined(RCC_I2C5CFGR_I2C5LPEN)
/**
  * @brief  Enable I2C5 peripheral clocks enable during CSleep mode
  * @rmtoll I2C5         I2C5LPEN         LL_RCC_I2C5_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C5_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5LPEN);
}
#endif /* RCC_I2C5CFGR_I2C5LPEN */

#if defined(RCC_I2C6CFGR_I2C6LPEN)
/**
  * @brief  Enable I2C6 peripheral clocks enable during CSleep mode
  * @rmtoll I2C6         I2C6LPEN         LL_RCC_I2C6_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C6_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6LPEN);
}
#endif /* RCC_I2C6CFGR_I2C6LPEN */

#if defined(RCC_I2C3CFGR_I2C3LPEN)
/**
  * @brief  Enable I2C3 peripheral clocks enable during CSleep mode
  * @rmtoll I2C3         I2C3LPEN         LL_RCC_I2C3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C3_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3LPEN);
}
#endif /* RCC_I2C3CFGR_I2C3LPEN */

#if defined(RCC_I2C4CFGR_I2C4LPEN)
/**
  * @brief  Enable I2C4 peripheral clocks enable during CSleep mode
  * @rmtoll I2C4         I2C4LPEN         LL_RCC_I2C4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C4_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4LPEN);
}
#endif /* RCC_I2C4CFGR_I2C4LPEN */

/**
  * @brief  Enable I2C1 peripheral clocks enable during CSleep mode
  * @rmtoll I2C1         I2C1LPEN         LL_RCC_I2C1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C1_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1LPEN);
}

/**
  * @brief  Enable I2C2 peripheral clocks enable during CSleep mode
  * @rmtoll I2C2         I2C2LPEN         LL_RCC_I2C2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C2_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2LPEN);
}

/**
  * @brief  Enable UART4 peripheral clocks enable during CSleep mode
  * @rmtoll UART4         UART4LPEN         LL_RCC_UART4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART4_EnableClockSleep(void)
{
  SET_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4LPEN);
}

/**
  * @brief  Enable UART5 peripheral clocks enable during CSleep mode
  * @rmtoll UART5         UART5LPEN         LL_RCC_UART5_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART5_EnableClockSleep(void)
{
  SET_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5LPEN);
}

/**
  * @brief  Enable USART2 peripheral clocks enable during CSleep mode
  * @rmtoll USART2         USART2LPEN         LL_RCC_USART2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART2_EnableClockSleep(void)
{
  SET_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2LPEN);
}

/**
  * @brief  Enable USART3 peripheral clocks enable during CSleep mode
  * @rmtoll USART3         USART3LPEN         LL_RCC_USART3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART3_EnableClockSleep(void)
{
  SET_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3LPEN);
}

/**
  * @brief  Enable SPI3 peripheral clocks enable during CSleep mode
  * @rmtoll SPI3         SPI3LPEN         LL_RCC_SPI3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI3_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3LPEN);
}

/**
  * @brief  Enable SPDIFRX peripheral clocks enable during CSleep mode
  * @rmtoll SPDIFRX         SPDIFRXLPEN         LL_RCC_SPDIFRX_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPDIFRX_EnableClockSleep(void)
{
  SET_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXLPEN);
}

/**
  * @brief  Enable LPTIM2 peripheral clocks enable during CSleep mode
  * @rmtoll LPTIM2         LPTIM2LPEN         LL_RCC_LPTIM2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM2_EnableClockSleep(void)
{
  SET_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2LPEN);
}

/**
  * @brief  Enable SPI2 peripheral clocks enable during CSleep mode
  * @rmtoll SPI2         SPI2LPEN         LL_RCC_SPI2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI2_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2LPEN);
}

/**
  * @brief  Enable TIM14 peripheral clocks enable during CSleep mode
  * @rmtoll TIM14         TIM14LPEN         LL_RCC_TIM14_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM14_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14LPEN);
}

/**
  * @brief  Enable LPTIM1 peripheral clocks enable during CSleep mode
  * @rmtoll LPTIM1         LPTIM1LPEN         LL_RCC_LPTIM1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM1_EnableClockSleep(void)
{
  SET_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1LPEN);
}

/**
  * @brief  Enable TIM12 peripheral clocks enable during CSleep mode
  * @rmtoll TIM12         TIM12LPEN         LL_RCC_TIM12_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM12_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12LPEN);
}

/**
  * @brief  Enable TIM13 peripheral clocks enable during CSleep mode
  * @rmtoll TIM13         TIM13LPEN         LL_RCC_TIM13_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM13_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13LPEN);
}

/**
  * @brief  Enable TIM6 peripheral clocks enable during CSleep mode
  * @rmtoll TIM6         TIM6LPEN         LL_RCC_TIM6_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM6_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6LPEN);
}

/**
  * @brief  Enable TIM7 peripheral clocks enable during CSleep mode
  * @rmtoll TIM7         TIM7LPEN         LL_RCC_TIM7_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM7_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7LPEN);
}

/**
  * @brief  Enable TIM4 peripheral clocks enable during CSleep mode
  * @rmtoll TIM4         TIM4LPEN         LL_RCC_TIM4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM4_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4LPEN);
}

/**
  * @brief  Enable TIM5 peripheral clocks enable during CSleep mode
  * @rmtoll TIM5         TIM5LPEN         LL_RCC_TIM5_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM5_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5LPEN);
}

/**
  * @brief  Enable TIM2 peripheral clocks enable during CSleep mode
  * @rmtoll TIM2         TIM2LPEN         LL_RCC_TIM2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM2_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2LPEN);
}

/**
  * @brief  Enable TIM3 peripheral clocks enable during CSleep mode
  * @rmtoll TIM3         TIM3LPEN         LL_RCC_TIM3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM3_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3LPEN);
}

/**
  * @brief  Disable TIM11 peripheral clocks during CSleep mode
  * @rmtoll TIM11         TIM11LPEN         LL_RCC_TIM11_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM11_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11LPEN);
}

/**
  * @brief  Disable TIM10 peripheral clocks during CSleep mode
  * @rmtoll TIM10         TIM10LPEN         LL_RCC_TIM10_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM10_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10LPEN);
}

/**
  * @brief  Disable I3C2 peripheral clocks during CSleep mode
  * @rmtoll I3C2         I3C2LPEN         LL_RCC_I3C2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2LPEN);
}

#if defined(RCC_I3C3CFGR_I3C3LPEN)
/**
  * @brief  Disable I3C3 peripheral clocks during CSleep mode
  * @rmtoll I3C3         I3C3LPEN         LL_RCC_I3C3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3LPEN);
}
#endif /* RCC_I3C3CFGR_I3C3LPEN */

#if defined(RCC_I2C7CFGR_I2C7LPEN)
/**
  * @brief  Disable I2C7 peripheral clocks during CSleep mode
  * @rmtoll I2C7         I2C7LPEN         LL_RCC_I2C7_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C7_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7LPEN);
}
#endif /* RCC_I2C7CFGR_I2C7LPEN */

/**
  * @brief  Disable I3C1 peripheral clocks during CSleep mode
  * @rmtoll I3C1         I3C1LPEN         LL_RCC_I3C1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1LPEN);
}

#if defined(RCC_I2C5CFGR_I2C5LPEN)
/**
  * @brief  Disable I2C5 peripheral clocks during CSleep mode
  * @rmtoll I2C5         I2C5LPEN         LL_RCC_I2C5_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C5_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5LPEN);
}
#endif /* RCC_I2C5CFGR_I2C5LPEN */


#if defined(RCC_I2C6CFGR_I2C6LPEN)
/**
  * @brief  Disable I2C6 peripheral clocks during CSleep mode
  * @rmtoll I2C6         I2C6LPEN         LL_RCC_I2C6_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C6_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6LPEN);
}
#endif /* RCC_I2C6CFGR_I2C6LPEN */

#if defined(RCC_I2C3CFGR_I2C3LPEN)
/**
  * @brief  Disable I2C3 peripheral clocks during CSleep mode
  * @rmtoll I2C3         I2C3LPEN         LL_RCC_I2C3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3LPEN);
}
#endif /* RCC_I2C3CFGR_I2C3LPEN */

#if defined(RCC_I2C4CFGR_I2C4LPEN)
/**
  * @brief  Disable I2C4 peripheral clocks during CSleep mode
  * @rmtoll I2C4         I2C4LPEN         LL_RCC_I2C4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4LPEN);
}
#endif /* RCC_I2C4CFGR_I2C4LPEN */

/**
  * @brief  Disable I2C1 peripheral clocks during CSleep mode
  * @rmtoll I2C1         I2C1LPEN         LL_RCC_I2C1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1LPEN);
}

/**
  * @brief  Disable I2C2 peripheral clocks during CSleep mode
  * @rmtoll I2C2         I2C2LPEN         LL_RCC_I2C2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2LPEN);
}

/**
  * @brief  Disable UART4 peripheral clocks during CSleep mode
  * @rmtoll UART4         UART4LPEN         LL_RCC_UART4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4LPEN);
}

/**
  * @brief  Disable UART5 peripheral clocks during CSleep mode
  * @rmtoll UART5         UART5LPEN         LL_RCC_UART5_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART5_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5LPEN);
}

/**
  * @brief  Disable USART2 peripheral clocks during CSleep mode
  * @rmtoll USART2         USART2LPEN         LL_RCC_USART2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2LPEN);
}

/**
  * @brief  Disable USART3 peripheral clocks during CSleep mode
  * @rmtoll USART3         USART3LPEN         LL_RCC_USART3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3LPEN);
}

/**
  * @brief  Disable SPI3 peripheral clocks during CSleep mode
  * @rmtoll SPI3         SPI3LPEN         LL_RCC_SPI3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3LPEN);
}

/**
  * @brief  Disable SPDIFRX peripheral clocks during CSleep mode
  * @rmtoll SPDIFRX         SPDIFRXLPEN         LL_RCC_SPDIFRX_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPDIFRX_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXLPEN);
}

/**
  * @brief  Disable LPTIM2 peripheral clocks during CSleep mode
  * @rmtoll LPTIM2         LPTIM2LPEN         LL_RCC_LPTIM2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2LPEN);
}

/**
  * @brief  Disable SPI2 peripheral clocks during CSleep mode
  * @rmtoll SPI2         SPI2LPEN         LL_RCC_SPI2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2LPEN);
}

/**
  * @brief  Disable TIM14 peripheral clocks during CSleep mode
  * @rmtoll TIM14         TIM14LPEN         LL_RCC_TIM14_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM14_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14LPEN);
}

/**
  * @brief  Disable LPTIM1 peripheral clocks during CSleep mode
  * @rmtoll LPTIM1         LPTIM1LPEN         LL_RCC_LPTIM1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1LPEN);
}

/**
  * @brief  Disable TIM12 peripheral clocks during CSleep mode
  * @rmtoll TIM12         TIM12LPEN         LL_RCC_TIM12_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM12_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12LPEN);
}

/**
  * @brief  Disable TIM13 peripheral clocks during CSleep mode
  * @rmtoll TIM13         TIM13LPEN         LL_RCC_TIM13_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM13_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13LPEN);
}

/**
  * @brief  Disable TIM6 peripheral clocks during CSleep mode
  * @rmtoll TIM6         TIM6LPEN         LL_RCC_TIM6_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM6_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6LPEN);
}

/**
  * @brief  Disable TIM7 peripheral clocks during CSleep mode
  * @rmtoll TIM7         TIM7LPEN         LL_RCC_TIM7_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM7_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7LPEN);
}

/**
  * @brief  Disable TIM4 peripheral clocks during CSleep mode
  * @rmtoll TIM4         TIM4LPEN         LL_RCC_TIM4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4LPEN);
}

/**
  * @brief  Disable TIM5 peripheral clocks during CSleep mode
  * @rmtoll TIM5         TIM5LPEN         LL_RCC_TIM5_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM5_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5LPEN);
}

/**
  * @brief  Disable TIM2 peripheral clocks during CSleep mode
  * @rmtoll TIM2         TIM2LPEN         LL_RCC_TIM2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2LPEN);
}

/**
  * @brief  Disable TIM3 peripheral clocks during CSleep mode
  * @rmtoll TIM3         TIM3LPEN         LL_RCC_TIM3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3LPEN);
}

/**
  * @brief  Assert TIM11 reset
  * @rmtoll TIM11         TIM11RST         LL_RCC_TIM11_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM11_ForceReset(void)
{
  SET_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11RST);
}

/**
  * @brief  Assert TIM10 reset
  * @rmtoll TIM10         TIM10RST         LL_RCC_TIM10_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM10_ForceReset(void)
{
  SET_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10RST);
}

/**
  * @brief  Assert I3C2 reset
  * @rmtoll I3C2         I3C2RST         LL_RCC_I3C2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C2_ForceReset(void)
{
  SET_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2RST);
}

#if defined(RCC_I3C3CFGR_I3C3RST)
/**
  * @brief  Assert I3C3 reset
  * @rmtoll I3C3         I3C3RST         LL_RCC_I3C3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C3_ForceReset(void)
{
  SET_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3RST);
}
#endif /* RCC_I3C3CFGR_I3C3RST */

#if defined(RCC_I2C7CFGR_I2C7RST)
/**
  * @brief  Assert I2C7 reset
  * @rmtoll I2C7         I2C7RST         LL_RCC_I2C7_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C7_ForceReset(void)
{
  SET_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7RST);
}
#endif /* RCC_I2C7CFGR_I2C7RST */

/**
  * @brief  Assert I3C1 reset
  * @rmtoll I3C1         I3C1RST         LL_RCC_I3C1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C1_ForceReset(void)
{
  SET_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1RST);
}

#if defined(RCC_I2C5CFGR_I2C5RST)
/**
  * @brief  Assert I2C5 reset
  * @rmtoll I2C5         I2C5RST         LL_RCC_I2C5_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C5_ForceReset(void)
{
  SET_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5RST);
}
#endif /* RCC_I2C5CFGR_I2C5RST */

#if defined(RCC_I2C6CFGR_I2C6RST)
/**
  * @brief  Assert I2C6 reset
  * @rmtoll I2C6         I2C6RST         LL_RCC_I2C6_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C6_ForceReset(void)
{
  SET_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6RST);
}
#endif /* RCC_I2C6CFGR_I2C6RST */

#if defined(RCC_I2C3CFGR_I2C3RST)
/**
  * @brief  Assert I2C3 reset
  * @rmtoll I2C3         I2C3RST         LL_RCC_I2C3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C3_ForceReset(void)
{
  SET_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3RST);
}
#endif /* RCC_I2C3CFGR_I2C3RST */

#if defined(RCC_I2C4CFGR_I2C4RST)
/**
  * @brief  Assert I2C4 reset
  * @rmtoll I2C4         I2C4RST         LL_RCC_I2C4_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C4_ForceReset(void)
{
  SET_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4RST);
}
#endif /* RCC_I2C4CFGR_I2C4RST */

/**
  * @brief  Assert I2C1 reset
  * @rmtoll I2C1         I2C1RST         LL_RCC_I2C1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C1_ForceReset(void)
{
  SET_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1RST);
}

/**
  * @brief  Assert I2C2 reset
  * @rmtoll I2C2         I2C2RST         LL_RCC_I2C2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C2_ForceReset(void)
{
  SET_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2RST);
}

/**
  * @brief  Assert UART4 reset
  * @rmtoll UART4         UART4RST         LL_RCC_UART4_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART4_ForceReset(void)
{
  SET_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4RST);
}

/**
  * @brief  Assert UART5 reset
  * @rmtoll UART5         UART5RST         LL_RCC_UART5_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART5_ForceReset(void)
{
  SET_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5RST);
}

/**
  * @brief  Assert USART2 reset
  * @rmtoll USART2         USART2RST         LL_RCC_USART2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART2_ForceReset(void)
{
  SET_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2RST);
}

/**
  * @brief  Assert USART3 reset
  * @rmtoll USART3         USART3RST         LL_RCC_USART3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART3_ForceReset(void)
{
  SET_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3RST);
}

/**
  * @brief  Assert SPI3 reset
  * @rmtoll SPI3         SPI3RST         LL_RCC_SPI3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI3_ForceReset(void)
{
  SET_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3RST);
}

/**
  * @brief  Assert SPDIFRX reset
  * @rmtoll SPDIFRX         SPDIFRXRST         LL_RCC_SPDIFRX_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPDIFRX_ForceReset(void)
{
  SET_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXRST);
}

/**
  * @brief  Assert LPTIM2 reset
  * @rmtoll LPTIM2         LPTIM2RST         LL_RCC_LPTIM2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM2_ForceReset(void)
{
  SET_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2RST);
}

/**
  * @brief  Assert SPI2 reset
  * @rmtoll SPI2         SPI2RST         LL_RCC_SPI2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI2_ForceReset(void)
{
  SET_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2RST);
}

/**
  * @brief  Assert TIM14 reset
  * @rmtoll TIM14         TIM14RST         LL_RCC_TIM14_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM14_ForceReset(void)
{
  SET_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14RST);
}

/**
  * @brief  Assert LPTIM1 reset
  * @rmtoll LPTIM1         LPTIM1RST         LL_RCC_LPTIM1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM1_ForceReset(void)
{
  SET_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1RST);
}

/**
  * @brief  Assert TIM12 reset
  * @rmtoll TIM12         TIM12RST         LL_RCC_TIM12_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM12_ForceReset(void)
{
  SET_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12RST);
}

/**
  * @brief  Assert TIM13 reset
  * @rmtoll TIM13         TIM13RST         LL_RCC_TIM13_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM13_ForceReset(void)
{
  SET_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13RST);
}

/**
  * @brief  Assert TIM6 reset
  * @rmtoll TIM6         TIM6RST         LL_RCC_TIM6_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM6_ForceReset(void)
{
  SET_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6RST);
}

/**
  * @brief  Assert TIM7 reset
  * @rmtoll TIM7         TIM7RST         LL_RCC_TIM7_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM7_ForceReset(void)
{
  SET_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7RST);
}

/**
  * @brief  Assert TIM4 reset
  * @rmtoll TIM4         TIM4RST         LL_RCC_TIM4_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM4_ForceReset(void)
{
  SET_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4RST);
}

/**
  * @brief  Assert TIM5 reset
  * @rmtoll TIM5         TIM5RST         LL_RCC_TIM5_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM5_ForceReset(void)
{
  SET_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5RST);
}

/**
  * @brief  Assert TIM2 reset
  * @rmtoll TIM2         TIM2RST         LL_RCC_TIM2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM2_ForceReset(void)
{
  SET_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2RST);
}

/**
  * @brief  Assert TIM3 reset
  * @rmtoll TIM3         TIM3RST         LL_RCC_TIM3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM3_ForceReset(void)
{
  SET_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3RST);
}

/**
  * @brief  Release TIM11 reset
  * @rmtoll TIM11         TIM11RST         LL_RCC_TIM11_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM11_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM11CFGR, RCC_TIM11CFGR_TIM11RST);
}

/**
  * @brief  Release TIM10 reset
  * @rmtoll TIM10         TIM10RST         LL_RCC_TIM10_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM10_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM10CFGR, RCC_TIM10CFGR_TIM10RST);
}

/**
  * @brief  Release I3C2 reset
  * @rmtoll I3C2         I3C2RST         LL_RCC_I3C2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I3C2CFGR, RCC_I3C2CFGR_I3C2RST);
}

#if defined(RCC_I3C3CFGR_I3C3RST)
/**
  * @brief  Release I3C3 reset
  * @rmtoll I3C3         I3C3RST         LL_RCC_I3C3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I3C3CFGR, RCC_I3C3CFGR_I3C3RST);
}
#endif /* RCC_I3C3CFGR_I3C3RST */

#if defined(RCC_I2C7CFGR_I2C7RST)
/**
  * @brief  Release I2C7 reset
  * @rmtoll I2C7         I2C7RST         LL_RCC_I2C7_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C7_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C7CFGR, RCC_I2C7CFGR_I2C7RST);
}
#endif /* RCC_I2C7CFGR_I2C7RST */

/**
  * @brief  Release I3C1 reset
  * @rmtoll I3C1         I3C1RST         LL_RCC_I3C1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I3C1CFGR, RCC_I3C1CFGR_I3C1RST);
}

#if defined(RCC_I2C5CFGR_I2C5RST)
/**
  * @brief  Release I2C5 reset
  * @rmtoll I2C5         I2C5RST         LL_RCC_I2C5_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C5_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C5CFGR, RCC_I2C5CFGR_I2C5RST);
}
#endif /* RCC_I2C5CFGR_I2C5RST */

#if defined(RCC_I2C6CFGR_I2C6RST)
/**
  * @brief  Release I2C6 reset
  * @rmtoll I2C6         I2C6RST         LL_RCC_I2C6_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C6_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C6CFGR, RCC_I2C6CFGR_I2C6RST);
}
#endif /* RCC_I2C6CFGR_I2C6RST */

#if defined(RCC_I2C3CFGR_I2C3RST)
/**
  * @brief  Release I2C3 reset
  * @rmtoll I2C3         I2C3RST         LL_RCC_I2C3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C3CFGR, RCC_I2C3CFGR_I2C3RST);
}
#endif /* RCC_I2C3CFGR_I2C3RST */

#if defined(RCC_I2C4CFGR_I2C4RST)
/**
  * @brief  Release I2C4 reset
  * @rmtoll I2C4         I2C4RST         LL_RCC_I2C4_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C4_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C4CFGR, RCC_I2C4CFGR_I2C4RST);
}
#endif /* RCC_I2C4CFGR_I2C4RST */

/**
  * @brief  Release I2C1 reset
  * @rmtoll I2C1         I2C1RST         LL_RCC_I2C1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C1CFGR, RCC_I2C1CFGR_I2C1RST);
}

/**
  * @brief  Release I2C2 reset
  * @rmtoll I2C2         I2C2RST         LL_RCC_I2C2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C2CFGR, RCC_I2C2CFGR_I2C2RST);
}

/**
  * @brief  Release UART4 reset
  * @rmtoll UART4         UART4RST         LL_RCC_UART4_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART4_ReleaseReset(void)
{
  CLEAR_BIT(RCC->UART4CFGR, RCC_UART4CFGR_UART4RST);
}

/**
  * @brief  Release UART5 reset
  * @rmtoll UART5         UART5RST         LL_RCC_UART5_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART5_ReleaseReset(void)
{
  CLEAR_BIT(RCC->UART5CFGR, RCC_UART5CFGR_UART5RST);
}

/**
  * @brief  Release USART2 reset
  * @rmtoll USART2         USART2RST         LL_RCC_USART2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USART2CFGR, RCC_USART2CFGR_USART2RST);
}

/**
  * @brief  Release USART3 reset
  * @rmtoll USART3         USART3RST         LL_RCC_USART3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USART3CFGR, RCC_USART3CFGR_USART3RST);
}

/**
  * @brief  Release SPI3 reset
  * @rmtoll SPI3         SPI3RST         LL_RCC_SPI3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI3CFGR, RCC_SPI3CFGR_SPI3RST);
}

/**
  * @brief  Release SPDIFRX reset
  * @rmtoll SPDIFRX         SPDIFRXRST         LL_RCC_SPDIFRX_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPDIFRX_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPDIFRXCFGR, RCC_SPDIFRXCFGR_SPDIFRXRST);
}

/**
  * @brief  Release LPTIM2 reset
  * @rmtoll LPTIM2         LPTIM2RST         LL_RCC_LPTIM2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LPTIM2CFGR, RCC_LPTIM2CFGR_LPTIM2RST);
}

/**
  * @brief  Release SPI2 reset
  * @rmtoll SPI2         SPI2RST         LL_RCC_SPI2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI2CFGR, RCC_SPI2CFGR_SPI2RST);
}

/**
  * @brief  Release TIM14 reset
  * @rmtoll TIM14         TIM14RST         LL_RCC_TIM14_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM14_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM14CFGR, RCC_TIM14CFGR_TIM14RST);
}

/**
  * @brief  Release LPTIM1 reset
  * @rmtoll LPTIM1         LPTIM1RST         LL_RCC_LPTIM1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LPTIM1CFGR, RCC_LPTIM1CFGR_LPTIM1RST);
}

/**
  * @brief  Release TIM12 reset
  * @rmtoll TIM12         TIM12RST         LL_RCC_TIM12_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM12_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM12CFGR, RCC_TIM12CFGR_TIM12RST);
}

/**
  * @brief  Release TIM13 reset
  * @rmtoll TIM13         TIM13RST         LL_RCC_TIM13_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM13_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM13CFGR, RCC_TIM13CFGR_TIM13RST);
}

/**
  * @brief  Release TIM6 reset
  * @rmtoll TIM6         TIM6RST         LL_RCC_TIM6_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM6_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM6CFGR, RCC_TIM6CFGR_TIM6RST);
}

/**
  * @brief  Release TIM7 reset
  * @rmtoll TIM7         TIM7RST         LL_RCC_TIM7_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM7_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM7CFGR, RCC_TIM7CFGR_TIM7RST);
}

/**
  * @brief  Release TIM4 reset
  * @rmtoll TIM4         TIM4RST         LL_RCC_TIM4_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM4_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM4CFGR, RCC_TIM4CFGR_TIM4RST);
}

/**
  * @brief  Release TIM5 reset
  * @rmtoll TIM5         TIM5RST         LL_RCC_TIM5_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM5_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM5CFGR, RCC_TIM5CFGR_TIM5RST);
}

/**
  * @brief  Release TIM2 reset
  * @rmtoll TIM2         TIM2RST         LL_RCC_TIM2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM2CFGR, RCC_TIM2CFGR_TIM2RST);
}

/**
  * @brief  Release TIM3 reset
  * @rmtoll TIM3         TIM3RST         LL_RCC_TIM3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM3CFGR, RCC_TIM3CFGR_TIM3RST);
}

#if defined(RCC_UART8CFGR_UART8EN)
/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB2 APB2
  * @{
  */
/**
  * @brief  Enable UART8  peripheral clock
  * @rmtoll UART8         UART8EN         LL_RCC_UART8_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART8_EnableClock(void)
{
  SET_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8EN);
}
#endif /* RCC_UART8CFGR_UART8EN */

/**
  * @brief  Enable UART7  peripheral clock
  * @rmtoll UART7         UART7EN         LL_RCC_UART7_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART7_EnableClock(void)
{
  SET_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7EN);
}

#if defined(RCC_SPI7CFGR_SPI7EN)
/**
  * @brief  Enable SPI7  peripheral clock
  * @rmtoll SPI7         SPI7EN         LL_RCC_SPI7_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI7_EnableClock(void)
{
  SET_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7EN);
}
#endif /* RCC_SPI7CFGR_SPI7EN */

#if defined(RCC_SPI6CFGR_SPI6EN)
/**
  * @brief  Enable SPI6  peripheral clock
  * @rmtoll SPI6         SPI6EN         LL_RCC_SPI6_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI6_EnableClock(void)
{
  SET_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6EN);
}
#endif /* RCC_SPI6CFGR_SPI6EN */

/**
  * @brief  Enable SAI4  peripheral clock
  * @rmtoll SAI4         SAI4EN         LL_RCC_SAI4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI4_EnableClock(void)
{
  SET_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4EN);
}

/**
  * @brief  Enable USART1  peripheral clock
  * @rmtoll USART1         USART1EN         LL_RCC_USART1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART1_EnableClock(void)
{
  SET_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1EN);
}

#if defined(RCC_TIM20CFGR_TIM20EN)
/**
  * @brief  Enable TIM20  peripheral clock
  * @rmtoll TIM20         TIM20EN         LL_RCC_TIM20_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM20_EnableClock(void)
{
  SET_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20EN);
}
#endif /* RCC_TIM20CFGR_TIM20EN */

/**
  * @brief  Enable FDCAN  peripheral clock
  * @rmtoll FDCAN         FDCANEN         LL_RCC_FDCAN_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FDCAN_EnableClock(void)
{
  SET_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANEN);
}

#if defined(RCC_UART9CFGR_UART9EN)
/**
  * @brief  Enable UART9  peripheral clock
  * @rmtoll UART9         UART9EN         LL_RCC_UART9_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART9_EnableClock(void)
{
  SET_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9EN);
}
#endif /* RCC_UART9CFGR_UART9EN */

/**
  * @brief  Enable SAI3  peripheral clock
  * @rmtoll SAI3         SAI3EN         LL_RCC_SAI3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI3_EnableClock(void)
{
  SET_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3EN);
}

/**
  * @brief  Enable SAI2  peripheral clock
  * @rmtoll SAI2         SAI2EN         LL_RCC_SAI2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI2_EnableClock(void)
{
  SET_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2EN);
}

/**
  * @brief  Enable SAI1  peripheral clock
  * @rmtoll SAI1         SAI1EN         LL_RCC_SAI1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI1_EnableClock(void)
{
  SET_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1EN);
}

/**
  * @brief  Enable SPI5  peripheral clock
  * @rmtoll SPI5         SPI5EN         LL_RCC_SPI5_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI5_EnableClock(void)
{
  SET_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5EN);
}

/**
  * @brief  Enable TIM17  peripheral clock
  * @rmtoll TIM17         TIM17EN         LL_RCC_TIM17_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM17_EnableClock(void)
{
  SET_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17EN);
}

/**
  * @brief  Enable TIM16  peripheral clock
  * @rmtoll TIM16         TIM16EN         LL_RCC_TIM16_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM16_EnableClock(void)
{
  SET_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16EN);
}

/**
  * @brief  Enable TIM15  peripheral clock
  * @rmtoll TIM15         TIM15EN         LL_RCC_TIM15_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM15_EnableClock(void)
{
  SET_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15EN);
}

/**
  * @brief  Enable SPI4  peripheral clock
  * @rmtoll SPI4         SPI4EN         LL_RCC_SPI4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI4_EnableClock(void)
{
  SET_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4EN);
}

/**
  * @brief  Enable SPI1  peripheral clock
  * @rmtoll SPI1         SPI1EN         LL_RCC_SPI1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI1_EnableClock(void)
{
  SET_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1EN);
}

/**
  * @brief  Enable USART6  peripheral clock
  * @rmtoll USART6         USART6EN         LL_RCC_USART6_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART6_EnableClock(void)
{
  SET_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6EN);
}

/**
  * @brief  Enable TIM8  peripheral clock
  * @rmtoll TIM8         TIM8EN         LL_RCC_TIM8_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM8_EnableClock(void)
{
  SET_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8EN);
}

/**
  * @brief  Enable TIM1  peripheral clock
  * @rmtoll TIM1         TIM1EN         LL_RCC_TIM1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM1_EnableClock(void)
{
  SET_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1EN);
}

#if defined(RCC_UART8CFGR_UART8EN)
/**
  * @brief  Disable UART8  peripheral clock
  * @rmtoll UART8         UART8EN         LL_RCC_UART8_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART8_DisableClock(void)
{
  CLEAR_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8EN);
}
#endif /* RCC_UART8CFGR_UART8EN */

/**
  * @brief  Disable UART7  peripheral clock
  * @rmtoll UART7         UART7EN         LL_RCC_UART7_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART7_DisableClock(void)
{
  CLEAR_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7EN);
}

#if defined(RCC_SPI7CFGR_SPI7EN)
/**
  * @brief  Disable SPI7  peripheral clock
  * @rmtoll SPI7         SPI7EN         LL_RCC_SPI7_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI7_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7EN);
}
#endif /* RCC_SPI7CFGR_SPI7EN */

#if defined(RCC_SPI6CFGR_SPI6EN)
/**
  * @brief  Disable SPI6  peripheral clock
  * @rmtoll SPI6         SPI6EN         LL_RCC_SPI6_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI6_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6EN);
}
#endif /* RCC_SPI6CFGR_SPI6EN */

/**
  * @brief  Disable SAI4  peripheral clock
  * @rmtoll SAI4         SAI4EN         LL_RCC_SAI4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI4_DisableClock(void)
{
  CLEAR_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4EN);
}

/**
  * @brief  Disable USART1  peripheral clock
  * @rmtoll USART1         USART1EN         LL_RCC_USART1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART1_DisableClock(void)
{
  CLEAR_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1EN);
}

#if defined(RCC_TIM20CFGR_TIM20EN)
/**
  * @brief  Disable TIM20  peripheral clock
  * @rmtoll TIM20         TIM20EN         LL_RCC_TIM20_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM20_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20EN);
}
#endif /* RCC_TIM20CFGR_TIM20EN*/

/**
  * @brief  Disable FDCAN  peripheral clock
  * @rmtoll FDCAN         FDCANEN         LL_RCC_FDCAN_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FDCAN_DisableClock(void)
{
  CLEAR_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANEN);
}

#if defined(RCC_UART9CFGR_UART9EN)
/**
  * @brief  Disable UART9  peripheral clock
  * @rmtoll UART9         UART9EN         LL_RCC_UART9_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART9_DisableClock(void)
{
  CLEAR_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9EN);
}
#endif /* RCC_UART9CFGR_UART9EN */

/**
  * @brief  Disable SAI3  peripheral clock
  * @rmtoll SAI3         SAI3EN         LL_RCC_SAI3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI3_DisableClock(void)
{
  CLEAR_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3EN);
}

/**
  * @brief  Disable SAI2  peripheral clock
  * @rmtoll SAI2         SAI2EN         LL_RCC_SAI2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI2_DisableClock(void)
{
  CLEAR_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2EN);
}

/**
  * @brief  Disable SAI1  peripheral clock
  * @rmtoll SAI1         SAI1EN         LL_RCC_SAI1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI1_DisableClock(void)
{
  CLEAR_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1EN);
}

/**
  * @brief  Disable SPI5  peripheral clock
  * @rmtoll SPI5         SPI5EN         LL_RCC_SPI5_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI5_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5EN);
}

/**
  * @brief  Disable TIM17  peripheral clock
  * @rmtoll TIM17         TIM17EN         LL_RCC_TIM17_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM17_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17EN);
}

/**
  * @brief  Disable TIM16  peripheral clock
  * @rmtoll TIM16         TIM16EN         LL_RCC_TIM16_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM16_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16EN);
}

/**
  * @brief  Disable TIM15  peripheral clock
  * @rmtoll TIM15         TIM15EN         LL_RCC_TIM15_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM15_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15EN);
}

/**
  * @brief  Disable SPI4  peripheral clock
  * @rmtoll SPI4         SPI4EN         LL_RCC_SPI4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI4_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4EN);
}

/**
  * @brief  Disable SPI1  peripheral clock
  * @rmtoll SPI1         SPI1EN         LL_RCC_SPI1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI1_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1EN);
}

/**
  * @brief  Disable USART6  peripheral clock
  * @rmtoll USART6         USART6EN         LL_RCC_USART6_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART6_DisableClock(void)
{
  CLEAR_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6EN);
}

/**
  * @brief  Disable TIM8  peripheral clock
  * @rmtoll TIM8         TIM8EN         LL_RCC_TIM8_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM8_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8EN);
}

/**
  * @brief  Disable TIM1  peripheral clock
  * @rmtoll TIM1         TIM1EN         LL_RCC_TIM1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM1_DisableClock(void)
{
  CLEAR_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1EN);
}

#if defined(RCC_UART8CFGR_UART8LPEN)
/**
  * @brief  Enable UART8 peripheral clocks enable during CSleep mode
  * @rmtoll UART8         UART8LPEN         LL_RCC_UART8_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART8_EnableClockSleep(void)
{
  SET_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8LPEN);
}
#endif /* RCC_UART8CFGR_UART8LPEN */

/**
  * @brief  Enable UART7 peripheral clocks enable during CSleep mode
  * @rmtoll UART7         UART7LPEN         LL_RCC_UART7_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART7_EnableClockSleep(void)
{
  SET_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7LPEN);
}

#if defined(RCC_SPI7CFGR_SPI7LPEN)
/**
  * @brief  Enable SPI7 peripheral clocks enable during CSleep mode
  * @rmtoll SPI7         SPI7LPEN         LL_RCC_SPI7_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI7_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7LPEN);
}
#endif /* RCC_SPI7CFGR_SPI7LPEN */

#if defined(RCC_SPI6CFGR_SPI6LPEN)
/**
  * @brief  Enable SPI6 peripheral clocks enable during CSleep mode
  * @rmtoll SPI6         SPI6LPEN         LL_RCC_SPI6_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI6_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6LPEN);
}
#endif /* RCC_SPI6CFGR_SPI6LPEN */

/**
  * @brief  Enable SAI4 peripheral clocks enable during CSleep mode
  * @rmtoll SAI4         SAI4LPEN         LL_RCC_SAI4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI4_EnableClockSleep(void)
{
  SET_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4LPEN);
}

/**
  * @brief  Enable USART1 peripheral clocks enable during CSleep mode
  * @rmtoll USART1         USART1LPEN         LL_RCC_USART1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART1_EnableClockSleep(void)
{
  SET_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1LPEN);
}

#if defined(RCC_TIM20CFGR_TIM20LPEN)
/**
  * @brief  Enable TIM20 peripheral clocks enable during CSleep mode
  * @rmtoll TIM20         TIM20LPEN         LL_RCC_TIM20_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM20_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20LPEN);
}
#endif /* RCC_TIM20CFGR_TIM20LPEN */

/**
  * @brief  Enable FDCAN peripheral clocks enable during CSleep mode
  * @rmtoll FDCAN         FDCANLPEN         LL_RCC_FDCAN_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FDCAN_EnableClockSleep(void)
{
  SET_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANLPEN);
}

#if defined(RCC_UART9CFGR_UART9LPEN)
/**
  * @brief  Enable UART9 peripheral clocks enable during CSleep mode
  * @rmtoll UART9         UART9LPEN         LL_RCC_UART9_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART9_EnableClockSleep(void)
{
  SET_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9LPEN);
}
#endif /* RCC_UART9CFGR_UART9LPEN */

/**
  * @brief  Enable SAI3 peripheral clocks enable during CSleep mode
  * @rmtoll SAI3         SAI3LPEN         LL_RCC_SAI3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI3_EnableClockSleep(void)
{
  SET_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3LPEN);
}

/**
  * @brief  Enable SAI2 peripheral clocks enable during CSleep mode
  * @rmtoll SAI2         SAI2LPEN         LL_RCC_SAI2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI2_EnableClockSleep(void)
{
  SET_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2LPEN);
}

/**
  * @brief  Enable SAI1 peripheral clocks enable during CSleep mode
  * @rmtoll SAI1         SAI1LPEN         LL_RCC_SAI1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI1_EnableClockSleep(void)
{
  SET_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1LPEN);
}

/**
  * @brief  Enable SPI5 peripheral clocks enable during CSleep mode
  * @rmtoll SPI5         SPI5LPEN         LL_RCC_SPI5_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI5_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5LPEN);
}

/**
  * @brief  Enable TIM17 peripheral clocks enable during CSleep mode
  * @rmtoll TIM17         TIM17LPEN         LL_RCC_TIM17_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM17_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17LPEN);
}

/**
  * @brief  Enable TIM16 peripheral clocks enable during CSleep mode
  * @rmtoll TIM16         TIM16LPEN         LL_RCC_TIM16_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM16_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16LPEN);
}

/**
  * @brief  Enable TIM15 peripheral clocks enable during CSleep mode
  * @rmtoll TIM15         TIM15LPEN         LL_RCC_TIM15_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM15_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15LPEN);
}

/**
  * @brief  Enable SPI4 peripheral clocks enable during CSleep mode
  * @rmtoll SPI4         SPI4LPEN         LL_RCC_SPI4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI4_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4LPEN);
}

/**
  * @brief  Enable SPI1 peripheral clocks enable during CSleep mode
  * @rmtoll SPI1         SPI1LPEN         LL_RCC_SPI1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI1_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1LPEN);
}

/**
  * @brief  Enable USART6 peripheral clocks enable during CSleep mode
  * @rmtoll USART6         USART6LPEN         LL_RCC_USART6_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART6_EnableClockSleep(void)
{
  SET_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6LPEN);
}

/**
  * @brief  Enable TIM8 peripheral clocks enable during CSleep mode
  * @rmtoll TIM8         TIM8LPEN         LL_RCC_TIM8_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM8_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8LPEN);
}

/**
  * @brief  Enable TIM1 peripheral clocks enable during CSleep mode
  * @rmtoll TIM1         TIM1LPEN         LL_RCC_TIM1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM1_EnableClockSleep(void)
{
  SET_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1LPEN);
}

#if defined(RCC_UART8CFGR_UART8LPEN)
/**
  * @brief  Disable UART8 peripheral clocks during CSleep mode
  * @rmtoll UART8         UART8LPEN         LL_RCC_UART8_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART8_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8LPEN);
}
#endif /* RCC_UART8CFGR_UART8LPEN */

/**
  * @brief  Disable UART7 peripheral clocks during CSleep mode
  * @rmtoll UART7         UART7LPEN         LL_RCC_UART7_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART7_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7LPEN);
}

#if defined(RCC_SPI7CFGR_SPI7LPEN)
/**
  * @brief  Disable SPI7 peripheral clocks during CSleep mode
  * @rmtoll SPI7         SPI7LPEN         LL_RCC_SPI7_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI7_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7LPEN);
}
#endif /* RCC_SPI7CFGR_SPI7LPEN */

#if defined(RCC_SPI6CFGR_SPI6LPEN)
/**
  * @brief  Disable SPI6 peripheral clocks during CSleep mode
  * @rmtoll SPI6         SPI6LPEN         LL_RCC_SPI6_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI6_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6LPEN);
}
#endif /* RCC_SPI6CFGR_SPI6LPEN */

/**
  * @brief  Disable SAI4 peripheral clocks during CSleep mode
  * @rmtoll SAI4         SAI4LPEN         LL_RCC_SAI4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4LPEN);
}

/**
  * @brief  Disable USART1 peripheral clocks during CSleep mode
  * @rmtoll USART1         USART1LPEN         LL_RCC_USART1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1LPEN);
}

#if defined(RCC_TIM20CFGR_TIM20LPEN)
/**
  * @brief  Disable TIM20 peripheral clocks during CSleep mode
  * @rmtoll TIM20         TIM20LPEN         LL_RCC_TIM20_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM20_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20LPEN);
}
#endif /* RCC_TIM20CFGR_TIM20LPEN */

/**
  * @brief  Disable FDCAN peripheral clocks during CSleep mode
  * @rmtoll FDCAN         FDCANLPEN         LL_RCC_FDCAN_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FDCAN_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANLPEN);
}

#if defined(RCC_UART9CFGR_UART9LPEN)
/**
  * @brief  Disable UART9 peripheral clocks during CSleep mode
  * @rmtoll UART9         UART9LPEN         LL_RCC_UART9_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART9_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9LPEN);
}
#endif /* RCC_UART9CFGR_UART9LPEN */

/**
  * @brief  Disable SAI3 peripheral clocks during CSleep mode
  * @rmtoll SAI3         SAI3LPEN         LL_RCC_SAI3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3LPEN);
}

/**
  * @brief  Disable SAI2 peripheral clocks during CSleep mode
  * @rmtoll SAI2         SAI2LPEN         LL_RCC_SAI2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2LPEN);
}

/**
  * @brief  Disable SAI1 peripheral clocks during CSleep mode
  * @rmtoll SAI1         SAI1LPEN         LL_RCC_SAI1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1LPEN);
}

/**
  * @brief  Disable SPI5 peripheral clocks during CSleep mode
  * @rmtoll SPI5         SPI5LPEN         LL_RCC_SPI5_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI5_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5LPEN);
}

/**
  * @brief  Disable TIM17 peripheral clocks during CSleep mode
  * @rmtoll TIM17         TIM17LPEN         LL_RCC_TIM17_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM17_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17LPEN);
}

/**
  * @brief  Disable TIM16 peripheral clocks during CSleep mode
  * @rmtoll TIM16         TIM16LPEN         LL_RCC_TIM16_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM16_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16LPEN);
}

/**
  * @brief  Disable TIM15 peripheral clocks during CSleep mode
  * @rmtoll TIM15         TIM15LPEN         LL_RCC_TIM15_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM15_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15LPEN);
}

/**
  * @brief  Disable SPI4 peripheral clocks during CSleep mode
  * @rmtoll SPI4         SPI4LPEN         LL_RCC_SPI4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4LPEN);
}

/**
  * @brief  Disable SPI1 peripheral clocks during CSleep mode
  * @rmtoll SPI1         SPI1LPEN         LL_RCC_SPI1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1LPEN);
}

/**
  * @brief  Disable USART6 peripheral clocks during CSleep mode
  * @rmtoll USART6         USART6LPEN         LL_RCC_USART6_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART6_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6LPEN);
}

/**
  * @brief  Disable TIM8 peripheral clocks during CSleep mode
  * @rmtoll TIM8         TIM8LPEN         LL_RCC_TIM8_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM8_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8LPEN);
}

/**
  * @brief  Disable TIM1 peripheral clocks during CSleep mode
  * @rmtoll TIM1         TIM1LPEN         LL_RCC_TIM1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1LPEN);
}

#if defined(RCC_UART8CFGR_UART8RST)
/**
  * @brief  Assert UART8 reset
  * @rmtoll UART8         UART8RST         LL_RCC_UART8_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART8_ForceReset(void)
{
  SET_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8RST);
}
#endif /* RCC_UART8CFGR_UART8RST */

/**
  * @brief  Assert UART7 reset
  * @rmtoll UART7         UART7RST         LL_RCC_UART7_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART7_ForceReset(void)
{
  SET_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7RST);
}

#if defined(RCC_SPI7CFGR_SPI7RST)
/**
  * @brief  Assert SPI7 reset
  * @rmtoll SPI7         SPI7RST         LL_RCC_SPI7_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI7_ForceReset(void)
{
  SET_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7RST);
}
#endif /* RCC_SPI7CFGR_SPI7RST */

#if defined(RCC_SPI6CFGR_SPI6RST)
/**
  * @brief  Assert SPI6 reset
  * @rmtoll SPI6         SPI6RST         LL_RCC_SPI6_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI6_ForceReset(void)
{
  SET_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6RST);
}
#endif /* RCC_SPI6CFGR_SPI6RST */

/**
  * @brief  Assert SAI4 reset
  * @rmtoll SAI4         SAI4RST         LL_RCC_SAI4_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI4_ForceReset(void)
{
  SET_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4RST);
}

/**
  * @brief  Assert USART1 reset
  * @rmtoll USART1         USART1RST         LL_RCC_USART1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART1_ForceReset(void)
{
  SET_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1RST);
}

#if defined(RCC_TIM20CFGR_TIM20RST)
/**
  * @brief  Assert TIM20 reset
  * @rmtoll TIM20         TIM20RST         LL_RCC_TIM20_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM20_ForceReset(void)
{
  SET_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20RST);
}
#endif /* RCC_TIM20CFGR_TIM20RST */

/**
  * @brief  Assert FDCAN reset
  * @rmtoll FDCAN         FDCANRST         LL_RCC_FDCAN_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FDCAN_ForceReset(void)
{
  SET_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANRST);
}

#if defined(RCC_UART9CFGR_UART9RST)
/**
  * @brief  Assert UART9 reset
  * @rmtoll UART9         UART9RST         LL_RCC_UART9_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART9_ForceReset(void)
{
  SET_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9RST);
}
#endif /* RCC_UART9CFGR_UART9RST */

/**
  * @brief  Assert SAI3 reset
  * @rmtoll SAI3         SAI3RST         LL_RCC_SAI3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI3_ForceReset(void)
{
  SET_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3RST);
}

/**
  * @brief  Assert SAI2 reset
  * @rmtoll SAI2         SAI2RST         LL_RCC_SAI2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI2_ForceReset(void)
{
  SET_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2RST);
}

/**
  * @brief  Assert SAI1 reset
  * @rmtoll SAI1         SAI1RST         LL_RCC_SAI1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI1_ForceReset(void)
{
  SET_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1RST);
}

/**
  * @brief  Assert SPI5 reset
  * @rmtoll SPI5         SPI5RST         LL_RCC_SPI5_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI5_ForceReset(void)
{
  SET_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5RST);
}

/**
  * @brief  Assert TIM17 reset
  * @rmtoll TIM17         TIM17RST         LL_RCC_TIM17_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM17_ForceReset(void)
{
  SET_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17RST);
}

/**
  * @brief  Assert TIM16 reset
  * @rmtoll TIM16         TIM16RST         LL_RCC_TIM16_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM16_ForceReset(void)
{
  SET_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16RST);
}

/**
  * @brief  Assert TIM15 reset
  * @rmtoll TIM15         TIM15RST         LL_RCC_TIM15_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM15_ForceReset(void)
{
  SET_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15RST);
}

/**
  * @brief  Assert SPI4 reset
  * @rmtoll SPI4         SPI4RST         LL_RCC_SPI4_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI4_ForceReset(void)
{
  SET_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4RST);
}

/**
  * @brief  Assert SPI1 reset
  * @rmtoll SPI1         SPI1RST         LL_RCC_SPI1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI1_ForceReset(void)
{
  SET_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1RST);
}

/**
  * @brief  Assert USART6 reset
  * @rmtoll USART6         USART6RST         LL_RCC_USART6_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART6_ForceReset(void)
{
  SET_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6RST);
}

/**
  * @brief  Assert TIM8 reset
  * @rmtoll TIM8         TIM8RST         LL_RCC_TIM8_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM8_ForceReset(void)
{
  SET_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8RST);
}

/**
  * @brief  Assert TIM1 reset
  * @rmtoll TIM1         TIM1RST         LL_RCC_TIM1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM1_ForceReset(void)
{
  SET_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1RST);
}

#if defined(RCC_UART8CFGR_UART8RST)
/**
  * @brief  Release UART8 reset
  * @rmtoll UART8         UART8RST         LL_RCC_UART8_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART8_ReleaseReset(void)
{
  CLEAR_BIT(RCC->UART8CFGR, RCC_UART8CFGR_UART8RST);
}
#endif /* RCC_UART8CFGR_UART8RST */

/**
  * @brief  Release UART7 reset
  * @rmtoll UART7         UART7RST         LL_RCC_UART7_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART7_ReleaseReset(void)
{
  CLEAR_BIT(RCC->UART7CFGR, RCC_UART7CFGR_UART7RST);
}

#if defined(RCC_SPI7CFGR_SPI7RST)
/**
  * @brief  Release SPI7 reset
  * @rmtoll SPI7         SPI7RST         LL_RCC_SPI7_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI7_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI7CFGR, RCC_SPI7CFGR_SPI7RST);
}
#endif /* RCC_SPI7CFGR_SPI7RST */

#if defined(RCC_SPI6CFGR_SPI6RST)
/**
  * @brief  Release SPI6 reset
  * @rmtoll SPI6         SPI6RST         LL_RCC_SPI6_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI6_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI6CFGR, RCC_SPI6CFGR_SPI6RST);
}
#endif /* RCC_SPI6CFGR_SPI6RST */

/**
  * @brief  Release SAI4 reset
  * @rmtoll SAI4         SAI4RST         LL_RCC_SAI4_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI4_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SAI4CFGR, RCC_SAI4CFGR_SAI4RST);
}

/**
  * @brief  Release USART1 reset
  * @rmtoll USART1         USART1RST         LL_RCC_USART1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USART1CFGR, RCC_USART1CFGR_USART1RST);
}

#if defined(RCC_TIM20CFGR_TIM20RST)
/**
  * @brief  Release TIM20 reset
  * @rmtoll TIM20         TIM20RST         LL_RCC_TIM20_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM20_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM20CFGR, RCC_TIM20CFGR_TIM20RST);
}
#endif /* RCC_TIM20CFGR_TIM20RST */

/**
  * @brief  Release FDCAN reset
  * @rmtoll FDCAN         FDCANRST         LL_RCC_FDCAN_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_FDCAN_ReleaseReset(void)
{
  CLEAR_BIT(RCC->FDCANCFGR, RCC_FDCANCFGR_FDCANRST);
}

#if defined(RCC_UART9CFGR_UART9RST)
/**
  * @brief  Release UART9 reset
  * @rmtoll UART9         UART9RST         LL_RCC_UART9_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UART9_ReleaseReset(void)
{
  CLEAR_BIT(RCC->UART9CFGR, RCC_UART9CFGR_UART9RST);
}
#endif /* RCC_UART9CFGR_UART9RST */

/**
  * @brief  Release SAI3 reset
  * @rmtoll SAI3         SAI3RST         LL_RCC_SAI3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SAI3CFGR, RCC_SAI3CFGR_SAI3RST);
}

/**
  * @brief  Release SAI2 reset
  * @rmtoll SAI2         SAI2RST         LL_RCC_SAI2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SAI2CFGR, RCC_SAI2CFGR_SAI2RST);
}

/**
  * @brief  Release SAI1 reset
  * @rmtoll SAI1         SAI1RST         LL_RCC_SAI1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SAI1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SAI1CFGR, RCC_SAI1CFGR_SAI1RST);
}

/**
  * @brief  Release SPI5 reset
  * @rmtoll SPI5         SPI5RST         LL_RCC_SPI5_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI5_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI5CFGR, RCC_SPI5CFGR_SPI5RST);
}

/**
  * @brief  Release TIM17 reset
  * @rmtoll TIM17         TIM17RST         LL_RCC_TIM17_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM17_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM17CFGR, RCC_TIM17CFGR_TIM17RST);
}

/**
  * @brief  Release TIM16 reset
  * @rmtoll TIM16         TIM16RST         LL_RCC_TIM16_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM16_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM16CFGR, RCC_TIM16CFGR_TIM16RST);
}

/**
  * @brief  Release TIM15 reset
  * @rmtoll TIM15         TIM15RST         LL_RCC_TIM15_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM15_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM15CFGR, RCC_TIM15CFGR_TIM15RST);
}

/**
  * @brief  Release SPI4 reset
  * @rmtoll SPI4         SPI4RST         LL_RCC_SPI4_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI4_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI4CFGR, RCC_SPI4CFGR_SPI4RST);
}

/**
  * @brief  Release SPI1 reset
  * @rmtoll SPI1         SPI1RST         LL_RCC_SPI1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI1CFGR, RCC_SPI1CFGR_SPI1RST);
}

/**
  * @brief  Release USART6 reset
  * @rmtoll USART6         USART6RST         LL_RCC_USART6_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USART6_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USART6CFGR, RCC_USART6CFGR_USART6RST);
}

/**
  * @brief  Release TIM8 reset
  * @rmtoll TIM8         TIM8RST         LL_RCC_TIM8_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM8_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM8CFGR, RCC_TIM8CFGR_TIM8RST);
}

/**
  * @brief  Release TIM1 reset
  * @rmtoll TIM1         TIM1RST         LL_RCC_TIM1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TIM1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TIM1CFGR, RCC_TIM1CFGR_TIM1RST);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB3 APB3
  * @{
  */
/**
  * @brief  Enable HDP  peripheral clock
  * @rmtoll HDP         HDPEN         LL_RCC_HDP_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HDP_EnableClock(void)
{
  SET_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPEN);
}

/**
  * @brief  Enable WWDG1  peripheral clock
  * @rmtoll WWDG1         WWDG1EN         LL_RCC_WWDG1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG1_EnableClock(void)
{
  SET_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1EN);
}

/**
  * @brief  Enable IWDG4  peripheral clock
  * @rmtoll IWDG4         IWDG4EN         LL_RCC_IWDG4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG4_EnableClock(void)
{
  SET_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4EN);
}

/**
  * @brief  Enable VREF  peripheral clock
  * @rmtoll VREF         VREFEN         LL_RCC_VREF_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_VREF_EnableClock(void)
{
  SET_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFEN);
}

/**
  * @brief  Enable IWDG3  peripheral clock
  * @rmtoll IWDG3         IWDG3EN         LL_RCC_IWDG3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG3_EnableClock(void)
{
  SET_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3EN);
}

/**
  * @brief  Enable IWDG2  peripheral clock
  * @rmtoll IWDG2         IWDG2EN         LL_RCC_IWDG2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG2_EnableClock(void)
{
  SET_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2EN);
}

/**
  * @brief  Enable IWDG1  peripheral clock
  * @rmtoll IWDG1         IWDG1EN         LL_RCC_IWDG1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG1_EnableClock(void)
{
  SET_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1EN);
}

/**
  * @brief  Enable BSEC  peripheral clock
  * @rmtoll BSEC         BSECEN         LL_RCC_BSEC_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BSEC_EnableClock(void)
{
  SET_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECEN);
}

/**
  * @brief  Disable HDP  peripheral clock
  * @rmtoll HDP         HDPEN         LL_RCC_HDP_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HDP_DisableClock(void)
{
  CLEAR_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPEN);
}

/**
  * @brief  Disable WWDG1  peripheral clock
  * @rmtoll WWDG1         WWDG1EN         LL_RCC_WWDG1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG1_DisableClock(void)
{
  CLEAR_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1EN);
}

/**
  * @brief  Disable IWDG4  peripheral clock
  * @rmtoll IWDG4         IWDG4EN         LL_RCC_IWDG4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG4_DisableClock(void)
{
  CLEAR_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4EN);
}

/**
  * @brief  Disable VREF  peripheral clock
  * @rmtoll VREF         VREFEN         LL_RCC_VREF_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_VREF_DisableClock(void)
{
  CLEAR_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFEN);
}

/**
  * @brief  Disable IWDG3  peripheral clock
  * @rmtoll IWDG3         IWDG3EN         LL_RCC_IWDG3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG3_DisableClock(void)
{
  CLEAR_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3EN);
}

/**
  * @brief  Disable IWDG2  peripheral clock
  * @rmtoll IWDG2         IWDG2EN         LL_RCC_IWDG2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG2_DisableClock(void)
{
  CLEAR_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2EN);
}

/**
  * @brief  Disable IWDG1  peripheral clock
  * @rmtoll IWDG1         IWDG1EN         LL_RCC_IWDG1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG1_DisableClock(void)
{
  CLEAR_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1EN);
}

/**
  * @brief  Disable BSEC  peripheral clock
  * @rmtoll BSEC         BSECEN         LL_RCC_BSEC_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BSEC_DisableClock(void)
{
  CLEAR_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECEN);
}

/**
  * @brief  Enable WWDG1 peripheral clocks enable during CSleep mode
  * @rmtoll WWDG1         WWDG1LPEN         LL_RCC_WWDG1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG1_EnableClockSleep(void)
{
  SET_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1LPEN);
}

/**
  * @brief  Enable IWDG4 peripheral clocks enable during CSleep mode
  * @rmtoll IWDG4         IWDG4LPEN         LL_RCC_IWDG4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG4_EnableClockSleep(void)
{
  SET_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4LPEN);
}

/**
  * @brief  Enable VREF peripheral clocks enable during CSleep mode
  * @rmtoll VREF         VREFLPEN         LL_RCC_VREF_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_VREF_EnableClockSleep(void)
{
  SET_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFLPEN);
}

/**
  * @brief  Enable IWDG3 peripheral clocks enable during CSleep mode
  * @rmtoll IWDG3         IWDG3LPEN         LL_RCC_IWDG3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG3_EnableClockSleep(void)
{
  SET_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3LPEN);
}

/**
  * @brief  Enable IWDG2 peripheral clocks enable during CSleep mode
  * @rmtoll IWDG2         IWDG2LPEN         LL_RCC_IWDG2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG2_EnableClockSleep(void)
{
  SET_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2LPEN);
}

/**
  * @brief  Enable IWDG1 peripheral clocks enable during CSleep mode
  * @rmtoll IWDG1         IWDG1LPEN         LL_RCC_IWDG1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG1_EnableClockSleep(void)
{
  SET_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1LPEN);
}

/**
  * @brief  Enable BSEC peripheral clocks enable during CSleep mode
  * @rmtoll BSEC         BSECLPEN         LL_RCC_BSEC_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BSEC_EnableClockSleep(void)
{
  SET_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECLPEN);
}

/**
  * @brief  Disable WWDG1 peripheral clocks during CSleep mode
  * @rmtoll WWDG1         WWDG1LPEN         LL_RCC_WWDG1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1LPEN);
}

/**
  * @brief  Disable IWDG4 peripheral clocks during CSleep mode
  * @rmtoll IWDG4         IWDG4LPEN         LL_RCC_IWDG4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IWDG4CFGR, RCC_IWDG4CFGR_IWDG4LPEN);
}

/**
  * @brief  Disable VREF peripheral clocks during CSleep mode
  * @rmtoll VREF         VREFLPEN         LL_RCC_VREF_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_VREF_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFLPEN);
}

/**
  * @brief  Disable IWDG3 peripheral clocks during CSleep mode
  * @rmtoll IWDG3         IWDG3LPEN         LL_RCC_IWDG3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IWDG3CFGR, RCC_IWDG3CFGR_IWDG3LPEN);
}

/**
  * @brief  Disable IWDG2 peripheral clocks during CSleep mode
  * @rmtoll IWDG2         IWDG2LPEN         LL_RCC_IWDG2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IWDG2CFGR, RCC_IWDG2CFGR_IWDG2LPEN);
}

/**
  * @brief  Disable IWDG1 peripheral clocks during CSleep mode
  * @rmtoll IWDG1         IWDG1LPEN         LL_RCC_IWDG1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IWDG1CFGR, RCC_IWDG1CFGR_IWDG1LPEN);
}

/**
  * @brief  Disable BSEC peripheral clocks during CSleep mode
  * @rmtoll BSEC         BSECLPEN         LL_RCC_BSEC_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BSEC_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->BSECCFGR, RCC_BSECCFGR_BSECLPEN);
}

/**
  * @brief  Assert HDP reset
  * @rmtoll HDP         HDPRST         LL_RCC_HDP_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HDP_ForceReset(void)
{
  SET_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPRST);
}

/**
  * @brief  Assert WWDG1 reset
  * @rmtoll WWDG1         WWDG1RST         LL_RCC_WWDG1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG1_ForceReset(void)
{
  SET_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1RST);
}

/**
  * @brief  Assert VREF reset
  * @rmtoll VREF         VREFRST         LL_RCC_VREF_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_VREF_ForceReset(void)
{
  SET_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFRST);
}

/**
  * @brief  Release HDP reset
  * @rmtoll HDP         HDPRST         LL_RCC_HDP_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_HDP_ReleaseReset(void)
{
  CLEAR_BIT(RCC->HDPCFGR, RCC_HDPCFGR_HDPRST);
}

/**
  * @brief  Release WWDG1 reset
  * @rmtoll WWDG1         WWDG1RST         LL_RCC_WWDG1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->WWDG1CFGR, RCC_WWDG1CFGR_WWDG1RST);
}

/**
  * @brief  Release VREF reset
  * @rmtoll VREF         VREFRST         LL_RCC_VREF_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_VREF_ReleaseReset(void)
{
  CLEAR_BIT(RCC->VREFCFGR, RCC_VREFCFGR_VREFRST);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_APB4 APB4
  * @{
  */
#if defined(RCC_UCPDCFGR_UCPDEN)
/**
  * @brief  Enable UCPD1  peripheral clock
  * @rmtoll UCPD1         UCPD1EN         LL_RCC_UCPD1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UCPD1_EnableClock(void)
{
  SET_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDEN);
}
#endif /* RCC_UCPDCFGR_UCPDEN */
#if defined(RCC_BUSPERFMCFGR_BUSPERFMEN)
/**
  * @brief  Enable BUSPERF  peripheral clock
  * @rmtoll BUSPERF         BUSPERFEN         LL_RCC_BUSPERF_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BUSPERFM_EnableClock(void)
{
  SET_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMEN);
}
#endif /* RCC_BUSPERFMCFGR_BUSPERFMEN */
#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN)
/**
  * @brief  Enable USB3PCI  peripheral clock
  * @rmtoll USB3PCI         USB3PCIEN         LL_RCC_USB3PCI_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3PCIEPHY_EnableClock(void)
{
  SET_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN);
}
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN */

/**
  * @brief  Enable LTDC  peripheral clock
  * @rmtoll LTDC         LTDCEN         LL_RCC_LTDC_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LTDC_EnableClock(void)
{
  SET_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCEN);
}

#if defined(RCC_GICV2MCFGR_GICV2MEN)
/**
  * @brief  Enable GICV2M  peripheral clock
  * @rmtoll GICV2M         GICV2MEN         LL_RCC_GICV2M_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GICV2M_EnableClock(void)
{
  SET_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MEN);
}
#endif /* RCC_GICV2MCFGR_GICV2MEN */

#if defined(RCC_UCPDCFGR_UCPDEN)
/**
  * @brief  Disable UCPD1  peripheral clock
  * @rmtoll UCPD1         UCPD1EN         LL_RCC_UCPD1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UCPD1_DisableClock(void)
{
  CLEAR_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDEN);
}
#endif /* RCC_UCPDCFGR_UCPDEN */
#if defined(RCC_BUSPERFMCFGR_BUSPERFMEN)
/**
  * @brief  Disable BUSPERF  peripheral clock
  * @rmtoll BUSPERF         BUSPERFEN         LL_RCC_BUSPERF_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BUSPERFM_DisableClock(void)
{
  CLEAR_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMEN);
}
#endif /* RCC_BUSPERFMCFGR_BUSPERFMEN */
#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN)
/**
  * @brief  Disable USB3PCI  peripheral clock
  * @rmtoll USB3PCI         USB3PCIEN         LL_RCC_USB3PCI_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3PCIEPHY_DisableClock(void)
{
  CLEAR_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN);
}
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYEN */

/**
  * @brief  Disable LTDC  peripheral clock
  * @rmtoll LTDC         LTDCEN         LL_RCC_LTDC_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LTDC_DisableClock(void)
{
  CLEAR_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCEN);
}

#if defined(RCC_GICV2MCFGR_GICV2MEN)
/**
  * @brief  Disable GICV2M  peripheral clock
  * @rmtoll GICV2M         GICV2MEN         LL_RCC_GICV2M_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GICV2M_DisableClock(void)
{
  CLEAR_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MEN);
}
#endif /* RCC_GICV2MCFGR_GICV2MEN */

#if defined(RCC_UCPDCFGR_UCPDLPEN)
/**
  * @brief  Enable UCPD1 peripheral clocks enable during CSleep mode
  * @rmtoll UCPD1         UCPD1LPEN         LL_RCC_UCPD1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UCPD1_EnableClockSleep(void)
{
  SET_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDLPEN);
}
#endif /* RCC_UCPDCFGR_UCPDLPEN */
#if defined(RCC_BUSPERFMCFGR_BUSPERFMLPEN)
/**
  * @brief  Enable BUSPERF peripheral clocks enable during CSleep mode
  * @rmtoll BUSPERF         BUSPERFLPEN         LL_RCC_BUSPERF_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BUSPERFM_EnableClockSleep(void)
{
  SET_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMLPEN);
}
#endif /* RCC_BUSPERFMCFGR_BUSPERFMLPEN */
#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN)
/**
  * @brief  Enable USB3PCI peripheral clocks enable during CSleep mode
  * @rmtoll USB3PCI         USB3PCILPEN         LL_RCC_USB3PCI_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3PCIEPHY_EnableClockSleep(void)
{
  SET_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN);
}
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN */

/**
  * @brief  Enable LTDC peripheral clocks enable during CSleep mode
  * @rmtoll LTDC         LTDCLPEN         LL_RCC_LTDC_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LTDC_EnableClockSleep(void)
{
  SET_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCLPEN);
}

#if defined(RCC_GICV2MCFGR_GICV2MLPEN)
/**
  * @brief  Enable GICV2M peripheral clocks enable during CSleep mode
  * @rmtoll GICV2M         GICV2MLPEN         LL_RCC_GICV2M_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GICV2M_EnableClockSleep(void)
{
  SET_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MLPEN);
}
#endif /* RCC_GICV2MCFGR_GICV2MLPEN */

#if defined(RCC_UCPDCFGR_UCPDLPEN)
/**
  * @brief  Disable UCPD1 peripheral clocks during CSleep mode
  * @rmtoll UCPD1         UCPD1LPEN         LL_RCC_UCPD1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UCPD1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDLPEN);
}
#endif /* RCC_UCPDCFGR_UCPDLPEN */
#if defined(RCC_BUSPERFMCFGR_BUSPERFMLPEN)
/**
  * @brief  Disable BUSPERF peripheral clocks during CSleep mode
  * @rmtoll BUSPERF         BUSPERFLPEN         LL_RCC_BUSPERF_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BUSPERFM_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMLPEN);
}
#endif /* RCC_BUSPERFMCFGR_BUSPERFMLPEN */
#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN)
/**
  * @brief  Disable USB3PCI peripheral clocks during CSleep mode
  * @rmtoll USB3PCI         USB3PCILPEN         LL_RCC_USB3PCI_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3PCIEPHY_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN);
}
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYLPEN */

/**
  * @brief  Disable LTDC peripheral clocks during CSleep mode
  * @rmtoll LTDC         LTDCLPEN         LL_RCC_LTDC_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LTDC_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCLPEN);
}

#if defined(RCC_GICV2MCFGR_GICV2MLPEN)
/**
  * @brief  Disable GICV2M peripheral clocks during CSleep mode
  * @rmtoll GICV2M         GICV2MLPEN         LL_RCC_GICV2M_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_GICV2M_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->GICV2MCFGR, RCC_GICV2MCFGR_GICV2MLPEN);
}
#endif /* RCC_GICV2MCFGR_GICV2MLPEN */

#if defined(RCC_UCPDCFGR_UCPDRST)
/**
  * @brief  Assert UCPD1 reset
  * @rmtoll UCPD1         UCPD1RST         LL_RCC_UCPD1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UCPD1_ForceReset(void)
{
  SET_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDRST);
}
#endif /* RCC_UCPDCFGR_UCPDRST */
#if defined(RCC_BUSPERFMCFGR_BUSPERFMRST)
/**
  * @brief  Assert BUSPERF reset
  * @rmtoll BUSPERF         BUSPERFRST         LL_RCC_BUSPERF_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BUSPERFM_ForceReset(void)
{
  SET_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMRST);
}
#endif /* RCC_BUSPERFMCFGR_BUSPERFMRST */
#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST)
/**
  * @brief  Assert USB3PCI reset
  * @rmtoll USB3PCI         USB3PCIRST         LL_RCC_USB3PCI_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3PCIEPHY_ForceReset(void)
{
  SET_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST);
}
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST */

/**
  * @brief  Assert LTDC reset
  * @rmtoll LTDC         LTDCRST         LL_RCC_LTDC_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LTDC_ForceReset(void)
{
  SET_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCRST);
}

#if defined(RCC_UCPDCFGR_UCPDRST)
/**
  * @brief  Release UCPD1 reset
  * @rmtoll UCPD1         UCPD1RST         LL_RCC_UCPD1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_UCPD1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->UCPDCFGR, RCC_UCPDCFGR_UCPDRST);
}
#endif /* RCC_UCPDCFGR_UCPDRST */
#if defined(RCC_BUSPERFMCFGR_BUSPERFMRST)
/**
  * @brief  Release BUSPERF reset
  * @rmtoll BUSPERF         BUSPERFRST         LL_RCC_BUSPERF_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_BUSPERFM_ReleaseReset(void)
{
  CLEAR_BIT(RCC->BUSPERFMCFGR, RCC_BUSPERFMCFGR_BUSPERFMRST);
}
#endif /* RCC_BUSPERFMCFGR_BUSPERFMRST */
#if defined(RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST)
/**
  * @brief  Release USB3PCI reset
  * @rmtoll USB3PCI         USB3PCIRST         LL_RCC_USB3PCI_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_USB3PCIEPHY_ReleaseReset(void)
{
  CLEAR_BIT(RCC->USB3PCIEPHYCFGR, RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST);
}
#endif /* RCC_USB3PCIEPHYCFGR_USB3PCIEPHYRST */

/**
  * @brief  Release LTDC reset
  * @rmtoll LTDC         LTDCRST         LL_RCC_LTDC_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LTDC_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LTDCCFGR, RCC_LTDCCFGR_LTDCRST);
}

/**
  * @}
  */

#if defined(RCC_WWDG2CFGR_WWDG2EN)
/** @defgroup BUS_LL_EF_APBSMARTRUN APB Smartrun
  * @{
  */
/**
  * @brief  Enable WWDG2  peripheral clock
  * @rmtoll WWDG2         WWDG2EN         LL_RCC_WWDG2_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG2_EnableClock(void)
{
  SET_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2EN);
}
#endif /* RCC_WWDG2CFGR_WWDG2EN */

#if defined(RCC_I3C4CFGR_I3C4EN)
/**
  * @brief  Enable I3C4  peripheral clock
  * @rmtoll I3C4         I3C4EN         LL_RCC_I3C4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_EnableClock(void)
{
  SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4EN);
}
#endif /* RCC_I3C4CFGR_I3C4EN */

#if defined(RCC_IWDG5CFGR_IWDG5EN)
/**
  * @brief  Enable IWDG5  peripheral clock
  * @rmtoll IWDG5         IWDG5EN         LL_RCC_IWDG5_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG5_EnableClock(void)
{
  SET_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5EN);
}
#endif /* RCC_IWDG5CFGR_IWDG5EN */

/**
  * @brief  Enable LPTIM4  peripheral clock
  * @rmtoll LPTIM4         LPTIM4EN         LL_RCC_LPTIM4_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM4_EnableClock(void)
{
  SET_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4EN);
}

/**
  * @brief  Enable LPTIM5  peripheral clock
  * @rmtoll LPTIM5         LPTIM5EN         LL_RCC_LPTIM5_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM5_EnableClock(void)
{
  SET_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5EN);
}

#if defined(RCC_I2C8CFGR_I2C8EN)
/**
  * @brief  Enable I2C8  peripheral clock
  * @rmtoll I2C8         I2C8EN         LL_RCC_I2C8_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C8_EnableClock(void)
{
  SET_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8EN);
}
#endif /* RCC_I2C8CFGR_I2C8EN */
/**
  * @brief  Enable LPTIM3  peripheral clock
  * @rmtoll LPTIM3         LPTIM3EN         LL_RCC_LPTIM3_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM3_EnableClock(void)
{
  SET_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3EN);
}

#if defined(RCC_SPI8CFGR_SPI8EN)
/**
  * @brief  Enable SPI8  peripheral clock
  * @rmtoll SPI8         SPI8EN         LL_RCC_SPI8_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI8_EnableClock(void)
{
  SET_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8EN);
}
#endif /* RCC_SPI8CFGR_SPI8EN */

/**
  * @brief  Enable LPUART1  peripheral clock
  * @rmtoll LPUART1         LPUART1EN         LL_RCC_LPUART1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPUART1_EnableClock(void)
{
  SET_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1EN);
}

/**
  * @brief  Enable RTC  peripheral clock
  * @rmtoll RTC         RTCEN         LL_RCC_RTC_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RTC_EnableClock(void)
{
  SET_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCEN);
}

#if defined(RCC_WWDG2CFGR_WWDG2EN)
/**
  * @brief  Disable WWDG2  peripheral clock
  * @rmtoll WWDG2         WWDG2EN         LL_RCC_WWDG2_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG2_DisableClock(void)
{
  CLEAR_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2EN);
}
#endif /* RCC_WWDG2CFGR_WWDG2EN */

#if defined(RCC_I3C4CFGR_I3C4EN)
/**
  * @brief  Disable I3C4  peripheral clock
  * @rmtoll I3C4         I3C4EN         LL_RCC_I3C4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_DisableClock(void)
{
  CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4EN);
}
#endif /* RCC_I3C4CFGR_I3C4EN */

#if defined(RCC_I3C4CFGR_I3C4EN)
/**
  * @brief  Disable IWDG5  peripheral clock
  * @rmtoll IWDG5         IWDG5EN         LL_RCC_IWDG5_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG5_DisableClock(void)
{
  CLEAR_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5EN);
}
#endif /* RCC_IWDG5CFGR_IWDG5EN */

/**
  * @brief  Disable LPTIM4  peripheral clock
  * @rmtoll LPTIM4         LPTIM4EN         LL_RCC_LPTIM4_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM4_DisableClock(void)
{
  CLEAR_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4EN);
}

/**
  * @brief  Disable LPTIM5  peripheral clock
  * @rmtoll LPTIM5         LPTIM5EN         LL_RCC_LPTIM5_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM5_DisableClock(void)
{
  CLEAR_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5EN);
}

#if defined(RCC_I2C8CFGR_I2C8EN)
/**
  * @brief  Disable I2C8  peripheral clock
  * @rmtoll I2C8         I2C8EN         LL_RCC_I2C8_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C8_DisableClock(void)
{
  CLEAR_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8EN);
}
#endif /* RCC_I2C8CFGR_I2C8EN */

/**
  * @brief  Disable LPTIM3  peripheral clock
  * @rmtoll LPTIM3         LPTIM3EN         LL_RCC_LPTIM3_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM3_DisableClock(void)
{
  CLEAR_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3EN);
}

#if defined(RCC_SPI8CFGR_SPI8EN)
/**
  * @brief  Disable SPI8  peripheral clock
  * @rmtoll SPI8         SPI8EN         LL_RCC_SPI8_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI8_DisableClock(void)
{
  CLEAR_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8EN);
}
#endif /* RCC_SPI8CFGR_SPI8EN */

/**
  * @brief  Disable LPUART1  peripheral clock
  * @rmtoll LPUART1         LPUART1EN         LL_RCC_LPUART1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPUART1_DisableClock(void)
{
  CLEAR_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1EN);
}

/**
  * @brief  Disable RTC  peripheral clock
  * @rmtoll RTC         RTCEN         LL_RCC_RTC_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RTC_DisableClock(void)
{
  CLEAR_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCEN);
}

#if defined(RCC_WWDG2CFGR_WWDG2LPEN)
/**
  * @brief  Enable WWDG2 peripheral clocks enable during CSleep mode
  * @rmtoll WWDG2         WWDG2LPEN         LL_RCC_WWDG2_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG2_EnableClockSleep(void)
{
  SET_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2LPEN);
}
#endif /* RCC_WWDG2CFGR_WWDG2LPEN */

#if defined(RCC_I3C4CFGR_I3C4LPEN)
/**
  * @brief  Enable I3C4 peripheral clocks enable during CSleep mode
  * @rmtoll I3C4         I3C4LPEN         LL_RCC_I3C4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_EnableClockSleep(void)
{
  SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4LPEN);
}
#endif /* RCC_I3C4CFGR_I3C4LPEN */

#if defined(RCC_I3C4CFGR_I3C4AMEN)
/**
  * @brief  Enable I3C4 peripheral clocks during Autonomous mode
  * @rmtoll I3C4         I3C4AMEN         LL_RCC_I3C4_EnableClockAutonomous
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_EnableClockAutonomous(void)
{
  SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4AMEN);
}
#endif /* RCC_I3C4CFGR_I3C4AMEN */

#if defined(RCC_IWDG5CFGR_IWDG5LPEN)
/**
  * @brief  Enable IWDG5 peripheral clocks enable during CSleep mode
  * @rmtoll IWDG5         IWDG5LPEN         LL_RCC_IWDG5_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG5_EnableClockSleep(void)
{
  SET_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5LPEN);
}
#endif /* RCC_IWDG5CFGR_IWDG5LPEN */

/**
  * @brief  Enable LPTIM4 peripheral clocks enable during CSleep mode
  * @rmtoll LPTIM4         LPTIM4LPEN         LL_RCC_LPTIM4_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM4_EnableClockSleep(void)
{
  SET_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4LPEN);
}

/**
  * @brief  Enable LPTIM5 peripheral clocks enable during CSleep mode
  * @rmtoll LPTIM5         LPTIM5LPEN         LL_RCC_LPTIM5_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM5_EnableClockSleep(void)
{
  SET_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5LPEN);
}

#if defined(RCC_I2C8CFGR_I2C8LPEN)
/**
  * @brief  Enable I2C8 peripheral clocks enable during CSleep mode
  * @rmtoll I2C8         I2C8LPEN         LL_RCC_I2C8_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C8_EnableClockSleep(void)
{
  SET_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8LPEN);
}
#endif /* RCC_I2C8CFGR_I2C8LPEN */

/**
  * @brief  Enable LPTIM3 peripheral clocks enable during CSleep mode
  * @rmtoll LPTIM3         LPTIM3LPEN         LL_RCC_LPTIM3_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM3_EnableClockSleep(void)
{
  SET_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3LPEN);
}

#if defined(RCC_SPI8CFGR_SPI8LPEN)
/**
  * @brief  Enable SPI8 peripheral clocks enable during CSleep mode
  * @rmtoll SPI8         SPI8LPEN         LL_RCC_SPI8_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI8_EnableClockSleep(void)
{
  SET_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8LPEN);
}
#endif /* RCC_SPI8CFGR_SPI8LPEN */

/**
  * @brief  Enable LPUART1 peripheral clocks enable during CSleep mode
  * @rmtoll LPUART1         LPUART1LPEN         LL_RCC_LPUART1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPUART1_EnableClockSleep(void)
{
  SET_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1LPEN);
}

/**
  * @brief  Enable RTC peripheral clocks enable during CSleep mode
  * @rmtoll RTC         RTCLPEN         LL_RCC_RTC_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RTC_EnableClockSleep(void)
{
  SET_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCLPEN);
}

#if defined(RCC_WWDG2CFGR_WWDG2LPEN)
/**
  * @brief  Disable WWDG2 peripheral clocks during CSleep mode
  * @rmtoll WWDG2         WWDG2LPEN         LL_RCC_WWDG2_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG2_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2LPEN);
}
#endif /* RCC_WWDG2CFGR_WWDG2LPEN */

#if defined(RCC_I3C4CFGR_I3C4LPEN)
/**
  * @brief  Disable I3C4 peripheral clocks during CSleep mode
  * @rmtoll I3C4         I3C4LPEN         LL_RCC_I3C4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4LPEN);
}
#endif /* RCC_I3C4CFGR_I3C4LPEN */

#if defined(RCC_I3C4CFGR_I3C4AMEN)
/**
  * @brief  Disable I3C4 peripheral clocks during Autonomous mode
  * @rmtoll I3C4         I3C4AMEN         LL_RCC_I3C4_EnableClockAutonomous
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_DisableClockAutonomous(void)
{
  CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4AMEN);
}
#endif /* RCC_I3C4CFGR_I3C4AMEN */

#if defined(RCC_IWDG5CFGR_IWDG5LPEN)
/**
  * @brief  Disable IWDG5 peripheral clocks during CSleep mode
  * @rmtoll IWDG5         IWDG5LPEN         LL_RCC_IWDG5_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IWDG5_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IWDG5CFGR, RCC_IWDG5CFGR_IWDG5LPEN);
}
#endif /* RCC_IWDG5CFGR_IWDG5LPEN */

/**
  * @brief  Disable LPTIM4 peripheral clocks during CSleep mode
  * @rmtoll LPTIM4         LPTIM4LPEN         LL_RCC_LPTIM4_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM4_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4LPEN);
}

/**
  * @brief  Disable LPTIM5 peripheral clocks during CSleep mode
  * @rmtoll LPTIM5         LPTIM5LPEN         LL_RCC_LPTIM5_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM5_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5LPEN);
}

#if defined(RCC_I2C8CFGR_I2C8LPEN)
/**
  * @brief  Disable I2C8 peripheral clocks during CSleep mode
  * @rmtoll I2C8         I2C8LPEN         LL_RCC_I2C8_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C8_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8LPEN);
}
#endif /* RCC_I2C8CFGR_I2C8LPEN */

/**
  * @brief  Disable LPTIM3 peripheral clocks during CSleep mode
  * @rmtoll LPTIM3         LPTIM3LPEN         LL_RCC_LPTIM3_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM3_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3LPEN);
}

#if defined(RCC_SPI8CFGR_SPI8LPEN)
/**
  * @brief  Disable SPI8 peripheral clocks during CSleep mode
  * @rmtoll SPI8         SPI8LPEN         LL_RCC_SPI8_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI8_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8LPEN);
}
#endif /* RCC_SPI8CFGR_SPI8LPEN */

/**
  * @brief  Disable LPUART1 peripheral clocks during CSleep mode
  * @rmtoll LPUART1         LPUART1LPEN         LL_RCC_LPUART1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPUART1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1LPEN);
}

/**
  * @brief  Disable RTC peripheral clocks during CSleep mode
  * @rmtoll RTC         RTCLPEN         LL_RCC_RTC_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_RTC_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->RTCCFGR, RCC_RTCCFGR_RTCLPEN);
}

#if defined(RCC_WWDG2CFGR_WWDG2RST)
/**
  * @brief  Assert WWDG2 reset
  * @rmtoll WWDG2         WWDG2RST         LL_RCC_WWDG2_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG2_ForceReset(void)
{
  SET_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2RST);
}
#endif /* RCC_WWDG2CFGR_WWDG2RST */

#if defined(RCC_I3C4CFGR_I3C4RST)
/**
  * @brief  Assert I3C4 reset
  * @rmtoll I3C4         I3C4RST         LL_RCC_I3C4_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_ForceReset(void)
{
  SET_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4RST);
}
#endif /* RCC_I3C4CFGR_I3C4RST */

/**
  * @brief  Assert LPTIM4 reset
  * @rmtoll LPTIM4         LPTIM4RST         LL_RCC_LPTIM4_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM4_ForceReset(void)
{
  SET_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4RST);
}

/**
  * @brief  Assert LPTIM5 reset
  * @rmtoll LPTIM5         LPTIM5RST         LL_RCC_LPTIM5_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM5_ForceReset(void)
{
  SET_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5RST);
}

#if defined(RCC_I2C8CFGR_I2C8RST)
/**
  * @brief  Assert I2C8 reset
  * @rmtoll I2C8         I2C8RST         LL_RCC_I2C8_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C8_ForceReset(void)
{
  SET_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8RST);
}
#endif /* RCC_I2C8CFGR_I2C8RST */

/**
  * @brief  Assert LPTIM3 reset
  * @rmtoll LPTIM3         LPTIM3RST         LL_RCC_LPTIM3_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM3_ForceReset(void)
{
  SET_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3RST);
}

#if defined(RCC_SPI8CFGR_SPI8RST)
/**
  * @brief  Assert SPI8 reset
  * @rmtoll SPI8         SPI8RST         LL_RCC_SPI8_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI8_ForceReset(void)
{
  SET_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8RST);
}
#endif /* RCC_SPI8CFGR_SPI8RST */

/**
  * @brief  Assert LPUART1 reset
  * @rmtoll LPUART1         LPUART1RST         LL_RCC_LPUART1_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPUART1_ForceReset(void)
{
  SET_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1RST);
}

#if defined(RCC_WWDG2CFGR_WWDG2LPEN)
/**
  * @brief  Release WWDG2 reset
  * @rmtoll WWDG2         WWDG2RST         LL_RCC_WWDG2_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_WWDG2_ReleaseReset(void)
{
  CLEAR_BIT(RCC->WWDG2CFGR, RCC_WWDG2CFGR_WWDG2RST);
}
#endif /* RCC_WWDG2CFGR_WWDG2LPEN */

#if defined(RCC_I3C4CFGR_I3C4RST)
/**
  * @brief  Release I3C4 reset
  * @rmtoll I3C4         I3C4RST         LL_RCC_I3C4_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I3C4_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I3C4CFGR, RCC_I3C4CFGR_I3C4RST);
}
#endif /* RCC_I3C4CFGR_I3C4RST */

/**
  * @brief  Release LPTIM4 reset
  * @rmtoll LPTIM4         LPTIM4RST         LL_RCC_LPTIM4_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM4_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LPTIM4CFGR, RCC_LPTIM4CFGR_LPTIM4RST);
}

/**
  * @brief  Release LPTIM5 reset
  * @rmtoll LPTIM5         LPTIM5RST         LL_RCC_LPTIM5_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM5_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LPTIM5CFGR, RCC_LPTIM5CFGR_LPTIM5RST);
}

#if defined(RCC_I2C8CFGR_I2C8RST)
/**
  * @brief  Release I2C8 reset
  * @rmtoll I2C8         I2C8RST         LL_RCC_I2C8_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_I2C8_ReleaseReset(void)
{
  CLEAR_BIT(RCC->I2C8CFGR, RCC_I2C8CFGR_I2C8RST);
}
#endif /* RCC_I2C8CFGR_I2C8RST*/

/**
  * @brief  Release LPTIM3 reset
  * @rmtoll LPTIM3         LPTIM3RST         LL_RCC_LPTIM3_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPTIM3_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LPTIM3CFGR, RCC_LPTIM3CFGR_LPTIM3RST);
}

#if defined(RCC_SPI8CFGR_SPI8RST)
/**
  * @brief  Release SPI8 reset
  * @rmtoll SPI8         SPI8RST         LL_RCC_SPI8_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SPI8_ReleaseReset(void)
{
  CLEAR_BIT(RCC->SPI8CFGR, RCC_SPI8CFGR_SPI8RST);
}
#endif /* RCC_SPI8CFGR_SPI8RST */

/**
  * @brief  Release LPUART1 reset
  * @rmtoll LPUART1         LPUART1RST         LL_RCC_LPUART1_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LPUART1_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LPUART1CFGR, RCC_LPUART1CFGR_LPUART1RST);
}

/**
  * @}
  */

/** @defgroup BUS_LL_EF_OTHERS Others
  * @{
  */
/**
  * @brief  Enable ETR  peripheral clock
  * @rmtoll ETR         ETREN         LL_RCC_ETR_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETR_EnableClock(void)
{
  SET_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETREN);
}

/**
  * @brief  Enable SYSCPU1  peripheral clock
  * @rmtoll SYSCPU1         SYSCPU1EN         LL_RCC_SYSCPU1_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSCPU1_EnableClock(void)
{
  SET_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1EN);
}
#if defined(RCC_IS2MCFGR_IS2MEN)
/**
  * @brief  Enable IS2M  peripheral clock
  * @rmtoll IS2M         IS2MEN         LL_RCC_IS2M_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IS2M_EnableClock(void)
{
  SET_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MEN);
}
#endif /* RCC_IS2MCFGR_IS2MEN */
#if defined(RCC_LVDSCFGR_LVDSEN)
/**
  * @brief  Enable LVDS  peripheral clock
  * @rmtoll LVDS         LVDSEN         LL_RCC_LVDS_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LVDS_EnableClock(void)
{
  SET_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSEN);
}
#endif /* RCC_LVDSCFGR_LVDSEN */
#if defined(RCC_CCICFGR_CCIEN)
/**
  * @brief  Enable CCI  peripheral clock
  * @rmtoll CCI         CCIEN         LL_RCC_CCI_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CCI_EnableClock(void)
{
  SET_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIEN);
}
#endif /* RCC_CCICFGR_CCIEN */

#if defined(RCC_TMPSENSCFGR_TMPSENSEN)
/**
  * @brief  Enable TMPSENS  peripheral clock
  * @rmtoll TMPSENS         TMPSENSEN         LL_RCC_TMPSENS_EnableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TMPSENS_EnableClock(void)
{
  SET_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSEN);
}
#endif /* RCC_TMPSENSCFGR_TMPSENSEN */

/**
  * @brief  Disable ETR  peripheral clock
  * @rmtoll ETR         ETREN         LL_RCC_ETR_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETR_DisableClock(void)
{
  CLEAR_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETREN);
}

/**
  * @brief  Disable SYSCPU1  peripheral clock
  * @rmtoll SYSCPU1         SYSCPU1EN         LL_RCC_SYSCPU1_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSCPU1_DisableClock(void)
{
  CLEAR_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1EN);
}
#if defined(RCC_IS2MCFGR_IS2MEN)
/**
  * @brief  Disable IS2M  peripheral clock
  * @rmtoll IS2M         IS2MEN         LL_RCC_IS2M_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IS2M_DisableClock(void)
{
  CLEAR_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MEN);
}
#endif /* RCC_IS2MCFGR_IS2MEN */

#if defined(RCC_LVDSCFGR_LVDSEN)
/**
  * @brief  Disable LVDS  peripheral clock
  * @rmtoll LVDS         LVDSEN         LL_RCC_LVDS_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LVDS_DisableClock(void)
{
  CLEAR_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSEN);
}
#endif /* RCC_LVDSCFGR_LVDSEN */
#if defined(RCC_CCICFGR_CCIEN)
/**
  * @brief  Disable CCI  peripheral clock
  * @rmtoll CCI         CCIEN         LL_RCC_CCI_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CCI_DisableClock(void)
{
  CLEAR_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIEN);
}
#endif /* RCC_CCICFGR_CCIEN */

#if defined(RCC_TMPSENSCFGR_TMPSENSEN)
/**
  * @brief  Disable TMPSENS  peripheral clock
  * @rmtoll TMPSENS         TMPSENSEN         LL_RCC_TMPSENS_DisableClock
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TMPSENS_DisableClock(void)
{
  CLEAR_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSEN);
}
#endif /* RCC_TMPSENSCFGR_TMPSENSEN */

/**
  * @brief  Enable ETR peripheral clocks enable during CSleep mode
  * @rmtoll ETR         ETRLPEN         LL_RCC_ETR_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETR_EnableClockSleep(void)
{
  SET_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETRLPEN);
}

/**
  * @brief  Enable SYSCPU1 peripheral clocks enable during CSleep mode
  * @rmtoll SYSCPU1         SYSCPU1LPEN         LL_RCC_SYSCPU1_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSCPU1_EnableClockSleep(void)
{
  SET_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1LPEN);
}
#if defined(RCC_IS2MCFGR_IS2MLPEN)
/**
  * @brief  Enable IS2M peripheral clocks enable during CSleep mode
  * @rmtoll IS2M         IS2MLPEN         LL_RCC_IS2M_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IS2M_EnableClockSleep(void)
{
  SET_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MLPEN);
}
#endif /* RCC_IS2MCFGR_IS2MLPEN */

#if defined(RCC_LVDSCFGR_LVDSLPEN)
/**
  * @brief  Enable LVDS peripheral clocks enable during CSleep mode
  * @rmtoll LVDS         LVDSLPEN         LL_RCC_LVDS_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LVDS_EnableClockSleep(void)
{
  SET_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSLPEN);
}
#endif /* RCC_LVDSCFGR_LVDSLPEN */
#if defined(RCC_CCICFGR_CCILPEN)
/**
  * @brief  Enable CCI peripheral clock during CSleep mode
  * @rmtoll CCI         CCILPEN         LL_RCC_CCI_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CCI_EnableClockSleep(void)
{
  SET_BIT(RCC->CCICFGR, RCC_CCICFGR_CCILPEN);
}
#endif /* RCC_CCICFGR_CCILPEN */

#if defined(RCC_TMPSENSCFGR_TMPSENSLPEN)
/**
  * @brief  Enable TMPSENS peripheral clocks enable during CSleep mode
  * @rmtoll TMPSENS         TMPSENSLPEN         LL_RCC_TMPSENS_EnableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TMPSENS_EnableClockSleep(void)
{
  SET_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSLPEN);
}
#endif /* RCC_TMPSENSCFGR_TMPSENSLPEN */

/**
  * @brief  Disable ETR peripheral clocks during CSleep mode
  * @rmtoll ETR         ETRLPEN         LL_RCC_ETR_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_ETR_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->ETRCFGR, RCC_ETRCFGR_ETRLPEN);
}

/**
  * @brief  Disable SYSCPU1 peripheral clocks during CSleep mode
  * @rmtoll SYSCPU1         SYSCPU1LPEN         LL_RCC_SYSCPU1_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_SYSCPU1_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->SYSCPU1CFGR, RCC_SYSCPU1CFGR_SYSCPU1LPEN);
}
#if defined(RCC_IS2MCFGR_IS2MLPEN)
/**
  * @brief  Disable IS2M peripheral clocks during CSleep mode
  * @rmtoll IS2M         IS2MLPEN         LL_RCC_IS2M_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IS2M_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MLPEN);
}
#endif /* RCC_IS2MCFGR_IS2MLPEN */
#if defined(RCC_LVDSCFGR_LVDSLPEN)
/**
  * @brief  Disable LVDS peripheral clocks during CSleep mode
  * @rmtoll LVDS         LVDSLPEN         LL_RCC_LVDS_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LVDS_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSLPEN);
}
#endif /* RCC_LVDSCFGR_LVDSLPEN */
#if defined(RCC_CCICFGR_CCILPEN)
/**
  * @brief  Disable CCI peripheral clocks during CSleep mode
  * @rmtoll CCI         CCILPEN         LL_RCC_CCI_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CCI_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->CCICFGR, RCC_CCICFGR_CCILPEN);
}
#endif /* RCC_CCICFGR_CCILPEN */

#if defined(RCC_TMPSENSCFGR_TMPSENSLPEN)
/**
  * @brief  Disable TMPSENS peripheral clocks during CSleep mode
  * @rmtoll TMPSENS         TMPSENSLPEN         LL_RCC_TMPSENS_DisableClockSleep
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TMPSENS_DisableClockSleep(void)
{
  CLEAR_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSLPEN);
}
#endif /* RCC_TMPSENSCFGR_TMPSENSLPEN */
#if defined(RCC_IS2MCFGR_IS2MRST)
/**
  * @brief  Assert IS2M reset
  * @rmtoll IS2M         IS2MRST         LL_RCC_IS2M_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IS2M_ForceReset(void)
{
  SET_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MRST);
}
#endif /* RCC_IS2MCFGR_IS2MRST */
#if defined(RCC_LVDSCFGR_LVDSRST)
/**
  * @brief  Assert LVDS reset
  * @rmtoll LVDS         LVDSRST         LL_RCC_LVDS_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LVDS_ForceReset(void)
{
  SET_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSRST);
}
#endif /* RCC_LVDSCFGR_LVDSRST */
#if defined(RCC_CCICFGR_CCIRST)
/**
  * @brief  Assert CCI reset
  * @rmtoll CCI         CCIRST         LL_RCC_CCI_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CCI_ForceReset(void)
{
  SET_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIRST);
}
#endif /* RCC_CCICFGR_CCIRST */

#if defined(RCC_TMPSENSCFGR_TMPSENSRST)
/**
  * @brief  Assert TMPSENS reset
  * @rmtoll TMPSENS         TMPSENSRST         LL_RCC_TMPSENS_ForceReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TMPSENS_ForceReset(void)
{
  SET_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSRST);
}
#endif /* RCC_TMPSENSCFGR_TMPSENSRST */
#if defined(RCC_IS2MCFGR_IS2MRST)
/**
  * @brief  Release IS2M reset
  * @rmtoll IS2M         IS2MRST         LL_RCC_IS2M_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_IS2M_ReleaseReset(void)
{
  CLEAR_BIT(RCC->IS2MCFGR, RCC_IS2MCFGR_IS2MRST);
}
#endif /* RCC_IS2MCFGR_IS2MRST */
#if defined(RCC_LVDSCFGR_LVDSRST)
/**
  * @brief  Release LVDS reset
  * @rmtoll LVDS         LVDSRST         LL_RCC_LVDS_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_LVDS_ReleaseReset(void)
{
  CLEAR_BIT(RCC->LVDSCFGR, RCC_LVDSCFGR_LVDSRST);
}
#endif /* RCC_LVDSCFGR_LVDSRST */
#if defined(RCC_CCICFGR_CCIRST)
/**
  * @brief  Release CCI reset
  * @rmtoll CCI         CCIRST         LL_RCC_CCI_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_CCI_ReleaseReset(void)
{
  CLEAR_BIT(RCC->CCICFGR, RCC_CCICFGR_CCIRST);
}
#endif /* RCC_CCICFGR_CCIRST */

#if defined(RCC_TMPSENSCFGR_TMPSENSRST)
/**
  * @brief  Release TMPSENS reset
  * @rmtoll TMPSENS         TMPSENSRST         LL_RCC_TMPSENS_ReleaseReset
  * @retval None
  */
__STATIC_INLINE void LL_RCC_TMPSENS_ReleaseReset(void)
{
  CLEAR_BIT(RCC->TMPSENSCFGR, RCC_TMPSENSCFGR_TMPSENSRST);
}
#endif /* RCC_TMPSENSCFGR_TMPSENSRST */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* RCC */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32MP2xx_LL_BUS_H */
