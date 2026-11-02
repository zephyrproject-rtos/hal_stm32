/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_axim.h
  * @brief   Header file of AXIM HAL module.
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
#ifndef STM32H7PXX_HAL_AXIM_H
#define STM32H7PXX_HAL_AXIM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_axim.h"

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */
#if defined (AXIM)

/** @defgroup AXIM AXIM
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup AXIM_Exported_Types HAL AXIM Types
  * @{
  */

/*! AXIM initiators enumeration definition */
typedef enum
{
  HAL_AXIM_INI_GPDMA  = LL_AXIM_ASIB_GPDMA,  /*!< Initiator 1:  GPDMA  */
  HAL_AXIM_INI_SDMMC1 = LL_AXIM_ASIB_SDMMC1, /*!< Initiator 2:  SDMMC1 */
  HAL_AXIM_INI_HPDMA  = LL_AXIM_ASIB_HPDMA,  /*!< Initiator 3:  HPDMA  */
  HAL_AXIM_INI_CORE   = LL_AXIM_ASIB_CORE,   /*!< Initiator 4:  CORE   */
  HAL_AXIM_INI_NPU_1  = LL_AXIM_ASIB_NPU_1,  /*!< Initiator 5:  NPU 1  */
  HAL_AXIM_INI_NPU_2  = LL_AXIM_ASIB_NPU_2   /*!< Initiator 6:  NPU 2  */
} hal_axim_ini_t;

/*! AXIM targets enumeration definition */
typedef enum
{
  HAL_AXIM_TARG_AHBIC_BRIDGE = LL_AXIM_AMIB_AHBIC_BRIDGE, /*!< Target 1:  AHBIC_BRIDGE */
  HAL_AXIM_TARG_FMC          = LL_AXIM_AMIB_FMC,          /*!< Target 2:  FMC          */
  HAL_AXIM_TARG_XSPI1        = LL_AXIM_AMIB_XSPI1,        /*!< Target 3:  XSPI1        */
  HAL_AXIM_TARG_AXISRAM3     = LL_AXIM_AMIB_AXISRAM3,     /*!< Target 4:  AXISRAM3     */
  HAL_AXIM_TARG_AXISRAM2     = LL_AXIM_AMIB_AXISRAM2,     /*!< Target 5:  AXISRAM2     */
  HAL_AXIM_TARG_AXISRAM1     = LL_AXIM_AMIB_AXISRAM1,     /*!< Target 6:  AXISRAM1     */
  HAL_AXIM_TARG_FLASH        = LL_AXIM_AMIB_FLASH,        /*!< Target 7:  FLASH        */
  HAL_AXIM_TARG_AXISRAM4     = LL_AXIM_AMIB_AXISRAM4,     /*!< Target 8:  AXISRAM4     */
  HAL_AXIM_TARG_AHBS_BRIDGE  = LL_AXIM_AMIB_AHBS_BRIDGE   /*!< Target 9:  AHBS_BRIDGE  */
} hal_axim_targ_t;

/*! AXIM read/write issuing capability enumeration definition */
typedef enum
{
  HAL_AXIM_ISSUING_NORMAL         = LL_AXIM_ISSUING_NORMAL,         /*!< AXIM Issuing capability No Override */
  HAL_AXIM_ISSUING_OVERRIDE_READ  = LL_AXIM_ISSUING_OVERRIDE_READ,  /*!< AXIM Issuing capability Override Read */
  HAL_AXIM_ISSUING_OVERRIDE_WRITE = LL_AXIM_ISSUING_OVERRIDE_WRITE, /*!< AXIM Issuing capability Override Write */
  HAL_AXIM_ISSUING_OVERRIDE_BOTH  = LL_AXIM_ISSUING_OVERRIDE_BOTH   /*!< AXIM Issuing capability Override Read and Write */
} hal_axim_issuing_capability_t;

