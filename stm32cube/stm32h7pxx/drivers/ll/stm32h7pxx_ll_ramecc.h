/**
  **********************************************************************************************************************
  * @file   stm32h7pxx_ll_ramecc.h
  * @brief  Header file of RAMECC LL module.
  **********************************************************************************************************************
    * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */
/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_LL_RAMECC_H
#define STM32H7PXX_LL_RAMECC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

/** @addtogroup RAMECC_LL RAMECC
  * @{
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_LL_Exported_Constants RAMECC LL RAMECC Constants
  * @{
  */

/** @defgroup RAMECC_FLAG RAMECC Monitor Flags
  * @{
  */
#define LL_RAMECC_FLAG_SE       RAMECC_SR_SEDCF         /*!< RAMECC single error detected and corrected flag */
#define LL_RAMECC_FLAG_DE       RAMECC_SR_DEDF          /*!< RAMECC double error detected flag               */
#define LL_RAMECC_FLAG_DEBW     RAMECC_SR_DEBWDF        /*!< RAMECC double error on byte write detected flag */
#define LL_RAMECC_FLAG_ALL      (LL_RAMECC_FLAG_SE \
                                 | LL_RAMECC_FLAG_DE \
                                 | LL_RAMECC_FLAG_DEBW) /*!< RAMECC all ECC error flags */
/**
  * @}
  */

/** @defgroup RAMECC_Global_Interrupt RAMECC Global Interrupts
  * @{
  */
#define  LL_RAMECC_GLOBAL_IT_SE   RAMECC_IER_GECCSEIE     /*!< RAMECC global single error interrupt               */
#define  LL_RAMECC_GLOBAL_IT_DE   RAMECC_IER_GECCDEIE     /*!< RAMECC global double error interrupt               */
#define  LL_RAMECC_GLOBAL_IT_DEBW RAMECC_IER_GECCDEBWIE   /*!< RAMECC global double error on byte write interrupt */
#define  LL_RAMECC_GLOBAL_IT_ALL  RAMECC_IER_GIE          /*!< RAMECC global all RAMECC interrupts                */
/**
  * @}
  */

/** @defgroup RAMECC_Monitor_Interrupt RAMECC Monitor Interrupts
  * @{
  */
