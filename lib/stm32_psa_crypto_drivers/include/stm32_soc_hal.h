/**
 ******************************************************************************
 * @file    stm32_soc_hal.h
 * @brief   SoC generic HAL header file inclusion for all STM32 HAL drivers
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
#ifndef STM32_PSA_CRYPTO_DRIVERS_STM32_SOC_HAL_H
#define STM32_PSA_CRYPTO_DRIVERS_STM32_SOC_HAL_H

/* Includes ------------------------------------------------------------------*/

/*
 * The project is expected to define STM32<product>xx (including some legacy
 * defines we rely on here to include the needed HAL SoC series main header file.
 */

#if /* C0 */ \
    defined(STM32C011xx) || defined(STM32C031xx) || defined(STM32C051xx) || \
    defined(STM32C071xx) || defined(STM32C091xx) || defined(STM32C092xx)
#include "stm32c0xx_hal.h"

#elif /* C5 */ \
      defined(STM32C531xx) || defined(STM32C532xx) || defined(STM32C542xx) || \
      defined(STM32C551xx) || defined(STM32C552xx) || defined(STM32C562xx) || \
      defined(STM32C591xx) || defined(STM32C593xx) || defined(STM32C5A3xx)
#include "stm32_hal.h"

#elif /* F0 */ \
      defined(STM32F030x6) || defined(STM32F030x8) || \
      defined(STM32F031x6) || defined(STM32F038xx) || \
      defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F070x6) || \
      defined(STM32F051x8) || defined(STM32F058xx) || \
      defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
      defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC) || \
      /* Legacy */ \
      defined(STM32F030x4) || defined(STM32F072x8)
#include "stm32f0xx.h"

#elif /* F1 */ \
      defined(STM32F100xB) || defined(STM32F100xE) || defined(STM32F101x6) || \
      defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6) || \
      defined(STM32F103xB) || defined(STM32F103xE) || defined(STM32F103xG) || defined(STM32F105xC) || defined(STM32F107xC) || \
      /* Legacy */ \
      defined(STM32F103x8) || defined(STM32F105xB)
#include "stm32f1xx.h"

#elif /* F2 */ \
      defined(STM32F205xx) || defined(STM32F215xx) || defined(STM32F207xx) || defined(STM32F217xx)
#include "stm32f2xx.h"

#elif /* F3 */ \
      defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
      defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
      defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
      defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
      defined(STM32F373xC) || defined(STM32F378xx)
#include "stm32f3xx.h"

#elif /* F4 */ \
      defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
      defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
      defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
      defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || \
      defined(STM32F479xx) || defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || \
      defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#include "stm32f4xx.h"

#elif /* F7 */ \
      defined(STM32F756xx) || defined(STM32F746xx) || defined(STM32F745xx) || defined(STM32F765xx) || \
      defined(STM32F767xx) || defined(STM32F769xx) || defined(STM32F777xx) || defined(STM32F779xx) || \
      defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F732xx) || defined(STM32F733xx) || \
      defined(STM32F730xx) || defined(STM32F750xx)
#include "stm32f7xx.h"

#elif /* G0 */ \
      defined(STM32G071xx) || defined(STM32G081xx) || defined(STM32G070xx) || \
      defined(STM32G030xx) || defined(STM32G031xx) || defined(STM32G041xx) || \
      defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx) || \
      defined(STM32G050xx) || defined(STM32G051xx) || defined(STM32G061xx)
#include "stm32g0xx.h"

#elif /* G4 */ \
      defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx) || \
      defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G484xx) || \
      defined(STM32GBK1CB) || defined(STM32G491xx) || defined(STM32G4A1xx) || \
      defined(STM32G411xB) || defined(STM32G411xC) || defined(STM32G414xx)
#include "stm32g4xx.h"

#elif /* H5 */ \
      defined(STM32H5F5xx) || defined(STM32H5F4xx) || \
      defined(STM32H5F4xx) || defined(STM32H5E4xx) || \
      defined(STM32H573xx) || defined(STM32H563xx) || \
      defined(STM32H562xx) || defined(STM32H503xx) || \
      defined(STM32H533xx) || defined(STM32H523xx)
#include "stm32h5xx.h"