/*! AXIM packing state enumeration definition */
typedef enum
{
  HAL_AXIM_PACKING_DISABLE = 0U, /*!< AXIM packing disable */
  HAL_AXIM_PACKING_ENABLE  = 1U  /*!< AXIM packing enable  */
} hal_axim_packing_state_t;

/*! AXIM packing status enumeration definition */
typedef enum
{
  HAL_AXIM_PACKING_DISABLED = 0U, /*!< AXIM packing disabled */
  HAL_AXIM_PACKING_ENABLED  = 1U  /*!< AXIM packing enabled  */
} hal_axim_packing_status_t;

/*! AXIM increment override enumeration definition */
typedef enum
{
  HAL_AXIM_INCREMENT_NORMAL         = LL_AXIM_INCREMENT_NORMAL,         /*!< AXIM normal increment behavior */
  HAL_AXIM_INCREMENT_OVERRIDE_READ  = LL_AXIM_INCREMENT_OVERRIDE_READ,  /*!< AXIM override increment for read */
  HAL_AXIM_INCREMENT_OVERRIDE_WRITE = LL_AXIM_INCREMENT_OVERRIDE_WRITE, /*!< AXIM override increment for write */
  HAL_AXIM_INCREMENT_OVERRIDE_BOTH  = LL_AXIM_INCREMENT_OVERRIDE_BOTH   /*!< AXIM override increment for both read and write */
} hal_axim_increment_override_t;


/*! AXIM long burst state enumeration definition */
typedef enum
{
  HAL_AXIM_LONG_BURST_DISABLE = 0U, /*!< AXIM long burst disable */
  HAL_AXIM_LONG_BURST_ENABLE  = 1U  /*!< AXIM long burst enable  */
} hal_axim_long_burst_state_t;

/*! AXIM long burst status enumeration definition */
typedef enum
{
  HAL_AXIM_LONG_BURST_DISABLED = 0U, /*!< AXIM long burst disabled */
  HAL_AXIM_LONG_BURST_ENABLED  = 1U  /*!< AXIM long burst enabled  */
} hal_axim_long_burst_status_t;

/*! AXIM initiator configuration structure definition */
typedef struct
{
  uint8_t                       read_qos;           /*!< Read priority(QoS)               */
  uint8_t                       write_qos;          /*!< Write priority(QoS)              */
  hal_axim_issuing_capability_t capability;         /*!< Read/Write issuing capability    */
  hal_axim_packing_state_t      packing;            /*!< Packing state                    */
  hal_axim_increment_override_t increment_override; /*!< Increment override configuration */
} hal_axim_ini_config_t;

/*! AXIM target configuration structure definition */
typedef struct
{
  hal_axim_issuing_capability_t bus_matrix_capability; /*!< Target bus matrix r/w issuing capability */
  hal_axim_issuing_capability_t capability;            /*!< Target r/w issuing capability            */
  hal_axim_packing_state_t      packing;               /*!< Target packing state                     */
  hal_axim_long_burst_state_t   long_burst;            /*!< Target long burst state                  */
} hal_axim_targ_config_t;

/*! AXIM JEP-106 identification structure definition */
typedef struct
{
  uint32_t jep_continuation_code : 4; /*!< JEP-106 Continuation Code */
  uint32_t jep_identity_code     : 7; /*!< JEP-106 Identity Code     */
  uint32_t jep_code_flag         : 1; /*!< JEP-106 Code Flag         */
} hal_axim_jep_id_t;

/*! AXIM peripheral information structure definition */
typedef struct
{
  hal_axim_jep_id_t    jep_id;           /*!< JEP-106 Identification      */
  uint16_t             part_number;      /*!< AXIM Part Number            */
  uint8_t              file_size_unit4k; /*!< AXIM File Size in 4KB units */
  uint8_t              revision;         /*!< AXIM Revision               */
} hal_axim_periph_info_t;

