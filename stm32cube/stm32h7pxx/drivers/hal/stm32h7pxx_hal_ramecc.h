/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_ramecc.h
  * @brief   Header file of RAMECC HAL module.
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
#ifndef STM32H7PXX_HAL_RAMECC_H
#define STM32H7PXX_HAL_RAMECC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_ramecc.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

#if defined (RAMECC1) || defined (RAMECC2)

/** @addtogroup RAMECC
  * @{
  */

/* Exported constants ---------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Constants RAMECC Exported Constants
  * @{
  */

/** @defgroup  RAMECC_Controller_Interrupts RAMECC controller interrupts
  * @{
  */
#define HAL_RAMECC_CONTROLLER_IT_SINGLE             LL_RAMECC_GLOBAL_IT_SE   /*!< RAMECC controller single error
                                                                                  interrupt                       */
#define HAL_RAMECC_CONTROLLER_IT_DOUBLE             LL_RAMECC_GLOBAL_IT_DE   /*!< RAMECC controller double error
                                                                                  interrupt                       */
#define HAL_RAMECC_CONTROLLER_IT_DOUBLE_BYTE_WRITE  LL_RAMECC_GLOBAL_IT_DEBW /*!< RAMECC controller double error
                                                                                  on byte write interrupt         */
#define HAL_RAMECC_CONTROLLER_IT_ALL                LL_RAMECC_GLOBAL_IT_ALL  /*!< RAMECC controller all RAMECC
                                                                                  interrupts                      */
/**
  * @}
  */

/** @defgroup  RAMECC_Monitor_Interrupts RAMECC monitor interrupts
  * @{
  */
#define HAL_RAMECC_MONITOR_IT_SINGLE            LL_RAMECC_MONITOR_IT_SE   /*!< RAMECC monitor single error interrupt  */
#define HAL_RAMECC_MONITOR_IT_DOUBLE            LL_RAMECC_MONITOR_IT_DE   /*!< RAMECC monitor double error interrupt  */
#define HAL_RAMECC_MONITOR_IT_DOUBLE_BYTE_WRITE LL_RAMECC_MONITOR_IT_DEBW /*!< RAMECC monitor double error on byte
                                                                               write interrupt                        */