#elif /* H7 */ \
      defined(STM32H743xx) || defined(STM32H753xx)  || defined(STM32H750xx) || defined(STM32H742xx) || \
      defined(STM32H745xx) || defined(STM32H745xG)  || defined(STM32H755xx)  || defined(STM32H747xx) || defined(STM32H747xG)|| defined(STM32H757xx) || \
      defined(STM32H7A3xx) || defined(STM32H7A3xxQ) || defined(STM32H7B3xx) || defined(STM32H7B3xxQ) || defined(STM32H7B0xx)  || defined(STM32H7B0xxQ) || \
      defined(STM32H735xx) || defined(STM32H733xx)  || defined(STM32H730xx) || defined(STM32H730xxQ)  || defined(STM32H725xx) || defined(STM32H723xx)
#include "stm32h7xx.h"

#elif /* H7R/S */ \
      defined(STM32H7R7xx) || defined(STM32H7R3xx) || defined(STM32H7S3xx) || defined(STM32H7S7xx)
#include "stm32h7rsxx.h"

#elif /* L0 */ \
      defined(STM32L010x4) || defined(STM32L010x6) || defined(STM32L010x8) || defined(STM32L010xB) || \
      defined(STM32L011xx) || defined(STM32L021xx) || \
      defined(STM32L031xx) || defined(STM32L041xx) || \
      defined(STM32L051xx) || defined(STM32L052xx) || defined(STM32L053xx) || \
      defined(STM32L062xx) || defined(STM32L063xx) || \
      defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || \
      defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)
#include "stm32l0xx.h"

#elif /* L1 */ \
      defined(STM32L100xB) || defined(STM32L100xBA) || defined(STM32L100xC) || \
      defined(STM32L151xB) || defined(STM32L151xBA) || defined(STM32L151xC) || defined(STM32L151xCA) || defined(STM32L151xD) || defined(STM32L151xDX) || defined(STM32L151xE) || \
      defined(STM32L152xB) || defined(STM32L152xBA) || defined(STM32L152xC) || defined(STM32L152xCA) || defined(STM32L152xD) || defined(STM32L152xDX) || defined(STM32L152xE) || \
      defined(STM32L162xC) || defined(STM32L162xCA) || defined(STM32L162xD) || defined(STM32L162xDX) || defined(STM32L162xE)
#include "stm32l1xx.h"

#elif /* L4 */ \
      defined(STM32L412xx) || defined(STM32L422xx) || \
      defined(STM32L431xx) || defined(STM32L432xx) || defined(STM32L433xx) || defined(STM32L442xx) || defined(STM32L443xx) || \
      defined(STM32L451xx) || defined(STM32L452xx) || defined(STM32L462xx) || \
      defined(STM32L471xx) || defined(STM32L475xx) || defined(STM32L476xx) || defined(STM32L485xx) || defined(STM32L486xx) || \
      defined(STM32L496xx) || defined(STM32L4A6xx) || \
      defined(STM32L4P5xx) || defined(STM32L4Q5xx) || \
      defined(STM32L4R5xx) || defined(STM32L4R7xx) || defined(STM32L4R9xx) || defined(STM32L4S5xx) || defined(STM32L4S7xx) || defined(STM32L4S9xx)
#include "stm32l4xx.h"

#elif /* L5 */ \
      defined(STM32L552xx) || defined(STM32L562xx)
#include "stm32l5xx.h"

#elif /* MP1 */ \
      defined(STM32MP15xx)  /* keep for backward compatibility STM32MP15xx = STM32MP157Cxx */ || \
      defined(STM32MP157Axx) || defined(STM32MP157Cxx) || defined(STM32MP157Dxx) || defined(STM32MP157Fxx) || \
      defined(STM32MP153Axx) || defined(STM32MP153Cxx) || defined(STM32MP153Dxx) || defined(STM32MP153Fxx) || \
      defined(STM32MP151Axx) || defined(STM32MP151Cxx) || defined(STM32MP151Dxx) || defined(STM32MP151Fxx)
#include "stm32mp1xx.h"

#elif /* MP13 */ \
      defined(STM32MP13xx)  /* keep for backward compatibility STM32MP13xx = STM32MP135Cxx */ || \
      defined(STM32MP135Axx) || defined(STM32MP135Cxx) || defined(STM32MP135Dxx) || defined(STM32MP135Fxx) || \
      defined(STM32MP133Axx) || defined(STM32MP133Cxx) || defined(STM32MP133Dxx) || defined(STM32MP133Fxx) || \
      defined(STM32MP131Axx) || defined(STM32MP131Cxx) || defined(STM32MP131Dxx) || defined(STM32MP131Fxx)
#include "stm32mp13xx.h"