/*! AXIM component information structure definition */
typedef struct
{
  uint32_t preamble;   /*!< AXIM Component Preamble bits */
  uint8_t  comp_class; /*!< AXIM Component Class         */
} hal_axim_component_info_t;

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @defgroup AXIM_Exported_Functions HAL AXIM Functions
  * @{
  */

/** @defgroup AXIM_Exported_Functions_Group1 AXIM Initiator function prototypes.
  * @{
  */

hal_status_t HAL_AXIM_INI_SetConfig(hal_axim_ini_t ini, const hal_axim_ini_config_t *p_ini_config);
void HAL_AXIM_INI_GetConfig(hal_axim_ini_t ini, hal_axim_ini_config_t *p_ini_config);

hal_status_t HAL_AXIM_INI_SetReadQoS(hal_axim_ini_t ini, uint32_t read_qos);
uint32_t HAL_AXIM_INI_GetReadQoS(hal_axim_ini_t ini);

hal_status_t HAL_AXIM_INI_SetWriteQoS(hal_axim_ini_t ini, uint32_t write_qos);
uint32_t HAL_AXIM_INI_GetWriteQoS(hal_axim_ini_t ini);

hal_status_t HAL_AXIM_INI_SetIssuingCapability(hal_axim_ini_t ini, hal_axim_issuing_capability_t capability);
hal_axim_issuing_capability_t HAL_AXIM_INI_GetIssuingCapability(hal_axim_ini_t ini);

hal_status_t HAL_AXIM_INI_EnablePacking(hal_axim_ini_t ini);
hal_status_t HAL_AXIM_INI_DisablePacking(hal_axim_ini_t ini);
hal_axim_packing_status_t HAL_AXIM_INI_IsEnabledPacking(hal_axim_ini_t ini);

hal_status_t HAL_AXIM_INI_SetIncrementOverride(hal_axim_ini_t ini, hal_axim_increment_override_t increment_override);
hal_axim_increment_override_t HAL_AXIM_INI_GetIncrementOverride(hal_axim_ini_t ini);
/**
  * @}
  */

/** @defgroup AXIM_Exported_Functions_Group2 AXIM Target function prototypes.
  * @{
  */
hal_status_t HAL_AXIM_TARG_SetConfig(hal_axim_targ_t targ, const hal_axim_targ_config_t *p_targ_config);
void HAL_AXIM_TARG_GetConfig(hal_axim_targ_t targ, hal_axim_targ_config_t *p_targ_config);

hal_status_t HAL_AXIM_TARG_SetBusMatrixIssuingCapability(hal_axim_targ_t targ,
                                                         hal_axim_issuing_capability_t bus_matrix_capability);
hal_axim_issuing_capability_t HAL_AXIM_TARG_GetBusMatrixIssuingCapability(hal_axim_targ_t targ);

hal_status_t HAL_AXIM_TARG_SetIssuingCapability(hal_axim_targ_t targ, hal_axim_issuing_capability_t capability);
hal_axim_issuing_capability_t HAL_AXIM_TARG_GetIssuingCapability(hal_axim_targ_t targ);

hal_status_t HAL_AXIM_TARG_EnablePacking(hal_axim_targ_t targ);
hal_status_t HAL_AXIM_TARG_DisablePacking(hal_axim_targ_t targ);
hal_axim_packing_status_t HAL_AXIM_TARG_IsEnabledPacking(hal_axim_targ_t targ);

hal_status_t HAL_AXIM_TARG_EnableLongBurst(hal_axim_targ_t targ);
hal_status_t HAL_AXIM_TARG_DisableLongBurst(hal_axim_targ_t targ);
hal_axim_long_burst_status_t HAL_AXIM_TARG_IsEnabledLongBurst(hal_axim_targ_t targ);

/**
  * @}
  */

/** @defgroup AXIM_Exported_Functions_Group3 AXIM Information function prototypes.
  * @{
  */
void HAL_AXIM_GetPeripheralInfo(hal_axim_periph_info_t *p_periph_info);
void HAL_AXIM_GetComponentInfo(hal_axim_component_info_t *p_component_info);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* AXIM */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_AXIM_H */
