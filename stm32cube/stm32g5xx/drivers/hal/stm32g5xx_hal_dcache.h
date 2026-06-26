/**
  ******************************************************************************
  * @file    stm32g5xx_hal_dcache.h
  * @brief   Header file of DCACHE HAL module.
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
#ifndef STM32G5XX_HAL_DCACHE_H
#define STM32G5XX_HAL_DCACHE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g5xx_hal_def.h"
#include "stm32g5xx_ll_dcache.h"

/** @addtogroup STM32G5xx_HAL_Driver
  * @{
  */

#if defined (DCACHE)

/** @defgroup DCACHE DCACHE
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** @defgroup DCACHE_Exported_Types HAL DCACHE Types
  * @{
  */

/** @defgroup DCACHE_Exported_Types_Group1 Enumerations
  * @{
  */

/**
  * @brief HAL DCACHE Instance Definition
  *
  */
typedef enum
{
  HAL_DCACHE = DCACHE_BASE,   /*!< Instance DCACHE   */
} hal_dcache_t;

/**
  * @brief HAL DCACHE Read Burst Type Definition
  *
  */
typedef enum
{
  HAL_DCACHE_READ_BURST_WRAP = LL_DCACHE_READ_BURST_WRAP, /*!< WRAP configuration */
  HAL_DCACHE_READ_BURST_INCR = LL_DCACHE_READ_BURST_INCR, /*!< INCR configuration */
} hal_dcache_read_burst_t;

/**
  * @brief HAL DCACHE State Definition
  *
  */
typedef enum
{
  HAL_DCACHE_STATE_RESET        = 0UL,           /*!< DCACHE driver not initialized and not started */
  HAL_DCACHE_STATE_IDLE         = (1UL << 31U),  /*!< DCACHE driver initialized and not started */
  HAL_DCACHE_STATE_ACTIVE       = (1UL << 30U),  /*!< DCACHE driver initialized and started */
  HAL_DCACHE_STATE_MAINTENANCE  = (1UL << 29U),  /*!< DCACHE driver initialized, started and a maintenance operation is ongoing */
} hal_dcache_state_t;

/**
  * @brief DCACHE ECC Type Definition
  *
  */
typedef enum
{
  HAL_DCACHE_ECC_NONE   = 0U,                   /*!< DCACHE ECC none                   */
  HAL_DCACHE_ECC_SINGLE = LL_DCACHE_SR_SERRF,   /*!< DCACHE ECC single error detection */
  HAL_DCACHE_ECC_DOUBLE = LL_DCACHE_SR_DERRF    /*!< DCACHE ECC double error detection */
} hal_dcache_ecc_type_t;

/**
  * @brief DCACHE ECC Status Definition
  *
  */
typedef enum
{
  HAL_DCACHE_ECC_NOT_CORRECTED = 0U,     /*!< DCACHE ECC not corrected */
  HAL_DCACHE_ECC_CORRECTED     = 1U      /*!< DCACHE ECC corrected     */
} hal_dcache_ecc_status_t;

/**
  * @brief DCACHE ECC Fail Info Definition
  *
  */