#define LL_RAMECC_MONITOR_IT_SE   RAMECC_CR_ECCSEIE     /*!< RAMECC single error interrupt               */
#define LL_RAMECC_MONITOR_IT_DE   RAMECC_CR_ECCDEIE     /*!< RAMECC double error interrupt               */
#define LL_RAMECC_MONITOR_IT_DEBW RAMECC_CR_ECCDEBWIE   /*!< RAMECC double error on byte write interrupt */
#define LL_RAMECC_MONITOR_IT_ALL  (LL_RAMECC_MONITOR_IT_SE \
                                   | LL_RAMECC_MONITOR_IT_DE \
                                   | LL_RAMECC_MONITOR_IT_DEBW) /*!< RAMECC all RAMECC interrupts        */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_LL_Exported_Macros RAMECC Exported Macros
  * @{
  */

/** @defgroup RAMECC_LL_EM_COMMON_READ_REGISTERS Common Read Registers macro
  * @{
  */

/**
  * @brief  Write a value in RAMECC register.
  * @param  instance RAMECC Instance
  * @param  reg      Register to be written
  * @param  value    Value to be written in the register
  */
#define LL_RAMECC_WRITE_REG(instance, reg, value) STM32_WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in RAMECC register.
  * @param  instance RAMECC Instance.
  * @param  reg      Register to be read.
  * @return Register value.
  */
#define LL_RAMECC_READ_REG(instance, reg) STM32_READ_REG((instance)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_LL_Exported_Functions RAMECC Exported Functions
  * @{
  */

/** @defgroup RAMECC_LL_EF_IT_Management Monitor IT Management
  * @{
  */

/**
  * @brief  Enable the specified RAMECC global interrupts.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_EnableGlobalIT \n
  *  IER           GIE                LL_RAMECC_EnableGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupts Interrupt sources to enable.
  *         This parameter can take one or a combination of the following values:
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_EnableGlobalIT(RAMECC_TypeDef *p_ramecc, uint32_t interrupts)
{
  STM32_SET_BIT(p_ramecc->IER, interrupts);
}

/**
  * @brief  Disable the specified RAMECC global interrupts.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_DisableGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_DisableGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_DisableGlobalIT \n
  *  IER           GIE                LL_RAMECC_DisableGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupts Interrupt sources to disable.
  *         This parameter can take one or a combination of the following values:
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_DisableGlobalIT(RAMECC_TypeDef *p_ramecc, uint32_t interrupts)
{
  STM32_CLEAR_BIT(p_ramecc->IER, interrupts);
}

/**
  * @brief  Check if the specified RAMECC global interrupt is enabled or disabled.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_IsEnabledGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_IsEnabledGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_IsEnabledGlobalIT \n
  *  IER           GIE                LL_RAMECC_IsEnabledGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupt Interrupt source to check.
  *         This parameter can take one of the following values:
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_ALL   : All Interrupt Mask.
  * @return State of the specified global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledGlobalIT(const RAMECC_TypeDef *p_ramecc, uint32_t interrupt)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  interrupt) == (interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Get the specified RAMECC global interrupt enable status.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_GetGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_GetGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_GetGlobalIT \n
  *  IER           GIE                LL_RAMECC_GetGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupts Interrupt sources to get.
  *         This parameter can take one or a combination of the following values:
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_ALL   : All Interrupt Mask.
  * @retval Returned value can be one or a combination of the following values:
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_SE
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DE
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_DEBW
  *           @arg @ref  LL_RAMECC_GLOBAL_IT_ALL
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetGlobalIT(const RAMECC_TypeDef *p_ramecc, uint32_t interrupts)
{
  return STM32_READ_BIT(p_ramecc->IER,  interrupts);
}

/**
  * @brief  Enable the all ECC errors RAMECC global interrupt.
  * @rmtoll
  *  IER           GIE              LL_RAMECC_EnableIT_Global
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableIT_Global(RAMECC_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_ALL);
}


/**
  * @brief  Disable the all ECC errors RAMECC global interrupt.
  * @rmtoll
  *  IER           GIE              LL_RAMECC_DisableIT_Global
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableIT_Global(RAMECC_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_ALL);
}

/**
  * @brief  Check whether the all ECC errors RAMECC global interrupt is enabled or not.
  * @rmtoll
  *  IER           GIE              LL_RAMECC_IsEnabledIT_Global
  * @param  p_ramecc RAMECC Instance.
  * @return State of all ECC errors global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledIT_Global(const RAMECC_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_ALL) == (LL_RAMECC_GLOBAL_IT_ALL)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC single error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCSEIE              LL_RAMECC_EnableIT_GlobalSE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableIT_GlobalSE(RAMECC_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_SE);
}


/**
  * @brief  Disable the ECC single error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCSEIE              LL_RAMECC_DisableIT_GlobalSE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableIT_GlobalSE(RAMECC_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_SE);
}

/**
  * @brief  Check whether the ECC single error RAMECC global interrupt is enabled or not.
  * @rmtoll
  *  IER           GECCSEIE              LL_RAMECC_IsEnabledIT_GlobalSE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC single error global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledIT_GlobalSE(const RAMECC_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_SE) == (LL_RAMECC_GLOBAL_IT_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEIE              LL_RAMECC_EnableIT_GlobalDE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableIT_GlobalDE(RAMECC_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_DE);
}

/**
  * @brief  Disable the ECC double error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEIE              LL_RAMECC_DisableIT_GlobalDE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableIT_GlobalDE(RAMECC_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_DE);
}

/**
  * @brief  Check whether the ECC double error RAMECC global interrupt is enabled or not.
  * @rmtoll
  *  IER           GECCDEIE              LL_RAMECC_IsEnabledIT_GlobalDE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledIT_GlobalDE(const RAMECC_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_DE) == (LL_RAMECC_GLOBAL_IT_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error on byte write RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEBWIE            LL_RAMECC_EnableIT_GlobalDEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableIT_GlobalDEBW(RAMECC_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_DEBW);
}

/**
  * @brief  Disable the ECC double error on byte write RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEBWIE            LL_RAMECC_DisableIT_GlobalDEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableIT_GlobalDEBW(RAMECC_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_DEBW);
}

/**
  * @brief  Check whether the ECC double error on byte write RAMECC global interrupt is enabled or not.
  * @rmtoll
  *  IER           GECCDEBWIE            LL_RAMECC_IsEnabledIT_GlobalDEBW
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error on byte write global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledIT_GlobalDEBW(const RAMECC_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  LL_RAMECC_GLOBAL_IT_DEBW) == (LL_RAMECC_GLOBAL_IT_DEBW)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RAMECC_LL_EF_IT_Management Monitor IT Management
  * @{
  */

/**
  * @brief  Enable the specified RAMECC interrupts.
  * @rmtoll
  *  CR           ECCSEIE           LL_RAMECC_EnableMonitorIT \n
  *  CR           ECCDEIE           LL_RAMECC_EnableMonitorIT \n
  *  CR           ECCDEBWIE         LL_RAMECC_EnableMonitorIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupts Interrupt sources to enable.
  *         This parameter can take one or a combination of the following values:
  *           @arg @ref LL_RAMECC_MONITOR_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_MONITOR_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_MONITOR_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref LL_RAMECC_MONITOR_IT_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_EnableMonitorIT(RAMECC_Monitor_TypeDef *p_ramecc, uint32_t interrupts)
{
  STM32_SET_BIT(p_ramecc->CR, interrupts);
}

/**
  * @brief  Disable the specified RAMECC interrupts.
  * @rmtoll
  *  CR           ECCSEIE           LL_RAMECC_DisableMonitorIT \n
  *  CR           ECCDEIE           LL_RAMECC_DisableMonitorIT \n
  *  CR           ECCDEBWIE         LL_RAMECC_DisableMonitorIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupts Interrupt sources to disable.
  *         This parameter can take one or a combination of the following values:
  *           @arg @ref LL_RAMECC_MONITOR_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_MONITOR_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_MONITOR_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref LL_RAMECC_MONITOR_IT_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_DisableMonitorIT(RAMECC_Monitor_TypeDef *p_ramecc, uint32_t interrupts)
{
  STM32_CLEAR_BIT(p_ramecc->CR, interrupts);
}

/**
  * @brief  Check if the specified RAMECC interrupt is enabled or disabled.
  * @rmtoll
  *  CR           ECCSEIE           LL_RAMECC_IsEnabledMonitorIT \n
  *  CR           ECCDEIE           LL_RAMECC_IsEnabledMonitorIT \n
  *  CR           ECCDEBWIE         LL_RAMECC_IsEnabledMonitorIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupt Interrupt source to check.
  *         This parameter can take one of the following values:
  *           @arg @ref  LL_RAMECC_MONITOR_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_MONITOR_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_MONITOR_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  * @return State of the selected interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledMonitorIT(const RAMECC_Monitor_TypeDef *p_ramecc, uint32_t interrupt)
{
  return ((STM32_READ_BIT(p_ramecc->CR,  interrupt) == (interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Get the specified RAMECC interrupt enable status.
  * @rmtoll
  *  IER           ECCSEIE           LL_RAMECC_GetMonitorIT \n
  *  IER           ECCDEIE           LL_RAMECC_GetMonitorIT \n
  *  IER           ECCDEBWIE         LL_RAMECC_GetMonitorIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupts Interrupt sources to get.
  *         This parameter can take one or a combination of the following values:
  *           @arg @ref  LL_RAMECC_MONITOR_IT_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_MONITOR_IT_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_MONITOR_IT_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_MONITOR_IT_ALL   : All Interrupt Mask.
  * @retval Returned value can be one or a combination of the following values:
  *           @arg @ref  LL_RAMECC_MONITOR_IT_SE
  *           @arg @ref  LL_RAMECC_MONITOR_IT_DE
  *           @arg @ref  LL_RAMECC_MONITOR_IT_DEBW
  *           @arg @ref  LL_RAMECC_MONITOR_IT_ALL
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetMonitorIT(const RAMECC_Monitor_TypeDef *p_ramecc, uint32_t interrupts)
{
  return STM32_READ_BIT(p_ramecc->CR,  interrupts);
}

/**
  * @brief  Enable the ECC single error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCSEIE              LL_RAMECC_EnableIT_MonitorSE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableIT_MonitorSE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_SE);
}

/**
  * @brief  Disable the ECC single error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCSEIE              LL_RAMECC_DisableIT_MonitorSE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableIT_MonitorSE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_SE);
}

/**
  * @brief  Check whether the ECC single error RAMECC interrupt is enabled or not.
  * @rmtoll
  *  CR           ECCSEIE              LL_RAMECC_IsEnabledIT_MonitorSE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC single error interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledIT_MonitorSE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_SE) == (LL_RAMECC_MONITOR_IT_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEIE              LL_RAMECC_EnableIT_MonitorDE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableIT_MonitorDE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_DE);
}

/**
  * @brief  Disable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEIE              LL_RAMECC_DisableIT_MonitorDE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableIT_MonitorDE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_DE);
}

/**
  * @brief  Check whether the ECC double error RAMECC interrupt is enabled or not.
  * @rmtoll
  *  CR           ECCDEIE              LL_RAMECC_IsEnabledIT_MonitorDE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledIT_MonitorDE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_DE) == (LL_RAMECC_MONITOR_IT_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEBWIE            LL_RAMECC_EnableIT_MonitorDEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableIT_MonitorDEBW(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_DEBW);
}

/**
  * @brief  Disable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEBWIE            LL_RAMECC_DisableIT_MonitorDEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableIT_MonitorDEBW(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_DEBW);
}

/**
  * @brief  Check whether the ECC double error RAMECC interrupt is enabled or not.
  * @rmtoll
  *  CR           ECCDEBWIE            LL_RAMECC_IsEnabledIT_MonitorDEBW
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledIT_MonitorDEBW(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, LL_RAMECC_MONITOR_IT_DEBW) == (LL_RAMECC_MONITOR_IT_DEBW)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the RAMECC monitor instance address latching error.
  * @rmtoll
  *  CR           ECCELEN            LL_RAMECC_EnableAddressLatch
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableAddressLatch(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, RAMECC_CR_ECCELEN);
}

/**
  * @brief  Disable the RAMECC monitor instance address latching error.
  * @rmtoll
  *  CR           ECCELEN            LL_RAMECC_DisableAddressLatch
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableAddressLatch(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, RAMECC_CR_ECCELEN);
}

/**
  * @brief  Check whether the RAMECC monitor instance address latching error is enabled or not.
  * @rmtoll
  *  CR           ECCELEN            LL_RAMECC_IsEnabledAddressLatch
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of address latching error (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledAddressLatch(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, RAMECC_CR_ECCELEN) == (RAMECC_CR_ECCELEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the RAMECC monitor instance ECC test access.
  * @rmtoll
  *  CR           ECCTEA            LL_RAMECC_EnableECCTestAccess
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableECCTestAccess(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, RAMECC_CR_ECCTEA);
}

/**
  * @brief  Disable the RAMECC monitor instance ECC test access.
  * @rmtoll
  *  CR           ECCTEA            LL_RAMECC_DisableECCTestAccess
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableECCTestAccess(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, RAMECC_CR_ECCTEA);
}

/**
  * @brief  Check whether the RAMECC monitor instance ECC test access is enabled or not.
  * @rmtoll
  *  CR           ECCTEA            LL_RAMECC_IsEnabledECCTestAccess
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of ECC test access (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledECCTestAccess(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, RAMECC_CR_ECCTEA) == (RAMECC_CR_ECCTEA)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RAMECC_LL_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief  Clear the RAMECC monitor pending flags.
  * @rmtoll
  *  SR           SEDCF           LL_RAMECC_ReadFlag \n
  *  SR           DEDF            LL_RAMECC_ReadFlag \n
  *  SR           DEBWDF          LL_RAMECC_ReadFlag
  * @param  p_ramecc RAMECC Monitor Instance.
  * @param  flags    Flags to read.
  *         This parameter can take one or a combination of the following values:
  *            @arg @ref LL_RAMECC_FLAG_SE   : Single Error Detected and Corrected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DE   : Double Error Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DEBW : Double Error on Byte Write Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_ALL  : RAMECC All Error Flags.
  * @retval State of selected flags.
            The return value can be one or a combination of the following values:
              @arg @ref LL_RAMECC_FLAG_SE
              @arg @ref LL_RAMECC_FLAG_DE
              @arg @ref LL_RAMECC_FLAG_DEBW
              @arg @ref LL_RAMECC_FLAG_ALL
  */
__STATIC_INLINE uint32_t LL_RAMECC_ReadFlag(const RAMECC_Monitor_TypeDef *p_ramecc, uint32_t flags)
{
  return STM32_READ_BIT(p_ramecc->SR, flags);
}

/**
  * @brief  Clear the RAMECC monitor pending flags.
  * @rmtoll
  *  SR           SEDCF           LL_RAMECC_ClearFlag \n
  *  SR           DEDF            LL_RAMECC_ClearFlag \n
  *  SR           DEBWDF          LL_RAMECC_ClearFlag
  * @param  p_ramecc RAMECC Monitor Instance.
  * @param  flags    Flags to clear.
  *         This parameter can take one or a combination of the following values:
  *            @arg @ref LL_RAMECC_FLAG_SE   : Single Error Detected and Corrected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DE   : Double Error Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DEBW : Double Error on Byte Write Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_ALL  : RAMECC All Error Flags.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag(RAMECC_Monitor_TypeDef *p_ramecc, uint32_t flags)
{
  STM32_MODIFY_REG(p_ramecc->SR, flags, ~flags);
}

/**
  * @brief  Get the RAMECC Single Error Detected and Corrected flag.
  * @rmtoll
  *  SR           SEDCF               LL_RAMECC_IsActiveFlag_SE
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of SE flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsActiveFlag_SE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->SR, LL_RAMECC_FLAG_SE) == (LL_RAMECC_FLAG_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the RAMECC Single Error Detected and Corrected flag.
  * @rmtoll
  *  SR           SEDCF           LL_RAMECC_ClearFlag_SE
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag_SE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->SR, LL_RAMECC_FLAG_SE);
}

/**
  * @brief  Get the RAMECC Double Error Detected flag.
  * @rmtoll
  *  SR           DEDF                LL_RAMECC_IsActiveFlag_DE
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of DE flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsActiveFlag_DE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DE) == (LL_RAMECC_FLAG_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the RAMECC Double Error Detected flag.
  * @rmtoll
  *  SR           DEDF            LL_RAMECC_ClearFlag_DE
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag_DE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DE);
}

/**
  * @brief  Get the RAMECC Double Error on Byte Write Detected flag.
  * @rmtoll
  *  SR           DEBWDF              LL_RAMECC_IsActiveFlag_DEBW
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of DEBW flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsActiveFlag_DEBW(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DEBW) == (LL_RAMECC_FLAG_DEBW)) ? 1UL : 0UL);
}

/**
  * @brief  Clear the RAMECC Double Error on Byte Write Detected flag.
  * @rmtoll
  *  SR           DEBWDF            LL_RAMECC_ClearFlag_DE
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag_DEBW(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DEBW);
}

/**
  * @}
  */

/** @defgroup RAMECC_LL_Error_Info_Getters Error Info Getters
  * @{
  */

/**
  * @brief  Get the RAMECC error address.
  * @rmtoll
  *  FAR           FAR           LL_RAMECC_GetErrorAddressOffset
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return Error address offset.
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetErrorAddressOffset(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((uint32_t)STM32_READ_REG(p_ramecc->FAR));
}

/**
  * @brief  Get the RAMECC error data bytes.
  * @rmtoll
  *  FDR           FDR         LL_RAMECC_GetErrorDataBytes
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return Error data bytes.
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetErrorDataBytes(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((uint32_t)STM32_READ_REG(p_ramecc->FDR));
}

/**
  * @brief  Get the RAMECC error code.
  * @rmtoll
  *  FEC           FEC           LL_RAMECC_GetErrorCode
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return Error code offset.
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetErrorCode(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((uint32_t)STM32_READ_REG(p_ramecc->FECR));
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_LL_RAMECC_H */