#elif /* MP25 */ \
      defined(STM32MP257Fxx) || defined(STM32MP257Dxx) || defined(STM32MP257Cxx) || defined(STM32MP257Axx) || \
      defined(STM32MP255Fxx) || defined(STM32MP255Dxx) || defined(STM32MP255Cxx) || defined(STM32MP255Axx) || \
      defined(STM32MP253Fxx) || defined(STM32MP253Dxx) || defined(STM32MP253Cxx) || defined(STM32MP253Axx) || \
      defined(STM32MP251Fxx) || defined(STM32MP251Dxx) || defined(STM32MP251Cxx) || defined(STM32MP251Axx) || \
      /* MP21 */ \
      defined(STM32MP215Fxx) || defined(STM32MP215Dxx) || defined(STM32MP215Cxx) || defined(STM32MP215Axx) || \
      defined(STM32MP213Fxx) || defined(STM32MP213Dxx) || defined(STM32MP213Cxx) || defined(STM32MP213Axx) || \
      defined(STM32MP211Fxx) || defined(STM32MP211Dxx) || defined(STM32MP211Cxx) || defined(STM32MP211Axx) || \
      /* MP21 */ \
      defined(STM32MP235Fxx) || defined(STM32MP235Dxx) || defined(STM32MP235Cxx) || defined(STM32MP235Axx) || \
      defined(STM32MP233Fxx) || defined(STM32MP233Dxx) || defined(STM32MP233Cxx) || defined(STM32MP233Axx) || \
      defined(STM32MP231Fxx) || defined(STM32MP231Dxx) || defined(STM32MP231Cxx) || defined(STM32MP231Axx)
#include "stm32mp2xx.h"

#elif /* N6 */ \
      defined(STM32N647xx) || defined(STM32N657xx) || defined(STM32N645xx) || defined(STM32N655xx)
#include "stm32n6xx.h"

#elif /* U0 */ \
      defined(STM32U073xx) || defined(STM32U083xx) || defined(STM32U031xx)
#include "stm32u0xx.h"

#elif /* U3 */ \
      defined(STM32U375xx) || defined(STM32U385xx) || defined(STM32U3B5xx)  || defined(STM32U3C5xx)
#include "stm32u3xx.h"

#elif /* U5 */ \
      defined(STM32U575xx) || defined(STM32U585xx) || \
      defined(STM32U595xx) || defined(STM32U599xx) || \
      defined(STM32U5A5xx) || defined(STM32U5A9xx) || \
      defined(STM32U5F7xx) || defined(STM32U5G7xx) || \
      defined(STM32U5F9xx) || defined(STM32U5G9xx) || \
      defined(STM32U535xx) || defined(STM32U545xx)
#include "stm32u5xx.h"

#elif /* WB */ \
      defined(STM32WB55xx) || defined(STM32WB5Mxx) || defined(STM32WB50xx) || \
      defined(STM32WB35xx) || defined(STM32WB30xx) || \
      defined(STM32WB15xx) || defined(STM32WB10xx) || defined(STM32WB1Mxx)
#include "stm32wbxx.h"

#elif /* WB0 */ \
      defined(STM32WB05xx) || defined(STM32WB05) || \
      defined(STM32WB06xx) || defined(STM32WB06) || \
      defined(STM32WB07xx) || defined(STM32WB07) || \
      defined(STM32WB09xx) || defined(STM32WB09)
#include "stm32wb0x.h"

#elif /* WBA */ \
      defined(STM32WBA20xx) || defined(STM32WBA23xx) || defined(STM32WBA25xx) || \
      defined(STM32WBA50xx) || defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) || \
      defined(STM32WBA5Mxx) || defined(STM32WBA62xx) || defined(STM32WBA63xx) || defined(STM32WBA64xx) || \
      defined(STM32WBA65xx) || defined(STM32WBA6Mxx)
#include "stm32wbaxx.h"

#elif /* WL */ \
      defined(STM32WL55xx) || defined(STM32WL54xx) || \
      defined(STM32WLE5xx) || defined(STM32WLE4xx) || defined(STM32WL5Mxx)
#include "stm32wlxx.h"

#elif /* WL3 */ \
      defined(STM32WL33) || defined(STM32WL3XX) || \
      defined(STM32WL3R) || defined(STM32WL3RX)
#include "stm32wl3x.h"

#else
#error "Target STM32 SoC not supported or not defined"
#endif

#endif /* STM32_PSA_CRYPTO_DRIVERS_STM32_SOC_HAL_H */

