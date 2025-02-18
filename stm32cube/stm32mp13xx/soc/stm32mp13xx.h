/**
  ******************************************************************************
  * @file    stm32mp13xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32MP13xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32MP13xx device used in the target application
  *              - To use or not the peripheral�s drivers in application code(i.e.
  *                code will be based on direct access to peripheral�s registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32mp1xx
  * @{
  */

#ifndef __STM32MP13xx_H
#define __STM32MP13xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/* Uncomment the line below according to the target STM32MP1 device used in your
   application
  */

#if !defined (STM32MP13)
#define STM32MP13
#endif /* STM32MP13 */

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number
  */
#define __STM32MP13xx_CMSIS_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32MP13xx_CMSIS_VERSION_SUB1   (0x01U) /*!< [23:16] sub1 version */
#define __STM32MP13xx_CMSIS_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32MP13xx_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32MP13xx_CMSIS_VERSION        ((__CMSIS_DEVICE_VERSION_MAIN     << 24)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB1 << 16)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB2 << 8 )\
                                      |(__CMSIS_DEVICE_HAL_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */
#if defined(CORE_CA7)
#if defined(STM32MP13xx)  /* keep for backward compatibility STM32MP13xx = STM32MP135Cxx */
  #include "stm32mp135cxx_ca7.h"
#elif defined(STM32MP135Axx)
  #include "stm32mp135axx_ca7.h"
#elif defined(STM32MP135Cxx)
  #include "stm32mp135cxx_ca7.h"
#elif defined(STM32MP135Dxx)
  #include "stm32mp135dxx_ca7.h"
#elif defined(STM32MP135Fxx)
  #include "stm32mp135fxx_ca7.h"
#elif defined(STM32MP133Axx)
  #include "stm32mp133axx_ca7.h"
#elif defined(STM32MP133Cxx)
  #include "stm32mp133cxx_ca7.h"
#elif defined(STM32MP133Dxx)
  #include "stm32mp133dxx_ca7.h"
#elif defined(STM32MP133Fxx)
  #include "stm32mp133fxx_ca7.h"
#elif defined(STM32MP131Axx)
  #include "stm32mp131axx_ca7.h"
#elif defined(STM32MP131Cxx)
  #include "stm32mp131cxx_ca7.h"
#elif defined(STM32MP131Dxx)
  #include "stm32mp131dxx_ca7.h"
#elif defined(STM32MP131Fxx)
  #include "stm32mp131fxx_ca7.h"
#else
 #error "Please select first the target STM32MP13xx device used in your application (in stm32mp1xx.h file)"
#endif
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  ERROR = 0,
  SUCCESS = !ERROR
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))


/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32mp13xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32MP13xx_H */
/**
  * @}
  */

/**
  * @}
  */