#define HAL_RAMECC_MONITOR_IT_ALL               LL_RAMECC_MONITOR_IT_ALL  /*!< RAMECC monitor all RAMECC interrupts   */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Types HAL RAMECC Types
  * @{
  */

/*! HAL RAMECC controller instance enumeration definition */
typedef enum
{
  HAL_RAMECC1 = RAMECC1_BASE,  /*!< RAMECC controller 1 instance */
  HAL_RAMECC2 = RAMECC2_BASE   /*!< RAMECC controller 2 instance */
} hal_ramecc_controller_t;

/*! HAL RAMECC monitor instance enumeration definition */
typedef enum
{
  HAL_RAMECC_AXISRAM1 = RAMECC1_AXISRAM1_BASE,  /*!< RAMECC AXISRAM1 monitor instance */
  HAL_RAMECC_AXISRAM2 = RAMECC1_AXISRAM2_BASE,  /*!< RAMECC AXISRAM2 monitor instance */
  HAL_RAMECC_AXISRAM3 = RAMECC1_AXISRAM3_BASE,  /*!< RAMECC AXISRAM3 monitor instance */
  HAL_RAMECC_AXISRAM4 = RAMECC1_AXISRAM4_BASE,  /*!< RAMECC AXISRAM4 monitor instance */
  HAL_RAMECC_ITCM     = RAMECC1_ITCM_BASE,      /*!< RAMECC ITCM monitor instance     */
  HAL_RAMECC_DTCM0    = RAMECC1_DTCM0_BASE,     /*!< RAMECC DTCM0 monitor instance    */
  HAL_RAMECC_DTCM1    = RAMECC1_DTCM1_BASE,     /*!< RAMECC DTCM1 monitor instance    */
  HAL_RAMECC_BKPSRAM  = RAMECC2_BKPSRAM_BASE    /*!< RAMECC BKPSRAM monitor instance   */
} hal_ramecc_monitor_t;

/*! HAL RAMECC ECC fail type enumeration definition */
typedef enum
{
  HAL_RAMECC_ECC_NONE              = 0U,                  /*!< RAMECC ECC none                                  */
  HAL_RAMECC_ECC_SINGLE            = LL_RAMECC_FLAG_SE,   /*!< RAMECC ECC single error detection                */
  HAL_RAMECC_ECC_DOUBLE            = LL_RAMECC_FLAG_DE,   /*!< RAMECC ECC double error detection                */
  HAL_RAMECC_ECC_DOUBLE_BYTE_WRITE = LL_RAMECC_FLAG_DEBW  /*!< RAMECC ECC double error on byte write detection  */
} hal_ramecc_ecc_type_t;

/*! HAL RAMECC ECC type enumeration definition */
typedef enum
{
  HAL_RAMECC_ECC_NOT_CORRECTED = 0U,  /*!< RAMECC ECC not corrected */
  HAL_RAMECC_ECC_CORRECTED     = 1U   /*!< RAMECC ECC corrected     */
} hal_ramecc_ecc_status_t;

/*! HAL RAMECC ECC fail structure definition */
typedef struct
{
  hal_ramecc_ecc_type_t   type;    /*!< RAMECC ECC type    */
  hal_ramecc_ecc_status_t status;  /*!< RAMECC ECC status  */
  uint32_t                address; /*!< RAMECC ECC address */
  uint32_t                code;    /*!< RAMECC ECC code    */
  uint32_t                data;    /*!< RAMECC ECC data    */
} hal_ramecc_ecc_info_t;

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Functions HAL RAMECC Functions
  * @{
  */

/** @defgroup RAMECC_Exported_Functions_Group1 Controller-level ECC management functions
  * @{
  */

hal_status_t HAL_RAMECC_EnableController(hal_ramecc_controller_t instance);
hal_status_t HAL_RAMECC_EnableController_IT(hal_ramecc_controller_t instance, uint32_t interrupt);
hal_status_t HAL_RAMECC_DisableController(hal_ramecc_controller_t instance);

/**
  * @}
  */

/** @defgroup RAMECC_Exported_Functions_Group2 Monitor-level ECC management functions
  * @{
  */

hal_status_t HAL_RAMECC_EnableMonitor(hal_ramecc_monitor_t instance);
hal_status_t HAL_RAMECC_EnableMonitor_IT(hal_ramecc_monitor_t instance, uint32_t interrupt);
hal_status_t HAL_RAMECC_DisableMonitor(hal_ramecc_monitor_t instance);

void HAL_RAMECC_GetInfo(hal_ramecc_monitor_t instance, hal_ramecc_ecc_info_t *p_info);
void HAL_RAMECC_CleanInfo(hal_ramecc_monitor_t instance);

/**
  * @}
  */

/** @defgroup RAMECC_Exported_Functions_Group3 Handle interrupt and callbacks functions
  * @{
  */

/* IRQHandler API */
void HAL_RAMECC_IRQHandler(hal_ramecc_monitor_t instance);

/* Callback API */
void HAL_RAMECC_ErrorCallback(hal_ramecc_monitor_t instance);

/**
  * @}
  */

/** @defgroup RAMECC_Exported_Functions_Group4 Instance and SRAM info getter functions
  * @{
  */

RAMECC_TypeDef *HAL_RAMECC_GetLLControllerInstance(hal_ramecc_controller_t instance);
RAMECC_Monitor_TypeDef *HAL_RAMECC_GetLLMonitorInstance(hal_ramecc_monitor_t instance);
uint32_t HAL_RAMECC_GetSRAMBaseAddress(hal_ramecc_monitor_t instance);
uint32_t HAL_RAMECC_GetSRAMSize(hal_ramecc_monitor_t instance);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* RAMECC1 || RAMECC2 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif
#endif /* STM32H7PXX_HAL_RAMECC_H */