typedef struct
{
  hal_dcache_ecc_type_t   type;     /*!< DCACHE ECC type    */
  hal_dcache_ecc_status_t status;   /*!< DCACHE ECC status  */
} hal_dcache_ecc_fail_info_t;

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Types_Group2 Handle Structure
  * @{
  */

typedef struct hal_dcache_handle_s hal_dcache_handle_t; /*!< DCACHE Handle Type Definition */

#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
typedef  void (*hal_dcache_cb_t)(hal_dcache_handle_t *hdcache); /*!< Pointer to a DCACHE callback functions */
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */

/**
  * @brief DCACHE Handle Structure Definition
  *
  */
struct hal_dcache_handle_s
{
  /*! Peripheral instance. */
  hal_dcache_t instance;

  /*! DCACHE global state. */
  volatile hal_dcache_state_t global_state;

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
  /*! Variable storing the last errors. */
  volatile uint32_t last_error_codes;
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
  /*! Error user callback (disabled if the switch USE_HAL_DCACHE_REGISTER_CALLBACKS is set to 0U) */
  hal_dcache_cb_t p_error_cb;
  /*! Clean by Address user callback (disabled if the switch USE_HAL_DCACHE_REGISTER_CALLBACKS is set to 0U) */
  hal_dcache_cb_t p_clean_by_addr_cb;
  /*! Invalidate by Address user callback (disabled if the switch USE_HAL_DCACHE_REGISTER_CALLBACKS is set to 0U) */
  hal_dcache_cb_t p_invalidate_by_addr_cb;
  /*! Invalidate Complete user callback (disabled if the switch USE_HAL_DCACHE_REGISTER_CALLBACKS is set to 0U) */
  hal_dcache_cb_t p_invalidate_cplt_cb;
  /*! Clean and Invalidate by Address user callback
     (disabled if the switch USE_HAL_DCACHE_REGISTER_CALLBACKS is set to 0U) */
  hal_dcache_cb_t p_clean_invalid_by_addr_cb;
  /*! ECC Error user callback (disabled if the switch USE_HAL_DCACHE_REGISTER_CALLBACKS is set to 0U) */
  hal_dcache_cb_t p_ecc_error_cb;

#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */

#if defined(USE_HAL_DCACHE_USER_DATA) && (USE_HAL_DCACHE_USER_DATA == 1)
  /*! DCACHE user data */
  const void *p_user_data;
#endif /* USE_HAL_DCACHE_USER_DATA */
};

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DCACHE_Exported_Constants HAL DCACHE Constants
  * @{
  */

/** @defgroup DCACHE_Monitor_Type Monitor type
  * @{
  */
#define HAL_DCACHE_MONITOR_READ_HIT        LL_DCACHE_MONITOR_READ_HIT    /*!< Read Hit Monitor */
#define HAL_DCACHE_MONITOR_READ_MISS       LL_DCACHE_MONITOR_READ_MISS   /*!< Read Miss Monitor */
#define HAL_DCACHE_MONITOR_WRITE_HIT       LL_DCACHE_MONITOR_WRITE_HIT   /*!< Write Hit Monitor */
#define HAL_DCACHE_MONITOR_WRITE_MISS      LL_DCACHE_MONITOR_WRITE_MISS  /*!< Write Miss Monitor */
#define HAL_DCACHE_MONITOR_ALL             LL_DCACHE_MONITOR_ALL         /*!< Write/Read Miss/Hit Monitors */
/**
  * @}
  */

/** @defgroup DCACHE_Interrupts Interrupts
  * @{
  */
#define HAL_DCACHE_IT_NONE        0U                     /*!< No interrupt               */
#define HAL_DCACHE_IT_ERROR       LL_DCACHE_IER_ERRIE    /*!< Error interrupt            */
/**
  * @}
  */

/** @defgroup DCACHE_Error_Code Error Code
  * @{
  */
#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
#define HAL_DCACHE_ERROR_NONE            0U              /*!< No error */
#define HAL_DCACHE_ERROR_EVICTION_CLEAN  1U              /*!< Error due to line eviction or clean operation */
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

/** @defgroup DCACHE_ECC_Interrupts ECC Interrupts
  * @{
  */
#define HAL_DCACHE_IT_ECC_SINGLE    LL_DCACHE_IER_SERRIE    /*!< Single-bit ECC interrupt */
#define HAL_DCACHE_IT_ECC_DOUBLE    LL_DCACHE_IER_DERRIE    /*!< Double-bit ECC interrupt */
#define HAL_DCACHE_IT_ECC_ALL       (HAL_DCACHE_IT_ECC_SINGLE | HAL_DCACHE_IT_ECC_DOUBLE) /*!< All ECC interrupts */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DCACHE_Exported_Functions HAL DCACHE Functions
  * @{
  */

/** @defgroup DCACHE_Exported_Functions_Group1 Initialization and DeInitialization functions
  * @{
  */

hal_status_t HAL_DCACHE_Init(hal_dcache_handle_t *hdcache, hal_dcache_t instance);
void HAL_DCACHE_DeInit(hal_dcache_handle_t *hdcache);

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group2 Configuration functions
  * @{
  */

hal_status_t HAL_DCACHE_SetReadBurstType(hal_dcache_handle_t *hdcache, hal_dcache_read_burst_t read_burst_type);
hal_dcache_read_burst_t HAL_DCACHE_GetReadBurstType(const hal_dcache_handle_t *hdcache);

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group3 Control functions
  * @{
  */

hal_status_t HAL_DCACHE_Start(hal_dcache_handle_t *hdcache, uint32_t interrupts);
hal_status_t HAL_DCACHE_Stop(hal_dcache_handle_t *hdcache);

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group4 ECC hardware control functions
  * @{
  */

hal_status_t HAL_DCACHE_ECC_Enable(hal_dcache_handle_t *hdcache);
hal_status_t HAL_DCACHE_ECC_Disable(hal_dcache_handle_t *hdcache);
hal_status_t HAL_DCACHE_ECC_Enable_IT(hal_dcache_handle_t *hdcache, uint32_t interrupts);

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group5 Monitoring functions
  * @{
  */

hal_status_t HAL_DCACHE_EnableMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type);
hal_status_t HAL_DCACHE_DisableMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type);
hal_status_t HAL_DCACHE_ResetMonitors(hal_dcache_handle_t *hdcache, uint32_t monitor_type);
uint32_t HAL_DCACHE_GetMonitorReadHitValue(const hal_dcache_handle_t *hdcache);
uint32_t HAL_DCACHE_GetMonitorReadMissValue(const hal_dcache_handle_t *hdcache);
uint32_t HAL_DCACHE_GetMonitorWriteHitValue(const hal_dcache_handle_t *hdcache);
uint32_t HAL_DCACHE_GetMonitorWriteMissValue(const hal_dcache_handle_t *hdcache);

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group6 Maintenance Operations functions
  * @{
  */

hal_status_t HAL_DCACHE_Invalidate(hal_dcache_handle_t *hdcache);
hal_status_t HAL_DCACHE_Invalidate_IT(hal_dcache_handle_t *hdcache);
hal_status_t HAL_DCACHE_InvalidateByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
hal_status_t HAL_DCACHE_InvalidateByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
hal_status_t HAL_DCACHE_CleanByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
hal_status_t HAL_DCACHE_CleanByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
hal_status_t HAL_DCACHE_CleanInvalidByAddr(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);
hal_status_t HAL_DCACHE_CleanInvalidByAddr_IT(hal_dcache_handle_t *hdcache, uint32_t addr, uint32_t size_byte);

/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group7 IRQ and callback functions
  * @{
  */
void HAL_DCACHE_IRQHandler(hal_dcache_handle_t *hdcache);
void HAL_DCACHE_ErrorCallback(hal_dcache_handle_t *hdcache);
void HAL_DCACHE_ECC_ErrorCallback(hal_dcache_handle_t *hdcache);
void HAL_DCACHE_InvalidateCompleteCallback(hal_dcache_handle_t *hdcache);
void HAL_DCACHE_CleanByAddrCallback(hal_dcache_handle_t *hdcache);
void HAL_DCACHE_InvalidateByAddrCallback(hal_dcache_handle_t *hdcache);
void HAL_DCACHE_CleanInvalidByAddrCallback(hal_dcache_handle_t *hdcache);

#if defined(USE_HAL_DCACHE_REGISTER_CALLBACKS) && (USE_HAL_DCACHE_REGISTER_CALLBACKS == 1)
hal_status_t HAL_DCACHE_RegisterErrorCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
hal_status_t HAL_DCACHE_RegisterECCErrorCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
hal_status_t HAL_DCACHE_RegisterInvalidateCompleteCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
hal_status_t HAL_DCACHE_RegisterCleanByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
hal_status_t HAL_DCACHE_RegisterInvalidateByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
hal_status_t HAL_DCACHE_RegisterCleanInvalidByAddrCallback(hal_dcache_handle_t *hdcache, hal_dcache_cb_t p_callback);
#endif /* USE_HAL_DCACHE_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group8 State functions
  * @{
  */
hal_dcache_state_t HAL_DCACHE_GetState(const hal_dcache_handle_t *hdcache);
/**
  * @}
  */

#if defined(USE_HAL_DCACHE_GET_LAST_ERRORS) && (USE_HAL_DCACHE_GET_LAST_ERRORS == 1)
/** @defgroup DCACHE_Exported_Functions_Group9 Error functions
  * @{
  */
uint32_t HAL_DCACHE_GetLastErrorCodes(const hal_dcache_handle_t *hdcache);
/**
  * @}
  */
#endif /* USE_HAL_DCACHE_GET_LAST_ERRORS */

/** @defgroup DCACHE_Exported_Functions_Group10 Accessor and Instance functions
  * @{
  */
#if defined(USE_HAL_DCACHE_USER_DATA) && (USE_HAL_DCACHE_USER_DATA == 1)
void HAL_DCACHE_SetUserData(hal_dcache_handle_t *hdcache, const void *p_user_data);
const void *HAL_DCACHE_GetUserData(const hal_dcache_handle_t *hdcache);
#endif /* USE_HAL_DCACHE_USER_DATA */

hal_dcache_t HAL_DCACHE_GetInstance(const hal_dcache_handle_t *hdcache);
DCACHE_TypeDef *HAL_DCACHE_GetLLInstance(const hal_dcache_handle_t *hdcache);
/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group11 ECC info functions
  * @{
  */
void HAL_DCACHE_ECC_GetInfo(const hal_dcache_handle_t *hdcache, hal_dcache_ecc_fail_info_t *p_info);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* DCACHE */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G5XX_HAL_DCACHE_H */
